#pragma once

#include <stdint.h>

class OneWireDriver;

class DS18B20
{
public:
    DS18B20( OneWireDriver& inOneWire );

    float readTemperature();

    ~DS18B20();

protected:
private:
    int16_t readSingle();
    uint16_t readScratchPad();
    OneWireDriver& m_oneWire;
};