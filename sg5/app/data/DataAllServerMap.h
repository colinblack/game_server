/*
 * DataAllServerMap.h
 *
 *  Created on: 2015-9-15
 *      Author: Ralf
 */

#ifndef DATAALLSERVERMAP_H_
#define DATAALLSERVERMAP_H_

#include "Kernel.h"
#include "DataBase.h"
#include "AllServerMap.pb.h"

#define ALL_SERVER_MAP_LEVEL_1 30
#define ALL_SERVER_MAP_SEG_1 5
#define ALL_SERVER_MAP_SEG_2 10
#define ALL_SERVER_MAP_MIN_LEVEL 5

typedef map<unsigned, set<unsigned> > AllServerLevelMap; //level -> uid
typedef map<unsigned, unsigned> AllServerUserMap;

class CDataAllServerMap : public DataBase
{
public:
	CDataAllServerMap(string path);
	virtual ~CDataAllServerMap(){}
	int Init();
	int Save();
	int Get(unsigned level, unsigned count, set<unsigned> &res);//random level + random size, may include self
	int Set(map<unsigned, unsigned> &res);
private:
	AllServerLevelMap m_levelMap;
	AllServerUserMap m_user;
};

#endif /* DATAALLSERVERMAP_H_ */
