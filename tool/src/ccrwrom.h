#pragma once
#include <inttypes.h>

#define USB_READ_TIMEOUT	5000

#define USB_VID 0x04D8
#define USB_PID 0x003E
#define USB_PACKET_SIZE 0x40

#define MAX_STR 255


#define DBGPrintf wprintf

#define ARRAY_SIZE(array) \
    (sizeof(array) / sizeof(array[0]))





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