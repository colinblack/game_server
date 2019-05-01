/*
 * EquipCfgWrap.h
 *
 *  Created on: 2016-9-9
 *      Author: dawx62fac
 */

#ifndef EQUIPCFGWRAP_H_
#define EQUIPCFGWRAP_H_

#include "DataInc.h"

class EquipCfgWrap
{
public:
	EquipCfgWrap();

public:
	const EquipmentConfig::EquipList EquipList(){return cfg_;}
	const EquipmentConfig::Equip & GetEquip(unsigned equip_id) const;

	//获取装备购买价格
	int GetEquipPrice(unsigned eqid);

	//判断是否是装备
	bool IsEquipment(unsigned eqid);

	//判断是否是勋章
	bool IsMedal(unsigned eqid);
    
	//获取套装类型
	bool IsEquipSuit(unsigned eqid);

	bool IsEquipSuitByType(int type);

	//获取英雄经验道具增长的经验
	int GetEquipExpByEqid(unsigned eqid);

	//根据装备id获取洗练的最大等级
	int GetSubMaxLevel(unsigned eqid);

	//判断两件装备属性相减的结果
	int GetPropertySubValue(unsigned srceqid, unsigned dsteqid);

	//根据配置类型获取对应的属性
	void GetFightAttr(int type, int level, HeroFightAttr& attr);
	void GetFightAttr(int types[], int levels[], int len, HeroFightAttr& attr);
	//获取装备属性配置
	void GetEquipBaseFightAttr(int equipId, HeroFightAttr& attr);

	//礼包
	bool IsGifgBag(unsigned eqid);

	const EquipmentConfig::TimeLimitProp& GetTimeLimitProp(unsigned eqid) const;

	const EquipmentConfig::NormalGiftBag& GetNormalGiftBag(unsigned eqid) const;
	const EquipmentConfig::LuckGiftBag&	GetLuckGiftBag(unsigned eqid) const;
private:
	DemoHeroProperty Type2Property(int type) const;

	const EquipmentConfig::EquipList& cfg_;
};


#endif /* EQUIPCFGWRAP_H_ */
