/*
 * LogicResourceManager.h
 *
 *  Created on: 2016-9-10
 *      Author: dawx62fac
 */

#ifndef LOGICRESOURCEMANAGER_H_
#define LOGICRESOURCEMANAGER_H_

#include "ServerInc.h"

class LogicResourceManager : public CSingleton<LogicResourceManager>
{
private:
	friend class CSingleton<LogicResourceManager>;
	LogicResourceManager() {}
	virtual ~LogicResourceManager() {}
public:
	virtual void CallDestroy() {Destroy();}
	//上线逻辑
	void Online(unsigned uid);
	void Sync(unsigned uid, BattleReward& r, unsigned rewardb);
	//离线
	void Offline(unsigned uid);


	const OfflineResourceItem& AddExploit(unsigned uid, int exploit);

	//同一天的充值积分
	unsigned GetRechargePays(unsigned uid, unsigned time);

	//////////////////////////////////////////////////////////////////////////
	OfflineResourceItem& Get(unsigned uid);
	int Sync(const DataBase& userBase);

	void SyncRecruitRate(unsigned uid, unsigned rate);
	void SyncUserLevel(unsigned uid, unsigned level);
	void SyncPropertyValue(unsigned uid, DemoOfflineProperty prop, unsigned value);

	void Print();
	//////////////////////////////////////////////////////////////////////////
	//祭司
	int Process(unsigned uid, ProtoResource::FlamenReq* req, ProtoResource::FlamemResp* resp);

	//黑市秒cd
	int Process(unsigned uid, ProtoResource::CutBlackMarketCDReq * req, ProtoResource::CutBlackMarketCDResp * respmsg);

	//黑市购买
	int Process(unsigned uid, ProtoResource::BMarketExchangeReq *req, ProtoResource::BMarketExchangeResp * respmsg);

private:
	//验证cd时间
	int VerifyCDTime(DataBase & base, unsigned now);

	//黑市兑换外部接口
	int BMarketExternalInterface(unsigned uid);
};

#endif /* LOGICRESOURCEMANAGER_H_ */
