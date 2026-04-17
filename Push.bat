@echo off

setlocal

set AVR_DUDE_ROOT=3rd_party\avrdude
echo AVR_DUDE_ROOT: %AVR_DUDE_ROOT%
set AVR_DUDE_BIN=%AVR_DUDE_ROOT%\avrdude
echo AVR_DUDE_BIN: %AVR_DUDE_BIN%

%AVR_DUDE_BIN% -c usbasp -p atmega32 -U flash:w:main.hex:i