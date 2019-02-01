/*
 * DataChick.cpp
 *
 *  Created on: 2018年7月26日
 *      Author: Ralf
 */


#include "DataChick.h"

int CDataChick::Sig(int sig)
{
	if(sig == SIGRTMIN)
		start();
	else if(sig == SIGRTMIN + 1)
		end();

	return 0;
}

void CDataChick::start()
{
	m_data.reg = true;
	m_data.user.clear();
	Save();
}
void CDataChick::end()
{
	m_data.reg = false;
	if(!m_data.user.empty())
	{
		vector<pair<unsigned, unsigned> > m;
		try
		{
			string buf;
			Json::Value json;
			string path = "chickmap.json";
			path = MainConfig::GetAllServerPath(CONFIG_XML_PATH + path);
			int ret = File::Read(path, buf);
			if(ret == 0)
			{
				Json::Reader reader;
				if(reader.parse(buf, json) && json.isArray())
				{
					for(unsigned i=0;i<json.size();++i)
					{
						if(json[i].isArray() && json[i].size() == 2)
							m.push_back(make_pair(json[i][0u].asUInt(), json[i][1u].asUInt()));
					}
				}
			}
		}
		catch(exception &e){}
		if(m.empty())
		{
			for(int i=0;i<CHICK_MAP;++i)
			{
				for(int j=0;j<CHICK_MAP;++j)
					m.push_back(make_pair(i, j));
			}
		}
		vector<DataChickUser> temp;
		for (map<unsigned int, DataChickUser>::iterator it = m_data.user.begin();it != m_data.user.end(); ++it)
			temp.push_back(it->second);
		random_shuffle(temp.begin(), temp.end());
		unsigned z = temp.size() / CHICK_USER + 1;
		vector<DataChickUser>::iterator it = temp.begin();
		for(unsigned i=1;i<=z;++i)
		{
			random_shuffle(m.begin(), m.end());
			unsigned j = 0;
			Json::Value t;
			while(it != temp.end() && j < CHICK_USER)
			{
				m_data.user[it->uid].zone = i;
				it->Get(t[CTrans::UTOS(it->uid)], m[j]);
				++it;
				++j;
			}
			string path = CHICK_PATH + CTrans::UTOS(i) + ".zone";
			File::Write(path, Json::ToString(t));

			Json::Value t_loot;
			j = CHICK_USER ;
			while(j < CHICK_USER + CHICK_EQUIP)
			{
				Json::Value item;
				item.clear();
				item["x"] = m[j].first;
				item["y"] = m[j].second;
				item["loot"] = Json::Value(Json::arrayValue);
				for (unsigned loop = 0;loop<5;loop++)
					item["loot"].append(0);
				if  (j < CHICK_USER + 5)
					item["loot"][0u] = 1000;
				else if (j < CHICK_USER + 5 + 10)
					item["loot"][0u] = 300;
				else if (j < CHICK_USER + 5 + 10 + 10)
					item["loot"][0u] = 500;
				else if (j < CHICK_USER + 5 + 10 + 10 + 5)
					item["loot"][1u] = 1000;
				else if (j < CHICK_USER + 5 + 10 + 10 + 5 + 10)
					item["loot"][1u] = 300;
				else if (j < CHICK_USER + 5 + 10 + 10 + 5 + 10 + 10)
					item["loot"][1u] = 500;
				else
					item["loot"][4u] = 10;
				t_loot.append(item);
				++j;
			}
			string path2 = CHICK_PATH + CTrans::UTOS(i) + ".loot";
			File::Write(path2, Json::ToString(t_loot));
		}
	}
	Save();
}

int CDataChick::GetChickReg(unsigned uid, Json::Value &res)
{
	if(m_data.user.count(uid))
	{
		res["reg"] = 1;
		res["zone"] = m_data.user[uid].zone;
	}
	else
	{
		res["reg"] = 0;
		res["zone"] = 0;
	}

	return 0;
}
int CDataChick::ChickReg(unsigned uid, Json::Value &data, Json::Value &res)
{
	if(!m_data.reg || m_data.user.count(uid))
		return R_ERR_LOGIC;

	m_data.user[uid].uid = uid;
	m_data.user[uid].name = data["name"].asString();
	m_data.user[uid].fig = data["fig"].asString();
	m_data.user[uid].level = data["level"].asUInt();
	m_data.user[uid].hero.level = data["hero"]["level"].asUInt();
	for(int i=0;i<NewWorldProperty_max;++i)
		m_data.user[uid].hero.property.push_back(data["hero"]["property"][i].asUInt());
	m_data.user[uid].zone = 0;

	return 0;
}

