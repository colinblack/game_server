/*
 * BlockUser.cpp
 *
 *  Created on: 2014-6-20
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

	if (argc != 4)
	{
		cout << "usage: " << argv[0] << " [uid] [block ts] [reason]" << endl;
		return 1;
	}
	unsigned uid = atoi(argv[1]);
	unsigned ts = atoi(argv[2]);
	string r = argv[3];

	CLogicAdmin logicAdmin;
	int ret = logicAdmin.ChangeBlockTs(uid, ts, r);
	if(ret == 0)
		cout<<"ok"<<endl;
	else
		cout<<"ret="<<ret<<endl;

	vector<DataEmail> vEmail;
	vector<DataEmail>::iterator it ;
	CLogicEmail logicEmail;
	CDataEmail dbEmail;
	ret = logicEmail.GetOutboxEmailList(uid, vEmail);
	if(ret)
		return ret;
	it = vEmail.begin();
	for(;it != vEmail.end();it++)
		dbEmail.DeleteEmailFrom((*it).opposite_uid, (*it).uid);

	return 0;
}



