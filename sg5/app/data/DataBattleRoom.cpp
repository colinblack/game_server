/*
 * DataBattleRoom.cpp
 *
 *  Created on: 2015-5-26
 *      Author: Ralf
 */

#include "DataBattleRoom.h"

unsigned CDataBattleRoom::attacking(BattleHeroRoomProperty &attacker, BattleHeroRoomProperty &defender)
{
	bool diea = attacker.hpCheck();
	bool died = defender.hpCheck();
	if(diea && died)
		return BattleRoomHeroAttackResult_all_die;
	else if(diea)
		return BattleRoomHeroAttackResult_defender_win;
	else if(died)
		return BattleRoomHeroAttackResult_attacker_win;

	float ja = getJobEffect(attacker, defender);
	float jd = getJobEffect(defender, attacker);
	float sa = getSpeedEffect(attacker, defender);
	float sd = getSpeedEffect(defender, attacker);
	float pa = getProtectEffect(attacker, defender);
	float pd = getProtectEffect(defender, attacker);
	float ca = getCritEffect(attacker, defender);
	float cd = getCritEffect(defender, attacker);
	float aa = getAttackEffect(attacker, defender);
	float ad = getAttackEffect(defender, attacker);
	float la = getLevelEffect(attacker, attacker);
	float ld = 2.0f - la;
	float ra = getReflectEffect(attacker, defender);
	float rd = getReflectEffect(defender, attacker);
	float ea = getExtraEffect(attacker, defender);
	float ed = getExtraEffect(defender, attacker);
	float fa = getRandomEffect();
	float fd = getRandomEffect();
	//temp value
	float tta = ja*sa*fa;
	float ttd = jd*sd*fd;
	float ta = ca*aa*la*tta;
	float td = cd*ad*ld*ttd;
	//dps=attack+reflect+extra
	float dpsa = pa*ta + ra*td + ea*tta;
	float dpsd = pd*td + rd*ta + ed*ttd;
	//time=min(hp/dps)
	float timea = ((float)attacker.hp)/std::max(dpsd, BATTLE_ROOM_HERO_MIN_DPS);
	float timed = ((float)defender.hp)/std::max(dpsa, BATTLE_ROOM_HERO_MIN_DPS);
	float time = std::min(timea, timed);
	//damage
	attacker.hp -= (int)ceil(std::max(BATTLE_ROOM_HERO_MIN_HIT, dpsd * time));
	defender.hp -= (int)ceil(std::max(BATTLE_ROOM_HERO_MIN_HIT, dpsa * time));

	diea = attacker.die();
	died = defender.die();
	if(diea && died)
		return BattleRoomHeroAttackResult_all_die;
	else if(diea)
		return BattleRoomHeroAttackResult_defender_win;
	else if(died)
		return BattleRoomHeroAttackResult_attacker_win;
	return BattleRoomHeroAttackResult_none;
}
