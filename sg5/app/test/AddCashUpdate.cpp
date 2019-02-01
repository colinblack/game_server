#include "LogicInc.h"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {

	if (!Kernel::Init(APP_CONFIG_PATH)) {
		cout << "Init kernel fail!" << endl;
		return -1;
	}
	Config::SetDomain(0);

	string reason;
	if(argc > 1)
		reason = argv[1];

	typedef pair<unsigned,int> cash;
	CLogicPay logicPay;
	CLogicUpdates logicUpdates;

CASH:
	{
		cout<<"cash"<<endl;
		vector<cash> vec;
		ifstream fin("cash");
		if (!fin.good()) {
			goto COIN;
		}
		while (!fin.eof() && fin.good()) {
			cash temp;
			fin >> temp.first >> temp.second;
			vec.push_back(temp);
		}

		for(vector<cash>::iterator it=vec.begin();it!=vec.end();++it)
		{
			int ret = logicPay.ChangePay(it->first, it->second, 0 , "ADMINOP", PAY_FLAG_COST_ALL);

			if(ret == 0)
			{
				//cout<<it->first<<" "<<it->second<<endl;

//				DataPayHistory payhis;
//				payhis.channel = PCT_TEST;
//				payhis.channel_pay_id = "0";
//				payhis.count = 1;
//				payhis.credit = it->second;
//				payhis.status = PST_OK;
//				payhis.type = 0;
//				payhis.uid = it->first;
//				payhis.open_id = "gm";
//				logicPay.AddPayHistory(payhis);

				if(!reason.empty())
				{
					Json::Value updatesData = Json::Value(Json::arrayValue);
					updatesData.resize(1);
					updatesData[0u]["ts"] = Time::GetGlobalTime();
					updatesData[0u]["s"] = "paybackmessage";
					updatesData[0u]["r"] = reason;
					updatesData[0u]["coins"] = it->second;
					ret = logicUpdates.AddUpdates(it->first, updatesData);
					if (0 != ret)
						cout << "AddUpdates fail,ret=" << ret << ",uid="<< it->first << endl;
				}
			}
			else
				cout<<it->first<<" "<<it->second<<" fail"<<endl;
		}

		system("rm cash -f");
	}

COIN:
	{
		cout<<"coin"<<endl;
		vector<cash> vec;
		ifstream fin("coin");
		if (!fin.good()) {
			goto LUCK;
		}
		while (!fin.eof() && fin.good()) {
			cash temp;
			fin >> temp.first >> temp.second;
			vec.push_back(temp);
		}

		for(vector<cash>::iterator it=vec.begin();it!=vec.end();++it)
		{
			int ret = logicPay.ChangePay(it->first, 0, it->second,  "ADMINOP", PAY_FLAG_COST_ALL);

			if(ret == 0)
			{
//				cout<<it->first<<" "<<it->second<<endl;

//				DataPayHistory payhis;
//				payhis.channel = PCT_TEST;
//				payhis.channel_pay_id = "0";
//				payhis.count = 1;
//				payhis.credit = it->second;
//				payhis.status = PST_OK;
//				payhis.type = 0;
//				payhis.uid = it->first;
//				payhis.open_id = "gm";
//				logicPay.AddPayHistory(payhis);

				if(!reason.empty())
				{
					Json::Value updatesData = Json::Value(Json::arrayValue);
					updatesData.resize(1);
					updatesData[0u]["ts"] = Time::GetGlobalTime();
					updatesData[0u]["s"] = "paybackmessage";
					updatesData[0u]["r"] = reason;
					updatesData[0u]["coins"] = it->second;
					ret = logicUpdates.AddUpdates(it->first, updatesData);
					if (0 != ret)
						cout << "AddUpdates fail,ret=" << ret << ",uid="<< it->first << endl;
				}
			}
			else
				cout<<it->first<<" "<<it->second<<" fail"<<endl;
		}

		system("rm coin -f");
	}

LUCK:
	{
		cout<<"luck"<<endl;
		vector<unsigned> vec;
		ifstream fin("luck");
		if (!fin.good()) {
			goto END;
		}
		while (!fin.eof() && fin.good()) {
			unsigned temp;
			fin >> temp;
			vec.push_back(temp);
		}

		for(vector<unsigned>::iterator it=vec.begin();it!=vec.end();++it)
		{
			Json::Value updatesData = Json::Value(Json::arrayValue);
			updatesData.resize(1);
			updatesData[0u]["ts"] = Time::GetGlobalTime();
			updatesData[0u]["s"] = "luckyplayer";
			int ret = logicUpdates.AddUpdates(*it, updatesData);
			if (0 != ret) {
				cout << "AddUpdates fail,ret=" << ret << ",uid="
						<< *it << endl;
			}
			cout<<*it<<endl;
		}

		system("rm luck -f");
	}

END:
	return 0;
}

