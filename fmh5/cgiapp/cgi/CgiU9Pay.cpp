/*
 * CgiU9Pay.cpp
 *
 *  Created on: 2018年8月24日
 *      Author: Ralf
 */

#include "LogicInc.h"
#include "LogicQQPay.h"

class CCgiU9Pay : public CCgiBase
{
public:
	CCgiU9Pay() : CCgiBase("u9pay")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(u9pay)

	int u9pay()
	{
		const string openid = CCGIIn::GetCGIStr("openid");
		const string itemid = CCGIIn::GetCGIStr("itemid");
		const int itemnum = CCGIIn::GetCGIInt("itemnum", 0, 100000, 0, 0);
		int serverid = CCGIIn::GetCGIInt("serverid", 0, 100000, 0, 0);
		ConfigManager::Instance()->SetServer(serverid);

		if (openid.empty() || itemid.empty() || itemnum == 0)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		QQItemInfo itemInfo;
		int ret = CLogicQQPay::GetItemInfo(itemid, itemInfo);
		if(ret)
			return ret;

		unsigned uid = 0;
		ret = CDataUserMapping().GetMapping(openid, 0, uid);
		if(ret)
		{
			PARAM_ERROR_RETURN_MSG("no_uid");
		}

		DataPayHistory payhis;
		payhis.channel = PT_U9;
		payhis.channel_pay_id = "";
		payhis.count = itemInfo.cash * itemnum;
		payhis.credit = 0;
		payhis.status = PST_PENDING;
		payhis.type = CTrans::STOI(itemInfo.itemid);
		payhis.uid = uid;
		payhis.open_id = openid;
		ret = CLogicQQPay().AddPayHistory(payhis);
		if (ret != 0)
		{
			error_log("[AddPayHistory fail][ret=%d,openid=%s]",	ret,openid.c_str());
			DATA_ERROR_RETURN_MSG("AddPayHistory_fail");
		}

		m_jsonResult["pay_id"] = CTrans::UTOS(payhis.pay_id);

		CGI_SEND_LOG("openid=%s&itemid=%s", openid.c_str(),itemid.c_str());
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiU9Pay)



