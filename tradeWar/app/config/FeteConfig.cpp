/*
 * FeteConfig.cpp
 *
 *  Created on: 2016年4月13日
 *      Author: Administrator
 */

#include "FeteConfig.h"

CFeteConfig::CFeteConfig() {
}

CFeteConfig::~CFeteConfig() {
}

bool CFeteConfig::init(const string &path)
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
	if(!xmlConf.FindElem("fetes") )
	{
		error_log("find_node_fetes_fail");
		return false;
	}
	xmlConf.IntoElem();
	m_totalWeight = 0;
	while(xmlConf.FindElem("baoji"))
	{
		FetConfig config;
		config.bj = String::s2i(xmlConf.GetAttrib("bj"),0);
		config.weight = String::s2i(xmlConf.GetAttrib("rate"),0);
		m_totalWeight += config.weight;
		m_config.push_back(config);
	}

	if(m_totalWeight == 0)
	{
		error_log("weight error");
		return false;
	}
	return true;
}

byte CFeteConfig::getBj()
{
	uint32_t randData = rand()%m_totalWeight;
	uint32_t curWeight = 0;
	for(vector<FetConfig>::iterator it = m_config.begin(); it != m_config.end(); ++it)
	{
		curWeight += it->weight;
		if(randData < curWeight)
		{
			return it->bj;
		}
	}

	return 1;
}
