#ifndef BAOT_CONFIG_H_
#define BAOT_CONFIG_H_

#include "Kernel.h"
#include "Award.h"

struct BoatConfig {
	byte type;
	uint16_t count;
	uint16_t ts;
	uint32_t box;
	vector<uint32_t> cost;
	vector<uint32_t> reward;

	BoatConfig() :
			type(0), count(0), ts(0), box(0) {
		cost.clear();
		reward.clear();
	}
};

struct BoatNpcItem {
	uint32_t id;
	uint32_t res;
	uint32_t power;

	BoatNpcItem() :
			id(0), res(0), power(0) {
	}
};

struct BoatNpcConfig {
	uint32_t exp;
	byte lv;
	vector<BoatNpcItem> npc;

	BoatNpcConfig() : exp(0), lv(0) {
		npc.clear();
	}
};

class CBoatConfig {
public:
	virtual ~CBoatConfig();
	static CBoatConfig *getInstance() {
		static CBoatConfig instance;
		return &instance;
	}
	bool init(const string &path);
	uint32_t getReward(uint32_t type, uint32_t lv);
	uint32_t getCost(uint32_t type, uint32_t lv);
	uint32_t getTransportTs(uint32_t type);
	uint32_t getCount(uint32_t type);
	uint32_t getBox(uint32_t type);
	const BoatNpcConfig* getBoatNpc(uint32_t lv);
	string getNpcName();
	bool getAllNpc(map<uint32_t, vector<uint64_t> > &data);
protected:
	CBoatConfig();
private:
	map<uint32_t, BoatConfig> m_config;
	map<uint32_t, BoatNpcConfig> m_npc;
	vector<string> m_npc_name;
};

#endif /* BAOT_CONFIG_H_ */
