/*
 * DataWorld.h
 *
 *  Created on: 2012-3-13
 *      Author: dada
 */

#ifndef DATAWORLD_H_
#define DATAWORLD_H_

#include "Kernel.h"

class CDataWorld : public CDataBaseDBC
{
public:
	CDataWorld(int table = DB_WORLD) : CDataBaseDBC(table) {}

public:
	int Add(unsigned position, unsigned baseid);
	int Set(unsigned position, unsigned baseid);
	int Get(unsigned position, unsigned &baseid);
	int Remove(unsigned position);
	int Replace(unsigned position, unsigned baseid);

};

#endif /* DATAWORLD_H_ */
