/*
 * DataUser.h
 *
 *  Created on: 2011-5-26
 *      Author: dada
 */

#ifndef DATAUSER_H_
#define DATAUSER_H_

#include "Kernel.h"

struct DataUser
{
	unsigned uid;
	int register_platform;
	unsigned register_time;
	unsigned invite_uid;
	int last_login_platform;
	unsigned last_login_time;
	unsigned last_active_time;
	unsigned login_times;
	int invite_count;
	int status;
	unsigned main_base_id;
	int level;
	uint64_t point;
	uint64_t value;
	int tutorial_stage;
	unsigned r1;
	unsigned r1_max;
	unsigned r2;
	unsigned r2_max;
	unsigned r3;
	unsigned r3_max;
	unsigned r4;
	unsigned r4_max;
	unsigned alliance_id;
	int unread_message;
	int world;
};

class CDataUser : public CDataBaseDBC
{
public:
	CDataUser(int table = DB_USER) : CDataBaseDBC(table) {}

public:
	int AddUser(DataUser &user);
	int SetUser(const DataUser &user);
	int GetUser(unsigned uid, DataUser &user);
	int RemoveUser(unsigned uid);

	int SetMainBaseId(unsigned uid, unsigned main_base_id);
	int GetMainBaseId(unsigned uid, unsigned &main_base_id);
	int SetAllianceId(unsigned uid, unsigned alliance_id);
	int GetAllianceId(unsigned uid, unsigned &alliance_id);
	int SetWorld(unsigned uid, int world);
	int GetWorld(unsigned uid, int &world);

	int GetActiveTime(unsigned uid, unsigned last_active_time);
	int SetActiveTime(unsigned uid, unsigned last_active_time);

	int SetStatus(unsigned uid, int status);
	int AddInviteCount(unsigned uid, int invite_count);
	int SetUnreadMessage(unsigned uid, int unread_message);

};

#endif /* DATAUSER_H_ */
