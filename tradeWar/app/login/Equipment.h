/*
 * Equipment.h
 *
 *  Created on: 2015-8-26
 *      Author: Administrator
 */

#ifndef EQUIPMENT_H_
#define EQUIPMENT_H_

#include "MapObject.h"

class Equipment: public MapObject {
public:
	Equipment();
	~Equipment();
public:
	bool encode(IBuffer *buffer);
	bool setData(const string &jsonData);
	bool saveData(bool isNew = false);
};

#endif /* EQUIPMENT_H_ */
