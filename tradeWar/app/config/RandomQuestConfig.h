/*
 * RandomQuestConfig.h
 *
 *  Created on: 2018年11月30日
 *      Author: Administrator
 */

#ifndef RANDOM_QUEST_CONFIG_H_
#define RANDOM_QUEST_CONFIG_H_

#include "Kernel.h"
#include "Award.h"

struct RandomQuestReward {
	uint32_t id;
	uint32_t cost;
	Award reward;

	RandomQuestReward() {
		id = 0;
		cost = 0;
	}
};

struct RandomQuestSoldier {
	uint32_t id;
	vector<uint32_t> soldier;

	RandomQuestSoldier() {
		id = 0;
		soldier.clear();
	}
};

struct RandomQuestBoxRandom {
	uint32_t rate;
	Award reward;

	RandomQuestBoxRandom() {
		rate = 0;
	}
};

struct RandomQuestBoxLevel {
	byte lv;
	byte count;
	uint16_t cost;
	uint32_t rs1;
	uint32_t rs2;
	vector<uint16_t> skill;

	RandomQuestBoxLevel() {
		lv = 0;
		count = 0;
		cost = 0;
		rs1 = 0;
		rs2 = 0;
		skill.clear();
	}
};

struct RandomQuest {
	uint32_t id;
	vector<uint32_t> rate;
	vector<uint32_t> rateKey;
	Award reward1;
	Award reward2;

	RandomQuest() {
		id = 0;
		rate.clear();
		rateKey.clear();
	}
};



class RandomQuestConfig {
	SINGLETON_CLASS(RandomQuestConfig);
	enum {
		e_RandomQuestTypeReward = 1,
		e_RandomQuestTypeSoldier = 2
	};
	bool init(const string &path);
	const RandomQuest* getQuestByLv(uint32_t lv) const;
	const RandomQuest* getQuestById(uint32_t id) const;
	const RandomQuestReward* getReward(uint32_t id) const;
	const RandomQuestSoldier* getSoldier(uint32_t id) const;
	const RandomQuestBoxLevel* getBoxLevel(uint32_t lv) const;
	const Award* getBoxRandom() const;
	bool randomReward(uint32_t id, uint32_t &id1, uint32_t &id2);
	bool randomSoldier(uint32_t id, uint32_t &id1);
private:
	map<uint32_t, RandomQuest> m_quest;
	map<uint32_t, RandomQuestReward> m_reward;
	map<uint32_t, RandomQuestSoldier> m_soldier;
	map<uint32_t, RandomQuestBoxLevel> m_boxLevel;
	vector<RandomQuestBoxRandom> m_boxRandom;
};

#endif /* RANDOM_QUEST_CONFIG_H_ */

