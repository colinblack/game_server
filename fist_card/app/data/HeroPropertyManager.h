#ifndef HEROPROPERTYMANAGER_H_
#define HEROPROPERTYMANAGER_H_

#include "Kernel.h"
#include "DataInc.h"

class HeroAttr
{
public:
	HeroAttr();
	void Clear();

	void 	 SetAttr(HeroProperty attr, unsigned val);
	void 	 AddAttr(HeroProperty attr, unsigned val);
	unsigned GetAttr(HeroProperty attr) const;

	HeroAttr& operator +=(const HeroAttr& obj)
	{
		for (int i = 0; i < HeroProperty_max; i++)
		{
			val_[(HeroProperty)i] += obj.val_[(HeroProperty)i];
		}

		return *this;
	}

	HeroAttr operator +(const HeroAttr& obj)
	{
		HeroAttr result;
		for (int i = 0; i < HeroProperty_max; i++)
		{
			HeroProperty prop = (HeroProperty)i;
			result.val_[prop] = val_[prop] + obj.val_[prop];
		}

		return result;
	}

	bool operator ==(const HeroAttr& obj)
	{
		for (int i = 0; i < HeroProperty_max; i++)
		{
			HeroProperty prop = (HeroProperty)i;
			if (val_[prop] != obj.val_[prop])
			{
				return false;
			}
		}

		return true;
	}

	void FullMessage(ProtoHero::HeroBaseInfoCPP* hero) const
	{
		hero->set_hp(GetAttr(HeroProperty_hp));
		hero->set_att(GetAttr(HeroProperty_attack));
		hero->set_def(GetAttr(HeroProperty_defend));
		hero->set_first(GetAttr(HeroProperty_first));
		hero->set_hit(GetAttr(HeroProperty_hit));
		hero->set_dodge(GetAttr(HeroProperty_dodge));
		hero->set_critstrike(GetAttr(HeroProperty_crit_strike));
		hero->set_critresist(GetAttr(HeroProperty_crit_resist));
		hero->set_critrate(GetAttr(HeroProperty_crit_rate));
	}
	template<class T>
	void AddtionPercent(map<unsigned, double> & addition_percent, T attr)
	{
		//血量加成
		if(attr.has_hp_add())
			addition_percent[HeroProperty_hp] += attr.hp_add();
		//攻击加成
		if(attr.has_att_add())
			addition_percent[HeroProperty_attack] += attr.att_add();
		//防御加成
		if(attr.has_def_add())
			addition_percent[HeroProperty_defend] += attr.def_add();

	}

	template<class T>
	void AddtionValue(map<unsigned, unsigned> &addition_value, T attr)
	{
		//血量
		if(attr.has_hp())
			addition_value[HeroProperty_hp] += attr.hp();
		//攻击
		if(attr.has_att())
			addition_value[HeroProperty_attack] += attr.att();
		//防御
		if(attr.has_def())
			addition_value[HeroProperty_defend] += attr.def();
		//先手
		if(attr.has_first())
			addition_value[HeroProperty_first] += attr.first();
		//命中
		if(attr.has_hit())
			addition_value[HeroProperty_hit] += attr.hit();
		//闪避
		if(attr.has_dodge())
			addition_value[HeroProperty_dodge] += attr.dodge();
		//暴击
		if(attr.has_critstrike())
			addition_value[HeroProperty_crit_strike] += attr.critstrike();

		//暴击伤害
		if(attr.has_critrate())
			addition_value[HeroProperty_crit_rate] += attr.critrate();
		//抗暴击
		if(attr.has_critresist())
			addition_value[HeroProperty_crit_resist] += attr.critresist();

	}

	void SetAllAttr(map<unsigned, double> & addition_percent, map<unsigned, unsigned> &addition_value, unsigned heroid, unsigned level);

private:
	unsigned val_[HeroProperty_max]; //英雄属性
};


#endif /* HEROPROPERTYMANAGER_H_ */
