/*
 * ProtocolBuyGoods.h
 *
 *  Created on: 2016-3-17
 *      Author: Administrator
 */

#ifndef PROTOCOLBUYGOODS_H_
#define PROTOCOLBUYGOODS_H_

#include "Kernel.h"

DEFINE_RECEIVE_PACKET_BEGIN(CBuyGoodsProtocol)
	byte cmd;
	byte subCmd;
	string openId;
	string openKey;
	string itemId;
	string pf;
	string pfKey;
	string appId;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
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
		PACKET_DECODE(String, appId);
//		PACKET_DECODE_SKIP(1);
	IMPLEMENT_PACKET_DECODE_END

	IMPLEMENT_PACKET_ENCODE_BEGIN
		PACKET_ENCODE(Byte, cmd);
		PACKET_ENCODE(Byte, subCmd);
		PACKET_ENCODE(String, itemId);
		PACKET_ENCODE(Byte,0);
		PACKET_ENCODE(String, openId);
		PACKET_ENCODE(Byte,0);
		PACKET_ENCODE(String, openKey);
		PACKET_ENCODE(Byte,0);
		PACKET_ENCODE(String, pf);
		PACKET_ENCODE(Byte,0);
		PACKET_ENCODE(String, pfKey);
		PACKET_ENCODE(Byte,0);
		PACKET_ENCODE(String, appId);
		PACKET_ENCODE(Byte,0);
	IMPLEMENT_PACKET_ENCODE_END

DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBuyGoodsRetProtocol)
	byte cmd;
	byte subCmd;
	string appId;
	string url_params;
	uint32_t uid;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(String, appId);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, url_params);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(UInt32, uid);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

//鍥炶皟鍙戣揣
DEFINE_RECEIVE_PACKET_BEGIN(CDeliveryRetProtocol)
	byte protocolType;
	byte command;
	uint32_t itemid;
	uint32_t price;
	int32_t payamt_coins;
	int32_t pubacct_payamt_coins;
	uint32_t count;
	int cash;
	uint32_t uid;
	int socketFd;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, protocolType);
		PACKET_DECODE(Byte, command);
		PACKET_DECODE(UInt32, itemid);
		PACKET_DECODE(UInt32, price);
		PACKET_DECODE(Int32, payamt_coins);
		PACKET_DECODE(Int32, pubacct_payamt_coins);
		PACKET_DECODE(UInt32, count);
		PACKET_DECODE(Int32, cash);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(Int32, socketFd);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END


DEFINE_RECEIVE_PACKET_BEGIN(CBlueRenewProtocol)
	byte cmd;
	byte subCmd;
	uint32_t uid;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, uid);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBuyGoodGetBalanceProtocol)
	byte cmd;
	byte subCmd;
	string openId;
	string openKey;
	string pf;
	uint32_t platform;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(String, openId);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, openKey);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, pf);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(UInt32, platform);
	IMPLEMENT_PACKET_DECODE_END;

DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBuyGoodGetBalanceResProtocol)
	byte cmd;
	byte subCmd;
	uint32_t uid;
	byte code;
	uint32_t score;
	string mpid;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(Byte, code);
		PACKET_DECODE(UInt32, score);
		PACKET_DECODE(String, mpid);
	IMPLEMENT_PACKET_DECODE_END;

DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBuyGoodPayProtocol)
	byte cmd;
	byte subCmd;
	string openId;
	string openKey;
	string pf;
	uint32_t platform;
	uint32_t itemId;
	uint32_t count;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(String, openId);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, openKey);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, pf);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(UInt32, platform);
		PACKET_DECODE(UInt32, itemId);
		PACKET_DECODE(UInt32, count);
	IMPLEMENT_PACKET_DECODE_END;

DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBuyGoodPayResProtocol)
	byte cmd;
	byte subCmd;
	byte code;
	uint32_t uid;
	uint32_t itemid;
	string billon;
	uint32_t cash;
	uint32_t cost;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, code);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, itemid);
		PACKET_DECODE(String, billon);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(UInt32, cash);
		PACKET_DECODE(UInt32, cost);
	IMPLEMENT_PACKET_DECODE_END;

DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBuyGoodPerOrderProtocol)
	byte cmd;
	byte subCmd;
	string openId;
	string openKey;
	string pf;
	uint32_t goodId;
	uint32_t goodCount;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(String, openId);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, openKey);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(String, pf);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(UInt32, goodId);
		PACKET_DECODE(UInt32, goodCount);
	IMPLEMENT_PACKET_DECODE_END;

DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBuyGoodPerOrderResProtocol)
	byte cmd;
	byte subCmd;
	byte code;
	uint32_t uid;
	string prepayId;
	uint32_t amt;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(Byte, code);
		PACKET_DECODE(String, prepayId);
		PACKET_DECODE_SKIP(1);
		PACKET_DECODE(UInt32, amt);
	IMPLEMENT_PACKET_DECODE_END;

DEFINE_RECEIVE_PACKET_END

#endif /* PROTOCOLBUYGOODS_H_ */
