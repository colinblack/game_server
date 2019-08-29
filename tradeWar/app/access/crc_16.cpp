/*
 * crc_16.cpp
 *
 *  Created on: 2013-8-23
 *      Author: Administrator
 */
#include "crc_16.h"
#include <stdint.h>
#include <string>

unsigned int POLYNOMIAL = 4129;
int crc_arr[] = { 0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFC, 0xFFFFFFF8, 0xFFFFFFF0, 0xFFFFFFE0, 0xFFFFFFC0, 0xFFFFFF80, 0xFFFFFF00, 0xFFFFFE00, 0xFFFFFC00, 0xFFFFF800, 0xFFFFF000, 0xFFFFE000, 0xFFFFC000, 0xFFFF8000 };
int crc_table[256];

CrcUtil::CrcUtil()
{
	init_table();
}

bool CrcUtil::enCrypt(char* p, unsigned length, unsigned key)
{
	for (int i = 0; i < length; i++)
	{
		p[i] ^= ((char*) &key)[i % 4];
	}
	return true;
}

bool CrcUtil::deCrypt(char* p, unsigned length, unsigned key)
{
	for (int i = 0; i < length; i++)
	{
		p[i] ^= ((char*) &key)[i % 4];
	}
	return true;
}

unsigned CrcUtil::crcBitReflect(unsigned arg1, unsigned arg2)
{
	int local3 = 0;
	int local4 = 0;
	int local5 = 0;
	arg2--;
	int local6 = 0;

	while (local6 <= arg2)
	{
		local5 = arg2 - local6;
		if ((arg1 & 1))
		{
			local3 = (local3 | ((1 << local5) & crc_arr[local5]));
		}
		arg1 = ((arg1 >> 1) & 0x7FFFFFFF);
		local6++;
	}
	return local3;
}

unsigned short CrcUtil::update(const char* arg1, int arg1Len)
{
	int local4 = 0;
	int local5 = 0;
	int arg3 = arg1Len;
	int local6 = 0;

	while (local6 < arg3)
	{
		local5 = ((crcBitReflect(arg1[local6], 8) & 0xFF) ^ ((local4 >> 8) & 0xFFFFFF));
		local5 = (local5 & 0xFF);
		local4 = (crc_table[local5] ^ ((local4 << 8) & 0xFFFFFF00));
		local6++;
	}
	unsigned xxx = ((crcBitReflect(local4, 16) ^ 0) & 0xFFFF);
	return xxx;
}

void CrcUtil::init_table()
{
	int local1 = 0;
	int local3 = 0;
	int local4 = 0;
	while (local3 < 0x0100)
	{
		local1 = ((local3 << 8) & 0xFFFFFF00);
		local4 = 0;
		while (local4 < 8)
		{
			local1 = (((local1 & 0x8000)) ? (((local1 << 1) & 0xFFFFFFFE) ^ POLYNOMIAL) : ((local1 << 1) & 0xFFFFFFFE));
			local4++;
		}
		crc_table[local3] = local1;
		local3++;
	}
}

