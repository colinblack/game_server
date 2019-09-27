#ifndef DATANEWDOUJIANG_H_
#define DATANEWDOUJIANG_H_


#include <math.h>
#include "Kernel.h"
#include "DataBase.h"
//#include "LogicUser.h"


class DataNewDouJiangHistory {
public:
	unsigned int uid;
	unsigned int type;
	int n;
	int point;
	unsigned int ts;
	bool hasfc;
	DataNewDouJiangHistory() {
		uid = 0;
		type = 0;
		n = 0;
		point = 0;
		ts = 0;
		hasfc = false;
	}
	~DataNewDouJiangHistory() {
	}
	void Serialize(NewDouJiang::NewDouJiangHistory *p) {
		p->set_uid(uid);
		p->set_type(type);
		p->set_n(n);
		p->set_point(point);
		p->set_ts(ts);
		p->set_hasfc(hasfc);
	}
	void Parse(const NewDouJiang::NewDouJiangHistory &p) {
		uid = p.uid();
		type = p.type();
		n = p.n();
		point = p.point();
		ts = p.ts();
		hasfc = p.hasfc();
	}

	void GetJson(Json::Value& res)
	{
		res["uid"] = uid;
		res["type"] = type;
		res["n"] = n;
		res["point"] = point;
		res["ts"] = ts;
		res["hasfc"] = hasfc;
	}
};

class DataNewDouJiangAttackInfo {
public:
	unsigned uid;
	unsigned type;
	unsigned ts;
	DataNewDouJiangAttackInfo() {
		uid = type = ts = 0;
	}
	~DataNewDouJiangAttackInfo() {
	}
	void Serialize(NewDouJiang::NewDouJiangAttackInfo *p) {
		p->set_uid(uid);
		p->set_type(type);
		p->set_ts(ts);
	}

	void Parse(const NewDouJiang::NewDouJiangAttackInfo &p) {
		uid = p.uid();
		type = p.type();
		ts = p.ts();
	}

	void GetJson(Json::Value& res)
	{
		res["uid"] = uid;
		res["type"] = type;
		res["ts"] = ts;
	}
};

class DataNewDouJiangUser {
public:
	unsigned uid;
	unsigned seq;
	unsigned ts;
	int pppoint;
	int fcpoint;
	int zspoint;
	unsigned numpp;
	set<unsigned> szheros;
	set<unsigned> ppheros;
	set<unsigned> fcheros;
	set<unsigned> zsheros;
	map<unsigned, DataNewDouJiangAttackInfo> flist;
	list<DataNewDouJiangHistory> his;
	DataNewDouJiangUser() {
		uid = seq = ts = pppoint = fcpoint = zspoint =numpp = 0;
	}
	~DataNewDouJiangUser() {
	}
	void Serialize(NewDouJiang::NewDouJiangUser *p) {
		p->set_uid(uid);
		p->set_seq(seq);
		p->set_ts(ts);
		p->set_pppoint(pppoint);
		p->set_fcpoint(fcpoint);
		p->set_zspoint(zspoint);
		p->set_numpp(numpp);
		for (set<unsigned>::iterator it = szheros.begin(); it!=szheros.end();++it) {
			p->add_szheros(*it);
		}
		for (set<unsigned>::iterator it = ppheros.begin(); it!=ppheros.end();++it) {
			p->add_ppheros(*it);
		}
		for (set<unsigned>::iterator it = fcheros.begin(); it!=fcheros.end();++it) {
			p->add_fcheros(*it);
		}
		for (set<unsigned>::iterator it = zsheros.begin(); it!=zsheros.end();++it) {
			p->add_zsheros(*it);
		}
		for (map<unsigned, DataNewDouJiangAttackInfo>::iterator it = flist.begin(); it != flist.end(); ++it)
			(it->second).Serialize(p->add_flist());
		for (list<DataNewDouJiangHistory>::iterator it = his.begin(); it != his.end(); ++it)
			it->Serialize(p->add_his());
	}

	void Parse(const NewDouJiang::NewDouJiangUser &p) {
		uid = p.uid();
		seq = p.seq();
		ts = p.ts();
		pppoint = p.pppoint();
		zspoint = p.zspoint();
		fcpoint = p.fcpoint();
		numpp = p.numpp();
		for (int i = 0; i < p.szheros_size(); ++i)
			szheros.insert(p.szheros(i));
		for (int i = 0; i < p.ppheros_size(); ++i)
			ppheros.insert(p.ppheros(i));
		for (int i = 0; i < p.fcheros_size(); ++i)
			fcheros.insert(p.fcheros(i));
		for (int i = 0; i < p.zsheros_size(); ++i)
			zsheros.insert(p.zsheros(i));
		for (int i = 0; i < p.flist_size(); ++i)
		{
			DataNewDouJiangAttackInfo t;
			flist[p.flist(i).uid()].Parse(p.flist(i));
		}
		for (int i = 0; i < p.his_size(); ++i)
		{
			DataNewDouJiangHistory t;
			t.Parse(p.his(i));
			his.push_back(t);
		}
	}

	void GetJson(Json::Value& res)
	{
		res["seq"] = seq;
		for (set<unsigned>::iterator it = szheros.begin();it!=szheros.end();++it) {
			res["szheros"].append(*it);
		}
		for (set<unsigned>::iterator it = ppheros.begin();it!=ppheros.end();++it) {
			res["ppheros"].append(*it);
		}
		for (set<unsigned>::iterator it = fcheros.begin();it!=fcheros.end();++it) {
			res["fcheros"].append(*it);
		}
		for (set<unsigned>::iterator it = zsheros.begin();it!=zsheros.end();++it) {
			res["zsheros"].append(*it);
		}
		res["flist"].resize(0);
		for(map<unsigned, DataNewDouJiangAttackInfo>::iterator it=flist.begin();it!=flist.end();)
		{
			if ((it->second).ts + NEW_DOUJIANG_ATTACK_MAX_TIME < Time::GetGlobalTime())
			{
				flist.erase(it++);
			}
			else
				++it;
		}
		for(map<unsigned, DataNewDouJiangAttackInfo>::iterator it=flist.begin();it!=flist.end();++it)
		{
			Json::Value t;
			it->second.GetJson(t);
			res["flist"].append(t);
		}
		res["pppoint"] = pppoint;
		res["fcpoint"] = fcpoint;
		res["zspoint"] = zspoint;
		res["numpp"] = numpp;
		res["timestamp"] = ts;
	}
};



class DataNewDouJiang {
public:
	map<unsigned, DataNewDouJiangUser> user;
	int ver;
	int rewarded;
	DataNewDouJiang()  {
		ver = -1;
		rewarded = 0;
	}
	~DataNewDouJiang() {
	}
	void Serialize(NewDouJiang::NewDouJiang *p)
	{
		p->set_ver(ver);
		p->set_rewarded(rewarded);
		for (map<unsigned, DataNewDouJiangUser>::iterator it = user.begin(); it!=user.end(); ++it) {
			it->second.Serialize(p->add_user());
		}
	}

	void Parse(const NewDouJiang::NewDouJiang &p) {
		ver = p.ver();
		rewarded = p.rewarded();
		for (int i = 0; i < p.user_size(); ++i)
			user[p.user(i).uid()].Parse(p.user(i));
	}
};

/**********************************************************/

class CDataNewDouJiang : public DataBase
{
public:
	CDataNewDouJiang(string path);
	virtual ~CDataNewDouJiang(){}
	int Init();
	int Save();
	int Sig(int sig);

	void CheckVersion();
	int GetDuanWei(int score);
	int SetZhenRong(unsigned uid,const vector<unsigned>& p, Json::Value & result);
	int GetZhenRong(unsigned uid,Json::Value & result);
	int GetMyList(unsigned uid,Json::Value & result);
	int PiPei(unsigned uid,unsigned seq,Json::Value & result);
	int StartAttack(unsigned uid, unsigned type, unsigned uid2, unsigned hud, unsigned seq, unsigned ud, Json::Value & result, unsigned fcts=0);
	int SetResult(unsigned uid, unsigned type, unsigned uid2, unsigned win, unsigned hud, unsigned seq, unsigned ud, Json::Value & result);
	int GetRankList(unsigned uid, Json::Value & result);
	int GetZhanBao(unsigned uid, Json::Value &result);
private:
	void CheckUserHerosTs(unsigned uid);

private:
	DataNewDouJiang m_data;
};

#endif /* DATANEWDOUJIANG_H_ */
