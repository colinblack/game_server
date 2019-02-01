/*
 * CgiXunLeiDeliver.cpp
 *
 *  Created on: 2017-3-21
 *      Author: Ralf
 */


#include "LogicInc.h"
#include "XunLeiPlatform.h"

class CCgiXunLeiDeliver : public CCgiBase
{
public:
	CCgiXunLeiDeliver() : CCgiBase("xunleideliver")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(deliver)

	int deliver()
	{
		const unsigned serverid = CCGIIn::GetCGIInt("server");
		const string serverid_s = CCGIIn::GetCGIStr("server");
		const string order_id = CCGIIn::GetCGIStr("orderid");
		const string openid = Crypt::UrlDecode(CCGIIn::GetCGIStr("user"));
		const unsigned cash = CCGIIn::GetCGIInt("gold");
		const string cash_s = CCGIIn::GetCGIStr("gold");
		const unsigned moneys = CCGIIn::GetCGIInt("money");
		unsigned money = moneys * 100;
		const string moneys_s = CCGIIn::GetCGIStr("money");
		const unsigned time = CCGIIn::GetCGIInt("time");
		const string time_s = CCGIIn::GetCGIStr("time");
		const string sign = CCGIIn::GetCGIStr("sign");

		if(openid.empty() || order_id.empty() || sign.empty() ||
		cash == CCGIIn::CGI_INT_ERR || time == CCGIIn::CGI_INT_ERR || cash == 0)
			return PrintResult(-1);

		if (Math::Abs(Time::GetGlobalTime() - time) > 180)
			return PrintResult(-4);

		string osig  = order_id + openid + cash_s + moneys_s + time_s + OpenPlatform::GetPlatform()->GetAppKey();
		string sig = Crypt::Md5Encode(osig);
		if(sig != sign)
			return PrintResult(-2);

		int ret = 0;
		unsigned uid = 0;
		CDataUserMapping dbUserMapping;
		ret = dbUserMapping.GetUID(openid, serverid, uid);
		if(ret == R_ERR_NO_DATA)
			return PrintResult(-3);
		if(ret || uid == 0)
			return PrintResult(-7);

		//防重发, 如果该payment_id已经处理, 那么不再增加钻石
		DataPayHistory payHistory;
		CDataPayHistory dbPayHistory;
		ret = dbPayHistory.GetPayHistory(uid, OpenPlatform::GetType(), order_id, payHistory);
		if(ret == 0)
			return PrintResult(2);

		bool bsave = false;
		DataPay pay;
		CLogicUser logicUser;
		DataUser user;
		Json::Value user_flag;
		Json::Reader reader;
		ret = logicUser.GetUser(uid,user);
		if(ret)
			return PrintResult(-7);
		reader.parse(user.user_flag, user_flag);

		CLogicPay logicPay;
		ret = logicPay.ChangePay(uid, cash, 0, pay, "XUNLEITOPUP", user_flag, bsave, PAY_FLAG_CHARGE);
		if (ret != 0)
			return PrintResult(-7);
		logicPay.DoPay(uid,user,cash);
		if(bsave)
			logicUser.SetUserFlag(uid,user_flag);

		DataPayHistory payhis;
		payhis.channel = OpenPlatform::GetType();
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

		PrintResult(1);
		CGI_SEND_LOG("openid=%s&order_id=%s&serverid=%d&num=%u", openid.c_str(),order_id.c_str(),serverid,cash);
		return 0;
	}

private:
	int PrintResult(int ret)
	{
		CgiUtil::PrintText(CTrans::ITOS(ret));
		return ret;
	}
};

CGI_MAIN(CCgiXunLeiDeliver)




