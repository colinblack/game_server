/*
 * ReinCarnManager.h
 *
 *  Created on: 2019年6月27日
 *      Author: Administrator
 */
#ifndef REINCARN_MANAGER_H_
#define REINCARN_MANAGER_H_
#include "BattleBaseInc.h"

#define NORAML_DAN_ITEMID	210240001
#define SUPER_DAN_ITEMID	210240002

class ReinCarnManager: public CSingleton<ReinCarnManager> {
private:
	friend class CSingleton<ReinCarnManager>;
	ReinCarnManager();
	~ReinCarnManager();
public:
	bool CalcProperty(const UserCache &cache, byte rid, PropertySets &props);

public:
	bool onAddExp(uint32_t uid,uint32_t num);
	int Process(uint32_t uid, reincarn::CSRingActive *req);
	int Process(uint32_t uid, reincarn::CSReinCarn *req);
	int Process(uint32_t uid, reincarn::CSReinCarnGetExpByItems *req);
	int Process(uint32_t uid, reincarn::CSReinCarnGetExpByLevel *req);

private:
	void save(uint32_t uid);
public:
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SInt *resp);
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SReincarnInfo *resp);
};

#endif /* REINCARN_MANAGER_H_ */
