/*
 *SaveRankPoint.cpp
 *
 *  Created on: 2016-10-10
 *      Author: City
 */

#include "LogicInc.h"
#include <fstream>
#include "Admin.pb.h"

int main(int argc, char* argv[])
{
	if (!Kernel::Init())
	{
		cout << "init error";
		return 1;
	}

	if (argc != 2)
	{
		cout << "param error. usage: ./programe param";
		return 1;
	}
	uint32_t param = CTrans::STOI(argv[1]);
	if(param != 1)
	{
		error_log("invalid param=%u", param);
		return 1;
	}
	/*
	string dbIp;
	if(!MainConfig::GetValue(dbIp, "sg17_mapping_host"))
	{
		error_log("read dbIp sg17_mapping_host fail");
		return 1;
	}
	string path = Config::GetPath("tools/");
	string file = path + "rankpoint.json";
	Json::Value globalRank;
	FileToJson::fileToJson(file, globalRank);
	if(!globalRank.isArray())
	{
		error_log("invalid format");
		return 1;
	}
	string sqlStr = "mysql -uroot -p1234 -h" + dbIp + " -e 'replace into sg17_mapping.alliance_race_point(alliance_id,version,point) values";
	uint32_t count = 0;
	for(uint32_t i = 0; i < globalRank.size(); ++i)
	{
		Json::Value& obj = globalRank[i];
		uint32_t aid = 0;
		uint32_t version = 0;
		uint32_t point = 0;
		if(obj.isMember("v") && Json::GetUInt(obj, "v", version))
		{
		}
		if(obj.isMember("aid") && Json::GetUInt(obj, "aid", aid))
		{
		}
		if(obj.isMember("p") && Json::GetUInt(obj, "p", point))
		{
		}
		if(aid > 0)
		{
			if(count++ > 0)
			{
				sqlStr += ",";
			}
			sqlStr += "(" + CTrans::UTOS(aid) + "," + CTrans::UTOS(version) + "," + CTrans::UTOS(point) + ")";
		}
	}
	sqlStr += ";'";
	cout << sqlStr << endl;
	if(system(sqlStr.c_str()) == -1)
	{
		error_log("system fail");
		return 1;
	}

	cout<<"batch success"<<endl;
	*/
	return 0;
}


