/*
 * CgiCrowdFunding.cpp
 *
 *  Created on: 2016-1-25
 *      Author: Ralf
 */



#include "LogicInc.h"

class CCgiCrowdFunding: public CCgiBase {
public:

	CCgiCrowdFunding() : CCgiBase("crowdfunding")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);

		int ret = CLogicCrowdFunding::Init(CONFIG_CROWD_FUNDING_DATA_PATH, true);
		if(ret)
			exit(ret);
	}

	CGI_SIMPLE_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("Get", Get)
	CGI_SET_ACTION_MAP("Buy", Buy)
	CGI_ACTION_MAP_END

	~CCgiCrowdFunding()
	{
		CLogicCrowdFunding::Exit();
	}

	void ProcessSig(int sig)
	{
		CLogicCrowdFunding::Sig(sig);
	}

	int Get()
	{
		unsigned uid = CCGIIn::GetCGIInt("uid");

		int ret = 0;
		CLogicCrowdFunding logicCrowdFunding;
		ret = logicCrowdFunding._Get(uid, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=Get&uid=%u", uid);
		return ret;
	}

	int Buy()
	{
		unsigned uid = CCGIIn::GetCGIInt("uid");
		unsigned id = CCGIIn::GetCGIInt("id");
		unsigned need = CCGIIn::GetCGIInt("need");

		int ret = 0;
		CLogicCrowdFunding logicCrowdFunding;
		ret = logicCrowdFunding._Buy(uid, id, need, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=Buy&uid=%u", uid);
		return ret;
	}

};

CGI_MAIN(CCgiCrowdFunding)


