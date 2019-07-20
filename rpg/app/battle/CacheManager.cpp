/*
 * CacheManager.cpp
 *
 *  Created on: 2019年6月21日
 *      Author: Administrator
 */

#include "CacheManager.h"

CacheManager::CacheManager() {
}

CacheManager::~CacheManager() {
}

bool CacheManager::ActorLogin(uint32_t uid) {
	m_offline.erase(uid);

	map<uint32_t, UserCache>::iterator itr = m_mapUser.find(uid);
	if (itr != m_mapUser.end() && itr->second.init_) {
		return true;
	}

	UserCache &cache = m_mapUser[uid];
	cache.uid_ = uid;
	if (!LoadBase(cache)) {
		return false;
	}
	if (!LoadPay(cache)) {
		return false;
	}
	if (!LoadPos(cache)) {
		return false;
	}
	if (!LoadRole(cache)) {
		return false;
	}
	if (!LoadSkill(cache)) {
		return false;
	}
	if (!LoadMission(cache)) {
		return false;
	}
	if (!LoadAdvance(cache)) {
		return false;
	}
	if (!LoadEquip(cache)) {
		return false;
	}
	if (!LoadShenQi(cache)) {
		return false;
	}
	if (!LoadBagExtend(cache)) {
		return false;
	}
	if (!LoadTreasure(cache)) {
		return false;
	}
	if (!LoadForge(cache)) {
		return false;
	}
	if (!LoadAttr(cache)) {
		return false;
	}
	if (!LoadRoleSuit(cache)) {
		return false;
	}
	if (!LoadActive(cache)) {
		return false;
	}

	cache.init_ = true;
	debug_log("cache init uid=%u", uid);
	return true;
}

bool CacheManager::ActorOffline(uint32_t uid) {
	UserCache &cache = m_mapUser[uid];
	cache.base_.offline_time =
	DataBaseManager::Instance()->Set(cache.base_);
	m_offline[uid] = Time::GetGlobalTime();
	return true;
}

void CacheManager::OnSecondTimer() {
	map<uint32_t, uint32_t>::iterator itr = m_offline.begin();
	while (itr != m_offline.end()) {
		if (itr->second < USER_CACHE_TS) {
			++itr;
			continue;
		}
		m_mapUser.erase(itr->first);
		m_offline.erase(itr++);
	}
}

UserCache& CacheManager::GetUser(uint32_t uid) {
	UserCache &cache = m_mapUser[uid];
	cache.uid_ = uid;
	return cache;
}

bool CacheManager::LoadBase(UserCache &cache) {
	int ret = DataBaseManager::Instance()->Get(cache.uid_, cache.base_);
	if (0 != ret && R_ERR_NO_DATA != ret) {
		error_log("load base error ret=%d uid=%u", ret, cache.uid_);
		return false;
	}
	return true;
}

bool CacheManager::LoadPay(UserCache &cache) {
	cache.pay_.clear();
	vector<DataPay> datas;
	int ret = DataPayManager::Instance()->Get(cache.uid_, datas);
	if (0 != ret && R_ERR_NO_DATA != ret) {
		error_log("load pay error ret=%d uid=%u", ret, cache.uid_);
		return false;
	}
	vector<DataPay>::iterator itr = datas.begin();
	for (; itr != datas.end(); ++itr) {
		cache.pay_[itr->id] = *itr;
	}
	return true;
}

bool CacheManager::LoadPos(UserCache &cache) {
	int ret = DataPosManager::Instance()->Get(cache.uid_, cache.pos_);
	if (0 != ret && R_ERR_NO_DATA != ret) {
		error_log("load pos error ret=%d uid=%u", ret, cache.uid_);
		return false;
	}
	return true;
}

bool CacheManager::LoadRole(UserCache &cache) {
	cache.role_.clear();
	vector<DataRole> datas;
	int ret = DataRoleManager::Instance()->Get(cache.uid_, datas);
	if (0 != ret && R_ERR_NO_DATA != ret) {
		error_log("load role error ret=%d uid=%u", ret, cache.uid_);
		return false;
	}
	vector<DataRole>::iterator itr = datas.begin();
	for (; itr != datas.end(); ++itr) {
		cache.role_[itr->id] = *itr;
	}
	return true;
}

bool CacheManager::LoadSkill(UserCache &cache) {
	cache.skill_.clear();
	vector<DataSkill> datas;
	int ret = DataSkillManager::Instance()->Get(cache.uid_, datas);
	if (0 != ret && R_ERR_NO_DATA != ret) {
		error_log("load skill error ret=%d uid=%u", ret, cache.uid_);
		return false;
	}
	vector<DataSkill>::iterator itr = datas.begin();
	for (; itr != datas.end(); ++itr) {
		cache.skill_.push_back(*itr);
	}
	return true;
}

bool CacheManager::LoadMission(UserCache &cache) {
	cache.mission_.clear();
	vector<DataMission> datas;
	int ret = DataMissionManager::Instance()->Get(cache.uid_, datas);
	if (0 != ret && R_ERR_NO_DATA != ret) {
		error_log("load mission error ret=%d uid=%u", ret, cache.uid_);
		return false;
	}
	vector<DataMission>::iterator itr = datas.begin();
	for (; itr != datas.end(); ++itr) {
		cache.mission_[itr->id] = *itr;
	}
	return true;
}

bool CacheManager::LoadAdvance(UserCache &cache) {
	cache.advance_.clear();
	vector<DataAdvance> datas;
	int ret = DataAdvanceManager::Instance()->Get(cache.uid_, datas);
	if (0 != ret && R_ERR_NO_DATA != ret) {
		error_log("load advance error ret=%d uid=%u", ret, cache.uid_);
		return false;
	}
	vector<DataAdvance>::iterator itr = datas.begin();
	for (; itr != datas.end(); ++itr) {
		cache.advance_.push_back(*itr);
	}
	return true;
}

bool CacheManager::LoadEquip(UserCache &cache) {
	cache.equip_.clear();
	vector<DataEquip> datas;
	int ret = DataEquipManager::Instance()->Get(cache.uid_, datas);
	if (0 != ret && R_ERR_NO_DATA != ret) {
		error_log("load equip error ret=%d uid=%u", ret, cache.uid_);
		return false;
	}
	vector<DataEquip>::iterator itr = datas.begin();
	for (; itr != datas.end(); ++itr) {
		cache.equip_[itr->ud] = *itr;
	}
	return true;
}

bool CacheManager::LoadShenQi(UserCache &cache) {
	int ret = DataShenQiManager::Instance()->Get(cache.uid_, cache.shenqi_);
	if (0 != ret && R_ERR_NO_DATA != ret) {
		error_log("load shen qi error ret=%d uid=%u", ret, cache.uid_);
		return false;
	}
	return true;
}

bool CacheManager::LoadBagExtend(UserCache &cache) {
	cache.bag_extend_.clear();
	vector<DataBagExtend> datas;
	int ret = DataBagExtendManager::Instance()->Get(cache.uid_, datas);
	if (0 != ret && R_ERR_NO_DATA != ret) {
		error_log("load bag extend error ret=%d uid=%u", ret, cache.uid_);
		return false;
	}
	vector<DataBagExtend>::iterator itr = datas.begin();
	for (; itr != datas.end(); ++itr) {
		cache.bag_extend_[itr->bag] = *itr;
	}
	return true;
}

bool CacheManager::LoadTreasure(UserCache &cache) {
	cache.treasure_.clear();
	vector<DataTreasure> datas;
	int ret = DataTreasureManager::Instance()->Get(cache.uid_, datas);
	if (0 != ret && R_ERR_NO_DATA != ret) {
		error_log("load Treasure error ret=%d uid=%u", ret, cache.uid_);
		return false;
	}
	vector<DataTreasure>::iterator it = datas.begin();
	for (; it != datas.end(); ++it) {
		cache.treasure_[it->type] = *it;
	}
	return true;
}

bool CacheManager::LoadForge(UserCache &cache) {
	cache.forge_.clear();
	vector<DataForge> datas;
	int ret = DataForgeManager::Instance()->Get(cache.uid_, datas);
	if (0 != ret && R_ERR_NO_DATA != ret) {
		error_log("load strength error ret=%d uid=%u", ret, cache.uid_);
		return false;
	}
	vector<DataForge>::iterator itr = datas.begin();
	for (; itr != datas.end(); ++itr) {
		cache.forge_.push_back(*itr);
	}
	return true;
}

bool CacheManager::LoadAttr(UserCache &cache) {
	vector<DataAttr> datas;
	int ret = DataAttrManager::Instance()->Get(cache.uid_, datas);
	if (0 != ret && R_ERR_NO_DATA != ret) {
		error_log("load attr error ret=%d uid=%u", ret, cache.uid_);
		return false;
	}
	for (uint32_t i = 0; i < datas.size(); i++) {
		if (datas[i].type == TYPE_ATTR_CARD) {
			CardInfo cardInfo;
			memcpy((void*)&cardInfo,(const void*)&datas[i],sizeof(DataAttr));
			cache.m_cards.insert(make_pair(cardInfo.id,cardInfo));
		}
		else if(datas[i].type ==TYPE_ATTR_REINCARN){
			memcpy((void*)&cache.m_reinCarnInfo,(const void*)&datas[i],sizeof(DataAttr));
		}
		else if(datas[i].type ==TYPE_ATTR_COPY){
			CopyInfo copyInfo;
			memcpy((void*)&copyInfo,(const void*)&datas[i],sizeof(DataAttr));
			cache.m_copyInfo.insert(make_pair(copyInfo.id,copyInfo));
		}else if (datas[i].type == TYPE_ATTR_TREASURE_HUNT) {
			TreasureHunt draw;
			draw.FromAttr(datas[i]);
			cache.m_treasure_hunt[draw.id] = draw;
		}
		else if(datas[i].type == TYPE_ATTR_ACTIVITY_INFO) {
			DataActivity act_info;
			memcpy((void*)&act_info, (const void*)&datas[i], sizeof(DataAttr));
			cache.act_info_.insert(make_pair(act_info.id, act_info));
		}
		else if(datas[i].type == TYPE_ATTR_ACT_CNT) {
			DataActivity act_cnt;
			memcpy((void*)&act_cnt, (const void*)&datas[i], sizeof(DataAttr));
			cache.act_cnt_.insert(make_pair(act_cnt.id, act_cnt));
		}
	}
	return true;
}

bool CacheManager::LoadRoleSuit(UserCache &cache) {
	vector<DataRoleAttr> datas;
	int ret = DataRoleAttrManager::Instance()->Get(cache.uid_, datas);
	if (0 != ret && R_ERR_NO_DATA != ret) {
		error_log("load role attr error ret=%d uid=%u", ret, cache.uid_);
		return false;
	}

	for(uint32_t i=0;i<datas.size();i++){
		if(datas[i].type ==TYPE_ROLE_SUIT){
			DataRoleSuit RoleSuit;
			memcpy((void*)&RoleSuit,(const void*)&datas[i],sizeof(DataRoleAttr));
			cache.role_suit_[RoleSuit.rid].insert(make_pair(RoleSuit.id, RoleSuit));
		}
		if(datas[i].type ==TYPE_ROLE_RUNE){
			DataRoleRune runeInfo;
			memcpy((void*)&runeInfo,(const void*)&datas[i],sizeof(DataRoleAttr));
			cache.m_runeInfo.insert(make_pair(runeInfo.rid, runeInfo));
		}
		if(datas[i].type ==TYPE_ROLE_TITLE){
			DataTitle titleInfo;
			memcpy((void*)&titleInfo,(const void*)&datas[i],sizeof(DataTitle));
			cache.role_title_[titleInfo.rid].insert(make_pair(titleInfo.id, titleInfo));
		}
	}
	return true;
}

bool CacheManager::LoadActive(UserCache &cache) {
	DataActive data;
	int ret = DataActiveManager::Instance()->Get(cache.uid_, data);
	memcpy((void*)&(cache.m_active_),(const void*)&data,sizeof(data));

	if (0 != ret && R_ERR_NO_DATA != ret) {
		error_log("load Active error ret=%d uid=%u", ret, cache.uid_);
		return false;
	}
	return true;
}
