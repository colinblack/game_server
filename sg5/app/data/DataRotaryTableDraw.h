/*
 * DataShootPointRank.h
 *
 *  Created on: 2015-10-19
 *      Author: Administrator
 */

#ifndef ROTARYTABLE_H_
#define ROTARYTABLE_H_

#include "Kernel.h"

#define ROTARYTABLE_LIST_USER_COUNT 20
#define ROTARYTABLE_LIMIT_PRIZE_COUNT 64
struct DataRotaryTableDrawUser
{
	unsigned uid;
	unsigned itemid;
	unsigned itemcnt;
	unsigned itemtype;//1:装备,2:英雄
	char name[32];
	DataRotaryTableDrawUser()
	{
		uid=0,itemid=0;itemtype = 0;itemcnt = 0;
		memset(name,0,sizeof(name));
	}
	DataRotaryTableDrawUser& operator=(const DataRotaryTableDrawUser& data)
	{
		uid = data.uid;
		itemid = data.itemid;
		itemtype = data.itemtype;
		itemcnt = data.itemcnt;
		strncpy(name, data.name, sizeof(name)-1);
		return *this;
	}
};

struct DataRotaryTableDraw
{
	DataRotaryTableDrawUser list[ROTARYTABLE_LIST_USER_COUNT];
	unsigned numprize[ROTARYTABLE_LIMIT_PRIZE_COUNT];
	unsigned version;
	unsigned listsize;
	DataRotaryTableDraw()
	{
		version = 0;
		listsize = 0;
		memset(list,0,sizeof(list));
		memset(numprize,0,sizeof(numprize));
	}
};

//转盘抽奖
class CDataRotaryTableDraw
{
public:
	CDataRotaryTableDraw(){m_init=false;}
	virtual ~CDataRotaryTableDraw(){}
public:
	//初始化
	int Init(const string &path, semdat sem=sem_rotaty_table_draw);

	//抽奖
	int Draw(unsigned uid,unsigned costItemUd,unsigned version,Json::Value &result);

	//获取抽奖记录信息
	int GetDrawInfo(unsigned version,Json::Value &result);
private:
	int GetList(unsigned version, vector<DataRotaryTableDrawUser> &list, vector<int>& left);
	int AddUser(unsigned version, DataRotaryTableDrawUser& user, vector<DataRotaryTableDrawUser> &list, unsigned &type,unsigned &id,vector<int> &left);
	int TurnLuckTable(vector<unsigned> & prates, int len, int & target);
	CShareMemory m_sh;
	bool m_init;
};

#endif /* DATASHOOTPOINTRANK_H_ */
