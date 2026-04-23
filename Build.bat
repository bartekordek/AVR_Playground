@echo off
setlocal

set "BASE_DIR=%~dp0"
echo Current dir: %BASE_DIR%

set AVR_ROOT=%BASE_DIR%\3rd_party\avr8-gnu-toolchain-win32_x86_64
echo Root: %AVR_ROOT%
set AVR_BIN=%AVR_ROOT%\bin
set AVR_GCC=%AVR_BIN%\avr-gcc
set AVR_GPP=%AVR_BIN%\avr-g++
set AVR_OBJCOPY=%AVR_BIN%\avr-objcopy
set AVR_AR=%AVR_BIN%\avr-ar
echo BIN: %AVR_BIN%
echo GCC: %AVR_GCC%
echo GPP: %AVR_GPP%
echo OBJCOPY: %AVR_OBJCOPY%
echo AR: %AVR_AR%

set C_STANDARD=-std=c17
set CPP_STANDARD=-std=gnu++17
set C_FLAGS=-mmcu=atmega32 -DF_CPU=16000000UL -Os %C_STANDARD% -Wall -Wextra
set CPP_FLAGS=-mmcu=atmega32 -DF_CPU=16000000UL -Os %CPP_STANDARD% -Wall -Wextra -Wl,-u,vfprintf -lprintf_flt


pushd Utils

call Build.bat
popd
if errorlevel 1 exit /b 1

echo Compile program...
set SOURCES=src/main.cpp src/HD44780Driver.cpp src/OneWire.cpp src/DS18B20.cpp
set INC_DIRS=-Iinc -IUtils/inc
%AVR_GPP% %SOURCES% %INC_DIRS% -LUtils -lutil -o main.elf %CPP_FLAGS% -flto -v
if errorlevel 1 exit /b 1

echo Change name to hex...
%AVR_OBJCOPY% main.elf -O ihex main.hex
if errorlevel 1 exit /b 1

echo Done.
exit /b 0