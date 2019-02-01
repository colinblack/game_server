/*
 * LogicUserGradeManager.h
 *
 *  Created on: 2018年8月8日
 *      Author: colin
 */

#ifndef APP_BATTLE_LOGICUSERGRADEMANAGER_H_
#define APP_BATTLE_LOGICUSERGRADEMANAGER_H_

#include "ServerInc.h"

class LogicUserGradeManager: public CSingleton<LogicUserGradeManager>
{
private:
	friend class CSingleton<LogicUserGradeManager>;
	LogicUserGradeManager():win_idx_{{3, 0}, {5, 1}, {7, 2}, {10, 3}, {20, 4}} {};
	virtual ~LogicUserGradeManager(){}
public:
	virtual void CallDestroy() {Destroy();}
	UserGradeItem& Get(unsigned uid);
	unsigned Match(unsigned uid, unsigned grade);
	void UpdateScore(unsigned uid, unsigned score);
	int GetWinIdex(unsigned count)
	{
		if(win_idx_.count(count) > 0)
			return win_idx_[count];
		return -1;
	}
	void FullMessage(unsigned uid, User::GradeBattle* msg);
	//玩家段位排行
	void UserGradeRank();
	//排位赛战绩排行
	void UserGradeResultRank();

private:
	map<unsigned, int> win_idx_; //连胜次数和索引对应关系

private:
	int Init(unsigned uid);
};




#endif /* APP_BATTLE_LOGICUSERGRADEMANAGER_H_ */
