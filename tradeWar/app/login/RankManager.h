/*
 * RankManager.h
 *
 *  Created on: 2015-12-16
 *      Author: nick
 */

#ifndef RANK_MANAGER_H_
#define RANK_MANAGER_H_

#include "Kernel.h"
#include "NetPacket.h"
#include "PbMessage.h"

#define ALL_RANK_LV 1000

struct RankExp {
	uint32_t uid;
	uint32_t exp;
	string name;
	string pic;

	RankExp(): uid(0), exp(0) {
	}
	void Parse(const ProtoRankList::RankItem &msg) {
		uid = msg.uid();
		exp = msg.value();
		name = msg.name();
		pic = msg.pic();
	}
	void Serialize(ProtoRankList::RankItem *msg) {
		msg->set_uid(uid);
		msg->set_value(exp);
		msg->set_name(name);
		msg->set_pic(pic);
	}
	inline bool operator<=(const RankExp & item) const {
		return this->exp <= item.exp;
	}
	inline bool operator>(const RankExp & item) const {
		return this->exp > item.exp;
	}
};

struct RankCombat {
	uint32_t uid;
	uint32_t combat;
	string name;
	string pic;

	RankCombat() : uid(0), combat(0){
	}
	void Parse(const ProtoRankList::RankItem &msg) {
		uid = msg.uid();
		combat = msg.value();
		name = msg.name();
		pic = msg.pic();
	}
	void Serialize(ProtoRankList::RankItem *msg) {
		msg->set_uid(uid);
		msg->set_value(combat);
		msg->set_name(name);
		msg->set_pic(pic);
	}
	inline bool operator<=(const RankCombat & item) const {
		return this->combat <= item.combat;
	}
	inline bool operator>(const RankCombat & item) const {
		return this->combat > item.combat;
	}
};

struct RankTransport {
	uint32_t uid;
	uint32_t res;
	string name;
	string pic;

	RankTransport() : uid(0), res(0){
	}
	void Parse(const ProtoRankList::RankItem &msg) {
		uid = msg.uid();
		res = msg.value();
		name = msg.name();
		pic = msg.pic();
	}
	void Serialize(ProtoRankList::RankItem *msg) {
		msg->set_uid(uid);
		msg->set_value(res);
		msg->set_name(name);
		msg->set_pic(pic);
	}
	inline bool operator<=(const RankTransport & item) const {
		return this->res <= item.res;
	}
	inline bool operator>(const RankTransport & item) const {
		return this->res > item.res;
	}
};

class RankManager {
public:
	static RankManager* getInstance() {
		static RankManager rankManager;
		return &rankManager;
	}
	~RankManager();
	bool init();
	bool save();
	bool doPacket(CNetPacket *packet);
	bool onLogin(uint32_t uid);
	bool onOffline(uint32_t uid);
	bool addRankExp(uint32_t uid);
	bool addRankCombat(uint32_t uid);
	bool addRankTransport(uint32_t uid);
	bool onLevelChange(uint32_t uid, uint32_t old);
protected:
	RankManager();
private:
	bool doQueryRankExp(CNetPacket *packet);
	bool doQueryRankCombat(CNetPacket *packet);
	bool doQueryRankTransport(CNetPacket *packet);
	bool sendRankExp(uint32_t uid, uint32_t v, uint32_t lv);
	bool sendRankCombat(uint32_t uid, uint32_t v, uint32_t lv);
	bool sendRankTransport(uint32_t uid, uint32_t v, uint32_t lv);
	bool initRankExp();
	bool initRankCombat();
	bool initRankTransport();
	bool saveRankExp();
	bool saveRankCombat();
	bool saveRankTransport();
	bool getDataPath(const string &name, string &path);
	bool noticeRank(uint32_t uid, uint32_t type, uint32_t rank);
	bool resetTransport();
private:
	template<typename DataType>
	uint32_t findItem(list<DataType>& data, uint32_t uid);

	template<typename DataType>
	uint32_t delItem(list<DataType>& data, uint32_t uid);

	template<typename DataType>
	uint32_t addItem(list<DataType>& data, const DataType& item, uint32_t max_size = MAX_RANK_SIZE);
private:
	map<uint32_t, list<RankExp> > m_rankExp;
	map<uint32_t, list<RankCombat> > m_rankCombat;
	map<uint32_t, list<RankTransport> > m_rankTransport;
	uint32_t m_transport_reset_ts;
};

template<typename DataType>
uint32_t RankManager::findItem(list<DataType>& data, uint32_t uid) {
	if (data.empty()) {
		return 0;
	}
	uint32_t rank = 1;
	typename list<DataType>::iterator iter = data.begin();
	for (; iter != data.end(); ++iter, ++rank) {
		if (iter->uid == uid) {
			return rank;
		}
	}
	return 0;
}

template<typename DataType>
uint32_t RankManager::delItem(list<DataType>& data, uint32_t uid) {
	if (data.empty()) {
		return 0;
	}
	uint32_t rank = 1;
	typename list<DataType>::iterator iter = data.begin();
	for (; iter != data.end(); ++iter, ++rank) {
		if (iter->uid == uid) {
			data.erase(iter);
			return rank;
		}
	}
	return 0;
}

template<typename DataType>
uint32_t RankManager::addItem(list<DataType>& data, const DataType& item, uint32_t max_size) {
	uint32_t rank = 0;
	typename list<DataType>::iterator iter = data.begin();
	for (; iter != data.end() && (item <= *iter); ++iter, ++rank) {
	}
	data.insert(iter, item);
	if (data.size() > max_size) {
		data.pop_back();
	}
	return rank > max_size ? 0 : rank;
}

#endif /* RANK_MANAGER_H_ */
