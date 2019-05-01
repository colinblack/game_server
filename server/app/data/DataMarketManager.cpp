#include "DataMarketManager.h"

int DataMarketManager::OnInit()
{
	for(unsigned i=0;i<DB_BASE_BUFF*DB_MARKET_FULL;++i)
	{
		if(!m_data->Empty(i))
			m_map[m_data->data[i].uid] = i;
	}

	return 0;
}

void DataMarketManager::OnExit()
{

}

void DataMarketManager::OnTimer1()
{

}

void DataMarketManager::OnTimer2()
{

}

int DataMarketManager::AddBuff(DataMarket & datamarket)
{
	unsigned index = GetFreeIndex();

	if(index == -1)
		return R_ERR_DATA;

	if(Add(index, datamarket))
	{
		m_map[datamarket.uid] = index;
		return 0;
	}
	else
		return R_ERR_DATA;
}

int DataMarketManager::LoadBuff(unsigned uid)
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
	{
		return ret;
	}
}

unsigned DataMarketManager::GetIndex(unsigned uid)
{
	if(m_map.count(uid))
		return m_map[uid];

	return -1;
}

void DataMarketManager::DoClear(unsigned uid)
{
	if(m_map.count(uid))
	{
		Clear(m_map[uid]);
		m_map.erase(uid);
	}
}

void DataMarketManager::DoSave(unsigned uid)
{
	if(m_map.count(uid))
		AddSave(m_map[uid]);
}

DataMarket & DataMarketManager::Get(unsigned uid)
{
	int index = GetIndex(uid);

	if (index < 0)
	{
		error_log("uid: %u, index=%u", uid, index);
		throw std::runtime_error("get_market_info_error");
	}

	return  m_data->data[index];
}

bool DataMarketManager::IsDataMarketExists(unsigned uid)
{
	if (m_map.count(uid))
	{
		return true;
	}

	return false;
}

bool DataMarketManager::UpdateDataMarket(unsigned index)
{
	return m_data->MarkChange(index);
}

bool DataMarketManager::UpdateDataMarket(DataMarket& datamarket)
{
	unsigned index = GetIndex(datamarket.uid);

	if (-1 == index)
	{
		return false;
	}

	return UpdateDataMarket(index);
}
