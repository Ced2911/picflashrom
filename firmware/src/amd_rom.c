/*
 * File:   amd_rom.c
 * Author: cc
 *
 * Created on 20 janvier 2017, 17:05
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

uint8_t amd_unlock_rom_write_8_16(uint8_t * in, uint32_t addr, uint8_t _len) {
    uint8_t p = 0;
    uint8_t * buf = in;
    const uint8_t len = 0x40;
		
	/** data polling vars **/
    uint8_t data = 0;
	uint8_t val = 0;
	
	/** cache some vars **/
	uint8_t addr0 = addr;
	uint8_t addr8 = (addr & 0x0000FF00) >> 8;
	uint8_t addr16 = (addr & 0x00FF0000) >> 16;
	
	/** Start write **/
	TRISA = 0x00;	
	WE_H;
	LATCbits.LC1 = 1; // OE H
    
	for(int loop = 4; loop > 0; loop--) {
		// Set cmd addr                         
		LATB = addr8;
		LATD = addr16; 
		LATA = 0;    
		                                    
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
		// Cmd written
		LATA = addr0++;    
		// Toggle 74hc573 Clk               
		LATCbits.LC6 = 1;                   
		LATCbits.LC6 = 0;                   
		// Set data                         
		LATA = *buf;                    	
		val = LATA & 0x80;					
		                                   
		// Toggle CE/WE                    
		LATCbits.LC2 = 0; // CE Low        
		WE_L; //                           
		                                   
		// Wait                            
		__nop();                           
		                                    
		WE_H;  // WE High                  
		LATCbits.LC2 = 1;  // CE High      
		// End Write data 
		
		
        /** Wait for completion or error **/
		if (mx_data_poll(val) != 0) {
            // ERROR !
            return ROM_ERROR;
        }
		*buf++;
		// Set cmd addr                         
		LATB = addr8;
		LATD = addr16; 
		LATA = 0;    
		                                    
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
		// Cmd written
		LATA = addr0++;    
		// Toggle 74hc573 Clk               
		LATCbits.LC6 = 1;                   
		LATCbits.LC6 = 0;                   
		// Set data                         
		LATA = *buf;                    	
		val = LATA & 0x80;					
		                                   
		// Toggle CE/WE                    
		LATCbits.LC2 = 0; // CE Low        
		WE_L; //                           
		                                   
		// Wait                            
		__nop();                           
		                                    
		WE_H;  // WE High                  
		LATCbits.LC2 = 1;  // CE High      
		// End Write data 
		
		
        /** Wait for completion or error **/
		if (mx_data_poll(val) != 0) {
            // ERROR !
            return ROM_ERROR;
        }
		*buf++;
		// Set cmd addr                         
		LATB = addr8;
		LATD = addr16; 
		LATA = 0;    
		                                    
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
		// Cmd written
		LATA = addr0++;    
		// Toggle 74hc573 Clk               
		LATCbits.LC6 = 1;                   
		LATCbits.LC6 = 0;                   
		// Set data                         
		LATA = *buf;                    	
		val = LATA & 0x80;					
		                                   
		// Toggle CE/WE                    
		LATCbits.LC2 = 0; // CE Low        
		WE_L; //                           
		                                   
		// Wait                            
		__nop();                           
		                                    
		WE_H;  // WE High                  
		LATCbits.LC2 = 1;  // CE High      
		// End Write data 
		
		
        /** Wait for completion or error **/
		if (mx_data_poll(val) != 0) {
            // ERROR !
            return ROM_ERROR;
        }
		*buf++;
		// Set cmd addr                         
		LATB = addr8;
		LATD = addr16; 
		LATA = 0;    
		                                    
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
		// Cmd written
		LATA = addr0++;    
		// Toggle 74hc573 Clk               
		LATCbits.LC6 = 1;                   
		LATCbits.LC6 = 0;                   
		// Set data                         
		LATA = *buf;                    	
		val = LATA & 0x80;					
		                                   
		// Toggle CE/WE                    
		LATCbits.LC2 = 0; // CE Low        
		WE_L; //                           
		                                   
		// Wait                            
		__nop();                           
		                                    
		WE_H;  // WE High                  
		LATCbits.LC2 = 1;  // CE High      
		// End Write data 
		
		
        /** Wait for completion or error **/
		if (mx_data_poll(val) != 0) {
            // ERROR !
            return ROM_ERROR;
        }
		*buf++;
		// Set cmd addr                         
		LATB = addr8;
		LATD = addr16; 
		LATA = 0;    
		                                    
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
		// Cmd written
		LATA = addr0++;    
		// Toggle 74hc573 Clk               
		LATCbits.LC6 = 1;                   
		LATCbits.LC6 = 0;                   
		// Set data                         
		LATA = *buf;                    	
		val = LATA & 0x80;					
		                                   
		// Toggle CE/WE                    
		LATCbits.LC2 = 0; // CE Low        
		WE_L; //                           
		                                   
		// Wait                            
		__nop();                           
		                                    
		WE_H;  // WE High                  
		LATCbits.LC2 = 1;  // CE High      
		// End Write data 
		
		
        /** Wait for completion or error **/
		if (mx_data_poll(val) != 0) {
            // ERROR !
            return ROM_ERROR;
        }
		*buf++;
		// Set cmd addr                         
		LATB = addr8;
		LATD = addr16; 
		LATA = 0;    
		                                    
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
		// Cmd written
		LATA = addr0++;    
		// Toggle 74hc573 Clk               
		LATCbits.LC6 = 1;                   
		LATCbits.LC6 = 0;                   
		// Set data                         
		LATA = *buf;                    	
		val = LATA & 0x80;					
		                                   
		// Toggle CE/WE                    
		LATCbits.LC2 = 0; // CE Low        
		WE_L; //                           
		                                   
		// Wait                            
		__nop();                           
		                                    
		WE_H;  // WE High                  
		LATCbits.LC2 = 1;  // CE High      
		// End Write data 
		
		
        /** Wait for completion or error **/
		if (mx_data_poll(val) != 0) {
            // ERROR !
            return ROM_ERROR;
        }
		*buf++;
		// Set cmd addr                         
		LATB = addr8;
		LATD = addr16; 
		LATA = 0;    
		                                    
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
		// Cmd written
		LATA = addr0++;    
		// Toggle 74hc573 Clk               
		LATCbits.LC6 = 1;                   
		LATCbits.LC6 = 0;                   
		// Set data                         
		LATA = *buf;                    	
		val = LATA & 0x80;					
		                                   
		// Toggle CE/WE                    
		LATCbits.LC2 = 0; // CE Low        
		WE_L; //                           
		                                   
		// Wait                            
		__nop();                           
		                                    
		WE_H;  // WE High                  
		LATCbits.LC2 = 1;  // CE High      
		// End Write data 
		
		
        /** Wait for completion or error **/
		if (mx_data_poll(val) != 0) {
            // ERROR !
            return ROM_ERROR;
        }
		*buf++;
		// Set cmd addr                         
		LATB = addr8;
		LATD = addr16; 
		LATA = 0;    
		                                    
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
		// Cmd written
		LATA = addr0++;    
		// Toggle 74hc573 Clk               
		LATCbits.LC6 = 1;                   
		LATCbits.LC6 = 0;                   
		// Set data                         
		LATA = *buf;                    	
		val = LATA & 0x80;					
		                                   
		// Toggle CE/WE                    
		LATCbits.LC2 = 0; // CE Low        
		WE_L; //                           
		                                   
		// Wait                            
		__nop();                           
		                                    
		WE_H;  // WE High                  
		LATCbits.LC2 = 1;  // CE High      
		// End Write data 
		
		
        /** Wait for completion or error **/
		if (mx_data_poll(val) != 0) {
            // ERROR !
            return ROM_ERROR;
        }
		*buf++;
		// Set cmd addr                         
		LATB = addr8;
		LATD = addr16; 
		LATA = 0;    
		                                    
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
		// Cmd written
		LATA = addr0++;    
		// Toggle 74hc573 Clk               
		LATCbits.LC6 = 1;                   
		LATCbits.LC6 = 0;                   
		// Set data                         
		LATA = *buf;                    	
		val = LATA & 0x80;					
		                                   
		// Toggle CE/WE                    
		LATCbits.LC2 = 0; // CE Low        
		WE_L; //                           
		                                   
		// Wait                            
		__nop();                           
		                                    
		WE_H;  // WE High                  
		LATCbits.LC2 = 1;  // CE High      
		// End Write data 
		
		
        /** Wait for completion or error **/
		if (mx_data_poll(val) != 0) {
            // ERROR !
            return ROM_ERROR;
        }
		*buf++;
		// Set cmd addr                         
		LATB = addr8;
		LATD = addr16; 
		LATA = 0;    
		                                    
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
		// Cmd written
		LATA = addr0++;    
		// Toggle 74hc573 Clk               
		LATCbits.LC6 = 1;                   
		LATCbits.LC6 = 0;                   
		// Set data                         
		LATA = *buf;                    	
		val = LATA & 0x80;					
		                                   
		// Toggle CE/WE                    
		LATCbits.LC2 = 0; // CE Low        
		WE_L; //                           
		                                   
		// Wait                            
		__nop();                           
		                                    
		WE_H;  // WE High                  
		LATCbits.LC2 = 1;  // CE High      
		// End Write data 
		
		
        /** Wait for completion or error **/
		if (mx_data_poll(val) != 0) {
            // ERROR !
            return ROM_ERROR;
        }
		*buf++;
		// Set cmd addr                         
		LATB = addr8;
		LATD = addr16; 
		LATA = 0;    
		                                    
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
		// Cmd written
		LATA = addr0++;    
		// Toggle 74hc573 Clk               
		LATCbits.LC6 = 1;                   
		LATCbits.LC6 = 0;                   
		// Set data                         
		LATA = *buf;                    	
		val = LATA & 0x80;					
		                                   
		// Toggle CE/WE                    
		LATCbits.LC2 = 0; // CE Low        
		WE_L; //                           
		                                   
		// Wait                            
		__nop();                           
		                                    
		WE_H;  // WE High                  
		LATCbits.LC2 = 1;  // CE High      
		// End Write data 
		
		
        /** Wait for completion or error **/
		if (mx_data_poll(val) != 0) {
            // ERROR !
            return ROM_ERROR;
        }
		*buf++;
		// Set cmd addr                         
		LATB = addr8;
		LATD = addr16; 
		LATA = 0;    
		                                    
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
		// Cmd written
		LATA = addr0++;    
		// Toggle 74hc573 Clk               
		LATCbits.LC6 = 1;                   
		LATCbits.LC6 = 0;                   
		// Set data                         
		LATA = *buf;                    	
		val = LATA & 0x80;					
		                                   
		// Toggle CE/WE                    
		LATCbits.LC2 = 0; // CE Low        
		WE_L; //                           
		                                   
		// Wait                            
		__nop();                           
		                                    
		WE_H;  // WE High                  
		LATCbits.LC2 = 1;  // CE High      
		// End Write data 
		
		
        /** Wait for completion or error **/
		if (mx_data_poll(val) != 0) {
            // ERROR !
            return ROM_ERROR;
        }
		*buf++;
		// Set cmd addr                         
		LATB = addr8;
		LATD = addr16; 
		LATA = 0;    
		                                    
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
		// Cmd written
		LATA = addr0++;    
		// Toggle 74hc573 Clk               
		LATCbits.LC6 = 1;                   
		LATCbits.LC6 = 0;                   
		// Set data                         
		LATA = *buf;                    	
		val = LATA & 0x80;					
		                                   
		// Toggle CE/WE                    
		LATCbits.LC2 = 0; // CE Low        
		WE_L; //                           
		                                   
		// Wait                            
		__nop();                           
		                                    
		WE_H;  // WE High                  
		LATCbits.LC2 = 1;  // CE High      
		// End Write data 
		
		
        /** Wait for completion or error **/
		if (mx_data_poll(val) != 0) {
            // ERROR !
            return ROM_ERROR;
        }
		*buf++;
		// Set cmd addr                         
		LATB = addr8;
		LATD = addr16; 
		LATA = 0;    
		                                    
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
		// Cmd written
		LATA = addr0++;    
		// Toggle 74hc573 Clk               
		LATCbits.LC6 = 1;                   
		LATCbits.LC6 = 0;                   
		// Set data                         
		LATA = *buf;                    	
		val = LATA & 0x80;					
		                                   
		// Toggle CE/WE                    
		LATCbits.LC2 = 0; // CE Low        
		WE_L; //                           
		                                   
		// Wait                            
		__nop();                           
		                                    
		WE_H;  // WE High                  
		LATCbits.LC2 = 1;  // CE High      
		// End Write data 
		
		
        /** Wait for completion or error **/
		if (mx_data_poll(val) != 0) {
            // ERROR !
            return ROM_ERROR;
        }
		*buf++;
		// Set cmd addr                         
		LATB = addr8;
		LATD = addr16; 
		LATA = 0;    
		                                    
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
		// Cmd written
		LATA = addr0++;    
		// Toggle 74hc573 Clk               
		LATCbits.LC6 = 1;                   
		LATCbits.LC6 = 0;                   
		// Set data                         
		LATA = *buf;                    	
		val = LATA & 0x80;					
		                                   
		// Toggle CE/WE                    
		LATCbits.LC2 = 0; // CE Low        
		WE_L; //                           
		                                   
		// Wait                            
		__nop();                           
		                                    
		WE_H;  // WE High                  
		LATCbits.LC2 = 1;  // CE High      
		// End Write data 
		
		
        /** Wait for completion or error **/
		if (mx_data_poll(val) != 0) {
            // ERROR !
            return ROM_ERROR;
        }
		*buf++;
		// Set cmd addr                         
		LATB = addr8;
		LATD = addr16; 
		LATA = 0;    
		                                    
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
		// Cmd written
		LATA = addr0++;    
		// Toggle 74hc573 Clk               
		LATCbits.LC6 = 1;                   
		LATCbits.LC6 = 0;                   
		// Set data                         
		LATA = *buf;                    	
		val = LATA & 0x80;					
		                                   
		// Toggle CE/WE                    
		LATCbits.LC2 = 0; // CE Low        
		WE_L; //                           
		                                   
		// Wait                            
		__nop();                           
		                                    
		WE_H;  // WE High                  
		LATCbits.LC2 = 1;  // CE High      
		// End Write data 
		
		
        /** Wait for completion or error **/
		if (mx_data_poll(val) != 0) {
            // ERROR !
            return ROM_ERROR;
        }
		*buf++;
	}

    return ROM_OK;
}