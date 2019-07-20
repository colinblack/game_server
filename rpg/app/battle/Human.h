#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "BattleBaseInc.h"
#include "MapMoveObject.h"

class Human: public MapMoveObject {
public:
	Human();
	virtual ~Human();
	bool init(const UserCache &cache, byte rid);
	virtual bool propsCalc();
	virtual bool initSkill();
	virtual void onDie();
	virtual void onSetPos();
	virtual void onSetPath();
	virtual void onSetState();
	virtual void doAi();
	virtual bool doAttack(MapMoveObject* other);
	virtual Msg* doAppear();
	bool doUseSkill(int32_t skillId, vector<uint32_t> &tar, const Point &cen);
	bool doAddSkill(const DataSkill &skill);

public:
	uint32_t getTeamId() {
		return m_teamId;
	}
	uint32_t getUid() {
		return id_;
	}
private:
	bool findTarget();

private:
	uint16_t m_attackRadius;		//攻击半径
	uint32_t m_teamId;
	Point m_dest;					//目标点
};

#endif
