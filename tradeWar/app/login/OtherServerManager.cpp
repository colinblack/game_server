/*
 * OtherServerManager.cpp
 *
 *  Created on: 2019年3月6日
 *      Author: Administrator
 */

#include "OtherServerManager.h"
#include "PlayerManager.h"
#include "BattleManager.h"

OtherServerManager::OtherServerManager(){
}
OtherServerManager::~OtherServerManager(){
}
bool OtherServerManager::doPacket(CNetPacket *p) {
	switch (p->subCmd) {
	case PROTOCOL_SUBCMD_OTHSRV_INTERACT_REQ:
		doUserInteractReq(p);
		break;
	case PROTOCOL_SUBCMD_OTHSRV_INTERACT_RESP:
		doUserInteractResp(p);
		break;
	case PROTOCOL_SUBCMD_OTHSRV_INFO_REQ:
		doUserInfoReq(p);
		break;
	case PROTOCOL_SUBCMD_OTHSRV_INFO_RESP:
		doUserInfoResp(p);
		break;
	}
	return true;
}
bool OtherServerManager::sendUserInteractReq(uint32_t myuid, uint32_t othuid, uint32_t lv, uint32_t type, const string &name, const string &pic) {
	CNetPacket sp;
	sp.uid = othuid;
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_OTHSRV);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_OTHSRV_INTERACT_REQ);
	PACKET_ENCODE(UInt32, myuid);
	PACKET_ENCODE(Byte, lv);
	PACKET_ENCODE(Byte, type);
	PACKET_ENCODE(String, name);
	PACKET_ENCODE(String, pic);
	LogicManager::getInstance()->sendToLogin(&sp);
	return true;
}
bool OtherServerManager::sendUserInfoReq(uint32_t myuid, uint32_t othuid) {
	CNetPacket sp;
	sp.uid = othuid;
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_OTHSRV);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_OTHSRV_INFO_REQ);
	PACKET_ENCODE(UInt32, myuid);
	LogicManager::getInstance()->sendToLogin(&sp);
	return true;
}
bool OtherServerManager::doUserInteractReq(CNetPacket *p) {
	uint32_t uid = p->uid;
	COthSrvUserInteractReqProtocol proto;
	if (!proto.Decode(p->GetBody())) {
		error_log("decode error uid=%u", uid);
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadForcePlayer(uid);
	if (player == NULL) {
		error_log("load playe error uid=%u", uid);
		return onUserInteractResp(proto.uid, R_ERROR, 0);
	}
	int16_t cnt = 0;
	if (!player->onInteract(proto.uid, proto.lv, proto.type, proto.name, proto.pic, cnt)) {
		error_log("interact error uid=%u", uid);
		return onUserInteractResp(proto.uid, R_ERROR, 0);
	}
	BUSI_MISC("play|interact|%u|%u|%u|%u", proto.uid, uid, static_cast<uint32_t>(proto.type), Time::GetGlobalTime());
	onUserInteractResp(proto.uid, R_SUCCESS, cnt);
	return true;
}
bool OtherServerManager::doUserInteractResp(CNetPacket *p) {
	uint32_t uid = p->uid;
	Player *player = PlayerManager::getInstance()->LoadForcePlayer(uid);
	if (player == NULL) {
		return false;
	}
	COthSrvUserInteractRespProtocol proto;
	if (!proto.Decode(p->GetBody())) {
		return player->onInteractResp(R_ERROR, proto.cnt);
	}
	player->onInteractResp(proto.ret, proto.cnt);
	return true;
}
bool OtherServerManager::doUserInfoReq(CNetPacket *p) {
	uint32_t uid = p->uid;
	COthSrvUserInfoReqProtocol proto;
	if (!proto.Decode(p->GetBody())) {
		error_log("decode error uid=%u", uid);
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadForcePlayer(uid);
	if (player == NULL) {
		error_log("load playe error uid=%u", uid);
		return false;
	}
	CNetPacket sp;
	sp.uid = proto.uid;
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_OTHSRV);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_OTHSRV_INFO_RESP);
	BattleManager::getInstance()->packArchive(proto.uid, sp.GetBody(), player);
	LogicManager::getInstance()->sendToLogin(&sp);
	return true;
}
bool OtherServerManager::doUserInfoResp(CNetPacket *p) {
	uint32_t uid = p->uid;
	CNetPacket sp;
	sp.uid = uid;
	sp.GetBody()->AppendBuffer(p->GetBody());
	uint32_t nsize = sp.GetBody()->GetSize();
	sp.GetBody()->SetSize(0);
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_BATTLE);
	PACKET_ENCODE(Byte, PROTOCOL_RSP_SUBCMD_BATTLE_SPY);
	sp.GetBody()->SetSize(nsize);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
bool OtherServerManager::onUserInteractResp(uint32_t uid, byte ret, int16_t cnt) {
	CNetPacket sp;
	sp.uid = uid;
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_OTHSRV);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_OTHSRV_INTERACT_RESP);
	PACKET_ENCODE(Byte, ret);
	PACKET_ENCODE(Int16, cnt);
	LogicManager::getInstance()->sendToLogin(&sp);
	return true;
}
