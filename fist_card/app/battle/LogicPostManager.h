/*
 * LogicPostManager.h
 *
 *  Created on: 2018年9月13日
 *      Author: colin
 */

#ifndef APP_BATTLE_LOGICPOSTMANAGER_H_
#define APP_BATTLE_LOGICPOSTMANAGER_H_

#include "Common.h"
#include "Kernel.h"
#include "DataInc.h"

class  LogicPostManager : public BattleSingleton, public CSingleton<LogicPostManager>
{
private:
	friend class CSingleton<LogicPostManager>;
	LogicPostManager() {};

public:
	virtual void CallDestroy() { Destroy();}

	int AddPost(unsigned uid, MartialClubItem& club);

	void FullMessage(unsigned uid, ProtoNotify::PostItemCPPAll* msg);

	//删除通知
	int Process(unsigned uid, ProtoNotify::PostRemove* req);


};



#endif /* APP_BATTLE_LOGICPOSTMANAGER_H_ */
