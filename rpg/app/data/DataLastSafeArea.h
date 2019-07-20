/*
 * DataLastSafeArea.h
 *
 *  Created on: 2013-5-13
 *      Author: Administrator
 */

#ifndef DATA_LAST_SAFE_AREA_H_
#define DATA_LAST_SAFE_AREA_H_

#include "Kernel.h"
struct DataLastSafeArea {
	unsigned fbInstanceId;
	unsigned rid;
	int mapId;
	int x;
	int y;
};
class CDataLastSafeArea: public CDataBaseDBC {
public:
	CDataLastSafeArea(int table = DB_LAST_SAFEAREA) : CDataBaseDBC(table) {
	}
	virtual ~CDataLastSafeArea();
public:
	int addLastSafeArea(const DataLastSafeArea &data);
	int updateLastSafeArea(const DataLastSafeArea &data);
	int getLastSafeArea(DataLastSafeArea &data);
};

#endif /* DATA_LAST_SAFE_AREA_H_ */
