/*
 * CgiBaiduReport.cpp
 *
 *  Created on: 2015-12-14
 *      Author: dawx5fsd
 */

#include "LogicInc.h"
#include "LogicBaiduReport.h"


class CCgiBaiduReport : public CCgiBase
{
public:
	CCgiBaiduReport() : CCgiBase("baidureport")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_APPEND_HASH);
		SetFeature(CF_CRYPT_DATA);
		SetFeature(CF_DECRYPT_DATA);
	}

	CGI_DIRECT_PROCESS(BaiduReport)

	int BaiduReport()
	{
		unsigned uid;
		string action;

		uid = CCGIIn::GetCGIUin("uid");
		action = CCGIIn::GetCGIStr("action");


		if (action.empty())
		{
			error_log("[baidu report][action is empty]");
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicBaiduReport logicBaiduRep;

		int ret = logicBaiduRep.Report(uid, action);
		if (ret)
		{
			// 防止前台掉线
			return 0;
		}

		CGI_SEND_LOG("uid=%u&action=%s", uid,action.c_str());

		return R_SUCCESS;
	}

};


CGI_MAIN(CCgiBaiduReport)
