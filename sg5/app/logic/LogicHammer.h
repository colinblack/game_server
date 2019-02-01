/*
 * LogicHammer.h
 *
 *  Created on: 2014年10月10日
 *      Author: Administrator
 */

#ifndef LOGICHAMMER_H_
#define LOGICHAMMER_H_
#include "LogicInc.h"

struct HammerHit{
	int nextHammer;
	vector<uint32_t> items;
	int hammerCost;
	HammerHit(){
		nextHammer = 1;
		hammerCost = 0;
	}
};

class LogicHammer {

public:
	int hitJar(uint32_t uid, int curHammerId, unsigned hammerud, Json::Value &result, bool isOneHit, bool isAllServer = false);

	int StageReward(uint32_t uid, unsigned point, const Json::Value& stage_flag, Json::Value& result);
private:
	int hit(uint32_t uid, int curHammerId, HammerHit &hitRlt, bool isOneHit = true, bool isAllServer = false);
	int oneHit(int curHammerId, const Hammer &hammer, HammerHit &hitRlt);
	int nextHammer(int hammerId);
	int costHammer(int hammerId);
};

#endif /* LOGICHAMMER_H_ */
