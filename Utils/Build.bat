@echo off


echo Compile utils lib...

%AVR_GCC% -c src/utils.c -Iinc %C_FLAGS% -o utils.o
if errorlevel 1 exit /b 1
echo Done.

echo Linking libutil...
%AVR_AR% rcs libutil.a utils.o
if errorlevel 1 exit /b 1

echo Done.