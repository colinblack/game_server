/*
 * MessageManager.h
 *
 *  Created on: 2018年9月13日
 *      Author: colin
 */

#ifndef APP_DATA_POSTMANAGER_H_
#define APP_DATA_POSTMANAGER_H_

#include "Kernel.h"


struct RandomUserItem
{
	unsigned uid, id, ts, type;
	char content[NOTIFY_CONTENT_LEN];

	RandomUserItem():
		uid(0),
		id(0),
		ts(0),
		type(0)
	{
		memset(content, 0 , sizeof (content));
	}

	void Clear()
	{
		uid = id = ts = type = 0;
		memset(content, 0 , sizeof (content));
	}

	void SetMessage(ProtoNotify::RandomUserItemCPP * msg)
	{
		msg->set_id(id);
		msg->set_ts(ts);
		msg->set_uid(uid);
		msg->set_type(type);
		msg->set_content(content);
	}
};


struct PropItem
{
	unsigned propid;
	unsigned count;

	PropItem():
		propid(0)
		,count(0)
	{
	}
};


struct MartialClubItem
{
	unsigned uid, id, type, ts, uuid, level, grade, slot, coin, win;
	char name[BASE_NAME_LEN];
	char fig[BASE_FIG_LEN];
	PropItem pros[MARTIAL_CLUB_REAP_PROPS];

	MartialClubItem():
		 uid(0)
		,id(0)
		,type(0)
		,ts(0)
		,uuid(0)
		,level(0)
		,grade(0)
		,slot(0)
		,coin(0)
		,win(0)
	{
		memset(name, 0, sizeof(name));
		memset(fig, 0, sizeof(fig));
	}

	void Clear()
	{
		id = type = ts = uid = uuid = level = grade = slot = coin = win = 0;
		memset(name, 0, sizeof(name));
		memset(fig, 0, sizeof(fig));
	}

	void SetMessage(ProtoNotify::MartialClubItemCpp* msg)
	{
		msg->set_id(id);
		msg->set_type(type);
		msg->set_ts(ts);
		msg->set_uid(uuid);
		msg->set_level(level);
		msg->set_grade(grade);
		msg->set_slot(slot);
		msg->set_coin(coin);
		msg->set_name(name);
		msg->set_fig(fig);
		msg->set_win(win);

		for(int i = 0; i < MARTIAL_CLUB_REAP_PROPS; ++i)
		{
			auto p = msg->add_props();
			p->set_count(pros[i].count);
			p->set_propid(pros[i].propid);
		}
	}

};


struct PostData
{
	RandomUserItem item1[DB_BASE_BUFF*PER_USER_MAX_POST];
	MartialClubItem item2[DB_BASE_BUFF*PER_USER_MAX_POST];
	MartialClubItem item3[DB_BASE_BUFF*PER_USER_MAX_POST];
};

typedef map<unsigned, map<unsigned, unsigned>> PostMap;

class PostManager : public MemorySingleton<PostData, MEMORY_POST>, public CSingleton<PostManager>
{
private:
	friend class CSingleton<PostManager>;
	PostManager(){};
	virtual ~PostManager(){}

	set<unsigned> m_freeIndex[e_Post_max];
	PostMap m_map[e_Post_max];

	static const int MAX_SIZE = DB_BASE_BUFF*PER_USER_MAX_POST;

public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();

	const PostMap& GetMap(PostType type){return m_map[(int)type];}

	bool IsFull()
	{
		if(m_freeIndex[e_Post_randomUser].size() < 1000)
			return true;
		if(m_freeIndex[e_Post_inviteUser].size() < 1000)
			return true;
		if(m_freeIndex[e_post_martialBattle].size() < 1000)
			return true;

		return false;
	}

	unsigned GetFreeIndex(PostType type)
	{
		if(m_freeIndex[(int)type].empty())
			return -1;
		return *(m_freeIndex[(int)type].begin());
	}

	void Del(unsigned uid)
	{
		if(m_map[e_Post_randomUser].count(uid))
		{
			for(map<unsigned, unsigned>::iterator it = m_map[e_Post_randomUser][uid].begin(); it!=m_map[e_Post_randomUser][uid].end(); ++it)
			{
				m_data->item1[it->second].Clear();
				m_freeIndex[e_Post_randomUser].insert(it->second);
			}
			m_map[e_Post_randomUser][uid].clear();
			m_map[e_Post_randomUser].erase(uid);
		}

		if(m_map[e_Post_inviteUser].count(uid))
		{
			for(map<unsigned, unsigned>::iterator it = m_map[e_Post_inviteUser][uid].begin(); it!=m_map[e_Post_inviteUser][uid].end(); ++it)
			{
				m_data->item2[it->second].Clear();
				m_freeIndex[e_Post_inviteUser].insert(it->second);
			}
			m_map[e_Post_inviteUser][uid].clear();
			m_map[e_Post_inviteUser].erase(uid);
		}
		if(m_map[e_post_martialBattle].count(uid))
		{
			for(map<unsigned, unsigned>::iterator it = m_map[e_post_martialBattle][uid].begin(); it!=m_map[e_post_martialBattle][uid].end(); ++it)
			{
				m_data->item3[it->second].Clear();
				m_freeIndex[e_post_martialBattle].insert(it->second);
			}
			m_map[e_post_martialBattle][uid].clear();
			m_map[e_post_martialBattle].erase(uid);
		}

	}

	void DelItem(unsigned uid, unsigned id, PostType type)
	{
		if(m_map[type].count(uid) && m_map[type][uid].count(id))
		{
			unsigned index = m_map[type][uid][id];
			if(e_Post_randomUser == type)
				m_data->item1[index].Clear();
			else if(e_Post_inviteUser == type)
				m_data->item2[index].Clear();
			else if(e_post_martialBattle == type)
				m_data->item3[index].Clear();

			m_freeIndex[type].insert(index);
			m_map[type][uid].erase(id);
		}
	}

	void Clear()
	{
		for(int i = 0; i < e_Post_max; ++i)
		{
			m_map[i].clear();
			m_freeIndex[i].clear();

			for(int j = 0; j < MAX_SIZE; ++j)
			{
				if(e_Post_randomUser == j)
					m_data->item1[i].Clear();
				else if(e_Post_inviteUser == j)
					m_data->item2[i].Clear();
				else if(e_post_martialBattle == j)
					m_data->item3[i].Clear();

				m_freeIndex[i].insert(j);
			}
		}
	}


	int Add(unsigned uid , MartialClubItem& item)
	{
		unsigned type = item.type;

		unsigned i = GetFreeIndex((PostType)type);
		if(i == (unsigned)-1)
			return R_ERR_DATA;

		m_freeIndex[type].erase(i);
		m_map[type][uid][i] = i;

		debug_log("------------ uid: %u, uuid: %u, i: %u, slot: %u, type: %u -------- ", uid, item.uuid, i, item.slot, type);
		if(type == e_Post_inviteUser)
		{
			m_data->item2[i].uid = uid;
			m_data->item2[i].id = i;
			m_data->item2[i].ts = item.ts;
			m_data->item2[i].uuid = item.uuid;
			m_data->item2[i].type = type;
			m_data->item2[i].level = item.level;
			m_data->item2[i].grade = item.grade;
			m_data->item2[i].slot= item.slot;
			m_data->item2[i].coin = item.coin;

			memcpy(m_data->item2[i].name, item.name, sizeof(m_data->item2[i].name));
			memcpy(m_data->item2[i].fig, item.fig, sizeof(m_data->item2[i].fig));

			for(int j = 0; j < MARTIAL_CLUB_REAP_PROPS; ++j)
			{
				m_data->item2[i].pros[j].count = item.pros[j].count;
				m_data->item2[i].pros[j].propid = item.pros[j].propid;
			}
		}
		if(type == e_post_martialBattle)
		{
			m_data->item3[i].uid = uid;
			m_data->item3[i].id = i;
			m_data->item3[i].ts = item.ts;
			m_data->item3[i].uuid = item.uuid;
			m_data->item3[i].type = type;
			m_data->item3[i].level = item.level;
			m_data->item3[i].grade = item.grade;
			m_data->item3[i].slot= item.slot;
			m_data->item3[i].coin = item.coin;
			m_data->item3[i].win = item.win;

			memcpy(m_data->item3[i].name, item.name, sizeof(m_data->item3[i].name));
			memcpy(m_data->item3[i].fig, item.fig, sizeof(m_data->item3[i].fig));

			for(int j = 0; j < MARTIAL_CLUB_REAP_PROPS; ++j)
			{
				m_data->item3[i].pros[j].count = item.pros[j].count;
				m_data->item3[i].pros[j].propid = item.pros[j].propid;
			}
		}

		return 0;
	}

	int Add(unsigned uid, RandomUserItem& item)
	{
		unsigned type = item.type;

		unsigned i = GetFreeIndex((PostType)type);
		if(i == (unsigned)-1)
			return R_ERR_DATA;

		m_freeIndex[type].erase(i);
		m_map[type][uid][i] = i;
		m_data->item1[i].uid = uid;
		m_data->item1[i].id = i;
		m_data->item1[i].ts = item.ts;
		m_data->item1[i].type = type;

		memcpy(m_data->item1[i].content, item.content, sizeof(m_data->item1[i].content));

		return 0;
	}

	bool Has(unsigned uid, unsigned id, PostType type)
	{
		if (m_map[type].count(uid) && m_map[type][uid].count(id))
		{
			return true;
		}

		return false;
	}

	MartialClubItem& GetInviteMartial(unsigned uid, unsigned id)
	{
		if(m_map[e_Post_inviteUser].count(uid) && m_map[e_Post_inviteUser][uid].count(id))
			return m_data->item2[m_map[e_Post_inviteUser][uid][id]];

		throw runtime_error("pos_not_exist");
	}

	MartialClubItem& GetMartialBattle(unsigned uid, unsigned id)
	{
		if(m_map[e_post_martialBattle].count(uid) && m_map[e_post_martialBattle][uid].count(id))
			return m_data->item3[m_map[e_post_martialBattle][uid][id]];

		throw runtime_error("pos_not_exist");
	}

};


#endif /* APP_DATA_POSTMANAGER_H_ */
