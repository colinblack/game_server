/*
 * LogicEquipmentManager.h
 *
 *  Created on: 2016-9-16
 *      Author: city
 */

#ifndef LOGIC_EQUIPMENT_MANAGER_H_
#define LOGIC_EQUIPMENT_MANAGER_H_

#include "ServerInc.h"
#include "DataEquipment.h"


class DBCEquipmentWrap
{
public:
	DBCEquipmentWrap(unsigned uid, unsigned equd);

	void Save()
	{
		container_->m_data->MarkChange(index_);
	}

	DataEquipment& Obj()
	{
		return data_;
	}

	const DataEquipment& Obj() const
	{
		return data_;
	}


	//升级前面cnt属性
	void UpgradeAttr();
	bool IsFullLevel() const;
	bool IsReachLevel(int lvl) const;

	//指定统一属性
	void AssignAttr(int type);

	bool IsDressed() const;
	//洗练
	void Smelt(EquipSmeltType type);
private:
	bool IsFullLevel(int index) const;
private:
	EquipmentManager*	container_;
	unsigned 			index_;
	DataEquipment& 		data_;
};

class LogicEquipmentManager : public BattleSingleton, public CSingleton<LogicEquipmentManager>
{
private:
	friend class CSingleton<LogicEquipmentManager>;
	LogicEquipmentManager();
	virtual ~LogicEquipmentManager(){}
    
    enum
    {
        meal_position_code  = 7, //勋章pid值
        medal_level_limit = 35, //勋章用户等级35级限制
    };

public:
	virtual void CallDestroy() {Destroy();}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//装备出售接口
	int Process(unsigned uid, ProtoEquip::SoldEquipReq *reqmsg, ProtoEquip::SoldEquipResp * respmsg);
	//打开回购窗口的接口
	int Process(unsigned uid, ProtoEquip::OpenRepurchaseWindowReq *reqmsg, ProtoEquip::OpenRepurchaseWindowResp * respmsg);


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//获取所有战斗属性
	void GetFightAttr(unsigned uid, unsigned heroid, HeroFightAttr& attr);
	//@end

	//获取套装属性
	void GetEquipSuitAttr(unsigned uid, unsigned heroid, HeroFightAttr& attr);

	//消耗装备，返回装备msg
	int UseEquipment(unsigned uid, unsigned eqid, unsigned equd, unsigned count, string reason, DataCommon::EquipmentCPP * msg);

	//消耗装备
	int UseEquipment(unsigned uid, unsigned eqid, unsigned equd, unsigned count, string reason, unsigned & restcount);
	bool IsOwnerEquipments(unsigned uid, unsigned eqid, unsigned equd, unsigned count);

	//登录检查
	int EquipLoginInit(unsigned uid);

	/*
	 * 统一的添加道具的对外接口--会生成sub属性
	 * param  uid(in),eqid(in),count(in),reason(in),msg(out) --多个装备信息
	 * exception runtime_error
	 * return 0-成功
	 */
	int AddEquipment(unsigned uid, unsigned eqid, unsigned count, string  reason, DataCommon::EquipmentAllCPP * msg);

	int AddEquipment(unsigned uid, unsigned eqid, unsigned count, const string& reason);
	int AddEquipment(unsigned uid, const VipGiftConfig::EquipReward& equip, const string& reason);

	/*
	 * 添加道具的底层方法
	 * param  equip(in),reason(in),msg(out) --单个装备信息
	 * exception runtime_error
	 * return 0-成功
	 */
	int AddEqupmentUnderlying(DataEquipment& equip, string  reason, DataCommon::EquipmentCPP * msg);

	/*
	 * 穿装备
	 * param  uid(in),equd(in)-新穿装备,oldequd(in)--旧装备,heroid(in),msg(out) --多个装备信息
	 * exception runtime_error
	 * return 0-成功
	 */
	int DressEquipment(unsigned uid, unsigned equd, unsigned oldequd, unsigned heroid, ProtoHero::EquipmentWrapCPP * msg);

	/*
	 * 脱装备
	 * param  uid(in),equd(in),heroid(in),msg(out) --单个装备信息
	 * exception runtime_error
	 * return 0-成功
	 */
	int UnDressEquipment(unsigned uid, unsigned equd, unsigned heroid, DataCommon::EquipmentCPP * msg);

	/*
	 * 一键装备
	 * param  uid(in),heroid(in),msg(out) --批量装备信息
	 * exception runtime_error
	 * return 0-成功
	 */
	int OneKeyDressEquipment(unsigned uid, unsigned heroid, ProtoHero::EquipmentWrapCPP * msg);

	/*
	 * 互换装备
	 * param  uid(in),heroid(in),othheroid(in),msg(out) --批量装备信息
	 * exception runtime_error
	 * return 0-成功
	 */
	int SwitchDress(unsigned uid, unsigned heroid, unsigned othheroid, ProtoHero::EquipmentWrapCPP * msg);

	/*
	 * 一键卸装
	 * param  uid(in),heroid(in),msg(out) --批量装备信息
	 * exception runtime_error
	 * return 0-成功
	 */
	int UnDressAllEquipment(unsigned uid, unsigned heroid, ProtoHero::EquipmentWrapCPP * msg);

	/*
	 * 装备洗练，针对单个装备
	 * param  uid(in),equd(in),msg(out)
	 * exception runtime_error
	 * return 0-成功
	 */
	int SmeltEquipment(unsigned uid, unsigned equd, int type, ProtoHero::EquipSmeltResp* msg);

	/*
	 * 装备售出
	 * param  uid(in),equd(in),msg(out)
	 * exception runtime_error
	 * return 0-成功
	 */
	int SoldEquipment(unsigned uid, unsigned equd, ProtoEquip::SoldEquipResp * msg);

	/*
	 * 结算免费洗练按时间累积的次数
	 * param  uid(in),last_offtime(in)
	 * return 0-成功
	 */
	int CalculateRefreshTimes(unsigned uid, unsigned last_offtime);

	/*
	 * 获取免费洗练次数
	 * param  uid(in)
	 * return 次数
	 */
	int GetRefreshTimes(unsigned uid);

	/*
	 * 合成套装
	 * param  uid(in)
	 * exception runtime_error
	 * return 套装的ud
	 */
	unsigned ComposeEquipSuit(unsigned uid, unsigned equd, vector<unsigned> & material, DataCommon::EquipmentAllCPP * msg);

	//获取该英雄的僚机的eqid
	unsigned GetWingmanByHeroid(unsigned uid, unsigned heroid);

	//获取用户是否已拥有某僚机
	bool IsHaveTheWingman(unsigned uid, unsigned eqid);

	//判断是否是僚机
	bool IsWingMan(unsigned uid, unsigned equd);

	//清空装备表-ADMIN接口
	int AdminClear(unsigned uid, bool isAdmin = false);

private:
	//洗练外部接口
	int SmeltExternalInterface(unsigned uid, unsigned equd);

	//装备外部接口
	int EquipExternalInterface(unsigned uid, unsigned type);

	//消耗洗练次数
	int SmeltCostTimesOrCash(unsigned uid, int type, ProtoHero::EquipSmeltResp* msg);

	//升级洗练属性等级
	int UpgradeSubProperty(DataEquipment& equip, int type);

	//更新激活的洗练属性
	int UpdateExtraSubProperty(DataEquipment& equip, bool isSame = true);

	//合成套装前进行验证
	int VerifyComposeCondition(unsigned uid, unsigned equd, vector<unsigned> & material, vector<unsigned> & counts);

	//继承旧装备的洗练属性
	int InheritSubProperty(DataEquipment& equip, DataEquipment& oldequip);

	//判断是否属性值满级且相同
	bool IsEquipSubFullAndSame(DataEquipment& equip, int maxlevel, int maxstar);

	//判断洗练属性是否满级
	bool IsEquipSubFull(DataEquipment& equip, int maxlevel, int maxstar);

	/*
	 * 检查并删除已出售并且在回购时效外的装备
	 * param  uid(in)
	 * exception runtime_error
	 * return 0-成功
	 */
	int DelEquipmentCheck(unsigned uid);

	//装备相关属性计算
	void GetFightAttr(const DataEquipment& equip, HeroFightAttr& attr);

	/*
	 * 产生定制的装备
	 * param  equip(out)
	 * return 0-成功
	 */
	int ProduceSpecialEquipment(DataEquipment & equip);

	/*
	 * 针对装备进行处理--确定星级，产生洗练属性
	 * param  equip(out)
	 * return 0-成功
	 */
	int ProduceEquipment(DataEquipment & equip);

	/*
	 * 初始化洗练属性等级
	 * param  equip(in&out)
	 * return 0-成功
	 */
	int InitEquipSubLv(DataEquipment & equip);

	/*
	 * 针对饰品进行处理--确定品质，产生统和勇属性
	 * param  equip(out)
	 * return 0-成功
	 */
	int ProduceMedal(DataEquipment & equip);

	/*
	 * 洗练属性
	 * param  equip(in&out),star(in)
	 * return 0-成功
	 */
	int SmeltProperty(DataEquipment & equip, unsigned star = 0);

	/*
	 * 获取指定位置处的属性等级
	 * param  equip(in),pos(in)
	 * return -1-失败
	 */
	int GetPropertyLevel(DataEquipment & equip, int pos);

	/*
	 *设置指定位置处的属性等级
	 * param  equip(out),pos(in),val(in)
	 * return 0-成功
	 */
	int SetPropertyLevel(DataEquipment & equip, int pos, int val);

	friend class DBCEquipmentWrap;
public:
	static const  int MAX_REFRESH_TIME = 12;
	static const  int MAX_WINGMAN_KIND	= 9;
	static const int Wing_Man_Eqids[MAX_WINGMAN_KIND];
};


#endif /* LOGIC_EQUIPMENT_MANAGER_H_ */
