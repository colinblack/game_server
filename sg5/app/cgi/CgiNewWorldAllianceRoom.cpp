/*
 * CgiNewWorldAllianceRoom.cpp
 *
 *  Created on: 2014-9-17
 *      Author: Ralf
 */



#include "LogicInc.h"
class CCgiNewWorldAllianceRoom: public CCgiBase {
public:
	static map<string, string> m_EnvMap;

	CCgiNewWorldAllianceRoom() : CCgiBase("newworldallianceroom")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_GET_UID);
		SetFeature(CF_CHECK_TIME);
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_CHECK_HASH);
		SetFeature(CF_CHECK_VERSION);
		SetFeature(CF_APPEND_HASH);
		SetFeature(CF_PARSE_DATA);
		SetFeature(CF_CRYPT_DATA);
		SetFeature(CF_DECRYPT_DATA);
		SetFeature(CF_COMPRESS_OUT);

		m_EnvMap[EVN_NEW_WORLD_ALLIANCE_ROOM_NUM] = getenv(EVN_NEW_WORLD_ALLIANCE_ROOM_NUM);

		string path(CONFIG_NEW_WORLD_ALLIANCE_ROOM_DATA);
		path = path + "." + m_EnvMap[EVN_NEW_WORLD_ALLIANCE_ROOM_NUM];

		int ret = CLogicNewWorldAllianceRoom::Init(path, true);
		if(ret)
			exit(ret);
	}

	CGI_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("GetWorld", GetWorld)
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
	CGI_SET_ACTION_MAP("Rush", Rush)
	CGI_SET_ACTION_MAP("CollectOther", CollectOther)
	CGI_SET_ACTION_MAP("Blink", Blink)
	CGI_SET_ACTION_MAP("Explode", Explode)
	CGI_SET_ACTION_MAP("Buildyjt", Buildyjt)

	CGI_ACTION_MAP_END

	~CCgiNewWorldAllianceRoom()
	{
		CLogicNewWorldAllianceRoom::Exit();
	}

	void ProcessSig(int sig)
	{
		CLogicNewWorldAllianceRoom::Sig(sig);
	}

	int GetWorld()
	{
		int ret = 0;

		unsigned rid = 0;
		if(!Json::GetUInt(m_data, "rid", rid))
			return R_ERR_PARAM;

		CLogicNewWorldAllianceRoom logicNewWorldAllianceRoom;
		ret = logicNewWorldAllianceRoom.GetWorld(rid, m_jsonResult);

		CGI_SEND_LOG("action=GetWorld&uid=%u", m_uid);
		return ret;
	}

	int GetCity()
	{
		int ret = 0;

		unsigned rid = 0;
		if(!Json::GetUInt(m_data, "rid", rid))
			return R_ERR_PARAM;

		unsigned cid = 0;
		if(!Json::GetUInt(m_data, "cid", cid))
			return R_ERR_PARAM;

		CLogicNewWorldAllianceRoom logicNewWorldAllianceRoom;
		ret = logicNewWorldAllianceRoom.GetCity(rid, cid, m_jsonResult);

		CGI_SEND_LOG("action=GetCity&uid=%u&cid=%u", m_uid, cid);
		return ret;
	}

	int GetBattle()
	{
		int ret = 0;

		unsigned rid = 0;
		if(!Json::GetUInt(m_data, "rid", rid))
			return R_ERR_PARAM;

		unsigned cid = 0;
		if(!Json::GetUInt(m_data, "cid", cid))
			return R_ERR_PARAM;

		CLogicNewWorldAllianceRoom logicNewWorldAllianceRoom;
		ret = logicNewWorldAllianceRoom.GetBattle(rid, cid, m_jsonResult);

		CGI_SEND_LOG("action=GetBattle&uid=%u", m_uid);
		return ret;
	}

	int GetBattleList()
	{
		int ret = 0;

		unsigned rid = 0;
		if(!Json::GetUInt(m_data, "rid", rid))
			return R_ERR_PARAM;

		unsigned cid = 0;
		if(!Json::GetUInt(m_data, "cid", cid))
			return R_ERR_PARAM;

		unsigned camp = 0;
		if(!Json::GetUInt(m_data, "camp", camp))
			return R_ERR_PARAM;

		CLogicNewWorldAllianceRoom logicNewWorldAllianceRoom;
		ret = logicNewWorldAllianceRoom.GetBattleList(rid, cid, camp, m_jsonResult);

		CGI_SEND_LOG("action=GetBattleList&uid=%u", m_uid);
		return ret;
	}

	int GetHero()
	{
		int ret = 0;

		unsigned rid = 0;
		if(!Json::GetUInt(m_data, "rid", rid))
			return R_ERR_PARAM;

		unsigned index = 0;
		if(!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;

		CLogicNewWorldAllianceRoom logicNewWorldAllianceRoom;
		ret = logicNewWorldAllianceRoom.GetHero(rid, m_uid, index, m_jsonResult);

		CGI_SEND_LOG("action=GetHero&uid=%u", m_uid);
		return ret;
	}

	int GetAllHero()
	{
		int ret = 0;

		unsigned rid = 0;
		if(!Json::GetUInt(m_data, "rid", rid))
			return R_ERR_PARAM;

		CLogicNewWorldAllianceRoom logicNewWorldAllianceRoom;
		ret = logicNewWorldAllianceRoom.GetAllHero(rid, m_uid, m_jsonResult);

		CGI_SEND_LOG("action=GetAllHero&uid=%u", m_uid);
		return ret;
	}

	int SetHero()
	{
		int ret = 0;

		unsigned rid = 0;
		if(!Json::GetUInt(m_data, "rid", rid))
			return R_ERR_PARAM;

		unsigned index = 0;
		if(!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;

		unsigned seq = 0;
		if(!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		CLogicNewWorldAllianceRoom logicNewWorldAllianceRoom;
		ret = logicNewWorldAllianceRoom.SetHero(rid, m_uid, index, m_data, m_jsonResult, seq);

		CGI_SEND_LOG("action=SetHero&uid=%u", m_uid);
		return ret;
	}

	int Move()
	{
		int ret = 0;

		unsigned rid = 0;
		if(!Json::GetUInt(m_data, "rid", rid))
			return R_ERR_PARAM;

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

		unsigned seq = 0;
		if(!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		CLogicNewWorldAllianceRoom logicNewWorldAllianceRoom;
		ret = logicNewWorldAllianceRoom.Move(rid, m_uid, index, cid, leave?true:false, fly?1:0, m_jsonResult, seq);

		CGI_SEND_LOG("action=Move&uid=%u", m_uid);
		return ret;
	}

	int Change()
	{
		int ret = 0;

		unsigned rid = 0;
		if(!Json::GetUInt(m_data, "rid", rid))
			return R_ERR_PARAM;

		unsigned index = 0;
		if(!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;

		unsigned type = 0;
		if(!Json::GetUInt(m_data, "type", type))
			return R_ERR_PARAM;

		unsigned seq = 0;
		if(!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		CLogicNewWorldAllianceRoom logicNewWorldAllianceRoom;
		ret = logicNewWorldAllianceRoom.Change(rid, m_uid, index, (type-1)%NewWorldAllianceRoomHeroJob_max, m_jsonResult, seq);

		CGI_SEND_LOG("action=Change&uid=%u", m_uid);
		return ret;
	}

	int Clone()
	{
		int ret = 0;

		unsigned rid = 0;
		if(!Json::GetUInt(m_data, "rid", rid))
			return R_ERR_PARAM;

		unsigned index = 0;
		if(!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;

		unsigned seq = 0;
		if(!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		CLogicNewWorldAllianceRoom logicNewWorldAllianceRoom;
		ret = logicNewWorldAllianceRoom.Clone(rid, m_uid, index, m_jsonResult, seq);

		CGI_SEND_LOG("action=Clone&uid=%u", m_uid);
		return ret;
	}

	int Recover()
	{
		int ret = 0;

		unsigned rid = 0;
		if(!Json::GetUInt(m_data, "rid", rid))
			return R_ERR_PARAM;

		unsigned index = 0;
		if(!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;

		unsigned num = 0;
		if(!Json::GetUInt(m_data, "num", num) || !num)
			return R_ERR_PARAM;

		unsigned seq = 0;
		if(!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		CLogicNewWorldAllianceRoom logicNewWorldAllianceRoom;
		ret = logicNewWorldAllianceRoom.Recover(rid, m_uid, index, num, m_jsonResult, seq);

		CGI_SEND_LOG("action=Recover&uid=%u", m_uid);
		return ret;
	}

	int Explode()
	{
		int ret = 0;

		unsigned rid = 0;
		if(!Json::GetUInt(m_data, "rid", rid))
			return R_ERR_PARAM;

		unsigned index = 0;
		if(!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;

		unsigned seq = 0;
		if(!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		CLogicNewWorldAllianceRoom logicNewWorldAllianceRoom;
		ret = logicNewWorldAllianceRoom.Explode(rid, m_uid, index, m_jsonResult, seq);

		CGI_SEND_LOG("action=Explode&uid=%u", m_uid);
		return ret;
	}

	int Rush()
	{
		int ret = 0;

		unsigned rid = 0;
		if(!Json::GetUInt(m_data, "rid", rid))
			return R_ERR_PARAM;

		unsigned index = 0;
		if(!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;

		unsigned fly = 0;
		Json::GetUInt(m_data, "fly", fly);

		unsigned seq = 0;
		if(!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		CLogicNewWorldAllianceRoom logicNewWorldAllianceRoom;
		ret = logicNewWorldAllianceRoom.Rush(rid, m_uid, index, fly?true:false, m_jsonResult, seq);

		CGI_SEND_LOG("action=Rush&uid=%u", m_uid);
		return ret;
	}

	int CollectOther()
	{
		int ret = 0;

		unsigned rid = 0;
		if(!Json::GetUInt(m_data, "rid", rid))
			return R_ERR_PARAM;

		unsigned index = 0;
		if(!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;

		unsigned seq = 0;
		if(!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		CLogicNewWorldAllianceRoom logicNewWorldAllianceRoom;
		ret = logicNewWorldAllianceRoom.CollectOther(rid, m_uid, index, m_jsonResult, seq);

		CGI_SEND_LOG("action=CollectOther&uid=%u", m_uid);

		return ret;

	}

	int Blink()
	{
		int ret = 0;
		unsigned cid = 0;
		Json::Value freeHeroIndex, seq;

		unsigned rid = 0;
		if(!Json::GetUInt(m_data, "rid", rid))
			return R_ERR_PARAM;

		if (!Json::GetUInt(m_data, "cid", cid)
		|| !Json::GetArray(m_data, "index", freeHeroIndex) || freeHeroIndex.size() < 1
		|| !Json::GetArray(m_data, "seq", seq) || seq.size() != freeHeroIndex.size())
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		CLogicNewWorldAllianceRoom logicNewWorldAllianceRoom;
		ret = logicNewWorldAllianceRoom.Blink(rid, m_uid, cid, freeHeroIndex, m_jsonResult, seq);

		CGI_SEND_LOG("action=Blink&uid = %u", m_uid);
		return ret;
	}

	int Buildyjt()
	{
		int ret = 0;

		unsigned rid = 0;
		if(!Json::GetUInt(m_data, "rid", rid))
			return R_ERR_PARAM;

		unsigned index = 0;
		if(!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;

		unsigned seq = 0;
		if(!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		CLogicNewWorldAllianceRoom logicNewWorldAllianceRoom;
		ret = logicNewWorldAllianceRoom.Buildyjt(rid, m_uid, index, m_jsonResult, seq);

		CGI_SEND_LOG("action=Buildyjt&uid=%u", m_uid);
		return ret;
	}


private:

};

map<string, string> CCgiNewWorldAllianceRoom::m_EnvMap;

CGI_MAIN(CCgiNewWorldAllianceRoom)
