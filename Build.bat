@echo off



echo Root: %AVR_ROOT%
set AVR_BIN=%AVR_ROOT%\bin
set AVR_GCC=%AVR_BIN%\avr-gcc
set AVR_OBJCOPY=%AVR_BIN%\avr-objcopy
set AVR_AR=%AVR_BIN%\avr-ar
echo BIN: %AVR_BIN%
echo GCC: %AVR_GCC%
echo OBJCOPY: %AVR_OBJCOPY%
echo AR: %AVR_AR%

set C_STANDARD=-std=c17
set C_FLAGS=-mmcu=atmega32 -DF_CPU=16000000UL -Os %C_STANDARD% -Wall -Wextra -Werror

setlocal

pushd Utils
call Build.bat
popd
if errorlevel 1 exit /b 1

echo Compile program...
set SOURCES=src/main.c src/HD44780Driver.c
set INC_DIRS=-Iinc -IUtils/inc
%AVR_GCC% %SOURCES% %INC_DIRS% -LUtils -lutil -o main.elf %C_FLAGS%
if errorlevel 1 exit /b 1

echo Change name to hex...
%AVR_OBJCOPY% main.elf -O ihex main.hex
if errorlevel 1 exit /b 1

echo Done.
exit /b 0