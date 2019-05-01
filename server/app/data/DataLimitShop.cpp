/*
 * DataLimitShop.cpp
 *
 *  Created on: 2016-11-1
 *      Author: dawx62fac
 */

#include "DataLimitShop.h"

DBCLimitShop::DBCLimitShop()
	: uid(0)
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

void DBCLimitShop::Reset(unsigned version_)
{
	version = version_;
	op_time = 0;
	for (int i = 1; i <= MAX_ID; i++)
	{
		uint16_t* ptr = ItemCnt(i);
		*ptr = 0;
	}
}

uint16_t* DBCLimitShop::ItemCnt(unsigned id)
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

uint16_t DBCLimitShop::GetBuyCnt(unsigned id)
{
	uint16_t* ptr = ItemCnt(id);
	return *ptr;
}

void DBCLimitShop::OP(unsigned id)
{
	uint16_t* ptr = ItemCnt(id);
	(*ptr) ++;

	op_time = Time::GetGlobalTime();
}
/////////////////////////////////////////////////////////////////////////////
int DBCLimitShopHandler::Get(DBCLimitShop &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(version);
	DBCREQ_NEED(op_time);
	DBCREQ_NEED(item_1_cnt);
	DBCREQ_NEED(item_2_cnt);
	DBCREQ_NEED(item_3_cnt);
	DBCREQ_NEED(item_4_cnt);
	DBCREQ_NEED(item_5_cnt);
	DBCREQ_NEED(item_6_cnt);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, version);
	DBCREQ_GET_INT(data, op_time);
	DBCREQ_GET_INT(data, item_1_cnt);
	DBCREQ_GET_INT(data, item_2_cnt);
	DBCREQ_GET_INT(data, item_3_cnt);
	DBCREQ_GET_INT(data, item_4_cnt);
	DBCREQ_GET_INT(data, item_5_cnt);
	DBCREQ_GET_INT(data, item_6_cnt);

	return 0;
}

int DBCLimitShopHandler::Add(DBCLimitShop &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

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

int DBCLimitShopHandler::Set(DBCLimitShop &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

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

int DBCLimitShopHandler::Get(vector<DBCLimitShop> &data)
{
	warn_log("nonsupport_interface");
	return 0;
}

int DBCLimitShopHandler::Del(DBCLimitShop &data)
{
	//
	warn_log("nonsupport_interface");
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
int DataLimitShopMgr::OnInit()
{
	for(unsigned i=0; i < DB_BASE_BUFF*DB_BASE_FULL; ++i)
	{
		if(!m_data->Empty(i))
		{
			const DBCLimitShop& item = m_data->data[i];
			m_map[item.uid] = i;
		}
	}
	return 0;
}

int DataLimitShopMgr::FreeIndex()
{
	int index = GetFreeIndex();
	if (index < 0)
	{
		error_log("index: %d", index);
		throw std::runtime_error("Get_free_index_error");
	}

	return index;
}

void DataLimitShopMgr::NewItem(unsigned uid, int index)
{
	DBCLimitShop data;
	data.uid = uid;
	//int index = FreeIndex();
	if(Add(index, data))
	{
		m_map[uid] = index;
	}
	else
	{
		error_log("add_error.uid=%u,", uid);
		throw std::runtime_error("add_limit_shop_item_error");
	}
}

int DataLimitShopMgr::LoadBuffer(unsigned uid)
{
	if (m_map.count(uid) > 0)
	{
		throw std::runtime_error("already_load_limit_shop_data");
	}

	if (IsFull())
	{
		error_log("uid:%u, load_data_error", uid);
		throw std::runtime_error("limit_shop_data_is_full");
	}

	int index = FreeIndex();
	m_data->data[index].uid = uid;
	int ret = base::Load(index);
	if (R_ERR_NO_DATA == ret)
	{
		NewItem(uid, index);
	}
	else
	{
		if (ret != 0)
		{
			error_log("uid:%u, load_data_error, ret:%d", uid, ret);
			throw std::runtime_error("load_limit_shop_error");
		}

		m_map[uid] = index;
	}

	return index;
}

void DataLimitShopMgr::DoClear(unsigned uid)
{
	std::map<unsigned, unsigned>::iterator it = m_map.find(uid);
	if (it != m_map.end())
	{
		unsigned idx = it->second;
		base::Clear(idx);

		m_map.erase(uid);
	}
}

void DataLimitShopMgr::DoSave(unsigned uid)
{
	std::map<unsigned, unsigned>::iterator it = m_map.find(uid);
	if (it != m_map.end())
	{
		unsigned idx = it->second;
		base::AddSave(idx);
	}
}

void DataLimitShopMgr::Online(unsigned uid)
{
	try
	{
		LoadBuffer(uid);
	}
	catch(const std::exception& e)
	{
		//error_log("uid: %u, %s", uid, e.what());
	}
}


int DataLimitShopMgr::GetIndex(unsigned uid)
{
	std::map<unsigned, unsigned>::iterator it = m_map.find(uid);
	if (it != m_map.end())
	{
		return it->second;
	}
	else
	{
		return this->LoadBuffer(uid);
	}
}


