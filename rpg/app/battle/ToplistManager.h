/*
 * ToplistManager.h
 *
 *  Created on: 2019年8月8日
 *      Author: colin
 *      tile: 排行榜
 */

#ifndef APP_BATTLE_TOPLISTMANAGER_H_
#define APP_BATTLE_TOPLISTMANAGER_H_

#include "BattleBaseInc.h"

enum ToplistType{
	TypeNearEnemy = 15   //血战四方击杀排名
};


class ToplistManager : public  CSingleton<ToplistManager>{
private:
	friend class CSingleton<ToplistManager>;
	ToplistManager();
	~ToplistManager();


public:
	int Process(uint32_t uid, logins::SGetTopListReq *req, msgs::SToplist *resp);


};



#endif /* APP_BATTLE_TOPLISTMANAGER_H_ */
