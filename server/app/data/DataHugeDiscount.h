/*
 * DataHugeDiscount.h
 *
 *  Created on: 2016-12-19
 *      Author: dawx62fac
 */

#ifndef DATAHUGEDISCOUNT_H_
#define DATAHUGEDISCOUNT_H_

#include "Kernel.h"
#include "DBCMultipleTemplate.h"

class DBCHugeDiscount
{
	enum {
		MAX_ID = 6,
	};
private:
	uint16_t* ItemCnt(unsigned id);
public:
	DBCHugeDiscount();
	DBCHugeDiscount(unsigned uid, unsigned id);

	void 		Reset(unsigned version);
	uint16_t 	GetBuyCnt(unsigned id);
	void 		OP(unsigned id);

	int 		StartId() const { return 1; }
	int 		EndId() const { return MAX_ID; }
public:
	uint32_t uid;
	uint32_t id;
	uint32_t version; //活动版本
	uint32_t op_time; //
	uint16_t item_1_cnt; //购买次数
	uint16_t item_2_cnt;
	uint16_t item_3_cnt;
	uint16_t item_4_cnt;
	uint16_t item_5_cnt;
	uint16_t item_6_cnt;
};

class DBCHugeDiscountHandler : public DBCBase<DBCHugeDiscount, DB_HUGE_DISCOUNT>
{
public:
	virtual int Get(DBCHugeDiscount &data);
	virtual int Get(std::vector<DBCHugeDiscount> &data);
	virtual int Add(DBCHugeDiscount &data);
	virtual int Set(DBCHugeDiscount &data);
	virtual int Del(DBCHugeDiscount &data);
};

class DataHugeDiscountMgr
	: public DBCMultipleTemplate<DBCHugeDiscount, DB_HUGE_DISCOUNT, DB_HUGE_DISCOUNT_FACTOR, DBCHugeDiscountHandler>
	, public CSingleton<DataHugeDiscountMgr>
{
public:
	 virtual void CallDestroy() { Destroy();}

	 const char* name() const  { return "DBCHugeDiscount"; }
};

#endif /* DATAHUGEDISCOUNT_H_ */
