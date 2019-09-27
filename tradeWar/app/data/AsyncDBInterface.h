#ifndef _ASYNC_DB_INTERFACE_H_
#define _ASYNC_DB_INTERFACE_H_

#include "NetPacket.h"

#define DB_ENCODE(type, ...)	if(!writer.Append##type(__VA_ARGS__)) return -1
#define DB_DECODE(type, ...)	if(!reader.Get##type(__VA_ARGS__)) return -1
#define DB_ENCODE_BEGIN(tableId,opId) CNetPacket packet;packet.fd = tableId;packet.stime = opId;CBufferWriter writer(&packet.body)
#define DB_ENCODE_END if(!AsyncDBManager::getInstance()->send(&packet)) return -1
#define DB_DECODE_BEGIN(data) CBufferReader reader(data)
#define DB_DECODE_END

#define OP_PROCESS_BEGIN(className) void className::doRequest(CNetPacket* packet){\
	switch(packet->stime){
#define OP_PROCESS_END default:\
		error_log("unknown opid %u",packet->stime);\
		break;\
	}\
}
#define OP_PROCESS(op,func) case op:\
	if(0 != func(packet)){\
			error_log(#func" failed");\
		}\
		break;

enum DBAsyncType {
	e_DBAsyncTypeAdd = 1,   //新增
	e_DBAsyncTypeSet = 2,   //修改
	e_DBAsyncTypeRep = 3,   //替换
	e_DBAsyncTypeDel = 4,   //删除
	e_DBAsyncTypeMax
};

class AsyncDBInterface {
public:
	virtual ~AsyncDBInterface() {
	}
	virtual void doRequest(CNetPacket* packet) = 0;
};

#endif
