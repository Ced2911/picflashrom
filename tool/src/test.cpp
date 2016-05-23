#include <stdio.h>
#include <stdlib.h>
#include "ccrwrom.h"
#include "usb.h"
#include "debug.h"
#include "Command.h"



int rom_debug_write(const char * filename, uint32_t size) {
#define BSIZE	0x410000 
#define DUMP_SIZE	0x80
	uint8_t * data = new uint8_t[BSIZE];
	uint8_t * verif = new uint8_t[BSIZE];
	FILE * fd = fopen(filename, "rb");
	if (fd) {
		fread(data, BSIZE, 1, fd);

		// Erase the chip first
		cmd_erase();

		// now flash !
		if (cmd_write_rom(data, size) == -1) {
			fprintf(stdout, "error will writing %s.\r\n", filename);
			return -1;
		}
		fclose(fd);

		// now read back data
		cmd_read_rom(verif, size + 0x40);

		// now compare
		for (int i = 0; i < size; i++) {
			if (data[i] != verif[i]) {

				fprintf(stdout, "error at %08x\r\n", i);

				fprintf(stdout, "read\r\n");
				hexdump(&verif[i & 0xFFF0], DUMP_SIZE);

				fprintf(stdout, "source\r\n");
				hexdump(&data[i & 0xFFF0], DUMP_SIZE);
				return -1;
			}
		}
		fprintf(stdout, "test ok\r\n");
		return 0;
	}
	else {
		fprintf(stdout, "Can not open %s for reading.\r\n", filename);
	}
	return -1;
}

