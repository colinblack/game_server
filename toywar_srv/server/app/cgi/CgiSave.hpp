/*
 * CgiXSave.cpp
 *
 *  Created on: 2011-6-1
 *      Author: dada
 */

#include "LogicInc.h"

class CCgiSave : public CCgiBase
{

public:

	CCgiSave() : CCgiBase("setbase")
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

	CGI_DIRECT_PROCESS(Save)

	int Save()
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

		CLogicArchive logicArchive;
		int result = logicArchive.Save(uid, baseid, m_uid, m_data, m_jsonResult);
		if(result != 0)
		{
			return result;
		}

		CGI_SEND_LOG("uid=%u&userid=%u&baseid=%u", m_uid, uid, baseid);
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiSave)
