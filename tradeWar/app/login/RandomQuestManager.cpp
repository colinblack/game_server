/*
 * RandomQuestManager.cpp
 *
 *  Created on: 2018年11月30日
 *      Author: Administrator
 */

#include "RandomQuestManager.h"
#include "PlayerManager.h"
#include "RandomQuestConfig.h"

#define MAX_RANDOM_QUEST_ID 4
#define MAX_RANDOM_QUEST_COUNT 5
#define RANDOM_QUEST_RECOVER_INTERVAL 1500

RandomQuestManager::RandomQuestManager() {
	m_data.clear();
}

RandomQuestManager::~RandomQuestManager() {
}

bool RandomQuestManager::doPacket(CNetPacket *packet) {
	switch (packet->subCmd) {
	case PROTOCOL_SUBCMD_RANDOM_QUEST_INFO:
		doQuery(packet);
		break;
	case PROTOCOL_SUBCMD_RANDOM_QUEST_QUEST:
		doQuest(packet);
		break;
	case PROTOCOL_SUBCMD_RANDOM_QUEST_REWARD:
		doReward(packet);
		break;
	}
	return true;
}

bool RandomQuestManager::load(uint32_t uid) {
	int ret = 0;
	CDataRandomQuest dbc;
	vector<DataRandomQuest> datas;
	ret = dbc.Get(uid, datas);
	vector<DataRandomQuest>::iterator itr;
	for (byte id = 1; id <= MAX_RANDOM_QUEST_ID; ++id) {
		itr = find(datas.begin(), datas.end(), id);
		if (itr == datas.end()) {
			DataRandomQuest item;
			item.id = id;
			item.uid = uid;
			m_data.push_back(item);
			saveInfo(item, true);
		} else {
			m_data.push_back(*itr);
		}
	}
	return true;
}

bool RandomQuestManager::onLogin() {
	vector<DataRandomQuest>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		recover(*itr);
		randomInfo(*itr);
	}
	sendInfo();
	sync();
	return true;
}

bool RandomQuestManager::onTimer() {
	bool is_sync = false;
	vector<DataRandomQuest>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		if (recover(*itr)) {
			is_sync = true;
		}
		if (randomInfo(*itr)) {
			is_sync = true;
		}
	}

	if (is_sync) {
		sendInfo();
		sync();
	}
	return true;
}

bool RandomQuestManager::doQuery(CNetPacket *packet) {
	sendInfo();
	return true;
}

bool RandomQuestManager::doQuest(CNetPacket *packet) {
	bool ret = false;
	uint32_t uid = packet->uid;
	CRandomQuestProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", uid);
		return onQuest(RandomQuestRetFail);
	}
	vector<DataRandomQuest>::iterator itr = find(m_data.begin(), m_data.end(), static_cast<byte>(proto.id));
	if (itr == m_data.end()) {
		error_log("id error uid=%u id=%u", uid, proto.id);
		return onQuest(RandomQuestRetFail);
	}
	DataRandomQuest &quest = *itr;
	if (quest.count == 0) {
		error_log("count error uid=%u id=%u", uid, proto.id);
		return onQuest(RandomQuestRetFail);
	}
	int type = quest.quest % 10;
	if (type == RandomQuestConfig::e_RandomQuestTypeReward) {
		ret = doQuestReward(quest, proto.op);
	} else {
		ret = doQuestSoldier(quest, proto.soldier);
	}
	if (!ret) {
		error_log("quest error uid=%u id=%u", uid, proto.id);
		return onQuest(RandomQuestRetFail);
	}
	quest.quest = 0;
	quest.count -= 1;
	if (quest.ts < LogicManager::GlobalTime) {
		quest.ts = LogicManager::GlobalTime + RANDOM_QUEST_RECOVER_INTERVAL;
	}
	quest.sync = true;
	recover(quest);
	randomInfo(quest);
	onQuest(RandomQuestRetSuccess);
	sendInfo();
	sync();
	m_player->getActManager()->addTaskCount(ActSevenTask::ActSevenTaskZhengWu, 1);
	m_player->getTaskManager()->onRandomQuest();
	m_player->getActivenessManager()->onZhengWu();
	m_player->getActManager()->addZhengWu(1);
	BUSI_MISC("play|zhengwu|%u|%u|%u|%u", m_player->getUid(), proto.id, m_player->getLevel(), Time::GetGlobalTime());
	return true;
}

bool RandomQuestManager::doReward(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	const RandomQuestBoxLevel *cfg = RandomQuestConfig::getInstance()->getBoxLevel(m_player->getLevel());
	if (cfg == NULL) {
		error_log("get config error uid=%u lv=%u", uid, m_player->getLevel());
		return onReward(RandomQuestRetFail);
	}
	Award reward;
	if (cfg->rs1 > 0) {
		AwardInfo item;
		item.type = AWARD_TYPE_R1;
		item.count = cfg->rs1;
		reward.add(item);
	}
	if (cfg->rs2 > 0) {
		AwardInfo item;
		item.type = AWARD_TYPE_R2;
		item.count = cfg->rs2;
		reward.add(item);
	}
	if (!cfg->skill.empty()) {
		for (int i = 0; i < cfg->count; ++i) {
			AwardInfo item;
			item.type = AWARD_TYPE_SKILL;
			item.id = *(cfg->skill.begin() + Math::GetRandomInt(cfg->skill.size()));
			item.count = 1;
			reward.add(item);
		}
	}
	const Award *box = RandomQuestConfig::getInstance()->getBoxRandom();
	if (box != NULL) {
		vector<AwardInfo>::const_iterator itr = box->get().begin();
		for (; itr != box->get().end(); ++itr) {
			reward.add(*itr);
		}
	}

	string code = "loyal_reward_" + CTrans::ITOS(m_player->getLevel());
	ResourceCost cost;
	cost.p1 = cfg->cost;
	if (!m_player->getRm()->useResources(cost, code)) {
		error_log("use res error uid=%u lv=%u cost=%u", uid, m_player->getLevel(), cost.p1);
		return onReward(RandomQuestRetFail);
	}
	if (!m_player->doReward(&reward, code)) {
		error_log("reward error uid=%u lv=%u", uid, m_player->getLevel());
		return onReward(RandomQuestRetFail);
	}

	onReward(RandomQuestRetSuccess);

	sendInfo();

	debug_log("uid=%u", uid);

	return true;
}

bool RandomQuestManager::onQuest(byte ret) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_RANDOM_QUEST);
	writer.AppendByte(PROTOCOL_SUBCMD_RANDOM_QUEST_QUEST);
	writer.AppendByte(ret);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return ret == RandomQuestRetSuccess;
}

bool RandomQuestManager::onReward(byte ret) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_RANDOM_QUEST);
	writer.AppendByte(PROTOCOL_SUBCMD_RANDOM_QUEST_REWARD);
	writer.AppendByte(ret);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return ret == RandomQuestRetSuccess;
}

bool RandomQuestManager::sendInfo() {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_RANDOM_QUEST);
	writer.AppendByte(PROTOCOL_SUBCMD_RANDOM_QUEST_INFO);
	writer.AppendByte(0);
	writer.AppendUInt32(m_player->getRm()->getResources()->p1);
	writer.AppendUInt32(m_data.size());
	vector<DataRandomQuest>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		writer.AppendUInt32(itr->id);
		writer.AppendUInt32(itr->quest);
		writer.AppendUInt32(itr->quest % 10);
		writer.AppendUInt32(itr->reward1);
		writer.AppendUInt32(itr->reward2);
		writer.AppendUInt32(itr->soldier);
		writer.AppendUInt32(itr->count);
		writer.AppendUInt32(itr->ts);
	}
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool RandomQuestManager::saveInfo(const DataRandomQuest &data, bool isNew) {
	int ret = 0;
	CDataRandomQuest dbc;
	if (isNew) {
		ret = dbc.Add(data);
	} else {
		ret = dbc.Set(data);
	}
	if (ret != 0) {
		error_log("save error uid=%u id=%u", data.uid, static_cast<uint32_t>(data.id));
		return false;
	}
	return true;
}

bool RandomQuestManager::recover(DataRandomQuest &data) {
	if (data.count >= MAX_RANDOM_QUEST_COUNT || data.ts > LogicManager::GlobalTime) {
		return false;
	}
	uint32_t cnt = (LogicManager::GlobalTime - data.ts) / RANDOM_QUEST_RECOVER_INTERVAL + 1;
	data.count += cnt;
	if (data.count >= MAX_RANDOM_QUEST_COUNT) {
		data.ts = LogicManager::GlobalTime;
		data.count = MAX_RANDOM_QUEST_COUNT;
	} else {
		data.ts = data.ts + cnt * RANDOM_QUEST_RECOVER_INTERVAL;
	}
	data.sync = true;
	return true;
}

bool RandomQuestManager::randomInfo(DataRandomQuest &data) {
	if (data.quest != 0 || data.count == 0) {
		return false;
	}
	const RandomQuest *cfg = RandomQuestConfig::getInstance()->getQuestByLv(m_player->getLevel());
	if (cfg == NULL) {
		error_log("get cfg error uid=%u lv=%u id=%u", m_player->getUid(), m_player->getLevel(), data.id);
		return false;
	}
	int type = cfg->id % 10;
	if (type == RandomQuestConfig::e_RandomQuestTypeSoldier) {
		data.reward1 = 0;
		data.reward2 = 0;
		if (!RandomQuestConfig::getInstance()->randomSoldier(cfg->id, data.soldier)) {
			error_log("random soldier error uid=%u lv=%u id=%u", m_player->getUid(), m_player->getLevel(), data.id);
			return false;
		}
	} else {
		data.soldier = 0;
		if (!RandomQuestConfig::getInstance()->randomReward(cfg->id, data.reward1, data.reward2)) {
			error_log("random reward error uid=%u lv=%u id=%u", m_player->getUid(), m_player->getLevel(), data.id);
			return false;
		}
	}
	data.quest = cfg->id;
	data.sync = true;
	return true;
}

bool RandomQuestManager::sync() {
	vector<DataRandomQuest>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		if (!itr->sync) {
			continue;
		}
		saveInfo(*itr, false);
		itr->sync = false;
	}
	return true;
}

bool RandomQuestManager::doQuestReward(const DataRandomQuest &data, uint32_t id) {
	const RandomQuestReward *cfg = RandomQuestConfig::getInstance()->getReward(id);
	if (cfg == NULL) {
		error_log("get reward error uid=%u id=%u rid=%u", data.uid, data.quest, id);
		return false;
	}
	string code = "random_quest_" + CTrans::ITOS(data.quest) + "_" + CTrans::ITOS(id);
	if (cfg->cost > 0) {
		MoneyCost cost;
		cost.cash = cfg->cost;
		if (!m_player->getRm()->useMoney(cost, code)) {
			error_log("use money error uid=%u id=%u rid=%u", data.uid, data.quest, id);
			return false;
		}
	}
	if (!m_player->doReward(&(cfg->reward), code)) {
		error_log("reward error uid=%u id=%u rid=%u", data.uid, data.quest, id);
		return false;
	}
	return true;
}

bool RandomQuestManager::doQuestSoldier(const DataRandomQuest &data, const vector<pair<uint32_t, uint32_t> > &soldier) {
	float rate = 1.0f;
	const RandomQuestSoldier *scfg = RandomQuestConfig::getInstance()->getSoldier(data.soldier);
	if (scfg == NULL) {
		error_log("get soldier error uid=%u id=%u sid=%u", data.uid, data.quest, data.soldier);
		return false;
	}

	set<uint32_t> soldier_id;
	vector<pair<uint32_t, uint32_t> >::const_iterator sitr = soldier.begin();
	for (; sitr != soldier.end(); ++sitr) {
		soldier_id.insert(sitr->first);
	}

	if (!calcSoldier(scfg->soldier, soldier_id, rate)) {
		error_log("get soldier rate error uid=%u id=%u sid=%u", data.uid, data.quest, data.soldier);
		rate = 0;
	}
	if (rate > 1.0f) {
		rate = 1.0f;
	}

	const RandomQuest *cfg = RandomQuestConfig::getInstance()->getQuestById(data.quest);
	if (cfg == NULL) {
		error_log("get quest error uid=%u id=%u sid=%u", data.uid, data.quest, data.soldier);
		return false;
	}
	Award reward;
	vector<AwardInfo>::const_iterator itr;
	for (itr = cfg->reward1.get().begin(); itr != cfg->reward1.get().end(); ++itr) {
		AwardInfo item = *itr;
		item.count = static_cast<float>(item.count) * (1.0f + rate);
		reward.add(item);
	}
	if (rate >= 1.0) {
		for (itr = cfg->reward2.get().begin(); itr != cfg->reward2.get().end(); ++itr) {
			reward.add(*itr);
		}
	}
	char code[512] = { 0 };
	snprintf(code, 511, "random_quest_%u_%0.2f_%u", data.quest, rate, data.soldier);
	if (!m_player->doReward(&reward, code)) {
		error_log("reward error uid=%u id=%u sid=%u", data.uid, data.quest, data.soldier);
		return false;
	}
	return true;
}

bool RandomQuestManager::calcSoldier(const vector<uint32_t> &cfg, const set<uint32_t> &soldier, float &rate) {
	if (cfg.empty()) {
		error_log("cfg soldier empty");
		return false;
	}
	uint32_t match = 0;
	uint32_t star = 0;
	uint32_t level = 0;
	uint32_t chs[5] = { 0, 0, 0, 0, 0 };
	set<uint32_t>::const_iterator itr = soldier.begin();
	for (; itr != soldier.end(); ++itr) {
		Soldier *pSoldier = m_player->getSoldierManager()->getSoldierByType(*itr);
		if (pSoldier == NULL) {
			continue;
		}

		star += pSoldier->getStar();
		level += pSoldier->getLevel();
		uint32_t ch = pSoldier->getQuality();
		if (ch > 0 && ch < 5) {
			chs[ch] += 1;
		}
		vector<uint32_t>::const_iterator it = find(cfg.begin(), cfg.end(), *itr);
		if (it != cfg.end()) {
			match += 1;
		}
	}
	uint32_t quality = chs[1] + chs[2] * 2 + chs[3] * 4 + chs[4] * 8;
	float p = cfg.size();
	float a = static_cast<float>(match * 65) / p;
	float b = static_cast<float>(star * 5) / p;
	float c = static_cast<float>(level) / (4.0f * p);
	float d = static_cast<float>(quality * 5) / (4.0f * p);

	rate = (10.0f + a + b + c + d) / 100.0f;

	debug_log("%u,%u,%u,%u,%u,%0.2f", m_player->getUid(), match, star, level, quality, p);

	return true;
}
