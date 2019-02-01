/*
 * CDataPointsRank.h
 *
 *  Created on: 2012-10-16
 *      Author: Administrator
 */

#ifndef CDATAPOINTSRANK_H_
#define CDATAPOINTSRANK_H_
#include "Kernel.h"

/**********砸罐活动排行榜********************/
#define RANK_SIZE 10
struct DataPoints{
	int unsigned uid;
	int unsigned points;
	char name[32];
	byte reward;

public:
	DataPoints()
	{
		uid = 0;
		points = 0;
		memset(name,0,sizeof(name));
		reward = 0;
	}

	DataPoints &operator =( const DataPoints &other )
	{
		uid = other.uid;
		points = other.points;
		memcpy(name,other.name,sizeof(name) - 1);
		reward = other.reward;
		return *this;
	}
};
struct PointsRank{
	DataPoints pointRank[RANK_SIZE + 1];
};
class CDataPointsRank {
public:
	CDataPointsRank();
	virtual ~CDataPointsRank();
	int Init(const std::string &path, semdat sem=sem_pointsrank);
	int UpdateRankList(const  DataPoints &point);
	int GetRankList( DataPoints vecPoints[]);
	int SetReward(unsigned uid, byte reward);
	int CleanRankList(void);
private:
	bool m_init;
	CShareMemory m_sh;
};
/******************************************/

/*******跨服砸罐活动排行榜*********************/
#define POINT_RANK_ALL_SERVER_DAY 200
#define POINT_RANK_ALL_SERVER_ALL 100
struct PRUser
{
	unsigned uid;
	unsigned points;
	unsigned pre;
	unsigned next;
	char name[32];

	PRUser()
	{
		uid = points = 0;
		pre = next = -1;
		memset(name, 0, sizeof(name));
	}
	void Clear()
	{
		uid = points = 0;
		pre = next = -1;
		memset(name, 0, sizeof(name));
	}
};

struct PRDay
{
	unsigned head;
	unsigned tail;
	unsigned num;
	PRUser user[POINT_RANK_ALL_SERVER_DAY];

	PRDay()
	{
		head = tail = -1;
		num = 0;
	}
	void Clear()
	{
		head = tail = -1;
		num = 0;
		for (unsigned i = 0; i < POINT_RANK_ALL_SERVER_DAY; ++i)
		{
			user[i].Clear();
		}
	}
};

struct PRAll
{
	unsigned head;
	unsigned tail;
	unsigned num;
	PRUser user[POINT_RANK_ALL_SERVER_ALL];

	PRAll()
	{
		head = tail = -1;
		num = 0;
	}
	void Clear()
	{
		head = tail = -1;
		num = 0;
		for (unsigned i = 0; i < POINT_RANK_ALL_SERVER_DAY; ++i)
		{
			user[i].Clear();
		}
	}
};

struct PointsRankALLServer
{
	unsigned version;
	unsigned rewardFlag;
	PRDay day;
	PRAll all;

	PointsRankALLServer()
	{
		version = rewardFlag = 0;
	}
	void Clear()
	{
		version = rewardFlag = 0;
		day.Clear();
		all.Clear();
	}
};
class CDataPointsRankAllServer{
public:
	CDataPointsRankAllServer();
	~CDataPointsRankAllServer();
	int Init(const std::string &path, semdat sem=sem_pointsrank);
	int GetRankList(unsigned uid, vector<PRUser> &day, vector<PRUser> &all);
	int UpdateRankList(unsigned uid, unsigned pointsDay, unsigned pointsAll, string& name, unsigned& need);
	PointsRankALLServer* _get() { return (PointsRankALLServer *) m_sh.GetAddress(); }
private:
	bool m_init;
	CShareMemory m_sh;
};
/*****************************************************/

#endif /* CDATAPOINTSRANK_H_ */
