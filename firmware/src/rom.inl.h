#ifndef MAKE_FN_NAME
#define MAKE_FN_NAME(x, y) rom_##x##_##y
#define ROM_FUNC_NAME(name, suffix) MAKE_FN_NAME(name, suffix)
#define ROM_SUFFIX      8
#define ROM_PREFIX      rom
#define SIZE_OF_DATA    8
#define SIZE_OF_CMD    16
#define ROM_IS_SNES     0    
#endif

#undef AddrConv
#if SIZE_OF_CMD == 16 && SIZE_OF_DATA == 8
#define  AddrConv(X)   ((X<<1)+!(X&0x1))
#else
#define  AddrConv(X)   (X)
#endif

uint8_t ROM_FUNC_NAME(read, ROM_SUFFIX)(uint8_t * out, uint32_t addr, uint8_t _len) {
    uint8_t p = 0;
    uint8_t * buf = out;

#if ROM_IS_SNES
    // /RESET Low
    TRISEbits.RE2 = 0;
#endif
    TRISEbits.RE1 = 1;
    WE_H;
    CSH;

    for (p = 0; p < 0x40; p++, addr++, buf) {
        // Set low addr
        SET_ADDR(addr);
        CSL;
        NOP();
        // Read data
        TRISA = 0xFF;
        *buf++ = PORTA;
#if SIZE_OF_DATA == 16
        TRISD = 0xFF;
        *buf++ = PORTD;
#endif
        CSH;
    }


    return ROM_OK;
}

uint8_t ROM_FUNC_NAME(identify, ROM_SUFFIX)(uint8_t * in) {
    // Start write
    TRISA = 0x00;
    TRISD = 0x00;

    // Send command
#if SIZE_OF_DATA == 8
    write_8_cmd(AddrConv(0x5555), 0xAA);
    write_8_cmd(AddrConv(0xAAAA), 0x55);
    write_8_cmd(AddrConv(0x5555), 0x90);
#else
    write_16_cmd(0x5555, 0xAA);
    write_16_cmd(0xAAAA, 0x55);
    write_16_cmd(0x5555, 0x90);
#endif

    SET_ADDR(0);
        
    // Start read
    TRISA = 0xFF;
    TRISD = 0xFF;

    // Read id
    ROM_READ8(AddrConv(0), in[0]);
    ROM_READ8(AddrConv(1), in[1]);
    ROM_READ8(AddrConv(2), in[2]);
    ROM_READ8(AddrConv(3), in[3]);

    return ROM_OK;
}

uint8_t ROM_FUNC_NAME(reset, ROM_SUFFIX)() {
#if SIZE_OF_DATA == 8
    // Start write
    TRISA = 0x00;

    write_8_cmd(AddrConv(0x5555), 0xAA);
    write_8_cmd(AddrConv(0xAAAA), 0x55);
    write_8_cmd(AddrConv(0x5555), 0xF0);
#else
    // Start write
    TRISA = 0x00;
    TRISD = 0x00;

    write_16(AddrConv(0x5555), 0xAAAA);
    write_16(AddrConv(0xAAAA), 0x5555);
    write_16(AddrConv(0x5555), 0xF0F0);
#endif
    return ROM_OK;
}

uint8_t ROM_FUNC_NAME(erase, ROM_SUFFIX)(uint8_t * in) {

#if SIZE_OF_DATA == 8
    // Start write
    TRISA = 0x00;

    write_8_cmd(AddrConv(0x5555), 0xAA);
    write_8_cmd(AddrConv(0xAAAA), 0x55);
    write_8_cmd(AddrConv(0x5555), 0x80);
    write_8_cmd(AddrConv(0x5555), 0xAA);
    write_8_cmd(AddrConv(0xAAAA), 0x55);
    write_8_cmd(AddrConv(0x5555), 0x10);
#else
    // Start write
    TRISA = 0x00;
    TRISD = 0x00;

    write_16(AddrConv(0x5555), 0xAAAA);
    write_16(AddrConv(0xAAAA), 0x5555);
    write_16(AddrConv(0x5555), 0xF0F0);
    write_16(AddrConv(0x5555), 0xAAAA);
    write_16(AddrConv(0xAAAA), 0x5555);
    write_16(AddrConv(0x5555), 0x1010);
#endif

    return ROM_OK;
}

/**
 * http://ww1.microchip.com/downloads/en/DeviceDoc/20005022C.pdf
 * 
 * @param in
 * @param addr
 * @param _len
 * @return 
 */
uint8_t ROM_FUNC_NAME(write, ROM_SUFFIX)(uint8_t * in, uint32_t addr, uint8_t _len) {
    uint8_t p = 0;
    uint8_t * buf = in;

    WE_H;
    
    for (p = 0; p < 0x40; p++, addr++, buf++) {
        // Start write
        TRISA = 0x00;

        write_8_cmd(AddrConv(0x5555), 0xAA);
        write_8_cmd(AddrConv(0xAAAA), 0x55);
        write_8_cmd(AddrConv(0x5555), 0xA0);

        write_8_cmd(addr, *buf);
        
        // Wait
        if (mx_data_poll(*buf) != 0) {
            return ROM_ERROR;
        }
    }

    return ROM_OK;
}


// End macro template
#undef AddrConv