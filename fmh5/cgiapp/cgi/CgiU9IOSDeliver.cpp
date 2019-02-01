/*
 * CgiU9IOSDeliver.cpp
 *
 *  Created on: 2018年9月8日
 *      Author: Ralf
 */



#include "LogicInc.h"
#include "LogicQQPay.h"

class CgiU9IOSDeliver : public CCgiBase
{
public:
	CgiU9IOSDeliver() : CCgiBase("u9iosdeliver")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(buy)

	int buy()
	{
		string transdata = CCGIIn::GetCGIStr("transdata");
		string sign = CCGIIn::GetCGIStr("sign");
		Json::Value data;
		if(transdata.empty() || sign.empty() || Crypt::Md5EncodeC(transdata+"&key="+OpenPlatform::GetPlatform()->GetAppKey()) != sign || !Json::Reader().parse(transdata, data))
		{
			error_log("parse error: transdata=%s, sign=%s", transdata.c_str(), sign.c_str());
			CgiUtil::PrintText("FAIL");
			return 0;
		}

		int result=1, amount=0;
		string app_order_id, app_ext;
		Json::GetInt(data, "result", result);
		Json::GetInt(data, "amount", amount);
		Json::GetString(data, "app_order_id", app_order_id);
		Json::GetString(data, "app_ext", app_ext);
		if(result)
		{
			error_log("result error: transdata=%s, sign=%s", transdata.c_str(), sign.c_str());
			CgiUtil::PrintText("FAIL");
			return 0;
		}
		vector<string> rlt;
		String::Split(app_ext, '_', rlt);
		if (rlt.size() < 2 || rlt[0].empty())
		{
			error_log("app_ext error: transdata=%s, sign=%s", transdata.c_str(), sign.c_str());
			CgiUtil::PrintText("FAIL");
			return 0;
		}
		string openid = rlt[0];
		int serverid = CTrans::STOI(rlt[1]);
		ConfigManager::Instance()->SetServer(serverid);

		unsigned uid = 0;
		int ret = CDataUserMapping().GetMapping(openid, 0, uid);
		if(ret)
		{
			error_log("openid error: transdata=%s, sign=%s", transdata.c_str(), sign.c_str());
			CgiUtil::PrintText("FAIL");
			return 0;
		}

		DataPayHistory payHistory;
		CDataPayHistory dbPayHistory;
		ret = dbPayHistory.GetPayHistory(uid, CTrans::STOI64(app_order_id), payHistory);
		if(ret != 0 || payHistory.status != PST_PENDING)
		{
			error_log("app_order_id error: transdata=%s, sign=%s", transdata.c_str(), sign.c_str());
			CgiUtil::PrintText("FAIL");
			return 0;
		}

		CSG17Packet packet;
		packet.cmd = PROTOCOL_DELIVER;
		Common::Pay* msg = new Common::Pay;
		msg->set_uid(uid);
		msg->set_cash(payHistory.count);
		msg->set_itemid(payHistory.type);
		msg->set_ts(Time::GetGlobalTime());
		packet.m_msg = msg;

		bool f = true;
		ret = BattleSocket::Send(Config::GetZoneByUID(uid), &packet);
		if(ret)
		{
			error_log("[Send error][openid=%s,billno=%s,cash=%u,cost=%u]", openid.c_str(), app_order_id.c_str(), payHistory.count, amount);
			f = false;
		}
		else
		{
			CSG17Packet reply;
			ret = BattleSocket::Receive(Config::GetZoneByUID(uid), &reply);
			if(ret)
			{
				error_log("[Receive error][openid=%s,billno=%s,cash=%u,cost=%u]", openid.c_str(), app_order_id.c_str(), payHistory.count, amount);
				f = false;
			}
			else
			{
				Common::ReplyPay* rmsg = (Common::ReplyPay*)reply.m_msg;
				ret = rmsg->ret();
				if(ret)
				{
					error_log("[Receive error][openid=%s,billno=%s,cash=%u,cost=%u,ret=%u]", openid.c_str(), app_order_id.c_str(), payHistory.count, amount, ret);
					f = false;
				}
			}
		}

		if(f)
		{
			CgiUtil::PrintText("{\"Code\":0,\"Message\":\"success\"}");
			payHistory.channel_pay_id = app_order_id;
			payHistory.status = PST_OK;
			payHistory.credit = amount;
			dbPayHistory.SetPayHistory(uid, payHistory.pay_id, payHistory);
		}
		else
			CgiUtil::PrintText("{\"Code\":1,\"Message\":\"failure\"}");


		CGI_SEND_LOG("openid=%s&billno=%s&cash=%u&cost=%u&itemid=%u&uid=%u&ret=%d",
				openid.c_str(),app_order_id.c_str(),payHistory.count,payHistory.credit,payHistory.type,uid,ret);
		return R_SUCCESS;
	}

};

CGI_MAIN(CgiU9IOSDeliver)


