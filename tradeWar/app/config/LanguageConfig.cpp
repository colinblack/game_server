/*
 * LanguageConfig.cpp
 *
 *  Created on: 2015-12-28
 *      Author: Administrator
 */

#include "LanguageConfig.h"

LanguageConfig* LanguageConfig::getInstance()
{
	static LanguageConfig langConfig;
	return &langConfig;
}

const string& LanguageConfig::getLang(const string& key) const
{
	static string empty="";

	map<string,string>::const_iterator it = m_langMap.find(key);
	if(it == m_langMap.end()){
		return empty;
	}

	return it->second;
}

bool LanguageConfig::init(const string & path)
{
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(path.c_str()))
	{
		error_log("load_fail");
		return false;
	}

	if(!xmlConf.FindElem("content") )
	{
		error_log("find_node_content_fail");
		return false;
	}

	xmlConf.IntoElem();
	while(xmlConf.FindElem("tips"))
	{
		string idStr = xmlConf.GetAttrib("id");
		string msg = xmlConf.GetData();
		m_langMap[idStr] = msg;
	}

	return true;
}
