/*
 * Config.cpp
 *
 *  Created on: 2011-5-25
 *      Author: dada
 */

#include "Config.h"
#include "Common.h"
#include "../kernel/AppDefine.h"

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

	xmlConf.ResetMainPos();
	//各服IP和端口配置
	if(xmlConf.FindElem("servers") )
	{
		xmlConf.IntoElem();
		while(xmlConf.FindElem("config"))
		{
			string name = xmlConf.GetAttrib("name");
			string value = xmlConf.GetAttrib("value");
			g_config[name] = value;
		}
		xmlConf.OutOfElem();
	}

	// 获取所有服务器共享配置
	if(!getShareConf("server_conf"))
	{
		error_log("getShareConf server_conf fail");
		return false;
	}
	if(!getShareConf("common_file"))
	{
		error_log("getShareConf common_file fail");
		return false;
	}
	if(!getShareConf("front_back_file"))
	{
		error_log("getShareConf front_back_file fail");
		return false;
	}
	return true;
}
bool Config::getShareConf(const string& confName)
{
	if(g_config.find(confName) != g_config.end())
	{
		CMarkupSTL xmlConf;
		if(!xmlConf.Load(g_config[confName].c_str()))
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
			if(g_config.find(name) == g_config.end())
			{
				g_config[name] = value;
			}
		}
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
	if(value.empty())
	{
		error_log("config %s not exist", name.c_str());
	}
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

unsigned int Config::GetZoneByUID(unsigned int uid)
{
	return (uid - UID_MIN) / UID_ZONE + 1;
}
