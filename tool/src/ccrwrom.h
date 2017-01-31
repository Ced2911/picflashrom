#pragma once
#include <inttypes.h>
#include "debug.h"
#include "romdb.h"

#define USB_READ_TIMEOUT	5000

#define USB_VID 0x04D8
#define USB_PID 0x003E
#define USB_PACKET_SIZE 0x40

#define MAX_STR 255


#define DBGPrintf wprintf

#define ARRAY_SIZE(array) \
    (sizeof(array) / sizeof(array[0]))

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

enum {
	CONSOLE_TYPE_RAW,
	CONSOLE_TYPE_SNES,
	CONSOLE_TYPE_GENESIS
};

enum {
	MEMORY_AREA_ROM,
	MEMORY_AREA_SRAM
};

extern int console_type;
extern int console_memory_area;
void progress_barr(char *label, int step, int total);
uint32_t file_size(const char * filename);

// rom.cpp - threaded func
void rom_read(const char * filename, uint32_t size);
int rom_write(const char * filename, uint32_t size, const rom_t * rom = NULL);
int rom_erase(const rom_t * rom = NULL);

#include <ctime>
class cclock {
protected:
	clock_t _start;

public:
	cclock() {
		start();
	}

	void start() {
		_start = clock();
	}

	double elapsed() {
		return double(std::difftime(clock(), _start));
	}
};