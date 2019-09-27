/*
 * ProtocolEmail.h
 *
 *  Created on: 2016年3月12日
 *      Author: Administrator
 */

#ifndef PROTOCOLEMAIL_H_
#define PROTOCOLEMAIL_H_

#include "Kernel.h"
// 邮件删除
DEFINE_RECEIVE_PACKET_BEGIN(CEmailDeleteProtocol)
		byte cmd;
		byte subCmd;
		uint32_t count;
		vector<uint32_t> vec;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, count);
		vec.resize(count);
		for(uint32_t i = 0; i < count; ++i)
		{
			PACKET_DECODE(UInt32, vec[i]);
		}
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 读邮件
DEFINE_RECEIVE_PACKET_BEGIN(CEmailReadProtocol)
		byte cmd;
		byte subCmd;
		uint32_t id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CEmailWriteProtocol)
		byte cmd;
		byte subCmd;
		vector<uint32_t> vecUid;
		string title;
		string content;
		uint32_t count;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(String, title);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, content);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(UInt32, count);
		vecUid.resize(count);
		for(uint32_t i = 0; i < count; ++i)
		{
			PACKET_DECODE(UInt32, vecUid[i]);
		}

	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CEmailNewProtocol)
		byte cmd;
		byte subCmd;
		uint32_t id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END
#endif /* PROTOCOLEMAIL_H_ */
