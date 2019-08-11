/*
 * ReinCarnShengManager.cpp
 *
 *  Created on: 2019年7月29日
 *      Author: next
 */

#include "BattleInc.h"

#define  SHENG_MISSION_TYPE		11

enum ShengmissionPart {
	SHENG_MISSION_PART_0 = 0,
	SHENG_MISSION_PART_1 = 1,
	SHENG_MISSION_PART_2 = 2,
	SHENG_MISSION_PART_3 = 3,
	SHENG_MISSION_PART_4 = 4,
	SHENG_MISSION_PART_5 = 5,
	SHENG_MISSION_PART_6 = 6,
	SHENG_MISSION_PART_7 = 7,
	SHENG_MISSION_PART_ALL = -1,
	SHENG_MISSION_PART_SIZE = 9,
};

ReinCarnShengManager::ReinCarnShengManager() {
}

bool ReinCarnShengManager::CalcProperty(const UserCache &cache, byte rid, PropertySets &props) {
	map<byte, map<byte, uint32_t> >::const_iterator it = cache.role_bag_.begin();
	for (; it != cache.role_bag_.end(); ++it) {
		if (it->first != rid) {
			continue;
		}
		getShengMissionProps(cache, it->second, props);
	}
	PropertyCfg::showProps(cache.uid_, rid, props, "RoleSuit");
	return true;
}

bool ReinCarnShengManager::getShengMissionProps(const UserCache &cache, map<byte, uint32_t> role_equip, PropertySets &props) {
	map<uint32_t, DataShengMission>::const_iterator it = cache.shengMission_.begin();
	for(; it != cache.shengMission_.end(); ++it) {
		for(int i = 0; i < SHENG_MISSION_PART_SIZE - 1; ++i) {
			if(it->second.mission[i]) {
				const CfgReinCarnSheng::ShengMission& sheng_cfg = ShengMissionCfgWrap().getShengMission(i, it->first);
				//增加配置属性
				PropertyCfg::setProps(sheng_cfg.attr(), 1.0, props);
				//增加角色对应位置装备属性百分比
				if(role_equip.count(sheng_cfg.part())) {
					map<uint32_t, DataEquip>::const_iterator item = cache.equip_.find(role_equip[i]);
					if(item != cache.equip_.end()) {
						const CfgItem::Equip& equip_cfg = ItemCfgWrap().GetEquip(item->second.id);
						PropertyCfg::setProps(equip_cfg.attr(), (double)sheng_cfg.rate()/10000, props);
					}
				}
			}
		}

		if(it->second.mission[SHENG_MISSION_PART_SIZE - 1]) {
			//当前阶数，所有任务已完成
			const CfgReinCarnSheng::ShengMission& sheng_cfg = ShengMissionCfgWrap().getShengMission(SHENG_MISSION_PART_ALL, it->first);
			//增加配置属性
			PropertyCfg::setProps(sheng_cfg.attr(), 1.0, props);
			//增加角色所有位置装备属性百分比
			map<byte, uint32_t>::iterator itr = role_equip.begin();
			for(; itr != role_equip.end(); ++itr) {
				map<uint32_t, DataEquip>::const_iterator item = cache.equip_.find(itr->second);
				if(item != cache.equip_.end()) {
					const CfgItem::Equip& equip_cfg = ItemCfgWrap().GetEquip(item->second.id);
					PropertyCfg::setProps(equip_cfg.attr(), (double)sheng_cfg.rate()/10000, props);
				}
			}
		}
	}
	return true;
}

bool ReinCarnShengManager::addShengMission(UserCache& cache, uint32_t reinCarnLevel) {
	DataShengMission data;
	data.init(cache.uid_, TYPE_SHENG_MISSION, reinCarnLevel);
	cache.shengMission_.insert(make_pair(data.reinCarnlevel, data));
	ATTR_DB_ADD(data);
	return true;
}

bool ReinCarnShengManager::addShengCount(UserCache& cache, uint32_t reinCarnLevel) {
	DataShengCount data;
	data.init(cache.uid_, TYPE_SHENG_COUNT, reinCarnLevel);
	cache.shengCount_.insert(make_pair(data.reinCarnlevel, data));
	ATTR_DB_ADD(data);
	return true;
}

int32_t ReinCarnShengManager::getIndexByPart(int32_t part) {
	switch(part) {
	case SHENG_MISSION_PART_0:
		return 0;
	case SHENG_MISSION_PART_1:
		return 1;
	case SHENG_MISSION_PART_2:
		return 2;
	case SHENG_MISSION_PART_3:
		return 3;
	case SHENG_MISSION_PART_4:
		return 4;
	case SHENG_MISSION_PART_5:
		return 5;
	case SHENG_MISSION_PART_6:
		return 6;
	case SHENG_MISSION_PART_7:
		return 7;
	case SHENG_MISSION_PART_ALL:
		return 8;
	default:
		error_log("part out of range");
		throw std::runtime_error("part out of range");
	}
}

bool ReinCarnShengManager::onShengMission(uint32_t uid, uint32_t type, uint32_t num) {
	UserCache& cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return false;
	}
	map<uint32_t, DataMission>::iterator it = cache.mission_.begin();
	for(; it != cache.mission_.end(); ++it) {
		DataMission& data = it->second;
		if(data.status != MISSION_DOING) {
			continue;
		}
		const CfgMission::Mission &cfg = MissionCfgWrap().Get(data.id);
		const CfgReinCarnSheng::ShengMission& sheng_cfg = ShengMissionCfgWrap().getShengMission(cfg.shengid());
		uint32_t reinCarnLevel = sheng_cfg.reincarnlevel();
		if(cache.m_reinCarnInfo.reinCarnLevel < reinCarnLevel) {
			continue;
		}

		for(int i = 0; i < cfg.condition_size(); ++i) {
			if(type != cfg.condition(i).v1()) {
				continue;
			}
			if(0 == cache.shengCount_.count(reinCarnLevel)) {
				addShengCount(cache, reinCarnLevel);
				addShengMission(cache, reinCarnLevel);
			}
			int32_t index  = sheng_cfg.part();
			cache.shengCount_[reinCarnLevel].datas[index] += num;
			ATTR_DB_SET(cache.shengCount_[reinCarnLevel]);

			if(cache.shengCount_[reinCarnLevel].datas[index] < cfg.condition(i).v2())	{
				continue;
			}

			data.step = 1;
			data.status = MISSION_COMPLETE;
			DataMissionManager::Instance()->Set(data);
			MissionManager::Instance()->SendMsg(data);
		}
	}
	return true;
}

bool ReinCarnShengManager::onShengSubMission(uint32_t uid, uint32_t type, uint32_t subType, uint32_t num) {
	UserCache& cache = CacheManager::Instance()->GetUser(uid);
		if(!cache.init_) {
			return false;
		}
		map<uint32_t, DataMission>::iterator it = cache.mission_.begin();
		for(; it != cache.mission_.end(); ++it) {
			DataMission& data = it->second;
			if(data.status != MISSION_DOING) {
				continue;
			}
			const CfgMission::Mission &cfg = MissionCfgWrap().Get(data.id);
			if(SHENG_MISSION_TYPE != cfg.type()) {
				continue;
			}
			const CfgReinCarnSheng::ShengMission& sheng_cfg = ShengMissionCfgWrap().getShengMission(cfg.shengid());
			uint32_t reinCarnLevel = sheng_cfg.reincarnlevel();
			if(cache.m_reinCarnInfo.reinCarnLevel < reinCarnLevel) {
				continue;
			}

			for(int i = 0; i < cfg.condition_size(); ++i) {
					if(cfg.condition(i).v1() == type && cfg.condition(i).v2() == subType) {
					if(0 == cache.shengCount_.count(reinCarnLevel)) {
						addShengCount(cache, reinCarnLevel);
						addShengMission(cache, reinCarnLevel);
					}
					int32_t index  = sheng_cfg.part();
					cache.shengCount_[reinCarnLevel].datas[index] += num;
					ATTR_DB_SET(cache.shengCount_[reinCarnLevel]);
					if( cache.shengCount_[reinCarnLevel].datas[index] < cfg.condition(i).v3()) {
						continue;
					}
					data.step = 1;
					data.status = MISSION_COMPLETE;
					DataMissionManager::Instance()->Set(data);
					MissionManager::Instance()->SendMsg(data);
					break;
				}
			}
		}
		return true;
}

int ReinCarnShengManager::Process(uint32_t uid, logins::SCommitShengMissionReq *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	map<uint32_t, DataMission> &missions = cache.mission_;
	map<uint32_t, DataMission>::iterator itr = missions.find(req->missionId);
	if (itr == missions.end()) {
		error_log("missionId not exist");
		return R_ERROR;
	}

	DataMission &data = itr->second;
	if (data.status == MISSION_COMMIT) {
		MissionManager::Instance()->SendMsg(data);
		return 0;
	}

	data.status = MISSION_COMMIT;
	data.step = 1;
	DataMissionManager::Instance()->Set(data);
	MissionManager::Instance()->SendMsg(data);

	PropertyManager::Instance()->AddUser(uid);

	cache.pre_mission_.insert(data.id);
	missions.erase(itr);

	//保存已完成圣装任务
	const CfgMission::Mission& mission_cfg = MissionCfgWrap().Get(data.id);
	const CfgReinCarnSheng::ShengMission& sheng_cfg = ShengMissionCfgWrap().getShengMission(mission_cfg.shengid());
	DataShengMission& sheng_data = cache.shengMission_[sheng_cfg.reincarnlevel()];
	uint32_t index = getIndexByPart(sheng_cfg.part());
	sheng_data.mission[index] = sheng_cfg.id();
	ATTR_DB_SET(sheng_data);
	LogicManager::Instance()->AddSync(CMD_SHENG_INFO);

	debug_log("uid=%u,id=%d", uid, req->missionId);
	return 0;

}

int ReinCarnShengManager::Process(uint32_t uid, logins::SRequestShengMissionReq *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	if(cache.m_reinCarnInfo.reinCarnLevel < ShengMissionCfgWrap().getLimitReinCarnLevel()) {
		error_log("reinCarn level:%d is limited", cache.m_reinCarnInfo.reinCarnLevel);
		return R_ERROR;
	}
	for(int i = 0; i < SHENG_MISSION_PART_SIZE - 1; ++i) {
		const CfgReinCarnSheng::ShengMission& sheng_cfg = ShengMissionCfgWrap().getShengMission(i, cache.m_reinCarnInfo.reinCarnLevel);
		const CfgMission::Mission& mission_Cfg = MissionCfgWrap().GetByShengId(sheng_cfg.id());
		map<uint32_t, DataMission>& missions = cache.mission_;

		if(0 == cache.mission_.count(mission_Cfg.id())) {
			DataMission data;
			data.uid = uid;
			data.id = mission_Cfg.id();
			data.ts = Time::GetGlobalTime();
			data.status = MISSION_DOING;
			DataMissionManager::Instance()->Add(data);
			missions[data.id] = data;
			MissionManager::Instance()->SendMsg(data);
		}
	}
	return R_SUCCESS;
}

int ReinCarnShengManager::Sync(const UserCache& cache, uint32_t cmd, msgs::SShengInfo *resp) {
	map<uint32_t, DataShengMission>::const_iterator it = cache.shengMission_.begin();
	for(; it != cache.shengMission_.end(); ++it) {
		const DataShengMission& data = it->second;
		for(int i = 0; i < SHENG_MISSION_PART_SIZE; ++i) {
			if(0 != data.mission[i]) {
				resp->shengLst_.push_back(data.mission[i]);
			}
		}
	}
	if (!LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp)) {
		return R_ERROR;
	}
	return 0;
}
