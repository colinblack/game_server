/*
 * R5.cpp
 *
 *  Created on: 2015-8-6
 *      Author: Ralf
 */


#include "LogicInc.h"
#include <iostream>

int GetE3(int rank)
{
	if(rank <= 1)
		return 8;
	else if(rank <= 3)
		return 6;
	else if(rank <= 10)
		return 4;
	else if(rank <= 20)
		return 2;
	else if(rank <= 30)
		return 1;
	else
		return 0;
}

int main(int argc, char *argv[])
{
	if (!Kernel::Init(APP_CONFIG_PATH))
	{
		cout << "init kernel fail" << endl;
		return 1;
	}
	Config::SetDomain(0);

	set<int> db;
	string serverid;
	unsigned zone;
	if (Config::GetValue(serverid, CONFIG_SERVER_ID))
	{
		Convert::StringToUInt(zone, serverid);
		unsigned domain = MainConfig::GetMergedDomain(zone);
		if(domain != zone)
		{
			cout<<domain<<"!="<<zone<<endl;
			return 0;
		}
		MainConfig::GetIncludeDomains(domain, db);
		for(set<int>::iterator it=db.begin();it!=db.end();++it)
			cout<<*it<<" ";
		cout<<endl;
	}

	string ranklist_path("../webroot/data/r5");
	string ranklist_buff;
	int ret = File::Read(ranklist_path,ranklist_buff);
	if (0 != ret)
	{
		cout << "Read file faile path=" << ranklist_path << endl;
		return 1;
	}
	Json::Reader reader;
	Json::Value ranklist;
	if (!reader.parse(ranklist_buff, ranklist) || !ranklist.isMember("r5") || !ranklist["r5"].isArray())
	{
		cout << "Parse Json error!" << reader.getFormatedErrorMessages() << endl;
		return 1;
	}

	CLogicUpdates logicUpdates;
	CLogicAlliance logicAlliance;
	unsigned now = Time::GetGlobalTime();
	for(unsigned i=0;i<ranklist["r5"].size();++i)
	{
		vector<DataAllianceMember> members;
		ret = logicAlliance.GetMembers(ranklist["r5"][i]["aid"].asUInt(), members);
		if(ret != 0)
			return ret;
		for(vector<DataAllianceMember>::const_iterator itr = members.begin(); itr != members.end(); itr++)
		{
			Json::Value update;
			update["s"] = "R5";
			update["rank"] = i + 1;
			update["r5"] = ranklist["r5"][i]["r5"].asInt();
			update["e3"] = GetE3(i+1);
			update["ts"] = now;
			ret = logicUpdates.AddUpdates(itr->uid, update);
			if (0 != ret)
			{
				cout << "AddUpdates error uid=" << itr->uid << endl;
			}
		}
	}

	cout << "ok" << endl;
	return 0;
}





