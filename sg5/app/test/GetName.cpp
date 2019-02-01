/*
 * GetName.cpp
 *
 *  Created on: 2014-4-3
 *      Author: Ralf
 */
#include "LogicInc.h"

int main(int argc, char* argv[])
{
	if (!Kernel::Init(APP_CONFIG_PATH))
	{
		cout << "init kernel fail" << endl;
		return 1;
	}
	Config::SetDomain(0);

	if (argc != 2)
	{
		cout << "usage: " << argv[0] << " [uid]" << endl;
		return 1;
	}
	unsigned uid = atoi(argv[1]);
	DataUserBasic userBasic;

	CLogicUserBasic logicUserBasic;
	int ret = logicUserBasic.GetUserBasicLimit(uid, PT_TEST, userBasic);
	CLogicUser logicUser;
	DataUser user;
	ret += logicUser.GetUserLimit(uid, user);
	CLogicPay logicPay;
	DataPay pay;
	ret += logicPay.GetPay(uid, pay);
	if (ret == 0)
		cout<<uid<<"|"
			<<Config::GetZoneByUID(uid)<<"|"
			<<userBasic.open_id<<"|"
			<<userBasic.name<<"|"
			<<user.level<<"|"
			<<user.accCharge<<"|"
			<<pay.cash<<"|"
			<<pay.coins<<"|"
			<<user.alliance_id<<"|"
			<<user.register_time<<"|"
			<<user.last_login_time
			<<endl;
	else
		cout<<"ret="<<ret<<endl;

	return 0;
}
