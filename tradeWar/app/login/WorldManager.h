/*
 * WorldManager.h
 *
 *  Created on: 2018年12月24日
 *      Author: Administrator
 */

#ifndef WORLD_MANAGER_H_
#define WORLD_MANAGER_H_

#include "Kernel.h"
#include "PbMessage.h"
#include "ProtocolInc.h"

#define WORLD_SOLDIER_NUM 5
#define WORLD_RANK_NUM 50
#define WORLD_PROTECT_CID 19

#define MAKE_POINT(x, y) ((static_cast<uint32_t>(x) << 16) | (y))

struct DataWorldCitySoldier {
	uint32_t id;
	uint32_t value;

	DataWorldCitySoldier() {
		id = 0;
		value = 0;
	}
	void Parse(const WorldBattle::WorldBattleSoldier &msg) {
		id = msg.id();
		value = msg.value();
	}
	void Serialize(WorldBattle::WorldBattleSoldier *msg) {
		msg->set_id(id);
		msg->set_value(value);
	}
};

struct DataWorldCityUser {
	uint32_t uid;
	uint32_t ts;
	vector<DataWorldCitySoldier> soldiers;
	string name;
	string fig;

	DataWorldCityUser() {
		uid = 0;
		ts = 0;
		soldiers.clear();
		name.clear();
		fig.clear();
	}
	void Parse(const WorldBattle::WorldBattleUser &msg) {
		uid = msg.uid();
		ts = msg.ts();
		for (int i = 0; i < msg.soldiers_size() && i < WORLD_SOLDIER_NUM; ++i) {
			DataWorldCitySoldier soldier;
			soldier.Parse(msg.soldiers(i));
			soldiers.push_back(soldier);
		}
		if (msg.has_name()) {
			name = msg.name();
		}
		if (msg.has_fig()) {
			fig = msg.fig();
		}
	}
	void Serialize(WorldBattle::WorldBattleUser *msg) {
		msg->set_uid(uid);
		msg->set_ts(ts);
		for (size_t i = 0; i < soldiers.size(); ++i) {
			soldiers[i].Serialize(msg->add_soldiers());
		}
		msg->set_name(name);
		msg->set_fig(fig);
	}
	void Clean() {
		uid = 0;
		ts = 0;
		soldiers.clear();
		name.clear();
		fig.clear();
	}
};

struct DataWorldCity {
	uint16_t id;
	vector<DataWorldCityUser> users;

	DataWorldCity() {
		id = 0;
	}

	void Parse(const WorldBattle::WorldBattleCity &msg) {
		id = msg.id();
		for (int i = 0; i < msg.users_size(); ++i) {
			DataWorldCityUser user;
			user.Parse(msg.users(i));
			users.push_back(user);
		}
	}
	void Serialize(WorldBattle::WorldBattleCity *msg) {
		msg->set_id(id);
		for (size_t i = 0; i < users.size(); ++i) {
			users[i].Serialize(msg->add_users());
		}
	}
};

struct DataWorldRankItem {
	uint32_t uid;
	uint16_t value;
	uint16_t cid;
	string name;
	string fig;

	DataWorldRankItem() {
		uid = 0;
		value = 0;
		cid = 0;
		name.clear();
		fig.clear();
	}
	void Parse(const WorldBattle::WorldBattleRank &msg) {
		uid = msg.uid();
		value = msg.value();
		cid = msg.cid();
		name = msg.name();
		fig = msg.fig();
	}
	void Serialize(WorldBattle::WorldBattleRank *msg) {
		msg->set_uid(uid);
		msg->set_value(value);
		msg->set_cid(cid);
		msg->set_name(name);
		msg->set_fig(fig);
	}
	inline bool operator<=(const DataWorldRankItem & item) const {
		return this->value <= item.value;
	}
	inline bool operator>(const DataWorldRankItem & item) const {
		return this->value > item.value;
	}
};

class WorldManager {
public:
	static WorldManager* getInstance() {
		static WorldManager _ins;
		return &_ins;
	}
	virtual ~WorldManager();
	bool init();
	bool load();
	bool save();
	bool doPacket(CNetPacket *p);
	bool doGetWorld(CNetPacket *p);
	bool doGetCity(CNetPacket *p);
	bool doGetSelf(CNetPacket *p);
	bool doSoldier(CNetPacket *p);
	bool doAttack(CNetPacket *p);
	bool doFinish(CNetPacket *p);
	bool doShopInfo(CNetPacket *p);
	bool doShopBuy(CNetPacket *p);
	bool doHarvest(CNetPacket *p);
	bool doRankInfo(CNetPacket *p);
	bool packetRank(IBuffer *buff);
	const list<DataWorldRankItem>& getRandData() const;
protected:
	WorldManager();
	bool sendWorld(uint32_t uid);
	bool sendCity(uint32_t uid, uint32_t cid);
	bool sendUser(uint32_t uid);
	bool sendShopInfo(uint32_t uid);
	bool onSoldier(uint32_t uid, byte ret);
	bool onAttackErr(uint32_t uid, uint32_t cid, uint32_t pid, uint32_t def);
	bool onFinish(uint32_t uid, uint32_t cid, uint32_t pid, byte ret);
	bool onShopBuy(uint32_t uid, byte ret);
	bool onHarvest(uint32_t uid, byte ret);
	bool onUserLost(uint32_t uid, uint32_t ts, uint16_t cid, uint16_t pid);
	bool onUserOccupy(uint32_t uid, uint16_t cid, uint16_t pid);
	bool addRank(uint32_t uid, uint32_t value, uint16_t cid);
	bool delRank(uint32_t uid);
	DataWorldCityUser* getUser(uint32_t cid, uint32_t pid);
	bool occupyProtect(uint32_t uid);
private:
	map<uint16_t, DataWorldCity> m_world;
	map<uint32_t, set<uint32_t> > m_occupy;
	list<DataWorldRankItem> m_rank;
	map<uint32_t, uint32_t> m_protect;
};

#endif /* WORLD_MANAGER_H_ */
