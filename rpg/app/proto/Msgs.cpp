#include "Msgs.h"
#include "MsgPool.h"
namespace msgs{
bool SCloakSingle::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,jingLianExp_);
PACKET_DECODE(Int32,jiLianLevel_);
PACKET_DECODE(Int32,jiLianStar_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);jiLianCount_[k] = v;}}
return true;}
bool SCloakSingle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,jingLianExp_);
PACKET_ENCODE(Int32,jiLianLevel_);
PACKET_ENCODE(Int32,jiLianStar_);
PACKET_ENCODE(UVar32,jiLianCount_.size());
for(map<int32_t, int32_t>::const_iterator it=jiLianCount_.begin();it!=jiLianCount_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCloakSingle::clear(){
jingLianExp_ = 0;
jiLianLevel_ = 0;
jiLianStar_ = 0;
jiLianCount_.clear();
}
bool SCloakInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SCloakSingle v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}cloakMap_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);jiBan_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SCloakSingle v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}gloveMap_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);gloveJiBan_[k] = v;}}
return true;}
bool SCloakInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,cloakMap_.size());
for(map<int32_t, SCloakSingle>::const_iterator it=cloakMap_.begin();it!=cloakMap_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
PACKET_ENCODE(UVar32,jiBan_.size());
for(map<int32_t, bool>::const_iterator it=jiBan_.begin();it!=jiBan_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
PACKET_ENCODE(UVar32,gloveMap_.size());
for(map<int32_t, SCloakSingle>::const_iterator it=gloveMap_.begin();it!=gloveMap_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
PACKET_ENCODE(UVar32,gloveJiBan_.size());
for(map<int32_t, bool>::const_iterator it=gloveJiBan_.begin();it!=gloveJiBan_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
return true;}
void SCloakInfo::clear(){
cloakMap_.clear();
jiBan_.clear();
gloveMap_.clear();
gloveJiBan_.clear();
}
bool SFightAttribute::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,maxLife_);
PACKET_DECODE(Int64,attack_);
PACKET_DECODE(Int64,defence_);
PACKET_DECODE(Int32,wuxingHurt_);
PACKET_DECODE(Int32,wuxingDefense_);
PACKET_DECODE(Int32,hit_);
PACKET_DECODE(Int32,dodge_);
PACKET_DECODE(Int32,hitRate_);
PACKET_DECODE(Int32,dodgeRate_);
PACKET_DECODE(Int32,crit_);
PACKET_DECODE(Int32,critBreak_);
PACKET_DECODE(Int32,critRate_);
PACKET_DECODE(Int32,critBreakRate_);
PACKET_DECODE(Int32,critDmg_);
PACKET_DECODE(Int32,ignoreDef_);
PACKET_DECODE(Int32,ignoreDefBreak_);
PACKET_DECODE(Int32,luckRate_);
PACKET_DECODE(Int32,curseRate_);
PACKET_DECODE(Int32,inPower_);
PACKET_DECODE(Int32,inPowerRecover_);
PACKET_DECODE(Int32,inPowerDmgPer_);
PACKET_DECODE(Int32,dizzyRate_);
PACKET_DECODE(Int32,dizzyRateBreak_);
PACKET_DECODE(Int32,fixDmg_);
PACKET_DECODE(Int32,fixDmgDec_);
PACKET_DECODE(Int32,recoverLife_);
PACKET_DECODE(Int32,dmgAdd_);
PACKET_DECODE(Int32,dmgDec_);
PACKET_DECODE(Int32,dmgBossAdd_);
PACKET_DECODE(Int32,xpDmgAdd_);
PACKET_DECODE(Int32,xpDmgDec_);
PACKET_DECODE(Int32,zsDmgAdd_);
PACKET_DECODE(Int32,zsDmgDec_);
PACKET_DECODE(Int32,fsDmgAdd_);
PACKET_DECODE(Int32,fsDmgDec_);
PACKET_DECODE(Int32,dsDmgAdd_);
PACKET_DECODE(Int32,dsDmgDec_);
PACKET_DECODE(Int32,skillDmgAdd_);
PACKET_DECODE(Int32,skillDmgDec_);
PACKET_DECODE(Int32,pvpDmgAdd_);
PACKET_DECODE(Int32,pvpDmgDec_);
PACKET_DECODE(Int32,luckDmgAdd_);
PACKET_DECODE(Int32,luckDmgDec_);
PACKET_DECODE(Int32,armor_);
PACKET_DECODE(Int32,critDmgAdd_);
PACKET_DECODE(Int32,critDmgDec_);
PACKET_DECODE(Int32,zhuXianRate_);
PACKET_DECODE(Int32,zhuXian_);
PACKET_DECODE(Int32,zhuXianDec_);
PACKET_DECODE(Int32,maxAvaLife_);
PACKET_DECODE(Int32,avatarAttack_);
PACKET_DECODE(Int64,avaLifeTop_);
PACKET_DECODE(Int32,avaAttackTop_);
PACKET_DECODE(Int32,avaCritRate_);
PACKET_DECODE(Int32,avaCritBreakRate_);
PACKET_DECODE(Int32,avaCrit_);
PACKET_DECODE(Int32,avaCritBreak_);
PACKET_DECODE(Int32,comboRate_);
PACKET_DECODE(Int32,comboBreakRate_);
PACKET_DECODE(Int32,combo_);
PACKET_DECODE(Int32,comboBreak_);
PACKET_DECODE(Int32,maxMagic_);
PACKET_DECODE(Int32,attackSpeed_);
return true;}
bool SFightAttribute::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,maxLife_);
PACKET_ENCODE(Int64,attack_);
PACKET_ENCODE(Int64,defence_);
PACKET_ENCODE(Int32,wuxingHurt_);
PACKET_ENCODE(Int32,wuxingDefense_);
PACKET_ENCODE(Int32,hit_);
PACKET_ENCODE(Int32,dodge_);
PACKET_ENCODE(Int32,hitRate_);
PACKET_ENCODE(Int32,dodgeRate_);
PACKET_ENCODE(Int32,crit_);
PACKET_ENCODE(Int32,critBreak_);
PACKET_ENCODE(Int32,critRate_);
PACKET_ENCODE(Int32,critBreakRate_);
PACKET_ENCODE(Int32,critDmg_);
PACKET_ENCODE(Int32,ignoreDef_);
PACKET_ENCODE(Int32,ignoreDefBreak_);
PACKET_ENCODE(Int32,luckRate_);
PACKET_ENCODE(Int32,curseRate_);
PACKET_ENCODE(Int32,inPower_);
PACKET_ENCODE(Int32,inPowerRecover_);
PACKET_ENCODE(Int32,inPowerDmgPer_);
PACKET_ENCODE(Int32,dizzyRate_);
PACKET_ENCODE(Int32,dizzyRateBreak_);
PACKET_ENCODE(Int32,fixDmg_);
PACKET_ENCODE(Int32,fixDmgDec_);
PACKET_ENCODE(Int32,recoverLife_);
PACKET_ENCODE(Int32,dmgAdd_);
PACKET_ENCODE(Int32,dmgDec_);
PACKET_ENCODE(Int32,dmgBossAdd_);
PACKET_ENCODE(Int32,xpDmgAdd_);
PACKET_ENCODE(Int32,xpDmgDec_);
PACKET_ENCODE(Int32,zsDmgAdd_);
PACKET_ENCODE(Int32,zsDmgDec_);
PACKET_ENCODE(Int32,fsDmgAdd_);
PACKET_ENCODE(Int32,fsDmgDec_);
PACKET_ENCODE(Int32,dsDmgAdd_);
PACKET_ENCODE(Int32,dsDmgDec_);
PACKET_ENCODE(Int32,skillDmgAdd_);
PACKET_ENCODE(Int32,skillDmgDec_);
PACKET_ENCODE(Int32,pvpDmgAdd_);
PACKET_ENCODE(Int32,pvpDmgDec_);
PACKET_ENCODE(Int32,luckDmgAdd_);
PACKET_ENCODE(Int32,luckDmgDec_);
PACKET_ENCODE(Int32,armor_);
PACKET_ENCODE(Int32,critDmgAdd_);
PACKET_ENCODE(Int32,critDmgDec_);
PACKET_ENCODE(Int32,zhuXianRate_);
PACKET_ENCODE(Int32,zhuXian_);
PACKET_ENCODE(Int32,zhuXianDec_);
PACKET_ENCODE(Int32,maxAvaLife_);
PACKET_ENCODE(Int32,avatarAttack_);
PACKET_ENCODE(Int64,avaLifeTop_);
PACKET_ENCODE(Int32,avaAttackTop_);
PACKET_ENCODE(Int32,avaCritRate_);
PACKET_ENCODE(Int32,avaCritBreakRate_);
PACKET_ENCODE(Int32,avaCrit_);
PACKET_ENCODE(Int32,avaCritBreak_);
PACKET_ENCODE(Int32,comboRate_);
PACKET_ENCODE(Int32,comboBreakRate_);
PACKET_ENCODE(Int32,combo_);
PACKET_ENCODE(Int32,comboBreak_);
PACKET_ENCODE(Int32,maxMagic_);
PACKET_ENCODE(Int32,attackSpeed_);
return true;}
void SFightAttribute::clear(){
maxLife_ = 0;
attack_ = 0;
defence_ = 0;
wuxingHurt_ = 0;
wuxingDefense_ = 0;
hit_ = 0;
dodge_ = 0;
hitRate_ = 0;
dodgeRate_ = 0;
crit_ = 0;
critBreak_ = 0;
critRate_ = 0;
critBreakRate_ = 0;
critDmg_ = 0;
ignoreDef_ = 0;
ignoreDefBreak_ = 0;
luckRate_ = 0;
curseRate_ = 0;
inPower_ = 0;
inPowerRecover_ = 0;
inPowerDmgPer_ = 0;
dizzyRate_ = 0;
dizzyRateBreak_ = 0;
fixDmg_ = 0;
fixDmgDec_ = 0;
recoverLife_ = 0;
dmgAdd_ = 0;
dmgDec_ = 0;
dmgBossAdd_ = 0;
xpDmgAdd_ = 0;
xpDmgDec_ = 0;
zsDmgAdd_ = 0;
zsDmgDec_ = 0;
fsDmgAdd_ = 0;
fsDmgDec_ = 0;
dsDmgAdd_ = 0;
dsDmgDec_ = 0;
skillDmgAdd_ = 0;
skillDmgDec_ = 0;
pvpDmgAdd_ = 0;
pvpDmgDec_ = 0;
luckDmgAdd_ = 0;
luckDmgDec_ = 0;
armor_ = 0;
critDmgAdd_ = 0;
critDmgDec_ = 0;
zhuXianRate_ = 0;
zhuXian_ = 0;
zhuXianDec_ = 0;
maxAvaLife_ = 0;
avatarAttack_ = 0;
avaLifeTop_ = 0;
avaAttackTop_ = 0;
avaCritRate_ = 0;
avaCritBreakRate_ = 0;
avaCrit_ = 0;
avaCritBreak_ = 0;
comboRate_ = 0;
comboBreakRate_ = 0;
combo_ = 0;
comboBreak_ = 0;
maxMagic_ = 0;
attackSpeed_ = 0;
}
bool SFightMiniAttribute::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,attack_);
PACKET_DECODE(Int64,defence_);
PACKET_DECODE(Int32,ignoreDef_);
PACKET_DECODE(Int32,crit_);
PACKET_DECODE(Int32,critRate_);
PACKET_DECODE(Int32,dmgAdd_);
PACKET_DECODE(Int32,dmgDec_);
PACKET_DECODE(Int32,skillDmgAdd_);
PACKET_DECODE(Int32,skillDmgDec_);
PACKET_DECODE(Int32,dodgeRate_);
PACKET_DECODE(Int32,dodge_);
PACKET_DECODE(Int32,luckRate_);
PACKET_DECODE(Int32,curseRate_);
PACKET_DECODE(Int32,hit_);
PACKET_DECODE(Int32,wuxingHurt_);
PACKET_DECODE(Int32,wuxingDefense_);
PACKET_DECODE(Int32,hitRate_);
return true;}
bool SFightMiniAttribute::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,attack_);
PACKET_ENCODE(Int64,defence_);
PACKET_ENCODE(Int32,ignoreDef_);
PACKET_ENCODE(Int32,crit_);
PACKET_ENCODE(Int32,critRate_);
PACKET_ENCODE(Int32,dmgAdd_);
PACKET_ENCODE(Int32,dmgDec_);
PACKET_ENCODE(Int32,skillDmgAdd_);
PACKET_ENCODE(Int32,skillDmgDec_);
PACKET_ENCODE(Int32,dodgeRate_);
PACKET_ENCODE(Int32,dodge_);
PACKET_ENCODE(Int32,luckRate_);
PACKET_ENCODE(Int32,curseRate_);
PACKET_ENCODE(Int32,hit_);
PACKET_ENCODE(Int32,wuxingHurt_);
PACKET_ENCODE(Int32,wuxingDefense_);
PACKET_ENCODE(Int32,hitRate_);
return true;}
void SFightMiniAttribute::clear(){
attack_ = 0;
defence_ = 0;
ignoreDef_ = 0;
crit_ = 0;
critRate_ = 0;
dmgAdd_ = 0;
dmgDec_ = 0;
skillDmgAdd_ = 0;
skillDmgDec_ = 0;
dodgeRate_ = 0;
dodge_ = 0;
luckRate_ = 0;
curseRate_ = 0;
hit_ = 0;
wuxingHurt_ = 0;
wuxingDefense_ = 0;
hitRate_ = 0;
}
bool STeamData::decode(CBufferReader &reader) {
if(!teamId_.decode(reader)){return false;}
PACKET_DECODE(String,teamName_);
PACKET_DECODE(Int16,onlineNum_);
PACKET_DECODE(Int16,isLeader_);
PACKET_DECODE(Int32,copyId_);
return true;}
bool STeamData::encode(CBufferWriter &writer) const {
if(!teamId_.encode(writer)){return false;}
PACKET_ENCODE(String,teamName_);
PACKET_ENCODE(Int16,onlineNum_);
PACKET_ENCODE(Int16,isLeader_);
PACKET_ENCODE(Int32,copyId_);
return true;}
void STeamData::clear(){
teamId_.clear();
teamName_.clear();
onlineNum_ = 0;
isLeader_ = 0;
copyId_ = 0;
}
bool SGuildData::decode(CBufferReader &reader) {
if(!guildId_.decode(reader)){return false;}
PACKET_DECODE(String,guildName_);
PACKET_DECODE(Int16,position_);
return true;}
bool SGuildData::encode(CBufferWriter &writer) const {
if(!guildId_.encode(writer)){return false;}
PACKET_ENCODE(String,guildName_);
PACKET_ENCODE(Int16,position_);
return true;}
void SGuildData::clear(){
guildId_.clear();
guildName_.clear();
position_ = 0;
}
bool SMateData::decode(CBufferReader &reader) {
if(!mateId_.decode(reader)){return false;}
PACKET_DECODE(String,mateName_);
PACKET_DECODE(Int64,mateAttack_);
return true;}
bool SMateData::encode(CBufferWriter &writer) const {
if(!mateId_.encode(writer)){return false;}
PACKET_ENCODE(String,mateName_);
PACKET_ENCODE(Int64,mateAttack_);
return true;}
void SMateData::clear(){
mateId_.clear();
mateName_.clear();
mateAttack_ = 0;
}
bool SRechargeRewardInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewardInfo_[k] = v;}}
PACKET_DECODE(Int32,firstRecharge_);
return true;}
bool SRechargeRewardInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,rewardInfo_.size());
for(map<int32_t, int32_t>::const_iterator it=rewardInfo_.begin();it!=rewardInfo_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,firstRecharge_);
return true;}
void SRechargeRewardInfo::clear(){
rewardInfo_.clear();
firstRecharge_ = 0;
}
bool SRechargeInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,todayRecharge_);
PACKET_DECODE(Int32,totalRecharge_);
PACKET_DECODE(Int32,rechargeCount_);
PACKET_DECODE(Int32,maxDayRecharge_);
PACKET_DECODE(Int32,monthRecharge_);
PACKET_DECODE(Int64,lastRechargeDt_);
return true;}
bool SRechargeInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,todayRecharge_);
PACKET_ENCODE(Int32,totalRecharge_);
PACKET_ENCODE(Int32,rechargeCount_);
PACKET_ENCODE(Int32,maxDayRecharge_);
PACKET_ENCODE(Int32,monthRecharge_);
PACKET_ENCODE(Int64,lastRechargeDt_);
return true;}
void SRechargeInfo::clear(){
todayRecharge_ = 0;
totalRecharge_ = 0;
rechargeCount_ = 0;
maxDayRecharge_ = 0;
monthRecharge_ = 0;
lastRechargeDt_ = 0;
}
bool SDayRecharge::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);target_[k] = v;}}
return true;}
bool SDayRecharge::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,target_.size());
for(map<int32_t, bool>::const_iterator it=target_.begin();it!=target_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
return true;}
void SDayRecharge::clear(){
target_.clear();
}
bool SAccumDayReward::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,cycle_);
PACKET_DECODE(Int32,day_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);rewardGot_[k] = v;}}
return true;}
bool SAccumDayReward::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,cycle_);
PACKET_ENCODE(Int32,day_);
PACKET_ENCODE(UVar32,rewardGot_.size());
for(map<int32_t, bool>::const_iterator it=rewardGot_.begin();it!=rewardGot_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
return true;}
void SAccumDayReward::clear(){
cycle_ = 0;
day_ = 0;
rewardGot_.clear();
}
bool SLimitRecharge::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,day_);
PACKET_DECODE(Int32,index_);
PACKET_DECODE(Int32,recharge_);
PACKET_DECODE(Int64,endTime_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);notGots_[k] = v;}}
return true;}
bool SLimitRecharge::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,day_);
PACKET_ENCODE(Int32,index_);
PACKET_ENCODE(Int32,recharge_);
PACKET_ENCODE(Int64,endTime_);
PACKET_ENCODE(UVar32,notGots_.size());
for(map<int32_t, int32_t>::const_iterator it=notGots_.begin();it!=notGots_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SLimitRecharge::clear(){
day_ = 0;
index_ = 0;
recharge_ = 0;
endTime_ = 0;
notGots_.clear();
}
bool SPlayerWeekDayRecharge::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,recharge_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);gots_.push_back(item);}}
return true;}
bool SPlayerWeekDayRecharge::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,recharge_);
PACKET_ENCODE(UVar32,gots_.size());
for(vector<int32_t>::const_iterator vit=gots_.begin();vit!=gots_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SPlayerWeekDayRecharge::clear(){
recharge_ = 0;
gots_.clear();
}
bool SInt::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,value_);
return true;}
bool SInt::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,value_);
return true;}
void SInt::clear(){
value_ = 0;
}
bool SInts::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);values_.push_back(item);}}
return true;}
bool SInts::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,values_.size());
for(vector<int32_t>::const_iterator vit=values_.begin();vit!=values_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SInts::clear(){
values_.clear();
}
bool SLong::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,value_);
return true;}
bool SLong::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,value_);
return true;}
void SLong::clear(){
value_ = 0;
}
bool SLongs::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int64_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int64,item);values_.push_back(item);}}
return true;}
bool SLongs::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,values_.size());
for(vector<int64_t>::const_iterator vit=values_.begin();vit!=values_.end();++vit){PACKET_ENCODE(Int64,*vit);}
return true;}
void SLongs::clear(){
values_.clear();
}
bool SString::decode(CBufferReader &reader) {
PACKET_DECODE(String,value_);
return true;}
bool SString::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,value_);
return true;}
void SString::clear(){
value_.clear();
}
bool SStrings::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);string item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(String,item);values_.push_back(item);}}
return true;}
bool SStrings::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,values_.size());
for(vector<string>::const_iterator vit=values_.begin();vit!=values_.end();++vit){PACKET_ENCODE(String,*vit);}
return true;}
void SStrings::clear(){
values_.clear();
}
bool SIdentity::decode(CBufferReader &reader) {
if(!value_.decode(reader)){return false;}
return true;}
bool SIdentity::encode(CBufferWriter &writer) const {
if(!value_.encode(writer)){return false;}
return true;}
void SIdentity::clear(){
value_.clear();
}
bool SIdentitys::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Identity item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}values_.push_back(item);}}
return true;}
bool SIdentitys::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,values_.size());
for(vector<Identity>::const_iterator vit=values_.begin();vit!=values_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SIdentitys::clear(){
values_.clear();
}
bool SIntIntPair::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,first_);
PACKET_DECODE(Int32,second_);
return true;}
bool SIntIntPair::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,first_);
PACKET_ENCODE(Int32,second_);
return true;}
void SIntIntPair::clear(){
first_ = 0;
second_ = 0;
}
bool SLongLongPair::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,first_);
PACKET_DECODE(Int64,second_);
return true;}
bool SLongLongPair::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,first_);
PACKET_ENCODE(Int64,second_);
return true;}
void SLongLongPair::clear(){
first_ = 0;
second_ = 0;
}
bool SPoint::decode(CBufferReader &reader) {
if(!value_.decode(reader)){return false;}
return true;}
bool SPoint::encode(CBufferWriter &writer) const {
if(!value_.encode(writer)){return false;}
return true;}
void SPoint::clear(){
value_.clear();
}
bool SPoints::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Point item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}values_.push_back(item);}}
return true;}
bool SPoints::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,values_.size());
for(vector<Point>::const_iterator vit=values_.begin();vit!=values_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPoints::clear(){
values_.clear();
}
bool SItemAmount::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,itemCode_);
PACKET_DECODE(Int32,itemNum_);
return true;}
bool SItemAmount::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,itemCode_);
PACKET_ENCODE(Int32,itemNum_);
return true;}
void SItemAmount::clear(){
itemCode_ = 0;
itemNum_ = 0;
}
bool SIntBoolMap::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);maps_[k] = v;}}
return true;}
bool SIntBoolMap::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,maps_.size());
for(map<int32_t, bool>::const_iterator it=maps_.begin();it!=maps_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
return true;}
void SIntBoolMap::clear(){
maps_.clear();
}
bool SIntIntBoolMap::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SIntBoolMap v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}maps_[k] = v;}}
return true;}
bool SIntIntBoolMap::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,maps_.size());
for(map<int32_t, SIntBoolMap>::const_iterator it=maps_.begin();it!=maps_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SIntIntBoolMap::clear(){
maps_.clear();
}
bool SIntIntMap::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);maps_[k] = v;}}
return true;}
bool SIntIntMap::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,maps_.size());
for(map<int32_t, int32_t>::const_iterator it=maps_.begin();it!=maps_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SIntIntMap::clear(){
maps_.clear();
}
bool SIntIntIntMap::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;map<int32_t, int32_t> v;PACKET_DECODE(Int32,k);{uint32_t len1=0;PACKET_DECODE(UVar32,len1);for(uint32_t i1=0;i1<len1;++i1){int32_t k1;int32_t v1;PACKET_DECODE(Int32,k1);PACKET_DECODE(Int32,v1);v[k1] = v1;}}
maps_[k] = v;}}
return true;}
bool SIntIntIntMap::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,maps_.size());
for(map<int32_t, map<int32_t, int32_t> >::const_iterator it=maps_.begin();it!=maps_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(UVar32,it->second.size());
for(map<int32_t, int32_t>::const_iterator it1=it->second.begin();it1!=it->second.end();++it1){PACKET_ENCODE(Int32,it1->first);PACKET_ENCODE(Int32,it1->second);}
}
return true;}
void SIntIntIntMap::clear(){
maps_.clear();
}
bool SDateTime::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,value_);
return true;}
bool SDateTime::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,value_);
return true;}
void SDateTime::clear(){
value_ = 0;
}
bool SBoolInt::decode(CBufferReader &reader) {
PACKET_DECODE(Bool,boolVal_);
PACKET_DECODE(Int32,intVal_);
return true;}
bool SBoolInt::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Bool,boolVal_);
PACKET_ENCODE(Int32,intVal_);
return true;}
void SBoolInt::clear(){
boolVal_ = 0;
intVal_ = 0;
}
bool SAttribute::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;map<int16_t, int64_t> v;PACKET_DECODE(Int16,k);{uint32_t len1=0;PACKET_DECODE(UVar32,len1);for(uint32_t i1=0;i1<len1;++i1){int16_t k1;int64_t v1;PACKET_DECODE(Int16,k1);PACKET_DECODE(Int64,v1);v[k1] = v1;}}
attr_[k] = v;}}
return true;}
bool SAttribute::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,attr_.size());
for(map<int16_t, map<int16_t, int64_t> >::const_iterator it=attr_.begin();it!=attr_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(UVar32,it->second.size());
for(map<int16_t, int64_t>::const_iterator it1=it->second.begin();it1!=it->second.end();++it1){PACKET_ENCODE(Int16,it1->first);PACKET_ENCODE(Int64,it1->second);}
}
return true;}
void SAttribute::clear(){
attr_.clear();
}
bool SReincarnInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,levelDelCount_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);itemDelCount_[k] = v;}}
PACKET_DECODE(Int32,hadGotLevel_);
PACKET_DECODE(Int32,hadGotLevelCount_);
return true;}
bool SReincarnInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,levelDelCount_);
PACKET_ENCODE(UVar32,itemDelCount_.size());
for(map<int32_t, int32_t>::const_iterator it=itemDelCount_.begin();it!=itemDelCount_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,hadGotLevel_);
PACKET_ENCODE(Int32,hadGotLevelCount_);
return true;}
void SReincarnInfo::clear(){
levelDelCount_ = 0;
itemDelCount_.clear();
hadGotLevel_ = 0;
hadGotLevelCount_ = 0;
}
bool SShengInfo::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);shengLst_.push_back(item);}}
return true;}
bool SShengInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,shengLst_.size());
for(vector<int32_t>::const_iterator vit=shengLst_.begin();vit!=shengLst_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SShengInfo::clear(){
shengLst_.clear();
}
bool SMiniPlayer::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int16,sex_);
PACKET_DECODE(Int16,career_);
PACKET_DECODE(Int16,careerLevel_);
PACKET_DECODE(Int16,level_);
PACKET_DECODE(Int16,vipLevel_);
PACKET_DECODE(Int32,hangLevel_);
PACKET_DECODE(Int64,combat_);
PACKET_DECODE(Int16,camp_);
PACKET_DECODE(Byte,online_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);ornaments_[k] = v;}}
return true;}
bool SMiniPlayer::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int16,sex_);
PACKET_ENCODE(Int16,career_);
PACKET_ENCODE(Int16,careerLevel_);
PACKET_ENCODE(Int16,level_);
PACKET_ENCODE(Int16,vipLevel_);
PACKET_ENCODE(Int32,hangLevel_);
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(Int16,camp_);
PACKET_ENCODE(Byte,online_);
PACKET_ENCODE(UVar32,ornaments_.size());
for(map<int16_t, int32_t>::const_iterator it=ornaments_.begin();it!=ornaments_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SMiniPlayer::clear(){
entityId_.clear();
name_.clear();
sex_ = 0;
career_ = 0;
careerLevel_ = 0;
level_ = 0;
vipLevel_ = 0;
hangLevel_ = 0;
combat_ = 0;
camp_ = 0;
online_ = 0;
ornaments_.clear();
}
bool SPublicPlayer::decode(CBufferReader &reader) {
if(!SMiniPlayer::decode(reader)){return false;}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);entityShows_[k] = v;}}
if(!teamId_.decode(reader)){return false;}
PACKET_DECODE(String,teamName_);
PACKET_DECODE(Bool,isLeader_);
PACKET_DECODE(Int32,teamCopyId_);
if(!guildId_.decode(reader)){return false;}
PACKET_DECODE(String,guildName_);
PACKET_DECODE(Int16,guildPos_);
if(!mateId_.decode(reader)){return false;}
PACKET_DECODE(String,mateName_);
PACKET_DECODE(Int16,oldServerId_);
return true;}
bool SPublicPlayer::encode(CBufferWriter &writer) const {
if(!SMiniPlayer::encode(writer)){return false;}
PACKET_ENCODE(UVar32,entityShows_.size());
for(map<int16_t, int32_t>::const_iterator it=entityShows_.begin();it!=entityShows_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
if(!teamId_.encode(writer)){return false;}
PACKET_ENCODE(String,teamName_);
PACKET_ENCODE(Bool,isLeader_);
PACKET_ENCODE(Int32,teamCopyId_);
if(!guildId_.encode(writer)){return false;}
PACKET_ENCODE(String,guildName_);
PACKET_ENCODE(Int16,guildPos_);
if(!mateId_.encode(writer)){return false;}
PACKET_ENCODE(String,mateName_);
PACKET_ENCODE(Int16,oldServerId_);
return true;}
void SPublicPlayer::clear(){
entityShows_.clear();
teamId_.clear();
teamName_.clear();
isLeader_ = 0;
teamCopyId_ = 0;
guildId_.clear();
guildName_.clear();
guildPos_ = 0;
mateId_.clear();
mateName_.clear();
oldServerId_ = 0;
}
bool SPublicPlayerEx::decode(CBufferReader &reader) {
if(!SPublicPlayer::decode(reader)){return false;}
PACKET_DECODE(String,gameChannel_);
PACKET_DECODE(String,platformData_);
PACKET_DECODE(String,loginIp_);
return true;}
bool SPublicPlayerEx::encode(CBufferWriter &writer) const {
if(!SPublicPlayer::encode(writer)){return false;}
PACKET_ENCODE(String,gameChannel_);
PACKET_ENCODE(String,platformData_);
PACKET_ENCODE(String,loginIp_);
return true;}
void SPublicPlayerEx::clear(){
gameChannel_.clear();
platformData_.clear();
loginIp_.clear();
}
bool SPublicPlayerExt::decode(CBufferReader &reader) {
if(!SPublicPlayerEx::decode(reader)){return false;}
PACKET_DECODE(Int64,gameDt_);
PACKET_DECODE(String,username_);
return true;}
bool SPublicPlayerExt::encode(CBufferWriter &writer) const {
if(!SPublicPlayerEx::encode(writer)){return false;}
PACKET_ENCODE(Int64,gameDt_);
PACKET_ENCODE(String,username_);
return true;}
void SPublicPlayerExt::clear(){
gameDt_ = 0;
username_.clear();
}
bool SArenaWzInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,wzLevel_);
PACKET_DECODE(Int32,winCount_);
PACKET_DECODE(Int32,winTotalCount_);
PACKET_DECODE(Int32,totalCount_);
return true;}
bool SArenaWzInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,wzLevel_);
PACKET_ENCODE(Int32,winCount_);
PACKET_ENCODE(Int32,winTotalCount_);
PACKET_ENCODE(Int32,totalCount_);
return true;}
void SArenaWzInfo::clear(){
wzLevel_ = 0;
winCount_ = 0;
winTotalCount_ = 0;
totalCount_ = 0;
}
bool SArenaWzExtendInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,matchCount_);
PACKET_DECODE(Int32,buyCount_);
PACKET_DECODE(Int64,recoverTime_);
return true;}
bool SArenaWzExtendInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,matchCount_);
PACKET_ENCODE(Int32,buyCount_);
PACKET_ENCODE(Int64,recoverTime_);
return true;}
void SArenaWzExtendInfo::clear(){
matchCount_ = 0;
buyCount_ = 0;
recoverTime_ = 0;
}
bool SArenaWzResult::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,result_);
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,addStar_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);reward_[k] = v;}}
return true;}
bool SArenaWzResult::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,result_);
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,addStar_);
PACKET_ENCODE(UVar32,reward_.size());
for(map<int32_t, int32_t>::const_iterator it=reward_.begin();it!=reward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SArenaWzResult::clear(){
result_ = 0;
level_ = 0;
addStar_ = 0;
reward_.clear();
}
bool SArenaWzResultFromGate::decode(CBufferReader &reader) {
PACKET_DECODE(Bool,isWin_);
PACKET_DECODE(Bool,sendClient_);
PACKET_DECODE(Int16,count_);
return true;}
bool SArenaWzResultFromGate::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Bool,isWin_);
PACKET_ENCODE(Bool,sendClient_);
PACKET_ENCODE(Int16,count_);
return true;}
void SArenaWzResultFromGate::clear(){
isWin_ = 0;
sendClient_ = 0;
count_ = 0;
}
bool SArenaMatchEnemy::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int16,career_);
PACKET_DECODE(Int16,wzLevel_);
PACKET_DECODE(Bool,isRobot_);
return true;}
bool SArenaMatchEnemy::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int16,career_);
PACKET_ENCODE(Int16,wzLevel_);
PACKET_ENCODE(Bool,isRobot_);
return true;}
void SArenaMatchEnemy::clear(){
entityId_.clear();
name_.clear();
career_ = 0;
wzLevel_ = 0;
isRobot_ = 0;
}
bool SArenaTtSeason::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,seaon_);
PACKET_DECODE(Int64,beginDt_);
return true;}
bool SArenaTtSeason::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,seaon_);
PACKET_ENCODE(Int64,beginDt_);
return true;}
void SArenaTtSeason::clear(){
seaon_ = 0;
beginDt_ = 0;
}
bool SArenaTtInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,score_);
PACKET_DECODE(Int32,gongxun_);
return true;}
bool SArenaTtInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,score_);
PACKET_ENCODE(Int32,gongxun_);
return true;}
void SArenaTtInfo::clear(){
level_ = 0;
score_ = 0;
gongxun_ = 0;
}
bool SArenaTtExtendInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,matchCount_);
PACKET_DECODE(Int32,buyCount_);
PACKET_DECODE(Int32,todayCount_);
PACKET_DECODE(Int32,totalCount_);
PACKET_DECODE(Int32,winCount_);
PACKET_DECODE(Int32,getDailyHonor_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);joinReward_.push_back(item);}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);gongxunReward_.push_back(item);}}
return true;}
bool SArenaTtExtendInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,matchCount_);
PACKET_ENCODE(Int32,buyCount_);
PACKET_ENCODE(Int32,todayCount_);
PACKET_ENCODE(Int32,totalCount_);
PACKET_ENCODE(Int32,winCount_);
PACKET_ENCODE(Int32,getDailyHonor_);
PACKET_ENCODE(UVar32,joinReward_.size());
for(vector<int32_t>::const_iterator vit=joinReward_.begin();vit!=joinReward_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(UVar32,gongxunReward_.size());
for(vector<int32_t>::const_iterator vit=gongxunReward_.begin();vit!=gongxunReward_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SArenaTtExtendInfo::clear(){
matchCount_ = 0;
buyCount_ = 0;
todayCount_ = 0;
totalCount_ = 0;
winCount_ = 0;
getDailyHonor_ = 0;
joinReward_.clear();
gongxunReward_.clear();
}
bool SArenaTtResult::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,result_);
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,addScore_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);reward_[k] = v;}}
return true;}
bool SArenaTtResult::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,result_);
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,addScore_);
PACKET_ENCODE(UVar32,reward_.size());
for(map<int32_t, int32_t>::const_iterator it=reward_.begin();it!=reward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SArenaTtResult::clear(){
result_ = 0;
level_ = 0;
addScore_ = 0;
reward_.clear();
}
bool SArenaTtRankInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,score_);
PACKET_DECODE(Int32,rank_);
return true;}
bool SArenaTtRankInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,score_);
PACKET_ENCODE(Int32,rank_);
return true;}
void SArenaTtRankInfo::clear(){
level_ = 0;
score_ = 0;
rank_ = 0;
}
bool SArenaTtHistoryRank::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SArenaTtRankInfo v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}hRank_[k] = v;}}
return true;}
bool SArenaTtHistoryRank::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,hRank_.size());
for(map<int32_t, SArenaTtRankInfo>::const_iterator it=hRank_.begin();it!=hRank_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SArenaTtHistoryRank::clear(){
hRank_.clear();
}
bool SArenaTopPlayer::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,stage_);
PACKET_DECODE(Int32,pos_);
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,carerr_);
PACKET_DECODE(Int64,combat_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);ornaments_[k] = v;}}
return true;}
bool SArenaTopPlayer::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,stage_);
PACKET_ENCODE(Int32,pos_);
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,carerr_);
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(UVar32,ornaments_.size());
for(map<int16_t, int32_t>::const_iterator it=ornaments_.begin();it!=ornaments_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SArenaTopPlayer::clear(){
stage_ = 0;
pos_ = 0;
entityId_.clear();
name_.clear();
carerr_ = 0;
combat_ = 0;
ornaments_.clear();
}
bool SArenaTopArea::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SArenaTopPlayer item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}players_.push_back(item);}}
return true;}
bool SArenaTopArea::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,players_.size());
for(vector<SArenaTopPlayer>::const_iterator vit=players_.begin();vit!=players_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SArenaTopArea::clear(){
players_.clear();
}
bool SArenaTopType::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SArenaTopArea v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}areas_[k] = v;}}
return true;}
bool SArenaTopType::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,areas_.size());
for(map<int32_t, SArenaTopArea>::const_iterator it=areas_.begin();it!=areas_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SArenaTopType::clear(){
areas_.clear();
}
bool SArenaTopTotal::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,stage_);
PACKET_DECODE(Int32,myType_);
PACKET_DECODE(Int32,myArea_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);total_[k] = v;}}
return true;}
bool SArenaTopTotal::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,stage_);
PACKET_ENCODE(Int32,myType_);
PACKET_ENCODE(Int32,myArea_);
PACKET_ENCODE(UVar32,total_.size());
for(map<int32_t, int32_t>::const_iterator it=total_.begin();it!=total_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SArenaTopTotal::clear(){
stage_ = 0;
myType_ = 0;
myArea_ = 0;
total_.clear();
}
bool SArenaTopYazhu::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,pos_);
PACKET_DECODE(Int32,index_);
if(!entity_.decode(reader)){return false;}
PACKET_DECODE(Int32,result_);
return true;}
bool SArenaTopYazhu::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,pos_);
PACKET_ENCODE(Int32,index_);
if(!entity_.encode(writer)){return false;}
PACKET_ENCODE(Int32,result_);
return true;}
void SArenaTopYazhu::clear(){
pos_ = 0;
index_ = 0;
entity_.clear();
result_ = 0;
}
bool SArenaTopInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Bool,isSignUp_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;map<int32_t, vector<SArenaTopYazhu> > v;PACKET_DECODE(Int32,k);{uint32_t len1=0;PACKET_DECODE(UVar32,len1);for(uint32_t i1=0;i1<len1;++i1){int32_t k1;vector<SArenaTopYazhu> v1;PACKET_DECODE(Int32,k1);{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SArenaTopYazhu item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}v1.push_back(item);}}
v[k1] = v1;}}
yazhu_[k] = v;}}
return true;}
bool SArenaTopInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Bool,isSignUp_);
PACKET_ENCODE(UVar32,yazhu_.size());
for(map<int32_t, map<int32_t, vector<SArenaTopYazhu> > >::const_iterator it=yazhu_.begin();it!=yazhu_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(UVar32,it->second.size());
for(map<int32_t, vector<SArenaTopYazhu> >::const_iterator it1=it->second.begin();it1!=it->second.end();++it1){PACKET_ENCODE(Int32,it1->first);PACKET_ENCODE(UVar32,it1->second.size());
for(vector<SArenaTopYazhu>::const_iterator vit=it1->second.begin();vit!=it1->second.end();++vit){if(!vit->encode(writer)){return false;}}
}
}
return true;}
void SArenaTopInfo::clear(){
isSignUp_ = 0;
yazhu_.clear();
}
bool SArenaTopResult::decode(CBufferReader &reader) {
if(!winId_.decode(reader)){return false;}
if(!loseId_.decode(reader)){return false;}
PACKET_DECODE(String,name1_);
PACKET_DECODE(String,name2_);
return true;}
bool SArenaTopResult::encode(CBufferWriter &writer) const {
if(!winId_.encode(writer)){return false;}
if(!loseId_.encode(writer)){return false;}
PACKET_ENCODE(String,name1_);
PACKET_ENCODE(String,name2_);
return true;}
void SArenaTopResult::clear(){
winId_.clear();
loseId_.clear();
name1_.clear();
name2_.clear();
}
bool SArenaTopResults::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,stage_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;map<int32_t, map<int32_t, SArenaTopResult> > v;PACKET_DECODE(Int32,k);{uint32_t len1=0;PACKET_DECODE(UVar32,len1);for(uint32_t i1=0;i1<len1;++i1){int32_t k1;map<int32_t, SArenaTopResult> v1;PACKET_DECODE(Int32,k1);{uint32_t len2=0;PACKET_DECODE(UVar32,len2);for(uint32_t i2=0;i2<len2;++i2){int32_t k2;SArenaTopResult v2;PACKET_DECODE(Int32,k2);if(!v2.decode(reader)){return false;}v1[k2] = v2;}}
v[k1] = v1;}}
result_[k] = v;}}
return true;}
bool SArenaTopResults::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,stage_);
PACKET_ENCODE(UVar32,result_.size());
for(map<int32_t, map<int32_t, map<int32_t, SArenaTopResult> > >::const_iterator it=result_.begin();it!=result_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(UVar32,it->second.size());
for(map<int32_t, map<int32_t, SArenaTopResult> >::const_iterator it1=it->second.begin();it1!=it->second.end();++it1){PACKET_ENCODE(Int32,it1->first);PACKET_ENCODE(UVar32,it1->second.size());
for(map<int32_t, SArenaTopResult>::const_iterator it2=it1->second.begin();it2!=it1->second.end();++it2){PACKET_ENCODE(Int32,it2->first);if(!it2->second.encode(writer)){return false;}}
}
}
return true;}
void SArenaTopResults::clear(){
stage_ = 0;
result_.clear();
}
bool SArenaTopSeaResult::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){Identity k;int32_t v;if(!k.decode(reader)){return false;}PACKET_DECODE(Int32,v);seaResult_[k] = v;}}
return true;}
bool SArenaTopSeaResult::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,seaResult_.size());
for(map<Identity, int32_t>::const_iterator it=seaResult_.begin();it!=seaResult_.end();++it){if(!it->first.encode(writer)){return false;}PACKET_ENCODE(Int32,it->second);}
return true;}
void SArenaTopSeaResult::clear(){
seaResult_.clear();
}
bool SFriend::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,friendType_);
PACKET_DECODE(Int32,intimacy_);
PACKET_DECODE(Int32,lastChatTime_);
PACKET_DECODE(String,openid_);
PACKET_DECODE(Int32,isBeCalled_);
PACKET_DECODE(Int64,offlineDt_);
if(!miniPlayer_.decode(reader)){return false;}
PACKET_DECODE(Bool,hadGroupFightTeam_);
return true;}
bool SFriend::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,friendType_);
PACKET_ENCODE(Int32,intimacy_);
PACKET_ENCODE(Int32,lastChatTime_);
PACKET_ENCODE(String,openid_);
PACKET_ENCODE(Int32,isBeCalled_);
PACKET_ENCODE(Int64,offlineDt_);
if(!miniPlayer_.encode(writer)){return false;}
PACKET_ENCODE(Bool,hadGroupFightTeam_);
return true;}
void SFriend::clear(){
friendType_ = 0;
intimacy_ = 0;
lastChatTime_ = 0;
openid_.clear();
isBeCalled_ = 0;
offlineDt_ = 0;
miniPlayer_.clear();
hadGroupFightTeam_ = 0;
}
bool SFriendList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SFriend item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}friends_.push_back(item);}}
return true;}
bool SFriendList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,friends_.size());
for(vector<SFriend>::const_iterator vit=friends_.begin();vit!=friends_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SFriendList::clear(){
friends_.clear();
}
bool SFriendRemove::decode(CBufferReader &reader) {
if(!fromId_.decode(reader)){return false;}
PACKET_DECODE(Int32,reason_);
return true;}
bool SFriendRemove::encode(CBufferWriter &writer) const {
if(!fromId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,reason_);
return true;}
void SFriendRemove::clear(){
fromId_.clear();
reason_ = 0;
}
bool SFriendOnline::decode(CBufferReader &reader) {
if(!fromId_.decode(reader)){return false;}
PACKET_DECODE(Int32,online_);
return true;}
bool SFriendOnline::encode(CBufferWriter &writer) const {
if(!fromId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,online_);
return true;}
void SFriendOnline::clear(){
fromId_.clear();
online_ = 0;
}
bool SFriendDecline::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,playerName_);
return true;}
bool SFriendDecline::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,playerName_);
return true;}
void SFriendDecline::clear(){
entityId_.clear();
playerName_.clear();
}
bool SSendFlower::decode(CBufferReader &reader) {
if(!fromPlayer_.decode(reader)){return false;}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);items_[k] = v;}}
PACKET_DECODE(Bool,anonynous_);
return true;}
bool SSendFlower::encode(CBufferWriter &writer) const {
if(!fromPlayer_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,items_.size());
for(map<int32_t, int32_t>::const_iterator it=items_.begin();it!=items_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Bool,anonynous_);
return true;}
void SSendFlower::clear(){
fromPlayer_.clear();
items_.clear();
anonynous_ = 0;
}
bool SSendFlowerBroadcast::decode(CBufferReader &reader) {
if(!sender_.decode(reader)){return false;}
if(!receiver_.decode(reader)){return false;}
PACKET_DECODE(Int32,itemId_);
PACKET_DECODE(Int32,itemNum_);
return true;}
bool SSendFlowerBroadcast::encode(CBufferWriter &writer) const {
if(!sender_.encode(writer)){return false;}
if(!receiver_.encode(writer)){return false;}
PACKET_ENCODE(Int32,itemId_);
PACKET_ENCODE(Int32,itemNum_);
return true;}
void SSendFlowerBroadcast::clear(){
sender_.clear();
receiver_.clear();
itemId_ = 0;
itemNum_ = 0;
}
bool SFriendZanData::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);friendIds_.push_back(item);}}
PACKET_DECODE(Int32,expNum_);
return true;}
bool SFriendZanData::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,friendIds_.size());
for(vector<int32_t>::const_iterator vit=friendIds_.begin();vit!=friendIds_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(Int32,expNum_);
return true;}
void SFriendZanData::clear(){
friendIds_.clear();
expNum_ = 0;
}
bool SFriendBeZan::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int64,exp_);
return true;}
bool SFriendBeZan::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int64,exp_);
return true;}
void SFriendBeZan::clear(){
entityId_.clear();
name_.clear();
exp_ = 0;
}
bool SPlayerMrRight::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);dbs::TPlayerMrRight item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}mrRights_.push_back(item);}}
return true;}
bool SPlayerMrRight::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,mrRights_.size());
for(vector<dbs::TPlayerMrRight>::const_iterator vit=mrRights_.begin();vit!=mrRights_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerMrRight::clear(){
mrRights_.clear();
}
bool SPlayerLifeFairy::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);dbs::TPlayerLifeFairy item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}lifeFairies_.push_back(item);}}
return true;}
bool SPlayerLifeFairy::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,lifeFairies_.size());
for(vector<dbs::TPlayerLifeFairy>::const_iterator vit=lifeFairies_.begin();vit!=lifeFairies_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerLifeFairy::clear(){
lifeFairies_.clear();
}
bool SMeridiansSingle::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,star_);
PACKET_DECODE(Bool,isActive_);
PACKET_DECODE(Int32,bless_);
return true;}
bool SMeridiansSingle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,star_);
PACKET_ENCODE(Bool,isActive_);
PACKET_ENCODE(Int32,bless_);
return true;}
void SMeridiansSingle::clear(){
roleId_ = 0;
level_ = 0;
star_ = 0;
isActive_ = 0;
bless_ = 0;
}
bool SMeridiansInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SMeridiansSingle v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}meriMap_[k] = v;}}
return true;}
bool SMeridiansInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,meriMap_.size());
for(map<int32_t, SMeridiansSingle>::const_iterator it=meriMap_.begin();it!=meriMap_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SMeridiansInfo::clear(){
meriMap_.clear();
}
bool SOrnament::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,id_);
PACKET_DECODE(Int32,star_);
return true;}
bool SOrnament::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,id_);
PACKET_ENCODE(Int32,star_);
return true;}
void SOrnament::clear(){
id_ = 0;
star_ = 0;
}
bool SOrnamentList::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SOrnament item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}ornamentList_.push_back(item);}}
return true;}
bool SOrnamentList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(UVar32,ornamentList_.size());
for(vector<SOrnament>::const_iterator vit=ornamentList_.begin();vit!=ornamentList_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SOrnamentList::clear(){
type_ = 0;
ornamentList_.clear();
}
bool SOrnamentAdd::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
if(!ornament_.decode(reader)){return false;}
return true;}
bool SOrnamentAdd::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
if(!ornament_.encode(writer)){return false;}
return true;}
void SOrnamentAdd::clear(){
type_ = 0;
ornament_.clear();
}
bool SPlayerLevelReward::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewardDict_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);numDict_[k] = v;}}
return true;}
bool SPlayerLevelReward::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,rewardDict_.size());
for(map<int32_t, int32_t>::const_iterator it=rewardDict_.begin();it!=rewardDict_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,numDict_.size());
for(map<int32_t, int32_t>::const_iterator it=numDict_.begin();it!=numDict_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SPlayerLevelReward::clear(){
rewardDict_.clear();
numDict_.clear();
}
bool SAvatarAdvanceSingle::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,star_);
PACKET_DECODE(Int32,bless_);
PACKET_DECODE(Int32,target_);
return true;}
bool SAvatarAdvanceSingle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,star_);
PACKET_ENCODE(Int32,bless_);
PACKET_ENCODE(Int32,target_);
return true;}
void SAvatarAdvanceSingle::clear(){
level_ = 0;
star_ = 0;
bless_ = 0;
target_ = 0;
}
bool SAvatarAdvanceInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SAvatarAdvanceSingle v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}maps_[k] = v;}}
PACKET_DECODE(Int32,enterId_);
return true;}
bool SAvatarAdvanceInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,maps_.size());
for(map<int32_t, SAvatarAdvanceSingle>::const_iterator it=maps_.begin();it!=maps_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
PACKET_ENCODE(Int32,enterId_);
return true;}
void SAvatarAdvanceInfo::clear(){
maps_.clear();
enterId_ = 0;
}
bool SPlayerJiebaiInfo::decode(CBufferReader &reader) {
PACKET_DECODE(String,jiebaiId_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);msgs::SPublicPlayer item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}jiebaiList_.push_back(item);}}
return true;}
bool SPlayerJiebaiInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,jiebaiId_);
PACKET_ENCODE(UVar32,jiebaiList_.size());
for(vector<msgs::SPublicPlayer>::const_iterator vit=jiebaiList_.begin();vit!=jiebaiList_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerJiebaiInfo::clear(){
jiebaiId_.clear();
jiebaiList_.clear();
}
bool SJiebaiYaoqing::decode(CBufferReader &reader) {
if(!fromPlayer_.decode(reader)){return false;}
return true;}
bool SJiebaiYaoqing::encode(CBufferWriter &writer) const {
if(!fromPlayer_.encode(writer)){return false;}
return true;}
void SJiebaiYaoqing::clear(){
fromPlayer_.clear();
}
bool SJiebaiHuifu::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(Bool,okey_);
return true;}
bool SJiebaiHuifu::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(Bool,okey_);
return true;}
void SJiebaiHuifu::clear(){
entityId_.clear();
okey_ = 0;
}
bool SJiebaiHuifuList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);bool item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Bool,item);huifuList_.push_back(item);}}
return true;}
bool SJiebaiHuifuList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,huifuList_.size());
for(vector<bool>::const_iterator vit=huifuList_.begin();vit!=huifuList_.end();++vit){PACKET_ENCODE(Bool,*vit);}
return true;}
void SJiebaiHuifuList::clear(){
huifuList_.clear();
}
bool SJiebaiCheckResult::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,playerName_);
PACKET_DECODE(Bool,isOnline_);
PACKET_DECODE(Bool,hasItems_);
PACKET_DECODE(Bool,canJiebai_);
return true;}
bool SJiebaiCheckResult::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,playerName_);
PACKET_ENCODE(Bool,isOnline_);
PACKET_ENCODE(Bool,hasItems_);
PACKET_ENCODE(Bool,canJiebai_);
return true;}
void SJiebaiCheckResult::clear(){
entityId_.clear();
playerName_.clear();
isOnline_ = 0;
hasItems_ = 0;
canJiebai_ = 0;
}
bool SJiebaiCheckErrorList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SJiebaiCheckResult item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}errorList_.push_back(item);}}
return true;}
bool SJiebaiCheckErrorList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,errorList_.size());
for(vector<SJiebaiCheckResult>::const_iterator vit=errorList_.begin();vit!=errorList_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SJiebaiCheckErrorList::clear(){
errorList_.clear();
}
bool SJiebaiSuccess::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);msgs::SPublicPlayer item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}playerList_.push_back(item);}}
return true;}
bool SJiebaiSuccess::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,playerList_.size());
for(vector<msgs::SPublicPlayer>::const_iterator vit=playerList_.begin();vit!=playerList_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SJiebaiSuccess::clear(){
playerList_.clear();
}
bool SJiebaiPrepareList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);msgs::SPublicPlayer item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}playerList_.push_back(item);}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);bool item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Bool,item);huifuList_.push_back(item);}}
return true;}
bool SJiebaiPrepareList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,playerList_.size());
for(vector<msgs::SPublicPlayer>::const_iterator vit=playerList_.begin();vit!=playerList_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(UVar32,huifuList_.size());
for(vector<bool>::const_iterator vit=huifuList_.begin();vit!=huifuList_.end();++vit){PACKET_ENCODE(Bool,*vit);}
return true;}
void SJiebaiPrepareList::clear(){
playerList_.clear();
huifuList_.clear();
}
bool SJiebaiToupiao::decode(CBufferReader &reader) {
if(!fromPlayer_.decode(reader)){return false;}
if(!toPlayer_.decode(reader)){return false;}
return true;}
bool SJiebaiToupiao::encode(CBufferWriter &writer) const {
if(!fromPlayer_.encode(writer)){return false;}
if(!toPlayer_.encode(writer)){return false;}
return true;}
void SJiebaiToupiao::clear(){
fromPlayer_.clear();
toPlayer_.clear();
}
bool SJiebaiToupiaoResult::decode(CBufferReader &reader) {
if(!toEntityId_.decode(reader)){return false;}
PACKET_DECODE(Bool,result_);
return true;}
bool SJiebaiToupiaoResult::encode(CBufferWriter &writer) const {
if(!toEntityId_.encode(writer)){return false;}
PACKET_ENCODE(Bool,result_);
return true;}
void SJiebaiToupiaoResult::clear(){
toEntityId_.clear();
result_ = 0;
}
bool SPlayerTreasure::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,drawNum_);
PACKET_DECODE(Int32,useFreeNum_);
PACKET_DECODE(Int32,todayNum_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);leftSelNums_[k] = v;}}
PACKET_DECODE(Bool,hasDraw50_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);drewHis_.push_back(item);}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);hasGotTarget_[k] = v;}}
PACKET_DECODE(Int32,useFree10num_);
return true;}
bool SPlayerTreasure::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,drawNum_);
PACKET_ENCODE(Int32,useFreeNum_);
PACKET_ENCODE(Int32,todayNum_);
PACKET_ENCODE(UVar32,leftSelNums_.size());
for(map<int32_t, int32_t>::const_iterator it=leftSelNums_.begin();it!=leftSelNums_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Bool,hasDraw50_);
PACKET_ENCODE(UVar32,drewHis_.size());
for(vector<int32_t>::const_iterator vit=drewHis_.begin();vit!=drewHis_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(UVar32,hasGotTarget_.size());
for(map<int32_t, int32_t>::const_iterator it=hasGotTarget_.begin();it!=hasGotTarget_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,useFree10num_);
return true;}
void SPlayerTreasure::clear(){
type_ = 0;
drawNum_ = 0;
useFreeNum_ = 0;
todayNum_ = 0;
leftSelNums_.clear();
hasDraw50_ = 0;
drewHis_.clear();
hasGotTarget_.clear();
useFree10num_ = 0;
}
bool SPlayerTreasureInfo::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SPlayerTreasure item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool SPlayerTreasureInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<SPlayerTreasure>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerTreasureInfo::clear(){
list_.clear();
}
bool STreasurePoolSuc::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,drawPerType_);
PACKET_DECODE(Int32,drawGold_);
return true;}
bool STreasurePoolSuc::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,drawPerType_);
PACKET_ENCODE(Int32,drawGold_);
return true;}
void STreasurePoolSuc::clear(){
drawPerType_ = 0;
drawGold_ = 0;
}
bool SGuildTerritory::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Bool,hasReward_);
return true;}
bool SGuildTerritory::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Bool,hasReward_);
return true;}
void SGuildTerritory::clear(){
level_ = 0;
hasReward_ = 0;
}
bool SGuild::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,guildId_);
PACKET_DECODE(String,guildName_);
PACKET_DECODE(String,purpose_);
PACKET_DECODE(Int32,leaderId_);
PACKET_DECODE(String,leaderName_);
PACKET_DECODE(Int64,totalCombat_);
PACKET_DECODE(Int16,level_);
PACKET_DECODE(Int64,joinCombat_);
PACKET_DECODE(Int16,joinVip_);
PACKET_DECODE(Int16,curMemberNum_);
PACKET_DECODE(Int16,maxMemberNum_);
PACKET_DECODE(Int64,createDt_);
PACKET_DECODE(Int16,joinListNum_);
PACKET_DECODE(Int32,guildFund_);
PACKET_DECODE(Int64,guildDt_);
PACKET_DECODE(Int16,position_);
PACKET_DECODE(Int32,contribute_);
PACKET_DECODE(Int32,totalFund_);
PACKET_DECODE(Int32,totalContribute_);
PACKET_DECODE(Int16,signNum_);
PACKET_DECODE(String,buildings_);
PACKET_DECODE(Bool,isSign_);
PACKET_DECODE(Int16,donateGold_);
PACKET_DECODE(Int16,donateCoin_);
PACKET_DECODE(Int32,warehouseScore_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SGuildTerritory v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}territorys_[k] = v;}}
PACKET_DECODE(Int32,curGuildBoss_);
PACKET_DECODE(Int32,guildBossMinGot_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);guildBossGotLst_.push_back(item);}}
PACKET_DECODE(Int32,xianCaoNum_);
PACKET_DECODE(Bool,guildWarSuccess_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);guildWarRankRewards_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);guildWarHasGots_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);requestGuilds_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);responseGuilds_[k] = v;}}
return true;}
bool SGuild::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,guildId_);
PACKET_ENCODE(String,guildName_);
PACKET_ENCODE(String,purpose_);
PACKET_ENCODE(Int32,leaderId_);
PACKET_ENCODE(String,leaderName_);
PACKET_ENCODE(Int64,totalCombat_);
PACKET_ENCODE(Int16,level_);
PACKET_ENCODE(Int64,joinCombat_);
PACKET_ENCODE(Int16,joinVip_);
PACKET_ENCODE(Int16,curMemberNum_);
PACKET_ENCODE(Int16,maxMemberNum_);
PACKET_ENCODE(Int64,createDt_);
PACKET_ENCODE(Int16,joinListNum_);
PACKET_ENCODE(Int32,guildFund_);
PACKET_ENCODE(Int64,guildDt_);
PACKET_ENCODE(Int16,position_);
PACKET_ENCODE(Int32,contribute_);
PACKET_ENCODE(Int32,totalFund_);
PACKET_ENCODE(Int32,totalContribute_);
PACKET_ENCODE(Int16,signNum_);
PACKET_ENCODE(String,buildings_);
PACKET_ENCODE(Bool,isSign_);
PACKET_ENCODE(Int16,donateGold_);
PACKET_ENCODE(Int16,donateCoin_);
PACKET_ENCODE(Int32,warehouseScore_);
PACKET_ENCODE(UVar32,territorys_.size());
for(map<int32_t, SGuildTerritory>::const_iterator it=territorys_.begin();it!=territorys_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
PACKET_ENCODE(Int32,curGuildBoss_);
PACKET_ENCODE(Int32,guildBossMinGot_);
PACKET_ENCODE(UVar32,guildBossGotLst_.size());
for(vector<int32_t>::const_iterator vit=guildBossGotLst_.begin();vit!=guildBossGotLst_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(Int32,xianCaoNum_);
PACKET_ENCODE(Bool,guildWarSuccess_);
PACKET_ENCODE(UVar32,guildWarRankRewards_.size());
for(map<int32_t, int32_t>::const_iterator it=guildWarRankRewards_.begin();it!=guildWarRankRewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,guildWarHasGots_.size());
for(map<int32_t, int32_t>::const_iterator it=guildWarHasGots_.begin();it!=guildWarHasGots_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,requestGuilds_.size());
for(map<int32_t, int32_t>::const_iterator it=requestGuilds_.begin();it!=requestGuilds_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,responseGuilds_.size());
for(map<int32_t, int32_t>::const_iterator it=responseGuilds_.begin();it!=responseGuilds_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SGuild::clear(){
guildId_ = 0;
guildName_.clear();
purpose_.clear();
leaderId_ = 0;
leaderName_.clear();
totalCombat_ = 0;
level_ = 0;
joinCombat_ = 0;
joinVip_ = 0;
curMemberNum_ = 0;
maxMemberNum_ = 0;
createDt_ = 0;
joinListNum_ = 0;
guildFund_ = 0;
guildDt_ = 0;
position_ = 0;
contribute_ = 0;
totalFund_ = 0;
totalContribute_ = 0;
signNum_ = 0;
buildings_.clear();
isSign_ = 0;
donateGold_ = 0;
donateCoin_ = 0;
warehouseScore_ = 0;
territorys_.clear();
curGuildBoss_ = 0;
guildBossMinGot_ = 0;
guildBossGotLst_.clear();
xianCaoNum_ = 0;
guildWarSuccess_ = 0;
guildWarRankRewards_.clear();
guildWarHasGots_.clear();
requestGuilds_.clear();
responseGuilds_.clear();
}
bool SGuildInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,guildId_);
PACKET_DECODE(String,guildName_);
PACKET_DECODE(Int32,leaderId_);
PACKET_DECODE(String,leaderName_);
PACKET_DECODE(Int64,totalCombat_);
PACKET_DECODE(Int64,joinCombat_);
PACKET_DECODE(Int16,joinVip_);
PACKET_DECODE(Int16,guildLevel_);
PACKET_DECODE(Int16,curMemberNum_);
PACKET_DECODE(Int16,maxMemberNum_);
PACKET_DECODE(Bool,isApply_);
PACKET_DECODE(Int64,createDt_);
return true;}
bool SGuildInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,guildId_);
PACKET_ENCODE(String,guildName_);
PACKET_ENCODE(Int32,leaderId_);
PACKET_ENCODE(String,leaderName_);
PACKET_ENCODE(Int64,totalCombat_);
PACKET_ENCODE(Int64,joinCombat_);
PACKET_ENCODE(Int16,joinVip_);
PACKET_ENCODE(Int16,guildLevel_);
PACKET_ENCODE(Int16,curMemberNum_);
PACKET_ENCODE(Int16,maxMemberNum_);
PACKET_ENCODE(Bool,isApply_);
PACKET_ENCODE(Int64,createDt_);
return true;}
void SGuildInfo::clear(){
guildId_ = 0;
guildName_.clear();
leaderId_ = 0;
leaderName_.clear();
totalCombat_ = 0;
joinCombat_ = 0;
joinVip_ = 0;
guildLevel_ = 0;
curMemberNum_ = 0;
maxMemberNum_ = 0;
isApply_ = 0;
createDt_ = 0;
}
bool SGuildMember::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Int16,sex_);
PACKET_DECODE(Int16,career_);
PACKET_DECODE(Int16,careerLevel_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);ornaments_[k] = v;}}
PACKET_DECODE(Int16,level_);
PACKET_DECODE(Int16,vip_);
PACKET_DECODE(Int64,combat_);
PACKET_DECODE(Int16,position_);
PACKET_DECODE(Int32,totalContribute_);
PACKET_DECODE(Int32,offlineTime_);
PACKET_DECODE(Bool,hadGroupFightTeam_);
return true;}
bool SGuildMember::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int16,sex_);
PACKET_ENCODE(Int16,career_);
PACKET_ENCODE(Int16,careerLevel_);
PACKET_ENCODE(UVar32,ornaments_.size());
for(map<int16_t, int32_t>::const_iterator it=ornaments_.begin();it!=ornaments_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int16,level_);
PACKET_ENCODE(Int16,vip_);
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(Int16,position_);
PACKET_ENCODE(Int32,totalContribute_);
PACKET_ENCODE(Int32,offlineTime_);
PACKET_ENCODE(Bool,hadGroupFightTeam_);
return true;}
void SGuildMember::clear(){
playerId_ = 0;
name_.clear();
sex_ = 0;
career_ = 0;
careerLevel_ = 0;
ornaments_.clear();
level_ = 0;
vip_ = 0;
combat_ = 0;
position_ = 0;
totalContribute_ = 0;
offlineTime_ = 0;
hadGroupFightTeam_ = 0;
}
bool SGuildJoin::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Int16,sex_);
PACKET_DECODE(Int16,career_);
PACKET_DECODE(Int16,careerLevel_);
PACKET_DECODE(Int16,level_);
PACKET_DECODE(Int16,vip_);
PACKET_DECODE(Int64,combat_);
PACKET_DECODE(Int64,joinDt_);
return true;}
bool SGuildJoin::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int16,sex_);
PACKET_ENCODE(Int16,career_);
PACKET_ENCODE(Int16,careerLevel_);
PACKET_ENCODE(Int16,level_);
PACKET_ENCODE(Int16,vip_);
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(Int64,joinDt_);
return true;}
void SGuildJoin::clear(){
playerId_ = 0;
name_.clear();
sex_ = 0;
career_ = 0;
careerLevel_ = 0;
level_ = 0;
vip_ = 0;
combat_ = 0;
joinDt_ = 0;
}
bool SGuildUpdateData::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,data1_);
PACKET_DECODE(Int64,data2_);
PACKET_DECODE(String,data3_);
return true;}
bool SGuildUpdateData::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,data1_);
PACKET_ENCODE(Int64,data2_);
PACKET_ENCODE(String,data3_);
return true;}
void SGuildUpdateData::clear(){
data1_ = 0;
data2_ = 0;
data3_.clear();
}
bool SGuildUpdateJoinList::decode(CBufferReader &reader) {
PACKET_DECODE(Int16,operNum_);
PACKET_DECODE(Int32,playerId_);
join_ = MsgPool::Instance()->DecodeMsg(reader);
PACKET_DECODE(Bool,topCombat_);
PACKET_DECODE(Bool,topVip_);
return true;}
bool SGuildUpdateJoinList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int16,operNum_);
PACKET_ENCODE(Int32,playerId_);
if(!MsgPool::Instance()->EncodeMsg(writer, join_)){return false;}
PACKET_ENCODE(Bool,topCombat_);
PACKET_ENCODE(Bool,topVip_);
return true;}
void SGuildUpdateJoinList::clear(){
operNum_ = 0;
playerId_ = 0;
join_ = NULL;
topCombat_ = 0;
topVip_ = 0;
}
bool SGuildUpdateMemberNum::decode(CBufferReader &reader) {
PACKET_DECODE(Int16,totalNum_);
PACKET_DECODE(Int16,operNum_);
if(!memberId_.decode(reader)){return false;}
member_ = MsgPool::Instance()->DecodeMsg(reader);
return true;}
bool SGuildUpdateMemberNum::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int16,totalNum_);
PACKET_ENCODE(Int16,operNum_);
if(!memberId_.encode(writer)){return false;}
if(!MsgPool::Instance()->EncodeMsg(writer, member_)){return false;}
return true;}
void SGuildUpdateMemberNum::clear(){
totalNum_ = 0;
operNum_ = 0;
memberId_.clear();
member_ = NULL;
}
bool SGuildUpdateSetting::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,joinCombat_);
PACKET_DECODE(Int16,joinVip_);
return true;}
bool SGuildUpdateSetting::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,joinCombat_);
PACKET_ENCODE(Int16,joinVip_);
return true;}
void SGuildUpdateSetting::clear(){
joinCombat_ = 0;
joinVip_ = 0;
}
bool SGuildUpdateMerge::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);requestGuilds_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);responseGuilds_[k] = v;}}
return true;}
bool SGuildUpdateMerge::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,requestGuilds_.size());
for(map<int32_t, int32_t>::const_iterator it=requestGuilds_.begin();it!=requestGuilds_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,responseGuilds_.size());
for(map<int32_t, int32_t>::const_iterator it=responseGuilds_.begin();it!=responseGuilds_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SGuildUpdateMerge::clear(){
requestGuilds_.clear();
responseGuilds_.clear();
}
bool SGuildMemberUpdateData::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,data1_);
PACKET_DECODE(Int32,data2_);
return true;}
bool SGuildMemberUpdateData::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,data1_);
PACKET_ENCODE(Int32,data2_);
return true;}
void SGuildMemberUpdateData::clear(){
data1_ = 0;
data2_ = 0;
}
bool SGuildMemberUpdateContribute::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,contri_);
PACKET_DECODE(Int32,totalContri_);
PACKET_DECODE(Int32,totalFund_);
return true;}
bool SGuildMemberUpdateContribute::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,contri_);
PACKET_ENCODE(Int32,totalContri_);
PACKET_ENCODE(Int32,totalFund_);
return true;}
void SGuildMemberUpdateContribute::clear(){
contri_ = 0;
totalContri_ = 0;
totalFund_ = 0;
}
bool SGuildItem::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,id_);
PACKET_DECODE(Int32,itemId_);
PACKET_DECODE(String,itemExtend_);
return true;}
bool SGuildItem::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,id_);
PACKET_ENCODE(Int32,itemId_);
PACKET_ENCODE(String,itemExtend_);
return true;}
void SGuildItem::clear(){
id_ = 0;
itemId_ = 0;
itemExtend_.clear();
}
bool SGuildItemRecord::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,playerName_);
PACKET_DECODE(Int16,position_);
PACKET_DECODE(Int16,oper_);
PACKET_DECODE(Int32,id_);
PACKET_DECODE(Int32,itemId_);
PACKET_DECODE(String,itemExtend_);
PACKET_DECODE(Int64,recordDt_);
return true;}
bool SGuildItemRecord::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,playerName_);
PACKET_ENCODE(Int16,position_);
PACKET_ENCODE(Int16,oper_);
PACKET_ENCODE(Int32,id_);
PACKET_ENCODE(Int32,itemId_);
PACKET_ENCODE(String,itemExtend_);
PACKET_ENCODE(Int64,recordDt_);
return true;}
void SGuildItemRecord::clear(){
playerId_ = 0;
playerName_.clear();
position_ = 0;
oper_ = 0;
id_ = 0;
itemId_ = 0;
itemExtend_.clear();
recordDt_ = 0;
}
bool SAddGuildMemberContribute::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,value_);
return true;}
bool SAddGuildMemberContribute::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,value_);
return true;}
void SAddGuildMemberContribute::clear(){
value_ = 0;
}
bool SGuildMemberUpdateGuildBoss::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,curGuildBoss_);
PACKET_DECODE(Int32,guildBossMinGot_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);guildBossGotList_.push_back(item);}}
return true;}
bool SGuildMemberUpdateGuildBoss::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,curGuildBoss_);
PACKET_ENCODE(Int32,guildBossMinGot_);
PACKET_ENCODE(UVar32,guildBossGotList_.size());
for(vector<int32_t>::const_iterator vit=guildBossGotList_.begin();vit!=guildBossGotList_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SGuildMemberUpdateGuildBoss::clear(){
curGuildBoss_ = 0;
guildBossMinGot_ = 0;
guildBossGotList_.clear();
}
bool SGuildMiniInfo::decode(CBufferReader &reader) {
if(!guildId_.decode(reader)){return false;}
PACKET_DECODE(String,guildName_);
if(!leaderId_.decode(reader)){return false;}
PACKET_DECODE(String,leaderName_);
return true;}
bool SGuildMiniInfo::encode(CBufferWriter &writer) const {
if(!guildId_.encode(writer)){return false;}
PACKET_ENCODE(String,guildName_);
if(!leaderId_.encode(writer)){return false;}
PACKET_ENCODE(String,leaderName_);
return true;}
void SGuildMiniInfo::clear(){
guildId_.clear();
guildName_.clear();
leaderId_.clear();
leaderName_.clear();
}
bool SZhanqi::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,level_);
return true;}
bool SZhanqi::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,level_);
return true;}
void SZhanqi::clear(){
level_ = 0;
}
bool SZhanqiInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,puton_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SZhanqi v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}zhanqis_[k] = v;}}
PACKET_DECODE(Int32,tryId_);
PACKET_DECODE(Int64,deadDt_);
return true;}
bool SZhanqiInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,puton_);
PACKET_ENCODE(UVar32,zhanqis_.size());
for(map<int32_t, SZhanqi>::const_iterator it=zhanqis_.begin();it!=zhanqis_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
PACKET_ENCODE(Int32,tryId_);
PACKET_ENCODE(Int64,deadDt_);
return true;}
void SZhanqiInfo::clear(){
puton_ = 0;
zhanqis_.clear();
tryId_ = 0;
deadDt_ = 0;
}
bool SZhanqiFightData::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,engineNum_);
PACKET_DECODE(Int32,engineSpeed_);
PACKET_DECODE(Int32,engineHurt_);
return true;}
bool SZhanqiFightData::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,engineNum_);
PACKET_ENCODE(Int32,engineSpeed_);
PACKET_ENCODE(Int32,engineHurt_);
return true;}
void SZhanqiFightData::clear(){
engineNum_ = 0;
engineSpeed_ = 0;
engineHurt_ = 0;
}
bool SPlayerMissionList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);dbs::TPlayerMission item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}missions_.push_back(item);}}
return true;}
bool SPlayerMissionList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,missions_.size());
for(vector<dbs::TPlayerMission>::const_iterator vit=missions_.begin();vit!=missions_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerMissionList::clear(){
missions_.clear();
}
bool SMissionMonster::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,monsterId_);
return true;}
bool SMissionMonster::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,monsterId_);
return true;}
void SMissionMonster::clear(){
monsterId_ = 0;
}
bool SRoundMission::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,round_);
PACKET_DECODE(Int32,missionId_);
PACKET_DECODE(Int32,extraRound_);
PACKET_DECODE(Int32,lotteryTimes_);
PACKET_DECODE(Int32,reward_);
return true;}
bool SRoundMission::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,round_);
PACKET_ENCODE(Int32,missionId_);
PACKET_ENCODE(Int32,extraRound_);
PACKET_ENCODE(Int32,lotteryTimes_);
PACKET_ENCODE(Int32,reward_);
return true;}
void SRoundMission::clear(){
type_ = 0;
round_ = 0;
missionId_ = 0;
extraRound_ = 0;
lotteryTimes_ = 0;
reward_ = 0;
}
bool SRoundMissionList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SRoundMission item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool SRoundMissionList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<SRoundMission>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SRoundMissionList::clear(){
list_.clear();
}
bool SMissionMonsterPlan::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);monsterPlans_[k] = v;}}
return true;}
bool SMissionMonsterPlan::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,monsterPlans_.size());
for(map<int32_t, int32_t>::const_iterator it=monsterPlans_.begin();it!=monsterPlans_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SMissionMonsterPlan::clear(){
monsterPlans_.clear();
}
bool SEntityUpdate::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(Int16,updateType_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int64_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int64,item);updateData_.push_back(item);}}
PACKET_DECODE(String,updateStr_);
return true;}
bool SEntityUpdate::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(Int16,updateType_);
PACKET_ENCODE(UVar32,updateData_.size());
for(vector<int64_t>::const_iterator vit=updateData_.begin();vit!=updateData_.end();++vit){PACKET_ENCODE(Int64,*vit);}
PACKET_ENCODE(String,updateStr_);
return true;}
void SEntityUpdate::clear(){
entityId_.clear();
updateType_ = 0;
updateData_.clear();
updateStr_.clear();
}
bool SUpdateDiffAttr::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int64,combat_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int64_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int64,v);diffAttr_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int64_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int64,v);diffCopyAttr_[k] = v;}}
return true;}
bool SUpdateDiffAttr::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(UVar32,diffAttr_.size());
for(map<int16_t, int64_t>::const_iterator it=diffAttr_.begin();it!=diffAttr_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int64,it->second);}
PACKET_ENCODE(UVar32,diffCopyAttr_.size());
for(map<int16_t, int64_t>::const_iterator it=diffCopyAttr_.begin();it!=diffCopyAttr_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int64,it->second);}
return true;}
void SUpdateDiffAttr::clear(){
roleId_ = 0;
combat_ = 0;
diffAttr_.clear();
diffCopyAttr_.clear();
}
bool SUpdateTotalAttrDiff::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int64_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int64,v);attr_[k] = v;}}
return true;}
bool SUpdateTotalAttrDiff::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,attr_.size());
for(map<int16_t, int64_t>::const_iterator it=attr_.begin();it!=attr_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int64,it->second);}
return true;}
void SUpdateTotalAttrDiff::clear(){
attr_.clear();
}
bool SEntityUpdateEntityShows::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);shows_[k] = v;}}
return true;}
bool SEntityUpdateEntityShows::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,shows_.size());
for(map<int16_t, int32_t>::const_iterator it=shows_.begin();it!=shows_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SEntityUpdateEntityShows::clear(){
entityId_.clear();
shows_.clear();
}
bool SEntityUpdateEntityValues::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);values_[k] = v;}}
return true;}
bool SEntityUpdateEntityValues::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,values_.size());
for(map<int16_t, int32_t>::const_iterator it=values_.begin();it!=values_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SEntityUpdateEntityValues::clear(){
entityId_.clear();
values_.clear();
}
bool SEntityUpdateExtraAttr::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int64_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int64,v);attrMap_[k] = v;}}
return true;}
bool SEntityUpdateExtraAttr::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(UVar32,attrMap_.size());
for(map<int16_t, int64_t>::const_iterator it=attrMap_.begin();it!=attrMap_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int64,it->second);}
return true;}
void SEntityUpdateExtraAttr::clear(){
roleId_ = 0;
attrMap_.clear();
}
bool SEntityTotalAttr::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,code_);
if(!entityId_.decode(reader)){return false;}
if(!totalAttr_.decode(reader)){return false;}
return true;}
bool SEntityTotalAttr::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,code_);
if(!entityId_.encode(writer)){return false;}
if(!totalAttr_.encode(writer)){return false;}
return true;}
void SEntityTotalAttr::clear(){
code_ = 0;
entityId_.clear();
totalAttr_.clear();
}
bool SBuffInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,buffId_);
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int32,overlay_);
PACKET_DECODE(Int32,count_);
PACKET_DECODE(Int64,value_);
PACKET_DECODE(Int64,endDt_);
PACKET_DECODE(Int64,extend_);
return true;}
bool SBuffInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,buffId_);
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int32,overlay_);
PACKET_ENCODE(Int32,count_);
PACKET_ENCODE(Int64,value_);
PACKET_ENCODE(Int64,endDt_);
PACKET_ENCODE(Int64,extend_);
return true;}
void SBuffInfo::clear(){
buffId_ = 0;
roleId_ = 0;
overlay_ = 0;
count_ = 0;
value_ = 0;
endDt_ = 0;
extend_ = 0;
}
bool SFightData::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int16,sex_);
PACKET_DECODE(Int16,career_);
PACKET_DECODE(Int16,careerLevel_);
PACKET_DECODE(Int64,combat_);
PACKET_DECODE(Int16,status_);
PACKET_DECODE(Int64,statusEnd_);
if(!spacePos_.decode(reader)){return false;}
PACKET_DECODE(Int16,direction_);
PACKET_DECODE(Int16,speed_);
PACKET_DECODE(Int16,bodySize_);
PACKET_DECODE(Int16,camp_);
PACKET_DECODE(Int16,force_);
PACKET_DECODE(Int16,level_);
PACKET_DECODE(Int32,vipLevel_);
PACKET_DECODE(Int64,curLife_);
PACKET_DECODE(Int64,inPower_);
PACKET_DECODE(Int32,avaLife_);
PACKET_DECODE(Int32,curMagic_);
PACKET_DECODE(Int16,fightMode_);
PACKET_DECODE(Int32,touxian_);
PACKET_DECODE(Int32,statusMask_);
PACKET_DECODE(Bool,isRide_);
if(!warHorse_.decode(reader)){return false;}
PACKET_DECODE(Bool,isHide_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);entityShows_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);entityValues_[k] = v;}}
if(!fightAttr_.decode(reader)){return false;}
if(!totalAttr_.decode(reader)){return false;}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int64_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int64,v);copyAttr_[k] = v;}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);skills_.push_back(item);}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SBuffInfo item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}buffs_.push_back(item);}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);runes_.push_back(item);}}
teamData_ = MsgPool::Instance()->DecodeMsg(reader);
guildData_ = MsgPool::Instance()->DecodeMsg(reader);
return true;}
bool SFightData::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int16,sex_);
PACKET_ENCODE(Int16,career_);
PACKET_ENCODE(Int16,careerLevel_);
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(Int16,status_);
PACKET_ENCODE(Int64,statusEnd_);
if(!spacePos_.encode(writer)){return false;}
PACKET_ENCODE(Int16,direction_);
PACKET_ENCODE(Int16,speed_);
PACKET_ENCODE(Int16,bodySize_);
PACKET_ENCODE(Int16,camp_);
PACKET_ENCODE(Int16,force_);
PACKET_ENCODE(Int16,level_);
PACKET_ENCODE(Int32,vipLevel_);
PACKET_ENCODE(Int64,curLife_);
PACKET_ENCODE(Int64,inPower_);
PACKET_ENCODE(Int32,avaLife_);
PACKET_ENCODE(Int32,curMagic_);
PACKET_ENCODE(Int16,fightMode_);
PACKET_ENCODE(Int32,touxian_);
PACKET_ENCODE(Int32,statusMask_);
PACKET_ENCODE(Bool,isRide_);
if(!warHorse_.encode(writer)){return false;}
PACKET_ENCODE(Bool,isHide_);
PACKET_ENCODE(UVar32,entityShows_.size());
for(map<int16_t, int32_t>::const_iterator it=entityShows_.begin();it!=entityShows_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,entityValues_.size());
for(map<int16_t, int32_t>::const_iterator it=entityValues_.begin();it!=entityValues_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
if(!fightAttr_.encode(writer)){return false;}
if(!totalAttr_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,copyAttr_.size());
for(map<int16_t, int64_t>::const_iterator it=copyAttr_.begin();it!=copyAttr_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int64,it->second);}
PACKET_ENCODE(UVar32,skills_.size());
for(vector<int32_t>::const_iterator vit=skills_.begin();vit!=skills_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(UVar32,buffs_.size());
for(vector<SBuffInfo>::const_iterator vit=buffs_.begin();vit!=buffs_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(UVar32,runes_.size());
for(vector<int32_t>::const_iterator vit=runes_.begin();vit!=runes_.end();++vit){PACKET_ENCODE(Int32,*vit);}
if(!MsgPool::Instance()->EncodeMsg(writer, teamData_)){return false;}
if(!MsgPool::Instance()->EncodeMsg(writer, guildData_)){return false;}
return true;}
void SFightData::clear(){
entityId_.clear();
name_.clear();
sex_ = 0;
career_ = 0;
careerLevel_ = 0;
combat_ = 0;
status_ = 0;
statusEnd_ = 0;
spacePos_.clear();
direction_ = 0;
speed_ = 0;
bodySize_ = 0;
camp_ = 0;
force_ = 0;
level_ = 0;
vipLevel_ = 0;
curLife_ = 0;
inPower_ = 0;
avaLife_ = 0;
curMagic_ = 0;
fightMode_ = 0;
touxian_ = 0;
statusMask_ = 0;
isRide_ = 0;
warHorse_.clear();
isHide_ = 0;
entityShows_.clear();
entityValues_.clear();
fightAttr_.clear();
totalAttr_.clear();
copyAttr_.clear();
skills_.clear();
buffs_.clear();
runes_.clear();
teamData_ = NULL;
guildData_ = NULL;
}
bool SFightPlayer::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(Int16,cellLine_);
PACKET_DECODE(Int32,spaceId_);
if(!spacePos_.decode(reader)){return false;}
PACKET_DECODE(Int32,copyCode_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Int16,career_);
PACKET_DECODE(Int16,careerLevel_);
PACKET_DECODE(Int16,camp_);
PACKET_DECODE(Int16,level_);
PACKET_DECODE(Int32,vipLevel_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);ornaments_[k] = v;}}
PACKET_DECODE(Int64,combat_);
PACKET_DECODE(Int16,fightMode_);
PACKET_DECODE(Int32,hangLevel_);
PACKET_DECODE(Int16,nuqi_);
PACKET_DECODE(Int16,nuqiRecover_);
PACKET_DECODE(Int32,zhanling_);
PACKET_DECODE(Int32,godRingAttackLevel_);
PACKET_DECODE(Int32,godRingDefenseLevel_);
teamData_ = MsgPool::Instance()->DecodeMsg(reader);
guildData_ = MsgPool::Instance()->DecodeMsg(reader);
mateData_ = MsgPool::Instance()->DecodeMsg(reader);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SFightData item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}fightDatas_.push_back(item);}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);dragonSoulAttr_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);addCopyDropRate_[k] = v;}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);flyUpSkills_.push_back(item);}}
PACKET_DECODE(Int32,zhanqiAtkPer_);
PACKET_DECODE(Int32,zhanqiHurtPer_);
PACKET_DECODE(Int32,officialId_);
PACKET_DECODE(Int32,crossOfficialId_);
PACKET_DECODE(String,jiebaiId_);
PACKET_DECODE(Bool,isBeCaller_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);roleZhanWei_[k] = v;}}
PACKET_DECODE(Int16,oldServerId_);
return true;}
bool SFightPlayer::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(Int16,cellLine_);
PACKET_ENCODE(Int32,spaceId_);
if(!spacePos_.encode(writer)){return false;}
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int16,career_);
PACKET_ENCODE(Int16,careerLevel_);
PACKET_ENCODE(Int16,camp_);
PACKET_ENCODE(Int16,level_);
PACKET_ENCODE(Int32,vipLevel_);
PACKET_ENCODE(UVar32,ornaments_.size());
for(map<int16_t, int32_t>::const_iterator it=ornaments_.begin();it!=ornaments_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(Int16,fightMode_);
PACKET_ENCODE(Int32,hangLevel_);
PACKET_ENCODE(Int16,nuqi_);
PACKET_ENCODE(Int16,nuqiRecover_);
PACKET_ENCODE(Int32,zhanling_);
PACKET_ENCODE(Int32,godRingAttackLevel_);
PACKET_ENCODE(Int32,godRingDefenseLevel_);
if(!MsgPool::Instance()->EncodeMsg(writer, teamData_)){return false;}
if(!MsgPool::Instance()->EncodeMsg(writer, guildData_)){return false;}
if(!MsgPool::Instance()->EncodeMsg(writer, mateData_)){return false;}
PACKET_ENCODE(UVar32,fightDatas_.size());
for(vector<SFightData>::const_iterator vit=fightDatas_.begin();vit!=fightDatas_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(UVar32,dragonSoulAttr_.size());
for(map<int32_t, int32_t>::const_iterator it=dragonSoulAttr_.begin();it!=dragonSoulAttr_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,addCopyDropRate_.size());
for(map<int32_t, int32_t>::const_iterator it=addCopyDropRate_.begin();it!=addCopyDropRate_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,flyUpSkills_.size());
for(vector<int32_t>::const_iterator vit=flyUpSkills_.begin();vit!=flyUpSkills_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(Int32,zhanqiAtkPer_);
PACKET_ENCODE(Int32,zhanqiHurtPer_);
PACKET_ENCODE(Int32,officialId_);
PACKET_ENCODE(Int32,crossOfficialId_);
PACKET_ENCODE(String,jiebaiId_);
PACKET_ENCODE(Bool,isBeCaller_);
PACKET_ENCODE(UVar32,roleZhanWei_.size());
for(map<int32_t, int32_t>::const_iterator it=roleZhanWei_.begin();it!=roleZhanWei_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int16,oldServerId_);
return true;}
void SFightPlayer::clear(){
entityId_.clear();
cellLine_ = 0;
spaceId_ = 0;
spacePos_.clear();
copyCode_ = 0;
name_.clear();
career_ = 0;
careerLevel_ = 0;
camp_ = 0;
level_ = 0;
vipLevel_ = 0;
ornaments_.clear();
combat_ = 0;
fightMode_ = 0;
hangLevel_ = 0;
nuqi_ = 0;
nuqiRecover_ = 0;
zhanling_ = 0;
godRingAttackLevel_ = 0;
godRingDefenseLevel_ = 0;
teamData_ = NULL;
guildData_ = NULL;
mateData_ = NULL;
fightDatas_.clear();
dragonSoulAttr_.clear();
addCopyDropRate_.clear();
flyUpSkills_.clear();
zhanqiAtkPer_ = 0;
zhanqiHurtPer_ = 0;
officialId_ = 0;
crossOfficialId_ = 0;
jiebaiId_.clear();
isBeCaller_ = 0;
roleZhanWei_.clear();
oldServerId_ = 0;
}
bool SDisplayData::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int16,status_);
PACKET_DECODE(Int64,statusEnd_);
PACKET_DECODE(Int32,spaceId_);
if(!spacePos_.decode(reader)){return false;}
PACKET_DECODE(Int32,copyCode_);
PACKET_DECODE(Int16,direction_);
PACKET_DECODE(Int16,speed_);
return true;}
bool SDisplayData::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int16,status_);
PACKET_ENCODE(Int64,statusEnd_);
PACKET_ENCODE(Int32,spaceId_);
if(!spacePos_.encode(writer)){return false;}
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(Int16,direction_);
PACKET_ENCODE(Int16,speed_);
return true;}
void SDisplayData::clear(){
entityId_.clear();
name_.clear();
status_ = 0;
statusEnd_ = 0;
spaceId_ = 0;
spacePos_.clear();
copyCode_ = 0;
direction_ = 0;
speed_ = 0;
}
bool SPlayerSkillInfo::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);dbs::TPlayerSkill item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}skills_.push_back(item);}}
return true;}
bool SPlayerSkillInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,skills_.size());
for(vector<dbs::TPlayerSkill>::const_iterator vit=skills_.begin();vit!=skills_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerSkillInfo::clear(){
skills_.clear();
}
bool SUpdateSkill::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);dbs::TPlayerSkill item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}skills_.push_back(item);}}
PACKET_DECODE(Byte,oper_);
return true;}
bool SUpdateSkill::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,skills_.size());
for(vector<dbs::TPlayerSkill>::const_iterator vit=skills_.begin();vit!=skills_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(Byte,oper_);
return true;}
void SUpdateSkill::clear(){
skills_.clear();
oper_ = 0;
}
bool SFightUpdate::decode(CBufferReader &reader) {
PACKET_DECODE(Int16,updateType_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int64_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int64,item);updateData_.push_back(item);}}
return true;}
bool SFightUpdate::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int16,updateType_);
PACKET_ENCODE(UVar32,updateData_.size());
for(vector<int64_t>::const_iterator vit=updateData_.begin();vit!=updateData_.end();++vit){PACKET_ENCODE(Int64,*vit);}
return true;}
void SFightUpdate::clear(){
updateType_ = 0;
updateData_.clear();
}
bool SBeginFight::decode(CBufferReader &reader) {
PACKET_DECODE(Int16,attackId_);
PACKET_DECODE(Int32,skillId_);
if(!fromEntity_.decode(reader)){return false;}
if(!centerPoint_.decode(reader)){return false;}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Identity item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}toEntitys_.push_back(item);}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SFightUpdate item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}propertyUpdates_.push_back(item);}}
return true;}
bool SBeginFight::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int16,attackId_);
PACKET_ENCODE(Int32,skillId_);
if(!fromEntity_.encode(writer)){return false;}
if(!centerPoint_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,toEntitys_.size());
for(vector<Identity>::const_iterator vit=toEntitys_.begin();vit!=toEntitys_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(UVar32,propertyUpdates_.size());
for(vector<SFightUpdate>::const_iterator vit=propertyUpdates_.begin();vit!=propertyUpdates_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SBeginFight::clear(){
attackId_ = 0;
skillId_ = 0;
fromEntity_.clear();
centerPoint_.clear();
toEntitys_.clear();
propertyUpdates_.clear();
}
bool SSkillCast::decode(CBufferReader &reader) {
if(!beginFight_.decode(reader)){return false;}
PACKET_DECODE(Int64,endTime_);
return true;}
bool SSkillCast::encode(CBufferWriter &writer) const {
if(!beginFight_.encode(writer)){return false;}
PACKET_ENCODE(Int64,endTime_);
return true;}
void SSkillCast::clear(){
beginFight_.clear();
endTime_ = 0;
}
bool SSkillStopLead::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,skillId_);
PACKET_DECODE(Int32,series_);
PACKET_DECODE(Int64,cdTime_);
return true;}
bool SSkillStopLead::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,skillId_);
PACKET_ENCODE(Int32,series_);
PACKET_ENCODE(Int64,cdTime_);
return true;}
void SSkillStopLead::clear(){
skillId_ = 0;
series_ = 0;
cdTime_ = 0;
}
bool SBeatMove::decode(CBufferReader &reader) {
if(!fromPoint_.decode(reader)){return false;}
if(!toPoint_.decode(reader)){return false;}
return true;}
bool SBeatMove::encode(CBufferWriter &writer) const {
if(!fromPoint_.encode(writer)){return false;}
if(!toPoint_.encode(writer)){return false;}
return true;}
void SBeatMove::clear(){
fromPoint_.clear();
toPoint_.clear();
}
bool SFightInfo::decode(CBufferReader &reader) {
if(!fromEntityId_.decode(reader)){return false;}
PACKET_DECODE(Int32,skillId_);
PACKET_DECODE(Bool,isFirst_);
PACKET_DECODE(Int32,attackId_);
extra_ = MsgPool::Instance()->DecodeMsg(reader);
extraAttrs_ = MsgPool::Instance()->DecodeMsg(reader);
return true;}
bool SFightInfo::encode(CBufferWriter &writer) const {
if(!fromEntityId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,skillId_);
PACKET_ENCODE(Bool,isFirst_);
PACKET_ENCODE(Int32,attackId_);
if(!MsgPool::Instance()->EncodeMsg(writer, extra_)){return false;}
if(!MsgPool::Instance()->EncodeMsg(writer, extraAttrs_)){return false;}
return true;}
void SFightInfo::clear(){
fromEntityId_.clear();
skillId_ = 0;
isFirst_ = 0;
attackId_ = 0;
extra_ = NULL;
extraAttrs_ = NULL;
}
bool SDoFight::decode(CBufferReader &reader) {
PACKET_DECODE(Int16,attackId_);
PACKET_DECODE(Int32,skillId_);
if(!fromEntity_.decode(reader)){return false;}
if(!entity_.decode(reader)){return false;}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SFightUpdate item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}propertyUpdates_.push_back(item);}}
return true;}
bool SDoFight::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int16,attackId_);
PACKET_ENCODE(Int32,skillId_);
if(!fromEntity_.encode(writer)){return false;}
if(!entity_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,propertyUpdates_.size());
for(vector<SFightUpdate>::const_iterator vit=propertyUpdates_.begin();vit!=propertyUpdates_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SDoFight::clear(){
attackId_ = 0;
skillId_ = 0;
fromEntity_.clear();
entity_.clear();
propertyUpdates_.clear();
}
bool SDoFights::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SDoFight item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}doFights_.push_back(item);}}
return true;}
bool SDoFights::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,doFights_.size());
for(vector<SDoFight>::const_iterator vit=doFights_.begin();vit!=doFights_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SDoFights::clear(){
doFights_.clear();
}
bool SPlayerBuffInfo::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);msgs::SBuffInfo item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}buffs_.push_back(item);}}
return true;}
bool SPlayerBuffInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,buffs_.size());
for(vector<msgs::SBuffInfo>::const_iterator vit=buffs_.begin();vit!=buffs_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerBuffInfo::clear(){
buffs_.clear();
}
bool SUpdateBuff::decode(CBufferReader &reader) {
PACKET_DECODE(Byte,op_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);msgs::SBuffInfo item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}buffs_.push_back(item);}}
return true;}
bool SUpdateBuff::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Byte,op_);
PACKET_ENCODE(UVar32,buffs_.size());
for(vector<msgs::SBuffInfo>::const_iterator vit=buffs_.begin();vit!=buffs_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SUpdateBuff::clear(){
op_ = 0;
buffs_.clear();
}
bool SBroadBuffInfo::decode(CBufferReader &reader) {
if(!buffs_.decode(reader)){return false;}
if(!toEntityId_.decode(reader)){return false;}
if(!fromEntityId_.decode(reader)){return false;}
return true;}
bool SBroadBuffInfo::encode(CBufferWriter &writer) const {
if(!buffs_.encode(writer)){return false;}
if(!toEntityId_.encode(writer)){return false;}
if(!fromEntityId_.encode(writer)){return false;}
return true;}
void SBroadBuffInfo::clear(){
buffs_.clear();
toEntityId_.clear();
fromEntityId_.clear();
}
bool SUpdateSkillCd::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);updateCds_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);updateCdPers_[k] = v;}}
return true;}
bool SUpdateSkillCd::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(UVar32,updateCds_.size());
for(map<int32_t, int32_t>::const_iterator it=updateCds_.begin();it!=updateCds_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,updateCdPers_.size());
for(map<int32_t, int32_t>::const_iterator it=updateCdPers_.begin();it!=updateCdPers_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SUpdateSkillCd::clear(){
roleId_ = 0;
updateCds_.clear();
updateCdPers_.clear();
}
bool SRoleUpdateRune::decode(CBufferReader &reader) {
PACKET_DECODE(Byte,op_);
PACKET_DECODE(Int32,roleId_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);runes_.push_back(item);}}
return true;}
bool SRoleUpdateRune::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Byte,op_);
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(UVar32,runes_.size());
for(vector<int32_t>::const_iterator vit=runes_.begin();vit!=runes_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SRoleUpdateRune::clear(){
op_ = 0;
roleId_ = 0;
runes_.clear();
}
bool SEntityPoint::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
if(!point_.decode(reader)){return false;}
return true;}
bool SEntityPoint::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
if(!point_.encode(writer)){return false;}
return true;}
void SEntityPoint::clear(){
entityId_.clear();
point_.clear();
}
bool SCleanSkill::decode(CBufferReader &reader) {
PACKET_DECODE(Int16,skillUid_);
return true;}
bool SCleanSkill::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int16,skillUid_);
return true;}
void SCleanSkill::clear(){
skillUid_ = 0;
}
bool SPlayerGodMagicSkill::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int32,selectType_);
return true;}
bool SPlayerGodMagicSkill::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int32,selectType_);
return true;}
void SPlayerGodMagicSkill::clear(){
roleId_ = 0;
selectType_ = 0;
}
bool SChildInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);unlockMap_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);childMap_[k] = v;}}
PACKET_DECODE(Int32,curFightChild_);
PACKET_DECODE(Int64,tryEndTime_);
PACKET_DECODE(Int32,tryEnterId_);
return true;}
bool SChildInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,unlockMap_.size());
for(map<int32_t, bool>::const_iterator it=unlockMap_.begin();it!=unlockMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
PACKET_ENCODE(UVar32,childMap_.size());
for(map<int32_t, int32_t>::const_iterator it=childMap_.begin();it!=childMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,curFightChild_);
PACKET_ENCODE(Int64,tryEndTime_);
PACKET_ENCODE(Int32,tryEnterId_);
return true;}
void SChildInfo::clear(){
unlockMap_.clear();
childMap_.clear();
curFightChild_ = 0;
tryEndTime_ = 0;
tryEnterId_ = 0;
}
bool SFeiJianInfo::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);dbs::TPlayerFeiJian item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool SFeiJianInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<dbs::TPlayerFeiJian>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SFeiJianInfo::clear(){
list_.clear();
}
bool STurntableSingle::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);recordMap_[k] = v;}}
PACKET_DECODE(Int32,count_);
PACKET_DECODE(Int32,group_);
PACKET_DECODE(Int32,totalCount_);
return true;}
bool STurntableSingle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,recordMap_.size());
for(map<int32_t, bool>::const_iterator it=recordMap_.begin();it!=recordMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
PACKET_ENCODE(Int32,count_);
PACKET_ENCODE(Int32,group_);
PACKET_ENCODE(Int32,totalCount_);
return true;}
void STurntableSingle::clear(){
recordMap_.clear();
count_ = 0;
group_ = 0;
totalCount_ = 0;
}
bool STurntableInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;STurntableSingle v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}turntableMap_[k] = v;}}
return true;}
bool STurntableInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,turntableMap_.size());
for(map<int32_t, STurntableSingle>::const_iterator it=turntableMap_.begin();it!=turntableMap_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void STurntableInfo::clear(){
turntableMap_.clear();
}
bool STurntableRecordSingle::decode(CBufferReader &reader) {
PACKET_DECODE(String,playerName_);
PACKET_DECODE(Int32,itemId_);
PACKET_DECODE(Int32,itemCount_);
return true;}
bool STurntableRecordSingle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,playerName_);
PACKET_ENCODE(Int32,itemId_);
PACKET_ENCODE(Int32,itemCount_);
return true;}
void STurntableRecordSingle::clear(){
playerName_.clear();
itemId_ = 0;
itemCount_ = 0;
}
bool STurntableRecord::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);STurntableRecordSingle item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}records_.push_back(item);}}
return true;}
bool STurntableRecord::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,records_.size());
for(vector<STurntableRecordSingle>::const_iterator vit=records_.begin();vit!=records_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void STurntableRecord::clear(){
records_.clear();
}
bool STeamMember::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
if(!mirrorId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int16,sex_);
PACKET_DECODE(Int16,career_);
PACKET_DECODE(Int16,careerLevel_);
PACKET_DECODE(Int16,level_);
PACKET_DECODE(Int64,combat_);
PACKET_DECODE(Int32,spaceId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);ornaments_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);entityShows_[k] = v;}}
return true;}
bool STeamMember::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
if(!mirrorId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int16,sex_);
PACKET_ENCODE(Int16,career_);
PACKET_ENCODE(Int16,careerLevel_);
PACKET_ENCODE(Int16,level_);
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(Int32,spaceId_);
PACKET_ENCODE(UVar32,ornaments_.size());
for(map<int16_t, int32_t>::const_iterator it=ornaments_.begin();it!=ornaments_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,entityShows_.size());
for(map<int16_t, int32_t>::const_iterator it=entityShows_.begin();it!=entityShows_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void STeamMember::clear(){
entityId_.clear();
mirrorId_.clear();
name_.clear();
sex_ = 0;
career_ = 0;
careerLevel_ = 0;
level_ = 0;
combat_ = 0;
spaceId_ = 0;
ornaments_.clear();
entityShows_.clear();
}
bool SMiniTeamMember::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int16,sex_);
PACKET_DECODE(Int16,career_);
PACKET_DECODE(Int16,careerLevel_);
PACKET_DECODE(Int16,level_);
PACKET_DECODE(Int64,combat_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);ornaments_[k] = v;}}
return true;}
bool SMiniTeamMember::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int16,sex_);
PACKET_ENCODE(Int16,career_);
PACKET_ENCODE(Int16,careerLevel_);
PACKET_ENCODE(Int16,level_);
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(UVar32,ornaments_.size());
for(map<int16_t, int32_t>::const_iterator it=ornaments_.begin();it!=ornaments_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SMiniTeamMember::clear(){
entityId_.clear();
name_.clear();
sex_ = 0;
career_ = 0;
careerLevel_ = 0;
level_ = 0;
combat_ = 0;
ornaments_.clear();
}
bool STeam::decode(CBufferReader &reader) {
if(!teamId_.decode(reader)){return false;}
PACKET_DECODE(String,teamName_);
if(!leaderId_.decode(reader)){return false;}
PACKET_DECODE(Int32,copyId_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);STeamMember item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}members_.push_back(item);}}
if(!target_.decode(reader)){return false;}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);targetList_.push_back(item);}}
PACKET_DECODE(Int16,needLevel_);
PACKET_DECODE(Bool,autoJoin_);
PACKET_DECODE(Bool,isMatching_);
return true;}
bool STeam::encode(CBufferWriter &writer) const {
if(!teamId_.encode(writer)){return false;}
PACKET_ENCODE(String,teamName_);
if(!leaderId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,copyId_);
PACKET_ENCODE(UVar32,members_.size());
for(vector<STeamMember>::const_iterator vit=members_.begin();vit!=members_.end();++vit){if(!vit->encode(writer)){return false;}}
if(!target_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,targetList_.size());
for(vector<int32_t>::const_iterator vit=targetList_.begin();vit!=targetList_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(Int16,needLevel_);
PACKET_ENCODE(Bool,autoJoin_);
PACKET_ENCODE(Bool,isMatching_);
return true;}
void STeam::clear(){
teamId_.clear();
teamName_.clear();
leaderId_.clear();
copyId_ = 0;
members_.clear();
target_.clear();
targetList_.clear();
needLevel_ = 0;
autoJoin_ = 0;
isMatching_ = 0;
}
bool SMiniTeam::decode(CBufferReader &reader) {
if(!teamId_.decode(reader)){return false;}
PACKET_DECODE(String,teamName_);
if(!leader_.decode(reader)){return false;}
PACKET_DECODE(Int32,memberNum_);
if(!target_.decode(reader)){return false;}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);targetList_.push_back(item);}}
return true;}
bool SMiniTeam::encode(CBufferWriter &writer) const {
if(!teamId_.encode(writer)){return false;}
PACKET_ENCODE(String,teamName_);
if(!leader_.encode(writer)){return false;}
PACKET_ENCODE(Int32,memberNum_);
if(!target_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,targetList_.size());
for(vector<int32_t>::const_iterator vit=targetList_.begin();vit!=targetList_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SMiniTeam::clear(){
teamId_.clear();
teamName_.clear();
leader_.clear();
memberNum_ = 0;
target_.clear();
targetList_.clear();
}
bool STeamMemberUpdateData::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int64_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int64,item);updateData_.push_back(item);}}
PACKET_DECODE(String,updateStr_);
return true;}
bool STeamMemberUpdateData::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,updateData_.size());
for(vector<int64_t>::const_iterator vit=updateData_.begin();vit!=updateData_.end();++vit){PACKET_ENCODE(Int64,*vit);}
PACKET_ENCODE(String,updateStr_);
return true;}
void STeamMemberUpdateData::clear(){
entityId_.clear();
updateData_.clear();
updateStr_.clear();
}
bool STeamUpdateLeader::decode(CBufferReader &reader) {
if(!leaderId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
return true;}
bool STeamUpdateLeader::encode(CBufferWriter &writer) const {
if(!leaderId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
return true;}
void STeamUpdateLeader::clear(){
leaderId_.clear();
name_.clear();
}
bool STeamUpdateSetting::decode(CBufferReader &reader) {
PACKET_DECODE(Int16,needLevel_);
PACKET_DECODE(Bool,autoJoin_);
if(!target_.decode(reader)){return false;}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);targetList_.push_back(item);}}
return true;}
bool STeamUpdateSetting::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int16,needLevel_);
PACKET_ENCODE(Bool,autoJoin_);
if(!target_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,targetList_.size());
for(vector<int32_t>::const_iterator vit=targetList_.begin();vit!=targetList_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void STeamUpdateSetting::clear(){
needLevel_ = 0;
autoJoin_ = 0;
target_.clear();
targetList_.clear();
}
bool STeamUpdateTarget::decode(CBufferReader &reader) {
if(!target_.decode(reader)){return false;}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);targetList_.push_back(item);}}
return true;}
bool STeamUpdateTarget::encode(CBufferWriter &writer) const {
if(!target_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,targetList_.size());
for(vector<int32_t>::const_iterator vit=targetList_.begin();vit!=targetList_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void STeamUpdateTarget::clear(){
target_.clear();
targetList_.clear();
}
bool STeamJoinData::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int16,sex_);
PACKET_DECODE(Int16,career_);
PACKET_DECODE(Int16,careerLevel_);
PACKET_DECODE(Int16,level_);
PACKET_DECODE(Int64,combat_);
PACKET_DECODE(Int64,operDt_);
return true;}
bool STeamJoinData::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int16,sex_);
PACKET_ENCODE(Int16,career_);
PACKET_ENCODE(Int16,careerLevel_);
PACKET_ENCODE(Int16,level_);
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(Int64,operDt_);
return true;}
void STeamJoinData::clear(){
entityId_.clear();
name_.clear();
sex_ = 0;
career_ = 0;
careerLevel_ = 0;
level_ = 0;
combat_ = 0;
operDt_ = 0;
}
bool STeamJoinList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);STeamJoinData item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool STeamJoinList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<STeamJoinData>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void STeamJoinList::clear(){
list_.clear();
}
bool STeamVoteStart::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(Int32,touxianId_);
PACKET_DECODE(Int32,titleId_);
return true;}
bool STeamVoteStart::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,touxianId_);
PACKET_ENCODE(Int32,titleId_);
return true;}
void STeamVoteStart::clear(){
copyCode_ = 0;
entityId_.clear();
touxianId_ = 0;
titleId_ = 0;
}
bool STeamVoteAnswer::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
PACKET_DECODE(Bool,agree_);
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(Int32,touxianId_);
PACKET_DECODE(Int32,titleId_);
return true;}
bool STeamVoteAnswer::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(Bool,agree_);
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,touxianId_);
PACKET_ENCODE(Int32,titleId_);
return true;}
void STeamVoteAnswer::clear(){
copyCode_ = 0;
agree_ = 0;
entityId_.clear();
touxianId_ = 0;
titleId_ = 0;
}
bool STeamInviteBroadcast::decode(CBufferReader &reader) {
if(!teamId_.decode(reader)){return false;}
PACKET_DECODE(Int32,copyCode_);
PACKET_DECODE(Int32,needLevel_);
return true;}
bool STeamInviteBroadcast::encode(CBufferWriter &writer) const {
if(!teamId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(Int32,needLevel_);
return true;}
void STeamInviteBroadcast::clear(){
teamId_.clear();
copyCode_ = 0;
needLevel_ = 0;
}
bool STeamMemberCopyCheck::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,errorCode_);
PACKET_DECODE(String,errorWhat_);
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(Int32,spaceId_);
PACKET_DECODE(Int32,enterRemainNum_);
PACKET_DECODE(Int32,assistRemainNum_);
PACKET_DECODE(Int32,career_);
return true;}
bool STeamMemberCopyCheck::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,errorCode_);
PACKET_ENCODE(String,errorWhat_);
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,spaceId_);
PACKET_ENCODE(Int32,enterRemainNum_);
PACKET_ENCODE(Int32,assistRemainNum_);
PACKET_ENCODE(Int32,career_);
return true;}
void STeamMemberCopyCheck::clear(){
errorCode_ = 0;
errorWhat_.clear();
entityId_.clear();
spaceId_ = 0;
enterRemainNum_ = 0;
assistRemainNum_ = 0;
career_ = 0;
}
bool SYunGou::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,index_);
PACKET_DECODE(Int32,hadBuyCount_);
PACKET_DECODE(Int32,myBuyCount_);
return true;}
bool SYunGou::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,index_);
PACKET_ENCODE(Int32,hadBuyCount_);
PACKET_ENCODE(Int32,myBuyCount_);
return true;}
void SYunGou::clear(){
index_ = 0;
hadBuyCount_ = 0;
myBuyCount_ = 0;
}
bool SYunGouInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,status_);
PACKET_DECODE(Int64,openDt_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SYunGou item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}items_.push_back(item);}}
return true;}
bool SYunGouInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,status_);
PACKET_ENCODE(Int64,openDt_);
PACKET_ENCODE(UVar32,items_.size());
for(vector<SYunGou>::const_iterator vit=items_.begin();vit!=items_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SYunGouInfo::clear(){
status_ = 0;
openDt_ = 0;
items_.clear();
}
bool SYunGouWin::decode(CBufferReader &reader) {
PACKET_DECODE(String,winName_);
PACKET_DECODE(Int32,winCount_);
PACKET_DECODE(Int32,buyCount_);
return true;}
bool SYunGouWin::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,winName_);
PACKET_ENCODE(Int32,winCount_);
PACKET_ENCODE(Int32,buyCount_);
return true;}
void SYunGouWin::clear(){
winName_.clear();
winCount_ = 0;
buyCount_ = 0;
}
bool SYunGouRecord::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,itemId_);
PACKET_DECODE(Int32,itemNum_);
PACKET_DECODE(Int32,winNum_);
return true;}
bool SYunGouRecord::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,itemId_);
PACKET_ENCODE(Int32,itemNum_);
PACKET_ENCODE(Int32,winNum_);
return true;}
void SYunGouRecord::clear(){
entityId_.clear();
name_.clear();
itemId_ = 0;
itemNum_ = 0;
winNum_ = 0;
}
bool SYunGouRecords::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,openTime_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SYunGouRecord item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}records_.push_back(item);}}
return true;}
bool SYunGouRecords::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,openTime_);
PACKET_ENCODE(UVar32,records_.size());
for(vector<SYunGouRecord>::const_iterator vit=records_.begin();vit!=records_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SYunGouRecords::clear(){
openTime_ = 0;
records_.clear();
}
bool SGhostMazeInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
PACKET_DECODE(Int32,freeCount_);
PACKET_DECODE(Int32,resetCount_);
PACKET_DECODE(Int32,curPos_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);msgs::SIntIntPair item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}rewards_.push_back(item);}}
return true;}
bool SGhostMazeInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(Int32,freeCount_);
PACKET_ENCODE(Int32,resetCount_);
PACKET_ENCODE(Int32,curPos_);
PACKET_ENCODE(UVar32,rewards_.size());
for(vector<msgs::SIntIntPair>::const_iterator vit=rewards_.begin();vit!=rewards_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SGhostMazeInfo::clear(){
activeId_ = 0;
freeCount_ = 0;
resetCount_ = 0;
curPos_ = 0;
rewards_.clear();
}
bool SGhostMazeRecord::decode(CBufferReader &reader) {
PACKET_DECODE(String,playerName_);
PACKET_DECODE(Int32,itemId_);
PACKET_DECODE(Int32,itemNum_);
return true;}
bool SGhostMazeRecord::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,playerName_);
PACKET_ENCODE(Int32,itemId_);
PACKET_ENCODE(Int32,itemNum_);
return true;}
void SGhostMazeRecord::clear(){
playerName_.clear();
itemId_ = 0;
itemNum_ = 0;
}
bool SGhostMazeRecords::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SGhostMazeRecord item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}records_.push_back(item);}}
return true;}
bool SGhostMazeRecords::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,records_.size());
for(vector<SGhostMazeRecord>::const_iterator vit=records_.begin();vit!=records_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SGhostMazeRecords::clear(){
records_.clear();
}
bool SMineTreasureInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
PACKET_DECODE(Int32,freeTimes_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);msgs::SIntIntPair item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}recordMap_.push_back(item);}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewardlist_[k] = v;}}
return true;}
bool SMineTreasureInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(Int32,freeTimes_);
PACKET_ENCODE(UVar32,recordMap_.size());
for(vector<msgs::SIntIntPair>::const_iterator vit=recordMap_.begin();vit!=recordMap_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(UVar32,rewardlist_.size());
for(map<int32_t, int32_t>::const_iterator it=rewardlist_.begin();it!=rewardlist_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SMineTreasureInfo::clear(){
activeId_ = 0;
freeTimes_ = 0;
recordMap_.clear();
rewardlist_.clear();
}
bool SFlyingUpInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,round_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);commitMap_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);flyingUpMap_[k] = v;}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);curFightVec_.push_back(item);}}
PACKET_DECODE(Int64,startTime_);
PACKET_DECODE(Int64,countDownTime_);
PACKET_DECODE(Int32,buyTime_);
PACKET_DECODE(Bool,isCountDown_);
PACKET_DECODE(Int32,buyEnterNum_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);bool item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Bool,item);lockVec_.push_back(item);}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);flyingUpGodGrid_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);talent_[k] = v;}}
PACKET_DECODE(Int64,tryEndTime_);
return true;}
bool SFlyingUpInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,round_);
PACKET_ENCODE(UVar32,commitMap_.size());
for(map<int32_t, bool>::const_iterator it=commitMap_.begin();it!=commitMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
PACKET_ENCODE(UVar32,flyingUpMap_.size());
for(map<int32_t, int32_t>::const_iterator it=flyingUpMap_.begin();it!=flyingUpMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,curFightVec_.size());
for(vector<int32_t>::const_iterator vit=curFightVec_.begin();vit!=curFightVec_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(Int64,startTime_);
PACKET_ENCODE(Int64,countDownTime_);
PACKET_ENCODE(Int32,buyTime_);
PACKET_ENCODE(Bool,isCountDown_);
PACKET_ENCODE(Int32,buyEnterNum_);
PACKET_ENCODE(UVar32,lockVec_.size());
for(vector<bool>::const_iterator vit=lockVec_.begin();vit!=lockVec_.end();++vit){PACKET_ENCODE(Bool,*vit);}
PACKET_ENCODE(UVar32,flyingUpGodGrid_.size());
for(map<int32_t, int32_t>::const_iterator it=flyingUpGodGrid_.begin();it!=flyingUpGodGrid_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,talent_.size());
for(map<int32_t, int32_t>::const_iterator it=talent_.begin();it!=talent_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int64,tryEndTime_);
return true;}
void SFlyingUpInfo::clear(){
round_ = 0;
commitMap_.clear();
flyingUpMap_.clear();
curFightVec_.clear();
startTime_ = 0;
countDownTime_ = 0;
buyTime_ = 0;
isCountDown_ = 0;
buyEnterNum_ = 0;
lockVec_.clear();
flyingUpGodGrid_.clear();
talent_.clear();
tryEndTime_ = 0;
}
bool SFightFlyingUp::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,commonCD_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int64_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int64,v);flyingUpCD_[k] = v;}}
PACKET_DECODE(Int64,stCommonCD_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int64_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int64,v);stFlyingUpCD_[k] = v;}}
return true;}
bool SFightFlyingUp::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,commonCD_);
PACKET_ENCODE(UVar32,flyingUpCD_.size());
for(map<int32_t, int64_t>::const_iterator it=flyingUpCD_.begin();it!=flyingUpCD_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int64,it->second);}
PACKET_ENCODE(Int64,stCommonCD_);
PACKET_ENCODE(UVar32,stFlyingUpCD_.size());
for(map<int32_t, int64_t>::const_iterator it=stFlyingUpCD_.begin();it!=stFlyingUpCD_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int64,it->second);}
return true;}
void SFightFlyingUp::clear(){
commonCD_ = 0;
flyingUpCD_.clear();
stCommonCD_ = 0;
stFlyingUpCD_.clear();
}
bool SCosmosInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);cosmosMap_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);commitMissions_[k] = v;}}
PACKET_DECODE(Int32,curRole_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);guangWuMap_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);guangWuBless_[k] = v;}}
return true;}
bool SCosmosInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,cosmosMap_.size());
for(map<int32_t, int32_t>::const_iterator it=cosmosMap_.begin();it!=cosmosMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,commitMissions_.size());
for(map<int32_t, bool>::const_iterator it=commitMissions_.begin();it!=commitMissions_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
PACKET_ENCODE(Int32,curRole_);
PACKET_ENCODE(UVar32,guangWuMap_.size());
for(map<int32_t, int32_t>::const_iterator it=guangWuMap_.begin();it!=guangWuMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,guangWuBless_.size());
for(map<int32_t, int32_t>::const_iterator it=guangWuBless_.begin();it!=guangWuBless_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCosmosInfo::clear(){
cosmosMap_.clear();
commitMissions_.clear();
curRole_ = 0;
guangWuMap_.clear();
guangWuBless_.clear();
}
bool SPlayerCopyDataList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);dbs::TPlayerCopyData item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}copyDatas_.push_back(item);}}
return true;}
bool SPlayerCopyDataList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,copyDatas_.size());
for(vector<dbs::TPlayerCopyData>::const_iterator vit=copyDatas_.begin();vit!=copyDatas_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerCopyDataList::clear(){
copyDatas_.clear();
}
bool SPlayerCopyDataUpdateNum::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyGroup_);
PACKET_DECODE(Int32,enterNum_);
PACKET_DECODE(Int32,assistNum_);
PACKET_DECODE(Int32,getBackNum_);
PACKET_DECODE(Int32,totalEnterNum_);
PACKET_DECODE(Int32,completeNum_);
PACKET_DECODE(Int32,totalCompleteNum_);
return true;}
bool SPlayerCopyDataUpdateNum::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyGroup_);
PACKET_ENCODE(Int32,enterNum_);
PACKET_ENCODE(Int32,assistNum_);
PACKET_ENCODE(Int32,getBackNum_);
PACKET_ENCODE(Int32,totalEnterNum_);
PACKET_ENCODE(Int32,completeNum_);
PACKET_ENCODE(Int32,totalCompleteNum_);
return true;}
void SPlayerCopyDataUpdateNum::clear(){
copyGroup_ = 0;
enterNum_ = 0;
assistNum_ = 0;
getBackNum_ = 0;
totalEnterNum_ = 0;
completeNum_ = 0;
totalCompleteNum_ = 0;
}
bool SCopyTimeInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
PACKET_DECODE(Int64,startDt_);
PACKET_DECODE(Int64,endDt_);
return true;}
bool SCopyTimeInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(Int64,startDt_);
PACKET_ENCODE(Int64,endDt_);
return true;}
void SCopyTimeInfo::clear(){
copyCode_ = 0;
startDt_ = 0;
endDt_ = 0;
}
bool SEnterCopy::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
return true;}
bool SEnterCopy::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
return true;}
void SEnterCopy::clear(){
copyCode_ = 0;
}
bool SCompleteCopy::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
PACKET_DECODE(Int32,costCount_);
PACKET_DECODE(Bool,failed_);
return true;}
bool SCompleteCopy::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(Int32,costCount_);
PACKET_ENCODE(Bool,failed_);
return true;}
void SCompleteCopy::clear(){
copyCode_ = 0;
costCount_ = 0;
failed_ = 0;
}
bool SNotifyEnterCopy::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
return true;}
bool SNotifyEnterCopy::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
return true;}
void SNotifyEnterCopy::clear(){
copyCode_ = 0;
}
bool SCompleteExpCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int64,lastTotalExp_);
PACKET_DECODE(Int64,singleTotalExp_);
PACKET_DECODE(Int32,monsterKilledNum_);
PACKET_DECODE(Int32,extraAddon_);
return true;}
bool SCompleteExpCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int64,lastTotalExp_);
PACKET_ENCODE(Int64,singleTotalExp_);
PACKET_ENCODE(Int32,monsterKilledNum_);
PACKET_ENCODE(Int32,extraAddon_);
return true;}
void SCompleteExpCopy::clear(){
lastTotalExp_ = 0;
singleTotalExp_ = 0;
monsterKilledNum_ = 0;
extraAddon_ = 0;
}
bool SExpCopyInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
PACKET_DECODE(Int32,count_);
PACKET_DECODE(Int64,totalExp_);
PACKET_DECODE(Int16,coinNum_);
PACKET_DECODE(Int16,goldNum_);
return true;}
bool SExpCopyInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(Int32,count_);
PACKET_ENCODE(Int64,totalExp_);
PACKET_ENCODE(Int16,coinNum_);
PACKET_ENCODE(Int16,goldNum_);
return true;}
void SExpCopyInfo::clear(){
copyCode_ = 0;
count_ = 0;
totalExp_ = 0;
coinNum_ = 0;
goldNum_ = 0;
}
bool STrialBossResult::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,evaluation_);
PACKET_DECODE(Bool,isPromot_);
PACKET_DECODE(Int32,bestEvaluation_);
PACKET_DECODE(Bool,isAssist_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool STrialBossResult::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,evaluation_);
PACKET_ENCODE(Bool,isPromot_);
PACKET_ENCODE(Int32,bestEvaluation_);
PACKET_ENCODE(Bool,isAssist_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void STrialBossResult::clear(){
evaluation_ = 0;
isPromot_ = 0;
bestEvaluation_ = 0;
isAssist_ = 0;
rewards_.clear();
}
bool SCompleteEquipCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,evaluation_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool SCompleteEquipCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,evaluation_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompleteEquipCopy::clear(){
evaluation_ = 0;
rewards_.clear();
}
bool STrialBossLeftInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,bossCode_);
PACKET_DECODE(Int32,num_);
PACKET_DECODE(Int32,round_);
PACKET_DECODE(Int64,roundEndTime_);
PACKET_DECODE(Int32,evaluation_);
return true;}
bool STrialBossLeftInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,bossCode_);
PACKET_ENCODE(Int32,num_);
PACKET_ENCODE(Int32,round_);
PACKET_ENCODE(Int64,roundEndTime_);
PACKET_ENCODE(Int32,evaluation_);
return true;}
void STrialBossLeftInfo::clear(){
bossCode_ = 0;
num_ = 0;
round_ = 0;
roundEndTime_ = 0;
evaluation_ = 0;
}
bool SRefineTargetReward::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool SRefineTargetReward::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SRefineTargetReward::clear(){
copyCode_ = 0;
rewards_.clear();
}
bool SRefineCopyInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
PACKET_DECODE(Int32,score_);
PACKET_DECODE(Int32,layer_);
return true;}
bool SRefineCopyInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(Int32,score_);
PACKET_ENCODE(Int32,layer_);
return true;}
void SRefineCopyInfo::clear(){
copyCode_ = 0;
score_ = 0;
layer_ = 0;
}
bool SCompleteRefineCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,score_);
PACKET_DECODE(Int32,completeTime_);
PACKET_DECODE(Int32,layer_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
PACKET_DECODE(Bool,isNewRecord_);
return true;}
bool SCompleteRefineCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,score_);
PACKET_ENCODE(Int32,completeTime_);
PACKET_ENCODE(Int32,layer_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Bool,isNewRecord_);
return true;}
void SCompleteRefineCopy::clear(){
score_ = 0;
completeTime_ = 0;
layer_ = 0;
rewards_.clear();
isNewRecord_ = 0;
}
bool SCompleteBeingGodCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,masterFloor_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool SCompleteBeingGodCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,masterFloor_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompleteBeingGodCopy::clear(){
masterFloor_ = 0;
rewards_.clear();
}
bool SBeingGodCopyInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
PACKET_DECODE(Int32,floor_);
PACKET_DECODE(Int32,score_);
PACKET_DECODE(Int32,gotScore_);
PACKET_DECODE(Int32,num_);
return true;}
bool SBeingGodCopyInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(Int32,floor_);
PACKET_ENCODE(Int32,score_);
PACKET_ENCODE(Int32,gotScore_);
PACKET_ENCODE(Int32,num_);
return true;}
void SBeingGodCopyInfo::clear(){
copyCode_ = 0;
floor_ = 0;
score_ = 0;
gotScore_ = 0;
num_ = 0;
}
bool SBeingGodUpdateData::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,score_);
PACKET_DECODE(Int32,num_);
PACKET_DECODE(String,byName_);
return true;}
bool SBeingGodUpdateData::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,score_);
PACKET_ENCODE(Int32,num_);
PACKET_ENCODE(String,byName_);
return true;}
void SBeingGodUpdateData::clear(){
score_ = 0;
num_ = 0;
byName_.clear();
}
bool SBeingGodRankItem::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,num_);
PACKET_DECODE(Int32,maxKillNum_);
return true;}
bool SBeingGodRankItem::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,num_);
PACKET_ENCODE(Int32,maxKillNum_);
return true;}
void SBeingGodRankItem::clear(){
entityId_.clear();
name_.clear();
num_ = 0;
maxKillNum_ = 0;
}
bool SBeingGodRankList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SBeingGodRankItem item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool SBeingGodRankList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<SBeingGodRankItem>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SBeingGodRankList::clear(){
list_.clear();
}
bool SBeingGodContinuousKill::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int16,career_);
PACKET_DECODE(Int16,killNum_);
return true;}
bool SBeingGodContinuousKill::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int16,career_);
PACKET_ENCODE(Int16,killNum_);
return true;}
void SBeingGodContinuousKill::clear(){
entityId_.clear();
name_.clear();
career_ = 0;
killNum_ = 0;
}
bool SCompleteExpeditionCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,id_);
PACKET_DECODE(Int32,idx_);
PACKET_DECODE(Int32,completeTime_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool SCompleteExpeditionCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,id_);
PACKET_ENCODE(Int32,idx_);
PACKET_ENCODE(Int32,completeTime_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompleteExpeditionCopy::clear(){
id_ = 0;
idx_ = 0;
completeTime_ = 0;
rewards_.clear();
}
bool SExpeditionCopyInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);killedBoss_[k] = v;}}
return true;}
bool SExpeditionCopyInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(UVar32,killedBoss_.size());
for(map<int32_t, int32_t>::const_iterator it=killedBoss_.begin();it!=killedBoss_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SExpeditionCopyInfo::clear(){
copyCode_ = 0;
killedBoss_.clear();
}
bool SEliteBossLeftInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,bossCode_);
PACKET_DECODE(Int64,roundEndTime_);
PACKET_DECODE(Int32,evaluation_);
PACKET_DECODE(Int32,layer_);
return true;}
bool SEliteBossLeftInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,bossCode_);
PACKET_ENCODE(Int64,roundEndTime_);
PACKET_ENCODE(Int32,evaluation_);
PACKET_ENCODE(Int32,layer_);
return true;}
void SEliteBossLeftInfo::clear(){
bossCode_ = 0;
roundEndTime_ = 0;
evaluation_ = 0;
layer_ = 0;
}
bool SEliteBossResult::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,evaluation_);
PACKET_DECODE(Int32,layer_);
PACKET_DECODE(Bool,isPromot_);
PACKET_DECODE(Int32,bestEvaluation_);
PACKET_DECODE(Int32,bestLayer_);
PACKET_DECODE(Bool,isAssist_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool SEliteBossResult::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,evaluation_);
PACKET_ENCODE(Int32,layer_);
PACKET_ENCODE(Bool,isPromot_);
PACKET_ENCODE(Int32,bestEvaluation_);
PACKET_ENCODE(Int32,bestLayer_);
PACKET_ENCODE(Bool,isAssist_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SEliteBossResult::clear(){
evaluation_ = 0;
layer_ = 0;
isPromot_ = 0;
bestEvaluation_ = 0;
bestLayer_ = 0;
isAssist_ = 0;
rewards_.clear();
}
bool SMagicRingsCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
PACKET_DECODE(Int32,completeTime_);
return true;}
bool SMagicRingsCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,completeTime_);
return true;}
void SMagicRingsCopy::clear(){
rewards_.clear();
completeTime_ = 0;
}
bool SCompleteMagicTowerCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,completeTime_);
PACKET_DECODE(Int32,layer_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
PACKET_DECODE(Bool,isQuick_);
PACKET_DECODE(Bool,isDoubleExp_);
return true;}
bool SCompleteMagicTowerCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,completeTime_);
PACKET_ENCODE(Int32,layer_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Bool,isQuick_);
PACKET_ENCODE(Bool,isDoubleExp_);
return true;}
void SCompleteMagicTowerCopy::clear(){
completeTime_ = 0;
layer_ = 0;
rewards_.clear();
isQuick_ = 0;
isDoubleExp_ = 0;
}
bool SMagicTowerCopyInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,layer_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);remainBoss_[k] = v;}}
return true;}
bool SMagicTowerCopyInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,layer_);
PACKET_ENCODE(UVar32,remainBoss_.size());
for(map<int32_t, int32_t>::const_iterator it=remainBoss_.begin();it!=remainBoss_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SMagicTowerCopyInfo::clear(){
layer_ = 0;
remainBoss_.clear();
}
bool SLotteryMagicTower::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,round_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);rewardMap_[k] = v;}}
PACKET_DECODE(Int32,remainCount_);
return true;}
bool SLotteryMagicTower::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,round_);
PACKET_ENCODE(UVar32,rewardMap_.size());
for(map<int32_t, bool>::const_iterator it=rewardMap_.begin();it!=rewardMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
PACKET_ENCODE(Int32,remainCount_);
return true;}
void SLotteryMagicTower::clear(){
round_ = 0;
rewardMap_.clear();
remainCount_ = 0;
}
bool SCompleteMaterialCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool SCompleteMaterialCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompleteMaterialCopy::clear(){
rewards_.clear();
}
bool SMaterialCopyInfo::decode(CBufferReader &reader) {
return true;}
bool SMaterialCopyInfo::encode(CBufferWriter &writer) const {
return true;}
void SMaterialCopyInfo::clear(){
}
bool SEnterReincarnCopy::decode(CBufferReader &reader) {
if(!SEnterCopy::decode(reader)){return false;}
return true;}
bool SEnterReincarnCopy::encode(CBufferWriter &writer) const {
if(!SEnterCopy::encode(writer)){return false;}
return true;}
void SEnterReincarnCopy::clear(){
}
bool SCompleteReincarnCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool SCompleteReincarnCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompleteReincarnCopy::clear(){
rewards_.clear();
}
bool SReincarnCopyBossKill::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);bossKill_[k] = v;}}
return true;}
bool SReincarnCopyBossKill::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,bossKill_.size());
for(map<int32_t, int32_t>::const_iterator it=bossKill_.begin();it!=bossKill_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SReincarnCopyBossKill::clear(){
bossKill_.clear();
}
bool SEnterSpecialRingCopy::decode(CBufferReader &reader) {
if(!SEnterCopy::decode(reader)){return false;}
return true;}
bool SEnterSpecialRingCopy::encode(CBufferWriter &writer) const {
if(!SEnterCopy::encode(writer)){return false;}
return true;}
void SEnterSpecialRingCopy::clear(){
}
bool SCompleteSpecialRingCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
return true;}
bool SCompleteSpecialRingCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
return true;}
void SCompleteSpecialRingCopy::clear(){
}
bool SCompleteBonfireCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
return true;}
bool SCompleteBonfireCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
return true;}
void SCompleteBonfireCopy::clear(){
}
bool SBonfireCopyInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,gatherCount_);
PACKET_DECODE(Int32,woodNum_);
PACKET_DECODE(Int32,answerCount_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);totalRewards_[k] = v;}}
return true;}
bool SBonfireCopyInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,gatherCount_);
PACKET_ENCODE(Int32,woodNum_);
PACKET_ENCODE(Int32,answerCount_);
PACKET_ENCODE(UVar32,totalRewards_.size());
for(map<int32_t, int32_t>::const_iterator it=totalRewards_.begin();it!=totalRewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SBonfireCopyInfo::clear(){
gatherCount_ = 0;
woodNum_ = 0;
answerCount_ = 0;
totalRewards_.clear();
}
bool SBonfireCopyQuestion::decode(CBufferReader &reader) {
PACKET_DECODE(Int16,stage_);
PACKET_DECODE(Int64,nextStateTime_);
PACKET_DECODE(Int32,questionId_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int16_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int16,item);rates_.push_back(item);}}
PACKET_DECODE(Int16,myAnswer_);
PACKET_DECODE(Int16,minAnswer_);
PACKET_DECODE(Int16,minAnswerNum_);
return true;}
bool SBonfireCopyQuestion::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int16,stage_);
PACKET_ENCODE(Int64,nextStateTime_);
PACKET_ENCODE(Int32,questionId_);
PACKET_ENCODE(UVar32,rates_.size());
for(vector<int16_t>::const_iterator vit=rates_.begin();vit!=rates_.end();++vit){PACKET_ENCODE(Int16,*vit);}
PACKET_ENCODE(Int16,myAnswer_);
PACKET_ENCODE(Int16,minAnswer_);
PACKET_ENCODE(Int16,minAnswerNum_);
return true;}
void SBonfireCopyQuestion::clear(){
stage_ = 0;
nextStateTime_ = 0;
questionId_ = 0;
rates_.clear();
myAnswer_ = 0;
minAnswer_ = 0;
minAnswerNum_ = 0;
}
bool SEnterTaskCopy::decode(CBufferReader &reader) {
if(!SEnterCopy::decode(reader)){return false;}
return true;}
bool SEnterTaskCopy::encode(CBufferWriter &writer) const {
if(!SEnterCopy::encode(writer)){return false;}
return true;}
void SEnterTaskCopy::clear(){
}
bool SCompleteTaskCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);msgs::SItemAmount item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}rewards_.push_back(item);}}
PACKET_DECODE(Int32,ownerMonsterId_);
return true;}
bool SCompleteTaskCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(UVar32,rewards_.size());
for(vector<msgs::SItemAmount>::const_iterator vit=rewards_.begin();vit!=rewards_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(Int32,ownerMonsterId_);
return true;}
void SCompleteTaskCopy::clear(){
rewards_.clear();
ownerMonsterId_ = 0;
}
bool STaskCopyInfo::decode(CBufferReader &reader) {
if(!belongId_.decode(reader)){return false;}
return true;}
bool STaskCopyInfo::encode(CBufferWriter &writer) const {
if(!belongId_.encode(writer)){return false;}
return true;}
void STaskCopyInfo::clear(){
belongId_.clear();
}
bool SEnterArenaWzCopy::decode(CBufferReader &reader) {
if(!SEnterCopy::decode(reader)){return false;}
return true;}
bool SEnterArenaWzCopy::encode(CBufferWriter &writer) const {
if(!SEnterCopy::encode(writer)){return false;}
return true;}
void SEnterArenaWzCopy::clear(){
}
bool SCompleteArenaWzCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,addStar_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);reward_[k] = v;}}
return true;}
bool SCompleteArenaWzCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,addStar_);
PACKET_ENCODE(UVar32,reward_.size());
for(map<int32_t, int32_t>::const_iterator it=reward_.begin();it!=reward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompleteArenaWzCopy::clear(){
level_ = 0;
addStar_ = 0;
reward_.clear();
}
bool SGuildBossData::decode(CBufferReader &reader) {
if(!guildId_.decode(reader)){return false;}
PACKET_DECODE(String,guildName_);
PACKET_DECODE(Int32,curId_);
PACKET_DECODE(Int64,curLife_);
return true;}
bool SGuildBossData::encode(CBufferWriter &writer) const {
if(!guildId_.encode(writer)){return false;}
PACKET_ENCODE(String,guildName_);
PACKET_ENCODE(Int32,curId_);
PACKET_ENCODE(Int64,curLife_);
return true;}
void SGuildBossData::clear(){
guildId_.clear();
guildName_.clear();
curId_ = 0;
curLife_ = 0;
}
bool SCompleteGuildBossCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,initId_);
PACKET_DECODE(Int32,curId_);
PACKET_DECODE(Int64,totalHurt_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool SCompleteGuildBossCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,initId_);
PACKET_ENCODE(Int32,curId_);
PACKET_ENCODE(Int64,totalHurt_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompleteGuildBossCopy::clear(){
initId_ = 0;
curId_ = 0;
totalHurt_ = 0;
rewards_.clear();
}
bool SGuildBossCopyInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,initId_);
PACKET_DECODE(Int32,killedId_);
PACKET_DECODE(Int32,addHurtPer_);
PACKET_DECODE(Int64,totalHurt_);
PACKET_DECODE(Int32,spaceMaxRound_);
return true;}
bool SGuildBossCopyInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,initId_);
PACKET_ENCODE(Int32,killedId_);
PACKET_ENCODE(Int32,addHurtPer_);
PACKET_ENCODE(Int64,totalHurt_);
PACKET_ENCODE(Int32,spaceMaxRound_);
return true;}
void SGuildBossCopyInfo::clear(){
initId_ = 0;
killedId_ = 0;
addHurtPer_ = 0;
totalHurt_ = 0;
spaceMaxRound_ = 0;
}
bool SGuildBossCopyRank::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int64,hurt_);
return true;}
bool SGuildBossCopyRank::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int64,hurt_);
return true;}
void SGuildBossCopyRank::clear(){
entityId_.clear();
name_.clear();
hurt_ = 0;
}
bool SGuildBossCopyRankList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SGuildBossCopyRank item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}rankList_.push_back(item);}}
return true;}
bool SGuildBossCopyRankList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,rankList_.size());
for(vector<SGuildBossCopyRank>::const_iterator vit=rankList_.begin();vit!=rankList_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SGuildBossCopyRankList::clear(){
rankList_.clear();
}
bool SEnterDefenseCopy::decode(CBufferReader &reader) {
if(!SEnterCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,isGuide_);
return true;}
bool SEnterDefenseCopy::encode(CBufferWriter &writer) const {
if(!SEnterCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,isGuide_);
return true;}
void SEnterDefenseCopy::clear(){
isGuide_ = 0;
}
bool SCompleteDefenseCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool SCompleteDefenseCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompleteDefenseCopy::clear(){
rewards_.clear();
}
bool SDefenseCopyInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,towerId_);
PACKET_DECODE(Int32,monsterNum_);
PACKET_DECODE(Int32,score_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool SDefenseCopyInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,towerId_);
PACKET_ENCODE(Int32,monsterNum_);
PACKET_ENCODE(Int32,score_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SDefenseCopyInfo::clear(){
towerId_ = 0;
monsterNum_ = 0;
score_ = 0;
rewards_.clear();
}
bool SDefenseCopyRefreshInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,buyBoss_);
PACKET_DECODE(Int32,round_);
PACKET_DECODE(Int64,nextRefreshDt_);
return true;}
bool SDefenseCopyRefreshInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,buyBoss_);
PACKET_ENCODE(Int32,round_);
PACKET_ENCODE(Int64,nextRefreshDt_);
return true;}
void SDefenseCopyRefreshInfo::clear(){
buyBoss_ = 0;
round_ = 0;
nextRefreshDt_ = 0;
}
bool SEnterBattleCopy::decode(CBufferReader &reader) {
if(!SEnterCopy::decode(reader)){return false;}
return true;}
bool SEnterBattleCopy::encode(CBufferWriter &writer) const {
if(!SEnterCopy::encode(writer)){return false;}
return true;}
void SEnterBattleCopy::clear(){
}
bool SBattleCopyInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,changeForceDt_);
return true;}
bool SBattleCopyInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,changeForceDt_);
return true;}
void SBattleCopyInfo::clear(){
changeForceDt_ = 0;
}
bool SBattlePlayerInfo::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);getIds_.push_back(item);}}
return true;}
bool SBattlePlayerInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,getIds_.size());
for(vector<int32_t>::const_iterator vit=getIds_.begin();vit!=getIds_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SBattlePlayerInfo::clear(){
getIds_.clear();
}
bool SBattleScoreUpdate::decode(CBufferReader &reader) {
PACKET_DECODE(Int16,type_);
PACKET_DECODE(Int16,addScore_);
PACKET_DECODE(Int32,valueEx_);
PACKET_DECODE(String,name_);
return true;}
bool SBattleScoreUpdate::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int16,type_);
PACKET_ENCODE(Int16,addScore_);
PACKET_ENCODE(Int32,valueEx_);
PACKET_ENCODE(String,name_);
return true;}
void SBattleScoreUpdate::clear(){
type_ = 0;
addScore_ = 0;
valueEx_ = 0;
name_.clear();
}
bool SBattleCopyRankItem::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(String,gname_);
PACKET_DECODE(Int32,score_);
return true;}
bool SBattleCopyRankItem::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(String,gname_);
PACKET_ENCODE(Int32,score_);
return true;}
void SBattleCopyRankItem::clear(){
entityId_.clear();
name_.clear();
gname_.clear();
score_ = 0;
}
bool SBattleRankInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,rank_);
PACKET_DECODE(Int32,score_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SBattleCopyRankItem item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool SBattleRankInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,rank_);
PACKET_ENCODE(Int32,score_);
PACKET_ENCODE(UVar32,list_.size());
for(vector<SBattleCopyRankItem>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SBattleRankInfo::clear(){
rank_ = 0;
score_ = 0;
list_.clear();
}
bool SBattleCopyResult::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,score_);
PACKET_DECODE(Int32,rank_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SBattleCopyRankItem item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool SBattleCopyResult::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,score_);
PACKET_ENCODE(Int32,rank_);
PACKET_ENCODE(UVar32,list_.size());
for(vector<SBattleCopyRankItem>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SBattleCopyResult::clear(){
score_ = 0;
rank_ = 0;
list_.clear();
}
bool SEnterFairylandCopy::decode(CBufferReader &reader) {
if(!SEnterCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,floor_);
return true;}
bool SEnterFairylandCopy::encode(CBufferWriter &writer) const {
if(!SEnterCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,floor_);
return true;}
void SEnterFairylandCopy::clear(){
floor_ = 0;
}
bool SCompleteFairylandCopyToClient::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,floor_);
PACKET_DECODE(Int32,grade_);
PACKET_DECODE(Bool,firstS_);
PACKET_DECODE(Int32,timeTaken_);
return true;}
bool SCompleteFairylandCopyToClient::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,floor_);
PACKET_ENCODE(Int32,grade_);
PACKET_ENCODE(Bool,firstS_);
PACKET_ENCODE(Int32,timeTaken_);
return true;}
void SCompleteFairylandCopyToClient::clear(){
floor_ = 0;
grade_ = 0;
firstS_ = 0;
timeTaken_ = 0;
}
bool SFairylandRank::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,rank_);
PACKET_DECODE(Int32,vip_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,floor_);
PACKET_DECODE(Int32,timeTaken_);
return true;}
bool SFairylandRank::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,rank_);
PACKET_ENCODE(Int32,vip_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,floor_);
PACKET_ENCODE(Int32,timeTaken_);
return true;}
void SFairylandRank::clear(){
rank_ = 0;
vip_ = 0;
name_.clear();
floor_ = 0;
timeTaken_ = 0;
}
bool SFairylandRankList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SFairylandRank item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}rankLists_.push_back(item);}}
return true;}
bool SFairylandRankList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,rankLists_.size());
for(vector<SFairylandRank>::const_iterator vit=rankLists_.begin();vit!=rankLists_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SFairylandRankList::clear(){
rankLists_.clear();
}
bool SJiuTianPlayerData::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,exp_);
PACKET_DECODE(Int32,glory_);
return true;}
bool SJiuTianPlayerData::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,exp_);
PACKET_ENCODE(Int32,glory_);
return true;}
void SJiuTianPlayerData::clear(){
exp_ = 0;
glory_ = 0;
}
bool SJiuTianRankData::decode(CBufferReader &reader) {
PACKET_DECODE(String,playerName_);
PACKET_DECODE(String,guildName_);
PACKET_DECODE(Int32,exp_);
PACKET_DECODE(Int32,glory_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rankReward_[k] = v;}}
return true;}
bool SJiuTianRankData::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,playerName_);
PACKET_ENCODE(String,guildName_);
PACKET_ENCODE(Int32,exp_);
PACKET_ENCODE(Int32,glory_);
PACKET_ENCODE(UVar32,rankReward_.size());
for(map<int32_t, int32_t>::const_iterator it=rankReward_.begin();it!=rankReward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SJiuTianRankData::clear(){
playerName_.clear();
guildName_.clear();
exp_ = 0;
glory_ = 0;
rankReward_.clear();
}
bool SJiuTianRankList::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,exp_);
PACKET_DECODE(Int32,glory_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rankReward_[k] = v;}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SJiuTianRankData item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}rankList_.push_back(item);}}
return true;}
bool SJiuTianRankList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,exp_);
PACKET_ENCODE(Int32,glory_);
PACKET_ENCODE(UVar32,rankReward_.size());
for(map<int32_t, int32_t>::const_iterator it=rankReward_.begin();it!=rankReward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,rankList_.size());
for(vector<SJiuTianRankData>::const_iterator vit=rankList_.begin();vit!=rankList_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SJiuTianRankList::clear(){
exp_ = 0;
glory_ = 0;
rankReward_.clear();
rankList_.clear();
}
bool SJiuTianOccupier::decode(CBufferReader &reader) {
if(!playerEntityId_.decode(reader)){return false;}
if(!point_.decode(reader)){return false;}
PACKET_DECODE(Int32,type_);
return true;}
bool SJiuTianOccupier::encode(CBufferWriter &writer) const {
if(!playerEntityId_.encode(writer)){return false;}
if(!point_.encode(writer)){return false;}
PACKET_ENCODE(Int32,type_);
return true;}
void SJiuTianOccupier::clear(){
playerEntityId_.clear();
point_.clear();
type_ = 0;
}
bool SJiuTianJuTianPos::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Point item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}juPoints_.push_back(item);}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Point item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}tianPoints_.push_back(item);}}
return true;}
bool SJiuTianJuTianPos::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,juPoints_.size());
for(vector<Point>::const_iterator vit=juPoints_.begin();vit!=juPoints_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(UVar32,tianPoints_.size());
for(vector<Point>::const_iterator vit=tianPoints_.begin();vit!=tianPoints_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SJiuTianJuTianPos::clear(){
juPoints_.clear();
tianPoints_.clear();
}
bool SJiuTianCopyInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Point item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}juPoints_.push_back(item);}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Identity item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}juOccupier_.push_back(item);}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Point item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}tianPoints_.push_back(item);}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Identity item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}tianOccupier_.push_back(item);}}
PACKET_DECODE(Int32,exp_);
PACKET_DECODE(Int32,glory_);
return true;}
bool SJiuTianCopyInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(UVar32,juPoints_.size());
for(vector<Point>::const_iterator vit=juPoints_.begin();vit!=juPoints_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(UVar32,juOccupier_.size());
for(vector<Identity>::const_iterator vit=juOccupier_.begin();vit!=juOccupier_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(UVar32,tianPoints_.size());
for(vector<Point>::const_iterator vit=tianPoints_.begin();vit!=tianPoints_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(UVar32,tianOccupier_.size());
for(vector<Identity>::const_iterator vit=tianOccupier_.begin();vit!=tianOccupier_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(Int32,exp_);
PACKET_ENCODE(Int32,glory_);
return true;}
void SJiuTianCopyInfo::clear(){
copyCode_ = 0;
juPoints_.clear();
juOccupier_.clear();
tianPoints_.clear();
tianOccupier_.clear();
exp_ = 0;
glory_ = 0;
}
bool SCopyVp::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
PACKET_DECODE(Int32,vp_);
return true;}
bool SCopyVp::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(Int32,vp_);
return true;}
void SCopyVp::clear(){
copyCode_ = 0;
vp_ = 0;
}
bool SCopyVpKickPlayer::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
PACKET_DECODE(Int64,kickTime_);
return true;}
bool SCopyVpKickPlayer::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(Int64,kickTime_);
return true;}
void SCopyVpKickPlayer::clear(){
copyCode_ = 0;
kickTime_ = 0;
}
bool SEnterZhulingCopy::decode(CBufferReader &reader) {
if(!SEnterCopy::decode(reader)){return false;}
return true;}
bool SEnterZhulingCopy::encode(CBufferWriter &writer) const {
if(!SEnterCopy::encode(writer)){return false;}
return true;}
void SEnterZhulingCopy::clear(){
}
bool SCompleteZhulingCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,grade_);
PACKET_DECODE(Int32,timeTaken_);
PACKET_DECODE(Int32,lingli_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);specialReward_[k] = v;}}
return true;}
bool SCompleteZhulingCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,grade_);
PACKET_ENCODE(Int32,timeTaken_);
PACKET_ENCODE(Int32,lingli_);
PACKET_ENCODE(UVar32,specialReward_.size());
for(map<int32_t, int32_t>::const_iterator it=specialReward_.begin();it!=specialReward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompleteZhulingCopy::clear(){
level_ = 0;
grade_ = 0;
timeTaken_ = 0;
lingli_ = 0;
specialReward_.clear();
}
bool SImmortalRoadRankRecord::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int64,hurt_);
return true;}
bool SImmortalRoadRankRecord::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int64,hurt_);
return true;}
void SImmortalRoadRankRecord::clear(){
entityId_.clear();
name_.clear();
hurt_ = 0;
}
bool SCompleteImmortalRoadCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Bool,isAssist_);
PACKET_DECODE(Int32,costTime_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SImmortalRoadRankRecord item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}records_.push_back(item);}}
return true;}
bool SCompleteImmortalRoadCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Bool,isAssist_);
PACKET_ENCODE(Int32,costTime_);
PACKET_ENCODE(UVar32,records_.size());
for(vector<SImmortalRoadRankRecord>::const_iterator vit=records_.begin();vit!=records_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SCompleteImmortalRoadCopy::clear(){
isAssist_ = 0;
costTime_ = 0;
records_.clear();
}
bool SImmortalRoadCopyInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int16,waveNum_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);monsters_[k] = v;}}
return true;}
bool SImmortalRoadCopyInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int16,waveNum_);
PACKET_ENCODE(UVar32,monsters_.size());
for(map<int32_t, int32_t>::const_iterator it=monsters_.begin();it!=monsters_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SImmortalRoadCopyInfo::clear(){
waveNum_ = 0;
monsters_.clear();
}
bool SEnterGuildTrialCopy::decode(CBufferReader &reader) {
if(!SEnterCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,fightTime_);
PACKET_DECODE(Int32,layer_);
return true;}
bool SEnterGuildTrialCopy::encode(CBufferWriter &writer) const {
if(!SEnterCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,fightTime_);
PACKET_ENCODE(Int32,layer_);
return true;}
void SEnterGuildTrialCopy::clear(){
fightTime_ = 0;
layer_ = 0;
}
bool SCompleteGuildTrialCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,completeTime_);
PACKET_DECODE(Int32,layer_);
return true;}
bool SCompleteGuildTrialCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,completeTime_);
PACKET_ENCODE(Int32,layer_);
return true;}
void SCompleteGuildTrialCopy::clear(){
completeTime_ = 0;
layer_ = 0;
}
bool SGuildTrialCopyInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
PACKET_DECODE(Int32,layer_);
PACKET_DECODE(Int64,fightTime_);
return true;}
bool SGuildTrialCopyInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(Int32,layer_);
PACKET_ENCODE(Int64,fightTime_);
return true;}
void SGuildTrialCopyInfo::clear(){
copyCode_ = 0;
layer_ = 0;
fightTime_ = 0;
}
bool SGuildTrialBossSingle::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,layer_);
PACKET_DECODE(Int32,life_);
PACKET_DECODE(Int64,refreshTime_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);msgs::SGuildMember item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}curPlayers_.push_back(item);}}
return true;}
bool SGuildTrialBossSingle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,layer_);
PACKET_ENCODE(Int32,life_);
PACKET_ENCODE(Int64,refreshTime_);
PACKET_ENCODE(UVar32,curPlayers_.size());
for(vector<msgs::SGuildMember>::const_iterator vit=curPlayers_.begin();vit!=curPlayers_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SGuildTrialBossSingle::clear(){
layer_ = 0;
life_ = 0;
refreshTime_ = 0;
curPlayers_.clear();
}
bool SGuildTrialBossList::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SGuildTrialBossSingle v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}bossList_[k] = v;}}
return true;}
bool SGuildTrialBossList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,bossList_.size());
for(map<int32_t, SGuildTrialBossSingle>::const_iterator it=bossList_.begin();it!=bossList_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SGuildTrialBossList::clear(){
bossList_.clear();
}
bool SGuildTrialKickPlayer::decode(CBufferReader &reader) {
return true;}
bool SGuildTrialKickPlayer::encode(CBufferWriter &writer) const {
return true;}
void SGuildTrialKickPlayer::clear(){
}
bool SEnterArenaTtCopy::decode(CBufferReader &reader) {
if(!SEnterCopy::decode(reader)){return false;}
return true;}
bool SEnterArenaTtCopy::encode(CBufferWriter &writer) const {
if(!SEnterCopy::encode(writer)){return false;}
return true;}
void SEnterArenaTtCopy::clear(){
}
bool SCompleteArenaTtCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,addScore_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);reward_[k] = v;}}
return true;}
bool SCompleteArenaTtCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,addScore_);
PACKET_ENCODE(UVar32,reward_.size());
for(map<int32_t, int32_t>::const_iterator it=reward_.begin();it!=reward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompleteArenaTtCopy::clear(){
level_ = 0;
addScore_ = 0;
reward_.clear();
}
bool SArenaTtPlayerInfo::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,career_);
PACKET_DECODE(Int32,arenaLevel_);
PACKET_DECODE(Int32,loseCount_);
return true;}
bool SArenaTtPlayerInfo::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,career_);
PACKET_ENCODE(Int32,arenaLevel_);
PACKET_ENCODE(Int32,loseCount_);
return true;}
void SArenaTtPlayerInfo::clear(){
entityId_.clear();
name_.clear();
career_ = 0;
arenaLevel_ = 0;
loseCount_ = 0;
}
bool SPartnerIslandInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,copyCode_);
return true;}
bool SPartnerIslandInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,copyCode_);
return true;}
void SPartnerIslandInfo::clear(){
type_ = 0;
copyCode_ = 0;
}
bool SCompletePartnerIsland::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,layer_);
PACKET_DECODE(Int32,completeTime_);
PACKET_DECODE(Bool,isQuick_);
PACKET_DECODE(Bool,isDoubleExp_);
return true;}
bool SCompletePartnerIsland::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,layer_);
PACKET_ENCODE(Int32,completeTime_);
PACKET_ENCODE(Bool,isQuick_);
PACKET_ENCODE(Bool,isDoubleExp_);
return true;}
void SCompletePartnerIsland::clear(){
type_ = 0;
layer_ = 0;
completeTime_ = 0;
isQuick_ = 0;
isDoubleExp_ = 0;
}
bool SCompleteGodAnimalIsland::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,layer_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool SCompleteGodAnimalIsland::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,layer_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompleteGodAnimalIsland::clear(){
layer_ = 0;
rewards_.clear();
}
bool SPlayerCompletePartnerIsland::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
PACKET_DECODE(Int32,layer_);
return true;}
bool SPlayerCompletePartnerIsland::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(Int32,layer_);
return true;}
void SPlayerCompletePartnerIsland::clear(){
copyCode_ = 0;
layer_ = 0;
}
bool SGodAnimalIslandPlayer::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,layer_);
PACKET_DECODE(Int64,completeTime_);
return true;}
bool SGodAnimalIslandPlayer::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,layer_);
PACKET_ENCODE(Int64,completeTime_);
return true;}
void SGodAnimalIslandPlayer::clear(){
playerId_ = 0;
name_.clear();
layer_ = 0;
completeTime_ = 0;
}
bool SGodAnimalIslandRank::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SGodAnimalIslandPlayer item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}ranks_.push_back(item);}}
return true;}
bool SGodAnimalIslandRank::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,ranks_.size());
for(vector<SGodAnimalIslandPlayer>::const_iterator vit=ranks_.begin();vit!=ranks_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SGodAnimalIslandRank::clear(){
ranks_.clear();
}
bool SMonsterKill::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,monsterId_);
if(!killPoint_.decode(reader)){return false;}
return true;}
bool SMonsterKill::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,monsterId_);
if(!killPoint_.encode(writer)){return false;}
return true;}
void SMonsterKill::clear(){
monsterId_ = 0;
killPoint_.clear();
}
bool SGodAnimalIslandRound::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,round_);
PACKET_DECODE(Int64,refreshTime_);
return true;}
bool SGodAnimalIslandRound::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,round_);
PACKET_ENCODE(Int64,refreshTime_);
return true;}
void SGodAnimalIslandRound::clear(){
round_ = 0;
refreshTime_ = 0;
}
bool SCompleteThreeWorld::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,layer_);
PACKET_DECODE(Int32,layerHead_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool SCompleteThreeWorld::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,layer_);
PACKET_ENCODE(Int32,layerHead_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompleteThreeWorld::clear(){
layer_ = 0;
layerHead_ = 0;
rewards_.clear();
}
bool SThreeWorldInfoList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);msgs::SMiniPlayer item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
PACKET_DECODE(Int32,layer_);
return true;}
bool SThreeWorldInfoList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<msgs::SMiniPlayer>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(Int32,layer_);
return true;}
void SThreeWorldInfoList::clear(){
list_.clear();
layer_ = 0;
}
bool SSyncThreeWorldHead::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Identity item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}headList_.push_back(item);}}
PACKET_DECODE(String,uid_);
return true;}
bool SSyncThreeWorldHead::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,headList_.size());
for(vector<Identity>::const_iterator vit=headList_.begin();vit!=headList_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(String,uid_);
return true;}
void SSyncThreeWorldHead::clear(){
headList_.clear();
uid_.clear();
}
bool SCompletePetTotem::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,page_);
PACKET_DECODE(Int32,layer_);
PACKET_DECODE(Int32,star_);
PACKET_DECODE(Int32,completeTime_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool SCompletePetTotem::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,page_);
PACKET_ENCODE(Int32,layer_);
PACKET_ENCODE(Int32,star_);
PACKET_ENCODE(Int32,completeTime_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompletePetTotem::clear(){
page_ = 0;
layer_ = 0;
star_ = 0;
completeTime_ = 0;
rewards_.clear();
}
bool SAwakeCopyInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
PACKET_DECODE(Int32,floor_);
PACKET_DECODE(Int32,layer_);
return true;}
bool SAwakeCopyInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(Int32,floor_);
PACKET_ENCODE(Int32,layer_);
return true;}
void SAwakeCopyInfo::clear(){
copyCode_ = 0;
floor_ = 0;
layer_ = 0;
}
bool SCompleteAwakeCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,floor_);
PACKET_DECODE(Int32,layer_);
return true;}
bool SCompleteAwakeCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,floor_);
PACKET_ENCODE(Int32,layer_);
return true;}
void SCompleteAwakeCopy::clear(){
floor_ = 0;
layer_ = 0;
}
bool SPlayerPetTotem::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,totalStar_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);stars_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);notGotFirstReward_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);notGotCollectStarReward_[k] = v;}}
return true;}
bool SPlayerPetTotem::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,totalStar_);
PACKET_ENCODE(UVar32,stars_.size());
for(map<int32_t, int32_t>::const_iterator it=stars_.begin();it!=stars_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,notGotFirstReward_.size());
for(map<int32_t, int32_t>::const_iterator it=notGotFirstReward_.begin();it!=notGotFirstReward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,notGotCollectStarReward_.size());
for(map<int32_t, int32_t>::const_iterator it=notGotCollectStarReward_.begin();it!=notGotCollectStarReward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SPlayerPetTotem::clear(){
totalStar_ = 0;
stars_.clear();
notGotFirstReward_.clear();
notGotCollectStarReward_.clear();
}
bool SPetTotemInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,page_);
PACKET_DECODE(Int32,layer_);
return true;}
bool SPetTotemInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,page_);
PACKET_ENCODE(Int32,layer_);
return true;}
void SPetTotemInfo::clear(){
page_ = 0;
layer_ = 0;
}
bool SCompleteMengPetCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,layer_);
PACKET_DECODE(Bool,isAssist_);
PACKET_DECODE(Int32,assistNum_);
PACKET_DECODE(Int32,costTime_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);reward_[k] = v;}}
return true;}
bool SCompleteMengPetCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,layer_);
PACKET_ENCODE(Bool,isAssist_);
PACKET_ENCODE(Int32,assistNum_);
PACKET_ENCODE(Int32,costTime_);
PACKET_ENCODE(UVar32,reward_.size());
for(map<int32_t, int32_t>::const_iterator it=reward_.begin();it!=reward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompleteMengPetCopy::clear(){
layer_ = 0;
isAssist_ = 0;
assistNum_ = 0;
costTime_ = 0;
reward_.clear();
}
bool SHirePlayer::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int64,combat_);
PACKET_DECODE(Int32,career_);
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,careerLevel_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);ornaments_[k] = v;}}
PACKET_DECODE(Int32,count_);
return true;}
bool SHirePlayer::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(Int32,career_);
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,careerLevel_);
PACKET_ENCODE(UVar32,ornaments_.size());
for(map<int16_t, int32_t>::const_iterator it=ornaments_.begin();it!=ornaments_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,count_);
return true;}
void SHirePlayer::clear(){
entityId_.clear();
name_.clear();
combat_ = 0;
career_ = 0;
level_ = 0;
careerLevel_ = 0;
ornaments_.clear();
count_ = 0;
}
bool SMengPetHireList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SHirePlayer item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}hireList_.push_back(item);}}
return true;}
bool SMengPetHireList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,hireList_.size());
for(vector<SHirePlayer>::const_iterator vit=hireList_.begin();vit!=hireList_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SMengPetHireList::clear(){
hireList_.clear();
}
bool SDragonSoulCopyInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,floor_);
PACKET_DECODE(Int32,layer_);
return true;}
bool SDragonSoulCopyInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,floor_);
PACKET_ENCODE(Int32,layer_);
return true;}
void SDragonSoulCopyInfo::clear(){
floor_ = 0;
layer_ = 0;
}
bool SCompleteDragonSoulCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,floor_);
PACKET_DECODE(Int32,layer_);
PACKET_DECODE(Int32,completeTime_);
PACKET_DECODE(Int32,star_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool SCompleteDragonSoulCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,floor_);
PACKET_ENCODE(Int32,layer_);
PACKET_ENCODE(Int32,completeTime_);
PACKET_ENCODE(Int32,star_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompleteDragonSoulCopy::clear(){
floor_ = 0;
layer_ = 0;
completeTime_ = 0;
star_ = 0;
rewards_.clear();
}
bool SForgeCopyInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
PACKET_DECODE(Int32,floor_);
PACKET_DECODE(Int32,round_);
PACKET_DECODE(Int32,monsterKilled_);
PACKET_DECODE(Int32,fleed_);
if(!encourage_.decode(reader)){return false;}
if(!slowDown_.decode(reader)){return false;}
return true;}
bool SForgeCopyInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(Int32,floor_);
PACKET_ENCODE(Int32,round_);
PACKET_ENCODE(Int32,monsterKilled_);
PACKET_ENCODE(Int32,fleed_);
if(!encourage_.encode(writer)){return false;}
if(!slowDown_.encode(writer)){return false;}
return true;}
void SForgeCopyInfo::clear(){
copyCode_ = 0;
floor_ = 0;
round_ = 0;
monsterKilled_ = 0;
fleed_ = 0;
encourage_.clear();
slowDown_.clear();
}
bool SCompleteForgeCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,floor_);
PACKET_DECODE(Int32,grade_);
PACKET_DECODE(Int32,monsterKilledNum_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);drop_[k] = v;}}
PACKET_DECODE(Bool,isFirstToS_);
return true;}
bool SCompleteForgeCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,floor_);
PACKET_ENCODE(Int32,grade_);
PACKET_ENCODE(Int32,monsterKilledNum_);
PACKET_ENCODE(UVar32,drop_.size());
for(map<int32_t, int32_t>::const_iterator it=drop_.begin();it!=drop_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Bool,isFirstToS_);
return true;}
void SCompleteForgeCopy::clear(){
floor_ = 0;
grade_ = 0;
monsterKilledNum_ = 0;
drop_.clear();
isFirstToS_ = 0;
}
bool SForgeCopyRank::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,floor_);
PACKET_DECODE(Int32,fleedNum_);
return true;}
bool SForgeCopyRank::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,floor_);
PACKET_ENCODE(Int32,fleedNum_);
return true;}
void SForgeCopyRank::clear(){
playerId_ = 0;
name_.clear();
floor_ = 0;
fleedNum_ = 0;
}
bool SForgeCopyRankList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SForgeCopyRank item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}ranks_.push_back(item);}}
return true;}
bool SForgeCopyRankList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,ranks_.size());
for(vector<SForgeCopyRank>::const_iterator vit=ranks_.begin();vit!=ranks_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SForgeCopyRankList::clear(){
ranks_.clear();
}
bool SCompleteWeekCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,level_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);reward_[k] = v;}}
return true;}
bool SCompleteWeekCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(UVar32,reward_.size());
for(map<int32_t, int32_t>::const_iterator it=reward_.begin();it!=reward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompleteWeekCopy::clear(){
level_ = 0;
reward_.clear();
}
bool SCompletePlaceTreasureCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,level_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);reward_[k] = v;}}
return true;}
bool SCompletePlaceTreasureCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(UVar32,reward_.size());
for(map<int32_t, int32_t>::const_iterator it=reward_.begin();it!=reward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompletePlaceTreasureCopy::clear(){
level_ = 0;
reward_.clear();
}
bool SEnterSPACopy::decode(CBufferReader &reader) {
if(!SEnterCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,cellNum_);
return true;}
bool SEnterSPACopy::encode(CBufferWriter &writer) const {
if(!SEnterCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,cellNum_);
return true;}
void SEnterSPACopy::clear(){
cellNum_ = 0;
}
bool SSPACopyReward::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);reward_[k] = v;}}
return true;}
bool SSPACopyReward::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,reward_.size());
for(map<int32_t, int32_t>::const_iterator it=reward_.begin();it!=reward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SSPACopyReward::clear(){
reward_.clear();
}
bool SSPACopyRoomInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);roomInfo_[k] = v;}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);recentRoom_.push_back(item);}}
return true;}
bool SSPACopyRoomInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(UVar32,roomInfo_.size());
for(map<int32_t, int32_t>::const_iterator it=roomInfo_.begin();it!=roomInfo_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,recentRoom_.size());
for(vector<int32_t>::const_iterator vit=recentRoom_.begin();vit!=recentRoom_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SSPACopyRoomInfo::clear(){
copyCode_ = 0;
roomInfo_.clear();
recentRoom_.clear();
}
bool SSPACopyAct::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,num_);
PACKET_DECODE(Int64,time_);
return true;}
bool SSPACopyAct::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,num_);
PACKET_ENCODE(Int64,time_);
return true;}
void SSPACopyAct::clear(){
num_ = 0;
time_ = 0;
}
bool SSPACopyActInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SSPACopyAct v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}actInfo_[k] = v;}}
PACKET_DECODE(Int32,lastType_);
PACKET_DECODE(Int64,lastTime_);
return true;}
bool SSPACopyActInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(UVar32,actInfo_.size());
for(map<int32_t, SSPACopyAct>::const_iterator it=actInfo_.begin();it!=actInfo_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
PACKET_ENCODE(Int32,lastType_);
PACKET_ENCODE(Int64,lastTime_);
return true;}
void SSPACopyActInfo::clear(){
copyCode_ = 0;
actInfo_.clear();
lastType_ = 0;
lastTime_ = 0;
}
bool SSPACopyActBROInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
if(!fromId_.decode(reader)){return false;}
if(!toId_.decode(reader)){return false;}
PACKET_DECODE(Int64,time_);
return true;}
bool SSPACopyActBROInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
if(!fromId_.encode(writer)){return false;}
if(!toId_.encode(writer)){return false;}
PACKET_ENCODE(Int64,time_);
return true;}
void SSPACopyActBROInfo::clear(){
type_ = 0;
fromId_.clear();
toId_.clear();
time_ = 0;
}
bool SSPACopyFlower::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);flower_[k] = v;}}
return true;}
bool SSPACopyFlower::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(UVar32,flower_.size());
for(map<int32_t, int32_t>::const_iterator it=flower_.begin();it!=flower_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SSPACopyFlower::clear(){
copyCode_ = 0;
flower_.clear();
}
bool SSPAMiniPlayer::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(Int32,career_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,rank_);
PACKET_DECODE(Int32,recFlower_);
PACKET_DECODE(Int16,sex_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);ornaments_[k] = v;}}
return true;}
bool SSPAMiniPlayer::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,career_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,rank_);
PACKET_ENCODE(Int32,recFlower_);
PACKET_ENCODE(Int16,sex_);
PACKET_ENCODE(UVar32,ornaments_.size());
for(map<int16_t, int32_t>::const_iterator it=ornaments_.begin();it!=ornaments_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SSPAMiniPlayer::clear(){
entityId_.clear();
career_ = 0;
name_.clear();
rank_ = 0;
recFlower_ = 0;
sex_ = 0;
ornaments_.clear();
}
bool SCompleteSPACopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewardGot_[k] = v;}}
return true;}
bool SCompleteSPACopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(UVar32,rewardGot_.size());
for(map<int32_t, int32_t>::const_iterator it=rewardGot_.begin();it!=rewardGot_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompleteSPACopy::clear(){
rewardGot_.clear();
}
bool SSPAFlorwerRankList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SSPAMiniPlayer item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}rankList_.push_back(item);}}
return true;}
bool SSPAFlorwerRankList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,rankList_.size());
for(vector<SSPAMiniPlayer>::const_iterator vit=rankList_.begin();vit!=rankList_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SSPAFlorwerRankList::clear(){
rankList_.clear();
}
bool SCopyContinueKill::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
PACKET_DECODE(Int32,killNum_);
return true;}
bool SCopyContinueKill::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(Int32,killNum_);
return true;}
void SCopyContinueKill::clear(){
copyCode_ = 0;
killNum_ = 0;
}
bool SSPACopySendFlowerInfo::decode(CBufferReader &reader) {
if(!fromPlayerId_.decode(reader)){return false;}
PACKET_DECODE(String,fromName_);
if(!toPlayerId_.decode(reader)){return false;}
PACKET_DECODE(Int32,itemCode_);
return true;}
bool SSPACopySendFlowerInfo::encode(CBufferWriter &writer) const {
if(!fromPlayerId_.encode(writer)){return false;}
PACKET_ENCODE(String,fromName_);
if(!toPlayerId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,itemCode_);
return true;}
void SSPACopySendFlowerInfo::clear(){
fromPlayerId_.clear();
fromName_.clear();
toPlayerId_.clear();
itemCode_ = 0;
}
bool SSPAPlayerFlower::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,receive_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);bought_[k] = v;}}
return true;}
bool SSPAPlayerFlower::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,receive_);
PACKET_ENCODE(UVar32,bought_.size());
for(map<int32_t, int32_t>::const_iterator it=bought_.begin();it!=bought_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SSPAPlayerFlower::clear(){
receive_ = 0;
bought_.clear();
}
bool SPryCrossBServer::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,serverId_);
PACKET_DECODE(Int32,proxyId_);
PACKET_DECODE(Int32,goldValue_);
PACKET_DECODE(Int32,activeKey_);
return true;}
bool SPryCrossBServer::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,serverId_);
PACKET_ENCODE(Int32,proxyId_);
PACKET_ENCODE(Int32,goldValue_);
PACKET_ENCODE(Int32,activeKey_);
return true;}
void SPryCrossBServer::clear(){
serverId_ = 0;
proxyId_ = 0;
goldValue_ = 0;
activeKey_ = 0;
}
bool SCompletePryCrossB::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
return true;}
bool SCompletePryCrossB::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
return true;}
void SCompletePryCrossB::clear(){
}
bool SPryCrossBInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,serverId_);
PACKET_DECODE(Int32,proxyId_);
PACKET_DECODE(Int32,copyCode_);
PACKET_DECODE(Int32,belongValue_);
PACKET_DECODE(Int32,attackValue_);
PACKET_DECODE(Int32,defenseValue_);
PACKET_DECODE(Int32,mineralAttack_);
return true;}
bool SPryCrossBInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,serverId_);
PACKET_ENCODE(Int32,proxyId_);
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(Int32,belongValue_);
PACKET_ENCODE(Int32,attackValue_);
PACKET_ENCODE(Int32,defenseValue_);
PACKET_ENCODE(Int32,mineralAttack_);
return true;}
void SPryCrossBInfo::clear(){
serverId_ = 0;
proxyId_ = 0;
copyCode_ = 0;
belongValue_ = 0;
attackValue_ = 0;
defenseValue_ = 0;
mineralAttack_ = 0;
}
bool SEnterOfficialCampaign::decode(CBufferReader &reader) {
if(!SEnterCopy::decode(reader)){return false;}
PACKET_DECODE(Bool,isCross_);
PACKET_DECODE(Int32,officialId_);
return true;}
bool SEnterOfficialCampaign::encode(CBufferWriter &writer) const {
if(!SEnterCopy::encode(writer)){return false;}
PACKET_ENCODE(Bool,isCross_);
PACKET_ENCODE(Int32,officialId_);
return true;}
void SEnterOfficialCampaign::clear(){
isCross_ = 0;
officialId_ = 0;
}
bool SCompleteOfficialCampaign::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Bool,isCross_);
PACKET_DECODE(Int32,officialId_);
PACKET_DECODE(Int64,combat_);
return true;}
bool SCompleteOfficialCampaign::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Bool,isCross_);
PACKET_ENCODE(Int32,officialId_);
PACKET_ENCODE(Int64,combat_);
return true;}
void SCompleteOfficialCampaign::clear(){
isCross_ = 0;
officialId_ = 0;
combat_ = 0;
}
bool SOfficialCampaignInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Bool,isCross_);
PACKET_DECODE(Int32,copyCode_);
return true;}
bool SOfficialCampaignInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Bool,isCross_);
PACKET_ENCODE(Int32,copyCode_);
return true;}
void SOfficialCampaignInfo::clear(){
isCross_ = 0;
copyCode_ = 0;
}
bool SOfficialInfoSingle::decode(CBufferReader &reader) {
PACKET_DECODE(Bool,isCross_);
if(!publicPlayer_.decode(reader)){return false;}
PACKET_DECODE(Int64,updateTime_);
return true;}
bool SOfficialInfoSingle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Bool,isCross_);
if(!publicPlayer_.encode(writer)){return false;}
PACKET_ENCODE(Int64,updateTime_);
return true;}
void SOfficialInfoSingle::clear(){
isCross_ = 0;
publicPlayer_.clear();
updateTime_ = 0;
}
bool SOfficialInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Bool,isCross_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SOfficialInfoSingle v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}officialMap_[k] = v;}}
return true;}
bool SOfficialInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Bool,isCross_);
PACKET_ENCODE(UVar32,officialMap_.size());
for(map<int32_t, SOfficialInfoSingle>::const_iterator it=officialMap_.begin();it!=officialMap_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SOfficialInfo::clear(){
isCross_ = 0;
officialMap_.clear();
}
bool SCompleteGodMagicTower::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,tower_);
PACKET_DECODE(Int32,layer_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);targetRewards_[k] = v;}}
return true;}
bool SCompleteGodMagicTower::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,tower_);
PACKET_ENCODE(Int32,layer_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,targetRewards_.size());
for(map<int32_t, int32_t>::const_iterator it=targetRewards_.begin();it!=targetRewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompleteGodMagicTower::clear(){
tower_ = 0;
layer_ = 0;
rewards_.clear();
targetRewards_.clear();
}
bool SGodMagicTowerAttr::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,per_);
PACKET_DECODE(Int32,tower_);
PACKET_DECODE(Int32,layer_);
return true;}
bool SGodMagicTowerAttr::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,per_);
PACKET_ENCODE(Int32,tower_);
PACKET_ENCODE(Int32,layer_);
return true;}
void SGodMagicTowerAttr::clear(){
playerId_ = 0;
name_.clear();
per_ = 0;
tower_ = 0;
layer_ = 0;
}
bool SGodMagicTowerAddAttr::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SGodMagicTowerAttr item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}likeAttr_.push_back(item);}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SGodMagicTowerAttr item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}helpedAttr_.push_back(item);}}
return true;}
bool SGodMagicTowerAddAttr::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,likeAttr_.size());
for(vector<SGodMagicTowerAttr>::const_iterator vit=likeAttr_.begin();vit!=likeAttr_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(UVar32,helpedAttr_.size());
for(vector<SGodMagicTowerAttr>::const_iterator vit=helpedAttr_.begin();vit!=helpedAttr_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SGodMagicTowerAddAttr::clear(){
likeAttr_.clear();
helpedAttr_.clear();
}
bool SGodMagicTowerRank::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,tower_);
PACKET_DECODE(Int32,layer_);
PACKET_DECODE(Bool,canLike_);
return true;}
bool SGodMagicTowerRank::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,tower_);
PACKET_ENCODE(Int32,layer_);
PACKET_ENCODE(Bool,canLike_);
return true;}
void SGodMagicTowerRank::clear(){
playerId_ = 0;
name_.clear();
tower_ = 0;
layer_ = 0;
canLike_ = 0;
}
bool SGodMagicTowerRankList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SGodMagicTowerRank item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}ranks_.push_back(item);}}
return true;}
bool SGodMagicTowerRankList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,ranks_.size());
for(vector<SGodMagicTowerRank>::const_iterator vit=ranks_.begin();vit!=ranks_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SGodMagicTowerRankList::clear(){
ranks_.clear();
}
bool SGodMagicTowerHelp::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,career_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);ornaments_[k] = v;}}
PACKET_DECODE(Int32,helpTime_);
PACKET_DECODE(Int32,addPer_);
return true;}
bool SGodMagicTowerHelp::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,career_);
PACKET_ENCODE(UVar32,ornaments_.size());
for(map<int16_t, int32_t>::const_iterator it=ornaments_.begin();it!=ornaments_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,helpTime_);
PACKET_ENCODE(Int32,addPer_);
return true;}
void SGodMagicTowerHelp::clear(){
playerId_ = 0;
name_.clear();
career_ = 0;
ornaments_.clear();
helpTime_ = 0;
addPer_ = 0;
}
bool SGodMagicTowerHelpList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SGodMagicTowerHelp item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool SGodMagicTowerHelpList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<SGodMagicTowerHelp>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SGodMagicTowerHelpList::clear(){
list_.clear();
}
bool SCompleteAvatarTower::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,floor_);
PACKET_DECODE(Int32,completeTime_);
PACKET_DECODE(Bool,isFirst_);
return true;}
bool SCompleteAvatarTower::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,floor_);
PACKET_ENCODE(Int32,completeTime_);
PACKET_ENCODE(Bool,isFirst_);
return true;}
void SCompleteAvatarTower::clear(){
floor_ = 0;
completeTime_ = 0;
isFirst_ = 0;
}
bool SAvatarTowerInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
PACKET_DECODE(Int32,floor_);
return true;}
bool SAvatarTowerInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(Int32,floor_);
return true;}
void SAvatarTowerInfo::clear(){
copyCode_ = 0;
floor_ = 0;
}
bool SCompleteMonsterAround::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,gold_);
PACKET_DECODE(Int32,life_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);reward_[k] = v;}}
return true;}
bool SCompleteMonsterAround::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,gold_);
PACKET_ENCODE(Int32,life_);
PACKET_ENCODE(UVar32,reward_.size());
for(map<int32_t, int32_t>::const_iterator it=reward_.begin();it!=reward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompleteMonsterAround::clear(){
level_ = 0;
gold_ = 0;
life_ = 0;
reward_.clear();
}
bool SMonsterAroundCopyInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,level_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;Point v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}towerPos_[k] = v;}}
return true;}
bool SMonsterAroundCopyInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(UVar32,towerPos_.size());
for(map<int32_t, Point>::const_iterator it=towerPos_.begin();it!=towerPos_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SMonsterAroundCopyInfo::clear(){
level_ = 0;
towerPos_.clear();
}
bool SMonsterAroundTower::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,index_);
PACKET_DECODE(Int32,life_);
PACKET_DECODE(Bool,beAttack_);
return true;}
bool SMonsterAroundTower::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,index_);
PACKET_ENCODE(Int32,life_);
PACKET_ENCODE(Bool,beAttack_);
return true;}
void SMonsterAroundTower::clear(){
index_ = 0;
life_ = 0;
beAttack_ = 0;
}
bool SMonsterAroundTowers::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SMonsterAroundTower item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}towers_.push_back(item);}}
return true;}
bool SMonsterAroundTowers::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,towers_.size());
for(vector<SMonsterAroundTower>::const_iterator vit=towers_.begin();vit!=towers_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SMonsterAroundTowers::clear(){
towers_.clear();
}
bool SMonsterAroundChat::decode(CBufferReader &reader) {
if(!fromId_.decode(reader)){return false;}
PACKET_DECODE(String,fromName_);
PACKET_DECODE(Int32,chatIndex_);
return true;}
bool SMonsterAroundChat::encode(CBufferWriter &writer) const {
if(!fromId_.encode(writer)){return false;}
PACKET_ENCODE(String,fromName_);
PACKET_ENCODE(Int32,chatIndex_);
return true;}
void SMonsterAroundChat::clear(){
fromId_.clear();
fromName_.clear();
chatIndex_ = 0;
}
bool SMonsterAroundKillInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,killNum_);
PACKET_DECODE(Int32,openNum_);
return true;}
bool SMonsterAroundKillInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,killNum_);
PACKET_ENCODE(Int32,openNum_);
return true;}
void SMonsterAroundKillInfo::clear(){
killNum_ = 0;
openNum_ = 0;
}
bool SCrossCityData::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,index_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Identity item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}emperors_.push_back(item);}}
if(!occupyServer_.decode(reader)){return false;}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Identity item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}fightServers_.push_back(item);}}
return true;}
bool SCrossCityData::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,index_);
PACKET_ENCODE(UVar32,emperors_.size());
for(vector<Identity>::const_iterator vit=emperors_.begin();vit!=emperors_.end();++vit){if(!vit->encode(writer)){return false;}}
if(!occupyServer_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,fightServers_.size());
for(vector<Identity>::const_iterator vit=fightServers_.begin();vit!=fightServers_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SCrossCityData::clear(){
index_ = 0;
emperors_.clear();
occupyServer_.clear();
fightServers_.clear();
}
bool SCompleteCrossCityWarCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,cityIndex_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool SCompleteCrossCityWarCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,cityIndex_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompleteCrossCityWarCopy::clear(){
cityIndex_ = 0;
rewards_.clear();
}
bool SCrossCityWarServerData::decode(CBufferReader &reader) {
if(!serverId_.decode(reader)){return false;}
PACKET_DECODE(Int32,force_);
PACKET_DECODE(Int32,score_);
return true;}
bool SCrossCityWarServerData::encode(CBufferWriter &writer) const {
if(!serverId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,force_);
PACKET_ENCODE(Int32,score_);
return true;}
void SCrossCityWarServerData::clear(){
serverId_.clear();
force_ = 0;
score_ = 0;
}
bool SCrossCityWarCopyInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,cityIndex_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SCrossCityWarServerData item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}servers_.push_back(item);}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);towers_[k] = v;}}
return true;}
bool SCrossCityWarCopyInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,cityIndex_);
PACKET_ENCODE(UVar32,servers_.size());
for(vector<SCrossCityWarServerData>::const_iterator vit=servers_.begin();vit!=servers_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(UVar32,towers_.size());
for(map<int32_t, int32_t>::const_iterator it=towers_.begin();it!=towers_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCrossCityWarCopyInfo::clear(){
cityIndex_ = 0;
servers_.clear();
towers_.clear();
}
bool SCrossCityWarPlayerInfo::decode(CBufferReader &reader) {
if(!serverId_.decode(reader)){return false;}
PACKET_DECODE(Int32,gonglao_);
PACKET_DECODE(Int32,killNum_);
return true;}
bool SCrossCityWarPlayerInfo::encode(CBufferWriter &writer) const {
if(!serverId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,gonglao_);
PACKET_ENCODE(Int32,killNum_);
return true;}
void SCrossCityWarPlayerInfo::clear(){
serverId_.clear();
gonglao_ = 0;
killNum_ = 0;
}
bool SCompleteCrossCityWar2Copy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,cityIndex_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool SCompleteCrossCityWar2Copy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,cityIndex_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompleteCrossCityWar2Copy::clear(){
cityIndex_ = 0;
rewards_.clear();
}
bool SCrossCityWar2ServerData::decode(CBufferReader &reader) {
if(!serverId_.decode(reader)){return false;}
PACKET_DECODE(Int32,force_);
PACKET_DECODE(Int32,score_);
PACKET_DECODE(Bool,defence_);
return true;}
bool SCrossCityWar2ServerData::encode(CBufferWriter &writer) const {
if(!serverId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,force_);
PACKET_ENCODE(Int32,score_);
PACKET_ENCODE(Bool,defence_);
return true;}
void SCrossCityWar2ServerData::clear(){
serverId_.clear();
force_ = 0;
score_ = 0;
defence_ = 0;
}
bool SCrossCityWar2CopyInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,cityIndex_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SCrossCityWar2ServerData item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}servers_.push_back(item);}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Identity item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}towerList_.push_back(item);}}
return true;}
bool SCrossCityWar2CopyInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,cityIndex_);
PACKET_ENCODE(UVar32,servers_.size());
for(vector<SCrossCityWar2ServerData>::const_iterator vit=servers_.begin();vit!=servers_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(UVar32,towerList_.size());
for(vector<Identity>::const_iterator vit=towerList_.begin();vit!=towerList_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SCrossCityWar2CopyInfo::clear(){
cityIndex_ = 0;
servers_.clear();
towerList_.clear();
}
bool SCrossCityWar2PlayerInfo::decode(CBufferReader &reader) {
if(!serverId_.decode(reader)){return false;}
PACKET_DECODE(Int32,gonglao_);
PACKET_DECODE(Int32,killNum_);
return true;}
bool SCrossCityWar2PlayerInfo::encode(CBufferWriter &writer) const {
if(!serverId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,gonglao_);
PACKET_ENCODE(Int32,killNum_);
return true;}
void SCrossCityWar2PlayerInfo::clear(){
serverId_.clear();
gonglao_ = 0;
killNum_ = 0;
}
bool SCrossCityHistory::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,cityIndex_);
if(!serverId_.decode(reader)){return false;}
PACKET_DECODE(Int64,occupyDt_);
PACKET_DECODE(Bool,isOccupy_);
return true;}
bool SCrossCityHistory::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,cityIndex_);
if(!serverId_.encode(writer)){return false;}
PACKET_ENCODE(Int64,occupyDt_);
PACKET_ENCODE(Bool,isOccupy_);
return true;}
void SCrossCityHistory::clear(){
cityIndex_ = 0;
serverId_.clear();
occupyDt_ = 0;
isOccupy_ = 0;
}
bool SCrossCityList::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,signUpDt1_);
PACKET_DECODE(Int64,signUpDt2_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SCrossCityData item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}cityList_.push_back(item);}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SCrossCityHistory item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}historys_.push_back(item);}}
return true;}
bool SCrossCityList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,signUpDt1_);
PACKET_ENCODE(Int64,signUpDt2_);
PACKET_ENCODE(UVar32,cityList_.size());
for(vector<SCrossCityData>::const_iterator vit=cityList_.begin();vit!=cityList_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(UVar32,historys_.size());
for(vector<SCrossCityHistory>::const_iterator vit=historys_.begin();vit!=historys_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SCrossCityList::clear(){
signUpDt1_ = 0;
signUpDt2_ = 0;
cityList_.clear();
historys_.clear();
}
bool SCrossCityWarSignUp::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,index_);
if(!serverId_.decode(reader)){return false;}
return true;}
bool SCrossCityWarSignUp::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,index_);
if(!serverId_.encode(writer)){return false;}
return true;}
void SCrossCityWarSignUp::clear(){
index_ = 0;
serverId_.clear();
}
bool SSyncCrossCity::decode(CBufferReader &reader) {
if(!serverId_.decode(reader)){return false;}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);cityMap_[k] = v;}}
return true;}
bool SSyncCrossCity::encode(CBufferWriter &writer) const {
if(!serverId_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,cityMap_.size());
for(map<int32_t, int32_t>::const_iterator it=cityMap_.begin();it!=cityMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SSyncCrossCity::clear(){
serverId_.clear();
cityMap_.clear();
}
bool SCrossCityWarCopyBroadcastKill::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,killType_);
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,playerName_);
PACKET_DECODE(Int32,killNum_);
PACKET_DECODE(String,toPlayerName_);
return true;}
bool SCrossCityWarCopyBroadcastKill::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,killType_);
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,playerName_);
PACKET_ENCODE(Int32,killNum_);
PACKET_ENCODE(String,toPlayerName_);
return true;}
void SCrossCityWarCopyBroadcastKill::clear(){
killType_ = 0;
entityId_.clear();
playerName_.clear();
killNum_ = 0;
toPlayerName_.clear();
}
bool SCrossCityHuangDiPos::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(Int32,cityIndex_);
return true;}
bool SCrossCityHuangDiPos::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,cityIndex_);
return true;}
void SCrossCityHuangDiPos::clear(){
entityId_.clear();
cityIndex_ = 0;
}
bool SPlayerCrossCityWar::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);dailyGot_.push_back(item);}}
return true;}
bool SPlayerCrossCityWar::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,dailyGot_.size());
for(vector<int32_t>::const_iterator vit=dailyGot_.begin();vit!=dailyGot_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SPlayerCrossCityWar::clear(){
dailyGot_.clear();
}
bool SCrossTeamRecord::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int64,hurt_);
return true;}
bool SCrossTeamRecord::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int64,hurt_);
return true;}
void SCrossTeamRecord::clear(){
entityId_.clear();
name_.clear();
hurt_ = 0;
}
bool SCompleteCrossTeamCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Bool,isAssist_);
PACKET_DECODE(Int32,costTime_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SCrossTeamRecord item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}records_.push_back(item);}}
return true;}
bool SCompleteCrossTeamCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Bool,isAssist_);
PACKET_ENCODE(Int32,costTime_);
PACKET_ENCODE(UVar32,records_.size());
for(vector<SCrossTeamRecord>::const_iterator vit=records_.begin();vit!=records_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SCompleteCrossTeamCopy::clear(){
isAssist_ = 0;
costTime_ = 0;
records_.clear();
}
bool SCrossTeamCopyInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int16,waveNum_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);monsters_[k] = v;}}
return true;}
bool SCrossTeamCopyInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int16,waveNum_);
PACKET_ENCODE(UVar32,monsters_.size());
for(map<int32_t, int32_t>::const_iterator it=monsters_.begin();it!=monsters_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCrossTeamCopyInfo::clear(){
waveNum_ = 0;
monsters_.clear();
}
bool SPlayerCrossTeamData::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,targetGot_);
PACKET_DECODE(Int32,maxPassedCopy_);
PACKET_DECODE(Int32,passedNum_);
return true;}
bool SPlayerCrossTeamData::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,targetGot_);
PACKET_ENCODE(Int32,maxPassedCopy_);
PACKET_ENCODE(Int32,passedNum_);
return true;}
void SPlayerCrossTeamData::clear(){
targetGot_ = 0;
maxPassedCopy_ = 0;
passedNum_ = 0;
}
bool SCompleteGroupFight::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,addStar_);
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(Int32,todayCount_);
PACKET_DECODE(Int32,addTeamStar_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool SCompleteGroupFight::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,addStar_);
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,todayCount_);
PACKET_ENCODE(Int32,addTeamStar_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompleteGroupFight::clear(){
addStar_ = 0;
entityId_.clear();
todayCount_ = 0;
addTeamStar_ = 0;
rewards_.clear();
}
bool SCompleteGroupFightVec::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SCompleteGroupFight item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}res_.push_back(item);}}
return true;}
bool SCompleteGroupFightVec::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,res_.size());
for(vector<SCompleteGroupFight>::const_iterator vit=res_.begin();vit!=res_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SCompleteGroupFightVec::clear(){
res_.clear();
}
bool SGroupFightJoin::decode(CBufferReader &reader) {
if(!playerId_.decode(reader)){return false;}
PACKET_DECODE(String,playerName_);
PACKET_DECODE(String,teamName_);
PACKET_DECODE(Int32,career_);
PACKET_DECODE(Int64,combat_);
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,star_);
return true;}
bool SGroupFightJoin::encode(CBufferWriter &writer) const {
if(!playerId_.encode(writer)){return false;}
PACKET_ENCODE(String,playerName_);
PACKET_ENCODE(String,teamName_);
PACKET_ENCODE(Int32,career_);
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,star_);
return true;}
void SGroupFightJoin::clear(){
playerId_.clear();
playerName_.clear();
teamName_.clear();
career_ = 0;
combat_ = 0;
level_ = 0;
star_ = 0;
}
bool SGroupFightTeam::decode(CBufferReader &reader) {
PACKET_DECODE(String,name_);
if(!captainId_.decode(reader)){return false;}
PACKET_DECODE(String,captainName_);
PACKET_DECODE(Int32,captainLevel_);
PACKET_DECODE(Int32,captainStar_);
if(!teams_.decode(reader)){return false;}
return true;}
bool SGroupFightTeam::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,name_);
if(!captainId_.encode(writer)){return false;}
PACKET_ENCODE(String,captainName_);
PACKET_ENCODE(Int32,captainLevel_);
PACKET_ENCODE(Int32,captainStar_);
if(!teams_.encode(writer)){return false;}
return true;}
void SGroupFightTeam::clear(){
name_.clear();
captainId_.clear();
captainName_.clear();
captainLevel_ = 0;
captainStar_ = 0;
teams_.clear();
}
bool SGroupFightTeams::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SGroupFightTeam item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}teams_.push_back(item);}}
return true;}
bool SGroupFightTeams::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,teams_.size());
for(vector<SGroupFightTeam>::const_iterator vit=teams_.begin();vit!=teams_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SGroupFightTeams::clear(){
teams_.clear();
}
bool SGroupFightMatchSingle::decode(CBufferReader &reader) {
PACKET_DECODE(String,teamName_);
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,star_);
PACKET_DECODE(Int32,successCount_);
PACKET_DECODE(Int32,todayCount_);
if(!publicPlayer_.decode(reader)){return false;}
return true;}
bool SGroupFightMatchSingle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,teamName_);
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,star_);
PACKET_ENCODE(Int32,successCount_);
PACKET_ENCODE(Int32,todayCount_);
if(!publicPlayer_.encode(writer)){return false;}
return true;}
void SGroupFightMatchSingle::clear(){
teamName_.clear();
level_ = 0;
star_ = 0;
successCount_ = 0;
todayCount_ = 0;
publicPlayer_.clear();
}
bool SGroupFightMatch::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SGroupFightMatchSingle item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}firstTeam_.push_back(item);}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SGroupFightMatchSingle item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}secondTeam_.push_back(item);}}
PACKET_DECODE(Bool,isMatch_);
return true;}
bool SGroupFightMatch::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,firstTeam_.size());
for(vector<SGroupFightMatchSingle>::const_iterator vit=firstTeam_.begin();vit!=firstTeam_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(UVar32,secondTeam_.size());
for(vector<SGroupFightMatchSingle>::const_iterator vit=secondTeam_.begin();vit!=secondTeam_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(Bool,isMatch_);
return true;}
void SGroupFightMatch::clear(){
firstTeam_.clear();
secondTeam_.clear();
isMatch_ = 0;
}
bool SGroupFightMatchVec::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SGroupFightMatch item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}teams_.push_back(item);}}
return true;}
bool SGroupFightMatchVec::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,teams_.size());
for(vector<SGroupFightMatch>::const_iterator vit=teams_.begin();vit!=teams_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SGroupFightMatchVec::clear(){
teams_.clear();
}
bool SXianMoShenInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
PACKET_DECODE(Int32,floor_);
PACKET_DECODE(Int32,room_);
PACKET_DECODE(Int64,forceCD_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);monsters_[k] = v;}}
return true;}
bool SXianMoShenInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(Int32,floor_);
PACKET_ENCODE(Int32,room_);
PACKET_ENCODE(Int64,forceCD_);
PACKET_ENCODE(UVar32,monsters_.size());
for(map<int32_t, int32_t>::const_iterator it=monsters_.begin();it!=monsters_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SXianMoShenInfo::clear(){
copyCode_ = 0;
floor_ = 0;
room_ = 0;
forceCD_ = 0;
monsters_.clear();
}
bool SXianMoShenBossKill::decode(CBufferReader &reader) {
if(!belongId_.decode(reader)){return false;}
PACKET_DECODE(String,belongName_);
PACKET_DECODE(Int16,belongCareer_);
PACKET_DECODE(String,belongGuildName_);
PACKET_DECODE(Int32,belongForce_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool SXianMoShenBossKill::encode(CBufferWriter &writer) const {
if(!belongId_.encode(writer)){return false;}
PACKET_ENCODE(String,belongName_);
PACKET_ENCODE(Int16,belongCareer_);
PACKET_ENCODE(String,belongGuildName_);
PACKET_ENCODE(Int32,belongForce_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SXianMoShenBossKill::clear(){
belongId_.clear();
belongName_.clear();
belongCareer_ = 0;
belongGuildName_.clear();
belongForce_ = 0;
rewards_.clear();
}
bool SXianMoShenBossSkillBooks::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);skillBooks_[k] = v;}}
PACKET_DECODE(Int32,energy_);
return true;}
bool SXianMoShenBossSkillBooks::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,skillBooks_.size());
for(map<int32_t, int32_t>::const_iterator it=skillBooks_.begin();it!=skillBooks_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,energy_);
return true;}
void SXianMoShenBossSkillBooks::clear(){
skillBooks_.clear();
energy_ = 0;
}
bool SCompleteXianMoShen::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool SCompleteXianMoShen::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompleteXianMoShen::clear(){
rewards_.clear();
}
bool SXianMoShenContinuousKill::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int16,career_);
PACKET_DECODE(Int16,killNum_);
return true;}
bool SXianMoShenContinuousKill::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int16,career_);
PACKET_ENCODE(Int16,killNum_);
return true;}
void SXianMoShenContinuousKill::clear(){
entityId_.clear();
name_.clear();
career_ = 0;
killNum_ = 0;
}
bool SXianMoShenKillPlayer::decode(CBufferReader &reader) {
if(!fromPlayerId_.decode(reader)){return false;}
PACKET_DECODE(String,fromPlayerName_);
if(!toPlayerId_.decode(reader)){return false;}
PACKET_DECODE(String,toPlayerName_);
PACKET_DECODE(Int32,skillBookNum_);
return true;}
bool SXianMoShenKillPlayer::encode(CBufferWriter &writer) const {
if(!fromPlayerId_.encode(writer)){return false;}
PACKET_ENCODE(String,fromPlayerName_);
if(!toPlayerId_.encode(writer)){return false;}
PACKET_ENCODE(String,toPlayerName_);
PACKET_ENCODE(Int32,skillBookNum_);
return true;}
void SXianMoShenKillPlayer::clear(){
fromPlayerId_.clear();
fromPlayerName_.clear();
toPlayerId_.clear();
toPlayerName_.clear();
skillBookNum_ = 0;
}
bool SXianMoShenBoss::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int64_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int64,v);bossRefresh_[k] = v;}}
return true;}
bool SXianMoShenBoss::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,bossRefresh_.size());
for(map<int32_t, int64_t>::const_iterator it=bossRefresh_.begin();it!=bossRefresh_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int64,it->second);}
return true;}
void SXianMoShenBoss::clear(){
bossRefresh_.clear();
}
bool SCompleteGridCopy::decode(CBufferReader &reader) {
if(!SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,floor_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
PACKET_DECODE(Int32,completeTime_);
return true;}
bool SCompleteGridCopy::encode(CBufferWriter &writer) const {
if(!SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,floor_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,completeTime_);
return true;}
void SCompleteGridCopy::clear(){
floor_ = 0;
rewards_.clear();
completeTime_ = 0;
}
bool SGridCopyInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,floor_);
return true;}
bool SGridCopyInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,floor_);
return true;}
void SGridCopyInfo::clear(){
floor_ = 0;
}
bool SPlayerWorshipArena::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,worshipCount_);
PACKET_DECODE(Int32,todayMoney_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){string k;int32_t v;PACKET_DECODE(String,k);PACKET_DECODE(Int32,v);worshipPlayer_[k] = v;}}
return true;}
bool SPlayerWorshipArena::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,worshipCount_);
PACKET_ENCODE(Int32,todayMoney_);
PACKET_ENCODE(UVar32,worshipPlayer_.size());
for(map<string, int32_t>::const_iterator it=worshipPlayer_.begin();it!=worshipPlayer_.end();++it){PACKET_ENCODE(String,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SPlayerWorshipArena::clear(){
worshipCount_ = 0;
todayMoney_ = 0;
worshipPlayer_.clear();
}
bool SUpdateWorshipArena::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(Int32,worshipCount_);
return true;}
bool SUpdateWorshipArena::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,worshipCount_);
return true;}
void SUpdateWorshipArena::clear(){
entityId_.clear();
worshipCount_ = 0;
}
bool SWorshipTodayMoney::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){string k;int32_t v;PACKET_DECODE(String,k);PACKET_DECODE(Int32,v);todayCount_[k] = v;}}
return true;}
bool SWorshipTodayMoney::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,todayCount_.size());
for(map<string, int32_t>::const_iterator it=todayCount_.begin();it!=todayCount_.end();++it){PACKET_ENCODE(String,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SWorshipTodayMoney::clear(){
todayCount_.clear();
}
bool SWorshipRankSingle::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,rank_);
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,careerLevel_);
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int64,combat_);
PACKET_DECODE(String,guildName_);
PACKET_DECODE(Int32,vipLevel_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);entityShow_[k] = v;}}
PACKET_DECODE(Int32,career_);
return true;}
bool SWorshipRankSingle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,rank_);
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,careerLevel_);
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(String,guildName_);
PACKET_ENCODE(Int32,vipLevel_);
PACKET_ENCODE(UVar32,entityShow_.size());
for(map<int16_t, int32_t>::const_iterator it=entityShow_.begin();it!=entityShow_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,career_);
return true;}
void SWorshipRankSingle::clear(){
rank_ = 0;
entityId_.clear();
name_.clear();
careerLevel_ = 0;
level_ = 0;
combat_ = 0;
guildName_.clear();
vipLevel_ = 0;
entityShow_.clear();
career_ = 0;
}
bool SWorshipRank::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SWorshipRankSingle v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}list_[k] = v;}}
return true;}
bool SWorshipRank::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(map<int32_t, SWorshipRankSingle>::const_iterator it=list_.begin();it!=list_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SWorshipRank::clear(){
list_.clear();
}
bool SFirstArenaMatchPlayer::decode(CBufferReader &reader) {
if(!playerId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int64,combat_);
PACKET_DECODE(Int32,score_);
PACKET_DECODE(Int16,career_);
return true;}
bool SFirstArenaMatchPlayer::encode(CBufferWriter &writer) const {
if(!playerId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(Int32,score_);
PACKET_ENCODE(Int16,career_);
return true;}
void SFirstArenaMatchPlayer::clear(){
playerId_.clear();
name_.clear();
combat_ = 0;
score_ = 0;
career_ = 0;
}
bool SFirstArenaMatch::decode(CBufferReader &reader) {
if(!aPlayer_.decode(reader)){return false;}
if(!bPlayer_.decode(reader)){return false;}
return true;}
bool SFirstArenaMatch::encode(CBufferWriter &writer) const {
if(!aPlayer_.encode(writer)){return false;}
if(!bPlayer_.encode(writer)){return false;}
return true;}
void SFirstArenaMatch::clear(){
aPlayer_.clear();
bPlayer_.clear();
}
bool SFirstArenaResult::decode(CBufferReader &reader) {
if(!msgs::SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,result_);
PACKET_DECODE(Int32,addScore_);
PACKET_DECODE(Int32,score_);
PACKET_DECODE(Int32,rank_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
PACKET_DECODE(Int32,failCount_);
PACKET_DECODE(Int32,successCount_);
return true;}
bool SFirstArenaResult::encode(CBufferWriter &writer) const {
if(!msgs::SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,result_);
PACKET_ENCODE(Int32,addScore_);
PACKET_ENCODE(Int32,score_);
PACKET_ENCODE(Int32,rank_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,failCount_);
PACKET_ENCODE(Int32,successCount_);
return true;}
void SFirstArenaResult::clear(){
result_ = 0;
addScore_ = 0;
score_ = 0;
rank_ = 0;
rewards_.clear();
failCount_ = 0;
successCount_ = 0;
}
bool SFirstArenaFinalPlayer::decode(CBufferReader &reader) {
if(!playerId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int64,combat_);
PACKET_DECODE(Int32,score_);
PACKET_DECODE(Int32,layer_);
PACKET_DECODE(Bool,canWatch_);
PACKET_DECODE(Int16,career_);
PACKET_DECODE(Int32,bangType_);
return true;}
bool SFirstArenaFinalPlayer::encode(CBufferWriter &writer) const {
if(!playerId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(Int32,score_);
PACKET_ENCODE(Int32,layer_);
PACKET_ENCODE(Bool,canWatch_);
PACKET_ENCODE(Int16,career_);
PACKET_ENCODE(Int32,bangType_);
return true;}
void SFirstArenaFinalPlayer::clear(){
playerId_.clear();
name_.clear();
combat_ = 0;
score_ = 0;
layer_ = 0;
canWatch_ = 0;
career_ = 0;
bangType_ = 0;
}
bool SFirstArenaFinalList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SFirstArenaFinalPlayer item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
PACKET_DECODE(Int32,layer_);
PACKET_DECODE(Int32,status_);
PACKET_DECODE(Int64,endDt_);
PACKET_DECODE(Int32,bangType_);
return true;}
bool SFirstArenaFinalList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<SFirstArenaFinalPlayer>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(Int32,layer_);
PACKET_ENCODE(Int32,status_);
PACKET_ENCODE(Int64,endDt_);
PACKET_ENCODE(Int32,bangType_);
return true;}
void SFirstArenaFinalList::clear(){
list_.clear();
layer_ = 0;
status_ = 0;
endDt_ = 0;
bangType_ = 0;
}
bool SFirstArenaFinalUpdate::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,layer_);
PACKET_DECODE(Int32,status_);
PACKET_DECODE(Int64,endDt_);
PACKET_DECODE(Int32,bangType_);
return true;}
bool SFirstArenaFinalUpdate::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,layer_);
PACKET_ENCODE(Int32,status_);
PACKET_ENCODE(Int64,endDt_);
PACKET_ENCODE(Int32,bangType_);
return true;}
void SFirstArenaFinalUpdate::clear(){
layer_ = 0;
status_ = 0;
endDt_ = 0;
bangType_ = 0;
}
bool SFirstArenaRankList::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,rankType_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);dbs::TFirstArenaRank item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
PACKET_DECODE(Int32,myScore_);
PACKET_DECODE(Int32,myRank_);
return true;}
bool SFirstArenaRankList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,rankType_);
PACKET_ENCODE(UVar32,list_.size());
for(vector<dbs::TFirstArenaRank>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(Int32,myScore_);
PACKET_ENCODE(Int32,myRank_);
return true;}
void SFirstArenaRankList::clear(){
rankType_ = 0;
list_.clear();
myScore_ = 0;
myRank_ = 0;
}
bool SBudoBossRank::decode(CBufferReader &reader) {
if(!playerId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int64,hurt_);
PACKET_DECODE(Int32,rank_);
return true;}
bool SBudoBossRank::encode(CBufferWriter &writer) const {
if(!playerId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int64,hurt_);
PACKET_ENCODE(Int32,rank_);
return true;}
void SBudoBossRank::clear(){
playerId_.clear();
name_.clear();
hurt_ = 0;
rank_ = 0;
}
bool SBudoBossRankList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SBudoBossRank item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool SBudoBossRankList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<SBudoBossRank>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SBudoBossRankList::clear(){
list_.clear();
}
bool SCompleteBudoBoss::decode(CBufferReader &reader) {
if(!msgs::SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,myRank_);
PACKET_DECODE(Int64,myHurt_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
if(!ranks_.decode(reader)){return false;}
return true;}
bool SCompleteBudoBoss::encode(CBufferWriter &writer) const {
if(!msgs::SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,myRank_);
PACKET_ENCODE(Int64,myHurt_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
if(!ranks_.encode(writer)){return false;}
return true;}
void SCompleteBudoBoss::clear(){
myRank_ = 0;
myHurt_ = 0;
rewards_.clear();
ranks_.clear();
}
bool SBudoBoss::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,bossCode_);
PACKET_DECODE(Int64,life_);
PACKET_DECODE(Int16,career_);
PACKET_DECODE(String,name_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);entityShow_[k] = v;}}
return true;}
bool SBudoBoss::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,bossCode_);
PACKET_ENCODE(Int64,life_);
PACKET_ENCODE(Int16,career_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(UVar32,entityShow_.size());
for(map<int32_t, int32_t>::const_iterator it=entityShow_.begin();it!=entityShow_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SBudoBoss::clear(){
bossCode_ = 0;
life_ = 0;
career_ = 0;
name_.clear();
entityShow_.clear();
}
bool SBudoBossList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SBudoBoss item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool SBudoBossList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<SBudoBoss>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SBudoBossList::clear(){
list_.clear();
}
bool SFirstArenaBet::decode(CBufferReader &reader) {
if(!dbs::TFirstArenaBet::decode(reader)){return false;}
PACKET_DECODE(Int32,aBetCount_);
PACKET_DECODE(Int32,bBetCount_);
return true;}
bool SFirstArenaBet::encode(CBufferWriter &writer) const {
if(!dbs::TFirstArenaBet::encode(writer)){return false;}
PACKET_ENCODE(Int32,aBetCount_);
PACKET_ENCODE(Int32,bBetCount_);
return true;}
void SFirstArenaBet::clear(){
aBetCount_ = 0;
bBetCount_ = 0;
}
bool SFirstArenaBetList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SFirstArenaBet item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool SFirstArenaBetList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<SFirstArenaBet>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SFirstArenaBetList::clear(){
list_.clear();
}
bool SFirstArenaBetInfo::decode(CBufferReader &reader) {
if(!aPlayerId_.decode(reader)){return false;}
if(!bPlayerId_.decode(reader)){return false;}
PACKET_DECODE(String,aName_);
PACKET_DECODE(String,bName_);
PACKET_DECODE(Int32,aScore_);
PACKET_DECODE(Int32,bScore_);
PACKET_DECODE(Bool,hasBet_);
return true;}
bool SFirstArenaBetInfo::encode(CBufferWriter &writer) const {
if(!aPlayerId_.encode(writer)){return false;}
if(!bPlayerId_.encode(writer)){return false;}
PACKET_ENCODE(String,aName_);
PACKET_ENCODE(String,bName_);
PACKET_ENCODE(Int32,aScore_);
PACKET_ENCODE(Int32,bScore_);
PACKET_ENCODE(Bool,hasBet_);
return true;}
void SFirstArenaBetInfo::clear(){
aPlayerId_.clear();
bPlayerId_.clear();
aName_.clear();
bName_.clear();
aScore_ = 0;
bScore_ = 0;
hasBet_ = 0;
}
bool SFirstArenaFinalHis::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,result_);
PACKET_DECODE(Int32,num_);
return true;}
bool SFirstArenaFinalHis::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,result_);
PACKET_ENCODE(Int32,num_);
return true;}
void SFirstArenaFinalHis::clear(){
result_ = 0;
num_ = 0;
}
bool SFirstArenaFinalHisList::decode(CBufferReader &reader) {
PACKET_DECODE(String,aName_);
PACKET_DECODE(String,bName_);
PACKET_DECODE(Int32,aCareer_);
PACKET_DECODE(Int32,bCareer_);
PACKET_DECODE(Int32,result_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SFirstArenaFinalHis item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool SFirstArenaFinalHisList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,aName_);
PACKET_ENCODE(String,bName_);
PACKET_ENCODE(Int32,aCareer_);
PACKET_ENCODE(Int32,bCareer_);
PACKET_ENCODE(Int32,result_);
PACKET_ENCODE(UVar32,list_.size());
for(vector<SFirstArenaFinalHis>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SFirstArenaFinalHisList::clear(){
aName_.clear();
bName_.clear();
aCareer_ = 0;
bCareer_ = 0;
result_ = 0;
list_.clear();
}
bool SFirstArenaFinalWaiting::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,round_);
PACKET_DECODE(Int32,num_);
PACKET_DECODE(Int64,endDt_);
return true;}
bool SFirstArenaFinalWaiting::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,round_);
PACKET_ENCODE(Int32,num_);
PACKET_ENCODE(Int64,endDt_);
return true;}
void SFirstArenaFinalWaiting::clear(){
round_ = 0;
num_ = 0;
endDt_ = 0;
}
bool SYaoChong::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,idx_);
PACKET_DECODE(Int32,id_);
PACKET_DECODE(Int32,loseNum_);
PACKET_DECODE(Int32,timeNum_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);items_[k] = v;}}
PACKET_DECODE(Int64,dt_);
return true;}
bool SYaoChong::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,idx_);
PACKET_ENCODE(Int32,id_);
PACKET_ENCODE(Int32,loseNum_);
PACKET_ENCODE(Int32,timeNum_);
PACKET_ENCODE(UVar32,items_.size());
for(map<int32_t, int32_t>::const_iterator it=items_.begin();it!=items_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int64,dt_);
return true;}
void SYaoChong::clear(){
idx_ = 0;
id_ = 0;
loseNum_ = 0;
timeNum_ = 0;
items_.clear();
dt_ = 0;
}
bool SYaoChongRecord::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,id_);
PACKET_DECODE(String,name_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);items_[k] = v;}}
return true;}
bool SYaoChongRecord::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,id_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(UVar32,items_.size());
for(map<int32_t, int32_t>::const_iterator it=items_.begin();it!=items_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SYaoChongRecord::clear(){
id_ = 0;
name_.clear();
items_.clear();
}
bool SYaoChongInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,extraNum_);
PACKET_DECODE(Int32,forage_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SYaoChong item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}yaochongLst_.push_back(item);}}
return true;}
bool SYaoChongInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,extraNum_);
PACKET_ENCODE(Int32,forage_);
PACKET_ENCODE(UVar32,yaochongLst_.size());
for(vector<SYaoChong>::const_iterator vit=yaochongLst_.begin();vit!=yaochongLst_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SYaoChongInfo::clear(){
extraNum_ = 0;
forage_ = 0;
yaochongLst_.clear();
}
bool SYaoChongGrabInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,grabNum_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SYaoChongRecord item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}records_.push_back(item);}}
return true;}
bool SYaoChongGrabInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,grabNum_);
PACKET_ENCODE(UVar32,records_.size());
for(vector<SYaoChongRecord>::const_iterator vit=records_.begin();vit!=records_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SYaoChongGrabInfo::clear(){
grabNum_ = 0;
records_.clear();
}
bool SYaoChongUpdate::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SYaoChong item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}ups_.push_back(item);}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);dels_.push_back(item);}}
return true;}
bool SYaoChongUpdate::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,ups_.size());
for(vector<SYaoChong>::const_iterator vit=ups_.begin();vit!=ups_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(UVar32,dels_.size());
for(vector<int32_t>::const_iterator vit=dels_.begin();vit!=dels_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SYaoChongUpdate::clear(){
ups_.clear();
dels_.clear();
}
bool SYaoChongPlayer::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,num_);
PACKET_DECODE(Int32,maxNum_);
return true;}
bool SYaoChongPlayer::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,num_);
PACKET_ENCODE(Int32,maxNum_);
return true;}
void SYaoChongPlayer::clear(){
entityId_.clear();
name_.clear();
num_ = 0;
maxNum_ = 0;
}
bool SYaoChongPlayerList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SYaoChongPlayer item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool SYaoChongPlayerList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<SYaoChongPlayer>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SYaoChongPlayerList::clear(){
list_.clear();
}
bool SServerInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,nowDt_);
PACKET_DECODE(Int64,openDt_);
PACKET_DECODE(Int64,preOpenDt_);
PACKET_DECODE(Int32,mergeCount_);
PACKET_DECODE(Int64,mergeDt_);
PACKET_DECODE(Bool,switchGate_);
PACKET_DECODE(Int32,worldLevel_);
PACKET_DECODE(Int32,offsetHour_);
PACKET_DECODE(Int32,antiAddiction_);
PACKET_DECODE(Int32,rechargeId_);
PACKET_DECODE(String,serverConfig_);
PACKET_DECODE(Int64,crossAOpenDt_);
PACKET_DECODE(Int64,crossBOpenDt_);
PACKET_DECODE(Int64,crossCOpenDt_);
PACKET_DECODE(Int64,crossDOpenDt_);
PACKET_DECODE(Int32,payNum_);
return true;}
bool SServerInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,nowDt_);
PACKET_ENCODE(Int64,openDt_);
PACKET_ENCODE(Int64,preOpenDt_);
PACKET_ENCODE(Int32,mergeCount_);
PACKET_ENCODE(Int64,mergeDt_);
PACKET_ENCODE(Bool,switchGate_);
PACKET_ENCODE(Int32,worldLevel_);
PACKET_ENCODE(Int32,offsetHour_);
PACKET_ENCODE(Int32,antiAddiction_);
PACKET_ENCODE(Int32,rechargeId_);
PACKET_ENCODE(String,serverConfig_);
PACKET_ENCODE(Int64,crossAOpenDt_);
PACKET_ENCODE(Int64,crossBOpenDt_);
PACKET_ENCODE(Int64,crossCOpenDt_);
PACKET_ENCODE(Int64,crossDOpenDt_);
PACKET_ENCODE(Int32,payNum_);
return true;}
void SServerInfo::clear(){
nowDt_ = 0;
openDt_ = 0;
preOpenDt_ = 0;
mergeCount_ = 0;
mergeDt_ = 0;
switchGate_ = 0;
worldLevel_ = 0;
offsetHour_ = 0;
antiAddiction_ = 0;
rechargeId_ = 0;
serverConfig_.clear();
crossAOpenDt_ = 0;
crossBOpenDt_ = 0;
crossCOpenDt_ = 0;
crossDOpenDt_ = 0;
payNum_ = 0;
}
bool SErrorMessage::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,errorCode_);
PACKET_DECODE(String,errorWhat_);
return true;}
bool SErrorMessage::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,errorCode_);
PACKET_ENCODE(String,errorWhat_);
return true;}
void SErrorMessage::clear(){
errorCode_ = 0;
errorWhat_.clear();
}
bool SWorldLevel::decode(CBufferReader &reader) {
PACKET_DECODE(Int16,worldLevel_);
PACKET_DECODE(Int64,updateDt_);
return true;}
bool SWorldLevel::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int16,worldLevel_);
PACKET_ENCODE(Int64,updateDt_);
return true;}
void SWorldLevel::clear(){
worldLevel_ = 0;
updateDt_ = 0;
}
bool SServerOpenInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,openDt_);
PACKET_DECODE(Int64,preOpenDt_);
PACKET_DECODE(Int32,mergeCount_);
PACKET_DECODE(Int64,mergeDt_);
PACKET_DECODE(Bool,switchGate_);
return true;}
bool SServerOpenInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,openDt_);
PACKET_ENCODE(Int64,preOpenDt_);
PACKET_ENCODE(Int32,mergeCount_);
PACKET_ENCODE(Int64,mergeDt_);
PACKET_ENCODE(Bool,switchGate_);
return true;}
void SServerOpenInfo::clear(){
openDt_ = 0;
preOpenDt_ = 0;
mergeCount_ = 0;
mergeDt_ = 0;
switchGate_ = 0;
}
bool SServerCrossOpenInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,crossAOpenDt_);
PACKET_DECODE(Int64,crossBOpenDt_);
PACKET_DECODE(Int64,crossCOpenDt_);
PACKET_DECODE(Int64,crossDOpenDt_);
PACKET_DECODE(Int16,aServerId_);
PACKET_DECODE(Int16,bServerId_);
PACKET_DECODE(Int16,cServerId_);
PACKET_DECODE(Int16,dServerId_);
return true;}
bool SServerCrossOpenInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,crossAOpenDt_);
PACKET_ENCODE(Int64,crossBOpenDt_);
PACKET_ENCODE(Int64,crossCOpenDt_);
PACKET_ENCODE(Int64,crossDOpenDt_);
PACKET_ENCODE(Int16,aServerId_);
PACKET_ENCODE(Int16,bServerId_);
PACKET_ENCODE(Int16,cServerId_);
PACKET_ENCODE(Int16,dServerId_);
return true;}
void SServerCrossOpenInfo::clear(){
crossAOpenDt_ = 0;
crossBOpenDt_ = 0;
crossCOpenDt_ = 0;
crossDOpenDt_ = 0;
aServerId_ = 0;
bServerId_ = 0;
cServerId_ = 0;
dServerId_ = 0;
}
bool SPublicCounter::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);map_[k] = v;}}
return true;}
bool SPublicCounter::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(UVar32,map_.size());
for(map<int32_t, int32_t>::const_iterator it=map_.begin();it!=map_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SPublicCounter::clear(){
type_ = 0;
map_.clear();
}
bool SInterestedEntity::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(Int64,lift_);
PACKET_DECODE(Int64,inPower_);
if(!pos_.decode(reader)){return false;}
return true;}
bool SInterestedEntity::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(Int64,lift_);
PACKET_ENCODE(Int64,inPower_);
if(!pos_.encode(writer)){return false;}
return true;}
void SInterestedEntity::clear(){
entityId_.clear();
lift_ = 0;
inPower_ = 0;
pos_.clear();
}
bool SUpdateInterestedEntity::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SInterestedEntity item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}entities_.push_back(item);}}
return true;}
bool SUpdateInterestedEntity::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,entities_.size());
for(vector<SInterestedEntity>::const_iterator vit=entities_.begin();vit!=entities_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SUpdateInterestedEntity::clear(){
entities_.clear();
}
bool SRechargePersonNum::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,num_);
return true;}
bool SRechargePersonNum::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,num_);
return true;}
void SRechargePersonNum::clear(){
num_ = 0;
}
bool SMonsterAroundInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Bool,autoBook_);
PACKET_DECODE(Bool,isOpen_);
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,life_);
PACKET_DECODE(Int32,bookHour_);
PACKET_DECODE(Int32,getReward_);
return true;}
bool SMonsterAroundInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Bool,autoBook_);
PACKET_ENCODE(Bool,isOpen_);
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,life_);
PACKET_ENCODE(Int32,bookHour_);
PACKET_ENCODE(Int32,getReward_);
return true;}
void SMonsterAroundInfo::clear(){
autoBook_ = 0;
isOpen_ = 0;
level_ = 0;
life_ = 0;
bookHour_ = 0;
getReward_ = 0;
}
bool SMonsterAroundRecord::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(Int32,career_);
PACKET_DECODE(Int32,itemCode_);
PACKET_DECODE(Int32,itemNum_);
PACKET_DECODE(String,name_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);ornaments_[k] = v;}}
return true;}
bool SMonsterAroundRecord::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,career_);
PACKET_ENCODE(Int32,itemCode_);
PACKET_ENCODE(Int32,itemNum_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(UVar32,ornaments_.size());
for(map<int16_t, int32_t>::const_iterator it=ornaments_.begin();it!=ornaments_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SMonsterAroundRecord::clear(){
entityId_.clear();
career_ = 0;
itemCode_ = 0;
itemNum_ = 0;
name_.clear();
ornaments_.clear();
}
bool SMonsterAroundRecords::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SMonsterAroundRecord item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}records_.push_back(item);}}
return true;}
bool SMonsterAroundRecords::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,records_.size());
for(vector<SMonsterAroundRecord>::const_iterator vit=records_.begin();vit!=records_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SMonsterAroundRecords::clear(){
records_.clear();
}
bool SRoleLegendEquip::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);levelMap_[k] = v;}}
return true;}
bool SRoleLegendEquip::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,levelMap_.size());
for(map<int32_t, int32_t>::const_iterator it=levelMap_.begin();it!=levelMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SRoleLegendEquip::clear(){
levelMap_.clear();
}
bool SLegendEquip::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SRoleLegendEquip v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}advanceMap_[k] = v;}}
return true;}
bool SLegendEquip::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,advanceMap_.size());
for(map<int32_t, SRoleLegendEquip>::const_iterator it=advanceMap_.begin();it!=advanceMap_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SLegendEquip::clear(){
advanceMap_.clear();
}
bool SPlayerLoginData::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(UInt16,proxyId_);
PACKET_DECODE(UInt16,serverId_);
PACKET_DECODE(String,testStr_);
PACKET_DECODE(Int32,idCardStatus_);
return true;}
bool SPlayerLoginData::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(UInt16,proxyId_);
PACKET_ENCODE(UInt16,serverId_);
PACKET_ENCODE(String,testStr_);
PACKET_ENCODE(Int32,idCardStatus_);
return true;}
void SPlayerLoginData::clear(){
playerId_ = 0;
entityId_.clear();
proxyId_ = 0;
serverId_ = 0;
testStr_.clear();
idCardStatus_ = 0;
}
bool SPlayerRoleList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Msg* item;for(uint32_t vi=0;vi<vlen;++vi){item = MsgPool::Instance()->DecodeMsg(reader);roleList_.push_back(item);}}
return true;}
bool SPlayerRoleList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,roleList_.size());
for(vector<Msg*>::const_iterator vit=roleList_.begin();vit!=roleList_.end();++vit){if(!MsgPool::Instance()->EncodeMsg(writer, *vit)){return false;}}
return true;}
void SPlayerRoleList::clear(){
roleList_.clear();
}
bool SAddExp::decode(CBufferReader &reader) {
PACKET_DECODE(Int16,updateCode_);
PACKET_DECODE(Int64,exp_);
PACKET_DECODE(Int32,addon_);
return true;}
bool SAddExp::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int16,updateCode_);
PACKET_ENCODE(Int64,exp_);
PACKET_ENCODE(Int32,addon_);
return true;}
void SAddExp::clear(){
updateCode_ = 0;
exp_ = 0;
addon_ = 0;
}
bool SPlayerInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,loginDays_);
return true;}
bool SPlayerInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,loginDays_);
return true;}
void SPlayerInfo::clear(){
loginDays_ = 0;
}
bool SLevelUp::decode(CBufferReader &reader) {
PACKET_DECODE(Int16,level_);
PACKET_DECODE(Int64,exp_);
PACKET_DECODE(Int64,levelDt_);
return true;}
bool SLevelUp::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int16,level_);
PACKET_ENCODE(Int64,exp_);
PACKET_ENCODE(Int64,levelDt_);
return true;}
void SLevelUp::clear(){
level_ = 0;
exp_ = 0;
levelDt_ = 0;
}
bool SPlayerCombatData::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,combat_);
PACKET_DECODE(Int64,avatarCombat_);
return true;}
bool SPlayerCombatData::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(Int64,avatarCombat_);
return true;}
void SPlayerCombatData::clear(){
combat_ = 0;
avatarCombat_ = 0;
}
bool SPlayerCombatChange::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,combat_);
PACKET_DECODE(Int64,avatarCombat_);
return true;}
bool SPlayerCombatChange::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(Int64,avatarCombat_);
return true;}
void SPlayerCombatChange::clear(){
combat_ = 0;
avatarCombat_ = 0;
}
bool SRoleCombatData::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int64,combat_);
if(!fightAttr_.decode(reader)){return false;}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int64_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int64,v);copyAttr_[k] = v;}}
if(!fixAttr_.decode(reader)){return false;}
return true;}
bool SRoleCombatData::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int64,combat_);
if(!fightAttr_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,copyAttr_.size());
for(map<int16_t, int64_t>::const_iterator it=copyAttr_.begin();it!=copyAttr_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int64,it->second);}
if(!fixAttr_.encode(writer)){return false;}
return true;}
void SRoleCombatData::clear(){
roleId_ = 0;
combat_ = 0;
fightAttr_.clear();
copyAttr_.clear();
fixAttr_.clear();
}
bool SRoleCombatChange::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int64,combat_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int64_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int64,v);diffAttr_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int64_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int64,v);diffCopyAttr_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int64_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int64,v);diffFixAttr_[k] = v;}}
return true;}
bool SRoleCombatChange::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(UVar32,diffAttr_.size());
for(map<int16_t, int64_t>::const_iterator it=diffAttr_.begin();it!=diffAttr_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int64,it->second);}
PACKET_ENCODE(UVar32,diffCopyAttr_.size());
for(map<int16_t, int64_t>::const_iterator it=diffCopyAttr_.begin();it!=diffCopyAttr_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int64,it->second);}
PACKET_ENCODE(UVar32,diffFixAttr_.size());
for(map<int16_t, int64_t>::const_iterator it=diffFixAttr_.begin();it!=diffFixAttr_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int64,it->second);}
return true;}
void SRoleCombatChange::clear(){
roleId_ = 0;
combat_ = 0;
diffAttr_.clear();
diffCopyAttr_.clear();
diffFixAttr_.clear();
}
bool SPlayerDeath::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,deathType_);
PACKET_DECODE(Int32,reviveType_);
PACKET_DECODE(Int32,bossCode_);
if(!fromId_.decode(reader)){return false;}
PACKET_DECODE(String,fromName_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int64_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int64,item);reviveCd_.push_back(item);}}
PACKET_DECODE(Int32,freeRevive_);
return true;}
bool SPlayerDeath::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,deathType_);
PACKET_ENCODE(Int32,reviveType_);
PACKET_ENCODE(Int32,bossCode_);
if(!fromId_.encode(writer)){return false;}
PACKET_ENCODE(String,fromName_);
PACKET_ENCODE(UVar32,reviveCd_.size());
for(vector<int64_t>::const_iterator vit=reviveCd_.begin();vit!=reviveCd_.end();++vit){PACKET_ENCODE(Int64,*vit);}
PACKET_ENCODE(Int32,freeRevive_);
return true;}
void SPlayerDeath::clear(){
deathType_ = 0;
reviveType_ = 0;
bossCode_ = 0;
fromId_.clear();
fromName_.clear();
reviveCd_.clear();
freeRevive_ = 0;
}
bool SPlayerExpAddon::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,addon_);
PACKET_DECODE(Int64,endDt_);
return true;}
bool SPlayerExpAddon::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,addon_);
PACKET_ENCODE(Int64,endDt_);
return true;}
void SPlayerExpAddon::clear(){
addon_ = 0;
endDt_ = 0;
}
bool SPlayerRevive::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
if(!fromEntityId_.decode(reader)){return false;}
return true;}
bool SPlayerRevive::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
if(!fromEntityId_.encode(writer)){return false;}
return true;}
void SPlayerRevive::clear(){
type_ = 0;
fromEntityId_.clear();
}
bool SPlayerThreat::decode(CBufferReader &reader) {
PACKET_DECODE(String,name_);
PACKET_DECODE(Int64,value_);
PACKET_DECODE(Int64,hurt_);
return true;}
bool SPlayerThreat::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int64,value_);
PACKET_ENCODE(Int64,hurt_);
return true;}
void SPlayerThreat::clear(){
name_.clear();
value_ = 0;
hurt_ = 0;
}
bool SPlayerThreats::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SPlayerThreat item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}threats_.push_back(item);}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SPlayerThreat item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}belongHurt_.push_back(item);}}
return true;}
bool SPlayerThreats::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,threats_.size());
for(vector<SPlayerThreat>::const_iterator vit=threats_.begin();vit!=threats_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(UVar32,belongHurt_.size());
for(vector<SPlayerThreat>::const_iterator vit=belongHurt_.begin();vit!=belongHurt_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerThreats::clear(){
threats_.clear();
belongHurt_.clear();
}
bool SRoleShowInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int16,career_);
PACKET_DECODE(Int64,combat_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);dbs::TPlayerEquip item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}equips_.push_back(item);}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);dbs::TPlayerItem item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}equipItems_.push_back(item);}}
PACKET_DECODE(String,entityShows_);
PACKET_DECODE(String,entityAttrs_);
PACKET_DECODE(Int64,devilDeadline_);
PACKET_DECODE(Int64,angelDeadline_);
PACKET_DECODE(Int64,decHurtDeadline_);
return true;}
bool SRoleShowInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int16,career_);
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(UVar32,equips_.size());
for(vector<dbs::TPlayerEquip>::const_iterator vit=equips_.begin();vit!=equips_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(UVar32,equipItems_.size());
for(vector<dbs::TPlayerItem>::const_iterator vit=equipItems_.begin();vit!=equipItems_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(String,entityShows_);
PACKET_ENCODE(String,entityAttrs_);
PACKET_ENCODE(Int64,devilDeadline_);
PACKET_ENCODE(Int64,angelDeadline_);
PACKET_ENCODE(Int64,decHurtDeadline_);
return true;}
void SRoleShowInfo::clear(){
roleId_ = 0;
career_ = 0;
combat_ = 0;
equips_.clear();
equipItems_.clear();
entityShows_.clear();
entityAttrs_.clear();
devilDeadline_ = 0;
angelDeadline_ = 0;
decHurtDeadline_ = 0;
}
bool SPlayerShowInfo::decode(CBufferReader &reader) {
if(!publicPlayer_.decode(reader)){return false;}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SRoleShowInfo v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}roleMap_[k] = v;}}
return true;}
bool SPlayerShowInfo::encode(CBufferWriter &writer) const {
if(!publicPlayer_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,roleMap_.size());
for(map<int32_t, SRoleShowInfo>::const_iterator it=roleMap_.begin();it!=roleMap_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SPlayerShowInfo::clear(){
publicPlayer_.clear();
roleMap_.clear();
}
bool SPlayerReviveInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,useFreeCount_);
return true;}
bool SPlayerReviveInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,useFreeCount_);
return true;}
void SPlayerReviveInfo::clear(){
useFreeCount_ = 0;
}
bool SPlayerFighting::decode(CBufferReader &reader) {
PACKET_DECODE(Bool,isFighting_);
PACKET_DECODE(Bool,isPvpFighting_);
return true;}
bool SPlayerFighting::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Bool,isFighting_);
PACKET_ENCODE(Bool,isPvpFighting_);
return true;}
void SPlayerFighting::clear(){
isFighting_ = 0;
isPvpFighting_ = 0;
}
bool SPlayerOpenServerGiftBag::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);giftBags_[k] = v;}}
return true;}
bool SPlayerOpenServerGiftBag::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,giftBags_.size());
for(map<int32_t, bool>::const_iterator it=giftBags_.begin();it!=giftBags_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
return true;}
void SPlayerOpenServerGiftBag::clear(){
giftBags_.clear();
}
bool SAddictionUpdate::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,totalSec_);
return true;}
bool SAddictionUpdate::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,totalSec_);
return true;}
void SAddictionUpdate::clear(){
totalSec_ = 0;
}
bool SRoleFightInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int16,career_);
PACKET_DECODE(Int64,combat_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);skills_.push_back(item);}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);buffs_.push_back(item);}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);entityShows_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int64_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int64,v);entityAttrs_[k] = v;}}
return true;}
bool SRoleFightInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int16,career_);
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(UVar32,skills_.size());
for(vector<int32_t>::const_iterator vit=skills_.begin();vit!=skills_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(UVar32,buffs_.size());
for(vector<int32_t>::const_iterator vit=buffs_.begin();vit!=buffs_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(UVar32,entityShows_.size());
for(map<int16_t, int32_t>::const_iterator it=entityShows_.begin();it!=entityShows_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,entityAttrs_.size());
for(map<int16_t, int64_t>::const_iterator it=entityAttrs_.begin();it!=entityAttrs_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int64,it->second);}
return true;}
void SRoleFightInfo::clear(){
roleId_ = 0;
career_ = 0;
combat_ = 0;
skills_.clear();
buffs_.clear();
entityShows_.clear();
entityAttrs_.clear();
}
bool SPlayerFightInfo::decode(CBufferReader &reader) {
if(!publicPlayer_.decode(reader)){return false;}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SRoleFightInfo v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}roleMap_[k] = v;}}
return true;}
bool SPlayerFightInfo::encode(CBufferWriter &writer) const {
if(!publicPlayer_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,roleMap_.size());
for(map<int32_t, SRoleFightInfo>::const_iterator it=roleMap_.begin();it!=roleMap_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SPlayerFightInfo::clear(){
publicPlayer_.clear();
roleMap_.clear();
}
bool SPlayerLimitedGift::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);buyTimes_[k] = v;}}
return true;}
bool SPlayerLimitedGift::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,buyTimes_.size());
for(map<int32_t, int32_t>::const_iterator it=buyTimes_.begin();it!=buyTimes_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SPlayerLimitedGift::clear(){
buyTimes_.clear();
}
bool SCardGroup::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);activeNum_[k] = v;}}
return true;}
bool SCardGroup::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,activeNum_.size());
for(map<int32_t, int32_t>::const_iterator it=activeNum_.begin();it!=activeNum_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCardGroup::clear(){
activeNum_.clear();
}
bool SDevilAngelRoleDate::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int64_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int64,v);roleDate_[k] = v;}}
return true;}
bool SDevilAngelRoleDate::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,roleDate_.size());
for(map<int32_t, int64_t>::const_iterator it=roleDate_.begin();it!=roleDate_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int64,it->second);}
return true;}
void SDevilAngelRoleDate::clear(){
roleDate_.clear();
}
bool SDevilAngelDate::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SDevilAngelRoleDate v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}devilAngelDate_[k] = v;}}
return true;}
bool SDevilAngelDate::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,devilAngelDate_.size());
for(map<int32_t, SDevilAngelRoleDate>::const_iterator it=devilAngelDate_.begin();it!=devilAngelDate_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SDevilAngelDate::clear(){
devilAngelDate_.clear();
}
bool SPlayerShareInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,count_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);getIndex_.push_back(item);}}
PACKET_DECODE(Int64,nextShareDt_);
return true;}
bool SPlayerShareInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,count_);
PACKET_ENCODE(UVar32,getIndex_.size());
for(vector<int32_t>::const_iterator vit=getIndex_.begin();vit!=getIndex_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(Int64,nextShareDt_);
return true;}
void SPlayerShareInfo::clear(){
count_ = 0;
getIndex_.clear();
nextShareDt_ = 0;
}
bool SPlayerWorshipData::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,count_);
PACKET_DECODE(Int64,dt_);
return true;}
bool SPlayerWorshipData::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,count_);
PACKET_ENCODE(Int64,dt_);
return true;}
void SPlayerWorshipData::clear(){
count_ = 0;
dt_ = 0;
}
bool SPlayerFirstGroupBuy::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,personNum_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);rewards_.push_back(item);}}
return true;}
bool SPlayerFirstGroupBuy::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,personNum_);
PACKET_ENCODE(UVar32,rewards_.size());
for(vector<int32_t>::const_iterator vit=rewards_.begin();vit!=rewards_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SPlayerFirstGroupBuy::clear(){
personNum_ = 0;
rewards_.clear();
}
bool SPlayerIDCardStatus::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,status_);
return true;}
bool SPlayerIDCardStatus::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,status_);
return true;}
void SPlayerIDCardStatus::clear(){
status_ = 0;
}
bool SPlayerOnlinePoint::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);onlinePoints_[k] = v;}}
return true;}
bool SPlayerOnlinePoint::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,onlinePoints_.size());
for(map<int32_t, int32_t>::const_iterator it=onlinePoints_.begin();it!=onlinePoints_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SPlayerOnlinePoint::clear(){
onlinePoints_.clear();
}
bool SPlayerBossBelong::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);bossBlongTimes_[k] = v;}}
return true;}
bool SPlayerBossBelong::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,bossBlongTimes_.size());
for(map<int32_t, int32_t>::const_iterator it=bossBlongTimes_.begin();it!=bossBlongTimes_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SPlayerBossBelong::clear(){
bossBlongTimes_.clear();
}
bool SPlayerUpdateBossBelong::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,num_);
return true;}
bool SPlayerUpdateBossBelong::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,num_);
return true;}
void SPlayerUpdateBossBelong::clear(){
type_ = 0;
num_ = 0;
}
bool SPlayerOfficialInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Bool,isCross_);
PACKET_DECODE(Int32,officialLevel_);
PACKET_DECODE(Int32,maxOfficialLevel_);
PACKET_DECODE(Int64,endTime_);
PACKET_DECODE(Bool,isGotReward_);
return true;}
bool SPlayerOfficialInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Bool,isCross_);
PACKET_ENCODE(Int32,officialLevel_);
PACKET_ENCODE(Int32,maxOfficialLevel_);
PACKET_ENCODE(Int64,endTime_);
PACKET_ENCODE(Bool,isGotReward_);
return true;}
void SPlayerOfficialInfo::clear(){
isCross_ = 0;
officialLevel_ = 0;
maxOfficialLevel_ = 0;
endTime_ = 0;
isGotReward_ = 0;
}
bool SPlayerMarryInvest::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,fromPlayerId_);
PACKET_DECODE(Int32,toPlayerId_);
PACKET_DECODE(Bool,gotGetReward_);
PACKET_DECODE(Bool,gotSendReward_);
PACKET_DECODE(Int64,getEndTime_);
PACKET_DECODE(Int64,sendEndTime_);
PACKET_DECODE(Int32,dayRequestNum_);
return true;}
bool SPlayerMarryInvest::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,fromPlayerId_);
PACKET_ENCODE(Int32,toPlayerId_);
PACKET_ENCODE(Bool,gotGetReward_);
PACKET_ENCODE(Bool,gotSendReward_);
PACKET_ENCODE(Int64,getEndTime_);
PACKET_ENCODE(Int64,sendEndTime_);
PACKET_ENCODE(Int32,dayRequestNum_);
return true;}
void SPlayerMarryInvest::clear(){
fromPlayerId_ = 0;
toPlayerId_ = 0;
gotGetReward_ = 0;
gotSendReward_ = 0;
getEndTime_ = 0;
sendEndTime_ = 0;
dayRequestNum_ = 0;
}
bool SShareCopyExp::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);todayShareMap_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);totalShareMap_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);vipShareMap_[k] = v;}}
PACKET_DECODE(Bool,isVipShare_);
return true;}
bool SShareCopyExp::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,todayShareMap_.size());
for(map<int32_t, int32_t>::const_iterator it=todayShareMap_.begin();it!=todayShareMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,totalShareMap_.size());
for(map<int32_t, int32_t>::const_iterator it=totalShareMap_.begin();it!=totalShareMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,vipShareMap_.size());
for(map<int32_t, int32_t>::const_iterator it=vipShareMap_.begin();it!=vipShareMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Bool,isVipShare_);
return true;}
void SShareCopyExp::clear(){
todayShareMap_.clear();
totalShareMap_.clear();
vipShareMap_.clear();
isVipShare_ = 0;
}
bool SPlayerUpdateOrnaments::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);ornaments_[k] = v;}}
return true;}
bool SPlayerUpdateOrnaments::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,ornaments_.size());
for(map<int16_t, int32_t>::const_iterator it=ornaments_.begin();it!=ornaments_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SPlayerUpdateOrnaments::clear(){
ornaments_.clear();
}
bool SCenterGroupFightSingle::decode(CBufferReader &reader) {
if(!publicPlayer_.decode(reader)){return false;}
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,star_);
PACKET_DECODE(Int32,successCount_);
PACKET_DECODE(Int32,todayCount_);
PACKET_DECODE(Int32,lastWeekLevel_);
PACKET_DECODE(Bool,weekReward_);
PACKET_DECODE(Bool,weekTeamReward_);
PACKET_DECODE(Bool,weekRankReward_);
PACKET_DECODE(Bool,weekTeamRankReward_);
return true;}
bool SCenterGroupFightSingle::encode(CBufferWriter &writer) const {
if(!publicPlayer_.encode(writer)){return false;}
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,star_);
PACKET_ENCODE(Int32,successCount_);
PACKET_ENCODE(Int32,todayCount_);
PACKET_ENCODE(Int32,lastWeekLevel_);
PACKET_ENCODE(Bool,weekReward_);
PACKET_ENCODE(Bool,weekTeamReward_);
PACKET_ENCODE(Bool,weekRankReward_);
PACKET_ENCODE(Bool,weekTeamRankReward_);
return true;}
void SCenterGroupFightSingle::clear(){
publicPlayer_.clear();
level_ = 0;
star_ = 0;
successCount_ = 0;
todayCount_ = 0;
lastWeekLevel_ = 0;
weekReward_ = 0;
weekTeamReward_ = 0;
weekRankReward_ = 0;
weekTeamRankReward_ = 0;
}
bool SCenterGroupFight::decode(CBufferReader &reader) {
PACKET_DECODE(String,teamName_);
if(!captain_.decode(reader)){return false;}
PACKET_DECODE(Int32,teamLevel_);
PACKET_DECODE(Int32,teamStar_);
PACKET_DECODE(Int32,lastWeekTeamLevel_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SCenterGroupFightSingle item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}partner_.push_back(item);}}
PACKET_DECODE(Int64,outDate_);
return true;}
bool SCenterGroupFight::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,teamName_);
if(!captain_.encode(writer)){return false;}
PACKET_ENCODE(Int32,teamLevel_);
PACKET_ENCODE(Int32,teamStar_);
PACKET_ENCODE(Int32,lastWeekTeamLevel_);
PACKET_ENCODE(UVar32,partner_.size());
for(vector<SCenterGroupFightSingle>::const_iterator vit=partner_.begin();vit!=partner_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(Int64,outDate_);
return true;}
void SCenterGroupFight::clear(){
teamName_.clear();
captain_.clear();
teamLevel_ = 0;
teamStar_ = 0;
lastWeekTeamLevel_ = 0;
partner_.clear();
outDate_ = 0;
}
bool SBoss::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,bossId_);
PACKET_DECODE(Int32,copyCode_);
PACKET_DECODE(Int64,life_);
PACKET_DECODE(Int64,maxLife_);
PACKET_DECODE(Int64,refreshTime_);
PACKET_DECODE(String,lastKillName_);
PACKET_DECODE(Int64,lastKillTime_);
PACKET_DECODE(Int32,line_);
PACKET_DECODE(Int32,playerNum_);
return true;}
bool SBoss::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,bossId_);
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(Int64,life_);
PACKET_ENCODE(Int64,maxLife_);
PACKET_ENCODE(Int64,refreshTime_);
PACKET_ENCODE(String,lastKillName_);
PACKET_ENCODE(Int64,lastKillTime_);
PACKET_ENCODE(Int32,line_);
PACKET_ENCODE(Int32,playerNum_);
return true;}
void SBoss::clear(){
bossId_ = 0;
copyCode_ = 0;
life_ = 0;
maxLife_ = 0;
refreshTime_ = 0;
lastKillName_.clear();
lastKillTime_ = 0;
line_ = 0;
playerNum_ = 0;
}
bool SRemoveBoss::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);bossIds_.push_back(item);}}
PACKET_DECODE(Int32,line_);
PACKET_DECODE(Int32,type_);
return true;}
bool SRemoveBoss::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,bossIds_.size());
for(vector<int32_t>::const_iterator vit=bossIds_.begin();vit!=bossIds_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(Int32,line_);
PACKET_ENCODE(Int32,type_);
return true;}
void SRemoveBoss::clear(){
bossIds_.clear();
line_ = 0;
type_ = 0;
}
bool SCompleteBoss::decode(CBufferReader &reader) {
if(!msgs::SCompleteCopy::decode(reader)){return false;}
if(!publicPlayer_.decode(reader)){return false;}
if(!guildId_.decode(reader)){return false;}
PACKET_DECODE(String,guildName_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);msgs::SItemAmount item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}rewards_.push_back(item);}}
if(!serverId_.decode(reader)){return false;}
return true;}
bool SCompleteBoss::encode(CBufferWriter &writer) const {
if(!msgs::SCompleteCopy::encode(writer)){return false;}
if(!publicPlayer_.encode(writer)){return false;}
if(!guildId_.encode(writer)){return false;}
PACKET_ENCODE(String,guildName_);
PACKET_ENCODE(UVar32,rewards_.size());
for(vector<msgs::SItemAmount>::const_iterator vit=rewards_.begin();vit!=rewards_.end();++vit){if(!vit->encode(writer)){return false;}}
if(!serverId_.encode(writer)){return false;}
return true;}
void SCompleteBoss::clear(){
publicPlayer_.clear();
guildId_.clear();
guildName_.clear();
rewards_.clear();
serverId_.clear();
}
bool SBossList::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SBoss item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}seq_.push_back(item);}}
return true;}
bool SBossList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(UVar32,seq_.size());
for(vector<SBoss>::const_iterator vit=seq_.begin();vit!=seq_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SBossList::clear(){
type_ = 0;
seq_.clear();
}
bool SWorldBossKillHis::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);dbs::TBossKillRecord item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}seq_.push_back(item);}}
return true;}
bool SWorldBossKillHis::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,seq_.size());
for(vector<dbs::TBossKillRecord>::const_iterator vit=seq_.begin();vit!=seq_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SWorldBossKillHis::clear(){
seq_.clear();
}
bool SVipBoss::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,code_);
PACKET_DECODE(Int64,refreshTime_);
return true;}
bool SVipBoss::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,code_);
PACKET_ENCODE(Int64,refreshTime_);
return true;}
void SVipBoss::clear(){
code_ = 0;
refreshTime_ = 0;
}
bool SVipBossInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,code_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SVipBoss item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}seq_.push_back(item);}}
return true;}
bool SVipBossInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,code_);
PACKET_ENCODE(UVar32,seq_.size());
for(vector<SVipBoss>::const_iterator vit=seq_.begin();vit!=seq_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SVipBossInfo::clear(){
code_ = 0;
seq_.clear();
}
bool SBossKillHis::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,bossCode_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);dbs::TBossKillRecord item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}seq_.push_back(item);}}
return true;}
bool SBossKillHis::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,bossCode_);
PACKET_ENCODE(UVar32,seq_.size());
for(vector<dbs::TBossKillRecord>::const_iterator vit=seq_.begin();vit!=seq_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SBossKillHis::clear(){
bossCode_ = 0;
seq_.clear();
}
bool SShiledBreak::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,bossId_);
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(Int32,diceId_);
PACKET_DECODE(Int32,shieldId_);
PACKET_DECODE(Int64,endTime_);
PACKET_DECODE(Int32,rewardId_);
return true;}
bool SShiledBreak::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,bossId_);
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,diceId_);
PACKET_ENCODE(Int32,shieldId_);
PACKET_ENCODE(Int64,endTime_);
PACKET_ENCODE(Int32,rewardId_);
return true;}
void SShiledBreak::clear(){
bossId_ = 0;
entityId_.clear();
diceId_ = 0;
shieldId_ = 0;
endTime_ = 0;
rewardId_ = 0;
}
bool SDiceResult::decode(CBufferReader &reader) {
if(!belongPlayer_.decode(reader)){return false;}
PACKET_DECODE(Int32,bossCode_);
PACKET_DECODE(Int32,diceNum_);
PACKET_DECODE(Int32,diceId_);
PACKET_DECODE(Int32,shieldId_);
return true;}
bool SDiceResult::encode(CBufferWriter &writer) const {
if(!belongPlayer_.encode(writer)){return false;}
PACKET_ENCODE(Int32,bossCode_);
PACKET_ENCODE(Int32,diceNum_);
PACKET_ENCODE(Int32,diceId_);
PACKET_ENCODE(Int32,shieldId_);
return true;}
void SDiceResult::clear(){
belongPlayer_.clear();
bossCode_ = 0;
diceNum_ = 0;
diceId_ = 0;
shieldId_ = 0;
}
bool SPlayerBossHurt::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int64,hurt_);
PACKET_DECODE(Int32,rank_);
return true;}
bool SPlayerBossHurt::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int64,hurt_);
PACKET_ENCODE(Int32,rank_);
return true;}
void SPlayerBossHurt::clear(){
entityId_.clear();
name_.clear();
hurt_ = 0;
rank_ = 0;
}
bool SBossHurtRank::decode(CBufferReader &reader) {
if(!bossEntityId_.decode(reader)){return false;}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SPlayerBossHurt item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}ranks_.push_back(item);}}
PACKET_DECODE(Int32,myRank_);
return true;}
bool SBossHurtRank::encode(CBufferWriter &writer) const {
if(!bossEntityId_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,ranks_.size());
for(vector<SPlayerBossHurt>::const_iterator vit=ranks_.begin();vit!=ranks_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(Int32,myRank_);
return true;}
void SBossHurtRank::clear(){
bossEntityId_.clear();
ranks_.clear();
myRank_ = 0;
}
bool SCancelBelong::decode(CBufferReader &reader) {
if(!toEntityId_.decode(reader)){return false;}
return true;}
bool SCancelBelong::encode(CBufferWriter &writer) const {
if(!toEntityId_.encode(writer)){return false;}
return true;}
void SCancelBelong::clear(){
toEntityId_.clear();
}
bool SXianHunBelongNum::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,belongNum_);
return true;}
bool SXianHunBelongNum::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,belongNum_);
return true;}
void SXianHunBelongNum::clear(){
belongNum_ = 0;
}
bool SHunqiBoss::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
PACKET_DECODE(Int32,playerNum_);
PACKET_DECODE(Int32,bossNum_);
PACKET_DECODE(Int32,maxBossNum_);
PACKET_DECODE(Int64,refreshTime_);
return true;}
bool SHunqiBoss::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(Int32,playerNum_);
PACKET_ENCODE(Int32,bossNum_);
PACKET_ENCODE(Int32,maxBossNum_);
PACKET_ENCODE(Int64,refreshTime_);
return true;}
void SHunqiBoss::clear(){
copyCode_ = 0;
playerNum_ = 0;
bossNum_ = 0;
maxBossNum_ = 0;
refreshTime_ = 0;
}
bool SHunqiBossList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SHunqiBoss item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool SHunqiBossList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<SHunqiBoss>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SHunqiBossList::clear(){
list_.clear();
}
bool SHunqiBossDetail::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,bossCode_);
PACKET_DECODE(Int64,life_);
PACKET_DECODE(Int64,refreshTime_);
return true;}
bool SHunqiBossDetail::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,bossCode_);
PACKET_ENCODE(Int64,life_);
PACKET_ENCODE(Int64,refreshTime_);
return true;}
void SHunqiBossDetail::clear(){
bossCode_ = 0;
life_ = 0;
refreshTime_ = 0;
}
bool SHunqiBossDetailList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SHunqiBossDetail item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool SHunqiBossDetailList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<SHunqiBossDetail>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SHunqiBossDetailList::clear(){
list_.clear();
}
bool SHunqiCopyBoss::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,bossCode_);
PACKET_DECODE(Bool,isLive_);
return true;}
bool SHunqiCopyBoss::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,bossCode_);
PACKET_ENCODE(Bool,isLive_);
return true;}
void SHunqiCopyBoss::clear(){
bossCode_ = 0;
isLive_ = 0;
}
bool SHunqiCopyBossList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SHunqiCopyBoss item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool SHunqiCopyBossList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<SHunqiCopyBoss>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SHunqiCopyBossList::clear(){
list_.clear();
}
bool SGodMagic::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
PACKET_DECODE(Int64,liveTime_);
PACKET_DECODE(Int64,refreshTime_);
return true;}
bool SGodMagic::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(Int64,liveTime_);
PACKET_ENCODE(Int64,refreshTime_);
return true;}
void SGodMagic::clear(){
copyCode_ = 0;
liveTime_ = 0;
refreshTime_ = 0;
}
bool SGodMagicList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SGodMagic item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool SGodMagicList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<SGodMagic>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SGodMagicList::clear(){
list_.clear();
}
bool SGodMagicFlag::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,monsterCode_);
PACKET_DECODE(Int32,flagId_);
PACKET_DECODE(Int32,plan_);
if(!belongId_.decode(reader)){return false;}
if(!flagPoint_.decode(reader)){return false;}
return true;}
bool SGodMagicFlag::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,monsterCode_);
PACKET_ENCODE(Int32,flagId_);
PACKET_ENCODE(Int32,plan_);
if(!belongId_.encode(writer)){return false;}
if(!flagPoint_.encode(writer)){return false;}
return true;}
void SGodMagicFlag::clear(){
monsterCode_ = 0;
flagId_ = 0;
plan_ = 0;
belongId_.clear();
flagPoint_.clear();
}
bool SGodMagicFlagList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SGodMagicFlag item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool SGodMagicFlagList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<SGodMagicFlag>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SGodMagicFlagList::clear(){
list_.clear();
}
bool SCompleteNeutralBoss::decode(CBufferReader &reader) {
if(!SCompleteBoss::decode(reader)){return false;}
return true;}
bool SCompleteNeutralBoss::encode(CBufferWriter &writer) const {
if(!SCompleteBoss::encode(writer)){return false;}
return true;}
void SCompleteNeutralBoss::clear(){
}
bool SNeutralBossList::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);lives_[k] = v;}}
return true;}
bool SNeutralBossList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,lives_.size());
for(map<int32_t, bool>::const_iterator it=lives_.begin();it!=lives_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
return true;}
void SNeutralBossList::clear(){
lives_.clear();
}
bool SShieldRandomGiftUpdate::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,diceId_);
PACKET_DECODE(Int32,leftNum_);
return true;}
bool SShieldRandomGiftUpdate::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,diceId_);
PACKET_ENCODE(Int32,leftNum_);
return true;}
void SShieldRandomGiftUpdate::clear(){
diceId_ = 0;
leftNum_ = 0;
}
bool SCompleteFourCityBoss::decode(CBufferReader &reader) {
if(!msgs::SCompleteCopy::decode(reader)){return false;}
if(!serverId_.decode(reader)){return false;}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);msgs::SItemAmount item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}belongRewards_.push_back(item);}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);msgs::SItemAmount item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}rewards_.push_back(item);}}
PACKET_DECODE(Int32,rankReward_);
PACKET_DECODE(Int32,rank_);
PACKET_DECODE(Int64,hurt_);
return true;}
bool SCompleteFourCityBoss::encode(CBufferWriter &writer) const {
if(!msgs::SCompleteCopy::encode(writer)){return false;}
if(!serverId_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,belongRewards_.size());
for(vector<msgs::SItemAmount>::const_iterator vit=belongRewards_.begin();vit!=belongRewards_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(UVar32,rewards_.size());
for(vector<msgs::SItemAmount>::const_iterator vit=rewards_.begin();vit!=rewards_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(Int32,rankReward_);
PACKET_ENCODE(Int32,rank_);
PACKET_ENCODE(Int64,hurt_);
return true;}
void SCompleteFourCityBoss::clear(){
serverId_.clear();
belongRewards_.clear();
rewards_.clear();
rankReward_ = 0;
rank_ = 0;
hurt_ = 0;
}
bool SCompleteFairylandBoss::decode(CBufferReader &reader) {
if(!msgs::SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,star_);
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,subType_);
PACKET_DECODE(Int32,layer_);
PACKET_DECODE(Int32,useTime_);
return true;}
bool SCompleteFairylandBoss::encode(CBufferWriter &writer) const {
if(!msgs::SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,star_);
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,subType_);
PACKET_ENCODE(Int32,layer_);
PACKET_ENCODE(Int32,useTime_);
return true;}
void SCompleteFairylandBoss::clear(){
star_ = 0;
type_ = 0;
subType_ = 0;
layer_ = 0;
useTime_ = 0;
}
bool SMiracleIslandBoss::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode_);
PACKET_DECODE(Int32,bossId_);
if(!serverId_.decode(reader)){return false;}
PACKET_DECODE(Int64,refreshDt_);
return true;}
bool SMiracleIslandBoss::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(Int32,bossId_);
if(!serverId_.encode(writer)){return false;}
PACKET_ENCODE(Int64,refreshDt_);
return true;}
void SMiracleIslandBoss::clear(){
copyCode_ = 0;
bossId_ = 0;
serverId_.clear();
refreshDt_ = 0;
}
bool SMiracleIslandBossList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SMiracleIslandBoss item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool SMiracleIslandBossList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<SMiracleIslandBoss>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SMiracleIslandBossList::clear(){
list_.clear();
}
bool SCompleteMiracleIslandBoss::decode(CBufferReader &reader) {
if(!msgs::SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,bossId_);
PACKET_DECODE(Int32,isOwn_);
PACKET_DECODE(String,ownName_);
if(!publicPlayer_.decode(reader)){return false;}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);msgs::SItemAmount item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}rewards_.push_back(item);}}
return true;}
bool SCompleteMiracleIslandBoss::encode(CBufferWriter &writer) const {
if(!msgs::SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,bossId_);
PACKET_ENCODE(Int32,isOwn_);
PACKET_ENCODE(String,ownName_);
if(!publicPlayer_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,rewards_.size());
for(vector<msgs::SItemAmount>::const_iterator vit=rewards_.begin();vit!=rewards_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SCompleteMiracleIslandBoss::clear(){
bossId_ = 0;
isOwn_ = 0;
ownName_.clear();
publicPlayer_.clear();
rewards_.clear();
}
bool SFairylandEvaluate::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,endTime_);
PACKET_DECODE(Int32,star_);
return true;}
bool SFairylandEvaluate::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,endTime_);
PACKET_ENCODE(Int32,star_);
return true;}
void SFairylandEvaluate::clear(){
endTime_ = 0;
star_ = 0;
}
bool SFairylandBoss::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,layer_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);hasGotReward_[k] = v;}}
PACKET_DECODE(Int32,star_);
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,subtype_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);mops_[k] = v;}}
PACKET_DECODE(Int32,lastLayer_);
return true;}
bool SFairylandBoss::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,layer_);
PACKET_ENCODE(UVar32,hasGotReward_.size());
for(map<int32_t, int32_t>::const_iterator it=hasGotReward_.begin();it!=hasGotReward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,star_);
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,subtype_);
PACKET_ENCODE(UVar32,mops_.size());
for(map<int32_t, int32_t>::const_iterator it=mops_.begin();it!=mops_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,lastLayer_);
return true;}
void SFairylandBoss::clear(){
layer_ = 0;
hasGotReward_.clear();
star_ = 0;
type_ = 0;
subtype_ = 0;
mops_.clear();
lastLayer_ = 0;
}
bool SFairylandBossInfo::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SFairylandBoss item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}layers_.push_back(item);}}
return true;}
bool SFairylandBossInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,layers_.size());
for(vector<SFairylandBoss>::const_iterator vit=layers_.begin();vit!=layers_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SFairylandBossInfo::clear(){
layers_.clear();
}
bool SLunHuiBossRank::decode(CBufferReader &reader) {
if(!playerId_.decode(reader)){return false;}
PACKET_DECODE(Int32,rank_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Int64,hurt_);
return true;}
bool SLunHuiBossRank::encode(CBufferWriter &writer) const {
if(!playerId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,rank_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int64,hurt_);
return true;}
void SLunHuiBossRank::clear(){
playerId_.clear();
rank_ = 0;
name_.clear();
hurt_ = 0;
}
bool SCompleteLunHuiBoss::decode(CBufferReader &reader) {
if(!SCompleteBoss::decode(reader)){return false;}
PACKET_DECODE(Int32,rank_);
PACKET_DECODE(Int64,hurt_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SLunHuiBossRank item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}ranks_.push_back(item);}}
return true;}
bool SCompleteLunHuiBoss::encode(CBufferWriter &writer) const {
if(!SCompleteBoss::encode(writer)){return false;}
PACKET_ENCODE(Int32,rank_);
PACKET_ENCODE(Int64,hurt_);
PACKET_ENCODE(UVar32,ranks_.size());
for(vector<SLunHuiBossRank>::const_iterator vit=ranks_.begin();vit!=ranks_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SCompleteLunHuiBoss::clear(){
rank_ = 0;
hurt_ = 0;
ranks_.clear();
}
bool SCompleteReincarnTowerBoss::decode(CBufferReader &reader) {
if(!msgs::SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,openDay_);
PACKET_DECODE(Int32,layer_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);baseRewards_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);extraRewards_[k] = v;}}
PACKET_DECODE(Bool,notRdExtra_);
PACKET_DECODE(Int32,duration_);
return true;}
bool SCompleteReincarnTowerBoss::encode(CBufferWriter &writer) const {
if(!msgs::SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,openDay_);
PACKET_ENCODE(Int32,layer_);
PACKET_ENCODE(UVar32,baseRewards_.size());
for(map<int32_t, int32_t>::const_iterator it=baseRewards_.begin();it!=baseRewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,extraRewards_.size());
for(map<int32_t, int32_t>::const_iterator it=extraRewards_.begin();it!=extraRewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Bool,notRdExtra_);
PACKET_ENCODE(Int32,duration_);
return true;}
void SCompleteReincarnTowerBoss::clear(){
openDay_ = 0;
layer_ = 0;
baseRewards_.clear();
extraRewards_.clear();
notRdExtra_ = 0;
duration_ = 0;
}
bool SRoleXianDan::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);xianDanItem_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);xianDan_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);addValue_[k] = v;}}
return true;}
bool SRoleXianDan::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,xianDanItem_.size());
for(map<int32_t, int32_t>::const_iterator it=xianDanItem_.begin();it!=xianDanItem_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,xianDan_.size());
for(map<int32_t, int32_t>::const_iterator it=xianDan_.begin();it!=xianDan_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,addValue_.size());
for(map<int32_t, int32_t>::const_iterator it=addValue_.begin();it!=addValue_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SRoleXianDan::clear(){
xianDanItem_.clear();
xianDan_.clear();
addValue_.clear();
}
bool SXianDanInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SRoleXianDan v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}roleDanMap_[k] = v;}}
return true;}
bool SXianDanInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,roleDanMap_.size());
for(map<int32_t, SRoleXianDan>::const_iterator it=roleDanMap_.begin();it!=roleDanMap_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SXianDanInfo::clear(){
roleDanMap_.clear();
}
bool SChildFamilyInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,happyValue_);
PACKET_DECODE(Int64,happyLimit_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);building_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);events_[k] = v;}}
PACKET_DECODE(Int32,freeCount_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int64_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int64,v);beginDts_[k] = v;}}
PACKET_DECODE(Int32,stealCount_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int64_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int64,v);activeDts_[k] = v;}}
return true;}
bool SChildFamilyInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,happyValue_);
PACKET_ENCODE(Int64,happyLimit_);
PACKET_ENCODE(UVar32,building_.size());
for(map<int32_t, int32_t>::const_iterator it=building_.begin();it!=building_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,events_.size());
for(map<int32_t, int32_t>::const_iterator it=events_.begin();it!=events_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,freeCount_);
PACKET_ENCODE(UVar32,beginDts_.size());
for(map<int32_t, int64_t>::const_iterator it=beginDts_.begin();it!=beginDts_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int64,it->second);}
PACKET_ENCODE(Int32,stealCount_);
PACKET_ENCODE(UVar32,activeDts_.size());
for(map<int32_t, int64_t>::const_iterator it=activeDts_.begin();it!=activeDts_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int64,it->second);}
return true;}
void SChildFamilyInfo::clear(){
happyValue_ = 0;
happyLimit_ = 0;
building_.clear();
events_.clear();
freeCount_ = 0;
beginDts_.clear();
stealCount_ = 0;
activeDts_.clear();
}
bool SChildFamilyRecord::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
PACKET_DECODE(String,playerName_);
PACKET_DECODE(String,buildName_);
PACKET_DECODE(Int64,value_);
return true;}
bool SChildFamilyRecord::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(String,playerName_);
PACKET_ENCODE(String,buildName_);
PACKET_ENCODE(Int64,value_);
return true;}
void SChildFamilyRecord::clear(){
type_ = 0;
playerName_.clear();
buildName_.clear();
value_ = 0;
}
bool SChildFamilyRecords::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SChildFamilyRecord item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}lists_.push_back(item);}}
return true;}
bool SChildFamilyRecords::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,lists_.size());
for(vector<SChildFamilyRecord>::const_iterator vit=lists_.begin();vit!=lists_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SChildFamilyRecords::clear(){
lists_.clear();
}
bool SChildFamilySingle::decode(CBufferReader &reader) {
if(!playerId_.decode(reader)){return false;}
PACKET_DECODE(String,playerName_);
PACKET_DECODE(Int64,happyValue_);
PACKET_DECODE(Int32,buildingLevel_);
PACKET_DECODE(Int32,career_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);building_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int64_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int64,v);beginDts_[k] = v;}}
return true;}
bool SChildFamilySingle::encode(CBufferWriter &writer) const {
if(!playerId_.encode(writer)){return false;}
PACKET_ENCODE(String,playerName_);
PACKET_ENCODE(Int64,happyValue_);
PACKET_ENCODE(Int32,buildingLevel_);
PACKET_ENCODE(Int32,career_);
PACKET_ENCODE(UVar32,building_.size());
for(map<int32_t, int32_t>::const_iterator it=building_.begin();it!=building_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,beginDts_.size());
for(map<int32_t, int64_t>::const_iterator it=beginDts_.begin();it!=beginDts_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int64,it->second);}
return true;}
void SChildFamilySingle::clear(){
playerId_.clear();
playerName_.clear();
happyValue_ = 0;
buildingLevel_ = 0;
career_ = 0;
building_.clear();
beginDts_.clear();
}
bool SChildFamilyList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SChildFamilySingle item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}lists_.push_back(item);}}
return true;}
bool SChildFamilyList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,lists_.size());
for(vector<SChildFamilySingle>::const_iterator vit=lists_.begin();vit!=lists_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SChildFamilyList::clear(){
lists_.clear();
}
bool SChildFamilyGrow::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,id_);
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,star_);
PACKET_DECODE(Int64,endTime_);
PACKET_DECODE(Int64,happy_);
PACKET_DECODE(Int64,activeDt_);
return true;}
bool SChildFamilyGrow::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,id_);
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,star_);
PACKET_ENCODE(Int64,endTime_);
PACKET_ENCODE(Int64,happy_);
PACKET_ENCODE(Int64,activeDt_);
return true;}
void SChildFamilyGrow::clear(){
id_ = 0;
level_ = 0;
star_ = 0;
endTime_ = 0;
happy_ = 0;
activeDt_ = 0;
}
bool SChildFamilyGrows::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SChildFamilyGrow v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}maps_[k] = v;}}
return true;}
bool SChildFamilyGrows::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,maps_.size());
for(map<int32_t, SChildFamilyGrow>::const_iterator it=maps_.begin();it!=maps_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SChildFamilyGrows::clear(){
maps_.clear();
}
bool SChildFamilyBesteal::decode(CBufferReader &reader) {
PACKET_DECODE(String,playerName_);
PACKET_DECODE(Int64,stealValue_);
return true;}
bool SChildFamilyBesteal::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,playerName_);
PACKET_ENCODE(Int64,stealValue_);
return true;}
void SChildFamilyBesteal::clear(){
playerName_.clear();
stealValue_ = 0;
}
bool STrumpSingle::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,needTime_);
return true;}
bool STrumpSingle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,needTime_);
return true;}
void STrumpSingle::clear(){
needTime_ = 0;
}
bool STrumpInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Bool,unlock_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);activeMap_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;STrumpSingle v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}trumpMap_[k] = v;}}
PACKET_DECODE(Int32,curFight_);
return true;}
bool STrumpInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Bool,unlock_);
PACKET_ENCODE(UVar32,activeMap_.size());
for(map<int32_t, bool>::const_iterator it=activeMap_.begin();it!=activeMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
PACKET_ENCODE(UVar32,trumpMap_.size());
for(map<int32_t, STrumpSingle>::const_iterator it=trumpMap_.begin();it!=trumpMap_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
PACKET_ENCODE(Int32,curFight_);
return true;}
void STrumpInfo::clear(){
unlock_ = 0;
activeMap_.clear();
trumpMap_.clear();
curFight_ = 0;
}
bool SPlayerSuperVip::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,level_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);levelReward_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);weekReward_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);todayRechargeMap_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);copyCount_[k] = v;}}
PACKET_DECODE(Int32,lastWeekLevel_);
return true;}
bool SPlayerSuperVip::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(UVar32,levelReward_.size());
for(map<int32_t, bool>::const_iterator it=levelReward_.begin();it!=levelReward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
PACKET_ENCODE(UVar32,weekReward_.size());
for(map<int32_t, bool>::const_iterator it=weekReward_.begin();it!=weekReward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
PACKET_ENCODE(UVar32,todayRechargeMap_.size());
for(map<int32_t, bool>::const_iterator it=todayRechargeMap_.begin();it!=todayRechargeMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
PACKET_ENCODE(UVar32,copyCount_.size());
for(map<int32_t, int32_t>::const_iterator it=copyCount_.begin();it!=copyCount_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,lastWeekLevel_);
return true;}
void SPlayerSuperVip::clear(){
level_ = 0;
levelReward_.clear();
weekReward_.clear();
todayRechargeMap_.clear();
copyCount_.clear();
lastWeekLevel_ = 0;
}
bool SActive::decode(CBufferReader &reader) {
if(!dbs::TActive::decode(reader)){return false;}
PACKET_DECODE(Int64,openDt_);
PACKET_DECODE(Int64,closeDt_);
PACKET_DECODE(Int64,prepareDt_);
return true;}
bool SActive::encode(CBufferWriter &writer) const {
if(!dbs::TActive::encode(writer)){return false;}
PACKET_ENCODE(Int64,openDt_);
PACKET_ENCODE(Int64,closeDt_);
PACKET_ENCODE(Int64,prepareDt_);
return true;}
void SActive::clear(){
openDt_ = 0;
closeDt_ = 0;
prepareDt_ = 0;
}
bool SActiveList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SActive item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}activeLst_.push_back(item);}}
return true;}
bool SActiveList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,activeLst_.size());
for(vector<SActive>::const_iterator vit=activeLst_.begin();vit!=activeLst_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SActiveList::clear(){
activeLst_.clear();
}
bool SActiveUpdate::decode(CBufferReader &reader) {
PACKET_DECODE(Int16,status_);
if(!active_.decode(reader)){return false;}
return true;}
bool SActiveUpdate::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int16,status_);
if(!active_.encode(writer)){return false;}
return true;}
void SActiveUpdate::clear(){
status_ = 0;
active_.clear();
}
bool SActiveUpdateList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SActiveUpdate item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}actives_.push_back(item);}}
return true;}
bool SActiveUpdateList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,actives_.size());
for(vector<SActiveUpdate>::const_iterator vit=actives_.begin();vit!=actives_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SActiveUpdateList::clear(){
actives_.clear();
}
bool SActiveTemplateInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,server_id_);
PACKET_DECODE(Int32,config_id_);
PACKET_DECODE(Int64,openDt_);
PACKET_DECODE(Int64,endDt_);
return true;}
bool SActiveTemplateInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,server_id_);
PACKET_ENCODE(Int32,config_id_);
PACKET_ENCODE(Int64,openDt_);
PACKET_ENCODE(Int64,endDt_);
return true;}
void SActiveTemplateInfo::clear(){
server_id_ = 0;
config_id_ = 0;
openDt_ = 0;
endDt_ = 0;
}
bool SActiveTemplateList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SActiveTemplateInfo item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}activeList_.push_back(item);}}
return true;}
bool SActiveTemplateList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,activeList_.size());
for(vector<SActiveTemplateInfo>::const_iterator vit=activeList_.begin();vit!=activeList_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SActiveTemplateList::clear(){
activeList_.clear();
}
bool SActiveTemplateUpdate::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,updateType_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SActiveTemplateInfo item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}updateList_.push_back(item);}}
return true;}
bool SActiveTemplateUpdate::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,updateType_);
PACKET_ENCODE(UVar32,updateList_.size());
for(vector<SActiveTemplateInfo>::const_iterator vit=updateList_.begin();vit!=updateList_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SActiveTemplateUpdate::clear(){
updateType_ = 0;
updateList_.clear();
}
bool SContinousTopUpRebateInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);getFlag_.push_back(item);}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);indexMap_[k] = v;}}
return true;}
bool SContinousTopUpRebateInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,getFlag_.size());
for(vector<int32_t>::const_iterator vit=getFlag_.begin();vit!=getFlag_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(UVar32,indexMap_.size());
for(map<int32_t, int32_t>::const_iterator it=indexMap_.begin();it!=indexMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SContinousTopUpRebateInfo::clear(){
activeId_ = 0;
getFlag_.clear();
indexMap_.clear();
}
bool SAccumRechargeInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
PACKET_DECODE(Int32,rechaege_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);rewardGot_[k] = v;}}
return true;}
bool SAccumRechargeInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(Int32,rechaege_);
PACKET_ENCODE(UVar32,rewardGot_.size());
for(map<int32_t, bool>::const_iterator it=rewardGot_.begin();it!=rewardGot_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
return true;}
void SAccumRechargeInfo::clear(){
activeId_ = 0;
rechaege_ = 0;
rewardGot_.clear();
}
bool SLoveTaskInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
PACKET_DECODE(Bool,hasGotReward_);
PACKET_DECODE(Bool,isComplete_);
return true;}
bool SLoveTaskInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(Bool,hasGotReward_);
PACKET_ENCODE(Bool,isComplete_);
return true;}
void SLoveTaskInfo::clear(){
activeId_ = 0;
hasGotReward_ = 0;
isComplete_ = 0;
}
bool SActiveTargets::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;map<int32_t, int32_t> v;PACKET_DECODE(Int32,k);{uint32_t len1=0;PACKET_DECODE(UVar32,len1);for(uint32_t i1=0;i1<len1;++i1){int32_t k1;int32_t v1;PACKET_DECODE(Int32,k1);PACKET_DECODE(Int32,v1);v[k1] = v1;}}
mapValue_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);intValue_[k] = v;}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);gotIndexs_.push_back(item);}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);gotDayIndex_.push_back(item);}}
return true;}
bool SActiveTargets::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,mapValue_.size());
for(map<int32_t, map<int32_t, int32_t> >::const_iterator it=mapValue_.begin();it!=mapValue_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(UVar32,it->second.size());
for(map<int32_t, int32_t>::const_iterator it1=it->second.begin();it1!=it->second.end();++it1){PACKET_ENCODE(Int32,it1->first);PACKET_ENCODE(Int32,it1->second);}
}
PACKET_ENCODE(UVar32,intValue_.size());
for(map<int32_t, int32_t>::const_iterator it=intValue_.begin();it!=intValue_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,gotIndexs_.size());
for(vector<int32_t>::const_iterator vit=gotIndexs_.begin();vit!=gotIndexs_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(UVar32,gotDayIndex_.size());
for(vector<int32_t>::const_iterator vit=gotDayIndex_.begin();vit!=gotDayIndex_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SActiveTargets::clear(){
activeId_ = 0;
mapValue_.clear();
intValue_.clear();
gotIndexs_.clear();
gotDayIndex_.clear();
}
bool SActiveDayRecharge::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);rewardGot_[k] = v;}}
return true;}
bool SActiveDayRecharge::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,rewardGot_.size());
for(map<int32_t, bool>::const_iterator it=rewardGot_.begin();it!=rewardGot_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
return true;}
void SActiveDayRecharge::clear(){
activeId_ = 0;
rewardGot_.clear();
}
bool SActiveAccuConsume::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
PACKET_DECODE(Int32,consume_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);rewardGot_[k] = v;}}
return true;}
bool SActiveAccuConsume::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(Int32,consume_);
PACKET_ENCODE(UVar32,rewardGot_.size());
for(map<int32_t, bool>::const_iterator it=rewardGot_.begin();it!=rewardGot_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
return true;}
void SActiveAccuConsume::clear(){
activeId_ = 0;
consume_ = 0;
rewardGot_.clear();
}
bool SActiveDayConsume::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
PACKET_DECODE(Int32,consume_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);rewardGot_[k] = v;}}
return true;}
bool SActiveDayConsume::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(Int32,consume_);
PACKET_ENCODE(UVar32,rewardGot_.size());
for(map<int32_t, bool>::const_iterator it=rewardGot_.begin();it!=rewardGot_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
return true;}
void SActiveDayConsume::clear(){
activeId_ = 0;
consume_ = 0;
rewardGot_.clear();
}
bool SContinousLogin::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);rewardMap_[k] = v;}}
PACKET_DECODE(Int32,loginDays_);
return true;}
bool SContinousLogin::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,rewardMap_.size());
for(map<int32_t, bool>::const_iterator it=rewardMap_.begin();it!=rewardMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
PACKET_ENCODE(Int32,loginDays_);
return true;}
void SContinousLogin::clear(){
activeId_ = 0;
rewardMap_.clear();
loginDays_ = 0;
}
bool SActiveCompound::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);countMap_[k] = v;}}
return true;}
bool SActiveCompound::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,countMap_.size());
for(map<int32_t, int32_t>::const_iterator it=countMap_.begin();it!=countMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SActiveCompound::clear(){
activeId_ = 0;
countMap_.clear();
}
bool SActiveShareGame::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
PACKET_DECODE(Int32,dayShareNum_);
PACKET_DECODE(Int32,totalShareNum_);
PACKET_DECODE(Bool,isGotDayReward_);
PACKET_DECODE(Bool,isGotTotolReward_);
return true;}
bool SActiveShareGame::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(Int32,dayShareNum_);
PACKET_ENCODE(Int32,totalShareNum_);
PACKET_ENCODE(Bool,isGotDayReward_);
PACKET_ENCODE(Bool,isGotTotolReward_);
return true;}
void SActiveShareGame::clear(){
activeId_ = 0;
dayShareNum_ = 0;
totalShareNum_ = 0;
isGotDayReward_ = 0;
isGotTotolReward_ = 0;
}
bool SActiveQQVipDayGift::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
PACKET_DECODE(Int32,vip_);
return true;}
bool SActiveQQVipDayGift::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(Int32,vip_);
return true;}
void SActiveQQVipDayGift::clear(){
activeId_ = 0;
vip_ = 0;
}
bool SActivePlatformReward::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);fRewardGod_.push_back(item);}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);rewardGot_[k] = v;}}
PACKET_DECODE(Bool,setZoneCover_);
return true;}
bool SActivePlatformReward::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,fRewardGod_.size());
for(vector<int32_t>::const_iterator vit=fRewardGod_.begin();vit!=fRewardGod_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(UVar32,rewardGot_.size());
for(map<int32_t, bool>::const_iterator it=rewardGot_.begin();it!=rewardGot_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
PACKET_ENCODE(Bool,setZoneCover_);
return true;}
void SActivePlatformReward::clear(){
activeId_ = 0;
fRewardGod_.clear();
rewardGot_.clear();
setZoneCover_ = 0;
}
bool SActiveQQPetReward::decode(CBufferReader &reader) {
PACKET_DECODE(String,values_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);rewardMap_[k] = v;}}
return true;}
bool SActiveQQPetReward::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,values_);
PACKET_ENCODE(UVar32,rewardMap_.size());
for(map<int32_t, bool>::const_iterator it=rewardMap_.begin();it!=rewardMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
return true;}
void SActiveQQPetReward::clear(){
values_.clear();
rewardMap_.clear();
}
bool SActiveTreasure::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
return true;}
bool SActiveTreasure::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
return true;}
void SActiveTreasure::clear(){
activeId_ = 0;
}
bool SInviteFirend::decode(CBufferReader &reader) {
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,career_);
PACKET_DECODE(String,via_);
PACKET_DECODE(Bool,getReward_);
return true;}
bool SInviteFirend::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,career_);
PACKET_ENCODE(String,via_);
PACKET_ENCODE(Bool,getReward_);
return true;}
void SInviteFirend::clear(){
name_.clear();
career_ = 0;
via_.clear();
getReward_ = 0;
}
bool SInviteFriends::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);targetIndexs_.push_back(item);}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SInviteFirend v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}friends_[k] = v;}}
return true;}
bool SInviteFriends::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,targetIndexs_.size());
for(vector<int32_t>::const_iterator vit=targetIndexs_.begin();vit!=targetIndexs_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(UVar32,friends_.size());
for(map<int32_t, SInviteFirend>::const_iterator it=friends_.begin();it!=friends_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SInviteFriends::clear(){
targetIndexs_.clear();
friends_.clear();
}
bool SInvteFriendRedPack::decode(CBufferReader &reader) {
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,gold_);
return true;}
bool SInvteFriendRedPack::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,gold_);
return true;}
void SInvteFriendRedPack::clear(){
name_.clear();
gold_ = 0;
}
bool SInvteFriendRedPacks::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SInvteFriendRedPack item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}redPacks_.push_back(item);}}
return true;}
bool SInvteFriendRedPacks::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,redPacks_.size());
for(vector<SInvteFriendRedPack>::const_iterator vit=redPacks_.begin();vit!=redPacks_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SInvteFriendRedPacks::clear(){
redPacks_.clear();
}
bool SInviteFriendHelp::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,succNum_);
PACKET_DECODE(Int32,hasNum_);
return true;}
bool SInviteFriendHelp::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,succNum_);
PACKET_ENCODE(Int32,hasNum_);
return true;}
void SInviteFriendHelp::clear(){
succNum_ = 0;
hasNum_ = 0;
}
bool SShareLittleGame::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
PACKET_DECODE(Int32,dayShare_);
PACKET_DECODE(Int32,totalShare_);
PACKET_DECODE(Int64,cd_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);dayRewardGot_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewardGot_[k] = v;}}
return true;}
bool SShareLittleGame::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(Int32,dayShare_);
PACKET_ENCODE(Int32,totalShare_);
PACKET_ENCODE(Int64,cd_);
PACKET_ENCODE(UVar32,dayRewardGot_.size());
for(map<int32_t, int32_t>::const_iterator it=dayRewardGot_.begin();it!=dayRewardGot_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,rewardGot_.size());
for(map<int32_t, int32_t>::const_iterator it=rewardGot_.begin();it!=rewardGot_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SShareLittleGame::clear(){
activeId_ = 0;
dayShare_ = 0;
totalShare_ = 0;
cd_ = 0;
dayRewardGot_.clear();
rewardGot_.clear();
}
bool SActiveSecretSell::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);sells_[k] = v;}}
PACKET_DECODE(Int64,lastFlush_);
return true;}
bool SActiveSecretSell::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,sells_.size());
for(map<int32_t, bool>::const_iterator it=sells_.begin();it!=sells_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
PACKET_ENCODE(Int64,lastFlush_);
return true;}
void SActiveSecretSell::clear(){
activeId_ = 0;
sells_.clear();
lastFlush_ = 0;
}
bool SActiveRechargeTurntable::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
PACKET_DECODE(Int32,totalRecharge_);
PACKET_DECODE(Int32,count_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);recordMap_[k] = v;}}
return true;}
bool SActiveRechargeTurntable::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(Int32,totalRecharge_);
PACKET_ENCODE(Int32,count_);
PACKET_ENCODE(UVar32,recordMap_.size());
for(map<int32_t, bool>::const_iterator it=recordMap_.begin();it!=recordMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
return true;}
void SActiveRechargeTurntable::clear(){
activeId_ = 0;
totalRecharge_ = 0;
count_ = 0;
recordMap_.clear();
}
bool SActiveConsumeTurntable::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
PACKET_DECODE(Int32,totalConsume_);
PACKET_DECODE(Int32,count_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);recordMap_[k] = v;}}
return true;}
bool SActiveConsumeTurntable::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(Int32,totalConsume_);
PACKET_ENCODE(Int32,count_);
PACKET_ENCODE(UVar32,recordMap_.size());
for(map<int32_t, bool>::const_iterator it=recordMap_.begin();it!=recordMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
return true;}
void SActiveConsumeTurntable::clear(){
activeId_ = 0;
totalConsume_ = 0;
count_ = 0;
recordMap_.clear();
}
bool SActiveOneRecharge::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,active_id_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);states_[k] = v;}}
return true;}
bool SActiveOneRecharge::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,active_id_);
PACKET_ENCODE(UVar32,states_.size());
for(map<int32_t, int32_t>::const_iterator it=states_.begin();it!=states_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SActiveOneRecharge::clear(){
active_id_ = 0;
states_.clear();
}
bool SActiveFlashSale::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,active_id_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;msgs::SIntIntPair v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}saleTimes_[k] = v;}}
return true;}
bool SActiveFlashSale::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,active_id_);
PACKET_ENCODE(UVar32,saleTimes_.size());
for(map<int32_t, msgs::SIntIntPair>::const_iterator it=saleTimes_.begin();it!=saleTimes_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SActiveFlashSale::clear(){
active_id_ = 0;
saleTimes_.clear();
}
bool SActiveExpRain::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,per_);
return true;}
bool SActiveExpRain::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,per_);
return true;}
void SActiveExpRain::clear(){
per_ = 0;
}
bool SActiveDayRank::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
PACKET_DECODE(Int32,toplistType_);
PACKET_DECODE(Int32,day_);
return true;}
bool SActiveDayRank::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(Int32,toplistType_);
PACKET_ENCODE(Int32,day_);
return true;}
void SActiveDayRank::clear(){
activeId_ = 0;
toplistType_ = 0;
day_ = 0;
}
bool SWeekActive::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
return true;}
bool SWeekActive::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
return true;}
void SWeekActive::clear(){
activeId_ = 0;
}
bool STodayCombat::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int64_t k;bool v;PACKET_DECODE(Int64,k);PACKET_DECODE(Bool,v);gotRewardMap_[k] = v;}}
return true;}
bool STodayCombat::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,gotRewardMap_.size());
for(map<int64_t, bool>::const_iterator it=gotRewardMap_.begin();it!=gotRewardMap_.end();++it){PACKET_ENCODE(Int64,it->first);PACKET_ENCODE(Bool,it->second);}
return true;}
void STodayCombat::clear(){
activeId_ = 0;
gotRewardMap_.clear();
}
bool SActiveRechargeDoubleReset::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
return true;}
bool SActiveRechargeDoubleReset::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
return true;}
void SActiveRechargeDoubleReset::clear(){
activeId_ = 0;
}
bool SActiveTask::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);completeTimes_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);gotRewardTime_[k] = v;}}
return true;}
bool SActiveTask::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,completeTimes_.size());
for(map<int32_t, int32_t>::const_iterator it=completeTimes_.begin();it!=completeTimes_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,gotRewardTime_.size());
for(map<int32_t, int32_t>::const_iterator it=gotRewardTime_.begin();it!=gotRewardTime_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SActiveTask::clear(){
activeId_ = 0;
completeTimes_.clear();
gotRewardTime_.clear();
}
bool SActiveExchangeParty::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);completeTimes_[k] = v;}}
return true;}
bool SActiveExchangeParty::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,completeTimes_.size());
for(map<int32_t, int32_t>::const_iterator it=completeTimes_.begin();it!=completeTimes_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SActiveExchangeParty::clear(){
activeId_ = 0;
completeTimes_.clear();
}
bool SActiveAccuRank::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
PACKET_DECODE(Int32,toplistType_);
PACKET_DECODE(Int32,day_);
PACKET_DECODE(Int64,value_);
return true;}
bool SActiveAccuRank::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(Int32,toplistType_);
PACKET_ENCODE(Int32,day_);
PACKET_ENCODE(Int64,value_);
return true;}
void SActiveAccuRank::clear(){
activeId_ = 0;
toplistType_ = 0;
day_ = 0;
value_ = 0;
}
bool SActiveAccuCombat::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
PACKET_DECODE(Int64,combat_);
return true;}
bool SActiveAccuCombat::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(Int64,combat_);
return true;}
void SActiveAccuCombat::clear(){
activeId_ = 0;
combat_ = 0;
}
bool SActiveRedPacketInfo::decode(CBufferReader &reader) {
if(!playerId_.decode(reader)){return false;}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);info_[k] = v;}}
return true;}
bool SActiveRedPacketInfo::encode(CBufferWriter &writer) const {
if(!playerId_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,info_.size());
for(map<int32_t, int32_t>::const_iterator it=info_.begin();it!=info_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SActiveRedPacketInfo::clear(){
playerId_.clear();
info_.clear();
}
bool SActiveRedPlayerShow::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,career_);
PACKET_DECODE(String,name_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);ornaments_[k] = v;}}
PACKET_DECODE(Int32,itemId_);
PACKET_DECODE(Int32,num_);
return true;}
bool SActiveRedPlayerShow::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,career_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(UVar32,ornaments_.size());
for(map<int16_t, int32_t>::const_iterator it=ornaments_.begin();it!=ornaments_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,itemId_);
PACKET_ENCODE(Int32,num_);
return true;}
void SActiveRedPlayerShow::clear(){
career_ = 0;
name_.clear();
ornaments_.clear();
itemId_ = 0;
num_ = 0;
}
bool SActivePlayerRedPacket::decode(CBufferReader &reader) {
if(!playerId_.decode(reader)){return false;}
PACKET_DECODE(Int32,num_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);msgs::SIntIntPair item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}itemsGot_.push_back(item);}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SActiveRedPlayerShow item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}show_.push_back(item);}}
if(!self_.decode(reader)){return false;}
return true;}
bool SActivePlayerRedPacket::encode(CBufferWriter &writer) const {
if(!playerId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,num_);
PACKET_ENCODE(UVar32,itemsGot_.size());
for(vector<msgs::SIntIntPair>::const_iterator vit=itemsGot_.begin();vit!=itemsGot_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(UVar32,show_.size());
for(vector<SActiveRedPlayerShow>::const_iterator vit=show_.begin();vit!=show_.end();++vit){if(!vit->encode(writer)){return false;}}
if(!self_.encode(writer)){return false;}
return true;}
void SActivePlayerRedPacket::clear(){
playerId_.clear();
num_ = 0;
itemsGot_.clear();
show_.clear();
self_.clear();
}
bool SActiveRedPacketShow::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SActiveRedPlayerShow item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}show_.push_back(item);}}
return true;}
bool SActiveRedPacketShow::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,show_.size());
for(vector<SActiveRedPlayerShow>::const_iterator vit=show_.begin();vit!=show_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SActiveRedPacketShow::clear(){
show_.clear();
}
bool SActiveRechargeReturn::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rechargeReturn_[k] = v;}}
return true;}
bool SActiveRechargeReturn::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,rechargeReturn_.size());
for(map<int32_t, int32_t>::const_iterator it=rechargeReturn_.begin();it!=rechargeReturn_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SActiveRechargeReturn::clear(){
activeId_ = 0;
rechargeReturn_.clear();
}
bool SActiveRedPacketAdd::decode(CBufferReader &reader) {
if(!playerId_.decode(reader)){return false;}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);items_[k] = v;}}
return true;}
bool SActiveRedPacketAdd::encode(CBufferWriter &writer) const {
if(!playerId_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,items_.size());
for(map<int32_t, int32_t>::const_iterator it=items_.begin();it!=items_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SActiveRedPacketAdd::clear(){
playerId_.clear();
items_.clear();
}
bool SActiveOnlinePoint::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);hasGotReward_[k] = v;}}
return true;}
bool SActiveOnlinePoint::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,hasGotReward_.size());
for(map<int32_t, int32_t>::const_iterator it=hasGotReward_.begin();it!=hasGotReward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SActiveOnlinePoint::clear(){
activeId_ = 0;
hasGotReward_.clear();
}
bool SActiveStrongestGuildData::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
PACKET_DECODE(Int32,guildScore_);
PACKET_DECODE(Int32,selfScore_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);gols_.push_back(item);}}
return true;}
bool SActiveStrongestGuildData::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(Int32,guildScore_);
PACKET_ENCODE(Int32,selfScore_);
PACKET_ENCODE(UVar32,gols_.size());
for(vector<int32_t>::const_iterator vit=gols_.begin();vit!=gols_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SActiveStrongestGuildData::clear(){
activeId_ = 0;
guildScore_ = 0;
selfScore_ = 0;
gols_.clear();
}
bool SRedPacketRainGrabber::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,itemId_);
PACKET_DECODE(Int32,itemNum_);
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,playerName_);
PACKET_DECODE(Int32,career_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);ornaments_[k] = v;}}
return true;}
bool SRedPacketRainGrabber::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,itemId_);
PACKET_ENCODE(Int32,itemNum_);
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,playerName_);
PACKET_ENCODE(Int32,career_);
PACKET_ENCODE(UVar32,ornaments_.size());
for(map<int16_t, int32_t>::const_iterator it=ornaments_.begin();it!=ornaments_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SRedPacketRainGrabber::clear(){
itemId_ = 0;
itemNum_ = 0;
playerId_ = 0;
playerName_.clear();
career_ = 0;
ornaments_.clear();
}
bool SRedPacketRainPacket::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,redpacketId_);
PACKET_DECODE(Int32,splitNum_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SRedPacketRainGrabber item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}grabbers_.push_back(item);}}
return true;}
bool SRedPacketRainPacket::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,redpacketId_);
PACKET_ENCODE(Int32,splitNum_);
PACKET_ENCODE(UVar32,grabbers_.size());
for(vector<SRedPacketRainGrabber>::const_iterator vit=grabbers_.begin();vit!=grabbers_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SRedPacketRainPacket::clear(){
redpacketId_ = 0;
splitNum_ = 0;
grabbers_.clear();
}
bool SActiveRedPacketRain::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
PACKET_DECODE(Int32,index_);
PACKET_DECODE(Int64,endDt_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);grabbed_.push_back(item);}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SRedPacketRainPacket item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}packets_.push_back(item);}}
return true;}
bool SActiveRedPacketRain::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(Int32,index_);
PACKET_ENCODE(Int64,endDt_);
PACKET_ENCODE(UVar32,grabbed_.size());
for(vector<int32_t>::const_iterator vit=grabbed_.begin();vit!=grabbed_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(UVar32,packets_.size());
for(vector<SRedPacketRainPacket>::const_iterator vit=packets_.begin();vit!=packets_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SActiveRedPacketRain::clear(){
activeId_ = 0;
index_ = 0;
endDt_ = 0;
grabbed_.clear();
packets_.clear();
}
bool SActiveRedPacketRainGrab::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
PACKET_DECODE(Int32,index_);
PACKET_DECODE(Int32,redpacketIdx_);
PACKET_DECODE(Int32,itemId_);
PACKET_DECODE(Int32,itemNum_);
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,playerName_);
PACKET_DECODE(Int32,career_);
return true;}
bool SActiveRedPacketRainGrab::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(Int32,index_);
PACKET_ENCODE(Int32,redpacketIdx_);
PACKET_ENCODE(Int32,itemId_);
PACKET_ENCODE(Int32,itemNum_);
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,playerName_);
PACKET_ENCODE(Int32,career_);
return true;}
void SActiveRedPacketRainGrab::clear(){
activeId_ = 0;
index_ = 0;
redpacketIdx_ = 0;
itemId_ = 0;
itemNum_ = 0;
playerId_ = 0;
playerName_.clear();
career_ = 0;
}
bool SActiveTreasureRank::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
PACKET_DECODE(Int32,treasureCount_);
return true;}
bool SActiveTreasureRank::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(Int32,treasureCount_);
return true;}
void SActiveTreasureRank::clear(){
activeId_ = 0;
treasureCount_ = 0;
}
bool SActiveTreasureTarget::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
PACKET_DECODE(Int32,treasureCount_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);hasGotReward_[k] = v;}}
return true;}
bool SActiveTreasureTarget::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(Int32,treasureCount_);
PACKET_ENCODE(UVar32,hasGotReward_.size());
for(map<int32_t, int32_t>::const_iterator it=hasGotReward_.begin();it!=hasGotReward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SActiveTreasureTarget::clear(){
activeId_ = 0;
treasureCount_ = 0;
hasGotReward_.clear();
}
bool SScriptRewards::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
PACKET_DECODE(String,values_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);hasGotReward_[k] = v;}}
return true;}
bool SScriptRewards::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(String,values_);
PACKET_ENCODE(UVar32,hasGotReward_.size());
for(map<int32_t, bool>::const_iterator it=hasGotReward_.begin();it!=hasGotReward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
return true;}
void SScriptRewards::clear(){
activeId_ = 0;
values_.clear();
hasGotReward_.clear();
}
bool SActiveInvest::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;map<int32_t, bool> v;PACKET_DECODE(Int32,k);{uint32_t len1=0;PACKET_DECODE(UVar32,len1);for(uint32_t i1=0;i1<len1;++i1){int32_t k1;bool v1;PACKET_DECODE(Int32,k1);PACKET_DECODE(Bool,v1);v[k1] = v1;}}
gotRewardMap_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int64_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int64,v);startTime_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int64_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int64,v);endTime_[k] = v;}}
return true;}
bool SActiveInvest::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,gotRewardMap_.size());
for(map<int32_t, map<int32_t, bool> >::const_iterator it=gotRewardMap_.begin();it!=gotRewardMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(UVar32,it->second.size());
for(map<int32_t, bool>::const_iterator it1=it->second.begin();it1!=it->second.end();++it1){PACKET_ENCODE(Int32,it1->first);PACKET_ENCODE(Bool,it1->second);}
}
PACKET_ENCODE(UVar32,startTime_.size());
for(map<int32_t, int64_t>::const_iterator it=startTime_.begin();it!=startTime_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int64,it->second);}
PACKET_ENCODE(UVar32,endTime_.size());
for(map<int32_t, int64_t>::const_iterator it=endTime_.begin();it!=endTime_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int64,it->second);}
return true;}
void SActiveInvest::clear(){
activeId_ = 0;
gotRewardMap_.clear();
startTime_.clear();
endTime_.clear();
}
bool SDirectBuyGift::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);buyMap_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);gotRewardMap_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);dayRewardMap_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);discountMoney_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);dayRewardTotal_[k] = v;}}
return true;}
bool SDirectBuyGift::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,buyMap_.size());
for(map<int32_t, int32_t>::const_iterator it=buyMap_.begin();it!=buyMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,gotRewardMap_.size());
for(map<int32_t, int32_t>::const_iterator it=gotRewardMap_.begin();it!=gotRewardMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,dayRewardMap_.size());
for(map<int32_t, int32_t>::const_iterator it=dayRewardMap_.begin();it!=dayRewardMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,discountMoney_.size());
for(map<int32_t, int32_t>::const_iterator it=discountMoney_.begin();it!=discountMoney_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,dayRewardTotal_.size());
for(map<int32_t, int32_t>::const_iterator it=dayRewardTotal_.begin();it!=dayRewardTotal_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SDirectBuyGift::clear(){
activeId_ = 0;
buyMap_.clear();
gotRewardMap_.clear();
dayRewardMap_.clear();
discountMoney_.clear();
dayRewardTotal_.clear();
}
bool SGroupBuyGift::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;msgs::SInts v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}buyMap_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;msgs::SIntIntMap v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}getMap_[k] = v;}}
PACKET_DECODE(Int32,totalConsume_);
return true;}
bool SGroupBuyGift::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,buyMap_.size());
for(map<int32_t, msgs::SInts>::const_iterator it=buyMap_.begin();it!=buyMap_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
PACKET_ENCODE(UVar32,getMap_.size());
for(map<int32_t, msgs::SIntIntMap>::const_iterator it=getMap_.begin();it!=getMap_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
PACKET_ENCODE(Int32,totalConsume_);
return true;}
void SGroupBuyGift::clear(){
activeId_ = 0;
buyMap_.clear();
getMap_.clear();
totalConsume_ = 0;
}
bool SPlayerPuzzle::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
PACKET_DECODE(Int32,lightCount_);
PACKET_DECODE(Int32,helpCount_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);isActive_[k] = v;}}
return true;}
bool SPlayerPuzzle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(Int32,lightCount_);
PACKET_ENCODE(Int32,helpCount_);
PACKET_ENCODE(UVar32,isActive_.size());
for(map<int32_t, bool>::const_iterator it=isActive_.begin();it!=isActive_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
return true;}
void SPlayerPuzzle::clear(){
activeId_ = 0;
lightCount_ = 0;
helpCount_ = 0;
isActive_.clear();
}
bool SPuzzleRecordSingle::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,updateDt_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,count_);
return true;}
bool SPuzzleRecordSingle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,updateDt_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,count_);
return true;}
void SPuzzleRecordSingle::clear(){
updateDt_ = 0;
name_.clear();
count_ = 0;
}
bool SPuzzleRecord::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SPuzzleRecordSingle item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}records_.push_back(item);}}
return true;}
bool SPuzzleRecord::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,records_.size());
for(vector<SPuzzleRecordSingle>::const_iterator vit=records_.begin();vit!=records_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPuzzleRecord::clear(){
activeId_ = 0;
records_.clear();
}
bool SActivePuzzleData::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
PACKET_DECODE(Int32,puzzleId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;msgs::SIntBoolMap v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}puzzleMap_[k] = v;}}
PACKET_DECODE(Int32,beHelpCount_);
if(!helpRecords_.decode(reader)){return false;}
return true;}
bool SActivePuzzleData::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(Int32,puzzleId_);
PACKET_ENCODE(UVar32,puzzleMap_.size());
for(map<int32_t, msgs::SIntBoolMap>::const_iterator it=puzzleMap_.begin();it!=puzzleMap_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
PACKET_ENCODE(Int32,beHelpCount_);
if(!helpRecords_.encode(writer)){return false;}
return true;}
void SActivePuzzleData::clear(){
activeId_ = 0;
puzzleId_ = 0;
puzzleMap_.clear();
beHelpCount_ = 0;
helpRecords_.clear();
}
bool SActiveZhiBaoTarget::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);hasGotReward_[k] = v;}}
return true;}
bool SActiveZhiBaoTarget::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,hasGotReward_.size());
for(map<int32_t, int32_t>::const_iterator it=hasGotReward_.begin();it!=hasGotReward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SActiveZhiBaoTarget::clear(){
activeId_ = 0;
hasGotReward_.clear();
}
bool SKeepPrivilege::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
PACKET_DECODE(Int64,endDt_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){string k;bool v;PACKET_DECODE(String,k);PACKET_DECODE(Bool,v);gotRewards_[k] = v;}}
return true;}
bool SKeepPrivilege::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(Int64,endDt_);
PACKET_ENCODE(UVar32,gotRewards_.size());
for(map<string, bool>::const_iterator it=gotRewards_.begin();it!=gotRewards_.end();++it){PACKET_ENCODE(String,it->first);PACKET_ENCODE(Bool,it->second);}
return true;}
void SKeepPrivilege::clear(){
activeId_ = 0;
endDt_ = 0;
gotRewards_.clear();
}
bool SActiveFreeTreasure::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);selectTreasures_.push_back(item);}}
PACKET_DECODE(Int32,treasureCount_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);hasGotTarget_[k] = v;}}
return true;}
bool SActiveFreeTreasure::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,selectTreasures_.size());
for(vector<int32_t>::const_iterator vit=selectTreasures_.begin();vit!=selectTreasures_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(Int32,treasureCount_);
PACKET_ENCODE(UVar32,hasGotTarget_.size());
for(map<int32_t, int32_t>::const_iterator it=hasGotTarget_.begin();it!=hasGotTarget_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SActiveFreeTreasure::clear(){
activeId_ = 0;
selectTreasures_.clear();
treasureCount_ = 0;
hasGotTarget_.clear();
}
bool SActiveRechargeBless::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);rechargeMap_.push_back(item);}}
PACKET_DECODE(Int32,blessCount_);
PACKET_DECODE(Int32,curPer_);
PACKET_DECODE(Int32,totalCount_);
return true;}
bool SActiveRechargeBless::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,rechargeMap_.size());
for(vector<int32_t>::const_iterator vit=rechargeMap_.begin();vit!=rechargeMap_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(Int32,blessCount_);
PACKET_ENCODE(Int32,curPer_);
PACKET_ENCODE(Int32,totalCount_);
return true;}
void SActiveRechargeBless::clear(){
activeId_ = 0;
rechargeMap_.clear();
blessCount_ = 0;
curPer_ = 0;
totalCount_ = 0;
}
bool SActiveFlowerTreasure::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);targetRewards_[k] = v;}}
return true;}
bool SActiveFlowerTreasure::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,targetRewards_.size());
for(map<int32_t, bool>::const_iterator it=targetRewards_.begin();it!=targetRewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
return true;}
void SActiveFlowerTreasure::clear(){
activeId_ = 0;
targetRewards_.clear();
}
bool SActiveScrapeReward::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int64_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int64,v);startTime_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;msgs::SIntIntMap v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}numberMap_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;msgs::SIntBoolMap v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}rewardMap_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);finalRewardNum_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);usedFreeNum_[k] = v;}}
return true;}
bool SActiveScrapeReward::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,startTime_.size());
for(map<int32_t, int64_t>::const_iterator it=startTime_.begin();it!=startTime_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int64,it->second);}
PACKET_ENCODE(UVar32,numberMap_.size());
for(map<int32_t, msgs::SIntIntMap>::const_iterator it=numberMap_.begin();it!=numberMap_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
PACKET_ENCODE(UVar32,rewardMap_.size());
for(map<int32_t, msgs::SIntBoolMap>::const_iterator it=rewardMap_.begin();it!=rewardMap_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
PACKET_ENCODE(UVar32,finalRewardNum_.size());
for(map<int32_t, int32_t>::const_iterator it=finalRewardNum_.begin();it!=finalRewardNum_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,usedFreeNum_.size());
for(map<int32_t, int32_t>::const_iterator it=usedFreeNum_.begin();it!=usedFreeNum_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SActiveScrapeReward::clear(){
activeId_ = 0;
startTime_.clear();
numberMap_.clear();
rewardMap_.clear();
finalRewardNum_.clear();
usedFreeNum_.clear();
}
bool SActiveCallBack::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);hasGotReward_[k] = v;}}
PACKET_DECODE(Int32,totalRecharge_);
PACKET_DECODE(Int32,seqRechargeCount_);
PACKET_DECODE(Int32,backDay_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);callerHasGotReward_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);callerTotalRecharge_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);callerSeqRechargeCount_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);callerBackDay_[k] = v;}}
PACKET_DECODE(Int32,callCount_);
return true;}
bool SActiveCallBack::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,hasGotReward_.size());
for(map<int32_t, int32_t>::const_iterator it=hasGotReward_.begin();it!=hasGotReward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,totalRecharge_);
PACKET_ENCODE(Int32,seqRechargeCount_);
PACKET_ENCODE(Int32,backDay_);
PACKET_ENCODE(UVar32,callerHasGotReward_.size());
for(map<int32_t, int32_t>::const_iterator it=callerHasGotReward_.begin();it!=callerHasGotReward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,callerTotalRecharge_.size());
for(map<int32_t, int32_t>::const_iterator it=callerTotalRecharge_.begin();it!=callerTotalRecharge_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,callerSeqRechargeCount_.size());
for(map<int32_t, int32_t>::const_iterator it=callerSeqRechargeCount_.begin();it!=callerSeqRechargeCount_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,callerBackDay_.size());
for(map<int32_t, int32_t>::const_iterator it=callerBackDay_.begin();it!=callerBackDay_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,callCount_);
return true;}
void SActiveCallBack::clear(){
activeId_ = 0;
hasGotReward_.clear();
totalRecharge_ = 0;
seqRechargeCount_ = 0;
backDay_ = 0;
callerHasGotReward_.clear();
callerTotalRecharge_.clear();
callerSeqRechargeCount_.clear();
callerBackDay_.clear();
callCount_ = 0;
}
bool SActiveSevenDayHigh::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);dayRewards_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);targetRewards_[k] = v;}}
PACKET_DECODE(Int32,day_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;map<int32_t, int32_t> v;PACKET_DECODE(Int32,k);{uint32_t len1=0;PACKET_DECODE(UVar32,len1);for(uint32_t i1=0;i1<len1;++i1){int32_t k1;int32_t v1;PACKET_DECODE(Int32,k1);PACKET_DECODE(Int32,v1);v[k1] = v1;}}
mapValue_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);intValue_[k] = v;}}
return true;}
bool SActiveSevenDayHigh::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,dayRewards_.size());
for(map<int32_t, int32_t>::const_iterator it=dayRewards_.begin();it!=dayRewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,targetRewards_.size());
for(map<int32_t, int32_t>::const_iterator it=targetRewards_.begin();it!=targetRewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,day_);
PACKET_ENCODE(UVar32,mapValue_.size());
for(map<int32_t, map<int32_t, int32_t> >::const_iterator it=mapValue_.begin();it!=mapValue_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(UVar32,it->second.size());
for(map<int32_t, int32_t>::const_iterator it1=it->second.begin();it1!=it->second.end();++it1){PACKET_ENCODE(Int32,it1->first);PACKET_ENCODE(Int32,it1->second);}
}
PACKET_ENCODE(UVar32,intValue_.size());
for(map<int32_t, int32_t>::const_iterator it=intValue_.begin();it!=intValue_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SActiveSevenDayHigh::clear(){
activeId_ = 0;
dayRewards_.clear();
targetRewards_.clear();
day_ = 0;
mapValue_.clear();
intValue_.clear();
}
bool SCopyDropRateInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rateMap_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int64_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int64,v);endTime_[k] = v;}}
return true;}
bool SCopyDropRateInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,rateMap_.size());
for(map<int32_t, int32_t>::const_iterator it=rateMap_.begin();it!=rateMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,endTime_.size());
for(map<int32_t, int64_t>::const_iterator it=endTime_.begin();it!=endTime_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int64,it->second);}
return true;}
void SCopyDropRateInfo::clear(){
rateMap_.clear();
endTime_.clear();
}
bool SActiveTopicCollected::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);targetRewards_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;map<int32_t, int32_t> v;PACKET_DECODE(Int32,k);{uint32_t len1=0;PACKET_DECODE(UVar32,len1);for(uint32_t i1=0;i1<len1;++i1){int32_t k1;int32_t v1;PACKET_DECODE(Int32,k1);PACKET_DECODE(Int32,v1);v[k1] = v1;}}
mapValue_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);intValue_[k] = v;}}
return true;}
bool SActiveTopicCollected::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,targetRewards_.size());
for(map<int32_t, int32_t>::const_iterator it=targetRewards_.begin();it!=targetRewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,mapValue_.size());
for(map<int32_t, map<int32_t, int32_t> >::const_iterator it=mapValue_.begin();it!=mapValue_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(UVar32,it->second.size());
for(map<int32_t, int32_t>::const_iterator it1=it->second.begin();it1!=it->second.end();++it1){PACKET_ENCODE(Int32,it1->first);PACKET_ENCODE(Int32,it1->second);}
}
PACKET_ENCODE(UVar32,intValue_.size());
for(map<int32_t, int32_t>::const_iterator it=intValue_.begin();it!=intValue_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SActiveTopicCollected::clear(){
activeId_ = 0;
targetRewards_.clear();
mapValue_.clear();
intValue_.clear();
}
bool SActiveTripleTreasure::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);activeMap_[k] = v;}}
return true;}
bool SActiveTripleTreasure::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,activeMap_.size());
for(map<int32_t, bool>::const_iterator it=activeMap_.begin();it!=activeMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
return true;}
void SActiveTripleTreasure::clear(){
activeId_ = 0;
activeMap_.clear();
}
bool SPlayerDujieInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,rewardCount_);
PACKET_DECODE(Int32,timeCount_);
return true;}
bool SPlayerDujieInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,rewardCount_);
PACKET_ENCODE(Int32,timeCount_);
return true;}
void SPlayerDujieInfo::clear(){
level_ = 0;
rewardCount_ = 0;
timeCount_ = 0;
}
bool SPlayerBag::decode(CBufferReader &reader) {
PACKET_DECODE(Int16,type_);
PACKET_DECODE(Int16,privilegeNum_);
PACKET_DECODE(Int16,extendNum_);
PACKET_DECODE(Int32,extendMinute_);
return true;}
bool SPlayerBag::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int16,type_);
PACKET_ENCODE(Int16,privilegeNum_);
PACKET_ENCODE(Int16,extendNum_);
PACKET_ENCODE(Int32,extendMinute_);
return true;}
void SPlayerBag::clear(){
type_ = 0;
privilegeNum_ = 0;
extendNum_ = 0;
extendMinute_ = 0;
}
bool SPlayerItem::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,itemUid_);
PACKET_DECODE(Int32,itemId_);
PACKET_DECODE(Int32,itemNum_);
PACKET_DECODE(Int16,bagType_);
PACKET_DECODE(String,extend_);
PACKET_DECODE(Int64,createDt_);
return true;}
bool SPlayerItem::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,itemUid_);
PACKET_ENCODE(Int32,itemId_);
PACKET_ENCODE(Int32,itemNum_);
PACKET_ENCODE(Int16,bagType_);
PACKET_ENCODE(String,extend_);
PACKET_ENCODE(Int64,createDt_);
return true;}
void SPlayerItem::clear(){
itemUid_ = 0;
itemId_ = 0;
itemNum_ = 0;
bagType_ = 0;
extend_.clear();
createDt_ = 0;
}
bool SPlayerBagList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SPlayerBag item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}bags_.push_back(item);}}
return true;}
bool SPlayerBagList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,bags_.size());
for(vector<SPlayerBag>::const_iterator vit=bags_.begin();vit!=bags_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerBagList::clear(){
bags_.clear();
}
bool SPlayerBagItemList::decode(CBufferReader &reader) {
PACKET_DECODE(Int16,bagType_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SPlayerItem item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}items_.push_back(item);}}
return true;}
bool SPlayerBagItemList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int16,bagType_);
PACKET_ENCODE(UVar32,items_.size());
for(vector<SPlayerItem>::const_iterator vit=items_.begin();vit!=items_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerBagItemList::clear(){
bagType_ = 0;
items_.clear();
}
bool SPlayerBagItemOper::decode(CBufferReader &reader) {
PACKET_DECODE(Int16,operType_);
PACKET_DECODE(Int32,operNum_);
if(!item_.decode(reader)){return false;}
return true;}
bool SPlayerBagItemOper::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int16,operType_);
PACKET_ENCODE(Int32,operNum_);
if(!item_.encode(writer)){return false;}
return true;}
void SPlayerBagItemOper::clear(){
operType_ = 0;
operNum_ = 0;
item_.clear();
}
bool SPlayerBagItemOperList::decode(CBufferReader &reader) {
PACKET_DECODE(Int16,updateCode_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SPlayerBagItemOper item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}opers_.push_back(item);}}
return true;}
bool SPlayerBagItemOperList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int16,updateCode_);
PACKET_ENCODE(UVar32,opers_.size());
for(vector<SPlayerBagItemOper>::const_iterator vit=opers_.begin();vit!=opers_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerBagItemOperList::clear(){
updateCode_ = 0;
opers_.clear();
}
bool SPlayerMoneyList::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int64_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int64,v);moneys_[k] = v;}}
return true;}
bool SPlayerMoneyList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,moneys_.size());
for(map<int32_t, int64_t>::const_iterator it=moneys_.begin();it!=moneys_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int64,it->second);}
return true;}
void SPlayerMoneyList::clear(){
moneys_.clear();
}
bool SPlayerMoneyOper::decode(CBufferReader &reader) {
PACKET_DECODE(Int16,operType_);
PACKET_DECODE(Int32,operNum_);
PACKET_DECODE(Int32,moneyId_);
PACKET_DECODE(Int64,moneyNum_);
return true;}
bool SPlayerMoneyOper::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int16,operType_);
PACKET_ENCODE(Int32,operNum_);
PACKET_ENCODE(Int32,moneyId_);
PACKET_ENCODE(Int64,moneyNum_);
return true;}
void SPlayerMoneyOper::clear(){
operType_ = 0;
operNum_ = 0;
moneyId_ = 0;
moneyNum_ = 0;
}
bool SPlayerMoneyOperList::decode(CBufferReader &reader) {
PACKET_DECODE(Int16,updateCode_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SPlayerMoneyOper item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}opers_.push_back(item);}}
return true;}
bool SPlayerMoneyOperList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int16,updateCode_);
PACKET_ENCODE(UVar32,opers_.size());
for(vector<SPlayerMoneyOper>::const_iterator vit=opers_.begin();vit!=opers_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerMoneyOperList::clear(){
updateCode_ = 0;
opers_.clear();
}
bool SPlayerConsume::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,totalConsumeGold_);
PACKET_DECODE(Int32,todayConsumeGold_);
return true;}
bool SPlayerConsume::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,totalConsumeGold_);
PACKET_ENCODE(Int32,todayConsumeGold_);
return true;}
void SPlayerConsume::clear(){
totalConsumeGold_ = 0;
todayConsumeGold_ = 0;
}
bool SPlayerItemExpires::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);items_.push_back(item);}}
return true;}
bool SPlayerItemExpires::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,items_.size());
for(vector<int32_t>::const_iterator vit=items_.begin();vit!=items_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SPlayerItemExpires::clear(){
items_.clear();
}
bool SPlayerEquipList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);dbs::TPlayerEquip item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}equips_.push_back(item);}}
return true;}
bool SPlayerEquipList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,equips_.size());
for(vector<dbs::TPlayerEquip>::const_iterator vit=equips_.begin();vit!=equips_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerEquipList::clear(){
equips_.clear();
}
bool SPlayerGemTargets::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;map<int32_t, int32_t> v;PACKET_DECODE(Int32,k);{uint32_t len1=0;PACKET_DECODE(UVar32,len1);for(uint32_t i1=0;i1<len1;++i1){int32_t k1;int32_t v1;PACKET_DECODE(Int32,k1);PACKET_DECODE(Int32,v1);v[k1] = v1;}}
activateTargets_[k] = v;}}
return true;}
bool SPlayerGemTargets::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,activateTargets_.size());
for(map<int32_t, map<int32_t, int32_t> >::const_iterator it=activateTargets_.begin();it!=activateTargets_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(UVar32,it->second.size());
for(map<int32_t, int32_t>::const_iterator it1=it->second.begin();it1!=it->second.end();++it1){PACKET_ENCODE(Int32,it1->first);PACKET_ENCODE(Int32,it1->second);}
}
return true;}
void SPlayerGemTargets::clear(){
activateTargets_.clear();
}
bool SPlayerRefineTargets::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;map<int32_t, int32_t> v;PACKET_DECODE(Int32,k);{uint32_t len1=0;PACKET_DECODE(UVar32,len1);for(uint32_t i1=0;i1<len1;++i1){int32_t k1;int32_t v1;PACKET_DECODE(Int32,k1);PACKET_DECODE(Int32,v1);v[k1] = v1;}}
activateTargets_[k] = v;}}
return true;}
bool SPlayerRefineTargets::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,activateTargets_.size());
for(map<int32_t, map<int32_t, int32_t> >::const_iterator it=activateTargets_.begin();it!=activateTargets_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(UVar32,it->second.size());
for(map<int32_t, int32_t>::const_iterator it1=it->second.begin();it1!=it->second.end();++it1){PACKET_ENCODE(Int32,it1->first);PACKET_ENCODE(Int32,it1->second);}
}
return true;}
void SPlayerRefineTargets::clear(){
activateTargets_.clear();
}
bool SCosmosRefineTargets::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;vector<int32_t> v;PACKET_DECODE(Int32,k);{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);v.push_back(item);}}
targets_[k] = v;}}
return true;}
bool SCosmosRefineTargets::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,targets_.size());
for(map<int32_t, vector<int32_t> >::const_iterator it=targets_.begin();it!=targets_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(UVar32,it->second.size());
for(vector<int32_t>::const_iterator vit=it->second.begin();vit!=it->second.end();++vit){PACKET_ENCODE(Int32,*vit);}
}
return true;}
void SCosmosRefineTargets::clear(){
targets_.clear();
}
bool SPlayerSuitCollects::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;map<int32_t, int32_t> v;PACKET_DECODE(Int32,k);{uint32_t len1=0;PACKET_DECODE(UVar32,len1);for(uint32_t i1=0;i1<len1;++i1){int32_t k1;int32_t v1;PACKET_DECODE(Int32,k1);PACKET_DECODE(Int32,v1);v[k1] = v1;}}
activeSuitCollect_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);unlockSuitCollect_[k] = v;}}
return true;}
bool SPlayerSuitCollects::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(UVar32,activeSuitCollect_.size());
for(map<int32_t, map<int32_t, int32_t> >::const_iterator it=activeSuitCollect_.begin();it!=activeSuitCollect_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(UVar32,it->second.size());
for(map<int32_t, int32_t>::const_iterator it1=it->second.begin();it1!=it->second.end();++it1){PACKET_ENCODE(Int32,it1->first);PACKET_ENCODE(Int32,it1->second);}
}
PACKET_ENCODE(UVar32,unlockSuitCollect_.size());
for(map<int32_t, int32_t>::const_iterator it=unlockSuitCollect_.begin();it!=unlockSuitCollect_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SPlayerSuitCollects::clear(){
roleId_ = 0;
activeSuitCollect_.clear();
unlockSuitCollect_.clear();
}
bool SPlayerActiveSuitCollect::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int32,suitId_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);activeSlots_.push_back(item);}}
return true;}
bool SPlayerActiveSuitCollect::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int32,suitId_);
PACKET_ENCODE(UVar32,activeSlots_.size());
for(vector<int32_t>::const_iterator vit=activeSlots_.begin();vit!=activeSlots_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SPlayerActiveSuitCollect::clear(){
roleId_ = 0;
suitId_ = 0;
activeSlots_.clear();
}
bool SPlayerUnlockSuitCollect::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int32,suitId_);
return true;}
bool SPlayerUnlockSuitCollect::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int32,suitId_);
return true;}
void SPlayerUnlockSuitCollect::clear(){
roleId_ = 0;
suitId_ = 0;
}
bool SPlayerDressSuitCollect::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int32,dressSuitId_);
return true;}
bool SPlayerDressSuitCollect::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int32,dressSuitId_);
return true;}
void SPlayerDressSuitCollect::clear(){
roleId_ = 0;
dressSuitId_ = 0;
}
bool SRingWash::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,index_);
PACKET_DECODE(Int32,bless_);
PACKET_DECODE(Int32,targetLevel_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);holes_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);tmpHoles_[k] = v;}}
return true;}
bool SRingWash::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,index_);
PACKET_ENCODE(Int32,bless_);
PACKET_ENCODE(Int32,targetLevel_);
PACKET_ENCODE(UVar32,holes_.size());
for(map<int32_t, int32_t>::const_iterator it=holes_.begin();it!=holes_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,tmpHoles_.size());
for(map<int32_t, int32_t>::const_iterator it=tmpHoles_.begin();it!=tmpHoles_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SRingWash::clear(){
index_ = 0;
bless_ = 0;
targetLevel_ = 0;
holes_.clear();
tmpHoles_.clear();
}
bool SPlayerRingWash::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SRingWash v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}ringWashes_[k] = v;}}
return true;}
bool SPlayerRingWash::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,ringWashes_.size());
for(map<int32_t, SRingWash>::const_iterator it=ringWashes_.begin();it!=ringWashes_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SPlayerRingWash::clear(){
ringWashes_.clear();
}
bool SPlayerReincarnMark::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;msgs::SIntIntMap v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}maps_[k] = v;}}
return true;}
bool SPlayerReincarnMark::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,maps_.size());
for(map<int32_t, msgs::SIntIntMap>::const_iterator it=maps_.begin();it!=maps_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SPlayerReincarnMark::clear(){
maps_.clear();
}
bool SPlayerAvatar::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,avatarId_);
PACKET_DECODE(Int32,exp_);
PACKET_DECODE(Int32,avatarStar_);
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,star_);
PACKET_DECODE(Int64,initDt_);
return true;}
bool SPlayerAvatar::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,avatarId_);
PACKET_ENCODE(Int32,exp_);
PACKET_ENCODE(Int32,avatarStar_);
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,star_);
PACKET_ENCODE(Int64,initDt_);
return true;}
void SPlayerAvatar::clear(){
avatarId_ = 0;
exp_ = 0;
avatarStar_ = 0;
level_ = 0;
star_ = 0;
initDt_ = 0;
}
bool SPlayerAvatarInfo::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SPlayerAvatar item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}avatars_.push_back(item);}}
return true;}
bool SPlayerAvatarInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,avatars_.size());
for(vector<SPlayerAvatar>::const_iterator vit=avatars_.begin();vit!=avatars_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerAvatarInfo::clear(){
avatars_.clear();
}
bool SAvatarTrump::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,status_);
PACKET_DECODE(Int32,advance_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);posAdv_[k] = v;}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);activeAvd_.push_back(item);}}
PACKET_DECODE(Bool,activeCore_);
return true;}
bool SAvatarTrump::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,status_);
PACKET_ENCODE(Int32,advance_);
PACKET_ENCODE(UVar32,posAdv_.size());
for(map<int32_t, int32_t>::const_iterator it=posAdv_.begin();it!=posAdv_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,activeAvd_.size());
for(vector<int32_t>::const_iterator vit=activeAvd_.begin();vit!=activeAvd_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(Bool,activeCore_);
return true;}
void SAvatarTrump::clear(){
status_ = 0;
advance_ = 0;
posAdv_.clear();
activeAvd_.clear();
activeCore_ = 0;
}
bool SAvatarTrumpInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,puton_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SAvatarTrump v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}trumps_[k] = v;}}
return true;}
bool SAvatarTrumpInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,puton_);
PACKET_ENCODE(UVar32,trumps_.size());
for(map<int32_t, SAvatarTrump>::const_iterator it=trumps_.begin();it!=trumps_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SAvatarTrumpInfo::clear(){
puton_ = 0;
trumps_.clear();
}
bool SAvatarHangInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,hangId_);
return true;}
bool SAvatarHangInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,hangId_);
return true;}
void SAvatarHangInfo::clear(){
hangId_ = 0;
}
bool SDragonSoulSingle::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,id_);
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,star_);
PACKET_DECODE(Bool,out_);
return true;}
bool SDragonSoulSingle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,id_);
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,star_);
PACKET_ENCODE(Bool,out_);
return true;}
void SDragonSoulSingle::clear(){
id_ = 0;
level_ = 0;
star_ = 0;
out_ = 0;
}
bool SDragonSoulInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SDragonSoulSingle v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}dsMap_[k] = v;}}
PACKET_DECODE(Int32,outNum_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);target_[k] = v;}}
return true;}
bool SDragonSoulInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,dsMap_.size());
for(map<int32_t, SDragonSoulSingle>::const_iterator it=dsMap_.begin();it!=dsMap_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
PACKET_ENCODE(Int32,outNum_);
PACKET_ENCODE(UVar32,target_.size());
for(map<int32_t, bool>::const_iterator it=target_.begin();it!=target_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
return true;}
void SDragonSoulInfo::clear(){
dsMap_.clear();
outNum_ = 0;
target_.clear();
}
bool SShopInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);limitSellsDay_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);limitSellsWeek_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);limitSellsForever_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);limitSellsWeekActive_[k] = v;}}
return true;}
bool SShopInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,limitSellsDay_.size());
for(map<int32_t, int32_t>::const_iterator it=limitSellsDay_.begin();it!=limitSellsDay_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,limitSellsWeek_.size());
for(map<int32_t, int32_t>::const_iterator it=limitSellsWeek_.begin();it!=limitSellsWeek_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,limitSellsForever_.size());
for(map<int32_t, int32_t>::const_iterator it=limitSellsForever_.begin();it!=limitSellsForever_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,limitSellsWeekActive_.size());
for(map<int32_t, int32_t>::const_iterator it=limitSellsWeekActive_.begin();it!=limitSellsWeekActive_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SShopInfo::clear(){
limitSellsDay_.clear();
limitSellsWeek_.clear();
limitSellsForever_.clear();
limitSellsWeekActive_.clear();
}
bool SPlayerShanHai::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);activeCollects_[k] = v;}}
return true;}
bool SPlayerShanHai::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,activeCollects_.size());
for(map<int32_t, int32_t>::const_iterator it=activeCollects_.begin();it!=activeCollects_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SPlayerShanHai::clear(){
activeCollects_.clear();
}
bool SXiuXianHole::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,layer_);
PACKET_DECODE(Int32,playerNum_);
PACKET_DECODE(Bool,isActive_);
return true;}
bool SXiuXianHole::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,layer_);
PACKET_ENCODE(Int32,playerNum_);
PACKET_ENCODE(Bool,isActive_);
return true;}
void SXiuXianHole::clear(){
layer_ = 0;
playerNum_ = 0;
isActive_ = 0;
}
bool SXiuXianHoleList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SXiuXianHole item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool SXiuXianHoleList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<SXiuXianHole>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SXiuXianHoleList::clear(){
list_.clear();
}
bool SXiuXianHoleResult::decode(CBufferReader &reader) {
if(!msgs::SCompleteCopy::decode(reader)){return false;}
return true;}
bool SXiuXianHoleResult::encode(CBufferWriter &writer) const {
if(!msgs::SCompleteCopy::encode(writer)){return false;}
return true;}
void SXiuXianHoleResult::clear(){
}
bool SXiuXianHoleBagItemList::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);itemList_[k] = v;}}
return true;}
bool SXiuXianHoleBagItemList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,itemList_.size());
for(map<int32_t, int32_t>::const_iterator it=itemList_.begin();it!=itemList_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SXiuXianHoleBagItemList::clear(){
itemList_.clear();
}
bool SXiuXianHoleFuDi::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,pointId_);
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int64,combat_);
PACKET_DECODE(Int64,protectDt_);
return true;}
bool SXiuXianHoleFuDi::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,pointId_);
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(Int64,protectDt_);
return true;}
void SXiuXianHoleFuDi::clear(){
pointId_ = 0;
entityId_.clear();
name_.clear();
combat_ = 0;
protectDt_ = 0;
}
bool SXiuXianHoleFuDiList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SXiuXianHoleFuDi item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool SXiuXianHoleFuDiList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<SXiuXianHoleFuDi>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SXiuXianHoleFuDiList::clear(){
list_.clear();
}
bool SXiuXianHoleRankList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);dbs::TXiuXianHoleRank item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
PACKET_DECODE(Int32,xianYuan_);
return true;}
bool SXiuXianHoleRankList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<dbs::TXiuXianHoleRank>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(Int32,xianYuan_);
return true;}
void SXiuXianHoleRankList::clear(){
list_.clear();
xianYuan_ = 0;
}
bool SXiuXianHoleCopyInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,layer_);
PACKET_DECODE(Int32,playerNum_);
PACKET_DECODE(Int64,doubleEndDt_);
PACKET_DECODE(Int32,holdId_);
PACKET_DECODE(Int32,leftDouble_);
return true;}
bool SXiuXianHoleCopyInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,layer_);
PACKET_ENCODE(Int32,playerNum_);
PACKET_ENCODE(Int64,doubleEndDt_);
PACKET_ENCODE(Int32,holdId_);
PACKET_ENCODE(Int32,leftDouble_);
return true;}
void SXiuXianHoleCopyInfo::clear(){
layer_ = 0;
playerNum_ = 0;
doubleEndDt_ = 0;
holdId_ = 0;
leftDouble_ = 0;
}
bool SXiuxianInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,star_);
PACKET_DECODE(Int32,gotLevel_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);itemCount_[k] = v;}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);targets_.push_back(item);}}
return true;}
bool SXiuxianInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,star_);
PACKET_ENCODE(Int32,gotLevel_);
PACKET_ENCODE(UVar32,itemCount_.size());
for(map<int32_t, int32_t>::const_iterator it=itemCount_.begin();it!=itemCount_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,targets_.size());
for(vector<int32_t>::const_iterator vit=targets_.begin();vit!=targets_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SXiuxianInfo::clear(){
level_ = 0;
star_ = 0;
gotLevel_ = 0;
itemCount_.clear();
targets_.clear();
}
bool SXiuxianGem::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,item_);
PACKET_DECODE(Int32,level_);
return true;}
bool SXiuxianGem::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,item_);
PACKET_ENCODE(Int32,level_);
return true;}
void SXiuxianGem::clear(){
item_ = 0;
level_ = 0;
}
bool SXiuxianGemInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;map<int32_t, SXiuxianGem> v;PACKET_DECODE(Int32,k);{uint32_t len1=0;PACKET_DECODE(UVar32,len1);for(uint32_t i1=0;i1<len1;++i1){int32_t k1;SXiuxianGem v1;PACKET_DECODE(Int32,k1);if(!v1.decode(reader)){return false;}v[k1] = v1;}}
gemMap_[k] = v;}}
return true;}
bool SXiuxianGemInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,gemMap_.size());
for(map<int32_t, map<int32_t, SXiuxianGem> >::const_iterator it=gemMap_.begin();it!=gemMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(UVar32,it->second.size());
for(map<int32_t, SXiuxianGem>::const_iterator it1=it->second.begin();it1!=it->second.end();++it1){PACKET_ENCODE(Int32,it1->first);if(!it1->second.encode(writer)){return false;}}
}
return true;}
void SXiuxianGemInfo::clear(){
gemMap_.clear();
}
bool SMarryRequest::decode(CBufferReader &reader) {
if(!player_.decode(reader)){return false;}
PACKET_DECODE(Int32,type_);
return true;}
bool SMarryRequest::encode(CBufferWriter &writer) const {
if(!player_.encode(writer)){return false;}
PACKET_ENCODE(Int32,type_);
return true;}
void SMarryRequest::clear(){
player_.clear();
type_ = 0;
}
bool SMarryRespone::decode(CBufferReader &reader) {
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,result_);
return true;}
bool SMarryRespone::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,result_);
return true;}
void SMarryRespone::clear(){
name_.clear();
result_ = 0;
}
bool SPlayerMarry::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,marryId_);
PACKET_DECODE(Int64,marryDt_);
if(!mate_.decode(reader)){return false;}
PACKET_DECODE(Int32,divorceId_);
PACKET_DECODE(Int64,divorceDt_);
return true;}
bool SPlayerMarry::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,marryId_);
PACKET_ENCODE(Int64,marryDt_);
if(!mate_.encode(writer)){return false;}
PACKET_ENCODE(Int32,divorceId_);
PACKET_ENCODE(Int64,divorceDt_);
return true;}
void SPlayerMarry::clear(){
marryId_ = 0;
marryDt_ = 0;
mate_.clear();
divorceId_ = 0;
divorceDt_ = 0;
}
bool SPlayerWedding::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,marryId_);
PACKET_DECODE(Int32,weddingStatus_);
PACKET_DECODE(Int64,bookDt_);
PACKET_DECODE(Int32,guestNum_);
PACKET_DECODE(Int32,weddingCount_);
return true;}
bool SPlayerWedding::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,marryId_);
PACKET_ENCODE(Int32,weddingStatus_);
PACKET_ENCODE(Int64,bookDt_);
PACKET_ENCODE(Int32,guestNum_);
PACKET_ENCODE(Int32,weddingCount_);
return true;}
void SPlayerWedding::clear(){
marryId_ = 0;
weddingStatus_ = 0;
bookDt_ = 0;
guestNum_ = 0;
weddingCount_ = 0;
}
bool SGatePlayerMarry::decode(CBufferReader &reader) {
PACKET_DECODE(Bool,mateOnline_);
PACKET_DECODE(Int32,matelockLevel_);
PACKET_DECODE(Int64,mateAttack_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);myReqNum_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);mateReqNum_[k] = v;}}
marry_ = MsgPool::Instance()->DecodeMsg(reader);
wedding_ = MsgPool::Instance()->DecodeMsg(reader);
return true;}
bool SGatePlayerMarry::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Bool,mateOnline_);
PACKET_ENCODE(Int32,matelockLevel_);
PACKET_ENCODE(Int64,mateAttack_);
PACKET_ENCODE(UVar32,myReqNum_.size());
for(map<int32_t, int32_t>::const_iterator it=myReqNum_.begin();it!=myReqNum_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,mateReqNum_.size());
for(map<int32_t, int32_t>::const_iterator it=mateReqNum_.begin();it!=mateReqNum_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
if(!MsgPool::Instance()->EncodeMsg(writer, marry_)){return false;}
if(!MsgPool::Instance()->EncodeMsg(writer, wedding_)){return false;}
return true;}
void SGatePlayerMarry::clear(){
mateOnline_ = 0;
matelockLevel_ = 0;
mateAttack_ = 0;
myReqNum_.clear();
mateReqNum_.clear();
marry_ = NULL;
wedding_ = NULL;
}
bool SPlayerMarryRequestInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);myReqNum_[k] = v;}}
return true;}
bool SPlayerMarryRequestInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,myReqNum_.size());
for(map<int32_t, int32_t>::const_iterator it=myReqNum_.begin();it!=myReqNum_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SPlayerMarryRequestInfo::clear(){
myReqNum_.clear();
}
bool SWeddingBookList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);bookDts_.push_back(item);}}
return true;}
bool SWeddingBookList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,bookDts_.size());
for(vector<int32_t>::const_iterator vit=bookDts_.begin();vit!=bookDts_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SWeddingBookList::clear(){
bookDts_.clear();
}
bool SWeddingGuest::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;string v;PACKET_DECODE(Int32,k);PACKET_DECODE(String,v);guestList_[k] = v;}}
return true;}
bool SWeddingGuest::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,guestList_.size());
for(map<int32_t, string>::const_iterator it=guestList_.begin();it!=guestList_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(String,it->second);}
return true;}
void SWeddingGuest::clear(){
guestList_.clear();
}
bool SWeddingGuestUpdate::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;string v;PACKET_DECODE(Int32,k);PACKET_DECODE(String,v);addGuests_[k] = v;}}
return true;}
bool SWeddingGuestUpdate::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,addGuests_.size());
for(map<int32_t, string>::const_iterator it=addGuests_.begin();it!=addGuests_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(String,it->second);}
return true;}
void SWeddingGuestUpdate::clear(){
addGuests_.clear();
}
bool SWeddingPreGuest::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;string v;PACKET_DECODE(Int32,k);PACKET_DECODE(String,v);prGuestList_[k] = v;}}
return true;}
bool SWeddingPreGuest::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,prGuestList_.size());
for(map<int32_t, string>::const_iterator it=prGuestList_.begin();it!=prGuestList_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(String,it->second);}
return true;}
void SWeddingPreGuest::clear(){
prGuestList_.clear();
}
bool SWeddingPreGuestUpdate::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,oper_);
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,name_);
return true;}
bool SWeddingPreGuestUpdate::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,oper_);
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,name_);
return true;}
void SWeddingPreGuestUpdate::clear(){
oper_ = 0;
playerId_ = 0;
name_.clear();
}
bool SEnterWedding::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,marryId_);
if(!man_.decode(reader)){return false;}
if(!woman_.decode(reader)){return false;}
PACKET_DECODE(Int32,weddingStage_);
PACKET_DECODE(Int64,beginDt_);
PACKET_DECODE(Int32,hotValue_);
PACKET_DECODE(Int32,collectCount_);
return true;}
bool SEnterWedding::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,marryId_);
if(!man_.encode(writer)){return false;}
if(!woman_.encode(writer)){return false;}
PACKET_ENCODE(Int32,weddingStage_);
PACKET_ENCODE(Int64,beginDt_);
PACKET_ENCODE(Int32,hotValue_);
PACKET_ENCODE(Int32,collectCount_);
return true;}
void SEnterWedding::clear(){
marryId_ = 0;
man_.clear();
woman_.clear();
weddingStage_ = 0;
beginDt_ = 0;
hotValue_ = 0;
collectCount_ = 0;
}
bool SCompleteFoodLove::decode(CBufferReader &reader) {
if(!msgs::SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Int32,level_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool SCompleteFoodLove::encode(CBufferWriter &writer) const {
if(!msgs::SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCompleteFoodLove::clear(){
level_ = 0;
rewards_.clear();
}
bool SFoodLoveInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,level_);
return true;}
bool SFoodLoveInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,level_);
return true;}
void SFoodLoveInfo::clear(){
level_ = 0;
}
bool SPlayerPetFetter::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);activesFetter_.push_back(item);}}
return true;}
bool SPlayerPetFetter::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,activesFetter_.size());
for(vector<int32_t>::const_iterator vit=activesFetter_.begin();vit!=activesFetter_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SPlayerPetFetter::clear(){
activesFetter_.clear();
}
bool SPlayerNewPetInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,petHurt_);
PACKET_DECODE(Int32,marryPetHurt_);
PACKET_DECODE(Int32,mengPetHurt_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);dbs::TPlayerNewPet item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}pets_.push_back(item);}}
return true;}
bool SPlayerNewPetInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,petHurt_);
PACKET_ENCODE(Int32,marryPetHurt_);
PACKET_ENCODE(Int32,mengPetHurt_);
PACKET_ENCODE(UVar32,pets_.size());
for(vector<dbs::TPlayerNewPet>::const_iterator vit=pets_.begin();vit!=pets_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerNewPetInfo::clear(){
petHurt_ = 0;
marryPetHurt_ = 0;
mengPetHurt_ = 0;
pets_.clear();
}
bool SPlayerPetFormateInfo::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);dbs::TPlayerPetFormate item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}formates_.push_back(item);}}
return true;}
bool SPlayerPetFormateInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,formates_.size());
for(vector<dbs::TPlayerPetFormate>::const_iterator vit=formates_.begin();vit!=formates_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerPetFormateInfo::clear(){
formates_.clear();
}
bool SPetAssistInfo::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);petAssist_.push_back(item);}}
return true;}
bool SPetAssistInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,petAssist_.size());
for(vector<int32_t>::const_iterator vit=petAssist_.begin();vit!=petAssist_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SPetAssistInfo::clear(){
petAssist_.clear();
}
bool SPetTryInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,tryPetId_);
PACKET_DECODE(Int64,tryDeadline_);
return true;}
bool SPetTryInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,tryPetId_);
PACKET_ENCODE(Int64,tryDeadline_);
return true;}
void SPetTryInfo::clear(){
tryPetId_ = 0;
tryDeadline_ = 0;
}
bool SPlayFirework::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,livelyValue_);
return true;}
bool SPlayFirework::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,livelyValue_);
return true;}
void SPlayFirework::clear(){
livelyValue_ = 0;
}
bool SLivelyBossCreate::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,group_);
PACKET_DECODE(Int32,bossId_);
return true;}
bool SLivelyBossCreate::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,group_);
PACKET_ENCODE(Int32,bossId_);
return true;}
void SLivelyBossCreate::clear(){
group_ = 0;
bossId_ = 0;
}
bool SLivelyBossDead::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,group_);
PACKET_DECODE(Int32,bossId_);
PACKET_DECODE(String,belongName_);
PACKET_DECODE(Int32,belongCarrer_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);belongOrnaments_[k] = v;}}
return true;}
bool SLivelyBossDead::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,group_);
PACKET_ENCODE(Int32,bossId_);
PACKET_ENCODE(String,belongName_);
PACKET_ENCODE(Int32,belongCarrer_);
PACKET_ENCODE(UVar32,belongOrnaments_.size());
for(map<int16_t, int32_t>::const_iterator it=belongOrnaments_.begin();it!=belongOrnaments_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SLivelyBossDead::clear(){
group_ = 0;
bossId_ = 0;
belongName_.clear();
belongCarrer_ = 0;
belongOrnaments_.clear();
}
bool SLivelyValue::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,group_);
PACKET_DECODE(Int32,livelyValue_);
PACKET_DECODE(Int32,bossCurValue_);
PACKET_DECODE(Bool,bossIsAlive_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);redPacketId_[k] = v;}}
return true;}
bool SLivelyValue::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,group_);
PACKET_ENCODE(Int32,livelyValue_);
PACKET_ENCODE(Int32,bossCurValue_);
PACKET_ENCODE(Bool,bossIsAlive_);
PACKET_ENCODE(UVar32,redPacketId_.size());
for(map<int32_t, int32_t>::const_iterator it=redPacketId_.begin();it!=redPacketId_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SLivelyValue::clear(){
group_ = 0;
livelyValue_ = 0;
bossCurValue_ = 0;
bossIsAlive_ = 0;
redPacketId_.clear();
}
bool SLivelyBossDrop::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,group_);
PACKET_DECODE(Int32,bossId_);
return true;}
bool SLivelyBossDrop::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,group_);
PACKET_ENCODE(Int32,bossId_);
return true;}
void SLivelyBossDrop::clear(){
group_ = 0;
bossId_ = 0;
}
bool STotemInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);totemMap_[k] = v;}}
return true;}
bool STotemInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,totemMap_.size());
for(map<int32_t, int32_t>::const_iterator it=totemMap_.begin();it!=totemMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void STotemInfo::clear(){
totemMap_.clear();
}
bool SPlayerHolyBeast::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);dbs::TPlayerHolyBeast item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool SPlayerHolyBeast::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<dbs::TPlayerHolyBeast>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerHolyBeast::clear(){
list_.clear();
}
bool SPlayerHolyBeastGoOut::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);goOuts_[k] = v;}}
PACKET_DECODE(Bool,isGoOut_);
return true;}
bool SPlayerHolyBeastGoOut::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,goOuts_.size());
for(map<int32_t, int32_t>::const_iterator it=goOuts_.begin();it!=goOuts_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Bool,isGoOut_);
return true;}
void SPlayerHolyBeastGoOut::clear(){
goOuts_.clear();
isGoOut_ = 0;
}
bool SApplyHolyBeastBreed::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,applyPlayerId_);
PACKET_DECODE(String,applyName_);
PACKET_DECODE(Int32,applyModelId_);
PACKET_DECODE(Int32,applyTalent_);
PACKET_DECODE(Int32,applyLevel_);
PACKET_DECODE(Int32,applyRaitry_);
return true;}
bool SApplyHolyBeastBreed::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,applyPlayerId_);
PACKET_ENCODE(String,applyName_);
PACKET_ENCODE(Int32,applyModelId_);
PACKET_ENCODE(Int32,applyTalent_);
PACKET_ENCODE(Int32,applyLevel_);
PACKET_ENCODE(Int32,applyRaitry_);
return true;}
void SApplyHolyBeastBreed::clear(){
applyPlayerId_ = 0;
applyName_.clear();
applyModelId_ = 0;
applyTalent_ = 0;
applyLevel_ = 0;
applyRaitry_ = 0;
}
bool SConfirmHolyBeastBreed::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,otherPlayerId_);
PACKET_DECODE(Int32,otherModelId_);
PACKET_DECODE(String,otherName_);
PACKET_DECODE(Int32,otherTalent_);
PACKET_DECODE(Int32,beastId_);
return true;}
bool SConfirmHolyBeastBreed::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,otherPlayerId_);
PACKET_ENCODE(Int32,otherModelId_);
PACKET_ENCODE(String,otherName_);
PACKET_ENCODE(Int32,otherTalent_);
PACKET_ENCODE(Int32,beastId_);
return true;}
void SConfirmHolyBeastBreed::clear(){
otherPlayerId_ = 0;
otherModelId_ = 0;
otherName_.clear();
otherTalent_ = 0;
beastId_ = 0;
}
bool SBreedHolyBeastPlayers::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);msgs::SMiniPlayer item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool SBreedHolyBeastPlayers::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<msgs::SMiniPlayer>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SBreedHolyBeastPlayers::clear(){
list_.clear();
}
bool SRedPacketInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,grabNum_);
PACKET_DECODE(Int32,grabNumPrivate_);
PACKET_DECODE(Int32,numForRecharge_);
PACKET_DECODE(Int32,giveForRecharge_);
PACKET_DECODE(Int32,giveForPrivate_);
PACKET_DECODE(Int32,numForMonth_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);grabNumBosses_[k] = v;}}
return true;}
bool SRedPacketInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,grabNum_);
PACKET_ENCODE(Int32,grabNumPrivate_);
PACKET_ENCODE(Int32,numForRecharge_);
PACKET_ENCODE(Int32,giveForRecharge_);
PACKET_ENCODE(Int32,giveForPrivate_);
PACKET_ENCODE(Int32,numForMonth_);
PACKET_ENCODE(UVar32,grabNumBosses_.size());
for(map<int32_t, int32_t>::const_iterator it=grabNumBosses_.begin();it!=grabNumBosses_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SRedPacketInfo::clear(){
grabNum_ = 0;
grabNumPrivate_ = 0;
numForRecharge_ = 0;
giveForRecharge_ = 0;
giveForPrivate_ = 0;
numForMonth_ = 0;
grabNumBosses_.clear();
}
bool SRedPacket::decode(CBufferReader &reader) {
if(!dbs::TRedPacket::decode(reader)){return false;}
return true;}
bool SRedPacket::encode(CBufferWriter &writer) const {
if(!dbs::TRedPacket::encode(writer)){return false;}
return true;}
void SRedPacket::clear(){
}
bool SRedPacketList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SRedPacket item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool SRedPacketList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<SRedPacket>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SRedPacketList::clear(){
list_.clear();
}
bool SRedPacketGrab::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,redPacketId_);
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,playerName_);
PACKET_DECODE(Int32,moneyId_);
PACKET_DECODE(Int32,moneyNum_);
return true;}
bool SRedPacketGrab::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,redPacketId_);
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,playerName_);
PACKET_ENCODE(Int32,moneyId_);
PACKET_ENCODE(Int32,moneyNum_);
return true;}
void SRedPacketGrab::clear(){
redPacketId_ = 0;
playerId_ = 0;
playerName_.clear();
moneyId_ = 0;
moneyNum_ = 0;
}
bool SPlayerUpdateTalent::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,num_);
PACKET_DECODE(Int32,point_);
return true;}
bool SPlayerUpdateTalent::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,num_);
PACKET_ENCODE(Int32,point_);
return true;}
void SPlayerUpdateTalent::clear(){
roleId_ = 0;
type_ = 0;
num_ = 0;
point_ = 0;
}
bool SPlayerTalentInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);talents_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);talentsPoints_[k] = v;}}
return true;}
bool SPlayerTalentInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(UVar32,talents_.size());
for(map<int32_t, int32_t>::const_iterator it=talents_.begin();it!=talents_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,talentsPoints_.size());
for(map<int32_t, int32_t>::const_iterator it=talentsPoints_.begin();it!=talentsPoints_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SPlayerTalentInfo::clear(){
roleId_ = 0;
talents_.clear();
talentsPoints_.clear();
}
bool SPlayerZhenFa::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,id_);
return true;}
bool SPlayerZhenFa::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,id_);
return true;}
void SPlayerZhenFa::clear(){
id_ = 0;
}
bool SPlayerZhenWeiSkill::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,id_);
PACKET_DECODE(Int32,star_);
PACKET_DECODE(Int32,level_);
return true;}
bool SPlayerZhenWeiSkill::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,id_);
PACKET_ENCODE(Int32,star_);
PACKET_ENCODE(Int32,level_);
return true;}
void SPlayerZhenWeiSkill::clear(){
id_ = 0;
star_ = 0;
level_ = 0;
}
bool SPlayerZhenFaExtend::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeLoginDay_);
PACKET_DECODE(Int32,activeRechargeDay_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SPlayerZhenFa item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}zhenfaList_.push_back(item);}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SPlayerZhenWeiSkill item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}zhenweiSkillList_.push_back(item);}}
return true;}
bool SPlayerZhenFaExtend::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeLoginDay_);
PACKET_ENCODE(Int32,activeRechargeDay_);
PACKET_ENCODE(UVar32,zhenfaList_.size());
for(vector<SPlayerZhenFa>::const_iterator vit=zhenfaList_.begin();vit!=zhenfaList_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(UVar32,zhenweiSkillList_.size());
for(vector<SPlayerZhenWeiSkill>::const_iterator vit=zhenweiSkillList_.begin();vit!=zhenweiSkillList_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerZhenFaExtend::clear(){
activeLoginDay_ = 0;
activeRechargeDay_ = 0;
zhenfaList_.clear();
zhenweiSkillList_.clear();
}
bool SPlayerUseZhenFaExtend::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,useZhanfaId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;map<int32_t, int32_t> v;PACKET_DECODE(Int32,k);{uint32_t len1=0;PACKET_DECODE(UVar32,len1);for(uint32_t i1=0;i1<len1;++i1){int32_t k1;int32_t v1;PACKET_DECODE(Int32,k1);PACKET_DECODE(Int32,v1);v[k1] = v1;}}
zhanweis_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;map<int32_t, int32_t> v;PACKET_DECODE(Int32,k);{uint32_t len1=0;PACKET_DECODE(UVar32,len1);for(uint32_t i1=0;i1<len1;++i1){int32_t k1;int32_t v1;PACKET_DECODE(Int32,k1);PACKET_DECODE(Int32,v1);v[k1] = v1;}}
zhanweiskills_[k] = v;}}
return true;}
bool SPlayerUseZhenFaExtend::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,useZhanfaId_);
PACKET_ENCODE(UVar32,zhanweis_.size());
for(map<int32_t, map<int32_t, int32_t> >::const_iterator it=zhanweis_.begin();it!=zhanweis_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(UVar32,it->second.size());
for(map<int32_t, int32_t>::const_iterator it1=it->second.begin();it1!=it->second.end();++it1){PACKET_ENCODE(Int32,it1->first);PACKET_ENCODE(Int32,it1->second);}
}
PACKET_ENCODE(UVar32,zhanweiskills_.size());
for(map<int32_t, map<int32_t, int32_t> >::const_iterator it=zhanweiskills_.begin();it!=zhanweiskills_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(UVar32,it->second.size());
for(map<int32_t, int32_t>::const_iterator it1=it->second.begin();it1!=it->second.end();++it1){PACKET_ENCODE(Int32,it1->first);PACKET_ENCODE(Int32,it1->second);}
}
return true;}
void SPlayerUseZhenFaExtend::clear(){
useZhanfaId_ = 0;
zhanweis_.clear();
zhanweiskills_.clear();
}
bool SXianWu::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,id_);
PACKET_DECODE(Int32,level_);
return true;}
bool SXianWu::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,id_);
PACKET_ENCODE(Int32,level_);
return true;}
void SXianWu::clear(){
id_ = 0;
level_ = 0;
}
bool SPlayerXianWuInfo::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SXianWu item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}seq_.push_back(item);}}
return true;}
bool SPlayerXianWuInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,seq_.size());
for(vector<SXianWu>::const_iterator vit=seq_.begin();vit!=seq_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerXianWuInfo::clear(){
seq_.clear();
}
bool SPlayerDressXianWu::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,dressId_);
return true;}
bool SPlayerDressXianWu::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,dressId_);
return true;}
void SPlayerDressXianWu::clear(){
dressId_ = 0;
}
bool SToplist::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);crossTypes_.push_back(item);}}
PACKET_DECODE(Int32,toplistType_);
PACKET_DECODE(Int32,version_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);dbs::TToplist item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}records_.push_back(item);}}
return true;}
bool SToplist::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,crossTypes_.size());
for(vector<int32_t>::const_iterator vit=crossTypes_.begin();vit!=crossTypes_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(Int32,toplistType_);
PACKET_ENCODE(Int32,version_);
PACKET_ENCODE(UVar32,records_.size());
for(vector<dbs::TToplist>::const_iterator vit=records_.begin();vit!=records_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SToplist::clear(){
crossTypes_.clear();
toplistType_ = 0;
version_ = 0;
records_.clear();
}
bool SToplistVersionUpdate::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);versions_[k] = v;}}
return true;}
bool SToplistVersionUpdate::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,versions_.size());
for(map<int32_t, int32_t>::const_iterator it=versions_.begin();it!=versions_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SToplistVersionUpdate::clear(){
versions_.clear();
}
bool SAchievementCopy::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);copyInfo_[k] = v;}}
return true;}
bool SAchievementCopy::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,copyInfo_.size());
for(map<int32_t, int32_t>::const_iterator it=copyInfo_.begin();it!=copyInfo_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SAchievementCopy::clear(){
copyInfo_.clear();
}
bool SFlyChessSingle::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,pos_);
PACKET_DECODE(Int32,freeCount_);
PACKET_DECODE(Int32,resetCount_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);route_.push_back(item);}}
PACKET_DECODE(Int32,buyCount_);
return true;}
bool SFlyChessSingle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,pos_);
PACKET_ENCODE(Int32,freeCount_);
PACKET_ENCODE(Int32,resetCount_);
PACKET_ENCODE(UVar32,route_.size());
for(vector<int32_t>::const_iterator vit=route_.begin();vit!=route_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(Int32,buyCount_);
return true;}
void SFlyChessSingle::clear(){
pos_ = 0;
freeCount_ = 0;
resetCount_ = 0;
route_.clear();
buyCount_ = 0;
}
bool SFlyChess::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SFlyChessSingle v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}flyChessMap_[k] = v;}}
return true;}
bool SFlyChess::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,flyChessMap_.size());
for(map<int32_t, SFlyChessSingle>::const_iterator it=flyChessMap_.begin();it!=flyChessMap_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SFlyChess::clear(){
flyChessMap_.clear();
}
bool SFlyChessEnd::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);totalRewards_[k] = v;}}
return true;}
bool SFlyChessEnd::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,totalRewards_.size());
for(map<int32_t, int32_t>::const_iterator it=totalRewards_.begin();it!=totalRewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SFlyChessEnd::clear(){
totalRewards_.clear();
}
bool SAdvance::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int32,star_);
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,lastDayLevel_);
PACKET_DECODE(Int32,bless_);
PACKET_DECODE(Int32,tmpBless_);
PACKET_DECODE(Int32,modelId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);dan_[k] = v;}}
return true;}
bool SAdvance::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int32,star_);
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,lastDayLevel_);
PACKET_ENCODE(Int32,bless_);
PACKET_ENCODE(Int32,tmpBless_);
PACKET_ENCODE(Int32,modelId_);
PACKET_ENCODE(UVar32,dan_.size());
for(map<int32_t, int32_t>::const_iterator it=dan_.begin();it!=dan_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SAdvance::clear(){
type_ = 0;
roleId_ = 0;
star_ = 0;
level_ = 0;
lastDayLevel_ = 0;
bless_ = 0;
tmpBless_ = 0;
modelId_ = 0;
dan_.clear();
}
bool SAdvanceUpdate::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int32,star_);
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,lastDayLevel_);
PACKET_DECODE(Int32,bless_);
PACKET_DECODE(Int32,tmpBless_);
PACKET_DECODE(Int32,modelId_);
return true;}
bool SAdvanceUpdate::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int32,star_);
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,lastDayLevel_);
PACKET_ENCODE(Int32,bless_);
PACKET_ENCODE(Int32,tmpBless_);
PACKET_ENCODE(Int32,modelId_);
return true;}
void SAdvanceUpdate::clear(){
type_ = 0;
roleId_ = 0;
star_ = 0;
level_ = 0;
lastDayLevel_ = 0;
bless_ = 0;
tmpBless_ = 0;
modelId_ = 0;
}
bool SAdvanceDanUpdate::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,danType_);
PACKET_DECODE(Int32,num_);
return true;}
bool SAdvanceDanUpdate::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,danType_);
PACKET_ENCODE(Int32,num_);
return true;}
void SAdvanceDanUpdate::clear(){
roleId_ = 0;
type_ = 0;
danType_ = 0;
num_ = 0;
}
bool SPlayerAdvanceInfo::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SAdvance item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}advances_.push_back(item);}}
return true;}
bool SPlayerAdvanceInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,advances_.size());
for(vector<SAdvance>::const_iterator vit=advances_.begin();vit!=advances_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerAdvanceInfo::clear(){
advances_.clear();
}
bool SAdvanceAwaken::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,star_);
return true;}
bool SAdvanceAwaken::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,star_);
return true;}
void SAdvanceAwaken::clear(){
roleId_ = 0;
type_ = 0;
level_ = 0;
star_ = 0;
}
bool SPlayerAdvanceAwakenInfo::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SAdvanceAwaken item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}awakens_.push_back(item);}}
return true;}
bool SPlayerAdvanceAwakenInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,awakens_.size());
for(vector<SAdvanceAwaken>::const_iterator vit=awakens_.begin();vit!=awakens_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerAdvanceAwakenInfo::clear(){
awakens_.clear();
}
bool SAdvanceAwakenUpdate::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,star_);
return true;}
bool SAdvanceAwakenUpdate::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,star_);
return true;}
void SAdvanceAwakenUpdate::clear(){
roleId_ = 0;
type_ = 0;
level_ = 0;
star_ = 0;
}
bool SPlayerGuardList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);dbs::TPlayerGuard item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}guards_.push_back(item);}}
return true;}
bool SPlayerGuardList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,guards_.size());
for(vector<dbs::TPlayerGuard>::const_iterator vit=guards_.begin();vit!=guards_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerGuardList::clear(){
guards_.clear();
}
bool SPlayerGuardExInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,score_);
return true;}
bool SPlayerGuardExInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,score_);
return true;}
void SPlayerGuardExInfo::clear(){
score_ = 0;
}
bool SGuardItem::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,id_);
PACKET_DECODE(Int32,itemId_);
PACKET_DECODE(String,itemExtend_);
return true;}
bool SGuardItem::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,id_);
PACKET_ENCODE(Int32,itemId_);
PACKET_ENCODE(String,itemExtend_);
return true;}
void SGuardItem::clear(){
id_ = 0;
itemId_ = 0;
itemExtend_.clear();
}
bool SGuardItemRecord::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,playerName_);
PACKET_DECODE(Int32,oper_);
PACKET_DECODE(Int32,id_);
PACKET_DECODE(Int32,itemId_);
PACKET_DECODE(String,itemExtend_);
PACKET_DECODE(Int64,recordDt_);
return true;}
bool SGuardItemRecord::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,playerName_);
PACKET_ENCODE(Int32,oper_);
PACKET_ENCODE(Int32,id_);
PACKET_ENCODE(Int32,itemId_);
PACKET_ENCODE(String,itemExtend_);
PACKET_ENCODE(Int64,recordDt_);
return true;}
void SGuardItemRecord::clear(){
playerId_ = 0;
playerName_.clear();
oper_ = 0;
id_ = 0;
itemId_ = 0;
itemExtend_.clear();
recordDt_ = 0;
}
bool SAdvanceDayInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);isGotRewards_[k] = v;}}
return true;}
bool SAdvanceDayInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,isGotRewards_.size());
for(map<int32_t, bool>::const_iterator it=isGotRewards_.begin();it!=isGotRewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
return true;}
void SAdvanceDayInfo::clear(){
isGotRewards_.clear();
}
bool SZhanlingInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,dai_);
PACKET_DECODE(Int32,mission_);
PACKET_DECODE(Int64,deadline_);
PACKET_DECODE(Int32,adv_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);advance_[k] = v;}}
return true;}
bool SZhanlingInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,dai_);
PACKET_ENCODE(Int32,mission_);
PACKET_ENCODE(Int64,deadline_);
PACKET_ENCODE(Int32,adv_);
PACKET_ENCODE(UVar32,advance_.size());
for(map<int32_t, int32_t>::const_iterator it=advance_.begin();it!=advance_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SZhanlingInfo::clear(){
dai_ = 0;
mission_ = 0;
deadline_ = 0;
adv_ = 0;
advance_.clear();
}
bool SFashion::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,promoteLevel_);
PACKET_DECODE(Int32,bless_);
PACKET_DECODE(Int32,dian_);
PACKET_DECODE(Int64,deadDt_);
return true;}
bool SFashion::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,promoteLevel_);
PACKET_ENCODE(Int32,bless_);
PACKET_ENCODE(Int32,dian_);
PACKET_ENCODE(Int64,deadDt_);
return true;}
void SFashion::clear(){
level_ = 0;
promoteLevel_ = 0;
bless_ = 0;
dian_ = 0;
deadDt_ = 0;
}
bool SFashionInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,puton_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SFashion v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}fashions_[k] = v;}}
return true;}
bool SFashionInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,puton_);
PACKET_ENCODE(UVar32,fashions_.size());
for(map<int32_t, SFashion>::const_iterator it=fashions_.begin();it!=fashions_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SFashionInfo::clear(){
puton_ = 0;
fashions_.clear();
}
bool SRoleFashionInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;msgs::SInts v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}suits_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SFashionInfo v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}roleFashion_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;msgs::SIntBoolMap v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}roleItem_[k] = v;}}
return true;}
bool SRoleFashionInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,suits_.size());
for(map<int32_t, msgs::SInts>::const_iterator it=suits_.begin();it!=suits_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
PACKET_ENCODE(UVar32,roleFashion_.size());
for(map<int32_t, SFashionInfo>::const_iterator it=roleFashion_.begin();it!=roleFashion_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
PACKET_ENCODE(UVar32,roleItem_.size());
for(map<int32_t, msgs::SIntBoolMap>::const_iterator it=roleItem_.begin();it!=roleItem_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SRoleFashionInfo::clear(){
suits_.clear();
roleFashion_.clear();
roleItem_.clear();
}
bool SPlayerFashionInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SRoleFashionInfo v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}playerFashion_[k] = v;}}
return true;}
bool SPlayerFashionInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,playerFashion_.size());
for(map<int32_t, SRoleFashionInfo>::const_iterator it=playerFashion_.begin();it!=playerFashion_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SPlayerFashionInfo::clear(){
playerFashion_.clear();
}
bool SSendFashion::decode(CBufferReader &reader) {
if(!fromId_.decode(reader)){return false;}
PACKET_DECODE(String,fromName_);
PACKET_DECODE(Int32,fashionId_);
return true;}
bool SSendFashion::encode(CBufferWriter &writer) const {
if(!fromId_.encode(writer)){return false;}
PACKET_ENCODE(String,fromName_);
PACKET_ENCODE(Int32,fashionId_);
return true;}
void SSendFashion::clear(){
fromId_.clear();
fromName_.clear();
fashionId_ = 0;
}
bool SPlayerSignFourteenDay::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,index_);
PACKET_DECODE(Int32,gotIndex_);
return true;}
bool SPlayerSignFourteenDay::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,index_);
PACKET_ENCODE(Int32,gotIndex_);
return true;}
void SPlayerSignFourteenDay::clear(){
index_ = 0;
gotIndex_ = 0;
}
bool SPlayerSignEveryDay::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,freeCount_);
PACKET_DECODE(Int32,todayIsSign_);
PACKET_DECODE(Int32,signNum_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);targetGots_.push_back(item);}}
return true;}
bool SPlayerSignEveryDay::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,freeCount_);
PACKET_ENCODE(Int32,todayIsSign_);
PACKET_ENCODE(Int32,signNum_);
PACKET_ENCODE(UVar32,targetGots_.size());
for(vector<int32_t>::const_iterator vit=targetGots_.begin();vit!=targetGots_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SPlayerSignEveryDay::clear(){
freeCount_ = 0;
todayIsSign_ = 0;
signNum_ = 0;
targetGots_.clear();
}
bool SMarryTrialInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,level_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);skillMap_[k] = v;}}
return true;}
bool SMarryTrialInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(UVar32,skillMap_.size());
for(map<int32_t, bool>::const_iterator it=skillMap_.begin();it!=skillMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
return true;}
void SMarryTrialInfo::clear(){
level_ = 0;
skillMap_.clear();
}
bool SMarryTrialMateInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,level_);
return true;}
bool SMarryTrialMateInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,level_);
return true;}
void SMarryTrialMateInfo::clear(){
level_ = 0;
}
bool SMarryTrialStatusUpdate::decode(CBufferReader &reader) {
PACKET_DECODE(Bool,isMarry_);
if(!playerA_.decode(reader)){return false;}
if(!playerB_.decode(reader)){return false;}
return true;}
bool SMarryTrialStatusUpdate::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Bool,isMarry_);
if(!playerA_.encode(writer)){return false;}
if(!playerB_.encode(writer)){return false;}
return true;}
void SMarryTrialStatusUpdate::clear(){
isMarry_ = 0;
playerA_.clear();
playerB_.clear();
}
bool SDailyActivityInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activity_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);hadGetRewards_[k] = v;}}
PACKET_DECODE(Int32,levelLimit_);
PACKET_DECODE(Int32,carrerLevelLimit_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);getActCnt_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);getActivity_[k] = v;}}
PACKET_DECODE(Int32,weekActivity_);
PACKET_DECODE(Int32,weekLevelLimit_);
PACKET_DECODE(Int32,weekCarrerLevelLimit_);
return true;}
bool SDailyActivityInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activity_);
PACKET_ENCODE(UVar32,hadGetRewards_.size());
for(map<int32_t, int32_t>::const_iterator it=hadGetRewards_.begin();it!=hadGetRewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,levelLimit_);
PACKET_ENCODE(Int32,carrerLevelLimit_);
PACKET_ENCODE(UVar32,getActCnt_.size());
for(map<int32_t, int32_t>::const_iterator it=getActCnt_.begin();it!=getActCnt_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,getActivity_.size());
for(map<int32_t, int32_t>::const_iterator it=getActivity_.begin();it!=getActivity_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,weekActivity_);
PACKET_ENCODE(Int32,weekLevelLimit_);
PACKET_ENCODE(Int32,weekCarrerLevelLimit_);
return true;}
void SDailyActivityInfo::clear(){
activity_ = 0;
hadGetRewards_.clear();
levelLimit_ = 0;
carrerLevelLimit_ = 0;
getActCnt_.clear();
getActivity_.clear();
weekActivity_ = 0;
weekLevelLimit_ = 0;
weekCarrerLevelLimit_ = 0;
}
bool SMagicSingle::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);isOpenHole_[k] = v;}}
return true;}
bool SMagicSingle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,isOpenHole_.size());
for(map<int32_t, int32_t>::const_iterator it=isOpenHole_.begin();it!=isOpenHole_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SMagicSingle::clear(){
isOpenHole_.clear();
}
bool SMagicInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SMagicSingle v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}roleHole_[k] = v;}}
PACKET_DECODE(Int32,magicCopyLayer_);
return true;}
bool SMagicInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,roleHole_.size());
for(map<int32_t, SMagicSingle>::const_iterator it=roleHole_.begin();it!=roleHole_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
PACKET_ENCODE(Int32,magicCopyLayer_);
return true;}
void SMagicInfo::clear(){
roleHole_.clear();
magicCopyLayer_ = 0;
}
bool SHorcruxeSingle::decode(CBufferReader &reader) {
PACKET_DECODE(Bool,isActive_);
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,subtype_);
PACKET_DECODE(Int32,star_);
PACKET_DECODE(Int32,level_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);fulPer_[k] = v;}}
PACKET_DECODE(Int32,fulNum_);
return true;}
bool SHorcruxeSingle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Bool,isActive_);
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,subtype_);
PACKET_ENCODE(Int32,star_);
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(UVar32,fulPer_.size());
for(map<int32_t, int32_t>::const_iterator it=fulPer_.begin();it!=fulPer_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,fulNum_);
return true;}
void SHorcruxeSingle::clear(){
isActive_ = 0;
type_ = 0;
subtype_ = 0;
star_ = 0;
level_ = 0;
fulPer_.clear();
fulNum_ = 0;
}
bool SHorcruxeTypeMap::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SHorcruxeSingle v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}horcruxeMap_[k] = v;}}
return true;}
bool SHorcruxeTypeMap::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,horcruxeMap_.size());
for(map<int32_t, SHorcruxeSingle>::const_iterator it=horcruxeMap_.begin();it!=horcruxeMap_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SHorcruxeTypeMap::clear(){
horcruxeMap_.clear();
}
bool SHorcruxeInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SHorcruxeTypeMap v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}horcruxeTypeMap_[k] = v;}}
return true;}
bool SHorcruxeInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,horcruxeTypeMap_.size());
for(map<int32_t, SHorcruxeTypeMap>::const_iterator it=horcruxeTypeMap_.begin();it!=horcruxeTypeMap_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SHorcruxeInfo::clear(){
horcruxeTypeMap_.clear();
}
bool SMiniMail::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,id_);
PACKET_DECODE(String,sender_);
PACKET_DECODE(String,title_);
PACKET_DECODE(Int64,mailDt_);
PACKET_DECODE(Bool,isRead_);
PACKET_DECODE(Bool,hasAttach_);
return true;}
bool SMiniMail::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,id_);
PACKET_ENCODE(String,sender_);
PACKET_ENCODE(String,title_);
PACKET_ENCODE(Int64,mailDt_);
PACKET_ENCODE(Bool,isRead_);
PACKET_ENCODE(Bool,hasAttach_);
return true;}
void SMiniMail::clear(){
id_ = 0;
sender_.clear();
title_.clear();
mailDt_ = 0;
isRead_ = 0;
hasAttach_ = 0;
}
bool SNotifyMailboxStatus::decode(CBufferReader &reader) {
PACKET_DECODE(Bool,notRead_);
PACKET_DECODE(Bool,hasAttach_);
return true;}
bool SNotifyMailboxStatus::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Bool,notRead_);
PACKET_ENCODE(Bool,hasAttach_);
return true;}
void SNotifyMailboxStatus::clear(){
notRead_ = 0;
hasAttach_ = 0;
}
bool SNotifyNewMail::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SMiniMail item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}list_.push_back(item);}}
return true;}
bool SNotifyNewMail::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,list_.size());
for(vector<SMiniMail>::const_iterator vit=list_.begin();vit!=list_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SNotifyNewMail::clear(){
list_.clear();
}
bool SNotifyDelMail::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,id_);
return true;}
bool SNotifyDelMail::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,id_);
return true;}
void SNotifyDelMail::clear(){
id_ = 0;
}
bool SAddMail::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,updateCode_);
PACKET_DECODE(String,updateStr_);
if(!entityId_.decode(reader)){return false;}
if(!mail_.decode(reader)){return false;}
return true;}
bool SAddMail::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,updateCode_);
PACKET_ENCODE(String,updateStr_);
if(!entityId_.encode(writer)){return false;}
if(!mail_.encode(writer)){return false;}
return true;}
void SAddMail::clear(){
updateCode_ = 0;
updateStr_.clear();
entityId_.clear();
mail_.clear();
}
bool SChatMsg::decode(CBufferReader &reader) {
PACKET_DECODE(Int16,channel_);
if(!fromPlayer_.decode(reader)){return false;}
PACKET_DECODE(String,content_);
PACKET_DECODE(String,extend_);
return true;}
bool SChatMsg::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int16,channel_);
if(!fromPlayer_.encode(writer)){return false;}
PACKET_ENCODE(String,content_);
PACKET_ENCODE(String,extend_);
return true;}
void SChatMsg::clear(){
channel_ = 0;
fromPlayer_.clear();
content_.clear();
extend_.clear();
}
bool SChatInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,freeHorn_);
PACKET_DECODE(Int32,hornNum_);
PACKET_DECODE(Int64,feedbackDt_);
return true;}
bool SChatInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,freeHorn_);
PACKET_ENCODE(Int32,hornNum_);
PACKET_ENCODE(Int64,feedbackDt_);
return true;}
void SChatInfo::clear(){
freeHorn_ = 0;
hornNum_ = 0;
feedbackDt_ = 0;
}
bool SOpenServerTargetInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);isGetReward_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);bossKill_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);godPlaneKill_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);vipBossKill_[k] = v;}}
return true;}
bool SOpenServerTargetInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,isGetReward_.size());
for(map<int32_t, int32_t>::const_iterator it=isGetReward_.begin();it!=isGetReward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,bossKill_.size());
for(map<int32_t, bool>::const_iterator it=bossKill_.begin();it!=bossKill_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
PACKET_ENCODE(UVar32,godPlaneKill_.size());
for(map<int32_t, int32_t>::const_iterator it=godPlaneKill_.begin();it!=godPlaneKill_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,vipBossKill_.size());
for(map<int32_t, int32_t>::const_iterator it=vipBossKill_.begin();it!=vipBossKill_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SOpenServerTargetInfo::clear(){
isGetReward_.clear();
bossKill_.clear();
godPlaneKill_.clear();
vipBossKill_.clear();
}
bool SOpenServerTreasure::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);treasureCount_[k] = v;}}
return true;}
bool SOpenServerTreasure::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,treasureCount_.size());
for(map<int32_t, int32_t>::const_iterator it=treasureCount_.begin();it!=treasureCount_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SOpenServerTreasure::clear(){
treasureCount_.clear();
}
bool SOpenServerTargetCounter::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewardCounter_[k] = v;}}
return true;}
bool SOpenServerTargetCounter::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,rewardCounter_.size());
for(map<int32_t, int32_t>::const_iterator it=rewardCounter_.begin();it!=rewardCounter_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SOpenServerTargetCounter::clear(){
rewardCounter_.clear();
}
bool SOpenServerAdvanceCounter::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);counter_[k] = v;}}
return true;}
bool SOpenServerAdvanceCounter::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,counter_.size());
for(map<int32_t, int32_t>::const_iterator it=counter_.begin();it!=counter_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SOpenServerAdvanceCounter::clear(){
counter_.clear();
}
bool SZeroGiftInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);dayRecharge_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;map<int32_t, bool> v;PACKET_DECODE(Int32,k);{uint32_t len1=0;PACKET_DECODE(UVar32,len1);for(uint32_t i1=0;i1<len1;++i1){int32_t k1;bool v1;PACKET_DECODE(Int32,k1);PACKET_DECODE(Bool,v1);v[k1] = v1;}}
gotRewards_[k] = v;}}
return true;}
bool SZeroGiftInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,dayRecharge_.size());
for(map<int32_t, int32_t>::const_iterator it=dayRecharge_.begin();it!=dayRecharge_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,gotRewards_.size());
for(map<int32_t, map<int32_t, bool> >::const_iterator it=gotRewards_.begin();it!=gotRewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(UVar32,it->second.size());
for(map<int32_t, bool>::const_iterator it1=it->second.begin();it1!=it->second.end();++it1){PACKET_ENCODE(Int32,it1->first);PACKET_ENCODE(Bool,it1->second);}
}
return true;}
void SZeroGiftInfo::clear(){
dayRecharge_.clear();
gotRewards_.clear();
}
bool SBroadcastContent::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,broadcastId_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);string item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(String,item);params_.push_back(item);}}
PACKET_DECODE(Int32,proxyId_);
return true;}
bool SBroadcastContent::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,broadcastId_);
PACKET_ENCODE(UVar32,params_.size());
for(vector<string>::const_iterator vit=params_.begin();vit!=params_.end();++vit){PACKET_ENCODE(String,*vit);}
PACKET_ENCODE(Int32,proxyId_);
return true;}
void SBroadcastContent::clear(){
broadcastId_ = 0;
params_.clear();
proxyId_ = 0;
}
bool SSystemNotify::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
PACKET_DECODE(String,content_);
PACKET_DECODE(Bool,isFloat_);
PACKET_DECODE(Int16,minLevel_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);string item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(String,item);gameChannels_.push_back(item);}}
return true;}
bool SSystemNotify::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(String,content_);
PACKET_ENCODE(Bool,isFloat_);
PACKET_ENCODE(Int16,minLevel_);
PACKET_ENCODE(UVar32,gameChannels_.size());
for(vector<string>::const_iterator vit=gameChannels_.begin();vit!=gameChannels_.end();++vit){PACKET_ENCODE(String,*vit);}
return true;}
void SSystemNotify::clear(){
type_ = 0;
content_.clear();
isFloat_ = 0;
minLevel_ = 0;
gameChannels_.clear();
}
bool SPlayerHelp::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(Int64,combat_);
PACKET_DECODE(Int32,count_);
PACKET_DECODE(Int32,career_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);ornaments_[k] = v;}}
PACKET_DECODE(String,name_);
PACKET_DECODE(Bool,entrust_);
return true;}
bool SPlayerHelp::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(Int32,count_);
PACKET_ENCODE(Int32,career_);
PACKET_ENCODE(UVar32,ornaments_.size());
for(map<int16_t, int32_t>::const_iterator it=ornaments_.begin();it!=ornaments_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Bool,entrust_);
return true;}
void SPlayerHelp::clear(){
entityId_.clear();
combat_ = 0;
count_ = 0;
career_ = 0;
ornaments_.clear();
name_.clear();
entrust_ = 0;
}
bool SPlayerHelpOwn::decode(CBufferReader &reader) {
if(!helpPlayer_.decode(reader)){return false;}
if(!beHelpPlayer_.decode(reader)){return false;}
return true;}
bool SPlayerHelpOwn::encode(CBufferWriter &writer) const {
if(!helpPlayer_.encode(writer)){return false;}
if(!beHelpPlayer_.encode(writer)){return false;}
return true;}
void SPlayerHelpOwn::clear(){
helpPlayer_.clear();
beHelpPlayer_.clear();
}
bool SPlayerMiracleIslandInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCount_);
PACKET_DECODE(Int32,helpCount_);
PACKET_DECODE(Int32,beHelpCount_);
PACKET_DECODE(Bool,helpOthter_);
return true;}
bool SPlayerMiracleIslandInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCount_);
PACKET_ENCODE(Int32,helpCount_);
PACKET_ENCODE(Int32,beHelpCount_);
PACKET_ENCODE(Bool,helpOthter_);
return true;}
void SPlayerMiracleIslandInfo::clear(){
copyCount_ = 0;
helpCount_ = 0;
beHelpCount_ = 0;
helpOthter_ = 0;
}
bool SMiracleIslandRankItem::decode(CBufferReader &reader) {
if(!serverId_.decode(reader)){return false;}
PACKET_DECODE(Int32,killNum_);
return true;}
bool SMiracleIslandRankItem::encode(CBufferWriter &writer) const {
if(!serverId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,killNum_);
return true;}
void SMiracleIslandRankItem::clear(){
serverId_.clear();
killNum_ = 0;
}
bool SMiracleBossReward::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(Int32,career_);
PACKET_DECODE(Int32,isOwn_);
PACKET_DECODE(String,name_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);reward_[k] = v;}}
return true;}
bool SMiracleBossReward::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,career_);
PACKET_ENCODE(Int32,isOwn_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(UVar32,reward_.size());
for(map<int32_t, int32_t>::const_iterator it=reward_.begin();it!=reward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SMiracleBossReward::clear(){
entityId_.clear();
career_ = 0;
isOwn_ = 0;
name_.clear();
reward_.clear();
}
bool SMiracleBossPlayerData::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(Int32,copyCount_);
PACKET_DECODE(Int32,helpCount_);
PACKET_DECODE(String,helpName_);
return true;}
bool SMiracleBossPlayerData::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,copyCount_);
PACKET_ENCODE(Int32,helpCount_);
PACKET_ENCODE(String,helpName_);
return true;}
void SMiracleBossPlayerData::clear(){
entityId_.clear();
copyCount_ = 0;
helpCount_ = 0;
helpName_.clear();
}
bool SMarket::decode(CBufferReader &reader) {
if(!dbs::TDbMarket::decode(reader)){return false;}
if(!entityId_.decode(reader)){return false;}
return true;}
bool SMarket::encode(CBufferWriter &writer) const {
if(!dbs::TDbMarket::encode(writer)){return false;}
if(!entityId_.encode(writer)){return false;}
return true;}
void SMarket::clear(){
entityId_.clear();
}
bool SMarketInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,page_);
PACKET_DECODE(Int32,totalPage_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SMarket item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}seq_.push_back(item);}}
return true;}
bool SMarketInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,page_);
PACKET_ENCODE(Int32,totalPage_);
PACKET_ENCODE(UVar32,seq_.size());
for(vector<SMarket>::const_iterator vit=seq_.begin();vit!=seq_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SMarketInfo::clear(){
page_ = 0;
totalPage_ = 0;
seq_.clear();
}
bool SMarketHis::decode(CBufferReader &reader) {
if(!dbs::TMarketHis::decode(reader)){return false;}
if(!entityId_.decode(reader)){return false;}
return true;}
bool SMarketHis::encode(CBufferWriter &writer) const {
if(!dbs::TMarketHis::encode(writer)){return false;}
if(!entityId_.encode(writer)){return false;}
return true;}
void SMarketHis::clear(){
entityId_.clear();
}
bool SMarketHisInfo::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SMarketHis item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}seq_.push_back(item);}}
return true;}
bool SMarketHisInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,seq_.size());
for(vector<SMarketHis>::const_iterator vit=seq_.begin();vit!=seq_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SMarketHisInfo::clear(){
seq_.clear();
}
bool SPlayerAutoDrop::decode(CBufferReader &reader) {
if(!belongEntityId_.decode(reader)){return false;}
if(!dropPoint_.decode(reader)){return false;}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);msgs::SItemAmount item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}items_.push_back(item);}}
PACKET_DECODE(Int32,type_);
return true;}
bool SPlayerAutoDrop::encode(CBufferWriter &writer) const {
if(!belongEntityId_.encode(writer)){return false;}
if(!dropPoint_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,items_.size());
for(vector<msgs::SItemAmount>::const_iterator vit=items_.begin();vit!=items_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(Int32,type_);
return true;}
void SPlayerAutoDrop::clear(){
belongEntityId_.clear();
dropPoint_.clear();
items_.clear();
type_ = 0;
}
bool SLianYao::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,id_);
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,star_);
return true;}
bool SLianYao::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,id_);
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,star_);
return true;}
void SLianYao::clear(){
id_ = 0;
level_ = 0;
star_ = 0;
}
bool SPlayerLianYaoInfo::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SLianYao item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}seq_.push_back(item);}}
return true;}
bool SPlayerLianYaoInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,seq_.size());
for(vector<SLianYao>::const_iterator vit=seq_.begin();vit!=seq_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerLianYaoInfo::clear(){
seq_.clear();
}
bool SMonthCardSingle::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,buyDate_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);dayRewardMap_[k] = v;}}
return true;}
bool SMonthCardSingle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,buyDate_);
PACKET_ENCODE(UVar32,dayRewardMap_.size());
for(map<int32_t, bool>::const_iterator it=dayRewardMap_.begin();it!=dayRewardMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
return true;}
void SMonthCardSingle::clear(){
buyDate_ = 0;
dayRewardMap_.clear();
}
bool SMonthCardInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SMonthCardSingle v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}cards_[k] = v;}}
return true;}
bool SMonthCardInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,cards_.size());
for(map<int32_t, SMonthCardSingle>::const_iterator it=cards_.begin();it!=cards_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SMonthCardInfo::clear(){
cards_.clear();
}
bool SMonthCardSingle2::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,beginDt_);
PACKET_DECODE(Int64,endDt_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);dayRewardMap_[k] = v;}}
PACKET_DECODE(Int32,versionCount_);
return true;}
bool SMonthCardSingle2::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,beginDt_);
PACKET_ENCODE(Int64,endDt_);
PACKET_ENCODE(UVar32,dayRewardMap_.size());
for(map<int32_t, bool>::const_iterator it=dayRewardMap_.begin();it!=dayRewardMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
PACKET_ENCODE(Int32,versionCount_);
return true;}
void SMonthCardSingle2::clear(){
beginDt_ = 0;
endDt_ = 0;
dayRewardMap_.clear();
versionCount_ = 0;
}
bool SMonthCardInfo2::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SMonthCardSingle2 v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}cards_[k] = v;}}
return true;}
bool SMonthCardInfo2::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,cards_.size());
for(map<int32_t, SMonthCardSingle2>::const_iterator it=cards_.begin();it!=cards_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SMonthCardInfo2::clear(){
cards_.clear();
}
bool SBuyMonthCard::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
return true;}
bool SBuyMonthCard::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
return true;}
void SBuyMonthCard::clear(){
type_ = 0;
}
bool SMonthCardReBuy::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);reBuyMap_[k] = v;}}
return true;}
bool SMonthCardReBuy::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeId_);
PACKET_ENCODE(UVar32,reBuyMap_.size());
for(map<int32_t, int32_t>::const_iterator it=reBuyMap_.begin();it!=reBuyMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SMonthCardReBuy::clear(){
activeId_ = 0;
reBuyMap_.clear();
}
bool SHangLevelBoss::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,bossId_);
if(!point_.decode(reader)){return false;}
return true;}
bool SHangLevelBoss::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,bossId_);
if(!point_.encode(writer)){return false;}
return true;}
void SHangLevelBoss::clear(){
bossId_ = 0;
point_.clear();
}
bool SHangBossPass::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,result_);
PACKET_DECODE(Int32,newHangLevel_);
return true;}
bool SHangBossPass::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,result_);
PACKET_ENCODE(Int32,newHangLevel_);
return true;}
void SHangBossPass::clear(){
result_ = 0;
newHangLevel_ = 0;
}
bool SHangBossResult::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,result_);
PACKET_DECODE(Int32,newHangLevel_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool SHangBossResult::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,result_);
PACKET_ENCODE(Int32,newHangLevel_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SHangBossResult::clear(){
result_ = 0;
newHangLevel_ = 0;
rewards_.clear();
}
bool SHangPower::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,power_);
return true;}
bool SHangPower::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,power_);
return true;}
void SHangPower::clear(){
power_ = 0;
}
bool SHangOfflineReward::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,exp_);
PACKET_DECODE(Int32,coin_);
PACKET_DECODE(Int32,decomposeNum_);
PACKET_DECODE(Int64,offlineTime_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
PACKET_DECODE(Int32,type_);
return true;}
bool SHangOfflineReward::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,exp_);
PACKET_ENCODE(Int32,coin_);
PACKET_ENCODE(Int32,decomposeNum_);
PACKET_ENCODE(Int64,offlineTime_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,type_);
return true;}
void SHangOfflineReward::clear(){
exp_ = 0;
coin_ = 0;
decomposeNum_ = 0;
offlineTime_ = 0;
rewards_.clear();
type_ = 0;
}
bool SHangResetPoint::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,hang_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Point item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}toPoints_.push_back(item);}}
return true;}
bool SHangResetPoint::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,hang_);
PACKET_ENCODE(UVar32,toPoints_.size());
for(vector<Point>::const_iterator vit=toPoints_.begin();vit!=toPoints_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SHangResetPoint::clear(){
hang_ = 0;
toPoints_.clear();
}
bool SFeaturesReward::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);getReward_[k] = v;}}
return true;}
bool SFeaturesReward::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,getReward_.size());
for(map<int32_t, bool>::const_iterator it=getReward_.begin();it!=getReward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
return true;}
void SFeaturesReward::clear(){
getReward_.clear();
}
bool SGuildWarGuildInfo::decode(CBufferReader &reader) {
PACKET_DECODE(String,guildName_);
PACKET_DECODE(Int32,guildPlayerNum_);
PACKET_DECODE(Int32,score_);
return true;}
bool SGuildWarGuildInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,guildName_);
PACKET_ENCODE(Int32,guildPlayerNum_);
PACKET_ENCODE(Int32,score_);
return true;}
void SGuildWarGuildInfo::clear(){
guildName_.clear();
guildPlayerNum_ = 0;
score_ = 0;
}
bool SGuildWarPlayerInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,exploits_);
PACKET_DECODE(Int32,score_);
PACKET_DECODE(Int32,gotTargetId_);
return true;}
bool SGuildWarPlayerInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,exploits_);
PACKET_ENCODE(Int32,score_);
PACKET_ENCODE(Int32,gotTargetId_);
return true;}
void SGuildWarPlayerInfo::clear(){
exploits_ = 0;
score_ = 0;
gotTargetId_ = 0;
}
bool SGuildWarAddScore::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,addScore_);
PACKET_DECODE(String,killName_);
PACKET_DECODE(Int32,monsterCode_);
return true;}
bool SGuildWarAddScore::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,addScore_);
PACKET_ENCODE(String,killName_);
PACKET_ENCODE(Int32,monsterCode_);
return true;}
void SGuildWarAddScore::clear(){
addScore_ = 0;
killName_.clear();
monsterCode_ = 0;
}
bool SGuildWarResult::decode(CBufferReader &reader) {
PACKET_DECODE(Bool,success_);
if(!placeGuildId_.decode(reader)){return false;}
PACKET_DECODE(String,placeGuildName_);
PACKET_DECODE(String,placeLeaderName_);
PACKET_DECODE(String,myGuildName_);
PACKET_DECODE(Int32,myGuildScore_);
PACKET_DECODE(Int32,myGuildRank_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);myGuildRewards_[k] = v;}}
PACKET_DECODE(Int32,myScore_);
PACKET_DECODE(Int32,myRank_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);myRewards_[k] = v;}}
return true;}
bool SGuildWarResult::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Bool,success_);
if(!placeGuildId_.encode(writer)){return false;}
PACKET_ENCODE(String,placeGuildName_);
PACKET_ENCODE(String,placeLeaderName_);
PACKET_ENCODE(String,myGuildName_);
PACKET_ENCODE(Int32,myGuildScore_);
PACKET_ENCODE(Int32,myGuildRank_);
PACKET_ENCODE(UVar32,myGuildRewards_.size());
for(map<int32_t, int32_t>::const_iterator it=myGuildRewards_.begin();it!=myGuildRewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,myScore_);
PACKET_ENCODE(Int32,myRank_);
PACKET_ENCODE(UVar32,myRewards_.size());
for(map<int32_t, int32_t>::const_iterator it=myRewards_.begin();it!=myRewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SGuildWarResult::clear(){
success_ = 0;
placeGuildId_.clear();
placeGuildName_.clear();
placeLeaderName_.clear();
myGuildName_.clear();
myGuildScore_ = 0;
myGuildRank_ = 0;
myGuildRewards_.clear();
myScore_ = 0;
myRank_ = 0;
myRewards_.clear();
}
bool SGuildWarFlagInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,status_);
PACKET_DECODE(Int64,endTime_);
if(!playerId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
if(!guildId_.decode(reader)){return false;}
PACKET_DECODE(String,guildName_);
return true;}
bool SGuildWarFlagInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,status_);
PACKET_ENCODE(Int64,endTime_);
if(!playerId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
if(!guildId_.encode(writer)){return false;}
PACKET_ENCODE(String,guildName_);
return true;}
void SGuildWarFlagInfo::clear(){
status_ = 0;
endTime_ = 0;
playerId_.clear();
name_.clear();
guildId_.clear();
guildName_.clear();
}
bool SGuildWarGuildRankReward::decode(CBufferReader &reader) {
if(!guildId_.decode(reader)){return false;}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);hasGots_[k] = v;}}
return true;}
bool SGuildWarGuildRankReward::encode(CBufferWriter &writer) const {
if(!guildId_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,hasGots_.size());
for(map<int32_t, int32_t>::const_iterator it=hasGots_.begin();it!=hasGots_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SGuildWarGuildRankReward::clear(){
guildId_.clear();
rewards_.clear();
hasGots_.clear();
}
bool SGuildWarGuildRank::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,guildId_);
PACKET_DECODE(String,guildName_);
PACKET_DECODE(String,leaderName_);
PACKET_DECODE(Int32,score_);
return true;}
bool SGuildWarGuildRank::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,guildId_);
PACKET_ENCODE(String,guildName_);
PACKET_ENCODE(String,leaderName_);
PACKET_ENCODE(Int32,score_);
return true;}
void SGuildWarGuildRank::clear(){
guildId_ = 0;
guildName_.clear();
leaderName_.clear();
score_ = 0;
}
bool SGuildWarPlayerRank::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,guildId_);
PACKET_DECODE(String,guildName_);
PACKET_DECODE(Int32,score_);
return true;}
bool SGuildWarPlayerRank::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,guildId_);
PACKET_ENCODE(String,guildName_);
PACKET_ENCODE(Int32,score_);
return true;}
void SGuildWarPlayerRank::clear(){
playerId_ = 0;
name_.clear();
guildId_ = 0;
guildName_.clear();
score_ = 0;
}
bool SGuildWarGuildRankList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SGuildWarGuildRank item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}guildRanks_.push_back(item);}}
return true;}
bool SGuildWarGuildRankList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,guildRanks_.size());
for(vector<SGuildWarGuildRank>::const_iterator vit=guildRanks_.begin();vit!=guildRanks_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SGuildWarGuildRankList::clear(){
guildRanks_.clear();
}
bool SGuildWarPlayerRankList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SGuildWarPlayerRank item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}playerRanks_.push_back(item);}}
return true;}
bool SGuildWarPlayerRankList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,playerRanks_.size());
for(vector<SGuildWarPlayerRank>::const_iterator vit=playerRanks_.begin();vit!=playerRanks_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SGuildWarPlayerRankList::clear(){
playerRanks_.clear();
}
bool SGuildWarPlayerData::decode(CBufferReader &reader) {
PACKET_DECODE(Bool,gotDayReward_);
return true;}
bool SGuildWarPlayerData::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Bool,gotDayReward_);
return true;}
void SGuildWarPlayerData::clear(){
gotDayReward_ = 0;
}
bool SGuildWarPrePlaceInfo::decode(CBufferReader &reader) {
if(!guildId_.decode(reader)){return false;}
PACKET_DECODE(String,guildName_);
if(!playerId_.decode(reader)){return false;}
return true;}
bool SGuildWarPrePlaceInfo::encode(CBufferWriter &writer) const {
if(!guildId_.encode(writer)){return false;}
PACKET_ENCODE(String,guildName_);
if(!playerId_.encode(writer)){return false;}
return true;}
void SGuildWarPrePlaceInfo::clear(){
guildId_.clear();
guildName_.clear();
playerId_.clear();
}
bool SServerTerritoryInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);territoryReward_[k] = v;}}
PACKET_DECODE(Int32,hasGotPlaceRank_);
PACKET_DECODE(Int32,hasGotKillRank_);
PACKET_DECODE(Int32,placeRank_);
PACKET_DECODE(Int32,killRank_);
return true;}
bool SServerTerritoryInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,territoryReward_.size());
for(map<int32_t, int32_t>::const_iterator it=territoryReward_.begin();it!=territoryReward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,hasGotPlaceRank_);
PACKET_ENCODE(Int32,hasGotKillRank_);
PACKET_ENCODE(Int32,placeRank_);
PACKET_ENCODE(Int32,killRank_);
return true;}
void SServerTerritoryInfo::clear(){
territoryReward_.clear();
hasGotPlaceRank_ = 0;
hasGotKillRank_ = 0;
placeRank_ = 0;
killRank_ = 0;
}
bool SServerTerritoryCopyInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,targetId_);
PACKET_DECODE(Int32,score_);
PACKET_DECODE(Int32,killNum_);
PACKET_DECODE(Int32,feats_);
PACKET_DECODE(Int32,killTower_);
return true;}
bool SServerTerritoryCopyInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,targetId_);
PACKET_ENCODE(Int32,score_);
PACKET_ENCODE(Int32,killNum_);
PACKET_ENCODE(Int32,feats_);
PACKET_ENCODE(Int32,killTower_);
return true;}
void SServerTerritoryCopyInfo::clear(){
targetId_ = 0;
score_ = 0;
killNum_ = 0;
feats_ = 0;
killTower_ = 0;
}
bool SServerTerritoryFightInfo::decode(CBufferReader &reader) {
if(!attackId_.decode(reader)){return false;}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);attackePlace_.push_back(item);}}
if(!defenseId_.decode(reader)){return false;}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);defensePlace_.push_back(item);}}
PACKET_DECODE(Bool,hasFight_);
PACKET_DECODE(Bool,isEnd_);
return true;}
bool SServerTerritoryFightInfo::encode(CBufferWriter &writer) const {
if(!attackId_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,attackePlace_.size());
for(vector<int32_t>::const_iterator vit=attackePlace_.begin();vit!=attackePlace_.end();++vit){PACKET_ENCODE(Int32,*vit);}
if(!defenseId_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,defensePlace_.size());
for(vector<int32_t>::const_iterator vit=defensePlace_.begin();vit!=defensePlace_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(Bool,hasFight_);
PACKET_ENCODE(Bool,isEnd_);
return true;}
void SServerTerritoryFightInfo::clear(){
attackId_.clear();
attackePlace_.clear();
defenseId_.clear();
defensePlace_.clear();
hasFight_ = 0;
isEnd_ = 0;
}
bool SServerTerritoryResult::decode(CBufferReader &reader) {
if(!msgs::SCompleteCopy::decode(reader)){return false;}
PACKET_DECODE(Bool,isAttacker_);
PACKET_DECODE(Int32,territory_);
PACKET_DECODE(Int32,delTerritory_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool SServerTerritoryResult::encode(CBufferWriter &writer) const {
if(!msgs::SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(Bool,isAttacker_);
PACKET_ENCODE(Int32,territory_);
PACKET_ENCODE(Int32,delTerritory_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SServerTerritoryResult::clear(){
isAttacker_ = 0;
territory_ = 0;
delTerritory_ = 0;
rewards_.clear();
}
bool SServerTerritoryCenterResult::decode(CBufferReader &reader) {
if(!centerId_.decode(reader)){return false;}
PACKET_DECODE(Int32,result_);
return true;}
bool SServerTerritoryCenterResult::encode(CBufferWriter &writer) const {
if(!centerId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,result_);
return true;}
void SServerTerritoryCenterResult::clear(){
centerId_.clear();
result_ = 0;
}
bool SServerTerritoryUpdatePlace::decode(CBufferReader &reader) {
if(!centerId_.decode(reader)){return false;}
PACKET_DECODE(Int64,activeCombat_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);territorys_.push_back(item);}}
return true;}
bool SServerTerritoryUpdatePlace::encode(CBufferWriter &writer) const {
if(!centerId_.encode(writer)){return false;}
PACKET_ENCODE(Int64,activeCombat_);
PACKET_ENCODE(UVar32,territorys_.size());
for(vector<int32_t>::const_iterator vit=territorys_.begin();vit!=territorys_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SServerTerritoryUpdatePlace::clear(){
centerId_.clear();
activeCombat_ = 0;
territorys_.clear();
}
bool SServerTerritoryTower::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){string k;int32_t v;PACKET_DECODE(String,k);PACKET_DECODE(Int32,v);towers_[k] = v;}}
return true;}
bool SServerTerritoryTower::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,towers_.size());
for(map<string, int32_t>::const_iterator it=towers_.begin();it!=towers_.end();++it){PACKET_ENCODE(String,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SServerTerritoryTower::clear(){
towers_.clear();
}
bool SCrossFightsStatus::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,status_);
PACKET_DECODE(Int32,regStatus_);
PACKET_DECODE(Int64,endTime_);
PACKET_DECODE(Int32,stage_);
PACKET_DECODE(Int32,successCount_);
return true;}
bool SCrossFightsStatus::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,status_);
PACKET_ENCODE(Int32,regStatus_);
PACKET_ENCODE(Int64,endTime_);
PACKET_ENCODE(Int32,stage_);
PACKET_ENCODE(Int32,successCount_);
return true;}
void SCrossFightsStatus::clear(){
status_ = 0;
regStatus_ = 0;
endTime_ = 0;
stage_ = 0;
successCount_ = 0;
}
bool SCrossFightsInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,score_);
PACKET_DECODE(Int32,targetId_);
PACKET_DECODE(Int32,lifeCount_);
PACKET_DECODE(Int64,beginLiveTime_);
PACKET_DECODE(Int32,roomLevel_);
return true;}
bool SCrossFightsInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,score_);
PACKET_ENCODE(Int32,targetId_);
PACKET_ENCODE(Int32,lifeCount_);
PACKET_ENCODE(Int64,beginLiveTime_);
PACKET_ENCODE(Int32,roomLevel_);
return true;}
void SCrossFightsInfo::clear(){
score_ = 0;
targetId_ = 0;
lifeCount_ = 0;
beginLiveTime_ = 0;
roomLevel_ = 0;
}
bool SCrossFightsRank::decode(CBufferReader &reader) {
if(!playerId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,lifeCount_);
PACKET_DECODE(Int32,score_);
PACKET_DECODE(Int32,isFailed_);
return true;}
bool SCrossFightsRank::encode(CBufferWriter &writer) const {
if(!playerId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,lifeCount_);
PACKET_ENCODE(Int32,score_);
PACKET_ENCODE(Int32,isFailed_);
return true;}
void SCrossFightsRank::clear(){
playerId_.clear();
name_.clear();
lifeCount_ = 0;
score_ = 0;
isFailed_ = 0;
}
bool SCrossFightsRankList::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SCrossFightsRank item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}ranks_.push_back(item);}}
return true;}
bool SCrossFightsRankList::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,ranks_.size());
for(vector<SCrossFightsRank>::const_iterator vit=ranks_.begin();vit!=ranks_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SCrossFightsRankList::clear(){
ranks_.clear();
}
bool SCrossFightsKill::decode(CBufferReader &reader) {
PACKET_DECODE(String,fromName_);
PACKET_DECODE(String,toName_);
PACKET_DECODE(Int32,killNum_);
PACKET_DECODE(Int32,fromCareer_);
PACKET_DECODE(Int32,toCareer_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);fromOrnaments_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);toOrnaments_[k] = v;}}
return true;}
bool SCrossFightsKill::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,fromName_);
PACKET_ENCODE(String,toName_);
PACKET_ENCODE(Int32,killNum_);
PACKET_ENCODE(Int32,fromCareer_);
PACKET_ENCODE(Int32,toCareer_);
PACKET_ENCODE(UVar32,fromOrnaments_.size());
for(map<int16_t, int32_t>::const_iterator it=fromOrnaments_.begin();it!=fromOrnaments_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,toOrnaments_.size());
for(map<int16_t, int32_t>::const_iterator it=toOrnaments_.begin();it!=toOrnaments_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SCrossFightsKill::clear(){
fromName_.clear();
toName_.clear();
killNum_ = 0;
fromCareer_ = 0;
toCareer_ = 0;
fromOrnaments_.clear();
toOrnaments_.clear();
}
bool SCompleteCrossFights::decode(CBufferReader &reader) {
if(!msgs::SCompleteCopy::decode(reader)){return false;}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SCrossFightsRank item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}ranks_.push_back(item);}}
return true;}
bool SCompleteCrossFights::encode(CBufferWriter &writer) const {
if(!msgs::SCompleteCopy::encode(writer)){return false;}
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,ranks_.size());
for(vector<SCrossFightsRank>::const_iterator vit=ranks_.begin();vit!=ranks_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SCompleteCrossFights::clear(){
rewards_.clear();
ranks_.clear();
}
bool SShuraWar::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);tasks_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);completeTasks_[k] = v;}}
PACKET_DECODE(Int32,star_);
PACKET_DECODE(Bool,killKing_);
PACKET_DECODE(Int32,killNum_);
PACKET_DECODE(Int32,beKillNum_);
return true;}
bool SShuraWar::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,tasks_.size());
for(map<int32_t, int32_t>::const_iterator it=tasks_.begin();it!=tasks_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,completeTasks_.size());
for(map<int32_t, int32_t>::const_iterator it=completeTasks_.begin();it!=completeTasks_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,star_);
PACKET_ENCODE(Bool,killKing_);
PACKET_ENCODE(Int32,killNum_);
PACKET_ENCODE(Int32,beKillNum_);
return true;}
void SShuraWar::clear(){
tasks_.clear();
completeTasks_.clear();
star_ = 0;
killKing_ = 0;
killNum_ = 0;
beKillNum_ = 0;
}
bool SShuraBoss::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,bossId_);
PACKET_DECODE(Int64,refreshTime_);
return true;}
bool SShuraBoss::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,bossId_);
PACKET_ENCODE(Int64,refreshTime_);
return true;}
void SShuraBoss::clear(){
bossId_ = 0;
refreshTime_ = 0;
}
bool SShuraBossInfo::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SShuraBoss item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}littleBoss_.push_back(item);}}
PACKET_DECODE(Bool,bigBossAlive_);
return true;}
bool SShuraBossInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,littleBoss_.size());
for(vector<SShuraBoss>::const_iterator vit=littleBoss_.begin();vit!=littleBoss_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(Bool,bigBossAlive_);
return true;}
void SShuraBossInfo::clear(){
littleBoss_.clear();
bigBossAlive_ = 0;
}
bool SShuraWarScore::decode(CBufferReader &reader) {
if(!playerId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,score_);
return true;}
bool SShuraWarScore::encode(CBufferWriter &writer) const {
if(!playerId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,score_);
return true;}
void SShuraWarScore::clear(){
playerId_.clear();
name_.clear();
score_ = 0;
}
bool SShuraWarScoreRank::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SShuraWarScore item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}ranks_.push_back(item);}}
return true;}
bool SShuraWarScoreRank::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,ranks_.size());
for(vector<SShuraWarScore>::const_iterator vit=ranks_.begin();vit!=ranks_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SShuraWarScoreRank::clear(){
ranks_.clear();
}
bool SShuraWarSeqKill::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int16,career_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);ornaments_[k] = v;}}
PACKET_DECODE(Int16,killNum_);
return true;}
bool SShuraWarSeqKill::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int16,career_);
PACKET_ENCODE(UVar32,ornaments_.size());
for(map<int16_t, int32_t>::const_iterator it=ornaments_.begin();it!=ornaments_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int16,killNum_);
return true;}
void SShuraWarSeqKill::clear(){
entityId_.clear();
name_.clear();
career_ = 0;
ornaments_.clear();
killNum_ = 0;
}
bool SPlayerTitle::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,titleId_);
PACKET_DECODE(Int64,indateTime_);
return true;}
bool SPlayerTitle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,titleId_);
PACKET_ENCODE(Int64,indateTime_);
return true;}
void SPlayerTitle::clear(){
titleId_ = 0;
indateTime_ = 0;
}
bool SPlayerTitleInfo::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SPlayerTitle item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}titles_.push_back(item);}}
return true;}
bool SPlayerTitleInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,titles_.size());
for(vector<SPlayerTitle>::const_iterator vit=titles_.begin();vit!=titles_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerTitleInfo::clear(){
titles_.clear();
}
bool SPlayerTouxianInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,touxianId_);
PACKET_DECODE(Int32,feat_);
return true;}
bool SPlayerTouxianInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,touxianId_);
PACKET_ENCODE(Int32,feat_);
return true;}
void SPlayerTouxianInfo::clear(){
touxianId_ = 0;
feat_ = 0;
}
bool SFourGod::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,status_);
PACKET_DECODE(Int32,advance_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);dan_[k] = v;}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);suitLevel_.push_back(item);}}
return true;}
bool SFourGod::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,status_);
PACKET_ENCODE(Int32,advance_);
PACKET_ENCODE(UVar32,dan_.size());
for(map<int32_t, int32_t>::const_iterator it=dan_.begin();it!=dan_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,suitLevel_.size());
for(vector<int32_t>::const_iterator vit=suitLevel_.begin();vit!=suitLevel_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SFourGod::clear(){
status_ = 0;
advance_ = 0;
dan_.clear();
suitLevel_.clear();
}
bool SFourGodInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SFourGod v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}fgs_[k] = v;}}
return true;}
bool SFourGodInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,fgs_.size());
for(map<int32_t, SFourGod>::const_iterator it=fgs_.begin();it!=fgs_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SFourGodInfo::clear(){
fgs_.clear();
}
bool SPlayerVipInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,level_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);gotReward_[k] = v;}}
PACKET_DECODE(Int32,weekReward_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);fakeGotReward_[k] = v;}}
PACKET_DECODE(Bool,isFake_);
return true;}
bool SPlayerVipInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(UVar32,gotReward_.size());
for(map<int32_t, int32_t>::const_iterator it=gotReward_.begin();it!=gotReward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,weekReward_);
PACKET_ENCODE(UVar32,fakeGotReward_.size());
for(map<int32_t, int32_t>::const_iterator it=fakeGotReward_.begin();it!=fakeGotReward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Bool,isFake_);
return true;}
void SPlayerVipInfo::clear(){
level_ = 0;
gotReward_.clear();
weekReward_ = 0;
fakeGotReward_.clear();
isFake_ = 0;
}
bool SOneYuanTreasureSingle::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeType_);
PACKET_DECODE(Int32,id_);
PACKET_DECODE(Int32,status_);
PACKET_DECODE(Int64,startTime_);
PACKET_DECODE(Int64,endTime_);
PACKET_DECODE(Int32,hadBuyCount_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){string k;int32_t v;PACKET_DECODE(String,k);PACKET_DECODE(Int32,v);buyCountMap_[k] = v;}}
PACKET_DECODE(String,winPlayerName_);
return true;}
bool SOneYuanTreasureSingle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeType_);
PACKET_ENCODE(Int32,id_);
PACKET_ENCODE(Int32,status_);
PACKET_ENCODE(Int64,startTime_);
PACKET_ENCODE(Int64,endTime_);
PACKET_ENCODE(Int32,hadBuyCount_);
PACKET_ENCODE(UVar32,buyCountMap_.size());
for(map<string, int32_t>::const_iterator it=buyCountMap_.begin();it!=buyCountMap_.end();++it){PACKET_ENCODE(String,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(String,winPlayerName_);
return true;}
void SOneYuanTreasureSingle::clear(){
activeType_ = 0;
id_ = 0;
status_ = 0;
startTime_ = 0;
endTime_ = 0;
hadBuyCount_ = 0;
buyCountMap_.clear();
winPlayerName_.clear();
}
bool SOneYuanTreasure::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,activeType_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SOneYuanTreasureSingle v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}statusMap_[k] = v;}}
return true;}
bool SOneYuanTreasure::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,activeType_);
PACKET_ENCODE(UVar32,statusMap_.size());
for(map<int32_t, SOneYuanTreasureSingle>::const_iterator it=statusMap_.begin();it!=statusMap_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SOneYuanTreasure::clear(){
activeType_ = 0;
statusMap_.clear();
}
bool SOneYuanTreasureRecordSingle::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,openTime_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Bool,spike_);
PACKET_DECODE(Int32,itemId_);
PACKET_DECODE(Int32,itemNum_);
PACKET_DECODE(Int32,buyNum_);
PACKET_DECODE(Bool,isWinner_);
return true;}
bool SOneYuanTreasureRecordSingle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,openTime_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Bool,spike_);
PACKET_ENCODE(Int32,itemId_);
PACKET_ENCODE(Int32,itemNum_);
PACKET_ENCODE(Int32,buyNum_);
PACKET_ENCODE(Bool,isWinner_);
return true;}
void SOneYuanTreasureRecordSingle::clear(){
openTime_ = 0;
name_.clear();
spike_ = 0;
itemId_ = 0;
itemNum_ = 0;
buyNum_ = 0;
isWinner_ = 0;
}
bool SOneYuanTreasureRecord::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SOneYuanTreasureRecordSingle item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}records_.push_back(item);}}
return true;}
bool SOneYuanTreasureRecord::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,records_.size());
for(vector<SOneYuanTreasureRecordSingle>::const_iterator vit=records_.begin();vit!=records_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SOneYuanTreasureRecord::clear(){
records_.clear();
}
bool SOneYuanTreasureTarget::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;bool v;PACKET_DECODE(Int32,k);PACKET_DECODE(Bool,v);gotRewardMap_[k] = v;}}
PACKET_DECODE(Int32,totalCount_);
return true;}
bool SOneYuanTreasureTarget::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,gotRewardMap_.size());
for(map<int32_t, bool>::const_iterator it=gotRewardMap_.begin();it!=gotRewardMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Bool,it->second);}
PACKET_ENCODE(Int32,totalCount_);
return true;}
void SOneYuanTreasureTarget::clear(){
gotRewardMap_.clear();
totalCount_ = 0;
}
bool SOneYuanTreasurePlayer::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(Int32,historyCount_);
PACKET_DECODE(String,playerName_);
return true;}
bool SOneYuanTreasurePlayer::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(Int32,historyCount_);
PACKET_ENCODE(String,playerName_);
return true;}
void SOneYuanTreasurePlayer::clear(){
entityId_.clear();
historyCount_ = 0;
playerName_.clear();
}
bool SOneYuanTreasureEndInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){Identity k;bool v;if(!k.decode(reader)){return false;}PACKET_DECODE(Bool,v);spikeMap_[k] = v;}}
PACKET_DECODE(Int32,itemId_);
PACKET_DECODE(Int32,itemNum_);
PACKET_DECODE(Int64,endTime_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){Identity k;int32_t v;if(!k.decode(reader)){return false;}PACKET_DECODE(Int32,v);buyCountMap_[k] = v;}}
if(!winEntityId_.decode(reader)){return false;}
return true;}
bool SOneYuanTreasureEndInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,spikeMap_.size());
for(map<Identity, bool>::const_iterator it=spikeMap_.begin();it!=spikeMap_.end();++it){if(!it->first.encode(writer)){return false;}PACKET_ENCODE(Bool,it->second);}
PACKET_ENCODE(Int32,itemId_);
PACKET_ENCODE(Int32,itemNum_);
PACKET_ENCODE(Int64,endTime_);
PACKET_ENCODE(UVar32,buyCountMap_.size());
for(map<Identity, int32_t>::const_iterator it=buyCountMap_.begin();it!=buyCountMap_.end();++it){if(!it->first.encode(writer)){return false;}PACKET_ENCODE(Int32,it->second);}
if(!winEntityId_.encode(writer)){return false;}
return true;}
void SOneYuanTreasureEndInfo::clear(){
spikeMap_.clear();
itemId_ = 0;
itemNum_ = 0;
endTime_ = 0;
buyCountMap_.clear();
winEntityId_.clear();
}
bool SNearEnemy::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,career_);
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,career_level_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);ornaments_[k] = v;}}
return true;}
bool SNearEnemy::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,career_);
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,career_level_);
PACKET_ENCODE(UVar32,ornaments_.size());
for(map<int16_t, int32_t>::const_iterator it=ornaments_.begin();it!=ornaments_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SNearEnemy::clear(){
playerId_ = 0;
name_.clear();
career_ = 0;
level_ = 0;
career_level_ = 0;
ornaments_.clear();
}
bool SNearEnemyInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,zhangong_);
PACKET_DECODE(Int32,shalu_);
PACKET_DECODE(Int32,totalKill_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SNearEnemy item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}enemys_.push_back(item);}}
return true;}
bool SNearEnemyInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,zhangong_);
PACKET_ENCODE(Int32,shalu_);
PACKET_ENCODE(Int32,totalKill_);
PACKET_ENCODE(UVar32,enemys_.size());
for(vector<SNearEnemy>::const_iterator vit=enemys_.begin();vit!=enemys_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SNearEnemyInfo::clear(){
zhangong_ = 0;
shalu_ = 0;
totalKill_ = 0;
enemys_.clear();
}
bool SNearEnemyResult::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,succ_);
PACKET_DECODE(Int32,hangLevel_);
PACKET_DECODE(Int32,enemyId_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);msgs::SItemAmount item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}rewards_.push_back(item);}}
return true;}
bool SNearEnemyResult::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,succ_);
PACKET_ENCODE(Int32,hangLevel_);
PACKET_ENCODE(Int32,enemyId_);
PACKET_ENCODE(UVar32,rewards_.size());
for(vector<msgs::SItemAmount>::const_iterator vit=rewards_.begin();vit!=rewards_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SNearEnemyResult::clear(){
succ_ = 0;
hangLevel_ = 0;
enemyId_ = 0;
rewards_.clear();
}
bool SSoulSingle::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);isOpenHole_[k] = v;}}
return true;}
bool SSoulSingle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,isOpenHole_.size());
for(map<int32_t, int32_t>::const_iterator it=isOpenHole_.begin();it!=isOpenHole_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SSoulSingle::clear(){
isOpenHole_.clear();
}
bool SSoulInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SSoulSingle v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}roleHole_[k] = v;}}
return true;}
bool SSoulInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,roleHole_.size());
for(map<int32_t, SSoulSingle>::const_iterator it=roleHole_.begin();it!=roleHole_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SSoulInfo::clear(){
roleHole_.clear();
}
bool SCheats::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,itemId_);
PACKET_DECODE(Int32,isLock_);
return true;}
bool SCheats::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,itemId_);
PACKET_ENCODE(Int32,isLock_);
return true;}
void SCheats::clear(){
itemId_ = 0;
isLock_ = 0;
}
bool SPlayerCheats::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SCheats item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}cheats_.push_back(item);}}
PACKET_DECODE(Int32,roleId_);
return true;}
bool SPlayerCheats::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,cheats_.size());
for(vector<SCheats>::const_iterator vit=cheats_.begin();vit!=cheats_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(Int32,roleId_);
return true;}
void SPlayerCheats::clear(){
cheats_.clear();
roleId_ = 0;
}
bool SUpdateCheats::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,index_);
PACKET_DECODE(Int32,itemId_);
PACKET_DECODE(Int32,isLock_);
PACKET_DECODE(Int32,roleId_);
return true;}
bool SUpdateCheats::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,index_);
PACKET_ENCODE(Int32,itemId_);
PACKET_ENCODE(Int32,isLock_);
PACKET_ENCODE(Int32,roleId_);
return true;}
void SUpdateCheats::clear(){
index_ = 0;
itemId_ = 0;
isLock_ = 0;
roleId_ = 0;
}
bool SShenqiInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,cur_shenqi_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);actived_pieces_.push_back(item);}}
return true;}
bool SShenqiInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,cur_shenqi_);
PACKET_ENCODE(UVar32,actived_pieces_.size());
for(vector<int32_t>::const_iterator vit=actived_pieces_.begin();vit!=actived_pieces_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SShenqiInfo::clear(){
cur_shenqi_ = 0;
actived_pieces_.clear();
}
bool SPlayerWsGodRing::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,attackLevel_);
PACKET_DECODE(Int32,defenseLevel_);
return true;}
bool SPlayerWsGodRing::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,attackLevel_);
PACKET_ENCODE(Int32,defenseLevel_);
return true;}
void SPlayerWsGodRing::clear(){
attackLevel_ = 0;
defenseLevel_ = 0;
}
bool SZhiBaoSingle::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,star_);
PACKET_DECODE(Int32,bless_);
PACKET_DECODE(Int32,target_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);danMap_[k] = v;}}
return true;}
bool SZhiBaoSingle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,star_);
PACKET_ENCODE(Int32,bless_);
PACKET_ENCODE(Int32,target_);
PACKET_ENCODE(UVar32,danMap_.size());
for(map<int32_t, int32_t>::const_iterator it=danMap_.begin();it!=danMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SZhiBaoSingle::clear(){
level_ = 0;
star_ = 0;
bless_ = 0;
target_ = 0;
danMap_.clear();
}
bool SZhiBaoInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SZhiBaoSingle v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}maps_[k] = v;}}
return true;}
bool SZhiBaoInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,maps_.size());
for(map<int32_t, SZhiBaoSingle>::const_iterator it=maps_.begin();it!=maps_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SZhiBaoInfo::clear(){
maps_.clear();
}
bool SVersionReward::decode(CBufferReader &reader) {
PACKET_DECODE(Bool,isGotReward_);
return true;}
bool SVersionReward::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Bool,isGotReward_);
return true;}
void SVersionReward::clear(){
isGotReward_ = 0;
}
bool SPlayerOnlineReward::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,onlineTime_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);hasGotReward_[k] = v;}}
return true;}
bool SPlayerOnlineReward::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,onlineTime_);
PACKET_ENCODE(UVar32,hasGotReward_.size());
for(map<int32_t, int32_t>::const_iterator it=hasGotReward_.begin();it!=hasGotReward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SPlayerOnlineReward::clear(){
onlineTime_ = 0;
hasGotReward_.clear();
}
bool SPlayerCallInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,isBeCall_);
PACKET_DECODE(Int32,isSetCaller_);
PACKET_DECODE(Int64,backDt_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);hasGotReward_[k] = v;}}
return true;}
bool SPlayerCallInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,isBeCall_);
PACKET_ENCODE(Int32,isSetCaller_);
PACKET_ENCODE(Int64,backDt_);
PACKET_ENCODE(UVar32,hasGotReward_.size());
for(map<int32_t, int32_t>::const_iterator it=hasGotReward_.begin();it!=hasGotReward_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SPlayerCallInfo::clear(){
isBeCall_ = 0;
isSetCaller_ = 0;
backDt_ = 0;
hasGotReward_.clear();
}
bool SCountryGold::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,countryGold_);
PACKET_DECODE(Int32,point0Gold_);
if(!serverId_.decode(reader)){return false;}
return true;}
bool SCountryGold::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,countryGold_);
PACKET_ENCODE(Int32,point0Gold_);
if(!serverId_.encode(writer)){return false;}
return true;}
void SCountryGold::clear(){
countryGold_ = 0;
point0Gold_ = 0;
serverId_.clear();
}
bool SAddCountryGold::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,gold_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);string item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(String,item);params_.push_back(item);}}
return true;}
bool SAddCountryGold::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,gold_);
PACKET_ENCODE(UVar32,params_.size());
for(vector<string>::const_iterator vit=params_.begin();vit!=params_.end();++vit){PACKET_ENCODE(String,*vit);}
return true;}
void SAddCountryGold::clear(){
type_ = 0;
gold_ = 0;
params_.clear();
}
bool SDelCountryGold::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,gold_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);string item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(String,item);params_.push_back(item);}}
return true;}
bool SDelCountryGold::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,gold_);
PACKET_ENCODE(UVar32,params_.size());
for(vector<string>::const_iterator vit=params_.begin();vit!=params_.end();++vit){PACKET_ENCODE(String,*vit);}
return true;}
void SDelCountryGold::clear(){
type_ = 0;
gold_ = 0;
params_.clear();
}
bool SPlayerCountryGold::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,hasGotSalary_);
return true;}
bool SPlayerCountryGold::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,hasGotSalary_);
return true;}
void SPlayerCountryGold::clear(){
hasGotSalary_ = 0;
}
bool SCutTree::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,itemId_);
PACKET_DECODE(Int32,life_);
PACKET_DECODE(Int32,maxLife_);
if(!belongId_.decode(reader)){return false;}
PACKET_DECODE(String,belongName_);
PACKET_DECODE(Int64,refreshTime_);
return true;}
bool SCutTree::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,itemId_);
PACKET_ENCODE(Int32,life_);
PACKET_ENCODE(Int32,maxLife_);
if(!belongId_.encode(writer)){return false;}
PACKET_ENCODE(String,belongName_);
PACKET_ENCODE(Int64,refreshTime_);
return true;}
void SCutTree::clear(){
type_ = 0;
itemId_ = 0;
life_ = 0;
maxLife_ = 0;
belongId_.clear();
belongName_.clear();
refreshTime_ = 0;
}
bool SCutTreeInfo::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);SCutTree item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}trees_.push_back(item);}}
return true;}
bool SCutTreeInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,trees_.size());
for(vector<SCutTree>::const_iterator vit=trees_.begin();vit!=trees_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SCutTreeInfo::clear(){
trees_.clear();
}
bool SBless::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,targetCount_);
PACKET_DECODE(Int64,freeCd_);
PACKET_DECODE(Int32,useMoneyCount_);
return true;}
bool SBless::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,targetCount_);
PACKET_ENCODE(Int64,freeCd_);
PACKET_ENCODE(Int32,useMoneyCount_);
return true;}
void SBless::clear(){
type_ = 0;
targetCount_ = 0;
freeCd_ = 0;
useMoneyCount_ = 0;
}
bool SPlayerBless::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SBless v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}blesses_[k] = v;}}
return true;}
bool SPlayerBless::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,blesses_.size());
for(map<int32_t, SBless>::const_iterator it=blesses_.begin();it!=blesses_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SPlayerBless::clear(){
blesses_.clear();
}
bool SLunHuiBook::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,preDt_);
PACKET_DECODE(Int32,preSeqDays_);
PACKET_DECODE(Int64,beginDt_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);hasGot_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);hasGotMulCount_[k] = v;}}
PACKET_DECODE(Int32,useVipCount_);
return true;}
bool SLunHuiBook::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,preDt_);
PACKET_ENCODE(Int32,preSeqDays_);
PACKET_ENCODE(Int64,beginDt_);
PACKET_ENCODE(UVar32,hasGot_.size());
for(map<int32_t, int32_t>::const_iterator it=hasGot_.begin();it!=hasGot_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,hasGotMulCount_.size());
for(map<int32_t, int32_t>::const_iterator it=hasGotMulCount_.begin();it!=hasGotMulCount_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int32,useVipCount_);
return true;}
void SLunHuiBook::clear(){
preDt_ = 0;
preSeqDays_ = 0;
beginDt_ = 0;
hasGot_.clear();
hasGotMulCount_.clear();
useVipCount_ = 0;
}
bool STransport::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,missionCount_);
PACKET_DECODE(Int32,refreshCount_);
PACKET_DECODE(Int32,leftCount_);
PACKET_DECODE(Int32,fightEscort_);
return true;}
bool STransport::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,missionCount_);
PACKET_ENCODE(Int32,refreshCount_);
PACKET_ENCODE(Int32,leftCount_);
PACKET_ENCODE(Int32,fightEscort_);
return true;}
void STransport::clear(){
type_ = 0;
missionCount_ = 0;
refreshCount_ = 0;
leftCount_ = 0;
fightEscort_ = 0;
}
bool SEscortMissionFailed::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,fightName_);
PACKET_DECODE(Int32,configId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool SEscortMissionFailed::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,fightName_);
PACKET_ENCODE(Int32,configId_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SEscortMissionFailed::clear(){
entityId_.clear();
fightName_.clear();
configId_ = 0;
rewards_.clear();
}
bool SFightEscortSuccess::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,configId_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);rewards_[k] = v;}}
return true;}
bool SFightEscortSuccess::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,configId_);
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, int32_t>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SFightEscortSuccess::clear(){
configId_ = 0;
rewards_.clear();
}
bool SGetBackRewardSingle::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,round_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);items_[k] = v;}}
PACKET_DECODE(Int64,exp_);
return true;}
bool SGetBackRewardSingle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,round_);
PACKET_ENCODE(UVar32,items_.size());
for(map<int32_t, int32_t>::const_iterator it=items_.begin();it!=items_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(Int64,exp_);
return true;}
void SGetBackRewardSingle::clear(){
round_ = 0;
items_.clear();
exp_ = 0;
}
bool SGetBackRewardInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);counts_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SGetBackRewardSingle v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}rewards_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SGetBackRewardSingle v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}halfRewards_[k] = v;}}
return true;}
bool SGetBackRewardInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,counts_.size());
for(map<int32_t, int32_t>::const_iterator it=counts_.begin();it!=counts_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,rewards_.size());
for(map<int32_t, SGetBackRewardSingle>::const_iterator it=rewards_.begin();it!=rewards_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
PACKET_ENCODE(UVar32,halfRewards_.size());
for(map<int32_t, SGetBackRewardSingle>::const_iterator it=halfRewards_.begin();it!=halfRewards_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SGetBackRewardInfo::clear(){
counts_.clear();
rewards_.clear();
halfRewards_.clear();
}
bool SSyncThreeWorldInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,proxy_);
PACKET_DECODE(Int32,server_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);msgs::SFightPlayer item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}players_.push_back(item);}}
PACKET_DECODE(Int32,totalNum_);
return true;}
bool SSyncThreeWorldInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,proxy_);
PACKET_ENCODE(Int32,server_);
PACKET_ENCODE(UVar32,players_.size());
for(vector<msgs::SFightPlayer>::const_iterator vit=players_.begin();vit!=players_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(Int32,totalNum_);
return true;}
void SSyncThreeWorldInfo::clear(){
proxy_ = 0;
server_ = 0;
players_.clear();
totalNum_ = 0;
}
bool STreasureAdvanceSingle::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,star_);
PACKET_DECODE(Int32,bless_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);danMap_[k] = v;}}
return true;}
bool STreasureAdvanceSingle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,star_);
PACKET_ENCODE(Int32,bless_);
PACKET_ENCODE(UVar32,danMap_.size());
for(map<int32_t, int32_t>::const_iterator it=danMap_.begin();it!=danMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void STreasureAdvanceSingle::clear(){
type_ = 0;
level_ = 0;
star_ = 0;
bless_ = 0;
danMap_.clear();
}
bool STreasureAdvanceInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;STreasureAdvanceSingle v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}treasureMap_[k] = v;}}
return true;}
bool STreasureAdvanceInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,treasureMap_.size());
for(map<int32_t, STreasureAdvanceSingle>::const_iterator it=treasureMap_.begin();it!=treasureMap_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void STreasureAdvanceInfo::clear(){
treasureMap_.clear();
}
bool SMapEntity::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
if(!spacePos_.decode(reader)){return false;}
return true;}
bool SMapEntity::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
if(!spacePos_.encode(writer)){return false;}
return true;}
void SMapEntity::clear(){
entityId_.clear();
spacePos_.clear();
}
bool SMapPlayer::decode(CBufferReader &reader) {
if(!SMapEntity::decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int16,sex_);
PACKET_DECODE(Int16,career_);
PACKET_DECODE(Int16,careerLevel_);
PACKET_DECODE(Int16,camp_);
PACKET_DECODE(Int16,force_);
PACKET_DECODE(Int16,level_);
PACKET_DECODE(Int16,vipLevel_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Point item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}moving_.push_back(item);}}
PACKET_DECODE(Int16,direction_);
PACKET_DECODE(Int16,speed_);
PACKET_DECODE(Int64,curLife_);
PACKET_DECODE(Int64,maxLife_);
PACKET_DECODE(Int16,fightMode_);
PACKET_DECODE(Int16,status_);
PACKET_DECODE(Bool,isRide_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);entityShows_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);entityValues_[k] = v;}}
if(!ownerId_.decode(reader)){return false;}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);msgs::SBuffInfo item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}buffs_.push_back(item);}}
teamData_ = MsgPool::Instance()->DecodeMsg(reader);
guildData_ = MsgPool::Instance()->DecodeMsg(reader);
return true;}
bool SMapPlayer::encode(CBufferWriter &writer) const {
if(!SMapEntity::encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int16,sex_);
PACKET_ENCODE(Int16,career_);
PACKET_ENCODE(Int16,careerLevel_);
PACKET_ENCODE(Int16,camp_);
PACKET_ENCODE(Int16,force_);
PACKET_ENCODE(Int16,level_);
PACKET_ENCODE(Int16,vipLevel_);
PACKET_ENCODE(UVar32,moving_.size());
for(vector<Point>::const_iterator vit=moving_.begin();vit!=moving_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(Int16,direction_);
PACKET_ENCODE(Int16,speed_);
PACKET_ENCODE(Int64,curLife_);
PACKET_ENCODE(Int64,maxLife_);
PACKET_ENCODE(Int16,fightMode_);
PACKET_ENCODE(Int16,status_);
PACKET_ENCODE(Bool,isRide_);
PACKET_ENCODE(UVar32,entityShows_.size());
for(map<int16_t, int32_t>::const_iterator it=entityShows_.begin();it!=entityShows_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,entityValues_.size());
for(map<int16_t, int32_t>::const_iterator it=entityValues_.begin();it!=entityValues_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
if(!ownerId_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,buffs_.size());
for(vector<msgs::SBuffInfo>::const_iterator vit=buffs_.begin();vit!=buffs_.end();++vit){if(!vit->encode(writer)){return false;}}
if(!MsgPool::Instance()->EncodeMsg(writer, teamData_)){return false;}
if(!MsgPool::Instance()->EncodeMsg(writer, guildData_)){return false;}
return true;}
void SMapPlayer::clear(){
name_.clear();
sex_ = 0;
career_ = 0;
careerLevel_ = 0;
camp_ = 0;
force_ = 0;
level_ = 0;
vipLevel_ = 0;
moving_.clear();
direction_ = 0;
speed_ = 0;
curLife_ = 0;
maxLife_ = 0;
fightMode_ = 0;
status_ = 0;
isRide_ = 0;
entityShows_.clear();
entityValues_.clear();
ownerId_.clear();
buffs_.clear();
teamData_ = NULL;
guildData_ = NULL;
}
bool SMapRole::decode(CBufferReader &reader) {
if(!SMapEntity::decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int16,sex_);
PACKET_DECODE(Int16,career_);
PACKET_DECODE(Int16,careerLevel_);
PACKET_DECODE(Int16,camp_);
PACKET_DECODE(Int16,force_);
PACKET_DECODE(Int16,level_);
PACKET_DECODE(Int16,vipLevel_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Point item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}moving_.push_back(item);}}
PACKET_DECODE(Int16,direction_);
PACKET_DECODE(Int16,speed_);
PACKET_DECODE(Int16,bodySize_);
PACKET_DECODE(Int64,curLife_);
PACKET_DECODE(Int64,inPower_);
PACKET_DECODE(Int32,avaLife_);
PACKET_DECODE(Int64,maxLife_);
PACKET_DECODE(Int64,maxInPower_);
PACKET_DECODE(Int32,maxAvaLife_);
PACKET_DECODE(Int16,fightMode_);
PACKET_DECODE(Int16,status_);
PACKET_DECODE(Bool,isRide_);
if(!warHorse_.decode(reader)){return false;}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);entityShows_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);entityValues_[k] = v;}}
if(!ownerId_.decode(reader)){return false;}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);msgs::SBuffInfo item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}buffs_.push_back(item);}}
teamData_ = MsgPool::Instance()->DecodeMsg(reader);
guildData_ = MsgPool::Instance()->DecodeMsg(reader);
fightAttr_ = MsgPool::Instance()->DecodeMsg(reader);
return true;}
bool SMapRole::encode(CBufferWriter &writer) const {
if(!SMapEntity::encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int16,sex_);
PACKET_ENCODE(Int16,career_);
PACKET_ENCODE(Int16,careerLevel_);
PACKET_ENCODE(Int16,camp_);
PACKET_ENCODE(Int16,force_);
PACKET_ENCODE(Int16,level_);
PACKET_ENCODE(Int16,vipLevel_);
PACKET_ENCODE(UVar32,moving_.size());
for(vector<Point>::const_iterator vit=moving_.begin();vit!=moving_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(Int16,direction_);
PACKET_ENCODE(Int16,speed_);
PACKET_ENCODE(Int16,bodySize_);
PACKET_ENCODE(Int64,curLife_);
PACKET_ENCODE(Int64,inPower_);
PACKET_ENCODE(Int32,avaLife_);
PACKET_ENCODE(Int64,maxLife_);
PACKET_ENCODE(Int64,maxInPower_);
PACKET_ENCODE(Int32,maxAvaLife_);
PACKET_ENCODE(Int16,fightMode_);
PACKET_ENCODE(Int16,status_);
PACKET_ENCODE(Bool,isRide_);
if(!warHorse_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,entityShows_.size());
for(map<int16_t, int32_t>::const_iterator it=entityShows_.begin();it!=entityShows_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,entityValues_.size());
for(map<int16_t, int32_t>::const_iterator it=entityValues_.begin();it!=entityValues_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
if(!ownerId_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,buffs_.size());
for(vector<msgs::SBuffInfo>::const_iterator vit=buffs_.begin();vit!=buffs_.end();++vit){if(!vit->encode(writer)){return false;}}
if(!MsgPool::Instance()->EncodeMsg(writer, teamData_)){return false;}
if(!MsgPool::Instance()->EncodeMsg(writer, guildData_)){return false;}
if(!MsgPool::Instance()->EncodeMsg(writer, fightAttr_)){return false;}
return true;}
void SMapRole::clear(){
name_.clear();
sex_ = 0;
career_ = 0;
careerLevel_ = 0;
camp_ = 0;
force_ = 0;
level_ = 0;
vipLevel_ = 0;
moving_.clear();
direction_ = 0;
speed_ = 0;
bodySize_ = 0;
curLife_ = 0;
inPower_ = 0;
avaLife_ = 0;
maxLife_ = 0;
maxInPower_ = 0;
maxAvaLife_ = 0;
fightMode_ = 0;
status_ = 0;
isRide_ = 0;
warHorse_.clear();
entityShows_.clear();
entityValues_.clear();
ownerId_.clear();
buffs_.clear();
teamData_ = NULL;
guildData_ = NULL;
fightAttr_ = NULL;
}
bool SMapMonster::decode(CBufferReader &reader) {
if(!SMapEntity::decode(reader)){return false;}
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,monsterId_);
PACKET_DECODE(Int16,force_);
PACKET_DECODE(Int16,level_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Point item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}moving_.push_back(item);}}
PACKET_DECODE(Int16,direction_);
PACKET_DECODE(Int16,speed_);
PACKET_DECODE(Int64,curLife_);
PACKET_DECODE(Int64,maxLife_);
PACKET_DECODE(Int32,avaLife_);
PACKET_DECODE(Int32,maxAvaLife_);
PACKET_DECODE(Int16,status_);
if(!ownerId_.decode(reader)){return false;}
if(!belongId_.decode(reader)){return false;}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);msgs::SBuffInfo item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}buffs_.push_back(item);}}
PACKET_DECODE(Int32,shield_);
PACKET_DECODE(String,extend_);
return true;}
bool SMapMonster::encode(CBufferWriter &writer) const {
if(!SMapEntity::encode(writer)){return false;}
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,monsterId_);
PACKET_ENCODE(Int16,force_);
PACKET_ENCODE(Int16,level_);
PACKET_ENCODE(UVar32,moving_.size());
for(vector<Point>::const_iterator vit=moving_.begin();vit!=moving_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(Int16,direction_);
PACKET_ENCODE(Int16,speed_);
PACKET_ENCODE(Int64,curLife_);
PACKET_ENCODE(Int64,maxLife_);
PACKET_ENCODE(Int32,avaLife_);
PACKET_ENCODE(Int32,maxAvaLife_);
PACKET_ENCODE(Int16,status_);
if(!ownerId_.encode(writer)){return false;}
if(!belongId_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,buffs_.size());
for(vector<msgs::SBuffInfo>::const_iterator vit=buffs_.begin();vit!=buffs_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(Int32,shield_);
PACKET_ENCODE(String,extend_);
return true;}
void SMapMonster::clear(){
name_.clear();
monsterId_ = 0;
force_ = 0;
level_ = 0;
moving_.clear();
direction_ = 0;
speed_ = 0;
curLife_ = 0;
maxLife_ = 0;
avaLife_ = 0;
maxAvaLife_ = 0;
status_ = 0;
ownerId_.clear();
belongId_.clear();
buffs_.clear();
shield_ = 0;
extend_.clear();
}
bool SMapPet::decode(CBufferReader &reader) {
if(!SMapEntity::decode(reader)){return false;}
PACKET_DECODE(Int32,petId_);
PACKET_DECODE(Int16,force_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Point item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}moving_.push_back(item);}}
PACKET_DECODE(Int16,direction_);
PACKET_DECODE(Int16,speed_);
PACKET_DECODE(Int64,attack_);
PACKET_DECODE(Int64,curLife_);
PACKET_DECODE(Int64,maxLife_);
PACKET_DECODE(Int16,status_);
if(!ownerId_.decode(reader)){return false;}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);msgs::SBuffInfo item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}buffs_.push_back(item);}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);entityShows_[k] = v;}}
return true;}
bool SMapPet::encode(CBufferWriter &writer) const {
if(!SMapEntity::encode(writer)){return false;}
PACKET_ENCODE(Int32,petId_);
PACKET_ENCODE(Int16,force_);
PACKET_ENCODE(UVar32,moving_.size());
for(vector<Point>::const_iterator vit=moving_.begin();vit!=moving_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(Int16,direction_);
PACKET_ENCODE(Int16,speed_);
PACKET_ENCODE(Int64,attack_);
PACKET_ENCODE(Int64,curLife_);
PACKET_ENCODE(Int64,maxLife_);
PACKET_ENCODE(Int16,status_);
if(!ownerId_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,buffs_.size());
for(vector<msgs::SBuffInfo>::const_iterator vit=buffs_.begin();vit!=buffs_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(UVar32,entityShows_.size());
for(map<int16_t, int32_t>::const_iterator it=entityShows_.begin();it!=entityShows_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SMapPet::clear(){
petId_ = 0;
force_ = 0;
moving_.clear();
direction_ = 0;
speed_ = 0;
attack_ = 0;
curLife_ = 0;
maxLife_ = 0;
status_ = 0;
ownerId_.clear();
buffs_.clear();
entityShows_.clear();
}
bool SMapNpc::decode(CBufferReader &reader) {
if(!SMapEntity::decode(reader)){return false;}
PACKET_DECODE(Int32,npcId_);
return true;}
bool SMapNpc::encode(CBufferWriter &writer) const {
if(!SMapEntity::encode(writer)){return false;}
PACKET_ENCODE(Int32,npcId_);
return true;}
void SMapNpc::clear(){
npcId_ = 0;
}
bool SMapDrop::decode(CBufferReader &reader) {
if(!SMapEntity::decode(reader)){return false;}
if(!belongTo_.decode(reader)){return false;}
PACKET_DECODE(Int32,itemId_);
PACKET_DECODE(Int32,itemNum_);
return true;}
bool SMapDrop::encode(CBufferWriter &writer) const {
if(!SMapEntity::encode(writer)){return false;}
if(!belongTo_.encode(writer)){return false;}
PACKET_ENCODE(Int32,itemId_);
PACKET_ENCODE(Int32,itemNum_);
return true;}
void SMapDrop::clear(){
belongTo_.clear();
itemId_ = 0;
itemNum_ = 0;
}
bool SMapCorpse::decode(CBufferReader &reader) {
if(!SMapEntity::decode(reader)){return false;}
PACKET_DECODE(Int32,monsterId_);
PACKET_DECODE(Int32,line_);
PACKET_DECODE(Int64,reviveTime_);
return true;}
bool SMapCorpse::encode(CBufferWriter &writer) const {
if(!SMapEntity::encode(writer)){return false;}
PACKET_ENCODE(Int32,monsterId_);
PACKET_ENCODE(Int32,line_);
PACKET_ENCODE(Int64,reviveTime_);
return true;}
void SMapCorpse::clear(){
monsterId_ = 0;
line_ = 0;
reviveTime_ = 0;
}
bool SMapWarHorse::decode(CBufferReader &reader) {
if(!SMapEntity::decode(reader)){return false;}
PACKET_DECODE(Int32,warHorseId_);
PACKET_DECODE(Int16,moveId_);
PACKET_DECODE(Int16,direction_);
PACKET_DECODE(Int16,speed_);
PACKET_DECODE(Bool,isHide_);
return true;}
bool SMapWarHorse::encode(CBufferWriter &writer) const {
if(!SMapEntity::encode(writer)){return false;}
PACKET_ENCODE(Int32,warHorseId_);
PACKET_ENCODE(Int16,moveId_);
PACKET_ENCODE(Int16,direction_);
PACKET_ENCODE(Int16,speed_);
PACKET_ENCODE(Bool,isHide_);
return true;}
void SMapWarHorse::clear(){
warHorseId_ = 0;
moveId_ = 0;
direction_ = 0;
speed_ = 0;
isHide_ = 0;
}
bool SMapZazen::decode(CBufferReader &reader) {
if(!SMapEntity::decode(reader)){return false;}
PACKET_DECODE(Int16,career_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,pointId_);
PACKET_DECODE(Int64,protectDt_);
if(!tagEntityId_.decode(reader)){return false;}
return true;}
bool SMapZazen::encode(CBufferWriter &writer) const {
if(!SMapEntity::encode(writer)){return false;}
PACKET_ENCODE(Int16,career_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,pointId_);
PACKET_ENCODE(Int64,protectDt_);
if(!tagEntityId_.encode(writer)){return false;}
return true;}
void SMapZazen::clear(){
career_ = 0;
name_.clear();
pointId_ = 0;
protectDt_ = 0;
tagEntityId_.clear();
}
bool SMapArena::decode(CBufferReader &reader) {
if(!SMapEntity::decode(reader)){return false;}
PACKET_DECODE(Int32,rank_);
PACKET_DECODE(Int16,career_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Int16,direction_);
if(!tagEntityId_.decode(reader)){return false;}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);entityShows_[k] = v;}}
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int16_t k;int32_t v;PACKET_DECODE(Int16,k);PACKET_DECODE(Int32,v);entityValues_[k] = v;}}
return true;}
bool SMapArena::encode(CBufferWriter &writer) const {
if(!SMapEntity::encode(writer)){return false;}
PACKET_ENCODE(Int32,rank_);
PACKET_ENCODE(Int16,career_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int16,direction_);
if(!tagEntityId_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,entityShows_.size());
for(map<int16_t, int32_t>::const_iterator it=entityShows_.begin();it!=entityShows_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
PACKET_ENCODE(UVar32,entityValues_.size());
for(map<int16_t, int32_t>::const_iterator it=entityValues_.begin();it!=entityValues_.end();++it){PACKET_ENCODE(Int16,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SMapArena::clear(){
rank_ = 0;
career_ = 0;
name_.clear();
direction_ = 0;
tagEntityId_.clear();
entityShows_.clear();
entityValues_.clear();
}
bool SMapEntityEnters::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Msg* item;for(uint32_t vi=0;vi<vlen;++vi){item = MsgPool::Instance()->DecodeMsg(reader);entities_.push_back(item);}}
return true;}
bool SMapEntityEnters::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,entities_.size());
for(vector<Msg*>::const_iterator vit=entities_.begin();vit!=entities_.end();++vit){if(!MsgPool::Instance()->EncodeMsg(writer, *vit)){return false;}}
return true;}
void SMapEntityEnters::clear(){
entities_.clear();
}
bool SMapEntityMoves::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Point item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}path_.push_back(item);}}
return true;}
bool SMapEntityMoves::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,path_.size());
for(vector<Point>::const_iterator vit=path_.begin();vit!=path_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SMapEntityMoves::clear(){
entityId_.clear();
path_.clear();
}
bool SMapEntityLeaves::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Identity item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}entityIds_.push_back(item);}}
return true;}
bool SMapEntityLeaves::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,entityIds_.size());
for(vector<Identity>::const_iterator vit=entityIds_.begin();vit!=entityIds_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SMapEntityLeaves::clear(){
entityIds_.clear();
}
bool SPlayerEnterMap::decode(CBufferReader &reader) {
PACKET_DECODE(UInt16,incId_);
if(!enterCellId_.decode(reader)){return false;}
PACKET_DECODE(Int16,cellLine_);
PACKET_DECODE(Int32,spaceId_);
if(!spacePos_.decode(reader)){return false;}
PACKET_DECODE(Int32,copyCode_);
PACKET_DECODE(Int16,fightMode_);
PACKET_DECODE(Bool,useUninterested_);
return true;}
bool SPlayerEnterMap::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UInt16,incId_);
if(!enterCellId_.encode(writer)){return false;}
PACKET_ENCODE(Int16,cellLine_);
PACKET_ENCODE(Int32,spaceId_);
if(!spacePos_.encode(writer)){return false;}
PACKET_ENCODE(Int32,copyCode_);
PACKET_ENCODE(Int16,fightMode_);
PACKET_ENCODE(Bool,useUninterested_);
return true;}
void SPlayerEnterMap::clear(){
incId_ = 0;
enterCellId_.clear();
cellLine_ = 0;
spaceId_ = 0;
spacePos_.clear();
copyCode_ = 0;
fightMode_ = 0;
useUninterested_ = 0;
}
bool SPlayerLeaveMap::decode(CBufferReader &reader) {
PACKET_DECODE(UInt16,incId_);
if(!leaveCellId_.decode(reader)){return false;}
return true;}
bool SPlayerLeaveMap::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UInt16,incId_);
if(!leaveCellId_.encode(writer)){return false;}
return true;}
void SPlayerLeaveMap::clear(){
incId_ = 0;
leaveCellId_.clear();
}
bool SPlayerCurrentMapPos::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(UInt16,moveId_);
if(!curPos_.decode(reader)){return false;}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Point item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}moving_.push_back(item);}}
PACKET_DECODE(Int16,direction_);
return true;}
bool SPlayerCurrentMapPos::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(UInt16,moveId_);
if(!curPos_.encode(writer)){return false;}
PACKET_ENCODE(UVar32,moving_.size());
for(vector<Point>::const_iterator vit=moving_.begin();vit!=moving_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(Int16,direction_);
return true;}
void SPlayerCurrentMapPos::clear(){
entityId_.clear();
moveId_ = 0;
curPos_.clear();
moving_.clear();
direction_ = 0;
}
bool SRoleEnterMap::decode(CBufferReader &reader) {
PACKET_DECODE(Bool,isMain_);
PACKET_DECODE(UInt16,moveId_);
fightData_ = MsgPool::Instance()->DecodeMsg(reader);
return true;}
bool SRoleEnterMap::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Bool,isMain_);
PACKET_ENCODE(UInt16,moveId_);
if(!MsgPool::Instance()->EncodeMsg(writer, fightData_)){return false;}
return true;}
void SRoleEnterMap::clear(){
isMain_ = 0;
moveId_ = 0;
fightData_ = NULL;
}
bool SRoleEnterMapEnd::decode(CBufferReader &reader) {
PACKET_DECODE(Int16,roleNum_);
return true;}
bool SRoleEnterMapEnd::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int16,roleNum_);
return true;}
void SRoleEnterMapEnd::clear(){
roleNum_ = 0;
}
bool SRoleLeaveMap::decode(CBufferReader &reader) {
if(!cellId_.decode(reader)){return false;}
if(!entityId_.decode(reader)){return false;}
return true;}
bool SRoleLeaveMap::encode(CBufferWriter &writer) const {
if(!cellId_.encode(writer)){return false;}
if(!entityId_.encode(writer)){return false;}
return true;}
void SRoleLeaveMap::clear(){
cellId_.clear();
entityId_.clear();
}
bool SPlayerMove::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(Int64,operTime_);
PACKET_DECODE(UInt16,moveId_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Point item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}path_.push_back(item);}}
return true;}
bool SPlayerMove::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(Int64,operTime_);
PACKET_ENCODE(UInt16,moveId_);
PACKET_ENCODE(UVar32,path_.size());
for(vector<Point>::const_iterator vit=path_.begin();vit!=path_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPlayerMove::clear(){
entityId_.clear();
operTime_ = 0;
moveId_ = 0;
path_.clear();
}
bool SPlayerUpdateMapPos::decode(CBufferReader &reader) {
PACKET_DECODE(UInt16,moveId_);
if(!pos_.decode(reader)){return false;}
return true;}
bool SPlayerUpdateMapPos::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UInt16,moveId_);
if(!pos_.encode(writer)){return false;}
return true;}
void SPlayerUpdateMapPos::clear(){
moveId_ = 0;
pos_.clear();
}
bool SPlayerLeaveByCell::decode(CBufferReader &reader) {
PACKET_DECODE(UInt16,incId_);
if(!leaveCellId_.decode(reader)){return false;}
return true;}
bool SPlayerLeaveByCell::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UInt16,incId_);
if(!leaveCellId_.encode(writer)){return false;}
return true;}
void SPlayerLeaveByCell::clear(){
incId_ = 0;
leaveCellId_.clear();
}
bool SEntityJumpTo::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(String,jumpId_);
PACKET_DECODE(Bool,isReverse_);
if(!endPos_.decode(reader)){return false;}
return true;}
bool SEntityJumpTo::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(String,jumpId_);
PACKET_ENCODE(Bool,isReverse_);
if(!endPos_.encode(writer)){return false;}
return true;}
void SEntityJumpTo::clear(){
entityId_.clear();
jumpId_.clear();
isReverse_ = 0;
endPos_.clear();
}
bool SPlayerCollect::decode(CBufferReader &reader) {
if(!fromEntityId_.decode(reader)){return false;}
if(!toEntityId_.decode(reader)){return false;}
PACKET_DECODE(Int64,endTime_);
return true;}
bool SPlayerCollect::encode(CBufferWriter &writer) const {
if(!fromEntityId_.encode(writer)){return false;}
if(!toEntityId_.encode(writer)){return false;}
PACKET_ENCODE(Int64,endTime_);
return true;}
void SPlayerCollect::clear(){
fromEntityId_.clear();
toEntityId_.clear();
endTime_ = 0;
}
bool SPlayerEndCollect::decode(CBufferReader &reader) {
if(!fromEntityId_.decode(reader)){return false;}
if(!toEntityId_.decode(reader)){return false;}
return true;}
bool SPlayerEndCollect::encode(CBufferWriter &writer) const {
if(!fromEntityId_.encode(writer)){return false;}
if(!toEntityId_.encode(writer)){return false;}
return true;}
void SPlayerEndCollect::clear(){
fromEntityId_.clear();
toEntityId_.clear();
}
bool SPlayerBreakCollect::decode(CBufferReader &reader) {
if(!fromEntityId_.decode(reader)){return false;}
if(!toEntityId_.decode(reader)){return false;}
return true;}
bool SPlayerBreakCollect::encode(CBufferWriter &writer) const {
if(!fromEntityId_.encode(writer)){return false;}
if(!toEntityId_.encode(writer)){return false;}
return true;}
void SPlayerBreakCollect::clear(){
fromEntityId_.clear();
toEntityId_.clear();
}
bool SPlayerChangeMainRole::decode(CBufferReader &reader) {
if(!oldEntityId_.decode(reader)){return false;}
if(!newEntityId_.decode(reader)){return false;}
return true;}
bool SPlayerChangeMainRole::encode(CBufferWriter &writer) const {
if(!oldEntityId_.encode(writer)){return false;}
if(!newEntityId_.encode(writer)){return false;}
return true;}
void SPlayerChangeMainRole::clear(){
oldEntityId_.clear();
newEntityId_.clear();
}
bool SMapMiniPlayer::decode(CBufferReader &reader) {
if(!playerId_.decode(reader)){return false;}
PACKET_DECODE(String,name_);
if(!point_.decode(reader)){return false;}
return true;}
bool SMapMiniPlayer::encode(CBufferWriter &writer) const {
if(!playerId_.encode(writer)){return false;}
PACKET_ENCODE(String,name_);
if(!point_.encode(writer)){return false;}
return true;}
void SMapMiniPlayer::clear(){
playerId_.clear();
name_.clear();
point_.clear();
}
bool SYuanshenInfo::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,fightType_);
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);activeMap_[k] = v;}}
return true;}
bool SYuanshenInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,fightType_);
PACKET_ENCODE(UVar32,activeMap_.size());
for(map<int32_t, int32_t>::const_iterator it=activeMap_.begin();it!=activeMap_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SYuanshenInfo::clear(){
level_ = 0;
fightType_ = 0;
activeMap_.clear();
}
bool SElementSingle::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,exp_);
return true;}
bool SElementSingle::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,exp_);
return true;}
void SElementSingle::clear(){
level_ = 0;
exp_ = 0;
}
bool SElementInfo::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;SElementSingle v;PACKET_DECODE(Int32,k);if(!v.decode(reader)){return false;}elementMap_[k] = v;}}
return true;}
bool SElementInfo::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,elementMap_.size());
for(map<int32_t, SElementSingle>::const_iterator it=elementMap_.begin();it!=elementMap_.end();++it){PACKET_ENCODE(Int32,it->first);if(!it->second.encode(writer)){return false;}}
return true;}
void SElementInfo::clear(){
elementMap_.clear();
}
}