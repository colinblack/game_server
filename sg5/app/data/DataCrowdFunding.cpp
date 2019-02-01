/*
 * DataCrowdFunding.cpp
 *
 *  Created on: 2016-1-25
 *      Author: Ralf
 */

#include "DataCrowdFunding.h"
#include "DataUserBasic.h"
#include "LogicUpdates.h"
#include "LogicEquipment.h"
#include "LogicPay.h"

map<unsigned, CrowdFundingConfigItme> CDataCrowdFunding::m_CrowdFundingMap;

int CDataCrowdFunding::InitCrowdFunding()
{
	if(!m_CrowdFundingMap.empty())
		return R_SUCCESS;

	int ret = 0;
	Json::Value data;

	ret = CDataXML::readJsonConfFile("zhongchouchoujiang.json", data);
	if (ret)
	{
		return ret;
	}

	if(!data.isMember("item1") || !data["item1"].isArray()
	|| !data.isMember("item2") || !data["item2"].isArray()
	|| !data.isMember("item3") || !data["item3"].isArray()
	|| !data.isMember("item4") || !data["item4"].isArray())
	{
		error_log("parse zhongchouchoujiang.json error");
		return R_ERR_DATA;
	}

	for (unsigned i = 0; i < data["item1"].size(); ++i)
	{
		unsigned id = data["item1"][i]["id"].asUInt();
		m_CrowdFundingMap[id].id = id;
		m_CrowdFundingMap[id].count = data["item1"][i]["count"].asUInt();
		m_CrowdFundingMap[id].need = data["item1"][i]["need"].asUInt();
	}
	for (unsigned i = 0; i < data["item2"].size(); ++i)
	{
		unsigned id = data["item2"][i]["id"].asUInt();
		m_CrowdFundingMap[id].id = id;
		m_CrowdFundingMap[id].count = data["item2"][i]["count"].asUInt();
		m_CrowdFundingMap[id].need = data["item2"][i]["need"].asUInt();
	}
	for (unsigned i = 0; i < data["item3"].size(); ++i)
	{
		unsigned id = data["item3"][i]["id"].asUInt();
		m_CrowdFundingMap[id].id = id;
		m_CrowdFundingMap[id].count = data["item3"][i]["count"].asUInt();
		m_CrowdFundingMap[id].need = data["item3"][i]["need"].asUInt();
	}
	for (unsigned i = 0; i < data["item4"].size(); ++i)
	{
		unsigned id = data["item4"][i]["id"].asUInt();
		m_CrowdFundingMap[id].id = id;
		m_CrowdFundingMap[id].count = data["item4"][i]["count"].asUInt();
		m_CrowdFundingMap[id].need = data["item4"][i]["need"].asUInt();
	}

	return R_SUCCESS;
}

CDataCrowdFunding::CDataCrowdFunding(string path)
	: DataBase(path)
{
	m_msg = new CrowdFunding::CrowdFunding();
}
int CDataCrowdFunding::Init()
{
	int ret = InitCrowdFunding();
	if(ret)
		return ret;

	ret = Parse();
	if(ret == 0)
	{
		m_data.Parse(*(CrowdFunding::CrowdFunding *)m_msg);

		((CrowdFunding::CrowdFunding *)m_msg)->Clear();
	}
	else if(ret != R_ERR_NO_DATA)
		return ret;

	for(map<unsigned, CrowdFundingConfigItme>::const_iterator it=m_CrowdFundingMap.begin();it!=m_CrowdFundingMap.end();++it)
	{
		m_data.item[it->first].id = it->first;
		m_data.item[it->first].count = it->second.count;
		m_data.item[it->first].need = it->second.need;
		//cout<<"add:"<<it->first<<endl;
	}
	vector<unsigned int> del;
	for(map<unsigned int, DataCrowdFundingItem>::iterator it=m_data.item.begin();it!=m_data.item.end();++it)
	{
		if(!m_CrowdFundingMap.count(it->first))
			del.push_back(it->first);
	}
	for(vector<unsigned int>::iterator it=del.begin();it!=del.end();++it)
	{
		m_data.item.erase(*it);
		//cout<<"del:"<<*it<<endl;
	}

	Save();
	return 0;
}
int CDataCrowdFunding::Save()
{
	m_data.Serialize((CrowdFunding::CrowdFunding *)m_msg);

	int ret = Serialize();
	if(ret)
		return ret;

	//File::Write("/data/release/sgonline/debug", m_msg->DebugString());

	((CrowdFunding::CrowdFunding *)m_msg)->Clear();

	return 0;
}
int CDataCrowdFunding::Sig(int sig)
{
	if(sig == SIGRTMIN)
		Restart();

	return 0;
}

int CDataCrowdFunding::Get(unsigned uid, Json::Value &result)
{
	result["item"].resize(0);
	for(map<unsigned int, DataCrowdFundingItem>::iterator it=m_data.item.begin();it!=m_data.item.end();++it)
	{
		Json::Value temp;
		temp["id"] = it->second.id;
		temp["had"] = it->second.had;
		temp["lastuid"] = it->second.lastuid;
		temp["lastname"] = it->second.lastname;
		temp["lasthad"] = it->second.lasthad;
		if(it->second.user.count(uid))
			temp["self"] = it->second.user[uid].had;
		else
			temp["self"] = 0;
		result["item"].append(temp);
	}
	return 0;
}
int CDataCrowdFunding::Buy(unsigned uid, unsigned id, unsigned need, Json::Value &result)
{
	if(!m_data.item.count(id))
		return R_ERR_LOGIC;

	if(need + m_data.item[id].had > m_data.item[id].need)
		need = m_data.item[id].need - m_data.item[id].had;
	m_data.item[id].had += need;
	if(m_data.item[id].user.count(uid))
		m_data.item[id].user[uid].had += need;
	else
	{
		m_data.item[id].user[uid].uid = uid;
		m_data.item[id].user[uid].had = need;
	}

	if(m_data.item[id].had >= m_data.item[id].need)
	{
		unsigned sum = 0;
		unsigned winner = 0;
		unsigned r = Math::GetRandomInt(m_data.item[id].need) + 1;
		for (map<unsigned int, DataCrowdFundingUser>::iterator it =	m_data.item[id].user.begin(); it != m_data.item[id].user.end(); ++it)
		{
			sum += it->second.had;
			if(sum >= r)
			{
				winner = it->first;
				break;
			}
		}
		if(winner)
		{
			m_data.item[id].lastuid = winner;
			m_data.item[id].lasthad = m_data.item[id].user[winner].had;
			CDataUserBasic userBasic;
			userBasic.GetUserName(winner,PT_TEST,m_data.item[id].lastname);

			Json::Value update, res;
			CLogicEquipment logicEquipment;
			CLogicUpdates logicUpdates;
			logicEquipment.AddOneItem(winner, m_data.item[id].id, m_data.item[id].count, "CrowdFunding", res);
			update["ts"] = Time::GetGlobalTime();
			update["s"] = "CrowdFunding_winner";
			update["id"] = m_data.item[id].id;
			update["count"] = m_data.item[id].count;
			update["had"] = m_data.item[id].user[winner].had;
			logicUpdates.AddUpdates(winner,update,true);

			m_data.item[id].user.erase(winner);
			for (map<unsigned int, DataCrowdFundingUser>::iterator it =	m_data.item[id].user.begin(); it != m_data.item[id].user.end(); ++it)
			{
				unsigned count = it->second.had / CROWD_FUNDING_NEED_BAG;
				if(count)
					logicEquipment.AddOneItem(it->first, CROWD_FUNDING_BAG, count, "CrowdFunding", res);
				update["ts"] = Time::GetGlobalTime();
				update["s"] = "CrowdFunding_loser";
				update["id"] = m_data.item[id].id;
				update["count"] = m_data.item[id].count;
				update["had"] = it->second.had;
				logicUpdates.AddUpdates(it->first,update,true);
			}
		}
		else
		{
			Json::Value update;
			CLogicUpdates logicUpdates;
			CLogicPay logicPay;
			for (map<unsigned int, DataCrowdFundingUser>::iterator it =	m_data.item[id].user.begin(); it != m_data.item[id].user.end(); ++it)
			{
				logicPay.ChangePay(it->first, it->second.had * CROWD_FUNDING_NEED_CASH, 0, "CrowdFunding");
				update["ts"] = Time::GetGlobalTime();
				update["s"] = "CrowdFunding_fail";
				update["id"] = m_data.item[id].id;
				update["count"] = m_data.item[id].count;
				update["had"] = it->second.had;
				logicUpdates.AddUpdates(it->first,update,true);
			}
		}
		m_data.item[id].had = 0;
		m_data.item[id].user.clear();

		Save();
	}

	result["id"] = id;
	result["had"] =m_data.item[id].had;
	result["lastuid"] = m_data.item[id].lastuid;
	result["lastname"] = m_data.item[id].lastname;
	result["lasthad"] = m_data.item[id].lasthad;
	if(m_data.item[id].user.count(uid))
		result["self"] = m_data.item[id].user[uid].had;
	else
		result["self"] = 0;
	result["need"] = need;

	return 0;
}
void CDataCrowdFunding::Restart()
{
	if(Time::GetGlobalTime() > Config::GetIntValue(CONFIG_LOTTERY_END_TS) && Time::GetGlobalTime() < Config::GetIntValue(CONFIG_LOTTERY_END_TS) + 86400)
	{
		Json::Value update;
		CLogicUpdates logicUpdates;
		CLogicPay logicPay;
		for(map<unsigned int, DataCrowdFundingItem>::iterator it=m_data.item.begin();it!=m_data.item.end();++it)
		{
			for (map<unsigned int, DataCrowdFundingUser>::iterator iter = it->second.user.begin(); iter != it->second.user.end(); ++iter)
			{
				logicPay.ChangePay(iter->first, iter->second.had * CROWD_FUNDING_NEED_CASH, 0, "CrowdFunding");
				update["ts"] = Time::GetGlobalTime();
				update["s"] = "CrowdFunding_fail";
				update["id"] = it->second.id;
				update["count"] = it->second.count;
				update["had"] = iter->second.had;
				logicUpdates.AddUpdates(iter->first,update,true);
			}
			it->second.had = 0;
			it->second.user.clear();
		}
		Save();
	}
}
