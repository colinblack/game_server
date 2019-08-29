/*
 * ProtocolMisc.h
 *
 *  Created on: 2015-12-30
 *      Author: Administrator
 */

#ifndef PROTOCOLMISC_H_
#define PROTOCOLMISC_H_

#include "Kernel.h"

DEFINE_RECEIVE_PACKET_BEGIN(CRewardQueryProtocol)
	byte protocolType;
	byte command;
	uint32_t activityId;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(UInt32, activityId);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CRewardGetProtocol)
	byte protocolType;
	byte command;
	uint32_t activityId;
	uint32_t rewardIndex;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(UInt32, activityId);
		PACKET_DECODE(UInt32, rewardIndex);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CInvadeListQueryProtocol)
	byte protocolType;
	byte command;
	uint32_t lfrom;
	uint32_t lto;
	uint32_t rfrom;
	uint32_t rto;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(UInt32, lfrom);
		PACKET_DECODE(UInt32, lto);
		PACKET_DECODE(UInt32, rfrom);
		PACKET_DECODE(UInt32, rto);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CInvadeOverProtocol)
	byte protocolType;
	byte command;
	double battleId;
	uint32_t win;
	uint32_t point;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Double, battleId);
		PACKET_DECODE(UInt32, win);
		PACKET_DECODE(UInt32, point);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CLoginRewardProtocol)
	byte protocolType;
	byte command;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END


DEFINE_RECEIVE_PACKET_BEGIN(CQQGameGrowRewardProtocol)
	byte protocolType;
	byte command;
	byte id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Byte, id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END




DEFINE_RECEIVE_PACKET_BEGIN(CQZoneGrowRewardProtocol)
	byte protocolType;
	byte command;
	byte id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Byte, id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CActivityTimeProtocol)
	byte protocolType;
	byte command;
	uint16_t actId;
	uint32_t beginTime;
	uint32_t endTime;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(UInt16, actId);
		PACKET_DECODE(UInt32, beginTime);
		PACKET_DECODE(UInt32, endTime);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CYellowQueryProtocol)
	byte protocolType;
	byte command;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CYellowGetProtocol)
	byte protocolType;
	byte command;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBlueDailyGetProtocol)
	byte protocolType;
	byte command;
	byte type;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Byte,type);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBlueLevelUpGetProtocol)
	byte protocolType;
	byte command;
	byte id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Byte,id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CInviteProtocol)
	byte protocolType;
	byte command;
	string open_id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(String,open_id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CInviteAwardProtocol)
	byte protocolType;
	byte command;
	uint32_t id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(UInt32,id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CAdvertChatProtocol)
	byte protocolType;
	byte command;
	uint32_t key;
	string msg;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(UInt32,key);
		PACKET_DECODE(String,msg);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CAddictionRateProtocol)
	byte protocolType;
	byte command;
	float rate;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Float,rate);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CMatchExitRoomProtocol)
	byte protocolType;
	byte command;
	uint32_t room_id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(UInt32,room_id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CMatchKickRoomProtocol)
	byte protocolType;
	byte command;
	uint32_t room_id;
	uint32_t uid_to_kick;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(UInt32,room_id);
		PACKET_DECODE(UInt32,uid_to_kick);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CMatchQueryRoomProtocol)
	byte protocolType;
	byte command;
	uint32_t room_id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(UInt32,room_id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CMatchCreateRoomProtocol)
	byte protocolType;
	byte command;
	uint32_t diff_level;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(UInt32,diff_level);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CMatchCreateRoomFromLoginProtocol)
	byte protocolType;
	byte command;
	uint32_t diff_level;
	uint32_t hero_type;
	uint32_t hero_level;
	uint32_t hero_star;
	uint32_t hero_quality;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(UInt32,diff_level);
		PACKET_DECODE(UInt32,hero_type);
		PACKET_DECODE(UInt32,hero_level);
		PACKET_DECODE(UInt32,hero_star);
		PACKET_DECODE(UInt32,hero_quality);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CMatchRoomProtocol)
	byte protocolType;
	byte command;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CMatchRoomFromLoginProtocol)
	byte protocolType;
	byte command;
	uint32_t hero_type;
	uint32_t hero_level;
	uint32_t hero_star;
	uint32_t hero_quality;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(UInt32,hero_type);
		PACKET_DECODE(UInt32,hero_level);
		PACKET_DECODE(UInt32,hero_star);
		PACKET_DECODE(UInt32,hero_quality);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CMatchPositiveProtocol)
	byte protocolType;
	byte command;
	uint32_t gate_level;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(UInt32,gate_level);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CMatchJoinRoomProtocol)
	byte protocolType;
	byte command;
	uint32_t room_id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(UInt32,room_id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CMatchJoinRoomFromLoginProtocol)
	byte protocolType;
	byte command;
	uint32_t room_id;
	uint32_t hero_type;
	uint32_t hero_level;
	uint32_t hero_star;
	uint32_t hero_quality;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(UInt32,room_id);
		PACKET_DECODE(UInt32,hero_type);
		PACKET_DECODE(UInt32,hero_level);
		PACKET_DECODE(UInt32,hero_star);
		PACKET_DECODE(UInt32,hero_quality);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CMatchBattleStartProtocol)
	byte protocolType;
	byte command;
	uint32_t room_id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(UInt32,room_id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CMatchBattleOverProtocol)
	byte protocolType;
	byte command;
	double battleId;
	uint32_t room_id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Double, battleId);
		PACKET_DECODE(UInt32,room_id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CMatchPositiveBattleOverProtocol)
	byte protocolType;
	byte command;
	double battleId;
	uint32_t gate_level;
	uint32_t room_id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Double, battleId);
		PACKET_DECODE(UInt32,gate_level);
		PACKET_DECODE(UInt32,room_id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CMatchBattlePointProtocol)
	byte protocolType;
	byte command;
	double battleId;
	uint32_t point;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Double, battleId);
		PACKET_DECODE(UInt32, point);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CMatchBattleExitProtocol)
	byte protocolType;
	byte command;
	double battleId;
	uint32_t room_id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Double, battleId);
		PACKET_DECODE(UInt32,room_id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CMatchBattleResultProtocol)
	byte protocolType;
	byte command;
	double battleId;
	uint32_t diff_level;
	byte ret;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Double, battleId);
		PACKET_DECODE(UInt32,diff_level);
		PACKET_DECODE(Byte,ret);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CHomeBaseMoveProtocol)
	byte protocolType;
	byte command;
	uint32_t from_location;
	uint32_t to_location;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(UInt32,from_location);
		PACKET_DECODE(UInt32,to_location);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CActiveOptionProtocol)
	byte protocolType;
	byte command;
	uint32_t option;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(UInt32,option);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CSevenDayFundsBuy)
	byte protocolType;
	byte command;
	byte type;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Byte,type);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CSevenDayFundsAward)
	byte protocolType;
	byte command;
	uint32_t id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(UInt32,id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CDailyGroupBuyAward)
	byte protocolType;
	byte command;
	uint32_t id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(UInt32,id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CTimeCostAcitivityBuy)
	byte protocolType;
	byte command;
	uint32_t pid;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(UInt32,pid);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBarbarianChallengeProtocol)
	byte protocolType;
	byte command;
	byte lvl;
	byte costType;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Byte,lvl);
		PACKET_DECODE(Byte,costType);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CGodChallengeProtocol)
	byte protocolType;
	byte command;
	byte lvl;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Byte,lvl);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBarbarianQueryAllianceRankProtocol)
	byte protocolType;
	byte command;
	byte country;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Byte,country);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CGoldenEggHitProtocol)
	byte protocolType;
	byte command;
	byte pos;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Byte,pos);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CGoldenEggRefreshProtocol)
	byte protocolType;
	byte command;
	byte type;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Byte,type);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END


DEFINE_RECEIVE_PACKET_BEGIN(CAllianceChargeAwardProtocol)
	byte protocolType;
	byte command;
	byte index;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Byte,index);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CAllianceChargeSaleProtocol)
	byte protocolType;
	byte command;
	byte index;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Byte,index);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END


DEFINE_RECEIVE_PACKET_BEGIN(CMonthChargeAwardProtocol)
	byte protocolType;
	byte command;
	uint16_t id;
	byte days;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(UInt16,id);
//		PACKET_DECODE(Byte,days);

	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CHeroExchangeProtocol)
	byte protocolType;
	byte command;
	byte id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Byte,id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CMaterialBuyProtocol)
	byte protocolType;
	byte command;
	byte id;
	uint32_t eqId;
	uint32_t count;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Byte,id);
		PACKET_DECODE(UInt32,eqId);
		PACKET_DECODE(UInt32,count);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CChargeReturnBuyProtocol)
	byte protocolType;
	byte command;
	byte id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Byte,id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CMagicSquareUpProtocol)
	byte protocolType;
	byte command;
	byte part;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Byte,part);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBusinessBuyProtocol)
	byte protocolType;
	byte command;
	byte id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Byte,id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END


DEFINE_RECEIVE_PACKET_BEGIN(CWarKingBuyProtocol)
	byte protocolType;
	byte command;
	byte type;
	uint32_t days;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,protocolType);
		PACKET_DECODE(Byte,command);
		PACKET_DECODE(Byte,type);
		PACKET_DECODE(UInt32,days);

	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(SoldierRefreshProtocol)
	byte cmd;
	byte subCmd;
	byte id;
	byte type;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, id);
		PACKET_DECODE(Byte, type);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CannonFireCostProtocol)
	byte cmd;
	byte subCmd;
	byte type;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, type);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(NewServerRewardProtocol)
	byte cmd;
	byte subCmd;
	byte type;
	byte index;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, type);
		PACKET_DECODE(Byte, index);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(DailyQuestFinishProtocol)
	byte cmd;
	byte subCmd;
	byte index;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, index);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(DailyQuestRewardProtocol)
	byte cmd;
	byte subCmd;
	byte index;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, index);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(FundRewardProtocol)
	byte cmd;
	byte subCmd;
	byte index;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, index);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

#endif /* PROTOCOLMISC_H_ */
