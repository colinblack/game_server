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
}

#endif