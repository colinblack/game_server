/*
 * VNPay.cpp
 *
 *  Created on: 2014-3-28
 *      Author: Ralf
 */

#include "LogicInc.h"
#include "LogicVNTelPay.h"
#include <iostream>

int main(int argc, char *argv[]) {
	if (!Kernel::Init(APP_CONFIG_PATH)) {
		cout << "Init kernel fail!" << endl;
		return -1;
	}

	Config::SetDomain(0);
	if (argc != 5) {
		error_log("[VNPay][para error]");
		return R_ERR_PARAM;
	}

	int ret;
	string openid(argv[1]);
	unsigned serverid = CTrans::STOI(argv[2]);
	int amt = CTrans::STOI(argv[3]);
	string pid(argv[4]);

	unsigned uid = 0;
	CDataUserMapping dbUserMapping;
	ret = dbUserMapping.GetUID(openid, serverid, uid);
	if( ret!=0 || uid == 0)
	{
		return R_ERR_DB;
		error_log("[VNPay][uid error]");
	}

	CLogicVNTelPay logicVNTelPay;
	ret = logicVNTelPay.deliver(uid,openid,pid,amt);
	if(ret)
		error_log("[VNPay][deliver error]");

	return 0;
}

