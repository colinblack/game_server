/*
 * MapConfig.cpp
 *
 *  Created on: 2015-9-24
 *      Author: Administrator
 */
#include "MapsConfig.h"

MapsConfig::MapsConfig()
{

}

MapsConfig::~MapsConfig()
{

}

bool MapsConfig::init(const string & path)
{
	string mapsPath = Config::GetValue(MAP_CONFIG_PATH);
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
	while(xmlConf.FindElem("map"))
	{
		MapConfig sMapConfig;
		string mapIdStr = xmlConf.GetAttrib("id");
		uint32_t mapId = CTrans::STOI(mapIdStr);
		string mapTypeStr = xmlConf.GetAttrib("type");
		uint32_t mapType = CTrans::STOI(mapTypeStr);
		string name = xmlConf.GetAttrib("name");
		string datafile = xmlConf.GetAttrib("datafile");
		string maxLookersStr = xmlConf.GetAttrib("maxLookers");
		uint32_t maxLookers = CTrans::STOI(maxLookersStr);
		string maxPlayersStr = xmlConf.GetAttrib("maxPlayers");
		uint32_t maxPlayers = CTrans::STOI(maxPlayersStr);
		sMapConfig.mapId = mapId;
		sMapConfig.mapType = mapType;
		sMapConfig.maxLookers = maxLookers;
		sMapConfig.maxPlayers = maxPlayers;
		sMapConfig.mapName = name;
		sMapConfig.dataFile = mapsPath + datafile;
		m_config.push_back(sMapConfig);
	}
	return true;
}

bool MapsConfig::getConfig(uint32_t mapId,MapConfig & sCon)
{
	for(uint32_t i=0; i<m_config.size(); i++)
	{
		if(m_config[i].mapId == mapId)
		{
			sCon = m_config[i];
			return true;
		}
	}
	return false;
}

vector<MapConfig> & MapsConfig::getAllConfig()
{
	return m_config;
}
