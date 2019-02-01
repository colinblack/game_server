/*
 * SetAllianceTech.cpp
 *
 *  Created on: 2014-8-22
 *      Author: Ralf
 */

#include "LogicInc.h"

int main(int argc, char *argv[])
{
	if (argc < 4)
	{
		cout << "usage: SetAllianceTech aid index lvl " << endl;
		return 1;
	}
	if (!Kernel::Init(APP_CONFIG_PATH))
	{
		cout << "init fail" << endl;
		return 1;
	}
	Config::SetDomain(0);

	int ret;
	unsigned aid 	= atol(argv[1]);
	unsigned index 	= atoi(argv[2]);
	unsigned lvl 	= atoi(argv[3]);

	CLogicAlliance logicAlliance;
	ret = logicAlliance.SetAllianceTech(aid,index,lvl);

	if (ret != 0)
	{
		cout << "fail " << endl;
		return ret;
	}
	cout <<" ok" << endl;
	return 0;
}


