/*
 * RuneManager.h
 *
 *  Created on: 2019年6月27日
 *      Author: Administrator
 */
#ifndef RUNE_MANAGER_H_
#define RUNE_MANAGER_H_
#include "BattleBaseInc.h"




class RuneManager: public CSingleton<RuneManager> {
private:
	friend class CSingleton<RuneManager>;
	RuneManager();
	~RuneManager();
public:
	bool CalcProperty(const UserCache &cache, byte rid, PropertySets &props);
public:
	int Process(uint32_t uid, rune::CSMagicOpenHole *req);
	int Process(uint32_t uid, rune::CSMagicLearn *req);
	int Process(uint32_t uid, rune::CSMagicUpgrade *req);
	int Process(uint32_t uid, rune::CSMagicDecomPose *req);
	bool addExt(string &str, uint32_t micl);
private:
	bool addExt(string &str, uint32_t micl, uint32_t micp);
	uint32_t getLevel(const string &str);
	uint32_t getPos(string &str);
	bool upgradeExt(string &str);
public:
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SMagicInfo *resp);

};

#endif /* RUNE_MANAGER_H_ */
