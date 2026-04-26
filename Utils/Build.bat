@echo off

echo Compile utils lib...
echo AVR_GPP: %AVR_GPP%
%AVR_GPP% -c src/utils.cpp -Iinc %CPP_FLAGS% -o utils.o
if errorlevel 1 exit /b 1
echo Done.

echo Linking libutil...
%AVR_AR% rcs libutil.a utils.o
if errorlevel 1 exit /b 1

echo Done.