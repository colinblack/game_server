/*
 * CgiMVP.cpp
 *
 *  Created on: 2017-08-03
 *      Author: Ralf
 */

#include "LogicInc.h"

class CCgiMVP : public CCgiBase
{
public:
	CCgiMVP() : CCgiBase("MVP")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);

		int ret = CLogicMVP::Init(CONFIG_MVP_DATA, true);
		if(ret)
			exit(ret);
	}

	CGI_SIMPLE_ACTION_MAP_BEGIN

	CGI_SET_ACTION_MAP("GetAllServerMVP", GetAllServerMVP)
	CGI_SET_ACTION_MAP("StartAllServerMVP", StartAllServerMVP)
	CGI_SET_ACTION_MAP("EndAllServerMVP", EndAllServerMVP)
	CGI_SET_ACTION_MAP("SetAllServerMVP", SetAllServerMVP)
	CGI_SET_ACTION_MAP("StartAllServerBattleMVP", StartAllServerBattleMVP)
	CGI_SET_ACTION_MAP("EndAllServerBattleMVP", EndAllServerBattleMVP)
	CGI_SET_ACTION_MAP("EndAllServerNewWorldFightMVP", EndAllServerNewWorldFightMVP)
	CGI_ACTION_MAP_END

	~CCgiMVP()
	{
		CLogicMVP::Exit();
	}

	void ProcessSig(int sig)
	{
		CLogicMVP::Sig(sig);
	}

	int GetAllServerMVP()
	{
		CLogicMVP logicgroup;
		int ret = logicgroup.GetAllServerMVP(m_jsonResult);
		if (ret)
			return ret;

		CGI_SEND_LOG("action=GetAllServerMVP");
		return R_SUCCESS;
	}

	int StartAllServerMVP()
	{
		unsigned rank = CCGIIn::GetCGIInt("rank");
		unsigned uid = CCGIIn::GetCGIInt("uid");

		CLogicMVP logicgroup;
		int ret = logicgroup.StartAllServerMVP(rank, uid);
		if (ret)
			return ret;

		CGI_SEND_LOG("action=StartAllServerMVP&rank=%u&uid=%u", rank, uid);
		return R_SUCCESS;
	}

	int EndAllServerMVP()
	{
		unsigned rank = CCGIIn::GetCGIInt("rank");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		unsigned win = CCGIIn::GetCGIInt("win");
		string sdata = CCGIIn::GetCGIStr("data");
		Json::Value data;
		Json::Reader().parse(sdata, data);

		CLogicMVP logicgroup;
		int ret = logicgroup.EndAllServerMVP(rank, uid, win!=0, data);
		if (ret)
			return ret;

		CGI_SEND_LOG("action=EndAllServerMVP&rank=%u&uid=%u&win=%u", rank, uid, win);
		return R_SUCCESS;
	}

	int SetAllServerMVP()
	{
		unsigned uid = CCGIIn::GetCGIInt("uid");
		string sign = CCGIIn::GetCGIStr("sign");

		CLogicMVP logicgroup;
		int ret = logicgroup.SetAllServerMVP(uid, sign);
		if (ret)
			return ret;

		CGI_SEND_LOG("action=SetAllServerMVP&uid=%u", uid);
		return R_SUCCESS;
	}

	int StartAllServerBattleMVP()
	{
		unsigned rank = CCGIIn::GetCGIInt("rank");
		unsigned uid = CCGIIn::GetCGIInt("uid");

		CLogicMVP logicgroup;
		int ret = logicgroup.StartAllServerBattleMVP(rank, uid);
		if (ret)
			return ret;

		CGI_SEND_LOG("action=StartAllServerBattleMVP&rank=%u&uid=%u", rank, uid);
		return R_SUCCESS;
	}

	int EndAllServerBattleMVP()
	{
		unsigned rank = CCGIIn::GetCGIInt("rank");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		unsigned win = CCGIIn::GetCGIInt("win");
		string sdata = CCGIIn::GetCGIStr("data");
		Json::Value data;
		Json::Reader().parse(sdata, data);

		CLogicMVP logicgroup;
		int ret = logicgroup.EndAllServerBattleMVP(rank, uid, win!=0, data);
		if (ret)
			return ret;

		CGI_SEND_LOG("action=EndAllServerBattleMVP&rank=%u&uid=%u&win=%u", rank, uid, win);
		return R_SUCCESS;
	}

	int EndAllServerNewWorldFightMVP()
	{
		unsigned rank = CCGIIn::GetCGIInt("rank");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		unsigned win = CCGIIn::GetCGIInt("win");
		string sdata = CCGIIn::GetCGIStr("data");
		Json::Value data;
		Json::Reader().parse(sdata, data);

		CLogicMVP logicgroup;
		int ret = logicgroup.EndAllServerNewWorldFightMVP(rank, uid, win!=0, data);
		if (ret)
			return ret;

		CGI_SEND_LOG("action=EndAllServerNewWorldFightMVP&rank=%u&uid=%u&win=%u", rank, uid, win);
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiMVP)


