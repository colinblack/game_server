#include "DataHero.h"
#include "DataInc.h"

void DataHero::AddExp(int exp)
{
	if(exp < 0)
	{
		error_log("params error. uid=%u, hero_exp = %d", uid, exp);
		return;
	}
	if(exp == 0)
		return;
	this->exp += exp;

	int levelSize = ConfigManager::Instance()->hero_level_exp.size();
	uint64_t max_exp = ConfigManager::Instance()->hero_level_exp[levelSize-1];
	if(this->exp >= max_exp)
	{
		this->exp = max_exp;
		level = levelSize;
	}
	else
	{
		for (int i = level; i < levelSize; i++)
		{
			if (this->exp < ConfigManager::Instance()->hero_level_exp[i])
			{
				level = i;
				break;
			}
		}
	}

}

int CDataHero::Get(DataHero &data)
{
    DBCREQ_DECLARE(DBC::GetRequest, data.uid);
    DBCREQ_SET_KEY(data.uid);
    DBCREQ_SET_CONDITION(EQ, id, data.id);

    DBCREQ_NEED_BEGIN();
    DBCREQ_NEED(uid);
    DBCREQ_NEED(id);
    DBCREQ_NEED(exp);
    DBCREQ_NEED(level);
    DBCREQ_NEED(dragon_ball);
    DBCREQ_NEED(star);
    DBCREQ_NEED(skill);
    DBCREQ_NEED(battle_power);
    DBCREQ_NEED(base_power);
    DBCREQ_NEED(skill_power);
    DBCREQ_NEED(dragon_power);
    DBCREQ_NEED(star_power);
    DBCREQ_NEED(archive_power);
    DBCREQ_NEED(share_reward);

    DBCREQ_EXEC;
    DBCREQ_IFNULLROW;
    DBCREQ_IFFETCHROW;

    DBCREQ_GET_BEGIN();
    DBCREQ_GET_INT(data, uid);
    DBCREQ_GET_INT(data, id);
    DBCREQ_GET_INT(data, exp);
    DBCREQ_GET_INT(data, level);
    DBCREQ_GET_INT(data, dragon_ball);
    DBCREQ_GET_INT(data, star);
    DBCREQ_GET_BINARY(data, skill, HERO_SKILL_LENGTH);
    DBCREQ_GET_INT(data, battle_power);
    DBCREQ_GET_INT(data, base_power);
    DBCREQ_GET_INT(data, skill_power);
    DBCREQ_GET_INT(data, dragon_power);
    DBCREQ_GET_INT(data, star_power);
    DBCREQ_GET_INT(data, archive_power);
    DBCREQ_GET_INT(data, share_reward);

	return 0;
}

int CDataHero::Get(vector<DataHero>& data)
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
    DBCREQ_NEED(exp);
    DBCREQ_NEED(level);
    DBCREQ_NEED(dragon_ball);
    DBCREQ_NEED(star);
    DBCREQ_NEED(skill);
    DBCREQ_NEED(battle_power);
    DBCREQ_NEED(base_power);
    DBCREQ_NEED(skill_power);
    DBCREQ_NEED(dragon_power);
    DBCREQ_NEED(star_power);
    DBCREQ_NEED(archive_power);
    DBCREQ_NEED(share_reward);

    data.clear();

    DBCREQ_EXEC;
	DBCREQ_ARRAY_GET_BEGIN(data);
	DBCREQ_ARRAY_GET_INT(data, uid);
	DBCREQ_ARRAY_GET_INT(data, id);
	DBCREQ_ARRAY_GET_INT(data, exp);
	DBCREQ_ARRAY_GET_INT(data, level);
	DBCREQ_ARRAY_GET_INT(data, dragon_ball);
	DBCREQ_ARRAY_GET_INT(data, star);
	DBCREQ_ARRAY_GET_BINARY(data, skill, HERO_SKILL_LENGTH);
	DBCREQ_ARRAY_GET_INT(data, battle_power);
	DBCREQ_ARRAY_GET_INT(data, base_power);
	DBCREQ_ARRAY_GET_INT(data, skill_power);
	DBCREQ_ARRAY_GET_INT(data, dragon_power);
	DBCREQ_ARRAY_GET_INT(data, star_power);
	DBCREQ_ARRAY_GET_INT(data, archive_power);
	DBCREQ_ARRAY_GET_INT(data, share_reward);

	DBCREQ_ARRAY_GET_END();

	return 0;
}


int CDataHero::Add(DataHero &data)
{
    DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
    DBCREQ_SET_KEY(data.uid);

    DBCREQ_SET_INT(data, id);
    DBCREQ_SET_INT(data, exp);
    DBCREQ_SET_INT(data, level);
    DBCREQ_SET_INT(data, dragon_ball);
    DBCREQ_SET_INT(data, star);
    DBCREQ_SET_BINARY(data, skill, HERO_SKILL_LENGTH);
    DBCREQ_SET_INT(data, battle_power);
    DBCREQ_SET_INT(data, base_power);
    DBCREQ_SET_INT(data, skill_power);
    DBCREQ_SET_INT(data, dragon_power);
    DBCREQ_SET_INT(data, star_power);
    DBCREQ_SET_INT(data, archive_power);
    DBCREQ_SET_INT(data, share_reward);

    DBCREQ_EXEC;

	return 0;
}

int CDataHero::Set(DataHero &data)
{
    DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
    DBCREQ_SET_KEY(data.uid);
    DBCREQ_SET_CONDITION(EQ, id, data.id);

    DBCREQ_SET_INT(data, exp);
    DBCREQ_SET_INT(data, level);
    DBCREQ_SET_INT(data, dragon_ball);
    DBCREQ_SET_INT(data, star);
    DBCREQ_SET_BINARY(data, skill, HERO_SKILL_LENGTH);
    DBCREQ_SET_INT(data, battle_power);
    DBCREQ_SET_INT(data, base_power);
    DBCREQ_SET_INT(data, skill_power);
    DBCREQ_SET_INT(data, dragon_power);
    DBCREQ_SET_INT(data, star_power);
    DBCREQ_SET_INT(data, archive_power);
    DBCREQ_SET_INT(data, share_reward);

    DBCREQ_EXEC;

	return 0;
}

int CDataHero::Del(DataHero &data)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
    DBCREQ_SET_CONDITION(EQ, id, data.id);
	DBCREQ_EXEC;

	return 0;
}



