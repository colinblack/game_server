/*
 * ResourceManager.cpp
 *
 *  Created on: 2015-9-16
 *      Author: Administrator
 */

#include "ResourceManager.h"
#include "PlayerManager.h"
#include "ProtocolInc.h"
#include "FeteConfig.h"
#include "VipConfig.h"

ResourceManager::ResourceManager(): m_player(NULL), m_r1Max(0), m_r2Max(0), m_tlMax(0) {
}

ResourceManager::~ResourceManager() {
}

bool ResourceManager::load(uint32_t uid) {
	int ret = 0;

	initMax();

	CDataUserResource dbRes;
	ret = dbRes.Get(uid, m_ur);
	if (ret == -1) {
		error_log("load %u's resouce failed", uid);
		return false;
	} else if (ret == R_ERR_NO_DATA) {
		memset((void*) &m_ur, 0, sizeof(m_ur));
		m_ur.uid = uid;
		m_ur.tl = m_tlMax;
		if (dbRes.Add(m_ur) != 0) {
			error_log("add new user %u's resouce failed", uid);
			return false;
		}
	}

	CDataPay dbPay;
	ret = dbPay.GetPay(uid, m_pay);
	if (ret == -1) {
		error_log("load %u's pay failed", uid);
		return false;
	} else if (ret == R_ERR_NO_DATA) {
		memset((void*) &m_pay, 0, sizeof(m_pay));
		m_pay.uid = uid;
		if (dbPay.AddPay(m_pay) != 0) {
			error_log("add new user %u's resouce failed", uid);
			return false;
		}
	}

	checkValid();

	return true;
}

bool ResourceManager::onLogin() {
	return initMax();
}

bool ResourceManager::initMax() {
	if (m_player == NULL) {
		return false;
	}
	m_r1Max = m_player->getBm()->getResourceGoldCapacity();
	m_r2Max = m_player->getBm()->getResourceMagicCapacity();
	m_tlMax = initTLMax();
	return true;
}

void ResourceManager::checkValid() {
	bool needSave = false;
	if (m_ur.r1 > m_r1Max) {
		m_ur.r1 = m_r1Max;
		needSave = true;
	}
	if (m_ur.r2 > m_r2Max) {
		m_ur.r2 = m_r2Max;
		needSave = true;
	}
	if (m_ur.tl > m_tlMax) {
		m_ur.tl = m_tlMax;
		needSave = true;
	}

	if (needSave) {
		CDataUserResource dbRes;
		if (dbRes.Set(m_ur) != 0) {
			error_log("update user %u's resouce failed", m_ur.uid);
		}
	}

}

bool ResourceManager::setUserResourceData(const DataUserResource & dur) {
	m_ur = dur;
	initMax();
	return true;
}

bool ResourceManager::setUserPayData(const DataPay & pay) {
	m_pay = pay;
	return true;
}

bool ResourceManager::doPacket(CNetPacket * packet) {
	switch (packet->subCmd) {
	case PROTOCOL_SUBCMD_RESOURCE_QUERY:
		doQueryResource(packet);
		break;
	case PROTOCOL_SUBCMD_USE_RES:
		doUpdateResource(packet);
		break;
	}
	return true;
}

void ResourceManager::ResToCash(ResourceCost &res, uint32_t &cash) {
	if (res.r1 > m_ur.r1) {
		cash += ::ceil(0.038 * pow((res.r1 - m_ur.r1), 0.758));
		res.r1 = m_ur.r1;
	}
	if (res.r2 > m_ur.r2) {
		cash += ::ceil(0.038 * pow((res.r2 - m_ur.r2), 0.758));
		res.r2 = m_ur.r2;
	}
}

bool ResourceManager::doQueryResource(CNetPacket * packet) {
	if (!sendResourceList()) {
		error_log("doQueryResource_fail&uid=%u", m_ur.uid);
		return false;
	}
	return true;
}

bool ResourceManager::doUpdateResource(CNetPacket *packet) {
	byte ret = 0;
	CUseResProtocol protocol;
	if (!protocol.Decode(&(packet->body))) {
		ret = PROTOCOL_RET_RESOURCE_FAIL;
	}
	if (ret == 0 && !upR1(protocol.r1, "client_update")) {
		ret = PROTOCOL_RET_RESOURCE_FAIL;
	}
	if (ret == 0 && !upR2(protocol.r2, "client_update")) {
		ret = PROTOCOL_RET_RESOURCE_FAIL;
	}

	CNetPacket sRspPacket;
	sRspPacket.uid = m_ur.uid;
	sRspPacket.cmd = PROTOCOL_CMD_RESOURCE;
	sRspPacket.subCmd = PROTOCOL_SUBCMD_USE_RES;
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_RESOURCE);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_USE_RES);
	selfWriter.AppendByte(ret);

	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket)) {
		error_log("sendAccess_fail&uid=%u", m_ur.uid);
		return false;
	}

	return true;
}

bool ResourceManager::useResources(const ResourceCost & cost, const string & code) {
	if (cost.r1 > m_ur.r1
	|| cost.r2 > m_ur.r2
	|| cost.r3 > m_ur.r3
	|| cost.r4 > m_ur.r4
	|| cost.tl > m_ur.tl
	|| cost.p1 > m_ur.p1
	|| cost.p2 > m_ur.p2
	|| cost.p3 > m_ur.p3
	) {
		error_log("resource not enough uid=%u", m_ur.uid);
		return false;
	}
	m_ur.r1 -= cost.r1;
	m_ur.r2 -= cost.r2;
	m_ur.r3 -= cost.r3;
	m_ur.r4 -= cost.r4;
	m_ur.tl -= cost.tl;
	m_ur.p1 -= cost.p1;
	m_ur.p2 -= cost.p2;
	m_ur.p3 -= cost.p3;

	CDataUserResource dbRes;
	if (dbRes.Set(m_ur) != 0) {
		error_log("update user %u's resouce failed", m_ur.uid);
		return false;
	}
	if (!sendResourceList()) {
		error_log("sendResource_fail&uid=%u", m_ur.uid);
	}
	BUSI_RES("%u|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%s|%u",
			m_ur.uid, -cost.r1, -cost.r2, -cost.p1, -cost.p2, -cost.p3,
			m_ur.r1, m_ur.r2, m_ur.p1, m_ur.p2, m_ur.p3,
			code.c_str(), LogicManager::GlobalTime);
	if (cost.r1 > 0) {
		m_player->getActManager()->addCoins(cost.r1);
	}
	return true;
}

bool ResourceManager::useMoney(const MoneyCost & cost, const string & code) {
	if (!checkUseMoney(cost.coin, cost.cash)) {
		error_log("checkUserMoney fail uid=%u", m_ur.uid);
		return false;
	}
	m_pay.cash -= cost.cash;
	m_pay.coins -= cost.coin;
	CDataPay dbData;
	if (dbData.SetPay(m_pay) != 0) {
		error_log("update user %u's pay failed", m_pay.uid);
		return false;
	}
	if (!sendResourceList()) {
		error_log("sendResource_fail&uid=%u", m_ur.uid);
	}
	BUSI_COIN("code=%s|%u|%d|%d|%u|%u|%u",
			code.c_str(), m_ur.uid, -cost.cash, -cost.coin,
			m_pay.cash, m_pay.coins, LogicManager::GlobalTime);
	if (cost.cash > 0) {
		m_player->getActManager()->addConsume(cost.cash);
	}
	return true;
}

bool ResourceManager::addMoney(const MoneyCost & cost, const string & code) {
	m_pay.cash += cost.cash;
	m_pay.coins += cost.coin;
	CDataPay dbData;
	if (dbData.SetPay(m_pay) != 0) {
		error_log("update user %u's pay failed", m_pay.uid);
		return false;
	}
	if (!sendResourceList()) {
		error_log("sendResource_fail&uid=%u", m_ur.uid);
	}
	BUSI_COIN("code=%s|%u|%d|%d|%u|%u|%u",
			code.c_str(), m_ur.uid, cost.cash, cost.coin,
			m_pay.cash, m_pay.coins, LogicManager::GlobalTime);
	return true;
}

bool ResourceManager::checkUseMoney(uint32_t coins, uint32_t cash) {
	if (coins > m_pay.coins) {
		return false;
	}
	if (cash > m_pay.cash) {
		return false;
	}
	return true;
}

bool ResourceManager::addResources(const ResourceCost & cost, const string & code) {
	if (IS_VALID_NPC_UID(m_ur.uid)) {
		return true;
	}

	int32_t cr1 = updateResourceInLimit(m_ur.r1, cost.r1, m_r1Max);
	int32_t cr2 = updateResourceInLimit(m_ur.r2, cost.r2, m_r2Max);
	//int32_t cr3 = updateResourceInLimit(m_ur.r3, cost.r3, 0xFFFFFFFF);
	//int32_t cr4 = updateResourceInLimit(m_ur.r4, cost.r4, 0xFFFFFFFF);
	//int32_t crtl = updateResourceInLimit(m_ur.tl, cost.tl, m_tlMax);
	int32_t cp1 = updateResourceInLimit(m_ur.p1, cost.p1, 0xFFFFFFFF);
	int32_t cp2 = updateResourceInLimit(m_ur.p2, cost.p2, 0xFFFFFFFF);
	int32_t cp3 = updateResourceInLimit(m_ur.p3, cost.p3, 0xFFFFFFFF);

	CDataUserResource dbRes;
	if (dbRes.Set(m_ur) != 0) {
		error_log("update user %u's resouce failed", m_ur.uid);
		return false;
	}
	if (!sendResourceList()) {
		error_log("sendResource_fail&uid=%u", m_ur.uid);
	}
	BUSI_RES("%u|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%s|%u|",
			m_ur.uid, cr1, cr2, cp1, cp2, cp3,
			m_ur.r1, m_ur.r2, m_ur.p1, m_ur.p2, m_ur.p3,
			code.c_str(), LogicManager::GlobalTime);
	return true;
}

bool ResourceManager::getResourceCapacity(uint32_t & cap) {
	if (!m_player) {
		error_log("m_player is null");
		return false;
	}
	BuildingManager * pBm = m_player->getBm();
	if (!pBm) {
		error_log("m_player is null");
		return false;
	}

	cap = pBm->getResourceCapacity();

	return true;
}

int32_t ResourceManager::updateResourceInLimit(uint32_t & curRes, int32_t chgRes, uint32_t maxCap) {
	int32_t change = 0;
	if (m_player == NULL) {
		return 0;
	}

	int64_t res = curRes + chgRes;
	res = res < 0 ? 0 : res;
	res = res > maxCap ? maxCap : res;
	change = res - curRes;
	curRes = res;
	return change;
}

uint32_t ResourceManager::initTLMax() {
	uint32_t maxTL = getMaxTLLimit();
	uint32_t rate = 0;
	if (rate > 0) {
		maxTL = maxTL * (1.0f + static_cast<float>(rate) / 100.0f);
	}
	return maxTL;
}

bool ResourceManager::sendResourceList() {
	CNetPacket sRspPacket;
	sRspPacket.uid = m_ur.uid;
	sRspPacket.cmd = PROTOCOL_CMD_RESOURCE;
	sRspPacket.subCmd = PROTOCOL_RSP_SUBCMD_RESOURCE_QUERY;
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_RESOURCE);
	selfWriter.AppendByte(PROTOCOL_RSP_SUBCMD_RESOURCE_QUERY);
	selfWriter.AppendByte(0);
	selfWriter.AppendUInt32(m_ur.r1);
	selfWriter.AppendUInt32(m_r1Max);
	selfWriter.AppendUInt32(m_ur.r2);
	selfWriter.AppendUInt32(m_r2Max);
	selfWriter.AppendUInt32(m_ur.r3);
	selfWriter.AppendUInt32(m_ur.r3);
	selfWriter.AppendUInt32(m_ur.r4);
	selfWriter.AppendUInt32(m_ur.r4);
	selfWriter.AppendUInt32(m_ur.tl);
	selfWriter.AppendUInt32(m_tlMax);
	selfWriter.AppendUInt32(0);
	selfWriter.AppendUInt32(0);
	selfWriter.AppendUInt32(IS_VALID_NPC_UID(m_ur.uid) ? 0 : m_pay.cash);
	selfWriter.AppendUInt32(IS_VALID_NPC_UID(m_ur.uid) ? 0 : m_pay.coins);
	selfWriter.AppendUInt32(0);  // m1
	selfWriter.AppendUInt32(0);  // m2
	selfWriter.AppendUInt32(0);  // m3
	selfWriter.AppendUInt32(0);  // m4
	selfWriter.AppendUInt32(0);  // ww
	selfWriter.AppendUInt32(0);  // mf
	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket)) {
		error_log("sendAccess_fail&uid=%u", m_ur.uid);
		return false;
	}
	return true;
}

bool ResourceManager::upR1(int32_t count, const string & code) {
	if (count == 0) {
		return true;
	}
	if (count >= 0) {
		ResourceCost cost;
		cost.r1 = count;
		return addResources(cost, code);
	} else {
		ResourceCost cost;
		cost.r1 = -count;
		return useResources(cost, code);
	}
	return true;
}

bool ResourceManager::upR2(int32_t count, const string & code) {
	if (count == 0) {
		return true;
	}
	if (count >= 0) {
		ResourceCost cost;
		cost.r2 = count;
		return addResources(cost, code);
	} else {
		ResourceCost cost;
		cost.r2 = -count;
		return useResources(cost, code);
	}
	return true;
}

bool ResourceManager::upR3(int32_t count, const string & code) {
	if (count == 0) {
		return true;
	}
	if (count >= 0) {
		ResourceCost cost;
		cost.r3 = count;
		return addResources(cost, code);
	} else {
		ResourceCost cost;
		cost.r3 = -count;
		return useResources(cost, code);
	}
	return true;
}

bool ResourceManager::upR1Rate(int32_t rate, const string & code) {
	if (rate == 0) {
		return true;
	}
	if (rate > 0) {
		ResourceCost cost;
		cost.r1 = m_r1Max * rate / 100;
		return addResources(cost, code);
	}
	return true;
}

bool ResourceManager::upR2Rate(int32_t rate, const string & code) {
	if (rate == 0) {
		return true;
	}
	if (rate > 0) {
		ResourceCost cost;
		cost.r2 = m_r2Max * rate / 100;
		return addResources(cost, code);
	}
	return true;
}

bool ResourceManager::upEnergy(int32_t energy, const string & code) {
	if (energy == 0) {
		return true;
	}
	if (energy >= 0) {
		ResourceCost cost;
		cost.tl = energy;
		return addResources(cost, code);
	} else {
		ResourceCost cost;
		cost.tl = -energy;
		return useResources(cost, code);
	}
	return true;
}

bool ResourceManager::upCash(int32_t cash, const string & code) {
	if (cash >= 0) {
		MoneyCost cost;
		cost.cash = cash;
		return addMoney(cost, code);
	} else {
		MoneyCost cost;
		cost.cash = -cash;
		return useMoney(cost, code);
	}
	return true;
}

bool ResourceManager::upCoin(int32_t coin, const string & code) {
	if (coin >= 0) {
		MoneyCost cost;
		cost.coin = coin;
		return addMoney(cost, code);
	} else {
		MoneyCost cost;
		cost.coin = -coin;
		return useMoney(cost, code);
	}
	return true;
}

bool ResourceManager::upLoyal(int32_t value, const string & code) {
	return false;
}

uint32_t ResourceManager::getMaxTLLimit() {
	static uint32_t maxTLLimit = Config::GetIntValue("max_tl_limit");
	return maxTLLimit;
}

uint32_t ResourceManager::getTLRecoveInterval() {
	static uint32_t TLRecoveInterval = Config::GetIntValue("tl_recove_interval");
	return TLRecoveInterval;
}

bool ResourceManager::updateResource(ResourceInfo & sInfo, const string & code) {
	if (!upR1(sInfo.r1, code)) {
		error_log("upSupply fail uid=%u", m_ur.uid);
		return false;
	}
	if (!upR2(sInfo.r2, code)) {
		error_log("upOil fail uid=%u", m_ur.uid);
		return false;
	}
	return true;
}
