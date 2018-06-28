
#include "DataBase.h"
#include "DataInc.h"


int CDataBase::Get(DataBase &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(register_platform);
	DBCREQ_NEED(register_time);
	DBCREQ_NEED(last_login_platform);
	DBCREQ_NEED(last_login_time);
	DBCREQ_NEED(login_times);
	DBCREQ_NEED(login_days);
	DBCREQ_NEED(last_active_time);
	DBCREQ_NEED(last_off_time);
	DBCREQ_NEED(forbid_ts);
	DBCREQ_NEED(forbid_reason);
	DBCREQ_NEED(tutorial_stage);
	DBCREQ_NEED(name);
	DBCREQ_NEED(fig);
	DBCREQ_NEED(exp);
	DBCREQ_NEED(level);
	DBCREQ_NEED(acccharge);
	DBCREQ_NEED(viplevel);
	DBCREQ_NEED(first_recharge);
	DBCREQ_NEED(alliance_id);
	DBCREQ_NEED(cash);
	DBCREQ_NEED(coin);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, register_platform);
	DBCREQ_GET_INT(data, register_time);
	DBCREQ_GET_INT(data, last_login_platform);
	DBCREQ_GET_INT(data, last_login_time);
	DBCREQ_GET_INT(data, login_times);
	DBCREQ_GET_INT(data, login_days);
	DBCREQ_GET_INT(data, last_active_time);
	DBCREQ_GET_INT(data, last_off_time);
	DBCREQ_GET_INT(data, forbid_ts);
	DBCREQ_GET_CHAR(data, forbid_reason, BASE_FORBID_REASON_LEN);
	DBCREQ_GET_INT(data, tutorial_stage);
	DBCREQ_GET_CHAR(data, name, BASE_NAME_LEN);
	DBCREQ_GET_CHAR(data, fig, BASE_FIG_LEN);
	DBCREQ_GET_INT(data, exp);
	DBCREQ_GET_INT(data, level);
	DBCREQ_GET_INT(data, acccharge);
	DBCREQ_GET_INT(data, viplevel);
	DBCREQ_GET_INT(data, cash);
	DBCREQ_GET_INT(data, coin);
	DBCREQ_GET_INT(data, first_recharge);
	DBCREQ_GET_INT(data, alliance_id);

	return 0;
}

int CDataBase::Add(DataBase &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, register_platform);
	DBCREQ_SET_INT(data, register_time);
	DBCREQ_SET_INT(data, last_login_platform);
	DBCREQ_SET_INT(data, last_login_time);
	DBCREQ_SET_INT(data, login_times);
	DBCREQ_SET_INT(data, login_days);
	DBCREQ_SET_INT(data, last_active_time);
	DBCREQ_SET_INT(data, last_off_time);
	DBCREQ_SET_INT(data, forbid_ts);
	DBCREQ_SET_CHAR(data, forbid_reason, BASE_FORBID_REASON_LEN);
	DBCREQ_SET_INT(data, tutorial_stage);
	DBCREQ_SET_CHAR(data, name, BASE_NAME_LEN);
	DBCREQ_SET_CHAR(data, fig, BASE_FIG_LEN);
	DBCREQ_SET_INT(data, exp);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, acccharge);
	DBCREQ_SET_INT(data, viplevel);
	DBCREQ_SET_INT(data, cash);
	DBCREQ_SET_INT(data, coin);
	DBCREQ_SET_INT(data, first_recharge);
	DBCREQ_SET_INT(data, alliance_id);

	DBCREQ_EXEC;
	return 0;
}

int CDataBase::Set(DataBase &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, register_platform);
	DBCREQ_SET_INT(data, register_time);
	DBCREQ_SET_INT(data, last_login_platform);
	DBCREQ_SET_INT(data, last_login_time);
	DBCREQ_SET_INT(data, login_times);
	DBCREQ_SET_INT(data, login_days);
	DBCREQ_SET_INT(data, last_active_time);
	DBCREQ_SET_INT(data, last_off_time);
	DBCREQ_SET_INT(data, forbid_ts);
	DBCREQ_SET_CHAR(data, forbid_reason, BASE_FORBID_REASON_LEN);
	DBCREQ_SET_INT(data, tutorial_stage);
	DBCREQ_SET_CHAR(data, name, BASE_NAME_LEN);
	DBCREQ_SET_CHAR(data, fig, BASE_FIG_LEN);
	DBCREQ_SET_INT(data, exp);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, acccharge);
	DBCREQ_SET_INT(data, viplevel);
	DBCREQ_SET_INT(data, cash);
	DBCREQ_SET_INT(data, coin);
	DBCREQ_SET_INT(data, first_recharge);
	DBCREQ_SET_INT(data, alliance_id);

	DBCREQ_EXEC;
	return 0;
}

int CDataBase::Del(DataBase &data)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_EXEC;
	return 0;
}


