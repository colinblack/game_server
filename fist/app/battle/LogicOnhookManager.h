/*
 * LogicOnhookManager.h
 *
 *  Created on: 2018年8月28日
 *      Author: colin
 */

#ifndef APP_BATTLE_LOGICONHOOKMANAGER_H_
#define APP_BATTLE_LOGICONHOOKMANAGER_H_

#include "ServerInc.h"


class LogicOnhookManager : public BattleSingleton, public CSingleton<LogicOnhookManager>
{
private:
	friend class CSingleton<LogicOnhookManager>;
	LogicOnhookManager(){}

public:
	virtual void CallDestroy(){Destroy();}
	void FullMessage(unsigned uid, User::OnhookReward* msg);
	//挂机经验或者金币
	int OnhookExpOrCoin(OnhookType type, unsigned startTs, unsigned endTs, unsigned stageId);

	//在线玩家挂机道具奖励
	void OnhookOnlineProp();

	//离线玩家挂机道具奖励
	bool OnhookOfflineProp(unsigned startTs, unsigned endTs, unsigned stageId, CommonGiftConfig::CommonModifyItem& cfg);
};




#endif /* APP_BATTLE_LOGICONHOOKMANAGER_H_ */
