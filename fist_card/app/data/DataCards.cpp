/*
 * DataCards.cpp
 *
 *  Created on: 2018年11月21日
 *      Author: colin
 */

#include "DataCards.h"


 int CDataCards::Get(DataCards &data)
 {
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

    DBCREQ_NEED_BEGIN();
    DBCREQ_NEED(uid);
    DBCREQ_NEED(id);
    DBCREQ_NEED(card_id);
    DBCREQ_NEED(star);

    DBCREQ_EXEC;
    DBCREQ_IFNULLROW;
    DBCREQ_IFFETCHROW;

    DBCREQ_GET_BEGIN();
    DBCREQ_GET_INT(data, uid);
    DBCREQ_GET_INT(data, id);
    DBCREQ_GET_INT(data, card_id);
    DBCREQ_GET_INT(data, star);

    return 0;
 }
 int CDataCards::Get(vector<DataCards>&data)
 {
	if (0 == data.size())
	{
		return R_ERR_PARAM;
	}

	DBCREQ_DECLARE(DBC::GetRequest, data[0].uid);
	DBCREQ_SET_KEY(data[0].uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(card_id);
	DBCREQ_NEED(star);

    data.clear();

    DBCREQ_EXEC;
	DBCREQ_ARRAY_GET_BEGIN(data);
	DBCREQ_ARRAY_GET_INT(data, uid);
	DBCREQ_ARRAY_GET_INT(data, id);
	DBCREQ_ARRAY_GET_INT(data, card_id);
	DBCREQ_ARRAY_GET_INT(data, star);

	DBCREQ_ARRAY_GET_END();

	return 0;
 }
 int CDataCards::Add(DataCards &data)
 {
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

    DBCREQ_SET_INT(data, id);
    DBCREQ_SET_INT(data, card_id);
    DBCREQ_SET_INT(data, star);

    DBCREQ_EXEC;

    return 0;
 }
 int CDataCards::Set(DataCards &data)
 {
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);

    DBCREQ_SET_INT(data, card_id);
    DBCREQ_SET_INT(data, star);

    DBCREQ_EXEC;

    return 0;
 }
 int CDataCards::Del(DataCards &data)
 {
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, id, data.id);
	DBCREQ_EXEC;

	return 0;
 }

