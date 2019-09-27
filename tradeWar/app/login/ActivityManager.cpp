/*
 * ActivityManager.cpp
 *
 *  Created on: 2018年12月3日
 *      Author: Administrator
 */

#include "ActivityManager.h"
#include "ActivityTimeManager.h"
#include "PlayerManager.h"
#include "ActSevenDayTask.h"

ActivityManager::ActivityManager() {
	m_charge_act.clear();
	m_charge_act.push_back(e_ActivityTypeDailyChargeEquip);
	m_charge_act.push_back(e_ActivityTypeDailyChargeCash);
	m_charge_act.push_back(e_ActivityTypeContinueCharge);
}

ActivityManager::~ActivityManager() {
	map<uint32_t, ActivityUtil*>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		if (itr->second != NULL) {
			delete itr->second;
			itr->second = NULL;
		}
	}
	m_data.clear();
}
bool ActivityManager::onLogin() {
	vector<uint32_t> ids;
	set<uint32_t> can;
	ActivityTimeManager::getInstance()->getValidId(ids);
	vector<uint32_t>::iterator itr = ids.begin();
	for (; itr != ids.end(); ++itr) {
		ActivityUtil *act = loadActivity(*itr);
		if (act == NULL) {
			continue;
		}
		act->setNotify(false);
	}
	return true;
}
bool ActivityManager::onCharge() {
	set<uint32_t> can;
	vector<uint32_t>::iterator itr = m_charge_act.begin();
	for (; itr != m_charge_act.end(); ++itr) {
		ActivityUtil *act = loadActivity(*itr);
		if (act == NULL) {
			continue;
		}
		if (act->getNotify()) {
			continue;
		}
		if (!act->canReward()) {
			continue;
		}
		can.insert(*itr);
	}
	if (!can.empty()) {
		sendAllData(m_player->getUid(), can);
	}
	return true;
}
bool ActivityManager::onReload() {
	map<uint32_t, ActivityUtil*>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		ActivityUtil *act = itr->second;
		if (act == NULL) {
			continue;
		}
		act->checkVer();
	}
	return true;
}
bool ActivityManager::doPacket(CNetPacket *packet) {
	switch (packet->subCmd) {
	case PROTOCOL_SUBCMD_ACTIVITY_DATA:
		doGetData(packet);
		break;
	case PROTOCOL_SUBCMD_ACTIVITY_REWARD:
		doReward(packet);
		break;
	case PROTOCOL_SUBCMD_ACTIVITY_ADD_COUNT:
		doAddCount(packet);
		break;
	case PROTOCOL_SUBCMD_ACTIVITY_BUY_SCORE:
		doBuyScore(packet);
		break;
	case PROTOCOL_SUBCMD_ACTIVITY_LEVEL_REWARD:
		doLevelReward(packet);
		break;
	case PROTOCOL_SUBCMD_ACTIVITY_QUEST_REWARD:
		doQuestReward(packet);
		break;
	case PROTOCOL_SUBCMD_ACTIVITY_LOTTERY:
		doLottery(packet);
		break;
	case PROTOCOL_SUBCMD_ACTIVITY_ALL_DATA:
		doGetAllData(packet);
		break;
	}
	return true;
}

bool ActivityManager::load(uint32_t uid) {
	return true;
}

bool ActivityManager::onTimer() {
	return true;
}
bool ActivityManager::addSoldier(uint32_t v) {
	ActNewSrvSoldierRank *act = dynamic_cast<ActNewSrvSoldierRank*>(loadActivity(e_ActivityTypeSoldierRank));
	if (act != NULL) {
		act->addScore(v);
	}
	ActSevenDayTask *SDAct = dynamic_cast<ActSevenDayTask*>(loadActivity(e_ActivityTypeSevenDayTask));
	if (SDAct != NULL) {
		SDAct->onAddSoldier(v);
		SDAct->onSoldierColor();
	}
	ActSoldierRank *ract = dynamic_cast<ActSoldierRank*>(loadActivity(e_ActivityTypeSoldierRankNew));
	if (ract != NULL) {
		ract->addScore(v);
	}
	return true;
}
bool ActivityManager::addExp(uint32_t v, int chg) {
	ActNewSrvExpRank *act = dynamic_cast<ActNewSrvExpRank*>(loadActivity(e_ActivityTypeExpRank));
	if (act != NULL) {
		act->setScore(v);
	}
	ActSevenDayTask *SDAct = dynamic_cast<ActSevenDayTask*>(loadActivity(e_ActivityTypeSevenDayTask));
	if (SDAct != NULL) {
		SDAct->onExp(v);
	}
	if (chg > 0) {
		ActExpRank *ract = dynamic_cast<ActExpRank*>(loadActivity(e_ActivityTypeExpRankNew));
		if (ract != NULL) {
			ract->addScore(chg);
		}
	}
	return true;
}
bool ActivityManager::addPower(uint32_t v, int chg) {
	ActNewSrvPowerRank *act = dynamic_cast<ActNewSrvPowerRank*>(loadActivity(e_ActivityTypePowerRank));
	if (act != NULL) {
		act->setScore(v);
	}
	ActSevenDayTask *SDAct = dynamic_cast<ActSevenDayTask*>(loadActivity(e_ActivityTypeSevenDayTask));
	if (SDAct != NULL) {
		SDAct->onPower(v);
	}

	ActPowerRank *ract = dynamic_cast<ActPowerRank*>(loadActivity(e_ActivityTypePowerRankNew));
	if (ract != NULL) {
		ract->addScore(chg);
	}

	return true;
}
bool ActivityManager::addGem(uint32_t v) {
	ActNewSrvGemRank *act = dynamic_cast<ActNewSrvGemRank*>(loadActivity(e_ActivityTypeGemRank));
	if (act == NULL) {
		return false;
	}
	return act->setScore(v);
}
bool ActivityManager::addConsume(uint32_t v) {
	ActNewSrvConsumeRank *act = dynamic_cast<ActNewSrvConsumeRank*>(loadActivity(e_ActivityTypeConsumeRank));
	if (act != NULL) {
		act->addScore(v);
	}
	ActConsumeRank *ract = dynamic_cast<ActConsumeRank*>(loadActivity(e_ActivityTypeConsumeRankNew));
	if (ract != NULL) {
		ract->addScore(v);
	}
	return true;
}
bool ActivityManager::addTransport(uint32_t v) {
	ActNewSrvTransportRank *act = dynamic_cast<ActNewSrvTransportRank*>(loadActivity(e_ActivityTypeTransportRank));
	if (act != NULL) {
		act->addScore(v);
	}
	ActSevenDayTask *SDAct = dynamic_cast<ActSevenDayTask*>(loadActivity(e_ActivityTypeSevenDayTask));
	if (SDAct != NULL) {
		SDAct->onBoat(v);
	}
	ActBoatRank *ract = dynamic_cast<ActBoatRank*>(loadActivity(e_ActivityTypeBoatRankNew));
	if (ract != NULL) {
		ract->addScore(v);
	}
	return true;
}
bool ActivityManager::addCoins(uint32_t v) {
	ActNewSrvCoinsRank *act = dynamic_cast<ActNewSrvCoinsRank*>(loadActivity(e_ActivityTypeCoinsRank));
	if (act == NULL) {
		return false;
	}
	return act->addScore(v);
}
bool ActivityManager::addArena(uint32_t v) {
	ActNewSrvWorldBattleRank *act = dynamic_cast<ActNewSrvWorldBattleRank*>(loadActivity(e_ActivityTypeWorldBattleRank));
	if (act != NULL) {
		act->addScore(v);
	}
	ActSevenDayTask *SDAct = dynamic_cast<ActSevenDayTask*>(loadActivity(e_ActivityTypeSevenDayTask));
	if (SDAct != NULL) {
		SDAct->onArenaWin(1);
		SDAct->onArenaRank(v);
	}
	return true;
}
bool ActivityManager::addSoldierScore(uint32_t v) {
	ActSevenDayTask *SDAct = dynamic_cast<ActSevenDayTask*>(loadActivity(e_ActivityTypeSevenDayTask));
	if (SDAct != NULL) {
		SDAct->onSolderScore(v);
	}
	return true;
}
bool ActivityManager::addZhengWu(uint32_t v) {
	ActSevenDayTask *SDAct = dynamic_cast<ActSevenDayTask*>(loadActivity(e_ActivityTypeSevenDayTask));
	if (SDAct != NULL) {
		SDAct->onZhengwu(v);
	}
	return true;
}
bool ActivityManager::addBuildingUp(uint32_t v) {
	ActSevenDayTask *SDAct = dynamic_cast<ActSevenDayTask*>(loadActivity(e_ActivityTypeSevenDayTask));
	if (SDAct != NULL) {
		SDAct->onBuilding(v);
	}
	return true;
}
bool ActivityManager::addBoss(uint32_t v) {
	ActSevenDayTask *SDAct = dynamic_cast<ActSevenDayTask*>(loadActivity(e_ActivityTypeSevenDayTask));
	if (SDAct != NULL) {
		SDAct->onBoss(v);
	}
	return true;
}
bool ActivityManager::addDefendGate(uint32_t v) {
	ActSevenDayTask *SDAct = dynamic_cast<ActSevenDayTask*>(loadActivity(e_ActivityTypeSevenDayTask));
	if (SDAct != NULL) {
		SDAct->onDefendGate(v);
	}
	return true;
}
bool ActivityManager::addBattleGate(uint32_t v) {
	ActSevenDayTask *SDAct = dynamic_cast<ActSevenDayTask*>(loadActivity(e_ActivityTypeSevenDayTask));
	if (SDAct != NULL) {
		SDAct->onBattleGate(v);
	}
	return true;
}

bool ActivityManager::addTaskCount(uint32_t quest, uint32_t cnt) {
	if (cnt == 0) {
		return false;
	}
	ActivityUtil *act = loadActivity(e_ActivityTypeSevenTask);
	if (act == NULL) {
		return false;
	}
	ActSevenTask *dact = dynamic_cast<ActSevenTask*>(act);
	dact->doQuest(quest, cnt);
	return true;
}

bool ActivityManager::setBuyFlag() {
	ActivityUtil *act = loadActivity(e_ActivityTypeSevenTask);
	if (act == NULL) {
		return false;
	}
	ActSevenTask *dact = dynamic_cast<ActSevenTask*>(act);
	dact->setBuyFlag();
	return true;
}

bool ActivityManager::doGetData(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CActivityGetDataProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", uid);
		return false;
	}
	ActivityUtil *act = loadActivity(proto.id);
	if (act == NULL) {
		error_log("act timeout uid=%u id=%u", uid, proto.id);
		return false;
	}
	act->checkVer();
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_ACTIVITY);
	writer.AppendByte(PROTOCOL_SUBCMD_ACTIVITY_DATA);
	act->encodeData(sp.GetBody());
	writer.AppendUInt32(0);
	writer.AppendUInt32(0);
	PlayerManager::getInstance()->sendToAccess(&sp);
	debug_log("uid=%u,id=%u,buff_len=%u", uid, proto.id, sp.GetBody()->GetSize());
	return true;
}

bool ActivityManager::doReward(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CActivityRewardProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", uid);
		return false;
	}
	ActivityUtil *act = loadActivity(proto.id);
	if (act == NULL) {
		error_log("act timeout uid=%u id=%u", uid, proto.id);
		return false;
	}
	if (!act->doReward(proto.index)) {
		error_log("reward error uid=%u id=%u", uid, proto.id);
	}

	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_ACTIVITY);
	writer.AppendByte(PROTOCOL_SUBCMD_ACTIVITY_REWARD);
	act->encodeData(sp.GetBody());
	act->getReward(sp.GetBody());
	PlayerManager::getInstance()->sendToAccess(&sp);
	debug_log("uid=%u,id=%u,index=%u", uid, proto.id, proto.index);
	return true;
}

bool ActivityManager::doAddCount(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	byte ret = 0;
	CActivityAddCountProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", uid);
		ret = 1;
	}
	ActivityUtil *act = NULL;
	if (ret == 0 && (act = loadActivity(e_ActivityTypeSevenTask)) == NULL) {
		ret = 1;
	} else {
		ActSevenTask *dact = dynamic_cast<ActSevenTask*>(act);
		if (!dact->doAddCount(proto.quest, proto.count, proto.type == 1)) {
			ret = 1;
		} else {
			dact->saveData();
		}
	}

	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_ACTIVITY);
	writer.AppendByte(PROTOCOL_SUBCMD_ACTIVITY_ADD_COUNT);
	writer.AppendByte(ret);
	PlayerManager::getInstance()->sendToAccess(&sp);

	sendData(e_ActivityTypeSevenTask);

	debug_log("uid=%u,aid=%u,id=%u,cnt=%u,t=%u", uid, proto.id, proto.quest, proto.count, static_cast<uint32_t>(proto.type));

	return true;
}

bool ActivityManager::doBuyScore(CNetPacket *packet) {
	byte ret = 0;
	ActivityUtil *act = NULL;
	if (ret == 0 && (act = loadActivity(e_ActivityTypeSevenTask)) == NULL) {
		ret = 1;
	} else {
		ActSevenTask *dact = dynamic_cast<ActSevenTask*>(act);
		if (!dact->doBuyScore()) {
			ret = ACT_RET_FAIL;
		}
	}
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_ACTIVITY);
	writer.AppendByte(PROTOCOL_SUBCMD_ACTIVITY_BUY_SCORE);
	writer.AppendByte(ret);
	PlayerManager::getInstance()->sendToAccess(&sp);

	sendData(e_ActivityTypeSevenTask);
	return true;
}

bool ActivityManager::doQuestReward(CNetPacket *packet) {
	byte ret = 0;
	uint32_t uid = packet->uid;
	CActivityQuestRewardProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", uid);
		ret = ACT_RET_FAIL;
	}
	ActivityUtil *act = NULL;
	if (ret == 0 && (act = loadActivity(e_ActivityTypeSevenTask)) == NULL) {
		ret = 1;
	} else {
		ActSevenTask *dact = dynamic_cast<ActSevenTask*>(act);
		if (!dact->doQuestReward(proto.type == 1, proto.id)) {
			ret = ACT_RET_FAIL;
		} else {
			dact->saveData();
		}
	}

	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_ACTIVITY);
	writer.AppendByte(PROTOCOL_SUBCMD_ACTIVITY_QUEST_REWARD);
	writer.AppendByte(ret);
	PlayerManager::getInstance()->sendToAccess(&sp);

	sendData(e_ActivityTypeSevenTask);

	debug_log("uid=%u,id=%u,t=%u", uid, proto.id, proto.type);
	return true;
}

bool ActivityManager::doLevelReward(CNetPacket *packet) {
	byte ret = 0;
	uint32_t uid = packet->uid;
	CActivityRewardProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", uid);
		ret = ACT_RET_FAIL;
	}
	ActivityUtil *act = NULL;
	if (ret == 0 && (act = loadActivity(e_ActivityTypeSevenTask)) == NULL) {
		ret = 1;
	} else {
		ActSevenTask *dact = dynamic_cast<ActSevenTask*>(act);
		if (!dact->doLevelReward(proto.id, proto.index)) {
			ret = ACT_RET_FAIL;
		}
	}

	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_ACTIVITY);
	writer.AppendByte(PROTOCOL_SUBCMD_ACTIVITY_LEVEL_REWARD);
	writer.AppendByte(ret);
	PlayerManager::getInstance()->sendToAccess(&sp);

	sendData(e_ActivityTypeSevenTask);
	return true;
}

bool ActivityManager::doLottery(CNetPacket *packet) {
	byte ret = 0;
	uint32_t uid = packet->uid;
	CActivityLotteryProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", uid);
		ret = ACT_RET_FAIL;
	}
	ActivityUtil *act = NULL;
	if (0 == ret && (act = loadActivity(proto.id)) == NULL) {
		error_log("get act error uid=%u id=%u", uid, proto.id);
		ret = ACT_RET_FAIL;
	}
	if (0 == ret && !act->doLottery(proto.cnt)) {
		error_log("lottery error uid=%u id=%u", uid, proto.id);
		ret = ACT_RET_FAIL;
	}
	CNetPacket sp;
	sp.uid = m_player->getUid();
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_ACTIVITY);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_ACTIVITY_LOTTERY);
	PACKET_ENCODE(Byte, ret);
	PACKET_ENCODE(UInt32, proto.id);
	if (0 == ret) {
		PACKET_ENCODE(UInt32, act->getScore());
		act->getLotteryResult(sp.GetBody());
	} else {
		PACKET_ENCODE(UInt32, 0);
		PACKET_ENCODE(UInt32, 0);
		PACKET_ENCODE(UInt32, 0);
	}
	PlayerManager::getInstance()->sendToAccess(&sp);
	debug_log("uid=%u,id=%u,ret=%d", uid, proto.id, static_cast<int>(ret));
	return true;
}

bool ActivityManager::doGetAllData(CNetPacket *packet) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	long sts = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	vector<uint32_t> ids;
	set<uint32_t> can;
	ActivityTimeManager::getInstance()->getValidId(ids);
	vector<uint32_t>::iterator itr = ids.begin();
	for (; itr != ids.end(); ++itr) {
		ActivityUtil *act = loadActivity(*itr);
		if (act == NULL || !act->canReward()) {
			continue;
		}
		can.insert(*itr);
	}
	sendAllData(m_player->getUid(), can);
	gettimeofday(&tv, NULL);
	long ets = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	debug_log("uid=%u,count=%u,ts=%ld", packet->uid, can.size(), ets - sts);
	return true;
}

bool ActivityManager::sendData(uint32_t id) {
	ActivityUtil *act = loadActivity(id);
	if (act == NULL) {
		return false;
	}
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_ACTIVITY);
	writer.AppendByte(PROTOCOL_SUBCMD_ACTIVITY_DATA);
	act->encodeData(sp.GetBody());
	writer.AppendUInt32(0);
	writer.AppendUInt32(0);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool ActivityManager::sendAllData(uint32_t uid, const set<uint32_t> &ids) {
	CNetPacket sp;
	sp.uid = uid;
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_ACTIVITY);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_ACTIVITY_ALL_DATA);
	PACKET_ENCODE(UInt32, ids.size());
	set<uint32_t>::const_iterator itr = ids.begin();
	for (; itr != ids.end(); ++itr) {
		PACKET_ENCODE(UInt32, *itr);
	}
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

ActivityUtil* ActivityManager::loadActivity(uint32_t id) {
	map<uint32_t, ActivityUtil*>::iterator itr = m_data.find(id);
	if (itr != m_data.end()) {
		return itr->second;
	}
	ActivityUtil *act = NULL;
	uint32_t uid = m_player->getUid();
	switch (id) {
	case e_ActivityTypeExpRank:
		act = new ActNewSrvExpRank(uid);
		break;
	case e_ActivityTypePowerRank:
		act = new ActNewSrvPowerRank(uid);
		break;
	case e_ActivityTypeTransportRank:
		act = new ActNewSrvTransportRank(uid);
		break;
	case e_ActivityTypeConsumeRank:
		act = new ActNewSrvConsumeRank(uid);
		break;
	case e_ActivityTypeSevenTask:
		act = new ActSevenTask(uid);
		break;
	case e_ActivityTypeDailyBuyBag:
		act = new ActDailyBuyBag(uid, e_ActivityTypeDailyBuyBag, true);
		break;
	case e_ActivityTypeDailyChargeEquip:
		act = new ActDailyChargeEquip(uid, e_ActivityTypeDailyChargeEquip, true);
		break;
	case e_ActivityTypeDailyChargeCash:
		act = new ActDailyChargeCash(uid, e_ActivityTypeDailyChargeCash, true);
		break;
	case e_ActivityTypeContinueCharge:
		act = new ActContinueCharge(uid, e_ActivityTypeContinueCharge, true);
		break;
	case e_ActivityTypeLuckyLottery:
		act = new ActLuckyLottery(uid);
		break;
	case e_ActivityTypeSoldierRank:
		act = new ActNewSrvSoldierRank(uid);
		break;
	case e_ActivityTypeGemRank:
		act = new ActNewSrvGemRank(uid);
		break;
	case e_ActivityTypeCoinsRank:
		act = new ActNewSrvCoinsRank(uid);
		break;
	case e_ActivityTypeWorldBattleRank:
		act = new ActNewSrvWorldBattleRank(uid);
		break;
	case e_ActivityTypeSevenDayTask:
		act = new ActSevenDayTask(uid);
		break;
	case e_ActivityTypeSoldierRankNew:
		act = new ActSoldierRank(uid);
		break;
	case e_ActivityTypeExpRankNew:
		act = new ActExpRank(uid);
		break;
	case e_ActivityTypePowerRankNew:
		act = new ActPowerRank(uid);
		break;
	case e_ActivityTypeBoatRankNew:
		act = new ActBoatRank(uid);
		break;
	case e_ActivityTypeConsumeRankNew:
		act = new ActConsumeRank(uid);
		break;
	case e_ActivityTypeArenaRankNew:
		act = new ActArenaRank(uid);
		break;
	case e_ActivityTypeDailyBuyBagNew:
		act = new ActDailyBuyBag(uid, e_ActivityTypeDailyBuyBagNew, false);
		break;
	case e_ActivityTypeDChargeEquipNew:
		act = new ActDailyChargeEquip(uid, e_ActivityTypeDChargeEquipNew, false);
		break;
	case e_ActivityTypeDChargeCashNew:
		act = new ActDailyChargeCash(uid, e_ActivityTypeDChargeCashNew, false);
		break;
	case e_ActivityTypeCChargeNew:
		act = new ActContinueCharge(uid, e_ActivityTypeCChargeNew, false);
		break;
	}
	if (act == NULL) {
		return NULL;
	}
	m_data.insert(make_pair(id, act));
	return act;
}
