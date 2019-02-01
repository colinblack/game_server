/*
 * DataAlliance.h
 *
 *  Created on: 2018年4月19日
 *      Author: Ralf
 */

#ifndef CGIAPP_DATA_DATAALLIANCE_H_
#define CGIAPP_DATA_DATAALLIANCE_H_

#include "Kernel.h"


struct DataAlliance
{

	uint32_t alliance_id;  //商会uid
	uint32_t create_uid;   //创建者uid
	uint32_t create_time; /*创建时间*/
	uint32_t qqgroup;  //qq群号
	uint32_t active_ts; // 活跃时间戳
	uint32_t race_ts;	// 竞赛时间戳
	uint32_t race_point; // 竞赛积分
	uint32_t race_total_point;	// 竞赛历史积分
	int8_t flag;   /*商会标志*/
	int8_t apply_type;  //入会申请类型.0-无需申请 1-申请进入 2-仅接受邀请进入
	int8_t apply_level_limit;  //入会等级限制
	int8_t race_level;	// 竞赛等级


	char name[DataAlliance_name_LENG];   /*商会名称*/
	char description[DataAlliance_description_LENG];   //商会描述
	char create_username[BASE_NAME_LEN];   //创建者名称

	DataAlliance()
	{
		alliance_id = 0;
		memset(name, 0, sizeof(name));
		flag = 0;
		create_uid = 0;
		create_time = 0;
		apply_type = 0;
		apply_level_limit = 0;
		race_level = 0;
		qqgroup = 0;
		active_ts = 0;
		race_ts = 0;
		race_point = 0;
		race_total_point = 0;
		memset(description, 0, sizeof(description));
		memset(create_username, 0, sizeof(create_username));
	}

};

class CDataAlliance: public CDataBaseDBC
{
public:
	CDataAlliance(int table = DB_ALLIANCE) : CDataBaseDBC(table) {}

	virtual int Get(DataAlliance &data)
	{
		DBCREQ_DECLARE(DBC::GetRequest, data.alliance_id);
		DBCREQ_SET_KEY(data.alliance_id);

		DBCREQ_NEED_BEGIN();
		DBCREQ_NEED(alliance_id);
		DBCREQ_NEED(name);
		DBCREQ_NEED(flag);
		DBCREQ_NEED(create_uid);
		DBCREQ_NEED(create_time);
		DBCREQ_NEED(apply_type);
		DBCREQ_NEED(apply_level_limit);
		DBCREQ_NEED(qqgroup);
		DBCREQ_NEED(description);
		DBCREQ_NEED(create_username);
		DBCREQ_NEED(race_level);
		DBCREQ_NEED(active_ts);
		DBCREQ_NEED(race_ts);
		DBCREQ_NEED(race_point);
		DBCREQ_NEED(race_total_point);

		DBCREQ_EXEC;

		DBCREQ_IFNULLROW;
		DBCREQ_IFFETCHROW;
		DBCREQ_GET_BEGIN();
		DBCREQ_GET_INT(data, alliance_id);
		DBCREQ_GET_CHAR(data, name, DataAlliance_name_LENG);
		DBCREQ_GET_INT(data, flag);
		DBCREQ_GET_INT(data, create_uid);
		DBCREQ_GET_INT(data, create_time);
		DBCREQ_GET_INT(data, apply_type);
		DBCREQ_GET_INT(data, apply_level_limit);
		DBCREQ_GET_INT(data, qqgroup);
		DBCREQ_GET_CHAR(data, description, DataAlliance_description_LENG);
		DBCREQ_GET_CHAR(data, create_username, BASE_NAME_LEN);
		DBCREQ_GET_INT(data, race_level);
		DBCREQ_GET_INT(data, active_ts);
		DBCREQ_GET_INT(data, race_ts);
		DBCREQ_GET_INT(data, race_point);
		DBCREQ_GET_INT(data, race_total_point);

		return 0;
	}

	virtual int Add(DataAlliance &data)
	{
		DBCREQ_DECLARE(DBC::InsertRequest, data.alliance_id);
		DBCREQ_SET_KEY(data.alliance_id);

		DBCREQ_SET_CHAR(data, name, DataAlliance_name_LENG);
		DBCREQ_SET_INT(data, flag);
		DBCREQ_SET_INT(data, create_uid);
		DBCREQ_SET_INT(data, create_time);
		DBCREQ_SET_INT(data, apply_type);
		DBCREQ_SET_INT(data, apply_level_limit);
		DBCREQ_SET_INT(data, qqgroup);
		DBCREQ_SET_INT(data, race_level);
		DBCREQ_SET_INT(data, active_ts);
		DBCREQ_SET_INT(data, race_ts);
		DBCREQ_SET_INT(data, race_point);
		DBCREQ_SET_INT(data, race_total_point);
		DBCREQ_SET_CHAR(data, description, DataAlliance_description_LENG);
		DBCREQ_SET_CHAR(data, create_username, BASE_NAME_LEN);

		DBCREQ_EXEC;

		return 0;
	}

	virtual int Set(DataAlliance &data)
	{
		DBCREQ_DECLARE(DBC::UpdateRequest, data.alliance_id);
		DBCREQ_SET_KEY(data.alliance_id);

		DBCREQ_SET_CHAR(data, name, DataAlliance_name_LENG);
		DBCREQ_SET_INT(data, flag);
		DBCREQ_SET_INT(data, create_uid);
		DBCREQ_SET_INT(data, create_time);
		DBCREQ_SET_INT(data, apply_type);
		DBCREQ_SET_INT(data, apply_level_limit);
		DBCREQ_SET_INT(data, qqgroup);
		DBCREQ_SET_INT(data, race_level);
		DBCREQ_SET_INT(data, active_ts);
		DBCREQ_SET_INT(data, race_ts);
		DBCREQ_SET_INT(data, race_point);
		DBCREQ_SET_INT(data, race_total_point);
		DBCREQ_SET_CHAR(data, description, DataAlliance_description_LENG);
		DBCREQ_SET_CHAR(data, create_username, BASE_NAME_LEN);

		DBCREQ_EXEC;

		return 0;
	}

	virtual int Del(DataAlliance &data)
	{
		DBCREQ_DECLARE(DBC::DeleteRequest, data.alliance_id);
		DBCREQ_SET_KEY(data.alliance_id);

		DBCREQ_EXEC;

		return 0;
	}
};


struct DataAllianceMember
{
	uint32_t alliance_id;  //商会id
	uint32_t id;  //用户id
	uint32_t authority;  //权限
	uint32_t helptimes; //帮助次数
	uint32_t userlevel;  //用户等级

	uint8_t position; //成员职位
	char username[BASE_NAME_LEN];   //创建者名称

	DataAllianceMember()
	{
		alliance_id = 0;
		id = 0;
		authority = 0;
		helptimes = 0;
		position = 0;
		userlevel = 0;

		memset(username, 0, sizeof(username));
	}
};

class CDataAllianceMember: public CDataBaseDBC
{
public:
	CDataAllianceMember(int table = DB_ALLIANCE_MEMBER) : CDataBaseDBC(table) {}

	virtual int Get(DataAllianceMember &data)
	{
		DBCREQ_DECLARE(DBC::GetRequest, data.alliance_id);
		DBCREQ_SET_KEY(data.alliance_id);
		DBCREQ_SET_CONDITION(EQ, id, data.id);

		DBCREQ_NEED_BEGIN();
		DBCREQ_NEED(alliance_id);
		DBCREQ_NEED(id);
		DBCREQ_NEED(position);
		DBCREQ_NEED(authority);
		DBCREQ_NEED(helptimes);
		DBCREQ_NEED(userlevel);
		DBCREQ_NEED(username);

		DBCREQ_EXEC;

		DBCREQ_IFNULLROW;
		DBCREQ_IFFETCHROW;
		DBCREQ_GET_BEGIN();
		DBCREQ_GET_INT(data, alliance_id);
		DBCREQ_GET_INT(data, id);
		DBCREQ_GET_INT(data, position);
		DBCREQ_GET_INT(data, authority);
		DBCREQ_GET_INT(data, helptimes);
		DBCREQ_GET_INT(data, userlevel);
		DBCREQ_GET_CHAR(data, username, BASE_NAME_LEN);

		return 0;
	}

	virtual int Get(vector<DataAllianceMember> &data)
	{
		if (data.empty())
			return R_ERROR;
		DBCREQ_DECLARE(DBC::GetRequest, data[0].alliance_id);
		DBCREQ_SET_KEY(data[0].alliance_id);

		data.clear();
		DBCREQ_NEED_BEGIN();
		DBCREQ_NEED(alliance_id);
		DBCREQ_NEED(id);
		DBCREQ_NEED(position);
		DBCREQ_NEED(authority);
		DBCREQ_NEED(helptimes);
		DBCREQ_NEED(userlevel);
		DBCREQ_NEED(username);

		DBCREQ_EXEC;

		DBCREQ_ARRAY_GET_BEGIN(data);
		DBCREQ_ARRAY_GET_INT(data, alliance_id);
		DBCREQ_ARRAY_GET_INT(data, id);
		DBCREQ_ARRAY_GET_INT(data, position);
		DBCREQ_ARRAY_GET_INT(data, authority);
		DBCREQ_ARRAY_GET_INT(data, helptimes);
		DBCREQ_ARRAY_GET_INT(data, userlevel);
		DBCREQ_ARRAY_GET_CHAR(data, username, BASE_NAME_LEN);
		DBCREQ_ARRAY_GET_END();

		return 0;
	}

	virtual int Add(DataAllianceMember &data)
	{
		DBCREQ_DECLARE(DBC::InsertRequest, data.alliance_id);
		DBCREQ_SET_KEY(data.alliance_id);
		DBCREQ_SET_INT(data, id);
		DBCREQ_SET_INT(data, position);
		DBCREQ_SET_INT(data, authority);
		DBCREQ_SET_INT(data, helptimes);
		DBCREQ_SET_INT(data, userlevel);
		DBCREQ_SET_CHAR(data, username, BASE_NAME_LEN);

		DBCREQ_EXEC;

		return 0;
	}

	virtual int Set(DataAllianceMember &data)
	{
		DBCREQ_DECLARE(DBC::UpdateRequest, data.alliance_id);
		DBCREQ_SET_KEY(data.alliance_id);
		DBCREQ_SET_CONDITION(EQ, id, data.id);
		DBCREQ_SET_INT(data, id);
		DBCREQ_SET_INT(data, position);
		DBCREQ_SET_INT(data, authority);
		DBCREQ_SET_INT(data, helptimes);
		DBCREQ_SET_INT(data, userlevel);
		DBCREQ_SET_CHAR(data, username, BASE_NAME_LEN);

		DBCREQ_EXEC;

		return 0;
	}

	virtual int Del(DataAllianceMember &data)
	{
		DBCREQ_DECLARE(DBC::DeleteRequest, data.alliance_id);
		DBCREQ_SET_KEY(data.alliance_id);
		DBCREQ_SET_CONDITION(EQ, id, data.id);

		DBCREQ_EXEC;

		return 0;
	}
};

#endif /* CGIAPP_DATA_DATAALLIANCE_H_ */
