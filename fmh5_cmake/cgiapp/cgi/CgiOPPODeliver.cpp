#include "LogicInc.h"
#include "LogicQQPay.h"
#include "OPPOPlatform.h"

class CCgiOPPODeliver : public CCgiBase
{
public:
	CCgiOPPODeliver() : CCgiBase("oppodeliver")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(oppodeliver)

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

	int responeXMFourMsg(bool ret,string errorMsg = "")
	{
		string postdata = "";
		if(ret)
			postdata += "result=OK&resultMsg=\"\"";
		else
			postdata += "result=FAIL&resultMsg=" + errorMsg;
		CgiUtil::PrintText(postdata);
		return 0;
	}

	int oppodeliver()
	{
		const string notifyId = CCGIIn::GetCGIStr("notifyId");
		const string partnerOrder = CCGIIn::GetCGIStr("partnerOrder");
		const string productName = CCGIIn::GetCGIStr("productName");
		const string productDesc = CCGIIn::GetCGIStr("productDesc");
		const string price = CCGIIn::GetCGIStr("price");
		const string count = CCGIIn::GetCGIStr("count");
		const string attach = CCGIIn::GetCGIStr("attach");
		const string sign = CCGIIn::GetCGIStr("sign");

		//校验签名
		string publicKey = OpenPlatform::GetPlatform()->GetConfig("publicKey");

		string signData;
		signData += "notifyId=" + notifyId;
		signData += "&partnerOrder=" + partnerOrder;
		signData += "&productName=" + productName;
		signData += "&productDesc=" + productDesc;
		signData += "&price=" + price;
		signData += "&count=" + count;
		signData += "&attach=" + attach;

		bool isValid = OPPOPlatform().CheckSign(signData,publicKey,sign);
		if(!isValid)
		{
			error_log("sig_check_error:signData=%s,sign=%s,publicKey=%s",signData.c_str(),sign.c_str(),publicKey.c_str());
			responeXMFourMsg(false,"验签失败");
			return 0;
		}

		//根据cpOrderNumber获取openid，itemid
		vector<string>strlist;
		SplitString(partnerOrder,strlist,"_");
		string openid = strlist[0];
		string itemid = strlist[1];

		//获取uid
		unsigned uid = 0;
		CDataUserMapping dbUserMapping;
		int ret = dbUserMapping.GetMapping(openid, 0, uid);
		if (ret != 0)
		{
			error_log("openid_error:openid=%s",openid.c_str());
			responeXMFourMsg(false,"无效用户");
			return 0;
		}
		int serverid = Config::GetZoneByUID(uid);
		ConfigManager::Instance()->SetServer(serverid);

		//校验订单是否已存在
		DataPayHistory payChcekHistory;
		CDataPayHistory dbCheckPayHistory;
		ret = dbCheckPayHistory.GetPayHistory(uid, PT_OPPO,notifyId, payChcekHistory);
		if(ret == 0 && payChcekHistory.status == PST_OK)			//订单已充值,重复订单
		{
			error_log("order_alreay_exsit:openid=%s",openid.c_str());
			responeXMFourMsg(true,"此前已充值成功");
			return 0;
		}

		//读取物品配置
		QQItemInfo itemInfo;
		ret = CLogicQQPay::GetItemInfo(itemid, itemInfo);
		if(ret)
		{
			error_log("itemid_error:itemid=%s",itemid.c_str());
			responeXMFourMsg(false,"物品不存在");
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
		msg->set_currency(CTrans::STOI(price));
		msg->set_tradeno(notifyId);
		msg->set_channeltradeno(notifyId);
		packet.m_msg = msg;

		bool f = true;
		ret = BattleSocket::Send(Config::GetZoneByUID(uid), &packet);
		if(ret)
		{
			error_log("[Send error][openid=%s,billno=%s,cash=%u,cost=%u]", openid.c_str(), notifyId.c_str(), cash, cash);
			f = false;
		}
		else
		{
			CSG17Packet reply;
			ret = BattleSocket::Receive(Config::GetZoneByUID(uid), &reply);
			if(ret)
			{
				error_log("[Receive error][openid=%s,billno=%s,cash=%u,cost=%u]", openid.c_str(), notifyId.c_str(), cash, cash);
				f = false;
			}
			else
			{
				Common::ReplyPay* rmsg = (Common::ReplyPay*)reply.m_msg;
				ret = rmsg->ret();
				if(ret)
				{
					error_log("[Receive error][openid=%s,billno=%s,cash=%u,cost=%u,ret=%u]", openid.c_str(), notifyId.c_str(), cash, cash, ret);
					f = false;
				}
			}
		}

		if(f)
		{
			DataPayHistory payhis;
			payhis.channel = PT_OPPO;
			payhis.channel_pay_id = notifyId;
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
						ret,openid.c_str(),notifyId.c_str(),cash,cash);
			}
			CGI_SEND_LOG("openid=%s&billno=%s&cash=%u&cost=%u&itemids=%s&uid=%u&ret=%d",
					openid.c_str(),notifyId.c_str(),cash,CTrans::STOI(price),itemid.c_str(),uid,ret);
			responeXMFourMsg(true);
			return R_SUCCESS;
		}
		else
		{
			error_log("battle_charge_error:itemid");
			responeXMFourMsg(false,"加钻失败");
			return 0;
		}
	}
};

CGI_MAIN(CCgiOPPODeliver)


