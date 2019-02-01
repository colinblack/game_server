/*
 * Cgi4399Deliver.cpp
 *
 *  Created on: 2015-4-30
 *      Author: Ralf
 */

#include "Logic4399Pay.h"
#include "LogicInc.h"
#include "LogicCMD.h"

class CCgi4399Deliver : public CCgiBase
{
public:
	CCgi4399Deliver() : CCgiBase("deliver4399")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(deliver)

	int deliver()
	{
		if(m_ipstr != OpenPlatform::GetPlatform()->GetConfig(CONFIG_4399_PAY_IP_1)
		&& m_ipstr != OpenPlatform::GetPlatform()->GetConfig(CONFIG_4399_PAY_IP_2)
		&& m_ipstr != OpenPlatform::GetPlatform()->GetConfig(CONFIG_4399_PAY_IP_3)
		&& m_ipstr != OpenPlatform::GetPlatform()->GetConfig(CONFIG_4399_PAY_IP_4)
		&& m_ipstr != OpenPlatform::GetPlatform()->GetConfig(CONFIG_4399_PAY_IP_5)
		&& m_ipstr != OpenPlatform::GetPlatform()->GetConfig("4399_pay_ip_6")
		&& m_ipstr != OpenPlatform::GetPlatform()->GetConfig("4399_pay_ip_7")
		&& m_ipstr != OpenPlatform::GetPlatform()->GetConfig("4399_pay_ip_8"))
		{
			CgiUtil::PrintText("-10");
			PARAM_ERROR_RETURN_MSG("ip_error");
		}

		const string openid = CCGIIn::GetCGIStr("username");
		const string order = CCGIIn::GetCGIStr("order");
		const string flag = CCGIIn::GetCGIStr("flag");
		const unsigned cash = CCGIIn::GetCGIInt("gold");
		const unsigned time = CCGIIn::GetCGIInt("time");
		const double money = CCGIIn::GetCGIDbl("money", 0, 100000000, 0, 0);
		if(openid.empty() || order.empty() || flag.empty() ||
		cash == CCGIIn::CGI_INT_ERR || time == CCGIIn::CGI_INT_ERR || cash == 0)
		{
			CgiUtil::PrintText("-1");
			PARAM_ERROR_RETURN_MSG("no_param");
		}

		if (Math::Abs(Time::GetGlobalTime() - time) > 30)
		{
			CgiUtil::PrintText("-4");
			PARAM_ERROR_RETURN_MSG("time_error");
		}

		string osig  = order + openid
				+ CTrans::ITOS(cash) + CTrans::ITOS(time)
				+ OpenPlatform::GetPlatform()->GetConfig(CONFIG_4399_PAY_KEY);
		string sig = Crypt::Md5Encode(osig);
		if(sig != flag)
		{
			CgiUtil::PrintText("-2");
			PARAM_ERROR_RETURN_MSG("flag_error");
		}

		int server = 0;
		Config::GetDB(server);
		CLogic4399Pay logicPay;
		int ret = logicPay.deliver(openid, server, cash, order, (unsigned)(money*100));
		if (ret != 0)
		{
			CgiUtil::PrintText("-100");
			return ret;
		}

		//CgiUtil::PrintText("{\"ret\":0,\"msg\":\"OK\"}");防止回调过久移动到各平台虚函数
		CGI_SEND_LOG("openid=%s&billno=%s&serverid=%d&num=%u", openid.c_str(),order.c_str(),server,cash);
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgi4399Deliver)

