/*
 * DataConsumeRank.h
 *
 *  Created on: 2015-2-2
 *      Author: Ralf
 */

#ifndef DATACONSUMERANK_H_
#define DATACONSUMERANK_H_
#include "Kernel.h"

#define CR_ALL 100
#define CR_DAY 200

struct CRUser
{
	unsigned uid;
	unsigned cash;
	unsigned pre;
	unsigned next;
	char name[32];
	CRUser()
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
struct CRDay
{
	unsigned head;
	unsigned tail;
	unsigned num;
	CRUser user[CR_DAY];
	CRDay()
	{
		head = tail = -1;
		num = 0;
	}
	void Clear()
	{
		head = tail = -1;
		num = 0;
		for(unsigned i=0;i<CR_DAY;++i)
			user[i].Clear();
	}
};
struct CRAll
{
	unsigned head;
	unsigned tail;
	unsigned num;
	CRUser user[CR_ALL];
	CRAll()
	{
		head = tail = -1;
		num = 0;
	}
	void Clear()
	{
		head = tail = -1;
		num = 0;
		for(unsigned i=0;i<CR_ALL;++i)
			user[i].Clear();
	}
};
struct DataConsumeRank
{
	unsigned version;
	unsigned rewardFlag;
	CRDay day;
	CRAll all;
	DataConsumeRank()
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

class CDataConsumeRank
{
public:
	CDataConsumeRank();
	virtual ~CDataConsumeRank();
	int Init(const std::string &path, semdat sem=sem_consume_rank);
	int GetList(vector<CRUser> &day, vector<CRUser> &all);
	int SetUser(unsigned uid, unsigned cashDay, unsigned cashAll, string& name, unsigned& need);

protected:
	bool m_init;
	CShareMemory m_sh;
};




#endif /* DATACONSUMERANK_H_ */
