#include "LogicInc.h"
#include "WanBaPlatform.h"
#include "LogicQQPay.h"

class CCgiWBBuy : public CCgiBase
{
public:
	CCgiWBBuy() : CCgiBase("wbbuy")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(buy)

	int buy()
	{
		if(OpenPlatform::GetType() != PT_WB)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		const string openid = CCGIIn::GetCGIStr("openid");
		const string openkey = CCGIIn::GetCGIStr("openkey");
		const string pf = CCGIIn::GetCGIStr("pf");
		const int count = CCGIIn::GetCGIInt("count");
		const string id = CCGIIn::GetCGIStr("id");
		int serverid = CCGIIn::GetCGIInt("serverid", 0, 100000, 0, 0);
		ConfigManager::Instance()->SetServer(serverid);
		if (openid.empty() || openkey.empty() || pf.empty() || count == 0 || id.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		unsigned uid = 0;
		int ret = CDataUserMapping().GetMapping(openid, 0, uid);
		if(ret)
		{
			PARAM_ERROR_RETURN_MSG("no_uid");
		}

		const string api_name = "/v3/user/buy_playzone_item";
		const string &appid = OpenPlatform::GetPlatform()->GetAppId();
		const string &appkey = OpenPlatform::GetPlatform()->GetAppKey();
		QQItemInfo itemInfo;
		ret = CLogicQQPay::GetItemInfo(id, itemInfo);
		if (ret)
			return ret;
		map<string, string> param_map;
		param_map["appid"] = appid;
		param_map["openid"] = openid;
		param_map["openkey"] = openkey;
		param_map["pf"] = pf;
		param_map["format"] = "json";
		param_map["userip"] = m_ipstr;
		param_map["zoneid"] = Config::GetIntValue(CONFIG_ZONE_ID);
		param_map["billno"] = Crypt::Md5Encode(openid + CTrans::ITOS(Time::GetGlobalTime()) + itemInfo.itemid);
		param_map["itemid"] = itemInfo.itemid;
		param_map["count"] = CTrans::ITOS(count);

		string url;
		WanBaPlatform::formatUrl(param_map, appkey, api_name, url, OpenPlatform::GetPlatform()->GetConfig("v3domain"));
		debug_log("openid=%s,url=%s", openid.c_str(), url.c_str());
		string response;
		if (!Network::HttpGetRequest(response, url) || response.empty())
		{
			error_log("[http request fail][url=%s,openid=%s,response=%s]", url.c_str(), openid.c_str(), response.c_str());
			ERROR_RETURN_MSG(R_ERR_NO_DATA, "http_request_fail");
		}
		Json::Value result;
		Json::Reader reader;
		int responsetRet = 0;
		if (response.empty()
		|| !reader.parse(response, result)
		|| !Json::GetInt(result, "code", responsetRet)
		|| responsetRet != 0
		|| !result.isMember("data")
		|| !result["data"].isArray()
		|| result["data"].size() == 0)
		{
			error_log("[response error][openid=%s,response=%s]", openid.c_str(), response.c_str());
			ERROR_RETURN_MSG(R_ERR_NO_DATA, "response_error");
		}

		unsigned cash = 0, cost = 0;
		string billno;
		Json::GetString(result["data"][0u], "billno", billno);
		Json::GetUInt(result["data"][0u], "cost", cost);
		cash = itemInfo.cash * count;

		CSG17Packet packet;
		packet.cmd = PROTOCOL_DELIVER;
		Common::Pay* msg = new Common::Pay;
		msg->set_uid(uid);
		msg->set_cash(cash);
		msg->set_ts(Time::GetGlobalTime());
		packet.m_msg = msg;

		bool f = true;
		ret = BattleSocket::Send(Config::GetZoneByUID(uid), &packet);
		if(ret)
		{
			error_log("[Send error][openid=%s,billno=%s,cash=%u,cost=%u]", openid.c_str(), billno.c_str(), cash, cost);
			f = false;
		}
		else
		{
			CSG17Packet reply;
			ret = BattleSocket::Receive(Config::GetZoneByUID(uid), &reply);
			if(ret)
			{
				error_log("[Receive error][openid=%s,billno=%s,cash=%u,cost=%u]", openid.c_str(), billno.c_str(), cash, cost);
				f = false;
			}
			else
			{
				Common::ReplyPay* rmsg = (Common::ReplyPay*)reply.m_msg;
				ret = rmsg->ret();
				if(ret)
				{
					error_log("[Receive error][openid=%s,billno=%s,cash=%u,cost=%u,ret=%u]", openid.c_str(), billno.c_str(), cash, cost, ret);
					f = false;
				}
			}
		}

		DataPayHistory payhis;
		payhis.channel = PT_WB;
		payhis.channel_pay_id = billno;
		payhis.count = cash;
		payhis.credit = cost;
		payhis.status = f?PST_OK:PST_PENDING;
		payhis.type = itemInfo.type;
		payhis.uid = uid;
		payhis.open_id = openid;
		ret = CLogicQQPay().AddPayHistory(payhis);
		if (ret != 0)
		{
			error_log("[AddPayHistory fail][ret=%d,openid=%s,billno=%s,cash=%u,cost=%u]",
					ret,openid.c_str(),billno.c_str(),cash,cost);
		}

		m_jsonResult["cash"] = cash;
		m_jsonResult["cost"] = cost;
		m_jsonResult["succ"] = f?1:0;
		CGI_SEND_LOG("openid=%s&billno=%s&cash=%u&cost=%u", openid.c_str(),billno.c_str(),cash,cost);
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiWBBuy)
