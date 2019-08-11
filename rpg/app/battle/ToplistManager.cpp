/*
 * ToplistManager.cpp
 *
 *  Created on: 2019年8月8日
 *      Author: colin
 */

#include "BattleInc.h"

ToplistManager::ToplistManager(){
}


ToplistManager::~ToplistManager(){
}


int ToplistManager::Process(uint32_t uid, logins::SGetTopListReq *req,msgs::SToplist *resp) {
	uint32_t toplistType = req->toplistType;
	uint32_t ret = 0;

	switch (toplistType) {
	case TypeNearEnemy:
		ret = NearEnemyManager::Instance()->killEnemyRank(uid, resp);
		break;
	default:
		break;
	}

	return ret;
}



