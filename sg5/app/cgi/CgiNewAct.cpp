/*
 * CgiNewAct.cpp
 *
 *  Created on: 2017-3-15
 *      Author: Ralf
 */

#include "LogicInc.h"
#include "LogicNewYearActive.h"

class CCgiNewAct: public CCgiBase {
public:
	CCgiNewAct() : CCgiBase("NewAct")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_GET_UID);
		SetFeature(CF_CHECK_SESSION);
		SetFeature(CF_CHECK_TIME);
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_CHECK_HASH);
		SetFeature(CF_CHECK_VERSION);
		SetFeature(CF_APPEND_HASH);
		SetFeature(CF_PARSE_DATA);
		SetFeature(CF_CRYPT_DATA);
		SetFeature(CF_DECRYPT_DATA);
		SetFeature(CF_COMPRESS_OUT);

		int ret = CLogicAllianceConsume::Init(CONFIG_ALLIANCE_CONSUME_DATA, false);
		if(ret)
			exit(ret);
		ret = CLogicNewYearActive::Init(CONFIG_NEWYEAR_ACTIVNE_DATA, false);
		if (ret)
			exit(ret);
	}

	CGI_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("AllianceShopInfo", AllianceShopInfo)
	CGI_SET_ACTION_MAP("AllianceShopBuy", AllianceShopBuy)
	CGI_SET_ACTION_MAP("AllianceShopLimit", AllianceShopLimit)
	CGI_SET_ACTION_MAP("AllianceShopGift", AllianceShopGift)

	CGI_SET_ACTION_MAP("GroupBuyingLoad", GroupBuyingLoad)
	CGI_SET_ACTION_MAP("GroupBuyingJoin", GroupBuyingJoin)

	CGI_SET_ACTION_MAP("newyearactivevisit", NewYearActiveVisit)
	CGI_SET_ACTION_MAP("newyearactiveinfo", NewYearActiveInfo)
	CGI_SET_ACTION_MAP("newyearactiverefresh", NewYearActiveRefresh)

	CGI_ACTION_MAP_END

	~CCgiNewAct()
	{
		CLogicAllianceConsume::Exit();
		CLogicNewYearActive::Exit();
	}

	void ProcessSig(int sig)
	{
		CLogicAllianceConsume::Sig(sig);
		CLogicNewYearActive::Sig(sig);
	}

	int AllianceShopInfo()
	{
		int ret = 0;

		unsigned aid;
		if (!Json::GetUInt(m_data, "aid", aid))
			return R_ERR_PARAM;

		CLogicAllianceConsume logicAllianceConsume;
		ret = logicAllianceConsume.AllianceShopInfo(aid, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=AllianceShopInfo&uid=%u", m_uid);
		return ret;
	}

	int AllianceShopBuy()
	{
		int ret = 0;

		unsigned aid;
		if (!Json::GetUInt(m_data, "aid", aid))
			return R_ERR_PARAM;
		unsigned index;
		if (!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;
		unsigned count;
		if (!Json::GetUInt(m_data, "count", count))
			return R_ERR_PARAM;

		CLogicAllianceConsume logicAllianceConsume;
		ret = logicAllianceConsume.AllianceShopBuy(m_uid, aid, index, count, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=AllianceShopBuy&uid=%u", m_uid);
		return ret;
	}

	int AllianceShopLimit()
	{
		int ret = 0;

		unsigned aid;
		if (!Json::GetUInt(m_data, "aid", aid))
			return R_ERR_PARAM;
		unsigned type;
		if (!Json::GetUInt(m_data, "type", type))
			return R_ERR_PARAM;
		unsigned index;
		if (!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;
		unsigned count;
		if (!Json::GetUInt(m_data, "count", count))
			return R_ERR_PARAM;

		CLogicAllianceConsume logicAllianceConsume;
		ret = logicAllianceConsume.AllianceShopLimit(m_uid, aid, type, index, count, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=AllianceShopLimit&uid=%u", m_uid);
		return ret;
	}

	int AllianceShopGift()
	{
		int ret = 0;

		unsigned aid;
		if (!Json::GetUInt(m_data, "aid", aid))
			return R_ERR_PARAM;
		unsigned index;
		if (!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;

		CLogicAllianceConsume logicAllianceConsume;
		ret = logicAllianceConsume.AllianceShopGift(m_uid, aid, index, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=AllianceShopGift&uid=%u", m_uid);
		return ret;
	}

	int GroupBuyingLoad()
	{
		int ret = 0;

		string url = "action=load";
		string uid;
		String::Format(uid, "%u", m_uid);
		url.append("&uid=");
		url += uid;

		CLogicAllServerBaseMatch logicBaseMatch;

		ret = logicBaseMatch.RequestBaseMatch(url, m_jsonResult, CONFIG_ALLSERVER_GROUPBUY_PATH, true);

		if (0 != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=GroupBuyingLoad&uid=%u", m_uid);
		return ret;
	}

	int GroupBuyingJoin()
	{
		int ret = 0;
		unsigned id;

		if (!Json::GetUInt(m_data, "id", id))
			return R_ERR_PARAM;

		string url = "action=join";
		string uid;
		String::Format(uid, "%u", m_uid);

		url.append("&uid=");
		url += uid;

		string sid;
		String::Format(sid, "%u", id);

		url.append("&id=");
		url += sid;

		CLogicAllServerBaseMatch logicBaseMatch;

		ret = logicBaseMatch.RequestBaseMatch(url, m_jsonResult, CONFIG_ALLSERVER_GROUPBUY_PATH, true);

		if (0 != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=GroupBuyingJoin&uid=%u", m_uid);
		return ret;
	}

	int NewYearActiveVisit()
	{
		unsigned userid = 0;
		Json::GetUInt(m_data, "userid", userid);
		CLogicNewYearActive logicNewYearActive;
		int ret = logicNewYearActive.Visit(m_uid, userid, m_jsonResult);
		if (ret)
		{
			return ret;
		}
		CGI_SEND_LOG("action=newyearactivevisit&uid=%u&userid=%u", m_uid, userid);
		return 0;
	}

	int NewYearActiveInfo()
	{
		unsigned userid = 0;
		Json::GetUInt(m_data, "userid", userid);
		CLogicNewYearActive logicNewYearActive;
		int ret = logicNewYearActive.GetInfo(userid, m_uid, m_jsonResult);
		if (ret)
		{
			return ret;
		}
		CGI_SEND_LOG("action=newyearactiveinfo&uid=%u&userid=%u", m_uid, userid);
		return 0;
	}

	int NewYearActiveRefresh()
	{
		CLogicNewYearActive logicNewYearActive;
		int ret = logicNewYearActive.Refresh(m_uid, m_jsonResult);
		if (ret)
		{
			return ret;
		}
		CGI_SEND_LOG("action=newyearactiverefresh&uid=%u", m_uid);
		return 0;
	}
};

CGI_MAIN(CCgiNewAct)


