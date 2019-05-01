/*
 * DataTouchGoldActivity.h
 *
 *  Created on: 2016-12-9
 *      Author: dawx62fac
 */

#ifndef DATATOUCHGOLDACTIVITY_H_
#define DATATOUCHGOLDACTIVITY_H_

#include "Kernel.h"
#include "DBCSimpleTemplate.h"

/**
 * 摸金校尉活动
 */

class DBCTouchGold
{
	enum {
		TOMB_CNT = 5, //古墓的个数
		TOUCH_CNT = 5, //摸金次数
		TOUCH_POS_CNT = 9,
	};
public:
	DBCTouchGold();

	void ResetVersion(unsigned version);

	void ResetTomb(unsigned id);

	void UnlockTomb(int id);
	bool IsUnlocked(int id) const;

	uint8_t MaxId() const { return TOMB_CNT ;}
	uint8_t	MaxTouchPosition() const { return TOUCH_POS_CNT - 1; }
	uint8_t MaxTouches() const { return TOUCH_CNT; }

	void TouchGold(int index, uint16_t gold);
	bool IsTouched(int index) const;

	void CheckIdParams(int id) const;

	uint16_t  GetOutput(int index) const;
	uint16_t* Output(int index);

	uint16_t GetTouches() const;
public:
	uint32_t uid;
	uint32_t version;
	uint16_t total_touchs;    //总的摸金次数
	int8_t	 tomb_id;		  //当前古墓id
	uint8_t	 tomb_unlock_bit; //古墓解锁状态
	uint16_t touch_bit;		  //摸金状态记录
	uint8_t	 surpluses;		  //单回合剩余几次
	uint16_t output_1_cnt;	  //第一次产出数量
	uint16_t output_2_cnt;
	uint16_t output_3_cnt;
	uint16_t output_4_cnt;
	uint16_t output_5_cnt;
	uint32_t ts_op;				//操作时间戳
};

class DBCTouchGoldHandler : public DBCBase<DBCTouchGold, DB_TOUCH_GOLD>
{
public:
	virtual int Get(DBCTouchGold &data);
	virtual int Get(vector<DBCTouchGold> &data);
	virtual int Add(DBCTouchGold &data);
	virtual int Set(DBCTouchGold &data);
	virtual int Del(DBCTouchGold &data);
};

class DataTouchGoldMgr
	 : public DBCSimpleTemplate<DBCTouchGold, DB_TOUCH_GOLD, DBCTouchGoldHandler>
	 , public CSingleton<DataTouchGoldMgr>
{
public:
	 virtual void CallDestroy() { Destroy();}

	 const char* name() const  { return "DBCTouchGold"; }
};


#endif /* DATATOUCHGOLDACTIVITY_H_ */
