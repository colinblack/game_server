#include "LogicInc.h"
#include "LogicRockpay.h"

class CCgiRockpayConfirm : public CCgiBase
{
public:
	CCgiRockpayConfirm() : CCgiBase("rockpay/confirm")
	{
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(Confirm)

	int Confirm()
	{
		const string aoid = CCGIIn::GetCGIStr("aoid");
		const string m1 = CCGIIn::GetCGIStr("m1");
		const string m2 = CCGIIn::GetCGIStr("m2");
		const string tid = CCGIIn::GetCGIStr("tid");
		const string v_code = CCGIIn::GetCGIStr("v_code");

		if (aoid.empty() || m2.empty() || tid.empty() || v_code.empty())
		{
			error_log("[param error][aoid=%s,m1=%s,m2=%s,tid=%s,v_code=%s]",
					aoid.c_str(),m1.c_str(),m2.c_str(),tid.c_str(),v_code.c_str());

			//CgiUtil::PrintText("aoid="+aoid+"&m1="+m1+"&m2="+m2+"&tid="+tid+"&v_code="+v_code);
			return R_ERR_PARAM;
		}

		int cash = 0;
		CLogicRockpay rockpay;
		int ret = rockpay.PayCallback(aoid, m1, m2, tid, v_code, cash);
		if (ret != 0)
		{
			CgiUtil::ScriptRedirect("/pay.html?error="+CTrans::ITOS(ret)+"&msg="+rockpay.GetErrMsg());
			return ret;
		}

		CGI_SEND_LOG("aoid=%s&m1=%s", aoid.c_str(), m1.c_str());
		CgiUtil::ScriptRedirect("/pay.html?error=0&cash="+CTrans::ITOS(cash));
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiRockpayConfirm)
