/*
 * DataUser.cpp
 *
 *  Created on: 2015-9-2
 *      Author: Administrator
 */

#include "DataUser.h"
#include "AsyncDBManager.h"
#include "DataTableUidIdData.h"

#define OP_ADD_USER 1
#define OP_UPDATE_USER 2
#define OP_REMOVE_USER 3
#define OP_REPLACE_USER 4

int CDataUser::GetUser(uint32_t uid, DataUser& data) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(register_platform);
	DBCREQ_NEED(register_time);
	DBCREQ_NEED(block_time);
	DBCREQ_NEED(login_time);
	DBCREQ_NEED(offline_time);
	DBCREQ_NEED(level);
	DBCREQ_NEED(exp);
	DBCREQ_NEED(bag_grid);
	DBCREQ_NEED(protected_time);
	DBCREQ_NEED(anti_addiction);
	DBCREQ_NEED(total_charge);
	DBCREQ_NEED(viplevel);
	DBCREQ_NEED(name);
	DBCREQ_NEED(figure_url);
	DBCREQ_NEED(menubar);
	DBCREQ_NEED(combat);
	DBCREQ_NEED(gem_combat);
	DBCREQ_NEED(transport);
	DBCREQ_NEED(tutorial_stage);
	DBCREQ_NEED(trailer_stage);
	DBCREQ_NEED(trailer_stage_b);
	DBCREQ_NEED(invite_by);
	DBCREQ_NEED(auto_reward_ts);
	DBCREQ_NEED(auto_reward_count);
	DBCREQ_NEED(daily_charge);
	DBCREQ_NEED(daily_reset_ts);
	DBCREQ_NEED(daily_charge_reward);
	DBCREQ_NEED(total_charge_reward);
	DBCREQ_NEED(first_charge_reward);
	DBCREQ_NEED(sys_msg_ts);
	DBCREQ_NEED(defend_num);
	DBCREQ_NEED(buy_special);
	DBCREQ_NEED(shortcut);
	DBCREQ_NEED(daily_buy);
	DBCREQ_NEED(help_count);
	DBCREQ_NEED(help_reward);
	DBCREQ_NEED(help_box);
	DBCREQ_NEED(help_ts);
	DBCREQ_NEED(free_equp_ts);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, register_platform);
	DBCREQ_GET_INT(data, register_time);
	DBCREQ_GET_INT(data, block_time);
	DBCREQ_GET_INT(data, login_time);
	DBCREQ_GET_INT(data, offline_time);
	DBCREQ_GET_INT(data, level);
	DBCREQ_GET_INT(data, exp);
	DBCREQ_GET_INT(data, bag_grid);
	DBCREQ_GET_INT(data, protected_time);
	DBCREQ_GET_INT(data, anti_addiction);
	DBCREQ_GET_INT(data, total_charge);
	DBCREQ_GET_INT(data, viplevel);
	DBCREQ_GET_STR(data, name);
	DBCREQ_GET_STR(data, figure_url);
	DBCREQ_GET_INT(data, menubar);
	DBCREQ_GET_INT(data, combat);
	DBCREQ_GET_INT(data, gem_combat);
	DBCREQ_GET_INT(data, transport);
	DBCREQ_GET_INT(data, tutorial_stage);
	DBCREQ_GET_INT(data, trailer_stage);
	DBCREQ_GET_INT(data, trailer_stage_b);
	DBCREQ_GET_INT(data, invite_by);
	DBCREQ_GET_INT(data, auto_reward_ts);
	DBCREQ_GET_INT(data, auto_reward_count);
	DBCREQ_GET_INT(data, daily_charge);
	DBCREQ_GET_INT(data, daily_reset_ts);
	DBCREQ_GET_INT(data, daily_charge_reward);
	DBCREQ_GET_INT(data, total_charge_reward);
	DBCREQ_GET_INT(data, first_charge_reward);
	DBCREQ_GET_INT(data, sys_msg_ts);
	DBCREQ_GET_INT(data, defend_num);
	DBCREQ_GET_INT(data, buy_special);
	DBCREQ_GET_INT(data, shortcut);
	DBCREQ_GET_INT(data, daily_buy);
	DBCREQ_GET_INT(data, help_count);
	DBCREQ_GET_INT(data, help_reward);
	DBCREQ_GET_INT(data, help_box);
	DBCREQ_GET_INT(data, help_ts);
	DBCREQ_GET_INT(data, free_equp_ts);
	DBCREQ_GET_INT(data, speed_up);
	return 0;
}

int CDataUser::GetUserLevel(uint32_t uid, uint32_t &level) {
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(level);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT_V(level);

	return 0;
}

int CDataUser::AddUser(const DataUser& dataUser) {
	CNetPacket sp;
	sp.fd = DB_USER;
	sp.stime = OP_ADD_USER;
	if (!dataUser.Encode(sp.GetBody())) {
		error_log("data user encode error uid=%u", dataUser.uid);
		return -1;
	}
	if (!AsyncDBManager::getInstance()->send(&sp)) {
		return -1;
	}
	return 0;
}

int CDataUser::RealAddUser(CNetPacket* packet) {
	DataUser data;
	if (!data.Decode(packet->GetBody())) {
		return -1;
	}

	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, register_platform);
	DBCREQ_SET_INT(data, register_time);
	DBCREQ_SET_INT(data, block_time);
	DBCREQ_SET_INT(data, login_time);
	DBCREQ_SET_INT(data, offline_time);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, exp);
	DBCREQ_SET_INT(data, bag_grid);
	DBCREQ_SET_INT(data, protected_time);
	DBCREQ_SET_INT(data, anti_addiction);
	DBCREQ_SET_INT(data, total_charge);
	DBCREQ_SET_INT(data, viplevel);
	DBCREQ_SET_STR(data, name);
	DBCREQ_SET_STR(data, figure_url);
	DBCREQ_SET_INT(data, menubar);
	DBCREQ_SET_INT(data, combat);
	DBCREQ_SET_INT(data, gem_combat);
	DBCREQ_SET_INT(data, transport);
	DBCREQ_SET_INT(data, tutorial_stage);
	DBCREQ_SET_INT(data, trailer_stage);
	DBCREQ_SET_INT(data, trailer_stage_b);
	DBCREQ_SET_INT(data, invite_by);
	DBCREQ_SET_INT(data, auto_reward_ts);
	DBCREQ_SET_INT(data, auto_reward_count);
	DBCREQ_SET_INT(data, daily_charge);
	DBCREQ_SET_INT(data, daily_reset_ts);
	DBCREQ_SET_INT(data, daily_charge_reward);
	DBCREQ_SET_INT(data, total_charge_reward);
	DBCREQ_SET_INT(data, first_charge_reward);
	DBCREQ_SET_INT(data, sys_msg_ts);
	DBCREQ_SET_INT(data, defend_num);
	DBCREQ_SET_INT(data, buy_special);
	DBCREQ_SET_INT(data, shortcut);
	DBCREQ_SET_INT(data, daily_buy);
	DBCREQ_SET_INT(data, help_count);
	DBCREQ_SET_INT(data, help_reward);
	DBCREQ_SET_INT(data, help_box);
	DBCREQ_SET_INT(data, help_ts);
	DBCREQ_SET_INT(data, free_equp_ts);
	DBCREQ_SET_INT(data, speed_up);


	DBCREQ_EXEC;

	return 0;
}

int CDataUser::SetUser(const DataUser& dataUser) {
	CNetPacket sp;
	sp.fd = DB_USER;
	sp.stime = OP_UPDATE_USER;
	if (!dataUser.Encode(sp.GetBody())) {
		error_log("data user encode error uid=%u", dataUser.uid);
		return -1;
	}
	if (!AsyncDBManager::getInstance()->send(&sp)) {
		return -1;
	}
	return 0;
}

int CDataUser::RealSetUser(CNetPacket* packet) {
	DataUser data;
	if (!data.Decode(packet->GetBody())) {
		return -1;
	}

	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	//DBCREQ_SET_INT(data, register_platform);
	//DBCREQ_SET_INT(data, register_time);
	DBCREQ_SET_INT(data, block_time);
	DBCREQ_SET_INT(data, login_time);
	DBCREQ_SET_INT(data, offline_time);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, exp);
	DBCREQ_SET_INT(data, bag_grid);
	DBCREQ_SET_INT(data, protected_time);
	DBCREQ_SET_INT(data, anti_addiction);
	DBCREQ_SET_INT(data, total_charge);
	DBCREQ_SET_INT(data, viplevel);
	DBCREQ_SET_STR(data, name);
	DBCREQ_SET_STR(data, figure_url);
	DBCREQ_SET_INT(data, menubar);
	DBCREQ_SET_INT(data, combat);
	DBCREQ_SET_INT(data, gem_combat);
	DBCREQ_SET_INT(data, transport);
	DBCREQ_SET_INT(data, tutorial_stage);
	DBCREQ_SET_INT(data, trailer_stage);
	DBCREQ_SET_INT(data, trailer_stage_b);
	DBCREQ_SET_INT(data, invite_by);
	DBCREQ_SET_INT(data, auto_reward_ts);
	DBCREQ_SET_INT(data, auto_reward_count);
	DBCREQ_SET_INT(data, daily_charge);
	DBCREQ_SET_INT(data, daily_reset_ts);
	DBCREQ_SET_INT(data, daily_charge_reward);
	DBCREQ_SET_INT(data, total_charge_reward);
	DBCREQ_SET_INT(data, first_charge_reward);
	DBCREQ_SET_INT(data, sys_msg_ts);
	DBCREQ_SET_INT(data, defend_num);
	DBCREQ_SET_INT(data, buy_special);
	DBCREQ_SET_INT(data, shortcut);
	DBCREQ_SET_INT(data, daily_buy);
	DBCREQ_SET_INT(data, help_count);
	DBCREQ_SET_INT(data, help_reward);
	DBCREQ_SET_INT(data, help_box);
	DBCREQ_SET_INT(data, help_ts);
	DBCREQ_SET_INT(data, free_equp_ts);
	DBCREQ_SET_INT(data, speed_up);

	DBCREQ_EXEC;

	return 0;
}

int CDataUser::ReplaceUser(const DataUser& dataUser) {
	CNetPacket sp;
	sp.fd = DB_USER;
	sp.stime = OP_REPLACE_USER;
	if (!dataUser.Encode(sp.GetBody())) {
		error_log("data user encode error uid=%u", dataUser.uid);
		return -1;
	}
	if (!AsyncDBManager::getInstance()->send(&sp)) {
		return -1;
	}
	return 0;
}

int CDataUser::RealReplaceUser(CNetPacket* packet) {
	DataUser data;
	if (!data.Decode(packet->GetBody())) {
		return -1;
	}

	DBCREQ_DECLARE(DBC::ReplaceRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_SET_INT(data, register_platform);
	DBCREQ_SET_INT(data, register_time);
	DBCREQ_SET_INT(data, block_time);
	DBCREQ_SET_INT(data, login_time);
	DBCREQ_SET_INT(data, offline_time);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, exp);
	DBCREQ_SET_INT(data, bag_grid);
	DBCREQ_SET_INT(data, protected_time);
	DBCREQ_SET_INT(data, anti_addiction);
	DBCREQ_SET_INT(data, total_charge);
	DBCREQ_SET_INT(data, viplevel);
	DBCREQ_SET_STR(data, name);
	DBCREQ_SET_STR(data, figure_url);
	DBCREQ_SET_INT(data, menubar);
	DBCREQ_SET_INT(data, combat);
	DBCREQ_SET_INT(data, gem_combat);
	DBCREQ_SET_INT(data, transport);
	DBCREQ_SET_INT(data, tutorial_stage);
	DBCREQ_SET_INT(data, trailer_stage);
	DBCREQ_SET_INT(data, trailer_stage_b);
	DBCREQ_SET_INT(data, invite_by);
	DBCREQ_SET_INT(data, auto_reward_ts);
	DBCREQ_SET_INT(data, auto_reward_count);
	DBCREQ_SET_INT(data, daily_charge);
	DBCREQ_SET_INT(data, daily_reset_ts);
	DBCREQ_SET_INT(data, daily_charge_reward);
	DBCREQ_SET_INT(data, total_charge_reward);
	DBCREQ_SET_INT(data, first_charge_reward);
	DBCREQ_SET_INT(data, sys_msg_ts);
	DBCREQ_SET_INT(data, defend_num);
	DBCREQ_SET_INT(data, buy_special);
	DBCREQ_SET_INT(data, shortcut);
	DBCREQ_SET_INT(data, daily_buy);
	DBCREQ_SET_INT(data, help_count);
	DBCREQ_SET_INT(data, help_reward);
	DBCREQ_SET_INT(data, help_box);
	DBCREQ_SET_INT(data, help_ts);
	DBCREQ_SET_INT(data, free_equp_ts);
	DBCREQ_SET_INT(data, speed_up);

	DBCREQ_EXEC;

	return 0;
}

int CDataUser::RemoveUser(const uint32_t uid) {
	DB_ENCODE_BEGIN(DB_USER, OP_REMOVE_USER);
	DB_ENCODE(UInt32, uid);
	DB_ENCODE_END;

	return 0;
}

int CDataUser::RealRemoveUser(CNetPacket* packet) {
	uint32_t uid;
	DB_DECODE_BEGIN(&packet->body);
	DB_DECODE(UInt32, uid);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::DeleteRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_EXEC;

	return 0;
}

void CDataUser::doRequest(CNetPacket* packet) {
	int ret = 0;
	switch(packet->stime){
	case OP_ADD_USER:
		ret = RealAddUser(packet);
		break;
	case OP_UPDATE_USER:
		ret = RealSetUser(packet);
		break;
	case OP_REMOVE_USER:
		ret = RealRemoveUser(packet);
		break;
	case OP_REPLACE_USER:
		ret = RealReplaceUser(packet);
		break;
	default:
		ret = R_ERR_PARAM;
	}
	if (ret != 0) {
		error_log("ret=%d,op=%u", ret, packet->stime);
	}
}

