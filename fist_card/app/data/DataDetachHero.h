/*
 * DataDetachHero.h
 *
 *  Created on: 2018年11月16日
 *      Author: colin
 */

#ifndef APP_DATA_DATADETACHHERO_H_
#define APP_DATA_DATADETACHHERO_H_

#include "Kernel.h"

struct DataDetachHero{
	uint32_t uid;
	uint32_t id;
	uint32_t detach_uid;  	//兼职武馆玩家uid
	uint32_t detach_slot; 	//兼职武馆槽位号
	uint32_t club_level;  	//兼职武馆等级
	uint32_t hero_num;    	//兼职武馆英雄数量
	uint32_t detach_coins;	//兼职武馆收益
	uint32_t start_ts;		//收益开始时间

	DataDetachHero() :
		 uid(0),
		 id(0),
		 detach_uid(0),
		 detach_slot(0),
		 club_level(0),
		 hero_num(0),
		 detach_coins(0),
		 start_ts(0)
	{
	}
	void Set(unsigned uid, unsigned level, unsigned slot, unsigned num)
	{
		detach_uid = uid;
		club_level = level;
		hero_num   = num;
		detach_slot = slot;
		start_ts   = Time::GetGlobalTime();
	}

};

class CDataDetachHero: public DBCBase<DataDetachHero, DB_DETACH_HERO>
{
public:
	virtual int Get(DataDetachHero &data);
	virtual int Get(vector<DataDetachHero>&data);
	virtual int Add(DataDetachHero &data);
	virtual int Set(DataDetachHero &data);
	virtual int Del(DataDetachHero &data);
};


#endif /* APP_DATA_DATADETACHHERO_H_ */
