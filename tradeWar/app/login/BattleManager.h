#ifndef _BATTLE_MANAGER_H_
#define _BATTLE_MANAGER_H_

#include "Kernel.h"
#include "Player.h"

class BattleManager {
public:
	static BattleManager * getInstance() {
		static BattleManager bm;
		return &bm;
	}

	~BattleManager();
	bool doAccessPacket(CNetPacket * packet);
	bool doBattlePacket(CNetPacket * packet);
	bool doBattleSpySingle(CNetPacket* packet);
	bool doBattleHome(CNetPacket* packet);
	bool packArchive(uint32_t uid, IBuffer* buff, Player* player);

protected:
	bool sendBattleError(uint32_t uid, byte errorcode);
	bool sendPlayerArchive(uint32_t recvUid, uint32_t targetUid);
	bool packPlayerInfo(uint32_t uid, IBuffer* buff, Player* player);

private:
	BattleManager();
};

#endif /* _BATTLE_MANAGER_H_ */
