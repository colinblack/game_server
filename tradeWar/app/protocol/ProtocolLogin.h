/*
 * ProtocolLogin.h
 *
 *  Created on: 2015-8-24
 *      Author: Administrator
 */

#ifndef PROTOCOLLOGIN_H_
#define PROTOCOLLOGIN_H_

#include "Kernel.h"

struct TencentBasicInfo
{
	string name;
	string url;
	uint32_t is_vip;		// 1:是 0:不是(黄钻)
	uint32_t is_year_vip;	// 年费黄钻
	uint32_t vip_level;		// 黄钻等级
	uint32_t gift;			// 礼包领取标记

	TencentBasicInfo()
	{
		name = "";
		url = "";
		is_vip = 0;
		is_year_vip = 0;
		vip_level = 0;
		gift = 0;
	}
};

//1,1
DEFINE_RECEIVE_PACKET_BEGIN(CLoginProtocol)
	byte cmd;
	byte subCmd;
	string openId;
	string openKey;
	uint32_t span_id;			//游戏平台
	uint32_t reg_server_id;
	uint32_t cur_server_id;
	uint32_t platform;			//操作系统平台
	uint32_t platform_gift;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(String, openId);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, openKey);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(UInt32, span_id);
		PACKET_DECODE(UInt32, reg_server_id);
		PACKET_DECODE(UInt32, cur_server_id);
		if (!reader.GetUInt32(platform)){platform=0;}
		if (!reader.GetUInt32(platform_gift)){platform_gift=0;}
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

//1,1
DEFINE_RECEIVE_PACKET_BEGIN(CTransitLoginProtocol)
	byte cmd;
	byte subCmd;
	string openId;
	string openKey;
	uint32_t reg_server_id;
	uint32_t cur_server_id;
	TencentBasicInfo info;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(String, openId);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, openKey);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(UInt32, reg_server_id);
		PACKET_DECODE(UInt32, cur_server_id);
		PACKET_DECODE(String, info.name);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, info.url);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(UInt32, info.is_vip);
		PACKET_DECODE(UInt32, info.gift);
		PACKET_DECODE(UInt32, info.vip_level);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END


//
DEFINE_RECEIVE_PACKET_BEGIN(CTransitBlueInfoProtocol)
	byte cmd;
	byte subCmd;
	uint32_t isBlue;
	uint32_t isBlueYear;
	uint32_t isBlueLuxury;
	uint32_t blueLevel;
	uint32_t blueValidTime;
	uint32_t blueYearValidTime;
	uint32_t blueLuxuryValidTime;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, isBlue);
		PACKET_DECODE(UInt32, isBlueYear);
		PACKET_DECODE(UInt32, isBlueLuxury);
		PACKET_DECODE(UInt32, blueLevel);
		PACKET_DECODE(UInt32, blueValidTime);
		PACKET_DECODE(UInt32, blueYearValidTime);
		PACKET_DECODE(UInt32, blueLuxuryValidTime);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

//
DEFINE_RECEIVE_PACKET_BEGIN(CTransitPayGetTokenProtocol)
	byte cmd;
	byte subCmd;
	string token;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(String, token);
		PACKET_DECODE_SKIP(1);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CTransitFriendProtocol)
	byte cmd;
	byte subcmd;
	uint32_t count;
	vector<string> openids;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,cmd);
		PACKET_DECODE(Byte,subcmd);
		PACKET_DECODE(UInt32,count);
		if (count > 0)
		{
			openids.resize(count);
			for (uint32_t i=0; i<count; ++i)
			{
				PACKET_DECODE(String,openids[i]);
			}
		}
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

//返回服务器时间，精确到毫秒
DEFINE_SEND_PACKET_BEGIN(CSrvTimeProtocol)
	byte cmd;
	byte subCmd;
	uint32_t stime;	//秒
	uint32_t mtime; //毫秒
	IMPLEMENT_PACKET_ENCODE_BEGIN
		PACKET_ENCODE(Byte, cmd);
		PACKET_ENCODE(Byte, subCmd);
		PACKET_ENCODE(UInt32, stime);
		PACKET_ENCODE(UInt32, mtime);
	IMPLEMENT_PACKET_ENCODE_END
DEFINE_SEND_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CHeartBeatProtocol)
	byte cmd;
	byte subCmd;
	uint32_t clientTime;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, clientTime);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

//定时器消息包
DEFINE_SEND_PACKET_BEGIN(CTimerProtocol)
	uint64_t utime;
	IMPLEMENT_PACKET_ENCODE_BEGIN
		PACKET_ENCODE(UInt64,utime);
	IMPLEMENT_PACKET_ENCODE_END

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(UInt64, utime);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_SEND_PACKET_END


DEFINE_SEND_PACKET_BEGIN(CLoginRspProtocol)
	byte cmd;
	byte subcmd;
	byte loginRet;
	IMPLEMENT_PACKET_ENCODE_BEGIN
		PACKET_ENCODE(Byte,cmd);
		PACKET_ENCODE(Byte,subcmd);
		PACKET_ENCODE(Byte,loginRet);
	IMPLEMENT_PACKET_ENCODE_END
DEFINE_SEND_PACKET_END

#endif /* PROTOCOLLOGIN_H_ */
