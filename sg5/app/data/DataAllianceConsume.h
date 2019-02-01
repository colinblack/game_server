/*
 * DataAllianceConsume.h
 *
 *  Created on: 2017-3-15
 *      Author: Ralf
 */

#ifndef DATAALLIANCECONSUME_H_
#define DATAALLIANCECONSUME_H_

#include "Kernel.h"
#include "DataBase.h"

/**********************************************************/
class DataAllianceConsumeUser {
public:
	unsigned int uid;
	unsigned int consume;
	DataAllianceConsumeUser() {
		uid = 0;
		consume = 0;
	}
	~DataAllianceConsumeUser() {
	}
	void Serialize(AllianceConsume::AllianceConsumeUser *p) {
		p->set_uid(uid);
		p->set_consume(consume);
	}
	void Parse(const AllianceConsume::AllianceConsumeUser &p) {
		uid = p.uid();
		consume = p.consume();
	}
	void GetJson(Json::Value &t)
	{
		t["uid"] = uid;
		t["c"] = consume;
	}
};
class DataAllianceConsumeAlliance {
public:
	unsigned int aid;
	map<unsigned int, DataAllianceConsumeUser> user;
	DataAllianceConsumeAlliance() {
		aid = 0;
	}
	~DataAllianceConsumeAlliance() {
	}
	void Serialize(AllianceConsume::AllianceConsumeAlliance *p) {
		p->set_aid(aid);
		for (map<unsigned int, DataAllianceConsumeUser>::iterator it = user.begin(); it != user.end(); ++it)
			it->second.Serialize(p->add_user());
	}
	void Parse(const AllianceConsume::AllianceConsumeAlliance &p) {
		aid = p.aid();
		for (int i = 0; i < p.user_size(); ++i)
			user[p.user(i).uid()].Parse(p.user(i));
	}
	void GetJson(Json::Value &p)
	{
		p["consume"].resize(0);
		for(map<unsigned int, DataAllianceConsumeUser>::iterator it=user.begin();it!=user.end();++it)
		{
			Json::Value t;
			it->second.GetJson(t);
			p["consume"].append(t);
		}
	}
	void Add(unsigned u, unsigned v)
	{
		if(user.count(u))
			user[u].consume += v;
		else
		{
			user[u].uid = u;
			user[u].consume = v;
		}
	}
	bool Check(unsigned c, unsigned v)
	{
		unsigned s = 0;
		for(map<unsigned int, DataAllianceConsumeUser>::iterator it=user.begin();it!=user.end();++it)
		{
			if(it->second.consume >= v)
				++s;
			if(s >= c)
				return true;
		}
		return false;
	}
};
class DataAllianceConsume {
public:
	unsigned int ver;
	map<unsigned int, DataAllianceConsumeAlliance> alliance;
	DataAllianceConsume() {
		ver = 0;
	}
	~DataAllianceConsume() {
	}
	void Serialize(AllianceConsume::AllianceConsume *p) {
		p->set_ver(ver);
		for (map<unsigned int, DataAllianceConsumeAlliance>::iterator it = alliance.begin(); it != alliance.end(); ++it)
			it->second.Serialize(p->add_alliance());
	}
	void Parse(const AllianceConsume::AllianceConsume &p) {
		ver = p.ver();
		for (int i = 0; i < p.alliance_size(); ++i)
			alliance[p.alliance(i).aid()].Parse(p.alliance(i));
	}
	void GetJson(unsigned a, Json::Value &t)
	{
		if(alliance.count(a))
			alliance[a].GetJson(t);
		else
			t["consume"].resize(0);
	}
	void Add(unsigned a, unsigned u, unsigned v)
	{
		if(!alliance.count(a))
			alliance[a].aid = a;
		alliance[a].Add(u, v);
	}
	bool Check(unsigned a, unsigned c, unsigned v)
	{
		if(alliance.count(a))
			return alliance[a].Check(c, v);
		return false;
	}
};
/**********************************************************/

class CDataAllianceConsume : public DataBase
{
public:
	CDataAllianceConsume(string path);
	virtual ~CDataAllianceConsume(){}
	int Init();
	int Save();

	int AllianceShopInfo(unsigned aid, Json::Value &result);
	int AllianceShopBuy(unsigned uid, unsigned aid, unsigned index, unsigned count, Json::Value &result);
	int AllianceShopLimit(unsigned uid, unsigned aid, unsigned type, unsigned index, unsigned count, Json::Value &result);
	int AllianceShopGift(unsigned uid, unsigned aid, unsigned index, Json::Value &result);
private:

	DataAllianceConsume m_data;
};

#endif /* DATAALLIANCECONSUME_H_ */
