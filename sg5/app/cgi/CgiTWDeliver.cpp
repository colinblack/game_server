#include "LogicInc.h"
#include "LogicTWPay.h"

class CCgiTWDeliver : public CCgiBase
{
public:
	CCgiTWDeliver() : CCgiBase("twdeliver")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(deliver)

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

	int deliver()
	{
		const string openid = CCGIIn::GetCGIStr("openid");
		if (openid.empty())
		{
			CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（openid）\"}");
			ERROR_RETURN_MSG(4, "请求参数错误：（openid）");
		}
		const string ts = CCGIIn::GetCGIStr("ts");
		if (ts.empty())
		{
			CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（ts）\"}");
			ERROR_RETURN_MSG(4, "请求参数错误：（ts）");
		}
		const string serverid = CCGIIn::GetCGIStr("serverid");
		if (serverid.empty())
		{
			CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（serverid）\"}");
			ERROR_RETURN_MSG(4, "请求参数错误：（serverid）");
		}
		const string num = CCGIIn::GetCGIStr("num");
		if (num.empty())
		{
			CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（num）\"}");
			ERROR_RETURN_MSG(4, "请求参数错误：（num）");
		}
		const string token = CCGIIn::GetCGIStr("token"); //token表示订单号
		if (token.empty())
		{
			CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（token）\"}");
			ERROR_RETURN_MSG(4, "请求参数错误：（token）");
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

			string osig = "GET&%2Fcgi%2Fbsgdeliver&" + Crypt::UrlEncodeForTX(qsig);
			string sha1Key = appkey + "&";
			string bnsig = Crypt::HmacSha1(osig, sha1Key);

            string expected_sig;
            StrToHex(bnsig, expected_sig);

			string nsig;
			//Crypt::Base64Encode(nsig, bnsig);
			Crypt::Base64Encode(nsig, expected_sig);

			//info_log("[twdeliver sig][dsig=%s,nsig=%s,osig=%s,key=%s]",dsig.c_str(),nsig.c_str(),osig.c_str(),sha1Key.c_str());
			if (dsig != nsig)
			{
				error_log("[twdeliver sig error][dsig=%s,nsig=%s,osig=%s]",dsig.c_str(),nsig.c_str(), osig.c_str());
				CgiUtil::PrintText("{\"ret\":4,\"msg\":\"请求参数错误：（sig）\"}");
				ERROR_RETURN_MSG(4, "请求参数错误：（sig）");
			}
		}

        string product = OpenPlatform::GetPlatform()->GetConfig(CONFIG_FB_PAYMENT_PRODUCT);
        CLogicTWPay logicPay;
		int ret = logicPay.deliver(openid, CTrans::STOI(serverid), token, product, CTrans::STOI(num));
		if (ret != 0)
		{
			CgiUtil::PrintText("{\"ret\":"+CTrans::ITOS(ret)+",\"msg\":\"ChangePay failed\"}");
			return ret;
		}

		//CgiUtil::PrintText("{\"ret\":0,\"msg\":\"OK\"}");防止回调过久移动到各平台虚函数
		CGI_SEND_LOG("openid=%s&billno=%s&serverid=%s&num=%s", openid.c_str(),token.c_str(),serverid.c_str(),num.c_str());
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiTWDeliver)
