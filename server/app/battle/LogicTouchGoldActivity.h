/*
 * LogicTouchGoldActivity.h
 *
 *  Created on: 2016-12-9
 *      Author: dawx62fac
 */

#ifndef LOGICTOUCHGOLDACTIVITY_H_
#define LOGICTOUCHGOLDACTIVITY_H_

#include "ServerInc.h"

class DBCTouchGoldWrap
{
	enum {
		TOUCH_TOTAL_MAX_CNT = 100, //摸金总次数
	};
public:
	DBCTouchGoldWrap(unsigned uid);

	void Save()
	{
		container_->m_data->MarkChange(index_);
	}

	DBCTouchGold& Obj()
	{
		return data_;
	}

	const DBCTouchGold& Obj() const
	{
		return data_;
	}

	void OpenTomb(int id);
	void OpenNextTomb(int cur_id);
	bool IsTombOpened(int id) const;

	void SwitchTomb(int id);


	unsigned TouchGold(int index);
	//一键摸金
	unsigned TouchGold();

	void Reset();

	void FullMessage(const DataBase& base, ProtoActivity::TouchGoldInfo* obj);
private:
	unsigned _Index(unsigned uid);

	void CheckTombId(int id) const;

	bool IsOpenNextTomb(int id) const;
private:
	DataTouchGoldMgr*  	container_;
	unsigned	  		index_;
	DBCTouchGold& 		data_;
};

/////////////////////////////////////////////////////////////
class LogicTouchGold
	: public ActivitySingleton<e_Activity_TouchGold>
	, public CSingleton<LogicTouchGold>
{
	enum
	{
		TOUCH_FREE_CNT = 3, //免费摸金次数
	};
private:
	friend class CSingleton<LogicTouchGold>;
	LogicTouchGold(){};
	virtual ~LogicTouchGold(){}
private:

public:
	void CallDestroy() {Destroy();}

	void Online(unsigned uid);
	//获取摸金的相关信息
	int Process(unsigned uid, ProtoActivity::TouchGoldInfoReq* req, ProtoActivity::TouchGoldInfo* resp);
	//单词摸金
	int Process(unsigned uid, ProtoActivity::TouchGoldOnceReq* req, ProtoActivity::TouchGoldResp* resp);
	//一键摸金
	int Process(unsigned uid, ProtoActivity::TouchGoldAllReq* req, ProtoActivity::TouchGoldResp* resp);
	//重置
	int Process(unsigned uid, ProtoActivity::TouchGoldResetReq* req, ProtoActivity::TouchGoldInfo* resp);
	//切换古墓
	int Process(unsigned uid, ProtoActivity::TouchGoldSwitchReq* req, ProtoActivity::TouchGoldInfo* resp);
	//解锁古墓
	int Process(unsigned uid, ProtoActivity::TouchGoldUnlockReq* req, ProtoActivity::TouchGoldResp* resp);
};

#endif /* LOGICTOUCHGOLDACTIVITY_H_ */
