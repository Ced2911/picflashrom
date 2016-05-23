/*
 * File:   rom.c
 * Author: cc
 *
 * Created on 28 avril 2016, 09:04
 */


/**
 * Pinouts:
 * PORTA => 8bit low data
 * PORTB RB2:RB7 => A0:A5
 * PORTB RB0 MISO
 * PORTB RB1 SCK
 * PORTB RB2(shared) SPI CS
 * PORTC RC0 CE
 * PORTC RC1 OE
 * PORTC RC7 WE
 */

#include <xc.h>
#include "rom.h"
#include "mcp23s17.h"
#include "system_config.h"

#define SECTOR_SIZE_4K             4096

#define MCP_DATA_ADDR   0
#define MCP_ADDR_HIGH   1

//#define SET_ADDR_H(addr)    {MCP_Write(MCP_ADDR_HIGH, GPIOA, addr>>6); MCP_Write(MCP_ADDR_HIGH, GPIOB, addr>>14);}
#define SET_ADDR_H(addr)    {MCP_Write16AB(MCP_ADDR_HIGH, GPIOA, addr>>6, addr>>14);}
#define SET_ADDR_L(addr)    {LATB = (LATB & 3) | ((addr<<2)&0xFC);}

#define CSL {PORTC = PORTC & 0xFC;}
#define CSH {PORTC = PORTC | 0x03;}

#define CE_L_OE_H {PORTC = (PORTC & 0xFC) | 0x2 ;}
#define CE_H_OE_H {PORTC = PORTC | 0x03;}
#define CE_L    {PORTCbits.RC0 = 0;}
#define CE_H    {PORTCbits.RC0 = 1;}
#define OE_L    {PORTCbits.RC1 = 0;}
#define OE_H    {PORTCbits.RC1 = 1;}


#define DELAY_P { __delay_us(1); }
#define DELAY_CMD_X { __delay_us(2); }
#define DELAY_TWP   { __delay_us(1); }
#define OUTB(x) { LATA = x;}

// SST ! Ced config !!
#define WE_L {LATBbits.LB0 = 0;}
#define WE_H {LATBbits.LB0 = 1;}

#define PORT_DATA   PORTA

//#define DELAY_TACC  { __delay_us(2);} // OKAY
//#define DELAY_CS    { __delay_us(1);} // OKAY

#define DELAY_TACC  { __delay_us(2);} // OKAY
#define DELAY_CS    { __delay_us(1);} // OKAY
#define DELAY_CMD    { __delay_us(2);} // TEST
#define DELAY_ERASE {__delay_ms(10); } // TEST
#define DELAY_BYTE_WRITE { __delay_us(1);} // OKAY

#define MAX_EEPROM_READ    0x40

static void PORT_INIT() {
    INTCON2bits.RBPU = 0;
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    // set as portA as input
    TRISA = 0xFF;
    // set addr as output
    TRISB = 0x00;
    //TRISBbits.TRISB0 = 1; // SDI pin input

    // set port addr low as otuput
    TRISCbits.RC6 = 0;
    TRISCbits.RC7 = 0;
    TRISCbits.RC0 = 0;
    TRISCbits.RC1 = 0;

    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;

    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
}

void rom_start_read() {
    // set as portA as input
    TRISA = 0xFF;
}

void rom_start_write() {
    // set as portA as output
    TRISA = 0x00;
}

inline void rom_finish_write() {
    rom_start_read();
}

void rom_init() {
    SPI_Init();
    MCP_Init(MCP_ADDR_HIGH);
    MCP_Init(MCP_DATA_ADDR);

    //MCP23008_Init();
    PORT_INIT();

    // set addr high as otuput
    MCP_Write(MCP_ADDR_HIGH, IODIRA, 0x00);
    MCP_Write(MCP_ADDR_HIGH, IODIRB, 0x00);
    MCP_Write(MCP_ADDR_HIGH, GPIOA, 0x00);
    MCP_Write(MCP_ADDR_HIGH, GPIOB, 0x00);

    OE_L
    WE_H
    CE_H
    OE_H
}


static __inline void rom_write_8(uint32_t addr, uint8_t b) {
    SET_ADDR_H(addr);
    SET_ADDR_L(addr);
    OUTB(b);

    // adress and data already set !
    CE_L
    WE_L
    // ....
    WE_H
    CE_H
}

static void rom_send_command_8(uint8_t cmd) {
    rom_start_write();
    OE_H

    rom_write_8(0x5555, 0xAA);
    rom_write_8(0x2AAA, 0x55);
    rom_write_8(0x5555, cmd);
}


#define _READ8(a, x) \
{ \
    WE_H \
    CSH \
    SET_ADDR_H(a);  \
    SET_ADDR_L(a);  \
    CSL; \
    x = PORT_DATA;\
    CSH; \
}

#define _READ_TOGGLE(x) \
{ \
    WE_H \
    CSL; \
    x = PORT_DATA;\
    CSH; \
}

#define _START_C() { \
    OE_L;   \
    CE_H;   \
    WE_H;   \
    OE_H;   \
}

void rom_identify(uint8_t * in);

void Check_Toggle_Ready() {
    BYTE Loop = 1;
    BYTE PreData;
    BYTE CurrData;
    unsigned long TimeOut = 0;

    _READ_TOGGLE(PreData);
    PreData = PreData & 0x40;
    while ((TimeOut < 0x07FFFFFF) && (Loop)) {
        _READ_TOGGLE(CurrData);
        CurrData = CurrData & 0x40;
        if (PreData == CurrData)
            Loop = 0; /* ready to exit the while loop */
        PreData = CurrData;
        TimeOut++;
    }
}


#define DELAY_100ms() { \
__delay_ms(20); \
__delay_ms(20); \
__delay_ms(20); \
__delay_ms(20); \
__delay_ms(20); \
}

#define DELAY_200ms() { \
    DELAY_100ms(); DELAY_100ms(); \
}

#define DELAY_1s() {\
    DELAY_200ms();DELAY_200ms();DELAY_200ms();DELAY_200ms();DELAY_200ms();\
}


void rom_read(uint8_t * out, uint32_t addr, uint8_t len) {
    uint8_t p = 0;
    uint8_t * buf = out;

    WE_H;
    CSH;
    SET_ADDR_H(addr);
#if 0
    for (p = 0; p < len; p++, addr++) {
        DELAY_CS;
        SET_ADDR_L(addr);
        CSL;
        DELAY_TACC;
        * buf++ = PORT_DATA;
        CSH;
    }
#else // unroll loop
    for (p = 0; p < len; p+=8) {
        DELAY_CS;
        SET_ADDR_L(addr++);
        CSL;
        DELAY_TACC;
        *buf++ = PORT_DATA;
        CSH;
        
        DELAY_CS;
        SET_ADDR_L(addr++);
        CSL;
        DELAY_TACC;
        *buf++ = PORT_DATA;
        CSH;
        
        DELAY_CS;
        SET_ADDR_L(addr++);
        CSL;
        DELAY_TACC;
        *buf++ = PORT_DATA;
        CSH;
        
        DELAY_CS;
        SET_ADDR_L(addr++);
        CSL;
        DELAY_TACC;
        *buf++ = PORT_DATA;
        CSH;
        
        DELAY_CS;
        SET_ADDR_L(addr++);
        CSL;
        DELAY_TACC;
        *buf++ = PORT_DATA;
        CSH;
        
        DELAY_CS;
        SET_ADDR_L(addr++);
        CSL;
        DELAY_TACC;
        *buf++ = PORT_DATA;
        CSH;
        
        DELAY_CS;
        SET_ADDR_L(addr++);
        CSL;
        DELAY_TACC;
        *buf++ = PORT_DATA;
        CSH;
        
        DELAY_CS;
        SET_ADDR_L(addr++);
        CSL;
        DELAY_TACC;
        *buf++ = PORT_DATA;
        CSH;
    }
    
#endif
}

static inline void JEDEC_WRITE_8(uint32_t addr, uint8_t b) {
    _START_C()

    //rom_jedec_clear();
    rom_send_command_8(0xA0);
    rom_write_8(addr, b);
    DELAY_BYTE_WRITE
}

#if 0 // MCP23s17 slowdown everything !
/**
 * http://ww1.microchip.com/downloads/en/DeviceDoc/20005022C.pdf
 *
 * @param in
 * @param addr
 * @param len
 */
void SST39xx_rom_write(uint8_t * in, uint32_t addr, uint8_t len) {
    uint8_t p = 0;
    uint8_t toggle_bit = 0;
    uint8_t * buf = in;

    rom_start_write();
    
#if 0

    for (p = 0; p < len; p++, addr++, buf++) {
        _START_C()
        rom_send_command_8(0xA0);

        rom_write_8(addr, *buf);

        DELAY_BYTE_WRITE;

        rom_start_read();
        WE_H
        CSH

    }
    
#else
    
    WE_H
    CSH
            
    for (p = 0; p < len; p+=8) {
        rom_send_command_8(0xA0);
        rom_write_8(addr++, *buf++);
        DELAY_BYTE_WRITE;
        WE_H
        CSH
        
        rom_send_command_8(0xA0);
        rom_write_8(addr++, *buf++);
        DELAY_BYTE_WRITE;
        WE_H
        CSH

        rom_send_command_8(0xA0);
        rom_write_8(addr++, *buf++);
        DELAY_BYTE_WRITE;
        WE_H
        CSH

        rom_send_command_8(0xA0);
        rom_write_8(addr++, *buf++);
        DELAY_BYTE_WRITE;
        WE_H
        CSH

        rom_send_command_8(0xA0);
        rom_write_8(addr++, *buf++);
        DELAY_BYTE_WRITE;
        WE_H
        CSH

        rom_send_command_8(0xA0);
        rom_write_8(addr++, *buf++);
        DELAY_BYTE_WRITE;
        WE_H
        CSH

        rom_send_command_8(0xA0);
        rom_write_8(addr++, *buf++);
        DELAY_BYTE_WRITE;
        WE_H
        CSH

        rom_send_command_8(0xA0);
        rom_write_8(addr++, *buf++);
        DELAY_BYTE_WRITE;
        WE_H
        CSH
    }
    
#endif
}
#else

/**
 * http://ww1.microchip.com/downloads/en/DeviceDoc/20005022C.pdf
 *
 * @param in
 * @param addr
 * @param len
 */
void SST39xx_rom_write(uint8_t * in, uint32_t addr, uint8_t len) {
    uint8_t p = 0;
    uint8_t toggle_bit = 0;
    uint8_t * buf = in;

    rom_start_write();
    
    WE_H
    CSH
    for (p = 0; p < len; p++, addr++, buf++) {
        //_START_C()
        rom_send_command_8(0xA0);

        rom_write_8(addr, *buf);

        DELAY_BYTE_WRITE;

        rom_start_read();
        WE_H
        CSH

    }
}

#endif

void SST39xx_rom_erase(uint8_t * in) {
    rom_start_write();

    _START_C()

    rom_send_command_8(0x80);
    rom_send_command_8(0x10);

    rom_start_read();
    WE_H
    CSH

    DELAY_1s();
#if 0
    Check_Toggle_Ready();
    _READ8(0, in[0]);
    _READ8(1, in[1]);
    _READ8(2, in[2]);
    _READ8(3, in[3]);
    _READ8(4, in[4]);
    _READ8(5, in[5]);
#endif
    
    
    MCP_Write(MCP_ADDR_HIGH, GPIOA, 0x00);
    MCP_Write(MCP_ADDR_HIGH, GPIOB, 0x00);
}

void rom_identify(uint8_t * in) {
    rom_start_write();

    _START_C()

    rom_send_command_8(0xF0);
    
    rom_send_command_8(0x90);
    DELAY_CMD_X

    rom_start_read();

    _READ8(0, in[0]);
    _READ8(1, in[1]);

    _START_C()

    rom_send_command_8(0xF0);
    DELAY_CMD_X

    rom_start_read();
    rom_read(&in[2], 0, 0xF);
    
    
    
    MCP_Write(MCP_ADDR_HIGH, GPIOA, 0xFF);
    MCP_Write(MCP_ADDR_HIGH, GPIOB, 0xFF);
}

