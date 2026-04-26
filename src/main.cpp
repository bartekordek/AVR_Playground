#include <stdio.h>
#include "HD44780Driver.hpp"
#include "OneWire.hpp"
#include "DS18b20.hpp"
#include "utils/utils.hpp"
#include <string.h>
#include <stdlib.h>
#include <avr/interrupt.h>

constexpr float tempMin = -20.f;
constexpr float tempMax = 40.f;

float getValue( DS18B20& driver )
{
    float result = driver.readTemperature();
    while( !Utils::isValueCorrect( result, tempMin, tempMax ) )
    {
        result = driver.readTemperature();
    }
    return result;
}

uint32_t someCount{ 0u };
volatile uint32_t seconds{ 0u };
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
    char cnt0[10];
    char cnt1[10];
    char cnt2[10];
    char firstLine[16];
    char secondLine[16];
    memset( cnt0, 0, sizeof( cnt0 ) );
    memset( cnt1, 0, sizeof( cnt1 ) );
    memset( cnt2, 0, sizeof( cnt2 ) );

    memset( firstLine, 0, sizeof( firstLine ) );
    memset( secondLine, 0, sizeof( secondLine ) );

    HD44780Driver driver( 'C', 'B', 0, 1, 2 );

    OneWireDriver owDriver( 'D', 0 );
    DS18B20 dsDriver( owDriver );

    setPinMode( 'D', 1, Write );  // Button

    uint8_t seconds{ 0u };
    bool onOff{ true };

    float temperature = getValue( dsDriver );
    float temperatureLow = temperature;
    float temperatureHigh = temperature;

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
                temperature = getValue( dsDriver );
                temperatureLow = ut_min( temperatureLow, temperature );
                temperatureHigh = ut_max( temperatureHigh, temperature );

                dtostrf( temperature, 4, 2, cnt0 );
                dtostrf( temperatureLow, 4, 2, cnt1 );
                dtostrf( temperatureHigh, 4, 2, cnt2 );

                sprintf( firstLine, "C %s Mi %s", cnt0, cnt1 );
                sprintf( secondLine, "Max %s, %5d", cnt2, seconds );
                driver.writeString( firstLine, 0, 0 );
                driver.writeString( secondLine, 0, 1 );
            }

            if( seconds > 8 )
            {
                driver.setLightMode( EDisplayLightMode::Off );
            }

            if( ut_getPinValue( 'D', 1 ) != Low )
            {
                seconds = 0;
                driver.setLightMode( EDisplayLightMode::On );
            }
        }

        ut_waitForMs( 1000 );
        ++seconds;
    }
}