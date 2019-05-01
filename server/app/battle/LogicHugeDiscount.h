/*
 * LogicHugeDiscount.h
 *
 *  Created on: 2016-12-19
 *      Author: dawx62fac
 */

#ifndef LOGICHUGEDISCOUNT_H_
#define LOGICHUGEDISCOUNT_H_

#include "ServerInc.h"

class DBCHugeDiscountWrap
{
public:
	DBCHugeDiscountWrap(unsigned uid, unsigned id);
	DBCHugeDiscountWrap(unsigned index);

	void Save()
	{
		container_->m_data->MarkChange(index_);
	}

	DBCHugeDiscount& Obj()
	{
		return data_;
	}

	const DBCHugeDiscount& Obj() const
	{
		return data_;
	}

	unsigned TotalRecharge() const;

	bool IsActive() const;

	void DoBuy(unsigned id);

	void FullMessage(unsigned id, ProtoActivity::HugeDiscountItem* obj) const;
	void FullMessage(ProtoActivity::HugeDiscountPage* obj) const;
private:
	unsigned _index(unsigned index) const;
	unsigned _id2index(unsigned uid, unsigned id);

	void _init();
private:
	DataHugeDiscountMgr*  	container_;
	unsigned	  			index_;
	DBCHugeDiscount& 		data_;
};


class LogicHugeDiscount
	: public ActivitySingleton<e_Activity_HugeDiscound>
	, public CSingleton<LogicHugeDiscount>
{
private:
	friend class CSingleton<LogicHugeDiscount>;
	LogicHugeDiscount(){};
	virtual ~LogicHugeDiscount(){}
private:


public:
	void CallDestroy() {Destroy();}

	void Online(unsigned uid);

	//信息
	int Process(unsigned uid, ProtoActivity::HugeDiscountInfoReq* req, ProtoActivity::HugeDiscountInfoResp* resp);
	//购买
	int Process(unsigned uid, ProtoActivity::HugeDiscountBuyReq* req, ProtoActivity::HugeDiscountBuyResp* resp);
};


#endif /* LOGICHUGEDISCOUNT_H_ */
