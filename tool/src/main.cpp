#ifdef WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#ifdef WIN32
#include "getopt_win32.h"
#endif
#include <assert.h>
#include "hidapi.h"
#include "Command.h"
#include "usb.h"
#include "ccrwrom.h"
#include "romdb.h"
#include "debug.h"


enum ARG_COMMAND {
	ARG_HELP = 0,
	ARG_BOOTLOADER,
	ARG_READ,
	ARG_ID,
	ARG_ERASE,
	ARG_WRITE,

	ARG_DBG,
};

int rom_debug_write(const char * filename, uint32_t size);

void help() {
	puts("help: \r\n");
}

void rom_read(const char * filename, uint32_t size) {
	uint8_t * data = new uint8_t[size];
	FILE * fd = fopen(filename, "wb");
	if (fd) {
		cmd_read_rom(data, size);
		fwrite(data, size, 1, fd);
	}
	else {
		fprintf(stdout, "Can not open %s for writing.\r\n", filename);
	}
	fclose(fd);
	//delete[] data;
}

void convert_rom() {
	// sst39f addr 16 is oe...
	// 
}

int rom_write(const char * filename, uint32_t size) {
	uint8_t * data = new uint8_t[size];
	FILE * fd = fopen(filename, "rb");
	if (fd) {
		fread(data, size, 1, fd);

		// Erase the chip first
		cmd_erase();

		// now flash !
		if (cmd_write_rom(data, size) == -1) {
			fprintf(stdout, "error will writing %s.\r\n", filename);
			return -1;
		}
		fclose(fd);
		return 0;
	}
	else {
		fprintf(stdout, "Can not open %s for reading.\r\n", filename);
	}
	return -1;
	//delete[] data;
}


int main(int argc, char* argv[])
{
	void *handle = NULL;
	int c;
	extern char * optarg;
	extern int optind, opterr;
	char filename[MAX_STR];
	uint8_t buf[USB_PACKET_SIZE << 1] = {};
	uint32_t size = 0;

	// Compiler check !
	assert(sizeof(usb_packet_t) == USB_PACKET_SIZE);
	assert(sizeof(usb_packet_w_t) == USB_PACKET_SIZE);

	ARG_COMMAND command = ARG_HELP;
	const rom_t * rom = NULL;
	uint8_t id[2] = {};

	while ((c = getopt(argc, argv, "bier:w:s:m:d:")) != -1)
		switch (c) {
		case 'd':
			command = ARG_DBG;
			if (optarg) {
				strcpy(filename, optarg);
			}
			break;
		case 's':
			//size = atoi(optarg) * 128 * 1024;
			size = atoi(optarg);
			break;

		case 'm':
			size = atoi(optarg) * 128 * 1024;
			//size = atoi(optarg);
			break;
		case 'b':
			command = ARG_BOOTLOADER;
			break;
		case 'i':
			command = ARG_ID;
			break;
		case 'e':
			command = ARG_ERASE;
			break;
		case 'r':
			command = ARG_READ;
			if (optarg) {
				strcpy(filename, optarg);
			}
			break;
		case 'w':
			command = ARG_WRITE;
			if (optarg) {
				strcpy(filename, optarg);
			}
			break;
		}

	if (command == ARG_HELP) {
		help();
	}
	else {
		handle = usb.connect();
		if (handle != NULL) {
			cmd_query(buf);
			if (buf[0x01] == 0x29) {

			}
			switch (command) {
			case ARG_BOOTLOADER:
				cmd_bootloader();
				puts("reboot to bootloader\r\n");
				break;

			case ARG_ID:
				// Identify rom
				cmd_read_id(buf);
				rom = romdb_identify(buf[0], buf[1]);
				if (rom) {
					puts(rom->manufacturer);
					puts(rom->name);
				}
				else {
					puts("Unknown chip\r\n");
				}

				break;
			case ARG_READ:
				if (size == 0) {
					cmd_read_id(buf);
					rom = romdb_identify(buf[0], buf[1]);
					if (rom) {
						size = rom->size;
					}
				}
				if (size > 0) {
					rom_read(filename, size);
					puts("Chip read\r\n");
				}

				break;
			case ARG_ERASE:
				cmd_erase();
				puts("Chip erased\r\n");
				break;
			case ARG_WRITE:
				//size = 0x40;
				if (size == 0) {
					cmd_read_id(buf);
					rom = romdb_identify(buf[0], buf[1]);
					if (rom) {
						size = rom->size;
					}
				}
				if (size > 0) {
					if (rom_write(filename, size) == 0) {
						puts("Chip written\r\n");
					}
					else {
						puts("Error\r\n");
					}
				}
				break;

			case ARG_DBG:
				rom_debug_write(filename, size);
				break;
			}
		}
		else {
			puts("No device connected\r\n");
		}

		usb.close();
	}


	return 0;
}