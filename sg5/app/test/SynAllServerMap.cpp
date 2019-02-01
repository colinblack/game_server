/*
 * SynAllServerMap.cpp
 *
 *  Created on: 2015-9-17
 *      Author: Ralf
 */



#include "LogicInc.h"

int main(int argc, char *argv[])
{
	if (!Kernel::Init(APP_CONFIG_PATH))
	{
		cout << "init fail" << endl;
		return 0;
	}
	Config::SetDomain(0);

	if(argc > 1)
	{
		string arg = argv[1];
		if(arg == "build")
		{
			int serverid;
			Config::GetDB(serverid);
			uint64_t uidEnd;
			unsigned userid = Config::GetUIDStart(serverid);
			CLogicIdCtrl logicIdCtrl;
			int ret = logicIdCtrl.GetCurrentId(KEY_UID_CTRL, uidEnd, serverid);
			if (ret != 0)
			{
				cout<<"get current user id fail!";
				return ret;
			}
			Json::Value val;
			val.resize(0);
			int n = 0;
			for (; userid <= (unsigned) uidEnd; ++userid)
			{
				int mainBdLvl;
				Json::Value mainBd;
				CLogicBuilding logicBd;
				ret = logicBd.Get(userid, 1,0,true, mainBd);
				if (ret)
					continue;
				if (mainBd.isMember("l") && mainBd["l"].isIntegral())
					mainBdLvl = mainBd["l"].asInt();
				else
					continue;
				if(mainBdLvl < ALL_SERVER_MAP_MIN_LEVEL)
					continue;
				Json::Value temp;
				temp[0u] = userid;
				temp[1u] = mainBdLvl;
				val.append(temp);

				++n;
				if(n == 10 || userid == (unsigned) uidEnd)
				{
					string url = "action=set";
					string datastr = Json::ToString(val);
					url.append("&data=").append(Crypt::UrlEncode(datastr));

					CLogicAllServerBaseMatch logicBaseMatch;
					Json::Value result;
					logicBaseMatch.RequestBaseMatch(url,result,CONFIG_ALLS_MAP_PATH);

					val.resize(0);
					n = 0;
				}
			}
			return 0;
		}
	}

	CLogicAllServerMap logicAllServerMap;
	return logicAllServerMap.Syn();
}

