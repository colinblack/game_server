#include "LogicInc.h"
#include <iostream>
#include <fstream>
using namespace std;


struct ItemConsume
{
	unsigned uid_, num_;
	ItemConsume(): uid_(0), num_(0)
	{}
};


int calcute_soul(float& b_sgrowth, int num_temp)
{
	for(;  num_temp > 0; --num_temp)
	{
		float sub = 0.0;
		if (b_sgrowth > 0 && b_sgrowth < 780)  			 // (0, 780)     吃  6001
		{
			sub = 0.3*10;
		} else if (b_sgrowth >= 780 && b_sgrowth < 1516) // [780, 1516)  吃  6002
		{
			sub = 0.02667*10;
		} else if (b_sgrowth >= 1516) 					 // [1516    )    吃 6003
		{
			sub = 0.01*10;
		} else
		{
			b_sgrowth = 0.0;
			break;
		}

		b_sgrowth -= sub;
		if (b_sgrowth < 0)
		{
			b_sgrowth = 0;
		}
	}

	return R_SUCCESS;
}


int main(int argc, const char *argv[])
{
	if(argc != 2)
	{
		cout<<"need file"<<endl;
		return 1;
	}
	if (!Kernel::Init(APP_CONFIG_PATH))
	{
		cout << "init kernel fail" << endl;
		return 1;
	}

	vector<ItemConsume> process_soul;
	process_soul.clear();
	ifstream fin(argv[1]);
	if (!fin.good())
	{
		cout<<"file error"<<endl;
		return 1;
	}
	while (!fin.eof() && fin.good())
	{
		//文件记录格式：uid	eqid(消耗的道具)		num(消耗的道具个数)
		unsigned uid_temp = 0, eqid_temp = 0, num_temp = 0;
		fin >> uid_temp >> eqid_temp >> num_temp;
		if (uid_temp &&
			num_temp &&
		    (eqid_temp == 6001))   //魔元丹：  6001
		{
			ItemConsume item_temp;
			item_temp.uid_ = uid_temp;
			item_temp.num_ = num_temp;
			process_soul.push_back(item_temp);
		} else
		{
			cout <<"unprocess uid: "<< uid_temp << endl;

		}
	}

	cout << "uid  "
		 << "eqid  "
		 << "num  "
		 << "now_sgrowth  "
		 << "b_sgrowth" << endl;

	for(vector<ItemConsume>::iterator it=process_soul.begin(); it != process_soul.end(); ++it)
	{
		unsigned uid_temp = 0, num_temp = 0;
		uid_temp = it->uid_;
		num_temp = it->num_;

		CLogicUser logicUser;
		DataUser dataUser;
		int ret = 0;
		ret = logicUser.GetUser(uid_temp, dataUser);
		if(ret)
			return ret;
		Json::Value tech;
		Json::Reader reader;
		reader.parse(dataUser.user_tech, tech);
		int now_sgrowth = tech["sgrowth"].asInt(); 	//,"sgrowth":1428,
		if (now_sgrowth > 0 && num_temp > 0)
		{
			float b_sgrowth = 0.0;
			b_sgrowth = now_sgrowth;
			calcute_soul(b_sgrowth, num_temp);

			tech["sgrowth"] = ceil(b_sgrowth);
			Json::FastWriter writer;
			dataUser.user_tech = writer.write(tech);
			ret = logicUser.SetUser(uid_temp, dataUser);
			if (ret)
			{
				return ret;
			}
			cout << uid_temp << " "
				 << "6001" << " "
				 << num_temp << " "
				 << now_sgrowth << " "
				 << ceil(b_sgrowth) << endl;

		}
	}

	cout << "ok" << endl;
}
