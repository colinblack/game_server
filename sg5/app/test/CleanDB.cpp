/*
 * CleanDB.cpp
 *
 *  Created on: 2014-5-23
 *      Author: Ralf
 */

#include "LogicInc.h"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
	if (!Kernel::Init(APP_CONFIG_PATH)) {
		cout << "init kernel fail" << endl;
		return -1;
	}
	Config::SetDomain(0);

	if (argc < 2) {
			cout << "usage: " << argv[0] << "ts" << endl;
			return 1;
		}
	int ts = CTrans::STOI(argv[1]);

USER_ATTACK:
{
	CDataUserAttack db;
	ifstream fin("attackuid2clean");
	if (!fin.good()) {
		cout << "open attackuid2clean fail" << endl;
		goto ATTACK;
	}
	while (!fin.eof() && fin.good()) {
		unsigned id = 0;
		fin >> id;
		db.DelUserAttacksBeforeTS(id,ts);
	}
}
ATTACK:
{
	CDataAttack db;
	ifstream fin("attack2clean");
	if (!fin.good()) {
		cout << "open attack2clean fail" << endl;
		goto EMAIL;
	}
	while (!fin.eof() && fin.good()) {
		unsigned long long id = 0;
		fin >> id;
		db.DelAttack(id);
	}
}
EMAIL:
{
	CDataEmail db;
	ifstream fin("email2clean");
	if (!fin.good()) {
		cout << "open email2clean fail" << endl;
		goto UPDATES;
	}
	while (!fin.eof() && fin.good()) {
		unsigned id = 0;
		fin >> id;
		db.DeleteEmailBeforeTs(id, ts);
	}
}
UPDATES:
{
	CDataUpdates db;
	ifstream fin("updates2clean");
	if (!fin.good()) {
		cout << "open updates2clean fail" << endl;
		goto ALLIANCE_MESSAGE;
	}
	while (!fin.eof() && fin.good()) {
		unsigned id = 0;
		fin >> id;
		db.RemoveUpdatesBeforeTs(id, ts);
	}
}
ALLIANCE_MESSAGE:
{
	CDataAllianceMessage db;
	ifstream fin("alliancemessage2clean");
	if (!fin.good()) {
		cout << "open alliancemessage2clean fail" << endl;
		goto USER_MESSAGE;
	}
	while (!fin.eof() && fin.good()) {
		unsigned id = 0;
		fin >> id;
		db.DelAllianceMessageBeforeTS(id, ts);
	}
}
USER_MESSAGE:
{
	CDataUserMessage db;
	ifstream fin("usermessage2clean");
	if (!fin.good()) {
		cout << "open usermessage2clean fail" << endl;
		goto MESSAGE;
	}
	while (!fin.eof() && fin.good()) {
		unsigned id = 0;
		fin >> id;
		db.DelUserMessageBeforeTS(id, ts);
	}
}
MESSAGE:
{
	CDataMessage db;
	ifstream fin("message2clean");
	if (!fin.good()) {
		cout << "open message2clean fail" << endl;
		goto HELP_HISTORY;
	}
	while (!fin.eof() && fin.good()) {
		unsigned long long id = 0;
		fin >> id;
		db.RemoveMessage(id);
	}
}
HELP_HISTORY:
{
	CDataHelpHist db;
	ifstream fin("helphistory2clean");
	if (!fin.good()) {
		cout << "open helphistory2clean fail" << endl;
		goto ALLIANCE_INTERACT;
	}
	while (!fin.eof() && fin.good()) {
		unsigned id = 0;
		fin >> id;
		db.RemoveHelpHistBeforeTs(id, ts);
	}
}
ALLIANCE_INTERACT:
{
	CDataAllianceInteract db;
	ifstream fin("allianceinteract2clean");
	if (!fin.good()) {
		cout << "open allianceinteract2clean fail" << endl;
		goto USER_INTERACT;
	}
	while (!fin.eof() && fin.good()) {
		unsigned id = 0;
		fin >> id;
		db.DelAllianceInteractsBeforeTS(id, ts);
	}
}
USER_INTERACT:
{
	CDataUserInteract db;
	ifstream fin("userinteract2clean");
	if (!fin.good()) {
		cout << "open userinteract2clean fail" << endl;
		goto END;
	}
	while (!fin.eof() && fin.good()) {
		unsigned id = 0;
		fin >> id;
		db.DelUserInteractsBeforeTS(id, ts);
	}
}
END:
	return 0;
}



