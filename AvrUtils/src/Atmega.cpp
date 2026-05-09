#include "Avr/Atmega.hpp"

Atmega::Atmega()
{
}

void Atmega::initADCPorts()
{
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
    return PinValue();
}

void Atmega::waitForMs( int ms )
{
}

void Atmega::waitForUs( int us )
{
}
