/*
 * CopyArchive.cpp
 *
 *  Created on: 2015-1-4
 *      Author: Ralf
 */


#include "LogicInc.h"

int main(int argc, char *argv[]) {
	if (!Kernel::Init(APP_CONFIG_PATH)) {
		cout << "Init kernel fail!" << endl;
		return -1;
	}
	Config::SetDomain(0);

	if (argc != 3) {
		cout << "usage: " << argv[0] << " uidfrom uidto " << endl;
		return 1;
	}
	unsigned uidfrom = atoi(argv[1]);
	if (!uidfrom) {
		cout << "uidfrom wrong!" << endl;
		return 1;
	}
	unsigned uidto = atoi(argv[2]);
	if (!uidto) {
		cout << "uidto wrong!" << endl;
		return 1;
	}
	int ret = 0;

	DataUserBasic userBasic;
	CLogicUserBasic logicUserBasic;
	ret = logicUserBasic.GetUserBasicLimit(uidto, PT_TEST, userBasic);
	if (ret != 0)
	{
		cout<<"get basic fail, ret="<<ret<<endl;
		return ret;
	}

	CLogicAdmin logicAdmin;
	Json::Value data;
	ret = logicAdmin.ExportArchive(uidfrom, data);
	if (ret != 0)
	{
		cout<<"export fail, ret="<<ret<<endl;
		return ret;
	}

	data["userid"] = uidto;

	ret = logicAdmin.ImportArchive(uidto, data);
	if (ret != 0) {
		cout << "import fail!" << endl;
		return ret;
	}

	CLogicUser logicUser;
	DataUser userfrom, userto;
	ret = logicUser.GetUserLimit(uidfrom, userfrom);
	ret += logicUser.GetUserLimit(uidto, userto);
	if(ret == 0)
	{
		userto.login_times = userfrom.login_times;
		userto.last_active_time = userfrom.last_active_time;
		userto.last_login_time = userfrom.last_login_time;
		userto.last_save_time = userfrom.last_save_time;
		ret = logicUser.SetUserLimit(uidto, userto);
		CDataUserMapping dbUserMapping;
		ret += dbUserMapping.SetLastLogin(userBasic.open_id, Config::GetZoneByUID(uidto), userfrom.last_login_time);
		if (ret != 0) {
			cout << "set lastlogin fail!" << endl;
			return ret;
		}
	}

	cout << "copy ok!" << endl;

	return 0;
}


