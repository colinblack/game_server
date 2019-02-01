/*
 * ChampionshipManager.h
 *
 *  Created on: 2018年10月9日
 *      Author: colin
 */

#ifndef APP_DATA_CHAMPIONSHIPMANAGER_H_
#define APP_DATA_CHAMPIONSHIPMANAGER_H_

#include "Kernel.h"
#include "BattleDemo.h"

enum ChampionshipStatus
{
	match_status_ready	= 0,  //比赛准备中
	match_status_start  = 1,  //比赛开始
	match_status_over	= 2,  //比赛结束

	match_max,
};

enum PlayersStatus
{
	player_status_not_ready  = 0, //未就绪
	player_status_ready	 	 = 1, //就绪
	player_status_win		 = 2, //胜利
	player_status_lose		 = 3, //失败
	player_status_leave	     = 4, //离开比赛

	player_status_max,
};


struct SkillItem
{
	unsigned id;
	unsigned type;
	double   hurt;
	double	 mul; //伤害系数
	unsigned p_c; //初始权重
	unsigned p_a; //增加权重

	SkillItem()
		: id(0)
		, type(0)
		, hurt(0)
		, mul(0)
		, p_c(0)
		, p_a(0)
	{

	}

	SkillItem(unsigned c_id, unsigned c_type, double c_hurt, double c_mul, unsigned c_p_c, unsigned c_p_a)
		: id(c_id)
		, type(c_type)
		, hurt(c_hurt)
		, mul(c_mul)
		, p_c(c_p_c)
		, p_a(c_p_a)
	{
	}

	void Clear()
	{
		id = type = p_c = p_a = 0;
		hurt = mul = 0.0;
	}
};

struct HeroAttrItem
{
	unsigned id;    //英雄id
	double 	 hp;    //初始血量
	double 	 att;	//攻击
	double	 def;	//防御
	unsigned crit;	//暴击
	unsigned acrit; //抗暴击
	unsigned dodge; //闪避
	unsigned adodge; //命中
	double	 critt; //暴击倍数
	unsigned speed;	//先手
	unsigned battlePower; //战力
	SkillItem skills[e_skill_max]; //技能

	HeroAttrItem()
		: id(0)
		, hp(0)
		, att(0)
		, def(0)
		, crit(0)
		, acrit(0)
		, dodge(0)
		, adodge(0)
		, critt(0)
		, speed(0)
		, battlePower(0)
	{
	}

	HeroAttrItem(unsigned c_id, double c_hp, double c_att, double c_def, unsigned c_crit, unsigned c_acrit
			,unsigned c_dodge, unsigned c_adodge, double c_critt, unsigned c_speed, unsigned c_battle_pow, vector<SkillItem>& s)
		: id(c_id)
		, hp(c_hp)
		, att(c_att)
		, def(c_def)
		, crit(c_crit)
		, acrit(c_acrit)
		, dodge(c_dodge)
		, adodge(c_adodge)
		, critt(c_critt)
		, speed(c_speed)
		, battlePower(c_battle_pow)
	{
		for(int i = 0 ; i < e_skill_max; ++i)
		{
			skills[i] = s[i];
		}
	}

	void Clear()
	{
		id  = crit = acrit = dodge = adodge =  speed = battlePower = 0;
		hp = att = def = critt = 0.0;

		for(int i = 0; i < e_skill_max; ++i)
		{
			skills[i].Clear();
		}
	}
};


struct PlayerItem
{
	unsigned uid;
	unsigned level; //玩家等级
	unsigned hero_num; //英雄数量
	unsigned props[2]; //道具
	HeroAttrItem heros[2];    //出战英雄

	PlayerItem()
		: uid(0)
		, level(0)
		, hero_num(0)
	{
		memset(props, 0, sizeof(props));
	}

	PlayerItem& operator= (PlayerItem& obj)
	{
		if(&obj != this)
		{
			uid 		= obj.uid;
			level  		= obj.level;
			hero_num 	= obj.hero_num;
		}
		return *this;
	}

	void clear()
	{
		uid = level = hero_num = 0;
		memset(props, 0, sizeof(props));
		for(int i = 0; i < 2; ++i)
		{
			heros[i].Clear();
		}
	}

	unsigned Level()
	{
		return level;
	}

	vector<BattleDemoHero> GetBattleDemo();
	vector<BattleDemoItem> GetBattleItem();
	CommonGiftConfig::CommonModifyItem GetConfigItem();
};


struct MatchItem
{
	unsigned id;  //比赛id
	PlayerItem att; //玩家信息
	PlayerItem def;	//玩家信息
	unsigned count;	//比赛人数
	unsigned ready_num; //开始战斗人数
	unsigned winner; //赢家
	unsigned last_ts; //判断比赛是否超时
	unsigned cur_player; //比赛超时，判断谁获胜
	unsigned battle_time; //战斗时长

	MatchItem()
		: id(0)
		, count(0)
		, ready_num(0)
		, winner(0)
		, last_ts(0)
		, cur_player(0)
		, battle_time(0)
	{
	}

	void clear()
	{
		id = 0;
		count = 0;
		ready_num = 0;
		winner = 0;
		last_ts = 0;
		cur_player = 0;
		battle_time = 0;
		att.clear();
		def.clear();
	}
	unsigned Winner()
	{
		return winner;
	}

	void UpdateLastTs()
	{
		last_ts = Time::GetGlobalTime();
	}

	unsigned LastTs()
	{
		return last_ts;
	}

	void UpdateReadyNum(unsigned uid)
	{
		++ready_num;
		cur_player = uid;
	}

	bool IsAllReady()
	{
		return ready_num == 2 ? true: false;
	}

	void SetWinner(unsigned obj)
	{
		winner = obj;
	}

	//当前玩家
	unsigned CurPlayer()
	{
		return cur_player;
	}

	//设置道具
	void SetProp(unsigned uid, unsigned battleid, vector<unsigned>& prob)
	{
		unsigned* props = nullptr;
		if(uid == att.uid)
			props = att.props;
		else if(uid == def.uid)
			props = def.props;

		for(int i = 0; i < prob.size() && i < 2; ++i)
		{
			props[i] = prob[i];
		}
	}

	//设置战斗时长
	void SetBattleTime(unsigned time)
	{
		battle_time = time;
	}

	unsigned BattleTime()
	{
		return battle_time;
	}
};

struct MatchData
{
	MatchItem item[MEMORY_MATCH_NUM];
};

class ChampionshipManager : public MemorySingleton<MatchData, MEMORY_CHAMPIONSHIP>, public CSingleton<ChampionshipManager>
{
private:
	friend class CSingleton<ChampionshipManager>;
	ChampionshipManager(){};
	virtual ~ChampionshipManager(){}

public:
	virtual void CallDestroy() {Destroy();}
	int OnInit()
	{
		for(int i = 0; i < MEMORY_MATCH_NUM; ++i)
		{
			m_data->item[i].clear();
			m_freeIndex.insert(i);
		}

		return 0;
	}
	//获取索引
	unsigned GetFreeIndex()
	{
		if(m_freeIndex.empty())
			return (unsigned)-1;

		return *(m_freeIndex.begin());
	}

	MatchItem& GetData(unsigned id)
	{
		if(m_map.count(id) == 0)
			throw runtime_error("no_data");
		unsigned index = m_map[id];

		return m_data->item[index];
	}

	//创建比赛
	unsigned CreateGame()
	{
		unsigned i = GetFreeIndex();
		if(i == (unsigned)-1)
		{
			error_log("free index is empty");
			return (unsigned)-1;
		}

		m_freeIndex.erase(i);
		unsigned battleid = i+1;
		m_data->item[i].id = battleid;
		m_map[battleid] = i;

		return battleid;
	}

	//添加玩家到比赛
	int AddUser(unsigned uid, unsigned id, unsigned level)
	{
		if(m_map.count(id) == 0)
			return R_ERR_PARAM;

		unsigned index = m_map[id];
		unsigned& count = m_data->item[index].count;

		if(count == 0)
		{
			m_data->item[index].att.uid = uid;
			m_data->item[index].att.level = level;
		}
		else if(count == 1)
		{
			m_data->item[index].def.uid = uid;
			m_data->item[index].def.level = level;
		}
		else
			return R_ERROR;

		if(!IsValidUid(uid))
			m_data->item[index].ready_num++;

		++count;
		return R_SUCCESS;
	}

	//设置英雄属性
	int SetHeroAttr(unsigned uid, unsigned id, const HeroAttrItem& attr)
	{
		if(m_map.count(id) == 0)
			return R_ERR_PARAM;


		unsigned index = m_map[id];

		HeroAttrItem* item = nullptr;
		if(uid == m_data->item[index].att.uid)
		{
			unsigned& num = m_data->item[index].att.hero_num;
		//	debug_log("battleid: %u, uid: %u, hero_num: %u", id, uid, num);
			if(num == 2)
				return R_ERROR;

			item = &(m_data->item[index].att.heros[num++]);
		}
		else if(uid == m_data->item[index].def.uid)
		{
			unsigned& num = m_data->item[index].def.hero_num;
		//	debug_log("battleid: %u, uid: %u, hero_num: %u", id, uid, num);
			if(num == 2)
				return R_ERROR;

			item = &(m_data->item[index].def.heros[num++]);
		}
		else
		{
			return R_ERROR;
		}

		item->id			= attr.id;
		item->hp			= attr.hp;
		item->att 			= attr.att;
		item->def 			= attr.def;
		item->crit 			= attr.crit;
		item->acrit 		= attr.acrit;
		item->dodge 		= attr.dodge;
		item->adodge 		= attr.adodge;
		item->critt 		= attr.critt;
		item->speed			= attr.speed;
		item->battlePower 	= attr.battlePower;

		for(int i = 0; i < e_skill_max; ++i)
			item->skills[i] = attr.skills[i];

		return R_SUCCESS;
	}

	//比赛是否合法
	bool IsValid(unsigned id)
	{
		return m_map.count(id) == 0 ? false : true;
	}

	void Clear(unsigned battleid)
	{
		if(m_map.count(battleid))
		{
			unsigned i = m_map[battleid];
			memset(&(m_data->item[i]), 0, sizeof(MatchItem));
			m_freeIndex.insert(i);
			m_map.erase(battleid);
		}
	}

private:
	set<unsigned> m_freeIndex;
	map<unsigned, unsigned> m_map;
};



#endif /* APP_DATA_CHAMPIONSHIPMANAGER_H_ */
