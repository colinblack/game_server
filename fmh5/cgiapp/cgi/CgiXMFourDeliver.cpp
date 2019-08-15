#include "LogicInc.h"
#include "XMFourPlatform.h"

class CCgiXMFourDeliver : public CCgiBase
{
public:

	CCgiXMFourDeliver() : CCgiBase("qqdeliver")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(deliver)

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
			postdata += "{\"code\":200 }";
		else
			postdata += "{\"code\":400 }";
		CgiUtil::PrintText(postdata);
		return 0;
	}

	int deliver()
	{
		//--------获取post提交的data数据
		string method;
		CgiUtil::GetRequestMethod(method);
		if(method != "POST")
		{
			error_log("method_is_error,method=%s",method.c_str());
			responeXMFourMsg(false);
			return R_ERROR;
		}
		string postdata;
		CgiUtil::GetPostData(postdata);
		Json::Value value;
		if (!Json::Reader().parse(postdata, value))
		{
			error_log("[postdata_parse_failed][postdata=%s]",postdata.c_str());
			responeXMFourMsg(false);
			return R_ERROR;
		}

		string status;
		string msgdata;
		string extend;
		string orderId;
		uint64_t timestmap;
		string sign;
		bool f1,f2,f3,f4,f5,f6;
		f1 = Json::GetString(value, "status", status);
		f2 = Json::GetString(value, "msg", msgdata);
		f3 = Json::GetString(value, "extend", extend);
		f4 = Json::GetString(value, "orderId", orderId);
		f5 = Json::GetUInt64(value, "timestamp", timestmap);
		f6 = Json::GetString(value, "sign", sign);
		if(!f1 || !f2 || !f3 || !f4 || !f5 || !f6)
		{
			error_log("[data_parse_failed][f1=%d,f2=%d,%f3=%d,f4=%d,f5=%d,f6=%d,timestmap=%llu,data=%s]",
						f1,f2,f3,f4,f5,f6,timestmap,postdata.c_str());
			responeXMFourMsg(false);
			return R_ERROR;
		}

		//校验消息状态
		if(status != "TRADE_SUCCESS")
		{
			//如果消息状态码不对，直接返回200,后端不做加钻逻辑
			responeXMFourMsg(true);
			return 0;
		}

		//校验签名、验证数据是否合法
		map<string,string>Param;
		Param["status"] = status;
		Param["msg"] = msgdata;
		Param["extend"] = extend;
		Param["orderId"] = orderId;
		vector<string> timestr;
		SplitString(CTrans::FTOS(timestmap),timestr,".");
		Param["timestamp"] = timestr[0];
		string sigkey = OpenPlatform::GetPlatform()->GetConfig("appkey");//签名key
		string sig = XMFourPlatform::GetSigStr(Param,sigkey);
		if(sign != sig)
		{
			error_log("[data_check_failed][sign=%s,sig=%s]",sign.c_str(),sig.c_str());
			responeXMFourMsg(false);
			return R_ERROR;
		}

		//签名通过-----------
		vector<string> userdata;
		SplitString(extend,userdata,"_");
		if(userdata.size() != 4){
			error_log("extend_data_error,extend=%s",extend.c_str());
			responeXMFourMsg(false);
			return R_ERROR;
		}
		string openid = userdata[0];
		unsigned uid = CTrans::STOI(userdata[1].c_str());
		string itemid = userdata[2];
		int itemcnt = CTrans::STOI(userdata[3].c_str());


		//读取物品配置信息
		QQItemInfo itemInfo;
		int ret = CLogicQQPay::GetItemInfo(itemid, itemInfo);
		if(ret) {
			error_log("item error:%s,itemid=%s", itemid.c_str());
			responeXMFourMsg(false);
			return R_ERROR;
		}

		//获取订单信息
		unsigned cash = 0;
		string billno = orderId;
		cash = itemInfo.cash * itemcnt;

		//------------加钻、充值记录处理
		ConfigManager::Instance()->SetServer(Config::GetZoneByUID(uid));
		CSG17Packet packet;
		packet.cmd = PROTOCOL_DELIVER;
		Common::Pay* msg = new Common::Pay;
		msg->set_uid(uid);
		msg->set_cash(cash);
		msg->set_ts(Time::GetGlobalTime());
		msg->set_itemid(CTrans::STOI(itemid));
		msg->set_currency(itemInfo.price * itemcnt);
		msg->set_tradeno(billno);
		msg->set_channeltradeno(billno);
		packet.m_msg = msg;

		bool f = true;
		ret = BattleSocket::Send(Config::GetZoneByUID(uid), &packet);
		if(ret)
		{
			error_log("[Send error][billno=%s,cash=%u]", billno.c_str(), cash);
			f = false;
		}
		else
		{
			CSG17Packet reply;
			ret = BattleSocket::Receive(Config::GetZoneByUID(uid), &reply);
			if(ret)
			{
				error_log("[Receive error][billno=%s,cash=%u]", billno.c_str(), cash);
				f = false;
			}
			else
			{
				Common::ReplyPay* rmsg = (Common::ReplyPay*)reply.m_msg;
				ret = rmsg->ret();
				if(ret)
				{
					error_log("[Receive error][billno=%s,cash=%u,ret=%u]", billno.c_str(), cash, ret);
					f = false;
				}
			}
		}

		DataPayHistory payhis;
		payhis.channel = PT_XMFOUR;
		payhis.channel_pay_id = billno;
		payhis.count = cash;
		payhis.credit = CTrans::STOI(Param["total_fee"]);
		payhis.status = f?PST_OK:PST_PENDING;
		payhis.type = itemInfo.type;
		payhis.uid = uid;
		payhis.open_id = openid;
		ret = CLogicQQPay().AddPayHistory(payhis);
		if (ret != 0)
		{
			error_log("[AddPayHistory fail][ret=%d,openid=%s,billno=%s,cash=%u]",
					ret,openid.c_str(),billno.c_str(),cash);
		}
		responeXMFourMsg(f);

		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiXMFourDeliver)
