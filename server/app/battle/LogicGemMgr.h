/*
 * LogicGemMgr.h
 *
 *  Created on: 2016-9-26
 *      Author: dawx62fac
 */

#ifndef LOGICGEMMGR_H_
#define LOGICGEMMGR_H_

#include "ServerInc.h"

class LogicGemMgr : public BattleSingleton, public CSingleton<LogicGemMgr>
{
private:
	friend class CSingleton<LogicGemMgr>;
	LogicGemMgr(){};


public:
	virtual void CallDestroy() { Destroy();}

	void Online(unsigned uid);
	void Offline(unsigned uid);
};

#endif /* LOGICGEMMGR_H_ */
