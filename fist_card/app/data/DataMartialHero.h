/*
 * DataMartialHero.h
 *
 *  Created on: 2018年8月30日
 *      Author: colin
 */

#ifndef APP_DATA_DATAMARTIALHERO_H_
#define APP_DATA_DATAMARTIALHERO_H_

#include "Kernel.h"

struct DataMartialHero
{
	uint32_t uid;
	uint32_t id;
	uint32_t owner_uid;  //英雄所属玩家id
	char name[BASE_NAME_LEN];//名字
	char fig[BASE_FIG_LEN];//头像ur
	uint32_t club_grade; //所属武馆星级
	uint32_t owner_level; //英雄所属玩家等级
	uint32_t heroid;	//英雄id
	uint32_t hp;	//生命
	uint32_t att;	//攻击
	uint32_t def;	//防御
	uint32_t crit;	//暴击
	uint32_t acrit;	//抗暴击
	uint32_t dodge; //闪避
	uint32_t adodge; //命中
	uint32_t critt;  //暴击倍数
	uint32_t speed; //先手
	double	 battlePower; //战力
	char skill[HERO_SKILL_LENGTH];  //技能等级

	DataMartialHero()
	{
		uid = 0;
		id = 0;
		owner_uid = 0;
		club_grade = 0;
		owner_level = 0;
		heroid = 0;
		hp  = 0;
		att = 0;
		def = 0;
		crit   = 0;
		acrit  = 0;
		dodge  = 0;
		adodge = 0;
		critt  = 0;
		speed  = 0;

		battlePower = 0;
		memset(name, 0, sizeof(name));
		memset(fig, 0, sizeof(fig));
		memset(skill, 0, sizeof(skill));
	}

	void SetMessage(ProtoMartialClub::MartialHeroInfo *msg) const
	{
		msg->mutable_hero()->set_heroid(heroid);
		msg->mutable_hero()->set_slot(id);

		msg->mutable_user()->set_uid(owner_uid);
		msg->mutable_user()->set_name(name);
		msg->mutable_user()->set_fig(fig);
		msg->mutable_user()->set_level(owner_level);
		msg->mutable_user()->set_grade(club_grade);


	}
};

class CDataMartialHero : public DBCBase<DataMartialHero, DB_MARTIAL_HERO>
{
public:
	virtual int Get(DataMartialHero &data)
	{
		DBCREQ_DECLARE(DBC::GetRequest, data.uid);
		DBCREQ_SET_KEY(data.uid);
		DBCREQ_SET_CONDITION(EQ, id, data.id);

		DBCREQ_NEED_BEGIN();
		DBCREQ_NEED(uid);
		DBCREQ_NEED(id);
		DBCREQ_NEED(owner_uid);
		DBCREQ_NEED(name);
		DBCREQ_NEED(fig);
		DBCREQ_NEED(club_grade);
		DBCREQ_NEED(owner_level);
		DBCREQ_NEED(heroid);
		DBCREQ_NEED(hp);
		DBCREQ_NEED(att);
		DBCREQ_NEED(def);
		DBCREQ_NEED(crit);
		DBCREQ_NEED(acrit);
		DBCREQ_NEED(dodge);
		DBCREQ_NEED(adodge);
		DBCREQ_NEED(critt);
		DBCREQ_NEED(speed);
		DBCREQ_NEED(skill);

		DBCREQ_EXEC;
		DBCREQ_IFNULLROW;
		DBCREQ_IFFETCHROW;

		DBCREQ_GET_BEGIN();
		DBCREQ_GET_INT(data, uid);
		DBCREQ_GET_INT(data, id);
		DBCREQ_GET_INT(data, owner_uid);
		DBCREQ_GET_CHAR(data, name, BASE_NAME_LEN);
		DBCREQ_GET_CHAR(data, fig, BASE_FIG_LEN);
		DBCREQ_GET_INT(data, club_grade);
		DBCREQ_GET_INT(data, owner_level);
		DBCREQ_GET_INT(data, heroid);
		DBCREQ_GET_INT(data, hp);
		DBCREQ_GET_INT(data, att);
		DBCREQ_GET_INT(data, def);
		DBCREQ_GET_INT(data, crit);
		DBCREQ_GET_INT(data, acrit);
		DBCREQ_GET_INT(data, dodge);
		DBCREQ_GET_INT(data, adodge);
		DBCREQ_GET_INT(data, critt);
		DBCREQ_GET_INT(data, speed);
	    DBCREQ_GET_BINARY(data, skill, HERO_SKILL_LENGTH)

		return 0;
	}

	virtual int Get(vector<DataMartialHero> &data)
	{
		if (data.empty())
			return R_ERROR;

		DBCREQ_DECLARE(DBC::GetRequest, data[0].uid);
		DBCREQ_SET_KEY(data[0].uid);

		DBCREQ_NEED_BEGIN();
		DBCREQ_NEED(uid);
		DBCREQ_NEED(id);
		DBCREQ_NEED(owner_uid);
		DBCREQ_NEED(name);
		DBCREQ_NEED(fig);
		DBCREQ_NEED(club_grade);
		DBCREQ_NEED(owner_level);
		DBCREQ_NEED(heroid);
		DBCREQ_NEED(hp);
		DBCREQ_NEED(att);
		DBCREQ_NEED(def);
		DBCREQ_NEED(crit);
		DBCREQ_NEED(acrit);
		DBCREQ_NEED(dodge);
		DBCREQ_NEED(adodge);
		DBCREQ_NEED(critt);
		DBCREQ_NEED(speed);
		DBCREQ_NEED(skill);

		data.clear();

		DBCREQ_EXEC;

		DBCREQ_ARRAY_GET_BEGIN(data);
		DBCREQ_ARRAY_GET_INT(data, uid);
		DBCREQ_ARRAY_GET_INT(data, id);
		DBCREQ_ARRAY_GET_INT(data, owner_uid);
		DBCREQ_ARRAY_GET_CHAR(data, name, BASE_NAME_LEN);
		DBCREQ_ARRAY_GET_CHAR(data, fig, BASE_FIG_LEN);
		DBCREQ_ARRAY_GET_INT(data, club_grade);
		DBCREQ_ARRAY_GET_INT(data, owner_level);
		DBCREQ_ARRAY_GET_INT(data, heroid);
		DBCREQ_ARRAY_GET_INT(data,hp);
		DBCREQ_ARRAY_GET_INT(data,att);
		DBCREQ_ARRAY_GET_INT(data,def);
		DBCREQ_ARRAY_GET_INT(data,crit);
		DBCREQ_ARRAY_GET_INT(data,acrit);
		DBCREQ_ARRAY_GET_INT(data,dodge);
		DBCREQ_ARRAY_GET_INT(data,adodge);
		DBCREQ_ARRAY_GET_INT(data,critt);
		DBCREQ_ARRAY_GET_INT(data,speed);
		DBCREQ_ARRAY_GET_BINARY(data, skill, HERO_SKILL_LENGTH);

		DBCREQ_ARRAY_GET_END();

		return 0;
	}

	virtual int Add(DataMartialHero &data)
	{
		DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
		DBCREQ_SET_KEY(data.uid);

		DBCREQ_SET_INT(data, id);
		DBCREQ_SET_INT(data, owner_uid);
		DBCREQ_SET_CHAR(data, name, BASE_NAME_LEN);
		DBCREQ_SET_CHAR(data, fig, BASE_FIG_LEN);
		DBCREQ_SET_INT(data, club_grade);
		DBCREQ_SET_INT(data, owner_level);
		DBCREQ_SET_INT(data, heroid);
		DBCREQ_SET_INT(data, hp);
		DBCREQ_SET_INT(data, att);
		DBCREQ_SET_INT(data, def);
		DBCREQ_SET_INT(data, crit);
		DBCREQ_SET_INT(data, acrit);
		DBCREQ_SET_INT(data, dodge);
		DBCREQ_SET_INT(data, adodge);
		DBCREQ_SET_INT(data, critt);
		DBCREQ_SET_INT(data, speed);
	    DBCREQ_SET_BINARY(data, skill, HERO_SKILL_LENGTH);
		DBCREQ_EXEC;

		return 0;
	}

	virtual int Set(DataMartialHero &data)
	{
		DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
		DBCREQ_SET_KEY(data.uid);
		DBCREQ_SET_CONDITION(EQ, id, data.id);

		DBCREQ_SET_INT(data, owner_uid);
		DBCREQ_SET_CHAR(data, name, BASE_NAME_LEN);
		DBCREQ_SET_CHAR(data, fig, BASE_FIG_LEN);
		DBCREQ_SET_INT(data, club_grade);
		DBCREQ_SET_INT(data, owner_level);
		DBCREQ_SET_INT(data, heroid);
		DBCREQ_SET_INT(data, hp);
		DBCREQ_SET_INT(data, att);
		DBCREQ_SET_INT(data, def);
		DBCREQ_SET_INT(data, crit);
		DBCREQ_SET_INT(data, acrit);
		DBCREQ_SET_INT(data, dodge);
		DBCREQ_SET_INT(data, adodge);
		DBCREQ_SET_INT(data, critt);
		DBCREQ_SET_INT(data, speed);
	    DBCREQ_SET_BINARY(data, skill, HERO_SKILL_LENGTH);

		DBCREQ_EXEC;

		return 0;
	}

	virtual int Del(DataMartialHero &data)
	{
		DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
		DBCREQ_SET_KEY(data.uid);
		DBCREQ_SET_CONDITION(EQ, id, data.id);

		DBCREQ_EXEC;

		return 0;
	}

};

#endif /* APP_DATA_DATAMARTIALHERO_H_ */
