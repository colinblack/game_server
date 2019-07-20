#ifndef _LOGIC_MANAGER_H_
#define _LOGIC_MANAGER_H_

#include "BattleBaseInc.h"
#include "Dispatcher.h"

struct OfflineItem {
	uint32_t requestTime;
	CFirePacket reqPacket;
};

class LogicManager: public CSingleton<LogicManager> {
private:
	friend class CSingleton<LogicManager>;
	LogicManager();
public:
	bool Init();
	bool InitLocalData();
	bool SaveLocalData();
	void onExit();
	void Process(CFirePacket* packet);
	bool SendMsg(uint32_t uid, uint32_t cmd, const Msg *msg);
	void OfflineProcess(CFirePacket* packet, const string &reason);
	void ClientProcess(CFirePacket* packet);
	bool ForceKick(uint32_t uid, uint32_t rid, const string &reason);
	bool BattleKick(uint32_t fd, uint32_t ts, uint32_t mts);
	void SetErrMsg(const string &msg);
	void SetReply(Msg *reply);
	uint32_t GetUid();
	bool GetSession(uint32_t uid, int &verifycode, int &relogincode);
	bool SetSession(uint32_t uid, int &verifycode, int &relogincode);
	void RegProto();
	void RegSync();
	bool ActorLogin(uint32_t uid);
	bool AfterLogin(uint32_t uid);
	void AddSync(uint32_t cmd);
	void DoReply(uint32_t cb, uint32_t err);
	void DoSync();

public:
	int Process(uint32_t uid, igameapp::SLoginGame *req);
	int Process(uint32_t uid, logins::SLoginPing *req, logins::SLoginPong *resp);
	int Process(uint32_t uid, logins::SQueryGameData *req);

public:
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SServerInfo *resp);

private:
	bool BusiLogInit();
	void TimerProcess(CFirePacket* packet);
	void OnSecondTimer();
	void PreOffline(CFirePacket* packet);

public:
	static uint32_t GlobalTime;
	static uint32_t GlobalMilliTime;
	static uint32_t ServerId;
	static uint32_t ProxyId;
	static uint32_t SecOpenTime;
	static bool IsClosed;
	static bool IsPreClosed;
	static uint64_t StartMilliTime;

private:
	int32_t channel_id_;
	uint32_t last_loop_time_;
	uint32_t curr_fd_;
	uint32_t curr_ts_;
	uint32_t curr_mts_;
	string err_msg_;
	MsgDispatcher dispatcher_;
	MsgSync synchronizer_;
	Msg* reply_;
	list<OfflineItem> leave_list_;
	list<uint32_t> sync_cmds_;
};

#endif
