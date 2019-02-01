/*
 * DataXML3.cpp
 *
 *  Created on: 2016-11-15
 *      Author: Ralf
 */

#include "DataInc.h"
#include <math.h>
#include "OpenPlatform.h"
#include "IOpenPlatform.h"
#include "DataXmlUnit.h"
#include <stdexcept>



bool GiftEquipment::CopyFromJson(const Json::Value& jsonEquips)
{
	do
	{
		if (! Json::GetInt(jsonEquips, "id", id))
		{
			break;
		}

		if (! Json::GetInt(jsonEquips, "c", cnt))
		{
			break;
		}

		if (! Json::GetInt(jsonEquips, "q", quality))
		{
			break;
		}

		Json::GetInt(jsonEquips, "ch", ch);

		return true;

	} while (0);

	id = 0;
	cnt = 0;
	quality = 0;
	ch = 0;

	return false;
}

GiftEquipItem::GiftEquipItem()
	: m_nId(0)
	,m_nCnt(0)
	,m_nQuality(0)
	,m_nCh(0)
	,m_bIsHero(false)
{

}


GiftEquipItem::GiftEquipItem(const Json::Value& jsonEquips, bool ishero)
	: m_nId(0)
	,m_nCnt(1)
	,m_nQuality(0)
	,m_nCh(0)
	,m_bIsHero(ishero)
{
	if (! Json::GetUInt(jsonEquips, "id", m_nId))
	{
		throw std::runtime_error("Equip_config_need_id");
	}

	Json::GetUInt(jsonEquips, "c", m_nCnt);
	Json::GetUInt(jsonEquips, "q", m_nQuality); //强化等级
	Json::GetUInt(jsonEquips, "ch", m_nCh);  //品质
}


bool GiftEquipItem::IsHero() const
{
	return (m_nId > 0 &&  m_bIsHero);
}

bool GiftEquipItem::IsEquip() const
{
	return (m_nId > 0 &&  (!m_bIsHero));
}

bool GiftEquipItem::IsSame(GiftEquipItem & othitem)
{
	if (m_bIsHero == othitem.m_bIsHero && m_nId == othitem.m_nId)
	{
		return true;
	}

	return false;
}

void GiftEquipItem::Double()
{
	m_nCnt *= 2;
}

//-----------------------------------------------------------

CDataXML::CDataXML()
{
	m_init = false;
}

CDataXML::~CDataXML()
{
}

unsigned CDataXML::Str2Hero(string& str)
{
	return CTrans::STOI(str.substr(1).c_str());
}
string CDataXML::Hero2Str(unsigned id)
{
	return string("H").append(CTrans::UTOS(id));
}

CDataXML* CDataXML::GetInitXML()
{
	if(!m_pData)
	{
		m_pData = new CDataXML;
		string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
		if (dataPath.empty())
		{
			return NULL;
		}
		int ret = m_pData->Init(dataPath,sem_xml,true);
		if(ret)
		{
			delete m_pData;
			return NULL;
		}
	}
	return m_pData;
}
CDataXML* CDataXML::GetCDataXML()
{
	if(!m_pData)
	{
		m_pData = new CDataXML;
		string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
		if (dataPath.empty())
		{
			error_log("Init data fail!");
			return NULL;
		}

		int ret = m_pData->Init(dataPath,sem_xml);
		if (0 != ret)
		{
			error_log("Init data fail!");
			delete m_pData;
			m_pData = NULL;
		}
	}
	return m_pData;
}

int CDataXML::Init(const std::string &path, semdat sem, bool initconfig)
{
	if(m_init)
	{
		return 0;
	}
	if (path.empty())
	{
		error_log("[init_DataXML_data_fail][path=%s]", path.c_str());
		return R_ERROR;
	}

	int semgroup = 0;
	int semserver = 0;
	string mapfile;

#define INIT_XML_DAT(name) \
	mapfile = path; \
	if (path[path.length() - 1] != '/') \
		mapfile.append("/"); \
	mapfile.append(#name).append(".xmldat"); \
	if(!m_sh##name.CreateOrOpen(mapfile.c_str(), sizeof(DataXML##name), SEM_ID(sem,semgroup,semserver),LOCK_MAX)) \
	{ \
		error_log("[init_DataXML_data_fail][path=%s]", mapfile.c_str()); \
		return R_ERROR; \
	} \
	if(!initconfig) \
	{ \
		CAutoLock lock##name(&(m_sh##name), true); \
		if(!m_sh##name.HasInit()) \
		{ \
			/*********
			DataXML##name *pdata = (DataXML##name *)m_sh##name.GetAddress(); \
			memset(pdata, 0, sizeof(*pdata)); \
			m_sh##name.SetInitDone(); \
			************/ \
			error_log("[DataXML_no_data][path=%s]", mapfile.c_str()); \
			return R_ERROR; \
		} \
	} \

	INIT_XML_DAT(Building)
	INIT_XML_DAT(Hero)
	INIT_XML_DAT(MixHero)
	INIT_XML_DAT(VIP)
	INIT_XML_DAT(sggiftbagconfig)
	INIT_XML_DAT(EquipSub)
	INIT_XML_DAT(Boats)
	INIT_XML_DAT(Hammer)
	INIT_XML_DAT(TreasureHunt)
	INIT_XML_DAT(equipintensifys)
	INIT_XML_DAT(olequipset)
	INIT_XML_DAT(Shop)
	INIT_XML_DAT(WorldBattleShop)
	INIT_XML_DAT(RankBattleShop)
	INIT_XML_DAT(HufuShop)
	INIT_XML_DAT(Equipment)
	INIT_XML_DAT(newlottery)
	INIT_XML_DAT(choujiang)
	INIT_XML_DAT(ActReward)
	INIT_XML_DAT(GateReward)
	INIT_XML_DAT(QuestReward)
	INIT_XML_DAT(HeavenDaoist)
	INIT_XML_DAT(CostHeavenDaoist)
	INIT_XML_DAT(Double11)
	INIT_XML_DAT(BetShop)
	INIT_XML_DAT(Barbar)
	INIT_XML_DAT(FiveTiger)
	INIT_XML_DAT(sgsigninnewconfig)
	INIT_XML_DAT(sginvitegiftconfig)
	INIT_XML_DAT(partpowerconfig)
	INIT_XML_DAT(PreSummer)
	INIT_XML_DAT(NewJueshiWS)
	INIT_XML_DAT(Opporknock)
	INIT_XML_DAT(FortunatelyAgain)
	INIT_XML_DAT(RechargeOptional)
	INIT_XML_DAT(NewRecharge)
	INIT_XML_DAT(GroupBuyDaily)
	INIT_XML_DAT(LittleRecharge)
	INIT_XML_DAT(Temple)
	INIT_XML_DAT(SoldierTrainAndUp)
	INIT_XML_DAT(HeavenDaoSkill)
	INIT_XML_DAT(TurnPlate)
	INIT_XML_DAT(MonthGiftBag)
	INIT_XML_DAT(CombinedShop)
	INIT_XML_DAT(NewerAdvance)
	INIT_XML_DAT(FashionShop)
	INIT_XML_DAT(HouHuiYouQi)
	INIT_XML_DAT(ChaoZhiZheKou)
	INIT_XML_DAT(YueHuiJuXian)
	INIT_XML_DAT(LimitBuyOfZone)
	INIT_XML_DAT(FiveDefendGrow)
	INIT_XML_DAT(CountryDay)
	INIT_XML_DAT(WuxingPearl)
	INIT_XML_DAT(HeartbeatBigSale)
	INIT_XML_DAT(FiveShop)
	INIT_XML_DAT(JueXingTeHui)
	INIT_XML_DAT(FreeExchange)
	INIT_XML_DAT(DoubleEleven)
	INIT_XML_DAT(JuBaoXia)
	INIT_XML_DAT(HeavenStep)
	INIT_XML_DAT(DaoistStep)
	INIT_XML_DAT(ZhenBaoGeHero)
	INIT_XML_DAT(ZhenBaoGeBuilding)
	INIT_XML_DAT(HeroStoneStep)
	INIT_XML_DAT(BuildingStoneStep)
	INIT_XML_DAT(GrowDevelop)
	INIT_XML_DAT(TreasureHuntExchange)
	INIT_XML_DAT(DailyCharge)
	INIT_XML_DAT(TreasureBox)
	INIT_XML_DAT(Christmas)
	INIT_XML_DAT(Keepsake)
	INIT_XML_DAT(PointExchange)
	INIT_XML_DAT(ChargeFeedback)
	INIT_XML_DAT(CelebrateNewYear)
	INIT_XML_DAT(BuildingSkin)
	INIT_XML_DAT(TutorLogin)
	INIT_XML_DAT(ImperialGift)
	INIT_XML_DAT(TimeLimitUpgrade)
	INIT_XML_DAT(YearFortune)
	INIT_XML_DAT(HequActivity)
	INIT_XML_DAT(AncientScroll)
	INIT_XML_DAT(ProtectFlag)
	INIT_XML_DAT(ProtectGoddess)
	INIT_XML_DAT(Catapult)
	INIT_XML_DAT(CostCatapult)
	INIT_XML_DAT(CatapultSkill)
	INIT_XML_DAT(ChongZhiZiXuan)
	INIT_XML_DAT(Beauty)
	INIT_XML_DAT(Investment)
	INIT_XML_DAT(EightFormation)
	INIT_XML_DAT(CostEightFormation)
	INIT_XML_DAT(BirdBridge)
	INIT_XML_DAT(UnionTech)
	INIT_XML_DAT(ShengDan)
	if(!initconfig)
	{
		//building map
		{
			CAutoLock lock(const_cast<CShareMemory *>(&(m_shBuilding)), true);
			DataXMLBuilding *pdata = (DataXMLBuilding *)m_shBuilding.GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}
			for(unsigned i=0;i<XML_BUILDING_NUM;++i)
			{
				if(pdata->build[i].t == 0 || pdata->build[i].lv == 0)
					break;
				m_mapBuilding[make_pair(pdata->build[i].t, pdata->build[i].lv)] = i;
			}
		}
		//hero map
		{
			CAutoLock lock(const_cast<CShareMemory *>(&(m_shHero)), true);
			DataXMLHero *pdata = (DataXMLHero *)m_shHero.GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}
			unsigned sumrate[XML_HERO_RATE];
			memset(sumrate,0,sizeof(sumrate));
			unsigned sum = 0;

			for(unsigned i=0;i<XML_HERO_NUM;++i)
			{
				m_mapXMLHero[pdata->xmlhero[i].id] = i;

				for(unsigned m=0;m<XML_HERO_STAR;++m)
				{
					for(unsigned k=0;k<XML_HERO_RATE;++k)
					{
						for(unsigned l=0;l<pdata->xmlhero[i].rate[m][k];++l)
						{
							m_mapXMLHeroRate[k][sumrate[k]] = pair<unsigned, unsigned>(i,m+1);
							++sumrate[k];
						}
						if(k == XML_HERO_RATE - 2 && pdata->xmlhero[i].type >= 4)
						{
							for(unsigned l=0;l<pdata->xmlhero[i].rate[m][k];++l)
							{
								m_mapXMLHeroRatePurple[sum] = pair<unsigned, unsigned>(i,m+1);
								++sum;
							}
						}
					}
				}
			}
		}
		// boat map
		{
			CAutoLock lock(const_cast<CShareMemory *>(&(m_shBoats)), true);
			DataXMLBoats *pdata = (DataXMLBoats *)m_shBoats.GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}
			m_vBoat.clear();
			unsigned sumrate = 0;
			m_mapBoatType.clear();
			for(size_t i = 0; i < XML_BOATS_COUNT; ++i)
			{
				m_vBoat.push_back(pdata->boats[i]);
				for(unsigned l=0;l<pdata->boats[i].rate;++l)
				{
					m_mapBoatType[sumrate] = pdata->boats[i].id;
					++sumrate;
				}
			}
		}
		// hammer map
		{
			CAutoLock lock(const_cast<CShareMemory *>(&(m_shHammer)), true);
			DataXMLHammer *pdata = (DataXMLHammer *)m_shHammer.GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}
			m_mapHammer.clear();
			for(size_t i = 0; i < XML_HAMMER_COUNT; ++i) {
				uint32_t hammerId = pdata->hammers[i].type;
				Hammer hammer;
				for(size_t idx = 0; idx < HAMMER_ITEM_NUM; ++idx){
					uint32_t id = pdata->hammers[i].items[idx].id;
					int rate = pdata->hammers[i].items[idx].rate;
					if(id == 0){
						break;
					}
					hammer.items.push_back(HammerItem(id, rate));
					hammer.total_rate += rate;
				}
				m_mapHammer[hammerId] = hammer;
			}

			m_mapHammerAllServer.clear();
			for(size_t i = 0; i < XML_HAMMER_COUNT; ++i) {
				uint32_t hammerId = pdata->hammersAllServer[i].type;
				Hammer hammer;
				for(size_t idx = 0; idx < HAMMER_ITEM_NUM; ++idx){
					uint32_t id = pdata->hammersAllServer[i].items[idx].id;
					int rate = pdata->hammersAllServer[i].items[idx].rate;
					if(id == 0){
						break;
					}
					hammer.items.push_back(HammerItem(id, rate));
					hammer.total_rate += rate;
				}
				m_mapHammerAllServer[hammerId] = hammer;
			}
		}
		//invite map
		{
			CAutoLock lock(const_cast<CShareMemory*>(&(m_shsginvitegiftconfig)), true);

			DataXMLsginvitegiftconfig *pdata
				= (DataXMLsginvitegiftconfig*)m_shsginvitegiftconfig.GetAddress();
			if (NULL == pdata)
			{
				return R_ERR_DB;
			}

			for (int i = 0; i < XML_INVITE_LEVEL_ITEMS_MAX; ++i)
			{
				if (0 != pdata->levelItems[i].id)
				{
					m_mapXMLInvite[pdata->levelItems[i].id] = i;
				}
				else
				{
					break;
				}
			}
		}
		//giftbag map
		{
			CAutoLock lock(const_cast<CShareMemory *>(&(m_shsggiftbagconfig)), true);

			DataXMLsggiftbagconfig *pdata = (DataXMLsggiftbagconfig *)m_shsggiftbagconfig.GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}

			for(int i=0;i<DATA_GIFT_MAX;++i)
			{
				if(pdata->GiftBag[i].id != 0)
				{
					m_mapXMLGiftBag[pdata->GiftBag[i].id] = i;
					if(pdata->GiftBag[i].gift[0].rate != 0)
					{
						vector<int> rate;
						rate.clear();
						int sum_rate = 0;
						for(int j=0;j<XML_GIFT_MAX;++j)
						{
							if(pdata->GiftBag[i].gift[j].rate == 0)
							{
								break;
							}

							if(pdata->GiftBag[i].gift[j].rate != 0)
							{
								sum_rate += pdata->GiftBag[i].gift[j].rate;
								rate.push_back(sum_rate);
							}
						}
						m_mapXMLGiftBagRate[pdata->GiftBag[i].id] = rate;
					}
				}
			}
		}
		//武魂
		{
			CAutoLock lock(const_cast<CShareMemory *>(&(m_shpartpowerconfig)), true);

			DataXMLpartpowerconfig *pData
						= (DataXMLpartpowerconfig *)m_shpartpowerconfig.GetAddress();
			if (NULL == pData)
			{
				return R_ERR_DB;
			}

			for (int i = 0; i < XML_WEAPON_SOUL_ITEMS_MAX; ++i)
			{
				if (pData->items[i].id == 0)
				{
					break;
				}

				m_mapWeaponSoulCost[pData->items[i].id] = i;
			}
		}
		//equip sub map
		{
			CAutoLock lock(const_cast<CShareMemory *>(&(m_shEquipSub)), true);

			DataXMLEquipSub *pdata = (DataXMLEquipSub *)m_shEquipSub.GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}

			unsigned k = 0;
			m_mapEquipSub.clear();
			m_mapEquipSubItem.clear();
			for(k=0;k<XML_EQUIP_SUB_LEVEL;++k)
			{
				if(pdata->sub[k].start && pdata->sub[k].end)
				{
					EquipSubLevel lvlkey(pdata->sub[k].id,pdata->sub[k].start,pdata->sub[k].end,pdata->sub[k].stone,pdata->sub[k].gold);
					unsigned lvlsum = 0, j = 0;
					for(j=0;j<XML_EQUIP_SUB_ITEM_S;++j)
					{
						unsigned subsum = 0, m = 0;
						if(pdata->sub[k].subs[j].id[0])
						{
							EquipSubItem subkey(pdata->sub[k].start,pdata->sub[k].end,pdata->sub[k].subs[j].id);
							for(m=0;m<pdata->sub[k].subs[j].rate;++m)
							{
								m_mapEquipSub[lvlkey][lvlsum] = pdata->sub[k].subs[j].id;
								++lvlsum;
							}
							for(m=0;m<XML_EQUIP_SUB_ITEM;++m)
							{
								EquipSub eqsub(pdata->sub[k].subs[j].items[m].star,pdata->sub[k].subs[j].items[m].value,pdata->sub[k].subs[j].id);
								unsigned n = 0;
								for(n=0;n<pdata->sub[k].subs[j].items[m].rate;++n)
								{
									m_mapEquipSubItem[subkey][subsum] = eqsub;
									++subsum;
								}
								m_mapEquipSubValue[lvlkey][string(pdata->sub[k].subs[j].id)][pdata->sub[k].subs[j].items[m].star] = pdata->sub[k].subs[j].items[m].value;
								m_mapEquipSubStar[lvlkey][string(pdata->sub[k].subs[j].id)][pdata->sub[k].subs[j].items[m].value] = pdata->sub[k].subs[j].items[m].star;
							}
						}
					}
				}
			}
		}
		//TreasureHunt
		{
			CAutoLock lock(const_cast<CShareMemory *>(&(m_shTreasureHunt)), true);

			DataXMLTreasureHunt *pdata = (DataXMLTreasureHunt *)m_shTreasureHunt.GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}

			unsigned k = 0, j = 0, l = 0;
			map<unsigned,TreasureHuntItem> temp;
			m_mapTreasureHunt.clear();
			for(k=0;k<XML_TREASURE_HUNT;++k)
			{
				if(pdata->item[k].id)
					temp[k] = pdata->item[k];
			}
			for(map<unsigned,TreasureHuntItem>::iterator it=temp.begin();it!=temp.end();++it)
			{
				unsigned sum = 0, zero = 0, temprate = 0, sumrate = 0;
				vector<pair<unsigned,unsigned> > rate;
				map<unsigned,TreasureHuntItem>::iterator iter = it;
				for(j=0;j<XML_TREASURE_RAND;++j)
				{
					++iter;
					if(iter == temp.end())
						iter = temp.begin();
					sum += iter->second.rate;
					rate.push_back(pair<unsigned,unsigned>(iter->first, iter->second.rate));
					if(iter->second.rate == 0)
						++zero;
				}
				if(zero)
					temprate = (XML_TREASURE_RATE - sum) / zero;
				for(j=0;j<XML_TREASURE_RAND;++j)
				{
					if(rate[j].second == 0)
						rate[j].second  = temprate;
					for(l=0;l<rate[j].second;++l)
					{
						m_mapTreasureHunt[it->first][sumrate] = rate[j].first;
						++sumrate;
					}
				}
			}
		}
		//payrank lottery
		{
			unsigned sumrate[PAYRANK_LEVEL] = {0};
			for(unsigned i=0;i<PAYRANK_COUNT;++i)
			{
				int min = sumrate[0];
				int max = level_1[i].rate + sumrate[0];
				for(unsigned j=min; j<max; ++j)
				{
					m_mapPayrank[0][j] = i;
				}
				sumrate[0] += level_1[i].rate;
			}
			for(unsigned i=0;i<PAYRANK_COUNT;++i)
			{
				int min = sumrate[1];
				int max = level_2[i].rate + sumrate[1];
				for(unsigned j=min; j<max; ++j)
				{
					m_mapPayrank[1][j] = i;
				}
				sumrate[1] += level_2[i].rate;
			}
			for(unsigned i=0;i<PAYRANK_COUNT;++i)
			{
				int min = sumrate[2];
				int max = level_3[i].rate + sumrate[2];
				for(unsigned j=min; j<max; ++j)
				{
					m_mapPayrank[2][j] = i;
				}
				sumrate[2] += level_3[i].rate;
			}
		}
		//4399payrank lottery
		{
			unsigned sumrate[PAYRANK_LEVEL] = {0};
			for(unsigned i=0;i<PAYRANK_COUNT;++i)
			{
				int min = sumrate[0];
				int max = level_4_1[i].rate + sumrate[0];
				for(unsigned j=min; j<max; ++j)
				{
					m_map4Payrank[0][j] = i;
				}
				sumrate[0] += level_4_1[i].rate;
			}
			for(unsigned i=0;i<PAYRANK_COUNT;++i)
			{
				int min = sumrate[1];
				int max = level_4_2[i].rate + sumrate[1];
				for(unsigned j=min; j<max; ++j)
				{
					m_map4Payrank[1][j] = i;
				}
				sumrate[1] += level_4_2[i].rate;
			}
			for(unsigned i=0;i<PAYRANK_COUNT;++i)
			{
				int min = sumrate[2];
				int max = level_4_3[i].rate + sumrate[2];
				for(unsigned j=min; j<max; ++j)
				{
					m_map4Payrank[2][j] = i;
				}
				sumrate[2] += level_4_3[i].rate;
			}
		}
		// shop
		{
			CAutoLock lock(const_cast<CShareMemory *>(&(m_shShop)), true);
			DataXMLShop *pdata = (DataXMLShop *)m_shShop.GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}

			m_mapXMLShop.clear();
			for(unsigned j=0;j<XML_SHOP_ALL_ITEM;++j)
			{
				if(pdata->shop[j].id)
				{
					if(m_mapXMLShop.count(pdata->shop[j].id))
					{
						if(m_mapXMLShop[pdata->shop[j].id].vip)
							m_mapXMLShop[pdata->shop[j].id].price = pdata->shop[j].price;
						else if(m_mapXMLShop[pdata->shop[j].id].price)
							m_mapXMLShop[pdata->shop[j].id].vip = pdata->shop[j].vip;
					}
					else
					{
						m_mapXMLShop[pdata->shop[j].id] = pdata->shop[j];
					}
				}
				else
					break;
			}
		}
		// worldBattleshop
		{
			CAutoLock lock(const_cast<CShareMemory *>(&(m_shWorldBattleShop)), true);
			DataXMLWorldBattleShop *pdata = (DataXMLWorldBattleShop *)m_shWorldBattleShop.GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}

			m_mapXMLWorldBattleShop.clear();
			for(unsigned j=0;j<XML_WORLD_BATTLE_SHOP_ALL_ITEM;++j)
			{
				if(pdata->shop[j].id)
				{
					m_mapXMLWorldBattleShop[pdata->shop[j].id] = pdata->shop[j];
				}
				else
					break;
			}
		}
		// rankBattleshop
		{
			CAutoLock lock(const_cast<CShareMemory *>(&(m_shRankBattleShop)), true);
			DataXMLRankBattleShop *pdata = (DataXMLRankBattleShop *)m_shRankBattleShop.GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}

			m_mapXMLRankBattleShop.clear();
			for(unsigned j=0;j<XML_RANK_BATTLE_SHOP_ALL_ITEM;++j)
			{
				if(pdata->shop[j].id)
				{
					m_mapXMLRankBattleShop[pdata->shop[j].id] = pdata->shop[j];
				}
				else
					break;
			}
		}
		// Hufushop
		{
			CAutoLock lock(const_cast<CShareMemory *>(&(m_shHufuShop)), true);
			DataXMLHufuShop *pdata = (DataXMLHufuShop *)m_shHufuShop.GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}

			m_mapXMLHufuShop.clear();
			for(unsigned j=0;j<XML_HUFU_SHOP_ALL_ITEM;++j)
			{
				if(pdata->shop[j].id)
				{
					m_mapXMLHufuShop[pdata->shop[j].id] = pdata->shop[j];
				}
				else
					break;
			}
		}
		// equipment
		{
			CAutoLock lock(const_cast<CShareMemory *>(&(m_shEquipment)), true);
			DataXMLEquipment *pdata = (DataXMLEquipment *)m_shEquipment.GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}

			m_setXMLEquipment.clear();
			for(unsigned j=0;j<XML_EQUIPMENT_ALL_ITEM;++j)
			{
				if(pdata->equip[j])
					m_setXMLEquipment.insert(pdata->equip[j]);
				else
					break;
			}
		}
		// new_lottery
		{
			CAutoLock lock(const_cast<CShareMemory *>(&(m_shnewlottery)), true);
			DataXMLnewlottery *pdata = (DataXMLnewlottery *)m_shnewlottery.GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}

			for(int i=0; i<XML_PARTITION_NUM; ++i)
			{
				m_mapXMLfirstlottery[i].clear();
				m_mapXMLsecondlottery[i].clear();
				unsigned first_rate = 0;
				for(int j=0; j<XML_FIRST_LAYER_NUM; ++j)
				{
					for(int k=0; k<pdata->part_zone[i].FirstLayer[j].rate; ++k)
					{
						m_mapXMLfirstlottery[i][first_rate] = pdata->part_zone[i].FirstLayer[j].id;
						++first_rate;
					}

				}

				unsigned second_rate = 0;
				for(int j=0; j<XML_SECOND_LAYER_NUM; ++j)
				{
					for(int k=0; k<pdata->part_zone[i].SecondLayer[j].rate; ++k)
					{
						m_mapXMLsecondlottery[i][second_rate] = pdata->part_zone[i].SecondLayer[j].id;
						++second_rate;
					}
				}
			}
		}
		//juexue
		{
			for(int i=0; i<XML_JUEXUE_NPC_NUM + 1; ++i)
			{
				unsigned sumrate = 0;
				m_mapXMLJuexueFall[i].clear();
				for(int j=0; j<e_juexue_type_max; ++j)
				{
					for(unsigned l=0;l<juexue_fall[i][j];++l)
					{
						m_mapXMLJuexueFall[i][sumrate] = j;
						++sumrate;
					}
				}
			}
			for(int k=0;k<XML_JUEXUE_LEVEL_NUM;++k)
			{
				for(int i=0; i<XML_JUEXUE_TYPE_NUM; ++i)
				{
					unsigned sumrate = 0;
					m_mapXMLJuexueType[k][i].clear();
					for(int j=0; j<e_juexue_max; ++j)
					{
						for(unsigned l=0;l<juexue_type[k][i][j];++l)
						{
							m_mapXMLJuexueType[k][i][sumrate] = j;
							++sumrate;
						}
					}
				}
			}
		}
		// qixi_choujiang
		{
			CAutoLock lock(const_cast<CShareMemory *>(&(m_shchoujiang)), true);
			DataXMLchoujiang *pdata = (DataXMLchoujiang *)m_shchoujiang.GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}

			unsigned rate = 0;
			m_mapFloor_1.clear();
			for(int i=0; i<XML_CHOUJIANG_RATE_FIRST; ++i)
			{
				for(int j=0; j<pdata->rate1[i]; ++j)
				{
					m_mapFloor_1[rate] = pdata->goods[i].index;
					++rate;
				}
			}

			rate = 0;
			m_mapFloor_2.clear();
			for(int i=0; i<XML_CHOUJIANG_RATE_SECOND; ++i)
			{
				for(int j=0; j<pdata->rate2[i]; ++j)
				{
					m_mapFloor_2[rate] = pdata->goods[i].index;
					++rate;
				}
			}
		}

		// jiangling
		{
			unsigned rate = 0;
			m_mapjiangling_rate1.clear();
			for(int i=0; i<4; ++i)
			{
				for(int j=0; j<jiang_ling_rate[0][i][1]; ++j)
				{
					m_mapjiangling_rate1[rate] = jiang_ling_rate[0][i][0];
					++rate;
				}
			}

			rate = 0;
			m_mapjiangling_rate2.clear();
			for(int i=0; i<5; ++i)
			{
				for(int j=0; j<jiang_ling_rate[1][i][1]; ++j)
				{
					m_mapjiangling_rate2[rate] = jiang_ling_rate[1][i][0];
					++rate;
				}
			}

			rate = 0;
			m_mapjiangling_rate3.clear();
			for(int i=0; i<5; ++i)
			{
				for(int j=0; j<jiang_ling_rate[2][i][1]; ++j)
				{
					m_mapjiangling_rate3[rate] = jiang_ling_rate[2][i][0];
					++rate;
				}
			}
		}

		//ActReward
		{
			DataXMLActReward *pdata = (DataXMLActReward *)m_shActReward.GetAddress();
			if(pdata == NULL)
			{
				return R_ERROR;
			}
			CAutoLock lock(const_cast<CShareMemory *>(&(m_shActReward)), true);

			for(unsigned i=0;i<ACT_REWARD_NUM;++i)
			{
				string temp(pdata->reward[i].act);
				if(m_mapXMLActivityRewad.count(temp))
					continue;

				m_mapXMLActivityRewad[temp] = i;
			}
		}

		//GateReward
		{
			DataXMLGateReward *pdata = (DataXMLGateReward *)m_shGateReward.GetAddress();
			if(pdata == NULL)
			{
				return R_ERROR;
			}
			CAutoLock lock(const_cast<CShareMemory *>(&(m_shGateReward)), true);

			for(unsigned i=0;i<GATE_REWARD_NUM;++i)
			{
				if(m_mapXMLOlGate.count(pdata->reward[i].level))
					continue;

				m_mapXMLOlGate[pdata->reward[i].level] = i;
			}
		}

		//QuestReward
		{
			DataXMLQuestReward *pdata = (DataXMLQuestReward *)m_shQuestReward.GetAddress();
			if(pdata == NULL)
			{
				return R_ERROR;
			}
			CAutoLock lock(const_cast<CShareMemory *>(&(m_shQuestReward)), true);

			for(unsigned i=0;i<QUEST_REWARD_NUM;++i)
			{
				string temp(pdata->reward[i].id);
				m_mapXMLQuest[temp] = i;
			}
		}

		{
			DataXMLHeavenDaoist *pdata = (DataXMLHeavenDaoist *)m_shHeavenDaoist.GetAddress();
			if (NULL == pdata)
			{
				return R_ERR_DB;
			}

			CAutoLock lock(const_cast<CShareMemory *>(&(m_shHeavenDaoist)), true);
			m_mapXMLHeavenDaoist.clear();

			for (unsigned i = 0; i < HEAVEN_DAOIST_NUM; ++i)
			{
				m_mapXMLHeavenDaoist[pdata->heavenDaoist[i].id] = i;
			}
		}

		{
			DataXMLCostHeavenDaoist *pdata = (DataXMLCostHeavenDaoist *)m_shCostHeavenDaoist.GetAddress();
			if (NULL == pdata)
			{
				return R_ERR_DB;
			}

			CAutoLock lock(const_cast<CShareMemory *>(&(m_shCostHeavenDaoist)), true);
			m_mapCostHeavenDaoist.clear();

			for (unsigned i = 0; i < HEAVEN_JIE_NUM + DAOIST_JIE_NUM; ++i)
			{
				m_mapCostHeavenDaoist[pdata->heavenDaoistCost[i].id] = pdata->heavenDaoistCost[i].cash;
			}
		}
		{
			DataXMLEightFormation *pdata = (DataXMLEightFormation *)m_shEightFormation.GetAddress();
			if (NULL == pdata)
			{
				return R_ERR_DB;
			}

			CAutoLock lock(const_cast<CShareMemory *>(&(m_shEightFormation)), true);
			memcpy(eight_formation, pdata->r, sizeof(eight_formation));
			for(int i = 0; i < EIGHT_FORMATION_R_NUM; ++i)
			{
				m_mapXMLEightFormation[i].clear();
			}
			for(int i = 0; i < EIGHT_FORMATION_R_NUM; ++i)
			{
				for (unsigned j = 0; j <= EIGHT_FORMATION_NUM; ++j)
				{
					m_mapXMLEightFormation[i][(pdata->eightFormation)[i][j].id] = j;
				}
			}

		}
		{
			DataXMLCostEightFormation *pdata = (DataXMLCostEightFormation *)m_shCostEightFormation.GetAddress();
			if (NULL == pdata)
			{
				return R_ERR_DB;
			}

			CAutoLock lock(const_cast<CShareMemory *>(&(m_shCostEightFormation)), true);
			m_mapCostEightFormation.clear();

			for (unsigned i = 0; i <= EIGHT_FORMATION_JIE_NUM; ++i)
			{
				m_mapCostEightFormation[pdata->eightFormationCost[i].id] = pdata->eightFormationCost[i].cash;
			}
		}
		{
			DataXMLBetShop *pdata = (DataXMLBetShop *)m_shBetShop.GetAddress();
			if (NULL == pdata)
			{
				return R_ERR_DB;
			}

			CAutoLock lock(const_cast<CShareMemory *>(&(m_shBetShop)), true);
			m_mapXMLBetShop.clear();

			for (unsigned i = 0; i < XMLBETSHOP_ITEMNUM; ++i)
			{
				unsigned eqid = pdata->bsitem[i].eqid;
				if (!m_mapXMLBetShop.count(eqid))
				{
					m_mapXMLBetShop[eqid] = pdata->bsitem[i];
				}
			}
		}

		//新绝世无双
		{
			DataXMLNewJueshiWS *pdata = (DataXMLNewJueshiWS *)m_shNewJueshiWS.GetAddress();

			if (NULL == pdata)
			{
				return R_ERR_DB;
			}

			CAutoLock lock(const_cast<CShareMemory*>(&(m_shNewJueshiWS)), true);
			m_mapJueshiWS.clear();

			for (unsigned i = 0; i < MAX_HERO_NUM; ++i)
			{
				if (pdata->heroitems[i].id != 0)
				{
					m_mapJueshiWS.insert(make_pair(pdata->heroitems[i].id, i));
				}
				else
				{
					break;
				}
			}
		}

		//鸿运当头
		{
			DataXMLOpporknock *pdata = (DataXMLOpporknock *)m_shOpporknock.GetAddress();

			if (NULL == pdata)
			{
				return R_ERR_DB;
			}

			CAutoLock lock(const_cast<CShareMemory*>(&(m_shOpporknock)), true);
			m_mapRefresh.clear();

			//只针对刷新奖池进行id和索引的映射
			for (unsigned i = 0; i < REFRESH_ITEMS_MAX; ++i)
			{
				if (pdata->refreshpools.allitems[i].id != 0)
				{
					m_mapRefresh.insert(make_pair(pdata->refreshpools.allitems[i].id, i));
				}
				else
				{
					break;
				}
			}
		}

		//幸运连连
		{
			DataXMLFortunatelyAgain *pdata = (DataXMLFortunatelyAgain *)m_shFortunatelyAgain.GetAddress();

			if (NULL == pdata)
			{
				return R_ERR_DB;
			}

			CAutoLock lock(const_cast<CShareMemory*>(&(m_shFortunatelyAgain)), true);
			m_mapEquipIndex.clear();
			EquipIndex indexval;

			for(int i = 0; i < MAX_POOL_ITEMS; ++i)
			{
				for (int j = 0; j < pdata->poolitems[i].weightcount; ++j)
				{
					for (int k = 0; k < MAX_EQUIPMENT_ITEMS; ++k)
					{
						if (pdata->poolitems[i].weightItems[j][k].index != 0)
						{
							indexval.poolindex = i;
							indexval.weightindex = j;
							indexval.equipindex = k;

							m_mapEquipIndex.insert(make_pair(pdata->poolitems[i].weightItems[j][k].index, indexval));
						}
						else
						{
							break;
						}
					}
				}
			}
		}

		//天命
		{
			DataXMLTurnPlate *pdata = (DataXMLTurnPlate *)m_shTurnPlate.GetAddress();

			if (NULL == pdata)
			{
				return R_ERR_DB;
			}

			CAutoLock lock(const_cast<CShareMemory*>(&(m_shTurnPlate)), true);
			m_mapTurnEquipIndex.clear();
			EquipIndex indexval;

			for(int i = 0; i < MAX_TURLPLATE_POOL_ITEMS; ++i)
			{
				for (int j = 0; j < pdata->poolitems[i].weightcount; ++j)
				{
					for (int k = 0; k < MAX_EQUIPMENT_ITEMS; ++k)
					{
						if (pdata->poolitems[i].weightItems[j][k].index != 0)
						{
							indexval.poolindex = i;
							indexval.weightindex = j;
							indexval.equipindex = k;

							m_mapTurnEquipIndex.insert(make_pair(pdata->poolitems[i].weightItems[j][k].index, indexval));
						}
						else
						{
							break;
						}
					}
				}
			}
		}

		//充值自选
		{
			DataXMLRechargeOptional *pdata = (DataXMLRechargeOptional *)m_shRechargeOptional.GetAddress();

			if (NULL == pdata)
			{
				return R_ERR_DB;
			}

			CAutoLock lock(const_cast<CShareMemory*>(&(m_shRechargeOptional)), true);
			m_mapOptional.clear();

			for (unsigned i = 0; i < OPTIONAL_ITEMS_MAX; ++i)
			{
				if (pdata->items[i].id != 0)
				{
					m_mapOptional.insert(make_pair(pdata->items[i].id , i));
				}
				else
				{
					break;
				}
			}
		}

		//小兵训练
		{
			DataXMLSoldierTrainAndUp *pdata = (DataXMLSoldierTrainAndUp *)m_shSoldierTrainAndUp.GetAddress();

			if (NULL == pdata)
			{
				return R_ERR_DB;
			}

			CAutoLock lock(const_cast<CShareMemory*>(&(m_shSoldierTrainAndUp)), true);
			m_mapSoldier.clear();

			for (unsigned i = 0; i < MAX_SOLDIER_KIND; ++i)
			{
				if (pdata->soldieritems[i].sid != 0)
				{
					m_mapSoldier.insert(make_pair(pdata->soldieritems[i].sid , i));
				}
				else
				{
					break;
				}
			}
		}

		//兵书遁甲技能
		{
			DataXMLHeavenDaoSkill *pdata = (DataXMLHeavenDaoSkill *)m_shHeavenDaoSkill.GetAddress();

			if (NULL == pdata)
			{
				return R_ERR_DB;
			}

			CAutoLock lock(const_cast<CShareMemory*>(&(m_shHeavenDaoSkill)), true);
			m_mapHeaven.clear();
			m_mapDAO.clear();

			for (unsigned i = 0; i < MAX_DAO_SKILL_ITEMS; ++i)
			{
				if (pdata->daoitem[i].id != 0)
				{
					m_mapDAO.insert(make_pair(pdata->daoitem[i].id , i));
				}
				else
				{
					break;
				}
			}

			for (unsigned i = 0; i < MAX_HEAVEN_SKILL_ITEMS; ++i)
			{
				if (pdata->heavenitem[i].id != 0)
				{
					m_mapHeaven.insert(make_pair(pdata->heavenitem[i].id , i));
				}
				else
				{
					break;
				}
			}
		}

		//时装殿
		{
			DataXMLFashionShop *pdata = (DataXMLFashionShop *)m_shFashionShop.GetAddress();
			if (NULL == pdata)
			{
				return R_ERR_DB;
			}
			CAutoLock lock(const_cast<CShareMemory*>(&(m_shFashionShop)), true);

			m_mapFashionShopIndex.clear();
			for (unsigned i = 0; i < MAX_FASHION_SHOP_ITEMS; ++i)
			{
				if (pdata->fashion_shop_items[i].id_ != 0)
				{
					m_mapFashionShopIndex[pdata->fashion_shop_items[i].id_] = i;
				}
				else
				{
					break;
				}
			}
		}

		//厚惠有期
		{
			DataXMLHouHuiYouQi *pdata = (DataXMLHouHuiYouQi *)m_shHouHuiYouQi.GetAddress();
			if (NULL == pdata)
			{
				return R_ERR_DB;
			}
			CAutoLock lock(const_cast<CShareMemory*>(&(m_shHouHuiYouQi)), true);

			m_mapMinZoneHouHuiYouQi.clear();
			m_mapMaxZoneHouHuiYouQi.clear();
			m_mapChargeHouHuiYouQi.clear();
			for (int inx = 0; inx < HOUHUIYOUQI_ZONE_SECTION; ++inx)
			{
				if ((pdata->houhuiyouqi_items[inx]).zone_start_ && (pdata->houhuiyouqi_items[inx]).zone_end_)
				{
					m_mapMinZoneHouHuiYouQi[inx] = (pdata->houhuiyouqi_items[inx]).zone_start_;
					m_mapMaxZoneHouHuiYouQi[inx] = (pdata->houhuiyouqi_items[inx]).zone_end_;
					for(int iny = 0; iny < HOUHUIYOUQI_BIG_TALBE_NUM; ++iny)
					{
						if ((pdata->houhuiyouqi_items[inx]).big_table_charge_need_[iny])
						{
							m_mapChargeHouHuiYouQi[inx][iny] = (pdata->houhuiyouqi_items[inx]).big_table_charge_need_[iny];
						} else
						{
							break;
						}
					}
				}
				else
				{
					break;
				}
			}

			//4399
			m_map4399MinZoneHouHuiYouQi.clear();
			m_map4399MaxZoneHouHuiYouQi.clear();
			m_map4399ChargeHouHuiYouQi.clear();
			for (int inx = 0; inx < HOUHUIYOUQI_4399_ZONE_SECTION; ++inx)
			{
				if ((pdata->houhuiyouqi_4399_items[inx]).zone_start_ && (pdata->houhuiyouqi_4399_items[inx]).zone_end_)
				{
					m_map4399MinZoneHouHuiYouQi[inx] = (pdata->houhuiyouqi_4399_items[inx]).zone_start_;
					m_map4399MaxZoneHouHuiYouQi[inx] = (pdata->houhuiyouqi_4399_items[inx]).zone_end_;
					for(int iny = 0; iny < HOUHUIYOUQI_BIG_TALBE_NUM; ++iny)
					{
						if ((pdata->houhuiyouqi_4399_items[inx]).big_table_charge_need_[iny])
						{
							m_map4399ChargeHouHuiYouQi[inx][iny] = (pdata->houhuiyouqi_4399_items[inx]).big_table_charge_need_[iny];
						} else
						{
							break;
						}
					}
				}
				else
				{
					break;
				}
			}
		}

		//超值折扣
		{
			DataXMLChaoZhiZheKou *pdata = (DataXMLChaoZhiZheKou *)m_shChaoZhiZheKou.GetAddress();
			if (NULL == pdata)
			{
				return R_ERR_DB;
			}
			CAutoLock lock(const_cast<CShareMemory*>(&(m_shChaoZhiZheKou)), true);

			m_mapMinZoneChaoZhiZheKou.clear();
			m_mapMaxZoneChaoZhiZheKou.clear();
			m_mapChargeChaoZhiZheKou.clear();
			for (int inx = 0; inx < CHAOZHIZHEKOU_ZONE_SECTION; ++inx)
			{
				if ((pdata->chaozhizhekou_items[inx]).zone_start_ && (pdata->chaozhizhekou_items[inx]).zone_end_)
				{
					m_mapMinZoneChaoZhiZheKou[inx] = (pdata->chaozhizhekou_items[inx]).zone_start_;
					m_mapMaxZoneChaoZhiZheKou[inx] = (pdata->chaozhizhekou_items[inx]).zone_end_;
					for(int iny = 0; iny < CHAOZHIZHEKOU_BIG_TALBE_NUM; ++iny)
					{
						if ((pdata->chaozhizhekou_items[inx]).big_table_charge_need_[iny])
						{
							m_mapChargeChaoZhiZheKou[inx][iny] = (pdata->chaozhizhekou_items[inx]).big_table_charge_need_[iny];
						} else
						{
							break;
						}
					}
				}
				else
				{
					break;
				}
			}
		}

		//约惠巨献
		{
			DataXMLYueHuiJuXian *pdata = (DataXMLYueHuiJuXian *)m_shYueHuiJuXian.GetAddress();
			if (NULL == pdata)
			{
				return R_ERR_DB;
			}
			CAutoLock lock(const_cast<CShareMemory*>(&(m_shYueHuiJuXian)), true);

			m_mapMinZoneYueHuiJuXian.clear();
			m_mapMaxZoneYueHuiJuXian.clear();
			m_mapChargeYueHuiJuXian.clear();
			for (int inx = 0; inx < YUEHUIJUXIAN_ZONE_SECTION; ++inx)
			{
				if ((pdata->yuehuijuxian_items[inx]).zone_start_ && (pdata->yuehuijuxian_items[inx]).zone_end_)
				{
					m_mapMinZoneYueHuiJuXian[inx] = (pdata->yuehuijuxian_items[inx]).zone_start_;
					m_mapMaxZoneYueHuiJuXian[inx] = (pdata->yuehuijuxian_items[inx]).zone_end_;
					for(int iny = 0; iny < YUEHUIJUXIAN_BIG_TALBE_NUM; ++iny)
					{
						if ((pdata->yuehuijuxian_items[inx]).big_table_charge_need_[iny])
						{
							m_mapChargeYueHuiJuXian[inx][iny] = (pdata->yuehuijuxian_items[inx]).big_table_charge_need_[iny];
						} else
						{
							break;
						}
					}
				}
				else
				{
					break;
				}
			}

			//后来添加ly 和 4399
			m_map4399MinZoneYueHuiJuXian.clear();
			m_map4399MaxZoneYueHuiJuXian.clear();
			m_map4399ChargeYueHuiJuXian.clear();
			for (int inx = 0; inx < YUEHUIJUXIAN_4399_ZONE_SECTION; ++inx)
			{
				if ((pdata->yuehuijuxian_4399_items[inx]).zone_start_ && (pdata->yuehuijuxian_4399_items[inx]).zone_end_)
				{
					m_map4399MinZoneYueHuiJuXian[inx] = (pdata->yuehuijuxian_4399_items[inx]).zone_start_;
					m_map4399MaxZoneYueHuiJuXian[inx] = (pdata->yuehuijuxian_4399_items[inx]).zone_end_;
					for(int iny = 0; iny < YUEHUIJUXIAN_BIG_TALBE_NUM; ++iny)
					{
						if ((pdata->yuehuijuxian_4399_items[inx]).big_table_charge_need_[iny])
						{
							m_map4399ChargeYueHuiJuXian[inx][iny] = (pdata->yuehuijuxian_4399_items[inx]).big_table_charge_need_[iny];
						} else
						{
							break;
						}
					}
				}
				else
				{
					break;
				}
			}
		}

		//全服限购
		{
			DataXMLLimitBuyOfZone *pdata = (DataXMLLimitBuyOfZone *)m_shLimitBuyOfZone.GetAddress();
			if (NULL == pdata)
			{
				return R_ERR_DB;
			}
			CAutoLock lock(const_cast<CShareMemory*>(&(m_shLimitBuyOfZone)), true);

			m_mapMinZoneLimitBuy.clear();
			m_mapMaxZoneLimitBuy.clear();
			m_mapConsumeLimitBuy.clear();

			//qq
			for (int inx = 0; inx < LIMITBUYOFZONE_ZONE_QQ_SECTION; ++inx)
			{
				if ((pdata->limitbuyofzone_qq_items[inx]).zone_start_ && (pdata->limitbuyofzone_qq_items[inx]).zone_end_)
				{
					m_mapMinZoneLimitBuy[0][inx] = (pdata->limitbuyofzone_qq_items[inx]).zone_start_;
					m_mapMaxZoneLimitBuy[0][inx] = (pdata->limitbuyofzone_qq_items[inx]).zone_end_;
					for(int iny = 0; iny < LIMITBUYOFZONE_TALBE_NUM; ++iny)
					{
						if ((pdata->limitbuyofzone_qq_items[inx]).section_limitbuyofzone_[iny].cond_)
						{
							m_mapConsumeLimitBuy[0][inx][iny] = (pdata->limitbuyofzone_qq_items[inx]).section_limitbuyofzone_[iny].cond_;
						} else
						{
							break;
						}
					}
				}
				else
				{
					break;
				}
			}

			//ly
			for (int inx = 0; inx < LIMITBUYOFZONE_ZONE_LY_SECTION; ++inx)
			{
				if ((pdata->limitbuyofzone_ly_items[inx]).zone_start_ && (pdata->limitbuyofzone_ly_items[inx]).zone_end_)
				{
					m_mapMinZoneLimitBuy[1][inx] = (pdata->limitbuyofzone_ly_items[inx]).zone_start_;
					m_mapMaxZoneLimitBuy[1][inx] = (pdata->limitbuyofzone_ly_items[inx]).zone_end_;
					for(int iny = 0; iny < LIMITBUYOFZONE_TALBE_NUM; ++iny)
					{
						if ((pdata->limitbuyofzone_ly_items[inx]).section_limitbuyofzone_[iny].cond_)
						{
							m_mapConsumeLimitBuy[1][inx][iny] = (pdata->limitbuyofzone_ly_items[inx]).section_limitbuyofzone_[iny].cond_;
						} else
						{
							break;
						}
					}
				}
				else
				{
					break;
				}
			}

			//4399
			for (int inx = 0; inx < LIMITBUYOFZONE_ZONE_4399_SECTION; ++inx)
			{
				if ((pdata->limitbuyofzone_4399_items[inx]).zone_start_ && (pdata->limitbuyofzone_4399_items[inx]).zone_end_)
				{
					m_mapMinZoneLimitBuy[2][inx] = (pdata->limitbuyofzone_4399_items[inx]).zone_start_;
					m_mapMaxZoneLimitBuy[2][inx] = (pdata->limitbuyofzone_4399_items[inx]).zone_end_;
					for(int iny = 0; iny < LIMITBUYOFZONE_TALBE_NUM; ++iny)
					{
						if ((pdata->limitbuyofzone_4399_items[inx]).section_limitbuyofzone_[iny].cond_)
						{
							m_mapConsumeLimitBuy[2][inx][iny] = (pdata->limitbuyofzone_4399_items[inx]).section_limitbuyofzone_[iny].cond_;
						} else
						{
							break;
						}
					}
				}
				else
				{
					break;
				}
			}
		}

		//百宝箱
		{
			DataXMLTreasureBox *pdata = (DataXMLTreasureBox *)m_shTreasureBox.GetAddress();

			if (NULL == pdata)
			{
				return R_ERR_DB;
			}

			CAutoLock lock(const_cast<CShareMemory*>(&(m_shTreasureBox)), true);
			m_treasurebox.clear();

			for(int i = 0; i < pdata->rewardnum; ++i)
			{
				if (pdata->rewarditems[i].id != 0)
				{
					m_treasurebox.insert(make_pair(pdata->rewarditems[i].id , i));
				}
				else
				{
					break;
				}
			}
		}

		//保护女神
		{
			DataXMLProtectGoddess *pdata = (DataXMLProtectGoddess *)m_shProtectGoddess.GetAddress();

			if (NULL == pdata)
			{
				return R_ERR_DB;
			}

			CAutoLock lock(const_cast<CShareMemory*>(&(m_shProtectGoddess)), true);
			m_protectgoddess.clear();

			for(int i = 0; i < MAX_REWARD_ITEM; ++i)
			{
				if (pdata->reward[i].id != 0)
				{
					m_protectgoddess.insert(make_pair(pdata->reward[i].id , i));
				}
				else
				{
					break;
				}
			}
		}
		{
			DataXMLCatapult *pdata = (DataXMLCatapult *)m_shCatapult.GetAddress();
			if (NULL == pdata)
			{
				return R_ERR_DB;
			}

			CAutoLock lock(const_cast<CShareMemory *>(&(m_shCatapult)), true);
			m_mapXMLCatapult.clear();

			for (unsigned i = 0; i < CATAPULT_NUM; ++i)
			{
				m_mapXMLCatapult[pdata->catapult[i].id] = i;
			}
		}

		{
			DataXMLCostCatapult *pdata = (DataXMLCostCatapult *)m_shCostCatapult.GetAddress();
			if (NULL == pdata)
			{
				return R_ERR_DB;
			}

			CAutoLock lock(const_cast<CShareMemory *>(&(m_shCostCatapult)), true);
			m_mapCostCatapult.clear();

			for (unsigned i = 0; i < CATAPULT_JIE_NUM; ++i)
			{
				m_mapCostCatapult[pdata->catapultCost[i].id] = pdata->catapultCost[i].cash;
			}
		}

		//投石车技能
		{
			DataXMLCatapultSkill *pdata = (DataXMLCatapultSkill *)m_shCatapultSkill.GetAddress();

			if (NULL == pdata)
			{
				return R_ERR_DB;
			}

			CAutoLock lock(const_cast<CShareMemory*>(&(m_shCatapultSkill)), true);
			m_mapCatapultSkill.clear();

			for (unsigned i = 0; i < MAX_CATAPULT_SKILL_ITEMS; ++i)
			{
				if (pdata->skillitem[i].id != 0)
				{
					m_mapCatapultSkill.insert(make_pair(pdata->skillitem[i].id , i));
				}
				else
				{
					break;
				}
			}
		}
	}

	int ret = 0;
	ret = InitEggReward();
	if (ret)
	{
		error_log("InitEggReward fail");
		return ret;
	}
	ret = InitJinqiushiyueChongzhihuikui();
	if (ret)
	{
		error_log("InitJinqiushiyueChongzhihuikui fail");
		return ret;
	}
	ret = InitZhiZunBaoXiang();
	if (ret)
	{
		error_log("InitZhiZunBaoXiang fail");
		return ret;
	}
	ret = InitJinQiuNovember();
	if (ret)
	{
		error_log("InitJinQiuNovember fail");
		return ret;
	}
	ret = InitAcchargeBackShenwen();
	if (ret)
	{
		error_log("InitAcchargeBackShenwen fail");
		return ret;
	}

	ret = InitJsonWinterHolidayRevelry();
	if (ret)
	{
		error_log("InitJsonWinterHolidayRevelry fail");
		return ret;
	}

	ret = InitPayOptional();
	if (ret)
	{
		error_log("InitPayOptional fail");
		return ret;
	}

	ret = InitTokenIntensify();
	if (ret)
	{
		error_log("TokenIntensify fail");
		return ret;
	}

	ret = InitWorldTreasure();
	if (ret)
	{
		error_log("WorldTreasure fail");
		return ret;
	}

	ret = InitSoulFeedback();
	if (ret)
	{
		error_log("SoulFeedback fail");
		return ret;
	}

	ret = InitAwakenFeedback();
	if (ret)
	{
		error_log("AwakenFeedback fail");
		return ret;
	}

	ret = InitCastSoulDiscount();
	if(ret)
	{
		error_log("CastSoulDiscount fail");
		return ret;
	}

	ret = InitGemDiscount();
	if (ret)
	{
		error_log("GemDiscount fail");
		return ret;
	}

	ret = InitTreasuresAllAround();
	if (ret)
	{
		error_log("InitTreasuresAllAround fail");
		return ret;
	}

	ret = InitSpiritFoster();
	if (ret)
	{
		error_log("InitSpiritFoser fail");
		return ret;
	}

	ret = InitChargeHorse();
	if (ret)
	{
		error_log("InitChargeHorse fail");
		return ret;
	}

	ret = InitVickyAccX();
	if (ret)
	{
		error_log("InitVickyAccX fail");
		return ret;
	}

	m_init = true;
	return 0;
}

/*****************building*****************/
int CDataXML::InitBuilding()
{
	DataXMLBuilding *pdata = (DataXMLBuilding *)m_shBuilding.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shBuilding), true,LOCK_MAX);

	memset(pdata,0,sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("sgbuildingdata.xml");
	CMarkupSTL xmlConf;

	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout<<("content node wrong")<<endl;
		return 1;
	}

	xmlConf.IntoElem();

	if(!xmlConf.FindElem("buildings"))
	{
		cout<<("buildings node wrong")<<endl;
		return 1;
	}

	xmlConf.IntoElem();

	unsigned i = 0;
	m_mapBuilding.clear();

	while(xmlConf.FindElem("building"))
	{
		string t = xmlConf.GetAttrib("id");
		string lv = xmlConf.GetAttrib("level");
		string produce = xmlConf.GetAttrib("produce");
		string capacity = xmlConf.GetAttrib("capacity");

		string cost, time;
		xmlConf.IntoElem();

		if(xmlConf.FindElem("costs"))
		{
			xmlConf.IntoElem();

			if(xmlConf.FindElem("cost"))
			{
				cost = xmlConf.GetAttrib("food");
				time = xmlConf.GetAttrib("time");
			}
			else
			{
				cout<<("building config wrong 1 id=")<<t<<" level="<<lv<<" i="<<i<<endl;
				return 1;
			}

			xmlConf.OutOfElem();
		}
		else
		{
			cout<<("building config wrong 2 id=")<<t<<" level="<<lv<<" i="<<i<<endl;
			return 1;
		}

		xmlConf.OutOfElem();

		if(t.empty() || lv.empty() || cost.empty() || time.empty())
		{
			cout<<("building config wrong 3 id=")<<t<<" level="<<lv<<" food="<<cost<<" time="<<time<<" i="<<i<<endl;
			return 1;
		}

		cost = cost.substr(1, cost.length()-2);
		vector<string> c;
		String::Split(cost, ',', c);

		if(c.size() < XML_BUILDING_RES)
		{
			cout<<("building config wrong 4 id=")<<t<<" level="<<lv<<" i="<<i<<endl;
			return 1;
		}

		pdata->build[i].t = CTrans::STOI(t.c_str());
		pdata->build[i].lv = CTrans::STOI(lv.c_str());
		pdata->build[i].time = CTrans::STOI(time.c_str());

		if (!produce.empty())
		{
			pdata->build[i].produce = CTrans::STOI(produce.c_str())/6;   //10min的产量.除以6，是这么规定的。
		}

		if (!capacity.empty())
		{
			pdata->build[i].capacity = CTrans::STOI(capacity.c_str());
		}

		for(unsigned s=0;s<XML_BUILDING_RES;++s)
			pdata->build[i].cost[s] = CTrans::STOI(c[s].c_str());

		m_mapBuilding[make_pair(pdata->build[i].t, pdata->build[i].lv)] = i;
		++i;
	}

	m_shBuilding.SetInitDone();
	return 0;
}

int CDataXML::GetBuilding(unsigned t, unsigned lv, XMLBuildingItem& build)
{
	pair<unsigned, unsigned> id(t, lv);
	if(!m_mapBuilding.count(id))
		return R_ERR_PARAM;

	DataXMLBuilding *pdata = (DataXMLBuilding *)m_shBuilding.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory *>(&(m_shBuilding)), true);

	build = pdata->build[m_mapBuilding[id]];

	return 0;
}
/****************Hero*********************/
int CDataXML::InitHero()
{
	DataXMLHero *pdata = (DataXMLHero *)m_shHero.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shHero), true,LOCK_MAX);

	memset(pdata,0,sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("olhero.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}
	if(!xmlConf.FindElem("content"))
	{
		cout<<("content node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();
	if(!xmlConf.FindElem("heroes"))
	{
		cout<<("heroes node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();

	unsigned i = 0;
	m_mapXMLHero.clear();
	unsigned sumrate[XML_HERO_RATE];
	unsigned sum = 0;
	for(unsigned m=0;m<XML_HERO_RATE;++m)
	{
		m_mapXMLHeroRate[m].clear();
		sumrate[m] = 0;
	}

	while(xmlConf.FindElem("hero"))
	{
		string id = xmlConf.GetAttrib("id");
		string type = xmlConf.GetAttrib("type");
		string mix = xmlConf.GetAttrib("mix");
		string prof = xmlConf.GetAttrib("prof");
		string country = xmlConf.GetAttrib("country");
		string rate = xmlConf.GetAttrib("rate");
		string point;
		if(xmlConf.FindChildElem("point"))
		{
			point = xmlConf.GetChildData();
			point = point.substr(1,point.length()-2);
		}

		string hirecost;

		if(xmlConf.FindChildElem("hirecost"))
		{
			hirecost = xmlConf.GetChildData();
			hirecost = hirecost.substr(1, hirecost.length()-2);
		}

		if(id.empty() || type.empty() || prof.empty() || country.empty() || rate.empty() || point.empty())
		{
			cout<<("hero config wrong 1 ")<<id<<endl;
			return 1;
		}
		vector<string> rltstar;
		vector<string> rltrate[XML_HERO_STAR];
		String::Split(rate, '|', rltstar);
		if(rltstar.size() < XML_HERO_STAR)
		{
			cout<<("hero config wrong 2.1 ")<<id<<endl;
			return 1;
		}
		for(int r=0;r<XML_HERO_STAR;++r)
		{
			String::Split(rltstar[r], ',', rltrate[r]);
			if(rltrate[r].size() < XML_HERO_RATE)
			{
				cout<<("hero config wrong 2.2 ")<<id<<endl;
				return 1;
			}
		}
		id = id.substr(1);

		pdata->xmlhero[i].id = CTrans::STOI(id.c_str());
		pdata->xmlhero[i].type = CTrans::STOI(type.c_str());
		pdata->xmlhero[i].mix = mix.empty()?0:CTrans::STOI(mix.c_str());
		pdata->xmlhero[i].prof = CTrans::STOI(prof.c_str());
		pdata->xmlhero[i].country = CTrans::STOI(country.c_str());

		for(unsigned s=0;s<XML_HERO_STAR;++s)
		{
			for(unsigned j=0;j<XML_HERO_RATE;++j)
				pdata->xmlhero[i].rate[s][j] = CTrans::STOI(rltrate[s][j].c_str());
		}

		pdata->xmlhero[i].point = CTrans::STOI(point.c_str());
		pdata->xmlhero[i].hirecost = CTrans::STOI(hirecost.c_str());

		m_mapXMLHero[pdata->xmlhero[i].id] = i;
		for(unsigned m=0;m<XML_HERO_STAR;++m)
		{
			for(unsigned k=0;k<XML_HERO_RATE;++k)
			{
				for(unsigned l=0;l<pdata->xmlhero[i].rate[m][k];++l)
				{
					m_mapXMLHeroRate[k][sumrate[k]] = pair<unsigned, unsigned>(i,m+1);
					++sumrate[k];
				}
				if(k == XML_HERO_RATE - 2 && pdata->xmlhero[i].type >= 4)
				{
					for(unsigned l=0;l<pdata->xmlhero[i].rate[m][k];++l)
					{
						m_mapXMLHeroRatePurple[sum] = pair<unsigned, unsigned>(i,m+1);
						++sum;
					}
				}
			}
		}
		++i;
	}

	m_shHero.SetInitDone();
	return 0;
}
int CDataXML::GetHero(unsigned id, XMLHero& hero)
{
	if(!m_mapXMLHero.count(id))
		return R_ERR_PARAM;

	DataXMLHero *pdata = (DataXMLHero *)m_shHero.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory *>(&(m_shHero)), true);

	hero = pdata->xmlhero[m_mapXMLHero[id]];

	return 0;
}
int CDataXML::CheckHero(unsigned id)
{
	if(m_mapXMLHero.count(id))
		return 0;
	return R_ERR_DATA;
}
int CDataXML::RefreshHero(unsigned type,unsigned& hero1,unsigned& star1,unsigned& hero2,unsigned& star2,unsigned& hero3,unsigned& star3, bool purple)
{
	if(type >= XML_HERO_RATE - 1)
		return R_ERR_PARAM;

	DataXMLHero *pdata = (DataXMLHero *)m_shHero.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory *>(&(m_shHero)), true);

	pair<unsigned,unsigned> h1,h2,h3;
	if(type == XML_HERO_RATE - 2)
	{
		if(purple)
			h1 = m_mapXMLHeroRatePurple[Math::GetRandomInt(m_mapXMLHeroRatePurple.rbegin()->first + 1)];
		else
			h1 = m_mapXMLHeroRate[XML_HERO_RATE - 2][Math::GetRandomInt(m_mapXMLHeroRate[XML_HERO_RATE - 2].rbegin()->first + 1)];
		h2 = m_mapXMLHeroRate[XML_HERO_RATE - 1][Math::GetRandomInt(m_mapXMLHeroRate[XML_HERO_RATE - 1].rbegin()->first + 1)];
		h3 = m_mapXMLHeroRate[XML_HERO_RATE - 1][Math::GetRandomInt(m_mapXMLHeroRate[XML_HERO_RATE - 1].rbegin()->first + 1)];
		if(Math::GetRandomInt(2))
		{
			pair<unsigned,unsigned> temp = h1;
			h1 = h2;
			h2 = temp;
		}
		else if(Math::GetRandomInt(2))
		{
			pair<unsigned,unsigned> temp = h1;
			h1 = h3;
			h3 = temp;
		}
		hero1 = pdata->xmlhero[h1.first].id;
		star1 = h1.second;
		hero2 = pdata->xmlhero[h2.first].id;
		star2 = h2.second;
		hero3 = pdata->xmlhero[h3.first].id;
		star3 = h3.second;
	}
	else
	{
		h1 = m_mapXMLHeroRate[type][Math::GetRandomInt(m_mapXMLHeroRate[type].rbegin()->first + 1)];
		h2 = m_mapXMLHeroRate[type][Math::GetRandomInt(m_mapXMLHeroRate[type].rbegin()->first + 1)];
		h3 = m_mapXMLHeroRate[type][Math::GetRandomInt(m_mapXMLHeroRate[type].rbegin()->first + 1)];
		hero1 = pdata->xmlhero[h1.first].id;
		star1 = h1.second;
		hero2 = pdata->xmlhero[h2.first].id;
		star2 = h2.second;
		hero3 = pdata->xmlhero[h3.first].id;
		star3 = h3.second;
	}

	return 0;
}
/*************************************/

/***************MixHero**********************/
int CDataXML::InitMixHero()
{
	DataXMLMixHero *pdata = (DataXMLMixHero *)m_shMixHero.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shMixHero), true,LOCK_MAX);

	memset(pdata,0,sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("heromix.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}
	if(!xmlConf.FindElem("content"))
	{
		cout<<("content node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();

	while(xmlConf.FindElem("mix"))
	{
		string id = xmlConf.GetAttrib("id");
		if(id.empty())
		{
			cout<<("mixhero config wrong 1 ")<<id<<endl;
			return 1;
		}
		unsigned mixid = CTrans::STOI(id.c_str());
		if(mixid > XML_HERO_NUM || !mixid)
		{
			cout<<("mixhero config wrong 1.1 ")<<id<<endl;
			return 1;
		}

		xmlConf.IntoElem();
		while(xmlConf.FindElem("star"))
		{
			string starid = xmlConf.GetAttrib("id");
			if(starid.empty())
			{
				cout<<("mixhero config wrong 2 ")<<starid<<endl;
				return 1;
			}
			unsigned mixstar = CTrans::STOI(starid.c_str());
			if(mixstar > XML_HERO_STAR || mixstar < 2)
			{
				cout<<("mixhero config wrong 2.1 ")<<starid<<endl;
				return 1;
			}

			unsigned i = 0;
			xmlConf.IntoElem();
			while(xmlConf.FindElem("item"))
			{
				if(i == XML_HERO_SOURCE)
					break;

				string heroId = xmlConf.GetAttrib("heroId");
				string type = xmlConf.GetAttrib("type");
				string star = xmlConf.GetAttrib("star");
				if(heroId.empty() || type.empty() || star.empty())
				{
					cout<<("mixhero config wrong 3 ")<<id<<endl;
					return 1;
				}

				if(heroId == "selfId")
					pdata->xmlmixhero[mixid-1][mixstar-2][i].heroId = XML_HERO_SELF;
				else
				{
					id = heroId.substr(1);
					pdata->xmlmixhero[mixid-1][mixstar-2][i].heroId = CTrans::STOI(heroId.c_str());
				}
				pdata->xmlmixhero[mixid-1][mixstar-2][i].type = CTrans::STOI(type.c_str());
				pdata->xmlmixhero[mixid-1][mixstar-2][i].star = CTrans::STOI(star.c_str());

				++i;
			}
			xmlConf.OutOfElem();
		}
		xmlConf.OutOfElem();
	}

	m_shMixHero.SetInitDone();
	return 0;
}

int CDataXML::GetMixHero(unsigned id, unsigned star, XMLSourceHero mixhero[XML_HERO_SOURCE])
{
	if(id > XML_HERO_NUM || !id)
		return R_ERR_PARAM;
	if(star > XML_HERO_STAR || star < 2)
		return R_ERR_PARAM;

	DataXMLMixHero *pdata = (DataXMLMixHero *)m_shMixHero.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory *>(&(m_shMixHero)), true);

	for(int i=0;i<XML_HERO_SOURCE;++i)
		mixhero[i] = pdata->xmlmixhero[id-1][star-2][i];

	return 0;
}
/*************************************/

/****************VIP*********************/
int CDataXML::InitVIP()
{
	DataXMLVIP *pdata = (DataXMLVIP *)m_shVIP.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shVIP), true,LOCK_MAX);

	memset(pdata,0,sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("sgvipconfig.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}
	if(!xmlConf.FindElem("content"))
	{
		cout<<("content node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();

	if(!xmlConf.FindElem("vipprivilege"))
	{
		cout<<("vipprivilege node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();
	while(xmlConf.FindElem("item"))
	{
		string id = xmlConf.GetAttrib("id");
		string type = xmlConf.GetAttrib("type");
		string index = xmlConf.GetAttrib("index");
		string privile = xmlConf.GetData();
		if(id.empty() || type.empty() || index.empty() || privile.empty())
		{
			cout<<("vipprivilege config wrong 1 ")<<index<<endl;
			return 1;
		}
		privile = privile.substr(1,privile.length()-2);
		vector<string> rlt;
		String::Split(privile, ',', rlt);
		if(rlt.size() != XML_VIP_GRADE)
		{
			cout<<("vipprivilege config wrong 2 ")<<index<<endl;
			return 1;
		}

		unsigned i = CTrans::STOI(index.c_str()) - 1;
		if(i >= XML_VIP_PRL)
		{
			cout<<("vipprivilege config wrong 3 ")<<index<<endl;
			return 1;
		}
		pdata->xmlvip[i].id = CTrans::STOI(id.c_str());
		pdata->xmlvip[i].type = CTrans::STOI(type.c_str());
		pdata->xmlvip[i].index = CTrans::STOI(index.c_str());
		for(unsigned j=0;j<XML_VIP_GRADE;++j)
			pdata->xmlvip[i].privile[j] = CTrans::STOI(rlt[j].c_str());
	}

	xmlConf.OutOfElem();
	if(!xmlConf.FindElem("vipprivilegesort"))
	{
		cout<<("vipprivilegesort node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();
	while(xmlConf.FindElem("item"))
	{
		string index = xmlConf.GetAttrib("index");
		string privile = xmlConf.GetData();
		if(index.empty() || privile.empty())
		{
			cout<<("vipprivilegesort config wrong 1 ")<<index<<endl;
			return 1;
		}
		privile = privile.substr(1,privile.length()-2);
		vector<string> rlt;
		String::Split(privile, ',', rlt);
		if(rlt.size() != XML_VIP_GRADE)
		{
			cout<<("vipprivilegesort config wrong 2 ")<<index<<endl;
			return 1;
		}

		unsigned i = CTrans::STOI(index.c_str()) - 1;
		if(i >= XML_VIP_PRL)
		{
			cout<<("vipprivilegesort config wrong 3 ")<<index<<endl;
			return 1;
		}
		for(unsigned j=0;j<XML_VIP_GRADE;++j)
			pdata->xmlvip[i].privileS[j] = CTrans::STOI(rlt[j].c_str());
	}

	xmlConf.OutOfElem();
	if(!xmlConf.FindElem("vipcharge"))
	{
		cout<<("vipcharge node wrong")<<endl;
		return 1;
	}
	string vipcharge = xmlConf.GetData();
	if(vipcharge.empty())
	{
		cout<<("vipcharge config wrong 1")<<endl;
		return 1;
	}
	vipcharge = vipcharge.substr(1,vipcharge.length()-2);
	vector<string> rlt;
	String::Split(vipcharge, ',', rlt);
	if(rlt.size() != XML_VIP_GRADE)
	{
		cout<<("vipcharge config wrong 2")<<endl;
		return 1;
	}
	for(unsigned j=0;j<XML_VIP_GRADE;++j)
		pdata->vipcharge[j] = CTrans::STOI(rlt[j].c_str());

	m_shVIP.SetInitDone();
	return 0;
}
int CDataXML::GetVIP(unsigned index, XMLVIP& vip)
{
	if(index > XML_VIP_PRL || !index)
		return R_ERR_PARAM;

	DataXMLVIP *pdata = (DataXMLVIP *)m_shVIP.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory *>(&(m_shVIP)), true);

	vip = pdata->xmlvip[index - 1];

	return 0;
}
int CDataXML::GetVIPCharge(unsigned vipcharge[XML_VIP_GRADE])
{
	DataXMLVIP *pdata = (DataXMLVIP *)m_shVIP.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory *>(&(m_shVIP)), true);

	memcpy(vipcharge, pdata->vipcharge, sizeof(vipcharge));

	return 0;
}
/*************************************/

int CDataXML::InitPreSummer()
{
	DataXMLPreSummer *pData
				= (DataXMLPreSummer *)m_shPreSummer.GetAddress();
	if (NULL == pData)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shPreSummer), true, LOCK_MAX);
	memset(pData, 0, sizeof(*pData));
	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
	{
		dataPath.append("/");
	}
	dataPath.append("newActivity.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<< "newActivity.xml path wrong: " << dataPath <<endl;
		error_log("load newActivity.xml failed. path: %s", dataPath.c_str());
		return R_ERROR;
	}

	if (! xmlConf.FindElem("content"))
	{
		std::cout << "newActivity.xml => content node error" << std::endl;
		error_log("newActivity.xml => content node error");
		return R_ERROR;
	}
	xmlConf.IntoElem();

	{
		if (! xmlConf.FindElem("summer"))
		{
			std::cout << "newActivity.xml => summer node error" << std::endl;
			error_log("newActivity.xml => summer node error");
			return R_ERROR;
		}

		string coststr = xmlConf.GetAttrib("cost");
		vector<string> coststrs;
		String::Split(coststr, ',', coststrs);
		if(coststrs.size() != XML_DATA_PRESUMMER_ITEMS)
		{
			cout << "newActivity.xml => cost size error" << endl;
			error_log("newActivity.xml => cost size error");
			return R_ERROR;
		}
		for(int i=0;i<XML_DATA_PRESUMMER_ITEMS;++i)
			pData->cost[i] = CTrans::STOI(coststrs[i]);

		xmlConf.IntoElem();

		int index = 0;
		while (xmlConf.FindElem("reward") && index < XML_DATA_PRESUMMER_ITEMS)
		{
			unsigned id = CTrans::STOI(xmlConf.GetAttrib("id"));

			if (id == 0)
			{
				error_log("newActivity.xml => id node error");
				continue;
			}

			std::string data = xmlConf.GetData();
			Json::Value jsonData;
			if (! Json::FromString(jsonData, data))
			{
				error_log("newActivity.xml => data error.1");
				return R_ERROR;
			}

			XMLPreSummerItem item;
			item.id = id;

			if (! item.equip.CopyFromJson(jsonData["reward"]["equip"]))
			{
				error_log("newActivity.xml => data error.2");
				return R_ERROR;
			}

			pData->items[index++] = item;
		}

		xmlConf.OutOfElem();
	}
	xmlConf.ResetMainPos();
	{
		if (! xmlConf.FindElem("summer2"))
		{
			std::cout << "newActivity.xml => summer2 node error" << std::endl;
			error_log("newActivity.xml => summer2 node error");
			return R_ERROR;
		}

		string coststr = xmlConf.GetAttrib("cost");
		vector<string> coststrs;
		String::Split(coststr, ',', coststrs);
		if(coststrs.size() != XML_DATA_PRESUMMER_ITEMS)
		{
			cout << "newActivity.xml => cost size error" << endl;
			error_log("newActivity.xml => cost size error");
			return R_ERROR;
		}
		for(int i=0;i<XML_DATA_PRESUMMER_ITEMS;++i)
			pData->cost2[i] = CTrans::STOI(coststrs[i]);

		xmlConf.IntoElem();

		int index = 0;
		while (xmlConf.FindElem("reward") && index < XML_DATA_PRESUMMER_ITEMS)
		{
			unsigned id = CTrans::STOI(xmlConf.GetAttrib("id"));

			if (id == 0)
			{
				error_log("newActivity.xml => id node error");
				continue;
			}

			std::string data = xmlConf.GetData();
			Json::Value jsonData;
			if (! Json::FromString(jsonData, data))
			{
				error_log("newActivity.xml => data error.1");
				return R_ERROR;
			}

			XMLPreSummerItem item;
			item.id = id;

			if (! item.equip.CopyFromJson(jsonData["reward"]["equip"]))
			{
				error_log("newActivity.xml => data error.2");
				return R_ERROR;
			}

			pData->items2[index++] = item;
		}

		xmlConf.OutOfElem();
	}
	xmlConf.ResetMainPos();
	{
		if (! xmlConf.FindElem("summer3"))
		{
			std::cout << "newActivity.xml => summer3 node error" << std::endl;
			error_log("newActivity.xml => summer3 node error");
			return R_ERROR;
		}

		string coststr = xmlConf.GetAttrib("cost");
		vector<string> coststrs;
		String::Split(coststr, ',', coststrs);
		if(coststrs.size() != XML_DATA_PRESUMMER_ITEMS)
		{
			cout << "newActivity.xml => cost size error" << endl;
			error_log("newActivity.xml => cost size error");
			return R_ERROR;
		}
		for(int i=0;i<XML_DATA_PRESUMMER_ITEMS;++i)
			pData->cost3[i] = CTrans::STOI(coststrs[i]);

		xmlConf.IntoElem();

		int index = 0;
		while (xmlConf.FindElem("reward") && index < XML_DATA_PRESUMMER_ITEMS)
		{
			unsigned id = CTrans::STOI(xmlConf.GetAttrib("id"));

			if (id == 0)
			{
				error_log("newActivity.xml => id node error");
				continue;
			}

			std::string data = xmlConf.GetData();
			Json::Value jsonData;
			if (! Json::FromString(jsonData, data))
			{
				error_log("newActivity.xml => data error.1");
				return R_ERROR;
			}

			XMLPreSummerItem item;
			item.id = id;

			if (! item.equip.CopyFromJson(jsonData["reward"]["equip"]))
			{
				error_log("newActivity.xml => data error.2");
				return R_ERROR;
			}

			pData->items3[index++] = item;
		}

		xmlConf.OutOfElem();
	}

	m_shPreSummer.SetInitDone();
	return R_SUCCESS;
}

XMLPreSummerItem& CDataXML::GetPreSummerItem(unsigned id, unsigned type)
{
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shPreSummer)), true);
	DataXMLPreSummer *pdata = (DataXMLPreSummer *)m_shPreSummer.GetAddress();
	if(NULL == pdata)
	{
		throw std::runtime_error("Get_pre_summer_sh_memory_error");
	}

	XMLPreSummerItem *items = type?(type==1?pdata->items2:pdata->items3):pdata->items;
	for (int i = 0; i < XML_DATA_PRESUMMER_ITEMS; i++)
	{
		if (items[i].id == id)
		{
			return items[i];
		}
	}

	throw std::runtime_error("Get_cfg_by_id_error");
}
unsigned CDataXML::GetPreSummerCost(unsigned index, unsigned type)
{
	if(index >= XML_DATA_PRESUMMER_ITEMS)
		throw std::runtime_error("Get_cfg_by_index_error");

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shPreSummer)), true);
	DataXMLPreSummer *pdata = (DataXMLPreSummer *)m_shPreSummer.GetAddress();
	if(NULL == pdata)
	{
		throw std::runtime_error("Get_pre_summer_sh_memory_error");
	}

	return type?(type==1?pdata->cost2[index]:pdata->cost3[index]):pdata->cost[index];
}
////////////////////////////////////////////////////////////////////////
int XMLTempleItem::GetRandomEquipIndex()
{
	int nTotal = 0;
	for (int i = 0; i < XML_DATA_GOODS_CNT; i++)
	{
		nTotal += rate[i];
	}

	int nRandom = Math::GetRandomInt(nTotal);

	int index = 0;
	for (int i = 0; i < XML_DATA_GOODS_CNT; i++)
	{
		if (nRandom < rate[i])
		{
			//index = i;
			return i;
		}

		nRandom -= rate[i];
	}

	throw std::runtime_error("random_equip_error");
}

int CDataXML::InitTemple()
{
	try
	{
		return  DataXMLTemplePray(m_shTemple, "prayconfig.xml").Initialize();
	}
	catch(const std::exception& e)
	{
		std::cout << "[InitTemple]Error: " << e.what() << std::endl;
		return R_ERROR;
	}
	return 0;
}

int CDataXML::InitNewRechargeBag()
{
	try
	{
		return DataXmlNewRechargeBagUnit(m_shNewRecharge, "newActivity.xml").Initialize();
	}
	catch(const std::exception& e)
	{
		std::cout << "[InitNewRechargeBag]Error: " << e.what() << std::endl;
		return R_ERROR;
	}
	return 0;
}

XMLTempleItem CDataXML::GetTemplePrayItem(unsigned id)
{
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shTemple)), true);
	DataXMLTemple *pdata = (DataXMLTemple *)m_shTemple.GetAddress();
	if(NULL == pdata)
	{
		throw std::runtime_error("Get_temple_sh_memory_error");
	}

	for (int i = 0;  i < XML_DATA_TEMPLE_ITEMS; ++i)
	{
		if (pdata->items[i].id == id)
		{
			return pdata->items[i];
		}
	}

	error_log("Get temple_item_error. id=%d", id);
	throw std::runtime_error("Can't_get the_temple_pray_item");
}

XMLNewRechargeRewardItem CDataXML::GetNewRechargeRewardItem(unsigned id)
{
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shNewRecharge)), true);
	DataXMLNewRecharge *pdata = (DataXMLNewRecharge*)m_shNewRecharge.GetAddress();
	if (NULL == pdata)
	{
		throw std::runtime_error("Get_m_shNewRecharge_sh_memory_error");
	}

	for (int  i = 0; i < XML_DATA_NEW_RECHARGE_ITEMS; ++i)
	{
		if (pdata->items[i].id == id)
		{
			return pdata->items[i];
		}
	}

	error_log("Get item_error. id=%d", id);
	throw std::runtime_error("Get_the_NewRechargeRewardItem_error");
}


std::vector<std::string> XMLNewRechargeRewardItem::GetHeros() const
{
	std::vector<std::string> result;

	for (int i = 0; i < XML_DATA_NEW_RECHARGE_REWARD_ITEMS; ++i)
	{
		if (items[i].IsHero())
		{
			for (unsigned k = 0; k < items[i].m_nCnt; ++k)
			{
				result.push_back(CDataXML::Hero2Str(items[i].m_nId));
			}
		}
	}

	return result;
}

////////////////////////////////////////////////////////////
int CDataXML::InitGroupBuyDaily()
{
	try
	{
		return DataXmlGroupBuyDailyUnit(m_shGroupBuyDaily, "sggiftbagconfig.xml").Initialize();
	}
	catch(const std::exception& e)
	{
		std::cout << "[InitGroupBuyDaily]Error: " << e.what() << std::endl;
		return R_ERROR;
	}
	return 0;
}

void CDataXML::GetGroupBuyDailyBuyTtem(DataXMLGroupBuyDailyBuyItem& result)
{
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shGroupBuyDaily)), true);
	DataXMLGroupBuyDaily *pdata = (DataXMLGroupBuyDaily*)m_shGroupBuyDaily.GetAddress();

	result = pdata->buyItem;
}

void CDataXML::GetGroupBuyDailyBuyReward(int id, DataXMLGroupBuyDailyReward& result)
{
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shGroupBuyDaily)), true);
	DataXMLGroupBuyDaily *pdata = (DataXMLGroupBuyDaily*)m_shGroupBuyDaily.GetAddress();

	for (unsigned i = 0; i < DataXMLGroupBuyDaily::REWARD_CNT; ++i)
	{
		if (pdata->rewards[i].id == id)
		{
			result = pdata->rewards[i];
			return ;
		}
	}

	throw std::runtime_error("GetGroupBuyDailyBuyReward::id_error");
}

////////////////////////////////////////////////////////////////////////
int CDataXML::InitLittleRecharge()
{
	try
	{
		return DataXmlLittleRechargeUnit(m_shLittleRecharge, "activityconfig.xml").Initialize();
	}
	catch(const std::exception& e)
	{
		std::cout << "[InitLittleRecharge]Error: " << e.what() << std::endl;
		return R_ERROR;
	}
	return 0;
}

void CDataXML::GetLittleRechargeReward(bool is4399, unsigned zoneId, DataXMLLittleRechargeZone& result)
{
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shLittleRecharge)), true);
	DataXMLLittleRecharge *pdata = (DataXMLLittleRecharge*)m_shLittleRecharge.GetAddress();
	DataXMLLittleRechargeZone* pZone = NULL;
	if (is4399)
	{
		pZone = pdata->zone4399;
	}
	else
	{
		pZone = pdata->zoneGeneral;
	}

	for (int i = 0; i < DataXMLLittleRecharge::ZONE_CNT; i++)
	{
		if (zoneId >= pZone[i].zoneStart && zoneId <= pZone[i].zoneEnd)
		{
			result = pZone[i];
			return;
		}
	}

	error_log("Is4399: %d, zoneId: %u", is4399, zoneId);
	throw std::runtime_error("no_cfg_zone_id");
}

////////////////////////////////////////////////////////////////////////
int CDataXML::InitMonthGiftBag()
{
	try
	{
		return DataXmlMonthGiftBagUnit(m_shMonthGiftBag, "activityconfig.xml").Initialize();
	}
	catch(const std::exception& e)
	{
		std::cout << "[InitMonthGiftBag]Error: " << e.what() << std::endl;
		return R_ERROR;
	}
	return 0;
}

unsigned CDataXML::GetMonthGiftBagEquipId(bool is4399, unsigned zoneid, unsigned index)
{
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shMonthGiftBag)), true);

	DataXMLMonthGiftBag *pdata = (DataXMLMonthGiftBag*)m_shMonthGiftBag.GetAddress();
	if (is4399)
	{
		for (int i = 0; i < DataXMLMonthGiftBag::ZONE_CNT; ++i)
		{
			if (pdata->zones[i].InZone(zoneid))
			{
				return pdata->zones4399[i].GetEquipId(index);
			}
		}
	}
	else
	{
		for (int i = 0; i < DataXMLMonthGiftBag::ZONE_CNT; ++i)
		{
			if (pdata->zones[i].InZone(zoneid))
			{
				return pdata->zones[i].GetEquipId(index);
			}
		}

	}

	throw std::runtime_error("param_zoneid_error");
}

unsigned DataXMLMonthGiftBagZone::GetEquipId(unsigned index)
{
	if (index >= DataXMLMonthGiftBagZone::EQUIP_ITEMS)
	{
		throw std::runtime_error("index_params_error");
	}

	return equips[index];
}

bool DataXMLMonthGiftBagZone::InZone(unsigned zoneId) const
{
	return (zoneId >= zoneStart) && (zoneId <= zoneEnd);
}

////////////////////////////////////////////////////////////////////////
int CDataXML::InitCombinedShop()
{
	try
	{
		return DataXmlCombinedShopUnit(m_shCombinedShop, "zhsd.xml").Initialize();
	}
	catch(const std::exception& e)
	{
		std::cout << "[InitCombinedShop]Error: " << e.what() << std::endl;
		return R_ERROR;
	}
	return 0;
}

void CDataXML::GetCombinedShopEquipItem(unsigned index, DataXMLCombinedShopItem& item)
{
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shCombinedShop)), true);

	DataXMLCombinedShop *pdata = (DataXMLCombinedShop*)m_shCombinedShop.GetAddress();


	if (index >= DataXMLCombinedShop::ITEMS_CNT)
	{
		throw std::runtime_error("index_params_error");
	}

	item = pdata->items[index];
}

unsigned DataXMLCombinedShopItem::GetEquipCnt(unsigned eqid)
{
	for (int i = 0; i < DataXMLCombinedShopItem::EQUIP_CNT; ++i)
	{
		if (equipsId[i] > 0 && equipsId[i] == eqid)
		{
			return equipsCnt[i];
		}
	}

	throw std::runtime_error("eqid_params_error");
}
////////////////////////////////////////////////////////////////////////
int CDataXML::InitNewerAdvance()
{
	try
	{
		return DataXmlNewerAdvanceUnit(m_shNewerAdvance, "sggiftbagconfig.xml").Initialize();
	}
	catch(const std::exception& e)
	{
		std::cout << "[InitNewerAdvance]Error: " << e.what() << std::endl;
		return R_ERROR;
	}
	return 0;
}

void CDataXML::GetNewerAdvanceItem(unsigned id, DataXMLNewerAdvanceItem& item)
{
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shNewerAdvance)), true);

	DataXMLNewerAdvance *pdata = (DataXMLNewerAdvance*)m_shNewerAdvance.GetAddress();

	for (int i = 0; i < DataXMLNewerAdvance::ITEMS_CNT; ++i)
	{
		if (pdata->items[i].id == id)
		{
			item = pdata->items[i];
			return ;
		}
	}

	throw std::runtime_error("params_id_error");
}

////////////////////////////////////////////////////////////////////////
int CDataXML::InitTreasureHuntExchange()
{
	try
	{
		return DataXmlTreasureHuntUnit(m_shTreasureHuntExchange, "treasurehuntconfig.xml").Initialize();
	}
	catch(const std::exception& e)
	{
		std::cout << "[InitTreasureHuntExchange]Error: " << e.what() << std::endl;
		return R_ERROR;
	}
	return 0;
}

void CDataXML::GetTreasureHuntExchangeItem(unsigned index,  bool isPoint, DataXMLTreasureHuntExchangeItem& item)
{
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shTreasureHuntExchange)), true);

	DataXMLTreasureHuntExchange *pdata = (DataXMLTreasureHuntExchange*)m_shTreasureHuntExchange.GetAddress();
	if (index >= DataXMLTreasureHuntExchange::ITEMS_CNT)
	{
		throw std::runtime_error("index_cfg_params_error");
	}

	if (isPoint)
	{
		item = pdata->point[index];
	}
	else
	{
		item = pdata->jade[index];
	}
}

////////////////////////////////////////////////////////////////////////
int CDataXML::InitChristmas()
{
	try
	{
		return DataXmlChristmasUint(m_shChristmas, "activityconfig.xml").Initialize();
	}
	catch(const std::exception& e)
	{
		std::cout << "[InitChristmas]Error: " << e.what() << std::endl;
		return R_ERROR;
	}

	return 0;
}

void CDataXML::GetChristmasExtraItem(unsigned id, DataXMLChristmasExtraItem& item)
{
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shChristmas)), true);
	DataXMLChristmas *pdata = (DataXMLChristmas*)m_shChristmas.GetAddress();

	for (int i = 0; i < DataXMLChristmas::EXTRA_ITEMS; i++)
	{
		if (pdata->extra[i].id == id)
		{
			item = pdata->extra[i];
			return ;
		}
	}

	throw std::runtime_error("id_extra_params_error");
}

void CDataXML::GetChristmasEggItem(unsigned id, DataXMLChristmasEgg& item)
{
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shChristmas)), true);
	DataXMLChristmas *pdata = (DataXMLChristmas*)m_shChristmas.GetAddress();

	for (int i = 0; i < DataXMLChristmas::EGG_ITEMS; i++)
	{
		if (pdata->egg[i].id == id)
		{
			item = pdata->egg[i];
			return ;
		}
	}

	throw std::runtime_error("id_egg_params_error");
}

////////////////////////////////////////////////////////////////////////
//积分互换
int CDataXML::InitPointExchange()
{
	try
	{
		return DataXmlPointExchangeUint(m_shPointExchange, "pointrewardconfig.xml").Initialize();
	}
	catch(const std::exception& e)
	{
		std::cout << "[InitPointExchange]Error: " << e.what() << std::endl;
		return R_ERROR;
	}

	return 0;
}

void CDataXML::GetPointExchangeItem(unsigned index, DataXMLPointExchageRewardItem& item)
{
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shPointExchange)), true);
	DataXMLPointExchange *pdata = (DataXMLPointExchange*)m_shPointExchange.GetAddress();

	if (index >= DataXMLPointExchange::ITEM_CNT)
	{
		throw std::runtime_error("get_point_exchage_item_index_params_error");
	}

	item = pdata->items[index];
}

unsigned DataXMLPointCutPrice::LevelByPoint(unsigned point) const
{
	for (int i = LEVLE_CNT - 1; i >= 0; i--)
	{
		if (point >= lvlInt[i])
		{
			return i + 1;
		}
	}

	return 0;
}

void CDataXML::GetPointCutPriceItem(unsigned id, DataXMLPointCutPriceItem& item)
{
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shPointExchange)), true);
	DataXMLPointExchange *pdata = (DataXMLPointExchange*)m_shPointExchange.GetAddress();

	for (int i = 0; i < DataXMLPointCutPrice::ITEM_CNT; i++)
	{
		if (pdata->cut_price.items[i].id == id)
		{
			item = pdata->cut_price.items[i];
			return ;
		}
	}

	throw std::runtime_error("get_point_cut_price_item_id_params_error");
}

unsigned CDataXML::GetPointCutPriceLvl(unsigned point)
{
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shPointExchange)), true);
	DataXMLPointExchange *pdata = (DataXMLPointExchange*)m_shPointExchange.GetAddress();

	return pdata->cut_price.LevelByPoint(point);
}

////////////////////////////////////////////////////////////////////////
int CDataXML::InitBuildSkin()
{
	try
	{
		return DataXmlBuildingSkinUnit(m_shBuildingSkin, "activityconfig.xml").Initialize();
	}
	catch(const std::exception& e)
	{
		std::cout << "[InitBuildSkin]Error: " << e.what() << std::endl;
		return R_ERROR;
	}

	return 0;
}

void CDataXML::GetBuildSkinBuy(unsigned id, DataXMLBuildingSkinBuy& buy_item)
{
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shBuildingSkin)), true);
	DataXMLBuildingSkin *pdata = (DataXMLBuildingSkin*)m_shBuildingSkin.GetAddress();

	for (int i = 0; i < DataXMLBuildingSkin::ITEM_CNT; i++)
	{
		if (id == pdata->buys[i].id)
		{
			buy_item = pdata->buys[i];
			return ;
		}
	}

	throw std::runtime_error("get_building_skin_buy_item_id_params_error");
}

void CDataXML::GetBuildSkinRelet(unsigned id, unsigned type, DataXMLBuildingSkinReletItem& relet)
{
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shBuildingSkin)), true);
	DataXMLBuildingSkin *pdata = (DataXMLBuildingSkin*)m_shBuildingSkin.GetAddress();

	for (int i = 0; i < DataXMLBuildingSkin::ITEM_CNT; i++)
	{
		if (id == pdata->relets[i].id)
		{
			for (int k = 0; k < DataXMLBuildingSkinRelet::ITEM_CNT; k++)
			{
				if (pdata->relets[i].items[k].id == type)
				{
					relet = pdata->relets[i].items[k];
					return;
				}
			}

			throw std::runtime_error("get_building_skin_relet_item_type_params_error");
		}
	}

	throw std::runtime_error("get_building_skin_relet_item_id_params_error");
}
////////////////////////////////////////////////////////////////////////
int CDataXML::InitTutorLogin()
{
	try
	{
		return DataXmlTutorLoginUint(m_shTutorLogin, "activityconfig.xml").Initialize();
	}
	catch(const std::exception& e)
	{
		std::cout << "[InitTutorLogin]Error: " << e.what() << std::endl;
		return R_ERROR;
	}

	return 0;
}

void CDataXML::GetTutorLoginItem(unsigned id, DataXMLTutorLoginItem& result)
{
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shTutorLogin)), true);
	DataXMLTutorLogin *pdata = (DataXMLTutorLogin*)m_shTutorLogin.GetAddress();

	for (int i = 0; i < DataXMLTutorLogin::ITEM_CNT; i++)
	{
		if (id == pdata->items[i].id)
		{
			result = pdata->items[i];
			return ;
		}
	}

	throw std::runtime_error("get_turor_login_item_id_params_error");
}
////////////////////////////////////////////////////////////////////////
int CDataXML::InitImperialGift()
{
	try
	{
		return DataXmlImperialGiftUnit(m_shImperialGift, "activityconfig.xml").Initialize();
	}
	catch(const std::exception& e)
	{
		std::cout << "[InitTutorLogin]Error: " << e.what() << std::endl;
		return R_ERROR;
	}

	return 0;
}

void CDataXML::GetImperialGift(unsigned id, DataXMLImperialGiftItem& result)
{
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shImperialGift)), true);
	DataXMLImperialGift *pdata = (DataXMLImperialGift*)m_shImperialGift.GetAddress();

	for (int i = 0; i < DataXMLImperialGift::ITEM_CNT; i++)
	{
		if (pdata->items[i].id == id)
		{
			result = pdata->items[i];
			return ;
		}
	}

	throw std::runtime_error("get_imperial_gift_id_params_error");
}
//////////////////////////////////////////////////////////////////////////////////
int CDataXML::InitTimeLimitUpgrade()
{
	try
	{
		return DataXmlTimeLimitUpgradeUnit(m_shTimeLimitUpgrade, "wonderfulconfig.xml").Initialize();
	}
	catch(const std::exception& e)
	{
		std::cout << "[InitTimeLimitUpgrade]Error: " << e.what() << std::endl;
		return R_ERROR;
	}
	return 0;
}

void CDataXML::GetTimeLimitUpgrade(unsigned index, DataXMLTimeLimitUpgradeItem& result)
{
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shTimeLimitUpgrade)), true);
	DataXMLTimeLimitUpgrade *pdata = (DataXMLTimeLimitUpgrade*)m_shTimeLimitUpgrade.GetAddress();
	if (index >= DataXMLTimeLimitUpgrade::ITEM_CNT)
	{
		throw std::runtime_error("get_time_limit_upgrade_item_index_error");
	}

	result = pdata->items[index];
}

//////////////////////////////////////////////////////////////////////////////
int CDataXML::InitYearFortune()
{
	try
	{
		return DataXmlYearFortuneUnit(m_shYearFortune, "newActivity.xml").Initialize();
	}
	catch(const std::exception& e)
	{
		std::cout << "[InitYearFortune]Error: " << e.what() << std::endl;
		return R_ERROR;
	}
	return 0;
}

DataXMLYearFortuneLib CDataXML::GetYearFortuneLib(unsigned id)
{
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shYearFortune)), true);
	DataXMLYearFortune *pdata = (DataXMLYearFortune*)m_shYearFortune.GetAddress();

	for (int i = 0; i < DataXMLYearFortune::LIB_CNT; i++)
	{
		if (pdata->libs[i].id == id)
		{
			return pdata->libs[i];
		}
	}

	throw std::runtime_error("get_year_fortune_lib_id_error");
}


int  CDataXML::GetYearFortuneNeedPoint(unsigned index)
{
	const int point_talbe[DataXMLYearFortune::STAGE_CNT] = {40, 70, 100, 150, 200, 260, 330};
	if (index >= DataXMLYearFortune::STAGE_CNT)
	{
		throw std::runtime_error("get_year_fortune_need_point_index_error");
	}

	return point_talbe[index];
}

int DataXMLYearFortuneLib::GetRandomItemOfId() const
{
	int nTotal = 0;
	for (int i = 0; i < DataXMLYearFortuneLib::ITEM_CNT; i++)
	{
		nTotal += items[i].rate;
	}

	if (nTotal == 0)
	{
		throw std::runtime_error("config_rate_error");
	}

	int nRandomVal = Math::GetRandomInt(nTotal);
	for (int i = 0; i < DataXMLYearFortuneLib::ITEM_CNT; i++)
	{
		if (nRandomVal < items[i].rate)
		{
			return items[i].id;
		}

		nRandomVal -= items[i].rate;
	}

	throw std::runtime_error("random_reward_logic_error");
}

DataXMLYearFortuneItem DataXMLYearFortuneLib::GetItem(unsigned id)
{
	for (int i = 0; i < DataXMLYearFortuneLib::ITEM_CNT; i++)
	{
		if (id == items[i].id)
		{
			return items[i];
		}
	}

	throw std::runtime_error("year_fortune_lib_get_item_id_error");
}

////////////////////////////////////////////////////////////////////////
int CDataXML::InitWeaponSoulCost()
{
	DataXMLpartpowerconfig *pData
			= (DataXMLpartpowerconfig *)m_shpartpowerconfig.GetAddress();
	if (NULL == pData)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shpartpowerconfig), true, LOCK_MAX);
	memset(pData, 0, sizeof(*pData));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
	{
		dataPath.append("/");
	}
	dataPath.append("partpowerconfig.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<< "partpowerconfig.xml path wrong: " << dataPath <<endl;
		error_log("load partpowerconfig.xml failed. path: %s", dataPath.c_str());
		return R_ERROR;
	}

	if (! xmlConf.FindElem("content"))
	{
		std::cout << "partpowerconfig.xml => content node error" << std::endl;
		error_log("partpowerconfig.xml => content node error");
		return R_ERROR;
	}
	xmlConf.IntoElem();

	if (! xmlConf.FindElem("costs"))
	{
		std::cout << "partpowerconfig.xml => costs node error" << std::endl;
		error_log("partpowerconfig.xml => costs node error");
		return R_ERROR;
	}
	xmlConf.IntoElem();

	int index = 0;
	while (xmlConf.FindElem("cost") && index < XML_WEAPON_SOUL_ITEMS_MAX)
	{
		unsigned id = CTrans::STOI(xmlConf.GetAttrib("id"));
		unsigned cost = CTrans::STOI(xmlConf.GetAttrib("cost"));
		float discount = CTrans::STOF(xmlConf.GetAttrib("discount"));

		if (id == 0)
		{
			error_log("partpowerconfig.xml => id node error");
			continue;
		}

		XMLWeaponSoulCostItem item;
		item.id = id;
		item.cost = cost;
		item.discount = discount;

		pData->items[index++] = item;

	}
	xmlConf.OutOfElem();

	std::cout << "Init items: " << index << std::endl;

	m_shpartpowerconfig.SetInitDone();


	return R_SUCCESS;
}

int CDataXML::GetWeaponSoulCostItem(unsigned id, XMLWeaponSoulCostItem& item)
{
	std::map<unsigned, unsigned>::iterator itor = m_mapWeaponSoulCost.find(id);
	if (itor == m_mapWeaponSoulCost.end())
	{
		return R_ERROR;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shpartpowerconfig)), true);
	DataXMLpartpowerconfig *pdata = (DataXMLpartpowerconfig *)m_shpartpowerconfig.GetAddress();
	if(NULL == pdata)
	{
		return R_ERR_DB;
	}

	if (itor->second < XML_WEAPON_SOUL_ITEMS_MAX)
	{
		item = pdata->items[itor->second];
	}

	return R_SUCCESS;
}

/**************************************/
int CDataXML::InitSignInReward()
{
	DataXMLsgsigninnewconfig *pData
		= (DataXMLsgsigninnewconfig *)m_shsgsigninnewconfig.GetAddress();
	if (NULL == pData)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shsgsigninnewconfig), true, LOCK_MAX);
	memset(pData, 0, sizeof(*pData));
	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
	{
		dataPath.append("/");
	}
	dataPath.append("sgsigninnewconfig.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<< "sgsigninnewconfig.xml path wrong: " << dataPath <<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout << ("sgsigninnewconfig.xml => content node error") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	if (!xmlConf.FindElem("signin"))
	{
		cout << ("sgsigninnewconfig.xml => signin node error") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	int number = 0;
	while(xmlConf.FindElem("reward") && number < SIGNIN_REWARDS_NUM)
	{
		Json::Value jsonRewardsContent, jsonReward;
		std::string szReward = xmlConf.GetData();
		if (! Json::FromString(jsonRewardsContent, xmlConf.GetData()))
		{
			cout << "sgsigninnewconfig.xml => [" << number <<"] reward.1 node error" << endl;
			continue;
		}

#pragma push_macro("GetObject")
#undef GetObject
		if (! Json::GetObject(jsonRewardsContent, "reward", jsonReward))
		{
			cout << "sgsigninnewconfig.xml => [" << number <<"] reward.2 node error" << endl;
			continue;
		}

		if (! Json::GetInt(jsonReward, "gold", pData->rewards[number].gold))
		{
			cout << "sgsigninnewconfig.xml => [" << number <<"] gold node error" << endl;
			continue;
		}

		if (! Json::GetInt(jsonReward, "prosper", pData->rewards[number].prosper))
		{
			cout << "sgsigninnewconfig.xml => [" << number <<"] prosper node error" << endl;
			continue;
		}


		Json::Value jsonEquips;
		GiftEquipment equip;

		for (int k = 0; k < SIGNIN_EQUIP_ITEMS; k++)
		{
			std::stringstream equipKey;
			equipKey << "equip" << k + 1;

			if (! Json::GetObject(jsonReward, equipKey.str().c_str(), jsonEquips))
			{
				break;
			}

			if (! equip.CopyFromJson(jsonEquips))
			{
				cout << "sgsigninnewconfig.xml => [" << number << "] init equip error" << endl;
				break;
			}

			pData->rewards[number].equipCnt = k + 1;
			pData->rewards[number].equips[k] = equip;
		}

		std::cout << "Gold: " << pData->rewards[number].gold
				<< " prosper:" << pData->rewards[number].prosper
				<< " equipCnt: " << pData->rewards[number].equipCnt << std::endl;

		++number;
	}

	if (number != SIGNIN_REWARDS_NUM)
	{
		cout << ("sgsigninnewconfig.xml => levels error") << endl;
		return 1;
	}

#pragma pop_macro("GetObject")

	m_shsgsigninnewconfig.SetInitDone();

	return 0;
}

//------------------------------------------------
int CDataXML::InitInviteReward()
{
	DataXMLsginvitegiftconfig *pdata = (DataXMLsginvitegiftconfig *)m_shsginvitegiftconfig.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shsginvitegiftconfig), true,LOCK_MAX);

	memset(pdata, 0, sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
	{
		dataPath.append("/");
	}
	dataPath.append("sginvitegiftconfig.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<< "sginvitegiftconfig.xml path wrong: " << dataPath <<endl;
		return R_ERROR;
	}

	if (! xmlConf.FindElem("content"))
	{
		std::cout << "sginvitegiftconfig.xml => content node error" << std::endl;
		return R_ERROR;
	}
	xmlConf.IntoElem();

	if (! xmlConf.FindElem("day"))
	{
		std::cout << "sginvitegiftconfig.xml => day node error" << std::endl;
		return R_ERROR;
	}

	xmlConf.IntoElem();
	if (! xmlConf.FindElem("reward"))
	{
		std::cout << "sginvitegiftconfig.xml => day:reward node.1 error" << std::endl;
		return R_ERROR;
	}

	Json::Value jsonData;
	if (! Json::FromString(jsonData, xmlConf.GetData()))
	{
		std::cout << "sginvitegiftconfig.xml => day:reward node.2 error" << std::endl;
		return R_ERROR;
	}

	Json::Value jsonEquips;
	GiftEquipment equip;
	for (int k = 0; k < XML_INVITE_REWARD_ITEM_MAX; k++)
	{
		std::stringstream equipKey;
		equipKey << "equip" << k + 1;

		if (! Json::GetObject(jsonData["reward"], equipKey.str().c_str(), jsonEquips))
		{
			break;
		}

		if (! equip.CopyFromJson(jsonEquips))
		{
			std::cout << "sginvitegiftconfig.xml => day:reward:equip node error" << std::endl;
			break;
		}

		pdata->dayItem.equips[pdata->dayItem.equipsCnt++] = equip;
	}

	xmlConf.OutOfElem();
	if (! xmlConf.FindElem("level"))
	{
		std::cout << "sginvitegiftconfig.xml => level node error" << std::endl;
		return R_ERROR;
	}

	xmlConf.IntoElem();
	int levelCnt = 0;
	while (xmlConf.FindElem("reward") && levelCnt < XML_INVITE_LEVEL_ITEMS_MAX)
	{
		std::string szId = xmlConf.GetAttrib("id");
		std::string szLevel = xmlConf.GetAttrib("level");
		std::string szNumber = xmlConf.GetAttrib("num");

		if (szId.empty() || szLevel.empty() || szNumber.empty())
		{
			std::cout << "sginvitegiftconfig.xml => Id or level or number is null" << std::endl;
			continue;
		}

		if (! Json::FromString(jsonData, xmlConf.GetData()))
		{
			std::cout << "sginvitegiftconfig.xml => level:reward node " << szId << " error" << std::endl;
			continue;
		}

		pdata->levelItems[levelCnt].id = CTrans::STOI(szId.c_str());
		pdata->levelItems[levelCnt].level = CTrans::STOI(szLevel.c_str());
		pdata->levelItems[levelCnt].number = CTrans::STOI(szNumber.c_str());

		if (0 == pdata->levelItems[levelCnt].id)
		{
			std::cout << "sginvitegiftconfig.xml => Id is zero: " << levelCnt << std::endl;
		}


		for (int k = 0; k < XML_INVITE_REWARD_ITEM_MAX; k++)
		{
			std::stringstream equipKey;
			equipKey << "equip" << k + 1;

			if (! Json::GetObject(jsonData["reward"], equipKey.str().c_str(), jsonEquips))
			{
				break;
			}

			if (! equip.CopyFromJson(jsonEquips))
			{
				std::cout << "sginvitegiftconfig.xml => level:reward:equip node " << szId << " error" << std::endl;
				break;
			}

			int index = pdata->levelItems[levelCnt].equipsCnt;
			pdata->levelItems[levelCnt].equips[index] = equip;
			++pdata->levelItems[levelCnt].equipsCnt;
		}

		++levelCnt;
	}

	std::cout << "level cnt: " << levelCnt << std::endl;
	std::cout << "sginvitegiftconfig.xml => parse success !" << std::endl;

	m_shsginvitegiftconfig.SetInitDone();

	return 0;
}

/*************************************/
int CDataXML::InitGiftBag()
{
	DataXMLsggiftbagconfig *pdata = (DataXMLsggiftbagconfig *)m_shsggiftbagconfig.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shsggiftbagconfig), true,LOCK_MAX);

	memset(pdata,0,sizeof(*pdata));

	Json::FastWriter writer;
	Json::Reader reader;
	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("sggiftbagconfig.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("sggiftbagconfig.xml path wrong")<<endl;
		return 1;
	}
	if(!xmlConf.FindElem("content"))
	{
		cout<<("sggiftbagconfig.xml content node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();

	if(!xmlConf.FindElem("level"))
	{
		cout<<("sggiftbagconfig.xml level node wrong")<<endl;
		return 1;
	}

	xmlConf.IntoElem();
	int i = 0;
	while(xmlConf.FindElem("reward"))
	{
		Json::Value Data;
		string id = xmlConf.GetAttrib("id");
		string level = xmlConf.GetAttrib("level");
		string reward_data = xmlConf.GetData();
		if(id.empty()  || reward_data.empty())
		{
			cout<<("sggiftbagconfig.xml levelpackage id wrong:")<<id<<endl;
			return 1;
		}

		pdata->GiftBagLevel[i].id = CTrans::STOI(id.c_str());
		pdata->GiftBagLevel[i].level = CTrans::STOI(level.c_str());
		memcpy(pdata->GiftBagLevel[i].data, reward_data.c_str(), reward_data.length());
		i++;
	}
	xmlConf.OutOfElem();

	if(!xmlConf.FindElem("levelpackage"))
	{
		cout<<("sggiftbagconfig.xml levelpackage node wrong")<<endl;
		return 1;
	}

	int number = 0;
	xmlConf.IntoElem();
	while(xmlConf.FindElem("reward"))
	{
		Json::Value Data;
		string id = xmlConf.GetAttrib("id");
		string reward_data = xmlConf.GetData();
		if(id.empty()  || reward_data.empty())
		{
			cout<<("sggiftbagconfig.xml levelpackage id wrong:")<<id<<endl;
			return 1;
		}

		Json::Value json_reward;
		json_reward.clear();
		reader.parse(reward_data,json_reward);
		Json::Value reward = json_reward["reward"];

		Json::Value::Members members(reward.getMemberNames());

		pdata->GiftBag[number].id = CTrans::STOI(id.c_str());

		int index = 0;
		for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it)
		{
			string type = *it;
			string data = writer.write(reward[*it]);
			memcpy(pdata->GiftBag[number].gift[index].type,type.c_str(),sizeof(pdata->GiftBag[number].gift[index].type) - 1);
			memcpy(pdata->GiftBag[number].gift[index].data,data.c_str(),sizeof(pdata->GiftBag[number].gift[index].data) - 1);
			pdata->GiftBag[number].gift[index].flag = 1;
			++index;
		}
		++number;
	}

	xmlConf.OutOfElem();
	if(!xmlConf.FindElem("equippackage"))
	{
		cout<<("sggiftbagconfig.xml equippackage wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();
	while(xmlConf.FindElem("reward"))
	{
		string id = xmlConf.GetAttrib("id");
		string reward_data = xmlConf.GetData();
		if(id.empty() || reward_data.empty())
		{
			cout<<("sggiftbagconfig.xml equippackage id wrong:")<<id<<endl;
			return 1;
		}

		Json::Value json_reward;
		json_reward.clear();
		reader.parse(reward_data,json_reward);
		Json::Value reward = json_reward["reward"];

		Json::Value::Members members(reward.getMemberNames());

		pdata->GiftBag[number].id = CTrans::STOI(id.c_str());


		int index = 0;
		for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it)
		{
			string type = *it;
			string data = writer.write(reward[*it]);
			memcpy(pdata->GiftBag[number].gift[index].type,type.c_str(),sizeof(pdata->GiftBag[number].gift[index].type) - 1);
			memcpy(pdata->GiftBag[number].gift[index].data,data.c_str(),sizeof(pdata->GiftBag[number].gift[index].data) - 1);
			pdata->GiftBag[number].gift[index].flag = 1;
			++index;
		}

		++number;
	}

	xmlConf.OutOfElem();
	if(!xmlConf.FindElem("luckybox"))
	{
		cout<<("sggiftbagconfig.xml luckybox wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();
	while(xmlConf.FindElem("box"))
	{
		string id = xmlConf.GetAttrib("id");
		string box_data = xmlConf.GetData();
		if(id.empty() || box_data.empty())
		{
			cout<<("sggiftbagconfig.xml luckybox id wrong:")<<id<<endl;
			return 1;
		}

		Json::Value json_box;
		reader.parse(box_data,json_box);

		Json::Value reward;
		reward = json_box["reward"];
		Json::Value::Members members(reward.getMemberNames());

		pdata->GiftBag[number].id = CTrans::STOI(id.c_str());

		Json::Value json_rate;
		json_rate = json_box["rate"];

		Json::Value json_ratekey;
		json_ratekey = json_box["ratekey"];


		int index = 0;
		for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it)
		{
			string type = *it;
			string data = writer.write(reward[*it]);
			memcpy(pdata->GiftBag[number].gift[index].type,type.c_str(),sizeof(pdata->GiftBag[number].gift[index].type) - 1);
			memcpy(pdata->GiftBag[number].gift[index].data,data.c_str(),sizeof(pdata->GiftBag[number].gift[index].data) - 1);
			pdata->GiftBag[number].gift[index].flag = 1;

			for(int i =0; i < json_ratekey.size();i++)
			{
				string rate_key = json_ratekey[i].asString();
				if(rate_key == type)
				{
					pdata->GiftBag[number].gift[index].rate = json_rate[i].asInt();
					break;
				}
			}
			++index;
		}
		++number;
	}

	xmlConf.OutOfElem();
	if(!xmlConf.FindElem("randommoney"))
	{
		cout<<("sggiftbagconfig.xml randommoney wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();
	while(xmlConf.FindElem("reward"))
	{
		string id = xmlConf.GetAttrib("id");
		string box_data = xmlConf.GetData();
		if(id.empty() || box_data.empty())
		{
			cout<<("sggiftbagconfig.xml randommoney id wrong:")<<id<<endl;
			return 1;
		}

		pdata->GiftBag[number].id = CTrans::STOI(id.c_str());
		Json::Value json_box;
		reader.parse(box_data,json_box);
		Json::Value reward;
		reward = json_box["reward"];
		Json::Value::Members members(reward.getMemberNames());
		int index = 0;
		for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it)
		{
			string type = *it;
			string data = writer.write(reward[*it]);
			memcpy(pdata->GiftBag[number].gift[index].type,type.c_str(),sizeof(pdata->GiftBag[number].gift[index].type) - 1);
			memcpy(pdata->GiftBag[number].gift[index].data,data.c_str(),sizeof(pdata->GiftBag[number].gift[index].data) - 1);
			pdata->GiftBag[number].gift[index].flag = 1;
			++index;
		}
		++number;
	}

	m_shsggiftbagconfig.SetInitDone();
	//cout<<number<<endl;
	return 0;
}

int CDataXML::GetGiftBag(unsigned uid,unsigned giftbag_id,unsigned count,Json::Value &data)
{
	DataXMLsggiftbagconfig *pdata = (DataXMLsggiftbagconfig *)m_shsggiftbagconfig.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory *>(&(m_shsggiftbagconfig)), true);

	if(m_mapXMLGiftBag.find(giftbag_id) == m_mapXMLGiftBag.end())
	{
		error_log("[giftbag_id error] [uid=%u,giftbag_id=%u]",uid,giftbag_id);
		return -1;
	}

	Json::FastWriter writer;
	Json::Reader reader;

	if(pdata->GiftBag[m_mapXMLGiftBag[giftbag_id]].gift[0].rate != 0)
	{

		for(int j = 0; j < count; ++j)
		{
			vector <int> rate;
			rate.clear();
			rate = m_mapXMLGiftBagRate[giftbag_id];

			int rate_num = 0;
			int rate_size = rate.size();
			rate_num = Math::GetRandomInt(rate[rate_size - 1]);
//			cout<<rate_num<<endl;
			for(int i=0;i < rate_size;++i)
			{
				if(rate_num >= 0 && rate_num < rate[0])
				{
					Json::Value gift_data;
					gift_data.clear();
					string type = pdata->GiftBag[m_mapXMLGiftBag[giftbag_id]].gift[0].type;
					string str_data = pdata->GiftBag[m_mapXMLGiftBag[giftbag_id]].gift[0].data;
					reader.parse(str_data, gift_data);
					data[j][type] = gift_data;
					break;
				}
				else if(rate_num >= rate[i] && rate_num < rate[i+1])
				{
					Json::Value gift_data;
					gift_data.clear();
					string type = pdata->GiftBag[m_mapXMLGiftBag[giftbag_id]].gift[i+1].type;
					string str_data = pdata->GiftBag[m_mapXMLGiftBag[giftbag_id]].gift[i+1].data;
					reader.parse(str_data, gift_data);
					data[j][type] = gift_data;
					break;
				}
			}

		}
	}
	else
	{
		string type;
		Json::Value gift_data;
		gift_data.clear();
		for(int i=0;i<XML_GIFT_MAX;++i)
		{
			if(pdata->GiftBag[m_mapXMLGiftBag[giftbag_id]].gift[i].flag != 0)
			{
				type = pdata->GiftBag[m_mapXMLGiftBag[giftbag_id]].gift[i].type;
				string str_data = pdata->GiftBag[m_mapXMLGiftBag[giftbag_id]].gift[i].data;
				reader.parse(str_data, gift_data[type]);
			}
		}

		for(int j = 0; j < count; ++j)
		{
			data[j] = gift_data;
		}
	}
	return 0;
}

int CDataXML::GetGiftBagLevel(unsigned id, XMLGifgBagLvl &item)
{
	if (id > GIFT_BAG_LEVEL_COUNT)
		return R_ERR_PARAM;
	DataXMLsggiftbagconfig *pdata = (DataXMLsggiftbagconfig *)m_shsggiftbagconfig.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	item = pdata->GiftBagLevel[id-1];
	return 0;
}
/*****************************************/

/***************EquipSub**********************/
int CDataXML::InitEquipSub()
{
	DataXMLEquipSub *pdata = (DataXMLEquipSub *)m_shEquipSub.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shEquipSub), true,LOCK_MAX);

	memset(pdata,0,sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("olequipsub.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}
	if(!xmlConf.FindElem("content"))
	{
		cout<<("content node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();
	if(!xmlConf.FindElem("equipsub"))
	{
		cout<<("equipsub node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();

	while(xmlConf.FindElem("sub"))
	{
		string id = xmlConf.GetAttrib("id");
		string start = xmlConf.GetAttrib("start");
		string end = xmlConf.GetAttrib("end");
		string stone = xmlConf.GetAttrib("stone");
		string gold = xmlConf.GetAttrib("gold");
		vector<string> golds;
		String::Split(gold, ',', golds);
		if(id.empty() || start.empty() || end.empty() || stone.empty() || golds.size() != XML_EQUIP_SUB_GOLD)
		{
			cout<<("equipsub config wrong 1 ")<<id<<endl;
			return 1;
		}
		unsigned subid = CTrans::STOI(id.c_str());
		if(subid >= XML_EQUIP_SUB_LEVEL)
		{
			cout<<("equipsub config wrong 1.1 ")<<id<<endl;
			return 1;
		}
		pdata->sub[subid].id = subid;
		pdata->sub[subid].start = CTrans::STOI(start.c_str());
		pdata->sub[subid].end = CTrans::STOI(end.c_str());
		pdata->sub[subid].stone = CTrans::STOI(stone.c_str());
		for(unsigned i=0;i<XML_EQUIP_SUB_GOLD;++i)
			pdata->sub[subid].gold[i] =  CTrans::STOI(golds[i].c_str());

		unsigned itemSnum = 0;
		xmlConf.IntoElem();
		while(xmlConf.FindElem("items"))
		{
			string items = xmlConf.GetAttrib("id");
			string itemsrate = xmlConf.GetAttrib("rate");
			if(items.empty() || itemsrate.empty())
			{
				cout<<("equipsub config wrong 2 ")<<items<<endl;
				return 1;
			}
			if(itemSnum + 1 >= XML_EQUIP_SUB_ITEM_S)
			{
				cout<<("equipsub config wrong 2.1 ")<<items<<endl;
				return 1;
			}
			memcpy(pdata->sub[subid].subs[itemSnum].id,items.c_str(),items.size()>XML_EQUIP_SUB_ID-1?XML_EQUIP_SUB_ID-1:items.size());
			pdata->sub[subid].subs[itemSnum].rate = CTrans::STOI(itemsrate.c_str());

			xmlConf.IntoElem();
			while(xmlConf.FindElem("item"))
			{
				string star = xmlConf.GetAttrib("star");
				string value = xmlConf.GetAttrib("value");
				string rate = xmlConf.GetAttrib("rate");
				if(star.empty() || value.empty() || rate.empty())
				{
					cout<<("equipsub config wrong 3 ")<<star<<endl;
					return 1;
				}
				unsigned itemstar = CTrans::STOI(star.c_str());
				if(itemstar > XML_EQUIP_SUB_ITEM || !itemstar)
				{
					cout<<("equipsub config wrong 3.1 ")<<star<<endl;
					return 1;
				}

				pdata->sub[subid].subs[itemSnum].items[itemstar-1].star = itemstar;
				pdata->sub[subid].subs[itemSnum].items[itemstar-1].value = CTrans::STOI(value.c_str());
				pdata->sub[subid].subs[itemSnum].items[itemstar-1].rate = CTrans::STOI(rate.c_str());
			}

			++itemSnum;
			xmlConf.OutOfElem();
		}
		xmlConf.OutOfElem();
	}

	unsigned k = 0;
	m_mapEquipSub.clear();
	m_mapEquipSubItem.clear();
	for(k=0;k<XML_EQUIP_SUB_LEVEL;++k)
	{
		if(pdata->sub[k].start && pdata->sub[k].end)
		{
			EquipSubLevel lvlkey(pdata->sub[k].id,pdata->sub[k].start,pdata->sub[k].end,pdata->sub[k].stone,pdata->sub[k].gold);
			unsigned lvlsum = 0, j = 0;
			for(j=0;j<XML_EQUIP_SUB_ITEM_S;++j)
			{
				unsigned subsum = 0, m = 0;
				if(pdata->sub[k].subs[j].id[0])
				{
					EquipSubItem subkey(pdata->sub[k].start,pdata->sub[k].end,pdata->sub[k].subs[j].id);
					for(m=0;m<pdata->sub[k].subs[j].rate;++m)
					{
						m_mapEquipSub[lvlkey][lvlsum] = pdata->sub[k].subs[j].id;
						++lvlsum;
					}
					for(m=0;m<XML_EQUIP_SUB_ITEM;++m)
					{
						EquipSub eqsub(pdata->sub[k].subs[j].items[m].star,pdata->sub[k].subs[j].items[m].value,pdata->sub[k].subs[j].id);
						unsigned n = 0;
						for(n=0;n<pdata->sub[k].subs[j].items[m].rate;++n)
						{
							m_mapEquipSubItem[subkey][subsum] = eqsub;
							++subsum;
						}
					}
				}
			}
		}
	}

	m_shEquipSub.SetInitDone();
	return 0;
}

int CDataXML::GetEquipSub(unsigned lvl, unsigned &stone, unsigned &gold, unsigned subNum, vector<string> &keep, vector<EquipSub> &subs)
{
	bool flag = false;
	for(map<EquipSubLevel, map<unsigned, string> >::iterator it=m_mapEquipSub.begin();it!=m_mapEquipSub.end();++it)
	{
		if(lvl >= it->first.start && lvl <= it->first.end)
		{
			flag = true;
			subs.clear();
			unsigned keepNum = keep.size();
			if(keepNum > XML_EQUIP_SUB_GOLD)
				return R_ERR_LOGIC;
			stone = it->first.stone;
			gold = keepNum == 0 ? 0 : it->first.gold[keepNum-1];

			vector<string> res;
			for(unsigned i=0;i<subNum;++i)
			{
				bool retry = true;
				unsigned times = 0;
				string id;
				while(retry)
				{
					if(++times == 100)
						return R_ERR_DB;

					id = it->second[Math::GetRandomInt(it->second.rbegin()->first + 1)];
					if(find(keep.begin(),keep.end(),id) == keep.end()
					&& find(res.begin(),res.end(),id) == res.end())
						retry = false;
				}
				if(id.empty())
					return R_ERR_DB;

				EquipSubItem key(it->first.start,it->first.end,id);
				if(!m_mapEquipSubItem.count(key))
					return R_ERR_DB;

				subs.push_back(m_mapEquipSubItem[key][Math::GetRandomInt(m_mapEquipSubItem[key].rbegin()->first + 1)]);
				res.push_back(id);
			}

			break;
		}
	}
	if(!flag)
		return R_ERR_DB;
	return 0;
}
int CDataXML::GetEquipSubValue(unsigned lvl, string id, unsigned star, unsigned &value)
{
	bool flag = false;
	for(map<EquipSubLevel, map<string, map<unsigned, unsigned> > >::iterator it=m_mapEquipSubValue.begin();it!=m_mapEquipSubValue.end();++it)
	{
		if(lvl >= it->first.start && lvl <= it->first.end)
		{
			flag = true;
			if(!it->second.count(id) || !it->second[id].count(star))
				return R_ERR_DB;
			value = it->second[id][star];
			break;
		}
	}
	if(!flag)
		return R_ERR_DB;
	return 0;
}
int CDataXML::GetEquipSubStar(unsigned lvl, string id, unsigned value, unsigned &star)
{
	bool flag = false;
	for(map<EquipSubLevel, map<string, map<unsigned, unsigned> > >::iterator it=m_mapEquipSubStar.begin();it!=m_mapEquipSubStar.end();++it)
	{
		if(lvl >= it->first.start && lvl <= it->first.end)
		{
			flag = true;
			if(!it->second.count(id) || !it->second[id].count(value))
				return R_ERR_DB;
			star = it->second[id][value];
			break;
		}
	}
	if(!flag)
		return R_ERR_DB;
	return 0;
}
/*************************************/

/***************Boats******************/
int CDataXML::InitBoats()
{
	DataXMLBoats *pdata = (DataXMLBoats *)m_shBoats.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shBoats), true,LOCK_MAX);

	memset(pdata,0,sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);
	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}
	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");
	dataPath.append("boatsconfig.xml");
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}
	if(!xmlConf.FindElem("content"))
	{
		cout<<("content node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();

	if(!xmlConf.FindElem("boats"))
	{
		cout<<("boats node wrong")<<endl;
		return 1;
	}
	xmlConf.IntoElem();
	while(xmlConf.FindElem("boat"))
	{
		string id = xmlConf.GetAttrib("id");
		string time = xmlConf.GetAttrib("time");
		string reward1 = xmlConf.GetAttrib("reward1");
		string reward2 = xmlConf.GetAttrib("reward2");
		string reward3 = xmlConf.GetAttrib("reward3");
		if(id.empty() || time.empty() || reward1.empty() || reward2.empty() || reward3.empty())
		{
			cout<<("boats config wrong 1 id:")<<id<<endl;
			return 1;
		}

		unsigned i = CTrans::STOI(id.c_str()) - 1;
		if(i >= XML_BOATS_COUNT)
		{
			cout<<("boats config wrong 2 id:")<<id<<endl;
			return 1;
		}
		pdata->boats[i].id = CTrans::STOI(id.c_str());
		pdata->boats[i].time = CTrans::STOI(time.c_str());
		pdata->boats[i].reward[0] = CTrans::STOI(reward1.c_str());
		pdata->boats[i].reward[1] = CTrans::STOI(reward2.c_str());
		pdata->boats[i].reward[2] = CTrans::STOI(reward3.c_str());
	}
	xmlConf.OutOfElem();

	if(!xmlConf.FindElem("refreshRate"))
	{
		cout<<("boats node wrong 2")<<endl;
		return 1;
	}
	string refreshRate = xmlConf.GetAttrib("rate");
	vector<string> rates;
	String::Split(refreshRate, ',', rates);
	if(rates.size() != XML_BOATS_COUNT)
	{
		cout<<("boats node wrong 2 rate")<<endl;
		return 1;
	}
	for(unsigned i=0;i<XML_BOATS_COUNT;++i)
		pdata->boats[i].rate = CTrans::STOI(rates[i].c_str());

	m_shBoats.SetInitDone();
	return 0;
}

int CDataXML::GetBoat(uint32_t boatId, XMLBoat &boat){
	if(boatId > XML_BOATS_COUNT || !boatId || boatId > m_vBoat.size())
		return R_ERR_PARAM;
	boat = m_vBoat[boatId-1];
	return 0;
}

int CDataXML::GetBoatType(unsigned &bt)
{
	if(m_mapBoatType.size())
	{
		bt = m_mapBoatType[Math::GetRandomInt(m_mapBoatType.rbegin()->first + 1)];
		return 0;
	}
	return R_ERR_DB;
}
/*************************************/

int CDataXML::InitDailyChargeReward()
{
	DataXMLDailyCharge *pdata = (DataXMLDailyCharge *)m_shDailyCharge.GetAddress();

	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shDailyCharge), true, LOCK_MAX);

	memset(pdata, 0, sizeof(*pdata));

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);

	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}

	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");

	dataPath.append("sggiftbagconfig.xml");
	CMarkupSTL xmlConf;

	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout<<("content node wrong")<<endl;
		return 1;
	}

	xmlConf.IntoElem();

	if(!xmlConf.FindElem("dailypay"))
	{
		cout<<("dailypay node wrong")<<endl;
		return 1;
	}

	xmlConf.IntoElem();
	int index = 0;

	while(xmlConf.FindElem("reward") && index < MAX_DAILY_OPTIONS)
	{
		string id = xmlConf.GetAttrib("id");
		string coin = xmlConf.GetAttrib("coin");
		string reward = xmlConf.GetAttrib("reward");

		if(id.empty() || coin.empty() || reward.empty())
		{
			cout<<"[sggiftbagconfig.xml] content->dailypay->reward["<<index<<"] attribute id or coin or reward have no value"<<endl;
			return R_ERROR;
		}

		pdata->dailyreward[index].id = CTrans::STOI(id.c_str());
		pdata->dailyreward[index].coin = CTrans::STOI(coin.c_str());
		pdata->dailyreward[index].reward = CTrans::STOI(reward.c_str());

		++index;
	}

	xmlConf.OutOfElem();

	m_shDailyCharge.SetInitDone();

	return R_SUCCESS;
}

int CDataXML::GetDailyChargeRewardItem(unsigned index, XMLDailyChargeReward & item)
{
	if (index >= MAX_DAILY_OPTIONS)
	{
		error_log("[GetDailyChargeRewardItem] wrong index param. index=%u", index);
		return R_ERROR;
	}

	DataXMLDailyCharge *pdata = (DataXMLDailyCharge *)m_shDailyCharge.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shDailyCharge)), true);

	item = pdata->dailyreward[index];

	return R_SUCCESS;
}

int CDataXML::InitTreasureBox()
{
	DataXMLTreasureBox *pdata = (DataXMLTreasureBox *)m_shTreasureBox.GetAddress();

	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	int ret = ParseXMLInterface((void *)pdata, sizeof(DataXMLTreasureBox), "baibaoConfig.xml", m_shTreasureBox, &CDataXML::ParseXMLTreasure);

	if (ret)
	{
		return ret;
	}

	return 0;
}

int CDataXML::ParseXMLTreasure(void * data, CMarkupSTL & xmlConf)
{
	DataXMLTreasureBox * pdata = (DataXMLTreasureBox *) data;

	if(!xmlConf.FindElem("reward"))
	{
		cout<<("content->reward node wrong")<<endl;
		return 1;
	}

	xmlConf.IntoElem();

	int index = 0;

	while(xmlConf.FindElem("item") && index < MAX_ITEM_NUMS)
	{
		string id = xmlConf.GetAttrib("id");
		string rate = xmlConf.GetAttrib("rate");

		if(id.empty() || rate.empty())
		{
			cout<<"content->reward->item["<<index<<"] attribute id or rate have no value"<<endl;
			return R_ERROR;
		}

		pdata->rewarditems[index].id = CTrans::STOI(id.c_str());
		pdata->rewarditems[index].rate = CTrans::STOI(rate.c_str());

		//读取装备或英雄的配置
		Json::Value rewardValue;

		if (! Json::FromString(rewardValue, xmlConf.GetData()))
		{
			cout << "content->reward->item["<<index<<"]'s value read fail."<< endl;
			return R_ERROR;
		}

		if (! rewardValue.isMember("reward"))
		{
			cout << "content->reward->item["<<index<<"]'s value read fail."<< endl;
			return R_ERROR;
		}

		if (rewardValue["reward"].isMember("hero"))  //英雄
		{
			pdata->rewarditems[index].item.m_bIsHero = true;
			pdata->rewarditems[index].item.m_nId = rewardValue["reward"]["hero"]["id"].asUInt();
			pdata->rewarditems[index].item.m_nCnt = rewardValue["reward"]["hero"]["c"].asUInt();
		}
		else if (rewardValue["reward"].isMember("equip"))
		{
			pdata->rewarditems[index].item.m_bIsHero = false;
			pdata->rewarditems[index].item.m_nId = rewardValue["reward"]["equip"]["id"].asUInt();
			pdata->rewarditems[index].item.m_nCnt = rewardValue["reward"]["equip"]["c"].asUInt();
			pdata->rewarditems[index].item.m_nQuality = rewardValue["reward"]["equip"]["q"].asUInt();
			pdata->rewarditems[index].item.m_nCh = rewardValue["reward"]["equip"]["ch"].asUInt();
		}

		++index;
	}

	pdata->rewardnum = index;

	xmlConf.OutOfElem();

	if(!xmlConf.FindElem("show"))
	{
		cout<<("content->show node wrong")<<endl;
		return 1;
	}

	xmlConf.IntoElem();

	index = 0;

	while(xmlConf.FindElem("item") && index < MAX_ITEM_NUMS)
	{
		string id = xmlConf.GetAttrib("id");
		string rate = xmlConf.GetAttrib("rate");

		if(id.empty() || rate.empty())
		{
			cout<<"content->show->item["<<index<<"] attribute id or rate have no value"<<endl;
			return R_ERROR;
		}

		pdata->showitems[index].id = CTrans::STOI(id.c_str());
		pdata->showitems[index].rate = CTrans::STOI(rate.c_str());

		//读取装备或英雄的配置
		Json::Value rewardValue;

		if (! Json::FromString(rewardValue, xmlConf.GetData()))
		{
			cout << "content->show->item["<<index<<"]'s value read fail."<< endl;
			return R_ERROR;
		}

		if (! rewardValue.isMember("reward"))
		{
			cout << "content->reward->item["<<index<<"]'s value read fail."<< endl;
			return R_ERROR;
		}

		if (rewardValue["reward"].isMember("hero"))  //英雄
		{
			pdata->showitems[index].item.m_bIsHero = true;
			pdata->showitems[index].item.m_nId = rewardValue["reward"]["hero"]["id"].asUInt();
			pdata->showitems[index].item.m_nCnt = rewardValue["reward"]["hero"]["c"].asUInt();
		}
		else if (rewardValue["reward"].isMember("equip"))
		{
			pdata->showitems[index].item.m_bIsHero = false;
			pdata->showitems[index].item.m_nId = rewardValue["reward"]["equip"]["id"].asUInt();
			pdata->showitems[index].item.m_nCnt = rewardValue["reward"]["equip"]["c"].asUInt();
			pdata->showitems[index].item.m_nQuality = rewardValue["reward"]["equip"]["q"].asUInt();
			pdata->showitems[index].item.m_nCh = rewardValue["reward"]["equip"]["ch"].asUInt();
		}

		++index;
	}

	pdata->shownum = index;

	xmlConf.OutOfElem();

	return 0;
}

int CDataXML::GetTreasureBoxRewardItems(DataXMLTreasureBox & treasureItems)
{
	DataXMLTreasureBox *pdata = (DataXMLTreasureBox *)m_shTreasureBox.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	treasureItems = *pdata;

	return R_SUCCESS;
}

int CDataXML::GetSpecificBoxReward(unsigned id, XMLTreasureBox & item)
{
	if (!m_treasurebox.count(id))
	{
		error_log("[GetDailyChargeRewardItem] wrong id param. id=%u", id);
		return R_ERROR;
	}

	DataXMLTreasureBox *pdata = (DataXMLTreasureBox *)m_shTreasureBox.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shTreasureBox)), true);

	unsigned index = m_treasurebox[id];

	item = pdata->rewarditems[index];

	return R_SUCCESS;
}

int CDataXML::InitKeepsake()
{
	DataXMLKeepsake *pdata = (DataXMLKeepsake *)m_shKeepsake.GetAddress();

	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	int ret = ParseXMLInterface((void *)pdata, sizeof(DataXMLKeepsake), "xinwu.xml", m_shKeepsake, &CDataXML::ParseXMLKeepSake);

	if (ret)
	{
		return ret;
	}

	return 0;
}

int CDataXML::GetKeepSakeProduceCfg(XMLKeepsakeProduce & produce)
{
	DataXMLKeepsake *pdata = (DataXMLKeepsake *)m_shKeepsake.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shKeepsake)), true);

	produce = pdata->produce;

	return 0;
}

int CDataXML::GetKeepSakeUpgradeCfg(XMLTokenUpgrade & upgrade)
{
	DataXMLKeepsake *pdata = (DataXMLKeepsake *)m_shKeepsake.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shKeepsake)), true);

	upgrade = pdata->upgrade;

	return 0;
}

int CDataXML::GetKeepSakeBaseCfg(XMLTokenBase & base)
{
	DataXMLKeepsake *pdata = (DataXMLKeepsake *)m_shKeepsake.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shKeepsake)), true);

	base = pdata->base;

	return 0;
}

int CDataXML::GetSakeDefective(unsigned & eqid)
{
	DataXMLKeepsake *pdata = (DataXMLKeepsake *)m_shKeepsake.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shKeepsake)), true);

	eqid = pdata->defective_eqid;

	return 0;
}

int CDataXML::GetSakeExpProps(unsigned & eqid)
{
	DataXMLKeepsake *pdata = (DataXMLKeepsake *)m_shKeepsake.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shKeepsake)), true);
	eqid = pdata->exp_props_eqid;

	return 0;
}

int CDataXML::GetLevelIndex(unsigned level)
{
	int index = -1;

	DataXMLKeepsake *pdata = (DataXMLKeepsake *)m_shKeepsake.GetAddress();

	if (NULL == pdata)
	{
		error_log("get DataXMLKeepsake address error.");
		return -1;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shKeepsake)), true);

	for(int i = MAX_USER_LEVEL_LIMITS - 1; i >= 0; --i)
	{
		if (level >= pdata->produce.level_produce[i].level)
		{
			index = i;
			break;
		}
	}

	if (-1 == index)
	{
		error_log("wrong level. should bigger than %u", pdata->produce.level_produce[0].level);
	}

	return index;
}

unsigned CDataXML::GetXinWuReward(unsigned index, bool first)
{
	if(index >= XINWU_FB)
		return 0;

	DataXMLKeepsake *pdata = (DataXMLKeepsake *)m_shKeepsake.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shKeepsake)), true);

	if(first)
		return pdata->reward.firstReward[index];
	return pdata->reward.reward[index];
}

int CDataXML::InitChargeFeedback()
{
	DataXMLChargeFeedback *pdata = (DataXMLChargeFeedback *)m_shChargeFeedback.GetAddress();

	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	int ret = ParseXMLInterface( (void *)pdata, sizeof(DataXMLChargeFeedback),
			"sggiftbagconfig.xml", m_shChargeFeedback, &CDataXML::ParseXMLChargeFeedback);

	if (ret)
	{
		return ret;
	}

	return 0;
}

int CDataXML::GetChargeFeedbackRewardItem(unsigned index, string type, XMLChargeFeedbackReward & item)
{
	if (index >= MAX_CHARGE_FEEDBACK_NUMS)
	{
		error_log("wrong index param. index=%u", index);
		return R_ERROR;
	}

	DataXMLChargeFeedback *pdata = (DataXMLChargeFeedback *)m_shChargeFeedback.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shChargeFeedback)), true);

	if ("heaven" == type)
	{
		item = pdata->heaven[index];
	}
	else if ("daoist" == type)
	{
		item = pdata->daoist[index];
	}
	else
	{
		return R_ERR_PARAM;
	}

	return R_SUCCESS;
}

int CDataXML::InitCelebrateNewYear()
{
	DataXMLCelebrateNewYear *pdata = (DataXMLCelebrateNewYear *)m_shCelebrateNewYear.GetAddress();

	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	int ret = ParseXMLInterface( (void *)pdata, sizeof(DataXMLCelebrateNewYear),
			"sggiftbagconfig.xml", m_shCelebrateNewYear, &CDataXML::ParseXMLCeleNewYear);

	if (ret)
	{
		return ret;
	}

	return 0;
}

int CDataXML::GetCeleNewYearRewardItem(unsigned index, XMLNewYearReward & item)
{
	if (index >= MAX_CELEBRATE_NUMS)
	{
		error_log("wrong index param. index=%u", index);
		return R_ERROR;
	}

	DataXMLCelebrateNewYear *pdata = (DataXMLCelebrateNewYear *)m_shCelebrateNewYear.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shCelebrateNewYear)), true);
	item = pdata->reward[index];

	return R_SUCCESS;
}

int CDataXML::ParseXMLInterface(void * pdata, int length, char * filename, CShareMemory& shmomory, ParseComplete pfun)
{
	//统一的接口
	//先初始化空间
	CAutoLock lock(&(shmomory), true, LOCK_MAX);
	memset(pdata, 0, length);

	string dataPath = MainConfig::GetAllServerPath(CONFIG_XML_PATH);

	if (dataPath.empty())
	{
		cout<<("data path empty")<<endl;
		return 1;
	}

	if (dataPath[dataPath.length() - 1] != '/')
		dataPath.append("/");

	dataPath.append(filename);

	CMarkupSTL xmlConf;

	if(!xmlConf.Load(dataPath.c_str()))
	{
		cout<<("data path wrong")<<endl;
		return 1;
	}

	if(!xmlConf.FindElem("content"))
	{
		cout<<("content node wrong")<<endl;
		return 1;
	}

	xmlConf.IntoElem();

	//调用函数的回调接口
	int ret = (this->*pfun)(pdata, xmlConf);

	if (ret)
	{
		cout<<"parse file:"<<dataPath<<" error."<<endl;
		return ret;
	}

	shmomory.SetInitDone();

	return 0;
}

int CDataXML::ParseXMLKeepSake(void * data, CMarkupSTL & xmlConf)
{
	int ret = 0;

	DataXMLKeepsake * pdata = (DataXMLKeepsake *) data;

	//读取产出的配置
	ret = ParseXMLSakeProduce(pdata, xmlConf);

	if (ret)
	{
		return ret;
	}

	//读取升级配置
	ret = ParseXMLSakeUpgrade(pdata, xmlConf);

	if (ret)
	{
		return ret;
	}

	//读取基础经验
	ret = ParseXMLSakeBase(pdata, xmlConf);

	if (ret)
	{
		return ret;
	}

	//读取残品id和经验石id
	ret = ParseXMLSakeOth(pdata, xmlConf);

	if (ret)
	{
		return ret;
	}

	ret = ParseXMLXinWuReward(pdata, xmlConf);

	if (ret)
	{
		return ret;
	}

	return 0;
}

int CDataXML::ParseXMLSakeProduce(DataXMLKeepsake * pdata, CMarkupSTL & xmlConf)
{
	//读取NPC产出概率
	int index = 0;

	while(xmlConf.FindElem("npc") && index < MAX_NPC_NUM)
	{
		string id = xmlConf.GetAttrib("id");
		string cost = xmlConf.GetAttrib("cost");
		string chance = xmlConf.GetAttrib("chance");

		if(id.empty() || cost.empty() || chance.empty())
		{
			cout<<"content->npc["<<index<<"] attribute id,cost or chance have no value"<<endl;
			return R_ERROR;
		}

		pdata->produce.npcs[index].npcid = CTrans::STOI(id.c_str());
		pdata->produce.npcs[index].cost = CTrans::STOI(cost.c_str());
		pdata->produce.npcs[index].nextrate = CTrans::STOI(chance.c_str());

		xmlConf.IntoElem();

		if(!xmlConf.FindElem("fall"))
		{
			cout<<"content->npc["<<index<<"] fall node error"<<endl;
			return 1;
		}

		//读取普通掉落概率
		Json::Value ratevalue;

		if (!Json::FromString(ratevalue, xmlConf.GetData()) || !ratevalue.isArray())
		{
			cout<<"content->npc["<<index<<"] fall's value read fail, or value format error."<< endl;
			return R_ERROR;
		}

		for(unsigned i = 0; i < ratevalue.size() && i < MAX_FULL_NUM; ++i)
		{
			pdata->produce.npcs[index].fallrate[i] = ratevalue[i].asUInt();
		}

		if(!xmlConf.FindElem("zh"))
		{
			++index;
			xmlConf.OutOfElem();
			continue;
		}

		//读取召唤之后的概率
		if (!Json::FromString(ratevalue, xmlConf.GetData()) || !ratevalue.isArray())
		{
			cout<<"content->npc["<<index<<"] zh's value read fail, or value format error."<< endl;
			return R_ERROR;
		}

		for(unsigned i = 0; i < ratevalue.size() && i < MAX_FULL_NUM; ++i)
		{
			pdata->produce.npcs[index].summonrate[i] = ratevalue[i].asUInt();
		}

		xmlConf.OutOfElem();

		++index;
	}

	//读取等级概率
	index = 0;

	while(xmlConf.FindElem("wucg") && index < MAX_USER_LEVEL_LIMITS)
	{
		string level = xmlConf.GetAttrib("level");
		string xinwu = xmlConf.GetAttrib("xinwu");

		if(level.empty() || xinwu.empty())
		{
			cout<<"content->wucg["<<index<<"] attribute level,xinwu have no value"<<endl;
			return R_ERROR;
		}

		pdata->produce.level_produce[index].level = CTrans::STOI(level.c_str());

		Json::Value arrayvalue;

		if (!Json::FromString(arrayvalue, xinwu) || !arrayvalue.isArray())
		{
			cout<<"content->wucg["<<index<<"] attribute xinwu's value or format error."<< endl;
			return R_ERROR;
		}

		//信物id
		for(unsigned i = 0; i < arrayvalue.size() && i < MAX_KEEPSAKE_NUM; ++i)
		{
			pdata->produce.level_produce[index].keepsakeid[i] = arrayvalue[i].asUInt();
		}

		//不同品质，信物的出现概率
		xmlConf.IntoElem();
		int charnum = 0;

		while(xmlConf.FindElem("f") && charnum < MAX_CHARACTER_NUM)
		{
			Json::Value ratevalue;

			//读取召唤之后的概率
			if (!Json::FromString(ratevalue, xmlConf.GetData()) || !ratevalue.isArray())
			{
				cout<<"content->wucg["<<index<<"] f["<<charnum<<"]'s value read fail, or format error."<< endl;
				return R_ERROR;
			}

			//信物出现概率
			for(unsigned j = 0; j < ratevalue.size() && j < MAX_KEEPSAKE_NUM; ++j)
			{
				pdata->produce.level_produce[index].character_rate[charnum][j] = ratevalue[j].asUInt();
			}

			++charnum;
		}

		++index;
		xmlConf.OutOfElem();
	}

	return 0;
}

int CDataXML::ParseXMLSakeUpgrade(DataXMLKeepsake * pdata, CMarkupSTL & xmlConf)
{
	if(!xmlConf.FindElem("xinwu_upgrade"))
	{
		cout<<"content->xinwu_upgrade node error"<<endl;
		return R_ERROR;
	}

	xmlConf.IntoElem();

	int index = 0;

	while(xmlConf.FindElem("item") && index < MAX_CHARACTER_NUM)
	{
		xmlConf.IntoElem();

		//先读取经验
		if(!xmlConf.FindElem("exp"))
		{
			cout<<"content->xinwu_upgrade->item["<<index<<"] exp node error"<<endl;
			return R_ERROR;
		}

		Json::Value arrayvalue;

		//读取经验数组
		if (!Json::FromString(arrayvalue, xmlConf.GetData()))
		{
			cout<<"content->xinwu_upgrade->item["<<index<<"] exp's value read fail."<< endl;
			return R_ERROR;
		}

		if (!arrayvalue.isArray())
		{
			cout<<"content->xinwu_upgrade->item["<<index<<"]->exp's format error. should be array"<< endl;
			return R_ERROR;
		}

		//经验数组
		for(unsigned i = 0; i < arrayvalue.size() && i < MAX_KEEPSAKE_LEVEL; ++i)
		{
			pdata->upgrade.character_upgrade[index].exp[i] = arrayvalue[i].asUInt();
		}

		//资源数组
		char key[4] = {0};

		for(int i = 0; i < RESOURCE_ITEMS; ++i)
		{
			sprintf(key, "r%d", (i+1));

			//读取各项资源
			if(!xmlConf.FindElem(key))
			{
				continue;
			}

			Json::Value arrayvalue;

			//读取资源消耗数组
			if (!Json::FromString(arrayvalue, xmlConf.GetData()))
			{
				cout<<"content->xinwu_upgrade->item["<<index<<"]->"<<key<<"'s value read fail."<< endl;
				return R_ERROR;
			}

			if (!arrayvalue.isArray())
			{
				cout<<"content->xinwu_upgrade->item["<<index<<"]->"<<key<<"'s format error. should be array"<< endl;
				return R_ERROR;
			}

			//资源消耗数组
			for(unsigned j = 0; j < arrayvalue.size() && j < MAX_KEEPSAKE_LEVEL; ++j)
			{
				pdata->upgrade.character_upgrade[index].resource[i][j] = arrayvalue[j].asUInt();
			}
		}

		//解析转化石消耗
		if(!xmlConf.FindElem("eqcost"))
		{
			cout<<"content->xinwu_upgrade->item["<<index<<"] eqcost node error"<<endl;
			return R_ERROR;
		}

		//数组
		if (!Json::FromString(arrayvalue, xmlConf.GetData()))
		{
			cout<<"content->xinwu_upgrade->item["<<index<<"] eqcost's value read fail."<< endl;
			return R_ERROR;
		}

		if (!arrayvalue.isArray())
		{
			cout<<"content->xinwu_upgrade->item["<<index<<"]->eqcost's format error. should be array"<< endl;
			return R_ERROR;
		}

		for(unsigned i = 0; i < arrayvalue.size() && i < MAX_KEEPSAKE_LEVEL; ++i)
		{
			pdata->upgrade.character_upgrade[index].convertcost[i] = arrayvalue[i].asUInt();
		}

		++index;
		xmlConf.OutOfElem();
	}

	xmlConf.OutOfElem();

	return 0;
}

int CDataXML::ParseXMLSakeBase(DataXMLKeepsake * pdata, CMarkupSTL & xmlConf)
{
	//读取基础属性
	if(!xmlConf.FindElem("deauft_exp"))
	{
		cout<<"content->deauft_exp node error"<<endl;
		return R_ERROR;
	}

	Json::Value arrayvalue;

	//读取品质经验数组
	if (!Json::FromString(arrayvalue, xmlConf.GetData()))
	{
		cout<<"content->deauft_exp's value read fail."<< endl;
		return R_ERROR;
	}

	if (!arrayvalue.isArray())
	{
		cout<<"content->deauft_exp's format error. should be array"<< endl;
		return R_ERROR;
	}

	//经验数组
	for(unsigned i = 0; i < arrayvalue.size() && i < MAX_CHARACTER_NUM; ++i)
	{
		pdata->base.character_exp[i] = arrayvalue[i].asUInt();
	}

	//读取从属性解锁等级
	if(!xmlConf.FindElem("accessory_unlock_level"))
	{
		cout<<"content->accessory_unlock_level node error"<<endl;
		return R_ERROR;
	}

	string level = xmlConf.GetAttrib("lvs");

	if (level.empty())
	{
		cout<<"content->accessory_unlock_level attibute lvs's value error"<<endl;
		return R_ERROR;
	}

	//从属性解锁等级数组
	if (!Json::FromString(arrayvalue, level))
	{
		cout<<"content->accessory_unlock_level attibute lvs's value error."<< endl;
		return R_ERROR;
	}

	if (!arrayvalue.isArray())
	{
		cout<<"content->accessory_unlock_level attibute lvs's format error. should be array"<< endl;
		return R_ERROR;
	}

	//从属性解锁等级数组
	for(unsigned i = 0; i < arrayvalue.size() && i < MAX_SLAVE_PROPNUM; ++i)
	{
		pdata->base.slave_unlock_level[i] = arrayvalue[i].asUInt();
	}

	return 0;
}

int CDataXML::ParseXMLSakeOth(DataXMLKeepsake * pdata, CMarkupSTL & xmlConf)
{
	//读取残品和经验石
	//读取从属性解锁等级
	if(!xmlConf.FindElem("xinwus"))
	{
		cout<<"content->xinwus node error"<<endl;
		return R_ERROR;
	}

	xmlConf.IntoElem();
	int index = 0;

	while(xmlConf.FindElem("xinwu"))
	{
		string id = xmlConf.GetAttrib("id");
		string type = xmlConf.GetAttrib("type");

		if(type.empty() || id.empty())
		{
			cout<<"content->xinwus->xinwu["<<index<<"] attribute id,type have no value"<<endl;
			return R_ERROR;
		}

		if (type == "2")  //残品
		{
			pdata->defective_eqid = CTrans::STOI(id.c_str());
		}
		else if (type == "3")  //经验石
		{
			pdata->exp_props_eqid = CTrans::STOI(id.c_str());
		}

		++index;
	}
	xmlConf.OutOfElem();

	return 0;
}

int CDataXML::ParseXMLXinWuReward(DataXMLKeepsake * pdata, CMarkupSTL & xmlConf)
{
	if(!xmlConf.FindElem("xinwuFBs"))
	{
		cout<<"content->xinwuFBs node error"<<endl;
		return R_ERROR;
	}
	Json::Reader reader;

	xmlConf.IntoElem();
	while(xmlConf.FindElem("xinwuFB"))
	{
		string level = xmlConf.GetAttrib("level");
		int index = CTrans::STOI(level.c_str());
		if(index <= 0 || index > XINWU_FB)
		{
			cout<<"content->xinwuFBs level error"<<endl;
			return R_ERROR;
		}
		--index;

		xmlConf.IntoElem();

		if(!xmlConf.FindElem("freward"))
		{
			cout<<"content->xinwuFBs freward error"<<endl;
			return R_ERROR;
		}
		string freward = xmlConf.GetData();
		Json::Value f;
		reader.parse(freward, f);
		if(!f.isMember("equip1") || !f["equip1"].isMember("c"))
		{
			cout<<"content->xinwuFBs freward json error"<<endl;
			return R_ERROR;
		}
		pdata->reward.firstReward[index] = f["equip1"]["c"].asUInt();

		if(!xmlConf.FindElem("breward"))
		{
			cout<<"content->xinwuFBs breward error"<<endl;
			return R_ERROR;
		}
		string breward = xmlConf.GetData();
		Json::Value b;
		reader.parse(breward, b);
		if(!b.isMember("equip1") || !b["equip1"].isMember("c"))
		{
			cout<<"content->xinwuFBs breward json error"<<endl;
			return R_ERROR;
		}
		pdata->reward.reward[index] = b["equip1"]["c"].asUInt();

		xmlConf.OutOfElem();
	}
	xmlConf.OutOfElem();

	return 0;
}

int CDataXML::ParseXMLChargeFeedback(void * data, CMarkupSTL & xmlConf)
{
	int ret = 0;

	DataXMLChargeFeedback * pdata = (DataXMLChargeFeedback *) data;

	if(!xmlConf.FindElem("dailypaydaoist"))
	{
		cout<<("dailypaydaoist node wrong")<<endl;
		return 1;
	}

	xmlConf.IntoElem();

	int index = 0;

	//解析遁甲配置
	while(xmlConf.FindElem("reward") && index < MAX_CHARGE_FEEDBACK_NUMS)
	{
		string id = xmlConf.GetAttrib("id");
		string diamond = xmlConf.GetAttrib("diamond");

		if(id.empty() || diamond.empty())
		{
			cout<<"content->dailypaydaoist->reward["<<index<<"] attribute id or diamond have no value"<<endl;
			return R_ERROR;
		}

		pdata->daoist[index].id = CTrans::STOI(id.c_str());
		pdata->daoist[index].diamond = CTrans::STOI(diamond.c_str());

		//读取装备配置
		Json::Value rewardval;
		if (!Json::FromString(rewardval, xmlConf.GetData()))
		{
			cout<<"content->dailypaydaoist->reward["<<index<<"]'s value read fail."<< endl;
			return R_ERROR;
		}

		pdata->daoist[index].equip.CopyFromJson(rewardval["reward"]["equip1"]);

		++index;
	}

	xmlConf.OutOfElem();

	if(!xmlConf.FindElem("dailypayheaven"))
	{
		cout<<("dailypayheaven node wrong")<<endl;
		return 1;
	}

	xmlConf.IntoElem();
	index = 0;

	//解析兵书配置
	while(xmlConf.FindElem("reward") && index < MAX_CHARGE_FEEDBACK_NUMS)
	{
		string id = xmlConf.GetAttrib("id");
		string diamond = xmlConf.GetAttrib("diamond");

		if(id.empty() || diamond.empty())
		{
			cout<<"content->dailypayheaven->reward["<<index<<"] attribute id or diamond have no value"<<endl;
			return R_ERROR;
		}

		pdata->heaven[index].id = CTrans::STOI(id.c_str());
		pdata->heaven[index].diamond = CTrans::STOI(diamond.c_str());

		//读取装备配置
		Json::Value rewardval;
		if (!Json::FromString(rewardval, xmlConf.GetData()))
		{
			cout<<"content->dailypayheaven->reward["<<index<<"]'s value read fail."<< endl;
			return R_ERROR;
		}

		pdata->heaven[index].equip.CopyFromJson(rewardval["reward"]["equip1"]);

		++index;
	}

	return 0;
}

int CDataXML::ParseXMLCeleNewYear(void * data, CMarkupSTL & xmlConf)
{
	int ret = 0;

	DataXMLCelebrateNewYear * pdata = (DataXMLCelebrateNewYear *) data;

	if(!xmlConf.FindElem("newchargepay"))
	{
		cout<<("newchargepay node wrong")<<endl;
		return 1;
	}

	xmlConf.IntoElem();

	int index = 0;

	//解析遁甲配置
	while(xmlConf.FindElem("reward") && index < MAX_CHARGE_FEEDBACK_NUMS)
	{
		string id = xmlConf.GetAttrib("id");
		string diamond = xmlConf.GetAttrib("coin");

		if(id.empty() || diamond.empty())
		{
			cout<<"content->newchargepay->reward["<<index<<"] attribute id or coin have no value"<<endl;
			return R_ERROR;
		}

		pdata->reward[index].id = CTrans::STOI(id.c_str());
		pdata->reward[index].diamond = CTrans::STOI(diamond.c_str());

		//读取装备配置
		Json::Value rewardval;
		if (!Json::FromString(rewardval, xmlConf.GetData()))
		{
			cout<<"content->newchargepay->reward["<<index<<"]'s value read fail."<< endl;
			return R_ERROR;
		}

		pdata->reward[index].equip.CopyFromJson(rewardval["reward"]["equip1"]);

		pdata->reward[index].coin = rewardval["reward"]["gold"].asUInt();

		++index;
	}

	xmlConf.OutOfElem();

	return 0;
}

int CDataXML::InitCatapult()
{
	DataXMLCatapult *pdata = (DataXMLCatapult *)m_shCatapult.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shCatapult), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));
	string dataPath;
	int ret = GetFile("catapultConfig.xml", dataPath);
	if (ret)
	{
		return ret;
	}

	CMarkupSTL xmlConf;
	if (!xmlConf.Load(dataPath.c_str()))
	{
		cout << ("data path wrong") << endl;
		return R_ERROR;
	}
	if (!xmlConf.FindElem("content"))
	{
		cout << ("content node wrong") << endl;
		return R_ERROR;
	}
	xmlConf.IntoElem();

	if (!xmlConf.FindElem("catapult"))
	{
		cout << ("catapult node wrong") << endl;
		return R_ERROR;
	}
	xmlConf.IntoElem();

	string id;
	string exp;
	string res;
	string needeq;
	string per;
	unsigned i = 0;
	unsigned n = 0;
	m_mapXMLCatapult.clear();

	for(i = 0; i < CATAPULT_NUM; ++i)
	{
		xmlConf.FindElem("floor");
		id = xmlConf.GetAttrib("id");
		exp = xmlConf.GetAttrib("exp");
		res = xmlConf.GetAttrib("res");
		needeq = xmlConf.GetAttrib("needeq");
		per = xmlConf.GetAttrib("per");

		if (id.empty() || exp.empty() || res.empty() || needeq.empty() || per.empty())
		{
			cout << ("catapult wrong") << endl;
			return R_ERROR;
		}

		n = res.find_last_of(',') + 1;

		pdata->catapult[i].id  = CTrans::STOI(id.c_str());
		pdata->catapult[i].exp = CTrans::STOI(exp.c_str());
		pdata->catapult[i].res = CTrans::STOI(res.substr(n).c_str());
		pdata->catapult[i].needeq = CTrans::STOI(needeq.c_str());
		pdata->catapult[i].per = CTrans::STOI(per.c_str());

		m_mapXMLCatapult[pdata->catapult[i].id] = i;
	}

	m_shCatapult.SetInitDone();
	return R_SUCCESS;
}

int CDataXML::GetCatapultItem(const unsigned id, XMLCatapult &item)
{
	if (!m_mapXMLCatapult.count(id))
	{
		return R_ERR_NO_DATA;
	}

	DataXMLCatapult *pdata = (DataXMLCatapult *)m_shCatapult.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(static_cast<CShareMemory *>(&(m_shCatapult)), true);

	item = pdata->catapult[m_mapXMLCatapult[id]];

	return R_SUCCESS;
}


int CDataXML::GetCatapultLv(unsigned id, unsigned exp, unsigned &lv)
{
	if (!m_mapXMLCatapult.count(id))
	{
		return R_ERR_NO_DATA;
	}

	DataXMLCatapult *pdata = (DataXMLCatapult *)m_shCatapult.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(static_cast<CShareMemory *>(&(m_shCatapult)), true);

	lv = m_mapXMLCatapult[id];

	while (lv && (pdata->catapult[lv].exp > exp))
	{
		--lv;
	}

	return R_SUCCESS;
}

int CDataXML::InitCostCatapult()
{
	DataXMLCostCatapult *pdata = (DataXMLCostCatapult *)m_shCostCatapult.GetAddress();
	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shCostCatapult), true, LOCK_MAX);

	memset(pdata, 0, sizeof(*pdata));

	string dataPath;
	int ret = GetFile("catapultConfig.xml", dataPath);
	if (ret)
	{
		return ret;
	}

	CMarkupSTL xmlConf;

	if (!xmlConf.Load(dataPath.c_str()))
	{
		cout << ("data path wrong") << endl;
		return R_ERROR;
	}

	if (!xmlConf.FindElem("content"))
	{
		cout << ("content node wrong") << endl;
		return R_ERROR;
	}
	xmlConf.IntoElem();

	if (!xmlConf.FindElem("cost"))
	{
		cout << ("cost node wrong") << endl;
		return R_ERROR;
	}
	xmlConf.IntoElem();

	string jie = "";
	string cash = "";
	m_mapCostCatapult.clear();
	for(unsigned i = 0; i < CATAPULT_JIE_NUM; ++i)
	{
		xmlConf.FindElem("catapult");
		jie = xmlConf.GetAttrib("jie");
		cash = xmlConf.GetAttrib("cash");
		if (jie.empty() || cash.empty())
		{
			cout << ("catapult cost wrong") << endl;
			return R_ERROR;
		}
		m_mapCostCatapult[i] = CTrans::STOI(cash.c_str());
		pdata->catapultCost[i].id = i;
		pdata->catapultCost[i].jie = CTrans::STOI(jie.c_str());
		pdata->catapultCost[i].cash = CTrans::STOI(cash.c_str());
	}

	m_shCostCatapult.SetInitDone();

	return R_SUCCESS;
}

int CDataXML::GetCostCatapult(unsigned jie_index, unsigned &cash)
{
	if (!m_mapCostCatapult.count(jie_index))
	{
		return R_ERR_NO_DATA;
	}

	cash = m_mapCostCatapult[jie_index];
	return R_SUCCESS;
}



int CDataXML::InitCatapultSkill()
{
	int ret = 0;

	DataXMLCatapultSkill *pdata = (DataXMLCatapultSkill *)m_shCatapultSkill.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_shCatapultSkill), true, LOCK_MAX);
	memset(pdata, 0, sizeof(*pdata));

	string dataPath;
	ret = GetFile("catapultConfig.xml", dataPath);

	if (ret)
	{
		return ret;
	}

	CMarkupSTL xmlConf;

	if (!xmlConf.Load(dataPath.c_str()))
	{
		cout << ("data path wrong") << endl;
		return R_ERROR;
	}

	if (!xmlConf.FindElem("content"))
	{
		cout << ("content node wrong") << endl;
		return R_ERROR;
	}

	xmlConf.IntoElem();

	if (!xmlConf.FindElem("skills"))
	{
		cout << ("content->skills node wrong") << endl;
		return R_ERROR;
	}

	xmlConf.IntoElem();

	int kind = 0;

	while(xmlConf.FindElem("skill") && kind < MAX_CATAPULT_SKILL_ITEMS)
	{
		string id, unlocklv, book, bookid;

		id = xmlConf.GetAttrib("id");
		unlocklv = xmlConf.GetAttrib("unlocklv");
		book = xmlConf.GetAttrib("book");
		bookid = xmlConf.GetAttrib("bookid");

		if (id.empty() || unlocklv.empty() || book.empty() || bookid.empty())
		{
			cout<<"content->skills->skill["<<kind<<"] 's attribute id or unlocklv or book or bookid is empty"<<endl;
			return R_ERROR;
		}

		pdata->skillitem[kind].id =  CTrans::STOI(id.c_str());
		pdata->skillitem[kind].unlocklv =  CTrans::STOI(unlocklv.c_str());

		vector<string> vecbook;
		vector<string> vecbookid;
		String::Split(book, ',', vecbook);
		String::Split(bookid, ',', vecbookid);
		for(size_t i = 0; i < vecbookid.size() && i < MAX_CATAPULT_SKILL_LEVEL; ++i)
		{
			pdata->skillitem[kind].bookid[i] = CTrans::STOI(vecbookid[i].c_str());
		}

		for(size_t i = 0; i < vecbook.size() && i < MAX_CATAPULT_SKILL_LEVEL; ++i)
		{
			pdata->skillitem[kind].booknum[i] = CTrans::STOI(vecbook[i].c_str());
		}

		++kind;
	}

	xmlConf.OutOfElem();
	m_shCatapultSkill.SetInitDone();

	return R_SUCCESS;
}

int CDataXML::GetCatapultSkillItem(unsigned id, XMLCatapultSkillItem & skillitem)
{
	map<unsigned, unsigned>::iterator uiter;

	if (m_mapCatapultSkill.end() == (uiter = m_mapCatapultSkill.find(id)))
	{
		return R_ERR_PARAM;
	}

	DataXMLCatapultSkill *pdata = (DataXMLCatapultSkill *)m_shCatapultSkill.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(const_cast<CShareMemory*>(&(m_shCatapultSkill)), true);

	skillitem = pdata->skillitem[uiter->second];

	return R_SUCCESS;
}

int CDataXML::InitChongZhiZiXuan()
{
	try
	{
		return DataXmlChongZhiZiXuanUnit(m_shChongZhiZiXuan, "activityconfig.xml").Initialize();
	}
	catch(const std::exception& e)
	{
		std::cout << "[InitChongZhiZiXuan]Error: " << e.what() << std::endl;
		return R_ERROR;
	}
	return 0;
}

int CDataXML::GetChongZhiZiXuanItem(unsigned pool, unsigned item, vector<GiftEquipItem> &data)
{
	if (pool >= CHONGZHIZIXUAN_POOL_COUNT) {
		return R_ERR_NO_DATA;
	}
	if (item >= CHONGZHIZIXUAN_ITEM_COUNT) {
		return R_ERR_NO_DATA;
	}
	DataXMLChongZhiZiXuan *pdata = (DataXMLChongZhiZiXuan *)m_shChongZhiZiXuan.GetAddress();
	if (NULL == pdata) {
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shChongZhiZiXuan)), true);
	for (int i = 0; i < CHONGZHIZIXUAN_REWARD_COUNT; ++i) {
		if (pdata->pool[pool].item[item].reward[i].IsEquip()){
			data.push_back(pdata->pool[pool].item[item].reward[i]);
		}
	}
	return R_SUCCESS;
}

int CDataXML::GetChongZhiZiXuanCharge(unsigned pool, unsigned charge, unsigned &count)
{
	if (pool >= CHONGZHIZIXUAN_POOL_COUNT) {
		return R_ERR_NO_DATA;
	}
	DataXMLChongZhiZiXuan *pdata = (DataXMLChongZhiZiXuan *)m_shChongZhiZiXuan.GetAddress();
	if (NULL == pdata) {
		return R_ERR_DB;
	}
	CAutoLock lock(const_cast<CShareMemory*>(&(m_shChongZhiZiXuan)), true);
	for (int i = 0; i < CHONGZHIZIXUAN_ITEM_COUNT; ++i) {
		if (charge > 0 && charge >= pdata->pool[pool].charge[i].require) {
			count += pdata->pool[pool].charge[i].times;
		}
	}
	return R_SUCCESS;
}

int CDataXML::InitBeauty() {
	try {
		return DataXMLBeautyUnit(m_shBeauty, "activityconfig.xml").Initialize();
	} catch(const std::exception& e) {
		std::cout << "[InitBeauty]Error: " << e.what() << std::endl;
		return R_ERROR;
	}
	return 0;
}
int CDataXML::GetBeautyActive(unsigned id, XMLBeautyActiveItem &item) {
	DataXMLBeauty *pdata = (DataXMLBeauty*)m_shBeauty.GetAddress();
	if (pdata == NULL) {
		return R_ERR_DATA;
	}
	for (int i = 0; i < XML_BEAUTY_ACTIVE_ITEM_COUNT; ++i) {
		if (id == pdata->active[i].id) {
			memcpy(&item, &(pdata->active[i]), sizeof(XMLBeautyActiveItem));
			return 0;
		}
	}
	return R_ERR_NO_DATA;
}
int CDataXML::GetBeautyReward(unsigned id, XMLBeautyRewardItem &item) {
	DataXMLBeauty *pdata = (DataXMLBeauty*)m_shBeauty.GetAddress();
	if (pdata == NULL) {
		return R_ERR_DATA;
	}
	for (int i = 0; i < XML_BEAUTY_REWARD_ITEM_COUNT; ++i) {
		if (id == pdata->reward[i].id) {
			memcpy(&item, &(pdata->reward[i]), sizeof(XMLBeautyRewardItem));
			return 0;
		}
	}
	return R_ERR_NO_DATA;
}
int CDataXML::InitInvestment() {
	try {
		return DataXMLInvestmentUnit(m_shInvestment, "activityconfig.xml").Initialize();
	} catch (const std::exception& e) {
		std::cout << "[InitInvestment]Error: " << e.what() << std::endl;
		return R_ERROR;
	}
	return 0;
}
int CDataXML::GetInvestmentRate(vector<unsigned> &r, bool last) {
	DataXMLInvestment *pdata = (DataXMLInvestment*)m_shInvestment.GetAddress();
	if (pdata == NULL) {
		return R_ERR_DATA;
	}
	CAutoLock lock(&(m_shInvestment), true, LOCK_MAX);
	if (last) {
		for (int i = 0; i < XML_INVESTMENT_RATE_NUM; ++i) {
			r.push_back(pdata->rate1[i] * XML_INVESTMENT_RATE_MULTIPLE);
		}
	} else {
		for (int i = 0; i < XML_INVESTMENT_RATE_NUM; ++i) {
			r.push_back(pdata->rate[i] * XML_INVESTMENT_RATE_MULTIPLE);
		}
	}
	return 0;
}
int CDataXML::GetInvestmentReward(unsigned id, XMLInvestmentReward &item) {
	DataXMLInvestment *pdata = (DataXMLInvestment*)m_shInvestment.GetAddress();
	if (pdata == NULL) {
		return R_ERR_DATA;
	}
	CAutoLock lock(&(m_shInvestment), true, LOCK_MAX);
	for (int i = 0; i < XML_INVESTMENT_REWARD_NUM; ++i) {
		if (pdata->item[i].id == id) {
			memcpy(&item, &(pdata->item[i]), sizeof(XMLInvestmentReward));
			return 0;
		}
	}
	return R_ERR_NO_DATA;
}
int CDataXML::InitBirdBridge() {
	try {
		return DataXMLBirdBridgeUnit(m_shBirdBridge, "activityconfig.xml").Initialize();
	} catch (const std::exception& e) {
		std::cout << "[InitBirdBridge]Error: " << e.what() << std::endl;
		return R_ERROR;
	}
	return 0;
}
int CDataXML::GetBirdBridgeItem(unsigned type, unsigned id, XMLBirdBridgeItem &item) {
	DataXMLBirdBridge *pdata = (DataXMLBirdBridge*)m_shBirdBridge.GetAddress();
	if (pdata == NULL) {
		return R_ERR_DATA;
	}
	CAutoLock lock(&(m_shBirdBridge), true, LOCK_MAX);
	if (type == 0) {
		for (int i = 0; i < XML_BIRD_BRIDGE_ITEM_NUM; ++i) {
			if (id == pdata->left[i].id) {
				memcpy(&item, &(pdata->left[i]), sizeof(XMLBirdBridgeItem));
				return 0;
			}
		}
	} else if (type == 1) {
		for (int i = 0; i < XML_BIRD_BRIDGE_ITEM_NUM; ++i) {
			if (id == pdata->right[i].id) {
				memcpy(&item, &(pdata->right[i]), sizeof(XMLBirdBridgeItem));
				return 0;
			}
		}
	} else {
		memcpy(&item, &(pdata->center), sizeof(XMLBirdBridgeItem));
		return 0;
	}
	return R_ERR_NO_DATA;
}
int CDataXML::InitUnionTech() {
	try {
		return DataXMLUnionTechUnit(m_shUnionTech, "uniontechconfig.xml").Initialize();
	} catch (const std::exception& e) {
		std::cout << "[InitUnionTech]Error: " << e.what() << std::endl;
		return R_ERROR;
	}
	return 0;
}
int CDataXML::GetUnionTechItem(unsigned id, XMLUnionTechItem &item) {
	DataXMLUnionTech *pdata = (DataXMLUnionTech*)m_shUnionTech.GetAddress();
	if (pdata == NULL) {
		return R_ERR_DATA;
	}
	CAutoLock lock(&(m_shUnionTech), true, LOCK_MAX);
	for (int i = 0; i < XML_MAX_UNIONTECH_NUM; ++i) {
		if (id == pdata->tech[i].id) {
			memcpy(&item, &(pdata->tech[i]), sizeof(XMLUnionTechItem));
			return 0;
		}
	}
	return R_ERR_NO_DATA;
}
void CDataXML::ViewUnionTech() {
	DataXMLUnionTech *pdata = (DataXMLUnionTech*)m_shUnionTech.GetAddress();
	if (pdata == NULL) {
		return;
	}
	CAutoLock lock(&(m_shUnionTech), true, LOCK_MAX);
	for (int i=0; i<XML_MAX_UNIONTECH_NUM; i++)
	{
		cout << "tech " << pdata->tech[i].id << ": " << endl;
		for (int j=0; j<XML_MAX_UNIONTECH_LEVEL; j++)
		{
			cout << pdata->tech[i].studypoint[j] << " "  << pdata->tech[i].gold[j] << " " <<
					pdata->tech[i].wood[j] << " " << pdata->tech[i].eqpoint[j] << endl;
		}

	}
}

int CDataXML::InitShengDan() {
	try {
		return DataXMLShengDanUnit(m_shShengDan, "activityconfig.xml").Initialize();
	} catch (const std::exception& e) {
		std::cout << "[InitUnionTech]Error: " << e.what() << std::endl;
		return R_ERROR;
	}
	return 0;
}

void CDataXML::ViewShengDan() {
	DataXMLShengDan *pdata = (DataXMLShengDan*)m_shShengDan.GetAddress();
	if (pdata == NULL) {
		return;
	}
	CAutoLock lock(&(m_shShengDan), true, LOCK_MAX);
	std::cout << "day :" << (pdata->day).m_nId<< " " << (pdata->day).m_nCnt << " " << std::endl;

}

int CDataXML::GetShengDanItem(DataXMLShengDan &item) {
	DataXMLShengDan *pdata = (DataXMLShengDan*)m_shShengDan.GetAddress();
	if (pdata == NULL) {
		return R_ERR_DATA;
	}
	CAutoLock lock(&(m_shShengDan), true, LOCK_MAX);
	memcpy(&item, pdata, sizeof(DataXMLShengDan));
	return 0;
}
