#include "LogicInc.h"
#include "LogicCMD.h"
#include <iostream>
#include <fstream>
using namespace std;


struct ItemConsume
{
	unsigned uid_, num_, eqid;
	ItemConsume(): uid_(0), num_(0),eqid(0)
	{}
};


int calcute_hevenDao(int type, unsigned cur, unsigned num, unsigned & inital, unsigned & b_lv)
{
	int ret = R_SUCCESS;

	if (0 == cur)
	{
		inital = 0;
		cout<<"rest num is:"<<num<<endl;
		return R_SUCCESS;
	}

	//根据经验，计算等级
	CDataXML *dataXML = CDataXML::GetCDataXML();
	XMLHeavenDaoist xmlHeavenDaoist;
	unsigned typePrefix = type ? HEAVEN_PREFIX : DAOIST_PREFIX;

	unsigned lv = 0;

	ret = dataXML->GetHeavenDaoistLv(typePrefix + MAXLV, cur, lv);

	if (ret)
	{
		return ret;
	}
	else
	{
		lv = type ? lv : (lv - HEAVEN_NUM);
	}

	//cout<<"cur-level is:"<<lv<<endl;

	ret = dataXML->GetHeavenDaoistItem(typePrefix + lv, xmlHeavenDaoist);

	unsigned curper = xmlHeavenDaoist.per;
	//unsigned curres = xmlHeavenDaoist.res;
	unsigned curneedeq = xmlHeavenDaoist.needeq;

	//计算出当前兵书的等级
	unsigned startexp = xmlHeavenDaoist.exp;

	unsigned curtimes = (unsigned)ceil((cur - startexp)/(float)curper);   //升级到目前等级所需的次数

	unsigned use_num = curtimes * curneedeq;   //需要消耗的道具数

	if (use_num >= num)   //当前道具个数大于已消耗的道具个数,说明初始经验大于起始经验
	{
		//cout<<"\t"<<lv<<flush;
		b_lv = lv;
		//计算根据当前道具个数，可以点击多少次
		unsigned realtimes = (unsigned)ceil((num)/(float)curneedeq);   //升级到目前等级所需的次数

		inital = (cur - (curper)*realtimes);
	}
	else
	{
		calcute_hevenDao(type, startexp, num - use_num , inital, b_lv);
	}

	//升阶之后，经验清为0
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

	//读文件，然后把满足条件的存放到vector里
	int ret = 0;
	vector<ItemConsume> process_hevens;
	process_hevens.clear();

	ofstream oper_log("heaven_dao.log", ios::out);
	ifstream fin(argv[1]);

	if (!fin.good())
	{
		cout<<"file error"<<endl;
		return 1;
	}

	const unsigned DAO_EQID = 4071;
	const unsigned HEAVEN_EQID = 4070;

	while (!fin.eof() && fin.good())
	{
		//文件记录格式：uid	eqid(消耗的道具)		num(消耗的道具个数)
		unsigned uid_temp = 0, eqid_temp = 0, num_temp = 0;
		fin >> uid_temp >> eqid_temp >> num_temp;
		if (uid_temp &&
			num_temp &&
		    (eqid_temp == HEAVEN_EQID || eqid_temp == DAO_EQID))   //兵书残卷：  4070,遁甲残卷 4071
		{
			ItemConsume item_temp;
			item_temp.uid_ = uid_temp;
			item_temp.num_ = num_temp;
			item_temp.eqid = eqid_temp;

			process_hevens.push_back(item_temp);
		}
		else
		{
			cout <<"unprocess uid: "<< uid_temp << endl;

		}
	}

	oper_log << "uid  "
		 << "eqid  "
		 << "num  "
		 << "now_exp  "
		 << "now_lv  "
		 << "b_exp  "
		 << "b_lv" << endl;

	for(vector<ItemConsume>::iterator it = process_hevens.begin(); it != process_hevens.end(); ++it)
	{
		unsigned uid_temp = 0, num_temp = 0;
		uid_temp = it->uid_;
		num_temp = it->num_;

		unsigned eqid = it->eqid;

		//兵书的数据表里的存放格式    "heaven":{"exp":3134,"lv":14}
		CLogicUser logicUser;
		DataUser dataUser;
		ret = logicUser.GetUser(uid_temp, dataUser);
		if(ret)
			return ret;
		Json::Value tech;
		Json::Reader reader;
		reader.parse(dataUser.user_tech, tech);

		unsigned now_exp = 0, now_lv = 0;
		unsigned b_exp = 0, b_lv = 0;

		if (HEAVEN_EQID == eqid)
		{
			Json::Value &heaven = tech["heaven"];

			//核心逻辑处理
			Json::GetUInt(heaven, "exp", now_exp);
			Json::GetUInt(heaven, "lv", now_lv);
			calcute_hevenDao(1, now_exp, num_temp, b_exp, b_lv);     // type:   0  遁甲,  1 天书
			heaven["exp"] = b_exp;
			heaven["lv"] = b_lv;
		}
		else if (DAO_EQID == eqid)
		{
			Json::Value &daoist = tech["daoist"];

			//核心逻辑处理
			Json::GetUInt(daoist, "exp", now_exp);
			Json::GetUInt(daoist, "lv", now_lv);
			calcute_hevenDao(0, now_exp, num_temp, b_exp, b_lv);     // type:   0  遁甲,  1 天书
			daoist["exp"] = b_exp;
			daoist["lv"] = b_lv;
		}
		else
		{
			continue;
		}

		Json::FastWriter writer;
		dataUser.user_tech = writer.write(tech);
		ret = logicUser.SetUser(uid_temp, dataUser);

		if (ret)
		{
			error_log("set user fail. uid=%u", uid_temp);
			return ret;
		}

		oper_log << uid_temp << " "
			 << eqid << " "
			 << num_temp << " "
			 << now_exp << " "
			 << now_lv << " "
			 << b_exp << " "
			 << b_lv << endl;
	}

	oper_log.close();

	cout << "ok" << endl;
}
