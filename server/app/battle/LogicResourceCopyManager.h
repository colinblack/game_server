#ifndef LOGIC_RESOURCECOPY_MANAGER_H
#define LOGIC_RESOURCECOPY_MANAGER_H

#include "ServerInc.h"

class LogicResourceCopyManager : public BattleSingleton, public CSingleton<LogicResourceCopyManager>
{
private:
	friend class CSingleton<LogicResourceCopyManager>;
	LogicResourceCopyManager(){};
	virtual ~LogicResourceCopyManager(){}

public:
	virtual void CallDestroy() {Destroy();}

	//打开窗口
	int Process(unsigned uid, ProtoResourceCopy::OpenGateWindowReq *reqmsg, ProtoResourceCopy::OpenGateWindowResp * respmsg);

	//购买资源副本
	int Process(unsigned uid, ProtoResourceCopy::BuyResourceCopyReq *reqmsg, ProtoResourceCopy::BuyResourceCopyResp * respmsg);

private:
	//打开窗口
	int OpenGateWindow(unsigned uid, ProtoResourceCopy::OpenGateWindowResp * respmsg);

	//购买资源副本奖励
	int BuyResourceCopy(unsigned uid, unsigned id, ProtoResourceCopy::BuyResourceCopyResp * respmsg);

	//填充全部信息
	int FullMessage(unsigned uid, ProtoResourceCopy::ResourceCopyCPPAll* msg);
};

#endif //LOGIC_RESOURCECOPY_MANAGER_H
