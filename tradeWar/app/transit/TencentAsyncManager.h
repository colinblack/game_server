/*
 * TencentAsyncManager.h
 *
 *  Created on: 2016-3-18
 *      Author: Administrator
 */

#ifndef TENCENTASYNCMANAGER_H_
#define TENCENTASYNCMANAGER_H_

#include "Kernel.h"
#include "TencentAsync.h"

using namespace std;

class TencentAsyncManager{
public:
	static TencentAsyncManager* getInstance(){
		static TencentAsyncManager cm;
		return &cm;
	}
	~TencentAsyncManager(){};
private:
	TencentAsyncManager(){}
public:
	bool addClient(TencentAsync* pClient);
	bool removeClient(TencentAsync* pClient);
	bool sendData(uint32_t fd, IBuffer* pBuff);
private:
	map<uint32_t,TencentAsync*> m_clients;//fd-client
};


#endif /* TENCENTASYNCMANAGER_H_ */
