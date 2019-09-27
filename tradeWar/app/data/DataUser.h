/*
 * DataUser.h
 *
 *  Created on: 2015-9-2
 *      Author: Administrator
 */

#ifndef DATAUSER_H_
#define DATAUSER_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

struct DataUser {
	uint32_t uid;					// 玩家ID
	uint32_t register_platform;		// 注册平台
	uint32_t register_time;			// 注册时间
	uint32_t block_time;            // 封号到期时间
	uint32_t login_time;			// 上线时间戳
	uint32_t offline_time;			// 下线时间戳
	uint32_t level;					// 段位
	uint32_t exp;					// 奖杯数
	uint32_t bag_grid;				// 背包格子数
	uint32_t protected_time;		// 保护时间
	uint32_t anti_addiction;		// 防沉迷
	uint32_t total_charge;			// 累积充值
	uint32_t viplevel;				// vip等级
	string   name;					// 玩家名字,QQ名字或者内网OPENID
	string   figure_url;			// 头像url
	uint64_t menubar;				// 玩家系统设置标志位集合(音乐开启、等等)
	uint32_t combat;				// 军力
	uint32_t gem_combat;			// 宝石军力
	uint32_t transport;				// 累计运输资源
	uint32_t transport_reset_ts;	// 累计运输资源重置时间
	uint32_t tutorial_stage;		// 新手阶段
	uint32_t trailer_stage;			// 预告阶段
	uint32_t trailer_stage_b;		// 预告阶段
	uint32_t invite_by;				// 邀请者UID
	uint32_t auto_reward_ts;        // 挂机奖励时间戳
	uint32_t auto_reward_count;     // 挂机奖励次数
	uint32_t daily_charge;			// 每日充值数
	uint32_t daily_reset_ts;		// 每日重置时间戳
	uint32_t total_charge_reward;	// 累积充值奖励
	uint32_t first_charge_reward;	// 首次充值奖励，从高位开始记录首次充值，从低位开始记录首充双倍
	uint32_t sys_msg_ts;			// 系统消息TS
	uint32_t buy_special;			// 特别优惠购买标记
	uint32_t help_box;              // 红心宝箱数
	uint32_t help_ts;               // 红心恢复时间戳
	uint8_t  daily_charge_reward;	// 每日充值奖励
	uint8_t  defend_num;			// 护卫副本挑战次数
	uint8_t  shortcut;				// 收藏标记
	uint8_t  daily_buy;				// VIP每日礼包
	int16_t  help_count;            // 红心数
	uint8_t  help_reward;           // 红心奖励
	uint32_t free_equp_ts;			// 免费史诗箱子时间戳
	uint8_t  speed_up;				// 战役加速标志位

	DataUser() {
		uid = 0;
		register_platform = 0;
		register_time = 0;
		block_time = 0;
		login_time = 0;
		offline_time = 0;
		level = 0;
		exp = 0;
		bag_grid = 0;
		protected_time = 0;
		anti_addiction = 0;
		total_charge = 0;
		viplevel = 0;
		menubar = 0;
		combat = 0;
		gem_combat = 0;
		transport = 0;
		transport_reset_ts = 0;
		tutorial_stage = 0;
		trailer_stage = 0;
		trailer_stage_b = 0;
		invite_by = 0;
		auto_reward_ts = 0;
		auto_reward_count = 0;
		daily_charge = 0;
		daily_reset_ts = 0;
		total_charge_reward = 0;
		first_charge_reward = 0;
		sys_msg_ts = 0;
		buy_special = 0;
		help_box = 0;
		help_count = 0;
		help_ts = 0;
		daily_charge_reward = 0;
		defend_num = 0;
		shortcut = 0;
		daily_buy = 0;
		help_reward = 0;
		free_equp_ts = 0;
		speed_up = 0;
	}

	bool Encode(IBuffer *buff) const {
		if (buff == NULL) {
			return false;
		}
		CBufferWriter writer(buff);
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, register_platform);
		PACKET_ENCODE(UInt32, register_time);
		PACKET_ENCODE(UInt32, block_time);
		PACKET_ENCODE(UInt32, login_time);
		PACKET_ENCODE(UInt32, offline_time);
		PACKET_ENCODE(UInt32, level);
		PACKET_ENCODE(UInt32, exp);
		PACKET_ENCODE(UInt32, bag_grid);
		PACKET_ENCODE(UInt32, protected_time);
		PACKET_ENCODE(UInt32, anti_addiction);
		PACKET_ENCODE(UInt32, total_charge);
		PACKET_ENCODE(UInt32, viplevel);
		PACKET_ENCODE(UInt64, menubar);
		PACKET_ENCODE(UInt32, combat);
		PACKET_ENCODE(UInt32, gem_combat);
		PACKET_ENCODE(UInt32, transport);
		PACKET_ENCODE(UInt32, tutorial_stage);
		PACKET_ENCODE(UInt32, trailer_stage);
		PACKET_ENCODE(UInt32, trailer_stage_b);
		PACKET_ENCODE(UInt32, invite_by);
		PACKET_ENCODE(UInt32, auto_reward_ts);
		PACKET_ENCODE(UInt32, auto_reward_count);
		PACKET_ENCODE(UInt32, daily_charge);
		PACKET_ENCODE(UInt32, daily_reset_ts);
		PACKET_ENCODE(UInt32, total_charge_reward);
		PACKET_ENCODE(UInt32, first_charge_reward);
		PACKET_ENCODE(UInt32, sys_msg_ts);
		PACKET_ENCODE(UInt32, buy_special);
		PACKET_ENCODE(UInt32, help_box);
		PACKET_ENCODE(UInt32, help_ts);
		PACKET_ENCODE(Int16,  help_count);
		PACKET_ENCODE(Byte,   daily_charge_reward);
		PACKET_ENCODE(Byte,   defend_num);
		PACKET_ENCODE(Byte,   shortcut);
		PACKET_ENCODE(Byte,   daily_buy);
		PACKET_ENCODE(Byte,   help_reward);
		PACKET_ENCODE(String, name);
		PACKET_ENCODE(String, figure_url);
		PACKET_ENCODE(UInt32,   free_equp_ts);
		PACKET_ENCODE(Byte,   speed_up);
		return true;
	}

	bool Decode(IBuffer *buff) {
		if (buff == NULL) {
			return false;
		}
		CBufferReader reader(buff);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, register_platform);
		PACKET_DECODE(UInt32, register_time);
		PACKET_DECODE(UInt32, block_time);
		PACKET_DECODE(UInt32, login_time);
		PACKET_DECODE(UInt32, offline_time);
		PACKET_DECODE(UInt32, level);
		PACKET_DECODE(UInt32, exp);
		PACKET_DECODE(UInt32, bag_grid);
		PACKET_DECODE(UInt32, protected_time);
		PACKET_DECODE(UInt32, anti_addiction);
		PACKET_DECODE(UInt32, total_charge);
		PACKET_DECODE(UInt32, viplevel);
		PACKET_DECODE(UInt64, menubar);
		PACKET_DECODE(UInt32, combat);
		PACKET_DECODE(UInt32, gem_combat);
		PACKET_DECODE(UInt32, transport);
		PACKET_DECODE(UInt32, tutorial_stage);
		PACKET_DECODE(UInt32, trailer_stage);
		PACKET_DECODE(UInt32, trailer_stage_b);
		PACKET_DECODE(UInt32, invite_by);
		PACKET_DECODE(UInt32, auto_reward_ts);
		PACKET_DECODE(UInt32, auto_reward_count);
		PACKET_DECODE(UInt32, daily_charge);
		PACKET_DECODE(UInt32, daily_reset_ts);
		PACKET_DECODE(UInt32, total_charge_reward);
		PACKET_DECODE(UInt32, first_charge_reward);
		PACKET_DECODE(UInt32, sys_msg_ts);
		PACKET_DECODE(UInt32, buy_special);
		PACKET_DECODE(UInt32, help_box);
		PACKET_DECODE(UInt32, help_ts);
		PACKET_DECODE(Int16,  help_count);
		PACKET_DECODE(Byte,   daily_charge_reward);
		PACKET_DECODE(Byte,   defend_num);
		PACKET_DECODE(Byte,   shortcut);
		PACKET_DECODE(Byte,   daily_buy);
		PACKET_DECODE(Byte,   help_reward);
		PACKET_DECODE(String, name);
		PACKET_DECODE(String, figure_url);
		PACKET_DECODE(UInt32, free_equp_ts);
		PACKET_DECODE(Byte,   speed_up);
		return true;
	}
};

class CDataUser: public CDataBaseDBC, public AsyncDBInterface {
public:
	CDataUser(int table = DB_USER) : CDataBaseDBC(table) {
	}
	virtual void doRequest(CNetPacket* packet);
	int GetUser(uint32_t uid, DataUser& data);
	int GetUserLevel(uint32_t uid, uint32_t &level);

	int AddUser(const DataUser& dataUser);
	int RealAddUser(CNetPacket* packet);

	int SetUser(const DataUser& dataUser);
	int RealSetUser(CNetPacket* packet);

	int ReplaceUser(const DataUser& dataUser);
	int RealReplaceUser(CNetPacket* packet);

	int RemoveUser(const uint32_t uid);
	int RealRemoveUser(CNetPacket* packet);
};

#endif /* DATAUSER_H_ */
