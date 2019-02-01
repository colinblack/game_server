/*
 * LogicNpc.h
 *
 *  Created on: 2011-7-19
 *      Author: dada
 */

#ifndef LOGICNPC_H_
#define LOGICNPC_H_

#include "LogicInc.h"

enum NpcStatus
{
	NS_UNPASS = '0',
	NS_PASS = '1'
};

namespace LogicNpc
{
	bool IsNpc(unsigned id);
	bool IsWildForce(unsigned id);
	bool IsGate(unsigned id);

	int GetInitBase(unsigned id, DataBaseExtra &baseExtra);
	int GetArchive(unsigned uid, unsigned id, bool attack, Json::Value &archive);
	int UpdateBase(unsigned uid, unsigned id, const Json::Value &data, DataBase &base);
	int ChangeResource(unsigned uid, DataBaseExtra &baseExtra, const Json::Value &resources);

	int SetNpcStatus(unsigned uid, unsigned id, NpcStatus status);

};

#endif /* LOGICNPC_H_ */
