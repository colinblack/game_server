/*
 * CgiUtil.cpp
 *
 *  Created on: 2011-5-27
 *      Author: dada
 */

#include "CgiUtil.h"

void CgiUtil::GetRequestMethod(string &method)
{
	const char *pMethod = getenv("REQUEST_METHOD");
	if(pMethod == NULL)
	{
		method.clear();
	}
	else
	{
		method = pMethod;
	}
}

void CgiUtil::GetContentType(string &contentType)
{
	const char *pContentType = getenv("CONTENT_TYPE");
	if(pContentType == NULL)
	{
		contentType.clear();
	}
	else
	{
		contentType = pContentType;
	}
}

void CgiUtil::GetRequestParams(map<string, string> &params)
{
	params.clear();
	const char *pQueryString = getenv("QUERY_STRING");
	if(pQueryString == NULL)
	{
		return;
	}
	vector<string> items;
	CBasic::StringSplitTrim(pQueryString, "&", items);
	for(vector<string>::iterator itr = items.begin(); itr != items.end(); itr++)
	{
		string::size_type mid = itr->find('=');
		if(mid == string::npos)
		{
			params[*itr] = "";
		}
		else
		{
			params[itr->substr(0, mid)] = itr->substr(mid + 1);
		}
	}
}

void CgiUtil::GetPostData(string &data)
{
	const char *pcLength = getenv("CONTENT_LENGTH");
	if(pcLength == NULL)
	{
		data.clear();
		return;
	}
	unsigned uLength;
	if(!Convert::StringToUInt(uLength, pcLength))
	{
		data.clear();
		return;
	}
	data.resize(uLength);
	FCGI_fread(const_cast<char *>(data.c_str()), uLength, 1, FCGI_stdin);
}

bool CgiUtil::PrintText(const string &text)
{
	/*FCGI_printf(
		"Content-type: text/html; charset=UTF-8\r\n"
		"Pragma: no-cache\r\n\r\n"
		"%s",
		text.c_str()
		);*/
	FCGI_printf(
		"Content-type: text/html; charset=UTF-8\r\n"
		"Cache-control: no-store, no-cache, must-revalidate, post-check=0, pre-check=0\r\n\r\n"
		"%s",
		text.c_str()
		);
	return true;
}

bool CgiUtil::PrintText(const string &text,const vector<string>& headers)
{
	string hs;
	for(vector<string>::const_iterator it=headers.begin();it!=headers.end();++it)
		hs += *it + "\n";
	hs += text;
	FCGI_printf(
		"Content-type: text/html; charset=UTF-8\r\n"
		"Cache-control: no-store, no-cache, must-revalidate, post-check=0, pre-check=0\r\n\r\n"
		"%s",
		hs.c_str()
		);
	return true;
}

bool CgiUtil::PrintFormat(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	FCGI_vprintf(format, args);
	va_end(args);
	return true;
}

bool CgiUtil::PrintJson(const Json::Value &json)
{
	return PrintText(Json::FastWriter().write(json));
}

bool CgiUtil::CompressPrint(const string &text)
{
	const char *pAcceptEncoding = getenv("HTTP_ACCEPT_ENCODING");
	if(pAcceptEncoding == NULL)
	{
		return PrintText(text);
	}
	string acceptEncoding = pAcceptEncoding;
	if(acceptEncoding.find("gzip") == string::npos)
	{
		return PrintText(text);
	}
	if(text.size() < 1000)
	{
		return PrintText(text);
	}
	string result;
	if(!Compress::GzipCompress(result, text))
	{
		return PrintText(text);
	}
	if(result.size() >= text.size() / 5 * 4)
	{
		return PrintText(text);
	}
	/*char head[] = "Content-type: text/html; charset=UTF-8\r\n"
			"Content-Encoding: gzip\r\n"
			"Pragma: no-cache\r\n\r\n";*/
	char head[] = "Content-type: text/html; charset=UTF-8\r\n"
			"Content-Encoding: gzip\r\n"
			"Cache-control: no-store, no-cache, must-revalidate, post-check=0, pre-check=0\r\n\r\n";
	FCGI_fwrite((void *)head, strlen(head), 1, FCGI_stdout);
	FCGI_fwrite((void *)result.c_str(), result.size(), 1, FCGI_stdout);
	return true;
}

bool CgiUtil::HttpRedirect(const string &url)
{
	FCGI_printf(
		"Content-type: text/html; charset=UTF-8\r\n"
		"Pragma: no-cache\r\n"
		"Status: 302 Found\r\n"
		"Location: %s\r\n\r\n",
		url.c_str()
		);
	return true;
}

bool CgiUtil::ScriptRedirect(const string &url)
{
	FCGI_printf(
		"Content-type: text/html; charset=UTF-8\r\n"
		"Pragma: no-cache\r\n\r\n"
		"<script type='text/javascript'>window.location.href='%s';</script>\r\n",
		url.c_str()
		);
	return true;
}

bool CgiUtil::ScriptTopRedirect(const string &url)
{
	FCGI_printf(
		"Content-type: text/html; charset=UTF-8\r\n"
		"Pragma: no-cache\r\n\r\n"
		"<script type='text/javascript'>top.location.href='%s';</script>\r\n",
		url.c_str()
		);
	return true;
}

