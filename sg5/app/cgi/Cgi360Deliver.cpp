/*
 * Cgi360Deliver.cpp
 *
 *  Created on: 2017-4-11
 *      Author: Ralf
 */



#include "LogicInc.h"
#include "Platform360.h"

class CCgi360Deliver : public CCgiBase
{
public:
	CCgi360Deliver() : CCgiBase("360deliver")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(deliver)

	int deliver()
	{
		const unsigned serverid = CCGIIn::GetCGIInt("skey");
		const string serverid_s = CCGIIn::GetCGIStr("skey");
		const string order_id = CCGIIn::GetCGIStr("order_id");
		const string openid = Crypt::UrlDecode(CCGIIn::GetCGIStr("uid"));
		const unsigned cash = CCGIIn::GetCGIInt("coins");
		const string cash_s = CCGIIn::GetCGIStr("coins");
		const unsigned moneys = CCGIIn::GetCGIInt("moneys");
		const string moneys_s = CCGIIn::GetCGIStr("moneys");
		const unsigned time = CCGIIn::GetCGIInt("time");
		const string time_s = CCGIIn::GetCGIStr("time");
		const string sign = CCGIIn::GetCGIStr("sign");
		const string platform = CCGIIn::GetCGIStr("platform");

		Json::Value data;
		data["errno"] = 0;
		data["errmsg"] = "充值成功";
		data["data"]["order_id"] = order_id;
		data["data"]["uid"] = openid;
		data["data"]["role_id"] = 0;
		data["data"]["role_name"] = "";
		data["data"]["platform"] = platform;
		data["data"]["gkey"] = OpenPlatform::GetPlatform()->GetAppId();
		data["data"]["skey"] = serverid;
		data["data"]["coins"] = cash;
		data["data"]["moneys"] = moneys;
		data["data"]["time"] = Time::GetGlobalTime();

		if(openid.empty() || order_id.empty() || sign.empty() ||
		cash == CCGIIn::CGI_INT_ERR || time == CCGIIn::CGI_INT_ERR || cash == 0)
		{
			data["errno"] = -1;
			data["errmsg"] = "参数不全";
			return PrintResult(data);
		}

		if (Math::Abs(Time::GetGlobalTime() - time) > 180)
		{
			data["errno"] = -4;
			data["errmsg"] = "请求超时";
			return PrintResult(data);
		}

		string osig  = openid + platform + OpenPlatform::GetPlatform()->GetAppId()
			+ serverid_s + time_s + order_id + cash_s + moneys_s + "#" + OpenPlatform::GetPlatform()->GetConfig("pay_key");
		string sig = Crypt::Md5Encode(osig);
		if(sig != sign)
		{
			data["errno"] = -2;
			data["errmsg"] = "签名错误";
			return PrintResult(data);
		}

		int ret = 0;
		unsigned uid = 0;
		CDataUserMapping dbUserMapping;
		ret = dbUserMapping.GetUID(openid, serverid, uid);
		if(ret == R_ERR_NO_DATA)
		{
			data["errno"] = -3;
			data["errmsg"] = "用户不存在";
			return PrintResult(data);
		}
		if(ret || uid == 0)
		{
			data["errno"] = -5;
			data["errmsg"] = "系统错误";
			return PrintResult(data);
		}

		//防重发, 如果该payment_id已经处理, 那么不再增加钻石
		DataPayHistory payHistory;
		CDataPayHistory dbPayHistory;
		ret = dbPayHistory.GetPayHistory(uid, OpenPlatform::GetType(), order_id, payHistory);
		if(ret == 0)
		{
			data["errno"] = 1;
			data["errmsg"] = "订单重复";
			return PrintResult(data);
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
			data["errno"] = -5;
			data["errmsg"] = "系统错误";
			return PrintResult(data);
		}
		reader.parse(user.user_flag, user_flag);

		string userName;
		CDataUserBasic dbUser;
		dbUser.GetUserName(uid, OpenPlatform::GetType(), userName);
		data["data"]["role_id"] = uid;
		data["data"]["role_name"] = userName;

		CLogicPay logicPay;
		ret = logicPay.ChangePay(uid, cash, 0, pay, "360TOPUP", user_flag, bsave, PAY_FLAG_CHARGE);
		if (ret != 0)
		{
			data["errno"] = -5;
			data["errmsg"] = "系统错误";
			return PrintResult(data);
		}
		logicPay.DoPay(uid,user,cash);
		if(bsave)
			logicUser.SetUserFlag(uid,user_flag);

		DataPayHistory payhis;
		payhis.channel = OpenPlatform::GetType();
		payhis.channel_pay_id = order_id;
		payhis.count = cash;
		payhis.credit = moneys;
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

		CGI_SEND_LOG("openid=%s&order_id=%s&serverid=%d&num=%u", openid.c_str(),order_id.c_str(),serverid,cash);
		return PrintResult(data);
	}

private:
	int PrintResult(Json::Value &data)
	{
		Json::FastWriter writer;
		CgiUtil::PrintText(writer.write(data));
		return data["errno"].asInt();
	}
};

CGI_MAIN(CCgi360Deliver)



