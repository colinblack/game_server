#ifndef _MAP_MOVE_OBJECT_H_
#define _MAP_MOVE_OBJECT_H_

#include "BattleBaseInc.h"
#include "MapAreaState.h"
#include "MapDisplayObject.h"
#include "PathManager.h"

#define MIN_MOVE_DISTANCE 0.0001f

struct SkillUseInfo {
	uint32_t skillId;
	uint16_t skillLevel;
	uint32_t hurtSkillId;
	uint32_t nextUseTime;
	uint32_t cdTime;
	uint32_t allCdTime;
	uint32_t costValue;
	uint32_t entityId;

	SkillUseInfo() {
		skillId = 0;
		skillLevel = 0;
		hurtSkillId = 0;
		nextUseTime = 0;
		cdTime = 0;
		allCdTime = 0;
		costValue = 0;
		entityId = 0;
	}

	SkillUseInfo &operator =(const SkillUseInfo &other) {
		skillId = other.skillId;
		skillLevel = other.skillLevel;
		nextUseTime = other.nextUseTime;
		cdTime = other.cdTime;
		allCdTime = other.allCdTime;
		costValue = other.costValue;
		entityId = other.entityId;
		return *this;
	}
};

struct AttackInfo {
	int addHurt;
	float addHurtRate;
	int hurtType;
	bool holyFlag; // true无视防御

	AttackInfo() {
		addHurt = 0;
		hurtType = 0;
		addHurtRate = 0.0;
		holyFlag = false;
	}
};

struct HurtInfo {
	uint32_t id; //攻击者id
	uint32_t race; //种族
	int32_t hurt; //伤害总值
	uint32_t lastTime; //最后一次攻击时间(s)
	double recog;

	HurtInfo() {
		id = 0;
		race = 0;
		hurt = 0;
		lastTime = 0;
		recog = 0;
	}

	void Clear() {
		id = 0;
		race = 0;
		hurt = 0;
		lastTime = 0;
		recog = 0;
	}
};

enum MOVE_TYPE {
	MOVE_TYPE_NONE	= 0,
	MOVE_TYPE_WALK	= 0x1,
	MOVE_TYPE_RUN	= 0x2,
	MOVE_TYPE_AI	= 0x4,
	MOVE_TYPE_CLI	= 0x8,

	MOVE_TYPE_MAX
};

class MapMoveObject: public MapDisplayObject {
public:
	MapMoveObject();
	virtual ~MapMoveObject();
protected:
	int dir_;
	int move_type_;			//1 walk 2 run
	int zone_id_;
	int dx_;				//destination
	int dy_;
	int bx_;				//birth pos
	int by_;
	int ltx_;				//last target pos
	int lty_;
	bool protect_flag_;
	bool hide_flag_;
	bool need_recove_;
	bool is_active_;
	bool pathing_flag_;
	float dis_;
	float dis_left_;
	float dis_move_;
	float dis_x_;
	float dis_y_;
	uint32_t next_skill_time_;
	uint32_t entity_id_;
	uint32_t pos_idx_;
	uint32_t state_;
	uint32_t last_move_time_;
	uint32_t alive_time_;
	uint32_t combat_;
	uint16_t body_width_;
	uint16_t level_;
	uint16_t speed_;
	uint16_t move_id_;
	byte sex_;
	byte career_;
	string name_;
	PropertySets props_;
	HurtInfo first_attacker_;
	HurtInfo last_attacker_;
	vector<msgs::SFightUpdate> fight_update_;
	vector<Point> target_points_;
	map<uint64_t, HurtInfo> hurt_map_;		// key:race<<32+id
	map<int32_t, SkillUseInfo> map_skill_info_;
	map<int16_t, int32_t> shows_;
	map<int16_t, int64_t> diff_attr;
	map<int16_t, int64_t> diff_fix_attr;
	list<APath::pos> move_path_;

public:
	static uint32_t getDistance(const MapMoveObject *pMoA, const MapMoveObject *pMoB);
	static uint32_t getDistance(Point p1, Point p2);
	static uint32_t getDistance(int sx, int sy, int ex, int ey);
public:
	virtual Msg* doAppear();
	virtual bool propsCalc();
	virtual void getRateProps(PropertySets &props);
	virtual void getAddProps(PropertySets &props);
	virtual void setPath(const PathRlt &rlt);
	virtual void setPath(const vector<Point> &path);
	virtual void doAi();
	virtual bool doAttack(MapMoveObject *other);
	virtual bool doRecover();
	virtual void onDie();
	virtual void onHurt(MapMoveObject *caster, const PropertySets &hurtProps);
	virtual void onAttack(int attackType);
	virtual void onFirstAttackerChange();
	virtual void onSetPath();
	virtual void onSetState();
	virtual void onUpdate(short type);
	virtual void doHurt(const PropertySets &props);
	virtual bool doLearnSKill(int32_t skillId);
	virtual bool skillUp(int32_t skillId);
	virtual bool initSkill();
	virtual bool updateSkillProficient(int32_t skillId);
	virtual void syncMoveInfo(bool self);
	virtual bool moveTick();
	virtual bool moveStop();
	virtual bool checkNextWayPoint(bool pop);
	virtual const SkillUseInfo* getSkill(uint32_t skillId);
	virtual void getFightUpdate(vector<msgs::SFightUpdate> &data);
	virtual void addFightUpdate(msgs::SFightUpdate &data);
	virtual bool isAlive();
	virtual uint32_t getBodyWidth();
	virtual void getShow(map<int16_t, int32_t> &data);
	virtual void setShow(uint16_t id, uint32_t value);
	virtual void sendShow();
	virtual uint32_t calcCombat();
	virtual void setProps(const PropertySets &props);
	virtual void getDiffProps(map<int16_t, int64_t> &diff, map<int16_t, int64_t> &fix);
	virtual void setFirstAttacker(MapMoveObject *pMo);
	virtual void addHp(int32_t hp);
public:
	void setLastAttacker(uint32_t race, uint32_t id);
	void setLastAttacker(MapMoveObject *pAttacker);
	bool isAttackAble(MapMoveObject *destObj);
	bool getTargetPoint(int &x, int &y);
	bool addTargetPoint(int &x, int &y);
	bool checkEntityId(uint32_t entityid);
public:
	// inline get and set
	void setPosIdx(uint32_t id) {
		pos_idx_ = id;
	}
	uint32_t getPosIdx() {
		return pos_idx_;
	}
	double getRecog() {
		return recog_;
	}
	void getLastPos(int &x, int &y) {
		x = lx_;
		y = ly_;
	}
	int getLastMapId() {
		return last_map_id_;
	}
	void setBirthPos(int x, int y) {
		bx_ = x;
		by_ = y;
	}
	void getBirthPos(int &x, int &y) {
		x = bx_;
		y = by_;
	}
	void setZoneId(int id) {
		zone_id_ = id;
	}
	int getZoneId() {
		return zone_id_;
	}
	void setEntityId(uint32_t id) {
		entity_id_ = id;
	}
	uint32_t getEntityId() {
		return entity_id_;
	}
	void getDPos(int &x, int &y) {
		x = dx_;
		y = dy_;
	}
	void setDir(int dir) {
		dir_ = dir;
	}
	int getDir() {
		return dir_;
	}
	void setMoveType(int type) {
		move_type_ = type;
	}
	int getMoveType() {
		return move_type_;
	}
	string getName() {
		return name_;
	}
	float getMoveSpeed() {
		return static_cast<float>(speed_) / 1000;
	}
	int16_t getSpeed() {
		return speed_;
	}
	int getLevel() {
		return level_;
	}
	PropertySets& getProps() {
		return props_;
	}
	bool isDie() {
		if (props_[AP_HP].pl == 0) {
			state_ |= AP_STAT_DIE;
			return true;
		}
		return false;
	}
	void setProp(int type, const Property& theProp) {
		props_[type].pi = theProp.pi;
	}
	void setState(uint32_t state) {
		state_ |= state;
		onSetState();
	}
	void delState(uint32_t state) {
		state_ &= ~state;
	}
	uint32_t getLastMoveTime() {
		return last_move_time_;
	}
	void setLastMoveTime(uint32_t ts) {
		last_move_time_ = ts;
	}
	bool isFullHp() {
		return props_[AP_HP].pl >= props_[AP_MAXLIFE].pl;
	}
	int64_t getHp() {
		return props_[AP_HP].pl;
	}
	uint32_t getMaxHp() {
		return props_[AP_MAXLIFE].pl;
	}
	HurtInfo* getLastAttacker() {
		return &last_attacker_;
	}
	uint32_t getLastAttackedTime() {
		return last_attacker_.lastTime;
	}
	void setProtected(bool flag) {
		protect_flag_ = flag;
	}
	bool getProtected() {
		return this->protect_flag_;
	}
	void setHideFlag(bool flag) {
		hide_flag_ = flag;
		ltx_ = 0;
	}
	bool getHideFlag() {
		return this->hide_flag_;
	}
	void setActive(bool flag) {
		is_active_ = flag;
	}
	bool isActive() {
		return is_active_;
	}
	bool isInBirthPos() {
		return x_ == bx_ && y_ == by_;
	}
	const HurtInfo &getFirstAttacker() {
		return first_attacker_;
	}
	void clearFirstAttacker() {
		first_attacker_.Clear();
	}
	bool isNeedRecove() {
		return need_recove_;
	}
	void setNeedRecove(bool flag) {
		need_recove_ = flag;
	}
	uint32_t getCombat() {
		return combat_;
	}
	byte getSex() {
		return sex_;
	}
	byte getCareer() {
		return career_;
	}
	bool getRide() {
		return (state_ & AP_STAT_RIDE) != 0;
	}
	void setMoveId(uint16_t id) {
		move_id_ = id;
	}
	void setRide(bool v) {
		if (v) {
			setState(AP_STAT_RIDE);
		} else {
			delState(AP_STAT_RIDE);
		}
		onUpdate(ATTR_UPDATE_RIDE);
	}
	uint16_t getMoveId() {
		return move_id_;
	}
};

#endif /* _MAP_MOVE_OBJECT_H_ */
