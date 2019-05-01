/*
 * HeroPropertyManager.cpp
 *
 *  Created on: 2016-9-2
 *      Author: Ralf
 */

#include "HeroPropertyManager.h"

HeroFightAttr::HeroFightAttr()
{
	memset(val_, 0, sizeof(val_));
}

void HeroFightAttr::Clear()
{
	memset(val_, 0, sizeof(val_));
}

void HeroFightAttr::SetAttr(DemoHeroProperty attr, int val)
{
	val_[(int)attr] = val;
}

void HeroFightAttr::AddAttr(DemoHeroProperty attr, int val)
{
	val_[(int)attr] += val;
}

int HeroFightAttr::GetAttr(DemoHeroProperty attr) const
{
	return val_[(int)attr];
}

void HeroFightAttr::AdditionFightBase(map<unsigned, double> & addition_percent)
{
	//属性计算
	for(map<unsigned, double>::iterator diter = addition_percent.begin(); diter != addition_percent.end(); ++diter)
	{
		int subtype = diter->first;
		double factor = diter->second;

		switch(subtype)
		{
			case property_type_attack_percent : val_[DemoHeroProperty_attack] += val_[DemoHeroProperty_attack] * factor / 100; break;
			case property_type_defend_percent : val_[DemoHeroProperty_defend] += val_[DemoHeroProperty_defend] * factor / 100; break;
			case property_type_hp_percent : val_[DemoHeroProperty_hp] += val_[DemoHeroProperty_hp] * factor / 100; break;
			case property_type_strong_percent : val_[DemoHeroProperty_skill_extra] += val_[DemoHeroProperty_skill_extra] * factor / 100; break;
			case property_type_control_percent : val_[DemoHeroProperty_skill_anti] += val_[DemoHeroProperty_skill_anti] * factor / 100; break;
			case property_type_strong_attack_percent : val_[DemoHeroProperty_attack_extra] += val_[DemoHeroProperty_attack_extra] * factor / 100; break;
			case property_type_strong_defend_percent : val_[DemoHeroProperty_attack_anti] += val_[DemoHeroProperty_attack_anti] * factor / 100; break;
			default : break;
		}
	}
}
//////////////////////////////////////////////////////////////////////
void HeroPropertyItem::UpdateProperty(const HeroFightAttr& fight_attr)
{
	for (int i = DemoHeroProperty_hp
			;i < DemoHeroProperty_max
			; i++)
	{
		property[i] = fight_attr.GetAttr((DemoHeroProperty)i);
	}

	//更新血量
	for (int i = 0; i < SG17_HERO_SOLDIER; ++i)
	{
		if (hp[i] > property[DemoHeroProperty_hp])
		{
			hp[i] = property[DemoHeroProperty_hp];
		}
	}
}

void HeroPropertyItem::GetHeroFightAttr(HeroFightAttr& fight_attr) const
{
	fight_attr.Clear();
	for (int i = DemoHeroProperty_hp
			;i < DemoHeroProperty_max
			; i++)
	{
		fight_attr.SetAttr((DemoHeroProperty)i, property[i]);
	}
}

unsigned HeroPropertyItem::GetTotalTroops(unsigned rows)
{
	unsigned nFactRows = rows > SG17_HERO_SOLDIER ? SG17_HERO_SOLDIER : rows;
	return nFactRows * property[DemoHeroProperty_hp] * SG17_HERO_SOLDIER_SUB;
}

unsigned HeroPropertyItem::GetActualTroops(unsigned nTotalRows)
{
	unsigned nFactRows = nTotalRows > SG17_HERO_SOLDIER ? SG17_HERO_SOLDIER : nTotalRows;
	int nVal = 0;
	for (int i = nFactRows - 1; i >= 0; i--)
	{
		nVal += hp[i] * SG17_HERO_SOLDIER_SUB;
	}

	return nVal;
}

int HeroPropertyItem::GetFreeTroops(unsigned nTotalRows)
{
	unsigned nFactRows = nTotalRows > SG17_HERO_SOLDIER ? SG17_HERO_SOLDIER : nTotalRows;
	int nVal = 0;
	for (int i = nFactRows - 1; i >= 0; i--)
	{
		nVal += hp[i];
	}

	return (nFactRows * property[DemoHeroProperty_hp] - nVal) * SG17_HERO_SOLDIER_SUB;
}

bool	HeroPropertyItem::IsFullTroops(unsigned nTotalRows)
{
	int nFactRows = nTotalRows > SG17_HERO_SOLDIER ? SG17_HERO_SOLDIER : nTotalRows;
	for (int i = nFactRows - 1; i >= 0; i--)
	{
		if (hp[i] < property[DemoHeroProperty_hp])
		{
			return false;
		}
	}

	return true;
}

unsigned	HeroPropertyItem::CalcRealRecruitSoldires(unsigned nTotalRows, int rate)
{
	unsigned result = 0;
	int nFactRows = nTotalRows > SG17_HERO_SOLDIER ? SG17_HERO_SOLDIER : nTotalRows;
	int limit = property[DemoHeroProperty_hp] /** SG17_HERO_SOLDIER_SUB*/;
	for (int i = nFactRows - 1; i >= 0; i--)
	{
		if (hp[i] >= limit) continue;
		if (rate <= 0) break;

		result += limit - hp[i];
	}

	result *= 3;

	return result  > rate ? rate : result;
}

void HeroPropertyItem::RecruitSoldires(unsigned nTotalRows, int rate)
{
	rate /= SG17_HERO_SOLDIER_SUB;

	int nFactRows = nTotalRows > SG17_HERO_SOLDIER ? SG17_HERO_SOLDIER : nTotalRows;
	int limit = property[DemoHeroProperty_hp];
	for (int i = nFactRows - 1; i >= 0; i--)
	{
		if (hp[i] >= limit) continue;
		if (rate <= 0) break;

		int dVal = limit - hp[i];
		if (rate <= dVal)
		{
			hp[i] += rate;
			rate = 0;
		}
		else
		{
			hp[i] = limit;
			rate -= dVal;
		}
	}
}


void HeroPropertyItem::FullSoldires(unsigned nTotalRows)
{
	int nFactRows = nTotalRows > SG17_HERO_SOLDIER ? SG17_HERO_SOLDIER : nTotalRows;
	int limit = property[DemoHeroProperty_hp];
	for (int i = nFactRows - 1; i >= 0; i--)
	{
		hp[i] = limit;
	}
}

//////////////////////////////////////////////////////////////////////

int HeroPropertyManager::OnInit() {
	for(unsigned i=0;i<MEMORY_HERO_PROPERTY_NUM*SG17_HERO_NUM;++i)
	{
		if(m_data->item[i].index.uid != 0)
		{
			m_map[m_data->item[i].index] = i;
			m_indexmap[m_data->item[i].index.uid].insert(m_data->item[i].index);
		}
		else
			m_freeIndex.insert(i);
	}
	return 0;
}
