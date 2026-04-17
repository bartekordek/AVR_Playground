#include <stdio.h>
#include "HD44780Driver.h"
#include "utils/utils.h"

int main( void )
{
    char cnt[10] = "", timeCnt = 0;

    HD44780Driver driver = create( 'C', 'B', 0, 1 );
    driver.initialize( &driver );
    setPinMode( 'D', 1, Write );

    while( 1 )
    {
        timeCnt++;
        // Convert timeCnt to String
        sprintf( cnt, "%d  ", timeCnt );
        // Select the upper right
        driver.writeCommand( &driver, 0x80 );
        /*Writing the text to the display*/
        driver.writeString( &driver, "Powered Up Time" );
        /*Select Second Line*/
        driver.writeCommand( &driver, 0xC0 );
        driver.writeString( &driver, cnt );
        driver.writeCommand( &driver, 0xC4 );
        driver.writeString( &driver, "Seconds1" );
        // setPinValue( 'D', 1, High );
        ut_waitForMs( 1000 );
        setPinValue( 'D', 1, Low );
    }
}