#include "LogicInc.h"
#include "LogicQQPay.h"
#include "OPPOPlatform.h"


class CCgiOPPOPrepay : public CCgiBase
{
public:
	CCgiOPPOPrepay() : CCgiBase("oppopay")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(oppopay)

	int oppopay()
	{
		const string productName = CCGIIn::GetCGIStr("productName");
		const string productDesc   = CCGIIn::GetCGIStr("orderDesc");
		const string itemid      = CCGIIn::GetCGIStr("itemId");
		const string count      = CCGIIn::GetCGIStr("itemcnt");
		const string appVersion = CCGIIn::GetCGIStr("appVersion");
		const string engineVersion = CCGIIn::GetCGIStr("engineVersion");
		const string openid      = CCGIIn::GetCGIStr("openId");

		unsigned itemnum = CTrans::STOI(count);
		if (productName.empty() || productDesc.empty() || itemid.empty() || count.empty() || itemnum <= 0 || appVersion.empty() || engineVersion.empty() || openid.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		//读取物品配置
		QQItemInfo itemInfo;
		int ret = CLogicQQPay::GetItemInfo(itemid, itemInfo);
		if(ret)
		{
			PARAM_ERROR_RETURN_MSG("itemid_error");
		}

		//获取uid
		unsigned uid = 0;
		CDataUserMapping dbUserMapping;
		ret = dbUserMapping.GetMapping(openid, 0, uid);
		if (ret != 0)
		{
			PARAM_ERROR_RETURN_MSG("no_uid");
		}
		int serverid = Config::GetZoneByUID(uid);
		ConfigManager::Instance()->SetServer(serverid);

		//随机生成预支付订单号最长64位
		string out_trade_no    = "order_" + openid + "_" + itemid + "_" + CTrans::UTOS(Time::GetGlobalTime()) + "_" + CTrans::UTOS(Math::GetRandomInt());
		unsigned fee = itemInfo.price * itemnum;

		//签名生成
		string signature;
		map<string,string> params;
		params.clear();
		params["appId"] = OpenPlatform::GetPlatform()->GetConfig("appid");
		params["openId"] = openid;
		params["timestamp"] = CTrans::ITOS(Time::GetGlobalTime());
		params["productName"] = productName;
		params["productDesc"] = productDesc;
		params["count"] = count;
		params["price"] = CTrans::ITOS(fee);
		params["currency"] = "CNY";
		params["callBackUrl"] = OpenPlatform::GetPlatform()->GetConfig("notifyurl");
		params["cpOrderId"] = out_trade_no;
		params["attach"] = openid;
		params["appVersion"] = appVersion;
		params["engineVersion"] = engineVersion;
		//string secretKey = OpenPlatform::GetPlatform()->GetConfig("secretkey");
		string secretKey = OpenPlatform::GetPlatform()->GetConfig("appkey");
		signature = OPPOPlatform().GetSigStr(params,secretKey);

		//发送post请求
		string url = OpenPlatform::GetPlatform()->GetConfig("v3domain");
		string postdata;
		OPPOPlatform::formatUrl(params, signature, "", postdata);
		string response;
		if (!Network::HttpPostRequest(response, url, postdata) || response.empty())
		{
			error_log("[http request fail][url=%s,data=%s,openid=%s,response=%s]", url.c_str(), postdata.c_str(), openid.c_str(), response.c_str());
			ERROR_RETURN_MSG(R_ERR_NO_DATA, "http_request_fail");
		}

		//解析请求结果
		Json::Value result;
		Json::Reader reader;
		int responsetRet = 0;
		if(response.empty())
		{
			ERROR_RETURN_MSG(R_ERR_NO_DATA, "http_request_fail");
		}
		info_log("response=%s",response.c_str());

		if (!reader.parse(response, result)
		|| !Json::GetInt(result, "code", responsetRet))
		{
			if(responsetRet != 200)
			{
				string respMsg;
				Json::GetString(result, "msg", respMsg);
				error_log("response_error.ret=%d,respMsg=%s",responsetRet,respMsg.c_str());
				ERROR_RETURN_MSG(R_ERR_NO_DATA, "pay_request_fail");
			}
			else
			{
				string orderNo = result["data"]["orderNo"].asString();
				string appKey = OpenPlatform::GetPlatform()->GetConfig("appkey");
				map<string,string>param;
				param.clear();
				param["orderNo"] = orderNo;
				param["timestamp"] = CTrans::ITOS(Time::GetGlobalTime());
				string paySign = OPPOPlatform().GetSigStr(param,appKey);
				m_jsonResult["orderNo"] = orderNo;
				m_jsonResult["paySign"] = paySign;
				m_jsonResult["timestamp"] = param["timestamp"];
			}
		}
		CGI_SEND_LOG("openid=%s&itemid=%s", openid.c_str(),itemid.c_str());
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiOPPOPrepay)



