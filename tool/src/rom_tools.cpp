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

void split_16_to_8(uint8_t * in, uint8_t * out0, uint8_t * out1, uint32_t in_size) {
	uint32_t size = (in_size >> 1);
	
	while (size--) {
		*out0++ = *in++;
		*out1++ = *in++;
	}
}


void swap_rom(const char * fin, const char *fout) {
	FILE * fd = fopen(fin, "rb");
	FILE * wa = fopen(fout, "wb");
	uint8_t * bin = NULL;
	uint8_t * ba = NULL;
	uint32_t s = 0;

	if (fd) {
		fseek(fd, 0, SEEK_END);
		s = ftell(fd);
		fseek(fd, 0, SEEK_SET);
	}
	else {
		return;
	}

	bin = new uint8_t[s];
	ba = new uint8_t[s];

	fread(bin, s, 1, fd);

	snes_swap_to_ss39(bin, ba, s);

	fwrite(ba, s, 1, wa);

	fclose(fd);
	fclose(wa);

	delete bin;
	delete ba;
}


void split_rom_16_8(const char * fin, const char *fouta, const char *foutb) {
	FILE * fd = fopen(fin, "rb");
	FILE * wa = fopen(fouta, "wb");
	FILE * wb = fopen(foutb, "wb");
	uint8_t * bin = NULL;
	uint8_t * ba = NULL;
	uint8_t * bb = NULL;
	uint32_t s = 0;

	if (fd) {
		fseek(fd, 0, SEEK_END);
		s = ftell(fd);
		fseek(fd, 0, SEEK_SET);
	}
	else {
		return;
	}

	bin = new uint8_t[s];
	ba = new uint8_t[s];
	bb = new uint8_t[s];

	fread(bin, s, 1, fd);

	split_16_to_8(bin, ba, bb, s);

#if 1 // FOR ME
	uint8_t * baw = new uint8_t[s];
	uint8_t * bbw = new uint8_t[s];

	snes_swap_to_ss39(ba, baw, s);
	snes_swap_to_ss39(bb, bbw, s);
	
	fwrite(baw, s >> 1, 1, wa);
	fwrite(bbw, s >> 1, 1, wb);

	delete baw;
	delete bbw;
#else
	fwrite(ba, s >> 1, 1, wa);
	fwrite(bb, s >> 1, 1, wb);
#endif

	fclose(fd);
	fclose(wa);
	fclose(wb);

	delete bin;
	delete ba;
	delete bb;
}


uint32_t file_size(const char * filename) {
	FILE * fd = fopen(filename, "rb");
	uint32_t s = 0;
	if (fd) {
		fseek(fd, 0, SEEK_END);
		s = ftell(fd);
	}
	fclose(fd);
	return s;
}

