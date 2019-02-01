#include "LogicInc.h"

int main(int argc, char *argv[]) {
	if (!Kernel::Init(APP_CONFIG_PATH)) {
		cout << "Init kernel fail!" << endl;
		return -1;
	}
	Config::SetDomain(0);

	if (argc != 3) {
		cout << "usage: " << argv[0] << "serverfrom serverto " << endl;
		return 1;
	}
	int serverfrom = atoi(argv[1]);
	int serverto = atoi(argv[2]);
	if (serverfrom<0 || serverto<0 || serverfrom>serverto) {
		cout << "server wrong!" << endl;
		return 1;
	}

	int ret;
	for(int i=serverfrom-1;i<serverto;++i)
	{
		uint64_t uidEnd;
		unsigned userid = Config::GetUIDStart(i+1);
		CLogicIdCtrl logicIdCtrl;
		ret = logicIdCtrl.GetCurrentId(KEY_UID_CTRL, uidEnd,i+1);
		if(ret != 0)
		{
			error_log("get current user id fail! from RepairArchive ---start!");
			return ret;
		}
		for(;userid <= (unsigned)uidEnd;++userid)
		{
			CDataUser dbUser;
			DataUser user;
			ret = dbUser.GetUser(userid, user);
			if(ret == 0 && dbUser._check_user_stat(user) == 0)
				dbUser.SetUser(userid,user);
		}
	}
	cout<<"ok"<<endl;

	return 0;
}
