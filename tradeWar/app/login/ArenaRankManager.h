/*
 * ArenaRankManager.h
 *
 *  Created on: 2019年2月27日
 *      Author: Administrator
 */

#ifndef ARENA_RANK_MANAGER_H_
#define ARENA_RANK_MANAGER_H_

#include "Kernel.h"
#include "PbMessage.h"

#define ARENA_RANK_MAX 1000
#define ARENA_RANK_MIN 1
#define ARENA_RANK_INVALID 1001

class ArenaRankManager {
public:
	virtual ~ArenaRankManager();
	static ArenaRankManager* getInstance() {
		static ArenaRankManager _ins;
		return &_ins;
	}
	bool init();
	bool save();
	bool onSecondTimer();
	/**
	 * @param
	 * uid: attacker uid
	 * ouid: defender uid
	 * r: attack rank
	 * sor: attacker old rank
	 * onr: defender new rank
	 */
	bool setRank(uint32_t uid, uint32_t ouid, uint32_t r, uint32_t &sor, uint32_t &onr);
	bool doRefresh(uint32_t id, vector<uint32_t> &ids);
	bool getUid(uint32_t id, uint32_t &uid);
	bool packetTop(IBuffer *buff, bool act = false);
	uint32_t getUserRank(uint32_t uid) const;

	inline static bool IsValidArenaRank(uint32_t r) {
		return r >= ARENA_RANK_MIN && r <= ARENA_RANK_MAX;
	}
	const vector<uint32_t>& getRankData(){
		return m_ranks;
	}
protected:
	ArenaRankManager();

private:
	vector<uint32_t> m_ranks;
	map<uint32_t, uint32_t> m_userHash;
	bool m_flag;
};

#endif /* ARENA_RANK_MANAGER_H_ */
