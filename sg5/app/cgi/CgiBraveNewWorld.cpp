/*
 * CgiBraveNewWorld.cpp
 *
 *  Created on: 2017-2-14
 *      Author: Ralf
 */



#include "LogicInc.h"

class CCgiBraveNewWorld: public CCgiBase {
public:
	CCgiBraveNewWorld() : CCgiBase("BraveNewWorld")
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

		int ret = CLogicBraveNewWorld::Init(CONFIG_BRAVE_NEW_WORLD_DATA, false);
		if(ret)
			exit(ret);
	}

	CGI_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("GetSelf", GetSelf)
	CGI_SET_ACTION_MAP("GetMissionInfo", GetMissionInfo)
	CGI_SET_ACTION_MAP("GetPoints", GetPoints)
	CGI_SET_ACTION_MAP("GetOnePoint", GetOnePoint)
	CGI_SET_ACTION_MAP("GetPointsLimit", GetPointsLimit)
	CGI_SET_ACTION_MAP("GetZones", GetZones)
	CGI_SET_ACTION_MAP("GetHistory", GetHistory)
	CGI_SET_ACTION_MAP("GetFavourate", GetFavourate)
	CGI_SET_ACTION_MAP("Collect", Collect)
	CGI_SET_ACTION_MAP("StartAttack", StartAttack)
	CGI_SET_ACTION_MAP("EndAttack", EndAttack)
	CGI_SET_ACTION_MAP("FastAttack", FastAttack)
	CGI_SET_ACTION_MAP("Move", Move)
	CGI_SET_ACTION_MAP("Build", Build)
	CGI_SET_ACTION_MAP("Defend", Defend)
	CGI_SET_ACTION_MAP("RecoverPoint", RecoverPoint)
	CGI_SET_ACTION_MAP("RevcoverUser", RevcoverUser)
	CGI_SET_ACTION_MAP("Discard", Discard)
	CGI_SET_ACTION_MAP("JoinAlliance", JoinAlliance)
	CGI_SET_ACTION_MAP("SetFavourate", SetFavourate)
	CGI_SET_ACTION_MAP("Buy_hts", Buy_hts)
	CGI_SET_ACTION_MAP("Buy_bts", Buy_bts)
	CGI_SET_ACTION_MAP("Buy_bt", Buy_bt)
	CGI_SET_ACTION_MAP("CollectOne", CollectOne)
	CGI_SET_ACTION_MAP("AttackSelf", AttackSelf)
	CGI_SET_ACTION_MAP("GetMission", GetMission)
	CGI_ACTION_MAP_END

	~CCgiBraveNewWorld()
	{
		CLogicBraveNewWorld::Exit();
	}

	void ProcessSig(int sig)
	{
		CLogicBraveNewWorld::Sig(sig);
	}

	int GetSelf()
	{
		int ret = 0;

		unsigned aid;
		if (!Json::GetUInt(m_data, "aid", aid))
			return R_ERR_PARAM;

		unsigned lv;
		if (!Json::GetUInt(m_data, "lv", lv))
			return R_ERR_PARAM;

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.GetSelf(m_uid, aid, lv, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=GetSelf&uid=%u", m_uid);
		return ret;
	}

	int GetMissionInfo()
	{
		int ret = 0;
		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.GetMissionInfo(m_uid, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=GetMissionInfo&uid=%u", m_uid);
		return ret;
	}

	int GetPoints()
	{
		int ret = 0;

		if(!m_data.isMember("lands") || !m_data["lands"].isArray())
			return R_ERR_PARAM;
		vector<BraveNewWorldPoint> p;
		for(unsigned i=0;i<m_data["lands"].size();++i)
			p.push_back(BraveNewWorldPoint(m_data["lands"][i]["x"].asUInt(), m_data["lands"][i]["y"].asUInt()));

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.GetPoints(p, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=GetPoints&uid=%u", m_uid);
		return ret;
	}

	int GetOnePoint()
	{
		int ret = 0;

		unsigned x;
		if (!Json::GetUInt(m_data, "x", x))
			return R_ERR_PARAM;

		unsigned y;
		if (!Json::GetUInt(m_data, "y", y))
			return R_ERR_PARAM;

		BraveNewWorldPoint p(x, y);

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.GetOnePoint(p, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=GetOnePoint&uid=%u", m_uid);
		return ret;
	}

	int GetPointsLimit()
	{
		int ret = 0;

		if(!m_data.isMember("lands") || !m_data["lands"].isArray())
			return R_ERR_PARAM;
		vector<BraveNewWorldPoint> p;
		for(unsigned i=0;i<m_data["lands"].size();++i)
			p.push_back(BraveNewWorldPoint(m_data["lands"][i]["x"].asUInt(), m_data["lands"][i]["y"].asUInt()));

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.GetPointsLimit(p, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=GetPointsLimit&uid=%u", m_uid);
		return ret;
	}

	int GetZones()
	{
		int ret = 0;

		if(!m_data.isMember("zones") || !m_data["zones"].isArray())
			return R_ERR_PARAM;
		vector<unsigned> z;
		for(unsigned i=0;i<m_data["zones"].size();++i)
			z.push_back(m_data["zones"][i].asUInt());

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.GetZones(z, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=GetZones&uid=%u", m_uid);
		return ret;
	}

	int GetHistory()
	{
		int ret = 0;

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.GetHistory(m_uid, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=GetHistory&uid=%u", m_uid);
		return ret;
	}

	int GetFavourate()
	{
		int ret = 0;

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.GetFavourate(m_uid, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=GetFavourate&uid=%u", m_uid);
		return ret;
	}

	int Collect()
	{
		int ret = 0;

		unsigned seq;
		if (!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.Collect(m_uid, seq, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=Collect&uid=%u", m_uid);
		return ret;
	}

	int StartAttack()
	{
		int ret = 0;

		unsigned seq;
		if (!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		unsigned x;
		if (!Json::GetUInt(m_data, "x", x))
			return R_ERR_PARAM;

		unsigned y;
		if (!Json::GetUInt(m_data, "y", y))
			return R_ERR_PARAM;

		unsigned cash = 0;
		Json::GetUInt(m_data, "cash", cash);

		BraveNewWorldPoint p(x, y);

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.StartAttack(m_uid, seq, p, cash, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=StartAttack&uid=%u", m_uid);
		return ret;
	}

	int EndAttack()
	{
		int ret = 0;

		unsigned seq;
		if (!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		unsigned x;
		if (!Json::GetUInt(m_data, "x", x))
			return R_ERR_PARAM;

		unsigned y;
		if (!Json::GetUInt(m_data, "y", y))
			return R_ERR_PARAM;

		vector<unsigned> hp;
		if(m_data.isMember("user"))
		{
			if(!m_data["user"].isMember("hp") || !m_data["user"]["hp"].isArray() || m_data["user"]["hp"].size() != BRAVE_NEW_WORLD_HP_USER)
				return R_ERR_PARAM;
			for(unsigned i=0;i<BRAVE_NEW_WORLD_HP_USER;++i)
				hp.push_back(m_data["user"]["hp"][i].asUInt());
		}
		else
		{
			if(m_data.isMember("def") && m_data["def"].isMember("hp"))
				hp.push_back(m_data["def"]["hp"].asUInt());
			if(m_data.isMember("hp"))
				hp.push_back(m_data["hp"].asUInt());
			else
				return R_ERR_PARAM;
		}

		BraveNewWorldPoint p(x, y);

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.EndAttack(m_uid, seq, p, hp, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=EndAttack&uid=%u", m_uid);
		return ret;
	}

	int FastAttack()
	{
		int ret = 0;

		unsigned seq;
		if (!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		unsigned x;
		if (!Json::GetUInt(m_data, "x", x))
			return R_ERR_PARAM;

		unsigned y;
		if (!Json::GetUInt(m_data, "y", y))
			return R_ERR_PARAM;

		unsigned cash = 0;
		Json::GetUInt(m_data, "cash", cash);

		unsigned cash1 = 0;
		Json::GetUInt(m_data, "cash1", cash1);

		BraveNewWorldPoint p(x, y);

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.FastAttack(m_uid, seq, p, cash, cash1, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=FastAttack&uid=%u", m_uid);
		return ret;
	}

	int Move()
	{
		int ret = 0;

		unsigned seq;
		if (!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		unsigned x;
		if (!Json::GetUInt(m_data, "x", x))
			return R_ERR_PARAM;

		unsigned y;
		if (!Json::GetUInt(m_data, "y", y))
			return R_ERR_PARAM;

		unsigned ud;
		if (!Json::GetUInt(m_data, "ud", ud))
			return R_ERR_PARAM;

		unsigned super = 0;
		Json::GetUInt(m_data, "super", super);

		BraveNewWorldPoint p(x, y);

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.Move(m_uid, seq, p, ud, super, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=Move&uid=%u", m_uid);
		return ret;
	}

	int Build()
	{
		int ret = 0;

		unsigned seq;
		if (!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		unsigned x;
		if (!Json::GetUInt(m_data, "x", x))
			return R_ERR_PARAM;

		unsigned y;
		if (!Json::GetUInt(m_data, "y", y))
			return R_ERR_PARAM;

		unsigned cash = 0;
		Json::GetUInt(m_data, "cash", cash);

		BraveNewWorldPoint p(x, y);

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.Build(m_uid, seq, cash, p, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=Build&uid=%u", m_uid);
		return ret;
	}

	int Defend()
	{
		int ret = 0;

		unsigned seq;
		if (!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		unsigned cash = 0;
		Json::GetUInt(m_data, "cash", cash);

		unsigned x;
		if (!Json::GetUInt(m_data, "x", x))
			return R_ERR_PARAM;

		unsigned y;
		if (!Json::GetUInt(m_data, "y", y))
			return R_ERR_PARAM;

		unsigned hero;
		if (!Json::GetUInt(m_data, "hero", hero))
			return R_ERR_PARAM;

		BraveNewWorldPoint p(x, y);

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.Defend(m_uid, seq, cash, p, hero, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=Defend&uid=%u", m_uid);
		return ret;
	}

	int RecoverPoint()
	{
		int ret = 0;

		unsigned seq;
		if (!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		unsigned x;
		if (!Json::GetUInt(m_data, "x", x))
			return R_ERR_PARAM;

		unsigned y;
		if (!Json::GetUInt(m_data, "y", y))
			return R_ERR_PARAM;

		unsigned cash = 0;
		Json::GetUInt(m_data, "cash", cash);

		BraveNewWorldPoint p(x, y);

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.RecoverPoint(m_uid, seq, p, cash, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=RecoverPoint&uid=%u", m_uid);
		return ret;
	}

	int RevcoverUser()
	{
		int ret = 0;

		unsigned seq;
		if (!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		unsigned cash = 0;
		Json::GetUInt(m_data, "cash", cash);

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.RevcoverUser(m_uid, seq, cash, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=RevcoverUser&uid=%u", m_uid);
		return ret;
	}

	int Discard()
	{
		int ret = 0;

		unsigned seq;
		if (!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		unsigned x;
		if (!Json::GetUInt(m_data, "x", x))
			return R_ERR_PARAM;

		unsigned y;
		if (!Json::GetUInt(m_data, "y", y))
			return R_ERR_PARAM;

		BraveNewWorldPoint p(x, y);

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.Discard(m_uid, seq, p, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=Discard&uid=%u", m_uid);
		return ret;
	}

	int JoinAlliance()
	{
		int ret = 0;

		unsigned userid;
		if (!Json::GetUInt(m_data, "userid", userid))
			return R_ERR_PARAM;

		unsigned aid;
		if (!Json::GetUInt(m_data, "aid", aid))
			return R_ERR_PARAM;

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.JoinAlliance(m_uid, userid, aid, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=JoinAlliance&uid=%u", m_uid);
		return ret;
	}

	int SetFavourate()
	{
		int ret = 0;

		unsigned seq;
		if (!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		if(!m_data.isMember("fav") || !m_data["fav"].isArray())
			return R_ERR_PARAM;
		vector<BraveNewWorldPoint> p;
		for(unsigned i=0;i<m_data["fav"].size();++i)
			p.push_back(BraveNewWorldPoint(m_data["fav"][i]["x"].asUInt(), m_data["fav"][i]["y"].asUInt()));

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.SetFavourate(m_uid, seq, p, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=SetFavourate&uid=%u", m_uid);
		return ret;
	}

	int Buy_hts()
	{
		int ret = 0;

		unsigned seq;
		if (!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.Buy_hts(m_uid, seq,m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=Buy_hts&uid=%u", m_uid);
		return ret;
	}

	int Buy_bts()
	{
		int ret = 0;

		unsigned seq;
		if (!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.Buy_bts(m_uid, seq, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=Buy_bts&uid=%u", m_uid);
		return ret;
	}

	int Buy_bt()
	{
		int ret = 0;

		unsigned seq;
		if (!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		unsigned count;
		if (!Json::GetUInt(m_data, "count", count))
			return R_ERR_PARAM;

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.Buy_bt(m_uid, seq, count, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=Buy_bt&uid=%u", m_uid);
		return ret;
	}

	int CollectOne()
	{
		int ret = 0;

		unsigned seq;
		if (!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		unsigned x;
		if (!Json::GetUInt(m_data, "x", x))
			return R_ERR_PARAM;

		unsigned y;
		if (!Json::GetUInt(m_data, "y", y))
			return R_ERR_PARAM;

		BraveNewWorldPoint p(x, y);

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.CollectOne(m_uid, seq, p, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=CollectOne&uid=%u", m_uid);
		return ret;
	}

	int AttackSelf()
	{
		int ret = 0;

		unsigned seq;
		if (!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		unsigned x;
		if (!Json::GetUInt(m_data, "x", x))
			return R_ERR_PARAM;

		unsigned y;
		if (!Json::GetUInt(m_data, "y", y))
			return R_ERR_PARAM;

		BraveNewWorldPoint p(x, y);

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.AttackSelf(m_uid, seq, p, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=AttackSelf&uid=%u", m_uid);
		return ret;
	}

	int GetMission()
	{
		int ret = 0;

		unsigned seq;
		if (!Json::GetUInt(m_data, "seq", seq))
			return R_ERR_PARAM;

		unsigned type;
		if (!Json::GetUInt(m_data, "type", type))
			return R_ERR_PARAM;

		CLogicBraveNewWorld logicBraveNewWorld;
		ret = logicBraveNewWorld.GetMission(m_uid, seq, type, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=GetMission&uid=%u", m_uid);
		return ret;
	}
};

CGI_MAIN(CCgiBraveNewWorld)


