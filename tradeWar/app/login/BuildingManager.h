#ifndef _BUILDING_MANAGER_H_
#define _BUILDING_MANAGER_H_

#include "Building.h"
#include "DataBuilding.h"
#include "DataTower.h"
#include "IManager.h"

#define BASE_MAX_CAPACITY 25000
#define TOWER_STAR_MIN_ID 1000

class BuildingManager: public IManager {
public:
	BuildingManager();
	~BuildingManager();
public:
	bool load(uint32_t uid);
	bool setOneBuilding(uint32_t uid, uint32_t id, const string &data);
	bool setBuildingData(vector<DataBuilding> &db);
	bool save(uint32_t uid);
	bool doPacket(CNetPacket *packet);
	map<uint32_t, Building*>& getBuilding() {
		return m_buildings;
	}
	Building* getBuilding(uint32_t ud);
	Building* getBuildingByType(uint32_t type);
	Building* getBaseBuilding();
	bool sendBuildingList();
	bool sendTower();
	bool sendTowerStar();
	bool unlockTower(uint32_t id);
	uint32_t getResourceCapacity();
	uint32_t getResourceGoldCapacity();
	uint32_t getResourceMagicCapacity();
	uint32_t getBuildingLevel(uint32_t type);
	uint32_t getBuildingTypeCount(uint32_t buildingId);
	uint32_t getTowerLevel(uint32_t id);
private:
	bool doBuildingQueryAll(CNetPacket *packet);
	bool doBuildingQueryOne(CNetPacket *packet);
	bool doBuildingCreate(CNetPacket *packet);
	bool doBuildingMove(CNetPacket *packet);
	bool doBuildingUpgrade(CNetPacket *packet);
	bool doBuildingHarvest(CNetPacket *packet);
	bool doBuildingRemove(CNetPacket *packet);
	bool doTowerUpgrade(CNetPacket *packet);
	bool doTowerUpgradeStar(CNetPacket *packet);
	void onTowerUpgradeResp(byte ret, uint32_t id, uint32_t lv);
	void onTowerUpgradeStarResp(byte ret, uint32_t id, uint32_t lv);
	void release();
	bool doBuildingHarvest(uint32_t uid, Building* pBuilding, int ret, uint32_t addResource);
	byte upgradeOneBuilding(uint32_t ud, bool acc);
	bool loadTower(uint32_t uid);
	bool initTowerStar();
	bool saveTower(uint32_t id, bool isNew);
	bool saveTowerStar(uint32_t id, bool isNew);
	bool calcTowerCombat(uint32_t id, uint32_t lv);
	bool checkRelyBuilding(uint32_t id, uint32_t lv);
private:
	map<uint32_t, Building*> m_buildings;
	map<uint32_t, DataTower> m_tower;
	map<uint32_t, uint32_t> m_towerStar;
	uint32_t m_maxUd;
};

#endif /* _BUILDING_MANAGER_H_ */
