#include "LogicInc.h"
#include <iostream>


int AddLonglin(unsigned uid,unsigned longlin)
{

	int ret = 0;
	Json::FastWriter writer;
	Json::Reader reader;
	CLogicUser LogicUser;
	DataUser user;
	ret = LogicUser.GetUser(uid, user);
	if (ret != 0 )
	{
		error_log("[GetUser fail][uid=%u,ret=%d]",uid,ret);
		DB_ERROR_RETURN_MSG("get_User_fail");
	}

	Json::Value user_tech;
	user_tech.clear();
	reader.parse(user.user_tech,user_tech);

	if(!user_tech.isMember("yinliang"))
	{
		user_tech["yinliang"] = longlin;
	}
	else
	{
		int total_longlin = user_tech["yinliang"].asInt() + longlin;
		user_tech["yinliang"] = total_longlin;
	}

	user.user_tech = writer.write(user_tech);
	ret = LogicUser.SetUser(uid,user);
	if (ret != 0)
	{
		error_log("[setuser fail][uid=%u,ret=%d]",uid,ret);
		DB_ERROR_RETURN_MSG("db_set_user_fail");
	}
	return 0;
}


int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cout << "usage: " << argv[0] << " [uid]" <<" [longlin]"<< endl;
		return 1;
	}

	Kernel::Init(APP_CONFIG_PATH);
	Config::SetDomain(0);

	unsigned uid = CTrans::STOI(argv[1]);
	unsigned longlin = CTrans::STOI(argv[2]);
	if (!IsValidUid(uid))
	{
		cout << "invalid uid" << endl;
		return 2;
	}

	int ret = AddLonglin(uid,longlin);
	if (ret != 0)
	{
		cout << "add longlin failed" << endl;
		return 3;
	}

	cout << "ok" << endl;
	return 0;
}
