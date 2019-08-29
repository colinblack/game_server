/*
 * DataVideo.h
 *
 *  Created on: 2015-12-3
 *      Author: Administrator
 */

#ifndef DATAVIDEO_H_
#define DATAVIDEO_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

struct DataVideo
{
	uint32_t uid;			//uid
	uint32_t bid;			//战报ID
	string   name;			//名字
	uint32_t identy;		//进攻者或是防守者
	uint32_t op_uid;		//对手UID
	string 	 op_name;		//对手名字
	uint32_t op_consume;	//进攻消耗
	uint32_t op_rank;		//对手排名
	uint32_t rob_r1;		//四种资源
	uint32_t rob_r2;
	uint32_t rob_r3;
	uint32_t rob_r4;
	uint32_t result;		//战斗结果
	uint32_t damage;		//损坏程度
	uint32_t star;			//星级
	uint32_t medal;			//勋章
	uint32_t revenge;		//是否复仇过
	DataVideo()
	{
		uid = 0;
		bid = 0;
		name = "";
		identy = 0;
		op_uid = 0;
		op_name = "";
		op_consume = 0;
		op_rank = 0;
		rob_r1 = 0;
		rob_r2 = 0;
		rob_r3 = 0;
		rob_r4 = 0;
		result = 0;
		damage = 0;
		star = 0;
		medal = 0;
		revenge = 0;
	}
};

class CDataVideo : public CDataBaseDBC, public AsyncDBInterface
{
public:
	CDataVideo(int table = DB_VIDEO) : CDataBaseDBC(table) {}
	virtual void doRequest(CNetPacket* packet);

	int GetVideo(unsigned uid, vector<DataVideo> &datas);

	int SetVideo(DataVideo & data);
	int AddVideo(DataVideo & data);
	int RemoveVideo(uint32_t uid,uint32_t bid);

	int RealSetVideo(CNetPacket* packet);
	int RealAddVideo(CNetPacket* packet);
	int RealRemoveVideo(CNetPacket* packet);
};


#endif /* DATAVIDEO_H_ */
