#include "ccrwrom.h"
#include "romdb.h"

const rom_t romdb[] = {
	{
		"SST",
		"SST39SF040",
		0xBF,
		0xB7,
		512 * 1024,
		FEAT_READ_8_BIT | FEAT_WRITE_8_BIT,
	}, {
		"MXIC",
		"MX29LV320",
		0xC2,
		0xA8,
		4 * 1024 * 1024,
		FEAT_READ_8_BIT | FEAT_WRITE_8_BIT | FEAT_COMMAND_16_BIT,
	},{
		"MXIC",
		"MX29LV160",
		0xC2,
		0x49,
		2 * 1024 * 1024,
		FEAT_READ_8_BIT | FEAT_WRITE_8_BIT | FEAT_COMMAND_16_BIT,
	},{
		"AMD",
		"AM29LV160D",
		0x01,
		0x49,
		2 * 1024 * 1024,
		FEAT_READ_8_BIT | FEAT_WRITE_8_BIT | FEAT_COMMAND_16_BIT | FEAT_FAST_WRITE_AMD,
	},{
		"MXIC",
		"MX29LV640",
		0xC2,
		0xC9,
		8 * 1024 * 1024,
		FEAT_READ_8_BIT | FEAT_WRITE_8_BIT | FEAT_COMMAND_16_BIT,
	},{
		"MXIC",
		"MX29L3211",
		0xC2,
		0xF9,
		4 * 1024 * 1024,
		FEAT_READ_8_BIT | FEAT_WRITE_8_BIT | FEAT_COMMAND_16_BIT | FEAT_PAGE_WRITE,
		//FEAT_READ_8_BIT | FEAT_WRITE_8_BIT | FEAT_COMMAND_16_BIT,
	},
};


const uint32_t romdb_size = ARRAY_SIZE(romdb);

const rom_t * romdb_identify(uint32_t manufacture_id, uint32_t device_id) {
	for (uint32_t i = 0; i < romdb_size; i++) {
		if (romdb[i].manufacture_id == manufacture_id && romdb[i].device_id == device_id) {
			return &romdb[i];
		}
	}

	return NULL;
}

const rom_t * romdb_identify(uint8_t * buf) {
	const rom_t * r = NULL;

	r = romdb_identify(buf[0], buf[1]);
	if (r == NULL) {
		// try 16 bit command ?
		r = romdb_identify(buf[0x8], buf[0x9]);
	}
	if (r == NULL) {
		// try genesis port ?
		r = romdb_identify(buf[0x11], buf[0x13]);
	}
	if (r == NULL) {
		// snes lorom 8 bit
		r = romdb_identify(buf[0x18], buf[0x19]);
	}
	if (r == NULL) {
		// snes lorom 8/16 bit
		r = romdb_identify(buf[0x20], buf[0x21]);
	}
	return r;
}


bool romdb_is_from_genesis_port(uint8_t * buf) {
	return romdb_identify(buf[0x21], buf[0x23]) != NULL;
}