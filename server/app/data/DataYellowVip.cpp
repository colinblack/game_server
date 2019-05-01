#include "DataYellowVip.h"

int CDataYellowVip::Get(DataYellowVip &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(levelstatus);
	DBCREQ_NEED(newerstatus);
	DBCREQ_NEED(dailystatus);
	DBCREQ_NEED(year_daily_status);
	DBCREQ_NEED(daily_reward_time);
	DBCREQ_NEED(year_reward_time);
	DBCREQ_NEED(qqzone_dailystatus);
	DBCREQ_NEED(qqzone_daily_time);
	DBCREQ_NEED(qqzone_levelstatus);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, levelstatus);
	DBCREQ_GET_INT(data, newerstatus);
	DBCREQ_GET_INT(data, dailystatus);
	DBCREQ_GET_INT(data, year_daily_status);
	DBCREQ_GET_INT(data, daily_reward_time);
	DBCREQ_GET_INT(data, year_reward_time);
	DBCREQ_GET_INT(data, qqzone_dailystatus);
	DBCREQ_GET_INT(data, qqzone_daily_time);
	DBCREQ_GET_INT(data, qqzone_levelstatus);

	return 0;
}

int CDataYellowVip::Add(DataYellowVip &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, levelstatus);
	DBCREQ_SET_INT(data, newerstatus);
	DBCREQ_SET_INT(data, dailystatus);
	DBCREQ_SET_INT(data, year_daily_status);
	DBCREQ_SET_INT(data, daily_reward_time);
	DBCREQ_SET_INT(data, year_reward_time);
	DBCREQ_SET_INT(data, qqzone_dailystatus);
	DBCREQ_SET_INT(data, qqzone_daily_time);
	DBCREQ_SET_INT(data, qqzone_levelstatus);

	DBCREQ_EXEC;

	return 0;
}

int CDataYellowVip::Set(DataYellowVip &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, levelstatus);
	DBCREQ_SET_INT(data, newerstatus);
	DBCREQ_SET_INT(data, dailystatus);
	DBCREQ_SET_INT(data, year_daily_status);
	DBCREQ_SET_INT(data, daily_reward_time);
	DBCREQ_SET_INT(data, year_reward_time);
	DBCREQ_SET_INT(data, qqzone_dailystatus);
	DBCREQ_SET_INT(data, qqzone_daily_time);
	DBCREQ_SET_INT(data, qqzone_levelstatus);

	DBCREQ_EXEC;

	return 0;
}

int CDataYellowVip::Del(DataYellowVip &data)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_EXEC;

	return 0;
}
