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
	~CrcUtil(){}
public:
    unsigned short update(const char* arg1,int arg1Len);
    bool enCrypt(char* p,unsigned length,unsigned key);
    bool deCrypt(char* p,unsigned length,unsigned key);
private:
	CrcUtil();
	void init_table();
	unsigned crcBitReflect(unsigned arg1, unsigned arg2);
};


/****************************************/
namespace Crypt
{
	//Base64
	bool Base64Encode(string &result, const string &text, const char *altChars = NULL);
	bool Base64EncodeTrim(string &result, const string &text, const char *altChars = NULL);
	bool Base64Decode(string &result, const string &text, const char *altChars = NULL);
	bool Base64UrlEncode(string &result, const string &text);
	bool Base64UrlEncodeTrim(string &result, const string &text);
	bool Base64UrlDecode(string &result, const string &text);

	//HMAC-SHA
	string Sha1(const string &text);
	string Sha1Raw(const string &text);
	string HmacSha1(const string &text, const string &key);
	string HmacSha256(const string &text, const string &key);
}

#endif /* CRC_16_H_ */
