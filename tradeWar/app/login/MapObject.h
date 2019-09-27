/*
 * MapObject.h
 *
 *  Created on: 2015-8-25
 *      Author: aaron
 */

#ifndef MAPOBJECT_H_
#define MAPOBJECT_H_

#include <map>
#include <string>
#include <math.h>
#include "Kernel.h"
#include "CommData.h"
#include "PropertyConfig.h"
#include "TimerInterface.h"
#include "BattleDefine.h"

using namespace std;

#define SPAWN_HERO_ENERGY 15

#define EXTRACT_JSON_UINT(jsonVal,key)	\
	if(jsonVal.isMember(key)){\
			m_data[PropertyConfig::m_attr2Idx[key]].pui = jsonVal[key].asUInt();\
		}
#define EXTRACT_JSON_INT(jsonVal,key)	\
	if(jsonVal.isMember(key)){\
			m_data[PropertyConfig::m_attr2Idx[key]].pi = jsonVal[key].asInt();\
		}
#define EXTRACT_JSON_FLOAT(jsonVal,key)	\
	if(jsonVal.isMember(key)){\
			m_data[PropertyConfig::m_attr2Idx[key]].pf = jsonVal[key].asDouble();\
		}

#define PUSH_JSON_INT(jsonVal,ap)	\
		PropertySets::iterator iter_##ap = m_data.find(ap); \
		if(iter_##ap != m_data.end()) \
		{ \
			if(PropertyConfig::m_idx2Attr.find(ap) != PropertyConfig::m_idx2Attr.end()) \
			{\
				jsonVal[PropertyConfig::m_idx2Attr[ap]] = iter_##ap->second.pi; \
			}\
		}

#define PUSH_JSON_INT_EXT(jsonVal, ap, m_data)	\
		PropertySets::iterator iter_##ap = m_data.find(ap); \
		if(iter_##ap != m_data.end()) \
		{ \
			if(PropertyConfig::m_idx2Attr.find(ap) != PropertyConfig::m_idx2Attr.end()) \
			{\
				jsonVal[PropertyConfig::m_idx2Attr[ap]] = iter_##ap->second.pi; \
			}\
		}


#define PUSH_JSON_FLOAT(jsonVal,ap)	\
		PropertySets::iterator iter_##ap = m_data.find(ap); \
		if(iter_##ap != m_data.end()) \
		{ \
			jsonVal[PropertyConfig::m_idx2Attr[ap]] = iter_##ap->second.pf; \
		}

#define PACK_PROPS(idxArr,buff)	{\
		CBufferWriter writer(&buff);\
		PACKET_ENCODE(Byte,sizeof(idxArr)/sizeof(uint32_t));\
		for(uint32_t i = 0; i < sizeof(idxArr)/sizeof(uint32_t); ++i){\
			PACKET_ENCODE(Byte,idxArr[i]);\
			PACKET_ENCODE(UInt32,m_data[idxArr[i]].pui);\
		}\
	}

struct TargetInfo
{
	uint32_t uid;
	uint32_t race;// 英雄/建筑
	uint32_t ud;
	uint64_t battleId;
	TargetInfo()
	{
		reset();
	}
	void reset(){uid = 0; race = 0; ud = 0; battleId = 0;}
};


struct HurtInfoKey
{
	uint32_t uid; //攻击者uid
	uint32_t ud; //ud
	uint32_t race; //种族
	HurtInfoKey(): uid(0), ud(0), race(0)
	{
	}
	bool operator < (const HurtInfoKey& other)const
	{
		if(uid == other.uid)
		{
			return (race == other.race) ? (ud < other.ud)  : (race < other.race);
		}
		else
		{
			return uid < other.uid;
		}
	}

	bool operator == (const HurtInfoKey& other) const
	{
		return uid == other.uid	&& ud == other.ud && race == other.race;
	}
};
struct HurtInfoValue
{
	int32_t hurt; //伤害总值
	uint32_t lastTime; //最后一次攻击时间(s)
	HurtInfoValue(): hurt(0), lastTime(0)
	{
	}
};
struct HurtInfo
{
	HurtInfoKey hurtInfoKey;
	HurtInfoValue hurtInfoValue;
};

struct AccInfo
{
	uint32_t lastAccTime;
	uint32_t accCount;

	AccInfo()
	{
		lastAccTime = 0;
		accCount = 0;
	}
};

#define MAX_ITEM_PACKET 1024

class PathRlt;
class CSkill;
class MapObject : public ITimerInterface{
public:
	MapObject();
	virtual ~MapObject(){};
public:
	virtual bool encode(IBuffer* buffer) = 0;
	bool encodePropsChange(IBuffer* buffer);
	bool encodePropsChange(IBuffer* buffer,const vector<byte> &propsChange);
	virtual bool onComplelete(uint32_t type){return true;}
	virtual bool onDie(){return true;}
	virtual void setPath(const PathRlt & rlt);
	void onTimer();
	bool onMapObjectHurt(MapObject *pAttacker, uint32_t hurt);
public:
	virtual void propsCalc();
	virtual void unLoadBuffProps();
	virtual void loadBuffProps();
	virtual void getRateProps(PropertySets & props);
	virtual void getAddProps(PropertySets & props);
	void updateProps(const Property &prop,byte type);
public:
	bool existAttr(int attr){return m_data.find(attr) != m_data.end();}
	uint32_t getType(){return m_data[AP_TYPE].pui;}
	uint32_t getUD(){return m_data[AP_UD].pui;}
	uint32_t getLevel(){return m_data[AP_LEVEL].pui;}
	uint32_t getStatus(){return m_data[AP_STATUS].pui;}
	uint32_t getState(){return m_data[AP_STATE].pui;}
	uint32_t getHp(){return m_data[AP_HP].pui;}
	uint32_t getMaxHp(){return m_data[AP_MAX_HP].pui;}
	uint32_t getMp(){return m_data[AP_MP].pui;}
	uint32_t getMaxMp(){return m_data[AP_MAX_MP].pui;}
	uint32_t getCapacity(){return m_data[AP_CAPACITY].pui;}
	uint32_t getMaxCapacity(){return m_data[AP_MAX_CAPACITY].pui;}
	uint32_t getAttackRadius(){return m_data[AP_RANGE].pui;}
	uint32_t getAttackSpeed(){return m_data[AP_RP].pui;}
	uint32_t getMoveSpeed(){return m_data[AP_SP].pui;}
	uint32_t getLastAttackTime(){return m_lastAttackTime;}
	uint32_t getRideSci1(){return m_data[AP_RIDE_SCIENCE1].pui;}
	uint32_t getRideSci2(){return m_data[AP_RIDE_SCIENCE2].pui;}
	uint32_t getCr(){return m_data[AP_CR].pi;}
	uint32_t getCb(){return m_data[AP_CB].pi;}
	uint32_t getCu(){return m_data[AP_CU].pi;}
	uint32_t getCp(){return m_data[AP_CP].pui;}
	uint32_t getUpts(){return m_data[AP_UPTS].pi;}
	uint32_t getHud(){return m_data[AP_HUD].pi;}
	uint32_t getStoneSlot(){return m_data[AP_STONE_SLOT].pi;}
	uint32_t getUpSlot(){return m_data[AP_UPGRADE_SLOT].pi;}
	uint32_t getStationId(){return m_data[AP_HERO_BUNKER].pi;}
	uint32_t getCount(){return m_data[AP_COUNT].pi;}
	uint32_t getStar(){return m_data[AP_STAR].pui;}
	uint32_t getCdTime(){return m_data[AP_CD_TIME].pui;}
	uint32_t getSmeltTimes(){return m_data[AP_EQ_XI].pui;}
	uint32_t getLock(){return m_data[AP_EQUIP_LOCK].pui;}
	uint32_t getRace(){return m_race;}
	uint32_t getMapId(){return m_mapId;}
	uint32_t getUid(){return m_uid;}
	uint64_t getBattleId(){return m_battleId;}
	uint32_t getTick(){return m_tick;}
	uint32_t getCamp(){return m_camp;}
	uint32_t getAppear(){return m_appear;}
	uint32_t getGrade(){return m_data[AP_GRADE].pui;}
	uint32_t getSpirit(){return m_data[AP_SPIRIT].pui;}
	float getPoint(){return m_data[AP_PT].pf;}
	const string& getUserName(){return m_userName;}
	uint32_t getHa(){return m_data[AP_HA].pui;}
	uint32_t getMa(){return m_data[AP_MA].pui;}
	uint32_t getHd(){return m_data[AP_HD].pui;}
	uint32_t getMd(){return m_data[AP_MD].pui;}
	uint32_t getBp(){return m_data[AP_BP].pui;}
	uint32_t getBv(){return m_data[AP_BV].pui;}
	uint32_t getEbp(){return m_data[AP_EBP].pui;}
	uint32_t getEp(){return m_data[AP_EP].pui;}
	uint32_t getHep(){return m_data[AP_HEP].pui;}
	uint32_t getMep(){return m_data[AP_MEP].pui;}
	uint32_t getHr(){return m_data[AP_HR].pui;}
	uint32_t getIp(){return m_data[AP_IP].pui;}
	uint32_t getTa(){return m_data[AP_TA].pui;}
	uint32_t getHe(){return m_data[AP_HE].pui;}
	uint32_t getEv(){return m_data[AP_EV].pui;}
	uint32_t getMe(){return m_data[AP_ME].pui;}
	uint32_t getProf(){return m_data[AP_PROF].pui;}
	uint32_t getCombat(){return m_data[AP_COMBAT].pui;}
	uint32_t getRange(){return m_data[AP_RANGE].pui;}
	void getPos(int & x,int & y){x=m_data[AP_X].pi;y=m_data[AP_Y].pi;}
	int getX(){return m_data[AP_X].pi;}
	int getY(){return m_data[AP_Y].pi;}
	uint32_t getQuality(){return m_data[AP_QUALITY].pui;}
	uint32_t getStrong(){return m_data[AP_STRONG].pui;}
	uint32_t getStoneEud(){return m_data[AP_STONE_EUD].pui;}
	uint32_t getEquipLock(){return m_data[AP_EQUIP_LOCK].pui;}
	uint32_t getHs(){return m_data[AP_WALL_HS].pui;}
	uint32_t getHurt(){return m_data[AP_HURT].pui;}
	uint32_t getEnergy(){return m_data[AP_ENERGY].pui;}
	uint32_t getCe(){return m_data[AP_CE].pui;}
	uint32_t getMaxEnergy(){return m_data[AP_MAX_ENERGY].pui;}
	uint32_t getLockCount(){return m_data[AP_LOCK_COUNT].pui;}

	void setType(uint32_t type){m_data[AP_TYPE].pui = type;}
	void setUD(uint32_t ud){m_data[AP_UD].pui = ud;}
	void setLevel(uint32_t level){m_data[AP_LEVEL].pui = level;}
	void setStatus(uint32_t status){m_data[AP_STATUS].pui = status;}
	void setState(uint32_t state){m_data[AP_STATE].pui = state;}
	void setHp(uint32_t hp){m_data[AP_HP].pui =  hp <= m_data[AP_MAX_HP].pui ? hp :m_data[AP_MAX_HP].pui ;}
	void setMaxMp();
	void setMp(uint32_t mp){m_data[AP_MAX_MP].pui = 200 + getLevel() * 20; m_data[AP_MP].pui = mp < m_data[AP_MAX_MP].pui ? mp : m_data[AP_MAX_MP].pui;}
	bool isFullHp(){return m_data[AP_HP].pui == m_data[AP_MAX_HP].pui;}
	void updateHp(int32_t hp);
	void setMaxHp(uint32_t maxHp){m_data[AP_MAX_HP].pui = maxHp;}
	void setCapacity(uint32_t capacity){m_data[AP_CAPACITY].pui = capacity;}
	void setMaxCapacity(uint32_t capacity){m_data[AP_MAX_CAPACITY].pui = capacity;}
	void setX(int x){m_data[AP_X].pi = x;}
	void setY(int y){m_data[AP_Y].pi = y;}
	void setPos(int x, int y){m_data[AP_X].pi = x;m_data[AP_Y].pi = y;}
	void setMoveSpeed(uint32_t sp){m_data[AP_SP].pui = sp;}
	void setCr(uint32_t t){m_data[AP_CR].pui = t;}
	void setCb(uint32_t t){m_data[AP_CB].pui = t;}
	void setCu(uint32_t t){m_data[AP_CU].pui = t;}
	void setCp(uint32_t t){m_data[AP_CP].pui = t;}
	void setUpts(uint32_t upts){m_data[AP_UPTS].pui = upts;}
	void setHud(uint32_t hud){m_data[AP_HUD].pui = hud;}
	void setUpSlot(uint32_t upSlot){m_data[AP_UPGRADE_SLOT].pui = upSlot;}
	void setUid(uint32_t uid){m_uid = uid;}
	void setTurn(uint32_t turn){m_turn = turn;}
	void setFresh(uint32_t fresh){m_fresh = fresh;}
	void setBattleId(uint64_t battleId){m_battleId = battleId;}
	void setStation(uint32_t bud){m_data[AP_HERO_BUNKER].pi = bud;}
	void setRace(uint32_t race){m_race = race;}
	void setMapId(uint32_t mapId){m_mapId = mapId;}
	void setPosition(int32_t x, int32_t y){m_data[AP_X].pi = x;m_data[AP_Y].pi = y;}
	void setUserName(const string& userName){m_userName = userName;}
	void setCamp(uint32_t camp){m_camp = camp;}
	void setPoint(float point){m_data[AP_PT].pf = point;}
	void setGrade(uint32_t grade){m_data[AP_GRADE].pui = grade;}
	void setAppear(uint32_t appear){m_appear = appear;}
	void setLastAttackTime(uint32_t atime){m_lastAttackTime = atime;}
	void setRideStar(uint32_t t){m_data[AP_RIDE_STAR].pui = t;}
	void setRideLevel(uint32_t t){m_data[AP_RIDE_LEVEL].pui = t;}
	void setRideSci1(uint32_t t){m_data[AP_RIDE_SCIENCE1].pui = t;}
	void setRideSci2(uint32_t t){m_data[AP_RIDE_SCIENCE2].pui = t;}
	void setStar(uint32_t t){m_data[AP_STAR].pui = t;}
	void setCombat(uint32_t c){m_data[AP_COMBAT].pui = c;}
	void setCount(uint32_t c){m_data[AP_COUNT].pui = c;}
	void setQuality(uint32_t c){m_data[AP_QUALITY].pui = c;}
	void setStrong(uint32_t c){m_data[AP_STRONG].pui = c;}
	void setStoneSlot(uint32_t c){m_data[AP_STONE_SLOT].pui = c;}
	void setCdTime(uint32_t c){m_data[AP_CD_TIME].pui = c;}
	void setSmeltTimes(uint32_t c){m_data[AP_EQ_XI].pui = c;}
	void setStoneEud(uint32_t c){m_data[AP_STONE_EUD].pui = c;}
	void setLock(uint32_t c){m_data[AP_EQUIP_LOCK].pui = c;}
	void setHurt(uint32_t c){m_data[AP_HURT].pui = c;}
	bool getAutomatic(){return m_automatic;}
	uint32_t getOriType(){return m_oriType;}
	uint32_t getTurn(){return m_turn;}
	uint32_t getFresh(){return m_fresh;}
	void setHa(uint32_t ha){m_data[AP_HA].pui = ha;}
	void setHd(uint32_t hd){m_data[AP_HD].pui = hd;}
	void setProf(uint32_t prof){m_data[AP_PROF].pui = prof;}
	void setAttackRadius(uint32_t range){m_data[AP_RANGE].pui = range;}
	void setAttackSpeed(uint32_t rp){m_data[AP_RP].pui = rp;}
	void setIp(uint32_t ip){m_data[AP_IP].pui = ip;}
	void setBp(uint32_t bp){m_data[AP_BP].pui = bp;}
	void setBv(uint32_t bv){m_data[AP_BV].pui = bv;}
	void setEffect(uint32_t effect){m_data[AP_EFFECT].pui = effect;}
	void setOriType(uint32_t oriType){m_oriType = oriType;}
	uint32_t getStat(){return m_data[AP_STAT].pui;}
	void setStat(uint32_t stat){m_data[AP_STAT].pui = stat;}
	void setHs(uint32_t hs){m_data[AP_WALL_HS].pui = hs;}
	void setEnergy(uint32_t jl){m_data[AP_ENERGY].pui = jl;}
	void setCe(uint32_t ts){m_data[AP_CE].pui = ts;}
	void setLockCount(uint32_t c){m_data[AP_LOCK_COUNT].pui = c;}

	bool isDizzy(){return getStat() & AP_STAT_DIZZY;}
	bool isInvincible(){return getStat() & AP_STAT_INVINCIBLE;}
	bool getTargetPoint(const Point & srcPoint,int & dx,int & dy);
	bool IsDie(){return m_data[AP_HP].pui == 0;}
	bool isAppear(){return m_appear == STATE_APPEAR;}
	bool isDisappear(){return m_appear == STATE_DISAPPEAR;}
	bool isBuilding(){return getRace() == RACE_TYPE_BUILDING;}
	bool isHero(){return getRace() == RACE_TYPE_HERO;}
	bool isBoss(){return getRace() == RACE_TYPE_WORLD_BOSS;}
	bool isStationNpc(){return getRace() == RACE_TYPE_STATION_NPC;}
	bool isAttackNpc(){return getRace() == RACE_TYPE_ATTACK_NPC;}
	bool isSoldier(){return getRace() == RACE_TYPE_SOLDIER;}
	bool isTrap();
	bool isResourceBuilding();
	bool isStorageBuilding();
	bool isValid();
	bool allowToFight();
	static uint32_t getDistance(MapObject * pMo1,MapObject * pMo2);
	static uint32_t getDistanceRect(const Point &src, const Point &des, uint32_t width, uint32_t heigth);
	static uint32_t getDistance(const Point &src,const Point &des);
	bool setProperty(uint32_t attrIdx,Property prop){if(attrIdx<AP_MAX){m_data[attrIdx]= prop;return true;}return false;}
	Property & getProperty(uint32_t attrIdx){return m_data[attrIdx];}
	void setTick(uint32_t tick){m_tick = tick;}
	void onTick(){m_tick--;}
	void resetFirstAttacker(){m_firstAttacker.hurtInfoKey.uid = 0;}
	uint32_t getTargetUid(){return m_target.uid;}
	uint32_t getTargetRace(){return m_target.race;}
	uint32_t getTargetUd(){return m_target.ud;}
	void resetTarget(){m_target.reset();}
	void setTarget(MapObject* pMo);
	bool inAttackSpeedLimit(uint32_t now);
	bool isSkillSyncToBattle(){return m_isSkillNeedSyncToBattle;}
	bool setSkillSyncToBattle(bool flag){return m_isSkillNeedSyncToBattle = flag;}
	const PropertySets &getProps(){return m_data;}
	void setGuardCenter(Point & center){m_guard_center = center;}
	Point & getGuardCenter(){return m_guard_center;}
public:
	BuffBattleState *getBuffState(){return &m_buffState;}
protected:
	uint32_t m_appear;
	uint32_t m_turn;
	uint32_t m_fresh;
	uint32_t m_camp; // 阵营
	uint32_t m_tick;
	uint32_t m_uid;
	uint32_t m_race;
	uint64_t m_battleId;
	uint32_t m_mapId;
	uint32_t m_lastAttackTime;
	uint32_t m_oriType; // 原始类型(允许多个不同ID的对象有相同的原始类型)
	bool m_automatic;
	string	 m_userName; // 玩家用户名
	PropertySets m_data;
	map<HurtInfoKey, HurtInfoValue> m_hurtMap;       // key:uid<<32+hud
	HurtInfo m_firstAttacker;	//第一攻击者，也是杀死该目标的受益者
	TargetInfo m_target;
	Point m_guard_center;
	bool m_isSkillNeedSyncToBattle;
private:
	BuffBattleState m_buffState;
};
#endif /* MAPOBJECT_H_ */
