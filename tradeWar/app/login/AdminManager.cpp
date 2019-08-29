/*
 * AdminManager.cpp
 *
 *  Created on: 2016年2月3日
 *      Author: asdf
 */
#include "AdminManager.h"
#include "ProtocolAdmin.h"
#include "FdManager.h"
#include "PlayerManager.h"
#include "LogicManager.h"
#include "LoginServer.h"
#include "SystemEmail.h"
#include "BuyGoodsManager.h"
#include "SocialManager.h"
#include "PayConfig.h"
#include "TroopsManager.h"

AdminManager::AdminManager() {
	m_adminInfo.clear();
}
AdminManager::~AdminManager() {
}

bool AdminManager::doAdmin(CNetPacket* packet) {
	switch (packet->subCmd) {
	case PROTOCOL_SUBCMD_ADMIN_SET_ALL_HERO_EXIT_BATTLE:
		doSetAllHeroExitBattle(packet);
		break;
	case PROTOCOL_SUBCMD_ADMIN_CHANGE_ACT_TIME:
		//ActivityOpenList::getInstance()->doChange(packet);
		break;
	case PROTOCOL_SUBCMD_ADMIN_KICK_USER:
		doKickUser(packet);
		break;
	case PROTOCOL_SUBCMD_ADMIN_PRINT_LOG:
		doPrintLog(packet);
		break;
	case PROTOCOL_SUBCMD_ADMIN_LOGIN:
		doLogin(packet);
		break;
	case PROTOCOL_SUBCMD_ADMIN_CLIENT:
		doClient(packet);
		break;
	default:
		error_log("unknow subcmd=%u", packet->subCmd);
		break;
	}
	info_log("cmd=%u,subcmd=%u,fd=%u", (int )(packet->cmd), (int )(packet->subCmd), packet->fd);
	return true;
}
bool AdminManager::doSetAllHeroExitBattle(CNetPacket* packet) {
	return false;
	CAdminSetHeroExitBattleProtocol protocol;
	if (!protocol.Decode(&(packet->body))) {
		error_log("CAdminSetHeroExitBattleProtocol_fail&uid=%u", packet->uid);
		return false;
	}
	uint32_t targetUid = protocol.targetUid; // 需要修改数据的目标用户
	Player * player = PlayerManager::getInstance()->LoadExistPlayer(targetUid);
	if (player == NULL) {
		error_log("not exist player targetUid=%u", targetUid);
		return false;
	}
	debug_log("setAllHeroExitBattle uid=%u targetUid=%u", packet->uid, targetUid);
	return true;
}

void AdminManager::addMoney(CNetPacket *packet) {
	CAddMoneyProtocol protocol;
	if (!protocol.Decode(&packet->body)) {
		error_log("decode protocol failed");
		return;
	}

	Player * player = PlayerManager::getInstance()->LoadExistPlayer(protocol.uid);
	if (!player) {
		return;
	}

	if (protocol.count > 0) {
		MoneyCost cost;
		cost.cash = protocol.type == 1 ? protocol.count : 0;
		cost.coin = protocol.type == 2 ? protocol.count : 0;
		string reason = protocol.flag == 1 ? "admin_buy" : "admin_add";
		player->getRm()->addMoney(cost, reason);
	} else {
		MoneyCost cost;
		cost.cash = protocol.type == 1 ? -protocol.count : 0;
		cost.coin = protocol.type == 2 ? -protocol.count : 0;
		player->getRm()->useMoney(cost, "admin_dec");
	}

}

void AdminManager::doPrintLog(CNetPacket* packet) {
	CPrintLogProtocol protocol;
	if (!protocol.Decode(&packet->body)) {
		error_log("CPrintLogProtocol decode protocol failed");
		return;
	}
	uint32_t sec = protocol.sec;
	if (sec > 10) {
		sec = 10;
	}
	LoginServer::getInstance()->setLogTs(Time::GetGlobalTime() + sec);
	return;
}
bool AdminManager::doKickUser(CNetPacket* packet) {
	uint32_t uid = packet->uid;
	CKickUserProtocol protocol;
	if (!protocol.Decode(&packet->body)) {
		error_log("CKickUserProtocol decode protocol failed uid=%u", uid);
		return false;
	}
	uint32_t kickUid = protocol.uid;
	Player* kickPlayer = NULL;
	if ((kickPlayer = PlayerManager::getInstance()->LoadExistPlayer(kickUid)) == NULL) {
		return true; // 已经下线
	}
	if (!PlayerManager::getInstance()->forceKick(kickUid, "admin_do_that")) {
		error_log("forceKick fail uid=%u kickUid=%u", uid, kickUid);
	}
	if (!PlayerManager::getInstance()->delLruPlayerCache(kickUid)) {
		error_log("delLruPlayerCache fail uid=%u kickUid=%u", uid, kickUid);
	}
	return true;
}
bool AdminManager::doKickUser(uint32_t kickUid) {
	Player* kickPlayer = NULL;
	if ((kickPlayer = PlayerManager::getInstance()->LoadExistPlayer(kickUid)) == NULL) {
		return true; // 已经下线
	}
	if (!PlayerManager::getInstance()->forceKick(kickUid, "admin_do_that")) {
		error_log("forceKick fail uid=%u kickUid=%u", kickUid, kickUid);
	}
	if (!PlayerManager::getInstance()->delLruPlayerCache(kickUid)) {
		error_log("delLruPlayerCache fail uid=%u kickUid=%u", kickUid, kickUid);
	}
	return true;
}

void AdminManager::doClient(CNetPacket* packet) {
	Json::Value result;
	result["error"] = -1;
	CAClientRquestProtocol request;
	if (!request.Decode(&packet->body)) {
		doClientResult(Json::ToString(result), packet);
		return;
	}
	debug_log("[data=%s]", request.data.c_str());
	Json::Value data;
	Json::Reader reader;
	if (!reader.parse(request.data, data)) {
		error_log("[parse error][data=%s]", request.data.c_str());
		doClientResult(Json::ToString(result), packet);
		return;
	}
	string action;
	if (!Json::GetString(data, "action", action)) {
		action.clear();
	}

	if (action == "export") {
		doExport(data, result);
	} else if (action == "import") {
		doImport(data, result);
	} else if (action == "querypay") {
		doQueryPay(data, result);
	} else if (action == "changepay") {
		doModifyPay(data, result);
	} else if (action == "email") {
		doEmail(data, result);
	} else if (action == "charge") {
		doCharge(data, result);
	} else if (action == "queryfriend") {
		doQueryFriend(data, result);
	} else if (action == "addfriend") {
		doAddFriend(data, result);
	} else if (action == "getequipment") {
		doQueryEquip(data, result);
	} else if (action == "addequipment") {
		doAddEquip(data, result);
	} else if (action == "blockuser") {
		doBlockUser(data, result);
	}
	doClientResult(Json::ToString(result), packet);
	return;
}

void AdminManager::doClientResult(const string &data, CNetPacket* packet) {
	CAClientReplyProtocol reply;
	reply.cmd = PROTOCOL_CMD_ADMIN;
	reply.subCmd = PROTOCOL_SUBCMD_ADMIN_CLIENT;
	reply.data = data;
	CStaticBuffer<MAX_PROTOCOL_BODY_SIZE> body;
	reply.Encode(&body);

	CNetPacket sPacket;
	sPacket.uid = 0;
	sPacket.ptype = PROTOCOL_TYPE_ADMIN;
	sPacket.fd = packet->fd;
	sPacket.stime = packet->stime;
	sPacket.mtime = packet->mtime;
	sPacket.SetBody(&body);
	LoginServer::getInstance()->sendData(&sPacket);
}

void AdminManager::doLogin(CNetPacket* packet) {
	Json::Value result;
	result["error"] = -1;
	CALoginRquestProtocol request;
	if (!request.Decode(&packet->body)) {
		doClientResult(Json::ToString(result), packet);
		return;
	}

	if (!InitAdminInfo()) {
		doClientResult(Json::ToString(result), packet);
		return;
	}
	map<string, AdminInfo>::iterator it = m_adminInfo.find(request.userName);
	if (it == m_adminInfo.end()) {
		doClientResult(Json::ToString(result), packet);
		return;
	}
	if (it->second.tryCount >= 10) {
		doClientResult(Json::ToString(result), packet);
		return;
	}
	if (request.passWord != it->second.pwd) {
		it->second.tryCount += 1;
		doClientResult(Json::ToString(result), packet);
		return;
	}
	it->second.skey = Math::GetRandomInt();
	result["skey"] = it->second.skey;
	result["error"] = 0;
	doClientResult(Json::ToString(result), packet);
	return;
}

void AdminManager::doExport(const Json::Value &data, Json::Value &result) {
	if (!CheckSkey(data)) {
		result["error"] = "check_key_error";
		return;
	}
	uint32_t userid;
	if (!Json::GetUInt(data, "uid", userid)) {
		result["error"] = "uid_error";
		return;
	}
	Json::Value archive;

	//soldier
	if (!exportSoldier(userid, archive["soldier"])) {
		result["error"] = "export_soldier_error";
		return;
	}
	//equipment
	if (!exportEquipment(userid, archive["equipment"])) {
		result["error"] = "export_equipment_error";
		return;
	}
	//building
	if (!exportBuilding(userid, archive["baseop"])) {
		result["error"] = "export_baseop_error";
		return;
	}
	//resource
	if (!exportResource(userid, archive["resource"])) {
		result["error"] = "export_resource_error";
		return;
	}
	//user
	if (!exportUser(userid, archive)) {
		result["error"] = "export_user_error";
		return;
	}
	//task
	if (!exportTask(userid, archive["task"])) {
		result["error"] = "export_task_error";
		return;
	}
	//pretask
	if (!exportPreTask(userid, archive["pretask"])) {
		result["error"] = "export_pre_task_error";
		return;
	}
	//gate
	if (!exportGate(userid, archive["gate"])) {
		result["error"] = "export_gate_error";
		return;
	}
	//state
	if (!exportState(userid, archive["state"])) {
		result["error"] = "export_state_error";
		return;
	}
	//hero
	if (!exportHero(userid, archive["hero"])) {
		result["error"] = "export_hero_error";
		return;
	}
	//troops
	if (!exportTroops(userid, archive["troops"])) {
		result["error"] = "export_troops_error";
		return;
	}
	//skill
	if (!exportSkill(userid, archive["skill"])) {
		result["error"] = "export_skill_error";
		return;
	}
	//defend
	if (!exportDefend(userid, archive["defend"])) {
		result["error"] = "export_defend_error";
		return;
	}
	//tower
	if (!exportTower(userid, archive["tower"])) {
		result["error"] = "export_tower_error";
		return;
	}
	//dailytask
	if (!exportActiveness(userid, archive["dailytask"])) {
		result["error"] = "export_dailytask_error";
		return;
	}
	//boat
	if (!exportBoat(userid, archive["boat"])) {
		result["error"] = "export_boat_error";
		return;
	}
	//activity
	if (!exportActivity(userid, archive["act"])) {
		result["error"] = "export_activity_error";
		return;
	}
	//chgs
	if (!exportChargeHistory(userid, archive["chgs"])) {
		result["error"] = "export_charge_history_error";
		return;
	}
	//gem
	if (!exportGem(userid, archive["gem"])) {
		result["error"] = "export_gem_error";
		return;
	}
	result["error"] = 0;
	result["archive"] = Json::ToString(archive);
	return;
}

void AdminManager::doImport(const Json::Value &data, Json::Value &result) {
	if (!CheckSkey(data)) {
		result["error"] = "check_key_error";
		return;
	}
	uint32_t userid;
	if (!Json::GetUInt(data, "uid", userid)) {
		result["error"] = -1;
		return;
	}
	string archiveStr;
	if (!Json::GetString(data, "archive", archiveStr)) {
		result["error"] = -1;
		return;
	}
	try {
		Json::Value archive;
		if (!Json::FromString(archive, archiveStr)) {
			result["error"] = "pare_archive_error";
			return;
		}
		if (archive.isNull() || !archive.isObject()) {
			result["error"] = "archive_error";
			return;
		}
		//soldier
		if (!importSoldier(userid, archive["soldier"])) {
			result["error"] = "import_soldier_error";
			return;
		}
		//equipment
		if (!importEquipment(userid, archive["equipment"])) {
			result["error"] = "import_equipment_error";
			return;
		}
		//building
		if (!importBuilding(userid, archive["baseop"])) {
			result["error"] = "import_baseop_error";
			return;
		}
		//resource
		if (!importResource(userid, archive["resource"])) {
			result["error"] = "import_resource_error";
			return;
		}
		//user
		if (!importUser(userid, archive)) {
			result["error"] = "import_user_error";
			return;
		}
		//task
		if (!importTask(userid, archive["task"])) {
			result["error"] = "import_task_error";
			return;
		}
		//pretask
		if (!importPreTask(userid, archive["pretask"])) {
			result["error"] = "import_pre_task_error";
			return;
		}
		//gate
		if (!importGate(userid, archive["gate"])) {
			result["error"] = "import_gate_error";
			return;
		}
		//state
		if (!importState(userid, archive["state"])) {
			result["error"] = "import_state_error";
			return;
		}
		//hero
		if (!importHero(userid, archive["hero"])) {
			result["error"] = "import_hero_error";
			return;
		}
		//troops
		if (!importTroops(userid, archive["troops"])) {
			result["error"] = "import_troops_error";
			return;
		}
		//skill
		if (!importSkill(userid, archive["skill"])) {
			result["error"] = "import_skill_error";
			return;
		}
		//defend
		if (!importDefend(userid, archive["defend"])) {
			result["error"] = "import_defend_error";
			return;
		}
		//tower
		if (!importTower(userid, archive["tower"])) {
			result["error"] = "import_tower_error";
			return;
		}
		//dailytask
		if (!importActiveness(userid, archive["dailytask"])) {
			result["error"] = "import_daily_task_error";
			return;
		}
		//boat
		if (!importBoat(userid, archive["boat"])) {
			result["error"] = "import_boat_error";
			return;
		}
		//activity
		if (!importActivity(userid, archive["act"])) {
			result["error"] = "import_activity_error";
			return;
		}
		//chgs
		if (!importChargeHistory(userid, archive["chgs"])) {
			result["error"] = "import_charge_history_error";
			return;
		}
		//gem
		if (!importGem(userid, archive["gem"])) {
			result["error"] = "import_gem_error";
			return;
		}
	} catch(const std::exception& e) {
		error_log("import error msg=%s", e.what());
		result["error"] = string("import_error_").append(e.what());
		return;
	}

	doKickUser(userid);
	result["error"] = 0;
	return;
}

void AdminManager::doQueryPay(const Json::Value &data, Json::Value &result) {
	if (!CheckSkey(data)) {
		result["error"] = -1;
		return;
	}
	uint32_t userid = 0;
	if (!Json::GetUInt(data, "uid", userid)) {
		error_log("[get uid error]");
		result["error"] = -1;
		return;
	}
	Player *player = PlayerManager::getInstance()->LoadForcePlayer(userid);
	if (player == NULL) {
		result["error"] = -1;
		return;
	}
	DataUserResource *pRc = player->getRm()->getResources();
	if (pRc != NULL) {
		result["r1"] = pRc->r1;
		result["r2"] = pRc->r2;
	}
	DataPay *pPay = player->getRm()->getPay();
	if (pPay != NULL) {
		result["cash"] = pPay->cash;
	}
	result["error"] = 0;
	return;
}

void AdminManager::doModifyPay(const Json::Value &data, Json::Value &result) {
	if (!CheckSkey(data)) {
		result["error"] = -1;
		return;
	}
	uint32_t userid = 0;
	if (!Json::GetUInt(data, "uid", userid)) {
		result["error"] = -1;
		return;
	}
	int cash, r1, r2;
	if (!Json::GetInt(data, "cash", cash) || !Json::GetInt(data, "r1", r1) || !Json::GetInt(data, "r2", r2)) {
		result["error"] = -1;
		return;
	}

	Player *player = PlayerManager::getInstance()->LoadForcePlayer(userid);
	if (player == NULL) {
		result["error"] = -1;
		return;
	}
	if (cash != 0) {
		player->getRm()->upCash(cash, "ADMINOP");
	}
	if (r1 != 0) {
		player->getRm()->upR1(r1, "ADMINOP");
	}
	if (r2 != 0) {
		player->getRm()->upR2(r2, "ADMINOP");
	}
	result["r1"] = player->getRm()->getResources()->r1;
	result["r2"] = player->getRm()->getResources()->r2;
	result["cash"] = player->getRm()->getPay()->cash;
	result["error"] = 0;
	return;
}

void AdminManager::doEmail(const Json::Value &data, Json::Value &result) {
	if (!CheckSkey(data)) {
		result["error"] = -1;
		return;
	}
	uint32_t userid = 0;
	if (!Json::GetUInt(data, "uid", userid)) {
		result["error"] = -1;
		return;
	}
	string titleStr = "";
	if (!Json::GetString(data, "title", titleStr)) {
		result["error"] = -1;
		return;
	}
	string contentStr = "";
	if (!Json::GetString(data, "content", contentStr)) {
		result["error"] = -1;
		return;
	}
	string attatch = "";
	Json::GetString(data, "attatch", attatch);

	Player * player = PlayerManager::getInstance()->LoadForcePlayer(userid);
	if (player == NULL) {
		result["error"] = -1;
		return;
	}

	player->getEmailManager()->addEmail(userid, titleStr, contentStr, attatch);

	result["error"] = 0;
	return;
}

void AdminManager::doCharge(const Json::Value &data, Json::Value &result) {
	if (!CheckSkey(data)) {
		result["error"] = -1;
		return;
	}
	uint32_t userid = 0;
	if (!Json::GetUInt(data, "uid", userid) || !IS_VALID_PLAYER_UID(userid)) {
		result["error"] = -1;
		return;
	}
	uint32_t cash = 0;
	if (!Json::GetUInt(data, "cash", cash)) {
		result["error"] = -1;
		return;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(userid);
	if (player == NULL) {
		result["error"] = -1;
		return;
	}
	const PayItem *cfg = PayConfig::getInstance()->getItem(cash);
	if (cfg == NULL) {
		result["error"] = -1;
		return;
	}
	MoneyCost cost;
	if (cfg->type == PayTypeDiamond) {
		cost.cash = cfg->gift;
		player->getRm()->addMoney(cost, "ADMINOP");
	}
	BuyGoodsManager::getInstance()->doAdminCharge(userid, cost.cash, cash);
	result["error"] = 0;
	return;
}

void AdminManager::doQueryFriend(const Json::Value &data, Json::Value &result) {
	uint32_t userid = 0;
	if (!Json::GetUInt(data, "uid", userid) || !IS_VALID_PLAYER_UID(userid)) {
		result["error"] = -1;
		return;
	}

	Player *player = PlayerManager::getInstance()->LoadExistPlayer(userid);
	if (player == NULL) {
		result["error"] = -1;
		return;
	}
	const vector<DataSocial> &friends = player->getSocialManager()->getData();
	result["list"] = Json::Value(Json::arrayValue);
	CDataUser dbUser;
	for (vector<DataSocial>::const_iterator itr = friends.begin(); itr != friends.end(); ++itr) {
		DataUser user;
		if (0 == dbUser.GetUser(itr->other_uid, user)) {
			Json::Value item;
			item["uid"] = user.uid;
			item["name"] = user.name;
			item["lv"] = user.level;
			item["vip"] = user.viplevel;

			result["list"].append(item);
		}
	}
	result["error"] = 0;

	return;
}

void AdminManager::doAddFriend(const Json::Value &data, Json::Value &result) {
	uint32_t userid = 0;
	if (!Json::GetUInt(data, "uid", userid) || !IS_VALID_PLAYER_UID(userid)) {
		result["error"] = "uid_error";
		return;
	}
	uint32_t friendUid = 0;
	if (!Json::GetUInt(data, "fuid", friendUid) || !IS_VALID_PLAYER_UID(friendUid)) {
		result["error"] = "fuid_error";
		return;
	}

	if (userid == friendUid) {
		result["error"] = "uid_and_fuid_is_same";
		return;
	}

	Player *player = PlayerManager::getInstance()->LoadExistPlayer(userid);
	if (player == NULL) {
		result["error"] = "load_player_error";
		return;
	}

	if (!player->getSocialManager()->onAccept(friendUid, "")) {
		result["error"] = "player_accept_error";
		return;
	}

	Player *accepter = PlayerManager::getInstance()->LoadForcePlayer(friendUid);
	if (accepter) {
		accepter->getUserInfo().invite_by = userid;
	}

	result["error"] = 0;
}

void AdminManager::doQueryEquip(const Json::Value &data, Json::Value &result) {
	uint32_t userid = 0;
	Json::GetUInt(data, "uid", userid);
	if (!exportEquipment(userid, result["list"])) {
		result["error"] = -1;
		return;
	}
	result["error"] = 0;
	return;
}

void AdminManager::doAddEquip(const Json::Value &data, Json::Value &result) {
	uint32_t userid = 0;
	Json::GetUInt(data, "uid", userid);
	uint32_t equipId = 0;
	Json::GetUInt(data, "id", equipId);
	uint32_t equipCount = 0;
	Json::GetUInt(data, "count", equipCount);

	Player * player = PlayerManager::getInstance()->LoadExistPlayer(userid);
	if (!player) {
		result["error"] = -1;
		return;
	}

	EquipmentManager * pEm = player->getEm();
	if (!pEm) {
		result["error"] = -1;
		return;
	}
	if (!pEm->addBagItem(equipId, equipCount, "admin")) {
		result["error"] = -1;
		return;
	}
	result["error"] = 0;
}

void AdminManager::doBlockUser(const Json::Value &data, Json::Value &result) {
	uint32_t userid = 0;
	Json::GetUInt(data, "uid", userid);
	uint32_t ts = 0;
	Json::GetUInt(data, "ts", ts);
	if (!IS_VALID_PLAYER_UID(userid)) {
		result["error"] = "uid_error";
		return;
	}
	Player *player = PlayerManager::getInstance()->LoadForcePlayer(userid);
	if (!player) {
		result["error"] = "load_user_error";
		return;
	}
	player->getUserInfo().block_time = ts;
	player->savePlayerUserInfo();
	if (ts > Time::GetGlobalTime()) {
		doKickUser(userid);
	}
	result["error"] = 0;
}

bool AdminManager::InitAdminInfo() {
	static time_t lastMTime = 0;
	string adminFile = Config::GetValue("admin_list");
	if (adminFile.empty()) {
		return false;
	}
	struct stat st;
	if (stat(adminFile.c_str(), &st) != 0) {
		return false;
	}
	if (lastMTime != st.st_mtime) {
		FILE *fp = fopen(adminFile.c_str(), "r");
		if (!fp) {
			return false;
		}
		char line[256];
		char *pch, *name, *pwd, *level;
		while (fgets(line, sizeof(line), fp) != NULL) {
			name = pwd = level = NULL;
			pch = line;
			while (*pch == ' ' || *pch == '\t')
				pch++;
			name = pch;
			while (*pch != '\0' && *pch != '\r' && *pch != '\n' && *pch != ' ' && *pch != '\t')
				pch++;
			if (*pch == '\0' || *pch == '\r' || *pch == '\n')
				continue;
			*pch++ = '\0';
			while (*pch == ' ' || *pch == '\t')
				pch++;
			pwd = pch;
			while (*pch != '\0' && *pch != '\r' && *pch != '\n' && *pch != ' ' && *pch != '\t')
				pch++;
			if (*pch == '\0' || *pch == '\r' || *pch == '\n')
				continue;
			*pch++ = '\0';
			while (*pch == ' ' || *pch == '\t')
				pch++;
			level = pch;
			while (*pch != '\0' && *pch != '\r' && *pch != '\n' && *pch != ' ' && *pch != '\t')
				pch++;
			if (*pch != '\0')
				*pch = '\0';

			AdminInfo info;
			info.pwd = pwd;
			info.level = atoi(level);
			m_adminInfo[string(name)] = info;
		}
		lastMTime = st.st_mtime;
	}
	return true;
}
bool AdminManager::CheckSkey(const Json::Value &data) {
	return true;

	string userName;
	if (!Json::GetString(data, "username", userName)) {
		error_log("[get username error]");
		return false;
	}
	uint32_t skey;
	if (!Json::GetUInt(data, "skey", skey)) {
		error_log("[get skey error]");
		return false;
	}
	map<string, AdminInfo>::iterator it = m_adminInfo.find(userName);
	if (it == m_adminInfo.end()) {
		error_log("[get username error]");
		return false;
	}
	if (it->second.skey != skey) {
		error_log("[skey error][server=%u,client=%u]", it->second.skey, skey);
		return false;
	}
	return true;
}

bool AdminManager::exportSoldier(uint32_t uid, Json::Value &result) {
	int ret = 0;
	Json::Reader reader;
	CDataSoldier dbSoldier;
	map<unsigned, string> soldierData;
	ret = dbSoldier.GetSoldier(uid, soldierData);
	if (ret != 0 && ret != R_ERR_NO_DATA) {
		error_log("GetSoldier error uid=%u ret=%d", uid, ret);
		return false;
	}
	result = Json::Value(Json::arrayValue);
	map<uint32_t, string>::const_iterator itr = soldierData.begin();
	for (; itr != soldierData.end(); ++itr) {
		Json::Value temp;
		if (reader.parse(itr->second, temp)) {
			result.append(temp);
		}
	}
	return true;
}
bool AdminManager::exportEquipment(uint32_t uid, Json::Value &result) {
	int ret = 0;
	Json::Reader reader;
	CDataEquipment dbEquipment;
	map<uint32_t, string> equipData;
	ret = dbEquipment.GetEquipment(uid, equipData);
	if (ret != 0 && ret != R_ERR_NO_DATA) {
		error_log("GetEquipment error uid=%u ret=%d", uid, ret);
		return false;
	}
	result = Json::Value(Json::arrayValue);
	map<uint32_t, string>::const_iterator itr = equipData.begin();
	for (; itr != equipData.end(); ++itr) {
		Json::Value temp;
		if (reader.parse(itr->second, temp)) {
			result.append(temp);
		}
	}
	return true;
}
bool AdminManager::exportBuilding(uint32_t uid, Json::Value &result) {
	int ret = 0;
	Json::Reader reader;
	CDataBuilding dbBuilding;
	map<unsigned, string> buildingData;
	ret = dbBuilding.GetBuilding(uid, buildingData);
	if (ret != 0 && ret != R_ERR_NO_DATA) {
		error_log("GetBuilding error uid=%u ret=%d", uid, ret);
		return false;
	}
	result = Json::Value(Json::arrayValue);
	map<uint32_t, string>::const_iterator itr = buildingData.begin();
	for (; itr != buildingData.end(); ++itr) {
		Json::Value temp;
		if (reader.parse(itr->second, temp)) {
			result.append(temp);
		}
	}
	return true;
}
bool AdminManager::exportResource(uint32_t uid, Json::Value &result) {
	int ret = 0;
	DataUserResource res;
	CDataUserResource dbRes;
	ret = dbRes.Get(uid, res);
	if (ret != 0) {
		error_log("GetUserResource error uid=%u ret=%d", uid, ret);
		return false;
	}
	result = Json::Value(Json::arrayValue);
	result.append(res.r1);
	result.append(res.r2);
	result.append(res.r3);
	result.append(res.r4);
	result.append(res.tl);
	result.append(res.p1);
	result.append(res.p2);
	result.append(res.p3);

	return true;
}
bool AdminManager::exportUser(uint32_t uid, Json::Value &result) {
	int ret = 0;
	DataUser user;
	CDataUser dbUser;
	ret = dbUser.GetUser(uid, user);
	if (ret != 0) {
		error_log("GetUser error uid=%u ret=%d", uid, ret);
		return false;
	}
	result["exp"] = user.exp;
	result["acc"] = user.total_charge;
	result["tutorial"] = user.tutorial_stage;
	result["protected"] = user.protected_time;
	result["fcharge"] = user.first_charge_reward;
	result["dc"] = user.defend_num;

	return true;
}
bool AdminManager::exportTask(uint32_t uid, Json::Value &result) {
	int ret = 0;
	vector<DataTask> tasks;
	CDataTask dbTask;
	ret = dbTask.GetTasks(uid, tasks);
	if (ret != 0 && ret != R_ERR_NO_DATA) {
		error_log("GetTasks error uid=%u ret=%d", uid, ret);
		return false;
	}
	result = Json::Value(Json::arrayValue);
	vector<DataTask>::const_iterator itr = tasks.begin();
	for (; itr != tasks.end(); ++itr) {
		Json::Value temp;
		temp["id"] = itr->id;
		temp["s"] = itr->status;
		temp["t"] = itr->type;
		temp["c"] = itr->curr;
		result.append(temp);
	}

	return true;
}
bool AdminManager::exportPreTask(uint32_t uid, Json::Value &result) {
	result = Json::Value(Json::arrayValue);
	CDataPreTask dbPreTask;
	vector<uint32_t> ids;
	int ret = dbPreTask.getPreTasks(uid, ids);
	if (ret != 0 && ret != R_ERR_NO_DATA) {
		error_log("getPreTasks error ret=%d uid=%u", ret, uid);
		return false;
	}
	vector<uint32_t>::const_iterator itr = ids.begin();
	for (; itr != ids.end(); ++itr) {
		result.append(*itr);
	}
	return true;
}
bool AdminManager::exportGate(uint32_t uid, Json::Value &result) {
	int ret = 0;
	vector<DataBattleGate> gates;
	CDataBattleGate dbGate;
	ret = dbGate.Get(uid, gates);
	if (ret != 0 && ret != R_ERR_NO_DATA) {
		error_log("GetGate error uid=%u ret=%d", uid, ret);
		return false;
	}
	result = Json::Value(Json::arrayValue);
	vector<DataBattleGate>::const_iterator itr = gates.begin();
	for (; itr != gates.end(); ++itr) {
		Json::Value temp;
		temp["id"] = itr->level;
		temp["star"] = static_cast<uint32_t>(itr->star);
		temp["sc"] = itr->score;
		temp["r"] = itr->res;
		result.append(temp);
	}
	return true;
}

bool AdminManager::exportState(uint32_t uid, Json::Value &result) {
	int ret = 0;
	CDataState dbState;
	vector<DataState> datas;
	ret = dbState.GetStates(uid, datas);
	if (ret != 0 && ret != R_ERR_NO_DATA) {
		error_log("GetStates error,ret=%d uid=%u", ret, uid);
		return false;
	}
	result = Json::Value(Json::arrayValue);
	vector<DataState>::const_iterator itr = datas.begin();
	for (; itr != datas.end(); ++itr) {
		Json::Value state;
		state["id"] = itr->id;
		state["data"] = itr->data;
		result.append(state);
	}
	return true;
}

bool AdminManager::exportHero(uint32_t uid, Json::Value &result) {
	int ret = 0;
	Json::Reader reader;
	CDataHero dbHero;
	map<unsigned, string> heroData;
	ret = dbHero.GetHero(uid, heroData);
	if (ret != 0 && ret != R_ERR_NO_DATA) {
		error_log("GetSoldier error uid=%u ret=%d", uid, ret);
		return false;
	}
	result = Json::Value(Json::arrayValue);
	map<uint32_t, string>::const_iterator itr = heroData.begin();
	for (; itr != heroData.end(); ++itr) {
		Json::Value temp;
		if (reader.parse(itr->second, temp)) {
			result.append(temp);
		}
	}
	return true;
}

bool AdminManager::exportTroops(uint32_t uid, Json::Value &result) {
	Json::Reader reader;
	CDataTroops dbTroops;
	map<uint32_t, string> data;
	int ret = dbTroops.GetTroops(uid, data);
	if (ret != 0 && ret != R_ERR_NO_DATA) {
		error_log("GetTroops error uid=%u ret=%d", uid, ret);
		return false;
	}
	result = Json::Value(Json::objectValue);
	map<uint32_t, string>::const_iterator itr = data.begin();
	for (; itr != data.end(); ++itr) {
		if (itr->first != TroopsManager::e_TROOPS_TYPE_ATTACK) {
			continue;
		}
		Json::Value temp;
		string key = CTrans::ITOS(itr->first);
		if (reader.parse(itr->second, temp)) {
			result[key] = temp;
		}
	}
	Json::Value jGuard = Json::Value(Json::arrayValue);
	CDataGuard dbGuard;
	vector<DataGuard> guards;
	dbGuard.Get(uid, guards);
	vector<DataGuard>::iterator it = guards.begin();
	for (; it != guards.end(); ++it) {
		Json::Value temp;
		temp["id"] = it->soldier;
		temp["v"] = it->id;
		jGuard.append(temp);
	}
	string key = CTrans::ITOS(TroopsManager::e_TROOPS_TYPE_DEFEND);
	result[key] = jGuard;
	return true;
}

bool AdminManager::exportSkill(uint32_t uid, Json::Value &result) {
	Json::Reader reader;
	CDataSkill dbSkill;
	vector<DataSkill> data;
	int ret = dbSkill.GetSkills(uid, data);
	if (ret != 0 && ret != R_ERR_NO_DATA) {
		error_log("GetSkills error uid=%u ret=%d", uid, ret);
		return false;
	}
	result = Json::Value(Json::arrayValue);
	vector<DataSkill>::const_iterator itr = data.begin();
	for (; itr != data.end(); ++itr) {
		Json::Value temp;
		temp["id"] = itr->skillId;
		temp["l"] = itr->level;
		temp["ts"] = itr->lastUpTime;
		temp["c"] = itr->count;
		temp["s"] = static_cast<uint32_t>(itr->status);
		result.append(temp);
	}
	return true;
}

bool AdminManager::exportDefend(uint32_t uid, Json::Value &result) {
	Json::Reader reader;
	CDataDefend dbDefend;
	vector<DataDefend> data;
	int ret = dbDefend.Get(uid, data);
	if (ret != 0 && ret != R_ERR_NO_DATA) {
		error_log("getDefends error uid=%u ret=%d", uid, ret);
		return false;
	}
	result = Json::Value(Json::arrayValue);
	vector<DataDefend>::const_iterator itr = data.begin();
	for (; itr != data.end(); ++itr) {
		Json::Value temp;
		temp["id"] = itr->level;
		temp["s"] = static_cast<uint32_t>(itr->star);
		result.append(temp);
	}
	return true;
}

bool AdminManager::exportTower(uint32_t uid, Json::Value &result) {
	Json::Reader reader;
	CDataTower dbTower;
	vector<DataTower> data;
	int ret = dbTower.GetTowers(uid, data);
	if (ret != 0 && ret != R_ERR_NO_DATA) {
		error_log("GetTowers error uid=%u ret=%d", uid, ret);
		return false;
	}
	result = Json::Value(Json::arrayValue);
	vector<DataTower>::const_iterator itr = data.begin();
	for (; itr != data.end(); ++itr) {
		Json::Value temp;
		temp["id"] = itr->id;
		temp["lv"] = itr->level;
		result.append(temp);
	}
	return true;
}

bool AdminManager::exportActiveness(uint32_t uid, Json::Value &result) {
	int ret = 0;
	DataUser user;
	CDataUser dbUser;
	ret = dbUser.GetUser(uid, user);
	if (ret != 0) {
		error_log("GetUser error uid=%u ret=%d", uid, ret);
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadForcePlayer(uid);
	if (player == NULL) {
		return false;
	}
	result["score"] = player->getActivenessManager()->getScore();
	return true;
}

bool AdminManager::exportBoat(uint32_t uid, Json::Value &result) {
	result = Json::Value(Json::arrayValue);
	CDataBoatTrain dbc;
	vector<DataBoatTrain> datas;
	dbc.Get(uid, datas);
	vector<DataBoatTrain>::iterator itr = datas.begin();
	for (; itr != datas.end(); ++itr) {
		Json::Value item;
		item["id"] = static_cast<uint32_t>(itr->id);
		item["first"] = static_cast<uint32_t>(itr->first);
		item["sts"] = itr->start_ts;
		item["ets"] = itr->end_ts;
		item["tres"] = itr->total_res;
		item["lres"] = itr->lost_res;
		item["u"] = static_cast<uint32_t>(itr->used_count);
		result.append(item);
	}
	return true;
}

bool AdminManager::exportActivity(uint32_t uid, Json::Value &result) {
	result = Json::Value(Json::arrayValue);
	CDataActivity dbc;
	vector<DataActivity> datas;
	dbc.Get(uid, datas);
	vector<DataActivity>::iterator itr = datas.begin();
	for (; itr != datas.end(); ++itr) {
		Json::Value item;
		item["id"] = itr->id;
		item["v"] = itr->ver;
		item["ts"] = itr->ts;
		item["s"] = itr->score;
		item["f"] = itr->flag;
		result.append(item);
	}
	return true;
}

bool AdminManager::exportChargeHistory(uint32_t uid, Json::Value &result) {
	result = Json::Value(Json::arrayValue);
	CDataChargeHistory dbc;
	vector<DataChargeHistory> datas;
	dbc.Get(uid, datas);
	vector<DataChargeHistory>::iterator itr = datas.begin();
	for (; itr != datas.end(); ++itr) {
		Json::Value item;
		item["ts"] = itr->ts;
		item["cash"] = itr->cash;
		item["cost"] = itr->cost;
		result.append(item);
	}
	return true;
}

bool AdminManager::exportGem(uint32_t uid, Json::Value &result) {
	result = Json::Value(Json::arrayValue);
	CDataGemPoint dbc;
	vector<DataGemPoint> datas;
	dbc.Get(uid, datas);
	vector<DataGemPoint>::iterator itr = datas.begin();
	for (; itr != datas.end(); ++itr) {
		Json::Value item;
		item["id"] = itr->id;
		item["points"] = Json::Value(Json::arrayValue);
		item["points"].append(itr->p1);
		item["points"].append(itr->p2);
		item["points"].append(itr->p3);
		item["points"].append(itr->p4);
		result.append(item);
	}
	return true;
}

bool AdminManager::importSoldier(uint32_t uid, const Json::Value &result) {
	if (result.isNull() || !result.isArray()) {
		return false;
	}
	int ret = 0;
	CDataSoldier dbSoldier;
	ret = dbSoldier.RemoveSoldier(uid);
	if (ret != 0) {
		error_log("RemoveSoldier error uid=%u ret=%d", uid, ret);
		return false;
	}
	for (size_t i = 0; i < result.size(); ++i) {
		unsigned ud = 0;
		if (!Json::GetUInt(result[i], "ud", ud)) {
			continue;
		}
		ret = dbSoldier.AddSoldier(uid, ud, Json::ToString(result[i]));
		if (ret != 0) {
			error_log("AddSoldier error uid=%u ud=%u ret=%d", uid, ud, ret);
			return false;
		}
	}
	return true;
}
bool AdminManager::importEquipment(uint32_t uid, const Json::Value &result) {
	if (result.isNull() || !result.isArray()) {
		return false;
	}

	int ret = 0;
	CDataEquipment dbEquipment;
	ret = dbEquipment.RemoveEquipment(uid);
	if (ret != 0) {
		error_log("RemoveEquipment error uid=%u ret=%d", uid, ret);
		return false;
	}
	for (size_t i = 0; i < result.size(); ++i) {
		unsigned ud = 0;
		if (!Json::GetUInt(result[i], "ud", ud)) {
			continue;
		}
		ret = dbEquipment.AddEquipment(uid, ud, Json::ToString(result[i]));
		if (ret != 0) {
			error_log("AddEquipment error uid=%u ud=%u ret=%d", uid, ud, ret);
			return false;
		}
	}
	return true;
}
bool AdminManager::importBuilding(uint32_t uid, const Json::Value &result) {
	if (result.isNull() || !result.isArray()) {
		return false;
	}
	int ret = 0;
	CDataBuilding dbBuilding;
	ret = dbBuilding.RemoveBuilding(uid);
	if (ret != 0) {
		error_log("RemoveBuilding error uid=%u ret=%d", uid, ret);
		return false;
	}
	for (size_t i = 0; i < result.size(); ++i) {
		uint32_t ud = 0;
		if (!Json::GetUInt(result[i], "ud", ud)) {
			continue;
		}
		ret = dbBuilding.AddBuilding(uid, ud, Json::ToString(result[i]));
		if (ret) {
			error_log("AddBuilding error uid=%u ud=%u ret=%d", uid, ud, ret);
			return false;
		}
	}

	return true;
}
bool AdminManager::importResource(uint32_t uid, const Json::Value &result) {
	if (result.isNull() || !result.isArray() || result.size() < 5) {
		return false;
	}
	int ret = 0;
	DataUserResource res;
	CDataUserResource dbRes;
	ret = dbRes.Get(uid, res);
	if (ret != 0) {
		error_log("GetUserResource error uid=%u ret=%d", uid, ret);
		return false;
	}
	res.r1 = result[0u].asUInt();
	res.r2 = result[1u].asUInt();
	res.r3 = result[2u].asUInt();
	res.r4 = result[3u].asUInt();
	res.tl = result[4u].asUInt();
	res.p1 = result[5u].asUInt();
	res.p2 = result[6u].asUInt();
	res.p3 = result.get(7u, 0).asUInt();
	ret = dbRes.Set(res);
	if (ret != 0) {
		error_log("SetUserResource error uid=%u ret=%d", uid, ret);
		return false;
	}

	return true;
}
bool AdminManager::importUser(uint32_t uid, const Json::Value &result) {
	int ret = 0;
	DataUser user;
	CDataUser dbUser;
	ret = dbUser.GetUser(uid, user);
	if (ret != 0) {
		error_log("GetUser error uid=%u ret=%d", uid, ret);
		return false;
	}
	bool needSave = false;
	if (result.isMember("exp")) {
		user.exp = result["exp"].asUInt();
		user.level = ExpConfig::getInstance()->getNextUserLevel(user.exp);
		needSave = true;
	}
	if (result.isMember("acc")) {
		user.total_charge = result["acc"].asUInt();
		needSave = true;
	}
	if (result.isMember("tutorial")) {
		user.tutorial_stage = result["tutorial"].asUInt();
		needSave = true;
	}
	if (result.isMember("protected")) {
		user.protected_time = result["protected"].asUInt();
		needSave = true;
	}
	if (result.isMember("fcharge")) {
		user.first_charge_reward = result["fcharge"].asUInt();
		needSave = true;
	}
	if (result.isMember("dc")) {
		user.defend_num = result["dc"].asUInt();
		needSave = true;
	}
	if (needSave) {
		ret = dbUser.SetUser(user);
		if (ret != 0) {
			error_log("SetUser error uid=%u ret=%d", uid, ret);
			return false;
		}
	}
	return true;
}
bool AdminManager::importTask(uint32_t uid, const Json::Value &result) {
	if (result.isNull() || !result.isArray()) {
		return false;
	}
	int ret = 0;
	CDataTask dbTask;
	ret = dbTask.DelTasks(uid);
	if (ret != 0) {
		error_log("RemoveTasks error uid=%u ret=%d", uid, ret);
		return false;
	}
	for (size_t i = 0; i < result.size(); ++i) {
		DataTask task;
		task.uid = uid;
		Json::GetUInt(result[i], "id", task.id);
		Json::GetUInt(result[i], "c", task.curr);
		uint32_t status = 0;
		Json::GetUInt(result[i], "s", status);
		task.status = status;
		uint32_t type = 0;
		Json::GetUInt(result[i], "t", type);
		task.type = type;
		ret = dbTask.AddTask(task);
		if (ret != 0) {
			error_log("AddTask failed uid=%u id=%u ret=%d", uid, task.id, ret);
		}
	}

	return true;
}
bool AdminManager::importPreTask(uint32_t uid, const Json::Value &result) {
	if (result.isNull() || !result.isArray()) {
		return false;
	}
	int ret = 0;
	CDataPreTask dbPreTask;
	ret = dbPreTask.delPreTask(uid);
	if (ret != 0) {
		error_log("delPreTask error ret=%d uid=%u", ret, uid);
		return false;
	}
	for (size_t i = 0; i < result.size(); ++i) {
		ret = dbPreTask.addPreTask(uid, result[i].asUInt());
		if (ret != 0) {
			error_log("addPreTask error ret=%d uid=%u id=%u", ret, uid, result[i].asUInt());
			return false;
		}
	}
	return true;
}
bool AdminManager::importGate(uint32_t uid, const Json::Value &result) {
	if (result.isNull() || !result.isArray()) {
		return false;
	}
	int ret = 0;
	CDataBattleGate dbGate;
	ret = dbGate.Del(uid);
	if (ret != 0) {
		error_log("RemoveGate error uid=%u ret=%d", uid, ret);
		return false;
	}
	for (size_t i = 0; i < result.size(); ++i) {
		DataBattleGate gate;
		gate.uid = uid;
		gate.star = result[i].get("star", 0).asUInt();
		Json::GetUInt(result[i], "id", gate.level);
		Json::GetUInt(result[i], "sc", gate.score);
		Json::GetUInt(result[i], "r", gate.res);
		ret = dbGate.Add(gate);
		if (ret != 0) {
			error_log("AddGate error uid=%u level=%u ret=%d", uid, gate.level, ret);
		}
	}
	return true;
}
bool AdminManager::importState(uint32_t uid, const Json::Value &result) {
	int ret = 0;
	if (result.isNull() || !result.isArray()) {
		return false;
	}

	CDataState dbState;
	for (size_t i = 0; i < result.size(); ++i) {
		DataState sData;
		sData.uid = uid;
		sData.id = 0;
		if (!Json::GetUInt(result[i], "id", sData.id)) {
			continue;
		}
		if (!Json::GetString(result[i], "data", sData.data)) {
			continue;
		}
		ret = dbState.ReplaceState(sData);
		if (ret) {
			return false;
		}
	}

	return true;
}

bool AdminManager::importHero(uint32_t uid, const Json::Value &result) {
	if (result.isNull() || !result.isArray()) {
		return true;
	}
	int ret = 0;
	CDataHero dbHero;
	ret = dbHero.RemoveHero(uid);
	if (ret != 0) {
		error_log("RemoveHero error uid=%u ret=%d", uid, ret);
		return false;
	}
	for (size_t i = 0; i < result.size(); ++i) {
		unsigned ud = 0;
		if (!Json::GetUInt(result[i], "ud", ud)) {
			continue;
		}
		ret = dbHero.AddHero(uid, ud, Json::ToString(result[i]));
		if (ret != 0) {
			error_log("AddSoldier error uid=%u ud=%u ret=%d", uid, ud, ret);
			return false;
		}

	}
	return true;
}

bool AdminManager::importTroops(uint32_t uid, Json::Value &result) {
	if (result.isNull() || !result.isObject()) {
		return true;
	}
	CDataTroops dbTroops;
	CDataGuard dbGuard;
	int ret = 0;
	ret = dbTroops.RemoveTroops(uid);
	if (ret != 0) {
		error_log("RemoveTroops error uid=%u ret=%d", uid, ret);
		return false;
	}
	Json::Value::Members mem = result.getMemberNames();
	for (Json::Value::Members::iterator itr = mem.begin(); itr != mem.end(); ++itr) {
		uint32_t ud = CTrans::STOI(*itr);
		if (ud == TroopsManager::e_TROOPS_TYPE_ATTACK) {
			ret = dbTroops.AddTroops(uid, ud, Json::ToString(result[*itr]));
			if (ret != 0) {
				error_log("AddTroops error uid=%u ud=%u ret=%d", uid, ud, ret);
				return false;
			}
		} else if (ud == TroopsManager::e_TROOPS_TYPE_DEFEND) {
			dbGuard.Del(uid, 0);
			const Json::Value &jGuard = result[*itr];
			for (size_t i = 0; i < jGuard.size(); ++i) {
				DataGuard guard;
				guard.uid = uid;
				guard.id = jGuard[i].get("v", 0).asUInt();
				guard.soldier = jGuard[i].get("id", 0).asUInt();
				if (guard.id == 0 || guard.soldier == 0) {
					continue;
				}
				dbGuard.Add(guard);
			}
		}
	}
	return true;
}
bool AdminManager::importSkill(uint32_t uid, Json::Value &result) {
	if (result.isNull() || !result.isArray()) {
		return true;
	}
	int ret = 0;
	CDataSkill dbSkill;
	ret = dbSkill.RemoveSkill(uid);
	if (0 != ret) {
		error_log("RemoveSkill error uid=%u ret=%d", uid, ret);
		return false;
	}
	for (size_t i = 0; i < result.size(); ++i) {
		DataSkill sk;
		sk.uid = uid;
		sk.skillId = result[i].get("id", 0).asUInt();
		sk.level = result[i].get("l", 0).asUInt();
		sk.lastUpTime = result[i].get("ts", 0).asUInt();
		sk.count = result[i].get("c", 0).asUInt();
		sk.status = result[i].get("s", 0).asUInt();
		ret = dbSkill.AddSkill(sk);
		if (0 != ret) {
			error_log("AddSkill error uid=%u ret=%d", uid, ret);
			return false;
		}
	}
	return true;
}

bool AdminManager::importDefend(uint32_t uid, Json::Value &result) {
	if (result.isNull() || !result.isArray()) {
		return true;
	}
	int ret = 0;
	CDataDefend dbDefend;
	ret = dbDefend.Del(uid);
	if (0 != ret) {
		error_log("delDefend error uid=%u ret=%d", uid, ret);
		return false;
	}
	for (size_t i = 0; i < result.size(); ++i) {
		DataDefend data;
		data.uid = uid;
		data.level = result[i]["id"].asUInt();
		data.star = result[i]["s"].asUInt();
		ret = dbDefend.Add(data);
		if (0 != ret) {
			error_log("addDefend error uid=%u ret=%d", uid, ret);
			return false;
		}
	}
	return true;
}

bool AdminManager::importTower(uint32_t uid, Json::Value &result) {
	if (result.isNull() || !result.isArray()) {
		return true;
	}
	int ret = 0;
	CDataTower dbTower;
	ret = dbTower.DelTower(uid);
	if (0 != ret) {
		error_log("DelTower error uid=%u ret=%d", uid, ret);
		return false;
	}
	for (size_t i = 0; i < result.size(); ++i) {
		DataTower data;
		data.uid = uid;
		data.id = result[i]["id"].asUInt();
		data.level = result[i]["lv"].asUInt();
		ret = dbTower.AddTower(data);
		if (0 != ret) {
			error_log("AddTower error uid=%u ret=%d", uid, ret);
			return false;
		}
	}
	return true;
}

bool AdminManager::importActiveness(uint32_t uid, Json::Value &result) {
	if (result.isNull()) {
		return true;
	}
	int ret = 0;
	DataUser user;
	CDataUser dbUser;
	ret = dbUser.GetUser(uid, user);
	if (ret != 0) {
		error_log("GetUser error uid=%u ret=%d", uid, ret);
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadForcePlayer(uid);
	if (player == NULL) {
		return false;
	}
	player->getActivenessManager()->setScore(result.get("score", 0).asUInt());
	return true;
}

bool AdminManager::importBoat(uint32_t uid, Json::Value &result) {
	if (result.isNull() || !result.isArray()) {
		return true;
	}
	CDataBoatTrain dbc;
	for (size_t i = 0; i < result.size(); ++i) {
		DataBoatTrain item;
		item.id = result[i].get("id", 0).asUInt();
		int ret = dbc.Get(uid, item.id, item);
		if (0 != ret) {
			continue;
		}
		item.first = result[i].get("first", 0).asUInt();
		item.start_ts = result[i].get("sts", 0).asUInt();
		item.end_ts = result[i].get("ets", 0).asUInt();
		item.total_res = result[i].get("tres", 0).asUInt();
		item.lost_res = result[i].get("lres", 0).asUInt();
		item.used_count = result[i].get("u", 0).asUInt();
		dbc.Set(item);
	}
	return true;
}

bool AdminManager::importActivity(uint32_t uid, Json::Value &result) {
	if (result.isNull() || !result.isArray()) {
		return true;
	}
	CDataActivity dbc;
	for (size_t i = 0; i < result.size(); ++i) {
		DataActivity item;
		item.uid = uid;
		item.id = result[i].get("id", 0).asUInt();
		item.ver = result[i].get("v", 0).asUInt();
		item.ts = result[i].get("ts", 0).asUInt();
		item.score = result[i].get("s", 0).asUInt();
		item.flag = result[i].get("f", 0).asUInt();
		dbc.Set(item);
	}
	return true;
}

bool AdminManager::importChargeHistory(uint32_t uid, Json::Value &result) {
	if (result.isNull() || !result.isArray()) {
		return true;
	}
	CDataChargeHistory dbc;
	dbc.Del(uid, 0);
	for (size_t i = 0; i < result.size(); ++i) {
		DataChargeHistory item;
		item.uid = uid;
		item.ts = result[i].get("ts", 0).asUInt();
		item.cash = result[i].get("cash", 0).asUInt();
		item.cost = result[i].get("cost", 0).asUInt();
		dbc.Add(item);
	}
	return true;
}

bool AdminManager::importGem(uint32_t uid, Json::Value &result) {
	if (result.isNull() || !result.isArray()) {
		return true;
	}
	CDataGemPoint dbc;
	DataGemPoint data;
	data.uid = uid;
	dbc.Del(data);
	for (size_t i = 0; i < result.size(); ++i) {
		DataGemPoint item;
		item.uid = uid;
		Json::GetUInt(result[i], "id", item.id);
		Json::GetUInt(result[i]["points"], 0u, item.p1);
		Json::GetUInt(result[i]["points"], 1u, item.p2);
		Json::GetUInt(result[i]["points"], 2u, item.p3);
		Json::GetUInt(result[i]["points"], 3u, item.p4);
		dbc.Add(item);
	}
	return true;
}

