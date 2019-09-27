/*
 * WorldConfig.h
 *
 *  Created on: 2018年12月25日
 *      Author: Administrator
 */

#ifndef _WORLD_CONFIG_H_
#define _WORLD_CONFIG_H_

#include "Kernel.h"
#include "Award.h"

struct WorldConfigCity {
	uint8_t  type;
	uint16_t id;
	uint16_t soldier;
	uint16_t npcid;
	uint32_t power;
	uint32_t exp;
	vector<uint32_t> produce;
	string name;
	string npcname;

	WorldConfigCity() {
		type = 0;
		id = 0;
		soldier = 0;
		npcid = 0;
		power = 0;
		exp = 0;
		name.clear();
		npcname.clear();
	}
};

struct WorldConfigShop {
	uint16_t id;
	uint16_t times;
	uint32_t require;
	Award reward;

	WorldConfigShop() {
		id = 0;
		times = 0;
		require = 0;
	}
};

class WorldConfig {
	SINGLETON_CLASS(WorldConfig);
	bool init(const string &path);
	bool isExists(uint32_t cid, uint32_t pid) const;
	uint32_t getProduce(uint32_t cid, uint32_t pid, uint32_t ts) const;
	uint32_t getShopSize() const;
	const WorldConfigShop* getShopItem(uint32_t id) const;
	const map<uint16_t, WorldConfigCity>& getCity() const;
	uint32_t getNpcId(uint32_t cid) const;
	uint32_t getRank(uint32_t cid, uint32_t pid) const;
	const string* getName(uint32_t cid) const;
	const WorldConfigCity* getItem(uint32_t cid) const;
private:
	map<uint16_t, WorldConfigCity> m_citys;
	map<uint16_t, WorldConfigShop> m_shops;
};

#endif /* _WORLD_CONFIG_H_ */
