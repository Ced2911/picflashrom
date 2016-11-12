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
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "rom.h"
#include "mcp23s17.h"
#include "system_config.h"

#define SECTOR_SIZE_4K             4096

#define MCP_DATA_ADDR   0
#define MCP_ADDR_HIGH   0

//#define SET_ADDR_H(addr)    {MCP_Write(MCP_ADDR_HIGH, GPIOA, addr>>6); MCP_Write(MCP_ADDR_HIGH, GPIOB, addr>>14);}
//#define SET_ADDR_H(addr)    
#define SET_ADDR_H(addr)    {MCP_Write16AB(MCP_ADDR_HIGH, GPIOA, addr>>6, addr>>14);}
//#define SET_ADDR_L(addr)    {LATB = (LATB & 3) | ((addr<<2)&0xFC); LATBbits.LB4 = 1;}
#define SET_ADDR_L(addr)    {LATB = (LATB & 3) | ((addr<<2)&0xFC); }

#define CSL {PORTC = PORTC & 0xFC;}
#define CSH {PORTC = PORTC | 0x03;}

#define CE_L_OE_H {PORTC = (PORTC & 0xFC) | 0x2 ;}
#define CE_H_OE_H {PORTC = PORTC | 0x03;}

#define CE_L    {LATCbits.LC0 = 0;}
#define CE_H    {LATCbits.LC0 = 1;}
#define OE_L    {LATCbits.LC1 = 0;}
#define OE_H    {LATCbits.LC1 = 1;}
#define WE_L    {LATCbits.LC2 = 0;}
#define WE_H    {LATCbits.LC2 = 1;}


#define CE  0
#define OE  1
#define WE  2

#define DELAY_P { __delay_us(1); }
#define DELAY_CMD_X { __delay_us(2); }
#define DELAY_TWP   { __delay_us(1); }
#define OUTB(x) { LATA = x;}

//#define DELAY_TACC  { __delay_us(2);} // OKAY
//#define DELAY_CS    { __delay_us(1);} // OKAY

#define DELAY_TACC  { __delay_us(2);} // OKAY
#define DELAY_CS    { __delay_us(1);} // OKAY
#define DELAY_CMD    { __delay_us(2);} // TEST
#define DELAY_ERASE {__delay_ms(10); } // TEST
#define DELAY_BYTE_WRITE { __delay_us(1);} // OKAY

#define MAX_EEPROM_READ    0x40

#define PORT_DATA PORTA

#define  AddrConv(X)   ((X<<1)+!(X&0x1))



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

#define _READ8LOW(a, x) \
{ \
    WE_H \
    CSH \
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

static void set_control(uint8_t ctrl) {
    LATC = (PORTC & 0xF8) | (ctrl & 0x7);
}

static void PORT_INIT() {
    INTCON = 0;
    INTCON2 = 0;
    INTCON3 = 0;
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
    TRISCbits.RC2 = 0;

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
    // PORT_INIT();
    //  return;

    SPI_Init();
    MCP_Init(MCP_ADDR_HIGH);

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

// Ok cmd

static __inline void rom_write_8_l(uint32_t addr, uint8_t b) {
    TRISA = 0x00;
    OE_H
    LATA = b;
    SET_ADDR_L(addr);
    
    // adress and data already set !
    CE_L;
    WE_L;
    
    __nop();
    __nop();
    
    WE_H;
    CE_H;
}

static __inline void rom_write_8(uint32_t addr, uint8_t b) {
    TRISA = 0x00;
    OE_H
    LATA = b;
    PORTA = b;
    SET_ADDR_H(addr);
    SET_ADDR_L(addr);

    // adress and data already set !
    CE_L;
    WE_L;
    
    __nop();    
    __nop();    
    
    WE_H;
    CE_H;
}

static void rom_send_command_8(uint8_t cmd) {
    rom_start_write();
    OE_H

    rom_write_8(0x5555, 0xAA);
    rom_write_8(0x2AAA, 0x55);
    rom_write_8(0x5555, cmd);
}

static void rom_send_command_8_16(uint8_t cmd) {
    rom_start_write();
    OE_H

    rom_write_8(0xAAAA, 0xAA);
    rom_write_8(0x5555, 0x55);
    rom_write_8(0xAAAA, cmd);
}

void rom_reset_status() {
    _START_C()
    rom_start_write();
    rom_write_8(0, 0xF0);
    rom_start_read();
}

uint8_t rom_read(uint8_t * out, uint32_t addr, uint8_t len) {
    uint8_t p = 0;
    uint8_t * buf = out;

    rom_reset_status();
    WE_H;
    CSH;
    SET_ADDR_H(addr);

    for (p = 0; p < len; p++, addr++, buf++) {
        SET_ADDR_L(addr);
        CSL;
        NOP();
        *buf = PORT_DATA;
        CSH;
        NOP();
    }


    return ROM_OK;
}

/**
 * http://ww1.microchip.com/downloads/en/DeviceDoc/20005022C.pdf
 *
 * @param in
 * @param addr
 * @param len
 */
uint8_t rom_write(uint8_t * in, uint32_t addr, uint8_t len) {
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


    return ROM_OK;
}

uint8_t rom_erase(uint8_t * in) {
    rom_start_write();

    _START_C()

    rom_send_command_8(0x80);
    rom_send_command_8(0x10);

    rom_start_read();
    WE_H
    CSH


    return ROM_OK;
}

uint8_t rom_identify(uint8_t * in) {
    rom_start_write();
    
    rom_send_command_8(0x90);

    DELAY_CMD_X

    rom_start_read();

    for (int i = 0; i < 8; i++)
        _READ8(i, in[i]);

    _START_C()

    rom_send_command_8(0xF0);
    DELAY_CMD_X

    rom_start_read();


    return ROM_OK;
}

static int amd_toggle_wait_8() {
    uint8_t status1 = 0;
    uint8_t status2 = 0;
    TRISA = 0xFF;

    while (1) {
        _READ_TOGGLE(status1);
        _READ_TOGGLE(status2);

        if (((status1 ^ status2) & (1 << 6)) == 0) {
            TRISA = 0x00;
            return 0;
        }

        if ((status1 & (1 << 5)) != 0) {
            _READ_TOGGLE(status1);
            _READ_TOGGLE(status2);

            if (((status1 ^ status2) & (1 << 6)) == 0) {
                TRISA = 0x00;
                return 0;
            }


            TRISA = 0x00;
            rom_write_8(0, 0xF0);
            return 0xFF;
        }
    }
}

static __inline void rom_write_8_test(uint32_t addr, uint8_t b) {
    TRISA = 0x00;
    LATA = b;
    OE_H;
    SET_ADDR_H(addr);
    SET_ADDR_L(addr);
    DELAY_CS;

    // adress and data already set !
    CE_L;
    WE_L;
    {
        __delay_us(10);
    }
    WE_H;
    CE_H;
    {
        __delay_us(10);
    }
}

static __inline void unlocked_rom_write_8(uint32_t addr, uint8_t b) {
    TRISA = 0x00;
    LATA = b;
    OE_H;
    SET_ADDR_L(addr);
    DELAY_CS;

    // adress and data already set !
    CE_L;
    WE_L;

    {
        __delay_us(2);
    }

    WE_H;
    CE_H;

    {
        __delay_us(10);
    }
}

uint8_t mx_rom_write_8_16(uint8_t * in, uint32_t addr, uint8_t _len) {
    uint8_t p = 0;
    uint8_t * buf = in;
    uint8_t len = 0x40;
    
    rom_reset();

    for (p = 0; p < len; p++, addr++, buf++) {
        rom_write_8(AddrConv(0x5555), 0xAA);
        rom_write_8(AddrConv(0xAAAA), 0x55);
        rom_write_8(AddrConv(0x5555), 0xA0);

        rom_write_8(addr, *buf);
    }

    return ROM_OK;
}

void amd_unlock_write_start() {
    // reset
    rom_write_8(0, 0xF0);

    // amd unlock start
    rom_write_8(AddrConv(0x555), 0xAA);
    rom_write_8(AddrConv(0xAAA), 0x55);
    rom_write_8(AddrConv(0x555), 0x20);
}

void amd_unlock_write_end() {
    // amd unlock end
    rom_write_8(0, 0x90);
    rom_write_8(0, 0x00);
    // reset
    rom_write_8(0, 0xF0);
}

uint8_t amd_unlock_rom_write_8_16(uint8_t * in, uint32_t addr, uint8_t _len) {
    uint8_t p = 0;
    uint8_t * buf = in;
    uint8_t len = 0x40;

    // spi is slow... call it only 1 time
    SET_ADDR_H(addr);

    for (p = 0; p < len; p++, addr++, buf++) {
        unlocked_rom_write_8(0x10, 0xA0);
        unlocked_rom_write_8(addr, *buf);
        if (amd_toggle_wait_8() != 0) {
            // ERROR !
            return ROM_ERROR;
        }
    }

    return ROM_OK;
}


uint8_t rom_reset() {    
    rom_start_write();
    rom_write_8(AddrConv(0x5555), 0xAA);
    rom_write_8(AddrConv(0xAAAA), 0x55);
    rom_write_8(AddrConv(0x5555), 0xF0);
}

uint8_t mx_rom_page_write_verify() {
    __delay_us(100);
    uint8_t status = 0;
        
    TRISA = 0xFF;
    
    do {
        _READ_TOGGLE(status);
    } while((status & 0x80)!=0x80);
        
    return (status & 0x10) ? ROM_ERROR:ROM_OK;
}

uint8_t rom_page_write_8_16(uint8_t * in, uint32_t _addr, uint8_t _len) {
    uint32_t p = 0;
    uint8_t * buf = in;
    uint32_t len = 0x100;
    uint32_t addr = _addr;
    
    uint8_t haddr = (addr>>6) & 0xFF;
    
    rom_write_8(AddrConv(0x5555), 0xAA);
    rom_write_8(AddrConv(0xAAAA), 0x55);
    rom_write_8(AddrConv(0x5555), 0xA0);
    
    MCP_Write16AB(MCP_ADDR_HIGH, GPIOA, addr>>6, addr>>14);

    for (p = 0; p < len; p++, addr++, buf++) {
        rom_write_8_l(addr, *buf);
        uint8_t spaddr = addr>>6;
        if (haddr != spaddr) {
            MCP_Write(MCP_ADDR_HIGH, GPIOA, spaddr);
            haddr = spaddr;
        }
    }
    
    __delay_us(200);
    
    uint8_t verify = mx_rom_page_write_verify();
    if (true ||verify == ROM_OK) {
        // Reset ..
        rom_write_8(AddrConv(0x5555), 0xAA);
        rom_write_8(AddrConv(0xAAAA), 0x55);
        rom_write_8(AddrConv(0x5555), 0x50);
    }
    
    //return verify;
    return ROM_OK;
}

uint8_t rom_write_8_16(uint8_t * in, uint32_t addr, uint8_t _len) {
    return mx_rom_write_8_16(in, addr, 0x40);
    //return rom_page_write_8_16(in, addr, 0x40);
}

uint8_t rom_erase_8_16(uint8_t * in) {
    rom_start_write();

    rom_write_8(AddrConv(0x5555), 0xAA);
    rom_write_8(AddrConv(0xAAAA), 0x55);
    rom_write_8(AddrConv(0x5555), 0x80);
    rom_write_8(AddrConv(0x5555), 0xAA);
    rom_write_8(AddrConv(0xAAAA), 0x55);
    rom_write_8(AddrConv(0x5555), 0x10);

    return ROM_OK;
}

uint8_t rom_identify_8_16(uint8_t * in) {
    rom_start_write();

    // ID
    rom_start_write();
    rom_write_8(AddrConv(0x5555), 0xAA);
    rom_write_8(AddrConv(0xAAAA), 0x55);
    rom_write_8(AddrConv(0x5555), 0x90);

    rom_start_read();

    SET_ADDR_H(0);

    _READ8LOW(0, in[0]);
    _READ8LOW(2, in[1]);
    _READ8LOW(6, in[2]);
    _READ8LOW(4, in[3]);

    return ROM_OK;
}

uint8_t rom_custom(uint8_t data, uint32_t addr) {
    SET_ADDR_H(addr);
    SET_ADDR_L(addr);

    PORTA = data;

    return ROM_OK;
}
