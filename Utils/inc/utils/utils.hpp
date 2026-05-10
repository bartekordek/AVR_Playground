#pragma once

#include <stdint.h>

namespace Utils
{

void waitForMs( int ms );
void waitForUs( int us );

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