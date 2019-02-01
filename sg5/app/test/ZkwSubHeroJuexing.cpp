#include "LogicInc.h"
#include "LogicCMD.h"
#include <iostream>
#include <fstream>
using namespace std;


struct ItemConsume
{
	unsigned uid_, num_;
	ItemConsume(): uid_(0), num_(0)
	{}
};


int calcute_juexing(unsigned level, unsigned cur, unsigned num, unsigned & inital, unsigned & b_lv)
{
	unsigned lv = level;

	int times = 90;

	unsigned expand_times = 100;
	//计算从下一级升到当前级，需要多少道具

	unsigned lastexp = 0;

	if (0 != lv)
	{
		lastexp = (unsigned)(HERO_POWER_2_UP_COST[lv-1][2]*times)/expand_times;   //升级到目前等级所需的道具个数
	}

	unsigned curper = (HERO_POWER_2_UP_COST[lv][1]);

	unsigned curneedeq = (HERO_POWER_2_UP_COST[lv][0]);

	//这个是从经验0开始增加的

	unsigned curtimes = (unsigned)ceil((cur)/(float)curper);   //升级到目前等级所需的次数

	unsigned use_num = curtimes * curneedeq;   //需要消耗的道具数

	if (use_num >= num)   //当前道具个数大于已消耗的道具个数,说明初始经验大于起始经验
	{
		//cout<<"\t"<<lv<<flush;
		b_lv = lv;
		//计算根据当前道具个数，可以点击多少次
		unsigned realtimes = (unsigned)ceil((num)/(float)curneedeq);   //升级到目前等级所需的次数
		unsigned addexp =  (curper)*realtimes;  //使用道具，实际增长的经验

		if (cur <= addexp)
		{
			inital = 0;
		}
		else
		{
			inital = (cur - addexp);
		}
	}
	else if (0 == lv)
	{
		inital = 0;
		//cout<<"\t"<<lv<<flush;
		b_lv = lv;
	}
	else
	{
		calcute_juexing(lv - 1, lastexp, num - use_num , inital, b_lv);
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

	vector<ItemConsume> process_juexing;
	process_juexing.clear();
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
		    (eqid_temp == 6050))   //洗髓丹：  6050
		{
			ItemConsume item_temp;
			item_temp.uid_ = uid_temp;
			item_temp.num_ = num_temp;
			process_juexing.push_back(item_temp);
		} else
		{
			cout <<"unprocess uid: "<< uid_temp << endl;

		}
	}

	cout << "uid  "
		 << "eqid  "
		 << "heroid  "
		 << "num  "
		 << "now_exp  "
		 << "now_lv  "
		 << "b_exp  "
		 << "b_lv" << endl;

	for(vector<ItemConsume>::iterator it=process_juexing.begin(); it != process_juexing.end(); ++it)
	{
		unsigned uid_temp = 0, num_temp = 0;
		uid_temp = it->uid_;
		num_temp = it->num_;

		CLogicHero logicHero;
		Json::Value heroData;
		heroData.clear();
		int ret = 0;
		ret = logicHero.GetHero(uid_temp, heroData);
		if (0 == ret)
		{
			for (int j=0; j<heroData.size(); ++j)
			{
				int def = 0;
				if (Json::GetInt(heroData[j], "def", def) && (1 == def))  //只删除主将的觉醒, def==1 时代表主将
				{
					Json::Value & hero = heroData[j];
					if(hero.isMember("ud") &&
					   hero.isMember("hs") && hero["hs"].isArray() && (hero["hs"].size() == 4))
					{
						//核心逻辑
						unsigned now_lv = 0,  now_exp = 0,  b_exp = 0,  b_lv = 0;
						now_lv =  hero["hs"][0u].asUInt();  //觉醒的数据表的存放格式   "hs":[25,304,0,0]
						now_exp = hero["hs"][1u].asUInt();
						calcute_juexing(now_lv, now_exp, num_temp, b_exp, b_lv);
						hero["hs"][0u] = b_lv;
						hero["hs"][1u] = b_exp;

						unsigned ud_temp = 0;
						ud_temp = hero["ud"].asUInt();
						string heroid = "";
						heroid = hero["id"].asString();
						ret = logicHero.Chg(uid_temp, ud_temp, hero);
						if(ret)
							return ret;
						cout << uid_temp << " "
							 << "6050" << " "
							 << heroid.c_str() << " "
							 << num_temp << " "
							 << now_exp << " "
							 << now_lv << " "
							 << b_exp << " "
							 << b_lv << endl;
						break;
					}
				}
			}
		}
	}

	cout << "ok" << endl;
}
