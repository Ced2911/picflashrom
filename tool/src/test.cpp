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
			LERROR("error will writing %s.", filename);
			return -1;
		}
		fclose(fd);

		// now read back data
		cmd_read_rom(verif, 0, size + 0x40);

		// now compare
		for (int i = 0; i < size; i++) {
			if (data[i] != verif[i]) {

				LERROR("error at %08x", i);

				LERROR("read");
				hexdump(&verif[i], DUMP_SIZE);

				LERROR("source");
				hexdump(&data[i], DUMP_SIZE);
				return -1;
			}
		}
		LERROR("test ok");
		return 0;
	}
	else {
		LERROR("Can not open %s for reading.", filename);
	}
	return -1;
}

