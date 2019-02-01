#include "LogicInc.h"
#include "LogicRockpay.h"

class CCgiRockpayCharge : public CCgiBase
{
public:
	CCgiRockpayCharge() : CCgiBase("rockpay/charge")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(GenerateOrderId)

	int GenerateOrderId()
	{
		const string openid = CCGIIn::GetCGIStr("openid");
		if (openid.empty())
		{
			return R_ERR_PARAM;
		}

		string app;
		string aoid;
		string r_url;
		string m1;
		string m2;
		string v_code;
		CLogicRockpay rockpay;
		int ret = rockpay.GenerateOrderId(openid, app, aoid, r_url, m1, m2, v_code);
		if (ret != 0)
		{
			return ret;
		}

		m_jsonResult["app"] = app;
		m_jsonResult["aoid"] = aoid;
		m_jsonResult["r_url"] = r_url;
		m_jsonResult["m1"] = m1;
		m_jsonResult["m2"] = m2;
		m_jsonResult["v_code"] = v_code;

		CGI_SEND_LOG("openid=%s&aoid=%s", openid.c_str(), aoid.c_str());
		return R_SUCCESS;
	}
};

CGI_MAIN(CCgiRockpayCharge)
