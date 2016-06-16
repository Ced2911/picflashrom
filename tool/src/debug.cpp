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

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int verbose_flag = VERBOSE_LEVEL;

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

		printf("%s\n", szBuf);

		buf.pData += lOutLen;
		buf.lSize -= lOutLen;
	}
}

#ifndef WIN32
#define outcolor(color) \
{	\
	char buffer[256];	\
	va_list args;	\
	va_start(args, str);		\
	fprintf(stdout,color);	\
	vsprintf(buffer, str, args);	\
	fprintf(stdout, buffer);	\
	fprintf(stdout,ANSI_COLOR_RESET); \
	va_end(args);	\
}
#else
#define outcolor(color) \
{	\
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); CONSOLE_SCREEN_BUFFER_INFO consoleInfo; WORD saved_attributes; \
	char buffer[256];	\
	va_list args;	\
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo); saved_attributes = consoleInfo.wAttributes; \
	SetConsoleTextAttribute(hConsole, color); \
	va_start(args, str);		\
	vsprintf(buffer, str, args);	\
	fprintf(stdout, buffer);	\
	va_end(args);	\
	SetConsoleTextAttribute(hConsole, saved_attributes); \
}

#endif

namespace output {
	void error(const char * str, ...) {
		outcolor(FOREGROUND_RED | FOREGROUND_INTENSITY)
	}

	void success(const char * str, ...) {
		outcolor(FOREGROUND_BLUE | FOREGROUND_INTENSITY)
	}

	void warning(const char * str, ...) {
		if (verbose_flag)
			outcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
	}

	void debug(const char * str, ...) {
		if (verbose_flag)
			outcolor(FOREGROUND_GREEN | FOREGROUND_INTENSITY)
	}

	void info(const char * str, ...) {
		if (verbose_flag)
			outcolor(FOREGROUND_BLUE| FOREGROUND_INTENSITY | FOREGROUND_GREEN)
	}

	void print(const char * str, ...) {
		char buffer[256];	
		va_list args;	
		va_start(args, str);		
		vsprintf(buffer, str, args);	
		fprintf(stdout, buffer);	
		va_end(args);	
	}

	void reset() {
		//puts(ANSI_COLOR_RESET);
	}
}


int dbg_compare_buf(uint8_t * in, uint8_t * out, int size) {
	for (int i = 0; i < size; i++) {
		if (in[i] != out[i]) {

			output::error("error at %08x %d\r\n", i, i);

			output::error("read\r\n");
			hexdump(&in[i], 0x40);

			output::error("source\r\n");
			hexdump(&out[i], 0x40);
			return -1;
		}
	}

	output::error("test ok\r\n");
	return 0;
}