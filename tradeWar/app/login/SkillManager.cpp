/*
 * SkillManager.cpp
 *
 *  Created on: 2018年5月21日
 *      Author: Administrator
 */

#include "SkillManager.h"
#include "SkillConfig.h"
#include "Player.h"

CSkillManager::CSkillManager() {
}

CSkillManager::~CSkillManager() {
}

bool CSkillManager::doPacket(CNetPacket *packet) {
	switch (packet->subCmd) {
	case PROTOCOL_SUBCMD_SKILL_QUERY:
		doQuery(packet);
		break;
	case PROTOCOL_SUBCMD_SKILL_UP:
		doUpgrade(packet);
		break;
	case PROTOCOL_SUBCMD_SKILL_USE:
		doUse(packet);
		break;
	case PROTOCOL_SUBCMD_SKILL_STATUS:
		doStatus(packet);
		break;
	}
	return true;
}

bool CSkillManager::load(uint32_t uid) {
	int ret = 0;
	CDataSkill db;
	vector<DataSkill> datas;
	ret = db.GetSkills(uid, datas);
	if (ret != 0 && ret != R_ERR_NO_DATA) {
		error_log("GetSkills error ret=%u uid=%u", ret, uid);
		return false;
	}
	vector<DataSkill>::iterator itr = datas.begin();
	for (; itr != datas.end(); ++itr) {
		m_data.insert(make_pair(itr->skillId, *itr));
	}
	return true;
}

bool CSkillManager::setSkill(const vector<DataSkill> &datas) {
	vector<DataSkill>::const_iterator itr = datas.begin();
	for (; itr != datas.end(); ++itr) {
		m_data.insert(make_pair(itr->skillId, *itr));
	}
	return true;
}

bool CSkillManager::onTimer() {
	return true;
}

bool CSkillManager::sendSkillToBattle(uint64_t battleId) {
	return true;
}

bool CSkillManager::checkSkill(uint32_t lvl, uint32_t count) {
	return false;
}

bool CSkillManager::checkBornSkill(uint32_t lvl, uint32_t count) {
	return false;
}

uint32_t CSkillManager::getCombat(uint16_t ud) {
	return 0;
}

bool CSkillManager::addSkill(uint16_t id, uint32_t count, const string &reason) {
	uint32_t uid = m_player->getUid();

	map<uint16_t, DataSkill>::iterator itr = m_data.find(id);
	if (itr == m_data.end()) {
		DataSkill skill;
		skill.uid = uid;
		skill.skillId = id;
		skill.count = count;
		skill.level = 1;
		m_data.insert(make_pair(id, skill));
		doSave(skill, true);
		m_player->getTroopsManager()->setSkill(id, count);
	} else {
		itr->second.count += count;
		doSave(itr->second, false);
	}

	sendSkills();

	BUSI_MISC("add_skill|code=%s|%u|%u|%u|%u", reason.c_str(), uid, id, count, LogicManager::GlobalTime);
	return true;
}

bool CSkillManager::packSkill(IBuffer *buff) {
	if (buff == NULL) {
		return false;
	}
	PACKET_ENCODE_BEGIN(buff);
	PACKET_ENCODE(UInt32, m_data.size());
	map<uint16_t, DataSkill>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		const DataSkill &item = itr->second;
		PACKET_ENCODE(UInt32, item.skillId);
		PACKET_ENCODE(UInt32, item.level);
		PACKET_ENCODE(UInt32, item.count);
	}
	return true;
}

bool CSkillManager::doUpgrade(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CSkillUpProtocol protocol;
	if (!protocol.Decode(&(packet->body))) {
		error_log("CSkillUpProtocol decode error uid=%u", uid);
		return false;
	}
	map<uint16_t, DataSkill>::iterator itr = m_data.find(protocol.skillId);
	if (itr == m_data.end()) {
		error_log("skill not exists uid=%u id=%u", uid, protocol.skillId);
		return false;
	}
	Building* pBuilding = m_player->getBm()->getBuildingByType(BUILDING_ID_LABORATORY);
	if (pBuilding == NULL) {
		error_log("building not exist uid=%u type=%u", uid, BUILDING_ID_LABORATORY);
		return false;
	}
	DataSkill &skill = itr->second;
	if (pBuilding->getLevel() <= skill.level) {
		error_log("building level not enough needlv=%u skillLevel=%u", pBuilding->getLevel(), skill.level);
		return false;
	}
	ResourceCost rcost;
	if (!CSkillConfig::getInstance()->getCost(skill.skillId, skill.level, rcost.r1)) {
		error_log("get cost error uid=%u id=%u lv=%u", uid, skill.skillId, skill.level);
		return false;
	}
	string code = "upgrade_skill_" + CTrans::ITOS(skill.level + 1);
	MoneyCost mcost;
	m_player->getRm()->ResToCash(rcost, mcost.cash);
	if (mcost.cash > 0 && !m_player->getRm()->useMoney(mcost, code)) {
		error_log("use res error uid=%u id=%u lv=%u", uid, skill.skillId, skill.level);
		return false;
	}
	if (rcost.ResSum() && !m_player->getRm()->useResources(rcost, code)) {
		error_log("use res error uid=%u id=%u lv=%u", uid, skill.skillId, skill.level);
		return false;
	}
	skill.level += 1;
	doSave(skill, false);
	sendSkillUp(skill);
	BUSI_MISC("play|skillupgrade|%u|%u|%u|%u", m_player->getUid(), protocol.skillId, skill.level, Time::GetGlobalTime());
	return true;
}

bool CSkillManager::doQuery(CNetPacket *packet) {
	sendSkills();
	return true;
}

bool CSkillManager::doUse(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CSkillUseProtocol protocol;
	if (!protocol.Decode(&(packet->body))) {
		error_log("Decode error uid=%u", uid);
		return false;
	}
	map<uint16_t, DataSkill>::iterator itr = m_data.find(protocol.ud);
	if (itr == m_data.end()) {
		error_log("skill not exists uid=%u ud=%u", uid, protocol.ud);
		return false;
	}
	DataSkill &skill = itr->second;
	if (skill.count == 0) {
		error_log("cont error uid=%u ud=%u", uid, protocol.ud);
		return false;
	}
	skill.count -= 1;
	doSave(skill, false);

	CNetPacket respPacket;
	respPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&(respPacket.body));
	selfWriter.AppendByte(PROTOCOL_CMD_SKILL);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_SKILL_USE);
	skill.encode(&(respPacket.body));

	PlayerManager::getInstance()->sendToAccess(&respPacket);

	if (skill.count == 0) {
		m_player->getTroopsManager()->delAttack(skill.skillId);
	}

	debug_log("uid=%u,ud=%u", uid, protocol.ud);

	return true;
}

bool CSkillManager::doStatus(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CSkillStatusProtocol protocol;
	if (!protocol.Decode(&(packet->body))) {
		return false;
	}
	map<uint16_t, DataSkill>::iterator itr = m_data.find(protocol.ud);
	if (itr == m_data.end()) {
		error_log("skill not exists uid=%u ud=%u", uid, protocol.ud);
		return false;
	}
	DataSkill &skill = itr->second;

	skill.status = protocol.status;

	doSave(skill, false);

	CNetPacket respPacket;
	respPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&(respPacket.body));
	selfWriter.AppendByte(PROTOCOL_CMD_SKILL);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_SKILL_USE);
	skill.encode(&(respPacket.body));

	PlayerManager::getInstance()->sendToAccess(&respPacket);

	debug_log("uid=%u,ud=%u", uid, protocol.ud);

	return true;
}

bool CSkillManager::onResultResp(byte subCmd, byte ret) {
	CNetPacket respPacket;
	respPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&(respPacket.body));
	selfWriter.AppendByte(PROTOCOL_CMD_SKILL);
	selfWriter.AppendByte(subCmd);
	selfWriter.AppendByte(ret);
	return PlayerManager::getInstance()->sendToAccess(&respPacket);
}

bool CSkillManager::doSave(const DataSkill &skill, bool isNew) {
	CDataSkill dbSkill;
	isNew ? dbSkill.AddSkill(skill) : dbSkill.SetSkill(skill);
	return true;
}

bool CSkillManager::sendSkillUp(const DataSkill &skill) {
	CNetPacket sRspPacket;
	sRspPacket.uid = getPlayer()->getUid();
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_SKILL);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_SKILL_UP);
	skill.encode(&sRspPacket.body);

	PlayerManager::getInstance()->sendToAccess(&sRspPacket);

	return true;
}

bool CSkillManager::sendSkills() {
	CNetPacket sRspPacket;
	sRspPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_SKILL);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_SKILL_QUERY);
	selfWriter.AppendByte(m_data.size());
	map<uint16_t, DataSkill>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		DataSkill &skill = itr->second;
		skill.encode(&sRspPacket.body);
	}
	return PlayerManager::getInstance()->sendToAccess(&sRspPacket);
}
