#include "LogicInc.h"
#include "LogicQQPay.h"

class CCgiQQDeliver : public CCgiBase
{
public:
	CCgiQQDeliver() : CCgiBase("qqdeliver")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(deliver)

	int deliver()
	{
		const string contractid = CCGIIn::GetCGIStr("contractid");
		if (!contractid.empty())
		{
			CgiUtil::PrintText("{\"ret\":0,\"msg\":\"OK\"}");
			return 0;
		}
		const string discountid = CCGIIn::GetCGIStr("discountid");
		//蓝钻包月活动回调
		if(discountid.find("UM140305160606500") != string::npos)
		{
			const string openid = CCGIIn::GetCGIStr("openid");
			if(openid.empty())
			{
				CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（openid）\"}");
				ERROR_RETURN_MSG(4, "请求参数错误：（openid）");
			}

			const string appid = CCGIIn::GetCGIStr("appid");
			if (appid.empty())
			{
				CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（appid）\"}");
				ERROR_RETURN_MSG(4, "请求参数错误：（appid）");
			}

			const string ts = CCGIIn::GetCGIStr("ts");
			if (ts.empty())
			{
				CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（ts）\"}");
				ERROR_RETURN_MSG(4, "请求参数错误：（ts）");
			}

			const string payitem = CCGIIn::GetCGIStr("payitem");
			if (payitem.empty())
			{
				CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（payitem）\"}");
				ERROR_RETURN_MSG(4, "请求参数错误：（payitem）");
			}

			const string token = CCGIIn::GetCGIStr("token");
			if (token.empty())
			{
				CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（token）\"}");
				ERROR_RETURN_MSG(4, "请求参数错误：（token）");
			}

			const string billno = CCGIIn::GetCGIStr("billno");
			if (billno.empty())
			{
				CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（billno）\"}");
				ERROR_RETURN_MSG(4, "请求参数错误：（billno）");
			}

			const string version = CCGIIn::GetCGIStr("version");
			if (version.empty())
			{
				CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（version）\"}");
				ERROR_RETURN_MSG(4, "请求参数错误：（version）");
			}

			const string zoneid = CCGIIn::GetCGIStr("zoneid");
			if (zoneid.empty())
			{
				CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（zoneid）\"}");
				ERROR_RETURN_MSG(4, "请求参数错误：（zoneid）");
			}

			const string providetype = CCGIIn::GetCGIStr("providetype");
			if (providetype.empty())
			{
				CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（providetype）\"}");
				ERROR_RETURN_MSG(4, "请求参数错误：（providetype）");
			}

			const string sig = CCGIIn::GetCGIStr("sig");
			if (sig.empty())
			{
				CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（sig）\"}");
				ERROR_RETURN_MSG(4, "请求参数错误：（sig）");
			}
			else
			{
				string appkey = OpenPlatform::GetPlatform()->GetAppKey();
				string qstr = getenv("QUERY_STRING");
				map<string, string> params;
				vector<string> reqs;
				CBasic::StringSplit(qstr, "&", reqs);
				for (unsigned i = 0; i < reqs.size(); i++)
				{
					string key;
					string value;
					size_t found;
					found = reqs[i].find('=');
					if (found != string::npos)
					{
						key = reqs[i].substr(0, found);
						value = reqs[i].substr(found + 1);
					}
					else
					{
						key = reqs[i];
						value = "";
					}
					params[key] = value;
				}
				string dsig;
				bool bfirst = true;
				string qsig;
				map<string, string>::const_iterator it = params.begin();
				for (; it != params.end(); it++)
				{
					if (it->first == "sig")
					{
						dsig = CBasic::unescape(it->second);
					}
					else
					{
						if (!bfirst) qsig += "&";
						qsig += it->first + "=" + Crypt::EncodeForTXSig(it->second);
						bfirst = false;
					}
				}
				string osig = "GET&%2Fcgi%2Fqqdeliver&" + Crypt::UrlEncodeForTX(qsig);
				string sha1Key = appkey + "&";
				string bnsig = Crypt::HmacSha1(osig, sha1Key);
				string nsig;
				Crypt::Base64Encode(nsig, bnsig);
				//info_log("[qqdeliver sig][dsig=%s,nsig=%s,osig=%s,key=%s]",dsig.c_str(),nsig.c_str(),osig.c_str(),sha1Key.c_str());
				if (dsig != nsig)
				{
					error_log("[qqdeliver vipcharge sig error][dsig=%s,nsig=%s,osig=%s]",dsig.c_str(),nsig.c_str(),osig.c_str());
					CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（sig）\"}");
					ERROR_RETURN_MSG(4, "请求参数错误：（sig）");
				}
				CLogicQQPay logicPay;
				int ret = logicPay.vip_charge_deliver(appid, openid, payitem);
				if (ret != 0)
				{
					CgiUtil::PrintText("{\"ret\":"+CTrans::ITOS(::GetError())+",\"msg\":\""+::GetErrorMessage()+"\"}");
					return ret;
				}
				CgiUtil::PrintText("{\"ret\":0,\"msg\":\"OK\"}");

				CGI_SEND_LOG("action=vipcharge&openid=%s&payitem=%s", openid.c_str(),payitem.c_str());
				return R_SUCCESS;

			}

		}
		else if(discountid.find("UM140505105610317") != string::npos) //冲年费蓝钻送将
		{
			const string openid = CCGIIn::GetCGIStr("openid");
			if(openid.empty())
			{
				CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（openid）\"}");
				ERROR_RETURN_MSG(4, "请求参数错误：（openid）");
			}

			const string appid = CCGIIn::GetCGIStr("appid");
			if (appid.empty())
			{
				CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（appid）\"}");
				ERROR_RETURN_MSG(4, "请求参数错误：（appid）");
			}

			const string ts = CCGIIn::GetCGIStr("ts");
			if (ts.empty())
			{
				CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（ts）\"}");
				ERROR_RETURN_MSG(4, "请求参数错误：（ts）");
			}

			const string payitem = CCGIIn::GetCGIStr("payitem");
			if (payitem.empty())
			{
				CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（payitem）\"}");
				ERROR_RETURN_MSG(4, "请求参数错误：（payitem）");
			}

			const string token = CCGIIn::GetCGIStr("token");
			if (token.empty())
			{
				CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（token）\"}");
				ERROR_RETURN_MSG(4, "请求参数错误：（token）");
			}

			const string billno = CCGIIn::GetCGIStr("billno");
			if (billno.empty())
			{
				CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（billno）\"}");
				ERROR_RETURN_MSG(4, "请求参数错误：（billno）");
			}

			const string version = CCGIIn::GetCGIStr("version");
			if (version.empty())
			{
				CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（version）\"}");
				ERROR_RETURN_MSG(4, "请求参数错误：（version）");
			}

			const string zoneid = CCGIIn::GetCGIStr("zoneid");
			if (zoneid.empty())
			{
				CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（zoneid）\"}");
				ERROR_RETURN_MSG(4, "请求参数错误：（zoneid）");
			}

			const string providetype = CCGIIn::GetCGIStr("providetype");
			if (providetype.empty())
			{
				CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（providetype）\"}");
				ERROR_RETURN_MSG(4, "请求参数错误：（providetype）");
			}

			const string sig = CCGIIn::GetCGIStr("sig");
			if (sig.empty())
			{
				CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（sig）\"}");
				ERROR_RETURN_MSG(4, "请求参数错误：（sig）");
			}
			else
			{
				string appkey = OpenPlatform::GetPlatform()->GetAppKey();
				string qstr = getenv("QUERY_STRING");
				map<string, string> params;
				vector<string> reqs;
				CBasic::StringSplit(qstr, "&", reqs);
				for (unsigned i = 0; i < reqs.size(); i++)
				{
					string key;
					string value;
					size_t found;
					found = reqs[i].find('=');
					if (found != string::npos)
					{
						key = reqs[i].substr(0, found);
						value = reqs[i].substr(found + 1);
					}
					else
					{
						key = reqs[i];
						value = "";
					}
					params[key] = value;
				}
				string dsig;
				bool bfirst = true;
				string qsig;
				map<string, string>::const_iterator it = params.begin();
				for (; it != params.end(); it++)
				{
					if (it->first == "sig")
					{
						dsig = CBasic::unescape(it->second);
					}
					else
					{
						if (!bfirst) qsig += "&";
						qsig += it->first + "=" + Crypt::EncodeForTXSig(it->second);
						bfirst = false;
					}
				}
				string osig = "GET&%2Fcgi%2Fqqdeliver&" + Crypt::UrlEncodeForTX(qsig);
				string sha1Key = appkey + "&";
				string bnsig = Crypt::HmacSha1(osig, sha1Key);
				string nsig;
				Crypt::Base64Encode(nsig, bnsig);
				//info_log("[qqdeliver sig][dsig=%s,nsig=%s,osig=%s,key=%s]",dsig.c_str(),nsig.c_str(),osig.c_str(),sha1Key.c_str());
				if (dsig != nsig)
				{
					error_log("[qqdeliver blue year charge sig error][dsig=%s,nsig=%s,osig=%s]",dsig.c_str(),nsig.c_str(),osig.c_str());
					CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（sig）\"}");
					ERROR_RETURN_MSG(4, "请求参数错误：（sig）");
				}
				CLogicQQPay logicPay;
				int ret = logicPay.blue_year_charge_deliver(appid, openid, payitem);
				if (ret != 0)
				{
					CgiUtil::PrintText("{\"ret\":"+CTrans::ITOS(::GetError())+",\"msg\":\""+::GetErrorMessage()+"\"}");
					return ret;
				}
				CgiUtil::PrintText("{\"ret\":0,\"msg\":\"OK\"}");

				CGI_SEND_LOG("action=blue_year_charge&openid=%s&payitem=%s", openid.c_str(),payitem.c_str());
				return R_SUCCESS;

			}
		}
		else if(!discountid.empty())
		{
			CgiUtil::PrintText("{\"ret\":0,\"msg\":\"OK\"}");
			return R_SUCCESS;
		}

		//error_log("qqdeliever failed");
		const string openid = CCGIIn::GetCGIStr("openid");
		if (openid.empty())
		{
			CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（openid）\"}");
			ERROR_RETURN_MSG(4, "请求参数错误：（openid）");
		}
		//error_log("qqdeliever failed");
		const string appid = CCGIIn::GetCGIStr("appid");
		if (appid.empty())
		{
			CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（appid）\"}");
			ERROR_RETURN_MSG(4, "请求参数错误：（appid）");
		}
		//error_log("qqdeliever failed");
		const string ts = CCGIIn::GetCGIStr("ts");
		if (ts.empty())
		{
			CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（ts）\"}");
			ERROR_RETURN_MSG(4, "请求参数错误：（ts）");
		}
		const string payitem = CCGIIn::GetCGIStr("payitem");
		if (payitem.empty())
		{
			CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（payitem）\"}");
			ERROR_RETURN_MSG(4, "请求参数错误：（payitem）");
		}
		//error_log("qqdeliever failed");
		const string amt = CCGIIn::GetCGIStr("amt");
		if (amt.empty())
		{
			CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（amt）\"}");
			ERROR_RETURN_MSG(4, "请求参数错误：（amt）");
		}
		//error_log("qqdeliever failed");
		const string token = CCGIIn::GetCGIStr("token");
		if (token.empty())
		{
			CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（token）\"}");
			ERROR_RETURN_MSG(4, "请求参数错误：（token）");
		}
		const string billno = CCGIIn::GetCGIStr("billno");
		if (billno.empty())
		{
			CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（billno）\"}");
			ERROR_RETURN_MSG(4, "请求参数错误：（billno）");
		}
		const string sig = CCGIIn::GetCGIStr("sig");
		if (sig.empty())
		{
			CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（sig）\"}");
			ERROR_RETURN_MSG(4, "请求参数错误：（sig）");
		}
		else
		{
			string appkey = OpenPlatform::GetPlatform()->GetAppKey();
			string qstr = getenv("QUERY_STRING");
			map<string, string> params;
			vector<string> reqs;
			CBasic::StringSplit(qstr, "&", reqs);
			for (unsigned i = 0; i < reqs.size(); i++)
			{
				string key;
				string value;
				size_t found;
				found = reqs[i].find('=');
				if (found != string::npos)
				{
					key = reqs[i].substr(0, found);
					value = reqs[i].substr(found + 1);
				}
				else
				{
					key = reqs[i];
					value = "";
				}
				params[key] = value;
			}
			string dsig;
			bool bfirst = true;
			string qsig;
			map<string, string>::const_iterator it = params.begin();
			for (; it != params.end(); it++)
			{
				if (it->first == "sig")
				{
					dsig = CBasic::unescape(it->second);
				}
				else
				{
					if (!bfirst) qsig += "&";
					qsig += it->first + "=" + Crypt::EncodeForTXSig(it->second);
					bfirst = false;
				}
			}
			string osig = "GET&%2Fcgi%2Fqqdeliver&" + Crypt::UrlEncodeForTX(qsig);
			string sha1Key = appkey + "&";
			string bnsig = Crypt::HmacSha1(osig, sha1Key);
			string nsig;
			Crypt::Base64Encode(nsig, bnsig);
			//info_log("[qqdeliver sig][dsig=%s,nsig=%s,osig=%s,key=%s]",dsig.c_str(),nsig.c_str(),osig.c_str(),sha1Key.c_str());
			if (dsig != nsig)
			{
				error_log("[qqdeliver sig error][dsig=%s,nsig=%s,osig=%s]",dsig.c_str(),nsig.c_str(),osig.c_str());
				CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（sig）\"}");
				ERROR_RETURN_MSG(4, "请求参数错误：（sig）");
			}

			/*  v2版本的验证签名，已弃用
			string osig;
			osig.append("amt").append(amt);
			osig.append("appid").append(appid);
			osig.append("billno").append(billno);
			osig.append("openid").append(openid);
			osig.append("payitem").append(payitem);
			osig.append("token").append(token);
			osig.append("ts").append(ts);
			osig.append(appkey);
			string check_sig = Crypt::Md5Encode(osig);
			if (!String::EqualNoCase(sig, check_sig))
			{
				CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（sig）\"}");
				ERROR_RETURN_MSG(4, "请求参数错误：（sig）");
			}
			*/
		}
		//error_log("qqdeliever failed");
		CLogicQQPay logicPay;
		int ret = logicPay.deliver(appid, openid, payitem, CTrans::STOI(amt), billno);
		if (ret != 0)
		{
			CgiUtil::PrintText("{\"ret\":"+CTrans::ITOS(::GetError())+",\"msg\":\""+::GetErrorMessage()+"\"}");
			return ret;
		}
		//CgiUtil::PrintText("{\"ret\":0,\"msg\":\"OK\"}");防止回调过久移动到各平台虚函数

		CGI_SEND_LOG("openid=%s&billno=%s&payitem=%s&amt=%s", openid.c_str(),billno.c_str(),payitem.c_str(),amt.c_str());
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiQQDeliver)
