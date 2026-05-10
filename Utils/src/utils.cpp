#include "utils/utils.hpp"
#include <avr/io.h>
#include <util/delay.h>
#include <util/crc16.h>

namespace Utils
{
// DDRx
// 1 - Pin produce data
// 0 - Pin gets data

void waitForMs( int ms )
{
    for( int i = 0; i < ms; ++i )
    {
        _delay_ms( 1 );
    }
}

void waitForUs( int us )
{
    for( int i = 0; i < us; ++i )
    {
        _delay_us( 1 );
    }
}

uint8_t crc8( uint8_t* data, uint8_t len )
{
    uint8_t crc = 0;

    for( uint8_t i = 0; i < len; ++i )
    {
        crc = _crc_ibutton_update( crc, data[i] );
    }

    return crc;
}
}  // namespace Utils