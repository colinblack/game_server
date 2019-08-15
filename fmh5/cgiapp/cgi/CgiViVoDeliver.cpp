#include "LogicInc.h"
#include "LogicQQPay.h"
#include "VIVOPlatform.h"

class CCgivivoDeliver : public CCgiBase
{
public:
	CCgivivoDeliver() : CCgiBase("vivodeliver")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(vivodeliver)

	//字符串分割
	void SplitString(const string& s, vector<string>& v, const string& c)
	{
		string::size_type pos1, pos2;
		pos2 = s.find(c);
		pos1 = 0;
		while(string::npos != pos2)
		{
			v.push_back(s.substr(pos1, pos2-pos1));

			pos1 = pos2 + c.size();
			pos2 = s.find(c, pos1);
		}
		if(pos1 != s.length())
			v.push_back(s.substr(pos1));
	}

	int responeXMFourMsg(bool ret)
	{
		string postdata = "";
		if(ret)
			postdata += "success";
		else
			postdata += "fail";
		CgiUtil::PrintText(postdata);
		return 0;
	}

	int vivodeliver()
	{
		const string respCode = CCGIIn::GetCGIStr("respCode");
		const string respMsg = CCGIIn::GetCGIStr("respMsg");
		const string signMethod = CCGIIn::GetCGIStr("signMethod");
		const string signature = CCGIIn::GetCGIStr("signature");
		const string cpOrderNumber = CCGIIn::GetCGIStr("cpOrderNumber");
		const string vivoOrderNumber = CCGIIn::GetCGIStr("vivoOrderNumber");
		const string orderAmount = CCGIIn::GetCGIStr("orderAmount");
		const string factAmount = CCGIIn::GetCGIStr("factAmount");
		const string paymentTime = CCGIIn::GetCGIStr("paymentTime");
		const string channel = CCGIIn::GetCGIStr("channel");
		const string channelOrderNo = CCGIIn::GetCGIStr("channelOrderNo");

		//校验签名
		string cpId = OpenPlatform::GetPlatform()->GetConfig("cpid");
		string appId = OpenPlatform::GetPlatform()->GetConfig("appid");
		string AppKey = OpenPlatform::GetPlatform()->GetConfig("appkey");
		if(respCode != "200" || respMsg != "SUCCESS")
		{
			error_log("resp_error:respcode=%s,respmsg=%s",respCode.c_str(),respMsg.c_str());
			responeXMFourMsg(false);
			return 0;
		}
		map<string,string>params;
		params.clear();
		params["respCode"] = respCode;
		params["respMsg"] = respMsg;
		params["cpOrderNumber"] = cpOrderNumber;
		params["vivoOrderNumber"] = vivoOrderNumber;
		params["orderAmount"] = orderAmount;
		params["factAmount"] = factAmount;
		params["paymentTime"] = paymentTime;
		params["channel"] = channel;
		params["channelOrderNo"] = channelOrderNo;
		params["cpId"] = cpId;
		params["appId"] = appId;
		string sig = VIVOPlatform().GetSigStr(params,AppKey);
		if(sig != signature)
		{
			error_log("sig_check_error:sig=%s,signature=%s",sig.c_str(),signature.c_str());
			responeXMFourMsg(false);
			return 0;
		}

		//根据cpOrderNumber获取openid，itemid
		vector<string>strlist;
		SplitString(cpOrderNumber,strlist,",");
		string openid = strlist[0];
		string itemid = strlist[1];

		//获取uid
		unsigned uid = 0;
		CDataUserMapping dbUserMapping;
		int ret = dbUserMapping.GetMapping(openid, 0, uid);
		if (ret != 0)
		{
			error_log("openid_error:openid=%s",openid.c_str());
			responeXMFourMsg(false);
			return 0;
		}
		int serverid = Config::GetZoneByUID(uid);
		ConfigManager::Instance()->SetServer(serverid);

		//校验订单是否已存在
		DataPayHistory payChcekHistory;
		CDataPayHistory dbCheckPayHistory;
		ret = dbCheckPayHistory.GetPayHistory(uid, PT_VIVO,vivoOrderNumber, payChcekHistory);
		if(ret == 0 && payChcekHistory.status == PST_OK)			//订单已充值,重复订单
		{
			error_log("order_alreay_exsit:openid=%s",openid.c_str());
			responeXMFourMsg(true);
			return 0;
		}


		//读取物品配置
		QQItemInfo itemInfo;
		ret = CLogicQQPay::GetItemInfo(itemid, itemInfo);
		if(ret)
		{
			error_log("itemid_error:itemid=%s",itemid.c_str());
			responeXMFourMsg(false);
			return 0;
		}
		unsigned cash = itemInfo.cash;

		//给battle发送消息
		CSG17Packet packet;
		packet.cmd = PROTOCOL_DELIVER;
		Common::Pay* msg = new Common::Pay;
		msg->set_uid(uid);
		msg->set_cash(cash);
		msg->set_itemid(CTrans::STOI(itemid));
		msg->set_ts(Time::GetGlobalTime());
		msg->set_currency(CTrans::STOI(factAmount) * 100);
		msg->set_tradeno(vivoOrderNumber);
		msg->set_channeltradeno(vivoOrderNumber);
		packet.m_msg = msg;

		bool f = true;
		ret = BattleSocket::Send(Config::GetZoneByUID(uid), &packet);
		if(ret)
		{
			error_log("[Send error][openid=%s,billno=%s,cash=%u,cost=%u]", openid.c_str(), vivoOrderNumber.c_str(), cash, cash);
			f = false;
		}
		else
		{
			CSG17Packet reply;
			ret = BattleSocket::Receive(Config::GetZoneByUID(uid), &reply);
			if(ret)
			{
				error_log("[Receive error][openid=%s,billno=%s,cash=%u,cost=%u]", openid.c_str(), vivoOrderNumber.c_str(), cash, cash);
				f = false;
			}
			else
			{
				Common::ReplyPay* rmsg = (Common::ReplyPay*)reply.m_msg;
				ret = rmsg->ret();
				if(ret)
				{
					error_log("[Receive error][openid=%s,billno=%s,cash=%u,cost=%u,ret=%u]", openid.c_str(), vivoOrderNumber.c_str(), cash, cash, ret);
					f = false;
				}
			}
		}

		if(f)
		{
			DataPayHistory payhis;
			payhis.channel = PT_VIVO;
			payhis.channel_pay_id = vivoOrderNumber;
			payhis.count = cash;
			payhis.credit = cash;
			payhis.status = PST_OK;
			payhis.type = itemInfo.type;
			payhis.uid = uid;
			payhis.open_id = openid;
			ret = CLogicQQPay().AddPayHistory(payhis);
			if (ret != 0)
			{
				error_log("[AddPayHistory fail][ret=%d,openid=%s,billno=%s,cash=%u,cost=%u]",
						ret,openid.c_str(),vivoOrderNumber.c_str(),cash,cash);
			}
			CGI_SEND_LOG("openid=%s&billno=%s&cash=%u&cost=%u&itemids=%s&uid=%u&ret=%d",
					openid.c_str(),vivoOrderNumber.c_str(),cash,CTrans::STOI(factAmount) * 100,itemid.c_str(),uid,ret);
			responeXMFourMsg(true);
			return R_SUCCESS;
		}
		else
		{
			error_log("battle_charge_error:itemid");
			responeXMFourMsg(false);
			return 0;
		}
	}
};

CGI_MAIN(CCgivivoDeliver)


