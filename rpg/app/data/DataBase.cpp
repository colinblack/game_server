#include "DataBase.h"

CDataBase::~CDataBase() {
}

int CDataBase::AddData(const DataBase &data) {
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, register_time);
	DBCREQ_SET_INT(data, login_time);
	DBCREQ_SET_INT(data, offline_time);
	DBCREQ_SET_INT(data, exp);
	DBCREQ_SET_INT(data, guild_id);
	DBCREQ_SET_INT(data, login_days);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, hang);
	DBCREQ_SET_INT(data, hang_power);
	DBCREQ_SET_INT(data, role_num);
	DBCREQ_SET_INT(data, main_role);
	DBCREQ_SET_STR(data, open_id);

	DBCREQ_EXEC;

	return 0;
}

int CDataBase::SetData(const DataBase &data) {
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, register_time);
	DBCREQ_SET_INT(data, login_time);
	DBCREQ_SET_INT(data, offline_time);
	DBCREQ_SET_INT(data, exp);
	DBCREQ_SET_INT(data, guild_id);
	DBCREQ_SET_INT(data, login_days);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, hang);
	DBCREQ_SET_INT(data, hang_power);
	DBCREQ_SET_INT(data, role_num);
	DBCREQ_SET_INT(data, main_role);
	DBCREQ_SET_STR(data, open_id);

	DBCREQ_EXEC;

	return 0;
}

int CDataBase::RepData(const DataBase &data) {
	return -1;
}

int CDataBase::DelData(const DataBase &data) {
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_EXEC;
	return 0;
}

int CDataBase::GetData(uint32_t uid, DataBase &data) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(register_time);
	DBCREQ_NEED(login_time);
	DBCREQ_NEED(offline_time);
	DBCREQ_NEED(exp);
	DBCREQ_NEED(guild_id);
	DBCREQ_NEED(login_days);
	DBCREQ_NEED(level);
	DBCREQ_NEED(hang);
	DBCREQ_NEED(hang_power);
	DBCREQ_NEED(role_num);
	DBCREQ_NEED(main_role);
	DBCREQ_NEED(open_id);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, register_time);
	DBCREQ_GET_INT(data, login_time);
	DBCREQ_GET_INT(data, offline_time);
	DBCREQ_GET_INT(data, exp);
	DBCREQ_GET_INT(data, guild_id);
	DBCREQ_GET_INT(data, login_days);
	DBCREQ_GET_INT(data, level);
	DBCREQ_GET_INT(data, hang);
	DBCREQ_GET_INT(data, hang_power);
	DBCREQ_GET_INT(data, role_num);
	DBCREQ_GET_INT(data, main_role);
	DBCREQ_GET_STR(data, open_id);

	return 0;
}

int CDataBase::GetData(uint32_t uid, vector<DataBase> &datas) {
	return -1;
}
