#pragma once

#include "Avr/IMicroController.hpp"

class Atmega: public IMicroController
{
public:
    Atmega();

    void enableInterrupts() override;
    void initADCPorts() override;
    void setPinMode( char inPortName, uint8_t inPinIndex, PinMode inMode ) override;
    void setPinValue( char inPortName, uint8_t inPinIndex, PinValue inValue ) override;
    void setWholePortMode( char inPortName, PinMode mode ) override;
    void setWholePortValue( char inPortName, uint8_t inPortValue ) override;
    PinValue getPinValue( char inPortName, uint8_t inPinIndex ) override;
    void waitForMs( int ms ) override;
    void waitForUs( int us ) override;

private:
};
