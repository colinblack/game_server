/*
 * HeroPropertyManager.h
 *
 *  Created on: 2016-9-2
 *      Author: Ralf
 */

#ifndef HEROPROPERTYMANAGER_H_
#define HEROPROPERTYMANAGER_H_

#include "Kernel.h"

class HeroFightAttr
{
public:
	HeroFightAttr();
	void Clear();

	void 	SetAttr(DemoHeroProperty attr, int val);
	void 	AddAttr(DemoHeroProperty attr, int val);
	int 	GetAttr(DemoHeroProperty attr) const;

	//各属性加成
	void 	AdditionFightBase(map<unsigned, double> & addition_percent);

	HeroFightAttr& operator +=(const HeroFightAttr& obj)
	{
		for (int i = 0; i < DemoHeroProperty_max; i++)
		{
			val_[(DemoHeroProperty)i] += obj.val_[(DemoHeroProperty)i];
		}

		return *this;
	}

	HeroFightAttr operator +(const HeroFightAttr& obj)
	{
		HeroFightAttr result;
		for (int i = 0; i < DemoHeroProperty_max; i++)
		{
			DemoHeroProperty prop = (DemoHeroProperty)i;
			result.val_[prop] = val_[prop] + obj.val_[prop];
		}

		return result;
	}

	bool operator ==(const HeroFightAttr& obj)
	{
		for (int i = 0; i < DemoHeroProperty_max; i++)
		{
			DemoHeroProperty prop = (DemoHeroProperty)i;
			if (val_[prop] != obj.val_[prop])
			{
				return false;
			}
		}

		return true;
	}

	void FullMessage(ProtoHero::HeroBaseInfoCPP* hero) const
	{
		int attack = GetAttr(DemoHeroProperty_attack);   //攻击
		int hp = GetAttr(DemoHeroProperty_hp);    //血量
		int defend = GetAttr(DemoHeroProperty_defend);   //防御
		int rule = GetAttr(DemoHeroProperty_int);   //统
		int courage = GetAttr(DemoHeroProperty_str);   //勇
		int power = GetAttr(DemoHeroProperty_power);

		hero->set_attack(attack);
		hero->set_hp(hp);
		hero->set_defend(defend);
		hero->set_rule(rule);
		hero->set_courage(courage);
		hero->set_power(power);
	}
private:
	int val_[DemoHeroProperty_max];//英雄属性
};
//////////////////////////////////////////////////////////////////////////////////////


struct HeroPropertyItemIndex
{
	unsigned uid;
	unsigned id;//英雄id

	HeroPropertyItemIndex()
	{
		uid = id = 0;
	}
	HeroPropertyItemIndex(unsigned u, unsigned i)
	{
		uid = u;
		id = i;
	}
	bool operator <(const HeroPropertyItemIndex& other) const
	{
		if(uid != other.uid)
			return uid < other.uid;
		else
			return id < other.id;
	}
	bool operator ==(const HeroPropertyItemIndex& other) const
	{
		if(uid == other.uid && id == other.id)
			return true;
		return false;
	}
	bool operator !=(const HeroPropertyItemIndex& other) const
	{
		if(uid == other.uid && id == other.id)
			return false;
		return true;
	}
	bool empty() const
	{
		return uid == 0;
	}
	bool IsUser() const
	{
		return IsValidUid(uid);
	}
	bool notHero() const
	{
		return uid && uid < ADMIN_UID;
	}
	bool isVision() const
	{
		return uid == e_vision_npc;
	}
	bool isOtherVision() const
	{
		return uid == e_vision_other;
	}
	bool isUserVision() const
	{
		return isVision() || isOtherVision();
	}
	bool isWorldNPC() const
	{
		return uid == e_normal_npc || uid == e_attack_npc  || uid == e_defend_npc;
	}
	bool isWorldActNpc() const
	{
		return uid == e_act_npc;
	}
	bool isWorldTTTNpc() const
	{
		return uid == e_ttt_npc;
	}
	bool isWorldNBNpc() const
	{
		return uid == e_nb_npc;
	}
	bool isWorld() const
	{
		return isWorldNPC() || isWorldActNpc() || isWorldTTTNpc() || isWorldNBNpc();
	}
	bool isGateNPC() const
	{
		return uid == e_gate_npc;
	}
	bool notReal() const
	{
		return isGateNPC() || isOtherVision();
	}
	bool isPVE() const
	{
		return notHero() && !isUserVision();
	}
	void Clear()
	{
		uid = id = 0;
	}
};
struct HeroPropertyItem
{
	HeroPropertyItemIndex index;
	int property[DemoHeroProperty_max];//英雄属性
	int hp[SG17_HERO_SOLDIER];//各排血量
	unsigned extraid;//副将id
	uint16_t city;//所在城市
	uint16_t gate;//所在关卡
	unsigned ouid;//幻影的uid,npc的kingdom
	unsigned oid;//npc或幻影的hero id

	HeroPropertyItem()
	{
		extraid = city = gate = oid = ouid = 0;
		memset(property, 0, sizeof(property));
		memset(hp, 0, sizeof(hp));
	}

	void CreateVision(HeroPropertyItem& obj)
	{
		memcpy(property, obj.property, sizeof(property));
		memcpy(hp, obj.hp, sizeof(hp));
		extraid = obj.extraid;
		city = obj.city;
		gate = obj.gate;
		ouid = obj.index.uid;
		oid = obj.index.id;
		bool flag = false;
		for(unsigned i=0;i<SG17_HERO_SOLDIER;++i)
		{
			if(!flag && hp[i])
				flag = true;
			if(flag && hp[i] == 0)
				break;
			hp[i] = property[DemoHeroProperty_hp];
		}
	}
	void CreateWorldNPC(unsigned k, unsigned c)
	{
		memset(property, 1, sizeof(property));
		memset(hp, 0, sizeof(hp));
		hp[0] = 1;
		extraid = 0;
		city = c;
		gate = 0;
		ouid = k;
		oid = 0;
	}
	void CreateActNPC(unsigned k, unsigned c, unsigned id, unsigned s, unsigned h)
	{
		memset(property, 1, sizeof(property));
		memset(hp, 0, sizeof(hp));
		for(unsigned i=0;i<s;++i)
			hp[i] = h;
		extraid = 0;
		city = c;
		gate = 0;
		ouid = k;
		oid = id;
	}

	bool IsDie()
	{
		for(unsigned i=0;i<SG17_HERO_SOLDIER;++i)
		{
			if(hp[i])
				return false;
		}
		return true;
	}

	void Die(uint16_t cid)
	{
		memset(hp, 0, sizeof(hp));
		gate = 0;
		city = cid;
		//debug_log("die hero uid=%u,id=%u,cid=%u", index.uid, index.id, city);
	}
	void SyncHP(vector<int> h)
	{
		for(unsigned i=0;i<h.size();++i)
			hp[i] = h[i];
	}
	bool IsNeedRecover(unsigned s)
	{
		s = min(s, (unsigned)SG17_HERO_SOLDIER);
		unsigned h = 0;
		for(unsigned i=0;i<s;++i)
			h += hp[i];
		return h * 4 < property[DemoHeroProperty_hp] * s;
	}

	void SetMessage(ProtoBattleField::Hero* msg, unsigned s)
	{
		if(extraid)
			++s;
		msg->set_id(index.id);
		for(unsigned i=0;i<DemoHeroProperty_max;++i)
			msg->add_property(property[i]);
		for(unsigned i=0;i<s;++i)
			msg->add_hp(hp[i]);
		msg->set_extraid(extraid);
		msg->set_city(city);
		msg->set_gate(gate);
		if(index.notHero())
		{
			msg->set_ouid(ouid);
			msg->set_oid(oid);
		}
	}
	unsigned SetMessage(ProtoBattleField::HidUid* msg)
	{
		msg->set_uid(index.uid);
		msg->set_id(index.id);
		if(index.notHero())
		{
			msg->set_ouid(ouid);
			msg->set_oid(oid);
			return ouid;
		}
		return index.uid;
	}

	void FullMessage(unsigned nTotalRows, ProtoHero::HeroSoldiersCPP* obj)
	{
		obj->set_heroid(index.id);
		obj->set_max(GetTotalTroops(nTotalRows));
		obj->set_soldiers(GetActualTroops(nTotalRows));
	}

	void UpdateProperty(const HeroFightAttr& fight_attr);
	void GetHeroFightAttr(HeroFightAttr& fight_attr) const;

	//总兵力//@input 英雄的总排数
	//英雄上限兵力=英雄血量*3*士兵排数
	unsigned GetTotalTroops(unsigned nTotalRows);
	unsigned GetActualTroops(unsigned nTotalRows);
	int GetFreeTroops(unsigned nTotalRows);

	bool	 IsFullTroops(unsigned nTotalRows);

	void	 RecruitSoldires(unsigned nTotalRows, int rate);
	unsigned	 CalcRealRecruitSoldires(unsigned nTotalRows, int rate);
	//恢复所有
	void 	 FullSoldires(unsigned nTotalRows);
};
struct HeroProperty
{
	HeroPropertyItem item[MEMORY_HERO_PROPERTY_NUM*SG17_HERO_NUM];
	unsigned npc_id;

	HeroProperty()
	{
		npc_id = 0;
	}
	HeroPropertyItemIndex CreateNPCIndex(unsigned type)
	{
		return HeroPropertyItemIndex(type, ++npc_id);
	}
};

typedef map<HeroPropertyItemIndex, unsigned> HeroPropertyMap;
typedef map<unsigned, set<HeroPropertyItemIndex> > HeroIndexMap;
class HeroPropertyManager : public MemorySingleton<HeroProperty, MEMORY_HERO_PROPERTY>, public CSingleton<HeroPropertyManager>
{
private:
	friend class CSingleton<HeroPropertyManager>;
	HeroPropertyManager(){};
	virtual ~HeroPropertyManager(){}

	set<unsigned> m_freeIndex;
	HeroPropertyMap m_map;
	HeroIndexMap m_indexmap;
public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();

	const HeroPropertyMap& GetMap() {return m_map;}
	const HeroIndexMap& GetIndexMap(){return m_indexmap;}
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
		return GetFreeCount() * 10 / (MEMORY_HERO_PROPERTY_NUM*SG17_HERO_NUM) <= 1;
	}
	void DoClear(unsigned uid)
	{
		if(m_indexmap.count(uid))
		{
			for(set<HeroPropertyItemIndex>::iterator it=m_indexmap[uid].begin();it!=m_indexmap[uid].end();++it)
			{
				unsigned i = m_map[*it];
				memset(&(m_data->item[i]), 0, sizeof(HeroPropertyItem));
				m_freeIndex.insert(i);
				m_map.erase(*it);
			}
			m_indexmap.erase(uid);
		}
		if(m_indexmap.count(e_vision_npc))
		{
			for(set<HeroPropertyItemIndex>::iterator it=m_indexmap[e_vision_npc].begin();it!=m_indexmap[e_vision_npc].end();++it)
			{
				unsigned i = m_map[*it];
				if(m_data->item[i].ouid == uid)
				{
					memset(&(m_data->item[i]), 0, sizeof(HeroPropertyItem));
					m_freeIndex.insert(i);
					m_map.erase(*it);
				}
			}
			if(m_indexmap[e_vision_npc].empty())
				m_indexmap.erase(e_vision_npc);
		}
		if(m_indexmap.count(e_attack_npc))
		{
			for(set<HeroPropertyItemIndex>::iterator it=m_indexmap[e_attack_npc].begin();it!=m_indexmap[e_attack_npc].end();++it)
			{
				unsigned i = m_map[*it];
				memset(&(m_data->item[i]), 0, sizeof(HeroPropertyItem));
				m_freeIndex.insert(i);
				m_map.erase(*it);
			}
			m_indexmap.erase(e_attack_npc);
		}
		if(m_indexmap.count(e_defend_npc))
		{
			for(set<HeroPropertyItemIndex>::iterator it=m_indexmap[e_defend_npc].begin();it!=m_indexmap[e_defend_npc].end();++it)
			{
				unsigned i = m_map[*it];
				memset(&(m_data->item[i]), 0, sizeof(HeroPropertyItem));
				m_freeIndex.insert(i);
				m_map.erase(*it);
			}
			m_indexmap.erase(e_defend_npc);
		}
	}
	bool GetHeros(unsigned uid, set<HeroPropertyItemIndex>& hero)
	{
		if(m_indexmap.count(uid))
		{
			hero = m_indexmap[uid];
			return true;
		}
		return false;
	}
	bool GetHeros(unsigned uid, vector<HeroPropertyItemIndex>& hero)
	{
		if(m_indexmap.count(uid))
		{
			for(set<HeroPropertyItemIndex>::iterator it=m_indexmap[uid].begin();it!=m_indexmap[uid].end();++it)
				hero.push_back(*it);
			return true;
		}
		return false;
	}
	bool HasHero(HeroPropertyItemIndex index)
	{
		return m_map.count(index);
	}
	unsigned GetIndex(HeroPropertyItemIndex index)
	{
		if(m_map.count(index))
			return m_map[index];
		return -1;
	}
	int Add(HeroPropertyItemIndex index)
	{
		unsigned i = GetFreeIndex();
		if(i == (unsigned)-1)
			return R_ERR_DATA;
		m_freeIndex.erase(i);
		m_map[index] = i;
		m_indexmap[index.uid].insert(index);
		m_data->item[i].index = index;
		return 0;
	}
	void Del(HeroPropertyItemIndex index)
	{
		if(m_map.count(index))
		{
			unsigned i = m_map[index];
			memset(&(m_data->item[i]), 0, sizeof(HeroPropertyItem));
			m_freeIndex.insert(i);
			m_map.erase(index);
			m_indexmap[index.uid].erase(index);
			if(m_indexmap[index.uid].empty())
				m_indexmap.erase(index.uid);
		}
	}

	HeroPropertyItem& Get(unsigned uid, unsigned heroId)
	{
		HeroPropertyItemIndex index(uid, heroId);
		if(m_map.count(index))
		{
			unsigned i = m_map[index];
			return m_data->item[i];
		}

		error_log("get_hero_property_error. uid=%u,hero=%u", uid, heroId);
		throw std::runtime_error("get_hero_property_error");
	}

	void SetMessage(unsigned uid, ProtoBattleField::Field* msg, unsigned s)
	{
		if(m_indexmap.count(uid))
		{
			for(set<HeroPropertyItemIndex>::iterator it=m_indexmap[uid].begin();it!=m_indexmap[uid].end();++it)
				m_data->item[m_map[*it]].SetMessage(msg->add_hero(), s);
		}
	}

	HeroPropertyItemIndex CreateVision(HeroPropertyItemIndex hi)
	{
		HeroPropertyItemIndex vi = m_data->CreateNPCIndex(e_vision_npc);
		Add(vi);
		m_data->item[m_map[vi]].CreateVision(m_data->item[m_map[hi]]);
		return vi;
	}
	HeroPropertyItemIndex CreateWorldNPC(unsigned t, unsigned k, unsigned c)
	{
		HeroPropertyItemIndex ni = m_data->CreateNPCIndex(t);
		if(Add(ni))
			ni.Clear();
		else
			m_data->item[m_map[ni]].CreateWorldNPC(k, c);
		return ni;
	}
	HeroPropertyItemIndex CreateActNPC(unsigned type, unsigned k, unsigned c, unsigned id, unsigned s, unsigned h)
	{
		HeroPropertyItemIndex ni = m_data->CreateNPCIndex(type);
		if(Add(ni))
			ni.Clear();
		else
			m_data->item[m_map[ni]].CreateActNPC(k, c, id, s, h);
		return ni;
	}
};

#endif /* HEROPROPERTYMANAGER_H_ */
