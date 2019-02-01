/*
 * CgiBaiduAdmin.cpp
 *
 *  Created on: 2015-12-13
 *      Author: zkw
 */


#include "LogicInc.h"
#include "StringUtil.h"

class CCgiBaiduAdmin : public CCgiBase
{
public:
	CCgiBaiduAdmin() : CCgiBase("baiduadmin")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(QueryUser)

	int QueryUser()
	{
		const string openid = CCGIIn::GetCGIStr("user_id");
		const string serverid_s = CCGIIn::GetCGIStr("server_id");
		const string time_s = CCGIIn::GetCGIStr("timestamp");
		const string sign = CCGIIn::GetCGIStr("sign");

		Json::Value result_wrong;
		result_wrong["errCode"] = "";
		result_wrong["errMsg"] = "";
		Json::Value result_right;
		result_right["userInfo"][0u]["roleName"] = "";
		result_right["userInfo"][0u]["roleLevel"] = 0;
		result_right["userInfo"][0u]["onlineTime"] = 0;

		if(openid.empty() || serverid_s.empty() || time_s.empty() || sign.empty())
		{
			result_wrong["errCode"] = "ERROR_-100";
			result_wrong["errMsg"] = "传入参数不符合规则";
			PrintResult(result_wrong);
			return -1;
		}
		string osig  = OpenPlatform::GetPlatform()->GetAppKey()
				       + "api_key" + OpenPlatform::GetPlatform()->GetAppId()
				       + "server_id" + serverid_s
				       + "timestamp" + time_s
				       + "user_id" + openid;
		string sig = Crypt::Md5Encode(osig);   //加密后 要求是 大写
		String::ToUpper(sig);
		if(sig != sign)
		{
			result_wrong["errCode"] = "ERROR_-100";
			result_wrong["errMsg"] = "传入参数不符合规则";
			PrintResult(result_wrong);
			return  -1;
		}

		// Get uid
		int serverid = 0;
		Config::GetDB(serverid);             //不知道这样做对不对
		CDataUserMapping userMapper;
		unsigned uid = 0;
		int ret = userMapper.GetUID(openid, serverid, uid);
		if (ret != 0)
		{
			result_wrong["errCode"] = "ERROR_-1406";
			result_wrong["errMsg"] = "角色不存在";
			PrintResult(result_wrong);
			return ret;
		}

		// Get User Info
		DataUser user;
		CLogicUser logicUser;
		ret = logicUser.GetUserLimit(uid, user);
		if(ret != 0)
		{
			result_wrong["errCode"] = "ERROR_-1406";
			result_wrong["errMsg"] = "角色不存在";
			PrintResult(result_wrong);
			return ret;
		}
		result_right["userInfo"][0u]["roleLevel"] = user.level;
		result_right["userInfo"][0u]["onlineTime"] = int((user.last_active_time - user.last_login_time)/60);

		string userName;
		CDataUserBasic dbUser;
		dbUser.GetUserName(uid, OpenPlatform::GetType(), userName);
		result_right["userInfo"][0u]["roleName"] = userName;
		PrintResult(result_right);

		return 0;
	}

private:
	void PrintResult(Json::Value &result)
	{
		Json::FastWriter writer;
		string res = writer.write(result);
		CgiUtil::PrintText(res.c_str());
	}
};

CGI_MAIN(CCgiBaiduAdmin)




