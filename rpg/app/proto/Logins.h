#ifndef _LOGINS_MSG_H_
#define _LOGINS_MSG_H_
#include "Kernel.h"
#include "Dbs.h"
#include "GameApps.h"
#include "MsgDef.h"
#include "Msgs.h"
namespace logins{
class SQuery: public Msg {
public:
string username_;
string gameChannel_;
string channelId_;
int32_t time_;
string flag_;
string version_;
int32_t serverId_;
string json_;
virtual inline int32_t msgId() const {return 342;}
static int32_t MsgId() {return 342;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SQuery();}
};
class SQueryResult: public Msg {
public:
uint16_t proxyId_;
uint16_t serverId_;
vector<dbs::TPlayer> playerList_;
virtual inline int32_t msgId() const {return 343;}
static int32_t MsgId() {return 343;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SQueryResult();}
};
class SLogin: public Msg {
public:
string username_;
string gameChannel_;
string channelId_;
int32_t time_;
string flag_;
string version_;
int32_t playerId_;
string name_;
int16_t sex_;
int16_t career_;
int32_t sdkTime_;
string platformExtend_;
int32_t serverId_;
string json_;
virtual inline int32_t msgId() const {return 344;}
static int32_t MsgId() {return 344;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SLogin();}
};
class SLoginResult: public Msg {
public:
string gateHost_;
int32_t gatePort_;
string token_;
uint16_t proxyId_;
uint16_t serverId_;
dbs::TPlayer player_;
virtual inline int32_t msgId() const {return 345;}
static int32_t MsgId() {return 345;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SLoginResult();}
};
class SLoginPing: public Msg {
public:
int64_t clientTs_;
string extend_;
virtual inline int32_t msgId() const {return 346;}
static int32_t MsgId() {return 346;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SLoginPing();}
};
class SLoginPong: public Msg {
public:
int64_t clientTs_;
int64_t serverTs_;
virtual inline int32_t msgId() const {return 347;}
static int32_t MsgId() {return 347;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SLoginPong();}
};
class SQueryGameData: public Msg {
public:
vector<int32_t> cmds_;
virtual inline int32_t msgId() const {return 348;}
static int32_t MsgId() {return 348;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SQueryGameData();}
};
class SRoleMove: public Msg {
public:
Identity entityId_;
int64_t operTime_;
uint16_t moveId_;
vector<Point> path_;
virtual inline int32_t msgId() const {return 349;}
static int32_t MsgId() {return 349;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRoleMove();}
};
class SEnterHang: public Msg {
public:
virtual inline int32_t msgId() const {return 350;}
static int32_t MsgId() {return 350;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEnterHang();}
};
class SBackToCity: public Msg {
public:
virtual inline int32_t msgId() const {return 351;}
static int32_t MsgId() {return 351;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBackToCity();}
};
class SBatchFightResultReq: public Msg {
public:
map<int32_t, int32_t> monsters_;
virtual inline int32_t msgId() const {return 352;}
static int32_t MsgId() {return 352;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBatchFightResultReq();}
};
class SBatchFightResultResp: public Msg {
public:
bool canRefreshElite_;
virtual inline int32_t msgId() const {return 353;}
static int32_t MsgId() {return 353;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBatchFightResultResp();}
};
class SHangChallengeBoss: public Msg {
public:
vector<Point> resetPoints_;
virtual inline int32_t msgId() const {return 354;}
static int32_t MsgId() {return 354;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SHangChallengeBoss();}
};
class SUseSkill: public Msg {
public:
int32_t roleId_;
igameapp::SFightOper oper_;
int16_t skillUid_;
bool noCd_;
virtual inline int32_t msgId() const {return 355;}
static int32_t MsgId() {return 355;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SUseSkill();}
};
class SFightResultReq: public Msg {
public:
int32_t monsterId_;
Point killPoint_;
virtual inline int32_t msgId() const {return 356;}
static int32_t MsgId() {return 356;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFightResultReq();}
};
class SMapJump: public Msg {
public:
Identity entityId_;
int64_t operTime_;
uint16_t moveId_;
string jumpId_;
bool isReverse_;
virtual inline int32_t msgId() const {return 366;}
static int32_t MsgId() {return 366;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMapJump();}
};
class SMapTransfer: public Msg {
public:
int64_t operTime_;
int32_t passType_;
int32_t passId_;
int32_t passToId_;
virtual inline int32_t msgId() const {return 367;}
static int32_t MsgId() {return 367;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMapTransfer();}
};
class SMissionReq: public Msg {
public:
int32_t missionId_;
virtual inline int32_t msgId() const {return 368;}
static int32_t MsgId() {return 368;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMissionReq();}
};
class SMissionCommit: public Msg {
public:
int32_t missionId_;
virtual inline int32_t msgId() const {return 369;}
static int32_t MsgId() {return 369;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMissionCommit();}
};
class SActiveAdvance: public Msg {
public:
int32_t roleId_;
int32_t type_;
virtual inline int32_t msgId() const {return 370;}
static int32_t MsgId() {return 370;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveAdvance();}
};
class SUpgradeSkill: public Msg {
public:
int32_t roleId_;
int32_t skillId_;
virtual inline int32_t msgId() const {return 371;}
static int32_t MsgId() {return 371;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SUpgradeSkill();}
};
class SAdvanceReq: public Msg {
public:
int32_t roleId_;
int32_t type_;
int32_t itemId_;
bool autoBuy_;
virtual inline int32_t msgId() const {return 519;}
static int32_t MsgId() {return 519;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAdvanceReq();}
};
class SAdvanceResp: public Msg {
public:
bool success_;
int32_t activeMul_;
virtual inline int32_t msgId() const {return 373;}
static int32_t MsgId() {return 373;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAdvanceResp();}
};
class SAdvanceEatDan: public Msg {
public:
int32_t roleId_;
int32_t type_;
int32_t itemId_;
virtual inline int32_t msgId() const {return 374;}
static int32_t MsgId() {return 374;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAdvanceEatDan();}
};
class SBagDecompose: public Msg {
public:
vector<int64_t> uidList;
virtual inline int32_t msgId() const {return 1699;}
static int32_t MsgId() {return 1699;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBagDecompose();}
};
class SShenQiPiece: public Msg {
public:
int32_t itemId_;
virtual inline int32_t msgId() const {return 375;}
static int32_t MsgId() {return 375;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SShenQiPiece();}
};
class SShenQi: public Msg {
public:
virtual inline int32_t msgId() const {return 376;}
static int32_t MsgId() {return 376;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SShenQi();}
};
class SUpgradeSkillAll: public Msg {
public:
int32_t roleId_;
virtual inline int32_t msgId() const {return 377;}
static int32_t MsgId() {return 377;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SUpgradeSkillAll();}
};
class SEquipEquip: public Msg {
public:
int32_t roleId_;
vector<int64_t> uds_;
virtual inline int32_t msgId() const {return 378;}
static int32_t MsgId() {return 378;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEquipEquip();}
};
class SBagOpenGrid: public Msg {
public:
int32_t bagType_;
int32_t gridId_;
int32_t gridNum_;
virtual inline int32_t msgId() const {return 379;}
static int32_t MsgId() {return 379;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBagOpenGrid();}
};
class SActiveTreasure: public Msg {
public:
int32_t type_;
virtual inline int32_t msgId() const {return 1773;}
static int32_t MsgId() {return 1773;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveTreasure();}
};
class STreasureAdvance: public Msg {
public:
int32_t type_;
int32_t itemId_;
virtual inline int32_t msgId() const {return 1754;}
static int32_t MsgId() {return 1754;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STreasureAdvance();}
};
class STreasureEatDan: public Msg {
public:
int32_t type_;
int32_t itemId_;
virtual inline int32_t msgId() const {return 1771;}
static int32_t MsgId() {return 1771;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STreasureEatDan();}
};
class SBagUse: public Msg {
public:
int32_t bagType_;
int64_t itemUid_;
int32_t itemNum_;
int32_t value_;
virtual inline int32_t msgId() const {return 422;}
static int32_t MsgId() {return 422;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBagUse();}
};
class SStrengthenReq: public Msg {
public:
int32_t roleId_;
vector<int32_t> equipType_;
int32_t toLevel_;
virtual inline int32_t msgId() const {return 1053;}
static int32_t MsgId() {return 1053;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SStrengthenReq();}
};
class SStrengthenResp: public Msg {
public:
vector<dbs::TPlayerEquip> equip_;
virtual inline int32_t msgId() const {return 1053;}
static int32_t MsgId() {return 1053;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SStrengthenResp();}
};
class SAdvanceRide: public Msg {
public:
bool ride_;
virtual inline int32_t msgId() const {return 599;}
static int32_t MsgId() {return 599;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAdvanceRide();}
};
class SPurifyReq: public Msg {
public:
int32_t roleId_;
vector<int32_t> equipType_;
virtual inline int32_t msgId() const {return 2222;}
static int32_t MsgId() {return 2222;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPurifyReq();}
};
class SPurifyResp: public Msg {
public:
vector<dbs::TPlayerEquip> equip_;
virtual inline int32_t msgId() const {return 2222;}
static int32_t MsgId() {return 2222;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPurifyResp();}
};
class CEmbedGemReq: public Msg {
public:
int32_t roleId_;
int32_t equipType_;
map<int32_t, int64_t> gemUidSlot_;
virtual inline int32_t msgId() const {return 1037;}
static int32_t MsgId() {return 1037;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CEmbedGemReq();}
};
class SEmbedGemResp: public Msg {
public:
dbs::TPlayerEquip tPlayerEquip_;
virtual inline int32_t msgId() const {return 1037;}
static int32_t MsgId() {return 1037;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEmbedGemResp();}
};
class CRemoveGemReq: public Msg {
public:
int32_t roleId_;
int32_t equipType_;
int32_t gemSlot_;
virtual inline int32_t msgId() const {return 1056;}
static int32_t MsgId() {return 1056;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CRemoveGemReq();}
};
class SRemoveGemResp: public Msg {
public:
dbs::TPlayerEquip tPlayerEquip_;
virtual inline int32_t msgId() const {return 1056;}
static int32_t MsgId() {return 1056;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRemoveGemResp();}
};
class CctivateGemTargetReq: public Msg {
public:
int32_t roleId_;
int32_t targetId_;
virtual inline int32_t msgId() const {return 1057;}
static int32_t MsgId() {return 1057;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CctivateGemTargetReq();}
};
class CUpgradeGemReq: public Msg {
public:
int32_t roleId_;
int32_t equipType_;
vector<int32_t> gemSlot_;
virtual inline int32_t msgId() const {return 1120;}
static int32_t MsgId() {return 1120;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CUpgradeGemReq();}
};
class SUpgradeGemResp: public Msg {
public:
dbs::TPlayerEquip tPlayerEquip_;
virtual inline int32_t msgId() const {return 1120;}
static int32_t MsgId() {return 1120;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SUpgradeGemResp();}
};
class STitleReq: public Msg {
public:
int32_t roleId_;
int32_t titleId_;
virtual inline int32_t msgId() const {return 1077;}
static int32_t MsgId() {return 1077;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STitleReq();}
};
class COnlineRewardReq: public Msg {
public:
int32_t onlineTime_;
virtual inline int32_t msgId() const {return 4071;}
static int32_t MsgId() {return 4071;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new COnlineRewardReq();}
};
class CActiveFashionReq: public Msg {
public:
int32_t roleId_;
int32_t type_;
int32_t fashionId_;
virtual inline int32_t msgId() const {return 1418;}
static int32_t MsgId() {return 1418;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CActiveFashionReq();}
};
class CAdvanceFashionReq: public Msg {
public:
int32_t roleId_;
int32_t type_;
int32_t fashionId_;
virtual inline int32_t msgId() const {return 2046;}
static int32_t MsgId() {return 2046;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CAdvanceFashionReq();}
};
class CPutOnFashionReq: public Msg {
public:
int32_t roleId_;
int32_t type_;
int32_t fashionId_;
virtual inline int32_t msgId() const {return 2047;}
static int32_t MsgId() {return 2047;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CPutOnFashionReq();}
};
class SPutOnFashionResp: public Msg {
public:
int32_t fashionId_;
virtual inline int32_t msgId() const {return 2047;}
static int32_t MsgId() {return 2047;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPutOnFashionResp();}
};
class CGetOffFashionReq: public Msg {
public:
int32_t roleId_;
int32_t type_;
int32_t fashionId_;
virtual inline int32_t msgId() const {return 2048;}
static int32_t MsgId() {return 2048;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CGetOffFashionReq();}
};
class SGetOffFashionResp: public Msg {
public:
int32_t fashionId_;
virtual inline int32_t msgId() const {return 2048;}
static int32_t MsgId() {return 2048;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGetOffFashionResp();}
};
class CActiveFashionSuitReq: public Msg {
public:
int32_t roleId_;
int32_t suitId_;
int32_t num_;
virtual inline int32_t msgId() const {return 3742;}
static int32_t MsgId() {return 3742;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new CActiveFashionSuitReq();}
};
class SActiveFashionSuitResp: public Msg {
public:
map<int32_t, msgs::SInts> suits_;
virtual inline int32_t msgId() const {return 3742;}
static int32_t MsgId() {return 3742;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveFashionSuitResp();}
};
class SActiveSuitReq: public Msg {
public:
int32_t roleId_;
int32_t suitId_;
vector<int64_t> uids_;
virtual inline int32_t msgId() const {return 3077;}
static int32_t MsgId() {return 3077;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveSuitReq();}
};
class SUnlockSuitReq: public Msg {
public:
int32_t roleId_;
int32_t suitId_;
virtual inline int32_t msgId() const {return 3085;}
static int32_t MsgId() {return 3085;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SUnlockSuitReq();}
};
class SDressSuitReq: public Msg {
public:
int32_t roleId_;
int32_t suitId_;
bool isDress_;
virtual inline int32_t msgId() const {return 3086;}
static int32_t MsgId() {return 3086;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SDressSuitReq();}
};
class STreasureDrawReq: public Msg {
public:
int32_t type_;
int32_t drewNum_;
virtual inline int32_t msgId() const {return 1486;}
static int32_t MsgId() {return 1486;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STreasureDrawReq();}
};
class STreasureDrawResp: public Msg {
public:
vector<int32_t> drawIds_;
vector<int32_t> rewards_;
virtual inline int32_t msgId() const {return 1486;}
static int32_t MsgId() {return 1486;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STreasureDrawResp();}
};
class STreasureGetRewardHisReq: public Msg {
public:
int32_t type_;
virtual inline int32_t msgId() const {return 1519;}
static int32_t MsgId() {return 1519;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STreasureGetRewardHisReq();}
};
class STreasureGetRewardHisResp: public Msg {
public:
vector<dbs::TTreasureRecord> records_;
virtual inline int32_t msgId() const {return 1519;}
static int32_t MsgId() {return 1519;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STreasureGetRewardHisResp();}
};
class SBagMoveItem: public Msg {
public:
int32_t fromBagType_;
int32_t toBagType_;
int64_t itemUid_;
virtual inline int32_t msgId() const {return 425;}
static int32_t MsgId() {return 425;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBagMoveItem();}
};
class SBagMoveItemAll: public Msg {
public:
int32_t fromBagType_;
int32_t toBagType_;
virtual inline int32_t msgId() const {return 2018;}
static int32_t MsgId() {return 2018;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBagMoveItemAll();}
};
class SGetActivityReq: public Msg {
public:
int32_t id_;
int32_t count_;
virtual inline int32_t msgId() const {return 2809;}
static int32_t MsgId() {return 2809;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGetActivityReq();}
};
class SGetActivityRewardReq: public Msg {
public:
int32_t id_;
virtual inline int32_t msgId() const {return 1127;}
static int32_t MsgId() {return 1127;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGetActivityRewardReq();}
};
class SzhulingUpLevelReq: public Msg {
public:
int32_t roleId_;
int32_t equipType_;
bool isAuto_;
virtual inline int32_t msgId() const {return 2577;}
static int32_t MsgId() {return 2577;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SzhulingUpLevelReq();}
};
class SzhulingUpLevelResp: public Msg {
public:
dbs::TPlayerEquip plyerEquip;
virtual inline int32_t msgId() const {return 2577;}
static int32_t MsgId() {return 2577;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SzhulingUpLevelResp();}
};
class SzhulingUpAdvanceReq: public Msg {
public:
int32_t roleId_;
int32_t equipType_;
virtual inline int32_t msgId() const {return 2585;}
static int32_t MsgId() {return 2585;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SzhulingUpAdvanceReq();}
};
class SzhulingUpAdvanceResp: public Msg {
public:
dbs::TPlayerEquip PlayerEquip;
virtual inline int32_t msgId() const {return 2585;}
static int32_t MsgId() {return 2585;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SzhulingUpAdvanceResp();}
};
class SopenZhulingReq: public Msg {
public:
int32_t roleId_;
virtual inline int32_t msgId() const {return 3493;}
static int32_t MsgId() {return 3493;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SopenZhulingReq();}
};
class SSkillCleanNuQi: public Msg {
public:
virtual inline int32_t msgId() const {return 2069;}
static int32_t MsgId() {return 2069;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SSkillCleanNuQi();}
};
class SBuyReq: public Msg {
public:
int32_t id;
int32_t itemId;
int32_t realPrice;
int32_t num;
virtual inline int32_t msgId() const {return 481;}
static int32_t MsgId() {return 481;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBuyReq();}
};
class SDevilAngelequipReq: public Msg {
public:
int32_t uid;
int32_t roleId;
virtual inline int32_t msgId() const {return 2244;}
static int32_t MsgId() {return 2244;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SDevilAngelequipReq();}
};
class SPlayerSignEveryDayReq: public Msg {
public:
int16_t flag_;
virtual inline int32_t msgId() const {return 1407;}
static int32_t MsgId() {return 1407;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerSignEveryDayReq();}
};
class SGetSignEverydayRwardReq: public Msg {
public:
int16_t day_;
virtual inline int32_t msgId() const {return 1884;}
static int32_t MsgId() {return 1884;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGetSignEverydayRwardReq();}
};
class SGetLevelRwardReq: public Msg {
public:
int32_t careerLevel;
int32_t level;
virtual inline int32_t msgId() const {return 1360;}
static int32_t MsgId() {return 1360;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGetLevelRwardReq();}
};
class STrumpActiveReq: public Msg {
public:
int32_t subtype;
int32_t id;
virtual inline int32_t msgId() const {return 1898;}
static int32_t MsgId() {return 1898;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STrumpActiveReq();}
};
class SCommitShengMissionReq: public Msg {
public:
int32_t missionId;
virtual inline int32_t msgId() const {return 4405;}
static int32_t MsgId() {return 4405;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCommitShengMissionReq();}
};
class SRequestShengMissionReq: public Msg {
public:
virtual inline int32_t msgId() const {return 4404;}
static int32_t MsgId() {return 4404;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRequestShengMissionReq();}
};
class STrumpUpgradeReq: public Msg {
public:
int32_t count;
virtual inline int32_t msgId() const {return 1899;}
static int32_t MsgId() {return 1899;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STrumpUpgradeReq();}
};
class SActiveTrumpSkillReq: public Msg {
public:
int32_t level;
virtual inline int32_t msgId() const {return 1992;}
static int32_t MsgId() {return 1992;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveTrumpSkillReq();}
};
class STrumpRequestMissionReq: public Msg {
public:
int32_t missionId;
virtual inline int32_t msgId() const {return 3507;}
static int32_t MsgId() {return 3507;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STrumpRequestMissionReq();}
};
class SUnlockTrumpReq: public Msg {
public:
virtual inline int32_t msgId() const {return 1965;}
static int32_t MsgId() {return 1965;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SUnlockTrumpReq();}
};
class SDressReq: public Msg {
public:
int32_t roleId;
int64_t uid;
virtual inline int32_t msgId() const {return 571;}
static int32_t MsgId() {return 571;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SDressReq();}
};
class SStrengthEquipReq: public Msg {
public:
int32_t roleId;
int32_t type;
int64_t uid;
virtual inline int32_t msgId() const {return 1889;}
static int32_t MsgId() {return 1889;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SStrengthEquipReq();}
};
class SOneKeyDressReq: public Msg {
public:
int32_t roleId;
int32_t type;
vector<int64_t> uids;
virtual inline int32_t msgId() const {return 2586;}
static int32_t MsgId() {return 2586;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SOneKeyDressReq();}
};
class SRecycleReq: public Msg {
public:
map<int64_t, int32_t> items;
virtual inline int32_t msgId() const {return 883;}
static int32_t MsgId() {return 883;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRecycleReq();}
};
class SLearnSkillReq: public Msg {
public:
int32_t roleId;
int32_t type;
int32_t skillId;
virtual inline int32_t msgId() const {return 1891;}
static int32_t MsgId() {return 1891;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SLearnSkillReq();}
};
class SAdvanceAwakenReq: public Msg {
public:
int32_t roleId;
int32_t type;
bool autoBuy;
virtual inline int32_t msgId() const {return 3106;}
static int32_t MsgId() {return 3106;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAdvanceAwakenReq();}
};
class SActiveAdvanceTargetReq: public Msg {
public:
int32_t type;
int32_t targetLevel;
virtual inline int32_t msgId() const {return 3340;}
static int32_t MsgId() {return 3340;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveAdvanceTargetReq();}
};
class SCardUpStarReq: public Msg {
public:
int64_t uid;
virtual inline int32_t msgId() const {return 1922;}
static int32_t MsgId() {return 1922;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCardUpStarReq();}
};
class SEquipZhanlingReq: public Msg {
public:
int64_t uid;
virtual inline int32_t msgId() const {return 1894;}
static int32_t MsgId() {return 1894;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEquipZhanlingReq();}
};
class SAdvanceZhanlingReq: public Msg {
public:
virtual inline int32_t msgId() const {return 1893;}
static int32_t MsgId() {return 1893;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAdvanceZhanlingReq();}
};
class SLearnZhanlingSkillReq: public Msg {
public:
int32_t skillId;
virtual inline int32_t msgId() const {return 3506;}
static int32_t MsgId() {return 3506;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SLearnZhanlingSkillReq();}
};
class SNearenmeyFightenemyReq: public Msg {
public:
int32_t playerId;
vector<Point> oldPoints;
virtual inline int32_t msgId() const {return 2152;}
static int32_t MsgId() {return 2152;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SNearenmeyFightenemyReq();}
};
class SNearenemyBacktoHangReq: public Msg {
public:
virtual inline int32_t msgId() const {return 2191;}
static int32_t MsgId() {return 2191;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SNearenemyBacktoHangReq();}
};
class SGetTopListReq: public Msg {
public:
int32_t toplistType;
virtual inline int32_t msgId() const {return 747;}
static int32_t MsgId() {return 747;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGetTopListReq();}
};
}

#endif