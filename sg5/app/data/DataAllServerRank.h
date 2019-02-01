/*
 * DataAllServerRank.h
 *
 *  Created on: 2014-7-10
 *      Author: Ralf
 */

#ifndef DATAALLSERVERRANK_H_
#define DATAALLSERVERRANK_H_

#include "Kernel.h"

#define ALL_SERVER_RANK_USER 500000
#define ALL_SERVER_RANK_SEASON 14
#define ALL_SERVER_RANK_HISTORY 5
#define ALL_SERVER_RANK_START 1000
#define ALL_SERVER_RANK_RANGE 250
#define ALL_SERVER_RANK_WIN 50
#define ALL_SERVER_RANK_LOSE 20
#define ALL_SERVER_RANK_BEAT 10
#define ALL_SERVER_RANK_CW 1
#define ALL_SERVER_RANK_BT 50

#define ALL_SERVER_RANK_SEG 10
#define ALL_SERVER_RANK_SEG_RANK 10

#define ALL_SERVER_RANK_1 	-1000000
#define ALL_SERVER_RANK_2 	1500
#define ALL_SERVER_RANK_3 	2000
#define ALL_SERVER_RANK_4 	2500
#define ALL_SERVER_RANK_5 	3000
#define ALL_SERVER_RANK_6 	3500
#define ALL_SERVER_RANK_7 	4000
#define ALL_SERVER_RANK_8 	4500
#define ALL_SERVER_RANK_9 	5000
#define ALL_SERVER_RANK_10 	5500
#define ALL_SERVER_RANK_11 	1000000

struct AllServerRankReward
{
	unsigned id, c1, c2;
	AllServerRankReward()
	{
		id = c1 = c2 = 0;
	}
	AllServerRankReward(unsigned id1, unsigned c11, unsigned c21)
	{
		id = id1;
		c1 = c11;
		c2 = c21;
	}
};

#define ALL_SERVER_RANK_R_1_EQID 4050
#define ALL_SERVER_RANK_R_2_EQID 4051
#define ALL_SERVER_RANK_R_3_EQID 4052

#define ALL_SERVER_RANK_R_1	AllServerRankReward(ALL_SERVER_RANK_R_1_EQID,10,10)
#define ALL_SERVER_RANK_R_2 AllServerRankReward(ALL_SERVER_RANK_R_1_EQID,15,15)
#define ALL_SERVER_RANK_R_3 AllServerRankReward(ALL_SERVER_RANK_R_1_EQID,20,20)
#define ALL_SERVER_RANK_R_4 AllServerRankReward(ALL_SERVER_RANK_R_1_EQID,30,30)
#define ALL_SERVER_RANK_R_5 AllServerRankReward(ALL_SERVER_RANK_R_1_EQID,40,40)
#define ALL_SERVER_RANK_R_6 AllServerRankReward(ALL_SERVER_RANK_R_1_EQID,50,50)
#define ALL_SERVER_RANK_R_7 AllServerRankReward(ALL_SERVER_RANK_R_1_EQID,60,60)
#define ALL_SERVER_RANK_R_8 AllServerRankReward(ALL_SERVER_RANK_R_1_EQID,70,70)
#define ALL_SERVER_RANK_R_9 AllServerRankReward(ALL_SERVER_RANK_R_1_EQID,80,80)
#define ALL_SERVER_RANK_R_10 AllServerRankReward(ALL_SERVER_RANK_R_1_EQID,100,100)

enum AllServerRankResult
{
	AllServerRankResult_Win 	= 1,
	AllServerRankResult_Lose	= 2,
	AllServerRankResult_Beat 	= 3,
	AllServerRankResult_Defend 	= 4,
};

enum AllServerRankFlag
{
	AllServerRankFlag_none		= 0,
	AllServerRankFlag_attacking	= 1,
};

struct AllServerRankHistory
{
	unsigned uid,ts,result;
	char name[32];
	AllServerRankHistory()
	{
		uid = ts = result = 0;
		memset(name,0,sizeof(name));
	}
	AllServerRankHistory(unsigned uid1,unsigned result1, string name1)
	{
		uid = uid1;
		ts = Time::GetGlobalTime();
		result = result1;
		memset(name,0,sizeof(name));
		memcpy(name,name1.c_str(),sizeof(name)-1);
	}
};

struct AllServerRankUser
{
	unsigned uid, lvl, tfight, tcwin, tbeat, swin, slose, sbeat, sdefend, shigh, slow, index, flag;//t=today,c=continues,s=season
	int tscore, score;
	char name[32];
	AllServerRankHistory history[ALL_SERVER_RANK_HISTORY];
	AllServerRankUser()
	{
		uid = lvl = tfight = tcwin = tbeat = swin = slose = sbeat = sdefend = shigh = slow = index = flag = 0;
		tscore = score = 0;
		memset(name,0,sizeof(name));
	}
};

struct DataAllServerRank
{
	unsigned count, day, dayts;
	AllServerRankUser user[ALL_SERVER_RANK_USER];
	DataAllServerRank()
	{
		count = day = dayts = 0;
	}
};

typedef map<unsigned, AllServerRankUser> AllServerRankUIDMap;
typedef multimap<int, unsigned> AllServerRankScoreMap;

class CDataAllServerRank
{
private:
	CDataAllServerRank();

public:
	virtual ~CDataAllServerRank();
	static CDataAllServerRank* GetCDataAllServerRank(bool init = true);
	int Init(const std::string &path, semdat sem=sem_allserver_rank, bool init=true);

	int GetUser(unsigned uid, AllServerRankUser &user, unsigned &count, unsigned &day, unsigned &dayts, unsigned &nextuid);
	int StartFight(unsigned attacker, unsigned defender);
	int SetResult(unsigned attacker, unsigned defender, bool win, unsigned lvl, string &attackername, string &defendername, int &scoreres);
	int Reward();
	int Rank(string path = "../webroot/data/allserverrank");
	int Day();

	int Watch();

	const AllServerRankUIDMap& GetAllServerRankUIDMap() { return m_uidmap; }
	const AllServerRankScoreMap& GetAllServerRankScoreMap() { return m_scoremap; }

protected:
	static CDataAllServerRank* m_pData;
	bool m_init;
	CShareMemory m_sh;
	unsigned m_count;
	unsigned m_day;
	unsigned m_dayts;
	AllServerRankUIDMap m_uidmap;
	AllServerRankScoreMap m_scoremap;
	static const int rank_seg[ALL_SERVER_RANK_SEG+1];
	static const AllServerRankReward rank_reward[ALL_SERVER_RANK_SEG];
};

#endif /* DATAALLSERVERRANK_H_ */
