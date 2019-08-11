
#ifndef TEAMMANAGER_H_
#define TEAMMANAGER_H_
#include "BattleBaseInc.h"
#include "MapManager.h"
struct Team{
	Identity team;
	Identity leader;
	Identity target;
	uint32_t leaderId;
	string teamName;
	vector<uint32_t> targetList;
	vector<Identity> mems;
	map<uint32_t,uint32_t> entityShows;
	uint32_t copyId;
	uint32_t needLevel;

};



class TeamManager: public CSingleton<TeamManager> {
private:
	friend class CSingleton<TeamManager>;
	TeamManager();
	~TeamManager();
public:
//	bool init();
//	bool onLogin();
//	bool onOffline();
//	void onSecondTimer();
//	bool isInTeam();
	bool sendTeamInfo();



	//queryList




public:
	int Process(uint32_t uid, team::CSCreateTeam *req);
	int Process(uint32_t uid, team::CSLeaveTeam *req);

	int Process(uint32_t uid, team::CSDisBandTeam *req);

	int Process(uint32_t uid, team::CSCheckMemCopy *req, team::SCCheckMemCopyResponse* resp);


	bool doLeaveTeam(uint32_t uid);

	bool sendTeamInfo(uint32_t uid);
	bool sendTeamList(uint32_t uid);
private:
	uint32_t m_max_id;
	map<uint32_t,Team> m_teams;						//teamId -team


	map<uint32_t, uint32_t> m_uid_teams;			//uid-teamId

};


#endif /* TEAMMANAGER_H_ */
