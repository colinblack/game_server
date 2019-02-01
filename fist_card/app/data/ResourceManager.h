/*
 * ResourceManager.h
 *
 *  Created on: 2016-9-2
 *      Author: Ralf
 */

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include "Kernel.h"

/***************************************************/

struct SkillInfo
{
	unsigned id;
	unsigned type;
	double 	 hurt;
	double	 multiple;
	unsigned initWeight;
	unsigned userAddWeight;

	SkillInfo() : id(0),type(0), hurt(0.0), multiple(0.0), initWeight(0), userAddWeight(0)
	{
	}
};

struct AttrInfo
{
	double hp;
	double att;
	double def;
	unsigned speed; //先手
	unsigned adodge;//命中
	unsigned dodge;//闪避
	unsigned crit; //暴击
	double   critt; //暴击伤害
	unsigned acrit; //抗暴击
	double  battlePower; //战力

	AttrInfo() : hp(0.0), att(0.0), def(0.0), speed(0), adodge(0), dodge(0),
			crit(0), critt(0.0), acrit(0), battlePower(0.0)
	{
	}
};

struct HeroInfo
{
	unsigned id;
	AttrInfo attr; //英雄属性
	SkillInfo skills[e_skill_max]; //技能

	HeroInfo():id(0)
	{
	}
};

struct OfflineResourceItem
{
	unsigned uid;
	unsigned level;
	unsigned viplevel;
	unsigned alliance_id;
	char name[BASE_NAME_LEN];//玩家名字
	char fig[BASE_FIG_LEN];//头像
	HeroInfo heros[MAX_FORMATION_HERO];
	unsigned props[MAX_BATTLE_PROPS];
	unsigned ts;//内容变化时戳
	unsigned last_login_time; //上次登录时间

	OfflineResourceItem():
		uid(0), level(0), viplevel(0), alliance_id(0), ts(0), last_login_time(0)
	{
		memset(name, 0, sizeof(name));
		memset(fig, 0, sizeof(fig));
	}

	bool CanClear()
	{
		return ts + 86400*7 < Time::GetGlobalTime();
	}

	void Parse(const Offline::User &msg)
	{
		if(msg.has_uid())
			uid = msg.uid();
		if(msg.has_level())
			level = msg.level();
		if(msg.has_viplevel())
			viplevel = msg.viplevel();
		if(msg.has_allianceid())
			alliance_id = msg.allianceid();
		if(msg.has_ts())
			ts = msg.ts();
		if(msg.has_lastlogintime())
			last_login_time = msg.lastlogintime();
		if(msg.has_name())
			memcpy(name, msg.name().c_str(), BASE_NAME_LEN);
		if(msg.has_fig())
			memcpy(fig, msg.fig().c_str(), BASE_FIG_LEN);
		for(int i = 0; i < msg.heros_size() && i < MAX_FORMATION_HERO; ++i)
			Parse(msg.heros(i), heros[i]);
		for(int i = 0; i < msg.props_size() && i < MAX_BATTLE_PROPS; ++i)
			props[i] = msg.props(i);
	}

	void Parse(const Offline::Hero &msg, HeroInfo & heros)
	{
		if(msg.has_id())
			heros.id = msg.id();
		if(msg.attr().has_hp())
			heros.attr.hp	=  msg.attr().hp();
		if(msg.attr().has_att())
			heros.attr.att	=  msg.attr().att();
		if(msg.attr().has_def())
			heros.attr.def	=  msg.attr().def();
		if(msg.attr().has_first())
			heros.attr.speed	=  msg.attr().first();
		if(msg.attr().has_hit())
			heros.attr.adodge	=  msg.attr().hit();
		if(msg.attr().has_dodge())
			heros.attr.dodge	=  msg.attr().dodge();
		if(msg.attr().has_critstrike())
			heros.attr.crit	=  msg.attr().critstrike();
		if(msg.attr().has_critrate())
			heros.attr.critt	=  msg.attr().critrate();
		if(msg.attr().has_critresist())
			heros.attr.acrit	=  msg.attr().critresist();
		if(msg.attr().has_battlepower())
			heros.attr.battlePower = msg.attr().battlepower();

		for(int i = 0; i < msg.skills_size() && i < e_skill_max; ++i)
			Parse(msg.skills(i), heros.skills[i]);
	}

	void Parse(const Offline::Skill &msg, SkillInfo &skill)
	{
		if(msg.has_id())
			skill.id = msg.id();
		if(msg.has_type())
			skill.type = msg.type();
		if(msg.has_hurt())
			skill.hurt = msg.hurt();
		if(msg.has_multiple())
			skill.multiple = msg.multiple();
		if(msg.has_initweight())
			skill.initWeight = msg.initweight();
		if(msg.has_useraddweight())
			skill.userAddWeight = msg.useraddweight();
	}

	void Serialize(Offline::User *msg)
	{
		msg->set_uid(uid);
		msg->set_level(level);
		msg->set_viplevel(viplevel);
		msg->set_allianceid(alliance_id);
		msg->set_ts(ts);
		msg->set_name(string(name));
		msg->set_fig(string(fig));
		msg->set_lastlogintime(last_login_time);
		for(int i = 0; i < MAX_FORMATION_HERO; ++i)
			Serialize(msg->add_heros(), heros[i]);
		for(int i = 0; i < MAX_BATTLE_PROPS; ++i)
			msg->add_props(props[i]);
	}

	void Serialize(Offline::Hero *msg, HeroInfo & heros)
	{
		msg->set_id(heros.id);
		auto p = msg->mutable_attr();
		p->set_hp(heros.attr.hp);
		p->set_att(heros.attr.att);
		p->set_def(heros.attr.def);
		p->set_first(heros.attr.speed);
		p->set_hit(heros.attr.adodge);
		p->set_dodge(heros.attr.dodge);
		p->set_critstrike(heros.attr.crit);
		p->set_critrate(heros.attr.critt);
		p->set_critresist(heros.attr.acrit);
		p->set_battlepower(heros.attr.battlePower);

		for(int i = 0; i < e_skill_max; ++i)
			Serialize(msg->add_skills(), heros.skills[i]);
	}

	void Serialize(Offline::Skill *msg, SkillInfo &skill)
	{
		msg->set_id(skill.id);
		msg->set_type(skill.type);
		msg->set_hurt(skill.hurt);
		msg->set_multiple(skill.multiple);
		msg->set_initweight(skill.initWeight);
		msg->set_useraddweight(skill.userAddWeight);
	}

	void SetMessage(unsigned grade, ProtoBattle::ProtoMatchResp* msg)
	{
		msg->set_fig(fig);
		msg->set_name(name);
		msg->set_grade(grade);
		for(int i = 0; i < MAX_FORMATION_HERO; ++i)
		{
			if(0 == heros[i].id)
				continue;
			msg->add_heroid(heros[i].id);
		}
	}

	void SetMessage(int index, ProtoHero::HeroBaseInfoCPP* msg)
	{
		msg->set_heroid(heros[index].id);
		msg->set_att(heros[index].attr.att);
		msg->set_hp(heros[index].attr.hp);
		msg->set_def(heros[index].attr.def);
	}

	void SetMessage(ProtoBattle::ProtoRefreshResp* msg)
	{
		msg->set_name(name);
		msg->set_fig(fig);
	}

};
struct OfflineResource
{
	OfflineResourceItem item[MEMORY_PROPERTY_NUM];

	void Parse(const Offline::Info& msg)
	{
		for(int i = 0; i < msg.users_size() && i < MEMORY_PROPERTY_NUM; ++i)
			item[i].Parse(msg.users(i));
	}

	void Serialize(Offline::Info* msg)
	{
		for(int i = 0; i < MEMORY_PROPERTY_NUM; ++i)
			item[i].Serialize(msg->add_users());
	}
};

class ResourceManager : public ProtoMemorySingleton<OfflineResource, MEMORY_RESOURCE, Offline::Info>, public CSingleton<ResourceManager>
{
private:
	friend class CSingleton<ResourceManager>;
	ResourceManager(){};
	virtual ~ResourceManager(){}
	set<unsigned> m_freeIndex;
	map<unsigned, unsigned> m_map;
	set<unsigned> m_friend_donation;	//已送体力好友
	set<unsigned> m_friend_battle;		//已打好友

public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();

	const map<unsigned, unsigned>& GetMap() {return m_map;}
	int Add(unsigned uid, unsigned heroId);
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
			memset(&(m_data->item[i]), 0, sizeof(OfflineResourceItem));
			m_freeIndex.insert(i);
			m_map.erase(uid);
			m_friend_battle.clear();
			m_friend_donation.clear();
		}
	}
	unsigned GetIndex(unsigned uid)
	{
		if(m_map.count(uid))
			return m_map[uid];
		return -1;
	}

	string GetUserName(unsigned uid)
	{
		if(!m_map.count(uid))
		{
			return "";
		}

		unsigned index = m_map[uid];

		return m_data->item[index].name;
	}

	void GetClear(vector<unsigned> &uids)
	{
		for(map<unsigned, unsigned>::iterator it=m_map.begin();it!=m_map.end();++it)
		{
			if(m_data->item[it->second].CanClear())
				uids.push_back(it->first);
		}
	}
	void TryClear(vector<unsigned> &uids)
	{
		for(map<unsigned, unsigned>::iterator it=m_map.begin();it!=m_map.end();++it)
		{
			debug_log("%u,%u,%s",m_data->item[it->second].uid, m_data->item[it->second].ts
					,m_data->item[it->second].CanClear()?"yes":"no");
			if(m_data->item[it->second].CanClear())
				uids.push_back(it->first);
		}
	}
};


#endif /* RESOURCEMANAGER_H_ */
