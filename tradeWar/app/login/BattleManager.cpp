#include "BattleManager.h"
#include "ProtocolUser.h"
#include "OtherServerManager.h"

BattleManager::BattleManager() {
}

BattleManager::~BattleManager() {

}

bool BattleManager::doAccessPacket(CNetPacket * packet) {
	switch (packet->subCmd) {
	case PROTOCOL_SUBCMD_BATTLE_SPY:
		doBattleSpySingle(packet);
		break;
	case PROTOCOL_SUBCMD_BATTLE_BACK_HOME:
		doBattleHome(packet);
		break;
	default:
		LogicManager::getInstance()->transToBattle(packet);
		break;
	}
	return true;
}

bool BattleManager::doBattlePacket(CNetPacket * packet) {
	return true;
}

bool BattleManager::doBattleSpySingle(CNetPacket * packet) {
	CUserViewProtocol protocol;
	if (!protocol.Decode(&packet->body)) {
		error_log("CLoginSpyProtocol decode failed by uid=%u", packet->uid);
		sendBattleError(packet->uid, R_ERROR);
		return false;
	}
	if (packet->uid == protocol.uid) {
		error_log("same uid=%u", packet->uid);
		sendBattleError(packet->uid, R_ERROR);
		return false;
	}
	if (ServerConfig::getInstance()->IsMerged(Config::GetZoneByUID(protocol.uid))) {
		if (!sendPlayerArchive(packet->uid, protocol.uid)) {
			error_log("sendPlayerArchive fail srcUid=%u targetUid=%u", packet->uid, protocol.uid);
			sendBattleError(packet->uid, R_ERROR);
			return false;
		}
	} else {
		OtherServerManager::getInstance()->sendUserInfoReq(packet->uid, protocol.uid);
	}
	return true;
}

bool BattleManager::doBattleHome(CNetPacket* packet) {
	uint32_t uid = packet->uid;
	Player * player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (!player) {
		error_log("player is NULL uid=%u", uid);
		sendBattleError(uid, R_ERROR);
		return false;
	}

	player->initTimerList();
	player->sendBaseInfo();
	player->sendHomeInfo();

	return true;
}

bool BattleManager::sendBattleError(uint32_t uid, byte errorcode) {
	CNetPacket aPacket;
	aPacket.uid = uid;
	CBufferWriter selfWriter(&aPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_BATTLE);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_BATTLE_ERROR);
	selfWriter.AppendDouble(0);
	selfWriter.AppendByte(errorcode);
	LogicManager::getInstance()->sendToAccess(&aPacket);
	error_log("battle error uid=%u errno:%d", uid, errorcode);
	return true;
}

bool BattleManager::sendPlayerArchive(uint32_t recvUid, uint32_t targetUid) {
	Player *player = PlayerManager::getInstance()->LoadForcePlayer(targetUid);
	if (!player) {
		error_log("player is NULL uid=%u", targetUid);
		return false;
	}
	CNetPacket sPacket;
	sPacket.uid = recvUid;
	CBufferWriter selfWriter(&sPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_BATTLE);
	selfWriter.AppendByte(PROTOCOL_RSP_SUBCMD_BATTLE_SPY);
	if (!packArchive(recvUid, sPacket.GetBody(), player)) {
		error_log("pack archive error uid=%u", targetUid);
		return false;
	}
	LogicManager::getInstance()->sendToAccess(&sPacket);
	return true;
}

bool BattleManager::packPlayerInfo(uint32_t uid, IBuffer* buff, Player* player) {
	PACKET_ENCODE_BEGIN(buff);
	if (player == NULL) {
		PACKET_ENCODE(UInt32, 0);
		return true;
	}
	const DataUser &sData = player->getUserInfo();
	PACKET_ENCODE(UInt32, sData.uid);
	PACKET_ENCODE(UInt32, player->getUserCombat());
	PACKET_ENCODE(UInt32, sData.level);
	PACKET_ENCODE(UInt32, sData.exp);
	PACKET_ENCODE(UInt32, sData.viplevel);
	PACKET_ENCODE(String, sData.name);
	PACKET_ENCODE(Byte, 0);
	PACKET_ENCODE(String, sData.figure_url);
	PACKET_ENCODE(Byte, 0);
	PACKET_ENCODE(Int16, sData.help_count);
	bool flag = player->getInteractManager()->checkDaily(uid);
	PACKET_ENCODE(Byte, flag ? 1 : 0);
	return true;
}

bool BattleManager::packArchive(uint32_t uid, IBuffer* buff, Player* player) {
	if (buff == NULL) {
		return false;
	}
	if (!packPlayerInfo(uid, buff, player)) {
		return false;
	}
	if (!player->getTroopsManager()->packDefend(buff)) {
		return false;
	}
	if (!player->getSoldierManager()->packInfo(buff)) {
		return false;
	}
	if (!player->getTroopsManager()->packAttack(buff)) {
		return false;
	}
	if (!player->getSkillManager()->packSkill(buff)) {
		return false;
	}
	return true;
}
