/*
 * CgiSogouDeliver.cpp
 *
 *  Created on: 2015-9-01
 *      Author: Eddard
 */

#include "LogicInc.h"
#include "SogouPlatform.h"

#define IP_NUM 37
const string ip_str[IP_NUM] = {
		"36.110.170.84",
		"106.120.151.74",
		"106.120.151.91",
		"123.125.125.173",
		"123.126.50.112",
		"123.126.50.113",
		"123.126.50.208",
		"123.126.50.26",
		"123.126.51.101",
		"123.126.51.108",
		"123.126.51.45",
		"123.126.51.46",
		"123.126.51.49",
		"123.126.51.51",
		"202.106.180.62",
		"220.181.11.232",
		"220.181.11.233",
		"220.181.124.60",
		"220.181.125.139",
		"220.181.125.140",
		"220.181.125.161",
		"220.181.125.185",
		"220.181.125.186",
		"220.181.125.187",
		"220.181.125.188",
		"220.181.125.224",
		"220.181.125.46",
		"220.181.125.54",
		"220.181.125.66",
		"61.135.189.24",
		"61.135.189.25",
		"123.125.125.172",
		"220.181.125.17",
		"111.202.103.132",
		"111.202.103.184",
		"111.202.103.131",
		"36.110.171.126"
};

class CCgiSogouDeliver: public CCgiBase {
public:
	CCgiSogouDeliver() : CCgiBase("sogoudeliver") {
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(deliver)

	int deliver() {
		const int gid = CCGIIn::GetCGIInt("gid");
		const int sid = CCGIIn::GetCGIInt("sid");
		const string openid = CCGIIn::GetCGIStr("uid");
		const string role = CCGIIn::GetCGIStr("role");
		const string oid = CCGIIn::GetCGIStr("oid");
		const string date = CCGIIn::GetCGIStr("date");
		const int money = CCGIIn::GetCGIInt("amount1"); //人民币元
		const int cash = CCGIIn::GetCGIInt("amount2"); //钻石
		const string time = CCGIIn::GetCGIStr("time");
		const string auth = CCGIIn::GetCGIStr("auth");

		if (openid.empty() || oid.empty() || auth.empty() || date.empty()
				|| time.empty() || money == CCGIIn::CGI_INT_ERR
				|| cash == CCGIIn::CGI_INT_ERR || money <= 0 || cash <= 0) {
			CgiUtil::PrintText("ERR_100");
			return -1;
		}

		/*bool bValidIp = false;
		for (unsigned i = 0; i < IP_NUM; ++i) {
			if (ip_str[i] == m_ipstr) {
				bValidIp = true;
				break;
			}
		}
		if (!bValidIp) {
			CgiUtil::PrintText("ERR_400");
			return -4;
		}*/

		map<string, string> pa;
		pa["gid"] = CTrans::ITOS(gid);
		pa["sid"] = CTrans::ITOS(sid);
		pa["uid"] = openid;
		pa["role"] = role;
		pa["oid"] = oid;
		pa["date"] = date;
		pa["amount1"] = CTrans::ITOS(money);
		pa["amount2"] = CTrans::ITOS(cash);
		pa["time"] = time;
		map<string, string>::iterator iter = pa.begin();
		string osig = "";
		for (; iter != pa.end(); ++iter) {
			osig += iter->first + "=" + iter->second + "&";
		}
		osig += OpenPlatform::GetPlatform()->GetAppKey();
		string sig = Crypt::Md5Encode(osig);
		if (sig != auth) {
			CgiUtil::PrintText("ERR_200");
			return -2;
		}

		int ret = 0;
		CLogicPay logicPay;
		unsigned uid = 0;
		int serverid = 0;
		Config::GetDB(serverid);
		CDataUserMapping dbUserMapping;
		ret = dbUserMapping.GetUID(openid, serverid, uid);
		if (ret == R_ERR_NO_DATA) {
			CgiUtil::PrintText("ERR_300");
			return -3;
		}
		if (ret || uid == 0) {
			CgiUtil::PrintText("ERR_500");
			return -5;
		}

		//防重发, 如果该payment_id已经处理, 那么不再增加钻石
		DataPayHistory payHistory;
		CDataPayHistory dbPayHistory;
		ret = dbPayHistory.GetPayHistory(uid, OpenPlatform::GetType(), oid,
				payHistory);
		if (ret == 0) {
			//重复订单返回OK
			CgiUtil::PrintText("OK");
			return 0;
		}

		bool bsave = false;
		DataPay pay;
		CLogicUser logicUser;
		DataUser user;
		Json::Value user_flag;
		Json::Reader reader;
		ret = logicUser.GetUser(uid, user);
		if (ret) {
			CgiUtil::PrintText("ERR_500");
			return -5;
		}
		reader.parse(user.user_flag, user_flag);

		ret = logicPay.ChangePay(uid, cash, 0, pay, "SOGOUTOPUP", user_flag,
				bsave, PAY_FLAG_CHARGE);
		if (ret != 0) {
			CgiUtil::PrintText("ERR_500");
			return -5;
		}
		logicPay.DoPay(uid, user, cash);
		if (bsave)
			logicUser.SetUserFlag(uid, user_flag);

		DataPayHistory payhis;
		payhis.channel = OpenPlatform::GetType();
		payhis.channel_pay_id = oid;
		payhis.count = cash;
		payhis.credit = money * 100;
		payhis.status = PST_OK;
		payhis.type = 0;
		payhis.uid = uid;
		payhis.open_id = openid;
		ret = logicPay.AddPayHistory(payhis);
		if (ret != 0) {
			error_log("[AddPayHistory fail][ret=%d,openid=%s,order_id=%s]",
					ret, openid.c_str(), oid.c_str());
		}

		CGI_SEND_LOG(
				"openid=%s&order_id=%s&serverid=%d&num=%u", openid.c_str(), oid.c_str(), serverid, cash);

		CgiUtil::PrintText("OK");
		return R_SUCCESS;
	}

private:
	void PrintResult(Json::Value &result) {
		Json::FastWriter writer;
		string res = writer.write(result);
		CgiUtil::PrintText(res.c_str());
	}
};

CGI_MAIN(CCgiSogouDeliver)

