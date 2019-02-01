/*!
 * \file stresc.cpp
 * \author FelitHuang
 * \version 1.0.0.1
 * \date    2005/12/20
*/

/************************************************************************/

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

//#include <mysql.h>

#include "trans.h"
#include "basic.h"
#include "stresc.h"


/*!
 * CStrBase-Member-Function-Definition
*/

CStrBase::CStrBase()
{
}

CStrBase::~CStrBase()
{
}

const std::string& CStrBase::Data() const
{
	return m_Data;
}

void CStrBase::ReplaceString(std::string& sData, const std::string* sSrc, const std::string* sDst, size_t nlen)
{
	for (size_t nIndex=0; nIndex<nlen; ++nIndex)
	{
		CBasic::StringReplace(sData, sSrc[nIndex], sDst[nIndex]);
	}
}


/*!
 * CStrDirect-Member-Function-Definition
*/

CStrDirect::CStrDirect(const char cInit)
{
	m_Data = cInit;
}

CStrDirect::CStrDirect(const std::string& sInit)
{
	m_Data = sInit;
}


/*!
 * CStrHtml-Member-Function-Definition
*/

CStrHtml::CStrHtml(const char cInit)
{
	m_Data = cInit;
	Translate();
}

CStrHtml::CStrHtml(const std::string& sInit)
{
	m_Data = sInit;
	Translate();
}


/*!
 * CStrInput-Member-Function-Definition
*/

CStrInput::CStrInput(const char cInit)
{
	m_Data = cInit;
	Translate();
}

CStrInput::CStrInput(const std::string& sInit)
{
	m_Data = sInit;
	Translate();
}


/*!
 * CStrScript-Member-Function-Definition
*/

CStrScript::CStrScript(const char cInit)
{
	m_Data = cInit;
	Translate();
}

CStrScript::CStrScript(const std::string& sInit)
{
	m_Data = sInit;
	Translate();
}

/*!
 * CStrTArea-Member-Function-Definition
*/

CStrTArea::CStrTArea(const char cInit)
{
	m_Data = cInit;
	Translate();
}

CStrTArea::CStrTArea(const std::string& sInit)
{
	m_Data = sInit;
	Translate();
}

/*!
 * CStrXml-Member-Function-Definition
*/

CStrXml::CStrXml(const char cInit)
{
	m_Data = cInit;
	Translate();
}

CStrXml::CStrXml(const std::string& sInit)
{
	m_Data = sInit;
	Translate();
}

/*!
 * CStrUrl-Member-Function-Definition
*/

CStrUrl::CStrUrl(const char cInit)
{
	m_Data = cInit;
	//Translate();
}

CStrUrl::CStrUrl(const std::string& sInit, const std::string& sProtocol, const std::string& sDomain)
{
	if (0 == CheckUrl(sInit, sProtocol, sDomain))
	{
		m_Data = sInit;
		//Translate();
	}
}

int CStrUrl::CheckUrl(const std::string& sUrl, const std::string& sProtocol, const std::string& sDomain)
{
	// do_not_need_to_check_if_empty
	if (sProtocol.empty() && sDomain.empty())
	{
		return 0;
	}

	// find_protocol
	std::string sProtocolDiv("://");
	std::string::size_type hpos = sUrl.find(sProtocolDiv);
	if (hpos==std::string::npos)
	{
		return -1;
	}

	// check_protocol
	if (!sProtocol.empty())
	{
		std::string sProtocolUrl = sUrl.substr(0, hpos+sProtocolDiv.size());
		std::string::size_type npos = sProtocol.find(sProtocolUrl);
		if (npos!=0 && sProtocol[npos-1]!='|')
		{
			return -1;
		}
	}
	
	// check_domain
	if (!sDomain.empty())
	{
		std::string::size_type bpos = hpos+sProtocolDiv.size();
		std::string::size_type epos = sUrl.find(sDomain, bpos);

		// no_found_domain
		if (epos==std::string::npos)
		{
			return -1;
		}

		// for_file:///
		if (sUrl[bpos]=='/')
		{
			++bpos;
		}

		// check_domain_divider
		if (epos!=bpos && sUrl[epos-1]!='.')
		{
			return -1;
		}

		// check_domain_valid_character
		for (std::string::size_type ipos=bpos; ipos<epos; ++ipos)
		{
			if (sUrl[ipos]>='A' && sUrl[ipos]<='Z' ||
				sUrl[ipos]>='a' && sUrl[ipos]<='z' ||
				sUrl[ipos]>='0' && sUrl[ipos]<='9' ||
				sUrl[ipos]=='-' || sUrl[ipos]=='.')
			{
				continue;
			}
			return -1;
		}
	}

	return 0;
}


/*!
 * CStrSqlValue-Member-Function-Definition
*/

CStrSqlValue::CStrSqlValue(const char cInit)
{
	m_Data = cInit;
	Translate();
}

CStrSqlValue::CStrSqlValue(const char* sInit, size_t nMaxlen)
{
	m_Data = sInit;
	if (nMaxlen>0 && nMaxlen<m_Data.size())
	{
		m_Data.resize(CBasic::CheckChn(m_Data.c_str(), nMaxlen));
	}
	Translate();
}

CStrSqlValue::CStrSqlValue(const std::string& sInit, size_t nMaxlen)
{
	m_Data = sInit;
	if (nMaxlen>0 && nMaxlen<m_Data.size())
	{
		m_Data.resize(CBasic::CheckChn(m_Data.c_str(), nMaxlen));
	}
	Translate();
}

CStrSqlValue::CStrSqlValue(int nInit)
{
	m_Data = CTrans::ITOS(nInit);
}

CStrSqlValue::CStrSqlValue(long nInit)
{
	m_Data = CTrans::ITOS((int)nInit);
}

CStrSqlValue::CStrSqlValue(size_t nInit)
{
	m_Data = CTrans::ITOS((int)nInit);
}

CStrSqlValue::CStrSqlValue(double dInit)
{
	m_Data = CTrans::FTOS(dInit);
}

/*!
 * CCgiOutValue-Member-Function-Definition
*/

CCgiOutValue::CCgiOutValue(int nInit)
{
	m_Data = CTrans::ITOS(nInit);
}

CCgiOutValue::CCgiOutValue(double dInit)
{
	m_Data = CTrans::FTOS(dInit);
}

CCgiOutValue::CCgiOutValue(const CStrBase& stInit) : m_Data(stInit.Data())
{
}

const std::string& CCgiOutValue::Data() const
{
	return m_Data;
}


/*!
 * The-Translate-Functions-Definition
*/

void CStrHtml::Translate()
{
	static std::string sSrc[] = { "&", " ", "'", "/", "<", ">", "\"", "\\", "\n", "\r" };
	static std::string sDst[] = {
		"&#38;",	//	|&|		-- must be the first one
		"&#160;",	//	| |
		"&#39;",	//	|'|
		"&#47;",	//	|/|
		"&#60;",	//	|<|
		"&#62;",	//	|>|
		"&#34;",	//	|"|
		"&#92;",	//	|\|
		"<BR>",		//	|\n|
		"<BR>"		//	|\r|
	};
	ReplaceString(m_Data, sSrc, sDst, sizeof(sSrc)/sizeof(sSrc[0]));
}

void CStrInput::Translate()
{
	static std::string sSrc[] = { "&", /*" ",*/ "'", "/", "<", ">", "\"", "\\", "\n", "\r" };
	static std::string sDst[] = {
		"&#38;",	//	|&|		-- must be the first one
	//	"&#160;",	//	| |		-- space can not be translated or it will make a mistake on the submit value 
		"&#39;",	//	|'|
		"&#47;",	//	|/|
		"&#60;",	//	|<|
		"&#62;",	//	|>|
		"&#34;",	//	|"|
		"&#92;",	//	|\|
		"",			//	|\n|
		""			//	|\r|
	};
	ReplaceString(m_Data, sSrc, sDst, sizeof(sSrc)/sizeof(sSrc[0]));
}

void CStrScript::Translate()
{
	std::size_t iRet = CBasic::CheckChn(m_Data.c_str(), m_Data.size());
	if(iRet != m_Data.size())
	{
		CBasic::StringChnCut(m_Data, iRet);
	}
	static std::string sSrc[] = { "\\",   "\"",    "'",    "\n",   "\r",  "\001"  };
	static std::string sDst[] = { "\\\\", "\\\"",  "\\'",  "\\n",  "\\r", "\\x01" };
	int nLen = m_Data.size();
	int nRep = sizeof(sSrc)/sizeof(sSrc[0]);
	for (int nIndex=0; nIndex<nLen; ++nIndex)
	{
		if (m_Data[nIndex] < 0)
		{
			++nIndex;
			continue;
		}
		for (int n=0; n<nRep; ++n)
		{
			if (m_Data[nIndex]==sSrc[n][0])
			{
				m_Data.replace(nIndex, 1, sDst[n]);
				nLen =  nLen+sDst[n].size()-1;
				nIndex = nIndex+sDst[n].size()-1;
				break;
			}
		}
	}
}

void CStrTArea::Translate()
{
	static std::string sSrc[] = { "&", /*" ",*/ "'", "/", "<", ">", "\"", "\\"};
	static std::string sDst[] = {
		"&#38;",	//	|&|		-- must be the first one
	//	"&#160;",	//	| |		-- space can not be translated or it will make a mistake on the submit value 
		"&#39;",	//	|'|
		"&#47;",	//	|/|
		"&#60;",	//	|<|
		"&#62;",	//	|>|
		"&#34;",	//	|"|
		"&#92;",	//	|\|
	};
	ReplaceString(m_Data, sSrc, sDst, sizeof(sSrc)/sizeof(sSrc[0]));
}

void CStrXml::Translate()
{
	m_Data = CBasic::XMLEncode(m_Data);
}

/*
void CStrUrl::Translate()
{
	static std::string sSrc[] = { "&", " ", "'", "/", "<", ">", "\"", "\\", "\n", "\r" };
	static std::string sDst[] = {
		"&#38;",	//	|&|		-- must be the first one
		"&#160;",	//	| |
		"&#39;",	//	|'|
		"&#47;",	//	|/|
		"&#60;",	//	|<|
		"&#62;",	//	|>|
		"&#34;",	//	|"|
		"&#92;",	//	|\|
		"",			//	|\n|
		""			//	|\r|
	};
	ReplaceString(m_Data, sSrc, sDst, sizeof(sSrc)/sizeof(sSrc[0]));
}
*/

void CStrSqlValue::Translate()
{
//#if 0	// 测试用,正式环境用MYSQL的函数
//	static std::string sSrc[] = { "\\",    "%",     "_",     "\"",    "'",    "\n",   "\r"  };
//	static std::string sDst[] = { "\\\\",  "\\%",  "\\_",  "\\\"",  "\\'",  "\\n",  "\\r" };
//	ReplaceString(m_Data, sSrc, sDst, sizeof(sSrc)/sizeof(sSrc[0]));
//#else
//	std::string sDst;
//	sDst.resize(m_Data.size()*2+1);
//	mysql_escape_string(const_cast<char *>(sDst.data()), m_Data.c_str(), m_Data.size());
//	m_Data = sDst.c_str();
//#endif
}

/************************************************************************/
