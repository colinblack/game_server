/*
 * LogicShop.h
 *
 *  Created on: 2016-10-28
 *      Author: dawx62fac
 */

#ifndef LOGICSHOP_H_
#define LOGICSHOP_H_

#include "ServerInc.h"

class DBCLimitShopWrap
{
public:
	DBCLimitShopWrap(unsigned uid);

	void Save()
	{
		container_->m_data->MarkChange(index_);
	}

	DBCLimitShop& Obj()
	{
		return data_;
	}

	const DBCLimitShop& Obj() const
	{
		return data_;
	}

	//购买次数是否已经用完
	bool IsFullBuyCnt(unsigned id, const ShopConfig::LimitShopItem& cfg);
	void OpBuy(unsigned id);
	unsigned GetBuyCnt(unsigned id);
	void FullMessage(unsigned id, ProtoActivity::LimitShopItem* obj);
private:
	unsigned _Index(unsigned uid);
private:
	DataLimitShopMgr*  	container_;
	unsigned	  		index_;
	DBCLimitShop& 		data_;
};


class LimitShop : public ActivitySingleton<e_Activity_Shop>, public CSingleton<LimitShop>
{
private:
	friend class CSingleton<LimitShop>;
	LimitShop(){};
	virtual ~LimitShop(){}
private:


public:
	void CallDestroy() {Destroy();}

	void Online(unsigned uid);
	void OnOffline(unsigned uid);

	//玩家的各项剩余购买次数
	int Process(unsigned uid, ProtoActivity::LimitShopUserInfoReq* rep, ProtoActivity::LimitShopUserInfoResp* resp);
	//购买指定商品
	int Process(unsigned uid, ProtoActivity::LimitShopBuyReq* req, ProtoActivity::LimitShopBuyResp* resp);
};


#endif /* LOGICSHOP_H_ */
