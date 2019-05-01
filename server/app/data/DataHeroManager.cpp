#include "DataHeroManager.h"

int DataHeroManager::OnInit()
{
	for(unsigned i=0; i < DB_BASE_BUFF*DB_HERO_FULL; ++i)
	{
		if(!m_data->Empty(i))
		{
			uint32_t uid = m_data->data[i].uid;
			uint32_t heroid = m_data->data[i].heroid;

			m_map[uid][heroid] = i;
		}
	}

	return 0;
}

void DataHeroManager::OnExit()
{

}

void DataHeroManager::OnTimer1()
{

}

void DataHeroManager::OnTimer2()
{

}

int DataHeroManager::CheckBuff(unsigned uid)
{
	if (!m_map.count(uid))
	{
		return R_ERR_NO_DATA;
	}

	return 0;
}

int DataHeroManager::AddBuff(DataHero & hero)
{
	unsigned index = GetFreeIndex();

	uint32_t uid = hero.uid;
	uint32_t heroid = hero.heroid ;


	if(index == -1)
	{
		error_log("[AddBuff] get free index error. uid=%u", uid);
		return R_ERR_DATA;
	}

	if(Add(index, hero))
	{
		m_map[uid][heroid] = index;
	}
	else
	{
		error_log("[AddBuff] Add to dbc failed. uid=%u", uid);
		return R_ERR_DATA;
	}

	return 0;
}

int DataHeroManager::LoadBuff(unsigned uid)
{
	//为防止重复加载
	if (m_map.count(uid) > 0)
	{
		return 0;
	}

	vector<DataHero> vcthero(1);
	vcthero[0].uid = uid;

	int ret = Load(vcthero);

	if (ret)
	{
		return ret;
	}

	if (0 == vcthero.size())
	{
		return R_ERR_NO_DATA;
	}

	//加载用户的所有装备商店表数据
	//单个逐个加载
	for(int i = 0; i < vcthero.size(); ++i)
	{
		int index = GetFreeIndex();

		if(index == -1)
		{
			error_log("[LoadBuff] get free index error. uid=%u", uid);
			return R_ERR_DATA;
		}

		m_data->data[index] = vcthero[i];  //给m_data内的数据赋值
		unsigned heroid = vcthero[i].heroid;

		if(m_data->MardLoad(index))
		{
			m_freeIndex.erase(index);
		}
		else
		{
			error_log("[LoadBuff] mark load failed. uid=%u,pid=%d.", uid, heroid);
			return R_ERROR;
		}

		m_map[uid][heroid] = index;
	}

	return 0;
}

void DataHeroManager::DoClear(unsigned uid)
{
	if(m_map.count(uid))
	{
		 map<uint32_t, uint32_t>::iterator miter = m_map[uid].begin();

		 for(; miter != m_map[uid].end();)
		 {
			 Clear(miter->second);
			 m_map[uid].erase(miter++);
		 }

		 m_map.erase(uid);
	}
}

void DataHeroManager::DoSave(unsigned uid)
{
	if(m_map.count(uid))
	{
		 map<uint32_t, uint32_t>::iterator miter = m_map[uid].begin();

		 for(; miter != m_map[uid].end(); ++miter)
		 {
				AddSave(miter->second);
		 }
	}
}

//////////////////////////////////////////////////////////////////////////////////////
DataHero& DataHeroManager::GetHero(unsigned uid, unsigned heroId)
{
	MapMap_ITER it = m_map.find(uid);
	if (it == m_map.end())
	{
		error_log("get_user_data_failed. uid=%u", uid);
		throw std::runtime_error("Get_user_data_error");
	}

	std::map<uint32_t, uint32_t>::const_iterator hero_it = it->second.find(heroId);
	if (hero_it == it->second.end())
	{
		error_log("get_hero_data_failed. uid=%u,heor=%u", uid, heroId);
		throw std::runtime_error("Get_hero_data_error");
	}

	unsigned index = hero_it->second;

	return m_data->data[index];
}

int  DataHeroManager::GetHeroIndex(unsigned uid, unsigned heroId)
{
	MapMap_ITER it = m_map.find(uid);
	if (it == m_map.end())
	{
		error_log("get_user_data_failed. uid=%u", uid);
		throw std::runtime_error("Get_user_data_error");
	}

	std::map<uint32_t, uint32_t>::const_iterator hero_it = it->second.find(heroId);
	if (hero_it == it->second.end())
	{
		error_log("get_hero_data_failed. uid=%u,hero=%u", uid, heroId);
		throw std::runtime_error("Get_hero_data_error");
	}

	return hero_it->second;
}

DataHero& DataHeroManager::GetHeroByIndex(unsigned index)
{
	if (index >= (DB_BASE_BUFF*DB_HERO_FULL))
	{
		throw std::runtime_error("wrong index param");
	}

	return m_data->data[index];
}

//////////////////////////////////////////////////////////////////////////////////////
bool DataHeroManager::isHeroExists(unsigned uid, unsigned heroid)
{
	if (m_map.count(uid) && m_map[uid].count(heroid))
	{
		return true;
	}

	return false;
}

DataHero & DataHeroManager::GetHero(unsigned uid, unsigned heroid, unsigned & index)
{
	if (!isHeroExists(uid, heroid))
	{
		error_log("[GetHero] heroid is not exist. heroid=%u,uid=%u", uid, heroid);
		throw std::runtime_error("get_hero_error");
	}

	index = m_map[uid][heroid];

	return m_data->data[index];
}

bool DataHeroManager::UpdateHero(unsigned index)
{
	return  m_data->MarkChange(index);
}

int DataHeroManager::GetUsingHeroNums(unsigned uid)
{
	int num = 0;

	if(m_map.count(uid))
	{
		 map<uint32_t, uint32_t>::iterator miter = m_map[uid].begin();

		 for(; miter != m_map[uid].end(); ++miter)
		 {
			 if(m_data->data[miter->second].status)
			 {
				 ++num;
			 }
		 }
	}

	return num;
}

int DataHeroManager::GetHeroPrice(unsigned uid, unsigned heroid, int & price)
{
	if (!ConfigManager::Instance()->m_mapHeroIndex.count(heroid))
	{
		error_log("[GetHeroPrice] heroid not exist. uid=%u, heroid=%u", uid, heroid);
		return R_ERROR;
	}

	unsigned index = ConfigManager::Instance()->m_mapHeroIndex[heroid];

	price = ConfigManager::Instance()->tavern.m_config.heroes(index).price();

	return 0;
}

int DataHeroManager::GetRecruitHero(unsigned uid, vector<DataHero> & vctHeros)
{
	if(m_map.count(uid))
	{
		 map<uint32_t, uint32_t>::iterator miter = m_map[uid].begin();

		 for(; miter != m_map[uid].end(); ++miter)
		 {
			 if(m_data->data[miter->second].status)
			 {
				 vctHeros.push_back(m_data->data[miter->second]);
			 }
		 }
	}

	return 0;
}

int DataHeroManager::GetRecruitHero(unsigned uid, vector<unsigned> & vHeroIndexs)
{
	vHeroIndexs.clear();
	if(m_map.count(uid))
	{
		 map<uint32_t, uint32_t>::iterator miter = m_map[uid].begin();

		 for(; miter != m_map[uid].end(); ++miter)
		 {
			 if(m_data->data[miter->second].status)
			 {
				 vHeroIndexs.push_back(miter->second);
			 }
		 }
	}

	return 0;
}

int DataHeroManager::GetHeros(unsigned uid, vector<unsigned> & indexs)
{
	if(m_map.count(uid))
	{
		 map<uint32_t, uint32_t>::iterator miter = m_map[uid].begin();

		 for(; miter != m_map[uid].end(); ++miter)
		 {
			 indexs.push_back(miter->second);
		 }
	}

	return 0;
}

int DataHeroManager::FullMessage(unsigned uid, User::Hero * hero)
{
	if(m_map.count(uid))
	{
		 map<uint32_t, uint32_t>::iterator miter = m_map[uid].begin();

		 for(; miter != m_map[uid].end(); ++miter)
		 {
			 m_data->data[miter->second].SetMessage(hero->add_hero());
		 }
	}

	return 0;
}
