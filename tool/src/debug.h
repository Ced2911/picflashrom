#pragma once

#include <memory>
#include "spdlog\spdlog.h"

#define L_DEBUG_ON
#define L_ERROR_ON
#define L_TRACE_ON
#define L_WARN_ON
#define L_INFO_ON

void hexdump(void *pAddressIn, long  lSize);
int dbg_compare_buf(uint8_t * in, uint8_t * out, int size);
extern int verbose_flag ;

class Logger {
private:
	static Logger * instance;
	std::shared_ptr<spdlog::logger> _logger;
	Logger();
public:
	static std::shared_ptr<spdlog::logger> getLoger() {
		if (instance == NULL) {
			instance = new Logger();
		}
		return instance->_logger;
	}
};

#ifdef L_DEBUG_ON
#define LDEBUG(...) Logger::getLoger()->debug(__VA_ARGS__)
#else
#define LDEBUG(logger, ...)
#endif

#ifdef L_ERROR_ON
#define LERROR(...) Logger::getLoger()->error(__VA_ARGS__)
#else
#define LERROR(logger, ...)
#endif

#ifdef L_TRACE_ON
#define LTRACE(...) Logger::getLoger()->debug(__VA_ARGS__)
#else
#define LTRACE(logger, ...)
#endif

#ifdef L_WARN_ON
#define LWARN(...) Logger::getLoger()->warn(__VA_ARGS__)
#else
#define LWARN(logger, ...)
#endif



#ifdef L_INFO_ON
#define LINFO(...) Logger::getLoger()->info(__VA_ARGS__)
#else
#define LINFO(logger, ...)
#endif
