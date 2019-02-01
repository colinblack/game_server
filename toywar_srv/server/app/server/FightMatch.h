#ifndef FIGHTMATCH_H_
#define FIGHTMATCH_H_
#include "Kernel.h"
struct WaitMatchGroup{
	int GroupId;
	unsigned JoinTime;
	int FightNum;
	bool IsMatched;
};

class FightMatch{
public:
	FightMatch();
	virtual ~FightMatch();
	int MatchAll(map<int,int> &matchGroup);
	void RemoveHaveMatchGroup(int GroupId);
	void AddWaitMatchGroup(int groupId,int fightNum);
	double Match(WaitMatchGroup group1,WaitMatchGroup group2);
	map<int,WaitMatchGroup> GetWaitGroup();
private:
	map<int,WaitMatchGroup> m_waitmatchgroups;
};
#endif
