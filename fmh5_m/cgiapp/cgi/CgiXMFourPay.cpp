#include "LogicInc.h"
#include "XMFourPlatform.h"

class CCgiXMFourPay : public CCgiBase
{
public:
	CCgiXMFourPay() : CCgiBase("qqpay")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(qqpay)

	int qqpay()
	{
		//获取前端参数
		const string itemid = CCGIIn::GetCGIStr("itemid");//物品id
		const string itemcnt = CCGIIn::GetCGIStr("itemcnt");//物品数量
		const string openid = CCGIIn::GetCGIStr("openid");//openid
		const string token = CCGIIn::GetCGIStr("token");//token
		int serverid = CCGIIn::GetCGIInt("serverid", 0, 100000, 0, 0);//serverid
		ConfigManager::Instance()->SetServer(serverid);

		if (openid.empty() ||  itemid.empty() || itemcnt.empty() || CTrans::STOI(itemcnt) == 0 || token.empty())
		{
			error_log("openid=%s,itemid=%s,itemcnt=%s,token=%s", openid.c_str(), itemid.c_str(), itemcnt.c_str(),token.c_str());
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		//读取物品配置
		QQItemInfo itemInfo;
		int ret = CLogicQQPay::GetItemInfo(itemid, itemInfo);
		if(ret)
		{
			PARAM_ERROR_RETURN_MSG("itemid_error");
		}

		unsigned totalfee = itemInfo.price * CTrans::STOI(itemcnt);

		//获取uid
		unsigned uid = 0;
		CDataUserMapping dbUserMapping;
		ret = dbUserMapping.GetMapping(openid, 0, uid);
		if (ret != 0)
		{
			PARAM_ERROR_RETURN_MSG("no_uid");
		}


		//--------------设置请求参数
		map<string,string>req;
		string reqUrl    = "https://platform.xgame.wali.com/v2/platform/pay";

		req["token"]       = token;
		req["timestamp"]   = CTrans::UTOS(Time::GetGlobalTime()) + "000";
		req["appId"]       = OpenPlatform::GetPlatform()->GetAppId();
		req["gameId"]      = OpenPlatform::GetPlatform()->GetConfig("gameid");
		req["currency"]    = "1";//人民币
		req["amount"]      = itemcnt;
		req["price"]       = CTrans::UTOS(totalfee);
		req["sname"]       = itemid;
		req["extend"]      = openid + "_" + uid + "_" + itemid + "_" + itemcnt;
		const string sigkey = OpenPlatform::GetPlatform()->GetConfig("appkey");//签名key
		const string sign  = XMFourPlatform::GetSigStr(req,sigkey);

		//发送请求
		string response;
		string postdata ;
		XMFourPlatform::GetPostData(req,sign,postdata);

		if (!Network::HttpPostRequest(response, reqUrl, postdata) || response.empty())
		{
			error_log("[http request fail][url=%s,openid=%s,response=%s,postdata=%s]", reqUrl.c_str(), openid.c_str(), response.c_str(),postdata.c_str());
			ERROR_RETURN_MSG(R_ERR_NO_DATA, "http_request_fail");
		}

		//解析返回结果
		Json::Value value;
		if (!Json::Reader().parse(response, value))
		{
			error_log("[response_data_parse_failed][response=%s]",response.c_str());
			ERROR_RETURN_MSG(R_ERROR,"response_data_parse_failed");
		}
		//是否成功返回
		int code = 0;
		if (!Json::GetInt(value, "code", code) && code != 200 )
		{
			error_log("[pay_request_fail][code=%d]",code);
			ERROR_RETURN_MSG(R_ERROR,"pay_request_fail");
		}
		else
		{
			if(!Json::IsObject(value, "data"))
			{
				error_log("[orderid_parse_failed][code=%d]",code);
				ERROR_RETURN_MSG(R_ERROR,"orderid_parse_failed");
			}
			else
			{
				//获取订单号
				Json::Value paydata;
				if(!Json::GetObject(value, "data",paydata))
				{
					error_log("[pay_data_parese__fail][code=%d]",code);
					ERROR_RETURN_MSG(R_ERROR,"pay_data_parese__fail");
				}
				else
				{
					string orderId;
					if (!Json::GetString(paydata, "orderId", orderId))
					{
						ERROR_RETURN_MSG(R_ERROR,"orderId_parese__fail");
					}
					else
					{
						m_jsonResult["orderId"] = orderId;
					}
				}
			}

		}
		return R_SUCCESS;
	}
};

CGI_MAIN(CCgiXMFourPay)
