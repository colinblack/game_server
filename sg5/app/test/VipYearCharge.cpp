#include "LogicInc.h"
#include <iostream>
#include<math.h>

int main(int argc, char *argv[])
{
	if (!Kernel::Init(APP_CONFIG_PATH))
	{
		cout << "init kernel fail" << endl;
		return 1;
	}
	if (argc != 4) {
		cout << "usage: " << argv[0] << " [openid] [hero_total] [hero_used]" << endl;
		return 1;
	}

	Config::SetDomain(0);
	int semgroup = 0;
	int semserver = 0;
	Config::GetDB(semserver);
	unsigned updatetime = Time::GetGlobalTime();

	string openid = argv[1];
	int total = CTrans::STOI(argv[2]);
	int used = CTrans::STOI(argv[3]);

	int gettotal = 0;
	int getused = 0;
	CDataVipCharge charge;
	int getret = charge.GetBlueYearVipCharge(openid,gettotal,getused);

	if(8 == getret)
	{
		int ret = charge.AddBlueYearVipCharge(openid,total,used);
		if(ret != 0){
			cout<<"AddVipYearCharge error  ret="<<ret<<endl;
			return ret;
		}
	}
	else
	{
		int ret = charge.UpdateBlueYearVipChargeUsed(openid,total,used);
		if(ret != 0){
			cout<<"AddVipYearCharge error  ret="<<ret<<endl;
			return ret;
		}
	}

	int ret = charge.GetBlueYearVipCharge(openid,total,used);
	if(ret != 0){
		cout<<"GetVipYearCharge error  ret="<<ret<<endl;
		return ret;
	}

	cout<<openid<<"  total:"<<total<<" used:"<<used<<endl;


	cout << "ok" << endl;
	return 0;
}
