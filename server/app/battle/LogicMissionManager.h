/*
 * LogicMissionManager.h
 *
 *  Created on: 2016-9-13
 *      Author: city
 */

#ifndef LOGIC_MISSION_MANAGER_H_
#define LOGIC_MISSION_MANAGER_H_

#include "ServerInc.h"
#include "DataMission.h"

class LogicMissionManager : public BattleSingleton, public CSingleton<LogicMissionManager>
{
private:
	friend class CSingleton<LogicMissionManager>;
	LogicMissionManager(){};
	virtual ~LogicMissionManager(){}

public:
	virtual void CallDestroy() {Destroy();}

	struct MissionParam
	{
		int type;  //任务类型
		vector<int> subparam;

		MissionParam():
			type(0)
		{

		}
	};

	//新手初始化
	int NewUserInit(unsigned uid);

	//登录检查
	int LoginCheck(unsigned uid);

	//领取任务接口
	int Process(unsigned uid, ProtoMission::GetMissionRewardReq *reqmsg, ProtoMission::GetMissionRewardResp * respmsg);

	//验证国战任务
	int Process(unsigned uid, ProtoMission::VerfifyMissonReq *reqmsg);

	//验证世界移动任务
	int Process(unsigned uid, ProtoMission::VerifyWorldMoveMissionReq *reqmsg);

	/*
	 * 根据当前完成的任务，去解锁下个任务
	 * param  uid(in),mid(in),nextmission(out)
	 * exception runtime_error
	 * return 0-成功
	 */
	int UnlockMission(unsigned uid, unsigned mid, ProtoMission::MissionAllCPP * nextmission = NULL);

	/*
	 * 验证任务是否完成 -不带输出,将内容推送给客户端
	 * param  uid(in),param(in)
	 * return 0-成功
	 */
	int VerifyMissionComplete(unsigned uid, MissionParam & param);

	/*
	 * 验证任务是否完成 -带输出
	 * param  uid(in),param(in),missions(out) 任务信息
	 * return 0-成功
	 */
	int VerifyMissionComplete(unsigned uid, MissionParam & param, ProtoMission::MissionAllCPP * missions);

	/*
	 * 领取任务奖励
	 * param  uid(in),mid(in),respmsg(out)
	 * exception runtime_error
	 * return 0-成功
	 */
	int GetMissionReward(unsigned uid, unsigned mid, ProtoMission::GetMissionRewardResp * respmsg);

	int FullMessage(unsigned uid, ProtoMission::MissionAllCPP * msg);

private:
	/*
	 * 验证任务是否完成
	 * param  uid(in),param(in)-任务参数,id(in)任务id
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyMission(unsigned uid, MissionParam & param, unsigned id);

	/*
	 * 首次登录验证
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyFirstLogin(unsigned uid, unsigned id);

	/*
	 * 升级子建筑验证
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyUpgradeBuild(unsigned uid, unsigned id);

	/*
	 * 注册游戏名称验证
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyRegister(unsigned uid, unsigned id);

	/*
	 * 闯关验证
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyGate(unsigned uid, unsigned id);

	/*
	 * 资源产量验证
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyProductivity(unsigned uid, unsigned id);

	/*
	 * 祭祀验证
	 * param  uid(in),id(in),vctPray(in)-祭祀资源类型
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyPray(unsigned uid, unsigned id, vector<int> &vctPray);

	/*
	 * 购买装备验证
	 * param  uid(in),id(in),vctEquips(in)-购买的装备id
	 * return 0-成功
	 */
	int VerifyPurchaseEquip(unsigned uid, unsigned id);

	/*
	 *穿戴装备验证
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyDressEquip(unsigned uid, unsigned id);

	/*
	 *英雄血量恢复
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyHeroHP(unsigned uid, unsigned id);

	/*
	 *科技研究验证
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyTechResearch(unsigned uid, unsigned id);

	/*
	 * 争霸杀敌验证
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyHegemonyKillNum(unsigned uid, unsigned id);

	/*
	 * 争霸功勋验证
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyHegemonyFeats(unsigned uid, unsigned id);

	/*
	 * 招募英雄验证
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyHeroRecruit(unsigned uid, unsigned id);

	/*
	 * 使用自动建造验证
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyAutoUpgrade(unsigned uid, unsigned id);

	/*
	 * 使用黄金锤子验证
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyUseHammer(unsigned uid, unsigned id);

	/*
	 * 购买指定品质装备验证
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyCharacterBuy(unsigned uid, unsigned id);

	/*
	 * 穿戴指定品质装备验证
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyCharacterDress(unsigned uid, unsigned id);

	/*
	 * 英雄升级验证
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyHeroUpgrade(unsigned uid, unsigned id);

	/*
	 * 穿戴指定数量装备验证
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyNumDress(unsigned uid, unsigned id);

	/*
	 * 政务事件领取验证
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyGovernAffair(unsigned uid, unsigned id);

	/*
	 * 开启功勋宝箱验证
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyOpenExploitbox(unsigned uid, unsigned id);

	/*
	 * 装备商店刷新验证
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyRefreshEquipshop(unsigned uid, unsigned id);

	/*
	 * 通过迷雾战验证
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyFogGateSuccess(unsigned uid, unsigned id);

	/*
	 * 世界移动验证
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyWorldMove(unsigned uid, unsigned id);

	/*
	 * 科技研究完成验证
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int VerifyTechDone(unsigned uid, unsigned id);

	/*
	 * 统一设置指定消息格式的数据
	 * param datamission(in),msg(out)
	 * return 0-成功
	 */
	int SetMissionMessage(DataMission & datamission, ProtoMission::MissionCPP * msg);

	/*
	 * 将用位数表示完成情况的任务转换成proto文件
	 * param datamission(in),msg(out)
	 * return 0-成功
	 */
	int SetSpecialMessage(DataMission & datamission, ProtoMission::MissionCPP * msg);
};


#endif /* LOGIC_MISSION_MANAGER_H_ */
