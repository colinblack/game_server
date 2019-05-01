/*
 * LogicTimeLimitPropMgr.h
 *
 *  Created on: 2016-11-29
 *      Author: dawx62fac
 */

#ifndef LOGICTIMELIMITPROPMGR_H_
#define LOGICTIMELIMITPROPMGR_H_

#include "ServerInc.h"

class DBCTimeLimitPropWrap
{
public:
	DBCTimeLimitPropWrap(unsigned index);
	DBCTimeLimitPropWrap(unsigned uid, unsigned id);

	void Save()
	{
		container_->m_data->MarkChange(index_);
	}

	DBCTimeLimitProp& Obj()
	{
		return data_;
	}

	const DBCTimeLimitProp& Obj() const
	{
		return data_;
	}

	int AttrType() const;
	int AttrValue() const;

	unsigned LostTime() const;
	unsigned OpTime() const;

	void Refresh();
	bool IsValid() const;

	void FullMessage(User::TimeLimtPropItem* obj) const;
private:
	unsigned _id2index(unsigned uid, unsigned id);
	unsigned _index(int index);

private:
	DataTimeLimitPropMgr*	container_;
	unsigned 				index_;
	DBCTimeLimitProp&		data_;
	const EquipmentConfig::TimeLimitProp& cfg_;
};

/////////////////////////////////////////////////////////////
class LogicTimeLimitPropMgr
	: public BattleSingleton
	, public CSingleton<LogicTimeLimitPropMgr>
{
	class _AttrItem
	{
	public:
		_AttrItem(const DBCTimeLimitPropWrap& prop)
		{
			uid = prop.Obj().uid;
			id =  prop.Obj().id;
			left_time = prop.LostTime() - Time::GetGlobalTime();
		}

		//////////////////////////////////
		unsigned uid;
		unsigned id;
		int 	 left_time;
	};

	enum AttrType
	{
		e_type1 = 1 , //钞票加成
		e_type2    	, //钢材
		e_type3		, //石油加成
		e_type4		, //黄金
		e_type5		, //维修
	};
private:
	friend class CSingleton<LogicTimeLimitPropMgr>;
	LogicTimeLimitPropMgr();
	virtual ~LogicTimeLimitPropMgr(){}

	void Notify(const DBCTimeLimitPropWrap& prop);
	void OnLost(const DBCTimeLimitPropWrap& prop);

	void RemoveUserFromAttrQueue(unsigned uid);
	void RemoveUserFromAttrQueue(unsigned uid, unsigned id);

	//失效
	void OnLoseEfficacy(const DBCTimeLimitPropWrap& prop);

	//
	//BUID_TYPES
	int AttrType2BuildType(AttrType type);
	AttrType BuildType2AttrType(int type);

	//建筑类加成
	void NotifyBuildingsStatus(const DBCTimeLimitPropWrap& prop);
	//建筑类lost
	void OnLostBuildingsProp(const DBCTimeLimitPropWrap& prop);

public:
	void CallDestroy() {Destroy();}

	void UseProp(unsigned uid, unsigned id);

	void Online(unsigned uid);
	void Offline(unsigned uid);

	int  GetBuildsIndex(unsigned uid, int type);

	unsigned  GetBuildAddFactor(unsigned uid, int type);

	void FullMessage(unsigned uid, ::google::protobuf::RepeatedPtrField< ::User::TimeLimtPropItem >* obj) const;
	//
	void OnTimer1();
private:
	typedef void (LogicTimeLimitPropMgr::*NotifyImpl)(const DBCTimeLimitPropWrap&);
	typedef void (LogicTimeLimitPropMgr::*OnLostImpl)(const DBCTimeLimitPropWrap&);

	std::map<AttrType, NotifyImpl> m_notify_table;
	std::map<AttrType, OnLostImpl> m_lost_table;
	std::deque<_AttrItem> attr_queue_;
};


#endif /* LOGICTIMELIMITPROPMGR_H_ */
