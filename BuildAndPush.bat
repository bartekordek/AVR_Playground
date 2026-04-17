@echo off

setlocal

call Build.bat
if errorlevel 1 (
    echo BUILD FAILED - aborting push
    exit /b 1
)

echo Build succeeded - pushing...
call Push.bat