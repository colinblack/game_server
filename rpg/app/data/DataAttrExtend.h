/*
 * DataAttrExtend.h
 *
 *  Created on: 2019年7月12日
 *      Author: Administrator
 */

#ifndef DATA_ATTR_EXTEND_H_
#define DATA_ATTR_EXTEND_H_

#include "DataAttr.h"

//图鉴
struct CardInfo {
	uint32_t uid;
	uint32_t type;
	uint32_t id;
	uint32_t startId;
	uint32_t activeIndex;
	uint32_t reserve[8];
	CardInfo() {
		memset(this,0,sizeof(*this));
	}
};

//境界和转生
struct ReinCarnInfo {
	uint32_t uid;
	uint32_t type;
	uint32_t id;
	uint32_t value;				//境界经验
	uint32_t level;				//境界等级
	uint32_t reinCarnLevel; 	//转生等级
	uint32_t reserve0;			//转生修为
	uint32_t gotCount;
	uint32_t gotLevel;
	uint32_t normalItemCount;
	uint32_t superItemCount;
	uint32_t reserve[2];
	ReinCarnInfo() {
		memset(this,0,sizeof(*this));
	}
};


// 称号 储存在数据库中的结构
struct DataTitle {
	uint32_t uid;
	uint32_t type;
	uint32_t id;
	uint32_t rid;
	uint32_t isWear;
	uint32_t indateTime;
	uint32_t reseve[8];

	DataTitle() {
		memset(this,0,sizeof(*this));
	}

	bool init(uint32_t p_uid,uint32_t p_rid, uint32_t p_type, uint32_t p_id,uint32_t p_isWear){
		memset(this,0,sizeof(*this));
		uid = p_uid;
		type = p_type;
		id = p_id;
		rid = p_rid;
		isWear = p_isWear;
		return true;
	}
};

// 称号 储存在数据库中的结构
struct DataOnlineReward {
	uint32_t uid;
	uint32_t type;
	uint32_t id;
	uint32_t hasGotReward;
	uint32_t reseve[9];

	DataOnlineReward() {
		memset(this,0,sizeof(*this));
	}

	bool init(uint32_t p_uid, uint32_t p_type, uint32_t p_id,uint32_t p_hasGotReward){
		memset(this,0,sizeof(*this));
		uid = p_uid;
		type = p_type;
		id = p_id;
		hasGotReward = p_hasGotReward;
		return true;
	}
};


//BOSS信息
struct CopyInfo {
	uint32_t uid;
	uint32_t type;
	uint32_t id;
	uint32_t rewardMark;
	uint32_t payNum;
	uint32_t resetTime;
	uint32_t enterTime;
	uint32_t firstEnterTime;
	uint16_t totalEnterNum;
	uint16_t totalCompleteNum;
	uint16_t totalEnterDay;
	uint16_t completeNum;
	uint16_t enterNum;
	uint16_t data;
	uint16_t dataExt;
	uint16_t reserve[3];
	CopyInfo() {
		memset(this,0,sizeof(*this));
	}
};


struct MagicTowerInfo {
	uint32_t uid;
	uint32_t type;
	uint32_t id;
	uint32_t layer;
	uint32_t reserve[9];
	MagicTowerInfo() {
		memset(this,0,sizeof(*this));
	}
};

//日常活动
struct DataActivity{
	uint32_t uid;
	uint32_t type;
	uint32_t id;
	uint32_t cnt;
	uint32_t reserve[9];
	DataActivity() {
		memset(this, 0, sizeof(*this));
	}
	bool init(uint32_t Uid, uint32_t Type, uint32_t Id) {
		memset(this,0,sizeof(*this));
		uid = Uid;
		type = Type;
		id = Id;
		return true;
	}
};

struct TreasureHunt {
	uint32_t uid;
	uint32_t id;
	uint32_t ts;
	uint32_t total_num;
	uint32_t daily_num;
	uint32_t use_free;
	uint32_t has_fifty;

	TreasureHunt() {
		uid = 0;
		id = 0;
		ts = 0;
		total_num = 0;
		daily_num = 0;
		use_free = 0;
		has_fifty = 0;
	}

	void FromAttr(const DataAttr &data) {
		uid = data.uid;
		id = data.id;
		ts = data.v1;
		total_num = data.v2;
		daily_num = data.v3;
		use_free = data.v4;
		has_fifty = data.v5;
	}

	void ToAttr(DataAttr &data) {
		data.uid = uid;
		data.type = TYPE_ATTR_TREASURE_HUNT;
		data.id = id;
		data.v1 = ts;
		data.v2 = total_num;
		data.v3 = daily_num;
		data.v4 = use_free;
		data.v5 = has_fifty;
	}
};

struct DataZhanLing {
	uint32_t uid;
	uint32_t dai;
	uint32_t mission;
	uint32_t deadline;
	uint32_t adv;
	uint32_t nuqi;

	DataZhanLing() {
		uid = 0;
		dai = 0;
		mission = 0;
		deadline = 0;
		adv = 0;
		nuqi = 0;
	}

	void FromAttr(const DataAttr &data) {
		uid = data.uid;
		dai = data.v1;
		mission = data.v2;
		deadline = data.v3;
		adv = data.v4;
		nuqi = data.v5;
	}
	void ToAttr(DataAttr &data) {
		data.uid = uid;
		data.type = TYPE_ATTR_ZHAN_LING;
		data.id = 0;
		data.v1 = dai;
		data.v2 = mission;
		data.v3 = deadline;
		data.v4 = adv;
		data.v5 = nuqi;
	}
};

//圣装任务
struct DataShengMission{
	uint32_t uid;
	uint32_t type;
	uint32_t reinCarnlevel;
	uint32_t mission[9];
	uint32_t reserve;
	DataShengMission() {
		memset(this, 0, sizeof(*this));
	}

	bool init(uint32_t Uid, uint32_t Type, uint32_t ReinCarnlevel) {
		memset(this, 0, sizeof(*this));
		uid = Uid;
		type = Type;
		reinCarnlevel = ReinCarnlevel;
		return true;
	}
};
//圣装任务数据
struct DataShengCount{
	uint32_t uid;
	uint32_t type;
	uint32_t reinCarnlevel;
	uint32_t reserve;
	uint32_t datas[9];
	DataShengCount() {
		memset(this, 0, sizeof(*this));
	}

	bool init(uint32_t Uid, uint32_t Type, uint32_t ReinCarnlevel) {
		memset(this, 0, sizeof(*this));
		uid = Uid;
		type = Type;
		reinCarnlevel = ReinCarnlevel;
		return true;
	}
};

//进阶羁绊
struct DataAdvanceTarget{
	uint32_t uid;
	uint32_t type;
	uint32_t advance_type;
	uint32_t advance;
	uint32_t reserve[9];
	DataAdvanceTarget() {
		memset(this, 0, sizeof(*this));
	}

	bool init(uint32_t Uid, uint32_t Type, uint32_t AdvanceType) {
		memset(this, 0, sizeof(*this));
		uid = Uid;
		type = Type;
		advance_type = AdvanceType;
		return true;
	}
};

//进阶羁绊
struct DataShop{
	uint32_t uid;
	uint32_t type;
	uint32_t id;
	uint32_t cnt;
	uint32_t ts;
	uint32_t reserve[8];
	DataShop() {
		memset(this, 0, sizeof(*this));
	}

	bool init(uint32_t Uid, uint32_t Type, uint32_t Id) {
		memset(this, 0, sizeof(*this));
		uid = Uid;
		type = Type;
		id = Id;
		return true;
	}
};

#endif /* DATA_ATTR_EXTEND_H_ */
