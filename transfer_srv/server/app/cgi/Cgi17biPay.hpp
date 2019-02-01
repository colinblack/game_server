/*
 * Cgi17biPay.hpp
 *
 *  Created on: 2012-4-13
 *      Author: dada
 */

#include "LogicInc.h"

#define URL_17BI_PAY "http://17bi.net/yqbapi/exchangerqb/eid/%s/randval/%s/style/1"

class CCgi17biPay : public CCgiBase
{
public:

	CCgi17biPay() : CCgiBase("17bi")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_GET_UID);
		SetFeature(CF_CHECK_SESSION);
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_CHECK_HASH);
		SetFeature(CF_APPEND_HASH);
		SetFeature(CF_PARSE_DATA);
		SetFeature(CF_CRYPT_DATA);
		SetFeature(CF_DECRYPT_DATA);
	}

	CGI_DIRECT_PROCESS(Pay)

	int Pay()
	{
//		$eid = $_GET['eid'];
//		$num = $_GET['number'];
//		$userkey = $_GET['userkey'];
//		$keyval = $_GET['keyval'];
//		if(empty($eid) || empty($num) || empty($keyval) || empty($userkey)){
//			echo "-1";	//参数为空
//			exit();
//		}
//		//组合密钥：
//		$strval = $eid."#".$num."#17bi".$keyval;
//		$randval = md5($strval);
//		$url = "http://17bi.net/yqbapi/exchangerqb/eid/".$eid."/randval/".$randval."/style/1";
//		$result = file_get_contents($url);
//
//		if($result > 0){
//			/* 更新$userkey的游戏币数据（+$num） */
//		}
//
//		echo $result;

		//check
		string eid;
		unsigned count;
		string key;
		if(!Json::GetString(m_data, "eid", eid) ||
			!Json::GetUInt(m_data, "count", count) ||
			!Json::GetString(m_data, "key", key))
		{
			PARAM_ERROR_RETURN();
		}
		if(eid.empty() || count == 0 || key.empty())
		{
			PARAM_ERROR_RETURN();
		}
		string baseString;
		String::Format(baseString, "%s#%u#17bi%s", eid.c_str(), count, key.c_str());
		string checkKey = Crypt::Md5Encode(baseString);
		string url;
		String::Format(url, URL_17BI_PAY, eid.c_str(), checkKey.c_str());
		string response;
		if(!Network::HttpGetRequest(response, url))
		{
			error_log("[17bi_http_request_fail][url=%s,error=%s,eid=%s,count=%u]",
					url.c_str(), response.c_str(), eid.c_str(), count);
			ERROR_RETURN(R_ERR_PLATFORM);
		}
		int result;
		if(!Convert::StringToInt(result, response))
		{
			error_log("[17bi_pay_error][url=%s,response=%s,eid=%s,count=%u,key=%s,check=%s]",
					url.c_str(), response.c_str(), eid.c_str(), count, key.c_str(), checkKey.c_str());
			ERROR_RETURN(R_ERR_PLATFORM);
		}
		if(result <= 0)
		{
			error_log("[17bi_pay_error][url=%s,response=%s,eid=%s,count=%u,key=%s,check=%s]",
					url.c_str(), response.c_str(), eid.c_str(), count, key.c_str(), checkKey.c_str());
			ERROR_RETURN(R_ERR_AUTH);
		}
		if((unsigned)result != count)
		{
			error_log("[17bi_count_mismatch][url=%s,response=%s,eid=%s,count=%u,key=%s,check=%s]",
					url.c_str(), response.c_str(), eid.c_str(), count, key.c_str(), checkKey.c_str());
			count = result;
		}

		//add cash
		int ret;
		CLogicPay logicPay;
		DataPayHistory payHistory;
		payHistory.uid = m_uid;
		payHistory.type = 0;
		payHistory.channel = PCT_17BI;
		payHistory.channel_pay_id = eid;
		payHistory.credit = count;
		payHistory.count = count;
		payHistory.status = PST_OK;
		ret = logicPay.AddPayHistory(payHistory);
		if(ret != 0)
		{
			error_log("[AddPayHistory fail][channel=17bi,ret=%d,platform=%d,uid=%s,payid=%s,cash=%u]",
					ret, OpenPlatform::GetType(), m_uid, eid.c_str(), count);
			return ret;
		}
		ret = logicPay.BuyCash(m_uid, count, count);
		if(ret != 0)
		{
			error_log("[BuyCash fail][channel=17bi,ret=%d,platform=%d,uid=%s,payid=%s,cash=%u]",
					ret, OpenPlatform::GetType(), m_uid, eid.c_str(), count);
			return ret;
		}
		unsigned cash;
		ret = logicPay.GetCash(m_uid, cash);
		if(ret == 0)
		{
			m_jsonResult["credits"] = cash;
		}
		CGI_SEND_LOG("platform=%d&uid=%u&eid=%s&count=%u&payid=%llu",
				OpenPlatform::GetType(), m_uid, eid.c_str(), count, payHistory.pay_id);
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgi17biPay)
