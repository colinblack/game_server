#ifndef _STD_MONSETER_H_
#define _STD_MONSETER_H_

#include "MapMoveObject.h"
#include "Human.h"
#include "MapAreaState.h"

enum MONSTER_TYPE {
	COMMON_MONSTER = 1,
	ELITE_MONSTER = 2,
	BOSS_MONSTER = 4
};

class StdMonster: public MapMoveObject {
public:
	StdMonster();
	virtual ~StdMonster();
	bool init(uint32_t id, uint32_t fbId, uint32_t mapId, const Point &p);
	virtual bool initSkill();
	virtual bool getSceneMsg();
	virtual bool getMoveMsg();
	virtual bool onFightInfo();
	virtual bool doAttack(MapMoveObject* other);
	virtual bool doUseSKill(MapMoveObject *target);
	virtual void onDestory();
	virtual void onSetPos();
	virtual bool canAttack(MapMoveObject *target);
	virtual bool recove();
	virtual void doMove(IBuffer* buf);
	virtual void doAi();
	virtual Msg* doAppear();
	virtual void onDie();
	virtual void onFirstAttackerChange();
	virtual void onSetPath();
	void setCanMove(bool flag);
	void setActively(bool flag);

private:
	bool findTarget();

private:
	bool m_canMove;					//是否可移动
	bool m_isActively;				//是否主动攻击
	bool m_isReturn;				//是否在返回状态
	bool m_pathFlag;				//是否寻找过路径
	uint16_t m_attackRadius;		//攻击半径
	uint16_t m_viewRadius;			//视野半径
	uint16_t m_guardRadius;			//守卫半径，对于主动攻击性怪物，角色进入该距离，怪物发起追踪
	uint16_t m_maxRadius;			//怪物离开出生点的最大距离
	uint16_t m_holdRadius;			//凝视半径
	uint32_t m_lastLoopMilliTime;	//最近一次扫描的毫秒时间
	int32_t m_type;					//普通怪 :1 boss:4  精英:2
	Point m_dest;					//目标点
};

#endif
