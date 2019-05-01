/*
 * LogicPassActivityMgr.h
 *
 *  Created on: 2016-11-23
 *      Author: dawx62fac
 */

#ifndef LOGICPASSACTIVITYMGR_H_
#define LOGICPASSACTIVITYMGR_H_

/**
 * //闯关送钻
 */
#include "ServerInc.h"

class PassActivityRecord
{
public:
	PassActivityRecord(const std::string& name, unsigned pass_id, int cash)
		: name_(name)
		, pass_id_(pass_id)
		, cash_(cash)
	{

	}

	const std::string& Name() const { return name_; }
	const unsigned PassId() const { return pass_id_; }
	const unsigned Cash() const { return cash_; }
private:
	std::string name_;
	unsigned 	pass_id_;
	unsigned 	cash_;
};

class  LogicPassActivityMgr
		: public BattleSingleton
		, public CSingleton<LogicPassActivityMgr>
{
private:
	friend class CSingleton<LogicPassActivityMgr>;
	LogicPassActivityMgr();

	bool IsValidPeroid(const DBCUserBaseWrap& user);
public:
	virtual void CallDestroy() { Destroy();}

	//
	void AddRecord(const PassActivityRecord& record);

	int Process(unsigned uid, ProtoActivity::PassActivityInfoReq* req, ProtoActivity::PassActivityInfoResp* resp);
	int Process(unsigned uid, ProtoActivity::PassActivityRewardReq* req, ProtoActivity::PassActivityRewardResp* resp);
private:
	std::deque<PassActivityRecord> record_;
};

#endif /* LOGICPASSACTIVITYMGR_H_ */
