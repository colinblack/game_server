/*
 * FashionManager.cpp
 *
 *  Created on: 2019年7月30日
 *      Author: memory
 */

#include "FashionManager.h"
#include "BattleInc.h"

FashionManager::FashionManager() {
}

FashionManager::~FashionManager() {
}

// 激活 1418
bool FashionManager:: Process(uint32_t uid, logins::CActiveFashionReq *req, msgs::SFashion* resp) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	// 1、服务器收到客户端的消息后  1、去数据库验证合法性 - 是否有该roleId
	if(!cache.role_.count(req->roleId_))
	{
		error_log("role_id:%d not exist", req->roleId_);
		return R_ERROR;
	}

	// 判断该角色身上是否穿戴了，如果穿戴脱下，然后再穿上，没有直接穿上，并保存在数据库
	map<uint32_t, DataRoleFashion> ::iterator it = cache.role_fashion_[req->roleId_][req->type_].begin();
	for (; it != cache.role_fashion_[req->roleId_][req->type_].end(); ++it){
		if(it->second.rid == req->roleId_ && it->second.isWear){
			DataRoleFashion& fashion = cache.role_fashion_[req->roleId_][req->type_][it->first];
			fashion.isWear = 0;
			ROLE_ATTR_DB_SET(fashion);
			break;
		}
	}

	// 数据库中没有这一套时装,初始化后存入数据库
	if (cache.role_fashion_[req->roleId_][req->type_].count(req->fashionId_) == 0) {
		DataRoleFashion fashion;
		fashion.init(uid, req->roleId_,TYPE_ROLE_FASHION, req->fashionId_,req->type_);
		fashion.level = 1;
		fashion.isWear = 1;
		fashion.fashionType = req->type_;
		ROLE_ATTR_DB_ADD(fashion);
		cache.role_fashion_[req->roleId_][req->type_].insert(make_pair(fashion.id, fashion));
	}

	resp->dian_ = 0;
	resp->bless_ = 0;
	resp->deadDt_ = 0;
	resp->level_ = 1;
	resp->promoteLevel_ = 1;


	// 使用道具 srv:265,271  消耗道具
	const CfgFashion::Fashion&cfg = FashionCfgWrap().GetFashionByIdAndLevel(req->fashionId_,1);
	UserManager::Instance()->UseItem(uid,cfg.itemid(),cfg.itemcount(),"ActiveFashion");

	// 增加战斗力
	PropertyManager::Instance()->AddUser(uid);	// 触发添加称号属性函数 CalcProperty
	return 0;
}

// 穿戴 2047
bool FashionManager::Process(uint32_t uid, logins::CPutOnFashionReq *req, logins::SPutOnFashionResp* resp){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	// 1、服务器收到客户端的消息后  1、去数据库验证合法性 - 是否有该roleId
	if(!cache.role_.count(req->roleId_))
	{
		error_log("role_id:%d not exist", req->roleId_);
		return R_ERROR;
	}
	if(cache.role_fashion_[req->roleId_][req->type_].count(req->fashionId_) == 0){
		error_log("fashionId:%d not exist", req->fashionId_);
		return R_ERROR;
	}

	DataRoleFashion& fashion = cache.role_fashion_[req->roleId_][req->type_][req->fashionId_];
	fashion.isWear = 1;
	ROLE_ATTR_DB_SET(fashion);
	resp->fashionId_ = req->fashionId_;

	// 触发消息 srv:1554 ,1559
	LogicManager::Instance()->AddSync(CMD_PLAYER_FASHION);// 时装


	// 更新消息  952-956
	const CfgFashion::Fashion&cfg = FashionCfgWrap().GetFashionByIdAndLevel(req->fashionId_,fashion.level);
	UpdateManager::Instance()->roleShows(uid, cfg.modelid(), fashion.isWear, 1001);

	return 0;
}

// 脱下 2048
bool FashionManager::Process(uint32_t uid, logins::CGetOffFashionReq *req, logins::SGetOffFashionResp* resp){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	// 1、服务器收到客户端的消息后  1、去数据库验证合法性 - 是否有该roleId
	if(!cache.role_.count(req->roleId_))
	{
		error_log("role_id:%d not exist", req->roleId_);
		return R_ERROR;
	}
	DataRoleFashion& fashion = cache.role_fashion_[req->roleId_][req->type_][req->fashionId_];
	fashion.isWear = 0;
	ROLE_ATTR_DB_SET(fashion);
	resp->fashionId_ = req->fashionId_;

	// 更新消息  952-956
	UpdateManager::Instance()->roleShows(uid, 0, fashion.isWear, 1001);

	return 0;
}

// 处理客户端消息 升级时装  2046
bool FashionManager::Process(uint32_t uid, logins::CAdvanceFashionReq *req,msgs::SFashion* resp){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	// 1、服务器收到客户端的消息后  1、去数据库验证合法性 - 是否有该roleId
	if(!cache.role_.count(req->roleId_))
	{
		error_log("role_id:%d not exist", req->roleId_);
		return R_ERROR;
	}
	if(cache.role_fashion_[req->roleId_][req->type_].count(req->fashionId_) == 0){
		error_log("fashionId:%d not exist", req->fashionId_);
		return R_ERROR;
	}

	DataRoleFashion& fashion = cache.role_fashion_[req->roleId_][req->type_][req->fashionId_];
	fashion.level++;
	ROLE_ATTR_DB_SET(fashion);

	resp->dian_ = 0;
	resp->bless_ = 0;
	resp->deadDt_ = 0;
	resp->level_ = fashion.level;
	resp->promoteLevel_ = fashion.level;

	// 使用道具 srv:265,271  消耗道具
	const CfgFashion::Fashion&cfg = FashionCfgWrap().GetFashionByIdAndLevel(req->fashionId_,fashion.level);
	UserManager::Instance()->UseItem(uid,cfg.itemid(),cfg.itemcount(),"AdvanceFashion");
	// 增加战斗力
	PropertyManager::Instance()->AddUser(uid);	// 触发添加称号属性函数 CalcProperty
	return 0;
}

// 计算战斗力
bool FashionManager::CalcProperty(const UserCache &cache, byte rid,PropertySets &props) {
	map<uint32_t, ROLE_FASHION_INFO>::const_iterator itr = cache.role_fashion_.begin();
	for (; itr != cache.role_fashion_.end(); ++itr) {
		if (itr->first != rid) {continue;}
		ROLE_FASHION_INFO::const_iterator item = itr->second.begin();
		for(; item != itr->second.end(); ++item) {
			map<uint32_t, DataRoleFashion>::const_iterator it = item->second.begin();
			for (; it != item->second.end(); ++it) {
				const CfgFashion::Fashion&cfg = FashionCfgWrap().GetFashionByIdAndLevel(it->first,it->second.level);
				PropertyCfg::setProps(cfg.attr(), 1.0, props);
			}
		}
	}

	// 从数据库缓存中拿到时装-套装的数据
	map<uint32_t, DataRoleFashionSuit>::const_iterator it = cache.role_fashion_suit_.begin();
	for (; it != cache.role_fashion_suit_.end(); ++it) {
		if (it->second.rid != rid) {
			continue;
		}
		const CfgFashionSuit::FashionSuit&cfg = FashionSuitCfgWrap().GetFashionSuitByIdAndCount(it->second.suitId,it->second.num);
		PropertyCfg::setProps(cfg.attr(), 1.0, props);
	}
	PropertyCfg::showProps(cache.uid_, rid, props, "Fashion and RoleTitle");
	return true;
}

// 服务器主动推送的消息  s2c:更新消息  srv:1554,1559  上线的时候推送，角色时装信息  多层嵌套数组
int FashionManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerFashionInfo *resp) {
	// 所有role
	map<uint32_t, ROLE_FASHION_INFO>::const_iterator it = cache.role_fashion_.begin();
	for(;it != cache.role_fashion_.end();++it){
		msgs::SRoleFashionInfo& sRoleFashionInfo = resp->playerFashion_[it->first];
		// 所有type
		ROLE_FASHION_INFO::const_iterator item = it->second.begin();
		for(; item != it->second.end(); ++item) {
			msgs::SFashionInfo sFashionInfo;
			map<uint32_t, DataRoleFashion>::const_iterator itr = item->second.begin();
			// type 下对应的所有 id
			for (; itr != item->second.end(); ++itr) {
				msgs::SFashion sFashion;
				sFashion.level_ =itr->second.level;
				sFashion.promoteLevel_ = itr->second.level;
				sFashion.dian_ = 1;// 点亮
				sFashion.bless_ = 0;
				sFashion.deadDt_ = 0;
				sFashionInfo.fashions_.insert(make_pair(itr->second.id, sFashion));// id ,DATA
				if(itr->second.isWear){
					sFashionInfo.puton_ = itr->second.id;// 穿戴的id
				}
			}

			sRoleFashionInfo.roleFashion_.insert(make_pair(item->first, sFashionInfo));// type,DATA

			//	sRoleFashionInfo.suits_
			//	sRoleFashionInfo.roleItem_
		}
		map<uint32_t, DataRoleFashionSuit>::const_iterator itt  = cache.role_fashion_suit_.begin();
		msgs::SInts SintsTemp;
		for(;itt != cache.role_fashion_suit_.end();++itt){
			SintsTemp.values_.push_back(itt->second.num);
			sRoleFashionInfo.suits_[itt->second.suitId] = SintsTemp;
		}
	}

	LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp);
	return 0;
}

// TODO 将数据存放在一条中，数据库中  一个id存放一条
uint32_t FashionManager::GetIndexByIdAndNum(uint32_t id,uint32_t num){
	uint32_t index = 0;

	return  index;
}

// 时装-套装激活 3742
bool FashionManager::Process(uint32_t uid, logins::CActiveFashionSuitReq* req,logins::SActiveFashionSuitResp * resp){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	// 1、服务器收到客户端的消息后  1、去数据库验证合法性 - 是否有该roleId
	if(!cache.role_.count(req->roleId_))
	{
		error_log("role_id:%d not exist", req->roleId_);
		return R_ERROR;
	}

	// 数据库中没有这一套时装,初始化后存入数据库(id 和 num作为 key)
	uint32_t key = req->suitId_ * 1000 + req->num_;
	map<uint32_t, DataRoleFashionSuit>::iterator it = cache.role_fashion_suit_.find(key);
	if (it == cache.role_fashion_suit_.end()) {
		DataRoleFashionSuit fashionSuit;
		fashionSuit.init(uid, req->roleId_,TYPE_ROLE_FASHION_SUIT, key,req->suitId_,req->num_);
		ROLE_ATTR_DB_ADD(fashionSuit);
		cache.role_fashion_suit_.insert(make_pair(key, fashionSuit));
	}

	//判断是否激活
	//修改数据
	// 从数据库缓存中拿到时装-套装的数据
	it = cache.role_fashion_suit_.begin();
	msgs::SInts SintsTemp;
	for(;it != cache.role_fashion_suit_.end();++it){
		SintsTemp.values_.push_back(it->second.num);
		resp->suits_[it->second.suitId] = SintsTemp;
	}

	// 增加战斗力
	PropertyManager::Instance()->AddUser(uid);	// 触发添加称号属性函数 CalcProperty
	return 0;
}
