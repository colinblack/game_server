/*
 * AddUser.cpp
 *
 *  Created on: 2017-1-4
 *      Author: Ralf
 */


#include "LogicInc.h"

int main(int argc, char *argv[])
{
	if (!Kernel::Init(APP_CONFIG_PATH))
	{
		cout<<"null"<<endl;
		return 1;
	}
	Config::SetDomain(0);

	if(argc < 2)
	{
		cout<<"null"<<endl;
		return 1;
	}
	string openid = argv[1];

	OPUserInfo userinfo;
	userinfo.OpenId = openid;
	string iopenid, via;
	unsigned uid = 0;
	bool isNewUser = false;
	CLogicUserMapping LogicUserMapping;
	int ret = LogicUserMapping.LoginPlatformUser(PT_TEST, userinfo, iopenid, uid,isNewUser,via);
	if(ret || !isNewUser)
	{
		cout<<"null"<<endl;
		return ret;
	}

	cout<<uid<<endl;

	return 0;
}




