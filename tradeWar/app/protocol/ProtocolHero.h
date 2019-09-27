/*
 * ProtocolHero.h
 *
 *  Created on: 2015年12月8日
 *      Author: asdf
 */

#ifndef SERVERS_APP_PROTOCOL_PROTOCOLHERO_H_
#define SERVERS_APP_PROTOCOL_PROTOCOLHERO_H_

#include "Kernel.h"
// 升级
DEFINE_RECEIVE_PACKET_BEGIN(CTrainHeroProtocol)
	byte cmd;
	byte subCmd;
	uint32_t ud; // 英雄ud

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, ud);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 设置状态列表
DEFINE_RECEIVE_PACKET_BEGIN(CHeroSetStateProtocol)
	byte cmd;
	byte subCmd;
	uint32_t slotId; // 槽位id
	uint32_t newHeroUd; // 新选中的英雄ud

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, slotId);
		PACKET_DECODE(UInt32, newHeroUd);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 查询状态列表
DEFINE_RECEIVE_PACKET_BEGIN(CHeroQueryStateListProtocol)
	byte cmd;
	byte subCmd;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 英雄一键回血
DEFINE_RECEIVE_PACKET_BEGIN(CHeroFullHpProtocol)
	byte cmd;
	byte subCmd;
	uint32_t hud;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, hud);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 英雄刷新
DEFINE_RECEIVE_PACKET_BEGIN(CHeroRefreshProtocol)
	byte cmd;
	byte subCmd;
	byte refreshType;
	byte payType;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, refreshType);
		PACKET_DECODE(Byte, payType);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 英雄刷新一键十次
DEFINE_RECEIVE_PACKET_BEGIN(CHeroAutoRefreshProtocol)
	byte cmd;
	byte subCmd;
	byte idx;
	byte payType;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, idx);
		PACKET_DECODE(Byte, payType);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 英雄培养
DEFINE_RECEIVE_PACKET_BEGIN(CHeroCultureProtocol)
	byte cmd;
	byte subCmd;
	uint32_t hud;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, hud);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 英雄升星
DEFINE_RECEIVE_PACKET_BEGIN(CHeroUpStarProtocol)
	byte cmd;
	byte subCmd;
	uint32_t hud;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, hud);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 英雄花钱回血
DEFINE_RECEIVE_PACKET_BEGIN(CHeroPayToFullHpProtocol)
	byte cmd;
	byte subCmd;
	uint32_t hud;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, hud);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 金盾铁甲加固
DEFINE_RECEIVE_PACKET_BEGIN(CHeroShieldArmorReinforceProtocol)
	byte cmd;
	byte subCmd;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 解雇将领
DEFINE_RECEIVE_PACKET_BEGIN(CHeroFiredProtocol)
	byte cmd;
	byte subCmd;
	uint32_t hud;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, hud);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CHeroBuddyProtocol)
	byte cmd;
	byte subCmd;
	uint32_t ud;
	byte pos;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, ud);
		PACKET_DECODE(Byte, pos);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 英雄潜能提升属性
DEFINE_RECEIVE_PACKET_BEGIN(CHeroQueryPropChangeByPointProtocol)
	byte cmd;
	byte subCmd;
	uint32_t hud;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, hud);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 查询积分兑换列表
DEFINE_RECEIVE_PACKET_BEGIN(CHeroQueryCreditTradeListProtocol)
	byte cmd;
	byte subCmd;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 刷新积分兑换列表
DEFINE_RECEIVE_PACKET_BEGIN(CHeroRefreshCreditTradeListProtocol)
	byte cmd;
	byte subCmd;
	byte payType;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, payType);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 积分兑换物品
DEFINE_RECEIVE_PACKET_BEGIN(CHeroCreditTradeProtocol)
	byte cmd;
	byte subCmd;
	uint32_t id;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 俘虏将领
DEFINE_RECEIVE_PACKET_BEGIN(CHeroCaptiveProtocol)
	byte cmd;
	byte subCmd;
	uint32_t captiveUid;
	uint32_t captiveUd;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, captiveUid);
		PACKET_DECODE(UInt32, captiveUd);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 营救将领
DEFINE_RECEIVE_PACKET_BEGIN(CHeroRescueProtocol)
	byte cmd;
	byte subCmd;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CHeroEnergyCostProtocol)
	byte cmd;
	byte subCmd;
	uint32_t ud;
	uint32_t cost;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, ud);
		PACKET_DECODE(UInt32, cost);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CHeroEnergyAddProtocol)
	byte cmd;
	byte subCmd;
	uint32_t ud;
	uint32_t eqid;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, ud);
		PACKET_DECODE(UInt32, eqid);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 解锁武将
DEFINE_RECEIVE_PACKET_BEGIN(CHeroUnLockProtocol)
	byte cmd;
	byte subCmd;
	uint32_t id;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END


#endif /* SERVERS_APP_PROTOCOL_PROTOCOLHERO_H_ */