/*
 * crc.cpp
 *
 *  Created on: 2011-1-9
 *      Author: zhihaoliu
 */

#include "crc.h"


bool CCRC::bcrc32init = false;
bool CCRC::bcrc16init = false;

unsigned int  CCRC::GetCrc32(std::string s)
{
	return GetCrc32(s.c_str(),s.length());
}


unsigned int CCRC::GetCrc32(const char* p,unsigned int len)
{
	static unsigned int Crc32Table[256];
	if(!bcrc32init)
	{
		int i,j;
		unsigned int Crc;
		for (i = 0; i < 256; i++){
		Crc = i;
		for (j = 0; j < 8; j++){
		  if (Crc & 1)
			Crc = (Crc >> 1) ^ 0xEDB88320;
		  else
			Crc >>= 1;
		}
		Crc32Table[i] = Crc;
		}
		bcrc32init == true;
	}

	//开始计算CRC32校验值
	unsigned int Crc;
	Crc=0xffffffff;
	for(int i=0; i<len; i++)
	{
		Crc = (Crc >> 8) ^ Crc32Table[(Crc & 0xFF) ^ (unsigned char)p[i]];
	}

	Crc ^= 0xFFFFFFFF;
	return Crc;
}


unsigned short CCRC::GetCrc16(std::string s)
{
	return GetCrc16(s.c_str(),s.length());
}


unsigned short CCRC::GetCrc16(const char* p,unsigned int len)
{
	  //生成Crc16的查询表
	unsigned short Crc16Table[256];
	if(!bcrc32init)
	{
		unsigned int i,j;
		unsigned int Crc;
		for (i = 0; i < 256; i++)
		{
			Crc = i;
			for (j = 0; j < 8; j++)
			{
			  if(Crc & 0x1)
				Crc = (Crc >> 1) ^ 0xA001;
			  else
				Crc >>= 1;
			}
			Crc16Table[i] = Crc;
		}
		bcrc32init = true;
	}

	//开始计算CRC16校验值
	unsigned short Crc;
	Crc=0x0000;
	for(int i=0; i<len; i++){
	Crc = (Crc >> 8) ^ Crc16Table[(Crc & 0xFF) ^ p[i]];

	}
	//Crc ^= 0x0000;
	return Crc;
}
