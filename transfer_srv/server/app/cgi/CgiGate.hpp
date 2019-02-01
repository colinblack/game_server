/*
 * CgiGate.cpp
 *
 *  Created on: 2011-7-13
 *      Author: auto
 */

#include "LogicInc.h"

class CCgiGate : public CCgiBase
{

public:

	CCgiGate() : CCgiBase("gate")
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
	}

	CGI_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("addtimes", AddTimes)
	CGI_SET_ACTION_MAP("getgaterank", GetGateRank)
	CGI_SET_ACTION_MAP("getgates", GetGateDatas)
	CGI_SET_ACTION_MAP("beginGate", BeginGate)
	CGI_SET_ACTION_MAP("updateGating", UpdateGating)
	CGI_SET_ACTION_MAP("endGate", EndGate)
	CGI_SET_ACTION_MAP("restartGate", RestartGate)
	CGI_SET_ACTION_MAP("resetStatus", ResetStatus)
	CGI_SET_ACTION_MAP("activeNewLevel", ActiveNewLevel)
	CGI_ACTION_MAP_END


	int ActiveNewLevel()
	{
		int ret = 0;
		CLogicGate logic;
		int level;
		if(!Json::GetInt(m_data, "level", level))
		{
			return R_ERR_PARAM;
		}

		int buildingLevel;
		if(!Json::GetInt(m_data, "buildingLevel", buildingLevel))
		{
			return R_ERR_PARAM;
		}

		DataGate data;


		ret = logic.ActiveNewLevel(m_uid, level, buildingLevel, data);
		if (ret != 0)
		{
			return ret;
		}

		Json::Value gateResult;
		CLogicGate::GetGateJson(data, gateResult);
		m_jsonResult["gate"] = gateResult;
		m_jsonResult["level"] = level;
		m_jsonResult["error"] = 0;
		m_jsonResult["currenttime"] = Time::GetGlobalTime();
		// m_jsonResult["h"] = "c108bdf7aa78248efe7a191141dd993f";
		// m_jsonResult["hn"] = 8071936;

		CGI_SEND_LOG("uid=%u", m_uid);

		return R_SUCCESS;
	}

	int ResetStatus()
	{
		int ret = 0;
		CLogicGate logic;
		int level;
		if(!Json::GetInt(m_data, "level", level))
		{
			return R_ERR_PARAM;
		}

		ret = logic.ResetStatus(m_uid, level);
		if (ret != 0)
		{
			return ret;
		}
		m_jsonResult["level"] = level;
		m_jsonResult["error"] = 0;
		m_jsonResult["currenttime"] = Time::GetGlobalTime();
		// m_jsonResult["h"] = "c108bdf7aa78248efe7a191141dd993f";
		// m_jsonResult["hn"] = 8071936;

		CGI_SEND_LOG("uid=%u", m_uid);

		return R_SUCCESS;
	}

	int AddTimes()
	{
		int ret = 0;
		CLogicGate logic;
		int timeleft = 0;
		int usecach = 0;
		ret = logic.AddTimes(m_uid, timeleft, usecach);
		if (ret != 0)
		{
			return ret;
		}

		m_jsonResult["usecach"] = usecach;
		m_jsonResult["timeleft"] = timeleft;
		m_jsonResult["error"] = 0;
		m_jsonResult["currenttime"] = Time::GetGlobalTime();
		// m_jsonResult["h"] = "c108bdf7aa78248efe7a191141dd993f";
		// m_jsonResult["hn"] = 8071936;

		CGI_SEND_LOG("uid=%u&lefttime=%d&usecach=%d", m_uid, timeleft, usecach);

		return R_SUCCESS;
	}

	int GetGateRank()
	{
		int level;
		if(!Json::GetInt(m_data, "level", level))
		{
			return R_ERR_PARAM;
		}
		int ret = 0;
		CLogicGate logic;
		vector<DataRank> gates;
		ret = logic.GetGateRank(m_uid, level, gates);
		if (ret != 0)
		{
			return ret;
		}

		Json::Value gatesResult;
		gatesResult.resize(gates.size());

		vector<DataRank>::iterator iterbegin = gates.begin();
		vector<DataRank>::iterator iterend = gates.end();
		vector<DataRank>::iterator iter = iterbegin;
		int index= 0;
		for (; iter != iterend; iter++)
		{
			index = iter - iterbegin;
			CLogicGate::GetGateRankJson(gates[index], gatesResult[index]);
		}

		m_jsonResult["gates"] = gatesResult;
		m_jsonResult["level"] = level;
		m_jsonResult["error"] = 0;
		m_jsonResult["currenttime"] = Time::GetGlobalTime();
		// m_jsonResult["h"] = "c108bdf7aa78248efe7a191141dd993f";
		// m_jsonResult["hn"] = 8071936;

		CGI_SEND_LOG("uid=%u&gates=%d", m_uid, gates.size());

		return R_SUCCESS;
	}

	int GetGateDatas()
	{
		int ret = 0;
		CLogicGate logic;
		vector<DataGate> gates;
		ret = logic.GetGates(m_uid, gates);
		if (ret != 0)
		{
			return ret;
		}

		Json::Value gatesResult;
		gatesResult.resize(gates.size());

		vector<DataGate>::iterator iterbegin = gates.begin();
		vector<DataGate>::iterator iterend = gates.end();
		vector<DataGate>::iterator iter = iterbegin;
		int index= 0;
		for (; iter != iterend; iter++)
		{
			index = iter - iterbegin;
			CLogicGate::GetGateJson(gates[index], gatesResult[index]);
		}

		m_jsonResult["gates"] = gatesResult;
		m_jsonResult["error"] = 0;
		m_jsonResult["currenttime"] = Time::GetGlobalTime();
		// m_jsonResult["h"] = "c108bdf7aa78248efe7a191141dd993f";
		// m_jsonResult["hn"] = 8071936;

		CGI_SEND_LOG("uid=%u&gates=%d", m_uid, gates.size());

		return R_SUCCESS;
	}

	int BeginGate()
	{
		int ret = 0;
		int level;
		if(!Json::GetInt(m_data, "level", level))
		{
			return R_ERR_PARAM;
		}
		int timeleft = 0;
		CLogicGate logic;
		DataGate data;
		ret = logic.BeginGate(m_uid, level, data, timeleft);

		if (ret != 0)
		{
			return ret;
		}

		Json::Value gateResult;
		CLogicGate::GetGateJson(data, gateResult);
		m_jsonResult["gate"] = gateResult;
		m_jsonResult["timeleft"] = timeleft;
		m_jsonResult["error"] = 0;
		m_jsonResult["currenttime"] = Time::GetGlobalTime();
		// m_jsonResult["h"] = "c108bdf7aa78248efe7a191141dd993f";
		// m_jsonResult["hn"] = 8071936;

		CGI_SEND_LOG("uid=%u", m_uid);

		return R_SUCCESS;
	}

	int UpdateGating()
	{
		int ret = 0;
		int level;
		if(!Json::GetInt(m_data, "level", level))
		{
			return R_ERR_PARAM;
		}
		int useTime;
		if(!Json::GetInt(m_data, "useTime", useTime))
		{
			return R_ERR_PARAM;
		}
		int useResource;
		if(!Json::GetInt(m_data, "useResource", useResource))
		{
			return R_ERR_PARAM;
		}

		CLogicGate logic;
		DataGate data;
		ret = logic.UpdateGating(m_uid, level, useTime, useResource, data);

		if (ret != 0)
		{
			return ret;
		}

		Json::Value gateResult;
		CLogicGate::GetGateJson(data, gateResult);
		m_jsonResult["gate"] = gateResult;
		m_jsonResult["error"] = 0;
		m_jsonResult["currenttime"] = Time::GetGlobalTime();
		// m_jsonResult["h"] = "c108bdf7aa78248efe7a191141dd993f";
		// m_jsonResult["hn"] = 8071936;

		CGI_SEND_LOG("uid=%u", m_uid);
		return R_SUCCESS;
	}

	int EndGate()
	{
		int ret = 0;
		int level;
		if(!Json::GetInt(m_data, "level", level))
		{
			return R_ERR_PARAM;
		}
		int useTime;
		if(!Json::GetInt(m_data, "useTime", useTime))
		{
			return R_ERR_PARAM;
		}
		int useResource;
		if(!Json::GetInt(m_data, "useResource", useResource))
		{
			return R_ERR_PARAM;
		}
		int iswin;
		if(!Json::GetInt(m_data, "iswin", iswin))
		{
			return R_ERR_PARAM;
		}

		int buildingLevel;
		if(!Json::GetInt(m_data, "buildingLevel", buildingLevel))
		{
			buildingLevel = 1;
			// return R_ERR_PARAM;
		}

		int hasNewGate = 0;

		CLogicGate logic;
		DataGate data;
		DataGate newgate;
		CLogicGate::GataConfig reward;

		ret = logic.EndGate(m_uid, level, useTime, useResource, iswin, data, hasNewGate, newgate, reward, buildingLevel);

		if (ret != 0)
		{
			return ret;
		}

		Json::Value gateResult;
		Json::Value newgateResult;
		Json::Value rewardResult;
		CLogicGate::GetGateJson(data, gateResult);
		if (hasNewGate != 0)
		{
			CLogicGate::GetGateJson(newgate, newgateResult);
			m_jsonResult["newgate"] = newgateResult;
		}
		CLogicGate::GetRewardJson(reward, rewardResult);

		m_jsonResult["reward"] = rewardResult;
		m_jsonResult["gate"] = gateResult;
		m_jsonResult["iswin"] = iswin;
		m_jsonResult["hasNewGate"] = hasNewGate;
		m_jsonResult["error"] = 0;
		m_jsonResult["currenttime"] = Time::GetGlobalTime();
		// m_jsonResult["h"] = "c108bdf7aa78248efe7a191141dd993f";
		// m_jsonResult["hn"] = 8071936;
		CGI_SEND_LOG("uid=%u", m_uid);
		return R_SUCCESS;
	}

	int RestartGate()
	{
		int level;
		if(!Json::GetInt(m_data, "level", level))
		{
			return R_ERR_PARAM;
		}
		CLogicGate logic;
		DataGate data;

		int ret = 0;
		ret = logic.RestartGate(m_uid, level, data);

		if (ret != 0)
		{
			return ret;
		}

		Json::Value gateResult;
		CLogicGate::GetGateJson(data, gateResult);
		m_jsonResult["gate"] = gateResult;
		m_jsonResult["error"] = 0;
		m_jsonResult["currenttime"] = Time::GetGlobalTime();
		// m_jsonResult["h"] = "c108bdf7aa78248efe7a191141dd993f";
		// m_jsonResult["hn"] = 8071936;
		CGI_SEND_LOG("uid=%u", m_uid);
		return R_SUCCESS;
	}
};

CGI_MAIN(CCgiGate)
