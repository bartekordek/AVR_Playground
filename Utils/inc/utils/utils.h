#ifndef __lib_utils_h__
#define __lib_utils_h__

#include <stdint.h>

enum PinMode
{
    None = 0,
    Read,
    Write
};

enum PinValue
{
    High,
    Low
};

void setPinValue( char inPortName, uint8_t inPinIndex, enum PinValue value );
void setPinMode( char inPortName, uint8_t inPinIndex, enum PinMode mode );
void ut_setWholePortMode( char inPortName, enum PinMode mode );
void ut_setWholePortValue( char inPortName, uint8_t inPortValue );

void ut_waitForMs( int ms );

#endif  // __lib_utils_h__