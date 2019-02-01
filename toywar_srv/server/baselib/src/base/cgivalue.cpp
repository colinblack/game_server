
/*!
 * \file cgivalue.cpp
 * \author FelitHuang
 * \date 2006-02-08
*/

#include "trans.h"
#include "basic.h"
#include "cgivalue.h"
#include "ctime.h"
#include <string.h>
#include <stdlib.h>
#include "fcgio.h"
#include "fcgi_config.h"

#include "staticdata.h"

#include "fcgi_stdio.h"	//add by bob

CCGIValue::CData& CCGIValue::GetData()
{
	static CData* s_xData = NULL;
	if (NULL == s_xData || 0 == STATICDATA::m_iCGIValueState)
	{
		if (NULL != s_xData)
		{
			delete s_xData;
		}
		s_xData = new CData();
		STATICDATA::m_iCGIValueState = 1;
	}
	return *s_xData;
}

int CCGIValue::CData::ParseStringValue(std::string& sValue, const std::string& sData, const std::string& sHead, const std::string& sTail, std::string::size_type bpos, std::string::size_type epos)
{
	/*
	 * 本函数用于获取sData中[bpos,epos]之间,sHead后面,sTail前面的内容
	 * 如果没有符合要求的数据,返回错误
	*/

	std::string::size_type nHead = sData.find(sHead, bpos);
	if (std::string::npos == nHead || (nHead += sHead.size()) > epos)
	{
		return -1;
	}
	
	std::string::size_type nTail = sData.find(sTail, nHead);
	if (std::string::npos == nTail || (nTail + sTail.size()) > epos)
	{
		return -1;
	}
	
	sValue = sData.substr(nHead, nTail-nHead);
	
	return 0;
}

CCGIValue::CData::CData()
{
	// GET-Method
	//int iTime0=CTime::GetCurrentuTime();
	CGIGetParam();
	//int iTime1=CTime::GetCurrentuTime();
	// POST-Multipart-Form-Data
	CGIMultipartParam();
	//int iTime2=CTime::GetCurrentuTime();
	// POST-Method
	CGIPostParam();
    //int iTime3=CTime::GetCurrentuTime();
//	QQSHOW_LOG((LV_DEBUG,"CCGIValue::CData "+CTrans::ITOS(iTime0)+" "
//                                            +CTrans::ITOS(iTime1)+" "
//                                            +CTrans::ITOS(iTime2)+" "
//                                            +CTrans::ITOS(iTime3)));
	// Additional element used in the search function
	#ifdef _DEBUG_
	CGIDebugParam();
	#endif
	CItem xItem;
	xItem.iType = TYPE_UNKNOW;
	m_vData.push_back(xItem);
}

void CCGIValue::CData::CGIDebugParam()
{
	//char* pcData = getenv("QUERY_STRING");
	unsigned char p = 0;
	char pcData[1024] = {0};
	for (;;)
	{
		p = getchar();
		if (p == '\n' || p == '\r')
		{
			break;
		}
		snprintf(pcData+strlen(pcData),sizeof(pcData),"%c",p);
	}
	
	if (NULL == pcData || pcData[0]==0)
	{
		return;
	}
	
	std::string sData(pcData);
	std::vector<std::string> vData;
	
	CBasic::StringSplit(sData, "&", vData);
	
	for (std::vector<std::string>::iterator itItem=vData.begin(); itItem!=vData.end(); ++itItem)
	{
		std::string::size_type cpos = itItem->find("=");
		CItem stData;
		stData.sName.insert(0, *itItem, 0, cpos);
		if (cpos != std::string::npos)
		{
			stData.sData.insert(0, *itItem, cpos+1, std::string::npos);
		}
		
		// The following processes will decode the CGI data and
		// convert the Unicode (%XX) format to the Multi-Bytes format.
		// The Unicode (%uXXXX) format may not be processed
		// depending on the CBasic::unescape function
		CBasic::StringReplace(stData.sName, "+", " ");		// replace the '+' with a space.
		CBasic::StringReplace(stData.sData, "+", " ");
		stData.sName = CBasic::unescape(stData.sName);	// %XX -> C
		stData.sData = CBasic::unescape(stData.sData);
		stData.iType = TYPE_GET;
		
		m_vData.push_back(stData);
	}
}
void CCGIValue::CData::CGIGetParam()
{
	/*
	 * The GET-Method data: name1=value1&name2=value2&name3=value3
	*/

	char* pcData = getenv("QUERY_STRING");
	
	if (NULL == pcData || pcData[0]==0)
	{
		return;
	}
	
	std::string sData(pcData);
	std::vector<std::string> vData;
	
	CBasic::StringSplit(sData, "&", vData);
	
	for (std::vector<std::string>::iterator itItem=vData.begin(); itItem!=vData.end(); ++itItem)
	{
		std::string::size_type cpos = itItem->find("=");
		CItem stData;
		stData.sName.insert(0, *itItem, 0, cpos);
		if (cpos != std::string::npos)
		{
			stData.sData.insert(0, *itItem, cpos+1, std::string::npos);
		}
		
		// The following processes will decode the CGI data and
		// convert the Unicode (%XX) format to the Multi-Bytes format.
		// The Unicode (%uXXXX) format may not be processed
		// depending on the CBasic::unescape function
		CBasic::StringReplace(stData.sName, "+", " ");		// replace the '+' with a space.
		CBasic::StringReplace(stData.sData, "+", " ");
		stData.sName = CBasic::unescape(stData.sName);	// %XX -> C
		stData.sData = CBasic::unescape(stData.sData);
		stData.iType = TYPE_GET;
		
		m_vData.push_back(stData);
	}
}

void CCGIValue::CData::CGIPostParam()
{
	/*
	 * The POST-Method data: name1=value1&name2=value2&name3=value3
	*/
   // int iTime0=CTime::GetCurrentuTime();
	char* pcData = getenv("REQUEST_METHOD");
	if (NULL == pcData || std::string("POST") != pcData)
	{
		return;
	}
	//int iTime1=CTime::GetCurrentuTime();
	pcData = getenv("CONTENT_TYPE");
	if (NULL != pcData && std::string::npos != std::string(pcData).find("multipart/form-data"))
	{
		return;
	}
	
	pcData = getenv("CONTENT_LENGTH");
	if (NULL == pcData)
	{
		return;
	}
   // int iTime2=CTime::GetCurrentuTime();
	
	int nlen = CTrans::STOI(pcData);
	if (0 == nlen)
	{
		return;
	}
	
	
	std::string sData;
	sData.resize(nlen);
	//int iTime3=CTime::GetCurrentuTime();

	//modify by bob,start
	//std::cin.read(const_cast<char *>(sData.data()), nlen);		// Read the data from the stdin
	FCGI_fread( const_cast<char *>(sData.data()), nlen, 1, FCGI_stdin );
	//modify by bob,end

	//int iTime4=CTime::GetCurrentuTime();
	std::vector<std::string> vData;
	
	CBasic::StringSplit(sData, "&", vData);
	//int iTime5=CTime::GetCurrentuTime();
	for (std::vector<std::string>::iterator itItem=vData.begin(); itItem!=vData.end(); ++itItem)
	{
		std::string::size_type cpos = itItem->find("=");
		CItem stData;
		stData.sName.insert(0, *itItem, 0, cpos);
		if (cpos != std::string::npos)
		{
			stData.sData.insert(0, *itItem, cpos+1, std::string::npos);
		}
		
		CBasic::StringReplace(stData.sName, "+", " ");
		CBasic::StringReplace(stData.sData, "+", " ");
		stData.sName = CBasic::unescape(stData.sName);
		stData.sData = CBasic::unescape(stData.sData);
		stData.iType = TYPE_POSTURL;
		
		m_vData.push_back(stData);
	}
   // int iTime6=CTime::GetCurrentuTime();
//    QQSHOW_LOG((LV_DEBUG,"CData::CGIPostParam "+CTrans::ITOS(iTime0)+" "
//                                            +CTrans::ITOS(iTime1)+" "
//                                            +CTrans::ITOS(iTime2)+" "
//                                            +CTrans::ITOS(iTime3)+" "
//                                            +CTrans::ITOS(iTime4)+" "
//                                            +CTrans::ITOS(iTime5)+" "
//                                            +CTrans::ITOS(iTime6)));
}

void CCGIValue::CData::CGIMultipartParam()
{
	/*
	 * The POST-Multipart-Form-Data:
	   boundary(endl)
	   head-infomation(endl)
	   [head-information(endl)]
	   (endl)
	   data
	   (endl)
	   boundary--
	*/

	char* pcData = getenv("REQUEST_METHOD");
	if (NULL == pcData || std::string("POST") != pcData)
	{
		return;
	}
	
	pcData = getenv("CONTENT_TYPE");
	if (NULL == pcData || std::string::npos == std::string(pcData).find("multipart/form-data"))
	{
		return;
	}
	
	
	std::string sBKeyWord("boundary=");
	std::string sBoundary(pcData);
	
	std::string::size_type cpos = sBoundary.find(sBKeyWord);
	if (std::string::npos == cpos)
	{
		return;
	}
	
	sBoundary.erase(0, cpos+sBKeyWord.size());
	
	pcData = getenv("CONTENT_LENGTH");
	
	if (NULL == pcData)
	{
		return;
	}
	
	int nlen = CTrans::STOI(pcData);
	if (0 == nlen)
	{
		return;
	}
	
	std::string sData;
	sData.resize(nlen);
	
#ifdef WIN32 // ###########################
	setmode(fileno(stdin), O_BINARY);
	_fmode = O_BINARY;
#endif // WIN32 ###########################
	
	
	//modify by bob,start
	//std::cin.read(const_cast<char *>(sData.data()), nlen);
	FCGI_fread( const_cast<char *>(sData.data()), nlen, 1, FCGI_stdin );
	//modify by bob,end

	std::vector<std::string::size_type> vbpos;
	std::vector<std::string::size_type> vepos;
	vbpos.reserve(32);
	vepos.reserve(32);
	
	// Check the endl type: "\n" or "\r\n"
	std::string::size_type fpos = sData.find("\n");
	std::string sLend = (std::string::npos==fpos) ? ("\r\n") : (fpos>0 && sData[fpos-1]=='\r') ? ("\r\n") : ("\n");
	std::string sDend(sLend+sLend);
	
	std::string sNameHead("name=\"");		// Beginning of the CGI name
	std::string sNameTail("\"");			// Ended with a '"'
	std::string sFileHead("filename=\"");	// Beginning of the File-name (If it's a file)
	std::string sFileTail("\"");			// Ended with a '"'
	
	// Find out all the data beginning positions and ending positions
	cpos = 0;
	vbpos.push_back(cpos);
	while (std::string::npos != (cpos=sData.find(sBoundary, cpos)))
	{
		std::string::size_type xpos = cpos;
		cpos += sBoundary.size();
		std::string::size_type epos = sData.rfind(sLend, xpos);
		std::string::size_type bpos = sData.find(sLend, cpos);
		
		if (std::string::npos == epos && std::string::npos == bpos)
		{
			vbpos[vbpos.size()-1] = cpos;
		}
		else if (std::string::npos == epos)
		{
			vbpos[vbpos.size()-1] = cpos;
		}
		else if (std::string::npos == bpos)
		{
			vepos.push_back(epos);
			vbpos.push_back(cpos);
		}
		else
		{
			vepos.push_back(epos);
			vbpos.push_back(bpos+sLend.size());
		}
	}	
	vepos.push_back(sData.size());
	
	for (std::vector<std::string::size_type>::size_type nIndex=0; nIndex<vbpos.size(); ++nIndex)
	{
		CItem stData;
		
		std::string::size_type bpos = vbpos[nIndex];
		std::string::size_type epos = vepos[nIndex];
		
		if (epos < bpos+32)
		{
			continue;	// not valid data
		}
		
		std::string::size_type dpos = sData.find(sDend, bpos);
		
		if (std::string::npos == dpos || dpos >= epos)
		{
			continue;
		}
		
		if (0 != ParseStringValue(stData.sName, sData, sNameHead, sNameTail, bpos, dpos))
		{
			continue;
		}
		
		ParseStringValue(stData.sValue, sData, sFileHead, sFileTail, bpos, dpos);
		
		stData.sData = sData.substr(dpos+sDend.size(), epos-dpos-sDend.size());

		stData.iType = TYPE_POSTFILE;
		
		m_vData.push_back(stData);
	}
}

const CCGIValue::CData::CItem& CCGIValue::CData::GetData(const std::string& sName)
{
	std::list<CCGIValue::CData::CItem>::reverse_iterator s_itRBegin = m_vData.rbegin();
	
	s_itRBegin->sName = sName;
	
	std::list<CCGIValue::CData::CItem>::iterator itItem=m_vData.begin();
	
	while (itItem!=m_vData.end() && itItem->sName!=sName)
	{
		++itItem;
	}
	
	return *itItem;
}

void CCGIValue::CData::GetData(const std::string& sName, std::vector<const CCGIValue::CData::CItem*>& vValue)
{
	std::list<CCGIValue::CData::CItem>::reverse_iterator s_itRBegin = m_vData.rbegin();
	
	s_itRBegin->sName = ("");
	
	for (std::list<CCGIValue::CData::CItem>::iterator itItem=m_vData.begin(); itItem!=m_vData.end(); ++itItem)
	{			
		if (itItem->sName == sName)
		{
			vValue.push_back(&*itItem);
		}
	}
}

int CCGIValue::CheckExists(const std::string& sName)
{
	return (&GetData().GetData(sName) != &*GetData().m_vData.rbegin()) ? (0) : (-1);
}

const std::string& CCGIValue::GetValue(const std::string& sName)
{
	return GetData().GetData(sName).sData;
}

const std::string& CCGIValue::GetFileName(const std::string& sName)
{
	return GetData().GetData(sName).sValue;
}

const std::string& CCGIValue::GetFileData(const std::string& sName)
{
	return GetData().GetData(sName).sData;
}

void CCGIValue::GetValue(const std::string& sName, std::vector<std::string>& vValue)
{
	std::vector<const CCGIValue::CData::CItem*> vData;
	GetData().GetData(sName, vData);
	
	for (std::vector<const CCGIValue::CData::CItem*>::iterator itItem=vData.begin(); itItem!=vData.end(); ++itItem)
	{
		vValue.push_back((*itItem)->sData);
	}
}

void CCGIValue::GetFileName(const std::string& sName, std::vector<std::string>& vValue)
{
	std::vector<const CCGIValue::CData::CItem*> vData;
	GetData().GetData(sName, vData);
	for (std::vector<const CCGIValue::CData::CItem*>::iterator itItem=vData.begin(); itItem!=vData.end(); ++itItem)
	{
		vValue.push_back((*itItem)->sValue);			
	}
}

void CCGIValue::GetFileData(const std::string& sName, std::vector<std::string>& vValue)
{
	std::vector<const CCGIValue::CData::CItem*> vData;
	GetData().GetData(sName, vData);
	for (std::vector<const CCGIValue::CData::CItem*>::iterator itItem=vData.begin(); itItem!=vData.end(); ++itItem)
	{
		vValue.push_back((*itItem)->sData);			
	}
}


