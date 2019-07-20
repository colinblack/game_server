/*
 * CardManager.cpp
 *
 *  Created on: 2019年6月27日
 *      Author: Administrator
 */

#include "CardManager.h"
#include "BattleInc.h"

CardManager::CardManager() {
}

CardManager::~CardManager() {
}

bool CardManager::CalcProperty(const UserCache &cache, byte rid, PropertySets &props) {
	try {
		CardCfgWrap cfg_wrap;
		CardGroupWrap	group_wrap;
		const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->card_attr_cfg_Index;
		const map<uint32_t, uint32_t> &groupIndexs = ConfigManager::Instance()->card_group_cfg_Index;
		map<uint32_t,uint32_t>::const_iterator it;
		//已经激活的属性
		for(map<uint32_t, CardInfo>::const_iterator it = cache.m_cards.begin();it!= cache.m_cards.end();it++){
			for(uint32_t i=0;i<20;i++){
				if(GET_BIT(it->second.activeIndex,i)){
					map<uint32_t, uint32_t>::const_iterator itr = indexs.find(it->second.startId+i);
					if (itr == indexs.end()) {
						error_log("id not exists rid=%u id=%u", rid, it->second.startId+i);
						continue;
					}
					const CfgCard::Card &cfg = cfg_wrap.GetCard(it->second.startId+i);
					PropertyCfg::setProps(cfg.attr(), 1.0, props);
					PropertyCfg::setProps(cfg.exattr(), 1.0, props);
				}
			}
		}

		//套装属性
		for(map<uint32_t, CardInfo>::const_iterator it = cache.m_cards.begin();it!= cache.m_cards.end();it++){
			uint32_t count =0;
			for(uint32_t i=0;i<20;i++){
				if(GET_BIT(it->second.activeIndex,i)){
					count++;
				}
			}
			for(uint32_t j=1;j<5;j++){
				uint32_t key = CFG_MAKE_KEY(it->second.id,j);
				map<uint32_t, uint32_t>::const_iterator its = groupIndexs.find(key);
				if (its == groupIndexs.end()) {
					error_log("group not exists rid=%u id=%u", rid, key);
					continue;
				}
				const CfgCard::CardGroup& group =  group_wrap.GetCardGroup(key);
				if(count>=group.neednum()){
					PropertyCfg::setProps(group.attr(), 1.0, props);
				}
			}
		}
	} catch (...) {
		return false;
	}
	PropertyCfg::showProps(cache.uid_, rid, props, "card");
	return true;
}


int CardManager::Process(uint32_t uid, card::CSCardActiveCard *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	UpdateManager::Instance()->SetCode(UC_MoveItem);

	map<uint32_t, DataEquip>::iterator it = cache.equip_.find(req->uid);
	if(it== cache.equip_.end()){
		error_log("ud= %d not exists in bag uid=%u ", req->uid, uid);
		return R_ERROR;
	}
	uint32_t itemId = it->second.id;
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->card_attr_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(itemId);
	if (itr == indexs.end()) {
		error_log("id not exists uid=%u id=%u", uid, itemId);
		return R_ERROR;
	}
	if(it->second.num==1){
		it->second.bag = BAG_CARD;
		DataEquipManager::Instance()->Set(it->second);
		UpdateManager::Instance()->ChgBag(uid, BAG_ALL, BAG_CARD, it->second);
	}
	else{
		it->second.num--;
		DataEquip equipTmp = it->second;
		equipTmp.num =1;
		equipTmp.bag = BAG_CARD;
		uint32_t ud =1;
		if (!cache.equip_.empty()) {
			ud = cache.equip_.rbegin()->first + 1;
		}
		equipTmp.ud=ud;
		DataEquipManager::Instance()->Set(it->second);
		DataEquipManager::Instance()->Add(equipTmp);
		cache.equip_[equipTmp.ud] = equipTmp;
		UpdateManager::Instance()->ChgBag(uid, BAG_ALL, BAG_CARD, it->second);
	}
	CardSuitWrap cfg_wrap;
	const CfgCard::Suit &cfg = cfg_wrap.GetSuitByCard(itemId);
	uint32_t suitId = cfg.id();
	uint32_t startId = cfg.include(0);
	if(itemId-startId>20){
		return R_ERROR;
	}
	map<uint32_t, CardInfo>::iterator its = cache.m_cards.find(suitId);
	DataAttr attr;
	if(its==cache.m_cards.end()){
		CardInfo tmpInfo;
		tmpInfo.uid = uid;
		tmpInfo.type = TYPE_ATTR_CARD;
		tmpInfo.id = suitId;
		tmpInfo.startId = startId;
		SET_BIT(tmpInfo.activeIndex,(itemId-startId));
		cache.m_cards.insert(make_pair(tmpInfo.id,tmpInfo));
		memcpy((void*)&attr,(const void*)&tmpInfo,sizeof(DataAttr));
		DataAttrManager::Instance()->Add(attr);
	}else{
		if(GET_BIT(its->second.activeIndex,(itemId-startId))){
			error_log("id has activated uid=%u id=%u", uid, itemId);
			return R_ERROR;
		}
		SET_BIT(its->second.activeIndex,(itemId-startId));
		memcpy((void*)&attr,(const void*)&its->second,sizeof(DataAttr));
		DataAttrManager::Instance()->Set(attr);
	}
	LogicManager::Instance()->AddSync(CMD_PLAYER_CARDGROUP);
	PropertyManager::Instance()->AddUser(uid);
	return 0;
}


int CardManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SCardGroup *resp) {
	uint32_t  count ;
	for(map<uint32_t, CardInfo>::const_iterator it = cache.m_cards.begin();it!= cache.m_cards.end();it++){
		count =0;
		for(uint32_t i=0;i<20;i++){
			if(GET_BIT(it->second.activeIndex,i)){
				count++;
			}
		}
		if(count){
			resp->activeNum_.insert((make_pair(it->second.id,count)));
		}
	}
	LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp);
	return 0;
}
