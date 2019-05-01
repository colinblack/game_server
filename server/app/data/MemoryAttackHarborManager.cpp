#include "MemoryAttackHarborManager.h"

int MemoryAttackHarborManager::OnInit()
{
	for(unsigned i = 0; i < MEMORY_HERO_PROPERTY_NUM;++i)
	{
		if(m_data->data[i].uid != 0)
		{
			m_map[m_data->data[i].uid] = i;
			CalcuteCountry(m_data->data[i].wreckage, m_data->data[i]);
		}
		else
		{
			m_freeIndex.insert(i);
		}
	}

	return 0;
}

int MemoryAttackHarborManager::AddWreckage(unsigned uid, uint8_t kingdom, unsigned count)
{
	bool isexist = IsUserExist(uid);

	if (!isexist)
	{
		//用户的相关战斗记录不存在，新添加
		int ret = Add(uid);

		if (ret)
		{
			error_log("Add user attack record failed. uid=%u,ret=%d", uid, ret);
			return R_ERROR;
		}
	}

	unsigned index = GetIndex(uid);

	//先将残骸数加上
	MemoryAttackRecord & record = m_data->data[index];
	record.kingdom = kingdom;
	record.wreckage += count;

	//处理国家残骸排行
	CalcuteCountry(count, record);

	return 0;
}

int MemoryAttackHarborManager::CalcuteCountry(unsigned singlecount, MemoryAttackRecord & record)
{
	//将数量值加入到对应国家的残骸数中
	unsigned kingdom = record.kingdom;
	unsigned count = record.wreckage;
	unsigned uid = record.uid;

	m_kwreckage[kingdom] += singlecount;

	//比较当前国家的王牌
	if (m_kindom_trump.count(kingdom))
	{
		//先判断是否是自己与自己比较
		if (m_kindom_trump[kingdom].first == uid)
		{
			//自己本身
			m_kindom_trump[kingdom].second = record.wreckage;
		}
		else if(m_kindom_trump[kingdom].second < record.wreckage)  //不同人之间的比较
		{
			//挑战者更勇猛，替换
			m_kindom_trump[kingdom].first = uid;
			m_kindom_trump[kingdom].second = record.wreckage;
		}
	}
	else  //之前没有数据，则直接新增
	{
		m_kindom_trump[kingdom].first = uid;
		m_kindom_trump[kingdom].second = record.wreckage;
	}

	return 0;
}
