#pragma once

#include <stdint.h>

enum class PinMode : uint8_t
{
    Output,
    Input
};

enum class PinValue : uint8_t
{
    High = 0u,
    Low
};

class MicroController
{
public:
    MicroController();
    void enableInterrupts();
    void initADCPorts();
    uint16_t ADC_ReadStable( uint8_t channel );
    uint16_t ADC_Read( uint8_t channel );

    void setPinMode( char inPortName, uint8_t inPinIndex, PinMode inMode );
    void setPinValue( char inPortName, uint8_t inPinIndex, PinValue inValue );
    void setWholePortMode( char inPortName, PinMode mode );
    void setWholePortValue( char inPortName, uint8_t inPortValue );
    PinValue getPinValue( char inPortName, uint8_t inPinIndex );

protected:
private:
};