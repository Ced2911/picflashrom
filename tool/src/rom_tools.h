#pragma once
#include <inttypes.h>

uint8_t * snes_remove_header(uint8_t * in, uint32_t in_size);
void snes_swap_to_ss39(uint8_t * in, uint8_t * out, uint32_t in_size);

