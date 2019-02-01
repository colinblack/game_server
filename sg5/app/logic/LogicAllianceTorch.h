/*
 * LogicAllianceTorch.h
 *
 *  Created on: 2016-05-18
 *      Author: zkw
 */

#ifndef LOGICALLIANCETORCH_H_
#define LOGICALLIANCETORCH_H_


#include "LogicInc.h"
#include "LogicBase.h"

class CLogicAllianceTorch : public LogicBase<CDataAllianceTorch>
{
public:
	CLogicAllianceTorch(){}
	~CLogicAllianceTorch(){}
	int checkLastSaveUID(DataUser &user);
	int checkLastSaveTime(DataUser &user,unsigned lasttime,unsigned seqid);
	int GetAllianceTorchCurrStatus(unsigned aid, Json::Value &result);
	int BurnAllianceTorch(unsigned aid, unsigned uid, unsigned torch_type, Json::Value &result, unsigned lasttime, unsigned seqid);
	int GetAllianceTorchBuyLog(unsigned aid, Json::Value &result);
};


#endif /* LOGICALLIANCETORCH_H_ */
