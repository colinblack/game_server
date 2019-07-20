#ifndef _WANGXUAN_UTILS_H_
#define _WANGXUAN_UTILS_H_

#include <string>
#include <list>
#include <vector>
#include <arpa/inet.h>

extern volatile int stop;

class Utils {
public:
	static int fdinfo(int fd, char* ipStr, uint32_t& ipVal, uint16_t& port);
	static int daemonStart();
	static int daemonInit(int argc, char** argv);
	static std::string b2s(const char *ptr, size_t nbytes, int32_t line_len = 10);
	static unsigned int getMaxMapPageCount();
	static unsigned int getCurSharePageCount();
	static bool Parse2DFloat(const std::string& value, const std::string& split1, const std::string& split2, std::list< std::vector<float> >& data);
public:
	static volatile int timerFlag;
};

#endif
