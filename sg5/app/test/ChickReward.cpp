/*
 * ChickReward.cpp
 *
 *  Created on: 2018年7月27日
 *      Author: Ralf
 */

#include "LogicInc.h"

int main(int argc, char *argv[])
{
	if (!Kernel::Init(APP_CONFIG_PATH))
	{
		cout << "init kernel fail" << endl;
		return 1;
	}
	Config::SetDomain(0);

	if(argc < 2)
	{
		cout<<"need zone num"<<endl;
		return 1;
	}
	unsigned num = atoi(argv[1]);
	if(num == 0)
	{
		cout<<"need zone num"<<endl;
		return 1;
	}

	Json::Reader reader;
	CLogicUpdates logicUpdates;
	CLogicEquipment LogicEquipment;
	Json::Value res, update;

	map<unsigned, pair<unsigned, string> > am;
	string arp = string(CHICK_PATH) + "ranklist";
	string arb;
	Json::Value arl;
	int ver = 0;
	if(File::Read(arp,arb) == 0 && reader.parse(arb, arl) && (ver = arl["ver"].asUInt()) < CHICK_SEASON)
	{
		for(unsigned i=0;i<arl["rank"].size();++i)
			am[arl["rank"][i]["uid"].asUInt()] = make_pair(arl["rank"][i]["score"].asUInt(), arl["rank"][i]["name"].asString());
	}

	for(int index=1;index<=num;++index)
	{
		map<unsigned, string> nm;
		string rp = CHICK_PATH + CTrans::UTOS(index) + ".zone";
		string rb;
		Json::Value rl;
		if(File::Read(rp,rb) == 0 && reader.parse(rb, rl))
		{
			Json::Value::Members m = rl.getMemberNames();
			for(Json::Value::Members::iterator it=m.begin();it!=m.end();++it)
				nm[rl[*it]["uid"].asUInt()] = rl[*it]["name"].asString();
		}

		string ranklist_path = CHICK_PATH + CTrans::UTOS(index) + ".result";
		string ranklist_buff;
		int ret = File::Read(ranklist_path,ranklist_buff);
		if (0 != ret)
		{
			cout << "Read file faile path=" << ranklist_path << endl;
			continue;
		}
		Json::Value ranklist;
		if (!reader.parse(ranklist_buff, ranklist) || !ranklist.isArray())
		{
			cout << "Parse Json error!" << reader.getFormatedErrorMessages() << endl;
			continue;
		}

		for(unsigned i=0;i<ranklist.size();++i)
		{
			if(i >= CHICK_USER)
				break;

			unsigned uid = ranklist[i]["Uid"].asUInt();
			unsigned score = ranklist[i]["Score"].asUInt();

			if(am.count(uid))
				score += am[uid].first;
			am[uid] = make_pair(score, nm[uid]);

			/*
			unsigned id = 50127;
			unsigned c = 0;
			if(i < 1)
				c = 20;
			else if(i < 2)
				c = 15;
			else if(i < 3)
				c = 12;
			else if(i < 6)
				c = 10;
			else if(i < 10)
				c = 8;
			else if(i < 20)
				c = 6;
			else
				c = 3;
			LogicEquipment.AddOneItem(uid, id, c, "ChickReward", res);
			update["ts"] = Time::GetGlobalTime();
			update["s"] = "ChickReward";
			update["r"] = i + 1;
			update["id"] = id;
			update["c"] = c;
			logicUpdates.AddUpdates(uid, update, true);
			*/
		}
	}

	vector<pair<unsigned, pair<unsigned, string> > > all;
	for(map<unsigned, pair<unsigned, string> >::iterator it=am.begin();it!=am.end();++it)
		all.push_back(make_pair(it->second.first, make_pair(it->first, it->second.second)));
	sort(all.begin(), all.end());

	++ver;
	if(ver > CHICK_SEASON)
		ver = 1;
	arl.clear();
	arl["ver"] = ver;
	arl["rank"].resize(0);
	unsigned i=0;
	for(vector<pair<unsigned, pair<unsigned, string> > >::reverse_iterator it=all.rbegin();it!=all.rend();++it)
	{
		Json::Value t;
		t["uid"] = it->second.first;
		t["score"] = it->first;
		t["name"] = it->second.second;
		arl["rank"].append(t);

		if(ver == CHICK_SEASON)
		{
			if(i >= CHICK_REWARD)
				continue;

			/*
			unsigned id = 50127;
			unsigned c = 0;
			if(i < 1)
				c = 80;
			else if(i < 2)
				c = 70;
			else if(i < 3)
				c = 60;
			else if(i < 6)
				c = 50;
			else if(i < 10)
				c = 40;
			else if(i < 25)
				c = 35;
			else if(i < 50)
				c = 30;
			else
				c = 20;
			LogicEquipment.AddOneItem(it->second.first, id, c, "ChickSeason", res);
			update["ts"] = Time::GetGlobalTime();
			update["s"] = "ChickReward";
			update["r"] = i + 1;
			update["id"] = id;
			update["c"] = c;
			logicUpdates.AddUpdates(it->second.first, update, true);
			*/

			++i;
		}
	}
	arb = Json::FastWriter().write(arl);
	File::Write(arp, arb);

	cout << "ok" << endl;
	return 0;
}
