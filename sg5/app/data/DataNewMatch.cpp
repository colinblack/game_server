/*
 * DataNewMatch.cpp
 *
 *  Created on: 2015-10-23
 *      Author: Ralf
 */

#include "DataNewMatch.h"
#include "DataNewWorld.h"
#include "LogicNewMatch.h"

static bool NewMatchUserCompare(const NewMatchUser &left, const NewMatchUser &right)
{
	return left.score > right.score;
}

const int NEW_MATCH_NPC_POWER[DATA_NEW_MATCH_REGULAR] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 40, 90, 150, 210, 270};
const int NEW_MATCH_NPC_JOB[DATA_NEW_MATCH_REGULAR][DATA_NEW_MATCH_HERO] = {
		{3,2,1,1,2},
		{3,2,1,2,1},
		{2,3,3,3,1},
		{3,3,2,1,2},
		{3,2,2,3,1},
		{2,3,2,3,1},
		{3,1,2,1,2},
		{3,2,1,3,1},
		{3,2,1,1,2},
		{3,2,1,1,2},
		{3,1,2,1,2},
		{3,2,1,2,1},
		{3,1,2,1,2},
		{3,1,1,2,2},
		{3,1,1,2,2},
};

CDataNewMatch::CDataNewMatch(string path)
	: DataBase(path)
{
	m_msg = new ProtoNewMatch::ProtoNewMatch();
}

int CDataNewMatch::Init()
{
	int ret = Parse();
	if(ret)
		return ret;

	m_data.parse((ProtoNewMatch::ProtoNewMatch *)m_msg);

	((ProtoNewMatch::ProtoNewMatch *)m_msg)->Clear();

	return 0;
}

int CDataNewMatch::Save()
{
	m_data.serialize((ProtoNewMatch::ProtoNewMatch *)m_msg);

	int ret = Serialize();
	if(ret)
		return ret;

	((ProtoNewMatch::ProtoNewMatch *)m_msg)->Clear();

	return 0;
}

int CDataNewMatch::Sig(int sig)
{
	if(sig == SIGRTMIN)
		Restart();
	else if(sig == SIGRTMIN + 1)
		Regular();
	else if(sig == SIGRTMIN + 2)
		Top8();
	else if(sig == SIGRTMIN + 3)
		Top4();
	else if(sig == SIGRTMIN + 4)
		Top2();

	return 0;
}

int CDataNewMatch::Apply(NewMatchUser& user)
{
	if(m_data.user.count(user.uid))
		return R_ERR_LOGIC;

	if(m_data.stage != e_NewMatchStage_apply_regular)
		return R_ERR_LOGIC;

	user.Recover();
	m_data.user[user.uid] = user;

	return 0;
}

int CDataNewMatch::ChangeIndex(unsigned uid, unsigned index[DATA_NEW_MATCH_HERO])
{
	if(m_data.stage == e_NewMatchStage_apply_regular)
	{
		if(m_data.user.count(uid))
		{
			m_data.user[uid].ChangeIndex(index);
			return 0;
		}
	}
	else if(m_data.stage == e_NewMatchStage_guess_top8)
	{
		for(unsigned i=0;i<8;++i)
		{
			if(m_data.top8[i].uid == uid)
			{
				m_data.top8[i].ChangeIndex(index);
				return 0;
			}
		}
	}
	else if(m_data.stage == e_NewMatchStage_guess_top4)
	{
		for(unsigned i=0;i<4;++i)
		{
			if(m_data.top4[i].uid == uid)
			{
				m_data.top4[i].ChangeIndex(index);
				return 0;
			}
		}
	}
	else if(m_data.stage == e_NewMatchStage_guess_top2)
	{
		for(unsigned i=0;i<2;++i)
		{
			if(m_data.top2[i].uid == uid)
			{
				m_data.top2[i].ChangeIndex(index);
				return 0;
			}
		}
	}

	return R_ERR_LOGIC;
}

int CDataNewMatch::Fight(unsigned uid, NewMatchUser user[2])
{
	if(m_data.stage != e_NewMatchStage_apply_regular)
		return R_ERR_LOGIC;

	if(!m_data.user.count(uid))
		return R_ERR_LOGIC;

	if(m_data.user[uid].turn >= DATA_NEW_MATCH_REGULAR)
		return R_ERR_LOGIC;

	unsigned win = 0;
	for(unsigned j=0;j<DATA_NEW_MATCH_HERO;++j)
	{
		if(!m_data.user[uid].hero[j].dead())
			++win;
	}
	if(win < DATA_NEW_MATCH_HERO/2 + 1)
		return R_ERR_LOGIC;

	NewMatchUser npc;
	makeNPC(m_data.user[uid].turn, npc);
	m_data.user[uid].Recover();
	for(unsigned j=0;j<DATA_NEW_MATCH_HERO;++j)
		CDataBattleRoom::attacking(m_data.user[uid].hero[m_data.user[uid].index[j]], npc.hero[npc.index[j]]);

	win = 0;
	for(unsigned j=0;j<DATA_NEW_MATCH_HERO;++j)
	{
		if(!m_data.user[uid].hero[j].dead())
			++win;
	}
	m_data.user[uid].score += win;
	if(win >= DATA_NEW_MATCH_HERO/2 + 1)
		++m_data.user[uid].turn;

	if(win)
	{
		bool change = false, add = false;
		for(unsigned i=0;i<DATA_NEW_MATCH_RANK;++i)
		{
			if(m_data.rank[i].uid == uid)
			{
				change = true;
				m_data.rank[i].score = m_data.user[uid].score;
			}
		}
		if(!change && m_data.user[uid].score > m_data.rank[DATA_NEW_MATCH_RANK-1].score)
			add = true;
		if(add || change)
		{
			vector<NewMatchUser> vec;
			for(unsigned i=0;i<DATA_NEW_MATCH_RANK;++i)
				vec.push_back(m_data.rank[i]);
			if(add)
			{
				NewMatchUser temp;
				temp.uid = uid;
				temp.score = m_data.user[uid].score;
				temp.name = m_data.user[uid].name;
				temp.aname = m_data.user[uid].aname;
				temp.fig = m_data.user[uid].fig;
				vec.push_back(temp);
			}
			sort(vec.begin(),vec.end(),NewMatchUserCompare);
			for(unsigned i=0;i<DATA_NEW_MATCH_RANK;++i)
				m_data.rank[i] = vec[i];
		}
	}

	user[0] = m_data.user[uid];
	user[1] = npc;

	return 0;
}

int CDataNewMatch::Guess(unsigned uid, unsigned guess, unsigned bet)
{
	if(m_data.stage != e_NewMatchStage_guess_top8)
		return R_ERR_LOGIC;

	if(m_data.guess.count(uid))
		return R_ERR_LOGIC;

	m_data.guess[uid].uid = uid;
	m_data.guess[uid].bet = bet;
	m_data.guess[uid].guess = guess;

	return 0;
}

int CDataNewMatch::Regular()
{
	if(m_data.stage != e_NewMatchStage_apply_regular)
		return R_ERR_LOGIC;

	m_data.stage = e_NewMatchStage_guess_top8;

	for(unsigned i=0;i<8;++i)
	{
		if(IsValidUid(m_data.rank[i].uid))
		{
			m_data.top8[i] = m_data.user[m_data.rank[i].uid];
			m_data.top8[i].Recover();
		}
	}

	return 0;
}

int CDataNewMatch::Top8()
{
	if(m_data.stage != e_NewMatchStage_guess_top8)
		return R_ERR_LOGIC;

	m_data.stage = e_NewMatchStage_guess_top4;

	for(unsigned i=0;i<4;++i)
	{
		unsigned attacker = i, defender = 7 - i;

		 if(!IsValidUid(m_data.top8[attacker].uid) && !IsValidUid(m_data.top8[defender].uid))
			 continue;

		if(IsValidUid(m_data.top8[attacker].uid) && IsValidUid(m_data.top8[defender].uid))
		{
			for(unsigned j=0;j<DATA_NEW_MATCH_HERO;++j)
				CDataBattleRoom::attacking(m_data.top8[attacker].hero[m_data.top8[attacker].index[j]], m_data.top8[defender].hero[m_data.top8[defender].index[j]]);

			unsigned win = 0;
			for(unsigned j=0;j<DATA_NEW_MATCH_HERO;++j)
			{
				if(m_data.top8[defender].hero[j].dead())
					++win;
			}
			m_data.top4[i] = (win >= DATA_NEW_MATCH_HERO/2 + 1)?m_data.top8[attacker]:m_data.top8[defender];

			m_data.top4[i].Recover();
		}
		else
			m_data.top4[i] = IsValidUid(m_data.top8[attacker].uid)?m_data.top8[attacker]:m_data.top8[defender];
	}

	return 0;
}

int CDataNewMatch::Top4()
{
	if(m_data.stage != e_NewMatchStage_guess_top4)
		return R_ERR_LOGIC;

	m_data.stage = e_NewMatchStage_guess_top2;

	for(unsigned i=0;i<2;++i)
	{
		unsigned attacker = i, defender = 3 - i;

		 if(!IsValidUid(m_data.top4[attacker].uid) && !IsValidUid(m_data.top4[defender].uid))
			 continue;

		if(IsValidUid(m_data.top4[attacker].uid) && IsValidUid(m_data.top4[defender].uid))
		{
			for(unsigned j=0;j<DATA_NEW_MATCH_HERO;++j)
				CDataBattleRoom::attacking(m_data.top4[attacker].hero[m_data.top4[attacker].index[j]], m_data.top4[defender].hero[m_data.top4[defender].index[j]]);

			unsigned win = 0;
			for(unsigned j=0;j<DATA_NEW_MATCH_HERO;++j)
			{
				if(m_data.top4[defender].hero[j].dead())
					++win;
			}
			m_data.top2[i] = (win >= DATA_NEW_MATCH_HERO/2 + 1)?m_data.top4[attacker]:m_data.top4[defender];

			m_data.top2[i].Recover();
		}
		else
			m_data.top2[i] = IsValidUid(m_data.top4[attacker].uid)?m_data.top4[attacker]:m_data.top4[defender];
	}

	return 0;
}

int CDataNewMatch::Top2()
{
	if(m_data.stage != e_NewMatchStage_guess_top2)
		return R_ERR_LOGIC;

	m_data.stage = e_NewMatchStage_end;

	 if(!IsValidUid(m_data.top2[0].uid) && !IsValidUid(m_data.top2[1].uid))
		 return 0;

	if(IsValidUid(m_data.top2[0].uid) && IsValidUid(m_data.top2[1].uid))
	{
		for(unsigned j=0;j<DATA_NEW_MATCH_HERO;++j)
			CDataBattleRoom::attacking(m_data.top2[0].hero[m_data.top2[0].index[j]], m_data.top2[1].hero[m_data.top2[1].index[j]]);
	}

	CLogicNewMatch logicNewMatch;
	logicNewMatch.Reward();

	Save();
	return 0;
}

int CDataNewMatch::Restart()
{
	m_data.Restart();
	Save();
	return 0;
}

void CDataNewMatch::makeNPC(unsigned turn, NewMatchUser& npc)
{
	unsigned day = CTime::GetDayInterval(Config::GetIntValue(CONFIG_OPEN_TS), Time::GetGlobalTime());
	if(day >= NEW_WORLD_HERO_DAY)
		day = NEW_WORLD_HERO_DAY - 1;
	unsigned npcdefault = CDataNewWorld::npc_day_default[day];

	if(turn >= DATA_NEW_MATCH_REGULAR)
		turn  = DATA_NEW_MATCH_REGULAR - 1;

	npc.uid = ADMIN_UID;
	for(unsigned j=0;j<DATA_NEW_MATCH_HERO;++j)
	{
		npc.hero[j].job = NEW_MATCH_NPC_JOB[turn][j] - 1;
		npc.hero[j].level = CDataNewWorld::npc_level[npcdefault];
		for(unsigned k=0;k<BattleRoomHeroProperty_max;++k)
			npc.hero[j].property[k] = CDataNewWorld::npc_property[npc.hero[j].job][npcdefault][k] * NEW_MATCH_NPC_POWER[turn];
	}
	npc.Recover();
}
