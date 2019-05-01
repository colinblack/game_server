/*
 * UserManager.h
 *
 *  Created on: 2016-8-16
 *      Author: Ralf
 */

#ifndef LOGIC_EQUIP_SHOP_MANAGER_H_
#define LOGIC_EQUIP_SHOP_MANAGER_H_

#include "ServerInc.h"

class LogicEquipShopManager : public BattleSingleton, public CSingleton<LogicEquipShopManager>
{
private:
	friend class CSingleton<LogicEquipShopManager>;
	LogicEquipShopManager(){};
	virtual ~LogicEquipShopManager(){}
public:

	enum
	{
		price_wingman_1 = 100,
		price_wingman_2 = 500,
		price_wingman_3 = 1000,
		price_wingman_4 = 5000,
		price_wingman_5 = 10000,
	};

	virtual void CallDestroy() {Destroy();}

	//普通刷新
	int Process(unsigned uid, EquipShopLogic::RefreshReq *reqmsg, EquipShopLogic::RefreshResp * respmsg);

	//极品刷新
	int Process(unsigned uid, EquipShopLogic::SuperRefreshReq *reqmsg, EquipShopLogic::SuperRefreshResp * respmsg);

	//秒cd
	int Process(unsigned uid, EquipShopLogic::CutRefreshReq *reqmsg, EquipShopLogic::CutRefreshResp *respmsg);

	//购买装备
	int Process(unsigned uid, EquipShopLogic::PurchaseEquipReq *reqmsg, EquipShopLogic::PurchaseEquipResp *respmsg);

	//僚机兑换
	int Process(unsigned uid, EquipShopLogic::ExchangeWingmanReq *reqmsg, EquipShopLogic::ExchangeWingmanResp *respmsg);

	int EquipshopInit(unsigned uid);  //新手初始化，将数据给用户

	int LoginCheck(unsigned uid);

private:
	int DoSuperRefresh(unsigned uid, int ipool, int &jppid);

	//普通装备购买
	int PurChaseEquip(unsigned uid, DataEquipShop & equipshop, EquipShopLogic::PurchaseEquipResp *respmsg);

	//僚机兑换
	int WingManExchange(unsigned uid, unsigned eqid, EquipShopLogic::ExchangeWingmanResp * respmsg);

	int VerifyRefreshConditon(DataBase & base, unsigned now);
	int RefreshPart(DataEquipShop & equipshop, int lindex, int & eindex);  //部位刷新
	int GenerateSub(DataEquipShop & equipshop);
	int GetLevelPoolIndex(unsigned uid, int & ipool);
	int LoadEquipShopConfig();

	//装备商店刷新外部接口
	int RefreshExternalInterface(unsigned uid);

private:
	static const int MAX_POSITION = 6;
	static const int POOL_ITEMS_MAX = 6;
	static const int MAX_STAR_NUM = 4;
};


#endif /* LOGIC_EQUIP_SHOP_MANAGER_H_ */
