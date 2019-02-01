/*
 * CgiLoad.cpp
 *
 *  Created on: 2011-6-1
 *      Author: dada
 */

#include "LogicInc.h"

class CCgiLoad : public CCgiBase
{

public:

	CCgiLoad() : CCgiBase("getbase")
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

	CGI_DIRECT_PROCESS(Load)

	int Load()
	{
		unsigned uid;
		if(!Json::GetUInt(m_data, "userid", uid))
		{
			return R_ERR_PARAM;
		}
		if(uid == 0)
		{
			uid = m_uid;
		}

		unsigned baseid;
		if(!Json::GetUInt(m_data, "baseid", baseid))
		{
			return R_ERR_PARAM;
		}

		string sType;
		if(!Json::GetString(m_data, "type", sType))
		{
			return R_ERR_PARAM;
		}
		LoadType type = LT_UNKNOW;
		static char s_loadTypes[][10] = { "build", "view", "help", "attack"};
		for(unsigned i = 0; i < COUNT_OF(s_loadTypes); i++)
		{
			if(sType.find(s_loadTypes[i]) != string::npos)
			{
				type = (LoadType)(LT_UNKNOW + i + 1);
				break;
			}
		}
		if(type == LT_UNKNOW)
		{
			error_log("[invalid load type][uid=%u,userid=%u,baseid=%u,type=%s]",
						m_uid, uid, baseid, sType.c_str());
			return R_ERR_PARAM;
		}


		CLogicArchive logicArchive;
		int result = logicArchive.Load(uid, baseid, m_uid, type, m_jsonResult);
		if(result != 0)
		{
			return result;
		}

		CGI_SEND_LOG("uid=%u&userid=%u&baseid=%u", m_uid, uid, baseid);
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiLoad)
