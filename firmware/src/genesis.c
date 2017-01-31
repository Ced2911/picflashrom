/*
 * File:   genesis.c
 * Author: cc
 *
 * Created on 20 janvier 2017, 17:08
 */

#include <xc.h>
#include <stdint.h>
#include "rom.h"
#include "rom.config.h"
#define _XTAL_FREQ 16000000


void genesis_sram_access(uint8_t l) {    
    TRISEbits.RE0 = 0;
    LATEbits.LE0 = 1;
       
    TRISA = 0x00;       
    LATAbits.LA0 = l;
    
    TRISEbits.RE0 = 0;
    LATEbits.LE0 = 0;
}


uint8_t genesis_sram_read(uint8_t * out, uint32_t addr, uint8_t len) {
    uint8_t p = 0;
    uint8_t * buf = out;
    
    CE_L;
    OE_H;
    WE_H;
    
    LATEbits.LE0 = 1;
    LATEbits.LE1 = 1;
    LATEbits.LE2 = 1;

    for (p = 0; p < 0x20; p++, addr++) {
        // Set low addr
        SET_ADDR(addr);
        // Read data
        TRISA = 0xFF;
        TRISD = 0xFF;
        OE_L;
        CE_H;
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        *buf++ = addr & 0xFF;
        *buf++ = PORTA;
        OE_H;
        CE_L;
    }
    
    LATEbits.LE0 = 0;
    return ROM_OK;
}


uint8_t genesis_sram_write(uint8_t * in, uint32_t addr, uint8_t len) {
    uint8_t p = 0;
    uint8_t * buf = in;
    
    OE_H;        
    CE_H;
    WE_H;
    
    LATEbits.LE2 = 1;
    LATEbits.LE1 = 1;    
    LATEbits.LE0 = 1;
    
    for (p = 0; p < 0x40; p++, addr++, buf++) {
       __delay_us(1);
        SET_ADDR(addr);
        //WE_L;
       
        CE_L;
        WE_L;
        LATEbits.LE2 = 0;
        LATEbits.LE1 = 0;
        LATEbits.LE0 = 0;
       
        TRISA = 0x00; 
        TRISD = 0x00;
        //LATA = *buf;
        //PORTA = *buf;
        LATA = *buf;
        
        CE_H;
        WE_H;
        LATEbits.LE2 = 1;
        LATEbits.LE1 = 1;    
        LATEbits.LE0 = 1;
    }
    
    return ROM_OK;
}
