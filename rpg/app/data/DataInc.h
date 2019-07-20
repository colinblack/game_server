/*
 * DataInc.h
 *
 *  Created on: 2019年4月18日
 *      Author: Administrator
 */

#ifndef _DATA_INC_H_
#define _DATA_INC_H_

#include "DataUserMapping.h"
#include "DataRoleMapping.h"
#include "DataIdCtrl.h"
#include "DataBase.h"
#include "DataLastSafeArea.h"
#include "DataPos.h"
#include "DataSkill.h"
#include "DataPay.h"
#include "DataRole.h"
#include "DataMission.h"
#include "DataAdvance.h"
#include "DataEquip.h"
#include "DataShenQi.h"
#include "DataBagExtend.h"
#include "DataTreasure.h"
#include "DataForge.h"
#include "DataAttr.h"
#include "DataRoleAttr.h"
#include "DataAttrExtend.h"
#include "DataActive.h"
#include "DataLocal.h"

class UserCache {
public:
	UserCache() {
		uid_ = 0;
		init_ = false;
	}

	bool init_;
	uint32_t uid_;
	DataBase base_;
	map<uint32_t, DataPay> pay_;
	DataPos pos_;
	DataShenQi shenqi_;
	map<uint32_t, DataMission> mission_;
	map<byte, DataRole> role_;
	map<byte, map<byte, uint32_t> > role_bag_;	//<bagtype, <part, ud>>
	list<DataSkill> skill_;
	list<DataAdvance> advance_;
	map<uint32_t, DataEquip> equip_;
	map<uint16_t, DataBagExtend> bag_extend_;
	map<uint32_t, DataTreasure> treasure_;
	list<DataForge> forge_;
	map<uint32_t,CardInfo> m_cards;
	ReinCarnInfo m_reinCarnInfo;
	map<uint32_t, map<uint32_t, DataRoleSuit> > role_suit_;
	map<uint32_t,DataRoleRune> m_runeInfo;
	map<uint32_t, TreasureHunt> m_treasure_hunt;
	map<uint32_t, CopyInfo> m_copyInfo;
	map<uint32_t, DataActivity> act_info_;
	map<uint32_t, DataActivity> act_cnt_;
	map<uint32_t, map<uint32_t, DataTitle> > role_title_;
	DataActiveEtr m_active_;

};

#endif /* _DATA_INC_H_ */
