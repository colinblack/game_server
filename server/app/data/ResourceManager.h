/*
 * ResourceManager.h
 *
 *  Created on: 2016-9-2
 *      Author: Ralf
 */

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include "Kernel.h"
#include "AsynManager.h"

struct PayHis
{
	unsigned pay, cost, ts;
	PayHis()
	{
		pay = cost = ts = 0;
	}
	PayHis(unsigned p, unsigned c)
	{
		pay = p;
		cost = c;
		ts = Time::GetGlobalTime();
	}
	bool IsSameDay(unsigned t)
	{
		return CTime::GetDayInterval(t, ts) == 0;
	}
	bool Append(PayHis& o)
	{
		if(ts == 0)
		{
			pay = o.pay;
			cost = o.cost;
			ts = o.ts;
			return true;
		}
		if(IsSameDay(o.ts))
		{
			pay += o.pay;
			cost += o.cost;
			return true;
		}
		return false;
	}
};
/***************************************************/
struct OfflineResourceItemHexp
{
	unsigned id;
	unsigned hexp;//英雄经验
	unsigned occupy;//英雄累计攻城数
	unsigned win;//英雄累计胜利单挑数
	unsigned kill;//英雄的累计杀敌数
	OfflineResourceItemHexp()
	{
		id = hexp = occupy = win = kill = 0;
	}
	void Append(OfflineResourceItemHexp& obj)
	{
		hexp += obj.hexp;
		occupy += obj.occupy;
		win += obj.win;
		kill += obj.kill;
	}
	void SetMessage(ProtoBattleField::HeroReward* msg)
	{
		msg->set_id(id);
		msg->set_hexp(hexp);
		msg->set_occupy(occupy);
		msg->set_win(win);
		msg->set_kill(kill);
	}
};
/***************************************************/
class BattleReward
{
public:
	uint64_t exp;//经验
	unsigned coin;//铜币
	unsigned wood;//木材
	unsigned food;//粮食
	unsigned iron;//镔铁
	unsigned gem;//(1级宝石)废弃，作为龙鳞
	unsigned kill;//杀敌数
	unsigned damage;//闯关杀敌数
	unsigned hurt;//受伤
	unsigned head;//人头
	map<unsigned,OfflineResourceItemHexp> hexp;
	bool has;
	unsigned reward;//功勋
	unsigned bkill;//国战杀敌
	map<unsigned, unsigned> item;

	BattleReward()
	{
		exp = 0;
		coin = wood = food = iron = gem = kill = hurt = head = damage = reward = bkill = 0;
		has = false;
	}
	void Clear()
	{
		if(has)
		{
			exp = 0;
			coin = wood = food = iron = gem = kill = hurt = head = damage = reward = bkill = 0;
			hexp.clear();
			item.clear();
			has = false;
		}
		else
			damage = hurt = head = reward = bkill = 0;
	}
	void Append(BattleReward& obj)
	{
		exp += obj.exp;
		coin += obj.coin;
		wood += obj.wood;
		food += obj.food;
		iron += obj.iron;
		gem += obj.gem;
		kill += obj.kill;
		hurt += obj.hurt;
		head += obj.head;
		damage += obj.damage;
		for(map<unsigned,OfflineResourceItemHexp>::iterator it=obj.hexp.begin();it!=obj.hexp.end();++it)
		{
			if(hexp.count(it->first))
				hexp[it->first].Append(it->second);
			else
				hexp[it->first] = it->second;
		}
		reward = obj.reward;
		bkill = obj.bkill;
		for(map<unsigned, unsigned>::iterator it=obj.item.begin();it!=obj.item.end();++it)
		{
			if(item.count(it->first))
				item[it->first] += it->second;
			else
				item[it->first] = it->second;
		}
	}
	void SetMessage(ProtoBattleField::UserReward* msg, bool gate)
	{
		msg->set_exp(exp);
		msg->set_coin(coin);
		msg->set_wood(wood);
		msg->set_food(food);
		msg->set_iron(iron);
		msg->set_gem(gem);
		for(map<unsigned,OfflineResourceItemHexp>::iterator it=hexp.begin();it!=hexp.end();++it)
			it->second.SetMessage(msg->add_hexp());
		if(gate)
		{
			msg->set_kill(damage);
			msg->set_hurt(hurt);
			msg->set_head(head);
		}
		else
		{
			msg->set_reward(reward);
			msg->set_bkill(bkill);
		}
		for(map<unsigned, unsigned>::iterator it=item.begin();it!=item.end();++it)
		{
			ProtoBattleField::ItemReward* t = msg->add_item();
			t->set_id(it->first);
			t->set_count(it->second);
		}
	}
};
typedef map<unsigned, BattleReward> BattleRewardMap;
/***************************************************/
struct OfflineResourceItem
{
	unsigned uid;
	uint64_t exp;//经验
	unsigned coin;//铜币
	unsigned wood;//木材
	unsigned food;//粮食
	unsigned iron;//镔铁
	unsigned silk;//(丝绸)废弃，作为回血次数
	unsigned gem;//(1级宝石)废弃，作为龙鳞
	unsigned mkill;//国战任务期间杀敌数
	unsigned kill;//杀敌数
	unsigned occupy;//占领数
	unsigned foccupy;//助攻数
	unsigned rush;//单挑数
	unsigned reward;//功勋
	unsigned rewardb;//增加的功勋宝箱
	unsigned cfood;//下线前拥有的粮食，用于回血
	unsigned ufood;//自动回血用掉的粮食
	OfflineResourceItemHexp hexp[SG17_HERO_NUM];
	int property[DemoOfflineProperty_max];//回血和战斗用到的属性
	char name[BASE_NAME_LEN];//玩家名字
	char fig[BASE_FIG_LEN];//头像
	uint8_t kingdom;//国家
	uint8_t aid;
	uint8_t job;
	uint8_t viplevel;
	bool is_atuo;
	unsigned forbid_talk_ts;
	unsigned forbid_move_ts;
	PayHis payHis[RMI_PAY_HIS];
	unsigned ts;//内容变化时戳

	OfflineResourceItem()
	{
		uid = exp = coin = wood = food = iron = silk = gem = mkill = kill = occupy = foccupy = rush = reward = rewardb = cfood = ufood = kingdom = aid = job = viplevel = forbid_talk_ts = forbid_move_ts = ts = 0;
		is_atuo = false;
		memset(property, 0, sizeof(property));
		memset(name, 0, sizeof(name));
		memset(fig, 0, sizeof(fig));
	}

	bool CanClear()
	{
		return ts + 86400*7 < Time::GetGlobalTime();
	}
	void DailyReset()
	{
		mkill = occupy = foccupy = rush = reward = 0;
	}

	void KillReset()
	{
		kill = 0;
	}

	void MissionReset()
	{
		mkill = 0;
	}

	void ResetProductResource()
	{
		coin = 0;
		wood = 0;
		food = 0;
		iron = 0;
		ufood = 0;
		gem = 0;
	}

	void ResetHexp()
	{
		memset(hexp, 0, sizeof(OfflineResourceItemHexp) * SG17_HERO_NUM);
	}

	void SetMessage(ProtoBattleField::ReplyRewardInfo* msg)
	{
		msg->set_mkill(mkill);
		msg->set_kill(kill);
		msg->set_occupy(occupy);
		msg->set_foccupy(foccupy);
		msg->set_rush(rush);
		msg->set_reward(reward);
	}

	unsigned GetSoldiresRows() const
	{
		return property[DemoOfflineProperty_soldier];
	}

	unsigned GetSoldierLevel() const
	{
		return property[DemoOfflineProperty_s_level];
	}

	//回血速度
	unsigned GetRecruitRate() const
	{
		return property[DemoOfflineProperty_chp];
	}
	void SetMessage(ProtoBattleField::UserInfo* msg, bool hasfig)
	{
		msg->set_uid(uid);
		msg->set_name(string(name));
		msg->set_kingdom(kingdom);
		if(hasfig)
			msg->set_fig(string(fig));
	}
	unsigned CalcAddExplotBox(int exploit, int box_lvl, int add_exploit) const;
	void AddReward(unsigned areward)
	{
		rewardb += CalcAddExplotBox(reward, property[DemoOfflineProperty_b_level], areward);
		reward += areward;
	}
	unsigned SyncReward(unsigned areward)
	{
		unsigned arewardb = CalcAddExplotBox(reward, property[DemoOfflineProperty_b_level], areward);
		reward += areward;
		return arewardb;
	}
	unsigned CalcReward(unsigned okill, unsigned akill)
	{
		unsigned killreward = ConfigManager::Instance()->GetKillReward(property[DemoOfflineProperty_u_level]);
		return (okill + akill) / killreward - okill / killreward;
	}
	unsigned ProcessKill(unsigned akill, bool mission)
	{
		if(akill)
		{
			if(mission)
				mkill += akill;
			unsigned areward = CalcReward(kill, akill);
			kill += akill;
			return SyncReward(areward);
		}
		return 0;
	}
	unsigned SyncKill(BattleReward& r, bool mission)
	{
		ts = Time::GetGlobalTime();
		unsigned d =  ProcessKill(r.kill, mission);
		r.reward = reward;
		r.bkill = kill;
		return d;
	}
	void Sync(BattleReward& r, bool mission)
	{
		exp += r.exp;
		coin += r.coin;
		wood += r.wood;
		food += r.food;
		iron += r.iron;
		gem += r.gem;
		rewardb += ProcessKill(r.kill, mission);
		r.reward = reward;
		r.bkill = kill;
		for(map<unsigned,OfflineResourceItemHexp>::iterator it=r.hexp.begin();it!=r.hexp.end();++it)
		{
			unsigned e = -1;
			bool flag = true;
			for(unsigned i=0;i<SG17_HERO_NUM;++i)
			{
				if(hexp[i].id == 0)
				{
					if(e == (unsigned)-1)
						e = i;
				}
				else if(hexp[i].id == it->first)
				{
					hexp[i].Append(it->second);
					flag = false;
					break;
				}
			}
			if(flag)
			{
				if(e == (unsigned)-1)
					hexp[0].Append(it->second);
				else
				{
					hexp[e].id = it->first;
					hexp[e].Append(it->second);
				}
			}
		}
		for(map<unsigned, unsigned>::iterator it=r.item.begin();it!=r.item.end();++it)
			AsynManager::Instance()->Add(uid, it->first, it->second);
		ts = Time::GetGlobalTime();
	}
	void AddHeroOccupy(unsigned id)
	{
		for(unsigned i=0;i<SG17_HERO_NUM;++i)
		{
			if(hexp[i].id == id)
			{
				++hexp[i].occupy;
				break;
			}
		}
	}
	void AddPay(unsigned pay)
	{
		PayHis o(pay, 0);
		if(payHis[0].Append(o))
			return;
		for(unsigned i=RMI_PAY_HIS-1;i>0;--i)
			payHis[i] = payHis[i-1];
		payHis[0] = o;

	}
	void AddCost(unsigned cost)
	{
		PayHis o(0, cost);
		if(payHis[0].Append(o))
			return;
		for(unsigned i=RMI_PAY_HIS-1;i>0;--i)
			payHis[i] = payHis[i-1];
		payHis[0] = o;
	}

	void SetMessage(ProtoBattleField::RMIField* msg)
	{
		msg->set_aid(aid);
		msg->set_job(job);
		msg->set_is_atuo(is_atuo);
		msg->set_forbid_talk_ts(forbid_talk_ts);
		msg->set_forbid_move_ts(forbid_move_ts);
		msg->set_silk(silk);
	}

	void SetMessage(Bot::ChatInfo *msg)
	{
		msg->set_uid(uid);
		msg->set_name(name);
		msg->set_kingdom(kingdom);
		msg->set_vip(viplevel);
		msg->set_lvl(property[DemoOfflineProperty_u_level]);
	}

	void SetMessage(ProtoBattleField::ReplyCityMaster *msg)
	{
		msg->set_aid(aid);
		msg->set_job(job);
		msg->set_level(property[DemoOfflineProperty_u_level]);
	}
};
struct OfflineResource
{
	OfflineResourceItem item[MEMORY_HERO_PROPERTY_NUM];
};

class ResourceManager : public MemorySingleton<OfflineResource, MEMORY_RESOURCE>, public CSingleton<ResourceManager>
{
private:
	friend class CSingleton<ResourceManager>;
	ResourceManager(){};
	virtual ~ResourceManager(){}

	set<unsigned> m_freeIndex;
	map<unsigned, unsigned> m_map;
public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();

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
		return GetFreeCount() * 10 / MEMORY_HERO_PROPERTY_NUM <= 1;
	}
	void DoClear(unsigned uid)
	{
		if(m_map.count(uid))
		{
			unsigned i = m_map[uid];
			memset(&(m_data->item[i]), 0, sizeof(OfflineResourceItem));
			m_freeIndex.insert(i);
			m_map.erase(uid);
		}
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
		m_data->item[i].uid = uid;
		m_data->item[i].ts = Time::GetGlobalTime();
		return 0;
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
