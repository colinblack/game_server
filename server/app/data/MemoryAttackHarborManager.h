#ifndef MEMORY_ATTACK_HARBOR_MANAGER_H_
#define MEMORY_ATTACK_HARBOR_MANAGER_H_

#include "Kernel.h"

struct MemoryAttackRecord
{
	uint8_t kingdom;
	unsigned uid;
	unsigned wreckage;

	MemoryAttackRecord():
		kingdom(0),
		uid(0),
		wreckage(0)
	{

	}

	void Clear()
	{
		kingdom = 0;
		uid = 0;
		wreckage = 0;
	}
};

struct MemoryAttackRecordAllInfo
{
	unsigned refreshts;  //上次npc刷新的时间
	MemoryAttackRecord data[MEMORY_HERO_PROPERTY_NUM];
};

class MemoryAttackHarborManager : public MemorySingleton<MemoryAttackRecordAllInfo, MEMORY_ATTACK_HARBOR>, public CSingleton<MemoryAttackHarborManager>
{
private:
	friend class CSingleton<MemoryAttackHarborManager>;
	MemoryAttackHarborManager(){};
	virtual ~MemoryAttackHarborManager(){}
public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();

	int AddWreckage(unsigned uid, uint8_t kingdom, unsigned count);

	//计算国家排名和王牌.singlecount-单次增加的数量
	int CalcuteCountry(unsigned singlecount, MemoryAttackRecord & record);

	const map<unsigned, unsigned>& GetMap() {return m_map;}

	void GetIndexs(vector<unsigned> & indexs)
	{
		for(map<unsigned, unsigned>::iterator uiter = m_map.begin(); uiter != m_map.end(); ++uiter)
		{
			indexs.push_back(uiter->second);
		}
	}

	void ClearIndexs()
	{
		for(map<unsigned, unsigned>::iterator uiter = m_map.begin(); uiter != m_map.end(); ++uiter)
		{
			m_freeIndex.insert(uiter->second);
		}

		m_map.clear();
	}

	unsigned GetLastRefreshts()
	{
		return m_data->refreshts;
	}

	void SetLastRefreshts(unsigned ts)
	{
		m_data->refreshts = ts;
	}

	void ClearBeforeAttack()
	{
		//副本开始前重置
		m_kwreckage.clear();
		m_kindom_trump.clear();
		memset(m_data->data, 0, sizeof(m_data->data));

		ClearIndexs();
	}

	unsigned GetFreeIndex()
	{
		if(m_freeIndex.empty())
			return -1;
		return *(m_freeIndex.begin());
	}

	int Add(unsigned uid)
	{
		unsigned i = GetFreeIndex();

		if(i == (unsigned)-1)
			return R_ERR_DATA;

		m_freeIndex.erase(i);

		m_map[uid] = i;
		m_data->data[i].uid = uid;

		return 0;
	}

	bool IsUserExist(unsigned uid)
	{
		if(m_map.count(uid))
			return true;

		return false;
	}

	unsigned GetIndex(unsigned uid)
	{
		if(m_map.count(uid))
			return m_map[uid];

		return -1;
	}

	void DoClear(unsigned uid)
	{
		if (m_map.count(uid))
		{
			unsigned index = m_map[uid];
			m_data->data[index].Clear();

			//释放空间
			m_map.erase(uid);
			m_freeIndex.insert(index);
		}
	}
public:
	map<uint8_t, unsigned> m_kwreckage; //记录每个国家总的残骸数. kingdom->残骸
	map<uint8_t, pair<unsigned, unsigned> > m_kindom_trump;  //国家王牌. kingdom->(uid,残骸)
private:
	set<unsigned> m_freeIndex;
	map<unsigned, unsigned> m_map;
};


#endif //MEMORY_ATTACK_HARBOR_MANAGER_H_
