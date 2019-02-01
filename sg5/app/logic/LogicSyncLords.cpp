/*
 * LogicSyncLords.cpp
 *
 *  Created on: 2016-7-8
 *      Author: dawx62fac
 */

#include <stdexcept>
#include "LogicSyncLords.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "LogicBarbarianKing.h"

const int PAGE_ITEMS = 5;

CLogicLordExploit::CLogicLordExploit(const std::string& path)
	: m_nTime(0)
	, m_nStop(0)
	, m_nReset(1)
	, m_path(path)
{
	if (File::IsExist(m_path))
	{
		std::string content;
		int ret = File::Read(m_path, content);
		if (ret < 0)
		{
			throw std::runtime_error("CLogicLordExploit_read_file_error");
		}

		Json::Value jsonData;
		if (content.size() > 0)
		{
			if(! Json::FromString(jsonData, content))
			{
				throw std::runtime_error("CLogicLordExploit_file_content_error");
			}

			m_nTime = jsonData["upTime"].asInt();

			unsigned now = Time::GetGlobalTime();
			//隔月，重置文件
			if (CTime::GetMonthBeginTime(m_nTime) != CTime::GetMonthBeginTime(now))
			{
				m_nReset = 1;
				m_nStop = 0;
			}
			else
			{
				m_nReset = jsonData["reset"].asInt();
				m_nStop = jsonData["stop"].asInt();

				if (m_nStop == 0 && jsonData.isMember("data") && jsonData["data"].isArray())
				{
					for (size_t i = 0; i < jsonData["data"].size(); i++)
					{
						unsigned uid = jsonData["data"][i]["uid"].asInt();
						if (0 == uid)
						{
							continue;
						}

						//
						m_mapData[uid] = jsonData["data"][i];
					}
				}
			}
		}

		ret = File::Clear(m_path);
		if (ret != 0)
		{
			throw std::runtime_error("CLogicLordExploit_clear_file_error");
		}
	}
	else
	{
		std::cout << "File: " << path << "isn't exist" << std::endl;
	}
}


void CLogicLordExploit::Save()
{
	Json::Value jsonData;
	jsonData["upTime"] = m_nTime/*Time::GetGlobalTime()*/;
	jsonData["stop"] = m_nStop;
	jsonData["reset"] = m_nReset;
	jsonData["data"] = Json::arrayValue;

	for (std::map<unsigned, Json::Value>::iterator it = m_mapData.begin();
			it  != m_mapData.end(); ++it)
	{
		jsonData["data"].append(it->second);
	}

	//
	int ret = File::Write(m_path, Json::ToString(jsonData));
	if(ret)
	{
		error_log("Write_lord_exploit_data_error. ret=%d", ret);
	}
}


void CLogicLordExploit::UpdateMapData(unsigned uid, const std::string& name, unsigned incVal)
{
	if (incVal > 0)
	{
		std::map<unsigned, Json::Value>::iterator itData = m_mapData.find(uid);
		if (itData != m_mapData.end())
		{
			itData->second["value"] = itData->second["value"].asInt() + incVal;
		}
		else
		{
			Json::Value jsonItem;
			jsonItem["uid"] = uid;
			jsonItem["name"] = name;
			jsonItem["value"] = incVal;
			//插入新的
			m_mapData[uid] = jsonItem;
		}
	}
}

std::map<unsigned, Json::Value> CLogicLordExploit::GetData()
{
	std::map<unsigned, Json::Value> copyData = m_mapData;
	m_mapData.clear();
	Save();

	return copyData;
}


std::string CLogicLordExploit::GetName(
		unsigned uid, const std::map<unsigned, string>& mapHeroNames)
{
	std::map<unsigned, std::string>::const_iterator it = mapHeroNames.find(uid);
	if (it != mapHeroNames.end())
	{
		return it->second;
	}

	return "";
}

//统计增量
void CLogicLordExploit::StatisticsIcrement(
			const std::string& path,
			const std::map<unsigned, unsigned>& mapHerokills,
			const std::map<unsigned, std::string>& mapHeroNames)
{
	//已经停止更新排名列表
	if (m_nStop == 1)
	{
		return ;
	}

	//重置
	if (m_nReset == 1)
	{
		for (std::map<unsigned, unsigned>::const_iterator it = mapHerokills.begin();
							it != mapHerokills.end(); ++it)
		{
			UpdateMapData(it->first, GetName(it->first, mapHeroNames), it->second);
		}

		m_nReset = 0;
	}
	else
	{
		//
		std::string content;
		int ret = File::Read(path, content);
		if (0 != ret)
		{
			std::cerr << "Read data from: " << path << " error. ret: " << ret << std::endl;
			return ;
		}

		Json::Value jsonRankList;
		if (! Json::FromString(jsonRankList, content) || !jsonRankList.isArray())
		{
			std::cerr << "Parae file data error. not json array" << std::endl;
			return ;
		}

		std::map<unsigned, unsigned> mapCopyHeroKills = mapHerokills;

		for (size_t i = 0; i < jsonRankList.size(); ++i)
		{
			Json::Value item;
			unsigned uid =  jsonRankList[i]["uid"].asInt();
			int kills = jsonRankList[i]["kill"].asInt();

			std::map<unsigned, unsigned>::iterator it = mapCopyHeroKills.find(uid);
			if (it != mapCopyHeroKills.end())
			{
				int inc = (int)it->second - kills;
				if (inc < 0)
				{
					error_log("saved kills: %d, cur kills: %d", kills, (int)it->second);
					continue;
				}


				UpdateMapData(it->first, GetName(it->first, mapHeroNames), inc);

				mapCopyHeroKills.erase(it);
			}
			else
			{
				UpdateMapData(it->first, GetName(it->first, mapHeroNames), it->second);
			}
		}

		//没有记录在档的
		for (std::map<unsigned, unsigned>::iterator it = mapCopyHeroKills.begin();
				it != mapCopyHeroKills.end(); ++it)
		{
			UpdateMapData(it->first, GetName(it->first, mapHeroNames), it->second);
		}
	}

	m_nTime = Time::GetGlobalTime();

	Save();
}

void CLogicLordExploit::Reset()
{
	m_nReset = 1;

	m_nTime = Time::GetGlobalTime();

	Save();
}

void CLogicLordExploit::Stop()
{
	m_nStop = 1;

	Save();
}

//------------------------------------------------
void BaseLordUnit::HttpRequest(const std::string& action, const std::string& data, Json::Value& result)
{
	string url = "action=" + action;
	url.append("&data=").append(Crypt::UrlEncode(data));

	//std::cout << "Req:" << data << std::endl;

	CLogicAllServerBaseMatch logicBaseMatch;
	int ret = logicBaseMatch.RequestBaseMatch(url, result, CONFIG_ALLSERVER_LORDS_CGI, true);
	if (ret != 0)
	{
		std::cout << "Request error. ret: " << result << std::endl;
		return ;
	}

	//std::cout << "result: " << result << std::endl;
}

std::string BaseLordUnit::UserName(unsigned uid)
{
	CDataUserBasic dbUser;
	std::string userName;
	if (R_SUCCESS == dbUser.GetUserName(uid, OpenPlatform::GetType(), userName))
	{
		return userName;
	}

	throw std::runtime_error("get_user_name_error.");
}

void BaseLordUnit::Establish()
{
	Json::Value jsonReqData;
	Json::Value result;
	jsonReqData["type"] = Type();
	HttpRequest("Establish", Json::ToString(jsonReqData), result);
}

//------------------
int LordExploitUnit::Type() const
{
	return 1;
}

void LordExploitUnit::Sync(const std::string& cachePath)
{
	CLogicLordExploit logicExploit(cachePath);

	int i = 0;
	Json::Value jsonReqData;
	Json::Value result;

	jsonReqData["type"] = Type();
	const std::map<unsigned, Json::Value> data = logicExploit.GetData();
	for (std::map<unsigned, Json::Value>::const_iterator it = data.begin();
			it != data.end(); ++it)
	{

		jsonReqData["data"].append(it->second);
		++i;

		if (i == PAGE_ITEMS)
		{
			HttpRequest("Sync", Json::ToString(jsonReqData), result);
			i = 0;
			jsonReqData["data"].clear();
		}
	}

	if (jsonReqData["data"].size() > 0)
	{
		HttpRequest("Sync", Json::ToString(jsonReqData), result);
		jsonReqData["data"].clear();
	}
}



int LordTryndamereUnit::Type() const
{
	return 2;
}

void LordTryndamereUnit::Sync(const std::string& path)
{
	CLogicBarbarianKing logicBarbarianKing;
	CDataBarbarianKing* dataBarbarianKing = logicBarbarianKing.GetCDataBarbarianKing();
	if (!dataBarbarianKing)
	{
		error_log("init_BarbarianKing_fail");
		//DB_ERROR_RETURN_MSG("init_BarbarianKing_fail");
		return ;
	}

	Json::Value jsonReqData, result;
	jsonReqData["type"] = Type();

	int cnt = 0;
	for (int group = 0; group < 3; ++group)
	{
		vector<BKChallenger> challenger;
		int ret = dataBarbarianKing->GetBKList(group, challenger);
		if(ret) continue;

		if(challenger.size() > 0)
		{
			for(unsigned i=0;i<challenger.size();++i)
			{
				Json::Value jsonItem;
				jsonItem["uid"] = challenger[i].uid;
				jsonItem["value"] = challenger[i].point;
				jsonItem["name"] = challenger[i].name;

				jsonReqData["data"].append(jsonItem);

				cnt++;

				if (cnt == PAGE_ITEMS)
				{
					cnt = 0;
					HttpRequest("Sync", Json::ToString(jsonReqData), result);
					jsonReqData["data"].clear();
				}
			}
		}
	}

	if (jsonReqData["data"].size() > 0)
	{
		HttpRequest("Sync", Json::ToString(jsonReqData), result);
	}
}




int LordPlunderUnit::Type() const
{
	return 3;
}

void LordPlunderUnit::Sync(const std::string& path)
{
	if (File::IsExist(path))
	{
		std::string content;
		if (0 != File::Read(path, content))
		{
			std::cerr << "Read file: " << path << " error." << std::endl;
			return;
		}

		Json::Value jsonData;
		if (! Json::FromString(jsonData, content) || ! jsonData.isArray())
		{
			std::cerr << "Parse from file: " << path << " error." << std::endl;
			return;
		}

		if (jsonData.size() == 0) return ;

		Json::Value jsonReqData, result;
		jsonReqData["type"] = Type();
		int accCnt = 0;
		for (size_t i = 0; i < jsonData.size(); ++i)
		{
			Json::Value jsonItem;
			unsigned uid = jsonData[i]["uid"].asInt();
			if (0 == uid) continue;

			try
			{
				jsonItem["uid"] = uid;
				jsonItem["name"] = this->UserName(uid);
				//jsonItem["value"] = jsonData[i]["loot"].asInt();
				jsonItem["value"] = 0;
				jsonItem["uint64_val"] = jsonData[i]["loot"].asDouble();

				jsonReqData["data"].append(jsonItem);

				++accCnt;

				if (accCnt == PAGE_ITEMS)
				{
					HttpRequest("Sync", Json::ToString(jsonReqData), result);
					accCnt = 0;
					jsonReqData["data"].clear();
				}
			}
			catch (const std::exception& e)
			{
				(void)e;
				continue;
			}
		}

		if (jsonReqData["data"].size() > 0)
		{
			HttpRequest("Sync", Json::ToString(jsonReqData), result);
		}
	}
	else
	{
		std::cerr << "file: " << path << "isn't exist" << std::endl;
	}

}

int LordR5Unit::Type() const
{
	return 3;
}

void LordR5Unit::Sync(const std::string& path)
{
	if (File::IsExist(path))
	{
		std::string content;
		if (0 != File::Read(path, content))
		{
			std::cerr << "Read file: " << path << " error." << std::endl;
			return;
		}

		Json::Value jsonData;
		if (! Json::FromString(jsonData, content) || ! jsonData.isArray())
		{
			std::cerr << "Parse from file: " << path << " error." << std::endl;
			return;
		}

		if (jsonData.size() == 0) return ;

		Json::Value jsonReqData, result;
		jsonReqData["type"] = Type();
		int accCnt = 0;
		for (size_t i = 0; i < jsonData.size(); ++i)
		{
			Json::Value jsonItem;
			unsigned uid = jsonData[i]["uid"].asInt();
			if (0 == uid) continue;

			try
			{
				unsigned val = jsonData[i]["r5"].asInt();
				if (val == 0) continue;

				jsonItem["uid"] = uid;
				jsonItem["name"] = this->UserName(uid);

				jsonItem["value"] = val;
				jsonReqData["data"].append(jsonItem);

				++accCnt;

				if (accCnt == PAGE_ITEMS)
				{
					HttpRequest("Sync", Json::ToString(jsonReqData), result);
					accCnt = 0;
					jsonReqData["data"].clear();
				}
			}
			catch (const std::exception& e)
			{
				(void)e;
				continue;
			}
		}

		if (jsonReqData["data"].size() > 0)
		{
			HttpRequest("Sync", Json::ToString(jsonReqData), result);
		}
	}
	else
	{
		std::cerr << "file: " << path << "isn't exist" << std::endl;
	}
}

int LordCostUnit::Type() const
{
	return 4;
}

void LordCostUnit::Sync(const std::string& path)
{
	if (! File::IsExist(path))
	{
		std::cerr << "file: " << path << "isn't exist" << std::endl;
		return ;
	}

	std::ifstream fin(path.c_str(), std::ios::in);
	char line[256] = {0};
	unsigned uid = 0;
	int cost = 0;
	int i = 0;
	Json::Value jsonItem, jsonReqData, result;
	jsonReqData["data"] = Json::arrayValue;
	jsonReqData["type"] = Type();
	while(fin.getline(line, sizeof(line)))
	{
		std::stringstream data(line);
		data >> uid;
		data >> cost;
		if (! IsValidUid(uid))
		{
			std::cerr << "LoardRechargeUnit read uid:" << uid <<" from file: " << path << " error" << std::endl;
			return;
		}
		if (cost >= 0) continue;
		try
		{
			++i;
			jsonItem["uid"] = uid;
			jsonItem["name"] = this->UserName(uid);
			jsonItem["value"] = -cost;

			jsonReqData["data"].append(jsonItem);

			if (i == PAGE_ITEMS)
			{
				HttpRequest("Sync", Json::ToString(jsonReqData), result);
				i = 0;
				jsonReqData["data"].clear();
			}
		}
		catch(const std::exception& e)
		{
			(void)e;
			continue;
		}
	}

	if (jsonReqData["data"].size() > 0)
	{
		HttpRequest("Sync", Json::ToString(jsonReqData), result);
	}
}

int LordRechargeUnit::Type() const
{
	return 5;
}

void LordRechargeUnit::Sync(const std::string& path)
{
	if (! File::IsExist(path))
	{
		std::cerr << "file: " << path << "isn't exist" << std::endl;
		return ;
	}

	std::ifstream fin(path.c_str(), std::ios::in);
	char line[256] = {0};
	unsigned uid = 0;
	int recharge = 0;
	int i = 0;
	Json::Value jsonItem, jsonReqData, result;
	jsonReqData["data"] = Json::arrayValue;
	jsonReqData["type"] = Type();
	while(fin.getline(line, sizeof(line)))
	{
		std::stringstream data(line);
		data >> uid;
		data >> recharge;
		if (! IsValidUid(uid))
		{
			std::cerr << "LoardRechargeUnit read uid:" << uid <<" from file: " << path << " error" << std::endl;
			return;
		}

		if (recharge <= 0) continue;
		try
		{
			++i;
			jsonItem["uid"] = uid;
			jsonItem["name"] = this->UserName(uid);
			jsonItem["value"] = recharge;

			jsonReqData["data"].append(jsonItem);

			if (i == PAGE_ITEMS)
			{
				HttpRequest("Sync", Json::ToString(jsonReqData), result);
				i = 0;
				jsonReqData["data"].clear();
			}
		}
		catch(const std::exception& e)
		{
			(void)e;
			continue;
		}
	}

	if (jsonReqData["data"].size() > 0)
	{
		HttpRequest("Sync", Json::ToString(jsonReqData), result);
	}
}


//////////////////////////////////////////////////////////////////////////
int CLogicLordRamote::HttpRequest(const std::string& action, const std::string& data, Json::Value& result)
{
	string url = "action=" + action;
	if (data.size() > 0)
	{
		url.append("&data=").append(Crypt::UrlEncode(data));
	}

	CLogicAllServerBaseMatch logicBaseMatch;
	int ret = logicBaseMatch.RequestBaseMatch(url, result, CONFIG_ALLSERVER_LORDS_CGI, true);
	return ret;
}

int CLogicLordRamote::GetAllLords(unsigned uid, Json::Value& result)
{
	Json::Value jsonReqData;
	jsonReqData["uid"] = uid;
	int ret = HttpRequest("GetAllLords", Json::ToString(jsonReqData), result);
	return ret;
}

int CLogicLordRamote::GetRankList(unsigned uid, int type, Json::Value& result)
{
	Json::Value jsonReqData;
	jsonReqData["type"] = type;
	jsonReqData["uid"] = uid;

	int ret = HttpRequest("GetRanksList", Json::ToString(jsonReqData), result);
	return ret;
}

