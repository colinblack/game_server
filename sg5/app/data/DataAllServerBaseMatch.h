#ifndef _DATA_ALL_SERVER_BASEMATCH_H_
#define _DATA_ALL_SERVER_BASEMATCH_H_

#include "Kernel.h"

#define ALL_SERVER_BASEMATCH_TEAMS_MAX 50000

struct AllServerBaseMatchData
{
	unsigned instance_ndx;
	char stage;					//0:报名阶段,1:常规赛,2:季后赛
	unsigned numOfApply;		//报名的联盟数量
	BaseMatchTeam teams[ALL_SERVER_BASEMATCH_TEAMS_MAX];	//已报名的队
	unsigned numOfReg;			//常规赛联盟数
	BaseMatchRegularTeam rteams[ALL_SERVER_BASEMATCH_TEAMS_MAX];
	BaseMatchPlayoffTeam top8[8];
	BaseMatchPlayoffTeam top4[4];
	BaseMatchPlayoffTeam top2[2];
	BaseMatchPlayoffTeam champion;
};


class CDataAllServerBaseMatch
{
public:
	CDataAllServerBaseMatch();
	int Init(const string &path, semdat sem=sem_basematch);
	int View(unsigned aid, unsigned uid, int &stage, BaseMatchTeam &team, BaseMatchRegularRival &rival,
			vector<BaseMatchPlayoffTeam> &playoff);
	int Apply(unsigned aid, const string &aname, int flag, unsigned uid, const string &name, unsigned &instanceid,bool allserver=false);
	int ReportResult(unsigned uid, int order, int damage);
	int StartRegular();
	int StartGuess(bool allserver=false);
	int StartPlayoff8();
	int StartPlayoff4(bool allserver=false);
	int StartPlayoff2(bool allserver=false);
	int FinishMatch(const AllServerBaseMatchData **p,bool allserver=false);
	int NextTurn();
	int IsBaseMatchProtect(unsigned aid, unsigned uid, bool &prot);

	int GetApplyPlayersOfTeam(unsigned aid, vector<BaseMatchPlayer> &players);
	int GetRegularScore(unsigned aid, unsigned &damage, unsigned &rank, vector<BaseMatchRegularRival> &players);

	int ResetInsts();
	int GetStage(int& stage);

	AllServerBaseMatchData * GetMatchData();

protected:
	CShareMemory m_sh;
	bool m_init;
};

#endif
