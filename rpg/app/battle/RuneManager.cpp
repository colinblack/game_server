/*
 * RuneManager.cpp
 *
 *  Created on: 2019年6月27日
 *      Author: Administrator
 */

#include "RuneManager.h"
#include "BattleInc.h"

RuneManager::RuneManager() {
}

RuneManager::~RuneManager() {
}


bool RuneManager::CalcProperty(const UserCache &cache, byte rid, PropertySets &props) {
	try {
		for(map<uint32_t,DataRoleRune>::const_iterator it = cache.m_runeInfo.begin();it!=cache.m_runeInfo.end();it++){
			for(uint32_t i=0;i<NORMAL_RUNE_COUNT;i++){
				if(it->second.normalRune[i]>1){
					map<uint32_t, DataEquip>::const_iterator itp = cache.equip_.find(it->second.normalRune[i]);
					if(itp== cache.equip_.end()){
						error_log("ud= %d not exists in bag", it->second.normalRune[i]);
						continue;
					}
					uint32_t itemId = itp->second.id;
					uint32_t level = getLevel(itp->second.ext);

					ItemCfgWrap cfg_wrap;
					const CfgItem::Item &itemCfg = cfg_wrap.GetItem(itemId);
					MagicWrap magic_wrap;
					const CfgMagic::Magic &magicCfg = magic_wrap.GetMagic(level,itemCfg.subtype());
					double attrRate=0;
					if(8-itemCfg.color()<=5){
						attrRate = magicCfg.attrcal(8-itemCfg.color())/10000.0;
					}
					PropertyCfg::setProps(magicCfg.attr(), attrRate, props);
				}
			}
			for(uint32_t i=0;i<SPECIAL_RUNE_COUNT;i++){
				if(it->second.specialRune[i]>1){
					map<uint32_t, DataEquip>::const_iterator itp = cache.equip_.find(it->second.specialRune[i]);
					if(itp== cache.equip_.end()){
						error_log("ud= %d not exists in bag", it->second.specialRune[i]);
						continue;
					}
					uint32_t itemId = itp->second.id;
					uint32_t level = getLevel(itp->second.ext);
					ItemCfgWrap cfg_wrap;
					const CfgItem::Item &itemCfg = cfg_wrap.GetItem(itemId);
					MagicWrap magic_wrap;
					const CfgMagic::Magic &magicCfg = magic_wrap.GetMagic(level,itemCfg.subtype());
					double attrRate=0.0;
					if(8-itemCfg.color()<=5){
						attrRate = magicCfg.attrcal(8-itemCfg.color())/10000.0;
					}
					PropertyCfg::setProps(magicCfg.attr(), attrRate, props);
				}
			}
		}
	} catch (...) {
		return false;
	}
	PropertyCfg::showProps(cache.uid_, rid, props, "magic");
	return true;
}

bool  RuneManager::addExt(string &str, uint32_t micl, uint32_t micp) {
	static Json::Reader reader;
	static Json::FastWriter writer;
	Json::Value value;
	value = Json::Value(Json::objectValue);
	value["micl"] = micl;
	value["micp"] = micp;
	str = writer.write(value);
	return true;
}

bool  RuneManager::addExt(string &str, uint32_t micl) {
	static Json::Reader reader;
	static Json::FastWriter writer;
	Json::Value value;
	value = Json::Value(Json::objectValue);
	value["micl"] = micl;
	str = writer.write(value);
	return true;
}

uint32_t RuneManager::getLevel(const string &str) {
	static Json::Reader reader;
	Json::Value value;
	reader.parse(str, value);
	if(value.isMember("micl")){
		uint32_t level = value["micl"].asUInt();
		return level;
	}else{
		return 0;
	}
}

uint32_t RuneManager::getPos(string &str) {
	static Json::Reader reader;
	Json::Value value;
	reader.parse(str, value);
	if(value.isMember("micp")){
		uint32_t pos = value["micp"].asUInt();
		return pos;
	}else{
		return 0;
	}
}

bool RuneManager::upgradeExt(string &str){
	static Json::Reader reader;
	static Json::FastWriter writer;
	Json::Value value;
	reader.parse(str, value);

	if(value.isMember("micl")){
		uint32_t level = value["micl"].asUInt();
		value["micl"] = level++;
		str = writer.write(value);
	}else{
		return false;
	}
	return true;
}


int RuneManager::Process(uint32_t uid, rune::CSMagicOpenHole *req){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	map<uint32_t,DataRoleRune>::iterator it = cache.m_runeInfo.find(req->roleId);
	if(it ==cache.m_runeInfo.end()){
		DataRoleRune roleRuneInfo;
		roleRuneInfo.uid = uid;
		roleRuneInfo.rid = req->roleId;
		roleRuneInfo.type = TYPE_ROLE_RUNE;
		if(req->id<=NORMAL_RUNE_COUNT){
			roleRuneInfo.normalRune[req->id-1] = 100000;
		}
		else if(req->id==100||req->id==101){
			roleRuneInfo.specialRune[req->id-SPECIAL_RUNE_ID_BASE]=100000;
		}
		else{
			return -1;
		}
		cache.m_runeInfo.insert(make_pair(roleRuneInfo.rid,roleRuneInfo));
		DataRoleAttr attr;
		memcpy((void*)&attr,(const void*)&roleRuneInfo,sizeof(DataRoleAttr));
		DataRoleAttrManager::Instance()->Add(attr);
	}
	else{
		if(req->id<=NORMAL_RUNE_COUNT){
			it->second.normalRune[req->id-1] = 100000;
		}
		else if(req->id==100||req->id==101){
			it->second.specialRune[req->id-SPECIAL_RUNE_ID_BASE]=100000;
		}
		else{
			return -1;
		}
		ROLE_ATTR_DB_SET(it->second);
	}
	LogicManager::Instance()->AddSync(CMD_MAGIC_INFO);
	return 0;
}


int RuneManager::Process(uint32_t uid, rune::CSMagicLearn *req){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	debug_log("roleId=%d,holdId=%d,magicUid=%d",req->roleId,req->holeId,req->magicUid);

	map<uint32_t,DataRoleRune>::iterator it = cache.m_runeInfo.find(req->roleId);
	if(it ==cache.m_runeInfo.end()){
		return R_ERROR;
	}

	if(req->holeId<=NORMAL_RUNE_COUNT&&req->holeId>0){
		if(it->second.normalRune[req->holeId-1]!=0&&it->second.normalRune[req->holeId-1]!=100000){
			//卸下
			UpdateManager::Instance()->SetCode(UC_MoveItem);
			map<uint32_t, DataEquip>::iterator itq = cache.equip_.find(it->second.normalRune[req->holeId-1]);
			if(itq== cache.equip_.end()){
				error_log("ud= %d not exists in bag uid=%u ", it->second.normalRune[req->holeId-1], uid);
				return R_ERROR;
			}
			uint32_t level = getLevel(itq->second.ext);
			addExt(itq->second.ext,level);
			UpdateManager::Instance()->ChgBag(uid, itq->second.bag, BAG_ALL, itq->second);
			itq->second.bag = BAG_ALL;
			DataEquipManager::Instance()->Set(itq->second);
			it->second.normalRune[req->holeId-1] = 100000;
		}
		map<uint32_t, DataEquip>::iterator itp = cache.equip_.find(req->magicUid);
		if(itp!= cache.equip_.end()){
			//穿
			UpdateManager::Instance()->SetCode(UC_LearnMagic);
			itp->second.bag = BAG_ROLE_RUNE+req->roleId;
			uint32_t level = getLevel(itp->second.ext);
			addExt(itp->second.ext,level,req->holeId);
			DataEquipManager::Instance()->Set(itp->second);
			UpdateManager::Instance()->ChgBag(uid, BAG_ALL, itp->second.bag, itp->second);
			it->second.normalRune[req->holeId-1] = req->magicUid;
		}

	}else if(req->holeId==100||req->holeId==101){
		if(it->second.specialRune[req->holeId-SPECIAL_RUNE_ID_BASE]!=0&&it->second.specialRune[req->holeId-SPECIAL_RUNE_ID_BASE]!=100000){
			//卸下
			UpdateManager::Instance()->SetCode(UC_MoveItem);
			map<uint32_t, DataEquip>::iterator itq = cache.equip_.find(it->second.normalRune[req->holeId-1]);
			if(itq== cache.equip_.end()){
				error_log("ud= %d not exists in bag uid=%u ", it->second.specialRune[req->holeId-SPECIAL_RUNE_ID_BASE], uid);
				return R_ERROR;
			}
			uint32_t level = getLevel(itq->second.ext);
			addExt(itq->second.ext,level);
			UpdateManager::Instance()->ChgBag(uid, itq->second.bag, BAG_ALL, itq->second);
			itq->second.bag = BAG_ALL;
			DataEquipManager::Instance()->Set(itq->second);
			it->second.specialRune[req->holeId-SPECIAL_RUNE_ID_BASE] = 100000;
		}
		map<uint32_t, DataEquip>::iterator itp = cache.equip_.find(req->magicUid);
		if(itp!= cache.equip_.end()){
			//穿
			UpdateManager::Instance()->SetCode(UC_LearnMagic);
			itp->second.bag = BAG_ROLE_RUNE+req->roleId;
			uint32_t level = getLevel(itp->second.ext);
			addExt(itp->second.ext,level,req->holeId);
			DataEquipManager::Instance()->Set(itp->second);
			UpdateManager::Instance()->ChgBag(uid, BAG_ALL, itp->second.bag, itp->second);
			it->second.specialRune[req->holeId-SPECIAL_RUNE_ID_BASE] = req->magicUid;
		}
	}
	ROLE_ATTR_DB_SET(it->second);
	PropertyManager::Instance()->AddUser(uid);
	return 0;
}


int RuneManager::Process(uint32_t uid,rune::CSMagicUpgrade *req){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	map<uint32_t, DataEquip>::iterator it = cache.equip_.find(req->magicUid);
	if(it== cache.equip_.end()){
		error_log("ud= %d not exists in bag uid=%u ", req->magicUid, uid);
		return R_ERROR;
	}
	uint32_t itemId = it->second.id;
	uint32_t level = getLevel(it->second.ext);
	ItemCfgWrap cfg_wrap;
	const CfgItem::Item &itemCfg = cfg_wrap.GetItem(itemId);
	MagicWrap magic_wrap;
	const CfgMagic::Magic &magicCfg = magic_wrap.GetMagic(level,itemCfg.subtype());
	uint32_t exp=0;
	if(8-itemCfg.color()<=6){
		exp = magicCfg.exp()*(magicCfg.expcal(8-itemCfg.color())/10000.0);
	}
	string code;
	String::Format(code, "magic_upgrade_%u", req->magicUid);
	if (UserManager::Instance()->UseMoney(uid, MONEY_MAGIC_EXP, exp, code)) {
		return R_ERROR;
	}
	UpdateManager::Instance()->SetCode(UC_UpgradeMagic);
	uint32_t pos = getPos(it->second.ext);
	addExt(it->second.ext,level+1,pos);
	UpdateManager::Instance()->Bag(uid, 0, it->second);
	DataEquipManager::Instance()->Set(it->second);
	PropertyManager::Instance()->AddUser(uid);
	return 0;
}


int RuneManager::Process(uint32_t uid, rune::CSMagicDecomPose *req){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	uint32_t exp=0;
	UpdateManager::Instance()->SetCode(UC_SwalMagic);
	Award SmeltRward;
	for(uint32_t i=0;i<req->uidList.size();i++){
		map<uint32_t, DataEquip>::iterator it = cache.equip_.find(req->uidList[i]);
		if(it== cache.equip_.end()){
			error_log("ud= %d not exists in bag uid=%u ", req->uidList[i], uid);
			return R_ERROR;
		}

		uint32_t level = getLevel(it->second.ext);
		uint32_t itemId = it->second.id;
		ItemCfgWrap cfg_wrap;
		const CfgItem::Item &itemCfg = cfg_wrap.GetItem(itemId);
		//符文精华
		if(itemCfg.subtype()==0){
			if(itemCfg.color()==2){
				exp+=850;
			}else if(itemCfg.color()==3){
				exp +=4200;
			}else if(itemCfg.color()==4){
				exp +=17000;
			}else if(itemCfg.color()==5){
				exp +=85000;
			}else if(itemCfg.color()==6){
				exp +=420000;
			}
		}else{
			MagicWrap magic_wrap;
			const CfgMagic::Magic &magicCfg = magic_wrap.GetMagic(level,itemCfg.subtype());
			if(8-itemCfg.color()<=6){
				exp +=magicCfg.smeltcal(8-itemCfg.color());
			}
			//分解增加其他物品item找
			SmeltRward.Format(itemCfg.smeltaward(), 1);
		}
		UpdateManager::Instance()->DelBag(uid,1,it->second);
		DataEquipManager::Instance()->Del(it->second);
		cache.equip_.erase(it);
	}
	SmeltRward.Add(MONEY_MAGIC_EXP, exp);
	UserManager::Instance()->Reward(uid, SmeltRward, "magic Smelt Rward");
	PropertyManager::Instance()->AddUser(uid);
	return 0;
}

int RuneManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SMagicInfo *resp) {
	for(map<uint32_t,DataRoleRune>::const_iterator it = cache.m_runeInfo.begin();it!=cache.m_runeInfo.end();it++){
		msgs::SMagicSingle tmp;
		for(uint32_t i=0;i<NORMAL_RUNE_COUNT;i++){
			if(it->second.normalRune[i]!=0){
				tmp.isOpenHole_.insert(make_pair(i+1,1));
			}
		}
		for(uint32_t i=0;i<SPECIAL_RUNE_COUNT;i++){
			if(it->second.specialRune[i]!=0){
				tmp.isOpenHole_.insert(make_pair(i+SPECIAL_RUNE_ID_BASE,1));
			}
		}
		resp->roleHole_.insert(make_pair(it->second.rid,tmp));
	}


	map<uint32_t,CopyInfo>::const_iterator itc =  cache.m_copyInfo.find(220);
	if(itc== cache.m_copyInfo.end()){
		resp->magicCopyLayer_=1;
	}
	else
		resp->magicCopyLayer_ = itc->second.data;
	LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp);
	return 0;
}


