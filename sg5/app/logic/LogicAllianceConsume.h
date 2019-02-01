/*
 * LogicAllianceConsume.h
 *
 *  Created on: 2017-3-15
 *      Author: Ralf
 */

#ifndef LOGICALLIANCECONSUME_H_
#define LOGICALLIANCECONSUME_H_


#include "LogicInc.h"
#include "LogicBase.h"

class CLogicAllianceConsume : public LogicBase<CDataAllianceConsume>
{
public:
	CLogicAllianceConsume(){}
	~CLogicAllianceConsume(){}

	int AllianceShopInfo(unsigned aid, Json::Value &result);
	int AllianceShopBuy(unsigned uid, unsigned aid, unsigned index, unsigned count, Json::Value &result);
	int AllianceShopLimit(unsigned uid, unsigned aid, unsigned type, unsigned index, unsigned count, Json::Value &result);
	int AllianceShopGift(unsigned uid, unsigned aid, unsigned index, Json::Value &result);
};



#endif /* LOGICALLIANCECONSUME_H_ */
