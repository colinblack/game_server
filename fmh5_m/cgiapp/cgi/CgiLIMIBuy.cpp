#include "LogicInc.h"
#include "LiMiPlatform.h"
#include "LogicQQPay.h"

class CCgiLIMIBuy : public CCgiBase
{
public:
	CCgiLIMIBuy() : CCgiBase("limibuy")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(buy)

	int buy()
	{
		const string openid = CCGIIn::GetCGIStr("openid");
		const string openkey = CCGIIn::GetCGIStr("openkey");
		const string cmd = "2";//消耗道具
		const string itemids = CCGIIn::GetCGIStr("itemids");
		const string itemnums = CCGIIn::GetCGIStr("itemnums");
		const string itemseqs = CTrans::UTOS(Time::GetGlobalTime());
		int serverid = CCGIIn::GetCGIInt("serverid", 0, 100000, 0, 0);
		ConfigManager::Instance()->SetServer(serverid);
		if (openid.empty() || openkey.empty() || itemids.empty() || itemnums.empty() || CTrans::STOI(itemnums) == 0 || CTrans::STOI(itemids) == 0)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		unsigned uid = 0;
		int ret = CDataUserMapping().GetMapping(openid, 0, uid);
		if(ret)
		{
			PARAM_ERROR_RETURN_MSG("no_uid");
		}

		const string api_name = "/openapi/apollo_game_item_proxy";
		const string appid = OpenPlatform::GetPlatform()->GetAppId();
		const string appkey = OpenPlatform::GetPlatform()->GetAppKey();
		const string gameid = OpenPlatform::GetPlatform()->GetConfig("gameid");

		map<string, string> param_map;
		param_map.clear();
		param_map["appid"] = appid;
		param_map["openid"] = openid;
		param_map["openkey"] = openkey;
		param_map["itemids"] = itemids;
		param_map["itemnums"] = itemnums;
		param_map["itemseqs"] = itemseqs;
		param_map["cmd"] = cmd;
		param_map["gameid"] = gameid;
		param_map["ts"] = CTrans::UTOS(Time::GetGlobalTime());
		param_map["rnd"] = CTrans::UTOS(Math::GetRandomUInt());

		QQItemInfo itemInfo;
		ret = CLogicQQPay::GetItemInfo(itemids, itemInfo);
		if(ret)
			return ret;

		//发送请求
		string url = OpenPlatform::GetPlatform()->GetConfig("v3domain") + api_name;
		string postdata;
		LiMiPlatform::formatUrl(param_map, appkey, api_name, postdata);
		string response;
		if (!Network::HttpPostRequest(response, url, postdata) || response.empty())
		{
			error_log("[http request fail][url=%s,data=%s,openid=%s,response=%s]", url.c_str(), postdata.c_str(), openid.c_str(), response.c_str());
			ERROR_RETURN_MSG(R_ERR_NO_DATA, "http_request_fail");
		}
		Json::Value result;
		Json::Reader reader;
		int responsetRet = 0;
		if (response.empty()
		|| !reader.parse(response, result)
		|| !Json::GetInt(result, "ret", responsetRet)
		|| responsetRet != 0
		|| !result.isMember("data")
		|| !result["data"]["succList"].isArray()
		|| result["data"]["succList"].size() == 0)
		{
			error_log("[response error][url=%s,data=%s,openid=%s,response=%s]", url.c_str(), postdata.c_str(), openid.c_str(), response.c_str());
			ERROR_RETURN_MSG(R_ERR_NO_DATA, "response_error");
		}

		unsigned cash = 0, cost = 0;
		string billno;
		Json::GetString(result["data"]["succList"][0u], "seq", billno);
		cash = itemInfo.cash * CTrans::STOI(itemnums);
		cost = cash;


		CSG17Packet packet;
		packet.cmd = PROTOCOL_DELIVER;
		Common::Pay* msg = new Common::Pay;
		msg->set_uid(uid);
		msg->set_cash(cash);
		msg->set_itemid(CTrans::STOI(itemids));
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
		payhis.channel = PT_LIMI;
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
		CGI_SEND_LOG("openid=%s&billno=%s&cash=%u&cost=%u&itemids=%s&itemnums=%s&uid=%u&ret=%d",
				openid.c_str(),billno.c_str(),cash,cost,itemids.c_str(),itemnums.c_str(),uid,ret);
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiLIMIBuy)
