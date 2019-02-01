/*
 * CgiNew4399Deliver.cpp
 *
 *  Created on: 2017-3-28
 *      Author: Ralf
 */



#include "Logic4399Pay.h"
#include "LogicInc.h"
#include "LogicCMD.h"

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

		CLogic4399Pay logicPay;
		int ret = logicPay.deliver(PayToUser, serverid, CTrans::STOI(PayGold), PayNum, (unsigned)(CTrans::STOF(PayRMB)*100));
		if (ret != 0)
		{
			CgiUtil::PrintText("-99");
			return ret;
		}

		//CgiUtil::PrintText("{\"ret\":0,\"msg\":\"OK\"}");防止回调过久移动到各平台虚函数
		CGI_SEND_LOG("openid=%s&billno=%s&serverid=%u&num=%s", PayToUser.c_str(),PayNum.c_str(),serverid,PayGold.c_str());
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiNew4399Deliver)



