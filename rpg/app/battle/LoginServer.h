/*
 * LoginServer.h
 *
 *  Created on: 2019年6月29日
 *      Author: Administrator
 */

#ifndef LOGIN_SERVER_H_
#define LOGIN_SERVER_H_

#include "Kernel.h"
#include "Listener.h"

class LoginServer: public CPollThread, public CSingleton<LoginServer> {
private:
	friend class CSingleton<LoginServer>;
	LoginServer();
	~LoginServer();
public:
	bool Init();
	virtual void onIdle();
	virtual void onExit();
};

#endif /* LOGIN_SERVER_H_ */
