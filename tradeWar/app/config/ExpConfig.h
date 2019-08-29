#ifndef _EXP_CONFIG_H_
#define _EXP_CONFIG_H_

#include "Kernel.h"
#include "Award.h"

struct ExpLevelItem {
	uint16_t level;
	uint32_t star;
	uint32_t reward;
	uint32_t firstCost;
	uint32_t refreshCost;
	uint32_t attackReward;
	Award award;

	ExpLevelItem() : level(0), star(0), reward(0), firstCost(0), refreshCost(0), attackReward(0) {
	}
};

class ExpConfig {
private:
	ExpConfig();
public:
	~ExpConfig();
	static ExpConfig* getInstance() {
		static ExpConfig hc;
		return &hc;
	}
	bool init(const string& path);
	bool getHeroExp(uint32_t level, uint32_t& heroExp);
	bool getUserExp(uint32_t level, uint32_t& userExp);
	uint32_t getNextHeroLevel(uint32_t curLevel, uint32_t heroExp);
	uint32_t getNextUserLevel(uint32_t userExp);
	uint32_t getExpLevelSize() const;
	const ExpLevelItem* getExpLevel(uint16_t level) const;
private:
	vector<uint32_t> m_heroExp;
	vector<uint32_t> m_userExp;
	map<uint16_t, ExpLevelItem> m_levels;
};

#endif /* _EXP_CONFIG_H_ */
