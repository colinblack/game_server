/*
 * DataLimitShop.h
 *
 *  Created on: 2016-11-1
 *      Author: dawx62fac
 */

#ifndef DATALIMITSHOP_H_
#define DATALIMITSHOP_H_

#include "Kernel.h"

class DBCLimitShop
{
	enum {
		MAX_ID = 6,
	};
private:
	//unsigned MaxId() const { return MAX_ID; }
	uint16_t* ItemCnt(unsigned id);
public:
	DBCLimitShop();

	void Reset(unsigned version);
	uint16_t GetBuyCnt(unsigned id);
	void OP(unsigned id);
public:
	uint32_t uid;
	uint32_t version; //活动版本
	uint32_t op_time; //最后一次购买时间
	uint16_t item_1_cnt; //购买次数
	uint16_t item_2_cnt;
	uint16_t item_3_cnt;
	uint16_t item_4_cnt;
	uint16_t item_5_cnt;
	uint16_t item_6_cnt;
};

class DBCLimitShopHandler : public DBCBase<DBCLimitShop, DB_LIMIT_SHOP>
{
public:
	virtual int Get(DBCLimitShop &data);
	virtual int Get(vector<DBCLimitShop> &data);
	virtual int Add(DBCLimitShop &data);
	virtual int Set(DBCLimitShop &data);
	virtual int Del(DBCLimitShop &data);
};

class DataLimitShopMgr
	 :	public DataSingleton<DBCLimitShop, DB_LIMIT_SHOP, DB_BASE_BUFF*DB_BASE_FULL, DBCLimitShopHandler, DB_BASE_FULL>
	 ,  public CSingleton<DataLimitShopMgr>
{
	typedef DataSingleton<DBCLimitShop, DB_LIMIT_SHOP, DB_BASE_BUFF*DB_BASE_FULL, DBCLimitShopHandler, DB_BASE_FULL> base;
private:
	int FreeIndex();

	void NewItem(unsigned uid, int index);

	int LoadBuffer(unsigned uid);
public:
	int OnInit();

	virtual void CallDestroy() { Destroy();}

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	void Online(unsigned uid);

	int GetIndex(unsigned uid);
private:
	std::map<unsigned, unsigned> m_map;
};


#endif /* DATALIMITSHOP_H_ */
