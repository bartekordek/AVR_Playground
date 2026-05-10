#include "utils/utils.hpp"
#include <avr/io.h>
#include <util/delay.h>
#include <util/crc16.h>

namespace Utils
{
// DDRx
// 1 - Pin produce data
// 0 - Pin gets data

void setWholePortMode( char inPortName, enum PinMode mode )
{
    switch( inPortName )
    {
        case 'a':
        case 'A':
            DDRA = ( mode == Write ) ? 0xFF : 0x00;
            break;
        case 'b':
        case 'B':
            DDRB = ( mode == Write ) ? 0xFF : 0x00;
            break;
        case 'c':
        case 'C':
            DDRC = ( mode == Write ) ? 0xFF : 0x00;
            break;
        case 'd':
        case 'D':
            DDRD = ( mode == Write ) ? 0xFF : 0x00;
            break;
    }
}

void setWholePortValue( char inPortName, uint8_t inPortValue )
{
    switch( inPortName )
    {
        case 'a':
        case 'A':
            PORTA = inPortValue;
            break;
        case 'b':
        case 'B':
            PORTB = inPortValue;
            break;
        case 'c':
        case 'C':
            PORTC = inPortValue;
            break;
        case 'd':
        case 'D':
            PORTD = inPortValue;
            break;
    }
}

void waitForMs( int ms )
{
    for( int i = 0; i < ms; ++i )
    {
        _delay_ms( 1 );
    }
}

void waitForUs( int us )
{
    for( int i = 0; i < us; ++i )
    {
        _delay_us( 1 );
    }
}

uint8_t crc8( uint8_t* data, uint8_t len )
{
    uint8_t crc = 0;

    for( uint8_t i = 0; i < len; ++i )
    {
        crc = _crc_ibutton_update( crc, data[i] );
    }

    return crc;
}
}  // namespace Utils