#include "OneWire.hpp"
#include "utils/utils.hpp"

// Command bytes
static const uint8_t kConvertCommand = 0x44;
static const uint8_t kReadScatchPad = 0xBE;
static const int8_t kScratchPadLength = 9;

// Scratch pad data indexes
static const uint8_t kScratchPad_tempLSB = 0;
static const uint8_t kScratchPad_tempMSB = 1;
static const uint8_t kScratchPad_crc = 8;

// Special return values
static const uint16_t kDS18B20_DeviceNotFound = 0xA800;
static const uint16_t kDS18B20_CrcCheckFailed = 0x5000;

uint8_t reset( struct OneWireDriver* self );
void outputHigh( struct OneWireDriver* self );

OneWireDriver::OneWireDriver( char inControlPort, int8_t inDataPin )
    : m_ControlPort( inControlPort )
    , m_DataPin( inDataPin )
{
}

bool OneWireDriver::reset()
{
    outputHigh();
    output();

    outputLow();
    Utils::waitForUs( 480 );

    setInputHiz();
    Utils::waitForUs( 70 );

    Utils::PinValue result = Utils::getPinValue( m_ControlPort, m_DataPin );
    Utils::waitForUs( 460 );

    return result == Utils::High;
}

void OneWireDriver::convert()
{
    skiprom();
    write( kConvertCommand );
}

void OneWireDriver::skiprom()
{
    write( 0xCC );
}

void OneWireDriver::outputHigh()
{
    setPinValue( m_ControlPort, m_DataPin, Utils::High );
}

void OneWireDriver::output()
{
    setPinMode( m_ControlPort, m_DataPin, Utils::Read );
}

void OneWireDriver::setInputHiz()
{
    setPinMode( m_ControlPort, m_DataPin, Utils::Write );
    outputLow();
}

void OneWireDriver::outputLow()
{
   setPinValue( m_ControlPort, m_DataPin, Utils::Low );
}

void OneWireDriver::write( uint8_t inByte )
{
    // Configure for output
    outputHigh();
    output();

    for( uint8_t i = 8; i != 0; --i )
    {
        writeBit( inByte & 0x1 );

        // Next bit (LSB first)
        inByte >>= 1;
    }
}

void OneWireDriver::writeBit( uint8_t bit )
{
    if( bit != 0 )
    {  // Write high

        // Pull low for less than 15uS to write a high
        outputLow();
        Utils::waitForUs( 5 );
        outputHigh();

        // Wait for the rest of the minimum slot time
        Utils::waitForUs( 55 );
    }
    else
    {  // Write low

        // Pull low for 60 - 120uS to write a low
        outputLow();
        Utils::waitForUs( 55 );

        // Stop pulling down line
        outputHigh();

        // Recovery time between slots
        Utils::waitForUs( 5 );
    }
}

uint8_t OneWireDriver::read()
{
    uint8_t buffer = 0x0;

    // Configure for input
    setInputHiz();

    // Read 8 bits (LSB first)
    for( uint8_t bit = 0x01; bit; bit <<= 1 )
    {
        // Copy read bit to least significant bit of buffer
        if( onewire_read_bit() )
        {
            buffer |= bit;
        }
    }

    return buffer;
}

uint8_t OneWireDriver::onewire_read_bit()
{  // Pull the 1-wire bus low for >1uS to generate a read slot
    outputLow();
    output();
    Utils::waitForUs( 1 );

    // Configure for reading (releases the line)
    setInputHiz();

    // Wait for value to stabilise (bit must be read within 15uS of read slot)
    Utils::waitForUs( 10 );

    uint8_t result = Utils::getPinValue( m_ControlPort, m_DataPin ) != Utils::High;

    // Wait for the end of the read slot
    Utils::waitForUs( 50 );

    return result;
}
