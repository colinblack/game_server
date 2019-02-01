#ifndef __DATA_HERO_H__
#define __DATA_HERO_H__

#include "Kernel.h"

struct DataHero {
	uint32_t uid;
	uint32_t id;
	uint64_t exp;
	uint32_t level;
	uint32_t dragon_ball;			//龙珠
	uint32_t star;					//星级
	uint32_t battle_power;			//总战力
	uint32_t base_power;			//基础战力
	uint32_t skill_power;			//技能战力
	uint32_t dragon_power;			//龙珠战力
	uint32_t star_power;			//升星战力
	uint32_t archive_power;			//图鉴战力
	uint32_t share_reward;			//分享奖励标志

	char skill[HERO_SKILL_LENGTH];  //技能等级
	DataHero(){
		uid = 0;
		id = 0;
		exp = 0;
		level = 1;
		dragon_ball = 0;
		star = 0;
		battle_power = 0;
		base_power = 0;
		skill_power = 0;
		dragon_power = 0;
		star_power = 0;
		archive_power = 0;
		share_reward = 0;
		memset(skill, 1, sizeof(skill));
	}

	void SetMessage(ProtoHero::HeroBaseInfoCPP *msg) const
	{
		msg->set_heroid(id);
		msg->set_exp(exp);
		msg->set_level(level);
		msg->set_dragonball(dragon_ball);
		msg->set_stars(star);
		msg->set_battlepower(battle_power);

		uint64_t levelExp = ConfigManager::Instance()->hero_level_exp[level-1];
		unsigned addExp = exp - levelExp;
		if(exp < levelExp)
		{
			error_log("exp wrong: exp: %u, levelExp: %u", exp, levelExp);
			throw runtime_error("exp_wrong");
		}

		msg->set_addexp(addExp);
		for(int i = 0; i < HERO_SKILL_LENGTH; ++i)
		{
			msg->add_skill(skill[i]);
		}

	}

	void AddExp(int exp);
};


class CDataHero :public DBCBase<DataHero, DB_HERO>
{
public:
	virtual int Get(DataHero &data);
	virtual int Get(vector<DataHero>&data);
	virtual int Add(DataHero &data);
	virtual int Set(DataHero &data);
	virtual int Del(DataHero &data);
};



#endif
