#include "BoatManager.h"
#include "PlayerManager.h"
#include "BoatConfig.h"
#include "GiftBagConfig.h"
#include "NpcManager.h"
#include "SoldierConfig.h"
#include "SystemMessage.h"
#include "SkillConfig.h"
#include "AutoTransportManager.h"

BoatManager::BoatManager() {
	revenge_id = 0;
}
BoatManager::~BoatManager() {
}
bool BoatManager::doPacket(CNetPacket *packet) {
	switch (packet->subCmd) {
	case PROTOCOL_SUBCMD_MERCHANT_INFO:
		doSend();
		break;
	case PROTOCOL_SUBCMD_MERCHANT_START:
		doStart(packet);
		break;
	case PROTOCOL_SUBCMD_MERCHANT_BUY_COUNT:
		doBuyCount(packet);
		break;
	case PROTOCOL_SUBCMD_MERCHANT_REWARD:
		doReward(packet);
		break;
	case PROTOCOL_SUBCMD_MERCHANT_GET_TARGET:
		doGetTarget(packet);
		break;
	case PROTOCOL_SUBCMD_MERCHANT_GET_TARGET_COUNT:
		doGetTargetCount(packet);
		break;
	case PROTOCOL_SUBCMD_MERCHANT_ROB_RESULT:
		doRobResult(packet);
		break;
	case PROTOCOL_SUBCMD_MERCHANT_ROB_LOG:
		doGetLog(packet);
		break;
	case PROTOCOL_SUBCMD_MERCHANT_SPEED_UP:
		doSpeedUp(packet);
		break;
	case PROTOCOL_SUBCMD_MERCHANT_STAR:
		doStarReward(packet);
		break;
	case PROTOCOL_SUBCMD_MERCHANT_ASRV_TARGET:
		doAsrvTarget(packet);
		break;
	case PROTOCOL_SUBCMD_MERCHANT_TARGET_INFO_REQ:
		doTargetInfoReq(packet);
		break;
	case PROTOCOL_SUBCMD_MERCHANT_TARGET_INFO_RESP:
		doTargetInfoResp(packet);
		break;
	case PROTOCOL_SUBCMD_MERCHANT_REVENGE:
		doRevenge(packet);
		break;
	case PROTOCOL_SUBCMD_MERCHANT_ASRV_REVENGE:
		doAsrvRevenge(packet);
		break;
	case PROTOCOL_SUBCMD_MERCHANT_CASH_RESET:
		doCashReset(packet);
		break;
	case PROTOCOL_SUBCMD_MERCHANT_ROB_RES:
		doRobRes(packet);
		break;
	default:
		error_log("no process uid=%u subcmd=%u", packet->uid, static_cast<uint32_t>(packet->subCmd));
		break;
	}
	return true;
}
bool BoatManager::load(uint32_t uid) {
	int ret = 0;
	CDataBoat dbBoat;
	ret = dbBoat.Get(uid, m_boat);
	if (0 != ret && R_ERR_NO_DATA != ret) {
		error_log("get boat error uid=%u ret=%d", uid, ret);
		return false;
	}
	if (R_ERR_NO_DATA == ret) {
		m_boat.uid = uid;
		m_boat.reset_ts = 0;
		m_boat.refresh_count = 0;
		m_boat.speed_up = 0;
		m_boat.star = 0;
		m_boat.star_reward = 0;
		dbBoat.Add(m_boat);
	}

	CDataBoatTrain dbBoatTrain;
	vector<DataBoatTrain> trains;
	ret = dbBoatTrain.Get(uid, trains);
	if (0 == ret) {
		for (vector<DataBoatTrain>::iterator itr = trains.begin(); itr != trains.end(); ++itr) {
			m_train.insert(make_pair(itr->id, *itr));
		}
	}

	bool get_log = false;
	for (byte id = 1; id <= MAX_MERCHANT_NUM; ++id) {
		if (!m_train.count(id)) {
			DataBoatTrain item;
			item.id = id;
			item.uid = uid;
			m_train.insert(make_pair(id, item));
			dbBoatTrain.Add(item);
		}
		if (m_train[id].end_ts != 0) {
			get_log = true;
		}
	}

	if (get_log) {
		CDataBoatRobLog dbBoatRobLog;
		vector<DataBoatRobLog> rob_logs;
		dbBoatRobLog.GetLimit(uid, rob_logs);
		for (vector<DataBoatRobLog>::iterator itr = rob_logs.begin(); itr != rob_logs.end(); ++itr) {
			if (itr->type != BOAT_ROB_LOG_STATUS_DEF) {
				continue;
			}
			for (byte id = 1; id <= MAX_MERCHANT_NUM; ++id) {
				DataBoatTrain &item = m_train[id];
				if (itr->train_id == id && itr->ts > item.start_ts && itr->ts < item.end_ts) {
					vector<DataBoatRobLog> &rob_log = m_rob_log[id];
					rob_log.push_back(*itr);
				}
			}
		}
	}

	return true;
}
bool BoatManager::doReset() {
	if (CTime::GetDayInterval(m_boat.reset_ts, LogicManager::GlobalTime) == 0) {
		return false;
	}
	m_boat.reset_ts = LogicManager::GlobalTime;
	m_boat.refresh_count = 0;
	m_boat.speed_up = 0;
	m_boat.star = 0;
	m_boat.star_reward = 0;
	m_boat.reset_flag = 0;

	CDataBoatTrain dbBoatTrain;
	for (byte id = 1; id <= MAX_MERCHANT_NUM; ++id) {
		DataBoatTrain &item = m_train[id];
		if (item.used_count != 0) {
			item.used_count = 0;
		}
	}

	return true;
}
bool BoatManager::doSave() {
	int ret = 0;
	uint32_t uid = m_player->getUid();
	CDataBoat dbBoat;
	ret = dbBoat.Set(m_boat);
	if (0 != ret) {
		error_log("set baot error uid=%u ret=%d", uid, ret);
		return ret;
	}
	CDataBoatTrain dbBoatTrain;
	for (byte id = 1; id <= MAX_MERCHANT_NUM; ++id) {
		ret = dbBoatTrain.Set(m_train[id]);
		if (0 != ret) {
			error_log("set baot train error uid=%u ret=%d", uid, ret);
			return ret;
		}
	}
	return true;
}
bool BoatManager::doSend() {
	CNetPacket sPacket;
	sPacket.uid = m_player->getUid();
	CBufferWriter bWriter(&(sPacket.body));
	bWriter.AppendByte(PROTOCOL_CMD_BOAT);
	bWriter.AppendByte(PROTOCOL_SUBCMD_MERCHANT_INFO);
	bWriter.AppendByte(m_boat.speed_up);
	bWriter.AppendByte(m_boat.star);
	bWriter.AppendByte(m_boat.star_reward);
	bWriter.AppendByte(m_boat.reset_flag);

	bWriter.AppendUInt32(MAX_MERCHANT_NUM);
	for (byte id = 1; id <= MAX_MERCHANT_NUM; ++id) {
		DataBoatTrain &item = m_train[id];
		bWriter.AppendByte(item.id);
		bWriter.AppendByte(item.level);
		bWriter.AppendUInt32(item.end_ts);
		bWriter.AppendUInt32(item.used_count);
		vector<DataBoatRobLog> &rob_log = m_rob_log[id];
		bWriter.AppendUInt32(rob_log.size());
		vector<DataBoatRobLog>::iterator itr = rob_log.begin();
		for (; itr != rob_log.end(); ++itr) {
			bWriter.AppendUInt32(itr->ts);
			bWriter.AppendUInt32(itr->userid);
			bWriter.AppendUInt32(itr->res);
			bWriter.AppendString(itr->username);
			bWriter.AppendByte(0);
		}
	}

	PlayerManager::getInstance()->sendToAccess(&sPacket);

	return true;
}
bool BoatManager::onRob(uint32_t uid, uint32_t id, const string &name, uint32_t robRes, uint32_t &res) {
	if (id < 1 || id > MAX_MERCHANT_NUM) {
		error_log("boat train id error uid=%u,id=%u,rob=%u", m_player->getUid(), id, uid);
		return false;
	}
	DataBoatTrain &train = m_train[id];
	if (train.end_ts <= LogicManager::GlobalTime) {
		error_log("boat train is finish uid=%u,id=%u,rob=%u,endTs=%u", m_player->getUid(), id, uid, train.end_ts);
		return false;
	}

	res = caleRes(train.total_res, train.lost_res, robRes);
	if (robRes > 0 && res == 0) {
		error_log("not left res uid=%u,id=%u,rob=%u", m_player->getUid(), id, uid);
		return false;
	}
	train.lost_res += res;

	doSave();

	DataBoatRobLog rob;
	rob.uid = m_player->getUid();
	rob.userid = uid;
	rob.type = BOAT_ROB_LOG_STATUS_DEF;
	rob.res = res;
	rob.username = name;
	rob.ts = LogicManager::GlobalTime;

	vector<DataBoatRobLog> &rob_log = m_rob_log[id];
	rob_log.push_back(rob);

	if (id == MAX_MERCHANT_NUM) {
		AutoTransportManager::getInstance()->onRob(m_player->getUid(), res);
	}
	debug_log("uid=%u,id=%u,rob=%u,res=%u,damage=%u,totalRes=%u,lostRes=%u",
			m_player->getUid(), id, uid, res, robRes, train.total_res, train.lost_res);

	return true;
}
bool BoatManager::onRobByOther(uint32_t uid, uint32_t id, const string &name, uint32_t res, int32_t exp) {
	if (id < 1 || id > MAX_MERCHANT_NUM) {
		error_log("boat train id error uid=%u,id=%u,rob=%u", m_player->getUid(), id, uid);
		return false;
	}
	DataBoatTrain &train = m_train[id];
	if (train.end_ts <= LogicManager::GlobalTime) {
		error_log("boat train is finish uid=%u,id=%u,rob=%u,endTs=%u", m_player->getUid(), id, uid, train.end_ts);
		return false;
	}
	uint32_t real_res = caleRes(train.total_res, train.lost_res, res);
	if (res > 0 && real_res == 0) {
		error_log("not left res uid=%u,id=%u,rob=%u", m_player->getUid(), id, uid);
		return false;
	}
	train.lost_res += real_res;
	if (exp < 0) {
		exp *= 0.8;
	}
	m_player->upPlayerExp(exp, "rob_by_" + CTrans::ITOS(uid));
	m_player->getTaskManager()->onLostRes(real_res);

	DataBoatRobLog rob;
	rob.uid = m_player->getUid();
	rob.userid = uid;
	rob.type = BOAT_ROB_LOG_STATUS_DEF;
	rob.res = real_res;
	rob.username = name;
	rob.ts = LogicManager::GlobalTime;

	vector<DataBoatRobLog> &rob_log = m_rob_log[id];
	rob_log.push_back(rob);

	onRobNotice(m_player->getUid());

	if (res > 0) {
		CNetPacket asrvp;
		asrvp.uid = m_player->getUid();
		CBufferWriter writer(asrvp.GetBody());
		writer.AppendByte(PROTOCOL_CMD_TRANSPORT);
		writer.AppendByte(PROTOCOL_SUBCMD_TRANSPORT_ROB);
		writer.AppendByte(id);
		writer.AppendUInt32(m_player->getUid());
		writer.AppendUInt32(res);
		LogicManager::getInstance()->sendToAllServer(&asrvp);
	}

	debug_log("uid=%u,id=%u,rob=%u,res=%u,damage=%u,totalRes=%u,lostRes=%u",
			m_player->getUid(), id, uid, real_res, res, train.total_res, train.lost_res);

	return true;
}

bool BoatManager::onLogin() {
	asyncAutoTrain();
	if (doReset()) {
		doSave();
	}
	return true;
}
bool BoatManager::asyncAutoTrain() {
	uint32_t ets = 0;
	uint32_t res = 0;
	AutoTransportManager::getInstance()->getInfo(m_player->getUid(), ets, res);
	if (ets == 0) {
		return false;
	}
	uint32_t bts = ets - AUTO_TRANSPORT_TIME;
	DataBoatTrain &train = m_train[MAX_MERCHANT_NUM];
	train.end_ts = ets;
	train.start_ts = bts;
	train.total_res = res;
	vector<DataBoatRobLog> &rob_log = m_rob_log[MAX_MERCHANT_NUM];
	vector<DataBoatRobLog>::iterator itr = rob_log.begin();
	for (; itr != rob_log.end();) {
		if (itr->ts >= bts && itr->ts <= ets) {
			++itr;
			continue;
		} else {
			itr = rob_log.erase(itr);
		}
	}
	return true;
}
bool BoatManager::autoTrain(uint32_t ets, uint32_t res) {
	uint32_t bts = ets - AUTO_TRANSPORT_TIME;
	DataBoatTrain &train = m_train[MAX_MERCHANT_NUM];
	train.end_ts = ets;
	train.start_ts = bts;
	train.total_res = res;
	train.lost_res = 0;
	train.level = m_player->getLevel();
	vector<DataBoatRobLog> &rob_log = m_rob_log[MAX_MERCHANT_NUM];
	rob_log.clear();
	if (PlayerManager::getInstance()->IsOnline(m_player->getUid())) {
		doSave();
		doSend();
	}
	return true;
}
bool BoatManager::addRevengeCount() {
	if (revenge_id == 0) {
		return false;
	}
	CDataBoatRobLog dbc;
	byte count = 0;
	int ret = dbc.GetRevengeCount(m_player->getUid(), revenge_id, count);
	if (ret != 0) {
		return false;
	}
	count += 1;
	dbc.SetRevengeCount(m_player->getUid(), revenge_id, count);
	return true;
}
bool BoatManager::doStart(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CBoatStartProtocol protocol;
	if (!protocol.Decode(&(packet->body))) {
		error_log("Decode error uid=%u", uid);
		onStartResp(uid, PROCESS_RET_FAIL);
		return false;
	}

	uint32_t id = protocol.id;

	if (id < 1 || id > MAX_MERCHANT_NUM) {
		error_log("id error uid=%u id=%u", uid, id);
		onStartResp(uid, PROCESS_RET_FAIL);
		return false;
	}

	doReset();

	uint32_t boatCost = CBoatConfig::getInstance()->getCost(id, m_player->getLevel());
	ResourceCost cost;
	cost.r2 = boatCost;

	if (!m_player->getRm()->useResources(cost, "merchant_train")) {
		error_log("useResources error uid=%u", uid);
		onStartResp(uid, PROCESS_RET_FAIL);
		return false;
	}

	DataBoatTrain &train = m_train[id];
	if (train.end_ts != 0) {
		error_log("endTs error uid=%u id=%u", uid, id);
		onStartResp(uid, PROCESS_RET_FAIL);
		return false;
	}
	uint32_t maxCount = CBoatConfig::getInstance()->getCount(id);
	if (id == 3) {
		maxCount += m_player->getVipManager()->getRight(VipManager::VIP_RIGHT_BOAT_TIMES);
	}
	if (train.used_count >= maxCount) {
		error_log("usedCount error uid=%u id=%u use=%u max=%u", uid, id, train.used_count, maxCount);
		onStartResp(uid, PROCESS_RET_FAIL);
		return false;
	}

	train.id = id;
	if (train.first == 0 && id == 1) {
		train.first = 1;
		train.end_ts = LogicManager::GlobalTime + 3;
	} else {
		train.end_ts = LogicManager::GlobalTime + CBoatConfig::getInstance()->getTransportTs(id);
	}

	train.used_count += 1;
	train.level = m_player->getLevel();
	train.start_ts = LogicManager::GlobalTime;
	train.lost_res = 0;
	train.total_res = boatCost;

	vector<DataBoatRobLog> &rob_log = m_rob_log[id];
	rob_log.clear();

	doSave();

	doSend();

	onStartResp(uid, PROCESS_RET_SUCCESS);

	m_player->getActManager()->addTaskCount(ActSevenTask::ActSevenTaskTR2, boatCost);
	m_player->getActivenessManager()->onBoat();
	m_player->getTaskManager()->onBoatStart();

	CNetPacket asrvp;
	asrvp.uid = uid;
	CBufferWriter writer(asrvp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_TRANSPORT);
	writer.AppendByte(PROTOCOL_SUBCMD_TRANSPORT_START);
	writer.AppendByte(id);
	writer.AppendByte(m_player->getLevel());
	writer.AppendUInt32(uid);
	writer.AppendUInt32(boatCost);
	writer.AppendUInt32(train.end_ts);
	LogicManager::getInstance()->sendToAllServer(&asrvp);

	debug_log("uid=%u,id=%u,level=%u", uid, id, static_cast<uint32_t>(train.level));
	BUSI_MISC("play|transport|%u|%u|%u|%u", uid, id, boatCost, Time::GetGlobalTime());
	return true;
}
bool BoatManager::doBuyCount(CNetPacket *packet) {
	return true;
}
bool BoatManager::doReward(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	Award reward;
	CBoatRewardProtocol protocol;
	if (!protocol.Decode(&(packet->body))) {
		error_log("Decode error,uid=%u", uid);
		onRewardResp(uid, PROCESS_RET_FAIL, 0, reward);
		return false;
	}

	doReset();

	uint32_t id = protocol.id;
	if (id < 1 || id > MAX_MERCHANT_NUM) {
		error_log("id error,uid=%u,id=%u", uid, id);
		onRewardResp(uid, PROCESS_RET_FAIL, id, reward);
		return false;
	}
	DataBoatTrain &train = m_train[id];
	if (train.end_ts == 0 || train.end_ts > LogicManager::GlobalTime) {
		error_log("end ts error,uid=%u,id=%d", uid, id);
		onRewardResp(uid, PROCESS_RET_FAIL, id, reward);
		return false;
	}
	uint32_t lostRes = 0;
	vector<DataBoatRobLog> &rob_log = m_rob_log[id];
	for (size_t i = 0; i < rob_log.size(); ++i) {
		lostRes += rob_log[i].res;
	}
	uint32_t boatCost = CBoatConfig::getInstance()->getCost(id, train.level);
	lostRes = std::min(static_cast<float>(lostRes), static_cast<float>(boatCost) * 0.5f);
	uint32_t boatReward = CBoatConfig::getInstance()->getReward(id, train.level);
	double rate = static_cast<double>(boatCost) / static_cast<double>(boatReward);
	uint32_t transport_res = static_cast<double>(boatCost - lostRes) / rate;

	ResourceCost cost;
	float vip_rate = m_player->getVipManager()->getRight(VipManager::VIP_RIGHT_BOAT_RES);
	debug_log("uid=%u vip_rate=%f", uid, vip_rate);
	cost.r1 = transport_res + (static_cast<float>(transport_res) * vip_rate);
	m_player->getRm()->addResources(cost, "reward_ship");

	m_player->getTaskManager()->onTransportRes(cost.r1);

	if (!onBoxReward(train.level, id, CBoatConfig::getInstance()->getBox(id), &reward)) {
		error_log("box reward error,uid=%u,id=%d,lv=%u", uid, id, static_cast<uint32_t>(train.level));
		onRewardResp(uid, PROCESS_RET_FAIL, id, reward);
		return false;
	}

	Award sysAward;
	vector<AwardInfo>::const_iterator itr = reward.get().begin();
	for (; itr != reward.get().end(); ++itr) {
		if (itr->type == AWARD_TYPE_SOLDIER) {
			const SoldierItemConfig *cfg = SoldierConfig::getInstance()->getItemConfig(itr->id);
			if (cfg != NULL && cfg->q >= 3) {
				sysAward.add(*itr);
			}
		} else if (itr->type == AWARD_TYPE_SKILL) {
			const SkillConfig *cfg = CSkillConfig::getInstance()->getConfig(itr->id);
			if (cfg != NULL && cfg->q >= 3) {
				sysAward.add(*itr);
			}
		}
	}
	if (!sysAward.get().empty()) {
		SystemMessage::getInstance()->addBoatBag(uid, itr->id, &sysAward);
	}

	train.level = 0;
	train.end_ts = 0;
	train.start_ts = 0;
	train.total_res = 0;
	train.lost_res = 0;
	rob_log.clear();

	doSave();

	doSend();

	onRewardResp(uid, PROCESS_RET_SUCCESS, id, reward);

	debug_log("uid=%u,id=%u,rewardSize=%u", uid, id, reward.get().size());

	m_player->addTransPort(transport_res);

	return true;
}
bool BoatManager::doGetTarget(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CBoatGetTargetProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", uid);
		onGetTargetErrResp();
		return false;
	}

	doReset();
	revenge_id = 0;

	const ExpLevelItem *cfg = ExpConfig::getInstance()->getExpLevel(m_player->getLevel());
	if (cfg == NULL) {
		error_log("cfg is null uid=%u level=%u", uid, m_player->getLevel());
		onGetTargetErrResp();
		return false;
	}

	string code = "get_rob_target_" + CTrans::ITOS(m_boat.refresh_count);
	ResourceCost cost;
	cost.r1 = cfg->firstCost + m_boat.refresh_count * cfg->refreshCost;
	MoneyCost ncost;
	m_player->getRm()->ResToCash(cost, ncost.cash);
	if (ncost.cash && !m_player->getRm()->useMoney(ncost, code)) {
		error_log("useMoney error uid=%u level=%u", uid, m_player->getLevel());
		return false;
	}
	if (cost.ResSum() && !m_player->getRm()->useResources(cost, code)) {
		error_log("useResources error uid=%u level=%u", uid, m_player->getLevel());
		return false;
	}

	if (m_boat.refresh_count == 0 || proto.first == 1) {
		m_boat.reset_ts = LogicManager::GlobalTime;
	}

	m_boat.refresh_count += 1;

	doSave();

	if (m_player->getUserInfo().tutorial_stage < 10000) {
		error_log("tutorial_stage uid=%u level=%u", uid, m_player->getLevel());
		onGetTargetErrResp();
		return true;
	}

	uint32_t ulv = m_player->getLevel();
	uint32_t ts = LogicManager::GlobalTime > m_boat.reset_ts ? LogicManager::GlobalTime - m_boat.reset_ts : 0;

	CNetPacket asrvp;
	asrvp.uid = uid;
	CBufferWriter writer(asrvp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_TRANSPORT);
	writer.AppendByte(PROTOCOL_SUBCMD_TRANSPORT_SEARCH);
	writer.AppendByte(ulv);
	writer.AppendUInt32(uid);
	writer.AppendUInt32(ts);
	LogicManager::getInstance()->sendToAllServer(&asrvp);

	debug_log("uid=%u,lv=%u,ts=%u", uid, ulv, ts);

	return true;
}
bool BoatManager::doGetTargetCount(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	if (doReset()) {
		doSave();
	}
	CNetPacket sPacket;
	sPacket.uid = uid;
	CBufferWriter bWriter(&(sPacket.body));
	bWriter.AppendByte(PROTOCOL_CMD_BOAT);
	bWriter.AppendByte(PROTOCOL_SUBCMD_MERCHANT_GET_TARGET_COUNT);
	bWriter.AppendUInt32(m_boat.refresh_count);

	PlayerManager::getInstance()->sendToAccess(&sPacket);
	return true;
}
bool BoatManager::doRobResult(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CBoatRobResultProtocol protocol;
	if (!protocol.Decode(&(packet->body))) {
		error_log("Decode error uid=%u", uid);
		onRobResultResp(uid, PROCESS_RET_FAIL, 0, 0);
		return false;
	}

	doReset();
	m_boat.refresh_count = 0;

	uint32_t userid = protocol.userid;
	uint32_t id = protocol.id;
	uint32_t damage = protocol.damage > 100 ? 100 : protocol.damage;
	uint32_t star = protocol.star > 3 ? 3 : protocol.star;

	if (id < 1 || id > MAX_MERCHANT_NUM) {
		error_log("id error uid=%u userid=%u id=%u", uid, userid, id);
		return false;
	}

	if (IS_VALID_PLAYER_UID(userid)) {
		//robUser(uid, protocol);
		robTarget(uid,  protocol);
	} else {
		initNpc();
		if (m_npc.count(userid)) {
			robNpc(uid, protocol);
		} else {
			error_log("NPC error uid=%u userid=%u damage=%u", uid, userid, damage);
			onRobResultResp(uid, PROCESS_RET_FAIL, 0, 0);
		}
	}
	if (m_boat.star + star > 10) {
		m_boat.star = 10;
	} else {
		m_boat.star += star;
	}
	doSave();

	doSend();

	m_player->getActivenessManager()->onAttack();

	debug_log("uid=%u,userid=%u,id=%u,damage=%u,star=%u", uid, userid, id, damage, static_cast<unsigned>(protocol.star));

	BUSI_MISC("play|rob|%u|%u|%u|%u|%u", uid, id, star, m_player->getLevel(), Time::GetGlobalTime());

	return true;
}
bool BoatManager::doRobRes(CNetPacket *packet) {
	CBoatRobResProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", packet->uid);
		return false;
	}
	onRobByOther(proto.uid, proto.id, proto.name, proto.res, proto.exp);

	return true;
}
bool cmpRobLog(const DataBoatRobLog &left, const DataBoatRobLog &rigth) {
	return left.ts > rigth.ts;
}
bool BoatManager::doGetLog(CNetPacket *packet) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	long sts = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	uint32_t uid = packet->uid;
	multimap<uint32_t, uint32_t> rob_rank;
	CDataBoatRobLog dbc;
	vector<DataBoatRobLog> datas;
	dbc.Get(uid, datas);
	if (datas.size() > 20) {
		sort(datas.begin(), datas.end(), cmpRobLog);
		for (vector<DataBoatRobLog>::iterator itr = datas.begin() + 20; itr != datas.end();) {
			dbc.Del(uid, itr->ts);
			itr = datas.erase(itr);
		}
	}

	for (vector<DataBoatRobLog>::iterator itr = datas.begin(); itr != datas.end();) {
		if (CTime::GetDayInterval(itr->ts, LogicManager::GlobalTime) > 3) {
			dbc.Del(uid, itr->ts);
			itr = datas.erase(itr);
		} else {
			if (itr->type == BOAT_ROB_LOG_STATUS_DEF) {
				rob_rank.insert(make_pair(itr->ts, itr->userid));
			}
			++itr;
		}
	}

	uint32_t min_ts = LogicManager::GlobalTime;
	CDataBoatTrain dbBoatTrain;
	set<uint32_t> runing;
	multimap<uint32_t, uint32_t>::reverse_iterator ritr = rob_rank.rbegin();
	for (int i = 0; i < 5; ++i) {
		if (ritr == rob_rank.rend()) {
			break;
		}
		if (!runing.count(ritr->second)) {
			vector<DataBoatTrain> trains;
			dbBoatTrain.Get(ritr->second, trains);
			for (vector<DataBoatTrain>::iterator itr = trains.begin(); itr != trains.end(); ++itr) {
				if (itr->end_ts <= LogicManager::GlobalTime
				|| itr->lost_res >= itr->total_res * 0.5f
				|| (itr->id == MAX_MERCHANT_NUM && itr->level < AUTO_TRANSPORT_MIN_LEVEL)) {
					continue;
				}
				runing.insert(ritr->second);
				if (min_ts > ritr->first) {
					min_ts = ritr->first;
				}
				break;
			}
		} else {
			if (min_ts > ritr->first) {
				min_ts = ritr->first;
			}
		}
		++ritr;
	}

	Json::Reader reader;
	CNetPacket sp;
	sp.uid = uid;
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_BOAT);
	writer.AppendByte(PROTOCOL_SUBCMD_MERCHANT_ROB_LOG);
	writer.AppendUInt32(datas.size());
	for (vector<DataBoatRobLog>::iterator itr = datas.begin(); itr != datas.end(); ++itr) {
		writer.AppendByte(itr->type);
		writer.AppendByte(itr->win);
		writer.AppendByte(itr->damage);
		writer.AppendByte(itr->star);
		writer.AppendUInt32(itr->ts);
		writer.AppendUInt32(itr->userid);
		writer.AppendString(itr->username);
		writer.AppendByte(0);
		writer.AppendUInt32(itr->res);
		writer.AppendUInt32(itr->exp);

		Json::Value soldier;
		if (reader.parse(itr->soldier, soldier) && soldier.isArray()) {
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
		if (reader.parse(itr->tower, tower) && tower.isArray()) {
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
		if (reader.parse(itr->soldier_dead, soldier_dead) && soldier_dead.isArray()) {
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
		if (reader.parse(itr->skill, skill) && skill.isArray()) {
			writer.AppendUInt32(skill.size());
			for (size_t i = 0; i < skill.size(); ++i) {
				writer.AppendUInt32(skill[i]["id"].asUInt());
				writer.AppendUInt32(skill[i]["l"].asUInt());
				writer.AppendUInt32(skill[i]["c"].asUInt());
			}
		} else {
			writer.AppendUInt32(0);
		}

		if (itr->ts >= min_ts
		&& itr->type == BOAT_ROB_LOG_STATUS_DEF
		&& runing.count(itr->userid)
		&& itr->revenge_count < MAX_REVENGE_NUM) {
			writer.AppendByte(1);
		} else {
			writer.AppendByte(0);
		}
	}

	PlayerManager::getInstance()->sendToAccess(&sp);

	gettimeofday(&tv, NULL);
	long ets = tv.tv_sec * 1000 + tv.tv_usec / 1000;

	debug_log("uid=%u,ts=%ld", uid, ets - sts);

	return true;
}
bool BoatManager::doSpeedUp(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CBoatSpeedUpProtocol protocol;
	if (!protocol.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", uid);
		onSpeedUpResp(uid, PROCESS_RET_FAIL);
		return false;
	}
	uint32_t id = protocol.id;
	if (id < 1 || id > MAX_MERCHANT_NUM) {
		error_log("id error uid=%u id=%u", uid, id);
		onSpeedUpResp(uid, PROCESS_RET_FAIL);
		return false;
	}
	doReset();
	if (m_boat.speed_up >= 99) {
		error_log("speed up count error uid=%u id=%u", uid, id);
		onSpeedUpResp(uid, PROCESS_RET_FAIL);
		return false;
	}
	DataBoatTrain &train = m_train[id];
	if (train.end_ts <= LogicManager::GlobalTime) {
		error_log("end ts error uid=%u id=%u", uid, id);
		onSpeedUpResp(uid, PROCESS_RET_FAIL);
		return false;
	}
	if (!m_player->getEm()->useBagItemByType(602, 1, "speed_up_" + CTrans::ITOS(id))) {
		error_log("use item error uid=%u id=%u", uid, id);
		onSpeedUpResp(uid, PROCESS_RET_FAIL);
		return false;
	}
	train.end_ts -= 600;
	m_boat.speed_up += 1;
	doSave();

	doSend();
	onSpeedUpResp(uid, PROCESS_RET_SUCCESS);

	CNetPacket asrvp;
	asrvp.uid = uid;
	CBufferWriter writer(asrvp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_TRANSPORT);
	writer.AppendByte(PROTOCOL_SUBCMD_TRANSPORT_SPEED_UP);
	writer.AppendByte(train.id);
	writer.AppendUInt32(uid);
	writer.AppendUInt32(train.end_ts);
	LogicManager::getInstance()->sendToAllServer(&asrvp);

	debug_log("uid=%u,id=%u", uid, id);
	return true;
}
bool BoatManager::doStarReward(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	Award reward;
	doReset();
	if (m_boat.star < MAX_DAILY_STAR) {
		error_log("star error uid=%u", uid);
		onStarRewardResp(uid, PROCESS_RET_FAIL, reward);
		return false;
	}
	if (m_boat.star_reward == 1) {
		error_log("star error uid=%u", uid);
		onStarRewardResp(uid, PROCESS_RET_FAIL, reward);
		return false;
	}
	m_boat.star_reward = 1;
	doSave();

	uint32_t reward_id = 3;
	if (!onBoxReward(m_player->getLevel(), reward_id, CBoatConfig::getInstance()->getBox(reward_id), &reward)) {
		error_log("onBoxReward error uid=%u", uid);
		onStarRewardResp(uid, PROCESS_RET_FAIL, reward);
		return false;
	}

	onStarRewardResp(uid, PROCESS_RET_SUCCESS, reward);

	doSend();

	return true;
}
bool BoatManager::doAsrvTarget(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CBoatAsrvTargetProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		return false;
	}
	if (!IS_VALID_PLAYER_UID(proto.target_uid)) {
		CNetPacket sp;
		sp.uid = m_player->getUid();
		CBufferWriter bWriter(sp.GetBody());
		bWriter.AppendByte(PROTOCOL_CMD_BOAT);
		bWriter.AppendByte(PROTOCOL_SUBCMD_MERCHANT_GET_TARGET);
		getNpcInfo(proto.target_uid, sp.GetBody());
		PlayerManager::getInstance()->sendToAccess(&sp);
	} else if (ServerConfig::getInstance()->IsMerged(Config::GetZoneByUID(proto.target_uid))) {
		Player *player = PlayerManager::getInstance()->LoadForcePlayer(proto.target_uid);
		if (player == NULL) {
			return false;
		}
		CNetPacket sp;
		sp.uid = m_player->getUid();
		CBufferWriter bWriter(sp.GetBody());
		bWriter.AppendByte(PROTOCOL_CMD_BOAT);
		bWriter.AppendByte(PROTOCOL_SUBCMD_MERCHANT_GET_TARGET);
		MerchantNpc target_data;
		if (!player->getBoatManager()->getBoatInfo(proto.boat_id, sp.GetBody(), target_data)) {
			onGetTargetErrResp();
		} else {
			m_target = target_data;
			PlayerManager::getInstance()->sendToAccess(&sp);
		}
	} else {
		CNetPacket sp;
		sp.uid = proto.target_uid;
		CBufferWriter bWriter(sp.GetBody());
		bWriter.AppendByte(PROTOCOL_CMD_BOAT);
		bWriter.AppendByte(PROTOCOL_SUBCMD_MERCHANT_TARGET_INFO_REQ);
		bWriter.AppendUInt32(m_player->getUid());
		bWriter.AppendUInt32(proto.boat_id);
		LogicManager::getInstance()->sendToLogin(&sp);
	}
	debug_log("uid=%u,tar=%u,id=%u", uid, proto.target_uid, proto.boat_id);
	return true;
}

bool BoatManager::doTargetInfoReq(CNetPacket *packet) {
	byte ret = 0;
	CBoatAsrvTargetProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		ret = 1;
	}
	CNetPacket sp;
	sp.uid = proto.target_uid;
	CBufferWriter bWriter(sp.GetBody());
	bWriter.AppendByte(PROTOCOL_CMD_BOAT);
	bWriter.AppendByte(PROTOCOL_SUBCMD_MERCHANT_TARGET_INFO_RESP);
	CStaticBuffer<MAX_PROTOCOL_BODY_SIZE> boat_info;
	MerchantNpc target_data;
	if (0 == ret && !getBoatInfo(proto.boat_id, &boat_info, target_data)) {
		ret = 1;
	}
	bWriter.AppendByte(ret);
	if (0 == ret) {
		sp.GetBody()->AppendBuffer(&boat_info);
	}
	LogicManager::getInstance()->sendToLogin(&sp);
	debug_log("uid=%u,tuid=%u,bid=%u,ret=%d", packet->uid, proto.target_uid, proto.boat_id, static_cast<int>(ret));
	return true;
}

bool BoatManager::doTargetInfoResp(CNetPacket *packet) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter bWriter(sp.GetBody());
	bWriter.AppendByte(PROTOCOL_CMD_BOAT);
	bWriter.AppendByte(PROTOCOL_SUBCMD_MERCHANT_GET_TARGET);
	CBufferReader reader(packet->GetBody());
	byte cmd, subCmd, ret;
	if (reader.GetByte(cmd) && reader.GetByte(subCmd) && reader.GetByte(ret) && 0 == ret) {
		reader.GetUInt32(m_target.id);
		reader.GetUInt32(m_target.power);
		reader.GetUInt32(m_target.totalRes);
		reader.GetUInt32(m_target.lostRes);
		reader.GetUInt32(m_target.exp);
		uint32_t refresh_count = 0;
		reader.GetUInt32(refresh_count);
		uint32_t trainId = 0;
		reader.GetUInt32(trainId);
		m_target.trainId = trainId;
		reader.GetString(m_target.name);
		sp.GetBody()->Append(packet->GetBody()->GetNativeBuffer() + 3, packet->GetBody()->GetSize() - 3);
		PlayerManager::getInstance()->sendToAccess(&sp);
	} else {
		onGetTargetErrResp();
	}
	debug_log("uid=%u", packet->uid);
	return true;
}

bool BoatManager::doRevenge(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CBoatRevengeProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", uid);
		onRevengeResp(PROCESS_RET_FAIL);
		return false;
	}

	if (uid == proto.target_uid) {
		error_log("uid error uid=%u", uid);
		onRevengeResp(PROCESS_RET_FAIL);
		return false;
	}
	revenge_id = proto.ts;

	CNetPacket asrvp;
	asrvp.uid = uid;
	CBufferWriter writer(asrvp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_TRANSPORT);
	writer.AppendByte(PROTOCOL_SUBCMD_TRANSPORT_TARGET);
	writer.AppendUInt32(proto.target_uid);
	LogicManager::getInstance()->sendToAllServer(&asrvp);

	debug_log("uid=%u,target=%u,ts=%u", uid, proto.target_uid, proto.ts);
	return true;
}

bool BoatManager::doAsrvRevenge(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CBoatAsrvTargetProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", uid);
		return false;
	}
	if (!IS_VALID_PLAYER_UID(proto.target_uid)) {
		onRevengeResp(PROCESS_RET_FAIL);
	} else if (ServerConfig::getInstance()->IsMerged(Config::GetZoneByUID(proto.target_uid))) {
		Player *player = PlayerManager::getInstance()->LoadForcePlayer(proto.target_uid);
		if (player == NULL) {
			return false;
		}
		CNetPacket sp;
		sp.uid = m_player->getUid();
		CBufferWriter bWriter(sp.GetBody());
		bWriter.AppendByte(PROTOCOL_CMD_BOAT);
		bWriter.AppendByte(PROTOCOL_SUBCMD_MERCHANT_GET_TARGET);
		MerchantNpc target_data;
		if (!player->getBoatManager()->getBoatInfo(proto.boat_id, sp.GetBody(), target_data)) {
			onRevengeResp(PROCESS_RET_FAIL);
		} else {
			m_target = target_data;
			PlayerManager::getInstance()->sendToAccess(&sp);
		}
	} else {
		CNetPacket sp;
		sp.uid = proto.target_uid;
		CBufferWriter bWriter(sp.GetBody());
		bWriter.AppendByte(PROTOCOL_CMD_BOAT);
		bWriter.AppendByte(PROTOCOL_SUBCMD_MERCHANT_TARGET_INFO_REQ);
		bWriter.AppendUInt32(m_player->getUid());
		bWriter.AppendUInt32(proto.boat_id);
		LogicManager::getInstance()->sendToLogin(&sp);
	}

	debug_log("uid=%u,tuid=%u,tid=%u", uid, proto.target_uid, proto.boat_id);

	return true;
}

bool BoatManager::doCashReset(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	doReset();
	if (m_boat.reset_flag != 0) {
		error_log("reset flag error uid=%u", uid);
		onCashResetResp(PROCESS_RET_FAIL);
		return false;
	}

	MoneyCost cost;
	cost.cash = 80;
	if (!m_player->getRm()->useMoney(cost, "cash_reset_boat")) {
		error_log("use cash error uid=%u", uid);
		onCashResetResp(PROCESS_RET_FAIL);
		return false;
	}

	m_boat.reset_flag = 1;
	for (byte id = 1; id <= MAX_MERCHANT_NUM; ++id) {
		DataBoatTrain &item = m_train[id];
		if (item.used_count != 0) {
			item.used_count = 0;
		}
	}

	doSave();
	doSend();
	onCashResetResp(PROCESS_RET_SUCCESS);

	debug_log("uid=%u", uid);

	return true;
}

void BoatManager::onStartResp(uint32_t uid, byte ret) {
	CNetPacket sPacket;
	sPacket.uid = uid;
	CBufferWriter bWriter(&(sPacket.body));
	bWriter.AppendByte(PROTOCOL_CMD_BOAT);
	bWriter.AppendByte(PROTOCOL_SUBCMD_MERCHANT_START);
	bWriter.AppendByte(ret);

	PlayerManager::getInstance()->sendToAccess(&sPacket);
}
void BoatManager::onBuyCountResp(uint32_t uid, byte ret) {
	CNetPacket sPacket;
	sPacket.uid = uid;
	CBufferWriter bWriter(&(sPacket.body));
	bWriter.AppendByte(PROTOCOL_CMD_BOAT);
	bWriter.AppendByte(PROTOCOL_SUBCMD_MERCHANT_BUY_COUNT);
	bWriter.AppendByte(ret);

	PlayerManager::getInstance()->sendToAccess(&sPacket);
}
void BoatManager::onRewardResp(uint32_t uid, byte ret, byte id, const Award &reward) {
	CNetPacket sPacket;
	sPacket.uid = uid;
	CBufferWriter bWriter(&(sPacket.body));
	bWriter.AppendByte(PROTOCOL_CMD_BOAT);
	bWriter.AppendByte(PROTOCOL_SUBCMD_MERCHANT_REWARD);
	bWriter.AppendByte(ret);
	bWriter.AppendByte(id);
	reward.packetData(bWriter);

	PlayerManager::getInstance()->sendToAccess(&sPacket);
}
void BoatManager::onGetTargetErrResp() {
	MerchantNpc *npc = randNpc();
	if (npc == NULL) {
		error_log("rand npc error uid=%u", m_player->getUid());
		return;
	}
	CNetPacket sPacket;
	sPacket.uid = m_player->getUid();
	CBufferWriter bWriter(&(sPacket.body));
	bWriter.AppendByte(PROTOCOL_CMD_BOAT);
	bWriter.AppendByte(PROTOCOL_SUBCMD_MERCHANT_GET_TARGET);
	bWriter.AppendUInt32(npc->id);
	bWriter.AppendUInt32(npc->power);
	bWriter.AppendUInt32(npc->totalRes);
	bWriter.AppendUInt32(npc->lostRes);
	bWriter.AppendUInt32(npc->exp);
	bWriter.AppendUInt32(m_boat.refresh_count);
	bWriter.AppendUInt32(1);
	bWriter.AppendString(m_last_npc_name);
	bWriter.AppendByte(0);
	bWriter.AppendString("");
	bWriter.AppendByte(0);

	NpcManager::getInstance()->GetNpc(npc->id, &(sPacket.body));

	PlayerManager::getInstance()->sendToAccess(&sPacket);

	debug_log("uid=%u, npcid=%u, myexp=%u npcexp=%u ", m_player->getUid(), npc->id, m_player->getExp(), npc->exp);
}
void BoatManager::onRobResultResp(uint32_t uid, byte ret, int32_t exp, int32_t res) {
	CNetPacket sPacket;
	sPacket.uid = m_player->getUid();
	CBufferWriter bWriter(&(sPacket.body));
	bWriter.AppendByte(PROTOCOL_CMD_BOAT);
	bWriter.AppendByte(PROTOCOL_SUBCMD_MERCHANT_ROB_RESULT);
	bWriter.AppendByte(ret);
	bWriter.AppendInt32(res);
	bWriter.AppendInt32(exp);

	PlayerManager::getInstance()->sendToAccess(&sPacket);
}
void BoatManager::onRobNotice(uint32_t uid) {
	CNetPacket sPacket;
	sPacket.uid = uid;
	CBufferWriter bWriter(&(sPacket.body));
	bWriter.AppendByte(PROTOCOL_CMD_BOAT);
	bWriter.AppendByte(PROTOCOL_SUBCMD_MERCHANT_ROB_NOTICE);

	PlayerManager::getInstance()->sendToAccess(&sPacket);
}
void BoatManager::onSpeedUpResp(uint32_t uid, byte ret) {
	CNetPacket sPacket;
	sPacket.uid = m_player->getUid();
	CBufferWriter bWriter(&(sPacket.body));
	bWriter.AppendByte(PROTOCOL_CMD_BOAT);
	bWriter.AppendByte(PROTOCOL_SUBCMD_MERCHANT_SPEED_UP);
	bWriter.AppendByte(ret);

	PlayerManager::getInstance()->sendToAccess(&sPacket);
}
void BoatManager::onStarRewardResp(uint32_t uid, byte ret, const Award &reward) {
	CNetPacket sPacket;
	sPacket.uid = uid;
	CBufferWriter bWriter(&(sPacket.body));
	bWriter.AppendByte(PROTOCOL_CMD_BOAT);
	bWriter.AppendByte(PROTOCOL_SUBCMD_MERCHANT_STAR);
	bWriter.AppendByte(ret);
	reward.packetData(bWriter);

	PlayerManager::getInstance()->sendToAccess(&sPacket);
}
void BoatManager::onRevengeResp(byte ret) {
	CNetPacket sPacket;
	sPacket.uid = m_player->getUid();
	CBufferWriter bWriter(sPacket.GetBody());
	bWriter.AppendByte(PROTOCOL_CMD_BOAT);
	bWriter.AppendByte(PROTOCOL_SUBCMD_MERCHANT_REVENGE);
	bWriter.AppendByte(ret);

	PlayerManager::getInstance()->sendToAccess(&sPacket);
}
void BoatManager::onCashResetResp(byte ret) {
	CNetPacket sPacket;
	sPacket.uid = m_player->getUid();
	CBufferWriter bWriter(sPacket.GetBody());
	bWriter.AppendByte(PROTOCOL_CMD_BOAT);
	bWriter.AppendByte(PROTOCOL_SUBCMD_MERCHANT_CASH_RESET);
	bWriter.AppendByte(ret);

	PlayerManager::getInstance()->sendToAccess(&sPacket);
}
bool BoatManager::onBoxReward(uint32_t lv, uint32_t id, uint32_t count, Award *result) {
	uint32_t boxId = (lv == 0 ? 1 : lv) * 1000 + id;

	Award award;

	GiftBagConfig::getInstance()->openAllLuckyBox(boxId, count, award);

	m_player->doReward(&award, "boat_box_" + CTrans::ITOS(boxId), false, result);

	return true;
}
bool BoatManager::initNpc() {
	vector<uint32_t> lvs;
	uint32_t ulv = m_player->getLevel();
	lvs.push_back(ulv);
	if (ulv > 1) {
		lvs.push_back(ulv - 1);
	}
	lvs.push_back(ulv + 1);
	for (vector<uint32_t>::iterator it = lvs.begin(); it != lvs.end(); ++it) {
		const BoatNpcConfig *cfg = CBoatConfig::getInstance()->getBoatNpc(*it);
		if (cfg == NULL) {
			continue;
		}
		vector<BoatNpcItem>::const_iterator itr = cfg->npc.begin();
		for (; itr != cfg->npc.end(); ++itr) {
			MerchantNpc &npc = m_npc[itr->id];
			if (npc.lostRes >= npc.totalRes * 0.5) {
				npc.totalRes = itr->res;
				npc.exp = cfg->exp;
				npc.id = itr->id;
				npc.power = itr->power;
			}
		}
	}
	return true;
}
MerchantNpc* BoatManager::randNpc() {
	initNpc();
	if (m_npc.empty()) {
		return NULL;
	}
	int r = Math::GetRandomInt(m_npc.size());
	map<uint32_t, MerchantNpc>::iterator itr = m_npc.begin();
	for (; itr != m_npc.end(); ++itr, --r) {
		if (r == 0) {
			int ctrl = 0;
			string name;
			do {
				name = CBoatConfig::getInstance()->getNpcName();
			} while (m_last_npc_name == name && ++ctrl < 20);
			m_last_npc_name = name;
			return &(itr->second);
		}
	}
	return NULL;
}
int32_t BoatManager::calcExp(int32_t ae, int32_t be, uint32_t star, uint32_t lv) {
	double k = 29.0;
	if (star == 1) {
		k = 11.0;
	} else if (star == 2) {
		k = 19.0;
	}

	if (star > 0) {
		double power = static_cast<double>(ae - be) / (320.0f + static_cast<float>(lv) * 80.0f);
		return floor(1.0 / (1.0 + pow(10, power)) * k);
	} else {
		double power = static_cast<double>(be - ae) / (320.0f + static_cast<float>(lv) * 80.0f);
		return floor(1.0 / (1.0 + pow(10, power)) * -20.0);
	}
}
uint32_t BoatManager::caleRes(uint32_t totalRes, uint32_t lostRes, uint32_t res) {
	totalRes *= 0.5;
	uint32_t leftRes = totalRes > lostRes ? totalRes - lostRes : 0;
	return leftRes > res ? res : leftRes;
}
bool BoatManager::setLogStr(string &s, const map<pair<unsigned, unsigned>, unsigned> data) {
	Json::Value v = Json::Value(Json::arrayValue);
	map<pair<unsigned, unsigned>, unsigned>::const_iterator itr = data.begin();
	for (; itr != data.end(); ++itr) {
		Json::Value item;
		item["id"] = itr->first.first;
		item["l"] = itr->first.second;
		item["c"] = itr->second;
		v.append(item);
	}
	s = Json::ToString(v);
	return true;
}
void BoatManager::delTimeOutLog(unsigned uid) {
	CDataBoatRobLog robLogDbc;
	vector<DataBoatRobLog> datas;
	robLogDbc.GetLimit(uid, datas);
	for (vector<DataBoatRobLog>::iterator itr = datas.begin(); itr != datas.end(); ++itr) {
		if (CTime::GetDayInterval(itr->ts, LogicManager::GlobalTime) > 3) {
			robLogDbc.Del(uid, itr->ts);
		}
	}
}
bool BoatManager::robUser(uint32_t uid, CBoatRobResultProtocol &p) {
	uint32_t userid = p.userid;
	if (!IS_VALID_PLAYER_UID(userid)) {
		return false;
	}

	uint32_t id = p.id;
	uint32_t damage = p.damage > 100 ? 100 : p.damage;
	uint32_t star = p.star > 3 ? 3 : p.star;

	Player *player = PlayerManager::getInstance()->LoadForcePlayer(userid);
	if (player == NULL) {
		error_log("LoadForcePlayer error uid=%u userid=%u", uid, userid);
		onRobResultResp(uid, PROCESS_RET_FAIL, 0, 0);
		return false;
	}
	uint32_t res = 0;
	if (!player->getBoatManager()->onRob(uid, id, m_player->getName(), p.res, res)) {
		error_log("onRob error uid=%u userid=%u damage=%u", uid, userid, damage);
		onRobResultResp(uid, PROCESS_RET_FAIL, 0, 0);
		return false;
	}

	string code = "rob_" + CTrans::ITOS(userid);
	int32_t exp = calcExp(m_player->getExp(), player->getExp(), star, m_player->getLevel());
	m_player->upPlayerExp(exp, code);
	if (exp > 0) {
		player->upPlayerExp(-1 * exp * 0.8, code);
	} else {
		player->upPlayerExp(-1 * exp, code);
	}

	ResourceCost cost;
	cost.r2 = res;
	const ExpLevelItem *cfg = ExpConfig::getInstance()->getExpLevel(m_player->getLevel());
	if (cfg != NULL && star > 0) {
		float vip_rate = m_player->getVipManager()->getRight(VipManager::VIP_RIGHT_LOOT_ADD);
		cost.r2 += cfg->attackReward * static_cast<float>(1 + vip_rate);
	}

	m_player->getRm()->addResources(cost, code);

	onRobResultResp(uid, PROCESS_RET_SUCCESS, exp, res);

	m_player->getTaskManager()->onRobRes(res);
	player->getTaskManager()->onLostRes(res);
	if (star >= 3) {
		m_player->getTaskManager()->onFullStar();
	}

	string soldier, tower, soldierDead, skill;
	setLogStr(soldier, p.soldiers);
	setLogStr(tower, p.towers);
	setLogStr(soldierDead, p.soldier_dead);
	setLogStr(skill, p.skill);

	addLog(uid, userid, damage, star, res, exp, id, soldier, tower, soldierDead, skill);

	m_player->getActManager()->addTaskCount(ActSevenTask::ActSevenTaskAR2, res);

	if (res > 0 && id == 4) {
		SystemMessage::getInstance()->addRob(uid, userid, res);
	}
	onRobNotice(userid);
	addRevengeCount();
	CNetPacket asrvp;
	asrvp.uid = uid;
	CBufferWriter writer(asrvp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_TRANSPORT);
	writer.AppendByte(PROTOCOL_SUBCMD_TRANSPORT_ROB);
	writer.AppendByte(id);
	writer.AppendUInt32(userid);
	writer.AppendUInt32(res);
	LogicManager::getInstance()->sendToAllServer(&asrvp);

	return true;
}
bool BoatManager::robNpc(uint32_t uid, CBoatRobResultProtocol &p) {
	uint32_t userid = p.userid;
	if (IS_VALID_PLAYER_UID(userid)) {
		return false;
	}
	uint32_t id = p.id;
	uint32_t damage = p.damage > 100 ? 100 : p.damage;
	uint32_t star = p.star > 3 ? 3 : p.star;

	MerchantNpc &npc = m_npc[userid];
	int32_t exp = calcExp(m_player->getExp(), npc.exp, star, m_player->getLevel());
	string code = "rob_" + CTrans::ITOS(userid);
	m_player->upPlayerExp(exp, code);
	m_npc[userid].addExp(-1 * exp);
	uint32_t res = caleRes(npc.totalRes, npc.lostRes, p.res);
	if (res > 0) {
		ResourceCost cost;
		cost.r2 = res;
		const ExpLevelItem *cfg = ExpConfig::getInstance()->getExpLevel(m_player->getLevel());
		if (cfg != NULL && star > 0) {
			float vip_rate = m_player->getVipManager()->getRight(VipManager::VIP_RIGHT_LOOT_ADD);
			cost.r2 += cfg->attackReward * static_cast<float>(1 + vip_rate);
		}
		m_player->getRm()->addResources(cost, code);
		m_player->getActManager()->addTaskCount(ActSevenTask::ActSevenTaskAR2, res);
	}
	onRobResultResp(uid, PROCESS_RET_SUCCESS, exp, res);

	m_player->getTaskManager()->onRobRes(res);
	if (star >= 3) {
		m_player->getTaskManager()->onFullStar();
	}

	string soldier, tower, soldierDead, skill;
	setLogStr(soldier, p.soldiers);
	setLogStr(tower, p.towers);
	setLogStr(soldierDead, p.soldier_dead);
	setLogStr(skill, p.skill);

	addLog(uid, userid, damage, star, res, exp, id, soldier, tower, soldierDead, skill);

	return true;
}
bool BoatManager::robTarget(uint32_t uid, CBoatRobResultProtocol &p) {
	uint32_t userid = p.userid;
	if (!IS_VALID_PLAYER_UID(userid) || userid != m_target.id) {
		error_log("userid error uid=%u userid=%u tid=%u", uid, userid, m_target.id);
		onRobResultResp(uid, PROCESS_RET_FAIL, 0, 0);
		return false;
	}
	uint32_t id = p.id;
	uint32_t damage = p.damage > 100 ? 100 : p.damage;
	uint32_t star = p.star > 3 ? 3 : p.star;
	int32_t exp = calcExp(m_player->getExp(), m_target.exp, star, m_player->getLevel());
	uint32_t res = caleRes(m_target.totalRes, m_target.lostRes, p.res);
	string code = "rob_" + CTrans::ITOS(userid);

	//add my res and exp
	if (exp != 0) {
		m_player->upPlayerExp(exp, code);
	}
	if (res > 0) {
		ResourceCost cost;
		float vip_rate = m_player->getVipManager()->getRight(VipManager::VIP_RIGHT_LOOT_ADD);
		cost.r2 = res + static_cast<float>(res) * vip_rate;
		const ExpLevelItem *cfg = ExpConfig::getInstance()->getExpLevel(m_player->getLevel());
		if (cfg != NULL && star > 0) {
			cost.r2 += cfg->attackReward;
		}
		m_player->getRm()->addResources(cost, code);
	}

	onRobResultResp(uid, PROCESS_RET_SUCCESS, exp, res);

	m_player->getTaskManager()->onRobRes(res);
	if (star >= 3) {
		m_player->getTaskManager()->onFullStar();
	}

	string soldier, tower, soldierDead, skill;
	setLogStr(soldier, p.soldiers);
	setLogStr(tower, p.towers);
	setLogStr(soldierDead, p.soldier_dead);
	setLogStr(skill, p.skill);

	addLog(uid, userid, damage, star, res, exp, id, soldier, tower, soldierDead, skill);

	m_player->getActManager()->addTaskCount(ActSevenTask::ActSevenTaskAR2, res);

	addRevengeCount();

	//sub target res and exp
	if (!ServerConfig::getInstance()->IsMerged(Config::GetZoneByUID(userid))) {
		//transpond
		CNetPacket sp;
		sp.uid = userid;
		CBufferWriter writer(sp.GetBody());
		writer.AppendByte(PROTOCOL_CMD_BOAT);
		writer.AppendByte(PROTOCOL_SUBCMD_MERCHANT_ROB_RES);
		writer.AppendUInt32(uid);
		writer.AppendUInt32(id);
		writer.AppendUInt32(res);
		writer.AppendInt32(0 - exp);
		writer.AppendString(m_player->getName());
		LogicManager::getInstance()->sendToLogin(&sp);
		return true;
	}

	Player *player = PlayerManager::getInstance()->LoadForcePlayer(userid);
	if (player != NULL) {
		player->getBoatManager()->onRobByOther(uid, m_target.trainId, m_player->getName(), res, 0 - exp);
	} else {
		error_log("load player error uid=%u userid=%u", uid, userid);
	}
	if (res > 0 && id == 4) {
		SystemMessage::getInstance()->addRob(uid, userid, res);
	}
	return true;
}

bool BoatManager::addLog(uint32_t att, uint32_t def, uint32_t damage, uint32_t star, int32_t res, int32_t ex, byte train_id, const string &s, const string &t, const string &sd, const string &sk) {
	DataBoatRobLog mRobLog;
	DataBoatRobLog oRobLog;
	mRobLog.uid = att;
	mRobLog.ts = LogicManager::GlobalTime;
	mRobLog.type = BOAT_ROB_LOG_STATUS_ATT;
	mRobLog.userid = def;
	mRobLog.soldier = s;
	mRobLog.tower = t;
	mRobLog.soldier_dead = sd;
	mRobLog.skill = sk;
	mRobLog.train_id = train_id;

	oRobLog.uid = def;
	oRobLog.ts = LogicManager::GlobalTime;
	oRobLog.type = BOAT_ROB_LOG_STATUS_DEF;
	oRobLog.userid = att;
	oRobLog.soldier = s;
	oRobLog.tower = t;
	oRobLog.soldier_dead = sd;
	oRobLog.skill = sk;
	oRobLog.train_id = train_id;

	if (star > 0) {
		mRobLog.win = BOAT_ROB_RESULT_WIN;
		oRobLog.win = BOAT_ROB_RESULT_LOST;
	} else {
		oRobLog.win = BOAT_ROB_RESULT_WIN;
		mRobLog.win = BOAT_ROB_RESULT_LOST;
	}

	oRobLog.res = mRobLog.res = Math::Abs(res);
	mRobLog.exp = Math::Abs(ex);
	if (ex > 0) {
		oRobLog.exp = ex * 0.8;
	} else {
		oRobLog.exp = 0 - ex;
	}
	oRobLog.star = mRobLog.star = star;
	oRobLog.damage = mRobLog.damage = damage;

	oRobLog.username = m_player->getName();
	if (IS_VALID_PLAYER_UID(def)) {
		mRobLog.username = m_target.name;
	} else {
		mRobLog.username = m_last_npc_name;
	}

	CDataBoatRobLog robLogDbc;

	robLogDbc.Add(mRobLog);
	delTimeOutLog(att);

	if (IS_VALID_PLAYER_UID(def)) {
		robLogDbc.Add(oRobLog);
		delTimeOutLog(def);
	}

	return true;
}

bool BoatManager::getBoatInfo(uint32_t id, IBuffer *buff, MerchantNpc &data) {
	if (id < 1 || id > MAX_MERCHANT_NUM) {
		return false;
	}
	const DataBoatTrain &train = m_train[id];
	CBufferWriter bWriter(buff);
	bWriter.AppendUInt32(m_player->getUid());
	bWriter.AppendUInt32(m_player->getUserCombat());
	bWriter.AppendUInt32(train.total_res); // total res
	bWriter.AppendUInt32(train.lost_res); // lost res
	bWriter.AppendUInt32(m_player->getExp());
	bWriter.AppendUInt32(m_boat.refresh_count);
	bWriter.AppendUInt32(id);
	bWriter.AppendString(m_player->getName());
	bWriter.AppendByte(0);
	bWriter.AppendString(m_player->getUserInfo().figure_url);
	bWriter.AppendByte(0);
	m_player->getTroopsManager()->packDefend(buff);
	m_player->getSoldierManager()->packInfo(buff);
	m_player->getGemManager()->encode(buff);

	data.id = m_player->getUid();
	data.totalRes = train.total_res;
	data.lostRes = train.lost_res;
	data.exp = m_player->getExp();
	data.trainId = id;
	data.name = m_player->getName();

	return true;
}

bool BoatManager::getNpcInfo(uint32_t id, IBuffer *buff) {
	initNpc();
	map<uint32_t, MerchantNpc>::iterator itr = m_npc.find(id);
	if (itr == m_npc.end()) {
		error_log("npc id error id=%u", id);
		for (itr = m_npc.begin(); itr != m_npc.end(); ++itr) {
			error_log("uid=%u, id=%u", m_player->getUid(), itr->first);
		}
		return false;
	}
	int ctrl = 0;
	string name;
	do {
		name = CBoatConfig::getInstance()->getNpcName();
	} while (m_last_npc_name == name && ++ctrl < 20);
	m_last_npc_name = name;
	const MerchantNpc &npc = itr->second;

	debug_log("uid=%u,buff=%u", m_player->getUid(), buff->GetSize());
	CBufferWriter bWriter(buff);
	bWriter.AppendUInt32(npc.id);
	bWriter.AppendUInt32(npc.power);
	bWriter.AppendUInt32(npc.totalRes);
	bWriter.AppendUInt32(npc.lostRes);
	bWriter.AppendUInt32(npc.exp);
	bWriter.AppendUInt32(m_boat.refresh_count);
	bWriter.AppendUInt32(1);
	bWriter.AppendString(m_last_npc_name);
	bWriter.AppendByte(0);
	bWriter.AppendString("");
	bWriter.AppendByte(0);

	debug_log("uid=%u,buff=%u", m_player->getUid(), buff->GetSize());

	NpcManager::getInstance()->GetNpc(id, buff);

	debug_log("uid=%u,buff=%u", m_player->getUid(), buff->GetSize());

	return true;
}
