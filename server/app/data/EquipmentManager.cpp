#include "EquipmentManager.h"
#include "BaseManager.h"

int EquipmentManager::OnInit()
{
	for(unsigned i=0; i < DB_BASE_BUFF*DB_EQUIPMENT_FULL; ++i)
	{
		if(!m_data->Empty(i))
		{
			uint32_t uid = m_data->data[i].uid;
			uint32_t ud = m_data->data[i].ud;

			uint32_t eqid = m_data->data[i].eqid;

			CreateSelfIndex(uid, eqid, ud, i);
		}
	}

	return 0;
}

void EquipmentManager::OnExit()
{

}

void EquipmentManager::OnTimer1()
{

}

void EquipmentManager::OnTimer2()
{

}

int EquipmentManager::InitUserEquip(unsigned uid)
{
	int ret = CheckBuff(uid);

	if (ret)  //数据不存在，可能是因为没有从dbc写入到文件中
	{
		LoadBuff(uid);
	}

	//遍历uid下的所有ud
	map<uint32_t, uint32_t>::iterator miter;

	unsigned maxud = 0;

	for(miter = m_map[uid].begin(); miter != m_map[uid].end(); ++miter)
	{
		if (miter->first > maxud)
		{
			maxud = miter->first;
		}
	}

	m_userMaxEqud[uid] = maxud;

	return 0;
}

int EquipmentManager::CheckBuff(unsigned uid)
{
	if(!m_map.count(uid))
		return R_ERR_NO_DATA;

	return 0;
}

int EquipmentManager::AddBuff(DataEquipment & equipment)
{
	unsigned index = GetFreeIndex();

	uint32_t uid = equipment.uid;
	uint32_t ud = equipment.ud ;


	if(index == -1)
	{
		error_log("[AddBuff] get free index error. uid=%u", uid);
		return R_ERR_DATA;
	}

	if(Add(index, equipment))
	{
		CreateSelfIndex(uid, equipment.eqid, ud, index);
	}
	else
	{
		error_log("[AddBuff] Add to dbc failed. uid=%u", uid);
		return R_ERR_DATA;
	}

	return 0;
}

int EquipmentManager::LoadBuff(unsigned uid)
{
	//为防止重复加载
	if (m_map.count(uid) > 0)
	{
		return 0;
	}

	vector<DataEquipment> vctequip(1);
	vctequip[0].uid = uid;

	int ret = Load(vctequip);

	if (ret)
	{
		return ret;
	}

	if (0 == vctequip.size())
	{
		return R_ERR_NO_DATA;
	}

	//加载用户的所有装备数据
	//单个逐个加载
	for(int i = 0; i < vctequip.size(); ++i)
	{
		unsigned index = GetFreeIndex();

		if(index == -1)
		{
			error_log("[LoadBuff] get free index error. uid=%u", uid);
			return R_ERR_DATA;
		}

		m_data->data[index] = vctequip[i];  //给m_data内的数据赋值
		unsigned ud = vctequip[i].ud;

		if(m_data->MardLoad(index))
		{
			m_freeIndex.erase(index);
		}
		else
		{
			error_log("[LoadBuff] mark load failed. uid=%u,pid=%d.", uid, ud);
			return R_ERROR;
		}

		CreateSelfIndex(uid, vctequip[i].eqid, ud, index);
	}

	return 0;
}

void EquipmentManager::DoClear(unsigned uid)
{
	if(m_map.count(uid))
	{
		 map<uint32_t, uint32_t>::iterator miter = m_map[uid].begin();

		 for(; miter != m_map[uid].end(); )
		 {
			 Clear(miter->second);
			 m_map[uid].erase(miter++);
		 }

		 m_map.erase(uid);
		 m_mapequd.erase(uid);
	}
}

void EquipmentManager::DoSave(unsigned uid)
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

DataEquipment & EquipmentManager::GetEquipment(unsigned uid, unsigned ud, unsigned & index)
{
	if (!m_map.count(uid) || !m_map[uid].count(ud))
	{
		error_log("[GetEquipment] ud is not exists. uid=%u,ud=%u", uid, ud);
		throw std::runtime_error("get_equip_error");
	}

	index = m_map[uid][ud];

	return m_data->data[index];
}

DataEquipment & EquipmentManager::GetEquipmentNoIndex(unsigned uid, unsigned ud)
{
	if (!m_map.count(uid) || !m_map[uid].count(ud))
	{
		error_log("[GetEquipmentNoIndex] ud is not exists. uid=%u,ud=%u", uid, ud);
		throw std::runtime_error("get_equip_error");
	}

	unsigned index = m_map[uid][ud];

	return m_data->data[index];
}

bool EquipmentManager::IsEquipmentExists(unsigned uid, unsigned ud)
{
	if (!m_map.count(uid) || !m_map[uid].count(ud))
	{
		return false;
	}

	return true;
}

bool EquipmentManager::UpdateEquipment(unsigned index)
{
	return  m_data->MarkChange(index);
}

bool EquipmentManager::DeleteDBCEquipment(unsigned index)
{
	//mark删除状态
	m_data->MarkDel(index);

	//添加至操作队列
	AddSave(index);

	return true;
}

bool EquipmentManager::DeleteEquipment(DataEquipment & equip)
{
	unsigned uid = equip.uid;
	unsigned ud = equip.ud;

	if (!m_map.count(uid) || !m_map[uid].count(ud))
	{
		error_log("[DeleteEquipment] get equip error. uid=%u, id=%u", uid, ud);
		throw std::runtime_error("get_equip_error");
	}

	unsigned index = m_map[uid][ud];

	bool isSuccess = DeleteDBCEquipment(index);

	if (!isSuccess)
	{
		return false;
	}

	DeleteSelfIndex(uid, equip.eqid, ud);

	return true;
}

int EquipmentManager::GetOptionalEquipment(unsigned uid, vector<unsigned> & vctindexs)
{
	//遍历map
	if(m_map.count(uid))
	{
		 map<uint32_t, uint32_t>::iterator miter = m_map[uid].begin();

		 for(; miter != m_map[uid].end(); ++miter)
		 {
			 //排除已出售装备
			 if(0 == m_data->data[miter->second].heroid && 0 == m_data->data[miter->second].issold)
			 {
				 vctindexs.push_back(miter->second);
			 }
		 }
	}

	return 0;
}

DataEquipment &  EquipmentManager::GetEquipmentByIndex(unsigned index)
{
	if (index >= (DB_BASE_BUFF*DB_EQUIPMENT_FULL))
	{
		throw std::runtime_error("wrong index param");
	}

	return m_data->data[index];
}

int EquipmentManager::GetHeroEquipment(unsigned uid, unsigned heroid, vector<unsigned> & vctindexs)
{
	//遍历map
	if(m_map.count(uid))
	{
		 map<uint32_t, uint32_t>::iterator miter = m_map[uid].begin();

		 for(; miter != m_map[uid].end(); ++miter)
		 {
			 if(m_data->data[miter->second].heroid == heroid)
			 {
				 vctindexs.push_back(miter->second);
			 }
		 }
	}

	return 0;
}

int EquipmentManager::GetEquipments(unsigned uid, vector<unsigned> & vctindexs)
{
	//遍历map
	if(m_map.count(uid))
	{
		 map<uint32_t, uint32_t>::iterator miter = m_map[uid].begin();

		 for(; miter != m_map[uid].end(); ++miter)
		 {
			 if(m_data->data[miter->second].issold == false)
			 {
				 vctindexs.push_back(miter->second);
			 }
		 }
	}

	return 0;
}

int EquipmentManager::GetSoldEquipment(unsigned uid, vector<unsigned> & vctindexs)
{
	//遍历map
	if(m_map.count(uid))
	{
		 map<uint32_t, uint32_t>::iterator miter = m_map[uid].begin();

		 for(; miter != m_map[uid].end(); ++miter)
		 {
			 if(m_data->data[miter->second].issold)
			 {
				 vctindexs.push_back(miter->second);
			 }
		 }
	}

	return 0;
}

int EquipmentManager::GetEquipmentPid(unsigned eqid)
{
	return EquipCfgWrap().GetEquip(eqid).postion();
}

void EquipmentManager::GetHeroEquips(unsigned uid, unsigned heroid, std::vector<DataEquipment>& equips)
{
	equips.clear();
	//TODO
	std::vector<unsigned> vIndexs;
	int ret = GetHeroEquipment(uid, heroid, vIndexs);
	if (ret != 0)
	{
		error_log("get_hero_equips_error. uid=%u,heroid=%u", uid, heroid);
		throw std::runtime_error("get_hero_equips_index_error");
	}

	for (size_t i = 0; i < vIndexs.size(); ++i)
	{
		equips.push_back(m_data->data[vIndexs[i]]);
	}
}

int EquipmentManager::GetEquipmentConfig(unsigned uid, unsigned eqid, EquipConfInfo & equipinfo)
{
	if (!ConfigManager::Instance()->m_equipmap.count(eqid))
	{
		error_log("[GetEquipmentConfig] eqid not found in config. uid=%u, eqid=%u", uid, eqid);
		throw std::runtime_error("get_equip_error");
	}

	const EquipmentConfig::Equip& equipconfig = EquipCfgWrap().GetEquip(eqid);

	equipinfo.pid = equipconfig.postion();
	equipinfo.type = equipconfig.type();
	equipinfo.character = equipconfig.character();
	equipinfo.price = equipconfig.price();

	return 0;
}

bool EquipmentManager::IsAllowOverlay(unsigned eqid)
{
	//根据eqid获取配置文件中的叠加配置选项
	int limit = EquipCfgWrap().GetEquip(eqid).limitnum();

	return (limit > 1 ? true : false);
}

unsigned EquipmentManager::GetUserNextUd(unsigned uid, unsigned eqid, unsigned count)
{
	bool isoverlay = IsAllowOverlay(eqid);

	if (isoverlay)   //允许叠加
	{
		//可叠加的装备，对于后台来说，没有上限.对于可叠加的装备来说，一个eqid就只会有一份equd
		if (m_mapequd[uid].count(eqid))   //该物品已经存在
		{
			//遍历所有可用的ud，排除已出售的可叠加道具
			set<uint32_t>::iterator siter;

			for(siter = m_mapequd[uid][eqid].begin(); siter != m_mapequd[uid][eqid].end(); ++siter)
			{
				//获取装备信息
				unsigned equd = *siter;
				unsigned index = m_map[uid][equd];

				if (!m_data->data[index].issold)  //未出售，可用
				{
					return equd;
				}
			}
		}
	}

	m_userMaxEqud[uid] = m_userMaxEqud[uid] + 1;  //自增当前的ud

	return m_userMaxEqud[uid];
}

int EquipmentManager::CreateSelfIndex(unsigned uid, unsigned eqid, unsigned equd, unsigned index)
{
	m_map[uid][equd] = index;
	m_mapequd[uid][eqid].insert(equd);

	return 0;
}

int EquipmentManager::DeleteSelfIndex(unsigned uid, unsigned eqid, unsigned equd)
{
	m_map[uid].erase(equd);  //清除映射
	m_mapequd[uid][eqid].erase(equd);

	if (m_mapequd[uid][eqid].empty())
	{
		m_mapequd[uid].erase(eqid);
	}

	return 0;
}

int EquipmentManager::FullMessage(unsigned uid, User::User* reply)
{
	//加载数据
	map<uint32_t, uint32_t>::iterator miter = m_map[uid].begin();

	for(; miter != m_map[uid].end(); ++miter)
	{
		unsigned index = miter->second;

		DataCommon::EquipmentCPP * equip = reply->add_equip();
		m_data->data[index].SetMessage(equip);
	}

	return 0;
}
