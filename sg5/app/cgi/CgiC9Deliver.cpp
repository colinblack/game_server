/*
 * CgiC9Deliver.cpp
 *
 *  Created on: 2015-8-26
 *      Author: Ralf
 */



#include "LogicInc.h"
#include "C9Platform.h"

class CCgiC9Deliver : public CCgiBase
{
public:
	CCgiC9Deliver() : CCgiBase("c9deliver")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(deliver)

	int deliver()
	{
		const unsigned serverid = CCGIIn::GetCGIInt("serverid");
		const string serverid_s = CCGIIn::GetCGIStr("serverid");
		const string order_id = CCGIIn::GetCGIStr("order_id");
		const string openid = CCGIIn::GetCGIStr("uid");
		unsigned cash = CCGIIn::GetCGIInt("coins");
		const string cash_s = CCGIIn::GetCGIStr("coins");
		const double moneys = CCGIIn::GetCGIDbl("moneys", 0, 100000000, 0, 0);
		unsigned money = (unsigned)(moneys*100);
		const string moneys_s = CCGIIn::GetCGIStr("moneys");
		const unsigned time = CCGIIn::GetCGIInt("time");
		const string time_s = CCGIIn::GetCGIStr("time");
		const string sign = CCGIIn::GetCGIStr("sign");

		Json::Value result;
		result["errno"] = 0;
		result["errmsg"] = "充值成功";
		result["data"]["order_id"] = order_id;
		result["data"]["uid"] = openid;
		result["data"]["role_id"] = 0;
		result["data"]["role_name"] = "";
		result["data"]["platfrom"] = 0;
		result["data"]["gkey"] = "城防三国";
		result["data"]["skey"] = serverid;
		result["data"]["coins"] = cash;
		result["data"]["moneys"] = moneys;
		result["data"]["time"] = Time::GetGlobalTime();

		if(openid.empty() || order_id.empty() || sign.empty() ||
		cash == CCGIIn::CGI_INT_ERR || time == CCGIIn::CGI_INT_ERR || cash == 0)
		{
			result["errno"] = -1;
			result["errmsg"] = "参数不全";
			return PrintResult(result);
		}

		if (Math::Abs(Time::GetGlobalTime() - time) > 180)
		{
			result["errno"] = -4;
			result["errmsg"] = "请求超时";
			return PrintResult(result);
		}

		string osig  = serverid_s + order_id + openid + moneys_s + cash_s + time_s + OpenPlatform::GetPlatform()->GetAppKey();
		string sig = Crypt::Md5Encode(osig);
		if(sig != sign)
		{
			result["errno"] = -2;
			result["errmsg"] = "签名错误";
			return PrintResult(result);
		}

		int ret = 0;
		CLogicPay logicPay;
		unsigned uid = 0;
		CDataUserMapping dbUserMapping;
		ret = dbUserMapping.GetUID(openid, serverid, uid);
		if(ret == R_ERR_NO_DATA)
		{
			result["errno"] = -3;
			result["errmsg"] = "用户不存在";
			return PrintResult(result);
		}
		if(ret || uid == 0)
		{
			result["errno"] = -5;
			result["errmsg"] = "系统错误";
			return PrintResult(result);
		}

		//防重发, 如果该payment_id已经处理, 那么不再增加钻石
		DataPayHistory payHistory;
		CDataPayHistory dbPayHistory;
		ret = dbPayHistory.GetPayHistory(uid, OpenPlatform::GetType(), order_id, payHistory);
		if(ret == 0)
		{
			result["errno"] = 1;
			result["errmsg"] = "订单重复";
			return PrintResult(result);
		}

		bool bsave = false;
		DataPay pay;
		CLogicUser logicUser;
		DataUser user;
		Json::Value user_flag;
		Json::Reader reader;
		ret = logicUser.GetUser(uid,user);
		if(ret)
		{
			result["errno"] = -6;
			result["errmsg"] = "系统错误";
			return PrintResult(result);
		}
		reader.parse(user.user_flag, user_flag);

		string userName;
		CDataUserBasic dbUser;
		dbUser.GetUserName(uid, OpenPlatform::GetType(), userName);
		result["data"]["role_id"] = uid;
		result["data"]["role_name"] = userName;
		Json::FastWriter writer;
		string res = writer.write(result);
		OpenPlatform::GetPlatform()->SetReply(res);


		if (OpenPlatform::GetPlatform()->GetAppKey() == "a8c1850bb4043bd69bfac68d9f5903be"){
			cash = ceil(cash / 0.728f);
			result["data"]["coins"] = cash;
		}
		ret = logicPay.ChangePay(uid, cash, 0, pay, "C9TOPUP", user_flag, bsave, PAY_FLAG_CHARGE);
		if (ret != 0)
		{
			result["errno"] = -7;
			result["errmsg"] = "系统错误";
			return PrintResult(result);
		}
		logicPay.DoPay(uid,user,cash);
		if(bsave)
			logicUser.SetUserFlag(uid,user_flag);

		DataPayHistory payhis;
		payhis.channel = OpenPlatform::IsQQPlatform()?PT_TX_C9:user.last_login_platform;
		payhis.channel_pay_id = order_id;
		payhis.count = cash;
		payhis.credit = money;
		payhis.status = PST_OK;
		payhis.type = 0;
		payhis.uid = uid;
		payhis.open_id = openid;
		ret = logicPay.AddPayHistory(payhis);
		if (ret != 0)
		{
			error_log("[AddPayHistory fail][ret=%d,openid=%s,order_id=%s]",
					ret,openid.c_str(),order_id.c_str());
		}

		CDataUser().SetLastLogin(uid, Time::GetGlobalTime(), Time::GetGlobalTime());
		CDataUserMapping().SetLastLogin(openid, serverid, Time::GetGlobalTime());

		Json::Value v;
		CLogicEquipment().AddOneItem(uid, 5108, 1, "C9Deliver", v);

		CGI_SEND_LOG("openid=%s&order_id=%s&serverid=%d&num=%u", openid.c_str(),order_id.c_str(),serverid,cash);
		return R_SUCCESS;
	}

private:
	int PrintResult(Json::Value &result)
	{
		Json::FastWriter writer;
		string res = writer.write(result);
		CgiUtil::PrintText(res.c_str());
		unsigned ret = 0;
		Json::GetUInt(result,"errno",ret);
		return ret;
	}
};

CGI_MAIN(CCgiC9Deliver)

