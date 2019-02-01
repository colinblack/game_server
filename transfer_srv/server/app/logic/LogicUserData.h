/*
 * LogicUserData.h
 *
 *  Created on: 2011-11-1
 *      Author: dada
 */

#ifndef LOGICUSERDATA_H_
#define LOGICUSERDATA_H_

#include "LogicInc.h"

class CLogicUserData
{

public:

	int SetUserData(unsigned uid, const Json::Value &data);
	int GetUserData(unsigned uid, Json::Value &data);	//不存在自动增加空数据
	int RemoveUserData(unsigned uid);

	int GetPromoteFriends(unsigned uid, int count, vector<string> &friends);
	int GetNoAppFriends(unsigned uid, int count, vector<OPUserInfo> &friends);

protected:

	int GetRelationData(unsigned uid, Json::Value &data, bool autoSave = true);

};

#endif /* LOGICUSERDATA_H_ */
