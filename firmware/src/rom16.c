/*
 * File:   rom16.c
 * Author: cc
 *
 * Created on 20 janvier 2017, 17:17
 */

#include <xc.h>
#include <stdint.h>
#include "rom.h"
#include "rom.config.h"

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

uint8_t rom_identify_16(uint8_t * in) {    
    // Start write
    TRISA = 0x00;
    TRISD = 0x00;

    // Send command
    write_16_cmd(0x5555, 0xAA);
    write_16_cmd(0xAAAA, 0x55);
    write_16_cmd(0x5555, 0x90);

    SET_ADDR(0);
        
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


uint8_t rom_erase_16(uint8_t * in) {        
    // Start write
    TRISA = 0x00;
    TRISD = 0x00;

    // Send command
    write_16_cmd(0x5555, 0xAA);
    write_16_cmd(0xAAAA, 0x55);
    write_16_cmd(0x5555, 0x80);
    write_16_cmd(0x5555, 0xAA);
    write_16_cmd(0xAAAA, 0x55);
    write_16_cmd(0x5555, 0x10);
    
    // Poll
    TRISA = 0xFF;
    //__delay_us(30);
    
    uint8_t data = 0;
    int max_try = 200;

    while ((max_try--)>0) {
        _READ_TOGGLE(data);

        if (data == 0xFF) {
            return ROM_OK;
        }
        
       
       //__delay_us(3);
    }
 
    return ROM_ERROR;
}


uint8_t rom_write_16(uint8_t * out, uint32_t addr, uint8_t _len) {
    uint8_t p = 0;
    uint8_t * buf = out;
    
    WE_H;

    for (p = 0; p < 0x20; p++, addr++, buf+=2) {    
        TRISA = 0x00;
        TRISD = 0x00;
        
        // Skip empty packet
        if ( buf[0] == 0xFF && buf[1] == 0xFF) {
            continue;
        }
        // Write command
        write_16_cmd(0x5555, 0xAA);
        write_16_cmd(0xAAAA, 0x55);
        write_16_cmd(0x5555, 0xA0);
        
        // Write data
        write_16_data(addr, buf[0], buf[1]);
       
        // Wait
        if (mx_data_poll(buf[1]) != 0) {
            return ROM_ERROR;
        }
    }
    
    return ROM_OK;
}


uint8_t rom_read_16(uint8_t * out, uint32_t addr, uint8_t _len) {
    uint8_t p = 0;
    uint8_t * buf = out;
    
    WE_H;
    TRISA = 0x00;

    for (p = 0; p < 0x20; p++, addr++) {
        SET_ADDR(addr);
        // Read data
        CSL;
        TRISA = 0xFF;
        TRISD = 0xFF;
        *buf++ = PORTD;
        *buf++ = PORTA;
        CSH;
    }
    
    return ROM_OK;
}


uint8_t rom_reset_16() {
    TRISA = 0x00;

    write_16_cmd((0x5555), 0xAA);
    write_16_cmd((0xAAAA), 0x55);
    write_16_cmd((0x5555), 0xF0);
    
    return ROM_OK;
}
