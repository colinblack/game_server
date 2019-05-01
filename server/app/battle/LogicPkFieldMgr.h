/*
 * LogicPkFieldMgr.h
 *
 *  Created on: 2016-10-20
 *      Author: dawx62fac
 */

#ifndef LOGICPKFIELDMGR_H_
#define LOGICPKFIELDMGR_H_


#include "ServerInc.h"

class DBCUserBaseWrap;
class  LogicPkFieldMgr : public BattleSingleton, public CSingleton<LogicPkFieldMgr>
{
private:
	friend class CSingleton<LogicPkFieldMgr>;
	LogicPkFieldMgr(){};

private:
	void FullMessage(unsigned uid, int rank, ::ProtoPkField::PkUserItem* obj);

	//切换一批竞争对手
	bool RefreshRival(const DBCUserBaseWrap& user, ::google::protobuf::RepeatedPtrField< ::ProtoPkField::PkUserItem >* obj = NULL);
	bool RefreshRival(int kingdom, int rank, ::google::protobuf::RepeatedPtrField< ::ProtoPkField::PkUserItem >* obj = NULL);

	void CheckUser(const DBCUserBaseWrap& user);

	//竞技场外部接口
	int PKFieldExternalInterface(unsigned uid);

	void AddNotifyMsg(unsigned uid, unsigned rank, const CommonGiftConfig::BaseReward& reward);
public:
	virtual void CallDestroy() { Destroy();}

	void FinishPkSuccess(unsigned uid, unsigned rank);

	void OnHour();

	//打开界面
	int Process(unsigned uid, ProtoPkField::PkFieldReq* req, ProtoPkField::PkFieldResp* resp);

	//进入竞技场
	int Process(unsigned uid, ProtoPkField::EnterPkFieldReq* req, ProtoPkField::EnterPkFieldResp* resp);

	//开始战斗
	int Process(unsigned uid, ProtoPkField::StartPkReq* req);

	//换一批
	int Process(unsigned uid, ProtoPkField::RefreshRivalReq* req, ProtoPkField::RefreshRivalResp* resp);
	//竞技场领奖
	int Process(unsigned uid, ProtoPkField::PkRewardReq* req, ProtoPkField::PkRewardResp* resp);
};



#endif /* LOGICPKFIELDMGR_H_ */
