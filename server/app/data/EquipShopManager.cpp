#include "EquipShopManager.h"

int EquipShopManager::OnInit()
{
	for(unsigned i=0; i < DB_BASE_BUFF*DB_EQUIP_SHOP_FULL; ++i)
	{
		if(!m_data->Empty(i))
		{
			uint32_t uid = m_data->data[i].uid;
			uint8_t pid = m_data->data[i].pid;

			m_map[uid][pid] = i;
		}
	}

	return 0;
}

void EquipShopManager::OnExit()
{

}

void EquipShopManager::OnTimer1()
{

}

void EquipShopManager::OnTimer2()
{

}

int EquipShopManager::CheckBuff(unsigned uid)
{
	if(!m_map.count(uid))
		return R_ERR_NO_DATA;

	return 0;
}

int EquipShopManager::AddBuff(DataEquipShop & equipshop)
{
	int index = GetFreeIndex();

	uint32_t uid = equipshop.uid;
	uint8_t pid = equipshop.pid ;


	if(index == -1)
	{
		error_log("[AddBuff] get free index error. uid=%u", uid);
		return R_ERR_DATA;
	}

	if(Add(index, equipshop))
	{
		m_map[uid][pid] = index;
	}
	else
	{
		error_log("[AddBuff] Add to dbc failed. uid=%u", uid);
		return R_ERR_DATA;
	}

	return 0;
}

int EquipShopManager::LoadBuff(unsigned uid)
{
	//为防止重复加载
	if (m_map.count(uid) > 0)
	{
		return 0;
	}

	vector<DataEquipShop> vcteshop(1);
	vcteshop[0].uid = uid;

	int ret = Load(vcteshop);

	if (ret)
	{
		return ret;
	}

	//加载用户的所有装备商店表数据
	//单个逐个加载
	for(int i = 0; i < vcteshop.size(); ++i)
	{
		unsigned index = GetFreeIndex();

		if(index == -1)
		{
			error_log("[LoadBuff] get free index error. uid=%u", uid);
			return R_ERR_DATA;
		}

		m_data->data[index] = vcteshop[i];  //给m_data内的数据赋值
		unsigned pid = vcteshop[i].pid;

		if(m_data->MardLoad(index))
		{
			m_freeIndex.erase(index);
		}
		else
		{
			error_log("[LoadBuff] mark load failed. uid=%u,pid=%d.", uid, pid);
			return R_ERROR;
		}

		m_map[uid][pid] = index;
	}

	if (!m_map.count(uid))
	{
		return R_ERR_NO_DATA;
	}

	return 0;
}

DataEquipShop & EquipShopManager::GetEquipShop(unsigned uid, uint8_t pid, unsigned &index)
{
	if (!m_map.count(uid) || !m_map[uid].count(pid))
	{
		error_log("[GetEquipShop] get equipshop data error. uid=%u, pid=%hu", uid, pid);
		throw std::runtime_error("get_equip_shop_error");
	}

	index = m_map[uid][pid];

	return m_data->data[index];
}

int EquipShopManager::AddEquipShop(DataEquipShop & equipshop)
{
	return AddBuff(equipshop);
}

bool EquipShopManager::UpdateEquipShop(unsigned index)
{
	return m_data->MarkChange(index);
}

int EquipShopManager::FullMessage(unsigned uid, User::User* reply)
{
	//加载数据
	map<uint8_t, uint32_t>::iterator miter = m_map[uid].begin();

	for(; miter != m_map[uid].end(); ++miter)
	{
		DataCommon::EquipShopCPP * pmsg = reply->add_equipshop();
		m_data->data[miter->second].SetMessage(pmsg);
	}

	return 0;
}

void EquipShopManager::DoClear(unsigned uid)
{
	if(m_map.count(uid))
	{
		 map<uint8_t, uint32_t>::iterator miter = m_map[uid].begin();

		 for(; miter != m_map[uid].end(); )
		 {
			 Clear(miter->second);
			 m_map[uid].erase(miter++);
		 }

		 m_map.erase(uid);
	}
}

void EquipShopManager::DoSave(unsigned uid)
{
	if(m_map.count(uid))
	{
		 map<uint8_t, uint32_t>::iterator miter = m_map[uid].begin();

		 for(; miter != m_map[uid].end(); ++miter)
		 {
				AddSave(miter->second);
		 }
	}
}

