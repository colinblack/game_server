
#include "DataBase.h"
#include "DataInc.h"

int CDataBase::Get(DataBase &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(name);
	DBCREQ_NEED(fig);
	DBCREQ_NEED(level);
	DBCREQ_NEED(cash);
	DBCREQ_NEED(blue_info);
	DBCREQ_NEED(flag);
	DBCREQ_NEED(prosperity);
	DBCREQ_NEED(accthumbsup);
	DBCREQ_NEED(viplevel);
	DBCREQ_NEED(register_time);
	DBCREQ_NEED(last_login_time);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_CHAR(data, name, BASE_NAME_LEN);
	DBCREQ_GET_CHAR(data, fig, BASE_FIG_LEN);
	DBCREQ_GET_INT(data, level);
	DBCREQ_GET_INT(data, cash);
	DBCREQ_GET_INT(data, blue_info);
	DBCREQ_GET_INT(data, flag);
	DBCREQ_GET_INT(data, prosperity);
	DBCREQ_GET_INT(data, accthumbsup);
	DBCREQ_GET_INT(data, viplevel);
	DBCREQ_GET_INT(data, register_time);
	DBCREQ_GET_INT(data, last_login_time);


	return 0;
}

int CDataBase::Add(DataBase &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CHAR(data, name, BASE_NAME_LEN);
	DBCREQ_SET_CHAR(data, fig, BASE_FIG_LEN);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, cash);
	DBCREQ_SET_INT(data, blue_info);
	DBCREQ_SET_INT(data, flag);
	DBCREQ_SET_INT(data, prosperity);
	DBCREQ_SET_INT(data, accthumbsup);
	DBCREQ_SET_INT(data, viplevel);
	DBCREQ_SET_INT(data, register_time);
	DBCREQ_SET_INT(data, last_login_time);
	DBCREQ_EXEC;
	return 0;
}

int CDataBase::Set(DataBase &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CHAR(data, name, BASE_NAME_LEN);
	DBCREQ_SET_CHAR(data, fig, BASE_FIG_LEN);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, cash);
	DBCREQ_SET_INT(data, blue_info);
	DBCREQ_SET_INT(data, flag);
	DBCREQ_SET_INT(data, prosperity);
	DBCREQ_SET_INT(data, accthumbsup);
	DBCREQ_SET_INT(data, viplevel);
	DBCREQ_SET_INT(data, register_time);
	DBCREQ_SET_INT(data, last_login_time);
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


