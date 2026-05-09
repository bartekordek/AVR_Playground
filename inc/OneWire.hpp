#pragma once

#include <stdint.h>

class IMicroController;

class OneWireDriver
{
public:
    OneWireDriver( IMicroController& inMicroController,
                   char inControlPort,
                   int8_t inDataPin );

    bool reset();
    void convert();
    void skiprom();
    void write( uint8_t inByte );
    uint8_t read();

    ~OneWireDriver();

protected:
private:
    void outputHigh();
    void outputLow();
    void output();
    void setInputHiz();

    void writeBit( uint8_t bit );
    uint8_t onewire_read_bit();

    IMicroController& m_microController;
    char m_ControlPort;
    int8_t m_DataPin;
};
