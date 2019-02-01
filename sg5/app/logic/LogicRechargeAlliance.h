/*
 *LogicRechargeAlliance.h
 *
 *  Created on: 2013-12-18
 *      Author: Administrator
 */

#ifndef LOGIC_RECHARGE_ALLIANCE_H_
#define LOGIC_RECHARGE_ALLIANCE_H_
#include "LogicInc.h"
class CLogicRechargeAlliance {
	struct UpdateAllianceMember
	{
		unsigned allianceid;
		AllianceMember &recharge;
	};
public:
	CLogicRechargeAlliance();
	virtual ~CLogicRechargeAlliance();
	static CDataRechargeAlliance* GetRechargeAlliancePdata(unsigned allianceid);
	int GetRechargeAllianceData(unsigned uid,Json::Value &result);
	int UpdateRechargeAllianceData(AllianceMember &recharge);
	int UpdateRechargeAllianceData(unsigned allianceid, AllianceMember &recharge);
	int ReceiveRechargeAllianceData(Json::Value data);
	int ReplyRechargeAllianceData(const Json::Value para,Json::Value &result);
private:
	int _reportRechargeAllianceData(unsigned allianceid, AllianceMember &recharge);
	int _getRechargeAllianceData(unsigned allianceid,Json::Value &result);

};
#endif /* LOGIC_RECHARGE_ALLIANCE_H_ */
