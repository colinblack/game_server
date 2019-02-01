/*
 * ConfigManager.h
 *
 *  Created on: 2016-8-22
 *      Author: Ralf
 */

#ifndef CONFIGMANAGER_H_
#define CONFIGMANAGER_H_

#include "Kernel.h"
#include "ConfigPB.h"
#include "ConfigInc.h"

class ConfigManager
{
private:
	ConfigManager()
		:m_BraveNewWorldConfig("BraveNewWorldConfig.json")
		,m_AllianceConsumeConfig("AllianceConsumeConfig.json")
		,m_CompoundConfig("compound_shred.json")
		,m_yingling("yingling.json")
		,m_groupbuyConfig("baifutuangou.json")
		,m_scrollactivitycfg("scrollactivity.json")
		,m_kingtreasurecfg("kingtreasure.json")
		,m_scrollfeedbackcfg("scroll_feedback.json")
		,m_tokenupgradecfg("upgrade_token.json")
		,m_activitycfg("activityconfig.json")
		,m_twoholidaycfg("TwoHolidayEnjoyCfg.json")
		,m_functionscfg("functionConfig.json")
		,m_newsoulstone("newsoulstone.json")
	{
		Init();
	}

	void Init();
	static bool m_init;
	static ConfigManager* m_pData;

public:
	virtual ~ConfigManager(){}
	static void Fail(){m_init = false;}
	static ConfigManager* Instance();

	const ConfigPB<YingLing::YingLing> m_yingling;
	const ConfigPB<BraveNewWorldConfig::BraveNewWorldConfig> m_BraveNewWorldConfig;
	const ConfigPB<AllianceConsumeConfig::AllianceConsumeConfig> m_AllianceConsumeConfig;
	const ConfigPB<CompoundShredConfig::ShredCompounds> m_CompoundConfig;
	const ConfigPB<GroupBuyingConfig::GroupBuyingItemsCfg> m_groupbuyConfig;
	const ConfigPB<ConfigScrollActivity::ScrollActivity> m_scrollactivitycfg;
	const ConfigPB<ConfigKingTreasure::KingTreasure> m_kingtreasurecfg;
	const ConfigPB<ConfigScrollFeedback::ScrollFeedBack> m_scrollfeedbackcfg;
	const ConfigPB<ConfigTokenUpgrade::TokenUpgrade> m_tokenupgradecfg;
	const ConfigPB<ConfigActivity::Activities> m_activitycfg;
	const ConfigPB<TwoHolidayConfig::TwoHolidayItmCfg> m_twoholidaycfg;
	const ConfigPB<ConfigFunction::Functions> m_functionscfg;
	const ConfigPB<NewSoulStone::NewSoulStone> m_newsoulstone;

	map<unsigned, pair<unsigned, unsigned> > m_yingling_random_normal;
	map<unsigned, pair<unsigned, unsigned> > m_yingling_random_advance;
	map<unsigned, unsigned> m_yingling_exp;
	map<unsigned, unsigned> m_yingling_star;

	pair<unsigned, unsigned> GetYingLingRandom(unsigned type);
	const YingLing::YingLingExp& GetYingLingExp(unsigned id);
	const YingLing::YingLingStar& GetYingLingStar(unsigned id);

	map<pair<unsigned, unsigned>, unsigned> m_BraveNewWorldPoint;
	map<pair<unsigned, unsigned>, unsigned> m_BraveNewWorldProperty;
	map<unsigned, unsigned> m_BraveNewWorldZone;
	map<unsigned, unsigned> m_BraveNewWorldCity;

	const BraveNewWorldConfig::Point& GetBraveNewWorldConfigPoint(const pair<unsigned, unsigned>& p);
	const BraveNewWorldConfig::Property& GetBraveNewWorldConfigProperty(const pair<unsigned, unsigned>& tl);
	const BraveNewWorldConfig::Property& GetBraveNewWorldConfigPointProperty(const pair<unsigned, unsigned>& p);
	const BraveNewWorldConfig::Zone& GetBraveNewWorldConfigZone(unsigned l);
	const BraveNewWorldConfig::City& GetBraveNewWorldConfigCity(unsigned l);
	const BraveNewWorldConfig::Tech& GetBraveNewWorldConfigTech(unsigned j, unsigned t, unsigned l);

	map<unsigned, unsigned> m_compoundId;  //碎片id与下标的映射
	map<unsigned, pair<unsigned, unsigned> > m_scrollIndex;  //古卷专项活动的映射. id-><dayIndex, affarindex>
	map<unsigned, unsigned> m_treasureIndex;  //宝箱id与下标的映射

	map<unsigned, pair<unsigned, unsigned> > m_OldSoulStoneA;
	map<unsigned, unsigned> m_NewSoulStoneP[NEW_STONE_NUM];

	unsigned GetOldSoulStoneA(unsigned id);
	unsigned GetNewSoulStone(unsigned type);
};

#endif /* CONFIGMANAGER_H_ */
