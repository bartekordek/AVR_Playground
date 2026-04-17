#include "utils/utils.h"
#include <avr/io.h>
#include <util/delay.h>

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
            DDRA |= ( ( mode == Write ) ? ( 1 << inPinIndex ) : 0 );
            break;
        case 'b':
        case 'B':
            DDRB |= ( ( mode == Write ) ? ( 1 << inPinIndex ) : 0 );
            break;
        case 'c':
        case 'C':
            DDRC |= ( ( mode == Write ) ? ( 1 << inPinIndex ) : 0 );
            break;
        case 'd':
        case 'D':
            DDRD |= ( ( mode == Write ) ? ( 1 << inPinIndex ) : 0 );
            break;
    }
}

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