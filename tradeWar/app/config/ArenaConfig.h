/*
 * ArenaConfig.h
 *
 *  Created on: 2019年3月1日
 *      Author: Administrator
 */

#ifndef ARENA_CONFIG_H_
#define ARENA_CONFIG_H_

#include "Kernel.h"
#include "Award.h"

struct ArenaCfgRank {
	uint16_t from;
	uint16_t to;
	Award reward;

	ArenaCfgRank() {
		from = 0;
		to = 0;
	}
};

struct ArenaCfgShop {
	uint8_t id;
	uint8_t type;
	uint16_t count;
	uint32_t require;
	Award reward;

	ArenaCfgShop() {
		id = 0;
		type = 0;
		count = 0;
		require = 0;
	}
};

struct ArenaCfgNpc {
	uint16_t from;
	uint16_t to;
	uint32_t id;
	uint32_t power;
	uint32_t exp;
	string name;

	ArenaCfgNpc() {
		from = 0;
		to = 0;
		id = 0;
		power = 0;
		exp = 0;
		name.clear();
	}
};

enum ArenaCfgShopType {
	ArenaCfgShopType_A = 1,
	ArenaCfgShopType_B = 2
};

class ArenaConfig {
	SINGLETON_CLASS(ArenaConfig);
	map<uint8_t, ArenaCfgShop> m_shops;
	map<byte, vector<byte> > m_shop_type;
	vector<ArenaCfgRank> m_ranks;
	vector<ArenaCfgNpc> m_npc;
	vector<uint32_t> m_energy;
	byte m_shop_size;
	byte m_shop_refresh_cost;
public:
	bool init(const string &path);
	bool initShop(const Json::Value *v, byte type);
	const Award* getRankReward(uint32_t r) const;
	const ArenaCfgShop* getShop(uint32_t id) const;
	const ArenaCfgNpc* getNpc(uint32_t rank) const;
	uint32_t getShopCost() const;
	uint32_t getBuyEnergyCost(byte cnt);
	bool refreshShop(vector<byte> &ids);
};

#endif /* ARENA_CONFIG_H_ */
