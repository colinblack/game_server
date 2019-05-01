/*
 * LogicWeaponsMgr.h
 *
 *  Created on: 2016-9-9
 *      Author: dawx62fac
 */

#ifndef LOGICWEAPONSMGR_H_
#define LOGICWEAPONSMGR_H_

/*
 * 兵器系统
 */

#include "ServerInc.h"

class DBCWeaponWrap
{
public:
	DBCWeaponWrap(unsigned uid, unsigned id);
	DBCWeaponWrap(unsigned index);

	DBCWeapon& 	Obj()
	{
		return data_;
	}

	void Save()
	{
		container_->m_data->MarkChange(index_);
	}

	const WeaponConfig::WeaponLvL& CfgLVL() const;
	const WeaponConfig::WeaponItem& CfgItem() const;

	void Unlock();
	void Cast(unsigned nMul);

	void SetLevel(unsigned level);

	void Reset();
private:
	DataWeaponMgr*	container_;
	unsigned		index_;
	DBCWeapon& 		data_;
};

class LogicWeaponsMgr : public BattleSingleton, public CSingleton<LogicWeaponsMgr>
{
private:
	friend class CSingleton<LogicWeaponsMgr>;
	LogicWeaponsMgr(){}

private:
	unsigned GetWeaponCastMul(unsigned id, const WeaponConfig::WeaponLvL& cfg, const std::vector<unsigned>& v_extra_prob);

	DemoHeroProperty _Id2Property(unsigned id);

	//提升军工的外部接口
	int UpgradeWeaponExternalInterface(unsigned uid, unsigned iron);

public:
	virtual void CallDestroy() { Destroy();}

	void Online(unsigned uid);
	void Offline(unsigned uid);

	//用户的兵器研究重置
	void Reset(unsigned uid);

	//获取兵器系统增加的攻击，防御，血量等属性
	void GetHeroFightAttr(unsigned uid, HeroFightAttr& attr);

	void FullMessage(unsigned uid, User::Weapon* obj);

	void SetBotPlayerData(unsigned uid, const BotConfig::BotPlayer* obj);

	//////////////////////////////////////////////////////////////////////////
	//兵器解锁
	int Process(unsigned uid, ProtoWeapon::WeaponUnlockReq* req, ProtoWeapon::WeaponUnlockResp* resp);
	//兵器铸造
	int Process(unsigned uid, ProtoWeapon::WeaponCastReq* req, ProtoWeapon::WeaponCastResp* resp);

};

#endif /* LOGICWEAPONSMGR_H_ */
