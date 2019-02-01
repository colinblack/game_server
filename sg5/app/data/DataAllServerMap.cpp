/*
 * DataAllServerMap.cpp
 *
 *  Created on: 2015-9-15
 *      Author: Ralf
 */

#include "DataAllServerMap.h"

CDataAllServerMap::CDataAllServerMap(string path)
	: DataBase(path)
{
	m_msg = new AllServerMap::AllServerMap();
}

int CDataAllServerMap::Init()
{
	int ret = Parse();
	if(ret)
		return ret;

	AllServerMap::AllServerMap * msg = (AllServerMap::AllServerMap *)m_msg;

	for(int i=0;i<msg->user_size();++i)
	{
		m_user[msg->user(i).uid()] = msg->user(i).level();
		m_levelMap[msg->user(i).level()].insert(msg->user(i).uid());
	}

	msg->Clear();

	return 0;
}

int CDataAllServerMap::Save()
{
	AllServerMap::AllServerMap * msg = (AllServerMap::AllServerMap *)m_msg;
	for(AllServerUserMap::iterator it=m_user.begin();it!=m_user.end();++it)
	{
		AllServerMap::AllServerMapUser *p = msg->add_user();
		p->set_uid(it->first);
		p->set_level(it->second);
	}

	int ret = Serialize();
	if(ret)
		return ret;

	msg->Clear();

	return 0;
}

int CDataAllServerMap::Get(unsigned level, unsigned count, set<unsigned> &res)
{
	if(level < ALL_SERVER_MAP_SEG_1)
		level = ALL_SERVER_MAP_SEG_1;

	unsigned maxl, minl, numl;
	if(level <= ALL_SERVER_MAP_LEVEL_1)
	{
		maxl = level + ALL_SERVER_MAP_SEG_1;
		minl = level - ALL_SERVER_MAP_SEG_1;
	}
	else
	{
		maxl = level + ALL_SERVER_MAP_SEG_2;
		minl = level - ALL_SERVER_MAP_SEG_2;
	}
	numl = maxl - minl;

	for(int i=0;i<count*4;++i)
	{
		unsigned l = maxl - Math::GetRandomInt(numl);
		if(!m_levelMap.count(l))
			continue;
		if(m_levelMap[l].size() == 0)
			continue;

		unsigned r = Math::GetRandomInt(m_levelMap[l].size());
		set<unsigned>::iterator it = m_levelMap[l].begin();
		for(unsigned j=0;j<r;++j)
			++it;
		res.insert(*it);
		if(res.size() == count*2)
			break;
	}

	return 0;
}

int CDataAllServerMap::Set(map<unsigned, unsigned> &res)
{
	for(map<unsigned, unsigned>::iterator it=res.begin();it!=res.end();++it)
	{
		if(m_user.count(it->first) && m_levelMap.count(m_user[it->first]))
			m_levelMap[m_user[it->first]].erase(it->first);
		m_user[it->first] = it->second;
		m_levelMap[it->second].insert(it->first);
	}

	return 0;
}

