#ifndef _PROPERTY_SET_H_
#define _PROPERTY_SET_H_

#include "Kernel.h"
#include "ConfigInc.h"
#include "Msgs.h"

typedef union {
	double pd;
	float pf;
	int32_t pi;
	uint32_t pui;
	int64_t pl;
	uint64_t pul;
} Property;

typedef map<int, Property> PropertySets;

enum PROPS_TYPE {
	AP_MAXLIFE           = 0,	//
	AP_ATTACK            = 1,	//
	AP_DEFENCE           = 2,	//
	AP_WUXINGHURT        = 3,	//
	AP_WUXINGDEFENSE     = 4,	//
	AP_HIT               = 5,	//
	AP_DODGE             = 6,	//
	AP_HITRATE           = 7,	//
	AP_DODGERATE         = 8,	//
	AP_CRIT              = 9,	//
	AP_CRITBREAK         = 10,	//
	AP_CRITRATE          = 11,	//
	AP_CRITBREAKRATE     = 12,	//
	AP_CRITDMG           = 13,	//
	AP_IGNOREDEF         = 14,	//
	AP_IGNOREDEFBREAK    = 15,	//
	AP_LUCKRATE          = 16,	//
	AP_CURSERATE         = 17,	//
	AP_INPOWER           = 18,	//
	AP_INPOWERRECOVER    = 19,	//
	AP_INPOWERDMGPER     = 20,	//
	AP_DIZZYRATE         = 21,	//
	AP_DIZZYRATEBREAK    = 22,	//
	AP_FIXDMG            = 23,	//
	AP_FIXDMGDEC         = 24,	//
	AP_RECOVERLIFE       = 25,	//
	AP_DMGADD            = 26,	//
	AP_DMGDEC            = 27,	//
	AP_DMGBOSSADD        = 28,	//
	AP_XPDMGADD          = 29,	//
	AP_XPDMGDEC          = 30,	//
	AP_ZSDMGADD          = 31,	//
	AP_ZSDMGDEC          = 32,	//
	AP_FSDMGADD          = 33,	//
	AP_FSDMGDEC          = 34,	//
	AP_DSDMGADD          = 35,	//
	AP_DSDMGDEC          = 36,	//
	AP_SKILLDMGADD       = 37,	//
	AP_SKILLDMGDEC       = 38,	//
	AP_PVPDMGADD         = 39,	//
	AP_PVPDMGDEC         = 40,	//
	AP_LUCKDMGADD        = 41,	//
	AP_LUCKDMGDEC        = 42,	//
	AP_ARMOR             = 43,	//
	AP_CRITDMGADD        = 44,	//
	AP_CRITDMGDEC        = 45,	//
	AP_ZHUXIANRATE       = 46,	//
	AP_ZHUXIAN           = 47,	//
	AP_ZHUXIANDEC        = 48,	//
	AP_MAXAVALIFE        = 49,	//
	AP_AVATARATTACK      = 50,	//
	AP_AVALIFETOP        = 51,	//
	AP_AVAATTACKTOP      = 52,	//
	AP_AVACRITRATE       = 53,	//
	AP_AVACRITBREAKRATE  = 54,	//
	AP_AVACRIT           = 55,	//
	AP_AVACRITBREAK      = 56,	//
	AP_COMBORATE         = 57,	//
	AP_COMBOBREAKRATE    = 58,	//
	AP_COMBO             = 59,	//
	AP_COMBOBREAK        = 60,	//
	AP_MAXMAGIC          = 61,	//
	AP_ATTACKSPEED       = 62,	//
	AP_HP                = 63,	//
	AP_MAX_HURTPERCENT   = 64,	//
	AP_FIXDMGPERCENT     = 65,	//免伤百分比
	AP_FIXDMGMAX         = 66,	//免伤上限
	AP_VALUE_MAX
};

enum PROPS_DATA_TYPE {
	DT_INT = 5,
	DT_FLOAT = 4,
	DT_UINT = 8,
	DT_LONG = 9,
	DT_ULONG = 10,
	DT_MAX
};

enum PROPS_GROUP {
	PROPS_GROUP_BASE = 1,			//
	PROPS_GROUP_BASE_PERCENT = 6,	//
	PROPS_GROUP_MAX
};

class PropertyCfg {
public:
	static int getDataType(int type);
	static void setProps(const ::google::protobuf::RepeatedPtrField<CfgCommon::Attribute> &cfgs, double multiple, PropertySets &props);
	static void calcGroupBase(PropertySets &props, PropertySets &real);
	static void calcGroupBasePercent(PropertySets &props, PropertySets &real);
	static uint32_t getCombat(PropertySets &props);
	static void showProps(uint32_t uid, byte rid, const PropertySets &props, const string &code);
	static void getPropsMsg(const PropertySets &props, msgs::SFightAttribute &msg);
	static int64_t getInt64(const PropertySets &props, int ap);
	static int32_t getInt32(const PropertySets &props, int ap);
	static uint32_t getUInt32(const PropertySets &props, int ap);
	static float getFloat(const PropertySets &props, int ap);
};

#endif
