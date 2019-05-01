/*
 * MineManager.h
 *
 *  Created on: 2016-11-15
 *      Author: dawx62fac
 */

#ifndef MINEMANAGER_H_
#define MINEMANAGER_H_

#include "Kernel.h"


enum
{
	NORMAL_MINE_HOLE_CNT = 8, //普通矿洞个数
	KINGDOM_MINE_HOLE_CNT = 1, //国家矿洞
//	PRIMARY_DONATE_CNT = 5,    //
//	MIDDLE_DONATE_CNT_MAX = 10,
//	ADVANCE_DONATE_CNT_MAX = 15,
	DONATE_CNT_MAX = 20, //捐献次数
	MINE_RECORD_MAX = 200,
	MINE_RECORD_PARAMS_CNT = 5,
};

class MineHole
{
public:
	MineHole();

	void Open(unsigned uid, const std::string& name, int exp = -1);

	bool IsDonateFull() const;
	bool IsOpen() const;
	void Reset();

	bool IsDonated(unsigned uid) const;  //是否捐献过
	void Donate(unsigned uid);     //捐献

public:
	unsigned Uid() const  { return uid_; }
	unsigned Level() const { return level_; }
	unsigned DonateCnt() const { return donate_cnt_; }
	std::string Name() const { return std::string(name_); }
private:
	unsigned uid_;
	uint8_t	 level_; 	//煤窑等级  //国家矿洞没有等级
	uint8_t  donate_cnt_; 	//捐献次数
	unsigned donate_user_[DONATE_CNT_MAX];  //捐献人列表
	char 	 name_[BASE_NAME_LEN]; //操作者
};

enum MineOp
{
	e_OpenHole = 1, //开矿
	e_Donate = 2,   //援建
	e_MinersHarvest = 3, //矿主收获
	e_MineReward	= 4, //国家矿的奖励
};

class MineRecord
{
public:
	MineRecord(int op, int type)
		: op_ts_(Time::GetGlobalTime()), op_(op), type_(type)
	{
		memset(operate_,0, sizeof(operate_));
		memset(target_, 0, sizeof(target_));
		memset(params_, -1, sizeof(params_));
	}

	void SetOperate(const std::string& operate)
	{
		if (operate.size() >= BASE_NAME_LEN)
		{
			throw std::runtime_error("name_too_long");
		}

		memcpy(operate_, operate.c_str(), operate.size());
	}

	void SetTarget(const std::string& target)
	{
		if (target.size() >= BASE_NAME_LEN)
		{
			throw std::runtime_error("name_too_long");
		}

		memcpy(target_, target.c_str(), target.size());
	}

	void SetParams(int index , unsigned val)
	{
		if (index < 0 || index >= MINE_RECORD_PARAMS_CNT)
		{
			throw std::runtime_error("index_params_error");
		}

		params_[index] = val;
	}

	void FullMessage(ProtoMine::MineRecord* obj)
	{
		obj->set_operate(operate_);
		obj->set_target(target_);
		obj->set_op(op_);
		obj->set_type(type_);
		obj->set_ts(op_ts_);

		for (int i = 0; i < MINE_RECORD_PARAMS_CNT; i++)
		{
			if (params_[i] >= 0)
			{
				obj->add_params(params_[i]);
			}
			else
			{
				break;
			}
		}
	}
private:
	unsigned 	op_ts_;
	uint8_t	 	op_;
	uint8_t		type_;  //矿山类型 0--普通 1--国家
	int			params_[MINE_RECORD_PARAMS_CNT];
	char 		operate_[BASE_NAME_LEN]; //操作者
	char 		target_[BASE_NAME_LEN];
};

class MineKingdom
{
public:
	const MineHole& MineNoramlHoleIndex(unsigned index) const;
	MineHole& MineNoramlHoleIndex(unsigned index);

	int		  MineNoramlHoleSize() const { return NORMAL_MINE_HOLE_CNT; }
	const MineHole& MineKingdomHole() const { return country_; }
	MineHole& MineKingdomHole() { return country_; }

	//开启
	void AddOpenNoramlMineRecord(unsigned uid, const std::string& operate, const MineHole& hole);
	void AddOpenKingdomMineRecord(unsigned uid, const std::string& operate);
	//捐赠
	void AddNormalDonateRecord(unsigned uid, const std::string& operate, const MineHole& hole);
	void AddKingdomDonateRecord(unsigned uid, const std::string& operate);
	//收获
	void AddNormalHarvestRecord(const MineHole& hole, int val);
	void AddKingdomHarvestRecord(const MineHole& hole, int val);
	//
	void AddKingdomRewardRecord(unsigned uid, const std::string& operate, int val);

	void FullMessage(::google::protobuf::RepeatedPtrField< ::ProtoMine::MineRecord >* obj);

	bool IsMineMaster(unsigned uid);
private:
	void AddRecord(const MineRecord& record);
	void RomoveRecord(unsigned index, unsigned nCnt = 1);
private:
	MineHole normal_[NORMAL_MINE_HOLE_CNT];
	MineHole country_;
	unsigned record_ptr_;
	MineRecord record_[MINE_RECORD_MAX];
};

struct MineKingdomAllData
{
	MineKingdom data[SG17_KINGDOM];
};

class MineManager
	: public MemorySingleton<MineKingdomAllData, MEMORY_MINE>
	, public CSingleton<MineManager>
{
private:
	friend class CSingleton<MineManager>;
	MineManager(){}
	~MineManager() {}
public:
	void CallDestroy() {Destroy();}


	MineKingdom& GetMine(unsigned kingdom)
	{
		if (kingdom < 1 || kingdom > SG17_KINGDOM)
		{
			throw std::runtime_error("kingdom_params_error");
		}

		return this->m_data->data[kingdom - 1];
	}

};

#endif /* MINEMANAGER_H_ */
