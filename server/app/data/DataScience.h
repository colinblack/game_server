/*
 * DataScience.h
 *
 *  Created on: 2016-9-14
 *      Author: dawx62fac
 */

#ifndef DATASCIENCE_H_
#define DATASCIENCE_H_

#include "Kernel.h"

/**
 * 所有的加成是基于基数100的。计算: [本身属性]*[加成]/100=需要添加的属性值
 */
enum ScienceType
{
	S_TYPE_1 	 = 1, //历练 //战斗产出的英雄经验增加
	S_TYPE_2 	 = 2, //兵种升级 //兵种等级
	S_TYPE_3 	 = 3, //点兵  //兵的排数
	S_TYPE_4 	 = 4, //统帅力 //上阵英雄数
	S_TYPE_5 	 = 5, //强壮 ////上阵英雄攻防血百分比加成？固定值加成？
	S_TYPE_6 	 = 6, //英勇 //上阵英雄战法伤害加成
	S_TYPE_7	 = 7, //坚韧 //上阵英雄受到战法伤害减少
	S_TYPE_8	 = 8, //仓库建设 //仓库容量增加
	S_TYPE_9	 = 9, //挑战 //功勋宝箱等级
	S_TYPE_10	 = 10, //建筑功勋 //解锁建筑获得功勋     id  47
	S_TYPE_11	 = 11, //贸易增产 //钞票产量提升x%  id  48
	S_TYPE_12	 = 12, //钢铁增产 //钢铁产量提升x%  id  49
	S_TYPE_13	 = 13, //石油增产 //石油产量提升x%  id  50
	S_TYPE_14	 = 14, //黄金增产 //黄金产量提升x%  id  51
	S_TYPE_15	 = 15, //每日任务
	S_TYPE_16	 = 16, //
	S_TYPE_17	 = 17, //国战任务奖励 //国战任务提升
	S_TYPE_18 	 = 18, //突破军工等级上限 //军工等级上限不受人物等级影响，直接可以升级到150级
};

class DBCScience
{
public:
	uint32_t 	uid;
	uint16_t 	id;
	int8_t	 	status; //-1未解锁 0 正常 1--注资 2--cd
	uint32_t	value;	 //status=0[加成值]status=1[表示注资阶段]status=2[表示解锁的结束时间]

	DBCScience();
	DBCScience(uint32_t uid, uint16_t id);

	bool RefreshStatus(const ScienceConfig::ScienceItem& item);
	//bool RefreshStatus(const ScienceConfig::ScienceItem& item);
	void Capital(const ScienceConfig::ScienceItem& item);
	void FinishUnlock(const ScienceConfig::ScienceItem& item);

	bool Normal() const;
	bool IsCapitaling() const; //注资中
	bool IsUnlocking() const; //解锁中
	bool IsCanCapital() const; //是否可注资

	void FullMessage(ProtoScience::ScienceItemCPP* obj) const;

};


class DBCScienceHandler : public DBCBase<DBCScience, DB_SCIENCE>
{
public:
	virtual int Get(DBCScience &data) ;
	virtual int Get(vector<DBCScience> &data) ;
	virtual int Add(DBCScience &data) ;
	virtual int Set(DBCScience &data) ;
	virtual int Del(DBCScience &data) ;
};



#endif /* DATASCIENCE_H_ */
