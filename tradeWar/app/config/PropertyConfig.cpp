/*
 * PropertyConfig.cpp
 *
 *  Created on: 2015-9-2
 *      Author: Administrator
 */

#include "PropertyConfig.h"
#include <math.h>

map<string,uint32_t> PropertyConfig::m_attr2Idx;
map<uint32_t,string> PropertyConfig::m_idx2Attr;
bool PropertyConfig::m_bInit = PropertyConfig::attrMapInit();

#define ADD_ATTR_MAP(attr,idx) \
		PropertyConfig::m_attr2Idx[attr] = idx;\
		PropertyConfig::m_idx2Attr[idx] = attr


bool PropertyConfig::attrMapInit(){

	ADD_ATTR_MAP("l",AP_LEVEL);
	ADD_ATTR_MAP("t",AP_TYPE);
	ADD_ATTR_MAP("x",AP_X);
	ADD_ATTR_MAP("y",AP_Y);
	ADD_ATTR_MAP("bornlv",AP_BS_LVL);
	ADD_ATTR_MAP("bornlv2",AP_BS_LVL2);
	ADD_ATTR_MAP("bud",AP_HERO_BUNKER);
	ADD_ATTR_MAP("status",AP_STATUS);
	ADD_ATTR_MAP("exp",AP_EXP);
	ADD_ATTR_MAP("grade",AP_GRADE);
	ADD_ATTR_MAP("hp",AP_HP);
	ADD_ATTR_MAP("pt",AP_PT);	//
	ADD_ATTR_MAP("cr",AP_CR);	//修复剩余时间
	ADD_ATTR_MAP("cu",AP_CU);	//升级剩余时间
	ADD_ATTR_MAP("cp",AP_CP);	//产满剩余时间
	ADD_ATTR_MAP("cb",AP_CB);	//建造剩余时间
	ADD_ATTR_MAP("q",AP_QUALITY);
	ADD_ATTR_MAP("count",AP_COUNT);
	ADD_ATTR_MAP("s",AP_STRONG);
	ADD_ATTR_MAP("deadline",AP_DEADLINE);
	ADD_ATTR_MAP("hud",AP_HUD);	//英雄的UD
	ADD_ATTR_MAP("xi",AP_EQ_XI);
	ADD_ATTR_MAP("st",AP_CAPACITY);	//资源建筑当前容量
	ADD_ATTR_MAP("ud",AP_UD);
	ADD_ATTR_MAP("upts",AP_UPTS);
	ADD_ATTR_MAP("r1",AP_P1);
	ADD_ATTR_MAP("r2",AP_P2);
	ADD_ATTR_MAP("r3",AP_P3);
	ADD_ATTR_MAP("r4",AP_P4);
	ADD_ATTR_MAP("r5",AP_P5);
	ADD_ATTR_MAP("rs",AP_RIDE_STAR);
	ADD_ATTR_MAP("rl",AP_RIDE_LEVEL);
	ADD_ATTR_MAP("star",AP_STAR);
	ADD_ATTR_MAP("ctcd",AP_TRAIN_GAIN_EXP);
	ADD_ATTR_MAP("state",AP_STATE);
	ADD_ATTR_MAP("rsci1",AP_RIDE_SCIENCE1);
	ADD_ATTR_MAP("rsci2",AP_RIDE_SCIENCE2);
	ADD_ATTR_MAP("upslot",AP_UPGRADE_SLOT);
	ADD_ATTR_MAP("seud",AP_STONE_EUD);//宝石镶嵌位置
	ADD_ATTR_MAP("sslot",AP_STONE_SLOT);//宝石镶嵌位置
	ADD_ATTR_MAP("elock",AP_EQUIP_LOCK);//宝石镶嵌位置
	ADD_ATTR_MAP("cdt",AP_CD_TIME);
	ADD_ATTR_MAP("spirit",AP_SPIRIT);
	ADD_ATTR_MAP("jl",AP_ENERGY);
	ADD_ATTR_MAP("ce",AP_CE);
	ADD_ATTR_MAP("lc",AP_LOCK_COUNT);

	// 洗炼属性
	ADD_ATTR_MAP("hp1",AP_MAX_HP);
	ADD_ATTR_MAP("hd1",AP_HD);
	ADD_ATTR_MAP("ha1",AP_HA);
	ADD_ATTR_MAP("bp1",AP_BP);
	ADD_ATTR_MAP("ip1",AP_IP);
	ADD_ATTR_MAP("ebp1",AP_EBP);
	ADD_ATTR_MAP("hr1",AP_HR);
	ADD_ATTR_MAP("mp1",AP_MAX_MP);
	ADD_ATTR_MAP("csmp",AP_MP);
	ADD_ATTR_MAP("range",AP_RANGE);
	ADD_ATTR_MAP("rp2",AP_ATTACK_SPEED_RATE);
	ADD_ATTR_MAP("sp2",AP_MOVE_SPEED_RATE);
	ADD_ATTR_MAP("ibat",AP_BASE_RATE);
	ADD_ATTR_MAP("buddy",AP_BUDDY_POS);

	ADD_ATTR_MAP("hp2",AP_HP_RATE);
	ADD_ATTR_MAP("hd2",AP_HD_RATE);
	ADD_ATTR_MAP("ha2",AP_HA_RATE);
	ADD_ATTR_MAP("bp2",AP_BP_RATE);
	ADD_ATTR_MAP("ip2",AP_IP_RATE);
	ADD_ATTR_MAP("ebp2",AP_EBP_RATE);
	ADD_ATTR_MAP("hs",AP_WALL_HS);
	return true;
}

PropertyConfig::~PropertyConfig()
{
}

PropertyConfig * PropertyConfig::getInstance()
{
	static PropertyConfig inst;
	return & inst;
}

int PropertyConfig::getDataType(int type)
{
	switch (type)
	{
		case AP_X:
		case AP_Y:
			return (DT_INT);
		case AP_HA_RATE:
		case AP_HD_RATE:
		case AP_MOVE_SPEED_RATE:
		case AP_ATTACK_SPEED_RATE:
		case AP_BP_RATE:
		case AP_EBP_RATE:
		case AP_HP_RECOVE_RATE:
		case AP_MP_RECOVE_RATE:
		case AP_HIRE_FRONE_RATE:
		case AP_TRAIN_FRONE_RATE:
		case AP_MA_RATE:
		case AP_MD_RATE:
		case AP_HP_RATE:
		case AP_MP_RATE:
		case AP_CAPACITY_RATE:
		case AP_PRODUCT_RATE:
		case AP_IP_RATE:
		case AP_SKILL_CTL_RATE:
		case AP_SKILL_STRONG_RATE:
		case AP_SKILL_WEEK_RATE:
		case AP_SKILL_STATE_UP_RATE:
		case AP_PT:
			return (DT_FLOAT);
		default:
			return (DT_UNSIGNED_INT);
	};
	return DT_UNSIGNED_INT;
}
bool PropertyConfig::setAttr(Json::Value & value, int ap, Property & prop)
{
	map<uint32_t,string>::iterator attrIter = m_idx2Attr.find(ap);
	if(attrIter == m_idx2Attr.end())
	{
		return false;
	}
	int type = PropertyConfig::getDataType(ap);
	const string& attr = attrIter->second;
	switch(type)
	{
	case DT_INT:
		value[attr] = prop.pi;
		break;
	case DT_FLOAT:
		value[attr] = prop.pf;
		break;
	case DT_UNSIGNED_INT:
		value[attr] = prop.pui;
		break;
	}

	return true;
}
// 比例属性加成
bool PropertyConfig::accumulateByRateProps(PropertySets & rateProps, PropertySets & props)
{
	for(PropertySets::iterator it = rateProps.begin(); it != rateProps.end(); ++it)
	{
		int addAttr = attrRateToAdd(it->first);
		int type = getDataType(addAttr);
		switch(type)
		{
		case DT_INT:
			 props[addAttr].pi += props[addAttr].pi * it->second.pf * 0.01;
			 break;
		case DT_FLOAT:
			 props[addAttr].pf += props[addAttr].pf * it->second.pf * 0.01;
			 break;
		case DT_UNSIGNED_INT:
			 props[addAttr].pui += props[addAttr].pui * it->second.pf * 0.01;
			 break;
		}
	}
	return true;
}
bool PropertyConfig::accumulateByRate(double rate, PropertySets & props, PropertySets & nextProps)
{
	for(PropertySets::iterator it = nextProps.begin(); it != nextProps.end(); ++it)
	{
		if (!props.count(it->first))
		{
			continue;
		}
		int type = getDataType(it->first);
		switch(type)
		{
			case DT_INT:
			{
				int add = (it->second.pi - props[it->first].pi) * rate;
				props[it->first].pi += add<0 ? 0 : add;
				break;
			}
			case DT_FLOAT:
			{
				float add = (float)(it->second.pf - props[it->first].pf) * rate;
				props[it->first].pf += add<0 ? 0 : add;
				break;
			}
			case DT_UNSIGNED_INT:
			{
				int add = (it->second.pui - props[it->first].pui) * rate;
				props[it->first].pui += add<0 ? 0 : add;
				break;
			}
		}
	}
	return true;
}
// 属性集合累加
bool PropertyConfig::accumulateProps(PropertySets & newProps, PropertySets & baseProps)
{
	for(PropertySets::iterator iter = newProps.begin(); iter != newProps.end(); ++iter)
	{
		int type = getDataType(iter->first);
		switch(type)
		{
		case DT_INT:
			 baseProps[iter->first].pi += iter->second.pi;
			 break;
		case DT_FLOAT:
			 baseProps[iter->first].pf += iter->second.pf;
			 break;
		case DT_UNSIGNED_INT:
			 baseProps[iter->first].pui += iter->second.pui;
			 break;
		}
	}
	return true;
}
bool PropertyConfig::accumulateByLevel(PropertySets & minProps, PropertySets & baseProps, PropertySets & curProps)
{
	for(PropertySets::iterator iter = baseProps.begin(); iter != baseProps.end(); ++iter)
	{
		if (iter->first == AP_MAX_HP || iter->first == AP_HD || iter->first == AP_HA)
		{
			curProps[iter->first].pui += round((iter->second.pui - minProps[iter->first].pui) * 0.2);
		}
	}
	return true;
}
bool PropertyConfig::accumulateByBaseRate(PropertySets & base, double rate, PropertySets & props)
{
	for(PropertySets::iterator iter = base.begin(); iter != base.end(); ++iter)
	{
		if (iter->first == AP_MAX_HP || iter->first == AP_HD || iter->first == AP_HA)
		{
			props[iter->first].pui += ceil(static_cast<double>(iter->second.pui) * rate);
		}
	}
	return true;
}
int PropertyConfig::attrRateToAdd(int rateAttr)
{
	switch(rateAttr)
	{
	case AP_HA_RATE:
		return AP_HA;
	case AP_HD_RATE:
		return AP_HD;
	case AP_MOVE_SPEED_RATE:
		return AP_SP;
	case AP_ATTACK_SPEED_RATE:
		return AP_RP;
	case AP_BP_RATE:
		return AP_BP;
	case AP_EBP_RATE:
		return AP_EBP;
	case AP_MA_RATE:
		return AP_MA;
	case AP_MD_RATE:
		return AP_MD;
	case AP_HP_RATE:
		return AP_MAX_HP;
	case AP_MP_RATE:
		return AP_MP;
	case AP_CAPACITY_RATE:
		return AP_CAPACITY;
	case AP_IP_RATE:
		return AP_IP;
	default:
		error_log("no_match_addAttr&rateAttr=%u", rateAttr);
		break;
	}
	return AP_MAX;
}
