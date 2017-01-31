/*
 * File:   snes.c
 * Author: cc
 *
 * Created on 20 janvier 2017, 17:07
 * 
 * http://www.gatchan.net/uploads/Consoles/SNES/Flashcard/SNES_MemMap.txt
 */

#include <xc.h>
#include <stdint.h>
#include "rom.h"
#include "rom.config.h"

#define _XTAL_FREQ 16000000

#define nCART   LATCbits.LC1
#define nRD     LATCbits.LC2
#define nWR     LATCbits.LC0
#define nRESET  LATEbits.LE1

#define  LOROM_ADDR(addr)   ((addr & 0xFFFF) | ((addr & 0xFF0000)<<1))



static inline void _SET_ADDR(uint24_t addr) {
    LATA = addr;    
    LATB = (addr & 0x0000FF00) >> 8;
    LATD = (addr & 0x00FF0000) >> 16;    
    
    LATCbits.LC7 = 0; // 74hc574 OE
    LATCbits.LC6 = 1; // 74hc574 CP
    LATCbits.LC6 = 0; // 74hc574 CP
}

uint8_t snes_sram_write(uint8_t * in, uint32_t taddr, uint8_t len) {
    uint8_t p = 0;
    uint8_t * buf = in; 
    
    // SNES RESET HIGH
    nRESET = 1;
    nWR = 1;
    nRD = 1;
    nCART = 1; 

    TRISA = 0x00;
    
    for (p = 0x40; p > 0; p--) {
        _SET_ADDR(taddr++);        
        LATA = *buf++;        
        nWR = 0;
        
        __nop();
        __nop();
        __nop();

        nWR = 1;
    }
    nCART = 0;
            
    return ROM_OK;
}


uint8_t snes_sram_read(uint8_t * out, uint32_t addr, uint8_t len) {
    uint8_t p = 0;
    uint8_t * buf = out; 
    
    // SNES RESET HIGH
    nRESET = 1;
    nWR = 1;
    nRD = 1;
    nCART = 1;    

    for (p = 0x40; p >0; p--) {
        TRISA = 0x00;
        _SET_ADDR(addr++);
        nRD = 0;
        TRISA = 0xFF;
        *buf++ = PORTA;
        nRD = 1;
    }
            
    return ROM_OK;
}

uint8_t snes_lorom_identify_8(uint8_t * in) {    
    // Start write
    TRISA = 0x00;
    TRISD = 0x00;

    // Send command
    write_8_cmd(LOROM_ADDR(0x5555), 0xAA);
    write_8_cmd(LOROM_ADDR(0xAAAA), 0x55);
    write_8_cmd(LOROM_ADDR(0x5555), 0x90);

    SET_ADDR(0);
        
    // Start read
    TRISA = 0xFF;

    // Read id
    GEN_READ8(0, in[0]);
    GEN_READ8(1, in[1]);
    GEN_READ8(2, in[2]);
    GEN_READ8(3, in[3]);
 
    return ROM_OK;
}

uint8_t snes_lorom_identify_8_16(uint8_t * in) {    
    // Start write
    TRISA = 0x00;
    TRISD = 0x00;

    // Send command
    write_8_cmd(LOROM_ADDR(AddrConv(0x5555)), 0xAA);
    write_8_cmd(LOROM_ADDR(AddrConv(0xAAAA)), 0x55);
    write_8_cmd(LOROM_ADDR(AddrConv(0x5555)), 0x90);

    SET_ADDR(0);
        
    // Start read
    TRISA = 0xFF;

    // Read id
    GEN_READ8(AddrConv(0), in[0]);
    GEN_READ8(AddrConv(1), in[1]);
    GEN_READ8(AddrConv(2), in[2]);
    GEN_READ8(AddrConv(3), in[3]);
 
    return ROM_OK;
}


void snes_write_8_cmd(uint24_t addr, uint8_t b) {
    OE_H
    _SET_ADDR(addr);
    
    LATA = b;
    
    // address and data already set !
    //nRD = 0;
    nCART = 0;
    WE_L;

    // Wait
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();

    WE_H;
    nCART = 1;
   // nRD = 1;
}

uint8_t snes_hirom_identify_8_16(uint8_t * in) {    
    // Start write
    TRISA = 0x00;
    TRISD = 0x00;
    
    // SNES RESET HIGH
    nRESET = 1;
    nWR = 1;
    nRD = 1;
    nCART = 1;   

    // Send command
    snes_write_8_cmd(AddrConv(0x5555), 0xAA);
    snes_write_8_cmd(AddrConv(0xAAAA), 0x55);
    snes_write_8_cmd(AddrConv(0x5555), 0x90);

    _SET_ADDR(0);
        
    // Start read
    TRISA = 0xFF;

    // Read id
    GEN_READ8(AddrConv(0), in[0]);
    GEN_READ8(AddrConv(1), in[1]);
    GEN_READ8(AddrConv(2), in[2]);
    GEN_READ8(AddrConv(3), in[3]);
 
    return ROM_OK;
}

// HIROM OK - LOROM FAIL
/** see mad1 mapping */
uint8_t snes_read_rom(uint8_t * out, uint32_t addr, uint8_t _len) {
    uint8_t p = 0;
    uint8_t * buf = out;

    // SNES RESET HIGH
    nRESET = 1;
    nWR = 1;
    nRD = 1;
    nCART = 1;   

    for (p = 0x10; p > 0x0; p--) {
        TRISA = 0x00;
        
        // Set low addr
        _SET_ADDR(addr++);
        nCART = 0;
        __nop();
        
        // Read data
        TRISA = 0xFF;
        *buf++ = PORTA;
        
        nCART = 1;
        
        TRISA = 0x00;
        
        // Set low addr
        _SET_ADDR(addr++);
        nCART = 0;
        __nop();
        
        // Read data
        TRISA = 0xFF;
        *buf++ = PORTA;
        
        nCART = 1;
        
        TRISA = 0x00;
        
        // Set low addr
        _SET_ADDR(addr++);
        nCART = 0;
        __nop();
        
        // Read data
        TRISA = 0xFF;
        *buf++ = PORTA;
        
        nCART = 1;
        
        TRISA = 0x00;
        
        // Set low addr
        _SET_ADDR(addr++);
        nCART = 0;
        __nop();
        
        // Read data
        TRISA = 0xFF;
        *buf++ = PORTA;
        
        nCART = 1;
    }
    
    return ROM_OK;
}


