/*
 * MapConfig.h
 *
 *  Created on: 2015-9-24
 *      Author: Administrator
 */

#ifndef MAPCONFIG_H_
#define MAPCONFIG_H_

#include "Kernel.h"

struct MapConfig
{
	uint32_t mapId;
	uint32_t mapType;	//地图类型 1v1..NvN..
	uint32_t mapWidth;
	uint32_t mapHeight;
	uint32_t maxLookers;//最多观战人数
	uint32_t maxPlayers;//最多战斗人数
	string mapName;
	string dataFile;
	MapConfig()
	{
		mapType = 0;
		mapId = 0;
		mapWidth = 0;
		mapHeight = 0;
		maxLookers = 0;
		maxPlayers = 0;
	}
	bool operator ==(const MapConfig & other)
	{
		return mapId == other.mapId;
	}
};

class MapsConfig
{
private:
	MapsConfig();
public:
	~MapsConfig();
	static MapsConfig* getInstance()
	{
		static MapsConfig instance;
		return & instance;
	}
	bool init(const string &path);
	bool getConfig(uint32_t mapId,MapConfig & sCon);
	vector<MapConfig> & getAllConfig();
private:
	vector<MapConfig> m_config;
};

#endif /* MAPCONFIG_H_ */
