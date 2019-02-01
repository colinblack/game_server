/*
 * CgiNewWorldAllianceMap.cpp
 *
 *  Created on: 2015-12-21
 *      Author: Ralf
 */


#include "LogicInc.h"

class CCgiNewWorldAllianceMap: public CCgiBase {
public:
	CCgiNewWorldAllianceMap() : CCgiBase("newworldalliancemap")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_GET_UID);
		SetFeature(CF_CHECK_TIME);
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_CHECK_HASH);
		SetFeature(CF_CHECK_VERSION);
		SetFeature(CF_APPEND_HASH);
		SetFeature(CF_PARSE_DATA);
		SetFeature(CF_CRYPT_DATA);
		SetFeature(CF_DECRYPT_DATA);
		SetFeature(CF_COMPRESS_OUT);

		int ret = CLogicNewWorldAllianceMap::Init(CONFIG_NEW_WORLD_ALLIANCE_MAP_DATA, true);
		if(ret)
			exit(ret);
	}

	CGI_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("GetRoom", GetRoom)
	CGI_ACTION_MAP_END

	~CCgiNewWorldAllianceMap()
	{
		CLogicNewWorldAllianceMap::Exit();
	}

	void ProcessSig(int sig)
	{
		CLogicNewWorldAllianceMap::Sig(sig);
	}

	int GetRoom()
	{
		unsigned aid = 0;
		if(!Json::GetUInt(m_data, "aid", aid))
			return R_ERR_PARAM;

		int ret = 0;
		CLogicNewWorldAllianceMap logicNewWorldAllianceMap;
		ret = logicNewWorldAllianceMap.GetRoom(aid, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=GetRoom&uid=%u", m_uid);
		return ret;
	}
};

CGI_MAIN(CCgiNewWorldAllianceMap)
