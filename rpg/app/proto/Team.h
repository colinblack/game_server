#ifndef _TEAM_MSG_H_
#define _TEAM_MSG_H_
#include "Kernel.h"
#include "Dbs.h"
#include "MsgDef.h"
#include "Msgs.h"
namespace team{
class CSCreateTeam: public Msg {
public:
Identity target;
vector<int32_t> targetList;
int16_t needLevel;
virtual inline int32_t msgId() const {return 533;}
static int32_t MsgId() {return 533;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSCreateTeam();}
};
class CSLeaveTeam: public Msg {
public:
virtual inline int32_t msgId() const {return 534;}
static int32_t MsgId() {return 534;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSLeaveTeam();}
};
class CSDisBandTeam: public Msg {
public:
virtual inline int32_t msgId() const {return 2870;}
static int32_t MsgId() {return 2870;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSDisBandTeam();}
};
class CSCheckMemCopy: public Msg {
public:
virtual inline int32_t msgId() const {return 1185;}
static int32_t MsgId() {return 1185;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CSCheckMemCopy();}
};
class SCCheckMemCopyResponse: public Msg {
public:
vector<msgs::STeamMemberCopyCheck> checkList;
virtual inline int32_t msgId() const {return 1185;}
static int32_t MsgId() {return 1185;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCCheckMemCopyResponse();}
};
}

#endif