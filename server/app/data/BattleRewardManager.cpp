/*
 * BattleRewardManager.cpp
 *
 *  Created on: 2016-12-6
 *      Author: Ralf
 */

#include "BattleRewardManager.h"

int BattleRewardManager::OnInit() {
	for(unsigned i=0;i<DB_BASE_BUFF*DB_BASE_FULL;++i)
	{
		if(!m_data->Empty(i))
			m_map[m_data->data[i].uid] = i;
	}
	return 0;
}

int BattleRewardManager::CheckBuff(unsigned uid)
{
	if(!m_map.count(uid))
		return R_ERR_NO_DATA;
	return 0;
}
int BattleRewardManager::AddBuff(unsigned uid)
{
	unsigned index = GetFreeIndex();
	if(index == -1)
		return R_ERR_DATA;
	DataBattleReward b;
	b.uid = uid;
	if(Add(index, b))
	{
		m_map[uid] = index;
		return 0;
	}
	else
		return R_ERR_DATA;
}
int BattleRewardManager::LoadBuff(unsigned uid)
{
	unsigned index = GetFreeIndex();
	if(index == -1)
		return R_ERR_DATA;
	m_data->data[index].uid = uid;
	int ret = Load(index);
	if(ret == 0)
	{
		m_map[uid] = index;
		return 0;
	}
	else
		return ret;
}
unsigned BattleRewardManager::GetIndex(unsigned uid)
{
	if(m_map.count(uid))
		return m_map[uid];
	return -1;
}
void BattleRewardManager::DoClear(unsigned uid)
{
	if(m_map.count(uid))
	{
		Clear(m_map[uid]);
		m_map.erase(uid);
	}
}
void BattleRewardManager::DoSave(unsigned uid)
{
	if(m_map.count(uid))
		AddSave(m_map[uid]);
}

void BattleRewardManager::OnLogin(unsigned uid)
{
	if(CheckBuff(uid))
	{
		int ret = LoadBuff(uid);
		if(ret == R_ERR_NO_DATA)
			ret = AddBuff(uid);
		if(ret)
			throw runtime_error("get_BattleRewardManager_error");
	}

	unsigned index = GetIndex(uid);
	DataBattleReward &b = m_data->data[index];
	if(CTime::IsDiffDay(b.rts, Time::GetGlobalTime()))
	{
		b.rts = Time::GetGlobalTime();
		b.r = 0;
		m_data->MarkChange(index);
	}
	if(CTime::IsDiffDay(b.cts, Time::GetGlobalTime()))
	{
		b.cts = Time::GetGlobalTime();
		b.ctimes = 0;
		m_data->MarkChange(index);
	}
}
