#include "rom_tools.h"
#include "debug.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



// MAP
/*
A18		=>	A17*									VDD		  =>	VDD	
A16		=>	A18*									WE#		  =>	OE#	
A15		=>	A15										A17		  =>	A19* => SNES A16	
A12		=>	A12										A14		  =>	A14	
A7		=>	A7 										A13		  =>	A13	
A6		=>	A6 										A8		  =>	A8		
A5		=>	A5 										A9		  =>	A9		
A4		=>	A4 										A11		  =>	A11	
A3		=>	A3 										OE#		  =>	A16* => SST A17	
A2		=>	A2 										A10		  =>	A10	
A1		=>	A1 										CE#		  =>	CE#
A0		=>	A0 										DQ7		  =>	D7		
DQ0		=>	D0 										DQ6		  =>	D6		
DQ1		=>	D1 										DQ5		  =>	D5		
DQ2		=>	D2 										DQ4		  =>	D4		
VSS		=>	VSS							 			DQ3		  =>	D3	
*/


// sst39f addr 16 is oe...
void snes_swap_to_ss39(uint8_t * in, uint8_t * out, uint32_t in_size) {
	// 0 -> 15 same
	memcpy(out, in, in_size);

	memcpy(&out[0x10000], &in[0x40000], 0x10000);
	memcpy(&out[0x20000], &in[0x10000], 0x10000);
	memcpy(&out[0x30000], &in[0x50000], 0x10000);
	memcpy(&out[0x40000], &in[0x20000], 0x10000);
	memcpy(&out[0x50000], &in[0x60000], 0x10000);
	memcpy(&out[0x60000], &in[0x30000], 0x10000);
}

uint8_t * snes_remove_header(uint8_t * in, uint32_t in_size) {
	if ((in_size / 512) & 1) {
		return in + 512;
	} else {
		return in;
	}
}