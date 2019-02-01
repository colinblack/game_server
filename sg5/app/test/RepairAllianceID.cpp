/*
 * RepairAllianceID.cpp
 *
 *  Created on: 2014-7-16
 *      Author: Ralf
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

	CLogicKingdom logicKingdom;
	int ret = logicKingdom.RepairAllianceID();
	cout<<"ret="<<ret<<endl;

	CLogicAllianceBattle logicAllianceBattle;
	ret = logicAllianceBattle.RepairAllianceID();
	cout<<"ret="<<ret<<endl;

	return 0;
}


