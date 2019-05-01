/*
 * EquipCfgWrap.cpp
 *
 *  Created on: 2016-9-9
 *      Author: dawx62fac
 */

#include "EquipCfgWrap.h"
#include "ConfigManager.h"
#include "ConfigWrap.h"

EquipCfgWrap::EquipCfgWrap()
	: cfg_(ConfigManager::Instance()->equipment.m_config)
{

}

const EquipmentConfig::Equip & EquipCfgWrap::GetEquip(unsigned equip_id) const
{
	if (!ConfigManager::Instance()->m_equipmap.count(equip_id))
	{
		error_log("equip_cfg_error. equip_id:%u", equip_id);
		throw std::runtime_error("equip_cfg_error");
	}

	unsigned eindex = ConfigManager::Instance()->m_equipmap[equip_id];

	return cfg_.equips(eindex);
}

int EquipCfgWrap::GetEquipPrice(unsigned eqid)
{
	if (!ConfigManager::Instance()->mapEqidPrice.count(eqid))
	{
		error_log("[GetEquipPrice] get eqid's price error.eqid=%u", eqid);
		throw std::runtime_error("get_price_error");
	}

	return ConfigManager::Instance()->mapEqidPrice[eqid];
}

bool EquipCfgWrap::IsEquipment(unsigned eqid)
{
	//先判断是否是套装
	bool isSuit = IsEquipSuit(eqid);

	if (isSuit)
	{
		return true;
	}

	const EquipmentConfig::Equip & equipcfg = GetEquip(eqid);
	int type = equipcfg.type();

	if (equip_type_normal == type || equip_type_medal == type)
	{
		return true;
	}

	return false;
}

bool EquipCfgWrap::IsMedal(unsigned eqid)
{
	const EquipmentConfig::Equip & equipcfg = GetEquip(eqid);
	int type = equipcfg.type();

	if (equip_type_medal == type)
	{
		return true;
	}

	return false;
}

bool EquipCfgWrap::IsEquipSuit(unsigned eqid)
{
	const EquipmentConfig::Equip & equipcfg = GetEquip(eqid);
	int type = equipcfg.type();

	return IsEquipSuitByType(type);
}

bool EquipCfgWrap::IsEquipSuitByType(int type)
{
	if (equip_type_suit_one == type || equip_type_suit_two == type || equip_type_suit_three == type
			|| equip_type_suit_four == type || equip_type_suit_five == type)
	{
		return true;
	}

	return false;
}

int EquipCfgWrap::GetEquipExpByEqid(unsigned eqid)
{
	int exp = 0;

	for(int i = 0; i < cfg_.equipexp_size(); ++i)
	{
		if (cfg_.equipexp(i).eqid() == eqid)
		{
			exp = cfg_.equipexp(i).exp();
			break;
		}
	}

	return exp;
}

int EquipCfgWrap::GetSubMaxLevel(unsigned eqid)
{
	int maxlevel = -1;
	SmeltConfigWrap smelfconfig;  //洗练配置
	const EquipmentConfig::Equip & equipcfg = GetEquip(eqid);

	if (IsEquipSuit(eqid)) //套装
	{
		int suittype = equipcfg.type();
		maxlevel = smelfconfig.GetSuitMaxLevel(suittype);
	}
	else
	{
		//获得品质和品质对应的最高等级
		maxlevel = smelfconfig.GetCharacterMaxlevel(equipcfg.character());
	}

	return maxlevel;
}

int EquipCfgWrap::GetPropertySubValue(unsigned srceqid, unsigned dsteqid)
{
	//判断是否同一部位，同一部位才能比较
	const EquipmentConfig::Equip & equipcfgA = GetEquip(srceqid);
	const EquipmentConfig::Equip & equipcfgB = GetEquip(dsteqid);

	//只比较同一部位的装备
	if (equipcfgA.postion() != equipcfgB.postion())
	{
		return 0;
	}

	//先比较品质
	if (equipcfgA.character() > equipcfgB.character())
	{
		return 1;
	}
	else if (equipcfgA.character() < equipcfgB.character())
	{
		return -1;
	}

	//品质相同，则比较数值，此时，排除勋章，因为勋章的属性是随机生成的
	if (equip_type_medal == equipcfgA.type())
	{
		return 0;
	}

	int valsumA = 0;
	int valsumB = 0;

	for(int i = 0; i < equipcfgA.born_size(); ++i)
	{
		valsumA += equipcfgA.born(i).val();
	}

	for(int i = 0; i < equipcfgB.born_size(); ++i)
	{
		valsumB += equipcfgB.born(i).val();
	}

	//比较基础属性的大小
	if (valsumA > valsumB)
	{
		return 1;
	}
	else if (valsumA < valsumB)
	{
		return -1;
	}

	return 0;
}

DemoHeroProperty EquipCfgWrap::Type2Property(int type) const
{
	if (type < 1 || type > 7)
	{
		error_log("equip_type: %d", type);
		throw std::runtime_error("get_cfg_params_equip_type_error");
	}

	DemoHeroProperty propTb[7] = {
		DemoHeroProperty_attack,
		DemoHeroProperty_defend	,
		DemoHeroProperty_hp,
		DemoHeroProperty_skill_extra,
		DemoHeroProperty_skill_anti,
		DemoHeroProperty_attack_extra,
		DemoHeroProperty_attack_anti
	};

	return propTb[type - 1];
}

void EquipCfgWrap::GetEquipBaseFightAttr(int equipId, HeroFightAttr& attr)
{
	attr.Clear();

	const EquipmentConfig::Equip& equipCfg = EquipCfgWrap::GetEquip(equipId);
	if (equipCfg.type() == 1 || IsEquipSuit(equipId))
	{
		for (int i = 0; i < equipCfg.born_size(); ++i)
		{
			attr.AddAttr(Type2Property(equipCfg.born(i).type())
					, equipCfg.born(i).val());
		}
	}
}

void EquipCfgWrap::GetFightAttr(int types[], int levels[], int len, HeroFightAttr& result)
{
	/*1.攻击 2.防御 3.血量 4.强壮 5.掌控 6.强攻  7.强防*/
	/*
	 *	 等级	攻击	防御	血量	强壮  	掌控	强攻	强防
	 *
	 *	1	18	10	40	60	48	30	24
	 *	2	21	12	48	80	64	40	32
	 *	3	28	16	64	100	80	50	40
	 *	4	36	20	80	120	96	60	48
	 *	5	54	30	120	180	144	90	72
	 */
	/*
	const int dataTb[5][7] = {
		{18,10,40,60,48,30,24},
		{21,12,48,80,64,40,32},
		{28,16,64,100,80,50,40},
		{36,20,80,120,96,60,48},
		{54,30,120,180,144,90,72},
	};
	*/

	result.Clear();
	SmeltConfigWrap smeltconfig;  //洗练配置

	for (int i = 0; i < len; i++)
	{
		if (types[i] == 0 || levels[i] == 0) continue;

		if (types[i] < 1 || types[i] > 7)
		{
			error_log("equip_type: %d", types[i]);
			throw std::runtime_error("get_cfg_params_equip_type_error");
		}

		//以洗练配置中等级数组的长度为最大值
		if (levels[i] < 1 || levels[i] > smeltconfig.EquipSmelt().levelpro_size())
		{
			error_log("equip_level: %d", levels);
			throw std::runtime_error("get_cfg_params_equip_level_error");
		}

		int val = smeltconfig.GetValueByTypeAndlevel(types[i], levels[i]);
		result.AddAttr(Type2Property(types[i]), val);
	}
}

void EquipCfgWrap::GetFightAttr(int type, int level, HeroFightAttr& attr)
{
	attr.Clear();

	int types[1], levels[1];
	types[0] = type;
	levels[0] = level;

	GetFightAttr(types, levels, 1, attr);
}

const EquipmentConfig::TimeLimitProp& EquipCfgWrap::GetTimeLimitProp(unsigned eqid) const
{
	for (int i = 0; i < cfg_.time_limit_prop_size(); i++)
	{
		if (cfg_.time_limit_prop(i).eqid() == eqid)
		{
			return cfg_.time_limit_prop(i);
		}
	}

	error_log("eqid: %u, time_limit_prop_error.", eqid);
	throw std::runtime_error("time_limit_prop_error_cfg");
}

const EquipmentConfig::NormalGiftBag& EquipCfgWrap::GetNormalGiftBag(unsigned eqid) const
{
	for (int i = 0; i < cfg_.normal_giftbag_size(); ++i)
	{
		if (cfg_.normal_giftbag(i).eqid() == eqid)
		{
			return cfg_.normal_giftbag(i);
		}
	}

	error_log("eqid: %u, normal_gift_bag_error.", eqid);
	throw std::runtime_error("not_normal_gift_bag_cfg");
}

const EquipmentConfig::LuckGiftBag&	EquipCfgWrap::GetLuckGiftBag(unsigned eqid) const
{
	for (int i = 0; i < cfg_.luck_giftbag_size(); ++i)
	{
		if (cfg_.luck_giftbag(i).eqid() == eqid)
		{
			return cfg_.luck_giftbag(i);
		}
	}

	error_log("eqid: %u, luck_gift_bag_error.", eqid);
	throw std::runtime_error("not_luck_gift_bag_cfg");
}
