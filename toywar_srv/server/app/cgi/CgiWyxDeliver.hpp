#include "LogicInc.h"
#include "LogicWyxPay.h"

class CCgiWyxDeliver : public CCgiBase
{
public:

	CCgiWyxDeliver() : CCgiBase("wyx/pay")
	{
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(deliver)

	int deliver()
	{
		string openid = CCGIIn::GetCGIStr("order_uid");
		string order_id = CCGIIn::GetCGIStr("order_id");
		string appid = CCGIIn::GetCGIStr("appkey");
		int amount = CCGIIn::GetCGIInt("amount");
		if (openid.empty() || appid.empty() || order_id.empty())
		{
			return R_ERR_PARAM;
		}

		CLogicWyxPay wyxPay;
		int ret = wyxPay.WyxDeliverGood(openid, order_id, appid, amount);
		if (ret != 0)
		{
			CgiUtil::PrintText(GetErrorMessage());
			return ret;
		}

		CgiUtil::PrintText("OK");
		CGI_SEND_LOG("openid=%s&order_id=%s&amount=%d", openid.c_str(), order_id.c_str(), amount);
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiWyxDeliver)
