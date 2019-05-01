/*
 * LogicMineMgr.h
 *
 *  Created on: 2016-11-15
 *      Author: dawx62fac
 */

#ifndef LOGICMINEMGR_H_
#define LOGICMINEMGR_H_

#include "ServerInc.h"

#define MINE_OPEN_LEVEL (30) //矿开放等级

class  LogicMineMgr
		: public BattleSingleton
		, public CSingleton<LogicMineMgr>
{
private:
	friend class CSingleton<LogicMineMgr>;
	LogicMineMgr() {};

	void CheckUserParams(const DBCUserBaseWrap& user) const;

	MineManager* DataPtr()
	{
		return MineManager::Instance();
	}

private:
	void FullMessage(unsigned uid, const MineHole& mineHole, ProtoMine::MineItem* obj);
	void FullMessage(unsigned uid, const MineKingdom& mineObj, ::google::protobuf::RepeatedPtrField< ::ProtoMine::MineItem >* obj);

	void OnMineNormalHoleFull(MineKingdom& mineObj, const MineHole& mineHole);
	void OnMineKingdomHoleFull(int kingdom, MineKingdom& mineObj, const MineHole& mineHole);

	//矿藏援建外部接口
	int DonateExternalInterface(unsigned uid);

	//开矿外部接口
	int OpenMineExternalInterface(unsigned uid);

	int SendNotify(unsigned uid, unsigned cash);

public:
	virtual void CallDestroy() { Destroy();}

	void OnDay();

	void FullMessage(const DBCUserBaseWrap& user, User::MineItem* obj);

	//获取矿洞列表
	int Process(unsigned uid, ProtoMine::MineInfoReq* req, ProtoMine::MineInfoResp* resp);
	//开启普通矿洞
	int Process(unsigned uid, ProtoMine::MineNormalOpenReq* req, ProtoMine::MineOpenResp* resp);
	int Process(unsigned uid, ProtoMine::MineKingdomOpenReq* rep, ProtoMine::MineOpenResp* resp);
	//捐赠
	int Process(unsigned uid, ProtoMine::DonateNormalReq* req, ProtoMine::DonateResp* resp);
	int Process(unsigned uid, ProtoMine::DonateKingdomReq* req, ProtoMine::DonateResp* resp);
	//领奖
	int Process(unsigned uid, ProtoMine::MineKingdomRewardReq* req, ProtoMine::MineKingdomRewardResp* resp);
	int Process(unsigned uid, ProtoMine::MineKingdomMinerRewardReq* req,ProtoMine::MineKingdomMinerRewardResp* resp);
	//记录
	int Process(unsigned uid, ProtoMine::MineRecordReq* req, ProtoMine::MineRecordResp* resp);
};


#endif /* LOGICMINEMGR_H_ */
