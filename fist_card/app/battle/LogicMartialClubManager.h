/*
 * LogicMartialClubManager.h
 *
 *  Created on: 2018年8月31日
 *      Author: colin
 */

#ifndef APP_BATTLE_LOGICMARTIALCLUBMANAGER_H_
#define APP_BATTLE_LOGICMARTIALCLUBMANAGER_H_


#include "ServerInc.h"


class DBCMartialClubWrap
{
public:
	DBCMartialClubWrap(unsigned index);
	DBCMartialClubWrap(unsigned uid, unsigned id);

	DataMartialClub& Obj()
	{
		return data_;
	}
	void Save()
	{
		container_->m_data->MarkChange(index_);
	}
	void FullMessage(ProtoMartialClub::MartialClubInfo *msg) const;

private:
	DataMartialClubManager* container_;
	unsigned index_;
	DataMartialClub& data_;
};


class LogicMartialClubManager : public BattleSingleton, public CSingleton<LogicMartialClubManager>
{
private:
	friend class CSingleton<LogicMartialClubManager>;
	LogicMartialClubManager(){}

public:
	virtual void CallDestroy() { Destroy();}
	virtual int OnInit();

	int FullMessage(unsigned uid, User::MartialClub* msg);
	//开启武馆
	int Process(unsigned uid, ProtoMartialClub::ProtoOpenMartialClubReq *req, ProtoMartialClub::ProtoOpenMartialClubResp * resp);

	//获取自己武馆信息
	int Process(unsigned uid, ProtoMartialClub::ProtoGetOwnerClubReq* req, ProtoMartialClub::ProtoGetOwnerClubResp* resp);
	//获取自己或者别人武馆英雄信息
	int Process(unsigned uid, ProtoMartialClub::ProtoGetHeroReq* req);

	int Process(ProtoMartialClub::ProtoCSGetHeroReq* req);

	//获取所有兼职武馆信息
	int Process(unsigned uid, ProtoMartialClub::ProtoGetPartTimeClubReq* req);

	//跨服获取兼职武馆信息
	int Process(ProtoMartialClub::ProtoCSGetPartTimeClubReq* req);

	//设置英雄
	int Process(unsigned uid, ProtoMartialClub::ProtoSetHeroReq* req);

	//跨服设置英雄
	int Process(ProtoMartialClub::ProtoCSSetHeroReq* req);

	//跨服设置英雄回给battle的信息
	int Process(ProtoMartialClub::ProtoCSSetHeroToBattleReq* req);

	//获取邀请玩家列表
	int Process(unsigned uid, ProtoMartialClub::ProtoGetInviteUserReq* req, ProtoMartialClub::ProtoGetInviteUserResp* resp);

	//邀请玩家的英雄加入我的武馆
	int Process(unsigned uid, ProtoMartialClub::ProtoInviteUserReq* req);

	//跨服邀请玩家的英雄加入我的武馆
	int Process(ProtoMartialClub::ProtoCSInviteUserReq* req);

	//获取自己武馆的收益
	int Process(unsigned uid, ProtoMartialClub::ProtoGetIncomeReq* req, ProtoMartialClub::ProtoGetIncomeResp* resp);

	//获取兼职武馆收益
	int Process(unsigned uid, ProtoMartialClub::ProtoGetOtherIncomeReq* req);

	//推荐武馆
	int  Process(unsigned uid, ProtoMartialClub::ProtoGetMartialClubReq* req, ProtoMartialClub::ProtoGetMartialClubResp* resp);

	//武馆升级
	int Process(unsigned uid, ProtoMartialClub::ProtoUpdateLevelReq* req, ProtoMartialClub::ProtoUpdateLevelResp* resp);

	//卸载自己武馆英雄
	int Process(unsigned uid , ProtoMartialClub::ProtoDelHeroReq* req);
	//跨服卸载自己武馆英雄
	int Process(ProtoMartialClub::ProtoCSDelHeroReq* req);

	//卸载兼职武馆英雄
	int Process(unsigned uid, ProtoMartialClub::ProtoDelParttimerReq* req);

	//跨服卸载兼职武馆英雄
	int Process(ProtoMartialClub::ProtoCSDelParttimerReq* req);

	//跨服卸载兼职武馆英雄返给服务器消息
	int Process(ProtoMartialClub::ProtoCSDelParttimerToBattleReq* req);

	//改名
	int Process(unsigned uid, ProtoMartialClub::ProtoChangeNameReq* req);

	//离线武馆收益
	void MartialOfflineIncome(unsigned uid, unsigned offlineTs, unsigned loginTs);
	//在线武馆收益
	void MartialOnlineIncome();

	//所有武馆收益
	void ALLMartialClubIncome(unsigned uid);

	//单个武馆收益
	void SingleMartialClubIncome(unsigned uid, unsigned grade);

	//更新武馆收益
	void UpdateMartialClub(unsigned uid, unsigned index, unsigned endTs);

	//更新兼职武馆收益
	void UpdatePartTimeMartialClub(unsigned uid, unsigned index, unsigned endTs);

	map<unsigned, unsigned>& GetPropsIndex(){return m_props_index;}

private:
	//刷新邀请玩家
	void RefreshInviteUser(unsigned uid, vector<unsigned>& users);
	//随机选择玩家
	void SelectInviteUser(unsigned uid, vector<unsigned>& vecIn, vector<unsigned>& vecOut);

	void SetMessage(unsigned uid, unsigned heroId, ProtoMartialClub::MartialHeroInfo* msg);

	void SetMessage(unsigned uid, ProtoMartialClub::MartialClubUserInfo* msg);

	//按照活跃度推荐武馆
	void RecommandByVitality(unsigned uid, vector<DataMartialClub*>& club);

	//按照星级推荐武馆
	void RecommandByGrade(unsigned uid, unsigned grade, vector<DataMartialClub*>& club);

	void FullMessage(unsigned uid, unsigned id, ProtoMartialClub::MartialHeroInfo *msg);
private:
	map<unsigned, unsigned> m_props_index;  //收益道具id对应索引
};

#endif /* APP_BATTLE_LOGICMARTIALCLUBMANAGER_H_ */
