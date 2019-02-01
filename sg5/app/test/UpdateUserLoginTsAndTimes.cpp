/*
 * UpdateUserLoginTsAndTimes.cpp
 *
 *  Created on: 2016-7-12
 *      Author: zkw
 *      Purpose: spring stat need
 */


#include "LogicInc.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
	//需要输入的参数： file(uid), 登录时间， 登录次数， 人物等级，
	//注意更改  user_mapping的 lastlogin
	if(argc < 5)
	{
		cout<<"need uid_file ts times level"<<endl;
		return 1;
	}
	if (!Kernel::Init(APP_CONFIG_PATH))
	{
		cout << "init kernel fail" << endl;
		return 1;
	}

	int ret = 0;
	unsigned ts = atoi(argv[2]);
	unsigned login_times = atoi(argv[3]);
	unsigned level = atoi(argv[4]);
	ifstream fin(argv[1]);
	if (!fin.good())
	{
		cout<<"file error"<<endl;
		return 1;
	}
	vector<string> uid_vec;
	while (!fin.eof() && fin.good())
	{
		string temp;
		fin >> temp;
		uid_vec.push_back(temp);
	}

	CLogicUser logicUser;
	DataUser dataUser;
	CLogicUserBasic logicUserBasic;
	DataUserBasic  dataUserBasic;
	CDataUserMapping dataUserMapping;
	for(vector<string>::iterator it=uid_vec.begin();it!=uid_vec.end();++it)
	{
		unsigned now_uid = atoi((*it).c_str());
		ret = logicUser.GetUserLimit(now_uid, dataUser);
		if(ret)
			return ret;
		dataUser.last_login_time = dataUser.last_active_time = ts;
		dataUser.login_times = login_times;
		dataUser.level = level;
		ret = logicUser.SetUserLimit(now_uid, dataUser);
		if(ret)
			return ret;

		//更改user_mapping的lastlogin
		ret = logicUserBasic.GetUserBasicLimitWithoutPlatform(now_uid, dataUserBasic);
		if(ret)
			return ret;

		int now_serverid = 0;
		Config::GetDB(now_serverid);
		int ret = dataUserMapping.SetLastLogin(dataUserBasic.open_id, now_serverid,  ts);
		if(ret)
			return ret;

		++ts;
	}

	cout << "ok" << endl;
	return 0;
}


