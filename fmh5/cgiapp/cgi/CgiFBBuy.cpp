#include "LogicInc.h"
#include "LogicQQPay.h"

class CCgiFBBuy : public CCgiBase
{
public:
	CCgiFBBuy() : CCgiBase("fbbuy")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(buy)

	void ReplaceStr(string & strsrc)
	{
		int n_pos = 0;
		while( (n_pos=strsrc.find("-",n_pos)) != std::string::npos )
		{
			strsrc.replace( n_pos,1, "+" );
			n_pos += 1;
		}
		n_pos = 0;
		while( (n_pos=strsrc.find("_",n_pos)) != std::string::npos )
		{
			strsrc.replace( n_pos,1, "/" );
			n_pos += 1;
		}
	}

	int SignCheck(string signedRequest,string & part2Str)
	{
		//1.按'.' 将字符串分割成两份,存储在vector中
		vector<string>part;
		part.clear();
		unsigned pos = 0;
		string flag = ".";
		string var_openkey = signedRequest;
		pos = var_openkey.find(flag);
		if(string::npos != pos)
		{
			part.push_back(var_openkey.substr(0, pos));
			part.push_back(var_openkey.substr(pos + 1,var_openkey.length()));
		}
		else
		{
			error_log("signedRequest_param_error.signedRequest=%s",signedRequest.c_str());
			return -1;
		}

		//2.使用BASE64解码第一部分 得到签名
		string sig;
		string strsrc = part[0];
		ReplaceStr(strsrc);
		Crypt::Base64Decode(sig,strsrc);
		debug_log("strsrc=%s",strsrc.c_str());

		//2.使用 HMAC SHA-256 根据 secret key 加密第二部分，检验是否等于签名
		string sig2;
		string appkey  = OpenPlatform::GetPlatform()->GetConfig("appkey");//签名key
		sig2 = Crypt::HmacSha256(part[1],appkey);

		if(sig != sig2)
		{
			error_log("[sig_check_error],sig=%s,sig2=%s",sig.c_str(),sig2.c_str());
			return -1;
		}

		part2Str = part[1];
		return 0;
	}

	int buy()
	{
		const string openid = CCGIIn::GetCGIStr("openid");
		string itemnum  = CCGIIn::GetCGIStr("itemnum");
		const string developerPayload = CCGIIn::GetCGIStr("developerPayload");
		const string paymentID  = CCGIIn::GetCGIStr("paymentID");
		const string productID  = CCGIIn::GetCGIStr("productID");
		const string purchaseTime  = CCGIIn::GetCGIStr("purchaseTime");
		const string purchaseToken  = CCGIIn::GetCGIStr("purchaseToken");
		string signedRequest = CCGIIn::GetCGIStr("signedRequest");

		//1************************校验签名
		string part2Str;
		int ret = SignCheck(signedRequest,part2Str);
		if(ret != 0)
		{
			ERROR_RETURN_MSG(R_ERROR,"sign_check_error");
		}
		//2************************使用BASE64解码第二部分得到一个JSON字符串,并校验
		string jsonStr;
		ReplaceStr(part2Str);
		Crypt::Base64Decode(jsonStr,part2Str);
		Json::Value value;
		Json::Reader reader;
		if( !reader.parse( jsonStr, value ) )
		{
			error_log("[json_data_error].%s",jsonStr.c_str());
			ERROR_RETURN_MSG(R_ERROR,"json_data_error");
		}


		string developer_payload;
		string payment_id;//订单号
		string product_id;
		unsigned purchase_time;
		string purchase_token;
		bool f1,f2,f3,f4,f5;
		f1 = Json::GetString(value,"payment_id",payment_id);
		f2 = Json::GetUInt(value,"purchase_time",purchase_time);
		f3 = Json::GetString(value,"product_id",product_id);
		f4 = Json::GetString(value,"developer_payload",developer_payload);
		f5 = Json::GetString(value,"purchase_token",purchase_token);
		if(!f1 || !f2 || !f3 || !f4 || !f5)
		{
			error_log("[data_parse_failed][f1=%d,f2=%d,%f3=%d,f4=%d,f5=%d]",f1,f2,f3,f4,f5);
			ERROR_RETURN_MSG(R_ERROR,"data_parse_failed");
		}
		if(developer_payload != openid ||
			purchase_time !=  CTrans::STOI(purchaseTime) ||
			purchase_token != purchaseToken ||
			payment_id != paymentID ||
			product_id != productID)
		{
			error_log("[data_check_failed][developer_payload=%s,openid=%s,purchase_time=%u,purchaseTime=%s,purchase_token=%s,purchaseToken=%s,payment_id=%s,paymentID=%s,product_id=%s,productID=%s]",
					   developer_payload.c_str(),openid.c_str(),purchase_time,purchaseTime.c_str(),purchase_token.c_str(),purchaseToken.c_str(),payment_id.c_str(),paymentID.c_str(),product_id.c_str(),productID.c_str());
			ERROR_RETURN_MSG(R_ERROR,"data_check_failed");
		}

		//3************************校验数据是否合法
		unsigned uid = 0;
		ret = CDataUserMapping().GetMapping(openid, 0, uid);
		if(ret)
		{
			PARAM_ERROR_RETURN_MSG("no_uid");
		}

		QQItemInfo itemInfo;
		ret = CLogicQQPay::GetItemInfo(product_id, itemInfo);
		if(ret)
		{
			PARAM_ERROR_RETURN_MSG("itemid_error");
		}
		unsigned cash = 0, cost = 0,totalfee;
		cash = itemInfo.cash * CTrans::STOI(itemnum);
		cost = cash;
		totalfee = itemInfo.price * CTrans::STOI(itemnum);

		//4************************查询订单是否存在
		DataPayHistory payHistory;
		CDataPayHistory dbPayHistory;
		string billno = payment_id;
		ret = dbPayHistory.GetPayHistory(uid, PT_FB, billno,payHistory);
		if(ret == 0 && payHistory.status == PST_OK)
		{
			//订单已充值,直接返回
			m_jsonResult["token"] = purchase_token;
			return R_SUCCESS;
		}


		CSG17Packet packet;
		packet.cmd = PROTOCOL_DELIVER;
		Common::Pay* msg = new Common::Pay;
		msg->set_uid(uid);
		msg->set_cash(cash);
		msg->set_itemid(CTrans::STOI(product_id));
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

		if(f)
		{
			DataPayHistory payhis;
			payhis.channel = PT_FB;
			payhis.channel_pay_id = payment_id;
			payhis.count = cash;
			payhis.credit = cost;
			payhis.status = PST_OK;
			payhis.type = itemInfo.type;
			payhis.uid = uid;
			payhis.open_id = openid;
			ret = CLogicQQPay().AddPayHistory(payhis);
			CGI_SEND_LOG("openid=%s&billno=%s&cash=%u&cost=%u&itemids=%s&itemnums=%s&uid=%u&ret=%d",
					openid.c_str(),product_id.c_str(),cash,cost,product_id.c_str(),itemnum.c_str(),uid,ret);
			m_jsonResult["token"] = purchase_token;
			return R_SUCCESS;
		}
		else
		{
			ERROR_RETURN_MSG(R_ERROR,"charge_failed");
		}
	}


};

CGI_MAIN(CCgiFBBuy)
