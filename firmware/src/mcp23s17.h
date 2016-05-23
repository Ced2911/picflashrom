#ifndef MCP23S17_H
#define	MCP23S17_H

// MCP23S17
// #defines assume IOCON.BANK = 0
#define IODIRA   	0x00
#define IODIRB   	0x01
#define IPOLA    	0x02
#define IPOLB    	0x03
#define GPINTENA 	0x04
#define GPINTENB 	0x05
#define DEFVALA  	0x06
#define DEFVALB  	0x07
#define INTCONA  	0x08
#define INTCONB  	0x09
#define IOCONA   	0x0A
#define IOCONB   	0x0B
#define GPPUA    	0x0C
#define GPPUB    	0x0D
#define INTFA    	0x0E
#define INTFB    	0x0F
#define INTCAPA  	0x010
#define INTCAPB  	0x011
#define GPIOA    	0x012
#define GPIOB    	0x013
#define OLATA    	0x014
#define OLATB    	0x015

#define IODIR       IODIRA
#define GPPU        GPPUA
#define GPIO        GPIOA
#define IOCON       IOCONA

void SPI_Init();
void MCP_Init(unsigned char slave_addr);
void MCP_Write(unsigned char slave_addr, unsigned char port, unsigned char data);
void MCP_Write16(unsigned char slave_addr, unsigned char port, unsigned short data);
void MCP_Write16AB(unsigned char slave_addr, unsigned char port, unsigned char a,unsigned char b );
unsigned char MCP_Read(unsigned char slave_addr, unsigned char port);

#endif

