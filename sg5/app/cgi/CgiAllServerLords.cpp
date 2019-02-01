/*
 * CgiAllServerLords.cpp
 *
 *  Created on: 2016-7-7
 *      Author: dawx62fac
 */

#include "LogicInc.h"

class CgiAllServerLords : public CCgiBase
{
public:
	CgiAllServerLords() : CCgiBase("allserverlords")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);

		int ret = CLogicAllServerLordsList::Init(CONFIG_ALL_SERVER_LORDS_PATH, true);
		if(ret)
			exit(ret);
	}

	CGI_SIMPLE_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("Sync", Sync)		//同步排行榜数据
	//CGI_SET_ACTION_MAP("Establish", Establish) //确立尊主
	CGI_SET_ACTION_MAP("CloseWorship", CloseWorship) //停止膜拜
	CGI_SET_ACTION_MAP("Worship", Worship) //膜拜
	CGI_SET_ACTION_MAP("GetAllLords", GetAllLords) //获取所有的尊主
	CGI_SET_ACTION_MAP("GetRanksList", GetRanksList) //获取排行榜
	CGI_ACTION_MAP_END

	~CgiAllServerLords()
	{
		CLogicAllServerLordsList::Exit();
	}

	void ProcessSig(int sig)
	{
		CLogicAllServerLordsList::Sig(sig);
	}

	int Sync()
	{
		string data = CCGIIn::GetCGIStr("data");
		Json::Value jsonData;
		Json::Reader reader;
		if(!reader.parse(data, jsonData))
		{
			return R_ERR_PARAM;
		}

		if (! jsonData.isMember("type") || !jsonData.isMember("data"))
		{
			return R_ERR_PARAM;
		}

		CLogicAllServerLordsList logicLordsList;
		int ret = logicLordsList.Sync(jsonData["type"].asInt(), jsonData["data"]);
		if (ret != R_SUCCESS) return ret;

		CGI_SEND_LOG("action=Sync");

		return R_SUCCESS;
	}

#if 0
	int Establish()
	{
		string data = CCGIIn::GetCGIStr("data");
		Json::Value jsonData;
		Json::Reader reader;
		if(!reader.parse(data, jsonData))
		{
			return R_ERR_PARAM;
		}

		//lordType
		if (! jsonData.isMember("type"))
		{
			return R_ERR_PARAM;
		}

		CLogicAllServerLordsList logicLordsList;
		int ret = logicLordsList.Establish(jsonData["type"].asInt());
		if (ret != R_SUCCESS) return ret;

		CGI_SEND_LOG("action=Establish");

		return R_SUCCESS;
	}
#endif

	int CloseWorship()
	{
		CLogicAllServerLordsList logicLordsList;
		int ret = logicLordsList.CloseWorship();
		if (ret != R_SUCCESS) return ret;

		CGI_SEND_LOG("action=CloseWorship");

		return R_SUCCESS;
	}

	int Worship()
	{
		string data = CCGIIn::GetCGIStr("data");
		Json::Value jsonData;
		Json::Reader reader;
		if(!reader.parse(data, jsonData))
		{
			return R_ERR_PARAM;
		}

		unsigned id = 0, type = 0, uid = 0;
		if (! Json::GetUInt(jsonData, "uid", uid)
		|| ! Json::GetUInt(jsonData, "id", id)
		|| ! Json::GetUInt(jsonData, "type", type))
		{
			return R_ERR_PARAM;
		}

		CLogicAllServerLordsList logicLordsList;
		int ret = logicLordsList.Worship(uid, id, type, m_jsonResult);
		if (ret != R_SUCCESS) return ret;

		CGI_SEND_LOG("action=Worship");

		return R_SUCCESS;
	}

	int GetAllLords()
	{
		string data = CCGIIn::GetCGIStr("data");
		Json::Value jsonData;
		Json::Reader reader;
		if(!reader.parse(data, jsonData))
		{
			return R_ERR_PARAM;
		}

		unsigned uid = 0;
		if (! Json::GetUInt(jsonData, "uid", uid))
		{
			return R_ERR_PARAM;
		}

		CLogicAllServerLordsList logicLordsList;
		int ret = logicLordsList.GetAllLords(uid, m_jsonResult);
		if (ret != R_SUCCESS) return ret;

		CGI_SEND_LOG("action=GetAllLords");

		return R_SUCCESS;
	}

	int GetRanksList()
	{
		string data = CCGIIn::GetCGIStr("data");
		Json::Value jsonData;
		Json::Reader reader;
		if(!reader.parse(data, jsonData))
		{
			return R_ERR_PARAM;
		}

		unsigned type = 0, uid = 0;
		if (! Json::GetUInt(jsonData, "uid", uid)
		|| ! Json::GetUInt(jsonData, "type", type))
		{
			return R_ERR_PARAM;
		}


		CLogicAllServerLordsList logicLordsList;
		int ret = logicLordsList.GetRankList(uid, type, m_jsonResult);
		if (ret != R_SUCCESS) return ret;

		CGI_SEND_LOG("action=GetRanksList");

		return R_SUCCESS;
	}
};

CGI_MAIN(CgiAllServerLords)


