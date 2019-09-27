/*
 * DailyQuestConfig.h
 *
 *  Created on: 2017年12月27日
 *      Author: Administrator
 */

#ifndef DAILYQUEST_CONFIG_H_
#define DAILYQUEST_CONFIG_H_

#include "Kernel.h"
#include "Award.h"

struct DailyQuestItem
{
	byte id;
	byte score;
	byte level;
	uint32_t count;
	Award reward;

	DailyQuestItem() :
			id(0), score(0), level(0), count(0)
	{
	}
	bool operator==(uint32_t index) const
	{
		return id == index;
	}
};

struct DailyQuestReward
{
	byte id;
	uint16_t score;
	Award reward;
	DailyQuestReward() :
			id(0), score(0)
	{
	}
};

class DailyQuestConfig
{
public:
	virtual ~DailyQuestConfig();
	static DailyQuestConfig* getInstance()
	{
		static DailyQuestConfig instance;
		return &instance;
	}
	bool init(const string &path);
	bool getItemIds(set<uint32_t> &ids);
	const DailyQuestItem* getItem(uint32_t id) const;
	const DailyQuestReward* getReward(uint32_t index) const;
	const uint32_t getRewardSize() const;
protected:
	DailyQuestConfig();
private:
	vector<DailyQuestItem> m_items;
	vector<DailyQuestReward> m_reward;
};

#endif /* DAILYQUEST_CONFIG_H_ */
