/*
 * UserManager.h
 *
 *  Created on: 2012-3-8
 *      Author: dada
 */

#ifndef USERMANAGER_H_
#define USERMANAGER_H_

#include "Kernel.h"

struct UserData
{
	unsigned UserId;
	int SessionId;
	unsigned Delay;
	byte Platform;
	string Name;
	int FightNum;
	string vip;
	string lvl;
	string name;
	string openid;
	UserData& operator=(const UserData &user);
};

typedef vector<UserData> UserList;

class CUserManager
{
public:
	bool AddUser(const UserData &user);
	void RemoveUser(unsigned uid);
	bool GetUser(unsigned uid, UserData &user);
	int GetSessionId(unsigned uid);
	void UpdateUser(unsigned uid,int fightnum);
private:
	map<unsigned, UserData> m_users;

};

#endif /* USERMANAGER_H_ */
