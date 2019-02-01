/*
 * NewWorldTool.cpp
 *
 *  Created on: 2014-9-17
 *      Author: dawx123
 */


#include "LogicInc.h"
#include <iostream>
#include <fstream>


int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		cout<<"need para!"<<endl;
		return 1;
	}

	if (!Kernel::Init(APP_CONFIG_PATH))
	{
		cout << "init fail" << endl;
		return 0;
	}
	Config::SetDomain(0);

	int ret = 0;
	CLogicNewWorld logicNewWorld;
	string arg = argv[1];
	if(arg == "worldreward")
	{
		ret = logicNewWorld.WorldReward();
		logicNewWorld.KillRank();
	}
	else if(arg == "cityreward")
	{
		ret = logicNewWorld.CityReward();
	}
	else if(arg == "startmission")
	{
		ret = logicNewWorld.StartMission();
	}
	else if(arg == "endmission")
	{
		ret = logicNewWorld.EndMission();
	}
	else if(arg == "killreward")
	{
		ret = logicNewWorld.KillReward();
	}
	else if(arg == "hero")
	{
		CDataNewWorld world;
		ret = world.PrintHero();
	}
	else if(arg == "city")
	{
		CDataNewWorld world;
		ret = world.PrintCity();
	}
	else if(arg == "watch")
	{
		ret = logicNewWorld.Watch();
	}
	else if(arg == "fix")
	{
		ret = logicNewWorld.Fix();
	}
	else if(arg == "reset")
	{
		ret = logicNewWorld.Reset();
	}
	else if(arg == "back")
	{
		ret = logicNewWorld.Back();
	}
	else if(arg == "test")
	{
		if(argc < 8)
		{
			cout<<"need para!"<<endl;
			return 1;
		}
		NewWorldHero attacker, defender;
		unsigned hpa, hpd;
		attacker.index.uid = atoi(argv[2]);
		attacker.index.index = atoi(argv[3]);
		hpa = atoi(argv[4]);
		defender.index.uid = atoi(argv[5]);
		defender.index.index = atoi(argv[6]);
		hpd = atoi(argv[7]);
		ret = logicNewWorld.Test(attacker, hpa, defender, hpd);
		cout<<"hpa="<<attacker.hp<<"/"<<attacker.property[NewWorldProperty_hp]
		<<" hpd="<<defender.hp<<"/"<<defender.property[NewWorldProperty_hp]
		<<" ak="<<attacker.kill<<" dk="<<defender.kill
		<<endl;
	}
	else if(arg == "testtime")
	{
		if(argc < 6)
		{
			cout<<"need para!"<<endl;
			return 1;
		}
		NewWorldHero attacker, defender;
		unsigned times;
		attacker.index.uid = atoi(argv[2]);
		attacker.index.index = atoi(argv[3]);
		defender.index.uid = atoi(argv[4]);
		defender.index.index = atoi(argv[5]);
		ret = logicNewWorld.Test(attacker, defender, times);
		cout<<"hpa="<<attacker.hp<<"/"<<attacker.property[NewWorldProperty_hp]<<" hpd="<<defender.hp<<"/"<<defender.property[NewWorldProperty_hp]<<" times:"<<times<<endl;
	}
	else if(arg == "time")
	{
		CDataNewWorld world;
		ret = world.Time();
	}
	else if(arg == "change")
	{
		CDataNewWorld world;
		ret = world.change();
	}
	else if(arg == "fixold")
	{
		ret = logicNewWorld.FixOld();
	}
	else
	{
		cout<<"wrong para!"<<endl;
		return 1;
	}

	if(ret)
		cout<<arg<<" fail, ret="<<ret<<endl;
	else
		cout<<arg<<" ok"<<endl;

	return 0;
}


