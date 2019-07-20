/*
 * UpdateManager.cpp
 *
 *  Created on: 2019年6月25日
 *      Author: Administrator
 */

#include "UpdateManager.h"
#include "BattleInc.h"

UpdateManager::UpdateManager() {
	m_code = UC_Unknow;
}

UpdateManager::~UpdateManager() {

}

bool UpdateManager::SetCode(int16_t code) {
	if (code >= UC_CODE_MAX || code < UC_Unknow) {
		m_code = UC_Unknow;
	} else {
		m_code = code;
	}
	return true;
}

bool UpdateManager::Money(uint32_t uid, uint32_t item, int32_t chg, uint32_t curr) {
	msgs::SPlayerMoneyOperList &msg = m_moneys[uid];
	msgs::SPlayerMoneyOper op;
	op.moneyId_ = item;
	if (chg < 0) {
		op.operNum_ = 0 - chg;
		op.operType_ = MONEY_SUB;
	} else if (chg > 0) {
		op.operNum_ = chg;
		op.operType_ = MONEY_ADD;
	} else {
		op.operNum_ = 0;
		op.operType_ = MONEY_SET;
	}
	op.moneyNum_ = curr;
	msg.opers_.push_back(op);
	msg.updateCode_ = m_code;
	return true;
}

bool UpdateManager::Bag(uint32_t uid, int32_t chg, const DataEquip &data) {
	msgs::SPlayerBagItemOperList &msg = m_bags[uid];
	msgs::SPlayerBagItemOper op;
	op.clear();
	if (chg < 0) {
		op.operNum_ = 0 - chg;
		if (data.num == 0) {
			op.operType_ = ITEM_DEL;
		} else {
			op.operType_ = ITEM_SET;
		}
	} else if (chg > 0) {
		op.operNum_ = chg;
		op.operType_ = ITEM_ADD;
	} else {
		op.operNum_ = data.num;
		op.operType_ = ITEM_SET;
	}
	op.item_.itemUid_ = data.ud;
	op.item_.itemId_ = data.id;
	op.item_.itemNum_ = data.num;
	op.item_.bagType_ = data.bag;
	op.item_.extend_ = data.ext;
	op.item_.createDt_ = data.ts * 1000LL;
	msg.opers_.push_back(op);
	msg.updateCode_ = m_code;
	return true;
}

bool UpdateManager::DelBag(uint32_t uid, int32_t num, const DataEquip &data) {
	msgs::SPlayerBagItemOperList &msg = m_bags[uid];
	msgs::SPlayerBagItemOper op;
	op.clear();
	op.operType_ = ITEM_DEL;
	op.operNum_ = num;
	op.item_.itemUid_ = data.ud;
	op.item_.itemId_ = data.id;
	op.item_.itemNum_ = data.num;
	op.item_.bagType_ = data.bag;
	op.item_.extend_ = data.ext;
	op.item_.createDt_ = data.ts * 1000LL;
	msg.opers_.push_back(op);
	msg.updateCode_ = m_code;
	return true;
}

bool UpdateManager::ChgBag(uint32_t uid, int16_t from, int16_t to, const DataEquip &data) {
	msgs::SPlayerBagItemOperList &msg = m_bags[uid];
	msgs::SPlayerBagItemOper op;
	op.clear();
	op.operNum_ = data.num;
	op.operType_ = ITEM_DEL;
	op.item_.itemUid_ = data.ud;
	op.item_.itemId_ = data.id;
	op.item_.itemNum_ = 0;
	op.item_.bagType_ = from;
	op.item_.extend_ = data.ext;
	op.item_.createDt_ = data.ts * 1000LL;
	msg.opers_.push_back(op);

	op.operType_ = ITEM_ADD;
	op.item_.itemNum_ = data.num;
	op.item_.bagType_ = to;
	msg.opers_.push_back(op);

	msg.updateCode_ = m_code;
	return true;
}

bool UpdateManager::BagExtend(uint32_t uid, const DataBagExtend &data) {
	msgs::SPlayerBag &msg = m_bag_ext[uid];
	msg.clear();
	msg.type_ = data.bag;
	msg.extendNum_ = data.num;
	return true;
}

bool UpdateManager::Advance(uint32_t uid, const DataAdvance &data) {
	const CfgAdvance::Advance &cfg = AdvanceCfgWrap().Get(data.type, data.level, data.star);
	msgs::SAdvanceUpdate &msg = m_advances[uid];
	msg.type_ = data.type;
	msg.roleId_ = data.rid;
	msg.star_ = data.star;
	msg.level_ = data.level;
	msg.lastDayLevel_ = data.last_level;
	msg.bless_ = data.bless;
	msg.tmpBless_ = data.tmp_bless;
	msg.modelId_ = cfg.mode();
	return true;
}

bool UpdateManager::AdvanceDan(uint32_t uid, const DataAdvance &data, uint32_t id) {
	const uint16_t *ptr = data.GetDan(id);
	if (ptr == NULL) {
		return false;
	}
	msgs::SAdvanceDanUpdate &msg = m_advance_dans[uid];
	msg.roleId_ = data.rid;
	msg.type_ = data.type;
	msg.danType_ = id;
	msg.num_ = *ptr;
	return true;
}

bool UpdateManager::Treasure(uint32_t uid, const DataTreasure &data) {
	uint32_t id = TreasureCfgWrap().GetIdByType(data.type, data.level, data.star);
	const CfgTreasure::Treasure& cfg = TreasureCfgWrap().GetById(id);
	msgs::STreasureAdvanceSingle &msg = m_treasure[uid];
	msg.type_ = data.type;
	msg.level_ = data.level;
	msg.star_ = data.star;
	msg.bless_ = data.bless;
	for(int i = 0; i < cfg.dans().dans_size(); ++i) {
		uint32_t id = TreasureCfgWrap().GetDanId(data.type, data.level, data.star, i);
		const uint16_t *ptr = data.GetDan(i);
		if(ptr != NULL && *ptr > 0) {
			msg.danMap_.insert(make_pair(id, *ptr));
		}
	}
	return true;
}

bool UpdateManager::ActiveSuit(uint32_t uid, uint32_t roleId, uint32_t suitId, vector<uint32_t> & slots) {
	msgs::SPlayerActiveSuitCollect &msg = m_active_suit[uid];
	msg.roleId_ = roleId;
	msg.suitId_ = suitId;
	for(uint32_t i = 0; i < slots.size(); ++i) {
		msg.activeSlots_.push_back(slots[i]);
	}
	return true;
}

bool UpdateManager::roleUnlock(uint32_t uid, uint32_t roleId, uint32_t suitId) {
	msgs::SPlayerUnlockSuitCollect &msg_unlock = m_role_unlock[uid];
	msg_unlock.roleId_ = roleId;
	msg_unlock.suitId_ = suitId;
	return true;
}

bool UpdateManager::roleDress(uint32_t uid, uint32_t roleId, uint32_t suitId) {
	msgs::SPlayerDressSuitCollect &msg_dress = m_role_dress[uid];
	msg_dress.roleId_ = roleId;
	msg_dress.dressSuitId_ = suitId;
	return true;
}

bool UpdateManager::roleSkills(uint32_t uid, const CfgSuit::Suit& suit, uint32_t oper, uint32_t roleId) {
	msgs::SUpdateSkill& msg = m_role_skills[uid];
	msg.oper_ = oper;
	RoleSuitManager::Instance()->FormatSkills(uid, roleId, suit, msg.skills_);
	return true;
}

bool UpdateManager::roleTitle(uint32_t uid, uint32_t roleId, uint32_t titleId) {
	msgs::SIntIntMap& msg = m_role_title[uid];
	msg.maps_[roleId] = titleId;
	return true;
}

// 服务器回复称号激活
bool UpdateManager::S2CPlayerTitle(uint32_t uid,  uint32_t titleId) {
	msgs::SPlayerTitle& msg = m_player_title[uid];
	msg.titleId_ = titleId;
	const CfgTitle::Title &cfg = TitleCfgWrap().Get(titleId);// 通过id去获取单条数据
	msg.indateTime_ = cfg.limit_time(); //称号限时
	return true;
}


bool UpdateManager::roleShows(uint32_t uid, uint32_t modeId, uint32_t isDress, uint32_t showId) {
	msgs::SEntityUpdateEntityShows& msg = m_role_shows[uid];
	Human *pHuman = MapManager::Instance()->getHuman(uid);
	if(NULL == pHuman) {
		error_log("pHuman ptr error");
		return false;
	}
	msg.entityId_ = pHuman->getEntityMsg();
	if(isDress) {
		pHuman->setShow(showId, modeId);
	} else {
		pHuman->setShow(showId, 0);
	}

	pHuman->getShow(msg.shows_);
	return true;
}



bool UpdateManager::Send(uint32_t uid) {
	map<uint32_t, msgs::SPlayerMoneyOperList>::iterator moneyItr = m_moneys.find(uid);
	if (moneyItr != m_moneys.end()) {
		LogicManager::Instance()->SendMsg(uid, CMD_PLAYER_MONEY_OPER_LIST, &(moneyItr->second));
		m_moneys.erase(moneyItr);
	}

	map<uint32_t, msgs::SPlayerBagItemOperList>::iterator bagItr = m_bags.find(uid);
	if (bagItr != m_bags.end()) {
		LogicManager::Instance()->SendMsg(uid, CMD_PLAYER_BAG_ITEM_OPER_LIST, &(bagItr->second));
		m_bags.erase(bagItr);
	}

	map<uint32_t, msgs::SPlayerBag>::iterator bagExtitr = m_bag_ext.find(uid);
	if (bagExtitr != m_bag_ext.end()) {
		LogicManager::Instance()->SendMsg(uid, CMD_UPDATE_PLAYER_BAG, &(bagExtitr->second));
		m_bag_ext.erase(bagExtitr);
	}

	map<uint32_t, msgs::SAdvanceUpdate>::iterator advanceItr = m_advances.find(uid);
	if (advanceItr != m_advances.end()) {
		LogicManager::Instance()->SendMsg(uid, CMD_PLAYER_UPDATE_ADVANCE, &(advanceItr->second));
		m_advances.erase(advanceItr);
	}

	map<uint32_t, msgs::SAdvanceDanUpdate>::iterator advanceDanItr = m_advance_dans.find(uid);
	if (advanceDanItr != m_advance_dans.end()) {
		LogicManager::Instance()->SendMsg(uid, CMD_PLAYER_UPDATE_ADVANCE_DAN, &(advanceDanItr->second));
		m_advance_dans.erase(advanceDanItr);
	}

	map<uint32_t, msgs::STreasureAdvanceSingle>::iterator treasureItr = m_treasure.find(uid);
	if (treasureItr != m_treasure.end()) {
		LogicManager::Instance()->SendMsg(uid, CMD_TREASURE_ADVANCE_SINGLE_INFO, &(treasureItr->second));
		m_treasure.erase(treasureItr);
	}

	map<uint32_t, msgs::SPlayerActiveSuitCollect>::iterator active_suit = m_active_suit.find(uid);
	if (active_suit != m_active_suit.end()) {
		LogicManager::Instance()->SendMsg(uid, CMD_PLAYER_ACTIVE_SUIT_COLLECT, &(active_suit->second));
		m_active_suit.erase(active_suit);
	}

	map<uint32_t, msgs::SPlayerUnlockSuitCollect>::iterator role_unlock = m_role_unlock.find(uid);
	if (role_unlock != m_role_unlock.end()) {
		LogicManager::Instance()->SendMsg(uid, CMD_PLAYER_UNLOCK_SUIT_COLLECT, &(role_unlock->second));
		m_role_unlock.erase(role_unlock);
	}

	map<uint32_t, msgs::SPlayerDressSuitCollect>::iterator role_dress = m_role_dress.find(uid);
	if (role_dress != m_role_dress.end()) {
		LogicManager::Instance()->SendMsg(uid, CMD_PLAYER_DRESS_SUIT_COLLECT, &(role_dress->second));
		m_role_dress.erase(role_dress);
	}

	map<uint32_t, msgs::SUpdateSkill>::iterator role_skills = m_role_skills.find(uid);
	if (role_skills != m_role_skills.end()) {
		LogicManager::Instance()->SendMsg(uid, CMD_PLAYER_SKILL_UPDATE, &(role_skills->second));
		m_role_skills.erase(role_skills);
	}

	map<uint32_t, msgs::SEntityUpdateEntityShows>::iterator role_shows = m_role_shows.find(uid);
	if (role_shows != m_role_shows.end()) {
		LogicManager::Instance()->SendMsg(uid, CMD_PLAYER_UPDATE_ENTITY_SHOWS, &(role_shows->second));
		m_role_shows.erase(role_shows);
	}

	map<uint32_t, msgs::SIntIntMap>::iterator role_titles = m_role_title.find(uid);
	if (role_titles != m_role_title.end()) {
		LogicManager::Instance()->SendMsg(uid, CMD_PLAYER_WEAR_TITLE, &(role_titles->second));
		m_role_title.erase(role_titles);
	}

	map<uint32_t, msgs::SPlayerTitle>::iterator player_titles = m_player_title.find(uid);
	if (player_titles != m_player_title.end()) {
		LogicManager::Instance()->SendMsg(uid, CMD_PLAYER_UPDATE_TITLE, &(player_titles->second));
		m_player_title.erase(player_titles);
	}


	return true;
}
