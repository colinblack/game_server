/*
 * OtherServerManager.h
 *
 *  Created on: 2019年3月6日
 *      Author: Administrator
 */

#ifndef OTHER_SERVER_MANAGER_H_
#define OTHER_SERVER_MANAGER_H_

#include "Kernel.h"

class OtherServerManager {
public:
	~OtherServerManager();
	static OtherServerManager* getInstance() {
		static OtherServerManager _ins;
		return &_ins;
	}
	bool doPacket(CNetPacket *p);
	bool sendUserInteractReq(uint32_t myuid, uint32_t othuid, uint32_t lv, uint32_t type, const string &name, const string &pic);
	bool sendUserInfoReq(uint32_t myuid, uint32_t othuid);
protected:
	OtherServerManager();
private:
	bool doUserInteractReq(CNetPacket *p);
	bool doUserInteractResp(CNetPacket *p);
	bool doUserInfoReq(CNetPacket *p);
	bool doUserInfoResp(CNetPacket *p);
	bool onUserInteractResp(uint32_t uid, byte ret, int16_t cnt);
};

#endif /* OTHER_SERVER_MANAGER_H_ */
