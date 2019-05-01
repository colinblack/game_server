#include "DataHero.h"
#include "DataInc.h"

bool DataHero::AddExp(int exp_, int user_lvl)
{
	if (exp_ < 0 || user_lvl <= 0)
	{
		error_log("hero_add_exp_params error. uid=%u,exp=%d,user_lvl=%d", uid, exp_,user_lvl);
		return false;
	}

	if (exp_ == 0) return false;

	exp += exp_;

	//更新用户level数据
	const Hero::HeroInfoList& heroCfg =  HeroCfgWrap().HeroCfg();
	int levelSize = heroCfg.heroexp_size();
	if (levelSize <= 0)
	{
		throw std::runtime_error("hero_exp_cfg_error");
	}

	if (exp >=  heroCfg.heroexp(levelSize - 1))
	{
		exp =  heroCfg.heroexp(levelSize - 1);
		level = levelSize;
	}
	else
	{
		for (int i = level; i < levelSize; i++)
		{
			if (exp < (uint64_t)heroCfg.heroexp(i))
			{
				level = i;
				break;
			}
		}
	}

	if (level >= user_lvl)
	{
		level = user_lvl;
		if (level >= levelSize)
		{
			exp =  (uint64_t)heroCfg.heroexp(levelSize - 1);
		}
		else
		{
			exp = (uint64_t)heroCfg.heroexp(level) - 1;
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////
int CDataHero::Get(DataHero &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, heroid, data.heroid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(heroid);
	DBCREQ_NEED(level);
	DBCREQ_NEED(exp);
	DBCREQ_NEED(status);
	DBCREQ_NEED(attacknum);
	DBCREQ_NEED(ovonum);
	DBCREQ_NEED(killnum);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, heroid);
	DBCREQ_GET_INT(data, level);
	DBCREQ_GET_INT(data, exp);
	DBCREQ_GET_INT(data, status);
	DBCREQ_GET_INT(data, attacknum);
	DBCREQ_GET_INT(data, ovonum);
	DBCREQ_GET_INT(data, killnum);

	return 0;
}

int CDataHero::Get(vector<DataHero> &data)
{
	if (0 == data.size())
	{
		return R_ERR_PARAM;
	}

	DBCREQ_DECLARE(DBC::GetRequest, data[0].uid);
	DBCREQ_SET_KEY(data[0].uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(heroid);
	DBCREQ_NEED(level);
	DBCREQ_NEED(exp);
	DBCREQ_NEED(status);
	DBCREQ_NEED(attacknum);
	DBCREQ_NEED(ovonum);
	DBCREQ_NEED(killnum);

	data.clear();

	DBCREQ_EXEC;

	DBCREQ_ARRAY_GET_BEGIN(data);
	DBCREQ_ARRAY_GET_INT(data, uid);
	DBCREQ_ARRAY_GET_INT(data, heroid);
	DBCREQ_ARRAY_GET_INT(data, level);
	DBCREQ_ARRAY_GET_INT(data, exp);
	DBCREQ_ARRAY_GET_INT(data, status);
	DBCREQ_ARRAY_GET_INT(data, attacknum);
	DBCREQ_ARRAY_GET_INT(data, ovonum);
	DBCREQ_ARRAY_GET_INT(data, killnum);

	DBCREQ_ARRAY_GET_END();

	return 0;
}

int CDataHero::Add(DataHero &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, heroid);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, exp);
	DBCREQ_SET_INT(data, status);
	DBCREQ_SET_INT(data, attacknum);
	DBCREQ_SET_INT(data, ovonum);
	DBCREQ_SET_INT(data, killnum);

	DBCREQ_EXEC;

	return 0;
}

int CDataHero::Set(DataHero &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, heroid, data.heroid);

	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, exp);
	DBCREQ_SET_INT(data, status);
	DBCREQ_SET_INT(data, attacknum);
	DBCREQ_SET_INT(data, ovonum);
	DBCREQ_SET_INT(data, killnum);

	DBCREQ_EXEC;

	return 0;
}

int CDataHero::Del(DataHero &data)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ, heroid, data.heroid);

	DBCREQ_EXEC;

	return 0;
}
