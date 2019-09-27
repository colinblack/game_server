/*
 * ProtocolEquip.h
 *
 *  Created on: 2016-1-28
 *      Author: Administrator
 */

#ifndef PROTOCOLEQUIP_H_
#define PROTOCOLEQUIP_H_

#include "Kernel.h"
//#include "PropertyConfig.h"

//穿装备
DEFINE_RECEIVE_PACKET_BEGIN(CWearEquipProtocol)
	byte cmd;
	byte subCmd;
	uint32_t hud;	//英雄ud
	uint32_t eud; 	//装备ud
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, hud);
		PACKET_DECODE(UInt32, eud);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

//脱装备
DEFINE_RECEIVE_PACKET_BEGIN(CUnwearEquipProtocol)
	byte cmd;
	byte subCmd;
	uint32_t hud;	//英雄ud
	uint32_t eud; 	//装备ud
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, hud);
		PACKET_DECODE(UInt32, eud);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CStrengthProtocol)
	byte cmd;
	byte subCmd;
	uint32_t hud;
	uint32_t eud;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, hud);
		PACKET_DECODE(UInt32, eud);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CUpgradeEquipProtocol)
	byte cmd;
	byte subCmd;
	uint32_t hud;
	uint32_t eud;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, hud);
		PACKET_DECODE(UInt32, eud);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CStrengthQueryProtocol)
	byte cmd;
	byte subCmd;
	uint32_t hud;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, hud);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CStoneComposeProtocol)
	byte cmd;
	byte subCmd;
	byte flag; //0:普通合成 1:批量
	uint32_t type;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, flag);
		PACKET_DECODE(UInt32, type);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CStoneMountProtocol)
	byte cmd;
	byte subCmd;
	uint32_t hud;	//装备ud
	uint32_t eud;	//装备ud
	uint32_t sud;	//宝石ud
	byte slot;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, hud);
		PACKET_DECODE(UInt32, eud);
		PACKET_DECODE(UInt32, sud);
		PACKET_DECODE(Byte, slot);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBuildingStoneMountProtocol)
	byte cmd;
	byte subCmd;
	uint32_t bud;	//英雄ud
	uint32_t sud;	//宝石ud
	byte slot;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, bud);
		PACKET_DECODE(UInt32, sud);
		PACKET_DECODE(Byte, slot);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CStoneUnMountProtocol)
	byte cmd;
	byte subCmd;
	uint32_t hud;	//英雄ud
	uint32_t eud;	//英雄ud
	uint32_t sud;	//宝石ud
	byte slot;		//槽位
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, hud);
		PACKET_DECODE(UInt32, eud);
		PACKET_DECODE(UInt32, sud);
		PACKET_DECODE(Byte, slot);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBuildingStoneUnMountProtocol)
	byte cmd;
	byte subCmd;
	uint32_t bud;	//英雄ud
	uint32_t sud;	//宝石ud
	byte slot;		//槽位
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, bud);
		PACKET_DECODE(UInt32, sud);
		PACKET_DECODE(Byte, slot);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CStoneReplaceProtocol)
	byte cmd;
	byte subCmd;
	uint32_t hud;	//英雄ud
	uint32_t eud;
	uint32_t oldSud;	//旧宝石ud
	uint32_t newSud;	//新宝石ud
	byte slot;		//槽位
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, hud);
		PACKET_DECODE(UInt32, eud);
		PACKET_DECODE(UInt32, oldSud);
		PACKET_DECODE(UInt32, newSud);
		PACKET_DECODE(Byte, slot);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBuildingStoneReplaceProtocol)
	byte cmd;
	byte subCmd;
	uint32_t hud;	//英雄ud
	uint32_t oldSud;	//旧宝石ud
	uint32_t newSud;	//新宝石ud
	byte slot;		//槽位
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, hud);
		PACKET_DECODE(UInt32, oldSud);
		PACKET_DECODE(UInt32, newSud);
		PACKET_DECODE(Byte, slot);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CStoneUpgradeProtocol)
	byte cmd;
	byte subCmd;
	uint32_t hud;	//英雄ud
	uint32_t eud;	//英雄ud
	uint32_t sud;	//宝石ud
	byte slot;		//槽位
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, hud);
		PACKET_DECODE(UInt32, eud);
		PACKET_DECODE(UInt32, sud);
		PACKET_DECODE(Byte, slot);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBuildingStoneUpgradeProtocol)
	byte cmd;
	byte subCmd;
	uint32_t hud;	//英雄ud
	uint32_t sud;	//宝石ud
	byte slot;		//槽位
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, hud);
		PACKET_DECODE(UInt32, sud);
		PACKET_DECODE(Byte, slot);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CEquipmentSmeltProtocol)
	byte cmd;
	byte subCmd;
	byte autoBuy; // 是否自动购买
	uint32_t hud; // 装备Ud
	uint32_t equd; // 装备Ud
	byte size;
	set<byte> removeId;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, autoBuy);
		PACKET_DECODE(UInt32, hud);
		PACKET_DECODE(UInt32, equd);
		PACKET_DECODE(Byte, size);
		for(uint32_t i = 0; i < size; ++i)
		{
			byte attrId = 0;
			PACKET_DECODE(Byte, attrId);
			removeId.insert(attrId);
		}
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CEquipmentSetBuildProtocol)
	byte cmd;
	byte subCmd;
	byte part; // 部位
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, part);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CEquipmentSetUpgradeProtocol)
	byte cmd;
	byte subCmd;
	uint32_t equd; // 部位
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, equd);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CEquipmentSetChangeProtocol)
	byte cmd;
	byte subCmd;
	uint32_t equd; // 部位
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, equd);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CStoneUnLockProtocol)
	byte cmd;
	byte subCmd;
	uint32_t hud;	//英雄ud
	uint32_t eud;	//装备ud
	byte lock;		//位置1,2,3,4,5
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, hud);
		PACKET_DECODE(UInt32, eud);
		PACKET_DECODE(Byte, lock);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBuildingStoneUnLockProtocol)
	byte cmd;
	byte subCmd;
	uint32_t bud;	//英雄ud
	byte lock;		//位置1,2,3,4,5
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, bud);
		PACKET_DECODE(Byte, lock);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CStoneLockQueryProtocol)
	byte cmd;
	byte subCmd;
	uint32_t hud;	//英雄ud
	byte part;		//部为1,2,3,4,5,6
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, hud);
		PACKET_DECODE(Byte, part);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBuildingStoneLockQueryProtocol)
	byte cmd;
	byte subCmd;
	uint32_t bud;	//英雄ud
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, bud);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CEquipSellProtocol)
	byte cmd;
	byte subCmd;
	uint32_t ud;	//装备ud
	uint32_t count;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, ud);
		PACKET_DECODE(UInt32, count);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CEquipSellAllProtocol)
	byte cmd;
	byte subCmd;
	uint32_t part;
	uint32_t prof;
	uint32_t quality;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, part);
		PACKET_DECODE(UInt32, prof);
		PACKET_DECODE(UInt32, quality);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBagUnlockProtocol)
	byte cmd;
	byte subCmd;
	byte type;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, type);//1:金币 2:钻石
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBuyItemProtocol)
	byte cmd;
	byte subCmd;
	uint32_t id;
	uint32_t count;
	byte flag;
	byte useNow;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, id);
		PACKET_DECODE(UInt32, count);
		PACKET_DECODE(Byte, flag);
		if (!reader.GetByte(useNow)){
			useNow = 0;
		}
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CEquipUseProtocol)
	byte cmd;
	byte subCmd;
	byte targetType;	// 目标类型
	uint32_t targetUd;		// 目标UD
	uint32_t equipId;
	uint32_t count;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, targetType);
		PACKET_DECODE(UInt32, targetUd);
		PACKET_DECODE(UInt32, equipId);
		PACKET_DECODE(UInt32, count);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CEquipGemPointProtocol)
	byte cmd;
	byte subCmd;
	uint32_t type;
	uint32_t point;
	uint32_t id;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, type);
		PACKET_DECODE(UInt32, point);
		PACKET_DECODE(UInt32, id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CEquipGemCombineProtocol)
	byte cmd;
	byte subCmd;
	uint32_t id;
	uint32_t all;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, id);
		PACKET_DECODE(UInt32, all);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CEquipCombineProtocol)
	byte cmd;
	byte subCmd;
	uint32_t id;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

#endif /* PROTOCOLEQUIP_H_ */
