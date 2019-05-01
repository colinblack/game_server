/*
 * DataSmeltActivity.h
 *
 *  Created on: 2016-12-5
 *      Author: dawx62fac
 */

#ifndef DATASMELTACTIVITY_H_
#define DATASMELTACTIVITY_H_

#include "Kernel.h"
#include "DBCSimpleTemplate.h"

class DBCSmeltActivity
{
public:
	DBCSmeltActivity();

	void Reset(unsigned version);

	uint16_t GetRewardCnt(int id) const;
	uint16_t* RewardCnt(int id);
public:
	uint32_t uid;
	uint32_t version; //活动版本
	uint16_t total;	  //累计洗练次数
	uint16_t reward_1_cnt; //至尊洗练令 领取次数
	uint16_t reward_2_cnt; //升级洗练令 领取次数
	uint16_t reward_3_cnt; //指定洗练令 领取次数
};

class DBCSmeltActivityHandler : public DBCBase<DBCSmeltActivity, DB_SMELT_ACTIVITY>
{
public:
	virtual int Get(DBCSmeltActivity &data);
	virtual int Get(vector<DBCSmeltActivity> &data);
	virtual int Add(DBCSmeltActivity &data);
	virtual int Set(DBCSmeltActivity &data);
	virtual int Del(DBCSmeltActivity &data);
};

class DataSmeltActivityMgr
	 : public DBCSimpleTemplate<DBCSmeltActivity, DB_SMELT_ACTIVITY, DBCSmeltActivityHandler>
	 , public CSingleton<DataSmeltActivityMgr>
{
public:
	 virtual void CallDestroy() { Destroy();}

	 const char* name() const  { return "DBCSmeltActivity"; }
};


#endif /* DATASMELTACTIVITY_H_ */
