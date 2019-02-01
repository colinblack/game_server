/*
 * DataAllServerNewWorldBattle.cpp
 *
 *  Created on: 2015-2-12
 *      Author: Ralf
 */

#include "DataAllServerNewWorldBattle.h"


CDataAllServerNewWorldBattle::CDataAllServerNewWorldBattle() {
	m_init = false;
}
CDataAllServerNewWorldBattle:: ~CDataAllServerNewWorldBattle(){

}

int CDataAllServerNewWorldBattle::Init(const string &path, semdat sem) {
	if (m_init) {
		return 0;
	}

	int semgroup = 0;
	int semserver = 0;
	Config::GetDomain(semserver);
	if(!semserver)
		Config::GetDB(semserver);
	if (!m_sh.CreateOrOpen(path.c_str(), sizeof(DataAllServerNewWorldBattle),
			SEM_ID(sem,semgroup,semserver))) {
		error_log("[init_consume_rank_data_fail][path=%s]", path.c_str());
		return R_ERROR;
	}
	CAutoLock lock(&m_sh, true);
	if (!m_sh.HasInit()) {
		DataAllServerNewWorldBattle *pTable = (DataAllServerNewWorldBattle *) m_sh.GetAddress();
		memset(pTable, 0, sizeof(*pTable));
		m_sh.SetInitDone();
	}
	m_init = true;
	return 0;
}

int CDataAllServerNewWorldBattle::GetList(vector<NewWorldBattleServer> &domain)
{
	DataAllServerNewWorldBattle *pTable = (DataAllServerNewWorldBattle *) m_sh.GetAddress();
	if (pTable == NULL)
	{
		error_log("[GetList_fail]");
		return R_ERR_DB;
	}

	CAutoLock lock(&m_sh, true);

	for(int i=0;i<ALL_SERVER_NEW_WORLD_BATTLE_NUM;++i)
	{
		if(pTable->server[i].serverid == 0)
			break;
		domain.push_back(pTable->server[i]);
	}

	return 0;
}

int CDataAllServerNewWorldBattle::SetAttack(unsigned attack, unsigned kingdom, unsigned defend, vector<NewWorldBattleServer> &domain)
{
	if(kingdom > 3 || kingdom < 1)
		return R_ERR_PARAM;

	unsigned now = Time::GetGlobalTime();
	if(CTime::FormatTime("%a", now) == "Fri")
	{
		LOGIC_ERROR_RETURN_MSG("newworldbattle_signup_error");
	}

	DataAllServerNewWorldBattle *pTable = (DataAllServerNewWorldBattle *) m_sh.GetAddress();
	if (pTable == NULL) {
		error_log("[SetUser_fail]");
		return R_ERR_DB;
	}

	CAutoLock lock(&m_sh, true);

	unsigned sum[3] = {0, 0, 0};
	unsigned self = 0;
	int ret = 0;
	for(int i=0;i<ALL_SERVER_NEW_WORLD_BATTLE_NUM;++i)
	{
		if(pTable->server[i].serverid == 0)
			break;

		if(pTable->server[i].serverid == attack)
		{
			if(pTable->server[i].defendServer)
			{
				ret = checkSignUpTime(pTable->server[i].defendTS);
				if (ret)
					return ret;
			}
			if(pTable->server[i].kingdom[kingdom-1].attackServer)
			{
				ret = checkSignUpTime(pTable->server[i].kingdom[kingdom-1].attackTS);
				if(ret)
					return ret;
			}

			self += pTable->server[i].kingdom[kingdom-1].army;
		}
		else if(pTable->server[i].serverid == defend)
		{
			if(pTable->server[i].defendServer)
			{
				ret = checkSignUpTime(pTable->server[i].defendTS);
				if(ret)
					return ret;
			}

			for(int j=0;j<3;++j)
			{
				if(pTable->server[i].kingdom[j].attackServer)
				{
					ret = checkSignUpTime(pTable->server[i].kingdom[j].attackTS);
					if(ret)
						return ret;
				}

				sum[j] += pTable->server[i].kingdom[j].army;
			}
		}
	}

	for(int j=0;j<3;++j)
	{
		if(self <= sum[j])
		{
			LOGIC_ERROR_RETURN_MSG("newworldbattle_signup_error");
		}
	}

	for(int i=0;i<ALL_SERVER_NEW_WORLD_BATTLE_NUM;++i)
	{
		if(pTable->server[i].serverid == 0)
			break;

		if(pTable->server[i].serverid == attack)
		{
			pTable->server[i].kingdom[kingdom-1].attackServer = defend;
			pTable->server[i].kingdom[kingdom-1].attackTS = now;
			pTable->server[i].kingdom[kingdom-1].result = e_NewWorldBattleResult_get_ready;

		}
		else if(pTable->server[i].serverid == defend)
		{
			pTable->server[i].defendServer = attack;
			pTable->server[i].defendKingdom = kingdom;
			pTable->server[i].defendTS = now;
			pTable->server[i].result = e_NewWorldBattleResult_get_ready;
		}

		domain.push_back(pTable->server[i]);
	}

	return 0;
}

int CDataAllServerNewWorldBattle::SetArmy(unsigned serverid, unsigned domain, unsigned army[3], string& host)
{
	if(!serverid || !domain)
		return R_ERR_PARAM;

	DataAllServerNewWorldBattle *pTable = (DataAllServerNewWorldBattle *) m_sh.GetAddress();
	if (pTable == NULL) {
		error_log("[SetUser_fail]");
		return R_ERR_DB;
	}

	CAutoLock lock(&m_sh, true);

	for(int i=0;i<ALL_SERVER_NEW_WORLD_BATTLE_NUM;++i)
	{
		if(pTable->server[i].domain == domain || pTable->server[i].serverid == 0)
		{
			pTable->server[i].serverid = serverid;
			pTable->server[i].domain = domain;
			strcpy(pTable->server[i].host, host.c_str());
			for(int j=0;j<3;++j)
				pTable->server[i].kingdom[j].army = army[j];
			break;
		}
	}

	return 0;
}
int CDataAllServerNewWorldBattle::SetResult(unsigned defend, unsigned result)
{
	DataAllServerNewWorldBattle *pTable = (DataAllServerNewWorldBattle *) m_sh.GetAddress();
	if (pTable == NULL) {
		error_log("[SetUser_fail]");
		return R_ERR_DB;
	}

	CAutoLock lock(&m_sh, true);

	int ret = 0;
	for(int i=0;i<ALL_SERVER_NEW_WORLD_BATTLE_NUM;++i)
	{
		if(pTable->server[i].serverid == 0)
			break;

		if(pTable->server[i].serverid == defend
		&& pTable->server[i].defendServer)
		{
			ret = checkResultTime(pTable->server[i].defendTS);
			if (!ret)
				pTable->server[i].result = result;
		}
		else
		{
			for(int j=0;j<3;++j)
			{
				if(pTable->server[i].kingdom[j].attackServer == defend)
				{
					ret = checkResultTime(pTable->server[i].kingdom[j].attackTS);
					if (!ret)
						pTable->server[i].kingdom[j].result = result;
				}

			}
		}
	}

	return 0;
}

int CDataAllServerNewWorldBattle::checkSignUpTime(unsigned ts)
{
	if (ts == 0)
		return 0;

	unsigned now = Time::GetGlobalTime();
	if(now < ts || CTime::FormatTime("%a", now) == "Fri")
	{
		LOGIC_ERROR_RETURN_MSG("newworldbattle_signup_error");
	}

	unsigned battleFri = 0;
	getBattleFri(ts, battleFri);

	if (now < battleFri)
	{
		LOGIC_ERROR_RETURN_MSG("newworldbattle_signup_error");
	}

	return 0;
}

int CDataAllServerNewWorldBattle::checkResultTime(unsigned ts)
{
	if (ts == 0)
		return -1;

	unsigned battleFri = 0;
	getBattleFri(ts, battleFri);

	unsigned now = Time::GetGlobalTime();

	if (CTime::GetDayInterval(battleFri, now)==0)
		return 0;

	return -1;
}

void CDataAllServerNewWorldBattle::getBattleFri(const unsigned ts, unsigned &battleFri)
{
	if(CTime::FormatTime("%a", ts) == "Sat")
	{
		battleFri = CTime::GetDayBeginTime(ts) - CTime::SECONDS_OF_DAY + CTime::SECONDS_OF_WEEK;
	}
	else if(CTime::FormatTime("%a", ts) == "Sun")
	{
		battleFri = CTime::GetDayBeginTime(ts) - 2*CTime::SECONDS_OF_DAY + CTime::SECONDS_OF_WEEK;
	}
	else
	{
		// week begin on Monday
		battleFri = CTime::GetWeekBeginTime(ts) + 4*CTime::SECONDS_OF_DAY;
	}
}
