/*
 * SyncAllServerLordsList.cpp
 *
 *  Created on: 2016-7-6
 *      Author: dawx62fac
 */



#include "LogicInc.h"
#include <iostream>
#include "LogicSyncLords.h"

void HttpRequest(const std::string& action, const std::string& data, Json::Value& result)
{
	string url = "action=" + action;
	url.append("&data=").append(Crypt::UrlEncode(data));

	//std::cout << "Req:" << data << std::endl;

	CLogicAllServerBaseMatch logicBaseMatch;
	int ret = logicBaseMatch.RequestBaseMatch(url, result, CONFIG_ALLSERVER_LORDS_CGI);
	if (ret != 0)
	{
		std::cout << "Request error. ret: " << result << std::endl;
		return ;
	}

	//std::cout << "result: " << result << std::endl;
}


void ExecutiveSync(const std::string& action, const std::string& path)
{
	try
	{
		if (action == "exploit")
		{
			LordExploitUnit lordExploritUnit;
			lordExploritUnit.Sync(path);
		}
		else if (action == "tryndamere")
		{
			LordTryndamereUnit lordTryndamereUnit;
			lordTryndamereUnit.Sync(path);
		}
//		else if (action == "plunder")
//		{
//			LordPlunderUnit lordPlunderUnit;
//			lordPlunderUnit.Sync(path);
//		}
		else if (action == "r5")
		{
			LordR5Unit lordR5Unit;
			lordR5Unit.Sync(path);
		}
		else if (action == "cost")
		{
			LordCostUnit lordCostUnit;
			lordCostUnit.Sync(path);
		}
		else if (action == "recharge")
		{
			LordRechargeUnit lordRechargeUnit;
			lordRechargeUnit.Sync(path);
		}
		else
		{
			std::cerr << "ExecutiveLordSync Unkonw action: " << action << std::endl;
		}
	}
	catch (std::exception& e) {
		std::cerr << "Sync: " << action << " error: " << e.what() << std::endl;
	}
}

void ExecutiveEestablish(const std::string& action, const std::string& path)
{
#if 0
	try
	{
		if (action == "exploit")
		{
			LordExploitUnit lordExploritUnit;
			lordExploritUnit.Establish();
		}
		else if (action == "tryndamere")
		{
			LordTryndamereUnit lordTryndamereUnit;
			lordTryndamereUnit.Establish();
		}
		else if (action == "plunder")
		{
			LordPlunderUnit lordPlunderUnit;
			lordPlunderUnit.Establish();
		}
		else if (action == "cost")
		{
			LordCostUnit lordCostUnit;
			lordCostUnit.Establish();
		}
		else if (action == "recharge")
		{
			LordRechargeUnit lordRechargeUnit;
			lordRechargeUnit.Establish();
		}
		else
		{
			std::cerr << "ExecutiveLordSync Unkonw action: " << action << std::endl;
		}
	}
	catch (std::exception& e) {
		std::cerr << "Sync: " << action << " error: " << e.what() << std::endl;
	}
#endif
}



int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		std::cerr << "args error." << std::endl;

		exit(0);
	}

	if (!Kernel::Init(APP_CONFIG_PATH))
	{
		cout << "init fail" << endl;
		return 0;
	}
	Config::SetDomain(0);
	//
	std::string action = argv[1];
	std::string szCmd = argv[2];
	std::string path ;
	if (argc > 3)
	{
		path = argv[3];
	}

	std::cout << "Time: " << Time::GetGlobalTime()
				<< "Action: " << action << " Cmd: " << szCmd
				<< " Path: " << path << std::endl;

	if (szCmd == "sync")
	{
		ExecutiveSync(action, path);
	}
	else if (szCmd == "establish")
	{
#if 0
		ExecutiveEestablish(action, path);
#endif
	}
	else
	{
		if (action == "action")
		{
			if (szCmd == "CloseWorship")
			{
				Json::Value result;
				HttpRequest("CloseWorship", "", result);
			}
			else if(szCmd == "StopUpExploit")
			{
				CLogicLordExploit logicExploit(path);
				logicExploit.Stop();
			}
		}
		else
		{
			std::cerr << "Unknown cmd:" << szCmd << std::endl;
		}

	}

}
