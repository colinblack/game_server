/*
 * LogicUserInteract.h
 *
 *  Created on: 2011-7-13
 *      Author: dada
 */

#ifndef LOGICUSERINTERACT_H_
#define LOGICUSERINTERACT_H_

#include "LogicInc.h"

class CLogicUserInteract
{
public:

	int AddHelp(unsigned uidFrom, unsigned uidTo);
	int AddAttack(unsigned uidFrom, unsigned uidTo);
	int GetInteract(unsigned uid, unsigned oppositeUid, DataUserInteract &interact);
	int GetInteracts(unsigned uid, map<unsigned, DataUserInteract> &interacts);

	int ProcessRequest(const DataMessage &request, unsigned from, unsigned to, const string &type, int action, const Json::Value &data);

	int SendRequest(unsigned uid, const string &type, const string &data, const map<string, string> &userRequests);
	int GetRequestFilter(unsigned uid, const string &requestType, Json::Value &users);
	int FilterRequestUsers(const UidList &users, const Json::Value &filter, Json::Value &filterUsers);
	int RequestItem(unsigned uid, const string &itemid, int requireCount, uint64_t &messageId, unsigned &waitTime);
	int SendHelpReward(unsigned uid, const string &itemid, int count, uint64_t &messageId);
	int GetFriendInteracts(unsigned uid, map<unsigned, int> &interacts);
	int AddFriendInteract(unsigned uid, unsigned friendId, const string &type);

	int ChangeInteractPoint(unsigned uid, int count);
	int ChangeInteractStat(unsigned uid, const char *name, int delta);

};

#endif /* LOGICUSERINTERACT_H_ */
