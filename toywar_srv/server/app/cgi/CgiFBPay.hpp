#include "LogicInc.h"
#include "LogicFBPay.h"

class CCgiFBPay : public CCgiBase
{
public:
	CCgiFBPay() : CCgiBase("fbpay")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(FBPay)

	int FBPay()
	{
		const string method = CCGIIn::GetCGIStr("method");
		const string request = CCGIIn::GetCGIStr("signed_request");
		if (method.empty() || request.empty())
		{
			return R_ERR_PARAM;
		}

		//info_log("[fbpay][method=%s,req=%s]",method.c_str(),request.c_str());

		vector<string> vtmp;
		CBasic::StringSplit(request, ".", vtmp);
		if (vtmp.size() != 2)
		{
			return R_ERR_PARAM;
		}
		string sig;
		Crypt::Base64UrlDecode(sig, vtmp[0]);
		string sdata;
		Crypt::Base64UrlDecode(sdata, vtmp[1]);

		Json::Value data;
		Json::Reader reader;
		if (!reader.parse(sdata, data))
		{
			ERROR_RETURN_MSG(R_ERR_PARAM, "parser_error");
		}
		string algorithm;
		if (!Json::GetString(data, "algorithm", algorithm) || !String::EqualNoCase(algorithm, "HMAC-SHA256"))
		{
			ERROR_RETURN_MSG(R_ERR_PARAM, "algo_error");
		}
		// check sig
		string check_sig = Crypt::HmacSha256(vtmp[1], OpenPlatform::GetPlatform()->GetAppKey());
		if (sig != check_sig)
		{
			error_log("[sig error][method=%s,req=%s]",method.c_str(),request.c_str());
			ERROR_RETURN_MSG(R_ERR_REFUSE, "sig_error");
		}

		string openid;
		if (!Json::GetString(data, "user_id", openid) || openid.empty())
		{
			ERROR_RETURN_MSG(R_ERR_PARAM, "user_id_error");
		}
		if (!Json::IsObject(data, "credits"))
		{
			ERROR_RETURN_MSG(R_ERR_PARAM, "credits_error");
		}
		Json::Value &credits = data["credits"];
		uint64_t order_id_uint = 0;
		if (!Json::GetUInt64(credits, "order_id", order_id_uint))
		{
			error_log("[order_id error][order_id_uint=%llu]",order_id_uint);
			ERROR_RETURN_MSG(R_ERR_PARAM, "order_id_error");
		}
		string order_id = Convert::UInt64ToString(order_id_uint);

		Json::Value content;
		if (method == "payments_get_items")
		{
			string itemId_str;
			unsigned itemId = 0;
			if (!Json::GetString(credits, "order_info", itemId_str) || !Convert::StringToUInt(itemId, itemId_str))
			{
				error_log("[fbpay][itemId_str=%s,itemId=%u]",itemId_str.c_str(),itemId);
				return R_ERR_PARAM;
			}

			FBItemInfo itemInfo;
			CLogicFBPay logic;
			int ret = logic.payments_get_items(openid, order_id, itemId, itemInfo);
			if (ret != 0)
				return ret;
			Json::Value item;
			item["item_id"] = itemInfo.item_id;
			item["title"] = itemInfo.title;
			item["description"] = itemInfo.description;
			item["image_url"] = itemInfo.image_url;
			item["product_url"] = itemInfo.product_url;
			item["price"] = itemInfo.price;

			content.resize(1);
			content[(unsigned)0] = item;
		}
		else if (method == "payments_status_update")
		{
			string next_state;
			string status;
			if (!Json::GetString(credits, "status", status))
			{
				error_log("[fbpay][openid=%s,order_id=%s,status=%s]",openid.c_str(),order_id.c_str(),status.c_str());
				return R_ERR_PARAM;
			}
			info_log("[fbpay][openid=%s,order_id=%s,status=%s]", openid.c_str(), order_id.c_str(), status.c_str());
			CLogicFBPay logic;
			int ret = logic.payments_status_update(openid, order_id, status, next_state);
			if (ret != 0)
				return ret;
			if (!next_state.empty())
				content["status"] = next_state;

		}
		else
		{
			return R_ERR_PARAM;
		}

		m_jsonResult["content"] = content;
		m_jsonResult["method"] = method;


		CGI_SEND_LOG("openid=%s&order_id=%s&method=%s", openid.c_str(),order_id.c_str(),method.c_str());
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiFBPay)
