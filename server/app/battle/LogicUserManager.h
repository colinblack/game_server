/*
 * LogicUserMangager.h
 *
 *  Created on: 2016-9-12
 *      Author: dawx62fac
 */

#ifndef LOGICUSERMANGAGER_H_
#define LOGICUSERMANGAGER_H_

#include "ServerInc.h"

class UVIPPower
{
public:
	UVIPPower();

	UVIPPower(unsigned level);

	void RestoreEveryBasePower(DataBase& base);

	float GetMarketAdd() const; //黑市加成
	unsigned GetAutoBuildCnt() const; //自动建造次数

	unsigned GetFightExpAdd() const
	{
		return fight_exp_add_;
	}

	//
	unsigned ResourceYieldAdd() const
	{
		return resource_yield_add_;
	}

	unsigned StorageCapacityAdd() const
	{
		return storage_capacity_add_;
	}

	float PolityTaskFactor() const
	{
		return polity_task_factor_;
	}

	unsigned IronAdd() const
	{
		return iron_add_;
	}

	void WeaponProbAdd(std::vector<unsigned>& result) const;
private:
	void InitFromLvlPower(const VIPConfig::UVIPLvlPower& extra);

private:
	//base
	unsigned integral_cnt_; //补给次数 后勤奖励
	unsigned market_cnt_; 	//集市次数
	unsigned sacrifice_cnt_; //免费征收次数
	unsigned order_cnt_;	 //地勤令
	unsigned bmarket_add_;	 //黑市加成
	unsigned refresh_cnt_;	 //免费洗练
	unsigned market_add_;	 //集市加成
	unsigned auto_build_cnt_; //自动建造
	unsigned order_limit_;    //地勤令限制
	unsigned iron_add_;		   //黄金加成

	//extra
	unsigned resource_yield_add_; 	//资源产量
	unsigned fight_exp_add_;	  	//战斗产出角色经验增加
	float	 polity_task_factor_; 	//政务时间增加资源数
	unsigned weapon_prob_[4];		//军工升级暴击概率提升值
	unsigned storage_capacity_add_; //仓库容量加成
};

class DBCUserBaseWrap
{
public:
	DBCUserBaseWrap(unsigned uid);
	DBCUserBaseWrap(unsigned index, DataBase& data);

	void Save()
	{
		container_->m_data->MarkChange(index_);
	}

	DataBase& Obj()
	{
		return data_;
	}

	const DataBase& Obj() const
	{
		return data_;
	}

	bool AddExp(int exp);
	void UseFreeFlamen(int cnt);
	void FlamenCostCnt(int type, int cnt);
	void AddBuildExploit(int cnt);
	void AddTicket(int t);

	/////////////////////////////////////////////////////////////////////////
	void CostCash(int cash, const std::string& reason);
	void AddCash(int cash, const std::string& reason);
	//添加资源
	/*
	 * COINTS_TYPE = 1, //银币
	 * WOOD_TYPE = 2, //木头
	 * FOOD_TYPE = 3, //食物
	 * IRON_TYPE = 4, //镔铁
	 */
	void AddResource(std::map<unsigned, unsigned>& resource, const std::string& reason);
	void AddResource(int coins, int wood, int food, int iron, const std::string& reason);
	void CostUserResource(int coins, int wood, int food, int iron, const string& reason);

	//资源生产
	void RestoreResource();

	//是否通过副本关卡
	bool IsPassNPC(unsigned id, unsigned nCnt = 1);

	//建筑升级消耗
	int  BuildUpgrade(unsigned buildid, unsigned buildLvl);
	//使用募兵令
	int UseRecruitProp(unsigned nCnt);
	int RealUseRecruitProp(unsigned nCnt) const;
	//增加募兵令
	int AddRecruitProp(unsigned count , const string& reason);
	//增加黄金锤子
	int AddGoldHammer(unsigned count, const string& reason);
	void CostHarmmer(unsigned cnt, const std::string& reason);

	//增加龙鳞
	int AddMarket(unsigned count, const string & reason);
	int CostMarket(int count, const string & reason);

	//积分兑换
	int CostTicket(int count, const string & reason);

	//功勋宝箱
	void AddExploitBox(unsigned cnt);
	void UseExploitBox(unsigned cnt);

	bool FinalOfflineResource(const OfflineResourceItem& offline);
	void FinalBattleReward(BattleReward& r);
	//
	void FinalAsynData();
	void AddAsynItem(unsigned id, unsigned count, const std::string& op = "asyn_data");

	void ClearBuildExploit();
	//
	void Reward(const ::CommonGiftConfig::BaseReward& base
				, ::DataCommon::CommonBaseRewardCPP* obj
				, const std::string& reason, float factor = 1.0);

	//首充
	bool IsGetFirstRechargeReward() const;
	void SetFirstRechargeRewardStatus();
	//@ned

	//建筑自动升级
	void SetAutoBuild();
	bool IsAutoBuildPower() const;

	//整点奖
	void UseIntegralReward();

	//设置闯关记录id
	bool SetNPCPassId(unsigned id);
	//重置国家任务状态
	void ResetCountryTaskStatus();
	void ResetCountryTaskStatus(unsigned offline_time);

	//
	bool IsGetMissionPersonalReward(unsigned task_no) const;
	bool IsGetMissionCountryReward(unsigned task_no) const;

	void SetGetMissionPersonalRewardStatus(unsigned task_no);
	void SetGetMissionCountryRewardStatus(unsigned task_no);

	//零点逻辑，解决登录跨天导致的bug
	void EveryDayAction(int di = 1);

	void RestoreRecruitProp(int interval_days);

	//VIP
	UVIPPower VIPPower() const;
	void 	RefreshVIPLevel(bool isPush = true);
	void 	RestoreEveryVIPReward();

	void 	SetVIPReward();
	//////////////////////////////////////////////////////////
	//竞技场
	void 	ResetPkCnt();
	void 	UserPkCnt(int cnt = 1);
	void 	SetPkRewardTime(unsigned nTime);

	//领取了军职俸禄
	void    SetJobSalary();

	//矿洞
	void  OpenNormalHole(int exp);
	void  OpenKingdomHole(int exp);
	void  DonateHole(int exp);
	void  GetKingdomMineReward();

	void SetTokenOpTs(unsigned ts);

	//闯关送钻 标记
	void SetPassActivityRewardFlag(int idx);
	bool IsSetPassActivityRewardFlag(int idx) const;

	//至尊洗练次数增加
	void AddArefreshCnt(int cnt);

	//获取用户注册小时数
	unsigned GetRegisterHours() const;

	void FullData(const BotConfig::BotPlayer* obj);

	void FullMessage(DataCommon::UserResourceCPP* obj);

private:

	unsigned GetCountryTaskStage(bool isDiffDay, unsigned ts) const;

	int _Index(unsigned uid);

	void OnUserUpgradeReward(unsigned old_level);


	int AsynType2ResourceType(ASYN_TYPE type);
private:
	BaseManager*	container_;
	unsigned 		index_;
	DataBase& 		data_;
};


class LogicUserManager : public BattleSingleton, public CSingleton<LogicUserManager>
{
	class _RechargeRecord
	{
	public:
		_RechargeRecord(unsigned nUid, unsigned nCash)
			: uid(nUid), cash(nCash)
		{

		}

		unsigned uid;
		unsigned cash;
	};
private:
	friend class CSingleton<LogicUserManager>;
	LogicUserManager();

	enum
	{
		mission_times_max = 24,	//政务次数最大值
		loyal_exchange_limit = 100,  //民忠兑换限制
		loyal_value_max = 200,  //民忠上限
		affair_time_interval = 1200,  //间隔20分钟
	};

	float GetIntegralTimeFactor(unsigned level);
public:
	virtual void CallDestroy() { Destroy();}

	void OnTimer1();

	//登录时的检查
	int LoginCheck(unsigned uid);

	//用户经验增加
	bool AddExp(unsigned uid, int exp);

	//消耗资源
	void CostUserResource(unsigned uid, int coins, int wood, int food, int iron, string reason, Json::Value & result);
	void AddUserResource(unsigned uid, int coins, int wood, int food, int iron, string reason, Json::Value & result);
	//消费钻石
	void CostCash(unsigned uid, int cash, string reason, unsigned & newcash);

	//每日零点推送给所有在线用户奖励
	int EveryDayAction();

	//募兵令
	int UseRecruitProp(unsigned uid, unsigned nCnt);

	//提供接口，计算建筑升级是否增加政务次数
	int VerifyGovernAffairTimes(unsigned uid, unsigned buildid);

	//设置机器人数据
	void SetBotPlayerData(unsigned uid, const BotConfig::BotPlayer* obj);

	void NotifyRecharge(unsigned uid, unsigned cash);

	//消耗钻石
	int Process(unsigned uid, User::CostCashReq* req, User::CostCashResp* resp);
	//首充奖励
	int Process(unsigned uid, ProtoReward::FirstRechargeReq* req, ProtoReward::FirstRechargeResp* resp);
	//整点地勤奖励
	int Process(unsigned uid, ProtoReward::IntegralTimeReq* req, ProtoReward::IntegralTimeResp* resp);
	//vip奖励
	int Process(unsigned uid, ProtoReward::VIPReq* req, ProtoReward::VIPResp* resp);

	//打开政务事件窗口
	int Process(unsigned uid, ProtoGovernAffair::OpenAffairWindowReq* req, ProtoGovernAffair::OpenAffairWindowResp * respmsg);

	//政务事件奖励领取
	int Process(unsigned uid, ProtoGovernAffair::GetAffairRewardReq* req, ProtoGovernAffair::GetAffairRewardResp * respmsg);

	//政务事件民忠兑换
	int Process(unsigned uid, ProtoGovernAffair::LoyalExchangeReq* req, ProtoGovernAffair::LoyalExchangeResp * respmsg);

	//领取普通礼包
	int Process(unsigned uid, User::OpenNormalGifgBagReq* req, User::OpenGifgBagResp* resp);
	//幸运礼包
	int Process(unsigned uid, User::OpenLuckGifgBagReq* req, User::OpenGifgBagResp* resp);
	//使用道具
	int Process(unsigned uid, User::UseTimeLimitPropReq* req, User::UseTimeLimitPropResp* resp);


	//升级洗练令
	int Process(unsigned uid, User::UseUpdateSmeltPropReq* req, User::UseUpdateSmeltPropResp* resp);
	//指定洗练令
	int Process(unsigned uid, User::UseSpecificSmeltPropReq* req, User::UseSpecificSmeltPropResp* resp);

	//奖励的统一接口
	void OpReward(DBCUserBaseWrap& user
			, const ::RewardConfig::Reward& cfg
			, const std::string& reason
			, User::RewardBagInfo* obj);
private:
	//打开政务事件窗口
	int OpenAffairWindow(unsigned uid, ProtoGovernAffair::OpenAffairWindowResp * respmsg);

	//处理政务事件
	int GetAffairReward(unsigned uid, unsigned index, ProtoGovernAffair::GetAffairRewardResp * respmsg);

	//政务事件相关外部接口
	int AffairExternalInterface(unsigned uid);

	//民忠兑换外部接口
	int LoyalExternalInterface(unsigned uid);

	//民忠兑换
	int LoyalExchange(unsigned uid, ProtoGovernAffair::LoyalExchangeResp * respmsg);

	//增加政务次数，当政务次数为1时进行推送
	int AddAndPushMissonTimes(unsigned uid, unsigned times);

	//政务次数增加
	int AddMissionTimes(unsigned uid, unsigned times);

	//刷新政务事件
	int RefreshAffair(unsigned uid);

	void GetLuckBagGiftIndexs(const EquipmentConfig::LuckGiftBag& cfg, std::vector<int>& result);

private:
	BaseManager* baseData_;
	unsigned  start_time;

	std::deque<_RechargeRecord> recharge_records_;
};

#endif /* LOGICUSERMANGAGER_H_ */
