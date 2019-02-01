/*
 * DataBattleRoom.h
 *
 *  Created on: 2015-5-26
 *      Author: Ralf
 */

#ifndef DATABATTLEROOM_H_
#define DATABATTLEROOM_H_

#include "Kernel.h"
#include <math.h>
#include "ProtoNewMatch.pb.h"
#include "DataNewWorld.h"

#define BATTLE_ROOM_HERO_MIN_DPS		1.0f
#define BATTLE_ROOM_HERO_MIN_HIT		1.0f
#define BATTLE_ROOM_HERO_MIN_LIVE		0
#define BATTLE_ROOM_HERO_REDUCE 		0.65f

enum BattleRoomHeroProperty
{
	BattleRoomHeroProperty_hp					= 0,
	BattleRoomHeroProperty_attack				= 1,
	BattleRoomHeroProperty_defence				= 2,
	BattleRoomHeroProperty_speed				= 3,
	BattleRoomHeroProperty_crit					= 4,
	BattleRoomHeroProperty_anti_crit			= 5,
	BattleRoomHeroProperty_crit_times			= 6,
	BattleRoomHeroProperty_anti_crit_times		= 7,
	BattleRoomHeroProperty_dodge				= 8,
	BattleRoomHeroProperty_anti_dodge			= 9,
	BattleRoomHeroProperty_block				= 10,
	BattleRoomHeroProperty_anti_block			= 11,
	BattleRoomHeroProperty_extra				= 12,
	BattleRoomHeroProperty_anti_extra			= 13,
	BattleRoomHeroProperty_reflect				= 14,
	BattleRoomHeroProperty_anti_reflect			= 15,
	BattleRoomHeroProperty_type_extra			= 16,
	BattleRoomHeroProperty_anti_speed			= 17,

	BattleRoomHeroProperty_max
};

enum BattleRoomHeroJob
{
	BattleRoomHeroJob_warrior				= 0,
	BattleRoomHeroJob_shooter				= 1,
	BattleRoomHeroJob_wizard				= 2,

	BattleRoomHeroJob_max
};

enum BattleRoomHeroAttackResult
{
	BattleRoomHeroAttackResult_none			= 0,
	BattleRoomHeroAttackResult_attacker_win	= 1,
	BattleRoomHeroAttackResult_defender_win	= 2,
	BattleRoomHeroAttackResult_all_die		= 3,
};

struct BattleHeroRoomProperty
{
	unsigned hid, job, level;
	int hp;
	int property[BattleRoomHeroProperty_max];
	BattleHeroRoomProperty()
	{
		hid = job = level = 0;
		hp = 0;
		memset(property, 0, sizeof(property));
	}
	inline void recover()
	{
		hp = property[BattleRoomHeroProperty_hp];
	}
	inline bool hpCheck()
	{
		if(hp > property[BattleRoomHeroProperty_hp] || hp <= BATTLE_ROOM_HERO_MIN_LIVE)
		{
			hp = 0;
			return true;
		}
		return false;
	}
	inline bool dead() const
	{
		return hp == 0;
	}
	inline bool die()
	{
		if(hp <= BATTLE_ROOM_HERO_MIN_LIVE)
		{
			hp = 0;
			return true;
		}
		return false;
	}
	void parse(const ProtoNewMatch::ProtoHeroProperty& p)
	{
		hid = p.hid();
		job = p.job();
		level = p.level();
		hp = p.hp();
		for(int i=0;i<BattleRoomHeroProperty_max;++i)
			property[i] = p.property(i);
	}
	void serialize(ProtoNewMatch::ProtoHeroProperty* p)
	{
		p->set_hid(hid);
		p->set_job(job);
		p->set_level(level);
		p->set_hp(hp);
		for(int i=0;i<BattleRoomHeroProperty_max;++i)
			 p->add_property(property[i]);
	}
};

class CDataBattleRoom
{
public:
	//core
	static unsigned attacking(BattleHeroRoomProperty &attacker, BattleHeroRoomProperty &defender);
	static inline float getJobEffect(const BattleHeroRoomProperty &attacker, const BattleHeroRoomProperty &defender)
	{
		if((attacker.job + 1)%BattleRoomHeroJob_max == defender.job)
			return 1.05f;
		return 1.0f;
	}
	static inline float getRandomEffect()
	{
		return (float)(Math::GetRandomInt(200) + 900)/1000.0f;
	}
	static inline float getSpeedEffect(const BattleHeroRoomProperty &attacker, const BattleHeroRoomProperty &defender)
	{
		return std::max(1.0f, std::min(4.0f,
			(float)attacker.property[BattleRoomHeroProperty_speed]/100.0f
			* std::max(0.67f, std::min(1.0f, 1.0f-(float)defender.property[BattleRoomHeroProperty_anti_speed])/100.0f)));
	}
	static inline float getProtectEffect(const BattleHeroRoomProperty &attacker, const BattleHeroRoomProperty &defender)
	{
		return std::max(0.0f, 1.0f
			- BATTLE_ROOM_HERO_REDUCE * 0.5f * std::min(1.0f, std::max(0.0f, (float)defender.property[BattleRoomHeroProperty_block]
			      -(float)attacker.property[BattleRoomHeroProperty_anti_block])/1000.0f))
			* std::max(0.0f, 1.0f - BATTLE_ROOM_HERO_REDUCE * std::min(0.8f, std::max(0.0f,((float)defender.property[BattleRoomHeroProperty_dodge]-(float)attacker.property[BattleRoomHeroProperty_anti_dodge])
					/(float)CDataNewWorld::c_crit_dodge[defender.level-1])));
	}
	static inline float getCritEffect(const BattleHeroRoomProperty &attacker, const BattleHeroRoomProperty &defender)
	{
		return (1.0f
			+ BATTLE_ROOM_HERO_REDUCE * std::min(0.8f, std::max(0.0f,
				((float)attacker.property[BattleRoomHeroProperty_crit]-(float)defender.property[BattleRoomHeroProperty_anti_crit])
					/(float)CDataNewWorld::c_crit_dodge[attacker.level-1]))
			* std::max(attacker.property[BattleRoomHeroProperty_crit_times]
				  -defender.property[BattleRoomHeroProperty_anti_crit_times],0)/1000.0f);
	}
	static inline float getAttackEffect(const BattleHeroRoomProperty &attacker, const BattleHeroRoomProperty &defender)
	{
		return (float)CDataNewWorld::c_attack[attacker.level-1]
		   * (float)attacker.property[BattleRoomHeroProperty_attack]/std::max(1.0f,(float)defender.property[BattleRoomHeroProperty_defence]);
	}
	static inline float getLevelEffect(const BattleHeroRoomProperty &attacker, const BattleHeroRoomProperty &defender)
	{
		return 2.0f*(float)attacker.level/(float)(attacker.level+defender.level);
	}
	static inline float getReflectEffect(const BattleHeroRoomProperty &attacker, const BattleHeroRoomProperty &defender)
	{
		return 0.5f*(float)std::max(attacker.property[BattleRoomHeroProperty_reflect]-defender.property[BattleRoomHeroProperty_anti_reflect],0)/1000.0f;
	}
	static inline float getExtraEffect(const BattleHeroRoomProperty &attacker, const BattleHeroRoomProperty &defender)
	{
		return (float)std::max(0,attacker.property[BattleRoomHeroProperty_extra]-defender.property[BattleRoomHeroProperty_anti_extra]);
	}
};


#endif /* DATABATTLEROOM_H_ */
