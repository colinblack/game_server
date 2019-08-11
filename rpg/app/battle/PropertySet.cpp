#include "PropertySet.h"
#include "ConfigManager.h"

int PropertyCfg::getDataType(int type) {
	switch (type) {
	case AP_MAXLIFE:
		return DT_LONG;
	case AP_ATTACK:
	case AP_DEFENCE:
	case AP_HIT:
	case AP_DODGE:
	case AP_CRIT:
		return DT_INT;
	default:
		return DT_UINT;
	};
}

void PropertyCfg::setProps(const ::google::protobuf::RepeatedPtrField<CfgCommon::Attribute> &cfgs, double multiple, PropertySets &props) {
	map<uint32_t, map<uint32_t, uint32_t> >::const_iterator gItr;
	map<uint32_t, uint32_t>::const_iterator tItr;
	for (int i = 0; i < cfgs.size(); ++i) {
		const CfgCommon::Attribute &attr = cfgs.Get(i);
		int key = attr.group() * 1000 + attr.type();
		PropertySets::iterator pItr = props.find(key);
		if (pItr == props.end()) {
			props[key].pl = 0;
		}
		debug_log("key=%d", key);
		int type = getDataType(attr.type());
		switch (type) {
		case DT_LONG:
			props[key].pl += attr.num() * multiple;
			break;
		case DT_INT:
			props[key].pi += attr.num() * multiple;
			break;
		case DT_UINT:
			props[key].pui += attr.num() * multiple;
			break;
		}
	}
}

void PropertyCfg::calcGroupBase(PropertySets &props, PropertySets &real) {
	PropertySets::iterator itr = props.begin();
	for (; itr != props.end();) {
		int key = itr->first % 1000;
		int group = itr->first / 1000;
		if (group != PROPS_GROUP_BASE) {
			++itr;
			continue;
		}
		int type = getDataType(key);
		switch (type) {
		case DT_LONG:
			real[key].pl += itr->second.pl;
			break;
		case DT_INT:
			real[key].pi += itr->second.pi;
			break;
		case DT_UINT:
			real[key].pui += itr->second.pui;
			break;
		}
		props.erase(itr++);
	}
}

void PropertyCfg::calcGroupBasePercent(PropertySets &props, PropertySets &real) {
	PropertySets::iterator itr = props.begin();
	for (; itr != props.end();) {
		int key = itr->first % 1000;
		int group = itr->first / 1000;
		if (group != PROPS_GROUP_BASE_PERCENT) {
			++itr;
			continue;
		}
		float rate = static_cast<float>(itr->second.pi) / 10000;
		int type = getDataType(key);
		switch (type) {
		case DT_LONG:
			real[key].pl += real[key].pl * rate;
			break;
		case DT_INT:
			real[key].pi += real[key].pi * rate;
			break;
		case DT_UINT:
			real[key].pui += real[key].pui * rate;
			break;
		}
		props.erase(itr++);
	}
}

uint32_t PropertyCfg::getCombat(PropertySets &props) {
	double combat = 0;
	for (int type = AP_MAXLIFE; type < AP_VALUE_MAX; ++type) {
		switch (type) {
		case AP_MAXLIFE:
			combat += static_cast<double>(props[type].pl) * 0.2;
			break;
		case AP_ATTACK:
		case AP_DEFENCE:
		case AP_HIT:
		case AP_DODGE:
		case AP_WUXINGHURT:
		case AP_WUXINGDEFENSE:
		case AP_FIXDMG:
		case AP_FIXDMGDEC:
			combat += static_cast<double>(props[type].pui) * 3.6;
			break;
		case AP_CRITDMG:
			combat += static_cast<double>(props[type].pui) * 0.72;
			break;
		case AP_INPOWER:
			combat += static_cast<double>(props[type].pui) * 0.2;
			break;
		case AP_INPOWERRECOVER:
			combat += static_cast<double>(props[type].pui) * 1.2;
			break;
		default:
			break;
		}
	}
	debug_log("combat=%f", combat);
	return combat;
}

void PropertyCfg::showProps(uint32_t uid, byte rid, const PropertySets &props, const string &code) {
	PropertySets::const_iterator itr = props.begin();
	string log;
	char item[256];
	for (; itr != props.end(); ++itr) {
		int type = getDataType(itr->first);
		switch (type) {
		case DT_LONG:
			snprintf(item, 256, "[%d,%lld],", itr->first, itr->second.pl);
			break;
		case DT_INT:
			snprintf(item, 256, "[%d,%d],", itr->first, itr->second.pi);
			break;
		case DT_UINT:
			snprintf(item, 256, "[%d,%d],", itr->first, itr->second.pui);
			break;
		}
		log.append(item);
	}
	debug_log("uid=%u,rid=%u,code=%s,prop=%s", uid, rid, code.c_str(), log.c_str());
}

void PropertyCfg::getPropsMsg(const PropertySets &props, msgs::SFightAttribute &msg) {
	msg.maxLife_ = getInt64(props, AP_MAXLIFE);
	msg.attack_ = getInt64(props, AP_ATTACK);
	msg.defence_ = getInt64(props, AP_DEFENCE);
	msg.wuxingHurt_ = getInt32(props, AP_WUXINGHURT);
	msg.wuxingDefense_ = getInt32(props, AP_WUXINGDEFENSE);
	msg.hit_ = getInt32(props, AP_HIT);
	msg.dodge_ = getInt32(props, AP_DODGE);
	msg.hitRate_ = getInt32(props, AP_HITRATE);
	msg.dodgeRate_ = getInt32(props, AP_DODGERATE);
	msg.crit_ = getInt32(props, AP_CRIT);
	msg.critBreak_ = getInt32(props, AP_CRITBREAK);
	msg.critRate_ = getInt32(props, AP_CRITRATE);
	msg.critBreakRate_ = getInt32(props, AP_CRITBREAKRATE);
	msg.critDmg_ = getInt32(props, AP_CRITDMG);
	msg.ignoreDef_ = getInt32(props, AP_IGNOREDEF);
	msg.ignoreDefBreak_ = getInt32(props, AP_IGNOREDEFBREAK);
	msg.luckRate_ = getInt32(props, AP_LUCKRATE);
	msg.curseRate_ = getInt32(props, AP_CURSERATE);
	msg.inPower_ = getInt32(props, AP_INPOWER);
	msg.inPowerRecover_ = getInt32(props, AP_INPOWERRECOVER);
	msg.inPowerDmgPer_ = getInt32(props, AP_INPOWERDMGPER);
	msg.dizzyRate_ = getInt32(props, AP_DIZZYRATE);
	msg.dizzyRateBreak_ = getInt32(props, AP_DIZZYRATEBREAK);
	msg.fixDmg_ = getInt32(props, AP_FIXDMG);
	msg.fixDmgDec_ = getInt32(props, AP_FIXDMGDEC);
	msg.recoverLife_ = getInt32(props, AP_RECOVERLIFE);
	msg.dmgAdd_ = getInt32(props, AP_DMGADD);
	msg.dmgDec_ = getInt32(props, AP_DMGDEC);
	msg.dmgBossAdd_ = getInt32(props, AP_DMGBOSSADD);
	msg.xpDmgAdd_ = getInt32(props, AP_XPDMGADD);
	msg.xpDmgDec_ = getInt32(props, AP_XPDMGDEC);
	msg.zsDmgAdd_ = getInt32(props, AP_ZSDMGADD);
	msg.zsDmgDec_ = getInt32(props, AP_ZSDMGDEC);
	msg.fsDmgAdd_ = getInt32(props, AP_FSDMGADD);
	msg.fsDmgDec_ = getInt32(props, AP_FSDMGDEC);
	msg.dsDmgAdd_ = getInt32(props, AP_DSDMGADD);
	msg.dsDmgDec_ = getInt32(props, AP_DSDMGDEC);
	msg.skillDmgAdd_ = getInt32(props, AP_SKILLDMGADD);
	msg.skillDmgDec_ = getInt32(props, AP_SKILLDMGDEC);
	msg.pvpDmgAdd_ = getInt32(props, AP_PVPDMGADD);
	msg.pvpDmgDec_ = getInt32(props, AP_PVPDMGDEC);
	msg.luckDmgAdd_ = getInt32(props, AP_LUCKDMGADD);
	msg.luckDmgDec_ = getInt32(props, AP_LUCKDMGDEC);
	msg.armor_ = getInt32(props, AP_ARMOR);
	msg.critDmgAdd_ = getInt32(props, AP_CRITDMGADD);
	msg.critDmgDec_ = getInt32(props, AP_CRITDMGDEC);
	msg.zhuXianRate_ = getInt32(props, AP_ZHUXIANRATE);
	msg.zhuXian_ = getInt32(props, AP_ZHUXIAN);
	msg.zhuXianDec_ = getInt32(props, AP_ZHUXIANDEC);
	msg.maxAvaLife_ = getInt32(props, AP_MAXAVALIFE);
	msg.avatarAttack_ = getInt32(props, AP_AVATARATTACK);
	msg.avaLifeTop_ = getInt64(props, AP_AVALIFETOP);
	msg.avaAttackTop_ = getInt32(props, AP_AVAATTACKTOP);
	msg.avaCritRate_ = getInt32(props, AP_AVACRITRATE);
	msg.avaCritBreakRate_ = getInt32(props, AP_AVACRITBREAKRATE);
	msg.avaCrit_ = getInt32(props, AP_AVACRIT);
	msg.avaCritBreak_ = getInt32(props, AP_AVACRITBREAK);
	msg.comboRate_ = getInt32(props, AP_COMBORATE);
	msg.comboBreakRate_ = getInt32(props, AP_COMBOBREAKRATE);
	msg.combo_ = getInt32(props, AP_COMBO);
	msg.comboBreak_ = getInt32(props, AP_COMBOBREAK);
	msg.maxMagic_ = getInt32(props, AP_MAXMAGIC);
	msg.attackSpeed_ = getInt32(props, AP_ATTACKSPEED);
	msg.xpMonsterDmgAdd_=0;
	msg.xpPlayerDmgAdd_=0;
}

int64_t PropertyCfg::getInt64(const PropertySets &props, int ap) {
	static PropertySets::const_iterator itr;
	itr = props.find(ap);
	return itr == props.end() ? 0 : itr->second.pl;
}

int32_t PropertyCfg::getInt32(const PropertySets &props, int ap) {
	static PropertySets::const_iterator itr;
	itr = props.find(ap);
	return itr == props.end() ? 0 : itr->second.pi;
}

uint32_t PropertyCfg::getUInt32(const PropertySets &props, int ap) {
	static PropertySets::const_iterator itr;
	itr = props.find(ap);
	return itr == props.end() ? 0 : itr->second.pui;
}

float PropertyCfg::getFloat(const PropertySets &props, int ap) {
	static PropertySets::const_iterator itr;
	itr = props.find(ap);
	return itr == props.end() ? 0 : itr->second.pf;
}
