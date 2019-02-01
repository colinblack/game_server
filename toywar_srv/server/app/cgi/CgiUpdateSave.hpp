/*
 * CgiUpdateSave.cpp
 *
 *  Created on: 2011-6-1
 *      Author: dada
 */

#include "LogicInc.h"

class CCgiUpdateSave : public CCgiBase
{

public:

	CCgiUpdateSave() : CCgiBase("refresh")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_GET_UID);
		SetFeature(CF_CHECK_SESSION);
		SetFeature(CF_CHECK_TIME);
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_CHECK_HASH);
		SetFeature(CF_APPEND_HASH);
		SetFeature(CF_PARSE_DATA);
		SetFeature(CF_CRYPT_DATA);
		SetFeature(CF_DECRYPT_DATA);
	}

	CGI_DIRECT_PROCESS(UpdateSave)

	int UpdateSave()
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
		SaveType type = ST_UNKNOW;
		static char s_saveTypes[][10] = { "build", "view", "help", "attack"};
		for(unsigned i = 0; i < COUNT_OF(s_saveTypes); i++)
		{
			if(sType.find(s_saveTypes[i]) != string::npos)
			{
				type = (SaveType)(ST_UNKNOW + i + 1);
				break;
			}
		}
		if(type == ST_UNKNOW)
		{
			error_log("[invalid updatesave type][uid=%u,userid=%u,baseid=%u,type=%s]",
						m_uid, uid, baseid, sType.c_str());
			return R_ERR_PARAM;
		}

		CLogicArchive logicArchive;
		int result = logicArchive.UpdateSave(uid, baseid, m_uid, type, m_jsonResult);
		if(result != 0)
		{
			return result;
		}

		CGI_SEND_LOG("uid=%u&userid=%u&baseid=%u", m_uid, uid, baseid);
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiUpdateSave)
