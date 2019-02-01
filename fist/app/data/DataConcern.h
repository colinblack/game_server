/*
 * DataConcern.h
 *
 *  Created on: 2018年8月22日
 *      Author: colin
 */

#ifndef APP_DATA_DATACONCERN_H_
#define APP_DATA_DATACONCERN_H_

#include "Kernel.h"

struct DataConcern
{
	uint32_t uid;
	uint32_t id;
	uint32_t donationTs; //赠送体力标志
	uint32_t battleTs;  //挑战好友标志
	uint32_t battle;	//战斗结果

	DataConcern()
	{
		uid = 0;
		id = 0;
		donationTs = 0;
		battleTs = 0;
		battle = 0;
	}

	void SetMessage(ProtoFriend::RecommendInfo* msg) const
	{
		msg->set_uid(id);
		msg->set_donationts(donationTs);
		msg->set_battlets(battleTs);
		msg->set_battle(battle);
	}

};

class CDataConcern: public DBCBase<DataConcern, DB_CONCERN>
{
public:
	virtual int Get(DataConcern &data)
	{
		DBCREQ_DECLARE(DBC::GetRequest, data.uid);
		DBCREQ_SET_KEY(data.uid);
		DBCREQ_SET_CONDITION(EQ, id, data.id);
		DBCREQ_NEED_BEGIN();
		DBCREQ_NEED(uid);
		DBCREQ_NEED(id);
		DBCREQ_NEED(donationTs);
		DBCREQ_NEED(battleTs);
		DBCREQ_NEED(battle);

		DBCREQ_EXEC;

		DBCREQ_IFNULLROW;
		DBCREQ_IFFETCHROW;
		DBCREQ_GET_BEGIN();
		DBCREQ_GET_INT(data, uid);
		DBCREQ_GET_INT(data, id);
		DBCREQ_GET_INT(data, donationTs);
		DBCREQ_GET_INT(data, battleTs);
		DBCREQ_GET_INT(data, battle);

		return 0;
	}

	virtual int Get(vector<DataConcern> &data)
	{
		if (data.empty())
			return R_ERROR;

		DBCREQ_DECLARE(DBC::GetRequest, data[0].uid);
		DBCREQ_SET_KEY(data[0].uid);
		data.clear();
		DBCREQ_NEED_BEGIN();
		DBCREQ_NEED(uid);
		DBCREQ_NEED(id);
		DBCREQ_NEED(donationTs);
		DBCREQ_NEED(battleTs);
		DBCREQ_NEED(battle);

		DBCREQ_EXEC;

		DBCREQ_ARRAY_GET_BEGIN(data);
		DBCREQ_ARRAY_GET_INT(data, uid);
		DBCREQ_ARRAY_GET_INT(data, id);
		DBCREQ_ARRAY_GET_INT(data, donationTs);
		DBCREQ_ARRAY_GET_INT(data, battleTs);
		DBCREQ_ARRAY_GET_INT(data, battle);
		DBCREQ_ARRAY_GET_END();

		return 0;
	}

	virtual int Add(DataConcern &data)
	{
		DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
		DBCREQ_SET_KEY(data.uid);
		DBCREQ_SET_INT(data, id);
		DBCREQ_SET_INT(data, donationTs);
		DBCREQ_SET_INT(data, battleTs);
		DBCREQ_SET_INT(data, battle);

		DBCREQ_EXEC;

		return 0;
	}

	virtual int Set(DataConcern &data)
	{
		DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
		DBCREQ_SET_KEY(data.uid);
		DBCREQ_SET_CONDITION(EQ, id, data.id);
		DBCREQ_SET_INT(data, id);
		DBCREQ_SET_INT(data, donationTs);
		DBCREQ_SET_INT(data, battleTs);
		DBCREQ_SET_INT(data, battle);

		DBCREQ_EXEC;

		return 0;
	}

	virtual int Del(DataConcern &data)
	{
		DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
		DBCREQ_SET_KEY(data.uid);
		DBCREQ_SET_CONDITION(EQ, id, data.id);

		DBCREQ_EXEC;

		return 0;
	}
};


#endif /* APP_DATA_DATACONCERN_H_ */
