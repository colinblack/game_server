/*
 * TransitManager.h
 *
 *  Created on: 2016-3-15
 *      Author: Administrator
 */

#ifndef TRANSITMANAGER_H_
#define TRANSITMANAGER_H_

#include "Kernel.h"
#include "NetPacket.h"
#include "Common.h"
#include "ProtocolDefine.h"
#include "OpenPlatform.h"
#include "TransitManager.h"
#include "ProtocolTransit.h"
#include "LogicQQPay.h"
#include "ProtocolInc.h"

struct TencentPacket {
	int netfd;
	string msg;
};

enum TransitResultCode {
	TRANSIT_RESULT_SUCCESS = 0,
	TRANSIT_RESULT_FAIL = 1,
	TRANSIT_RESULT_PARAM_ERR = 2,
	TRANSIT_RESULT_PLATFORM_ERR = 3
};

enum HTTP_METHOD {
	HTTP_POST = 1,
	HTTP_GET = 2
};

class TransitManager {
private:
	TransitManager();
	~TransitManager();
public:
	static TransitManager* getInstance() {
		static TransitManager _ins;
		return &_ins;
	}
	bool HttpBody(string &msg, uint32_t &method, string &route, string &body);
	bool init();
	bool busiLogInit();
	bool initIds();
	bool saveIds();
	bool getId(const string &openid, uint32_t gift);
	bool setId(const string &openid, uint32_t gift);
	bool doLoginPacket(CNetPacket *packet);
	bool doTencentPacket(TencentPacket* packet);
	bool doLogin(CNetPacket *packet);
	bool doOffline(CNetPacket *packet);
	bool doGetFriend(CNetPacket *packet);
	bool doReport(CNetPacket *packet);
	bool doGetBalance(CNetPacket *packet);
	bool doPay(CNetPacket *packet);
	bool doGiftExchange(CNetPacket *packet);
	bool doQQMiniCallBack(int fd, string &body, string &root);
	bool doPreOrder(CNetPacket *packet);
	bool onGetBalance(uint32_t uid, byte ret, int score, const string &mpid);
	bool onPerOrder(uint32_t uid, byte ret, const string &perpayid, uint32_t amt);
	bool onPay(uint32_t uid, byte ret, uint32_t itemid, const string &oid, uint32_t cash, uint32_t cost);
	bool onGiftExchange(uint32_t uid, int ret, uint32_t giftid);
	bool sendMsgToTencent(int fd, int ret);
	bool getNextPayId(uint32_t &nextId, uint32_t serverId);
	bool sendMsgToLogin(CNetPacket *packet);
	bool report(const string &msg);
	bool wanbaGetBalance(const string &opid, const string &opkey, const string &pf, const string &ip, uint32_t pt, int &score);
	bool wanbaPay(uint32_t uid, uint32_t id, uint32_t cnt, uint32_t pt, const string &opid, const string &opkey, const string &pf, const string &ip, string &oid, uint32_t &cash, uint32_t &cost);
	bool midasGetBalance(const string &openid, const string &openkey, const string &pf, int &score, string &mid);
	bool midasPay(uint32_t uid, uint32_t id, const string &openid, const string &openkey, const string &pf,string &oid, uint32_t &cash, uint32_t &cost);
	bool QQPrePay(uint32_t uid, const string &openid, const string &openkey, const string &pf, string &prepayId, int goodId, int &amt);
private:
	//c6接入, 返回SDK服务器处理结果
	bool sendSDKServer(int fd, bool isSuccess);
	bool sendQQMini(int fd, bool isSuccess);
private:
	uint32_t m_ts;
	map<string, set<uint32_t> > m_ids;
	ThreadMutex m_idsMutex;
};

#endif /* TRANSITMANAGER_H_ */
