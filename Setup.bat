@echo off
setlocal enabledelayedexpansion

set "TOOLCHAIN_VERSION=avr8-gnu-toolchain-4.0.0.52-win32.any.x86_64"
set "TOOLCHAIN_ZIP=%TOOLCHAIN_VERSION%.zip"
set "TOOLCHAIN_URL=https://ww1.microchip.com/downloads/aemDocuments/documents/DEV/ProductDocuments/SoftwareTools/%TOOLCHAIN_ZIP%"

set "AVRDUDE_VERSION=avrdude-v8.1-windows-x64"
set "AVRDUDE_ZIP=%AVRDUDE_VERSION%.zip"
set "AVRDUDE_URL=https://github.com/avrdudes/avrdude/releases/download/v8.1/%AVRDUDE_ZIP%"

set "NINJA_VERSION=ninja-win"
set "NINJA_ZIP=%NINJA_VERSION%.zip"
set "NINJA_URL=https://github.com/ninja-build/ninja/releases/download/v1.13.2/%NINJA_ZIP%"

set "TARGET_DIR=3rd_party"

set "TOOLCHAIN_ZIP_PATH=%TARGET_DIR%\%TOOLCHAIN_ZIP%"
set "TOOLCHAIN_EXTRACT_DIR=%TARGET_DIR%\%TOOLCHAIN_VERSION%"

set "AVRDUDE_ZIP_PATH=%TARGET_DIR%\%AVRDUDE_ZIP%"
set "AVRDUDE_EXTRACT_DIR=%TARGET_DIR%\%AVRDUDE_VERSION%"

set "NINJA_ZIP_PATH=%TARGET_DIR%\%NINJA_ZIP%"
set "NINJA_EXTRACT_DIR=%TARGET_DIR%\ninja"


if not exist "%TARGET_DIR%" (
    mkdir "%TARGET_DIR%"
)

if not exist "%TARGET_DIR%\avrdude" (
    mkdir "%TARGET_DIR%\avrdude"
)

if not exist "%TOOLCHAIN_EXTRACT_DIR%" (
    echo Downloading AVR8 GNU Toolchain...
    echo URL: %TOOLCHAIN_URL%

    where curl >nul 2>nul
    if %errorlevel%==0 (
        curl --ssl-no-revoke -L "%TOOLCHAIN_URL%" -o "%TOOLCHAIN_ZIP_PATH%"
    ) else (
        powershell -NoProfile -ExecutionPolicy Bypass -Command ^
            "[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; Invoke-WebRequest -UseBasicParsing -Uri '%TOOLCHAIN_URL%' -OutFile '%TOOLCHAIN_ZIP_PATH%'"
    )

    if errorlevel 1 (
        echo Toolchain download failed.
        exit /b 1
    )

    echo Extracting AVR8 GNU Toolchain...

    where tar >nul 2>nul
    if %errorlevel%==0 (
        tar -xf "%TOOLCHAIN_ZIP_PATH%" -C "%TARGET_DIR%"
    ) else (
        powershell -NoProfile -ExecutionPolicy Bypass -Command ^
            "Expand-Archive -Path '%TOOLCHAIN_ZIP_PATH%' -DestinationPath '%TARGET_DIR%' -Force"
    )

    if errorlevel 1 (
        echo Toolchain extraction failed.
        exit /b 1
    )
) else (
    echo Toolchain already exists:
    echo %TOOLCHAIN_EXTRACT_DIR%
)

echo Current directory:
echo %CD%
echo AVRDUDE_EXTRACT_DIR: %AVRDUDE_EXTRACT_DIR%

if not exist "%AVRDUDE_EXTRACT_DIR%" (
    echo Downloading avrdude...
    echo URL: %AVRDUDE_URL%

    where curl >nul 2>nul
    if %errorlevel%==0 (
        curl --ssl-no-revoke -L "%AVRDUDE_URL%" -o "%AVRDUDE_ZIP_PATH%"
    ) else (
        powershell -NoProfile -ExecutionPolicy Bypass -Command ^
            "[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; Invoke-WebRequest -UseBasicParsing -Uri '%AVRDUDE_URL%' -OutFile '%AVRDUDE_ZIP_PATH%'"
    )

    where tar >nul 2>nul
    if %errorlevel%==0 (
        tar -xf "%AVRDUDE_ZIP_PATH%" -C "%TARGET_DIR%\avrdude"
    ) else (
        powershell -NoProfile -ExecutionPolicy Bypass -Command ^
            "Expand-Archive -Path '%AVRDUDE_ZIP_PATH%' -DestinationPath '%TARGET_DIR%\avrdude' -Force"
    )

) else (
    echo avrdude already exists:
    echo %AVRDUDE_EXTRACT_DIR%
)

if not exist "%NINJA_EXTRACT_DIR%" (
    echo Downloading Ninja build system...
    echo URL: %NINJA_URL%

    where curl >nul 2>nul
    if %errorlevel%==0 (
        curl --ssl-no-revoke -L "%NINJA_URL%" -o "%NINJA_ZIP_PATH%"
    ) else (
        powershell -NoProfile -ExecutionPolicy Bypass -Command ^
            "[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; Invoke-WebRequest -UseBasicParsing -Uri '%NINJA_URL%' -OutFile '%NINJA_ZIP_PATH%'"
    )

    if errorlevel 1 (
        echo Ninja download failed.
        exit /b 1
    )

    echo Extracting Ninja...

    if not exist "%NINJA_EXTRACT_DIR%" (
        mkdir "%NINJA_EXTRACT_DIR%"
    )

    where tar >nul 2>nul
    if %errorlevel%==0 (
        tar -xf "%NINJA_ZIP_PATH%" -C "%NINJA_EXTRACT_DIR%"
    ) else (
        powershell -NoProfile -ExecutionPolicy Bypass -Command ^
            "Expand-Archive -Path '%NINJA_ZIP_PATH%' -DestinationPath '%NINJA_EXTRACT_DIR%' -Force"
    )

    if errorlevel 1 (
        echo Ninja extraction failed.
        exit /b 1
    )

) else (
    echo Ninja already exists:
    echo %NINJA_EXTRACT_DIR%
)

echo Update system variables...
setx AVR_DUDE_ROOT "%TARGET_DIR%\avrdude"
setx AVR_ROOT "%TARGET_DIR%\avr8-gnu-toolchain-win32_x86_64"
setx NINJA_ROOT "%TARGET_DIR%\ninja"
echo Update system variables...done.
exit /b 0