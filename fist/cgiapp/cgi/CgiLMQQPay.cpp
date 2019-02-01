#include "LogicInc.h"
#include "LiMiPlatform.h"

class CCgiLMQQPay : public CCgiBase
{
public:
	CCgiLMQQPay() : CCgiBase("qqpay")
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
		int serverid = CCGIIn::GetCGIInt("serverid", 0, 100000, 0, 0);//serverid
		ConfigManager::Instance()->SetServer(serverid);

		if (openid.empty() ||  itemid.empty() || itemcnt.empty() || CTrans::STOI(itemcnt) == 0)
		{
			error_log("openid=%s,itemid=%s,itemcnt=%s", openid.c_str(), itemid.c_str(), itemcnt.c_str());
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

		//生成随机字符串
		string out_trade_no    = openid + CTrans::UTOS(Time::GetGlobalTime()) + CTrans::UTOS(Math::GetRandomInt());
		string out_trade_no_32 = Crypt::Md5Encode(out_trade_no);
		string randomstr = CTrans::UTOS(Math::GetRandomInt());
		string randomstr_32 = Crypt::Md5Encode(randomstr);

		//--------------设置请求参数
		map<string,string>req;
		string reqUrl    = "https://qpay.qq.com/cgi-bin/pay/qpay_unified_order.cgi";
		string attach    = "";
		attach += openid + "_" + CTrans::UTOS(uid) + "_" + itemid + "_" + itemcnt;//附加数据(openid+uid+itemid_itemcnt)
		const string noncestr = randomstr_32;//随机32位字符串
		const string body      = "FarmGame-H5";//商品描述
		const string outtradeno = out_trade_no_32;//商户订单号
		const string feetype = "CNY";//货币类型定义
		const string spbillcreateip =  m_ipstr;//终端IP
		const string tradetype = "JSAPI";//支付场景
		const string notifyurl = OpenPlatform::GetPlatform()->GetConfig("notifyurl");//支付结果通知地址
		const string sigkey = OpenPlatform::GetPlatform()->GetConfig("sigkey");//签名key
		const string appid    = OpenPlatform::GetPlatform()->GetAppId();//appid
		const string mchid   = OpenPlatform::GetPlatform()->GetConfig("mchid");//商户id
		req["appid"]       = appid;
		req["mch_id"]      = mchid;
		req["nonce_str"]   = noncestr;
		req["body"]        = body;
		req["attach"]      = attach;
		req["out_trade_no"] = outtradeno;
		req["fee_type"]     = feetype;
		req["total_fee"]    = CTrans::UTOS(totalfee);
		req["spbill_create_ip"] = spbillcreateip;
		req["trade_type"]   = tradetype;
		req["notify_url"]   = notifyurl;
		const string sign   = LiMiPlatform::GetSigStr(req,sigkey);
		req["sign"]         = sign;

		//发送请求
		string response;
		string postdata = LiMiPlatform::GenerateXMLStr(req);
		if (!Network::HttpPostRequest(response, reqUrl, postdata) || response.empty())
		{
			error_log("[http request fail][url=%s,openid=%s,response=%s,postdata=%s]", reqUrl.c_str(), openid.c_str(), response.c_str(),postdata.c_str());
			ERROR_RETURN_MSG(R_ERR_NO_DATA, "http_request_fail");
		}

		//解析返回结果
		CMarkupSTL xmlConf;
		if(!xmlConf.SetDoc(response.c_str()) || !xmlConf.FindElem("xml"))
		{
			error_log("[parse fail][url=%s,openid=%s,response=%s,postdata=%s]", reqUrl.c_str(), openid.c_str(), response.c_str(),postdata.c_str());
			ERROR_RETURN_MSG(R_ERROR, "xml_fail");
		}
		xmlConf.IntoElem();
		string return_code;
		string result_code;

		xmlConf.ResetMainPos();
		if(!xmlConf.FindElem("return_code"))
		{
			error_log("[parse return_code info fail][url=%s,openid=%s,response=%s,postdata=%s]", reqUrl.c_str(), openid.c_str(), response.c_str(),postdata.c_str());
			ERROR_RETURN_MSG(R_ERROR, "param_item_fail");
		}
		return_code = xmlConf.GetData();

		xmlConf.ResetMainPos();
		if(!xmlConf.FindElem("result_code"))
		{
			error_log("[parse result_code info fail][url=%s,openid=%s,response=%s,postdata=%s]", reqUrl.c_str(), openid.c_str(), response.c_str(),postdata.c_str());
			ERROR_RETURN_MSG(R_ERROR, "param_item_fail");
		}
		result_code = xmlConf.GetData();

		if(return_code != "SUCCESS" || result_code != "SUCCESS")
		{
			//打印错误日志
			if(return_code != "SUCCESS")
			{
				error_log("[return_code fail][url=%s,openid=%s,response=%s,postdata=%s]", reqUrl.c_str(), openid.c_str(), response.c_str(),postdata.c_str());
				PARAM_ERROR_RETURN_MSG(return_code);
			}
			else if(result_code != "SUCCESS")
			{
				xmlConf.ResetMainPos();
				if(!xmlConf.FindElem("err_code"))
				{
					error_log("[err_code fail][url=%s,openid=%s,response=%s,postdata=%s]", reqUrl.c_str(), openid.c_str(), response.c_str(),postdata.c_str());
					ERROR_RETURN_MSG(R_ERROR, "param_item_fail");
				}
				string result_code = xmlConf.GetData();
				error_log("[result_code fail][url=%s,openid=%s,response=%s,postdata=%s]", reqUrl.c_str(), openid.c_str(), response.c_str(),postdata.c_str());
				ERROR_RETURN_MSG(R_ERROR, "request_failed");
			}
		}
		else
		{
			xmlConf.ResetMainPos();
			if(!xmlConf.FindElem("trade_type"))
			{
				error_log("[trade_type fail][url=%s,openid=%s,response=%s,postdata=%s]", reqUrl.c_str(), openid.c_str(), response.c_str(),postdata.c_str());
				ERROR_RETURN_MSG(R_ERROR, "param_item_fail");
			}
			string trade_type = xmlConf.GetData();

			xmlConf.ResetMainPos();
			if(!xmlConf.FindElem("prepay_id"))
			{
				error_log("[prepay_id fail][url=%s,openid=%s,response=%s,postdata=%s]", reqUrl.c_str(), openid.c_str(), response.c_str(),postdata.c_str());
				ERROR_RETURN_MSG(R_ERROR, "param_item_fail");
			}
			string prepay_id = xmlConf.GetData();

			m_jsonResult["trade_type"] = trade_type;
			m_jsonResult["prepay_id"] = prepay_id;
		}

		return R_SUCCESS;
	}
};

CGI_MAIN(CCgiLMQQPay)
