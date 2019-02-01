/*
 * DataMartialClub.h
 *
 *  Created on: 2018年8月30日
 *      Author: colin
 */

#ifndef APP_DATA_DATAMARTIALCLUB_H_
#define APP_DATA_DATAMARTIALCLUB_H_

#include "Kernel.h"

struct DataMartialClub
{
	uint32_t uid;		//玩家id
	uint32_t id;		//武馆星级
	uint32_t hero_size; //武馆中已有英雄数量
	uint32_t level;		//武馆等级
	uint32_t use_props[MAX_BATTLE_PROPS]; //使用过的道具
	uint32_t coin;		//金币收益
	uint32_t props[MARTIAL_CLUB_REAP_PROPS]; //道具收益
	uint32_t props_ts;	//道具产生时戳
	char slots[MARTIAL_CLUB_MAX_SIZE];
	uint32_t win_count; //胜利次数
	uint32_t next_ts;	//下次可升级的时间
	uint32_t protect_ts; //踢馆保护时戳
	char 	martial_name[BASE_NAME_LEN];	//武馆名称
	uint32_t income_start_ts;			//收益开始时戳
	uint32_t ini_income;	//初始收益标志0:未生成  1:生成

	DataMartialClub()
	{
		uid = 0;
		id = 0;
		hero_size = 0;
		level = 0;
		coin = 0;
		props_ts = 0;
		win_count = 0;
		next_ts = 0;
		protect_ts = 0;
		income_start_ts = 0;
		ini_income = 0;

		memset(props, 0, sizeof(props));
		memset(use_props, 0, sizeof(use_props));
		memset(slots, 0, sizeof(slots));
		memset(martial_name, 0, sizeof(martial_name));
	}

	void SetMessage(ProtoMartialClub::MartialClubInfo *msg) const
	{
		msg->set_uid(uid);
		msg->set_grade(id);
		msg->set_level(level);
		msg->set_nextts(next_ts);
		msg->set_protectts(protect_ts);
		msg->set_martialname(martial_name);
		msg->set_incomestartts(income_start_ts);
		msg->set_coins(coin);
	}

	void SetMessage(map<unsigned, unsigned>& index, ProtoBattle::ProtoCSMartialClubBattleResp* msg)
	{
		msg->set_othuid(uid);
		msg->set_othmgrade(id);
		msg->set_othprotectts(protect_ts);
		msg->set_othcoins(coin);

		for(auto& e : index)
		{
			auto prop = msg->add_othprops();
			prop->set_id(e.first);
			prop->set_count(props[e.second]);
		}
	}
};

class CDataMartialClub : public DBCBase<DataMartialClub, DB_MARTIAL_CLUB>
{
public:
	virtual int Get(DataMartialClub &data)
	{
		DBCREQ_DECLARE(DBC::GetRequest, data.uid);
		DBCREQ_SET_KEY(data.uid);
		DBCREQ_SET_CONDITION(EQ, id, data.id);

		DBCREQ_NEED_BEGIN();
		DBCREQ_NEED(uid);
		DBCREQ_NEED(id);
		DBCREQ_NEED(hero_size);
		DBCREQ_NEED(level);
		DBCREQ_NEED(use_props);
		DBCREQ_NEED(coin);
		DBCREQ_NEED(props);
		DBCREQ_NEED(props_ts);
		DBCREQ_NEED(slots);
		DBCREQ_NEED(win_count);
		DBCREQ_NEED(next_ts);
		DBCREQ_NEED(protect_ts);
		DBCREQ_NEED(martial_name);
		DBCREQ_NEED(income_start_ts);
		DBCREQ_NEED(ini_income);

		DBCREQ_EXEC;
		DBCREQ_IFNULLROW;
		DBCREQ_IFFETCHROW;

		DBCREQ_GET_BEGIN();
		DBCREQ_GET_INT(data, uid);
		DBCREQ_GET_INT(data, id);
		DBCREQ_GET_INT(data, hero_size);
		DBCREQ_GET_INT(data, level);
		DBCREQ_GET_BIN_SIZE(data, use_props);
		DBCREQ_GET_INT(data, coin);
		DBCREQ_GET_BIN_SIZE(data, props);
		DBCREQ_GET_INT(data, props_ts);
		DBCREQ_GET_BINARY(data, slots, MARTIAL_CLUB_MAX_SIZE);
		DBCREQ_GET_INT(data, win_count);
		DBCREQ_GET_INT(data, next_ts);
		DBCREQ_GET_INT(data, protect_ts);
		DBCREQ_GET_BINARY(data, martial_name, BASE_NAME_LEN);
		DBCREQ_GET_INT(data, income_start_ts);
		DBCREQ_GET_INT(data, ini_income);

		return 0;
	}

	virtual int Get(vector<DataMartialClub> &data)
	{
		if (data.empty())
			return R_ERROR;

		DBCREQ_DECLARE(DBC::GetRequest, data[0].uid);
		DBCREQ_SET_KEY(data[0].uid);

		DBCREQ_NEED_BEGIN();
		DBCREQ_NEED(uid);
		DBCREQ_NEED(id);
		DBCREQ_NEED(hero_size);
		DBCREQ_NEED(level);
		DBCREQ_NEED(use_props);
		DBCREQ_NEED(coin);
		DBCREQ_NEED(props);
		DBCREQ_NEED(props_ts);
		DBCREQ_NEED(slots);
		DBCREQ_NEED(win_count);
		DBCREQ_NEED(next_ts);
		DBCREQ_NEED(protect_ts);
		DBCREQ_NEED(martial_name);
		DBCREQ_NEED(income_start_ts);
		DBCREQ_NEED(ini_income);

		data.clear();

		DBCREQ_EXEC;

		DBCREQ_ARRAY_GET_BEGIN(data);
		DBCREQ_ARRAY_GET_INT(data, uid);
		DBCREQ_ARRAY_GET_INT(data, id);
		DBCREQ_ARRAY_GET_INT(data, hero_size);
		DBCREQ_ARRAY_GET_INT(data, level);
		DBCREQ_ARRAY_GET_BIN_SIZE(data, use_props);
		DBCREQ_ARRAY_GET_INT(data, coin);
		DBCREQ_ARRAY_GET_BIN_SIZE(data, props);
		DBCREQ_ARRAY_GET_INT(data, props_ts);
		DBCREQ_ARRAY_GET_BINARY(data, slots, MARTIAL_CLUB_MAX_SIZE);
		DBCREQ_ARRAY_GET_INT(data, win_count);
		DBCREQ_ARRAY_GET_INT(data, next_ts);
		DBCREQ_ARRAY_GET_INT(data, protect_ts);
		DBCREQ_ARRAY_GET_BINARY(data, martial_name, BASE_NAME_LEN);
		DBCREQ_ARRAY_GET_INT(data, income_start_ts);
		DBCREQ_ARRAY_GET_INT(data, ini_income);

		DBCREQ_ARRAY_GET_END();

		return 0;
	}

	virtual int Add(DataMartialClub &data)
	{
		DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
		DBCREQ_SET_KEY(data.uid);
		DBCREQ_SET_INT(data, id);
		DBCREQ_SET_INT(data, hero_size);
		DBCREQ_SET_INT(data, level);
		DBCREQ_SET_BIN_SIZE(data, use_props);
		DBCREQ_SET_INT(data, coin);
		DBCREQ_SET_BIN_SIZE(data, props);
		DBCREQ_SET_INT(data, props_ts);
		DBCREQ_SET_BINARY(data, slots, MARTIAL_CLUB_MAX_SIZE);
		DBCREQ_SET_INT(data, win_count);
		DBCREQ_SET_INT(data, next_ts);
		DBCREQ_SET_INT(data, protect_ts);
		DBCREQ_SET_BINARY(data, martial_name, BASE_NAME_LEN);
		DBCREQ_SET_INT(data, income_start_ts);
		DBCREQ_SET_INT(data, ini_income);

		DBCREQ_EXEC;

		return 0;
	}

	virtual int Set(DataMartialClub &data)
	{
		DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
		DBCREQ_SET_KEY(data.uid);
		DBCREQ_SET_CONDITION(EQ, id, data.id);
		DBCREQ_SET_INT(data, hero_size);
		DBCREQ_SET_INT(data, level);
		DBCREQ_SET_BIN_SIZE(data, use_props);
		DBCREQ_SET_INT(data, coin);
		DBCREQ_SET_BIN_SIZE(data, props);
		DBCREQ_SET_INT(data, props_ts);
		DBCREQ_SET_BINARY(data, slots, MARTIAL_CLUB_MAX_SIZE);
		DBCREQ_SET_INT(data, win_count);
		DBCREQ_SET_INT(data, next_ts);
		DBCREQ_SET_INT(data, protect_ts);
		DBCREQ_SET_BINARY(data, martial_name, BASE_NAME_LEN);
		DBCREQ_SET_INT(data, income_start_ts);
		DBCREQ_SET_INT(data, ini_income);


		DBCREQ_EXEC;

		return 0;
	}

	virtual int Del(DataMartialClub &data)
	{
		DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
		DBCREQ_SET_KEY(data.uid);
		DBCREQ_SET_CONDITION(EQ, id, data.id);

		DBCREQ_EXEC;

		return 0;
	}

};


#endif /* APP_DATA_DATAMARTIALCLUB_H_ */
