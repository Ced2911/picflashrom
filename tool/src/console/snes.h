#pragma once
#include "console/cart.h"
class snes :
	public cart
{
protected:
	bool is_lorom;
	bool isLoRom();
	bool isHiRom();
	uint32_t readLoRom(uint8_t * out, uint32_t size);
	uint32_t readHiRom(uint8_t * out, uint32_t size);
public:
	virtual uint32_t identify();
	virtual uint32_t read(uint8_t * out, uint32_t size);
	virtual uint32_t read_sram(uint8_t * out, uint32_t size);
	virtual uint32_t write_sram(uint8_t * in, uint32_t size);
};

