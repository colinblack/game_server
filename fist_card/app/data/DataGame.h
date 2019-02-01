/*
 * DataGame.h
 *
 *  Created on: 2018年11月27日
 *      Author: colin
 */

#ifndef APP_DATA_DATAGAME_H_
#define APP_DATA_DATAGAME_H_

#include "Kernel.h"

struct BuffItem
{
	char ltype;	//效果持续类型1回合2受伤害3攻击次数4.死亡次数
	char ctype; //卡牌类型1攻击2辅助3咒术
	char aid;	//效果id
	char gain;  //增益类型 0:否, 1是
	char count;	//次数
	char type;	//数据类型
	char cardid; //卡牌id
	char star;	 //星级
	char index;	//效果配置索引
	char overlay; //叠加类型
	double value; //数据值


	BuffItem()
		: ltype(0)
		, ctype(0)
		, aid(0)
		, gain(0)
		, count(0)
		, type(0)
		, cardid(0)
		, star(0)
		, index(0)
		, overlay(0)
		, value(0)
	{
	}

	BuffItem(char lt, char ct, char a, char g, char c, char t,  char ca, char st, char i, char o, double v)
		: ltype(lt)
		, ctype(ct)
		, aid(a)
		, gain(g)
		, count(v)
		, type(t)
		, cardid(ca)
		, star(st)
		, index(i)
		, overlay()
		, value(v)

	{
	}

	BuffItem(const BuffItem& obj)
		: ltype(obj.type)
		, ctype(obj.ctype)
		, aid(obj.aid)
		, gain(obj.gain)
		, count(obj.count)
		, type(obj.type)
		, cardid(obj.cardid)
		, star(obj.star)
		, index(obj.index)
		, overlay(obj.overlay)
		, value(obj.value)
	{
	}
};

struct CardItem
{
	unsigned ud;
	unsigned id;
	char star;
	char temp;

	CardItem()
		: ud(0)
		, id(0)
		, star(0)
		, temp(0)
	{
	}
	CardItem(unsigned c_ud, unsigned c_id, char c_star, char c_temp)
		: ud(c_ud), id(c_id), star(c_star), temp(c_temp)
	{
	}

	CardItem(const CardItem& obj)
	{
		ud = obj.ud;
		id = obj.id;
		star = obj.star;
		temp = obj.temp;
	}

	CardItem& operator=(const CardItem& obj)
	{
		if(&obj != this)
		{
			ud 	= obj.ud;
			id 	= obj.id;
			star = obj.star;
			temp = obj.temp;
		}

		return *this;
	}

	void SetMessage(ProtoCards::UserCardsCPP* msg)
	{
		msg->set_ud(ud);
		msg->set_cardid(id);
		msg->set_star(star);
	}

	void Clear()
	{
		ud = 0;
		id = 0;
		star = 0;
	}
};

struct RecordItem
{
	char star;		//每次出牌的星级
	char index;		//效果配置索引
	char crited;	//0:没有暴击  1:有暴击
	char dodged;	//0:没有闪避, 1:有闪避
	char shot_back;	//0:没有反击, 1:有反击
	char bomb;		//0:没有引爆, 1:有引爆
	char died; 		//0: 没有死亡  , 1:有死亡
	char hurt_trans; //0:没有伤害转化, 1:有伤害转化
	char attr_change;//属性有变化:0没有4攻击5防御6护盾
	unsigned hurt_back;	//0:没有伤害反弹
	double dam;		//受到的伤害

	//清除每次出牌数据
	void ClearOnce()
	{
		crited = 0;
		dodged = 0;
		shot_back = 0;
		star = 0;
		index = 0;
		hurt_back = 0;
		hurt_trans = 0;
		died = 0;
		dam = 0.0;
		attr_change = 0;
		bomb = 0;
	}

	void Crited()
	{
		crited = 1;
	}

	void Dodoged()
	{
		dodged = 1;
	}


	bool IsCrited()
	{
		return crited == 1 ? true : false;
	}

	bool IsDodoged()
	{
		return dodged == 1 ? true : false;
	}

	void ShotBack()
	{
		shot_back = 1;
	}

	bool IsShotBack()
	{
		return shot_back == 1 ? true : false;
	}

	void HurtBack()
	{
		hurt_back = 1;
	}

	bool IsHurtBack()
	{
		return hurt_back == 1 ? true : false;
	}

	double Dam()
	{
		return dam;
	}

	void Dam(double value)
	{
		dam = value;
	}

	void Star(char s)
	{
		star = s;
	}

	void Index(char idx)
	{
		index = idx;
	}

	char Index()
	{
		return index;
	}

	char Star()
	{
		return star;
	}

	void AttrChange(unsigned type)
	{
		attr_change = type;
	}

	void Bomb()
	{
		bomb = 1;
	}

	RecordItem()
		: star(0)
		, index(0)
		, crited(0)
		, dodged(0)
		, shot_back(0)
		, bomb(0)
		, died(0)
		, hurt_trans(0)
		, attr_change(0)
		, hurt_back(0)
		, dam(0.0)
	{
	}
};

struct HeroAttrItem
{
	unsigned id;    //英雄id
	double 	 hp;    //初始血量
	double   n_hp;	//当前血量
	double   l_hp;	//损失的血量
	double 	 att;	//攻击
	double	 def;	//防御
	unsigned crit;	//暴击
	unsigned acrit; //抗暴击
	unsigned dodge; //闪避
	unsigned adodge; //命中
	double	 critt; //暴击倍数
	unsigned speed;	//先手
	unsigned battlePower; //战力
	unsigned shield; //护盾值
	double   dam_inc_r; //伤害增加
	double   dam_dec_r; //伤害减免

	unsigned c_hit;	//连续命中次数
	unsigned c_n_crit; //连续未暴击次数

	double GetAttr(int  type)
	{
		if(type == e_type_maxhp)		return  hp;
		if(type == e_type_currhp) 		return  n_hp;
		if(type == e_type_losehp) 		return  l_hp;
		if(type == e_type_att) 			return  att;
		if(type == e_type_def) 			return  def;
		if(type == e_type_shield) 		return  shield;

		return 0;
	}

	//直接修改数值
	void ModifyByValue(int type, double value)
	{

		if(type == e_type_currhp)
			n_hp += value;
		else if(type == e_type_att)
			att  += value;
		else if(type == e_type_def)
			def  += value;
		else if(type == e_type_shield)
			shield += (unsigned)value;
	}

	//百分比修改
	double ModifyByRate(int type, double rate)
	{
		double old = 0.0;
		double ret = 0.0;
		if(type == e_type_currhp)
		{
			old = n_hp;
			n_hp += rate * hp;
			if(n_hp > hp)
				n_hp = hp;
			ret = n_hp - old;
		}
		else if(type == e_type_att)
		{
			old  = att;
			att  = (1 + rate) * att;

			ret = att -old;
		}
		else if(type == e_type_def)
		{
			old = def;
			def  = (1 + rate) * def;
			ret = def - old;
		}
		else if(type == e_type_shield)
		{
			old = shield;
			shield = (unsigned)((1 + rate) * shield);
			ret = shield - old;
		}

		debug_log("----------- type: %lf,  value: %u ---------", type, ret);
		return ret;
	}

	//减属性
	void DecAttr(double value, int type)
	{
		if(type == e_type_currhp)
			n_hp -= value;
		else if(type == e_type_att)
			att -= value;
		else if(type == e_type_def)
			def -= value;
		else if(type == e_type_shield)
			shield -= (unsigned)value;
	}

	HeroAttrItem()
		: id(0)
		, hp(0)
		, n_hp(0)
		, l_hp(0)
		, att(0)
		, def(0)
		, crit(0)
		, acrit(0)
		, dodge(0)
		, adodge(0)
		, critt(0)
		, speed(0)
		, battlePower(0)
		, shield(0)
		, dam_inc_r(0)
		, dam_dec_r(0)
		, c_hit(0)
		, c_n_crit(0)
	{
	}

	HeroAttrItem(unsigned c_id, double c_hp, double c_att, double c_def, unsigned c_crit, unsigned c_acrit
				,unsigned c_dodge, unsigned c_adodge, double c_critt, unsigned c_speed, unsigned c_battle_pow
				, unsigned c_shield)
		: id(c_id)
		, hp(c_hp)
		, n_hp(c_hp)
		, l_hp(c_hp)
		, att(c_att)
		, def(c_def)
		, crit(c_crit)
		, acrit(c_acrit)
		, dodge(c_dodge)
		, adodge(c_adodge)
		, critt(c_critt)
		, speed(c_speed)
		, battlePower(c_battle_pow)
		, shield(c_shield)
		, dam_inc_r(0)
		, dam_dec_r(0)
		, c_hit(0)
		, c_n_crit(0)
	{
	}


	//最终伤害
	double LastDam(double dam, bool isShield)
	{
		double ret = 0.0;
		if(isShield)
		{
			if(dam > shield)
			{
				ret = dam - shield;
				shield = 0;
			}
			else
			{
				shield -= (unsigned)dam;
			}
		}
		else
		{
			ret = dam;
		}

		return ret;
	}

	void Injure(double dam)
	{
		n_hp -= dam;
	}

	void SetMessage(ProtoBattle::ProtoBattleHero* msg)
	{
		msg->set_id(id);
		msg->set_hp(hp);
		msg->set_def(def);
		msg->set_att(att);
		msg->set_shield(shield);
		msg->set_battlepower(battlePower);
		msg->set_daminc(dam_inc_r);
		msg->set_damdec(dam_dec_r);
	}

	void SetMessage(ProtoBattleBase::ProtoBattleAttr* msg, unsigned type)
	{
		msg->set_heroid(id);
		if(type == e_type_currhp)
			msg->set_hp((int)(n_hp));
		if(type == e_type_shield)
			msg->set_shield((int)(shield));
		if(type == e_type_att)
			msg->set_att((int)(att));
		if(type == e_type_def)
			msg->set_def((int)(def));
	}

};


struct GameTeam
{
	unsigned uid;			//玩家id
	unsigned level;			//玩家等级
	unsigned hero_num;		//英雄数量
	unsigned n_c;			//必爆次数
	HeroAttrItem  attr[2];	//英雄属性
	unsigned  left_point;	//剩余点数
	unsigned  turn_sec;		//回合描述
	unsigned  index;		//当前出场
	double    last_hurt;	//上次受到的伤害
	RecordItem record; 		//每次效果相关数据

	GameTeam()
		: uid(0)
		, level(0)
		, hero_num(0)
		, n_c(0)
		, left_point(0)
		, turn_sec(0)
		, index(0)
		, last_hurt(0.0)
	{
	}

	void LastHurt(double value)
	{
		last_hurt = value;
	}

	double LastHurt()
    {
	    return last_hurt;
    }

	void ResetLastHurt()
	{
		last_hurt = 0.0;
	}

	void AddPoint(unsigned point)
	{
		left_point += point;
	}

	//消耗点数
	unsigned CostPoint(unsigned point)
	{
		if(left_point <= point)
			left_point = 0;
		else
			left_point -= point;

		return left_point;
	}
	void Reset()
	{
		if(left_point < MAX_POINTS)
			left_point = MAX_POINTS;
	}

	void SetMessage(ProtoBattle::ProtoBattleTeam* msg)
	{
		msg->set_uid(uid);
		msg->set_level(level);
		for(int i = 0;  i < hero_num && i < 2; ++i)
		{
			attr[i].SetMessage(msg->add_heros());
		}
	}

	void SetMessage(ProtoBattleBase::ProtoBattleTurn* msg)
	{
		if(record.dam > 0)
		{
			msg->set_dam((unsigned)record.Dam());
			msg->set_crit(record.IsCrited());
		}
		if(record.hurt_back > 0)
		{
			msg->set_hurtback(record.hurt_back);
		}
		if(record.hurt_trans == 1)
		{
			msg->set_hurttrans(true);
		}
		if(record.bomb == 1)
		{
			msg->set_bomb(true);
		}
	}

	void SetMessage(ProtoBattleBase::ProtoBattleTurnInfo* msg)
	{
		SetMessage(msg->mutable_info());

		msg->mutable_attr()->set_heroid(attr[index].id);
		if(record.dam > 0)
			attr[index].SetMessage(msg->mutable_attr(), e_type_currhp);
		if(record.attr_change == e_type_currhp)
			attr[index].SetMessage(msg->mutable_attr(), e_type_currhp);
		if(record.attr_change == e_type_shield)
			attr[index].SetMessage(msg->mutable_attr(), e_type_shield);
		if(record.attr_change == e_type_att)
			attr[index].SetMessage(msg->mutable_attr(), e_type_att);
		if(record.attr_change == e_type_def)
			attr[index].SetMessage(msg->mutable_attr(), e_type_def);

		debug_log("record, uid:%u, dam:%lf, attr_change: %u", uid, record.dam, record.attr_change);

	}

};


struct GameItem
{
	unsigned id;		//战斗id
	unsigned type;		//战斗类型
	GameTeam att;		//玩家信息
	GameTeam def;		//玩家信息
	unsigned attacking;	//当前出牌玩家 0: att, 1, def
	unsigned count;		//比赛人数
	unsigned winner;  //0: def胜, 1
	unsigned cur_type;		//当前效果类型
	unsigned last_outcard_ts; //上次出牌时戳

	GameTeam* cur_att; //当前出牌玩家
	GameTeam* cur_def; //当前没出牌玩家
	GameItem()
		: id(0)
		, type(0)
		, attacking(e_att)
		, count(0)
		, winner(0)
		, cur_type(0)
		, last_outcard_ts(0)
		, cur_att(nullptr)
		, cur_def(nullptr)
	{
	}
	void UpdataOutCardTs(unsigned ts)
	{
		last_outcard_ts = ts;
	}

	unsigned LastOutCardTs()
	{
		return last_outcard_ts;
	}

	void SetCurrType(unsigned type)
	{
		cur_type = type;
	}

	//当前出牌玩家
	unsigned CurrentPlayer()
	{
		return attacking;
	}

	void Clear(unsigned obj)
	{
		cur_type = 0;
		if(obj == e_att)
			att.record.ClearOnce();
		if(obj == e_def)
			def.record.ClearOnce();
	}

	//先手 0: att, 1, def
	unsigned First()
	{
		unsigned a = att.attr[0].speed + att.attr[1].speed;
		unsigned d = def.attr[0].speed + def.attr[1].speed;
		attacking = a >= d ? e_att : e_def;
		attacking = e_att;
		return attacking;
	}

	unsigned ChangeAttacking()
	{
		attacking = (attacking + 1) % e_side_max;
		if(attacking == e_att)
		{
			cur_att = &att;
			cur_def = &def;
		}
		else
		{
			cur_def = &att;
			cur_att = &def;
		}

		return attacking == e_att ? att.uid : def.uid;
	}

	unsigned NextUser()
	{
		return attacking == e_att ? def.uid : att.uid;
	}

	bool AttackerWin()
	{
		return winner == att_win ? true : false;
	}

	unsigned Attacking()
	{
		return attacking;
	}

	void CurAtt(GameTeam* ptr)
	{
		cur_att = ptr;
	}

	GameTeam* CurAtt()
	{
		return cur_att;
	}

	void CurDef(GameTeam* ptr)
	{
		cur_def = ptr;
	}

	GameTeam* CurDef()
	{
		return cur_def;
	}

	//设置赢家
	void SetWinner(unsigned obj)
	{
		winner = obj;
	}

	unsigned Winner()
	{
		return winner;
	}

	void SetMessage(ProtoBattleBase::ProtoBattleInfo* msg,  unsigned aim)
	{

		msg->set_actiontype(cur_type);

		if(aim == e_own)
		{
			if(attacking == e_att)
				msg->set_aim(e_att);
			else
				msg->set_aim(e_def);
		}
		else
		{
			if(attacking == e_att)
				msg->set_aim(e_def);
			else
				msg->set_aim(e_att);
		}

		debug_log("ProtoBattleInfo, atype: %u, cur_type: %u, aim: %u, attacking: %u", msg->actiontype(), cur_type, msg->aim(), attacking);
	}
};


struct GameData
{
	GameItem item[MEMORY_GAME_NUM];
};

typedef unordered_map<unsigned, vector<BuffItem>> Buffs;

class DataGameManager : public MemorySingleton<GameData, MEMORY_GAME>, public CSingleton<DataGameManager>
{
private:
	friend class CSingleton<DataGameManager>;
	DataGameManager(){}
	virtual ~DataGameManager(){}

public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();

	//获取索引
	unsigned GetFreeIndex()
	{
		if(free_index_.empty())
			return (unsigned)-1;

		return *(free_index_.begin());
	}

	GameItem& GetData(unsigned battleid);

	//创建比赛
	unsigned CreateGame();
	//添加玩家到比赛
	int AddUser(unsigned uid, unsigned battleid, unsigned level);

	//设置英雄属性
	int SetHeroAttr(unsigned uid, unsigned battleid, unsigned heroid, const HeroAttrItem& attr);

	//设置战斗卡包 user:id=uid, npc:id=battleid
	void SetCardBag(unsigned battleid, unsigned id, vector<CardItem>& cardbags);

	//获取战斗卡包user:id=uid, npc:id=battleid
	vector<CardItem>& GetCardBag(unsigned battleid, unsigned id);

	//将卡加入卡包
	void AddCardBag(unsigned battleid, unsigned id, CardItem card);

	//加入弃牌包
	void AddCardTemp(unsigned battleid, unsigned id, CardItem& card);

	//获取弃牌包
	vector<CardItem>& GetTempCards(unsigned battleid, unsigned id);

//	CardItem* GetHandCards(unsigned battleid, unsigned attacker);

	vector<CardItem>& GetHandCards(unsigned battleid, unsigned id);

	//比赛是否合法
	bool IsValid(unsigned battleid);

	//比赛处理
	bool Impl(unsigned battleid);

	void Clear(unsigned battleid);

	int BuffCount(unsigned battleid, unsigned id, unsigned type)
	{
		if(0 == buff_.count(battleid) || 0 == buff_[battleid].count(id) || 0 == buff_[battleid][id].count(type))
			return 0;
		return buff_[battleid][id][type].front().count;
	}

	BuffItem& GetBuff(unsigned battleid, unsigned id, unsigned type)
	{
		return buff_[battleid][id][type].front();
	}

	vector<BuffItem>& GetBuffs(unsigned battleid, unsigned id, unsigned type)
	{
		return buff_[battleid][id][type];
	}

	Buffs& GetBuffs(unsigned battleid, unsigned id)
	{
		return buff_[battleid][id];
	}

	int AddBuff(unsigned battleid, unsigned id, unsigned type, BuffItem& buff)
	{
		 buff_[battleid][id][type].push_back(std::move(buff));
		 return R_SUCCESS;
	}

	int ClearBuff(unsigned battleid, unsigned id, unsigned type, unsigned value);

private:
	//设置没有暴击次数
	void SetNoCritCount(unsigned level,  unsigned& n_c);
	unordered_map<unsigned, unsigned> total_match_; //battleid=>索引
	unordered_map<unsigned, map<unsigned, vector<CardItem>>> cards_bag_; //战斗卡包
	unordered_map<unsigned, map<unsigned, vector<CardItem>>> temp_cards_; //弃牌包
	unordered_map<unsigned, map<unsigned, vector<CardItem>>> hand_cards_; //手牌

	unordered_map<unsigned, map<unsigned, Buffs>> buff_; //buff



	set<unsigned> free_index_;	//能用的索引
};


#endif /* APP_DATA_DATAGAME_H_ */
