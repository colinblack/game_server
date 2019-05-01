/*
 * UserManager.h
 *
 *  Created on: 2016-8-16
 *      Author: Ralf
 */

#ifndef LOGIC_HERO_MANAGER_H_
#define LOGIC_HERO_MANAGER_H_

#include "ServerInc.h"

class DBCHeroWrap
{
public:
	DBCHeroWrap(unsigned uid, unsigned heroid);
	DBCHeroWrap(unsigned index);

	DataHero& Obj()
	{
		return data_;
	}

	void Save()
	{
		container_->m_data->MarkChange(index_);
	}

	int GetFightAttr(HeroFightAttr& result, bool isPushSoldiers = true);

	bool FinalData(const OfflineResourceItemHexp& hexp, bool isPushSoldiers = true);
	void AddOccupy();

	bool AddExp(int exp, bool isPushSoldiers = true);

	void FullMessage(ProtoHero::HeroBaseInfoCPP * hero, bool isPushSoldiers);

private:
	DataHeroManager* container_;
	unsigned		 index_;
	DataHero& 		 data_;
};

////////////////////////////////////////////////////////////////////////////////////
class HeroPropertyWrap
{
public:
	HeroPropertyWrap(unsigned uid, unsigned heroId);
	const OfflineResourceItem&  Attr() const
	{
		return attr_;
	}

	HeroPropertyItem& 	Obj() const
	{
		return data_;
	}

	bool IsFullTroops();

	unsigned 	CalcRealRecruitSoldires(unsigned nAddSoldires);
	void		RecruitSoldires(unsigned nAddSoldires);
	void	 	FullSoldires();

	unsigned 	GetActualTroops();
	unsigned 	GetTotalTroops();
	unsigned	GetFreeTroops();

	void	 	GetHeroFightAttr(HeroFightAttr& fight_attr) const;

	unsigned	GetHeroLevel() const;

	void 		UpdateProperty(HeroFightAttr& result, bool isPushSoldiers = true);

	void FullMessage(ProtoHero::HeroSoldiersCPP * obj);


private:
	HeroPropertyItem& 			data_;
	const OfflineResourceItem&  attr_;
	unsigned					soldier_rows_; //士兵排数
};

/////////////////////////////////////////////////////////////////////////////////////
class LogicHeroManager : public BattleSingleton, public CSingleton<LogicHeroManager>
{
private:
	friend class CSingleton<LogicHeroManager>;
	LogicHeroManager();
	virtual ~LogicHeroManager(){}

	enum {
			UP_RECRUIT_INTERVAL = 5, //英雄募兵间隔
			parade_times_max	= 6,  //阅兵次数上限
			recover_times_max	= 60,  //可回血次数上限
			RECRUIT_PROP_TIME	= 300, //一个募兵令5分钟
			parade_time_interval = 4*3600,  //阅兵次数增加时间间隔
	};

	//
	float RecruitSoldiresCostFactor(int level);

	void CheckHeroIdParams(unsigned uid, unsigned heroId);
public:
	virtual void CallDestroy() {Destroy();}

	void OnTimer1();

	/*
	 * 英雄的属性计算
	 */
	int GetAllFightAttr(unsigned uid, unsigned heroid, HeroFightAttr& result);
	//@end
	bool FinalData(unsigned uid, OfflineResourceItemHexp hexp[SG17_HERO_NUM]);
	void FinalData(unsigned uid, BattleReward& r);

	////////////////////////////////////////////////////////////////////////////////
	HeroPropertyItem& GetHeroPropertyItem(unsigned uid, unsigned heroId);

	//////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * 新手初始化
	 * param  uid(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int NewUserInit(unsigned uid);

	/*
	 * 登录时对英雄是否存在于共享内存中做校验
	 * param  uid(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int LoginHeroCheck(unsigned uid);

	/*
	 * 英雄解锁校验.-不带输出，推送
	 * param  uid(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	bool UnlockVerify(unsigned uid, unsigned gateid);

	/*
	 * 英雄解锁校验.-带输出
	 * param  uid(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	bool UnlockVerify(unsigned uid, unsigned gateid, ProtoHero::HeroBaseInfoCPP * heromsg);

	/*
	 * 解锁英雄
	 * param  uid(in),heroid(in),heromsg(out)
	 * exception runtime_error
	 * return 0-成功
	 */
	int UnlockHero(unsigned uid, unsigned heroid, string reason, ProtoHero::HeroBaseInfoCPP * heromsg);

	 //英雄招募
	int Process(unsigned uid, ProtoHero::RecruitHeroReq *reqmsg, ProtoHero::RecruitHeroResp * respmsg);

	//解雇英雄
	int Process(unsigned uid, ProtoHero::FireHeroReq *reqmsg, ProtoHero::FireHeroResp * respmsg);

	//穿装备
	int Process(unsigned uid, ProtoHero::DressEquipReq *reqmsg, ProtoHero::DressEquipResp * respmsg);

	//穿装备之后的处理
	int AfterDress(unsigned uid, unsigned equd, unsigned heroid);

	//脱装备
	int Process(unsigned uid, ProtoHero::UnDressEquipReq *reqmsg, ProtoHero::UnDressEquipResp * respmsg);

	//脱装备之后的处理
	int AfterUnDress(unsigned uid, unsigned equd, unsigned heroid);

	//一键装备
	int Process(unsigned uid, ProtoHero::OneKeyDressReq *reqmsg, ProtoHero::OneKeyDressResp * respmsg);

	//互换装备
	int Process(unsigned uid, ProtoHero::SwitchDressReq *reqmsg, ProtoHero::SwitchDressResp * respmsg);

	//使用募兵令
	int Process(unsigned uid, ProtoHero::UseRecruitPropReq* req, ProtoHero::UseRecruitPropResp* resp);

	//士兵数同步
	int Process(unsigned uid, ProtoHero::SyncSoldiersReq* req, ProtoHero::SyncSoldiersResp* resp);

	//打开装备洗练窗口
	int Process(unsigned uid, ProtoHero::OpenSmeltWindowReq* reqmsg, ProtoHero::OpenSmeltWindowResp* respmsg);

	//装备洗练
	int Process(unsigned uid, ProtoHero::EquipSmeltReq* reqmsg, ProtoHero::EquipSmeltResp* respmsg);
	int Process(unsigned uid, ProtoHero::EquipSmeltPropReq* reqmsg, ProtoHero::EquipSmeltPropResp* respmsg);

	//使用英雄经验道具
	int Process(unsigned uid, ProtoHero::UseHeroexpPropsReq* reqmsg, ProtoHero::UseHeroexpPropsResp* respmsg);

	//套装合成
	int Process(unsigned uid, ProtoHero::ComposeSuitReq* reqmsg, ProtoHero::ComposeSuitResp * respmsg);

	//打开阅兵窗口
	int Process(unsigned uid, ProtoHero::OpenParadeWindowReq* reqmsg, ProtoHero::OpenParadeWindowResp* respmsg);

	//阅兵
	int Process(unsigned uid, ProtoHero::ParadeReq* reqmsg, ProtoHero::ParadeResp* respmsg);

	//装载部件
	int Process(unsigned uid, ProtoHero::LoadCompoReq* reqmsg, ProtoHero::LoadCompoResp* respmsg);

	//卸载部件
	int Process(unsigned uid, ProtoHero::UnLoadCompoReq* reqmsg, ProtoHero::UnLoadCompoResp* respmsg);

	//强化部件
	int Process(unsigned uid, ProtoHero::StrengthenCompoReq* reqmsg, ProtoHero::StrengthenCompoResp* respmsg);

	//一键强化部件
	int Process(unsigned uid, ProtoHero::OneKeyStrengthenCompoReq* reqmsg, ProtoHero::OneKeyStrengthenCompoResp* respmsg);

	/*
	 * 招募英雄
	 * param  uid(in),heroid(in),heromsg(out)
	 * exception runtime_error
	 * return 0-成功
	 */
	int RecruitHero(unsigned uid, unsigned heroid, bool isfree, ProtoHero::HeroBaseInfoCPP * heromsg);

	int FullMessage(unsigned uid, User::Hero * heromsg);

	void RecruitSoldiersByStartTime(unsigned uid,  unsigned start_time);

	bool IsHeroFullHP(unsigned uid, unsigned heroid);

	//获取用户的所有累积的单挑
	unsigned GetUserRush(unsigned uid);

	//获取用户的所有累积的杀敌
	unsigned GetUserKill(unsigned uid);

	//获取用户的所有累积的占领城市
	unsigned GetUserOccupy(unsigned uid);

	//推送所有英雄的信息
	void SyncUserHerosInfo(unsigned uid);
	//解雇所有已招募英雄-ADMIN接口
	int AdminFireHero(unsigned uid, bool isAdmin = false);

	//招募英雄且穿戴装备-ADMIN接口
	int AdminRecuruitHero(unsigned uid, const BotConfig::BotHero * herocfgmsg, bool isAdmin = false);

	 //判断英雄是否已招募
	int VerifyHeroRecruit(unsigned uid, unsigned heroid);

	//单挑、杀敌、占领城市等成就的验证
	int HeroFightExternal(unsigned uid);

private:
	//发送英雄信息
	int SetHeroMessage(unsigned uid, unsigned heroid, ProtoHero::HeroBaseInfoCPP * heromsg);

	//募兵
	void RecruitSoldiers(unsigned uid,  unsigned nCnt);

	//使用英雄经验道具升级
	int AddHeroExpByProps(unsigned uid, unsigned heroid, unsigned equd, unsigned eqid, unsigned count, ProtoHero::UseHeroexpPropsResp *msg);

	//合成套装
	int ComposeEquipSuit(unsigned uid, unsigned equd, vector<unsigned> & material, ProtoHero::ComposeSuitResp * respmsg);

	//装载部件
	int LoadComponent(unsigned uid, unsigned compud, unsigned oldcompud, unsigned heroid, unsigned pos, ProtoHero::LoadCompoResp *respmsg);

	//卸载部件
	int UnloadComponent(unsigned uid, unsigned compud, unsigned heroid, ProtoHero::UnLoadCompoResp *respmsg);

	//部件强化
	int StrengthenComponent(unsigned uid, unsigned compud, vector<unsigned> &othcompud, ProtoHero::StrengthenCompoResp *respmsg);

	//部件一键强化
	int OneKeyStrengthenComponent(unsigned uid, unsigned compud, ProtoHero::OneKeyStrengthenCompoResp *respmsg);

	//计算英雄属性，内部调用接口
	int CalcuteHeroProperty(unsigned uid, unsigned heroid, ProtoHero::HeroBaseInfoCPP * hero);

	//添加英雄信息到属性管理中，用于战斗
	int AddHeroProperty(unsigned uid, unsigned heroid);

	//打开阅兵窗口
	int OpenParadeWindow(unsigned uid, ProtoHero::OpenParadeWindowResp * respmsg);

	//阅兵
	int Parade(unsigned uid, ProtoHero::ParadeResp * respmsg);

	//阅兵外部接口
	int ParadeExternalInterface(unsigned uid);

	//结算阅兵次数
	int CalcuteParadeTimes(unsigned uid);

	//装备任务统一接口
	int CheckDressMission(unsigned uid);

private:
	unsigned up_recruit_time_;
};


#endif /* LOGIC_HERO_MANAGER_H_ */
