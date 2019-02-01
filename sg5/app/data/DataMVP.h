/*
 * DataMVP.h
 *
 *  Created on: 2017-08-03
 *      Author: Ralf
 */

#ifndef DATAMVP_H_
#define DATAMVP_H_

#include "Kernel.h"
#include "DataBase.h"

#define MVP_RANK 10
#define IS_VALID_MVP_RANK(i) (i>=1 && i<=MVP_RANK)

/**********************************************************/
class DataMVPHero {
public:
	unsigned int id;
	unsigned int lv;
	unsigned int dehp;
	string icon;
	string name;
	DataMVPHero() {
		id = 0;
		lv = 0;
		dehp = 0;
	}
	~DataMVPHero() {
	}
	void Serialize(MVP::MVPHero *p) {
		p->set_id(id);
		p->set_lv(lv);
		p->set_dehp(dehp);
		p->set_icon(icon);
		p->set_name(name);
	}
	void Parse(const MVP::MVPHero &p) {
		id = p.id();
		lv = p.lv();
		dehp = p.dehp();
		icon = p.icon();
		name = p.name();
	}
	void Get(Json::Value &result)
	{
		result["hero"]["id"] = id;
		result["hero"]["lv"] = lv;
		result["hero"]["dehp"] = dehp;
		result["hero"]["icon"] = icon;
		result["hero"]["name"] = name;
	}
};
class DataMVPUser {
public:
	unsigned int rank;
	unsigned int uid;
	string name;
	string fig;
	string sign;
	unsigned int mcity;
	DataMVPHero hero;
	unsigned int fid;
	unsigned int fts;
	DataMVPUser() {
		rank = 0;
		uid = 0;
		mcity = 0;
		fid = 0;
		fts = 0;
	}
	~DataMVPUser() {
	}
	void Serialize(MVP::MVPUser *p) {
		p->set_rank(rank);
		p->set_uid(uid);
		p->set_name(name);
		p->set_fig(fig);
		p->set_sign(sign);
		p->set_mcity(mcity);
		hero.Serialize(p->mutable_hero());
		p->set_fid(fid);
		p->set_fts(fts);
	}
	void Parse(const MVP::MVPUser &p) {
		rank = p.rank();
		uid = p.uid();
		name = p.name();
		fig = p.fig();
		sign = p.sign();
		mcity = p.mcity();
		hero.Parse(p.hero());
		fid = p.fid();
		fts = p.fts();
	}
	void Get(Json::Value &result)
	{
		result["rank"] = rank;
		result["uid"] = uid;
		result["name"] = name;
		result["fig"] = fig;
		result["sign"] = sign;
		result["mcity"] = mcity;
		hero.Get(result);
		result["fid"] = fid;
		result["fts"] = fts;
	}
};
class DataMVP {
public:
	map<unsigned int, DataMVPUser> user;
	map<unsigned int, DataMVPUser> player;
	map<unsigned int, DataMVPUser> fight;
	multimap<unsigned int, DataMVPUser> all;

	Json::Value res;
	Json::Value resBattle;
	Json::Value resFight;
	Json::Value resAll;

	DataMVP() {
	}
	~DataMVP() {
	}
	void Serialize(MVP::MVP *p) {
		for (map<unsigned int, DataMVPUser>::iterator it = user.begin();it != user.end(); ++it)
			it->second.Serialize(p->add_user());
		for(map<unsigned int, DataMVPUser>::iterator it = player.begin(); it != player.end(); ++it)
			it->second.Serialize(p->add_player());
		for(map<unsigned int, DataMVPUser>::iterator it = fight.begin(); it != fight.end(); ++it)
			it->second.Serialize(p->add_fight());
		for(multimap<unsigned int, DataMVPUser>::iterator it = all.begin(); it != all.end(); ++it)
			it->second.Serialize(p->add_all());
	}
	void Parse(const MVP::MVP &p) {
		for (int i = 0; i < p.user_size(); ++i)
			user[p.user(i).rank()].Parse(p.user(i));
		for (int i = 0; i < p.player_size(); ++i)
			player[p.player(i).rank()].Parse(p.player(i));
		for(int i = 0; i < p.fight_size(); ++i)
			fight[p.fight(i).rank()].Parse(p.fight(i));
		for(int i = 0; i < p.all_size(); ++i)
		{
			DataMVPUser t;
			t.Parse(p.all(i));
			all.insert(make_pair(p.all(i).rank(),t));
		}
	}

	void Get()
	{
		res.clear();
		res.resize(0);
		for(map<unsigned int, DataMVPUser>::iterator it=user.begin();it!=user.end();++it)
		{
			if(it->second.uid || (it->second.fid && it->second.fts + MVP_ATTACK_MAX_TIME > Time::GetGlobalTime()))
			{
				Json::Value t;
				it->second.Get(t);
				res.append(t);
			}
		}
	}
	void GetBattle()
	{
		resBattle.clear();
		resBattle.resize(0);
		for(map<unsigned int, DataMVPUser>::iterator it=player.begin();it!=player.end();++it)
		{
			if(it->second.uid || (it->second.fid && it->second.fts + MVP_ATTACK_MAX_TIME > Time::GetGlobalTime()))
			{
				Json::Value t;
				it->second.Get(t);
				resBattle.append(t);
			}
		}
	}
	void GetFight()
	{
		resFight.clear();
		resFight.resize(0);
		for(map<unsigned int, DataMVPUser>::iterator it=fight.begin();it!=fight.end();++it)
		{
			if(it->second.uid)
			{
				Json::Value t;
				it->second.Get(t);
				resFight.append(t);
			}
		}
	}
	void GetAll()
	{
		resAll.clear();
		resAll.resize(0);
		for(multimap<unsigned int, DataMVPUser>::reverse_iterator it=all.rbegin();it!=all.rend();++it)
		{
			Json::Value t;
			it->second.Get(t);
			resAll.append(t);
			if(resAll.size() >= MVP_RANK)
				break;
		}
	}
};
/**********************************************************/

class CDataMVP : public DataBase
{
public:
	CDataMVP(string path);
	virtual ~CDataMVP(){}
	int Init();
	int Save();
	int Sig(int sig);

	//攻城
	int GetAllServerMVP(Json::Value &result);
	int StartAllServerMVP(unsigned rank, unsigned uid);
	int EndAllServerMVP(unsigned rank, unsigned uid, bool win, Json::Value &data);
	int SetAllServerMVP(unsigned uid, string &sign);

	//斗将
	int StartAllServerBattleMVP(unsigned rank, unsigned uid);
	int EndAllServerBattleMVP(unsigned rank, unsigned uid, bool win, Json::Value &data);

	//争霸
	int EndAllServerNewWorldFightMVP(unsigned rank, unsigned uid, bool win, Json::Value &data);

private:
	void Daily();
	void Reward();
	void Clear();

	DataMVP m_data;
};

#endif /* DATAMVP_H_ */
