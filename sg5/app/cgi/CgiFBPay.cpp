#include "LogicInc.h"
#include "LogicFBPay.h"

class CCgiFBPay : public CCgiBase
{
public:
	CCgiFBPay() : CCgiBase("fbpay")
	{
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_PARSE_DATA);
		SetFeature(CF_GET_REMOTE_IP);
	}

	CGI_DIRECT_PROCESS(FBPay)

	/*
	int FBPay()
	{
		const string method = CCGIIn::GetCGIStr("method");
		const string request = CCGIIn::GetCGIStr("signed_request");
		if (method.empty() || request.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		vector<string> vtmp;
		CBasic::StringSplit(request, ".", vtmp);
		if (vtmp.size() != 2)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		string sig;
		Crypt::Base64UrlDecode(sig, vtmp[0]);
		string sdata;
		Crypt::Base64UrlDecode(sdata, vtmp[1]);

		Json::Value data;
		Json::Reader reader;
		if (!reader.parse(sdata, data))
		{
			PARAM_ERROR_RETURN_MSG("parser_error");
		}
		string algorithm;
		if (!Json::GetString(data, "algorithm", algorithm) || !String::EqualNoCase(algorithm, "HMAC-SHA256"))
		{
			PARAM_ERROR_RETURN_MSG("algo_error");
		}
		// check sig
		string check_sig = Crypt::HmacSha256(vtmp[1], OpenPlatform::GetPlatform()->GetAppKey());
		if (sig != check_sig)
		{
			error_log("[sig error][method=%s,req=%s]",method.c_str(),request.c_str());
			REFUSE_RETURN_MSG("sig_error");
		}

		string openid;
		if (!Json::GetString(data, "user_id", openid) || openid.empty())
		{
			PARAM_ERROR_RETURN_MSG("user_id_error");
		}
		if (!Json::IsObject(data, "credits"))
		{
			PARAM_ERROR_RETURN_MSG("credits_error");
		}
		Json::Value &credits = data["credits"];
		uint64_t order_id_uint = 0;
		if (!Json::GetUInt64(credits, "order_id", order_id_uint))
		{
			error_log("[order_id error][order_id_uint=%llu]",order_id_uint);
			PARAM_ERROR_RETURN_MSG("order_id_error");
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
				PARAM_ERROR_RETURN_MSG("param_error_order");
			}
			string locale;
			if (data.isMember("user") && data["user"].isObject() && data["user"].isMember("locale")
					&& data["user"]["locale"].isString())
			{
				locale = data["user"]["locale"].asString();
				String::ToLower(locale);
			}

			FBItemInfo itemInfo;
			CLogicFBPay logic;
			int ret = logic.payments_get_items(openid, order_id, itemId, locale, itemInfo);
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
			CLogicFBPay logic;
			int ret = logic.payments_status_update(openid, order_id, status, next_state);
			if (ret != 0)
				return ret;
			if (!next_state.empty())
				content["status"] = next_state;
		}
		else
		{
			PARAM_ERROR_RETURN_MSG("param_error_method");
		}

		m_jsonResult["content"] = content;
		m_jsonResult["method"] = method;

		CGI_SEND_LOG("openid=%s&order_id=%s&method=%s", openid.c_str(),order_id.c_str(),method.c_str());
		return R_SUCCESS;
	}
    */

    void StrToHex(const string &in, string &out)
    {
        static const char* table = "0123456789abcdef";
        size_t len = in.length();

        out.clear();
        out.reserve(2 * len);
        for (size_t i = 0; i < len; ++i)
        {
            char c = in[i];
            out.push_back(table[(c & 0xF0) >> 4]);
            out.push_back(table[c & 0x0F]);
        }
    }

	int FBPay()
	{
	    /*
        extern char **environ;
        for (int i = 0; environ[i] != NULL; i++)
            error_log(">>>> envir[%d] %s\n", i, environ[i]);
        */
	    
		string method;
		CgiUtil::GetRequestMethod(method);

		if(method == "GET")
		{
            string payments_token = OpenPlatform::GetPlatform()->GetConfig(CONFIG_FB_RTU_PAYMENTS_TOKEN);
			const string verify_token = CCGIIn::GetCGIStr("hub.verify_token");
			const string mode = CCGIIn::GetCGIStr("hub.mode");
			const string challenge = CCGIIn::GetCGIStr("hub.challenge");
			if (verify_token.empty() || verify_token != payments_token
					|| mode.empty() || mode != "subscribe")
			{
				error_log("[verify_token error][hub.vrify_token=%s,hub.mode=%s]",
				       verify_token.c_str(),mode.c_str());
				REFUSE_RETURN_MSG("sig_error");
			}

            CgiUtil::PrintText(challenge);
		}
		else if (method == "POST") //TODO when failed, return 404, if success, return nothing.
		{
		    //error_log("[fbpay start][m_strData=%s]", m_strData.c_str());

            string app_secret = OpenPlatform::GetPlatform()->GetConfig(CONFIG_FB_APP_SECRET);

			//verify X-Hub-Signature signature
			//http://www.sitepoint.com/using-facebooks-realtime-updates-and-subscription-api/
            string signature;
            const char *pSignature = getenv("HTTP_X_HUB_SIGNATURE");
            if (pSignature)
                signature = pSignature;

            string sha1 = Crypt::HmacSha1(m_strData, app_secret);
            string expected_sig;
            StrToHex(sha1, expected_sig);
            if (signature.substr(strlen("sha1=")) != expected_sig)
            {
                error_log("[sig error][body=%s,sig=%s,sha1=%s,expected_sig=%s]", m_strData.c_str(), 
                        signature.c_str(), sha1.c_str(), expected_sig.c_str());
                REFUSE_RETURN_MSG("sig_error");
            }

			if (m_data["object"] != "payments")
			{
				PARAM_ERROR_RETURN_MSG("not_payments_object");
			}

            size_t zero = 0;
            size_t one = 1;
			if (m_data["entry"].size() != 1 
			        || !m_data["entry"][zero].isMember("id")
			        || m_data["entry"][zero]["changed_fields"].size() != 1
			        || m_data["entry"][zero]["changed_fields"][zero].asString() != "actions")
            {
				PARAM_ERROR_RETURN_MSG("invalid_entry");
            }

			string payment_id = m_data["entry"][zero]["id"].asString();
            //CGI_SEND_LOG("payment_id=%s", payment_id.c_str());

			//get app_access_token by /oauth/access_token?client_id=&client_secret=
			//&grant_type=client_credentials
			string app_access_token = OpenPlatform::GetPlatform()->GetConfig(CONFIG_FB_APP_ACCESS_TOKEN);
			string url = "https://graph.facebook.com/" + payment_id + "?access_token=" + app_access_token;
			string response;
			if (!Network::HttpGetRequest(response, url) || response.empty())
			{
				error_log("[http request fail][payment_id=%s]",payment_id.c_str());
				ERROR_RETURN_MSG(R_ERR_NO_DATA, "http_request_fail");
			}

			Json::Value result;
			Json::Reader query_reader;
			if (response.empty() || !query_reader.parse(response, result)
					|| !result.isMember("id") || result["id"].asString() != payment_id)
			{
				error_log("[response error][response=%s]",response.c_str());
				ERROR_RETURN_MSG(R_ERR_NO_DATA, "response_error");
			}

			bool noitem = false;
			string openid = result["user"]["id"].asString();
			string openname = result["user"]["name"].asString();
			unsigned serverid = 0;
			if(result.isMember("request_id"))
			{
				string request_id = result["request_id"].asString();
				vector<string> rlt;
				String::Split(request_id, '.', rlt);
				serverid = atoi(rlt[0].c_str());
			}
			string product = OpenPlatform::GetPlatform()->GetConfig(CONFIG_FB_PAYMENT_PRODUCT);
			unsigned quantity = result["items"][zero]["quantity"].asUInt();
			if (result["items"].size() != 1
					|| result["items"][zero]["type"].asString() != "IN_APP_PURCHASE"
					|| result["items"][zero]["product"].asString() != product)
			{
				noitem = true;
				error_log("[invalid payment id][invalid items]");
			}

			bool charge = false;
			bool charged = false;
			bool chargeback = false;
			bool dispute = false;
			if (result["actions"].size() == 1
				&& result["actions"][zero]["type"].asString() == "charge"
				&& result["actions"][zero]["status"].asString() == "completed")
				charge = true;
			if (result["actions"].size() >= 1
				&& result["actions"][zero]["type"].asString() == "charge"
				&& result["actions"][zero]["status"].asString() == "completed")
				charged = true;
			if (result["actions"].size() > 1
			    && (result["actions"][one]["type"].asString() == "chargeback"
			    	|| result["actions"][one]["type"].asString() == "decline")
			    && result["actions"][one]["status"].asString() == "completed")
				chargeback = true;
			 if (result["disputes"].size() > 0
				&& result["disputes"][zero]["status"].asString() == "pending")
				dispute = true;

			if(charge && !noitem && !dispute)
			{
				CLogicFBPay logicPay;
				if(serverid == 0)
				{
					int ret = logicPay.deliver_no_serverid(openid, payment_id, product, quantity);
					if (ret != 0) {
						error_log("[fb pay failed][payment_id=%s&openid=%s&product=%s&quantity=%u]",
								payment_id.c_str(), openid.c_str(), product.c_str(), quantity);
						return ret;
					}
				}
				else
				{
					int ret = logicPay.deliver_serverid(openid, serverid, payment_id, product, quantity);
					if (ret != 0) {
						error_log("[fb pay failed][payment_id=%s&product=%s&quantity=%u&serverid=%s&openid=%s]",
								payment_id.c_str(), product.c_str(), quantity, result["request_id"].asString().c_str(), openid.c_str());
						return ret;
					}
			   }

				error_log("[fb deliver after][payment_id=%s&openid=%s&product=%s&quantity=%u]",
						payment_id.c_str(), openid.c_str(), product.c_str(), quantity);
				CGI_SEND_LOG("openid=%s&product_id=%s&quantity=%u", openid.c_str(),product.c_str(),quantity);
			}
			else
			{
				if(chargeback && !noitem)
				{
					//charegeback
					CLogicFBPay logicPay;
					logicPay.chargeback(openid, serverid, payment_id, quantity);
				}
				if(dispute)
				{
					if(chargeback || noitem || !charged)
					{
						//deny
						string url = "https://graph.facebook.com/" + payment_id + "/dispute?access_token=" + app_access_token;
						string params = "reason=DENIED_REFUND";
						string response;

						if(!Network::HttpPostRequest(response, url, params))
						{
							error_log("[http request fail][reason=HttpPostRequest,openid=%s,errmsg=%s]",
									openid.c_str(), response.c_str());
							return -1;
						}
					}
					else
					{
						//recharge and solve
						CLogicFBPay logicPay;
						if(serverid == 0)
						{
							logicPay.deliver_no_serverid(openid, payment_id, product, quantity);
						}
						else
						{
							logicPay.deliver_serverid(openid, serverid, payment_id, product, quantity);
						}

						string url = "https://graph.facebook.com/" + payment_id + "/dispute?access_token=" + app_access_token;
						string params = "reason=GRANTED_REPLACEMENT_ITEM";
						string response;

						if(!Network::HttpPostRequest(response, url, params))
						{
							error_log("[http request fail][reason=HttpPostRequest,openid=%s,errmsg=%s]",
									openid.c_str(), response.c_str());
							return -1;
						}
					}

					COINS_LOG("[fb pay][disputes][user_comment=%s&time_created=%s]"
						"[payment_id=%s&openid=%s&product=%s&quantity=%u]",
						result["disputes"][zero]["user_comment"].asString().c_str(),
						result["disputes"][zero]["time_created"].asString().c_str(),
						payment_id.c_str(), openid.c_str(), product.c_str(), quantity);
				}
			}
		}
		return R_SUCCESS;
	}
};

CGI_MAIN(CCgiFBPay)
