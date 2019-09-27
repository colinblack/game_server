/*
 * ProtocolSoldier.h
 *
 *  Created on: 2015年12月8日
 *      Author: asdf
 */

#ifndef _PROTOCOL_SOLDIER_H_
#define _PROTOCOL_SOLDIER_H_

#include "Kernel.h"

// 升级
DEFINE_RECEIVE_PACKET_BEGIN(CSoldierUpgradeProtocol)
		byte cmd;
		byte subCmd;
		uint32_t type; // 士兵类型
		uint32_t level; // 士兵等级

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, type);
		PACKET_DECODE(UInt32, level);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 升级立即完成
DEFINE_RECEIVE_PACKET_BEGIN(CSoldierUpgradeFinishNowProtocol)
		byte cmd;
		byte subCmd;
		byte payType;
		uint32_t type; // 士兵type

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, payType);
		PACKET_DECODE(UInt32, type);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 训练
DEFINE_RECEIVE_PACKET_BEGIN(CSoldierTrainProtocol)
		byte cmd;
		byte subCmd;
		uint32_t type; // 士兵type
		uint32_t count; // 士兵数量

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, type);
		PACKET_DECODE(UInt32, count);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 训练立即完成
DEFINE_RECEIVE_PACKET_BEGIN(CSoldierTrainFinishNowProtocol)
		byte cmd;
		byte subCmd;
		byte payType;
		uint32_t slotId;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, payType);
		PACKET_DECODE(UInt32, slotId);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 训练槽位开启
DEFINE_RECEIVE_PACKET_BEGIN(CSoldierTrainSlotOpenProtocol)
		byte cmd;
		byte subCmd;
		byte payType; // 1:金币 2:钻石

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, payType);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CSoldierStationQueryProtocol)
		byte cmd;
		byte subCmd;
		uint32_t uid;
		uint32_t ud;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, ud);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CSoldierStationProtocol)
		byte cmd;
		byte subCmd;
		uint32_t uid;
		uint32_t ud;
		byte size;
		vector<byte> vecCount;
		vector<uint32_t> vecType;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, ud);

		PACKET_DECODE(Byte, size);
		vecCount.resize(size);
		vecType.resize(size);
		for(size_t index = 0; index < size; ++index)
		{
			PACKET_DECODE(UInt32, vecType[index]);

			PACKET_DECODE(Byte, vecCount[index]);
		}

	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CSoldierStationDelProtocol)
		byte cmd;
		byte subCmd;
		uint32_t ud;
		uint32_t id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, ud);
		PACKET_DECODE(UInt32, id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CSoldierTrainCancelProtocol)
	byte cmd;
	byte subCmd;
	uint32_t id;
	uint32_t count;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, id);
		PACKET_DECODE(UInt32, count);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CSoldierStrongProtocol)
	byte cmd;
	byte subCmd;
	uint32_t type;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, type);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CSoldierTroopsProtocol)
	byte cmd;
	byte subCmd;
	uint32_t len;
	vector< pair<uint32_t, uint32_t> > troops;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		uint32_t len = 0;
		if (!reader.GetUInt32(len)) {
			return false;
		}
		for (uint32_t i = 0; i < len; ++i) {
			pair<uint32_t, uint32_t> item;
			if (!reader.GetUInt32(item.first)) {
				return false;
			}
			if (!reader.GetUInt32(item.second)) {
				return false;
			}
			troops.push_back(item);
		}
	IMPLEMENT_PACKET_DECODE_END

DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CSoldierDelRecoverTrainProtocol)
	byte cmd;
	byte subCmd;
	byte type;
	uint32_t len;
	vector<uint32_t> data;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, type);
		uint32_t len = 0;
		PACKET_DECODE(UInt32, len);
		for (uint32_t i = 0; i < len; ++i) {
			uint32_t id = 0;
			PACKET_DECODE(UInt32, id);
			data.push_back(id);
		}
	IMPLEMENT_PACKET_DECODE_END

DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CSoldierAddRecoverTrainProtocol)
	byte cmd;
	byte subCmd;
	vector< pair<uint32_t, uint32_t> > data;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		uint32_t len = 0;
		if (!reader.GetUInt32(len)) {
			return false;
		}
		for (uint32_t i = 0; i < len; ++i) {
			uint32_t id = 0;
			if (!reader.GetUInt32(id)) {
				return false;
			}
			uint32_t count = 0;
			if (!reader.GetUInt32(count)) {
				return false;
			}
			data.push_back(make_pair(id, count));
		}
	IMPLEMENT_PACKET_DECODE_END

DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CSoldierSellProtocol)
	byte cmd;
	byte subCmd;
	vector< pair<uint32_t, uint32_t> > data;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		uint32_t len = 0;
		if (!reader.GetUInt32(len)) {
			return false;
		}
		for (uint32_t i = 0; i < len; ++i) {
			uint32_t id = 0;
			if (!reader.GetUInt32(id)) {
				return false;
			}
			uint32_t count = 0;
			if (!reader.GetUInt32(count)) {
				return false;
			}
			data.push_back(make_pair(id, count));
		}
	IMPLEMENT_PACKET_DECODE_END

DEFINE_RECEIVE_PACKET_END

#endif /* _PROTOCOL_SOLDIER_H_ */
