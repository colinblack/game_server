/*
 * crc_16.h
 *
 *  Created on: 2013-8-23
 *      Author: Administrator
 */

#ifndef CRC_16_H_
#define CRC_16_H_
#include <string>

using namespace std;

class CrcUtil
{
public:
	static CrcUtil* getInstance()
	{
		static CrcUtil crc;
		return &crc;
	}
	~CrcUtil()
	{
	}
public:
	unsigned short update(const char* arg1, int arg1Len);
	bool enCrypt(char* p, unsigned length, unsigned key);
	bool deCrypt(char* p, unsigned length, unsigned key);
private:
	CrcUtil();
	void init_table();
	unsigned crcBitReflect(unsigned arg1, unsigned arg2);
};

#endif /* CRC_16_H_ */
