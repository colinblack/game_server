#include "ptlogin.h"
#include "trans.h"
#include "ctime.h"
#include "basic.h"
#include "cookie.h"
#include "commlog.h"
#include "tsc.h"
#include "markupstl.h"
#include "cgiin.h"

#include <stdlib.h>
#include <string.h>


int CPtLogin::mn_Flag = 0;
int CPtLogin::mn_Appid = 15002358;

// 读取appid
int CPtLogin::Init(const char * config)
{

	return 0;
}

// ptlogin 从cookie提取号码
int CPtLogin::PickUin(const char* szUin)
{
	char* p = (char*)szUin;
	if(!p || *p != 'o')
		return 0;

	p++;
	while(*p== '0')
		p++;
	return atol(p);
}

int CPtLogin::GetRemoteAddress(string& sRemoteAddress)
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
		
		sRemoteAddress =
			CTrans::ITOS(INNER::HTOI(pchQVIA))+"."
			+ CTrans::ITOS(INNER::HTOI(pchQVIA+2))+"."
			+ CTrans::ITOS(INNER::HTOI(pchQVIA+4))+"."
			+ CTrans::ITOS(INNER::HTOI(pchQVIA+6));
	}
	else
	{
		char* pchAddr = getenv("REMOTE_ADDR");
		sRemoteAddress	= (pchAddr==NULL) ? ("") : (pchAddr);
	}
	//char* pchPort = getenv("REMOTE_PORT");
	//stClientInfo.sRemotePort	= (pchPort==NULL) ? ("") : (pchPort);

	return 0;
}


int CPtLogin::CheckLogin(unsigned int & iUin, bool bNotCkPtlogin /*=false*/)
{
	iUin = 0;
	std::string sKey = CCookie::GetCookie("skey");
	std::string sUin = CCookie::GetCookie("uin");
	if (sKey.empty() || sUin.empty()) {
		//TODO need do check
		iUin = CCGIIn::GetCGIInt("uin");


		return 0;
	}
	iUin = PickUin(sUin.c_str());

	return 0;
}


