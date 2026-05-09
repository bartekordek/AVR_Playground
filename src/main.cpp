#include "Avr/Atmega.hpp"

#include <stdio.h>
#include "HD44780Driver.hpp"
#include "OneWire.hpp"
#include "DS18b20.hpp"
#include "utils/utils.hpp"
#include <string.h>
#include <stdlib.h>
#include <avr/interrupt.h>

class CTime
{
public:
    void incSec()
    {
        ++Seconds;
        if( Seconds > 60u )
        {
            Seconds = 0u;
            ++Minutes;
        }

        if( Minutes > 60u )
        {
            Minutes = 0u;
            ++Hours;
        }

        if( Hours > 24u )
        {
            Hours = 0u;
            ++Days;
        }
    }

    volatile uint8_t Seconds{ 0u };
    volatile uint8_t Minutes{ 0u };
    volatile uint8_t Hours{ 0u };
    volatile uint8_t Days{ 0u };

protected:
private:
};

Atmega atmega;

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

float getLastOrNew( DS18B20& driver, float lastTemperature )
{
    constexpr float deltaT = 1.f;
    float result = getValue( driver );
    while( ( result < lastTemperature - deltaT ) ||
           ( result > lastTemperature + deltaT ) )
    {
        result = getValue( driver );
    }
    return result;
}

volatile uint8_t Seconds{ 0u };
volatile uint8_t Minutes{ 0u };
volatile uint8_t Hours{ 0u };
volatile uint8_t Days{ 0u };
volatile uint32_t timeSinceScreenTurnedOn{ 0u };
CTime g_upTime;
ISR( TIMER1_OVF_vect )
{
    TCNT1 = 3036;  // reload every second
    g_upTime.incSec();
    ++timeSinceScreenTurnedOn;
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
    atmega.enableInterrupts();

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

    Utils::setPinMode( 'D', 1, Utils::Write );  // Button

    uint8_t seconds{ 0u };
    bool onOff{ true };

    float temperature = getValue( dsDriver );
    float lastTemperature = temperature;
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
                temperature = getLastOrNew( dsDriver, lastTemperature );
                lastTemperature = temperature;
                temperatureLow = Utils::ut_min( temperatureLow, temperature );
                temperatureHigh = Utils::ut_max( temperatureHigh, temperature );

                dtostrf( temperature, 5, 2, cnt0 );
                dtostrf( temperatureLow, 4, 1, cnt1 );
                dtostrf( temperatureHigh, 4, 1, cnt2 );

                sprintf( firstLine, "%s %s/%s", cnt0, cnt1, cnt2 );
                sprintf( secondLine,
                         "%2dh:%2dm:%2ds",
                         g_upTime.Hours,
                         g_upTime.Minutes,
                         g_upTime.Seconds );
                driver.writeString( firstLine, 0, 0 );
                driver.writeString( secondLine, 0, 1 );
            }

            if( seconds > 8 )
            {
                driver.setLightMode( EDisplayLightMode::Off );
            }

            if( Utils::getPinValue( 'D', 1 ) != Utils::Low )
            {
                seconds = 0;
                driver.setLightMode( EDisplayLightMode::On );
            }
        }

        Utils::waitForMs( 1000 );
        ++seconds;
    }
}