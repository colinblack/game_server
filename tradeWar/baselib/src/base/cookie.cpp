/*!
 * \file cookie.cpp
 * \author FelitHuang
 * \date 2006-01-13
*/

#include <string>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include "basic.h"
#include "ctime.h"
#include "trans.h"
#include "cookie.h"

#include "staticdata.h"


int CHeader::ScriptHeader(const std::string& chSet, int iExpire)
{
	//static std::ostream& ostm = std::cout<<"Content-type: application/x-javascript; charset="<<chSet<<"\r\n" <<"Expires: "<<iExpire<<"\r\n\r\n";
	std::string sChSet = chSet;
	std::string sHeader = "Content-type: application/x-javascript; charset="+sChSet+"\r\n"+"Expires: "+CTrans::ITOS(iExpire)+"\r\n\r\n";

	//int iRet = write(STDOUT_FILENO,sHeader.c_str(),sHeader.size());
	int iRet = FCGI_printf("%s",sHeader.c_str());
    return 0;
}


int CHeader::HtmlHeader(const std::string& chSet, int iExpire)
{
	//static std::ostream& ostm = std::cout<<"Content-type: text/html; charset="<<chSet<<"\r\n" <<"Expires: "<<iExpire<<"\r\n\r\n";
	std::string sChSet = chSet;
	std::string sHeader = "Content-type: text/html; charset="+sChSet+"\r\n"+"Expires: "+CTrans::ITOS(iExpire)+"\r\n\r\n";

	//int iRet = write(STDOUT_FILENO,sHeader.c_str(),sHeader.size());
	int iRet = FCGI_printf("%s",sHeader.c_str());
    return 0;
}

int CHeader::XMLHeader(const std::string& chSet, int iExpire)
{
	//static std::ostream& ostm = std::cout<<"Content-type: text/xml; charset="<<chSet<<"\r\n"<<"Expires: "<<iExpire<<"\r\n\r\n";
	std::string sChSet = chSet;
	std::string sHeader = "Content-type: text/xml; charset="+sChSet+"\r\n"+"Expires: "+CTrans::ITOS(iExpire)+"\r\n\r\n";

	//int iRet = write(STDOUT_FILENO,sHeader.c_str(),sHeader.size());
	int iRet = FCGI_printf("%s",sHeader.c_str());

    return 0;
}

int CHeader::LocationHeader(const std::string& sLocation, const std::string& chSet, int iExpire)
{
	//std::cout<<"Location: "<<sLocation<<"\r\n";
	std::string sLoc = sLocation;
	std::string sHeader = "Location: "+sLoc;
	int iRet = write(STDOUT_FILENO,sHeader.c_str(),sHeader.size());
	HtmlHeader(chSet, iExpire);
    return (iRet);
}

int CHeader::Pragma(const std::string& sText)
{
	//std::cout<<"Pragma: "<<sText<<"\r\n";
	std::string sTmp = sText;
	std::string sHeader = "Pragma: "+sTmp+"\r\n";
	//int iRet = write(STDOUT_FILENO,sHeader.c_str(),sHeader.size());
	int iRet = FCGI_printf("%s",sHeader.c_str());
    return (iRet);
}


CCookie::CData& CCookie::GetData()
{
	static CData* s_xData = NULL;
	if (NULL == s_xData || 0 == STATICDATA::m_iCookieState)
	{
		if (NULL != s_xData)
		{
			delete s_xData;
		}
		s_xData = new CData();
		STATICDATA::m_iCookieState = 1;
	}
	return *s_xData;
}

CCookie::CData::CData()
{
	m_vData.clear();

	const char* pCookie = getenv("HTTP_COOKIE");
	
	std::string sCookie(pCookie==NULL? "" : pCookie);
	
	if (!sCookie.empty())
	{
		std::vector<std::string> vItems;
		
		CBasic::StringSplit(sCookie, "; ", vItems);		// COOKIE间隔符"; "中有一空格,此格式有待确认

		m_vData.reserve(vItems.size()+1);	// 保留多一个以作查找哨兵

		for (std::vector<std::string>::size_type iIndex=0; iIndex<vItems.size(); ++iIndex)
		{
			std::vector<std::string> vPairs;
			
			CBasic::StringSplit(vItems[iIndex], "=", vPairs);
			
			CItem stData;
			
			stData.sName = vPairs[0];
			stData.sData = (vPairs.size()>1) ? vPairs[1] : std::string("");
			
			stData.sName = CBasic::unescape(stData.sName);
			stData.sData = CBasic::unescape(stData.sData);
			
			m_vData.push_back(stData);
		}
	}
	
	m_vData.push_back(CItem());	// 查找哨兵
}

const std::string& CCookie::GetCookie(const std::string& sName)
{
	std::vector<CData::CItem>::reverse_iterator s_itRBegin = GetData().m_vData.rbegin();
	
	s_itRBegin->sName = sName;	// 设置哨兵
	
	std::vector<CData::CItem>::iterator itItem = GetData().m_vData.begin();
	
	while (sName != itItem->sName)
	{
		++itItem;
	}
	
	return itItem->sData;
}

int CCookie::CheckExists(const std::string& sName)
{
	return (&GetCookie(sName)==&(GetData().m_vData.rbegin()->sData)) ? -1 : 0;
}

int CCookie::SetCookie(const std::string& sName, const std::string& sValue, int iExpireSec, const std::string& sDomain, const std::string& sPath, bool bSecure)
{
	//std::cout<<"Set-Cookie: ";
	
	//std::cout<<sName<<"="<<CBasic::escape(sValue)<<";";
	
	std::string sContent = "Set-Cookie: " + sName + "=" + CBasic::escape(sValue) + ";";
	
	if (iExpireSec != 0)
	{
		time_t tTime = time(NULL)+iExpireSec;
		
		//std::cout<<" expires="<<CTime::UTCTime(tTime)<<";";
		sContent +=  " expires=" + CTime::UTCTime(tTime)+";";
	}
	
	if (!sPath.empty())
	{
		//std::cout<<" path="<<sPath<<";";
		sContent +=  " path="+sPath+";";
	}
	
	if (!sDomain.empty())
	{
		//std::cout<<" domain="<<sDomain<<";";
		sContent +=  " domain="+sDomain+";";
	}
	
	if (bSecure)
	{
		//std::cout<<" secure;";
		sContent +=  " secure;";
	}
	
	//std::cout<<"\r"<<std::endl;
	sContent += "\r\n";
	//int iRet = write(STDOUT_FILENO,sContent.c_str(),sContent.size());
	FCGI_printf("%s",sContent.c_str());
	return (0);
}

int CCookie::ClearCookie(const std::string& sName, const std::string& sDomain, const std::string& sPath, bool bSecure)
{
	//std::cout<<"Set-Cookie: ";
	
	//std::cout<<sName<<"=; expires="<<CTime::UTCTime(0)<<";";

	std::string sContent = "Set-Cookie: " + sName + "=; expires="+CTime::UTCTime(0)+";";
		
	if (!sPath.empty())
	{
		//std::cout<<" path="<<sPath<<";";
		sContent  +=  " path="+sPath+";";
	} 
	
	if (!sDomain.empty())
	{
		//std::cout<<" domain="<<sDomain<<";";
		sContent  +=  " domain="+sDomain+";";
	}
	
	if (bSecure)
	{
		//std::cout<<" secure;";
		sContent += " secure;";
	}
	
	//std::cout<<"\r"<<std::endl;
	sContent += "\r\n";
	//int iRet = write(STDOUT_FILENO,sContent.c_str(),sContent.size());
	FCGI_printf("%s",sContent.c_str());
	return (0);
}

