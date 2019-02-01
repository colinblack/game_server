/*
 * DataMVP.cpp
 *
 *  Created on: 2017-08-03
 *      Author: Ralf
 */


#include "DataMVP.h"
#include "LogicEquipment.h"

CDataMVP::CDataMVP(string path)
	: DataBase(path)
{
	m_msg = new MVP::MVP();
}

int CDataMVP::Init()
{
	int ret = Parse();
	if(ret && ret != R_ERR_NO_DATA)
		return ret;

	if(ret != R_ERR_NO_DATA)
		m_data.Parse(*(MVP::MVP *)m_msg);
	else
	{
		for(unsigned i=1;i<=MVP_RANK;++i)
			m_data.user[i].rank = i;
		for(unsigned i=1; i <= MVP_RANK; ++i)
			m_data.player[i].rank = i;
		for(unsigned i=1; i <= MVP_RANK; ++i)
			m_data.fight[i].rank = i;
	}

	((MVP::MVP *)m_msg)->Clear();

	m_data.Get();
	m_data.GetBattle();
	m_data.GetFight();
	m_data.GetAll();

	return 0;
}
int CDataMVP::Save()
{
	m_data.Serialize((MVP::MVP *)m_msg);

	int ret = Serialize();

	((MVP::MVP *)m_msg)->Clear();

	return ret;
}
int CDataMVP::Sig(int sig)
{
	if(sig == SIGRTMIN)
		Daily();
	else if(sig == SIGRTMIN + 1)
		Reward();
	else if(sig == SIGRTMIN + 2)
		Clear();

	return 0;
}

void CDataMVP::Daily()
{
	const unsigned sc[MVP_RANK] = {100, 85, 71, 58, 46, 35, 25, 17, 10, 5};

	map<unsigned, DataMVPUser> temp;
	for(multimap<unsigned int, DataMVPUser>::iterator it=m_data.all.begin();it!=m_data.all.end();++it)
		temp[it->second.uid] = it->second;

	for(map<unsigned int, DataMVPUser>::iterator it=m_data.user.begin();it!=m_data.user.end();++it)
	{
		if(!IS_VALID_MVP_RANK(it->second.rank) || !IsValidUid(it->second.uid))
			continue;
		if(!temp.count(it->second.uid))
		{
			temp[it->second.uid] = it->second;
			temp[it->second.uid].rank = 0;
		}
		temp[it->second.uid].rank += sc[it->second.rank - 1];
	}
	for(map<unsigned int, DataMVPUser>::iterator it=m_data.player.begin();it!=m_data.player.end();++it)
	{
		if(!IS_VALID_MVP_RANK(it->second.rank) || !IsValidUid(it->second.uid))
			continue;
		if(!temp.count(it->second.uid))
		{
			temp[it->second.uid] = it->second;
			temp[it->second.uid].rank = 0;
		}
		temp[it->second.uid].rank += sc[it->second.rank - 1];
	}
	for(map<unsigned int, DataMVPUser>::iterator it=m_data.fight.begin();it!=m_data.fight.end();++it)
	{
		if(!IS_VALID_MVP_RANK(it->second.rank) || !IsValidUid(it->second.uid))
			continue;
		if(!temp.count(it->second.uid))
		{
			temp[it->second.uid] = it->second;
			temp[it->second.uid].rank = 0;
		}
		temp[it->second.uid].rank += sc[it->second.rank - 1];
	}

	m_data.all.clear();
	for(map<unsigned int, DataMVPUser>::iterator it=temp.begin();it!=temp.end();++it)
		m_data.all.insert(make_pair(it->second.rank, it->second));

	m_data.GetAll();
	Save();
}
void CDataMVP::Reward()
{
	Json::Value res, update;
	CLogicEquipment eq;
	CLogicUpdates logicUpdates;
	unsigned i = 0;
	for(multimap<unsigned int, DataMVPUser>::reverse_iterator it=m_data.all.rbegin();it!=m_data.all.rend();++it)
	{
		++i;

		unsigned c = 0;
		if(i == 1)
			c = 50;
		else if(i <= 3)
			c = 30;
		else
			c = 15;

		eq.AddOneItem(it->second.uid, 10177, c, "MVPReward", res);

		update["ts"] = Time::GetGlobalTime();
		update["s"] = "MVPReward";
		update["r"] = i;
		update["sc"] = it->second.rank;
		update["id"] = 10177;
		update["c"] = c;
		logicUpdates.AddUpdates(it->second.uid, update, true);

		if(i >= MVP_RANK)
			break;
	}
}
void CDataMVP::Clear()
{
	m_data.all.clear();
	m_data.GetAll();
	Save();
}

int CDataMVP::GetAllServerMVP(Json::Value &result)
{
	result["mvp"] = m_data.res;
	result["fightmvp"] = m_data.resFight;
	result["battlemvp"] = m_data.resBattle;
	result["allmvp"] = m_data.resAll;
	return 0;
}
int CDataMVP::StartAllServerMVP(unsigned rank, unsigned uid)
{
	if(!IS_VALID_MVP_RANK(rank))
		return R_ERR_LOGIC;
	if(m_data.user[rank].uid == uid
	|| (m_data.user[rank].fid
	&& m_data.user[rank].fts + MVP_ATTACK_MAX_TIME > Time::GetGlobalTime()
	&& m_data.user[rank].fid != uid))
		return R_ERR_LOGIC;

	if(m_data.user[rank].fid == uid && m_data.user[rank].fts + MVP_ATTACK_MAX_TIME > Time::GetGlobalTime())
		return 0;
	m_data.user[rank].fid = uid;
	m_data.user[rank].fts = Time::GetGlobalTime();

	m_data.Get();
	return 0;
}
int CDataMVP::EndAllServerMVP(unsigned rank, unsigned uid, bool win, Json::Value &data)
{
	if(!IS_VALID_MVP_RANK(rank))
		return R_ERR_LOGIC;
	if(m_data.user[rank].fid != uid)
		return R_ERR_LOGIC;
	if(win && m_data.user[rank].fts + MVP_ATTACK_MAX_TIME > Time::GetGlobalTime())
	{
		m_data.user.erase(rank);
		m_data.user[rank].rank = rank;
		m_data.user[rank].uid = uid;
		Json::GetString(data, "name", m_data.user[rank].name);
		Json::GetString(data, "fig", m_data.user[rank].fig);
		Json::GetString(data, "sign", m_data.user[rank].sign);
		Json::GetUInt(data, "mcity", m_data.user[rank].mcity);
		if(data.isMember("hero"))
		{
			Json::GetUInt(data["hero"], "id", m_data.user[rank].hero.id);
			Json::GetUInt(data["hero"], "lv", m_data.user[rank].hero.lv);
			Json::GetUInt(data["hero"], "dehp", m_data.user[rank].hero.dehp);
			Json::GetString(data["hero"], "icon", m_data.user[rank].hero.icon);
			Json::GetString(data["hero"], "name", m_data.user[rank].hero.name);
		}

		for(unsigned i=1;i<=MVP_RANK;++i)
		{
			if(i == rank)
				continue;
			if(m_data.user[i].uid == uid)
			{
				unsigned fid = m_data.user[i].fid;
				unsigned fts = m_data.user[i].fts;
				m_data.user.erase(i);
				m_data.user[i].rank = i;
				m_data.user[i].fid = fid;
				m_data.user[i].fts = fts;
			}
		}
	}
	m_data.user[rank].fid = 0;
	m_data.user[rank].fts = 0;

	m_data.Get();
	return 0;
}
int CDataMVP::SetAllServerMVP(unsigned uid, string &sign)
{
	for(map<unsigned int, DataMVPUser>::iterator it=m_data.user.begin();it!=m_data.user.end();++it)
	{
		if(it->second.uid == uid)
		{
			it->second.sign = sign;
			break;
		}
	}
	for(map<unsigned int, DataMVPUser>::iterator it=m_data.player.begin();it!=m_data.player.end();++it)
	{
		if(it->second.uid == uid)
		{
			it->second.sign = sign;
			break;
		}
	}
	for(map<unsigned int, DataMVPUser>::iterator it=m_data.fight.begin();it!=m_data.fight.end();++it)
	{
		if(it->second.uid == uid)
		{
			it->second.sign = sign;
			break;
		}
	}
	for(multimap<unsigned int, DataMVPUser>::iterator it=m_data.all.begin();it!=m_data.all.end();++it)
	{
		if(it->second.uid == uid)
		{
			it->second.sign = sign;
			break;
		}
	}

	m_data.Get();
	m_data.GetBattle();
	m_data.GetFight();
	m_data.GetAll();
	return 0;
}

int CDataMVP::StartAllServerBattleMVP(unsigned rank, unsigned uid)
{
	if(!IS_VALID_MVP_RANK(rank))
		return R_ERR_LOGIC;
	if(m_data.player[rank].uid == uid
	|| (m_data.player[rank].fid
	&& m_data.player[rank].fts + MVP_ATTACK_MAX_TIME > Time::GetGlobalTime()
	&& m_data.player[rank].fid != uid))
		return R_ERR_LOGIC;

	if(m_data.player[rank].fid == uid && m_data.player[rank].fts + MVP_ATTACK_MAX_TIME > Time::GetGlobalTime())
		return 0;
	m_data.player[rank].fid = uid;
	m_data.player[rank].fts = Time::GetGlobalTime();

	m_data.GetBattle();
	return 0;
}
int CDataMVP::EndAllServerBattleMVP(unsigned rank, unsigned uid, bool win, Json::Value &data)
{
	if(!IS_VALID_MVP_RANK(rank))
		return R_ERR_LOGIC;
	if(m_data.player[rank].fid != uid)
		return R_ERR_LOGIC;
	if(win && m_data.player[rank].fts + MVP_ATTACK_MAX_TIME > Time::GetGlobalTime())
	{
		m_data.player.erase(rank);
		m_data.player[rank].rank = rank;
		m_data.player[rank].uid = uid;
		Json::GetString(data, "name", m_data.player[rank].name);
		Json::GetString(data, "fig", m_data.player[rank].fig);
		Json::GetString(data, "sign", m_data.player[rank].sign);
		if(data.isMember("hero"))
		{
			Json::GetUInt(data["hero"], "id", m_data.player[rank].hero.id);
			Json::GetUInt(data["hero"], "lv", m_data.player[rank].hero.lv);
			Json::GetUInt(data["hero"], "dehp", m_data.player[rank].hero.dehp);
			Json::GetString(data["hero"], "icon", m_data.player[rank].hero.icon);
			Json::GetString(data["hero"], "name", m_data.player[rank].hero.name);
		}

		for(unsigned i=1;i<=MVP_RANK;++i)
		{
			if(i == rank)
				continue;
			if(m_data.player[i].uid == uid)
			{
				unsigned fid = m_data.player[i].fid;
				unsigned fts = m_data.player[i].fts;
				m_data.player.erase(i);
				m_data.player[i].rank = i;
				m_data.player[i].fid = fid;
				m_data.player[i].fts = fts;
			}
		}
	}
	m_data.player[rank].fid = 0;
	m_data.player[rank].fts = 0;

	m_data.GetBattle();
	return 0;
}

int CDataMVP::EndAllServerNewWorldFightMVP(unsigned rank, unsigned uid, bool win, Json::Value &data)
{
	if(!IS_VALID_MVP_RANK(rank))
		return R_ERR_LOGIC;
	if(win)
	{
		m_data.fight.erase(rank);
		m_data.fight[rank].rank = rank;
		m_data.fight[rank].uid = uid;
		Json::GetString(data, "name", m_data.fight[rank].name);
		Json::GetString(data, "fig", m_data.fight[rank].fig);
		Json::GetString(data, "sign", m_data.fight[rank].sign);
		if(data.isMember("hero"))
		{
			Json::GetUInt(data["hero"], "id", m_data.fight[rank].hero.id);
			Json::GetUInt(data["hero"], "lv", m_data.fight[rank].hero.lv);
			Json::GetUInt(data["hero"], "dehp", m_data.fight[rank].hero.dehp);
			Json::GetString(data["hero"], "icon", m_data.fight[rank].hero.icon);
			Json::GetString(data["hero"], "name", m_data.fight[rank].hero.name);
		}

		for(unsigned i=1;i<=MVP_RANK;++i)
		{
			if(i == rank)
				continue;
			if(m_data.fight[i].uid == uid)
			{
				unsigned fid = m_data.fight[i].fid;
				unsigned fts = m_data.fight[i].fts;
				m_data.fight.erase(i);
				m_data.fight[i].rank = i;
				m_data.fight[i].fid = fid;
				m_data.fight[i].fts = fts;
			}
		}
	}
	m_data.fight[rank].fid = 0;
	m_data.fight[rank].fts = 0;

	m_data.GetFight();
	return 0;
}
