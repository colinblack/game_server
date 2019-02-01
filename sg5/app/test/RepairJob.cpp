/*
 * RepairJob.cpp
 *
 *  Created on: 2014-6-25
 *      Author: Ralf
 */

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

	CDataUser db;
	fstream fin("jobuid2clean");
	if (!fin.good()) {
		cout << "open jobuid2clean fail" << endl;
		goto REPAIR;
	}
	while (!fin.eof() && fin.good()) {
		unsigned id = 0;
		fin >> id;
		db.SetStatus(id,Job_None);
	}
REPAIR:
	CLogicKingdom logicKingdom;
	logicKingdom.RepairKingdom();

	return 0;
}






