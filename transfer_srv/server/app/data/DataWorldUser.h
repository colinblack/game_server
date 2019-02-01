/*
 * DataWorldUser.h
 *
 *  Created on: 2012-5-15
 *      Author: dada
 */

#ifndef DATAWORLDUSER_H_
#define DATAWORLDUSER_H_

#include "Kernel.h"

class CDataWorldUser
{
public:
	CDataWorldUser();
	int Init(const string &path);
	int SetUser(unsigned uid, int world);
	int GetUser(unsigned &uid, int world);
	int RemoveUser(unsigned uid);

protected:
	CShareMemory m_sh;
	bool m_init;
};

#endif /* DATAWORLDUSER_H_ */
