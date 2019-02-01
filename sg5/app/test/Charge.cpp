#include "LogicInc.h"
#include <iostream>

int main(int argc, char *argv[])
{
	Kernel::Init(APP_CONFIG_PATH);
	Config::SetDomain(0);

	if (argc != 4)
	{
		cout << "usage: " << argv[0] << " uid cash coin" << endl;
		return 1;
	}
	unsigned uid = CTrans::STOI(argv[1]);
	int cash = CTrans::STOI(argv[2]);
	int coin = CTrans::STOI(argv[3]);
	DataPay pay;
	CLogicPay logicPay;
	Json::Value user_flag;
	CLogicUser logicUser;
	bool save = false;
	int ret = logicUser.GetUserFlag(uid,user_flag);
	if(!ret)
		ret = logicPay.ChangePay(uid, cash, coin , pay, "ADMINOP", user_flag, save, PAY_FLAG_CHARGE|PAY_FLAG_COST_ALL|PAY_FLAG_NO_REPLY);
	if(!ret && save)
		ret = logicUser.SetUserFlag(uid,user_flag);
	cout << "ret="<<ret<< endl;
	return 0;
}
