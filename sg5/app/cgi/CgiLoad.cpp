/*
 * CgiLoad.cpp
 *
 *  Created on: 2011-6-1
 *      Author: dada
 */

#include "LogicInc.h"

class CCgiLoad : public CCgiBase
{

public:

	CCgiLoad() : CCgiBase("load")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_GET_UID);
		SetFeature(CF_CHECK_SESSION);
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_CHECK_HASH);
		SetFeature(CF_CHECK_VERSION);
		SetFeature(CF_APPEND_HASH);
		SetFeature(CF_PARSE_DATA);
		SetFeature(CF_CRYPT_DATA);
		SetFeature(CF_DECRYPT_DATA);
		SetFeature(CF_COMPRESS_OUT);
	}

	CGI_ACTION_DEFAULT_MAP_BEGIN(Load)
	CGI_SET_ACTION_DEFAULT_MAP("Hero", Hero)
	CGI_SET_ACTION_DEFAULT_MAP("Building", Building)
	CGI_SET_ACTION_DEFAULT_MAP("Equipment", Equipment)
	CGI_SET_ACTION_DEFAULT_MAP("NewAct", NewAct)
	CGI_SET_ACTION_DEFAULT_MAP("Name", Name)
	CGI_SET_ACTION_DEFAULT_MAP("SingleNewAct", SingleNewAct)
	CGI_SET_ACTION_DEFAULT_MAP("UserLimit", UserLimit)
	CGI_SET_ACTION_DEFAULT_MAP("AllianceName", AllianceName)
	CGI_SET_ACTION_DEFAULT_MAP("OneHero", OneHero)

	CGI_ACTION_DEFAULT_MAP_END

	int Load()
	{
		unsigned uid = 0;
		if (!Json::GetUInt(m_data, "userid", uid) || uid == 0)
		{
			uid = m_uid;
		}
/****************允许跨服*********************
		//防止跨服
		if (IsValidUid(uid) && uid != m_uid)
		{
			int serverid1 = (int)((m_uid - 10000000) / 500000);
			int serverid2 = (int)((uid - 10000000) / 500000);
			if (serverid1 != serverid2)
			{
				error_log("[not same server][operated=%u,operator=%u]",uid,m_uid);
				PARAM_ERROR_RETURN_MSG("not_same_server");
			}
		}
********************************************/
		/*if (IsValidUid(uid) && uid != m_uid)
		{
			int serverid1 = 0;
			Config::GetDomain(serverid1);
			int serverid2 = MainConfig::GetMergedDomain((int)((uid - 10000000) / 500000 + 1));
			if (serverid1 != serverid2)
			{
				error_log("[not same server][operated=%u,operator=%u]",uid,m_uid);
				PARAM_ERROR_RETURN_MSG("not_same_server");
			}
		}*/
		m_jsonResult["uid"] = uid;

		string type;
		Json::GetString(m_data, "type", type);
		unsigned lasttime = 0;
		Json::GetUInt(m_data, "lasttime", lasttime);
		CLogicArchive logicArchive;
		int ret = logicArchive.Load(uid, m_uid, type, m_data, m_jsonResult, lasttime);
		if(ret != 0)
			return ret;

		m_jsonResult["currenttime"] = Time::GetGlobalTime();

		CGI_SEND_LOG("operator=%u&operated=%u&type=%s",m_uid,uid,type.c_str());
		return R_SUCCESS;
	}
	int Hero()
	{
		unsigned uid = 0;
		if (!Json::GetUInt(m_data, "userid", uid) || uid == 0)
		{
			uid = m_uid;
		}
		m_jsonResult["uid"] = uid;

		CLogicHero logicHero;
		int ret = logicHero.GetHero(uid, m_jsonResult["Hero"]);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=Hero&operator=%u&operated=%u",m_uid,uid);
		return R_SUCCESS;
	}

	int Building()
	{
		unsigned uid = 0;
		if (!Json::GetUInt(m_data, "userid", uid) || uid == 0)
		{
			uid = m_uid;
		}
		m_jsonResult["uid"] = uid;

		CLogicBuilding logicBuilding;
		int ret = logicBuilding.GetAllBuilding(uid, m_jsonResult["Building"]);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=Building&operator=%u&operated=%u",m_uid,uid);
		return R_SUCCESS;
	}

	int Equipment()
	{
		unsigned uid = 0;
		if (!Json::GetUInt(m_data, "userid", uid) || uid == 0)
		{
			uid = m_uid;
		}
		m_jsonResult["uid"] = uid;

		CLogicEquipment logicEquipment;
		int ret = logicEquipment.GetEquipment(uid, m_uid, m_jsonResult["equipment"]);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=Equipment&operator=%u&operated=%u",m_uid,uid);
		return R_SUCCESS;
	}

	int NewAct()
	{
		unsigned uid = 0;
		if (!Json::GetUInt(m_data, "userid", uid) || uid == 0)
		{
			uid = m_uid;
		}
		m_jsonResult["uid"] = uid;

		CLogicSecinc logicSecinc;
		int ret = logicSecinc.GetSecinc(uid, m_jsonResult["NewAct"]);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=NewAct&operator=%u&operated=%u",m_uid,uid);
		return R_SUCCESS;
	}

	int Name()
	{
		if(!m_data.isMember("uidlist") || !m_data["uidlist"].isArray())
			return R_ERR_PARAM;

		CLogicUserBasic logicUserBasic;
		for(unsigned i=0;i<m_data["uidlist"].size();++i)
		{
			string name, fig;
			logicUserBasic.GetNameFig(m_data["uidlist"][i].asUInt(), name, fig);
			m_jsonResult["namelist"][i]["uid"] = m_data["uidlist"][i];
			m_jsonResult["namelist"][i]["name"] = name;
			m_jsonResult["namelist"][i]["fig"] = fig;
		}

		CGI_SEND_LOG("action=NewAct&operator=%u",m_uid);
		return R_SUCCESS;
	}

	int SingleNewAct()
	{
		unsigned uid = 0, sid = 0;

		if (!Json::GetUInt(m_data, "userid", uid) || uid == 0 )
		{
			uid = m_uid;
		}

		if (!Json::GetUInt(m_data, "sid", sid) || sid == 0 )
		{
			return R_ERR_PARAM;
		}

		m_jsonResult["uid"] = uid;

		CLogicSecinc logicSecinc;
		int ret = logicSecinc.GetSecinc(uid, sid, m_jsonResult["NewAct"]);

		if(ret && R_ERR_NO_DATA != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=SingleNewAct&operator=%u&operated=%u",m_uid,uid);
		return R_SUCCESS;
	}

	int UserLimit()
	{
		if(!m_data.isMember("uids") || !m_data["uids"].isArray())
			return R_ERR_PARAM;

		CLogicUserBasic logicUserBasic;
		CLogicUser logicUser;
		for(unsigned i=0;i<m_data["uids"].size();++i)
		{
			string name;
			DataUser user;
			unsigned u = m_data["uids"][i].asUInt();
			logicUserBasic.GetName(u, name);
			logicUser.GetUserLimit(u, user);
			m_jsonResult["uids"][i]["uid"] = u;
			m_jsonResult["uids"][i]["name"] = name;
			m_jsonResult["uids"][i]["level"] = user.level;
			m_jsonResult["uids"][i]["kingdom"] = user.kingdom;
			m_jsonResult["uids"][i]["aid"] = user.alliance_id;
			m_jsonResult["uids"][i]["bnwm"] = user.type;
		}

		CGI_SEND_LOG("action=UserLimit&operator=%u",m_uid);
		return R_SUCCESS;
	}

	int AllianceName()
	{
		if(!m_data.isMember("aids") || !m_data["aids"].isArray())
			return R_ERR_PARAM;

		CDataAlliance da;
		for(unsigned i=0;i<m_data["aids"].size();++i)
		{
			string name;
			unsigned a = m_data["aids"][i].asUInt();
			da.GetName(a, name);
			m_jsonResult["aids"][i]["aid"] = a;
			m_jsonResult["aids"][i]["name"] = name;
		}

		CGI_SEND_LOG("action=UserLimit&operator=%u",m_uid);
		return R_SUCCESS;
	}

	int OneHero()
	{
		unsigned uid = 0, ud = 0;

		if (!Json::GetUInt(m_data, "userid", uid) || uid == 0 )
		{
			uid = m_uid;
		}

		if (!Json::GetUInt(m_data, "ud", ud) || ud == 0 )
		{
			return R_ERR_PARAM;
		}

		m_jsonResult["uid"] = uid;

		CLogicHero logicHero;
		int ret = logicHero.Get(uid, ud, m_jsonResult["hero"]);

		if(ret && R_ERR_NO_DATA != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=OneHero&operator=%u&operated=%u",m_uid,uid);
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiLoad)
