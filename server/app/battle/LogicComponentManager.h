#ifndef LOGIC_COMPONENT_MANAGER_H
#define LOGIC_COMPONENT_MANAGER_H

#include "ServerInc.h"

class LogicComponentManager : public BattleSingleton, public CSingleton<LogicComponentManager>
{
private:
	friend class CSingleton<LogicComponentManager>;
	LogicComponentManager(){};
	virtual ~LogicComponentManager(){}

	enum
	{
		ret_by_not_enough = 1, //材料不足
		ret_by_already_max, //到达最高等级
	};
public:
	virtual void CallDestroy() {Destroy();}

	int LoginCheck(unsigned uid);

	//添加部件的接口
	int AddComponent(unsigned uid, unsigned compid, unsigned count, const string & reason, ProtoComponent::ComponentAllCPP* msg);

	int AddSingleComponent(unsigned uid, unsigned compid, const string & reason, ProtoComponent::ComponentCPP* msg);

	/*
	 * 添加部件的底层方法
	 * param  component(in),reason(in),msg(out) --单个部件信息
	 * exception runtime_error
	 * return 0-成功
	 */
	int AddComponentUnderlying(DataComponent& component, const string & reason, ProtoComponent::ComponentCPP * msg);

	//装载部件
	int LoadComponent(unsigned uid, unsigned compud, unsigned oldcompud, unsigned heroid, unsigned pos, ProtoComponent::ComponentAllCPP * compomsg);

	//卸载部件
	int UnloadComponent(unsigned uid, unsigned compud, unsigned heroid, ProtoComponent::ComponentCPP * compomsg);

	//强化部件
	int StrengthenComponent(unsigned uid, unsigned compud, unsigned othcompud, ProtoComponent::ComponentCPP * compomsg);

	//一键强化
	int OneKeyStrengthenComponent(unsigned uid, unsigned compud, ProtoComponent::ComponentCPP *compomsg, vector<unsigned> & delcompo);

	//计算部件基础属性，不包括百分比
	int GetBaseAttr(unsigned uid, unsigned heroid, HeroFightAttr& attr);

	//计算部件百分比属性
	int GetPercentAttr(unsigned uid, unsigned heroid, map<unsigned, double> & propertys);

	int FullMessage(unsigned uid, ProtoComponent::ComponentAllCPP* msg);

private:
	//强化部件
	int StrengthenComponentUnderly(unsigned uid, unsigned compud, unsigned othcompud);

	//加工部件，解锁主属性
	int ProcessComponent(DataComponent& component);

	int AddExp(unsigned uid, unsigned compud, unsigned exp);

	int UnlockSlave(DataComponent& component);

	int UnlockSlaveProperty(DataComponent& component, int target);

	int GetComponentBaseAttr(DataComponent& component, HeroFightAttr& attr);

	int GetComponentPercentAttr(DataComponent& component, map<unsigned, double> & propertys);

	//将oth的属性，合并到this中
	int MergePropertyFrom(map<unsigned, double> & thisPropertys, map<unsigned, double> & othPropertys);
};

#endif //LOGIC_COMPONENT_MANAGER_H
