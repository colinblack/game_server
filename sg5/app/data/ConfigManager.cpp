/*
 * ConfigManager.cpp
 *
 *  Created on: 2016-8-22
 *      Author: Ralf
 */


#include "ConfigManager.h"

bool ConfigManager::m_init = true;
ConfigManager* ConfigManager::m_pData = NULL;

ConfigManager* ConfigManager::Instance()
{
	if(!m_init)
		throw runtime_error("Init ConfigManager fail!");
	if(!m_pData)
	{
		m_pData = new ConfigManager;
		if(!m_init)
		{
			error_log("Init ConfigManager fail!");
			delete m_pData;
			m_pData = NULL;
			throw runtime_error("Init ConfigManager fail!");
		}
	}
	return m_pData;
}

void ConfigManager::Init()
{
	if(!m_init)
		return;

	for(int i=0;i<m_BraveNewWorldConfig.m_config.land_size();++i)
		m_BraveNewWorldPoint[pair<unsigned, unsigned>(m_BraveNewWorldConfig.m_config.land(i).x(),m_BraveNewWorldConfig.m_config.land(i).y())] = i;
	for(int i=0;i<m_BraveNewWorldConfig.m_config.config_size();++i)
		m_BraveNewWorldProperty[pair<unsigned, unsigned>(m_BraveNewWorldConfig.m_config.config(i).type(),m_BraveNewWorldConfig.m_config.config(i).level())] = i;
	for(int i=0;i<m_BraveNewWorldConfig.m_config.zone_size();++i)
		m_BraveNewWorldZone[m_BraveNewWorldConfig.m_config.zone(i).level()] = i;
	for(int i=0;i<m_BraveNewWorldConfig.m_config.city_size();++i)
		m_BraveNewWorldCity[m_BraveNewWorldConfig.m_config.city(i).level()] = i;

	//添加碎片与下标的映射关系
	for(int i = 0; i < m_CompoundConfig.m_config.shred_compounds_size(); ++i)
	{
		unsigned shredid = m_CompoundConfig.m_config.shred_compounds(i).shredid();

		m_compoundId[shredid] = i;
	}

	//添加古卷的映射关系
	for(int i = 0; i < m_scrollactivitycfg.m_config.activity_affairs_size(); ++i)
	{
		for(int j = 0; j < m_scrollactivitycfg.m_config.activity_affairs(i).affairs_size(); ++j)
		{
			unsigned id = m_scrollactivitycfg.m_config.activity_affairs(i).affairs(j).id();

			m_scrollIndex[id].first = i;
			m_scrollIndex[id].second = j;
		}
	}

	//添加天帝宝库的映射关系
	for(int i = 0; i < m_kingtreasurecfg.m_config.king_treasures_size(); ++i)
	{
		unsigned id = m_kingtreasurecfg.m_config.king_treasures(i).id();

		m_treasureIndex[id] = i;
	}

	//new soul stone
	for(int i = 0; i < m_newsoulstone.m_config.oldstone_size(); ++i)
		m_OldSoulStoneA[m_newsoulstone.m_config.oldstone(i).id()] = make_pair(m_newsoulstone.m_config.oldstone(i).a(0), m_newsoulstone.m_config.oldstone(i).a(1));
	for(int j=0;j<m_newsoulstone.m_config.newstone3_size();++j)
	{
		int s = 0;
		for(int i = 0; i < m_newsoulstone.m_config.newstone3(j).newstone_size(); ++i)
		{
			s += m_newsoulstone.m_config.newstone3(j).newstone(i).p();
			m_NewSoulStoneP[j][s] = m_newsoulstone.m_config.newstone3(j).newstone(i).id();
		}
	}

	int yingling_normal_s = 0;
	for(int i=0;i<m_yingling.m_config.normal_size();i++)
	{
		for(int j=0;j<m_yingling.m_config.normal(i).p();j++)
			m_yingling_random_normal[yingling_normal_s++] = make_pair(m_yingling.m_config.normal(i).id(), m_yingling.m_config.normal(i).count());
	}
	int yingling_advance_s = 0;
	for(int i=0;i<m_yingling.m_config.advance_size();i++)
	{
		for(int j=0;j<m_yingling.m_config.advance(i).p();j++)
			m_yingling_random_advance[yingling_advance_s++] = make_pair(m_yingling.m_config.advance(i).id(), m_yingling.m_config.advance(i).count());
	}
	for(int i=0;i<m_yingling.m_config.exp_size();i++)
		m_yingling_exp[m_yingling.m_config.exp(i).id()] = i;
	for(int i=0;i<m_yingling.m_config.star_size();i++)
		m_yingling_star[m_yingling.m_config.star(i).id()] = i;
}

const BraveNewWorldConfig::Point& ConfigManager::GetBraveNewWorldConfigPoint(const pair<unsigned, unsigned>& p)
{
	if(!m_BraveNewWorldPoint.count(p))
		throw runtime_error("xy error");
	return m_BraveNewWorldConfig.m_config.land(m_BraveNewWorldPoint[p]);
}
const BraveNewWorldConfig::Property& ConfigManager::GetBraveNewWorldConfigProperty(const pair<unsigned, unsigned>& tl)
{
	if(!m_BraveNewWorldProperty.count(tl))
		throw runtime_error("tl error");
	return m_BraveNewWorldConfig.m_config.config(m_BraveNewWorldProperty[tl]);
}
const BraveNewWorldConfig::Property& ConfigManager::GetBraveNewWorldConfigPointProperty(const pair<unsigned, unsigned>& p)
{
	if(!m_BraveNewWorldPoint.count(p))
		throw runtime_error("xy error");
	pair<unsigned, unsigned> tl(m_BraveNewWorldConfig.m_config.land(m_BraveNewWorldPoint[p]).type(), m_BraveNewWorldConfig.m_config.land(m_BraveNewWorldPoint[p]).level());
	return GetBraveNewWorldConfigProperty(tl);
}
const BraveNewWorldConfig::Zone& ConfigManager::GetBraveNewWorldConfigZone(unsigned l)
{
	if(!m_BraveNewWorldZone.count(l))
		throw runtime_error("l error");
	return m_BraveNewWorldConfig.m_config.zone(m_BraveNewWorldZone[l]);
}
const BraveNewWorldConfig::City& ConfigManager::GetBraveNewWorldConfigCity(unsigned l)
{
	if(!m_BraveNewWorldCity.count(l))
		throw runtime_error("l error");
	return m_BraveNewWorldConfig.m_config.city(m_BraveNewWorldCity[l]);
}
const BraveNewWorldConfig::Tech& ConfigManager::GetBraveNewWorldConfigTech(unsigned j, unsigned t, unsigned l)
{
	unsigned i = l*9 + j*3 + t;
	if(m_BraveNewWorldConfig.m_config.tech_size() <= i)
		throw runtime_error("tech error");
	return m_BraveNewWorldConfig.m_config.tech(i);
}

const BraveNewWorldConfig::Technology &ConfigManager::GetBraveNewWorldConfigKeji(unsigned type,unsigned lv)
{
	if(lv) lv -= 1;
	const BraveNewWorldConfig::FortTechlonogy &conf = m_BraveNewWorldConfig.m_config.keji(type);
	if(lv < 0 || lv >= conf.node_size())
		throw runtime_error("lv_error");
	return conf.node(lv);
}
const BraveNewWorldConfig::FortTechlonogy &ConfigManager::GetTechNodeConf(unsigned type)
{
	return m_BraveNewWorldConfig.m_config.keji(type);
}

unsigned ConfigManager::GetOldSoulStoneA(unsigned id)
{
	if(m_OldSoulStoneA.count(id))
		return Math::GetRandomInt(m_OldSoulStoneA[id].second - m_OldSoulStoneA[id].first + 1) + m_OldSoulStoneA[id].first;
	throw runtime_error("id error");
}
unsigned ConfigManager::GetNewSoulStone(unsigned type)
{
	if(type >= NEW_STONE_NUM)
		throw runtime_error("type error");
	unsigned p = Math::GetRandomInt(m_NewSoulStoneP[type].rbegin()->first);
	for(map<unsigned, unsigned>::iterator it=m_NewSoulStoneP[type].begin();it!=m_NewSoulStoneP[type].end();++it)
	{
		if(p < it->first)
			return it->second;
	}
	throw runtime_error("p error");
}

pair<unsigned, unsigned> ConfigManager::GetYingLingRandom(unsigned type)
{
	if(type)
		return m_yingling_random_advance[Math::GetRandomInt(m_yingling_random_advance.rbegin()->first+1)];
	return m_yingling_random_normal[Math::GetRandomInt(m_yingling_random_normal.rbegin()->first+1)];
}
const YingLing::YingLingExp& ConfigManager::GetYingLingExp(unsigned id)
{
	if(!m_yingling_exp.count(id))
		throw runtime_error("id error");
	return m_yingling.m_config.exp(m_yingling_exp[id]);
}
const YingLing::YingLingStar& ConfigManager::GetYingLingStar(unsigned id)
{
	if(!m_yingling_star.count(id))
		throw runtime_error("id error");
	return m_yingling.m_config.star(m_yingling_star[id]);
}
