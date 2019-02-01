/*
 * CgiAttack.cpp
 *
 *  Created on: 2011-6-29
 *      Author: dada
 */

#include "LogicInc.h"

class CCgiAttack : public CCgiBase
{

public:

	CCgiAttack() : CCgiBase("attack")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_GET_UID);
		SetFeature(CF_CHECK_SESSION);
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_CHECK_HASH);
		SetFeature(CF_APPEND_HASH);
		SetFeature(CF_PARSE_DATA);
		SetFeature(CF_CRYPT_DATA);
		SetFeature(CF_DECRYPT_DATA);
		SetFeature(CF_COMPRESS_OUT);
	}

	CGI_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("gethistory", GetAttackHistory)
	CGI_SET_ACTION_MAP("getlog", GetAttackLog)
	CGI_SET_ACTION_MAP("getdetail", GetAttackDetail)
	CGI_ACTION_MAP_END

	int GetAttackHistory()
	{
		vector<DataAttack> attacks;
		CLogicAttack logicAttack;
		int result = logicAttack.GetAttackHistory(m_uid, attacks);
		if(result != 0)
		{
			return result;
		}
		Json::Value &attacksData = m_jsonResult["attacks"];
		attacksData.resize(0);
		for(vector<DataAttack>::iterator itr = attacks.begin(); itr != attacks.end(); itr++)
		{
			Json::Value &attackData = attacksData[attacksData.size()];
			attackData["attack_id"] = Convert::UInt64ToString(itr->attack_id);
			attackData["a_uid"] = itr->attack_uid;
			attackData["d_uid"] = itr->defence_uid;
			attackData["d_baseid"] = itr->defence_baseid;
			attackData["a_pt"] = itr->attack_platform;
			attackData["a_name"] = itr->attack_user_name;
			if(IsAllianceId(itr->attack_alliance_id))
			{
				attackData["a_a_id"] = itr->attack_alliance_id;
				attackData["a_a_name"] = itr->attack_alliance_name;
				attackData["a_a_flag"] = itr->attack_alliance_flag;
			}
			attackData["d_pt"] = itr->defence_platform;
			attackData["d_name"] = itr->defence_user_name;
			attackData["d_base_name"] = itr->defence_base_name;
			if(IsAllianceId(itr->defence_alliance_id))
			{
				attackData["d_a_id"] = itr->defence_alliance_id;
				attackData["d_a_name"] = itr->defence_alliance_name;
				attackData["d_a_flag"] = itr->defence_alliance_flag;
			}
			attackData["st"] = itr->start_time;
			attackData["et"] = itr->end_time;
			attackData["r1"] = itr->r1_loot;
			attackData["r2"] = itr->r2_loot;
			attackData["r3"] = itr->r3_loot;
			attackData["r4"] = itr->r4_loot;
		}
		CGI_SEND_LOG("uid=%u&attacks=%u", m_uid, attacksData.size());
		return R_SUCCESS;
	}

	int GetAttackLog()
	{
		uint64_t attackId;
		if(!Json::GetUInt64(m_data, "attackid", attackId))
		{
			return R_ERR_PARAM;
		}
		CLogicAttack logicAttack;
		string attackLog;
		int result = logicAttack.GetAttackLog(attackId, m_uid, attackLog);
		if(result != 0)
		{
			return result;
		}
		m_jsonResult["attack_id"] = Convert::UInt64ToString(attackId);
		m_jsonResult["log"] = attackLog;
		CGI_SEND_LOG("uid=%u&attack_id=%llu&log_size=%u", m_uid, attackId, attackLog.size());
		return R_SUCCESS;
	}

	int GetAttackDetail()
	{
		uint64_t attackId;
		if(!Json::GetUInt64(m_data, "attackid", attackId))
		{
			return R_ERR_PARAM;
		}
		CLogicAttack logicAttack;
		DataAttack attack;
		int result = logicAttack.GetAttack(attackId,  attack);
		if(result != 0)
		{
			return result;
		}
		m_jsonResult["attack_id"] = Convert::UInt64ToString(attack.attack_id);
		m_jsonResult["a_uid"] = attack.attack_uid;
		m_jsonResult["d_uid"] = attack.defence_uid;
		m_jsonResult["d_baseid"] = attack.defence_baseid;
		m_jsonResult["a_pt"] = attack.attack_platform;
		m_jsonResult["a_name"] = attack.attack_user_name;
		if(IsAllianceId(attack.attack_alliance_id))
		{
			m_jsonResult["a_a_id"] = attack.attack_alliance_id;
			m_jsonResult["a_a_name"] = attack.attack_alliance_name;
			m_jsonResult["a_a_flag"] = attack.attack_alliance_flag;
		}
		m_jsonResult["d_pt"] = attack.defence_platform;
		m_jsonResult["d_name"] = attack.defence_user_name;
		m_jsonResult["d_base_name"] = attack.defence_base_name;
		if(IsAllianceId(attack.defence_alliance_id))
		{
			m_jsonResult["d_a_id"] = attack.defence_alliance_id;
			m_jsonResult["d_a_name"] = attack.defence_alliance_name;
			m_jsonResult["d_a_flag"] = attack.defence_alliance_flag;
		}
		m_jsonResult["st"] = attack.start_time;
		m_jsonResult["et"] = attack.end_time;
		m_jsonResult["r1"] = attack.r1_loot;
		m_jsonResult["r2"] = attack.r2_loot;
		m_jsonResult["r3"] = attack.r3_loot;
		m_jsonResult["r4"] = attack.r4_loot;
		m_jsonResult["log"] = attack.log;
		CGI_SEND_LOG("action=getdetail&uid=%u&attack_id=%llu", m_uid, attackId);
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiAttack)
