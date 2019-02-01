#ifndef __LOGIC_HERO_H__
#define __LOGIC_HERO_H__

#include "LogicInc.h"

struct HeroAdd
{
	string id, code;
	unsigned star, l;
	HeroAdd(string& i, string& c, unsigned s, unsigned lv)
	{
		id = i;
		code = c;
		star = s;
		l = lv;
	}
};

class CLogicHero
{
public:
	int InitializeHero(unsigned uid);

	int GetHero(unsigned uid, Json::Value &data);
	int GetHero(unsigned uid, map<unsigned,Json::Value> &data);
	int GetHeroUsed(unsigned uid, Json::Value &data);
	int GetHeroAccredited(unsigned uid,unsigned world_pos,Json::Value &data);
	int UpdateHero(unsigned uid, Json::Value &data, Json::Value &result, bool other=false);
	int ImportHero(unsigned uid, const Json::Value &data);

	int Get(unsigned uid, unsigned id, Json::Value &data);
	int Del(unsigned uid, unsigned id);
	int Chg(unsigned uid, unsigned id, Json::Value &data);

	int AddOneHero(unsigned uid, string id,string code,Json::Value &result, string icon="", string name="");
	int AddHeros(unsigned uid, vector<string> &id, vector<string> &code,Json::Value &result);
	int AddHeros(unsigned uid, vector<HeroAdd> &hero, Json::Value &result);

	bool IsGodHero(string &id);

	int AddHeroExp(unsigned uid, unsigned ud, int exp, int& expnow);

	Json::Value genHero(string &id,string &code, string icon="", string name="", unsigned star = 1, unsigned l = 1);
};

#endif
