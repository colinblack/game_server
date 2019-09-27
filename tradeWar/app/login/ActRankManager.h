/*
 * ActRankManager.h
 *
 *  Created on: 2018年12月3日
 *      Author: Administrator
 */

#ifndef ACT_RANK_MANAGER_H_
#define ACT_RANK_MANAGER_H_

#define ACT_RANK_LEN 10

#include "Kernel.h"
#include "PbMessage.h"

struct ActRankItem {
	uint32_t uid;
	uint32_t value;
	string name;
	string pic;

	ActRankItem(): uid(0), value(0) {
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
	inline bool operator<=(const ActRankItem & item) const {
		return this->value <= item.value;
	}
	inline bool operator>(const ActRankItem & item) const {
		return this->value > item.value;
	}
};

struct ActRank {
	uint32_t id;
	uint32_t ver;
	uint32_t ts;
	bool reward;
	list<ActRankItem> data;

	ActRank() {
		id = 0;
		ver = 0;
		ts = 0;
		reward = false;
	}

	void Parse(const ProtoRankList::ActRankItem &msg) {
		this->id = msg.id();
		this->ver = msg.ver();
		this->ts = msg.ts();
		this->reward = msg.reward();
		for (int i = 0; i < msg.data_size(); ++i) {
			ActRankItem item;
			item.Parse(msg.data(i));
			data.push_back(item);
		}
	}

	void Serialize(ProtoRankList::ActRankItem *msg) {
		msg->set_id(this->id);
		msg->set_ver(this->ver);
		msg->set_ts(this->ts);
		msg->set_reward(this->reward);
		list<ActRankItem>::iterator itr = data.begin();
		for (; itr != data.end() && msg->data_size() < ACT_RANK_LEN; ++itr) {
			itr->Serialize(msg->add_data());
		}
	}

	void AddItem(const ActRankItem &item) {
		list<ActRankItem>::iterator iter;
		for (iter = data.begin(); iter != data.end(); ++iter) {
			if (iter->uid == item.uid) {
				if (iter->value == item.value) {
					return;
				}
				data.erase(iter);
				break;
			}
		}
		if (data.size() >= ACT_RANK_LEN && item.value < data.back().value) {
			return;
		}
		for (iter = data.begin(); iter != data.end() && (item.value <= iter->value); ++iter) {
		}
		data.insert(iter, item);
		if (data.size() > ACT_RANK_LEN) {
			data.pop_back();
		}
	}

	bool Packet(IBuffer *buff) {
		if (buff == NULL) {
			return false;
		}
		CBufferWriter writer(buff);
		PACKET_ENCODE(UInt32, data.size());
		list<ActRankItem>::iterator itr = data.begin();
		for (; itr != data.end(); ++itr) {
			PACKET_ENCODE(UInt32, itr->uid);
			PACKET_ENCODE(UInt32, itr->value);
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

class ActRankManager {
public:
	static ActRankManager* getInstance() {
		static ActRankManager _inc;
		return &_inc;
	}
	virtual ~ActRankManager();
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
	bool onSecondTimer();
	bool doReward(uint32_t type);
	bool doArenaReward();
	bool isValid(uint32_t type);
protected:
	ActRankManager();
	uint32_t getActId(uint32_t type);
	bool getDelay(uint32_t type);
private:
	map<uint32_t, ActRank> m_ranks;
};

#endif /* ACT_RANK_MANAGER_H_ */
