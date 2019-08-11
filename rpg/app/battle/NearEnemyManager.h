/*
 * NearEnemyManager.h
 *
 *  Created on: 2019年7月31日
 *      Author: colin
 */

#ifndef APP_BATTLE_NEARENEMYMANAGER_H_
#define APP_BATTLE_NEARENEMYMANAGER_H_


#include "BattleBaseInc.h"

#define ENEMY_SIZE 4
#define ZHANGONG_BASE 25
#define ZHANGONG_CONST 5
#define SHALU_CONST 25
#define SHALU_LIMIT 100
#define RANK_LIMIT  10

#define ZhanGong(val) (ZHANGONG_BASE + ZHANGONG_CONST * (val -1))

struct NearEnemyData{
	uint32_t  total_kill;        //击杀值
	uint32_t  shalu;			 //pk值
	uint32_t  zhangong;			 //杀意值
};

class NearEnemyManager : public CSingleton<NearEnemyManager>{
public:
	struct Compare{
		bool operator()(const uint32_t& k1, const uint32_t& k2) const{
			return (m_data.at(k1).total_kill > m_data.at(k2).total_kill);
		}
	};

private:
	friend class CSingleton<NearEnemyManager>;
	NearEnemyManager();
	~NearEnemyManager();
	bool Recover(Human *pHuman);
	map<uint32_t, uint32_t> m_boss;
	map<uint32_t, vector<Point> > m_old_points; //玩家血战之前的位置
	map<uint32_t, set<uint32_t> > m_enemys;    //每个玩家匹配到的敌人
	set<uint32_t, Compare> m_kill_rank;  //击杀值排名 value=uid
	static map<uint32_t, NearEnemyData> m_data;

private:
	void GenEnemyList(uint32_t uid, uint32_t cnt, vector<uint32_t>& enemys); //获取敌人列表

public:
	int Process(uint32_t uid, logins::SNearenmeyFightenemyReq *req);
	int Process(uint32_t uid, logins::SNearenemyBacktoHangReq *req);
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SNearEnemyInfo *resp);

public:
	bool Init();
	bool OnMonsterDie(uint32_t uid, uint32_t monster_id, const Point &diePos);
	bool MonsterDrop(uint32_t uid, uint32_t id, vector<msgs::SItemAmount>& rewards);
	bool OnHumanDie(uint32_t uid);
	void onSecondTimer();
	int  killEnemyRank(uint32_t uid, msgs::SToplist* resp); //杀敌排行

};


#endif /* APP_BATTLE_NEARENEMYMANAGER_H_ */
