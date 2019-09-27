/*
 * BossRankManager.h
 *
 *  Created on: 2019年2月26日
 *      Author: Administrator
 */

#ifndef BOSS_RANK_MANAGER_H_
#define BOSS_RANK_MANAGER_H_

#include "Kernel.h"
#include "PbMessage.h"

struct DataBossRank {
	uint32_t uid;
	uint64_t hurt;
	string name;

	DataBossRank() {
		uid = 0;
		hurt = 0;
		name.clear();
	}

	void Parse(const ProtoRankList::BossRankItem &msg) {
		uid = msg.uid();
		hurt = msg.hurt();
		name = msg.name();
	}

	void Serialize(ProtoRankList::BossRankItem *msg) {
		msg->set_uid(uid);
		msg->set_hurt(hurt);
		msg->set_name(name);
	}

	inline bool operator<=(const DataBossRank &data) const {
		return this->hurt <= data.hurt;
	}

	inline bool operator>(const DataBossRank &data) const {
		return this->hurt > data.hurt;
	}
};

class BossRankManager {
public:
	~BossRankManager();
	static BossRankManager* getInstance() {
		static BossRankManager _ins;
		return &_ins;
	}
	bool init();
	bool save();
	bool reset();
	bool addRank(uint32_t uid, uint64_t hurt, const string &name);
	bool encode(IBuffer *buff);
	bool onSecondTimer();
	bool isValidTime();

protected:
	BossRankManager();

private:
	uint32_t m_ts;
	bool m_flag;
	list<DataBossRank> m_ranks;
};

#endif /* BOSS_RANK_MANAGER_H_ */
