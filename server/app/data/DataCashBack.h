/*
 * DataCashBack.h
 *
 *  Created on: 2016-11-22
 *      Author: dawx62fac
 */

#ifndef DATACASHBACK_H_
#define DATACASHBACK_H_

#include "Kernel.h"
#include "DBCSimpleTemplate.h"

class DBCCashBack
{
public:
	DBCCashBack();

	void Reset(unsigned version);
public:
	uint32_t uid;
	uint32_t version; //活动版本
	uint32_t total;	  //日累计充值
	uint32_t reward_flag; //领奖标记
	uint32_t ts_op;		//时间戳
};

class DBCCashBackHandler : public DBCBase<DBCCashBack, DB_CASH_BACK>
{
public:
	virtual int Get(DBCCashBack &data);
	virtual int Get(vector<DBCCashBack> &data);
	virtual int Add(DBCCashBack &data);
	virtual int Set(DBCCashBack &data);
	virtual int Del(DBCCashBack &data);
};

class DataCashBackMgr
	 : public DBCSimpleTemplate<DBCCashBack, DB_CASH_BACK, DBCCashBackHandler>
	 , public CSingleton<DataCashBackMgr>
{
public:
	 virtual void CallDestroy() { Destroy();}

	 const char* name() const  { return "DBCCashBack"; }

};


#endif /* DATACASHBACK_H_ */
