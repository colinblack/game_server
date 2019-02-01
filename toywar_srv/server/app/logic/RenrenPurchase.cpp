#include "RenrenPurchase.h"
#include "IOpenPlatform.h"
#include "DataPayHistory.h"
#include "tsc.h"
#include "trans.h"
#include "LogicPay.h"

int CRenrenPurchase::Purchase(unsigned int uid, short itemId, int count, int price, int cost,
			const string &meta, const string &itemUrl, vector<string> &out)
{
	unsigned int call_id = 0;
	mtime(call_id);
	unsigned int ts = 0;
	unixtime(ts);
	string api_key = OpenPlatform::GetPlatform()->GetConfig("appid");
	string appkey = OpenPlatform::GetPlatform()->GetConfig("appkey");
	string session_key;
	string data = Session::GetValue(uid, SESSION_DATA);
	Json::Reader reader;
	if (!data.empty())
	{
		Json::Value json;
		if (reader.parse(data, json))
		{
			session_key = json["okey"].asString();
		}
	}
	string order_id = CTrans::UTOS(uid) + CTrans::UTOS(ts);

	string ssig;
	String::Format(ssig, "amount=%dapi_key=%scall_id=%udesc=%sformat=JSONmethod=pay.regOrderorder_id=%ssession_key=%sv=1.0%s",
			cost, api_key.c_str(), call_id, meta.c_str(), order_id.c_str(), session_key.c_str(), appkey.c_str());
	string sig = Crypt::Md5Encode(ssig);
	string qstr;
	String::Format(qstr, "amount=%d&api_key=%s&call_id=%u&desc=%s&format=JSON&method=pay.regOrder&order_id=%s&session_key=%s&v=1.0&sig=%s",
			cost, api_key.c_str(), call_id, meta.c_str(), order_id.c_str(), session_key.c_str(), sig.c_str());

	string apiUrl = OpenPlatform::GetPlatform()->GetConfig("apiurl");

	//info_log("[renrenpay][uid=%d,qstr=%s]", uid,qstr.c_str());

	string response;
	if(!Network::HttpPostRequest(response, apiUrl, qstr))
	{
		m_errMsg = "http request fail";
		error_log("[http request fail][uid=%u,errmsg=%s]",
				uid, response.c_str());
		return -1;
	}
	Json::Value value;
	if(!reader.parse(response, value))
	{
		m_errMsg = "json parse fail";
		error_log("[json parse fail][uid=%d,response=%s]",
				uid, response.c_str());
		return -1;
	}
	string token = value["token"].asString();
	if (token.empty())
	{
		m_errMsg = "token is empty";
		error_log("[token is empty][uid=%d]", uid);
		return -1;
	}
	CDataPayHistory payHisDB;
	DataPayHistory payHis;
	payHis.uid = uid;
	payHis.pay_id = CTrans::STOI64(order_id);
	payHis.type = itemId;
	payHis.channel = PCT_RENREN;
	payHis.credit = cost;
	payHis.count = count;
	payHis.status = PST_PENDING;
	payHis.time = ts;
	payHis.channel_pay_id = token;
	int ret = payHisDB.AddPayHistory(payHis);
	if (ret != 0)
	{
		m_errMsg = "dbc error";
		error_log("[AddPayHistory fail][uid=%d,ret=%d]", uid,ret);
		return -1;
	}
	out.push_back(order_id);
	out.push_back(token);

	return 0;
}

int CRenrenPurchase::DeliverGood(unsigned int uid, const map<string, string> &params, vector<string> &out)
{
	map<string, string>::const_iterator it;
	it = params.find("xn_sig_order_id");
	if (it == params.end())
	{
		m_errMsg = "xn_sig_order_id error";
		error_log("[order id error][uid=%d]", uid);
		return -1;
	}
	string order_id = it->second;

	it = params.find("xn_sig_skey");
	if (it == params.end())
	{
		m_errMsg = "xn_sig_skey error";
		error_log("[xn_sig_skey error][uid=%d]", uid);
		return -1;
	}
	string sig_skey = it->second;

	it = params.find("xn_sig_user");
	if (it == params.end())
	{
		m_errMsg = "xn_sig_user error";
		error_log("[xn_sig_user error][uid=%d]", uid);
		return -1;
	}
	string sig_user = it->second;

	string ssig = "dawx1234" + sig_user;
	string sig = Crypt::Md5Encode(ssig);
	if (sig_skey != sig)
	{
		m_errMsg = "check skey fail";
		error_log("[check skey fail][uid=%d,sig=%s,sig_skey=%s,sig_user=%s]",
				uid,sig.c_str(),sig_skey.c_str(),sig_user.c_str());
		return -1;
	}

	CDataPayHistory payHisDB;
	DataPayHistory payHis;
	int ret = payHisDB.GetPayHistory(uid, CTrans::STOI64(order_id), payHis);
	if (ret != 0)
	{
		m_errMsg = "db error";
		error_log("[GetPayHistory fail][uid=%d,ret=%d,order=%s]", uid,ret,order_id.c_str());
		return -1;
	}
	if (payHis.status != 0)
	{
		out.push_back(CTrans::ITOS(payHis.credit));
		return 0;
	}
	payHis.status = 1;
	ret = payHisDB.SetPayHistoryStatus(uid, payHis.pay_id, 1);
	if (ret != 0)
	{
		m_errMsg = "db error";
		error_log("[SetPayHistoryStatus fail][uid=%d,ret=%d,order=%s]", uid,ret,order_id.c_str());
		return -1;
	}

	CLogicPay logicPay;
	switch(payHis.type)
	{
	case 1:
		ret = logicPay.BuyCash(uid, 50, payHis.credit);break;
	case 2:
		ret = logicPay.BuyCash(uid, 110, payHis.credit);break;
	case 3:
		ret = logicPay.BuyCash(uid, 575, payHis.credit);break;
	case 4:
		ret = logicPay.BuyCash(uid, 1200, payHis.credit);break;
	case 5:
		ret = logicPay.BuyCash(uid, 6250, payHis.credit);break;
	case 6:
		ret = logicPay.BuyCash(uid, 2450, payHis.credit);break;
	default:
		m_errMsg = "data error";
		return -1;
	}
	if (ret != 0)
	{
		m_errMsg = "db error";
		error_log("[BuyCash fail][uid=%d,ret=%d,order=%s]", uid,ret,order_id.c_str());
		return -1;
	}

	out.push_back(CTrans::ITOS(payHis.credit));
	return 0;
}
