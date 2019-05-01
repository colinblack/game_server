/*
 * DataHugeDiscount.cpp
 *
 *  Created on: 2016-12-19
 *      Author: dawx62fac
 */

#include "DataHugeDiscount.h"

DBCHugeDiscount::DBCHugeDiscount()
	: uid(0)
	, id(0)
	, version(0)
	, op_time(0)
	, item_1_cnt(0)
	, item_2_cnt(0)
	, item_3_cnt(0)
	, item_4_cnt(0)
	, item_5_cnt(0)
	, item_6_cnt(0)
{

}

DBCHugeDiscount::DBCHugeDiscount(unsigned uid_, unsigned id_)
	: uid(uid_)
	, id(id_)
	, version(0)
	, op_time(0)
	, item_1_cnt(0)
	, item_2_cnt(0)
	, item_3_cnt(0)
	, item_4_cnt(0)
	, item_5_cnt(0)
	, item_6_cnt(0)
{
}

uint16_t* DBCHugeDiscount::ItemCnt(unsigned id)
{
	uint16_t* item_ptr[MAX_ID] = {
			&item_1_cnt,
			&item_2_cnt,
			&item_3_cnt,
			&item_4_cnt,
			&item_5_cnt,
			&item_6_cnt,
	};

	if (id < 1 || id > MAX_ID)
	{
		throw std::runtime_error("id_out_valid_error");
	}

	return item_ptr[id - 1];
}

void DBCHugeDiscount::Reset(unsigned version_)
{
	version = version_;
	op_time = 0;

	for (int i = 1; i <= MAX_ID; i++)
	{
		uint16_t* ptr = ItemCnt(i);
		*ptr = 0;
	}
}

uint16_t DBCHugeDiscount::GetBuyCnt(unsigned id)
{
	uint16_t* ptr = ItemCnt(id);
	return *ptr;
}

void DBCHugeDiscount::OP(unsigned id)
{
	uint16_t* ptr = ItemCnt(id);
	(*ptr) ++;

	//op_time = Time::GetGlobalTime();
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
int DBCHugeDiscountHandler::Get(DBCHugeDiscount &data)
{
	warn_log("nonsupport_interface");
	return 0;
}

int DBCHugeDiscountHandler::Get(vector<DBCHugeDiscount> &data)
{
	if (data.empty())
	{
		return R_ERROR;
	}

	unsigned uid = data.begin()->uid;
	data.clear();

	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(version);
	DBCREQ_NEED(op_time);
	DBCREQ_NEED(item_1_cnt);
	DBCREQ_NEED(item_2_cnt);
	DBCREQ_NEED(item_3_cnt);
	DBCREQ_NEED(item_4_cnt);
	DBCREQ_NEED(item_5_cnt);
	DBCREQ_NEED(item_6_cnt);

	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(data);
	DBCREQ_ARRAY_GET_INT(data, uid);
	DBCREQ_ARRAY_GET_INT(data, id);
	DBCREQ_ARRAY_GET_INT(data, version);
	DBCREQ_ARRAY_GET_INT(data, op_time);
	DBCREQ_ARRAY_GET_INT(data, item_1_cnt);
	DBCREQ_ARRAY_GET_INT(data, item_2_cnt);
	DBCREQ_ARRAY_GET_INT(data, item_3_cnt);
	DBCREQ_ARRAY_GET_INT(data, item_4_cnt);
	DBCREQ_ARRAY_GET_INT(data, item_5_cnt);
	DBCREQ_ARRAY_GET_INT(data, item_6_cnt);
	DBCREQ_ARRAY_GET_END();

	return 0;
}

int DBCHugeDiscountHandler::Add(DBCHugeDiscount &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, version);
	DBCREQ_SET_INT(data, op_time);
	DBCREQ_SET_INT(data, item_1_cnt);
	DBCREQ_SET_INT(data, item_2_cnt);
	DBCREQ_SET_INT(data, item_3_cnt);
	DBCREQ_SET_INT(data, item_4_cnt);
	DBCREQ_SET_INT(data, item_5_cnt);
	DBCREQ_SET_INT(data, item_6_cnt);

	DBCREQ_EXEC;

	return 0;
}

int DBCHugeDiscountHandler::Set(DBCHugeDiscount &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, version);
	DBCREQ_SET_INT(data, op_time);
	DBCREQ_SET_INT(data, item_1_cnt);
	DBCREQ_SET_INT(data, item_2_cnt);
	DBCREQ_SET_INT(data, item_3_cnt);
	DBCREQ_SET_INT(data, item_4_cnt);
	DBCREQ_SET_INT(data, item_5_cnt);
	DBCREQ_SET_INT(data, item_6_cnt);

	DBCREQ_EXEC;
	return 0;
}



int DBCHugeDiscountHandler::Del(DBCHugeDiscount &data)
{
	//
	warn_log("nonsupport_interface");
	return 0;
}
