/*
 * InviteManager.cpp
 *
 *  Created on: 2016-6-8
 *      Author: Administrator
 */

#include "InviteManager.h"
#include "Kernel.h"
#include "PlayerManager.h"
#include "LanguageConfig.h"
#include "InviteConfig.h"
#include "SystemEmail.h"
#include "SocialManager.h"
#include "SystemMessage.h"
#include "GiftBagConfig.h"

#define MAX_INVITE_COUNT 100

InviteManager::InviteManager() {
}

InviteManager::~InviteManager() {
}

bool InviteManager::doPacket(CNetPacket * packet) {
	switch (packet->subCmd) {
	case PROTOCOL_SUBCMD_INVITE_REQUEST:
		//doInvite(packet);
		break;
	case PROTOCOL_SUBCMD_INVITE_SUCCESS:
		doAccept(packet);
		break;
	case PROTOCOL_SUBCMD_INVITE_QUERY:
		//doInviteQuery(packet);
		break;
	case PROTOCOL_SUBCMD_INVITE_AWARD:
		doInviteAward(packet);
		break;
	case PROTOCOL_SUBCMD_SHARE_SUCCESS:
		doShare(packet);
		break;
	}
	return true;
}

bool InviteManager::load(uint32_t uid) {
	if (!loadShareData(uid)) {
		error_log("load share data fail uid:%d", uid);
	}
	return true;
}

bool InviteManager::loadShareData(uint32_t uid) {
	CDataState dbState;
	DataState dataState;
	uint32_t id = PLAYER_DATA_STATE_SHARE_COUNT;
	dataState.uid = uid;
	dataState.id = id;

	Json::Value value;
	Json::FastWriter writer;
	Json::Reader reader;

	int ret = 0;
	ret = dbState.GetState(uid, id, dataState.data);
	if (ret != 0 && ret != R_ERR_NO_DATA) {
		error_log("load %u's state failed uid=%u id=%u ret=%d", uid, id, ret);
		return false;
	} else if (ret == R_ERR_NO_DATA) {
		ShareInfo info;
		value = info.ToJson();
		dataState.data = writer.write(value);
		if ((ret = dbState.AddState(dataState)) != 0) {
			error_log("add new state failed uid=%u id=%u ret=%d", uid, id, ret);
			return false;
		}
	} else {
		if (!reader.parse(dataState.data, value)) {
			error_log("parse str to json failed");
			return false;
		}
	}
	m_share.FromJson(value);

	resetShare();

	return true;
}

bool InviteManager::saveShareData() {
	CDataState dbStat;
	DataState dataState;
	dataState.uid = m_player->getUid();
	dataState.id = PLAYER_DATA_STATE_SHARE_COUNT;
	dataState.data = Json::ToString(m_share.ToJson());
	int ret = dbStat.SetState(dataState);
	if (ret != 0) {
		error_log("SetState fail ret=%d uid=%u", ret, dataState.uid);
		return false;
	}
	return true;
}

bool InviteManager::doShare(CNetPacket * packet) {
	CShareProtocol proto;
	if (!proto.Decode(&(packet->body))) {
		error_log("decode error, uid=%u", packet->uid);
		return false;
	}
	if (proto.type == ShareRewardDaily) {
		do {
			resetShare();
			if (m_share.first != 0) {
				break;
			}
			const Award *cfg = GiftBagConfig::getInstance()->getShare();
			if (cfg == NULL) {
				break;
			}
			m_share.first = 1;
			Award reward;
			GiftBagConfig::getInstance()->openAll(cfg->get(), reward);
			m_player->doReward(&reward, "daily_share");
			saveShareData();
		} while (false);
	} else {
		doShareDaily();
	}
	sendShareInfo();
	debug_log("uid=%u,type=%u", packet->uid, proto.type);
	return true;
}

bool InviteManager::doAccept(CNetPacket * packet) {
	CInviteProtocol protocol;
	if (!protocol.Decode(&(packet->body))) {
		error_log("CInviteProtocol uid=%u", packet->uid);
		return false;
	}
	if (m_player->getUserInfo().invite_by != 0) {
		error_log("had invite by other uid=%u", m_player->getUid());
		return true;
	}
	if (!m_player->getIsNewUser()) {
		error_log("is not new user uid=%u", m_player->getUid());
		return true;
	}
	uint32_t uidBy = Convert::StringToUInt(protocol.open_id);
	if (packet->uid == uidBy) {
		error_log("can not invite self:%d", packet->uid);
		return false;
	}
	if (ServerConfig::getInstance()->IsMerged(Config::GetZoneByUID(uidBy))) {
		Player *player = PlayerManager::getInstance()->LoadForcePlayer(uidBy);
		if (player) {
			player->getSocialManager()->onAccept(m_player->getUid(), m_player->getUserInfo().figure_url);
			player->getIm()->doInviteSuccess(m_player->getUid());
			m_player->getUserInfo().invite_by = uidBy;
		}
	} else {
		//TODO other server
	}

	m_player->setInviteBy(uidBy);

	debug_log("uid=%u,uidBy=%u", packet->uid, uidBy);

	return true;
}

bool InviteManager::doInviteAward(CNetPacket * packet) {
	CInviteAwardProtocol protocol;
	if (!protocol.Decode(packet->GetBody())) {
		return false;
	}
	if (protocol.id >= m_share.inviteNum) {
		return false;
	}
	if (m_share.rewardNum.size() < m_share.inviteNum) {
		m_share.rewardNum.resize(m_share.inviteNum, 0);
	}
	if (m_share.rewardNum[protocol.id] == 1) {
		return false;
	}
	m_share.rewardNum[protocol.id] = 1;

	Award reward = CShareConfig::getInstance()->getInvite();

	string code = "invite_reward_" + CTrans::ITOS(protocol.id);
	if (!m_player->doReward(&reward, code)) {
		return false;
	}

	saveShareData();

	sendShareInfo();

	return true;
}

bool InviteManager::doInviteSuccess(uint32_t uid) {
	if (m_share.inviteNum >= MAX_INVITE_COUNT) {
		return true;
	}

	m_share.inviteNum += 1;

	if (m_share.rewardNum.size() < m_share.inviteNum) {
		m_share.rewardNum.resize(m_share.inviteNum, 0);
	}

	if (!saveShareData()) {
		return false;
	}

	sendShareInfo();

	return true;
}

bool InviteManager::onLogin() {
	m_share.inviteNum = m_player->getSocialManager()->getData().size();
	if (m_share.inviteNum >= MAX_INVITE_COUNT) {
		m_share.inviteNum = MAX_INVITE_COUNT;
	}
	if (m_share.rewardNum.size() < m_share.inviteNum) {
		m_share.rewardNum.resize(m_share.inviteNum, 0);
	}

	if (resetShare()) {
		saveShareData();
	}

	sendShareInfo();

	return true;
}

bool InviteManager::doShareDaily() {
	resetShare();
	const DailyShare *pCf = CShareConfig::getInstance()->getDaily();
	if (pCf != NULL && m_share.dailyShareTs + pCf->interval <= LogicManager::GlobalTime && m_share.dailyShareGift < pCf->max) {
		rewardDaily();
	}

	debug_log("doShareDaily uid=%u dailyShareGift=%u dailyShareTs=%u", m_player->getUid(), m_share.dailyShareGift, m_share.dailyShareTs);

	return true;
}

bool InviteManager::rewardDaily() {
	m_share.dailyShareGift += 1;
	m_share.dailyShareTs = LogicManager::GlobalTime;
	if (!saveShareData()) {
		return false;
	}
	const DailyShare *pCf = CShareConfig::getInstance()->getDaily();
	if (!m_player->doReward(&(pCf->reward), "dailyShare")) {
		return false;
	}

	//sendShareReward(ShareRewardDaily, 0, 0);

	return true;
}

bool InviteManager::resetShare() {
	if (CTime::GetDayInterval(m_share.dailyShareTs, LogicManager::GlobalTime) != 0) {
		const DailyShare *pCf = CShareConfig::getInstance()->getDaily();
		if (pCf != NULL) {
			uint32_t bts = CTime::GetDayBeginTime(LogicManager::GlobalTime);
			if (LogicManager::GlobalTime - pCf->interval > bts) {
				m_share.dailyShareTs = LogicManager::GlobalTime - pCf->interval;
			} else {
				m_share.dailyShareTs = bts;
			}
		} else {
			m_share.dailyShareTs = LogicManager::GlobalTime;
		}
		m_share.dailyShareGift = 0;
		m_share.first = 0;
		return true;
	}
	return false;
}

bool InviteManager::sendShareInfo() {
	CNetPacket sRspPacket;
	sRspPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_INVITE);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_SHARE_SUCCESS);
	selfWriter.AppendUInt32(m_share.first);
	selfWriter.AppendUInt32(m_share.dailyShareGift);
	selfWriter.AppendUInt32(m_share.dailyShareTs);
	selfWriter.AppendUInt32(m_share.inviteNum);

	const vector<DataSocial> &friends = m_player->getSocialManager()->getData();
	vector<DataSocial>::const_iterator itr = friends.begin();
	for (size_t i = 0; i < m_share.inviteNum && i < m_share.rewardNum.size() && itr != friends.end(); ++i, ++itr) {
		selfWriter.AppendByte(m_share.rewardNum[i]);
		selfWriter.AppendUInt32(itr->other_uid);
		selfWriter.AppendString(itr->pic);
		selfWriter.AppendByte(0);
	}
	selfWriter.AppendUInt32(0);
	selfWriter.AppendUInt32(0);
	selfWriter.AppendUInt32(0);
	selfWriter.AppendUInt32(0);

	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket)) {
		error_log("sendAccess_fail&uid=%u", m_player->getUid());
		return false;
	}
	debug_log("sendShareInfo uid=%u dg=%u dt=%u fsize=%u",
			m_player->getUid(), m_share.dailyShareGift, m_share.dailyShareTs, friends.size());
	return true;
}

bool InviteManager::sendShareReward(uint32_t type, uint32_t r1, uint32_t r2) {
	CNetPacket sRspPacket;
	sRspPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_INVITE);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_SHARE_REWARD);
	selfWriter.AppendUInt32(type);
	selfWriter.AppendUInt32(r1);
	selfWriter.AppendUInt32(r2);

	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket)) {
		error_log("sendAccess_fail&uid=%u", m_player->getUid());
		return false;
	}
	return true;
}

bool InviteManager::onGateOver(uint64_t battleId, int32_t level, int32_t r1, int32_t r2) {
	return true;
}
