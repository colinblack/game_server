#ifndef _WX_BATTLE_MANAGER_H_
#define _WX_BATTLE_MANAGER_H_

#include <map>
#include "battle_async.h"
#include "Kernel.h"

using namespace std;

class BattleManager {
public:
	static BattleManager* getInstance() {
		static BattleManager bm;
		return &bm;
	}
	~BattleManager() {
	}
private:
	BattleManager() {
		m_pollThread = NULL;
	}
public:
	bool init();
	void setPollThread(CPollThread* pThread) {
		m_pollThread = pThread;
	}
	bool sendData(uint32_t serverId, const string& data);
	bool clientClose(uint32_t serverId, uint32_t fd, uint32_t time, uint32_t microTime, uint32_t ip);
private:
	CBattleAsync* connectBattle(uint32_t serverId);
private:
	map<uint32_t, CBattleAsync*> m_battles;
	CPollThread* m_pollThread;
};

#endif
