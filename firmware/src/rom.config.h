#ifndef ROMCFG_H
#define ROMCFG_H

#if 0
#define CSL {LATC = PORTC & 0xF9;}
#define CSH {LATC = PORTC | 0x06;}

#define CE_L_OE_H {LATC = (PORTC & 0xFC) | 0x2 ;}
#define CE_H_OE_H {LATC = PORTC | 0x03;}

#define WE_L    {LATCbits.LC0 = 0;}
#define WE_H    {LATCbits.LC0 = 1;}

#define CE_L    {LATCbits.LC1 = 0;}
#define CE_H    {LATCbits.LC1 = 1;}

#define OE_L    {LATCbits.LC2 = 0;}
#define OE_H    {LATCbits.LC2 = 1;}

#define CE  0
#define OE  1
#define WE  2

#else 
#if 0
#define CSL {LATC = PORTC & 0xF9;}
#define CSH {LATC = PORTC | 0x06;}
#else
#define CSL {LATC &= 0xF9;}
#define CSH {LATC |= 0x06;}
#endif

#define CE_L_OE_H {LATC = (PORTC & 0xFC) | 0x2 ;}
#define CE_H_OE_H {LATC = PORTC | 0x03;}

#define WE_L    {LATCbits.LC0 = 0;}
#define WE_H    {LATCbits.LC0 = 1;}

#define CE_L    {LATCbits.LC2 = 0;}
#define CE_H    {LATCbits.LC2 = 1;}

#define OE_L    {LATCbits.LC1 = 0;}
#define OE_H    {LATCbits.LC1 = 1;}

#define CE  0
#define OE  1
#define WE  2
#endif

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


#define ROM_READ8(a, x) \
{ \
    CSH \
    SET_ADDR(a);  \
    CSL; \
    TRISA = 0xFF; \
    x = PORTA;\
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

#define _READ16(a, x, y) \
{ \
    WE_H \
    CSH \
    SET_ADDR_16(a);  \
    CSL; \
    x = PORTA;\
    y = PORTD;\
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


void SET_ADDR_H(uint24_t addr);
void SET_ADDR_L(uint8_t addr);
void SET_ADDR(uint24_t addr);
void write_8_cmd(uint24_t addr, uint8_t b);
void write_16_cmd(uint24_t addr, uint8_t b);
void write_16_data(uint24_t addr, uint8_t d, uint8_t a);

#define GEN_READ16(a, x, y) \
{ \
    CSH \
    SET_ADDR(a);  \
    CSL; \
    TRISA = 0xFF; \
    TRISD = 0xFF; \
    x = PORTD;\
    y = PORTA;\
    CSH; \
}

#define GEN_READ8(a, x) \
{ \
    CSH \
    SET_ADDR(a);  \
    CSL; \
    TRISA = 0xFF; \
    x = PORTA;\
    CSH; \
}

#endif ROMCFG_H