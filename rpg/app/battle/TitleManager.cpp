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
bool TitleManager::ActiveTitle(uint32_t uid, uint32_t rid, uint32_t id) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}

	DataTitle title;
	title.init(uid, rid,TYPE_ROLE_TITLE, id);

	DataRoleAttr attr;
	memcpy((void*) &attr, (const void*) &title, sizeof(title));
	DataRoleAttrManager::Instance()->Add(attr);

	if (0 == cache.role_title_.count(rid)) {
		map<uint32_t, DataTitle> titleMap;
		titleMap.insert(make_pair(id, title));
		cache.role_title_.insert(make_pair(rid, titleMap));
	} else {
		map<uint32_t, DataTitle> &titleMap = cache.role_title_[rid];
		titleMap.insert(make_pair(id, title));
	}
	return true;
}
// 处理客户端消息 1077 佩戴或卸下称号
bool TitleManager::Process(uint32_t uid, logins::STitleReq *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	// 1、服务器收到客户端的消息后  1、去数据库验证合法性
	if(cache.role_.count(req->roleId_))
	{
		error_log("role_id:%d not exist", req->roleId_);
		return R_ERROR;
	}
	// 2、到配置表中查看是否有该称号id
	if(!TitleCfgWrap().isTitleExist(req->titleId_))
	{
		error_log("title_id:%d not exist", req->titleId_);
		return R_ERROR;
	}
	// 3、查看是否有该key存在(roleId & titleId 不存在就添加一条)
	if(cache.role_title_.count(req->roleId_) == 0 || cache.role_title_[req->roleId_].count(req->titleId_) == 0)
	{
		ActiveTitle(uid, req->roleId_, req->titleId_);
	}
	// 4、对数据进行更新并且存入数据库
	DataTitle title;
	title.init(uid, req->roleId_,TYPE_ROLE_TITLE, req->titleId_);

	DataAttr attr;
	memcpy((void*)&attr, (const void*)&title, sizeof(title));
	DataAttrManager::Instance()->Set(attr);
	// 更新消息  1167-1904
	UpdateManager::Instance()->roleTitle(uid, req->roleId_, req->titleId_);
	// 更新消息  952-956
	uint32_t showId = GetShowId();
	uint32_t isDress = req->titleId_ == 0 ? 0 : 1;
	UpdateManager::Instance()->roleShows(uid, req->titleId_, isDress, showId);
	return 0;
}

uint32_t TitleManager::GetShowId() {
	static uint32_t show_ids[] = {53};
	return show_ids[0];
}

// 激活称号时增加角色属性
bool TitleManager::CalcProperty(const UserCache &cache, byte rid,PropertySets &props) {
	map<uint32_t, map<uint32_t, DataTitle> >::const_iterator itr = cache.role_title_.begin();
	for (; itr != cache.role_title_.end(); ++itr) {
		if (itr->first != rid) {
			continue;
		}
		map<uint32_t, DataTitle>::const_iterator item = itr->second.begin();
		for(; item != itr->second.end(); ++item) {
			const CfgTitle::Title &cfg = TitleCfgWrap().Get(item->first);
			PropertyCfg::setProps(cfg.attr(), 1.0, props);
		}
	}
	PropertyCfg::showProps(cache.uid_, rid, props, "RoleTitle");
	return true;
}

// 服务器主动推送的消息
int TitleManager::Sync(const UserCache &cache, uint32_t cmd,msgs::SIntIntMap *resp) {
	if (!cache.init_) {
		return false;
	}

	if (!LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp)) {
		return R_ERROR;
	}

	return R_SUCCESS;
}

