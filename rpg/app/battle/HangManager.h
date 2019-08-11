/*
 * HangManager.h
 *
 *  Created on: 2019年6月12日
 *      Author: Administrator
 */

#ifndef HANG_MANAGER_H_
#define HANG_MANAGER_H_

#include "BattleBaseInc.h"

#define DEFAULT_HANG_X 206
#define DEFAULT_HANG_Y 400
#define DEFAULT_HANG_MAP 10001

class HangManager: public CSingleton<HangManager> {
private:
	friend class CSingleton<HangManager>;
	HangManager();
	map<uint32_t, uint32_t> m_boss;

public:
	int Process(uint32_t uid, logins::SBatchFightResultReq *req, logins::SBatchFightResultResp *resp);
	int Process(uint32_t uid, logins::SHangChallengeBoss *req);
	int Process(uint32_t uid, logins::SFightResultReq *req, logins::SBatchFightResultResp *resp);

public:
	bool OnMonsterDie(uint32_t uid, uint32_t monster_id, const Point &diePos);
	bool OnHumanDie(uint32_t uid);
	bool MonsterDrop(uint32_t uid, uint32_t monster_id, const Point &diePos);
	bool GetHangMap(uint16_t hang, uint32_t &des_map, Point &des_pos);
	bool OfflineReward(uint32_t uid, uint32_t hang, uint32_t offlineTs);
	bool AfterLogin(uint32_t uid);
};

#endif /* HANG_MANAGER_H_ */
