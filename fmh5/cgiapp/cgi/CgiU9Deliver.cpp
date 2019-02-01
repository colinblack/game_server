/*
 * CgiU9Deliver.cpp
 *
 *  Created on: 2018年8月24日
 *      Author: Ralf
 */


#include "LogicInc.h"
#include "LogicQQPay.h"

class CCgiU9Deliver : public CCgiBase
{
public:
	CCgiU9Deliver() : CCgiBase("u9deliver")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(buy)

	int buy()
	{
		const string openid = CCGIIn::GetCGIStr("UserId");
		const string ProductOrderId = CCGIIn::GetCGIStr("ProductOrderId");
		const string OrderId = CCGIIn::GetCGIStr("OrderId");
		const string ChannelOrderId = CCGIIn::GetCGIStr("ChannelOrderId");
		const string Sign = CCGIIn::GetCGIStr("Sign");
		int ReqAmount = CCGIIn::GetCGIInt("ReqAmount ", 0, 100000, 0, 0);
		int Code  = CCGIIn::GetCGIInt("Code  ", 0, 100000, 0, 0);
		int serverid = CCGIIn::GetCGIInt("AppExt ", 0, 100000, 0, 0);
		ConfigManager::Instance()->SetServer(serverid);

		if (openid.empty() || Code == 1 || Crypt::Md5Encode(ProductOrderId + OrderId + ChannelOrderId + OpenPlatform::GetPlatform()->GetAppKey()) != Sign)
		{
			error_log("para_err: openid=%s, ProductOrderId=%s, OrderId=%s, ChannelOrderId=%s, Sign=%s",
					openid.c_str(), ProductOrderId.c_str(), OrderId.c_str(), ChannelOrderId.c_str(), Sign.c_str());
			CgiUtil::PrintText("{\"Code\":1,\"Message\":\"failure\"}");
			return 0;
		}

		unsigned uid = 0;
		int ret = CDataUserMapping().GetMapping(openid, 0, uid);
		if(ret)
		{
			error_log("openid_err: openid=%s, ProductOrderId=%s, OrderId=%s, ChannelOrderId=%s, Sign=%s",
					openid.c_str(), ProductOrderId.c_str(), OrderId.c_str(), ChannelOrderId.c_str(), Sign.c_str());
			CgiUtil::PrintText("{\"Code\":1,\"Message\":\"failure\"}");
			return 0;
		}

		DataPayHistory payHistory;
		CDataPayHistory dbPayHistory;
		ret = dbPayHistory.GetPayHistory(uid, CTrans::STOI64(ProductOrderId), payHistory);
		if(ret != 0 || payHistory.status != PST_PENDING)
		{
			error_log("ProductOrderId_err: openid=%s, ProductOrderId=%s, OrderId=%s, ChannelOrderId=%s, Sign=%s",
					openid.c_str(), ProductOrderId.c_str(), OrderId.c_str(), ChannelOrderId.c_str(), Sign.c_str());
			CgiUtil::PrintText("{\"Code\":1,\"Message\":\"failure\"}");
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
			error_log("[Send error][openid=%s,billno=%s,cash=%u,cost=%u]", openid.c_str(), OrderId.c_str(), payHistory.count, ReqAmount);
			f = false;
		}
		else
		{
			CSG17Packet reply;
			ret = BattleSocket::Receive(Config::GetZoneByUID(uid), &reply);
			if(ret)
			{
				error_log("[Receive error][openid=%s,billno=%s,cash=%u,cost=%u]", openid.c_str(), OrderId.c_str(), payHistory.count, ReqAmount);
				f = false;
			}
			else
			{
				Common::ReplyPay* rmsg = (Common::ReplyPay*)reply.m_msg;
				ret = rmsg->ret();
				if(ret)
				{
					error_log("[Receive error][openid=%s,billno=%s,cash=%u,cost=%u,ret=%u]", openid.c_str(), OrderId.c_str(), payHistory.count, ReqAmount, ret);
					f = false;
				}
			}
		}

		if(f)
		{
			CgiUtil::PrintText("{\"Code\":0,\"Message\":\"success\"}");
			payHistory.channel_pay_id = OrderId;
			payHistory.status = PST_OK;
			payHistory.credit = ReqAmount;
			dbPayHistory.SetPayHistory(uid, payHistory.pay_id, payHistory);
		}
		else
			CgiUtil::PrintText("{\"Code\":1,\"Message\":\"failure\"}");


		CGI_SEND_LOG("openid=%s&billno=%s&cash=%u&cost=%u&itemid=%u&uid=%u&ret=%d",
				openid.c_str(),OrderId.c_str(),payHistory.count,payHistory.credit,payHistory.type,uid,ret);
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiU9Deliver)


