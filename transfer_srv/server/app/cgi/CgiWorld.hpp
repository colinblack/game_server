/*
 * CgiWorld.hpp
 *
 *  Created on: 2012-4-19
 *      Author: dada
 */

#include "LogicInc.h"

class CCgiWorld : public CCgiBase
{

public:

	CCgiWorld() : CCgiBase("world")
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
	CGI_SET_ACTION_MAP("AddUser", AddUser)
	CGI_SET_ACTION_MAP("RemoveUser", RemoveUser)
	CGI_SET_ACTION_MAP("GetBases", GetBases)
	CGI_SET_ACTION_MAP("OccupyBase", OccupyBase)
	CGI_SET_ACTION_MAP("MoveBase", MoveBase)
	CGI_SET_ACTION_MAP("SetMilitary", SetMilitary)
	CGI_SET_ACTION_MAP("SetBookmark", SetBookmark)
	CGI_SET_ACTION_MAP("InviteMove", InviteMove)
	CGI_SET_ACTION_MAP("AcceptMove", AcceptMove)
	CGI_ACTION_MAP_END

	int AddUser()
	{
		int ret;
		CWorldPoint point;
		ret = LogicWorld::AddUser(m_uid, point);
		if(ret != 0)
		{
			return ret;
		}
		m_jsonResult["world"] = point.World;
		m_jsonResult["x"] = point.X;
		m_jsonResult["y"] = point.Y;
		CGI_SEND_LOG("action=AddUser&uid=%u&world=%u&x=%d&y=%d", m_uid, point.World, point.X, point.Y);
		return 0;
	}

	int RemoveUser()
	{
		int ret;
		ret = LogicWorld::RemoveUser(m_uid);
		if(ret != 0)
		{
			return ret;
		}
		CGI_SEND_LOG("action=RemoveUser&uid=%u", m_uid);
		return 0;
	}

	int GetBases()
	{
		int ret;
		if(!Json::IsArray(m_data, "positions"))
		{
			PARAM_ERROR_RETURN();
		}
		ret = LogicWorld::GetBasesJson(m_uid, m_data["positions"], m_jsonResult);
		if(ret != 0)
		{
			return ret;
		}
		CGI_SEND_LOG("action=GetBases&uid=%u&bases=%d", m_uid, m_data["positions"].size());
		return 0;
	}

	int OccupyBase()
	{
		int ret;
		unsigned baseid;
		if(!Json::GetUInt(m_data, "baseid", baseid))
		{
			PARAM_ERROR_RETURN();
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
			PARAM_ERROR_RETURN();
		}
		unsigned cash;
		if(!Json::GetUInt(m_data, "cash", cash))
		{
			PARAM_ERROR_RETURN();
		}
		ret = LogicWorld::OccupyBase(m_uid, baseid, r1, r2, r3, r4, cash);
		if(ret != 0)
		{
			return ret;
		}
		CGI_SEND_LOG("action=OccupyBase&uid=%u&baseid=%u&r1=%u&r2=%u&r3=%u&r4=%u&cash=%u",
				m_uid, baseid, r1, r2, r3, r4, cash);
		return 0;
	}

	int MoveBase()
	{
		int ret;
		unsigned baseid;
		if(!Json::GetUInt(m_data, "baseid", baseid))
		{
			PARAM_ERROR_RETURN();
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
			PARAM_ERROR_RETURN();
		}
		unsigned cash;
		if(!Json::GetUInt(m_data, "cash", cash))
		{
			PARAM_ERROR_RETURN();
		}
		ret = LogicWorld::MoveBase(m_uid, baseid, r1, r2, r3, r4, cash);
		if(ret != 0)
		{
			return ret;
		}
		CGI_SEND_LOG("action=MoveBase&uid=%u&baseid=%u&r1=%u&r2=%u&r3=%u&r4=%u&cash=%u",
				m_uid, baseid, r1, r2, r3, r4, cash);
		return 0;
	}

	int SetMilitary()
	{
		if(!Json::IsArray(m_data, "data"))
		{
			PARAM_ERROR_RETURN();
		}
		int ret;
		int world;
		CHECK_CALL(LogicUser::GetWorld(m_uid, world));
		if(world == 0)
		{
			error_log("[not_in_world][uid=%u]", m_uid);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "not_in_world");
		}
		CHECK_CALL(LogicBase::UpdateMilitary(m_uid, m_data["data"]));
		CGI_SEND_LOG("action=SetMilitary&uid=%u", m_uid);
		return 0;
	}

	int SetBookmark()
	{
		int ret;
		if(!m_data.isMember("bookmarks"))
		{
			PARAM_ERROR_RETURN();
		}
		CHECK_CALL(LogicUser::SetBookmark(m_uid, m_data["bookmarks"]));
		CGI_SEND_LOG("action=SetBookmark&uid=%u", m_uid);
		return 0;
	}

	int InviteMove()
	{
		int ret;
		unsigned toUid;
		unsigned baseid;
		if(!Json::GetUInt(m_data, "to", toUid) ||
				!Json::GetUInt(m_data, "baseid", baseid))
		{
			PARAM_ERROR_RETURN();
		}
		uint64_t inviteId = 0;
		CHECK_CALL(LogicWorld::InviteMove(inviteId, m_uid, toUid, baseid));
		m_jsonResult["inviteid"] = Convert::UInt64ToString(inviteId);
		CGI_SEND_LOG("action=InviteMove&uid=%u&to=%u&baseid=%u&inviteid=%llu", m_uid, toUid, baseid, inviteId);
		return 0;
	}

	int AcceptMove()
	{
		int ret;
		uint64_t inviteId;
		if(!Json::GetUInt64(m_data, "inviteid", inviteId))
		{
			PARAM_ERROR_RETURN();
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
			PARAM_ERROR_RETURN();
		}
		unsigned cash;
		if(!Json::GetUInt(m_data, "cash", cash))
		{
			PARAM_ERROR_RETURN();
		}
		CHECK_CALL(LogicWorld::AcceptMove(m_uid, inviteId, r1, r2, r3, r4, cash));
		CGI_SEND_LOG("action=InviteMove&uid=%u&inviteid=%llu&r1=%u&r2=%u&r3=%u&r4=%u&cash=%u",
				m_uid, inviteId, r1, r2, r3, r4, cash);
		return 0;
	}

};

CGI_MAIN(CCgiWorld)
