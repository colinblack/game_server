/*
 * CgiAdmin.cpp
 *
 *  Created on: 2011-7-7
 *      Author: dada
 */

#include "LogicInc.h"

class CCgiAdmin : public CCgiBase
{

public:

	CCgiAdmin() : CCgiBase("admin")
	{
		m_lastUpateTime = 0;
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
	}

	CGI_SIMPLE_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("login", Login)
	CGI_SET_ACTION_MAP("getarchive", GetArchive)
	CGI_SET_ACTION_MAP("setarchive", SetArchive)
	CGI_SET_ACTION_MAP("changeresource", ChangeResource)
	CGI_SET_ACTION_MAP("changecash", ChangeCash)
	CGI_SET_ACTION_MAP("getcashflows", GetCashFlows)
	CGI_SET_ACTION_MAP("getinventory", GetInventory)
	CGI_SET_ACTION_MAP("changeinventory", ChangeInventory)
	CGI_SET_ACTION_MAP("blockuser", BlockUser)
	CGI_ACTION_MAP_END

	int Login()
	{
		string name = CCGIIn::GetCGIStr("name");
		string password = CCGIIn::GetCGIStr("password");
		if(name.empty() || password.empty())
		{
			error_log("[auth error][ip=%u,name=%s,password=%s]", m_remoteip, name.c_str(), password.c_str());
			return R_ERR_AUTH;
		}
		static unsigned s_nextUpdateTime = 0;
		if(Time::GetGlobalTime() > s_nextUpdateTime)
		{
			m_adminList.clear();
			s_nextUpdateTime = CTime::GetDayBeginTime(Time::GetGlobalTime()) + 30 * 60;

			string sAdminListPath;
			if(!Config::GetValue(sAdminListPath, CONFIG_ADMIN_LIST))
			{
				fatal_log("[config_not_exist][name=admin_list]");
				return R_ERR_AUTH;
			}
			string data;
			if(File::Read(sAdminListPath, data) != 0)
			{
				fatal_log("[admin_list_not_exist][path=%s]", sAdminListPath.c_str());
			}
			vector<string> whiteList;
			CBasic::StringSplitTrim(data, "\n", whiteList);
			for(vector<string>::iterator itr = whiteList.begin(); itr != whiteList.end(); itr++)
			{
				vector<string> whiteItems;
				CBasic::StringSplitTrim(*itr, ":", whiteItems);
				if(whiteItems.size() >= 2)
				{
					m_adminList[whiteItems[0]] = whiteItems[1];
				}
				else
				{
					error_log("[invalid_admin_list_item][data=%s]", itr->c_str());
				}
			}
		}

		map<string, string>::iterator itrFind;
		itrFind = m_adminList.find(name);
		if(itrFind == m_adminList.end())
		{
			error_log("[user not found][ip=%u,name=%s,password=%s]", m_remoteip, name.c_str(), password.c_str());
			return R_ERR_AUTH;
		}
		if(itrFind->second != password)
		{
			error_log("[auth error][ip=%u,name=%s,password=%s]", m_remoteip, name.c_str(), password.c_str());
			return R_ERR_AUTH;
		}
		string skey = Session::CreateSessionKey(0);
		m_session[name] = skey;
		m_jsonResult["skey"] = skey;
		info_log("[admin login][ip=%u,name=%s,skey=%s]", m_remoteip, name.c_str(), skey.c_str());
		CGI_SEND_LOG("action=login&ip=%u&name=%s&skey=%s", m_remoteip, name.c_str(), skey.c_str());
		return R_SUCCESS;
	}

	int GetArchive()
	{
		if(!CheckSession())
		{
			return R_ERR_SESSION;
		}

		int ret;
		int platform = 0;
		unsigned uid = 0;
		ret = GetUser(uid, platform);
		if(ret != 0)
		{
			return ret;
		}

		string sBaseId = CCGIIn::GetCGIStr("baseid");
		unsigned baseid = 0;
		if(!Convert::StringToUInt(baseid, sBaseId))
		{
			return R_ERR_PARAM;
		}

		Json::Value archive;
		CLogicArchive logicArchive;
		int result = logicArchive.GetArchive((PlatformType)platform, uid, baseid, archive);
		if(result != 0)
		{
			return result;
		}
		m_jsonResult["archive"] = Json::FastWriter().write(archive);

		CGI_SEND_LOG("action=getarchive&userid=%u&baseid=%u", uid, baseid);
		return R_SUCCESS;
	}

	int SetArchive()
	{
		if(!CheckSession())
		{
			return R_ERR_SESSION;
		}

		int ret;
		int platform = 0;
		unsigned uid = 0;
		ret = GetUser(uid, platform);
		if(ret != 0)
		{
			return ret;
		}

		string sBaseId = CCGIIn::GetCGIStr("baseid");
		unsigned baseid = 0;
		if(!Convert::StringToUInt(baseid, sBaseId))
		{
			return R_ERR_PARAM;
		}

		string sArchive = CCGIIn::GetCGIStr("archive");
		Json::Value archive;
		if(!Json::FromString(archive, sArchive))
		{
			return R_ERR_PARAM;
		}

		CLogicArchive logicArchive;
		int result = logicArchive.SetArchive((PlatformType)platform, uid, baseid, archive);
		if(result != 0)
		{
			return result;
		}

		string reason = CCGIIn::GetCGIStr("reason");
		info_log("[admin_change_archive][admin=%s,userid=%u,reason=%s]",
				m_adminName.c_str(), uid, reason.c_str());
		CGI_SEND_LOG("action=setarchive&admin=%s&userid=%u&reason=%s", m_adminName.c_str(), uid, reason.c_str());
		return R_SUCCESS;
	}

	int ChangeResource()
	{
		if(!CheckSession())
		{
			return R_ERR_SESSION;
		}

		int ret;
		int platform = 0;
		unsigned uid = 0;
		ret = GetUser(uid, platform);
		if(ret != 0)
		{
			return ret;
		}

		int r1 = CCGIIn::GetCGIInt("r1");
		int r2 = CCGIIn::GetCGIInt("r2");
		int r3 = CCGIIn::GetCGIInt("r3");
		int r4 = CCGIIn::GetCGIInt("r4");
		if(r1 == CCGIIn::CGI_INT_ERR ||
			r2 == CCGIIn::CGI_INT_ERR ||
			r3 == CCGIIn::CGI_INT_ERR ||
			r4 == CCGIIn::CGI_INT_ERR)
		{
			return R_ERR_PARAM;
		}

		ret = LogicUser::ChangeResource(uid, r1, r2, r3, r4);
		if(ret != 0)
		{
			return ret;
		}

		string reason = CCGIIn::GetCGIStr("reason");
		info_log("[admin_change_resource][admin=%s,userid=%u,r1=%d,r2=%d,r3=%d,r4=%d,reason=%s]",
				m_adminName.c_str(), uid, r1, r2, r3, r4, reason.c_str());
		CGI_SEND_LOG("action=changeresource&admin=%s&userid=%u&r1=%d&r2=%d&r3=%d&r4=%d&reason=%s",
				m_adminName.c_str(), uid, r1, r2, r3, r4, reason.c_str());
		return R_SUCCESS;
	}

	int ChangeCash()
	{
		if(!CheckSession())
		{
			return R_ERR_SESSION;
		}

		int ret;
		int platform = 0;
		unsigned uid = 0;
		ret = GetUser(uid, platform);
		if(ret != 0)
		{
			return ret;
		}

		int delta = CCGIIn::GetCGIInt("cash");
		if(delta == CCGIIn::CGI_INT_ERR)
		{
			return R_ERR_PARAM;
		}

		CLogicPay logicPay;
		unsigned cash;
		ret = logicPay.ChangeCash(uid, "ADMIN", delta, 1, 0, cash);
		if(ret != 0)
		{
			return ret;
		}

		m_jsonResult["cash"] = cash;

		string reason = CCGIIn::GetCGIStr("reason");
		info_log("[admin_change_cash][admin=%s,userid=%u,delta=%d,reason=%s,balance=%u]",
				m_adminName.c_str(), uid, delta, reason.c_str(), cash);
		CGI_SEND_LOG("action=changecash&admin=%s&userid=%u&delta=%d&reason=%s&balance=%d",
				m_adminName.c_str(), uid, delta, reason.c_str(), cash);
		return R_SUCCESS;
	}

	int GetCashFlows()
	{
		if(!CheckSession())
		{
			return R_ERR_SESSION;
		}

		int ret;
		int platform = 0;
		unsigned uid = 0;
		ret = GetUser(uid, platform);
		if(ret != 0)
		{
			return ret;
		}

		int start = CCGIIn::GetCGIInt("start");
		int end = CCGIIn::GetCGIInt("end");
		if(start == CCGIIn::CGI_INT_ERR || start < 0)
		{
			start = 0;
		}
		if(end == CCGIIn::CGI_INT_ERR || end < 0)
		{
			end = 0;
		}

		CLogicPay logicPay;
		vector<DataCashFlow> flows;
		ret = logicPay.GetCashFlows(uid, start, end, flows);
		if(ret != 0)
		{
			return ret;
		}
		m_jsonResult["userid"] = uid;
		Json::Value &flowsData = m_jsonResult["flows"];
		for(vector<DataCashFlow>::iterator itr = flows.begin(); itr != flows.end(); itr++)
		{
			Json::Value &flow = flowsData[flowsData.size()];
			flow["flowid"] = Convert::UInt64ToString(itr->flow_id);
			flow["type"] = itr->type;
			flow["count"] = itr->count;
			flow["cash"] = itr->cash;
			flow["balance"] = itr->balance;
			flow["time"] = itr->time;
			flow["data"] = itr->data;
		}
		CGI_SEND_LOG("action=getcashflows&admin=%s&userid=%u&start=%u&end=%u&count=%u",
				m_adminName.c_str(), uid, start, end, (unsigned)flows.size());
		return R_SUCCESS;
	}

	int GetInventory()
	{
		if(!CheckSession())
		{
			return R_ERR_SESSION;
		}
		int ret;
		int platform = 0;
		unsigned uid = 0;
		ret = GetUser(uid, platform);
		if(ret != 0)
		{
			return ret;
		}
		CLogicInventory logicInventory;
		CHECK_CALL(logicInventory.GetItemsJson(uid, m_jsonResult["inventory"]));
		CGI_SEND_LOG("action=getinventory&admin=%s&userid=%u", m_adminName.c_str(), uid);
		return R_SUCCESS;
	}

	int ChangeInventory()
	{
		if(!CheckSession())
		{
			return R_ERR_SESSION;
		}
		int ret;
		int platform = 0;
		unsigned uid = 0;
		ret = GetUser(uid, platform);
		if(ret != 0)
		{
			return ret;
		}
		string type = CCGIIn::GetCGIStr("type");
		int count = CCGIIn::GetCGIInt("count");
		if(type.empty() || count == CCGIIn::CGI_INT_ERR)
		{
			return R_ERR_PARAM;
		}
		CLogicInventory logicInventory;
		CHECK_CALL(logicInventory.ChangeItem(uid, type, count));
		string reason = CCGIIn::GetCGIStr("reason");
		info_log("[admin_change_inventory][admin=%s,userid=%u,type=%s,count=%d,reason=%s]",
				m_adminName.c_str(), uid, type.c_str(), count, reason.c_str());
		CHECK_CALL(logicInventory.GetItemsJson(uid, m_jsonResult["inventory"]));
		CGI_SEND_LOG("action=changeinventory&admin=%s&userid=%u&type=%s&count=%d&reason=%s",
				m_adminName.c_str(), uid, type.c_str(), count, reason.c_str());
		return R_SUCCESS;
	}

	int BlockUser()
	{
		if(!CheckSession())
		{
			return R_ERR_SESSION;
		}
		int ret;
		unsigned uid = 0;
		int platform = 0;
		ret = GetUser(uid, platform);
		if(ret != 0)
		{
			return ret;
		}
		string type = CCGIIn::GetCGIStr("type");
		CDataUser userDb;
		if (type == "block")
			ret = userDb.SetStatus(uid, US_BAN);
		else if (type == "active")
			ret = userDb.SetStatus(uid, US_ACTIVE);
		else
			return R_ERR_PARAM;
		if (ret != 0)
			return ret;
		string reason = CCGIIn::GetCGIStr("reason");
		CGI_SEND_LOG("action=blockuser&admin=%s&userid=%u&type=%s&reason=%s",
				m_adminName.c_str(), uid, type.c_str(), reason.c_str());
		return R_SUCCESS;
	}

protected:

	bool CheckSession()
	{
		string name = CCGIIn::GetCGIStr("name");
		string skey = CCGIIn::GetCGIStr("skey");
		if(name.empty() || skey.empty())
		{
			error_log("[admin_session_error][error=param_error,ip=%u,nname=%s,skey=%s]",
					m_remoteip, name.c_str(), skey.c_str());
			return false;
		}
		map<string, string>::iterator itrFind;
		itrFind = m_session.find(name);
		if(itrFind == m_session.end())
		{
			error_log("[admin_session_error][error=name_not_exist,ip=%u,nname=%s,skey=%s]",
					m_remoteip, name.c_str(), skey.c_str());
			return false;
		}
		if(itrFind->second != skey)
		{
			error_log("[admin_session_error][error=key_not_match,ip=%u,name=%s,skey=%s,real_skey=%s]",
					m_remoteip, name.c_str(), skey.c_str(), itrFind->second.c_str());
			return false;
		}
		m_adminName = name;
		return true;
	}

	int GetUser(unsigned &uid, int &platform)
	{
		platform = CCGIIn::GetCGIInt("platform");
		if(platform == CCGIIn::CGI_INT_ERR)
		{
			return R_ERR_PARAM;
		}
		string sUid = CCGIIn::GetCGIStr("userid");
		if(!Convert::StringToUInt(uid, sUid))
		{
			string openid = CCGIIn::GetCGIStr("openid");
			int ret = LogicUserBasic::GetUid(uid, (PlatformType)platform, openid);
			return ret;
		}
		return 0;
	}

private:
	unsigned m_lastUpateTime;
	map<string, string> m_adminList;
	map<string, string> m_session;
	string m_adminName;

};

CGI_MAIN(CCgiAdmin)

