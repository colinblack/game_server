/*
 * DataCOPY.h
 *
 *  Created on: 2018-11-20
 *      Author: Administrator
 */

#ifndef DATACOPY_H_
#define DATACOPY_H_

#include "Kernel.h"

#define TYPE_COPY_EXP		101
#define TYPE_COPY_WORLDBOSS 110
#define TYPE_COPY_GODPLANET 111
#define TYPE_COPY_TASKBOSS 130

#define TYPE_IMMORTALROAD_COPY 139
#define TYPE_PARTNERISLAND_COPY 143


#define TYPE_COPYBOSS_COUNT 10
#define BOSS_COUNT 100
#define COPY_PLAYER_RANK_MAX_COUNT 3


#define BOSS_STATUS_DEAD 0			//等待刷新
#define BOSS_STATUS_WAIT 1			//已经刷新，没有初始化在地图中
#define BOSS_STATUS_ALIVE 2			//已经在地图中产生








struct BossPlayerRank{
	uint64_t value;
	uint32_t rank;
	uint32_t uid;
	BossPlayerRank(){
		memset(this,0,sizeof(*this));
	}
	BossPlayerRank &operator =(const BossPlayerRank& other)
	{
		value = other.value;
		rank = other.rank;
		uid = other.uid;
		return *this;
	}
};

struct CopyBoss{
	uint32_t bossId;
	uint32_t copyId;
	uint32_t mapId;
	uint32_t wLevel;
	uint32_t init;
	uint32_t refreshTime;
	uint32_t status;
	uint32_t shield;
	uint64_t hp;
	uint64_t maxHp;
	uint32_t owner;
	BossPlayerRank playerRank[COPY_PLAYER_RANK_MAX_COUNT];
	CopyBoss(){
		memset(this,0,sizeof(*this));
	}
};



struct DataCopy{
	CopyBoss bossInfo[TYPE_COPYBOSS_COUNT][BOSS_COUNT];
	DataCopy(){
		memset(this,0,sizeof(*this));
	}
};


class CDataCopy
{
public:
	CDataCopy();
	bool Init(const string &path);
	bool getBossIndex(uint32_t type,uint32_t bossId,uint32_t& index1,uint32_t& index2);
	bool setBossRank(uint32_t type,uint32_t bossId,uint32_t uid,uint32_t hurt);
	bool getBossRank(uint32_t type,uint32_t bossId,vector<BossPlayerRank>& vector);
	DataCopy * getDataCopy();
protected:
	CShareMemory m_sh;
	bool m_init;

};


#endif /* DATACOPY_H_ */
