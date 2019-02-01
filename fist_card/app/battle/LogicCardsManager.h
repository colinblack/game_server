/*
 * LogicCardsManager.h
 *
 *  Created on: 2018年11月21日
 *      Author: colin
 */

#ifndef APP_BATTLE_LOGICCARDSMANAGER_H_
#define APP_BATTLE_LOGICCARDSMANAGER_H_

#include "ServerInc.h"

class LogicCardsManager : public BattleSingleton, public CSingleton<LogicCardsManager>
{
private:
	friend class CSingleton<LogicCardsManager>;
	LogicCardsManager(){};

public:
	virtual void CallDestroy() {Destroy();}
	int FullMessage(unsigned uid, User::CardsInfo* cardsmsg);
	int FullMessage(unsigned uid, User::UnlockCards* cardsmsg);
	//添加卡牌
	int AddCards(unsigned uid, unsigned cardsid, string reason, ProtoCards::CardsAllChangeCPP* msg);

	//卡牌升星
	int Process(unsigned uid, ProtoCards::ProtoUpdateCardReq* req, ProtoCards::ProtoUpdateCardResp* resp);
	//卡牌复制
	int Process(unsigned uid, ProtoCards::ProtoDupCardReq* req, ProtoCards::ProtoDupCardResp* resp);
	//删除卡牌
	int Process(unsigned uid, ProtoCards::ProtoDelCardReq* req, ProtoCards::ProtoDelCardResp* resp);
	//购买
	int Process(unsigned uid, ProtoCards::ProtoBuyCardReq* req, ProtoCards::ProtoBuyCardResp* resp);

};





#endif /* APP_BATTLE_LOGICCARDSMANAGER_H_ */
