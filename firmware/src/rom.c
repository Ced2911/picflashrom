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
#include "system_config.h"
#include "rom.config.h"
#include "rom.h"

#define SECTOR_SIZE_4K             4096

void SET_ADDR_H(uint32_t addr) {
    /*
    TRISA = 0x00;

    LATD = (addr & 0x0000FF00) >> 8;
    LATA = (addr & 0x00FF0000) >> 16;

    LATCbits.LC7 = 0; // 74hc574 OE
    LATCbits.LC6 = 1; // 74hc574 CP
    LATCbits.LC6 = 0; // 74hc574 CP
    
    */
    
    TRISB = 0x00;
    TRISD = 0x00;    
    
    LATD =  (addr & 0x00FF0000) >> 16;
    
    LATCbits.LC7 = 0; // 74hc574 OE
    LATCbits.LC6 = 1; // 74hc574 CP
    LATCbits.LC6 = 0; // 74hc574 CP
    
    LATB = (addr & 0x0000FF00) >> 8;
    
}

void SET_ADDR_L(uint8_t addr) {
    //LATB = addr;
    uint8_t tris = TRISA;
    TRISA = 0x00;
    
    LATA = addr;
    //
    LATCbits.LC7 = 0; // 74hc574 OE
    LATCbits.LC6 = 1; // 74hc574 CP
    LATCbits.LC6 = 0; // 74hc574 CP
    
    // restore
    TRISA = tris;
    
}


void SET_ADDR_16(uint32_t addr) {
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

void SET_ADDR(uint32_t addr) {
    //SET_ADDR_H(addr);
    //SET_ADDR_L(addr);
    
    SET_ADDR_16(addr);
}

static void PORT_INIT() {
    INTCON = 0;
    INTCON2 = 0;
    INTCON3 = 0;
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;
    LATD = 0x00;

    // set as portA as input
    TRISA = 0xFF;
    // set addr as output
    TRISB = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;

    // set port addr low as otuput
    TRISCbits.RC6 = 0;
    TRISCbits.RC7 = 0;
    TRISCbits.RC0 = 0;
    TRISCbits.RC1 = 0;
    TRISCbits.RC2 = 0;

    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    ANSELD = 0;

    PORTA = 0;
    PORTB = 0;


    TRISEbits.RE2 = 0;
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

static __inline void write_8(uint32_t addr, uint8_t b) {
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

static __inline void write_16(uint32_t addr, uint16_t b) {
    OE_H
    SET_ADDR_16(addr);
    
    TRISA = 0x00;
    TRISD = 0x00;
    
    LATA = b & 0xFF;
    PORTA = b & 0xFF;
    LATD = b >> 8;
    PORTD = b >> 8;

    // adress and data already set !
    CE_L;
    WE_L;

    __nop();
    __nop();

    WE_H;
    CE_H;
}

static __inline void gen_write_16_cmd(uint32_t addr, uint8_t b) {
    OE_H
    SET_ADDR_16(addr);
    
    TRISEbits.RE2 = 0;
    TRISEbits.RE1 = 0;
    
    LATA = b;
    LATD = b;

    // adress and data already set !
    CE_L;
    WE_L;    
    LATEbits.LE2 = 0;
    LATEbits.LE1 = 0;

    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();

    WE_H;
    CE_H; 
    LATEbits.LE2 = 1;
    LATEbits.LE1 = 1;
}

static __inline void gen_write_16_data(uint32_t addr, uint8_t d, uint8_t a) {
    OE_H
    SET_ADDR_16(addr);
    
    TRISEbits.RE2 = 0;
    TRISEbits.RE1 = 0;
    
    PORTA = a;
    PORTD = d;
    LATA = a;
    LATD = d;

    // adress and data already set !
    CE_L;
    WE_L;    
    LATEbits.LE2 = 0;
    LATEbits.LE1 = 0;

    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();

    WE_H;
    CE_H; 
    LATEbits.LE2 = 1;
    LATEbits.LE1 = 1;
}
uint8_t snes_sram_write(uint8_t * in, uint32_t addr, uint8_t len) {
    uint8_t p = 0;
    uint8_t * buf = in;

    // Set Read Mode
    WE_H;
    CE_H; // RD
    OE_H;// CART-ROMSEL
    TRISEbits.RE2 = 0;
    LATEbits.LE2 = 1;
    SET_ADDR_H(addr);

    for (p = 0; p < len; p++, addr++, buf++) {
        SET_ADDR_L(addr);
       __delay_us(1);
        WE_L;
       __delay_us(1);
        TRISA = 0x00;        
        LATA = *buf;
        PORTA = *buf;
        __delay_us(1);
         WE_H;
         __nop();
    }
            
    return ROM_OK;
}


uint8_t snes_sram_read(uint8_t * out, uint32_t addr, uint8_t len) {
    uint8_t p = 0;
    uint8_t * buf = out;

    // Set Read Mode
    WE_H;
    CE_L; // RD
    OE_H;// CART-ROMSEL
    TRISEbits.RE2 = 0;
    LATEbits.LE2 = 1;
    SET_ADDR_H(addr);

    for (p = 0; p < len; p++, addr++, buf++) {
        SET_ADDR_L(addr);       
       __delay_us(10);
        TRISA = 0xFF;
        *buf = PORT_DATA;
         __nop();
    }
            
    return ROM_OK;
}

uint8_t snes_rom_read(uint8_t * out, uint32_t addr, uint8_t len) {
    uint8_t p = 0;
    uint8_t * buf = out;
    
    // /RESET LOW
    TRISEbits.RE2 = 0;

    WE_H;
    CSH;
    SET_ADDR_H(addr);

    for (p = 0; p < len; p++, addr++, buf++) {
        SET_ADDR_L(addr);
        CSL;
        TRISA = 0xFF;
        *buf = PORT_DATA;
        CSH;
        NOP();
    }


    return ROM_OK;
}


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
    
    WE_H;

    LATEbits.LE0 = 1;
    for (p = 0; p < 0x20; p++, addr++) {
        // Set low addr
        SET_ADDR_16(addr);
        CSL;
        NOP();
        // Read data
        TRISA = 0xFF;
        TRISD = 0xFF;
        *buf++ = PORTA;
        *buf++ = PORTA;
        CSH;
    }
    
    
    LATEbits.LE0 = 0;
    return ROM_OK;
}


uint8_t genesis_sram_write(uint8_t * in, uint32_t addr, uint8_t len) {
    uint8_t p = 0;
    uint8_t * buf = in;
        
    CE_H; // RD
    OE_H;// CART-ROMSEL
    
    WE_H;
    LATEbits.LE2 = 1;
    LATEbits.LE1 = 1;
    
    LATEbits.LE0 = 1;
    for (p = 0; p < len; p++, addr++, buf++) {
        SET_ADDR(addr);
       __delay_us(1);
        //WE_L;
       
        CE_L;
        LATEbits.LE2 = 0;
        LATEbits.LE1 = 0;
        WE_L;
       
       __delay_us(1);
        TRISA = 0x00; 
        TRISD = 0x00;
        //LATA = *buf;
        //PORTA = *buf;
        LATA = 0x29;
        LATD = 0x29;
        __delay_us(1);
        
        CE_H;
        WE_H;
        LATEbits.LE2 = 1;
        LATEbits.LE1 = 1;
        
        __nop();
    }
    
    LATEbits.LE0 = 0;
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
            write_8(0, 0xF0);
            return 0xFF;
        }
    }

    return 0xFF;
}

uint8_t mx_rom_write_8_16(uint8_t * in, uint32_t addr, uint8_t _len) {
    uint8_t p = 0;
    uint8_t * buf = in;
    uint8_t len = 0x40;

    rom_reset_8_16();

    for (p = 0; p < len; p++, addr++, buf++) {
        write_8(AddrConv(0x5555), 0xAA);
        write_8(AddrConv(0xAAAA), 0x55);
        write_8(AddrConv(0x5555), 0xA0);

        write_8(addr, *buf);
    }

    return ROM_OK;
}

void amd_unlock_write_start() {
    // reset
    write_8(0, 0xF0);

    // amd unlock start
    write_8(AddrConv(0x555), 0xAA);
    write_8(AddrConv(0xAAA), 0x55);
    write_8(AddrConv(0x555), 0x20);
}

void amd_unlock_write_end() {
    // amd unlock end
    write_8(0, 0x90);
    write_8(0, 0x00);
    // reset
    write_8(0, 0xF0);
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


// Clean
#undef ROM_SUFFIX
#undef ROM_PREFIX
#undef SIZE_OF_DATA
#undef SIZE_OF_CMD
#undef ROM_IS_SNES

// 16 Bit with 16 bit cmd
#define ROM_SUFFIX      16
#define ROM_PREFIX      rom
#define SIZE_OF_DATA    16
#define SIZE_OF_CMD    16
#define ROM_IS_SNES     0
//#include "rom.inl.h"

#define GEN_READ16(a, x, y) \
{ \
    CSH \
    SET_ADDR_16(a);  \
    CSL; \
    TRISA = 0xFF; \
    TRISD = 0xFF; \
    x = PORTD;\
    y = PORTA;\
    CSH; \
}
#define  AddrConv(X)   ((X<<1)+!(X&0x1))
uint8_t genesis_rom_identify(uint8_t * in) {    
    TRISEbits.RE2 = 0;
    TRISEbits.RE1 = 0;
    
    LATEbits.LE2 = 1;
    LATEbits.LE1 = 1;
    
    // Start write
    TRISA = 0x00;
    TRISD = 0x00;

    // Send command
    gen_write_16_cmd(0x5555, 0xAA);
    gen_write_16_cmd(0xAAAA, 0x55);
    gen_write_16_cmd(0x5555, 0x90);

    SET_ADDR_16(0);
        
    // Start read
    TRISA = 0xFF;
    TRISD = 0xFF;

    // Read id
    GEN_READ16(0, in[0], in[1]);
    GEN_READ16(1, in[2], in[3]);
    GEN_READ16(2, in[4], in[5]);
    GEN_READ16(3, in[6], in[7]);
 
    return ROM_OK;
}

uint8_t genesis_rom_erase(uint8_t * in) {    
    TRISEbits.RE2 = 0;
    TRISEbits.RE1 = 0;
    
    LATEbits.LE2 = 1;
    LATEbits.LE1 = 1;
    
    // Start write
    TRISA = 0x00;
    TRISD = 0x00;

    // Send command
    gen_write_16_cmd(0x5555, 0xAA);
    gen_write_16_cmd(0xAAAA, 0x55);
    gen_write_16_cmd(0x5555, 0x80);
    gen_write_16_cmd(0x5555, 0xAA);
    gen_write_16_cmd(0xAAAA, 0x55);
    gen_write_16_cmd(0x5555, 0x10);
    
    // Poll
    TRISA = 0xFF;
    __delay_us(30);
    
    uint8_t data = 0;
    int max_try = 200;

    while ((max_try--)>0) {
        _READ_TOGGLE(data);

        if (data == 0xFF) {
            return ROM_OK;
        }
        
       
       __delay_us(3);
    }
 
    return ROM_ERROR;
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
    uint8_t data = 0;
    TRISA = 0xFF;
    uint8_t max_try = 0xFE;

    while ((max_try--)>0) {
        _READ_TOGGLE(data);

        if ((val & 0x80) == (data & 0x80)) {
            return 0;
        }
        
       __delay_us(5);
    }

    //error ...
    return 0xFF;
}

uint8_t genesis_rom_write(uint8_t * out, uint32_t addr, uint8_t _len) {
    uint8_t p = 0;
    uint8_t * buf = out;
    
    TRISEbits.RE2 = 0;
    TRISEbits.RE1 = 0;
    
    LATEbits.LE2 = 1;
    LATEbits.LE1 = 1;
    
    WE_H;
    
    TRISA = 0x00;
    TRISD = 0x00;

    for (p = 0; p < 0x20; p++, addr++, buf+=2) {
        if ( buf[0] == 0xFF && buf[1] == 0xFF) {
            continue;
        }
        gen_write_16_cmd(0x5555, 0xAA);
        gen_write_16_cmd(0xAAAA, 0x55);
        gen_write_16_cmd(0x5555, 0xA0);
        gen_write_16_data(addr, buf[0], buf[1]);
       
        if (mx_data_poll(buf[1]) != 0) {
            return ROM_ERROR;
        }
    }
    
    return ROM_OK;
}


uint8_t genesis_rom_reset_16() {
    TRISA = 0x00;

    gen_write_16_cmd((0x5555), 0xAA);
    gen_write_16_cmd((0xAAAA), 0x55);
    gen_write_16_cmd((0x5555), 0xF0);
    
    return ROM_OK;
}

uint8_t rom_read_16(uint8_t * out, uint32_t addr, uint8_t _len) {
    uint8_t p = 0;
    uint8_t * buf = out;
    
    WE_H;

    for (p = 0; p < 0x20; p++, addr++) {
        // Set low addr
        SET_ADDR_16(addr);
        // Read data
        TRISA = 0xFF;
        TRISD = 0xFF;
        CSL;
        NOP();
        *buf++ = PORTD;
        *buf++ = PORTA;
        NOP();
        CSH;
    }
    
    return ROM_OK;
}


uint8_t rom_reset_16() {
    TRISA = 0x00;

    write_16((0x5555), 0xAAAA);
    write_16((0xAAAA), 0x5555);
    write_16((0x5555), 0xF0F0);
    
    return ROM_OK;
}