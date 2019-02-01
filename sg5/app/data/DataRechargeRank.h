/*
 * DataRechargeRank.h
 *
 *  Created on: 2015-7-28
 *      Author: eddard
 */

#ifndef DATARECHARGERANK_H_
#define DATARECHARGERANK_H_
#include "Kernel.h"

#define RR_ALL 50
#define RR_DAY 100
#define RR_ZONE_NUM 3

struct RRUser
{
	unsigned uid;
	unsigned cash;
	unsigned pre;
	unsigned next;
	char name[32];
	RRUser()
	{
		uid = cash = 0;
		pre = next = -1;
		memset(name, 0, sizeof(name));
	}
	void Clear()
	{
		uid = cash = 0;
		pre = next = -1;
		memset(name, 0, sizeof(name));
	}
};
struct RRDay
{
	unsigned head;
	unsigned tail;
	unsigned num;
	RRUser user[RR_DAY];
	RRDay()
	{
		head = tail = -1;
		num = 0;
	}
	void Clear()
	{
		head = tail = -1;
		num = 0;
		for(unsigned i=0;i<RR_DAY;++i)
			user[i].Clear();
	}
};
struct RRAll
{
	unsigned head;
	unsigned tail;
	unsigned num;
	RRUser user[RR_ALL];
	RRAll()
	{
		head = tail = -1;
		num = 0;
	}
	void Clear()
	{
		head = tail = -1;
		num = 0;
		for(unsigned i=0;i<RR_ALL;++i)
			user[i].Clear();
	}
};
struct DataRechargeRank
{
	unsigned version;
	unsigned rewardFlag;
	RRDay day;
	RRAll all;
	DataRechargeRank()
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

class CDataRechargeRank
{
public:
	CDataRechargeRank();
	virtual ~CDataRechargeRank();
	int Init(const std::string &path, semdat sem=sem_recharge_rank);
	int GetList(unsigned uid, vector<RRUser> &day, vector<RRUser> &all);
	int SetUser(unsigned uid, unsigned cashDay, unsigned cashAll, string& name, unsigned& need);

protected:
	int getZoneId(unsigned uid, unsigned &zoneId);
	bool m_init;
	CShareMemory m_sh[RR_ZONE_NUM];
};




#endif /* DATARECHARGERANK_H_ */
