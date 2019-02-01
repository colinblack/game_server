/*
 * CgiThunderAdmin.cpp
 *
 *  Created on: 2017-3-28
 *      Author: dawx62fac
 */

/*
 * CgiC9Admin.cpp
 *
 *  Created on: 2015-8-26
 *      Author: Ralf
 */


#include "LogicInc.h"

class CCgiAdminThunder : public CCgiBase
{
public:
	CCgiAdminThunder() : CCgiBase("thunder_admin")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(Impl)

	int Impl()
	{
		std::string game_id = CCGIIn::GetCGIStr("gameid");
		int server_id = CCGIIn::GetCGIInt("serverid");
		std::string open_id = CCGIIn::GetCGIStr("userid");
		std::string role_name = Crypt::UrlDecode(CCGIIn::GetCGIStr("rolename"));
		int target = CCGIIn::GetCGIInt("target");
		int event = CCGIIn::GetCGIInt("event");
		int type = CCGIIn::GetCGIInt("type");
		int keep_time = CCGIIn::GetCGIInt("keeptime");
		int time = CCGIIn::GetCGIInt("time");
		std::string sign = CCGIIn::GetCGIStr("sign");


		Json::Value result;
		if(open_id.empty() || sign.empty() || time == CCGIIn::CGI_INT_ERR)
		{
			result["status"] = -1;
			error_log("open_id or sign or time is empty");
			return PrintResult(result);
		}

		if (type != 0 && type != 1)
		{
			result["status"] = -1;
			error_log("type params error");
			return PrintResult(result);
		}

		if (event != 1 && event != 2)
		{
			result["status"] = -1;
			error_log("status params error");
			return PrintResult(result);
		}

		if (Math::Abs(Time::GetGlobalTime() - time) > 180)
		{
			result["status"] = -1;
			error_log("time params error");
			return PrintResult(result);
		}

		string osig  = game_id
				+ server_id
				+ open_id
				+ role_name
				+ CTrans::ITOS(target)
				+ CTrans::ITOS(event)
				+ CTrans::ITOS(type)
				+ CTrans::ITOS(keep_time)
				+ CTrans::ITOS(time)
				+ OpenPlatform::GetPlatform()->GetAppKey();
		string sig = Crypt::Md5Encode(osig);
		if(sig != sign)
		{
			result["status"] = -1;
			error_log("check sign error");
			return PrintResult(result);
		}

		// Get uid
		CDataUserMapping userMapper;
		unsigned uid = 0;
		int ret = userMapper.GetUID(open_id, server_id, uid);
		if (ret != 0)
		{
			result["status"] = -1;
			error_log("not exist user. open_id: %s, serer_id: %d", open_id.c_str(), server_id);
			return PrintResult(result);
		}

		//
		if (type == 1 && keep_time == 0)
		{
			keep_time = 0x7fffffff;
		}

		if (event == 1)
		{
			//禁言
			ret = CLogicAdmin().AddForbidUser(uid, keep_time, CTrans::ITOS(server_id));
		}
		else
		{
			ret = CLogicAdmin().ChangeBlockTs(uid, keep_time, "xunlei");
		}

		result["status"] = 0;
		return PrintResult(result);
	}

private:

	int PrintResult(const Json::Value &result)
	{
		Json::FastWriter writer;
		string res = writer.write(result);
		CgiUtil::PrintText(res.c_str());

		unsigned ret = 0;
		Json::GetUInt(result,"status",ret);
		return ret;
	}
};

CGI_MAIN(CCgiAdminThunder)







