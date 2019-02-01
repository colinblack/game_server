/*
 * BattleConnect.h
 *
 *  Created on: 2018年4月10日
 *      Author: Ralf
 */

#ifndef APP_KERNEL_BATTLECONNECT_H_
#define APP_KERNEL_BATTLECONNECT_H_



#include "Common.h"
#include "FirePacket.h"
#include "ConfigManager.h"

class BattleConnect
{
public:
	static void AddSend(unsigned server, CFirePacket* packet);
	//static int Receive(unsigned server, CFirePacket* packet);
	static bool InitThread();
	static void DestoryThread();

	BattleConnect(unsigned server):serverid(server){}
	~BattleConnect(){}
private:
	static int Send(unsigned server, CFirePacket* packet);
	int Connect();
	int Send(CFirePacket* packet);
	//int Receive(CFirePacket* packet);
	bool IsClosed(){return socket.IsClosed();}

	CSocket socket;
	unsigned serverid;

	static map<unsigned, BattleConnect*> m_map;

	static void* _run(void* args);
	static CBaseMutex   m_mutex;
	static pthread_t m_thread;
	static pthread_cond_t m_cond;
	static list<CFirePacket*> m_send;
};




#endif /* APP_KERNEL_BATTLECONNECT_H_ */
