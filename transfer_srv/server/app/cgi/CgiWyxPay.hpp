#include "LogicInc.h"
#include "LogicWyxPay.h"

class CCgiWyxPay : public CCgiBase
{
public:

	CCgiWyxPay() : CCgiBase("wyx/prepay")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(buy)

	int buy()
	{
		const string openid = CCGIIn::GetCGIStr("openid");
		const string openkey = CCGIIn::GetCGIStr("openkey");
		int itemId = CCGIIn::GetCGIInt("itemid");
		if (openid.empty() || openkey.empty() || itemId == CCGIIn::CGI_INT_ERR)
		{
			return R_ERR_PARAM;
		}

		string order_id;
		string desc;
		int amount = 0;
		string token;

		CLogicWyxPay wyxPay;
		int ret = wyxPay.WyxGenerateOrder(openid, openkey, itemId, order_id, desc, amount, token);
		if (ret != 0)
			return ret;

		m_jsonResult["order_id"] = order_id;
		m_jsonResult["desc"] = desc;
		m_jsonResult["amount"] = amount;
		m_jsonResult["token"] = token;


		CGI_SEND_LOG("openid=%s&itemId=%d&order_id=%s", openid.c_str(), itemId, order_id.c_str());
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiWyxPay)
