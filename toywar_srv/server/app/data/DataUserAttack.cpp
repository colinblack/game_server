#include "DataUserAttack.h"

int CDataUserAttack::AddUserAttack(DataUserAttack &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);

	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, attack_id);
	DBCREQ_SET_INT(data, opposite_uid);
	DBCREQ_SET_INT(data, opposite_platform);
	DBCREQ_SET_INT(data, defence_baseid);
	DBCREQ_SET_INT(data, type);
	DBCREQ_SET_INT(data, status);
	DBCREQ_SET_INT(data, start_time);
	DBCREQ_EXEC;
	return 0;
}

int CDataUserAttack::SetUserAttacksStatus(unsigned uid, int statusOld, int type, int baseid, int status)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, status, statusOld);
	DBCREQ_SET_CONDITION(EQ, type, type);
	if(baseid != 0)
	{
		DBCREQ_SET_CONDITION(EQ, defence_baseid, baseid);
	}
	DBCREQ_SET_INT_V(status);
	DBCREQ_EXEC;
	return 0;
}

int CDataUserAttack::GetUserAttacksAfter(unsigned uid, unsigned time, vector<DataUserAttack> &datas)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);

	DBCREQ_SET_KEY(uid);
	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(attack_id);
	DBCREQ_NEED(opposite_uid);
	DBCREQ_NEED(opposite_platform);
	DBCREQ_NEED(defence_baseid);
	DBCREQ_NEED(type);
	DBCREQ_NEED(status);
	DBCREQ_NEED(start_time);
	DBCREQ_SET_CONDITION(GT, start_time, time);

	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, attack_id);
	DBCREQ_ARRAY_GET_INT(datas, opposite_uid);
	DBCREQ_ARRAY_GET_INT(datas, opposite_platform);
	DBCREQ_ARRAY_GET_INT(datas, defence_baseid);
	DBCREQ_ARRAY_GET_INT(datas, type);
	DBCREQ_ARRAY_GET_INT(datas, status);
	DBCREQ_ARRAY_GET_INT(datas, start_time);
	DBCREQ_ARRAY_GET_END();

	return 0;
}

int CDataUserAttack::GetUserAttacksCondition(unsigned uid, int status, int type, unsigned baseid, unsigned time, vector<DataUserAttack> &datas)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);

	DBCREQ_SET_KEY(uid);
	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(attack_id);
	DBCREQ_NEED(opposite_uid);
	DBCREQ_NEED(opposite_platform);
	DBCREQ_NEED(defence_baseid);
	DBCREQ_NEED(type);
	DBCREQ_NEED(status);
	DBCREQ_NEED(start_time);
	DBCREQ_SET_CONDITION(EQ, status, status);
	DBCREQ_SET_CONDITION(EQ, type, type);
	if(baseid != 0)
	{
		DBCREQ_SET_CONDITION(EQ, defence_baseid, baseid);
	}
	if(time != 0)
	{
		DBCREQ_SET_CONDITION(GT, start_time, time);
	}

	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, attack_id);
	DBCREQ_ARRAY_GET_INT(datas, opposite_uid);
	DBCREQ_ARRAY_GET_INT(datas, opposite_platform);
	DBCREQ_ARRAY_GET_INT(datas, defence_baseid);
	DBCREQ_ARRAY_GET_INT(datas, type);
	DBCREQ_ARRAY_GET_INT(datas, status);
	DBCREQ_ARRAY_GET_INT(datas, start_time);
	DBCREQ_ARRAY_GET_END();

	return 0;
}

int CDataUserAttack::GetUserAttacksCondition(unsigned uid, unsigned time, int type, unsigned baseid, vector<DataUserAttack> &datas)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);

	DBCREQ_SET_KEY(uid);
	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(attack_id);
	DBCREQ_NEED(opposite_uid);
	DBCREQ_NEED(opposite_platform);
	DBCREQ_NEED(defence_baseid);
	DBCREQ_NEED(type);
	DBCREQ_NEED(status);
	DBCREQ_NEED(start_time);
	DBCREQ_SET_CONDITION(GT, start_time, time);
	DBCREQ_SET_CONDITION(EQ, type, type);
	if(baseid != 0)
	{
		DBCREQ_SET_CONDITION(EQ, defence_baseid, baseid);
	}

	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, attack_id);
	DBCREQ_ARRAY_GET_INT(datas, opposite_uid);
	DBCREQ_ARRAY_GET_INT(datas, opposite_platform);
	DBCREQ_ARRAY_GET_INT(datas, defence_baseid);
	DBCREQ_ARRAY_GET_INT(datas, type);
	DBCREQ_ARRAY_GET_INT(datas, status);
	DBCREQ_ARRAY_GET_INT(datas, start_time);
	DBCREQ_ARRAY_GET_END();

	return 0;
}

int CDataUserAttack::GetUserAttacksCount(unsigned uid, unsigned time, int type, unsigned baseid, unsigned opposite_uid, int &count)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);

	DBCREQ_SET_KEY(uid);
	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(attack_id);
	DBCREQ_SET_CONDITION(GT, start_time, time);
	DBCREQ_SET_CONDITION(EQ, type, type);
	if(baseid != 0)
	{
		DBCREQ_SET_CONDITION(EQ, defence_baseid, baseid);
	}
	if(opposite_uid != 0)
	{
		DBCREQ_SET_CONDITION(EQ, opposite_uid, opposite_uid);
	}

	DBCREQ_EXEC;

	count = m_dbcret.TotalRows();

	return 0;
}

