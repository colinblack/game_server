#ifndef CSKILL_CONFIG_H_
#define CSKILL_CONFIG_H_

#include "Common.h"
#include "CommData.h"

struct SkillConfig {
	uint32_t id;
	byte q;
	vector<uint32_t> cost;

	SkillConfig() : id(0), q(0) {
		cost.clear();
	}
	inline bool operator==(uint32_t id) const {
		return this->id == id;
	}
};

enum SKILL_TYPE {
	SKILL_TYPE_ATTACK = 1, // 攻击
	SKILL_TYPE_HEAL = 2,   // 治疗
	SKILL_TYPE_CALL = 3,   // 召唤
	SKILL_TYPE_PROPS = 4,  // 被动加属性
	SKILL_TYPE_GLORY = 5,  // 光环
	SKILL_TYPE_TRIGGER = 6 // 被动触发
};

enum SKILE_BUILD {
	SKILE_BUILD_NONE = 0,  // 排除建筑
	SKILE_BUILD_EXCEPT = 1 // 排除非建筑
};

class CSkillConfig {

public:
	virtual ~CSkillConfig();
	static CSkillConfig *getInstance() {
		static CSkillConfig instance;
		return &instance;
	}
	bool init(const string &path);
	const SkillConfig* getConfig(uint32_t id);
	bool getCost(uint32_t id, uint32_t lv, uint32_t &cost);
private:
	CSkillConfig();
private:
	vector<SkillConfig> m_config;
};

#endif /* CSKILL_CONFIG_H_ */
