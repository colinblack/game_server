/*
 * BarbarianKingReward.cpp
 *
 *  Created on: 2014-4-3
 *      Author: dawx123
 */
#include "LogicInc.h"

int main(int argc, char* argv[])
{
	if (!Kernel::Init(APP_CONFIG_PATH))
	{
		cout << "init kernel fail" << endl;
		return 1;
	}
	Config::SetDomain(0);

	CLogicBarbarianKing logicBarbarianKing;
	int ret = logicBarbarianKing.Reward();
	cout<<"ret="<<ret<<endl;

	return 0;
}
