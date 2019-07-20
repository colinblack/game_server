#ifndef _RUNE_MSG_H_
#define _RUNE_MSG_H_
#include "Kernel.h"
#include "Dbs.h"
#include "MsgDef.h"
namespace rune{
class CSMagicOpenHole: public Msg {
public:
int32_t roleId;
int32_t id;
virtual inline int32_t msgId() const {return 1268;}
static int32_t MsgId() {return 1268;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSMagicOpenHole();}
};
class CSMagicLearn: public Msg {
public:
int32_t roleId;
int32_t holeId;
int64_t magicUid;
virtual inline int32_t msgId() const {return 1273;}
static int32_t MsgId() {return 1273;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSMagicLearn();}
};
class CSMagicUpgrade: public Msg {
public:
int32_t roleId;
int64_t magicUid;
virtual inline int32_t msgId() const {return 1274;}
static int32_t MsgId() {return 1274;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSMagicUpgrade();}
};
class CSMagicDecomPose: public Msg {
public:
vector<int64_t> uidList;
virtual inline int32_t msgId() const {return 1824;}
static int32_t MsgId() {return 1824;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSMagicDecomPose();}
};
}

#endif