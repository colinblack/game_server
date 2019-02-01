/*
 * ConfigXMLTest.cpp
 *
 *  Created on: 2014-5-6
 *      Author: dawx123
 */




#include "LogicInc.h"

void usage()
{
	cout << "usage: GetInitXML 	xml " << endl;
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
	CDataXML *dataXML1 = CDataXML::GetCDataXML();
	if(!dataXML1)
	{
		cout << "GetInitXML1 fail" << endl;
		return 1;
	}

	if (action == "signinreward")
	{
		XMLSignInReward reward;
		for (int i = 0;i < 5; ++i)
		{
			int ret = dataXML1->GetSignInReward(i, reward);
			std::cout << "index: " << i << " ret: " << ret << std::endl;
			std::cout << "Gold: " << reward.gold
					 << " prosper: " << reward.prosper
					 << " equipCnt: " << reward.equipCnt
					<< std::endl;
		}
	}
	else if (action == "hero")
	{
		XMLHero hero;
		ret = dataXML1->GetHero(3001,hero);
		unsigned hero1, hero2, hero3,star1,star2,star3;
		ret = dataXML1->RefreshHero(2, hero1, star1, hero2, star2, hero3, star3);
		cout<<hero1<<" "<<hero2<<" "<<hero3<<" "<<endl;
	}
	else if (action == "refreshhero")
	{
		int total = 1000000;
		map<unsigned, unsigned> all[3];
		for(int i=0;i<total;++i)
		{
			for(unsigned j=0;j<3;++j)
			{
				XMLHero hero;
				unsigned hero1, hero2, hero3,star1,star2,star3;
				ret = dataXML1->RefreshHero(j, hero1, star1, hero2, star2, hero3, star3);
				dataXML1->GetHero(hero1,hero);
				++all[j][hero.type];
				dataXML1->GetHero(hero2,hero);
				++all[j][hero.type];
				dataXML1->GetHero(hero3,hero);
				++all[j][hero.type];
			}
		}
		for(unsigned j=0;j<3;++j)
		{
			cout<<"refresh type:"<<j<<endl;
			for(unsigned k=0;k<10;++k)
			{
				if(all[j].count(k))
				{
					float p=(float)all[j][k]/(float)total;
					cout<<"hero type:"<<k<<" "<<all[j][k]<<"/"<<total<<"="<<p<<endl;
				}
			}
		}
	}
	else if (action == "vip")
	{
		XMLVIP vip;
		ret = dataXML1->GetVIP(1,vip);
		unsigned vipcharge[XML_VIP_GRADE];
		ret = dataXML1->GetVIPCharge(vipcharge);
	}
	else if (action == "mixhero")
	{
		XMLSourceHero mixhero[XML_HERO_SOURCE];
		ret = dataXML1->GetMixHero(1,2,mixhero);
	}
	else if (action == "getequipsub")
	{
		vector<string> keep;
		keep.push_back("p1");
		keep.push_back("p2");
		vector<EquipSub> sub;
		unsigned stone,gold;
		ret = dataXML1->GetEquipSub(90,stone,gold,5,keep,sub);
		if(ret == 0)
		{
			cout<<stone<<" "<<gold<<endl;
			cout<<sub[0].id<<" "<<sub[0].star<<endl;
			cout<<sub[1].id<<" "<<sub[1].star<<endl;
			cout<<sub[2].id<<" "<<sub[2].star<<endl;
			cout<<sub[3].id<<" "<<sub[1].star<<endl;
			cout<<sub[4].id<<" "<<sub[2].star<<endl;
		}
	}
	else if (action == "tryequipsub")
	{
		vector<EquipSub> sub;
		vector<string> keep;
		unsigned stone,gold;
		unsigned sum = 0, ten = 0;
		for(int i=0;i<1000000;++i)
		{
			ret = dataXML1->GetEquipSub(110,stone,gold,5,keep,sub);
			if(ret == 0)
			{
				sum += 5;
				for(unsigned k=0;k<5;k++)
				{
					if(sub[k].star == 10)
						++ten;
				}
			}
		}
		float p=(float)ten/(float)sum;
		cout<<ten<<"/"<<sum<<"="<<p<<" "<<endl;
	}
	else if (action == "treasurehunt")
	{
		unsigned id = Math::GetRandomInt(200) + 1;
		cout<<"start id="<<id<<endl;
		vector<TreasureHuntItem> result;
		ret = dataXML1->GetTreasureHunt(id,100,result);
		if(ret == 0)
		{
			for(int i=0;i<result.size();++i)
				cout<<"id="<<result[i].id<<" type="<<result[i].type<<" point="<<result[i].point<<" jade="<<result[i].jade<<" equip="<<result[i].equip<<" count="<<result[i].count<<endl;
		}
	}
	else if (action == "sggiftbagconfig")
	{
		if (argc < 5 )
		{
			cout << "usage: GetInitXML 	xml uid gift_id count" << endl;
			return 1;
		}
		Json::Value data;
		data.clear();

		unsigned uid = CTrans::STOI(argv[2]);
		unsigned gift_id = CTrans::STOI(argv[3]);
		unsigned count = CTrans::STOI(argv[4]);

		ret = dataXML1->GetGiftBag(uid,gift_id,count,data);

//		CLogicCMD Cmd;
//		ret = Cmd.useGiftBag(uid,gift_id,ud,data);
	}
	else if (action == "storeitem")
	{
		if (argc < 3 )
		{
			cout << "usage: ConfigXMLTest storeitem id" << endl;
			return 1;
		}
		unsigned id = CTrans::STOI(argv[2]);
		XMLShop item;
		ret = dataXML1->GetShopItem(id,item);
		if(ret == 0)
		{
			cout<<"id="<<item.id<<" type="<<item.type<<" price="<<item.price<<" vip="<<item.vip<<" ch="<<item.ch<<endl;
		}
	}
	else if (action == "juexue")
	{
		if (argc < 3 )
		{
			cout << "usage: ConfigXMLTest juexue level" << endl;
			return 1;
		}
		unsigned level = CTrans::STOI(argv[2]);
		unsigned npc = 0, id, cost, next;
		map<unsigned, unsigned> all;
		unsigned sum = 0;
		for(int i=0;i<1000000;++i)
		{
			ret = dataXML1->GetJuexue(npc, false, level, cost, id, next);
			if(ret == 0)
			{
				cout<<"cost:"<<cost<<" next:"<<next<<" id:"<<id<<endl;
				if(all.count(id))
					++all[id];
				else
					all[id] = 1;
				++sum;
				npc = next;
			}
			else
				cout<<"ret:"<<ret<<endl;
		}
		for(map<unsigned, unsigned>::iterator it=all.begin();it!=all.end();++it)
			cout<<it->first<<" "<<(float)it->second/(float)sum<<" "<<it->second<<endl;
		cout<<sum<<endl;
	}
	else if (action == "activityconfig")
	{
		string act = argv[2];
		map<string, string> config;
		ret = dataXML1->GetActivityConfig(act, config);
		for(map<string, string>::iterator it=config.begin();it!=config.end();++it)
			cout<<it->second<<endl;
	}
	else if (action == "olgateconfig")
	{
		unsigned id = CTrans::STOI(argv[2]);
		map<string, string> config;
		ret = dataXML1->GetOlGateConfig(id, config);
		for(map<string, string>::iterator it=config.begin();it!=config.end();++it)
			cout<<it->second<<endl;
	}
	else if (action == "questconfig")
	{
		string questid = argv[2];
		Json::Value config;
		ret = dataXML1->GetQuestConfig(questid, config);
		cout<<Json::ToString(config)<<endl;
	}


	if (ret != 0)
	{
		cout << "try "<<action<<" fail,ret:" << ret << endl;
		return ret;
	}
	cout << "try "<<action<<" ok" << endl;
	return 0;
}


