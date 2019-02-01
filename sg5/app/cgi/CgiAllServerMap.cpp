/*
 * CgiAllServerMap.cpp
 *
 *  Created on: 2015-9-15
 *      Author: Ralf
 */

#include "LogicInc.h"


class CCgiAllServerMap : public CCgiBase
{

public:

	CCgiAllServerMap() : CCgiBase("allservermap")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);

		int ret = CLogicAllServerMap::Init(CONFIG_ALL_SERVER_MAP_PATH, true);
		if(ret)
			exit(ret);
	}

	CGI_SIMPLE_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("get", Get)
	CGI_SET_ACTION_MAP("set", Set)
	CGI_ACTION_MAP_END

	~CCgiAllServerMap()
	{
		CLogicAllServerMap::Exit();
	}

	void ProcessSig(int sig)
	{
		CLogicAllServerMap::Sig(sig);
	}

	int Get()
	{
		unsigned level = CCGIIn::GetCGIInt("level");
		unsigned count = CCGIIn::GetCGIInt("count");

		CLogicAllServerMap logicAllServerMap;
		logicAllServerMap.ReplyGet(level, count, m_jsonResult["map"]);

		CGI_SEND_LOG("action=get&level=%u", level);
		return R_SUCCESS;
	}

	int Set()
	{
		string data = CCGIIn::GetCGIStr("data");
		Json::Value jsonData;
		Json::Reader reader;
		if(!reader.parse(data,jsonData))
			return R_ERR_PARAM;

		CLogicAllServerMap logicAllServerMap;
		logicAllServerMap.ReplySyn(jsonData);

		CGI_SEND_LOG("action=set");
		return R_SUCCESS;
	}
};

CGI_MAIN(CCgiAllServerMap)

