#include "ccrwrom.h"
#include "romdb.h"

const rom_t romdb[] = {
	{
		"SST",
		"SST39SF040",
		0xBF,
		0xB7,
		512 * 1024,
		FEAT_READ_8_BIT| FEAT_WRITE_8_BIT,
	}
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