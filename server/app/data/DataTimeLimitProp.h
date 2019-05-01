/*
 * DataTimeLimitProp.h
 *
 *  Created on: 2016-11-29
 *      Author: dawx62fac
 */

#ifndef DATATIMELIMITPROP_H_
#define DATATIMELIMITPROP_H_

#include "Kernel.h"
#include "DBCMultipleTemplate.h"

class DBCTimeLimitProp
{
public:
	DBCTimeLimitProp(unsigned uid, unsigned id);
	DBCTimeLimitProp();
public:
	uint32_t uid;
	uint32_t id;   		//道具id
	uint32_t op_time; 	//使用时间
};

class DBCTimeLimitPropHandler : public DBCBase<DBCTimeLimitProp, DB_TIME_LIMIT_PROP>
{
public:
	virtual int Get(DBCTimeLimitProp &data) ;
	virtual int Get(vector<DBCTimeLimitProp> &data) ;
	virtual int Add(DBCTimeLimitProp &data) ;
	virtual int Set(DBCTimeLimitProp &data) ;
	virtual int Del(DBCTimeLimitProp &data) ;
};


class DataTimeLimitPropMgr
	: public DBCMultipleTemplate<DBCTimeLimitProp, DB_TIME_LIMIT_PROP, DB_TIME_LIMIT_PROP_FACTOR, DBCTimeLimitPropHandler>
	, public CSingleton<DataTimeLimitPropMgr>
{
public:
	 virtual void CallDestroy() { Destroy();}

	 const char* name() const  { return "DBCTimeLimitProp"; }
};


#endif /* DATATIMELIMITPROP_H_ */
