/*
 * DataCrowdFunding.h
 *
 *  Created on: 2016-1-25
 *      Author: Ralf
 */

#ifndef DATACROWDFUNDING_H_
#define DATACROWDFUNDING_H_


#include "Kernel.h"
#include "DataBase.h"
#include "CrowdFunding.pb.h"

#define CROWD_FUNDING_NEED_CASH 10
#define CROWD_FUNDING_NEED_BAG 10
#define CROWD_FUNDING_BAG 831

struct CrowdFundingConfigItme
{
	unsigned id, count, need;
};

class DataCrowdFundingUser {
public:
	unsigned int uid;
	unsigned int had;
	DataCrowdFundingUser() {
		uid = 0;
		had = 0;
	}
	~DataCrowdFundingUser(){}
	void Serialize(CrowdFunding::CrowdFundingUser *p) {
		p->set_uid(uid);
		p->set_had(had);
	}
	void Parse(const CrowdFunding::CrowdFundingUser &p) {
		uid = p.uid();
		had = p.had();
	}
};
class DataCrowdFundingItem {
public:
	unsigned int id;
	unsigned int count;
	unsigned int need;
	unsigned int had;
	unsigned int lastuid;
	string lastname;
	unsigned int lasthad;
	map<unsigned int, DataCrowdFundingUser> user;
	DataCrowdFundingItem() {
		id = 0;
		count = 0;
		need = 0;
		had = 0;
		lastuid = 0;
		lasthad = 0;
	}
	~DataCrowdFundingItem(){}
	void Serialize(CrowdFunding::CrowdFundingItem *p) {
		p->set_id(id);
		p->set_count(count);
		p->set_need(need);
		p->set_had(had);
		p->set_lastuid(lastuid);
		p->set_lastname(lastname);
		p->set_lasthad(lasthad);
		for (map<unsigned int, DataCrowdFundingUser>::iterator it =	user.begin(); it != user.end(); ++it)
			it->second.Serialize(p->add_user());
	}
	void Parse(const CrowdFunding::CrowdFundingItem &p) {
		id = p.id();
		count = p.count();
		need = p.need();
		had = p.had();
		lastuid = p.lastuid();
		lastname = p.lastname();
		lasthad = p.lasthad();
		for (int i = 0; i < p.user_size(); ++i)
			user[p.user(i).uid()].Parse(p.user(i));
	}
};
class DataCrowdFunding {
public:
	map<unsigned int, DataCrowdFundingItem> item;
	DataCrowdFunding() {
	}
	~DataCrowdFunding(){}
	void Serialize(CrowdFunding::CrowdFunding *p) {
		for (map<unsigned int, DataCrowdFundingItem>::iterator it =	item.begin(); it != item.end(); ++it)
			it->second.Serialize(p->add_item());
	}
	void Parse(const CrowdFunding::CrowdFunding &p) {
		for (int i = 0; i < p.item_size(); ++i)
			item[p.item(i).id()].Parse(p.item(i));
	}
};

class CDataCrowdFunding : public DataBase
{
public:
	CDataCrowdFunding(string path);
	virtual ~CDataCrowdFunding(){}
	int Init();
	int Save();
	int Sig(int sig);
	int Get(unsigned uid, Json::Value &result);
	int Buy(unsigned uid, unsigned id, unsigned need, Json::Value &result);

private:
	void Restart();
	int InitCrowdFunding();
	DataCrowdFunding m_data;
	static map<unsigned, CrowdFundingConfigItme> m_CrowdFundingMap;
};

#endif /* DATACROWDFUNDING_H_ */
