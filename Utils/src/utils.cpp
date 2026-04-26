#include "utils/utils.hpp"
#include <avr/io.h>
#include <util/delay.h>
#include <util/crc16.h>

void setPinValue( char inPortName, uint8_t inPinIndex, enum PinValue value )
{
    switch( inPortName )
    {
        case 'a':
        case 'A':
        {
            if( value == High )
            {
                PORTA |= ( 1 << inPinIndex );
            }
            else
            {
                PORTA &= ~( 1 << inPinIndex );
            }

            break;
        }
        case 'b':
        case 'B':
        {
            if( value == High )
            {
                PORTB |= ( 1 << inPinIndex );
            }
            else
            {
                PORTB &= ~( 1 << inPinIndex );
            }
            break;
        }
        case 'c':
        case 'C':
        {
            if( value == High )
            {
                PORTC |= ( 1 << inPinIndex );
            }
            else
            {
                PORTC &= ~( 1 << inPinIndex );
                // cdC&= ~( 1 << RS );
            }
            break;
        }
        case 'd':
        case 'D':
        {
            if( value == High )
            {
                PORTD |= ( 1 << inPinIndex );
            }
            else
            {
                PORTD &= ~( 1 << inPinIndex );
            }
            break;
        }
    }
}

void setPinMode( char inPortName, uint8_t inPinIndex, enum PinMode mode )
{
    switch( inPortName )
    {
        case 'a':
        case 'A':
            if( mode == Read )
            {
                DDRA |= ( 1 << inPinIndex );
            }
            else
            {
                DDRA &= ~( 1 << inPinIndex );
            }
            break;
        case 'b':
        case 'B':
            if( mode == Read )
            {
                DDRB |= ( 1 << inPinIndex );
            }
            else
            {
                DDRB &= ~( 1 << inPinIndex );
            }
            break;
        case 'c':
        case 'C':
            if( mode == Read )
            {
                DDRC |= ( 1 << inPinIndex );
            }
            else
            {
                DDRC &= ~( 1 << inPinIndex );
            }
            break;
        case 'd':
        case 'D':
            if( mode == Read )
            {
                DDRD |= ( 1 << inPinIndex );
            }
            else
            {
                DDRD &= ~( 1 << inPinIndex );
            }
            break;
    }
}

// DDRx
// 1 - Pin produce data
// 0 - Pin gets data

void ut_setWholePortMode( char inPortName, enum PinMode mode )
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

void ut_setWholePortValue( char inPortName, uint8_t inPortValue )
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

void ut_waitForMs( int ms )
{
    for( int i = 0; i < ms; ++i )
    {
        _delay_ms( 1 );
    }
}

void ut_waitForUs( int us )
{
    for( int i = 0; i < us; ++i )
    {
        _delay_us( 1 );
    }
}

PinValue ut_getPinValue( char inPortName, uint8_t inPinIndex )
{
    switch( inPortName )
    {
        case 'a':
        case 'A':
            return ( PINA & ( 1 << inPinIndex ) ) > 0u ? Low : High;
        case 'b':
        case 'B':
            return ( PINB & ( 1 << inPinIndex ) ) > 0u ? Low : High;
        case 'c':
        case 'C':
            return ( PINC & ( 1 << inPinIndex ) ) > 0u ? Low : High;
        case 'd':
        case 'D':
            return ( PIND & ( 1 << inPinIndex ) ) > 0u ? Low : High;
    }
    return High;
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