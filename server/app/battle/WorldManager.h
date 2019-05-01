/*
 * WorldManager.h
 *
 *  Created on: 2016-9-8
 *      Author: Ralf
 */

#ifndef WORLDMANAGER_H_
#define WORLDMANAGER_H_

#include "ServerInc.h"

#define RMI ResourceManager::Instance()
#define HMI HeroPropertyManager::Instance()
#define BMI BattleFieldManager::Instance()
#define UMI UserManager::Instance()
#define LMI LogicManager::Instance()
#define CMI ConfigManager::Instance()
#define WMI WorldManager::Instance()
#define ATTMI MemoryAttackHarborManager::Instance()

#define SEQ_GET_HMI(seq) HMI->m_data->item[seq]
#define SEQ_GET_RMI(seq) RMI->m_data->item[seq]
#define GET_BMI BMI->m_data
#define SEQ_GET_BMI_CITY(seq) GET_BMI->city[seq]

#define GET_HMI(hi) SEQ_GET_HMI(HMI->GetIndex(hi))
#define GET_RMI(uid) SEQ_GET_RMI(RMI->GetIndex(uid))
#define GET_BMI_CITY(cid) SEQ_GET_BMI_CITY(BMI->getCitySeq(cid))
#define GET_BRMI(uid) BattleRewardManager::Instance()->m_data->data[BattleRewardManager::Instance()->GetIndex(uid)]

#define HERO_INFO(id) CMI->GetHero(id)
#define NPC_INFO(id) CMI->GetNPC(id)
#define DEMO_TIME CMI->demo.m_config.timeconfig()
#define DEMO_CONST CMI->demo.m_config.constconfig()
#define DEMO_REWARD CMI->demo.m_config.reward()
#define DEMO_CITY(cid) CMI->GetGid(cid)
#define DEMO_NPC_DAY(day,type) CMI->GetNPCID(day,type)
#define DEMO_NPC CMI->demo.m_config.npc()
#define SCIENCE_ITEM(id) CMI->GetScience(id)

/***************************************************/
class BattleDemoHero
{
public:
	static unsigned gatenpcid;
	HeroPropertyItemIndex index;
	vector<int> property;
	vector<int> hp;
	vector<uint8_t> shape;
	uint8_t skill;
	unsigned extraid;
	uint16_t city;
	uint16_t gate;
	unsigned ouid;
	unsigned oid;
	unsigned kingdom;
	int hurt, damage;
	BattleDemoHero* enemy;
	BattleReward reward;
	int hpi;

	void Clear()
	{
		hurt = damage = 0;
		enemy = NULL;
	}
	inline double RewardM()
	{
		return double(hurt);
	}
	inline double RewardV()
	{
		if(property[DemoFightProperty_s_level] && property[DemoFightProperty_s_level] <= DEMO_REWARD.v_c_size())
			return double(DEMO_REWARD.v_c(property[DemoFightProperty_s_level]-1));
		return double(DEMO_REWARD.v_c(0));
	}
	inline double RewardB(unsigned type)
	{
		if(type == e_battle_city || type == e_battle_rush)
			return double(DEMO_REWARD.b_c_w());
		return double(DEMO_REWARD.b_c_o());
	}
	inline double RewardC()
	{
		double c = double(damage)/double(hurt);
		if(c < DEMO_REWARD.c_1())
			return double(DEMO_REWARD.c_1_c());
		else if(c < DEMO_REWARD.c_2())
			return (c + double(1))*double(DEMO_REWARD.c_2_c());
		else
			return double(DEMO_REWARD.c_3_c());
	}
	inline double RewardI(unsigned l)
	{
		if(property[DemoFightProperty_u_level] + DEMO_REWARD.i() <= l)
		{
			return double(1)+min(double(1), double(l-property[DemoFightProperty_u_level]-DEMO_REWARD.i()+1)*double(DEMO_REWARD.i_c()));
		}
		return double(1);
	}
	inline double RewardF(unsigned k, unsigned range)
	{
		double x = double(0);
		if(k && kingdom != k)
		{
			if(range <= BATTLE_RANGE_1)
				x = double(DEMO_REWARD.f_1());
			else if(range <= BATTLE_RANGE_2)
				x = double(DEMO_REWARD.f_2());
			else if(range <= BATTLE_RANGE_3)
				x = double(DEMO_REWARD.f_3());
		}
		return double(1) + x;
	}
	inline double RewardFB(unsigned type, unsigned l)
	{
		if(type == e_battle_gate)
		{
			if(property[DemoFightProperty_u_level] > (int)l)
				return max(double(0), double(1)-(double(property[DemoFightProperty_u_level]-l)*DEMO_REWARD.fb()));
		}
		return double(1);
	}
	void CheckReward(unsigned type, unsigned k, unsigned range);
	bool CheckDie(unsigned type);
	static void Die(HeroPropertyItemIndex hi, unsigned k, uint16_t cid, unsigned type);
	BattleDemoHero(HeroPropertyItemIndex hi, bool otherVision=false, double diff=double(1));
	BattleDemoHero(const ProtoBattleField::HeroUid &hero);

	//战法伤害系数
	double GetHeroSkill();
	//是否是强化战术
	bool IsStrengthShape(unsigned g, unsigned s);
	//强化战术伤害
	double GetStrengthShape();
	//平砍地形加成系数
	double GetHeroAttackG(unsigned g);
	//科技战法加成
	double GetHeroTech();
	//科技战法抵抗
	double GetHeroAntiTech();
	//经验加成
	double GetExtraEXP();
	//技能排数
	unsigned GetSkillRange();
	//hp系数
	double GetHPX();
	//禁卫系数
	double GetRangeX(unsigned k, unsigned range);
	//获取英雄id
	unsigned GetHeroID()
	{
		if(index.IsUser())
			return index.id;
		return oid;
	}
	void Injure(int d, BattleDemoHero* e, int &explode);
	void Injure(int d, unsigned m, BattleDemoHero* e, int &explode);

	void SetMessage(ProtoBattleField::Hero* msg)
	{
		msg->set_id(index.id);
		for(unsigned i=0;i<property.size();++i)
			msg->add_property(property[i]);
		for(unsigned i=0;i<hp.size();++i)
			msg->add_hp(hp[i]);
		for(unsigned i=0;i<shape.size();++i)
			msg->add_shape(shape[i]);
		msg->set_skill(skill);
		msg->set_extraid(extraid);
		msg->set_city(city);
		msg->set_gate(gate);
		if(index.notHero())
		{
			msg->set_ouid(ouid);
			msg->set_oid(oid);
		}
	}
	unsigned SetMessage(ProtoBattleField::HeroUid* msg)
	{
		msg->set_uid(index.uid);
		SetMessage(msg->mutable_hero());
		if(index.notHero())
			return ouid;
		return index.uid;
	}
	int GetUnit()
	{
		return property[DemoFightProperty_soldier] - hpi;
	}
	int GetHp()
	{
		if(hpi < property[DemoFightProperty_soldier])
			return hp[hpi];
		return 0;
	}
	unsigned GetShape()
	{
		if(hpi < property[DemoFightProperty_soldier])
			return shape[hpi];
		return 0;
	}
	void SetShape(unsigned form)
	{
		if(hpi < property[DemoFightProperty_soldier])
		{
			if(shape[hpi] == DemoS_unchosen)
				shape[hpi] = form;
		}
	}
	void RandomShape(unsigned eshape)
	{
		if(hpi < property[DemoFightProperty_soldier])
		{
			if(shape[hpi] == DemoS_unchosen || shape[hpi] == DemoS_skill)
				shape[hpi] = Math::GetRandomInt(DemoS_shpae_3) + 1;
			else if(shape[hpi] == DemoS_shpae_a)
			{
				if(eshape >= DemoS_shpae_1 && eshape <= DemoS_shpae_3)
					shape[hpi] = (eshape == DemoS_shpae_1) ? DemoS_shpae_3 : (eshape - 1);
				else
					shape[hpi] = Math::GetRandomInt(DemoS_shpae_3) + 1;
			}
		}
	}
	bool HasSkill()
	{
		return hp[0] == property[DemoFightProperty_hp];
	}
	unsigned GetWingEffect()
	{
		if(extraid && hpi == property[DemoFightProperty_soldier] - 1)
			return extraid;
		return 0;
	}
};
typedef list<BattleDemoHero> BattleDemoQueue;
/***************************************************/
class BattleDemo
{
public:
	unsigned type;
	unsigned kingdom;//争霸和单挑
	uint16_t cid;//争霸和单挑
	unsigned range;//争霸和单挑
	unsigned uid;//闯关 竞技场
	uint16_t gate;//闯关 竞技场rank
	unsigned gid;
	unsigned nextts;
	bool waiting;
	int a_shape, d_shape, att_shape, def_shape, a_explode, d_explode;
	vector<int> a_skill, d_skill, a_attack, d_attack;
	double a_s, d_s;
	BattleDemoQueue attacker, defender;
	set<unsigned> watcher;
	ProtoBattleField::ReplyCity m_msg;
	BattleReward reward;//闯关
	bool immediately;

	void Clear()
	{
		waiting = true;
		a_shape = d_shape = att_shape = def_shape = a_explode = d_explode = 0;
		a_s = d_s = double(0);
		a_skill.clear();
		d_skill.clear();
		a_attack.clear();
		d_attack.clear();
		m_msg.Clear();
	}
	BattleDemo():type(0),kingdom(0),cid(0),range(0),uid(0),gate(0),gid(0),nextts(0),immediately(false) {Clear();}
	BattleDemo(uint16_t c);
	BattleDemo(unsigned u, unsigned g, unsigned gi, vector<HeroPropertyItemIndex> &hi, vector<unsigned> &npc, double diff);
	BattleDemo(uint16_t c, HeroPropertyItemIndex att, HeroPropertyItemIndex def);
	BattleDemo(unsigned u, unsigned r, vector<HeroPropertyItemIndex> &hi, vector<HeroPropertyItemIndex> &enemy, unsigned g = 0);
	BattleDemo(ProtoBattleField::RequestFight *msg, ProtoBattleField::ReplyFight *resp);
	~BattleDemo(){}
	void SetMessage(ProtoBattleField::Turn* msg);
	void SetMessage(ProtoBattleField::ReplyCity* msg);
	//选择战法战术
	void SetShape(HeroPropertyItemIndex index, unsigned form);
	bool Fight();
	bool _fight();
	//推送
	void SendMsg(bool over, bool attackerwin);
	//战斗回合
	void Turn();
	//检查队列
	bool CheckQueue();
	//返回空缺排数
	int NeedQueue(bool att);
	unsigned GetQueueSize(bool att);
	bool IsInQueue(HeroPropertyItemIndex index, bool att);
	//补充队列
	void AddQueue(bool att);

	//战法阶段
	void Skill(BattleDemoHero &att, BattleDemoQueue &queue, bool pve, vector<int> &res, int &explode);
	//寻找战法目标
	void SkillTarget(int &n, BattleDemoQueue &queue, vector<int> &m);

	//计算战法伤害
	void SkillDamage(BattleDemoHero &attacker, BattleDemoHero &defender, int n, int m, int &as, int &explode, bool first);
	//判断战法抵挡
	bool IsSkill(BattleDemoHero &attacker, BattleDemoHero &defender, bool pve);

	//战术阶段
	void Shape(BattleDemoHero &attacker, BattleDemoHero &defender);
	//判断战术相克
	bool IsShape(unsigned a, unsigned d);

	//平砍阶段
	void Attack(BattleDemoHero &attacker, BattleDemoHero &defender, bool pve);
	//计算平砍伤害
	void AttackDamage(BattleDemoHero &attacker, BattleDemoHero &defender, bool pve, double s, int &as);
};
typedef map<uint16_t, BattleDemo> WorldBattleMap;
typedef map<unsigned, BattleDemo> GateBattleMap;
typedef map<pair<HeroPropertyItemIndex, HeroPropertyItemIndex>, BattleDemo> RushBattleMap;
typedef map<unsigned, BattleDemo> LadderBattleMap;
/***************************************************/
class HeroMove
{
public:
	unsigned mts;//到达cids.begin的时间
	list<uint16_t> cids;

	HeroMove()
	{
		mts = 0;
	}
};
typedef map<HeroPropertyItemIndex, HeroMove> HeroMoveMap;
/***************************************************/
class CityHero
{
public:
	map<uint8_t, set<HeroPropertyItemIndex> > heros;
	list<HeroPropertyItemIndex> attacker, defender;
	unsigned countm, countn;

	CityHero()
	{
		countm = countn = 0;
	}

	bool Fighting() const
	{
		return !attacker.empty() || !defender.empty();
	}
	void SetMessage(ProtoBattleField::City* msg)
	{
		msg->set_fight(Fighting());
	}
};
typedef map<uint16_t, CityHero> CityHeroMap;
/***************************************************/
class WorldManager : public BattleSingleton, public CSingleton<WorldManager>
{
private:
	friend class CSingleton<WorldManager>;
	WorldManager():m_extra_t(600),m_extra_s_t(600),m_extra_c(5),m_extra_s_c(5){};
	virtual ~WorldManager(){}

	HeroMoveMap m_heroMoveMap;
	CityHeroMap m_cityHeroMap;
	map<unsigned, set<unsigned> > m_heroSend;
	BattleRewardMap m_rewardMap;
	set<uint16_t> m_citySend;
	WorldBattleMap m_worldBattleMap;
	GateBattleMap m_gateBattleMap;
	RushBattleMap m_rushBattleMap;
	LadderBattleMap m_ladderBattleMap;
	set<HeroPropertyItemIndex> m_fightOver;
	set<uint16_t> m_cityOver;
	map<unsigned, unsigned> m_gateOver;
	map<unsigned, pair<unsigned, unsigned> > m_fogOver;
	map<unsigned, unsigned> m_ladderOver;
	map<unsigned, pair<unsigned, unsigned> > m_kill_rank;  //杀敌排行榜，uid->pair<rank, exp>

	unsigned m_extra_t, m_extra_s_t, m_extra_c, m_extra_s_c;

	void processMove();
	void processFight();
	void processFightOver();
	void processCity();
	void processGate();
	void processLadder();
	void processShip();
	bool checkFight(HeroPropertyItem &hero);
	void createFight(uint16_t cid);
	void joinFight(HeroPropertyItemIndex index, uint16_t cid);

	void sendHeroState();
	void sendCityState();
	void sendMissionStat();

	bool checkMission(uint16_t cid);
	void startMission();
	void endMission();
	void onDay();

	int GetHistoryReward(unsigned uid, ProtoBattleField::ReplyHistoryReward* resp);

	void DefineWorldNPC();

public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();
	virtual void OnExit();
	virtual void OnTimer1();
	void OnHour();
	void OnMinute();
	uint16_t OnNPCAct(uint8_t kingdom, unsigned id);
	void CreateActNPC(unsigned type, unsigned count, uint16_t cid, uint8_t kingdom, unsigned id);
	void DelActNPC(unsigned type, uint16_t cid);

	void BattleLog();
	void BattleOver();

	void InsertHeroSend(HeroPropertyItemIndex index){ if(index.IsUser()) m_heroSend[index.uid].insert(index.id);}
	void InsertReward(unsigned uid, BattleReward& reward){m_rewardMap[uid].Append(reward);}
	void InsertCitySend(uint16_t cid){m_citySend.insert(cid);}
	void InsertHeroOver(HeroPropertyItemIndex index){m_fightOver.insert(index);}
	void InsertCityOver(uint16_t cid){m_cityOver.insert(cid);}
	void InsertGateOver(unsigned uid, unsigned gate){m_gateOver[uid] = gate;}
	void InsertFogOver(unsigned uid, unsigned gate, unsigned npc) {m_fogOver[uid] = make_pair(gate, npc);}
	void InsertShipOver(){/*todo*/}
	void InsertLadderOver(unsigned uid, unsigned rank){m_ladderOver[uid] = rank;}
	CityHero& GetCityHero(uint16_t cid){return m_cityHeroMap[cid];}

	void SetMessage(unsigned uid, ProtoBattleField::Field* msg);
	void SetMessage(unsigned uid, ProtoBattleField::ReplyRewardInfo* msg);
	bool IsHeroFighting(HeroPropertyItemIndex index);
	bool IsCityFighting(uint16_t cid);
	bool IsHeroMoving(HeroPropertyItemIndex index);
	bool IsCityHasMember(uint16_t cid, uint8_t kingdom);
	void NewAddHero(HeroPropertyItemIndex index, uint16_t c, uint8_t k){m_cityHeroMap[c].heros[k].insert(index);}
	bool TryRecoverHero(HeroPropertyItemIndex index);
	void CalcPower(HeroPropertyItemIndex index);

	uint8_t GetKingdom(HeroPropertyItemIndex index);
	void RemoveHeroFromCity(HeroPropertyItemIndex index, bool head);
	void RemoveNPCFromCity(uint16_t cid, uint8_t kingdom);

	int CreateGateFight(unsigned uid, unsigned gate, unsigned gid, vector<HeroPropertyItemIndex> &hi, vector<unsigned> &npc, double diff);
	int CreateLadderFight(unsigned uid, unsigned rank, vector<HeroPropertyItemIndex> &hi, vector<HeroPropertyItemIndex> &enemy, unsigned g = 0);

	int Process(unsigned uid, ProtoBattleField::RequestHero* msg, ProtoBattleField::HeroState* resp);
	int Process(unsigned uid, ProtoBattleField::RequestMove* msg, ProtoBattleField::ReplyMove* resp);
	int Process(unsigned uid, ProtoBattleField::RequestStop* msg);
	int Fly(HeroPropertyItemIndex index, uint16_t tid);
	int Process(unsigned uid, ProtoBattleField::RequestCityKingdom* msg, ProtoBattleField::ReplyCityKingdom* resp);
	int Process(unsigned uid, ProtoBattleField::RequestCityCount* msg, ProtoBattleField::ReplyCityCount* resp);
	int Process(unsigned uid, ProtoBattleField::RequestCity* msg, ProtoBattleField::ReplyCity* &resp);
	int Process(unsigned uid, ProtoBattleField::RequestGate* msg, ProtoBattleField::ReplyCity* &resp);
	int Process(unsigned uid, ProtoBattleField::RequestRush* msg, ProtoBattleField::ReplyCity* &resp);
	int Process(unsigned uid, ProtoBattleField::RequestLadder* msg, ProtoBattleField::ReplyCity* &resp);
	int Process(unsigned uid, ProtoBattleField::QuitCity* msg);
	int Process(unsigned uid, ProtoBattleField::QuitGate* msg);
	int Process(unsigned uid, ProtoBattleField::QuitRush* msg);
	int Process(unsigned uid, ProtoBattleField::QuitLadder* msg);
	int Process(unsigned uid, ProtoBattleField::RequestList* msg, ProtoBattleField::ReplyList* resp);
	int Process(unsigned uid, ProtoBattleField::SkillOrShapeCity* msg);
	int Process(unsigned uid, ProtoBattleField::SkillOrShapeGate* msg);
	int Process(unsigned uid, ProtoBattleField::SkillOrShapeRush* msg);
	int Process(unsigned uid, ProtoBattleField::SkillOrShapeLadder* msg);
	int Process(unsigned uid, ProtoBattleField::StartRush* msg);
	int Process(unsigned uid, ProtoBattleField::RequestVision* msg, ProtoBattleField::ReplyVision* resp);
	int Process(unsigned uid, ProtoBattleField::ImmediatelyCity* msg);
	int Process(unsigned uid, ProtoBattleField::ImmediatelyGate* msg);
	int Process(unsigned uid, ProtoBattleField::ImmediatelyRush* msg);
	int Process(unsigned uid, ProtoBattleField::ImmediatelyLadder* msg);
	int Process(unsigned uid, ProtoBattleField::RequestRewardInfo* msg, ProtoBattleField::ReplyRewardInfo* resp);
	//领取据点奖励
	int Process(unsigned uid, ProtoBattleField::RequestHistoryReward* msg, ProtoBattleField::ReplyHistoryReward* resp);
	int Process(unsigned uid, ProtoBattleField::RequestKillReward* msg, ProtoBattleField::ReplyKillReward* resp);

	//个人任务
	int Process(unsigned uid, ProtoBattleField::RequestMissionPersonalReward* msg, ProtoBattleField::ReplyMissionPersonalReward* resp);
	int Process(unsigned uid, ProtoBattleField::RequestMissionCountryReward* msg, ProtoBattleField::ReplyMissionCountryReward* resp);

	int Process(unsigned uid, ProtoBattleField::RequestAuto* msg);

	int Process(Bot::RequestMove* req);
	int Process(Bot::RequestCity* req);

	int Process(unsigned uid, ProtoBattleField::RequestBattleReward* msg, ProtoBattleField::ReplyBattleReward* resp);
	int Process(unsigned uid, ProtoBattleField::RequestCityMaster* msg, ProtoBattleField::ReplyCityMaster* resp);
	int Process(unsigned uid, ProtoBattleField::StartCityBattle* msg);
	int CityMasterWin(unsigned uid, uint16_t cid);
	int Process(unsigned uid, ProtoBattleField::RequestCityReward* msg, ProtoBattleField::ReplyCityReward* resp);

	int Process(unsigned uid, ProtoBattleField::RequestFight* msg, ProtoBattleField::ReplyFight* resp);

	void DoClear()
	{
		OnExit();
		m_heroMoveMap.clear();
		m_cityHeroMap.clear();
		m_heroSend.clear();
		m_rewardMap.clear();
		m_citySend.clear();
		m_worldBattleMap.clear();
		m_gateBattleMap.clear();
		m_rushBattleMap.clear();
		m_fightOver.clear();
		m_cityOver.clear();
		m_gateOver.clear();
		m_fogOver.clear();
		//todo: clear ship
		m_ladderBattleMap.clear();
		m_ladderOver.clear();
		OnInit();
	}

private:
	//产生本服排行榜文件
	int RefreshAllKillRank();
	int RefreshMap();

	//产生本国家的排行榜文件
	int RefreshKindomKillRank(vector<unsigned> & kindomuser, string filename);

	//发放杀敌排行榜的所有奖励
	int ProvideReward();

	//发放杀敌的经验奖励
	int ProvideExpRewardAndResetKill();

	//发放排名奖励-龙鳞
	int ProvideRankReward();

	//发送全部杀敌人员的通知
	int SendRankNotify();

private:
	const static string killrankpath;
	const static string killrankname;
	const static string mapname;
};

#endif /* WORLDMANAGER_H_ */
