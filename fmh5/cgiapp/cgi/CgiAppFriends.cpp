
#include "LogicInc.h"

class CCgiAppFriends : public CCgiBase
{
public:

	CCgiAppFriends() : CCgiBase("appfriends")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(AppFriends)

	int AppFriends()
	{
		string openid = CCGIIn::GetCGIStr("openid");
		string openkey = CCGIIn::GetCGIStr("openkey");
		string pf = CCGIIn::GetCGIStr("pf");
		int serverid = CCGIIn::GetCGIInt("serverid", 0, 100000, 0, 0);
		map<string, string> params;
		params["pf"] = pf;
		params["userip"] = m_ipstr;
		OpenPlatform::GetPlatform()->SetParameter(params);
		OPFriendList friendList;
		int ret = OpenPlatform::GetPlatform()->GetAppFriendList(friendList, openid, openkey);
		if(ret != 0)
		{
			error_log("[GetAppFriendList fail][ret=%d,openid=%s,openkey=%s]",
					ret,openid.c_str(),openkey.c_str());
		}
		CDataUserMapping dbUserMapping;
		m_jsonResult["friends"].resize(0);
		for (OPFriendList::const_iterator it = friendList.begin(); it != friendList.end(); it++)
		{
			ConfigManager::Instance()->SetServer(serverid);
			if (*it == openid)
				continue;
			unsigned fid = 0;
			dbUserMapping.GetMapping(*it, 0, fid);
			if(fid)
			{
				Json::Value t;
				t["openid"] = *it;
				t["uid"] = fid;
				m_jsonResult["friends"].append(t);
			}
		}
		CGI_SEND_LOG("operator=%s", openid.c_str());

		return R_SUCCESS;
	}
};

CGI_MAIN(CCgiAppFriends)
