/*
 * LogicFriendManager.h
 *
 *  Created on: 2018年8月24日
 *      Author: colin
 */

#ifndef APP_BATTLE_LOGICFRIENDMANAGER_H_
#define APP_BATTLE_LOGICFRIENDMANAGER_H_

#include "ServerInc.h"


class DBCFriendWrap
{
public:
	DBCFriendWrap(unsigned index);
	DBCFriendWrap(unsigned uid, unsigned id);
	DataConcern& Obj()
	{
		return data_;
	}
	void Save()
	{
		container_->m_data->MarkChange(index_);
	}

	void UpdateDonationTs(unsigned ts);
	bool UpdateBattleTs();
	void UpdateBattle(int type);

	void FullMessage(unsigned uid, ProtoFriend::RecommendInfo* friends);


private:
	DataConcernManager* container_;
	unsigned		 index_;
	DataConcern& data_;
};


class LogicFriendManager : public  BattleSingleton, public CSingleton<LogicFriendManager>
{
private:
	friend class CSingleton<LogicFriendManager>;
	LogicFriendManager(){}
public:
	virtual void CallDestroy() { Destroy();}
	int FullMessage(unsigned uid, User::FriendInfo*msg);
	void FullMessage(unsigned uid, ProtoFriend::RecommendInfo* msg);
	//推荐好友
	int Process(unsigned uid, ProtoFriend::ProtoRecommendUserReq* req, ProtoFriend::ProtoRecommendUserResp* resp);

	//加好友
	int Process(unsigned uid, ProtoFriend::ProtoConcernReq* req);

	//跨服加好友
	int Process(ProtoFriend::ProtoCSConcernReq* req);

	//删除好友
	int Process(unsigned uid, ProtoFriend::ProtoCancelConcernReq* req);

	//获取好友列表
	int Process(unsigned uid, ProtoFriend::ProtoGetFriendsReq* req);

	//跨服获取好友列表
	int Process(ProtoFriend::ProtoCSGetFriendsReq* req);

	//赠送体力
	int Process(unsigned uid, ProtoFriend::ProtoDonatePowerReq* req);

	//跨服赠送体力
	int Process(ProtoFriend::ProtoCSDonatePowerReq* req);

private:
	//随机推荐玩家
	void RecommendUser(unsigned uid, vector<unsigned>& users);

	//选择玩家
	void SelectUser(unsigned uid, set<unsigned>& userSet, vector<unsigned> &users);

	int Concern(unsigned uid, unsigned otherId);

	//赠送玩家体力
	int DonateFriendPower(unsigned otherId);
};





#endif /* APP_BATTLE_LOGICFRIENDMANAGER_H_ */
