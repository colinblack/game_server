/*
 * CgiKxOrder.cpp
 *
 *  Created on: 2012-2-6
 *      Author: dada
 */

#include "LogicInc.h"
#include "LogicKaixinPay.h"

class CCgiKxOrder : public CCgiBase
{

public:

	CCgiKxOrder() : CCgiBase("kx/order")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(KxOrder)

	int KxOrder()
	{
		int ret;
		if(OpenPlatform::GetType() != PT_KAIXIN)
		{
			error_log("[platform_error][cgi=kx/order,platform=%d]", OpenPlatform::GetType());
			SetError(R_ERR_REFUSE, "server_error");
			return R_ERR_REFUSE;
		}
		string openid = CCGIIn::GetCGIStr("openid");
		int type = CCGIIn::GetCGIInt("type");
		int cash = CCGIIn::GetCGIInt("cash");
		int price = CCGIIn::GetCGIInt("price");
		if(openid.empty() || type == CCGIIn::CGI_INT_ERR ||
				cash == CCGIIn::CGI_INT_ERR || price == CCGIIn::CGI_INT_ERR)
		{
			PARAM_ERROR_RETURN();
		}

		unsigned uid;
		ret = LogicUserBasic::GetUid(uid, OpenPlatform::GetType(), openid);
		if(ret != 0)
		{
			return ret;
		}

		CLogicKaixinPay logicKxPay;
		uint64_t payId;
		ret = logicKxPay.Order(uid, type, cash, price, payId);
		if(ret != 0)
		{
			return ret;
		}
		m_jsonResult["payid"] = Convert::UInt64ToString(payId);

		CGI_SEND_LOG("openid=%s&uid=%u&type=%d&cash=%d&price=%d&payid=%llu",
				openid.c_str(), uid, type, cash, price, payId);
		return 0;
	}


};

CGI_MAIN(CCgiKxOrder)

