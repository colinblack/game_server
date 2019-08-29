/*
 * RankManager.cpp
 *
 *  Created on: 2015-12-16
 *      Author: nick
 */

#include "RankManager.h"
#include <fstream>
#include "ProtocolRank.h"
#include "DataInc.h"
#include "PlayerManager.h"
#include "LoginServer.h"
#include "ProtocolRank.h"

RankManager::RankManager() {
	m_transport_reset_ts = 0;
}

RankManager::~RankManager() {
}

bool RankManager::init() {
	initRankExp();
	initRankCombat();
	initRankTransport();
	return true;
}

bool RankManager::save() {
	saveRankExp();
	saveRankCombat();
	saveRankTransport();
	return true;
}

bool RankManager::doPacket(CNetPacket *packet) {
	switch (packet->subCmd) {
	case PROTOCOL_SUBCMD_RANK_EXP:
		doQueryRankExp(packet);
		break;
	case PROTOCOL_SUBCMD_RANK_COMBAT:
		doQueryRankCombat(packet);
		break;
	case PROTOCOL_SUBCMD_RANK_TRANSPORT:
		doQueryRankTransport(packet);
		break;
	}
	return true;
}

bool RankManager::onLogin(uint32_t uid) {
	if (!IS_VALID_PLAYER_UID(uid)) {
		return false;
	}
	addRankExp(uid);
	addRankCombat(uid);
	addRankTransport(uid);
	return true;
}

bool RankManager::onOffline(uint32_t uid) {
	return true;
}

bool RankManager::addRankExp(uint32_t uid) {
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (player == NULL) {
		return false;
	}
	const DataUser &user = player->getUserInfo();
	if (user.exp == 0) {
		return false;
	}
	list<RankExp> &rank = m_rankExp[user.level];
	uint32_t old_r = delItem(rank, uid);
	RankExp item;
	item.uid = uid;
	item.exp = user.exp;
	item.name = user.name;
	item.pic = user.figure_url;
	uint32_t new_r = addItem(rank, item);
	if (new_r != old_r) {
		uint32_t f = old_r < new_r ? old_r : new_r;
		uint32_t t = old_r > new_r ? old_r : new_r;
		f = f == 0 ? MAX_RANK_SIZE : f;
		t = t == 0 ? MAX_RANK_SIZE : t;
		uint32_t r = 1;
		list<RankExp>::iterator itr = rank.begin();
		for (; itr != rank.end(); ++itr, ++r) {
			if (r >= f && r <= t) {
				noticeRank(itr->uid, e_RankDataTypeExp, r);
			}
		}
	}
	list<RankExp> &all_rank = m_rankExp[ALL_RANK_LV];
	delItem(all_rank, uid);
	if (all_rank.size() >= MAX_RANK_SIZE && all_rank.back().exp > item.exp) {
		return true;
	}
	addItem(all_rank, item);
	return true;
}

bool RankManager::addRankCombat(uint32_t uid) {
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (player == NULL) {
		return false;
	}
	const DataUser &user = player->getUserInfo();
	if (player->getUserCombat() == 0) {
		return false;
	}
	list<RankCombat> &rank = m_rankCombat[user.level];
	delItem(rank, uid);
	RankCombat item;
	item.uid = uid;
	item.combat = player->getUserCombat();
	item.name = user.name;
	item.pic = user.figure_url;
	addItem(rank, item);
	list<RankCombat> &all_rank = m_rankCombat[ALL_RANK_LV];
	delItem(all_rank, uid);
	if (all_rank.size() >= MAX_RANK_SIZE && all_rank.back().combat > item.combat) {
		return true;
	}
	addItem(all_rank, item);
	return true;
}

bool RankManager::addRankTransport(uint32_t uid) {
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (player == NULL) {
		return false;
	}
	const DataUser &user = player->getUserInfo();
	if (user.transport == 0) {
		return false;
	}
	resetTransport();
	list<RankTransport> &rank = m_rankTransport[user.level];
	delItem(rank, uid);
	RankTransport item;
	item.uid = uid;
	item.res = user.transport;
	item.name = user.name;
	item.pic = user.figure_url;
	addItem(rank, item);
	list<RankTransport> &all_rank = m_rankTransport[ALL_RANK_LV];
	delItem(all_rank, uid);
	if (all_rank.size() >= MAX_RANK_SIZE && all_rank.back().res > item.res) {
		return true;
	}
	addItem(all_rank, item);
	return true;
}

bool RankManager::onLevelChange(uint32_t uid, uint32_t old) {
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (player == NULL) {
		return false;
	}
	const DataUser &user = player->getUserInfo();
	if (old == user.level) {
		return true;
	}

	resetTransport();

	list<RankExp> &exp = m_rankExp[old];
	delItem(exp, uid);

	list<RankCombat> &combat = m_rankCombat[old];
	delItem(combat, uid);

	list<RankTransport> &transport = m_rankTransport[old];
	delItem(transport, uid);

	addRankExp(uid);
	addRankCombat(uid);
	addRankTransport(uid);

	return true;
}

bool RankManager::doQueryRankExp(CNetPacket *packet) {
	CRankQueryProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", packet->uid);
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(packet->uid);
	if (player == NULL) {
		error_log("load player error uid=%u", packet->uid);
		return false;
	}
	uint32_t lv = player->getLevel();
	if (proto.all == 1) {
		lv = ALL_RANK_LV;
	}
	sendRankExp(packet->uid, player->getExp(), lv);
	return true;
}

bool RankManager::doQueryRankCombat(CNetPacket *packet) {
	CRankQueryProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", packet->uid);
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(packet->uid);
	if (player == NULL) {
		return false;
	}
	uint32_t lv = player->getLevel();
	if (proto.all == 1) {
		lv = ALL_RANK_LV;
	}
	sendRankCombat(packet->uid, player->getUserCombat(), lv);
	return true;
}

bool RankManager::doQueryRankTransport(CNetPacket *packet) {
	CRankQueryProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", packet->uid);
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(packet->uid);
	if (player == NULL) {
		return false;
	}
	uint32_t lv = player->getLevel();
	if (proto.all == 1) {
		lv = ALL_RANK_LV;
	}
	sendRankTransport(packet->uid, player->getUserInfo().transport,lv);
	return true;
}

bool RankManager::sendRankExp(uint32_t uid, uint32_t v, uint32_t lv) {
	CNetPacket sp;
	sp.uid = uid;
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_RANK);
	writer.AppendByte(PROTOCOL_SUBCMD_RANK_EXP);
	writer.AppendUInt32(v);
	map<uint32_t, list<RankExp> >::iterator it = m_rankExp.find(lv);
	if (it == m_rankExp.end()) {
		writer.AppendUInt32(0);
	} else {
		const list<RankExp> &ranklist = it->second;
		writer.AppendUInt32(ranklist.size());
		list<RankExp>::const_iterator itr = ranklist.begin();
		uint32_t rank = 1;
		for (; itr != ranklist.end(); ++itr) {
			writer.AppendUInt32(itr->uid);
			writer.AppendUInt32(rank);
			writer.AppendUInt32(itr->exp);
			writer.AppendString(itr->name);
			writer.AppendByte(0);
			writer.AppendString(itr->pic);
			writer.AppendByte(0);
			++rank;
		}
	}
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool RankManager::sendRankCombat(uint32_t uid, uint32_t v, uint32_t lv) {
	CNetPacket sp;
	sp.uid = uid;
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_RANK);
	writer.AppendByte(PROTOCOL_SUBCMD_RANK_COMBAT);
	writer.AppendUInt32(v);
	map<uint32_t, list<RankCombat> >::iterator it = m_rankCombat.find(lv);
	if (it == m_rankCombat.end()) {
		writer.AppendUInt32(0);
	} else {
		const list<RankCombat> &ranklist = it->second;
		writer.AppendUInt32(ranklist.size());
		list<RankCombat>::const_iterator itr = ranklist.begin();
		uint32_t rank = 1;
		for (; itr != ranklist.end(); ++itr) {
			writer.AppendUInt32(itr->uid);
			writer.AppendUInt32(rank);
			writer.AppendUInt32(itr->combat);
			writer.AppendString(itr->name);
			writer.AppendByte(0);
			writer.AppendString(itr->pic);
			writer.AppendByte(0);
			++rank;
		}
	}
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool RankManager::sendRankTransport(uint32_t uid, uint32_t v, uint32_t lv) {
	resetTransport();
	CNetPacket sp;
	sp.uid = uid;
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_RANK);
	writer.AppendByte(PROTOCOL_SUBCMD_RANK_TRANSPORT);
	writer.AppendUInt32(v);
	map<uint32_t, list<RankTransport> >::iterator it = m_rankTransport.find(lv);
	if (it == m_rankTransport.end()) {
		writer.AppendUInt32(0);
	} else {
		const list<RankTransport> &ranklist = it->second;
		writer.AppendUInt32(ranklist.size());
		list<RankTransport>::const_iterator itr = ranklist.begin();
		uint32_t rank = 1;
		for (; itr != ranklist.end(); ++itr) {
			writer.AppendUInt32(itr->uid);
			writer.AppendUInt32(rank);
			writer.AppendUInt32(itr->res);
			writer.AppendString(itr->name);
			writer.AppendByte(0);
			writer.AppendString(itr->pic);
			writer.AppendByte(0);
			++rank;
		}
	}
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool RankManager::initRankExp() {
	string path;
	getDataPath(RANK_EXP_DATA_PATH, path);
	fstream input(path.c_str(), ios::in | ios::binary);
	if (!input.good()) {
		error_log("open file error path=%s", path.c_str());
		return false;
	}
	ProtoRankList::RankExp msg;
	if (!msg.ParseFromIstream(&input)) {
		error_log("parse file error path=%s", path.c_str());
		return false;
	}
	for (int i = 0; i < msg.data_size(); ++i) {
		list<RankExp> r;
		for (int j = 0; j < msg.data(i).data_size(); ++j) {
			RankExp item;
			item.Parse(msg.data(i).data(j));
			r.push_back(item);
		}
		m_rankExp.insert(make_pair(msg.data(i).lv(), r));
	}
	return true;
}

bool RankManager::initRankCombat() {
	string path;
	getDataPath(RANK_COMBAT_DATA_PATH, path);
	fstream input(path.c_str(), ios::in | ios::binary);
	if (!input.good()) {
		error_log("open file error path=%s", path.c_str());
		return false;
	}
	ProtoRankList::RankCombat msg;
	if (!msg.ParseFromIstream(&input)) {
		error_log("parse file error path=%s", path.c_str());
		return false;
	}
	for (int i = 0; i < msg.data_size(); ++i) {
		list<RankCombat> r;
		for (int j = 0; j < msg.data(i).data_size(); ++j) {
			RankCombat item;
			item.Parse(msg.data(i).data(j));
			r.push_back(item);
		}
		m_rankCombat.insert(make_pair(msg.data(i).lv(), r));
	}
	return true;
}

bool RankManager::initRankTransport() {
	string path;
	getDataPath(RANK_TRANSPORT_DATA_PATH, path);
	fstream input(path.c_str(), ios::in | ios::binary);
	if (!input.good()) {
		error_log("open file error path=%s", path.c_str());
		return false;
	}
	ProtoRankList::RankTransport msg;
	if (!msg.ParseFromIstream(&input)) {
		error_log("parse file error path=%s", path.c_str());
		return false;
	}
	for (int i = 0; i < msg.data_size(); ++i) {
		list<RankTransport> r;
		for (int j = 0; j < msg.data(i).data_size(); ++j) {
			RankTransport item;
			item.Parse(msg.data(i).data(j));
			r.push_back(item);
		}
		m_rankTransport.insert(make_pair(msg.data(i).lv(), r));
	}
	m_transport_reset_ts = msg.ts();
	return true;
}

bool RankManager::saveRankExp() {
	string path;
	getDataPath(RANK_EXP_DATA_PATH, path);
	fstream output(path.c_str(), ios::out | ios::binary);
	if (!output.good()) {
		error_log("open file error path=%s", path.c_str());
		return false;
	}
	ProtoRankList::RankExp msg;
	map<uint32_t, list<RankExp> >::iterator itr = m_rankExp.begin();
	for (; itr != m_rankExp.end(); ++itr) {
		list<RankExp>::iterator it = itr->second.begin();
		ProtoRankList::RankItemLevel *level = msg.add_data();
		level->set_lv(itr->first);
		for (; it != itr->second.end(); ++it) {
			it->Serialize(level->add_data());
		}
	}
	if (!msg.SerializeToOstream(&output)) {
		error_log("serialize file error path=%s", path.c_str());
		return false;
	}
	return true;
}

bool RankManager::saveRankCombat() {
	string path;
	getDataPath(RANK_COMBAT_DATA_PATH, path);
	fstream output(path.c_str(), ios::out | ios::binary);
	if (!output.good()) {
		error_log("open file error path=%s", path.c_str());
		return false;
	}
	ProtoRankList::RankCombat msg;
	map<uint32_t, list<RankCombat> >::iterator itr = m_rankCombat.begin();
	for (; itr != m_rankCombat.end(); ++itr) {
		list<RankCombat>::iterator it = itr->second.begin();
		ProtoRankList::RankItemLevel *level = msg.add_data();
		level->set_lv(itr->first);
		for (; it != itr->second.end(); ++it) {
			it->Serialize(level->add_data());
		}
	}
	if (!msg.SerializeToOstream(&output)) {
		error_log("serialize file error path=%s", path.c_str());
		return false;
	}
	return true;
}

bool RankManager::saveRankTransport() {
	string path;
	getDataPath(RANK_TRANSPORT_DATA_PATH, path);
	fstream output(path.c_str(), ios::out | ios::binary);
	if (!output.good()) {
		error_log("open file error path=%s", path.c_str());
		return false;
	}
	ProtoRankList::RankTransport msg;
	msg.set_ts(m_transport_reset_ts);
	map<uint32_t, list<RankTransport> >::iterator itr = m_rankTransport.begin();
	for (; itr != m_rankTransport.end(); ++itr) {
		list<RankTransport>::iterator it = itr->second.begin();
		ProtoRankList::RankItemLevel *level = msg.add_data();
		level->set_lv(itr->first);
		for (; it != itr->second.end(); ++it) {
			it->Serialize(level->add_data());
		}
	}
	if (!msg.SerializeToOstream(&output)) {
		error_log("serialize file error path=%s", path.c_str());
		return false;
	}
	return true;
}

bool RankManager::getDataPath(const string &name, string &path) {
	string serverid = Config::GetValue("server_id");
	String::Format(path, Config::GetValue(name).c_str(), serverid.c_str());
	return true;
}

bool RankManager::noticeRank(uint32_t uid, uint32_t type, uint32_t rank) {
	if (!PlayerManager::getInstance()->IsOnline(uid)) {
		return false;
	}
	CNetPacket sp;
	sp.uid = uid;
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_RANK);
	writer.AppendByte(PROTOCOL_SUBCMD_RANK_NOTICE);
	writer.AppendUInt32(type);
	writer.AppendUInt32(rank);

	PlayerManager::getInstance()->sendToAccess(&sp);

	return true;
}

bool RankManager::resetTransport() {
	if (Time::IsThisWeek(m_transport_reset_ts)) {
		return true;
	}
	m_rankTransport.clear();
	m_transport_reset_ts = Time::GetGlobalTime();
	return true;
}
