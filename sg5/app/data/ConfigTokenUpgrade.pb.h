// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ConfigTokenUpgrade.proto

#ifndef PROTOBUF_ConfigTokenUpgrade_2eproto__INCLUDED
#define PROTOBUF_ConfigTokenUpgrade_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
#include "RewardConfig.pb.h"
// @@protoc_insertion_point(includes)

namespace ConfigTokenUpgrade {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ConfigTokenUpgrade_2eproto();
void protobuf_AssignDesc_ConfigTokenUpgrade_2eproto();
void protobuf_ShutdownFile_ConfigTokenUpgrade_2eproto();

class ChargeReceive;
class TurnTable;
class ChargeLottery;
class TokenUpgrade;

// ===================================================================

class ChargeReceive : public ::google::protobuf::Message {
 public:
  ChargeReceive();
  virtual ~ChargeReceive();

  ChargeReceive(const ChargeReceive& from);

  inline ChargeReceive& operator=(const ChargeReceive& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ChargeReceive& default_instance();

  void Swap(ChargeReceive* other);

  // implements Message ----------------------------------------------

  ChargeReceive* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ChargeReceive& from);
  void MergeFrom(const ChargeReceive& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required uint32 point = 1;
  inline bool has_point() const;
  inline void clear_point();
  static const int kPointFieldNumber = 1;
  inline ::google::protobuf::uint32 point() const;
  inline void set_point(::google::protobuf::uint32 value);

  // required .RewardConfig.RewardItemCfg reward = 2;
  inline bool has_reward() const;
  inline void clear_reward();
  static const int kRewardFieldNumber = 2;
  inline const ::RewardConfig::RewardItemCfg& reward() const;
  inline ::RewardConfig::RewardItemCfg* mutable_reward();
  inline ::RewardConfig::RewardItemCfg* release_reward();
  inline void set_allocated_reward(::RewardConfig::RewardItemCfg* reward);

  // @@protoc_insertion_point(class_scope:ConfigTokenUpgrade.ChargeReceive)
 private:
  inline void set_has_point();
  inline void clear_has_point();
  inline void set_has_reward();
  inline void clear_has_reward();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::RewardConfig::RewardItemCfg* reward_;
  ::google::protobuf::uint32 point_;
  friend void  protobuf_AddDesc_ConfigTokenUpgrade_2eproto();
  friend void protobuf_AssignDesc_ConfigTokenUpgrade_2eproto();
  friend void protobuf_ShutdownFile_ConfigTokenUpgrade_2eproto();

  void InitAsDefaultInstance();
  static ChargeReceive* default_instance_;
};
// -------------------------------------------------------------------

class TurnTable : public ::google::protobuf::Message {
 public:
  TurnTable();
  virtual ~TurnTable();

  TurnTable(const TurnTable& from);

  inline TurnTable& operator=(const TurnTable& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const TurnTable& default_instance();

  void Swap(TurnTable* other);

  // implements Message ----------------------------------------------

  TurnTable* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TurnTable& from);
  void MergeFrom(const TurnTable& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required uint32 weight = 1;
  inline bool has_weight() const;
  inline void clear_weight();
  static const int kWeightFieldNumber = 1;
  inline ::google::protobuf::uint32 weight() const;
  inline void set_weight(::google::protobuf::uint32 value);

  // required .RewardConfig.RewardItemCfg reward = 2;
  inline bool has_reward() const;
  inline void clear_reward();
  static const int kRewardFieldNumber = 2;
  inline const ::RewardConfig::RewardItemCfg& reward() const;
  inline ::RewardConfig::RewardItemCfg* mutable_reward();
  inline ::RewardConfig::RewardItemCfg* release_reward();
  inline void set_allocated_reward(::RewardConfig::RewardItemCfg* reward);

  // @@protoc_insertion_point(class_scope:ConfigTokenUpgrade.TurnTable)
 private:
  inline void set_has_weight();
  inline void clear_has_weight();
  inline void set_has_reward();
  inline void clear_has_reward();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::RewardConfig::RewardItemCfg* reward_;
  ::google::protobuf::uint32 weight_;
  friend void  protobuf_AddDesc_ConfigTokenUpgrade_2eproto();
  friend void protobuf_AssignDesc_ConfigTokenUpgrade_2eproto();
  friend void protobuf_ShutdownFile_ConfigTokenUpgrade_2eproto();

  void InitAsDefaultInstance();
  static TurnTable* default_instance_;
};
// -------------------------------------------------------------------

class ChargeLottery : public ::google::protobuf::Message {
 public:
  ChargeLottery();
  virtual ~ChargeLottery();

  ChargeLottery(const ChargeLottery& from);

  inline ChargeLottery& operator=(const ChargeLottery& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ChargeLottery& default_instance();

  void Swap(ChargeLottery* other);

  // implements Message ----------------------------------------------

  ChargeLottery* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ChargeLottery& from);
  void MergeFrom(const ChargeLottery& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required uint32 cost = 1;
  inline bool has_cost() const;
  inline void clear_cost();
  static const int kCostFieldNumber = 1;
  inline ::google::protobuf::uint32 cost() const;
  inline void set_cost(::google::protobuf::uint32 value);

  // required uint32 limit = 2;
  inline bool has_limit() const;
  inline void clear_limit();
  static const int kLimitFieldNumber = 2;
  inline ::google::protobuf::uint32 limit() const;
  inline void set_limit(::google::protobuf::uint32 value);

  // repeated .ConfigTokenUpgrade.TurnTable turntable = 3;
  inline int turntable_size() const;
  inline void clear_turntable();
  static const int kTurntableFieldNumber = 3;
  inline const ::ConfigTokenUpgrade::TurnTable& turntable(int index) const;
  inline ::ConfigTokenUpgrade::TurnTable* mutable_turntable(int index);
  inline ::ConfigTokenUpgrade::TurnTable* add_turntable();
  inline const ::google::protobuf::RepeatedPtrField< ::ConfigTokenUpgrade::TurnTable >&
      turntable() const;
  inline ::google::protobuf::RepeatedPtrField< ::ConfigTokenUpgrade::TurnTable >*
      mutable_turntable();

  // @@protoc_insertion_point(class_scope:ConfigTokenUpgrade.ChargeLottery)
 private:
  inline void set_has_cost();
  inline void clear_has_cost();
  inline void set_has_limit();
  inline void clear_has_limit();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 cost_;
  ::google::protobuf::uint32 limit_;
  ::google::protobuf::RepeatedPtrField< ::ConfigTokenUpgrade::TurnTable > turntable_;
  friend void  protobuf_AddDesc_ConfigTokenUpgrade_2eproto();
  friend void protobuf_AssignDesc_ConfigTokenUpgrade_2eproto();
  friend void protobuf_ShutdownFile_ConfigTokenUpgrade_2eproto();

  void InitAsDefaultInstance();
  static ChargeLottery* default_instance_;
};
// -------------------------------------------------------------------

class TokenUpgrade : public ::google::protobuf::Message {
 public:
  TokenUpgrade();
  virtual ~TokenUpgrade();

  TokenUpgrade(const TokenUpgrade& from);

  inline TokenUpgrade& operator=(const TokenUpgrade& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const TokenUpgrade& default_instance();

  void Swap(TokenUpgrade* other);

  // implements Message ----------------------------------------------

  TokenUpgrade* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TokenUpgrade& from);
  void MergeFrom(const TokenUpgrade& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .ConfigTokenUpgrade.ChargeReceive charge_receive = 1;
  inline int charge_receive_size() const;
  inline void clear_charge_receive();
  static const int kChargeReceiveFieldNumber = 1;
  inline const ::ConfigTokenUpgrade::ChargeReceive& charge_receive(int index) const;
  inline ::ConfigTokenUpgrade::ChargeReceive* mutable_charge_receive(int index);
  inline ::ConfigTokenUpgrade::ChargeReceive* add_charge_receive();
  inline const ::google::protobuf::RepeatedPtrField< ::ConfigTokenUpgrade::ChargeReceive >&
      charge_receive() const;
  inline ::google::protobuf::RepeatedPtrField< ::ConfigTokenUpgrade::ChargeReceive >*
      mutable_charge_receive();

  // required .ConfigTokenUpgrade.ChargeLottery charge_lottery = 2;
  inline bool has_charge_lottery() const;
  inline void clear_charge_lottery();
  static const int kChargeLotteryFieldNumber = 2;
  inline const ::ConfigTokenUpgrade::ChargeLottery& charge_lottery() const;
  inline ::ConfigTokenUpgrade::ChargeLottery* mutable_charge_lottery();
  inline ::ConfigTokenUpgrade::ChargeLottery* release_charge_lottery();
  inline void set_allocated_charge_lottery(::ConfigTokenUpgrade::ChargeLottery* charge_lottery);

  // @@protoc_insertion_point(class_scope:ConfigTokenUpgrade.TokenUpgrade)
 private:
  inline void set_has_charge_lottery();
  inline void clear_has_charge_lottery();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::ConfigTokenUpgrade::ChargeReceive > charge_receive_;
  ::ConfigTokenUpgrade::ChargeLottery* charge_lottery_;
  friend void  protobuf_AddDesc_ConfigTokenUpgrade_2eproto();
  friend void protobuf_AssignDesc_ConfigTokenUpgrade_2eproto();
  friend void protobuf_ShutdownFile_ConfigTokenUpgrade_2eproto();

  void InitAsDefaultInstance();
  static TokenUpgrade* default_instance_;
};
// ===================================================================


// ===================================================================

// ChargeReceive

// required uint32 point = 1;
inline bool ChargeReceive::has_point() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ChargeReceive::set_has_point() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ChargeReceive::clear_has_point() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ChargeReceive::clear_point() {
  point_ = 0u;
  clear_has_point();
}
inline ::google::protobuf::uint32 ChargeReceive::point() const {
  // @@protoc_insertion_point(field_get:ConfigTokenUpgrade.ChargeReceive.point)
  return point_;
}
inline void ChargeReceive::set_point(::google::protobuf::uint32 value) {
  set_has_point();
  point_ = value;
  // @@protoc_insertion_point(field_set:ConfigTokenUpgrade.ChargeReceive.point)
}

// required .RewardConfig.RewardItemCfg reward = 2;
inline bool ChargeReceive::has_reward() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ChargeReceive::set_has_reward() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ChargeReceive::clear_has_reward() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ChargeReceive::clear_reward() {
  if (reward_ != NULL) reward_->::RewardConfig::RewardItemCfg::Clear();
  clear_has_reward();
}
inline const ::RewardConfig::RewardItemCfg& ChargeReceive::reward() const {
  // @@protoc_insertion_point(field_get:ConfigTokenUpgrade.ChargeReceive.reward)
  return reward_ != NULL ? *reward_ : *default_instance_->reward_;
}
inline ::RewardConfig::RewardItemCfg* ChargeReceive::mutable_reward() {
  set_has_reward();
  if (reward_ == NULL) reward_ = new ::RewardConfig::RewardItemCfg;
  // @@protoc_insertion_point(field_mutable:ConfigTokenUpgrade.ChargeReceive.reward)
  return reward_;
}
inline ::RewardConfig::RewardItemCfg* ChargeReceive::release_reward() {
  clear_has_reward();
  ::RewardConfig::RewardItemCfg* temp = reward_;
  reward_ = NULL;
  return temp;
}
inline void ChargeReceive::set_allocated_reward(::RewardConfig::RewardItemCfg* reward) {
  delete reward_;
  reward_ = reward;
  if (reward) {
    set_has_reward();
  } else {
    clear_has_reward();
  }
  // @@protoc_insertion_point(field_set_allocated:ConfigTokenUpgrade.ChargeReceive.reward)
}

// -------------------------------------------------------------------

// TurnTable

// required uint32 weight = 1;
inline bool TurnTable::has_weight() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TurnTable::set_has_weight() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TurnTable::clear_has_weight() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TurnTable::clear_weight() {
  weight_ = 0u;
  clear_has_weight();
}
inline ::google::protobuf::uint32 TurnTable::weight() const {
  // @@protoc_insertion_point(field_get:ConfigTokenUpgrade.TurnTable.weight)
  return weight_;
}
inline void TurnTable::set_weight(::google::protobuf::uint32 value) {
  set_has_weight();
  weight_ = value;
  // @@protoc_insertion_point(field_set:ConfigTokenUpgrade.TurnTable.weight)
}

// required .RewardConfig.RewardItemCfg reward = 2;
inline bool TurnTable::has_reward() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TurnTable::set_has_reward() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TurnTable::clear_has_reward() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TurnTable::clear_reward() {
  if (reward_ != NULL) reward_->::RewardConfig::RewardItemCfg::Clear();
  clear_has_reward();
}
inline const ::RewardConfig::RewardItemCfg& TurnTable::reward() const {
  // @@protoc_insertion_point(field_get:ConfigTokenUpgrade.TurnTable.reward)
  return reward_ != NULL ? *reward_ : *default_instance_->reward_;
}
inline ::RewardConfig::RewardItemCfg* TurnTable::mutable_reward() {
  set_has_reward();
  if (reward_ == NULL) reward_ = new ::RewardConfig::RewardItemCfg;
  // @@protoc_insertion_point(field_mutable:ConfigTokenUpgrade.TurnTable.reward)
  return reward_;
}
inline ::RewardConfig::RewardItemCfg* TurnTable::release_reward() {
  clear_has_reward();
  ::RewardConfig::RewardItemCfg* temp = reward_;
  reward_ = NULL;
  return temp;
}
inline void TurnTable::set_allocated_reward(::RewardConfig::RewardItemCfg* reward) {
  delete reward_;
  reward_ = reward;
  if (reward) {
    set_has_reward();
  } else {
    clear_has_reward();
  }
  // @@protoc_insertion_point(field_set_allocated:ConfigTokenUpgrade.TurnTable.reward)
}

// -------------------------------------------------------------------

// ChargeLottery

// required uint32 cost = 1;
inline bool ChargeLottery::has_cost() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ChargeLottery::set_has_cost() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ChargeLottery::clear_has_cost() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ChargeLottery::clear_cost() {
  cost_ = 0u;
  clear_has_cost();
}
inline ::google::protobuf::uint32 ChargeLottery::cost() const {
  // @@protoc_insertion_point(field_get:ConfigTokenUpgrade.ChargeLottery.cost)
  return cost_;
}
inline void ChargeLottery::set_cost(::google::protobuf::uint32 value) {
  set_has_cost();
  cost_ = value;
  // @@protoc_insertion_point(field_set:ConfigTokenUpgrade.ChargeLottery.cost)
}

// required uint32 limit = 2;
inline bool ChargeLottery::has_limit() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ChargeLottery::set_has_limit() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ChargeLottery::clear_has_limit() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ChargeLottery::clear_limit() {
  limit_ = 0u;
  clear_has_limit();
}
inline ::google::protobuf::uint32 ChargeLottery::limit() const {
  // @@protoc_insertion_point(field_get:ConfigTokenUpgrade.ChargeLottery.limit)
  return limit_;
}
inline void ChargeLottery::set_limit(::google::protobuf::uint32 value) {
  set_has_limit();
  limit_ = value;
  // @@protoc_insertion_point(field_set:ConfigTokenUpgrade.ChargeLottery.limit)
}

// repeated .ConfigTokenUpgrade.TurnTable turntable = 3;
inline int ChargeLottery::turntable_size() const {
  return turntable_.size();
}
inline void ChargeLottery::clear_turntable() {
  turntable_.Clear();
}
inline const ::ConfigTokenUpgrade::TurnTable& ChargeLottery::turntable(int index) const {
  // @@protoc_insertion_point(field_get:ConfigTokenUpgrade.ChargeLottery.turntable)
  return turntable_.Get(index);
}
inline ::ConfigTokenUpgrade::TurnTable* ChargeLottery::mutable_turntable(int index) {
  // @@protoc_insertion_point(field_mutable:ConfigTokenUpgrade.ChargeLottery.turntable)
  return turntable_.Mutable(index);
}
inline ::ConfigTokenUpgrade::TurnTable* ChargeLottery::add_turntable() {
  // @@protoc_insertion_point(field_add:ConfigTokenUpgrade.ChargeLottery.turntable)
  return turntable_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ConfigTokenUpgrade::TurnTable >&
ChargeLottery::turntable() const {
  // @@protoc_insertion_point(field_list:ConfigTokenUpgrade.ChargeLottery.turntable)
  return turntable_;
}
inline ::google::protobuf::RepeatedPtrField< ::ConfigTokenUpgrade::TurnTable >*
ChargeLottery::mutable_turntable() {
  // @@protoc_insertion_point(field_mutable_list:ConfigTokenUpgrade.ChargeLottery.turntable)
  return &turntable_;
}

// -------------------------------------------------------------------

// TokenUpgrade

// repeated .ConfigTokenUpgrade.ChargeReceive charge_receive = 1;
inline int TokenUpgrade::charge_receive_size() const {
  return charge_receive_.size();
}
inline void TokenUpgrade::clear_charge_receive() {
  charge_receive_.Clear();
}
inline const ::ConfigTokenUpgrade::ChargeReceive& TokenUpgrade::charge_receive(int index) const {
  // @@protoc_insertion_point(field_get:ConfigTokenUpgrade.TokenUpgrade.charge_receive)
  return charge_receive_.Get(index);
}
inline ::ConfigTokenUpgrade::ChargeReceive* TokenUpgrade::mutable_charge_receive(int index) {
  // @@protoc_insertion_point(field_mutable:ConfigTokenUpgrade.TokenUpgrade.charge_receive)
  return charge_receive_.Mutable(index);
}
inline ::ConfigTokenUpgrade::ChargeReceive* TokenUpgrade::add_charge_receive() {
  // @@protoc_insertion_point(field_add:ConfigTokenUpgrade.TokenUpgrade.charge_receive)
  return charge_receive_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ConfigTokenUpgrade::ChargeReceive >&
TokenUpgrade::charge_receive() const {
  // @@protoc_insertion_point(field_list:ConfigTokenUpgrade.TokenUpgrade.charge_receive)
  return charge_receive_;
}
inline ::google::protobuf::RepeatedPtrField< ::ConfigTokenUpgrade::ChargeReceive >*
TokenUpgrade::mutable_charge_receive() {
  // @@protoc_insertion_point(field_mutable_list:ConfigTokenUpgrade.TokenUpgrade.charge_receive)
  return &charge_receive_;
}

// required .ConfigTokenUpgrade.ChargeLottery charge_lottery = 2;
inline bool TokenUpgrade::has_charge_lottery() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TokenUpgrade::set_has_charge_lottery() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TokenUpgrade::clear_has_charge_lottery() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TokenUpgrade::clear_charge_lottery() {
  if (charge_lottery_ != NULL) charge_lottery_->::ConfigTokenUpgrade::ChargeLottery::Clear();
  clear_has_charge_lottery();
}
inline const ::ConfigTokenUpgrade::ChargeLottery& TokenUpgrade::charge_lottery() const {
  // @@protoc_insertion_point(field_get:ConfigTokenUpgrade.TokenUpgrade.charge_lottery)
  return charge_lottery_ != NULL ? *charge_lottery_ : *default_instance_->charge_lottery_;
}
inline ::ConfigTokenUpgrade::ChargeLottery* TokenUpgrade::mutable_charge_lottery() {
  set_has_charge_lottery();
  if (charge_lottery_ == NULL) charge_lottery_ = new ::ConfigTokenUpgrade::ChargeLottery;
  // @@protoc_insertion_point(field_mutable:ConfigTokenUpgrade.TokenUpgrade.charge_lottery)
  return charge_lottery_;
}
inline ::ConfigTokenUpgrade::ChargeLottery* TokenUpgrade::release_charge_lottery() {
  clear_has_charge_lottery();
  ::ConfigTokenUpgrade::ChargeLottery* temp = charge_lottery_;
  charge_lottery_ = NULL;
  return temp;
}
inline void TokenUpgrade::set_allocated_charge_lottery(::ConfigTokenUpgrade::ChargeLottery* charge_lottery) {
  delete charge_lottery_;
  charge_lottery_ = charge_lottery;
  if (charge_lottery) {
    set_has_charge_lottery();
  } else {
    clear_has_charge_lottery();
  }
  // @@protoc_insertion_point(field_set_allocated:ConfigTokenUpgrade.TokenUpgrade.charge_lottery)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ConfigTokenUpgrade

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ConfigTokenUpgrade_2eproto__INCLUDED
