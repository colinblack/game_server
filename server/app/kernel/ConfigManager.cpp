/*
 * ConfigManager.cpp
 *
 *  Created on: 2016-8-22
 *      Author: Ralf
 */


#include "ConfigManager.h"

bool ConfigManager::m_init = true;

bool ConfigManager::Reload()
{
	ConfigManager *temp = new ConfigManager;
	if(!m_init)
	{
		m_init = true;
		delete temp;
		return false;
	}
	delete temp;
	Destroy();
	temp = Instance();
	return true;
}

void ConfigManager::Init()
{
	if(!m_init)
		return;
	//先初始化装备配置
	//加载配置文件的映射
	int eq_size = equipment.m_config.equips_size();

	for(int i = 0; i < eq_size; ++i)
	{
		const EquipmentConfig::Equip & equip = equipment.m_config.equips(i);

		unsigned eqid = equip.eqid();

		m_equipmap.insert(make_pair(eqid, i));
	}

	//配置eqid对应的price
	for(int i = 0; i < equipshop.m_config.levelpool_size(); ++i)
	{
		for(int j = 0; j < equipshop.m_config.levelpool(i).positions_size(); ++j)
		{
			for(int k = 0; k < equipshop.m_config.levelpool(i).positions(j).equips_size(); ++k)
			{
				uint32_t eqid = equipshop.m_config.levelpool(i).positions(j).equips(k).eqid();

				mapEqidPrice[eqid] = equipshop.m_config.levelpool(i).positions(j).equips(k).price();
			}
		}
	}

	//添加英雄配置的映射
	for(int i = 0; i < tavern.m_config.heroes_size(); ++i)
	{
		unsigned heroid = tavern.m_config.heroes(i).heroid();
		m_mapHeroIndex.insert(make_pair(heroid, i));

		//闯关id
		unsigned gateid = tavern.m_config.heroes(i).condition().gateid();
		m_mapGateIndex[gateid] = i;
	}

	//任务配置文件的映射
	const MissionConfig::Mission & missiones = mission.m_config.missions();
	pair<int, unsigned> missionpair;

	for(int i = 0; i < missiones.whether_size(); ++i)
	{
		unsigned curmid = missiones.whether(i).id();
		unsigned pre = missiones.whether(i).pre();

		m_mapPreMission[pre].insert(curmid);
		missionpair = make_pair(mission_condition_whether, i);
		m_mapMissonIndex[curmid] = missionpair;

	}

	for(int i = 0; i < missiones.single_size(); ++i)
	{
		unsigned curmid = missiones.single(i).id();
		unsigned pre = missiones.single(i).pre();

		m_mapPreMission[pre].insert(curmid);

		missionpair = make_pair(mission_condition_single, i);
		m_mapMissonIndex[curmid] = missionpair;
	}

	for(int i = 0; i < missiones._double_size(); ++i)
	{
		unsigned curmid = missiones._double(i).id();
		unsigned pre = missiones._double(i).pre();

		m_mapPreMission[pre].insert(curmid);

		missionpair = make_pair(mission_condition_double, i);
		m_mapMissonIndex[curmid] = missionpair;
	}

	for(int i = 0; i < missiones.triple_size(); ++i)
	{
		unsigned curmid = missiones.triple(i).id();
		unsigned pre = missiones.triple(i).pre();

		m_mapPreMission[pre].insert(curmid);

		missionpair = make_pair(mission_condition_triple, i);
		m_mapMissonIndex[curmid] = missionpair;
	}

	for(int i = 0; i < missiones.assemble_size(); ++i)
	{
		unsigned curmid = missiones.assemble(i).id();
		unsigned pre = missiones.assemble(i).pre();

		m_mapPreMission[pre].insert(curmid);

		missionpair = make_pair(mission_condition_assemble, i);
		m_mapMissonIndex[curmid] = missionpair;
	}

	//建筑配置文件映射
	for(int i = 0; i < buildings.m_config.buildings_size(); ++i)
	{
		unsigned bid = buildings.m_config.buildings(i).id();

		m_mapBuildIndex.insert(make_pair(bid, i));
	}

	//黄钻等级映射
	const VipGiftConfig::PrivilegeGift & privilege = vipgift.m_config.yellowvip().privilege();
	for(int i = 0; i < privilege.leveldaily_size(); ++i)
	{
		unsigned level = privilege.leveldaily(i).level();
		m_mapVipLevelIndex[level] = i;
	}

	//集市中资源类型与索引的映射关系
	for(int i = 0; i < marketcfg.m_config.market_size(); ++i)
	{
		unsigned type = marketcfg.m_config.market(i).type();
		m_mapTypeIndex[type] = i;
	}

	//据点奖励，时间与下标的映射关系
	for(int i = 0; i < worldreward.m_config.stronghold().timemultiple_size(); ++i)
	{
		unsigned hour = worldreward.m_config.stronghold().timemultiple(i).time();

		m_mapHourIndex[hour] = i;
	}

	//政务事件id映射
	for(int i = 0; i < governaffairs.m_config.govern_affairs_size(); ++i)
	{
		unsigned id = governaffairs.m_config.govern_affairs(i).id();

		m_afairid[id] = i;
	}

	//套装前置eqid映射
	for(int i = 0; i < equipsuit.m_config.suitequip_size(); ++i)
	{
		unsigned preeqid = equipsuit.m_config.suitequip(i).preeqid();

		m_preeqidIndex[preeqid] = i;
	}

	//定制装备的映射
	for(int i = 0; i < specailequip.m_config.specialequip_size(); ++i)
	{
		unsigned eqid = specailequip.m_config.specialequip(i).eqid();
		specialIndex[eqid] = i;
	}

	//活动事件中,一维,id和二维的映射
	for(int i = 0; i < npcactivity.m_config.activity_affairs_size(); ++i)
	{
		for(int j = 0; j < npcactivity.m_config.activity_affairs(i).affairs_size(); ++j)
		{
			unsigned id = npcactivity.m_config.activity_affairs(i).affairs(j).id();
			dayAffaiIndex[id].first = i;
			dayAffaiIndex[id].second = j;
		}
	}

	//迷雾战关卡id和下标映射
	for(int i = 0; i < foggate.m_config.foggates_size(); ++i)
	{
		unsigned gateid = foggate.m_config.foggates(i).gateid();
		foggateIndex[gateid] = i;
	}

	//每日任务，需要双重映射
	for(int i = 0; i < dailymissions.m_config.daily_missions_size(); ++i)
	{
		for(int j = 0; j < dailymissions.m_config.daily_missions(i).missions_size(); ++j)
		{
			unsigned id = dailymissions.m_config.daily_missions(i).missions(j).id();
			dailymissionIndex[id].first = i;
			dailymissionIndex[id].second = j;
		}
	}

	//成就id和下标的映射
	for(int i = 0; i < achievements.m_config.achievements_size(); ++i)
	{
		unsigned id = achievements.m_config.achievements(i).id();
		achieveidIndex[id] = i;

		unsigned type = achievements.m_config.achievements(i).type();

		achieveTypeRelate[type].push_back(id);
	}

	//部件id和下标映射
	for(int i = 0; i < component.m_config.component().component_base_size(); ++i)
	{
		unsigned compid = component.m_config.component().component_base(i).compid();
		componentIndex[compid] = i;
	}

	//资源副本id与下标映射
	for(int i = 0; i < resource_copy.m_config.resource_copies_size(); ++i)
	{
		unsigned id = resource_copy.m_config.resource_copies(i).id();
		copyIndex[id] = i;
	}

	//剧本战
	for(int i = 0; i < operobattle.m_config.battle_rewards_size(); ++i)
	{
		unsigned gateid = operobattle.m_config.battle_rewards(i).id();
		operabattleIndex[gateid] = i;
	}

	//试炼
	for(int i = 0; i < modeltrial.m_config.gates_size(); ++i)
	{
		unsigned gateid = modeltrial.m_config.gates(i).id();
		trialIndex[gateid] = i;
	}

	for(int i = 0; i < crossbusiness.m_config.open_platform_shop_size(); ++i)
	{
		const CrossBusinessConfig::OpenPlatformSlots& plat_cfg = crossbusiness.m_config.open_platform_shop(i);

		for(int j = 0; j < plat_cfg.slots_size(); ++j)
		{
			unsigned id = plat_cfg.slots(j).id();

			businessIndex[id].first = i;
			businessIndex[id].second = j;
		}
	}

	for(int i=0;i<heroInfo.m_config.heroes_size();++i)
	{
		m_heroInfo[heroInfo.m_config.heroes(i).heroid()] = i;
		for(unsigned j=DemoGType_1;j<=DemoGType_4;++j)
		{
			unsigned k=0;
			switch(j)
			{
			case DemoGType_1:
				for(;k<heroInfo.m_config.heroes(i).tacticalarea1_size();++k)
					m_heroShape[heroInfo.m_config.heroes(i).heroid()][j].insert(heroInfo.m_config.heroes(i).tacticalarea1(k));
				break;
			case DemoGType_2:
				for(;k<heroInfo.m_config.heroes(i).tacticalarea2_size();++k)
					m_heroShape[heroInfo.m_config.heroes(i).heroid()][j].insert(heroInfo.m_config.heroes(i).tacticalarea2(k));
				break;
			case DemoGType_3:
				for(;k<heroInfo.m_config.heroes(i).tacticalarea3_size();++k)
					m_heroShape[heroInfo.m_config.heroes(i).heroid()][j].insert(heroInfo.m_config.heroes(i).tacticalarea3(k));
				break;
			case DemoGType_4:
				for(;k<heroInfo.m_config.heroes(i).tacticalarea4_size();++k)
					m_heroShape[heroInfo.m_config.heroes(i).heroid()][j].insert(heroInfo.m_config.heroes(i).tacticalarea4(k));
				break;
			default:
				break;
			}
		}
		for(unsigned j=0;j<heroInfo.m_config.heroes(i).giftarea_size();++j)
			m_heroG[heroInfo.m_config.heroes(i).heroid()].insert(heroInfo.m_config.heroes(i).giftarea(j));
	}

	for(int i=0;i<npc.m_config.npc_size();++i)
	{
		m_npcInfo[npc.m_config.npc(i).npcid()] = i;
		for(unsigned j=DemoGType_1;j<=DemoGType_4;++j)
		{
			unsigned k=0;
			switch(j)
			{
			case DemoGType_1:
				for(;k<npc.m_config.npc(i).tacticalarea1_size();++k)
					m_npcShape[npc.m_config.npc(i).npcid()][j].insert(npc.m_config.npc(i).tacticalarea1(k));
				break;
			case DemoGType_2:
				for(;k<npc.m_config.npc(i).tacticalarea2_size();++k)
					m_npcShape[npc.m_config.npc(i).npcid()][j].insert(npc.m_config.npc(i).tacticalarea2(k));
				break;
			case DemoGType_3:
				for(;k<npc.m_config.npc(i).tacticalarea3_size();++k)
					m_npcShape[npc.m_config.npc(i).npcid()][j].insert(npc.m_config.npc(i).tacticalarea3(k));
				break;
			case DemoGType_4:
				for(;k<npc.m_config.npc(i).tacticalarea4_size();++k)
					m_npcShape[npc.m_config.npc(i).npcid()][j].insert(npc.m_config.npc(i).tacticalarea4(k));
				break;
			default:
				break;
			}
		}
		for(unsigned j=0;j<npc.m_config.npc(i).giftarea_size();++j)
			m_npcG[npc.m_config.npc(i).npcid()].insert(npc.m_config.npc(i).giftarea(j));
	}

	for(int i=0;i<demo.m_config.normalnpc_size();++i)
		m_normalNPC[demo.m_config.normalnpc(i).day()] = demo.m_config.normalnpc(i).npcid();
	for(int i=0;i<demo.m_config.attacknpc_size();++i)
		m_attackNPC[demo.m_config.attacknpc(i).day()] = demo.m_config.attacknpc(i).npcid();
	for(int i=0;i<demo.m_config.defendnpc_size();++i)
		m_defendNPC[demo.m_config.defendnpc(i).day()] = demo.m_config.defendnpc(i).npcid();
	m_battleRewardR = 0;
	for(int i=0;i<demo.m_config.battlereward_size();++i)
	{
		m_battleRewardR += demo.m_config.battlereward(i).r();
		for(int j=0;j<demo.m_config.battlereward(i).count_size();++j)
			m_battleReward[i][demo.m_config.battlereward(i).count(j).day()] = demo.m_config.battlereward(i).count(j).c();
	}
	memset(m_cityRewardR, 0, sizeof(m_cityRewardR));
	for(int i=0;i<demo.m_config.cityreward_size();++i)
	{
		for(int j=0;j<demo.m_config.cityreward(i).r_size();++j)
			m_cityRewardR[i] += demo.m_config.cityreward(i).r(j);
		for(int j=0;j<demo.m_config.cityreward(i).npc_size();++j)
		{
			for(int k=0;k<demo.m_config.cityreward(i).npc(j).npc_size();++k)
				m_cityNPC[i][demo.m_config.cityreward(i).npc(j).day()].push_back(demo.m_config.cityreward(i).npc(j).npc(k));
		}
	}


	for(int i=0;i<demo.m_config.city_size();++i)
	{
		m_cityG[demo.m_config.city(i).cid()] = demo.m_config.city(i).gid();
		m_cityS[demo.m_config.city(i).cid()] = demo.m_config.city(i).scale();
	}

	for(int i=0;i<sciences.m_config.sciences_size();++i)
		m_ScienceInfo[sciences.m_config.sciences(i).id()] = i;

	for (int i = 0; i < weapon.m_config.weapons_size(); ++i)
	{
		m_weapon_index[weapon.m_config.weapons(i).id()] = i;

		for (int k = 0; k < weapon.m_config.weapons(i).lvls_size(); ++k)
		{
			unsigned weapon_id = weapon.m_config.weapons(i).id();
			unsigned level = weapon.m_config.weapons(i).lvls(k).lvl();
			m_weapon_lvl_index[weapon_id].insert(std::make_pair(level, k));
		}
	}

	for (int i = 0; i < passSystem.m_config.all_upc_pass_size(); ++i)
	{
		m_pass_index[passSystem.m_config.all_upc_pass(i).id()] = i;
	}

	for(int i=0;i<activity.m_config.act_size();++i)
		m_actmap[activity.m_config.act(i).id()] = i;

	for(int i=0;i<bot.m_config.account_size();++i)
		m_botAccount[bot.m_config.account(i).id()] = i;
	for(int i=0;i<bot.m_config.name_size();++i)
		m_botName[make_pair(bot.m_config.name(i).id(), bot.m_config.name(i).kingdom())] = i;
}
const Hero::HeroInfo& ConfigManager::GetHero(unsigned id)
{
	if(m_heroInfo.count(id))
		return heroInfo.m_config.heroes(m_heroInfo[id]);
	return heroInfo.m_config.heroes(m_heroInfo.begin()->second);
}
const NPC::NPCInfo& ConfigManager::GetNPC(unsigned id)
{
	if(m_npcInfo.count(id))
		return npc.m_config.npc(m_npcInfo[id]);
	return npc.m_config.npc(m_npcInfo.begin()->second);
}
unsigned ConfigManager::GetNPCID(unsigned day, unsigned type)
{
	if(type != e_normal_npc && type != e_attack_npc && type != e_defend_npc)
		return m_normalNPC.begin()->second;
	map<unsigned, unsigned>& t = type==e_normal_npc?m_normalNPC:(type==e_attack_npc?m_attackNPC:m_defendNPC);
	if(!t.count(day))
	{
		t[day] = 0;
		map<unsigned, unsigned>::iterator it = t.find(day);
		++it;
		if(it == t.end())
		{
			--it;
			--it;
		}
		t[day] = it->second;
	}
	return t[day];
}
unsigned ConfigManager::GetBattleRewardCount(unsigned t, unsigned d)
{
	if(!m_battleReward[t].count(d))
	{
		m_battleReward[t][d] = 0;
		map<unsigned, unsigned>::iterator it = m_battleReward[t].find(d);
		++it;
		if(it  == m_battleReward[t].end())
		{
			--it;
			--it;
		}
		m_battleReward[t][d] = it->second;
	}
	return m_battleReward[t][d];
}
unsigned ConfigManager::GetBattleRewardType()
{
	unsigned r = Math::GetRandomInt(m_battleRewardR);
	unsigned s = 0;
	for(int i=0;i<demo.m_config.battlereward_size();++i)
	{
		s += demo.m_config.battlereward(i).r();
		if(r < s)
			return i;
	}
	return 0;
}
unsigned ConfigManager::GetCityRewardCount(unsigned id, unsigned t)
{
	if(id < e_city_sacle_1 || id > e_city_sacle_4 || t > e_city_reward_type_set_3)
		throw runtime_error("id or t error");
	--id;
	return demo.m_config.cityreward(id).c(t);
}
unsigned ConfigManager::GetCityRewardType(unsigned id)
{
	if(id < e_city_sacle_1 || id > e_city_sacle_4)
		return e_city_reward_type_empty;
	--id;
	unsigned r = Math::GetRandomInt(m_cityRewardR[id]);
	unsigned s = 0;
	for(int i=0;i<demo.m_config.cityreward(id).r_size();++i)
	{
		s += demo.m_config.cityreward(id).r(i);
		if(r < s)
			return i;
	}
	return e_city_reward_type_empty;
}
const vector<unsigned>& ConfigManager::GetCityNPC(unsigned id, unsigned d)
{
	if(id < e_city_sacle_1 || id > e_city_sacle_4)
		throw runtime_error("id error");
	--id;
	if(!m_cityNPC[id].count(d))
	{
		vector<unsigned> temp;
		m_cityNPC[id][d] = temp;
		map<unsigned, vector<unsigned> >::iterator it = m_cityNPC[id].find(d);
		++it;
		if(it == m_cityNPC[id].end())
		{
			--it;
			--it;
		}
		m_cityNPC[id][d] = it->second;
	}
	return m_cityNPC[id][d];
}

unsigned ConfigManager::GetGid(uint16_t cid)
{
	if(!m_cityG.count(cid))
		return DemoGType_1;
	return m_cityG[cid];
}
unsigned ConfigManager::GetScale(uint16_t cid)
{
	if(!m_cityS.count(cid))
		return e_city_sacle_1;
	return m_cityS[cid];
}

bool ConfigManager::IsHeroStrengthShape(unsigned id, unsigned g, unsigned s)
{
	if(!m_heroShape.count(id)
	|| !m_heroShape[id].count(g)
	|| !m_heroShape[id][g].count(s))
		return false;
	return true;
}
bool ConfigManager::IsNPCStrengthShape(unsigned id, unsigned g, unsigned s)
{
	if(!m_npcShape.count(id)
	|| !m_npcShape[id].count(g)
	|| !m_npcShape[id][g].count(s))
		return false;
	return true;
}
bool ConfigManager::IsHeroG(unsigned id, unsigned g)
{
	if(!m_heroG.count(id)
	|| !m_heroG[id].count(g))
		return false;
	return true;
}
bool ConfigManager::IsNPCG(unsigned id, unsigned g)
{
	if(!m_npcG.count(id)
	|| !m_npcG[id].count(g))
		return false;
	return true;
}
const ScienceConfig::ScienceItem& ConfigManager::GetScience(unsigned id)
{
	if(m_ScienceInfo.count(id))
		return sciences.m_config.sciences(m_ScienceInfo[id]);
	return sciences.m_config.sciences(m_ScienceInfo.begin()->second);
}

bool ConfigManager::GetActivity(unsigned id, User::ActivityItem& act)
{
	if(m_actmap.count(id))
	{
		act = activity.m_config.act(m_actmap[id]);
		return true;
	}
	return false;
}
unsigned ConfigManager::GetKillReward(unsigned level)
{
	if(level > demo.m_config.killreward_size() || level == 0)
		return demo.m_config.killreward(demo.m_config.killreward_size()-1);
	return demo.m_config.killreward(level-1);
}

int ConfigManager::GetBotIndex(unsigned id, unsigned day)
{
	if(!m_botAccount.count(id))
		return -1;

	int index = -1;
	for(int i=0;i<bot.m_config.account(m_botAccount[id]).player_size();++i)
	{
		if(day <= bot.m_config.account(m_botAccount[id]).player(i).day())
		{
			index = i;
			break;
		}
	}
	if(index == -1)
		index = bot.m_config.account(m_botAccount[id]).player_size() - 1;
	return index;
}
int ConfigManager::NeedChangeBotAccount(unsigned id, unsigned day1, unsigned day2)
{
	if(!m_botAccount.count(id) || day1 == day2)
		return -1;

	int index1 = -1, index2 = -1;

	for(int i=0;i<bot.m_config.account(m_botAccount[id]).player_size();++i)
	{
		if(day1 <= bot.m_config.account(m_botAccount[id]).player(i).day())
		{
			index1 = i;
			break;
		}
	}
	if(index1 == -1)
		index1 = bot.m_config.account(m_botAccount[id]).player_size() - 1;

	for(int i=0;i<bot.m_config.account(m_botAccount[id]).player_size();++i)
	{
		if(day2 <= bot.m_config.account(m_botAccount[id]).player(i).day())
		{
			index2 = i;
			break;
		}
	}
	if(index2 == -1)
		index2 = bot.m_config.account(m_botAccount[id]).player_size() - 1;

	return index1 != index2 ? index2 : -1;
}
const BotConfig::BotPlayer& ConfigManager::GetBotAccount(unsigned id, int index)
{
	return bot.m_config.account(m_botAccount[id]).player(index);
}
string ConfigManager::GetBotName(unsigned id, unsigned kingdom, unsigned serverid)
{
	string name;
	pair<unsigned, unsigned> key = make_pair(id, kingdom);
	if(m_botName.count(key) && bot.m_config.name(m_botName[key]).name_size())
		name = bot.m_config.name(m_botName[key]).name(serverid % bot.m_config.name(m_botName[key]).name_size());
	return name;
}
string ConfigManager::GetBotChat()
{
	string chat;
	if(bot.m_config.chat_size())
		chat = bot.m_config.chat(Math::GetRandomInt(bot.m_config.chat_size()));
	return chat;
}
