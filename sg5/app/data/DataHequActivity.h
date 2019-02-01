/*
 * DataHequActivity.h
 *
 *  Created on: 2014-07-14
 *      Author: Administrator
 */

#ifndef CDATAHEQUACTIVITY_H_
#define CDATAHEQUACTIVITY_H_
#include "Kernel.h"

#define ALLIANCE_POINT_RANK_SIZE 1000
#define WORLD_ATTACK_RANK_SIZE 30000

struct AlliancePoint{
	unsigned alliance_id;
	unsigned point;
	char name[32];

public:
	AlliancePoint()
	{
		alliance_id = point  = 0;
		memset(name,0,sizeof(name));
	}
};

struct HequWorldAttack{
	unsigned uid;
	unsigned attack_num;
	char name[32];

public:
	HequWorldAttack()
	{
		uid = attack_num  = 0;
		memset(name,0,sizeof(name));
	}

};

struct DataHequAlliancePoint
{
	unsigned version;
	unsigned reward;
	AlliancePoint point[ALLIANCE_POINT_RANK_SIZE];
};


struct DataHequWorldAttack
{
	unsigned version;
	unsigned reward;
	HequWorldAttack attack[WORLD_ATTACK_RANK_SIZE];
};

class CDataAlliancePoint {
public:
	CDataAlliancePoint();
	virtual ~CDataAlliancePoint();
	int Init(const std::string &path, semdat sem=sem_alliance_point);

	int UpdateAlliancePointRankList(const AlliancePoint &point);
	int GetAlliancePointRankList( vector <AlliancePoint> &vecPoints);
	int RewardAlliancePointRankList( vector <AlliancePoint> &rewardPoints);

private:
	bool m_init;
	CShareMemory m_sh;
};


class CDataWorldAttack {
public:
	CDataWorldAttack();
	virtual ~CDataWorldAttack();
	int Init(const std::string &path, semdat sem=sem_world_attack);

	int UpdateWorldAttackRankList(const HequWorldAttack &attack_num);    //老争霸的个人攻城数量
	int UpdateNewWorldAttackRankList(multimap<unsigned, unsigned> herokill, map<unsigned, string> heroname);	//新国战的个人杀敌量
	int GetWorldAttackRankList( vector <HequWorldAttack> &attack_num);
	int GetWorldAttackSelfData( unsigned uid,HequWorldAttack &attack_num);
	int RewardWorldAttackRankList( vector <HequWorldAttack> &reward_num);

private:
	bool m_init;
	CShareMemory m_sh;
};

#endif /* CDATAHEQUACTIVITY_H_ */
