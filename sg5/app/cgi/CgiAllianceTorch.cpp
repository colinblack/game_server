/*
 * CgiAllianceTorch.cpp
 *
 *  Created on: 2016-05-18
 *      Author: zkw
 */


#include "LogicInc.h"

class CCgiAllianceTorch: public CCgiBase {
public:
	CCgiAllianceTorch() : CCgiBase("alliancetorch")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_GET_UID);
		SetFeature(CF_CHECK_SESSION);
		SetFeature(CF_CHECK_TIME);
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_CHECK_HASH);
		SetFeature(CF_CHECK_VERSION);
		SetFeature(CF_APPEND_HASH);
		SetFeature(CF_PARSE_DATA);
		SetFeature(CF_CRYPT_DATA);
		SetFeature(CF_DECRYPT_DATA);

		int ret = CLogicAllianceTorch::Init(CONFIG_ALLIANCE_TORCH_DATA, false);
		if(ret)
			exit(ret);
	}

	CGI_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("GetAllianceTorchCurrStatus", GetAllianceTorchCurrStatus)
	CGI_SET_ACTION_MAP("BurnAllianceTorch", 		 BurnAllianceTorch)
	CGI_SET_ACTION_MAP("GetAllianceTorchBuyLog",     GetAllianceTorchBuyLog)
	CGI_ACTION_MAP_END

	~CCgiAllianceTorch()
	{
		CLogicAllianceTorch::Exit();
	}

	void ProcessSig(int sig)
	{
		CLogicAllianceTorch::Sig(sig);
	}

	int GetAllianceTorchCurrStatus()
	{
		unsigned aid = 0;
		Json::GetUInt(m_data, "aid", aid);

		int ret = 0;
		CLogicAllianceTorch logicAllianceTorch;
		ret = logicAllianceTorch.GetAllianceTorchCurrStatus(aid, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=GetAllianceTorchCurrStatus&uid=%u", m_uid);
		return ret;
	}

	int BurnAllianceTorch()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		unsigned aid = 0, torch_type = 0;
		if(!Json::GetUInt(m_data, "aid", aid) || !Json::GetUInt(m_data, "torch_type", torch_type))
		{
			error_log("[burn_alliance_torch_param_error] [uid=%u]",m_uid);
			return R_ERR_PARAM;
		}
		if (torch_type > 2) // 0:红光火炬   1:黄光火炬   2:蓝光火炬
		{
			error_log("[param_torch_type_value_error] [uid=%u, torch_type=%u]",m_uid, torch_type);
			return R_ERR_PARAM;
		}

		int ret = 0;
		CLogicAllianceTorch logicAllianceTorch;
		ret = logicAllianceTorch.BurnAllianceTorch(aid, m_uid, torch_type, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=BurnAllianceTorch&uid=%u", m_uid);
		return ret;
	}

	int GetAllianceTorchBuyLog()
	{
		unsigned aid = 0;
		if(!Json::GetUInt(m_data, "aid", aid))
		{
			error_log("[GetAllianceTorchBuyLog para loss aid] [uid=%u]",m_uid);
			return R_ERR_PARAM;
		}

		int ret = 0;
		CLogicAllianceTorch logicAllianceTorch;
		ret = logicAllianceTorch.GetAllianceTorchBuyLog(aid, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=GetAllianceTorchBuyLog&uid=%u", m_uid);
		return ret;
	}
};

CGI_MAIN(CCgiAllianceTorch)
