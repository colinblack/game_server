/*
 * NearEnemy.h
 *
 *  Created on: 2019年8月2日
 *      Author: colin
 */

#ifndef APP_BATTLE_NEARENEMY_H_
#define APP_BATTLE_NEARENEMY_H_

#include "BattleBaseInc.h"
#include "MapMoveObject.h"


class NearEnemy: public StdMonster {
public:
	NearEnemy();
	virtual ~NearEnemy();
	bool init(const UserCache &cache, byte rid, uint32_t fbId, uint32_t mapId, const Point &p);
	virtual Msg* doAppear();
	virtual bool recove();
	bool doUseSkill(int32_t skillId, vector<uint32_t> &tar, const Point &cen);
private:
	uint32_t uid_;

public:
	uint32_t getUid() {
		return id_;
	}
};





#endif /* APP_BATTLE_NEARENEMY_H_ */
