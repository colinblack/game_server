#include "LogicEliteMilitaryManager.h"

int LogicEliteMilitaryManager::DestroyNPC()
{
	map<unsigned, uint8_t>::iterator uiter;

	for(uiter = m_cityNPC.begin(); uiter != m_cityNPC.end(); ++uiter)
	{
		unsigned cid = uiter->first;

		WMI->DelActNPC(e_nb_npc, cid);
	}

	m_cityNPC.clear();

	return 0;
}

int LogicEliteMilitaryManager::RefreshEliteNPC(uint8_t kingdom, unsigned cid)
{
	//根据开服天数，从相关库中随机抽取一类NPC
	int random_type = Math::GetRandomInt(4) + 1;  //类型1-4，分别对应NPC的四种类型
	unsigned diff = LogicManager::Instance()->GetOpenDays();

	const WorldEliteConfig::TypeNPC & typenpc = EliteNPCConfigWrap().GetTypeNPC(diff, random_type);

	//根据配置，创建npc
	for(int i = 0; i < typenpc.npcs_size(); ++i)
	{
		WMI->CreateActNPC(e_nb_npc, typenpc.npcs(i).count(), cid, kingdom, typenpc.npcs(i).npcid());
	}

	m_cityNPC[cid] = typenpc.type();

	return 0;
}

int LogicEliteMilitaryManager::FullMessage(User::EliteNPCInfoAll * msg)
{
	map<unsigned, uint8_t>::iterator uiter;

	for(uiter = m_cityNPC.begin(); uiter !=  m_cityNPC.end(); ++uiter)
	{
		User::EliteNPCInfo * npcmsg = msg->add_npc();

		npcmsg->set_cid(uiter->first);
		npcmsg->set_type(uiter->second);
	}

	return 0;
}

int LogicEliteMilitaryManager::SendRefreshNPCMsg()
{
	if (0 == m_cityNPC.size())
	{
		return 0;
	}

	User::EliteNPCPushReq * pushmsg = new User::EliteNPCPushReq;
	map<unsigned, uint8_t>::iterator uiter;

	//组装
	for(uiter = m_cityNPC.begin(); uiter != m_cityNPC.end(); ++uiter)
	{
		User::EliteNPCInfo * npcmsg = pushmsg->add_npcs();

		npcmsg->set_cid(uiter->first);
		npcmsg->set_type(uiter->second);
	}

	//广播发送
	LMI->broadcastMsg(pushmsg);

	return 0;
}
