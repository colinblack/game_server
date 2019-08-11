#ifndef _COPY_MSG_H_
#define _COPY_MSG_H_
#include "Kernel.h"
#include "Dbs.h"
#include "MsgDef.h"
namespace copy{
class CSEnterReincarnCopy: public Msg {
public:
int32_t copyCode;
virtual inline int32_t msgId() const {return 1827;}
static int32_t MsgId() {return 1827;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSEnterReincarnCopy();}
};
class CSLeaveCopy: public Msg {
public:
virtual inline int32_t msgId() const {return 1060;}
static int32_t MsgId() {return 1060;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSLeaveCopy();}
};
class CSQuickFinish: public Msg {
public:
int32_t copyCode;
virtual inline int32_t msgId() const {return 1885;}
static int32_t MsgId() {return 1885;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSQuickFinish();}
};
class CSGotReward: public Msg {
public:
int32_t copyCode;
virtual inline int32_t msgId() const {return 3456;}
static int32_t MsgId() {return 3456;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSGotReward();}
};
class CSEnterMagicTowerCopy: public Msg {
public:
virtual inline int32_t msgId() const {return 1562;}
static int32_t MsgId() {return 1562;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSEnterMagicTowerCopy();}
};
class CSEnterMaterialCopy: public Msg {
public:
int32_t copyCode;
virtual inline int32_t msgId() const {return 1562;}
static int32_t MsgId() {return 1562;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSEnterMaterialCopy();}
};
class CSLotteryMagicTower: public Msg {
public:
virtual inline int32_t msgId() const {return 2050;}
static int32_t MsgId() {return 2050;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSLotteryMagicTower();}
};
class SCLotteryMagicTowerResp: public Msg {
public:
int32_t pos;
virtual inline int32_t msgId() const {return 2050;}
static int32_t MsgId() {return 2050;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCLotteryMagicTowerResp();}
};
class CSQuickFinishMaterial: public Msg {
public:
vector<int32_t> copyCodes;
virtual inline int32_t msgId() const {return 2050;}
static int32_t MsgId() {return 2050;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSQuickFinishMaterial();}
};
class CSMopMaterial: public Msg {
public:
int32_t copyCode;
virtual inline int32_t msgId() const {return 2050;}
static int32_t MsgId() {return 2050;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSMopMaterial();}
};
class CSEnterWorldBoss: public Msg {
public:
int32_t copyCode;
virtual inline int32_t msgId() const {return 1803;}
static int32_t MsgId() {return 1803;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSEnterWorldBoss();}
};
class CSEnterTaskCopy: public Msg {
public:
int32_t copyCode;
virtual inline int32_t msgId() const {return 2001;}
static int32_t MsgId() {return 2001;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSEnterTaskCopy();}
};
class CSSavePlayerConfig: public Msg {
public:
string configString;
virtual inline int32_t msgId() const {return 1799;}
static int32_t MsgId() {return 1799;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSSavePlayerConfig();}
};
class CSGetWorldBossList: public Msg {
public:
virtual inline int32_t msgId() const {return 1315;}
static int32_t MsgId() {return 1315;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSGetWorldBossList();}
};
class CSGetGodPlaneList: public Msg {
public:
virtual inline int32_t msgId() const {return 1856;}
static int32_t MsgId() {return 1856;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSGetGodPlaneList();}
};
class CSEnterGodPlane: public Msg {
public:
int32_t copyCode;
virtual inline int32_t msgId() const {return 1857;}
static int32_t MsgId() {return 1857;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSEnterGodPlane();}
};
class CSFightRevive: public Msg {
public:
int32_t type;
virtual inline int32_t msgId() const {return 949;}
static int32_t MsgId() {return 949;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSFightRevive();}
};
class CSEnterImmortalroadCopy: public Msg {
public:
int32_t copyCode;
virtual inline int32_t msgId() const {return 2711;}
static int32_t MsgId() {return 2711;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSEnterImmortalroadCopy();}
};
class CSEnterExpCopy: public Msg {
public:
int32_t copyCode;
int32_t count;
virtual inline int32_t msgId() const {return 969;}
static int32_t MsgId() {return 969;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSEnterExpCopy();}
};
class CSEncourageExpCopy: public Msg {
public:
int32_t type;
int32_t count;
virtual inline int32_t msgId() const {return 981;}
static int32_t MsgId() {return 981;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSEncourageExpCopy();}
};
class CSBuyExtraExpCopy: public Msg {
public:
int32_t type;
virtual inline int32_t msgId() const {return 4149;}
static int32_t MsgId() {return 4149;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSBuyExtraExpCopy();}
};
class CSEnterPartnerIslandCopy: public Msg {
public:
int32_t type;
virtual inline int32_t msgId() const {return 2877;}
static int32_t MsgId() {return 2877;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSEnterPartnerIslandCopy();}
};
}

#endif