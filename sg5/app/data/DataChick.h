/*
 * DataChick.h
 *
 *  Created on: 2018年7月26日
 *      Author: Ralf
 */

#ifndef APP_DATA_DATACHICK_H_
#define APP_DATA_DATACHICK_H_


#include "Kernel.h"
#include "DataBase.h"
#include "DataNewWorld.h"

#define CHICK_HERO 10
#define CHICK_MAP 50
#define CHICK_USER 30
#define CHICK_EQUIP 60
#define CHICK_PATH "/data/release/chick/data/"
#define CHICK_SEASON 4
#define CHICK_REWARD 100

/**********************************************************/
class DataChickHero {
public:
	unsigned int level;
	vector<unsigned int> property;
	DataChickHero() {
		level = 0;
	}
	~DataChickHero() {
	}
	void Serialize(Chick::ChickHero *p) {
		p->set_level(level);
		for (vector<unsigned int>::iterator it = property.begin();it != property.end(); ++it)
			p->add_property(*it);
	}
	void Parse(const Chick::ChickHero &p) {
		level = p.level();
		for (int i = 0; i < p.property_size(); ++i)
			property.push_back(p.property(i));
	}

	void Get(Json::Value& t, pair<unsigned, unsigned>& p)
	{
		t["x"] = p.first;
		t["y"] = p.second;
		t["level"] = level;
		t["property"].resize(0);
		for(int i=0;i<NewWorldProperty_max;++i)
			t["property"].append(property[i]);
	}
};
class DataChickUser {
public:
	unsigned int uid;
	string name;
	string fig;
	unsigned level;
	DataChickHero hero;
	unsigned int zone;
	DataChickUser() {
		uid = 0;
		zone = 0;
		level = 0;
	}
	~DataChickUser() {
	}
	void Serialize(Chick::ChickUser *p) {
		p->set_uid(uid);
		p->set_name(name);
		p->set_fig(fig);
		p->set_level(level);
		hero.Serialize(p->mutable_hero());
		p->set_zone(zone);
	}
	void Parse(const Chick::ChickUser &p) {
		uid = p.uid();
		name = p.name();
		fig = p.fig();
		level = p.level();
		hero.Parse(p.hero());
		zone = p.zone();
	}

	void Get(Json::Value& t, pair<unsigned, unsigned>& p)
	{
		t["uid"] = uid;
		t["name"] = name;
		t["fig"] = fig;
		t["userlv"] = level;
		hero.Get(t, p);
	}
};
class DataChick {
public:
	map<unsigned int, DataChickUser> user;
	bool reg;
	DataChick():reg(false) {
	}
	~DataChick() {
	}
	void Serialize(Chick::Chick *p) {
		for (map<unsigned int, DataChickUser>::iterator it = user.begin();it != user.end(); ++it)
			it->second.Serialize(p->add_user());
		p->set_reg(reg);
	}
	void Parse(const Chick::Chick &p) {
		for (int i = 0; i < p.user_size(); ++i)
			user[p.user(i).uid()].Parse(p.user(i));
		reg = p.reg();
	}
};
/**********************************************************/

class CDataChick : public DataBaseT<Chick::Chick, DataChick>
{
public:
	CDataChick(string path):DataBaseT<Chick::Chick, DataChick>(path){}
	virtual ~CDataChick(){}
	int Sig(int sig);

	int GetChickReg(unsigned uid, Json::Value &res);
	int ChickReg(unsigned uid, Json::Value &data, Json::Value &res);

private:
	void start();
	void end();
};




#endif /* APP_DATA_DATACHICK_H_ */
