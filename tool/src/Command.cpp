#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#ifdef WIN32
#include <Windows.h>
#endif
#include "Command.h"
#include "usb.h"
#include "debug.h"

using namespace std;

void cmd_bootloader() {
	usb.cmd(TO_BOOLOADER);
}


uint32_t cmd_read_rom_16(uint8_t * out, uint32_t start, uint32_t size) {
	return cmd_read_rom_16(ROM_READ_16, out, start, size);
}

uint32_t cmd_read_rom_16(uint8_t cmd, uint8_t * out, uint32_t start, uint32_t size) {
	uint8_t * p = out;
	cmd_position.reset();

	LTRACE("cmd_read_rom_16");

	usb.cmd(cmd, start >> 1, (start + size) >> 1);

	for (uint32_t i = 0; i < size; i += USB_PACKET_SIZE, p += USB_PACKET_SIZE) {
		if (usb.read(p, sizeof(usb_packet_w_t)) == 0) {
			// Error !
			LERROR("Usb error at {0}", i);
			return -1;
		}
#ifdef _DEBUG
		if (i == 0 && start == 0) {
			hexdump(p, USB_PACKET_SIZE);
		}
#endif

		cmd_position.add(USB_PACKET_SIZE);
	}

	return 0;
}


uint32_t cmd_read_rom(uint8_t cmd, uint8_t * out, uint32_t start, uint32_t size) {
	uint8_t * p = out;
	cmd_position.reset();

	usb.cmd(cmd, start, start + size);

	for (uint32_t i = 0; i < size; i += USB_PACKET_SIZE, p += USB_PACKET_SIZE) {
		if (usb.read(p, sizeof(usb_packet_w_t)) == 0) {
			// Error !
			LERROR("Usb error at {0}", i);
			return -1;
		}
#ifdef _DEBUG
		if (i == 0 && start == 0) {
			hexdump(p, USB_PACKET_SIZE);
		}
#endif

		cmd_position.add(USB_PACKET_SIZE);
	}

	return 0;
}

uint32_t cmd_read_rom(uint8_t * out, uint32_t start, uint32_t size) {
	return cmd_read_rom(ROM_READ_8, out, start, size);
}


uint32_t cmd_write_rom_16(uint8_t cmd, uint32_t start, uint8_t * in, uint32_t size) {
	uint8_t * p = in;
	usb_packet_w_t read = { 0 };
	uint32_t rem = size;
	uint32_t w_address = 0;
	cmd_position.reset();

	LINFO("cmd_write_rom_16");
	usb.cmd(cmd, start >> 1, (start + size) >> 1);
	//usb.cmd(ROM_WRITE_8_16, 0, size);

	do {
		uint32_t w_size = min(rem, USB_PACKET_SIZE);
		if (usb.write(p, sizeof(usb_packet_w_t)) == 0) {
			LERROR("Usb error at  {0:x}", w_address);
			return -1;
		}

		if (usb.read(read, sizeof(usb_packet_w_t)) == 0) {
			// Error !
			LERROR("Usb error at  {0:x}", w_address);
			return -1;
		}
		if (read.w_command != 0) {
			LERROR("prog error {0:x} at {1:x}", read.w_command, w_address);
			return w_address;
		}

		rem -= w_size;
		w_address += w_size;
		p += w_size;
		cmd_position.add(w_size);

	} while (w_address < size);

	return 0;
}


uint32_t cmd_write_rom(uint8_t cmd, uint32_t start, uint8_t * in, uint32_t size) {
	uint8_t * p = in;
	usb_packet_w_t read = { 0 };
	uint32_t rem = size;
	uint32_t w_address = 0;
	cmd_position.reset();

	usb.cmd(cmd, start, start + size);
	//usb.cmd(ROM_WRITE_8_16, 0, size);

	do {
		uint32_t w_size = min(rem, USB_PACKET_SIZE);
		if (usb.write(p, sizeof(usb_packet_w_t)) == 0) {
			LERROR("Usb error");
			return -1;
		}

		if (usb.read(read, sizeof(usb_packet_w_t)) == 0) {
			// Error !
			LERROR("Usb error");
			return -1;
		}
		if (read.w_command != 0) {
			LERROR("prog error {0:x}", read.w_command);
			return w_address;
		}

		rem -= w_size;
		w_address += w_size;
		p += w_size;
		cmd_position.add(w_size);

	} while (w_address < size);

	return 0;
}

uint32_t cmd_write_rom(uint8_t cmd, uint8_t * in, uint32_t size) {	
	return cmd_write_rom(cmd, 0, in, size);
}

uint32_t cmd_write_rom(uint8_t * in, uint32_t size) {
	return cmd_write_rom(ROM_WRITE, in, size);
}

uint32_t cmd_write_rom_8_16(uint8_t * in, uint32_t size) {
	return cmd_write_rom(ROM_WRITE_8_16, in, size);
}

uint32_t cmd_write_rom_amd_unlocked(uint8_t * in, uint32_t size) {
	return cmd_write_rom(ROM_WRITE_UNLOCKED_AMD, in, size);
}

uint32_t cmd_write_rom_page(uint8_t * in, uint32_t size) {
	const uint32_t page_size = 0x100;
	uint8_t * p = in;
	usb_packet_w_t read = { 0 };
	uint32_t rem = size;
	uint32_t w_address = 0;
	cmd_position.reset();

	usb.cmd(ROM_WRITE_PAGE_8_16, 0, size);

	do {
		uint32_t w_size = min(rem, USB_PACKET_SIZE);
		if (usb.write(p, sizeof(usb_packet_w_t)) == 0) {
			LERROR("Usb error");
			return -1;
		}

		if (usb.read(read, sizeof(usb_packet_w_t)) == 0) {
			// Error !
			LERROR("Usb error");
			return -1;
		}

		//hexdump(read.bytes, USB_PACKET_SIZE);

		if (read.w_command != 0) {
			LERROR("prog error {0:x}", read.w_command);
			return w_address;
		}

		rem -= w_size;
		w_address += w_size;
		p += w_size;
		cmd_position.add(w_size);

	} while (w_address < size);

	return 0;
}

void cmd_read_id(uint8_t * out) {
	usb.cmd(PROM_ID);
	usb.read(out, sizeof(usb_packet_w_t));

	hexdump(out, USB_PACKET_SIZE);
}

void cmd_erase() {
	usb_packet_w_t packet = { 0 };
	usb.cmd(ROM_ERASE);
	usb.read(packet, sizeof(usb_packet_w_t));
}

void cmd_erase_8_16() {
	usb_packet_w_t packet = { 0 };
	usb.cmd(ROM_ERASE_8_16);
	usb.read(packet, sizeof(usb_packet_w_t));
}

void cmd_erase(uint8_t cmd) {
	usb_packet_w_t packet = { 0 };
	usb.cmd(cmd);
	usb.read(packet, sizeof(usb_packet_w_t));
}

void cmd_query(uint8_t * in) {
	usb.cmd(QUERY_DEVICE);
	usb.read(in, sizeof(usb_packet_w_t));
}

void cmd_dbg_data(uint8_t data, uint32_t addr) {
	usb.cmd(CMD_DBG, data, addr);
}


atomic_value<uint32_t> cmd_position;