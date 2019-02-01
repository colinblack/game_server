/*
 * DataQixi.h
 *
 *  Created on: 2013-08-06
 *      Author: Administrator
 */

#ifndef CDATAQIXI_H___
#define CDATAQIXI_H___
#include "Kernel.h"
#define RANK_SIZE 10

struct DataQixiRank{                        //抽奖次数前10名
	int unsigned uid;
	int unsigned pay;
	char name[32];
public:
	DataQixiRank()
	{
		uid =0;
		pay = 0;
		memset(name,0,sizeof(name));
	}
};

struct DataGetWinners{                    //抽到大奖的最新4个人
	int unsigned uid;
	int reward;
	unsigned ts;
	char name[32];
public:
	DataGetWinners()
	{
		uid =0;
		reward = 0;
		ts = 0;
		memset(name,0,sizeof(name));
	}

};


struct QixiAcvitityPayRank
{
	int version;						//活动版本控制
	int Lotterynumber;					//全区当天抽奖次数
	unsigned ts;						//上一次全区抽奖时间
	int markreward;						//上电视控制
	int prizenum[4];					//4个特别奖的个数
	int rewardflag;						//结束时积分前十发奖标记
	DataGetWinners GetRewards[4];
	DataQixiRank QixiAcvitityRank[RANK_SIZE + 1];
};

class CDataQixijie {
public:
	CDataQixijie();
	virtual ~CDataQixijie();
	int Init(const std::string &path, semdat sem=sem_qixijie);
//	int UpdateRankList(const  DataQixiRank &point);         //old
	int GetRankList( vector <DataQixiRank> &vecPoints,const int version);     //版本控制
	int GetReturnData(DataGetWinners vecPrize[],int &Lotterynumber,int &markreward,vector <int> &prizenum);
	int QixiChoujiang(unsigned uid,unsigned count, unsigned integral, vector <unsigned> &awards_index_id, vector <unsigned> &awards_type_id,
			vector <unsigned> &awards_eqid, vector <unsigned> &awards_num, Json::Value &result);
//	int LotteryResults(unsigned uid,Json::Value input,int s1, int s2, int platform,int &mark_reward);   //old
//	int SetRecordLotterynumber(int addNum);			//old
	int GetRewardData(vector <DataQixiRank> &reward_vec);


private:
	bool m_init;
	CShareMemory m_sh;
};

#endif /* CDATAQIXI_H_ */
