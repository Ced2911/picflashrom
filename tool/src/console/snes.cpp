#include "snes.h"
#include "Command.h"
#include "usb.h"
#include "debug.h"


bool snes::isLoRom() {
	return is_lorom;
}
bool snes::isHiRom() {
	return is_lorom;
}
uint32_t snes::identify() {
	char ROM_NAME[USB_PACKET_SIZE];
	uint8_t buf[USB_PACKET_SIZE * 2];
	uint8_t * low = buf;
	uint8_t * high = buf + USB_PACKET_SIZE;
	// Read 2 packet, if packet are same => lorom detected
	usb.cmd(SNES_ROM_READ, 0, USB_PACKET_SIZE);
	if (usb.read(low, sizeof(usb_packet_w_t)) == 0) {
		return -1;
	}
	// Read lorom mirrored data 
	usb.cmd(SNES_ROM_READ, 0x8000, USB_PACKET_SIZE + 0x8000);
	if (usb.read(high, sizeof(usb_packet_w_t)) == 0) {
		return -1;
	}

	is_lorom = (memcmp(low, high, USB_PACKET_SIZE) == 0);

	//is_lorom = false;

	if (is_lorom) {
		LINFO("lorom detected");
	}
	else {
		LINFO("hirom detected");
	}
	if (is_lorom) {
		usb.cmd(SNES_ROM_READ, 0x7fc0, USB_PACKET_SIZE+ 0x7fc0);
		if (usb.read((uint8_t*)ROM_NAME, sizeof(usb_packet_w_t)) == 0) {
			return -1;
		}
	}
	else {
		usb.cmd(SNES_ROM_READ, 0xffc0, USB_PACKET_SIZE + 0x7fc0);
		if (usb.read((uint8_t*)ROM_NAME, sizeof(usb_packet_w_t)) == 0) {
			return -1;
		}
	}
	ROM_NAME[20] = NULL;
	LINFO("Rom name: {0:s}", ROM_NAME);

	return 0;
}

uint32_t snes::readLoRom(uint8_t * out, uint32_t size) {
	const int banklen = 0x8000;
	int loop = size / banklen;
	cmd_position.reset();
	uint32_t offset = 0;


	for (int i = 0; i < loop; i++) {
		uint32_t start = (i * 2 * banklen);
		uint8_t * p = &out[offset];

		usb.cmd(SNES_ROM_READ, start, start + banklen);

		for (uint32_t i = 0; i < banklen; i += USB_PACKET_SIZE, p += USB_PACKET_SIZE) {
			if (usb.read(p, sizeof(usb_packet_w_t)) == 0) {
				// Error !
				LERROR("Usb error");
				return -1;
			}

			cmd_position.add(USB_PACKET_SIZE);
		}

		offset += banklen;
	}

	return 0;
}

uint32_t snes::readHiRom(uint8_t * out, uint32_t size) {
	uint8_t * p = out;
	cmd_position.reset();

	usb.cmd(SNES_ROM_READ, 0, size);

	for (uint32_t i = 0; i < size; i += USB_PACKET_SIZE, p += USB_PACKET_SIZE) {
		if (usb.read(p, sizeof(usb_packet_w_t)) == 0) {
			// Error !
			LERROR("Usb error");
		}

		cmd_position.add(USB_PACKET_SIZE);
	}

	return 0;
}

uint32_t snes::read(uint8_t * out, uint32_t size) {
	identify();
	if (isLoRom()) {
		return readLoRom(out, size);
	} else {
		return readHiRom(out, size);
	}
}

uint32_t snes::read_sram(uint8_t * out, uint32_t size) {

	uint32_t start = 0x700000;
	const int banklen = size;
	uint8_t * p = out;

	identify();

	if (!isLoRom()) {
		start = 0x206000;
	}
#if 0
	cmd_position.reset();

	usb.cmd(SNES_SRAM_READ, start, start + banklen);

	LINFO("read sram at {0:x}", start);

	for (uint32_t i = 0; i < size; i += USB_PACKET_SIZE, p += USB_PACKET_SIZE) {
		if (usb.read(p, sizeof(usb_packet_w_t)) == 0) {
			// Error !
			LERROR("Usb error");
			return -1;
		}
#ifdef _DEBUG
		if (i == 0) {
			hexdump(p, USB_PACKET_SIZE);
		}
#endif

		cmd_position.add(USB_PACKET_SIZE);
	}
#else
	cmd_read_rom(SNES_SRAM_READ, out, start, banklen);

#endif


	return 0;
}

uint32_t snes::write_sram(uint8_t * in, uint32_t size) {
	uint32_t start = 0x700000;
	const int banklen = size;
	uint8_t * p = in;

	if (true || !isLoRom()) {
		start = 0x206000;
	}

	start = 0x206000;

	cmd_position.reset();

	usb_packet_w_t read = { 0 };
	uint32_t rem = size;
	uint32_t w_address = 0;
	cmd_position.reset();

	usb.cmd(SNES_SRAM_WRITE, start, start+size);
	//usb.cmd(ROM_WRITE_8_16, 0, size);

	do {
		uint32_t w_size = MIN(rem, USB_PACKET_SIZE);
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