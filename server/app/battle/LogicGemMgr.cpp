/*
 * LogicGemMgr.cpp
 *
 *  Created on: 2016-9-26
 *      Author: dawx62fac
 */


#include "LogicGemMgr.h"


void LogicGemMgr::Online(unsigned uid)
{
	DataGemMgr::Instance()->Online(uid);
}

void LogicGemMgr::Offline(unsigned uid)
{
	DataGemMgr::Instance()->Offline(uid);
}
