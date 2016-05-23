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


uint32_t cmd_read_rom(uint8_t * out, uint32_t size) {
	uint8_t * p = out;

	cclock elapsed;
	usb.cmd(PROM_BULK_READ, 0, size);

	for (uint32_t i = 0; i < size; i += USB_PACKET_SIZE, p += USB_PACKET_SIZE) {
		if (usb.read(p, sizeof(usb_packet_w_t)) == 0) {
			// Error !
			puts("Usb error\r\n");
		}
		if (i == 0) {
			hexdump(p, USB_PACKET_SIZE);
		}
	}

	cout << " Time elapsed: " << elapsed.elapsed() << " ms" << endl;
	return 0;
}

uint32_t cmd_write_rom(uint8_t * in, uint32_t size) {
	uint8_t * p = in;
	usb_packet_w_t read = { 0 };
	uint32_t rem = size;
	uint32_t w_address = 0;

	cclock elapsed;

	usb.cmd(JEDEC_WRITE, 0, size);

	do {
		uint32_t w_size = min(rem, USB_PACKET_SIZE);
		if (usb.write(p, sizeof(usb_packet_w_t)) == 0) {
			return -1;
		}

		if (usb.read(read, sizeof(usb_packet_w_t)) == 0) {
			// Error !
			puts("Usb error\r\n");
		}

		rem -= w_size;
		w_address += w_size;
		p += w_size;
	} while (w_address < size);


	cout << " Time elapsed: " << elapsed.elapsed() << " ms" << endl;

	return 0;
}

void cmd_read_id(uint8_t * out) {
	usb_packet_w_t packet = { 0 };
	usb.cmd(PROM_ID);
	usb.read(packet, sizeof(usb_packet_w_t));

	hexdump(packet.bytes, USB_PACKET_SIZE);

	out[0] = packet.bytes[0];
	out[1] = packet.bytes[1];
}

void cmd_erase() {
	usb_packet_w_t packet = { 0 };
	usb.cmd(JEDEC_ERASE);

	usb.read(packet, sizeof(usb_packet_w_t));

	if (packet.command == JEDEC_ERASE) {
		// OK !
	}
}

void cmd_query(uint8_t * in) {
	usb.cmd(QUERY_DEVICE);
	usb.read(in, sizeof(usb_packet_w_t));
}