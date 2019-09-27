/*
 * WatchADConfig.h
 *
 *  Created on: 2019年 2月 27日
 *      Author: next
 */

#include "WatchADConfig.h"
#include "ConfigJson.h"
#include "CommonConfig.h"

WatchADConfig::WatchADConfig() {
}

WatchADConfig::~WatchADConfig() {
}

bool WatchADConfig::init(const string &path) {
	ConfigJson fileParser(path);
	if(!fileParser.Init()) {
		return false;
	}
	//观看有礼
	const Json::Value *DataForever = fileParser.getMember("forever");
	const Json::Value *DataDaily = fileParser.getMember("daily");
	const Json::Value *DataRandom = fileParser.getMember("random");

	if(DataForever == NULL || DataDaily == NULL || DataRandom == NULL) {
		error_log("watchADConfig error");
		return false;
	}

	forever.id = DataForever->get("id", 0).asUInt();
	forever.times = DataForever->get("times", 0).asUInt();
	Json::Value ForeverReward = DataForever->get("reward", Json::Value(Json::nullValue));
	forever.reward.Json2Award(ForeverReward);
	//每日豪礼
	const Json::Value &DailyCd = DataDaily->get("cd", Json::Value(Json::nullValue));
	if(DailyCd.isNull() || !DailyCd.isArray()) {
		error_log("cd error");
		return false;
	}
	parseArray(DailyCd, daily.cd);

	const Json::Value &DailyReward = DataDaily->get("reward", Json::Value(Json::nullValue));

	for(size_t i = 0; i < DailyReward.size(); ++i) {

		DailyRewardItem data;
		data.id = DailyReward[i].get("id", 0).asUInt();
		data.reward.Json2Award(DailyReward[i]["reward"]);
		daily.reward.insert(make_pair(data.id, data));
	}
	//空投补给
	random.total = DataRandom->get("total", 0).asUInt();
	random.prob = DataRandom->get("prob", 0).asUInt();
	const Json::Value &RandomCd = DataRandom->get("cd", Json::Value(Json::nullValue));
	if(RandomCd.isNull() || !RandomCd.isArray()) {
		error_log("cd error");
		return false;
	}
	parseArray(RandomCd, random.cd);
	const Json::Value &RandomReward = DataRandom->get("reward", Json::Value(Json::nullValue));
	if(RandomReward.isNull() || !RandomReward.isArray()) {
		error_log("RandomReward error");
		return false;
	}
	for(size_t i = 0; i < RandomReward.size(); ++i) {
		RandomRewardItem data;
		data.id = RandomReward[i].get("id", 0).asUInt();
		data.factor = RandomReward[i].get("factor", 0).asUInt();
		random.reward.insert(make_pair(data.id, data));
	}
	return true;
}
uint32_t WatchADConfig::getForeverLimit() {
	return forever.times;
}

bool WatchADConfig::isGetRandomReward() {
	if(Math::GetRandomInt(100) <= random.prob) {
		return true;
	} else {
		return false;
	}
}

uint32_t WatchADConfig::getDailyRewardID(uint32_t cur) {
	map<uint32_t, DailyRewardItem>::iterator itr = daily.reward.find(cur+1);
	if(itr != daily.reward.end()) {
		return cur+1;
	} else {
		itr = daily.reward.begin();
		return (*itr).first;
	}
}

uint32_t WatchADConfig::getRandomRewardID() {
	uint32_t rate = Math::GetRandomInt(random.reward.size());
	map<uint32_t, RandomRewardItem>::iterator itr = random.reward.begin();
	size_t i = 0;
	for(; itr != random.reward.end(); ++itr) {
		if(rate == i) {
			 return (*itr).first;
		}
		++i;
	}
	error_log("Get rewardID error");
	return 0;
}

bool WatchADConfig::getForeverReward(Award &data) {
	data = forever.reward;
	return true;
}
bool WatchADConfig::getDailyReward(uint32_t rewardID, Award &data) {
	map<uint32_t, DailyRewardItem>::iterator itr = daily.reward.find(rewardID);
	if(itr == daily.reward.end()) {
		return false;
	}
	data = daily.reward[rewardID].reward;
	return true;
}

uint32_t WatchADConfig::getRandomRewardRate(uint32_t rewardID) {
	map<uint32_t, RandomRewardItem>::iterator itr = random.reward.find(rewardID);
	if(itr == random.reward.end()) {
		return 0;
	}
	return random.reward[rewardID].factor;
}

uint32_t WatchADConfig::getDailyRewardSize() {
	return daily.reward.size();
}

uint32_t WatchADConfig::getRandomRewardSize() {
	return random.reward.size();
}

bool WatchADConfig::getRandomCdTime(uint32_t count, uint32_t &ts) {
	if(count >= random.cd.size()) {
		return false;
	}
	ts = random.cd[count];
	return true;
}
