/*
 * ZhanLingManager.h
 *
 *  Created on: 2019年7月20日
 *      Author: Administrator
 */

#ifndef ZHAN_LING_MANAGER_H_
#define ZHAN_LING_MANAGER_H_

#include "BattleBaseInc.h"

#define ZHAN_LING_UNLOCK_MISSION 100009
#define ZHAN_LING_MAX_NUQI 10000
#define ZHAN_LING_MAX_NUQI_SUB 1500
#define ZHAN_LING_MAX_NUQI_SPEED 169
#define ZHAN_LING_SKILL_START 13000001

class ZhanLingManager: public CSingleton<ZhanLingManager> {
private:
	friend class CSingleton<ZhanLingManager>;
	ZhanLingManager();
	~ZhanLingManager();
	map<uint32_t, uint16_t> m_recover;

public:
	bool ActorLogin(uint32_t uid);
	bool checkUnlock(uint32_t uid);
	bool onChangeMap(uint32_t uid);
	bool onSecondTimer();
	bool setNuQi(uint32_t uid, uint32_t nuqi);
	bool updateNuQi(uint32_t uid, uint32_t nuqi);
	bool useNuQi(uint32_t uid);
public:
	int Process(uint32_t uid, logins::SSkillCleanNuQi *req);

public:
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SZhanlingInfo *resp);
};

#endif /* ZHAN_LING_MANAGER_H_ */
