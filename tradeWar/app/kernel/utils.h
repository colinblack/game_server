#ifndef _WANGXUAN_UTILS_H_
#define _WANGXUAN_UTILS_H_

#include <string>
#include <arpa/inet.h>

extern volatile int stop;

class Utils{
public:
	static int fdinfo(int fd,char* ipStr,uint32_t& ipVal,uint16_t& port);
	static int daemonStart();
	static int daemonInit(int argc,char** argv);

	//static std::string b2s(const char * b, size_t len, unsigned lf);
	static std::string b2s(const char *ptr, size_t nbytes,int32_t line_len=10);
	//static uint64_t hton64(uint64_t n);
	//static uint64_t ntoh64(uint64_t n);
	
	static unsigned int getMaxMapPageCount();
	static unsigned int getCurSharePageCount();

public:
	static volatile int timerFlag;
};

/*
inline uint64_t Utils::hton64(uint64_t n)
{

#if __BYTE_ORDER == __BIG_ENDIAN
	return n;
#else
	return __bswap_64(n);
#endif 
}

inline uint64_t Utils::ntoh64(uint64_t n)
{
	return hton64(n);
}
*/
#endif
