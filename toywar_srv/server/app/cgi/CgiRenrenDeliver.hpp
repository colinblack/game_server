#include "LogicInc.h"
#include "IPurchase.h"

class CCgiRenrenDeliver : public CCgiBase
{

public:

	CCgiRenrenDeliver() : CCgiBase("pay/confirm")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(Deliver)

	int Deliver()
	{
		string user = CCGIIn::GetCGIStr("xn_sig_user");
		string skey = CCGIIn::GetCGIStr("xn_sig_skey");
		string order_id = CCGIIn::GetCGIStr("xn_sig_order_id");
		if (user.empty() || skey.empty() || order_id.empty())
		{
			return R_ERR_PARAM;
		}

		info_log("[RenrenDeliver param][xn_sig_user=%s,xn_sig_skey=%s,xn_sig_order_id=%s]",
				user.c_str(),skey.c_str(),order_id.c_str());

		CDataUserMapping mapping;
		unsigned int uid = 0;
		int ret = mapping.GetMapping(user, PT_RENREN, uid);	//TODO ...
		if (ret != 0)
		{
			return R_ERROR;
		}

		map<string, string> params;
		params.insert( pair<string, string>("xn_sig_user", user) );
		params.insert( pair<string, string>("xn_sig_skey", skey) );
		params.insert( pair<string, string>("xn_sig_order_id", order_id) );

		vector<string> out;
		ret = IPurchase::GetInstance()->DeliverGood(uid, params, out);
		if (ret != 0)
		{
			SetError(R_ERROR, IPurchase::GetInstance()->GetErrMsg());
			return ret;
		}

		m_jsonResult["app_res_user"] = user;
		m_jsonResult["app_res_order_id"] = order_id;
		m_jsonResult["app_res_amount"] = out[0];

		CGI_SEND_LOG("uid=%u&user=%s&order_id=%s", uid, user.c_str(), order_id.c_str());
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiRenrenDeliver)
