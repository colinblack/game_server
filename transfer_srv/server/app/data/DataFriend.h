/*
 * DataFriend.h
 *
 *  Created on: 2012-3-2
 *      Author: dada
 */

#ifndef DATAFRIEND_H_
#define DATAFRIEND_H_

#include "Kernel.h"

struct DataFriend
{
	unsigned uid;
	int platform;
	unsigned last_update_time;
	string friends;
	string friends_mapping;
};

class CDataFriend : public CDataBaseDBC
{
public:
	CDataFriend(int table = DB_FRIEND) : CDataBaseDBC(table) {}

public:
	int AddFriend(const DataFriend &dataFriend);
	int SetFriend(const DataFriend &dataFriend);
	int GetFriend(unsigned uid, int platform, DataFriend &dataFriend);
	int RemoveFriend(unsigned uid);

	int GetFriends(unsigned uid, int platform, string &friends);
};

#endif /* DATAFRIEND_H_ */
