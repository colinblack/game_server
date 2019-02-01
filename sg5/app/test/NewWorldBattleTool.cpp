/*
 * NewWorldBattleTool.cpp
 *
 *  Created on: 2015-2-12
 *      Author: Ralf
 */

#include "LogicInc.h"
#include <iostream>
#include <fstream>

#define NEW_WORLD_BATTLE_END_SERVER 499

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
	CLogicNewWorldBattle logicNewWorldBattle;
	string arg = argv[1];
	if(arg == "killrank")
	{
		ret = logicNewWorldBattle.KillRank();
	}
	else if(arg == "killreward")
	{
		ret = logicNewWorldBattle.KillRank();
		ret += logicNewWorldBattle.KillReward();
	}
	else if(arg == "hero")
	{
		CDataNewWorldBattle world;
		ret = world.PrintHero();
	}
	else if(arg == "city")
	{
		CDataNewWorldBattle world;
		ret = world.PrintCity();
	}
	else if(arg == "watch")
	{
		ret = logicNewWorldBattle.Watch();
	}
	else if(arg == "fix")
	{
		ret = logicNewWorldBattle.Fix();
	}
	else if(arg == "reset")
	{
		ret = logicNewWorldBattle.Reset();
	}
	else if(arg == "back")
	{
		ret = logicNewWorldBattle.Back();
	}
	else if(arg == "test")
	{
		if(argc < 8)
		{
			cout<<"need para!"<<endl;
			return 1;
		}
		NewWorldBattleHero attacker, defender;
		unsigned hpa, hpd;
		attacker.index.uid = atoi(argv[2]);
		attacker.index.index = atoi(argv[3]);
		hpa = atoi(argv[4]);
		defender.index.uid = atoi(argv[5]);
		defender.index.index = atoi(argv[6]);
		hpd = atoi(argv[7]);
		ret = logicNewWorldBattle.Test(attacker, hpa, defender, hpd);
		cout<<"hpa="<<attacker.hp<<"/"<<attacker.property[NewWorldBattleProperty_hp]
		<<" hpd="<<defender.hp<<"/"<<defender.property[NewWorldBattleProperty_hp]
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
		NewWorldBattleHero attacker, defender;
		unsigned times;
		attacker.index.uid = atoi(argv[2]);
		attacker.index.index = atoi(argv[3]);
		defender.index.uid = atoi(argv[4]);
		defender.index.index = atoi(argv[5]);
		ret = logicNewWorldBattle.Test(attacker, defender, times);
		cout<<"hpa="<<attacker.hp<<"/"<<attacker.property[NewWorldBattleProperty_hp]<<" hpd="<<defender.hp<<"/"<<defender.property[NewWorldBattleProperty_hp]<<" times:"<<times<<endl;
	}
	else if(arg == "time")
	{
		CDataNewWorldBattle world;
		ret = world.Time();
	}
	else if(arg == "army")
	{
		vector<unsigned> vec;
		ifstream fin("army");
		if (!fin.good()) {
			cout<<"army file error!"<<endl;
			return 1;
		}
		while (!fin.eof() && fin.good()) {
			unsigned temp;
			fin >> temp;
			vec.push_back(temp);
		}

		if(vec.size() < 9)
		{
			cout<<"army file size error:"<<vec.size()<<endl;
			return 2;
		}

		unsigned army[3];
		for(int i=0;i<3;++i)
			army[i] = vec[i*3]*10 + vec[i*3+1]*7 + vec[i*3+2]*2;

		int serverid = 0, domain = 0;
		Config::GetDB(domain);
		serverid = MainConfig::GetMergedDomain(domain);
		string host = MainConfig::GetHost(domain);

		if(domain <= NEW_WORLD_BATTLE_END_SERVER)
		{
			CLogicAllServerNewWorldBattle logicAllServerNewWorldBattle;
			ret = logicAllServerNewWorldBattle.SetArmy(serverid, domain, army, host);
		}
	}
	else if(arg == "restart")
	{
		ret = logicNewWorldBattle.Restart();
		system("killall -12 CgiNewWorldBattle");
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




