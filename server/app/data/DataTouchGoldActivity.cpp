/*
 * DataTouchGoldActivity.cpp
 *
 *  Created on: 2016-12-9
 *      Author: dawx62fac
 */

#include "DataTouchGoldActivity.h"

DBCTouchGold::DBCTouchGold()
	: uid(0)
	, version(0)
	, total_touchs(0)
	, tomb_id(0)
	, tomb_unlock_bit(0)
	, touch_bit(0)
	, surpluses(0)
	, output_1_cnt(0)
	, output_2_cnt(0)
	, output_3_cnt(0)
	, output_4_cnt(0)
	, output_5_cnt(0)
	, ts_op(0)
{
}

void DBCTouchGold::ResetVersion(unsigned version_)
{
	version = version_;
	total_touchs = 0;
	tomb_id = 0;
	tomb_unlock_bit = 0;
	touch_bit = 0;
	surpluses = 0;
	for (int i = 0; i < TOUCH_CNT; i++)
	{
		uint16_t* out_val = Output(i);
		*out_val = 0;
	}

	UnlockTomb(1);
	ResetTomb(1);
}

void DBCTouchGold::ResetTomb(unsigned id)
{
	CheckIdParams(id);

	tomb_id = id;
	for (int i = 0; i < TOUCH_CNT; i++)
	{
		uint16_t* out_val = Output(i);
		*out_val = 0;
	}
	touch_bit = 0;
	surpluses = TOUCH_CNT;
}

void DBCTouchGold::CheckIdParams(int id) const
{
	if (id <= 0 || id > TOMB_CNT)
	{
		throw std::runtime_error("tomb_id_params_error");
	}
}


void DBCTouchGold::UnlockTomb(int id)
{
	CheckIdParams(id);

	tomb_unlock_bit |=  1 << (id - 1);
}

bool DBCTouchGold::IsUnlocked(int id) const
{
	CheckIdParams(id);

	return (tomb_unlock_bit & (1 << (id - 1))) > 0;
}

uint16_t DBCTouchGold::GetOutput(int index) const
{
	if (index < 0 || index >= TOUCH_CNT)
	{
		throw std::runtime_error("output_index_params_error");
	}

	uint16_t output_addr[TOUCH_CNT] = {
			output_1_cnt,
			output_2_cnt,
			output_3_cnt,
			output_4_cnt,
			output_5_cnt,
	};

	return output_addr[index];
}

uint16_t* DBCTouchGold::Output(int index)
{
	if (index < 0 || index >= TOUCH_CNT)
	{
		throw std::runtime_error("output_index_params_error");
	}

	uint16_t* output_addr[TOUCH_CNT] = {
			&output_1_cnt,
			&output_2_cnt,
			&output_3_cnt,
			&output_4_cnt,
			&output_5_cnt,
	};

	return output_addr[index];
}

uint16_t DBCTouchGold::GetTouches() const
{
	uint16_t cnt = 0;
	for (int i = 0; i < TOUCH_POS_CNT; i++)
	{
		if ((touch_bit & (1 << i)) > 0)
		{
			cnt ++;
		}
	}

	return cnt;
}

bool DBCTouchGold::IsTouched(int index) const
{
	if (index < 0 || index >= TOUCH_POS_CNT)
	{
		throw std::runtime_error("touch_pos_index_params_error");
	}

	return ((touch_bit & (1 << index)) > 0);
}

void DBCTouchGold::TouchGold(int index, uint16_t gold)
{
	int touches = GetTouches();
	if (touches >= TOUCH_CNT)
	{
		throw std::runtime_error("out_touch_times");
	}

	if (gold == 0)
	{
		throw std::runtime_error("out_gold_need_over_zero");
	}

	if (index < 0 || index >= TOUCH_POS_CNT)
	{
		throw std::runtime_error("touch_gold_index_params_error");
	}

	if ((touch_bit & (1 << index)) > 0)
	{
		throw std::runtime_error("already_touched");
	}

	touch_bit |= (1 << index);
	//此处进行产出数据的重新排列
	uint16_t nVal[TOUCH_POS_CNT] = {0};
	int touch_index = 0;
	for (int i = 0; i <= MaxTouchPosition(); i++)
	{
		if ((touch_bit & (1 << i)) > 0)
		{
			if (i == index)
			{
				nVal[i] = gold;
			}
			else
			{
				nVal[i] = GetOutput(touch_index ++);
			}
		}
	}

	int re_index = 0;
	for (int i = 0; i <= MaxTouchPosition(); i++)
	{
		if (nVal[i] > 0)
		{
			uint16_t*  out_val = Output(re_index++);
			*out_val = nVal[i];
		}
	}
	//@end

}
///////////////////////////////////////////////////////////////////////////
int DBCTouchGoldHandler::Get(DBCTouchGold &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(version);
	DBCREQ_NEED(total_touchs);
	DBCREQ_NEED(tomb_id);
	DBCREQ_NEED(tomb_unlock_bit);
	DBCREQ_NEED(touch_bit);
	DBCREQ_NEED(surpluses);
	DBCREQ_NEED(output_1_cnt);
	DBCREQ_NEED(output_2_cnt);
	DBCREQ_NEED(output_3_cnt);
	DBCREQ_NEED(output_4_cnt);
	DBCREQ_NEED(output_5_cnt);
	DBCREQ_NEED(ts_op);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, version);
	DBCREQ_GET_INT(data, total_touchs);
	DBCREQ_GET_INT(data, tomb_id);
	DBCREQ_GET_INT(data, tomb_unlock_bit);
	DBCREQ_GET_INT(data, touch_bit);
	DBCREQ_GET_INT(data, surpluses);
	DBCREQ_GET_INT(data, output_1_cnt);
	DBCREQ_GET_INT(data, output_2_cnt);
	DBCREQ_GET_INT(data, output_3_cnt);
	DBCREQ_GET_INT(data, output_4_cnt);
	DBCREQ_GET_INT(data, output_5_cnt);
	DBCREQ_GET_INT(data, ts_op);

	return 0;
}

int DBCTouchGoldHandler::Get(vector<DBCTouchGold> &data)
{
	warn_log("nonsupport_interface");
	return 0;
}

int DBCTouchGoldHandler::Add(DBCTouchGold &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, version);
	DBCREQ_SET_INT(data, total_touchs);
	DBCREQ_SET_INT(data, tomb_id);
	DBCREQ_SET_INT(data, tomb_unlock_bit);
	DBCREQ_SET_INT(data, touch_bit);
	DBCREQ_SET_INT(data, surpluses);
	DBCREQ_SET_INT(data, output_1_cnt);
	DBCREQ_SET_INT(data, output_2_cnt);
	DBCREQ_SET_INT(data, output_3_cnt);
	DBCREQ_SET_INT(data, output_4_cnt);
	DBCREQ_SET_INT(data, output_5_cnt);
	DBCREQ_SET_INT(data, ts_op);

	DBCREQ_EXEC;

	return 0;

}

int DBCTouchGoldHandler::Set(DBCTouchGold &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, version);
	DBCREQ_SET_INT(data, total_touchs);
	DBCREQ_SET_INT(data, tomb_id);
	DBCREQ_SET_INT(data, tomb_unlock_bit);
	DBCREQ_SET_INT(data, touch_bit);
	DBCREQ_SET_INT(data, surpluses);
	DBCREQ_SET_INT(data, output_1_cnt);
	DBCREQ_SET_INT(data, output_2_cnt);
	DBCREQ_SET_INT(data, output_3_cnt);
	DBCREQ_SET_INT(data, output_4_cnt);
	DBCREQ_SET_INT(data, output_5_cnt);
	DBCREQ_SET_INT(data, ts_op);

	DBCREQ_EXEC;

	return 0;
}

int DBCTouchGoldHandler::Del(DBCTouchGold &data)
{
	warn_log("nonsupport_interface");
	return 0;
}
