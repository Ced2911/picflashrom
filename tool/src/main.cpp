#ifdef WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#ifdef WIN32
#include "getopt_win32.h"
#else
#include <getopt.h>
#endif
#include <thread>
#include <future>
#include <assert.h>
#include <filesystem>
#include "hidapi.h"
#include "Command.h"
#include "usb.h"
#include "ccrwrom.h"
#include "romdb.h"
#include "rom_tools.h"
#include "debug.h"

#ifdef WIN32
#define PATH_DELIM	'\\'
#else
#define PATH_DELIM	'/'
#endif


enum ARG_COMMAND {
	ARG_HELP = 0,
	ARG_BOOTLOADER,
	ARG_READ,
	ARG_ID,
	ARG_ERASE,
	ARG_WRITE,
#if _DEBUG
	ARG_DBG,
#endif
};


struct command_available_t : option {
	const char *help;
	command_available_t(const char *_name, int _has_arg, int *_flag, int _val, const char *_help)  {
		name = _name;
		has_arg = _has_arg;
		flag = _flag;
		val = _val;
		help = _help;
	}
};


static std::string app_name;
static char optlg[256] = "";

static command_available_t commands[] = {
	{ "verbose", no_argument,       &verbose_flag, 'v' , "Display verbose information" },
	{ "bootloader", no_argument,       0, 'b' , "Reboot to bootloader" },
	{ "erase",     no_argument,       0, 'e', "Erase the rom" },
	{ "identify",     no_argument,       0, 'i', "Identify the rom" },
	{ "write",  required_argument, 0, 'w', "Write file to the rom" },
	{ "read",  required_argument, 0, 'r' , "Read rom to file" },
	{ "size",    required_argument, 0, 's', "Size to read/write in bytes" },
	{ "M",    required_argument, 0, 'm', "Size to read/write in megabit" },
#if _DEBUG
	{ "debug",    required_argument, 0, 'd', "Debug cmd..." },
#endif
	{ NULL, NULL, NULL, NULL, NULL }
};

static void build_opt_lg() {
	char * o = optlg;
	for (int i = 0; i < ARRAY_SIZE(commands); i++) {
		if (commands[i].name != NULL) {
			*o++ = commands[i].val;
			if (commands[i].has_arg) {
				*o++ = ':';
			}
		}
	}
	*o++ = NULL;
}

int rom_debug_write(const char * filename, uint32_t size);

static void help() {
	char help[2048] = "";
	char * p = help;
	output::print("usage: %s\r\n", app_name.c_str());

	for (int i = 0; i < ARRAY_SIZE(commands); i++) {
		if (commands[i].name !=NULL)
			output::print("\t -%s \t\t %s\r\n", commands[i].name, commands[i].help);
	}
}


static void progress_barr(char *label, int step, int total)
{
	//progress width
	const int pwidth = 72;

	//minus label len
	int width = pwidth - strlen(label);
	int pos = (step * width) / total;
	int percent = (step * 100) / total;

	printf("%s[", label);

	//fill progress bar with =
	for (int i = 0; i < pos; i++)  printf("%c", '=');

	//fill progress bar with spaces
	printf("% *c", width - pos + 1, ']');
	printf(" %3d%%\r", percent);
}


static void rom_read(const char * filename, uint32_t size) {
	uint8_t * data = new uint8_t[size];
	FILE * fd = fopen(filename, "wb");
	if (fd) {
		// run in thread
		output::info("Reading to %s\r\n", filename);
		cclock elapsed;
		std::chrono::milliseconds span(100);
		std::future<uint32_t> read = std::async(cmd_read_rom, data, size);
		float percent = 0;

		while (read.wait_for(span) == std::future_status::timeout) {
			progress_barr("Reading: ", cmd_position.get(), size);
		}

		// Finished
		if (read.get() == 0) {
			// 100%
			progress_barr("Reading: ", size, size);

			if (verbose_flag) {
				output::info("\r\nTime elapsed %f\r\n", elapsed.elapsed());
			}

			fwrite(data, size, 1, fd);
		}
		else {
			output::error("Error reading eeprom to %s.\r\n", filename);
		}
	}
	else {
		output::error("Can not open %s for writing.\r\n", filename);
	}
	fclose(fd);
	//delete[] data;
}

static int rom_write(const char * filename, uint32_t size) {
	uint8_t * data = new uint8_t[size];
	FILE * fd = fopen(filename, "rb");
	if (fd) {
		fread(data, size, 1, fd);

		// Erase the chip first
		cmd_erase();


		// run in thread
		cclock elapsed;
		std::chrono::milliseconds span(100);
		std::future<uint32_t> write = std::async(cmd_write_rom, data, size);
		float percent = 0;
		output::info("Writing %s\r\n", filename);

		while (write.wait_for(span) == std::future_status::timeout) {
			progress_barr("Writing: ", cmd_position.get(), size);
		}

		// Finished
		if (write.get() == 0) {
			// 100%
			progress_barr("Writing: ", size, size);

			if (verbose_flag) {
				output::info("\r\nTime elapsed %f\r\n", elapsed.elapsed());
			}
		}
		fclose(fd);
		return 0;
	}
	else {
		output::error("Can not open %s for reading.\r\n", filename);
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
	int option_index = 0;

	app_name = std::tr2::sys::path(argv[0]).filename().generic_string();
	build_opt_lg();


	//while ((c = getopt(argc, argv, "bier:w:s:m:d:")) != -1)
	while ((c = getopt_long(argc, argv, optlg, commands, &option_index)) != -1)
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
				output::success("reboot to bootloader\r\n");
				break;

			case ARG_ID:
				// Identify rom
				cmd_read_id(buf);
				rom = romdb_identify(buf[0], buf[1]);
				if (rom) {
					output::info(rom->manufacturer);
					output::info(rom->name);
				}
				else {
					output::warning("Unknown chip\r\n");
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
					output::success("Chip read\r\n");
				}

				break;
			case ARG_ERASE:
				cmd_erase();
				output::success("Chip erased\r\n");
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
						output::success("Chip written\r\n");
					}
					else {
						output::error("Error\r\n");
					}
				}
				break;

			case ARG_DBG:
				rom_debug_write(filename, size);
				break;
			}
		}
		else {
			output::error("No device connected\r\n");
		}

		usb.close();
	}


	return 0;
}
