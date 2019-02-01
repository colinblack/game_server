/*
 * DataAllServerNewWorldBattle.h
 *
 *  Created on: 2015-2-12
 *      Author: Ralf
 */

#ifndef DATAALLSERVERNEWWORLDBATTLE_H_
#define DATAALLSERVERNEWWORLDBATTLE_H_

#include "Kernel.h"

#define ALL_SERVER_NEW_WORLD_BATTLE_NUM 4000

enum NewWorldBattleResult
{
	e_NewWorldBattleResult_get_ready	= 0,
	e_NewWorldBattleResult_time_over 	= 1,
	e_NewWorldBattleResult_defend_win 	= 2,
	e_NewWorldBattleResult_attack_win 	= 3,
};

struct NewWorldBattleKingdom
{
	unsigned attackTS, army, attackServer, result;
	NewWorldBattleKingdom()
	{
		attackTS = army = attackServer = result = 0;
	}
};

struct NewWorldBattleServer
{
	unsigned serverid, domain, defendTS, defendServer, defendKingdom, result;
	char host[128];
	NewWorldBattleKingdom kingdom[3];
	NewWorldBattleServer()
	{
		serverid = domain = defendTS = defendServer = defendKingdom = result = 0;
		memset(host, 0, sizeof(host));
	}
};

struct DataAllServerNewWorldBattle
{
	NewWorldBattleServer server[ALL_SERVER_NEW_WORLD_BATTLE_NUM];
};

class CDataAllServerNewWorldBattle
{
public:
	CDataAllServerNewWorldBattle();
	virtual ~CDataAllServerNewWorldBattle();
	int Init(const std::string &path, semdat sem=sem_all_server_new_world_battle);
	int GetList(vector<NewWorldBattleServer> &domain);
	int SetAttack(unsigned attack, unsigned kingdom, unsigned defend, vector<NewWorldBattleServer> &domain);
	int SetArmy(unsigned serverid, unsigned domain, unsigned army[3], string& host);
	int SetResult(unsigned defend, unsigned result);

protected:
	bool m_init;
	CShareMemory m_sh;

private:
	int checkSignUpTime(unsigned ts);
	int checkResultTime(unsigned ts);
	void getBattleFri(const unsigned ts, unsigned &battleFri);
};


#endif /* DATAALLSERVERNEWWORLDBATTLE_H_ */
