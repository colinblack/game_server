/*
 * CgiMobagePay.h
 *
 *  Created on: 2011-12-6
 *      Author: dada
 */


#include "LogicInc.h"
#include "OAuthUtil.h"

class CCgiMobagePay : public CCgiBase
{

public:

	CCgiMobagePay() : CCgiBase("mobage/pay")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(MobagePay)

	int MobagePay()
	{
		//check param
		info_log("[context][header=%s,querystring=%s]", getenv("HTTP_AUTHORIZATION"), getenv("QUERY_STRING"));
		if(OpenPlatform::GetType() != PT_MOBAGE)
		{
			error_log("[mismatch_platform][platform=%d,host=%s]", OpenPlatform::GetType(), getenv("SERVER_NAME"));
			PrintResponse("{\"response_code\":\"param_error\"}");
			return R_ERR_PARAM;
		}
		string sMethod;
		CgiUtil::GetRequestMethod(sMethod);
		OAuth::HttpRequestMethod requestMethod;
		if(sMethod == "POST")
		{
			requestMethod = OAuth::POST;
		}
		else if(sMethod == "GET")
		{
			requestMethod = OAuth::GET;
		}
		else
		{
			error_log("[unknow_request_method][method=%s]", sMethod.c_str());
			PrintResponse("{\"response_code\":\"param_error\"}");
			return R_ERR_PARAM;
		}
		string url = "http://";
		const char *pcHost = getenv("HTTP_HOST");
		if(pcHost != NULL)
		{
			url += pcHost;
		}
		const char *pcRequestUri = getenv("REQUEST_URI");
		if(pcRequestUri != NULL)
		{
			url += pcRequestUri;
		}
		size_t midPos = url.find('?');
		if(midPos != string::npos)
		{
			url.erase(midPos);
		}
		map<string, string> oauthHeader;
		if(!OAuth::GetAuthHeader(oauthHeader))
		{
			const char *pcAuthHeader = getenv("HTTP_AUTHORIZATION");
			error_log("[get_auth_header_fail][header=%s]", pcAuthHeader == NULL ? "<null>" : pcAuthHeader);
			PrintResponse("{\"response_code\":\"param_error\"}");
			return R_ERR_PARAM;
		}
		oauthHeader.erase("realm");
		string signMethod = oauthHeader["oauth_signature_method"];
		if(signMethod != "HMAC-SHA1")
		{
			error_log("[unknow_sign_method][header=%s]", getenv("HTTP_AUTHORIZATION"));
			PrintResponse("{\"response_code\":\"param_error\"}");
			return R_ERR_PARAM;
		}
		string signature = Crypt::UrlDecode(oauthHeader["oauth_signature"]);
		if(signature.empty())
		{
			error_log("[signature_empty][header=%s]", getenv("HTTP_AUTHORIZATION"));
			PrintResponse("{\"response_code\":\"param_error\"}");
			return R_ERR_PARAM;
		}
		oauthHeader.erase("oauth_signature");
		map<string, string> params;
		CgiUtil::GetRequestParams(params);
		for(map<string, string>::iterator itr = oauthHeader.begin(); itr != oauthHeader.end(); itr++)
		{
			params.insert(*itr);
		}
		OAuth::OAuthParam oauthParam;
		oauthParam.SignMethod = OAuth::HMAC_SHA1;
		oauthParam.TokenSecret = "";
		oauthParam.AppSecret = OpenPlatform::GetPlatform()->GetAppKey();
		if(!OAuth::CheckSignature(signature, requestMethod, url, params, oauthParam))
		{
			error_log("[check_signature_error][header=%s,querystring=%s]",
					getenv("HTTP_AUTHORIZATION"), getenv("QUERY_STRING"));
			PrintResponse("{\"response_code\":\"param_error\"}");
			return R_ERR_PARAM;
		}

		//process
		int ret;
		string response;
		string openid = Crypt::UrlDecode(params["opensocial_viewer_id"]);
		if(openid.empty())
		{
			error_log("[no_user_id][openid=<null>]");
			PrintResponse("{\"response_code\":\"param_error\"}");
			return R_ERR_PARAM;
		}
		unsigned uid;
		ret = LogicUserBasic::GetUid(uid, OpenPlatform::GetType(), openid);
		if(ret != 0)
		{
			error_log("[unknow_user][ret=%d,openid=%s]", ret, openid.c_str());
			PrintResponse("{\"response_code\":\"no_user\"}");
			return ret;
		}
		CLogicPay logicPay;
		DataPayHistory payHistory;
		if(requestMethod == OAuth::POST)
		{
			//Confirmation of settlement information
			string postData;
			CgiUtil::GetPostData(postData);
			string bodySign;
			Crypt::Base64Encode(bodySign, Crypt::Sha1Raw(postData));
			string bodySignCheck = Crypt::UrlDecode(oauthHeader["oauth_body_hash"]);
			if(bodySign != bodySignCheck)
			{
				error_log("[check_body_signature_error][body=%s,sign=%s,realsign=%s]",
						postData.c_str(), bodySignCheck.c_str(), bodySign.c_str());
				PrintResponse("{\"response_code\":\"param_error\"}");
				return R_ERR_PARAM;
			}

			Json::Value settleData;
			if(!Json::FromString(settleData, postData))
			{
				error_log("[parse_data_fail][data=%s]", postData.c_str());
				PrintResponse("{\"response_code\":\"param_error\"}");
				return R_ERR_PARAM;
			}
			payHistory.uid = uid;
			payHistory.status = PST_PENDING;
			payHistory.channel = PCT_MOBAGE;
			if(!Json::GetString(settleData, "PAYMENT_ID", payHistory.channel_pay_id))
			{
				error_log("[get_pay_id_fail][data=%s]", postData.c_str());
				PrintResponse("{\"response_code\":\"param_error\"}");
				return R_ERR_PARAM;
			}
			unsigned amount;
			if(!Json::GetUInt(settleData, "AMOUNT", amount))
			{
				error_log("[get_amount_fail][data=%s]", postData.c_str());
				PrintResponse("{\"response_code\":\"param_error\"}");
				return R_ERR_PARAM;
			}
			payHistory.credit = amount;
			if(!Json::IsArray(settleData, "ITEMS"))
			{
				error_log("[get_items_fail][data=%s]", postData.c_str());
				PrintResponse("{\"response_code\":\"param_error\"}");
				return R_ERR_PARAM;
			}
			if(settleData["ITEMS"].size() != 1 || !settleData["ITEMS"][0u].isObject())
			{
				error_log("[items_data_error][data=%s]", postData.c_str());
				PrintResponse("{\"response_code\":\"param_error\"}");
				return R_ERR_PARAM;
			}
			Json::Value &item = settleData["ITEMS"][0u];
			int price = 0;
			if(!Json::GetInt(item, "SKU_ID", payHistory.type) ||
				!Json::GetInt(item, "PRICE", price) ||
				!Json::GetInt(item, "COUNT", payHistory.count))
			{
				error_log("[item_data_error][data=%s]", postData.c_str());
				PrintResponse("{\"response_code\":\"param_error\"}");
				return R_ERR_PARAM;
			}
			if(payHistory.count < 0 || payHistory.count > 100 || price < 0 || price > 10000000)
			{
				error_log("[count_out_range][cpayid=%s,count=%d,price=%d]",
						payHistory.channel_pay_id.c_str(), payHistory.count, price);
				PrintResponse("{\"response_code\":\"param_error\"}");
				return R_ERR_PARAM;
			}
			int itemPrice;
			int itemCash;
			if(!GetItem(payHistory.type, itemCash, itemPrice))
			{
				error_log("[no_pay_item][cpayid=%s,type=%d]",
						payHistory.channel_pay_id.c_str(), payHistory.type);
				PrintResponse("{\"response_code\":\"no_pay_item\"}");
				return R_ERR_PARAM;
			}
			if(itemPrice != price)
			{
				error_log("[price_error][cpayid=%s,type=%d,price=%d,realprice=%d]",
						payHistory.channel_pay_id.c_str(), payHistory.type, price, itemPrice);
				PrintResponse("{\"response_code\":\"price_error\"}");
				return R_ERR_PARAM;
			}
			if(payHistory.count * price != payHistory.credit)
			{
				error_log("[amount_error][cpayid=%s,count=%d,price=%d,amount=%d]",
						payHistory.channel_pay_id.c_str(), payHistory.count, price, payHistory.credit);
				PrintResponse("{\"response_code\":\"amount_error\"}");
				return R_ERR_PARAM;
			}
			ret = logicPay.AddPayHistory(payHistory);
			if(ret != 0)
			{
				error_log("[add_pay_fail][ret=%d,uid=%u,cpayid=%s,amount=%d]", ret, uid, payHistory.channel_pay_id.c_str(), payHistory.credit);
				PrintResponse("{\"response_code\":\"no_user\"}");
				return ret;
			}
			String::Format(response, "{\"order_id\":\"%llu\",\"response_code\":\"OK\"}", payHistory.pay_id);
			PrintResponse(response);
			CGI_SEND_LOG("action=order&uid=%u&type=%d&price=%d&count=%d&amount=%d&chpayid=%s&payid=%llu",
					uid, payHistory.type, price, payHistory.count, payHistory.credit, payHistory.channel_pay_id.c_str(), payHistory.pay_id);
		}
		else
		{
			//Payment settlement
			string sPayId = Crypt::UrlDecode(params["order_id"]);
			uint64_t payId;
			if(!Convert::StringToUInt64(payId, sPayId))
			{
				error_log("[payid_error][payid=%s]", sPayId.c_str());
				PrintResponse("{\"response_code\":\"param_error\"}");
				return R_ERR_PARAM;
			}
			ret = logicPay.GetPayHistory(uid, payId, payHistory);
			if(ret != 0)
			{
				error_log("[get_pay_fail][ret=%d,uid=%u,payid=%llu]", ret, uid, payId);
				PrintResponse("{\"response_code\":\"order_not_found\"}");
				return R_ERR_PARAM;
			}
			int itemPrice;
			int itemCash;
			if(!GetItem(payHistory.type, itemCash, itemPrice))
			{
				error_log("[no_pay_item][payid=%llu,type=%d]", payHistory.pay_id, payHistory.type);
				PrintResponse("{\"response_code\":\"no_pay_item\"}");
				return R_ERR_PARAM;
			}
			int cashAdd = itemCash * payHistory.count;
			ret = logicPay.SetPayHistoryStatus(uid, payId, PST_OK);
			if(ret != 0)
			{
				error_log("[set_pay_fail][ret=%d,uid=%u,payid=%llu]", ret, uid, payId);
				PrintResponse("{\"response_code\":\"set_pay_fail\"}");
				return R_ERR_PARAM;
			}
			ret = logicPay.BuyCash(uid, cashAdd, payHistory.credit);
			if(ret != 0)
			{
				error_log("[add_cash_fail][ret=%d,uid=%u,cashadd=%d,payid=%llu]", ret, uid, cashAdd, payId);
				PrintResponse("{\"response_code\":\"add_cash_fail\"}");
				return R_ERR_PARAM;
			}
			String::Format(response, "{\"order_id\":\"%llu\",\"response_code\":\"OK\",\"amount\":%d}",
					payHistory.pay_id, payHistory.credit);
			PrintResponse(response);
			CGI_SEND_LOG("action=confirm&uid=%u&type=%d&credit=%d&payid=%llu&cashadd=%d",
					uid, payHistory.type, payHistory.credit, payHistory.pay_id, cashAdd);
		}

		return 0;
	}

protected:

	void PrintResponse(const string &text)
	{
		string bodySign;
		Crypt::Base64EncodeTrim(bodySign, Crypt::Sha1Raw(text));
		static char s_nonceSet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
		string nonce;
		nonce.resize(32);
		for(int i = 0; i < 32; i++)
		{
			nonce[i] = s_nonceSet[Math::GetRandomInt(62)];
		}
		string ts = Convert::UIntToString(Time::GetGlobalTime());
		string baseString;
		String::Format(baseString, "body_hash=%s&consumer_key=%s&nonce=%s&timestamp=%s",
				Crypt::UrlEncode(bodySign).c_str(), OpenPlatform::GetPlatform()->GetAppId().c_str(), nonce.c_str(), ts.c_str());
		string key = OpenPlatform::GetPlatform()->GetAppKey();
		string signature;
		Crypt::Base64EncodeTrim(signature, Crypt::HmacSha1(baseString, key));
		baseString += "&signature=" + Crypt::UrlEncode(signature);
		CgiUtil::PrintFormat(
			"Content-type: text/html; charset=UTF-8\r\n"
			"X-MBGA-PAYMENT-SIGNATURE: %s\r\n"
			"Pragma: no-cache\r\n\r\n"
			"%s",
			baseString.c_str(),
			text.c_str()
			);
	}

	bool GetItem(int type, int &cash, int &price)
	{
		static map<int, pair<int, int> > s_payItems;
		static bool s_initItems = false;
		if(!s_initItems)
		{
			string sItems = OpenPlatform::GetPlatform()->GetConfig("pay_items");
			vector<string> vItems;
			CBasic::StringSplitTrim(sItems, ";", vItems);
			for(vector<string>::iterator itrItem = vItems.begin(); itrItem != vItems.end(); itrItem++)
			{
				vector<string> vItem;
				CBasic::StringSplitTrim(*itrItem, ",", vItem);
				if(vItem.size() == 3)
				{
					int itemType;
					int itemCash;
					int itemPrice;
					if(Convert::StringToInt(itemType, vItem[0]) &&
						Convert::StringToInt(itemCash, vItem[1]) &&
						Convert::StringToInt(itemPrice, vItem[2]))
					{
						if(itemType >= 0 && itemCash >= 0 && itemPrice >= 0)
						{
							s_payItems[itemType] = make_pair(itemCash, itemPrice);
						}
					}
				}
			}
			s_initItems =  true;
		}
		map<int, pair<int, int> >::iterator itrFind = s_payItems.find(type);
		if(itrFind == s_payItems.end())
		{
			return false;
		}
		cash = itrFind->second.first;
		price = itrFind->second.second;
		return true;
	}

};

CGI_MAIN(CCgiMobagePay)
