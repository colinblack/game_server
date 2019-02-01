#include "LogicInc.h"
#include "IPurchase.h"

class CCgiRenrenPay : public CCgiBase
{
public:

	CCgiRenrenPay() : CCgiBase("renrenpay")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_SIMPLE_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("buy", buy)
	CGI_ACTION_MAP_END

	int buy()
	{
		string userid = CCGIIn::GetCGIStr("xn_sig_user");
		if (userid.empty())
		{
			m_jsonResult["ret"] = 4;
			m_jsonResult["msg"] = "user error.";
			CGI_SEND_LOG("openid=%s", userid.c_str());
			return R_SUCCESS;
		}
		int type = CCGIIn::GetCGIInt("type");
		CDataUserMapping mapping;
		unsigned int uid = 0;
		int ret = mapping.GetMapping(userid, PT_RENREN, uid);	//TODO ...
		if (ret != 0)
		{
			m_jsonResult["ret"] = 1;
			m_jsonResult["msg"] = "query user failed.";
			CGI_SEND_LOG("openid=%s&type=%d", userid.c_str(), type);
			return R_SUCCESS;
		}
		int price = 0;
		string meta;
		switch(type)
		{
		case 1:
			price = 5;meta = "50";break;
		case 2:
			price = 10;meta = "100";break;
		case 3:
			price = 50;meta = "500";break;
		case 4:
			price = 100;meta = "1000";break;
		case 5:
			price = 500;meta = "5000";break;
		case 6:
			price = 200;meta = "2000";break;
		default:
			m_jsonResult["ret"] = 2;
			m_jsonResult["msg"] = "type error.";
			CGI_SEND_LOG("uid=%u&openid=%s&type=%d", uid, userid.c_str(), type);
			return R_SUCCESS;
		}
		vector<string> out;
		ret = IPurchase::GetInstance()->Purchase(uid, type, 1, price, price, meta, "", out);
		if (ret != 0)
		{
			m_jsonResult["ret"] = 3;
			m_jsonResult["msg"] = IPurchase::GetInstance()->GetErrMsg();
			CGI_SEND_LOG("uid=%u&openid=%s&type=%d&msg=%s", uid, userid.c_str(), type,
					IPurchase::GetInstance()->GetErrMsg().c_str());
			return R_SUCCESS;
		}
		m_jsonResult["ret"] = 0;
		m_jsonResult["order_id"] = out[0];
		m_jsonResult["token"] = out[1];
		CGI_SEND_LOG("uid=%u&openid=%s&type=%d&order_id=%s", uid, userid.c_str(), type, out[0].c_str());
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiRenrenPay)
