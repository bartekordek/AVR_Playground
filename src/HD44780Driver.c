#include "HD44780Driver.h"
#include "utils/utils.h"

#include <avr/io.h>
#include <util/delay.h>

HD44780Driver create( char inControlPort,
                      char inDataPort,
                      uint8_t inRSPin,
                      uint8_t inENPin )
{
    HD44780Driver driver;
    driver.bInitialized = 0;
    driver.ControlPort = inControlPort;
    driver.DataPort = inDataPort;
    driver.RSPin = inRSPin;
    driver.ENPin = inENPin;
    driver.initialize = lcdPortInit;
    driver.writeCommand = writeCommand;
    driver.writeCharacter = writeChararacter;
    driver.writeString = writeString;

    return driver;
}

void lcdPortInit( struct HD44780Driver* self )
{
    /*PORTC and PORTB Are Output To LCD*/
    ut_setWholePortMode( self->DataPort, Write );
    ut_setWholePortMode( self->ControlPort, Write );

    /*Writing the instructions
 8-bit mode, 2-line,5x8 dot*/
    self->writeCommand( self, 0b00111000 );
    self->writeCommand( self, 0b00111000 );
    /*Turn On Display, Cursor Off*/
    self->writeCommand( self, 0b00001100 );
    /*Cursor Shift in Increment Mode*/
    self->writeCommand( self, 0b00000110 );
}

void writeCommand( struct HD44780Driver* self, char command )
{
    // Set RS to 0
    setPinValue( self->ControlPort, self->RSPin, Low );
    // Set EN to 1 to latch data
    setPinValue( self->ControlPort, self->ENPin, High );
    // Put command into the 8-bit PORT
    ut_setWholePortValue( self->DataPort, command );
    // Clear EN to finish
    setPinValue( self->ControlPort, self->ENPin, Low );
    _delay_ms( 2 );
}

void writeChararacter( struct HD44780Driver* self, char character )
{
    // Set RS to 1
    setPinValue( self->ControlPort, self->RSPin, High );
    // Set EN to 1 to latch data
    setPinValue( self->ControlPort, self->ENPin, High );
    // Put character into the 8-bit PORT
    ut_setWholePortValue( self->DataPort, character );
    // Clear EN to finish
    setPinValue( self->ControlPort, self->ENPin, Low );
    _delay_ms( 2 );
}

void writeString( struct HD44780Driver* self, const char* text )
{
    while( *text )
    {
        writeChararacter( self, *text++ );
    }
}
