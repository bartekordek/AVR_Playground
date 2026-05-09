#include "DS18b20.hpp"
#include "OneWire.hpp"
#include "utils/utils.hpp"

static const uint16_t kDS18B20_DeviceNotFound = 0xA800;
static const uint8_t kReadScatchPad = 0xBE;
static const uint16_t kDS18B20_CrcCheckFailed = 0x5000;

// Scratch pad data indexes
static const uint8_t kScratchPad_tempLSB = 0;
static const uint8_t kScratchPad_tempMSB = 1;
static const uint8_t kScratchPad_crc = 8;

DS18B20::DS18B20( OneWireDriver& inOneWire ) : m_oneWire( inOneWire )
{
}

float DS18B20::readTemperature()
{
    float result = 0.f;
    if( m_oneWire.reset() )
    {
        m_oneWire.convert();
        Utils::waitForUs( 750 );

        // Get the raw 2-byte temperature reading
        int16_t reading = readSingle();

        if( reading != kDS18B20_CrcCheckFailed )
        {
            // Convert to floating point (or keep as a Q12.4 fixed point value)
            result = ( (float)reading ) / 16;
        }
        else
        {
            // Handle bad temperature reading CRC
            // The datasheet suggests to just try reading again
        }
    }

    return result;
}

int16_t DS18B20::readSingle()
{
    // Confirm the device is still alive. Abort if no reply
    if( !m_oneWire.reset() )
    {
        return kDS18B20_DeviceNotFound;
    }

    // Reading a single device, so skip sending a device address
    m_oneWire.skiprom();
    m_oneWire.write( kReadScatchPad );

    // Read the data from the scratch pad
    return readScratchPad();
}

uint16_t DS18B20::readScratchPad()
{
    // Read scratchpad into buffer (LSB byte first)
    static const int8_t kScratchPadLength = 9;
    uint8_t buffer[kScratchPadLength];

    for( int8_t i = 0; i < kScratchPadLength; ++i )
    {
        buffer[i] = m_oneWire.read();
    }

    // Check the CRC (9th byte) against the 8 bytes of data
    if( Utils::crc8( buffer, 8 ) != buffer[kScratchPad_crc] )
    {
        return kDS18B20_CrcCheckFailed;
    }

    // Return the raw 9 to 12-bit temperature value
    return ( buffer[kScratchPad_tempMSB] << 8 ) | buffer[kScratchPad_tempLSB];
}

DS18B20::~DS18B20()
{
}