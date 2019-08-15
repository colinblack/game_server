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
		ConfigManager::Instance()->SetServer(0);

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
		int ret = userMapper.GetMapping(openid, 0, uid);
		if (ret != 0)
		{
			CgiUtil::PrintText("2");
			PARAM_ERROR_RETURN_MSG("user_error");
		}

		CDataBase dba;
		DataBase d;
		d.uid = uid;
		ret = dba.Get(d);
		if(ret)
		{
			CgiUtil::PrintText("0");
			PARAM_ERROR_RETURN_MSG("user_error");
		}

		Json::Value result;
		result["userid"] = openid;
		result["nickname"] = d.name;
		result["level"] = d.level;
		result["money"]["normal"] = d.cash;
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
		ConfigManager::Instance()->SetServer(0);

		Json::FastWriter writer;

		string order = Crypt::UrlDecode(CCGIIn::GetCGIStr("order"));
		int time = CCGIIn::GetCGIInt("time");
		string flag = CCGIIn::GetCGIStr("flag");
		string openid = Crypt::UrlDecode(CCGIIn::GetCGIStr("username"));//todo 我们的架构如果不传openid无法查询订单

		string md5String = Crypt::Md5Encode(order + CTrans::ITOS(time) + MD5KEY);
		if (md5String != flag)
		{
			CgiUtil::PrintText("5");
			PARAM_ERROR_RETURN_MSG("flag_error");
		}

		CDataUserMapping userMapper;
		unsigned uid = 0;
		int ret = userMapper.GetMapping(openid, 0, uid);
		if (ret != 0)
		{
			CgiUtil::PrintText("4");
			PARAM_ERROR_RETURN_MSG("user_error");
		}

		DataPayHistory payHistory;
		CDataPayHistory dbPayHistory;
		ret = dbPayHistory.GetPayHistory(uid, OpenPlatform::GetType(), order, payHistory);
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

		CDataBase dba;
		DataBase d;
		d.uid = uid;
		ret = dba.Get(d);

		Json::Value result;
		result["order"] = order;
		result["username"] = payHistory.open_id;
		result["money"] = payHistory.credit/100;
		result["gamemoney"] = payHistory.count;
		result["time"] = string(now);
		result["nickname"] = d.name;
		result["serve_id"] = 1;
		result["status"] = 1;

		Json::FastWriter write;
		string text = write.write(result);
		CgiUtil::PrintText(text);
		return 0;
	}

	int QueryOnline()
	{
		ConfigManager::Instance()->SetServer(0);

		int time = CCGIIn::GetCGIInt("time");
		string serverid = CCGIIn::GetCGIStr("serverid");
		string flag = CCGIIn::GetCGIStr("flag");

		string md5String = Crypt::Md5Encode(CTrans::ITOS(time) + MD5KEY);
		if (md5String != flag)
		{
			CgiUtil::PrintText("-2");
			PARAM_ERROR_RETURN_MSG("flag_error");
		}

		string ranklist_path = MainConfig::GetAllServerPath("access/log/4399.online.log");// 生成在线文件
		string ranklist_buff;
		File::Read(ranklist_path,ranklist_buff);

		if(serverid.empty())
		{
			Json::Value result;
			result["serverid"] = string("1");
			result["online"] = ranklist_buff;

			Json::FastWriter write;
			string text = write.write(result);
			string ret = "[" + text + "]";

			CgiUtil::PrintText(ret);
		}
		else
		{
			CgiUtil::PrintText(ranklist_buff);
		}

		return 0;
	}
};

CGI_MAIN(CCgiNew4399Admin)

