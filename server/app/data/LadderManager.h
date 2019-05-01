/*
 * LadderManager.h
 *
 *  Created on: 2016-10-19
 *      Author: Ralf
 */

#ifndef LADDERMANAGER_H_
#define LADDERMANAGER_H_


#include "Kernel.h"

struct LadderItem
{
	unsigned uid;
	int		 enemy[LADDER_ENEMY]; //-1没有对手 对手名次
	LadderItem()
	{
		uid = 0;
		memset(enemy,0,sizeof(enemy));
	}

	void ClearEnemy()
	{
		for (int i = 0; i < LADDER_ENEMY; ++i)
		{
			enemy[i] = -1;
		}
	}

	void ResetEnemy()
	{
		memset(enemy,0,sizeof(enemy));
	}

	bool IsInitValue() const
	{
		for (int i = 0; i < LADDER_ENEMY; i++)
		{
			if (enemy[i] > 0) return false;
		}

		return true;
	}

};
struct LadderKingdom
{
	LadderItem  item[LADDER_ITEM];
	unsigned reward[LADDER_ITEM];

	LadderKingdom()
	{
		memset(reward, 0, sizeof(reward));
	}

	void ResetReward()
	{
		memset(reward, 0, sizeof(reward));
	}
};
struct LadderData
{
	LadderKingdom ladder/*[SG17_KINGDOM]*/;
	unsigned ts;
	LadderData()
	{
		//memset(ladder,0,sizeof(ladder));
		ts = 0;
	}
};
/************************************************/
class LadderManager : public MemorySingleton<LadderData, MEMORY_LADDER>, public CSingleton<LadderManager>
{
private:
	friend class CSingleton<LadderManager>;
	LadderManager(){};
	virtual ~LadderManager(){}

	void OnReward();

	//map<unsigned, map<unsigned, unsigned> > m_laddermap, m_rewardmap;
	map<unsigned, unsigned> m_laddermap, m_rewardmap;
public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();
	void OnHour();
	void OnDay();
	int GetRank(unsigned kingdom, unsigned uid)
	{
		if (m_laddermap.count(uid))
		{
			return m_laddermap[uid];
		}
		return -1;
	}
	int GetReward(unsigned kingdom, unsigned uid)
	{
		if(m_rewardmap.count(uid))
		{
			return m_rewardmap[uid];
		}
		return -1;
	}

	void SetRankMap(unsigned kingdom, unsigned uid, unsigned rank)
	{
		if (uid > 0)
		{
			m_laddermap[uid] = rank;
		}
	}

	//rank 0-(LADDER_ITEM - 1)
	LadderItem& GetLadderItem(int kingdom, int rank);
	const map<unsigned, unsigned>& GetRewardMap() const
	{
		return m_rewardmap;
	}
};

#endif /* LADDERMANAGER_H_ */
