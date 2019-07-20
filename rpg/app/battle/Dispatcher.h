/*
 * Dispatcher.h
 *
 *  Created on: 2019年6月22日
 *      Author: Administrator
 */

#ifndef _DISPATCHER_H_
#define _DISPATCHER_H_

#include "Kernel.h"
#include "DataInc.h"

typedef int (*DispatchFun)(IBuffer *body);

class MsgDispatcher {
public:
	MsgDispatcher() {
	}
	int onMessage(uint32_t cmd, IBuffer *body) const {
		CallbackMap::const_iterator it = callbacks_.find(cmd);
		if (it != callbacks_.end()) {
			DispatchFun fun = it->second;
			return fun(body);
		} else {
			error_log("cmd not exists %u", cmd);
			return 0;
		}
	}
	void reg(uint32_t cmd, const DispatchFun &callback) {
		callbacks_[cmd] = callback;
	}
	typedef std::map<uint32_t, DispatchFun> CallbackMap;
	CallbackMap callbacks_;
};

typedef int (*SyncFun)(const UserCache &cache, uint32_t cmd);
class MsgSync {
public:
	int onSync(const UserCache &cache, uint32_t cmd) {
		SyncMap::iterator itr = syncs_.find(cmd);
		if (itr != syncs_.end()) {
			return itr->second(cache, cmd);
		} else {
			return R_ERR_NO_DATA;
		}
	}
	void reg(uint32_t cmd, const SyncFun &fun) {
		syncs_[cmd] = fun;
	}
	typedef std::map<uint32_t, SyncFun> SyncMap;
	SyncMap syncs_;
};

#endif /* APP_BATTLE_DISPATCHER_H_ */
