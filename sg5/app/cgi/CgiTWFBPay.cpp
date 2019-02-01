#include "LogicInc.h"
#include "LogicFBPay.h"

class CCgiTWFBPay : public CCgiBase
{
public:
	CCgiTWFBPay() : CCgiBase("twfbpay")
	{
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_PARSE_DATA);
		SetFeature(CF_GET_REMOTE_IP);
	}

	CGI_DIRECT_PROCESS(TWFBPay)

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

	int TWFBPay()
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
		    //error_log("[twfbpay start][m_strData=%s]", m_strData.c_str());

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
				error_log("[http request fail][app_access_token=%s]",app_access_token.c_str());
				ERROR_RETURN_MSG(R_ERR_NO_DATA, "http_request_fail");
			}

			Json::Value result;
			Json::Reader query_reader;
			if (response.empty() || !query_reader.parse(response, result)
					|| !result.isMember("id") || result["id"].asString() != payment_id
					|| !result.isMember("request_id"))
			{
				error_log("[response error][response=%s]",response.c_str());
				ERROR_RETURN_MSG(R_ERR_NO_DATA, "response_error");
			}

			string request_id = result["request_id"].asString();
			vector<string> rlt;
			String::Split(request_id, '.', rlt);
			unsigned serverid = atoi(rlt[0].c_str());
			if (serverid == 0)
			{
				error_log("[response error][response=%s]",response.c_str());
				ERROR_RETURN_MSG(R_ERR_NO_DATA, "response_error");
			}

			string openid = result["user"]["id"].asString();
			string openname = result["user"]["name"].asString();

			if (result["actions"].size() != 1
			        || result["actions"][zero]["type"].asString() != "charge"
			        || result["actions"][zero]["status"].asString() != "completed")
            {
				error_log("[invalid payment id][invalid actions]%s",response.c_str());
				PARAM_ERROR_RETURN_MSG("invalid_payment_actions");
            }

            string product = OpenPlatform::GetPlatform()->GetConfig(CONFIG_FB_PAYMENT_PRODUCT);
            unsigned quantity = result["items"][zero]["quantity"].asUInt();
			if (result["items"].size() != 1
			        || result["items"][zero]["type"].asString() != "IN_APP_PURCHASE"
			        || result["items"][zero]["product"].asString() != product)
            {
				error_log("[invalid payment id][invalid items]%s",response.c_str());
				PARAM_ERROR_RETURN_MSG("invalid_payment_items");
            }

            if (result["disputes"].size() > 0)
            {
            	string url = "https://graph.facebook.com/" + payment_id + "/dispute?access_token=" + app_access_token;
				string params = "reason=DENIED_REFUND";
				string response;

				if(!Network::HttpPostRequest(response, url, params))
				{
					error_log("[http request fail][reason=HttpPostRequest,openid=%s,errmsg=%s]",
							openid.c_str(), response.c_str());
					return -1;
				}

				error_log("[twfb pay][disputes][user_comment=%s&time_created=%s]"
				        "[payment_id=%s&openid=%s&product=%s&quantity=%u]",
				        result["disputes"][zero]["user_comment"].asString().c_str(),
				        result["disputes"][zero]["time_created"].asString().c_str(),
				        payment_id.c_str(), openid.c_str(), product.c_str(), quantity);
                return R_SUCCESS;
            }

            string tgid;
            //XXX 根据facebook openid获取tgid
            //http://www.goodogames.com.tw/Channge/UIDToTGID/{UID}

            {
                string url;
                string response;
#define URL_TW_GET_TGID "https://www.goodogames.com/Change/UIDToTGID/%s"
                String::Format(url, URL_TW_GET_TGID, openid.c_str());
                if(!Network::HttpGetRequest(response, url))
                {
                    error_log("[query tgid http request fail][reason=HttpGetRequest,openid=%s,errmsg=%s]",
                            openid.c_str(), "get_tgid_failed");
                    PARAM_ERROR_RETURN_MSG("get_tgid_failed");
                }

                Json::Value jsonUserInfo;
                Json::Reader reader;
                if(!reader.parse(response, jsonUserInfo))
                {
                    error_log("[query tgid response parse fail][reason=JsonParse,openid=%s,errmsg=%s,response=%s]",
                            openid.c_str(), "json_parse_fail", response.c_str());
                    PARAM_ERROR_RETURN_MSG("json_parse_fail");
                }
                if(!jsonUserInfo.isMember("tgid"))
                {
                    error_log("[query tgid data error][reason=QueryFail,openid=%s,errmsg=%s,response=%s]",
                            openid.c_str(), "query_fail", response.c_str());
                    PARAM_ERROR_RETURN_MSG("query_fail");
                }

                tgid = jsonUserInfo["tgid"].asString();
            }

            CLogicFBPay logicPay;
            int ret = logicPay.deliver_serverid(tgid, serverid, payment_id, product, quantity);
            if (ret != 0) {
				error_log("[twfb pay failed][payment_id=%s&tgid=%s&product=%s&quantity=%u&serverid=%u&openid=%s]",
				        payment_id.c_str(), tgid.c_str(), product.c_str(), quantity, serverid, openid.c_str());
                return ret;
            }

            error_log("[twfb deliver after][payment_id=%s&tgid=%s&product=%s&quantity=%u&serverid=%u&openid=%s]",
                    payment_id.c_str(), tgid.c_str(), product.c_str(), quantity, serverid, openid.c_str());

            CGI_SEND_LOG("openid=%s&product_id=%s&quantity=%u&serverid=%u&tgid=%s", openid.c_str(),product.c_str(),quantity,serverid, tgid.c_str());
            return R_SUCCESS;
		}

		return R_SUCCESS;
	}
};

CGI_MAIN(CCgiTWFBPay)
