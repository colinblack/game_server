/*
 * LogicSmeltActivity.h
 *
 *  Created on: 2016-12-5
 *      Author: dawx62fac
 */

#ifndef LOGICSMELTACTIVITY_H_
#define LOGICSMELTACTIVITY_H_


#include "ServerInc.h"

class DBCSmeltActivityWrap
{
public:
	DBCSmeltActivityWrap(unsigned uid);

	void Save()
	{
		container_->m_data->MarkChange(index_);
	}

	DBCSmeltActivity& Obj()
	{
		return data_;
	}

	const DBCSmeltActivity& Obj() const
	{
		return data_;
	}

	//洗练累计
	void AccumulateSmeltCnt(int cnt);
	//
	unsigned GetTotalRewardCnt(int id) const;
	//可领取次数
	unsigned GetAvailableRewardCnt(int id) const;
	//已经领取次数
	unsigned GetAlreadyRewardCnt(int id) const;
	//累计奖励次数
	void AccumulateRewardCnt(int id, int cnt);

	void FullMessage(::google::protobuf::RepeatedPtrField< ::ProtoActivity::SmeltItem >* obj) const;
	void FullMessage(unsigned id, ::ProtoActivity::SmeltItem* obj) const;
private:
	unsigned _Index(unsigned uid) const;
private:
	DataSmeltActivityMgr*  	container_;
	unsigned	  			index_;
	DBCSmeltActivity& 		data_;
};

/////////////////////////////////////////////////////////////
class LogicSmeltActivity
	: public ActivitySingleton<e_Activity_Smelt>
	, public CSingleton<LogicSmeltActivity>
{
private:
	friend class CSingleton<LogicSmeltActivity>;
	LogicSmeltActivity(){};
	virtual ~LogicSmeltActivity(){}
private:

public:
	void CallDestroy() {Destroy();}

	void Online(unsigned uid);
	//void Offline(unsigned uid);

	void AccumulateSmeltCnt(unsigned uid, int cnt);

	int Process(unsigned uid, ProtoActivity::SmeltInfoReq* req, ProtoActivity::SmeltInfoResp* resp);
	int Process(unsigned uid, ProtoActivity::SmeltRewardReq* req, ProtoActivity::SmeltRewardResp* resp);
};


#endif /* LOGICSMELTACTIVITY_H_ */
