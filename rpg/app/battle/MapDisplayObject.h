#ifndef _MAP_DISPLAY_OBJECT_H_
#define _MAP_DISPLAY_OBJECT_H_

#include "Kernel.h"
#include "MsgDef.h"

//races
enum RACE_TYPE {
	RACE_UNKNOW = 0,
	RACE_HUMAN = 1,
	RACE_MONSTER = 2,
	RACE_PET = 3,
	RACE_EFFECTS = 4,

	RACE_MAX
};

enum FORCE_TYPE {
	FORCE_FRIEND = 0,
	FORCE_HOSTILE = 1
};

enum ATTR_UPDATE_TYPE {
	ATTR_UPDATE_RIDE = 52,
	ATTR_UPDATE_HURT = 300,
	ATTR_UPDATE_HP = 301,
	ATTR_UPDATE_POINT = 309,
	ATTR_UPDATE_NUQI = 312,
	ATTR_UPDATE_MAX
};

#define IS_MONSTER_RACE(race) (race == RACE_MONSTER)

#define RACE_EQUIP 100

#define ID_COEFFICIENT 1.0

class MapDisplayObject {
public:
	MapDisplayObject();
	virtual ~MapDisplayObject();
	virtual void getPos(int& x, int& y);
	virtual uint32_t getId();
	virtual uint32_t getRid();
	virtual uint32_t getRealFbId();
	virtual uint32_t getMapId();
	virtual uint32_t getFbId();
	virtual uint32_t getLastFbId();
	virtual uint32_t getBelong();
	virtual uint32_t getOwner();
	virtual int16_t getForce();
	virtual int32_t  getRace();
	virtual Identity getEntityMsg();

public:
	virtual void setPos(int x, int y);
	virtual void setMapId(uint32_t id);
	virtual void setFbId(uint32_t id);
	virtual void setRealFbId(uint32_t id);
	virtual void setBelong(uint32_t id);
	virtual void setOwner(uint32_t id);
	virtual void setForce(int16_t v);

public:
	virtual void onSetPos();
	virtual void onSetMapId();
	virtual void onSetFbId();
	virtual void onDestory();
	virtual Msg* doAppear() = 0;

protected:
	void idInit();

protected:
	int lx_;			//last x
	int ly_;			//last y
	int x_;				//curr x
	int y_;				//curr y
	byte role_id_;
	int32_t race_;
	uint32_t id_;			//uid in map
	uint32_t map_id_;
	uint32_t last_map_id_;
	uint32_t fb_id_;
	uint32_t last_fb_id_;
	uint32_t belong_id_;
	uint32_t owner_id_;
	int16_t force_;
	uint32_t real_fb_id;
	double recog_;
	Identity entity_msg_;
	static list<uint32_t> idList;
	static list<uint32_t> otherIdList; //非需要AI驱动物件
public:
	static uint32_t maxMonsterId;
};

#endif
