/**
 * Mcp23s17 driver
 */
#include <xc.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "spi.h"
#include "mcp23s17.h"

// MCP23S17 SPI Slave Device
#define SPI_SLAVE_ID    0x40
#define SPI_SLAVE_WRITE 0x00
#define SPI_SLAVE_READ  0x01

#define PROTO_FAIL

#define CSL {PORTCbits.RC6 = 0;}
#define CSH {PORTCbits.RC6 = 1;}


// Violet/XX/bleu/gris/blanc

void SPI_Init() {  
    TRISBbits.TRISB1 = 0; // clock pin output
    //TRISBbits.TRISB0 = 1; // SDI pin input
    TRISCbits.RC6 = 0;//Pin CS
    
    SSPSTAT &= 0x3F; 
    SSPCON1 = 0x00; 
    //SSPCON1 |= 0x00; // SPI_FOSC_4 
    //SSPCON1 |= 0x02; // SPI_FOSC_4 
    SSPSTAT |= 0x80; // MODE_00
    
    SSPSTATbits.CKE = 1; //     
    SSPCON1bits.SSPEN=1;//SPI Enable
}

void MCP_Init(unsigned char slave_addr) {
    //MCP_Write(slave_addr, IOCONA, 0x18); // HAEN 
    MCP_Write(slave_addr, IOCONA, 0x00); // HAEN 
    MCP_Write(slave_addr, IOCONB, 0x00); // HAEN 
    MCP_Write(slave_addr, IODIRA, 0xff); // GPIO As Output
    MCP_Write(slave_addr, IODIRB, 0xff); // GPIO As Output
    MCP_Write(slave_addr, GPPUA, 0x00); // Disable Pull-up Resistor
    MCP_Write(slave_addr, GPPUB, 0x00); // Disable Pull-up Resistor
    MCP_Write(slave_addr, GPIOA, 0x00); // Reset Output
    MCP_Write(slave_addr, GPIOB, 0x00); // Reset Output
}

void MCP_Write16(unsigned char slave_addr, unsigned char port, unsigned short data) {
    CSL;
      
    SPI1_Exchange8bit(SPI_SLAVE_ID | ((slave_addr << 1) & 0x0E) | SPI_SLAVE_WRITE);
    SPI1_Exchange8bit(port);
    SPI1_Exchange8bit(data & 0xFF);
    SPI1_Exchange8bit(data >> 8);
    
    CSH;
}

void MCP_Write16AB(unsigned char slave_addr, unsigned char port, unsigned char a,unsigned char b ) {
    CSL;
      
    SPI1_Exchange8bit(SPI_SLAVE_ID | ((slave_addr << 1) & 0x0E) | SPI_SLAVE_WRITE);
    SPI1_Exchange8bit(port);
    SPI1_Exchange8bit(a);
    if (b) {
        SPI1_Exchange8bit(b);        
    }
    
    CSH;
}

void MCP_Write(unsigned char slave_addr, unsigned char port, unsigned char data) {
    CSL;
      
    SPI1_Exchange8bit(SPI_SLAVE_ID | ((slave_addr << 1) & 0x0E) | SPI_SLAVE_WRITE);
    SPI1_Exchange8bit(port);
    SPI1_Exchange8bit(data);
    
    CSH;
}

unsigned short MCP_Read16(unsigned char slave_addr, unsigned char port) {
    unsigned short n;
    CSL;
    
    SPI1_Exchange8bit(SPI_SLAVE_ID | ((slave_addr << 1) & 0x0E) | SPI_SLAVE_READ);
    SPI1_Exchange8bit(port);
    
    n = SPI1_Exchange8bit(0) & 0xFF;
    n = n | SPI1_Exchange8bit(0) << 8 ;
    
    CSH;

    return n;
}

unsigned char MCP_Read(unsigned char slave_addr, unsigned char port) {
    unsigned char n;
    CSL;
    
    SPI1_Exchange8bit(SPI_SLAVE_ID | ((slave_addr << 1) & 0x0E) | SPI_SLAVE_READ);
    SPI1_Exchange8bit(port);
    n = SPI1_Exchange8bit(0);
    
    CSH;

    return n;
}