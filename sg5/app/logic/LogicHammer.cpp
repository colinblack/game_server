/*
 * LogicHammer.cpp
 *
 *  Created on: 2014年10月10日
 *      Author: Administrator
 */

#include "LogicHammer.h"

int LogicHammer::hitJar(uint32_t uid, int curHammerId, unsigned hammerud, Json::Value &result, bool isOneHit, bool isAllServer) {
	++curHammerId;
	HammerHit hitRlt;
	int ret = hit(uid, curHammerId, hitRlt, isOneHit, isAllServer);
	if (ret != 0) {
		error_log("[Hammer] hit fail uid=%u", uid);
		return ret;
	}

	// 扣锤子
	uint32_t cuiziId = 5201;
	CLogicEquipment equipment;
	ret = equipment.UseEquipment(uid, cuiziId,hammerud,hitRlt.hammerCost, "activity_hammer_cost");
	if (ret != 0) {
		error_log("[Hammer]deduct hammer fail uid=%u, count=%d", uid, hitRlt.hammerCost);
		return ret;
	}
	result["hammerCost"] = hitRlt.hammerCost;
	result["hlv"]  = hitRlt.nextHammer - 1;

	// 发奖励
	vector<ItemAdd> items;
	for(size_t i = 0; i < hitRlt.items.size(); ++i) {
		ItemAdd item;
		item.eqid = hitRlt.items[i];
		item.count = 1;
		item.reason = "activity_hammer";
		items.push_back(item);
	}
	equipment.AddItems(uid, items,result["items"], true);

	return R_SUCCESS;
}

int LogicHammer::StageReward(uint32_t uid, unsigned point, const Json::Value& stage_flag, Json::Value& result)
{
	enum {
		STAGE_CNT = 4,
	};

	result["hrb"] = stage_flag;

	const unsigned PointTB[STAGE_CNT] = {998, 5888, 28888, 48888};
	const char* EquipTB[STAGE_CNT] = {"4425", "H3109", "44077", "44038"};
	int ret = 0;

	for (int i = 0; i < STAGE_CNT; i++)
	{
		if (point < PointTB[i])
		{
			break;
		}

		if (stage_flag[i].asInt() > 0)
		{
			continue;
		}

		result["hrb"][i] = 1;
		std::string op = "activity_hammer_stage_reward_op";
		if ('H' == EquipTB[i][0])
		{
			ret = CLogicHero().AddOneHero(uid, EquipTB[i], op, result["hero"]);
			if (ret)
			{
				return ret;
			}
		}
		else
		{
			unsigned eqid = CTrans::STOI(EquipTB[i]);
			ret = CLogicEquipment().AddOneItem(uid, eqid, 1, op, result["equip"], true);
			if (ret)
			{
				return ret;
			}
		}
	}

	return ret;
}


// oneHit: true-砸一次, false-连砸
int LogicHammer::hit(uint32_t uid, int curHammerId, HammerHit &hitRlt, bool isOneHit, bool isAllServer) {
	if(curHammerId<1 || curHammerId > 4) {
		return R_ERR_PARAM;
	}

	static bool initData = false;
	static bool initDataAllServer = false;
	static map<uint32_t, Hammer> mapHammer;
	static map<uint32_t, Hammer> mapHammerAllServer;
	int ret = 0;

	if (isAllServer)
	{
		if (!initDataAllServer) {
			CDataXML *pDataXML = CDataXML::GetCDataXML();
			if(!pDataXML)
			{
				error_log("[hit] GetCDataXML fail");
				return R_ERR_DATA;
			}

			ret = pDataXML->GetHammerAllServer(mapHammerAllServer);
			if (ret != 0) {
				error_log("[hit] GetHammerData fail");
				return ret;
			}
			initDataAllServer = true;
		}

		if (isOneHit) {   // 砸一次
			Hammer &hammer = mapHammerAllServer[curHammerId];
			ret = oneHit(curHammerId, hammer, hitRlt);
			if (ret != 0) {
				error_log("[hit] hit fail uid=%u",uid);
				return ret;
			}
		}
		else {  // 连砸100锤
			int hammer_left = 100;
			while (hammer_left >= costHammer(curHammerId)) {
				Hammer &hammer = mapHammerAllServer[curHammerId];
				ret = oneHit(curHammerId, hammer, hitRlt);
				if (ret != 0) {
					error_log("[hit] hit fail uid=%u",uid);
					return ret;
				}
				hammer_left -= costHammer(curHammerId);
				curHammerId = hitRlt.nextHammer;
			}
		}
	}//isAllServer==true
	else
	{
		if (!initData) {
			CDataXML *pDataXML = CDataXML::GetCDataXML();
			if(!pDataXML)
			{
				error_log("[hit] GetCDataXML fail");
				return R_ERR_DATA;
			}

			ret = pDataXML->GetHammer(mapHammer);
			if (ret != 0) {
				error_log("[hit] GetHammerData fail");
				return ret;
			}
			initData = true;
		}

		if (isOneHit) {   // 砸一次
			Hammer &hammer = mapHammer[curHammerId];
			ret = oneHit(curHammerId, hammer, hitRlt);
			if (ret != 0) {
				error_log("[hit] hit fail uid=%u",uid);
				return ret;
			}
		}
		else {  // 连砸100锤
			int hammer_left = 100;
			while (hammer_left >= costHammer(curHammerId)) {
				Hammer &hammer = mapHammer[curHammerId];
				ret = oneHit(curHammerId, hammer, hitRlt);
				if (ret != 0) {
					error_log("[hit] hit fail uid=%u",uid);
					return ret;
				}
				hammer_left -= costHammer(curHammerId);
				curHammerId = hitRlt.nextHammer;
			}
		}
	}

	return R_SUCCESS;
}

int LogicHammer::oneHit(int curHammerId, const Hammer &hammer, HammerHit &hitRlt){
	int total_rate = hammer.total_rate;
	int rd = rand() % total_rate;
	int sum = 0;
	bool isHit = false;
	for (size_t i = 0; i < hammer.items.size(); ++i) {
		sum += hammer.items[i].rate;
		if(rd < sum) {
			hitRlt.items.push_back(hammer.items[i].id);
			hitRlt.nextHammer = nextHammer(curHammerId);
			hitRlt.hammerCost += costHammer(curHammerId);
			isHit = true;
			break;
		}
	}
	if (!isHit) {
		error_log("[can't hit][curHammerId=%d&rd=&d&total_rate=%d&sum=%d]",curHammerId,rd,total_rate,sum);
		return R_ERR_LOGIC;
	}
	return R_SUCCESS;
}

int LogicHammer::nextHammer(int hammerId) {
	const static int fist = 1;
	int nextHammer = hammerId;
	switch (hammerId) {
	case 1:
		if (rand() % 100 < 20)
			++nextHammer;
		break;
	case 2:
		if (rand() % 100 < 30)
			++nextHammer;
		break;
	case 3:
		if (rand() % 100 < 40)
			++nextHammer;
		break;
	default:
		nextHammer = fist;
		break;
	}
	return nextHammer;
}

int LogicHammer::costHammer(int hammerId) {
	int cost;
	switch(hammerId) {
	case 1: cost = 1; break;
	case 2: cost = 3; break;
	case 3: cost = 5; break;
	case 4: cost = 10;break;
	default: cost = 1;break;
	}
	return cost;
}
