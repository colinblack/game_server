/*
 * DataBraveNewWorld.h
 *
 *  Created on: 2017-2-14
 *      Author: Ralf
 */

#ifndef DATABRAVENEWWORLD_H_
#define DATABRAVENEWWORLD_H_


#include <math.h>
#include "Kernel.h"
#include "DataBase.h"

#define BRAVE_NEW_WORLD_SIZE				200
#define BRAVE_NEW_WORLD_LEVEL				10
#define BRAVE_NEW_WORLD_NPC					5
#define BRAVE_NEW_WORLD_ZONE_1				30
#define BRAVE_NEW_WORLD_ZONE_2				9
#define BRAVE_NEW_WORLD_ZONE_3				3
#define BRAVE_NEW_WORLD_ZONE_4				1
#define BRAVE_NEW_WORLD_ZONE (BRAVE_NEW_WORLD_ZONE_1+BRAVE_NEW_WORLD_ZONE_2+BRAVE_NEW_WORLD_ZONE_3+BRAVE_NEW_WORLD_ZONE_4)
#define BRAVE_NEW_WORLD_ZONE_LEVEL			4
#define BRAVE_NEW_WORLD_HP					100
#define BRAVE_NEW_WORLD_HP_USER				20
#define BRAVE_NEW_WORLD_BT					24
#define BRAVE_NEW_WORLD_ME					42000
#define BRAVE_NEW_WORLD_ME_SUPER			42001
#define BRAVE_NEW_WORLD_REWARD				2029
#define BRAVE_NEW_WORLD_USER_MISSION		50
#define BRAVE_NEW_WORLD_USER_REWARD			4055
#define BRAVE_NEW_WORLD_ALLIANCE_MISSION	3

enum DataBraveNewWorldPointType
{
	e_DataBraveNewWorldPointType_disable	= 0,
	e_DataBraveNewWorldPointType_empty		= 1,
	e_DataBraveNewWorldPointType_resource	= 2,
	e_DataBraveNewWorldPointType_zone		= 3,
};
typedef pair<unsigned, unsigned> BraveNewWorldPoint;

enum DataBraveNewWorldMissionStat
{
	e_DataBraveNewWorldMissionStat_uncomplete	= 0,
	e_DataBraveNewWorldMissionStat_complete		= 1,
	e_DataBraveNewWorldMissionStat_got			= 2,
	e_DataBraveNewWorldMissionStat_got2			= -1,
};
enum DataBraveNewWorldMissionType
{
	e_DataBraveNewWorldMissionType_move		= 1,
	e_DataBraveNewWorldMissionType_coin		= 2,
	e_DataBraveNewWorldMissionType_occupy	= 3,
};

/**********************************************************/
class DataBraveNewWorldPoint {
public:
	unsigned int x;
	unsigned int y;
	unsigned int uid;
	bool def;
	unsigned int hero;
	unsigned int hp;
	unsigned int fid;
	unsigned int fts;
	unsigned int rts;
	unsigned int rc;
	unsigned int mtype;
	unsigned int mcount;
	unsigned int defts;  //堡垒建立时间

	void Clear()
	{
		uid = 0;
		def = false;
		hero = 0;
		hp = 0;
		rts = Time::GetGlobalTime();
	}

	DataBraveNewWorldPoint() {
		x = 0;
		y = 0;
		uid = 0;
		def = false;
		hero = 0;
		hp = 0;
		fid = 0;
		fts = 0;
		rts = 0;
		rc = 0;
		mtype = 0;
		mcount = 0;
		defts = 0;
	}

	~DataBraveNewWorldPoint() {
	}

	void Serialize(BraveNewWorld::BraveNewWorldPoint *p) {
		p->set_x(x);
		p->set_y(y);
		p->set_uid(uid);
		p->set_def(def);
		p->set_hero(hero);
		p->set_hp(hp);
		p->set_fid(fid);
		p->set_fts(fts);
		p->set_rts(rts);
		p->set_rc(rc);
		p->set_mtype(mtype);
		p->set_mcount(mcount);
		p->set_defts(defts);
	}

	void Parse(const BraveNewWorld::BraveNewWorldPoint &p) {
		x = p.x();
		y = p.y();
		uid = p.uid();
		def = p.def();
		hero = p.hero();
		hp = p.hp();
		fid = p.fid();
		fts = p.fts();
		rts = p.rts();
		if(p.has_rc())
			rc = p.rc();
		else
			rc = 0;

		if (p.has_mtype())
		{
			mtype = p.mtype();
		}
		else
		{
			mtype = 0;
		}

		if (p.has_mcount())
		{
			mcount = p.mcount();
		}
		else
		{
			mcount = 0;
		}

		if (p.has_defts())
		{
			defts = p.defts();
		}
		else
		{
			defts = Time::GetGlobalTime();
		}
	}

	void GetJsonLimit(Json::Value& res)
	{
		res["x"] = x;
		res["y"] = y;
		res["uid"] = uid;
		res["rc"] = rc;
		res["mtype"] = mtype;
		res["mcount"] = mcount;
	}
	void GetJson(Json::Value& res)
	{
		GetJsonLimit(res);
		res["fid"] = fid;
		res["fts"] = fts;
		res["rts"] = rts;
	}

	void GetDefLimit(Json::Value& res)
	{
		if(def)
		{
			//判断堡垒是否建立已超过50小时
			unsigned now = Time::GetGlobalTime();

			if (now >= (defts + 50*3600))
			{
				ClearDef();
			}
			else
			{
				res["def"]["hp"] = hp;
				res["def"]["defts"] = defts;
			}
		}
	}

	void GetDef(Json::Value& res)
	{
		if(def)
		{
			//判断堡垒是否建立已超过50小时
			unsigned now = Time::GetGlobalTime();

			if (now >= (defts + 50*3600))
			{
				ClearDef();
			}
			else
			{
				res["def"]["hp"] = hp;
				res["def"]["hero"] = hero;
				res["def"]["defts"] = defts;
			}
		}
	}

	void ClearDef()
	{
		def = false;
		hero = 0;
		hp = 0;
		defts = 0;
	}
};
class DataBraveNewWorldHistory {
public:
	unsigned int uid;
	unsigned int type;
	unsigned int x;
	unsigned int y;
	unsigned int lm;
	unsigned int nm;
	unsigned int lh;
	unsigned int nh;
	unsigned int ts;
	DataBraveNewWorldHistory() {
		uid = 0;
		type = 0;
		x = 0;
		y = 0;
		lm = 0;
		nm = 0;
		lh = 0;
		nh = 0;
		ts = 0;
	}
	~DataBraveNewWorldHistory() {
	}
	void Serialize(BraveNewWorld::BraveNewWorldHistory *p) {
		p->set_uid(uid);
		p->set_type(type);
		p->set_x(x);
		p->set_y(y);
		p->set_lm(lm);
		p->set_nm(nm);
		p->set_lh(lh);
		p->set_nh(nh);
		p->set_ts(ts);
	}
	void Parse(const BraveNewWorld::BraveNewWorldHistory &p) {
		uid = p.uid();
		type = p.type();
		x = p.x();
		y = p.y();
		lm = p.lm();
		nm = p.nm();
		lh = p.lh();
		nh = p.nh();
		ts = p.ts();
	}

	void GetJson(Json::Value& res)
	{
		res["uid"] = uid;
		res["type"] = type;
		res["x"] = x;
		res["y"] = y;
		res["lm"] = lm;
		res["nm"] = nm;
		res["lh"] = lh;
		res["nh"] = nh;
		res["ts"] = ts;
	}
};
class DataBraveNewWorldFavourate {
public:
	unsigned int x;
	unsigned int y;
	DataBraveNewWorldFavourate() {
		x = 0;
		y = 0;
	}
	DataBraveNewWorldFavourate(BraveNewWorldPoint &p) {
		x = p.first;
		y = p.second;
	}
	~DataBraveNewWorldFavourate() {
	}
	void Serialize(BraveNewWorld::BraveNewWorldFavourate *p) {
		p->set_x(x);
		p->set_y(y);
	}
	void Parse(const BraveNewWorld::BraveNewWorldFavourate &p) {
		x = p.x();
		y = p.y();
	}
	void GetJson(Json::Value& res)
	{
		res["x"] = x;
		res["y"] = y;
	}
};
class DataBraveNewWorldUserMission {
public:
	int m1;
	int m2;
	unsigned int mx;
	unsigned int my;
	int m3;
	DataBraveNewWorldUserMission() {
		m1 = 0;
		m2 = 0;
		mx = 0;
		my = 0;
		m3 = 0;
	}
	~DataBraveNewWorldUserMission() {
	}
	void Serialize(BraveNewWorld::BraveNewWorldUserMission *p) {
		p->set_m1(m1);
		p->set_m2(m2);
		p->set_mx(mx);
		p->set_my(my);
		p->set_m3(m3);
	}
	void Parse(const BraveNewWorld::BraveNewWorldUserMission &p) {
		m1 = p.m1();
		m2 = p.m2();
		mx = p.mx();
		my = p.my();
		m3 = p.m3();
	}
	void GetJson(Json::Value& res)
	{
		res["mission"]["m1"] = m1;
		res["mission"]["m2"] = m2;
		res["mission"]["m3"] = m3;
		res["mission"]["mx"] = mx;
		res["mission"]["my"] = my;
	}
};
class DataBraveNewWorldUser {
public:
	unsigned int uid;
	unsigned int seq;
	unsigned int aid;
	unsigned int lv;
	unsigned int x;
	unsigned int y;
	unsigned int rts;
	unsigned int hts;
	unsigned int pts;
	unsigned int bts;
	unsigned int bt;
	unsigned int tts;
	unsigned int rl;
	vector<unsigned int> hp;
	list<DataBraveNewWorldHistory> his;
	vector<DataBraveNewWorldFavourate> fav;
	DataBraveNewWorldUserMission mission;
	set<BraveNewWorldPoint> lands;
	DataBraveNewWorldUser() {
		uid = 0;
		seq = 0;
		aid = 0;
		lv = 0;
		x = 0;
		y = 0;
		rts = 0;
		hts = 0;
		pts = 0;
		bts = 0;
		bt = 0;
		tts = 0;
		rl = 0;
	}
	~DataBraveNewWorldUser() {
	}

	void RandMission()
	{
		mission.m1 = 0;
		mission.m2 = 0;
		mission.m3 = 0;
		int x = mission.mx, y = mission.my, rx = BRAVE_NEW_WORLD_USER_MISSION-Math::GetRandomInt(BRAVE_NEW_WORLD_USER_MISSION*2), ry = BRAVE_NEW_WORLD_USER_MISSION-Math::GetRandomInt(BRAVE_NEW_WORLD_USER_MISSION*2);
		mission.mx = max(0,min(BRAVE_NEW_WORLD_SIZE-1, x+rx));
		mission.my = max(0,min(BRAVE_NEW_WORLD_SIZE-1, y+ry));
	}

	void Serialize(BraveNewWorld::BraveNewWorldUser *p) {
		p->set_uid(uid);
		p->set_seq(seq);
		p->set_aid(aid);
		p->set_lv(lv);
		p->set_x(x);
		p->set_y(y);
		p->set_rts(rts);
		p->set_hts(hts);
		p->set_pts(pts);
		p->set_bts(bts);
		p->set_bt(bt);
		p->set_tts(tts);
		p->set_rl(rl);
		for (vector<unsigned int>::iterator it = hp.begin(); it != hp.end();++it)
			p->add_hp(*it);
		for (list<DataBraveNewWorldHistory>::iterator it = his.begin(); it != his.end(); ++it)
			it->Serialize(p->add_his());
		for (vector<DataBraveNewWorldFavourate>::iterator it = fav.begin(); it != fav.end(); ++it)
			it->Serialize(p->add_fav());
		mission.Serialize(p->mutable_mission());
	}
	void Parse(const BraveNewWorld::BraveNewWorldUser &p) {
		uid = p.uid();
		seq = p.seq();
		aid = p.aid();
		lv = p.lv();
		x = p.x();
		y = p.y();
		rts = p.rts();
		hts = p.hts();
		pts = p.pts();
		bts = p.bts();
		bt = p.bt();
		tts = p.tts();
		if(p.has_rl())
			rl = p.rl();
		else
			rl = 0;
		for (int i = 0; i < p.hp_size(); ++i)
			hp.push_back(p.hp(i));
		for (int i = 0; i < p.his_size(); ++i)
		{
			DataBraveNewWorldHistory t;
			t.Parse(p.his(i));
			his.push_back(t);
		}
		for (int i = 0; i < p.fav_size(); ++i)
		{
			DataBraveNewWorldFavourate t;
			t.Parse(p.fav(i));
			fav.push_back(t);
		}
		if(p.has_mission())
			mission.Parse(p.mission());
		else
			RandMission();

		if(hp.size() != BRAVE_NEW_WORLD_HP_USER)
		{
			hp.clear();
			for(int i=0;i<BRAVE_NEW_WORLD_HP_USER;++i)
				hp.push_back(BRAVE_NEW_WORLD_HP);
		}
	}

	void GetJson(Json::Value& res)
	{
		res["seq"] = seq;
		res["x"] = x;
		res["y"] = y;
		res["rts"] = rts;
		res["hts"] = hts;
		res["pts"] = pts;
		res["bts"] = bts;
		res["bt"] = bt;
		res["tts"] = tts;
		res["rl"] = rl;
		res["hp"].resize(0);
		for(unsigned i=0;i<hp.size();++i)
			res["hp"].append(hp[i]);
		res["lands"].resize(0);
		for(set<BraveNewWorldPoint>::iterator it=lands.begin();it!=lands.end();++it)
		{
			Json::Value t;
			t["x"] = it->first;
			t["y"] = it->second;
			res["lands"].append(t);
		}
		mission.GetJson(res);
	}
	void GetDefLimit(Json::Value& res)
	{
		res["user"]["uid"] = uid;
		res["user"]["lv"] = lv;
		res["user"]["hp"] = hp[0];
	}
	void GetDef(Json::Value& res)
	{
		res["user"]["uid"] = uid;
		res["user"]["lv"] = lv;
		res["user"]["hp"].resize(0);
		for(unsigned i=0;i<hp.size();++i)
			res["user"]["hp"].append(hp[i]);
		res["user"]["pts"] = pts;
	}
};
class DataBraveNewWorldZone {
public:
	unsigned int id;
	unsigned int aid;
	unsigned int ts;
	DataBraveNewWorldZone() {
		id = 0;
		aid = 0;
		ts = 0;
	}
	~DataBraveNewWorldZone() {
	}
	void Serialize(BraveNewWorld::BraveNewWorldZone *p) {
		p->set_id(id);
		p->set_aid(aid);
		p->set_ts(ts);
	}
	void Parse(const BraveNewWorld::BraveNewWorldZone &p) {
		id = p.id();
		aid = p.aid();
		ts = p.ts();
	}

	void GetJson(Json::Value& res)
	{
		res["id"] = id;
		res["aid"] = aid;
		res["ts"] = ts;
	}
};
class DataBraveNewWorldAllianceMission {
public:
	unsigned int id;
	bool m;
	DataBraveNewWorldAllianceMission() {
		id = 0;
		m = false;
	}
	~DataBraveNewWorldAllianceMission() {
	}
	void Serialize(BraveNewWorld::BraveNewWorldAllianceMission *p) {
		p->set_id(id);
		p->set_m(m);
	}
	void Parse(const BraveNewWorld::BraveNewWorldAllianceMission &p) {
		id = p.id();
		m = p.m();
	}
	void GetJson(Json::Value& res)
	{
		res["id"] = id;
		res["m"] = m?1:0;
	}
};
class DataBraveNewWorldAlliance {
public:
	unsigned int aid;
	map<unsigned int, DataBraveNewWorldAllianceMission> mission;
	DataBraveNewWorldAlliance() {
		aid = 0;
	}
	~DataBraveNewWorldAlliance() {
	}

	void RandMission()
	{
		mission.clear();
		unsigned id1 = 1+Math::GetRandomInt(BRAVE_NEW_WORLD_ZONE_1);
		mission[id1].id = id1;
		unsigned id2 = 1+BRAVE_NEW_WORLD_ZONE_1+Math::GetRandomInt(BRAVE_NEW_WORLD_ZONE_2);
		mission[id2].id = id2;
		unsigned id3 = 1+BRAVE_NEW_WORLD_ZONE_1+BRAVE_NEW_WORLD_ZONE_2+Math::GetRandomInt(BRAVE_NEW_WORLD_ZONE_3);
		mission[id3].id = id3;
	}

	void Serialize(BraveNewWorld::BraveNewWorldAlliance *p) {
		p->set_aid(aid);
		for (map<unsigned int, DataBraveNewWorldAllianceMission>::iterator it =
				mission.begin(); it != mission.end(); ++it)
			it->second.Serialize(p->add_mission());
	}
	void Parse(const BraveNewWorld::BraveNewWorldAlliance &p) {
		aid = p.aid();
		for (int i = 0; i < p.mission_size(); ++i)
			mission[p.mission(i).id()].Parse(p.mission(i));
		if(mission.size() != BRAVE_NEW_WORLD_ALLIANCE_MISSION)
			RandMission();
	}

	void GetJson(Json::Value& res)
	{
		res["alliance"].resize(0);
		for(map<unsigned int, DataBraveNewWorldAllianceMission>::iterator it=mission.begin();it!=mission.end();++it)
		{
			Json::Value t;
			it->second.GetJson(t);
			res["alliance"].append(t);
		}
	}
};
class DataBraveNewWorld {
public:
	map<BraveNewWorldPoint, DataBraveNewWorldPoint> land;
	map<unsigned int, DataBraveNewWorldUser> user;
	map<unsigned int, DataBraveNewWorldZone> zone;
	map<unsigned int, DataBraveNewWorldAlliance> alliance;
	map<BraveNewWorldPoint, unsigned> city;
	DataBraveNewWorld() {
	}
	~DataBraveNewWorld() {
	}
	void Serialize(BraveNewWorld::BraveNewWorld *p) {
		for (map<BraveNewWorldPoint, DataBraveNewWorldPoint>::iterator it = land.begin(); it != land.end(); ++it)
			it->second.Serialize(p->add_land());
		for (map<unsigned int, DataBraveNewWorldUser>::iterator it = user.begin(); it != user.end(); ++it)
			it->second.Serialize(p->add_user());
		for (map<unsigned int, DataBraveNewWorldZone>::iterator it = zone.begin(); it != zone.end(); ++it)
			it->second.Serialize(p->add_zone());
		for (map<unsigned int, DataBraveNewWorldAlliance>::iterator it = alliance.begin(); it != alliance.end(); ++it)
			it->second.Serialize(p->add_alliance());
	}
	void Parse(const BraveNewWorld::BraveNewWorld &p) {
		for (int i = 0; i < p.land_size(); ++i)
			land[BraveNewWorldPoint(p.land(i).x(),p.land(i).y())].Parse(p.land(i));
		for (int i = 0; i < p.user_size(); ++i)
		{
			unsigned uid = p.user(i).uid();
			user[uid].Parse(p.user(i));
			city[BraveNewWorldPoint(user[uid].x, user[uid].y)] = uid;
		}
		for (int i = 0; i < p.zone_size(); ++i)
			zone[p.zone(i).id()].Parse(p.zone(i));
		for (int i = 0; i < p.alliance_size(); ++i)
			alliance[p.alliance(i).aid()].Parse(p.alliance(i));

		if(land.size() != BRAVE_NEW_WORLD_SIZE * BRAVE_NEW_WORLD_SIZE)
		{
			land.clear();
			for(unsigned i=0;i<BRAVE_NEW_WORLD_SIZE;++i)
			{
				for(unsigned j=0;j<BRAVE_NEW_WORLD_SIZE;++j)
				{
					BraveNewWorldPoint p(i, j);
					DataBraveNewWorldPoint d;
					d.x = i;
					d.y = j;
					land[p] = d;
				}
			}
		}
		if(zone.size() != BRAVE_NEW_WORLD_ZONE)
		{
			zone.clear();
			for(unsigned i=1;i<=BRAVE_NEW_WORLD_ZONE;++i)
			{
				DataBraveNewWorldZone d;
				d.id = i;
				zone[i] = d;
			}
		}

		for(map<BraveNewWorldPoint, DataBraveNewWorldPoint>::iterator it=land.begin();it!=land.end();++it)
		{
			if(it->second.uid)
				user[it->second.uid].lands.insert(it->first);
		}
	}
};
/**********************************************************/

class CDataBraveNewWorld : public DataBase
{
public:
	CDataBraveNewWorld(string path);
	virtual ~CDataBraveNewWorld(){}
	int Init();
	int Save();
	int Sig(int sig);

	static const unsigned m_rect[BRAVE_NEW_WORLD_LEVEL][2][2];
	static unsigned m_zone[BRAVE_NEW_WORLD_ZONE][2][2];
	static unsigned m_user_point[BRAVE_NEW_WORLD_LEVEL];
	static int m_user_money[BRAVE_NEW_WORLD_LEVEL];

	int GetSelf(unsigned uid, unsigned aid, unsigned lv, Json::Value &result);
	int GetMissionInfo(unsigned uid, Json::Value &result);
	int GetPoints(vector<BraveNewWorldPoint>& p, Json::Value &result);
	int GetOnePoint(BraveNewWorldPoint& p, Json::Value &result);
	int GetPointsLimit(vector<BraveNewWorldPoint>& p, Json::Value &result);
	int GetZones(vector<unsigned>& z, Json::Value &result);
	int GetHistory(unsigned uid, Json::Value &result);
	int GetFavourate(unsigned uid, Json::Value &result);
	int Collect(unsigned uid, unsigned seq, Json::Value &result);
	int StartAttack(unsigned uid, unsigned seq, BraveNewWorldPoint& p, bool cash, Json::Value &result);
	int EndAttack(unsigned uid, unsigned seq, BraveNewWorldPoint& p, vector<unsigned>& hp, Json::Value &result);
	int FastAttack(unsigned uid, unsigned seq, BraveNewWorldPoint& p, bool cash, bool cash1, Json::Value &result);
	int Move(unsigned uid, unsigned seq, BraveNewWorldPoint& p, unsigned ud, bool super, Json::Value &result);
	int Build(unsigned uid, unsigned seq, bool cash, BraveNewWorldPoint& p, Json::Value &result);
	int Defend(unsigned uid, unsigned seq, bool cash, BraveNewWorldPoint& p, unsigned hero, Json::Value &result);
	int RecoverPoint(unsigned uid, unsigned seq, BraveNewWorldPoint& p, bool cash, Json::Value &result);
	int RevcoverUser(unsigned uid, unsigned seq, bool cash, Json::Value &result);
	int Discard(unsigned uid, unsigned seq, BraveNewWorldPoint& p, Json::Value &result);
	int JoinAlliance(unsigned uid, unsigned userid, unsigned aid, Json::Value &result);
	int SetFavourate(unsigned uid, unsigned seq, vector<BraveNewWorldPoint>& p, Json::Value &result);
	int Buy_hts(unsigned uid, unsigned seq, Json::Value &result);
	int Buy_bts(unsigned uid, unsigned seq, Json::Value &result);
	int Buy_bt(unsigned uid, unsigned seq, unsigned count, Json::Value &result);
	int CollectOne(unsigned uid, unsigned seq, BraveNewWorldPoint& p, Json::Value &result);
	int AttackSelf(unsigned uid, unsigned seq, BraveNewWorldPoint& p, Json::Value &result);
	int GetMission(unsigned uid, unsigned seq, unsigned type, Json::Value &result);

private:
	int getPointLevel(unsigned x, unsigned y);
	BraveNewWorldPoint getRandPoint(unsigned level);
	BraveNewWorldPoint getRandPointEmpty(unsigned level);
	int getPointLevel(BraveNewWorldPoint& p) { return getPointLevel(p.first, p.second);}
	int getZoneID(unsigned x, unsigned y);
	int getZoneID(BraveNewWorldPoint& p) { return getZoneID(p.first, p.second);}
	int getZoneLevel(unsigned id);
	int getZonePoints(unsigned id, set<BraveNewWorldPoint>& p);
	unsigned getCityUser(BraveNewWorldPoint& p) {if(m_data.city.count(p)) return m_data.city[p];	return 0;}
	unsigned getCityUser(unsigned x, unsigned y) { BraveNewWorldPoint p(x, y); return getCityUser(p);}
	bool isBeside(int x1, int y1, int x2, int y2) {return abs(x1-x2) <= 1 && abs(y1-y2) <= 1;}
	bool isBeside(BraveNewWorldPoint& p1, BraveNewWorldPoint& p2) {return isBeside(p1.first, p1.second, p2.first, p2.second);}
	unsigned getUserPoint(unsigned lv) {if(lv > BRAVE_NEW_WORLD_LEVEL || lv == 0) return 0; return m_user_point[lv-1];}
	int getUserMoney(unsigned lv) {if(lv > BRAVE_NEW_WORLD_LEVEL || lv == 0) return 0; return m_user_money[lv-1];}
	void getBesidePoints(BraveNewWorldPoint&p, set<BraveNewWorldPoint>& b);

	//材料的掉落
	int GetMaterial(unsigned uid, DataBraveNewWorldPoint & point, Json::Value & result);

	//判断该州府内是否存在有该用户的地块
	bool CheckZonePoint(unsigned zid, unsigned uid);

	void CreateMap();
	void OnDay();
	void OnHour();
	void OnHalfHour();

	DataBraveNewWorld m_data;

	int  m_material_type;  //当前的刷新材料类型
};

#endif /* DATABRAVENEWWORLD_H_ */
