/*
 * ArenaManager.cpp
 *
 *  Created on: 2019年2月27日
 *      Author: Administrator
 */

#include "ArenaManager.h"
#include "PlayerManager.h"
#include "ArenaRankManager.h"
#include "ArenaConfig.h"
#include "NpcManager.h"

#define ARENA_LOG_SIZE 5
#define ARENA_MAX_ENERGY 5

ArenaManager::ArenaManager() {
	m_new_data = false;
	m_refresh_ts = 0;
}
ArenaManager::~ArenaManager() {
}
bool ArenaManager::doPacket(CNetPacket *packet) {
	switch (packet->subCmd) {
	case PROTOCOL_SUBCMD_ARENA_QUERY:
		doQuery(packet);
		break;
	case PROTOCOL_SUBCMD_ARENA_BUY_ENERGY:
		doBuyEnergy(packet);
		break;
	case PROTOCOL_SUBCMD_ARENA_BEGIN_ATTACK:
		doBeginAttack(packet);
		break;
	case PROTOCOL_SUBCMD_ARENA_END_ATTACK:
		doEndAttack(packet);
		break;
	case PROTOCOL_SUBCMD_ARENA_RANK:
		doGetRank(packet);
		break;
	case PROTOCOL_SUBCMD_ARENA_REWARD:
		doRankReward(packet);
		break;
	case PROTOCOL_SUBCMD_ARENA_SHOP:
		doGetShop(packet);
		break;
	case PROTOCOL_SUBCMD_ARENA_SHOP_BUY:
		doShopBuy(packet);
		break;
	case PROTOCOL_SUBCMD_ARENA_LOG:
		doGetLog(packet);
		break;
	case PROTOCOL_SUBCMD_ARENA_REFRESH:
		doRefresh(packet);
		break;
	case PROTOCOL_SUBCMD_ARENA_SHOP_REFRESH:
		doShopRefresh(packet);
		break;
	}
	return true;
}
bool ArenaManager::load(uint32_t uid) {
	int ret = 0;
	CDataArena dbc;
	ret = dbc.Get(uid, m_data);
	if (R_SUCCESS != ret && R_ERR_NO_DATA != ret) {
		error_log("load error uid=%u ret=%d", uid, ret);
		return false;
	}
	if (R_ERR_NO_DATA == ret) {
		m_new_data = true;
		m_data.uid = uid;
		m_data.rank = ARENA_RANK_INVALID;
	}

	loadShop();
	loadTarget();

	if (reset()) {
		save();
	}

	CDataArenaLog dbclog;
	vector<DataArenaLog> att_log;
	dbclog.Get(uid, att_log);
	vector<DataArenaLog>::iterator itr = att_log.begin();
	for (; itr != att_log.end(); ++itr) {
		m_logs.insert(make_pair(itr->ts, *itr));
	}
	fixLogSize();
	return true;
}
bool ArenaManager::save() {
	int ret = 0;
	Json::Value shop = Json::Value(Json::arrayValue);
	vector<DataArenaShop>::iterator itr = m_shops.begin();
	for (; itr != m_shops.end(); ++itr) {
		Json::Value sitem;
		sitem["i"] = static_cast<uint32_t>(itr->id);
		sitem["c"] = itr->cnt;
		shop.append(sitem);
	}
	m_data.shop = Json::ToString(shop);
	Json::Value target = Json::Value(Json::arrayValue);
	vector<uint32_t>::iterator titr = m_targets.begin();
	for (; titr != m_targets.end(); ++titr) {
		target.append(*titr);
	}
	m_data.target = Json::ToString(target);
	CDataArena dbc;
	if (m_new_data) {
		m_new_data = false;
		ret = dbc.Add(m_data);
	} else {
		ret = dbc.Set(m_data);
	}
	if (0 != ret) {
		error_log("save error uid=%u ret=%d", m_player->getUid(), ret);
		return false;
	}
	return true;
}
bool ArenaManager::onLogin() {
	if (!reset()) {
		return false;
	}
	save();
	return true;
}
bool ArenaManager::push() {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_ARENA);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_ARENA_QUERY);
	PACKET_ENCODE(UInt16, ArenaRankManager::getInstance()->getUserRank(sp.uid));
	PACKET_ENCODE(Byte, m_data.energy);
	PACKET_ENCODE(UInt32, m_data.cd);
	packetTargets(sp.GetBody());
	PACKET_ENCODE(Byte, m_data.buy_energy);
	PACKET_ENCODE(UInt16, m_data.rank);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
bool ArenaManager::reset() {
	if (CTime::GetDayInterval(m_data.ts, Time::GetGlobalTime()) == 0) {
		return false;
	}
	m_data.ts = Time::GetGlobalTime();
	m_data.energy = ARENA_MAX_ENERGY;
	m_data.buy_energy = 0;
	m_data.cd = 0;
	m_data.shop_refresh = 0;
	refreshShop();
	return true;
}
bool ArenaManager::loadShop() {
	Json::Value v;
	Json::Reader r;
	if (!r.parse(m_data.shop, v)) {
		return false;
	}
	if (v.isNull() || !v.isArray()) {
		return false;
	}
	for (size_t i = 0; i < v.size(); ++i) {
		uint32_t id = 0;
		uint32_t count = 0;
		Json::GetUInt(v[i], "i", id);
		Json::GetUInt(v[i], "c", count);
		DataArenaShop item;
		item.id = id;
		item.cnt = count;
		m_shops.push_back(item);
	}
	return true;
}
bool ArenaManager::loadTarget() {
	Json::Value v;
	Json::Reader r;
	if (!r.parse(m_data.target, v)) {
		return false;
	}
	if (v.isNull() || !v.isArray()) {
		return false;
	}
	for (size_t i = 0; i < v.size(); ++i) {
		m_targets.push_back(v[i].asUInt());
	}
	debug_log("uid=%u,m_targetsize=%u,str=%s", m_player->getUid(), m_targets.size(), m_data.target.c_str());
	return true;
}
bool ArenaManager::doQuery(CNetPacket *packet) {
	if (m_targets.empty()) {
		ArenaRankManager::getInstance()->doRefresh(packet->uid, m_targets);
	}
	push();
	return true;
}
bool ArenaManager::doBuyEnergy(CNetPacket *packet) {
	reset();
	uint32_t uid = packet->uid;
	if (m_data.energy >= ARENA_MAX_ENERGY) {
		error_log("count error uid=%u count=%u", uid, static_cast<uint32_t>(m_data.energy));
		return onBuyEnergyResp(R_ERROR);
	}
	MoneyCost cost;
	cost.cash = ArenaConfig::getInstance()->getBuyEnergyCost(m_data.buy_energy);
	if (!m_player->getRm()->useMoney(cost, "arena_buy_count")) {
		error_log("cost error uid=%u count=%u", uid, cost.cash);
		return onBuyEnergyResp(R_ERROR);
	}
	m_data.energy += 1;
	m_data.buy_energy += 1;
	save();
	onBuyEnergyResp(R_SUCCESS);
	return true;
}
bool ArenaManager::doBeginAttack(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CArenaBeginAttackProto proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", uid);
		return onBeginAttackResp(R_ERROR, 0, 0);
	}
	reset();
	if (m_data.energy == 0) {
		error_log("attack count error uid=%u", uid);
		return onBeginAttackResp(R_ERROR, 0, 0);
	}
	if (m_data.cd > Time::GetGlobalTime()) {
		error_log("cd error uid=%u", uid);
		return onBeginAttackResp(R_ERROR, 0, 0);
	}
	uint32_t userid = 0;
	if (!ArenaRankManager::getInstance()->getUid(proto.rank, userid)) {
		error_log("target error uid=%u rank=%u", uid, proto.rank);
		return onBeginAttackResp(R_ERROR, 0, 0);
	}
	if (!onBeginAttackResp(R_SUCCESS, userid, proto.rank)) {
		error_log("resp error uid=%u rank=%u", uid, proto.rank);
		return false;
	}
	m_data.energy -= 1;
	save();
	return true;
}
bool ArenaManager::doEndAttack(CNetPacket *packet) {
	bool chg = false;
	uint32_t uid = packet->uid;
	CArenaEndAttackProto proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", uid);
		return onEndAttackResp(R_ERROR, 0, 0);
	}
	uint32_t self_old_rank = ARENA_RANK_INVALID;
	uint32_t self_now_rank = ARENA_RANK_INVALID;
	uint32_t other_now_rank = ARENA_RANK_INVALID;
	if (proto.win == 1) {
		ArenaRankManager::getInstance()->setRank(uid, proto.uid, proto.rank, self_old_rank, other_now_rank);
		self_now_rank = ArenaRankManager::getInstance()->getUserRank(uid);
		if (self_now_rank < m_data.rank) {
			chg = true;
			m_data.rank = self_now_rank;
		}
		Award reward;
		AwardInfo ritem;
		ritem.id = 605;
		ritem.type = AWARD_TYPE_ITEM;
		ritem.count = 100;
		reward.add(ritem);
		m_player->doReward(&reward, "arena_win");
		m_player->getActManager()->addArena(self_now_rank);
	} else {
		self_now_rank = ArenaRankManager::getInstance()->getUserRank(uid);
		self_old_rank = self_now_rank;
		if (m_data.cd >= Time::GetGlobalTime()) {
			m_data.cd += 600;
		} else {
			m_data.cd = Time::GetGlobalTime() + 600;
		}
		chg = true;
	}
	string soldier, tower, soldierDead, skill;
	BoatManager::setLogStr(soldier, proto.soldiers);
	BoatManager::setLogStr(tower, proto.towers);
	BoatManager::setLogStr(soldierDead, proto.soldier_dead);
	BoatManager::setLogStr(skill, proto.skill);
	addLog(uid, proto.uid, ARENA_ATT_FLAG, self_old_rank, self_now_rank, proto.win == 1, soldier, tower, soldierDead, skill);
	if (self_old_rank != self_now_rank) {
		ArenaRankManager::getInstance()->doRefresh(uid, m_targets);
		chg = true;
	}
	if (IS_VALID_PLAYER_UID(proto.uid)) {
		Player *player = PlayerManager::getInstance()->LoadForcePlayer(proto.uid);
		if (player != NULL) {
			player->getArenaManager()->onAttack(uid, proto.rank, proto.win != 1, soldier, tower, soldierDead, skill);
		}
	}
	if (chg) {
		save();
	}
	onEndAttackResp(R_SUCCESS, self_old_rank, self_now_rank);
	BUSI_MISC("play|arenaattack|%u|%u|%u|%u", m_player->getUid(), proto.rank, static_cast<uint32_t>(proto.win), Time::GetGlobalTime());
	return true;
}
bool ArenaManager::doGetRank(CNetPacket *packet) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_ARENA);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_ARENA_RANK);
	ArenaRankManager::getInstance()->packetTop(sp.GetBody());
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
bool ArenaManager::doRankReward(CNetPacket *packet) {
	return true;
}
bool ArenaManager::doGetShop(CNetPacket *packet) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_ARENA);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_ARENA_SHOP);
	if (!packShop(sp.GetBody())) {
		return false;
	}
	PACKET_ENCODE(Byte, m_data.shop_refresh);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
bool ArenaManager::doShopBuy(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CArenaShopBuyProto proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", uid);
		return onShopBuyResp(R_ERROR);
	}
	reset();
	uint32_t shop_id = proto.id;
	if (shop_id >= m_shops.size()) {
		error_log("shop id error uid=%u id=%u", uid, shop_id);
		return onShopBuyResp(R_ERROR);
	}
	DataArenaShop &shop = m_shops[shop_id];
	const ArenaCfgShop *cfg = ArenaConfig::getInstance()->getShop(shop.id);
	if (cfg == NULL) {
		error_log("cfg error uid=%u id=%u", uid, shop_id);
		return onShopBuyResp(R_ERROR);
	}
	if (shop.cnt >= cfg->count) {
		error_log("count error uid=%u id=%u count=%u", uid, shop_id, shop.cnt);
		return onShopBuyResp(R_ERROR);
	}
	string code = "boss_shop_" + CTrans::ITOS(shop_id);
	if (!m_player->getEm()->useBagItemByType(605u, cfg->require, code)) {
		error_log("cost error uid=%u id=%u count=%u", uid, shop_id, cfg->require);
		return onShopBuyResp(R_ERROR);
	}
	shop.cnt += 1;
	m_player->doReward(&(cfg->reward), code);
	save();
	return onShopBuyResp(R_SUCCESS);
	BUSI_MISC("play|arenashop|%u|%u|%u", uid, shop_id, Time::GetGlobalTime());
	return true;
}
bool ArenaManager::doGetLog(CNetPacket *packet) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_ARENA);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_ARENA_LOG);
	PACKET_ENCODE(Byte, 0);
	map<uint32_t, DataArenaLog>::reverse_iterator itr = m_logs.rbegin();
	uint32_t cnt = 0;
	Json::Reader reader;
	for (; itr != m_logs.rend(); ++itr) {
		const DataArenaLog &data = itr->second;
		PACKET_ENCODE(UInt32, data.uid);
		PACKET_ENCODE(UInt32, data.ts);
		PACKET_ENCODE(UInt32, data.userlevel);
		PACKET_ENCODE(UInt32, data.from_rank);
		PACKET_ENCODE(UInt32, data.to_rank);
		PACKET_ENCODE(String, data.username);
		PACKET_ENCODE(Byte, 0);
		PACKET_ENCODE(String, data.pic);
		PACKET_ENCODE(Byte, 0);
		PACKET_ENCODE(Byte, data.type);
		Json::Value soldier;
		if (reader.parse(data.soldier, soldier) && soldier.isArray()) {
			writer.AppendUInt32(soldier.size());
			for (size_t i = 0; i < soldier.size(); ++i) {
				writer.AppendUInt32(soldier[i]["id"].asUInt());
				writer.AppendUInt32(soldier[i]["l"].asUInt());
				writer.AppendUInt32(soldier[i]["c"].asUInt());
			}
		} else {
			writer.AppendUInt32(0);
		}

		Json::Value tower;
		if (reader.parse(data.tower, tower) && tower.isArray()) {
			writer.AppendUInt32(tower.size());
			for (size_t i = 0; i < tower.size(); ++i) {
				writer.AppendUInt32(tower[i]["id"].asUInt());
				writer.AppendUInt32(tower[i]["l"].asUInt());
				writer.AppendUInt32(tower[i]["c"].asUInt());
			}
		} else {
			writer.AppendUInt32(0);
		}

		Json::Value soldier_dead;
		if (reader.parse(data.soldier_dead, soldier_dead) && soldier_dead.isArray()) {
			writer.AppendUInt32(soldier_dead.size());
			for (size_t i = 0; i < soldier_dead.size(); ++i) {
				writer.AppendUInt32(soldier_dead[i]["id"].asUInt());
				writer.AppendUInt32(soldier_dead[i]["l"].asUInt());
				writer.AppendUInt32(soldier_dead[i]["c"].asUInt());
			}
		} else {
			writer.AppendUInt32(0);
		}

		Json::Value skill;
		if (reader.parse(data.skill, skill) && skill.isArray()) {
			writer.AppendUInt32(skill.size());
			for (size_t i = 0; i < skill.size(); ++i) {
				writer.AppendUInt32(skill[i]["id"].asUInt());
				writer.AppendUInt32(skill[i]["l"].asUInt());
				writer.AppendUInt32(skill[i]["c"].asUInt());
			}
		} else {
			writer.AppendUInt32(0);
		}
		++cnt;
	}
	uint32_t rs = sp.GetBody()->GetSize();
	sp.GetBody()->SetSize(2);
	PACKET_ENCODE(Byte, cnt);
	sp.GetBody()->SetSize(rs);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
bool ArenaManager::doRefresh(CNetPacket *packet) {
	if (m_refresh_ts + 5 < Time::GetGlobalTime()) {
		ArenaRankManager::getInstance()->doRefresh(m_player->getUid(), m_targets);
		m_refresh_ts = Time::GetGlobalTime();
	}
	CNetPacket sp;
	sp.uid = m_player->getUid();
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_ARENA);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_ARENA_REFRESH);
	PACKET_ENCODE(Byte, R_SUCCESS);
	packetTargets(sp.GetBody());
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
bool ArenaManager::doShopRefresh(CNetPacket *packet) {
	if (m_data.shop_refresh >= 2) {
		error_log("shop refresh count error uid=%u", packet->uid);
		return onShopRefreshResp(R_ERROR);
	}
	if (!m_player->getEm()->useBagItemByType(605u, ArenaConfig::getInstance()->getShopCost(), "refresh_arena_shop")) {
		error_log("cost error uid=%u", packet->uid);
		return onShopRefreshResp(R_ERROR);
	}
	refreshShop();
	m_data.shop_refresh += 1;
	save();
	onShopRefreshResp(R_SUCCESS);
	return true;
}
bool ArenaManager::onBeginAttackResp(byte ret, uint32_t uid, uint32_t r) {
	bool result = false;
	CNetPacket sp;
	sp.uid = m_player->getUid();
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_ARENA);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_ARENA_BEGIN_ATTACK);
	if (ret != R_SUCCESS) {
		if (!packetErrTarget(sp.GetBody(), ret)) {
			return false;
		}
	} else {
		if (IS_VALID_PLAYER_UID(uid)) {
			Player *player = PlayerManager::getInstance()->LoadForcePlayer(uid);
			if (player == NULL) {
				if (!packetErrTarget(sp.GetBody(), R_ERROR)) {
					return false;
				}
			} else {
				PACKET_ENCODE(Byte, R_SUCCESS);
				PACKET_ENCODE(UInt32, uid);
				PACKET_ENCODE(UInt32, r);
				PACKET_ENCODE(UInt32, player->getUserCombat());
				PACKET_ENCODE(UInt32, player->getExp());
				PACKET_ENCODE(String, player->getName());
				PACKET_ENCODE(Byte, 0);
				PACKET_ENCODE(String, player->getFig());
				PACKET_ENCODE(Byte, 0);
				player->getTroopsManager()->packDefend(sp.GetBody());
				player->getSoldierManager()->packInfo(sp.GetBody());
				player->getGemManager()->encode(sp.GetBody());
				result = true;
			}
		} else {
			const ArenaCfgNpc *cfg = ArenaConfig::getInstance()->getNpc(r);
			if (cfg == NULL) {
				packetErrTarget(sp.GetBody(), R_ERROR);
				return false;
			}
			PACKET_ENCODE(Byte, R_SUCCESS);
			PACKET_ENCODE(UInt32, cfg->id);
			PACKET_ENCODE(UInt32, r);
			PACKET_ENCODE(UInt32, cfg->power);
			PACKET_ENCODE(UInt32, cfg->exp);
			PACKET_ENCODE(String, cfg->name);
			PACKET_ENCODE(Byte, 0);
			PACKET_ENCODE(String, "");
			PACKET_ENCODE(Byte, 0);
			NpcManager::getInstance()->GetNpc(cfg->id, sp.GetBody());
			result = true;
		}
	}
	PlayerManager::getInstance()->sendToAccess(&sp);
	return result;
}
bool ArenaManager::onShopBuyResp(byte ret) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_ARENA);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_ARENA_SHOP_BUY);
	PACKET_ENCODE(Byte, ret);
	if (!packShop(sp.GetBody())) {
		return false;
	}
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
bool ArenaManager::onShopRefreshResp(byte ret) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_ARENA);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_ARENA_SHOP_REFRESH);
	PACKET_ENCODE(Byte, ret);
	if (!packShop(sp.GetBody())) {
		return false;
	}
	PACKET_ENCODE(Byte, m_data.shop_refresh);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
bool ArenaManager::onEndAttackResp(byte ret, uint16_t from, uint16_t to) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_ARENA);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_ARENA_END_ATTACK);
	PACKET_ENCODE(Byte, ret);
	PACKET_ENCODE(UInt16, from);
	PACKET_ENCODE(UInt16, to);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
bool ArenaManager::onBuyEnergyResp(byte ret) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_ARENA);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_ARENA_BUY_ENERGY);
	PACKET_ENCODE(Byte, ret);
	PACKET_ENCODE(Byte, m_data.energy);
	PACKET_ENCODE(Byte, m_data.buy_energy);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
bool ArenaManager::onCommonResp(byte sub, byte ret) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_ARENA);
	PACKET_ENCODE(Byte, sub);
	PACKET_ENCODE(Byte, ret);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
bool ArenaManager::onAttack(uint32_t uid, uint32_t r, bool win, const string &s, const string &t, const string &sd, const string &sk) {
	uint32_t my_uid = m_player->getUid();
	uint32_t rank = ArenaRankManager::getInstance()->getUserRank(my_uid);
	if (rank != r) {
		ArenaRankManager::getInstance()->doRefresh(my_uid, m_targets);
		save();
	}
	addLog(my_uid, uid, ARENA_DEF_FLAG, r, rank, win, s, t, sd, sk);
	return true;
}
bool ArenaManager::packetErrTarget(IBuffer *buff, byte ret) {
	PACKET_ENCODE_BEGIN(buff);
	PACKET_ENCODE(Byte, ret);
	PACKET_ENCODE(UInt32, 0);
	PACKET_ENCODE(UInt32, 0);
	PACKET_ENCODE(UInt32, 0);
	PACKET_ENCODE(UInt32, 0);
	PACKET_ENCODE(String, "");
	PACKET_ENCODE(Byte, 0);
	PACKET_ENCODE(String, "");
	PACKET_ENCODE(Byte, 0);
	PACKET_ENCODE(UInt32, 0);
	PACKET_ENCODE(UInt32, 0);
	PACKET_ENCODE(UInt32, 0);
	return true;
}
bool ArenaManager::packetTargets(IBuffer *buff) {
	if (buff == NULL) {
		return false;
	}
	uint32_t osize = buff->GetSize();
	PACKET_ENCODE_BEGIN(buff);
	PACKET_ENCODE(Byte, 0);
	uint32_t cnt = 0;
	vector<uint32_t>::iterator itr = m_targets.begin();
	for (; itr != m_targets.end(); ++itr) {
		uint32_t uid = 0;
		if (!ArenaRankManager::getInstance()->getUid(*itr, uid)) {
			continue;
		}
		if (!IS_VALID_PLAYER_UID(uid)) {
			const ArenaCfgNpc *npc = ArenaConfig::getInstance()->getNpc(*itr);
			if (npc == NULL) {
				continue;
			}
			PACKET_ENCODE(UInt32, npc->id);
			PACKET_ENCODE(UInt32, npc->power);
			PACKET_ENCODE(UInt32, *itr);
			PACKET_ENCODE(String, npc->name);
			PACKET_ENCODE(Byte, 0);
			PACKET_ENCODE(String, "");
			PACKET_ENCODE(Byte, 0);
		} else {
			Player *player = PlayerManager::getInstance()->LoadForcePlayer(uid);
			if (player == NULL) {
				continue;
			}
			PACKET_ENCODE(UInt32, uid);
			PACKET_ENCODE(UInt32, player->getUserCombat());
			PACKET_ENCODE(UInt32, *itr);
			PACKET_ENCODE(String, player->getName());
			PACKET_ENCODE(Byte, 0);
			PACKET_ENCODE(String, player->getFig());
			PACKET_ENCODE(Byte, 0);
		}
		++cnt;
	}
	uint32_t nsize = buff->GetSize();
	buff->SetSize(osize);
	PACKET_ENCODE(Byte, cnt);
	buff->SetSize(nsize);
	debug_log("uid=%u,cnt=%u", m_player->getUid(), cnt);
	return true;
}
bool ArenaManager::addLog(uint32_t uid, uint32_t ouid, byte ty, uint32_t fr, uint32_t to, bool win, const string &s, const string &t, const string &sd, const string &sk) {
	DataArenaLog data;
	data.uid = uid;
	data.ts = Time::GetGlobalTime();
	data.userid = ouid;
	data.from_rank = fr;
	data.to_rank = to;
	data.win = win ? 1 : 0;
	data.soldier = s;
	data.tower = t;
	data.soldier_dead = sd;
	data.skill = sk;
	data.type = ty;
	if (IS_VALID_PLAYER_UID(ouid)) {
		Player *player = PlayerManager::getInstance()->LoadForcePlayer(ouid);
		if (player != NULL) {
			data.username = player->getName();
			data.pic = player->getFig();
		}
	}
	CDataArenaLog dbc;
	m_logs.insert(make_pair(data.ts, data));
	dbc.Add(data);
	fixLogSize();
	return true;
}
bool ArenaManager::refreshShop() {
	m_shops.clear();
	vector<byte> ids;
	if (!ArenaConfig::getInstance()->refreshShop(ids)) {
		return false;
	}
	vector<byte>::iterator itr = ids.begin();
	for (; itr != ids.end(); ++itr) {
		DataArenaShop item;
		item.id = *itr;
		item.cnt = 0;
		m_shops.push_back(item);
	}
	return true;
}
bool ArenaManager::packShop(IBuffer *buff) {
	if (buff == NULL) {
		return false;
	}
	PACKET_ENCODE_BEGIN(buff);
	PACKET_ENCODE(Byte, m_shops.size());
	for (size_t i = 0; i < m_shops.size(); ++i) {
		PACKET_ENCODE(UInt32, m_shops[i].id);
		PACKET_ENCODE(UInt32, m_shops[i].cnt);
	}
	return true;
}
bool ArenaManager::fixLogSize() {
	int ret = 0;
	CDataArenaLog dbc;
	while (m_logs.size() > ARENA_LOG_SIZE) {
		map<uint32_t, DataArenaLog>::iterator itr = m_logs.begin();
		ret = dbc.Del(itr->second.uid, itr->first);
		if (0 != ret) {
			error_log("del log error uid=%u ts=%u ret=%d", itr->second.uid, itr->first, ret);
		}
		m_logs.erase(itr);
	}
	return true;
}
