#ifndef _LOGIC_HERO_MANAGER_H_
#define _LOGIC_HERO_MANAGER_H_

#include "ServerInc.h"
#include "HeroPropertyManager.h"

class DBCHeroWrap
{
public:
	DBCHeroWrap(unsigned index);
	DBCHeroWrap(unsigned uid, unsigned heroid);

	DataHero& Obj()
	{
		return data_;
	}
	void Save()
	{
		container_->m_data->MarkChange(index_);
	}

	//获取英雄属性
	int GetAttr(HeroAttr& result);
	void GetSkill(vector<char>& skills);
	void FullMessage(ProtoHero::HeroBaseInfoCPP * hero, unsigned extra = 1);
	void SetMessage(ProtoHero::HeroBaseInfoCPP * hero);
	bool AddExp(int exp);
	//激活龙珠
    bool ActDragonBall(int idx);
    bool DragonBallIsAct(int idx);
    //所有龙珠都激活
    bool DragonBallAllAct();

    //升星
    void UpdateStar(unsigned starid);
    //技能升级
	void UpdateSkillLevel(unsigned skillId);
	//基础战力
	double BaseBattlePower();
	//总战力
	unsigned BattlePower();
	static void SetCombineLimit(int idx);
	static void ResetCombineLimit();

private:
	DataHeroManager* container_;
	unsigned		 index_;
	DataHero& 	data_;
	HeroAttr    hero_attr_;
	//组合属性激活标志
	static  bitset<32> combine_limit;
};


class LogicHeroManager : public  BattleSingleton, public CSingleton<LogicHeroManager>
{
private:
	friend class CSingleton<LogicHeroManager>;
	LogicHeroManager(){};

public:
	virtual void CallDestroy() { Destroy();}
	int FullMessage(unsigned uid, User::HerosInfo * herosmsg);
	int AddHeros(unsigned uid, unsigned heroid, string reason);

	template <class T>
	void GetHeroAttr(unsigned uid, unsigned id, T& hero)
	{
		DBCHeroWrap heroWrap(uid, id);
		HeroAttr attr;
		heroWrap.GetAttr(attr);
		hero.hp						=  static_cast<double>(attr.GetAttr(HeroProperty_hp));
		hero.att					=  static_cast<double>(attr.GetAttr(HeroProperty_attack));
		hero.def					=  static_cast<double>(attr.GetAttr(HeroProperty_defend));
		hero.crit					=  attr.GetAttr(HeroProperty_crit_strike);
		hero.acrit  				=  attr.GetAttr(HeroProperty_crit_resist);
		hero.dodge					=  attr.GetAttr(HeroProperty_dodge);
		hero.adodge				 	=  attr.GetAttr(HeroProperty_hit);
		hero.critt					=  attr.GetAttr(HeroProperty_crit_rate)/(double)100;
		hero.speed				 	=  attr.GetAttr(HeroProperty_first);
		hero.battlePower			=  heroWrap.Obj().battle_power;
	}

	void GetSkill(unsigned uid, unsigned id, HeroInfo& hero);
	//掉落龙珠, 玩法改变已弃用
//	pair<int, int> DropDragonBall(unsigned stageId, vector<unsigned>& heroid);

	//购买英雄
	int Process(unsigned uid, ProtoHero::BuyHeroReq* req, ProtoHero::BuyHeroResp* resp);

	//通过金币提升英雄升级
	int Process(unsigned uid, ProtoHero::UpgradeHeroByCoinReq* req, ProtoHero::UpgradeHeroByCoinResp* resp);

	//英雄技能升级
	int Process(unsigned uid, ProtoHero::UpGradeHeroSkillReq* req, ProtoHero::UpGradeHeroSkillResp* resp);

	//英雄升星
	int Process(unsigned uid, ProtoHero::UpGradeHeroStarReq* req, ProtoHero::UpGradeHeroStarResp* resp);

	//设置英雄
	int Process(unsigned uid, ProtoHero::SetHeroReq* req, ProtoHero::SetHeroResp* resp);

	//图鉴碎片激活或取消
	int Process(unsigned uid, ProtoHero::ActArchiveChipReq* req, ProtoHero::ActArchiveChipResp *resp);

	//图鉴奖励
	int Process(unsigned uid, ProtoHero::ArchiveRewardReq* req, ProtoHero::ArchiveRewardResp* resp);

	//龙珠激活
	int Process(unsigned uid, ProtoHero::ProtoActDragonBallReq* req, ProtoHero::ProtoActDragonBallResp* resp);

	//更新战力
	void UpdateBattlePower(unsigned uid);

	//英雄获得分享奖励
	int Process(unsigned uid, ProtoHero::ProtoBuyHeroShareRewardReq* req, ProtoHero::ProtoBuyHeroShareRewardResp* resp);

public:
	//技能初始权重
	static const unsigned initWeight[4];
};


#endif /*_LOGIC_HERO_MANAGER_H_*/
