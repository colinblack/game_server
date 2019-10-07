/*
 * CCgiMi2Prepay.cpp
 *	小米2付费接口: 根据前端请求,生成预付订单并返回
 *  Created on: 2018年11月13日
 */

#include "LogicInc.h"
#include "LogicQQPay.h"
#include "Mi2Platform.h"

class CCgiMi2Prepay : public CCgiBase
{
public:
	CCgiMi2Prepay() : CCgiBase("mi2pay")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(mi2pay)

	int mi2pay()
	{
		const string appId = CCGIIn::GetCGIStr("appId");
		const string appAccountId = CCGIIn::GetCGIStr("appAccountId");
		const string session = CCGIIn::GetCGIStr("session");
		const string itemid = CCGIIn::GetCGIStr("itemId");
		const string displayName = CCGIIn::GetCGIStr("displayName");
		const string feeValue = CCGIIn::GetCGIStr("feeValue");
		const string uid = CCGIIn::GetCGIStr("cpUserInfo");			//小米2 cpUserInfo代表前端传的uid

		const int itemnum = 1;
		int serverid = Config::GetZoneByUID(CTrans::STOI(uid));		//计算serverId,从数据库查询数据有用
		ConfigManager::Instance()->SetServer(serverid);

		if (appAccountId.empty() || itemid.empty() || appId.empty() || uid.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		QQItemInfo itemInfo;
		int ret = CLogicQQPay::GetItemInfo(itemid, itemInfo);		//根据itemid从配置中读取相关信息
		if(ret != 0)
		{
			return ret;
		}
		DataPayHistory payhis;
		payhis.channel = PT_Mi2;
		payhis.channel_pay_id = "";
		payhis.count = itemInfo.cash * itemnum;
		payhis.credit = 0;
		payhis.status = PST_PENDING;
		payhis.type = CTrans::STOI(itemInfo.itemid);
		payhis.uid = CTrans::STOI(uid);
		payhis.open_id = appAccountId;
		ret = CLogicQQPay().AddPayHistory(payhis);
		if (ret != 0)
		{
			error_log("[AddPayHistory fail][ret=%d,openid=%s]",	ret,appAccountId.c_str());
			DATA_ERROR_RETURN_MSG("AddPayHistory_fail");
		}

		m_jsonResult["cpOrderId"] = CTrans::UTOS(payhis.pay_id);	//回传前端字段1：cpOrderId

		string signature;
		map<string,string> params;
		params["appAccountId"] = appAccountId;
		params["appId"] = appId;
		params["cpOrderId"] = CTrans::UTOS(payhis.pay_id);
		params["cpUserInfo"] = uid;
		params["displayName"] = Crypt::UrlDecode(displayName);
		params["feeValue"] = feeValue;
		params["session"] = session;

		//string AppKey = "5321789087779";
		string AppKey = OpenPlatform::GetPlatform()->GetConfig("appkey");
		signature = Mi2Platform().GetSig(params,AppKey);			//生成签名

		m_jsonResult["sign"] = signature;							//回传前端字段2：sign

		CGI_SEND_LOG("openid=%s&itemid=%s", appAccountId.c_str(),itemid.c_str());
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiMi2Prepay)



