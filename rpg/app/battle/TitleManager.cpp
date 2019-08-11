/*
 * TitleManager.cpp
 *
 *  Created on: 2019年7月16日
 *      Author: memory
 */

#include "TitleManager.h"
#include "BattleInc.h"

TitleManager::TitleManager() {
}

TitleManager::~TitleManager() {
}

// 背包激活称号 注意：  称号获得后，三个角色都可佩戴、同一个称号同时只能有一个角色可佩戴；
bool TitleManager::ActiveTitle(uint32_t uid, uint32_t rid, uint32_t titleId) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}

	// bool TitleManager::Process
	// 激活之前先判断role1身上是否穿戴了称号 如果穿戴了就脱下
	map<uint32_t, DataTitle>::iterator it = cache.user_title_.begin();
	for (; it != cache.user_title_.end(); ++it) {
		// 一个角色人只能穿戴一个称号
		// 一个称号只能属于一个角色
		if( 1 == it->second.rid && it->second.isWear) {
			DataTitle& title = it->second;
			title.isWear = false;
			title.rid = 0;
			ATTR_DB_SET(title);
			break;
		}
	}

	// 一个称号在数据库中只有一条  titleID
	if (cache.user_title_.count(titleId) == 0) {
		DataTitle title;
		title.init(uid, rid,TYPE_ROLE_TITLE, titleId,true);
		cache.user_title_[titleId] = title;
		ATTR_DB_ADD(title);
	}
	return true;
}

// 处理客户端消息 1077 佩戴或卸下称号
bool TitleManager::Process(uint32_t uid, logins::STitleReq *req) {
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
	// 2、客户端推送消息 titleID == 0 时卸下、反之亦然
	uint32_t isWear = req->titleId_ == 0 ? 0 : 1;

	// 穿戴消息
	if(isWear){
		// 1 、下面判断玩家身上是否穿戴了其他称号、先卸下其他称号在进行穿戴  2、判断改称号是否被其他角色穿戴
		// 找到该roleId 先取消掉其佩戴的称号  找到该titleId 取消掉其佩戴
		map<uint32_t, DataTitle>::iterator it = cache.user_title_.begin();
		for(; it != cache.user_title_.end(); ++it) {
			if( (req->roleId_ == it->second.rid && it->second.isWear) ||
				(req->titleId_ == it->second.id && it->second.isWear)) {
				DataTitle& title = it->second;
				title.isWear = false;
				title.rid = 0;
				ATTR_DB_SET(title);
				break;
			}
		}

		DataTitle& title = cache.user_title_[req->titleId_];	  // 重点  指针引用的数据修改
		title.isWear = true;
		title.rid = req->roleId_;
		ATTR_DB_SET(title);
	}
	else
	{
		map<uint32_t, DataTitle>::iterator it = cache.user_title_.begin();
		for(; it != cache.user_title_.end(); ++it) {
			if(req->roleId_ == it->second.rid && it->second.isWear) {
				DataTitle& title = it->second;
				title.isWear = false;
				title.rid = 0;
				ATTR_DB_SET(title);
				break;
			}
		}
	}

	// 更新消息  1167-1904
	LogicManager::Instance()->AddSync(CMD_PLAYER_WEAR_TITLE);
	// 更新消息  952-956
	uint32_t showId = GetShowId();
	UpdateManager::Instance()->roleShows(uid, req->titleId_, isWear, showId);
	return 0;
}

uint32_t TitleManager::GetShowId() {
	static uint32_t show_ids[] = {53};
	return show_ids[0];
}

// 激活称号时增加角色属性
bool TitleManager::CalcProperty(const UserCache &cache, byte rid,PropertySets &props) {
	map<uint32_t, DataTitle>::const_iterator itr = cache.user_title_.begin();
	for (; itr != cache.user_title_.end(); ++itr) {
		if (itr->second.rid != rid) {
			continue;
		}
		const CfgTitle::Title &cfg = TitleCfgWrap().Get(itr->first);
		PropertyCfg::setProps(cfg.attr(), 1.0, props);
	}

	PropertyCfg::showProps(cache.uid_, rid, props, "RoleTitle");
	return true;
}

// 背包使用称号道具
bool TitleManager::BagUseTitleItem(uint32_t uid ,uint32_t equipId)
{
	const CfgItem::Item &cfg = ItemCfgWrap().GetItem(equipId); // 通过id去获取单条数据
	uint32_t titleID  = cfg.data(); // 称号ID

	if(UpdateManager::Instance()->S2CPlayerTitle(uid,titleID)){ // 1168-1075
		TitleManager::Instance()->ActiveTitle(uid, 1, titleID); // 激活称号，存入数据库
		PropertyManager::Instance()->AddUser(uid);	// 触发添加称号属性函数 CalcProperty
		LogicManager::Instance()->AddSync(CMD_PLAYER_WEAR_TITLE);
		UpdateManager::Instance()->roleShows(uid, titleID,true, TitleManager::Instance()->GetShowId()); // 952-956
	}
	return true;
}

// 服务器主动推送的消息  s2c:1074,1076  上线的时候推送，称号的集合
int TitleManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerTitleInfo *resp) {
	// 遍历下数据库 从中获取玩家所拥有的称号集合
	vector<msgs::SPlayerTitle> titles;
	map<uint32_t, DataTitle>::const_iterator itr = cache.user_title_.begin();
	for (; itr != cache.user_title_.end(); ++itr) {
		msgs::SPlayerTitle playerTitle;
		playerTitle.titleId_ =itr->second.id;
		playerTitle.indateTime_ =itr->second.indateTime;

		titles.push_back(playerTitle);
	}
	resp->titles_ = titles;
	LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp);
	return 0;
}

// 服务器主动推送的消息  s2c:更新消息  1167-1904  上线的时候推送，称号的佩戴信息
int TitleManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SIntIntMap *resp) {
	// 遍历下数据库 从中获取玩家所拥有的称号集合
	map<uint32_t, DataTitle>::const_iterator itr = cache.user_title_.begin();
	for (; itr != cache.user_title_.end(); ++itr) {
		uint32_t titleId = itr->second.isWear ? itr->second.id : 0;
		resp->maps_.insert(make_pair(itr->second.rid, titleId));
//		resp->maps_[itr->second.rid] = itr->second.isWear ? itr->second.id : 0; //佩戴 roleID : titleID
	}

	LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp);
	return 0;
}
