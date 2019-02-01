/*
 * Cgi4399Admin.cpp
 *
 *  Created on: 2015-4-22
 *      Author: dawx123584
 */


#include "LogicInc.h"

#define MD5KEY OpenPlatform::GetPlatform()->GetConfig(CONFIG_4399_OTHER_KEY)
#define TIMEOUT 120     //验证超时时间为120s

class CCgi4399Admin : public CCgiBase
{
public:
	CCgi4399Admin() : CCgiBase("4399admin")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_SIMPLE_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("queryuser", QueryUser)
	CGI_SET_ACTION_MAP("forbidchat", ForbidChat)
	CGI_SET_ACTION_MAP("changeblockts", ChangeBlockTs)
	CGI_SET_ACTION_MAP("getranklist", GetRankList)
	CGI_SET_ACTION_MAP("changecash", ChangeCash)
	CGI_ACTION_MAP_END

	int QueryUser()
	{
		Json::FastWriter writer;

		string openid = CCGIIn::GetCGIStr("username");
		int time = CCGIIn::GetCGIInt("time");
		string flag = CCGIIn::GetCGIStr("flag");

		if(openid.empty() || flag.empty() || time == CCGIIn::CGI_INT_ERR)
		{
			PrintResultWithHeader("Return-Code: <-1>");
			return -1;
		}

		// Check flag and time
		string md5String = Crypt::Md5Encode(CTrans::ITOS(time) + openid + MD5KEY);
		if (md5String != flag)
		{
			PrintResultWithHeader("Return-Code: <-2>");
			return -1;
		}

		if(IsTimeout(time))
		{
			PrintResultWithHeader("Return-Code: <-3>");
			return -1;
		}

		// Get uid
		int serverid = 0;
		Config::GetDB(serverid);
		CDataUserMapping userMapper;
		unsigned uid = 0;
		int ret = userMapper.GetUID(openid, serverid, uid);
		if (ret != 0)
		{
			PrintResultWithHeader("Return-Code: <-1>");
			return ret;
		}

		// Get User Info
		DataUser user;
		CLogicAdmin logicAdmin;
		ret = logicAdmin.QueryUser(uid, user);
		if(ret != 0)
		{
			PrintResultWithHeader("Return-Code: <-4>");
			return ret;
		}

		// Get pay info
		CLogicPay logicPay;
		DataPay pay;
		ret = logicPay.GetPay(uid, pay);
		if(ret != 0)
		{
			PrintResultWithHeader("Return-Code: <-5>");
			return ret;
		}

		string userName;
		CDataUserBasic dbUser;
		dbUser.GetUserName(uid, OpenPlatform::GetType(), userName);
		// Success!
		Json::Value result;
		result["username"] = openid;
		result["role_id"] = uid;
		result["role"] = userName;
		result["effect_time"] = Time::GetGlobalTime() + 60;
		result["job"] = "";
		result["level"] = user.level;
		result["creation_time"] = user.register_time;
		result["last_login_time"] = user.last_login_time;
		result["remain_count"] = pay.cash;
		Json::Value temp;
		temp.resize(0);
		temp.append(result);

		Json::FastWriter write;
		string text = write.write(temp);
		CgiUtil::PrintText(text);
		return 0;
	}


	int ChangeCash()
	{
		if(m_ipstr != OpenPlatform::GetPlatform()->GetConfig(CONFIG_4399_ADMIN_IP))
		{
			Print4399Result("ip error");
			return (-1);
		}

		string openid = CCGIIn::GetCGIStr("username");
		string flag = CCGIIn::GetCGIStr("flag");
		int gold = CCGIIn::GetCGIInt("gold");
		string reason = CCGIIn::GetCGIStr("reason");
		int time = CCGIIn::GetCGIInt("time");

		if (openid.empty() || flag.empty()
		|| (CCGIIn::CGI_INT_ERR == gold)
		|| (CCGIIn::CGI_INT_ERR == time) || (time < 0))
		{
			Print4399Result("parameters error");
			return (-1);
		}

		// sign
		string md5String = Crypt::Md5Encode(CTrans::ITOS(time) + MD5KEY
				+ openid + CTrans::ITOS(gold));
		if (flag != md5String)
		{
			Print4399Result("sign error");
			return (-1);
		}

		// timeout
		if (IsTimeout(time))
		{
			Print4399Result("time error");
			return (-1);
		}

		// check user
		int serverid = 0;
		Config::GetDB(serverid);
		CDataUserMapping userMapper;
		unsigned int uid = 0;
		int ret = userMapper.GetUID(openid, serverid, uid);
		if (ret)
		{
			Print4399Result("user error");
			return (ret);
		}

		CLogicAdmin logicAdmin;
		DataPay pay;
		int channel = 0;
		ret = logicAdmin.ChangePay(uid, gold, 0, pay, channel);
		if (ret)
		{
			Print4399Result("platform error");
			return (ret);
		}

		// Success
		Print4399Result("");
		CLogicAdmin::Log(openid, "changeCash", reason, uid, "", "");
		CLogicAdmin::AddCheckLog(openid, m_ipstr, "钻石", reason, uid, 0, gold);
		return (0);
	}

	int ForbidChat()
	{
		string name = CCGIIn::GetCGIStr("nickname");
		int minutes = CCGIIn::GetCGIInt("minutes");
		int time = CCGIIn::GetCGIInt("time");
		string ticket = CCGIIn::GetCGIStr("ticket");
		string reason = CCGIIn::GetCGIStr("reason");

		if(name.empty() || ticket.empty() ||
		minutes == CCGIIn::CGI_INT_ERR || minutes < 0 ||
		time == CCGIIn::CGI_INT_ERR || time < 0)
		{
			Print4399Result("parameters error");
			return -1;
		}

		// Check ticket and time
		string md5String = Crypt::Md5Encode(name + CTrans::ITOS(minutes) + CTrans::ITOS(time) + MD5KEY);
		if (md5String != ticket)
		{
			Print4399Result("sign error");
			return -1;
		}

		if (IsTimeout(time))
		{
			Print4399Result("time error");
			return -1;
		}

		//Get uid
		int serverid = 0;
		Config::GetDomain(serverid);
		CDataName dbName;
		string openid;
		unsigned uid;
		int ret = dbName.GetName(name, openid, uid);
		if(ret)
		{
			Print4399Result("user error");
			return ret;
		}

		//Send request
		CLogicAdmin logicAdmin;
		unsigned forbidts = Time::GetGlobalTime() + minutes * 60;
		ret  = logicAdmin.AddForbidUser(uid, forbidts, CTrans::ITOS(serverid));
		if(ret != 0)
		{
			Print4399Result("platform error");
			return ret;
		}

		//成功
		Print4399Result("");

		CLogicAdmin::Log(openid, "forbidChat", reason, uid, CTrans::ITOS(minutes), "");
		CLogicAdmin::AddCheckLog(openid,m_ipstr,"禁言",reason,uid,0,0);
		return 0;
	}

	int ChangeBlockTs()
	{
		string nickname = CCGIIn::GetCGIStr("nickname");
		string openid = CCGIIn::GetCGIStr("username");
		string blockReason = CCGIIn::GetCGIStr("reason");
		string ticket = CCGIIn::GetCGIStr("ticket");
		int banTime = CCGIIn::GetCGIInt("banTime");
		int time = CCGIIn::GetCGIInt("time");

		if(nickname.empty() || openid.empty() ||
		ticket.empty() || banTime == CCGIIn::CGI_INT_ERR ||
		banTime < 0 || time == CCGIIn::CGI_INT_ERR || time < 0)
		{
			Print4399Result("parameters error");
			return -1;
		}

		// Check ticket and time
		string md5String = Crypt::Md5Encode(nickname + openid + CTrans::ITOS(banTime) + CTrans::ITOS(time) + MD5KEY);
		if (md5String != ticket)
		{
			Print4399Result("sign error");
			return -1;
		}

		if (IsTimeout(time))
		{
			Print4399Result("time error");
			return -1;
		}

		// Get uid
		int serverid = 0;
		Config::GetDB(serverid);
		CDataUserMapping userMapper;
		unsigned uid = 0;
		int ret = userMapper.GetUID(openid, serverid, uid);
		if (ret != 0)
		{
			Print4399Result("user error");
			return ret;
		}

		// 开始封号请求
		CLogicAdmin logicAdmin;
		unsigned blockTime = Time::GetGlobalTime() + banTime * 60;
		ret = logicAdmin.ChangeBlockTs(uid, blockTime, blockReason);
		if (ret != 0)
		{
			Print4399Result("platform error");
			return ret;
		}

		// 成功
		Print4399Result("");

		CLogicAdmin::Log(openid, "lockuser", blockReason, uid, CTrans::ITOS(banTime), "");
		CLogicAdmin::AddCheckLog(openid, m_ipstr, "封号", blockReason, uid, 0, 0);

		return 0;
	}

	int GetRankList()
	{
		string flag = CCGIIn::GetCGIStr("flag");
		int time = CCGIIn::GetCGIInt("time");

		if(flag.empty() || time == CCGIIn::CGI_INT_ERR || time < 0)
		{
			PrintResultWithHeader("Error-info: [-1]");
			return -1;
		}

		// Check flag and time
		string md5String = Crypt::Md5Encode(CTrans::ITOS(time) + MD5KEY);
		if (md5String != flag)
		{
			PrintResultWithHeader("Error-info: [-2]");
			return -1;
		}

		if (IsTimeout(time))
		{
			PrintResultWithHeader("Error-info: [-2]");
			return -1;
		}

		string ranklist_path = Config::GetPath("webroot/data/ranklist");
		string ranklist_buff;
		int ret = File::Read(ranklist_path,ranklist_buff);
		if(0 != ret)
		{
			PrintResultWithHeader("Error-info: [-3]");
			cout << "Read file faile path=" << ranklist_path << endl;
			return -1;
		}

		Json::Value temp;
		temp.resize(0);
		temp.append(ranklist_buff);
		Json::FastWriter write;
		string text = write.write(temp);
		CgiUtil::PrintText(text);
		return 0;
	}

private:
	void PrintResultWithHeader(const string &header)
	{
		Json::FastWriter writer;
		string text = writer.write(m_jsonResult);
		vector<string> headers;
		headers.push_back(header);
		CgiUtil::PrintText(text, headers);
	}

	void Print4399Result(const string &msg)
	{
		Json::FastWriter write;
		Json::Value temp;
		if(msg.empty())
		{
			temp["code"] = 1;
			temp["msg"] = "success";
		}
		else
		{
			temp["code"] = 0;
			temp["msg"] = msg;
		}
		string text = write.write(temp);
		CgiUtil::PrintText(text);
	}

	bool IsTimeout(unsigned time)
	{
		unsigned globalTime = Time::GetGlobalTime();

		if (Math::Abs(globalTime - time) > TIMEOUT)
		{
			return true;
		}
		return false;
	}
};

CGI_MAIN(CCgi4399Admin)


