/*
 * CgiMi2Deliver.cpp
 *	小米2 支付完成回调接口,根据回调参数cpOrderId给玩家充值
 *  Created on: 2018年11月13日
 *
 */


#include "LogicInc.h"
#include "LogicQQPay.h"
#include "Mi2Platform.h"

class CCgiMi2Deliver : public CCgiBase
{
public:
	CCgiMi2Deliver() : CCgiBase("Mi2deliver")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(buy)

	int buy()
	{
		const string appId = CCGIIn::GetCGIStr("appId");
		const string cpOrderId = CCGIIn::GetCGIStr("cpOrderId");
		const string cpUserInfo = CCGIIn::GetCGIStr("cpUserInfo");		//小米2 cpUserInfo代表前端传的uid
		const string openid = CCGIIn::GetCGIStr("uid");					//小米2 uid代表openid
		const string orderId = CCGIIn::GetCGIStr("orderId");
		const string orderStatus = CCGIIn::GetCGIStr("orderStatus");
		const string payFee = CCGIIn::GetCGIStr("payFee");
		const string payTime = CCGIIn::GetCGIStr("payTime");
		const string productCode = CCGIIn::GetCGIStr("productCode");
		const string productCount = CCGIIn::GetCGIStr("productCount");
		const string productName = CCGIIn::GetCGIStr("productName");
		const string signature = CCGIIn::GetCGIStr("signature");

		int serverid = Config::GetZoneByUID(CTrans::STOI(cpUserInfo));	 //计算serverId,从数据库查询数据有用
		ConfigManager::Instance()->SetServer(serverid);

		map<string,string> params;										//参数名必须按字典序排序
		params["appId"] = appId;
		params["cpOrderId"] = cpOrderId;
		params["cpUserInfo"] = cpUserInfo;
		params["orderId"] = orderId;
		params["orderStatus"] = orderStatus;
		params["payFee"] = payFee;
		params["payTime"] = payTime;
		params["productCode"] = productCode;
		params["productCount"] = productCount;
		params["productName"] = Crypt::UrlDecode(productName);
		params["uid"] = openid;

		//string AppSecret = "07UslPEoZmp7gCe8uRh+GQ==";
		string AppSecret = OpenPlatform::GetPlatform()->GetConfig("sigkey");
		string sign_check = Mi2Platform().GetSig(params, AppSecret);	//产生签名校验码

		if(sign_check.compare(signature) != 0 || orderStatus.compare("TRADE_SUCCESS") != 0)	//签名校验失败或者购买状态错误
		{
			error_log("signature maybe wrong,openid=%s,uid=%s,cpOrderId=%s,orderStatus=%s,signature=%s,sign_check=%s",
					openid.c_str(),cpUserInfo.c_str(),cpOrderId.c_str(),orderStatus.c_str(),signature.c_str(),sign_check.c_str());

			CgiUtil::PrintText("{\"errcode\":1525,\"errMsg\":\"wrong signature\"}");
			return 0;
		}

		unsigned uid = CTrans::STOI(cpUserInfo);
		DataPayHistory payHistory;
		CDataPayHistory dbPayHistory;
		int ret = dbPayHistory.GetPayHistory(uid, CTrans::STOI64(cpOrderId), payHistory);
		if(ret == 0 && payHistory.status == PST_OK)			//订单已充值,重复订单
		{
			CgiUtil::PrintText("{\"errcode\":200,\"errMsg\":\"success\"}");
			return 0;
		}
		if(ret !=0 || payHistory.status != PST_PENDING)		//数据库没有查询到该订单
		{
			error_log("search database failure,openid=%s,uid=%s,cpOrderId=%s,orderStatus=%s,signature=%s,sign_check=%s",
					openid.c_str(),cpUserInfo.c_str(),cpOrderId.c_str(),orderStatus.c_str(),signature.c_str(),sign_check.c_str());

			CgiUtil::PrintText("{\"errcode\":1,\"errMsg\":\"no such cpUserId\"}");
			return 0;
		}

		//通知battle充值
		CSG17Packet packet;
		packet.cmd = PROTOCOL_DELIVER;
		Common::Pay* msg = new Common::Pay;
		msg->set_uid(uid);
		msg->set_cash(payHistory.count);
		msg->set_itemid(payHistory.type);
		msg->set_ts(Time::GetGlobalTime());
		msg->set_currency(CTrans::STOI(payFee));
		msg->set_tradeno(cpOrderId);
		msg->set_channeltradeno(orderId);
		packet.m_msg = msg;

		bool f = true;
		ret = BattleSocket::Send(Config::GetZoneByUID(uid), &packet);
		if(ret)
		{
			error_log("[Send error][openid=%s,billno=%s,cash=%u,payFee=%s]", openid.c_str(), orderId.c_str(), payHistory.count, payFee.c_str());
			f = false;
		}
		else
		{
			CSG17Packet reply;
			ret = BattleSocket::Receive(Config::GetZoneByUID(uid), &reply);
			if(ret)
			{
				error_log("[Receive error][openid=%s,billno=%s,cash=%u,payFee=%s]", openid.c_str(), orderId.c_str(), payHistory.count, payFee.c_str());
				f = false;
			}
			else
			{
				Common::ReplyPay* rmsg = (Common::ReplyPay*)reply.m_msg;
				ret = rmsg->ret();
				if(ret)
				{
					error_log("[Receive error][openid=%s,billno=%s,cash=%u,payFee=%s,ret=%u]", openid.c_str(), orderId.c_str(), payHistory.count, payFee.c_str(), ret);
					f = false;
				}
			}
		}

		if(f)
		{
			CgiUtil::PrintText("{\"errcode\":200,\"errMsg\":\"success\"}");
			payHistory.channel_pay_id = orderId;
			payHistory.status = PST_OK;
			payHistory.credit = CTrans::STOI(payFee);
			dbPayHistory.SetPayHistory(uid, payHistory.pay_id, payHistory);
		}
		else
		{
			CgiUtil::PrintText("{\"errcode\":2,\"errMsg\":\"battle server refused\"}");
		}
		CGI_SEND_LOG("openid=%s&billno=%s&cash=%u&cost=%u&itemid=%u&uid=%u&ret=%d",
				openid.c_str(),orderId.c_str(),payHistory.count,payHistory.credit,payHistory.type,uid,ret);
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiMi2Deliver)


