/*
 * DataNewMatch.h
 *
 *  Created on: 2015-10-23
 *      Author: Ralf
 */

#ifndef DATANEWMATCH_H_
#define DATANEWMATCH_H_

#include "Kernel.h"
#include "DataBattleRoom.h"
#include "DataBase.h"
#include "ProtoNewMatch.pb.h"

#define DATA_NEW_MATCH_HERO 	5
#define DATA_NEW_MATCH_RANK		8
#define DATA_NEW_MATCH_REGULAR	15

enum NewMatchStage
{
	e_NewMatchStage_apply_regular	 = 0,
	e_NewMatchStage_guess_top8		 = 1,
	e_NewMatchStage_guess_top4		 = 2,
	e_NewMatchStage_guess_top2		 = 3,
	e_NewMatchStage_end				 = 4
};

class NewMatchUser
{
public:
	unsigned uid, score, turn, index[DATA_NEW_MATCH_HERO];
	string name, aname, fig;
	BattleHeroRoomProperty hero[DATA_NEW_MATCH_HERO];
	NewMatchUser()
	{
		uid = score = turn = 0;
		for(unsigned i=0;i<DATA_NEW_MATCH_HERO;++i)
			index[i] = i;
	}
	~NewMatchUser(){}
	void Clear()
	{
		uid = score = turn = 0;
		for(unsigned i=0;i<DATA_NEW_MATCH_HERO;++i)
			index[i] = i;
		name.clear();
		aname.clear();
		fig.clear();
		memset(hero, 0, sizeof(hero));
	}
	void Recover()
	{
		for(unsigned i=0;i<DATA_NEW_MATCH_HERO;++i)
			hero[i].recover();
	}
	void ChangeIndex(unsigned index1[DATA_NEW_MATCH_HERO])
	{
		memcpy(index, index1, sizeof(index));
	}
	void parse(const ProtoNewMatch::ProtoNewMatchUser &p)
	{
		uid = p.uid();
		score = p.score();
		turn = p.turn();
		for(int i=0;i<DATA_NEW_MATCH_HERO;++i)
			index[i] = p.index(i);
		name = p.name();
		aname = p.aname();
		fig = p.fig();
		for(int i=0;i<DATA_NEW_MATCH_HERO;++i)
			hero[i].parse(p.hero(i));
	}
	void serialize(ProtoNewMatch::ProtoNewMatchUser *p)
	{
		p->set_uid(uid);
		p->set_score(score);
		p->set_turn(turn);
		for(int i=0;i<DATA_NEW_MATCH_HERO;++i)
			p->add_index(index[i]);
		p->set_uid(uid);
		p->set_name(name);
		p->set_aname(aname);
		p->set_fig(fig);
		for(int i=0;i<DATA_NEW_MATCH_HERO;++i)
			 hero[i].serialize(p->add_hero());
	}
};

class NewMatchGuess
{
public:
	unsigned uid, guess, bet;
	NewMatchGuess()
	{
		uid = guess = bet = 0;
	}
	~NewMatchGuess(){}
	void parse(const ProtoNewMatch::ProtoNewMatchGuess &p)
	{
		uid = p.uid();
		guess = p.guess();
		bet = p.bet();
	}
	void serialize(ProtoNewMatch::ProtoNewMatchGuess *p)
	{
		p->set_uid(uid);
		p->set_guess(guess);
		p->set_bet(bet);
	}
};

typedef map<unsigned, NewMatchUser> NewMatchUserMap;
typedef map<unsigned, NewMatchGuess> NewMatchGuessMap;
class DataNewMatch
{
public:
	unsigned stage;
	NewMatchUser rank[DATA_NEW_MATCH_RANK];
	NewMatchUser top8[8];
	NewMatchUser top4[4];
	NewMatchUser top2[2];
	NewMatchUserMap user;
	NewMatchGuessMap guess;
	DataNewMatch()
	{
		stage = e_NewMatchStage_apply_regular;
	}
	~DataNewMatch(){}
	void Restart()
	{
		stage = e_NewMatchStage_apply_regular;
		for(unsigned i=0;i<DATA_NEW_MATCH_RANK;++i)
			rank[i].Clear();
		for(unsigned i=0;i<8;++i)
			top8[i].Clear();
		for(unsigned i=0;i<4;++i)
			top4[i].Clear();
		for(unsigned i=0;i<2;++i)
			top2[i].Clear();
		user.clear();
		guess.clear();
	}
	void parse(ProtoNewMatch::ProtoNewMatch* p)
	{
		stage = p->stage();
		for(int i=0;i<DATA_NEW_MATCH_RANK;++i)
			rank[i].parse(p->rank(i));
		for(int i=0;i<8;++i)
			top8[i].parse(p->top8(i));
		for(int i=0;i<4;++i)
			top4[i].parse(p->top4(i));
		for(int i=0;i<2;++i)
			top2[i].parse(p->top2(i));
		for(int i=0;i<p->user_size();++i)
			user[p->user(i).uid()].parse(p->user(i));
		for(int i=0;i<p->guess_size();++i)
			guess[p->guess(i).uid()].parse(p->guess(i));
	}
	void serialize(ProtoNewMatch::ProtoNewMatch *p)
	{
		p->set_stage(stage);
		for(int i=0;i<DATA_NEW_MATCH_RANK;++i)
			rank[i].serialize(p->add_rank());
		for(int i=0;i<8;++i)
			top8[i].serialize(p->add_top8());
		for(int i=0;i<4;++i)
			top4[i].serialize(p->add_top4());
		for(int i=0;i<2;++i)
			top2[i].serialize(p->add_top2());
		for(NewMatchUserMap::iterator it=user.begin();it!=user.end();++it)
			it->second.serialize(p->add_user());
		for(NewMatchGuessMap::iterator it=guess.begin();it!=guess.end();++it)
			it->second.serialize(p->add_guess());
	}
};

class CDataNewMatch : public DataBase
{
public:
	CDataNewMatch(string path);
	virtual ~CDataNewMatch(){}
	int Init();
	int Save();
	int Sig(int sig);
	const DataNewMatch& Get(){return m_data;}
	int Apply(NewMatchUser& user);
	int ChangeIndex(unsigned uid, unsigned index[DATA_NEW_MATCH_HERO]);
	int Fight(unsigned uid, NewMatchUser user[2]);
	int Guess(unsigned uid, unsigned guess, unsigned bet);
	int Regular();
	int Top8();
	int Top4();
	int Top2();
	int Restart();

private:
	void makeNPC(unsigned turn, NewMatchUser& npc);
	DataNewMatch m_data;
};

#endif /* DATANEWMATCH_H_ */
