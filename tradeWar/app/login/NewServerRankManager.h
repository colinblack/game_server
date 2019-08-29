/*
 * NewServerRankManager.h
 *
 *  Created on: 2018年12月3日
 *      Author: Administrator
 */

#ifndef NEW_SERVER_RANK_MANAGER_H_
#define NEW_SERVER_RANK_MANAGER_H_

#define NEW_SERVER_RANK_LEN 50

#include "Kernel.h"
#include "PbMessage.h"

struct NewServerRankItem {
	uint32_t uid;
	uint32_t value;
	string name;
	string pic;

	NewServerRankItem(): uid(0), value(0) {
	}
	void Parse(const ProtoRankList::RankItem &msg) {
		uid = msg.uid();
		value = msg.value();
		name = msg.name();
		pic = msg.pic();
	}
	void Serialize(ProtoRankList::RankItem *msg) {
		msg->set_uid(uid);
		msg->set_value(value);
		msg->set_name(name);
		msg->set_pic(pic);
	}
	inline bool operator<=(const NewServerRankItem & item) const {
		return this->value <= item.value;
	}
	inline bool operator>(const NewServerRankItem & item) const {
		return this->value > item.value;
	}
};

struct NewServerRank {
	uint32_t id;
	uint32_t ver;
	uint32_t ts;
	bool reward;
	list<NewServerRankItem> data;

	NewServerRank() {
		id = 0;
		ver = 0;
		ts = 0;
		reward = false;
	}

	void Parse(const ProtoRankList::NewServerRankItem &msg) {
		this->id = msg.id();
		this->ver = msg.ver();
		this->ts = msg.ts();
		this->reward = msg.reward();
		for (int i = 0; i < msg.data_size(); ++i) {
			NewServerRankItem item;
			item.Parse(msg.data(i));
			data.push_back(item);
		}
	}

	void Serialize(ProtoRankList::NewServerRankItem *msg) {
		msg->set_id(this->id);
		msg->set_ver(this->ver);
		msg->set_ts(this->ts);
		msg->set_reward(this->reward);
		list<NewServerRankItem>::iterator itr = data.begin();
		for (; itr != data.end() && msg->data_size() < NEW_SERVER_RANK_LEN; ++itr) {
			itr->Serialize(msg->add_data());
		}
	}

	void AddItem(const NewServerRankItem &item) {
		list<NewServerRankItem>::iterator iter;
		for (iter = data.begin(); iter != data.end(); ++iter) {
			if (iter->uid == item.uid) {
				if (iter->value == item.value) {
					return;
				}
				data.erase(iter);
				break;
			}
		}
		if (data.size() >= NEW_SERVER_RANK_LEN && item.value < data.back().value) {
			return;
		}
		for (iter = data.begin(); iter != data.end() && (item.value <= iter->value); ++iter) {
		}
		data.insert(iter, item);
		if (data.size() > NEW_SERVER_RANK_LEN) {
			data.pop_back();
		}
	}

	bool Packet(IBuffer *buff) {
		if (buff == NULL) {
			return false;
		}
		CBufferWriter writer(buff);
		PACKET_ENCODE(UInt32, data.size());
		list<NewServerRankItem>::iterator itr = data.begin();
		for (; itr != data.end(); ++itr) {
			PACKET_ENCODE(UInt32, itr->uid);
			PACKET_ENCODE(UInt32, itr->value);
			String::Utf8Regularize(itr->name);
			PACKET_ENCODE(String, itr->name);
			PACKET_ENCODE(Byte, 0);
			PACKET_ENCODE(String, itr->pic);
			PACKET_ENCODE(Byte, 0);
		}
		return true;
	}

	void Clear() {
		reward = false;
		data.clear();
	}
};

class NewServerRankManager {
public:
	static NewServerRankManager* getInstance() {
		static NewServerRankManager _inc;
		return &_inc;
	}
	virtual ~NewServerRankManager();
	bool init();
	bool save();
	bool reset();
	bool getData(uint32_t type, IBuffer *buff);
	bool setData(uint32_t uid, uint32_t type, uint32_t v);
	bool addSoldier(uint32_t uid, uint32_t v);
	bool addExp(uint32_t uid, uint32_t v);
	bool addPower(uint32_t uid, uint32_t v);
	bool addTransport(uint32_t uid, uint32_t v);
	bool addConsume(uint32_t uid, uint32_t v);
	bool addGem(uint32_t uid, uint32_t v);
	bool addCoins(uint32_t uid, uint32_t v);
	bool onTimer();
	bool doReward(uint32_t type, bool daily);
	bool doWorldBattleReward();
	bool isValid(uint32_t type);
protected:
	NewServerRankManager();
	uint32_t getActId(uint32_t type);
private:
	map<uint32_t, NewServerRank> m_ranks;
	uint32_t m_ts;
};

#endif /* NEW_SERVER_RANK_MANAGER_H_ */
