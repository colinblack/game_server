/*
 * DataVideo.cpp
 *
 *  Created on: 2015-12-3
 *      Author: Administrator
 */

#include "DataVideo.h"
#include "AsyncDBInterface.h"
#include "AsyncDBManager.h"

#define OP_ADD_VIDEO 1
#define OP_UPDATE_VIDEO 2
#define OP_REMOVE_VIDEO 3

int CDataVideo::GetVideo(unsigned uid, vector<DataVideo> & datas)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(bid);
	DBCREQ_NEED(name);
	DBCREQ_NEED(identy);
	DBCREQ_NEED(op_uid);
	DBCREQ_NEED(op_name);
	DBCREQ_NEED(op_consume);
	DBCREQ_NEED(op_rank);
	DBCREQ_NEED(rob_r1);
	DBCREQ_NEED(rob_r2);
	DBCREQ_NEED(rob_r3);
	DBCREQ_NEED(rob_r4);
	DBCREQ_NEED(result);
	DBCREQ_NEED(damage);
	DBCREQ_NEED(star);
	DBCREQ_NEED(medal);
	DBCREQ_NEED(revenge);
	DBCREQ_EXEC;
	DBCREQ_ARRAY_GET_BEGIN(datas);
	DBCREQ_ARRAY_GET_INT(datas, uid);
	DBCREQ_ARRAY_GET_INT(datas, bid);
	DBCREQ_ARRAY_GET_STR(datas, name);
	DBCREQ_ARRAY_GET_INT(datas, identy);
	DBCREQ_ARRAY_GET_INT(datas, op_uid);
	DBCREQ_ARRAY_GET_STR(datas, op_name);
	DBCREQ_ARRAY_GET_INT(datas, op_consume);
	DBCREQ_ARRAY_GET_INT(datas, op_rank);
	DBCREQ_ARRAY_GET_INT(datas, rob_r1);
	DBCREQ_ARRAY_GET_INT(datas, rob_r2);
	DBCREQ_ARRAY_GET_INT(datas, rob_r3);
	DBCREQ_ARRAY_GET_INT(datas, rob_r4);
	DBCREQ_ARRAY_GET_INT(datas, result);
	DBCREQ_ARRAY_GET_INT(datas, damage);
	DBCREQ_ARRAY_GET_INT(datas, star);
	DBCREQ_ARRAY_GET_INT(datas, medal);
	DBCREQ_ARRAY_GET_INT(datas, revenge);
	DBCREQ_ARRAY_GET_END();

	return 0;
}

int CDataVideo::AddVideo(DataVideo & data)
{
	DB_ENCODE_BEGIN(DB_VIDEO,OP_ADD_VIDEO);
	DB_ENCODE(Int32,data.uid);
	DB_ENCODE(Int32,data.bid);
	DB_ENCODE(String,data.name);
	DB_ENCODE(Int32,data.identy);
	DB_ENCODE(Int32,data.op_uid);
	DB_ENCODE(String,data.op_name);
	DB_ENCODE(Int32,data.op_consume);
	DB_ENCODE(Int32,data.op_rank);
	DB_ENCODE(Int32,data.rob_r1);
	DB_ENCODE(Int32,data.rob_r2);
	DB_ENCODE(Int32,data.rob_r3);
	DB_ENCODE(Int32,data.rob_r4);
	DB_ENCODE(Int32,data.result);
	DB_ENCODE(Int32,data.damage);
	DB_ENCODE(Int32,data.star);
	DB_ENCODE(Int32,data.medal);
	DB_ENCODE(Int32,data.revenge);
	DB_ENCODE_END;
	return 0;
}

int CDataVideo::SetVideo(DataVideo & data)
{
	DB_ENCODE_BEGIN(DB_VIDEO, OP_UPDATE_VIDEO);
	DB_ENCODE(Int32,data.uid);
	DB_ENCODE(Int32,data.bid);
	DB_ENCODE(String,data.name);
	DB_ENCODE(Int32,data.identy);
	DB_ENCODE(Int32,data.op_uid);
	DB_ENCODE(String,data.op_name);
	DB_ENCODE(Int32,data.op_consume);
	DB_ENCODE(Int32,data.op_rank);
	DB_ENCODE(Int32,data.rob_r1);
	DB_ENCODE(Int32,data.rob_r2);
	DB_ENCODE(Int32,data.rob_r3);
	DB_ENCODE(Int32,data.rob_r4);
	DB_ENCODE(Int32,data.result);
	DB_ENCODE(Int32,data.damage);
	DB_ENCODE(Int32,data.star);
	DB_ENCODE(Int32,data.medal);
	DB_ENCODE(Int32,data.revenge);
	DB_ENCODE_END;
	return 0;
}

int CDataVideo::RemoveVideo(uint32_t uid,uint32_t bid)
{
	DB_ENCODE_BEGIN(DB_VIDEO,OP_REMOVE_VIDEO);
	DB_ENCODE(UInt32, uid);
	DB_ENCODE(UInt32, bid);
	DB_ENCODE_END;
	return 0;
}

int CDataVideo::RealAddVideo(CNetPacket* packet)
{
	DataVideo data;
	DB_DECODE_BEGIN(&packet->body);
	DB_DECODE(UInt32,data.uid);
	DB_DECODE(UInt32,data.bid);
	DB_DECODE(String,data.name);
	DB_DECODE(UInt32,data.identy);
	DB_DECODE(UInt32,data.op_uid);
	DB_DECODE(String,data.op_name);
	DB_DECODE(UInt32,data.op_consume);
	DB_DECODE(UInt32,data.op_rank);
	DB_DECODE(UInt32,data.rob_r1);
	DB_DECODE(UInt32,data.rob_r2);
	DB_DECODE(UInt32,data.rob_r3);
	DB_DECODE(UInt32,data.rob_r4);
	DB_DECODE(UInt32,data.result);
	DB_DECODE(UInt32,data.damage);
	DB_DECODE(UInt32,data.star);
	DB_DECODE(UInt32,data.medal);
	DB_DECODE(UInt32,data.revenge);
	DB_DECODE_END;
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data,bid);
	DBCREQ_SET_STR(data,name);
	DBCREQ_SET_INT(data,identy);
	DBCREQ_SET_INT(data,op_uid);
	DBCREQ_SET_STR(data,op_name);
	DBCREQ_SET_INT(data,op_consume);
	DBCREQ_SET_INT(data,op_rank);
	DBCREQ_SET_INT(data,rob_r1);
	DBCREQ_SET_INT(data,rob_r2);
	DBCREQ_SET_INT(data,rob_r3);
	DBCREQ_SET_INT(data,rob_r4);
	DBCREQ_SET_INT(data,result);
	DBCREQ_SET_INT(data,damage);
	DBCREQ_SET_INT(data,star);
	DBCREQ_SET_INT(data,medal);
	DBCREQ_SET_INT(data,revenge);
	DBCREQ_EXEC;
	return 0;
}

int CDataVideo::RealSetVideo(CNetPacket* packet)
{
	DataVideo data;
	DB_DECODE_BEGIN(&packet->body);
	DB_DECODE(UInt32,data.uid);
	DB_DECODE(UInt32,data.bid);
	DB_DECODE(String,data.name);
	DB_DECODE(UInt32,data.identy);
	DB_DECODE(UInt32,data.op_uid);
	DB_DECODE(String,data.op_name);
	DB_DECODE(UInt32,data.op_consume);
	DB_DECODE(UInt32,data.op_rank);
	DB_DECODE(UInt32,data.rob_r1);
	DB_DECODE(UInt32,data.rob_r2);
	DB_DECODE(UInt32,data.rob_r3);
	DB_DECODE(UInt32,data.rob_r4);
	DB_DECODE(UInt32,data.result);
	DB_DECODE(UInt32,data.damage);
	DB_DECODE(UInt32,data.star);
	DB_DECODE(UInt32,data.medal);
	DB_DECODE(UInt32,data.revenge);
	DB_DECODE_END;
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_CONDITION(EQ,bid,data.bid);
	DBCREQ_SET_INT(data,bid);
	DBCREQ_SET_STR(data,name);
	DBCREQ_SET_INT(data,identy);
	DBCREQ_SET_INT(data,op_uid);
	DBCREQ_SET_STR(data,op_name);
	DBCREQ_SET_INT(data,op_consume);
	DBCREQ_SET_INT(data,op_rank);
	DBCREQ_SET_INT(data,rob_r1);
	DBCREQ_SET_INT(data,rob_r2);
	DBCREQ_SET_INT(data,rob_r3);
	DBCREQ_SET_INT(data,rob_r4);
	DBCREQ_SET_INT(data,result);
	DBCREQ_SET_INT(data,damage);
	DBCREQ_SET_INT(data,star);
	DBCREQ_SET_INT(data,medal);
	DBCREQ_SET_INT(data,revenge);
	DBCREQ_EXEC;
	return 0;
}

int CDataVideo::RealRemoveVideo(CNetPacket* packet)
{
	uint32_t uid = 0;
	uint32_t bid = 0;
	DB_DECODE_BEGIN(&packet->body);
	DB_DECODE(UInt32, uid);
	DB_DECODE(UInt32, bid);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::DeleteRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, bid, bid);
	DBCREQ_EXEC;
	return 0;
}

OP_PROCESS_BEGIN(CDataVideo)
OP_PROCESS(OP_ADD_VIDEO, RealAddVideo)
OP_PROCESS(OP_UPDATE_VIDEO, RealSetVideo)
OP_PROCESS(OP_REMOVE_VIDEO, RealRemoveVideo)
OP_PROCESS_END
