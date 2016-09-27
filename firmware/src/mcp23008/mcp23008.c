#include <xc.h>
#include "mcp23008.h"
               

#define MCP23008_ADDRESS  0x20
unsigned char gControlByte = 0x40;
// http://revealdtech.blogspot.fr/2014/06/pic-microcontroller-interfacing-i2c.html
static unsigned char I2CBaudGenerator = 0x27;	//0x12 = 100kHz I2C
static unsigned char gAddrPins = 0x20;

#define WrtCmd  0
#define RdCmd   1

/*****************************************************************
	int I2CReadByte(unsigned char addr))
	Reads a byte from the MCP23X08/17	
******************************************************************/
unsigned char I2CReadByte(unsigned char reg)
{
	unsigned char num;
	return(num);
}

/*****************************************************************
	I2CWriteByte(unsigned char addr, unsigned char byte)
	Writes a byte to the 23017
*****************************************************************/
void I2CWriteByte(unsigned char reg, unsigned char data)
{
	StartI2C();
    IdleI2C();
	WriteI2C( gAddrPins );
	IdleI2C();
	WriteI2C( reg );
	IdleI2C();
	WriteI2C( data );
	IdleI2C();
	StopI2C();
}

void MCP23008_Write(unsigned char reg, unsigned char data) {
    I2CWriteByte(GPIO, data);
}

// http://www.vincenzov.net/tutorial/PIC18/Code/i2c-MCP23017.c


static char is_init = 0;
void MCP23008_Init() {
    
    gAddrPins = MCP23008_ADDRESS | 0x0;
    
    if (is_init != 0) {
        //return;
    }

    SSPADD = I2CBaudGenerator;
    
    OpenI2C(MASTER, SLEW_ON);
    
    //I2CWriteByte(GPPU, 0xFF);    // Set Pull-up resistors
    I2CWriteByte(IODIR, 0x00);   // Rows = inputs; Columns = outputs
    I2CWriteByte(GPIO, 0xFF);    // Row is kept LOW while changing I/O
    //I2CWriteByte(INTCON, 0xF0);  // High nibble compares against DEFVAL
    //I2CWriteByte(DEFVAL, 0xF0);  // INT if any bits in high nibble = 0
    //I2CWriteByte(GPINTEN, 0xF0); // Interrupt on change of Rows
    
    is_init = 1;
}