/*
 * CgiNewWorld.cpp
 *
 *  Created on: 2014-9-17
 *      Author: Ralf
 */



#include "LogicInc.h"
class CCgiNewWorld: public CCgiBase {
public:
	CCgiNewWorld() : CCgiBase("newworld")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_GET_UID);
		SetFeature(CF_CHECK_SESSION);
		SetFeature(CF_CHECK_TIME);
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_CHECK_HASH);
		SetFeature(CF_CHECK_VERSION);
		SetFeature(CF_APPEND_HASH);
		SetFeature(CF_PARSE_DATA);
		SetFeature(CF_CRYPT_DATA);
		SetFeature(CF_DECRYPT_DATA);
		SetFeature(CF_COMPRESS_OUT);
	}

	CGI_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("GetWorld", GetWorld)
	CGI_SET_ACTION_MAP("GetHistory", GetHistory)
	CGI_SET_ACTION_MAP("GetMission", GetMission)
	CGI_SET_ACTION_MAP("GetCity", GetCity)
	CGI_SET_ACTION_MAP("GetBattle", GetBattle)
	CGI_SET_ACTION_MAP("GetBattleList", GetBattleList)
	CGI_SET_ACTION_MAP("GetHero", GetHero)
	CGI_SET_ACTION_MAP("GetAllHero", GetAllHero)
	CGI_SET_ACTION_MAP("SetHero", SetHero)
	CGI_SET_ACTION_MAP("Move", Move)
	CGI_SET_ACTION_MAP("Change", Change)
	CGI_SET_ACTION_MAP("Clone", Clone)
	CGI_SET_ACTION_MAP("Recover", Recover)
	CGI_SET_ACTION_MAP("Collect", Collect)
	CGI_SET_ACTION_MAP("Rush", Rush)
	CGI_SET_ACTION_MAP("Double", Double)
	CGI_SET_ACTION_MAP("rushTS", rushTS)
	CGI_SET_ACTION_MAP("CollectOther", CollectOther)
	CGI_SET_ACTION_MAP("Blink", Blink)
	CGI_SET_ACTION_MAP("Explode", Explode)
	CGI_SET_ACTION_MAP("Buildyjt", Buildyjt)
	CGI_SET_ACTION_MAP("UseJM", UseJM)
	CGI_SET_ACTION_MAP("BuyNPC", BuyNPC)

	CGI_ACTION_MAP_END

	~CCgiNewWorld()
	{
	}

	int GetWorld()
	{
		int ret = 0;

		CLogicNewWorld logicNewWorld;
		ret = logicNewWorld.GetWorld(m_jsonResult);

		CGI_SEND_LOG("action=GetWorld&uid=%u", m_uid);
		return ret;
	}

	int GetHistory()
	{
		int ret = 0;

		unsigned index = 0;
		if(!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;

		CLogicNewWorld logicNewWorld;
		ret = logicNewWorld.GetHistory(index, m_jsonResult);

		CGI_SEND_LOG("action=GetHistory&uid=%u", m_uid);
		return ret;
	}

	int GetMission()
	{
		int ret = 0;

		CLogicNewWorld logicNewWorld;
		ret = logicNewWorld.GetMission(m_jsonResult);

		CGI_SEND_LOG("action=GetMission&uid=%u", m_uid);
		return ret;
	}

	int GetCity()
	{
		int ret = 0;

		unsigned cid = 0;
		if(!Json::GetUInt(m_data, "cid", cid))
			return R_ERR_PARAM;

		CLogicNewWorld logicNewWorld;
		ret = logicNewWorld.GetCity(cid, m_jsonResult);

		CGI_SEND_LOG("action=GetCity&uid=%u&cid=%u", m_uid, cid);
		return ret;
	}

	int GetBattle()
	{
		int ret = 0;

		unsigned cid = 0;
		if(!Json::GetUInt(m_data, "cid", cid))
			return R_ERR_PARAM;

		CLogicNewWorld logicNewWorld;
		ret = logicNewWorld.GetBattle(cid, m_jsonResult);

		CGI_SEND_LOG("action=GetBattle&uid=%u", m_uid);
		return ret;
	}

	int GetBattleList()
	{
		int ret = 0;

		unsigned cid = 0;
		if(!Json::GetUInt(m_data, "cid", cid))
			return R_ERR_PARAM;

		unsigned camp = 0;
		if(!Json::GetUInt(m_data, "camp", camp))
			return R_ERR_PARAM;

		CLogicNewWorld logicNewWorld;
		ret = logicNewWorld.GetBattleList(cid, camp, m_jsonResult);

		CGI_SEND_LOG("action=GetBattleList&uid=%u", m_uid);
		return ret;
	}

	int GetHero()
	{
		int ret = 0;

		unsigned index = 0;
		if(!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;

		CLogicNewWorld logicNewWorld;
		ret = logicNewWorld.GetHero(m_uid, index, m_jsonResult);

		CGI_SEND_LOG("action=GetHero&uid=%u", m_uid);
		return ret;
	}

	int GetAllHero()
	{
		int ret = 0;

		CLogicNewWorld logicNewWorld;
		ret = logicNewWorld.GetAllHero(m_uid, m_jsonResult);

		CGI_SEND_LOG("action=GetAllHero&uid=%u", m_uid);
		return ret;
	}

	int SetHero()
	{
		int ret = 0;

		unsigned index = 0;
		if(!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;

		CLogicNewWorld logicNewWorld;
		ret = logicNewWorld.SetHero(m_uid, index, m_data, m_jsonResult);

		CGI_SEND_LOG("action=SetHero&uid=%u", m_uid);
		return ret;
	}

	int Move()
	{
		int ret = 0;

		unsigned index = 0;
		if(!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;

		unsigned cid = 0;
		if(!Json::GetUInt(m_data, "cid", cid))
			return R_ERR_PARAM;

		unsigned leave = 0;
		Json::GetUInt(m_data, "leave", leave);

		unsigned fly = 0;
		Json::GetUInt(m_data, "fly", fly);

		CLogicNewWorld logicNewWorld;
		ret = logicNewWorld.Move(m_uid, index, cid, leave?true:false, fly?1:0, m_jsonResult);

		CGI_SEND_LOG("action=Move&uid=%u", m_uid);
		return ret;
	}

	int Change()
	{
		int ret = 0;

		unsigned index = 0;
		if(!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;

		unsigned type = 0;
		if(!Json::GetUInt(m_data, "type", type))
			return R_ERR_PARAM;

		CLogicNewWorld logicNewWorld;
		ret = logicNewWorld.Change(m_uid, index, (type-1)%NewWorldHeroJob_max, m_jsonResult);

		CGI_SEND_LOG("action=Change&uid=%u", m_uid);
		return ret;
	}

	int Clone()
	{
		int ret = 0;

		unsigned index = 0;
		if(!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;
		unsigned equd = 0;
		if(!Json::GetUInt(m_data, "equd", equd))
			return R_ERR_PARAM;

		CLogicNewWorld logicNewWorld;
		ret = logicNewWorld.Clone(m_uid, index, equd, m_jsonResult);

		CGI_SEND_LOG("action=Clone&uid=%u", m_uid);
		return ret;
	}

	int Recover()
	{
		int ret = 0;

		unsigned index = 0;
		if(!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;
		unsigned equd = 0;
		if(!Json::GetUInt(m_data, "equd", equd))
			return R_ERR_PARAM;
		unsigned num = 0;
		if(!Json::GetUInt(m_data, "num", num) || !num)
			return R_ERR_PARAM;

		CLogicNewWorld logicNewWorld;
		ret = logicNewWorld.Recover(m_uid, index, equd, num, m_jsonResult);

		CGI_SEND_LOG("action=Recover&uid=%u", m_uid);
		return ret;
	}

	int Explode()
	{
		int ret = 0;

		unsigned index = 0;
		if(!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;
		unsigned equd = 0;
		if(!Json::GetUInt(m_data, "equd", equd))
			return R_ERR_PARAM;

		CLogicNewWorld logicNewWorld;
		ret = logicNewWorld.Explode(m_uid, index, equd, m_jsonResult);

		CGI_SEND_LOG("action=Explode&uid=%u", m_uid);
		return ret;
	}

	int Collect()
	{
		int ret = 0;

		unsigned cid = 0;
		if(!Json::GetUInt(m_data, "cid", cid))
			return R_ERR_PARAM;

		CLogicNewWorld logicNewWorld;
		ret = logicNewWorld.Collect(m_uid, cid, m_jsonResult);

		CGI_SEND_LOG("action=Collect&uid=%u&cid=%u", m_uid,cid);
		return ret;
	}

	int Rush()
	{
		int ret = 0;

		unsigned index = 0;
		if(!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;
		unsigned equd = 0;
		if(!Json::GetUInt(m_data, "equd", equd))
			return R_ERR_PARAM;
		unsigned fly = 0;
		Json::GetUInt(m_data, "fly", fly);

		CLogicNewWorld logicNewWorld;
		ret = logicNewWorld.Rush(m_uid, index, equd, fly?true:false, m_jsonResult);

		CGI_SEND_LOG("action=Rush&uid=%u", m_uid);
		return ret;
	}

	int Double()
	{
		// 1. 消耗道具
		// 2. 增加功勋

		int ret = 0;

		unsigned cid = 0;
		unsigned equd = 0;
		unsigned kingdom = 0;

		if (!Json::GetUInt(m_data, "cid", cid)
		|| !Json::GetUInt(m_data, "equd", equd)
		|| !Json::GetUInt(m_data, "kingdom", kingdom))
		{
			return R_ERR_PARAM;
		}

		CLogicNewWorld logicNewWorld;
		ret = logicNewWorld.Double(m_uid, kingdom, cid, equd, m_jsonResult);

		CGI_SEND_LOG("action=Double%uid=%u", m_uid);

		return ret;
	}

	int rushTS()
	{
		// 1. 消耗道具
		// 2. 增加功勋

		int ret = 0;

		unsigned cid = 0;
		unsigned equd = 0;
		unsigned kingdom = 0;

		if (!Json::GetUInt(m_data, "cid", cid)
		|| !Json::GetUInt(m_data, "equd", equd)
		|| !Json::GetUInt(m_data, "kingdom", kingdom))
		{
			return R_ERR_PARAM;
		}

		CLogicNewWorld logicNewWorld;
		ret = logicNewWorld.rushTS(m_uid, kingdom, cid, equd, m_jsonResult);

		CGI_SEND_LOG("action=rushTS%uid=%u", m_uid);

		return ret;
	}

	int CollectOther()
	{
		int ret = 0;
		unsigned cid = 0;
		unsigned equd = 0;

		if (!Json::GetUInt(m_data, "cid", cid) || !Json::GetUInt(m_data, "equd", equd))
		{
			return R_ERR_PARAM;
		}

		CLogicNewWorld logicNewWorld;
		ret = logicNewWorld.CollectOther(m_uid, cid, equd, m_jsonResult);

		CGI_SEND_LOG("action=CollectOther&uid=%u", m_uid);

		return ret;

	}

	int Blink()
	{
		int ret = 0;
		unsigned equd = 0;
		unsigned cid = 0;
		Json::Value freeHeroIndex;

		if (!Json::GetUInt(m_data, "equd", equd) || (0 == equd)
		|| !Json::GetUInt(m_data, "cid", cid)
		|| !Json::GetArray(m_data, "index", freeHeroIndex) || (freeHeroIndex.size() < 1))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		CLogicNewWorld logicNewWorld;
		ret = logicNewWorld.Blink(m_uid, cid, equd, freeHeroIndex, m_jsonResult);

		CGI_SEND_LOG("action=Blink&uid = %u", m_uid);
		return ret;
	}

	int Buildyjt()
	{
		int ret = 0;

		unsigned index = 0;
		if(!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;

		CLogicNewWorld logicNewWorld;
		ret = logicNewWorld.Buildyjt(m_uid, index, m_jsonResult);

		CGI_SEND_LOG("action=Buildyjt&uid=%u", m_uid);
		return ret;
	}

	int UseJM()
	{
		int ret = 0;

		unsigned cid = 0;
		unsigned id = 0;
		unsigned kingdom = 0;

		if (!Json::GetUInt(m_data, "cid", cid)
		|| !Json::GetUInt(m_data, "id", id)
		|| !Json::GetUInt(m_data, "kingdom", kingdom))
		{
			return R_ERR_PARAM;
		}

		CLogicNewWorld logicNewWorld;
		ret = logicNewWorld.UseJM(m_uid, id, cid, kingdom, m_jsonResult);

		CGI_SEND_LOG("action=UseJM%uid=%u", m_uid);

		return ret;
	}

	int BuyNPC()
	{
		int ret = 0;

		unsigned cid = 0;
		unsigned kingdom = 0;

		if (!Json::GetUInt(m_data, "cid", cid)
		|| !Json::GetUInt(m_data, "kingdom", kingdom))
		{
			return R_ERR_PARAM;
		}

		CLogicNewWorld logicNewWorld;
		ret = logicNewWorld.BuyNPC(m_uid, cid, kingdom, m_jsonResult);

		CGI_SEND_LOG("action=BuyNPC%uid=%u", m_uid);

		return ret;
	}

private:

};

CGI_MAIN(CCgiNewWorld)
