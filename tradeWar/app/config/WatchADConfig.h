/*
 * WatchADConfig.h
 *
 *  Created on: 2019年 2月 27日
 *      Author: next
 */

#ifndef WATCH_AD_CONFIG_H__
#define	WATCH_AD_CONFIG_H__

#include "Kernel.h"
#include "Award.h"

struct ForeverItem {
	byte id;
	byte times;
	Award reward;
};

struct DailyRewardItem {
	byte id;
	Award reward;
};

struct DailyItem {
	vector<uint32_t> cd;
	map<uint32_t, DailyRewardItem> reward;
};

struct RandomRewardItem {
	byte id;
	byte factor;
};

struct RandomItem {
	byte total;
	byte prob;
	vector<uint32_t> cd;
	map<uint32_t, RandomRewardItem> reward;
};

class WatchADConfig {
SINGLETON_CLASS(WatchADConfig);
	bool init(const string &path);
	uint32_t getForeverLimit();
	uint32_t getDailyRewardID(uint32_t cur);
	uint32_t getRandomRewardID();
	bool isGetRandomReward();
	bool getForeverReward(Award &data);
	bool getDailyReward(uint32_t rewardID, Award &data);
	bool getRandomCdTime(uint32_t count, uint32_t &ts);
	uint32_t getRandomRewardRate(uint32_t rewardID);
	uint32_t getDailyRewardSize();
	uint32_t getRandomRewardSize();
private:
	ForeverItem forever;
	DailyItem daily;
	RandomItem random;
};

#endif /*WATCH_AD_CONFIG_H__*/

