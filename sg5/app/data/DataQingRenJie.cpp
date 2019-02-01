/*
 * DataQingRenJie.cpp
 */


#include "DataQingRenJie.h"
#include "ConfigManager.h"
#include "LogicEquipment.h"
#include "LogicSecinc.h"
#include "LogicPay.h"
#include "LogicCmdBase.h"

CDataQingRenJie::CDataQingRenJie(string path)
	: DataBase(path)
{
	m_msg = new QingRenJie::QingRenJie();
}

int CDataQingRenJie::Init()
{
	int ret = Parse();
	if(ret && ret != R_ERR_NO_DATA)
		return ret;

	ActInfoConfig actconfig(CONFIG_QINGRENJIE_MEIGUI);
	if(ret != R_ERR_NO_DATA)
	{
		m_data.Parse(*(QingRenJie::QingRenJie *)m_msg);

		if(m_data.ver != actconfig.Version())
		{
			m_data.ver = actconfig.Version();
			m_data.rewarded = 0;
			m_data.nvshen.clear();
		}
	}
	m_data.ver = actconfig.Version();

	((QingRenJie::QingRenJie *)m_msg)->Clear();

	return 0;
}
int CDataQingRenJie::Save()
{
	m_data.Serialize((QingRenJie::QingRenJie *)m_msg);

	int ret = Serialize();

	((QingRenJie::QingRenJie *)m_msg)->Clear();

	return ret;
}

int CDataQingRenJie::SongHua(unsigned uid, unsigned nsid, unsigned num, Json::Value &result)
{
	m_data.Add(uid, nsid, num);
	m_data.GetJson(result);
	return 0;
}

int CDataQingRenJie::GetInfo(Json::Value &result)
{
	ActInfoConfig actconfig(CONFIG_QINGRENJIE_MEIGUI);
	if (!actconfig.IsActive())
	{
		LOGIC_ERROR_RETURN_MSG("activity is over");
	}
	if(m_data.ver != actconfig.Version())
	{
		m_data.ver = actconfig.Version();
		m_data.rewarded = 0;
		m_data.nvshen.clear();
	}
	m_data.GetJson(result);
	if (!m_data.rewarded && actconfig.EndTS() - Time::GetGlobalTime() <= 3600*2) {
		m_data.rewarded  = 1;
		unsigned max_num = 0;
		unsigned max_nsid = 1;
		for (map<unsigned int, DataQingRenJieNvShen>::iterator it = m_data.nvshen.begin(); it!=m_data.nvshen.end(); ++it) {
			if (max_num < (it->second).num)
			{
				max_num = (it->second).num;
				max_nsid = (it->second).nsid;
			}
		}
		vector<GiftEquipItem> reward;
		string code = "QingRenJieXianHuaQuanFu";
		CDataXML *dataXML = CDataXML::GetCDataXML();
		if(!dataXML)
		{
			error_log("GetInitXML fail");
			return R_ERR_DB;
		}
		DataXMLQingRenJieMeiGui config;
		int ret = dataXML->GetQingRenJieMeiGuitem(config);
		if (ret)
		{
			return ret;
		}
		for (int i=0;i<XML_QINGRENJIE_MEIGUI_REWARD_NUM;i++)
			reward.push_back(config.quanfu[max_nsid-1].reward[i]);

		Json::Value equip;
		set<unsigned> uidset;
		string email_title = "情人节女神特殊奖励";
		string name[XML_QINGRENJIE_NVSHEN_NUM] = {"祝融","貂蝉","小乔","大乔","甄姬","马云禄","蔡文姬"};
		string email_text = name[max_nsid-1]+"女神在情人节活动中收获玫瑰数量最多，向献过花的玩家们发放特殊奖励："+name[max_nsid-1]+"女神包*1！";
		vector<uint64_t> uids;
		for (map<unsigned int, DataQingRenJieNvShen>::iterator it = m_data.nvshen.begin(); it!=m_data.nvshen.end(); ++it) {
			for (map<unsigned int, DataQingRenJieUser>::iterator it2 = it->second.user.begin(); it2!=it->second.user.end(); ++it2) {
				if (!uidset.count(it2->first)) {
					uidset.insert(it2->first);
					BaseCmdUnit basecmdUnit(it2->first);
					basecmdUnit.AddGiftEquips(reward, code, equip);

					/*
					CLogicEmail logicEmail;
					uids.clear();
					uids.push_back(it2->first);
					logicEmail.SystemEmail(email_title, email_text, uids);
					*/
					Json::Value updates;
					CLogicUpdates logicUpdates;
					updates["s"] = "QingRenJieMeiGui";
					updates["nsid"] = max_nsid;
					updates["ts"] = Time::GetGlobalTime();
					logicUpdates.AddUpdates(it2->first,updates,true);
				}
			}
		}
	}
	return 0;
}
