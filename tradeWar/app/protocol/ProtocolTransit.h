/*
 * ProtocolTransit.h
 *
 *  Created on: 2016-3-15
 *      Author: Administrator
 */

#ifndef PROTOCOLTRANSIT_H_
#define PROTOCOLTRANSIT_H_

DEFINE_RECEIVE_PACKET_BEGIN(CLoginBodyProtocol)
	byte cmd;
	byte subCmd;
	string openId;
	string openKey;
	unsigned spandID;
	unsigned serverID;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(String, openId);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, openKey);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(UInt32, spandID);
		PACKET_DECODE(UInt32, serverID);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(COfflineProtocol)
	byte cmd;
	byte subCmd;
	uint32_t uid;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, uid);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBuyGoodsTransitAppProtocol)
	byte cmd;
	byte subCmd;
	uint32_t uid;
	string openId;
	string openKey;
	string itemId;
	string pf;
	string pfKey;
	uint32_t server_id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(String, openId);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, openKey);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, itemId);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, pf);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, pfKey);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(UInt32, server_id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CPayGetTokenTransitAppProtocol)
	byte cmd;
	byte subCmd;
	string openId;
	string openKey;
	string discountId;
	string tokenType;
	string pf;
	string pfKey;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(String, openId);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, openKey);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, discountId);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, tokenType);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, pf);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, pfKey);
		PACKET_DECODE_SKIP(1);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CTencentDeliverProtocol)
	string payitem;
	uint32_t amt;
	int32_t payamt_coins;
	int32_t pubacct_payamt_coins;
	int32_t socketFd;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(String, payitem);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(UInt32, amt);
		PACKET_DECODE(Int32, payamt_coins);
		PACKET_DECODE(Int32, pubacct_payamt_coins);
		PACKET_DECODE(Int32, socketFd);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CLoginDeliverProtocol)
	byte protocolType;
	byte command;
	uint32_t ret;
	int socketFd;
	uint32_t server_id;
	uint32_t uid;
	uint32_t item_id;
	uint32_t price;
	int32_t payamt_coins;
	int32_t pubacct_payamt_coins;
	uint32_t count;
	int cash;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, protocolType);
		PACKET_DECODE(Byte, command);
		PACKET_DECODE(UInt32, ret);
		PACKET_DECODE(Int32, socketFd);
		PACKET_DECODE(UInt32, server_id);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, item_id);
		PACKET_DECODE(UInt32, price);
		PACKET_DECODE(Int32, payamt_coins);
		PACKET_DECODE(Int32, pubacct_payamt_coins);
		PACKET_DECODE(UInt32, count);
		PACKET_DECODE(Int32, cash);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

//
DEFINE_RECEIVE_PACKET_BEGIN(CLoginGetBlueInfoProtocol)
	byte cmd;
	byte subCmd;
	string openId;
	string openKey;
	uint32_t span_id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(String, openId);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, openKey);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(UInt32, span_id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CTransitGetBalanceProtocol)
	byte cmd;
	byte subCmd;
	uint32_t uid;
	string openId;
	string openKey;
	string pf;
	uint32_t platform;
	uint32_t server_id;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(String, openId);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, openKey);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, pf);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(UInt32, platform);
		PACKET_DECODE(UInt32, server_id);
	IMPLEMENT_PACKET_DECODE_END

DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CTransitPayProtocol)
	byte cmd;
	byte subCmd;
	uint32_t uid;
	string openId;
	string openKey;
	string pf;
	uint32_t platform;
	uint32_t server_id;
	uint32_t itemId;
	uint32_t count;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(String, openId);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, openKey);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, pf);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(UInt32, platform);
		PACKET_DECODE(UInt32, server_id);
		PACKET_DECODE(UInt32, itemId);
		PACKET_DECODE(UInt32, count);
	IMPLEMENT_PACKET_DECODE_END

DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CTransitReportProtocol)
	byte cmd;
	byte subCmd;
	string msg;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(String, msg);
	IMPLEMENT_PACKET_DECODE_END

DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CTransitGiftExhangeProtocol)
	byte cmd;
	byte subCmd;
	string openid;
	string openkey;
	string pf;
	uint32_t giftid;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, giftid);
		PACKET_DECODE(String, openid);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, openkey);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, pf);
		PACKET_DECODE_SKIP(1);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CTransitGiftExhangeResProtocol)
	byte cmd;
	byte subCmd;
	int code;
	uint32_t giftid;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Int32, code);
		PACKET_DECODE(UInt32, giftid);
	IMPLEMENT_PACKET_DECODE_END

DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CTransitPerOrderProtocol)
	byte cmd;
	byte subCmd;
	uint32_t uid;
	string openId;
	string openKey;
	string pf;
	uint32_t goodId;
	uint32_t goodCount;
	uint32_t server_id;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(String, openId);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, openKey);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, pf);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(UInt32, goodId);
		PACKET_DECODE(UInt32, goodCount);
		PACKET_DECODE(UInt32, server_id);
	IMPLEMENT_PACKET_DECODE_END

DEFINE_RECEIVE_PACKET_END

#endif /* PROTOCOLTRANSIT_H_ */
