#include "LogicInc.h"

void usage()
{
	cout << "usage: AllianceBattleTool 	defence " << endl
		 << "                			attack " << endl
		 << "                 			occupy " << endl
		 << "                 			restart " << endl
		 << "                 			pay " << endl
		 << "                 			city " << endl
		 << "                 			battle cityid " << endl;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		usage();
		return 1;
	}
	if (!Kernel::Init(APP_CONFIG_PATH))
	{
		cout << "init fail" << endl;
		return 1;
	}
	Config::SetDomain(0);

	string action = argv[1];
	int ret = 0;
	CLogicAllianceBattle logicAllianceBattle;
	CLogicKingdom logicKingdom;
	if (action == "defence")
		ret = logicAllianceBattle.StartDefence();
	else if(action == "attack")
		ret = logicAllianceBattle.StartAttack();
	else if (action == "occupy")
		ret = logicAllianceBattle.StartOccupy();
	else if (action == "restart")
		ret = logicAllianceBattle.RewardAndRestart()
			+ logicAllianceBattle.ProcessKingdom()
			+ logicKingdom.RewardKingdom();
	else if (action == "pay")
	{
		Json::Value data;
		Json::FastWriter writer;
		ret = logicAllianceBattle.GetAllCityPrice(data);
		cout<< writer.write(data)<<endl;
	}
	else if (action == "city")
	{
		Json::Value data;
		Json::FastWriter writer;
		ret = logicAllianceBattle.GetAllCityLimit(data);
		cout<< writer.write(data)<<endl;
	}
	else if (action == "battle")
	{
		if (argc > 2)
		{
			unsigned bid =  atoi(argv[2]);
			Json::Value data;
			Json::FastWriter writer;
			ret = logicAllianceBattle.GetAllBattlePointLimit(bid/100%100,data);
			cout<< writer.write(data)<<endl;
			CDataAllianceBattle* dataAllianceBattle = CLogicAllianceBattle::GetCDataAllianceBattle();
			if (!dataAllianceBattle)
			{
				cout<<"init_allianceBattle_fail"<<endl;
				return 0;
			}
			BattlePoint point;
			ret = dataAllianceBattle->GetBattlePoint(bid,point);
			cout<< point.archive<<endl;
		}
	}
	else
	{
		usage();
		return 0;
	}
	if (ret != 0)
	{
		cout << "start"<<action<<"fail,ret:" << ret << endl;
		return ret;
	}
	cout << "start "<<action<<" ok" << endl;
	return 0;
}
