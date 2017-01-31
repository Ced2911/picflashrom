#include <stdio.h>
#include <stdlib.h>
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



static uint32_t snes_read(uint8_t * data, uint32_t size) {
	snes reader;
	return reader.read(data, size);
}

static uint32_t snes_read_sram(uint8_t * data, uint32_t size) {
	snes reader;
	size = MIN(size, 0x8000);
	// LOROM
	//uint32_t lorom_sram_start = 0x808000;
	//return cmd_read_rom(data, lorom_sram_start, size);
	//return reader.read(data, size);
	return reader.read_sram(data, size);
}

static uint32_t snes_write_sram(uint8_t * data, uint32_t size) {
	snes reader;
	return reader.write_sram(data, size);
}

static uint32_t genesis_write_sram(uint8_t * data, uint32_t size) {
	return cmd_write_rom(GENESIS_SRAM_WRITE, 0x200000, data, size);
}

static uint32_t _cmd_write_rom(const rom_t * rom, uint8_t * in, uint32_t size) {
	if (console_type == CONSOLE_TYPE_RAW) {
		if (rom && rom->feature & FEAT_FAST_WRITE_AMD) {
			LDEBUG("cmd_write_rom_amd_unlocked");
			return cmd_write_rom_amd_unlocked(in, size);
		}
		else if (rom && rom->feature & FEAT_PAGE_WRITE) {
			LDEBUG("cmd_write_rom_page");
			return cmd_write_rom_page(in, size);
		}
		else if (rom && rom->feature & FEAT_COMMAND_16_BIT) {
			LDEBUG("cmd_write_rom_8_16");
			return cmd_write_rom_8_16(in, size);
		}
		else {
			LDEBUG("cmd_write_rom");
			return cmd_write_rom(in, size);
		}
	}
	else if (console_type == CONSOLE_TYPE_SNES){
		LDEBUG("snes_write_sram");
		return snes_write_sram(in, size);
	}
	else if (console_type == CONSOLE_TYPE_GENESIS) {
		if (console_memory_area == MEMORY_AREA_SRAM) {
			LDEBUG("cmd_write_rom GENESIS_SRAM_WRITE");
			return cmd_write_rom(GENESIS_SRAM_WRITE, 0x780000, in, size);
		}
		else {
			LDEBUG("cmd_write_rom_16 GENESIS_ROM_WRITE");
			return cmd_write_rom_16(GENESIS_ROM_WRITE, 0, in, size);
		}
	}

	// Error
	return -1;
}


static uint32_t _cmd_read_rom(uint8_t * in, uint32_t size) {
	if (console_type == CONSOLE_TYPE_SNES) {
		if (console_memory_area == MEMORY_AREA_SRAM) {
			return snes_read_sram(in, size);
		} else {
			return snes_read(in, size);
		}
	}
	else if (console_type == CONSOLE_TYPE_GENESIS) {
		if (console_memory_area == MEMORY_AREA_SRAM) {
			LDEBUG("cmd_read_rom_16 GENESIS_SRAM_READ");
			//return cmd_read_rom_16(GENESIS_SRAM_READ, in, 0x780000>>1, size);
			return cmd_read_rom_16(GENESIS_SRAM_READ, in, 0x780000, size);
		}
		else {
			LDEBUG("cmd_read_rom_16 GENESIS_ROM_READ");
			return cmd_read_rom_16(GENESIS_ROM_READ, in, 0x0, size);
		}
	} else {
		LDEBUG("cmd_read_rom");
		return cmd_read_rom(in, 0, size);
	}
}

void rom_read(const char * filename, uint32_t size) {
	uint8_t * data = new uint8_t[size];
	memset(data, 0, size);
	FILE * fd = fopen(filename, "wb");
	if (fd) {
		// run in thread
		LINFO("Reading to {0}", filename);
		cclock elapsed;
		std::chrono::milliseconds span(100);
		std::future<uint32_t> read = std::async(_cmd_read_rom, data, size);
		float percent = 0;

		LINFO(""); // empty line

		while (read.wait_for(span) == std::future_status::timeout) {
			if (cmd_position.get() < size) {
				progress_barr("Reading: ", cmd_position.get(), size);
			}
		}

		// Finished
		if (read.get() == 0) {
			// 100%
			progress_barr("Reading: ", size, size);

			LINFO("Time elapsed {0:f}", elapsed.elapsed());

			fwrite(data, size, 1, fd);
		}
		else {
			LERROR("Error reading eeprom to {0}.", filename);
		}
	}
	else {
		LERROR("Can not open {0} for writing.", filename);
	}
	fclose(fd);
	//delete[] data;
}


static int probe_size(const rom_t * rom, uint32_t size) {
	if (console_type == CONSOLE_TYPE_SNES) {
		// to do ...
		return 0x2000;
	} else {
		return size;
	}
}

int rom_write(const char * filename, uint32_t size, const rom_t * rom) {
	uint32_t status = 0;
	size = probe_size(rom, size);
	uint8_t * data = new uint8_t[size];
	FILE * fd = fopen(filename, "rb");
	LINFO("sram: write {0}", size);
	if (fd) {
		fread(data, size, 1, fd);

		// Erase the chip first
		//cmd_erase();


		// run in thread
		cclock elapsed;
		std::chrono::milliseconds span(100);
		std::future<uint32_t> write = std::async(_cmd_write_rom, rom, data, size);

		//std::future<uint32_t> write = std::async(snes_write_sram, data, size);
		//std::future<uint32_t> write = std::async(genesis_write_sram, data, size);
		float percent = 0;
		LINFO("Writing {0}", filename);

		LINFO(""); // empty line
		while (write.wait_for(span) == std::future_status::timeout) {
			progress_barr("Writing: ", cmd_position.get(), size);
		}

		status = write.get();
		// Finished
		if (status == 0) {
			// 100%
			progress_barr("Writing: ", size, size);

			LINFO("Time elapsed {0}", elapsed.elapsed());
		}
		else {
			LINFO("Error writing at 0x{0:x}", status);
		}
		fclose(fd);
		return 0;
	}
	else {
		LERROR("Can not open {0} for reading.", filename);
	}
	return -1;
	//delete[] data;
}

int rom_erase(const rom_t * rom) {
	if (console_type == CONSOLE_TYPE_GENESIS) {
		LDEBUG("cmd_erase GENESIS_ROM_ERASE");
		cmd_erase(GENESIS_ROM_ERASE);
	}
	else {
		if (rom != NULL && (rom->feature &FEAT_COMMAND_16_BIT)) {
			LDEBUG("cmd_erase_8_16.");
			cmd_erase_8_16();
		}
		else {
			LDEBUG("cmd_erase.");
			cmd_erase();
		}
	}
	return 0;
}