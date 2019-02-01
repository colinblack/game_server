/*
 * LogicUserMangager.h
 *
 *  Created on: 2016-9-12
 *      Author: dawx62fac
 */

#ifndef LOGICUSERMANGAGER_H_
#define LOGICUSERMANGAGER_H_

#include "ServerInc.h"

//离线用户数据保存控制
class OffUserSaveControl
{
public:
	OffUserSaveControl(unsigned uid);

	~OffUserSaveControl();
private:
	unsigned uid_;
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

	void MarkLoad()
	{
		container_->m_data->SetPlusTS(index_);
	}

	DataBase& Obj()
	{
		return data_;
	}

	const DataBase& Obj() const
	{
		return data_;
	}

	unsigned Id() const { return data_.uid; }

	/////////////////////////////////////////////////////////////////////////
	void CostCash(int cash, const std::string& reason);
	void AddCash(int cash, const std::string& reason);
	unsigned GetCash();
	void CostCoin(int cash, const std::string& reason);
	void AddCoin(int cash, const std::string& reason);
	unsigned GetCoin();
	//累计充值
	void AccRecharge(int count, bool isPush = true);
	//
	void FinalAsynData();
	void AddAsynItem(unsigned id, unsigned count, const std::string& op = "asyn_data");

	//首充
	bool IsGetFirstRechargeReward() const;
	void SetFirstRechargeRewardStatus();

	//再次充值
	bool IsGetSecondRechargeReward() const;
	void SetSecondRechargeRewardStatus();

	//零点逻辑，解决登录跨天导致的bug
	void EveryDayAction(int di = 1);

	void 	RefreshVIPLevel(bool isPush = true);



	//获取用户注册小时数
	unsigned GetRegisterHours() const;

	bool AddExp(int exp);

	//加体力
	void AddPower(int power, int limit, const std::string& reason);
	//消耗体力
	void CostPower(int power, const std::string& reason);

	//体力恢复
	void RecoverPower(unsigned now, unsigned last);

	//加荣誉
	void AddHonor(int honor, const std::string& reason);

	void CostHonor(int honor, const std::string& reason);
	//过去关卡记录
	unsigned GetStages();

	void UpdateStages(unsigned idx);
	//玩家等级
	unsigned GetLevel();

	//获取图鉴
	bool GetArchive(unsigned id);

	//激活图鉴锁片
	bool ActArchiveChip(unsigned id, int idx);

	//取消激活图鉴碎片
	bool UnActArchiveChip(unsigned id, int idx);

	//图鉴升级
	bool ArchiveUpLevel(unsigned id);

	//更新图鉴奖励领奖次数
	bool UpateArchiveRewardCount(unsigned id);

	//获取体力道具对应索引
	int GetPowerPropIndex(unsigned propid) const;

	//充值体力道具使用次数
	void RestPowerPropTimes();

	//更新体力道具使用次数
	bool UpdatePowerPropTimes(int idx);

	//更新体力道具使用时戳
	void UpdatePowerPropTs(unsigned ts);

	//重置好友赠送体力
	void ResetDonatePower();

	//更新好友赠送体力时戳
	void UpdateDonatePowerTs(unsigned ts);

	void SetHero(unsigned heroid);

	//通用属性操作
	void BaseProcess(const ::CommonGiftConfig::BaseItem& base, DataCommon::UserBaseChangeCPP* obj,
			const std::string& reason, double factor = 1.0);

	//检查条件
	int CheckBaseBeforeCost(unsigned uid, const string & reason, const CommonGiftConfig::BaseItem & base);

	void FullMessage(User::Base* obj) const;
private:
	int _Index(unsigned uid);

	int AsynType2ResourceType(ASYN_TYPE type);

	void OnUserUpgradeReward(unsigned old_level);
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

public:
	virtual void CallDestroy() { Destroy();}

	void OnTimer1();

	//消费钻石
	void CostCash(unsigned uid, int cash, string reason, unsigned & newcash);

	//每日零点推送给所有在线用户奖励
	int EveryDayAction();

	int DonatePower(unsigned uid, unsigned power, const string& reason); //赠送体力
	void NotifyRecharge(unsigned uid, unsigned cash);

	//消耗钻石
	int Process(unsigned uid, User::CostCashReq* req, User::CostCashResp* resp);

	//体力购买
	int Process(unsigned uid, User::BuyPowerReq* req, User::BuyPowerResp* resp);

	//处理邀请好友链接
	int Process(unsigned uid, User::InviteActivityUrlReq* req);

	//跨服处理邀请好友链接
	int Process(User::CSInviteActivityUrlReq* req);

	//领取邀请好友奖励
	int Process(unsigned uid, User::GetInviteRewardReq* req, User::GetInviteRewardResp* resp);

	//领取累积邀请好友奖励
	int Process(unsigned uid, User::GetAddInviteRewardReq* req, User::GetAddInviteRewardResp* resp);

	//获取抽奖活动奖励
	int Process(unsigned uid, User::GetDrawRewardReq* req, User::GetDrawRewardResp* resp);

	//新手引导前端主动加经验
	int Process(unsigned uid, User::NewUserAddExpReq* req, User::NewUserAddExpResp* resp);

	//获取抽奖活动奖励id
	unsigned GetDrawRewardId(unsigned uid);
	//通用处理，包含通用消耗和通用奖励
	int CommonProcess(unsigned uid, const CommonGiftConfig::CommonModifyItem& modifyitem, const std::string& reason,
			DataCommon::CommonItemsCPP* obj, double multiple = 1.0);
	//重置邀请奖励
	void ResetInviteRwards(unsigned uid, unsigned lastOfftimeTs);

private:
	//通用处理底层
	void CommonUnderlaying(DBCUserBaseWrap& user, const CommonGiftConfig::CommonModifyItem& cfg, const std::string& reason,
			DataCommon::CommonItemsCPP* obj, double multiple = 1.0);

	void CheckPropsBeforeCost(unsigned uid, const string & reason, const CommonGiftConfig::CommonModifyItem& cfg);
private:
	BaseManager* baseData_;
	unsigned  start_time;
	map<unsigned, unsigned>	 draw_reward_cost_cash_; //保存抽检上次消耗钻石
	map<unsigned, unsigned>  draw_reward_id_; //保存抽奖奖励id

	std::deque<_RechargeRecord> recharge_records_;
};

#endif /* LOGICUSERMANGAGER_H_ */
