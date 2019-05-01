#ifndef LOGIC_ELITE_MILITARY_MANAGER_H_
#define LOGIC_ELITE_MILITARY_MANAGER_H_

#include "ServerInc.h"

class LogicEliteMilitaryManager : public BattleSingleton, public CSingleton<LogicEliteMilitaryManager>
{
private:
	friend class CSingleton<LogicEliteMilitaryManager>;
	LogicEliteMilitaryManager(){};
	virtual ~LogicEliteMilitaryManager(){}
public:
	virtual void CallDestroy() {Destroy();}

	//销毁NPC
	int DestroyNPC();

	/*desc:刷新精英部队
	 * param:kingdom-npc所属国家. cid-城id
	 */
	int RefreshEliteNPC(uint8_t kingdom, unsigned cid);

	//登录时，发送给前端
	int FullMessage(User::EliteNPCInfoAll * msg);

	//发送推送给前端
	int SendRefreshNPCMsg();
private:
	map<unsigned, uint8_t> m_cityNPC;
};


#endif /* LOGIC_ELITE_MILITARY_MANAGER_H_ */
