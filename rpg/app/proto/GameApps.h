#ifndef _GAMEAPPS_MSG_H_
#define _GAMEAPPS_MSG_H_
#include "Kernel.h"
#include "MsgDef.h"
namespace igameapp{
class SFightOper: public Msg {
public:
vector<Identity> seqEntity_;
int32_t skillId_;
Point centerPoint_;
int64_t nowTime_;
virtual inline int32_t msgId() const {return 367;}
static int32_t MsgId() {return 367;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFightOper();}
};
class SLoginGame: public Msg {
public:
string username_;
string gameChannel_;
string channelId_;
int32_t time_;
string flag_;
string version_;
int32_t playerId_;
string platformData_;
string json_;
string clientData_;
virtual inline int32_t msgId() const {return 360;}
static int32_t MsgId() {return 360;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SLoginGame();}
};
class SFormateOper: public Msg {
public:
int32_t petId_;
int32_t pos_;
virtual inline int32_t msgId() const {return 3141;}
static int32_t MsgId() {return 3141;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFormateOper();}
};
}

#endif
