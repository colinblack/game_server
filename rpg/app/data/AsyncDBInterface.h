#ifndef _ASYNC_DB_INTERFACE_H_
#define _ASYNC_DB_INTERFACE_H_

#include "DataPacket.h"

enum AsyncDbOp {
	AsyncDbAdd = 1, AsyncDbSet = 2, AsyncDbRep = 3, AsyncDbDel = 4
};

class AsyncDBInterfaceBase {
public:
	virtual ~AsyncDBInterfaceBase() {
	}
	virtual void doRequest(DataPacket* packet) = 0;
};
#endif
