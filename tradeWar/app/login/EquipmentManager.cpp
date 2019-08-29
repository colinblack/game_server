/*
 * EquipmentManager.cpp
 *
 *  Created on: 2015-9-1
 *      Author: Administrator
 */

#include "EquipmentManager.h"
#include "DataInc.h"
#include "PlayerManager.h"
#include "EquipmentConfig.h"
#include "ShopConfig.h"
#include "VipConfig.h"
#include "GiftBagConfig.h"
#include "SoldierConfig.h"
#include "SkillConfig.h"
#include "SystemMessage.h"

EquipmentManager::EquipmentManager() {
	m_maxUd = 0;
	m_player = NULL;
}

EquipmentManager::~EquipmentManager() {
	release();
}

void EquipmentManager::release() {
	map<uint32_t, Equipment*>::iterator itr = m_bags.begin();
	for (; itr != m_bags.end(); ++itr) {
		delete itr->second;
	}
	m_bags.clear();
}

bool EquipmentManager::load(uint32_t uid) {
	release();
	CDataEquipment dbEquipment;
	vector<DataEquipment> datas;
	if (dbEquipment.GetEquipment(uid, datas) != 0) {
		error_log("load %u's equipments failed", uid);
		return false;
	}
	setData(datas);
	return true;
}

bool EquipmentManager::parse(uint32_t uid, uint32_t id, const string &data) {
	if (id > m_maxUd) {
		m_maxUd = id;
	}
	Equipment *pEq = new Equipment();
	if (pEq == NULL) {
		return false;
	}
	if (!pEq->setData(data)) {
		error_log("set data error uid=%u id=%u", uid, id);
		delete pEq;
		return false;
	}
	pEq->setUid(uid);
	m_bags.insert(make_pair(id, pEq));
	return true;
}

bool EquipmentManager::setData(const vector<DataEquipment> &data)
{
	vector<DataEquipment>::const_iterator itr = data.begin();
	for (; itr != data.end(); ++itr) {
		parse(itr->uid, itr->id, itr->data);
	}
	return true;
}

bool EquipmentManager::save(uint32_t uid) {
	return true;
}

bool EquipmentManager::doPacket(CNetPacket * packet) {
	switch (packet->subCmd) {
	case PROTOCOL_SUBCMD_EQUIPMENTLIST:
		doQueryEquipment(packet);
		break;
	case PROTOCOL_SUBCMD_BAGLIST:
		doQueryBag(packet);
		break;
	case PROTOCOL_SUBCMD_SHOP_BUY:
		doBuyItem(packet);
		break;
	case PROTOCOL_SUBCMD_EQUIPMENT_USE:
		doEquipmentUse(packet);
		break;
	case PROTOCOL_SUBCMD_GEM_POINT_INFO:
		doGemInfo(packet);
		break;
	case PROTOCOL_SUBCMD_GEM_POINT:
		doGemPoint(packet);
		break;
	case PROTOCOL_SUBCMD_GEM_COMBINE:
		doGemCombine(packet);
		break;
	case PROTOCOL_SUBCMD_EQUIP_COMBINE:
		doEquipCombine(packet);
		break;
	default:
		error_log("unknow cmd=%u subCmd=%u", packet->cmd, packet->subCmd);
		break;
	}
	return true;
}

bool EquipmentManager::doQueryEquipment(CNetPacket *packet) {
	sendEquipmentList();
	return true;
}

bool EquipmentManager::doQueryBag(CNetPacket *packet) {
	sendBagList();
	return true;
}

void EquipmentManager::onBuyItemResponse(byte ret) {
	CNetPacket sPacket;
	sPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&sPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_EQUIPMENT);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_SHOP_BUY);
	selfWriter.AppendByte(ret);
	selfWriter.AppendInt32(m_player->getUserInfo().free_equp_ts);
	PlayerManager::getInstance()->sendToAccess(&sPacket);
}

bool EquipmentManager::onGemPoint(uint32_t type, byte ret) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_EQUIPMENT);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_GEM_POINT);
	PACKET_ENCODE(Byte, ret);
	m_player->getGemManager()->encode(type, sp.GetBody());
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool EquipmentManager::onGemCombine(byte ret) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_EQUIPMENT);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_GEM_COMBINE);
	PACKET_ENCODE(Byte, ret);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool EquipmentManager::onEquipCombine(byte ret, uint32_t type, Award &reward) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_EQUIPMENT);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_EQUIP_COMBINE);
	PACKET_ENCODE(Byte, ret);
	PACKET_ENCODE(UInt32, type);
	reward.packetData(writer);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool EquipmentManager::doBuyItem(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CBuyItemProtocol protocol;
	if (!protocol.Decode(&packet->body)) {
		error_log("CBuyItemProtocol decode fail uid=%u", uid);
		onBuyItemResponse(PROTOCOL_RET_EQUIP_PACKET_ERROR);
		return false;
	}

	const ShopGood *pItem = CShopConfig::getInstance()->getGoodItem(protocol.id);
	if (pItem == NULL) {
		error_log("getItem fail uid=%u id=%u", uid, protocol.id);
		onBuyItemResponse(PROTOCOL_RET_EQUIP_FAIL);
		return false;
	}

	MoneyCost cost;
	//每48小时史诗宝箱免费一次
	if(9005 == protocol.id &&
			(0 == m_player->getUserInfo().free_equp_ts ||
			 Time::GetGlobalTime() >= m_player->getUserInfo().free_equp_ts + (86400 * 2))) {
		cost.cash = 0;
		m_player->getUserInfo().free_equp_ts = Time::GetGlobalTime();
		m_player->savePlayerUserInfo();
	} else {
		cost.cash = pItem->cost * protocol.count;
	}
	if (!m_player->getRm()->useMoney(cost, string("buy_").append(String::i2s(pItem->id)))) {
		error_log("useMoney fail uid=%u count=%u", uid, protocol.count);
		onBuyItemResponse(PROTOCOL_RET_EQUIP_FAIL);
		return false;
	}
	if (protocol.useNow == 0 && !addBagItem(pItem->id, protocol.count, "shop_buy")) {
		error_log("addBagItem fail uid=%u count=%u", uid, protocol.count);
		onBuyItemResponse(PROTOCOL_RET_EQUIP_FAIL);
		return false;
	}
	int item = protocol.id;

	if(9005 == protocol.id || 9006 == protocol.id || 9007 == protocol.id) {
		item = m_player->getUserInfo().level* 1000 + 20 + (protocol.id - 9004);
	}

	if (protocol.useNow == 1) {
		if (!useGiftBag(item, protocol.count, false)) {
			onBuyItemResponse(PROTOCOL_RET_EQUIP_FAIL);
			return false;
		}
	}
	onBuyItemResponse(0);
	return true;
}

bool EquipmentManager::doEquipmentUse(CNetPacket *packet) {
	CEquipUseProtocol protocol;
	if (!protocol.Decode(&packet->body)) {
		error_log("CEquipUseProtocol decode fail");
		return false;
	}
	uint32_t uid = packet->uid;
	uint32_t equipId = protocol.equipId;
	uint32_t targetType = protocol.targetType;
	uint32_t targetUd = protocol.targetUd;
	uint32_t useCount = protocol.count;

	if (!useGiftBag(equipId, useCount, true)) {
		error_log("doItemEffect targetType=%u targetUd=%u uid=%u equipId=%u", targetType, targetUd, uid, equipId);
		return false;
	}

	CNetPacket sPacket;
	sPacket.uid = uid;
	CBufferWriter selfWriter(&sPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_EQUIPMENT);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_EQUIPMENT_USE);
	selfWriter.AppendByte(0);
	PlayerManager::getInstance()->sendToAccess(&sPacket);

	return true;
}

bool EquipmentManager::doGemInfo(CNetPacket *packet) {
	m_player->getGemManager()->push();
	return true;
}

bool EquipmentManager::doGemPoint(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CEquipGemPointProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", uid);
		return onGemPoint(0, R_ERROR);
	}

	//卸下
	if (proto.id == 0) {
		if(!m_player->getGemManager()->setPoint(proto.type, proto.point, proto.id)) {
			error_log("gem point error uid=%u id=%u", uid, proto.id);
			return onGemPoint(proto.type, R_ERROR);
		}
		onGemPoint(proto.type, R_SUCCESS);
		m_player->getGemManager()->push();
		error_log("uid=%u sid=%u p=%u id=%u", uid, proto.type, proto.point, proto.id);
		return true;
	}

	Equipment *eq = getEquipById(proto.id);
	if (eq == NULL) {
		error_log("gem error uid=%u id=%u", uid, proto.id);
		return onGemPoint(proto.type, R_ERROR);
	}
	if (eq->getLockCount() >= eq->getCount()) {
		error_log("gem count error uid=%u id=%u", uid, proto.id);
		return onGemPoint(proto.type, R_ERROR);
	}
	const EquipConfigItem *cfg = EquipmentConfig::getInstance()->getItemConfig(eq->getType());
	if (cfg == NULL) {
		error_log("cfg error uid=%u id=%u", uid, proto.id);
		return onGemPoint(proto.type, R_ERROR);
	}
	if (cfg->type != EQUIP_TYPE_GEM) {
		error_log("equip type error uid=%u id=%u type=%u", uid, proto.id, cfg->type);
		return onGemPoint(proto.type, R_ERROR);
	}
	if(!m_player->getGemManager()->setPoint(proto.type, proto.point, proto.id)) {
		error_log("gem point error uid=%u id=%u", uid, proto.id);
		return onGemPoint(proto.type, R_ERROR);
	}
	eq->setLockCount(eq->getLockCount() + 1);
	eq->saveData();

	onGemPoint(proto.type, R_SUCCESS);
	sendOneEquip(eq);
	m_player->getGemManager()->push();
	error_log("uid=%u sid=%u p=%u id=%u", uid, proto.type, proto.point, proto.id);
	return true;
}

bool EquipmentManager::doGemCombine(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CEquipGemCombineProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", uid);
		return onGemCombine(R_ERROR);
	}
	Equipment *eq = getEquipById(proto.id);
	if (eq == NULL) {
		error_log("get equip error uid=%u id=%u", uid, proto.id);
		return onGemCombine(R_ERROR);
	}
	const EquipConfigItem *cfg = EquipmentConfig::getInstance()->getItemConfig(eq->getType());
	if (cfg == NULL) {
		error_log("cfg error uid=%u id=%u", uid, proto.id);
		return onGemCombine(R_ERROR);
	}
	if (cfg->type != EQUIP_TYPE_GEM) {
		error_log("equip type error uid=%u id=%u type=%u", uid, proto.id, cfg->type);
		return onGemCombine(R_ERROR);
	}
	if (eq->getLockCount() >= eq->getCount()) {
		error_log("equip count error uid=%u id=%u", uid, proto.id);
		return onGemCombine(R_ERROR);
	}
	uint32_t c_num = proto.all == 1 ? (eq->getCount() - eq->getLockCount()) / 4 : 1;
	if (c_num == 0) {
		error_log("equip count error uid=%u id=%u all=%u", uid, proto.id, proto.all);
		return onGemCombine(R_ERROR);
	}
	if (eq->getLockCount() + c_num * 4 > eq->getCount()) {
		error_log("equip count error uid=%u id=%u all=%u", uid, proto.id, proto.all);
		return onGemCombine(R_ERROR);
	}
	uint32_t next_gem_id = EquipmentConfig::getInstance()->getGemId(cfg->gem_type, cfg->lv + 1);
	if (next_gem_id == 0) {
		error_log("next gem id error uid=%u id=%u", uid, proto.id);
		return onGemCombine(R_ERROR);
	}
	if (!useBagItemByType(eq->getType(), 4 * c_num, "gem_combine")) {
		error_log("user gem error uid=%u id=%u", uid, proto.id);
		return onGemCombine(R_ERROR);
	}
	addBagItem(next_gem_id, c_num, "gem_combine");
	onGemCombine(R_SUCCESS);
	return true;
}

bool EquipmentManager::doEquipCombine(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CEquipCombineProtocol proto;
	Award result;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", uid);
		return onEquipCombine(R_ERROR, 0, result);
	}
	const ShopChipItem *cfg = CShopConfig::getInstance()->getChip(proto.id);
	if (cfg == NULL) {
		error_log("cfg error uid=%u id=%u", uid, proto.id);
		return onEquipCombine(R_ERROR, 0, result);
	}
	Equipment *equip = getEquipById(cfg->equip);
	if (equip == NULL) {
		error_log("equip error uid=%u id=%u equipid=%u", uid, proto.id, cfg->equip);
		return onEquipCombine(R_ERROR, 0, result);
	}
	if (equip->getCount() < cfg->require) {
		error_log("equip count error uid=%u id=%u equipid=%u", uid, proto.id, cfg->equip);
		return onEquipCombine(R_ERROR, 0, result);
	}
	string code = "combine_soldier_" + CTrans::ITOS(proto.id);
	if(!useBagItemByType(equip->getType(), cfg->require, code)) {
		error_log("use equip error uid=%u id=%u equipid=%u", uid, proto.id, cfg->equip);
		return onEquipCombine(R_ERROR, 0, result);
	}
	AwardInfo rewardItem;
	rewardItem.type = AWARD_TYPE_SOLDIER;
	rewardItem.id = cfg->id;
	rewardItem.count = 1;
	Award reward;
	reward.add(rewardItem);
	m_player->doReward(&reward, code, false, &result);
	onEquipCombine(R_SUCCESS, AWARD_TYPE_SOLDIER, result);
	return true;
}

bool EquipmentManager::sendEquipmentList() {
	CNetPacket sRspPacket;
	sRspPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_EQUIPMENT);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_EQUIPMENTLIST);
	selfWriter.AppendUInt32(0);
	selfWriter.AppendUInt32(0);
	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket)) {
		error_log("sendAccess_fail&uid=%u", m_player->getUid());
		return false;
	}
	return true;
}

bool EquipmentManager::sendBagList() {
	CNetPacket sRspPacket;
	sRspPacket.uid = m_player->getUid();
	sRspPacket.cmd = PROTOCOL_CMD_EQUIPMENT;
	sRspPacket.subCmd = PROTOCOL_SUBCMD_BAGLIST;
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_EQUIPMENT);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_BAGLIST);
	selfWriter.AppendUInt32(m_bags.size());
	map<uint32_t, Equipment*>::iterator it;
	for (it = m_bags.begin(); it != m_bags.end(); it++) {
		it->second->encode(&sRspPacket.body);
	}
	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket)) {
		error_log("sendAccess_fail&uid=%u", m_player->getUid());
		return false;
	}
	return true;
}

bool EquipmentManager::sendOneEquip(Equipment *pEquip) {
	if (m_player == NULL) {
		error_log("m_player is NULL");
		return false;
	}
	if (pEquip == NULL) {
		error_log("pEquip is NULL");
		return false;
	}
	CNetPacket sPacket;
	sPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&sPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_EQUIPMENT);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_QUERY_ONE_EQUIPMENT);
	pEquip->encode(&sPacket.body);
	PlayerManager::getInstance()->sendToAccess(&sPacket);
	return true;
}

bool EquipmentManager::sendBagAdd(Equipment *pBag) {
	if (pBag == NULL) {
		error_log("pBag is NULL");
		return false;
	}
	CNetPacket sPacket;
	sPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&sPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_EQUIPMENT);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_BAG_ADD);
	pBag->encode(&sPacket.body);
	PlayerManager::getInstance()->sendToAccess(&sPacket);
	return true;
}

bool EquipmentManager::sendBagRemove(Equipment *pBag) {
	if (pBag == NULL) {
		error_log("pBag is NULL");
		return false;
	}
	CNetPacket sPacket;
	sPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&sPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_EQUIPMENT);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_BAG_REMOVE);
	selfWriter.AppendUInt32(pBag->getUD());
	PlayerManager::getInstance()->sendToAccess(&sPacket);
	return true;
}

bool EquipmentManager::sendCountChange(Equipment *pEquip) {
	if (pEquip == NULL) {
		error_log("pEquip is NULL");
		return false;
	}
	CNetPacket sPacket;
	sPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&sPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_EQUIPMENT);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_COUNT_CHANGE);
	selfWriter.AppendUInt32(pEquip->getUD());
	selfWriter.AppendUInt32(pEquip->getCount());
	PlayerManager::getInstance()->sendToAccess(&sPacket);
	return true;
}

bool EquipmentManager::addBagItem(uint32_t type, uint32_t count, const string &reason) {
	if (m_player == NULL) {
		error_log("m_player is NULL");
		return false;
	}
	uint32_t uid = m_player->getUid();
	if (count <= 0) {
		return true;
	}

	const EquipConfigItem * pEc = EquipmentConfig::getInstance()->getItemConfig(type);
	if (!pEc) {
		error_log("pEc is NULL");
		return false;
	}

	uint32_t eud = 0;
	map<uint32_t, Equipment*>::iterator itr = m_bags.begin();
	for (; itr != m_bags.end(); ++itr) {
		Equipment *pEquip = itr->second;
		if (pEquip == NULL) {
			continue;
		}
		if (pEquip->getType() == type) {
			pEquip->setCount(pEquip->getCount() + count);
			eud = pEquip->getUD();
			pEquip->saveData(false);
			sendCountChange(pEquip);
			BUSI_EQUIP("%u|%u|%u|%u|%u|%s|%u", uid, pEquip->getCount(), eud, type, count, reason.c_str(), LogicManager::GlobalTime);
			break;
		}
	}
	if (itr == m_bags.end()) {
		Equipment *pNew = getNewEquip(type, count);
		if (pNew != NULL) {
			eud = pNew->getUD();
			m_bags[eud] = pNew;
			pNew->saveData(true);
			sendBagAdd(pNew);
			BUSI_EQUIP("%u|%u|%u|%u|%u|%s|%u", uid, pNew->getCount(), eud, type, count, reason.c_str(), LogicManager::GlobalTime);
		}
	}
	if (pEc->type == EQUIP_TYPE_GEM) {
		m_player->setPropChange();
	}

	return true;
}

bool EquipmentManager::useBagItemByType(uint32_t equipId, uint32_t delCount, const string &reason) {
	if (m_player == NULL) {
		return false;
	}
	if (delCount == 0) {
		return false;
	}
	uint32_t uid = m_player->getUid();
	map<uint32_t, Equipment*>::iterator itr = m_bags.begin();
	for (; itr != m_bags.end(); ++itr) {
		Equipment *peq = itr->second;
		if (peq == NULL || peq->getType() != equipId) {
			continue;
		}
		uint32_t eud = peq->getUD();
		uint32_t holdCount = peq->getCount();
		if (holdCount == delCount) {
			CDataEquipment dbData;
			if (dbData.RemoveOneEquipment(uid, eud) != 0) {
				error_log("RemoveOneEquipment fail uid=%u ud=%u", peq->getUid(), eud);
			}
			sendBagRemove(peq);
			m_bags.erase(itr);
			BUSI_EQUIP("%u|%u|%u|%u|%d|%s|%u", uid, 0, eud, equipId, 0 - delCount, reason.c_str(), LogicManager::GlobalTime);
			delete peq;
		} else if (holdCount > delCount) {
			peq->setCount(holdCount - delCount);
			sendCountChange(peq);
			peq->saveData(false);
			BUSI_EQUIP("%u|%u|%u|%u|%d|%s|%u", uid, peq->getCount(), eud, equipId, 0 - delCount, reason.c_str(), LogicManager::GlobalTime);
		} else {
			error_log("checkItemEnough fail uid=%u equipType=%u delCount=%u", uid, equipId, delCount);
			return false;
		}
		break;
	}
	return true;
}

bool EquipmentManager::useGiftBag(uint32_t equipId, uint32_t count, bool bag) {
	if (m_player == NULL || count == 0) {
		return false;
	}
	uint32_t uid = m_player->getUid();
	Award award;
	GiftBagConfig::getInstance()->openAllLuckyBox(equipId, count, award);
	string code;
	String::Format(code, "use_equip_bag_%u", equipId);
	if (bag && !checkItemEnough(equipId, count)) {
		return false;
	}
	if (bag && !useBagItemByType(equipId, count, code)) {
		error_log("useBagItemByUd fail uid=%u equipId=%u", uid, equipId);
		return false;
	}
	Award awardResult;
	if (!m_player->doReward(&award, code, false, &awardResult)) {
		return false;
	}

	Award sysAward;
	vector<AwardInfo>::const_iterator sysItr = awardResult.get().begin();
	for (; sysItr != awardResult.get().end(); ++sysItr) {
		if (sysItr->type == AWARD_TYPE_SOLDIER) {
			const SoldierItemConfig *cfg = SoldierConfig::getInstance()->getItemConfig(sysItr->id);
			if (cfg != NULL && cfg->q >= 3) {
				sysAward.add(*sysItr);
			}
		} else if (sysItr->type == AWARD_TYPE_SKILL) {
			const SkillConfig *cfg = CSkillConfig::getInstance()->getConfig(sysItr->id);
			if (cfg != NULL && cfg->q >= 3) {
				sysAward.add(*sysItr);
			}
		}
	}

	if (!sysAward.get().empty()) {
		SystemMessage::getInstance()->addBuyBag(m_player->getUid(), equipId, &sysAward);
	}

	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter bWriter(&(sp.body));
	bWriter.AppendByte(PROTOCOL_CMD_EQUIPMENT);
	bWriter.AppendByte(PROTOCOL_SUBCMD_EQUIP_GIFT_REWARD);
	bWriter.AppendUInt32(equipId);
	bWriter.AppendUInt32(count);
	vector<AwardInfo> &awardList = awardResult.get();
	bWriter.AppendUInt32(awardList.size());
	for (vector<AwardInfo>::iterator it = awardList.begin(); it != awardList.end(); ++it) {
		bWriter.AppendByte(it->type);
		bWriter.AppendUInt32(it->id);
		bWriter.AppendUInt32(it->count);
	}
	PlayerManager::getInstance()->sendToAccess(&sp);

	return true;}

bool EquipmentManager::checkItemEnough(uint32_t equipType, uint32_t useCount) {
	if (m_player == NULL) {
		error_log("m_player is NULL");
		return false;
	}
	uint32_t leftCount = getItemCount(equipType);
	if (leftCount < useCount) {
		return false;
	}
	return true;
}

Equipment* EquipmentManager::getNewEquip(uint32_t type, uint32_t count) {
	Equipment * pNew = new Equipment();
	if (pNew) {
		pNew->setUid(m_player->getUid());
		pNew->setType(type);
		pNew->setCount(count);
		pNew->setUD(++m_maxUd);
		pNew->setStatus(0);
		return pNew;
	} else {
		return NULL;
	}
}

Equipment* EquipmentManager::getEquipById(uint32_t type) {
	map<uint32_t, Equipment*>::iterator itr = m_bags.begin();
	for (; itr != m_bags.end(); ++itr) {
		Equipment *p = itr->second;
		if (p == NULL) {
			continue;
		}
		if (p->getType() == type) {
			return p;
		}
	}
	return NULL;
}

uint32_t EquipmentManager::getItemCount(uint32_t type) {
	uint32_t count = 0;
	map<uint32_t, Equipment*>::iterator it;
	for (it = m_bags.begin(); it != m_bags.end(); it++) {
		Equipment * pEquip = it->second;
		if (pEquip != NULL && pEquip->getType() == type) {
			count += pEquip->getCount();
		}
	}
	return count;
}

bool EquipmentManager::subGemLockCount(uint32_t type, uint32_t cnt) {
	Equipment *equip = getEquipById(type);
	if (equip == NULL) {
		return false;
	}
	uint32_t now = equip->getLockCount() > cnt ? equip->getLockCount() - cnt : 0;
	equip->setLockCount(now);
	equip->saveData();
	sendOneEquip(equip);
	return true;
}

bool EquipmentManager::checkGemLockCount() {
	map<uint32_t, Equipment*>::iterator itr = m_bags.begin();
	for (; itr != m_bags.end(); ++itr) {
		Equipment *data = itr->second;
		if (data == NULL) {
			continue;
		}
		if (data->getLockCount() > 0) {
			uint32_t n = m_player->getGemManager()->getCount(data->getType());
			if (n != data->getLockCount()) {
				data->setLockCount(n);
				data->saveData(false);
			}
		}
	}
	return true;
}

uint32_t EquipmentManager::calcGemPower() {
	uint32_t power = 0;
	map<uint32_t, Equipment*>::iterator itr = m_bags.begin();
	for (; itr != m_bags.end(); ++itr) {
		Equipment *data = itr->second;
		if (data == NULL) {
			continue;
		}
		const EquipConfigItem *cfg = EquipmentConfig::getInstance()->getItemConfig(data->getType());
		if (cfg == NULL) {
			continue;
		}
		if (cfg->power == 0) {
			continue;
		}
		power += cfg->power * data->getCount();
	}
	return power;
}
