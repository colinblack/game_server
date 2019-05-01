
#ifndef MEMORY_OPERA_BATTLE_MANAGER_H_
#define MEMORY_OPERA_BATTLE_MANAGER_H_

#include "Kernel.h"

//剧本战记录
struct MemoryRecord
{
	uint8_t kingdom;
	char name[BASE_NAME_LEN];
	unsigned left_time;


	MemoryRecord():
		kingdom(0),
		left_time(0)
	{
		memset(name, 0, sizeof(name));
	}

	bool operator < (MemoryRecord & oth)
	{
		return left_time < oth.left_time;
	}

	void SetMessage(ProtoOperaBattle::MemoryRecordCPP *msg)
	{
		msg->set_kingdom(kingdom);
		msg->set_left_time(left_time);
		msg->set_name(name);
	}

	void Replace(MemoryRecord & oth)
	{
		if (this == &oth)
		{
			;
		}
		else
		{
			kingdom = oth.kingdom;
			left_time = oth.left_time;

			memset(name, 0, sizeof(name));
			sprintf(name, "%s", oth.name);
		}
	}
};

struct MemoryBattleInfo
{
	unsigned gateid;
	MemoryRecord battle_record[MAX_DIFFICULTY];

	MemoryBattleInfo():
		gateid(0)
	{

	}

	void SetMessage(ProtoOperaBattle::MemoryBattleRecordCPP * msg)
	{
		msg->set_gateid(gateid);
		//设置难度记录
		for(int i = 0; i < MAX_DIFFICULTY; ++i)
		{
			battle_record[i].SetMessage(msg->add_diff_record());
		}
	}
};

struct MemoryOperaBattleAllInfo
{
	MemoryBattleInfo data[MAX_BATTLE_NUM];
};

class MemoryOperaBattleManager : public MemorySingleton<MemoryOperaBattleAllInfo, MEMORY_OPERA_BATTLE>, public CSingleton<MemoryOperaBattleManager>
{
private:
	friend class CSingleton<MemoryOperaBattleManager>;
	MemoryOperaBattleManager(){};
	virtual ~MemoryOperaBattleManager(){}
public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();

	MemoryBattleInfo& GetBattleInfo(unsigned gateid);

	MemoryRecord & GetRecord(unsigned gateid, unsigned diff);

	void GetIndexs(vector<unsigned> & indexs)
	{
		for(map<unsigned, unsigned>::iterator uiter = m_map.begin(); uiter != m_map.end(); ++uiter)
		{
			indexs.push_back(uiter->second);
		}
	}

	unsigned GetFreeIndex()
	{
		if(m_freeIndex.empty())
			return -1;
		return *(m_freeIndex.begin());
	}

	int Add(unsigned gateid)
	{
		unsigned i = GetFreeIndex();

		if(i == (unsigned)-1)
			return R_ERR_DATA;

		m_freeIndex.erase(i);

		m_map[gateid] = i;
		m_data->data[i].gateid = gateid;

		return 0;
	}

	bool IsGateExist(unsigned gateid)
	{
		if(m_map.count(gateid))
			return true;

		return false;
	}

	unsigned GetIndex(unsigned gateid)
	{
		if(m_map.count(gateid))
			return m_map[gateid];

		return -1;
	}

private:
	set<unsigned> m_freeIndex;
	map<unsigned, unsigned> m_map;
};


#endif //MEMORY_OPERA_BATTLE_MANAGER_H_
