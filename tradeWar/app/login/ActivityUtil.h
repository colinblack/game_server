/*
 * ActivityUtil.h
 *
 *  Created on: 2018年12月3日
 *      Author: Administrator
 */

#ifndef ACTIVITY_UTIL_H_
#define ACTIVITY_UTIL_H_

#include "Kernel.h"
#include "DataActivity.h"
#include "Award.h"

class ActivityUtil {
public:
	ActivityUtil(uint32_t uid, uint32_t id);
	virtual ~ActivityUtil();
	virtual bool doReward(uint32_t index) = 0;
	virtual bool doLottery(uint32_t cnt);
	virtual bool checkVer();
	virtual bool loadData();
	virtual bool saveData();
	virtual bool encodeData(IBuffer *buff);
	virtual bool getRewardFlag(uint32_t index);
	virtual bool setRewardFlag(uint32_t index);
	virtual bool dailyReset();
	virtual uint32_t getChargeDay();
	virtual uint32_t getDailyCharge();
	virtual uint32_t getScore();
	virtual bool getLotteryResult(IBuffer *buff);
	virtual bool addScore(uint32_t c);
	virtual bool setScore(uint32_t c);
	virtual bool parseReward(const Award &award);
	virtual bool getReward(IBuffer *buff);
	virtual bool canReward();
	virtual bool getNotify();
	virtual bool setNotify(bool f);
protected:
	uint32_t m_uid;
	uint32_t m_id;
	vector<uint32_t> m_lotteryId;
	bool m_isNew;
	bool m_notify;
	DataActivity m_data;
	Award m_reward;
	Award m_box;
	Award m_normal;
};

class ActNewSrvRankBase: public ActivityUtil {
public:
	ActNewSrvRankBase(uint32_t uid, uint32_t id, uint32_t rid, bool daily, bool isNew, bool isDelay): ActivityUtil(uid, id) {
		m_rank_id = rid;
		m_daily = daily;
		m_new_srv = isNew;
		m_delay = isDelay;
	}
	virtual bool doReward(uint32_t index);
	virtual bool encodeData(IBuffer *buff);
	virtual bool addScore(uint32_t c);
	virtual bool setScore(uint32_t c);
	virtual const void* getConfig(uint32_t index);
	virtual bool canReward();
protected:
	uint32_t m_rank_id;
	bool m_daily;
	bool m_new_srv;
	bool m_delay;
};

class ActNewSrvExpRank: public ActNewSrvRankBase {
public:
	ActNewSrvExpRank(uint32_t uid): ActNewSrvRankBase(uid, e_ActivityTypeExpRank, NEW_SERVER_RANK_TYPE_EXP, false, true, false) {
	}
};

class ActNewSrvPowerRank: public ActNewSrvRankBase {
public:
	ActNewSrvPowerRank(uint32_t uid): ActNewSrvRankBase(uid, e_ActivityTypePowerRank, NEW_SERVER_RANK_TYPE_POWER, false, true, false) {
	}
};

class ActNewSrvTransportRank: public ActNewSrvRankBase {
public:
	ActNewSrvTransportRank(uint32_t uid): ActNewSrvRankBase(uid, e_ActivityTypeTransportRank, NEW_SERVER_RANK_TYPE_TRANSPORT, false, true, false) {
	}
};

class ActNewSrvConsumeRank: public ActNewSrvRankBase {
public:
	ActNewSrvConsumeRank(uint32_t uid): ActNewSrvRankBase(uid, e_ActivityTypeConsumeRank, NEW_SERVER_RANK_TYPE_CONSUME, false, true, false) {
	}
};

class ActNewSrvSoldierRank: public ActNewSrvRankBase {
public:
	ActNewSrvSoldierRank(uint32_t uid): ActNewSrvRankBase(uid, e_ActivityTypeSoldierRank, NEW_SERVER_RANK_TYPE_SOLDIER, false, true, false) {
	}
};

class ActNewSrvGemRank: public ActNewSrvRankBase {
public:
	ActNewSrvGemRank(uint32_t uid): ActNewSrvRankBase(uid, e_ActivityTypeGemRank, NEW_SERVER_RANK_TYPE_GEM, false, true, false) {
	}
};

class ActNewSrvCoinsRank: public ActNewSrvRankBase {
public:
	ActNewSrvCoinsRank(uint32_t uid): ActNewSrvRankBase(uid, e_ActivityTypeCoinsRank, NEW_SERVER_RANK_TYPE_COINS, true, true, false) {
	}
	const void* getConfig(uint32_t index);
};

class ActNewSrvWorldBattleRank: public ActNewSrvRankBase {
public:
	ActNewSrvWorldBattleRank(uint32_t uid): ActNewSrvRankBase(uid, e_ActivityTypeWorldBattleRank, NEW_SERVER_RANK_TYPE_WORLD_BATTLE, false, true, false) {
	}
};

class ActSoldierRank: public ActNewSrvRankBase {
public:
	ActSoldierRank(uint32_t uid): ActNewSrvRankBase(uid, e_ActivityTypeSoldierRankNew, ACT_RANK_TYPE_SOLDIER, false, false, true) {
	}
};

class ActExpRank: public ActNewSrvRankBase {
public:
	ActExpRank(uint32_t uid): ActNewSrvRankBase(uid, e_ActivityTypeExpRankNew, ACT_RANK_TYPE_EXP, false, false, true) {
	}
};

class ActPowerRank: public ActNewSrvRankBase {
public:
	ActPowerRank(uint32_t uid): ActNewSrvRankBase(uid, e_ActivityTypePowerRankNew, ACT_RANK_TYPE_POWER, false, false, true) {
	}
	virtual bool addScore(uint32_t c);
};

class ActBoatRank: public ActNewSrvRankBase {
public:
	ActBoatRank(uint32_t uid): ActNewSrvRankBase(uid, e_ActivityTypeBoatRankNew, ACT_RANK_TYPE_BOAT, false, false, true) {
	}
};

class ActConsumeRank: public ActNewSrvRankBase {
public:
	ActConsumeRank(uint32_t uid): ActNewSrvRankBase(uid, e_ActivityTypeConsumeRankNew, ACT_RANK_TYPE_CONSUME, false, false, true) {
	}
};

class ActArenaRank: public ActNewSrvRankBase {
public:
	ActArenaRank(uint32_t uid): ActNewSrvRankBase(uid, e_ActivityTypeArenaRankNew, ACT_RANK_TYPE_ARENA, false, false, true) {
	}
	bool encodeData(IBuffer *buff);
};

class ActSevenTask : public ActivityUtil {
public:
	enum {
		ActSevenTaskZhengWu = 2,
		ActSevenTaskAR2 = 5,
		ActSevenTaskSoldier = 7,
		ActSevenTaskTR2 = 11
	};
	enum {
		ActSevenTaskDailyLen = 3,
		ActSevenTaskWeekLen = 7
	};
	struct ActDataSevenTaskDaily {
		uint32_t id;
		uint32_t count;
		uint8_t  reward;
		ActDataSevenTaskDaily() {
			id = 0;
			count = 0;
			reward = 0;
		}
		void Clear() {
			id = 0;
			count = 0;
			reward = 0;
		}
	};
	struct ActDataSevenTaskWeek {
		uint32_t cnt;
		uint8_t lv;
		ActDataSevenTaskWeek() {
			cnt = 0;
			lv = 0;
		}
		void Clear() {
			cnt = 0;
			lv = 0;
		}
	};
	struct ActDataSevenTask {
		uint8_t  buy_flag;
		uint32_t ver;
		uint32_t ts;
		uint32_t score;
		uint32_t free_reward;
		uint32_t buy_reward;
		ActDataSevenTaskWeek week[ActSevenTaskWeekLen];
		ActDataSevenTaskDaily daily[ActSevenTaskDailyLen];

		ActDataSevenTask() {
			buy_flag = 0;
			ver = 0;
			ts = 0;
			score = 0;
			free_reward = 0;
			buy_reward = 0;
		}

		void Clear() {
			ver = 0;
			ts = 0;
			score = 0;
			free_reward = 0;
			buy_reward = 0;
			for (int i = 0; i < ActSevenTaskWeekLen; ++i) {
				week[i].Clear();
			}
			for (int i = 0; i < ActSevenTaskDailyLen; ++i) {
				daily[i].Clear();
			}
		}
	};
	ActSevenTask(uint32_t uid);
	bool doReward(uint32_t index) {
		return false;
	}
	bool doLevelReward(uint32_t type, uint32_t index);
	bool doQuestReward(bool daily, uint32_t id);
	bool doBuyScore();
	bool doAddCount(uint32_t id, uint32_t count, bool daily);
	bool doQuest(uint32_t quest, uint32_t cnt);
	bool setBuyFlag();
	bool checkVer();
	bool loadData();
	bool saveData();
	bool encodeData(IBuffer *buff);
private:
	ActDataSevenTask m_act_data;
};

/*
 * @每日大礼包
 */
class ActDailyBuyBag: public ActivityUtil {
public:
	ActDailyBuyBag(uint32_t uid, uint32_t id, bool is_new): ActivityUtil(uid, id) {
		m_new_srv = is_new;
	}
	bool doReward(uint32_t index);
	bool encodeData(IBuffer *buff);
	bool canReward();
	bool getReward(IBuffer *buff);
protected:
	bool m_new_srv;
};

/*
 * @每日充值返物品
 */
class ActDailyChargeEquip: public ActivityUtil {
public:
	ActDailyChargeEquip(uint32_t uid, uint32_t id, bool is_new): ActivityUtil(uid, id) {
		m_new_srv = is_new;
	}
	bool doReward(uint32_t index);
	bool encodeData(IBuffer *buff);
	bool canReward();
protected:
	bool m_new_srv;
};

/*
 * @每日充值返钻石
 */
class ActDailyChargeCash: public ActivityUtil {
public:
	ActDailyChargeCash(uint32_t uid, uint32_t id, bool is_new):ActivityUtil(uid, id) {
		m_new_srv = is_new;
	}
	bool doReward(uint32_t index);
	bool encodeData(IBuffer *buff);
	bool canReward();
protected:
	bool m_new_srv;
};

/*
 * @连续充值
 */
class ActContinueCharge: public ActivityUtil {
public:
	ActContinueCharge(uint32_t uid, uint32_t id, bool is_new):ActivityUtil(uid, id) {
		m_new_srv = is_new;
	}
	bool doReward(uint32_t index);
	bool encodeData(IBuffer *buff);
	bool canReward();
protected:
	bool m_new_srv;
};

/*
 * @每日寻宝
 */
class ActLuckyLottery: public ActivityUtil {
public:
	ActLuckyLottery(uint32_t uid):ActivityUtil(uid, e_ActivityTypeLuckyLottery) {
	}
	bool doReward(uint32_t index);
	bool doLottery(uint32_t cnt);
	bool encodeData(IBuffer *buff);
};

#endif /* ACTIVITY_UTIL_H_ */

