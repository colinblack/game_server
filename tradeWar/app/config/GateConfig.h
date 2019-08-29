/*
 * GateConfig.h
 *
 *  Created on: 2015-12-10
 *      Author: Administrator
 */

#ifndef GATECONFIG_H_
#define GATECONFIG_H_

#include "Kernel.h"
#include "Award.h"

#define 	CHAPTER_BOX_CNT		3

struct DefendGateItem {
	uint16_t id;
	uint16_t lv;
	Award award;

	DefendGateItem() {
		id = 0;
		lv = 0;
		award.clear();
	}
};

struct StarReward {
	uint16_t id;
	uint16_t star;
	Award award;
	byte box;
	StarReward() {
		id = 0;
		star = 0;
		box = 0;
		award.clear();
	}
};

struct GateStar {
	uint16_t chapter;
	StarReward rewards[CHAPTER_BOX_CNT];	//奖励id和该奖励的映射

	GateStar() {
		chapter = 0;
	}
};

class GateConfig {
private:
	GateConfig();
public:
	~GateConfig();
	static GateConfig * getInstance() {
		static GateConfig gc;
		return &gc;
	}
	bool initTrade(const string & path);
	bool initDefend(const string & path);
	uint32_t isOpenMap(uint32_t level);
	inline uint32_t getDefendCount() const {
		return m_defend_count;
	}
	const DefendGateItem* getDefend(uint16_t lv);
	bool getLevels(uint32_t chapter_id, vector<uint32_t> &data);
	uint32_t getChapterCnt();
	uint32_t getStarlimit(uint32_t chap_id, uint32_t index);
	uint32_t getchapIdByLevel(uint32_t level);
	bool getReward(uint32_t chap_id, uint32_t id, Award &reward);
	uint32_t getBox(uint32_t chap_id, uint32_t id);
private:
	map<uint32_t, uint32_t> m_trade;
	map<uint32_t, DefendGateItem> m_defend;
	uint32_t m_defend_count;
	map<uint32_t, GateStar> star_box;	//章节id和对应的奖励的映射
	map<uint32_t, vector<uint32_t> > level_map; //章节id和对应leve集合的映射
};
#endif /* GATECONFIG_H_ */
