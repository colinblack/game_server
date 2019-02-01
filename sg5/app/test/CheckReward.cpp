/*
 * CheckReward.cpp
 *
 *  Created on: 2016-1-13
 *      Author: Ralf
 */

#include "LogicInc.h"
#include <iostream>

int main(int argc, char *argv[])
{
	if (!Kernel::Init(APP_CONFIG_PATH))
	{
		cout << "init kernel fail" << endl;
		return 1;
	}
	Config::SetDomain(0);

	CLogicTopTenUser logicTopTenUser;
	logicTopTenUser.CheckTime(0, HERO_POWER_RANK);
	logicTopTenUser.CheckTime(0, USER_LOOT_RANK);

	CLogicPointsRank logicPointsRank;
	logicPointsRank.RewardPointRank();

	return 0;
}
