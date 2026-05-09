#include "HD44780Driver.hpp"
#include "utils/utils.hpp"

#include <avr/io.h>
#include <util/delay.h>

namespace FunctionSet
{
constexpr uint8_t bit8_lines2_5x7px = 0b00111000;
}

namespace InstructionSet
{
constexpr uint8_t cursor_disable = 0b00001100;
constexpr uint8_t cursor_blink = 0b00001111;
}  // namespace InstructionSet

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
    Utils::setWholePortMode( m_dataPort, Utils::Write );
    Utils::setWholePortMode( m_controlPort, Utils::Write );

    writeCommand( FunctionSet::bit8_lines2_5x7px );
    writeCommand( InstructionSet::cursor_disable );
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
    setPinValue( m_controlPort, m_RSPin, Utils::Low );
    // Set EN to 1 to latch data
    setPinValue( m_controlPort, m_ENPin, Utils::High );
    // Put command into the 8-bit PORT
    Utils::setWholePortValue( m_dataPort, command );
    // Clear EN to finish
    setPinValue( m_controlPort, m_ENPin, Utils::Low );
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
    Utils::setPinValue( m_controlPort, m_RSPin, Utils::High );
    // Set EN to 1 to latch data
    Utils::setPinValue( m_controlPort, m_ENPin, Utils::High );
    // Put character into the 8-bit PORT
    Utils::setWholePortValue( m_dataPort, character );
    // Clear EN to finish
    Utils::setPinValue( m_controlPort, m_ENPin, Utils::Low );
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
            Utils::setPinValue( m_controlPort, m_LightPin, Utils::High );
            break;

        case EDisplayLightMode::Off:
            Utils::setPinValue( m_controlPort, m_LightPin, Utils::Low );
            break;

        default:
            break;
    }
}
