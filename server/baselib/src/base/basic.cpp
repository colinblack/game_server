#include "trans.h"
#include "basic.h"
#include "ctime.h"
//#include "tbase_all.h"
//#include "md5c.h"
#include <sstream>
#include <iomanip>

#include "csconv.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>

#include <net/if.h>
/*初始化默认ID*/
std::string CBasic::sCallerID = "QQShowCGI";

/*初始化默认IP*/
std::string CBasic::sWebServerIP = "unknown";

int CBasic::SetCaller(const std::string &sCaller)
{
	if("" != sCaller)
		sCallerID = sCaller;
	return 0;
}

const std::string CBasic::GetCaller(void)
{
	return sCallerID;
}

const std::string CBasic::GetAtomCaller(void)
{
		std::string::size_type iIndex = std::string::npos;
	    iIndex = sCallerID.size() >  29 ? sCallerID.size() - 29 : 0;
		return sCallerID.substr(iIndex);
}

int CBasic::RecWebServerIP(const std::string &sIP)
{
	if(!sIP.empty())
	{	
		sWebServerIP = sIP;
	}
	return 0;
}

const std::string CBasic::GetWebServerIP(void)
{
	return sWebServerIP;
}


std::string& CBasic::StringReplace(std::string& sData, const std::string& sSrc, const std::string& sDst)
{
	std::string::size_type pos = 0;
	std::string::size_type slen = sSrc.size();
	std::string::size_type dlen = sDst.size();
	while ((pos=sData.find(sSrc, pos)) != std::string::npos)
	{
		sData.replace(pos, slen, sDst);
		pos += dlen;
	}

	return sData;
}

std::vector<std::string>& CBasic::StringSplit(const std::string& sData, const std::string& sDelim, std::vector<std::string>& vItems)
{
	vItems.clear();

	std::string::size_type bpos = 0;
	std::string::size_type epos = 0;
	std::string::size_type nlen = sDelim.size();
	while ((epos=sData.find(sDelim, epos)) != std::string::npos)
	{
		vItems.push_back(sData.substr(bpos, epos-bpos));
		epos += nlen;
		bpos = epos;
	}

	vItems.push_back(sData.substr(bpos, sData.size()-bpos));

	return vItems;
}

std::vector<int>& CBasic::StringSplit(const std::string& sData, const std::string& sDelim, std::vector<int>& vItems)
{
	std::vector<std::string> vStrings;

	vItems.clear();

	CBasic::StringSplit(sData, sDelim, vStrings);

	for (std::vector<std::string>::size_type iIndex=0; iIndex<vStrings.size(); ++iIndex)
	{
		vItems.push_back(CTrans::STOI(vStrings[iIndex]));
	}

	return vItems;
}

std::vector<long long>& CBasic::StringSplit(const std::string& sData, const std::string& sDelim, std::vector<long long>& vItems)
{
	std::vector<std::string> vStrings;

	vItems.clear();

	CBasic::StringSplit(sData, sDelim, vStrings);

	for (std::vector<std::string>::size_type iIndex=0; iIndex<vStrings.size(); ++iIndex)
	{
		vItems.push_back(CTrans::STOI64(vStrings[iIndex]));
	}

	return vItems;
}

std::vector<std::string>& CBasic::StringSplitTrim(const std::string& sData, const std::string& sDelim, std::vector<std::string>& vItems)
{
	vItems.clear();

	std::string::size_type bpos = 0;
	std::string::size_type epos = 0;
	std::string::size_type nlen = sDelim.size();

	while(sData.substr(epos,nlen) == sDelim)
	{	
		epos += nlen;
	}
	
	bpos = epos;

	while ((epos=sData.find(sDelim, epos)) != std::string::npos)
	{
		vItems.push_back(sData.substr(bpos, epos-bpos));
		
		epos += nlen;
		
		while(sData.substr(epos,nlen) == sDelim)
		{	
			epos += nlen;
		}
		
		bpos = epos;
	}

	if(bpos != sData.size())
	{
		vItems.push_back(sData.substr(bpos, sData.size()-bpos));
	}

	return vItems;
}

std::string CBasic::StringTrim(std::string& sData, const std::string& sDelim)
{
	// trim right
	sData.erase(sData.find_last_not_of(sDelim)+1);
	// trim left
	return sData.erase(0,sData.find_first_not_of(sDelim));
}

std::string CBasic::StringJoin(const std::vector<std::string>& vstElem, const std::string& sDelim)
{
	std::string sText;
	std::vector<std::string>::const_iterator bpos = vstElem.begin();
	std::vector<std::string>::const_iterator epos = vstElem.end();
	std::vector<std::string>::const_iterator cpos = bpos;
	while (cpos != epos)
	{
		if (cpos != bpos)
		{
			sText += sDelim;
		}
		sText += *cpos++;
	}
	return sText;
}

std::string CBasic::StringHumanJoin(const std::vector<std::string>& vstElem,
		const std::string& lastDelim, const std::string& listDelim)
{
	size_t size = vstElem.size();
	if(size<3)
	{
		return StringJoin(vstElem, lastDelim);
	}
	std::string sText(vstElem.front());
	--size;
	for(size_t i=1; i<size; ++i)
	{
		sText.append(listDelim);
		sText.append(vstElem.at(i));
	}
	sText.append(lastDelim);
	sText.append(vstElem.back());
	return sText;
}

std::string CBasic::StringJoin(const std::vector<int>& vstElem, const std::string& sDelim)
{
	std::string sText;
	std::vector<int>::const_iterator bpos = vstElem.begin();
	std::vector<int>::const_iterator epos = vstElem.end();
	std::vector<int>::const_iterator cpos = bpos;
	while (cpos != epos)
	{
		if (cpos != bpos)
		{
			sText += sDelim;
		}
		sText += CTrans::ITOS(*cpos++);
	}
	return sText;
}

std::string CBasic::StringEscape(const std::string& sData)
{
	std::string sValue;
	for (std::string::size_type xpos=0; xpos<sData.size(); ++xpos)
	{
		sValue += CTrans::CTOH(sData[xpos]);
	}
	return sValue;
}

std::string CBasic::StringUnEscape(const std::string& sData)
{
	std::string sValue(sData);
	std::string::size_type cpos = 0;
	while (std::string::npos != (cpos=sValue.find("%", cpos)))
	{
		sValue.replace(cpos, 3, 1, CTrans::HTOC(sValue.data() + cpos));
		cpos += 1;
	}
	return sValue;
}

std::string CBasic::XMLEncode(const std::string& sData)
{
	char vx2[3] = { 0, 0, 0 };
	char vx4[5] = { 0, 0, 0, 0, 0 };
	std::string sValue;
	const char* bpos = sData.data();
	const char* epos = sData.data()+sData.size();
	static bool s_esc[256] =
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	};
	while (bpos < epos)
	{
		if (*bpos < 0)
		{
			sValue += "&#x";
			sValue += CTrans::CTOX4(bpos, vx4);
			sValue += ";";
			bpos += 2;
		}
		else if (!s_esc[*(unsigned char*)bpos])
		{
			sValue += *bpos;
			bpos += 1;
		}
        else if (*bpos!=13 && *bpos!=10 && *bpos < 32) 
		{
            sValue += "&#x";
			sValue += "3F";    //全部替换为"?"
			sValue += ";";
			bpos += 1;
		}
		else
		{
			sValue += "&#x";
			sValue += CTrans::CTOX2(bpos, vx2);
			sValue += ";";
			bpos += 1;
		}
	}
	return sValue;
}

std::string CBasic::XMLMiniEncode(const std::string& sData)
{
	char vx2[3] = { 0, 0, 0 };
	std::string sValue;
	const char* bpos = sData.data();
	const char* epos = sData.data()+sData.size();
	static bool s_esc[256] =
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	};
	while (bpos < epos)
	{
		if (*bpos < 0)
		{
			sValue += bpos[0];
			sValue += bpos[1];
			bpos += 2;
		}
		else if (!s_esc[*(unsigned char*)bpos])
		{
			sValue += *bpos;
			bpos += 1;
		}
        else if (*bpos!=13 && *bpos!=10 && *bpos < 32) 
		{
            sValue += "&#x";
			sValue += "3F";    //全部替换为"?"
			sValue += ";";
			bpos += 1;
		}
		else
		{
			sValue += "&#x";
			sValue += CTrans::CTOX2(bpos, vx2);
			sValue += ";";
			bpos += 1;
		}
	}
	return sValue;
}

std::string CBasic::escape(const std::string& sData)
{
	char vx2[3] = { 0, 0, 0 };
	char vx4[5] = { 0, 0, 0, 0, 0 };
	std::string sValue;
	const char* bpos = sData.data();
	const char* epos = sData.data()+sData.size();
	static bool s_esc[256] =
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	};
	while (bpos < epos)
	{
		if (*bpos < 0)
		{
			sValue += "%u";
			sValue += CTrans::CTOX4(bpos, vx4);
			bpos += 2;
		}
		else if (!s_esc[*(unsigned char*)bpos])
		{
			sValue += *bpos;
			bpos += 1;
		}
		else
		{
			sValue += "%";
			sValue += CTrans::CTOX2(bpos, vx2);
			bpos += 1;
		}
	}
	return sValue;
}

std::string CBasic::unescape(const std::string& sData)
{
//	struct HEX
//	{
//		static bool isHex(char ch)
//		{
//			return (ch>='0' && ch<='9' || ch>='A' && ch<='F' || ch>='a' && ch<='f');
//		}
//	};
//
//	std::string sValue(sData);
//	std::string::size_type cpos = 0;
//	std::string::size_type nlen = sData.size();
//	while (std::string::npos != (cpos=sValue.find("%", cpos)))
//	{
//        char vc1[2] = { 0, 0 };
//    	char vc2[3] = { 0, 0, 0 };
//		if ((sValue[cpos+1]=='u' || sValue[cpos+1]=='U') && (nlen>cpos+5) && HEX::isHex(sValue[cpos+2]) && HEX::isHex(sValue[cpos+3]) && HEX::isHex(sValue[cpos+4]) && HEX::isHex(sValue[cpos+5]))
//		{
//			sValue.replace(cpos, 6, CTrans::X4TOC(sValue.data()+cpos+2, vc2), 2);
//			cpos += 2;
//		}
//		else if ((nlen>cpos+2) && HEX::isHex(sValue[cpos+1]) && HEX::isHex(sValue[cpos+2]))
//		{
//			sValue.replace(cpos, 3, CTrans::X2TOC(sValue.data()+cpos+1, vc1), 1);
//			cpos += 1;
//		}
//		else
//		{
//			cpos += 1;
//		}
//	}
//	return sValue;

	string result;
	result.resize(sData.size());
	char *pcResult = const_cast<char *>(result.c_str());
	const char *pcData = sData.c_str();
	const char *pcDataEnd = pcData + sData.size();
	char vc[2] = { 0, 0 };
	while(pcData < pcDataEnd)
	{
		if(*pcData == '%' && pcData + 2 < pcDataEnd && isxdigit(pcData[1]) && isxdigit(pcData[2]))
		{
			CTrans::X2TOC(pcData + 1, vc);
			*pcResult++ = vc[0];
			pcData += 3;
		}
		else
		{
			*pcResult++ = *pcData++;
		}
	}
	result.resize(pcResult - result.c_str());
	return result;
}

std::string CBasic::UTF8(const std::string& sData)
{
	std::string sUTF8;
	T_UC* tUC = new T_UC[sData.size()];
	int nUClen = XGBUC::cv(sData.data(), sData.size(), tUC, sData.size());
	if (nUClen > 0)
	{
		sUTF8.resize(nUClen*3);
		sUTF8.resize(XUCUTF8::cv(tUC, nUClen, (T_UTF8*)sUTF8.data(), sUTF8.size()));
	}
	delete[] tUC;
	return sUTF8;
}

std::string& CBasic::StringChnCut(std::string& sData, int nSize)
{
	if (nSize >= (int)sData.size())
	{
		return sData;
	}
	sData.erase(CheckChn(sData.data(), nSize), std::string::npos);
	return sData;
}

int CBasic::CheckChn(const char* pcData, int nSize)
{
	const char* pcEnd = pcData+nSize;
	while (pcData < pcEnd)
	{
		if (*pcData >= 0)
		{
			++pcData;
		}
		else
		{
			pcData += 2;
		}
	}
	return (pcData==pcEnd) ? (nSize) : (nSize-1);
}

int CBasic::Wordlen(const std::string& sData)
{
	int nlen = 0;
	const char* bp = sData.data();
	const char* ep = bp+sData.size();
	while (bp < ep)
	{
		nlen++;
		if (*bp>=0)
		{
			++bp;
		}
		else
		{
			bp += 2;
		}
	}
	return nlen;
}

std::string CBasic::Wordreserve(const std::string& sData, int nSize)
{
	const char* bp = sData.data();
	const char* ep = bp+sData.size();
	while (nSize>0 && bp<ep)
	{
		nSize--;
		if (*bp>=0)
		{
			++bp;
		}
		else
		{
			bp += 2;
		}
	}
	if (bp==ep)
	{
		return sData;
	}
	return sData.substr(0, bp-sData.data());
}

int CBasic::IsUinValid(int iUin)
{
	return (iUin>=UIN_MIN && iUin<=UIN_MAX) ? 0 : -1;
}

int CBasic::IsQQShowItemnoValid(int iItemNo)
{
	return (iItemNo>=1 && iItemNo<=50000) ? 0 : -1;
}

//int CBasic::MD5Make(const std::string& sData, int iDataLen, const std::string& sKey, int iKeyLen, std::string& sMD5, int iMD5Len)
//{
//	if (iMD5Len < MD5_MIN_LEN)
//	{
//		return -1;
//	}
//	else if (iMD5Len > MD5_MAX_LEN)
//	{
//		iMD5Len = MD5_MAX_LEN;
//	}
//	
//	sMD5.resize(iMD5Len);
//
//	return TBase_MD5Make((const unsigned char *)sData.c_str(), iDataLen, 
//		(const unsigned char *)sKey.c_str(), iKeyLen, 
//		(unsigned char *)(const_cast< char *>(sMD5.data())), iMD5Len);
//}
//
//
//int CBasic::MD5NCmp(const std::string& sData, int iDataLen, const std::string& sKey, int iKeyLen, const std::string& sMD5, int iMD5Len )
//{
//	if (iMD5Len < MD5_MIN_LEN)
//	{
//		return -1;
//	}
//	
//	return TBase_MD5NCmp((const unsigned char *)sData.c_str(), iDataLen, 
//		(const unsigned char *)sKey.c_str(), iKeyLen, 
//		(unsigned char *)sMD5.c_str(), iMD5Len);
//}
//
//std::string CBasic::MD5Make(const std::string& sData, const std::string& sKey)
//{
//	std::string sMD5;
//	MD5Make(sData, sData.size(), sKey, sKey.size(), sMD5, MD5_MAX_LEN);
//	return sMD5;
//}
//
//int CBasic::MD5NCmp(const std::string& sData, const std::string& sKey, const std::string& sMD5)
//{
//	return MD5NCmp(sData, sData.size(), sKey, sKey.size(), sMD5, sMD5.size());
//}
//
//int CBasic::MD5Comm(const std::string& sData, std::string& sMD5)
//{
//	MD5_CTX stCTX;
//	unsigned char uchOput[16];
//	memset(uchOput, 0, sizeof(uchOput));
//
//	MD5cInit(&stCTX);
//	MD5cUpdate(&stCTX, (unsigned char*)sData.c_str(), sData.size());
//	MD5cFinal(uchOput, &stCTX);
//
//	std::stringstream strm;
//	strm.setf(std::ios::uppercase);
//
//	for (unsigned int i=0; i<sizeof(uchOput); i++)
//	{
//		strm<<std::setw(2)<<std::setfill('0')<<std::hex<<((int)(uchOput[i]));
//	}
//
//	sMD5 = strm.str();
//
//	return 0;
//}

//int CBasic::CheckLimit(int iAppID, const std::string& sID)
//{
//    return 0;//TBase_CheckLimit(iAppID, CBasic::MD5Make(sID, "basic@frqlimit.com").substr(0, 14).c_str());
//}


std::string CBasic::QQShowInternalSerialID(const std::string& sCode)
{
	timeval tv = CTime::GetTimeOfDay();
	timeval t0 = { CTime::GetDayBeginTime(tv.tv_sec), 0 };
	return sCode+CTime::FormatTime("-%Y%m%d-", t0.tv_sec)+CTime::GetMSInterval(t0, tv);
}




// 现网机器上是双网卡，只记录内网IP（172开头的IP）

std::string CBasic::GetLocalIp()
{
   
	string localip = "";
  
	int fd;
 
	struct ifconf if_conf; 
	
	struct sockaddr_in *sin;

 
	fd = socket(PF_INET, SOCK_DGRAM, 0);

 
	if_conf.ifc_req = (struct ifreq *)malloc(10 * sizeof(struct ifreq));
	if_conf.ifc_len = 10 * sizeof(struct ifreq);
	
if(ioctl(fd, SIOCGIFCONF, &if_conf) == -1)
    
	{
		free(if_conf.ifc_req);
  
		close(fd);
     
		return "取IP信息失败";
  
	}

   
			//char p[20];
  
	for (unsigned int i = 0; i < if_conf.ifc_len / sizeof(struct ifreq); i++)
  
	{

		sin = (struct sockaddr_in *)&if_conf.ifc_req[i].ifr_addr;
   
		{
          
			char buf[64];
    
			const char *p;
         
			p = inet_ntop(AF_INET, &sin->sin_addr, buf, sizeof(buf));
   
			if(strncmp(p, "172", 3) == 0)
            
			{
             
				localip = p;
         
				break;
          
			}
       
		}
   
	}
        
  
	free(if_conf.ifc_req); 
	
close(fd);
 
	return localip;

}



/*
std::string& CBasic::Compress(const std::string& sinQQShowCode, std::string& soutQQShowCode);
std::string& CBasic::DeCompress(const std::string& sinQQShowCode, std::string& soutQQShowCode);
*/
