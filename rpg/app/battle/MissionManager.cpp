/*
 * MissionManager.cpp
 *
 *  Created on: 2019年6月20日
 *      Author: Administrator
 */

#include "MissionManager.h"
#include "BattleInc.h"

MissionManager::MissionManager() {

}

MissionManager::~MissionManager() {

}

bool MissionManager::Init() {
	m_unknow.insert(MT_ROLE_LEVEL);
	m_unknow.insert(MT_REINCARNATION);
	m_unknow.insert(MT_HANG_LEVEL);
	m_unknow.insert(MT_UNKNOW_3);
	m_unknow.insert(MT_UNKNOW_4);
	m_unknow.insert(MT_ACTIVATE_SHENQI_PIECES);
	m_unknow.insert(MT_REACTIVE_SHENQI);
	m_unknow.insert(MT_UPGRADE_STATE);
	m_unknow.insert(MT_UNKNOW_8);
	m_unknow.insert(MT_UNKNOW_9);
	m_unknow.insert(MT_UNKNOW_10);
	m_unknow.insert(MT_UNKNOW_11);
	m_unknow.insert(MT_UNKNOW_12);
	m_unknow.insert(MT_UNKNOW_13);
	m_unknow.insert(MT_UNKNOW_14);
	m_unknow.insert(MT_UNKNOW_15);
	m_unknow.insert(MT_CHALLANGE_BOSS);
	m_unknow.insert(MT_UNKNOW_17);
	m_unknow.insert(MT_UNKNOW_18);
	m_unknow.insert(MT_UNKNOW_19);
	m_unknow.insert(MT_UNKNOW_20);
	m_unknow.insert(MT_UNKNOW_21);
	m_unknow.insert(MT_UNKNOW_22);
	m_unknow.insert(MT_UNKNOW_23);
	m_unknow.insert(MT_UNKNOW_24);
	m_unknow.insert(MT_UNKNOW_25);
	m_unknow.insert(MT_UNKNOW_26);
	m_unknow.insert(MT_UNKNOW_27);
	m_unknow.insert(MT_UNKNOW_28);
	m_unknow.insert(MT_UNKNOW_29);
	m_unknow.insert(MT_UNKNOW_30);
	m_unknow.insert(MT_TREASUREHUNT);
	m_unknow.insert(MT_UNKNOW_32);
	m_unknow.insert(MT_UNKNOW_33);
	m_unknow.insert(MT_UNKNOW_34);
	m_unknow.insert(MT_ACHIEVEMENT);
	m_unknow.insert(MT_UNKNOW_36);
	m_unknow.insert(MT_UNKNOW_37);
	m_unknow.insert(MT_UNKNOW_38);
	m_unknow.insert(MT_UNKNOW_39);
	m_unknow.insert(MT_UNKNOW_40);
	m_unknow.insert(MT_UNKNOW_41);
	m_unknow.insert(MT_UNKNOW_42);
	m_unknow.insert(MT_UNKNOW_43);
	m_unknow.insert(MT_UNKNOW_44);
	m_unknow.insert(MT_UNKNOW_45);
	m_unknow.insert(MT_UNKNOW_46);
	m_unknow.insert(MT_UNKNOW_47);
	m_unknow.insert(MT_UNKNOW_48);
	m_unknow.insert(MT_UNKNOW_49);
	m_unknow.insert(MT_UNKNOW_50);
	m_unknow.insert(MT_UNKNOW_51);
	m_unknow.insert(MT_UNKNOW_52);
	m_unknow.insert(MT_UNKNOW_53);
	m_unknow.insert(MT_UNKNOW_54);
	m_unknow.insert(MT_UNKNOW_55);
	m_unknow.insert(MT_UNKNOW_56);
	m_unknow.insert(MT_UNKNOW_57);
	m_unknow.insert(MT_UNKNOW_58);
	m_unknow.insert(MT_UNKNOW_59);
	m_unknow.insert(MT_UNKNOW_60);
	m_unknow.insert(MT_UNKNOW_61);
	m_unknow.insert(MT_UNKNOW_62);
	m_unknow.insert(MT_UNKNOW_63);
	m_unknow.insert(MT_UNKNOW_64);
	m_unknow.insert(MT_UNKNOW_65);
	m_unknow.insert(MT_UNKNOW_66);
	m_unknow.insert(MT_UNKNOW_67);
	m_unknow.insert(MT_UNKNOW_68);
	m_unknow.insert(MT_UNKNOW_69);
	m_unknow.insert(MT_UNKNOW_70);
	m_unknow.insert(MT_UNKNOW_71);
	m_unknow.insert(MT_UNKNOW_72);
	m_unknow.insert(MT_UNKNOW_73);
	m_unknow.insert(MT_UNKNOW_74);
	m_unknow.insert(MT_UNKNOW_75);
	m_unknow.insert(MT_UNKNOW_76);
	m_unknow.insert(MT_UNKNOW_77);
	m_unknow.insert(MT_UNKNOW_78);
	m_unknow.insert(MT_UNKNOW_79);
	m_unknow.insert(MT_UNKNOW_80);
	m_unknow.insert(MT_UNKNOW_81);
	m_unknow.insert(MT_UNKNOW_82);
	m_unknow.insert(MT_UNKNOW_83);
	m_unknow.insert(MT_UNKNOW_84);
	m_unknow.insert(MT_UNKNOW_85);
	m_unknow.insert(MT_UNKNOW_86);
	m_unknow.insert(MT_UNKNOW_87);
	m_unknow.insert(MT_UNKNOW_88);
	m_unknow.insert(MT_UPGRADE_SKILL);
	m_unknow.insert(MT_KILL_HANG_MONSTER);
	m_unknow.insert(MT_SMELT_EQUIP);
	m_unknow.insert(MT_STRENGTH_EQUIP);
	m_unknow.insert(MT_UNKNOW_93);
	m_unknow.insert(MT_ACTIVATE_TREASURE);
	m_unknow.insert(MT_UPGRADE);
	m_unknow.insert(MT_UNKNOW_96);
	m_unknow.insert(MT_UNKNOW_97);
	m_unknow.insert(MT_UNKNOW_98);
	m_unknow.insert(MT_UNKNOW_99);
	m_unknow.insert(MT_UNKNOW_100);
	m_unknow.insert(MT_UNKNOW_101);
	m_unknow.insert(MT_UNKNOW_102);
	m_unknow.insert(MT_UNKNOW_103);
	m_unknow.insert(MT_UNKNOW_104);
	m_unknow.insert(MT_UNKNOW_105);
	m_unknow.insert(MT_UNKNOW_106);
	m_unknow.insert(MT_UNKNOW_107);
	m_unknow.insert(MT_UNKNOW_108);
	m_unknow.insert(MT_UNKNOW_109);
	m_unknow.insert(MT_UNKNOW_110);
	m_unknow.insert(MT_UNKNOW_111);
	m_unknow.insert(MT_UNKNOW_112);
	m_unknow.insert(MT_UNKNOW_113);
	m_unknow.insert(MT_UNKNOW_114);
	m_unknow.insert(MT_UNKNOW_115);
	m_unknow.insert(MT_UNKNOW_116);
	m_unknow.insert(MT_UNKNOW_117);
	m_unknow.insert(MT_ATTACH_NPC);
	m_unknow.insert(MT_KILL_MONSTER);
	return true;
}

bool MissionManager::ActorLogin(uint32_t uid) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	if (cache.mission_.empty()) {
		InitMission(cache);
	}
	return true;
}

bool MissionManager::InitMission(UserCache &cache) {
	map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->mission_cfg_Index;
	if (indexs.empty()) {
		return false;
	}
	DataMission data;
	data.uid = cache.uid_;
	data.id = indexs.begin()->first;
	data.step = 0;
	data.status = 1;
	data.ts = Time::GetGlobalTime();
	DataMissionManager::Instance()->Add(data);
	cache.mission_[data.id] = data;
	return true;
}

bool MissionManager::SendMsg(const DataMission &m) {
	dbs::TPlayerMission msg;
	msg.playerId_ = m.uid;
	msg.missionId_ = m.id;
	msg.step_ = m.step;
	msg.status_ = m.status;
	msg.requestDt_ = m.ts * 1000LL;
	msg.extend_ = m.extend;
	LogicManager::Instance()->SendMsg(m.uid, CMD_UPDATE_PLAYER_MISSION, &msg);
	return true;
}

bool MissionManager::TestCheck(uint32_t uid) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	MissionCfgWrap cfg_wrap;
	map<uint32_t, DataMission>::iterator itr = cache.mission_.begin();
	for (; itr != cache.mission_.end(); ++itr) {
		DataMission &item = itr->second;
		if (item.status != MISSION_DOING
		|| item.ts + 100 > Time::GetGlobalTime()) {
			continue;
		}
		const CfgMission::Mission &cfg = cfg_wrap.Get(item.id);
		for (int i = 0; i < cfg.condition_size(); ++i) {
			uint32_t type = cfg.condition(i).v1();
			if (m_unknow.find(type) == m_unknow.end()) {
				debug_log("id=%u type=%u", item.id, type);
				continue;
			}
			item.status = MISSION_COMPLETE;
			DataMissionManager::Instance()->Set(item);
			SendMsg(item);
		}
	}
	return true;
}

uint32_t MissionManager::AddIv(string &str, uint32_t t, uint32_t n) {
	static Json::Reader reader;
	static Json::FastWriter writer;

	string key;
	String::Format(key, "%u", t);
	Json::Value value;
	if (str.empty() || !reader.parse(str, value)) {
		value = Json::Value(Json::objectValue);
		value["iv"][key] = 0;
	}
	value["iv"][key] = value["iv"][key].asUInt() + n;
	str = writer.write(value);
	return value["iv"][key].asUInt();
}

uint32_t MissionManager::AddMv(string &str, uint32_t t, uint32_t st, uint32_t n) {
	static Json::Reader reader;
	static Json::FastWriter writer;

	string key, sub_key;
	String::Format(key, "%u", t);
	String::Format(sub_key, "%u", st);

	Json::Value value;
	if (str.empty() || !reader.parse(str, value)) {
		value = Json::Value(Json::objectValue);
		value["mv"][key] = Json::Value(Json::objectValue);
		value["mv"][key][sub_key] = 0;
	}
	value["mv"][key][sub_key] = value["mv"][key][sub_key].asUInt() + n;
	str = writer.write(value);
	return value["mv"][key][sub_key].asUInt();
}

bool MissionManager::OnKillHangMonster(uint32_t uid, uint32_t id, uint32_t num) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	map<uint32_t, DataMission>::iterator itr = cache.mission_.begin();
	MissionCfgWrap cfg_wrap;

	for (; itr != cache.mission_.end(); ++itr) {
		DataMission &data = itr->second;
		if (data.status != MISSION_DOING) {
			continue;
		}
		const CfgMission::Mission &cfg = cfg_wrap.Get(data.id);
		for (int i = 0; i < cfg.condition_size(); ++i) {
			uint32_t type = cfg.condition(i).v1();
			if (MT_KILL_HANG_MONSTER != type) {
				continue;
			}
			uint32_t curr = AddIv(data.extend, type, num);
			if (curr >= cfg.condition(i).v2()) {
				data.status = MISSION_COMPLETE;
			}
			DataMissionManager::Instance()->Set(data);
			SendMsg(data);
		}
	}
	return true;
}

bool MissionManager::OnHangLevel(uint32_t uid) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	map<uint32_t, DataMission>::iterator itr = cache.mission_.begin();
	MissionCfgWrap cfg_wrap;

	for (; itr != cache.mission_.end(); ++itr) {
		DataMission &data = itr->second;
		if (data.status != MISSION_DOING) {
			continue;
		}
		const CfgMission::Mission &cfg = cfg_wrap.Get(data.id);
		for (int i = 0; i < cfg.condition_size(); ++i) {
			uint32_t type = cfg.condition(i).v1();
			if (MT_HANG_LEVEL != type) {
				continue;
			}
			if (cache.base_.hang < cfg.condition(i).v2()) {
				continue;
			}
			data.status = MISSION_COMPLETE;
			DataMissionManager::Instance()->Set(data);
			SendMsg(data);
		}
	}
	return true;
}

bool MissionManager::onUpgrade(uint32_t uid,uint32_t advanceType,uint32_t num){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	map<uint32_t, DataMission>::iterator itr = cache.mission_.begin();
	MissionCfgWrap cfg_wrap;
	for (; itr != cache.mission_.end(); ++itr) {
		DataMission &data = itr->second;
		if (data.status != MISSION_DOING) {
			continue;
		}
		const CfgMission::Mission &cfg = cfg_wrap.Get(data.id);
		for (int i = 0; i < cfg.condition_size(); ++i) {
			uint32_t type = cfg.condition(i).v1();
			if (MT_UPGRADE != type) {
				continue;
			}
			if (cfg.condition(i).v2() != advanceType) {
				continue;
			}
			uint32_t level =0;
			list<DataAdvance>::iterator its = cache.advance_.begin();
			for (; its != cache.advance_.end(); ++its) {
				if (its->type ==advanceType) {
					if((uint32_t)its->level>level){
						level = its->level;
					}
				}
			}
			uint32_t curr = AddMv(data.extend, MT_UPGRADE,advanceType,level);
			if (curr < cfg.condition(i).v3()) {
				continue;
			}
			data.status = MISSION_COMPLETE;
			//data.step=1;
			DataMissionManager::Instance()->Set(data);
			SendMsg(data);
		}
	}
	return true;
}

bool MissionManager::onActivateShenqi(uint32_t uid,uint32_t itemId){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	map<uint32_t, DataMission>::iterator itr = cache.mission_.begin();
	MissionCfgWrap cfg_wrap;
	for (; itr != cache.mission_.end(); ++itr) {
		DataMission &data = itr->second;
		if (data.status != MISSION_DOING) {
			continue;
		}
		const CfgMission::Mission &cfg = cfg_wrap.Get(data.id);
		for (int i = 0; i < cfg.condition_size(); ++i) {
			uint32_t type = cfg.condition(i).v1();
			if (MT_ACTIVATE_SHENQI_PIECES != type) {
				continue;
			}
			if (cfg.condition(i).v2() != itemId) {
				continue;
			}
			data.status = MISSION_COMPLETE;
			DataMissionManager::Instance()->Set(data);
			SendMsg(data);
		}
	}
	return true;
}

bool MissionManager::onUpgradeSkill(uint32_t uid,uint32_t num){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	map<uint32_t, DataMission>::iterator itr = cache.mission_.begin();
	MissionCfgWrap cfg_wrap;
	for (; itr != cache.mission_.end(); ++itr) {
		DataMission &data = itr->second;
		if (data.status != MISSION_DOING) {
			continue;
		}
		const CfgMission::Mission &cfg = cfg_wrap.Get(data.id);
		for (int i = 0; i < cfg.condition_size(); ++i) {
			uint32_t type = cfg.condition(i).v1();
			if (MT_UPGRADE_SKILL != type) {
				continue;
			}
			if (num<cfg.condition(i).v2()) {
				continue;
			}
			data.status = MISSION_COMPLETE;
			DataMissionManager::Instance()->Set(data);
			SendMsg(data);
		}
	}
	return true;
}



int MissionManager::Process(uint32_t uid, logins::SMissionReq *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	MissionCfgWrap cfg_wrap;
	if (!cfg_wrap.IsExist(req->missionId_)) {
		return 0;
	}
	const CfgMission::Mission &cfg = cfg_wrap.Get(req->missionId_);
	map<uint32_t, DataMission> &missions = cache.mission_;
	map<uint32_t, DataMission>::iterator itr = missions.find(req->missionId_);
	if (itr != missions.end()) {
		return R_ERROR;
	}
	DataMission data;
	data.uid = uid;
	data.id = cfg.id();
	data.ts = Time::GetGlobalTime();
	data.status = MISSION_DOING;
	DataMissionManager::Instance()->Add(data);
	missions[data.id] = data;
	SendMsg(data);
	return 0;
}

int MissionManager::Process(uint32_t uid, logins::SMissionCommit *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	map<uint32_t, DataMission> &missions = cache.mission_;
	map<uint32_t, DataMission>::iterator itr = missions.find(req->missionId_);
	if (itr == missions.end()) {
		return R_ERROR;
	}

	DataMission &data = itr->second;
	if (data.status == MISSION_COMMIT) {
		SendMsg(data);
		return 0;
	}
	data.status = MISSION_COMMIT;
	data.step = 1;
	DataMissionManager::Instance()->Set(data);
	UpdateManager::Instance()->SetCode(UC_MissionReward);
	const CfgMission::Mission &cfg = MissionCfgWrap().Get(req->missionId_);
	Award reward;
	reward.Format(cfg.reward(), 1);
	UserManager::Instance()->Reward(uid, reward, "mission_" + CTrans::ITOS(req->missionId_));
	ReinCarnManager::Instance()->onAddExp(uid,cfg.exp());
	SendMsg(data);
	debug_log("uid=%u,id=%d", uid, req->missionId_);

	return 0;
}

int MissionManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerMissionList *resp) {
	const map<uint32_t, DataMission> &missions = cache.mission_;
	map<uint32_t, DataMission>::const_iterator itr = missions.begin();
	for (; itr != missions.end(); ++itr) {
		const DataMission &data = itr->second;
		if (data.status == MISSION_UNKNOW || data.status == MISSION_COMMIT) {
			continue;
		}
		dbs::TPlayerMission item;
		item.clear();
		item.playerId_ = cache.uid_;
		item.missionId_ = itr->first;
		item.step_ = data.step;
		item.status_ = data.status;
		item.requestDt_ = data.ts * 1000LL;
		resp->missions_.push_back(item);
	}
	if (!LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp)) {
		return R_ERROR;
	}
	return 0;
}
