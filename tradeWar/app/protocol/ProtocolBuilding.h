/*
 * ProtocolBuilding.h
 *
 *  Created on: 2015年9月18日
 *      Author: asdf
 */

#ifndef _PROTOCOL_BUILDING_H_
#define _PROTOCOL_BUILDING_H_

#include "Kernel.h"
#include "CommData.h"

// 查询单个建筑信息
DEFINE_RECEIVE_PACKET_BEGIN(CQueryOneBuildingProtocol)
	byte cmd;
	byte subCmd;
	uint32_t ud; // ud

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, ud);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END


// 建造
DEFINE_RECEIVE_PACKET_BEGIN(CBuildBuildingProtocol)
	byte cmd;
	byte subCmd;
	uint16_t bId; // id
	Property x; // x坐标
	Property y; // y坐标

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt16, bId);
		PACKET_DECODE(UInt32, x.pui);
		PACKET_DECODE(UInt32, y.pui);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 移动
DEFINE_RECEIVE_PACKET_BEGIN(CMoveBuildingProtocol)
	byte cmd;
	byte subCmd;
	uint32_t ud; // ud
	Property x; // x坐标
	Property y; // y坐标

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, ud);
		PACKET_DECODE(UInt32, x.pui);
		PACKET_DECODE(UInt32, y.pui);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 升级
DEFINE_RECEIVE_PACKET_BEGIN(CUpgradeBuildingProtocol)
	byte cmd;
	byte subCmd;
	uint32_t count; // 计数
	vector<uint32_t> udVec;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, count);
		udVec.resize(count);
		for (uint32_t i  = 0; i < count; ++i) {
			PACKET_DECODE(UInt32, udVec[i]);
		}
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 搜集资源
DEFINE_RECEIVE_PACKET_BEGIN(CCollectBuildingResourceProtocol)
		byte cmd;
		byte subCmd;
		uint32_t ud;
		uint32_t res;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, ud);
		PACKET_DECODE(UInt32, res);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

// 任务提交
DEFINE_RECEIVE_PACKET_BEGIN(CTaskSubmitProtocol)
		byte cmd;
		byte subCmd;
		uint32_t id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CTaskCountProtocol)
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

DEFINE_RECEIVE_PACKET_BEGIN(CBuildingRemoveProtocol)
		byte cmd;
		byte subCmd;
		uint32_t ud;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, ud);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBuildingTowerUpgradeProtocol)
		byte cmd;
		byte subCmd;
		uint32_t id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

#endif /* _PROTOCOL_BUILDING_H_ */
