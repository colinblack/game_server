/*
 * LadderManager.cpp
 *
 *  Created on: 2016-10-19
 *      Author: Ralf
 */


#include "LadderManager.h"


//////////////////////////////////////////////////////////////////////////
int LadderManager::OnInit()
{
	for (int i = 0; i < LADDER_ITEM; i++)
	{
		if (m_data->ladder.item[i].uid > 0)
		{
			m_laddermap[m_data->ladder.item[i].uid] = i;
		}

		if (m_data->ladder.reward[i] > 0)
		{
			m_rewardmap[m_data->ladder.reward[i]] = i;
		}
	}


	unsigned nts = Time::GetGlobalTime();
	unsigned nh = LogicCommonUtil::GetHourByTime(nts);
	unsigned oh = LogicCommonUtil::GetHourByTime(m_data->ts);
	if(CTime::IsDiffDay(m_data->ts, nts))
	{
		OnDay();
		if(nh >= LADDER_REWARD_T)
			OnReward();
	}
	else if(oh < LADDER_REWARD_T && nh >= LADDER_REWARD_T)
		OnReward();
	return 0;
}
void LadderManager::OnReward()
{
	m_data->ts = Time::GetGlobalTime();
	m_rewardmap.clear();

	for (int i = 0; i < LADDER_ITEM; i++)
	{
		unsigned uid = m_data->ladder.item[i].uid;
		m_data->ladder.reward[i] = uid;
		if (uid > 0)
		{
			m_rewardmap[uid] = i;
		}
	}
}
void LadderManager::OnDay()
{
	m_data->ts = Time::GetGlobalTime();
	m_rewardmap.clear();
	m_data->ladder.ResetReward();
}
void LadderManager::OnHour()
{
	unsigned hour = LogicCommonUtil::GetHourByTime(Time::GetGlobalTime());
	if(hour == LADDER_REWARD_T)
		OnReward();
	else if(hour == 0)
		OnDay();
}

LadderItem& LadderManager::GetLadderItem(int kingdom, int rank)
{
//	if (kingdom < 1 || kingdom > 3)
//	{
//		throw std::runtime_error("LadderManager::GetKingdom_kingdom_params_error");
//	}

	if (rank < 0 || rank >= LADDER_ITEM)
	{
		throw std::runtime_error("LadderManager::GetKingdom_kingdom_rank_error");
	}

	return LadderManager::Instance()->m_data->ladder.item[rank];
}
