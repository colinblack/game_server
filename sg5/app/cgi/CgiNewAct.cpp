/*
 * CgiNewAct.cpp
 *
 *  Created on: 2017-3-15
 *      Author: Ralf
 */

#include "LogicInc.h"
#include "LogicNewYearActive.h"
#include "LogicQunXing.h"

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
		if (ret) {
			exit(ret);
		}
		ret = CLogicNewYearActive::Init(CONFIG_NEWYEAR_ACTIVNE_DATA, false);
		if (ret) {
			exit(ret);
		}
		ret = CLogicQingRenJie::Init(CONFIG_QINGRENJIE_DATA, true);
		if (ret) {
			exit(ret);
		}
		ret = CLogicNewDouJiang::Init(CONFIG_NEWDOUJIANG_DATA, OpenPlatform::GetType() == PT_4399 || OpenPlatform::GetType() == PT_NEW_4399);
		if (ret) {
			exit(ret);
		}
		ret = CLogicQunXing::Init(CONFIG_QUNXING_DATA, false);
		if (0 != ret) {
			exit(ret);
		}
		ret = CLogicGiveHelpActive::Init(CONFIG_GIVEHELPACTION_DATA, false);
		if(ret) {
			exit(ret);
		}
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

	CGI_SET_ACTION_MAP("QingRenJieXianHua", QingRenJieXianHua)
	CGI_SET_ACTION_MAP("QingRenJieLeiJi", QingRenJieLeiJi)
	CGI_SET_ACTION_MAP("GetQingRenJie", GetQingRenJie)

	CGI_SET_ACTION_MAP("GetStartGiveHelpList", GetStartGiveHelpList)
	CGI_SET_ACTION_MAP("ClickGiveHelpList", ClickGiveHelpList)
	CGI_SET_ACTION_MAP("GiveHelpRetail", GiveHelpRetail)
	CGI_SET_ACTION_MAP("DelGiveHelp", DelGiveHelp)

	CGI_SET_ACTION_MAP("getqunxingtable", GetQunXingInfo)
	CGI_SET_ACTION_MAP("addqunxinghero", SetQunXingHero)
	CGI_SET_ACTION_MAP("delqunxinghero", DelQunXingHero)

	CGI_SET_ACTION_CHECKVERSION_MAP("SetZhenRong", SetZhenRong, CheckChongBang3Version)
	CGI_SET_ACTION_CHECKVERSION_MAP("GetZhenRong", GetZhenRong, CheckChongBang3Version)
	CGI_SET_ACTION_CHECKVERSION_MAP("GetMyList", GetMyList, CheckChongBang3Version)
	CGI_SET_ACTION_CHECKVERSION_MAP("PiPei", PiPei, CheckChongBang3Version)
	CGI_SET_ACTION_CHECKVERSION_MAP("StartAttack", StartAttack, CheckChongBang3Version)
	CGI_SET_ACTION_CHECKVERSION_MAP("SetResult", SetResult, CheckChongBang3Version)
	CGI_SET_ACTION_CHECKVERSION_MAP("GetRankList", GetRankList, CheckChongBang3Version)
	CGI_SET_ACTION_CHECKVERSION_MAP("GetZhanBao", GetZhanBao, CheckChongBang3Version)

	CGI_ACTION_MAP_END

	~CCgiNewAct()
	{
		CLogicAllianceConsume::Exit();
		CLogicNewYearActive::Exit();
		CLogicQingRenJie::Exit();
		CLogicNewDouJiang::Exit();
		CLogicGiveHelpActive::Exit();
		CLogicQunXing::Exit();
	}

	void ProcessSig(int sig)
	{
		CLogicAllianceConsume::Sig(sig);
		CLogicNewYearActive::Sig(sig);
		CLogicQingRenJie::Sig(sig);
		CLogicNewDouJiang::Sig(sig);
		CLogicGiveHelpActive::Sig(sig);
		CLogicQunXing::Sig(sig);
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

	int QingRenJieXianHua()
	{
		unsigned nsid;
		if (!Json::GetUInt(m_data, "nsid", nsid))
			return R_ERR_PARAM;

		unsigned num;
		if (!Json::GetUInt(m_data, "num", num))
			return R_ERR_PARAM;

		unsigned type;
		if (!Json::GetUInt(m_data, "type", type))
			return R_ERR_PARAM;

		CLogicQingRenJie logicQingRenJie;
		int ret = logicQingRenJie.QingRenJieXianHua(m_uid, nsid, type, num, m_jsonResult["result"]);
		if (ret)
		{
			return ret;
		}
		CGI_SEND_LOG("action=QingRenJieXianHua&uid=%u", m_uid);
		return 0;
	}

	int QingRenJieLeiJi()
	{
		unsigned id;
		if (!Json::GetUInt(m_data, "id", id))
			return R_ERR_PARAM;

		CLogicQingRenJie logicQingRenJie;
		int ret = logicQingRenJie.QingRenJieLeiJi(m_uid, id, m_jsonResult["result"]);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=QingRenJieLeiJi&uid=%u", m_uid);
		return 0;
	}

	int GetQingRenJie()
	{
		CLogicQingRenJie logicQingRenJie;
		int ret = logicQingRenJie.GetQingRenJie(m_jsonResult["info"]);
		if (ret)
		{
			return ret;
		}
		CGI_SEND_LOG("action=GetQingRenJie&uid=%u", m_uid);
		return 0;
	}

	int GetQunXingInfo() {
		CLogicQunXing logicQunXing;
		unsigned type = 0;
		Json::GetUInt(m_data, "type", type);
		int ret = logicQunXing.GetInfo(m_uid, type, m_jsonResult);
		if (0 != ret ) {
			return ret;
		}
		CGI_SEND_LOG("action=getqunxingtable&uid=%u", m_uid);
		return 0;
	}

	int SetQunXingHero() {
		int ret = 0;
		CLogicQunXing logicQunXing;
		unsigned type = 0, id = 0, hud = 0, hid = 0, power = 0;
		string smid, hname;
		Json::GetUInt(m_data, "type", type);
		Json::GetUInt(m_data, "id", id);
		Json::GetUInt(m_data, "hud", hud);
		Json::GetUInt(m_data, "hid", hid);
		Json::GetUInt(m_data, "power", power);
		Json::GetString(m_data, "smid", smid);
		Json::GetString(m_data, "hname", hname);

		ret = logicQunXing.AddGuest(m_uid, type, id, hud, hid, power, smid, hname, m_jsonResult);
		if (0 != ret) {
			return ret;
		}

		CGI_SEND_LOG("action=setqunxinghero&uid=%u&type=%u&id=%u&hud=%u&hid=%u&power=%u&smid=%s",
				m_uid, type, id, hud, hid, power, smid.c_str());
		return 0;
	}

	int DelQunXingHero() {
		int ret = 0;
		CLogicQunXing logicQunXing;
		unsigned type = 0, id = 0, userid = 0;
		Json::GetUInt(m_data, "type", type);
		Json::GetUInt(m_data, "id", id);
		Json::GetUInt(m_data, "userid", userid);
		ret = logicQunXing.DelGuest(m_uid, type, id, userid, m_jsonResult);
		if (0 != ret) {
			return ret;
		}
		CGI_SEND_LOG("action=setqunxinghero&uid=%u&type=%u&id=%u&userid=%u&", m_uid, type, id, userid);
		return 0;
	}

	void CheckChongBang3Version()
	{
		CLogicNewDouJiang logicNewDouJiang;
		logicNewDouJiang.CheckVersion();
	}

	int SetZhenRong()
	{
		int ret = 0;

		if(!m_data.isMember("zhen") || !m_data["zhen"].isArray() || m_data["zhen"].size()!=9 )
		{
			error_log("[zhen_error][uid=%u]",m_uid);
			return R_ERR_PARAM;
		}
		vector<unsigned> z;
		for(unsigned i=0;i<m_data["zhen"].size();++i)
			z.push_back(m_data["zhen"][i].asUInt());

		CLogicNewDouJiang logicNewDouJiang;
		ret = logicNewDouJiang.SetZhenRong(m_uid, z, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=SetZhenRong&uid=%u", m_uid);
		return 0;
	}

	int GetZhenRong()
	{
		int ret = 0;

		unsigned uid2;
		if (!Json::GetUInt(m_data, "uid2", uid2))
			return R_ERR_PARAM;

		CLogicNewDouJiang logicNewDouJiang;
		ret = logicNewDouJiang.GetZhenRong(uid2, m_jsonResult["result"]);
		if(ret)
			return ret;
		CGI_SEND_LOG("action=GetZhenRong&uid=%u", m_uid);
		return 0;
	}

	int GetMyList()
	{
		int ret = 0;

		CLogicNewDouJiang logicNewDouJiang;
		ret = logicNewDouJiang.GetMyList(m_uid, m_jsonResult["result"]);
		if(ret)
			return ret;
		CGI_SEND_LOG("action=GetMyList&uid=%u", m_uid);
		return 0;
	}

	int PiPei()
	{
		int ret = 0;

		unsigned seq;
		if (!Json::GetUInt(m_data, "seq", seq))
		{
			error_log("[seq_error][uid=%u]",m_uid);
			return R_ERR_PARAM;
		}

		CLogicNewDouJiang logicNewDouJiang;
		ret = logicNewDouJiang.PiPei(m_uid, seq, m_jsonResult["result"]);
		if(ret)
			return ret;
		CGI_SEND_LOG("action=PiPei&uid=%u", m_uid);
		return 0;
	}

	int StartAttack()
	{
		int ret = 0;
		unsigned type; //1匹配 2复仇 3追杀
		if (!Json::GetUInt(m_data, "type", type) || type < 1 || type > 3)
			return R_ERR_PARAM;

		unsigned uid2;
		if (!Json::GetUInt(m_data, "uid2", uid2))
			return R_ERR_PARAM;

		unsigned hud;
		if (!Json::GetUInt(m_data, "hud", hud))
			return R_ERR_PARAM;

		unsigned seq;
		if (!Json::GetUInt(m_data, "seq", seq))
		{
			error_log("[seq_error][uid=%u]",m_uid);
			return R_ERR_PARAM;
		}

		unsigned ud;
		Json::GetUInt(m_data, "ud", ud);

		unsigned fcts;
		if (type == 2)
		{
			if (!Json::GetUInt(m_data, "fcts", fcts))
			{
				error_log("[fcts_error][uid=%u]",m_uid);
				return R_ERR_PARAM;
			}
		}

		CLogicNewDouJiang logicNewDouJiang;
		ret = logicNewDouJiang.StartAttack(m_uid, type, uid2, hud, seq, ud, m_jsonResult["result"],fcts);
		if(ret)
			return ret;
		CGI_SEND_LOG("action=StartAttack&uid=%u", m_uid);
		return 0;
	}

	int SetResult()
	{
		int ret = 0;
		unsigned type; //1匹配 2复仇 3追杀
		if (!Json::GetUInt(m_data, "type", type) || type < 1 || type > 3)
			return R_ERR_PARAM;

		unsigned uid2;
		if (!Json::GetUInt(m_data, "uid2", uid2))
			return R_ERR_PARAM;

		unsigned win;
		if (!Json::GetUInt(m_data, "win", win))
			return R_ERR_PARAM;

		unsigned hud;
		if (!Json::GetUInt(m_data, "hud", hud))
			return R_ERR_PARAM;

		unsigned seq;
		if (!Json::GetUInt(m_data, "seq", seq))
		{
			error_log("[seq_error][uid=%u]",m_uid);
			return R_ERR_PARAM;
		}

		unsigned ud;
		Json::GetUInt(m_data, "ud", ud);

		CLogicNewDouJiang logicNewDouJiang;
		ret = logicNewDouJiang.SetResult(m_uid, type, uid2, win, hud, seq, ud, m_jsonResult["result"]);
		if(ret)
			return ret;
		CGI_SEND_LOG("action=SetResult&uid=%u", m_uid);
		return 0;
	}

	int GetRankList()
	{
		CLogicNewDouJiang logicNewDouJiang;
		int ret = logicNewDouJiang.GetRankList(m_uid, m_jsonResult["result"]);
		if(ret)
			return ret;
		CGI_SEND_LOG("action=GetRankList&uid=%u", m_uid);
		return 0;
	}

	int GetZhanBao()
	{
		int ret = 0;

		CLogicNewDouJiang logicNewDouJiang;
		ret = logicNewDouJiang.GetZhanBao(m_uid, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=GetZhanBao&uid=%u", m_uid);
		return ret;
	}

	int GetStartGiveHelpList()
	{
		int ret = 0;
		CLogicGiveHelpActive logicGiveHelp;
		ret = logicGiveHelp.GetStartGiveHelpList(m_uid, m_jsonResult);
		if(ret) {
			error_log("GetStartGiveHelpList error");
			return ret;
		}
		CGI_SEND_LOG("action=GetStartGiveHelpList&uid=%u", m_uid);
		return 0;
	}

	int ClickGiveHelpList()
	{
		int ret = 0;
		unsigned to_uid = 0;
		if(!Json::GetUInt(m_data,"tuid",to_uid)) {
			error_log("get tuid error");
			return R_ERR_PARAM;
		}
		if(to_uid && to_uid == m_uid) {
			LOGIC_ERROR_RETURN_MSG("Operation_error");
		}
		CLogicGiveHelpActive logicGiveHelp;
		ret = logicGiveHelp.ClickGiveHelpList(to_uid, m_uid, m_jsonResult);
		if(ret) {
			return ret;
		}
		CGI_SEND_LOG("action=ClickGiveHelpList&uid=%u", m_uid);
		return 0;
	}

	int GiveHelpRetail()
	{
		int ret = 0;
		CLogicGiveHelpActive logicGiveHelp;
		ret = logicGiveHelp.GiveHelpRetail(m_uid, m_jsonResult);
		if(ret) {
			return ret;
		}
		CGI_SEND_LOG("action=GiveHelpRetail&uid=%u", m_uid);
		return 0;
	}

	int DelGiveHelp() {
		int ret = 0;
		unsigned userid = 0;
		if(!Json::GetUInt(m_data, "userid", userid)) {
			return R_ERR_PARAM;
		}
		CLogicGiveHelpActive logicGiveHelp;
		ret = logicGiveHelp.DelHelper(m_uid, userid, m_jsonResult);
		if(ret) {
			return ret;
		}
		CGI_SEND_LOG("action=DelGiveHelp&uid=%u&userid=%u", m_uid, userid);
		return 0;
	}
};

CGI_MAIN(CCgiNewAct)


