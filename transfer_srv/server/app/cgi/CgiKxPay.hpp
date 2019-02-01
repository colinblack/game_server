/*
 * CgiKxPay.cpp
 *
 *  Created on: 2012-2-6
 *      Author: dada
 */

#include "LogicInc.h"
#include "LogicKaixinPay.h"

class CCgiKxPay : public CCgiBase
{

public:

	CCgiKxPay() : CCgiBase("kx/pay")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(KxPay)

	int KxPay()
	{
		//get params
		int ret;
		if(OpenPlatform::GetType() != PT_KAIXIN)
		{
			error_log("[platform_error][cgi=kx/order,platform=%d]", OpenPlatform::GetType());
			SetError(R_ERR_REFUSE, "server_error");
			return R_ERR_REFUSE;
		}
		string openid = CCGIIn::GetCGIStr("uid");
		string sPayId = CCGIIn::GetCGIStr("orderid");
		string channelPayId = CCGIIn::GetCGIStr("pid");
		string test = CCGIIn::GetCGIStr("test");
		string status = CCGIIn::GetCGIStr("status");
		string callbackkey = CCGIIn::GetCGIStr("callbackkey");
		string sig = CCGIIn::GetCGIStr("sig");
		if(openid.empty() || sPayId.empty() || channelPayId.empty() ||
				status.empty() || callbackkey.empty() || sig.empty())
		{
			PARAM_ERROR_RETURN();
		}
		uint64_t payId;
		if(!Convert::StringToUInt64(payId, sPayId) || status != "1" || callbackkey != "pay")
		{
			PARAM_ERROR_RETURN();
		}

		//check sig
		CLogicKaixinPay logicKxPay;
		map<string, string> params;
		CgiUtil::GetRequestParams(params);
		if(!logicKxPay.CheckSignature(params, OpenPlatform::GetPlatform()->GetAppKey(), sig))
		{
			PARAM_ERROR_RETURN();
		}

		//pay
		unsigned uid;
		ret = LogicUserBasic::GetUid(uid, OpenPlatform::GetType(), openid);
		if(ret != 0)
		{
			return ret;
		}
		ret = logicKxPay.Pay(uid, payId, channelPayId);
		if(ret != 0)
		{
			return ret;
		}
		CGI_SEND_LOG("openid=%s&uid=%u&payid=%llu&status=1&channelpayid=%s&test=%s",
				openid.c_str(), uid, payId, channelPayId.c_str(), test.c_str());
		return 0;
	}


};

CGI_MAIN(CCgiKxPay)
