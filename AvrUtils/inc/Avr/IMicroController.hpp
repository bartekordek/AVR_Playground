#pragma once

#include <stdint.h>

enum class PinMode : uint8_t
{
    None = 0u,
    Read,
    Write
};

enum class PinValue : uint8_t
{
    High = 0u,
    Low
};

class IMicroController
{
public:
    IMicroController() = default;
    virtual void initADCPorts() = 0;
    virtual void setPinMode( char inPortName, uint8_t inPinIndex, PinMode inMode ) = 0;
    virtual void setPinValue( char inPortName, uint8_t inPinIndex, PinValue inValue ) = 0;
    virtual void setWholePortMode( char inPortName, PinMode mode ) = 0;
    virtual void setWholePortValue( char inPortName, uint8_t inPortValue ) = 0;
    virtual PinValue getPinValue( char inPortName, uint8_t inPinIndex ) = 0;
    virtual void waitForMs( int ms ) = 0;
    virtual void waitForUs( int us ) = 0;

    ~IMicroController() = default;

protected:
private:
};