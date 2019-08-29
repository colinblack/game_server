/*
 * AdminManager.h
 *
 *  Created on: 2016年2月3日
 *      Author: asdf
 */

#ifndef SERVERS_APP_MAPOBJ_ADMINMANAGER_H_
#define SERVERS_APP_MAPOBJ_ADMINMANAGER_H_
#include "NetPacket.h"

struct AdminInfo
{
	string pwd;
	uint32_t skey;
	uint32_t level;
	uint32_t tryCount;
	AdminInfo()
	{
		pwd.clear();
		skey = level = tryCount = 0;
	}
};

class AdminManager
{
public:
	~AdminManager();
public:
	static AdminManager* getInstance()
	{
		static AdminManager am;
		return &am;
	}

	bool doAdmin(CNetPacket* packet);
	bool doSetAllHeroExitBattle(CNetPacket* packet);
	void addMoney(CNetPacket *packet);
	bool doKickUser(CNetPacket* packet);
	bool doKickUser(uint32_t kickUid);
	void doPrintLog(CNetPacket* packet);

	void doClient(CNetPacket* packet);
	void doClientResult(const string &data, CNetPacket* packet);
	void doLogin(CNetPacket* packet);
	void doExport(const Json::Value &data, Json::Value &result);
	void doImport(const Json::Value &data, Json::Value &result);
	void doQueryPay(const Json::Value &data, Json::Value &result);
	void doModifyPay(const Json::Value &data, Json::Value &result);
	void doEmail(const Json::Value &data, Json::Value &result);
	void doCharge(const Json::Value &data, Json::Value &result);
	void doQueryFriend(const Json::Value &data, Json::Value &result);
	void doAddFriend(const Json::Value &data, Json::Value &result);
	void doQueryEquip(const Json::Value &data, Json::Value &result);
	void doAddEquip(const Json::Value &data, Json::Value &result);
	void doBlockUser(const Json::Value &data, Json::Value &result);
protected:
	AdminManager();
	bool InitAdminInfo();
	bool CheckSkey(const Json::Value &data);

	bool exportSoldier(uint32_t uid, Json::Value &result);
	bool exportEquipment(uint32_t uid, Json::Value &result);
	bool exportBuilding(uint32_t uid, Json::Value &result);
	bool exportResource(uint32_t uid, Json::Value &result);
	bool exportUser(uint32_t uid, Json::Value &result);
	bool exportTask(uint32_t uid, Json::Value &result);
	bool exportPreTask(uint32_t uid, Json::Value &result);
	bool exportGate(uint32_t uid, Json::Value &result);
	bool exportState(uint32_t uid, Json::Value &result);
	bool exportHero(uint32_t uid, Json::Value &result);
	bool exportTroops(uint32_t uid, Json::Value &result);
	bool exportSkill(uint32_t uid, Json::Value &result);
	bool exportDefend(uint32_t uid, Json::Value &result);
	bool exportTower(uint32_t uid, Json::Value &result);
	bool exportActiveness(uint32_t uid, Json::Value &result);
	bool exportBoat(uint32_t uid, Json::Value &result);
	bool exportActivity(uint32_t uid, Json::Value &result);
	bool exportChargeHistory(uint32_t uid, Json::Value &result);
	bool exportGem(uint32_t uid, Json::Value &result);

	bool importSoldier(uint32_t uid, const Json::Value &result);
	bool importEquipment(uint32_t uid, const Json::Value &result);
	bool importBuilding(uint32_t uid, const Json::Value &result);
	bool importResource(uint32_t uid, const Json::Value &result);
	bool importUser(uint32_t uid, const Json::Value &result);
	bool importTask(uint32_t uid, const Json::Value &result);
	bool importPreTask(uint32_t uid, const Json::Value &result);
	bool importGate(uint32_t uid, const Json::Value &result);
	bool importState(uint32_t uid, const Json::Value &result);
	bool importHero(uint32_t uid, const Json::Value &result);
	bool importTroops(uint32_t uid, Json::Value &result);
	bool importSkill(uint32_t uid, Json::Value &result);
	bool importDefend(uint32_t uid, Json::Value &result);
	bool importTower(uint32_t uid, Json::Value &result);
	bool importActiveness(uint32_t uid, Json::Value &result);
	bool importBoat(uint32_t uid, Json::Value &result);
	bool importActivity(uint32_t uid, Json::Value &result);
	bool importChargeHistory(uint32_t uid, Json::Value &result);
	bool importGem(uint32_t uid, Json::Value &result);
private:
	map<string, AdminInfo> m_adminInfo;
};

#endif /* SERVERS_APP_MAPOBJ_ADMINMANAGER_H_ */


