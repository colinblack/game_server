/*
 * OpenPlatfrom.cpp
 *
 *  Created on: 2011-5-16
 *      Author: dada
 */

#include "OpenPlatform.h"
#include "TestPlatform.h"
#include "FacebookPlatform.h"
#include "TencentPlatform.h"
#include "C6GamePlatform.h"

static bool g_bInitPlatform = false;
static bool g_bMultiPlatform = true;
static PlatformType g_currPlatformType = PT_UNKNOW;
static IOpenPlatform *g_pCurrPlatform = NULL;
static map<string, string> g_mapPlatformConfig;
static map<string, IOpenPlatform *> g_mapPlatform;

IOpenPlatform *InitPlatform(const string &configPath)
{
	//load config
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(configPath.c_str()))
	{
		fatal_log("[load platform config fail][path=%s]", configPath.c_str());
		return NULL;
	}
	if(!xmlConf.FindElem("app"))
	{
		fatal_log("[parse platform config fail][path=%s,error=parse_config_fail]", configPath.c_str());
		return NULL;
	}
	xmlConf.IntoElem();

	map<string, string> config;
	while(xmlConf.FindElem("param"))
	{
		string name = xmlConf.GetAttrib("name");
		string value = xmlConf.GetAttrib("value");
		config[name] = value;
	}

	//init platform
	int nPlatform;
	if(!Convert::StringToInt(nPlatform, config["platform"]))
	{
		fatal_log("[parse platform config fail][path=%s, platform=%s,error=get_platform_type_fail]",
				configPath.c_str(), config["platform"].c_str());
		return NULL;
	}
	IOpenPlatform *pPlatform;
	switch(nPlatform)
	{
	case PT_TEST:
		pPlatform = new CTestPlatform();
		break;
	case PT_QZONE:
	case PT_WB_AND:
	case PT_WB_IOS:
	case PT_WX_MINI:
		pPlatform = new CTencentPlatform();
		break;
	case PT_FACEBOOK:
		pPlatform = new CFacebookPlatform();
		break;
	case PT_C6_IOS:
		pPlatform = new CC6GamePlatform();
		break;
	default:
		fatal_log("[parse platform config fail][path=%s, error=unknow_platform, platform=%s]",
				configPath.c_str(), config["platform"].c_str());
		return NULL;
	}

	if(pPlatform->Initialize(config["appid"], config["appkey"], config) != 0)
	{
		fatal_log("[Init platform fail][error=init_platform_fail, platform=%d, appid=%s, appkey=%s]",
				nPlatform, config["appid"].c_str(), config["appkey"].c_str());
		delete pPlatform;
		return NULL;
	}

	return pPlatform;
}

//获取当前平台对象
IOpenPlatform *OpenPlatform::GetPlatform()
{
	return g_pCurrPlatform;
}

//获取当前平台类型
PlatformType OpenPlatform::GetType()
{
	return g_currPlatformType;
}

bool OpenPlatform::Init(const string &path)
{
	string config_path = Config::GetValue("platform") + path + "_platform.xml";
	g_pCurrPlatform = InitPlatform(config_path);
	if(g_pCurrPlatform == NULL){
		return false;
	}

	return true;
}

//更新当前平台类型
bool OpenPlatform::Reset()
{
	if(!g_bInitPlatform)
	{
		//init
		g_bInitPlatform = true;
		string mappingPath;
		if(!Config::GetValue(mappingPath, CONFIG_PLATFORM_MAPPING))
		{
			//single platform init
			g_bMultiPlatform = false;
			info_log("[get platform mapping fail][mode=single_platform]");
			string configPath;
			if(!Config::GetValue(configPath, CONFIG_PLATFORM))
			{
				fatal_log("[get config fail][config_name=%s]", CONFIG_PLATFORM);
				return false;
			}
			g_pCurrPlatform = InitPlatform(configPath);
			if(g_pCurrPlatform == NULL)
			{
				return false;
			}
			g_currPlatformType = g_pCurrPlatform->GetPlatformType();
			return true;
		}

		//multi platform init
		info_log("[get platform mapping ok][mode=multi_platform]");
		CMarkupSTL xmlConf;
		if(!xmlConf.Load(mappingPath.c_str()))
		{
			fatal_log("[load platform mapping fail][path=%s]", mappingPath.c_str());
			return false;
		}
		if(!xmlConf.FindElem("mapping"))
		{
			fatal_log("[parse platform mapping fail][path=%s,error=parse_xml_fail]", mappingPath.c_str());
			return false;
		}
		xmlConf.IntoElem();
		map<string, string> config;
		while(xmlConf.FindElem("platform"))
		{
			string name = xmlConf.GetAttrib("host");
			string value = xmlConf.GetAttrib("config");
			if(name.empty() || value.empty())
			{
				fatal_log("[invalid platform mapping][path=%s,host=%s,config=%s]",
						mappingPath.c_str(), name.c_str(), value.c_str());
			}
			else
			{
				String::ToLower(name);
				g_mapPlatformConfig[name] = value;
			}
		}
	}

	//single platform
	if(!g_bMultiPlatform)
	{
		return g_pCurrPlatform != NULL;
	}

	//multi platform
	g_pCurrPlatform = NULL;
	g_currPlatformType = PT_UNKNOW;
	char *pHost = getenv("SERVER_NAME");
	if(pHost == NULL)
	{
		error_log("[server_name_empty][server_name=<null>]");
		return false;
	}
	string host = pHost;
	String::ToLower(host);
	map<string, IOpenPlatform *>::iterator itrMapPlatform;
	itrMapPlatform = g_mapPlatform.find(host);
	if(itrMapPlatform != g_mapPlatform.end())
	{
		//platform has inited
		g_pCurrPlatform = itrMapPlatform->second;
		if(g_pCurrPlatform == NULL)
		{
			error_log("[invalid_platform_type][host=%s,platform=NULL]", host.c_str());
			return false;
		}
		g_currPlatformType = g_pCurrPlatform->GetPlatformType();
		return true;
	}

	//init platform
	map<string, string>::iterator itrMapConfig;
	itrMapConfig = g_mapPlatformConfig.find(host);
	if(itrMapConfig == g_mapPlatformConfig.end())
	{
		error_log("[unknow_host][host=%s]", host.c_str());
		return false;
	}
	g_pCurrPlatform = InitPlatform(itrMapConfig->second);
	if(g_pCurrPlatform == NULL)
	{
		return false;
	}
	g_currPlatformType = g_pCurrPlatform->GetPlatformType();
	g_mapPlatform[host] = g_pCurrPlatform;
	return true;
}

PlatformType OpenPlatform::GetType(int pf, int platform) {
	if (pf == PF_TEST) {
		return PT_TEST;
	} else if (pf == PF_WB) {
		if (platform == OSPT_AND) {
			return PT_WB_AND;
		} else if (platform == OSPT_IOS) {
			return PT_WB_IOS;
		}
	} else if (pf == PF_WX) {
		return PT_WX_MINI;
	}
	else if(pf == PF_C6){
		return PT_C6_IOS;
	}
	else if(pf == PF_QQ) {
		return PT_QQ_MINI;
	}

	return PT_UNKNOW;
}
