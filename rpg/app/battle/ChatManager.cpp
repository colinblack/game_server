/*
 * ChatManager.cpp
 *
 *  Created on: 2019年6月20日
 *      Author: Administrator
 */

#include "ChatManager.h"
#include "BattleInc.h"

ChatManager::ChatManager() {
}

ChatManager::~ChatManager() {
}

bool ChatManager::Init() {
	return true;
}

bool ChatManager::ActorLogin(uint32_t uid) {
	return true;
}

int ChatManager::Process(uint32_t uid, chat::CSChatProxy *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	vector<string> tmp;
	String::Split(req->content, ':', tmp);
	if (tmp.size() < 2)
		return 0;
	vector<string> vSplit;
	String::Split(tmp[1], ' ', vSplit);
	if (vSplit.size() == 4) {
		string & cmd_str = vSplit[0];
		string & type_str = vSplit[1];
		string & id_str = vSplit[2];
		string & count_str = vSplit[3];
		if (cmd_str == "@add" && type_str != "" && id_str != "" && count_str != "") {
			uint32_t type = Convert::StringToInt(type_str);
			uint32_t id = Convert::StringToInt(id_str);
			uint32_t count = Convert::StringToInt(count_str);
			if (type == 0) {
				if (id == MONEY_EXP) {
					UserManager::Instance()->AddExp(uid, count);
				} else if (IS_MONEY(id)) {
					UserManager::Instance()->AddMoney(uid, id, count, "admin");
				}
			} else if (type == 1) {
				UserManager::Instance()->AddItem(uid, id, count, "admin");
			}
		}
	} else if (vSplit.size() == 3) {
		string & cmd = vSplit[0];
		string & type_str = vSplit[1];
		string & value_str = vSplit[2];
		if (cmd == "@set" && type_str == "lv" && value_str != "") {
			uint32_t level = Convert::StringToInt(value_str);
			if (level <= 500) {
				UserManager::Instance()->doTestLevel(uid, level);
				return true;
			}
		}
	}
	debug_log("receive chat uid=%u,channel=%d,content =%s", uid, req->channel, req->content.c_str(), req->extend.c_str());
	return 0;
}

