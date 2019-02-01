/*
 * DataVipRebates.h
 *
 *  Created on: 2014年7月15日
 *      Author: Administrator
 */

#ifndef DATAVIPREBATES_H_
#define DATAVIPREBATES_H_
#include "Kernel.h"
#define VIP_LEVEL_COUNT 5
#define VIP_MAX_COUNT 1000

struct VipUser{
	uint32_t uid;
	char name[32];
	VipUser(){
		uid = 0;
		memset(name, 0, sizeof(name));
	}
};

struct VipInc{
	uint32_t viplvl;
	VipUser users[VIP_MAX_COUNT];
	VipInc(){
		viplvl=0;
		memset(users, 0, sizeof(users));
	}
	bool append(const VipUser &user){
		for(size_t i = 0; i < VIP_MAX_COUNT; ++i) {
			if(users[i].uid == 0) {
				users[i].uid = user.uid;
				memcpy(users[i].name, user.name, sizeof(user.name));
				return true;
			}
			if(users[i].uid == user.uid) {
				return true;
			}
		}
		return false;
	}

	vector<VipUser> getVipUsers() {
		vector<VipUser> vecRtn;
		for(size_t i = 0; i < VIP_MAX_COUNT; ++i) {
			if(users[i].uid == 0) {
				continue;
			}
			vecRtn.push_back(users[i]);
		}
		return vecRtn;
	}
};

struct VipRebatesData{
	uint32_t updateTime;
	VipInc vips[VIP_LEVEL_COUNT];
	VipRebatesData(){
		updateTime=0;
		memset(vips, 0, sizeof(vips));
		for(size_t i = 0; i < VIP_LEVEL_COUNT; ++i) {
			vips[i].viplvl = VIP_LEVEL_COUNT + i + 1;	// 从6级开始
		}
	}
};

class CDataVipRebates {

public:
	CDataVipRebates();
	int Init(const string &path, semdat sem=sem_viprebates);
	int getVips(uint32_t viplvl, vector<VipUser> &rlt);
	int setVip(uint32_t uid, const string &name, uint32_t fromLvl, uint32_t toLvl);
	uint32_t getTime();
	int clear();

protected:
	CShareMemory m_sh;
	bool m_init;
};

#endif /* DATAVIPREBATES_H_ */
