/*
 * CgiAlliance.cpp
 *
 *  Created on: 2011-9-21
 *      Author: dada
 */

#include "LogicInc.h"

class CCgiAlliance : public CCgiBase
{

public:

	CCgiAlliance() : CCgiBase("alliance")
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
	CGI_SET_ACTION_MAP("AddAlliance", AddAlliance)
	CGI_SET_ACTION_MAP("SetAlliance", SetAlliance)
	CGI_SET_ACTION_MAP("GetAlliance", GetAlliance)
	CGI_SET_ACTION_MAP("SearchAlliance", SearchAlliance)
	CGI_SET_ACTION_MAP("GetAlliances", GetAlliances)
	CGI_SET_ACTION_MAP("GetAllianceEnemys", GetAllianceEnemys)
	CGI_SET_ACTION_MAP("RemoveAlliance", RemoveAlliance)
	CGI_SET_ACTION_MAP("RemoveMember", RemoveMember)
	CGI_SET_ACTION_MAP("Donate", Donate)
	CGI_SET_ACTION_MAP("SetData", SetData)
	CGI_SET_ACTION_MAP("Upgrade", Upgrade)
	CGI_SET_ACTION_MAP("GetSuggestedUsers", GetSuggestedUsers)
	CGI_ACTION_MAP_END

	int AddAlliance()
	{
		int ret;
		string name;
		if(!Json::GetString(m_data, "name", name))
		{
			return R_ERR_PARAM;
		}
		int flag;
		if(!Json::GetInt(m_data, "flag", flag))
		{
			return R_ERR_PARAM;
		}
		string description;
		if(!Json::GetString(m_data, "desc", description))
		{
			return R_ERR_PARAM;
		}
		StringFilter::Replace(description);
		int cash = 0;
		Json::GetInt(m_data, "cash", cash);
		if(cash < 0)
		{
			return R_ERR_PARAM;
		}
		int useres = 1;
		Json::GetInt(m_data, "useres", useres);

		CLogicAlliance logicAlliance;
		DataAlliance alliance;
		ret = logicAlliance.AddAlliance(m_uid, name, flag, description, cash, useres != 0, alliance);
		if(ret != 0)
		{
			return ret;
		}
		ret = logicAlliance.GetAllianceJson(m_uid, alliance.alliance_id, m_jsonResult);
		if(ret != 0)
		{
			return ret;
		}
		CGI_SEND_LOG("action=AddAlliance&uid=%u&aid=%u&name=%s&cash=%d&useres=%d",
				m_uid, alliance.alliance_id, name.c_str(), cash, useres);
		return R_SUCCESS;
	}

	int SetAlliance()
	{
		int ret;
		unsigned allianceId;
		if(!Json::GetUInt(m_data, "aid", allianceId))
		{
			return R_ERR_PARAM;
		}
		int flag = -1;
		bool bFlag = Json::GetInt(m_data, "flag", flag);
		string desc;
		bool bDesc = Json::GetString(m_data, "desc", desc);
		string notice;
		bool bNotice = Json::GetString(m_data, "notice", notice);
		unsigned leader = 0;
		bool bLeader = Json::GetUInt(m_data, "leader", leader);
		if(!bFlag && !bDesc && !bNotice && !bLeader)
		{
			return R_ERR_PARAM;
		}

		DataAlliance alliance;
		CLogicAlliance logicAlliance;
		if(!bDesc && !bNotice)
		{
			ret = logicAlliance.GetAllianceLimit(allianceId, alliance);
		}
		else
		{
			ret = logicAlliance.GetAlliance(allianceId, alliance);
		}
		if(ret != 0)
		{
			return ret;
		}
		if(alliance.leader_uid != m_uid)
		{
			error_log("[is_not_leader][aid=%u,uid=%u,luid=%u]", allianceId, m_uid, alliance.leader_uid);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "is_not_leader");
		}
		if(bFlag)
		{
			alliance.flag = flag;
		}
		if(bDesc)
		{
			alliance.description = desc;
			StringFilter::Replace(alliance.description);
		}
		if(bNotice)
		{
			alliance.notice = notice;
			StringFilter::Replace(alliance.notice);
		}
		if(!bDesc && !bNotice)
		{
			ret = logicAlliance.SetAllianceLimit(alliance);
		}
		else
		{
			ret = logicAlliance.SetAlliance(alliance);
		}
		if(ret != 0)
		{
			return ret;
		}
		if(bLeader && leader != alliance.leader_uid)
		{
			ret = logicAlliance.ChangeLeader(allianceId, leader);
			if(ret != 0)
			{
				return ret;
			}
		}
		CGI_SEND_LOG("action=SetAlliance&uid=%u&aid=%u&flag=%d&desc=%d&notice=%d&leader=%u", m_uid, allianceId,
				flag, bDesc ? (int)desc.size() : -1, bNotice ? (int)notice.size() : -1, leader);
		return R_SUCCESS;
	}

	int GetAlliance()
	{
		int ret;
		unsigned allianceId;
		if(!Json::GetUInt(m_data, "aid", allianceId))
		{
			return R_ERR_PARAM;
		}
		CLogicAlliance logicAlliance;
		ret = logicAlliance.GetAllianceJson(m_uid, allianceId, m_jsonResult);
		if(ret != 0)
		{
			return ret;
		}
		if(IsMercenary())
		{
			CLogicMessage logicMessage;
			logicMessage.GetChatJson(allianceId, TOWARD_RECV, m_jsonResult["messages"]);
		}
		CGI_SEND_LOG("action=GetAlliance&uid=%u&aid=%u", m_uid, allianceId);
		return R_SUCCESS;
	}

	int SearchAlliance()
	{
		int ret;
		string name;
		if(!Json::GetString(m_data, "name", name))
		{
			return R_ERR_PARAM;
		}
		if(name.empty())
		{
			return R_ERR_PARAM;
		}
		CLogicAlliance logicAlliance;
		ret = logicAlliance.SearchAllianceJson(name, m_jsonResult);
		if(ret != 0)
		{
			return ret;
		}
		CGI_SEND_LOG("action=SearchAlliance&uid=%u&name=%s", m_uid, name.c_str());
		return R_SUCCESS;
	}

	int GetAlliances()
	{
		int ret;
		CLogicAlliance logicAlliance;
		ret = logicAlliance.GetRandomAlliancesJson(m_jsonResult["alliances"]);
		if(ret != 0)
		{
			return ret;
		}
		CGI_SEND_LOG("action=GetAlliances&uid=%u&count=%u", m_uid, (unsigned)m_jsonResult.size());
		return R_SUCCESS;
	}

	int GetAllianceEnemys()
	{
		int ret;
		unsigned allianceId;
		if(!Json::GetUInt(m_data, "aid", allianceId))
		{
			return R_ERR_PARAM;
		}
		unsigned startIndex;
		if(!Json::GetUInt(m_data, "start", startIndex))
		{
			return R_ERR_PARAM;
		}
		unsigned count;
		if(!Json::GetUInt(m_data, "count", count))
		{
			return R_ERR_PARAM;
		}

		CLogicAlliance logicAlliance;
		ret = logicAlliance.GetAllianceEnemys(allianceId, startIndex, count, m_jsonResult);
		if(ret != 0)
		{
			return ret;
		}
		CGI_SEND_LOG("action=GetAllianceEnemys&uid=%u&aid=%u&start=%u&count=%u&rcount=%u",
				m_uid, allianceId, startIndex, count, (unsigned)m_jsonResult["enemys"].size());
		return R_SUCCESS;
	}

	int RemoveAlliance()
	{
		int ret;
		unsigned allianceId;
		if(!Json::GetUInt(m_data, "aid", allianceId))
		{
			return R_ERR_PARAM;
		}
		DataAlliance alliance;
		CLogicAlliance logicAlliance;
		ret = logicAlliance.GetAllianceLimit(allianceId, alliance);
		if(ret != 0)
		{
			return ret;
		}
		if(alliance.leader_uid != m_uid)
		{
			error_log("[is_not_leader][aid=%u,uid=%u,luid=%u]", allianceId, m_uid, alliance.leader_uid);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "is_not_leader");
		}
		ret = logicAlliance.RemoveAlliance(allianceId);
		if(ret != 0)
		{
			return ret;
		}
		CGI_SEND_LOG("action=RemoveAlliance&uid=%u&aid=%u", m_uid, alliance.alliance_id);
		return R_SUCCESS;
	}

	int RemoveMember()
	{
		int ret;
		unsigned allianceId;
		if(!Json::GetUInt(m_data, "aid", allianceId))
		{
			return R_ERR_PARAM;
		}
		unsigned removeUid;
		if(!Json::GetUInt(m_data, "remove", removeUid))
		{
			return R_ERR_PARAM;
		}
		DataUser userRemove;
		ret = LogicUser::GetUser(removeUid, userRemove);
		if(ret != 0)
		{
			return ret;
		}
		if(userRemove.alliance_id != allianceId)
		{
			return R_ERR_PARAM;
		}
		CLogicAlliance logicAlliance;
		DataAlliance alliance;
		if(removeUid != m_uid)
		{
			ret = logicAlliance.GetAllianceLimit(allianceId, alliance);
			if(ret != 0)
			{
				return ret;
			}
			if(alliance.leader_uid != m_uid)
			{
				error_log("[is_not_leader][aid=%u,uid=%u,luid=%u]", allianceId, m_uid, alliance.leader_uid);
				ERROR_RETURN_MSG(R_ERR_LOGIC, "is_not_leader");
			}
		}
		ret = logicAlliance.RemoveMember(allianceId, removeUid);
		if(ret != 0)
		{
			return ret;
		}

		//消息通知
		DataUserBasic userBasicRemove;
		ret = LogicUserBasic::GetUserSmart(removeUid, OpenPlatform::GetType(), userBasicRemove);
		if(ret == 0)
		{
			Json::Value activity;
			if(removeUid == m_uid)
			{
				activity["type"] = "exit";
			}
			else
			{
				activity["type"] = "remove";
			}
			activity["time"] = Time::GetGlobalTime();
			activity["name"] = userBasicRemove.name;
			logicAlliance.AddActivity(allianceId, activity);

			if(removeUid != m_uid)
			{
				string message;
				String::Format(message, "{\"id\":\"alliance_remove_member\",\"name\":\"%s\"}", alliance.name.c_str());
				CLogicMessage logicMessage;
				logicMessage.AddSysMessage(removeUid, message);
			}
		}

		CGI_SEND_LOG("action=RemoveMember&uid=%u&aid=%u&ruid=%u", m_uid, allianceId, removeUid);
		return R_SUCCESS;
	}

	int Donate()
	{
		int ret;
		unsigned allianceId;
		if(!Json::GetUInt(m_data, "aid", allianceId))
		{
			return R_ERR_PARAM;
		}
		unsigned r1;
		unsigned r2;
		unsigned r3;
		unsigned r4;
		if( !Json::GetUInt(m_data, "r1", r1) ||
			!Json::GetUInt(m_data, "r2", r2) ||
			!Json::GetUInt(m_data, "r3", r3) ||
			!Json::GetUInt(m_data, "r4", r4) )
		{
			return R_ERR_PARAM;
		}
		unsigned cash;
		if(!Json::GetUInt(m_data, "cash", cash))
		{
			return R_ERR_PARAM;
		}
		CLogicAlliance logicAlliance;
		ret = logicAlliance.Donate(m_uid, allianceId, r1, r2, r3, r4, cash);
		if(ret != 0)
		{
			return ret;
		}
		CGI_SEND_LOG("action=Donate&uid=%u&aid=%u&r1=%u&r2=%u&r3=%u&r4=%u&cash=%u",
				m_uid, allianceId, r1, r2, r3, r4, cash);
		return R_SUCCESS;
	}

	int SetData()
	{
		int ret;
		unsigned allianceId;
		if(!Json::GetUInt(m_data, "aid", allianceId))
		{
			return R_ERR_PARAM;
		}
		CLogicAlliance logicAlliance;
		if(Json::IsObject(m_data, "resource"))
		{
			Json::Value &resource = m_data["resource"];
			int r1 = 0;
			int r2 = 0;
			int r3 = 0;
			int r4 = 0;
			int cash = 0;
			Json::GetInt(resource, "r1", r1);
			Json::GetInt(resource, "r2", r2);
			Json::GetInt(resource, "r3", r3);
			Json::GetInt(resource, "r4", r4);
			Json::GetInt(resource, "cash", cash);
			if(r1 > 0 || r2 > 0 || r3 > 0 || r4 > 0 || cash > 0)
			{
				error_log("[change_resource_error][uid=%u,r1=%d,r2=%d,r3=%d,r4=%d,cash=%d]",  m_uid, r1, r2, r3, r4, cash);
				return R_ERR_PARAM;
			}
			if(r1 != 0 || r2 != 0 || r3 != 0 || r4 != 0 || cash != 0)
			{
				if(!logicAlliance.IsLeader(m_uid, allianceId))
				{
					error_log("[is_not_leader][aid=%u,uid=%u]", allianceId, m_uid);
					ERROR_RETURN_MSG(R_ERR_LOGIC, "is_not_leader");
				}
				ret  = logicAlliance.ChangeResource(allianceId, r1, r2, r3, r4, cash, "ALUSE");
				if(ret != 0)
				{
					return ret;
				}
			}
		}
		if(Json::IsObjectOrArray(m_data, "memberdata"))
		{
			ret = logicAlliance.SetMemberData(m_uid, allianceId, m_data["memberdata"]);
			if(ret != 0)
			{
				return ret;
			}
		}
		if(Json::IsObjectOrArray(m_data, "alliancedata"))
		{
			ret = logicAlliance.SetAllianceData(m_uid, allianceId, m_data["alliancedata"]);
			if(ret != 0)
			{
				return ret;
			}
			if(Json::IsObject(m_data, "activity"))
			{
				ret = logicAlliance.AddActivity(allianceId, m_data["activity"]);
				if(ret != 0)
				{
					return ret;
				}
			}
		}
		CGI_SEND_LOG("action=SetData&uid=%u&allianceId=%u", m_uid, allianceId);
		return 0;
	}

	int Upgrade()
	{
		int ret;
		unsigned allianceId;
		if(!Json::GetUInt(m_data, "aid", allianceId))
		{
			return R_ERR_PARAM;
		}
		unsigned r1;
		unsigned r2;
		unsigned r3;
		unsigned r4;
		if( !Json::GetUInt(m_data, "r1", r1) ||
			!Json::GetUInt(m_data, "r2", r2) ||
			!Json::GetUInt(m_data, "r3", r3) ||
			!Json::GetUInt(m_data, "r4", r4) )
		{
			return R_ERR_PARAM;
		}
		unsigned cash;
		if(!Json::GetUInt(m_data, "cash", cash))
		{
			return R_ERR_PARAM;
		}
		int level;
		if(!Json::GetInt(m_data, "level", level))
		{
			return R_ERR_PARAM;
		}
		CLogicAlliance logicAlliance;
		ret = logicAlliance.Upgrade(m_uid, allianceId, r1, r2, r3, r4, cash, level);
		if(ret != 0)
		{
			return ret;
		}
		m_jsonResult["level"] = level;
		CGI_SEND_LOG("action=Upgrade&uid=%u&aid=%u&r1=%u&r2=%u&r3=%u&r4=%u&cash=%u&newlevel=%d",
				m_uid, allianceId, r1, r2, r3, r4, cash, level);
		return R_SUCCESS;
	}

	int GetSuggestedUsers()
	{
		int ret;
		unsigned allianceId;
		int count;
		if(!Json::GetUInt(m_data, "aid", allianceId) ||
			!Json::GetInt(m_data, "count", count))
		{
			return R_ERR_PARAM;
		}
		CLogicAlliance logicAlliance;
		ret = logicAlliance.GetSuggestedUsers(m_uid, allianceId, count, m_jsonResult["users"]);
		if(ret != 0)
		{
			return ret;
		}
		CGI_SEND_LOG("action=GetSuggestedUsers&uid=%u&aid=%u&count=%d&rcount=%u",
				m_uid, allianceId, count, m_jsonResult["users"].size());
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiAlliance)

