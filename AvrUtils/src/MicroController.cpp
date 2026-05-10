#include "Avr/MicroController.hpp"
#include <avr/interrupt.h>

MicroController::MicroController()
{
}

void MicroController::initADCPorts()
{
}

void MicroController::enableInterrupts()
{
    TCCR1A = 0;
    TCCR1B = ( 1 << CS12 );   // prescaler 256
    TCNT1 = 3036;             // preload for 1 second
    TIMSK |= ( 1 << TOIE1 );  // enable overflow interrupt

    sei();
}

void MicroController::setPinMode( char inPortName, uint8_t inPinIndex, PinMode inMode )
{
    switch( inPortName )
    {
        case 'a':
        case 'A':
            if( inMode == PinMode::Read )
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
            if( inMode == PinMode::Read )
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
            if( inMode == PinMode::Read )
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
            if( inMode == PinMode::Read )
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

void MicroController::setPinValue( char inPortName, uint8_t inPinIndex, PinValue inValue )
{
    switch( inPortName )
    {
        case 'a':
        case 'A':
        {
            if( inValue == PinValue::High )
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
            if( inValue == PinValue::High )
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
            if( inValue == PinValue::High )
            {
                PORTC |= ( 1 << inPinIndex );
            }
            else
            {
                PORTC &= ~( 1 << inPinIndex );
            }
            break;
        }
        case 'd':
        case 'D':
        {
            if( inValue == PinValue::High )
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

void MicroController::setWholePortMode( char inPortName, PinMode inMode )
{
    switch( inPortName )
    {
        case 'a':
        case 'A':
            DDRA = ( inMode == PinMode::Write ) ? 0xFF : 0x00;
            break;
        case 'b':
        case 'B':
            DDRB = ( inMode == PinMode::Write ) ? 0xFF : 0x00;
            break;
        case 'c':
        case 'C':
            DDRC = ( inMode == PinMode::Write ) ? 0xFF : 0x00;
            break;
        case 'd':
        case 'D':
            DDRD = ( inMode == PinMode::Write ) ? 0xFF : 0x00;
            break;
    }
}

void MicroController::setWholePortValue( char inPortName, uint8_t inPortValue )
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

PinValue MicroController::getPinValue( char inPortName, uint8_t inPinIndex )
{
    switch( inPortName )
    {
        case 'a':
        case 'A':
            return ( PINA & ( 1 << inPinIndex ) ) > 0u ? PinValue::Low : PinValue::High;
        case 'b':
        case 'B':
            return ( PINB & ( 1 << inPinIndex ) ) > 0u ? PinValue::Low : PinValue::High;
        case 'c':
        case 'C':
            return ( PINC & ( 1 << inPinIndex ) ) > 0u ? PinValue::Low : PinValue::High;
        case 'd':
        case 'D':
            return ( PIND & ( 1 << inPinIndex ) ) > 0u ? PinValue::Low : PinValue::High;
    }
    return PinValue::High;
}

void MicroController::waitForMs( int ms )
{
}

void MicroController::waitForUs( int us )
{
}
