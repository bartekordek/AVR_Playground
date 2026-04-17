#ifndef __HD44780Driver_h__
#define __HD44780Driver_h__

#include <stdint.h>

typedef struct HD44780Driver
{
    int bInitialized : 1;
    char ControlPort;
    char DataPort;
    uint8_t RSPin;
    uint8_t ENPin;

    void ( *initialize )( struct HD44780Driver* self );
    void ( *writeCommand )( struct HD44780Driver* self, char command );
    void ( *writeCharacter )( struct HD44780Driver* self, char character );
    void ( *writeString )( struct HD44780Driver* self, const char* text );
} HD44780Driver;

HD44780Driver create( char inControlPort,
                      char inDataPort,
                      uint8_t inRSPin,
                      uint8_t inENPin );

void lcdPortInit( struct HD44780Driver* self );
void writeCommand( struct HD44780Driver* self, char command );
void writeChararacter( struct HD44780Driver* self, char character );
void writeString( struct HD44780Driver* self, const char* text );
#endif  // __HD44780Driver_h__
