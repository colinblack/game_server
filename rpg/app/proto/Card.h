#ifndef _CARD_MSG_H_
#define _CARD_MSG_H_
#include "Kernel.h"
#include "Dbs.h"
#include "MsgDef.h"
namespace card{
class CSCardActiveCard: public Msg {
public:
int64_t uid;
virtual inline int32_t msgId() const {return 1920;}
static int32_t MsgId() {return 1920;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSCardActiveCard();}
};
}

#endif