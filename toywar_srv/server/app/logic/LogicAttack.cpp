/*
 * LogicAttack.cpp
 *
 *  Created on: 2011-6-29
 *      Author: Administrator
 */

#include "LogicAttack.h"

int CLogicAttack::AddAttack(DataAttack &attack)
{
	int ret;
	CLogicIdCtrl logicIdCtrl;
	ret = logicIdCtrl.GetNextId(KEY_ATTACK_ID_CTRL, attack.attack_id);
	if(ret != 0)
	{
		return ret;
	}
	attack.start_time = Time::GetGlobalTime();
	attack.end_time = Time::GetGlobalTime();
	attack.r1_loot = 0;
	attack.r2_loot = 0;
	attack.r3_loot = 0;
	attack.r4_loot = 0;

	CDataAttack attackDB;
	ret = attackDB.AddAttack(attack);
	if (ret != 0)
	{
		fatal_log("[AddAttack fail][ret=%d,attack_uid=%d,defence_uid=%d,baseid=%d]",
				ret,attack.attack_uid,attack.defence_uid,attack.defence_baseid);
		DB_ERROR_RETURN_MSG("add_attack_fail");
	}

	CLogicUserInteract logicUserInteract;
	CDataUserAttack userAttackDB;
	DataUserAttack userAttack;
	userAttack.uid = attack.attack_uid;
	userAttack.attack_id = attack.attack_id;
	userAttack.opposite_uid = attack.defence_uid;
	userAttack.opposite_platform = attack.defence_platform;
	userAttack.defence_baseid = attack.defence_baseid;
	userAttack.type = AT_ATTACK;
	userAttack.status = AS_NO_READ;
	userAttack.start_time = attack.start_time;
	ret = userAttackDB.AddUserAttack(userAttack);

	if (attack.attack_uid != attack.defence_uid)
	{
		userAttack.uid = attack.defence_uid;
		userAttack.attack_id = attack.attack_id;
		userAttack.opposite_uid = attack.attack_uid;
		userAttack.opposite_platform = attack.attack_platform;;
		userAttack.defence_baseid = attack.defence_baseid;
		userAttack.type = AT_DEFENCE;
		userAttack.status = AS_NO_READ;
		userAttack.start_time = attack.start_time;
		ret = userAttackDB.AddUserAttack(userAttack);

		ret = logicUserInteract.AddAttack(attack.attack_uid, attack.defence_uid);
	}

	//记录联盟仇恨
	if(attack.attack_alliance_id != attack.defence_alliance_id)
	{
		if(IsAllianceId(attack.attack_alliance_id))
		{
			ret = logicUserInteract.AddAttack(attack.attack_alliance_id, attack.defence_uid);
		}
		if(IsAllianceId(attack.defence_alliance_id))
		{
			ret = logicUserInteract.AddAttack(attack.attack_uid, attack.defence_alliance_id);
		}
		if(IsAllianceId(attack.attack_alliance_id) && IsAllianceId(attack.defence_alliance_id))
		{
			ret = logicUserInteract.AddAttack(attack.attack_alliance_id, attack.defence_alliance_id);
		}
	}

	return 0;
}

int CLogicAttack::UpdateAttack(const DataAttack &attack)
{
	int ret;
	vector<DataUserAttack> userAttacks;
	CDataUserAttack dbUserAttack;
	ret = dbUserAttack.GetUserAttacksCondition(attack.attack_uid, AS_NO_READ, AT_ATTACK,
			0, Time::GetGlobalTime() - ATTACK_MAX_TIME, userAttacks);
	if(ret != 0)
	{
		error_log("[GetUserAttacksCondition fail][ret=%d,attack_uid=%d]", ret, attack.attack_uid);
		DB_ERROR_RETURN_MSG("get_user_attack_fail");
	}
	uint64_t attackId = 0;
	for(vector<DataUserAttack>::iterator itr = userAttacks.begin(); itr != userAttacks.end(); itr++)
	{
		if(itr->attack_id > attackId)
		{
			attackId = itr->attack_id;
		}
	}
	if (attackId == 0)
	{
		error_log("[get attackid fail][ret=%d,attack_uid=%d,defence_uid=%d,baseid=%d]",
				ret,attack.attack_uid,attack.defence_uid,attack.defence_baseid);
		DB_ERROR_RETURN_MSG("not_find_attack");
	}

	CDataAttack attackDB;
	DataAttack old_attack;
	ret = attackDB.GetAttackLimit(attackId, old_attack);
	if (ret != 0)
	{
		error_log("[GetAttackLimit fail][ret=%d,attack_uid=%d,attack_id=%ld]",
				ret,attack.attack_uid,attack.attack_id);
		DB_ERROR_RETURN_MSG("get_attack_fail");
	}
	if (old_attack.attack_platform != attack.attack_platform ||
			old_attack.defence_uid != attack.defence_uid ||
			old_attack.defence_baseid != attack.defence_baseid)
	{
		error_log("[attack info mismatch][uid=%u,attackid=%llu,apt=%d,r_apt=%d,duid=%u,r_duid=%u,dbid=%u,r_dbid=%u]",
			attack.attack_uid, attackId, attack.attack_platform, old_attack.attack_platform,
			attack.defence_uid, old_attack.defence_uid, attack.defence_baseid, old_attack.defence_baseid);
		DATA_ERROR_RETURN_MSG("attack_info_error");
	}
	old_attack.end_time = Time::GetGlobalTime();
	old_attack.r1_loot = attack.r1_loot;
	old_attack.r2_loot = attack.r2_loot;
	old_attack.r3_loot = attack.r3_loot;
	old_attack.r4_loot = attack.r4_loot;
	old_attack.log = attack.log;
	ret = attackDB.SetAttack(old_attack);
	if (ret != 0)
	{
		error_log("[SetAttack fail][ret=%d,uid=%d,attack_id=%ld]",
				ret,attack.attack_uid,attack.attack_id);
		DB_ERROR_RETURN_MSG("set_attack_fail");
	}

	return 0;
}

int CLogicAttack::GetAttack(uint64_t attackId, DataAttack &attack)
{
	CDataAttack dbAttack;
	int ret = dbAttack.GetAttack(attackId, attack);
	if (ret != 0)
	{
		error_log("[GetAttack fail][ret=%d,attack_id=%d]",ret,attackId);
		DB_ERROR_RETURN_MSG("get_attack_fail");
	}
	return 0;
}

int CLogicAttack::GetAttackLog(uint64_t attackId, unsigned uid, string &log)
{
	int ret;
	DataAttack attack;
	ret = GetAttack(attackId, attack);
	if(ret != 0)
	{
		return ret;
	}
	if(uid != attack.attack_uid && uid != attack.defence_uid)
	{
		ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "not_data_auth");
	}
	log = attack.log;
	return 0;
}

int CLogicAttack::SetAttackRead(unsigned uid, AttackType type, unsigned baseid)
{
	CDataUserAttack dbUserAttack;
	int ret = dbUserAttack.SetUserAttacksStatus(uid, AS_NO_READ, type, baseid, AS_READ);
	if (ret != 0)
	{
		error_log("[SetUserAttacksStatus fail][ret=%d,uid=%d,type=%d,baseid=%u]", ret, uid, type, baseid);
		DB_ERROR_RETURN_MSG("set_user_attack_fail");
	}
	return 0;
}

int CLogicAttack::GetUnreadAttacks(vector<DataUserAttack> &attacks, unsigned uid, AttackType type, unsigned baseid, unsigned time)
{
	CDataUserAttack userAttackDB;
	int ret = userAttackDB.GetUserAttacksCondition(uid, AS_NO_READ, type, baseid, time, attacks);
	if (ret != 0)
	{
		error_log("[GetUserAttacksInStatus fail][ret=%d,uid=%d]", ret, uid);
		DB_ERROR_RETURN_MSG("get_user_attack_fail");
	}
	return ret;
}

int CLogicAttack::GetAttackHistory(unsigned uid, vector<DataAttack> &attacks)
{
	CDataUserAttack userAttackDB;
	vector<DataUserAttack> datas;
	int ret = userAttackDB.GetUserAttacksAfter(uid, Time::GetGlobalTime() - ATTACK_HISTORY_TIME, datas);
	if (ret != 0)
	{
		error_log("[GetUserAttackAfter fail][ret=%d,uid=%d]",ret,uid);
		DB_ERROR_RETURN_MSG("get_user_attack_fail");
	}
	while(datas.size() > MAX_ATTACK_HISTORY)
	{
		size_t minIndex = 0;
		unsigned minTime = datas[0].start_time;
		for(size_t i = 1; i < datas.size(); i++)
		{
			DataUserAttack &userAttack = datas[i];
			if(userAttack.start_time <= minTime)
			{
				if(userAttack.attack_id < datas[minIndex].attack_id)
				{
					minTime = userAttack.start_time;
					minIndex = i;
				}
			}
		}
		datas.erase(datas.begin() + minIndex);
	}
	CDataAttack attackDB;
	for (size_t i = 0; i < datas.size(); i++)
	{
		DataAttack attack;
		ret = attackDB.GetAttackLimit(datas[i].attack_id, attack);
		if (ret != 0)
		{
			error_log("[GetAttackLimit fail][ret=%d,uid=%u,attack_id=%llu]", ret, uid, datas[i].attack_id);
		}
		else
		{
			attacks.push_back(attack);
		}
	}

	return 0;
}

int CLogicAttack::GetAttackCount(unsigned uid, unsigned startTime, AttackType type, unsigned baseid, unsigned oppositeUid)
{
	int count = 0;
	CDataUserAttack dbUserAttack;
	int ret = dbUserAttack.GetUserAttacksCount(uid, startTime, type, baseid, oppositeUid, count);
	if (ret != 0)
	{
		error_log("[GetUserAttacksCount fail][ret=%d,uid=%u,startTime=%u,type=%d,baseid=%u,oppositeUid=%u]",
				ret, uid, startTime, (int)type, baseid, oppositeUid);
		return 0;
	}
	return count;
}

unsigned CLogicAttack::GetConAttackProtect(unsigned uid, unsigned baseid)
{
	int count = 0;
	CDataUserAttack dbUserAttack;
	int ret = dbUserAttack.GetUserAttacksCount(uid, Time::GetGlobalTime() - (60 * 60), AT_DEFENCE, baseid, 0, count);
	if (ret != 0)
	{
		error_log("[GetUserAttacksCount fail][ret=%d,uid=%d,baseid=%u]", ret, uid, baseid);
		return 0;
	}
	if(count >= 4)
	{
		return Time::GetGlobalTime() + (60 * 60);
	}
//	int ret = dbUserAttack.GetUserAttacksCondition(uid, Time::GetGlobalTime() - (24 * 60 * 60), AT_DEFENCE, baseid, attacks);
//	if (ret != 0)
//	{
//		error_log("[GetUserAttacksCondition fail][ret=%d,uid=%d,baseid]", ret, uid, baseid);
//		return 0;
//	}
//	int attackIn1Hour = 0;
//	int attackIn24Hour = 0;
//	for(vector<DataUserAttack>::iterator itr = attacks.begin(); itr != attacks.end(); itr++)
//	{
//		if(Time::GetGlobalTime() - itr->start_time <= (24 * 60 * 60))
//		{
//			attackIn1Hour++;
//			attackIn24Hour++;
//		}
//		else if(Time::GetGlobalTime() - itr->start_time <= (60 * 60))
//		{
//			attackIn1Hour++;
//		}
//	}
//	if(attackIn24Hour >= 10)
//	{
//		return Time::GetGlobalTime() + (24 * 60 * 60);
//	}
//	else if(attackIn1Hour >= 4)
//	{
//		return Time::GetGlobalTime() + (60 * 60);
//	}
	return 0;
}
