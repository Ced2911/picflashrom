#pragma once

#ifdef _DEBUG
#define VERBOSE_LEVEL	0xF
#else
#define VERBOSE_LEVEL	0
#endif


void hexdump(void *pAddressIn, long  lSize);
int dbg_compare_buf(uint8_t * in, uint8_t * out, int size);
extern int verbose_flag ;