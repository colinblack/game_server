/*
 * LogicCmdBase.h
 *
 *  Created on: 2016-8-17
 *      Author: @oulong
 */

#ifndef LOGICCMDBASE_H_
#define LOGICCMDBASE_H_

#include "Kernel.h"
#include "LogicEquipment.h"
#include "LogicUnitWrap.h"

class BaseCmdUnit
{
public:
	BaseCmdUnit(unsigned uid);
	virtual ~BaseCmdUnit();

	//根据Config读取活动
	virtual bool IsActiving(unsigned nTime
			, const std::string& start
			, const std::string& end);
	virtual unsigned GetVersionCfg(const std::string& szVersion);

	//添加新装备
	void AddEquips(const std::vector<ItemAdd>& items, Json::Value& result);
	void AddEquips(unsigned eqid, const std::string& op, Json::Value& result);
	void AddEquips(unsigned eqid, unsigned cnt, const std::string& op, Json::Value& result);

	////////////////////////////////////////////////
	//处理装备套装
	void AddSuitEquips(const std::vector<ItemAdd>& items, Json::Value& result);
	void AddSuitEquips(unsigned eqid, const std::string& op,  Json::Value& result);

	//消耗装备
	void UseEquips(unsigned eqid, unsigned ud, unsigned count, string reason);
	bool IsExistEquips(unsigned eqid, unsigned ud, unsigned count) const;

	//钻石消耗的替换
	void CostPurpleKey(unsigned ud, unsigned count, string reason, Json::Value& result);
	void CostGreenKey(unsigned ud, unsigned count, string reason, Json::Value& result);

	//英雄经验添加
	void AddHeroExp(Json::Value & herodata, int userlv, int add_exp);

	ItemAdd Equip2ItemAdd(const GiftEquipItem& gift, const std::string& reason);
	//添加GiftEquipItem装备[包含普通装备，套装，英雄处理]
	void AddGiftEquips(
			GiftEquipItem equips[]
			, unsigned size
			, const std::string& reason
			, Json::Value& result);

	void AddGiftEquips(
				const GiftEquipItem& equips
				, const std::string& reason
				, Json::Value& result);
	void AddGiftEquips(
					std::vector<GiftEquipItem>& equips
					, const std::string& reason
					, Json::Value& result);

	//
	void LoadUserGiftData(Json::Value& jsonData) const;
	void SaveUserGiftData(const Json::Value& jsonData) const;

	//
	unsigned GetActivityVersion(const std::string& szVersion) const;

	void TopZoneHttpRequest(const std::string& cgi
			, const std::string& action
			, const Json::Value& req_data
			, Json::Value& result);

	//处理奖励配置
	int ProvideCommonReward(const RewardConfig::RewardItemCfg & rewardcfg, const string & reason, Json::Value & result, unsigned endts = 0, unsigned count = 1);

	//通过ID获取装备信息
	int GetEquipById(unsigned eqid, Json::Value &equipment);

protected:
	///生成套装
	void HandleOneSuitEquip(const ItemAdd& item, Json::Value& newEquip);
	int  GetEquipSubByCh(unsigned ch);

	virtual void Save();

	//从概率集合中，按照概率,随机抽取结果
	static int TurnVecLuckTable(vector<unsigned> & prates, int len, int & target);
	static int SetBitCurrent(unsigned & current, int pos);
	static bool CheckPosIsZero(unsigned value, unsigned pos);
	static CDataXML* DataXmlPtr();
protected:
	unsigned 	m_nUid; //Uid
	bool need_save;
	Json::Value m_jsonData;
};

//活动
class BaseActivityUnit : public BaseCmdUnit
{
public:
	BaseActivityUnit(unsigned uid, const std::string& name, unsigned sid = 0);
	virtual ~BaseActivityUnit() {}

	bool IsNewVersion(int version) const;

	int GetVersion();

	int GetBeginTs();

	int GetEndTs();

	//获取活动时间到指定时间内的充值数目
	unsigned GetChargeByTime(UserWrap& userWrap, unsigned endts);

	//版本号检查
	virtual int CheckActVersion();

	//各派生类需实现，之所以不用纯虚函数，是为了考虑要使用该类直接生成对象的情况。
	virtual int ResetAct();
protected:
	ActInfoConfig status_cfg_;

	unsigned sid_;  //活动id
};

//用于GetSecinc存储数据的活动
//nat_id 见AppDefine.h => NewActType
//占用两个nat_id的暂不支持
class SecincActivityUnit : public BaseActivityUnit
{
public:
	SecincActivityUnit(unsigned uid, const std::string& name, int nat_id);
protected:
	void 	Init();
	virtual void Reset() = 0;
protected:
	int nat_id_;
};

////////////////////////////////////////////////////////////////////////////////////////
class BaseCmdParams
{
public:
	BaseCmdParams(const Json::Value& jsonData);

	virtual ~BaseCmdParams() {}

	//请求序列和最后访问时间
	unsigned SeqId() const;
	unsigned LastTime() const;

	const Json::Value & ParamsObj() const { return json_params_; }

	unsigned 	ValueAsUInt(const std::string& key) const;
	int 		ValueAsInt(const std::string& key) const;
	int 		ValueAsInt(const std::string& key, int def) const;
	std::string ValueAsString(const std::string& key) const;
	void 		ValueAsArray(const std::string& key, std::vector<unsigned>& vals) const;
private:
	unsigned 	seqid_;
	unsigned 	lasttime_;

	const Json::Value & json_params_;
};

//id > 0
class UnitIdCmdParams : public BaseCmdParams
{
public:
	UnitIdCmdParams(const Json::Value& jsonData);

	int Id() const { return id_; }

	virtual ~UnitIdCmdParams() {}
private:
	int 	id_;
};

//index >= 0
class UnitIndexCmdParams : public BaseCmdParams
{
public:
	UnitIndexCmdParams(const Json::Value& jsonData);

	int Index() const { return index_; }

	virtual ~UnitIndexCmdParams() {}
private:
	int 	index_;
};


//钻石消费改金币,需要添加道具参数,so....
//ud字段为可缺失
class UnitUdCmdParams : public BaseCmdParams
{
public:
	UnitUdCmdParams(const Json::Value& jsonData);

	int Ud() const { return ud_; }

	virtual ~UnitUdCmdParams() {}
private:
	int 	ud_;
};

/////////////////////////////////////////////////////////////////////////////////
//充值回馈活动，类似铸魂打折
class BaseFeedbackActUnit : public SecincActivityUnit
{
public:
	class DrawParams : public UnitIndexCmdParams
	{
	public:
		DrawParams(const Json::Value& jsonData)
			: UnitIndexCmdParams(jsonData)
		{
			eq_index_ = ValueAsInt("eq_idx");
		}

		int EquipIndex() const { return eq_index_; }
	private:
		int eq_index_;
	};

	BaseFeedbackActUnit(unsigned uid, const std::string& name, int nat_id, bool all = false);

	//领取奖励
	virtual int DrawImpl(UserWrap& user, const DrawParams& params, Json::Value& result);
protected:
	virtual void Reset();
	//可以领取多少项
	virtual int GetDrawItems() const = 0;
	//对应拉取项的配置
	virtual const JsonFeedbackItem& GetFeedbackItem(int index) const = 0;
	//操作码
	virtual const char* DrawOp() const = 0;

	bool m_all;
};


#endif /* LOGICCMDBASE_H_ */
