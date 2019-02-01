/*
 * GameBase.h
 *
 *  Created on: 2018年11月27日
 *      Author: colin
 */

#ifndef APP_BATTLE_GAMEBASE_H_
#define APP_BATTLE_GAMEBASE_H_

#include "Kernel.h"
#include "DataInc.h"
#include "Common.h"


class GameBase
{
public:
	GameBase(){}
	virtual ~GameBase(){}

	virtual int GameStart(unsigned uid, unsigned battleid, const ProtoBattle::BattleCommonCPP& req, Message* message) = 0;
	virtual void GameEnd(unsigned battleid) = 0;
	virtual void CallDestroy() = 0;

protected:
	//初始化玩家信息
	int InitUserItem(unsigned uid, unsigned battleid);

	//生成玩家战斗卡包
	void CreateUserCardBag(unsigned battleid, unsigned uid);
	//生成npc战斗卡包
	void CreatNpcCardBag(unsigned battleid, unsigned id, vector<unsigned>& formation, vector<CardItem>& cardbag);

	void SendCard(unsigned uid, unsigned battleid, unsigned btype, ProtoBattle::ProtoBattleCPP* msg);

	int InitOthItem(unsigned uid, unsigned battleid);
public:
	//电脑出牌
	virtual int RobotOutCard(unsigned battleid);
	//生成手牌
	static void CreateHandCard(vector<CardItem>& cards, vector<CardItem>& carbags, vector<CardItem>& temp);
};

#endif /* APP_BATTLE_GAMEBASE_H_ */
