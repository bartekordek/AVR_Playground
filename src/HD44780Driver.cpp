#include "HD44780Driver.hpp"
#include "utils/utils.h"

#include <avr/io.h>
#include <util/delay.h>

HD44780Driver::HD44780Driver( char inControlPort,
                              char inDataPort,
                              uint8_t inRSPin,
                              uint8_t inENPin,
                              uint8_t inLightPin )
    : m_controlPort( inControlPort )
    , m_dataPort( inDataPort )
    , m_RSPin( inRSPin )
    , m_ENPin( inENPin )
    , m_LightPin( inLightPin )

{
    setLightMode( EDisplayLightMode::On );

    /*PORTC and PORTB Are Output To LCD*/
    ut_setWholePortMode( m_dataPort, Write );
    ut_setWholePortMode( m_controlPort, Write );

    /*Writing the instructions
 8-bit mode, 2-line,5x8 dot*/
    writeCommand( 0b00111000 );
    writeCommand( 0b00111000 );
    /*Turn On Display, Cursor Off*/
    writeCommand( 0b00001100 );
    /*Cursor Shift in Increment Mode*/
    writeCommand( 0b00000110 );

    clearDisplay();
}

void HD44780Driver::clearDisplay()
{
    writeCommand( 0b00000001 );
}

void HD44780Driver::writeCommand( char command )
{
    // Set RS to 0
    setPinValue( m_controlPort, m_RSPin, Low );
    // Set EN to 1 to latch data
    setPinValue( m_controlPort, m_ENPin, High );
    // Put command into the 8-bit PORT
    ut_setWholePortValue( m_dataPort, command );
    // Clear EN to finish
    setPinValue( m_controlPort, m_ENPin, Low );
    _delay_ms( 2 );
}

void HD44780Driver::writeCharacter( char character, uint8_t inColumn, uint8_t inRow )
{
    uint8_t address = 0;

    // Convert row/column to DDRAM address
    switch( inRow )
    {
        case 0:
        {
            address = 0x00 + inColumn;
            break;
        }

        case 1:
        {
            address = 0x40 + inColumn;
            break;
        }

        case 2:
        {
            address = 0x14 + inColumn;
            break;
        }

        case 3:
        {
            address = 0x54 + inColumn;
            break;
        }

        default:
        {
            address = 0x00;
            break;
        }
    }

    // Set cursor position
    writeCommand( 0x80 | address );

    // Write single character
    writeCharacter( character );
}

void HD44780Driver::writeCharacter( char character )
{
    // Set RS to 1
    setPinValue( m_controlPort, m_RSPin, High );
    // Set EN to 1 to latch data
    setPinValue( m_controlPort, m_ENPin, High );
    // Put character into the 8-bit PORT
    ut_setWholePortValue( m_dataPort, character );
    // Clear EN to finish
    setPinValue( m_controlPort, m_ENPin, Low );
    _delay_ms( 2 );
}

void HD44780Driver::writeString( const char* inText, uint8_t inColumn, uint8_t inRow )
{
    uint8_t address = 0;

    // Convert row/column to DDRAM address
    switch( inRow )
    {
        case 0:
        {
            address = 0x00 + inColumn;
            break;
        }

        case 1:
        {
            address = 0x40 + inColumn;
            break;
        }

        // Optional support for 20x4 displays
        case 2:
        {
            address = 0x14 + inColumn;
            break;
        }

        case 3:
        {
            address = 0x54 + inColumn;
            break;
        }

        default:
        {
            address = 0x00;
            break;
        }
    }

    // Set DDRAM address
    writeCommand( 0x80 | address );

    // Write the text starting from that position
    writeString( inText );
}

void HD44780Driver::writeString( const char* text )
{
    while( *text )
    {
        writeCharacter( *text++ );
    }
}

void HD44780Driver::setLightMode( EDisplayLightMode inMode )
{
    switch( inMode )
    {
        case EDisplayLightMode::On:
            setPinValue( m_controlPort, m_LightPin, High );
            break;

        case EDisplayLightMode::Off:
            setPinValue( m_controlPort, m_LightPin, Low );
            break;

        default:
            break;
    }
}
