#include <stdio.h>
#include "HD44780Driver.hpp"
#include "OneWire.hpp"
#include "DS18b20.hpp"
#include "utils/utils.h"
#include <string.h>
#include <stdlib.h>
#include <avr/interrupt.h>

uint32_t someCount{ 0u };
uint32_t seconds{ 0u };
ISR( TIMER1_OVF_vect )
{
    ++someCount;
    if( someCount > 244u )
    {
        someCount = 0u;
        ++seconds;
    }
}

char indexToCharHex( uint8_t index )
{
    if( index < 10 )
        return '0' + index;
    else
        return 'A' + index - 10;
}

constexpr bool testLCD{ false };

int main( void )
{
    char cnt[10];
    char firstLine[16];
    char secondLine[16];
    memset( cnt, 0, sizeof( cnt ) );
    memset( firstLine, 0, sizeof( firstLine ) );
    memset( secondLine, 0, sizeof( secondLine ) );

    float temperature;

    HD44780Driver driver( 'C', 'B', 0, 1, 2 );

    OneWireDriver owDriver( 'D', 0 );
    DS18B20 dsDriver( owDriver );

    // setPinMode( 'D', 0, Write );  // Button
    setPinMode( 'D', 1, Read );  // Led

    uint8_t seconds{ 0u };
    bool onOff{ true };

    while( 1 )
    {
        if( testLCD )
        {
            for( uint8_t row = 0; row < 2; ++row )
            {
                for( uint8_t column = 0; column < 16; ++column )
                {
                    char hexChar = indexToCharHex( column );
                    driver.writeCharacter( hexChar, column, row );
                }
            }
        }
        else
        {
            if( onOff )
            {
                temperature = dsDriver.readTemperature();
                dtostrf( temperature, 4, 3, cnt );
                sprintf( firstLine, "Temp: %s C", cnt );
                sprintf( secondLine, "Seconds: %lu", (unsigned long)seconds );
                driver.writeString( firstLine, 0, 0 );
                driver.writeString( secondLine, 0, 1 );
            }

            // onOff = !onOff;
            // if( onOff )
            // {
            //     driver.setLightMode( EDisplayLightMode::On );
            // }
            // else
            // {
            //     driver.setLightMode( EDisplayLightMode::Off );
            // }
        }

        ut_waitForMs( 1000 );
        ++seconds;
    }
}