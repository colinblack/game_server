/*
 *
 *  Created on: 2015-9-9
 *      Author: Administrator
 */

#include "PlayerManager.h"
#include "LoginServer.h"
#include "LogicIdCtrl.h"
#include "OpenPlatform.h"
#include "RankManager.h"
#include "ActivityTimeManager.h"

PlayerManager::PlayerManager() {
	m_last_lru_time = 0;
	m_last_stat_time = 0;
	m_load_times = 0;
	m_hit_times = 0;
}
PlayerManager::~PlayerManager() {
}
bool PlayerManager::doPacket(CNetPacket * packet) {
	Player *player = LoadForcePlayer(packet->uid);
	if (!player) {
		error_log("player manager do not find player:%u cmd=%u subcmd=%u", packet->uid, packet->cmd, packet->subCmd);
		return false;
	}
	player->doPacket(packet);
	return true;
}
bool PlayerManager::doLogin(CNetPacket * packet) {
	CLoginProtocol login;
	if (!login.Decode(&(packet->body))) {
		error_log("CLoginProtocol decode failed");
		return false;
	}
	int pt = OpenPlatform::GetType(login.span_id, login.platform);
	if (pt == PT_UNKNOW || (pt == PT_TEST && !IsInternal())) {
		error_log("unknow pt openid=%s platform=%u pf=%u", login.openId.c_str(), login.platform, login.span_id);
		return false;
	}
	uint32_t uid = 0;
	if (!GetUid(login.reg_server_id, pt, login.openId, uid)) {
		error_log("login in get uid failed openid=%s platform=%u pf=%u", login.openId.c_str(), login.platform, login.span_id);
		return false;
	}
	CDataUserMapping dbUserMapping;
	dbUserMapping.SetLastLogin(login.reg_server_id, pt, login.openId);
	uint32_t fd = 0;
	uint32_t stime = 0;
	uint32_t mtime = 0;
	bool online = FdManager::getInstance()->getFd(uid, fd, stime, mtime);
	if (online) {
		forceKick(uid, "repeat_login");
	}
	FdManager::getInstance()->addMap(packet->fd, packet->stime, packet->mtime, uid, 0, 0, login.reg_server_id);
	struct timeval tv;
	gettimeofday(&tv, NULL);
	uint32_t mts = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	bool isNewUser = false;
	if (!IsNewUser(uid, isNewUser)) {
		error_log("check is new user fail uid=%u", uid);
		return false;
	}
	Player *player = NULL;
	if (isNewUser) {
		player = CreatePlayer(uid, pt);
	} else {
		player = LoadForcePlayer(uid);
	}

	if (player == NULL) {
		error_log("LoadForcePlayer fail uid=%u", uid);
		return false;
	}
	if (!isNewUser) {
		player->setIsNewUser(false);
	}
	if (player->isBlock()) {
		error_log("block user uid=%u", uid);
		return false;
	}
	player->setOnline();
	LoginConfirm(uid, R_SUCCESS);
	player->getAutoTransportRes();
	player->initTimerList();
	player->setUid(uid);
	player->setOpenId(login.openId);
	player->setOpenKey(login.openKey);
	player->setVipLevel();
	player->setRegServerId(login.reg_server_id);
	player->setCurServerId(login.cur_server_id);
	player->setSpanId(login.span_id);
	if (IsInternal() && IS_VALID_PLAYER_UID(uid)) {
		player->setUserName(login.openId);
	}
	player->calcGemCombat(false);
	player->resetUserDaily();
	player->sendBaseInfo();
	player->onLogin();
	player->onPlatfromGift(login.platform_gift);
	m_onlines[player->getUid()] = player;

	gettimeofday(&tv, NULL);
	uint32_t mts2 = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	debug_log("uid=%u pf=%u pt=%u mts=%u mts2=%u span=%u", uid, login.span_id, login.platform, mts, mts2, mts2 - mts);
	packet->uid = uid;
	PlayerManager::getInstance()->doTransitLogin(packet);
	BUSI_LOGIN("%u|%u|login|%u|%u|%s|%u|%u", LogicManager::ServerId, uid, LogicManager::GlobalTime, player->getLevel(), login.openId.c_str(), pt, player->getIsNewUser() ? 1 : 0);
	return true;
}
bool PlayerManager::doTencentUserInfo(CNetPacket * packet) {
	uint32_t uid = packet->uid;
	CTransitLoginProtocol login;
	if (!login.Decode(&(packet->body))) {
		error_log("CTransitLoginProtocol decode failed");
		return false;
	}
	Player * player = LoadExistPlayer(uid);
	if (player == NULL) {
		error_log("LoadExistPlayer fail uid=%u", uid);
		return false;
	}
	player->setTencentInfo(login.info);
	if (login.info.name.length() > 0) {
		player->setUserName(login.info.name);
	}
	player->setUserUrl(login.info.url);
	player->sendTencentUserInfo();
	if (IS_VALID_PLAYER_UID(player->getUserInfo().invite_by)) {
		if (ServerConfig::getInstance()->IsMerged(Config::GetZoneByUID(player->getUserInfo().invite_by))) {
			Player *inviter = LoadForcePlayer(player->getUserInfo().invite_by);
			if (inviter) {
				inviter->getSocialManager()->updatePic(uid, login.info.url);
			}
		} else {
			// TODO other server
		}
	}
	player->doAddRank();
	return true;
}
bool PlayerManager::doTencentFriendInfo(CNetPacket * packet) {
	CTransitFriendProtocol protocol;
	if (!protocol.Decode(&(packet->body))) {
		error_log("CTransitFriendProtocol decode error uid=%u", packet->uid);
		return false;
	}
	uint32_t uid = packet->uid;
	Player * player = LoadExistPlayer(uid);
	if (player == NULL) {
		error_log("LoadExistPlayer fail uid=%u", uid);
		return false;
	}
	return true;
}
bool PlayerManager::IsNewUser(uint32_t uid, bool &isNew) {
	map<uint32_t, Player*>::iterator itr = m_players.find(uid);
	if (itr != m_players.end()) {
		isNew = false;
		return true;
	}
	CDataUser dbc;
	DataUser user;
	int ret = dbc.GetUser(uid, user);
	if (0 == ret) {
		isNew = false;
		return true;
	} else if (R_ERR_NO_DATA == ret) {
		isNew = true;
		return true;
	}
	return false;
}
Player* PlayerManager::CreatePlayer(uint32_t uid, uint32_t platform) {
	Player *player = NULL;
	map<uint32_t, Player*>::iterator it = m_players.find(uid);
	if (it != m_players.end()) {
		player = it->second;
	}
	if (!player) {
		player = new Player();
		m_players[uid] = player;
		player->setLoginPlatform(platform);
		player->setIsNewUser(true);
		if (!player || !player->LoadNewPlayerData(uid)) {
			m_players.erase(uid);
			if (player) {
				delete player;
				player = NULL;
			}
		}
	}
	if (player != NULL) {
		FreshLru(uid);
	}
	return player;
}
Player* PlayerManager::LoadForcePlayer(uint32_t uid) {
	m_load_times++;
	Player * player = NULL;
	map<uint32_t, Player*>::iterator it = m_players.find(uid);
	if (it != m_players.end()) {
		player = it->second;
		m_hit_times++;
	}
	if (!player) {
		player = new Player();
		m_players[uid] = player;
		if (!player || !player->LoadPlayerData(uid)) {
			m_players.erase(uid);
			if (player) {
				delete player;
				player = NULL;
			}
		}
	}
	if (player != NULL) {
		FreshLru(uid);
	}
	return player;
}
Player* PlayerManager::LoadExistPlayer(uint32_t uid) {
	Player * player = NULL;
	map<uint32_t, Player*>::iterator it = m_players.find(uid);
	if (it != m_players.end()) {
		player = it->second;
		FreshLru(uid);
	}
	return player;
}
bool PlayerManager::sendToAccess(CNetPacket* packet) {
	packet->ptype = PROTOCOL_TYPE_ACCESS_ANSWER;
	FDINFO fdInfo;
	if (FdManager::getInstance()->getFdInfo(packet->uid, fdInfo) && isLoadComplete(packet->uid)) {
		packet->fd = fdInfo.fd;
		packet->stime = fdInfo.time;
		packet->mtime = fdInfo.microTime;
		return LoginServer::getInstance()->sendData(packet);
	}
	byte cmd = 0;
	byte subCmd = 0;
	if (packet->body.GetSize() > 2) {
		packet->body.GetData(&cmd, 1, 0);
		packet->body.GetData(&subCmd, 1, 1);
	}
	error_log("getFdInfo fail uid=%u cmd=%d subCmd=%d", packet->uid, static_cast<int>(cmd), static_cast<int>(subCmd));
	return false;
}
bool PlayerManager::sendToBattle(CNetPacket* packet) {
	packet->fd = packet->uid;
	packet->ptype = PROTOCOL_TYPE_BATTLE_TRANSFER;
	LoginServer::getInstance()->sendData(packet);
	return false;
}
void PlayerManager::getCountryPlayer(byte country, vector<Player *> &vecPlayers) {
	vecPlayers.clear();
	map<uint32_t, Player*>::iterator it = m_players.begin();
	for (; it != m_players.end(); ++it) {
		if (it->second->getKingdom() == country) {
			vecPlayers.push_back(it->second);
		}
	}
}
bool PlayerManager::addPlayer(Player * player) {
	m_players[player->getUid()] = player;
	return true;
}
bool PlayerManager::onSecondTimer() {
	PrintStat();
	for (map<uint32_t, Player*>::iterator it = m_players.begin(); it != m_players.end(); ++it) {
		it->second->onTimer();
	}
	set<uint32_t> delUid;
	if (m_lru_player_cache.size() > CACHE_MAX_COUNT) {
		if (m_last_lru_time + CACHE_CHECK_INTER <= LogicManager::GlobalTime) {
			uint32_t extra_count = m_lru_player_cache.size() - CACHE_MAX_COUNT;
			uint32_t i;
			list<LruCache>::iterator it;
			for (it = m_lru_player_cache.begin(), i = 0; it != m_lru_player_cache.end() && i < extra_count;) {
				if (IsIdle(it->uid)) {
					i++;
					delUid.insert(it->uid);
					it = m_lru_player_cache.erase(it);
				} else {
					it++;
				}
			}
			m_last_lru_time = LogicManager::GlobalTime;
		}
	}
	for (set<uint32_t>::iterator uIter = delUid.begin(); uIter != delUid.end(); ++uIter) {
		map<uint32_t, Player*>::iterator iter = m_players.find(*uIter);
		if (iter != m_players.end()) {
			if (iter->second != NULL) {
				delete iter->second;
			}
			m_players.erase(iter);
		}
	}
	map<uint32_t, Player*>::iterator ito;
	for (ito = m_onlines.begin(); ito != m_onlines.end(); ito++) {
		Player * player = ito->second;
		if (player != NULL && player->isQzone()) {

		}
	}
	return true;
}
bool PlayerManager::onHeroLevelUp(uint32_t uid) {
	map<uint32_t, Player*>::iterator it = m_players.find(uid);
	if (it != m_players.end() && it->second) {
	}
	return false;
}
bool PlayerManager::doTransitLogin(CNetPacket * packet) {
	packet->stime = LogicManager::ServerId;
	packet->mtime = LogicManager::ServerId;
	packet->fd = packet->uid;

	return sendToTransit(packet);
}
bool PlayerManager::doGetBlueInfoAnswer(CNetPacket * packet) {
	return true;
}
bool PlayerManager::doPayGetTokenAnswer(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CTransitPayGetTokenProtocol protocol;
	if (!protocol.Decode(&(packet->body))) {
		error_log("CTransitPayGetTokenProtocol decode failed uid=%u", uid);
		return false;
	}
	Player * player = LoadExistPlayer(uid);
	if (player == NULL) {
		error_log("player is NULL uid=%u", uid);
		return false;
	}
	CNetPacket sRspPacket;
	sRspPacket.uid = uid;
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_USER);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_USER_GET_PAY_TOKEN);
	selfWriter.AppendString(protocol.token);
	selfWriter.AppendByte(0);
	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket)) {
		error_log("sendAccess_fail&uid=%u", uid);
		return false;
	}
	return true;
}
bool PlayerManager::sendToTransit(CNetPacket *packet) {
	packet->ptype = PROTOCOL_TYPE_TRANSIT_TRANSFER;
	packet->fd = packet->uid;
	return LoginServer::getInstance()->sendData(packet);
}
bool PlayerManager::setPlayerPropChange(uint32_t uid) {
	map<uint32_t, Player*>::iterator it = m_players.find(uid);
	if (it != m_players.end() && it->second != NULL) {
		it->second->setPropChange();
	}
	return false;
}
bool PlayerManager::IsOnline(uint32_t uid) {
	FDINFO sInfo;
	return FdManager::getInstance()->getFdInfo(uid, sInfo);
}
bool PlayerManager::isLoadComplete(uint32_t uid) {
	map<uint32_t, Player*>::iterator iter = m_players.find(uid);
	if (iter == m_players.end()) {
		return false;
	}
	Player* player = iter->second;
	if (player == NULL) {
		return false;
	}
	return player->isLoadComplete();
}
bool PlayerManager::forceKick(uint32_t uid, const string & reason) {
	FDINFO sInfo;
	if (!FdManager::getInstance()->getFdInfo(uid, sInfo)) {
		error_log("cannot find [%u]'s fd info", uid);
		return false;
	}
	CNetPacket sPacket;
	sPacket.uid = uid;
	sPacket.ptype = PROTOCOL_TYPE_LOFFLINE;
	sPacket.fd = sInfo.fd;
	sPacket.stime = sInfo.time;
	sPacket.mtime = sInfo.microTime;
	LoginServer::getInstance()->sendData(&sPacket);
	offlineProcess(uid, reason);
	return true;
}
bool PlayerManager::offlineProcess(uint32_t uid, const string & reason) {
	FDINFO sInfo;
	if (!FdManager::getInstance()->getFdInfo(uid, sInfo)) {
		error_log("offline can not find uid:%d", uid);
		return false;
	}
	uint32_t onlineTime = 0;
	FdManager::getInstance()->delMap(sInfo.fd, sInfo.time, sInfo.microTime);
	Player * player = LoadExistPlayer(uid);
	if (player) {
		player->onOffline(uid);
		player->setOffline();
		onlineTime = player->getOfflineTime() - player->getLoginTime();
		m_onlines.erase(uid);
	}
	InformTransit(uid);
	BUSI_LOGIN("%u|%u|offline|%s|%u|%u", LogicManager::ServerId, uid, reason.c_str(), LogicManager::GlobalTime, onlineTime);
	return true;
}
bool PlayerManager::InformTransit(uint32_t uid) {
	CNetPacket packet;
	CStaticBuffer<0xFF> body;
	CBufferWriter writer(&body);
	writer.AppendByte(PROTOCOL_CMD_TRANSIT);
	writer.AppendByte(PROTOCOL_SUBCMD_TRANSIT_OFFLINE);
	writer.AppendUInt32(uid);
	packet.SetBody(&body);

	sendToTransit(&packet);

	return true;
}
bool PlayerManager::GetUid(uint32_t serverId, uint32_t platform, string & openId, uint32_t & uid) {
	CDataUserMapping dbuserMapping;
	int ret = dbuserMapping.GetMapping(serverId, platform, openId, uid);
	if (ret == R_SUCCESS) {
		return true;
	} else if (ret == R_ERR_NO_DATA) {
		CLogicIdCtrl dbIdCtrl;
		uint32_t nextUid;
		ret = dbIdCtrl.GetNextId(KEY_UID_CTRL, nextUid, serverId);
		if (R_SUCCESS != ret) {
			error_log("GetNextId_fail&ret=%d", ret);
			return false;
		}
		uid = nextUid;
		ret = dbuserMapping.AddMapping(serverId, platform, openId, uid);
		if (ret != 0) {
			error_log("AddMapping_fail&openId=%s&uid=%u", openId.c_str(), uid);
			return false;
		}
		return true;
	} else {
		error_log("GetMapping fail openId=%s", openId.c_str());
		return false;
	}
}
bool PlayerManager::LoginConfirm(uint32_t uid, byte ret) {
	CNetPacket sRspPacket;
	sRspPacket.uid = uid;
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_LOGIN);
	selfWriter.AppendByte(PROTOCOL_RSP_SUBCMD_LOGIN);
	selfWriter.AppendByte(ret);
	PlayerManager::getInstance()->sendToAccess(&sRspPacket);
	return true;
}
void PlayerManager::FreshLru(uint32_t uid) {
	if (IS_VALID_PLAYER_UID(uid)) {
		LruCache sCache;
		sCache.uid = uid;
		list<LruCache>::iterator it = find(m_lru_player_cache.begin(), m_lru_player_cache.end(), sCache);
		if (it != m_lru_player_cache.end()) {
			m_lru_player_cache.erase(it);
		}
		sCache.set_stamp();
		m_lru_player_cache.push_back(sCache);
	} else {
		LruCache sCache;
		sCache.uid = uid;
		sCache.set_stamp();
		list<LruCache>::iterator it = find(m_lru_npc_cache.begin(), m_lru_npc_cache.end(), sCache);
		if (it == m_lru_npc_cache.end()) {
			m_lru_npc_cache.push_back(sCache);
		}
	}
}
bool PlayerManager::delLruPlayerCache(uint32_t uid) {
	set<uint32_t> delUid;
	for (list<LruCache>::iterator it = m_lru_player_cache.begin(); it != m_lru_player_cache.end(); ++it) {
		if (it->uid == uid) {
			delUid.insert(it->uid);
			it = m_lru_player_cache.erase(it);
			break;
		}
	}
	for (list<LruCache>::iterator it = m_lru_npc_cache.begin(); it != m_lru_npc_cache.end(); ++it) {
		if (it->uid == uid) {
			delUid.insert(it->uid);
			it = m_lru_npc_cache.erase(it);
			break;
		}
	}
	for (set<uint32_t>::iterator uIter = delUid.begin(); uIter != delUid.end(); ++uIter) {
		map<uint32_t, Player*>::iterator iter = m_players.find(*uIter);
		if (iter != m_players.end()) {
			if (iter->second != NULL) {
				delete iter->second;
			}
			m_players.erase(iter);
		}
	}
	return true;
}
bool PlayerManager::AddiactionNotify(uint32_t uid, uint32_t hour) {
	CNetPacket sRspPacket;
	sRspPacket.uid = uid;
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_USER);
	selfWriter.AppendByte(PROTOCOL_RSP_SUBCMD_ADDTCTION_NOTIFY);
	selfWriter.AppendUInt32(hour);
	PlayerManager::getInstance()->sendToAccess(&sRspPacket);
	return true;
}
bool PlayerManager::sendActTime() {
	map<uint32_t, Player*>::iterator itr = m_onlines.begin();
	for (; itr != m_onlines.end(); ++itr) {
		ActivityTimeManager::getInstance()->sendInfo(itr->first);
		Player *player = itr->second;
		if (player != NULL) {
			player->getActManager()->onReload();
		}
	}
	return true;
}
bool PlayerManager::IsInternal() {
	uint32_t isInter = Config::GetIntValue("internal");
	return isInter == 1;
}
bool PlayerManager::IsIdle(uint32_t uid) {
	return !IsOnline(uid);
}
bool PlayerManager::PrintStat() {
	if (m_last_stat_time + CACHE_STAT_INTER > LogicManager::GlobalTime) {
		return false;
	}
	debug_log("########### System LRU Info ###########");
	list<LruCache>::iterator its = m_lru_player_cache.begin();
	list<LruCache>::reverse_iterator ite = m_lru_player_cache.rbegin();
	debug_log("Npc cache count:%d", m_lru_npc_cache.size());
	debug_log("Player cache count:%d m_players_size:%u", m_lru_player_cache.size(), m_players.size());
	if (m_lru_player_cache.size() != 0) {
		debug_log("First cache uid:%d stamp:%d", its->uid, its->stamp);
		debug_log("Last cache uid:%d stamp:%d", ite->uid, ite->stamp);
	}
	string rate = "";
	if (m_load_times != 0) {
		uint32_t irate = m_hit_times * 100 / m_load_times;
		rate.append(Convert::IntToString(irate));
	} else {
		rate.append("NONE");
	}
	debug_log("Load times:%d Hit times:%d Hitrate:%s\%", m_load_times, m_hit_times, rate.c_str());
	m_last_stat_time = LogicManager::GlobalTime;
	return true;
}
bool PlayerManager::GetOnlineUsers(vector<uint32_t> & vUids) {
	vector<FDINFO> vecFd;
	vector<FDINFO>::iterator it;
	FdManager::getInstance()->getAllFd(vecFd);
	for (it = vecFd.begin(); it != vecFd.end(); it++) {
		uint32_t uid = 0;
		uint32_t rid = 0;
		if (FdManager::getInstance()->getRole(it->fd, it->time, it->microTime, uid, rid)) {
			vUids.push_back(uid);
		}
	}
	return true;
}
bool PlayerManager::getUserInfo(uint32_t uid, DataUser& dataUser) {
	Player* player = NULL;
	if ((player = PlayerManager::getInstance()->LoadExistPlayer(uid)) != NULL) {
		dataUser = player->getUserInfo();
		return true;
	} else {
		CDataUser user;
		if (user.GetUser(uid, dataUser) != 0) {
			error_log("GetUser fail uid=%u", uid);
			return false;
		}
		return true;
	}
	return false;
}
