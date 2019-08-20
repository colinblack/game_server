/*
 * DataQunXing.h
 *
 *  Created on: 2019年7月9日
 *      Author: Administrator
 */

#ifndef DATA_QUNXING_H_
#define DATA_QUNXING_H_

#include "Kernel.h"
#include "DataBase.h"
#include "ActivityQunXing.pb.h"

struct QunXingUser {
	uint32_t uid;
	set<uint32_t> hud;
	QunXingUser() {
		uid = 0;
		hud.clear();
	}
	void parse(const ActivityQunXing::User &msg) {
		uid = msg.uid();
		for (int i = 0; i < msg.heros_size(); ++i) {
			hud.insert(msg.heros(i));
		}
	}
	void serialize(ActivityQunXing::User *msg) {
		msg->set_uid(uid);
		set<uint32_t>::iterator itr = hud.begin();
		for (; itr != hud.end(); ++itr) {
			msg->add_heros(*itr);
		}
	}
};

struct QunXingGuest {
	uint32_t uid;
	uint32_t hid;
	uint32_t power;
	string name;
	string smid;
	string hname;

	QunXingGuest() {
		uid = 0;
		hid = 0;
		power = 0;
		name.clear();
		smid.clear();
		hname.clear();
	}

	void parse(const ActivityQunXing::Guest &msg) {
		uid = msg.uid();
		hid = msg.hid();
		power = msg.power();
		name = msg.name();
		smid = msg.smid();
		hname = msg.hname();
	}

	void serialize(ActivityQunXing::Guest *msg) {
		msg->set_uid(uid);
		msg->set_hid(hid);
		msg->set_power(power);
		msg->set_name(name);
		msg->set_smid(smid);
		msg->set_hname(hname);
	}
};

struct QunXingTable {
	uint32_t id;
	uint32_t type;
	uint32_t uid;
	uint32_t point;
	string name;
	vector<QunXingGuest> guests;

	QunXingTable() {
		id = 0;
		type = 0;
		uid = 0;
		point = 0;
		name.clear();
		guests.clear();
	}

	void parse(const ActivityQunXing::Table &msg) {
		id = msg.id();
		type = msg.type();
		uid = msg.uid();
		point = msg.point();
		name = msg.name();
		for (int i = 0; i < msg.guests_size(); ++i) {
			QunXingGuest item;
			item.parse(msg.guests(i));
			guests.push_back(item);
		}
	}

	void serialize(ActivityQunXing::Table *msg) {
		msg->set_id(id);
		msg->set_type(type);
		msg->set_uid(uid);
		msg->set_point(point);
		msg->set_name(name);
		vector<QunXingGuest>::iterator itr = guests.begin();
		for (; itr != guests.end(); ++itr) {
			itr->serialize(msg->add_guests());
		}
	}
};

struct DataQunXing {
	uint32_t ver;
	uint32_t ts;
	map<uint32_t, vector<QunXingTable> > tables;
	map<uint32_t, QunXingUser> users;

	DataQunXing() {
		ver = 0;
		ts = 0;
		tables.clear();
		users.clear();
	}

	void parse(const ActivityQunXing::QunXing *msg) {
		ver = msg->ver();
		ts = msg->ts();
		for (int i = 0; i < msg->tables_size(); ++i) {
			QunXingTable item;
			item.parse(msg->tables(i));
			vector<QunXingTable> &table = tables[item.type];
			table.push_back(item);
		}
		for (int i = 0; i < msg->users_size(); ++i) {
			QunXingUser item;
			item.parse(msg->users(i));
			users[item.uid] = item;
		}
	}

	void serialize(ActivityQunXing::QunXing *msg) {
		msg->set_ver(ver);
		msg->set_ts(ts);
		for (map<uint32_t, vector<QunXingTable> >::iterator itr = tables.begin(); itr != tables.end(); ++itr) {
			for (vector<QunXingTable>::iterator it = itr->second.begin(); it != itr->second.end(); ++it) {
				it->serialize(msg->add_tables());
			}
		}
		for (map<uint32_t, QunXingUser>::iterator itr = users.begin(); itr != users.end(); ++itr) {
			itr->second.serialize(msg->add_users());
		}
	}
	void Clear() {
		ver = 0;
		tables.clear();
		users.clear();
	}
};

class CDataQunXing : public DataBase {
public:
	CDataQunXing(const string &path);
	int Init();
	int Save();
	int Sig(int sig);
	int GetInfo(uint32_t uid, uint32_t type, Json::Value &result);
	int AddTable(uint32_t uid, uint32_t type, const string &name);
	int AddGuest(uint32_t id, uint32_t type, uint32_t hud, QunXingGuest &info, uint32_t &ledder);
	int DelGuest(uint32_t id, uint32_t type, uint32_t uid, uint32_t userid);
	int GetPoint(uint32_t uid, uint32_t &point);
	void CheckTs();
private:
	DataQunXing m_data;
};

#endif /* DATA_QUNXING_H_ */
