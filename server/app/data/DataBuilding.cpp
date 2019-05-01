/*
 * DataBuilding.cpp
 *
 *  Created on: 2016-8-31
 *      Author: dawx62fac
 */

#include <stdexcept>

#include "DataBuilding.h"
#include "BuildingCfgWrap.h"
#include "DataBuildingManager.h"


DBCBuildingData::DBCBuildingData()
		: uid(0)
		, id(0)
		, level(0)
		, status(-1)
		, is_speed(0)
		, handle_time(0)
{

}

DBCBuildingData::DBCBuildingData(unsigned uid_, const ::Building::Item& cfg)
	: uid(uid_)
	, level(1)
	, status(-1)
	, is_speed(0)
	, handle_time(0)
{
	id = cfg.id();
}

bool DBCBuildingData::Unlock()
{
	if (status != -1)
	{
		//throw std::runtime_error("can't_to_un_lock_build");
		return false;
	}

	status = 1;
	handle_time = Time::GetGlobalTime();

	return true;
}

void DBCBuildingData::FinishUnlock(int cost)
{
	status = 0;
	handle_time += cost;
}

void DBCBuildingData::FinishUpgrade(int cost)
{
	status = 0;
	level += 1;
	is_speed = 0;
	handle_time += cost;
}

unsigned DBCBuildingData::StartHandleTime()
{
	return handle_time;
}

unsigned DBCBuildingData::OverHandleTime()
{
	return handle_time;
}

void DBCBuildingData::OnceFinishUpgrade()
{
	unsigned now = Time::GetGlobalTime();
	int cost = now > handle_time ? (now - handle_time) : 0;

	FinishUpgrade(cost);
}

int DBCBuildingData::RefreshStatus()
{
	//解锁状态
	if (status == 1)
	{
		BuildCfgWrap buildCfgWrap;
		unsigned now = Time::GetGlobalTime();
		unsigned unlock_time = buildCfgWrap.UnlockTime(id);
		if (handle_time + unlock_time <= now)
		{
			FinishUnlock(unlock_time);
			return 1;
		}
	}

	//升级状态
	if (status == 2)
	{
		unsigned now = Time::GetGlobalTime();
		unsigned up_time = UpgradeTime();
		if (handle_time + up_time  <= now)
		{
			FinishUpgrade(up_time);
			return 2;
		}
	}

	return 0;
}

unsigned DBCBuildingData::UpgradeTime()
{
	BuildCfgWrap buildCfgWrap;

	unsigned up_time = buildCfgWrap.UpgradeTime(id, level + 1);
	if (is_speed > 0)
	{
		unsigned s_time = buildCfgWrap.SpeedTime(id, level + 1);
		unsigned costtime = up_time >= s_time ? (up_time - s_time) : 0;
		return costtime ;
	}
	else
	{
		return up_time;
	}

}

bool DBCBuildingData::IsUnLocked()
{
	return (status >= 0);
}

bool DBCBuildingData::Normal()
{
	return (status == 0);
}

bool DBCBuildingData::Upgrading()
{
	return (status == 2);
}

void DBCBuildingData::Upgrade(unsigned start_time)
{
	if (status != 0)
	{
		throw std::runtime_error("build_status_error");
	}

	status = 2;
	is_speed = 0;
	handle_time = start_time;

}

void DBCBuildingData::FreeSpeed()
{
	if (status != 2)
	{
		//throw std::runtime_error("over_upgrading");
		return ;
	}

	if (is_speed > 0)
	{
		//throw std::runtime_error("already_speed");
		return ;
	}

	BuildCfgWrap buildCfgWrap;
	is_speed = 1;

	unsigned up_time = UpgradeTime();
	if (handle_time + up_time <= Time::GetGlobalTime())
	{
		FinishUpgrade(up_time);
	}
}

void DBCBuildingData::FullMessage(::ProtoBuilding::BuildInfo* obj)
{
	obj->set_id(id);
	obj->set_level(level);
	obj->set_status(status);
	obj->set_handle_time(handle_time);
	obj->set_is_speed(is_speed > 0);
}

///////////////////////////////////////////////////////////////////////////
DBCBuidingQueueData::DBCBuidingQueueData()
	: uid(0)
	, auto_cnt(0)
	, type(0)
	, build_1(-1)
	, build_time_1(0)
	, build_2(-1)
	, build_time_2(0)
	, build_3(-1)
	, build_time_3(0)
	, build_4(-1)
	, build_time_4(0)
{
}

DBCBuidingQueueData::DBCBuidingQueueData(unsigned uid_)
	: uid(uid_)
	, auto_cnt(0)
	, type(0)
	, build_1(-1)
	, build_time_1(0)
	, build_2(-1)
	, build_time_2(0)
	, build_3(-1)
	, build_time_3(0)
	, build_4(-1)
	, build_time_4(0)
{
}

void DBCBuidingQueueData::Unlock(int unlock_cnt)
{
	for (int i = 0; i < DBCBuidingQueueData::capacity; ++i)
	{
		if (unlock_cnt <= 0) break;

		int32_t* q = Queue(i);
		if (*q < 0)
		{
			*q = 0;

			--unlock_cnt;
		}
	}
}

int32_t* DBCBuidingQueueData::Queue(int index)
{
	if (index < 0 || index >= DBCBuidingQueueData::capacity)
	{
		throw std::runtime_error("building_queue_index_error");
	}
	int32_t *queue[DBCBuidingQueueData::capacity] = {&build_1, &build_2, &build_3, &build_4};
	return (queue[index]);
}

uint32_t* DBCBuidingQueueData::QueueTime(int index)
{
	if (index < 0 || index >= DBCBuidingQueueData::capacity)
	{
		throw std::runtime_error("building_queue_time_index_error");
	}
	uint32_t *queue[DBCBuidingQueueData::capacity] = {&build_time_1, &build_time_2, &build_time_3, &build_time_4};
	return (queue[index]);
}

bool DBCBuidingQueueData::QueueIsBusy(int index)
{
	int32_t* q = Queue(index);
	return (*(q)) > 0;
}

void DBCBuidingQueueData::QueueOverWork(int index, uint32_t time)
{
	int32_t* q = Queue(index);
	uint32_t* q_t = QueueTime(index);

	*q = 0;
	*q_t = time;
}

unsigned DBCBuidingQueueData::QueueBuild(int index)
{
	int32_t* q = Queue(index);
	return *q;
}

unsigned DBCBuidingQueueData::QueueOverTime(int index)
{
	uint32_t* q_t = QueueTime(index);
	if (*q_t > 0)
	{
		return *q_t;
	}
	else
	{
		return Time::GetGlobalTime();
	}
}

int  DBCBuidingQueueData::GetEmpty() //-1为没有
{
	for (int i = 0; i < DBCBuidingQueueData::capacity; ++i)
	{
		int32_t* q = Queue(i);
		if (*q == 0)
		{
			return i;
		}
	}

	return -1;
}

void DBCBuidingQueueData::QueueUpgrade(int index, unsigned buildid)
{
	int32_t* q = Queue(index);
	*q = buildid;
}


bool DBCBuidingQueueData::IsAutoUpgrade()
{
	return (auto_cnt > 0) && (type > 0);
}

void DBCBuidingQueueData::DecAutoUpgrade()
{
	auto_cnt = auto_cnt > 1 ? auto_cnt - 1 : 0;
	if (0 == auto_cnt)
	{
		type = 0;
	}
}

unsigned DBCBuidingQueueData::FreeQueueCnt()
{
	unsigned cnt = 0;
	int32_t *queue[DBCBuidingQueueData::capacity] = {&build_1, &build_2, &build_3, &build_4};
	for (int i = 0; i < DBCBuidingQueueData::capacity; ++i)
	{
		if(*(queue[i]) == 0)
		{
			++cnt;
		}
	}

	return cnt;
}

unsigned DBCBuidingQueueData::UnlockQueueCnt()
{
	unsigned cnt = 0;
	for (int i = 0; i < DBCBuidingQueueData::capacity; ++i)
	{
		int32_t* q = Queue(i);
		if (*q >= 0)
		{
			++cnt;
		}
	}

	return cnt;
}

void DBCBuidingQueueData::SetAutoUpgrade(uint8_t build_type, int16_t cnt)
{
	type = build_type;
	auto_cnt = cnt;

	uint32_t *queue[DBCBuidingQueueData::capacity] = {&build_time_1, &build_time_2, &build_time_3, &build_time_4};
	for (int i = 0; i < DBCBuidingQueueData::capacity; ++i)
	{
		int32_t* q = Queue(i);
		if (*q == 0)
		{
			//
			*queue[i] = (uint32_t)Time::GetGlobalTime();
		}
	}
}

void DBCBuidingQueueData::AbolishAutoUpgrade()
{
	auto_cnt = 0;
	type = 0;
}

void DBCBuidingQueueData::GetUpgradeBuilds(std::vector<unsigned>& result)
{
	result.clear();
	for (int i = 0; i < DBCBuidingQueueData::capacity; ++i)
	{
		int32_t* q = Queue(i);
		if (*q > 0)
		{
			result.push_back(*q);
		}
	}
}

void DBCBuidingQueueData::FullMessage(ProtoBuilding::BuildQueue* obj)
{
	obj->set_left_cnt(auto_cnt);
	obj->set_type(type);

	int32_t *queue[4] = {&build_1, &build_2, &build_3, &build_4};
	for(int i = 0; i < 4; ++i)
	{
		obj->add_queue(*(queue[i]));
	}
}

//////////////////////////////////////////////////////////////////
int DBCBuildingHandler::Get(DBCBuildingData &data)
{
	warn_log("don't call this interface");
	//throw std::runtime_error("can't_call");
	return R_ERROR;
}

int DBCBuildingHandler::Get(vector<DBCBuildingData> &data)
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
	DBCREQ_NEED(level);
	DBCREQ_NEED(status);
	DBCREQ_NEED(is_speed);
	DBCREQ_NEED(handle_time);

	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(data);
	DBCREQ_ARRAY_GET_INT(data, uid);
	DBCREQ_ARRAY_GET_INT(data, id);
	DBCREQ_ARRAY_GET_INT(data, level);
	DBCREQ_ARRAY_GET_INT(data, status);
	DBCREQ_ARRAY_GET_INT(data, is_speed);
	DBCREQ_ARRAY_GET_INT(data, handle_time);
	DBCREQ_ARRAY_GET_END();

	return 0;
}

int DBCBuildingHandler::Add(DBCBuildingData &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, status);
	DBCREQ_SET_INT(data, is_speed);
	DBCREQ_SET_INT(data, handle_time);

	DBCREQ_EXEC;
	return 0;
}

int DBCBuildingHandler::Set(DBCBuildingData &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

	DBCREQ_SET_INT(data, id);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, status);
	DBCREQ_SET_INT(data, is_speed);
	DBCREQ_SET_INT(data, handle_time);

	DBCREQ_EXEC;

	return 0;
}

////////////////////////////////////////////////////////////////////////////////
//
int DBCBuildingQueueHandler::Get(DBCBuidingQueueData &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(auto_cnt);
	DBCREQ_NEED(type);
	DBCREQ_NEED(build_1);
	DBCREQ_NEED(build_time_1);
	DBCREQ_NEED(build_2);
	DBCREQ_NEED(build_time_2);
	DBCREQ_NEED(build_3);
	DBCREQ_NEED(build_time_3);
	DBCREQ_NEED(build_4);
	DBCREQ_NEED(build_time_4);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, auto_cnt);
	DBCREQ_GET_INT(data, type);
	DBCREQ_GET_INT(data, build_1);
	DBCREQ_GET_INT(data, build_time_1);
	DBCREQ_GET_INT(data, build_2);
	DBCREQ_GET_INT(data, build_time_2);
	DBCREQ_GET_INT(data, build_3);
	DBCREQ_GET_INT(data, build_time_3);
	DBCREQ_GET_INT(data, build_4);
	DBCREQ_GET_INT(data, build_time_4);

	return 0;
}

int DBCBuildingQueueHandler::Add(DBCBuidingQueueData &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, auto_cnt);
	DBCREQ_SET_INT(data, type);
	DBCREQ_SET_INT(data, build_1);
	DBCREQ_SET_INT(data, build_time_1);
	DBCREQ_SET_INT(data, build_2);
	DBCREQ_SET_INT(data, build_time_2);
	DBCREQ_SET_INT(data, build_3);
	DBCREQ_SET_INT(data, build_time_3);
	DBCREQ_SET_INT(data, build_4);
	DBCREQ_SET_INT(data, build_time_4);

	DBCREQ_EXEC;
	return 0;
}

int DBCBuildingQueueHandler::Set(DBCBuidingQueueData &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, auto_cnt);
	DBCREQ_SET_INT(data, type);
	DBCREQ_SET_INT(data, build_1);
	DBCREQ_SET_INT(data, build_time_1);
	DBCREQ_SET_INT(data, build_2);
	DBCREQ_SET_INT(data, build_time_2);
	DBCREQ_SET_INT(data, build_3);
	DBCREQ_SET_INT(data, build_time_3);
	DBCREQ_SET_INT(data, build_4);
	DBCREQ_SET_INT(data, build_time_4);

	DBCREQ_EXEC;
	return 0;
}







