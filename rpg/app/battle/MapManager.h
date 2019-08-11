#ifndef _MAP_MANAGER_H_
#define _MAP_MANAGER_H_

#include "BattleBaseInc.h"
#include "MapAreaState.h"
#include "Human.h"

#define ACTOR_BIRTH_BEGIN_X 114
#define ACTOR_BIRTH_BEGIN_Y 81
#define ACTOR_BIRTH_END_X 119
#define ACTOR_BIRTH_END_Y 86
#define BIRTH_MAP_ID  127

#define DEFAULT_X 3852
#define DEFAULT_Y 2772
#define DEFAULT_MAP_ID 10000

struct MapChangeInfo {
	uint32_t desFbInstanceId;
	uint32_t desMapId;
	Point desPoint;

	MapChangeInfo() {
		desFbInstanceId = 0;
		desMapId = 0;
	}
};

class MapManager : public CSingleton<MapManager> {
public:
	virtual ~MapManager();
	bool init();
	Map *getMapInstance(uint32_t fbInstanceId, uint32_t mapId);
	MapAreaState *getMapAreaStateInstance(uint32_t mapId);
public:
	int Process(uint32_t uid, logins::SRoleMove *req);
	int Process(uint32_t uid, logins::SEnterHang *req);
	int Process(uint32_t uid, logins::SBackToCity *req);
	int Process(uint32_t uid, logins::SMapJump *req);
	int Process(uint32_t uid, logins::SMapTransfer *req);
	int Process(uint32_t uid, logins::SAdvanceRide *req);

public:
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerEnterMap *resp);
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SRoleEnterMap *resp);
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SRoleEnterMapEnd *resp);
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SFightFlyingUp *resp);
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SHangPower *resp);
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SMapEntityEnters *resp);
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SRoleCombatData *resp);
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerCombatData *resp);

public:
	bool ActorLogin(uint32_t uid);
	bool actorTransfer(CFirePacket* pPacket);
	bool actorChangeMap(uint32_t uid, byte role_num, const MapChangeInfo &info);

	void actorOffline(uint32_t uid);
	void enterMapSync();

public:
	static void getDefaultMapInfo(int32_t &mapId, int32_t &x, int32_t &y);
	static void getDefaultPos(Point &point);
	static void getBirthPos(Point &point);

	static string getMapFile(uint32_t mapId);
	static string getMapName(uint32_t mapId);
	static string getwwmFile(uint32_t mapId);
	static bool IsInField(const Point &point, const Point &beginPoint, const Point &endPoint);

public:
	static int savePos(Human *pHuman);
	void mapRemoveObject(uint32_t id);
	void mapMoveObjectDie(MapMoveObject *caster, MapMoveObject *target);
	void mapMoveObjectMsg(MapMoveObject *pMo, Msg *msg, bool self);
	void mapFieldMsg(MapMoveObject *pMo, uint32_t cmd, Msg *msg);

public:
	Human* getHuman(uint32_t uid);
	const map<uint32_t, Human *> &getHumans() {
		return m_humans;
	}
	Human* getHumanByName(string name);
	void getMapHumans(uint32_t fbinstanceId, uint32_t mapId, vector<Human *> &vecHumans);
	void getAroundHuman(MapMoveObject *obj, vector<Human *> &vHuman);
	void getAroundHuman(uint32_t fbInstanceId, uint32_t mapId, const Point &point, map<uint32_t, Human*> &mapHumans);
	void getAroundMonsters(MapMoveObject *pMo, vector<MapMoveObject *> &vecMonsters);
	void getAroundObjects(MapMoveObject *pMo, vector<MapMoveObject *> &objs);
	void getArountPoints(uint32_t mapId, const Point &point, vector<Point> &vecPoints);
	void getAroundPoints(MapMoveObject* pObj, vector<Point> &vecPoints, int16_t distance = 1);
	bool getNearestEmptyPoint(MapMoveObject *pMo, Point &point);
	bool getMonsterBirthPoint(uint32_t fbInstanceId, uint32_t mapId, int zoneId, Point &point);
	bool addObject(MapDisplayObject *object);
	MapDisplayObject *getObject(uint32_t id);
	MapMoveObject *getObject(uint32_t id, int16_t race);
	MapMoveObject *getMonster(uint32_t monsterId);
	MapMoveObject *getMoveObject(uint32_t id);
	void reclaimBirthPoint(uint32_t fbInstanceId, uint32_t mapId, int zoneId, const Point &point);
	bool canMoveTo(Human *pHuman, Map *pMap, const Point &endPoint, const Point &curPoint, Point &desPoint);
public:
	static int calcForwardDirection(const Point &srcPoint, const Point &desPoint);
	static Point calcForwardPosition(int32_t x, int32_t y, int16_t dir, int16_t step);
	static int calcOppositeDirection(int16_t dir);

public:
	void updateSafeArea(const DataLastSafeArea &data);
	void getLastSafeArea(uint32_t rid, DataLastSafeArea &data);
	void getSafeArea(uint32_t rid, int32_t mapId, DataLastSafeArea &data);

public:
	uint32_t createCarbon(uint32_t fbId);
	void destoryCarbon(uint32_t fbInstanceId);
	void eraseObject(MapDisplayObject *pObj);

public:
	bool onSecondTimer();
	bool onTimer();

public:
	bool canUseTransferEquip(Human *pHuman);

private:
	bool canTransfer(Human *pHuman);

private:
	friend class CSingleton<MapManager>;
	MapManager() {
	}

private:
	map<uint32_t, map<uint32_t, Map*> > m_mapCarbon;       // map<fbinstanceId-fbid,map<mapId,Map *> >
	map<uint32_t, Human*> m_humans;                        // map<rid,Human *>
	map<uint32_t, MapDisplayObject*> m_allObjects;         // map<id,MapDisplayObject *>
	map<uint32_t, DataLastSafeArea> m_mapLastSafeArea;     // map<rid,DataLastSafeArea>
	static map<uint32_t, string> m_mapFiles;
	static map<uint32_t, string> m_mapNames;
	static map<uint32_t, string> m_mapwwmFiles;
};
#endif
