/*
 * LogicResourceManager.cpp
 *
 *  Created on: 2016-9-10
 *      Author: dawx62fac
 */


#include "LogicResourceManager.h"



////////////////////////////////////////////////////////////////////////////
OfflineResourceItem& LogicResourceManager::Get(unsigned uid)
{
	int index = ResourceManager::Instance()->GetIndex(uid);
	if (index < 0)
	{
		DataBase& userBase = BaseManager::Instance()->Get(uid);
		index = this->Sync(userBase);
	}

	return ResourceManager::Instance()->m_data->item[index];
}

int LogicResourceManager::Sync(const DataBase& userBase)
{
	unsigned uid = userBase.uid;
	int index = ResourceManager::Instance()->GetIndex(uid);
	if (index  < 0)
	{
		if(0 == userBase.heroId)
		{
			error_log("data_error uid: %u", uid);
			throw std::runtime_error("data_error");
		}
		int ret = ResourceManager::Instance()->Add(uid, userBase.heroId);
		if (ret != R_SUCCESS)
		{
			throw std::runtime_error("data_error");
		}

		index = ResourceManager::Instance()->GetIndex(uid);
		if (index < 0)
		{
			throw std::runtime_error("data_error");
		}
	}

	OfflineResourceItem& item = ResourceManager::Instance()->m_data->item[index];
	//同步需要的数据
	item.level = userBase.level;
	item.viplevel = userBase.viplevel;
	item.alliance_id = userBase.alliance_id;
	strncpy(item.fig, userBase.fig, BASE_FIG_LEN);
	strncpy(item.name, userBase.name, BASE_NAME_LEN);

	item.ts = Time::GetGlobalTime();
	return index;
}

unsigned LogicResourceManager::GetRechargePays(unsigned uid, unsigned time)
{
	vector<unsigned> indexs;

	DataChargeHistoryManager::Instance()->GetChargeHistoryList(uid, indexs);

	for(size_t i = 0; i < indexs.size(); ++i)
	{
		unsigned index = indexs[i];

		DataChargeHistory& charge = DataChargeHistoryManager::Instance()->GetChargeHistory(index);

		if (CTime::GetDayInterval(charge.ts, time) == 0)
		{
			return charge.cash;
		}
	}

	return 0;
}

unsigned LogicResourceManager::GetDurationRechargePays(unsigned uid, unsigned startts, unsigned endts)
{
	unsigned chargeTotal = 0;
	vector<unsigned> indexs;

	DataChargeHistoryManager::Instance()->GetChargeHistoryList(uid, indexs);

	for(size_t i = 0; i < indexs.size(); ++i)
	{
		unsigned index = indexs[i];

		DataChargeHistory& charge = DataChargeHistoryManager::Instance()->GetChargeHistory(index);

		if (charge.ts >= startts && charge.ts <= endts)
		{
			chargeTotal += charge.cash;
		}
	}

	return chargeTotal;
}

void LogicResourceManager::SyncUserLevel(unsigned uid, unsigned level)
{
	OfflineResourceItem& item = this->Get(uid);
	item.level = level;

	item.ts = Time::GetGlobalTime();
}

void LogicResourceManager::SyncHeroLevel(unsigned uid, unsigned id, unsigned level)
{
	OfflineResourceItem& item = this->Get(uid);

	int i = 0;
	for(; i < MAX_FORMATION_HERO; ++i)
	{
		if(item.heros[i].id == id)
			break;
	}
	if(i == MAX_FORMATION_HERO)
		return ;

	HeroInfo hero;
	hero.id = id;
	LogicHeroManager::Instance()->GetHeroAttr(uid, id, hero.attr);
	LogicHeroManager::Instance()->GetSkill(uid, id, hero);
	Update(uid, i, hero);
}

void LogicResourceManager::Online(unsigned uid)
{
	try
	{
		OfflineResourceItem& src = this->Get(uid);
		src.ts = Time::GetGlobalTime();
	}
	catch(const std::exception& e)
	{
		(void)e;
	}
}

void LogicResourceManager::Offline(unsigned uid)
{
	try
	{
		OfflineResourceItem& src = this->Get(uid);
		src.ts = Time::GetGlobalTime();
	}
	catch(const std::exception& e)
	{
		(void)e;
	}
}


void LogicResourceManager::Update(unsigned uid, int idx, HeroInfo& hero)
{
	if(idx >= MAX_FORMATION_HERO)
	{
		error_log("param_error uid: %u", uid);
		throw runtime_error("param_error");
	}
	int index = ResourceManager::Instance()->GetIndex(uid);
	if (index < 0)
	{
		error_log("data_error uid: %u", uid);
		throw runtime_error("data_error");
	}

	OfflineResourceItem& item = ResourceManager::Instance()->m_data->item[index];
	memcpy(&item.heros[idx], &hero, sizeof(item.heros[idx]));
}



void LogicResourceManager::Print()
{
	for (int  i = 0; i < MEMORY_PROPERTY_NUM; i++)
	{
		const  OfflineResourceItem& item =
				ResourceManager::Instance()->m_data->item[i];
		if (item.uid == 0) break;

		debug_log("=======================================================");
		debug_log("uid: %u, alliance_id: %u, viplevel:%u, level:%u"
				, item.uid, item.alliance_id, item.viplevel, item.level);
		debug_log("name: %s", item.name);
		debug_log("head: %s", item.fig);
	}
}
