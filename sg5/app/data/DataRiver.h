/*
 * DataRiver.h
 *
 *  Created on: 2013-3-20
 *      Author: Administrator
 */

#ifndef DATARIVER_H_
#define DATARIVER_H_

#include "Kernel.h"
#include "DataInc.h"

#define SHIP_USER_COUNT 10000

struct DataShip
{
	unsigned uid;
	int type;
	unsigned start_time;
	unsigned end_time;
	int posy;
	int attack_num;
	int user_level;
	char user_name[32];
	char alliance_name[32];
};


struct DataRiver {
	DataShip Ships[SHIP_USER_COUNT];
	unsigned count;
};

class CDataRiver {
public:
	CDataRiver();
	int Init(const string &path, semdat sem=sem_river);
	int AddShip(DataShip &ship, bool set);
	int GetShips(vector<DataShip> &ships, vector<DataShip> &over);
	int GetOneShip(unsigned uid,DataShip &ship);

protected:
	CShareMemory m_sh;
	bool m_init;
};

#endif /* DATARIVER_H_ */
