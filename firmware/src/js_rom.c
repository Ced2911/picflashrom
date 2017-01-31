/*
 * File:   js_rom.c
 * Author: cc
 *
 * Created on 18 janvier 2017, 14:50
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

const uint8_t cmd5555_0 = AddrConv(0x5555);
const uint8_t cmd5555_1 = (AddrConv(0x5555) & 0x0000FF00) >> 8;
const uint8_t cmdAAAA_0 = AddrConv(0xAAAA);
const uint8_t cmdAAAA_1 = (AddrConv(0xAAAA) & 0x0000FF00) >> 8;


uint8_t js_rom_read_8(uint8_t * out, uint32_t addr, uint8_t _len) {
	uint8_t p = 0;                                                                   
	uint8_t * buf = out;
	
	// Cache some vars
	uint8_t addr0 = addr;
	uint8_t addr8 = (addr & 0x0000FF00) >> 8;
	uint8_t addr16 = (addr & 0x00FF0000) >> 16;
	
	// Apply high addr
	LATB = addr8;
    LATD = addr16;    
	
	// !WE high                                         							
	WE_H;
	LATC |= 0x06; // CE / OE High  
	
	// Unrolled loop
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	// Read block [object Object]
	// Set addr                                        
	TRISA = 0x00;
	LATA = addr0++; // Set addr low
	// Toggle 74hc573 Clk
	LATCbits.LC6 = 1;
	LATCbits.LC6 = 0;	
	LATC &= 0xF9; // CE / OE low
	
	// Read data                                                                       
	__nop();                                                                 
	TRISA=0xFF;                              							
	*buf++ = PORTA; 
		
	LATC |= 0x06; // CE / OE High	
	
	
	return ROM_OK;                                                                   
}

uint8_t js_rom_write_8(uint8_t * in, uint32_t addr, uint8_t _len) {
	uint8_t p = 0;
	uint8_t * buf = in;	
	
	/** data polling vars **/
    uint8_t data = 0;
	uint8_t val = 0;

	/** cache some vars **/
	uint8_t addr0 = addr;
	uint8_t addr8 = (addr & 0x0000FF00) >> 8;
	uint8_t addr16 = (addr & 0x00FF0000) >> 16;

	WE_H;

	LATCbits.LC1 = 1; // OE H


	/** (Allmost) Unrolled loop **/
	for(int loop = 4; loop > 0; loop--) {

	/** Start write **/
	TRISA = 0x00;
	
	/** Write unlock command **/
	// Write command 0xAA	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xAA;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xAA 
	
	
	// Write command 0x55	         
	// Set addr                         
	LATB = cmdAAAA_1; 					 
	LATA = cmdAAAA_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0x55;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0x55 
	
	
	// Write command 0xA0	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xA0;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xA0 
	
	

	/** Write data **/
	// Set addr                         
	LATB = addr8;
	LATD = addr16; 
	LATA = addr0++;    
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set data                          
	LATA = *buf;                    
	val = (*buf & 0x80);			
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write data 
	
	

	/** Wait for completion or error **/
    TRISA = 0xFF;

	// poll for completion
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_80;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_80;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_80;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_80;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_80;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_80;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_80;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_80;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	
	// max attempt => write error
	goto label_error;

label_js_rom_write_80:
	*buf++;

	/** Start write **/
	TRISA = 0x00;
	
	/** Write unlock command **/
	// Write command 0xAA	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xAA;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xAA 
	
	
	// Write command 0x55	         
	// Set addr                         
	LATB = cmdAAAA_1; 					 
	LATA = cmdAAAA_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0x55;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0x55 
	
	
	// Write command 0xA0	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xA0;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xA0 
	
	

	/** Write data **/
	// Set addr                         
	LATB = addr8;
	LATD = addr16; 
	LATA = addr0++;    
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set data                          
	LATA = *buf;                    
	val = (*buf & 0x80);			
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write data 
	
	

	/** Wait for completion or error **/
    TRISA = 0xFF;

	// poll for completion
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_81;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_81;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_81;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_81;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_81;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_81;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_81;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_81;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	
	// max attempt => write error
	goto label_error;

label_js_rom_write_81:
	*buf++;

	/** Start write **/
	TRISA = 0x00;
	
	/** Write unlock command **/
	// Write command 0xAA	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xAA;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xAA 
	
	
	// Write command 0x55	         
	// Set addr                         
	LATB = cmdAAAA_1; 					 
	LATA = cmdAAAA_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0x55;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0x55 
	
	
	// Write command 0xA0	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xA0;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xA0 
	
	

	/** Write data **/
	// Set addr                         
	LATB = addr8;
	LATD = addr16; 
	LATA = addr0++;    
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set data                          
	LATA = *buf;                    
	val = (*buf & 0x80);			
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write data 
	
	

	/** Wait for completion or error **/
    TRISA = 0xFF;

	// poll for completion
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_82;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_82;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_82;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_82;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_82;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_82;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_82;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_82;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	
	// max attempt => write error
	goto label_error;

label_js_rom_write_82:
	*buf++;

	/** Start write **/
	TRISA = 0x00;
	
	/** Write unlock command **/
	// Write command 0xAA	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xAA;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xAA 
	
	
	// Write command 0x55	         
	// Set addr                         
	LATB = cmdAAAA_1; 					 
	LATA = cmdAAAA_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0x55;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0x55 
	
	
	// Write command 0xA0	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xA0;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xA0 
	
	

	/** Write data **/
	// Set addr                         
	LATB = addr8;
	LATD = addr16; 
	LATA = addr0++;    
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set data                          
	LATA = *buf;                    
	val = (*buf & 0x80);			
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write data 
	
	

	/** Wait for completion or error **/
    TRISA = 0xFF;

	// poll for completion
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_83;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_83;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_83;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_83;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_83;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_83;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_83;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_83;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	
	// max attempt => write error
	goto label_error;

label_js_rom_write_83:
	*buf++;

	/** Start write **/
	TRISA = 0x00;
	
	/** Write unlock command **/
	// Write command 0xAA	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xAA;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xAA 
	
	
	// Write command 0x55	         
	// Set addr                         
	LATB = cmdAAAA_1; 					 
	LATA = cmdAAAA_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0x55;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0x55 
	
	
	// Write command 0xA0	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xA0;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xA0 
	
	

	/** Write data **/
	// Set addr                         
	LATB = addr8;
	LATD = addr16; 
	LATA = addr0++;    
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set data                          
	LATA = *buf;                    
	val = (*buf & 0x80);			
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write data 
	
	

	/** Wait for completion or error **/
    TRISA = 0xFF;

	// poll for completion
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_84;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_84;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_84;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_84;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_84;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_84;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_84;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_84;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	
	// max attempt => write error
	goto label_error;

label_js_rom_write_84:
	*buf++;

	/** Start write **/
	TRISA = 0x00;
	
	/** Write unlock command **/
	// Write command 0xAA	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xAA;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xAA 
	
	
	// Write command 0x55	         
	// Set addr                         
	LATB = cmdAAAA_1; 					 
	LATA = cmdAAAA_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0x55;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0x55 
	
	
	// Write command 0xA0	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xA0;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xA0 
	
	

	/** Write data **/
	// Set addr                         
	LATB = addr8;
	LATD = addr16; 
	LATA = addr0++;    
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set data                          
	LATA = *buf;                    
	val = (*buf & 0x80);			
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write data 
	
	

	/** Wait for completion or error **/
    TRISA = 0xFF;

	// poll for completion
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_85;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_85;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_85;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_85;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_85;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_85;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_85;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_85;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	
	// max attempt => write error
	goto label_error;

label_js_rom_write_85:
	*buf++;

	/** Start write **/
	TRISA = 0x00;
	
	/** Write unlock command **/
	// Write command 0xAA	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xAA;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xAA 
	
	
	// Write command 0x55	         
	// Set addr                         
	LATB = cmdAAAA_1; 					 
	LATA = cmdAAAA_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0x55;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0x55 
	
	
	// Write command 0xA0	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xA0;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xA0 
	
	

	/** Write data **/
	// Set addr                         
	LATB = addr8;
	LATD = addr16; 
	LATA = addr0++;    
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set data                          
	LATA = *buf;                    
	val = (*buf & 0x80);			
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write data 
	
	

	/** Wait for completion or error **/
    TRISA = 0xFF;

	// poll for completion
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_86;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_86;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_86;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_86;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_86;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_86;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_86;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_86;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	
	// max attempt => write error
	goto label_error;

label_js_rom_write_86:
	*buf++;

	/** Start write **/
	TRISA = 0x00;
	
	/** Write unlock command **/
	// Write command 0xAA	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xAA;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xAA 
	
	
	// Write command 0x55	         
	// Set addr                         
	LATB = cmdAAAA_1; 					 
	LATA = cmdAAAA_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0x55;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0x55 
	
	
	// Write command 0xA0	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xA0;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xA0 
	
	

	/** Write data **/
	// Set addr                         
	LATB = addr8;
	LATD = addr16; 
	LATA = addr0++;    
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set data                          
	LATA = *buf;                    
	val = (*buf & 0x80);			
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write data 
	
	

	/** Wait for completion or error **/
    TRISA = 0xFF;

	// poll for completion
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_87;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_87;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_87;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_87;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_87;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_87;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_87;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_87;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	
	// max attempt => write error
	goto label_error;

label_js_rom_write_87:
	*buf++;

	/** Start write **/
	TRISA = 0x00;
	
	/** Write unlock command **/
	// Write command 0xAA	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xAA;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xAA 
	
	
	// Write command 0x55	         
	// Set addr                         
	LATB = cmdAAAA_1; 					 
	LATA = cmdAAAA_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0x55;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0x55 
	
	
	// Write command 0xA0	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xA0;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xA0 
	
	

	/** Write data **/
	// Set addr                         
	LATB = addr8;
	LATD = addr16; 
	LATA = addr0++;    
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set data                          
	LATA = *buf;                    
	val = (*buf & 0x80);			
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write data 
	
	

	/** Wait for completion or error **/
    TRISA = 0xFF;

	// poll for completion
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_88;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_88;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_88;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_88;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_88;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_88;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_88;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_88;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	
	// max attempt => write error
	goto label_error;

label_js_rom_write_88:
	*buf++;

	/** Start write **/
	TRISA = 0x00;
	
	/** Write unlock command **/
	// Write command 0xAA	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xAA;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xAA 
	
	
	// Write command 0x55	         
	// Set addr                         
	LATB = cmdAAAA_1; 					 
	LATA = cmdAAAA_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0x55;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0x55 
	
	
	// Write command 0xA0	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xA0;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xA0 
	
	

	/** Write data **/
	// Set addr                         
	LATB = addr8;
	LATD = addr16; 
	LATA = addr0++;    
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set data                          
	LATA = *buf;                    
	val = (*buf & 0x80);			
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write data 
	
	

	/** Wait for completion or error **/
    TRISA = 0xFF;

	// poll for completion
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_89;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_89;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_89;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_89;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_89;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_89;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_89;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_89;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	
	// max attempt => write error
	goto label_error;

label_js_rom_write_89:
	*buf++;

	/** Start write **/
	TRISA = 0x00;
	
	/** Write unlock command **/
	// Write command 0xAA	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xAA;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xAA 
	
	
	// Write command 0x55	         
	// Set addr                         
	LATB = cmdAAAA_1; 					 
	LATA = cmdAAAA_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0x55;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0x55 
	
	
	// Write command 0xA0	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xA0;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xA0 
	
	

	/** Write data **/
	// Set addr                         
	LATB = addr8;
	LATD = addr16; 
	LATA = addr0++;    
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set data                          
	LATA = *buf;                    
	val = (*buf & 0x80);			
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write data 
	
	

	/** Wait for completion or error **/
    TRISA = 0xFF;

	// poll for completion
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_810;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_810;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_810;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_810;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_810;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_810;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_810;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_810;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	
	// max attempt => write error
	goto label_error;

label_js_rom_write_810:
	*buf++;

	/** Start write **/
	TRISA = 0x00;
	
	/** Write unlock command **/
	// Write command 0xAA	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xAA;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xAA 
	
	
	// Write command 0x55	         
	// Set addr                         
	LATB = cmdAAAA_1; 					 
	LATA = cmdAAAA_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0x55;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0x55 
	
	
	// Write command 0xA0	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xA0;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xA0 
	
	

	/** Write data **/
	// Set addr                         
	LATB = addr8;
	LATD = addr16; 
	LATA = addr0++;    
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set data                          
	LATA = *buf;                    
	val = (*buf & 0x80);			
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write data 
	
	

	/** Wait for completion or error **/
    TRISA = 0xFF;

	// poll for completion
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_811;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_811;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_811;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_811;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_811;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_811;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_811;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_811;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	
	// max attempt => write error
	goto label_error;

label_js_rom_write_811:
	*buf++;

	/** Start write **/
	TRISA = 0x00;
	
	/** Write unlock command **/
	// Write command 0xAA	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xAA;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xAA 
	
	
	// Write command 0x55	         
	// Set addr                         
	LATB = cmdAAAA_1; 					 
	LATA = cmdAAAA_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0x55;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0x55 
	
	
	// Write command 0xA0	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xA0;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xA0 
	
	

	/** Write data **/
	// Set addr                         
	LATB = addr8;
	LATD = addr16; 
	LATA = addr0++;    
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set data                          
	LATA = *buf;                    
	val = (*buf & 0x80);			
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write data 
	
	

	/** Wait for completion or error **/
    TRISA = 0xFF;

	// poll for completion
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_812;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_812;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_812;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_812;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_812;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_812;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_812;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_812;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	
	// max attempt => write error
	goto label_error;

label_js_rom_write_812:
	*buf++;

	/** Start write **/
	TRISA = 0x00;
	
	/** Write unlock command **/
	// Write command 0xAA	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xAA;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xAA 
	
	
	// Write command 0x55	         
	// Set addr                         
	LATB = cmdAAAA_1; 					 
	LATA = cmdAAAA_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0x55;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0x55 
	
	
	// Write command 0xA0	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xA0;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xA0 
	
	

	/** Write data **/
	// Set addr                         
	LATB = addr8;
	LATD = addr16; 
	LATA = addr0++;    
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set data                          
	LATA = *buf;                    
	val = (*buf & 0x80);			
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write data 
	
	

	/** Wait for completion or error **/
    TRISA = 0xFF;

	// poll for completion
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_813;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_813;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_813;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_813;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_813;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_813;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_813;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_813;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	
	// max attempt => write error
	goto label_error;

label_js_rom_write_813:
	*buf++;

	/** Start write **/
	TRISA = 0x00;
	
	/** Write unlock command **/
	// Write command 0xAA	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xAA;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xAA 
	
	
	// Write command 0x55	         
	// Set addr                         
	LATB = cmdAAAA_1; 					 
	LATA = cmdAAAA_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0x55;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0x55 
	
	
	// Write command 0xA0	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xA0;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xA0 
	
	

	/** Write data **/
	// Set addr                         
	LATB = addr8;
	LATD = addr16; 
	LATA = addr0++;    
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set data                          
	LATA = *buf;                    
	val = (*buf & 0x80);			
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write data 
	
	

	/** Wait for completion or error **/
    TRISA = 0xFF;

	// poll for completion
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_814;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_814;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_814;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_814;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_814;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_814;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_814;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_814;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	
	// max attempt => write error
	goto label_error;

label_js_rom_write_814:
	*buf++;

	/** Start write **/
	TRISA = 0x00;
	
	/** Write unlock command **/
	// Write command 0xAA	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xAA;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xAA 
	
	
	// Write command 0x55	         
	// Set addr                         
	LATB = cmdAAAA_1; 					 
	LATA = cmdAAAA_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0x55;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0x55 
	
	
	// Write command 0xA0	         
	// Set addr                         
	LATB = cmd5555_1; 					 
	LATA = cmd5555_0;             		 
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set CMD                          
	LATA = 0xA0;                    
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write command 0xA0 
	
	

	/** Write data **/
	// Set addr                         
	LATB = addr8;
	LATD = addr16; 
	LATA = addr0++;    
	                                    
	// Toggle 74hc573 Clk               
	LATCbits.LC6 = 1;                   
	LATCbits.LC6 = 0;                   
	                                    
	// Set data                          
	LATA = *buf;                    
	val = (*buf & 0x80);			
	                                   
	// Toggle CE/WE                    
	LATCbits.LC2 = 0; // CE Low        
	WE_L; //                           
	                                   
	// Wait                            
	__nop();                           
	                                    
	WE_H;  // WE High                  
	LATCbits.LC2 = 1;  // CE High      
	// End Write data 
	
	

	/** Wait for completion or error **/
    TRISA = 0xFF;

	// poll for completion
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_815;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_815;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_815;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_815;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_815;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_815;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_815;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	// Wait a few
	__nop();
	CSL;
	// wait a few
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	data = PORTA;	
	CSH;

	// check bit 7 only
	if (val == (data & 0x80)) {
		// Finished
		goto label_js_rom_write_815;
	}

	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	
	// max attempt => write error
	goto label_error;

label_js_rom_write_815:
	*buf++;
	}

	return ROM_OK;
	
/** poll error ? **/	
label_error:		
	return 0xFF;
}



