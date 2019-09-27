#include "LogicInc.h"
#include "LogicQQPay.h"
#include "VIVOPlatform.h"


class CCgiVIVOPrepay : public CCgiBase
{
public:
	CCgiVIVOPrepay() : CCgiBase("vivopay")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(vivopay)

	int vivopay()
	{
		const string packageName = CCGIIn::GetCGIStr("packageName");
		const string orderAmount = CCGIIn::GetCGIStr("orderAmount");
		const string orderTitle  = CCGIIn::GetCGIStr("orderTitle");
		const string orderDesc   = CCGIIn::GetCGIStr("orderDesc");
		const string itemid      = CCGIIn::GetCGIStr("itemId");
		const string openid      = CCGIIn::GetCGIStr("openId");
		const int itemnum = 1;

		//校验参数
		if (packageName.empty() || orderAmount.empty() || orderTitle.empty() || orderDesc.empty() || itemid.empty() || openid.empty())
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
		string out_trade_no    = openid + "," + itemid + "," + CTrans::UTOS(Time::GetGlobalTime());
		out_trade_no.reserve(64);
		unsigned fee = itemInfo.price * itemnum / 100;
		char fee_str[10];
		sprintf(fee_str,"%u.00",fee);

		//格式化本地时间
		time_t times = Time::GetGlobalTime();
		tm *tm_ = localtime(&times);
		tm_->tm_year += 1900;
		tm_->tm_mon +=  1;
		char date[20];
		sprintf(date,"%d%02d%02d%02d%02d%02d",tm_->tm_year,tm_->tm_mon,tm_->tm_mday,tm_->tm_hour,tm_->tm_min,tm_->tm_sec);

		//签名生成
		string signature;
		map<string,string> params;
		params.clear();
		params["packageName"] = packageName;
		params["cpOrderNumber"] = out_trade_no;
		params["notifyUrl"] = OpenPlatform::GetPlatform()->GetConfig("notifyurl");
		params["orderTime"] = string(date);
		params["orderAmount"] = string(fee_str);
		params["orderTitle"] = orderTitle;
		params["orderDesc"] = orderDesc;
		params["version"] = "1.0.0";
		string AppKey = OpenPlatform::GetPlatform()->GetConfig("appkey");
		signature = VIVOPlatform().GetSigStr(params,AppKey);

		//发送post请求
		params["signMethod"] = "MD5";
		string url = OpenPlatform::GetPlatform()->GetConfig("v3domain");
		string postdata;
		VIVOPlatform::formatUrl(params, signature, "", postdata);
		string response;
		if (!Network::HttpPostRequest(response, url, postdata) || response.empty())
		{
			error_log("[http request fail][url=%s,data=%s,openid=%s,response=%s]", url.c_str(), postdata.c_str(), openid.c_str(), response.c_str());
			ERROR_RETURN_MSG(R_ERR_NO_DATA, "http_request_fail");
		}

		//解析请求结果
		Json::Value result;
		Json::Reader reader;
		string responsetRet;
		if(response.empty())
		{
			ERROR_RETURN_MSG(R_ERR_NO_DATA, "http_request_fail");
		}
		info_log("response=%s,out_trade_no=%s",response.c_str(),out_trade_no.c_str());


		if (!reader.parse(response, result)
		|| !Json::GetString(result, "respCode", responsetRet))
		{
			error_log("param_response_error.");
		}
		else
		{
			unsigned ret = CTrans::STOI(responsetRet);
			if(ret != 200)
			{
				string respMsg;
				Json::GetString(result, "respMsg", respMsg);
				error_log("response_error.ret=%s,respMsg=%s",responsetRet.c_str(),respMsg.c_str());
				ERROR_RETURN_MSG(R_ERR_NO_DATA, "pay_request_fail");
			}
			else
			{
				m_jsonResult["orderInfo"] = response;
			}
		}
		CGI_SEND_LOG("openid=%s&itemid=%s", openid.c_str(),itemid.c_str());
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiVIVOPrepay)



