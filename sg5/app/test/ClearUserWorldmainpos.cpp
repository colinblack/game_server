#include "LogicInc.h"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{
	if (!Kernel::Init(APP_CONFIG_PATH))
	{
		cout << "Init kernel fail!" << endl;
		return -1;
	}
	Config::SetDomain(0);
	if (argc < 2)
	{
		cout << "require ./ClearUserWorldmainpos yes! to confirm you really wanna clear db world & kingdom info!" << endl;
		return 1;
	}

USER_MAIN_POS:
{
	CLogicUser logicUser;
	ifstream fin("mainpos.tmp");
	if (!fin.good()) {
		cout << "open mainpos.tmp fail" << endl;
		goto KINGDOM;
	}
	while (!fin.eof() && fin.good()) {
		unsigned uid = 0;
		fin >> uid;
		logicUser.SetMainpos(uid,0);
	}
	system("rm mainpos.tmp -f");
}
KINGDOM:
{
	CLogicKingdom logicKingdom;
	logicKingdom.CleanKingdom();
}
	return 0;
}



