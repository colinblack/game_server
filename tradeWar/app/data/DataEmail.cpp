/*
 * DataEmail.cpp
 *
 *  Created on: 2014-9-5
 *      Author: Administrator
 */
#include "DataEmail.h"
#include "AsyncDBManager.h"

#define OP_ADD_EMAIL 1
#define OP_UPDATE_EMAIL 2
#define OP_REMOVE_EMAIL 3

int CDataEmail::AddEmail(const DataEmail &dataEmail)
{
	DB_ENCODE_BEGIN(DB_EMAIL,OP_ADD_EMAIL);
	DB_ENCODE(UInt32,dataEmail.uid);
	DB_ENCODE(UInt32,dataEmail.id);
	DB_ENCODE(UInt32,dataEmail.opposite_uid);
	DB_ENCODE(String,dataEmail.title);
	DB_ENCODE(String,dataEmail.text);
	DB_ENCODE(String,dataEmail.from_name);
	DB_ENCODE(String,dataEmail.to_name);
	DB_ENCODE(UInt32,dataEmail.post_ts);
	DB_ENCODE(UInt32,dataEmail.read_ts);
	DB_ENCODE(String,dataEmail.attachments);
	DB_ENCODE(Byte,dataEmail.attach_flag);
	DB_ENCODE(Byte,dataEmail.post_flag);
	DB_ENCODE_END;
	return 0;
}

int CDataEmail::RealAddEmail(CNetPacket* packet)
{
	DataEmail dataEmail;
	DB_DECODE_BEGIN(&packet->body);
	DB_DECODE(UInt32, dataEmail.uid);
	DB_DECODE(UInt32, dataEmail.id);
	DB_DECODE(UInt32, dataEmail.opposite_uid);
	DB_DECODE(String, dataEmail.title);
	DB_DECODE(String, dataEmail.text);
	DB_DECODE(String, dataEmail.from_name);
	DB_DECODE(String, dataEmail.to_name);
	DB_DECODE(UInt32, dataEmail.post_ts);
	DB_DECODE(UInt32, dataEmail.read_ts);
	DB_DECODE(String, dataEmail.attachments);
	DB_DECODE(Byte, dataEmail.attach_flag);
	DB_DECODE(Byte, dataEmail.post_flag);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::InsertRequest, dataEmail.uid);
	DBCREQ_SET_KEY(dataEmail.uid);
	DBCREQ_SET_INT(dataEmail, id);
	DBCREQ_SET_INT(dataEmail, opposite_uid);
	DBCREQ_SET_STR(dataEmail, title);
	DBCREQ_SET_STR(dataEmail, text);
	DBCREQ_SET_STR(dataEmail, from_name);
	DBCREQ_SET_STR(dataEmail, to_name);
	DBCREQ_SET_INT(dataEmail, post_ts);
	DBCREQ_SET_INT(dataEmail, read_ts);
	DBCREQ_SET_STR(dataEmail, attachments);
	DBCREQ_SET_INT(dataEmail, attach_flag);
	DBCREQ_SET_INT(dataEmail, post_flag);
	DBCREQ_EXEC;
	return 0;
}

int CDataEmail::syncAddEmail(const DataEmail &dataEmail)
{
	DBCREQ_DECLARE(DBC::InsertRequest, dataEmail.uid);
	DBCREQ_SET_KEY(dataEmail.uid);
	DBCREQ_SET_INT(dataEmail, id);
	DBCREQ_SET_INT(dataEmail, opposite_uid);
	DBCREQ_SET_STR(dataEmail, title);
	DBCREQ_SET_STR(dataEmail, text);
	DBCREQ_SET_STR(dataEmail, from_name);
	DBCREQ_SET_STR(dataEmail, to_name);
	DBCREQ_SET_INT(dataEmail, post_ts);
	DBCREQ_SET_INT(dataEmail, read_ts);
	DBCREQ_SET_STR(dataEmail, attachments);
	DBCREQ_SET_INT(dataEmail, attach_flag);
	DBCREQ_SET_INT(dataEmail, post_flag);
	DBCREQ_EXEC;
	return 0;
}

int CDataEmail::GetEmail(uint32_t uid, uint32_t email_id, DataEmail &dataEmail)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, id, email_id);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(opposite_uid);
	DBCREQ_NEED(title);
	DBCREQ_NEED(text);
	DBCREQ_NEED(from_name);
	DBCREQ_NEED(to_name);
	DBCREQ_NEED(post_ts);
	DBCREQ_NEED(read_ts);
	DBCREQ_NEED(attachments);
	DBCREQ_NEED(attach_flag);
	DBCREQ_NEED(post_flag);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(dataEmail, uid);
	DBCREQ_GET_INT(dataEmail, id);
	DBCREQ_GET_INT(dataEmail, opposite_uid);
	DBCREQ_GET_STR(dataEmail, title);
	DBCREQ_GET_STR(dataEmail, text);
	DBCREQ_GET_STR(dataEmail, from_name);
	DBCREQ_GET_STR(dataEmail, to_name);
	DBCREQ_GET_INT(dataEmail, post_ts);
	DBCREQ_GET_INT(dataEmail, read_ts);
	DBCREQ_GET_STR(dataEmail, attachments);
	DBCREQ_GET_INT(dataEmail, attach_flag);
	DBCREQ_GET_INT(dataEmail, post_flag);
	return 0;
}

int CDataEmail::GetEmails(uint32_t uid,vector<DataEmail> &dataEmail)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(id);
	DBCREQ_NEED(opposite_uid);
	DBCREQ_NEED(title);
	DBCREQ_NEED(text);
	DBCREQ_NEED(from_name);
	DBCREQ_NEED(to_name);
	DBCREQ_NEED(post_ts);
	DBCREQ_NEED(read_ts);
	DBCREQ_NEED(attachments);
	DBCREQ_NEED(attach_flag);
	DBCREQ_NEED(post_flag);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(dataEmail);
	DBCREQ_ARRAY_GET_INT(dataEmail, uid);
	DBCREQ_ARRAY_GET_INT(dataEmail, id);
	DBCREQ_ARRAY_GET_INT(dataEmail, opposite_uid);
	DBCREQ_ARRAY_GET_STR(dataEmail, title);
	DBCREQ_ARRAY_GET_STR(dataEmail, text);
	DBCREQ_ARRAY_GET_STR(dataEmail, from_name);
	DBCREQ_ARRAY_GET_STR(dataEmail, to_name);
	DBCREQ_ARRAY_GET_INT(dataEmail, post_ts);
	DBCREQ_ARRAY_GET_INT(dataEmail, read_ts);
	DBCREQ_ARRAY_GET_STR(dataEmail, attachments);
	DBCREQ_ARRAY_GET_INT(dataEmail, attach_flag);
	DBCREQ_ARRAY_GET_INT(dataEmail, post_flag);
	DBCREQ_ARRAY_GET_END();

	return 0;
}

int CDataEmail::RemoveEmail(uint32_t  uid, uint32_t id)
{
	DB_ENCODE_BEGIN(DB_EMAIL,OP_REMOVE_EMAIL);
	DB_ENCODE(UInt32, uid);
	DB_ENCODE(UInt32, id);
	DB_ENCODE_END;

	if(uid < 1000000)
	{
		debug_log("remove system email uid=%u id=%u",uid,id);
	}
	return 0;
}

int CDataEmail::RealRemoveEmail(CNetPacket* packet)
{
	uint32_t uid = 0;
	uint32_t id = 0;
	DB_DECODE_BEGIN(&packet->body);
	DB_DECODE(UInt32,uid);
	DB_DECODE(UInt32,id);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::DeleteRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, id, id);
	DBCREQ_EXEC;

	return 0;
}

int CDataEmail::UpdateEmail(const DataEmail &dataEmail)
{

	DB_ENCODE_BEGIN(DB_EMAIL,OP_UPDATE_EMAIL);
	DB_ENCODE(UInt32,dataEmail.uid);
	DB_ENCODE(UInt32,dataEmail.id);
	DB_ENCODE(UInt32,dataEmail.opposite_uid);
	DB_ENCODE(String,dataEmail.title);
	DB_ENCODE(String,dataEmail.text);
	DB_ENCODE(String,dataEmail.from_name);
	DB_ENCODE(String,dataEmail.to_name);
	DB_ENCODE(UInt32,dataEmail.post_ts);
	DB_ENCODE(UInt32,dataEmail.read_ts);
	DB_ENCODE(String,dataEmail.attachments);
	DB_ENCODE(Byte,dataEmail.attach_flag);
	DB_ENCODE(Byte,dataEmail.post_flag);
	DB_ENCODE_END;
	return 0;
}

int CDataEmail::RealUpdateEmail(CNetPacket* packet)
{
	DataEmail dataEmail;
	DB_DECODE_BEGIN(&packet->body);
	DB_DECODE(UInt32, dataEmail.uid);
	DB_DECODE(UInt32, dataEmail.id);
	DB_DECODE(UInt32, dataEmail.opposite_uid);
	DB_DECODE(String, dataEmail.title);
	DB_DECODE(String, dataEmail.text);
	DB_DECODE(String, dataEmail.from_name);
	DB_DECODE(String, dataEmail.to_name);
	DB_DECODE(UInt32, dataEmail.post_ts);
	DB_DECODE(UInt32, dataEmail.read_ts);
	DB_DECODE(String, dataEmail.attachments);
	DB_DECODE(Byte, dataEmail.attach_flag);
	DB_DECODE(Byte, dataEmail.post_flag);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::UpdateRequest, dataEmail.uid);
	DBCREQ_SET_KEY(dataEmail.uid);
	DBCREQ_SET_CONDITION(EQ, id, dataEmail.id);

	DBCREQ_SET_INT(dataEmail, id);
	DBCREQ_SET_INT(dataEmail, opposite_uid);
	DBCREQ_SET_STR(dataEmail, title);
	DBCREQ_SET_STR(dataEmail, text);
	DBCREQ_SET_STR(dataEmail, from_name);
	DBCREQ_SET_STR(dataEmail, to_name);
	DBCREQ_SET_INT(dataEmail, post_ts);
	DBCREQ_SET_INT(dataEmail, read_ts);
	DBCREQ_SET_STR(dataEmail, attachments);
	DBCREQ_SET_INT(dataEmail, attach_flag);
	DBCREQ_SET_INT(dataEmail, post_flag);
	DBCREQ_EXEC;
	return 0;

}

OP_PROCESS_BEGIN(CDataEmail)
OP_PROCESS(OP_ADD_EMAIL,RealAddEmail)
OP_PROCESS(OP_UPDATE_EMAIL,RealUpdateEmail)
OP_PROCESS(OP_REMOVE_EMAIL,RealRemoveEmail)
OP_PROCESS_END
