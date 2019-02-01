/*
 * DataQingRenJie.h
 */

#ifndef DATAQINGRENJIE_H_
#define DATAQINGRENJIE_H_

#include "Kernel.h"
#include "DataBase.h"

/**********************************************************/
class DataQingRenJieUser {
public:
	unsigned int uid;
	unsigned int num;
	DataQingRenJieUser() {
		uid = 0;
		num = 0;
	}
	~DataQingRenJieUser() {
	}
	void Serialize(QingRenJie::QingRenJieUser *p) {
		p->set_uid(uid);
		p->set_num(num);
	}
	void Parse(const QingRenJie::QingRenJieUser &p) {
		uid = p.uid();
		num = p.num();
	}
	void GetJson(Json::Value &t)
	{
		t["uid"] = uid;
		t["num"] = num;
	}
};
class DataQingRenJieNvShen {
public:
	unsigned int nsid;
	unsigned int num;
	map<unsigned int, DataQingRenJieUser> user;
	DataQingRenJieNvShen() {
		nsid = 0;
		num = 0;
	}
	~DataQingRenJieNvShen() {
	}
	void Serialize(QingRenJie::QingRenJieNvShen *p) {
		p->set_nsid(nsid);
		for (map<unsigned int, DataQingRenJieUser>::iterator it = user.begin(); it != user.end(); ++it)
			it->second.Serialize(p->add_user());
	}
	void Parse(const QingRenJie::QingRenJieNvShen &p) {
		nsid = p.nsid();
		num = 0;
		for (int i = 0; i < p.user_size(); ++i)
		{
			user[p.user(i).uid()].Parse(p.user(i));
			num += p.user(i).num();
		}
	}
	void GetJson(Json::Value &p)
	{
		p["nsid"] = nsid;
		p["num"] = num;
		/*
		p["nvshen"].resize(0);
		for(map<unsigned int, DataQingRenJieUser>::iterator it=user.begin();it!=user.end();++it)
		{
			Json::Value t;
			it->second.GetJson(t);
			p["nvshen"].append(t);
		}
		*/
	}
	void Add(unsigned uid, unsigned tnum)
	{
		if(!user.count(uid))
		{
			user[uid].uid = uid;
			user[uid].num = tnum;
		}
		else
		{
			user[uid].num += tnum;
		}
		num += tnum;
	}
};
class DataQingRenJie {
public:
	unsigned int ver;
	unsigned int rewarded;
	map<unsigned int, DataQingRenJieNvShen> nvshen;
	DataQingRenJie() {
		ver = 0;
		rewarded = 0;
	}
	~DataQingRenJie() {
	}
	void Serialize(QingRenJie::QingRenJie *p) {
		p->set_ver(ver);
		p->set_rewarded(rewarded);
		for (map<unsigned int, DataQingRenJieNvShen>::iterator it = nvshen.begin(); it != nvshen.end(); ++it)
			it->second.Serialize(p->add_nvshen());
	}
	void Parse(const QingRenJie::QingRenJie &p) {
		ver = p.ver();
		rewarded = p.rewarded();
		for (int i = 0; i < p.nvshen_size(); ++i)
			nvshen[p.nvshen(i).nsid()].Parse(p.nvshen(i));
	}
	void GetJson(Json::Value &t)
	{
		for (map<unsigned int, DataQingRenJieNvShen>::iterator it = nvshen.begin(); it != nvshen.end(); ++it)
		{
			Json::Value tns;
			it->second.GetJson(tns);
			t["nvshen"].append(tns);
		}
		/*
		if(nvshen.count(nsid))
			nvshen[nsid].GetJson(t);
		else
			t["nvshen"].resize(0);
		*/
	}
	void Add(unsigned uid, unsigned nsid, unsigned num)
	{
		if(!nvshen.count(nsid))
			nvshen[nsid].nsid = nsid;
		nvshen[nsid].Add(uid, num);
	}
};
/**********************************************************/

class CDataQingRenJie : public DataBase
{
public:
	CDataQingRenJie(string path);
	virtual ~CDataQingRenJie(){}
	int Init();
	int Save();
	int SongHua(unsigned uid, unsigned nsid, unsigned num, Json::Value &result);
	int GetInfo(Json::Value &result);

private:
	DataQingRenJie m_data;
};

#endif /* DATAQINGRENJIE_H_ */
