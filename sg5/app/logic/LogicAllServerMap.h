/*
 * LogicAllServerMap.h
 *
 *  Created on: 2015-9-15
 *      Author: Ralf
 */

#ifndef LOGICALLSERVERMAP_H_
#define LOGICALLSERVERMAP_H_

#include "LogicInc.h"
#include "LogicBase.h"


class CLogicAllServerMap : public LogicBase<CDataAllServerMap>
{
public:
	CLogicAllServerMap(){}
	~CLogicAllServerMap(){}
	int Get(unsigned level, unsigned count, vector<unsigned> &res);
	int ReplyGet(unsigned level, unsigned count, Json::Value &result);
	int Set(unsigned uid, unsigned level);
	int Syn();
	int ReplySyn(Json::Value &data);
};


#endif /* LOGICALLSERVERMAP_H_ */
