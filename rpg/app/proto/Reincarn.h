#ifndef _REINCARN_MSG_H_
#define _REINCARN_MSG_H_
#include "Kernel.h"
#include "Dbs.h"
#include "MsgDef.h"
namespace reincarn{
class CSRingActive: public Msg {
public:
int32_t ringId;
virtual inline int32_t msgId() const {return 1112;}
static int32_t MsgId() {return 1112;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSRingActive();}
};
class CSReinCarn: public Msg {
public:
virtual inline int32_t msgId() const {return 1724;}
static int32_t MsgId() {return 1724;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSReinCarn();}
};
class CSReinCarnGetExpByItems: public Msg {
public:
int32_t itemId;
virtual inline int32_t msgId() const {return 1725;}
static int32_t MsgId() {return 1725;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSReinCarnGetExpByItems();}
};
class CSReinCarnGetExpByLevel: public Msg {
public:
virtual inline int32_t msgId() const {return 1726;}
static int32_t MsgId() {return 1726;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSReinCarnGetExpByLevel();}
};
}

#endif