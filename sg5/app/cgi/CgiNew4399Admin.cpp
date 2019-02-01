/*
 * CgiNew4399Admin.cpp
 *
 *  Created on: 2017-3-28
 *      Author: Ralf
 */




#include "LogicInc.h"

#define MD5KEY OpenPlatform::GetPlatform()->GetConfig(CONFIG_4399_OTHER_KEY)
#define TIMEOUT 120     //验证超时时间为120s

class CCgiNew4399Admin : public CCgiBase
{
public:
	CCgiNew4399Admin() : CCgiBase("4399admin")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_SIMPLE_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("QueryUser", QueryUser)
	CGI_SET_ACTION_MAP("QueryOrder", QueryOrder)
	CGI_SET_ACTION_MAP("QueryOnline", QueryOnline)
	CGI_ACTION_MAP_END

	int QueryUser()
	{
		Json::FastWriter writer;

		string openid = Crypt::UrlDecode(CCGIIn::GetCGIStr("username"));
		int time = CCGIIn::GetCGIInt("time");
		int serverid = CCGIIn::GetCGIInt("serverid");
		string flag = CCGIIn::GetCGIStr("flag");

		string md5String = Crypt::Md5Encode(openid + CTrans::ITOS(serverid) + CTrans::ITOS(time) + MD5KEY);
		if (md5String != flag)
		{
			CgiUtil::PrintText("5");
			PARAM_ERROR_RETURN_MSG("flag_error");
		}

		CDataUserMapping userMapper;
		unsigned uid = 0;
		int ret = userMapper.GetUID(openid, serverid, uid);
		if (ret != 0)
		{
			CgiUtil::PrintText("2");
			PARAM_ERROR_RETURN_MSG("user_error");
		}

		DataUser user;
		CLogicUser logicUser;
		ret = logicUser.GetUserLimit(uid, user);
		if(ret)
		{
			CgiUtil::PrintText("0");
			PARAM_ERROR_RETURN_MSG("user_error");
		}

		CLogicPay logicPay;
		DataPay pay;
		ret = logicPay.GetPay(uid, pay);
		if(ret != 0)
		{
			CgiUtil::PrintText("0");
			PARAM_ERROR_RETURN_MSG("user_error");
		}

		string userName;
		CDataUserBasic dbUser;
		dbUser.GetUserName(uid, OpenPlatform::GetType(), userName);

		Json::Value result;
		result["userid"] = openid;
		result["nickname"] = userName;
		result["level"] = user.level;
		result["money"]["normal"] = pay.cash;
		result["money"]["bind"] = 0;
		Json::Value temp;
		temp.resize(0);
		temp.append(result);

		Json::FastWriter write;
		string text = write.write(temp);
		CgiUtil::PrintText(text);
		return 0;
	}

	int QueryOrder()
	{
		Json::FastWriter writer;

		string order = Crypt::UrlDecode(CCGIIn::GetCGIStr("order"));
		int time = CCGIIn::GetCGIInt("time");
		int uid = CCGIIn::GetCGIInt("uid");
		string flag = CCGIIn::GetCGIStr("flag");

		string md5String = Crypt::Md5Encode(order + CTrans::ITOS(time) + MD5KEY);
		if (md5String != flag)
		{
			CgiUtil::PrintText("5");
			PARAM_ERROR_RETURN_MSG("flag_error");
		}

		DataPayHistory payHistory;
		CDataPayHistory dbPayHistory;
		int ret = dbPayHistory.GetPayHistory(uid, OpenPlatform::GetType(), order, payHistory);
		if(ret)
		{
			CgiUtil::PrintText("-1");
			return 0;
		}

        char now[64];
        time_t tt;
        struct tm *ttime;
        tt = payHistory.time;
        ttime = localtime(&tt);
        strftime(now,64,"%Y-%m-%d %H:%M:%S",ttime);

		string userName;
		CDataUserBasic dbUser;
		dbUser.GetUserName(uid, OpenPlatform::GetType(), userName);

		Json::Value result;
		result["order"] = order;
		result["username"] = payHistory.open_id;
		result["money"] = payHistory.credit/100;
		result["gamemoney"] = payHistory.count;
		result["time"] = string(now);
		result["nickname"] = userName;
		result["serve_id"] = Config::GetZoneByUID(uid);
		result["status"] = 1;

		Json::FastWriter write;
		string text = write.write(result);
		CgiUtil::PrintText(text);
		return 0;
	}

	int QueryOnline()
	{
		int time = CCGIIn::GetCGIInt("time");
		int serverid = CCGIIn::GetCGIInt("serverid");
		string flag = CCGIIn::GetCGIStr("flag");

		string md5String = Crypt::Md5Encode(CTrans::ITOS(time) + MD5KEY);
		if (md5String != flag)
		{
			CgiUtil::PrintText("-2");
			PARAM_ERROR_RETURN_MSG("flag_error");
		}

		if(serverid == CCGIIn::CGI_INT_ERR)
		{
			Json::FastWriter write;
			Json::Value result;
			result.resize(0);
			set<int> domains;
			MainConfig::GetDomains(domains);
			for(set<int>::iterator it=domains.begin();it!=domains.end();++it)
			{
				Json::Value t;
				t["serverid"] = *it;
				string ranklist_path = Config::GetPath("tools/online", *it);
				string ranklist_buff;
				File::Read(ranklist_path,ranklist_buff);
				t["online"] = ranklist_buff;
				result.append(t);
			}
			CgiUtil::PrintText(write.write(result));
		}
		else
		{
			string ranklist_path = Config::GetPath("tools/online", serverid);
			string ranklist_buff;
			File::Read(ranklist_path,ranklist_buff);
			CgiUtil::PrintText(ranklist_buff);
		}

		return 0;
	}
};

CGI_MAIN(CCgiNew4399Admin)

