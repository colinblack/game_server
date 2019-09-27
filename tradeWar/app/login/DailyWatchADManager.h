/*
 * DailyWatchADManager.h
 *
 *  Created on: 2019年 2月 27日
 *      Author: next
 */
#ifndef DAILY_WATCH_AD_MANAGER_H__
#define DAILY_WATCH_AD_MANAGER_H__

#include "IManager.h"
#include "Award.h"

#define		WATCH_AD_TYPE_COUNT		3

enum {
	FOREVER_WATCH_ITEM 	= 0,
	DAILY_WATCH_ITEM	= 1,
	RANDOM_WATCH_ITEM	= 2
};

enum {
	WATCH_COUNT_ADD	= 1,
	WATCH_REWARD_GET = 2
};

enum {
	FOREVER_WATCH_ID	= 1,
	DAILY_WATCH_ID		= 2,
	RANDOM_WATCH_ID		= 3
};

struct WatchTypeItem {
	byte id;
	byte RewardFlg;
	byte Count;
	byte RandomFlg;

	uint32_t ReadCount;
	uint32_t RewardId;
	uint32_t RewardTs;

	WatchTypeItem() {
		id = 0;
		RewardFlg = 0;
		Count = 0;
		RandomFlg = 0;

		ReadCount = 0;
		RewardId = 0;
		RewardTs = 0;
	}
};

struct DailyWatchADItem {
	uint32_t ts;
	WatchTypeItem data[WATCH_AD_TYPE_COUNT];

	DailyWatchADItem () {
		ts = 0;
	}

	bool fromJson(const Json::Value &v) {
		ts = v.get("ts", 0).asUInt();
		if(v.isMember("data") && v["data"].isArray()) {
			for(size_t i = 0; i < v["data"].size() && i < WATCH_AD_TYPE_COUNT; ++i) {
				data[i].id = v["data"][i].get("id", 0).asUInt();
				data[i].ReadCount = v["data"][i].get("rc", 0).asUInt();
				data[i].RewardFlg = v["data"][i].get("f", 0).asUInt();
				data[i].RewardTs = v["data"][i].get("ts", 0).asUInt();
				data[i].Count = v["data"][i].get("c", 0).asUInt();
				data[i].RandomFlg = v["data"][i].get("rf", 0).asUInt();
				data[i].RewardId = v["data"][i].get("i", 0).asUInt();
			}
		} else {
			return false;
		}
		return true;
	}

	Json::Value toJson() const {
		Json::Value v;
		v["ts"] = ts;
		v["data"] = Json::Value(Json::arrayValue);
		v["data"].resize(WATCH_AD_TYPE_COUNT);
		for(size_t i = 0; i < WATCH_AD_TYPE_COUNT; ++i) {
			v["data"][i]["id"] = data[i].id;
			v["data"][i]["rc"] = data[i].ReadCount;
			v["data"][i]["f"] = data[i].RewardFlg;
			v["data"][i]["i"] = data[i].RewardId;
			v["data"][i]["ts"] = data[i].RewardTs;
			v["data"][i]["c"] = data[i].Count;
			v["data"][i]["rf"] = data[i].RandomFlg;
		}
		return v;
	}
};

class DailyWatchADManager : public IManager {
public:
	DailyWatchADManager();
	virtual ~DailyWatchADManager();
	bool doPacket(CNetPacket *p);
	bool load(uint32_t uid);
	bool save();
	bool DailyReset();
	bool push();
	bool isGetReward(uint32_t id);
	bool rewardGet(uint32_t id);
	bool isSendRandomGift();
	bool isCdTimeOut();
private:
	bool getInfo(CNetPacket* p);
	bool setWatchRewardInfo(CNetPacket* p);
	bool onResp(byte sub, byte ret);

private:
	DailyWatchADItem m_data;
};

#endif //DAILY_WATCH_AD_MANAGER_H__
