/*
 * LogicNPCPassMgr.h
 *
 *  Created on: 2016-9-23
 *      Author: dawx62fac
 */

#ifndef LOGICNPCPASSMGR_H_
#define LOGICNPCPASSMGR_H_

#include "ServerInc.h"


class  LogicNPCPassMgr : public BattleSingleton, public CSingleton<LogicNPCPassMgr>
{
private:
	friend class CSingleton<LogicNPCPassMgr>;
	LogicNPCPassMgr(){};

	//闯关外部接口
	int GateExternalInterface(unsigned uid);

public:
	virtual void CallDestroy() { Destroy();}

	//闯关成功
	void PassSuccess(unsigned uid, unsigned id);
	//获取关卡通过次数， 仅对于记录的关卡，未记录的且解锁返回1，否则返回0
	unsigned GetNPCPassCnt(unsigned uid, unsigned id);

	void FullMessage(unsigned uid, User::NPCPass* obj);

	//进入关卡
	int Process(unsigned uid, ProtoPass::EnterFightReq* req);
};


#endif /* LOGICNPCPASSMGR_H_ */
