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
#include <pic18.h>
#include <pic18f45k50.h>
#include "system_config.h"
#include "rom.config.h"
#include "rom.h"

#define SECTOR_SIZE_4K             4096


void SET_ADDR_H(uint24_t addr) {    
    TRISB = 0x00;
    TRISD = 0x00;    
    
    LATD =  (addr & 0x00FF0000) >> 16;
    
    LATCbits.LC7 = 0; // 74hc574 OE
    LATCbits.LC6 = 1; // 74hc574 CP
    LATCbits.LC6 = 0; // 74hc574 CP
    
    LATB = (addr & 0x0000FF00) >> 8;
    
}

void SET_ADDR_L(uint8_t addr) {
    TRISA = 0x00;
    
    LATA = addr;
    //
    LATCbits.LC7 = 0; // 74hc574 OE
    LATCbits.LC6 = 1; // 74hc574 CP
    LATCbits.LC6 = 0; // 74hc574 CP    
}


void SET_ADDR(uint24_t addr) {
    TRISA = 0x00;
    TRISB = 0x00;
    TRISD = 0x00;  
    
    LATA = addr;    
    LATB = (addr & 0x0000FF00) >> 8;
    LATD = (addr & 0x00FF0000) >> 16;    
    
    LATCbits.LC7 = 0; // 74hc574 OE
    LATCbits.LC6 = 1; // 74hc574 CP
    LATCbits.LC6 = 0; // 74hc574 CP
}

void write_8_cmd(uint24_t addr, uint8_t b) {
    OE_H
    SET_ADDR(addr);
    
    LATA = b;
    
    // address and data already set !
    CE_L;
    WE_L;

    // Wait
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();

    WE_H;
    CE_H;
}

void write_16_cmd(uint24_t addr, uint8_t b) {
    OE_H
    SET_ADDR(addr);
    
    LATA = b;
    LATD = b;

    // address and data already set !
    CE_L;
    WE_L;

    // Wait
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();

    WE_H;
    CE_H;
}

static void PORT_INIT() {
    INTCON = 0;
    INTCON2 = 0;
    INTCON3 = 0;
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;
    LATD = 0x00;

    TRISA = 0x00;
    TRISB = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
    TRISCbits.RC6 = 0;
    TRISCbits.RC7 = 0;
    TRISCbits.RC0 = 0;
    TRISCbits.RC1 = 0;
    TRISCbits.RC2 = 0;

    // Disable analog
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    ANSELD = 0;
}


inline void rom_finish_write() {
    rom_start_read();
}

void rom_init() {
    OE_L
    WE_H
    CE_H
    OE_H

    PORT_INIT();
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

static __inline void write_8(uint24_t addr, uint8_t b) {
    TRISA = 0x00;
    OE_H
    LATA = b;
    PORTA = b;

    SET_ADDR(addr);

    // address and data already set !
    CE_L;
    WE_L;

    // Wait
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();

    WE_H;
    CE_H;
}

void write_16_data(uint24_t addr, uint8_t d, uint8_t a) {
    OE_H
    SET_ADDR(addr);
        
    LATA = a;
    LATD = d;

    // address and data already set !
    CE_L;
    WE_L;

    // Wait
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();

    WE_H;
    CE_H;
}


static int mx_toggle_wait() {
    uint8_t status1 = 0;
    uint8_t status2 = 0;
    TRISA = 0xFF;
    int max_try = 1000;

    while ((max_try--)>0) {
        _READ_TOGGLE(status1);
        _READ_TOGGLE(status2);

        if (((status1 ^ status2) & (1 << 6)) == 0) {
            TRISA = 0x00;
            return 0;
        }
       __delay_us(3);
    }

    return 0xFF;
}

static uint8_t mx_data_poll(uint8_t val) {
    // 200us * 5 => 1ms
    uint8_t max_try = 200;
    uint8_t data = 0;
    TRISA = 0xFF;

    while ((max_try--)>0) {
        CSL; 
        __nop();
        data = PORTA;
        CSH;

        if ((val & 0x80) == (data & 0x80)) {
            TRISA = 0x00;
            return 0;
        }
        __nop();
        __nop();
        __nop();
        __nop();
        __nop();
        __nop();
        __nop();
        __nop();
    }

    //error ...
    return 0xFF;
}

static inline uint8_t amd_toggle_wait_8() {
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
            write_8_cmd(0, 0xF0);
            return 0xFF;
        }
    }

    return 0xFF;
}
void amd_unlock_write_start() {
    TRISA = 0x00;
    // reset
    write_8_cmd(0, 0xF0);

    // amd unlock start
    write_8_cmd(AddrConv(0x555), 0xAA);
    write_8_cmd(AddrConv(0xAAA), 0x55);
    write_8_cmd(AddrConv(0x555), 0x20);
}

void amd_unlock_write_end() {
    TRISA = 0x00;
    // amd unlock end
    write_8_cmd(0, 0x90);
    write_8_cmd(0, 0x00);
    // reset
    write_8_cmd(0, 0xF0);
}
/*
uint8_t amd_unlock_rom_write_8_16(uint8_t * in, uint32_t addr, uint8_t _len) {
    uint8_t p = 0;
    uint8_t * buf = in;
    const uint8_t len = 0x40;

    for (p = len; p>0; p--, addr++, buf++) {
        write_8_cmd(0x10, 0xA0);
        write_8_cmd(addr, *buf);
        if (mx_data_poll(*buf) != 0) {
            // ERROR !
            return ROM_ERROR;
        }
    }

    return ROM_OK;
}
*/

uint8_t mx_rom_page_write_verify() {
    __delay_us(100);
    uint8_t status = 0;

    TRISA = 0xFF;

    do {
        _READ_TOGGLE(status);
    } while ((status & 0x80) != 0x80);

    return (status & 0x10) ? ROM_ERROR : ROM_OK;
}

uint8_t rom_page_write_8_16(uint8_t * in, uint32_t _addr, uint8_t _len) {
    uint32_t p = 0;
    uint8_t * buf = in;
    uint32_t len = 0x100;
    uint32_t addr = _addr;

    uint8_t haddr = (addr >> 6) & 0xFF;

    write_8(AddrConv(0x5555), 0xAA);
    write_8(AddrConv(0xAAAA), 0x55);
    write_8(AddrConv(0x5555), 0xA0);

    SET_ADDR_H(addr);

    for (p = 0; p < len; p++, addr++, buf++) {
        rom_write_8_l(addr, *buf);
        uint8_t spaddr = addr >> 6;
        if (haddr != spaddr) {
            SET_ADDR_H(addr);
            haddr = spaddr;
        }
    }

    __delay_us(200);

    uint8_t verify = mx_rom_page_write_verify();
    if (true || verify == ROM_OK) {
        // Reset ..
        write_8(AddrConv(0x5555), 0xAA);
        write_8(AddrConv(0xAAAA), 0x55);
        write_8(AddrConv(0x5555), 0x50);
    }

    //return verify;
    return ROM_OK;
}

/*
uint8_t rom_write_8_16(uint8_t * in, uint32_t addr, uint8_t _len) {
    return mx_rom_write_8_16(in, addr, 0x40);
    //return rom_page_write_8_16(in, addr, 0x40);
}
*/

uint8_t rom_custom(uint8_t data, uint32_t addr) {
    SET_ADDR_H(addr);
    SET_ADDR_L(addr);

    PORTA = data;

    return ROM_OK;
}



#define MAKE_FN_NAME(x, y) rom_##x##_##y
#define ROM_FUNC_NAME(name, suffix) MAKE_FN_NAME(name, suffix)
#define CMD_WRITE_FUNC_NAME(x) write_##x
#define CMD_WRITE CMD_WRITE_FUNC_NAME(ROM_SUFFIX)

// 8 BIT
#define ROM_SUFFIX      8
#define ROM_PREFIX      rom
#define SIZE_OF_DATA    8
#define SIZE_OF_CMD    8
#define ROM_IS_SNES     0
#include "rom.inl.h"

// Clean
#undef ROM_SUFFIX
#undef ROM_PREFIX
#undef SIZE_OF_DATA
#undef SIZE_OF_CMD
#undef ROM_IS_SNES

// 8 Bit with 16 bit cmd
#define ROM_SUFFIX      8_16
#define ROM_PREFIX      rom
#define SIZE_OF_DATA    8
#define SIZE_OF_CMD    16
#define ROM_IS_SNES     0
#include "rom.inl.h"

