#pragma once
#include <stdint.h>
#include "Command.h"

class cart
{
protected:
	uint32_t cart_options;
public:
	cart(uint32_t op = 0) :cart_options(op) {

	}

	~cart() {

	}


	virtual uint32_t read(uint8_t * out, uint32_t size) {
		return -1;
	}
	virtual uint32_t write(uint8_t * in, uint32_t size) {
		return -1;
	}

	virtual uint32_t read_sram(uint8_t * out, uint32_t size) {
		return -1;
	}

	virtual uint32_t write_sram(uint8_t * out, uint32_t size) {
		return -1;
	}
};

