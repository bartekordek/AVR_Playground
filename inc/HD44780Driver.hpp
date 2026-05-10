#pragma once

#include <stdint.h>

enum class EDisplayLightMode : uint8_t
{
    On = 0u,
    Off,
};

class MicroController;

class HD44780Driver
{
public:
    HD44780Driver( MicroController& inMicroController,
                   char inControlPort,
                   char inDataPort,
                   uint8_t inRSPin,
                   uint8_t inENPin,
                   uint8_t inLightPin );
    void clearDisplay();
    void writeCommand( char command );
    void writeCharacter( char character );
    void writeCharacter( char character, uint8_t inColumn, uint8_t inRow );
    void writeString( const char* text );
    void writeString( const char* inText, uint8_t inColumn, uint8_t inRow );

    void setLightMode( EDisplayLightMode inMode );

    ~HD44780Driver();

protected:
private:
    MicroController& m_microController;
    char m_controlPort;
    char m_dataPort;
    uint8_t m_RSPin;
    uint8_t m_ENPin;
    uint8_t m_LightPin;
};
