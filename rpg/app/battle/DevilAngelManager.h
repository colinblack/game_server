/*
 * DevilAngelManager.h
 *
 *  Created on: 2019年7月23日
 *      Author: next
 */

#ifndef _DEVIL_ANGEL_MANAGER_H_
#define _DEVIL_ANGEL_MANAGER_H_

#include "BattleBaseInc.h"

class DevilAngelManager: public CSingleton<DevilAngelManager>{
private:
	friend class CSingleton<DevilAngelManager>;
	DevilAngelManager();
public:
	bool addDevilAngeleInfo(UserCache& cache, uint32_t equipId, uint32_t rid);
	bool onSecondTimer();
	bool DevilAngelTimeEnd(UserCache &cache);
	//恶魔天使
	int Process(uint32_t uid, logins::SBuyReq *req);
	int Process(uint32_t uid, logins::SDevilAngelequipReq *req);
public:
	int Sync(const UserCache & cache, uint32_t cmd, msgs::SDevilAngelDate *resp);
};

#endif /*_DEVIL_ANGEL_MANAGER_H_*/
