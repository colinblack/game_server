#ifndef _CHAT_MSG_H_
#define _CHAT_MSG_H_
#include "Kernel.h"
#include "Dbs.h"
#include "MsgDef.h"
namespace chat{
class CSChatProxy: public Msg {
public:
int16_t channel;
string content;
string extend;
Identity targetId;
int32_t useGold;
virtual inline int32_t msgId() const {return 580;}
static int32_t MsgId() {return 580;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSChatProxy();}
};
}

#endif