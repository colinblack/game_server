/*
 * CgiNew4399Deliver.cpp
 *
 *  Created on: 2017-3-28
 *      Author: Ralf
 */



#include "LogicInc.h"

class CCgiNew4399Deliver : public CCgiBase
{
public:
	CCgiNew4399Deliver() : CCgiBase("deliver4399")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(deliver)

	int deliver()
	{
		ConfigManager::Instance()->SetServer(0);

		if(m_ipstr.find("115.182.52.") == string::npos && m_ipstr != "113.107.149.212")
		{
			CgiUtil::PrintText("-6");
			PARAM_ERROR_RETURN_MSG("ip_error");
		}

		string p = CCGIIn::GetCGIStr("p");
		double charge = CCGIIn::GetCGIDbl("charge", 0, 100000000, 0, 0);
		unsigned serverid = CCGIIn::GetCGIInt("serverid");
		vector<string> rlt;
		String::Split(p, '|', rlt);
		if(rlt.size() < 7)
		{
			CgiUtil::PrintText("-1");
			PARAM_ERROR_RETURN_MSG("no_param");
		}

		string PayNum = rlt[0];
		string PayToUser = Crypt::UrlDecode(rlt[1]);
		string PayGold = rlt[2];
		string time = rlt[3];
		string flag = rlt[4];
		string PayRMB = rlt[5];
		string channel = rlt[6];
		string osig = PayNum + PayToUser + PayGold +PayRMB+ time + OpenPlatform::GetPlatform()->GetConfig(CONFIG_4399_PAY_KEY);
		string sig = Crypt::Md5Encode(osig);
		if(sig != flag)
		{
			CgiUtil::PrintText("-2");
			PARAM_ERROR_RETURN_MSG("flag_error");
		}

		if(CTrans::STOF(PayGold)/CTrans::STOF(PayRMB) > 20)
		{
			CgiUtil::PrintText("-5");
			PARAM_ERROR_RETURN_MSG("money_error");
		}

		string openid = PayToUser;
		unsigned cash = CTrans::STOI(PayGold);
		string order_id = PayNum;
		unsigned money = (unsigned)(CTrans::STOF(PayRMB)*100);

		unsigned uid = 0;
		CDataUserMapping dbUserMapping;
		int ret = dbUserMapping.GetMapping(openid, 0, uid);
		if(ret == R_ERR_NO_DATA)
		{
			CgiUtil::PrintText("-3");
			PARAM_ERROR_RETURN_MSG("no_user");
		}
		else if (ret != 0)
		{
			CgiUtil::PrintText("-99");
			PARAM_ERROR_RETURN_MSG("sys_error");
		}

		//防重发, 如果该payment_id已经处理, 那么不再增加钻石
		DataPayHistory payHistory;
		CDataPayHistory dbPayHistory;
		ret = dbPayHistory.GetPayHistory(uid, OpenPlatform::GetType(), order_id, payHistory);
		if(ret == 0)
		{
			CgiUtil::PrintText("2");
			PARAM_ERROR_RETURN_MSG("order_error");
		}

		CSG17Packet packet;
		packet.cmd = PROTOCOL_DELIVER;
		Common::Pay* msg = new Common::Pay;
		msg->set_uid(uid);
		msg->set_cash(cash);
		msg->set_ts(Time::GetGlobalTime());
		packet.m_msg = msg;

		ret = BattleSocket::Send(Config::GetZoneByUID(uid), &packet);
		if(ret)
		{
			CgiUtil::PrintText("-99");
			PARAM_ERROR_RETURN_MSG("sys_error");
		}

		CSG17Packet reply;
		ret = BattleSocket::Receive(Config::GetZoneByUID(uid), &reply);
		if(ret)
		{
			CgiUtil::PrintText("-99");
			PARAM_ERROR_RETURN_MSG("sys_error");
		}

		Common::ReplyPay* rmsg = (Common::ReplyPay*)reply.m_msg;
		ret = rmsg->ret();
		if(ret)
		{
			CgiUtil::PrintText("-99");
			PARAM_ERROR_RETURN_MSG("sys_error");
		}

		DataPayHistory payhis;
		payhis.channel = OpenPlatform::GetType();
		payhis.channel_pay_id = order_id;
		payhis.count = cash;
		payhis.credit = money;
		payhis.status = PST_OK;
		payhis.type = 0;
		payhis.uid = uid;
		payhis.open_id = openid;
		CLogicQQPay logicPay;
		ret = logicPay.AddPayHistory(payhis);
		if (ret != 0)
		{
			error_log("[AddPayHistory fail][ret=%d,openid=%s,order_id=%s]",
					ret,openid.c_str(),order_id.c_str());
		}

		CgiUtil::PrintText("1");
		CGI_SEND_LOG("openid=%s&billno=%s&serverid=%u&num=%s", PayToUser.c_str(),PayNum.c_str(),serverid,PayGold.c_str());
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiNew4399Deliver)

