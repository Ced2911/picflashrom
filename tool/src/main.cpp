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
#include "romdb.h"
#include "ccrwrom.h"
#include "rom_tools.h"
#include "debug.h"
#include "console/snes.h"

#ifdef WIN32
#define PATH_DELIM	'\\'
#else
#define PATH_DELIM	'/'
#endif

int verbose_flag = 0;
int console_type = CONSOLE_TYPE_RAW;
int console_memory_area = 0;

enum ARG_COMMAND {
	ARG_HELP = 0,
	ARG_BOOTLOADER,
	ARG_READ,
	ARG_ID,
	ARG_ERASE,
	ARG_WRITE,
#if _DEBUG
	ARG_DBG,
	ARG_DBG_DATA
#endif
};


struct command_available_t : option {
	const char *help;
	command_available_t(const char *_name, int _has_arg, int *_flag, int _val, const char *_help) {
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
	{ "console",    required_argument, 0, 'c', "Console type [raw, snes, genesis, ...]" },
	{ "area",    required_argument, 0, 'a', "memory area, 0 rom or 1 for sram" },
#if _DEBUG
	{ "debug",    required_argument, 0, 'W', "Debug write cmd..." },
	{ "debug",    required_argument, 0, 'G', "Debug cmd addr/data" },
	{ "debug_addr",    required_argument, 0, 'A', "Debug addr" },
	{ "debug_data",    required_argument, 0, 'D', "Debug data" },
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
	printf("usage: %s\r\n", app_name.c_str());

	for (int i = 0; i < ARRAY_SIZE(commands); i++) {
		if (commands[i].name != NULL)
			printf("\t -%s \t\t %s\r\n", commands[i].name, commands[i].help);
	}
}


void progress_barr(char *label, int step, int total)
{
	//progress width
	const int pwidth = 72;

	// clamp
	step = min(step, total);

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

	if (step == total) {
		printf("\r\n");
	}
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

#ifdef _DEBUG
	int dbg_addr = 0;
	int dbg_data = 0;
#endif


#if 0
	split_rom_16_8("Castlevania - Bloodlines (USA).md", "castleA.8bit.out", "castleB.8bit.out");
	swap_rom("Gradius III (Japan).sfc", "Gradius III (Japan).sfc.sw");
	return 0;
#endif

	console_type = CONSOLE_TYPE_RAW;
	console_memory_area = 0;

	//while ((c = getopt(argc, argv, "bier:w:s:m:d:")) != -1)
	while ((c = getopt_long(argc, argv, optlg, commands, &option_index)) != -1)
		switch (c) {
		case 'c':
			if (stricmp(optarg, "snes") == 0) {
				console_type = CONSOLE_TYPE_SNES;
			}
			else if (stricmp(optarg, "genesis") == 0) {
				console_type = CONSOLE_TYPE_GENESIS;
			}

			break;
		case 'a':
			if (stricmp(optarg, "rom") == 0) {
				console_memory_area = MEMORY_AREA_ROM;
			}
			else if (stricmp(optarg, "sram") == 0) {
				console_memory_area = MEMORY_AREA_SRAM;
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
#ifdef _DEBUG
		case 'W':
			command = ARG_DBG;
			if (optarg) {
				strcpy(filename, optarg);
			}
			break;
		case 'G':
			command = ARG_DBG_DATA;
			break;

		case 'D':
			dbg_data = strtoul(optarg, NULL, 16);
			break;

		case 'A':
			dbg_addr = strtoul(optarg, NULL, 16);
			break;

#endif // DEBUG

		}

	if (command == ARG_HELP) {
		help();
	}
	else {
		handle = usb.connect();
		if (handle != NULL) {
			cmd_query(buf);
			if (buf[0x01] == 0x29) {
				// Display firmware information

			}

			if (console_type == CONSOLE_TYPE_RAW) {
				LINFO("Running in raw mode");
			}
			else {
				LINFO("Running in {0} mode", (console_type == CONSOLE_TYPE_SNES) ? "SNES" : "GENESIS");
				LINFO("Memory area: {0:s}", (console_memory_area == MEMORY_AREA_ROM) ? "ROM" : "SRAM");
			}

			if ((console_type == CONSOLE_TYPE_RAW) || (command != ARG_READ)) {
				// Identify rom
				cmd_read_id(buf);
				rom = romdb_identify(buf);

				if (console_type == CONSOLE_TYPE_RAW) {
					// check if genesis port used
					if (romdb_is_from_genesis_port(buf)) {
						console_type = CONSOLE_TYPE_GENESIS;
					}
				}

				if (console_type == CONSOLE_TYPE_GENESIS) {
					LINFO("Genesis / 16bit mode");
				}
				else {
					LINFO("Snes / 8bit mode");
				}
				if (rom) {
					LINFO("Known chip: {0} - {1}", rom->manufacturer, rom->name);
				}
			}

			switch (command) {
			case ARG_BOOTLOADER:
				cmd_bootloader();
				LINFO("Reboot to bootloader");
				break;

			case ARG_ID:
				// Identify rom
				if (!rom) {
					LWARN("Unknown chip");
				}

				break;
			case ARG_READ:
				if (size == 0 && rom != NULL) {
					size = rom->size;
				}
				if (size > 0) {
					rom_read(filename, size);
					LINFO("Chip read");
				}

				break;
			case ARG_ERASE:
				rom_erase(rom);
				LINFO("Chip erased");
				break;
			case ARG_WRITE:
				if (console_memory_area == MEMORY_AREA_ROM) {
					if (size == 0 && rom != NULL) {
						// set/clamp max filesize
						size = min(file_size(filename), rom->size);
					}

					if (size > 0 && rom != NULL) {
						if (rom_write(filename, size, rom) == 0) {
							LINFO("Chip written");
						}
						else {
							LERROR("Error");
						}
					}
					else {
						LERROR("Unknow memory can't write");
					}
				}
				else {
					size = file_size(filename);
					if (rom_write(filename, size, NULL) == 0) {
						LINFO("Chip written");
					}
					else {
						LERROR("Error");
					}
				}

				break;

#ifdef _DEBUG
			case ARG_DBG:
				rom_debug_write(filename, size);
				break;

			case ARG_DBG_DATA:
				dbg_addr = -1;
				LINFO("send cmd_dbg_data %02x %08x", dbg_data, dbg_addr);
				cmd_dbg_data(dbg_data, dbg_addr);
				break;
			}
#endif
		}
		else {
			LERROR("No device connected");
		}

		usb.close();
	}


	return 0;
}
