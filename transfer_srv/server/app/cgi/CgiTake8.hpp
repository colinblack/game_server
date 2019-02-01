#include "LogicInc.h"
#include "LogicTake8.h"

class CCgiTake8 : public CCgiBase
{
public:
	CCgiTake8() : CCgiBase("take8")
	{
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_DIRECT_PROCESS(ProcessOrder)

	int ProcessOrder()
	{
		const string gameId = CCGIIn::GetCGIStr("GameID");
		const string orderId = CCGIIn::GetCGIStr("OrderID");
		const string fbuid = CCGIIn::GetCGIStr("UID");
		int amt = CCGIIn::GetCGIInt("Amount");
		const string vcode = CCGIIn::GetCGIStr("VCode");

		if (gameId.empty() || orderId.empty() || fbuid.empty() || vcode.empty())
		{
			error_log("[param error][gameId=%s,orderId=%s,fbuid=%s,vcode=%s]",
					gameId.c_str(),orderId.c_str(),fbuid.c_str(),vcode.c_str());

			CgiUtil::PrintText("0004");
			return R_ERR_PARAM;
		}

		CLogicTake8 take8;
		int ret = take8.ProcessOrder(gameId, orderId, fbuid, amt, vcode);
		if (ret != 0)
		{
			CgiUtil::PrintText(take8.m_outMsg);
			return ret;
		}

		CGI_SEND_LOG("orderId=%s&fbuid=%s&amt=%d",
				orderId.c_str(),fbuid.c_str(),amt);
		CgiUtil::PrintText("0000");
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiTake8)
