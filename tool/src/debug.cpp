#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdarg.h>
#include "debug.h"
#ifdef WIN32
#include <windows.h>
#endif


/**
* Credit: http://stahlworks.com/dev/index.php?tool=csc01
*/
void hexdump(void *pAddressIn, long  lSize)
{
	char szBuf[100];
	long lIndent = 1;
	long lOutLen, lIndex, lIndex2, lOutLen2;
	long lRelPos;
	struct { char *pData; unsigned long lSize; } buf;
	unsigned char *pTmp, ucTmp;
	unsigned char *pAddress = (unsigned char *)pAddressIn;

	buf.pData = (char *)pAddress;
	buf.lSize = lSize;

	while (buf.lSize > 0)
	{
		pTmp = (unsigned char *)buf.pData;
		lOutLen = (int)buf.lSize;
		if (lOutLen > 16)
			lOutLen = 16;

		// create a 64-character formatted output line:
		sprintf(szBuf, " >                            "
			"                      "
			"    %08lX", pTmp - pAddress);
		lOutLen2 = lOutLen;

		for (lIndex = 1 + lIndent, lIndex2 = 53 - 15 + lIndent, lRelPos = 0;
			lOutLen2;
			lOutLen2--, lIndex += 2, lIndex2++
			)
		{
			ucTmp = *pTmp++;

			sprintf(szBuf + lIndex, "%02X ", (unsigned short)ucTmp);
			if (!isprint(ucTmp))  ucTmp = '.'; // nonprintable char
			szBuf[lIndex2] = ucTmp;

			if (!(++lRelPos & 3))     // extra blank after 4 bytes
			{
				lIndex++; szBuf[lIndex + 2] = ' ';
			}
		}

		if (!(lRelPos & 3)) lIndex--;

		szBuf[lIndex] = '<';
		szBuf[lIndex + 1] = ' ';

		LDEBUG("{0}", szBuf);

		buf.pData += lOutLen;
		buf.lSize -= lOutLen;
	}
}

int dbg_compare_buf(uint8_t * in, uint8_t * out, int size) {
	for (int i = 0; i < size; i++) {
		if (in[i] != out[i]) {

			LERROR("error at %08x %d", i, i);

			LERROR("read");
			hexdump(&in[i], 0x40);

			LERROR("source");
			hexdump(&out[i], 0x40);
			return -1;
		}
	}

	LERROR("test ok");
	return 0;
}

Logger * Logger::instance = NULL;

Logger::Logger() {
	_logger = spdlog::stdout_color_mt("logger");
	_logger->set_level(spdlog::level::debug);
	spdlog::set_pattern("%v");
}

