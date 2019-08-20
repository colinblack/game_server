/*
 * LogicCMDUnit.h
 *
 *  Created on: 2016-4-12
 *      Author: dawx62fac
 */

#ifndef LOGICCMDUNIT_H_
#define LOGICCMDUNIT_H_

#include <stdexcept>
#include "LogicEquipment.h"
#include "LogicUnitWrap.h"
#include "LogicCmdBase.h"
#include "DataFortunePacks.h"

//幸运连连
const int MAX_REWARD_ITEMS = 8;
const int DEFAULT_RATE_VALUE = 20;  //默认的概率值

//充值送星级
const int MAX_STAR_ITEMS = 4;

//武将训练
const int SUN_ZI_BING_FA_EQID = 4015;   //孙子兵法的装备id

//天命
const int MAX_CHOUJIANG_ITEMS = 18;

//国庆盛典
#define  COUNTRY_DAY_REWARD_MONEY_BEGIN_TS  (1475164800)
#define  COUNTRY_DAY_REWARD_MONEY_END_TS    (1475769600)

//每1经验所消耗的英雄帖
#define  PER_EXP_HERO_POST	50

//暑假前奏
class PreSummerUnit
{
	enum {
		EXCHANGE_ITEMS = 3,
	};
public:
	PreSummerUnit(unsigned uid, unsigned type);

	//
	unsigned GetVersionCfg();
	//活动中
	bool IsActiving(unsigned nTime);

	//兑换奖励
	void Exchange(UserWrap& userWrap, unsigned equipId, Json::Value& result);

	void GetData(UserWrap& userWrap, Json::Value& result);

	//获取剩余积分
	unsigned GetSurplusPoint(UserWrap& userWrap);

	void Save();

	CDataXML* DataIns();
private:
	unsigned m_nUid;
	bool m_bSave;
	unsigned m_type;
	string m_bts, m_ets, m_ver;
	unsigned m_nat;

	Json::Value m_jsonData;
};

//尊主榜
class LordUnit
{
	enum {
		WORSHIP_CNT = 3,
	};
public:
	LordUnit(unsigned uid);
	void Worship(int id, int type, Json::Value& result);

private:
	void Save();

	int HttpRequest(const std::string& action, const std::string& data, Json::Value& result);

	void ProvideReward(Json::Value& result);

	ItemAdd GetReward();
private:
	unsigned m_nUid;

	Json::Value m_jsonData;
};

//幸运连连
class FortunatelyUnit : public BaseCmdUnit
{
public:
	class RewardParams : public UnitUdCmdParams
	{
	public:
		RewardParams(const Json::Value& data)
			: UnitUdCmdParams(data)
		{
			type_ = ValueAsInt("type");
			//判断类型是否正常
			if (1 != type_ && 2 != type_)
			{
				throw std::runtime_error("type_param_error");
			}
		}

		int Type() const { return type_; }
	private:
		int type_;
	};
public:
	FortunatelyUnit(const UserWrap& user);

	int CheckInitial(UserWrap& user, const BaseCmdParams& params, Json::Value& result);
	int RefreshWheel(UserWrap& user, const UnitUdCmdParams& params, Json::Value& result);
	int GetReward(UserWrap& user, const RewardParams& params, Json::Value& result);

	void Save();

	static unsigned GetVersionCfg();

private:
	void DoRefreshWheel(bool isFree, Json::Value & result, Json::Value & user_flag, int ud=0);

    void ProvideFortunatelyReward(int cash, vector<unsigned> vctIndexs, Json::Value &result, Json::Value & user_flag);

    int getSubNumByCh(unsigned ch);

};

//天命
class TurnPlateUnit : public BaseCmdUnit
{
public:
	class RefreshParams : public UnitUdCmdParams
	{
	public:
		RefreshParams(const Json::Value& data)
			: UnitUdCmdParams(data)
		{
#ifdef SG_USE_CASH
			type_ = ValueAsInt("type");
			if (REFRESH_BY_CASH != type_ && REFRESH_BY_COIN != type_)
			{
				throw std::runtime_error("type_param_error");
			}
#else
			type_ = 0;
#endif
		}

		int Type() const { return type_; }
	private:
		int type_;
	};

	class RewardParams : public UnitUdCmdParams
	{
	public:
		RewardParams(const Json::Value& data)
			: UnitUdCmdParams(data)
		{
			type_ = ValueAsInt("type");
			//判断类型是否正常
			if (1 != type_ && 2 != type_)
			{
				throw std::runtime_error("param_error");
			}
		}

		int Type() const { return type_; }
	private:
		int type_;
	};
public:

	enum
	{
		REFRESH_BY_CASH = 0X0,   //钻石刷新
		REFRESH_BY_COIN = 0X1,   //金币刷新
	};

	TurnPlateUnit(const UserWrap& user);

	int RefreshWheel(UserWrap& user, const RefreshParams& params, Json::Value& result);
	int GetReward(UserWrap& user, const RewardParams& params, Json::Value& result);
	int CheckInitial(UserWrap& user, const BaseCmdParams& params, Json::Value& result);

	static unsigned GetVersionCfg();
private:
	void DoRefreshWheel(Json::Value & result);

    void ProvideTrunPlateReward(UserWrap& userWrap, int cash, vector<unsigned> vctIndexs, Json::Value &result);

    int getSubNumByCh(unsigned ch);

    void InitGiftSub(string key, int num, Json::Value & gift);
};

//充值自选
class RechargeOptionalUnit
{
public:
	RechargeOptionalUnit(unsigned uid);

	static unsigned GetVersionCfg();
	//活动中
	static bool IsActiving(unsigned nTime);

	void UpdateRecharge(unsigned cash);

	void GetOptionalReward(UserWrap& userWrap, unsigned rewardcnt,Json::Value & data, Json::Value &result);
private:
	void ResetNewact(unsigned version);
	void Save();

private:
	unsigned m_nUid;
	Json::Value m_jsonData;
};

//消费自选
class PayOptionalUnit
{
public:
	enum{
		per_cash_one_times = 888,  //多少消费的钻石对应一次奖励
	};

	PayOptionalUnit(unsigned uid);

	static unsigned GetVersionCfg();

	//检查版本号的接口
	int CheckVersion(Json::Value & result);

	void GetOptionalReward(UserWrap& userWrap, unsigned rewardcnt,Json::Value & data, Json::Value &result);
private:
	void ResetNewact(unsigned version);
	void Save();

private:
	unsigned m_nUid;
	Json::Value m_jsonData;
};

//充值送星级
class HeroUpgrideUnit
{
public:
	HeroUpgrideUnit(unsigned uid);

	static unsigned GetVersionCfg();
	//活动中
	static bool IsActiving(unsigned nTime);

	void UpdateZMLUsed(unsigned num);

	void UpgrideHeroNew(UserWrap& userWrap, unsigned index, unsigned target, Json::Value& result);

private:
	void ResetNewact(unsigned version);
	void Save();

private:
	unsigned m_nUid;
	Json::Value m_jsonData;
};

////////////////////////////////////////////////////////
//开区充值大礼包
class NewRechargeUnit : public BaseCmdUnit
{
	enum {
		BAG_TYPE_CNT = 8,
	};
public:
	NewRechargeUnit(unsigned uid);

	//领取礼包接口
	void GetRewardBagAction(const UserWrap& userWrap, unsigned id, Json::Value& result);
private:

	bool IsActiving(unsigned nTime);

	void ProvideReward(unsigned id, XMLNewRechargeRewardItem& item, Json::Value& result);
};

////////////////////////////////////////////////////////
//每日团购
class GroupBuyDailyUnit : public BaseCmdUnit
{
	enum {
		GET_ITEMS = 4, //领取4次
		POINTS_ONCE = 10, //一次积分10
	};

public:
	GroupBuyDailyUnit(unsigned uid, const UserWrap& user);

public:
	void BuyAction(UserWrap& user, Json::Value& result);
	void GetRewardAction(unsigned index, UserWrap& user, Json::Value& result);
};

////////////////////////////////////////////////////////
//充点小钱
class LittleRechargeUnit : public BaseCmdUnit
{
public:
	LittleRechargeUnit(const UserWrap& user);

	void GetReward(UserWrap& user, Json::Value& result);
};

////////////////////////////////////////////////////////
//竞技场领奖
class AthleticsRankUnit : public BaseCmdUnit
{
public:
	AthleticsRankUnit(const UserWrap& user);

	int GetReward(UserWrap& user, const BaseCmdParams& params,  Json::Value& result);
};

////////////////////////////////////////////////////////
//每日奖 领取能量
class DailyRewardUnit : public BaseCmdUnit
{
public:
	DailyRewardUnit(const UserWrap& user);

	int GetReward(UserWrap& user, const BaseCmdParams& params,  Json::Value& result);
};

////////////////////////////////////////////////////////
//月度礼包
class MonthGiftParams : public BaseCmdParams
{
public:
	MonthGiftParams(const Json::Value& jsonData);
	unsigned Index() const;
private:
	unsigned index_;
};

class MonthGiftBagUnit : public BaseCmdUnit
{
public:
	MonthGiftBagUnit(const UserWrap& user);
	int GetReward(UserWrap& user, const MonthGiftParams& params,  Json::Value& result);
protected:
	unsigned GetCostDiamond(unsigned index);
};

////////////////////////////////////////////////////////
//选国家
class KingdomSelectParams : public BaseCmdParams
{
public:
	KingdomSelectParams(const Json::Value& jsonData);
	unsigned Kingdom() const { return kingdom_; }
	unsigned Type() const { return type_; }
private:
	unsigned kingdom_;
	unsigned type_; //1--手动选 0--自动选
};

class KingdomSelectUnit : public BaseCmdUnit
{
public:
	KingdomSelectUnit(const UserWrap& user);
	int Select(UserWrap& user, const KingdomSelectParams& params,  Json::Value& result);
private:
	int GetAddCoins(unsigned uid, unsigned type, unsigned kingdom);
};

////////////////////////////////////////////////////////
//组合商店
class CombinedShopParams : public BaseCmdParams
{
public:
	CombinedShopParams(const Json::Value& jsonData);

	unsigned Index() const { return index_; }
	const std::vector<unsigned>& Equips() const { return equips_; }
private:
	unsigned index_;
	std::vector<unsigned> equips_;
};

class CombinedShopUnit : public BaseCmdUnit
{
public:
	CombinedShopUnit(const UserWrap& user);

	int Buy(UserWrap& user, const CombinedShopParams& params,  Json::Value& result);
};
////////////////////////////////////////////////////////
//预告功能
class NewerAdvanceParams : public BaseCmdParams
{
public:
	NewerAdvanceParams(const Json::Value& jsonData);
	unsigned BuildLevel() const { return build_level_; }
private:
	unsigned build_level_;
};

class NewerAdvanceUnit : public BaseCmdUnit
{
public:
	NewerAdvanceUnit(const UserWrap& user);

	int Get(UserWrap& user, const NewerAdvanceParams& params,  Json::Value& result);
};

////////////////////////////////////////////////////////
//步步为营
class TreasureHuntExchangeParams : public BaseCmdParams
{
public:
	TreasureHuntExchangeParams(const Json::Value& jsonData);

	unsigned Index() const { return index_; }
	bool IsPoint() const { return is_point_; }
private:
	unsigned index_;
	bool	 is_point_;
};

class TreasureHuntUnit : public BaseCmdUnit
{
public:
	TreasureHuntUnit(const UserWrap& user);

	//兑换
	int Exchage(UserWrap& user, const TreasureHuntExchangeParams& params, Json::Value& result);
private:
	bool IsOpen() const; //是否开启活动
};

////////////////////////////////////////////////////////
//圣诞活动
class ChristmasParams : public BaseCmdParams
{
public:
	ChristmasParams(const Json::Value& jsonData);

	unsigned Id() const { return id_; }
private:
	unsigned id_;
};


class ChristmasUnit : public BaseCmdUnit
{
public:
	ChristmasUnit(const UserWrap& user);

	//兑换
	int Exchage(UserWrap& user, const ChristmasParams& params, Json::Value& result);
	//砸蛋
	int KnockEgg(UserWrap& user, const ChristmasParams& params, Json::Value& result);
private:
	bool IsOpen() const;

	unsigned GetVersionCfg() const;

	unsigned SurplusPoint() const;

	void ProductEquipItem(const DataXMLChristmasEgg& eggs, DataXMLChristmasEggItem& result);
private:
	Json::Value m_jsonStats_;
	unsigned total_recharge_point_ ;
};
////////////////////////////////////////////////////////
//积分相关
class PointCmdUnit : public BaseCmdUnit
{
public:
	PointCmdUnit(const UserWrap& user,const std::string& type);

	virtual ~PointCmdUnit() {}

	bool IsOpen(const std::string& type) const;

	void Save();

	unsigned SurplusPoint(UserWrap& user, int nfactor) const;
	void	 CostPoint(unsigned point);
	unsigned TotalPoint(UserWrap& user, int nfactor) const;
protected:
	void LoadData(unsigned uid);

	Json::Value m_jsonPoint_;
};
///////////
class PointExchangeParams : public BaseCmdParams
{
public:
	PointExchangeParams(const Json::Value& jsonData);

	unsigned Index() const { return index_; }
	unsigned Cnt() const { return cnt_; }

private:
	unsigned index_; //0-开始
	unsigned cnt_;	 //兑换个数
};

//积分兑换
class PointExchangeUnit : public PointCmdUnit
{
public:
	PointExchangeUnit(const UserWrap& user);

	int Exchage(UserWrap& user, const PointExchangeParams& params, Json::Value& result);
};

class PointCutPriceBuyParams : public BaseCmdParams
{
public:
	PointCutPriceBuyParams(const Json::Value& jsonData);

	unsigned Id() const { return id_; }
private:
	unsigned id_;
};

class PointCutPriceUnit : public PointCmdUnit
{
public:
	PointCutPriceUnit(const UserWrap& user);

	int Buy(UserWrap& user, const PointCutPriceBuyParams& params, Json::Value& result);
private:
	bool IsBuy(unsigned id);
	void SetBuyOp(unsigned id);
};
////////////////////////////////////////////////////////
//建筑皮肤
class BuildingSkinBuyParams : public BaseCmdParams
{
public:
	BuildingSkinBuyParams(const Json::Value& jsonData);

	unsigned Id() const { return id_; }
private:
	unsigned id_;
};

class BuildingSkinUseParams : public BaseCmdParams
{
public:
	BuildingSkinUseParams(const Json::Value& jsonData);

	unsigned Id() const { return id_; }
	unsigned EqUd() const  { return eq_ud_; }
private:
	unsigned id_;
	unsigned eq_ud_;
};

class BuildingSkinReletParams : public BaseCmdParams
{
public:
	BuildingSkinReletParams(const Json::Value& jsonData);

	unsigned Id() const { return id_; }
	unsigned Type() const  { return type_; }
private:
	unsigned type_;
	unsigned id_;
};

class BuildingSkinUint : public BaseCmdUnit
{
public:
	BuildingSkinUint(const UserWrap& user);

	int Buy(UserWrap& user, const BuildingSkinBuyParams& params, Json::Value& result);
	int Use(UserWrap& user, const BuildingSkinUseParams& params, Json::Value& result);
	int Relet(UserWrap& user, const BuildingSkinReletParams& params, Json::Value& result);
private:
	void Save(UserWrap& user);

	bool IsValid(unsigned id);
private:
	Json::Value m_jsonSkin;
};
////////////////////////////////////////////////////////
//砸罐子领取
class HammerHitUnit : public BaseCmdUnit
{
public:
	HammerHitUnit(const UserWrap& user);

	int DrawHammer(UserWrap& user, const BaseCmdParams& params, Json::Value& result);
};

////////////////////////////////////////////////////////
//七日登录
class TutorLoginUnit : public BaseCmdUnit
{
public:
	TutorLoginUnit(const UserWrap& user);

	int Reward(UserWrap& user, const UnitIdCmdParams& params, Json::Value& result);
};

////////////////////////////////////////////////////////
//霸业礼包
class ImperialGiftOpenParams  : public UnitIdCmdParams
{
public:
	ImperialGiftOpenParams(const Json::Value& jsonData);

	unsigned EquipUd() const  { return equip_ud_; }
private:
	unsigned equip_ud_;
};


class ImperialGiftUnit : public BaseCmdUnit
{
public:
	ImperialGiftUnit(const UserWrap& user);

	int Get(UserWrap& user, const BaseCmdParams& params, Json::Value& result);
	int Open(UserWrap& user, const ImperialGiftOpenParams& params, Json::Value& result);
};

////////////////////////////////////////////////////////
//限时冲级
class TimeLimitUpgradeRewardParams : public BaseCmdParams
{
public:
	TimeLimitUpgradeRewardParams(const Json::Value& jsonData);

	unsigned GradeRange() const { return grade_range_; }
private:

	unsigned grade_range_;
};

class TimeLimitUpgradeUnit : public BaseCmdUnit
{
public:
	TimeLimitUpgradeUnit(const UserWrap& user);

	int Reward(UserWrap& user, const TimeLimitUpgradeRewardParams& params, Json::Value& result);
private:
	CDataOpenAreaActivity* GetOpenAreaActivityPoint();
};

////////////////////////////////////////////////////////
//跨服天梯 cross server
class CServerladderUnit : public BaseCmdUnit
{
public:
	CServerladderUnit(const UserWrap& user);

	int Reward(UserWrap& user, const BaseCmdParams& params, Json::Value& result);
private:
	Json::Value m_jsonCrmr;
};

////////////////////////////////////////////////////////
//鸡年纳福
class YearFortuneUnit : public BaseCmdUnit
{
public:
	YearFortuneUnit(const UserWrap& user);

	//获取信息  //此接口用于当数据接口为空时，初始化奖品库
	int Info(UserWrap& user, const BaseCmdParams& params, Json::Value& result);
	//转运
	int Transfer(UserWrap& user, const BaseCmdParams& params, Json::Value& result);
	//
	int Reward(UserWrap& user, const BaseCmdParams& params, Json::Value& result);
private:
	void Reset();

	int BuildReward(int index);
	int TotalPoint(const UserWrap& user) const;
private:

};

//////////////////////////////////////////////////////////
//寒假狂欢
class WHRevelayDrawRewardParams : public BaseCmdParams
{
public:
	WHRevelayDrawRewardParams(const Json::Value& data);

	unsigned Cnt() const { return cnt_; }
private:
	unsigned cnt_;
};

class WinterHolidayRevelayUnit : public BaseCmdUnit
{
public:
	WinterHolidayRevelayUnit(const UserWrap& user);

	int DrawReward(UserWrap& user, const WHRevelayDrawRewardParams& params, Json::Value& result);
	int GetReward(UserWrap& user, const UnitIndexCmdParams& params, Json::Value& result);
private:
	void Reset(unsigned nVersion);
	int TotalRecharge(const UserWrap& user) const;
};

////////////////////////////////////////////////////////////
//塔楼外传
class TowerTreasureParams : public UnitIndexCmdParams
{
public:
	TowerTreasureParams(const Json::Value& data);

	int Ud() const { return ud_; }
private:
	int ud_;
};

class TowerOnceParams : public BaseCmdParams
{
public:
	TowerOnceParams(const Json::Value& data);

	unsigned Ud() const { return ud_; }
private:
	unsigned ud_;
};

class TowerActivityUnit : public BaseCmdUnit
{
	enum {
		TOWER_DEAFAULT_ID = 0,  //默认解锁塔楼
		TOWER_CNT = 5,          //塔楼的个数
		TOWER_REWARD_CNT = 9,   //挖宝的位置
		TOTAL_TOWER_ACT_CNT		= 100,  //累计挖宝上限
		TOWER_SKIP_ID = 3,      //用钻直接解锁的楼
		TOWER_ACT_CNT = 5,      //每个楼的挖宝次数
	};

	enum {
		TOWER_EQUIPS_ID = 8801,  //奖励道具
		TOWER_EXTRA_ID = 8804,
	};
public:
	TowerActivityUnit(const UserWrap& user);

	//重置
	int ResetImpl(UserWrap& user, const UnitIndexCmdParams& params, Json::Value& result);
	//探宝
	int TreasureImpl(UserWrap& user, const TowerTreasureParams& params, Json::Value& result);
	//一键
	int OnceImpl(UserWrap& user, const TowerOnceParams& params, Json::Value& result);
	//解锁
	int UnlockFloorImpl(UserWrap& user, const BaseCmdParams& params, Json::Value& result);
private:
	bool IsUnlock(unsigned index) const;
	void SetUnlock(unsigned index);
	void SetTreasure(int cnt, unsigned index);
	bool IsTreasure(unsigned index);

	unsigned TotalTreasure() const;

	//探宝
	unsigned Treasure(int index);
	unsigned GetExtraEquip(int index);
	unsigned GetTreasureCost(int cnt = 1) const;

	void Reset(unsigned nVersion);
	void ResetOut(unsigned id);
	unsigned GetOut(unsigned index) const;

	void Save();
private:
	Json::Value m_json_newAct1;
	Json::Value m_json_newAct2;

	unsigned m_total_treasure_cnt; //总共寻宝次数
	unsigned m_treasure_cnt;       //当前寻宝次数
	unsigned m_cur_id;
};

////////////////////////////////////////////////////////
//信物强化
class TokenIntensifyUnit : public BaseCmdUnit
{
public:
	TokenIntensifyUnit(const UserWrap& user);

	//全区物品剩余个数列表
	int ListImpl(UserWrap& user, const BaseCmdParams& params, Json::Value& result);
	//兑换
	int ExchangeZoneImpl(UserWrap& user, const UnitIndexCmdParams& params, Json::Value& result);
	//
	int ExchangeCommonImpl(UserWrap& user, const UnitIndexCmdParams& params, Json::Value& result);

private:
	void Reset(unsigned nVersion);
	void CostPoint(UserWrap& user, unsigned point);
	ShDataTokenIntensify* GetTokenIntensifyShm();
	ShDataTokenIntensify* ShmPtr();

	const DataTokenIntensify& cfg_;
};

////////////////////////////////////////////////////////
//世间秘宝
class WorldTreasureExtractParams : public UnitIndexCmdParams
{
public:
	WorldTreasureExtractParams(const Json::Value& jsonData);
	int Type() const { return type_; }
private:
	int type_;
};

class WorldTreasureUnit : public BaseCmdUnit
{
public:
	WorldTreasureUnit(const UserWrap& user);

	//领取密匙
	int DrawImpl(UserWrap& user, const BaseCmdParams& params, Json::Value& result);
	//抽取物品
	int ExtractImpl(UserWrap& user, const WorldTreasureExtractParams& params, Json::Value& result);
private:
	void Reset(unsigned nVersion);
	void ResetLibs();
	bool IsFull();

	void SaveAll();

	Json::Value& ExtractedRecordLib(int type);

private:
	const ConfigWorldTreasure& cfg_;
	Json::Value m_jsonRecord;
};
////////////////////////////////////////////////////////
//武魂回馈
class SoulFeedbackDrawParams : public UnitIndexCmdParams
{
public:
	SoulFeedbackDrawParams(const Json::Value& jsonData);

	int EquipIndex() const { return eq_index_; }
private:
	int eq_index_;
};

class SoulFeedbackUnit : public BaseCmdUnit
{
public:
	SoulFeedbackUnit(const UserWrap& user);

	//领取物品
	int DrawImpl(UserWrap& user, const SoulFeedbackDrawParams& params, Json::Value& result);
private:
	void Reset(unsigned nVersion);
private:
	const ConfigSoulFeedback& cfg_;
};


////////////////////////////////////////////////////////
//觉醒回馈
class AwakenFeedbackUnit : public BaseCmdUnit
{
public:
	AwakenFeedbackUnit(const UserWrap& user);
	//领取物品
	int DrawImpl(UserWrap& user, const SoulFeedbackDrawParams& params, Json::Value& result);
private:
	void Reset(unsigned nVersion);
private:
	const ConfigAwakenFeedback& cfg_;
};

////////////////////////////////////////////////////////
//铸魂打折
class CastSoulUnit : public BaseCmdUnit
{
public:
	CastSoulUnit(const UserWrap& user);
	//领取物品
	int DrawImpl(UserWrap& user, const SoulFeedbackDrawParams& params, Json::Value& result);
private:
	void Reset(unsigned nVersion);
private:
	const ConfigCastSoulDiscount& cfg_;
};

////////////////////////////////////////////////////////
//宝石折扣
class GemDiscountUnit : public BaseCmdUnit
{
public:
	GemDiscountUnit(const UserWrap& user);
	//领取物品
	int DrawImpl(UserWrap& user, const UnitIndexCmdParams& params, Json::Value& result);
private:
	void Reset(unsigned nVersion);

private:
	const ConfigGemDiscount& cfg_;
};

////////////////////////////////////////////////////////
//金玉满堂  活动
class TreasureAroundUnit : public SecincActivityUnit
{
public:
	TreasureAroundUnit(const UserWrap& user);

	//领取物品
	int DrawImpl(UserWrap& user, const UnitUdCmdParams& params, Json::Value& result);
	//抽十次
	int DrawTenTimes(UserWrap& user, const UnitUdCmdParams& params, Json::Value& result);
private:
	void Reset();
private:
	const ConfigTreasuresAllAround& cfg_;
};

////////////////////////////////////////////////////////
//将灵培养
class SpiritFosterUnit : public BaseFeedbackActUnit
{
public:
	SpiritFosterUnit(const UserWrap& user);
private:
	//可以领取多少项
	virtual int GetDrawItems() const
	{
		return cfg_.size();
	}
	//对应拉取项的配置
	virtual const JsonFeedbackItem& GetFeedbackItem(int index) const
	{
		return cfg_.Item(index);
	}
	//操作码
	virtual const char* DrawOp() const
	{
		return "spirit_foster_draw_op";
	}
private:
	const ConfigSpiritFoster& cfg_;
};

////////////////////////////////////////////////////////
//的卢凝魂
class ChargeHorseUnit : public BaseFeedbackActUnit
{
public:
	ChargeHorseUnit(const UserWrap& user);
private:
	//可以领取多少项
	virtual int GetDrawItems() const
	{
		return cfg_.size();
	}
	//对应拉取项的配置
	virtual const JsonFeedbackItem& GetFeedbackItem(int index) const
	{
		return cfg_.Item(index);
	}
	//操作码
	virtual const char* DrawOp() const
	{
		return "charge_horse_draw_op";
	}
private:
	const ConfigChargeHorse& cfg_;
};


////////////////////////////////////////////////////////
//天坛祈福
class TemplePrayUnit : public BaseCmdUnit
{
	enum {
		FREE_COMMON_GET_CNT = 1,
		FREE_VIP_GET_CNT = 2
	};

	enum {
		VIP_GET_LEVEL = 4, //超过VIP等级4 则有FREE_VIP_GET_CNT免费机会
	};
public:
	class PrayParams : public UnitUdCmdParams
	{
	public:
		PrayParams(const Json::Value& data)
			: UnitUdCmdParams(data)
		{
			id_ = ValueAsUInt("id");
			buildid_ = ValueAsUInt("buildid");
		}

		unsigned Id() const { return id_; }
		unsigned BuildId() const { return buildid_; }
	private:
		unsigned id_;
		unsigned buildid_;
	};
public:
	TemplePrayUnit(const UserWrap& user);

	int Pray(UserWrap& user, const PrayParams& params, Json::Value &result);
};

////////////////////
//英雄训练
class HeroTrainUnit : public BaseCmdUnit
{
public:
	enum
	{
		MAX_INDEX_ITEM = 0x3,    //最大索引数
		MAX_QUEUE_ITEMS= 0x5,    //最大训练队列数
	};

	enum
	{
		END_TRAIN_BY_CASH = 0X0,   //钻石结束
		END_TRAIN_BY_COIN = 0X1,   //金币结束
	};

	HeroTrainUnit(unsigned uid);

	void StartTrain(UserWrap& userWrap, unsigned heroud, unsigned index, unsigned blv, Json::Value & result);

	void ImproveTrainExp(UserWrap& userWrap, unsigned equd, unsigned tindex, Json::Value & result);

	void EndTrain(UserWrap& userWrap, unsigned type, unsigned tindex, Json::Value & result);

private:
	void Save();

private:

	static const int COIN_INDEX[MAX_INDEX_ITEM];        //金币
	static const int HOUR_INDEX[MAX_INDEX_ITEM];		//时间
	static const int EQUIP_NUM_INDEX[MAX_INDEX_ITEM];   //兵法消耗数量
};

////////////////////
//小兵训练和研究
class SoldierUnit
{
public:
	enum
	{
		MAX_QUEUE_ITEMS= 0x5,    //最大训练队列数
	};

	enum
	{
		END_SOLDIER_BY_CASH = 0X0,   //钻石结束
		END_SOLDIER_BY_COIN,   //金币结束
	};

	enum
	{
		START_SOLDIER_BY_RESOURCE = 0X1,   //资源开始训练
		START_SOLDIER_BY_COIN,  //金币开始训练
	};

	SoldierUnit(unsigned uid);

	void StartTrain(UserWrap& userWrap, string sid, int count, unsigned stype, unsigned costtype, Json::Value &result);   //训练


	void EndTrain(UserWrap& userWrap, unsigned bindex, unsigned etype, Json::Value &result);

	void StartResearch(UserWrap& userWrap, string sid, unsigned stype, unsigned rlevel, unsigned costtype, Json::Value &result);   //研究

	void CancelResearch(UserWrap& userWrap, string sid, Json::Value &result);

	void EndResearch(UserWrap& userWrap, string sid, unsigned etype, Json::Value &result);

private:
	int GetResourceCost(unsigned resource);

	int GetSoldierTimeCost(unsigned lefttime);

	int GetTrainNeedSoul(unsigned char grade, int level);

	int GetResearchNeedSoul(unsigned char grade, int level);

	int AddSoldiers(Json::Value & soldier, int count, string sid);

private:
	unsigned 	m_nUid;
	Json::Value m_jsonData;

	CDataXML* m_pdataXML;
};

class SkillUnit : public BaseCmdUnit
{
public:
	enum
	{
		MAX_QUEUE_ITEMS= 0x5,    //最大训练队列数
		MAX_VIP_LEVEL = 0x0A,  //vip最大等级
	};

	enum
	{
		SKILL_OF_HEAVEN = 0x1,    //兵书技能
		SKILL_OF_DAO,    //遁甲技能
	};

	enum
	{
		END_TRAIN_BY_CASH = 0X0,   //钻石结束
		END_TRAIN_BY_COIN,   //金币结束
		END_TRAIN_BY_TIME, //时间结束
	};

	SkillUnit(unsigned uid);

	void UpgradeInnateSkill(UserWrap& userWrap, unsigned heroud, Json::Value &result);   //天生技

	void StartSkillTrain(UserWrap& userWrap, unsigned heroud, string skid, Json::Value m_data, unsigned sectime, unsigned costpro, Json::Value &result);    //混元技或普通技

	void EndSkillTrain(UserWrap& userWrap,  unsigned sindex, unsigned type, Json::Value &result);    //混元技或普通技

	void AddSqkillQueue(UserWrap& userWrap,  unsigned sindex,  unsigned rentime,unsigned paytype,unsigned amount, Json::Value &result); //增加技能队列

	void EndSqkillQueue(UserWrap& userWrap,  unsigned sindex, Json::Value &result); //结束技能队列

	void CommderSkilLearn(UserWrap& userWrap, unsigned heroud, unsigned equd,Json::Value &result);  //争霸技能

	void PotianSkilLearn(UserWrap& userWrap, unsigned heroud,string skid,Json::Value &m_data,Json::Value &result);  //破天技能

	void UpgradeHevenDaoSkill(UserWrap& userWrap, unsigned index, unsigned type, unsigned equd, Json::Value &result);  //兵书遁甲技能

	void UpgradeCatapultSkill(UserWrap& userWrap, unsigned index, unsigned equd, Json::Value &result);  //投石机技能

	static int CheakSkillVer(Json::Value &tskill);
private:
	double GetGradeMaxPoint(int point, int grade);

	void VerifyTrainQueue(Json::Value & skillq, unsigned sectime, int & queue_index);

	int GetSkillTimeCost(unsigned lefttime, unsigned viplevel);

private:
	CDataXML* m_pdataXML;

	static const int FREE_SPEED_TIME[MAX_VIP_LEVEL];        //vip可加速的时间范围，单位为分钟
};

//福禄金袋
class FortuneFairyBagUnit
{
public:
	enum
	{
		TYPE_OF_NORMAL = 0x1,  //普通领取
		TYPE_OF_ONEHALF,   //1.5倍领取
		TYPE_OF_TRIPLE,   //3倍领取
	};

	FortuneFairyBagUnit(unsigned uid);

	void CalcuteFortune(UserWrap& userWrap, Json::Value & result);  //计算福禄值

	void RecieveFairyBagReward(UserWrap& userWrap, unsigned type, Json::Value & result);
private:
	void Save();
private:
	unsigned 	m_nUid;
	Json::Value m_jsonData;
	static const int MAX_FORTUNE_VAL = 10000;
};

//每日充值
class DailyChargeCoinUnit
{
public:
	enum
	{
		max_index_value = 12,  //最多12个索引
		max_heaven_dao_index = 14, //兵书遁甲最大索引
	};

	DailyChargeCoinUnit(unsigned uid);

	DailyChargeCoinUnit(unsigned uid, string atype);

	//领取每日充值金币奖励
	int GetDailyChargeCoinReward(UserWrap& userWrap, unsigned index, Json::Value & result);

protected:
	//检查user_stat中的数据是否包含所需字段，如果没有，则初始化
	bool CheckUserstatComplete(Json::Value & user_stat);

	int ResetUserstat(Json::Value & user_stat);

	//判断活动是否在活动范围内
	bool IsActivityOpen();

	bool IsFeedback();

protected:
	unsigned 	m_nUid;
	Json::Value m_jsonData;
	string      m_activetype;
	unsigned 	m_activity_endts;
};

//充值回馈-同每日充值送金币类似
class ChargeFeedbackUnit : DailyChargeCoinUnit
{
public:
	ChargeFeedbackUnit(unsigned uid, string type);

	//领取充值回馈 -返回兵书或者遁甲奖励
	int GetChargeFeedbackReward(UserWrap& userWrap, unsigned index, Json::Value & result);
};

//欢庆元旦
class CelebrateNewYearUnit: DailyChargeCoinUnit
{
public:
	CelebrateNewYearUnit(unsigned uid, string type);

	int GetNewYearReward(UserWrap& userWrap, unsigned index, Json::Value & result);
};

//百宝箱
class TreasureBoxUnit: public BaseCmdUnit
{
public:
	enum
	{
		max_treasure_box_items = 8,  //百宝箱格子数
		multi_lottery_num	= 10, //一键抽奖的抽奖次数
		per_cash_times = 100, //钻石和次数的兑换比例
	};

	TreasureBoxUnit(unsigned uid);

	//百宝箱，应有检查版本号的接口
	int CheckVersion(UserWrap& userWrap, Json::Value & result);

	//刷新奖品
	int RefreshBox(UserWrap& userWrap, Json::Value & result);

	int LotteryOnce(UserWrap& userWrap, Json::Value & result);

	//多次抽奖
	int LotteryMulti(UserWrap& userWrap, Json::Value & result);

	static unsigned GetVersionCfg();

private:
	//todo 判断活动是否开启
	bool IsActivityOpen();

	//检查user_stat中的数据是否包含所需字段，如果没有，则初始化
	bool CheckUserstatComplete(Json::Value & user_stat);

	int Refresh(Json::Value & user_stat, Json::Value & result);

	int ResetTreasureBox(Json::Value & user_stat, unsigned version);

	//抽奖
	int Lottery(UserWrap& userWrap, string reason, Json::Value & result);

	//设置bbr的值
	int SetTreasureBBR(Json::Value & user_stat, GiftEquipItem & item, unsigned index);
};

//信物
class KeepsakeUnit : public BaseCmdUnit
{
public:
	enum
	{
		ret_code_notenough = -2,  //道具不足
		ret_code_maxnpc = -3,   //已到达最大NPC
		ret_code_max_exp = -4,
		keepsake_of_defective = 0, //残品
		keepsake_of_green,  //绿色品质
		keepsake_of_blue,  //蓝色品质
		keepsake_of_purple,  //紫色品质
		keepsake_of_orange,  //橙色品质
		keepsake_of_expprops,  //经验道具
		keepsake_of_convertprops, //转换道具
		max_npc_id = 5,  //最大npc

		max_slave_property_kind	= 14,  //副属性类型条数
		max_summon_times = 30,  //一天最大召唤次数
		per_convert_num	= 50,  //一次产出的转生石数目
		summon_pay_cash = 200, //召唤花费钻石数目 undone
		each_defctive_to_produce = 400,  //一个残品产生的道具A个数
		exp_props_value	= 300,  //经验道具提供的经验值
		produce_need_equip = 8801, //产出需要消耗的道具A
		convert_props_eqid = 8804, //转换石eqid
		max_nextrate_limit = 10000,  //下一级的最大概率
	};

	KeepsakeUnit(unsigned uid);

	//召唤
	int SummonNPC(UserWrap& userWrap, Json::Value & result);

	//一键产出
	int OneKeyProduce(UserWrap& userWrap, unsigned equd, unsigned times, Json::Value & result);
	//一键满级
	int OneKeyFullLevel(unsigned ud_hero_post, unsigned ud_keepsake, Json::Value & result);
	//单次产出
	int ProduceKeepsake(UserWrap& userWrap, unsigned equd, Json::Value & result);

	//信物产出,消耗道具，且有一定概率返回1级.产出等级，是否花钻.这些信息记录在哪里比较合适？
	int ProduceKeepsakeInside(UserWrap& userWrap, unsigned equd, string reason, Json::Value & result);

	//一键卖出
	int OnekeySoldDefective(unsigned equd, Json::Value & result);

	//信物吞噬,只能吞噬小于等于该品质的信物，或者可以吞噬经验石
	int FeedKeepsake(UserWrap& userWrap, unsigned equd, unsigned convertud, Json::Value & data, Json::Value & result);

	//解锁副属性
	static int UnlockSlave(Json::Value & keepsake);
private:
	//条件验证
	int VerifyCondition(unsigned uid, Json::Value & self, Json::Value & others);

	//信物增加经验
	int AddExp(Json::Value & keepsake, int addexp, unsigned * pexp, int length);

	//解锁具体的副属性
	static int UnlockSlaveProperty(Json::Value & keepsake, int target);

private:
	int m_onekey_times;
};

//装备强化活动
class EquipStrengthenUnit
{
public:
	enum
	{
		max_status_length = 4,  //领取状态数组元素个数
	};

	struct RewardInfo
	{
		unsigned quota;
		unsigned luck_stone_id;
		unsigned luck_stone_num;
		unsigned strongthen_stone_id;
		unsigned strongthen_stone_num;

		RewardInfo():
			quota(0),
			luck_stone_id(0),
			luck_stone_num(0),
			strongthen_stone_id(0),
			strongthen_stone_num(0)
		{

		}
	};

	EquipStrengthenUnit(unsigned uid);

	//领取奖励
	int GetChargeReward(UserWrap& userWrap, unsigned index, Json::Value & result);

	//检查活动版本号
	int CheckVersion(Json::Value & result);
private:
	//检查活动是否开启
	int CheckActivityOpen();

	//重置活动数据
	int ResetActivity(unsigned version);

	//获取索引相关的条件和奖励信息
	int GetRewardInfo(unsigned index, RewardInfo & rewardinfo);

	static unsigned GetVersionCfg(const string& szVersion);

	void Save();

private:
	unsigned 	m_nUid;
	Json::Value m_jsonData;
};

//合区活动
class HeQuActivityUnit : public BaseCmdUnit
{
public:
	enum
	{
		max_charge_index = 10, //充值奖励最大索引
	};

	HeQuActivityUnit(unsigned uid);

	//累积充值
	int GetChargeReward(UserWrap& userWrap, unsigned index, Json::Value & result);

	//vip奖励
	int GetVIPCelebrate(UserWrap& userWrap, unsigned vindex, unsigned sindex, Json::Value & result);

	//合区补偿（现改为等级补偿）
	int GetCombineZoneRecompense(UserWrap& userWrap, unsigned index, Json::Value & result);

	//合区补助
	int GetCombineZoneBuZhu(UserWrap& userWrap, Json::Value & result);
protected:
	//检查user_stat中的数据是否包含所需字段，如果没有，则初始化
	bool CheckUserstatComplete(Json::Value & user_stat);

	//判断活动是否在活动范围内
	bool IsActivityOpen();
};

//新型兵书
class AncientScrollUnit : public BaseCmdUnit
{
public:
	enum
	{
		max_level_distance = 10,  //最大等级差
	};

	class AncientParam : public UnitUdCmdParams
	{
	public:
		AncientParam(const Json::Value& data)
			: UnitUdCmdParams(data)
		{
			id = ValueAsUInt("id");

			//判断类型是否正常
			if (id < 1 || id > ANCIENT_SCROLL_ITEMS)
			{
				throw std::runtime_error("id_param_error");
			}

			int ud = Ud();

			if (ud <= 0)
			{
				throw std::runtime_error("ud_param_error");
			}
		}

		unsigned Id() const { return id; }
	private:
		unsigned id;
	};

	AncientScrollUnit(const UserWrap& user);

	//注资，只能一次一次注资
	int InjectScroll(UserWrap& userWrap, const AncientParam & param, Json::Value & result);

private:
	//查找最低和最高等级
	int GetMinLevel();

	int CheckScrollInit();
};

//碎片合成
class CompoundShredUnit : public BaseCmdUnit
{
public:
	CompoundShredUnit(const UserWrap& user);

	//碎片合成
	int ShredCompound(UserWrap& userWrap, const UnitUdCmdParams & param, Json::Value & result);
};

//古卷专项活动
class ScrollActivityUnit : public BaseActivityUnit
{
public:
	enum
	{
		begin_of_activity = 1, //活动的起始天数。从1始
		complete_type_props = 1, //使用道具完成
		complete_type_cash = 2,  //使用钻石完成
		max_material_type = 3, //材料类型最大值
		max_activity_days = 3,  //活动天数
	};

	ScrollActivityUnit(unsigned uid);

	//材料的获得
	int GainMaterial(unsigned type, unsigned count);

	//加载活动信息
	int LoadScrollActivity(Json::Value & result);

	//完成事件
	int CompleteAffair(unsigned type, Json::Value & result);

	//领取活跃值奖励
	int GetActiveReward(unsigned index, Json::Value & result);

private:
	//距离活动开始的时间天数。包含活动开始当天
	int GetDistanceDays();

	//检查版本号
	int CheckVersion();

	int Reset();
};

//天帝宝库活动
class KingTreasureActivityUnit: public BaseActivityUnit
{
public:
	enum
	{
		king_token_eqid	= 2031,  //天帝宝令
	};

	KingTreasureActivityUnit(unsigned uid);

	//开箱子
	int OpenTreasureBox(unsigned equd, Json::Value & result);

	//领取奖励
	int ReceiveReward(Json::Value & result);

	//回收奖励
	int RecycleReward(Json::Value & result);

private:
	//检查版本号
	int CheckVersion();

	int Reset();
};

//古卷回馈
class ScrollFeedbackActivityUnit : public BaseActivityUnit
{
public:
	enum
	{
		item_max_index	= 14,  //奖励项目最大个数
	};

	ScrollFeedbackActivityUnit(unsigned uid);

	//领取回馈
	int ReceiveFeedback(unsigned index, UserWrap& userWrap, Json::Value & result);

private:
	int ResetAct();
};

//七日觉醒活动
class SevenDaysAwakenActivityUnit : public BaseActivityUnit
{
public:
	enum
	{
		type_of_daily	= 0,  //每日奖励类型
		type_of_seven	= 1,  //七日奖励类型
		special_command_days = 7,  //特殊奖励要求的充值天数
		daily__charge_cash	= 300,  //每日充值的钻石要求数
		daily_gift_eqid	= 855,  //礼包的eqid
	};

	SevenDaysAwakenActivityUnit(unsigned uid);

	//领取回馈
	int ReceiveGift(unsigned type, UserWrap& userWrap, Json::Value & result);

	//发放七日奖励
	int ProvideSevenDaysGift(Json::Value & user_flag, Json::Value & result);

	int ProvideDailyGift(Json::Value & user_flag, Json::Value & result);

private:
	int Reset();
};

//令牌提升活动
class TokenUpgradeActivityUnit : public BaseActivityUnit
{
public:
	enum
	{
		item_max_index	= 9,  //奖励项目最大个数
	};

	TokenUpgradeActivityUnit(const UserWrap& user);

	//领取充值积分奖励
	int ReceivePointGift(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result);

	//积分抽奖
	int PointLottery(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result);

private:
	//检查版本号
	int CheckVersion();

	int Reset();
};

//打造套装活动
class BuildSuitActivityUnit : public BaseActivityUnit
{
public:
	enum
	{
		item_max_index	= 5,  //奖励项目最大个数
	};

	BuildSuitActivityUnit(const UserWrap& user);

	//领取充值积分奖励
	int ReceiveChargeGift(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result);

private:
	//检查版本号
	int CheckVersion();

	int Reset();
};

//祝福积分活动
class BlessPointActivityUnit : public BaseActivityUnit
{
public:
	enum
	{
		item_max_index	= 5,  //兑换项目最大个数
	};

	class BlessParam : public UnitUdCmdParams
	{
	public:
		BlessParam(const Json::Value& data)
			: UnitUdCmdParams(data)
		{
			id = ValueAsUInt("id");

			//判断类型是否正常
			if (id < 1 || id > item_max_index)
			{
				throw std::runtime_error("id_param_error");
			}

			int ud = Ud();

			if (ud <= 0)
			{
				throw std::runtime_error("ud_param_error");
			}
		};

		unsigned Id() const { return id; }
	private:
		unsigned id;
	};

	BlessPointActivityUnit(const UserWrap& user);

	//兑换积分
	int BlessExchange(UserWrap& userWrap, const BlessParam & param, Json::Value & result);
private:
	virtual int ResetAct();

	//检查英雄身上的装备祝福等级以及数量是否满足要求
	bool CheckHeroEquips(unsigned heroud, unsigned cond_num, unsigned cond_level);
};

//双倍福利活动
class DoubleWelfareActivityUnit : public BaseActivityUnit
{
public:
	enum
	{
		item_max_index	= 2,  //兑换项目最大个数
	};

	DoubleWelfareActivityUnit(const UserWrap& user);

	//额外奖励领取
	int GetExtraReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result);

	//领取充值奖励
	int GetChareReward(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result);

private:
	virtual int ResetAct();
};

//灵珠进阶
class PearlAdvanceActivityUnit : public BaseActivityUnit
{
public:
	enum
	{
		item_max_index	= 7,  //兑换项目最大个数
	};

	PearlAdvanceActivityUnit(const UserWrap& user);

	//兑换灵珠
	int ExchangePearl(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result);

private:
	bool CheckEquipCondition(const ConfigActivity::PearlAdvance & pearlcfg, int need);

	virtual int ResetAct();
};

//绝学转盘
class UniqueDialActivityUnit : public BaseActivityUnit
{
public:
	UniqueDialActivityUnit(const UserWrap& user);

	//抽奖
	int BeginLottery(UserWrap& userWrap, BaseCmdParams & param, Json::Value & result);

private:
	virtual int ResetAct();
};

//精元礼包活动
class SpiritVitalityActivityUnit : public BaseActivityUnit
{
public:
	enum
	{
		item_max_index	= 3,  //奖励项目最大个数
	};

	SpiritVitalityActivityUnit(const UserWrap& user);

	//领取充值奖励
	int ReceiveChargeGift(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result);

private:
	virtual int ResetAct();
};

//熔炉熔炉
class ForgeSmeltActivityUnit : public BaseActivityUnit
{
public:
	ForgeSmeltActivityUnit(const UserWrap& user);

	//熔炉熔炼
	int ForgeSmelt(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result);

	//熔炉上帝aN购买
	int BuyGoods(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result);

private:
	//检查跨天
	int CheckDifferDay();

	virtual int ResetAct();
};

//紫将转盘
class HeroesDialActivityUnit : public BaseActivityUnit
{
public:
	enum
	{
		turn_type_once	= 1, //一次转动
		turn_type_ten	= 2,  //十次转动
	};

	HeroesDialActivityUnit(const UserWrap& user);

	//转动英雄转盘
	int TurnHeroTable(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result);
private:
	int StartTurn(UserWrap& userWrap, const ConfigActivity::HeroDial & herodialcfg, Json::Value &result);

	virtual int ResetAct();
};

//三国争霸
class KingdomWarActivityUnit : public BaseActivityUnit
{
public:
	KingdomWarActivityUnit(const UserWrap& user);

	//领取充值奖励
	int GetChargeReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result);

private:
	int CheckItemSize();

	virtual int ResetAct();
};

//保护旗帜升级
class ProtectiveFlagUnit : public BaseCmdUnit
{
public:
	enum
	{
		type_upgrade_once = 1,   //一次打造
		type_upgrade_onekey = 2,   //一键升级
	};

	ProtectiveFlagUnit(const UserWrap& user);

	//升级
	int Upgrade(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result);

private:
	int GetLevelByExp(unsigned * pexp, int size, int exp);
};

//1钻福利
class OneDiamondWelfareActivityUnit : public BaseActivityUnit
{
public:
	enum
	{
		first_buy_price = 1,  //首次购买价格
		max_buy_times = 2,  //最大购买次数
		diamond_kinds_item	= 5,  //钻石档
		reward_item	= 6,  //奖励档
	};

	OneDiamondWelfareActivityUnit(const UserWrap& user);

	//购买物品
	int BuyGoods(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result);
private:
	virtual int ResetAct();
	int sid;
};

//七夕回馈
class QiXiFeedbackActivityUnit : public BaseActivityUnit
{
public:
	QiXiFeedbackActivityUnit(const UserWrap& user);

	//领取奖励
	int GetFeedback(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result);
private:
	virtual int ResetAct();
	int sid;
};

//顺序充值
class FortunePacksActivityUnit : public BaseActivityUnit
{
public:
	enum
	{
		item_max_index	= 5,  //商品个数
		charge_condition = 100,  //充值条件
	};

	FortunePacksActivityUnit(const UserWrap& user);

	//打开活动窗口
	int OpenWindow(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result);

	//购买物品
	int Purchase(UserWrap& userWrap, const UnitIdCmdParams & param, Json::Value & result);

	int GetGiftedUsers(CDataFortunePacks* pdata, Json::Value & users);
private:
	virtual int ResetAct();
	int sid;
	static const int extra_num_relation[MAX_EXTRA_ITEMS];  //额外奖励与参与人数的对应关系
};

//七天好礼
class SevenDayPacksActivityUnit : public BaseActivityUnit
{
public:
	enum
	{
		item_max_index	= 7,  //奖励项数
		charge_condition = 100,  //充值条件
	};

	SevenDayPacksActivityUnit(const UserWrap& user);

	//领取奖励
	int GetReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result);

private:
	virtual int ResetAct();
	int sid;
};

//充值额度+领取奖励
class ChargeQuotaActivityBase : public BaseActivityUnit
{
public:
	ChargeQuotaActivityBase(unsigned uid, const std::string& actname, int sid_, int itemsize);

protected:
	virtual int ResetAct();

	virtual int CheckItemSize();

	int Reward(UserWrap& userWrap, unsigned index, const ConfigActivity::DiamondReward & itemcfg, string reason, Json::Value & result);

protected:
	int sid;
	int itemsize;
};

//冰凰来袭
class IcePhoenixActivityUnix : public ChargeQuotaActivityBase
{
public:
	enum
	{
		item_max_index	= 4,  //奖励项数
	};

	IcePhoenixActivityUnix(const UserWrap& user);

	//注意，函数名称不要和基类中的相同
	int GetChargeReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result);
};

//秋日回馈
class AutumnFeedbackActivityUnix : public ChargeQuotaActivityBase
{
public:
	enum
	{
		item_max_index	= 3,  //奖励项数
	};

	AutumnFeedbackActivityUnix(const UserWrap& user);

	//注意，函数名称不要和基类中的相同
	int GetChargeReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result);
};

//保护旗帜
class ProtectFlagActivityUnix : public ChargeQuotaActivityBase
{
public:
	enum
	{
		item_max_index	= 4,  //奖励项数
	};

	ProtectFlagActivityUnix(const UserWrap& user);

	//注意，函数名称不要和基类中的相同
	int GetChargeReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result);
};

//年末好礼
class YearEndGiftActivityUnix : public ChargeQuotaActivityBase
{
public:
	enum
	{
		item_max_index	= 4,  //奖励项数
	};

	YearEndGiftActivityUnix(const UserWrap& user);

	//注意，函数名称不要和基类中的相同
	int GetChargeReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result);

protected:
	int CheckItemSize();
};

//转盘狂惠
class RotaryTableActivityUnix : public BaseActivityUnit
{
public:
	enum
	{
		check_charge_item_size      = 1,
	};

	RotaryTableActivityUnix(const UserWrap& user);

	//获取充值奖励
	int GetChargeReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result);

	//获取随机奖励
	int GetRandomReward(UserWrap& userWrap, const UnitIdCmdParams & param, Json::Value & result);
protected:
	int ResetAct();
	int CheckItemSize();
private:
	int m_chargeitemsize;
};

//转盘回馈
class RotaryTableFeedBackUnix : public BaseActivityUnit
{
	public:
		RotaryTableFeedBackUnix(const UserWrap &user);
	
		//累计充值进度条奖励
		int GetChargeReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result);

		//随机抽奖奖励
		int GetRandomReward(UserWrap& userWrap, const InitIdCmdParams & param, Json::Value & result);

		//累计充值钻石
		int GetAccChargeReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result);
	protected:
		int ResetAct();
		int CheckItemSize();
	private:
		int m_chargeitemsize;  //抽奖
		int m_jinduSize;	   //进度条
		int m_countSize;	   //机会
		int m_singleSize;	   //累计充值钻石
};

class GiveHelpChargeUnit : public BaseActivityUnit {
public:
	GiveHelpChargeUnit(const UserWrap &user);
	int GetTotalChargeReward(UserWrap &userWrap, const UnitIndexCmdParams &param, Json::Value &result);
	int GetExtraReward(UserWrap &userWrap, const UnitIndexCmdParams &param, Json::Value &result);
	int SetHelpCount(unsigned count);
	int ResetAct();
private:
	int m_chargeItemSize;
	int m_extraItemSize;
	DataXMLGiveHelpItem m_config;
};

//小兵宝物
class BatmanTreasureActivityUnix : public BaseActivityUnit
{
public:
	BatmanTreasureActivityUnix(const UserWrap& user);

	//获取充值奖励
	int GetChargeReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result);

	//获取随机奖励
	int Draw(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result);
protected:
	int ResetAct();
	int CheckItemSize();
	int TurnLuckTable(vector<unsigned> & prates, int len, int & target);
private:
	int m_chargeitemsize;
};

//暑假精选
class SummerRewardActivityUnix : public BaseActivityUnit
{
	enum{
		check_acc_item = 1,//校验累积充值档位
		check_daily_item = 2,//校验每日充值档位
	};
public:
	SummerRewardActivityUnix(const UserWrap& user);

	//获取累积充值奖励
	int GetSummerAccReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result);

	//获取每日充值奖励
	int GetSummerDailyReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result);
protected:
	int ResetAct();
	int CheckItemSize(int flag);
	unsigned GetCurDateStartTs();
private:
	int m_acc_chargeitemsize;
	int m_daily_chargeitemsize;
};

//暑假回馈
class SummerHolidaysActivityUnix : public BaseActivityUnit
{
	enum{
		check_acc_item = 1,//校验累积充值档位
		check_exhange_item = 2,//校验兑换档位
	};
public:
	SummerHolidaysActivityUnix(const UserWrap& user);

	//获取累积充值奖励
	int GetChargeReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result);

	//物品兑换
	int ExchangeItem(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result);
protected:
	int ResetAct();
	int CheckItemSize(int flag);
private:
	int m_acc_chargeitemsize;
	int m_exchangeitemsize;
};


//兑换自选
class FreeExchangeUnit : public SecincActivityUnit
{
public:
	FreeExchangeUnit(const UserWrap& user);
	int DrawImpl(UserWrap& user, const BaseCmdParams& params, Json::Value& result);
private:
	void Reset();
};

//充值自选活动
class PayOptionalActivityUnix : public SecincActivityUnit
{
public:
	PayOptionalActivityUnix(const UserWrap& user);
	//领取每日自选奖励
	int GetEveryDayChargeReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result);
	int GetChargeByActivityToday(UserWrap& userWrap,unsigned end_ts);
protected:
	void Reset();
private:
	int itemsize_;//充值奖励项数
};


class ChinaDayActivityUnix : public SecincActivityUnit
{
	enum
		{
			reset_online_reward_tag = 1,            //重置"每天在线30分钟领取"标记
			reset_everyday_reward_tag,            //充值每日充值奖励领取
		};
public:

	ChinaDayActivityUnix(const UserWrap& user);

	//获取每日充值奖励
	int GetEveryDayReward(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result);
	//获取在线奖励
	int GetOnlineReward(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result);
	//获取副本奖励
	int GetInstanceZonesReward(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result);
	//扣除挑战次数
	int DeDuctChallengeNum(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result);

	int GetChargeByActivityToday(UserWrap& userWrap,unsigned end_ts);
protected:
	int ResetAct(int reset_type);
	void Reset();
};

class GuoQingKuangHuan : public SecincActivityUnit
{

public:
	GuoQingKuangHuan(const UserWrap& user);

	//获取国庆所有奖励
	int GetChargeReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result);

protected:
	void Reset();

private:
	int itemsize_;//充值奖励项数
};


//元旦庆典
class NewYearActivityUnix : public BaseActivityUnit
{
public:
	enum
	{
		combine_shop_per_item_cnt_max = 8 //组合商店每栏所含有的物品最大数
	};
	enum
	{
		combine_shop_select_item_cnt_max = 3  //组合商店最大可挑选的物品数
	};
	enum
	{
		reset_combine_shop_get_tag = 1, //重置"组合商店购买记录"标记
		reset_day_reward_tag,            //重置"每天在线30分钟领取"标记
		reset_charge_reward_tag         //重置"充值领奖励记录"标记
	};

	NewYearActivityUnix(const UserWrap& user);

	//注意，函数名称不要和基类中的相同
	int GetChargeReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result);

	int BuyItemFromCombinedShop(UserWrap& user, const BaseCmdParams& params,  Json::Value& result);

	int GetOnlineReward(UserWrap& user, const BaseCmdParams& params,  Json::Value& result);
protected:
	int ResetAct(int reset_type);
	int ResetAct();
private:
	int itemsize_;//充值奖励项数
	int combinebuyitem_;//组合商店档位
};

class OpenServerActivityUnix : public BaseActivityUnit
{
public:
	enum
	{
		check_bit_min = 1,
		check_bit_max = 32
	};

	enum
	{
		achievement_item_min = 1,
		achievement_item_max = 7
	};
	enum
	{
		jiangling_level_achievement  = 1,
		jiangling_growth_achievement = 2,
		wuhun_achievement            = 3,
		juexue_achievement           = 4,
		shengxing_achievement        = 5,
		bingshu_achievement          = 6,
		dunjia_achievement           = 7
	};

	OpenServerActivityUnix(const UserWrap& user);

	int GetAchievementGift(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result);
	int HandleAchievementGift(const RewardConfig::RewardItemCfg& itemCfg,int index_parent,int index_child,Json::Value & result);

	int GetDiscountShopGift(UserWrap& user, const UnitIndexCmdParams& params,  Json::Value& result);
	//处理折扣商店物品的购买
	int HandleDiscountShopBuy(UserWrap& user,const ConfigActivity::KaifuDiscountShop & itemcfg,string reason,int index,Json::Value& result);


	//属性判定
	int judgeLevel(const ConfigActivity::KaifuAchievement& itemcfg,UserWrap& user, int index); //将灵等级判定
	int judgeGrowth(const ConfigActivity::KaifuAchievement& itemcfg,UserWrap& user, int index); //将灵成长值判定
	int judgeEternal(const ConfigActivity::KaifuAchievement& itemcfg,UserWrap& user, int index); //武魂属性判定
	int judgeJueXue(const ConfigActivity::KaifuAchievement& itemcfg,UserWrap& user, int index); //绝学属性判定
	int judgeShengXing(const ConfigActivity::KaifuAchievement& itemcfg,UserWrap& user, int index); //升星属性判定
	int judgeBingShu(const ConfigActivity::KaifuAchievement& itemcfg,UserWrap& user, int index); //兵书属性判定
	int judgeDunJia(const ConfigActivity::KaifuAchievement& itemcfg,UserWrap& user, int index); //遁甲属性判定
protected:
	int ResetAct();
	void ResetDiscountAct();
};

//保护女神
class ProtectGoddessUnix : public BaseCmdUnit
{
public:
	ProtectGoddessUnix(const UserWrap& user);

	//领取积分奖励
	int GetPointReward(UserWrap& userWrap, const UnitIdCmdParams & param, Json::Value & result);
};

//密钥豪礼
class KeyLuxuryGiftActivityUnit : public BaseActivityUnit
{
public:
	KeyLuxuryGiftActivityUnit(const UserWrap& user);

	//领取奖励
	int GetReward(UserWrap& userWrap, const UnitIndexCmdParams & param, Json::Value & result);

private:
	int CheckItemSize();

	virtual int ResetAct();
	int sid;
};

//兵魂注入
class SoldierSpiritUnit : public BaseCmdUnit
{
public:
	enum
	{
		soldier_spirit_maxlevel = 10, //兵魂最大等级
		soldier_spirit_eqid	= 4093,  //兵魂道具id
	};

	SoldierSpiritUnit(const UserWrap& user);

	//注入
	int Inject(UserWrap& userWrap, const UnitUdCmdParams & param, Json::Value & result);
};

//畅享小礼
class EnjoySmallGiftActivityUnit : public BaseActivityUnit
{
public:
	enum
	{
		reward_type_charge = 1,  //充值奖励
		reward_type_consume,  //消费奖励
	};

	class GiftParam : public BaseCmdParams
	{
	public:
		GiftParam(const Json::Value& jsonData): BaseCmdParams(jsonData)
		{
			index = ValueAsUInt("index");
			type = ValueAsUInt("type");
		}

		unsigned Type() const {return type;}

		unsigned Index() const {return index;}
	private:
		unsigned int type;
		unsigned int index;
	};

	EnjoySmallGiftActivityUnit(const UserWrap& user);

	//领取奖励
	int GetReward(UserWrap& userWrap, const GiftParam & param, Json::Value & result);

private:
	int CheckItemSize();

	virtual int ResetAct();
};

//幸运好礼
class LuckyGiftActivityUnit : public BaseActivityUnit
{
public:
	enum
	{
		turn_type_key = 1,  //密钥转动
		turn_type_point  //充值积分转动
	};

	LuckyGiftActivityUnit(const UserWrap& user);

	//转动转盘
	int TurnTable(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result);
private:
	int TurnImpl(const ConfigActivity::LuckyGift & luckygiftcfg, Json::Value & subresult);

	virtual int ResetAct();
};

//旧有功能移后台
class ConvertToBackendUnit : public BaseCmdUnit
{
public:
	enum
	{
		resource_build_farm = 2,  //农田
		resource_build_quarry = 37, //采石场
		resource_build_iron_field = 38,  // 铁矿场
		resource_build_wood_field = 39, // 木材场
		resource_gain_interval = 600,  //10分钟收一次
		max_buy_times = 5,  //每日可购买次数
		time_energy_add = 10,  //自然恢复的能量增加
		invite_energy_add = 20,  //邀请好友增加的能量
		energy_add	= 100,  //购买时增加的能量
		energy_limit = 1000,  //自然恢复时的能量上限
		energy_interval	= 1800,  //自然恢复的时间间隔
		equip_energy_bag_1 = 5010,  //能量包1
		equip_energy_bag_2 = 5011,  //能量包2
	};

	ConvertToBackendUnit(const UserWrap& user);

	//能量回复
	int RecoverEnergyByTime(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result);

	//好友邀请加能力
	int RecoveryByInviteFriends(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result);

	//能量购买
	int BuyEnergy(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result);

	//打开能量包
	int OpenEnergyBag(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result);

	//资源收获
	int GainResource(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result);

private:
	bool IsResourceBuild(int type);

	int GetResourceTye(int type);
};

//打开特殊礼包
class OpenSpecialPackUnit : public BaseCmdUnit
{
public:
	OpenSpecialPackUnit(const UserWrap& user);

	int Choose(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result);

private:

};

//绝学突破
class JueXueBreakUnit: public BaseCmdUnit
{
public:
	enum
	{
		juexue_character_orange = 3,  //橙色绝学
		juexue_character_red = 4,  //红色绝学
		juexue_character_max = 5,  //品质数量
		break_through_level = 10,  //突破要求等级
		juexue_level_max = 12, //最高等级
		break_through_eqnum = 1000,  //突破所需道具数量
		break_through_eqid = 3018,  //突破要求道具
	};

	JueXueBreakUnit(const UserWrap& user);

	int BreakThrough(UserWrap& userWrap, const BaseCmdParams & param, Json::Value & result);

	static int GetJueXueLevel(unsigned int exp, int character);
};

/*
//黑金强化活动
class BlackEnhanceActivityUnit : public BaseActivityUnit
{
public:
	enum
	{
		item_max_index	= 4,  //兑换项目最大个数
	};

	class EnhanceParam : public UnitUdCmdParams
	{
	public:
		EnhanceParam(const Json::Value& data)
			: UnitUdCmdParams(data)
		{
			index = ValueAsUInt("index");

			//判断类型是否正常
			if (index < 1 || index > item_max_index)
			{
				throw std::runtime_error("index_param_error");
			}

			int ud = Ud();

			if (ud <= 0)
			{
				throw std::runtime_error("ud_param_error");
			}
		};

		unsigned Index() const { return index; }
	private:
		unsigned index;
	};

	BlackEnhanceActivityUnit(const UserWrap& user);

	//幸运石兑换
	int LuckyStoneExchange(UserWrap& userWrap, const EnhanceParam & param, Json::Value & result);
private:
	virtual int ResetAct();

	//检查英雄身上的装备强化等级以及数量是否满足要求
	bool CheckHeroEquips(unsigned heroud, unsigned cond_num, unsigned cond_level);
};
*/

////////////////////////////////////////////////////////
//星石置换  活动
class StarStoneChangeUnit : public SecincActivityUnit
{
public:
	StarStoneChangeUnit(const UserWrap& user);

	//领取物品
	int DrawImpl(UserWrap& user, const BaseCmdParams& params, Json::Value& result);
private:
	void Reset();
};
////////////////////////////////////////////////////////
//vicky又要做个充值活动
class VickyAccXUnit : public BaseFeedbackActUnit
{
public:
	VickyAccXUnit(const UserWrap& user);
private:
	//可以领取多少项
	virtual int GetDrawItems() const
	{
		return cfg_.size();
	}
	//对应拉取项的配置
	virtual const JsonFeedbackItem& GetFeedbackItem(int index) const
	{
		return cfg_.Item(index);
	}
	//操作码
	virtual const char* DrawOp() const
	{
		return "vicky_acc_x_draw_op";
	}
private:
	const ConfigVickyAccX& cfg_;
};
//vicky又要做个充值活动1
class VickyAccXUnit1 : public BaseFeedbackActUnit
{
public:
	VickyAccXUnit1(const UserWrap& user);
private:
	//可以领取多少项
	virtual int GetDrawItems() const
	{
		return cfg_.size();
	}
	//对应拉取项的配置
	virtual const JsonFeedbackItem& GetFeedbackItem(int index) const
	{
		return cfg_.Item(index);
	}
	//操作码
	virtual const char* DrawOp() const
	{
		return "vicky_acc_x1_draw_op";
	}
private:
	const ConfigVickyAccX1& cfg_;
};
//vicky又要做个充值活动2
class VickyAccXUnit2 : public BaseFeedbackActUnit
{
public:
	VickyAccXUnit2(const UserWrap& user);
private:
	//可以领取多少项
	virtual int GetDrawItems() const
	{
		return cfg_.size();
	}
	//对应拉取项的配置
	virtual const JsonFeedbackItem& GetFeedbackItem(int index) const
	{
		return cfg_.Item(index);
	}
	//操作码
	virtual const char* DrawOp() const
	{
		return "vicky_acc_x2_draw_op";
	}
private:
	const ConfigVickyAccX2& cfg_;
};
//vicky又要做个充值活动3
class VickyAccXUnit3 : public BaseFeedbackActUnit
{
public:
	VickyAccXUnit3(const UserWrap& user);
private:
	//可以领取多少项
	virtual int GetDrawItems() const
	{
		return cfg_.size();
	}
	//对应拉取项的配置
	virtual const JsonFeedbackItem& GetFeedbackItem(int index) const
	{
		return cfg_.Item(index);
	}
	//操作码
	virtual const char* DrawOp() const
	{
		return "vicky_acc_x3_draw_op";
	}
private:
	const ConfigVickyAccX3& cfg_;
};
//vicky又要做个充值活动4
class VickyAccXUnit4 : public BaseFeedbackActUnit
{
public:
	VickyAccXUnit4(const UserWrap& user);
private:
	//可以领取多少项
	virtual int GetDrawItems() const
	{
		return cfg_.size();
	}
	//对应拉取项的配置
	virtual const JsonFeedbackItem& GetFeedbackItem(int index) const
	{
		return cfg_.Item(index);
	}
	//操作码
	virtual const char* DrawOp() const
	{
		return "vicky_acc_x4_draw_op";
	}
private:
	const ConfigVickyAccX4& cfg_;
};
//vicky又要做个充值活动5
class VickyAccXUnit5 : public BaseFeedbackActUnit
{
public:
	VickyAccXUnit5(const UserWrap& user);
private:
	//可以领取多少项
	virtual int GetDrawItems() const
	{
		return cfg_.size();
	}
	//对应拉取项的配置
	virtual const JsonFeedbackItem& GetFeedbackItem(int index) const
	{
		return cfg_.Item(index);
	}
	//操作码
	virtual const char* DrawOp() const
	{
		return "vicky_acc_x5_draw_op";
	}
private:
	const ConfigVickyAccX5& cfg_;
};
//机甲黄忠
class huangzhongUnit : public BaseFeedbackActUnit
{
public:
	huangzhongUnit(const UserWrap& user);
private:
	//可以领取多少项
	virtual int GetDrawItems() const
	{
		return cfg_.size();
	}
	//对应拉取项的配置
	virtual const JsonFeedbackItem& GetFeedbackItem(int index) const
	{
		return cfg_.Item(index);
	}
	//操作码
	virtual const char* DrawOp() const
	{
		return "huangzhongUnit_draw_op";
	}
private:
	const Confighuangzhong& cfg_;
};
//vicky的开服活动
class VickyNewOpenUnit : public BaseFeedbackActUnit
{
public:
	VickyNewOpenUnit(const UserWrap& user);
private:
	//可以领取多少项
	virtual int GetDrawItems() const
	{
		return cfg_.size();
	}
	//对应拉取项的配置
	virtual const JsonFeedbackItem& GetFeedbackItem(int index) const
	{
		return cfg_.Item(index);
	}
	//操作码
	virtual const char* DrawOp() const
	{
		return "VickyNewOpenUnit_draw_op";
	}
private:
	const ConfigVickyNewOpen& cfg_;
};

class ChongZhiZiXuan : public SecincActivityUnit
{
public:
	ChongZhiZiXuan(const UserWrap& user);
	int Get(UserWrap& user, Json::Value& result);
	int DrawImpl(UserWrap& user, const BaseCmdParams& params, Json::Value& result);
	void Reset();
};

/********************************************************************/
/*  活动太多  先是抽象成模板  最后只能搞宏       */
#define CHARGE_DRAW_ACT(CONFIG_NAME, CONFIG_ALL, CONFIG_MEIRI) \
		class CONFIG_NAME##_Unit : public BaseFeedbackActUnit \
		{ \
		public: \
			CONFIG_NAME##_Unit(const UserWrap& user) \
			: BaseFeedbackActUnit(user.Id(), CONFIG_NAME, NAT_##CONFIG_NAME, CONFIG_ALL, CONFIG_MEIRI) \
			, cfg_(DataXmlPtr()->Get_##CONFIG_NAME()) {Init();} \
		private: \
			virtual int GetDrawItems() const {return cfg_.size();} \
			virtual const JsonFeedbackItem& GetFeedbackItem(int index) const {return cfg_.Item(index);} \
			virtual const char* DrawOp() const {return CONFIG_NAME"_draw_op";} \
		private: \
			const CONFIG_NAME##_CONFIG& cfg_; \
		};
/********************************************************************/
/********************************************************************/
/*  活动太多  先是抽象成模板  最后只能搞宏    活动时间名单独区分的宏   */
#define CHARGE_DRAW_ACT_TIME_NAME_ACT(CONFIG_NAME, ACT_TIME_NAME,CONFIG_ALL, CONFIG_MEIRI) \
		class CONFIG_NAME##_Unit : public BaseFeedbackActUnit \
		{ \
		public: \
			CONFIG_NAME##_Unit(const UserWrap& user) \
			: BaseFeedbackActUnit(user.Id(), ACT_TIME_NAME, NAT_##CONFIG_NAME, CONFIG_ALL, CONFIG_MEIRI) \
			, cfg_(DataXmlPtr()->Get_##CONFIG_NAME()) {Init();} \
		private: \
			virtual int GetDrawItems() const {return cfg_.size();} \
			virtual const JsonFeedbackItem& GetFeedbackItem(int index) const {return cfg_.Item(index);} \
			virtual const char* DrawOp() const {return CONFIG_NAME"_draw_op";} \
		private: \
			const CONFIG_NAME##_CONFIG& cfg_; \
		};
/********************************************************************/
//autolable6
CHARGE_DRAW_ACT(CONFIG_yongguansanjun, true, false)
CHARGE_DRAW_ACT_TIME_NAME_ACT(CONFIG_wuyiqingdian_leiji, ACTIVITY_TIME_wuyiqingdian, true, false)
CHARGE_DRAW_ACT(CONFIG_yvre618_2, true, false)
CHARGE_DRAW_ACT(CONFIG_yvre618_1, true, false)
CHARGE_DRAW_ACT(CONFIG_toushichejineng, false, false)
CHARGE_DRAW_ACT(CONFIG_chongbang_3, true, true)
CHARGE_DRAW_ACT(CONFIG_zhuanshucanjuan, false, false)
CHARGE_DRAW_ACT(CONFIG_baihuahuikui_3, true, false)
CHARGE_DRAW_ACT(CONFIG_baihuahuikui_2, true, false)
CHARGE_DRAW_ACT(CONFIG_baihuahuikui_1, true, false)
CHARGE_DRAW_ACT_TIME_NAME_ACT(CONFIG_guyv_leiji, ACTIVITY_TIME_GUYU, true, false)
CHARGE_DRAW_ACT_TIME_NAME_ACT(CONFIG_chengyuantisheng_2, CONFIG_chengyuantisheng, true, false)
CHARGE_DRAW_ACT_TIME_NAME_ACT(CONFIG_chengyuantisheng_1, CONFIG_chengyuantisheng, false, false)
CHARGE_DRAW_ACT(CONFIG_lueduotongqian_chongbang, true, true)
CHARGE_DRAW_ACT_TIME_NAME_ACT(CONFIG_anniversary_leiji, CONFIG_anniversary_chongzhi, true, false)
CHARGE_DRAW_ACT_TIME_NAME_ACT(CONFIG_anniversary_meiri, CONFIG_anniversary_chongzhi, true, true)
CHARGE_DRAW_ACT(CONFIG_zhengbashadi_chongbang, true, true)
CHARGE_DRAW_ACT(CONFIG_hanjiajingxuan, false, false)
CHARGE_DRAW_ACT(CONFIG_fuzhuhesui, true, false)
CHARGE_DRAW_ACT(CONFIG_zhuniandaji, true, false)
CHARGE_DRAW_ACT(CONFIG_vicky_qingrenjie, true, true)
CHARGE_DRAW_ACT(CONFIG_yuandan2018, false, false)
CHARGE_DRAW_ACT(CONFIG_yearend2018, false, false)
CHARGE_DRAW_ACT(CONFIG_winter2018, false, false)
CHARGE_DRAW_ACT(CONFIG_double11_2018, true, false)
CHARGE_DRAW_ACT(CONFIG_mid_aug_hao, true, false)
CHARGE_DRAW_ACT(CONFIG_mid_aug_reu, true, false)
CHARGE_DRAW_ACT(CONFIG_water_taotie, true, false)
CHARGE_DRAW_ACT(CONFIG_water_qilin, true, false)
CHARGE_DRAW_ACT(CONFIG_water_pheonix, true, false)
CHARGE_DRAW_ACT(CONFIG_vicky_nnom, false, false)
//vicky没想好名字的活动
CHARGE_DRAW_ACT(CONFIG_VICKY_NO_NAME, false, false)
CHARGE_DRAW_ACT(CONFIG_VICKY_BINGSHU, false, false)
CHARGE_DRAW_ACT(CONFIG_VICKY_QIANFU, false, false)
CHARGE_DRAW_ACT(CONFIG_VICKY_NNA, false, false)
///////////////////////////////////////////////////////////////

//任务好礼  活动
class TaskGiftUnit : public SecincActivityUnit
{
public:
	TaskGiftUnit(const UserWrap& user);

	//领取物品
	int DrawImpl(UserWrap& user, const UnitIndexCmdParams& params, Json::Value& result);
private:
	void Reset();
};

//美人献计  活动
class ActivityMeiRenUnit : public SecincActivityUnit
{
public:
	enum {
		e_ACT_MEIREN_POINT_ACTIVE = 0,
		e_ACT_MEIREN_POINT_CONSUME = 1,
		e_ACT_MEIREN_POINT_CHARGE = 2,
		e_ACT_MEIREN_POINT_MAX
	};
	enum {
		ACTIVE_POINT_MIN = 6,
		ACTIVE_POINT_MAX = 8
	};
	enum {
		COSUME_POINT_MIN = 19,
		COSUME_POINT_MAX = 21
	};
	enum {
		CHARGE_POINT_MIN = 95,
		CHARGE_POINT_MAX = 105
	};
	ActivityMeiRenUnit(const UserWrap& user);
	int DrawImpl(UserWrap& user, const BaseCmdParams& params, Json::Value& result);
	int AddPoint(UserWrap& user, const BaseCmdParams& params, Json::Value& result);
	int UsePoint(UserWrap& user, const BaseCmdParams& params, Json::Value& result);
	int Get(Json::Value& result);
	virtual void Init();
	virtual void Save();
	virtual void Reset() {
	}
protected:
	int UseActivePoint(unsigned count, Json::Value& result);
	int UseConsumePoint(unsigned count, Json::Value& result);
	int UseChargePoint(unsigned count, Json::Value& result);
private:
	const UserWrap& user_;
};

//充值投资
class ActivityInvestment: public SecincActivityUnit {
public:
	enum {
		e_ACT_INVESTMENT_ITEM_NUM = 4,
		e_ACT_INVESTMENT_PRICE = 100
	};
	ActivityInvestment(const UserWrap& user);
	virtual void Reset();
	int SelectCount(UserWrap& user, const BaseCmdParams& params, Json::Value& result);
	int SelectOption(UserWrap& user, const BaseCmdParams& params, Json::Value& result);
	int Reward(UserWrap& user, const BaseCmdParams& params, Json::Value& result);
	int Get(Json::Value& result);
	bool IsValidActTime();
protected:
	int AutoRate();
private:
	const UserWrap& user_;
};

//鹊桥相会
class ActivityBirdBridge: public SecincActivityUnit {
public:
	enum {
		ACT_BIRD_BRIDGE_REWARD_LEFT = 0,
		ACT_BIRD_BRIDGE_REWARD_RIGHT = 1,
		ACT_BIRD_BRIDGE_REWARD_CENTER = 2,
		ACT_BIRD_BRIDGE_REWARD_DAILY = 3,
	};
	ActivityBirdBridge(const UserWrap& user);
	virtual void Reset();
	int DrawImpl(UserWrap& user, const BaseCmdParams& params, Json::Value& result);
	int RewardCenter(unsigned pointLeft, unsigned pointRight, vector<GiftEquipItem> &reward);
	int RewardEdge(Json::Value &act, unsigned type, unsigned id, unsigned point, vector<GiftEquipItem> &reward);
	int RewardDaily(unsigned point, vector<GiftEquipItem> &reward);
private:
	string _left_code;
	string _right_code;
	string _center_code;
	string _daily_code;
};
class NewWorldHeroPointUint : public BaseCmdUnit
{
public:
	NewWorldHeroPointUint(const UserWrap& user);
	int DrawImpl(UserWrap& user, const BaseCmdParams& params, Json::Value& result);
	unsigned GetOpenNum();
};
#endif /* LOGICCMDUNIT_H_ */
