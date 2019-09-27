/*
 * TransitManager.cpp
 *
 *  Created on: 2016-3-15
 *      Author: Administrator
 */

#include "TransitManager.h"
#include "TencentAsyncManager.h"
#include "DataPayHistory.h"
#include "DataIdctrl.h"
#include "TransitServer.h"
#include "LogicMidasPay.h"
#include "PbMessage.h"
#include <fstream>

static map<int, string> m_platformMap;

TransitManager::TransitManager() {
	m_ts = 0;
	m_ids.clear();
}

TransitManager::~TransitManager() {
}

bool TransitManager::HttpBody(string &msg, uint32_t &method, string &route, string &body) {
	size_t hpos = msg.find("\r\n\r\n");
	if (hpos == string::npos || hpos + 4 > msg.length()) {
		error_log("pos error %s", msg.c_str());
		return false;
	}
	string head = msg.substr(0, hpos);
	vector<string> ver_head;
	CBasic::StringSplitTrim(head, "\r\n", ver_head);
	if (ver_head.empty()) {
		error_log("head error %s", msg.c_str());
		return false;
	}

	vector<string> ver;
	CBasic::StringSplitTrim(ver_head[0], " ", ver);
	if (ver.size() < 3) {
		return false;
	}

	if (ver[0] == "POST" || ver[0] == "post") {
		method = HTTP_POST;
	}

	if (ver[0] == "GET" || ver[0] == "get") {
		method = HTTP_GET;
	}

	route = ver[1];

	body = msg.substr(hpos + 4);

	return true;
}

bool TransitManager::init() {
	Time::UpdateGlobalTime();
	m_platformMap[PF_TEST] = "test";
	m_platformMap[PF_WB] = "wanba_ts";
	m_platformMap[PF_C6] = "c6";

	if (!OpenPlatform::Init("qzone")) {
		error_log("openPlatform init failed");
		return false;
	}
	if (!busiLogInit()) {
		error_log("busiLogInit failed");
		return false;
	}
	initIds();
	return true;
}
bool TransitManager::initIds() {
	string path = Config::GetValue(WANBA_GIFT_PATH);
	fstream input(path.c_str(), ios::in | ios::binary);
	if (!input.good()) {
		error_log("open file error path=%s", path.c_str());
		return false;
	}
	WanBaGift::Daily msg;
	if (!msg.ParseFromIstream(&input)) {
		error_log("parse file error path=%s", path.c_str());
		return false;
	}
	m_ts = msg.ts();
	if (CTime::GetDayInterval(m_ts, Time::GetGlobalTime()) == 0) {
		for (int i = 0; i < msg.ids_size(); ++i) {
			set<uint32_t> &ids = m_ids[msg.ids(i).openid()];
			for (int j = 0; j < msg.ids(i).gift_size(); ++j) {
				ids.insert(msg.ids(i).gift(j));
			}
		}
	}
	return true;
}
bool TransitManager::saveIds() {
	string path = Config::GetValue(WANBA_GIFT_PATH);
	fstream output(path.c_str(), ios::out | ios::binary);
	if (!output.good()) {
		error_log("open file error path=%s", path.c_str());
		return false;
	}

	WanBaGift::Daily msg;
	if (m_idsMutex.acquire() == 0) {
		map<string, set<uint32_t> >::iterator itr = m_ids.begin();
		for (; itr != m_ids.end(); ++itr) {
			WanBaGift::User *user = msg.add_ids();
			user->set_openid(itr->first);
			set<uint32_t>::iterator it = itr->second.begin();
			for (; it != itr->second.end(); ++it) {
				user->add_gift(*it);
			}
		}
		msg.set_ts(m_ts);
		m_idsMutex.release();
	}
	if (!msg.SerializeToOstream(&output)) {
		error_log("serialize file error path=%s", path.c_str());
		return false;
	}
	return true;
}
bool TransitManager::getId(const string &openid, uint32_t gift) {
	bool ret = false;
	if (m_idsMutex.acquire() == 0) {
		if (CTime::GetDayInterval(m_ts, Time::GetGlobalTime()) != 0) {
			m_ts = Time::GetGlobalTime();
			m_ids.clear();
		}
		map<string, set<uint32_t> >::const_iterator itr = m_ids.find(openid);
		if (itr == m_ids.end()) {
			ret = false;
		} else {
			ret = (itr->second.count(gift) > 0);
		}
		m_idsMutex.release();
	}
	return ret;
}
bool TransitManager::setId(const string &openid, uint32_t gift) {
	if (m_idsMutex.acquire() == 0) {
		if (CTime::GetDayInterval(m_ts, Time::GetGlobalTime()) != 0) {
			m_ts = Time::GetGlobalTime();
			m_ids.clear();
		}
		set<uint32_t> &ids = m_ids[openid];
		ids.insert(gift);
		m_idsMutex.release();
	}
	return true;
}
bool TransitManager::doLoginPacket(CNetPacket*packet) {
	switch (packet->subCmd) {
	case PROTOCOL_SUBCMD_TRANSIT_LOGIN:
		doLogin(packet);
		doGetFriend(packet);
		break;
	case PROTOCOL_SUBCMD_TRANSIT_OFFLINE:
		doOffline(packet);
		break;
	case PROTOCOL_SUBCMD_TRANSIT_GET_BALANCE:
		doGetBalance(packet);
		break;
	case PROTOCOL_SUBCMD_TRANSIT_PAY:
		doPay(packet);
		break;
	case PROTOCOL_SUBCMD_TRANSIT_REPORT:
		doReport(packet);
		break;
	case PROTOCOL_SUBCMD_TRANSIT_GIFT_EXHANGE:
		doGiftExchange(packet);
		break;
	case PROTOCOL_SUBCMD_TRANSIT_PER_ORDER:
		doPreOrder(packet);
		break;
	default:
		error_log("unkonw subCmd=%u", packet->subCmd);
	}
	return true;
}

bool TransitManager::doTencentPacket(TencentPacket* packet){
	int netfd = packet->netfd;
	string url = packet->msg;
	uint32_t method = 0;
	string route;
	string http_body;
	HttpBody(packet->msg, method, route, http_body);

	if (route == "/qqmini") {
		return doQQMiniCallBack(netfd, http_body, route);
	}

	if(url.empty())
	{
		error_log("getReceiveData failed");
		return sendSDKServer(netfd, false);
	}

	string::size_type pos = url.find("\r\n\r\n");
	int size = url.length();

	if(pos == string::npos || pos + 4 == url.length())
	{
		error_log("find http body failed by pos %lu", pos);
		return sendSDKServer(netfd, false);
	}

	string bodyHttp = url.substr(pos+4);
	int count = bodyHttp.find_last_of(" ");
	string body = bodyHttp.substr(0, count);
	count = body.find_last_of("&");
	string left = body.substr(0, count);
	count = body.find_last_of("=");
	string ext = body.substr(count+1);

	count = left.find_last_of("&");
	string check = left.substr(0, count);
	count = left.find_last_of("=");
	string checkSig = left.substr(count+1);

	vector<string> vbody;
	String::Split(check, '&', vbody);

	map<string, string> dataMap;
	for(vector<string>::iterator iter = vbody.begin(); iter != vbody.end(); ++iter)
	{
		pos = iter->find("=");
		size = iter->length();
		if(pos == string::npos)
		{
			error_log("find = failed by pos %u", pos);
			return sendSDKServer(netfd, false);
		}
		dataMap[iter->substr(0, pos)] = Crypt::UrlDecode(iter->substr(pos + 1, size - pos - 1));
	}

	string openid  = dataMap["mem_id"];
	string orderid = dataMap["order_id"];
	int orderStatus = atoi(dataMap["order_status"].c_str());
	int productPrice = atof(dataMap["product_price"].c_str()) * 100;
	unsigned time = atol(dataMap["pay_time"].c_str());
	unsigned productId = 0;
	std::size_t offest = dataMap["product_id"].find_first_of('_');
	if(offest != string::npos)
		productId = atoi(dataMap["product_id"].substr(offest+1).c_str());
	else
		productId = atoi( dataMap["product_id"].c_str());

	IOpenPlatform *pPlatform = OpenPlatform::GetPlatform();
	if (pPlatform == NULL)
	{
		error_log("GetPlatform error");
		return sendSDKServer(netfd, false);
	}

	string encodePair;
	for(map<string, string>::iterator iter = dataMap.begin(); iter != dataMap.end(); )
	{
		encodePair += iter->first + "=" + Crypt::UrlEncodeForTX(iter->second);
		if(++iter != dataMap.end())
			encodePair += "&";
	}
	encodePair += "&app_key=";
	encodePair += OpenPlatform::GetPlatform()->GetConfig("c6_appkey");

	string sig = Crypt::Md5Encode(encodePair);

	if(sig != checkSig)
	{
		error_log("sign error, %s, %s, %s", url.c_str(), checkSig.c_str(), sig.c_str());
		return sendSDKServer(netfd, false);
	}

	if(orderStatus != 2)
	{
		error_log("order_status error %d", orderStatus);
		return sendSDKServer(netfd, false);
	}

	unsigned uid = atol(ext.c_str());
	if(!IS_VALID_PLAYER_UID(uid))
	{
		error_log("get user id error, openid=%s", openid.c_str());
		return sendSDKServer(netfd, false);
	}

	DataPayHistory payHis;
	CDataPayHistory dbPayHis;
	int ret = dbPayHis.GetPayHistory(uid, OpenPlatform::GetType(), orderid, payHis);
	if (0 == ret)
		return sendSDKServer(netfd, true);

	QQItemInfo itemInfo;
	ret = CLogicQQPay::GetItemInfo(productId, OSPT_IOS, itemInfo);
	if (ret)
	{
		error_log("[GetItemInfo fail][ret=%d]", ret);
		return sendSDKServer(netfd, false);
	}

	uint32_t nextPayId = 0;
	if (getNextPayId(nextPayId, Config::GetZoneByUID(uid)))
	{
		DataPayHistory payhis;
		payhis.pay_id  = nextPayId;
		payhis.channel = PT_C6_IOS;
		payhis.channel_pay_id = orderid;
		payhis.count = productPrice;
		payhis.credit = productPrice;
		payhis.status = 1;
		payhis.type = productId;
		payhis.uid = uid;
		payhis.open_id = openid;
		payhis.time = time;

		ret = CDataPayHistory().AddPayHistory(payhis);
		if (ret != 0)
		{
			error_log("[AddPayHistory fail][ret=%d,openid=%s,order_id=%s,product_id=%u,product_price=%d]",
					ret,openid.c_str(),orderid.c_str(),productId,productPrice);
		}
	}
	else
	{
		error_log("get next pay id error uid=%u", uid);
	}

	onPay(uid, TRANSIT_RESULT_SUCCESS, productId, orderid, itemInfo.cash, productPrice);
	sendSDKServer(netfd, true);

	BUSI_BUY("%u|%u|%d|%s|%s",uid, productId, productPrice, orderid.c_str(), "buy");

	return true;
}

bool TransitManager::sendSDKServer(int fd, bool isSuccess){
	string msg = isSuccess ? "SUCCESS" : "FAILURE";
	string sendMsg = "HTTP/1.0 200 OK\r\nContent-type: text/html; charset=UTF-8\r\nContent-Length: ";
	sendMsg += Convert::IntToString(msg.length()) + "\r\nConnection: close\r\n\r\n" + msg;
	int len = send(fd, sendMsg.c_str(), sendMsg.length(), 0);
	if(len <= 0) {
		error_log("send sdk server error log failed");
		return false;
	}
	return true;
}

bool TransitManager::sendQQMini(int fd, bool isSuccess) {
	Json::Value value;
	if (isSuccess) {
		value["code"] = 0;
		value["msg"] = "Success";
	} else {
		value["code"] = 1;
		value["msg"] = "Failure";
	}
	string msg = Json::ToString(value);
	string sendMsg = "HTTP/1.0 200 OK\r\nContent-type: text/html; charset=UTF-8\r\nContent-Length: ";
	sendMsg += Convert::IntToString(msg.length()) + "\r\nConnection: close\r\n\r\n" + msg;
	int len = send(fd, sendMsg.c_str(), sendMsg.length(), 0);
	if (len <= 0) {
		error_log("send sdk server error log failed");
		return false;
	}
	return true;
}

bool TransitManager::doLogin(CNetPacket *packet) {
	packet->uid = packet->fd;
	CLoginProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("CLoginProtocol decode failed");
		return false;
	}

	if (m_platformMap.find(proto.span_id) == m_platformMap.end()) {
		//error_log("find pf failed by spandId=%d", proto.span_id);
		return false;
	}

	string pf = m_platformMap[proto.span_id];
	OPUserInfo userInfo;
	int ret = 0;
	if (Config::GetValue("is_test") != "yes") {
		ret = OpenPlatform::GetPlatform()->GetUserInfo(userInfo, proto.openId, proto.openKey, pf, "");
	}
	if (ret != 0) {
		error_log("[GetUserInfo fail][ret=%d,openid=%s,openkey=%s]", ret, proto.openId.c_str(), proto.openKey.c_str());
	}
	if (userInfo.Name.empty()) {
		error_log("[GetUserInfo name empty][openid=%s,openkey=%s,name=%s,pic=%s]", proto.openId.c_str(), proto.openKey.c_str(), userInfo.Name.c_str(), userInfo.FigureUrl.c_str());
	}
	uint32_t wb_vip = 0;
	if (Config::GetValue("is_test") != "yes") {
		ret = OpenPlatform::GetPlatform()->GetVipInfo(proto.openId, proto.openKey, pf, "", wb_vip);
		if (0 != ret) {
			error_log("get vip level error openid=%s", proto.openId.c_str());
		}
	}
	String::FixUtf8Len(userInfo.Name, 32);
	CNetPacket sPacket;
	sPacket.uid = packet->uid;
	CBufferWriter writer(sPacket.GetBody());
	writer.AppendByte(PROTOCOL_CMD_TRANSIT);
	writer.AppendByte(PROTOCOL_SUBCMD_TRANSIT_LOGIN);
	writer.AppendString(proto.openId);
	writer.AppendByte(0);
	writer.AppendString(proto.openKey);
	writer.AppendByte(0);
	writer.AppendUInt32(proto.reg_server_id);
	writer.AppendUInt32(proto.cur_server_id);
	writer.AppendString(userInfo.Name);
	writer.AppendByte(0);
	writer.AppendString(userInfo.FigureUrl);
	writer.AppendByte(0);
	if (wb_vip > 0) {
		writer.AppendUInt32(1);
	} else {
		writer.AppendUInt32(0);
	}
	bool gift = getId(proto.openId, 0);
	if (gift) {
		writer.AppendUInt32(1);
	} else {
		writer.AppendUInt32(0);
	}
	writer.AppendUInt32(wb_vip);

	info_log("uid=%u,name=%s,url=%s,wb_vip=%u,gift=%d", packet->uid, userInfo.Name.c_str(), userInfo.FigureUrl.c_str(), wb_vip, gift);

	if (!sendMsgToLogin(&sPacket)) {
		error_log("sendMsg loginPacket failed");
		return false;
	}

	return true;
}

bool TransitManager::busiLogInit() {
	if (0 != CLog::create_inst("coin", Config::GetValue("log_busi").c_str())) {
		return false;
	}
	if (0 != CLog::create_inst("equip", Config::GetValue("log_busi").c_str())) {
		return false;
	}
	if (0 != CLog::create_inst("login", Config::GetValue("log_busi").c_str())) {
		return false;
	}
	if (0 != CLog::create_inst("task", Config::GetValue("log_busi").c_str())) {
		return false;
	}
	if (0 != CLog::create_inst("online", Config::GetValue("log_busi").c_str())) {
		return false;
	}
	if (0 != CLog::create_inst("buy", Config::GetValue("log_busi").c_str())) {
		return false;
	}
	if (0 != CLog::create_inst("token", Config::GetValue("log_busi").c_str())) {
		return false;
	}
	return true;
}

bool TransitManager::sendMsgToLogin(CNetPacket *packet) {
	packet->ptype = PROTOCOL_TYPE_TRANSIT_ANSWER;
	packet->mtime = packet->uid;
	TransitServer::getInstance()->addSendLoginPacket(packet);
	return true;
}

bool TransitManager::sendMsgToTencent(int fd, int ret) {
	string msg;
	switch (ret) {
	case 0:
		msg = "{\"ret\":0,\"msg\":\"OK\"}";
		break;
	case 2:
		msg = "{\"ret\":4,\"msg\":\"请求参数错误:（sig）\"}";
		break;
	default:
		msg = "{\"ret\":4,\"msg\":\"请求参数错误:（payitem）\"}";
		break;
	}

	string sendmsg = "HTTP/1.0 200 OK\r\nContent-type: text/html; charset=UTF-8\r\nContent-Length: ";
	sendmsg += Convert::IntToString(msg.length()) + "\r\nConnection: close\r\n\r\n" + msg;

	CStaticBuffer<MAX_PROTOCOL_BODY_SIZE> body;
	body.Append((byte*) sendmsg.c_str(), sendmsg.length());
	TencentAsyncManager::getInstance()->sendData(fd, &body);
	debug_log("response QQ deliver successed");

	return true;
}
bool TransitManager::getNextPayId(uint32_t &nextId, uint32_t serverId) {
	int ret = 0;
	CDataIdCtrl dbIdCtrl;
	ret = dbIdCtrl.GetId(KEY_PAY_HISTORY_ID_CTRL, nextId, serverId);
	if (ret != 0) {
		error_log("[GetId fail][key=%d]", KEY_PAY_HISTORY_ID_CTRL);
		return false;
	}
	nextId++;
	ret = dbIdCtrl.SetId(KEY_PAY_HISTORY_ID_CTRL, nextId, serverId);
	if (ret != 0) {
		error_log("[SetId fail][key=%d,nextId=%llu]", KEY_PAY_HISTORY_ID_CTRL, nextId);
		return false;
	}
	return true;
}

bool TransitManager::report(const string &msg) {
	return true;
}

bool TransitManager::wanbaGetBalance(const string &opid, const string &opkey, const string &pf, const string &ip, uint32_t pt, int &score) {
	int ret = CLogicQQPay::v3_get_playzone_userinfo(opid, opkey, pf, String::i2s(pt), ip, score);
	if (0 != ret) {
		return false;
	}
	return true;
}

bool TransitManager::wanbaPay(uint32_t uid, uint32_t id, uint32_t cnt, uint32_t pt, const string &opid, const string &opkey, const string &pf, const string &ip, string &oid, uint32_t &cash, uint32_t &cost) {
	int ret = CLogicQQPay::v3_buy_playzone_item(opid, opkey, pf, String::i2s(pt), ip, id, cnt, oid, cash, cost);
	if (0 != ret) {
		return false;
	}
	uint32_t nextPayId = 0;
	if (getNextPayId(nextPayId, Config::GetZoneByUID(uid))) {
		DataPayHistory payHistory;
		payHistory.uid = uid;
		payHistory.pay_id = nextPayId;
		payHistory.channel = pt;
		payHistory.channel_pay_id = oid;
		payHistory.credit = cost;
		payHistory.count = cash;
		payHistory.type = 0;
		payHistory.open_id = opid;
		payHistory.time = Time::GetGlobalTime();
		payHistory.status = 1;
		ret = CDataPayHistory().AddPayHistory(payHistory);
		if (ret) {
			error_log("AddPayHistory error! uid=%u ret=%d", uid, ret);
		}
	} else {
		error_log("get next pay id error uid=%u", uid);
	}
	return true;
}

bool TransitManager::midasGetBalance(const string &openid, const string &openkey, const string &pf, int &score, string &mpid) {
	mpid = OpenPlatform::GetPlatform()->GetConfig("mp_id");
	const string &appid = OpenPlatform::GetPlatform()->GetConfig("wx_appid");
	const string &url = OpenPlatform::GetPlatform()->GetConfig("wx_v3domain");
	const string &appkey = OpenPlatform::GetPlatform()->GetConfig("wx_appkey");
	const string &sandbox = OpenPlatform::GetPlatform()->GetConfig("mp_sandbox");
	const string &mpkey = OpenPlatform::GetPlatform()->GetConfig("mp_secret");

	string api;
	if (sandbox == "1") {
		api = "/cgi-bin/midas/sandbox/getbalance";
	} else {
		api = "/cgi-bin/midas/getbalance";
	}

	map<string, string> params;
	params["openid"] = openid;
	params["appid"] = appid;
	params["offer_id"] = mpid;
	params["ts"] = CTrans::ITOS(Time::GetGlobalTime());
	params["zone_id"] = "1";
	params["pf"] = "android";

	string token;
	if (!CLogicMidasPay::GetToken(url, appid, appkey, pf, token)) {
		error_log("get token error openid=%s, openkey=%s", openid.c_str(), openkey.c_str());
		return false;
	}

	CLogicMidasPay::Sign(params, mpkey, openkey, pf, token, api, "POST");
	Json::Value post;
	for (map<string, string>::const_iterator itr = params.begin(); itr != params.end(); ++itr) {
		if (itr->first == "ts") {
			post[itr->first] = CTrans::STOI(itr->second);
		} else {
			post[itr->first] = itr->second;
		}
	}

	string post_url = "https://" + url + api + "?access_token=" + token;
	string resp;
	if (!Network::HttpPostRequest(resp, post_url, Json::ToString(post))) {
		error_log("post error openid=%s, openkey=%s, post=%s, url=%s", openid.c_str(), openkey.c_str(), Json::ToString(post).c_str(), post_url.c_str());
		return false;
	}

	Json::Value obj;
	Json::Reader reader;
	if (!reader.parse(resp, obj)) {
		error_log("resp error openid=%s, openkey=%s, post=%s, url=%s, resp=%s", openid.c_str(), openkey.c_str(), Json::ToString(post).c_str(), post_url.c_str(), resp.c_str());
		return false;
	}

	int errcode = 0;
	if (!Json::GetInt(obj, "errcode", errcode) || errcode != 0) {
		error_log("resp error openid=%s, openkey=%s, post=%s, url=%s, resp=%s", openid.c_str(), openkey.c_str(), Json::ToString(post).c_str(), post_url.c_str(), resp.c_str());
		if (errcode == CLogicMidasPay::TOKEN_ERR) {
			CLogicMidasPay::ResetToken();
		}
		return false;
	}

	Json::GetInt(obj, "balance", score);

	return true;
}

bool TransitManager::midasPay(uint32_t uid, uint32_t id, const string &openid, const string &openkey, const string &pf, string &oid, uint32_t &cash, uint32_t &cost) {
	int ret = 0;
	const string &appid = OpenPlatform::GetPlatform()->GetConfig("wx_appid");
	const string &url = OpenPlatform::GetPlatform()->GetConfig("wx_v3domain");
	const string &appkey = OpenPlatform::GetPlatform()->GetConfig("wx_appkey");
	const string &sandbox = OpenPlatform::GetPlatform()->GetConfig("mp_sandbox");
	const string &mpid = OpenPlatform::GetPlatform()->GetConfig("mp_id");
	const string &mpkey = OpenPlatform::GetPlatform()->GetConfig("mp_secret");

	string api;
	if (sandbox == "1") {
		api = "/cgi-bin/midas/sandbox/pay";
	} else {
		api = "/cgi-bin/midas/pay";
	}

	QQItemInfo itemInfo;
	ret = CLogicQQPay::GetItemInfo(id, OSPT_MINI, itemInfo);
	if (ret) {
		return false;
	}
	map<string, string> params;
	params["appid"] = appid;
	params["openid"] = openid;
	params["offer_id"] = mpid;
	params["ts"] = CTrans::ITOS(Time::GetGlobalTime());
	params["zone_id"] = "1";
	params["pf"] = "android";
	params["amt"] = CTrans::ITOS(itemInfo.price);
	params["bill_no"] = Crypt::Md5Encode(openid + CTrans::ITOS(Time::GetGlobalTime()) + itemInfo.itemid);

	string token;
	if (!CLogicMidasPay::GetToken(url, appid, appkey, pf, token)) {
		error_log("get token error openid=%s, openkey=%s", openid.c_str(), openkey.c_str());
		return false;
	}

	CLogicMidasPay::Sign(params, mpkey, openkey, pf, token, api, "POST");

	Json::Value post;
	for (map<string, string>::const_iterator itr = params.begin(); itr != params.end(); ++itr) {
		if (itr->first == "ts" || itr->first == "amt") {
			post[itr->first] = CTrans::STOI(itr->second);
		} else {
			post[itr->first] = itr->second;
		}
	}

	string post_url = "https://" + url + api + "?access_token=" + token;
	string resp;
	if (!Network::HttpPostRequest(resp, post_url, Json::ToString(post))) {
		error_log("post error openid=%s, openkey=%s, post=%s, url=%s", openid.c_str(), openkey.c_str(), Json::ToString(post).c_str(), post_url.c_str());
		return false;
	}

	Json::Value obj;
	Json::Reader reader;
	if (!reader.parse(resp, obj)) {
		error_log("resp error openid=%s, openkey=%s, post=%s, url=%s, resp=%s", openid.c_str(), openkey.c_str(), Json::ToString(post).c_str(), post_url.c_str(), resp.c_str());
		return false;
	}

	int errcode = 0;
	if (!Json::GetInt(obj, "errcode", errcode) || errcode != 0) {
		error_log("resp error openid=%s, openkey=%s, post=%s, url=%s, resp=%s", openid.c_str(), openkey.c_str(), Json::ToString(post).c_str(), post_url.c_str(), resp.c_str());
		if (errcode == CLogicMidasPay::TOKEN_ERR) {
			CLogicMidasPay::ResetToken();
		}
		return false;
	}

	string billno;
	Json::GetString(obj, "bill_no", billno);
	cash = itemInfo.cash;
	cost = itemInfo.price;
	uint32_t nextPayId = 0;
	if (getNextPayId(nextPayId, Config::GetZoneByUID(uid))) {
		DataPayHistory payHistory;
		payHistory.uid = uid;
		payHistory.pay_id = nextPayId;
		payHistory.channel = PT_WX_MINI;
		payHistory.channel_pay_id = billno;
		payHistory.credit = cost;
		payHistory.count = cash;
		payHistory.type = 0;
		payHistory.open_id = openid;
		payHistory.time = Time::GetGlobalTime();
		payHistory.status = 1;
		ret = CDataPayHistory().AddPayHistory(payHistory);
		if (ret) {
			error_log("AddPayHistory error! uid=%u ret=%d", uid, ret);
		}
	} else {
		error_log("get next pay id error uid=%u", uid);
	}
	return true;
}

bool TransitManager::doOffline(CNetPacket *packet) {
	COfflineProtocol offlineProtocol;
	if (!offlineProtocol.Decode(&(packet->body))) {
		error_log("offlineProtocol decode failed");
		return false;
	}
	return true;
}

bool TransitManager::doGetBalance(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	string mpid;
	CTransitGetBalanceProtocol proto;
	if (!proto.Decode(&(packet->body))) {
		error_log("decode failed uid=%u", uid);
		return onGetBalance(uid, TRANSIT_RESULT_FAIL, 0, "");
	}
	if (proto.openId.empty() || proto.openKey.empty() || proto.pf.empty()) {
		return onGetBalance(uid, TRANSIT_RESULT_PARAM_ERR, 0, "");
	}
	int32_t score = 0;
	bool ret = false;
	if (proto.pf.find("wanba_ts") != string::npos) {
		ret = wanbaGetBalance(proto.openId, proto.openKey, proto.pf, "", proto.platform, score);
	} else if (proto.pf.find("wxmini") != string::npos) {
		ret = midasGetBalance(proto.openId, proto.openKey, proto.pf, score, mpid);
	}
	if (!ret) {
		error_log("get balance error pf=%s, platform=%u, openid=%s, openkey=%s, uid=%u, srv_id=%u", proto.pf.c_str(), proto.platform, proto.openId.c_str(), proto.openKey.c_str(), proto.uid, proto.server_id);
		return onGetBalance(uid, TRANSIT_RESULT_PLATFORM_ERR, score, mpid);
	}
	onGetBalance(uid, TRANSIT_RESULT_SUCCESS, score, mpid);
	debug_log("uid=%u sid=%u score=%u", proto.uid, proto.server_id, score);
	return true;
}

bool TransitManager::doPay(CNetPacket *packet) {
	bool ret = false;
	uint32_t uid = packet->uid;
	string billon;
	uint32_t cash = 0;
	uint32_t cost = 0;
	CTransitPayProtocol proto;
	if (!proto.Decode(&(packet->body))) {
		error_log("decode failed uid=%u", uid);
		return onPay(uid, TRANSIT_RESULT_FAIL, 0, billon, cash, cost);
	}
	if (proto.itemId == 0 || proto.openId.empty() || proto.openKey.empty() || proto.pf.empty()) {
		error_log("protocol empty");
		return onPay(uid, TRANSIT_RESULT_PARAM_ERR, 0, billon, cash, cost);
	}
	if (proto.pf.find("wanba_ts") != string::npos) {
		ret = wanbaPay(uid, proto.itemId, proto.count, proto.platform, proto.openId, proto.openKey, proto.pf, "", billon, cash, cost);
	} else if (proto.pf.find("wxmini") != string::npos) {
		ret = midasPay(uid, proto.itemId, proto.openId, proto.openKey, proto.pf, billon, cash, cost);
	}
	if (!ret) {
		error_log("buy item error openid=%s uid=%u", proto.openId.c_str(), proto.uid);
		return onPay(uid, TRANSIT_RESULT_PLATFORM_ERR, 0, billon, cash, cost);
	}
	onPay(uid, TRANSIT_RESULT_SUCCESS, proto.itemId, billon, cash, cost);

	debug_log("uid=%u,openid=%s,id=%u", uid, proto.openId.c_str(), proto.itemId);

	BUSI_BUY("%u|%u|%u|%u|%u|%u|%d|%d|%s|%d|%s", proto.server_id, proto.uid, cost * 10, proto.itemId, proto.count, cash, 0, 0, "buy", 0, billon.c_str());

	return true;
}

bool TransitManager::doGiftExchange(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CTransitGiftExhangeProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", uid);
		return onGiftExchange(uid, R_ERROR, 0);
	}

	if (proto.giftid > 6) {
		if (getId(proto.openid, proto.giftid)) {
			return onGiftExchange(uid, R_ERR_REFUSE, proto.giftid);
		}
		setId(proto.openid, proto.giftid);
		debug_log("uid=%u,openid=%s,giftid=%d", uid, proto.openid.c_str(), proto.giftid);
		return onGiftExchange(uid, R_SUCCESS, proto.giftid);
	}

	int code = 0;
	int ret = OpenPlatform::GetPlatform()->GiftExchange(proto.openid, proto.openkey, proto.pf, "", CTrans::ITOS(proto.giftid), code);
	if (0 != ret) {
		error_log("exchange error uid=%u openid=%s giftid=%d", uid, proto.openid.c_str(), proto.giftid);
		return onGiftExchange(uid, R_ERROR, 0);
	}
	if (getId(proto.openid, 0)) {
		error_log("reward flag error openid=%s", proto.openid.c_str());
		code = R_ERR_REFUSE;
	}
	onGiftExchange(uid, code, proto.giftid);
	if (code == 0) {
		setId(proto.openid, 0);
	}
	debug_log("uid=%u,openid=%s,giftid=%d,code=%d", uid, proto.openid.c_str(), proto.giftid, code);
	return true;
}

bool TransitManager::doQQMiniCallBack(int fd, string &body, string &root) {
	debug_log("body=%s", body.c_str());

	const string &url = OpenPlatform::GetPlatform()->GetConfig("qq_url");
	const string &appkey = OpenPlatform::GetPlatform()->GetConfig("qq_appkey");

	Json::Value obj;
	Json::Reader reader;
	if (!reader.parse(body, obj)) {
		error_log("body parse error");
		sendQQMini(fd, false);
		return false;
	}
	//解析请求参数
	string openid = obj["openid"].asString();
	string bill_no = obj["bill_no"].asString();
	uint32_t amt = obj["amt"].asUInt();
	uint32_t ts = obj["ts"].asUInt();
	string app_remark = obj["app_remark"].asString();
	string sig = obj["sig"].asString();
	//参数表
	map<string, string> params;
	params["openid"] = openid;
	params["bill_no"] = bill_no;
	params["amt"] = CTrans::ITOS(amt);
	params["ts"] = CTrans::ITOS(ts);
	params["app_remark"] = app_remark;
	//生成检验签名
	CLogicMidasPay::QQCallBackSign(params, appkey, root, "POST");
	//校验数据包签名
	if (sig != params["checkSig"]) {
		error_log("sign error, %s, %s, %s", url.c_str(), sig.c_str(), params["checkSig"].c_str());
		sendQQMini(fd, false);
		return false;
	}
	//解析备注信息
	vector<string> remark_data;
	String::Split(app_remark, '#', remark_data);
	uint32_t uid = CTrans::STOI(remark_data[0]);
	uint32_t goodId = CTrans::STOI(remark_data[1]);
	//校验uid
	if (!IS_VALID_PLAYER_UID(uid)) {
		error_log("get uid error, openid=%s", openid.c_str());
		sendQQMini(fd, false);
		return false;
	}
	//校验物品ID
	QQItemInfo itemInfo;
	int ret = CLogicQQPay::GetItemInfo(goodId, OSPT_MINI, itemInfo);
	if (ret) {
		error_log("getItemInfo error");
		sendQQMini(fd, false);
		return false;
	}
	//支付记录
	DataPayHistory payHis;
	CDataPayHistory dbPayHis;
	ret = dbPayHis.GetPayHistory(uid, OpenPlatform::GetType(), bill_no, payHis);
	if (0 == ret) {
		error_log("PayHistory already exist");
		sendQQMini(fd, false);
		return false;
	}

	uint32_t nextPayId = 0;
	if (getNextPayId(nextPayId, Config::GetZoneByUID(uid))) {
		DataPayHistory payhis;
		payhis.pay_id = nextPayId;
		payhis.channel = PT_QQ_MINI;
		payhis.channel_pay_id = bill_no;
		payhis.count = itemInfo.cash;
		payhis.credit = itemInfo.price;
		payhis.status = 1;
		payhis.type = 0;
		payhis.uid = uid;
		payhis.open_id = openid;
		payhis.time = Time::GetGlobalTime();
		ret = CDataPayHistory().AddPayHistory(payhis);
		if (ret != 0) {
			error_log("[AddPayHistory fail][ret=%d,openid=%s,order_id=%s,product_id=%u,product_price=%d]",
					ret, openid.c_str(), bill_no.c_str(), goodId, itemInfo.price);
		}
	} else {
		error_log("get next pay id error uid=%u", uid);
	}
	onPay(uid, TRANSIT_RESULT_SUCCESS, goodId, bill_no, itemInfo.cash, itemInfo.price);
	sendQQMini(fd, true);
	BUSI_BUY("%u|%u|%u|%u|%u|%u|%d|%d|%s|%d|%s", Config::GetZoneByUID(uid), uid, itemInfo.price * 10, goodId, 1, itemInfo.cash, 0, 0, "buy", 0, bill_no.c_str());
	return true;
}

bool TransitManager::doPreOrder(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CTransitPerOrderProtocol proto;
	if(!proto.Decode(packet->GetBody())) {
		error_log("decode faild uid=%u", uid);
		return onPerOrder(uid, TRANSIT_RESULT_FAIL, "", 0);
	}
	if(proto.openId.empty() || proto.openKey.empty() || proto.pf.empty()) {
		return onPerOrder(uid, TRANSIT_RESULT_PARAM_ERR, "", 0);
	}
	//扣除游戏币数量
	int32_t coin_cnt = 0;
	//订单号
	string prepayId;
	bool ret = false;
	if(proto.pf.find("QQmini") != string::npos) {
		ret = QQPrePay(uid, proto.openId, proto.openKey, proto.pf, prepayId, proto.goodId, coin_cnt);
	}

	if(!ret) {
		error_log("do PerOrder error pf=%s, openid=%s, openkey=%s, uid=%u, srv_id=%u", proto.pf.c_str(), proto.openId.c_str(),
				proto.openKey.c_str(), proto.uid, proto.server_id);
		return onPerOrder(proto.uid, TRANSIT_RESULT_FAIL, "", 0);
	}

	onPerOrder(proto.uid, TRANSIT_RESULT_SUCCESS, prepayId, coin_cnt);
	debug_log("uid=%u, sid=%u, coin=%u", proto.uid, proto.server_id, coin_cnt);

	return true;
}


bool TransitManager::onGetBalance(uint32_t uid, byte ret, int score, const string &mpid) {
	CNetPacket sp;
	sp.uid = uid;
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_TRANSIT);
	writer.AppendByte(PROTOCOL_SUBCMD_TRANSIT_GET_BALANCE);
	writer.AppendUInt32(uid);
	writer.AppendByte(ret);
	writer.AppendUInt32(score);
	writer.AppendString(mpid);
	if (!sendMsgToLogin(&sp)) {
		error_log("send buyGoods msg failed");
		return false;
	}
	return true;
}

bool TransitManager::onPerOrder(uint32_t uid, byte ret, const string &perpayid, uint32_t amt) {
	CNetPacket sp;
	sp.uid = uid;
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_TRANSIT);
	writer.AppendByte(PROTOCOL_SUBCMD_TRANSIT_PER_ORDER);
	writer.AppendUInt32(uid);
	writer.AppendByte(ret);
	writer.AppendString(perpayid);
	writer.AppendByte(0);
	writer.AppendUInt32(amt);
	if (!sendMsgToLogin(&sp)) {
		error_log("send PreOrder msg failed");
		return false;
	}
	return true;
}

bool TransitManager::onPay(uint32_t uid, byte ret, uint32_t itemid, const string &oid, uint32_t cash, uint32_t cost) {
	CNetPacket sp;
	sp.uid = uid;
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_TRANSIT);
	writer.AppendByte(PROTOCOL_SUBCMD_TRANSIT_PAY);
	writer.AppendByte(ret);
	writer.AppendUInt32(uid);
	writer.AppendUInt32(itemid);
	writer.AppendString(oid);
	writer.AppendByte(0);
	writer.AppendUInt32(cash);
	writer.AppendUInt32(cost);
	if (!sendMsgToLogin(&sp)) {
		error_log("send buyGoods msg failed");
		return false;
	}
	return true;
}

bool TransitManager::onGiftExchange(uint32_t uid, int ret, uint32_t giftid) {
	CNetPacket sp;
	sp.uid = uid;
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_TRANSIT);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_TRANSIT_GIFT_EXHANGE);
	PACKET_ENCODE(Int32, ret);
	PACKET_ENCODE(UInt32, giftid);
	if (!sendMsgToLogin(&sp)) {
		error_log("send gift exhange msg failed");
		return false;
	}
	return true;
}

bool TransitManager::doGetFriend(CNetPacket *packet) {
	packet->uid = packet->fd;
	CLoginProtocol proto;
	if (!proto.Decode(&(packet->body))) {
		error_log("CLoginProtocol decode failed");
		return false;
	}
	if (m_platformMap.find(proto.span_id) == m_platformMap.end()) {
		//error_log("find pf failed by spandId=%d", proto.span_id);
		return false;
	}
	string pf = m_platformMap[proto.span_id];
	OPFriendList friendList;
	int ret = 0;
	if (Config::GetValue("is_test") != "yes") {
		ret = OpenPlatform::GetPlatform()->GetAppFriendList(friendList, proto.openId, proto.openKey, pf, "");
		if (0 != ret) {
			error_log("GetFriendList error! ret=%d", ret);
			friendList.clear();
		}
	}
	info_log("openid=%s friend_num=%u", proto.openId.c_str(), friendList.size());
	CNetPacket sp;
	sp.uid = packet->uid;
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_TRANSIT);
	writer.AppendByte(PROTOCOL_SUBCMD_TRANSIT_FRIEND_INFO);
	writer.AppendUInt32(friendList.size());
	for (size_t i = 0; i < friendList.size(); ++i) {
		writer.AppendString(friendList[i]);
	}
	if (!sendMsgToLogin(&sp)) {
		error_log("sendMsg loginPacket failed");
		return false;
	}
	return true;
}

bool TransitManager::doReport(CNetPacket *packet) {
	CTransitReportProtocol protocol;
	if (!protocol.Decode(&(packet->body))) {
		error_log("Decode error");
		return false;
	}
	report(protocol.msg);
	return true;
}

bool TransitManager::QQPrePay(uint32_t uid, const string &openid, const string &openkey, const string &pf, string &prepayId, int goodId, int &amt) {
	const string &appid = OpenPlatform::GetPlatform()->GetConfig("qq_appid");
	const string &url = OpenPlatform::GetPlatform()->GetConfig("qq_url");
	const string &appkey = OpenPlatform::GetPlatform()->GetConfig("qq_appkey");
	const string &qq_pf =  OpenPlatform::GetPlatform()->GetConfig("qq_pf");

	string api = "/api/json/openApiPay/GamePrePay";
	//获取物品信息
	QQItemInfo itemInfo;
	uint32_t ret = CLogicQQPay::GetItemInfo(goodId, OSPT_MINI, itemInfo);
	if (ret)
	{
		error_log("getItemInfo error");
		return false;
	}
	amt = itemInfo.price;
	//请求参数表
	map<string, string> params;
	params["openid"] = openid;
	params["appid"] = appid;
	params["ts"] = CTrans::ITOS(Time::GetGlobalTime());
	params["zone_id"] = "1";
	params["pf"] = qq_pf;
	params["amt"] = CTrans::ITOS(itemInfo.price);
	params["bill_no"] = Crypt::Md5Encode(openid + CTrans::ITOS(Time::GetGlobalTime()) + itemInfo.itemid);
	params["goodid"] = CTrans::ITOS(goodId);
	params["good_num"] = CTrans::ITOS(1);
	params["app_remark"] = CTrans::ITOS(uid) + "#" + CTrans::ITOS(goodId);
	//获取调用凭证
	string token;
	if (!CLogicMidasPay::GetToken(url, appid, appkey, pf, token)) {
		error_log("get token error openid=%s, openkey=%s", openid.c_str(), openkey.c_str());
		return false;
	}
	//生成签名
	CLogicMidasPay::Sign(params, appkey, openkey, pf, token, api, "POST");
	//生成POST数据
	Json::Value post;
	for (map<string, string>::const_iterator itr = params.begin(); itr != params.end(); ++itr) {
		if(itr->first == "access_token" || itr->first == "mp_sig") {
			continue;
		} else if (itr->first == "ts" || itr->first == "amt" || itr->first == "good_num") {
			post[itr->first] = CTrans::STOI(itr->second);
		} else {
			post[itr->first] = itr->second;
		}
	}

	map<string, string> headers;
	headers["Content-type"] = "application/json";

	string post_url = "https://" + url + api + "?access_token=" + token;
	string resp;
	if (!Network::HttpPostRequest(resp, post_url, Json::ToString(post), headers)) {
		error_log("post error openid=%s, openkey=%s, post=%s, url=%s", openid.c_str(), openkey.c_str(), Json::ToString(post).c_str(), post_url.c_str());
		return false;
	}

	Json::Value obj;
	Json::Reader reader;
	if (!reader.parse(resp, obj)) {
		error_log("resp error openid=%s, openkey=%s, post=%s, url=%s, resp=%s", openid.c_str(), openkey.c_str(), Json::ToString(post).c_str(), post_url.c_str(), resp.c_str());
		return false;
	}

	int errcode = 0;
	if (!Json::GetInt(obj, "errcode", errcode) || errcode != 0) {
		error_log("resp error openid=%s, openkey=%s, post=%s, url=%s, resp=%s", openid.c_str(), openkey.c_str(), Json::ToString(post).c_str(), post_url.c_str(), resp.c_str());
		if (errcode == CLogicMidasPay::TOKEN_ERR) {
			CLogicMidasPay::ResetToken();
		}
		return false;
	}

	Json::GetString(obj, "prepayId", prepayId);
	return true;
}
