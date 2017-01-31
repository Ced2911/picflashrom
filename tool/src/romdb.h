#pragma once
#include <inttypes.h>

enum {
	FEAT_READ_8_BIT = 0,
	FEAT_WRITE_8_BIT = 0,
	FEAT_READ_16_BIT = 0x1,
	FEAT_WRITE_16_BIT = 0x2,
	FEAT_COMMAND_16_BIT = 0x4,
	FEAT_FAST_WRITE_AMD = 0x8,
	FEAT_PAGE_WRITE = 0x10,
};

typedef struct {
	const char *manufacturer;
	const char *name;

	uint32_t manufacture_id;
	uint32_t device_id;

	uint32_t size;
	uint32_t feature;
} rom_t;

extern const rom_t romdb[];
extern const uint32_t romdb_size;

const rom_t * romdb_identify(uint32_t manufacture_id, uint32_t device_id);
const rom_t * romdb_identify(uint8_t * buf);
bool romdb_is_from_genesis_port(uint8_t * buf);
