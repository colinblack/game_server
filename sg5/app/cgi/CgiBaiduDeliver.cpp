/*
 * CgiBaiduDeliver.cpp
 *
 *  Created on: 2015-12-15
 *      Author: dawx5fsd
 */



#include "LogicInc.h"

static const string white_ip[] =
{
		"180.97.106.148",
		"180.97.106.149",
		"180.97.106.150",
		"61.135.190.220",
		"61.135.190.221",
		"61.135.190.100",
		"61.135.190.101",
		"61.135.190.104",
		"61.135.190.105",
		"61.135.190.222",
		"61.135.190.223",
		"61.135.190.102",
		"61.135.190.219",
		"61.135.190.103",
		"61.135.190.224",
		"111.13.102.4",
		"111.13.102.5",
		"111.13.102.6",
		"111.13.102.7",
		"111.13.102.136",
		"111.13.102.137",
		"111.13.102.138",
		"111.13.102.139",
		"111.13.102.8",
		"111.13.102.9",
		"111.13.102.10",
		"111.13.102.11",
		"111.13.102.132",
		"111.13.102.133",
		"111.13.102.134",
		"111.13.102.135",
		"220.181.50.5",
		"220.181.50.6",
		"220.181.50.7",
		"220.181.50.8",
		"220.181.50.70",
		"220.181.50.71",
		"220.181.50.68",
		"220.181.50.69",
		"220.181.50.34",
		"220.181.50.35",
		"220.181.50.36",
		"220.181.50.37"
		"220.181.50.100",
		"220.181.50.99",
		"220.181.50.98",
		"220.181.50.101",
		"220.181.50.12",
		"220.181.50.9",
		"220.181.50.10",
		"220.181.50.11",
		"220.181.50.38",
		"220.181.50.39",
		"220.181.50.40",
		"220.181.50.41",
		"220.181.50.72",
		"220.181.50.73",
		"220.181.50.75",
		"220.181.50.74",
		"220.181.50.102",
		"220.181.50.103",
		"220.181.50.104",
		"220.181.50.105",
};


class CCgiBaiduDeliver : public CCgiBase
{
public:

	CCgiBaiduDeliver() : CCgiBase("baiduDeliver")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(deliver)

	int deliver()
	{
		string api_key = CCGIIn::GetCGIStr("api_key");
		string openid = CCGIIn::GetCGIStr("user_id");
		unsigned serverid = CCGIIn::GetCGIInt("server_id");
		string order_id = CCGIIn::GetCGIStr("order_id");
		string wanba_oid = CCGIIn::GetCGIStr("wanba_oid");
		unsigned amount = CCGIIn::GetCGIInt("amount", 0, 10000000, 0, 0);
		string currency = CCGIIn::GetCGIStr("currency");
		unsigned result = CCGIIn::GetCGIInt("result");
		string back_send = CCGIIn::GetCGIStr("back_send");
		string timestamp = CCGIIn::GetCGIStr("timestamp");
		string sign = CCGIIn::GetCGIStr("sign");

		if (api_key.empty() || openid.empty() || order_id.empty()
				|| currency.empty()
				|| back_send.empty() || timestamp.empty()
				|| sign.empty() || wanba_oid.empty()
				|| (1 != result))
		{
			error_log("args error");
			return -1;
		}

		bool isValidIp = false;

		for (unsigned i = 0; i < sizeof(white_ip)/sizeof(white_ip[0]); ++i)
		{
			if (m_ipstr == white_ip[i])
			{
				isValidIp = true;
				break;
			}
		}

		if (false == isValidIp)
		{
			error_log("ip is error. remote_ip = %s", m_ipstr.c_str());
			return -1;
		}

		string app_secret = OpenPlatform::GetPlatform()->GetAppKey();
		string osig = app_secret + "amount" + CTrans::UTOS(amount)
		+ "api_key" + api_key
		+ "back_send" + back_send
		+ "currency" + currency
		+ "order_id" + order_id
		+ "result" + CTrans::UTOS(result)
		+ "server_id" + CTrans::UTOS(serverid)
		+ "timestamp" + timestamp
		+ "user_id" + openid
		+ "wanba_oid" + wanba_oid;

		string bsign = Crypt::Md5Encode(osig);

		if (0 != strcasecmp(sign.c_str(), bsign.c_str()))
		{
			error_log("sign is error. osig = %s, bsign = %s, sign = %s", osig.c_str(), bsign.c_str(), sign.c_str());
			return -1;
		}

		int ret = 0;
		unsigned uid;
		CDataUserMapping dbUserMapping;

		ret = dbUserMapping.GetUID(openid, serverid, uid);
		if (R_ERR_NO_DATA == ret)
		{
			error_log("user isnot exist");
			return -1;
		}
		else if (ret || (0 == uid))
		{
			error_log("GetUID failed. uid = %u, openid = %s, ret = %d", uid, openid.c_str(), ret);
			return -1;
		}

		DataPayHistory payHis;
		CDataPayHistory dbPayHis;

		// 收到后台通知, 检查如果前台通知未发币, 即发币, 并返回 res
		string res = "<!--recv=ok-->";

		ret = dbPayHis.GetPayHistory(uid, OpenPlatform::GetType(), order_id, payHis);
		if (0 == ret)
		{
			CgiUtil::PrintText(res.c_str());
			return R_SUCCESS;
		}

		CLogicUser logicUser;
		DataUser dataUser;

		ret = logicUser.GetUser(uid, dataUser);
		if (ret)
		{
			error_log("GetUser failed. uid = %u, ret = %d", uid, ret);
			return ret;
		}

		Json::Value user_flag;
		Json::Reader reader;
		bool bsave = false;

		reader.parse(dataUser.user_flag, user_flag);

		CLogicPay logicPay;
		DataPay pay;

		int cash = amount * 10;

		OpenPlatform::GetPlatform()->SetReply(res);

		ret = logicPay.ChangePay(uid, cash, 0, pay, "BaiduTOPUP", user_flag, bsave, PAY_FLAG_CHARGE);
		if (ret)
		{
			error_log("ChangePay failed. uid = %u, ret = %d", uid, ret);
			return ret;
		}

		logicPay.DoPay(uid, dataUser, cash);

		if (bsave)
		{
			logicUser.SetUserFlag(uid, user_flag);
		}

		DataPayHistory payhis;

		payhis.channel = dataUser.last_login_platform;
		payhis.channel_pay_id = order_id;
		payhis.count = cash;
		payhis.credit = amount * 100;
		payhis.status = PST_OK;
		payhis.type = 0;
		payhis.open_id = openid;
		payhis.uid = uid;

		ret = logicPay.AddPayHistory(payhis);
		if (ret)
		{
			error_log("[AddPayHistory fail][ret=%d,openid=%s,order_id=%s]",
					ret,openid.c_str(),order_id.c_str());
		}

		CGI_SEND_LOG("openid=%s&order_id=%s&serverid=%d&num=%u", openid.c_str(),order_id.c_str(),serverid, cash);
		return R_SUCCESS;
	}
};


CGI_MAIN(CCgiBaiduDeliver)
