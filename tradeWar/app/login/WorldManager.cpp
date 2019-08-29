/*
 * WorldManager.cpp
 *
 *  Created on: 2018年12月24日
 *      Author: Administrator
 */

#include "WorldManager.h"
#include "PlayerManager.h"
#include "ConfigInc.h"
#include "NpcManager.h"
#include <fstream>

WorldManager::WorldManager() {
}

WorldManager::~WorldManager() {
}

bool WorldManager::init() {
	load();
	const map<uint16_t, WorldConfigCity> &cfg = WorldConfig::getInstance()->getCity();
	map<uint16_t, WorldConfigCity>::const_iterator itr = cfg.begin();
	for (; itr != cfg.end(); ++itr) {
		DataWorldCity &city = m_world[itr->first];
		city.id = itr->first;
		if (city.users.size() > itr->second.produce.size()) {
			city.users.resize(itr->second.produce.size());
		} else if (city.users.size() < itr->second.produce.size()) {
			for (size_t i = 0; i < itr->second.produce.size() - city.users.size(); ++i) {
				DataWorldCityUser npc;
				npc.uid = itr->second.npcid;
				city.users.push_back(npc);
			}
		}
	}
	return true;
}
bool WorldManager::load() {
	string path = Config::GetValue(WORLD_BATTLE_PATH);
	fstream input(path.c_str(), ios::in | ios::binary);
	if (!input.good()) {
		error_log("open file error path=%s", path.c_str());
		return false;
	}
	WorldBattle::WorldBattle msg;
	if (!msg.ParseFromIstream(&input)) {
		error_log("parse file error path=%s", path.c_str());
		return false;
	}
	for (int i = 0; i < msg.citys_size(); ++i) {
		DataWorldCity city;
		city.Parse(msg.citys(i));
		m_world.insert(make_pair(city.id, city));
		for (size_t j = 0; j < city.users.size(); ++j) {
			if (IS_VALID_PLAYER_UID(city.users[j].uid)) {
				set<uint32_t> &occ = m_occupy[city.users[j].uid];
				occ.insert(MAKE_POINT(city.id, j));
			}
		}
	}
	for (int i = 0; i < msg.ranks_size(); ++i) {
		DataWorldRankItem item;
		item.Parse(msg.ranks(i));
		m_rank.push_back(item);
		if (m_rank.size() >= WORLD_RANK_NUM) {
			break;
		}
	}

	for (int i = 0; i < msg.pro_city_size(); ++i) {
		uint32_t p_uid = msg.pro_city(i).uid();
		uint32_t p_ts = msg.pro_city(i).ts();
		if (IS_VALID_PLAYER_UID(p_uid)) {
			m_protect.insert(make_pair(p_uid, p_ts));
			debug_log("uid=%u,ts=%u", p_uid, p_ts);
			set<uint32_t> &occ = m_occupy[p_uid];
			if (occ.size()) {
				error_log("why uid=%u", p_uid);
				occ.clear();
			}
			occ.insert(MAKE_POINT(WORLD_PROTECT_CID, 0));
		}
	}
	return true;
}
bool WorldManager::save() {
	string path = Config::GetValue(WORLD_BATTLE_PATH);
	fstream output(path.c_str(), ios::out | ios::binary);
	if (!output.good()) {
		error_log("open file error path=%s", path.c_str());
		return false;
	}

	WorldBattle::WorldBattle msg;
	map<uint16_t, DataWorldCity>::iterator itr = m_world.begin();
	for (; itr != m_world.end(); ++itr) {
		itr->second.Serialize(msg.add_citys());
	}

	list<DataWorldRankItem>::iterator it = m_rank.begin();
	for (; it != m_rank.end(); ++it) {
		it->Serialize(msg.add_ranks());
	}
	map<uint32_t, uint32_t>::iterator pit = m_protect.begin();
	for (; pit != m_protect.end(); ++pit) {
		WorldBattle::WorldBattleProtect *pp = msg.add_pro_city();
		pp->set_uid(pit->first);
		pp->set_ts(pit->second);
	}

	if (!msg.SerializeToOstream(&output)) {
		error_log("serialize file error path=%s", path.c_str());
		return false;
	}
	return true;
}

bool WorldManager::doPacket(CNetPacket *p) {
	switch (p->subCmd) {
	case PROTOCOL_SUBCMD_WORLD_ALL_INFO:
		doGetWorld(p);
		break;
	case PROTOCOL_SUBCMD_WORLD_CITY_INFO:
		doGetCity(p);
		break;
	case PROTOCOL_SUBCMD_WORLD_SELF_INFO:
		doGetSelf(p);
		break;
	case PROTOCOL_SUBCMD_WORLD_SOLDIER:
		doSoldier(p);
		break;
	case PROTOCOL_SUBCMD_WORLD_ATTACK:
		doAttack(p);
		break;
	case PROTOCOL_SUBCMD_WORLD_FINISH:
		doFinish(p);
		break;
	case PROTOCOL_SUBCMD_WORLD_SHOP_INFO:
		doShopInfo(p);
		break;
	case PROTOCOL_SUBCMD_WORLD_SHOP_BUY:
		doShopBuy(p);
		break;
	case PROTOCOL_SUBCMD_WORLD_RANK_INFO:
		doRankInfo(p);
		break;
	case PROTOCOL_SUBCMD_WORLD_HARVEST:
		doHarvest(p);
		break;
	}
	return true;
}

bool WorldManager::doGetWorld(CNetPacket *p) {
	sendWorld(p->uid);
	sendUser(p->uid);
	return true;
}

bool WorldManager::doGetCity(CNetPacket *p) {
	WorldCityInfoProto proto;
	if (!proto.Decode(p->GetBody())) {
		error_log("decode error uid=%u", p->uid);
		return false;
	}
	sendCity(p->uid, proto.id);
	return true;
}

bool WorldManager::doGetSelf(CNetPacket *p) {
	sendUser(p->uid);
	return true;
}

bool WorldManager::doSoldier(CNetPacket *p) {
	WorldSoldierProto proto;
	if (!proto.Decode(p->GetBody())) {
		error_log("decode error uid=%u", p->uid);
		return onSoldier(p->uid, R_ERROR);
	}
	DataWorldCityUser *user = WorldManager::getUser(proto.cid, proto.pid);
	if (user == NULL || user->uid != p->uid) {
		error_log("user error uid=%u cid=%u pid=%u", p->uid, proto.cid, proto.pid);
		return onSoldier(p->uid, R_ERROR);
	}
	vector<pair<uint32_t, uint32_t> >::iterator itr = proto.sold.begin();
	for (; itr != proto.sold.end(); ++itr) {
		DataWorldCitySoldier item;
		item.id = itr->first;
		item.value = itr->second;
		user->soldiers.push_back(item);
	}
	onSoldier(p->uid, R_SUCCESS);
	return true;
}

bool WorldManager::doAttack(CNetPacket *p) {
	WorldAttackProto proto;
	if (!proto.Decode(p->GetBody())) {
		error_log("decode error uid=%u", p->uid);
		return onAttackErr(p->uid, 0, 0, 0);
	}
	const DataWorldCityUser *user = WorldManager::getUser(proto.cid, proto.pid);
	if (user == NULL || user->uid == p->uid) {
		error_log("user error uid=%u cid=%u pid=%u", p->uid, proto.cid, proto.pid);
		return onAttackErr(p->uid, proto.cid, proto.pid, 0);
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(p->uid);
	if (player == NULL) {
		error_log("load player error uid=%u cid=%u pid=%u", p->uid, proto.cid, proto.pid);
		return onAttackErr(p->uid, proto.cid, proto.pid, 0);
	}
	if (!player->getWorldShopManager()->useAttackCount()) {
		error_log("cost error uid=%u cid=%u pid=%u", p->uid, proto.cid, proto.pid);
		return onAttackErr(p->uid, proto.cid, proto.pid, 0);
	}

	CNetPacket sp;
	sp.uid = p->uid;
	CBufferWriter writer(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_WORLD);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_WORLD_ATTACK);
	PACKET_ENCODE(Byte, R_SUCCESS);
	PACKET_ENCODE(UInt32, proto.cid);
	PACKET_ENCODE(UInt32, proto.pid);
	PACKET_ENCODE(UInt32, user->uid);
	if (!IS_VALID_PLAYER_UID(user->uid)) {
		uint32_t npcid = WorldConfig::getInstance()->getNpcId(proto.cid);
		const WorldConfigCity *cfg = WorldConfig::getInstance()->getItem(proto.cid);
		if (cfg != NULL) {
			PACKET_ENCODE(UInt32, cfg->power);
			PACKET_ENCODE(UInt32, cfg->exp);
			PACKET_ENCODE(String, cfg->npcname);
			PACKET_ENCODE(Byte, 0);
			PACKET_ENCODE(String, "");
			PACKET_ENCODE(Byte, 0);
		} else {
			PACKET_ENCODE(UInt32, 0);
			PACKET_ENCODE(UInt32, 0);
			PACKET_ENCODE(String, "");
			PACKET_ENCODE(Byte, 0);
			PACKET_ENCODE(String, "");
			PACKET_ENCODE(Byte, 0);
		}
		if (!NpcManager::getInstance()->GetNpc(npcid, sp.GetBody())) {
			error_log("load npc error uid=%u npcid=%u", user->uid, npcid);
			return onAttackErr(p->uid, proto.cid, proto.pid, 0);
		}
	} else {
		Player *player = PlayerManager::getInstance()->LoadForcePlayer(user->uid);
		if (player == NULL) {
			error_log("load player error uid=%u", user->uid);
			return onAttackErr(p->uid, proto.cid, proto.pid, 0);
		}
		PACKET_ENCODE(UInt32, player->getUserCombat());
		PACKET_ENCODE(UInt32, player->getExp());
		PACKET_ENCODE(String, player->getName());
		PACKET_ENCODE(Byte, 0);
		PACKET_ENCODE(String, player->getFig());
		PACKET_ENCODE(Byte, 0);
		player->getTroopsManager()->packDefend(sp.GetBody());
		player->getSoldierManager()->packInfo(sp.GetBody());
		player->getGemManager()->encode(sp.GetBody());
	}
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool WorldManager::doFinish(CNetPacket *p) {
	WorldFinishProto proto;
	if (!proto.Decode(p->GetBody())) {
		error_log("decode error uid=%u", p->uid);
		return onFinish(p->uid, 0, 0, R_ERROR);
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(p->uid);
	DataWorldCityUser *user = WorldManager::getUser(proto.cid, proto.pid);
	if (user == NULL) {
		error_log("user error uid=%u cid=%u pid=%u userid=%u", p->uid, proto.cid, proto.pid, proto.userid);
		return onFinish(p->uid, proto.cid, proto.pid, R_ERROR);
	}
	if (user->uid != proto.userid) {
		error_log("userid change uid=%u cid=%u pid=%u userid=%u", p->uid, proto.cid, proto.pid, proto.userid);
		if (player != NULL) {
			player->getWorldShopManager()->addAttackCount();
		}
		return onFinish(p->uid, proto.cid, proto.pid, R_ERROR);
	}
	if (proto.win == 0) {
		debug_log("lost uid=%u cid=%u pid=%u userid=%u", p->uid, proto.cid, proto.pid, proto.userid);
		return onFinish(p->uid, proto.cid, proto.pid, R_ERROR);
	}
	if (proto.cid == WORLD_PROTECT_CID) {
		occupyProtect(p->uid);
		return true;
	}

	uint32_t old_uid = user->uid;
	uint32_t old_ts = user->ts;

	user->uid = p->uid;
	user->ts = Time::GetGlobalTime();
	user->soldiers.clear();

	if (player != NULL) {
		user->name = player->getName();
		user->fig = player->getFig();
	}
	onUserOccupy(p->uid, proto.cid, proto.pid);
	onFinish(p->uid, proto.cid, proto.pid, R_SUCCESS);
	sendUser(p->uid);
	uint32_t rank = WorldConfig::getInstance()->getRank(proto.cid, proto.pid);
	addRank(p->uid, rank, proto.cid);
	onUserLost(old_uid, old_ts, proto.cid, proto.pid);

	debug_log("win uid=%u cid=%u pid=%u userid=%u", p->uid, proto.cid, proto.pid, proto.userid);
	return true;
}

bool WorldManager::doShopInfo(CNetPacket *p) {
	sendShopInfo(p->uid);
	return true;
}

bool WorldManager::doShopBuy(CNetPacket *p) {
	WorldBuyShopProto proto;
	if (!proto.Decode(p->GetBody())) {
		error_log("decode error uid=%u", p->uid);
		return onShopBuy(p->uid, R_ERROR);
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(p->uid);
	if (player == NULL) {
		error_log("load player error uid=%u", p->uid);
		return onShopBuy(p->uid, R_ERROR);
	}
	if (!player->getWorldShopManager()->buy(proto.id)) {
		error_log("buy error uid=%u id=%u", p->uid, proto.id);
		return onShopBuy(p->uid, R_ERROR);
	}
	onShopBuy(p->uid, R_SUCCESS);
	sendShopInfo(p->uid);
	sendUser(p->uid);
	return true;
}

bool WorldManager::doHarvest(CNetPacket *p) {
	if (!m_occupy.count(p->uid)) {
		error_log("user not occupy uid=%u", p->uid);
		return onHarvest(p->uid, R_ERROR);
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(p->uid);
	if (player == NULL) {
		error_log("load player error uid=%u", p->uid);
		return onHarvest(p->uid, R_ERROR);
	}
	uint32_t res = 0;
	set<uint32_t> &occ = m_occupy[p->uid];
	set<uint32_t>::iterator itr = occ.begin();
	for (; itr != occ.end(); ++itr) {
		uint32_t cid = (*itr >> 16) & 0x0000FFFF;
		uint32_t pid = (*itr) & 0x0000FFFF;
		DataWorldCityUser *user = getUser(cid, pid);
		if (user == NULL) {
			continue;
		}
		res += WorldConfig::getInstance()->getProduce(cid, pid, Time::GetGlobalTime() - user->ts);
		user->ts = Time::GetGlobalTime();
	}
	ResourceCost cost;
	cost.p3 = res;
	if (!player->getRm()->addResources(cost, "world_harvest")) {
		error_log("load player error uid=%u", p->uid);
		return onHarvest(p->uid, R_ERROR);
	}
	onHarvest(p->uid, R_SUCCESS);
	sendUser(p->uid);
	return true;
}

bool WorldManager::doRankInfo(CNetPacket *p) {
	CNetPacket sp;
	sp.uid = p->uid;
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_WORLD);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_WORLD_RANK_INFO);
	PACKET_ENCODE(UInt32, m_rank.size());
	uint32_t rank = 1;
	list<DataWorldRankItem>::iterator itr = m_rank.begin();
	for (; itr != m_rank.end(); ++itr) {
		PACKET_ENCODE(UInt32, itr->uid);
		PACKET_ENCODE(UInt32, rank);
		PACKET_ENCODE(UInt32, itr->cid);
		PACKET_ENCODE(String, itr->name);
		PACKET_ENCODE(Byte, 0);
		++rank;
	}
	PlayerManager::getInstance()->sendToAccess(&sp);
	debug_log("uid=%u", p->uid);
	return true;
}

bool WorldManager::packetRank(IBuffer *buff) {
	if (buff == NULL) {
		return false;
	}
	PACKET_ENCODE_BEGIN(buff);
	PACKET_ENCODE(UInt32, m_rank.size());
	uint32_t rank = 1;
	list<DataWorldRankItem>::iterator itr = m_rank.begin();
	for (; itr != m_rank.end(); ++itr) {
		PACKET_ENCODE(UInt32, itr->uid);
		PACKET_ENCODE(UInt32, rank);
		PACKET_ENCODE(String, itr->name);
		PACKET_ENCODE(Byte, 0);
		PACKET_ENCODE(String, itr->fig);
		PACKET_ENCODE(Byte, 0);
		++rank;
	}
	return true;
}

const list<DataWorldRankItem>& WorldManager::getRandData() const {
	return m_rank;
}

bool WorldManager::sendWorld(uint32_t uid) {
	CNetPacket sp;
	sp.uid = uid;
	CBufferWriter writer(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_WORLD);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_WORLD_ALL_INFO);
	PACKET_ENCODE(UInt32, m_world.size());
	map<uint16_t, DataWorldCity>::iterator itr = m_world.begin();
	for (; itr != m_world.end(); ++itr) {
		PACKET_ENCODE(UInt32, itr->first);
		vector<DataWorldCityUser>::iterator it = itr->second.users.begin();
		uint32_t count = 0;
		for (; it != itr->second.users.end(); ++it) {
			if (IS_VALID_PLAYER_UID(it->uid)) {
				++count;
			}
		}
		PACKET_ENCODE(UInt32, count);
	}
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool WorldManager::sendCity(uint32_t uid, uint32_t cid) {
	map<uint16_t, DataWorldCity>::iterator itr = m_world.find(cid);
	if (itr == m_world.end()) {
		error_log("cid error uid=%u cid=%u", uid, cid);
		return false;
	}
	CNetPacket sp;
	sp.uid = uid;
	CBufferWriter writer(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_WORLD);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_WORLD_CITY_INFO);
	PACKET_ENCODE(UInt32, cid);
	if (cid == WORLD_PROTECT_CID) {
		if (m_protect.count(uid)) {
			PACKET_ENCODE(UInt32, 1);
			PACKET_ENCODE(UInt32, uid);
			Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
			if (player != NULL) {
				PACKET_ENCODE(String, player->getName());
				PACKET_ENCODE(Byte, 0);
				PACKET_ENCODE(String, player->getFig());
				PACKET_ENCODE(Byte, 0);
			} else {
				PACKET_ENCODE(String, "");
				PACKET_ENCODE(Byte, 0);
				PACKET_ENCODE(String, "");
				PACKET_ENCODE(Byte, 0);
			}
		} else {
			PACKET_ENCODE(UInt32, 1);
			PACKET_ENCODE(UInt32, 0);
			PACKET_ENCODE(String, "");
			PACKET_ENCODE(Byte, 0);
			PACKET_ENCODE(String, "");
			PACKET_ENCODE(Byte, 0);
		}
	} else {
		vector<DataWorldCityUser> &users = itr->second.users;
		PACKET_ENCODE(UInt32, users.size());
		vector<DataWorldCityUser>::iterator it = users.begin();
		for (; it != users.end(); ++it) {
			PACKET_ENCODE(UInt32, it->uid);
			PACKET_ENCODE(String, it->name);
			PACKET_ENCODE(Byte, 0);
			PACKET_ENCODE(String, it->fig);
			PACKET_ENCODE(Byte, 0);
		}
	}
	PlayerManager::getInstance()->sendToAccess(&sp);
	debug_log("uid=%u cid=%u", uid, cid);
	return true;
}

bool WorldManager::sendUser(uint32_t uid) {
	CNetPacket sp;
	sp.uid = uid;
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (player == NULL) {
		return false;
	}
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_WORLD);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_WORLD_SELF_INFO);
	PACKET_ENCODE(UInt32, player->getRm()->getResources()->p3); // res
	PACKET_ENCODE(UInt32, 0); // produce
	PACKET_ENCODE(UInt32, 0); // len
	map<uint32_t, set<uint32_t> >::iterator itr = m_occupy.find(uid);
	if (itr == m_occupy.end()) {
		PACKET_ENCODE(UInt32, player->getWorldShopManager()->getAttackCount());
		PlayerManager::getInstance()->sendToAccess(&sp);
		return true;
	}
	uint32_t cnt = 0;
	uint32_t produce = 0;

	set<uint32_t> &occ = m_occupy[uid];
	set<uint32_t>::iterator it = occ.begin();
	for (; it != occ.end(); ++it) {
		uint32_t cid = (*it >> 16) & 0x0000FFFF;
		uint32_t pid = (*it) & 0x0000FFFF;
		PACKET_ENCODE(UInt32, cid);
		PACKET_ENCODE(UInt32, pid);
		if (cid == WORLD_PROTECT_CID) {
			if (m_protect.count(uid)) {
				produce += WorldConfig::getInstance()->getProduce(cid, pid, Time::GetGlobalTime() - m_protect[uid]);
			}
			PACKET_ENCODE(UInt32, 0);
		} else {
			const DataWorldCityUser *user = getUser(cid, pid);
			if (user == NULL) {
				PACKET_ENCODE(UInt32, 0);
			} else {
				produce += WorldConfig::getInstance()->getProduce(cid, pid, Time::GetGlobalTime() - user->ts);
				PACKET_ENCODE(UInt32, user->soldiers.size());
				vector<DataWorldCitySoldier>::const_iterator sit = user->soldiers.begin();
				for (; sit != user->soldiers.end(); ++sit) {
					PACKET_ENCODE(UInt32, sit->id);
					PACKET_ENCODE(UInt32, sit->value);
				}
			}
		}
		++cnt;
		//TODO only support one occupy
		break;
	}
	PACKET_ENCODE(UInt32, player->getWorldShopManager()->getAttackCount());
	uint32_t si = sp.GetBody()->GetSize();
	sp.GetBody()->SetSize(6);
	PACKET_ENCODE(UInt32, produce);
	PACKET_ENCODE(UInt32, cnt);
	sp.GetBody()->SetSize(si);

	PlayerManager::getInstance()->sendToAccess(&sp);
	debug_log("uid=%u,cnt=%u", uid, cnt);
	return true;
}

bool WorldManager::sendShopInfo(uint32_t uid) {
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (player == NULL) {
		error_log("load player error uid=%u", uid);
		return false;
	}
	CNetPacket sp;
	sp.uid = uid;
	CBufferWriter writer(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_WORLD);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_WORLD_SHOP_INFO);
	player->getWorldShopManager()->getInfo(sp.GetBody());
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool WorldManager::onSoldier(uint32_t uid, byte ret) {
	CNetPacket sp;
	sp.uid = uid;
	CBufferWriter writer(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_WORLD);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_WORLD_SOLDIER);
	PACKET_ENCODE(Byte, ret);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool WorldManager::onAttackErr(uint32_t uid, uint32_t cid, uint32_t pid, uint32_t def) {
	CNetPacket sp;
	sp.uid = uid;
	CBufferWriter writer(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_WORLD);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_WORLD_ATTACK);
	PACKET_ENCODE(Byte, R_ERROR);
	PACKET_ENCODE(UInt32, cid);
	PACKET_ENCODE(UInt32, pid);
	PACKET_ENCODE(UInt32, def);
	PACKET_ENCODE(UInt32, 0);
	PACKET_ENCODE(UInt32, 0);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool WorldManager::onFinish(uint32_t uid, uint32_t cid, uint32_t pid, byte ret) {
	CNetPacket sp;
	sp.uid = uid;
	CBufferWriter writer(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_WORLD);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_WORLD_FINISH);
	PACKET_ENCODE(Byte, ret);
	PACKET_ENCODE(UInt32, cid);
	PACKET_ENCODE(UInt32, pid);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool WorldManager::onShopBuy(uint32_t uid, byte ret) {
	CNetPacket sp;
	sp.uid = uid;
	CBufferWriter writer(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_WORLD);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_WORLD_SHOP_BUY);
	PACKET_ENCODE(Byte, ret);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool WorldManager::onHarvest(uint32_t uid, byte ret) {
	CNetPacket sp;
	sp.uid = uid;
	CBufferWriter writer(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_WORLD);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_WORLD_HARVEST);
	PACKET_ENCODE(Byte, ret);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool WorldManager::onUserLost(uint32_t uid, uint32_t ts, uint16_t cid, uint16_t pid) {
	if (!IS_VALID_PLAYER_UID(uid)) {
		return false;
	}
	if (m_occupy.count(uid)) {
		set<uint32_t> &occ = m_occupy[uid];
		occ.erase(MAKE_POINT(cid, pid));
	}
	uint32_t res = WorldConfig::getInstance()->getProduce(cid, pid, Time::GetGlobalTime() - ts);
	delRank(uid);
	if (PlayerManager::getInstance()->IsOnline(uid)) {
		sendUser(uid);
	}
	Player *player = PlayerManager::getInstance()->LoadForcePlayer(uid);
	if (player == NULL) {
		error_log("laod player error uid=%u", uid);
		return false;
	}
	ResourceCost cost;
	cost.p3 = res;
	player->getRm()->addResources(cost, "world_battle_lost_res");
	const string *cname = WorldConfig::getInstance()->getName(cid);
	string title = GET_LANG("world_battle_t");
	string content;
	String::Format(content, GET_LANG("world_battle_lost_c").c_str(), cname == NULL ? "" : cname->c_str(), res);
	player->getEmailManager()->addEmail(uid, title, content, "");
	return true;
}

bool WorldManager::onUserOccupy(uint32_t uid, uint16_t cid, uint16_t pid) {
	set<uint32_t> &occ = m_occupy[uid];
	uint32_t res = 0;
	for (set<uint32_t>::iterator itr = occ.begin(); itr != occ.end(); ++itr) {
		uint16_t ocid = (*itr) >> 16;
		uint16_t opid = (*itr) & 0x0000FFFF;
		if (ocid == WORLD_PROTECT_CID) {
			if (m_protect.count(uid)) {
				res += WorldConfig::getInstance()->getProduce(cid, pid, Time::GetGlobalTime() - m_protect[uid]);
			}
		} else {
			DataWorldCityUser *ouser = WorldManager::getUser(ocid, opid);
			if (ouser == NULL || ouser->uid != uid) {
				continue;
			}
			res += WorldConfig::getInstance()->getProduce(cid, pid, Time::GetGlobalTime() - ouser->ts);
			ouser->Clean();
		}
	}
	occ.clear();
	occ.insert(MAKE_POINT(cid, pid));
	m_protect.erase(uid);
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (player == NULL) {
		error_log("laod player error uid=%u", uid);
		return false;
	}
	if (res > 0) {
		ResourceCost cost;
		cost.p3 = res;
		player->getRm()->addResources(cost, "world_battle_give_up");
		string title = GET_LANG("world_battle_t");
		string content;
		String::Format(content, GET_LANG("world_battle_win_c").c_str(), res);
		player->getEmailManager()->addEmail(uid, title, content, "");
	}
	return true;
}

bool WorldManager::addRank(uint32_t uid, uint32_t value, uint16_t cid) {
	if (value == 0) {
		return false;
	}
	delRank(uid);
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (player == NULL) {
		return false;
	}
	DataWorldRankItem item;
	item.uid = uid;
	item.value = value;
	item.cid = cid;
	item.name = player->getName();

	list<DataWorldRankItem>::iterator itr = m_rank.begin();
	for (itr = m_rank.begin(); itr != m_rank.end() && (item.value > itr->value); ++itr) {
	}
	m_rank.insert(itr, item);
	if (m_rank.size() > WORLD_RANK_NUM) {
		m_rank.pop_back();
	}
	return true;
}

bool WorldManager::delRank(uint32_t uid) {
	list<DataWorldRankItem>::iterator itr = m_rank.begin();
	for (; itr != m_rank.end(); ++itr) {
		if (itr->uid == uid) {
			m_rank.erase(itr);
			return true;
		}
	}
	return false;
}

DataWorldCityUser* WorldManager::getUser(uint32_t cid, uint32_t pid) {
	if (!WorldConfig::getInstance()->isExists(cid, pid)) {
		return NULL;
	}
	DataWorldCity &city = m_world[cid];
	if (city.users.size() <= pid) {
		city.users.resize(pid + 1);
	}
	return &(city.users[pid]);
}

bool WorldManager::occupyProtect(uint32_t uid) {
	map<uint32_t, uint32_t>::iterator itr = m_protect.find(uid);
	if (itr != m_protect.end()) {
		return true;
	}
	m_protect.insert(make_pair(uid, Time::GetGlobalTime()));
	set<uint32_t> &occ = m_occupy[uid];
	for (set<uint32_t>::iterator itr = occ.begin(); itr != occ.end(); ++itr) {
		uint16_t ocid = (*itr) >> 16;
		uint16_t opid = (*itr) & 0x0000FFFF;
		DataWorldCityUser *ouser = WorldManager::getUser(ocid, opid);
		if (ouser == NULL || ouser->uid != uid) {
			continue;
		}
		ouser->Clean();
	}
	occ.clear();
	occ.insert(MAKE_POINT(WORLD_PROTECT_CID, 0));
	onFinish(uid, WORLD_PROTECT_CID, 0, R_SUCCESS);
	sendUser(uid);
	delRank(uid);
	return true;
}

