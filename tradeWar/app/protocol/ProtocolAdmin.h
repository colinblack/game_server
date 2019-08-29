/*
 * ProtocolAdmin.h
 *
 *  Created on: 2016年2月3日
 *      Author: asdf
 */

#ifndef SERVERS_APP_PROTOCOL_PROTOCOLADMIN_H_
#define SERVERS_APP_PROTOCOL_PROTOCOLADMIN_H_

#include "Kernel.h"

#define PROTOCOL_TYPE_REFRESH COMBINE_PROTOCOL_TYPE(1, 3)
#define PROTOCOL_TYPE_LOGIN COMBINE_PROTOCOL_TYPE(1, 1)
#define PROTOCOL_TYPE_CHAT_SUBMIT COMBINE_PROTOCOL_TYPE(4, 1)
#define PROTOCOL_TYPE_FORBID_CHAT COMBINE_PROTOCOL_TYPE(5, 1)

// 清除用户内存数据
DEFINE_RECEIVE_PACKET_BEGIN(CAdminSetHeroExitBattleProtocol)
		byte cmd;
		byte subCmd;
		uint32_t targetUid;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, targetUid);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

#define SESSION_SECRET_KEY_SIZE 16

DEFINE_RECEIVE_PACKET_BEGIN(CLoginReceive)
			uint32_t SessionKey;
			CStaticBuffer<SESSION_SECRET_KEY_SIZE> SecretKey;
			IMPLEMENT_PACKET_DECODE_BEGIN
			reader.SetSwapByte(true);

			PACKET_DECODE(UInt32, SessionKey);
			PACKET_DECODE(Bytes, SecretKey.GetNativeBuffer(), SecretKey.GetFreeCapacity());
			IMPLEMENT_PACKET_DECODE_END
			// IMPLEMENT_TO_STRING("Platform=%u&Name=%s", (unsigned)SessionKey,  );
		DEFINE_RECEIVE_PACKET_END


		DEFINE_SEND_PACKET_BEGIN(CLoginSend)
			byte platform;
			string name;
			IMPLEMENT_PACKET_ENCODE_BEGIN
			writer.SetSwapByte(true);
				PACKET_ENCODE(Byte, platform);
				PACKET_ENCODE(String,name);
			IMPLEMENT_PACKET_ENCODE_END
			//IMPLEMENT_TO_STRING("SessionKey=0x%08X&SecretKey=%s", SessionKey, SecretKey.ToString().c_str())
		DEFINE_SEND_PACKET_END


		//1-3
		//心跳
		DEFINE_SEND_PACKET_BEGIN(CRefreshRequestProtocol)
			uint32_t ts;
			uint32_t delay;
			IMPLEMENT_PACKET_ENCODE_BEGIN
			writer.SetSwapByte(true);
				PACKET_ENCODE(UInt32, ts);
				PACKET_ENCODE(UInt32,delay);
			IMPLEMENT_PACKET_ENCODE_END
		DEFINE_SEND_PACKET_END



DEFINE_SEND_PACKET_BEGIN(CChatRequest)
	byte ToType;
	uint32_t ToId;
	string Message;
	IMPLEMENT_PACKET_ENCODE_BEGIN
	writer.SetSwapByte(true);
		PACKET_ENCODE(Byte, ToType);
		PACKET_ENCODE(UInt32, ToId);
		PACKET_ENCODE(String, Message);
	IMPLEMENT_PACKET_ENCODE_END
	IMPLEMENT_TO_STRING("ToType=%u&ToId=%u&Message=%s", (unsigned)ToType, ToId, Message.c_str())
DEFINE_SEND_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CChatReply)
	string Message;
	IMPLEMENT_PACKET_DECODE_BEGIN
	reader.SetSwapByte(true);

		PACKET_DECODE(String, Message);
	IMPLEMENT_PACKET_DECODE_END
	IMPLEMENT_TO_STRING("Message=%s", Message.c_str())
DEFINE_RECEIVE_PACKET_END

//5-1
//指定用户禁言

DEFINE_SEND_PACKET_BEGIN(CForbidChatRequest)
	uint32_t ForbidUid;
	uint32_t ForbidTs;
	IMPLEMENT_PACKET_ENCODE_BEGIN
	writer.SetSwapByte(true);
	PACKET_ENCODE(UInt32, ForbidUid);
	PACKET_ENCODE(UInt32, ForbidTs);
	IMPLEMENT_PACKET_ENCODE_END
	IMPLEMENT_TO_STRING("ForbidUid=%u&ForbidTs=%u", ForbidUid, ForbidTs)
DEFINE_SEND_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CForbidChatReply)
	uint32_t Result;
	string Message;
	IMPLEMENT_PACKET_DECODE_BEGIN
	reader.SetSwapByte(true);

	PACKET_DECODE(UInt32, Result);
	PACKET_DECODE(String, Message);
	IMPLEMENT_PACKET_DECODE_END
	IMPLEMENT_TO_STRING("Message=%s,Result = %u", Message.c_str(),Result)
DEFINE_RECEIVE_PACKET_END


DEFINE_RECEIVE_PACKET_BEGIN(CAddMoneyProtocol)
		byte cmd;
		byte subCmd;
		uint32_t uid;
		byte type;
		int32_t count;
		byte flag;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(Byte, type);
		PACKET_DECODE(Int32, count);
		PACKET_DECODE(Byte, flag);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CPrintLogProtocol)
		byte cmd;
		byte subCmd;
		uint32_t sec;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, sec);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CKickUserProtocol)
		byte cmd;
		byte subCmd;
		uint32_t uid;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, uid);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CAddEquipProtocol)
		byte cmd;
		byte subCmd;
		uint32_t uid;
		uint32_t itemId;
		uint32_t count;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, itemId);
		PACKET_DECODE(UInt32, count);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CALoginRquestProtocol)
	byte cmd;
	byte subCmd;
	string userName;
	string passWord;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(String, userName);
		PACKET_DECODE(String, passWord);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CAClientRquestProtocol)
	byte cmd;
	byte subCmd;
	string data;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(String, data);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_SEND_PACKET_BEGIN(CAClientReplyProtocol)
	byte cmd;
	byte subCmd;
	string data;
	IMPLEMENT_PACKET_ENCODE_BEGIN
	PACKET_ENCODE(Byte, cmd);
	PACKET_ENCODE(Byte, subCmd);
	PACKET_ENCODE(String, data);
	IMPLEMENT_PACKET_ENCODE_END
DEFINE_SEND_PACKET_END

#endif /* SERVERS_APP_PROTOCOL_PROTOCOLADMIN_H_ */
