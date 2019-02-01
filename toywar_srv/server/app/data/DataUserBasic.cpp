/*
 * DataUserBasic.cpp
 *
 *  Created on: 2011-7-8
 *      Author: dada
 */

#include "DataUserBasic.h"

int CDataUserBasic::AddUser(const DataUserBasic &user)
{
	DBCREQ_DECLARE(DBC::InsertRequest, user.uid);
	DBCREQ_SET_KEY(user.uid);
	DBCREQ_SET_INT(user, platform);
	DBCREQ_SET_INT(user, is_register_platform);
	DBCREQ_SET_STR(user, open_id);
	DBCREQ_SET_STR(user, name);
	DBCREQ_SET_INT(user, gender);
	DBCREQ_SET_STR(user, nation);
	DBCREQ_SET_STR(user, province);
	DBCREQ_SET_STR(user, city);
	DBCREQ_SET_STR(user, figure_url);
	DBCREQ_SET_INT(user, vip_type);
	DBCREQ_SET_INT(user, vip_level);
	DBCREQ_SET_STR(user, extra_data);
	DBCREQ_EXEC;
	return 0;
}

int CDataUserBasic::SetUser(const DataUserBasic &user)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, user.uid);
	DBCREQ_SET_KEY(user.uid);
	DBCREQ_SET_CONDITION(EQ, platform, user.platform);
	DBCREQ_SET_INT(user, is_register_platform);
	DBCREQ_SET_STR(user, open_id);
	DBCREQ_SET_STR(user, name);
	DBCREQ_SET_INT(user, gender);
	DBCREQ_SET_STR(user, nation);
	DBCREQ_SET_STR(user, province);
	DBCREQ_SET_STR(user, city);
	DBCREQ_SET_STR(user, figure_url);
	DBCREQ_SET_INT(user, vip_type);
	DBCREQ_SET_INT(user, vip_level);
	DBCREQ_SET_STR(user, extra_data);
	DBCREQ_EXEC;
	return 0;
}

int CDataUserBasic::GetUser(unsigned uid, int platform, DataUserBasic &user)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, platform, platform);
	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(platform);
	DBCREQ_NEED(is_register_platform);
	DBCREQ_NEED(open_id);
	DBCREQ_NEED(name);
	DBCREQ_NEED(gender);
	DBCREQ_NEED(nation);
	DBCREQ_NEED(province);
	DBCREQ_NEED(city);
	DBCREQ_NEED(figure_url);
	DBCREQ_NEED(vip_type);
	DBCREQ_NEED(vip_level);
	DBCREQ_NEED(extra_data);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(user, uid);
	DBCREQ_GET_INT(user, platform);
	DBCREQ_GET_INT(user, is_register_platform);
	DBCREQ_GET_STR(user, open_id);
	DBCREQ_GET_STR(user, name);
	DBCREQ_GET_INT(user, gender);
	DBCREQ_GET_STR(user, nation);
	DBCREQ_GET_STR(user, province);
	DBCREQ_GET_STR(user, city);
	DBCREQ_GET_STR(user, figure_url);
	DBCREQ_GET_INT(user, vip_type);
	DBCREQ_GET_INT(user, vip_level);
	DBCREQ_GET_STR(user, extra_data);

	return 0;
}

int CDataUserBasic::GetUserRegister(unsigned uid, DataUserBasic &user)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, is_register_platform, True);
	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(platform);
	DBCREQ_NEED(is_register_platform);
	DBCREQ_NEED(open_id);
	DBCREQ_NEED(name);
	DBCREQ_NEED(gender);
	DBCREQ_NEED(nation);
	DBCREQ_NEED(province);
	DBCREQ_NEED(city);
	DBCREQ_NEED(figure_url);
	DBCREQ_NEED(vip_type);
	DBCREQ_NEED(vip_level);
	DBCREQ_NEED(extra_data);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(user, uid);
	DBCREQ_GET_INT(user, platform);
	DBCREQ_GET_INT(user, is_register_platform);
	DBCREQ_GET_STR(user, open_id);
	DBCREQ_GET_STR(user, name);
	DBCREQ_GET_INT(user, gender);
	DBCREQ_GET_STR(user, nation);
	DBCREQ_GET_STR(user, province);
	DBCREQ_GET_STR(user, city);
	DBCREQ_GET_STR(user, figure_url);
	DBCREQ_GET_INT(user, vip_type);
	DBCREQ_GET_INT(user, vip_level);
	DBCREQ_GET_STR(user, extra_data);

	return 0;
}

int CDataUserBasic::GetUserAll(unsigned uid, vector<DataUserBasic> &users)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(platform);
	DBCREQ_NEED(is_register_platform);
	DBCREQ_NEED(open_id);
	DBCREQ_NEED(name);
	DBCREQ_NEED(gender);
	DBCREQ_NEED(nation);
	DBCREQ_NEED(province);
	DBCREQ_NEED(city);
	DBCREQ_NEED(figure_url);
	DBCREQ_NEED(vip_type);
	DBCREQ_NEED(vip_level);
	DBCREQ_NEED(extra_data);

	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(users);
	DBCREQ_ARRAY_GET_INT(users, uid);
	DBCREQ_ARRAY_GET_INT(users, platform);
	DBCREQ_ARRAY_GET_INT(users, is_register_platform);
	DBCREQ_ARRAY_GET_STR(users, open_id);
	DBCREQ_ARRAY_GET_STR(users, name);
	DBCREQ_ARRAY_GET_INT(users, gender);
	DBCREQ_ARRAY_GET_STR(users, nation);
	DBCREQ_ARRAY_GET_STR(users, province);
	DBCREQ_ARRAY_GET_STR(users, city);
	DBCREQ_ARRAY_GET_STR(users, figure_url);
	DBCREQ_ARRAY_GET_INT(users, vip_type);
	DBCREQ_ARRAY_GET_INT(users, vip_level);
	DBCREQ_ARRAY_GET_STR(users, extra_data);
	DBCREQ_ARRAY_GET_END();

	return 0;
}

int CDataUserBasic::RemoveUser(unsigned uid)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_EXEC;
	return 0;
}

