/*
 * search.cpp
 *
 *  Created on: 2018年9月21日
 *      Author: Ralf
 */

#include "LogicInc.h"
#include <fstream>
#include <iostream>
#include <math.h>


int main(int argc, char *argv[]) {
	if (!Kernel::Init(APP_CONFIG_PATH)) {
		cout << "Init kernel fail!" << endl;
		return -1;
	}
	Config::SetDomain(0);
	int ret = 0;

	if (argc < 2)
	{
		std::cout << "parsms error" << std::endl;
		return 1;
	}

	fstream fin(argv[1]);
	if (!fin.good()) {
		cout << "open file fail" << endl;
		return 1;
	}

	CLogicUser lgUser;
	CLogicHero lgHero;
	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		cout<<"xml error"<<endl;
		return R_ERR_DATA;
	}
	string z("[[11001,10],[11005,10],[11002,8],[11003,3],[11006,5],[11008,5],[11004,8],[11007,5],[11022,10],[11023,8],[11024,3],[11025,5],[11026,5],[11021,5],[11041,10],[11042,10],[11043,10],[11044,5],[11009,3],[11027,3],[11028,5],[11029,3],[11051,8],[11052,5]]");
	string g("[[12001,10],[12002,10],[12003,8],[12004,5],[12006,3],[12041,10],[12009,5],[12042,10],[12005,8],[12007,3],[12008,5],[12010,3],[12023,5],[12024,3],[12026,5],[12028,3],[12043,10],[12044,5],[12051,3],[12052,8],[12021,10],[12022,8],[12025,5],[12027,5]]");
	string f("[[13002,10],[13021,10],[13022,8],[13001,10],[13041,10],[13042,8],[13003,8],[13004,3],[13009,5],[13010,3],[13043,5],[13044,5],[13005,5],[13007,5],[13008,5],[13045,5],[13046,5],[13047,3],[13023,5],[13025,3],[13026,5],[13027,3],[13051,8],[13052,5]]");
	Json::Value s;
	s.resize(4);
	Json::Reader reader;
	reader.parse(z,s[1u]);
	reader.parse(g,s[2u]);
	reader.parse(f,s[3u]);
	while (!fin.eof() && fin.good()) {
		unsigned uid = 0;
		fin >> uid;
		DataUser user;
		map<unsigned,Json::Value> data;
		/*
		if(lgUser.GetUserLimit(uid, user) == 0 && user.level >= 30 &&  user.level < 85 && lgHero.GetHero(uid, data) == 0)
		{
			for(map<unsigned,Json::Value>::iterator it=data.begin();it!=data.end();++it)
			{
				if(it->second["def"].asInt() == 1 && it->second["tskill"].size() == 0)
				{
					cout<<uid<<endl;
					break;
				}
			}
		}
		*/
		if(lgHero.GetHero(uid, data) == 0)
		{
			for(map<unsigned,Json::Value>::iterator it=data.begin();it!=data.end();++it)
			{
				if(it->second["l"].asInt() >= 100)
				{
					XMLHero hero;
					string id = it->second["id"].asString();
					pDataXML->GetHero(CDataXML::Str2Hero(id), hero);
					if(hero.prof >= 1 && hero.prof <= 3)
					{
						it->second["tskill"] = s[hero.prof];
						lgHero.Chg(uid, it->first, it->second);
					}
				}
			}
		}
	}

	return R_SUCCESS;
}
