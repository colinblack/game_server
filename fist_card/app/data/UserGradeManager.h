/*
 * UserGradeManager.h
 *
 *  Created on: 2018年8月7日
 *      Author: colin
 */

#ifndef APP_DATA_USERGRADEMANAGER_H_
#define APP_DATA_USERGRADEMANAGER_H_

#include "Kernel.h"

struct UserGradeItem
{
	unsigned uid;
	unsigned grade;	//段位
	unsigned score; //积分
	unsigned daily_score; //每日积分
	bool	 win_record[RECORD_GRADE_LEN]; //连胜纪录
	unsigned win;	//胜利累计次数
	unsigned daily_reward_ts; //每日奖励时戳
	unsigned refresh_cnt;	//挑战玩家刷新次数
	unsigned battle_cnt;	//战斗次数

	void Clear()
	{
		grade = 1;
		score = 0;
		daily_score = 0;
		memset(win_record, 0, sizeof(win_record));
		daily_reward_ts = 0;
		refresh_cnt = 0;
	}

	void IncWin()
	{
		++win;
	}

	unsigned Win()
	{
		return win;
	}

	void ClearWin()
	{
		win = 0;
	}

	bool Streaking(int index)
	{
		return win_record[index];
	}

	void Streaking(int index, bool flag)
	{
		win_record[index] = flag;
	}

	UserGradeItem() : uid(0), grade(1), score(0), daily_score(0), win(0), daily_reward_ts(0), refresh_cnt(0), battle_cnt(0)
	{
		memset(win_record, false, sizeof(win_record));
	}


	void SetMessage(ProtoBattle::ProtoGradeBattleResult* msg)
	{
		msg->set_grade(grade);
		msg->set_score(score);
		msg->set_dailyscore(daily_score);
	}

};

struct UserGrades
{
	unsigned season_ts;	//赛季重置时戳
	UserGradeItem item[MEMORY_PROPERTY_NUM];
	UserGrades() : season_ts(0)
	{
	}

	void Parse(const UserGrade::Grade& msg)
	{
		for(int i = 0; i < msg.users_size() && i < MEMORY_PROPERTY_NUM; ++i)
		{
			item[i].grade = msg.users(i).grade();
			item[i].score = msg.users(i).score();
			item[i].daily_score	= msg.users(i).dailyscore();
			item[i].win	  = msg.users(i).win();
			item[i].daily_reward_ts	= msg.users(i).dailyrewardts();
			for(int j = 0; j < RECORD_GRADE_LEN; ++j)
			{
				item[i].win_record[j] = msg.users(i).winrecord(j);
			}
		}
	}

	void Serialize(UserGrade::Grade* msg)
	{
		for(int i = 0; i < MEMORY_PROPERTY_NUM; ++i)
		{
			auto p = msg->add_users();
			p->set_grade(item[i].grade);
			p->set_score(item[i].score);
			p->set_dailyscore(item[i].daily_score);
			p->set_win(item[i].win);
			p->set_dailyrewardts(item[i].daily_reward_ts);
			for(int j = 0; j < RECORD_GRADE_LEN; ++j)
			{
				p->add_winrecord(item[i].win_record[j]);
			}
		}
	}
};


class UserGradeManager : public ProtoMemorySingleton<UserGrades, MEMORY_USER_GRADE, UserGrade::Grade>, public CSingleton<UserGradeManager>
{
private:
	friend class CSingleton<UserGradeManager>;
	UserGradeManager(){};
	virtual ~UserGradeManager(){}
	set<unsigned> m_freeIndex;
	set<unsigned> m_perGradeIndex[USER_GRADE_INDEX];
	map<unsigned, unsigned> m_map;
public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit()
	{
		for(unsigned i=0;i < MEMORY_PROPERTY_NUM;++i)
		{
			if(m_data->item[i].uid != 0)
			{
				m_map[m_data->item[i].uid] = i;
				m_perGradeIndex[m_data->item[i].grade-1].insert(m_data->item[i].uid);
			}
			else
				m_freeIndex.insert(i);
		}
		if(0 == m_data->season_ts)
			m_data->season_ts = Time::GetGlobalTime();
		else
		{
			unsigned now = Time::GetGlobalTime();
			unsigned gap = (unsigned)ceil((now - m_data->season_ts) / 86400);
			if(gap > GRADE_SEASON)
			{
				//重置
				m_data->season_ts = Time::GetGlobalTime();
			}
		}
		return 0;
	};

	const map<unsigned, unsigned>& GetMap() {return m_map;}

	unsigned GetFreeCount()
	{
		return m_freeIndex.size();
	}

	unsigned GetFreeIndex()
	{
		if(m_freeIndex.empty())
			return -1;
		return *(m_freeIndex.begin());
	}

	bool IsNeedClear()
	{
		return GetFreeCount() * 10 / MEMORY_PROPERTY_NUM <= 1;
	}

	void DoClear(unsigned uid)
	{
		if(m_map.count(uid))
		{
			unsigned i = m_map[uid];
			unsigned idx = m_data->item[i].grade - 1;
			memset(&(m_data->item[i]), 0, sizeof(UserGradeItem));
			m_perGradeIndex[idx].erase(i);
			m_freeIndex.insert(i);
			m_map.erase(uid);
		}
	}

	void UpdateGradeIndex(unsigned uid, int oldIdx, int newIdx)
	{
		if(oldIdx < 0 || newIdx < 0)
			return ;
		if(m_perGradeIndex[oldIdx].count(uid) != 0)
			m_perGradeIndex[oldIdx].erase(uid);

		if(m_perGradeIndex[newIdx].count(uid) == 0)
			m_perGradeIndex[newIdx].insert(uid);
	}

	void Reset()
	{
		if(NewSeason())
		{

			m_data->season_ts =  Time::GetGlobalTime();
			for(unsigned i = 0; i < MEMORY_PROPERTY_NUM; ++i)
			{
				m_data->item[i].Clear();
			}
		}
		else
		{
			for(unsigned i = 0; i < MEMORY_PROPERTY_NUM; ++i)
			{
				m_data->item[i].daily_score = 0;
			}
		}
	}

	bool NewSeason()
	{
		unsigned now =  Time::GetGlobalTime();
		unsigned gap = (unsigned)ceil((now - m_data->season_ts) / 86400);
		if(gap > GRADE_SEASON)
			return true;
		return false;
	}

	unsigned GetIndex(unsigned uid)
	{
		if(m_map.count(uid))
			return m_map[uid];
		return -1;
	}

	int Add(unsigned uid)
	{
		unsigned i = GetFreeIndex();
		if(i == (unsigned)-1)
			return R_ERR_DATA;
		m_freeIndex.erase(i);
		m_map[uid] = i;
		m_perGradeIndex[0].insert(uid);
		m_data->item[i].uid = uid;
		m_data->item[i].grade = 1;
		m_data->item[i].score = 0;
		return 0;
	}

	//随机获取真玩家
	unsigned GetUserRandom(unsigned uid, int idx)
	{
		unsigned ret = 0;
		if(idx < 0 || idx >= USER_GRADE_INDEX)
			return 0;
		if(m_perGradeIndex[idx].empty())
			return 0;

		if(m_perGradeIndex[idx].size() == 1 && m_perGradeIndex[idx].count(uid) >0)
			return 0;

		bool self = false;
		if(m_perGradeIndex[idx].count(uid) > 0)
		{
			self = true;
			m_perGradeIndex[idx].erase(uid);
		}
		auto iter = m_perGradeIndex[idx].begin();
		int offest = Math::GetRandomInt(m_perGradeIndex[idx].size());
		advance(iter, offest);
		ret = *iter;

		if(self)
			m_perGradeIndex[idx].insert(uid);

		return ret;
	}

	//随机获取假玩家或真玩家
	unsigned GetUserRandom(unsigned uid, unsigned grade, unsigned cfgSize)
	{
		if(grade < 1 || grade > USER_GRADE_INDEX)
			return -1;
		bool self = false;
		if(m_perGradeIndex[grade-1].count(uid) != 0)
		{
			self = true;
			m_perGradeIndex[grade-1].erase(uid);
		}


		int size1 = m_perGradeIndex[grade-1].size();
		int size2 = cfgSize;


		unsigned ret = 0;
		int pos = Math::GetRandomInt(size1+size2);
		if(pos  > size1-1)
		{
			ret = pos - size1;
		}
		else
		{
			auto iter = m_perGradeIndex[grade-1].begin();
			advance(iter, pos);
			ret = *iter;
		}


		if(self)
			m_perGradeIndex[grade-1].insert(uid);

		return ret;
	}
};



#endif /* APP_DATA_USERGRADEMANAGER_H_ */
