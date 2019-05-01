/*
 * LogicBuidingManager.h
 *
 *  Created on: 2016-8-31
 *      Author: dawx62fac
 */

#ifndef LOGICBUIDINGMANAGER_H_
#define LOGICBUIDINGMANAGER_H_

#include "ServerInc.h"


class DBCBuildingDataWrap
{
public:
	DBCBuildingDataWrap(unsigned uid, unsigned buildid);
	DBCBuildingDataWrap(unsigned index);
	~DBCBuildingDataWrap();

	DBCBuildingData& Obj()
	{
		return data_;
	}

	void Save()
	{
		container_->m_data->MarkChange(index_);
	}

	void Unlock();
	void FreeSpeed();
	void OnceFinishUpgrade();
	int Upgrade(unsigned startTime);

	void FullMessage(::ProtoBuilding::BuildInfo* obj);
private:
	void Init();
	unsigned _Index(unsigned index);
	///////////////////////////////////////////////////
	void FinishUpgrade();

	void SyncYield();

	//建筑升级外部接口
	int UpgradeExternalInterface();

	//产量外部接口
	int ProductExternalInterface();
private:
	DataBuildingManager*	container_;
	unsigned		 		index_;
	DBCBuildingData& 		data_;
	int						type_;
};

class DBCBuildingQueueDataWrap
{
public:
	DBCBuildingQueueDataWrap(unsigned uid);

	DBCBuidingQueueData& Obj()
	{
		return data_;
	}

	void Save()
	{
		container_->m_data->MarkChange(index_);
	}

	int Upgrade(unsigned index, unsigned build_id);
	void Unlock(unsigned cnt);
	void GetAutoUpgradeBuilds(unsigned uid, int cnt, int type, std::vector<unsigned>& vBuilds);

	void SetAutoUpgrade(uint8_t build_type, int16_t cnt);
	void AbolishAutoUpgrade();

	void FullMessage(ProtoBuilding::BuildQueue* obj);

private:
	DataBuildQueue* 		container_;
	unsigned 				index_;
	DBCBuidingQueueData& 	data_;
};

class LogicBuildManager : public BattleSingleton, public CSingleton<LogicBuildManager>
{
private:
	friend class CSingleton<LogicBuildManager>;
	LogicBuildManager();

private:
	const DataBase& UserData(unsigned uid) const;

	int BuildId2Type(unsigned id) const;

	void CheckParamsBuildId(unsigned id) const;
public:
	virtual void CallDestroy() { Destroy();}

	//DBCBuildingData& Get(unsigned uid, unsigned build_id);

	//募兵速率  5s生产数
	unsigned RecruitRate(unsigned uid);
	unsigned GetCapacity(unsigned uid, int type);

	//时间段内的产量
	unsigned ProductValue(unsigned uid, int type, unsigned start, unsigned end);

	//总产量
	unsigned Yields(unsigned uid, int type);

	//成就的产量计算
	unsigned YieldAchievement(unsigned uid, int type);

	//加成
	unsigned YieldsAddition(unsigned uid, int type, unsigned baseValue);
	//基本
	unsigned YieldsBase(unsigned uid, int type);

	void SyncYield(unsigned uid);
	void SyncYield(unsigned uid, int type);
	void SyncRecruitRate(unsigned uid);

	////////////////////////////////////////////////////////////////////////////////////////
	int Process(unsigned uid, ProtoBuilding::BuildSyncReq* msg, ProtoBuilding::BuildSyncResp* resp);
	int Process(unsigned uid, ProtoBuilding::BuildUnlockReq* msg, ProtoBuilding::BuildUnlockResp* resp);
	int Process(unsigned uid, ProtoBuilding::BuildUpgradeReq* msg, ProtoBuilding::BuildUpgradeResp* resp);
	int Process(unsigned uid, ProtoBuilding::BuildFreeSpeedReq* msg, ProtoBuilding::BuildSyncResp* resp);
	int Process(unsigned uid, ProtoBuilding::BuildOverOnceReq* msg, ProtoBuilding::BuildOverOnceResp* resp);
	int Process(unsigned uid, ProtoBuilding::BuildAutoUpgradeReq* msg, ProtoBuilding::BuildAutoUpgradeResp* resp);
	int Process(unsigned uid, ProtoBuilding::BuildExploitReq* msg, ProtoBuilding::BuildExploitResp* resp);
	int Process(unsigned uid, ProtoBuilding::BuildResourceSyncReq* msg, ProtoBuilding::BuildResourceSyncResq* resp);
	int Process(unsigned uid, ProtoBuilding::BuildUnlockQueueReq* msg, ProtoBuilding::BuildUnlockQueueResp* resp);


	void FullMessageInLogin(unsigned uid, User::Building* obj);
	void FullMessage(unsigned uid, int type, ProtoBuilding::BuildYield* obj);


	int GetBuildingByType(unsigned uid, int type, vector<DBCBuildingData> &vctBuilds);
private:

	unsigned Capacity(unsigned uid, int type);
};




#endif /* LOGICBUIDINGMANAGER_H_ */
