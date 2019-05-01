/*
 * LogicCashBack.h
 *
 *  Created on: 2016-11-22
 *      Author: dawx62fac
 */

#ifndef LOGICCASHBACK_H_
#define LOGICCASHBACK_H_

#include "ServerInc.h"

class DBCCashBackWrap
{
public:
	DBCCashBackWrap(unsigned uid);

	void Save()
	{
		container_->m_data->MarkChange(index_);
	}

	DBCCashBack& Obj()
	{
		return data_;
	}

	const DBCCashBack& Obj() const
	{
		return data_;
	}

	//void Accumulation(int val);
	void SetRewardFlag(int id);

	bool IsRewardFlag(int id) const;
private:
	unsigned _Index(unsigned uid);
private:
	DataCashBackMgr*  	container_;
	unsigned	  		index_;
	DBCCashBack& 		data_;
};

/////////////////////////////////////////////////////////////
class LogicCashBack
	: public ActivitySingleton<e_Activity_CashBack>
	, public CSingleton<LogicCashBack>
{
private:
	friend class CSingleton<LogicCashBack>;
	LogicCashBack(){};
	virtual ~LogicCashBack(){}
private:

public:
	void CallDestroy() {Destroy();}

	void Online(unsigned uid);
	void OnOffline(unsigned uid);

	bool IsOpen();

	//累计充值
	//void Accumulation(unsigned uid, int val);

	int Process(unsigned uid, ProtoActivity::CashBackInfoReq* req, ProtoActivity::CashBackInfoResp* resp);
	int Process(unsigned uid, ProtoActivity::CashBackRewardReq* req, ProtoActivity::CashBackRewardResp* resp);
};

#endif /* LOGICCASHBACK_H_ */
