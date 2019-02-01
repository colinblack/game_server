#include "LogicInc.h"
#include "LiMiPlatform.h"

class CCgiLMQQDeliver : public CCgiBase
{
public:
	CCgiLMQQDeliver() : CCgiBase("qqdeliver")
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

	//将xml字符串data中的数据存储在param中
	int paramXML(map<string,string> & param,const string data)
	{
		CMarkupSTL xml;
		if(!xml.SetDoc(data.c_str()) || !xml.FindElem("xml"))
		{
			error_log("parse_error:%s", data.c_str());
			ERROR_RETURN_MSG(R_ERROR, "parse_error");
		}
		xml.IntoElem();
		while(xml.FindElem())
			param[xml.GetTagName()] = xml.GetData();
		return 0;
	}

	int responeQQBagMsg(bool ret)
	{
		map<string,string>resp;
		resp.clear();
		if(ret)
			resp["return_code"] = "SUCCESS";
		else
			resp["return_code"] = "FAIL";

		string postdata = LiMiPlatform::GenerateXMLStr(resp);
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
			error_log("method_is_error");
			responeQQBagMsg(false);
			return R_ERROR;
		}
		string postdata;
		CgiUtil::GetPostData(postdata);

		//-------初始化请求中的post数据
		map<string,string>Param;
		int ret = paramXML(Param,postdata);
		if(ret) {
			responeQQBagMsg(false);
			return R_ERROR;
		}

		//------验证签名
		string sigkey = OpenPlatform::GetPlatform()->GetConfig("sigkey");//签名key
		string deliverSig;
		map<string,string>::iterator it = Param.find("sign");
		if(it != Param.end())
		{
			deliverSig = Param["sign"];//接收到的签名
			Param.erase(it);//签名验证前祛除签名参数
		}
		string sig = LiMiPlatform::GetSigStr(Param,sigkey);
		if(sig != deliverSig) {
			error_log("sig error:%s,deliverSig=%s,sig=%s", postdata.c_str(), deliverSig.c_str(), sig.c_str());
			responeQQBagMsg(false);
			return R_ERROR;
		}

		//----------签名通过
		//获取附加数据
		vector<string> userdata;
		SplitString(Param["attach"],userdata,"_");
		if(userdata.size() != 4){
			error_log("attach error:%s,deliverSig=%s,sig=%s", postdata.c_str(), deliverSig.c_str(), sig.c_str());
			responeQQBagMsg(false);
			return R_ERROR;
		}
		string openid = userdata[0];
		unsigned uid = CTrans::STOI(userdata[1].c_str());
		string itemid = userdata[2];
		int itemcnt = CTrans::STOI(userdata[3].c_str());

		//读取物品配置信息
		QQItemInfo itemInfo;
		ret = CLogicQQPay::GetItemInfo(itemid, itemInfo);
		if(ret) {
			error_log("item error:%s,deliverSig=%s,sig=%s", postdata.c_str(), deliverSig.c_str(), sig.c_str());
			responeQQBagMsg(false);
			return R_ERROR;
		}

		//获取订单信息
		unsigned cash = 0;
		string billno = Param["out_trade_no"];
		cash = itemInfo.cash * itemcnt;

		//------------加钻、充值记录处理
		ConfigManager::Instance()->SetServer(Config::GetZoneByUID(uid));
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
		payhis.channel = PT_LIMI;
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

		//商户处理后同步返回给QQ钱包
		responeQQBagMsg(f);

		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiLMQQDeliver)
