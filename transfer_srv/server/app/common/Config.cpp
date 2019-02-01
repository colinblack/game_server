/*
 * Config.cpp
 *
 *  Created on: 2011-5-25
 *      Author: dada
 */

#include "Config.h"
#include "Common.h"

static map<string, string> g_config;

bool Config::Init(const string &path)
{
	g_config.clear();
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(path.c_str()))
	{
		return false;
	}
	if(!xmlConf.FindElem("configs") )
	{
		return false;
	}
	xmlConf.IntoElem();
	while(xmlConf.FindElem("config"))
	{
		string name = xmlConf.GetAttrib("name");
		string value = xmlConf.GetAttrib("value");
		g_config[name] = value;
	}
	return true;
}

bool Config::GetValue(string &value, const string &name)
{
	map<string, string>::iterator itr = g_config.find(name);
	if(itr == g_config.end())
	{
		return false;
	}
	value = itr->second;
	return true;
}

string Config::GetValue(const string &name)
{
	string value;
	Config::GetValue(value, name);
	return value;
}

bool Config::GetIntValue(int &value, const string &name)
{
	string sValue;
	if(!Config::GetValue(sValue, name))
	{
		return false;
	}
	return Convert::StringToInt(value, sValue);
}

int Config::GetIntValue(const string &name)
{
	int value;
	if(!Config::GetIntValue(value, name))
	{
		return 0;
	}
	return value;
}
