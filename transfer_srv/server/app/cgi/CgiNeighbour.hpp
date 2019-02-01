/*
 * CgiNeighbour.cpp
 *
 *  Created on: 2011-6-9
 *      Author: dada
 */

#include "LogicInc.h"

class CCgiNeighbour : public CCgiBase
{

public:

	CCgiNeighbour() : CCgiBase("neighbour")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_GET_UID);
		SetFeature(CF_CHECK_SESSION);
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_CHECK_HASH);
		SetFeature(CF_APPEND_HASH);
		SetFeature(CF_PARSE_DATA);
		SetFeature(CF_CRYPT_DATA);
		SetFeature(CF_DECRYPT_DATA);
		SetFeature(CF_COMPRESS_OUT);
	}

	CGI_DIRECT_PROCESS(GetNeighbour)

	int GetNeighbour()
	{
		CLogicMap logicMap;
		Json::Value neighbours;
		int result = logicMap.GetMapUsersJson(m_uid, OpenPlatform::GetType(), neighbours);
		if(result != 0)
		{
			return result;
		}

		m_jsonResult["bases"] = neighbours;
		m_jsonResult["currenttime"] = Time::GetGlobalTime();

		CGI_SEND_LOG("uid=%u&platform=%d&neighbours=%d", m_uid, OpenPlatform::GetType(), neighbours.size());
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiNeighbour)
