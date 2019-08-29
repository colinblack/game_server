/*
 * InviteConfig.cpp
 *
 *  Created on: 2016-6-8
 *      Author: Administrator
 */

#include "InviteConfig.h"

InviteConfig::InviteConfig()
{

}
InviteConfig::~InviteConfig()
{

}

bool InviteConfig::init(const string & path)
{
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(path.c_str()))
	{
		error_log("load_fail");
		return false;
	}
	if(!xmlConf.FindElem("content") )
	{
		error_log("find_node_content_fail");
		return false;
	}
	xmlConf.IntoElem();
	if(!xmlConf.FindElem("day") )
	{
		error_log("find_node_day_fail");
		return false;
	}
	xmlConf.IntoElem();
	if(!xmlConf.FindElem("reward") )
	{
		return false;
	}
	Json::Value rewardValue;
	string rewarddata = xmlConf.GetData();
	if(!FileToJson::stringToJson(rewarddata, rewardValue))
	{
		error_log("gate config data error! data=[%s]", rewarddata.c_str());
		return false;
	}

	if(!rewardValue.isMember("reward"))
	{
		error_log("filetojson error by path=%s", path.c_str());
		return false;
	}

	Json::Value & interValue = rewardValue["reward"];
	Json::Value::Members member = interValue.getMemberNames();
	for(Json::Value::Members::iterator iter = member.begin(); iter != member.end(); ++iter)
	{
		string key = *iter;
		if(key.find("equip") != string::npos)
		{
			Json::Value & equipObj = interValue[key];
			AwardInfo sInfo;
			if(!Json::GetUInt(equipObj, "id", sInfo.id))
			{
				error_log("get random award id fail str=%s", rewarddata.c_str());
				return false;
			}

			uint32_t count = 0;
			if(!Json::GetUInt(equipObj, "c", count))
			{
				error_log("get random award c fail str=%s", rewarddata.c_str());
				return false;
			}
			sInfo.count = count;
			sInfo.type = AWARD_TYPE_ITEM;
			vdayAward.push_back(sInfo);
		}
	}
	xmlConf.OutOfElem();
	if(!xmlConf.FindElem("level") )
	{
		return false;
	}
	xmlConf.IntoElem();
	while(xmlConf.FindElem("reward"))
	{
		InviteLevelConfig sConfig;
		sConfig.vAward.clear();
		string idStr = xmlConf.GetAttrib("id");
		sConfig.id = CTrans::STOI(idStr);

		string levelStr = xmlConf.GetAttrib("level");
		sConfig.level = CTrans::STOI(levelStr);

		string numStr = xmlConf.GetAttrib("num");
		sConfig.count = CTrans::STOI(numStr);

		Json::Value rewardValue;
		string rewarddata = xmlConf.GetData();
		if(!FileToJson::stringToJson(rewarddata, rewardValue))
		{
			error_log("gate config data error! data=[%s]", rewarddata.c_str());
			return false;
		}

		Json::Value & interValue = rewardValue["reward"];
		Json::Value::Members member = interValue.getMemberNames();
		for(Json::Value::Members::iterator iter = member.begin(); iter != member.end(); ++iter)
		{
			string key = *iter;
			if(key.find("equip") != string::npos)
			{
				Json::Value & equipObj = interValue[key];
				AwardInfo sInfo;
				if(!Json::GetUInt(equipObj, "id", sInfo.id))
				{
					error_log("get random award id fail str=%s", rewarddata.c_str());
					return false;
				}

				uint32_t count = 0;
				if(!Json::GetUInt(equipObj, "c", count))
				{
					error_log("get random award c fail str=%s", rewarddata.c_str());
					return false;
				}
				sInfo.count = count;
				sInfo.type = AWARD_TYPE_ITEM;
				sConfig.vAward.push_back(sInfo);
			}
		}
		m_levels.push_back(sConfig);
	}
	return true;
}

bool InviteConfig::getConfig(uint32_t id, InviteLevelConfig & sConfig)
{
	vector<InviteLevelConfig>::iterator it;
	for(it = m_levels.begin(); it != m_levels.end(); it++)
	{
		if(it->id == id)
		{
			sConfig = *it;
			return true;
		}
	}
	return false;
}
