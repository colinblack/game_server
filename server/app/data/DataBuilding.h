/*
 * DataBuilding.h
 *
 *  Created on: 2016-8-31
 *      Author: dawx62fac
 */

#ifndef DATABUILDING_H_
#define DATABUILDING_H_

#include "Kernel.h"
#include "DataBase.h"
#include "ConfigInc.h"

class DBCBuildingData
{
public:
	uint32_t uid;
	uint16_t id; 		//建筑id
	uint16_t level;   	//建筑等级
	int8_t	 status;	//状态 [例如解锁，升级]
	int8_t	 is_speed;	//是否加速
	uint32_t handle_time; //解锁开始时间，解锁结束时间，升级开始时间，升级结束时间

private:
	unsigned UpgradeTime();
	void FinishUpgrade(int cost);
	void FinishUnlock(int cost);
public:
	DBCBuildingData();
	DBCBuildingData(unsigned uid_, const ::Building::Item& cfg);

	bool Unlock();

	int RefreshStatus();

	unsigned StartHandleTime();
	unsigned OverHandleTime();

	bool Normal();
	bool Upgrading();//升级中
	bool IsUnLocked();

	void Upgrade(unsigned start_time);

	void FreeSpeed(); //加速

	void OnceFinishUpgrade();

	void FullMessage(::ProtoBuilding::BuildInfo* obj);
};

class DBCBuidingQueueData
{
public:
	enum {
		capacity = 4,
	};
public:
	uint32_t uid;
	int16_t  auto_cnt;
	uint8_t	 type;
	int32_t  build_1;
	uint32_t build_time_1; //建造位置对应的完成时间
	int32_t  build_2;
	uint32_t build_time_2;
	int32_t  build_3;
	uint32_t build_time_3;
	int32_t  build_4;
	uint32_t build_time_4;
private:
	int32_t* Queue(int index);
	uint32_t* QueueTime(int index);
public:
	DBCBuidingQueueData();
	DBCBuidingQueueData(unsigned uid_);

	void Unlock(int unlock_cnt);

	bool QueueIsBusy(int index);
	void QueueOverWork(int index, uint32_t time);
	unsigned QueueBuild(int index);
	unsigned QueueOverTime(int index);
	int  GetEmpty(); //-1为没有
	void QueueUpgrade(int index, unsigned buildid);

	bool IsAutoUpgrade();
	void DecAutoUpgrade(); //
	unsigned FreeQueueCnt();
	unsigned UnlockQueueCnt();

	//获取升级队列
	void GetUpgradeBuilds(std::vector<unsigned>& result);

	void SetAutoUpgrade(uint8_t build_type, int16_t cnt);
	void AbolishAutoUpgrade();

	void FullMessage(ProtoBuilding::BuildQueue* obj);
};

class DBCBuildingHandler : public DBCBase<DBCBuildingData, DB_BUILDING>
{
public:
	virtual int Get(DBCBuildingData &data);
	virtual int Get(vector<DBCBuildingData> &data);
	virtual int Add(DBCBuildingData &data);
	virtual int Set(DBCBuildingData &data);
	virtual int Del(DBCBuildingData &data) {return 0;}
};

class DBCBuildingQueueHandler : public DBCBase<DBCBuidingQueueData, DB_BUILD_QUEUE>
{
public:
	virtual int Get(DBCBuidingQueueData &data);
	virtual int Get(vector<DBCBuidingQueueData> &data) {return 0;}
	virtual int Add(DBCBuidingQueueData &data);
	virtual int Set(DBCBuidingQueueData &data);
	virtual int Del(DBCBuidingQueueData &data) {return 0;}
};



#endif /* DATABUILDING_H_ */
