/*!
 * \file cgiin.cpp
 * \author FelitHuang
 * \version 1.0.0.1
 * \date    2005/12/20
*/

/************************************************************************/

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "basic.h"
#include "trans.h"
#include "cookie.h"
#include "cgivalue.h"
#include "cgiin.h"

// ************************************************************************

unsigned int CCGIIn::m_uiStatus(0);

// ************************************************************************

int CCGIIn::GetCGIInt(const std::string& sName, int nMin, int nMax, int nInvalidate, int nNull)
{
	m_uiStatus = 0x00;
	const std::string& sValue = CCGIValue::GetValue(sName);
	return CheckInt(sValue, nMin, nMax, nInvalidate, nNull);
}

double CCGIIn::GetCGIDbl(const std::string& sName, double dMin, double dMax, double dInvalidate, double dNull)
{
	m_uiStatus = 0x00;
	const std::string& sValue = CCGIValue::GetValue(sName);
	return CheckDbl(sValue, dMin, dMax, dInvalidate, dNull);
}

char CCGIIn::GetCGIChr(const std::string& sName, const std::string& sChSet, char cInvalidate, char cNull)
{
	m_uiStatus = 0x00;
	const std::string& sValue = CCGIValue::GetValue(sName);
	return CheckChr(sValue, sChSet, cInvalidate, cNull);
}

const std::string CCGIIn::GetCGIStr(const std::string& sName, int nSize, bool bChkDirty, const std::string& sChSet, bool bAllSpaceValid)
{
	m_uiStatus = 0x00;
	const std::string& sValue = CCGIValue::GetValue(sName);
	return CheckStr(sValue, nSize, sChSet, bChkDirty, bAllSpaceValid);
}

const std::string CCGIIn::GetCGIFmtStr(const std::string& sName, int nSize, const std::string& sChSet)
{
	m_uiStatus = 0x00;
	const std::string& sValue = CCGIValue::GetValue(sName);
	return CheckFmtStr(sValue, nSize, sChSet);
}

// ************************************************************************

void CCGIIn::GetCGIIntMul(const std::string& sName, std::vector<int>& vInt, int nMin, int nMax, int nInvalidate, int nNull)
{
	m_uiStatus = 0x00;
	std::vector<std::string> vValue;
	CCGIValue::GetValue(sName, vValue);
	for (std::vector<std::string>::size_type nIndex=0; nIndex<vValue.size(); ++nIndex)
	{
		vInt.push_back(CCGIIn::CheckInt(vValue[nIndex], nMin, nMax, nInvalidate, nNull));
	}
}

void CCGIIn::GetCGIStrMul(const std::string& sName, std::vector<std::string>& vStr, int nSize, bool bChkDirty, const std::string& sChSet, bool bAllSpaceValid)
{
	m_uiStatus = 0x00;
	std::vector<std::string> vValue;
	CCGIValue::GetValue(sName, vValue);
	for (std::vector<std::string>::size_type nIndex=0; nIndex<vValue.size(); ++nIndex)
	{
		vStr.push_back(CCGIIn::CheckStr(vValue[nIndex], nSize, sChSet, bChkDirty, bAllSpaceValid));
	}
}

void CCGIIn::GetCGIFmtStrMul(const std::string& sName, std::vector<std::string>& vStr, int nSize, const std::string& sChSet)
{
	m_uiStatus = 0x00;
	std::vector<std::string> vValue;
	CCGIValue::GetValue(sName, vValue);
	for (std::vector<std::string>::size_type nIndex=0; nIndex<vValue.size(); ++nIndex)
	{
		vStr.push_back(CCGIIn::CheckFmtStr(vValue[nIndex], nSize, sChSet));
	}
}

int CCGIIn::GetCGIUin(const std::string& sName)
{
	int iUin = GetCGIInt(sName);
	return (0==CBasic::IsUinValid(iUin)) ? iUin : -1;
}

unsigned CCGIIn::GetRemoteIP()
{
	char *szRemoteAddr = getenv("HTTP_QVIA");  // proxy
	if( szRemoteAddr )
	{ 
		struct sockaddr_in addr;
		if( sscanf(szRemoteAddr, "%8x", (unsigned int*) &(addr.sin_addr)) > 0 )
		{
			return addr.sin_addr.s_addr;
		}
	}
	else
	{
		szRemoteAddr = getenv("REMOTE_ADDR"); // no proxy
	}

	if( szRemoteAddr == NULL )
	{
		return -1;
	}
	else
	{
		return ntohl ( inet_addr( szRemoteAddr ));
	}
}

char *CCGIIn::GetStrRemoteIP()
{
	char *szRemoteAddr = getenv("HTTP_QVIA");  // proxy

	if( szRemoteAddr ) { 
		return szRemoteAddr;
	} else {
		return getenv("REMOTE_ADDR"); // no proxy
	}
}


// ************************************************************************

int CCGIIn::GetCookieInt(const std::string& sName, int nMin, int nMax, int nInvalidate, int nNull)
{
	m_uiStatus = 0x00;
	const std::string& sValue = CCookie::GetCookie(sName);
	return CheckInt(sValue, nMin, nMax, nInvalidate, nNull);
}

double CCGIIn::GetCookieDbl(const std::string& sName, double dMin, double dMax, double dInvalidate, double dNull)
{
	m_uiStatus = 0x00;
	const std::string& sValue = CCookie::GetCookie(sName);
	return CheckDbl(sValue, dMin, dMax, dInvalidate, dNull);
}

char CCGIIn::GetCookieChr(const std::string& sName, const std::string& sChSet, char cInvalidate, char cNull)
{
	m_uiStatus = 0x00;
	const std::string& sValue = CCookie::GetCookie(sName);
	return CheckChr(sValue, sChSet, cInvalidate, cNull);
}

const std::string CCGIIn::GetCookieStr(const std::string& sName, int nSize, bool bChkDirty, const std::string& sChSet, bool bAllSpaceValid)
{
	m_uiStatus = 0x00;
	const std::string& sValue = CCookie::GetCookie(sName);
	return CheckStr(sValue, nSize, sChSet, bChkDirty, bAllSpaceValid);
}

const std::string CCGIIn::GetCookieFmtStr(const std::string& sName, int nSize, const std::string& sChSet)
{
	m_uiStatus = 0x00;
	const std::string& sValue = CCookie::GetCookie(sName);
	return CheckFmtStr(sValue, nSize, sChSet);
}

// ************************************************************************

int CCGIIn::GetClientInfo(QQShowClientInfo& stClientInfo)
{
	struct INNER
	{
		static int HTOI(const char* pchHex)
		{
			int iH = (pchHex[0]>='0' && pchHex[0]<='9') ? (pchHex[0]-'0') : (pchHex[0]>='A' && pchHex[0]<='F') ? (pchHex[0]-'A'+10) : (pchHex[0]>='a' && pchHex[0]<='f') ? (pchHex[0]-'a'+10) : 0;
			int iL = (pchHex[1]>='0' && pchHex[1]<='9') ? (pchHex[1]-'0') : (pchHex[1]>='A' && pchHex[1]<='F') ? (pchHex[1]-'A'+10) : (pchHex[1]>='a' && pchHex[1]<='f') ? (pchHex[1]-'a'+10) : 0;
			return iH*16+iL;
		}
	};
	if (getenv("HTTP_QVIA") != NULL)
	{
		const char* pchQVIA = getenv("HTTP_QVIA");
		
		stClientInfo.sRemoteAddress =
			CTrans::ITOS(INNER::HTOI(pchQVIA))+"."
			+ CTrans::ITOS(INNER::HTOI(pchQVIA+2))+"."
			+ CTrans::ITOS(INNER::HTOI(pchQVIA+4))+"."
			+ CTrans::ITOS(INNER::HTOI(pchQVIA+6));
	}
	else
	{
		char* pchAddr = getenv("REMOTE_ADDR");
		stClientInfo.sRemoteAddress	= (pchAddr==NULL) ? ("") : (pchAddr);
	}
	char* pchPort = getenv("REMOTE_PORT");
	stClientInfo.sRemotePort	= (pchPort==NULL) ? ("") : (pchPort);

	return 0;
}

// ************************************************************************

int CCGIIn::CheckInt(const std::string& sValue, int nMin, int nMax, int nInvalidate, int nNull)
{
	if (sValue.empty())
	{
		m_uiStatus |= CGI_EM_NUL;
		return nNull;
	}
	int nValue = CTrans::STOI(sValue);
	if (nValue < nMin || nValue > nMax)
	{
		m_uiStatus |= CGI_EM_INV;
		return nInvalidate;
	}

	return nValue;
}

double CCGIIn::CheckDbl(const std::string& sValue, double dMin, double dMax, double dInvalidate, double dNull)
{
	if (sValue.empty())
	{
		m_uiStatus |= CGI_EM_NUL;
		return dNull;
	}
	double dValue = CTrans::STOF(sValue);
	if (dValue < dMin || dValue > dMax)
	{
		m_uiStatus |= CGI_EM_INV;
		return dInvalidate;
	}

	return dValue;
}

const std::string CCGIIn::CheckStr(const std::string& sValue, int nSize, const std::string& sChSet, bool bChkDirty, bool bAllSpaceValid)
{
	if (sValue.empty())
	{
		m_uiStatus |= CGI_EM_NUL;
		return sValue;
	}
	if (!sChSet.empty() && 0!=CCGIIn::CheckInSet(sValue, sChSet))
	{
		m_uiStatus |= CGI_EM_SET;
		return std::string("");
	}
	if (bChkDirty && 0 != CCGIIn::CheckDirty(sValue))
	{
		m_uiStatus |= CGI_EM_DIR;
		return std::string("");
	}
	if (!bAllSpaceValid && sValue.size()>0 && 0==CheckInSet(sValue, QQSHOW_CHSET_SPACE))
	{
		m_uiStatus |= CGI_EM_SPC;
		return std::string("");
	}
	if (nSize > 0 && (int)sValue.size() > nSize)
	{
		return sValue.substr(0, CBasic::CheckChn(sValue.c_str(), nSize));
	}

	return sValue;
}

char CCGIIn::CheckChr(const std::string& sValue, const std::string& sChSet, char cInvalidate, char cNull)
{
	if (sValue.empty())
	{
		m_uiStatus |= CGI_EM_NUL;
		return cNull;
	}
	char cValue = sValue[0];
	if (!sChSet.empty() && std::string::npos==sChSet.find(cValue, 0))
	{
		m_uiStatus |= CGI_EM_INV | CGI_EM_SET;
		return cInvalidate;
	}
	return cValue;
}

const std::string CCGIIn::CheckFmtStr(const std::string& sValue, int nSize, const std::string& sChSet)
{
	if (sValue.empty())
	{
		m_uiStatus |= CGI_EM_NUL;
		return sValue;
	}
	if (!sChSet.empty() && 0!=CCGIIn::CheckInSet(sValue, sChSet))
	{
		m_uiStatus |= CGI_EM_SET;
		return std::string("");
	}
	if (nSize > 0 && (int)sValue.size() > nSize)
	{
		return sValue.substr(0, nSize);
	}

	return sValue;
}

// ************************************************************************

int CCGIIn::CheckDirty(const std::string& sValue)
{
	//because never use check dirty function, so commented by paulhuang 2010.1.20
	return 0;
}

int CCGIIn::CheckInSet(const std::string& sValue, const std::string& sChSet)
{
	for (std::string::size_type nIndex=0; nIndex<sValue.size(); ++nIndex)
	{
		if (std::string::npos == sChSet.find(sValue[nIndex]))
		{
			return -1;
		}
	}
	return 0;
}

// ************************************************************************
