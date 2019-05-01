/*
 * MineManager.cpp
 *
 *  Created on: 2016-11-15
 *      Author: dawx62fac
 */


#include "MineManager.h"
#include "DataInc.h"

MineHole::MineHole() : uid_(0), level_(0), donate_cnt_(0)
{

}

void MineHole::Reset()
{
	uid_ = 0;
	level_ = 0;
	donate_cnt_ = 0;
	memset(donate_user_, 0, sizeof(donate_user_));
	memset(name_, 0, sizeof(name_));
}


bool MineHole::IsDonateFull() const
{
	int cnt = 0;
	if (level_ == 0)
	{
		cnt = MineCfgWrap().GetKingdomDonateCnt();
	}
	else
	{
		cnt = MineCfgWrap().GetNormalDonateCnt(level_);
	}

	if (cnt > DONATE_CNT_MAX)
	{
		error_log("mine_cfg_donate_cnt_error. %d", cnt);
		throw std::runtime_error("mine_cfg_donate_cnt_error");
	}

	return (cnt  == donate_cnt_);
}

bool MineHole::IsDonated(unsigned uid) const
{
	for (int i = 0; i < (int)donate_cnt_; i++)
	{
		if (donate_user_[i] == uid)
		{
			return true;
		}
	}

	return false;
}

void MineHole::Donate(unsigned uid)
{
	if (! IsOpen())
	{
		throw std::runtime_error("the_mine_not_open");
	}

	if (IsDonated(uid))
	{
		throw std::runtime_error("already_donated");
	}

	donate_user_[donate_cnt_ ++] = uid;
}

bool MineHole::IsOpen() const
{
	return uid_ > 0;
}

void MineHole::Open(unsigned uid, const std::string& name, int exp)
{
	if (uid_ > 0 && uid > 0)
	{
		throw std::runtime_error("the_mine_already_open");
	}

	if (name.size() >= BASE_NAME_LEN)
	{
		throw std::runtime_error("name_too_long");
	}

	uid_ = uid;
	if (exp >= 0)
	{
		level_ = MineCfgWrap().Exp2Level(exp);
	}
	else
	{
		level_ = 0;
	}

	donate_cnt_ = 0;
	memset(donate_user_, 0, sizeof(donate_user_));

	memset(name_, 0, sizeof(name_));
	memcpy(name_, name.c_str(), name.size());
}

////////////////////////////////////////////////////////////////////////////////
const MineHole& MineKingdom::MineNoramlHoleIndex(unsigned index) const
{
	if (index >= NORMAL_MINE_HOLE_CNT)
	{
		throw std::runtime_error("normal_mine_index_params_error");
	}

	return normal_[index];
}

MineHole& MineKingdom::MineNoramlHoleIndex(unsigned index)
{
	if (index >= NORMAL_MINE_HOLE_CNT)
	{
		throw std::runtime_error("normal_mine_index_params_error");
	}

	return normal_[index];
}

void MineKingdom::AddRecord(const MineRecord& record)
{
	if (record_ptr_  >= MINE_RECORD_MAX)
	{
		RomoveRecord(0, 10);
	}

	record_[record_ptr_++] = record;
}

void MineKingdom::RomoveRecord(unsigned index, unsigned nCnt)
{
	if (record_ptr_ <= (int)index)
	{
		return ;
	}

	int mv_cnt = record_ptr_ - index - nCnt;
	if (mv_cnt <= 0)
	{
		record_ptr_ = index;
		return ;
	}

	memmove(record_ + index, record_ + index + nCnt, mv_cnt * sizeof(MineRecord));
	record_ptr_ -= nCnt;
}

bool MineKingdom::IsMineMaster(unsigned uid)
{
	for (int i = 0; i < NORMAL_MINE_HOLE_CNT; i++)
	{
		if (normal_[i].Uid() == uid)
		{
			return true;
		}
	}

	return false;
}

void MineKingdom::AddOpenNoramlMineRecord(unsigned uid
		, const std::string& operate
		, const MineHole& hole)
{
	MineRecord record(e_OpenHole, 0);
	record.SetOperate(operate);
	record.SetParams(0, uid);
	record.SetParams(1, 0);
	record.SetParams(2, hole.Level());

	AddRecord(record);
}

void MineKingdom::AddOpenKingdomMineRecord(unsigned uid
		, const std::string& operate)
{
	MineRecord record(e_OpenHole, 1);
	record.SetOperate(operate);
	record.SetParams(0, uid);
	record.SetParams(1, 0);

	AddRecord(record);
}

void MineKingdom::AddNormalDonateRecord(unsigned uid
		, const std::string& operate, const MineHole& hole)
{
	MineRecord record(e_Donate, 0);
	record.SetOperate(operate);
	record.SetTarget(hole.Name());
	record.SetParams(0, uid);
	record.SetParams(1, hole.Uid());
	record.SetParams(2, hole.Level());
	record.SetParams(3, hole.DonateCnt());
	record.SetParams(4, MineCfgWrap().GetNormalDonateCnt(hole.Level()));

	AddRecord(record);
}

void MineKingdom::AddKingdomDonateRecord(unsigned uid
		, const std::string& operate)
{
	MineRecord record(e_Donate, 1);
	record.SetOperate(operate);
	record.SetParams(0, uid);
	record.SetParams(1, 0);

	AddRecord(record);
}

void MineKingdom::AddNormalHarvestRecord(const MineHole& hole, int val)
{
	MineRecord record(e_MinersHarvest, 0);
	record.SetOperate(hole.Name());
	record.SetParams(0, hole.Uid());
	record.SetParams(1, 0);
	record.SetParams(2, hole.Level());
	record.SetParams(3, val);

	AddRecord(record);
}

void MineKingdom::AddKingdomHarvestRecord(const MineHole& hole, int val)
{
	MineRecord record(e_MinersHarvest, 1);
	record.SetOperate(hole.Name());
	record.SetParams(0, hole.Uid());
	record.SetParams(1, 0);
	record.SetParams(2, val);

	AddRecord(record);
}

void MineKingdom::AddKingdomRewardRecord(unsigned uid
		, const std::string& operate, int val)
{
	MineRecord record(e_MineReward, 1);
	record.SetOperate(operate);
	record.SetParams(0, uid);
	record.SetParams(1, 0);
	record.SetParams(2, val);

	AddRecord(record);
}

void MineKingdom::FullMessage(::google::protobuf::RepeatedPtrField< ::ProtoMine::MineRecord >* obj)
{
	for (int i = 0; i < record_ptr_; i++)
	{
		record_[i].FullMessage(obj->Add());
	}
}
