#ifndef _DBS_MSG_H_
#define _DBS_MSG_H_
#include "Kernel.h"
namespace dbs{
class TPlayerRole: public Msg {
public:
int32_t playerId_;
int32_t roleId_;
int32_t career_;
int64_t curLife_;
int64_t inPower_;
int32_t avaLife_;
int64_t combat_;
int32_t curMagic_;
int64_t maxCombat_;
int64_t lastMaxCombat_;
string entityShows_;
string entityAttrs_;
virtual inline int32_t msgId() const {return 191;}
static int32_t MsgId() {return 191;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TPlayerRole();}
};
class TPlayer: public Msg {
public:
int32_t playerId_;
string username_;
int32_t type_;
string name_;
int32_t sex_;
int32_t career_;
int32_t careerLevel_;
int32_t hangLevel_;
int32_t hangPower_;
int64_t lastHangDt_;
int32_t vipLevel_;
string gameChannel_;
int32_t oldServer_;
int32_t level_;
int32_t nuqi_;
int64_t levelDt_;
int64_t exp_;
int64_t combat_;
int64_t maxCombat_;
int64_t maxCombatDt_;
int64_t lastMaxCombat_;
int64_t offlineDt_;
int64_t reserveDt_;
int64_t gameDt_;
string ornaments_;
string entityShows_;
int64_t personOSDt_;
int64_t forbidChat_;
int32_t forbidLogin_;
virtual inline int32_t msgId() const {return 143;}
static int32_t MsgId() {return 143;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TPlayer();}
};
class TPlayerBag: public Msg {
public:
int32_t playerId_;
int32_t type_;
int32_t privilegeNum_;
int32_t extendNum_;
int32_t extendMinute_;
string extend_;
virtual inline int32_t msgId() const {return 155;}
static int32_t MsgId() {return 155;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TPlayerBag();}
};
class TPlayerItem: public Msg {
public:
int32_t playerId_;
int64_t itemUid_;
int32_t itemId_;
int32_t itemNum_;
int32_t bagType_;
string extend_;
int64_t createDt_;
virtual inline int32_t msgId() const {return 173;}
static int32_t MsgId() {return 173;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TPlayerItem();}
};
class TPlayerSkill: public Msg {
public:
int32_t playerId_;
int32_t roleId_;
int32_t skillSeries_;
int32_t skillId_;
virtual inline int32_t msgId() const {return 197;}
static int32_t MsgId() {return 197;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TPlayerSkill();}
};
class TPlayerMission: public Msg {
public:
int32_t playerId_;
int32_t missionId_;
uint32_t step_;
int32_t status_;
string extend_;
int64_t requestDt_;
virtual inline int32_t msgId() const {return 413;}
static int32_t MsgId() {return 413;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TPlayerMission();}
};
class TPlayerConfig: public Msg {
public:
int32_t playerId_;
string extend_;
virtual inline int32_t msgId() const {return 508;}
static int32_t MsgId() {return 508;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TPlayerConfig();}
};
class TPlayerCopyData: public Msg {
public:
int32_t playerId_;
int32_t copyGroup_;
int32_t enterTime_;
int32_t totalCompleteNum_;
int32_t completeNum_;
int32_t todayEnterNum_;
int32_t totalEnterDay_;
int32_t totalEnterNum_;
int32_t enterNum_;
int32_t payNum_;
int32_t getBackNum_;
int32_t assistNum_;
int32_t grabNum_;
int64_t data_;
int64_t dataEx_;
string extend_;
string json_;
virtual inline int32_t msgId() const {return 754;}
static int32_t MsgId() {return 754;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TPlayerCopyData();}
};
class TPlayerEquip: public Msg {
public:
int32_t playerId_;
int32_t roleId_;
int32_t subtype_;
uint32_t strength_;
uint32_t purify_;
int32_t refineMoney_;
int32_t zhulingAdvance_;
int32_t zhulingLevel_;
int32_t perfect_;
int32_t quenchGrade_;
int32_t suitLevel_;
int32_t spirit_;
int32_t ringAdvance_;
int32_t ringBlink_;
int32_t zhenyan_;
int32_t advance_;
int32_t godCast_;
string extend_;
string extendEx_;
virtual inline int32_t msgId() const {return 1038;}
static int32_t MsgId() {return 1038;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TPlayerEquip();}
};
class TPlayerGuard: public Msg {
public:
int32_t playerId_;
int32_t guardId_;
int32_t activated_;
int32_t out_;
string extend_;
virtual inline int32_t msgId() const {return 1501;}
static int32_t MsgId() {return 1501;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TPlayerGuard();}
};
class TPlayerNewPet: public Msg {
public:
int32_t playerId_;
int32_t petId_;
int32_t level_;
int32_t star_;
int32_t fly_;
int32_t flyBless_;
int32_t status_;
int32_t target_;
string futi_;
virtual inline int32_t msgId() const {return 1836;}
static int32_t MsgId() {return 1836;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TPlayerNewPet();}
};
class TPlayerPetFormate: public Msg {
public:
int32_t formateId_;
int32_t playerId_;
int32_t level_;
int32_t exp_;
string posInfo_;
virtual inline int32_t msgId() const {return 3132;}
static int32_t MsgId() {return 3132;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TPlayerPetFormate();}
};
class TPlayerMrRight: public Msg {
public:
int32_t playerId_;
int32_t type_;
int32_t washTime_;
int32_t targetLevel_;
string openHoles_;
string tmpHoles_;
virtual inline int32_t msgId() const {return 4735;}
static int32_t MsgId() {return 4735;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TPlayerMrRight();}
};
class TPlayerLifeFairy: public Msg {
public:
int32_t playerId_;
int32_t type_;
int32_t advanceLevel_;
int32_t advanceBless_;
int32_t advanceStar_;
int32_t advanceTargetLevel_;
virtual inline int32_t msgId() const {return 4868;}
static int32_t MsgId() {return 4868;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TPlayerLifeFairy();}
};
class TPlayerHolyBeast: public Msg {
public:
int32_t playerId_;
int32_t beastId_;
int32_t goOut_;
int32_t talent_;
int64_t attack_;
int64_t life_;
int64_t defense_;
int32_t eatLevel_;
int32_t eatExp_;
int32_t rarity_;
int32_t modelId_;
int32_t breedPlayerId_;
string breedPlayerName_;
int32_t breedModelId_;
int32_t otherTalent_;
int64_t endBreedDt_;
virtual inline int32_t msgId() const {return 4901;}
static int32_t MsgId() {return 4901;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TPlayerHolyBeast();}
};
class TPlayerFeiJian: public Msg {
public:
int32_t playerId_;
int32_t roleId_;
int32_t feiJianId_;
int32_t advanceLevel_;
int32_t star_;
virtual inline int32_t msgId() const {return 5409;}
static int32_t MsgId() {return 5409;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TPlayerFeiJian();}
};
class TFirstArenaBet: public Msg {
public:
int64_t id_;
int64_t playerId_;
int64_t aPlayerId_;
int64_t bPlayerId_;
string aName_;
string bName_;
int32_t result_;
int32_t betSelect_;
int32_t round_;
int32_t bangType_;
int32_t score_;
int64_t betDt_;
virtual inline int32_t msgId() const {return 5280;}
static int32_t MsgId() {return 5280;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TFirstArenaBet();}
};
class TPlayerOnlineSkill: public Msg {
public:
int32_t playerId_;
int32_t roleId_;
string skills_;
virtual inline int32_t msgId() const {return 3574;}
static int32_t MsgId() {return 3574;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TPlayerOnlineSkill();}
};
class TFirstArenaRank: public Msg {
public:
int64_t id_;
int32_t proxy_;
int32_t server_;
int32_t playerId_;
int32_t type_;
string name_;
int64_t combat_;
int32_t career_;
int32_t careerLevel_;
string guildName_;
int32_t vipLevel_;
int32_t score_;
int32_t group_;
int32_t rank_;
virtual inline int32_t msgId() const {return 5245;}
static int32_t MsgId() {return 5245;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TFirstArenaRank();}
};
class TFirstArenaHis: public Msg {
public:
int64_t id_;
int64_t aPlayerId_;
int64_t bPlayerId_;
int32_t bangType_;
int32_t round_;
int32_t num_;
int32_t result_;
virtual inline int32_t msgId() const {return 5296;}
static int32_t MsgId() {return 5296;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TFirstArenaHis();}
};
class TBossKillRecord: public Msg {
public:
int32_t id_;
int32_t type_;
int32_t bossId_;
int32_t playerId_;
string name_;
int64_t killDt_;
virtual inline int32_t msgId() const {return 1233;}
static int32_t MsgId() {return 1233;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TBossKillRecord();}
};
class TForbidIp: public Msg {
public:
string ip_;
string reason_;
virtual inline int32_t msgId() const {return 4818;}
static int32_t MsgId() {return 4818;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TForbidIp();}
};
class TActive: public Msg {
public:
int32_t id_;
int32_t type_;
string name_;
int32_t status_;
int32_t cross_;
int64_t beginDt_;
int64_t endDt_;
string timeOfDay_;
string dayOfWeek_;
int32_t minOpenDay_;
int32_t maxOpenDay_;
int32_t duration_;
int32_t prepare_;
string extend_;
virtual inline int32_t msgId() const {return 119;}
static int32_t MsgId() {return 119;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TActive();}
};
class TPlayerCombat: public Msg {
public:
int32_t playerId_;
string extend_;
virtual inline int32_t msgId() const {return 3527;}
static int32_t MsgId() {return 3527;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TPlayerCombat();}
};
class TXiuXianHoleRank: public Msg {
public:
int64_t id_;
int32_t proxy_;
int32_t server_;
int32_t playerId_;
string name_;
int64_t combat_;
int32_t layer_;
int32_t xianYuan_;
int32_t rank_;
virtual inline int32_t msgId() const {return 5131;}
static int32_t MsgId() {return 5131;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TXiuXianHoleRank();}
};
class TTreasureRecord: public Msg {
public:
int32_t id_;
int32_t type_;
int32_t treasureId_;
int32_t playerId_;
string name_;
int32_t career_;
int32_t level_;
int32_t careerLevel_;
int64_t drawDt_;
virtual inline int32_t msgId() const {return 1507;}
static int32_t MsgId() {return 1507;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TTreasureRecord();}
};
class TRedPacket: public Msg {
public:
int32_t id_;
int32_t type_;
int32_t status_;
string senderName_;
int32_t senderCareer_;
int32_t playerId_;
int32_t guildId_;
int32_t moneyNum_;
int32_t splitNum_;
string extend_;
int64_t createDt_;
virtual inline int32_t msgId() const {return 1344;}
static int32_t MsgId() {return 1344;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TRedPacket();}
};
class TToplist: public Msg {
public:
int32_t version_;
int32_t toplistType_;
int32_t proxyId_;
int32_t serverId_;
int32_t entityType_;
int32_t entityId_;
int32_t rank_;
int64_t value_;
int64_t value2_;
string property1_;
string property2_;
string property3_;
string extend_;
int64_t updateDt_;
virtual inline int32_t msgId() const {return 771;}
static int32_t MsgId() {return 771;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TToplist();}
};
class TMail: public Msg {
public:
int32_t id_;
int32_t playerId_;
int32_t code_;
int32_t isRead_;
int32_t isFetched_;
string sender_;
string title_;
string content_;
string attachments_;
int64_t mailDt_;
virtual inline int32_t msgId() const {return 137;}
static int32_t MsgId() {return 137;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TMail();}
};
class TDbMarket: public Msg {
public:
string uid_;
int32_t playerId_;
string name_;
int32_t itemId_;
int32_t itemNum_;
int32_t price_;
string extendJs_;
int64_t sellTime_;
virtual inline int32_t msgId() const {return 1220;}
static int32_t MsgId() {return 1220;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TDbMarket();}
};
class TMarketHis: public Msg {
public:
string uid_;
int64_t buyEntityId_;
string buyPlayerName_;
int32_t itemId_;
int32_t itemNum_;
int32_t price_;
string extendJs_;
int64_t dealTime_;
int32_t isAuction_;
virtual inline int32_t msgId() const {return 2633;}
static int32_t MsgId() {return 2633;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TMarketHis();}
};
class TTip: public Msg {
public:
int32_t playerId_;
string key_;
string params_;
int64_t operDt_;
virtual inline int32_t msgId() const {return 796;}
static int32_t MsgId() {return 796;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TTip();}
};
class TTreasureCrossCount: public Msg {
public:
int32_t id_;
int32_t type_;
int32_t totalCount_;
string drawCounts_;
int64_t drawDt_;
virtual inline int32_t msgId() const {return 5311;}
static int32_t MsgId() {return 5311;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new TTreasureCrossCount();}
};
}

#endif