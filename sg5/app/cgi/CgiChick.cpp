/*
 * CgiChick.cpp
 *
 *  Created on: 2018年7月26日
 *      Author: Ralf
 */


#include "LogicInc.h"

class CCgiChick : public CCgiBase
{
public:
	CCgiChick() : CCgiBase("chick")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);

		int ret = CLogicChick::Init(CONFIG_CHICK_DATA, true);
		if(ret)
			exit(ret);
	}

	CGI_SIMPLE_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("GetChickReg", GetChickReg)
	CGI_SET_ACTION_MAP("ChickReg", ChickReg)
	CGI_ACTION_MAP_END

	~CCgiChick()
	{
		CLogicChick::Exit();
	}

	void ProcessSig(int sig)
	{
		CLogicChick::Sig(sig);
	}

	int GetChickReg()
	{
		unsigned uid = CCGIIn::GetCGIInt("uid");

		CLogicChick chick;
		int ret = chick.GetChickReg(uid, m_jsonResult);
		if (ret)
			return ret;

		CGI_SEND_LOG("action=GetChickReg&uid=%u", uid);
		return R_SUCCESS;
	}

	int ChickReg()
	{
		unsigned uid = CCGIIn::GetCGIInt("uid");
		string sdata = CCGIIn::GetCGIStr("data");
		Json::Value data;
		Json::Reader().parse(sdata, data);

		CLogicChick chick;
		int ret = chick.ChickReg(uid, data, m_jsonResult);
		if (ret)
			return ret;

		CGI_SEND_LOG("action=ChickReg&uid=%u", uid);
		return R_SUCCESS;
	}
};

CGI_MAIN(CCgiChick)





