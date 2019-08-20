/*
 * DataQunXing.cpp
 *
 *  Created on: 2019年7月9日
 *      Author: Administrator
 */

#include "DataQunXing.h"
#include "ConfigWrap.h"
#include "ActivityConfig.h"

CDataQunXing::CDataQunXing(const string &path) : DataBase(path) {
	m_msg = new ActivityQunXing::QunXing();
}

int CDataQunXing::Init() {
	int ret = 0;
	ret = Parse();
	if (ret) {
		return ret;
	}

	m_data.parse((ActivityQunXing::QunXing *) m_msg);

	((ActivityQunXing::QunXing *) m_msg)->Clear();

	return 0;
}

int CDataQunXing::Save() {
	int ret = 0;
	m_data.serialize((ActivityQunXing::QunXing *) m_msg);
	ret = Serialize();
	if (ret) {
		return ret;
	}

	((ActivityQunXing::QunXing *) m_msg)->Clear();

	return 0;
}

int CDataQunXing::Sig(int sig) {
	return 0;
}

int CDataQunXing::GetInfo(uint32_t uid, uint32_t type, Json::Value &result) {
	CheckTs();
	result["tables"] = Json::Value(Json::arrayValue);
	const vector<QunXingTable> &temp = m_data.tables[type];
	vector<QunXingGuest>::const_iterator it;
	for (vector<QunXingTable>::const_iterator itr = temp.begin(); itr != temp.end(); ++itr) {
		Json::Value item;
		item["id"] = itr->id;
		item["uid"] = itr->uid;
		item["point"] = itr->point;
		item["name"] = itr->name;
		item["user"] = Json::Value(Json::arrayValue);
		for (it = itr->guests.begin(); it != itr->guests.end(); ++it) {
			Json::Value user;
			user["uid"] = it->uid;
			user["hid"] = it->hid;
			user["power"] = it->power;
			user["name"] = it->name;
			user["smid"] = it->smid;
			user["hname"] = it->hname;
			item["user"].append(user);
		}
		result["tables"].append(item);
	}
	result["heros"] = Json::Value(Json::arrayValue);
	map<uint32_t, QunXingUser>::iterator user_itr = m_data.users.find(uid);
	if (user_itr == m_data.users.end()) {
		return 0;
	}
	const QunXingUser &user = user_itr->second;
	for (set<uint32_t>::const_iterator itr = user.hud.begin(); itr != user.hud.end(); ++itr) {
		result["heros"].append(*itr);
	}
	return 0;
}

int CDataQunXing::AddTable(uint32_t uid, uint32_t type, const string &name) {
	CheckTs();
	vector<QunXingTable> &temp = m_data.tables[type];
	vector<QunXingTable>::iterator itr = temp.begin();
	for (; itr != temp.end(); ++itr) {
		if (itr->uid == uid) {
			return R_ERR_DATA;
		}
	}
	QunXingTable item;
	item.uid = uid;
	item.id = temp.size() + 1;
	item.type = type;
	item.name = name;
	temp.push_back(item);
	return 0;
}

int CDataQunXing::AddGuest(uint32_t id, uint32_t type, uint32_t hud, QunXingGuest &info, uint32_t &ledder) {
	uint32_t uid = info.uid;
	CheckTs();
	vector<QunXingTable> &temp = m_data.tables[type];
	vector<QunXingTable>::iterator itr = temp.begin();
	for (; itr != temp.end(); ++itr) {
		if (itr->id == id) {
			break;
		}
	}
	if (itr == temp.end()) {
		error_log("can not find table id id=%u type=%u", id, type);
		return R_ERROR;
	}

	if (itr->guests.size() > 8) {
		error_log("guest size limit id=%u type=%u", id, type);
		return R_ERROR;
	}

	const WuhunActivity::QunXingHuiJu &cfg = WuhunActivityWrap().GetQunXingHuiJu();
	if (itr->point >= cfg.yanhui(type).point()) {
		error_log("point full id=%u type=%u hold=%u max=%u", id, type, itr->point, cfg.yanhui(type).point());
		return R_ERROR;
	}

	QunXingUser &user = m_data.users[uid];
	user.uid = uid;
	if (user.hud.count(hud)) {
		error_log("the hero has used id=%u type=%u hud=%u", id, type, hud);
		return R_ERROR;
	}

	vector<QunXingGuest>::iterator gItr;
	for (gItr = itr->guests.begin(); gItr != itr->guests.end(); ++gItr) {
		if (gItr->uid == uid) {
			error_log("the user is in guest id=%u type=%u uid=%u", id, type, uid);
			return R_ERROR;
		}
	}

	itr->guests.push_back(info);
	ledder = itr->uid;
	user.hud.insert(hud);


	unsigned point = 0;
	for (int i = 0; i < cfg.zhanli_size(); ++i) {
		if (cfg.zhanli(i).zone_size() != 2) {
			continue;
		}
		if (info.power >= cfg.zhanli(i).zone(0) && info.power < cfg.zhanli(i).zone(1)) {
			point = cfg.zhanli(i).point();
			break;
		}
	}

	if (itr->point + point > cfg.yanhui(type).point()) {
		itr->point = cfg.yanhui(type).point();
	} else {
		itr->point += point;
	}
	return 0;
}

int CDataQunXing::DelGuest(uint32_t id, uint32_t type, uint32_t uid, uint32_t userid) {
	CheckTs();
	vector<QunXingTable> &temp = m_data.tables[type];
	vector<QunXingTable>::iterator itr = temp.begin();
	for (; itr != temp.end(); ++itr) {
		if (itr->id == id) {
			break;
		}
	}
	if (itr == temp.end()) {
		error_log("can not find table id id=%u type=%u", id, type);
		return R_ERROR;
	}
	if (itr->uid != uid) {
		error_log("user is not leader id=%u type=%u uid=%u leader=%u", id, type, uid, itr->uid);
		return R_ERROR;
	}
	const WuhunActivity::QunXingHuiJu &cfg = WuhunActivityWrap().GetQunXingHuiJu();
	if (itr->point >= cfg.yanhui(type).point()) {
		error_log("point full id=%u type=%u hold=%u max=%u", id, type, itr->point, cfg.yanhui(type).point());
		return R_ERROR;
	}
	vector<QunXingGuest>::iterator gItr;
	for (gItr = itr->guests.begin(); gItr != itr->guests.end(); ++gItr) {
		if (gItr->uid == userid) {
			itr->guests.erase(gItr);
			break;
		}
	}
	return 0;
}

int CDataQunXing::GetPoint(uint32_t uid, uint32_t &point) {
	map<uint32_t, vector<QunXingTable> >::const_iterator itr = m_data.tables.begin();
	vector<QunXingTable>::const_iterator tItr;
	for (; itr != m_data.tables.end(); ++itr) {
		const vector<QunXingTable> &ta = itr->second;
		for (tItr = ta.begin(); tItr != ta.end(); ++tItr) {
			if (tItr->uid == uid) {
				point += tItr->point;
			}
		}
	}
	return 0;
}

void CDataQunXing::CheckTs() {
	ActInfoConfig actTime(ACTIVITY_TIME_QUNXING);
	if (m_data.ver != actTime.Version()) {
		m_data.Clear();
		m_data.ver = actTime.Version();
		m_data.ts = Time::GetGlobalTime();
		return;
	}

	if (!CTime::IsDiffDay(m_data.ts, Time::GetGlobalTime())) {
		return;
	}
	m_data.ts = Time::GetGlobalTime();
	m_data.users.clear();
}
