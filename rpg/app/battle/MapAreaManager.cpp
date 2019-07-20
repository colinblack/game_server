/*
 * MapAreaManager.cpp
 *
 *  Created on: 2013-6-5
 *      Author: Administrator
 */

#include "MapAreaManager.h"
#include "BattleInc.h"

MapAreaManager::MapAreaManager() {
}

MapAreaManager::~MapAreaManager() {
}

MapAreaManager *MapAreaManager::getInstance() {
	static MapAreaManager instance;
	return &instance;
}

bool MapAreaManager::init(const string &path) {
	Json::Value mapAreaStateConfValue;
	if (!FileToJson::fileToJson(path, mapAreaStateConfValue)) {
		error_log("mapAreaStateConfFile convert to json failed sceneCnfFile=%s", path.c_str());
		return false;
	}

	MapAreaState *pMapAreaState = NULL;
	int iCount = mapAreaStateConfValue.size();
	for (int i = 0; i < iCount; i++) {
		Json::Value &areaInfoValue = mapAreaStateConfValue[i]["areaInfo"];
		uint32_t mapId = mapAreaStateConfValue[i]["mapId"].asInt();

		pMapAreaState = new MapAreaState();
		if (!pMapAreaState) {
			error_log("new MapAreaState failed");
			return false;
		}

		if (!pMapAreaState->init(areaInfoValue)) {
			error_log("init areaInfo failed mapId = %u", mapId);
			return false;
		}

		m_mapAreaInfo[mapId] = pMapAreaState;
	}

	return true;
}

MapAreaState *MapAreaManager::getMapAreaInfo(uint32_t mapId) {
	map<uint32_t, MapAreaState *>::iterator itr = m_mapAreaInfo.find(mapId);
	if (itr != m_mapAreaInfo.end()) {
		return (itr->second);
	}

	return NULL;
}

