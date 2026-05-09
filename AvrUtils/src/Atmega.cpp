#include "Avr/Atmega.hpp"
#include <avr/interrupt.h>

Atmega::Atmega()
{
}

void Atmega::initADCPorts()
{
}

void Atmega::enableInterrupts()
{
    TCCR1A = 0;
    TCCR1B = ( 1 << CS12 );   // prescaler 256
    TCNT1 = 3036;             // preload for 1 second
    TIMSK |= ( 1 << TOIE1 );  // enable overflow interrupt

    sei();
}

void Atmega::setPinMode( char inPortName, uint8_t inPinIndex, PinMode inMode )
{
}

void Atmega::setPinValue( char inPortName, uint8_t inPinIndex, PinValue inValue )
{
}

void Atmega::setWholePortMode( char inPortName, PinMode mode )
{
}

void Atmega::setWholePortValue( char inPortName, uint8_t inPortValue )
{
}

PinValue Atmega::getPinValue( char inPortName, uint8_t inPinIndex )
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

void Atmega::waitForMs( int ms )
{
}

void Atmega::waitForUs( int us )
{
}
