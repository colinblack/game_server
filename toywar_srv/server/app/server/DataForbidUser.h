/*
 * DataForbidUser.h
 *
 *  Created on: 2012-11-14
 *      Author: Administrator
 */

#ifndef DATAFORBIDUSER_H_
#define DATAFORBIDUSER_H_
#define MAX_USER_COUNT 200
#include "Kernel.h"
struct UserItem{
	unsigned uid;
	unsigned forbidTs;
};


struct UserForbidList{
	int iCount;
	UserItem uidList[MAX_USER_COUNT];
};

class CDataForbidUser {
public:
	CDataForbidUser();
	virtual ~CDataForbidUser();
	bool Init(const std::string &path);
	int update(unsigned uid,unsigned ts);
	bool IsForbid(unsigned uid);
	int GetMinForbidTsIndex(int &iIndex);
	int GetUserList(map<unsigned, unsigned> &userMap);
private:
	bool m_init;
	CShareMemory m_sh;
};

#endif /* DATAFORBIDUSER_H_ */
