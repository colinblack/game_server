/*
 * WorldManager.cpp
 *
 *  Created on: 2016-9-8
 *      Author: Ralf
 */

#include "WorldManager.h"

//#define BATTLE_DEBUG_LOG

const string WorldManager::killrankpath("../webroot/data/");
const string WorldManager::killrankname("killrank");
const string WorldManager::mapname("map");

void WorldManager::BattleLog()
{
	debug_log("---------------------------");
	const HeroPropertyMap& hm = HMI->GetMap();
	for(HeroPropertyMap::const_iterator it=hm.begin();it!=hm.end();++it)
	{
		uint8_t kingdom = GetKingdom(it->first);
		HeroPropertyItem& hero = SEQ_GET_HMI(it->second);
		debug_log("hero:%u-%u,city:%u,gate:%u,kingdom:%u,ouid:%u,oid:%u"
				,it->first.uid, it->first.id, hero.city, hero.gate, kingdom, hero.ouid, hero.oid);
	}
	debug_log("---------------------------");
	for(CityHeroMap::iterator it=m_cityHeroMap.begin();it!=m_cityHeroMap.end();++it)
	{
		debug_log("cid:%u,kingdom:%u,fighting:%u"
				,it->first, GET_BMI_CITY(it->first).kingdom, it->second.Fighting()?1:0);
	}
	debug_log("---------------------------");
	for(unsigned i=0;i<SG17_KINGDOM;++i)
	{
		debug_log("m1:%u,m1s:%u,m2:%u,m2s:%u"
				,GET_BMI->mission[i].m1,GET_BMI->mission[i].m1status,GET_BMI->mission[i].m2,GET_BMI->mission[i].m2status);
	}
	debug_log("---------------------------");
}
void WorldManager::BattleOver()
{
	for(WorldBattleMap::iterator it=m_worldBattleMap.begin();it!=m_worldBattleMap.end();++it)
		it->second.immediately = true;
	for(GateBattleMap::iterator it=m_gateBattleMap.begin();it!=m_gateBattleMap.end();++it)
		it->second.immediately = true;
	for(RushBattleMap::iterator it=m_rushBattleMap.begin();it!=m_rushBattleMap.end();++it)
		it->second.immediately = true;
	for(LadderBattleMap::iterator it=m_ladderBattleMap.begin();it!=m_ladderBattleMap.end();++it)
		it->second.immediately = true;
}

void WorldManager::DefineWorldNPC()
{
	unsigned d = LMI->GetOpenDays();
	if(d <= 3)
	{
		m_extra_t = 600;
		m_extra_s_t = 300;
		m_extra_c = 10;
		m_extra_s_c = 5;
	}
	else if(d <= 7)
	{
		m_extra_t = 600;
		m_extra_s_t = 600;
		m_extra_c = 8;
		m_extra_s_c = 10;
	}
	else
	{
		m_extra_t = 600;
		m_extra_s_t = 600;
		m_extra_c = 5;
		m_extra_s_c = 8;
	}
}
int WorldManager::OnInit() {
	DefineWorldNPC();

	for(unsigned i=0;i<BATTLE_FIELD_CITY;++i)
	{
		set<HeroPropertyItemIndex> t;
		for(unsigned j=1;j<=SG17_KINGDOM;++j)
			m_cityHeroMap[SEQ_GET_BMI_CITY(i).cid].heros[j] = t;
	}
	const HeroPropertyMap& hm = HMI->GetMap();
	vector<HeroPropertyItemIndex> rm;
	for(HeroPropertyMap::const_iterator it=hm.begin();it!=hm.end();++it)
	{
		if(it->first.isWorldActNpc() || it->first.isWorldNBNpc())
		{
			rm.push_back(it->first);
			continue;
		}
		uint8_t kingdom = GetKingdom(it->first);
		HeroPropertyItem& hero = SEQ_GET_HMI(it->second);
		if(hero.gate)
			hero.gate = 0;
		if(hero.IsDie())
			hero.city = BMI->getCapital(kingdom);
		m_cityHeroMap[hero.city].heros[kingdom].insert(it->first);
		if(hero.index.uid == e_normal_npc)
			++m_cityHeroMap[hero.city].countn;
	}
	for(vector<HeroPropertyItemIndex>::iterator it=rm.begin();it!=rm.end();++it)
		HMI->Del(*it);
	for(CityHeroMap::iterator it=m_cityHeroMap.begin();it!=m_cityHeroMap.end();++it)
	{
		uint8_t k = GET_BMI_CITY(it->first).kingdom;
		bool f = false;
		for(unsigned i=1;i<=SG17_KINGDOM;++i)
		{
			if(i != k && !it->second.heros[i].empty())
			{
				f = true;
				break;
			}
		}
		if(f)
			createFight(it->first);
	}

	unsigned nts = Time::GetGlobalTime();
	unsigned nh = LogicCommonUtil::GetHourByTime(nts);
	unsigned oh = LogicCommonUtil::GetHourByTime(GET_BMI->ts);

	//是否需要发放杀敌排行榜奖励
	bool isNeedReward = LogicCommonUtil::IsCrossTime(GET_BMI->ts, nts, KILL_RANK_REWARD);

	if(CTime::IsDiffDay(GET_BMI->ts, nts))
	{
		onDay();

		endMission();

		if(oh < BATTLE_CITY_REWARD_4 || nh >= BATTLE_CITY_REWARD_1)
			BMI->OnCityReward();

		GET_BMI->SyncHistory();
		//跨天，刷新排行榜
		RefreshAllKillRank();
		RefreshMap();
	}
	else
	{
		if((oh >= BATTLE_MISSION_1_S && oh < BATTLE_MISSION_1_E && nh >= BATTLE_MISSION_1_E)
		|| (oh >= BATTLE_MISSION_2_S && oh < BATTLE_MISSION_2_E && nh >= BATTLE_MISSION_2_E)
		|| (oh >= BATTLE_MISSION_3_S && oh < BATTLE_MISSION_3_E && nh >= BATTLE_MISSION_3_E))
			endMission();

		if((oh < BATTLE_CITY_REWARD_1 && nh >= BATTLE_CITY_REWARD_1)
		|| (oh < BATTLE_CITY_REWARD_2 && nh >= BATTLE_CITY_REWARD_2)
		|| (oh < BATTLE_CITY_REWARD_3 && nh >= BATTLE_CITY_REWARD_3)
		|| (oh < BATTLE_CITY_REWARD_4 && nh >= BATTLE_CITY_REWARD_4))
			BMI->OnCityReward();

		//判断是否跨小时
		if(nh != oh)
		{
			GET_BMI->SyncHistory();
			RefreshAllKillRank();  //刷新排行榜
			RefreshMap();
		}
	}

	if (isNeedReward)  //需要重新发放排行榜奖励
	{
		ProvideReward();
	}

	if((nh >= BATTLE_MISSION_1_S && nh < BATTLE_MISSION_1_E)
	|| (nh >= BATTLE_MISSION_2_S && nh < BATTLE_MISSION_2_E)
	|| (nh >= BATTLE_MISSION_3_S && nh < BATTLE_MISSION_3_E))
		startMission();

	//初始化偷袭珍珠港活动
	LogicAttackHarborManager::Instance()->AttackHarborInit();

	return 0;
}
void WorldManager::OnExit() {
	const HeroPropertyMap& hm = HMI->GetMap();
	for(HeroPropertyMap::const_iterator it=hm.begin();it!=hm.end();++it)
	{
		HeroPropertyItem& hero = SEQ_GET_HMI(it->second);
		if(hero.gate)
			hero.gate = 0;
		if(hero.IsDie())
			hero.city = BMI->getCapital(GetKingdom(it->first));
	}
}
void WorldManager::OnHour()
{
	GET_BMI->SyncHistory();
	unsigned hour = LogicCommonUtil::GetHourByTime(Time::GetGlobalTime());
	if(hour == BATTLE_MISSION_1_S || hour == BATTLE_MISSION_2_S || hour == BATTLE_MISSION_3_S)
		startMission();
	if(hour == BATTLE_MISSION_1_E || hour == BATTLE_MISSION_2_E || hour == BATTLE_MISSION_3_E)
		endMission();
	if(hour == BATTLE_CITY_REWARD_1 || hour == BATTLE_CITY_REWARD_2 || hour == BATTLE_CITY_REWARD_3 || hour == BATTLE_CITY_REWARD_4)
		BMI->OnCityReward();
	if(hour == 0)
		onDay();

	//每小时都刷新排行榜
	RefreshAllKillRank();
	RefreshMap();

	//22点发奖励
	if(hour == KILL_RANK_REWARD)
	{
		ProvideReward();
	}
}
void WorldManager::OnMinute()//npc创建不成功就return了，要加功能加前面
{
	unsigned ts = LMI->GetTimerTS();
	bool extra = (ts % m_extra_t == 0);
	bool extra_s = (ts % m_extra_s_t == 0);
	bool normal = (ts % DEMO_NPC.npc_m() == 0);
	bool nb = (LMI->GetOpenDays() >= 100 && ts % 3600 == 0);
	if(!extra && !extra_s && !normal && !nb)
		return;

	unsigned tc[SG17_KINGDOM+1], tr[SG17_KINGDOM+1];
	memset(tc, 0, sizeof(tc));
	memset(tr, 0xFFFF, sizeof(tr));
	vector<uint16_t> tn[SG17_KINGDOM+1];

	for(CityHeroMap::iterator it=m_cityHeroMap.begin();it!=m_cityHeroMap.end();++it)
	{
		if(BattleFieldManager::isCapital(it->first))
			continue;
		uint8_t ck = GET_BMI_CITY(it->first).kingdom;
		if(ck == 0)
			continue;

		if(extra || extra_s)
		{
			for(unsigned i=1;i<=SG17_KINGDOM;++i)
			{
				if(i == ck && !it->second.Fighting())
					continue;
				unsigned r = BMI->GetRange(i, it->first);
				if(r < tr[i])
				{
					tr[i] = r;
					tc[i] = it->first;
				}
			}
		}

		if(normal && it->second.countn < DEMO_NPC.npc_max())
		{
			HeroPropertyItemIndex ni = HMI->CreateWorldNPC(e_normal_npc, ck, it->first);
			//debug_log("npc uid:%u,id:%u,kingdom:%u,cid:%u", ni.uid, ni.id, ck, it->first);
			if(ni.empty())
				return;
			++it->second.countn;
			if(it->second.Fighting())
				joinFight(ni, it->first);
			else
				it->second.heros[ck].insert(ni);
		}

		if(nb)
		{
			unsigned r = BMI->GetRange(ck, it->first);
			if(r > 2)
				tn[ck].push_back(it->first);
		}
	}

	if(extra || extra_s)
	{
		ProtoBattleField::SendNPCMove *msg = new ProtoBattleField::SendNPCMove;
		for(unsigned i=1;i<=SG17_KINGDOM;++i)
		{
			if(tc[i])
			{
				const list<uint16_t>& cids = BMI->GetRoad(i, tc[i]);
				if(extra)
				{
					for(unsigned j=0;j<m_extra_c;++j)
					{
						HeroPropertyItemIndex ni = HMI->CreateWorldNPC(e_attack_npc, i, BattleFieldManager::getCapital(i));
						if(ni.empty())
							return;
						m_heroMoveMap[ni].mts = Time::GetGlobalTime() + BATTLE_FIELD_MOVE;
						m_heroMoveMap[ni].cids = cids;
					}
					ProtoBattleField::NPCMove *m = msg->add_move();
					m->set_id(e_attack_npc);
					for(list<uint16_t>::const_iterator it=cids.begin();it!=cids.end();++it)
						m->add_cids(*it);
				}
				if(extra_s && tr[i] <= BATTLE_RANGE_2)
				{
					for(unsigned j=0;j<m_extra_s_c;++j)
					{
						HeroPropertyItemIndex ni = HMI->CreateWorldNPC(e_defend_npc, i, BattleFieldManager::getCapital(i));
						if(ni.empty())
							return;
						m_heroMoveMap[ni].mts = Time::GetGlobalTime() + BATTLE_FIELD_MOVE;
						m_heroMoveMap[ni].cids = cids;
					}
					ProtoBattleField::NPCMove *m = msg->add_move();
					m->set_id(e_defend_npc);
					for(list<uint16_t>::const_iterator it=cids.begin();it!=cids.end();++it)
						m->add_cids(*it);
				}
			}
		}
		LMI->broadcastMsg(msg);
	}

	if(nb)
	{
		//todo : call func del e_nb_npc
		LogicEliteMilitaryManager::Instance()->DestroyNPC();

		for(unsigned i=1;i<=SG17_KINGDOM;++i)
		{
			random_shuffle(tn[i].begin(), tn[i].end());
			for(unsigned j=0;j<2;++j)
			{
				if(j >= tn[i].size())
					break;
				//todo : call func add e_nb_npc kingdom=i and city=tn[i][j]
				LogicEliteMilitaryManager::Instance()->RefreshEliteNPC(i, tn[i][j]);
			}
		}

		//刷新完毕后，发送推送协议
		LogicEliteMilitaryManager::Instance()->SendRefreshNPCMsg();
	}
}
void WorldManager::DelActNPC(unsigned type, uint16_t cid)
{
	if(m_cityHeroMap[cid].Fighting())
	{
		for(int i=0;i<2;++i)
		{
			list<HeroPropertyItemIndex> &queue = i?m_cityHeroMap[cid].attacker:m_cityHeroMap[cid].defender;
			unsigned s = m_worldBattleMap.count(cid)?m_worldBattleMap[cid].GetQueueSize(i):0;
			if(queue.size() <= s)
				continue;
			list<HeroPropertyItemIndex>::iterator it=queue.begin();
			for(int j=0;j<s;j++)
				++it;
			for(;it!=queue.end();)
			{
				if(it->uid == type)
				{
					m_cityHeroMap[cid].heros[GetKingdom(*it)].erase(*it);
					HMI->Del(*it);
					it = queue.erase(it);
				}
				else
					++it;
			}
		}
	}
	else
	{
		for(unsigned i=1;i<=SG17_KINGDOM;++i)
		{
			vector<HeroPropertyItemIndex> rm;
			for(set<HeroPropertyItemIndex>::iterator it=m_cityHeroMap[cid].heros[i].begin();it!=m_cityHeroMap[cid].heros[i].end();++it)
			{
				if(it->uid == type)
					rm.push_back(*it);
			}
			for(vector<HeroPropertyItemIndex>::iterator it=rm.begin();it!=rm.end();++it)
			{
				m_cityHeroMap[cid].heros[i].erase(*it);
				HMI->Del(*it);
			}
		}
	}
}
void WorldManager::CreateActNPC(unsigned type, unsigned count, uint16_t cid, uint8_t kingdom, unsigned id)
{
	uint8_t k = GET_BMI_CITY(cid).kingdom;
	const NPC::NPCInfo& npc = NPC_INFO(id);
	bool f = m_cityHeroMap[cid].Fighting();
	for(unsigned i=0;i<count;++i)
	{
		HeroPropertyItemIndex ni = HMI->CreateActNPC(type, kingdom, cid, id, npc.p_soldier(), npc.p_hp());
		if(ni.empty())
			break;

		m_cityHeroMap[cid].heros[kingdom].insert(ni);
		if(f)
		{
			if(k != kingdom)
				m_cityHeroMap[cid].attacker.push_back(ni);
			else
				m_cityHeroMap[cid].defender.push_back(ni);
		}
	}
	if(!f)
	{
		createFight(cid);
		InsertCitySend(cid);
	}
}
uint16_t WorldManager::OnNPCAct(uint8_t kingdom, unsigned id)
{
	vector<uint16_t> cids;
	for(CityHeroMap::iterator it=m_cityHeroMap.begin();it!=m_cityHeroMap.end();++it)
	{
		if(BattleFieldManager::isCapital(it->first))
			continue;
		if(GET_BMI_CITY(it->first).kingdom == kingdom && !it->second.heros[kingdom].empty())
			cids.push_back(it->first);
	}

	if(cids.empty())
		return 0;

	uint8_t ek = kingdom==SG17_KINGDOM ? 1 : (kingdom+1);
	uint16_t cid = cids[Math::GetRandomInt(cids.size())];

	CreateActNPC(e_act_npc, 200, cid, ek, id);

	return cid;
}
void WorldManager::OnTimer1() {
	//debug_log("%u",Time::GetGlobalTime());
	processMove();
	processFight();
	processCity();
	processFightOver();
	processGate();
	processLadder();
	processShip();
	sendHeroState();
	sendCityState();
}
void WorldManager::sendHeroState()
{
	if(m_heroSend.empty())
		return;
	for(map<unsigned, set<unsigned> >::iterator it=m_heroSend.begin();it!=m_heroSend.end();++it)
	{
		if(UMI->IsOnline(it->first))
		{
			unsigned s = GET_RMI(it->first).property[DemoOfflineProperty_soldier];
			ProtoBattleField::HeroState * msg = new ProtoBattleField::HeroState;
			for(set<unsigned>::iterator iter=it->second.begin();iter!=it->second.end();++iter)
				GET_HMI(HeroPropertyItemIndex(it->first, *iter)).SetMessage(msg->add_hero(), s);
			if(m_rewardMap.count(it->first))
				m_rewardMap[it->first].SetMessage(msg->mutable_reward(), false);
#ifdef BATTLE_DEBUG_LOG
			debug_log("to:%u,msg:[%s]",it->first,msg->ShortDebugString().c_str());
#endif
			LMI->sendMsg(it->first, msg);
		}
		m_rewardMap.erase(it->first);
	}
	for(BattleRewardMap::iterator it=m_rewardMap.begin();it!=m_rewardMap.end();++it)
	{
		if(UMI->IsOnline(it->first))
		{
			ProtoBattleField::HeroState * msg = new ProtoBattleField::HeroState;
			m_rewardMap[it->first].SetMessage(msg->mutable_reward(), false);
			LMI->sendMsg(it->first, msg);
		}
	}
	m_heroSend.clear();
	m_rewardMap.clear();
}
void WorldManager::sendCityState()
{
	if(m_citySend.empty())
		return;
	ProtoBattleField::CityState * msg = new ProtoBattleField::CityState;
	for(set<uint16_t>::iterator it=m_citySend.begin();it!=m_citySend.end();++it)
	{
		ProtoBattleField::City* c = msg->add_city();
		GET_BMI_CITY(*it).SetMessage(c);
		m_cityHeroMap[*it].SetMessage(c);
	}
#ifdef BATTLE_DEBUG_LOG
	debug_log("msg:[%s]",msg->ShortDebugString().c_str());
#endif
	LMI->broadcastMsg(msg);
	m_citySend.clear();
}
void WorldManager::sendMissionStat()
{
	ProtoBattleField::MissionState * msg = new ProtoBattleField::MissionState;
	GET_BMI->SetMessage(msg);
	LMI->broadcastMsg(msg);
}
bool WorldManager::IsHeroFighting(HeroPropertyItemIndex index)
{
	HeroPropertyItem &hero = GET_HMI(index);
	if(hero.gate || m_cityHeroMap[hero.city].Fighting())
		return true;
	return false;
}
bool WorldManager::IsCityFighting(uint16_t cid)
{
	if(m_cityHeroMap.count(cid))
		return m_cityHeroMap[cid].Fighting();
	return false;
}
bool WorldManager::IsHeroMoving(HeroPropertyItemIndex index)
{
	if(m_heroMoveMap.count(index))
		return true;
	return false;
}
bool WorldManager::IsCityHasMember(uint16_t cid, uint8_t kingdom)
{
	if(m_cityHeroMap.count(cid) && m_cityHeroMap[cid].heros.count(kingdom) && !m_cityHeroMap[cid].heros[kingdom].empty())
		return true;
	return false;
}
bool WorldManager::TryRecoverHero(HeroPropertyItemIndex index)
{
	if(index.IsUser())
	{
		OfflineResourceItem& rmi = GET_RMI(index.uid);
		HeroPropertyItem& hmi = GET_HMI(index);
		if(rmi.silk && hmi.IsNeedRecover(rmi.property[DemoOfflineProperty_soldier] + (hmi.extraid?1:0)))
		{
			hmi.FullSoldires(rmi.property[DemoOfflineProperty_soldier] + (hmi.extraid?1:0));
			--rmi.silk;
			return true;
		}
	}
	return false;
}
void WorldManager::CalcPower(HeroPropertyItemIndex index)
{
	if(!index.IsUser())
		return;

	OfflineResourceItem& rmi = GET_RMI(index.uid);
	HeroPropertyItem& hmi = GET_HMI(index);

	hmi.property[DemoHeroProperty_power] = (int)ceil(
		double(hmi.property[DemoHeroProperty_attack] + hmi.property[DemoHeroProperty_defend] + hmi.property[DemoHeroProperty_hp] + hmi.property[DemoHeroProperty_attack_extra] + hmi.property[DemoHeroProperty_attack_anti])
		* double(rmi.property[DemoOfflineProperty_soldier] + (hmi.extraid?1:0))
		* (double(hmi.property[DemoHeroProperty_int]) * double(0.01) + double(0.5))
		+ (
		double(hmi.property[DemoHeroProperty_attack] + hmi.property[DemoHeroProperty_skill_extra])
		* double(HERO_INFO(index.id).skillco())
		* double(HERO_INFO(index.id).skillrange())
		* (double(1) + double(rmi.property[DemoOfflineProperty_tech]?SCIENCE_ITEM(rmi.property[DemoOfflineProperty_tech]).val():0) / double(100))
		+ double(hmi.property[DemoHeroProperty_defend] + hmi.property[DemoHeroProperty_skill_anti])
		* double(rmi.property[DemoOfflineProperty_soldier] + (hmi.extraid?1:0))
		* (double(1) + double(rmi.property[DemoOfflineProperty_anti_tech]?SCIENCE_ITEM(rmi.property[DemoOfflineProperty_anti_tech]).val():0) / double(100))
		) * (double(hmi.property[DemoHeroProperty_str]) * double(0.01) + double(0.5))
		);
}
void WorldManager::processFight(){
	vector<uint16_t> cids;
	for(WorldBattleMap::iterator it=m_worldBattleMap.begin();it!=m_worldBattleMap.end();++it)
	{
		if(it->second.Fight())
			cids.push_back(it->first);
	}
	for(vector<uint16_t>::iterator it=cids.begin();it!=cids.end();++it)
		m_worldBattleMap.erase(*it);

	vector<unsigned> gates;
	for(GateBattleMap::iterator it=m_gateBattleMap.begin();it!=m_gateBattleMap.end();++it)
	{
		if(it->second.Fight())
			gates.push_back(it->first);
	}
	for(vector<unsigned>::iterator it=gates.begin();it!=gates.end();++it)
		m_gateBattleMap.erase(*it);

	vector<pair<HeroPropertyItemIndex, HeroPropertyItemIndex> > rushs;
	for(RushBattleMap::iterator it=m_rushBattleMap.begin();it!=m_rushBattleMap.end();++it)
	{
		if(it->second.Fight())
			rushs.push_back(it->first);
	}
	for(vector<pair<HeroPropertyItemIndex, HeroPropertyItemIndex> >::iterator it=rushs.begin();it!=rushs.end();++it)
		m_rushBattleMap.erase(*it);

	vector<unsigned> ladders;
	for(LadderBattleMap::iterator it=m_ladderBattleMap.begin();it!=m_ladderBattleMap.end();++it)
	{
		if(it->second.Fight())
			ladders.push_back(it->first);
	}
	for(vector<unsigned>::iterator it=ladders.begin();it!=ladders.end();++it)
		m_ladderBattleMap.erase(*it);

	//todo: ship
}
void WorldManager::processFightOver(){
	for(set<HeroPropertyItemIndex>::iterator it=m_fightOver.begin();it!=m_fightOver.end();++it)
	{
		GET_HMI(*it).gate = 0;
		TryRecoverHero(*it);
		HeroPropertyItem &hero = GET_HMI(*it);
		if(m_cityHeroMap[hero.city].Fighting())
			joinFight(hero.index, hero.city);
		else if(!checkFight(hero))
			m_cityHeroMap[hero.city].heros[GetKingdom(*it)].insert(*it);
		InsertHeroSend(*it);
	}
	m_fightOver.clear();
}
void WorldManager::processCity(){
	for(set<uint16_t>::iterator it=m_cityOver.begin();it!=m_cityOver.end();++it)
	{
		if(!m_cityHeroMap[*it].attacker.empty() && m_cityHeroMap[*it].defender.empty())
		{
			//todo: kingdom change
			/***********add occupy**************/
			list<HeroPropertyItemIndex>::iterator z = m_cityHeroMap[*it].attacker.begin();
			HeroPropertyItemIndex o = *z;
			uint8_t k = GetKingdom(o);
			if(o.IsUser() || o.isVision())
			{
				HeroPropertyItem &hero = GET_HMI(o);
				unsigned u = hero.index.IsUser()?hero.index.uid:hero.ouid;
				unsigned d = hero.index.IsUser()?hero.index.id:hero.oid;
				OfflineResourceItem& item = GET_RMI(u);
				++item.occupy;
				if(UMI->IsOnline(u))
				{
					try
					{
						DBCUserBaseWrap(u).AddExploitBox(item.SyncReward(BATTLE_OCCUPY_REWARD));
						DBCHeroWrap(u, d).AddOccupy();
					}
					catch(const std::exception& e)
					{
						(void)e;
					}
				}
				else
				{
					item.AddReward(BATTLE_OCCUPY_REWARD);
					item.AddHeroOccupy(d);
				}
			}
			/***********add foccupy**************/
			for(;z!=m_cityHeroMap[*it].attacker.end();++z)
			{
				if(z->IsUser() || z->isVision())
				{
					HeroPropertyItem &hero = GET_HMI(*z);
					unsigned u = hero.index.IsUser()?hero.index.uid:hero.ouid;
					OfflineResourceItem& item = GET_RMI(u);
					++item.foccupy;
					if(UMI->IsOnline(u))
					{
						try
						{
							DBCUserBaseWrap(u).AddExploitBox(item.SyncReward(BATTLE_F_OCCUPY_REWARD));
						}
						catch(const std::exception& e)
						{
							(void)e;
						}
					}
					else
						item.AddReward(BATTLE_F_OCCUPY_REWARD);
				}
				if(z->isWorldActNpc())
				{
					m_cityHeroMap[*it].heros[GetKingdom(*z)].erase(*z);
					HMI->Del(*z);
				}
			}
			m_cityHeroMap[*it].attacker.clear();
			/************************************/
			BMI->KingdomChange(*it, k);
			for(unsigned i=0;i<DEMO_NPC.npc_change();++i)
			{
				HeroPropertyItemIndex ni = HMI->CreateWorldNPC(e_normal_npc, k, *it);
				//debug_log("npc uid:%u,id:%u,kingdom:%u,cid:%u", ni.uid, ni.id, k, *it);
				if(ni.empty())
					break;
				++m_cityHeroMap[*it].countn;
				m_cityHeroMap[*it].heros[k].insert(ni);
			}
			bool f = false;
			for(unsigned i=1;i<=SG17_KINGDOM;++i)
			{
				if(i != k && !m_cityHeroMap[*it].heros[i].empty())
				{
					f = true;
					break;
				}
			}
			if(f)
				createFight(*it);
			/*************************************/
			if(checkMission(*it))
				sendMissionStat();
		}
		else if(m_cityHeroMap[*it].attacker.empty() && !m_cityHeroMap[*it].defender.empty())
			m_cityHeroMap[*it].defender.clear();
		else if(!m_cityHeroMap[*it].attacker.empty() && !m_cityHeroMap[*it].defender.empty())
		{
			m_cityHeroMap[*it].attacker.clear();
			m_cityHeroMap[*it].defender.clear();
			error_log("cid:%u, battle over queue error!", *it);
		}
		InsertCitySend(*it);
	}
	m_cityOver.clear();
}
void WorldManager::processGate(){
	for(map<unsigned, unsigned>::iterator it=m_gateOver.begin();it!=m_gateOver.end();++it)
	{
		//判断是否是机型试炼副本
		if (LogicModelTrialManager::Instance()->IsTrialGate(it->second))
		{
			LogicModelTrialManager::Instance()->EndTrialGate(it->first, it->second);
		}
		else
		{
			LogicNPCPassMgr::Instance()->PassSuccess(it->first, it->second);
		}
	}

	m_gateOver.clear();

	for(map<unsigned, pair<unsigned, unsigned> >::iterator it=m_fogOver.begin();it!=m_fogOver.end();++it)
		LogicFogGateManager::Instance()->EndFogGate(it->first, it->second.first, it->second.second);
	m_fogOver.clear();
}
void WorldManager::processLadder(){
	for(map<unsigned, unsigned>::iterator it=m_ladderOver.begin();it!=m_ladderOver.end();++it)
		LogicPkFieldMgr::Instance()->FinishPkSuccess(it->first, it->second);
	m_ladderOver.clear();
}
void WorldManager::processShip(){
	//todo: process ship over
}
void WorldManager::processMove()
{
	set<HeroPropertyItemIndex> remove;
	unsigned now = Time::GetGlobalTime();
	for(HeroMoveMap::iterator it=m_heroMoveMap.begin();it!=m_heroMoveMap.end();++it)
	{
		if(it->second.mts > now)
			continue;
		if(it->second.cids.empty())
		{
			remove.insert(it->first);
			continue;
		}

		HeroPropertyItem &hero = GET_HMI(it->first);
		hero.city = *(it->second.cids.begin());
		//debug_log("move hero uid=%u,id=%u,cid=%u", it->first.uid, it->first.id, hero.city);
		if(m_cityHeroMap[hero.city].Fighting())
		{
			remove.insert(it->first);
			joinFight(hero.index, hero.city);
		}
		else if(checkFight(hero))
			remove.insert(it->first);
		else
		{
			if(it->second.cids.size() <= 1)
			{
				m_cityHeroMap[hero.city].heros[GetKingdom(it->first)].insert(it->first);
				remove.insert(it->first);
			}
			else
			{
				it->second.cids.pop_front();
				it->second.mts += BATTLE_FIELD_MOVE;
			}
		}
	}
	for(set<HeroPropertyItemIndex>::iterator it=remove.begin();it!=remove.end();++it)
	{
		if(UMI->IsOnline(it->uid) && GET_BMI->HasMission())
		{
			uint8_t k = GetKingdom(*it);
			if(k <= SG17_KINGDOM && k)
			{
				uint16_t c = GET_HMI(*it).city;
				if(GET_BMI->mission[k-1].m1 == c)
				{
					unsigned index = BaseManager::Instance()->GetIndex(it->uid);
					DataBase &base = BaseManager::Instance()->m_data->data[index];
					if(base.mp1 == 0)
					{
						base.mp1 = 1;
						BaseManager::Instance()->m_data->MarkChange(index);
					}
				}
				else if(GET_BMI->mission[k-1].m2 == c)
				{
					unsigned index = BaseManager::Instance()->GetIndex(it->uid);
					DataBase &base = BaseManager::Instance()->m_data->data[index];
					if(base.mp2 == 0)
					{
						base.mp2 = 1;
						BaseManager::Instance()->m_data->MarkChange(index);
					}
				}
			}
		}
		m_heroMoveMap.erase(*it);
		//to send hero state
		InsertHeroSend(*it);
	}
}
void WorldManager::createFight(uint16_t cid)
{
	if(m_worldBattleMap.count(cid))
		return;

	uint8_t k = GET_BMI_CITY(cid).kingdom;
	for(unsigned i=1;i<=SG17_KINGDOM;++i)
	{
		if(i == k)
		{
			for(set<HeroPropertyItemIndex>::reverse_iterator it=m_cityHeroMap[cid].heros[i].rbegin();it!=m_cityHeroMap[cid].heros[i].rend();++it)
			{
				//debug_log("%u-%u", it->uid, it->id);
				m_cityHeroMap[cid].defender.push_back(*it);
			}
		}
		else
		{
			for(set<HeroPropertyItemIndex>::reverse_iterator it=m_cityHeroMap[cid].heros[i].rbegin();it!=m_cityHeroMap[cid].heros[i].rend();++it)
				m_cityHeroMap[cid].attacker.push_back(*it);
		}
	}
	m_worldBattleMap.insert(make_pair(cid, BattleDemo(cid)));
}
bool WorldManager::checkFight(HeroPropertyItem &hero)
{
	//check if cause fight
	uint8_t ck = GET_BMI_CITY(hero.city).kingdom;
	uint8_t kingdom = GetKingdom(hero.index);
	if(kingdom == ck)
		return false;

	InsertCitySend(hero.city);
	if(m_cityHeroMap[hero.city].heros[ck].empty())
	{
		//todo: kingdom change
		/***********add occupy**************/
		if(hero.index.IsUser() || hero.index.isVision())
		{
			unsigned u = hero.index.IsUser()?hero.index.uid:hero.ouid;
			unsigned d = hero.index.IsUser()?hero.index.id:hero.oid;
			OfflineResourceItem& item = GET_RMI(u);
			++item.occupy;
			if(UMI->IsOnline(u))
			{
				try
				{
					DBCUserBaseWrap(u).AddExploitBox(item.SyncReward(BATTLE_OCCUPY_REWARD));
					DBCHeroWrap(u, d).AddOccupy();
				}
				catch(const std::exception& e)
				{
					(void)e;
				}
			}
			else
			{
				item.AddReward(BATTLE_OCCUPY_REWARD);
				item.AddHeroOccupy(d);
			}
		}
		/*************************************/
		BMI->KingdomChange(hero.city, kingdom);
		for(unsigned i=0;i<DEMO_NPC.npc_change();++i)
		{
			HeroPropertyItemIndex ni = HMI->CreateWorldNPC(e_normal_npc, kingdom, hero.city);
			//debug_log("npc uid:%u,id:%u,kingdom:%u,cid:%u", ni.uid, ni.id, kingdom, hero.city);
			if(ni.empty())
				break;
			++m_cityHeroMap[hero.city].countn;
			m_cityHeroMap[hero.city].heros[kingdom].insert(ni);
		}
		/*************************************/
		if(checkMission(hero.city))
			sendMissionStat();
		//debug_log("city change uid=%u,id=%u,cid=%u,kingdom=%u", hero.index.uid, hero.index.id, hero.city, kingdom);
		return false;
	}
	else
	{
		m_cityHeroMap[hero.city].heros[kingdom].insert(hero.index);
		createFight(hero.city);
	}
	return true;
}
void WorldManager::joinFight(HeroPropertyItemIndex index, uint16_t cid)
{
	//join queue
	uint8_t kingdom = GetKingdom(index);
	m_cityHeroMap[cid].heros[kingdom].insert(index);
	if(kingdom != GET_BMI_CITY(cid).kingdom)
		m_cityHeroMap[cid].attacker.push_back(index);
	else
		m_cityHeroMap[cid].defender.push_back(index);
}

void WorldManager::SetMessage(unsigned uid, ProtoBattleField::Field* msg)
{
	HMI->SetMessage(uid, msg, GET_RMI(uid).property[DemoOfflineProperty_soldier]);
	GET_BMI->SetMessage(msg);
	for(unsigned i=0;i<BATTLE_FIELD_CITY;++i)
		m_cityHeroMap[msg->city(i).cid()].SetMessage(msg->mutable_city(i));
	OfflineResourceItem& item = GET_RMI(uid);
	item.SetMessage(msg->mutable_rmi());
	GET_BMI->SetMessage(msg->mutable_reward(), item.kingdom, uid);
	GET_BRMI(uid).SetMessage(msg->mutable_reward());
}
void WorldManager::SetMessage(unsigned uid, ProtoBattleField::ReplyRewardInfo* msg)
{
	GET_BMI->SetMessage(msg);
	GET_RMI(uid).SetMessage(msg);
	unsigned index = BaseManager::Instance()->GetIndex(uid);
	DataBase &base = BaseManager::Instance()->m_data->data[index];
	msg->set_rewardb(base.rewardb);
	msg->set_mp1(base.mp1);
	msg->set_mp2(base.mp2);
	msg->set_mk1(base.mk1);
	msg->set_mk2(base.mk2);
	msg->set_mp3(base.mp3);
}

uint8_t WorldManager::GetKingdom(HeroPropertyItemIndex index){
	if(index.IsUser())
		return GET_RMI(index.uid).kingdom;
	else if(index.isVision())
		return GET_RMI(GET_HMI(index).ouid).kingdom;
	else if(index.isWorld())
		return GET_HMI(index).ouid;
	return 0;
}
void WorldManager::RemoveHeroFromCity(HeroPropertyItemIndex index, bool head){
	uint16_t cid = GET_HMI(index).city;
	uint8_t kingdom = GetKingdom(index);
	if(m_cityHeroMap[cid].Fighting())
	{
		//bool flag = true;
		list<HeroPropertyItemIndex> &queue = kingdom != GET_BMI_CITY(cid).kingdom?m_cityHeroMap[cid].attacker:m_cityHeroMap[cid].defender;
		if(head)
		{
			for(list<HeroPropertyItemIndex>::iterator it=queue.begin();it!=queue.end();++it)
			{
				if(*it == index)
				{
					//debug_log("%u-%u", it->uid, it->id);
					queue.erase(it);
					//flag = false;
					break;
				}
			}
		}
		else
		{
			for(list<HeroPropertyItemIndex>::reverse_iterator it=queue.rbegin();it!=queue.rend();++it)
			{
				if(*it == index)
				{
					queue.erase((++it).base());
					//flag = false;
					break;
				}
			}
		}
		//if(flag) debug_log("fail:uid:%u,index:%u,kingdom:%u,cid:%u", index.uid, index.id, kingdom,cid);
	}
	m_cityHeroMap[cid].heros[kingdom].erase(index);
}
void WorldManager::RemoveNPCFromCity(uint16_t cid, uint8_t kingdom)
{
	if(m_cityHeroMap[cid].countn && GET_BMI_CITY(cid).kingdom == kingdom)
	{
		//debug_log("%u-%u", cid, m_cityHeroMap[cid].countn);
		--m_cityHeroMap[cid].countn;
	}
}
int WorldManager::CreateGateFight(unsigned uid, unsigned gate, unsigned gid, vector<HeroPropertyItemIndex> &hi, vector<unsigned> &npc, double diff){
	if(m_gateBattleMap.count(uid))
	{
		LMI->SetErrMsg("in_gate");
		return R_ERR_LOGIC;
	}
	if(hi.empty())
		return R_ERR_PARAM;
	for(vector<HeroPropertyItemIndex>::iterator it=hi.begin();it!=hi.end();++it)
	{
		if(!HMI->HasHero(*it))
		{
			LMI->SetErrMsg("no_hero");
			return R_ERR_LOGIC;
		}
		if(m_heroMoveMap.count(*it))
		{
			LMI->SetErrMsg("hero_moving");
			return R_ERR_LOGIC;
		}
		HeroPropertyItem &hero = GET_HMI(*it);
		if(hero.gate || m_cityHeroMap[hero.city].Fighting())
		{
			LMI->SetErrMsg("hero_fighting");
			return R_ERR_LOGIC;
		}
		if(hero.IsDie())
		{
			LMI->SetErrMsg("hero_die");
			return R_ERR_LOGIC;
		}
	}
	for(vector<HeroPropertyItemIndex>::iterator it=hi.begin();it!=hi.end();++it)
	{
		HeroPropertyItem &hero = GET_HMI(*it);
		hero.gate = gate;
		m_cityHeroMap[hero.city].heros[GetKingdom(*it)].erase(*it);
	}

	m_gateBattleMap.insert(make_pair(uid, BattleDemo(uid, gate, gid, hi, npc, diff)));
	return 0;
}
int WorldManager::CreateLadderFight(unsigned uid, unsigned rank,  vector<HeroPropertyItemIndex> &hi,  vector<HeroPropertyItemIndex> &enemy, unsigned g){
	if(m_ladderBattleMap.count(uid))
	{
		LMI->SetErrMsg("in_ladder");
		return R_ERR_LOGIC;
	}
	if(hi.empty())
		return R_ERR_PARAM;
	for(vector<HeroPropertyItemIndex>::iterator it=hi.begin();it!=hi.end();++it)
	{
		if(!HMI->HasHero(*it))
		{
			LMI->SetErrMsg("no_hero");
			return R_ERR_LOGIC;
		}
		if(m_heroMoveMap.count(*it))
		{
			LMI->SetErrMsg("hero_moving");
			return R_ERR_LOGIC;
		}
		HeroPropertyItem &hero = GET_HMI(*it);
		if(hero.gate || m_cityHeroMap[hero.city].Fighting())
		{
			LMI->SetErrMsg("hero_fighting");
			return R_ERR_LOGIC;
		}
		if(hero.IsDie())
		{
			LMI->SetErrMsg("hero_die");
			return R_ERR_LOGIC;
		}
	}
	for(vector<HeroPropertyItemIndex>::iterator it=hi.begin();it!=hi.end();++it)
	{
		HeroPropertyItem &hero = GET_HMI(*it);
		hero.gate = e_gt_ladder;
		m_cityHeroMap[hero.city].heros[GetKingdom(*it)].erase(*it);
	}

	m_ladderBattleMap.insert(make_pair(uid, BattleDemo(uid, rank, hi, enemy, g)));
	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::RequestHero* msg, ProtoBattleField::HeroState* resp)
{
	unsigned s = GET_RMI(uid).property[DemoOfflineProperty_soldier];
	set<HeroPropertyItemIndex> h;
	HMI->GetHeros(uid, h);
	for(set<HeroPropertyItemIndex>::iterator it=h.begin();it!=h.end();++it)
		GET_HMI(*it).SetMessage(resp->add_hero(), s);
	return 0;
}
int WorldManager::Fly(HeroPropertyItemIndex index, uint16_t tid)
{
	if(GET_RMI(index.uid).forbid_move_ts > Time::GetGlobalTime())
	{
		LMI->SetErrMsg("forbid_move");
		return R_ERR_LOGIC;
	}
	if(m_heroMoveMap.count(index))
	{
		LMI->SetErrMsg("hero_moving");
		return R_ERR_LOGIC;
	}
	if(!HMI->HasHero(index))
	{
		LMI->SetErrMsg("no_hero");
		return R_ERR_LOGIC;
	}
	HeroPropertyItem& hero = GET_HMI(index);
	if(hero.IsDie())
	{
		LMI->SetErrMsg("hero_die");
		return R_ERR_LOGIC;
	}
	if(hero.gate)
	{
		LMI->SetErrMsg("in_gate");
		return R_ERR_LOGIC;
	}
	uint8_t kingdom = GetKingdom(index);
	if(BattleFieldManager::isCapital(tid) && kingdom != tid / BATTLE_FIELD_CITY_KINGDOM_SEQ)
	{
		LMI->SetErrMsg("no_road");
		return R_ERR_LOGIC;
	}
	if(m_cityHeroMap[hero.city].Fighting())
	{
		LMI->SetErrMsg("fighting_can_not_move");
		return R_ERR_LOGIC;
	}

	m_cityHeroMap[hero.city].heros[kingdom].erase(index);

	m_heroMoveMap[index].mts = 0;
	m_heroMoveMap[index].cids.push_back(tid);

	OfflineResourceItem& item = GET_RMI(index.uid);
	if(UMI->IsOnline(index.uid))
	{
		try
		{
			DBCUserBaseWrap(index.uid).AddExploitBox(item.SyncReward(BATTLE_FLY_REWARD));
		}
		catch(const std::exception& e)
		{
			(void)e;
		}
	}
	else
		item.AddReward(BATTLE_FLY_REWARD);

	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::RequestMove* msg, ProtoBattleField::ReplyMove* resp)
{
	if(GET_RMI(uid).forbid_move_ts > Time::GetGlobalTime())
	{
		LMI->SetErrMsg("forbid_move");
		return R_ERR_LOGIC;
	}
	uint16_t tid = msg->cids(0);
	if(msg->cids_size() == 0)
	{
		LMI->SetErrMsg("no_road");
		return R_ERR_LOGIC;
	}
	HeroPropertyItemIndex index(uid, msg->id());
	if(m_heroMoveMap.count(index))
	{
		LMI->SetErrMsg("hero_moving");
		return R_ERR_LOGIC;
	}
	if(!HMI->HasHero(index))
	{
		LMI->SetErrMsg("no_hero");
		return R_ERR_LOGIC;
	}
	HeroPropertyItem& hero = GET_HMI(index);
	if(hero.IsDie())
	{
		LMI->SetErrMsg("hero_die");
		return R_ERR_LOGIC;
	}
	if(hero.gate)
	{
		LMI->SetErrMsg("in_gate");
		return R_ERR_LOGIC;
	}
	uint8_t kingdom = GetKingdom(index);
	for(unsigned i=0;i<msg->cids_size()-1;++i)
	{
		uint16_t cid = msg->cids(i);
		if(BattleFieldManager::isCapital(cid) && kingdom != cid / BATTLE_FIELD_CITY_KINGDOM_SEQ)
		{
			LMI->SetErrMsg("no_road");
			return R_ERR_LOGIC;
		}
		if(!BMI->hasRoad(cid, msg->cids(i+1)))
		{
			LMI->SetErrMsg("no_road");
			return R_ERR_LOGIC;
		}
	}
	uint16_t lcid = msg->cids(msg->cids_size()-1);
	if(BattleFieldManager::isCapital(lcid) && kingdom != lcid / BATTLE_FIELD_CITY_KINGDOM_SEQ)
	{
		LMI->SetErrMsg("no_road");
		return R_ERR_LOGIC;
	}

	uint16_t cid = hero.city;
	if(!BMI->hasRoad(cid, tid))
	{
		LMI->SetErrMsg("no_road");
		return R_ERR_LOGIC;
	}
	uint8_t ck = GET_BMI_CITY(cid).kingdom;
	uint8_t tk = GET_BMI_CITY(tid).kingdom;
	if(m_cityHeroMap[cid].Fighting())
	{
		bool bt = kingdom != tk || m_cityHeroMap[tid].Fighting();
		list<HeroPropertyItemIndex> &queue = kingdom != ck?m_cityHeroMap[cid].attacker:m_cityHeroMap[cid].defender;
		if(bt)
		{
			list<HeroPropertyItemIndex> &eq = kingdom != ck?m_cityHeroMap[cid].defender:m_cityHeroMap[cid].attacker;
			if(queue.size()/3 < eq.size())
			{
				LMI->SetErrMsg("fighting_can_not_move");
				return R_ERR_LOGIC;
			}
		}

		if(m_worldBattleMap.count(cid) && m_worldBattleMap[cid].IsInQueue(index, kingdom != ck))
		{
			LMI->SetErrMsg("front_can_not_move");
			return R_ERR_LOGIC;
		}

		//todo 接入突进或撤退成就
		if(bt)
		{
		    LogicAchievementManager::AchievementParam achievementparam;
			achievementparam.type = achievement_type_march;

			LogicAchievementManager::Instance()->VerifyAchievementComplete(uid, achievementparam);
		}
		else  //撤退
		{
		    LogicAchievementManager::AchievementParam achievementparam;
			achievementparam.type = achievement_type_retreat;

			LogicAchievementManager::Instance()->VerifyAchievementComplete(uid, achievementparam);
		}
	}
	else if(kingdom != ck && kingdom != tk)
	{
		LMI->SetErrMsg("fighting_can_not_move");
		return R_ERR_LOGIC;
	}
	RemoveHeroFromCity(index, false);

	m_heroMoveMap[index].mts = Time::GetGlobalTime() + BATTLE_FIELD_MOVE;
	for(unsigned i=0;i<msg->cids_size();++i)
		m_heroMoveMap[index].cids.push_back(msg->cids(i));

	resp->set_id(index.id);
	resp->set_ts(Time::GetGlobalTime());
	resp->set_mts(Time::GetGlobalTime()+msg->cids_size()*BATTLE_FIELD_MOVE);

#ifdef BATTLE_DEBUG_LOG
	debug_log("to:%u,msg:[%s]",uid,resp->ShortDebugString().c_str());
#endif
	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::RequestStop* msg)
{
	HeroPropertyItemIndex index(uid, msg->id());
	if(!m_heroMoveMap.count(index))
	{
		LMI->SetErrMsg("not_moving");
		return R_ERR_LOGIC;
	}
	if(!m_heroMoveMap[index].cids.empty())
	{
		uint16_t cid = *(m_heroMoveMap[index].cids.begin());
		m_heroMoveMap[index].cids.clear();
		m_heroMoveMap[index].cids.push_back(cid);
	}
	return 0;
}

int WorldManager::Process(unsigned uid, ProtoBattleField::RequestCityKingdom* msg, ProtoBattleField::ReplyCityKingdom* resp)
{
	for(unsigned i=0;i<msg->cid_size();++i)
	{
		uint16_t cid = msg->cid(i);
		if(!m_cityHeroMap.count(cid))
			return R_ERR_PARAM;
		resp->add_cid(cid);
		resp->add_kingdom(GET_BMI_CITY(cid).kingdom);
		resp->add_fight(m_cityHeroMap[cid].Fighting());
	}
	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::RequestCityCount* msg, ProtoBattleField::ReplyCityCount* resp)
{
	uint16_t cid = msg->cid();
	if(!m_cityHeroMap.count(cid))
		return R_ERR_PARAM;
	for(unsigned i=1;i<=SG17_KINGDOM;++i)
		resp->add_count(m_cityHeroMap[cid].heros[i].size());
	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::RequestCity* msg, ProtoBattleField::ReplyCity* &resp)
{
	uint16_t cid = msg->cid();
	if(!m_worldBattleMap.count(cid))
		return R_ERR_PARAM;
	//insert watch;
#ifdef BATTLE_DEBUG_LOG
	debug_log("city insert:%u", uid);
#endif
	m_worldBattleMap[cid].watcher.insert(uid);
	//set fight info
	resp = &(m_worldBattleMap[cid].m_msg);
	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::RequestGate* msg, ProtoBattleField::ReplyCity* &resp)
{
	unsigned u = msg->uid();
	if(!m_gateBattleMap.count(u))
		return R_ERR_PARAM;
	//insert watch;
#ifdef BATTLE_DEBUG_LOG
	debug_log("gate insert:%u", uid);
#endif
	m_gateBattleMap[u].watcher.insert(uid);
	//set fight info
	resp = &(m_gateBattleMap[u].m_msg);
	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::RequestRush* msg, ProtoBattleField::ReplyCity* &resp)
{
	unsigned u = msg->uid();
	unsigned id = msg->id();
	unsigned euid = msg->euid();
	unsigned eid = msg->eid();
	pair<HeroPropertyItemIndex, HeroPropertyItemIndex> k = make_pair(HeroPropertyItemIndex(u, id),  HeroPropertyItemIndex(euid, eid));
	if(!m_rushBattleMap.count(k))
		return R_ERR_PARAM;
	//insert watch;
#ifdef BATTLE_DEBUG_LOG
	debug_log("rush insert:%u", uid);
#endif
	m_rushBattleMap[k].watcher.insert(uid);
	//set fight info
	resp = &(m_rushBattleMap[k].m_msg);
	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::RequestLadder* msg, ProtoBattleField::ReplyCity* &resp)
{
	unsigned u = msg->uid();
	if(!m_ladderBattleMap.count(u))
		return R_ERR_PARAM;
	//insert watch;
#ifdef BATTLE_DEBUG_LOG
	debug_log("ladder insert:%u", uid);
#endif
	m_ladderBattleMap[u].watcher.insert(uid);
	//set fight info
	resp = &(m_ladderBattleMap[u].m_msg);
	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::QuitCity* msg)
{
	//remove watch;
	uint16_t cid = msg->cid();
	if(m_worldBattleMap.count(cid))
	{
#ifdef BATTLE_DEBUG_LOG
		debug_log("city erase:%u", uid);
#endif
		m_worldBattleMap[cid].watcher.erase(uid);
	}
	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::QuitGate* msg)
{
	//remove watch;
	unsigned u = msg->uid();
	if(m_gateBattleMap.count(u))
	{
#ifdef BATTLE_DEBUG_LOG
		debug_log("gate erase:%u", uid);
#endif
		m_gateBattleMap[u].watcher.erase(uid);
	}
	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::QuitRush* msg)
{
	//remove watch;
	unsigned u = msg->uid();
	unsigned id = msg->id();
	unsigned euid = msg->euid();
	unsigned eid = msg->eid();
	pair<HeroPropertyItemIndex, HeroPropertyItemIndex> k = make_pair(HeroPropertyItemIndex(u, id),  HeroPropertyItemIndex(euid, eid));
	if(m_rushBattleMap.count(k))
	{
#ifdef BATTLE_DEBUG_LOG
		debug_log("rush erase:%u", uid);
#endif
		m_rushBattleMap[k].watcher.erase(uid);
	}
	return 0;
}

int WorldManager::Process(unsigned uid, ProtoBattleField::QuitLadder* msg)
{
	//remove watch;
	unsigned u = msg->uid();
	if(m_ladderBattleMap.count(u))
	{
#ifdef BATTLE_DEBUG_LOG
		debug_log("ladder erase:%u", uid);
#endif
		m_ladderBattleMap[u].watcher.erase(uid);
	}
	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::RequestList* msg, ProtoBattleField::ReplyList* resp)
{
	uint16_t cid = msg->cid();
	bool att = msg->attack();
	unsigned page = msg->page();
	if(!m_cityHeroMap.count(cid) || page == 0)
		return R_ERR_PARAM;
	list<HeroPropertyItemIndex> &queue = att?m_cityHeroMap[cid].attacker:m_cityHeroMap[cid].defender;
	if(queue.size() < (page-1)*DEMO_SHOW_PAGE)
		return R_ERR_PARAM;
	list<HeroPropertyItemIndex>::iterator it=queue.begin();
	set<unsigned> uids;
	for(unsigned i=0;i<(page-1)*DEMO_SHOW_PAGE;++i)
		++it;
	for(unsigned i=0;i<DEMO_SHOW_PAGE;++i)
	{
		if(it == queue.end())
			break;
		uids.insert(GET_HMI(*it).SetMessage(resp->add_queue()));
		++it;
	}
	for(set<unsigned>::iterator iter=uids.begin();iter!=uids.end();++iter)
	{
		if(IsValidUid(*iter))
			GET_RMI(*iter).SetMessage(resp->add_info(), false);
	}
	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::SkillOrShapeCity* msg)
{
	uint16_t cid = msg->cid();
	if(m_worldBattleMap.count(cid))
	{
		unsigned hid = msg->hid();
		unsigned shape = msg->shape();
		HeroPropertyItemIndex index(uid, hid);
		m_worldBattleMap[cid].SetShape(index, shape);
	}
	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::SkillOrShapeGate* msg)
{
	unsigned u = msg->uid();
	if(m_gateBattleMap.count(u))
	{
		unsigned hid = msg->hid();
		unsigned shape = msg->shape();
		HeroPropertyItemIndex index(uid, hid);
		m_gateBattleMap[u].SetShape(index, shape);
	}
	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::SkillOrShapeRush* msg)
{
	unsigned u = msg->uid();
	unsigned id = msg->id();
	unsigned euid = msg->euid();
	unsigned eid = msg->eid();
	pair<HeroPropertyItemIndex, HeroPropertyItemIndex> k = make_pair(HeroPropertyItemIndex(u, id),  HeroPropertyItemIndex(euid, eid));
	if(m_rushBattleMap.count(k))
	{
		unsigned hid = msg->hid();
		unsigned shape = msg->shape();
		HeroPropertyItemIndex index(uid, hid);
		m_rushBattleMap[k].SetShape(index, shape);
	}
	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::SkillOrShapeLadder* msg)
{
	unsigned u = msg->uid();
	if(m_ladderBattleMap.count(u))
	{
		unsigned hid = msg->hid();
		unsigned shape = msg->shape();
		HeroPropertyItemIndex index(uid, hid);
		m_ladderBattleMap[u].SetShape(index, shape);
	}
	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::StartRush* msg)
{
    HeroPropertyItemIndex index(uid, msg->id());
	if(m_heroMoveMap.count(index))
	{
		LMI->SetErrMsg("hero_moving");
		return R_ERR_LOGIC;
	}
    if(!HMI->HasHero(index))
    {
        LMI->SetErrMsg("no_hero");
        return R_ERR_LOGIC;
    }
    HeroPropertyItem& hero = GET_HMI(index);
    if(hero.IsDie())
    {
        LMI->SetErrMsg("hero_die");
        return R_ERR_LOGIC;
    }
    if(hero.gate)
    {
        LMI->SetErrMsg("in_gate");
        return R_ERR_LOGIC;
    }
	uint16_t cid = msg->cid();
	if(hero.city != cid)
    {
        LMI->SetErrMsg("not_in_cid");
        return R_ERR_LOGIC;
    }
	if(!m_cityHeroMap[cid].Fighting())
    {
        LMI->SetErrMsg("not_fighting");
        return R_ERR_LOGIC;
    }
	uint8_t kingdom = GetKingdom(index);
	uint8_t ck = GET_BMI_CITY(cid).kingdom;
    list<HeroPropertyItemIndex> &eq = kingdom != ck?m_cityHeroMap[cid].defender:m_cityHeroMap[cid].attacker;
    if(m_worldBattleMap.count(cid) && eq.size() <= m_worldBattleMap[cid].GetQueueSize(kingdom == ck))
    {
        LMI->SetErrMsg("enemy_not_enough");
        return R_ERR_LOGIC;
    }
    if(m_worldBattleMap.count(cid) && m_worldBattleMap[cid].IsInQueue(index, kingdom != ck))
    {
        LMI->SetErrMsg("front_can_not_rush");
        return R_ERR_LOGIC;
    }
	try
	{
		DBCUserBaseWrap(uid).CostUserResource(1000, 0, 0, 0, "StartRush");
	}
	catch(const std::exception& e)
	{
		LMI->SetErrMsg(e.what());
		return R_ERR_LOGIC;
	}

    HeroPropertyItemIndex ei = *eq.rbegin();
    RemoveHeroFromCity(index, false);
    RemoveHeroFromCity(ei, false);
    GET_HMI(index).gate = e_gt_rush;
    GET_HMI(ei).gate = e_gt_rush;

    m_rushBattleMap.insert(make_pair(make_pair(index, ei), BattleDemo(cid, index, ei)));

    if(ei.IsUser() && UMI->IsOnline(ei.uid))
    {
    	ProtoBattleField::SendRush* m = new ProtoBattleField::SendRush;
    	m->set_uid(index.uid);
    	m->set_id(index.id);
    	m->set_euid(ei.uid);
    	m->set_eid(ei.id);
    	LMI->sendMsg(ei.uid, m);
    }

	OfflineResourceItem& item = GET_RMI(uid);
	++item.rush;
	if(UMI->IsOnline(uid))
	{
		try
		{
			DBCUserBaseWrap(uid).AddExploitBox(item.SyncReward(BATTLE_RUSH_REWARD));
		}
		catch(const std::exception& e)
		{
			(void)e;
		}
	}
	else
		item.AddReward(BATTLE_RUSH_REWARD);

	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::RequestVision* msg, ProtoBattleField::ReplyVision* resp)
{
	if(HMI->GetFreeIndex() == -1)
	{
		LMI->SetErrMsg("vision_full");
		return R_ERR_LOGIC;
	}
    HeroPropertyItemIndex index(uid, msg->id());
	if(m_heroMoveMap.count(index))
	{
		LMI->SetErrMsg("hero_moving");
		return R_ERR_LOGIC;
	}
    if(!HMI->HasHero(index))
    {
        LMI->SetErrMsg("no_hero");
        return R_ERR_LOGIC;
    }
    HeroPropertyItem& hero = GET_HMI(index);
    if(hero.IsDie())
    {
        LMI->SetErrMsg("hero_die");
        return R_ERR_LOGIC;
    }
    if(hero.gate)
    {
        LMI->SetErrMsg("in_gate");
        return R_ERR_LOGIC;
    }
	uint16_t cid = msg->cid();
	if(hero.city != cid)
    {
        LMI->SetErrMsg("not_in_cid");
        return R_ERR_LOGIC;
    }
	try
	{
		if(msg->has_equd())
		{
			unsigned c;
			LogicEquipmentManager::Instance()->UseEquipment(uid, 80009, msg->equd(), 1, "RequestVision", c);
		}
		else
		{
			DBCUserBaseWrap(uid).CostCash(20, "RequestVision");
		}
	}
	catch(const std::exception& e)
	{
		LMI->SetErrMsg(e.what());
		return R_ERR_LOGIC;
	}

	HeroPropertyItemIndex vi = HMI->CreateVision(index);
	if(m_cityHeroMap[cid].Fighting())
		joinFight(vi, cid);
	else
		m_cityHeroMap[cid].heros[GetKingdom(vi)].insert(vi);

	resp->set_id(vi.id);

	OfflineResourceItem& item = GET_RMI(uid);
	if(UMI->IsOnline(uid))
	{
		try
		{
			DBCUserBaseWrap(uid).AddExploitBox(item.SyncReward(BATTLE_VISION_REWARD));
		}
		catch(const std::exception& e)
		{
			(void)e;
		}
	}
	else
		item.AddReward(BATTLE_VISION_REWARD);

	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::ImmediatelyCity* msg)
{
	uint16_t cid = msg->cid();
	if(m_worldBattleMap.count(cid) && m_worldBattleMap[cid].immediately == false)
	{
		try
		{
			DBCUserBaseWrap(uid).CostCash(1000000, "ImmediatelyCity");
		}
		catch(const std::exception& e)
		{
			LMI->SetErrMsg(e.what());
			return R_ERR_LOGIC;
		}
		m_worldBattleMap[cid].immediately = true;
	}
	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::ImmediatelyGate* msg)
{
	unsigned u = msg->uid();
	if(m_gateBattleMap.count(u) && m_gateBattleMap[u].immediately == false)
	{
		try
		{
			DBCUserBaseWrap(uid).CostCash(5, "ImmediatelyGate");
		}
		catch(const std::exception& e)
		{
			LMI->SetErrMsg(e.what());
			return R_ERR_LOGIC;
		}
		m_gateBattleMap[u].immediately = true;
	}
	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::ImmediatelyRush* msg)
{
	unsigned u = msg->uid();
	unsigned id = msg->id();
	unsigned euid = msg->euid();
	unsigned eid = msg->eid();
	pair<HeroPropertyItemIndex, HeroPropertyItemIndex> k = make_pair(HeroPropertyItemIndex(u, id),  HeroPropertyItemIndex(euid, eid));
	if(m_rushBattleMap.count(k) && m_rushBattleMap[k].immediately == false)
	{
		try
		{
			DBCUserBaseWrap(uid).CostCash(1000000, "ImmediatelyRush");
		}
		catch(const std::exception& e)
		{
			LMI->SetErrMsg(e.what());
			return R_ERR_LOGIC;
		}
		m_rushBattleMap[k].immediately = true;
	}
	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::ImmediatelyLadder* msg)
{
	unsigned u = msg->uid();
	if(m_ladderBattleMap.count(u) && m_ladderBattleMap[u].immediately == false)
	{
		try
		{
			DBCUserBaseWrap(uid).CostCash(5, "ImmediatelyLadder");
		}
		catch(const std::exception& e)
		{
			LMI->SetErrMsg(e.what());
			return R_ERR_LOGIC;
		}
		m_ladderBattleMap[u].immediately = true;
	}
	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::RequestRewardInfo* msg, ProtoBattleField::ReplyRewardInfo* resp)
{
	SetMessage(uid, resp);

	//接入争霸杀敌任务
	LogicMissionManager::MissionParam missionparam;
	missionparam.type = mission_type_hegemony_kill;
	LogicMissionManager::Instance()->VerifyMissionComplete(uid, missionparam);

	//接入争霸功勋任务
	missionparam.type = mission_type_hegemony_feats;
	LogicMissionManager::Instance()->VerifyMissionComplete(uid, missionparam);

	return 0;
}

int WorldManager::Process(unsigned uid, ProtoBattleField::RequestHistoryReward* msg, ProtoBattleField::ReplyHistoryReward* resp)
{
	//领取据点奖励
	GetHistoryReward(uid, resp);

	return 0;
}

int WorldManager::GetHistoryReward(unsigned uid, ProtoBattleField::ReplyHistoryReward* resp)
{
	DBCUserBaseWrap dbcuser(uid);
	unsigned now = Time::GetGlobalTime();

	unsigned hournow = LogicCommonUtil::GetHourTime(now);  //获取当前时间的整点形式

	BattleField * battlefield = BattleFieldManager::Instance()->m_data;

	if (0 == dbcuser.Obj().rests)
	{
		int subhour = 0;

		//获取第一份包含奖励的数组下标
		for(int i = 23; i >= 0; --i)
		{
			bool isHaveData = false;

			for(int j = 0; j < BATTLE_FIELD_CITY; ++j)
			{
				if (battlefield->history[i][j] != 0)  //据点所属国非空
				{
					isHaveData = true;
					break;
				}
			}

			if (isHaveData)
			{
				subhour = i + 1;
				break;
			}
		}

		unsigned subtime = subhour*3600;  //x小时前

		if (hournow < subtime)
		{
			error_log("time error. uid=%u", uid);
			throw std::runtime_error("time_error");
		}

		dbcuser.Obj().rests = hournow - subtime;
	}

	if (hournow <= dbcuser.Obj().rests)  //当前时间的整点，小于等于上次领取的整点时间
	{
		error_log("[RequestHistoryReward] time is not ready. now=%u,lastreward=%u", hournow, dbcuser.Obj().rests);
		throw std::runtime_error("time_not_ready");
	}

	//获取从当前时间开始，到上次领取奖励时间范围内，经过的整点数
	int diff = (hournow - dbcuser.Obj().rests)/3600 - 1;   //计算结果，即为下标

	if (diff > 23)
	{
		diff = 23;
		dbcuser.Obj().rests = hournow - 24*3600;
	}

	//循环计算占领据点数
	bool isCaptial = false;  //是否占领中心城
	int kindom = dbcuser.Obj().kingdom;//获取当前用户所属的国家
	int stronghold = 0;

	for (int i = 0; i < BATTLE_FIELD_CITY; ++i)
	{
		if (0 == i) //中心城
		{
			if (battlefield->history[diff][i] == kindom)
			{
				isCaptial = true;
				++stronghold;
			}
		}
		else
		{
			if (battlefield->history[diff][i] == kindom)
			{
				++stronghold;
			}
		}
	}

	WorldRewardConfigWrap worldrewardconfig;

	unsigned hour = LogicCommonUtil::GetHourByTime(dbcuser.Obj().rests + 3600);  //下一个整点
	int multiple = worldrewardconfig.GetTimeMultiple(hour);  //时段系数

	//计算银币资源
	int coinbase = worldrewardconfig.GetCoinBase();
	int coinadd = coinbase * multiple * stronghold;  //基数*时间系数*据点数

	map<unsigned, unsigned> map_resource;
	map_resource.insert(make_pair(resource_type_coin, coinadd));

	if (isCaptial)  //占领中心城，额外奖励镔铁资源
	{
		unsigned tech_level = LogicScienceMgr::Instance()->GetCountryWarLevel(uid);
		int tech_coeff = worldrewardconfig.GetTechCoefficent(tech_level);

		int ironbase = worldrewardconfig.GetIronBase();
		int ironadd = ironbase * multiple * tech_coeff;
		map_resource.insert(make_pair(resource_type_iron, ironadd));
	}

	dbcuser.AddResource(map_resource, "World_History_Reward");
	dbcuser.Obj().rests += 3600; //下一个整点,即为当前领取的资源时间点

	dbcuser.Save();

	resp->set_coin(dbcuser.Obj().coin);
	resp->set_rests(dbcuser.Obj().rests);

	if (isCaptial)
	{
		resp->set_iron(dbcuser.Obj().iron);
	}

	return 0;
}

int WorldManager::RefreshMap()
{
	if (!File::IsExist(killrankpath))
	{
		File::RecursiveMkdir(killrankpath.c_str());
	}
	string filename = killrankpath + mapname;

	Json::Value m;
	m.resize(0);
	const BattleField* data = BMI->m_data;
	for(unsigned i=0;i<BATTLE_FIELD_CITY;++i)
		m.append(data->history[0][i]);

	return File::Write(filename, Json::ToString(m));
}
int WorldManager::RefreshAllKillRank()
{
	//从resourcemanager中取出所有玩家的资源信息
	OfflineResourceItem * killdata = ResourceManager::Instance()->m_data->item;
	map<unsigned, vector<unsigned> > kindomIndexRelation;   //不同国家的所有玩家信息。

	const map<unsigned, unsigned>& datamap = ResourceManager::Instance()->GetMap();

	//按国家划分
	for(map<unsigned,unsigned>::const_iterator uiter = datamap.begin(); uiter != datamap.end(); ++uiter)
	{
		unsigned kindom = killdata[uiter->second].kingdom;
		kindomIndexRelation[kindom].push_back(uiter->second);
	}

	char sztemp[4] = {0};

	//判断路径是否存在，如果不存在，则创建
	if (!File::IsExist(killrankpath))
	{
		File::RecursiveMkdir(killrankpath.c_str());
	}

	for(map<unsigned, vector<unsigned> >::iterator viter = kindomIndexRelation.begin(); viter != kindomIndexRelation.end(); ++viter)
	{
		if (0 == viter->first)  //跳过国家为0
		{
			continue;
		}

		sprintf(sztemp, "%u", viter->first);

		string filename = killrankpath + killrankname + string("_")+ string(sztemp);

		RefreshKindomKillRank(viter->second, filename);
	}

	//刷新活跃活动中的全服排行榜
	LogicEnlivenKillActivity::Instance()->RefreshFullServerKillRank(killrankpath);

	return 0;
}

int WorldManager::RefreshKindomKillRank(vector<unsigned> & kindomuser, string filename)
{
	multimap<unsigned, unsigned> killrank;   //杀敌数为key，下标为value

	for(int i = 0; i < kindomuser.size(); ++i)
	{
		unsigned index = kindomuser[i];

		const OfflineResourceItem & resource = ResourceManager::Instance()->m_data->item[index];
		killrank.insert(make_pair(resource.kill, index));
	}

	Json::Value rank(Json::arrayValue);
	int num = 0;

	for(multimap<unsigned, unsigned>::reverse_iterator it= killrank.rbegin();it!= killrank.rend();++it)
	{
		if(it->first == 0)   //杀敌数为0，则退出循环
			break;

		unsigned index = it->second;
		const OfflineResourceItem & resource = ResourceManager::Instance()->m_data->item[index];

		//再生成排行榜文件
		rank[num]["uid"] = resource.uid;
		rank[num]["rank"] = num+1;
		rank[num]["name"] = resource.name;
		rank[num]["level"] = resource.property[DemoOfflineProperty_u_level];  //玩家当时等级
		rank[num]["kill"] = it->first;

		++num;

		if(num == 50)
			break;
	}

	int ret = File::Write(filename, Json::ToString(rank));

	if(ret)
	{
		error_log("[RefreshKindomKillRank] write killrank fail");
		return ret;
	}

	return 0;
}

int WorldManager::ProvideReward()
{
	//清除
	m_kill_rank.clear();
	//发放经验奖励，并且重置杀敌量
	ProvideExpRewardAndResetKill();

	//发放排行榜奖励
	ProvideRankReward();

	//发送通知
	SendRankNotify();

	//发放杀敌活跃活动排行榜奖励
	LogicEnlivenKillActivity::Instance()->ProvideRankReward(killrankpath);

	return 0;
}

int WorldManager::ProvideExpRewardAndResetKill()
{
	//扫描每一个用户的杀敌数
	OfflineResourceItem * killdata = ResourceManager::Instance()->m_data->item;
	const map<unsigned, unsigned>& datamap = ResourceManager::Instance()->GetMap();
	const KillRankConfig::KillRankItem & rankitem = KillRankConfigWrap().KillRank().killrank();

	//取出杀敌与经验的配置
	for(map<unsigned,unsigned>::const_iterator uiter = datamap.begin(); uiter != datamap.end(); ++uiter)
	{
		float exp = 0;

		unsigned kill = killdata[uiter->second].kill;

		if (0 == kill)  //跳过杀敌量为0的玩家
		{
			continue;
		}

		unsigned uid = killdata[uiter->second].uid;

		//根据杀敌数，标记出所在的范围下标
		int target = 0;

		for(int i = rankitem.exp_killrange_size() -1; i >= 0; --i)
		{
			if (kill > rankitem.exp_killrange(i))
			{
				target = i; //最后的下标
				break;
			}
		}

		unsigned currentkill = kill;

		for(int j = target; j >= 0; --j)
		{
			unsigned lastnum = rankitem.exp_killrange(j);  //上一个阀值
			exp += (currentkill - lastnum) * rankitem.exp_coefficient(j);

			currentkill = lastnum;  //当前杀敌数
		}

		int addexp = (int)exp;

		m_kill_rank[uid].second = addexp;

		//判断用户是否在线
		if (UserManager::Instance()->IsOnline(uid))  //在线
		{
			LogicUserManager::Instance()->AddExp(uid, addexp);

			//在线用户，则重置杀敌活跃活动的奖励领取状态
			LogicEnlivenKillActivity::Instance()->ResetRewardStatus(uid);
		}
		else  //离线，将经验写会资源管理
		{
			killdata[uiter->second].exp += addexp;   //等待上线进行结算
		}

		killdata[uiter->second].KillReset();  //杀敌数重置
	}

	return 0;
}

int WorldManager::ProvideRankReward()
{
	//读取各个国家的文件
	char sztemp[4] = {0};
	Json::Reader reader;
	Json::Value jdata;
	int ret = 0;

	//获取杀敌排行榜奖励配置
	const KillRankConfig::KillRankItem & rankitem = KillRankConfigWrap().KillRank().killrank();

	for(int i = 1; i <= 3; ++i)
	{
		//判断文件是否存在
		sprintf(sztemp, "%u", i);
		string filename = killrankpath + killrankname + string("_")+ string(sztemp);

		if (!File::IsExist(filename))   //文件不存在，则认为没有排行榜数据，不做处理
		{
			continue;
		}

		//读取文件
		string data;
		ret = File::Read(filename, data);

		if (ret)
		{
			error_log("[ProvideRankReward] read file error. path=%s", filename.c_str());
			return R_ERR_DATA;
		}

		if (!reader.parse(data, jdata))
		{
			string reason = reader.getFormatedErrorMessages();
			error_log("[ProvideRankReward] reader parse failed. reason = %s", reason.c_str());
			return R_ERR_DATA;
		}

		if (!jdata.isArray())
		{
			error_log("[ProvideRankReward] json data format error, must be array. path=%s", filename.c_str());
			return R_ERR_DATA;
		}

		//处理数据
		for(unsigned j = 0; j < jdata.size(); ++j)
		{
			unsigned uid = jdata[j]["uid"].asUInt();
			unsigned rank = jdata[j]["rank"].asUInt();
			unsigned count = rankitem.reward(rank - 1).base().market();

			m_kill_rank[uid].first = rank;

			//判断用户是否在线
			if (UserManager::Instance()->IsOnline(uid))  //在线
			{
				DBCUserBaseWrap userwrap(uid);
				userwrap.AddMarket(count, "Kill_Rank_Reward");
			}
			else  //离线，将龙鳞写回资源管理
			{
				OfflineResourceItem & resourceitem = LogicResourceManager::Instance()->Get(uid);
				resourceitem.gem += count;
			}
		}
	}

	return 0;
}

int WorldManager::SendRankNotify()
{
	map<unsigned, pair<unsigned, unsigned> >::iterator piter;
	Json::FastWriter writer;
	Json::Value notifyval;
	NotifyItem notifyitem;
	string content;

	unsigned now = Time::GetGlobalTime();

	for(piter = m_kill_rank.begin(); piter != m_kill_rank.end(); ++piter)
	{
		unsigned uid = piter->first;
		unsigned rank = piter->second.first;
		unsigned exp = piter->second.second;

		//组装json数据
		notifyval.clear();
		content.clear();
		notifyval["rank"] = rank;
		notifyval["exp"] = exp;
		content  = writer.write(notifyval);

		//拼接通知内容
		notifyitem.Clear();

		notifyitem.uid = uid;
		notifyitem.id = e_Notify_Killrank;
		notifyitem.ts = now;
		snprintf(notifyitem.content, NOTIFY_CONTENT_LEN, "%s", content.c_str());

		LogicNotifyManager::Instance()->AddNotify(notifyitem);
	}

	return 0;
}

int WorldManager::Process(unsigned uid, ProtoBattleField::RequestKillReward* msg, ProtoBattleField::ReplyKillReward* resp)
{
	//
	DBCUserBaseWrap user(uid);

	if (user.Obj().rewardb <= 0)
	{
		throw std::runtime_error("not_enougth_exploit_box");
	}
	//
	ExploitBoxCfgWrap cfg;
	unsigned box_lvl = LogicScienceMgr::Instance()->GetExploitBoxLevel(uid);
	const ExploitBoxConfig::ExploitReward& rewardCfg = cfg.BoxReward(box_lvl);

	//
	user.UseExploitBox(1);
	resp->set_exploit_box_cnt(user.Obj().rewardb);

	int nMul = cfg.GetRewardMul(rewardCfg);
	resp->set_multiple(nMul);
	std::string reason = "expoit_box_reward";
	if (rewardCfg.has_equips())
	{
		unsigned eqid = rewardCfg.equips().eqid();
		unsigned cnt = rewardCfg.equips().count() * nMul;

		resp->set_equips_cnt(cnt);

		LogicEquipmentManager::Instance()->AddEquipment(uid, eqid, cnt, reason, resp->mutable_equips());
	}

	if (rewardCfg.has_base())
	{
		user.Reward(rewardCfg.base(), resp->mutable_base(), reason, nMul);
	}

	const CommonGiftConfig::BaseReward& baseCfg = cfg.BaseReward(box_lvl);
	user.Reward(baseCfg, resp->mutable_base(), reason);

	//todo 接入开启功勋宝箱任务
	LogicMissionManager::MissionParam missionparam;
	missionparam.type = mission_type_open_exploitbox;

	LogicMissionManager::Instance()->VerifyMissionComplete(uid, missionparam);

	return 0;
}

bool WorldManager::checkMission(uint16_t cid)
{
	bool ret = false;
	for(unsigned m=0;m<SG17_KINGDOM;++m)
	{
		if(GET_BMI->mission[m].m1 == cid && GET_BMI->mission[m].m1status == BattleFieldMissonStatus_defending)
		{
			ret = true;
			GET_BMI->mission[m].m1status = BattleFieldMissonStatus_defend_over;
		}
		if(GET_BMI->mission[m].m1 == cid && GET_BMI->mission[m].m1status == BattleFieldMissonStatus_attacking)
		{
			ret = true;
			GET_BMI->mission[m].m1status = BattleFieldMissonStatus_attack_over;
		}
		if(GET_BMI->mission[m].m2 == cid && GET_BMI->mission[m].m2status == BattleFieldMissonStatus_defending)
		{
			ret = true;
			GET_BMI->mission[m].m2status = BattleFieldMissonStatus_defend_over;
		}
		if(GET_BMI->mission[m].m2 == cid && GET_BMI->mission[m].m2status == BattleFieldMissonStatus_attacking)
		{
			ret = true;
			GET_BMI->mission[m].m2status = BattleFieldMissonStatus_attack_over;
		}
	}
	return ret;
}
void WorldManager::startMission()
{
	if(GET_BMI->HasMission())
		return;

	const map<unsigned, unsigned>& m = RMI->GetMap();
	for(map<unsigned, unsigned>::const_iterator it=m.begin();it!=m.end();++it)
		RMI->m_data->item[it->second].MissionReset();

	vector<unsigned> uids;
	UMI->GetOnlineUsers(uids);
	for (vector<unsigned>::iterator it=uids.begin();it!=uids.end();++it)
	{
		try
		{
			DBCUserBaseWrap(*it).ResetCountryTaskStatus();
		}
		catch(const std::exception& e)
		{
			(void)e;
		}
	}

	vector<uint16_t> dc;
	map<uint8_t, vector<uint16_t> > nkm, bkm;
	for(CityHeroMap::iterator it=m_cityHeroMap.begin();it!=m_cityHeroMap.end();++it)
	{
		uint8_t ck = GET_BMI_CITY(it->first).kingdom;
		if(ck == 0)
			continue;
		if(BMI->IsCityBesideEnemy(it->first))
			bkm[ck].push_back(it->first);
		else
			nkm[ck].push_back(it->first);
	}
	uint8_t fk = 0;
	for(unsigned i=1;i<=SG17_KINGDOM;++i)
	{
		if(nkm[i].size() + bkm[i].size() > 200)
		{
			fk = i;
			break;
		}
	}
	if(fk)//2v1
	{
		uint8_t ek1, ek2;
		if(fk == 1)
		{
			ek1 = 2;
			ek2 = 3;
		}
		else if(fk == 2)
		{
			ek1 = 1;
			ek2 = 3;
		}
		else
		{
			ek1 = 1;
			ek2 = 2;
		}

		map<unsigned, vector<uint16_t> > sk1, sk2;
		for(vector<uint16_t>::iterator it=nkm[fk].begin();it!=nkm[fk].end();++it)
		{
			sk1[BMI->GetRange(ek1, *it)].push_back(*it);
			sk2[BMI->GetRange(ek2, *it)].push_back(*it);
		}
		random_shuffle(sk1.begin()->second.begin(), sk1.begin()->second.end());
		random_shuffle(sk2.begin()->second.begin(), sk2.begin()->second.end());

		GET_BMI->mission[ek1-1].m1 = GET_BMI->mission[fk-1].m1 = *(sk1.begin()->second.begin());
		GET_BMI->mission[ek2-1].m1 = GET_BMI->mission[fk-1].m2 = *(sk2.begin()->second.begin());
		GET_BMI->mission[ek1-1].m1status = GET_BMI->mission[ek2-1].m1status = BattleFieldMissonStatus_attacking;
		GET_BMI->mission[fk-1].m1status = GET_BMI->mission[fk-1].m2status = BattleFieldMissonStatus_defending;

		GET_BMI->mission[ek1-1].m2 = nkm[ek1].empty()?*(bkm[ek1].rbegin()):*(nkm[ek1].rbegin());
		GET_BMI->mission[ek2-1].m2 = nkm[ek2].empty()?*(bkm[ek2].rbegin()):*(nkm[ek2].rbegin());
		GET_BMI->mission[ek1-1].m2status = GET_BMI->mission[ek2-1].m2status = BattleFieldMissonStatus_defending;

		dc.push_back(GET_BMI->mission[fk-1].m1);
		dc.push_back(GET_BMI->mission[fk-1].m2);
		dc.push_back(GET_BMI->mission[ek1-1].m2);
		dc.push_back(GET_BMI->mission[ek2-1].m2);
	}
	else//1v1v1
	{
		map<uint8_t, uint8_t> vs;
		if(Math::GetRandomInt(2))
		{
			vs[1] = 2;
			vs[2] = 3;
			vs[3] = 1;
		}
		else
		{
			vs[1] = 3;
			vs[2] = 1;
			vs[3] = 2;
		}

		map<uint8_t, map<unsigned, vector<uint16_t> > > sk;
		for(unsigned i=1;i<=SG17_KINGDOM;++i)
		{
			vector<uint16_t> &km = nkm[vs[i]].empty()?bkm[vs[i]]:nkm[vs[i]];
			for(vector<uint16_t>::iterator it=km.begin();it!=km.end();++it)
				sk[i][BMI->GetRange(i, *it)].push_back(*it);
			random_shuffle(sk[i].begin()->second.begin(), sk[i].begin()->second.end());
			GET_BMI->mission[i-1].m1 = GET_BMI->mission[vs[i]-1].m2 = *(sk[i].begin()->second.begin());
			GET_BMI->mission[i-1].m1status = BattleFieldMissonStatus_attacking;
			GET_BMI->mission[vs[i]-1].m2status = BattleFieldMissonStatus_defending;

			dc.push_back(GET_BMI->mission[vs[i]-1].m2);
		}
	}

	sendMissionStat();

	//放在最后，npc创建不成功就return了
	for(vector<uint16_t>::iterator it=dc.begin();it!=dc.end();++it)
	{
		if(!m_cityHeroMap.count(*it))
			continue;
		uint8_t ck = GET_BMI_CITY(*it).kingdom;
		while(m_cityHeroMap[*it].countn < 30)
		{
			HeroPropertyItemIndex ni = HMI->CreateWorldNPC(e_normal_npc, ck, *it);
			if(ni.empty())
				return;
			++m_cityHeroMap[*it].countn;
			if(m_cityHeroMap[*it].Fighting())
				joinFight(ni, *it);
			else
				m_cityHeroMap[*it].heros[ck].insert(ni);
		}
	}
}
void WorldManager::endMission()
{
	if(!GET_BMI->HasMission())
		return;

	for(unsigned i=0;i<SG17_KINGDOM;++i)
	{
		switch(GET_BMI->mission[i].m1status)
		{
		case BattleFieldMissonStatus_attacking:
			GET_BMI->mission[i].m1status = BattleFieldMissonStatus_attack_lose;
			break;
		case BattleFieldMissonStatus_attack_over:
			GET_BMI->mission[i].m1status = BattleFieldMissonStatus_attack_win;
			break;
		case BattleFieldMissonStatus_defending:
			GET_BMI->mission[i].m1status = BattleFieldMissonStatus_defend_win;
			break;
		case BattleFieldMissonStatus_defend_over:
			GET_BMI->mission[i].m1status = BattleFieldMissonStatus_defend_lose;
			break;
		}
		switch(GET_BMI->mission[i].m2status)
		{
		case BattleFieldMissonStatus_attacking:
			GET_BMI->mission[i].m2status = BattleFieldMissonStatus_attack_lose;
			break;
		case BattleFieldMissonStatus_attack_over:
			GET_BMI->mission[i].m2status = BattleFieldMissonStatus_attack_win;
			break;
		case BattleFieldMissonStatus_defending:
			GET_BMI->mission[i].m2status = BattleFieldMissonStatus_defend_win;
			break;
		case BattleFieldMissonStatus_defend_over:
			GET_BMI->mission[i].m2status = BattleFieldMissonStatus_defend_lose;
			break;
		}
	}

	sendMissionStat();
}
void WorldManager::onDay()
{
	DefineWorldNPC();

	const map<unsigned, unsigned>& m = RMI->GetMap();
	for(map<unsigned, unsigned>::const_iterator it=m.begin();it!=m.end();++it)
		RMI->m_data->item[it->second].DailyReset();

	BMI->OnDay();
	ProtoBattleField::ResetBattleReward * msg = new ProtoBattleField::ResetBattleReward;
	GET_BMI->SetMessage(msg);
	LMI->broadcastMsg(msg);
}

int WorldManager::Process(unsigned uid, ProtoBattleField::RequestMissionPersonalReward* msg, ProtoBattleField::ReplyMissionPersonalReward* resp)
{
	DBCUserBaseWrap user(uid);
	unsigned task_no = msg->task_no();

	if (! user.IsGetMissionPersonalReward(task_no))
	{
		throw std::runtime_error("get_mission_Personal_reward_status_error");
	}

	if (task_no == 3 && LogicResourceManager::Instance()->Get(uid).mkill < 50000)
	{
		throw std::runtime_error("kills_not_enough");
	}

	user.SetGetMissionPersonalRewardStatus(task_no);

	const CountryTaskCfgWrap::PersonalRewardType& rewardCfg
					= CountryTaskCfgWrap().PersonalReward(task_no);
	std::string reason = "country_task_personal_reward";
	for (int i = 0; i < rewardCfg.size(); i++)
	{
		const RewardConfig::Reward& itemCfg = rewardCfg.Get(i);

		if (itemCfg.has_equips())
		{
			unsigned eqid = itemCfg.equips().eqid();
			unsigned cnt = itemCfg.equips().count();


			resp->add_equips_cnt(cnt);

			LogicEquipmentManager::Instance()
				->AddEquipment(uid, eqid, cnt, reason, resp->mutable_equips());
		}

		if (itemCfg.has_base())
		{
			unsigned tech_level = LogicScienceMgr::Instance()->GetCountryWarLevel(uid);
			int tech_coeff = CountryTaskCfgWrap().GetTechCoefficent(tech_level);

			user.Reward(itemCfg.base(), resp->mutable_base(), reason, tech_coeff);
		}
	}

	resp->add_mp(user.Obj().mp1);
	resp->add_mp(user.Obj().mp2);
	resp->add_mp(user.Obj().mp3);

	return 0;
}


int WorldManager::Process(unsigned uid, ProtoBattleField::RequestMissionCountryReward* msg, ProtoBattleField::ReplyMissionCountryReward* resp)
{
	BattleField * battlefield = BattleFieldManager::Instance()->m_data;
	if (battlefield->HasMission())
	{
		throw std::runtime_error("not_publish_mission");
	}

	DBCUserBaseWrap user(uid);
	if(user.Obj().kingdom > SG17_KINGDOM || user.Obj().kingdom == 0)
	{
		throw std::runtime_error("kingdom_error");
	}
	unsigned task_no = msg->task_no();
	if (! battlefield->mission[user.Obj().kingdom - 1].IsGetTaskReward(task_no))
	{
		throw std::runtime_error("country_task_is_not_over");
	}

	bool isExpand = battlefield->mission[user.Obj().kingdom - 1].IsGetExpandTaskReward(task_no);
	if (! user.IsGetMissionCountryReward(task_no))
	{
		throw std::runtime_error("get_mission_Country_reward_status_error");
	}

	user.SetGetMissionCountryRewardStatus(task_no);

	//开服时间
	unsigned open_days = LMI->GetOpenDays();
	unsigned kills = LogicResourceManager::Instance()->Get(uid).mkill;

	CountryTaskCfgWrap cfg = CountryTaskCfgWrap();
	const CommonGiftConfig::BaseReward& rewardCfg
						= cfg.BaseCountryReward(open_days, kills);
	float factor = cfg.GetBaseFactor(open_days, kills);
	if (isExpand)
	{
		float expand_factor = factor * cfg.GetExpandFactor(open_days, kills);
		factor += expand_factor;

		unsigned hour = LogicCommonUtil::GetHourByTime(Time::GetGlobalTime());
		if(hour >= BATTLE_MISSION_3_E || hour < BATTLE_MISSION_1_S)
			user.AddTicket(5);
		else
			user.AddTicket(3);
	}

	std::string reason = "country_task_country_reward";
	user.Reward(rewardCfg, resp->mutable_base(), reason, factor);

	resp->add_mk(user.Obj().mk1);
	resp->add_mk(user.Obj().mk2);

	return 0;
}

int WorldManager::Process(unsigned uid, ProtoBattleField::RequestAuto* msg)
{
	if(GET_RMI(uid).viplevel >= 2)
		GET_RMI(uid).is_atuo = msg->b_atuo();
	return 0;
}

int WorldManager::Process(Bot::RequestMove* req)
{
	unsigned uid = req->uid();

	if(!UMI->IsOnline(uid))
		return R_ERROR;

	set<HeroPropertyItemIndex> heros;
	HMI->GetHeros(uid, heros);
	bool flag = false;
	uint16_t c = 0;
	for(set<HeroPropertyItemIndex>::iterator it=heros.begin();it!=heros.end();++it)
	{
		if(BattleFieldManager::isCapital(GET_HMI(*it).city))
		{
			flag = true;
			break;
		}
	}
	if(flag)
	{
		OfflineResourceItem& rmi = GET_RMI(uid);
		uint8_t uk = rmi.kingdom;
		vector<uint16_t> e;
		unsigned a = 1;
		for(CityHeroMap::iterator it=m_cityHeroMap.begin();it!=m_cityHeroMap.end();++it)
		{
			if(BattleFieldManager::isCapital(it->first))
				continue;
			if(GET_BMI_CITY(it->first).kingdom != uk)
			{
				if(BMI->IsCityBesideKingdom(it->first, uk))
					e.push_back(it->first);
			}
			else
				++a;
		}
		if(e.empty())
			return 0;
		if((a > 100 && a <= 120 && Math::GetRandomInt(100) < 50)
		|| (a > 120 && a <= 140 && Math::GetRandomInt(100) < 80)
		|| a > 140)
			return 0;

		Bot::BotMove *m = new Bot::BotMove;
		rmi.SetMessage(m->mutable_info());

		c = e[Math::GetRandomInt(e.size())];
		const list<uint16_t>& cids = BMI->GetRoad(uk, c);
		ProtoBattleField::RequestMove msg;
		ProtoBattleField::ReplyMove resp;
		for(list<uint16_t>::const_iterator it=cids.begin();it!=cids.end();++it)
		{
			msg.add_cids(unsigned(*it));
			m->add_cids(unsigned(*it));
		}

		for(set<HeroPropertyItemIndex>::iterator it=heros.begin();it!=heros.end();++it)
		{
			HeroPropertyItem& hmi = GET_HMI(*it);
			if(BattleFieldManager::isCapital(hmi.city))
			{
				m->add_id(it->id);
				hmi.FullSoldires(rmi.property[DemoOfflineProperty_soldier] + (hmi.extraid?1:0));
				msg.set_id(it->id);
				Process(uid, &msg, &resp);
			}
		}

		LMI->broadcastMsg(m);
	}

	//debug_log("uid=%u,target=%u", uid, c);
	return 0;
}
int WorldManager::Process(Bot::RequestCity* req)
{
	unsigned uid = req->uid();

	if(!UMI->IsOnline(uid))
		return R_ERROR;

	OfflineResourceItem& rmi = GET_RMI(uid);
	set<HeroPropertyItemIndex> heros;
	vector<HeroPropertyItemIndex> vhero;
	HMI->GetHeros(uid, heros);
	uint16_t c = 0;
	for(set<HeroPropertyItemIndex>::iterator it=heros.begin();it!=heros.end();++it)
	{
		if(!IsHeroFighting(*it))
		{
			HeroPropertyItem& hmi = GET_HMI(*it);
			hmi.FullSoldires(rmi.property[DemoOfflineProperty_soldier] + (hmi.extraid?1:0));
			vhero.push_back(*it);
		}
	}
	if(!vhero.empty())
	{
		uint8_t uk = rmi.kingdom;
		vector<uint16_t> e;
		for(CityHeroMap::iterator it=m_cityHeroMap.begin();it!=m_cityHeroMap.end();++it)
		{
			if(GET_BMI_CITY(it->first).kingdom == uk)
				e.push_back(it->first);
		}
		if(e.empty())
			return 0;

		c = e[Math::GetRandomInt(e.size())];
		unsigned euid = GET_BMI_CITY(c).uid;
		if(uid == euid)
			return 0;

		vector<HeroPropertyItemIndex> enemy;
		if (euid > 0)
			HMI->GetHeros(euid, enemy);
		if(enemy.empty())
		{
			const vector<unsigned> &ids = CMI->GetCityNPC(CMI->GetScale(c), LMI->GetOpenDays());
			for(vector<unsigned>::const_iterator it = ids.begin();it!=ids.end();++it)
				enemy.push_back(HeroPropertyItemIndex(e_gate_npc,*it));
		}
		return WMI->CreateLadderFight(uid, e_gt_city_min + c, vhero, enemy, CMI->GetGid(c));
	}

	return 0;
}

int WorldManager::Process(unsigned uid, ProtoBattleField::RequestBattleReward* msg, ProtoBattleField::ReplyBattleReward* resp)
{
	unsigned ri = msg->index();
	bool ca = msg->cash();
	if(ri >= BATTLE_FIELD_REWARD_R)
		return R_ERR_PARAM;

	OfflineResourceItem& rmi = GET_RMI(uid);
	if(rmi.kingdom == 0 || rmi.kingdom > SG17_KINGDOM)
		return R_ERR_PARAM;
	uint16_t cid = GET_BMI->reward[rmi.kingdom-1][uid%BATTLE_FIELD_REWARD_R][ri][0];
	unsigned t = GET_BMI->reward[rmi.kingdom-1][uid%BATTLE_FIELD_REWARD_R][ri][1];
	if(GET_BMI_CITY(cid).kingdom != rmi.kingdom || IsCityFighting(cid) )
		return R_ERR_LOGIC;

	unsigned index = BattleRewardManager::Instance()->GetIndex(uid);
	DataBattleReward &b = BattleRewardManager::Instance()->m_data->data[index];
	if(CTime::IsDiffDay(b.rts, Time::GetGlobalTime()))
	{
		b.rts = Time::GetGlobalTime();
		b.r = 0;
		BattleRewardManager::Instance()->m_data->MarkChange(index);
	}
	if(0x01<<ri & b.r)
		return R_ERR_LOGIC;
	b.r |= 0x01<<ri;
	BattleRewardManager::Instance()->m_data->MarkChange(index);

	unsigned c = CMI->GetBattleRewardCount(t, LMI->GetOpenDays());
	if(ca)
	{
		DBCUserBaseWrap(uid).CostCash(CMI->demo.m_config.battlereward(t).cu(), "RequestBattleReward");
		c *= CMI->demo.m_config.battlereward(t).c();
	}

	if(t == e_battle_reward_type_order)
		DBCUserBaseWrap(uid).AddRecruitProp(c, "RequestBattleReward");
	else if(t == e_battle_reward_type_set_1 || t == e_battle_reward_type_set_2 || t == e_battle_reward_type_set_3)
	{
		unsigned eqid = 0;
		switch(t)
		{
		case e_battle_reward_type_set_1:
			eqid = SET_MAT_1;
			break;
		case e_battle_reward_type_set_2:
			eqid = SET_MAT_2;
			break;
		case e_battle_reward_type_set_3:
			eqid = SET_MAT_3;
			break;
		default:
			break;
		}
		DataCommon::EquipmentAllCPP m;
		LogicEquipmentManager::Instance()->AddEquipment(uid, eqid, c, "RequestBattleReward", &m);
		resp->set_equd(m.equips(0).equd());
	}
	else if(t == e_battle_reward_type_longlin)
		DBCUserBaseWrap(uid).AddMarket(c, "RequestBattleReward");
	else
	{
		unsigned coin = 0, food = 0, wood = 0, iron = 0;
		switch(t)
		{
		case e_battle_reward_type_coin:
			coin = c;
			break;
		case e_battle_reward_type_food:
			food = c;
			break;
		case e_battle_reward_type_wood:
			wood = c;
			break;
		case e_battle_reward_type_iron:
			iron = c;
			break;
		default:
			break;
		}
		DBCUserBaseWrap(uid).AddResource(coin, food, wood, iron, "RequestBattleReward");
	}

	resp->set_type(t);
	resp->set_count(c);

	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::RequestCityMaster* msg, ProtoBattleField::ReplyCityMaster* resp)
{
	uint16_t cid = msg->cid();
	if(!m_cityHeroMap.count(cid))
		return R_ERR_PARAM;

	unsigned u = GET_BMI_CITY(cid).SetMessage(resp);
	if(u)
	{
		GET_RMI(u).SetMessage(resp);

		set<HeroPropertyItemIndex> heros;
		HMI->GetHeros(u, heros);
		for(set<HeroPropertyItemIndex>::const_iterator it = heros.begin();it != heros.end();++it)
		{
			try
			{
				HeroPropertyWrap hero(it->uid, it->id);
				resp->add_hero_ids(it->id);
				resp->add_hero_lvl(hero.GetHeroLevel());
				resp->add_hero_troops(hero.GetTotalTroops());
			}
			catch (const std::exception& e) {
				(void)e;
			}
		}
	}

	unsigned index = BattleRewardManager::Instance()->GetIndex(uid);
	DataBattleReward &b = BattleRewardManager::Instance()->m_data->data[index];
	if(CTime::IsDiffDay(b.cts, Time::GetGlobalTime()))
	{
		b.cts = Time::GetGlobalTime();
		b.ctimes = 0;
		BattleRewardManager::Instance()->m_data->MarkChange(index);
	}
	resp->set_ccd(b.ccd);
	resp->set_ctimes(b.ctimes);

	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::StartCityBattle* msg)
{
	uint16_t cid = msg->cid();
	if(!m_cityHeroMap.count(cid))
		return R_ERR_PARAM;

	unsigned euid = GET_BMI_CITY(cid).uid;
	if(uid == euid)
	{
		LMI->SetErrMsg("is_master");
		return R_ERR_LOGIC;
	}

	if(GET_RMI(uid).kingdom != GET_BMI_CITY(cid).kingdom)
	{
		LMI->SetErrMsg("not_same_kingdom");
		return R_ERR_LOGIC;
	}

	DBCUserBaseWrap(uid).CostUserResource(0, 0, 5000, 0, "StartCityBattle");

	unsigned index = BattleRewardManager::Instance()->GetIndex(uid);
	DataBattleReward &b = BattleRewardManager::Instance()->m_data->data[index];
	if(b.ccd > Time::GetGlobalTime())
	{
		LMI->SetErrMsg("no_times");
		return R_ERR_LOGIC;
	}
	b.ccd = Time::GetGlobalTime() + 600;
	BattleRewardManager::Instance()->m_data->MarkChange(index);

	vector<HeroPropertyItemIndex> heros;
	for (int i = 0;i < msg->hero_size(); ++i)
		heros.push_back(HeroPropertyItemIndex(uid, msg->hero(i)));
	vector<HeroPropertyItemIndex> enemy;
	if (euid > 0)
		HMI->GetHeros(euid, enemy);
	if(enemy.empty())
	{
		const vector<unsigned> &ids = CMI->GetCityNPC(CMI->GetScale(cid), LMI->GetOpenDays());
		for(vector<unsigned>::const_iterator it = ids.begin();it!=ids.end();++it)
			enemy.push_back(HeroPropertyItemIndex(e_gate_npc,*it));
	}
	return WMI->CreateLadderFight(uid, e_gt_city_min + cid, heros, enemy, CMI->GetGid(cid));
}
int WorldManager::CityMasterWin(unsigned uid, uint16_t cid)
{
	uint16_t oc = BMI->GetCityByMaster(uid);
	if(oc)
	{
		BMI->ResetMaster(oc);
		InsertCitySend(oc);
	}

	BMI->SetMaster(cid, uid);
	unsigned i = RMI->GetIndex(uid);
	if(i != -1)
		strncpy(GET_BMI_CITY(cid).name, SEQ_GET_RMI(i).name, BASE_NAME_LEN);
	InsertCitySend(cid);

	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::RequestCityReward* msg, ProtoBattleField::ReplyCityReward* resp)
{
	uint16_t cid = msg->cid();
	if(!m_cityHeroMap.count(cid))
		return R_ERR_PARAM;

	BattleFieldCity &city = GET_BMI_CITY(cid);
	if(uid != city.uid)
	{
		LMI->SetErrMsg("not_master");
		return R_ERR_LOGIC;
	}
	unsigned t = city.reward;
	if(t == e_city_reward_type_empty || t >= e_city_reward_type_max)
	{
		LMI->SetErrMsg("no_reward");
		return R_ERR_LOGIC;
	}

	unsigned index = BattleRewardManager::Instance()->GetIndex(uid);
	DataBattleReward &b = BattleRewardManager::Instance()->m_data->data[index];
	if(CTime::IsDiffDay(b.cts, Time::GetGlobalTime()))
	{
		b.cts = Time::GetGlobalTime();
		b.ctimes = 0;
		BattleRewardManager::Instance()->m_data->MarkChange(index);
	}
	if(b.ctimes >= 10)
	{
		LMI->SetErrMsg("no_times");
		return R_ERR_LOGIC;
	}

	++b.ctimes;
	BattleRewardManager::Instance()->m_data->MarkChange(index);
	city.reward = e_city_reward_type_max;

	unsigned c = CMI->GetCityRewardCount(CMI->GetScale(cid), t);
	resp->set_type(t);
	resp->set_count(c);
	if(t == e_city_reward_type_set_1 || t == e_city_reward_type_set_2 || t == e_city_reward_type_set_3)
	{
		unsigned eqid = 0;
		switch(t)
		{
		case e_city_reward_type_set_1:
			eqid = SET_MAT_1;
			break;
		case e_city_reward_type_set_2:
			eqid = SET_MAT_2;
			break;
		case e_city_reward_type_set_3:
			eqid = SET_MAT_3;
			break;
		default:
			break;
		}
		DataCommon::EquipmentAllCPP m;
		LogicEquipmentManager::Instance()->AddEquipment(uid, eqid, c, "RequestCityReward", &m);
		resp->set_equd(m.equips(0).equd());
	}
	else if(t == e_city_reward_type_iron)
		DBCUserBaseWrap(uid).AddResource(0, 0, 0, c, "RequestCityReward");

	return 0;
}
int WorldManager::Process(unsigned uid, ProtoBattleField::RequestFight* msg, ProtoBattleField::ReplyFight* resp)
{
	BattleDemo(msg, resp);
	return 0;
}
/***************************************************/
unsigned BattleDemoHero::gatenpcid = 0;
BattleDemoHero::BattleDemoHero(HeroPropertyItemIndex hi, bool otherVision, double diff)
{
	Clear();
	if(hi.isGateNPC())
	{
		const NPC::NPCInfo& npc = NPC_INFO(hi.id);
		property.push_back(int(double(npc.p_hp())*diff));
		property.push_back(int(double(npc.p_attack())*diff));
		property.push_back(int(double(npc.p_defend())*diff));
		property.push_back(npc.p_skill_extra());
		property.push_back(npc.p_skill_anti());
		property.push_back(npc.p_attack_extra());
		property.push_back(npc.p_attack_anti());
		property.push_back(npc.p_int());
		property.push_back(npc.p_str());
		property.push_back(npc.p_level());
		property.push_back(0);
		property.push_back(npc.p_soldier());
		property.push_back(npc.p_tech());
		property.push_back(npc.p_anti_tech());
		property.push_back(0);
		property.push_back(0);
		property.push_back(npc.p_level());

		for(unsigned i=0;i<property[DemoFightProperty_soldier];++i)
		{
			hp.push_back(property[DemoFightProperty_hp]);
			shape.push_back(Math::GetRandomInt(DemoS_shpae_3) + 1);
		}
		if(HasSkill())
			skill = npc.skilltime();
		else
			skill = 0;
		extraid = 0;
		city = 0;
		gate = 0;
		ouid = 0;
		oid = hi.id;
		kingdom = 0;
		hi.id = ++gatenpcid;
	}
	else if(hi.isWorld())
	{
		HeroPropertyItem& hero = GET_HMI(hi);
		unsigned id = hero.oid == 0?DEMO_NPC_DAY(LMI->GetOpenDays(),hi.uid):hero.oid;

		const NPC::NPCInfo& npc = NPC_INFO(id);
		property.push_back(int(double(npc.p_hp())*diff));
		property.push_back(int(double(npc.p_attack())*diff));
		property.push_back(int(double(npc.p_defend())*diff));
		property.push_back(npc.p_skill_extra());
		property.push_back(npc.p_skill_anti());
		property.push_back(npc.p_attack_extra());
		property.push_back(npc.p_attack_anti());
		property.push_back(npc.p_int());
		property.push_back(npc.p_str());
		property.push_back(npc.p_level());
		property.push_back(0);
		property.push_back(npc.p_soldier());
		property.push_back(npc.p_tech());
		property.push_back(npc.p_anti_tech());
		property.push_back(0);
		property.push_back(0);
		property.push_back(npc.p_level());

		for(unsigned i=0;i<property[DemoFightProperty_soldier];++i)
		{
			if(hero.oid == 0)
			{
				hp.push_back(property[DemoFightProperty_hp]);
				hero.hp[i] = property[DemoFightProperty_hp];
			}
			else
				hp.push_back(int(double(hero.hp[i])*diff));
			shape.push_back(Math::GetRandomInt(DemoS_shpae_3) + 1);
		}
		if(HasSkill())
			skill = npc.skilltime();
		else
			skill = 0;
		extraid = hero.extraid;
		city = hero.city;
		gate = hero.gate;
		ouid = hero.ouid;
		if(hero.oid == 0)
			oid = hero.oid = id;
		else
			oid = hero.oid;
		kingdom = hero.ouid;
	}
	else
	{
		HeroPropertyItem& hero = GET_HMI(hi);
		OfflineResourceItem& user = GET_RMI(hi.isVision()?hero.ouid:hi.uid);
		for(unsigned i=0;i<DemoHeroProperty_max;++i)
			property.push_back(hero.property[i]);
		property[DemoFightProperty_hp] = int(double(property[DemoFightProperty_hp])*diff);
		property[DemoFightProperty_attack] = int(double(property[DemoFightProperty_attack])*diff);
		property[DemoFightProperty_defend] = int(double(property[DemoFightProperty_defend])*diff);
		for(unsigned i=DemoOfflineProperty_soldier;i<=DemoOfflineProperty_u_level;++i)
			property.push_back(user.property[i]);
		if(hero.extraid)
			++property[DemoFightProperty_soldier];
		for(unsigned i=0;i<property[DemoFightProperty_soldier];++i)
		{
			hp.push_back(otherVision?property[DemoFightProperty_hp]:int(double(hero.hp[i])*diff));
			shape.push_back((hi.IsUser() && user.is_atuo) ? DemoS_shpae_a : DemoS_unchosen);
		}
		if(HasSkill())
			skill = HERO_INFO(hi.isVision()?hero.oid:hi.id).skilltime();
		else
			skill = 0;
		extraid = hero.extraid;
		city = otherVision?0:hero.city;
		gate = otherVision?0:hero.gate;
		ouid = otherVision?hi.uid:hero.ouid;
		oid = otherVision?hi.id:hero.oid;
		kingdom = user.kingdom;
		if(otherVision)
		{
			hi.uid = e_vision_other;
			hi.id = ++gatenpcid;
		}
	}
	index = hi;
	hpi = property[DemoFightProperty_soldier];
	for(int i=0;i<property[DemoFightProperty_soldier];++i)
	{
		if(hp[i] > 0)
		{
			hpi = i;
			break;
		}
	}
	if(hpi == property[DemoFightProperty_soldier] - 1)
	{
		switch(extraid)
		{
		case e_WingManID_5:
			property[DemoFightProperty_attack] = (int)ceil(double(property[DemoFightProperty_attack]) * double(WING_EFFECT_5));
			break;
		case e_WingManID_6:
			property[DemoFightProperty_defend] = (int)ceil(double(property[DemoFightProperty_defend]) * double(WING_EFFECT_5));
			break;
		case e_WingManID_7:
			property[DemoFightProperty_int] = (int)ceil(double(property[DemoFightProperty_int]) * double(WING_EFFECT_5));
			break;
		case e_WingManID_8:
			property[DemoFightProperty_attack_extra] = (int)ceil(double(property[DemoFightProperty_attack_extra]) * double(WING_EFFECT_5));
			break;
		case e_WingManID_9:
			property[DemoFightProperty_attack_anti] = (int)ceil(double(property[DemoFightProperty_attack_anti]) * double(WING_EFFECT_5));
			break;
		default:
			break;
		}
	}
}
BattleDemoHero::BattleDemoHero(const ProtoBattleField::HeroUid &hero)
{
	Clear();
	index.uid = hero.uid();
	index.id = hero.hero().id();
	if(hero.hero().property_size() != DemoFightProperty_max)
		throw runtime_error("property_wrong");
	for(int i=0;i<DemoFightProperty_max;++i)
		property.push_back(hero.hero().property(i));
	if(hero.hero().hp_size() != property[DemoFightProperty_soldier] || hero.hero().shape_size() != property[DemoFightProperty_soldier])
		throw runtime_error("s_wrong");
	for(int i=0;i<property[DemoFightProperty_soldier];++i)
	{
		hp.push_back(hero.hero().hp(i));
		shape.push_back(hero.hero().shape(i));
	}
	skill = hero.hero().skill();
	extraid = hero.hero().extraid();
	city = hero.hero().city();
	gate = hero.hero().gate();
	ouid = hero.hero().ouid();
	oid = hero.hero().oid();
	kingdom = 0;
	hpi = property[DemoFightProperty_soldier];
	for(int i=0;i<property[DemoFightProperty_soldier];++i)
	{
		if(hp[i] > 0)
		{
			hpi = i;
			break;
		}
	}
	if(hpi == property[DemoFightProperty_soldier])
		throw runtime_error("hp_wrong");
	if(hpi == property[DemoFightProperty_soldier] - 1)
	{
		switch(extraid)
		{
		case e_WingManID_5:
			property[DemoFightProperty_attack] = (int)ceil(double(property[DemoFightProperty_attack]) * double(WING_EFFECT_5));
			break;
		case e_WingManID_6:
			property[DemoFightProperty_defend] = (int)ceil(double(property[DemoFightProperty_defend]) * double(WING_EFFECT_5));
			break;
		case e_WingManID_7:
			property[DemoFightProperty_int] = (int)ceil(double(property[DemoFightProperty_int]) * double(WING_EFFECT_5));
			break;
		case e_WingManID_8:
			property[DemoFightProperty_attack_extra] = (int)ceil(double(property[DemoFightProperty_attack_extra]) * double(WING_EFFECT_5));
			break;
		case e_WingManID_9:
			property[DemoFightProperty_attack_anti] = (int)ceil(double(property[DemoFightProperty_attack_anti]) * double(WING_EFFECT_5));
			break;
		default:
			break;
		}
	}
}

//战法伤害系数
double BattleDemoHero::GetHeroSkill(){
	if(index.isUserVision())
		return double(HERO_INFO(oid).skillco());
	else if(index.isPVE())
		return double(NPC_INFO(oid).skillco());
	else if(index.IsUser())
		return double(HERO_INFO(index.id).skillco());
	return double(0);
}
//是否是强化战术
bool BattleDemoHero::IsStrengthShape(unsigned g, unsigned s){
	if(index.isUserVision())
		return CMI->IsHeroStrengthShape(oid, g, s);
	else if(index.isPVE())
		return CMI->IsNPCStrengthShape(oid, g, s);
	else if(index.IsUser())
		return CMI->IsHeroStrengthShape(index.id, g, s);
	return false;
}
//强化战术伤害
double BattleDemoHero::GetStrengthShape(){
	if(index.isUserVision())
		return double(HERO_INFO(oid).tacticaladd());
	else if(index.isPVE())
		return double(NPC_INFO(oid).tacticaladd());
	else if(index.IsUser())
		return double(HERO_INFO(index.id).tacticaladd());
	return double(0);
}
//平砍地形加成系数
double BattleDemoHero::GetHeroAttackG(unsigned g){
	double c = double(0);
	if(index.isUserVision() && CMI->IsHeroG(oid, g))
		c = double(HERO_INFO(oid).giftadd());
	else if(index.isPVE() && CMI->IsNPCG(oid, g))
		c =  double(NPC_INFO(oid).giftadd());
	else if(index.IsUser() && CMI->IsHeroG(index.id, g))
		c =  double(HERO_INFO(index.id).giftadd());
	return double(1) + c;
}
//科技战法加成
double BattleDemoHero::GetHeroTech(){
	if(property[DemoFightProperty_tech])
		return double(SCIENCE_ITEM(property[DemoFightProperty_tech]).val())/double(100);
	return double(0);
}
//科技战法抵抗
double BattleDemoHero::GetHeroAntiTech(){
	if(property[DemoFightProperty_anti_tech])
		return double(SCIENCE_ITEM(property[DemoFightProperty_anti_tech]).val())/double(100);
	return double(0);
}
//经验加成
double BattleDemoHero::GetExtraEXP(){
	double c = double(0);
	if(property[DemoFightProperty_hexp])
		c = double(SCIENCE_ITEM(property[DemoFightProperty_hexp]).val())/double(100);
	return double(1) + c;
}
//技能排数
unsigned BattleDemoHero::GetSkillRange(){
	if(index.isUserVision())
		return double(HERO_INFO(oid).skillrange());
	else if(index.isPVE())
		return double(NPC_INFO(oid).skillrange());
	else if(index.IsUser())
		return double(HERO_INFO(index.id).skillrange());
	return 1;
}
//hp系数
double BattleDemoHero::GetHPX(){
	return double(GetHp()) / double(property[DemoFightProperty_hp]) + double(DEMO_CONST.hp_c());
}
//禁卫系数
double BattleDemoHero::GetRangeX(unsigned k, unsigned range){
	double x = double(0);
	if(k && kingdom != k)
	{
		if(range <= BATTLE_RANGE_1)
			x = double(DEMO_CONST.r_a());
		else if(range <= BATTLE_RANGE_2)
			x = double(DEMO_CONST.r_b());
		else if(range <= BATTLE_RANGE_3)
			x = double(DEMO_CONST.r_c());
	}
	return double(1) - x;
}
void BattleDemoHero::BattleDemoHero::Injure(int d, BattleDemoHero* e, int &explode)
{
	enemy = e;
	if(hpi < property[DemoFightProperty_soldier])
	{
		int r = min(hp[hpi], d);
		hp[hpi] -= r;
		hurt += r*SG17_HERO_SOLDIER_SUB;
		enemy->damage += r*SG17_HERO_SOLDIER_SUB;
		//debug_log("%u:%u,%u:%u", index.uid, hurt, enemy->index.uid, enemy->damage);
		if(hp[hpi] == 0)
		{
			++hpi;
			switch(extraid)
			{
			case e_WingManID_3:
				if(hpi == property[DemoFightProperty_soldier])
					explode = (int)ceil(double(property[DemoFightProperty_hp])*double(WING_EFFECT_3));
				break;
			case e_WingManID_5:
				if(hpi == property[DemoFightProperty_soldier] - 1)
					property[DemoFightProperty_attack] = (int)ceil(double(property[DemoFightProperty_attack]) * double(WING_EFFECT_5));
				break;
			case e_WingManID_6:
				if(hpi == property[DemoFightProperty_soldier] - 1)
					property[DemoFightProperty_defend] = (int)ceil(double(property[DemoFightProperty_defend]) * double(WING_EFFECT_5));
				break;
			case e_WingManID_7:
				if(hpi == property[DemoFightProperty_soldier] - 1)
					property[DemoFightProperty_int] = (int)ceil(double(property[DemoFightProperty_int]) * double(WING_EFFECT_5));
				break;
			case e_WingManID_8:
				if(hpi == property[DemoFightProperty_soldier] - 1)
					property[DemoFightProperty_attack_extra] = (int)ceil(double(property[DemoFightProperty_attack_extra]) * double(WING_EFFECT_5));
				break;
			case e_WingManID_9:
				if(hpi == property[DemoFightProperty_soldier] - 1)
					property[DemoFightProperty_attack_anti] = (int)ceil(double(property[DemoFightProperty_attack_anti]) * double(WING_EFFECT_5));
				break;
			default:
				break;
			}

			if(index.isWorldTTTNpc() && (enemy->index.IsUser() || enemy->index.isVision()))
			{
				unsigned u = enemy->index.IsUser()?enemy->index.uid:enemy->ouid;
				LogicAttackHarborManager::Instance()->AddTTT(u, 1);
			}
		}
	}
}
void BattleDemoHero::Injure(int d, unsigned m, BattleDemoHero* e, int &explode)
{
	enemy = e;
	int ohpi = hpi;
	for(int i=hpi;i<property[DemoFightProperty_soldier];++i)
	{
		int r = min(hp[i], d);
		hp[i] -= r;
		hurt += r*SG17_HERO_SOLDIER_SUB;
		enemy->damage += r*SG17_HERO_SOLDIER_SUB;
		//debug_log("%u:%u,%u:%u", index.uid, hurt, enemy->index.uid, enemy->damage);
		if(hp[i] == 0)
		{
			++hpi;
			switch(extraid)
			{
			case e_WingManID_3:
				if(ohpi == property[DemoFightProperty_soldier] - 1)
					explode = (int)ceil(double(property[DemoFightProperty_hp])*double(WING_EFFECT_3));
				break;
			case e_WingManID_5:
				if(hpi == property[DemoFightProperty_soldier] - 1)
					property[DemoFightProperty_attack] = (int)ceil(double(property[DemoFightProperty_attack]) * double(WING_EFFECT_5));
				break;
			case e_WingManID_6:
				if(hpi == property[DemoFightProperty_soldier] - 1)
					property[DemoFightProperty_defend] = (int)ceil(double(property[DemoFightProperty_defend]) * double(WING_EFFECT_5));
				break;
			case e_WingManID_7:
				if(hpi == property[DemoFightProperty_soldier] - 1)
					property[DemoFightProperty_int] = (int)ceil(double(property[DemoFightProperty_int]) * double(WING_EFFECT_5));
				break;
			case e_WingManID_8:
				if(hpi == property[DemoFightProperty_soldier] - 1)
					property[DemoFightProperty_attack_extra] = (int)ceil(double(property[DemoFightProperty_attack_extra]) * double(WING_EFFECT_5));
				break;
			case e_WingManID_9:
				if(hpi == property[DemoFightProperty_soldier] - 1)
					property[DemoFightProperty_attack] = (int)ceil(double(property[DemoFightProperty_attack]) * double(WING_EFFECT_5));
				break;
			default:
				break;
			}
		}
		--m;
		if(m == 0)
			break;
	}

	int dn = hpi - ohpi;
	if(dn && index.isWorldTTTNpc() && (enemy->index.IsUser() || enemy->index.isVision()))
	{
		unsigned u = enemy->index.IsUser()?enemy->index.uid:enemy->ouid;
		LogicAttackHarborManager::Instance()->AddTTT(u, dn);
	}
}
void BattleDemoHero::CheckReward(unsigned type, unsigned k, unsigned range){
	bool dead = GetUnit() == 0;
	if(damage)
	{
		reward.damage += damage;
		if(type == e_battle_city || type == e_battle_rush)
		{
			reward.has = true;
			reward.kill += damage;
		}
	}
	if(hurt)
	{
		reward.hurt += hurt;
		if(index.IsUser() || index.isVision())
		{
			reward.has = true;
			double x = RewardM() * RewardV() * RewardB(type) * RewardC() * RewardI(enemy->property[DemoFightProperty_u_level]);
			unsigned tid = index.IsUser()?index.id:oid;
			reward.hexp[tid].id = tid;
			reward.hexp[tid].hexp += (unsigned)ceil(x * double(DEMO_REWARD.hexp()));
			if(type == e_battle_city || type == e_battle_rush)
				reward.hexp[tid].kill += damage;
			double z = x * RewardFB(type, enemy->property[DemoFightProperty_u_level]);
			if(unsigned(z))
			{
				reward.exp += (unsigned)ceil(z * GetExtraEXP() * RewardF(k, range));
				reward.coin += (unsigned)ceil(z / double(DEMO_REWARD.coin()));
			}
		}

		if(!index.notReal() && !dead)
		{
			GET_HMI(index).SyncHP(hp);
			WMI->InsertHeroSend(index);
		}
	}
	if(index.isPVE() && dead && enemy && (enemy->index.IsUser() || enemy->index.isVision()))
	{
		++enemy->reward.head;
		enemy->reward.exp += NPC_INFO(oid).r_exp();
		enemy->reward.coin += NPC_INFO(oid).r_coin();
		enemy->reward.food += NPC_INFO(oid).r_food();
		enemy->reward.wood += NPC_INFO(oid).r_wood();
		enemy->reward.iron += NPC_INFO(oid).r_iron();
		for(int i=0;i<NPC_INFO(oid).r_item_size();++i)
			enemy->reward.item[NPC_INFO(oid).r_item(i).id()] = NPC_INFO(oid).r_item(i).count();
		if(enemy->reward.exp || enemy->reward.coin || enemy->reward.food || enemy->reward.wood || enemy->reward.iron || !enemy->reward.item.empty())
			enemy->reward.has = true;
	}
	if(type == e_battle_rush && dead && enemy && enemy->GetUnit() && (enemy->index.IsUser() || enemy->index.isVision()))
	{
		enemy->reward.has = true;
		unsigned tid = enemy->index.IsUser()?enemy->index.id:enemy->oid;
		enemy->reward.hexp[tid].id = tid;
		enemy->reward.hexp[tid].win += 1;
	}
}
void BattleDemoHero::Die(HeroPropertyItemIndex hi, unsigned k, uint16_t cid, unsigned type){
	if(hi.isWorld() || hi.isVision())
	{
		if(type == e_battle_city)
			WMI->RemoveHeroFromCity(hi, true);
		HMI->Del(hi);
		if(hi.uid == e_normal_npc)
			WMI->RemoveNPCFromCity(cid, k);
	}
	else if(hi.IsUser())
	{
		if(type == e_battle_city)
			WMI->RemoveHeroFromCity(hi, true);
		GET_HMI(hi).Die(BMI->getCapital(k));
		WMI->TryRecoverHero(hi);
		WMI->InsertHeroSend(hi);
	}
}
bool BattleDemoHero::CheckDie(unsigned type){
	if(reward.has && (index.IsUser() || index.isVision()))
	{
		unsigned u = index.IsUser()?index.uid:ouid;
		if(UMI->IsOnline(u))
			LogicResourceManager::Instance()->Sync(u, reward, GET_RMI(u).SyncKill(reward, GET_BMI->HasMission()));
		else
			GET_RMI(u).Sync(reward, GET_BMI->HasMission());
		WMI->InsertReward(u, reward);
	}
	if(GetUnit())
	{
		Clear();
		return false;
	}
	Die(index, kingdom, city, type);
	return true;
}
/***************************************************/
BattleDemo::BattleDemo(uint16_t c){
	type = e_battle_city;
	cid = c;
	kingdom = cid / BATTLE_FIELD_CITY_KINGDOM_SEQ;
	range = kingdom?BMI->GetRange(kingdom, cid):0;
	uid = 0;
	gate = 0;
	gid = CMI->GetGid(cid);
	immediately = false;
	CheckQueue();
}
BattleDemo::BattleDemo(unsigned u, unsigned g, unsigned gi, vector<HeroPropertyItemIndex> &hi, vector<unsigned> &npc, double diff){
	type = e_battle_gate;
	cid = 0;
	kingdom = 0;
	range = 0;
	uid = u;
	gate = g;
	gid = gi;
	watcher.insert(u);
	for(vector<HeroPropertyItemIndex>::iterator it=hi.begin();it!=hi.end();++it)
		attacker.push_back(BattleDemoHero(*it, false, diff));
	for(vector<unsigned>::iterator it=npc.begin();it!=npc.end();++it)
		defender.push_back(BattleDemoHero(HeroPropertyItemIndex(e_gate_npc,*it)));
	immediately = false;
	CheckQueue();
}
BattleDemo::BattleDemo(uint16_t c, HeroPropertyItemIndex att, HeroPropertyItemIndex def){
	type = e_battle_rush;
	cid = c;
	kingdom = cid / BATTLE_FIELD_CITY_KINGDOM_SEQ;
	range = kingdom?BMI->GetRange(kingdom, cid):0;
	uid = 0;
	gate = 0;
	gid = CMI->GetGid(cid);
	watcher.insert(att.uid);
	attacker.push_back(BattleDemoHero(att));
	defender.push_back(BattleDemoHero(def));
	immediately = false;
	CheckQueue();
}
BattleDemo::BattleDemo(unsigned u, unsigned r, vector<HeroPropertyItemIndex> &hi, vector<HeroPropertyItemIndex> &enemy, unsigned g){
	type = e_battle_ladder;
	cid = 0;
	kingdom = 0;
	range = 0;
	uid = u;
	gate = r;
	gid = g?g:(r%DemoGType_4+1);
	watcher.insert(u);
	for(vector<HeroPropertyItemIndex>::iterator it=hi.begin();it!=hi.end();++it)
		attacker.push_back(BattleDemoHero(*it));
	for(vector<HeroPropertyItemIndex>::iterator it=enemy.begin();it!=enemy.end();++it)
		defender.push_back(BattleDemoHero(*it,true));
	immediately = false;
	CheckQueue();
}
BattleDemo::BattleDemo(ProtoBattleField::RequestFight *msg, ProtoBattleField::ReplyFight *resp)
{
	type = e_battle_temp;
	cid = 0;
	kingdom = 0;
	range = 0;
	uid = 0;
	gate = 0;
	gid = msg->gid();
	if(msg->attacker_size() == 0 || msg->defender_size() == 0)
		throw runtime_error("no_queue");
	for(int i=0;i<msg->attacker_size();++i)
		attacker.push_back(BattleDemoHero(msg->attacker(i)));
	for(int i=0;i<msg->defender_size();++i)
		defender.push_back(BattleDemoHero(msg->defender(i)));
	immediately = false;
	Clear();
	Turn();
	resp->set_id(msg->id());
	SetMessage(resp->mutable_turn());
}

void BattleDemo::SetMessage(ProtoBattleField::Turn* msg){
	msg->set_a_shape(a_shape);
	msg->set_d_shape(d_shape);
	msg->set_att_shape(att_shape);
	msg->set_def_shape(def_shape);
	for(vector<int>::iterator it=a_skill.begin();it!=a_skill.end();++it)
		msg->add_a_skill(*it);
	for(vector<int>::iterator it=d_skill.begin();it!=d_skill.end();++it)
		msg->add_d_skill(*it);
	for(vector<int>::iterator it=a_attack.begin();it!=a_attack.end();++it)
		msg->add_a_attack(*it);
	for(vector<int>::iterator it=d_attack.begin();it!=d_attack.end();++it)
		msg->add_d_attack(*it);
	msg->set_ts(Time::GetGlobalTime());
	msg->set_nextts(nextts);
	if(a_explode)
		msg->set_a_explode(a_explode);
	if(d_explode)
		msg->set_d_explode(d_explode);
}
void BattleDemo::SetMessage(ProtoBattleField::ReplyCity* msg){
	set<unsigned> uids;
	for(BattleDemoQueue::iterator it=attacker.begin();it!=attacker.end();++it)
		uids.insert(it->SetMessage(msg->add_attacker()));
	for(BattleDemoQueue::iterator it=defender.begin();it!=defender.end();++it)
		uids.insert(it->SetMessage(msg->add_defender()));
	for(set<unsigned>::iterator iter=uids.begin();iter!=uids.end();++iter)
	{
		if(IsValidUid(*iter))
			GET_RMI(*iter).SetMessage(msg->add_info(), true);
	}
	if(waiting)
	{
		msg->set_ts(Time::GetGlobalTime());
		msg->set_nextts(nextts);
	}
	msg->set_gid(gid);
	msg->set_type(type);
	msg->set_cid(cid);
	msg->set_uid(uid);
	msg->set_gate(gate);
}
//选择战法战术
void BattleDemo::SetShape(HeroPropertyItemIndex index, unsigned form){
	if(attacker.begin()->index == index)
		attacker.begin()->SetShape(form);
	else if(defender.begin()->index == index)
		defender.begin()->SetShape(form);
}
bool BattleDemo::Fight(){
	if(immediately)
	{
		while(!_fight());
		return true;
	}
	else
		return _fight();
}
bool BattleDemo::_fight(){
	if(waiting)
	{
		if(attacker.empty() || defender.empty())
			return CheckQueue();
		//debug_log("%u-%u-%u-%u-%u", uid, attacker.begin()->GetShape(), defender.begin()->GetShape(), nextts, Time::GetGlobalTime());
		if((attacker.begin()->GetShape()!=DemoS_unchosen && defender.begin()->GetShape()!=DemoS_unchosen)
		|| nextts <= Time::GetGlobalTime() || immediately)
		{
			Turn();
			SendMsg(false, true);
		}
	}
	else
	{
		if(nextts <= Time::GetGlobalTime() || immediately)
			return CheckQueue();
	}
	return false;
}
//推送
void BattleDemo::SendMsg(bool over, bool attackerwin){
	Message* m = NULL;
	if(!over)
	{
		if(!immediately)
		{
			if(waiting)
			{
				SetMessage(&m_msg);
				m = &m_msg;
			}
			else
			{
				SetMessage(m_msg.mutable_turn());
				m = m_msg.mutable_turn();
			}
		}
	}
	else if(IS_SEND_REWARD(type) && UMI->IsOnline(uid))
	{
		watcher.erase(uid);
		ProtoBattleField::BattleOver* msg = new ProtoBattleField::BattleOver;
		msg->set_attackerwin(attackerwin);
		msg->set_gate(type==e_battle_ladder?e_gt_ladder:gate);
		reward.SetMessage(msg->mutable_reward(), true);
#ifdef BATTLE_DEBUG_LOG
		debug_log("to:%u,msg:[%s]", uid, msg->ShortDebugString().c_str());
#endif
		LMI->sendMsg(uid, msg);
	}

	if(!watcher.empty() && (!immediately || over))
	{
		if(over)
		{
			ProtoBattleField::BattleOver* msg = new ProtoBattleField::BattleOver;
			msg->set_attackerwin(attackerwin);
			m = msg;
		}
		set<unsigned> del;
		for(set<unsigned>::iterator it=watcher.begin();it!=watcher.end();++it)
		{
			if(UMI->IsOnline(*it))
			{
#ifdef BATTLE_DEBUG_LOG
				debug_log("to:%u", *it);
#endif
				//LMI->sendMsg(*it, m, false); Ralf 20170310 change to sendMsgGroup
			}
			else
			{
#ifdef BATTLE_DEBUG_LOG
				debug_log("del:%u", *it);
#endif
				del.insert(*it);
			}
		}
#ifdef BATTLE_DEBUG_LOG
		debug_log("uid:%u,cid:%u,msg:[%s]", uid, cid, m->ShortDebugString().c_str());
#endif
		for(set<unsigned>::iterator it=del.begin();it!=del.end();++it)
			watcher.erase(*it);
		LMI->sendMsgGroup(watcher, m, false);//Ralf 20170310 change to sendMsgGroup
		if(over)
			delete m;
	}
}
//返回空缺排数
int BattleDemo::NeedQueue(bool att){
	BattleDemoQueue &queue = att?attacker:defender;
	int m = DEMO_SHOW_UNIT;
	BattleDemoQueue::iterator it = queue.begin();
	while(m > 0 && it != queue.end())
	{
		m -= it->GetUnit();
		++it;
	}
	if(m > 0)
		return m;
	return 0;
}
unsigned BattleDemo::GetQueueSize(bool att)
{
	if(att)
		return attacker.size();
	else
		return defender.size();
}
bool BattleDemo::IsInQueue(HeroPropertyItemIndex index, bool att)
{
	BattleDemoQueue &queue = att?attacker:defender;
	for(BattleDemoQueue::iterator it=queue.begin();it!=queue.end();++it)
	{
		if(index == it->index)
			return true;
	}
	return false;
}
//补充队列
void BattleDemo::AddQueue(bool att){
	if(type != e_battle_city)
		return;
	int m = NeedQueue(att);
	if(m == 0)
		return;

	BattleDemoQueue& mq = att?attacker:defender;
	CityHero& city = WMI->GetCityHero(cid);
	list<HeroPropertyItemIndex> &queue = att?city.attacker:city.defender;
	int ms = mq.size();
	int qs = queue.size();
	if(qs <= ms)
		return ;

	list<HeroPropertyItemIndex>::iterator it=queue.begin();
	for(int i=0;i<ms;++i)
		++it;
	set<HeroPropertyItemIndex> dead;
	while(m > 0 && it != queue.end())
	{
		if(GET_HMI(*it).IsDie())
			dead.insert(*it);
		else
		{
			mq.push_back(BattleDemoHero(*it));
			//debug_log("%u-%u", it->uid, it->id);
			m -= mq.rbegin()->GetUnit();
		}
		++it;
	}
	for(set<HeroPropertyItemIndex>::iterator it=dead.begin();it!=dead.end();++it)
		BattleDemoHero::Die(*it, WMI->GetKingdom(*it), cid, type);
}
//检查队列
bool BattleDemo::CheckQueue(){
	Clear();
	for(BattleDemoQueue::iterator it=attacker.begin();it!=attacker.end();++it)
		it->CheckReward(type, kingdom, range);
	for(BattleDemoQueue::iterator it=defender.begin();it!=defender.end();++it)
		it->CheckReward(type, kingdom, range);
	for(BattleDemoQueue::iterator it=attacker.begin();it!=attacker.end();)
	{
		if(IS_SEND_REWARD(type))
			reward.Append(it->reward);
		if(it->CheckDie(type))
			it = attacker.erase(it);
		else
		{
			it->reward.Clear();
			++it;
		}
	}
	for(BattleDemoQueue::iterator it=defender.begin();it!=defender.end();)
	{
		if(it->CheckDie(type))
			it = defender.erase(it);
		else
		{
			it->reward.Clear();
			++it;
		}
	}

	AddQueue(true);
	AddQueue(false);

	bool over = attacker.empty() || defender.empty();
	if(over)
	{
		if(type == e_battle_city)
			WMI->InsertCityOver(cid);
		else
		{
			if(type == e_battle_gate)
			{
				if(LogicFogGateManager::Instance()->IsFogGate(gate))
					WMI->InsertFogOver(uid, gate, defender.size());
				else if(!attacker.empty())
					WMI->InsertGateOver(uid, gate);
			}
			else if(type == e_battle_ladder)
			{
				if(!attacker.empty())
					WMI->InsertLadderOver(uid, gate);
			}
			else if(type == e_battle_ship)
			{
				//todo: ship over
				WMI->InsertShipOver();
			}
			for(BattleDemoQueue::iterator it=attacker.begin();it!=attacker.end();++it)
			{
				if(!it->index.notReal())
					WMI->InsertHeroOver(it->index);
			}
			for(BattleDemoQueue::iterator it=defender.begin();it!=defender.end();++it)
			{
				if(!it->index.notReal())
					WMI->InsertHeroOver(it->index);
			}
		}
	}
	else
		nextts = Time::GetGlobalTime() + (defender.begin()->index.isGateNPC()?DEMO_TIME.npcwait():DEMO_TIME.userwait());

	SendMsg(over, !attacker.empty());
	return over;
}
//战斗回合
void BattleDemo::Turn(){
	waiting = false;
	nextts = Time::GetGlobalTime() + DEMO_TIME.move();
	BattleDemoHero &att = *(attacker.begin());
	BattleDemoHero &def = *(defender.begin());
	bool pve = att.index.isPVE() && def.index.isPVE();
	int an = att.GetUnit(), dn = def.GetUnit();
	att_shape = att.GetShape();
	def_shape = def.GetShape();
	bool askill = att.skill > 0 && (att.index.IsUser()?(att_shape==DemoS_skill || att_shape==DemoS_shpae_a || (att_shape==DemoS_unchosen && an == att.skill)):true);
	bool dskill = def.skill > 0 && (def.index.IsUser()?(def_shape==DemoS_skill || def_shape==DemoS_shpae_a || (def_shape==DemoS_unchosen && dn == def.skill)):true);
	att.RandomShape(def_shape);
	def.RandomShape(att_shape);
	att_shape = att.GetShape();
	def_shape = def.GetShape();

	if(askill)
		Skill(att, defender, pve, a_skill, d_explode);
	if(att.GetUnit() != an || def.GetUnit() != dn)
		return;
	if(dskill)
		Skill(def, attacker, pve, d_skill, a_explode);
	if(att.GetUnit() != an || def.GetUnit() != dn)
		return;

	if(!askill && !dskill)
	{
		Shape(att, def);
		if(att.GetUnit() != an || def.GetUnit() != dn)
			return;
	}

	while(att.GetUnit() == an && def.GetUnit() == dn)
		Attack(att, def, pve);
	nextts += DEMO_TIME.attack() * min(7, (int)a_attack.size());
}

//战法阶段
void BattleDemo::Skill(BattleDemoHero &att, BattleDemoQueue &queue, bool pve, vector<int> &res, int &explode){
	nextts += DEMO_TIME.skill();
	--att.skill;
	BattleDemoQueue::iterator d = queue.begin();
	if(!IsSkill(att, *d, pve))
	{
		nextts += DEMO_TIME.skilldodge();
		res.push_back(0);
		return;
	}
	nextts += DEMO_TIME.skillattack();

	int n = att.GetSkillRange();
	vector<int> m;
	SkillTarget(n, queue, m);

	bool first = true;
	for(vector<int>::iterator it=m.begin();it!=m.end();++it)
	{
		int as = 0;
		SkillDamage(att, *d, n, *it, as, explode, first);
		first = false;
		for(unsigned i=0;i<*it;++i)
			res.push_back(as);
		++d;
	}
}
//寻找战法目标
void BattleDemo::SkillTarget(int &n, BattleDemoQueue &queue, vector<int> &m){
	BattleDemoQueue::iterator it = queue.begin();
	int j = n;
	while(n > 0 && it != queue.end())
	{
		int k = min(n, it->GetUnit());
		n -= k;
		m.push_back(k);
		++it;
	}
	n = j - n;
}

//计算战法伤害
void BattleDemo::SkillDamage(BattleDemoHero &attacker, BattleDemoHero &defender, int n, int m, int &as, int &explode, bool first){
	int a = max(0, attacker.property[DemoFightProperty_attack] - defender.property[DemoFightProperty_defend]);
	double a1 = double(a);
	if(a)
	{
		double v1 = double(attacker.GetSkillRange());
		double v2 = double(n);
		a1 *= attacker.GetHeroSkill() * v1 / v2 * (double(1) - (v1 - v2)/double(DEMO_CONST.skillrange()));
	}

	double e = double(attacker.property[DemoFightProperty_skill_extra]);
	if(attacker.property[DemoFightProperty_skill_extra])
	{
		if(a < DEMO_CONST.skill_a())
			e *= double(DEMO_CONST.skill_a_c());
		else if(a < DEMO_CONST.skill_b())
			e *= double(DEMO_CONST.skill_b_c());
		else
			e *= double(DEMO_CONST.skill_c_c());
	}

	as = (int)ceil((a1 + e - double(defender.property[DemoFightProperty_skill_anti]))
		 * (double(1) + attacker.GetHeroTech() - defender.GetHeroAntiTech()));
	if(as <= DEMO_CONST.skill_l())
		as = DEMO_CONST.skill_l() + Math::GetRandomInt(DEMO_CONST.skill_h() - DEMO_CONST.skill_l());

	if(first)
	{
		defender.Injure(as, m, &attacker, explode);
		if(explode)
		{
			int t;
			attacker.Injure(explode, &defender, t);
		}
	}
	else
	{
		int t;
		defender.Injure(as, m, &attacker, t);
	}
}
//判断战法抵挡
bool BattleDemo::IsSkill(BattleDemoHero &attacker, BattleDemoHero &defender, bool pve){
	if(defender.GetHeroID() == VIP_HERO_ID_8 || defender.GetWingEffect() == e_WingManID_2 )
		return false;

	/*这里的代码是错误的，写反了，未修改，直接使用新公式
	int x = pve ? DEMO_CONST.npcskill() : DEMO_CONST.userskill();
	int p = max(DEMO_CONST.skillmin(), min(DEMO_CONST.skillmax(),
			DEMO_CONST.skill_p_a()
			+ (attacker.property[DemoFightProperty_str] - defender.property[DemoFightProperty_str]) * 10 / x
			+ (attacker.property[DemoFightProperty_level] - defender.property[DemoFightProperty_level]) * 10 / DEMO_CONST.skill_p_b()));
	int r = Math::GetRandomInt(1000) + 1;
	return r > p;
	*/
	return Math::GetRandomInt(100) >= defender.property[DemoFightProperty_str] - attacker.property[DemoFightProperty_str];
}

//判断战术相克
bool BattleDemo::IsShape(unsigned a, unsigned d){
	return (a + 1 == d) || (a == DemoS_shpae_3 && d == DemoS_shpae_1);
}
//战术阶段
void BattleDemo::Shape(BattleDemoHero &attacker, BattleDemoHero &defender){
	nextts += DEMO_TIME.form();
	if(IsShape(att_shape, def_shape))
	{
		if(attacker.IsStrengthShape(gid, att_shape))
		{
			a_s = double(DEMO_CONST.f_s_w());
			a_shape = max(1, (int)ceil(double(DEMO_CONST.form_s_w()) * (double)attacker.GetHp() + attacker.GetStrengthShape()));
		}
		else
		{
			a_s = double(DEMO_CONST.f_w());
			a_shape = max(1, (int)ceil(double(DEMO_CONST.form_w()) * (double)attacker.GetHp()));
		}

		if(defender.IsStrengthShape(gid, def_shape))
			d_shape = max(1, (int)ceil(double(DEMO_CONST.form_s_l()) * (double)defender.GetHp()));
		else
			d_shape = max(1, (int)ceil(double(DEMO_CONST.form_l()) * (double)defender.GetHp()));
	}
	else if(IsShape(def_shape, att_shape))
	{
		if(attacker.IsStrengthShape(gid, att_shape))
			a_shape = max(1, (int)ceil(double(DEMO_CONST.form_s_l()) * (double)attacker.GetHp()));
		else
			a_shape = max(1, (int)ceil(double(DEMO_CONST.form_l()) * (double)attacker.GetHp()));

		if(defender.IsStrengthShape(gid, def_shape))
		{
			d_s = double(DEMO_CONST.f_s_w());
			d_shape = max(1, (int)ceil(double(DEMO_CONST.form_s_w()) * (double)defender.GetHp() + defender.GetStrengthShape()));
		}
		else
		{
			d_s = double(DEMO_CONST.f_w());
			d_shape = max(1, (int)ceil(double(DEMO_CONST.form_w()) * (double)defender.GetHp()));
		}
	}
	else
	{
		if(attacker.IsStrengthShape(gid, att_shape))
		{
			a_s = double(DEMO_CONST.f_s_e());
			a_shape = max(1, (int)ceil(double(DEMO_CONST.form_s_e()) * (double)attacker.GetHp() + attacker.GetStrengthShape()));
		}
		else
		{
			a_s = double(DEMO_CONST.f_e());
			a_shape = max(1, (int)ceil(double(DEMO_CONST.form_e()) * (double)attacker.GetHp()));
		}

		if(defender.IsStrengthShape(gid, def_shape))
		{
			d_s = double(DEMO_CONST.f_s_e());
			d_shape = max(1, (int)ceil(double(DEMO_CONST.form_s_e()) * (double)defender.GetHp() + defender.GetStrengthShape()));
		}
		else
		{
			d_s = double(DEMO_CONST.f_e());
			d_shape = max(1, (int)ceil(double(DEMO_CONST.form_e()) * (double)defender.GetHp()));
		}
	}

	if(attacker.GetHeroID() == VIP_HERO_ID_7)
		a_shape = (int)ceil(double(a_shape) * double(VIP_HERO_EFFECT_7));
	else
	{
		switch(attacker.GetWingEffect())
		{
		case e_WingManID_1:
			a_shape = (int)ceil(double(a_shape) * double(WING_EFFECT_1));
			break;
		case e_WingManID_4:
			if(attacker.property[DemoFightProperty_defend] > defender.property[DemoFightProperty_defend])
				a_shape = (int)ceil(double(a_shape) * double(WING_EFFECT_4));
			break;
		default:
			break;
		}
	}
	if(defender.GetHeroID() == VIP_HERO_ID_7)
		d_shape = (int)ceil(double(d_shape) * double(VIP_HERO_EFFECT_7));
	else
	{
		switch(defender.GetWingEffect())
		{
		case e_WingManID_1:
			d_shape = (int)ceil(double(d_shape) * double(WING_EFFECT_1));
			break;
		case e_WingManID_4:
			if(defender.property[DemoFightProperty_defend] > attacker.property[DemoFightProperty_defend])
				d_shape = (int)ceil(double(d_shape) * double(WING_EFFECT_4));
			break;
		default:
			break;
		}
	}

	attacker.Injure(d_shape, &defender, a_explode);
	defender.Injure(a_shape, &attacker, d_explode);
	if(d_explode)
	{
		int t;
		attacker.Injure(d_explode, &defender, t);
	}
	if(a_explode)
	{
		int t;
		defender.Injure(a_explode, &attacker, t);
	}
}

//平砍阶段
void BattleDemo::Attack(BattleDemoHero &attacker, BattleDemoHero &defender, bool pve){
	int as, ds;
	AttackDamage(attacker, defender, pve, a_s, as);
	AttackDamage(defender, attacker, pve, d_s, ds);
	a_attack.push_back(as);
	d_attack.push_back(ds);
	attacker.Injure(ds, &defender, a_explode);
	defender.Injure(as, &attacker, d_explode);
	if(d_explode)
	{
		int t;
		attacker.Injure(d_explode, &defender, t);
	}
	if(a_explode)
	{
		int t;
		defender.Injure(a_explode, &attacker, t);
	}
}
//计算平砍伤害
void BattleDemo::AttackDamage(BattleDemoHero &attacker, BattleDemoHero &defender, bool pve, double s, int &as){
	int a = max(0, attacker.property[DemoFightProperty_attack] - defender.property[DemoFightProperty_defend]);
	double a1 = double(a);
	if(a)
	{
		double x = double(pve ? DEMO_CONST.npcattack() : DEMO_CONST.userattack());
		a1 *= ((double(attacker.property[DemoFightProperty_int]) / double(defender.property[DemoFightProperty_int]) - double(1)) / x + double(1))
			* attacker.GetHPX() / defender.GetHPX() * attacker.GetHeroAttackG(gid) * (double(1) + s) * attacker.GetRangeX(kingdom, range);
	}
	double r = double(DEMO_CONST.randmin() + Math::GetRandomInt(1 + DEMO_CONST.randmax() - DEMO_CONST.randmin())) / double(100);
	double w = double(1.0);
	if(attacker.GetWingEffect() == e_WingManID_4 && attacker.property[DemoFightProperty_defend] > defender.property[DemoFightProperty_defend])
		w = double(WING_EFFECT_4);
	as = max(1, (int)ceil((a1 + double(attacker.property[DemoFightProperty_attack_extra]) - double(defender.property[DemoFightProperty_attack_anti])) * r * w));
}
