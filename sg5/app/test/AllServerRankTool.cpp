/*
 * AllServerRankTool.cpp
 *
 *  Created on: 2014-7-10
 *      Author: Ralf
 */

#include "LogicInc.h"
#include <iostream>
#include <fstream>


int main(int argc, char *argv[])
{
	if (!Kernel::Init(APP_CONFIG_PATH))
	{
		cout << "init fail" << endl;
		return 0;
	}
	Config::SetDomain(0);

	string arg;
	bool init = false;
	if(argc > 1)
		arg = argv[1];
	if(arg == "day")
		init = true;


	if(init)
	{
		int ret = 0;
		CDataAllServerRank *data = CDataAllServerRank::GetCDataAllServerRank();
		if(!data)
		{
			cout << "GetCDataAllServerRank fail" << endl;
			return 1;
		}

		ret = data->Reward();
		if(ret)
			cout<<"Reward all server rank fail!"<<endl;
		//ret = data->Watch();

		/*
		ret = data->Rank();
		if(ret)
			cout<<"rank all server rank fail!"<<endl;
		//ret = data->Watch();
		*/

		ret = data->Day();
		if(ret)
			cout<<"day all server rank fail!"<<endl;
		//ret = data->Watch();
		system("killall -12 CgiAllServerRank");
	}
	else
	{
		int ret = 0;
		CDataAllServerRank *data = CDataAllServerRank::GetCDataAllServerRank(false);
		if(!data)
		{
			cout << "GetCDataAllServerRank fail" << endl;
			return 1;
		}

		ret = data->Watch();
	}

	return 0;
}
