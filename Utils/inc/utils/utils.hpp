#pragma once

#include <stdint.h>

namespace Utils
{

enum PinMode
{
    None = 0,
    Read,
    Write
};

enum PinValue
{
    High = 0u,
    Low
};

void setPinValue( char inPortName, uint8_t inPinIndex, enum PinValue value );
void setPinMode( char inPortName, uint8_t inPinIndex, enum PinMode mode );
void setWholePortMode( char inPortName, enum PinMode mode );
void setWholePortValue( char inPortName, uint8_t inPortValue );

void waitForMs( int ms );
void waitForUs( int us );

PinValue getPinValue( char inPortName, uint8_t inPinIndex );

uint8_t crc8( uint8_t* data, uint8_t len );

template <typename Type>
Type ut_min( Type a, Type b )
{
    return ( a < b ) ? a : b;
}

template <typename Type>
Type ut_max( Type a, Type b )
{
    return ( a > b ) ? a : b;
}

template <typename Type>
Type discardWrongValue( Type inMinValue,
                        Type inMaxValue,
                        Type inCurrentValue,
                        Type inPreviousValue )
{
    if( inCurrentValue < inMinValue )
    {
        return inPreviousValue;
    }

    if( inCurrentValue > inMaxValue )
    {
        return inPreviousValue;
    }

    return inCurrentValue;
}

template <typename Type>
bool isValueCorrect( Type inCurrentValue, Type inMinValue, Type inMaxValue )
{
    if( inCurrentValue < inMinValue )
    {
        return false;
    }

    if( inCurrentValue > inMaxValue )
    {
        return false;
    }

    return true;
}

}  // namespace Utils