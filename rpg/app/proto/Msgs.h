#ifndef _MSGS_MSG_H_
#define _MSGS_MSG_H_
#include "Kernel.h"
#include "Dbs.h"
#include "MsgDef.h"
namespace msgs{
class SCloakSingle: public Msg {
public:
int32_t jingLianExp_;
int32_t jiLianLevel_;
int32_t jiLianStar_;
map<int32_t, int32_t> jiLianCount_;
virtual inline int32_t msgId() const {return 5060;}
static int32_t MsgId() {return 5060;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCloakSingle();}
};
class SCloakInfo: public Msg {
public:
map<int32_t, SCloakSingle> cloakMap_;
map<int32_t, bool> jiBan_;
map<int32_t, SCloakSingle> gloveMap_;
map<int32_t, bool> gloveJiBan_;
virtual inline int32_t msgId() const {return 5054;}
static int32_t MsgId() {return 5054;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCloakInfo();}
};
class SFightAttribute: public Msg {
public:
int64_t maxLife_;
int64_t attack_;
int64_t defence_;
int32_t wuxingHurt_;
int32_t wuxingDefense_;
int32_t hit_;
int32_t dodge_;
int32_t hitRate_;
int32_t dodgeRate_;
int32_t crit_;
int32_t critBreak_;
int32_t critRate_;
int32_t critBreakRate_;
int32_t critDmg_;
int32_t ignoreDef_;
int32_t ignoreDefBreak_;
int32_t luckRate_;
int32_t curseRate_;
int32_t inPower_;
int32_t inPowerRecover_;
int32_t inPowerDmgPer_;
int32_t dizzyRate_;
int32_t dizzyRateBreak_;
int32_t fixDmg_;
int32_t fixDmgDec_;
int32_t recoverLife_;
int32_t dmgAdd_;
int32_t dmgDec_;
int32_t dmgBossAdd_;
int32_t xpDmgAdd_;
int32_t xpDmgDec_;
int32_t zsDmgAdd_;
int32_t zsDmgDec_;
int32_t fsDmgAdd_;
int32_t fsDmgDec_;
int32_t dsDmgAdd_;
int32_t dsDmgDec_;
int32_t skillDmgAdd_;
int32_t skillDmgDec_;
int32_t pvpDmgAdd_;
int32_t pvpDmgDec_;
int32_t luckDmgAdd_;
int32_t luckDmgDec_;
int32_t armor_;
int32_t critDmgAdd_;
int32_t critDmgDec_;
int32_t zhuXianRate_;
int32_t zhuXian_;
int32_t zhuXianDec_;
int32_t maxAvaLife_;
int32_t avatarAttack_;
int64_t avaLifeTop_;
int32_t avaAttackTop_;
int32_t avaCritRate_;
int32_t avaCritBreakRate_;
int32_t avaCrit_;
int32_t avaCritBreak_;
int32_t comboRate_;
int32_t comboBreakRate_;
int32_t combo_;
int32_t comboBreak_;
int32_t maxMagic_;
int32_t attackSpeed_;
virtual inline int32_t msgId() const {return 319;}
static int32_t MsgId() {return 319;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFightAttribute();}
};
class SFightMiniAttribute: public Msg {
public:
int64_t attack_;
int64_t defence_;
int32_t ignoreDef_;
int32_t crit_;
int32_t critRate_;
int32_t dmgAdd_;
int32_t dmgDec_;
int32_t skillDmgAdd_;
int32_t skillDmgDec_;
int32_t dodgeRate_;
int32_t dodge_;
int32_t luckRate_;
int32_t curseRate_;
int32_t hit_;
int32_t wuxingHurt_;
int32_t wuxingDefense_;
int32_t hitRate_;
virtual inline int32_t msgId() const {return 2015;}
static int32_t MsgId() {return 2015;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFightMiniAttribute();}
};
class STeamData: public Msg {
public:
Identity teamId_;
string teamName_;
int16_t onlineNum_;
int16_t isLeader_;
int32_t copyId_;
virtual inline int32_t msgId() const {return 616;}
static int32_t MsgId() {return 616;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STeamData();}
};
class SGuildData: public Msg {
public:
Identity guildId_;
string guildName_;
int16_t position_;
virtual inline int32_t msgId() const {return 639;}
static int32_t MsgId() {return 639;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildData();}
};
class SMateData: public Msg {
public:
Identity mateId_;
string mateName_;
int64_t mateAttack_;
virtual inline int32_t msgId() const {return 4001;}
static int32_t MsgId() {return 4001;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMateData();}
};
class SRechargeRewardInfo: public Msg {
public:
map<int32_t, int32_t> rewardInfo_;
int32_t firstRecharge_;
virtual inline int32_t msgId() const {return 477;}
static int32_t MsgId() {return 477;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRechargeRewardInfo();}
};
class SRechargeInfo: public Msg {
public:
int32_t todayRecharge_;
int32_t totalRecharge_;
int32_t rechargeCount_;
int32_t maxDayRecharge_;
int32_t monthRecharge_;
int64_t lastRechargeDt_;
virtual inline int32_t msgId() const {return 480;}
static int32_t MsgId() {return 480;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRechargeInfo();}
};
class SDayRecharge: public Msg {
public:
map<int32_t, bool> target_;
virtual inline int32_t msgId() const {return 1928;}
static int32_t MsgId() {return 1928;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SDayRecharge();}
};
class SAccumDayReward: public Msg {
public:
int32_t cycle_;
int32_t day_;
map<int32_t, bool> rewardGot_;
virtual inline int32_t msgId() const {return 2199;}
static int32_t MsgId() {return 2199;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAccumDayReward();}
};
class SLimitRecharge: public Msg {
public:
int32_t day_;
int32_t index_;
int32_t recharge_;
int64_t endTime_;
map<int32_t, int32_t> notGots_;
virtual inline int32_t msgId() const {return 3234;}
static int32_t MsgId() {return 3234;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SLimitRecharge();}
};
class SPlayerWeekDayRecharge: public Msg {
public:
int32_t recharge_;
vector<int32_t> gots_;
virtual inline int32_t msgId() const {return 3368;}
static int32_t MsgId() {return 3368;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerWeekDayRecharge();}
};
class SInt: public Msg {
public:
int32_t value_;
virtual inline int32_t msgId() const {return 214;}
static int32_t MsgId() {return 214;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SInt();}
};
class SInts: public Msg {
public:
vector<int32_t> values_;
virtual inline int32_t msgId() const {return 215;}
static int32_t MsgId() {return 215;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SInts();}
};
class SLong: public Msg {
public:
int64_t value_;
virtual inline int32_t msgId() const {return 373;}
static int32_t MsgId() {return 373;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SLong();}
};
class SLongs: public Msg {
public:
vector<int64_t> values_;
virtual inline int32_t msgId() const {return 374;}
static int32_t MsgId() {return 374;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SLongs();}
};
class SString: public Msg {
public:
string value_;
virtual inline int32_t msgId() const {return 375;}
static int32_t MsgId() {return 375;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SString();}
};
class SStrings: public Msg {
public:
vector<string> values_;
virtual inline int32_t msgId() const {return 3819;}
static int32_t MsgId() {return 3819;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SStrings();}
};
class SIdentity: public Msg {
public:
Identity value_;
virtual inline int32_t msgId() const {return 376;}
static int32_t MsgId() {return 376;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SIdentity();}
};
class SIdentitys: public Msg {
public:
vector<Identity> values_;
virtual inline int32_t msgId() const {return 377;}
static int32_t MsgId() {return 377;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SIdentitys();}
};
class SIntIntPair: public Msg {
public:
int32_t first_;
int32_t second_;
virtual inline int32_t msgId() const {return 216;}
static int32_t MsgId() {return 216;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SIntIntPair();}
};
class SLongLongPair: public Msg {
public:
int64_t first_;
int64_t second_;
virtual inline int32_t msgId() const {return 5141;}
static int32_t MsgId() {return 5141;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SLongLongPair();}
};
class SPoint: public Msg {
public:
Point value_;
virtual inline int32_t msgId() const {return 1737;}
static int32_t MsgId() {return 1737;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPoint();}
};
class SPoints: public Msg {
public:
vector<Point> values_;
virtual inline int32_t msgId() const {return 1738;}
static int32_t MsgId() {return 1738;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPoints();}
};
class SItemAmount: public Msg {
public:
int32_t itemCode_;
int32_t itemNum_;
virtual inline int32_t msgId() const {return 1766;}
static int32_t MsgId() {return 1766;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SItemAmount();}
};
class SIntBoolMap: public Msg {
public:
map<int32_t, bool> maps_;
virtual inline int32_t msgId() const {return 4485;}
static int32_t MsgId() {return 4485;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SIntBoolMap();}
};
class SIntIntBoolMap: public Msg {
public:
map<int32_t, SIntBoolMap> maps_;
virtual inline int32_t msgId() const {return 4560;}
static int32_t MsgId() {return 4560;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SIntIntBoolMap();}
};
class SIntIntMap: public Msg {
public:
map<int32_t, int32_t> maps_;
virtual inline int32_t msgId() const {return 1904;}
static int32_t MsgId() {return 1904;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SIntIntMap();}
};
class SIntIntIntMap: public Msg {
public:
map<int32_t, map<int32_t, int32_t> > maps_;
virtual inline int32_t msgId() const {return 3343;}
static int32_t MsgId() {return 3343;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SIntIntIntMap();}
};
class SDateTime: public Msg {
public:
int64_t value_;
virtual inline int32_t msgId() const {return 2089;}
static int32_t MsgId() {return 2089;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SDateTime();}
};
class SBoolInt: public Msg {
public:
bool boolVal_;
int32_t intVal_;
virtual inline int32_t msgId() const {return 4359;}
static int32_t MsgId() {return 4359;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBoolInt();}
};
class SAttribute: public Msg {
public:
map<int16_t, map<int16_t, int64_t> > attr_;
virtual inline int32_t msgId() const {return 4374;}
static int32_t MsgId() {return 4374;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAttribute();}
};
class SReincarnInfo: public Msg {
public:
int32_t levelDelCount_;
map<int32_t, int32_t> itemDelCount_;
int32_t hadGotLevel_;
int32_t hadGotLevelCount_;
virtual inline int32_t msgId() const {return 1728;}
static int32_t MsgId() {return 1728;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SReincarnInfo();}
};
class SShengInfo: public Msg {
public:
vector<int32_t> shengLst_;
virtual inline int32_t msgId() const {return 4407;}
static int32_t MsgId() {return 4407;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SShengInfo();}
};
class SMiniPlayer: public Msg {
public:
Identity entityId_;
string name_;
int16_t sex_;
int16_t career_;
int16_t careerLevel_;
int16_t level_;
int16_t vipLevel_;
int32_t hangLevel_;
int64_t combat_;
int16_t camp_;
uint8_t online_;
map<int16_t, int32_t> ornaments_;
virtual inline int32_t msgId() const {return 1535;}
static int32_t MsgId() {return 1535;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMiniPlayer();}
};
class SPublicPlayer: public SMiniPlayer {
public:
map<int16_t, int32_t> entityShows_;
Identity teamId_;
string teamName_;
bool isLeader_;
int32_t teamCopyId_;
Identity guildId_;
string guildName_;
int16_t guildPos_;
Identity mateId_;
string mateName_;
int16_t oldServerId_;
virtual inline int32_t msgId() const {return 322;}
static int32_t MsgId() {return 322;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPublicPlayer();}
};
class SPublicPlayerEx: public SPublicPlayer {
public:
string gameChannel_;
string platformData_;
string loginIp_;
virtual inline int32_t msgId() const {return 2552;}
static int32_t MsgId() {return 2552;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPublicPlayerEx();}
};
class SPublicPlayerExt: public SPublicPlayerEx {
public:
int64_t gameDt_;
string username_;
virtual inline int32_t msgId() const {return 5067;}
static int32_t MsgId() {return 5067;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPublicPlayerExt();}
};
class SArenaWzInfo: public Msg {
public:
int32_t wzLevel_;
int32_t winCount_;
int32_t winTotalCount_;
int32_t totalCount_;
virtual inline int32_t msgId() const {return 1987;}
static int32_t MsgId() {return 1987;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SArenaWzInfo();}
};
class SArenaWzExtendInfo: public Msg {
public:
int32_t matchCount_;
int32_t buyCount_;
int64_t recoverTime_;
virtual inline int32_t msgId() const {return 2111;}
static int32_t MsgId() {return 2111;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SArenaWzExtendInfo();}
};
class SArenaWzResult: public Msg {
public:
int32_t result_;
int32_t level_;
int32_t addStar_;
map<int32_t, int32_t> reward_;
virtual inline int32_t msgId() const {return 1999;}
static int32_t MsgId() {return 1999;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SArenaWzResult();}
};
class SArenaWzResultFromGate: public Msg {
public:
bool isWin_;
bool sendClient_;
int16_t count_;
virtual inline int32_t msgId() const {return 4448;}
static int32_t MsgId() {return 4448;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SArenaWzResultFromGate();}
};
class SArenaMatchEnemy: public Msg {
public:
Identity entityId_;
string name_;
int16_t career_;
int16_t wzLevel_;
bool isRobot_;
virtual inline int32_t msgId() const {return 2255;}
static int32_t MsgId() {return 2255;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SArenaMatchEnemy();}
};
class SArenaTtSeason: public Msg {
public:
int32_t seaon_;
int64_t beginDt_;
virtual inline int32_t msgId() const {return 2829;}
static int32_t MsgId() {return 2829;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SArenaTtSeason();}
};
class SArenaTtInfo: public Msg {
public:
int32_t level_;
int32_t score_;
int32_t gongxun_;
virtual inline int32_t msgId() const {return 2830;}
static int32_t MsgId() {return 2830;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SArenaTtInfo();}
};
class SArenaTtExtendInfo: public Msg {
public:
int32_t matchCount_;
int32_t buyCount_;
int32_t todayCount_;
int32_t totalCount_;
int32_t winCount_;
int32_t getDailyHonor_;
vector<int32_t> joinReward_;
vector<int32_t> gongxunReward_;
virtual inline int32_t msgId() const {return 2831;}
static int32_t MsgId() {return 2831;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SArenaTtExtendInfo();}
};
class SArenaTtResult: public Msg {
public:
int32_t result_;
int32_t level_;
int32_t addScore_;
map<int32_t, int32_t> reward_;
virtual inline int32_t msgId() const {return 2832;}
static int32_t MsgId() {return 2832;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SArenaTtResult();}
};
class SArenaTtRankInfo: public Msg {
public:
int32_t level_;
int32_t score_;
int32_t rank_;
virtual inline int32_t msgId() const {return 3007;}
static int32_t MsgId() {return 3007;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SArenaTtRankInfo();}
};
class SArenaTtHistoryRank: public Msg {
public:
map<int32_t, SArenaTtRankInfo> hRank_;
virtual inline int32_t msgId() const {return 3003;}
static int32_t MsgId() {return 3003;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SArenaTtHistoryRank();}
};
class SArenaTopPlayer: public Msg {
public:
int32_t stage_;
int32_t pos_;
Identity entityId_;
string name_;
int32_t carerr_;
int64_t combat_;
map<int16_t, int32_t> ornaments_;
virtual inline int32_t msgId() const {return 3854;}
static int32_t MsgId() {return 3854;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SArenaTopPlayer();}
};
class SArenaTopArea: public Msg {
public:
vector<SArenaTopPlayer> players_;
virtual inline int32_t msgId() const {return 3855;}
static int32_t MsgId() {return 3855;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SArenaTopArea();}
};
class SArenaTopType: public Msg {
public:
map<int32_t, SArenaTopArea> areas_;
virtual inline int32_t msgId() const {return 3856;}
static int32_t MsgId() {return 3856;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SArenaTopType();}
};
class SArenaTopTotal: public Msg {
public:
int32_t stage_;
int32_t myType_;
int32_t myArea_;
map<int32_t, int32_t> total_;
virtual inline int32_t msgId() const {return 3857;}
static int32_t MsgId() {return 3857;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SArenaTopTotal();}
};
class SArenaTopYazhu: public Msg {
public:
int32_t pos_;
int32_t index_;
Identity entity_;
int32_t result_;
virtual inline int32_t msgId() const {return 3860;}
static int32_t MsgId() {return 3860;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SArenaTopYazhu();}
};
class SArenaTopInfo: public Msg {
public:
bool isSignUp_;
map<int32_t, map<int32_t, vector<SArenaTopYazhu> > > yazhu_;
virtual inline int32_t msgId() const {return 3861;}
static int32_t MsgId() {return 3861;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SArenaTopInfo();}
};
class SArenaTopResult: public Msg {
public:
Identity winId_;
Identity loseId_;
string name1_;
string name2_;
virtual inline int32_t msgId() const {return 3925;}
static int32_t MsgId() {return 3925;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SArenaTopResult();}
};
class SArenaTopResults: public Msg {
public:
int32_t stage_;
map<int32_t, map<int32_t, map<int32_t, SArenaTopResult> > > result_;
virtual inline int32_t msgId() const {return 3926;}
static int32_t MsgId() {return 3926;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SArenaTopResults();}
};
class SArenaTopSeaResult: public Msg {
public:
map<Identity, int32_t> seaResult_;
virtual inline int32_t msgId() const {return 3929;}
static int32_t MsgId() {return 3929;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SArenaTopSeaResult();}
};
class SFriend: public Msg {
public:
int32_t friendType_;
int32_t intimacy_;
int32_t lastChatTime_;
string openid_;
int32_t isBeCalled_;
int64_t offlineDt_;
msgs::SMiniPlayer miniPlayer_;
bool hadGroupFightTeam_;
virtual inline int32_t msgId() const {return 894;}
static int32_t MsgId() {return 894;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFriend();}
};
class SFriendList: public Msg {
public:
vector<SFriend> friends_;
virtual inline int32_t msgId() const {return 567;}
static int32_t MsgId() {return 567;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFriendList();}
};
class SFriendRemove: public Msg {
public:
Identity fromId_;
int32_t reason_;
virtual inline int32_t msgId() const {return 990;}
static int32_t MsgId() {return 990;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFriendRemove();}
};
class SFriendOnline: public Msg {
public:
Identity fromId_;
int32_t online_;
virtual inline int32_t msgId() const {return 993;}
static int32_t MsgId() {return 993;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFriendOnline();}
};
class SFriendDecline: public Msg {
public:
Identity entityId_;
string playerName_;
virtual inline int32_t msgId() const {return 4061;}
static int32_t MsgId() {return 4061;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFriendDecline();}
};
class SSendFlower: public Msg {
public:
msgs::SMiniPlayer fromPlayer_;
map<int32_t, int32_t> items_;
bool anonynous_;
virtual inline int32_t msgId() const {return 1130;}
static int32_t MsgId() {return 1130;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SSendFlower();}
};
class SSendFlowerBroadcast: public Msg {
public:
msgs::SMiniPlayer sender_;
msgs::SMiniPlayer receiver_;
int32_t itemId_;
int32_t itemNum_;
virtual inline int32_t msgId() const {return 3810;}
static int32_t MsgId() {return 3810;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SSendFlowerBroadcast();}
};
class SFriendZanData: public Msg {
public:
vector<int32_t> friendIds_;
int32_t expNum_;
virtual inline int32_t msgId() const {return 2945;}
static int32_t MsgId() {return 2945;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFriendZanData();}
};
class SFriendBeZan: public Msg {
public:
Identity entityId_;
string name_;
int64_t exp_;
virtual inline int32_t msgId() const {return 2943;}
static int32_t MsgId() {return 2943;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFriendBeZan();}
};
class SPlayerMrRight: public Msg {
public:
vector<dbs::TPlayerMrRight> mrRights_;
virtual inline int32_t msgId() const {return 4730;}
static int32_t MsgId() {return 4730;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerMrRight();}
};
class SPlayerLifeFairy: public Msg {
public:
vector<dbs::TPlayerLifeFairy> lifeFairies_;
virtual inline int32_t msgId() const {return 4876;}
static int32_t MsgId() {return 4876;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerLifeFairy();}
};
class SMeridiansSingle: public Msg {
public:
int32_t roleId_;
int32_t level_;
int32_t star_;
bool isActive_;
int32_t bless_;
virtual inline int32_t msgId() const {return 2020;}
static int32_t MsgId() {return 2020;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMeridiansSingle();}
};
class SMeridiansInfo: public Msg {
public:
map<int32_t, SMeridiansSingle> meriMap_;
virtual inline int32_t msgId() const {return 2021;}
static int32_t MsgId() {return 2021;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMeridiansInfo();}
};
class SOrnament: public Msg {
public:
int32_t id_;
int32_t star_;
virtual inline int32_t msgId() const {return 4803;}
static int32_t MsgId() {return 4803;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SOrnament();}
};
class SOrnamentList: public Msg {
public:
int32_t type_;
vector<SOrnament> ornamentList_;
virtual inline int32_t msgId() const {return 4782;}
static int32_t MsgId() {return 4782;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SOrnamentList();}
};
class SOrnamentAdd: public Msg {
public:
int32_t type_;
SOrnament ornament_;
virtual inline int32_t msgId() const {return 4783;}
static int32_t MsgId() {return 4783;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SOrnamentAdd();}
};
class SPlayerLevelReward: public Msg {
public:
map<int32_t, int32_t> rewardDict_;
map<int32_t, int32_t> numDict_;
virtual inline int32_t msgId() const {return 1466;}
static int32_t MsgId() {return 1466;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerLevelReward();}
};
class SAvatarAdvanceSingle: public Msg {
public:
int32_t level_;
int32_t star_;
int32_t bless_;
int32_t target_;
virtual inline int32_t msgId() const {return 4522;}
static int32_t MsgId() {return 4522;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAvatarAdvanceSingle();}
};
class SAvatarAdvanceInfo: public Msg {
public:
map<int32_t, SAvatarAdvanceSingle> maps_;
int32_t enterId_;
virtual inline int32_t msgId() const {return 4520;}
static int32_t MsgId() {return 4520;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAvatarAdvanceInfo();}
};
class SPlayerJiebaiInfo: public Msg {
public:
string jiebaiId_;
vector<msgs::SPublicPlayer> jiebaiList_;
virtual inline int32_t msgId() const {return 4954;}
static int32_t MsgId() {return 4954;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerJiebaiInfo();}
};
class SJiebaiYaoqing: public Msg {
public:
msgs::SMiniPlayer fromPlayer_;
virtual inline int32_t msgId() const {return 4955;}
static int32_t MsgId() {return 4955;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SJiebaiYaoqing();}
};
class SJiebaiHuifu: public Msg {
public:
Identity entityId_;
bool okey_;
virtual inline int32_t msgId() const {return 4956;}
static int32_t MsgId() {return 4956;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SJiebaiHuifu();}
};
class SJiebaiHuifuList: public Msg {
public:
vector<bool> huifuList_;
virtual inline int32_t msgId() const {return 4984;}
static int32_t MsgId() {return 4984;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SJiebaiHuifuList();}
};
class SJiebaiCheckResult: public Msg {
public:
Identity entityId_;
string playerName_;
bool isOnline_;
bool hasItems_;
bool canJiebai_;
virtual inline int32_t msgId() const {return 4969;}
static int32_t MsgId() {return 4969;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SJiebaiCheckResult();}
};
class SJiebaiCheckErrorList: public Msg {
public:
vector<SJiebaiCheckResult> errorList_;
virtual inline int32_t msgId() const {return 4970;}
static int32_t MsgId() {return 4970;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SJiebaiCheckErrorList();}
};
class SJiebaiSuccess: public Msg {
public:
vector<msgs::SPublicPlayer> playerList_;
virtual inline int32_t msgId() const {return 4973;}
static int32_t MsgId() {return 4973;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SJiebaiSuccess();}
};
class SJiebaiPrepareList: public Msg {
public:
vector<msgs::SPublicPlayer> playerList_;
vector<bool> huifuList_;
virtual inline int32_t msgId() const {return 4978;}
static int32_t MsgId() {return 4978;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SJiebaiPrepareList();}
};
class SJiebaiToupiao: public Msg {
public:
msgs::SMiniPlayer fromPlayer_;
msgs::SMiniPlayer toPlayer_;
virtual inline int32_t msgId() const {return 4998;}
static int32_t MsgId() {return 4998;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SJiebaiToupiao();}
};
class SJiebaiToupiaoResult: public Msg {
public:
Identity toEntityId_;
bool result_;
virtual inline int32_t msgId() const {return 4999;}
static int32_t MsgId() {return 4999;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SJiebaiToupiaoResult();}
};
class SPlayerTreasure: public Msg {
public:
int32_t type_;
int32_t drawNum_;
int32_t useFreeNum_;
int32_t todayNum_;
map<int32_t, int32_t> leftSelNums_;
bool hasDraw50_;
vector<int32_t> drewHis_;
map<int32_t, int32_t> hasGotTarget_;
int32_t useFree10num_;
virtual inline int32_t msgId() const {return 2621;}
static int32_t MsgId() {return 2621;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerTreasure();}
};
class SPlayerTreasureInfo: public Msg {
public:
vector<SPlayerTreasure> list_;
virtual inline int32_t msgId() const {return 2622;}
static int32_t MsgId() {return 2622;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerTreasureInfo();}
};
class STreasurePoolSuc: public Msg {
public:
int32_t drawPerType_;
int32_t drawGold_;
virtual inline int32_t msgId() const {return 4355;}
static int32_t MsgId() {return 4355;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STreasurePoolSuc();}
};
class SGuildTerritory: public Msg {
public:
int32_t level_;
bool hasReward_;
virtual inline int32_t msgId() const {return 1480;}
static int32_t MsgId() {return 1480;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildTerritory();}
};
class SGuild: public Msg {
public:
int32_t guildId_;
string guildName_;
string purpose_;
int32_t leaderId_;
string leaderName_;
int64_t totalCombat_;
int16_t level_;
int64_t joinCombat_;
int16_t joinVip_;
int16_t curMemberNum_;
int16_t maxMemberNum_;
int64_t createDt_;
int16_t joinListNum_;
int32_t guildFund_;
int64_t guildDt_;
int16_t position_;
int32_t contribute_;
int32_t totalFund_;
int32_t totalContribute_;
int16_t signNum_;
string buildings_;
bool isSign_;
int16_t donateGold_;
int16_t donateCoin_;
int32_t warehouseScore_;
map<int32_t, SGuildTerritory> territorys_;
int32_t curGuildBoss_;
int32_t guildBossMinGot_;
vector<int32_t> guildBossGotLst_;
int32_t xianCaoNum_;
bool guildWarSuccess_;
map<int32_t, int32_t> guildWarRankRewards_;
map<int32_t, int32_t> guildWarHasGots_;
map<int32_t, int32_t> requestGuilds_;
map<int32_t, int32_t> responseGuilds_;
virtual inline int32_t msgId() const {return 692;}
static int32_t MsgId() {return 692;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuild();}
};
class SGuildInfo: public Msg {
public:
int32_t guildId_;
string guildName_;
int32_t leaderId_;
string leaderName_;
int64_t totalCombat_;
int64_t joinCombat_;
int16_t joinVip_;
int16_t guildLevel_;
int16_t curMemberNum_;
int16_t maxMemberNum_;
bool isApply_;
int64_t createDt_;
virtual inline int32_t msgId() const {return 694;}
static int32_t MsgId() {return 694;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildInfo();}
};
class SGuildMember: public Msg {
public:
int32_t playerId_;
string name_;
int16_t sex_;
int16_t career_;
int16_t careerLevel_;
map<int16_t, int32_t> ornaments_;
int16_t level_;
int16_t vip_;
int64_t combat_;
int16_t position_;
int32_t totalContribute_;
int32_t offlineTime_;
bool hadGroupFightTeam_;
virtual inline int32_t msgId() const {return 641;}
static int32_t MsgId() {return 641;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildMember();}
};
class SGuildJoin: public Msg {
public:
int32_t playerId_;
string name_;
int16_t sex_;
int16_t career_;
int16_t careerLevel_;
int16_t level_;
int16_t vip_;
int64_t combat_;
int64_t joinDt_;
virtual inline int32_t msgId() const {return 642;}
static int32_t MsgId() {return 642;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildJoin();}
};
class SGuildUpdateData: public Msg {
public:
int32_t data1_;
int64_t data2_;
string data3_;
virtual inline int32_t msgId() const {return 707;}
static int32_t MsgId() {return 707;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildUpdateData();}
};
class SGuildUpdateJoinList: public Msg {
public:
int16_t operNum_;
int32_t playerId_;
Msg* join_;
bool topCombat_;
bool topVip_;
virtual inline int32_t msgId() const {return 1054;}
static int32_t MsgId() {return 1054;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildUpdateJoinList();}
};
class SGuildUpdateMemberNum: public Msg {
public:
int16_t totalNum_;
int16_t operNum_;
Identity memberId_;
Msg* member_;
virtual inline int32_t msgId() const {return 1027;}
static int32_t MsgId() {return 1027;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildUpdateMemberNum();}
};
class SGuildUpdateSetting: public Msg {
public:
int64_t joinCombat_;
int16_t joinVip_;
virtual inline int32_t msgId() const {return 792;}
static int32_t MsgId() {return 792;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildUpdateSetting();}
};
class SGuildUpdateMerge: public Msg {
public:
map<int32_t, int32_t> requestGuilds_;
map<int32_t, int32_t> responseGuilds_;
virtual inline int32_t msgId() const {return 3676;}
static int32_t MsgId() {return 3676;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildUpdateMerge();}
};
class SGuildMemberUpdateData: public Msg {
public:
int32_t data1_;
int32_t data2_;
virtual inline int32_t msgId() const {return 823;}
static int32_t MsgId() {return 823;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildMemberUpdateData();}
};
class SGuildMemberUpdateContribute: public Msg {
public:
int32_t contri_;
int32_t totalContri_;
int32_t totalFund_;
virtual inline int32_t msgId() const {return 2419;}
static int32_t MsgId() {return 2419;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildMemberUpdateContribute();}
};
class SGuildItem: public Msg {
public:
int32_t id_;
int32_t itemId_;
string itemExtend_;
virtual inline int32_t msgId() const {return 860;}
static int32_t MsgId() {return 860;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildItem();}
};
class SGuildItemRecord: public Msg {
public:
int32_t playerId_;
string playerName_;
int16_t position_;
int16_t oper_;
int32_t id_;
int32_t itemId_;
string itemExtend_;
int64_t recordDt_;
virtual inline int32_t msgId() const {return 862;}
static int32_t MsgId() {return 862;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildItemRecord();}
};
class SAddGuildMemberContribute: public Msg {
public:
int32_t value_;
virtual inline int32_t msgId() const {return 1990;}
static int32_t MsgId() {return 1990;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAddGuildMemberContribute();}
};
class SGuildMemberUpdateGuildBoss: public Msg {
public:
int32_t curGuildBoss_;
int32_t guildBossMinGot_;
vector<int32_t> guildBossGotList_;
virtual inline int32_t msgId() const {return 2061;}
static int32_t MsgId() {return 2061;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildMemberUpdateGuildBoss();}
};
class SGuildMiniInfo: public Msg {
public:
Identity guildId_;
string guildName_;
Identity leaderId_;
string leaderName_;
virtual inline int32_t msgId() const {return 2173;}
static int32_t MsgId() {return 2173;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildMiniInfo();}
};
class SZhanqi: public Msg {
public:
int32_t level_;
virtual inline int32_t msgId() const {return 4064;}
static int32_t MsgId() {return 4064;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SZhanqi();}
};
class SZhanqiInfo: public Msg {
public:
int32_t puton_;
map<int32_t, SZhanqi> zhanqis_;
int32_t tryId_;
int64_t deadDt_;
virtual inline int32_t msgId() const {return 4065;}
static int32_t MsgId() {return 4065;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SZhanqiInfo();}
};
class SZhanqiFightData: public Msg {
public:
int32_t engineNum_;
int32_t engineSpeed_;
int32_t engineHurt_;
virtual inline int32_t msgId() const {return 4122;}
static int32_t MsgId() {return 4122;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SZhanqiFightData();}
};
class SPlayerMissionList: public Msg {
public:
vector<dbs::TPlayerMission> missions_;
virtual inline int32_t msgId() const {return 421;}
static int32_t MsgId() {return 421;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerMissionList();}
};
class SMissionMonster: public Msg {
public:
int32_t monsterId_;
virtual inline int32_t msgId() const {return 443;}
static int32_t MsgId() {return 443;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMissionMonster();}
};
class SRoundMission: public Msg {
public:
int32_t type_;
int32_t round_;
int32_t missionId_;
int32_t extraRound_;
int32_t lotteryTimes_;
int32_t reward_;
virtual inline int32_t msgId() const {return 1178;}
static int32_t MsgId() {return 1178;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRoundMission();}
};
class SRoundMissionList: public Msg {
public:
vector<SRoundMission> list_;
virtual inline int32_t msgId() const {return 1186;}
static int32_t MsgId() {return 1186;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRoundMissionList();}
};
class SMissionMonsterPlan: public Msg {
public:
map<int32_t, int32_t> monsterPlans_;
virtual inline int32_t msgId() const {return 1334;}
static int32_t MsgId() {return 1334;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMissionMonsterPlan();}
};
class SEntityUpdate: public Msg {
public:
Identity entityId_;
int16_t updateType_;
vector<int64_t> updateData_;
string updateStr_;
virtual inline int32_t msgId() const {return 284;}
static int32_t MsgId() {return 284;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEntityUpdate();}
};
class SUpdateDiffAttr: public Msg {
public:
int32_t roleId_;
int64_t combat_;
map<int16_t, int64_t> diffAttr_;
map<int16_t, int64_t> diffCopyAttr_;
virtual inline int32_t msgId() const {return 1719;}
static int32_t MsgId() {return 1719;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SUpdateDiffAttr();}
};
class SUpdateTotalAttrDiff: public Msg {
public:
map<int16_t, int64_t> attr_;
virtual inline int32_t msgId() const {return 930;}
static int32_t MsgId() {return 930;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SUpdateTotalAttrDiff();}
};
class SEntityUpdateEntityShows: public Msg {
public:
Identity entityId_;
map<int16_t, int32_t> shows_;
virtual inline int32_t msgId() const {return 956;}
static int32_t MsgId() {return 956;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEntityUpdateEntityShows();}
};
class SEntityUpdateEntityValues: public Msg {
public:
Identity entityId_;
map<int16_t, int32_t> values_;
virtual inline int32_t msgId() const {return 1332;}
static int32_t MsgId() {return 1332;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEntityUpdateEntityValues();}
};
class SEntityUpdateExtraAttr: public Msg {
public:
int32_t roleId_;
map<int16_t, int64_t> attrMap_;
virtual inline int32_t msgId() const {return 2691;}
static int32_t MsgId() {return 2691;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEntityUpdateExtraAttr();}
};
class SEntityTotalAttr: public Msg {
public:
int32_t code_;
Identity entityId_;
msgs::SFightAttribute totalAttr_;
virtual inline int32_t msgId() const {return 2976;}
static int32_t MsgId() {return 2976;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEntityTotalAttr();}
};
class SBuffInfo: public Msg {
public:
int32_t buffId_;
int32_t roleId_;
int32_t overlay_;
int32_t count_;
int64_t value_;
int64_t endDt_;
int64_t extend_;
virtual inline int32_t msgId() const {return 281;}
static int32_t MsgId() {return 281;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBuffInfo();}
};
class SFightData: public Msg {
public:
Identity entityId_;
string name_;
int16_t sex_;
int16_t career_;
int16_t careerLevel_;
int64_t combat_;
int16_t status_;
int64_t statusEnd_;
Point spacePos_;
int16_t direction_;
int16_t speed_;
int16_t bodySize_;
int16_t camp_;
int16_t force_;
int16_t level_;
int32_t vipLevel_;
int64_t curLife_;
int64_t inPower_;
int32_t avaLife_;
int32_t curMagic_;
int16_t fightMode_;
int32_t touxian_;
int32_t statusMask_;
bool isRide_;
Identity warHorse_;
bool isHide_;
map<int16_t, int32_t> entityShows_;
map<int16_t, int32_t> entityValues_;
msgs::SFightAttribute fightAttr_;
msgs::SFightAttribute totalAttr_;
map<int16_t, int64_t> copyAttr_;
vector<int32_t> skills_;
vector<SBuffInfo> buffs_;
vector<int32_t> runes_;
Msg* teamData_;
Msg* guildData_;
virtual inline int32_t msgId() const {return 282;}
static int32_t MsgId() {return 282;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFightData();}
};
class SFightPlayer: public Msg {
public:
Identity entityId_;
int16_t cellLine_;
int32_t spaceId_;
Point spacePos_;
int32_t copyCode_;
string name_;
int16_t career_;
int16_t careerLevel_;
int16_t camp_;
int16_t level_;
int32_t vipLevel_;
map<int16_t, int32_t> ornaments_;
int64_t combat_;
int16_t fightMode_;
int32_t hangLevel_;
int16_t nuqi_;
int16_t nuqiRecover_;
int32_t zhanling_;
int32_t godRingAttackLevel_;
int32_t godRingDefenseLevel_;
Msg* teamData_;
Msg* guildData_;
Msg* mateData_;
vector<SFightData> fightDatas_;
map<int32_t, int32_t> dragonSoulAttr_;
map<int32_t, int32_t> addCopyDropRate_;
vector<int32_t> flyUpSkills_;
int32_t zhanqiAtkPer_;
int32_t zhanqiHurtPer_;
int32_t officialId_;
int32_t crossOfficialId_;
string jiebaiId_;
bool isBeCaller_;
map<int32_t, int32_t> roleZhanWei_;
int16_t oldServerId_;
virtual inline int32_t msgId() const {return 1697;}
static int32_t MsgId() {return 1697;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFightPlayer();}
};
class SDisplayData: public Msg {
public:
Identity entityId_;
string name_;
int16_t status_;
int64_t statusEnd_;
int32_t spaceId_;
Point spacePos_;
int32_t copyCode_;
int16_t direction_;
int16_t speed_;
virtual inline int32_t msgId() const {return 283;}
static int32_t MsgId() {return 283;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SDisplayData();}
};
class SPlayerSkillInfo: public Msg {
public:
vector<dbs::TPlayerSkill> skills_;
virtual inline int32_t msgId() const {return 311;}
static int32_t MsgId() {return 311;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerSkillInfo();}
};
class SUpdateSkill: public Msg {
public:
vector<dbs::TPlayerSkill> skills_;
uint8_t oper_;
virtual inline int32_t msgId() const {return 312;}
static int32_t MsgId() {return 312;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SUpdateSkill();}
};
class SFightUpdate: public Msg {
public:
int16_t updateType_;
vector<int64_t> updateData_;
virtual inline int32_t msgId() const {return 1918;}
static int32_t MsgId() {return 1918;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFightUpdate();}
};
class SBeginFight: public Msg {
public:
int16_t attackId_;
int32_t skillId_;
Identity fromEntity_;
Point centerPoint_;
vector<Identity> toEntitys_;
vector<SFightUpdate> propertyUpdates_;
virtual inline int32_t msgId() const {return 313;}
static int32_t MsgId() {return 313;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBeginFight();}
};
class SSkillCast: public Msg {
public:
SBeginFight beginFight_;
int64_t endTime_;
virtual inline int32_t msgId() const {return 1122;}
static int32_t MsgId() {return 1122;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SSkillCast();}
};
class SSkillStopLead: public Msg {
public:
int32_t skillId_;
int32_t series_;
int64_t cdTime_;
virtual inline int32_t msgId() const {return 1125;}
static int32_t MsgId() {return 1125;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SSkillStopLead();}
};
class SBeatMove: public Msg {
public:
Point fromPoint_;
Point toPoint_;
virtual inline int32_t msgId() const {return 1788;}
static int32_t MsgId() {return 1788;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBeatMove();}
};
class SFightInfo: public Msg {
public:
Identity fromEntityId_;
int32_t skillId_;
bool isFirst_;
int32_t attackId_;
Msg* extra_;
Msg* extraAttrs_;
virtual inline int32_t msgId() const {return 380;}
static int32_t MsgId() {return 380;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFightInfo();}
};
class SDoFight: public Msg {
public:
int16_t attackId_;
int32_t skillId_;
Identity fromEntity_;
Identity entity_;
vector<SFightUpdate> propertyUpdates_;
virtual inline int32_t msgId() const {return 314;}
static int32_t MsgId() {return 314;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SDoFight();}
};
class SDoFights: public Msg {
public:
vector<SDoFight> doFights_;
virtual inline int32_t msgId() const {return 315;}
static int32_t MsgId() {return 315;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SDoFights();}
};
class SPlayerBuffInfo: public Msg {
public:
vector<msgs::SBuffInfo> buffs_;
virtual inline int32_t msgId() const {return 316;}
static int32_t MsgId() {return 316;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerBuffInfo();}
};
class SUpdateBuff: public Msg {
public:
uint8_t op_;
vector<msgs::SBuffInfo> buffs_;
virtual inline int32_t msgId() const {return 317;}
static int32_t MsgId() {return 317;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SUpdateBuff();}
};
class SBroadBuffInfo: public Msg {
public:
SUpdateBuff buffs_;
Identity toEntityId_;
Identity fromEntityId_;
virtual inline int32_t msgId() const {return 318;}
static int32_t MsgId() {return 318;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBroadBuffInfo();}
};
class SUpdateSkillCd: public Msg {
public:
int32_t roleId_;
map<int32_t, int32_t> updateCds_;
map<int32_t, int32_t> updateCdPers_;
virtual inline int32_t msgId() const {return 1907;}
static int32_t MsgId() {return 1907;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SUpdateSkillCd();}
};
class SRoleUpdateRune: public Msg {
public:
uint8_t op_;
int32_t roleId_;
vector<int32_t> runes_;
virtual inline int32_t msgId() const {return 1985;}
static int32_t MsgId() {return 1985;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRoleUpdateRune();}
};
class SEntityPoint: public Msg {
public:
Identity entityId_;
Point point_;
virtual inline int32_t msgId() const {return 2422;}
static int32_t MsgId() {return 2422;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEntityPoint();}
};
class SCleanSkill: public Msg {
public:
int16_t skillUid_;
virtual inline int32_t msgId() const {return 2955;}
static int32_t MsgId() {return 2955;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCleanSkill();}
};
class SPlayerGodMagicSkill: public Msg {
public:
int32_t roleId_;
int32_t selectType_;
virtual inline int32_t msgId() const {return 5017;}
static int32_t MsgId() {return 5017;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerGodMagicSkill();}
};
class SChildInfo: public Msg {
public:
map<int32_t, bool> unlockMap_;
map<int32_t, int32_t> childMap_;
int32_t curFightChild_;
int64_t tryEndTime_;
int32_t tryEnterId_;
virtual inline int32_t msgId() const {return 3863;}
static int32_t MsgId() {return 3863;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SChildInfo();}
};
class SFeiJianInfo: public Msg {
public:
vector<dbs::TPlayerFeiJian> list_;
virtual inline int32_t msgId() const {return 5421;}
static int32_t MsgId() {return 5421;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFeiJianInfo();}
};
class STurntableSingle: public Msg {
public:
map<int32_t, bool> recordMap_;
int32_t count_;
int32_t group_;
int32_t totalCount_;
virtual inline int32_t msgId() const {return 3266;}
static int32_t MsgId() {return 3266;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STurntableSingle();}
};
class STurntableInfo: public Msg {
public:
map<int32_t, STurntableSingle> turntableMap_;
virtual inline int32_t msgId() const {return 3263;}
static int32_t MsgId() {return 3263;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STurntableInfo();}
};
class STurntableRecordSingle: public Msg {
public:
string playerName_;
int32_t itemId_;
int32_t itemCount_;
virtual inline int32_t msgId() const {return 3277;}
static int32_t MsgId() {return 3277;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STurntableRecordSingle();}
};
class STurntableRecord: public Msg {
public:
vector<STurntableRecordSingle> records_;
virtual inline int32_t msgId() const {return 3278;}
static int32_t MsgId() {return 3278;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STurntableRecord();}
};
class STeamMember: public Msg {
public:
Identity entityId_;
Identity mirrorId_;
string name_;
int16_t sex_;
int16_t career_;
int16_t careerLevel_;
int16_t level_;
int64_t combat_;
int32_t spaceId_;
map<int16_t, int32_t> ornaments_;
map<int16_t, int32_t> entityShows_;
virtual inline int32_t msgId() const {return 485;}
static int32_t MsgId() {return 485;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STeamMember();}
};
class SMiniTeamMember: public Msg {
public:
Identity entityId_;
string name_;
int16_t sex_;
int16_t career_;
int16_t careerLevel_;
int16_t level_;
int64_t combat_;
map<int16_t, int32_t> ornaments_;
virtual inline int32_t msgId() const {return 484;}
static int32_t MsgId() {return 484;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMiniTeamMember();}
};
class STeam: public Msg {
public:
Identity teamId_;
string teamName_;
Identity leaderId_;
int32_t copyId_;
vector<STeamMember> members_;
Identity target_;
vector<int32_t> targetList_;
int16_t needLevel_;
bool autoJoin_;
bool isMatching_;
virtual inline int32_t msgId() const {return 487;}
static int32_t MsgId() {return 487;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STeam();}
};
class SMiniTeam: public Msg {
public:
Identity teamId_;
string teamName_;
SMiniTeamMember leader_;
int32_t memberNum_;
Identity target_;
vector<int32_t> targetList_;
virtual inline int32_t msgId() const {return 488;}
static int32_t MsgId() {return 488;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMiniTeam();}
};
class STeamMemberUpdateData: public Msg {
public:
Identity entityId_;
vector<int64_t> updateData_;
string updateStr_;
virtual inline int32_t msgId() const {return 494;}
static int32_t MsgId() {return 494;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STeamMemberUpdateData();}
};
class STeamUpdateLeader: public Msg {
public:
Identity leaderId_;
string name_;
virtual inline int32_t msgId() const {return 531;}
static int32_t MsgId() {return 531;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STeamUpdateLeader();}
};
class STeamUpdateSetting: public Msg {
public:
int16_t needLevel_;
bool autoJoin_;
Identity target_;
vector<int32_t> targetList_;
virtual inline int32_t msgId() const {return 1034;}
static int32_t MsgId() {return 1034;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STeamUpdateSetting();}
};
class STeamUpdateTarget: public Msg {
public:
Identity target_;
vector<int32_t> targetList_;
virtual inline int32_t msgId() const {return 1032;}
static int32_t MsgId() {return 1032;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STeamUpdateTarget();}
};
class STeamJoinData: public Msg {
public:
Identity entityId_;
string name_;
int16_t sex_;
int16_t career_;
int16_t careerLevel_;
int16_t level_;
int64_t combat_;
int64_t operDt_;
virtual inline int32_t msgId() const {return 556;}
static int32_t MsgId() {return 556;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STeamJoinData();}
};
class STeamJoinList: public Msg {
public:
vector<STeamJoinData> list_;
virtual inline int32_t msgId() const {return 557;}
static int32_t MsgId() {return 557;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STeamJoinList();}
};
class STeamVoteStart: public Msg {
public:
int32_t copyCode_;
Identity entityId_;
int32_t touxianId_;
int32_t titleId_;
virtual inline int32_t msgId() const {return 1080;}
static int32_t MsgId() {return 1080;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STeamVoteStart();}
};
class STeamVoteAnswer: public Msg {
public:
int32_t copyCode_;
bool agree_;
Identity entityId_;
int32_t touxianId_;
int32_t titleId_;
virtual inline int32_t msgId() const {return 1081;}
static int32_t MsgId() {return 1081;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STeamVoteAnswer();}
};
class STeamInviteBroadcast: public Msg {
public:
Identity teamId_;
int32_t copyCode_;
int32_t needLevel_;
virtual inline int32_t msgId() const {return 1148;}
static int32_t MsgId() {return 1148;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STeamInviteBroadcast();}
};
class STeamMemberCopyCheck: public Msg {
public:
int32_t errorCode_;
string errorWhat_;
Identity entityId_;
int32_t spaceId_;
int32_t enterRemainNum_;
int32_t assistRemainNum_;
int32_t career_;
virtual inline int32_t msgId() const {return 1183;}
static int32_t MsgId() {return 1183;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STeamMemberCopyCheck();}
};
class SYunGou: public Msg {
public:
int32_t index_;
int32_t hadBuyCount_;
int32_t myBuyCount_;
virtual inline int32_t msgId() const {return 4299;}
static int32_t MsgId() {return 4299;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SYunGou();}
};
class SYunGouInfo: public Msg {
public:
int32_t status_;
int64_t openDt_;
vector<SYunGou> items_;
virtual inline int32_t msgId() const {return 4300;}
static int32_t MsgId() {return 4300;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SYunGouInfo();}
};
class SYunGouWin: public Msg {
public:
string winName_;
int32_t winCount_;
int32_t buyCount_;
virtual inline int32_t msgId() const {return 4314;}
static int32_t MsgId() {return 4314;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SYunGouWin();}
};
class SYunGouRecord: public Msg {
public:
Identity entityId_;
string name_;
int32_t itemId_;
int32_t itemNum_;
int32_t winNum_;
virtual inline int32_t msgId() const {return 4301;}
static int32_t MsgId() {return 4301;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SYunGouRecord();}
};
class SYunGouRecords: public Msg {
public:
int64_t openTime_;
vector<SYunGouRecord> records_;
virtual inline int32_t msgId() const {return 4302;}
static int32_t MsgId() {return 4302;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SYunGouRecords();}
};
class SGhostMazeInfo: public Msg {
public:
int32_t activeId_;
int32_t freeCount_;
int32_t resetCount_;
int32_t curPos_;
vector<msgs::SIntIntPair> rewards_;
virtual inline int32_t msgId() const {return 4833;}
static int32_t MsgId() {return 4833;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGhostMazeInfo();}
};
class SGhostMazeRecord: public Msg {
public:
string playerName_;
int32_t itemId_;
int32_t itemNum_;
virtual inline int32_t msgId() const {return 4837;}
static int32_t MsgId() {return 4837;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGhostMazeRecord();}
};
class SGhostMazeRecords: public Msg {
public:
vector<SGhostMazeRecord> records_;
virtual inline int32_t msgId() const {return 4834;}
static int32_t MsgId() {return 4834;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGhostMazeRecords();}
};
class SMineTreasureInfo: public Msg {
public:
int32_t activeId_;
int32_t freeTimes_;
vector<msgs::SIntIntPair> recordMap_;
map<int32_t, int32_t> rewardlist_;
virtual inline int32_t msgId() const {return 5257;}
static int32_t MsgId() {return 5257;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMineTreasureInfo();}
};
class SFlyingUpInfo: public Msg {
public:
int32_t round_;
map<int32_t, bool> commitMap_;
map<int32_t, int32_t> flyingUpMap_;
vector<int32_t> curFightVec_;
int64_t startTime_;
int64_t countDownTime_;
int32_t buyTime_;
bool isCountDown_;
int32_t buyEnterNum_;
vector<bool> lockVec_;
map<int32_t, int32_t> flyingUpGodGrid_;
map<int32_t, int32_t> talent_;
int64_t tryEndTime_;
virtual inline int32_t msgId() const {return 3019;}
static int32_t MsgId() {return 3019;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFlyingUpInfo();}
};
class SFightFlyingUp: public Msg {
public:
int64_t commonCD_;
map<int32_t, int64_t> flyingUpCD_;
int64_t stCommonCD_;
map<int32_t, int64_t> stFlyingUpCD_;
virtual inline int32_t msgId() const {return 3760;}
static int32_t MsgId() {return 3760;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFightFlyingUp();}
};
class SCosmosInfo: public Msg {
public:
map<int32_t, int32_t> cosmosMap_;
map<int32_t, bool> commitMissions_;
int32_t curRole_;
map<int32_t, int32_t> guangWuMap_;
map<int32_t, int32_t> guangWuBless_;
virtual inline int32_t msgId() const {return 2433;}
static int32_t MsgId() {return 2433;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCosmosInfo();}
};
class SPlayerCopyDataList: public Msg {
public:
vector<dbs::TPlayerCopyData> copyDatas_;
virtual inline int32_t msgId() const {return 762;}
static int32_t MsgId() {return 762;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerCopyDataList();}
};
class SPlayerCopyDataUpdateNum: public Msg {
public:
int32_t copyGroup_;
int32_t enterNum_;
int32_t assistNum_;
int32_t getBackNum_;
int32_t totalEnterNum_;
int32_t completeNum_;
int32_t totalCompleteNum_;
virtual inline int32_t msgId() const {return 1166;}
static int32_t MsgId() {return 1166;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerCopyDataUpdateNum();}
};
class SCopyTimeInfo: public Msg {
public:
int32_t copyCode_;
int64_t startDt_;
int64_t endDt_;
virtual inline int32_t msgId() const {return 782;}
static int32_t MsgId() {return 782;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCopyTimeInfo();}
};
class SEnterCopy: public Msg {
public:
int32_t copyCode_;
virtual inline int32_t msgId() const {return 1153;}
static int32_t MsgId() {return 1153;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEnterCopy();}
};
class SCompleteCopy: public Msg {
public:
int32_t copyCode_;
int32_t costCount_;
bool failed_;
virtual inline int32_t msgId() const {return 1154;}
static int32_t MsgId() {return 1154;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteCopy();}
};
class SNotifyEnterCopy: public Msg {
public:
int32_t copyCode_;
virtual inline int32_t msgId() const {return 985;}
static int32_t MsgId() {return 985;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SNotifyEnterCopy();}
};
class SCompleteExpCopy: public SCompleteCopy {
public:
int64_t lastTotalExp_;
int64_t singleTotalExp_;
int32_t monsterKilledNum_;
int32_t extraAddon_;
virtual inline int32_t msgId() const {return 975;}
static int32_t MsgId() {return 975;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteExpCopy();}
};
class SExpCopyInfo: public Msg {
public:
int32_t copyCode_;
int32_t count_;
int64_t totalExp_;
int16_t coinNum_;
int16_t goldNum_;
virtual inline int32_t msgId() const {return 987;}
static int32_t MsgId() {return 987;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SExpCopyInfo();}
};
class STrialBossResult: public SCompleteCopy {
public:
int32_t evaluation_;
bool isPromot_;
int32_t bestEvaluation_;
bool isAssist_;
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 1144;}
static int32_t MsgId() {return 1144;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STrialBossResult();}
};
class SCompleteEquipCopy: public SCompleteCopy {
public:
int32_t evaluation_;
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 1146;}
static int32_t MsgId() {return 1146;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteEquipCopy();}
};
class STrialBossLeftInfo: public Msg {
public:
int32_t bossCode_;
int32_t num_;
int32_t round_;
int64_t roundEndTime_;
int32_t evaluation_;
virtual inline int32_t msgId() const {return 1156;}
static int32_t MsgId() {return 1156;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STrialBossLeftInfo();}
};
class SRefineTargetReward: public Msg {
public:
int32_t copyCode_;
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 1191;}
static int32_t MsgId() {return 1191;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRefineTargetReward();}
};
class SRefineCopyInfo: public Msg {
public:
int32_t copyCode_;
int32_t score_;
int32_t layer_;
virtual inline int32_t msgId() const {return 1193;}
static int32_t MsgId() {return 1193;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRefineCopyInfo();}
};
class SCompleteRefineCopy: public SCompleteCopy {
public:
int32_t score_;
int32_t completeTime_;
int32_t layer_;
map<int32_t, int32_t> rewards_;
bool isNewRecord_;
virtual inline int32_t msgId() const {return 1195;}
static int32_t MsgId() {return 1195;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteRefineCopy();}
};
class SCompleteBeingGodCopy: public SCompleteCopy {
public:
int32_t masterFloor_;
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 1311;}
static int32_t MsgId() {return 1311;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteBeingGodCopy();}
};
class SBeingGodCopyInfo: public Msg {
public:
int32_t copyCode_;
int32_t floor_;
int32_t score_;
int32_t gotScore_;
int32_t num_;
virtual inline int32_t msgId() const {return 1312;}
static int32_t MsgId() {return 1312;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBeingGodCopyInfo();}
};
class SBeingGodUpdateData: public Msg {
public:
int32_t score_;
int32_t num_;
string byName_;
virtual inline int32_t msgId() const {return 1328;}
static int32_t MsgId() {return 1328;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBeingGodUpdateData();}
};
class SBeingGodRankItem: public Msg {
public:
Identity entityId_;
string name_;
int32_t num_;
int32_t maxKillNum_;
virtual inline int32_t msgId() const {return 1313;}
static int32_t MsgId() {return 1313;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBeingGodRankItem();}
};
class SBeingGodRankList: public Msg {
public:
vector<SBeingGodRankItem> list_;
virtual inline int32_t msgId() const {return 1314;}
static int32_t MsgId() {return 1314;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBeingGodRankList();}
};
class SBeingGodContinuousKill: public Msg {
public:
Identity entityId_;
string name_;
int16_t career_;
int16_t killNum_;
virtual inline int32_t msgId() const {return 2872;}
static int32_t MsgId() {return 2872;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBeingGodContinuousKill();}
};
class SCompleteExpeditionCopy: public SCompleteCopy {
public:
int32_t id_;
int32_t idx_;
int32_t completeTime_;
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 1302;}
static int32_t MsgId() {return 1302;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteExpeditionCopy();}
};
class SExpeditionCopyInfo: public Msg {
public:
int32_t copyCode_;
map<int32_t, int32_t> killedBoss_;
virtual inline int32_t msgId() const {return 1303;}
static int32_t MsgId() {return 1303;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SExpeditionCopyInfo();}
};
class SEliteBossLeftInfo: public Msg {
public:
int32_t bossCode_;
int64_t roundEndTime_;
int32_t evaluation_;
int32_t layer_;
virtual inline int32_t msgId() const {return 1476;}
static int32_t MsgId() {return 1476;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEliteBossLeftInfo();}
};
class SEliteBossResult: public SCompleteCopy {
public:
int32_t evaluation_;
int32_t layer_;
bool isPromot_;
int32_t bestEvaluation_;
int32_t bestLayer_;
bool isAssist_;
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 1477;}
static int32_t MsgId() {return 1477;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEliteBossResult();}
};
class SMagicRingsCopy: public SCompleteCopy {
public:
map<int32_t, int32_t> rewards_;
int32_t completeTime_;
virtual inline int32_t msgId() const {return 1496;}
static int32_t MsgId() {return 1496;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMagicRingsCopy();}
};
class SCompleteMagicTowerCopy: public SCompleteCopy {
public:
int32_t completeTime_;
int32_t layer_;
map<int32_t, int32_t> rewards_;
bool isQuick_;
bool isDoubleExp_;
virtual inline int32_t msgId() const {return 1566;}
static int32_t MsgId() {return 1566;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteMagicTowerCopy();}
};
class SMagicTowerCopyInfo: public Msg {
public:
int32_t layer_;
map<int32_t, int32_t> remainBoss_;
virtual inline int32_t msgId() const {return 1587;}
static int32_t MsgId() {return 1587;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMagicTowerCopyInfo();}
};
class SLotteryMagicTower: public Msg {
public:
int32_t round_;
map<int32_t, bool> rewardMap_;
int32_t remainCount_;
virtual inline int32_t msgId() const {return 2051;}
static int32_t MsgId() {return 2051;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SLotteryMagicTower();}
};
class SCompleteMaterialCopy: public SCompleteCopy {
public:
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 1821;}
static int32_t MsgId() {return 1821;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteMaterialCopy();}
};
class SMaterialCopyInfo: public Msg {
public:
virtual inline int32_t msgId() const {return 1822;}
static int32_t MsgId() {return 1822;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMaterialCopyInfo();}
};
class SEnterReincarnCopy: public SEnterCopy {
public:
virtual inline int32_t msgId() const {return 1830;}
static int32_t MsgId() {return 1830;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEnterReincarnCopy();}
};
class SCompleteReincarnCopy: public SCompleteCopy {
public:
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 1831;}
static int32_t MsgId() {return 1831;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteReincarnCopy();}
};
class SReincarnCopyBossKill: public Msg {
public:
map<int32_t, int32_t> bossKill_;
virtual inline int32_t msgId() const {return 1924;}
static int32_t MsgId() {return 1924;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SReincarnCopyBossKill();}
};
class SEnterSpecialRingCopy: public SEnterCopy {
public:
virtual inline int32_t msgId() const {return 1940;}
static int32_t MsgId() {return 1940;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEnterSpecialRingCopy();}
};
class SCompleteSpecialRingCopy: public SCompleteCopy {
public:
virtual inline int32_t msgId() const {return 1941;}
static int32_t MsgId() {return 1941;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteSpecialRingCopy();}
};
class SCompleteBonfireCopy: public SCompleteCopy {
public:
virtual inline int32_t msgId() const {return 1961;}
static int32_t MsgId() {return 1961;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteBonfireCopy();}
};
class SBonfireCopyInfo: public Msg {
public:
int32_t gatherCount_;
int32_t woodNum_;
int32_t answerCount_;
map<int32_t, int32_t> totalRewards_;
virtual inline int32_t msgId() const {return 1962;}
static int32_t MsgId() {return 1962;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBonfireCopyInfo();}
};
class SBonfireCopyQuestion: public Msg {
public:
int16_t stage_;
int64_t nextStateTime_;
int32_t questionId_;
vector<int16_t> rates_;
int16_t myAnswer_;
int16_t minAnswer_;
int16_t minAnswerNum_;
virtual inline int32_t msgId() const {return 1967;}
static int32_t MsgId() {return 1967;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBonfireCopyQuestion();}
};
class SEnterTaskCopy: public SEnterCopy {
public:
virtual inline int32_t msgId() const {return 2004;}
static int32_t MsgId() {return 2004;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEnterTaskCopy();}
};
class SCompleteTaskCopy: public SCompleteCopy {
public:
vector<msgs::SItemAmount> rewards_;
int32_t ownerMonsterId_;
virtual inline int32_t msgId() const {return 2005;}
static int32_t MsgId() {return 2005;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteTaskCopy();}
};
class STaskCopyInfo: public Msg {
public:
Identity belongId_;
virtual inline int32_t msgId() const {return 2071;}
static int32_t MsgId() {return 2071;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STaskCopyInfo();}
};
class SEnterArenaWzCopy: public SEnterCopy {
public:
virtual inline int32_t msgId() const {return 2027;}
static int32_t MsgId() {return 2027;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEnterArenaWzCopy();}
};
class SCompleteArenaWzCopy: public SCompleteCopy {
public:
int32_t level_;
int32_t addStar_;
map<int32_t, int32_t> reward_;
virtual inline int32_t msgId() const {return 2028;}
static int32_t MsgId() {return 2028;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteArenaWzCopy();}
};
class SGuildBossData: public Msg {
public:
Identity guildId_;
string guildName_;
int32_t curId_;
int64_t curLife_;
virtual inline int32_t msgId() const {return 1684;}
static int32_t MsgId() {return 1684;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildBossData();}
};
class SCompleteGuildBossCopy: public SCompleteCopy {
public:
int32_t initId_;
int32_t curId_;
int64_t totalHurt_;
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 2036;}
static int32_t MsgId() {return 2036;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteGuildBossCopy();}
};
class SGuildBossCopyInfo: public Msg {
public:
int32_t initId_;
int32_t killedId_;
int32_t addHurtPer_;
int64_t totalHurt_;
int32_t spaceMaxRound_;
virtual inline int32_t msgId() const {return 2037;}
static int32_t MsgId() {return 2037;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildBossCopyInfo();}
};
class SGuildBossCopyRank: public Msg {
public:
Identity entityId_;
string name_;
int64_t hurt_;
virtual inline int32_t msgId() const {return 3110;}
static int32_t MsgId() {return 3110;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildBossCopyRank();}
};
class SGuildBossCopyRankList: public Msg {
public:
vector<SGuildBossCopyRank> rankList_;
virtual inline int32_t msgId() const {return 3111;}
static int32_t MsgId() {return 3111;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildBossCopyRankList();}
};
class SEnterDefenseCopy: public SEnterCopy {
public:
int32_t isGuide_;
virtual inline int32_t msgId() const {return 2226;}
static int32_t MsgId() {return 2226;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEnterDefenseCopy();}
};
class SCompleteDefenseCopy: public SCompleteCopy {
public:
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 2227;}
static int32_t MsgId() {return 2227;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteDefenseCopy();}
};
class SDefenseCopyInfo: public Msg {
public:
int32_t towerId_;
int32_t monsterNum_;
int32_t score_;
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 2228;}
static int32_t MsgId() {return 2228;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SDefenseCopyInfo();}
};
class SDefenseCopyRefreshInfo: public Msg {
public:
int32_t buyBoss_;
int32_t round_;
int64_t nextRefreshDt_;
virtual inline int32_t msgId() const {return 2240;}
static int32_t MsgId() {return 2240;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SDefenseCopyRefreshInfo();}
};
class SEnterBattleCopy: public SEnterCopy {
public:
virtual inline int32_t msgId() const {return 2467;}
static int32_t MsgId() {return 2467;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEnterBattleCopy();}
};
class SBattleCopyInfo: public Msg {
public:
int64_t changeForceDt_;
virtual inline int32_t msgId() const {return 2445;}
static int32_t MsgId() {return 2445;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBattleCopyInfo();}
};
class SBattlePlayerInfo: public Msg {
public:
vector<int32_t> getIds_;
virtual inline int32_t msgId() const {return 2446;}
static int32_t MsgId() {return 2446;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBattlePlayerInfo();}
};
class SBattleScoreUpdate: public Msg {
public:
int16_t type_;
int16_t addScore_;
int32_t valueEx_;
string name_;
virtual inline int32_t msgId() const {return 2447;}
static int32_t MsgId() {return 2447;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBattleScoreUpdate();}
};
class SBattleCopyRankItem: public Msg {
public:
Identity entityId_;
string name_;
string gname_;
int32_t score_;
virtual inline int32_t msgId() const {return 2448;}
static int32_t MsgId() {return 2448;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBattleCopyRankItem();}
};
class SBattleRankInfo: public Msg {
public:
int32_t rank_;
int32_t score_;
vector<SBattleCopyRankItem> list_;
virtual inline int32_t msgId() const {return 2449;}
static int32_t MsgId() {return 2449;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBattleRankInfo();}
};
class SBattleCopyResult: public Msg {
public:
int32_t score_;
int32_t rank_;
vector<SBattleCopyRankItem> list_;
virtual inline int32_t msgId() const {return 2468;}
static int32_t MsgId() {return 2468;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBattleCopyResult();}
};
class SEnterFairylandCopy: public SEnterCopy {
public:
int32_t floor_;
virtual inline int32_t msgId() const {return 2426;}
static int32_t MsgId() {return 2426;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEnterFairylandCopy();}
};
class SCompleteFairylandCopyToClient: public SCompleteCopy {
public:
int32_t floor_;
int32_t grade_;
bool firstS_;
int32_t timeTaken_;
virtual inline int32_t msgId() const {return 2430;}
static int32_t MsgId() {return 2430;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteFairylandCopyToClient();}
};
class SFairylandRank: public Msg {
public:
int32_t rank_;
int32_t vip_;
string name_;
int32_t floor_;
int32_t timeTaken_;
virtual inline int32_t msgId() const {return 2453;}
static int32_t MsgId() {return 2453;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFairylandRank();}
};
class SFairylandRankList: public Msg {
public:
vector<SFairylandRank> rankLists_;
virtual inline int32_t msgId() const {return 2454;}
static int32_t MsgId() {return 2454;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFairylandRankList();}
};
class SJiuTianPlayerData: public Msg {
public:
int32_t exp_;
int32_t glory_;
virtual inline int32_t msgId() const {return 2507;}
static int32_t MsgId() {return 2507;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SJiuTianPlayerData();}
};
class SJiuTianRankData: public Msg {
public:
string playerName_;
string guildName_;
int32_t exp_;
int32_t glory_;
map<int32_t, int32_t> rankReward_;
virtual inline int32_t msgId() const {return 2517;}
static int32_t MsgId() {return 2517;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SJiuTianRankData();}
};
class SJiuTianRankList: public Msg {
public:
int32_t exp_;
int32_t glory_;
map<int32_t, int32_t> rankReward_;
vector<SJiuTianRankData> rankList_;
virtual inline int32_t msgId() const {return 2518;}
static int32_t MsgId() {return 2518;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SJiuTianRankList();}
};
class SJiuTianOccupier: public Msg {
public:
Identity playerEntityId_;
Point point_;
int32_t type_;
virtual inline int32_t msgId() const {return 2523;}
static int32_t MsgId() {return 2523;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SJiuTianOccupier();}
};
class SJiuTianJuTianPos: public Msg {
public:
vector<Point> juPoints_;
vector<Point> tianPoints_;
virtual inline int32_t msgId() const {return 2562;}
static int32_t MsgId() {return 2562;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SJiuTianJuTianPos();}
};
class SJiuTianCopyInfo: public Msg {
public:
int32_t copyCode_;
vector<Point> juPoints_;
vector<Identity> juOccupier_;
vector<Point> tianPoints_;
vector<Identity> tianOccupier_;
int32_t exp_;
int32_t glory_;
virtual inline int32_t msgId() const {return 2751;}
static int32_t MsgId() {return 2751;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SJiuTianCopyInfo();}
};
class SCopyVp: public Msg {
public:
int32_t copyCode_;
int32_t vp_;
virtual inline int32_t msgId() const {return 2559;}
static int32_t MsgId() {return 2559;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCopyVp();}
};
class SCopyVpKickPlayer: public Msg {
public:
int32_t copyCode_;
int64_t kickTime_;
virtual inline int32_t msgId() const {return 2560;}
static int32_t MsgId() {return 2560;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCopyVpKickPlayer();}
};
class SEnterZhulingCopy: public SEnterCopy {
public:
virtual inline int32_t msgId() const {return 2566;}
static int32_t MsgId() {return 2566;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEnterZhulingCopy();}
};
class SCompleteZhulingCopy: public SCompleteCopy {
public:
int32_t level_;
int32_t grade_;
int32_t timeTaken_;
int32_t lingli_;
map<int32_t, int32_t> specialReward_;
virtual inline int32_t msgId() const {return 2567;}
static int32_t MsgId() {return 2567;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteZhulingCopy();}
};
class SImmortalRoadRankRecord: public Msg {
public:
Identity entityId_;
string name_;
int64_t hurt_;
virtual inline int32_t msgId() const {return 2744;}
static int32_t MsgId() {return 2744;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SImmortalRoadRankRecord();}
};
class SCompleteImmortalRoadCopy: public SCompleteCopy {
public:
bool isAssist_;
int32_t costTime_;
vector<SImmortalRoadRankRecord> records_;
virtual inline int32_t msgId() const {return 2709;}
static int32_t MsgId() {return 2709;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteImmortalRoadCopy();}
};
class SImmortalRoadCopyInfo: public Msg {
public:
int16_t waveNum_;
map<int32_t, int32_t> monsters_;
virtual inline int32_t msgId() const {return 2710;}
static int32_t MsgId() {return 2710;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SImmortalRoadCopyInfo();}
};
class SEnterGuildTrialCopy: public SEnterCopy {
public:
int32_t fightTime_;
int32_t layer_;
virtual inline int32_t msgId() const {return 2721;}
static int32_t MsgId() {return 2721;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEnterGuildTrialCopy();}
};
class SCompleteGuildTrialCopy: public SCompleteCopy {
public:
int32_t completeTime_;
int32_t layer_;
virtual inline int32_t msgId() const {return 2722;}
static int32_t MsgId() {return 2722;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteGuildTrialCopy();}
};
class SGuildTrialCopyInfo: public Msg {
public:
int32_t copyCode_;
int32_t layer_;
int64_t fightTime_;
virtual inline int32_t msgId() const {return 2758;}
static int32_t MsgId() {return 2758;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildTrialCopyInfo();}
};
class SGuildTrialBossSingle: public Msg {
public:
int32_t layer_;
int32_t life_;
int64_t refreshTime_;
vector<msgs::SGuildMember> curPlayers_;
virtual inline int32_t msgId() const {return 2725;}
static int32_t MsgId() {return 2725;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildTrialBossSingle();}
};
class SGuildTrialBossList: public Msg {
public:
map<int32_t, SGuildTrialBossSingle> bossList_;
virtual inline int32_t msgId() const {return 2726;}
static int32_t MsgId() {return 2726;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildTrialBossList();}
};
class SGuildTrialKickPlayer: public Msg {
public:
virtual inline int32_t msgId() const {return 2749;}
static int32_t MsgId() {return 2749;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildTrialKickPlayer();}
};
class SEnterArenaTtCopy: public SEnterCopy {
public:
virtual inline int32_t msgId() const {return 2822;}
static int32_t MsgId() {return 2822;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEnterArenaTtCopy();}
};
class SCompleteArenaTtCopy: public SCompleteCopy {
public:
int32_t level_;
int32_t addScore_;
map<int32_t, int32_t> reward_;
virtual inline int32_t msgId() const {return 2823;}
static int32_t MsgId() {return 2823;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteArenaTtCopy();}
};
class SArenaTtPlayerInfo: public Msg {
public:
Identity entityId_;
string name_;
int32_t career_;
int32_t arenaLevel_;
int32_t loseCount_;
virtual inline int32_t msgId() const {return 2845;}
static int32_t MsgId() {return 2845;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SArenaTtPlayerInfo();}
};
class SPartnerIslandInfo: public Msg {
public:
int32_t type_;
int32_t copyCode_;
virtual inline int32_t msgId() const {return 2895;}
static int32_t MsgId() {return 2895;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPartnerIslandInfo();}
};
class SCompletePartnerIsland: public SCompleteCopy {
public:
int32_t type_;
int32_t layer_;
int32_t completeTime_;
bool isQuick_;
bool isDoubleExp_;
virtual inline int32_t msgId() const {return 2876;}
static int32_t MsgId() {return 2876;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompletePartnerIsland();}
};
class SCompleteGodAnimalIsland: public SCompleteCopy {
public:
int32_t layer_;
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 2908;}
static int32_t MsgId() {return 2908;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteGodAnimalIsland();}
};
class SPlayerCompletePartnerIsland: public Msg {
public:
int32_t copyCode_;
int32_t layer_;
virtual inline int32_t msgId() const {return 4142;}
static int32_t MsgId() {return 4142;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerCompletePartnerIsland();}
};
class SGodAnimalIslandPlayer: public Msg {
public:
int32_t playerId_;
string name_;
int32_t layer_;
int64_t completeTime_;
virtual inline int32_t msgId() const {return 2911;}
static int32_t MsgId() {return 2911;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGodAnimalIslandPlayer();}
};
class SGodAnimalIslandRank: public Msg {
public:
vector<SGodAnimalIslandPlayer> ranks_;
virtual inline int32_t msgId() const {return 2912;}
static int32_t MsgId() {return 2912;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGodAnimalIslandRank();}
};
class SMonsterKill: public Msg {
public:
int32_t monsterId_;
Point killPoint_;
virtual inline int32_t msgId() const {return 3096;}
static int32_t MsgId() {return 3096;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMonsterKill();}
};
class SGodAnimalIslandRound: public Msg {
public:
int32_t round_;
int64_t refreshTime_;
virtual inline int32_t msgId() const {return 2952;}
static int32_t MsgId() {return 2952;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGodAnimalIslandRound();}
};
class SCompleteThreeWorld: public SCompleteCopy {
public:
int32_t layer_;
int32_t layerHead_;
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 3014;}
static int32_t MsgId() {return 3014;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteThreeWorld();}
};
class SThreeWorldInfoList: public Msg {
public:
vector<msgs::SMiniPlayer> list_;
int32_t layer_;
virtual inline int32_t msgId() const {return 3015;}
static int32_t MsgId() {return 3015;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SThreeWorldInfoList();}
};
class SSyncThreeWorldHead: public Msg {
public:
vector<Identity> headList_;
string uid_;
virtual inline int32_t msgId() const {return 3058;}
static int32_t MsgId() {return 3058;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SSyncThreeWorldHead();}
};
class SCompletePetTotem: public SCompleteCopy {
public:
int32_t page_;
int32_t layer_;
int32_t star_;
int32_t completeTime_;
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 3114;}
static int32_t MsgId() {return 3114;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompletePetTotem();}
};
class SAwakeCopyInfo: public Msg {
public:
int32_t copyCode_;
int32_t floor_;
int32_t layer_;
virtual inline int32_t msgId() const {return 3131;}
static int32_t MsgId() {return 3131;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAwakeCopyInfo();}
};
class SCompleteAwakeCopy: public SCompleteCopy {
public:
int32_t floor_;
int32_t layer_;
virtual inline int32_t msgId() const {return 3124;}
static int32_t MsgId() {return 3124;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteAwakeCopy();}
};
class SPlayerPetTotem: public Msg {
public:
int32_t totalStar_;
map<int32_t, int32_t> stars_;
map<int32_t, int32_t> notGotFirstReward_;
map<int32_t, int32_t> notGotCollectStarReward_;
virtual inline int32_t msgId() const {return 3196;}
static int32_t MsgId() {return 3196;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerPetTotem();}
};
class SPetTotemInfo: public Msg {
public:
int32_t page_;
int32_t layer_;
virtual inline int32_t msgId() const {return 3207;}
static int32_t MsgId() {return 3207;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPetTotemInfo();}
};
class SCompleteMengPetCopy: public SCompleteCopy {
public:
int32_t layer_;
bool isAssist_;
int32_t assistNum_;
int32_t costTime_;
map<int32_t, int32_t> reward_;
virtual inline int32_t msgId() const {return 3271;}
static int32_t MsgId() {return 3271;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteMengPetCopy();}
};
class SHirePlayer: public Msg {
public:
Identity entityId_;
string name_;
int64_t combat_;
int32_t career_;
int32_t level_;
int32_t careerLevel_;
map<int16_t, int32_t> ornaments_;
int32_t count_;
virtual inline int32_t msgId() const {return 3543;}
static int32_t MsgId() {return 3543;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SHirePlayer();}
};
class SMengPetHireList: public Msg {
public:
vector<SHirePlayer> hireList_;
virtual inline int32_t msgId() const {return 3544;}
static int32_t MsgId() {return 3544;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMengPetHireList();}
};
class SDragonSoulCopyInfo: public Msg {
public:
int32_t floor_;
int32_t layer_;
virtual inline int32_t msgId() const {return 3306;}
static int32_t MsgId() {return 3306;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SDragonSoulCopyInfo();}
};
class SCompleteDragonSoulCopy: public SCompleteCopy {
public:
int32_t floor_;
int32_t layer_;
int32_t completeTime_;
int32_t star_;
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 3307;}
static int32_t MsgId() {return 3307;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteDragonSoulCopy();}
};
class SForgeCopyInfo: public Msg {
public:
int32_t copyCode_;
int32_t floor_;
int32_t round_;
int32_t monsterKilled_;
int32_t fleed_;
msgs::SIntIntPair encourage_;
msgs::SIntIntPair slowDown_;
virtual inline int32_t msgId() const {return 3320;}
static int32_t MsgId() {return 3320;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SForgeCopyInfo();}
};
class SCompleteForgeCopy: public SCompleteCopy {
public:
int32_t floor_;
int32_t grade_;
int32_t monsterKilledNum_;
map<int32_t, int32_t> drop_;
bool isFirstToS_;
virtual inline int32_t msgId() const {return 3315;}
static int32_t MsgId() {return 3315;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteForgeCopy();}
};
class SForgeCopyRank: public Msg {
public:
int32_t playerId_;
string name_;
int32_t floor_;
int32_t fleedNum_;
virtual inline int32_t msgId() const {return 3332;}
static int32_t MsgId() {return 3332;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SForgeCopyRank();}
};
class SForgeCopyRankList: public Msg {
public:
vector<SForgeCopyRank> ranks_;
virtual inline int32_t msgId() const {return 3333;}
static int32_t MsgId() {return 3333;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SForgeCopyRankList();}
};
class SCompleteWeekCopy: public SCompleteCopy {
public:
int32_t level_;
map<int32_t, int32_t> reward_;
virtual inline int32_t msgId() const {return 3364;}
static int32_t MsgId() {return 3364;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteWeekCopy();}
};
class SCompletePlaceTreasureCopy: public SCompleteCopy {
public:
int32_t level_;
map<int32_t, int32_t> reward_;
virtual inline int32_t msgId() const {return 3460;}
static int32_t MsgId() {return 3460;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompletePlaceTreasureCopy();}
};
class SEnterSPACopy: public SEnterCopy {
public:
int32_t cellNum_;
virtual inline int32_t msgId() const {return 3535;}
static int32_t MsgId() {return 3535;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEnterSPACopy();}
};
class SSPACopyReward: public Msg {
public:
map<int32_t, int32_t> reward_;
virtual inline int32_t msgId() const {return 3538;}
static int32_t MsgId() {return 3538;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SSPACopyReward();}
};
class SSPACopyRoomInfo: public Msg {
public:
int32_t copyCode_;
map<int32_t, int32_t> roomInfo_;
vector<int32_t> recentRoom_;
virtual inline int32_t msgId() const {return 3471;}
static int32_t MsgId() {return 3471;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SSPACopyRoomInfo();}
};
class SSPACopyAct: public Msg {
public:
int32_t num_;
int64_t time_;
virtual inline int32_t msgId() const {return 3477;}
static int32_t MsgId() {return 3477;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SSPACopyAct();}
};
class SSPACopyActInfo: public Msg {
public:
int32_t copyCode_;
map<int32_t, SSPACopyAct> actInfo_;
int32_t lastType_;
int64_t lastTime_;
virtual inline int32_t msgId() const {return 3540;}
static int32_t MsgId() {return 3540;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SSPACopyActInfo();}
};
class SSPACopyActBROInfo: public Msg {
public:
int32_t type_;
Identity fromId_;
Identity toId_;
int64_t time_;
virtual inline int32_t msgId() const {return 3555;}
static int32_t MsgId() {return 3555;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SSPACopyActBROInfo();}
};
class SSPACopyFlower: public Msg {
public:
int32_t copyCode_;
map<int32_t, int32_t> flower_;
virtual inline int32_t msgId() const {return 3509;}
static int32_t MsgId() {return 3509;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SSPACopyFlower();}
};
class SSPAMiniPlayer: public Msg {
public:
Identity entityId_;
int32_t career_;
string name_;
int32_t rank_;
int32_t recFlower_;
int16_t sex_;
map<int16_t, int32_t> ornaments_;
virtual inline int32_t msgId() const {return 3549;}
static int32_t MsgId() {return 3549;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SSPAMiniPlayer();}
};
class SCompleteSPACopy: public SCompleteCopy {
public:
map<int32_t, int32_t> rewardGot_;
virtual inline int32_t msgId() const {return 3553;}
static int32_t MsgId() {return 3553;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteSPACopy();}
};
class SSPAFlorwerRankList: public Msg {
public:
vector<SSPAMiniPlayer> rankList_;
virtual inline int32_t msgId() const {return 3566;}
static int32_t MsgId() {return 3566;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SSPAFlorwerRankList();}
};
class SCopyContinueKill: public Msg {
public:
int32_t copyCode_;
int32_t killNum_;
virtual inline int32_t msgId() const {return 3501;}
static int32_t MsgId() {return 3501;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCopyContinueKill();}
};
class SSPACopySendFlowerInfo: public Msg {
public:
Identity fromPlayerId_;
string fromName_;
Identity toPlayerId_;
int32_t itemCode_;
virtual inline int32_t msgId() const {return 3572;}
static int32_t MsgId() {return 3572;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SSPACopySendFlowerInfo();}
};
class SSPAPlayerFlower: public Msg {
public:
int32_t receive_;
map<int32_t, int32_t> bought_;
virtual inline int32_t msgId() const {return 3581;}
static int32_t MsgId() {return 3581;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SSPAPlayerFlower();}
};
class SPryCrossBServer: public Msg {
public:
int32_t serverId_;
int32_t proxyId_;
int32_t goldValue_;
int32_t activeKey_;
virtual inline int32_t msgId() const {return 3700;}
static int32_t MsgId() {return 3700;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPryCrossBServer();}
};
class SCompletePryCrossB: public SCompleteCopy {
public:
virtual inline int32_t msgId() const {return 3600;}
static int32_t MsgId() {return 3600;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompletePryCrossB();}
};
class SPryCrossBInfo: public Msg {
public:
int32_t serverId_;
int32_t proxyId_;
int32_t copyCode_;
int32_t belongValue_;
int32_t attackValue_;
int32_t defenseValue_;
int32_t mineralAttack_;
virtual inline int32_t msgId() const {return 3601;}
static int32_t MsgId() {return 3601;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPryCrossBInfo();}
};
class SEnterOfficialCampaign: public SEnterCopy {
public:
bool isCross_;
int32_t officialId_;
virtual inline int32_t msgId() const {return 4017;}
static int32_t MsgId() {return 4017;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEnterOfficialCampaign();}
};
class SCompleteOfficialCampaign: public SCompleteCopy {
public:
bool isCross_;
int32_t officialId_;
int64_t combat_;
virtual inline int32_t msgId() const {return 4018;}
static int32_t MsgId() {return 4018;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteOfficialCampaign();}
};
class SOfficialCampaignInfo: public Msg {
public:
bool isCross_;
int32_t copyCode_;
virtual inline int32_t msgId() const {return 4019;}
static int32_t MsgId() {return 4019;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SOfficialCampaignInfo();}
};
class SOfficialInfoSingle: public Msg {
public:
bool isCross_;
msgs::SPublicPlayer publicPlayer_;
int64_t updateTime_;
virtual inline int32_t msgId() const {return 4047;}
static int32_t MsgId() {return 4047;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SOfficialInfoSingle();}
};
class SOfficialInfo: public Msg {
public:
bool isCross_;
map<int32_t, SOfficialInfoSingle> officialMap_;
virtual inline int32_t msgId() const {return 4048;}
static int32_t MsgId() {return 4048;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SOfficialInfo();}
};
class SCompleteGodMagicTower: public SCompleteCopy {
public:
int32_t tower_;
int32_t layer_;
map<int32_t, int32_t> rewards_;
map<int32_t, int32_t> targetRewards_;
virtual inline int32_t msgId() const {return 4114;}
static int32_t MsgId() {return 4114;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteGodMagicTower();}
};
class SGodMagicTowerAttr: public Msg {
public:
int32_t playerId_;
string name_;
int32_t per_;
int32_t tower_;
int32_t layer_;
virtual inline int32_t msgId() const {return 4131;}
static int32_t MsgId() {return 4131;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGodMagicTowerAttr();}
};
class SGodMagicTowerAddAttr: public Msg {
public:
vector<SGodMagicTowerAttr> likeAttr_;
vector<SGodMagicTowerAttr> helpedAttr_;
virtual inline int32_t msgId() const {return 4132;}
static int32_t MsgId() {return 4132;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGodMagicTowerAddAttr();}
};
class SGodMagicTowerRank: public Msg {
public:
int32_t playerId_;
string name_;
int32_t tower_;
int32_t layer_;
bool canLike_;
virtual inline int32_t msgId() const {return 4133;}
static int32_t MsgId() {return 4133;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGodMagicTowerRank();}
};
class SGodMagicTowerRankList: public Msg {
public:
vector<SGodMagicTowerRank> ranks_;
virtual inline int32_t msgId() const {return 4134;}
static int32_t MsgId() {return 4134;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGodMagicTowerRankList();}
};
class SGodMagicTowerHelp: public Msg {
public:
int32_t playerId_;
string name_;
int32_t career_;
map<int16_t, int32_t> ornaments_;
int32_t helpTime_;
int32_t addPer_;
virtual inline int32_t msgId() const {return 4138;}
static int32_t MsgId() {return 4138;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGodMagicTowerHelp();}
};
class SGodMagicTowerHelpList: public Msg {
public:
vector<SGodMagicTowerHelp> list_;
virtual inline int32_t msgId() const {return 4139;}
static int32_t MsgId() {return 4139;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGodMagicTowerHelpList();}
};
class SCompleteAvatarTower: public SCompleteCopy {
public:
int32_t floor_;
int32_t completeTime_;
bool isFirst_;
virtual inline int32_t msgId() const {return 4221;}
static int32_t MsgId() {return 4221;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteAvatarTower();}
};
class SAvatarTowerInfo: public Msg {
public:
int32_t copyCode_;
int32_t floor_;
virtual inline int32_t msgId() const {return 4222;}
static int32_t MsgId() {return 4222;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAvatarTowerInfo();}
};
class SCompleteMonsterAround: public SCompleteCopy {
public:
int32_t level_;
int32_t gold_;
int32_t life_;
map<int32_t, int32_t> reward_;
virtual inline int32_t msgId() const {return 4365;}
static int32_t MsgId() {return 4365;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteMonsterAround();}
};
class SMonsterAroundCopyInfo: public Msg {
public:
int32_t level_;
map<int32_t, Point> towerPos_;
virtual inline int32_t msgId() const {return 4366;}
static int32_t MsgId() {return 4366;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMonsterAroundCopyInfo();}
};
class SMonsterAroundTower: public Msg {
public:
int32_t index_;
int32_t life_;
bool beAttack_;
virtual inline int32_t msgId() const {return 4367;}
static int32_t MsgId() {return 4367;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMonsterAroundTower();}
};
class SMonsterAroundTowers: public Msg {
public:
vector<SMonsterAroundTower> towers_;
virtual inline int32_t msgId() const {return 4376;}
static int32_t MsgId() {return 4376;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMonsterAroundTowers();}
};
class SMonsterAroundChat: public Msg {
public:
Identity fromId_;
string fromName_;
int32_t chatIndex_;
virtual inline int32_t msgId() const {return 4420;}
static int32_t MsgId() {return 4420;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMonsterAroundChat();}
};
class SMonsterAroundKillInfo: public Msg {
public:
int32_t killNum_;
int32_t openNum_;
virtual inline int32_t msgId() const {return 4692;}
static int32_t MsgId() {return 4692;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMonsterAroundKillInfo();}
};
class SCrossCityData: public Msg {
public:
int32_t index_;
vector<Identity> emperors_;
Identity occupyServer_;
vector<Identity> fightServers_;
virtual inline int32_t msgId() const {return 4501;}
static int32_t MsgId() {return 4501;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCrossCityData();}
};
class SCompleteCrossCityWarCopy: public SCompleteCopy {
public:
int32_t cityIndex_;
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 4464;}
static int32_t MsgId() {return 4464;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteCrossCityWarCopy();}
};
class SCrossCityWarServerData: public Msg {
public:
Identity serverId_;
int32_t force_;
int32_t score_;
virtual inline int32_t msgId() const {return 4471;}
static int32_t MsgId() {return 4471;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCrossCityWarServerData();}
};
class SCrossCityWarCopyInfo: public Msg {
public:
int32_t cityIndex_;
vector<SCrossCityWarServerData> servers_;
map<int32_t, int32_t> towers_;
virtual inline int32_t msgId() const {return 4470;}
static int32_t MsgId() {return 4470;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCrossCityWarCopyInfo();}
};
class SCrossCityWarPlayerInfo: public Msg {
public:
Identity serverId_;
int32_t gonglao_;
int32_t killNum_;
virtual inline int32_t msgId() const {return 4566;}
static int32_t MsgId() {return 4566;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCrossCityWarPlayerInfo();}
};
class SCompleteCrossCityWar2Copy: public SCompleteCopy {
public:
int32_t cityIndex_;
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 4562;}
static int32_t MsgId() {return 4562;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteCrossCityWar2Copy();}
};
class SCrossCityWar2ServerData: public Msg {
public:
Identity serverId_;
int32_t force_;
int32_t score_;
bool defence_;
virtual inline int32_t msgId() const {return 4481;}
static int32_t MsgId() {return 4481;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCrossCityWar2ServerData();}
};
class SCrossCityWar2CopyInfo: public Msg {
public:
int32_t cityIndex_;
vector<SCrossCityWar2ServerData> servers_;
vector<Identity> towerList_;
virtual inline int32_t msgId() const {return 4482;}
static int32_t MsgId() {return 4482;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCrossCityWar2CopyInfo();}
};
class SCrossCityWar2PlayerInfo: public Msg {
public:
Identity serverId_;
int32_t gonglao_;
int32_t killNum_;
virtual inline int32_t msgId() const {return 4489;}
static int32_t MsgId() {return 4489;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCrossCityWar2PlayerInfo();}
};
class SCrossCityHistory: public Msg {
public:
int32_t cityIndex_;
Identity serverId_;
int64_t occupyDt_;
bool isOccupy_;
virtual inline int32_t msgId() const {return 4569;}
static int32_t MsgId() {return 4569;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCrossCityHistory();}
};
class SCrossCityList: public Msg {
public:
int64_t signUpDt1_;
int64_t signUpDt2_;
vector<SCrossCityData> cityList_;
vector<SCrossCityHistory> historys_;
virtual inline int32_t msgId() const {return 4512;}
static int32_t MsgId() {return 4512;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCrossCityList();}
};
class SCrossCityWarSignUp: public Msg {
public:
int32_t index_;
Identity serverId_;
virtual inline int32_t msgId() const {return 4516;}
static int32_t MsgId() {return 4516;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCrossCityWarSignUp();}
};
class SSyncCrossCity: public Msg {
public:
Identity serverId_;
map<int32_t, int32_t> cityMap_;
virtual inline int32_t msgId() const {return 4527;}
static int32_t MsgId() {return 4527;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SSyncCrossCity();}
};
class SCrossCityWarCopyBroadcastKill: public Msg {
public:
int32_t killType_;
Identity entityId_;
string playerName_;
int32_t killNum_;
string toPlayerName_;
virtual inline int32_t msgId() const {return 4536;}
static int32_t MsgId() {return 4536;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCrossCityWarCopyBroadcastKill();}
};
class SCrossCityHuangDiPos: public Msg {
public:
Identity entityId_;
int32_t cityIndex_;
virtual inline int32_t msgId() const {return 4538;}
static int32_t MsgId() {return 4538;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCrossCityHuangDiPos();}
};
class SPlayerCrossCityWar: public Msg {
public:
vector<int32_t> dailyGot_;
virtual inline int32_t msgId() const {return 4540;}
static int32_t MsgId() {return 4540;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerCrossCityWar();}
};
class SCrossTeamRecord: public Msg {
public:
Identity entityId_;
string name_;
int64_t hurt_;
virtual inline int32_t msgId() const {return 4847;}
static int32_t MsgId() {return 4847;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCrossTeamRecord();}
};
class SCompleteCrossTeamCopy: public SCompleteCopy {
public:
bool isAssist_;
int32_t costTime_;
vector<SCrossTeamRecord> records_;
virtual inline int32_t msgId() const {return 4848;}
static int32_t MsgId() {return 4848;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteCrossTeamCopy();}
};
class SCrossTeamCopyInfo: public Msg {
public:
int16_t waveNum_;
map<int32_t, int32_t> monsters_;
virtual inline int32_t msgId() const {return 4849;}
static int32_t MsgId() {return 4849;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCrossTeamCopyInfo();}
};
class SPlayerCrossTeamData: public Msg {
public:
int32_t targetGot_;
int32_t maxPassedCopy_;
int32_t passedNum_;
virtual inline int32_t msgId() const {return 4862;}
static int32_t MsgId() {return 4862;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerCrossTeamData();}
};
class SCompleteGroupFight: public SCompleteCopy {
public:
int32_t addStar_;
Identity entityId_;
int32_t todayCount_;
int32_t addTeamStar_;
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 4986;}
static int32_t MsgId() {return 4986;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteGroupFight();}
};
class SCompleteGroupFightVec: public Msg {
public:
vector<SCompleteGroupFight> res_;
virtual inline int32_t msgId() const {return 4989;}
static int32_t MsgId() {return 4989;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteGroupFightVec();}
};
class SGroupFightJoin: public Msg {
public:
Identity playerId_;
string playerName_;
string teamName_;
int32_t career_;
int64_t combat_;
int32_t level_;
int32_t star_;
virtual inline int32_t msgId() const {return 4936;}
static int32_t MsgId() {return 4936;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGroupFightJoin();}
};
class SGroupFightTeam: public Msg {
public:
string name_;
Identity captainId_;
string captainName_;
int32_t captainLevel_;
int32_t captainStar_;
msgs::SStrings teams_;
virtual inline int32_t msgId() const {return 4941;}
static int32_t MsgId() {return 4941;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGroupFightTeam();}
};
class SGroupFightTeams: public Msg {
public:
vector<SGroupFightTeam> teams_;
virtual inline int32_t msgId() const {return 4938;}
static int32_t MsgId() {return 4938;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGroupFightTeams();}
};
class SGroupFightMatchSingle: public Msg {
public:
string teamName_;
int32_t level_;
int32_t star_;
int32_t successCount_;
int32_t todayCount_;
msgs::SPublicPlayer publicPlayer_;
virtual inline int32_t msgId() const {return 4948;}
static int32_t MsgId() {return 4948;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGroupFightMatchSingle();}
};
class SGroupFightMatch: public Msg {
public:
vector<SGroupFightMatchSingle> firstTeam_;
vector<SGroupFightMatchSingle> secondTeam_;
bool isMatch_;
virtual inline int32_t msgId() const {return 4949;}
static int32_t MsgId() {return 4949;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGroupFightMatch();}
};
class SGroupFightMatchVec: public Msg {
public:
vector<SGroupFightMatch> teams_;
virtual inline int32_t msgId() const {return 4950;}
static int32_t MsgId() {return 4950;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGroupFightMatchVec();}
};
class SXianMoShenInfo: public Msg {
public:
int32_t copyCode_;
int32_t floor_;
int32_t room_;
int64_t forceCD_;
map<int32_t, int32_t> monsters_;
virtual inline int32_t msgId() const {return 5044;}
static int32_t MsgId() {return 5044;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SXianMoShenInfo();}
};
class SXianMoShenBossKill: public Msg {
public:
Identity belongId_;
string belongName_;
int16_t belongCareer_;
string belongGuildName_;
int32_t belongForce_;
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 5036;}
static int32_t MsgId() {return 5036;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SXianMoShenBossKill();}
};
class SXianMoShenBossSkillBooks: public Msg {
public:
map<int32_t, int32_t> skillBooks_;
int32_t energy_;
virtual inline int32_t msgId() const {return 5038;}
static int32_t MsgId() {return 5038;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SXianMoShenBossSkillBooks();}
};
class SCompleteXianMoShen: public SCompleteCopy {
public:
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 5039;}
static int32_t MsgId() {return 5039;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteXianMoShen();}
};
class SXianMoShenContinuousKill: public Msg {
public:
Identity entityId_;
string name_;
int16_t career_;
int16_t killNum_;
virtual inline int32_t msgId() const {return 5042;}
static int32_t MsgId() {return 5042;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SXianMoShenContinuousKill();}
};
class SXianMoShenKillPlayer: public Msg {
public:
Identity fromPlayerId_;
string fromPlayerName_;
Identity toPlayerId_;
string toPlayerName_;
int32_t skillBookNum_;
virtual inline int32_t msgId() const {return 5046;}
static int32_t MsgId() {return 5046;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SXianMoShenKillPlayer();}
};
class SXianMoShenBoss: public Msg {
public:
map<int32_t, int64_t> bossRefresh_;
virtual inline int32_t msgId() const {return 5066;}
static int32_t MsgId() {return 5066;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SXianMoShenBoss();}
};
class SCompleteGridCopy: public SCompleteCopy {
public:
int32_t floor_;
map<int32_t, int32_t> rewards_;
int32_t completeTime_;
virtual inline int32_t msgId() const {return 5095;}
static int32_t MsgId() {return 5095;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteGridCopy();}
};
class SGridCopyInfo: public Msg {
public:
int32_t floor_;
virtual inline int32_t msgId() const {return 5096;}
static int32_t MsgId() {return 5096;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGridCopyInfo();}
};
class SPlayerWorshipArena: public Msg {
public:
int32_t worshipCount_;
int32_t todayMoney_;
map<string, int32_t> worshipPlayer_;
virtual inline int32_t msgId() const {return 5224;}
static int32_t MsgId() {return 5224;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerWorshipArena();}
};
class SUpdateWorshipArena: public Msg {
public:
Identity entityId_;
int32_t worshipCount_;
virtual inline int32_t msgId() const {return 5243;}
static int32_t MsgId() {return 5243;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SUpdateWorshipArena();}
};
class SWorshipTodayMoney: public Msg {
public:
map<string, int32_t> todayCount_;
virtual inline int32_t msgId() const {return 5268;}
static int32_t MsgId() {return 5268;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SWorshipTodayMoney();}
};
class SWorshipRankSingle: public Msg {
public:
int32_t rank_;
Identity entityId_;
string name_;
int32_t careerLevel_;
int32_t level_;
int64_t combat_;
string guildName_;
int32_t vipLevel_;
map<int16_t, int32_t> entityShow_;
int32_t career_;
virtual inline int32_t msgId() const {return 5270;}
static int32_t MsgId() {return 5270;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SWorshipRankSingle();}
};
class SWorshipRank: public Msg {
public:
map<int32_t, SWorshipRankSingle> list_;
virtual inline int32_t msgId() const {return 5271;}
static int32_t MsgId() {return 5271;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SWorshipRank();}
};
class SFirstArenaMatchPlayer: public Msg {
public:
Identity playerId_;
string name_;
int64_t combat_;
int32_t score_;
int16_t career_;
virtual inline int32_t msgId() const {return 5205;}
static int32_t MsgId() {return 5205;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFirstArenaMatchPlayer();}
};
class SFirstArenaMatch: public Msg {
public:
SFirstArenaMatchPlayer aPlayer_;
SFirstArenaMatchPlayer bPlayer_;
virtual inline int32_t msgId() const {return 5206;}
static int32_t MsgId() {return 5206;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFirstArenaMatch();}
};
class SFirstArenaResult: public msgs::SCompleteCopy {
public:
int32_t result_;
int32_t addScore_;
int32_t score_;
int32_t rank_;
map<int32_t, int32_t> rewards_;
int32_t failCount_;
int32_t successCount_;
virtual inline int32_t msgId() const {return 5207;}
static int32_t MsgId() {return 5207;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFirstArenaResult();}
};
class SFirstArenaFinalPlayer: public Msg {
public:
Identity playerId_;
string name_;
int64_t combat_;
int32_t score_;
int32_t layer_;
bool canWatch_;
int16_t career_;
int32_t bangType_;
virtual inline int32_t msgId() const {return 5208;}
static int32_t MsgId() {return 5208;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFirstArenaFinalPlayer();}
};
class SFirstArenaFinalList: public Msg {
public:
vector<SFirstArenaFinalPlayer> list_;
int32_t layer_;
int32_t status_;
int64_t endDt_;
int32_t bangType_;
virtual inline int32_t msgId() const {return 5209;}
static int32_t MsgId() {return 5209;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFirstArenaFinalList();}
};
class SFirstArenaFinalUpdate: public Msg {
public:
int32_t layer_;
int32_t status_;
int64_t endDt_;
int32_t bangType_;
virtual inline int32_t msgId() const {return 5210;}
static int32_t MsgId() {return 5210;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFirstArenaFinalUpdate();}
};
class SFirstArenaRankList: public Msg {
public:
int32_t rankType_;
vector<dbs::TFirstArenaRank> list_;
int32_t myScore_;
int32_t myRank_;
virtual inline int32_t msgId() const {return 5253;}
static int32_t MsgId() {return 5253;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFirstArenaRankList();}
};
class SBudoBossRank: public Msg {
public:
Identity playerId_;
string name_;
int64_t hurt_;
int32_t rank_;
virtual inline int32_t msgId() const {return 5232;}
static int32_t MsgId() {return 5232;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBudoBossRank();}
};
class SBudoBossRankList: public Msg {
public:
vector<SBudoBossRank> list_;
virtual inline int32_t msgId() const {return 5233;}
static int32_t MsgId() {return 5233;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBudoBossRankList();}
};
class SCompleteBudoBoss: public msgs::SCompleteCopy {
public:
int32_t myRank_;
int64_t myHurt_;
map<int32_t, int32_t> rewards_;
SBudoBossRankList ranks_;
virtual inline int32_t msgId() const {return 5234;}
static int32_t MsgId() {return 5234;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteBudoBoss();}
};
class SBudoBoss: public Msg {
public:
int32_t bossCode_;
int64_t life_;
int16_t career_;
string name_;
map<int32_t, int32_t> entityShow_;
virtual inline int32_t msgId() const {return 5236;}
static int32_t MsgId() {return 5236;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBudoBoss();}
};
class SBudoBossList: public Msg {
public:
vector<SBudoBoss> list_;
virtual inline int32_t msgId() const {return 5237;}
static int32_t MsgId() {return 5237;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBudoBossList();}
};
class SFirstArenaBet: public dbs::TFirstArenaBet {
public:
int32_t aBetCount_;
int32_t bBetCount_;
virtual inline int32_t msgId() const {return 5294;}
static int32_t MsgId() {return 5294;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFirstArenaBet();}
};
class SFirstArenaBetList: public Msg {
public:
vector<SFirstArenaBet> list_;
virtual inline int32_t msgId() const {return 5288;}
static int32_t MsgId() {return 5288;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFirstArenaBetList();}
};
class SFirstArenaBetInfo: public Msg {
public:
Identity aPlayerId_;
Identity bPlayerId_;
string aName_;
string bName_;
int32_t aScore_;
int32_t bScore_;
bool hasBet_;
virtual inline int32_t msgId() const {return 5289;}
static int32_t MsgId() {return 5289;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFirstArenaBetInfo();}
};
class SFirstArenaFinalHis: public Msg {
public:
int32_t result_;
int32_t num_;
virtual inline int32_t msgId() const {return 5303;}
static int32_t MsgId() {return 5303;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFirstArenaFinalHis();}
};
class SFirstArenaFinalHisList: public Msg {
public:
string aName_;
string bName_;
int32_t aCareer_;
int32_t bCareer_;
int32_t result_;
vector<SFirstArenaFinalHis> list_;
virtual inline int32_t msgId() const {return 5304;}
static int32_t MsgId() {return 5304;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFirstArenaFinalHisList();}
};
class SFirstArenaFinalWaiting: public Msg {
public:
int32_t round_;
int32_t num_;
int64_t endDt_;
virtual inline int32_t msgId() const {return 5308;}
static int32_t MsgId() {return 5308;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFirstArenaFinalWaiting();}
};
class SYaoChong: public Msg {
public:
int32_t idx_;
int32_t id_;
int32_t loseNum_;
int32_t timeNum_;
map<int32_t, int32_t> items_;
int64_t dt_;
virtual inline int32_t msgId() const {return 5154;}
static int32_t MsgId() {return 5154;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SYaoChong();}
};
class SYaoChongRecord: public Msg {
public:
int32_t id_;
string name_;
map<int32_t, int32_t> items_;
virtual inline int32_t msgId() const {return 5155;}
static int32_t MsgId() {return 5155;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SYaoChongRecord();}
};
class SYaoChongInfo: public Msg {
public:
int32_t extraNum_;
int32_t forage_;
vector<SYaoChong> yaochongLst_;
virtual inline int32_t msgId() const {return 5156;}
static int32_t MsgId() {return 5156;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SYaoChongInfo();}
};
class SYaoChongGrabInfo: public Msg {
public:
int32_t grabNum_;
vector<SYaoChongRecord> records_;
virtual inline int32_t msgId() const {return 5165;}
static int32_t MsgId() {return 5165;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SYaoChongGrabInfo();}
};
class SYaoChongUpdate: public Msg {
public:
vector<SYaoChong> ups_;
vector<int32_t> dels_;
virtual inline int32_t msgId() const {return 5161;}
static int32_t MsgId() {return 5161;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SYaoChongUpdate();}
};
class SYaoChongPlayer: public Msg {
public:
Identity entityId_;
string name_;
int32_t num_;
int32_t maxNum_;
virtual inline int32_t msgId() const {return 5173;}
static int32_t MsgId() {return 5173;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SYaoChongPlayer();}
};
class SYaoChongPlayerList: public Msg {
public:
vector<SYaoChongPlayer> list_;
virtual inline int32_t msgId() const {return 5174;}
static int32_t MsgId() {return 5174;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SYaoChongPlayerList();}
};
class SServerInfo: public Msg {
public:
int64_t nowDt_;
int64_t openDt_;
int64_t preOpenDt_;
int32_t mergeCount_;
int64_t mergeDt_;
bool switchGate_;
int32_t worldLevel_;
int32_t offsetHour_;
int32_t antiAddiction_;
int32_t rechargeId_;
string serverConfig_;
int64_t crossAOpenDt_;
int64_t crossBOpenDt_;
int64_t crossCOpenDt_;
int64_t crossDOpenDt_;
int32_t payNum_;
virtual inline int32_t msgId() const {return 220;}
static int32_t MsgId() {return 220;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SServerInfo();}
};
class SErrorMessage: public Msg {
public:
int32_t errorCode_;
string errorWhat_;
virtual inline int32_t msgId() const {return 221;}
static int32_t MsgId() {return 221;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SErrorMessage();}
};
class SWorldLevel: public Msg {
public:
int16_t worldLevel_;
int64_t updateDt_;
virtual inline int32_t msgId() const {return 1019;}
static int32_t MsgId() {return 1019;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SWorldLevel();}
};
class SServerOpenInfo: public Msg {
public:
int64_t openDt_;
int64_t preOpenDt_;
int32_t mergeCount_;
int64_t mergeDt_;
bool switchGate_;
virtual inline int32_t msgId() const {return 1415;}
static int32_t MsgId() {return 1415;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SServerOpenInfo();}
};
class SServerCrossOpenInfo: public Msg {
public:
int64_t crossAOpenDt_;
int64_t crossBOpenDt_;
int64_t crossCOpenDt_;
int64_t crossDOpenDt_;
int16_t aServerId_;
int16_t bServerId_;
int16_t cServerId_;
int16_t dServerId_;
virtual inline int32_t msgId() const {return 3766;}
static int32_t MsgId() {return 3766;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SServerCrossOpenInfo();}
};
class SPublicCounter: public Msg {
public:
int32_t type_;
map<int32_t, int32_t> map_;
virtual inline int32_t msgId() const {return 1464;}
static int32_t MsgId() {return 1464;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPublicCounter();}
};
class SInterestedEntity: public Msg {
public:
Identity entityId_;
int64_t lift_;
int64_t inPower_;
Point pos_;
virtual inline int32_t msgId() const {return 2252;}
static int32_t MsgId() {return 2252;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SInterestedEntity();}
};
class SUpdateInterestedEntity: public Msg {
public:
vector<SInterestedEntity> entities_;
virtual inline int32_t msgId() const {return 2249;}
static int32_t MsgId() {return 2249;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SUpdateInterestedEntity();}
};
class SRechargePersonNum: public Msg {
public:
int32_t num_;
virtual inline int32_t msgId() const {return 3070;}
static int32_t MsgId() {return 3070;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRechargePersonNum();}
};
class SMonsterAroundInfo: public Msg {
public:
bool autoBook_;
bool isOpen_;
int32_t level_;
int32_t life_;
int32_t bookHour_;
int32_t getReward_;
virtual inline int32_t msgId() const {return 4360;}
static int32_t MsgId() {return 4360;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMonsterAroundInfo();}
};
class SMonsterAroundRecord: public Msg {
public:
Identity entityId_;
int32_t career_;
int32_t itemCode_;
int32_t itemNum_;
string name_;
map<int16_t, int32_t> ornaments_;
virtual inline int32_t msgId() const {return 4683;}
static int32_t MsgId() {return 4683;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMonsterAroundRecord();}
};
class SMonsterAroundRecords: public Msg {
public:
vector<SMonsterAroundRecord> records_;
virtual inline int32_t msgId() const {return 4684;}
static int32_t MsgId() {return 4684;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMonsterAroundRecords();}
};
class SRoleLegendEquip: public Msg {
public:
map<int32_t, int32_t> levelMap_;
virtual inline int32_t msgId() const {return 3349;}
static int32_t MsgId() {return 3349;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRoleLegendEquip();}
};
class SLegendEquip: public Msg {
public:
map<int32_t, SRoleLegendEquip> advanceMap_;
virtual inline int32_t msgId() const {return 3350;}
static int32_t MsgId() {return 3350;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SLegendEquip();}
};
class SPlayerLoginData: public Msg {
public:
int32_t playerId_;
Identity entityId_;
uint16_t proxyId_;
uint16_t serverId_;
string testStr_;
int32_t idCardStatus_;
virtual inline int32_t msgId() const {return 299;}
static int32_t MsgId() {return 299;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerLoginData();}
};
class SPlayerRoleList: public Msg {
public:
vector<Msg*> roleList_;
virtual inline int32_t msgId() const {return 1695;}
static int32_t MsgId() {return 1695;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerRoleList();}
};
class SAddExp: public Msg {
public:
int16_t updateCode_;
int64_t exp_;
int32_t addon_;
virtual inline int32_t msgId() const {return 300;}
static int32_t MsgId() {return 300;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAddExp();}
};
class SPlayerInfo: public Msg {
public:
int32_t loginDays_;
virtual inline int32_t msgId() const {return 2092;}
static int32_t MsgId() {return 2092;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerInfo();}
};
class SLevelUp: public Msg {
public:
int16_t level_;
int64_t exp_;
int64_t levelDt_;
virtual inline int32_t msgId() const {return 301;}
static int32_t MsgId() {return 301;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SLevelUp();}
};
class SPlayerCombatData: public Msg {
public:
int64_t combat_;
int64_t avatarCombat_;
virtual inline int32_t msgId() const {return 302;}
static int32_t MsgId() {return 302;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerCombatData();}
};
class SPlayerCombatChange: public Msg {
public:
int64_t combat_;
int64_t avatarCombat_;
virtual inline int32_t msgId() const {return 303;}
static int32_t MsgId() {return 303;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerCombatChange();}
};
class SRoleCombatData: public Msg {
public:
int32_t roleId_;
int64_t combat_;
msgs::SFightAttribute fightAttr_;
map<int16_t, int64_t> copyAttr_;
msgs::SFightAttribute fixAttr_;
virtual inline int32_t msgId() const {return 1716;}
static int32_t MsgId() {return 1716;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRoleCombatData();}
};
class SRoleCombatChange: public Msg {
public:
int32_t roleId_;
int64_t combat_;
map<int16_t, int64_t> diffAttr_;
map<int16_t, int64_t> diffCopyAttr_;
map<int16_t, int64_t> diffFixAttr_;
virtual inline int32_t msgId() const {return 1703;}
static int32_t MsgId() {return 1703;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRoleCombatChange();}
};
class SPlayerDeath: public Msg {
public:
int32_t deathType_;
int32_t reviveType_;
int32_t bossCode_;
Identity fromId_;
string fromName_;
vector<int64_t> reviveCd_;
int32_t freeRevive_;
virtual inline int32_t msgId() const {return 947;}
static int32_t MsgId() {return 947;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerDeath();}
};
class SPlayerExpAddon: public Msg {
public:
int32_t addon_;
int64_t endDt_;
virtual inline int32_t msgId() const {return 992;}
static int32_t MsgId() {return 992;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerExpAddon();}
};
class SPlayerRevive: public Msg {
public:
int32_t type_;
Identity fromEntityId_;
virtual inline int32_t msgId() const {return 1114;}
static int32_t MsgId() {return 1114;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerRevive();}
};
class SPlayerThreat: public Msg {
public:
string name_;
int64_t value_;
int64_t hurt_;
virtual inline int32_t msgId() const {return 1116;}
static int32_t MsgId() {return 1116;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerThreat();}
};
class SPlayerThreats: public Msg {
public:
vector<SPlayerThreat> threats_;
vector<SPlayerThreat> belongHurt_;
virtual inline int32_t msgId() const {return 1117;}
static int32_t MsgId() {return 1117;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerThreats();}
};
class SRoleShowInfo: public Msg {
public:
int32_t roleId_;
int16_t career_;
int64_t combat_;
vector<dbs::TPlayerEquip> equips_;
vector<dbs::TPlayerItem> equipItems_;
string entityShows_;
string entityAttrs_;
int64_t devilDeadline_;
int64_t angelDeadline_;
int64_t decHurtDeadline_;
virtual inline int32_t msgId() const {return 1782;}
static int32_t MsgId() {return 1782;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRoleShowInfo();}
};
class SPlayerShowInfo: public Msg {
public:
msgs::SPublicPlayer publicPlayer_;
map<int32_t, SRoleShowInfo> roleMap_;
virtual inline int32_t msgId() const {return 1339;}
static int32_t MsgId() {return 1339;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerShowInfo();}
};
class SPlayerReviveInfo: public Msg {
public:
int32_t useFreeCount_;
virtual inline int32_t msgId() const {return 1472;}
static int32_t MsgId() {return 1472;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerReviveInfo();}
};
class SPlayerFighting: public Msg {
public:
bool isFighting_;
bool isPvpFighting_;
virtual inline int32_t msgId() const {return 1778;}
static int32_t MsgId() {return 1778;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerFighting();}
};
class SPlayerOpenServerGiftBag: public Msg {
public:
map<int32_t, bool> giftBags_;
virtual inline int32_t msgId() const {return 1873;}
static int32_t MsgId() {return 1873;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerOpenServerGiftBag();}
};
class SAddictionUpdate: public Msg {
public:
int32_t totalSec_;
virtual inline int32_t msgId() const {return 1911;}
static int32_t MsgId() {return 1911;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAddictionUpdate();}
};
class SRoleFightInfo: public Msg {
public:
int32_t roleId_;
int16_t career_;
int64_t combat_;
vector<int32_t> skills_;
vector<int32_t> buffs_;
map<int16_t, int32_t> entityShows_;
map<int16_t, int64_t> entityAttrs_;
virtual inline int32_t msgId() const {return 2011;}
static int32_t MsgId() {return 2011;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRoleFightInfo();}
};
class SPlayerFightInfo: public Msg {
public:
msgs::SPublicPlayer publicPlayer_;
map<int32_t, SRoleFightInfo> roleMap_;
virtual inline int32_t msgId() const {return 2012;}
static int32_t MsgId() {return 2012;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerFightInfo();}
};
class SPlayerLimitedGift: public Msg {
public:
map<int32_t, int32_t> buyTimes_;
virtual inline int32_t msgId() const {return 2076;}
static int32_t MsgId() {return 2076;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerLimitedGift();}
};
class SCardGroup: public Msg {
public:
map<int32_t, int32_t> activeNum_;
virtual inline int32_t msgId() const {return 2053;}
static int32_t MsgId() {return 2053;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCardGroup();}
};
class SDevilAngelRoleDate: public Msg {
public:
map<int32_t, int64_t> roleDate_;
virtual inline int32_t msgId() const {return 2131;}
static int32_t MsgId() {return 2131;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SDevilAngelRoleDate();}
};
class SDevilAngelDate: public Msg {
public:
map<int32_t, SDevilAngelRoleDate> devilAngelDate_;
virtual inline int32_t msgId() const {return 2107;}
static int32_t MsgId() {return 2107;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SDevilAngelDate();}
};
class SPlayerShareInfo: public Msg {
public:
int32_t count_;
vector<int32_t> getIndex_;
int64_t nextShareDt_;
virtual inline int32_t msgId() const {return 2386;}
static int32_t MsgId() {return 2386;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerShareInfo();}
};
class SPlayerWorshipData: public Msg {
public:
int32_t count_;
int64_t dt_;
virtual inline int32_t msgId() const {return 2789;}
static int32_t MsgId() {return 2789;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerWorshipData();}
};
class SPlayerFirstGroupBuy: public Msg {
public:
int32_t personNum_;
vector<int32_t> rewards_;
virtual inline int32_t msgId() const {return 3069;}
static int32_t MsgId() {return 3069;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerFirstGroupBuy();}
};
class SPlayerIDCardStatus: public Msg {
public:
int32_t status_;
virtual inline int32_t msgId() const {return 3258;}
static int32_t MsgId() {return 3258;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerIDCardStatus();}
};
class SPlayerOnlinePoint: public Msg {
public:
map<int32_t, int32_t> onlinePoints_;
virtual inline int32_t msgId() const {return 3796;}
static int32_t MsgId() {return 3796;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerOnlinePoint();}
};
class SPlayerBossBelong: public Msg {
public:
map<int32_t, int32_t> bossBlongTimes_;
virtual inline int32_t msgId() const {return 4010;}
static int32_t MsgId() {return 4010;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerBossBelong();}
};
class SPlayerUpdateBossBelong: public Msg {
public:
int32_t type_;
int32_t num_;
virtual inline int32_t msgId() const {return 4011;}
static int32_t MsgId() {return 4011;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerUpdateBossBelong();}
};
class SPlayerOfficialInfo: public Msg {
public:
bool isCross_;
int32_t officialLevel_;
int32_t maxOfficialLevel_;
int64_t endTime_;
bool isGotReward_;
virtual inline int32_t msgId() const {return 4078;}
static int32_t MsgId() {return 4078;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerOfficialInfo();}
};
class SPlayerMarryInvest: public Msg {
public:
int32_t fromPlayerId_;
int32_t toPlayerId_;
bool gotGetReward_;
bool gotSendReward_;
int64_t getEndTime_;
int64_t sendEndTime_;
int32_t dayRequestNum_;
virtual inline int32_t msgId() const {return 4198;}
static int32_t MsgId() {return 4198;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerMarryInvest();}
};
class SShareCopyExp: public Msg {
public:
map<int32_t, int32_t> todayShareMap_;
map<int32_t, int32_t> totalShareMap_;
map<int32_t, int32_t> vipShareMap_;
bool isVipShare_;
virtual inline int32_t msgId() const {return 4247;}
static int32_t MsgId() {return 4247;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SShareCopyExp();}
};
class SPlayerUpdateOrnaments: public Msg {
public:
map<int16_t, int32_t> ornaments_;
virtual inline int32_t msgId() const {return 4788;}
static int32_t MsgId() {return 4788;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerUpdateOrnaments();}
};
class SCenterGroupFightSingle: public Msg {
public:
msgs::SPublicPlayer publicPlayer_;
int32_t level_;
int32_t star_;
int32_t successCount_;
int32_t todayCount_;
int32_t lastWeekLevel_;
bool weekReward_;
bool weekTeamReward_;
bool weekRankReward_;
bool weekTeamRankReward_;
virtual inline int32_t msgId() const {return 4974;}
static int32_t MsgId() {return 4974;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCenterGroupFightSingle();}
};
class SCenterGroupFight: public Msg {
public:
string teamName_;
Identity captain_;
int32_t teamLevel_;
int32_t teamStar_;
int32_t lastWeekTeamLevel_;
vector<SCenterGroupFightSingle> partner_;
int64_t outDate_;
virtual inline int32_t msgId() const {return 4881;}
static int32_t MsgId() {return 4881;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCenterGroupFight();}
};
class SBoss: public Msg {
public:
int32_t bossId_;
int32_t copyCode_;
int64_t life_;
int64_t maxLife_;
int64_t refreshTime_;
string lastKillName_;
int64_t lastKillTime_;
int32_t line_;
int32_t playerNum_;
virtual inline int32_t msgId() const {return 1815;}
static int32_t MsgId() {return 1815;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBoss();}
};
class SRemoveBoss: public Msg {
public:
vector<int32_t> bossIds_;
int32_t line_;
int32_t type_;
virtual inline int32_t msgId() const {return 5381;}
static int32_t MsgId() {return 5381;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRemoveBoss();}
};
class SCompleteBoss: public msgs::SCompleteCopy {
public:
msgs::SMiniPlayer publicPlayer_;
Identity guildId_;
string guildName_;
vector<msgs::SItemAmount> rewards_;
Identity serverId_;
virtual inline int32_t msgId() const {return 1900;}
static int32_t MsgId() {return 1900;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteBoss();}
};
class SBossList: public Msg {
public:
int32_t type_;
vector<SBoss> seq_;
virtual inline int32_t msgId() const {return 1816;}
static int32_t MsgId() {return 1816;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBossList();}
};
class SWorldBossKillHis: public Msg {
public:
vector<dbs::TBossKillRecord> seq_;
virtual inline int32_t msgId() const {return 1318;}
static int32_t MsgId() {return 1318;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SWorldBossKillHis();}
};
class SVipBoss: public Msg {
public:
int32_t code_;
int64_t refreshTime_;
virtual inline int32_t msgId() const {return 1390;}
static int32_t MsgId() {return 1390;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SVipBoss();}
};
class SVipBossInfo: public Msg {
public:
int32_t code_;
vector<SVipBoss> seq_;
virtual inline int32_t msgId() const {return 1391;}
static int32_t MsgId() {return 1391;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SVipBossInfo();}
};
class SBossKillHis: public Msg {
public:
int32_t bossCode_;
vector<dbs::TBossKillRecord> seq_;
virtual inline int32_t msgId() const {return 1392;}
static int32_t MsgId() {return 1392;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBossKillHis();}
};
class SShiledBreak: public Msg {
public:
int32_t bossId_;
Identity entityId_;
int32_t diceId_;
int32_t shieldId_;
int64_t endTime_;
int32_t rewardId_;
virtual inline int32_t msgId() const {return 1882;}
static int32_t MsgId() {return 1882;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SShiledBreak();}
};
class SDiceResult: public Msg {
public:
msgs::SMiniPlayer belongPlayer_;
int32_t bossCode_;
int32_t diceNum_;
int32_t diceId_;
int32_t shieldId_;
virtual inline int32_t msgId() const {return 1883;}
static int32_t MsgId() {return 1883;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SDiceResult();}
};
class SPlayerBossHurt: public Msg {
public:
Identity entityId_;
string name_;
int64_t hurt_;
int32_t rank_;
virtual inline int32_t msgId() const {return 2042;}
static int32_t MsgId() {return 2042;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerBossHurt();}
};
class SBossHurtRank: public Msg {
public:
Identity bossEntityId_;
vector<SPlayerBossHurt> ranks_;
int32_t myRank_;
virtual inline int32_t msgId() const {return 2043;}
static int32_t MsgId() {return 2043;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBossHurtRank();}
};
class SCancelBelong: public Msg {
public:
Identity toEntityId_;
virtual inline int32_t msgId() const {return 2374;}
static int32_t MsgId() {return 2374;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCancelBelong();}
};
class SXianHunBelongNum: public Msg {
public:
int32_t belongNum_;
virtual inline int32_t msgId() const {return 2391;}
static int32_t MsgId() {return 2391;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SXianHunBelongNum();}
};
class SHunqiBoss: public Msg {
public:
int32_t copyCode_;
int32_t playerNum_;
int32_t bossNum_;
int32_t maxBossNum_;
int64_t refreshTime_;
virtual inline int32_t msgId() const {return 2397;}
static int32_t MsgId() {return 2397;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SHunqiBoss();}
};
class SHunqiBossList: public Msg {
public:
vector<SHunqiBoss> list_;
virtual inline int32_t msgId() const {return 2398;}
static int32_t MsgId() {return 2398;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SHunqiBossList();}
};
class SHunqiBossDetail: public Msg {
public:
int32_t bossCode_;
int64_t life_;
int64_t refreshTime_;
virtual inline int32_t msgId() const {return 2477;}
static int32_t MsgId() {return 2477;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SHunqiBossDetail();}
};
class SHunqiBossDetailList: public Msg {
public:
vector<SHunqiBossDetail> list_;
virtual inline int32_t msgId() const {return 2495;}
static int32_t MsgId() {return 2495;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SHunqiBossDetailList();}
};
class SHunqiCopyBoss: public Msg {
public:
int32_t bossCode_;
bool isLive_;
virtual inline int32_t msgId() const {return 2581;}
static int32_t MsgId() {return 2581;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SHunqiCopyBoss();}
};
class SHunqiCopyBossList: public Msg {
public:
vector<SHunqiCopyBoss> list_;
virtual inline int32_t msgId() const {return 2582;}
static int32_t MsgId() {return 2582;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SHunqiCopyBossList();}
};
class SGodMagic: public Msg {
public:
int32_t copyCode_;
int64_t liveTime_;
int64_t refreshTime_;
virtual inline int32_t msgId() const {return 2588;}
static int32_t MsgId() {return 2588;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGodMagic();}
};
class SGodMagicList: public Msg {
public:
vector<SGodMagic> list_;
virtual inline int32_t msgId() const {return 2589;}
static int32_t MsgId() {return 2589;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGodMagicList();}
};
class SGodMagicFlag: public Msg {
public:
int32_t monsterCode_;
int32_t flagId_;
int32_t plan_;
Identity belongId_;
Point flagPoint_;
virtual inline int32_t msgId() const {return 2607;}
static int32_t MsgId() {return 2607;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGodMagicFlag();}
};
class SGodMagicFlagList: public Msg {
public:
vector<SGodMagicFlag> list_;
virtual inline int32_t msgId() const {return 2608;}
static int32_t MsgId() {return 2608;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGodMagicFlagList();}
};
class SCompleteNeutralBoss: public SCompleteBoss {
public:
virtual inline int32_t msgId() const {return 2694;}
static int32_t MsgId() {return 2694;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteNeutralBoss();}
};
class SNeutralBossList: public Msg {
public:
map<int32_t, bool> lives_;
virtual inline int32_t msgId() const {return 2716;}
static int32_t MsgId() {return 2716;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SNeutralBossList();}
};
class SShieldRandomGiftUpdate: public Msg {
public:
int32_t diceId_;
int32_t leftNum_;
virtual inline int32_t msgId() const {return 3695;}
static int32_t MsgId() {return 3695;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SShieldRandomGiftUpdate();}
};
class SCompleteFourCityBoss: public msgs::SCompleteCopy {
public:
Identity serverId_;
vector<msgs::SItemAmount> belongRewards_;
vector<msgs::SItemAmount> rewards_;
int32_t rankReward_;
int32_t rank_;
int64_t hurt_;
virtual inline int32_t msgId() const {return 3781;}
static int32_t MsgId() {return 3781;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteFourCityBoss();}
};
class SCompleteFairylandBoss: public msgs::SCompleteCopy {
public:
int32_t star_;
int32_t type_;
int32_t subType_;
int32_t layer_;
int32_t useTime_;
virtual inline int32_t msgId() const {return 4585;}
static int32_t MsgId() {return 4585;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteFairylandBoss();}
};
class SMiracleIslandBoss: public Msg {
public:
int32_t copyCode_;
int32_t bossId_;
Identity serverId_;
int64_t refreshDt_;
virtual inline int32_t msgId() const {return 4649;}
static int32_t MsgId() {return 4649;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMiracleIslandBoss();}
};
class SMiracleIslandBossList: public Msg {
public:
vector<SMiracleIslandBoss> list_;
virtual inline int32_t msgId() const {return 4650;}
static int32_t MsgId() {return 4650;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMiracleIslandBossList();}
};
class SCompleteMiracleIslandBoss: public msgs::SCompleteCopy {
public:
int32_t bossId_;
int32_t isOwn_;
string ownName_;
msgs::SMiniPlayer publicPlayer_;
vector<msgs::SItemAmount> rewards_;
virtual inline int32_t msgId() const {return 4664;}
static int32_t MsgId() {return 4664;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteMiracleIslandBoss();}
};
class SFairylandEvaluate: public Msg {
public:
int64_t endTime_;
int32_t star_;
virtual inline int32_t msgId() const {return 4641;}
static int32_t MsgId() {return 4641;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFairylandEvaluate();}
};
class SFairylandBoss: public Msg {
public:
int32_t layer_;
map<int32_t, int32_t> hasGotReward_;
int32_t star_;
int32_t type_;
int32_t subtype_;
map<int32_t, int32_t> mops_;
int32_t lastLayer_;
virtual inline int32_t msgId() const {return 4653;}
static int32_t MsgId() {return 4653;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFairylandBoss();}
};
class SFairylandBossInfo: public Msg {
public:
vector<SFairylandBoss> layers_;
virtual inline int32_t msgId() const {return 4654;}
static int32_t MsgId() {return 4654;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFairylandBossInfo();}
};
class SLunHuiBossRank: public Msg {
public:
Identity playerId_;
int32_t rank_;
string name_;
int64_t hurt_;
virtual inline int32_t msgId() const {return 5334;}
static int32_t MsgId() {return 5334;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SLunHuiBossRank();}
};
class SCompleteLunHuiBoss: public SCompleteBoss {
public:
int32_t rank_;
int64_t hurt_;
vector<SLunHuiBossRank> ranks_;
virtual inline int32_t msgId() const {return 5335;}
static int32_t MsgId() {return 5335;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteLunHuiBoss();}
};
class SCompleteReincarnTowerBoss: public msgs::SCompleteCopy {
public:
int32_t openDay_;
int32_t layer_;
map<int32_t, int32_t> baseRewards_;
map<int32_t, int32_t> extraRewards_;
bool notRdExtra_;
int32_t duration_;
virtual inline int32_t msgId() const {return 5395;}
static int32_t MsgId() {return 5395;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteReincarnTowerBoss();}
};
class SRoleXianDan: public Msg {
public:
map<int32_t, int32_t> xianDanItem_;
map<int32_t, int32_t> xianDan_;
map<int32_t, int32_t> addValue_;
virtual inline int32_t msgId() const {return 5149;}
static int32_t MsgId() {return 5149;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRoleXianDan();}
};
class SXianDanInfo: public Msg {
public:
map<int32_t, SRoleXianDan> roleDanMap_;
virtual inline int32_t msgId() const {return 5150;}
static int32_t MsgId() {return 5150;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SXianDanInfo();}
};
class SChildFamilyInfo: public Msg {
public:
int64_t happyValue_;
int64_t happyLimit_;
map<int32_t, int32_t> building_;
map<int32_t, int32_t> events_;
int32_t freeCount_;
map<int32_t, int64_t> beginDts_;
int32_t stealCount_;
map<int32_t, int64_t> activeDts_;
virtual inline int32_t msgId() const {return 5340;}
static int32_t MsgId() {return 5340;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SChildFamilyInfo();}
};
class SChildFamilyRecord: public Msg {
public:
int32_t type_;
string playerName_;
string buildName_;
int64_t value_;
virtual inline int32_t msgId() const {return 5351;}
static int32_t MsgId() {return 5351;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SChildFamilyRecord();}
};
class SChildFamilyRecords: public Msg {
public:
vector<SChildFamilyRecord> lists_;
virtual inline int32_t msgId() const {return 5352;}
static int32_t MsgId() {return 5352;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SChildFamilyRecords();}
};
class SChildFamilySingle: public Msg {
public:
Identity playerId_;
string playerName_;
int64_t happyValue_;
int32_t buildingLevel_;
int32_t career_;
map<int32_t, int32_t> building_;
map<int32_t, int64_t> beginDts_;
virtual inline int32_t msgId() const {return 5355;}
static int32_t MsgId() {return 5355;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SChildFamilySingle();}
};
class SChildFamilyList: public Msg {
public:
vector<SChildFamilySingle> lists_;
virtual inline int32_t msgId() const {return 5356;}
static int32_t MsgId() {return 5356;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SChildFamilyList();}
};
class SChildFamilyGrow: public Msg {
public:
int32_t id_;
int32_t level_;
int32_t star_;
int64_t endTime_;
int64_t happy_;
int64_t activeDt_;
virtual inline int32_t msgId() const {return 5366;}
static int32_t MsgId() {return 5366;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SChildFamilyGrow();}
};
class SChildFamilyGrows: public Msg {
public:
map<int32_t, SChildFamilyGrow> maps_;
virtual inline int32_t msgId() const {return 5367;}
static int32_t MsgId() {return 5367;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SChildFamilyGrows();}
};
class SChildFamilyBesteal: public Msg {
public:
string playerName_;
int64_t stealValue_;
virtual inline int32_t msgId() const {return 5379;}
static int32_t MsgId() {return 5379;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SChildFamilyBesteal();}
};
class STrumpSingle: public Msg {
public:
int32_t needTime_;
virtual inline int32_t msgId() const {return 3360;}
static int32_t MsgId() {return 3360;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STrumpSingle();}
};
class STrumpInfo: public Msg {
public:
bool unlock_;
map<int32_t, bool> activeMap_;
map<int32_t, STrumpSingle> trumpMap_;
int32_t curFight_;
virtual inline int32_t msgId() const {return 1964;}
static int32_t MsgId() {return 1964;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STrumpInfo();}
};
class SPlayerSuperVip: public Msg {
public:
int32_t level_;
map<int32_t, bool> levelReward_;
map<int32_t, bool> weekReward_;
map<int32_t, bool> todayRechargeMap_;
map<int32_t, int32_t> copyCount_;
int32_t lastWeekLevel_;
virtual inline int32_t msgId() const {return 5011;}
static int32_t MsgId() {return 5011;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerSuperVip();}
};
class SActive: public dbs::TActive {
public:
int64_t openDt_;
int64_t closeDt_;
int64_t prepareDt_;
virtual inline int32_t msgId() const {return 1126;}
static int32_t MsgId() {return 1126;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActive();}
};
class SActiveList: public Msg {
public:
vector<SActive> activeLst_;
virtual inline int32_t msgId() const {return 1136;}
static int32_t MsgId() {return 1136;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveList();}
};
class SActiveUpdate: public Msg {
public:
int16_t status_;
SActive active_;
virtual inline int32_t msgId() const {return 1134;}
static int32_t MsgId() {return 1134;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveUpdate();}
};
class SActiveUpdateList: public Msg {
public:
vector<SActiveUpdate> actives_;
virtual inline int32_t msgId() const {return 1250;}
static int32_t MsgId() {return 1250;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveUpdateList();}
};
class SActiveTemplateInfo: public Msg {
public:
int32_t server_id_;
int32_t config_id_;
int64_t openDt_;
int64_t endDt_;
virtual inline int32_t msgId() const {return 2862;}
static int32_t MsgId() {return 2862;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveTemplateInfo();}
};
class SActiveTemplateList: public Msg {
public:
vector<SActiveTemplateInfo> activeList_;
virtual inline int32_t msgId() const {return 2141;}
static int32_t MsgId() {return 2141;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveTemplateList();}
};
class SActiveTemplateUpdate: public Msg {
public:
int32_t updateType_;
vector<SActiveTemplateInfo> updateList_;
virtual inline int32_t msgId() const {return 2142;}
static int32_t MsgId() {return 2142;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveTemplateUpdate();}
};
class SContinousTopUpRebateInfo: public Msg {
public:
int32_t activeId_;
vector<int32_t> getFlag_;
map<int32_t, int32_t> indexMap_;
virtual inline int32_t msgId() const {return 2127;}
static int32_t MsgId() {return 2127;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SContinousTopUpRebateInfo();}
};
class SAccumRechargeInfo: public Msg {
public:
int32_t activeId_;
int32_t rechaege_;
map<int32_t, bool> rewardGot_;
virtual inline int32_t msgId() const {return 2197;}
static int32_t MsgId() {return 2197;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAccumRechargeInfo();}
};
class SLoveTaskInfo: public Msg {
public:
int32_t activeId_;
bool hasGotReward_;
bool isComplete_;
virtual inline int32_t msgId() const {return 2739;}
static int32_t MsgId() {return 2739;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SLoveTaskInfo();}
};
class SActiveTargets: public Msg {
public:
int32_t activeId_;
map<int32_t, map<int32_t, int32_t> > mapValue_;
map<int32_t, int32_t> intValue_;
vector<int32_t> gotIndexs_;
vector<int32_t> gotDayIndex_;
virtual inline int32_t msgId() const {return 2860;}
static int32_t MsgId() {return 2860;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveTargets();}
};
class SActiveDayRecharge: public Msg {
public:
int32_t activeId_;
map<int32_t, bool> rewardGot_;
virtual inline int32_t msgId() const {return 2961;}
static int32_t MsgId() {return 2961;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveDayRecharge();}
};
class SActiveAccuConsume: public Msg {
public:
int32_t activeId_;
int32_t consume_;
map<int32_t, bool> rewardGot_;
virtual inline int32_t msgId() const {return 2962;}
static int32_t MsgId() {return 2962;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveAccuConsume();}
};
class SActiveDayConsume: public Msg {
public:
int32_t activeId_;
int32_t consume_;
map<int32_t, bool> rewardGot_;
virtual inline int32_t msgId() const {return 2963;}
static int32_t MsgId() {return 2963;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveDayConsume();}
};
class SContinousLogin: public Msg {
public:
int32_t activeId_;
map<int32_t, bool> rewardMap_;
int32_t loginDays_;
virtual inline int32_t msgId() const {return 2973;}
static int32_t MsgId() {return 2973;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SContinousLogin();}
};
class SActiveCompound: public Msg {
public:
int32_t activeId_;
map<int32_t, int32_t> countMap_;
virtual inline int32_t msgId() const {return 2983;}
static int32_t MsgId() {return 2983;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveCompound();}
};
class SActiveShareGame: public Msg {
public:
int32_t activeId_;
int32_t dayShareNum_;
int32_t totalShareNum_;
bool isGotDayReward_;
bool isGotTotolReward_;
virtual inline int32_t msgId() const {return 3043;}
static int32_t MsgId() {return 3043;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveShareGame();}
};
class SActiveQQVipDayGift: public Msg {
public:
int32_t activeId_;
int32_t vip_;
virtual inline int32_t msgId() const {return 3052;}
static int32_t MsgId() {return 3052;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveQQVipDayGift();}
};
class SActivePlatformReward: public Msg {
public:
int32_t activeId_;
vector<int32_t> fRewardGod_;
map<int32_t, bool> rewardGot_;
bool setZoneCover_;
virtual inline int32_t msgId() const {return 3049;}
static int32_t MsgId() {return 3049;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActivePlatformReward();}
};
class SActiveQQPetReward: public Msg {
public:
string values_;
map<int32_t, bool> rewardMap_;
virtual inline int32_t msgId() const {return 3056;}
static int32_t MsgId() {return 3056;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveQQPetReward();}
};
class SActiveTreasure: public Msg {
public:
int32_t activeId_;
virtual inline int32_t msgId() const {return 3159;}
static int32_t MsgId() {return 3159;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveTreasure();}
};
class SInviteFirend: public Msg {
public:
string name_;
int32_t career_;
string via_;
bool getReward_;
virtual inline int32_t msgId() const {return 3149;}
static int32_t MsgId() {return 3149;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SInviteFirend();}
};
class SInviteFriends: public Msg {
public:
vector<int32_t> targetIndexs_;
map<int32_t, SInviteFirend> friends_;
virtual inline int32_t msgId() const {return 3150;}
static int32_t MsgId() {return 3150;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SInviteFriends();}
};
class SInvteFriendRedPack: public Msg {
public:
string name_;
int32_t gold_;
virtual inline int32_t msgId() const {return 3151;}
static int32_t MsgId() {return 3151;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SInvteFriendRedPack();}
};
class SInvteFriendRedPacks: public Msg {
public:
vector<SInvteFriendRedPack> redPacks_;
virtual inline int32_t msgId() const {return 3152;}
static int32_t MsgId() {return 3152;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SInvteFriendRedPacks();}
};
class SInviteFriendHelp: public Msg {
public:
int32_t succNum_;
int32_t hasNum_;
virtual inline int32_t msgId() const {return 3354;}
static int32_t MsgId() {return 3354;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SInviteFriendHelp();}
};
class SShareLittleGame: public Msg {
public:
int32_t activeId_;
int32_t dayShare_;
int32_t totalShare_;
int64_t cd_;
map<int32_t, int32_t> dayRewardGot_;
map<int32_t, int32_t> rewardGot_;
virtual inline int32_t msgId() const {return 3180;}
static int32_t MsgId() {return 3180;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SShareLittleGame();}
};
class SActiveSecretSell: public Msg {
public:
int32_t activeId_;
map<int32_t, bool> sells_;
int64_t lastFlush_;
virtual inline int32_t msgId() const {return 3178;}
static int32_t MsgId() {return 3178;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveSecretSell();}
};
class SActiveRechargeTurntable: public Msg {
public:
int32_t activeId_;
int32_t totalRecharge_;
int32_t count_;
map<int32_t, bool> recordMap_;
virtual inline int32_t msgId() const {return 3183;}
static int32_t MsgId() {return 3183;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveRechargeTurntable();}
};
class SActiveConsumeTurntable: public Msg {
public:
int32_t activeId_;
int32_t totalConsume_;
int32_t count_;
map<int32_t, bool> recordMap_;
virtual inline int32_t msgId() const {return 3184;}
static int32_t MsgId() {return 3184;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveConsumeTurntable();}
};
class SActiveOneRecharge: public Msg {
public:
int32_t active_id_;
map<int32_t, int32_t> states_;
virtual inline int32_t msgId() const {return 3188;}
static int32_t MsgId() {return 3188;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveOneRecharge();}
};
class SActiveFlashSale: public Msg {
public:
int32_t active_id_;
map<int32_t, msgs::SIntIntPair> saleTimes_;
virtual inline int32_t msgId() const {return 3223;}
static int32_t MsgId() {return 3223;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveFlashSale();}
};
class SActiveExpRain: public Msg {
public:
int32_t per_;
virtual inline int32_t msgId() const {return 3285;}
static int32_t MsgId() {return 3285;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveExpRain();}
};
class SActiveDayRank: public Msg {
public:
int32_t activeId_;
int32_t toplistType_;
int32_t day_;
virtual inline int32_t msgId() const {return 3358;}
static int32_t MsgId() {return 3358;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveDayRank();}
};
class SWeekActive: public Msg {
public:
int32_t activeId_;
virtual inline int32_t msgId() const {return 3366;}
static int32_t MsgId() {return 3366;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SWeekActive();}
};
class STodayCombat: public Msg {
public:
int32_t activeId_;
map<int64_t, bool> gotRewardMap_;
virtual inline int32_t msgId() const {return 3433;}
static int32_t MsgId() {return 3433;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STodayCombat();}
};
class SActiveRechargeDoubleReset: public Msg {
public:
int32_t activeId_;
virtual inline int32_t msgId() const {return 3496;}
static int32_t MsgId() {return 3496;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveRechargeDoubleReset();}
};
class SActiveTask: public Msg {
public:
int32_t activeId_;
map<int32_t, int32_t> completeTimes_;
map<int32_t, int32_t> gotRewardTime_;
virtual inline int32_t msgId() const {return 3562;}
static int32_t MsgId() {return 3562;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveTask();}
};
class SActiveExchangeParty: public Msg {
public:
int32_t activeId_;
map<int32_t, int32_t> completeTimes_;
virtual inline int32_t msgId() const {return 3563;}
static int32_t MsgId() {return 3563;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveExchangeParty();}
};
class SActiveAccuRank: public Msg {
public:
int32_t activeId_;
int32_t toplistType_;
int32_t day_;
int64_t value_;
virtual inline int32_t msgId() const {return 3589;}
static int32_t MsgId() {return 3589;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveAccuRank();}
};
class SActiveAccuCombat: public Msg {
public:
int32_t activeId_;
int64_t combat_;
virtual inline int32_t msgId() const {return 3592;}
static int32_t MsgId() {return 3592;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveAccuCombat();}
};
class SActiveRedPacketInfo: public Msg {
public:
Identity playerId_;
map<int32_t, int32_t> info_;
virtual inline int32_t msgId() const {return 3623;}
static int32_t MsgId() {return 3623;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveRedPacketInfo();}
};
class SActiveRedPlayerShow: public Msg {
public:
int32_t career_;
string name_;
map<int16_t, int32_t> ornaments_;
int32_t itemId_;
int32_t num_;
virtual inline int32_t msgId() const {return 3644;}
static int32_t MsgId() {return 3644;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveRedPlayerShow();}
};
class SActivePlayerRedPacket: public Msg {
public:
Identity playerId_;
int32_t num_;
vector<msgs::SIntIntPair> itemsGot_;
vector<SActiveRedPlayerShow> show_;
msgs::SIntIntPair self_;
virtual inline int32_t msgId() const {return 3624;}
static int32_t MsgId() {return 3624;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActivePlayerRedPacket();}
};
class SActiveRedPacketShow: public Msg {
public:
vector<SActiveRedPlayerShow> show_;
virtual inline int32_t msgId() const {return 3762;}
static int32_t MsgId() {return 3762;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveRedPacketShow();}
};
class SActiveRechargeReturn: public Msg {
public:
int32_t activeId_;
map<int32_t, int32_t> rechargeReturn_;
virtual inline int32_t msgId() const {return 3744;}
static int32_t MsgId() {return 3744;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveRechargeReturn();}
};
class SActiveRedPacketAdd: public Msg {
public:
Identity playerId_;
map<int32_t, int32_t> items_;
virtual inline int32_t msgId() const {return 3753;}
static int32_t MsgId() {return 3753;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveRedPacketAdd();}
};
class SActiveOnlinePoint: public Msg {
public:
int32_t activeId_;
map<int32_t, int32_t> hasGotReward_;
virtual inline int32_t msgId() const {return 3798;}
static int32_t MsgId() {return 3798;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveOnlinePoint();}
};
class SActiveStrongestGuildData: public Msg {
public:
int32_t activeId_;
int32_t guildScore_;
int32_t selfScore_;
vector<int32_t> gols_;
virtual inline int32_t msgId() const {return 3817;}
static int32_t MsgId() {return 3817;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveStrongestGuildData();}
};
class SRedPacketRainGrabber: public Msg {
public:
int32_t itemId_;
int32_t itemNum_;
int32_t playerId_;
string playerName_;
int32_t career_;
map<int16_t, int32_t> ornaments_;
virtual inline int32_t msgId() const {return 4042;}
static int32_t MsgId() {return 4042;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRedPacketRainGrabber();}
};
class SRedPacketRainPacket: public Msg {
public:
int32_t redpacketId_;
int32_t splitNum_;
vector<SRedPacketRainGrabber> grabbers_;
virtual inline int32_t msgId() const {return 4043;}
static int32_t MsgId() {return 4043;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRedPacketRainPacket();}
};
class SActiveRedPacketRain: public Msg {
public:
int32_t activeId_;
int32_t index_;
int64_t endDt_;
vector<int32_t> grabbed_;
vector<SRedPacketRainPacket> packets_;
virtual inline int32_t msgId() const {return 4044;}
static int32_t MsgId() {return 4044;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveRedPacketRain();}
};
class SActiveRedPacketRainGrab: public Msg {
public:
int32_t activeId_;
int32_t index_;
int32_t redpacketIdx_;
int32_t itemId_;
int32_t itemNum_;
int32_t playerId_;
string playerName_;
int32_t career_;
virtual inline int32_t msgId() const {return 4054;}
static int32_t MsgId() {return 4054;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveRedPacketRainGrab();}
};
class SActiveTreasureRank: public Msg {
public:
int32_t activeId_;
int32_t treasureCount_;
virtual inline int32_t msgId() const {return 4058;}
static int32_t MsgId() {return 4058;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveTreasureRank();}
};
class SActiveTreasureTarget: public Msg {
public:
int32_t activeId_;
int32_t treasureCount_;
map<int32_t, int32_t> hasGotReward_;
virtual inline int32_t msgId() const {return 4059;}
static int32_t MsgId() {return 4059;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveTreasureTarget();}
};
class SScriptRewards: public Msg {
public:
int32_t activeId_;
string values_;
map<int32_t, bool> hasGotReward_;
virtual inline int32_t msgId() const {return 4147;}
static int32_t MsgId() {return 4147;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SScriptRewards();}
};
class SActiveInvest: public Msg {
public:
int32_t activeId_;
map<int32_t, map<int32_t, bool> > gotRewardMap_;
map<int32_t, int64_t> startTime_;
map<int32_t, int64_t> endTime_;
virtual inline int32_t msgId() const {return 4164;}
static int32_t MsgId() {return 4164;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveInvest();}
};
class SDirectBuyGift: public Msg {
public:
int32_t activeId_;
map<int32_t, int32_t> buyMap_;
map<int32_t, int32_t> gotRewardMap_;
map<int32_t, int32_t> dayRewardMap_;
map<int32_t, int32_t> discountMoney_;
map<int32_t, int32_t> dayRewardTotal_;
virtual inline int32_t msgId() const {return 4292;}
static int32_t MsgId() {return 4292;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SDirectBuyGift();}
};
class SGroupBuyGift: public Msg {
public:
int32_t activeId_;
map<int32_t, msgs::SInts> buyMap_;
map<int32_t, msgs::SIntIntMap> getMap_;
int32_t totalConsume_;
virtual inline int32_t msgId() const {return 4430;}
static int32_t MsgId() {return 4430;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGroupBuyGift();}
};
class SPlayerPuzzle: public Msg {
public:
int32_t activeId_;
int32_t lightCount_;
int32_t helpCount_;
map<int32_t, bool> isActive_;
virtual inline int32_t msgId() const {return 4558;}
static int32_t MsgId() {return 4558;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerPuzzle();}
};
class SPuzzleRecordSingle: public Msg {
public:
int64_t updateDt_;
string name_;
int32_t count_;
virtual inline int32_t msgId() const {return 4575;}
static int32_t MsgId() {return 4575;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPuzzleRecordSingle();}
};
class SPuzzleRecord: public Msg {
public:
int32_t activeId_;
vector<SPuzzleRecordSingle> records_;
virtual inline int32_t msgId() const {return 4574;}
static int32_t MsgId() {return 4574;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPuzzleRecord();}
};
class SActivePuzzleData: public Msg {
public:
int32_t activeId_;
int32_t puzzleId_;
map<int32_t, msgs::SIntBoolMap> puzzleMap_;
int32_t beHelpCount_;
SPuzzleRecord helpRecords_;
virtual inline int32_t msgId() const {return 4599;}
static int32_t MsgId() {return 4599;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActivePuzzleData();}
};
class SActiveZhiBaoTarget: public Msg {
public:
int32_t activeId_;
map<int32_t, int32_t> hasGotReward_;
virtual inline int32_t msgId() const {return 4671;}
static int32_t MsgId() {return 4671;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveZhiBaoTarget();}
};
class SKeepPrivilege: public Msg {
public:
int32_t activeId_;
int64_t endDt_;
map<string, bool> gotRewards_;
virtual inline int32_t msgId() const {return 4764;}
static int32_t MsgId() {return 4764;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SKeepPrivilege();}
};
class SActiveFreeTreasure: public Msg {
public:
int32_t activeId_;
vector<int32_t> selectTreasures_;
int32_t treasureCount_;
map<int32_t, int32_t> hasGotTarget_;
virtual inline int32_t msgId() const {return 4790;}
static int32_t MsgId() {return 4790;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveFreeTreasure();}
};
class SActiveRechargeBless: public Msg {
public:
int32_t activeId_;
vector<int32_t> rechargeMap_;
int32_t blessCount_;
int32_t curPer_;
int32_t totalCount_;
virtual inline int32_t msgId() const {return 4794;}
static int32_t MsgId() {return 4794;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveRechargeBless();}
};
class SActiveFlowerTreasure: public Msg {
public:
int32_t activeId_;
map<int32_t, bool> targetRewards_;
virtual inline int32_t msgId() const {return 4797;}
static int32_t MsgId() {return 4797;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveFlowerTreasure();}
};
class SActiveScrapeReward: public Msg {
public:
int32_t activeId_;
map<int32_t, int64_t> startTime_;
map<int32_t, msgs::SIntIntMap> numberMap_;
map<int32_t, msgs::SIntBoolMap> rewardMap_;
map<int32_t, int32_t> finalRewardNum_;
map<int32_t, int32_t> usedFreeNum_;
virtual inline int32_t msgId() const {return 4839;}
static int32_t MsgId() {return 4839;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveScrapeReward();}
};
class SActiveCallBack: public Msg {
public:
int32_t activeId_;
map<int32_t, int32_t> hasGotReward_;
int32_t totalRecharge_;
int32_t seqRechargeCount_;
int32_t backDay_;
map<int32_t, int32_t> callerHasGotReward_;
map<int32_t, int32_t> callerTotalRecharge_;
map<int32_t, int32_t> callerSeqRechargeCount_;
map<int32_t, int32_t> callerBackDay_;
int32_t callCount_;
virtual inline int32_t msgId() const {return 5052;}
static int32_t MsgId() {return 5052;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveCallBack();}
};
class SActiveSevenDayHigh: public Msg {
public:
int32_t activeId_;
map<int32_t, int32_t> dayRewards_;
map<int32_t, int32_t> targetRewards_;
int32_t day_;
map<int32_t, map<int32_t, int32_t> > mapValue_;
map<int32_t, int32_t> intValue_;
virtual inline int32_t msgId() const {return 5144;}
static int32_t MsgId() {return 5144;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveSevenDayHigh();}
};
class SCopyDropRateInfo: public Msg {
public:
map<int32_t, int32_t> rateMap_;
map<int32_t, int64_t> endTime_;
virtual inline int32_t msgId() const {return 5325;}
static int32_t MsgId() {return 5325;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCopyDropRateInfo();}
};
class SActiveTopicCollected: public Msg {
public:
int32_t activeId_;
map<int32_t, int32_t> targetRewards_;
map<int32_t, map<int32_t, int32_t> > mapValue_;
map<int32_t, int32_t> intValue_;
virtual inline int32_t msgId() const {return 5326;}
static int32_t MsgId() {return 5326;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveTopicCollected();}
};
class SActiveTripleTreasure: public Msg {
public:
int32_t activeId_;
map<int32_t, bool> activeMap_;
virtual inline int32_t msgId() const {return 5388;}
static int32_t MsgId() {return 5388;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SActiveTripleTreasure();}
};
class SPlayerDujieInfo: public Msg {
public:
int32_t level_;
int32_t rewardCount_;
int32_t timeCount_;
virtual inline int32_t msgId() const {return 5444;}
static int32_t MsgId() {return 5444;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerDujieInfo();}
};
class SPlayerBag: public Msg {
public:
int16_t type_;
int16_t privilegeNum_;
int16_t extendNum_;
int32_t extendMinute_;
virtual inline int32_t msgId() const {return 805;}
static int32_t MsgId() {return 805;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerBag();}
};
class SPlayerItem: public Msg {
public:
int64_t itemUid_;
int32_t itemId_;
int32_t itemNum_;
int16_t bagType_;
string extend_;
int64_t createDt_;
virtual inline int32_t msgId() const {return 806;}
static int32_t MsgId() {return 806;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerItem();}
};
class SPlayerBagList: public Msg {
public:
vector<SPlayerBag> bags_;
virtual inline int32_t msgId() const {return 268;}
static int32_t MsgId() {return 268;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerBagList();}
};
class SPlayerBagItemList: public Msg {
public:
int16_t bagType_;
vector<SPlayerItem> items_;
virtual inline int32_t msgId() const {return 269;}
static int32_t MsgId() {return 269;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerBagItemList();}
};
class SPlayerBagItemOper: public Msg {
public:
int16_t operType_;
int32_t operNum_;
SPlayerItem item_;
virtual inline int32_t msgId() const {return 270;}
static int32_t MsgId() {return 270;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerBagItemOper();}
};
class SPlayerBagItemOperList: public Msg {
public:
int16_t updateCode_;
vector<SPlayerBagItemOper> opers_;
virtual inline int32_t msgId() const {return 271;}
static int32_t MsgId() {return 271;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerBagItemOperList();}
};
class SPlayerMoneyList: public Msg {
public:
map<int32_t, int64_t> moneys_;
virtual inline int32_t msgId() const {return 272;}
static int32_t MsgId() {return 272;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerMoneyList();}
};
class SPlayerMoneyOper: public Msg {
public:
int16_t operType_;
int32_t operNum_;
int32_t moneyId_;
int64_t moneyNum_;
virtual inline int32_t msgId() const {return 273;}
static int32_t MsgId() {return 273;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerMoneyOper();}
};
class SPlayerMoneyOperList: public Msg {
public:
int16_t updateCode_;
vector<SPlayerMoneyOper> opers_;
virtual inline int32_t msgId() const {return 274;}
static int32_t MsgId() {return 274;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerMoneyOperList();}
};
class SPlayerConsume: public Msg {
public:
int32_t totalConsumeGold_;
int32_t todayConsumeGold_;
virtual inline int32_t msgId() const {return 1030;}
static int32_t MsgId() {return 1030;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerConsume();}
};
class SPlayerItemExpires: public Msg {
public:
vector<int32_t> items_;
virtual inline int32_t msgId() const {return 2603;}
static int32_t MsgId() {return 2603;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerItemExpires();}
};
class SPlayerEquipList: public Msg {
public:
vector<dbs::TPlayerEquip> equips_;
virtual inline int32_t msgId() const {return 1051;}
static int32_t MsgId() {return 1051;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerEquipList();}
};
class SPlayerGemTargets: public Msg {
public:
map<int32_t, map<int32_t, int32_t> > activateTargets_;
virtual inline int32_t msgId() const {return 1062;}
static int32_t MsgId() {return 1062;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerGemTargets();}
};
class SPlayerRefineTargets: public Msg {
public:
map<int32_t, map<int32_t, int32_t> > activateTargets_;
virtual inline int32_t msgId() const {return 4382;}
static int32_t MsgId() {return 4382;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerRefineTargets();}
};
class SCosmosRefineTargets: public Msg {
public:
map<int32_t, vector<int32_t> > targets_;
virtual inline int32_t msgId() const {return 4415;}
static int32_t MsgId() {return 4415;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCosmosRefineTargets();}
};
class SPlayerSuitCollects: public Msg {
public:
int32_t roleId_;
map<int32_t, map<int32_t, int32_t> > activeSuitCollect_;
map<int32_t, int32_t> unlockSuitCollect_;
virtual inline int32_t msgId() const {return 3082;}
static int32_t MsgId() {return 3082;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerSuitCollects();}
};
class SPlayerActiveSuitCollect: public Msg {
public:
int32_t roleId_;
int32_t suitId_;
vector<int32_t> activeSlots_;
virtual inline int32_t msgId() const {return 3083;}
static int32_t MsgId() {return 3083;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerActiveSuitCollect();}
};
class SPlayerUnlockSuitCollect: public Msg {
public:
int32_t roleId_;
int32_t suitId_;
virtual inline int32_t msgId() const {return 3084;}
static int32_t MsgId() {return 3084;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerUnlockSuitCollect();}
};
class SPlayerDressSuitCollect: public Msg {
public:
int32_t roleId_;
int32_t dressSuitId_;
virtual inline int32_t msgId() const {return 3090;}
static int32_t MsgId() {return 3090;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerDressSuitCollect();}
};
class SRingWash: public Msg {
public:
int32_t index_;
int32_t bless_;
int32_t targetLevel_;
map<int32_t, int32_t> holes_;
map<int32_t, int32_t> tmpHoles_;
virtual inline int32_t msgId() const {return 4716;}
static int32_t MsgId() {return 4716;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRingWash();}
};
class SPlayerRingWash: public Msg {
public:
map<int32_t, SRingWash> ringWashes_;
virtual inline int32_t msgId() const {return 4712;}
static int32_t MsgId() {return 4712;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerRingWash();}
};
class SPlayerReincarnMark: public Msg {
public:
map<int32_t, msgs::SIntIntMap> maps_;
virtual inline int32_t msgId() const {return 5432;}
static int32_t MsgId() {return 5432;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerReincarnMark();}
};
class SPlayerAvatar: public Msg {
public:
int32_t avatarId_;
int32_t exp_;
int32_t avatarStar_;
int32_t level_;
int32_t star_;
int64_t initDt_;
virtual inline int32_t msgId() const {return 4203;}
static int32_t MsgId() {return 4203;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerAvatar();}
};
class SPlayerAvatarInfo: public Msg {
public:
vector<SPlayerAvatar> avatars_;
virtual inline int32_t msgId() const {return 4204;}
static int32_t MsgId() {return 4204;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerAvatarInfo();}
};
class SAvatarTrump: public Msg {
public:
int32_t status_;
int32_t advance_;
map<int32_t, int32_t> posAdv_;
vector<int32_t> activeAvd_;
bool activeCore_;
virtual inline int32_t msgId() const {return 4224;}
static int32_t MsgId() {return 4224;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAvatarTrump();}
};
class SAvatarTrumpInfo: public Msg {
public:
int32_t puton_;
map<int32_t, SAvatarTrump> trumps_;
virtual inline int32_t msgId() const {return 4225;}
static int32_t MsgId() {return 4225;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAvatarTrumpInfo();}
};
class SAvatarHangInfo: public Msg {
public:
int32_t hangId_;
virtual inline int32_t msgId() const {return 4266;}
static int32_t MsgId() {return 4266;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAvatarHangInfo();}
};
class SDragonSoulSingle: public Msg {
public:
int32_t id_;
int32_t level_;
int32_t star_;
bool out_;
virtual inline int32_t msgId() const {return 3296;}
static int32_t MsgId() {return 3296;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SDragonSoulSingle();}
};
class SDragonSoulInfo: public Msg {
public:
map<int32_t, SDragonSoulSingle> dsMap_;
int32_t outNum_;
map<int32_t, bool> target_;
virtual inline int32_t msgId() const {return 3297;}
static int32_t MsgId() {return 3297;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SDragonSoulInfo();}
};
class SShopInfo: public Msg {
public:
map<int32_t, int32_t> limitSellsDay_;
map<int32_t, int32_t> limitSellsWeek_;
map<int32_t, int32_t> limitSellsForever_;
map<int32_t, int32_t> limitSellsWeekActive_;
virtual inline int32_t msgId() const {return 483;}
static int32_t MsgId() {return 483;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SShopInfo();}
};
class SPlayerShanHai: public Msg {
public:
map<int32_t, int32_t> activeCollects_;
virtual inline int32_t msgId() const {return 4694;}
static int32_t MsgId() {return 4694;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerShanHai();}
};
class SXiuXianHole: public Msg {
public:
int32_t layer_;
int32_t playerNum_;
bool isActive_;
virtual inline int32_t msgId() const {return 5091;}
static int32_t MsgId() {return 5091;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SXiuXianHole();}
};
class SXiuXianHoleList: public Msg {
public:
vector<SXiuXianHole> list_;
virtual inline int32_t msgId() const {return 5092;}
static int32_t MsgId() {return 5092;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SXiuXianHoleList();}
};
class SXiuXianHoleResult: public msgs::SCompleteCopy {
public:
virtual inline int32_t msgId() const {return 5113;}
static int32_t MsgId() {return 5113;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SXiuXianHoleResult();}
};
class SXiuXianHoleBagItemList: public Msg {
public:
map<int32_t, int32_t> itemList_;
virtual inline int32_t msgId() const {return 5115;}
static int32_t MsgId() {return 5115;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SXiuXianHoleBagItemList();}
};
class SXiuXianHoleFuDi: public Msg {
public:
int32_t pointId_;
Identity entityId_;
string name_;
int64_t combat_;
int64_t protectDt_;
virtual inline int32_t msgId() const {return 5121;}
static int32_t MsgId() {return 5121;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SXiuXianHoleFuDi();}
};
class SXiuXianHoleFuDiList: public Msg {
public:
vector<SXiuXianHoleFuDi> list_;
virtual inline int32_t msgId() const {return 5122;}
static int32_t MsgId() {return 5122;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SXiuXianHoleFuDiList();}
};
class SXiuXianHoleRankList: public Msg {
public:
vector<dbs::TXiuXianHoleRank> list_;
int32_t xianYuan_;
virtual inline int32_t msgId() const {return 5127;}
static int32_t MsgId() {return 5127;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SXiuXianHoleRankList();}
};
class SXiuXianHoleCopyInfo: public Msg {
public:
int32_t layer_;
int32_t playerNum_;
int64_t doubleEndDt_;
int32_t holdId_;
int32_t leftDouble_;
virtual inline int32_t msgId() const {return 5128;}
static int32_t MsgId() {return 5128;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SXiuXianHoleCopyInfo();}
};
class SXiuxianInfo: public Msg {
public:
int32_t level_;
int32_t star_;
int32_t gotLevel_;
map<int32_t, int32_t> itemCount_;
vector<int32_t> targets_;
virtual inline int32_t msgId() const {return 3218;}
static int32_t MsgId() {return 3218;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SXiuxianInfo();}
};
class SXiuxianGem: public Msg {
public:
int32_t item_;
int32_t level_;
virtual inline int32_t msgId() const {return 3875;}
static int32_t MsgId() {return 3875;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SXiuxianGem();}
};
class SXiuxianGemInfo: public Msg {
public:
map<int32_t, map<int32_t, SXiuxianGem> > gemMap_;
virtual inline int32_t msgId() const {return 3880;}
static int32_t MsgId() {return 3880;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SXiuxianGemInfo();}
};
class SMarryRequest: public Msg {
public:
msgs::SMiniPlayer player_;
int32_t type_;
virtual inline int32_t msgId() const {return 2673;}
static int32_t MsgId() {return 2673;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMarryRequest();}
};
class SMarryRespone: public Msg {
public:
string name_;
int32_t result_;
virtual inline int32_t msgId() const {return 2704;}
static int32_t MsgId() {return 2704;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMarryRespone();}
};
class SPlayerMarry: public Msg {
public:
int32_t marryId_;
int64_t marryDt_;
msgs::SMiniPlayer mate_;
int32_t divorceId_;
int64_t divorceDt_;
virtual inline int32_t msgId() const {return 2674;}
static int32_t MsgId() {return 2674;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerMarry();}
};
class SPlayerWedding: public Msg {
public:
int32_t marryId_;
int32_t weddingStatus_;
int64_t bookDt_;
int32_t guestNum_;
int32_t weddingCount_;
virtual inline int32_t msgId() const {return 2675;}
static int32_t MsgId() {return 2675;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerWedding();}
};
class SGatePlayerMarry: public Msg {
public:
bool mateOnline_;
int32_t matelockLevel_;
int64_t mateAttack_;
map<int32_t, int32_t> myReqNum_;
map<int32_t, int32_t> mateReqNum_;
Msg* marry_;
Msg* wedding_;
virtual inline int32_t msgId() const {return 2802;}
static int32_t MsgId() {return 2802;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGatePlayerMarry();}
};
class SPlayerMarryRequestInfo: public Msg {
public:
map<int32_t, int32_t> myReqNum_;
virtual inline int32_t msgId() const {return 2960;}
static int32_t MsgId() {return 2960;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerMarryRequestInfo();}
};
class SWeddingBookList: public Msg {
public:
vector<int32_t> bookDts_;
virtual inline int32_t msgId() const {return 2677;}
static int32_t MsgId() {return 2677;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SWeddingBookList();}
};
class SWeddingGuest: public Msg {
public:
map<int32_t, string> guestList_;
virtual inline int32_t msgId() const {return 2732;}
static int32_t MsgId() {return 2732;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SWeddingGuest();}
};
class SWeddingGuestUpdate: public Msg {
public:
map<int32_t, string> addGuests_;
virtual inline int32_t msgId() const {return 2733;}
static int32_t MsgId() {return 2733;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SWeddingGuestUpdate();}
};
class SWeddingPreGuest: public Msg {
public:
map<int32_t, string> prGuestList_;
virtual inline int32_t msgId() const {return 2734;}
static int32_t MsgId() {return 2734;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SWeddingPreGuest();}
};
class SWeddingPreGuestUpdate: public Msg {
public:
int32_t oper_;
int32_t playerId_;
string name_;
virtual inline int32_t msgId() const {return 2735;}
static int32_t MsgId() {return 2735;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SWeddingPreGuestUpdate();}
};
class SEnterWedding: public Msg {
public:
int32_t marryId_;
msgs::SMiniPlayer man_;
msgs::SMiniPlayer woman_;
int32_t weddingStage_;
int64_t beginDt_;
int32_t hotValue_;
int32_t collectCount_;
virtual inline int32_t msgId() const {return 2785;}
static int32_t MsgId() {return 2785;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEnterWedding();}
};
class SCompleteFoodLove: public msgs::SCompleteCopy {
public:
int32_t level_;
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 4761;}
static int32_t MsgId() {return 4761;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteFoodLove();}
};
class SFoodLoveInfo: public Msg {
public:
int32_t level_;
virtual inline int32_t msgId() const {return 4773;}
static int32_t MsgId() {return 4773;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFoodLoveInfo();}
};
class SPlayerPetFetter: public Msg {
public:
vector<int32_t> activesFetter_;
virtual inline int32_t msgId() const {return 1152;}
static int32_t MsgId() {return 1152;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerPetFetter();}
};
class SPlayerNewPetInfo: public Msg {
public:
int32_t petHurt_;
int32_t marryPetHurt_;
int32_t mengPetHurt_;
vector<dbs::TPlayerNewPet> pets_;
virtual inline int32_t msgId() const {return 1844;}
static int32_t MsgId() {return 1844;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerNewPetInfo();}
};
class SPlayerPetFormateInfo: public Msg {
public:
vector<dbs::TPlayerPetFormate> formates_;
virtual inline int32_t msgId() const {return 3140;}
static int32_t MsgId() {return 3140;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerPetFormateInfo();}
};
class SPetAssistInfo: public Msg {
public:
vector<int32_t> petAssist_;
virtual inline int32_t msgId() const {return 3467;}
static int32_t MsgId() {return 3467;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPetAssistInfo();}
};
class SPetTryInfo: public Msg {
public:
int32_t tryPetId_;
int64_t tryDeadline_;
virtual inline int32_t msgId() const {return 3778;}
static int32_t MsgId() {return 3778;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPetTryInfo();}
};
class SPlayFirework: public Msg {
public:
int32_t livelyValue_;
virtual inline int32_t msgId() const {return 3643;}
static int32_t MsgId() {return 3643;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayFirework();}
};
class SLivelyBossCreate: public Msg {
public:
int32_t group_;
int32_t bossId_;
virtual inline int32_t msgId() const {return 3662;}
static int32_t MsgId() {return 3662;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SLivelyBossCreate();}
};
class SLivelyBossDead: public Msg {
public:
int32_t group_;
int32_t bossId_;
string belongName_;
int32_t belongCarrer_;
map<int16_t, int32_t> belongOrnaments_;
virtual inline int32_t msgId() const {return 3663;}
static int32_t MsgId() {return 3663;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SLivelyBossDead();}
};
class SLivelyValue: public Msg {
public:
int32_t group_;
int32_t livelyValue_;
int32_t bossCurValue_;
bool bossIsAlive_;
map<int32_t, int32_t> redPacketId_;
virtual inline int32_t msgId() const {return 3672;}
static int32_t MsgId() {return 3672;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SLivelyValue();}
};
class SLivelyBossDrop: public Msg {
public:
int32_t group_;
int32_t bossId_;
virtual inline int32_t msgId() const {return 3748;}
static int32_t MsgId() {return 3748;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SLivelyBossDrop();}
};
class STotemInfo: public Msg {
public:
map<int32_t, int32_t> totemMap_;
virtual inline int32_t msgId() const {return 4238;}
static int32_t MsgId() {return 4238;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STotemInfo();}
};
class SPlayerHolyBeast: public Msg {
public:
vector<dbs::TPlayerHolyBeast> list_;
virtual inline int32_t msgId() const {return 4908;}
static int32_t MsgId() {return 4908;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerHolyBeast();}
};
class SPlayerHolyBeastGoOut: public Msg {
public:
map<int32_t, int32_t> goOuts_;
bool isGoOut_;
virtual inline int32_t msgId() const {return 4943;}
static int32_t MsgId() {return 4943;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerHolyBeastGoOut();}
};
class SApplyHolyBeastBreed: public Msg {
public:
int32_t applyPlayerId_;
string applyName_;
int32_t applyModelId_;
int32_t applyTalent_;
int32_t applyLevel_;
int32_t applyRaitry_;
virtual inline int32_t msgId() const {return 5003;}
static int32_t MsgId() {return 5003;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SApplyHolyBeastBreed();}
};
class SConfirmHolyBeastBreed: public Msg {
public:
int32_t otherPlayerId_;
int32_t otherModelId_;
string otherName_;
int32_t otherTalent_;
int32_t beastId_;
virtual inline int32_t msgId() const {return 5009;}
static int32_t MsgId() {return 5009;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SConfirmHolyBeastBreed();}
};
class SBreedHolyBeastPlayers: public Msg {
public:
vector<msgs::SMiniPlayer> list_;
virtual inline int32_t msgId() const {return 5027;}
static int32_t MsgId() {return 5027;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBreedHolyBeastPlayers();}
};
class SRedPacketInfo: public Msg {
public:
int32_t grabNum_;
int32_t grabNumPrivate_;
int32_t numForRecharge_;
int32_t giveForRecharge_;
int32_t giveForPrivate_;
int32_t numForMonth_;
map<int32_t, int32_t> grabNumBosses_;
virtual inline int32_t msgId() const {return 1369;}
static int32_t MsgId() {return 1369;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRedPacketInfo();}
};
class SRedPacket: public dbs::TRedPacket {
public:
virtual inline int32_t msgId() const {return 1497;}
static int32_t MsgId() {return 1497;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRedPacket();}
};
class SRedPacketList: public Msg {
public:
vector<SRedPacket> list_;
virtual inline int32_t msgId() const {return 1833;}
static int32_t MsgId() {return 1833;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRedPacketList();}
};
class SRedPacketGrab: public Msg {
public:
int32_t redPacketId_;
int32_t playerId_;
string playerName_;
int32_t moneyId_;
int32_t moneyNum_;
virtual inline int32_t msgId() const {return 1849;}
static int32_t MsgId() {return 1849;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRedPacketGrab();}
};
class SPlayerUpdateTalent: public Msg {
public:
int32_t roleId_;
int32_t type_;
int32_t num_;
int32_t point_;
virtual inline int32_t msgId() const {return 3943;}
static int32_t MsgId() {return 3943;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerUpdateTalent();}
};
class SPlayerTalentInfo: public Msg {
public:
int32_t roleId_;
map<int32_t, int32_t> talents_;
map<int32_t, int32_t> talentsPoints_;
virtual inline int32_t msgId() const {return 3944;}
static int32_t MsgId() {return 3944;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerTalentInfo();}
};
class SPlayerZhenFa: public Msg {
public:
int32_t id_;
virtual inline int32_t msgId() const {return 5070;}
static int32_t MsgId() {return 5070;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerZhenFa();}
};
class SPlayerZhenWeiSkill: public Msg {
public:
int32_t id_;
int32_t star_;
int32_t level_;
virtual inline int32_t msgId() const {return 5071;}
static int32_t MsgId() {return 5071;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerZhenWeiSkill();}
};
class SPlayerZhenFaExtend: public Msg {
public:
int32_t activeLoginDay_;
int32_t activeRechargeDay_;
vector<SPlayerZhenFa> zhenfaList_;
vector<SPlayerZhenWeiSkill> zhenweiSkillList_;
virtual inline int32_t msgId() const {return 5072;}
static int32_t MsgId() {return 5072;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerZhenFaExtend();}
};
class SPlayerUseZhenFaExtend: public Msg {
public:
int32_t useZhanfaId_;
map<int32_t, map<int32_t, int32_t> > zhanweis_;
map<int32_t, map<int32_t, int32_t> > zhanweiskills_;
virtual inline int32_t msgId() const {return 5073;}
static int32_t MsgId() {return 5073;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerUseZhenFaExtend();}
};
class SXianWu: public Msg {
public:
int32_t id_;
int32_t level_;
virtual inline int32_t msgId() const {return 3900;}
static int32_t MsgId() {return 3900;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SXianWu();}
};
class SPlayerXianWuInfo: public Msg {
public:
vector<SXianWu> seq_;
virtual inline int32_t msgId() const {return 3901;}
static int32_t MsgId() {return 3901;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerXianWuInfo();}
};
class SPlayerDressXianWu: public Msg {
public:
int32_t dressId_;
virtual inline int32_t msgId() const {return 3916;}
static int32_t MsgId() {return 3916;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerDressXianWu();}
};
class SToplist: public Msg {
public:
vector<int32_t> crossTypes_;
int32_t toplistType_;
int32_t version_;
vector<dbs::TToplist> records_;
virtual inline int32_t msgId() const {return 742;}
static int32_t MsgId() {return 742;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SToplist();}
};
class SToplistVersionUpdate: public Msg {
public:
map<int32_t, int32_t> versions_;
virtual inline int32_t msgId() const {return 1793;}
static int32_t MsgId() {return 1793;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SToplistVersionUpdate();}
};
class SAchievementCopy: public Msg {
public:
map<int32_t, int32_t> copyInfo_;
virtual inline int32_t msgId() const {return 1518;}
static int32_t MsgId() {return 1518;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAchievementCopy();}
};
class SFlyChessSingle: public Msg {
public:
int32_t pos_;
int32_t freeCount_;
int32_t resetCount_;
vector<int32_t> route_;
int32_t buyCount_;
virtual inline int32_t msgId() const {return 3975;}
static int32_t MsgId() {return 3975;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFlyChessSingle();}
};
class SFlyChess: public Msg {
public:
map<int32_t, SFlyChessSingle> flyChessMap_;
virtual inline int32_t msgId() const {return 3971;}
static int32_t MsgId() {return 3971;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFlyChess();}
};
class SFlyChessEnd: public Msg {
public:
map<int32_t, int32_t> totalRewards_;
virtual inline int32_t msgId() const {return 3987;}
static int32_t MsgId() {return 3987;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFlyChessEnd();}
};
class SAdvance: public Msg {
public:
int32_t type_;
int32_t roleId_;
int32_t star_;
int32_t level_;
int32_t lastDayLevel_;
int32_t bless_;
int32_t tmpBless_;
int32_t modelId_;
map<int32_t, int32_t> dan_;
virtual inline int32_t msgId() const {return 530;}
static int32_t MsgId() {return 530;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAdvance();}
};
class SAdvanceUpdate: public Msg {
public:
int32_t type_;
int32_t roleId_;
int32_t star_;
int32_t level_;
int32_t lastDayLevel_;
int32_t bless_;
int32_t tmpBless_;
int32_t modelId_;
virtual inline int32_t msgId() const {return 543;}
static int32_t MsgId() {return 543;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAdvanceUpdate();}
};
class SAdvanceDanUpdate: public Msg {
public:
int32_t roleId_;
int32_t type_;
int32_t danType_;
int32_t num_;
virtual inline int32_t msgId() const {return 544;}
static int32_t MsgId() {return 544;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAdvanceDanUpdate();}
};
class SPlayerAdvanceInfo: public Msg {
public:
vector<SAdvance> advances_;
virtual inline int32_t msgId() const {return 516;}
static int32_t MsgId() {return 516;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerAdvanceInfo();}
};
class SAdvanceAwaken: public Msg {
public:
int32_t roleId_;
int32_t type_;
int32_t level_;
int32_t star_;
virtual inline int32_t msgId() const {return 3102;}
static int32_t MsgId() {return 3102;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAdvanceAwaken();}
};
class SPlayerAdvanceAwakenInfo: public Msg {
public:
vector<SAdvanceAwaken> awakens_;
virtual inline int32_t msgId() const {return 3103;}
static int32_t MsgId() {return 3103;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerAdvanceAwakenInfo();}
};
class SAdvanceAwakenUpdate: public Msg {
public:
int32_t roleId_;
int32_t type_;
int32_t level_;
int32_t star_;
virtual inline int32_t msgId() const {return 3104;}
static int32_t MsgId() {return 3104;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAdvanceAwakenUpdate();}
};
class SPlayerGuardList: public Msg {
public:
vector<dbs::TPlayerGuard> guards_;
virtual inline int32_t msgId() const {return 1557;}
static int32_t MsgId() {return 1557;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerGuardList();}
};
class SPlayerGuardExInfo: public Msg {
public:
int32_t score_;
virtual inline int32_t msgId() const {return 2922;}
static int32_t MsgId() {return 2922;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerGuardExInfo();}
};
class SGuardItem: public Msg {
public:
int32_t id_;
int32_t itemId_;
string itemExtend_;
virtual inline int32_t msgId() const {return 2923;}
static int32_t MsgId() {return 2923;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuardItem();}
};
class SGuardItemRecord: public Msg {
public:
int32_t playerId_;
string playerName_;
int32_t oper_;
int32_t id_;
int32_t itemId_;
string itemExtend_;
int64_t recordDt_;
virtual inline int32_t msgId() const {return 2924;}
static int32_t MsgId() {return 2924;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuardItemRecord();}
};
class SAdvanceDayInfo: public Msg {
public:
map<int32_t, bool> isGotRewards_;
virtual inline int32_t msgId() const {return 3559;}
static int32_t MsgId() {return 3559;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAdvanceDayInfo();}
};
class SZhanlingInfo: public Msg {
public:
int32_t dai_;
int32_t mission_;
int64_t deadline_;
int32_t adv_;
map<int32_t, int32_t> advance_;
virtual inline int32_t msgId() const {return 1896;}
static int32_t MsgId() {return 1896;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SZhanlingInfo();}
};
class SFashion: public Msg {
public:
int32_t level_;
int32_t promoteLevel_;
int32_t bless_;
int32_t dian_;
int64_t deadDt_;
virtual inline int32_t msgId() const {return 2786;}
static int32_t MsgId() {return 2786;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFashion();}
};
class SFashionInfo: public Msg {
public:
int32_t puton_;
map<int32_t, SFashion> fashions_;
virtual inline int32_t msgId() const {return 2045;}
static int32_t MsgId() {return 2045;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFashionInfo();}
};
class SRoleFashionInfo: public Msg {
public:
map<int32_t, msgs::SInts> suits_;
map<int32_t, SFashionInfo> roleFashion_;
map<int32_t, msgs::SIntBoolMap> roleItem_;
virtual inline int32_t msgId() const {return 2049;}
static int32_t MsgId() {return 2049;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRoleFashionInfo();}
};
class SPlayerFashionInfo: public Msg {
public:
map<int32_t, SRoleFashionInfo> playerFashion_;
virtual inline int32_t msgId() const {return 1559;}
static int32_t MsgId() {return 1559;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerFashionInfo();}
};
class SSendFashion: public Msg {
public:
Identity fromId_;
string fromName_;
int32_t fashionId_;
virtual inline int32_t msgId() const {return 4112;}
static int32_t MsgId() {return 4112;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SSendFashion();}
};
class SPlayerSignFourteenDay: public Msg {
public:
int32_t index_;
int32_t gotIndex_;
virtual inline int32_t msgId() const {return 1406;}
static int32_t MsgId() {return 1406;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerSignFourteenDay();}
};
class SPlayerSignEveryDay: public Msg {
public:
int32_t freeCount_;
int32_t todayIsSign_;
int32_t signNum_;
vector<int32_t> targetGots_;
virtual inline int32_t msgId() const {return 1383;}
static int32_t MsgId() {return 1383;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerSignEveryDay();}
};
class SMarryTrialInfo: public Msg {
public:
int32_t level_;
map<int32_t, bool> skillMap_;
virtual inline int32_t msgId() const {return 2767;}
static int32_t MsgId() {return 2767;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMarryTrialInfo();}
};
class SMarryTrialMateInfo: public Msg {
public:
int32_t level_;
virtual inline int32_t msgId() const {return 2819;}
static int32_t MsgId() {return 2819;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMarryTrialMateInfo();}
};
class SMarryTrialStatusUpdate: public Msg {
public:
bool isMarry_;
Identity playerA_;
Identity playerB_;
virtual inline int32_t msgId() const {return 4007;}
static int32_t MsgId() {return 4007;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMarryTrialStatusUpdate();}
};
class SDailyActivityInfo: public Msg {
public:
int32_t activity_;
map<int32_t, int32_t> hadGetRewards_;
int32_t levelLimit_;
int32_t carrerLevelLimit_;
map<int32_t, int32_t> getActCnt_;
map<int32_t, int32_t> getActivity_;
int32_t weekActivity_;
int32_t weekLevelLimit_;
int32_t weekCarrerLevelLimit_;
virtual inline int32_t msgId() const {return 1158;}
static int32_t MsgId() {return 1158;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SDailyActivityInfo();}
};
class SMagicSingle: public Msg {
public:
map<int32_t, int32_t> isOpenHole_;
virtual inline int32_t msgId() const {return 1812;}
static int32_t MsgId() {return 1812;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMagicSingle();}
};
class SMagicInfo: public Msg {
public:
map<int32_t, SMagicSingle> roleHole_;
int32_t magicCopyLayer_;
virtual inline int32_t msgId() const {return 1359;}
static int32_t MsgId() {return 1359;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMagicInfo();}
};
class SHorcruxeSingle: public Msg {
public:
bool isActive_;
int32_t type_;
int32_t subtype_;
int32_t star_;
int32_t level_;
map<int32_t, int32_t> fulPer_;
int32_t fulNum_;
virtual inline int32_t msgId() const {return 2402;}
static int32_t MsgId() {return 2402;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SHorcruxeSingle();}
};
class SHorcruxeTypeMap: public Msg {
public:
map<int32_t, SHorcruxeSingle> horcruxeMap_;
virtual inline int32_t msgId() const {return 2497;}
static int32_t MsgId() {return 2497;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SHorcruxeTypeMap();}
};
class SHorcruxeInfo: public Msg {
public:
map<int32_t, SHorcruxeTypeMap> horcruxeTypeMap_;
virtual inline int32_t msgId() const {return 2403;}
static int32_t MsgId() {return 2403;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SHorcruxeInfo();}
};
class SMiniMail: public Msg {
public:
int32_t id_;
string sender_;
string title_;
int64_t mailDt_;
bool isRead_;
bool hasAttach_;
virtual inline int32_t msgId() const {return 431;}
static int32_t MsgId() {return 431;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMiniMail();}
};
class SNotifyMailboxStatus: public Msg {
public:
bool notRead_;
bool hasAttach_;
virtual inline int32_t msgId() const {return 448;}
static int32_t MsgId() {return 448;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SNotifyMailboxStatus();}
};
class SNotifyNewMail: public Msg {
public:
vector<SMiniMail> list_;
virtual inline int32_t msgId() const {return 432;}
static int32_t MsgId() {return 432;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SNotifyNewMail();}
};
class SNotifyDelMail: public Msg {
public:
int32_t id_;
virtual inline int32_t msgId() const {return 897;}
static int32_t MsgId() {return 897;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SNotifyDelMail();}
};
class SAddMail: public Msg {
public:
int32_t updateCode_;
string updateStr_;
Identity entityId_;
dbs::TMail mail_;
virtual inline int32_t msgId() const {return 1228;}
static int32_t MsgId() {return 1228;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAddMail();}
};
class SChatMsg: public Msg {
public:
int16_t channel_;
msgs::SMiniPlayer fromPlayer_;
string content_;
string extend_;
virtual inline int32_t msgId() const {return 594;}
static int32_t MsgId() {return 594;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SChatMsg();}
};
class SChatInfo: public Msg {
public:
int32_t freeHorn_;
int32_t hornNum_;
int64_t feedbackDt_;
virtual inline int32_t msgId() const {return 1897;}
static int32_t MsgId() {return 1897;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SChatInfo();}
};
class SOpenServerTargetInfo: public Msg {
public:
map<int32_t, int32_t> isGetReward_;
map<int32_t, bool> bossKill_;
map<int32_t, int32_t> godPlaneKill_;
map<int32_t, int32_t> vipBossKill_;
virtual inline int32_t msgId() const {return 1598;}
static int32_t MsgId() {return 1598;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SOpenServerTargetInfo();}
};
class SOpenServerTreasure: public Msg {
public:
map<int32_t, int32_t> treasureCount_;
virtual inline int32_t msgId() const {return 3380;}
static int32_t MsgId() {return 3380;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SOpenServerTreasure();}
};
class SOpenServerTargetCounter: public Msg {
public:
map<int32_t, int32_t> rewardCounter_;
virtual inline int32_t msgId() const {return 2958;}
static int32_t MsgId() {return 2958;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SOpenServerTargetCounter();}
};
class SOpenServerAdvanceCounter: public Msg {
public:
map<int32_t, int32_t> counter_;
virtual inline int32_t msgId() const {return 3075;}
static int32_t MsgId() {return 3075;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SOpenServerAdvanceCounter();}
};
class SZeroGiftInfo: public Msg {
public:
map<int32_t, int32_t> dayRecharge_;
map<int32_t, map<int32_t, bool> > gotRewards_;
virtual inline int32_t msgId() const {return 3740;}
static int32_t MsgId() {return 3740;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SZeroGiftInfo();}
};
class SBroadcastContent: public Msg {
public:
int32_t broadcastId_;
vector<string> params_;
int32_t proxyId_;
virtual inline int32_t msgId() const {return 1105;}
static int32_t MsgId() {return 1105;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBroadcastContent();}
};
class SSystemNotify: public Msg {
public:
int32_t type_;
string content_;
bool isFloat_;
int16_t minLevel_;
vector<string> gameChannels_;
virtual inline int32_t msgId() const {return 1106;}
static int32_t MsgId() {return 1106;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SSystemNotify();}
};
class SPlayerHelp: public Msg {
public:
Identity entityId_;
int64_t combat_;
int32_t count_;
int32_t career_;
map<int16_t, int32_t> ornaments_;
string name_;
bool entrust_;
virtual inline int32_t msgId() const {return 4603;}
static int32_t MsgId() {return 4603;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerHelp();}
};
class SPlayerHelpOwn: public Msg {
public:
SPlayerHelp helpPlayer_;
SPlayerHelp beHelpPlayer_;
virtual inline int32_t msgId() const {return 4604;}
static int32_t MsgId() {return 4604;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerHelpOwn();}
};
class SPlayerMiracleIslandInfo: public Msg {
public:
int32_t copyCount_;
int32_t helpCount_;
int32_t beHelpCount_;
bool helpOthter_;
virtual inline int32_t msgId() const {return 4605;}
static int32_t MsgId() {return 4605;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerMiracleIslandInfo();}
};
class SMiracleIslandRankItem: public Msg {
public:
Identity serverId_;
int32_t killNum_;
virtual inline int32_t msgId() const {return 4607;}
static int32_t MsgId() {return 4607;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMiracleIslandRankItem();}
};
class SMiracleBossReward: public Msg {
public:
Identity entityId_;
int32_t career_;
int32_t isOwn_;
string name_;
map<int32_t, int32_t> reward_;
virtual inline int32_t msgId() const {return 4663;}
static int32_t MsgId() {return 4663;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMiracleBossReward();}
};
class SMiracleBossPlayerData: public Msg {
public:
Identity entityId_;
int32_t copyCount_;
int32_t helpCount_;
string helpName_;
virtual inline int32_t msgId() const {return 4667;}
static int32_t MsgId() {return 4667;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMiracleBossPlayerData();}
};
class SMarket: public dbs::TDbMarket {
public:
Identity entityId_;
virtual inline int32_t msgId() const {return 709;}
static int32_t MsgId() {return 709;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMarket();}
};
class SMarketInfo: public Msg {
public:
int32_t page_;
int32_t totalPage_;
vector<SMarket> seq_;
virtual inline int32_t msgId() const {return 710;}
static int32_t MsgId() {return 710;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMarketInfo();}
};
class SMarketHis: public dbs::TMarketHis {
public:
Identity entityId_;
virtual inline int32_t msgId() const {return 2665;}
static int32_t MsgId() {return 2665;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMarketHis();}
};
class SMarketHisInfo: public Msg {
public:
vector<SMarketHis> seq_;
virtual inline int32_t msgId() const {return 1204;}
static int32_t MsgId() {return 1204;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMarketHisInfo();}
};
class SPlayerAutoDrop: public Msg {
public:
Identity belongEntityId_;
Point dropPoint_;
vector<msgs::SItemAmount> items_;
int32_t type_;
virtual inline int32_t msgId() const {return 1765;}
static int32_t MsgId() {return 1765;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerAutoDrop();}
};
class SLianYao: public Msg {
public:
int32_t id_;
int32_t level_;
int32_t star_;
virtual inline int32_t msgId() const {return 3723;}
static int32_t MsgId() {return 3723;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SLianYao();}
};
class SPlayerLianYaoInfo: public Msg {
public:
vector<SLianYao> seq_;
virtual inline int32_t msgId() const {return 3724;}
static int32_t MsgId() {return 3724;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerLianYaoInfo();}
};
class SMonthCardSingle: public Msg {
public:
int32_t buyDate_;
map<int32_t, bool> dayRewardMap_;
virtual inline int32_t msgId() const {return 2115;}
static int32_t MsgId() {return 2115;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMonthCardSingle();}
};
class SMonthCardInfo: public Msg {
public:
map<int32_t, SMonthCardSingle> cards_;
virtual inline int32_t msgId() const {return 2116;}
static int32_t MsgId() {return 2116;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMonthCardInfo();}
};
class SMonthCardSingle2: public Msg {
public:
int64_t beginDt_;
int64_t endDt_;
map<int32_t, bool> dayRewardMap_;
int32_t versionCount_;
virtual inline int32_t msgId() const {return 4681;}
static int32_t MsgId() {return 4681;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMonthCardSingle2();}
};
class SMonthCardInfo2: public Msg {
public:
map<int32_t, SMonthCardSingle2> cards_;
virtual inline int32_t msgId() const {return 4682;}
static int32_t MsgId() {return 4682;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMonthCardInfo2();}
};
class SBuyMonthCard: public Msg {
public:
int32_t type_;
virtual inline int32_t msgId() const {return 3378;}
static int32_t MsgId() {return 3378;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBuyMonthCard();}
};
class SMonthCardReBuy: public Msg {
public:
int32_t activeId_;
map<int32_t, int32_t> reBuyMap_;
virtual inline int32_t msgId() const {return 4679;}
static int32_t MsgId() {return 4679;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMonthCardReBuy();}
};
class SHangLevelBoss: public Msg {
public:
int32_t bossId_;
Point point_;
virtual inline int32_t msgId() const {return 1734;}
static int32_t MsgId() {return 1734;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SHangLevelBoss();}
};
class SHangBossPass: public Msg {
public:
int32_t result_;
int32_t newHangLevel_;
virtual inline int32_t msgId() const {return 1744;}
static int32_t MsgId() {return 1744;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SHangBossPass();}
};
class SHangBossResult: public Msg {
public:
int32_t result_;
int32_t newHangLevel_;
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 1741;}
static int32_t MsgId() {return 1741;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SHangBossResult();}
};
class SHangPower: public Msg {
public:
int32_t power_;
virtual inline int32_t msgId() const {return 1748;}
static int32_t MsgId() {return 1748;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SHangPower();}
};
class SHangOfflineReward: public Msg {
public:
int64_t exp_;
int32_t coin_;
int32_t decomposeNum_;
int64_t offlineTime_;
map<int32_t, int32_t> rewards_;
int32_t type_;
virtual inline int32_t msgId() const {return 1776;}
static int32_t MsgId() {return 1776;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SHangOfflineReward();}
};
class SHangResetPoint: public Msg {
public:
int32_t hang_;
vector<Point> toPoints_;
virtual inline int32_t msgId() const {return 2168;}
static int32_t MsgId() {return 2168;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SHangResetPoint();}
};
class SFeaturesReward: public Msg {
public:
map<int32_t, bool> getReward_;
virtual inline int32_t msgId() const {return 2217;}
static int32_t MsgId() {return 2217;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFeaturesReward();}
};
class SGuildWarGuildInfo: public Msg {
public:
string guildName_;
int32_t guildPlayerNum_;
int32_t score_;
virtual inline int32_t msgId() const {return 2158;}
static int32_t MsgId() {return 2158;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildWarGuildInfo();}
};
class SGuildWarPlayerInfo: public Msg {
public:
int32_t exploits_;
int32_t score_;
int32_t gotTargetId_;
virtual inline int32_t msgId() const {return 2159;}
static int32_t MsgId() {return 2159;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildWarPlayerInfo();}
};
class SGuildWarAddScore: public Msg {
public:
int32_t addScore_;
string killName_;
int32_t monsterCode_;
virtual inline int32_t msgId() const {return 2160;}
static int32_t MsgId() {return 2160;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildWarAddScore();}
};
class SGuildWarResult: public Msg {
public:
bool success_;
Identity placeGuildId_;
string placeGuildName_;
string placeLeaderName_;
string myGuildName_;
int32_t myGuildScore_;
int32_t myGuildRank_;
map<int32_t, int32_t> myGuildRewards_;
int32_t myScore_;
int32_t myRank_;
map<int32_t, int32_t> myRewards_;
virtual inline int32_t msgId() const {return 2161;}
static int32_t MsgId() {return 2161;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildWarResult();}
};
class SGuildWarFlagInfo: public Msg {
public:
int32_t status_;
int64_t endTime_;
Identity playerId_;
string name_;
Identity guildId_;
string guildName_;
virtual inline int32_t msgId() const {return 2163;}
static int32_t MsgId() {return 2163;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildWarFlagInfo();}
};
class SGuildWarGuildRankReward: public Msg {
public:
Identity guildId_;
map<int32_t, int32_t> rewards_;
map<int32_t, int32_t> hasGots_;
virtual inline int32_t msgId() const {return 2190;}
static int32_t MsgId() {return 2190;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildWarGuildRankReward();}
};
class SGuildWarGuildRank: public Msg {
public:
int32_t guildId_;
string guildName_;
string leaderName_;
int32_t score_;
virtual inline int32_t msgId() const {return 2204;}
static int32_t MsgId() {return 2204;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildWarGuildRank();}
};
class SGuildWarPlayerRank: public Msg {
public:
int32_t playerId_;
string name_;
int32_t guildId_;
string guildName_;
int32_t score_;
virtual inline int32_t msgId() const {return 2205;}
static int32_t MsgId() {return 2205;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildWarPlayerRank();}
};
class SGuildWarGuildRankList: public Msg {
public:
vector<SGuildWarGuildRank> guildRanks_;
virtual inline int32_t msgId() const {return 2211;}
static int32_t MsgId() {return 2211;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildWarGuildRankList();}
};
class SGuildWarPlayerRankList: public Msg {
public:
vector<SGuildWarPlayerRank> playerRanks_;
virtual inline int32_t msgId() const {return 2212;}
static int32_t MsgId() {return 2212;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildWarPlayerRankList();}
};
class SGuildWarPlayerData: public Msg {
public:
bool gotDayReward_;
virtual inline int32_t msgId() const {return 2283;}
static int32_t MsgId() {return 2283;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildWarPlayerData();}
};
class SGuildWarPrePlaceInfo: public Msg {
public:
Identity guildId_;
string guildName_;
Identity playerId_;
virtual inline int32_t msgId() const {return 2530;}
static int32_t MsgId() {return 2530;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGuildWarPrePlaceInfo();}
};
class SServerTerritoryInfo: public Msg {
public:
map<int32_t, int32_t> territoryReward_;
int32_t hasGotPlaceRank_;
int32_t hasGotKillRank_;
int32_t placeRank_;
int32_t killRank_;
virtual inline int32_t msgId() const {return 3605;}
static int32_t MsgId() {return 3605;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SServerTerritoryInfo();}
};
class SServerTerritoryCopyInfo: public Msg {
public:
int32_t targetId_;
int32_t score_;
int32_t killNum_;
int32_t feats_;
int32_t killTower_;
virtual inline int32_t msgId() const {return 3640;}
static int32_t MsgId() {return 3640;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SServerTerritoryCopyInfo();}
};
class SServerTerritoryFightInfo: public Msg {
public:
Identity attackId_;
vector<int32_t> attackePlace_;
Identity defenseId_;
vector<int32_t> defensePlace_;
bool hasFight_;
bool isEnd_;
virtual inline int32_t msgId() const {return 3647;}
static int32_t MsgId() {return 3647;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SServerTerritoryFightInfo();}
};
class SServerTerritoryResult: public msgs::SCompleteCopy {
public:
bool isAttacker_;
int32_t territory_;
int32_t delTerritory_;
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 3654;}
static int32_t MsgId() {return 3654;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SServerTerritoryResult();}
};
class SServerTerritoryCenterResult: public Msg {
public:
Identity centerId_;
int32_t result_;
virtual inline int32_t msgId() const {return 3655;}
static int32_t MsgId() {return 3655;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SServerTerritoryCenterResult();}
};
class SServerTerritoryUpdatePlace: public Msg {
public:
Identity centerId_;
int64_t activeCombat_;
vector<int32_t> territorys_;
virtual inline int32_t msgId() const {return 3666;}
static int32_t MsgId() {return 3666;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SServerTerritoryUpdatePlace();}
};
class SServerTerritoryTower: public Msg {
public:
map<string, int32_t> towers_;
virtual inline int32_t msgId() const {return 3668;}
static int32_t MsgId() {return 3668;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SServerTerritoryTower();}
};
class SCrossFightsStatus: public Msg {
public:
int32_t status_;
int32_t regStatus_;
int64_t endTime_;
int32_t stage_;
int32_t successCount_;
virtual inline int32_t msgId() const {return 3835;}
static int32_t MsgId() {return 3835;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCrossFightsStatus();}
};
class SCrossFightsInfo: public Msg {
public:
int32_t score_;
int32_t targetId_;
int32_t lifeCount_;
int64_t beginLiveTime_;
int32_t roomLevel_;
virtual inline int32_t msgId() const {return 3845;}
static int32_t MsgId() {return 3845;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCrossFightsInfo();}
};
class SCrossFightsRank: public Msg {
public:
Identity playerId_;
string name_;
int32_t lifeCount_;
int32_t score_;
int32_t isFailed_;
virtual inline int32_t msgId() const {return 3846;}
static int32_t MsgId() {return 3846;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCrossFightsRank();}
};
class SCrossFightsRankList: public Msg {
public:
vector<SCrossFightsRank> ranks_;
virtual inline int32_t msgId() const {return 3847;}
static int32_t MsgId() {return 3847;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCrossFightsRankList();}
};
class SCrossFightsKill: public Msg {
public:
string fromName_;
string toName_;
int32_t killNum_;
int32_t fromCareer_;
int32_t toCareer_;
map<int16_t, int32_t> fromOrnaments_;
map<int16_t, int32_t> toOrnaments_;
virtual inline int32_t msgId() const {return 3851;}
static int32_t MsgId() {return 3851;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCrossFightsKill();}
};
class SCompleteCrossFights: public msgs::SCompleteCopy {
public:
map<int32_t, int32_t> rewards_;
vector<SCrossFightsRank> ranks_;
virtual inline int32_t msgId() const {return 3852;}
static int32_t MsgId() {return 3852;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCompleteCrossFights();}
};
class SShuraWar: public Msg {
public:
map<int32_t, int32_t> tasks_;
map<int32_t, int32_t> completeTasks_;
int32_t star_;
bool killKing_;
int32_t killNum_;
int32_t beKillNum_;
virtual inline int32_t msgId() const {return 4386;}
static int32_t MsgId() {return 4386;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SShuraWar();}
};
class SShuraBoss: public Msg {
public:
int32_t bossId_;
int64_t refreshTime_;
virtual inline int32_t msgId() const {return 4426;}
static int32_t MsgId() {return 4426;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SShuraBoss();}
};
class SShuraBossInfo: public Msg {
public:
vector<SShuraBoss> littleBoss_;
bool bigBossAlive_;
virtual inline int32_t msgId() const {return 4427;}
static int32_t MsgId() {return 4427;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SShuraBossInfo();}
};
class SShuraWarScore: public Msg {
public:
Identity playerId_;
string name_;
int32_t score_;
virtual inline int32_t msgId() const {return 4698;}
static int32_t MsgId() {return 4698;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SShuraWarScore();}
};
class SShuraWarScoreRank: public Msg {
public:
vector<SShuraWarScore> ranks_;
virtual inline int32_t msgId() const {return 4699;}
static int32_t MsgId() {return 4699;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SShuraWarScoreRank();}
};
class SShuraWarSeqKill: public Msg {
public:
Identity entityId_;
string name_;
int16_t career_;
map<int16_t, int32_t> ornaments_;
int16_t killNum_;
virtual inline int32_t msgId() const {return 4701;}
static int32_t MsgId() {return 4701;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SShuraWarSeqKill();}
};
class SPlayerTitle: public Msg {
public:
int32_t titleId_;
int64_t indateTime_;
virtual inline int32_t msgId() const {return 1075;}
static int32_t MsgId() {return 1075;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerTitle();}
};
class SPlayerTitleInfo: public Msg {
public:
vector<SPlayerTitle> titles_;
virtual inline int32_t msgId() const {return 1076;}
static int32_t MsgId() {return 1076;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerTitleInfo();}
};
class SPlayerTouxianInfo: public Msg {
public:
int32_t touxianId_;
int32_t feat_;
virtual inline int32_t msgId() const {return 1086;}
static int32_t MsgId() {return 1086;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerTouxianInfo();}
};
class SFourGod: public Msg {
public:
int32_t status_;
int32_t advance_;
map<int32_t, int32_t> dan_;
vector<int32_t> suitLevel_;
virtual inline int32_t msgId() const {return 3963;}
static int32_t MsgId() {return 3963;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFourGod();}
};
class SFourGodInfo: public Msg {
public:
map<int32_t, SFourGod> fgs_;
virtual inline int32_t msgId() const {return 3964;}
static int32_t MsgId() {return 3964;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFourGodInfo();}
};
class SPlayerVipInfo: public Msg {
public:
int32_t level_;
map<int32_t, int32_t> gotReward_;
int32_t weekReward_;
map<int32_t, int32_t> fakeGotReward_;
bool isFake_;
virtual inline int32_t msgId() const {return 845;}
static int32_t MsgId() {return 845;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerVipInfo();}
};
class SOneYuanTreasureSingle: public Msg {
public:
int32_t activeType_;
int32_t id_;
int32_t status_;
int64_t startTime_;
int64_t endTime_;
int32_t hadBuyCount_;
map<string, int32_t> buyCountMap_;
string winPlayerName_;
virtual inline int32_t msgId() const {return 3826;}
static int32_t MsgId() {return 3826;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SOneYuanTreasureSingle();}
};
class SOneYuanTreasure: public Msg {
public:
int32_t activeType_;
map<int32_t, SOneYuanTreasureSingle> statusMap_;
virtual inline int32_t msgId() const {return 3827;}
static int32_t MsgId() {return 3827;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SOneYuanTreasure();}
};
class SOneYuanTreasureRecordSingle: public Msg {
public:
int64_t openTime_;
string name_;
bool spike_;
int32_t itemId_;
int32_t itemNum_;
int32_t buyNum_;
bool isWinner_;
virtual inline int32_t msgId() const {return 3828;}
static int32_t MsgId() {return 3828;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SOneYuanTreasureRecordSingle();}
};
class SOneYuanTreasureRecord: public Msg {
public:
vector<SOneYuanTreasureRecordSingle> records_;
virtual inline int32_t msgId() const {return 3829;}
static int32_t MsgId() {return 3829;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SOneYuanTreasureRecord();}
};
class SOneYuanTreasureTarget: public Msg {
public:
map<int32_t, bool> gotRewardMap_;
int32_t totalCount_;
virtual inline int32_t msgId() const {return 3830;}
static int32_t MsgId() {return 3830;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SOneYuanTreasureTarget();}
};
class SOneYuanTreasurePlayer: public Msg {
public:
Identity entityId_;
int32_t historyCount_;
string playerName_;
virtual inline int32_t msgId() const {return 3955;}
static int32_t MsgId() {return 3955;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SOneYuanTreasurePlayer();}
};
class SOneYuanTreasureEndInfo: public Msg {
public:
map<Identity, bool> spikeMap_;
int32_t itemId_;
int32_t itemNum_;
int64_t endTime_;
map<Identity, int32_t> buyCountMap_;
Identity winEntityId_;
virtual inline int32_t msgId() const {return 3958;}
static int32_t MsgId() {return 3958;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SOneYuanTreasureEndInfo();}
};
class SNearEnemy: public Msg {
public:
int32_t playerId_;
string name_;
int32_t career_;
int32_t level_;
int32_t career_level_;
map<int16_t, int32_t> ornaments_;
virtual inline int32_t msgId() const {return 2150;}
static int32_t MsgId() {return 2150;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SNearEnemy();}
};
class SNearEnemyInfo: public Msg {
public:
int32_t zhangong_;
int32_t shalu_;
int32_t totalKill_;
vector<SNearEnemy> enemys_;
virtual inline int32_t msgId() const {return 2151;}
static int32_t MsgId() {return 2151;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SNearEnemyInfo();}
};
class SNearEnemyResult: public Msg {
public:
int32_t succ_;
int32_t hangLevel_;
int32_t enemyId_;
vector<msgs::SItemAmount> rewards_;
virtual inline int32_t msgId() const {return 2170;}
static int32_t MsgId() {return 2170;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SNearEnemyResult();}
};
class SSoulSingle: public Msg {
public:
map<int32_t, int32_t> isOpenHole_;
virtual inline int32_t msgId() const {return 2230;}
static int32_t MsgId() {return 2230;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SSoulSingle();}
};
class SSoulInfo: public Msg {
public:
map<int32_t, SSoulSingle> roleHole_;
virtual inline int32_t msgId() const {return 2231;}
static int32_t MsgId() {return 2231;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SSoulInfo();}
};
class SCheats: public Msg {
public:
int32_t itemId_;
int32_t isLock_;
virtual inline int32_t msgId() const {return 3483;}
static int32_t MsgId() {return 3483;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCheats();}
};
class SPlayerCheats: public Msg {
public:
vector<SCheats> cheats_;
int32_t roleId_;
virtual inline int32_t msgId() const {return 3484;}
static int32_t MsgId() {return 3484;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerCheats();}
};
class SUpdateCheats: public Msg {
public:
int32_t index_;
int32_t itemId_;
int32_t isLock_;
int32_t roleId_;
virtual inline int32_t msgId() const {return 3738;}
static int32_t MsgId() {return 3738;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SUpdateCheats();}
};
class SShenqiInfo: public Msg {
public:
int32_t cur_shenqi_;
vector<int32_t> actived_pieces_;
virtual inline int32_t msgId() const {return 1768;}
static int32_t MsgId() {return 1768;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SShenqiInfo();}
};
class SPlayerWsGodRing: public Msg {
public:
int32_t attackLevel_;
int32_t defenseLevel_;
virtual inline int32_t msgId() const {return 2775;}
static int32_t MsgId() {return 2775;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerWsGodRing();}
};
class SZhiBaoSingle: public Msg {
public:
int32_t level_;
int32_t star_;
int32_t bless_;
int32_t target_;
map<int32_t, int32_t> danMap_;
virtual inline int32_t msgId() const {return 4625;}
static int32_t MsgId() {return 4625;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SZhiBaoSingle();}
};
class SZhiBaoInfo: public Msg {
public:
map<int32_t, SZhiBaoSingle> maps_;
virtual inline int32_t msgId() const {return 4626;}
static int32_t MsgId() {return 4626;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SZhiBaoInfo();}
};
class SVersionReward: public Msg {
public:
bool isGotReward_;
virtual inline int32_t msgId() const {return 2202;}
static int32_t MsgId() {return 2202;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SVersionReward();}
};
class SPlayerOnlineReward: public Msg {
public:
int32_t onlineTime_;
map<int32_t, int32_t> hasGotReward_;
virtual inline int32_t msgId() const {return 1568;}
static int32_t MsgId() {return 1568;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerOnlineReward();}
};
class SPlayerCallInfo: public Msg {
public:
int32_t isBeCall_;
int32_t isSetCaller_;
int64_t backDt_;
map<int32_t, int32_t> hasGotReward_;
virtual inline int32_t msgId() const {return 4255;}
static int32_t MsgId() {return 4255;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerCallInfo();}
};
class SCountryGold: public Msg {
public:
int32_t countryGold_;
int32_t point0Gold_;
Identity serverId_;
virtual inline int32_t msgId() const {return 4497;}
static int32_t MsgId() {return 4497;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCountryGold();}
};
class SAddCountryGold: public Msg {
public:
int32_t type_;
int32_t gold_;
vector<string> params_;
virtual inline int32_t msgId() const {return 4486;}
static int32_t MsgId() {return 4486;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SAddCountryGold();}
};
class SDelCountryGold: public Msg {
public:
int32_t type_;
int32_t gold_;
vector<string> params_;
virtual inline int32_t msgId() const {return 4492;}
static int32_t MsgId() {return 4492;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SDelCountryGold();}
};
class SPlayerCountryGold: public Msg {
public:
int32_t hasGotSalary_;
virtual inline int32_t msgId() const {return 4491;}
static int32_t MsgId() {return 4491;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerCountryGold();}
};
class SCutTree: public Msg {
public:
int32_t type_;
int32_t itemId_;
int32_t life_;
int32_t maxLife_;
Identity belongId_;
string belongName_;
int64_t refreshTime_;
virtual inline int32_t msgId() const {return 4589;}
static int32_t MsgId() {return 4589;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCutTree();}
};
class SCutTreeInfo: public Msg {
public:
vector<SCutTree> trees_;
virtual inline int32_t msgId() const {return 4590;}
static int32_t MsgId() {return 4590;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SCutTreeInfo();}
};
class SBless: public Msg {
public:
int32_t type_;
int32_t targetCount_;
int64_t freeCd_;
int32_t useMoneyCount_;
virtual inline int32_t msgId() const {return 4707;}
static int32_t MsgId() {return 4707;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SBless();}
};
class SPlayerBless: public Msg {
public:
map<int32_t, SBless> blesses_;
virtual inline int32_t msgId() const {return 4708;}
static int32_t MsgId() {return 4708;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerBless();}
};
class SLunHuiBook: public Msg {
public:
int64_t preDt_;
int32_t preSeqDays_;
int64_t beginDt_;
map<int32_t, int32_t> hasGot_;
map<int32_t, int32_t> hasGotMulCount_;
int32_t useVipCount_;
virtual inline int32_t msgId() const {return 5436;}
static int32_t MsgId() {return 5436;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SLunHuiBook();}
};
class STransport: public Msg {
public:
int32_t type_;
int32_t missionCount_;
int32_t refreshCount_;
int32_t leftCount_;
int32_t fightEscort_;
virtual inline int32_t msgId() const {return 2663;}
static int32_t MsgId() {return 2663;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STransport();}
};
class SEscortMissionFailed: public Msg {
public:
Identity entityId_;
string fightName_;
int32_t configId_;
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 4753;}
static int32_t MsgId() {return 4753;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEscortMissionFailed();}
};
class SFightEscortSuccess: public Msg {
public:
int32_t configId_;
map<int32_t, int32_t> rewards_;
virtual inline int32_t msgId() const {return 4754;}
static int32_t MsgId() {return 4754;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SFightEscortSuccess();}
};
class SGetBackRewardSingle: public Msg {
public:
int32_t round_;
map<int32_t, int32_t> items_;
int64_t exp_;
virtual inline int32_t msgId() const {return 1306;}
static int32_t MsgId() {return 1306;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGetBackRewardSingle();}
};
class SGetBackRewardInfo: public Msg {
public:
map<int32_t, int32_t> counts_;
map<int32_t, SGetBackRewardSingle> rewards_;
map<int32_t, SGetBackRewardSingle> halfRewards_;
virtual inline int32_t msgId() const {return 1160;}
static int32_t MsgId() {return 1160;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SGetBackRewardInfo();}
};
class SSyncThreeWorldInfo: public Msg {
public:
int32_t proxy_;
int32_t server_;
vector<msgs::SFightPlayer> players_;
int32_t totalNum_;
virtual inline int32_t msgId() const {return 3961;}
static int32_t MsgId() {return 3961;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SSyncThreeWorldInfo();}
};
class STreasureAdvanceSingle: public Msg {
public:
int32_t type_;
int32_t level_;
int32_t star_;
int32_t bless_;
map<int32_t, int32_t> danMap_;
virtual inline int32_t msgId() const {return 1772;}
static int32_t MsgId() {return 1772;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STreasureAdvanceSingle();}
};
class STreasureAdvanceInfo: public Msg {
public:
map<int32_t, STreasureAdvanceSingle> treasureMap_;
virtual inline int32_t msgId() const {return 1762;}
static int32_t MsgId() {return 1762;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new STreasureAdvanceInfo();}
};
class SMapEntity: public Msg {
public:
Identity entityId_;
Point spacePos_;
virtual inline int32_t msgId() const {return 2247;}
static int32_t MsgId() {return 2247;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMapEntity();}
};
class SMapPlayer: public SMapEntity {
public:
string name_;
int16_t sex_;
int16_t career_;
int16_t careerLevel_;
int16_t camp_;
int16_t force_;
int16_t level_;
int16_t vipLevel_;
vector<Point> moving_;
int16_t direction_;
int16_t speed_;
int64_t curLife_;
int64_t maxLife_;
int16_t fightMode_;
int16_t status_;
bool isRide_;
map<int16_t, int32_t> entityShows_;
map<int16_t, int32_t> entityValues_;
Identity ownerId_;
vector<msgs::SBuffInfo> buffs_;
Msg* teamData_;
Msg* guildData_;
virtual inline int32_t msgId() const {return 246;}
static int32_t MsgId() {return 246;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMapPlayer();}
};
class SMapRole: public SMapEntity {
public:
string name_;
int16_t sex_;
int16_t career_;
int16_t careerLevel_;
int16_t camp_;
int16_t force_;
int16_t level_;
int16_t vipLevel_;
vector<Point> moving_;
int16_t direction_;
int16_t speed_;
int16_t bodySize_;
int64_t curLife_;
int64_t inPower_;
int32_t avaLife_;
int64_t maxLife_;
int64_t maxInPower_;
int32_t maxAvaLife_;
int16_t fightMode_;
int16_t status_;
bool isRide_;
Identity warHorse_;
map<int16_t, int32_t> entityShows_;
map<int16_t, int32_t> entityValues_;
Identity ownerId_;
vector<msgs::SBuffInfo> buffs_;
Msg* teamData_;
Msg* guildData_;
Msg* fightAttr_;
virtual inline int32_t msgId() const {return 1700;}
static int32_t MsgId() {return 1700;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMapRole();}
};
class SMapMonster: public SMapEntity {
public:
string name_;
int32_t monsterId_;
int16_t force_;
int16_t level_;
vector<Point> moving_;
int16_t direction_;
int16_t speed_;
int64_t curLife_;
int64_t maxLife_;
int32_t avaLife_;
int32_t maxAvaLife_;
int16_t status_;
Identity ownerId_;
Identity belongId_;
vector<msgs::SBuffInfo> buffs_;
int32_t shield_;
string extend_;
virtual inline int32_t msgId() const {return 247;}
static int32_t MsgId() {return 247;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMapMonster();}
};
class SMapPet: public SMapEntity {
public:
int32_t petId_;
int16_t force_;
vector<Point> moving_;
int16_t direction_;
int16_t speed_;
int64_t attack_;
int64_t curLife_;
int64_t maxLife_;
int16_t status_;
Identity ownerId_;
vector<msgs::SBuffInfo> buffs_;
map<int16_t, int32_t> entityShows_;
virtual inline int32_t msgId() const {return 717;}
static int32_t MsgId() {return 717;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMapPet();}
};
class SMapNpc: public SMapEntity {
public:
int32_t npcId_;
virtual inline int32_t msgId() const {return 248;}
static int32_t MsgId() {return 248;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMapNpc();}
};
class SMapDrop: public SMapEntity {
public:
Identity belongTo_;
int32_t itemId_;
int32_t itemNum_;
virtual inline int32_t msgId() const {return 249;}
static int32_t MsgId() {return 249;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMapDrop();}
};
class SMapCorpse: public SMapEntity {
public:
int32_t monsterId_;
int32_t line_;
int64_t reviveTime_;
virtual inline int32_t msgId() const {return 1469;}
static int32_t MsgId() {return 1469;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMapCorpse();}
};
class SMapWarHorse: public SMapEntity {
public:
int32_t warHorseId_;
int16_t moveId_;
int16_t direction_;
int16_t speed_;
bool isHide_;
virtual inline int32_t msgId() const {return 4055;}
static int32_t MsgId() {return 4055;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMapWarHorse();}
};
class SMapZazen: public SMapEntity {
public:
int16_t career_;
string name_;
int32_t pointId_;
int64_t protectDt_;
Identity tagEntityId_;
virtual inline int32_t msgId() const {return 5109;}
static int32_t MsgId() {return 5109;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMapZazen();}
};
class SMapArena: public SMapEntity {
public:
int32_t rank_;
int16_t career_;
string name_;
int16_t direction_;
Identity tagEntityId_;
map<int16_t, int32_t> entityShows_;
map<int16_t, int32_t> entityValues_;
virtual inline int32_t msgId() const {return 5251;}
static int32_t MsgId() {return 5251;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMapArena();}
};
class SMapEntityEnters: public Msg {
public:
vector<Msg*> entities_;
virtual inline int32_t msgId() const {return 250;}
static int32_t MsgId() {return 250;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMapEntityEnters();}
};
class SMapEntityMoves: public Msg {
public:
Identity entityId_;
vector<Point> path_;
virtual inline int32_t msgId() const {return 251;}
static int32_t MsgId() {return 251;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMapEntityMoves();}
};
class SMapEntityLeaves: public Msg {
public:
vector<Identity> entityIds_;
virtual inline int32_t msgId() const {return 252;}
static int32_t MsgId() {return 252;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMapEntityLeaves();}
};
class SPlayerEnterMap: public Msg {
public:
uint16_t incId_;
Identity enterCellId_;
int16_t cellLine_;
int32_t spaceId_;
Point spacePos_;
int32_t copyCode_;
int16_t fightMode_;
bool useUninterested_;
virtual inline int32_t msgId() const {return 253;}
static int32_t MsgId() {return 253;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerEnterMap();}
};
class SPlayerLeaveMap: public Msg {
public:
uint16_t incId_;
Identity leaveCellId_;
virtual inline int32_t msgId() const {return 254;}
static int32_t MsgId() {return 254;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerLeaveMap();}
};
class SPlayerCurrentMapPos: public Msg {
public:
Identity entityId_;
uint16_t moveId_;
Point curPos_;
vector<Point> moving_;
int16_t direction_;
virtual inline int32_t msgId() const {return 255;}
static int32_t MsgId() {return 255;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerCurrentMapPos();}
};
class SRoleEnterMap: public Msg {
public:
bool isMain_;
uint16_t moveId_;
Msg* fightData_;
virtual inline int32_t msgId() const {return 1704;}
static int32_t MsgId() {return 1704;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRoleEnterMap();}
};
class SRoleEnterMapEnd: public Msg {
public:
int16_t roleNum_;
virtual inline int32_t msgId() const {return 3548;}
static int32_t MsgId() {return 3548;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRoleEnterMapEnd();}
};
class SRoleLeaveMap: public Msg {
public:
Identity cellId_;
Identity entityId_;
virtual inline int32_t msgId() const {return 3289;}
static int32_t MsgId() {return 3289;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SRoleLeaveMap();}
};
class SPlayerMove: public Msg {
public:
Identity entityId_;
int64_t operTime_;
uint16_t moveId_;
vector<Point> path_;
virtual inline int32_t msgId() const {return 256;}
static int32_t MsgId() {return 256;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerMove();}
};
class SPlayerUpdateMapPos: public Msg {
public:
uint16_t moveId_;
Point pos_;
virtual inline int32_t msgId() const {return 257;}
static int32_t MsgId() {return 257;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerUpdateMapPos();}
};
class SPlayerLeaveByCell: public Msg {
public:
uint16_t incId_;
Identity leaveCellId_;
virtual inline int32_t msgId() const {return 3384;}
static int32_t MsgId() {return 3384;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerLeaveByCell();}
};
class SEntityJumpTo: public Msg {
public:
Identity entityId_;
string jumpId_;
bool isReverse_;
Point endPos_;
virtual inline int32_t msgId() const {return 259;}
static int32_t MsgId() {return 259;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SEntityJumpTo();}
};
class SPlayerCollect: public Msg {
public:
Identity fromEntityId_;
Identity toEntityId_;
int64_t endTime_;
virtual inline int32_t msgId() const {return 915;}
static int32_t MsgId() {return 915;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerCollect();}
};
class SPlayerEndCollect: public Msg {
public:
Identity fromEntityId_;
Identity toEntityId_;
virtual inline int32_t msgId() const {return 970;}
static int32_t MsgId() {return 970;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerEndCollect();}
};
class SPlayerBreakCollect: public Msg {
public:
Identity fromEntityId_;
Identity toEntityId_;
virtual inline int32_t msgId() const {return 971;}
static int32_t MsgId() {return 971;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerBreakCollect();}
};
class SPlayerChangeMainRole: public Msg {
public:
Identity oldEntityId_;
Identity newEntityId_;
virtual inline int32_t msgId() const {return 1752;}
static int32_t MsgId() {return 1752;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SPlayerChangeMainRole();}
};
class SMapMiniPlayer: public Msg {
public:
Identity playerId_;
string name_;
Point point_;
virtual inline int32_t msgId() const {return 2610;}
static int32_t MsgId() {return 2610;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SMapMiniPlayer();}
};
class SYuanshenInfo: public Msg {
public:
int32_t level_;
int32_t fightType_;
map<int32_t, int32_t> activeMap_;
virtual inline int32_t msgId() const {return 3991;}
static int32_t MsgId() {return 3991;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SYuanshenInfo();}
};
class SElementSingle: public Msg {
public:
int32_t level_;
int32_t exp_;
virtual inline int32_t msgId() const {return 2551;}
static int32_t MsgId() {return 2551;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SElementSingle();}
};
class SElementInfo: public Msg {
public:
map<int32_t, SElementSingle> elementMap_;
virtual inline int32_t msgId() const {return 1438;}
static int32_t MsgId() {return 1438;}
virtual bool decode(CBufferReader &reader);
virtual bool encode(CBufferWriter &writer) const;
virtual void clear();
virtual Msg* New() const {return new SElementInfo();}
};
}

#endif