/*
 * CardManager.h
 *
 *  Created on: 2019年6月27日
 *      Author: Administrator
 */

#ifndef CARD_MANAGER_H_
#define CARD_MANAGER_H_

#include "BattleBaseInc.h"

#define CARD_ITEMID_BASE 320000000



class CardManager: public CSingleton<CardManager> {
private:
	friend class CSingleton<CardManager>;
	CardManager();
	~CardManager();
public:
	bool CalcProperty(const UserCache &cache, byte rid, PropertySets &props);

public:
	int Process(uint32_t uid, card::CSCardActiveCard *req);

public:
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SCardGroup *resp);

};

#endif /* CARD_MANAGER_H_ */
