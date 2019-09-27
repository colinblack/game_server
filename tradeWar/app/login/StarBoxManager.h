/*
 * StarBoxManager.h
 *
 *  Created on: 2019年 4月 19日
 *      Author: next
 */
#ifndef 	__STAR_BOX_MANAGER_H__
#define		__STAR_BOX_MANAGER_H__

#include "IManager.h"
#include "Award.h"

#define 	CHAPTER_BOX_CNT		3

struct StarBoxItem {
	byte id;
	byte eFlag;
	byte gFlag;
	uint32_t ts;

	StarBoxItem() {
		id = 0;
		eFlag = false;
		gFlag = false;
		ts = 0;
	}
};

struct StarBox {
	byte chapId;
	StarBoxItem data[CHAPTER_BOX_CNT];
	StarBox() {
		chapId = 0;
	}

	bool fromJson(const Json::Value &v) {
		chapId = v.get("chapId", 0).asUInt();
		if(v.isMember("data") && v["data"].isArray()) {
			for(uint32_t i = 0; i < v["data"].size(); ++i) {
				const Json::Value &item = v["data"].get(i, Json::nullValue);
				if (item.isNull() || !item.isObject()) {
					continue;
				}
				data[i].id = item.get("id", 0).asUInt();
				data[i].eFlag = item.get("ef", 0).asUInt();
				data[i].gFlag = item.get("gf", 0).asUInt();
				data[i].ts = item.get("ts", 0).asUInt();
			}
			return true;
		} else {
			return false;
		}
	}

	Json::Value toJson() const {
		Json::Value v;
		v["chapId"] = chapId;
		for(int i = 0; i < CHAPTER_BOX_CNT; ++i) {
			v["data"][i]["id"] = data[i].id;
			v["data"][i]["ef"] = data[i].eFlag;
			v["data"][i]["gf"] = data[i].gFlag;
			v["data"][i]["ts"] = data[i].ts;
		}
		return v;
	}
};

class StarBoxManager: public IManager {
public:
	StarBoxManager();
	~StarBoxManager();
	bool doPacket(CNetPacket *p);
	bool load(uint32_t uid);
	bool save();
	bool getInfo(CNetPacket *p);
	bool openBox(CNetPacket *p);
	bool infoReFlash(uint32_t level);
	bool getALLBoxFlag(CNetPacket *p);

private:
	bool infoAdd(uint32_t id);
	bool onResp(byte sub, byte ret);
	uint32_t getChapStarCnt(uint32_t chap_id);
private:
	map<uint32_t, StarBox> starBoxMap;	//章节id和对应星级宝箱的映射
};

#endif/*__STAR_BOX_MANAGER_H__*/
