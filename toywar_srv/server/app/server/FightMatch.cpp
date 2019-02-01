#include "FightMatch.h"


FightMatch::FightMatch(){};
FightMatch::~FightMatch(){};
int FightMatch::MatchAll(map<int,int> &matchGroup ){
	int ret = m_waitmatchgroups.size();
	if(m_waitmatchgroups.size()<2)
	{
		return -1;
	}
	for(map<int,WaitMatchGroup>::iterator m1_Iter = m_waitmatchgroups.begin(); m1_Iter != m_waitmatchgroups.end( ); m1_Iter++)
	{
		int matchId = 0;
		double matchdegree = 0;
		WaitMatchGroup matchgroup1 = m1_Iter -> second;
		if(m1_Iter->second.IsMatched)
		{
			continue;
		}
		for(map<int,WaitMatchGroup>::iterator m2_Iter = ++m1_Iter; m2_Iter != m_waitmatchgroups.end(); m2_Iter++)
		{
			if(m2_Iter->second.IsMatched)
			{
				continue;
			}
			WaitMatchGroup matchgroup2 = m2_Iter -> second;
			double degree = Match(matchgroup1,matchgroup2);
			if(degree > matchdegree){
				matchdegree = degree;
				matchId = m2_Iter->first;
			}
		}
		--m1_Iter;
		if(matchId !=0)
		{
			m_waitmatchgroups[matchId].IsMatched = true;
			m1_Iter->second.IsMatched = true;
			matchGroup.insert(pair<int,int>(m1_Iter->first,matchId));
		}
	}
	fatal_log("Matchsuccess=%d",matchGroup.size());
	return ret;
}

void FightMatch::RemoveHaveMatchGroup(int groupId){
	map<int ,WaitMatchGroup >::iterator l_it =m_waitmatchgroups.find(groupId);
	if(l_it != m_waitmatchgroups.end() )
	{
		m_waitmatchgroups.erase(l_it);
	}
}

void FightMatch::AddWaitMatchGroup(int groupId,int fightNum){
	WaitMatchGroup waitMatchGroup;
	waitMatchGroup.GroupId = groupId;
	waitMatchGroup.FightNum = fightNum;
	waitMatchGroup.JoinTime = Time::GetGlobalTime();
	waitMatchGroup.IsMatched = false;
	fatal_log("groupid=%d , fightnum=%d ,jointime = %d ,ismatch=%d",groupId,waitMatchGroup.FightNum,waitMatchGroup.JoinTime,waitMatchGroup.IsMatched);
	m_waitmatchgroups.insert(pair<int, WaitMatchGroup> (groupId, waitMatchGroup));
}

double FightMatch::Match(WaitMatchGroup group1,WaitMatchGroup group2){
	if(group1.GroupId == group2.GroupId)
	{
		return false;
	}
	double degree =100 * (group1.FightNum < group2.FightNum?group1.FightNum : group2.FightNum) /(group1.FightNum > group2.FightNum?group1.FightNum : group2.FightNum);
	unsigned now = Time::GetGlobalTime();
	unsigned dtime = now -( group1.JoinTime>group2.JoinTime ? group1.JoinTime : group2.JoinTime);
	int per = 90 - 3*( dtime>10 ? dtime-10 : 0)  ;
	return degree > per ? degree : 0 ;
}
map<int,WaitMatchGroup> FightMatch::GetWaitGroup(){
	return m_waitmatchgroups;
}
