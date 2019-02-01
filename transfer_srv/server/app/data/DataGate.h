/*
 * DataGate.h
 *
 *  Created on: 2011-7-13
 *      Author: auto
 */

#ifndef __DATA_GATE_H__
#define __DATA_GATE_H__

#include "Kernel.h"


struct DataGate
{
	enum GATE_STATUS
	{
		UNGATE = 0,
		GATING = 1,

	};

	unsigned uid; // key

	int level; // key
	int is_win;
	int dare_times;
	int win_score;
	int best_score;
	int lose_score; // 当前闯关损失分

	int use_time; // 已使用时间. 一次闯关
	int use_resource; // 使用兵的人口. 一次闯关

	unsigned last_save_time; // 最后一次保存时间
	int status; // 当前状态 暂时没用

};

struct DataRank
{
	unsigned uid;
	int best_score;
	int rank;
	string name;
	string avatar;

	bool operator < (const DataRank& right) const
	{
		return best_score > right.best_score;
	}
};

class CDataGate : public CDataBaseDBC
{
public:
	CDataGate(int table = DB_GATE) : CDataBaseDBC(table) {}

public:
	int AddGate(const DataGate &data);
	int UpdateGate(const DataGate &gate);
	int GetGate(unsigned uid, int level, DataGate &gate);
	int GetGates(unsigned uid, vector<DataGate>& gates);
	int RemoveGate(unsigned uid, int level);
};

#endif /* __DATA_GATE_H__ */
