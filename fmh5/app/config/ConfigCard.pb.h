// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ConfigCard.proto

#ifndef PROTOBUF_ConfigCard_2eproto__INCLUDED
#define PROTOBUF_ConfigCard_2eproto__INCLUDED

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
#include "CommonGiftConfig.pb.h"
// @@protoc_insertion_point(includes)

namespace ConfigCard {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ConfigCard_2eproto();
void protobuf_AssignDesc_ConfigCard_2eproto();
void protobuf_ShutdownFile_ConfigCard_2eproto();

class MonthCardCPP;
class LifeCardCPP;
class CardCfg;

// ===================================================================

class MonthCardCPP : public ::google::protobuf::Message {
 public:
  MonthCardCPP();
  virtual ~MonthCardCPP();

  MonthCardCPP(const MonthCardCPP& from);

  inline MonthCardCPP& operator=(const MonthCardCPP& from) {
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
  static const MonthCardCPP& default_instance();

  void Swap(MonthCardCPP* other);

  // implements Message ----------------------------------------------

  MonthCardCPP* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MonthCardCPP& from);
  void MergeFrom(const MonthCardCPP& from);
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

  // required uint32 effective_day = 2;
  inline bool has_effective_day() const;
  inline void clear_effective_day();
  static const int kEffectiveDayFieldNumber = 2;
  inline ::google::protobuf::uint32 effective_day() const;
  inline void set_effective_day(::google::protobuf::uint32 value);

  // required .CommonGiftConfig.CommonModifyItem first_reward = 3;
  inline bool has_first_reward() const;
  inline void clear_first_reward();
  static const int kFirstRewardFieldNumber = 3;
  inline const ::CommonGiftConfig::CommonModifyItem& first_reward() const;
  inline ::CommonGiftConfig::CommonModifyItem* mutable_first_reward();
  inline ::CommonGiftConfig::CommonModifyItem* release_first_reward();
  inline void set_allocated_first_reward(::CommonGiftConfig::CommonModifyItem* first_reward);

  // required .CommonGiftConfig.CommonModifyItem reward = 4;
  inline bool has_reward() const;
  inline void clear_reward();
  static const int kRewardFieldNumber = 4;
  inline const ::CommonGiftConfig::CommonModifyItem& reward() const;
  inline ::CommonGiftConfig::CommonModifyItem* mutable_reward();
  inline ::CommonGiftConfig::CommonModifyItem* release_reward();
  inline void set_allocated_reward(::CommonGiftConfig::CommonModifyItem* reward);

  // @@protoc_insertion_point(class_scope:ConfigCard.MonthCardCPP)
 private:
  inline void set_has_cost();
  inline void clear_has_cost();
  inline void set_has_effective_day();
  inline void clear_has_effective_day();
  inline void set_has_first_reward();
  inline void clear_has_first_reward();
  inline void set_has_reward();
  inline void clear_has_reward();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 cost_;
  ::google::protobuf::uint32 effective_day_;
  ::CommonGiftConfig::CommonModifyItem* first_reward_;
  ::CommonGiftConfig::CommonModifyItem* reward_;
  friend void  protobuf_AddDesc_ConfigCard_2eproto();
  friend void protobuf_AssignDesc_ConfigCard_2eproto();
  friend void protobuf_ShutdownFile_ConfigCard_2eproto();

  void InitAsDefaultInstance();
  static MonthCardCPP* default_instance_;
};
// -------------------------------------------------------------------

class LifeCardCPP : public ::google::protobuf::Message {
 public:
  LifeCardCPP();
  virtual ~LifeCardCPP();

  LifeCardCPP(const LifeCardCPP& from);

  inline LifeCardCPP& operator=(const LifeCardCPP& from) {
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
  static const LifeCardCPP& default_instance();

  void Swap(LifeCardCPP* other);

  // implements Message ----------------------------------------------

  LifeCardCPP* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const LifeCardCPP& from);
  void MergeFrom(const LifeCardCPP& from);
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

  // required .CommonGiftConfig.CommonModifyItem first_reward = 2;
  inline bool has_first_reward() const;
  inline void clear_first_reward();
  static const int kFirstRewardFieldNumber = 2;
  inline const ::CommonGiftConfig::CommonModifyItem& first_reward() const;
  inline ::CommonGiftConfig::CommonModifyItem* mutable_first_reward();
  inline ::CommonGiftConfig::CommonModifyItem* release_first_reward();
  inline void set_allocated_first_reward(::CommonGiftConfig::CommonModifyItem* first_reward);

  // required .CommonGiftConfig.CommonModifyItem reward = 3;
  inline bool has_reward() const;
  inline void clear_reward();
  static const int kRewardFieldNumber = 3;
  inline const ::CommonGiftConfig::CommonModifyItem& reward() const;
  inline ::CommonGiftConfig::CommonModifyItem* mutable_reward();
  inline ::CommonGiftConfig::CommonModifyItem* release_reward();
  inline void set_allocated_reward(::CommonGiftConfig::CommonModifyItem* reward);

  // @@protoc_insertion_point(class_scope:ConfigCard.LifeCardCPP)
 private:
  inline void set_has_cost();
  inline void clear_has_cost();
  inline void set_has_first_reward();
  inline void clear_has_first_reward();
  inline void set_has_reward();
  inline void clear_has_reward();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::CommonGiftConfig::CommonModifyItem* first_reward_;
  ::CommonGiftConfig::CommonModifyItem* reward_;
  ::google::protobuf::uint32 cost_;
  friend void  protobuf_AddDesc_ConfigCard_2eproto();
  friend void protobuf_AssignDesc_ConfigCard_2eproto();
  friend void protobuf_ShutdownFile_ConfigCard_2eproto();

  void InitAsDefaultInstance();
  static LifeCardCPP* default_instance_;
};
// -------------------------------------------------------------------

class CardCfg : public ::google::protobuf::Message {
 public:
  CardCfg();
  virtual ~CardCfg();

  CardCfg(const CardCfg& from);

  inline CardCfg& operator=(const CardCfg& from) {
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
  static const CardCfg& default_instance();

  void Swap(CardCfg* other);

  // implements Message ----------------------------------------------

  CardCfg* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CardCfg& from);
  void MergeFrom(const CardCfg& from);
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

  // required .ConfigCard.MonthCardCPP monthcard = 1;
  inline bool has_monthcard() const;
  inline void clear_monthcard();
  static const int kMonthcardFieldNumber = 1;
  inline const ::ConfigCard::MonthCardCPP& monthcard() const;
  inline ::ConfigCard::MonthCardCPP* mutable_monthcard();
  inline ::ConfigCard::MonthCardCPP* release_monthcard();
  inline void set_allocated_monthcard(::ConfigCard::MonthCardCPP* monthcard);

  // required .ConfigCard.LifeCardCPP lifecard = 2;
  inline bool has_lifecard() const;
  inline void clear_lifecard();
  static const int kLifecardFieldNumber = 2;
  inline const ::ConfigCard::LifeCardCPP& lifecard() const;
  inline ::ConfigCard::LifeCardCPP* mutable_lifecard();
  inline ::ConfigCard::LifeCardCPP* release_lifecard();
  inline void set_allocated_lifecard(::ConfigCard::LifeCardCPP* lifecard);

  // @@protoc_insertion_point(class_scope:ConfigCard.CardCfg)
 private:
  inline void set_has_monthcard();
  inline void clear_has_monthcard();
  inline void set_has_lifecard();
  inline void clear_has_lifecard();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::ConfigCard::MonthCardCPP* monthcard_;
  ::ConfigCard::LifeCardCPP* lifecard_;
  friend void  protobuf_AddDesc_ConfigCard_2eproto();
  friend void protobuf_AssignDesc_ConfigCard_2eproto();
  friend void protobuf_ShutdownFile_ConfigCard_2eproto();

  void InitAsDefaultInstance();
  static CardCfg* default_instance_;
};
// ===================================================================


// ===================================================================

// MonthCardCPP

// required uint32 cost = 1;
inline bool MonthCardCPP::has_cost() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MonthCardCPP::set_has_cost() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MonthCardCPP::clear_has_cost() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MonthCardCPP::clear_cost() {
  cost_ = 0u;
  clear_has_cost();
}
inline ::google::protobuf::uint32 MonthCardCPP::cost() const {
  // @@protoc_insertion_point(field_get:ConfigCard.MonthCardCPP.cost)
  return cost_;
}
inline void MonthCardCPP::set_cost(::google::protobuf::uint32 value) {
  set_has_cost();
  cost_ = value;
  // @@protoc_insertion_point(field_set:ConfigCard.MonthCardCPP.cost)
}

// required uint32 effective_day = 2;
inline bool MonthCardCPP::has_effective_day() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MonthCardCPP::set_has_effective_day() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MonthCardCPP::clear_has_effective_day() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MonthCardCPP::clear_effective_day() {
  effective_day_ = 0u;
  clear_has_effective_day();
}
inline ::google::protobuf::uint32 MonthCardCPP::effective_day() const {
  // @@protoc_insertion_point(field_get:ConfigCard.MonthCardCPP.effective_day)
  return effective_day_;
}
inline void MonthCardCPP::set_effective_day(::google::protobuf::uint32 value) {
  set_has_effective_day();
  effective_day_ = value;
  // @@protoc_insertion_point(field_set:ConfigCard.MonthCardCPP.effective_day)
}

// required .CommonGiftConfig.CommonModifyItem first_reward = 3;
inline bool MonthCardCPP::has_first_reward() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void MonthCardCPP::set_has_first_reward() {
  _has_bits_[0] |= 0x00000004u;
}
inline void MonthCardCPP::clear_has_first_reward() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void MonthCardCPP::clear_first_reward() {
  if (first_reward_ != NULL) first_reward_->::CommonGiftConfig::CommonModifyItem::Clear();
  clear_has_first_reward();
}
inline const ::CommonGiftConfig::CommonModifyItem& MonthCardCPP::first_reward() const {
  // @@protoc_insertion_point(field_get:ConfigCard.MonthCardCPP.first_reward)
  return first_reward_ != NULL ? *first_reward_ : *default_instance_->first_reward_;
}
inline ::CommonGiftConfig::CommonModifyItem* MonthCardCPP::mutable_first_reward() {
  set_has_first_reward();
  if (first_reward_ == NULL) first_reward_ = new ::CommonGiftConfig::CommonModifyItem;
  // @@protoc_insertion_point(field_mutable:ConfigCard.MonthCardCPP.first_reward)
  return first_reward_;
}
inline ::CommonGiftConfig::CommonModifyItem* MonthCardCPP::release_first_reward() {
  clear_has_first_reward();
  ::CommonGiftConfig::CommonModifyItem* temp = first_reward_;
  first_reward_ = NULL;
  return temp;
}
inline void MonthCardCPP::set_allocated_first_reward(::CommonGiftConfig::CommonModifyItem* first_reward) {
  delete first_reward_;
  first_reward_ = first_reward;
  if (first_reward) {
    set_has_first_reward();
  } else {
    clear_has_first_reward();
  }
  // @@protoc_insertion_point(field_set_allocated:ConfigCard.MonthCardCPP.first_reward)
}

// required .CommonGiftConfig.CommonModifyItem reward = 4;
inline bool MonthCardCPP::has_reward() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void MonthCardCPP::set_has_reward() {
  _has_bits_[0] |= 0x00000008u;
}
inline void MonthCardCPP::clear_has_reward() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void MonthCardCPP::clear_reward() {
  if (reward_ != NULL) reward_->::CommonGiftConfig::CommonModifyItem::Clear();
  clear_has_reward();
}
inline const ::CommonGiftConfig::CommonModifyItem& MonthCardCPP::reward() const {
  // @@protoc_insertion_point(field_get:ConfigCard.MonthCardCPP.reward)
  return reward_ != NULL ? *reward_ : *default_instance_->reward_;
}
inline ::CommonGiftConfig::CommonModifyItem* MonthCardCPP::mutable_reward() {
  set_has_reward();
  if (reward_ == NULL) reward_ = new ::CommonGiftConfig::CommonModifyItem;
  // @@protoc_insertion_point(field_mutable:ConfigCard.MonthCardCPP.reward)
  return reward_;
}
inline ::CommonGiftConfig::CommonModifyItem* MonthCardCPP::release_reward() {
  clear_has_reward();
  ::CommonGiftConfig::CommonModifyItem* temp = reward_;
  reward_ = NULL;
  return temp;
}
inline void MonthCardCPP::set_allocated_reward(::CommonGiftConfig::CommonModifyItem* reward) {
  delete reward_;
  reward_ = reward;
  if (reward) {
    set_has_reward();
  } else {
    clear_has_reward();
  }
  // @@protoc_insertion_point(field_set_allocated:ConfigCard.MonthCardCPP.reward)
}

// -------------------------------------------------------------------

// LifeCardCPP

// required uint32 cost = 1;
inline bool LifeCardCPP::has_cost() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void LifeCardCPP::set_has_cost() {
  _has_bits_[0] |= 0x00000001u;
}
inline void LifeCardCPP::clear_has_cost() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void LifeCardCPP::clear_cost() {
  cost_ = 0u;
  clear_has_cost();
}
inline ::google::protobuf::uint32 LifeCardCPP::cost() const {
  // @@protoc_insertion_point(field_get:ConfigCard.LifeCardCPP.cost)
  return cost_;
}
inline void LifeCardCPP::set_cost(::google::protobuf::uint32 value) {
  set_has_cost();
  cost_ = value;
  // @@protoc_insertion_point(field_set:ConfigCard.LifeCardCPP.cost)
}

// required .CommonGiftConfig.CommonModifyItem first_reward = 2;
inline bool LifeCardCPP::has_first_reward() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void LifeCardCPP::set_has_first_reward() {
  _has_bits_[0] |= 0x00000002u;
}
inline void LifeCardCPP::clear_has_first_reward() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void LifeCardCPP::clear_first_reward() {
  if (first_reward_ != NULL) first_reward_->::CommonGiftConfig::CommonModifyItem::Clear();
  clear_has_first_reward();
}
inline const ::CommonGiftConfig::CommonModifyItem& LifeCardCPP::first_reward() const {
  // @@protoc_insertion_point(field_get:ConfigCard.LifeCardCPP.first_reward)
  return first_reward_ != NULL ? *first_reward_ : *default_instance_->first_reward_;
}
inline ::CommonGiftConfig::CommonModifyItem* LifeCardCPP::mutable_first_reward() {
  set_has_first_reward();
  if (first_reward_ == NULL) first_reward_ = new ::CommonGiftConfig::CommonModifyItem;
  // @@protoc_insertion_point(field_mutable:ConfigCard.LifeCardCPP.first_reward)
  return first_reward_;
}
inline ::CommonGiftConfig::CommonModifyItem* LifeCardCPP::release_first_reward() {
  clear_has_first_reward();
  ::CommonGiftConfig::CommonModifyItem* temp = first_reward_;
  first_reward_ = NULL;
  return temp;
}
inline void LifeCardCPP::set_allocated_first_reward(::CommonGiftConfig::CommonModifyItem* first_reward) {
  delete first_reward_;
  first_reward_ = first_reward;
  if (first_reward) {
    set_has_first_reward();
  } else {
    clear_has_first_reward();
  }
  // @@protoc_insertion_point(field_set_allocated:ConfigCard.LifeCardCPP.first_reward)
}

// required .CommonGiftConfig.CommonModifyItem reward = 3;
inline bool LifeCardCPP::has_reward() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void LifeCardCPP::set_has_reward() {
  _has_bits_[0] |= 0x00000004u;
}
inline void LifeCardCPP::clear_has_reward() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void LifeCardCPP::clear_reward() {
  if (reward_ != NULL) reward_->::CommonGiftConfig::CommonModifyItem::Clear();
  clear_has_reward();
}
inline const ::CommonGiftConfig::CommonModifyItem& LifeCardCPP::reward() const {
  // @@protoc_insertion_point(field_get:ConfigCard.LifeCardCPP.reward)
  return reward_ != NULL ? *reward_ : *default_instance_->reward_;
}
inline ::CommonGiftConfig::CommonModifyItem* LifeCardCPP::mutable_reward() {
  set_has_reward();
  if (reward_ == NULL) reward_ = new ::CommonGiftConfig::CommonModifyItem;
  // @@protoc_insertion_point(field_mutable:ConfigCard.LifeCardCPP.reward)
  return reward_;
}
inline ::CommonGiftConfig::CommonModifyItem* LifeCardCPP::release_reward() {
  clear_has_reward();
  ::CommonGiftConfig::CommonModifyItem* temp = reward_;
  reward_ = NULL;
  return temp;
}
inline void LifeCardCPP::set_allocated_reward(::CommonGiftConfig::CommonModifyItem* reward) {
  delete reward_;
  reward_ = reward;
  if (reward) {
    set_has_reward();
  } else {
    clear_has_reward();
  }
  // @@protoc_insertion_point(field_set_allocated:ConfigCard.LifeCardCPP.reward)
}

// -------------------------------------------------------------------

// CardCfg

// required .ConfigCard.MonthCardCPP monthcard = 1;
inline bool CardCfg::has_monthcard() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CardCfg::set_has_monthcard() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CardCfg::clear_has_monthcard() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void CardCfg::clear_monthcard() {
  if (monthcard_ != NULL) monthcard_->::ConfigCard::MonthCardCPP::Clear();
  clear_has_monthcard();
}
inline const ::ConfigCard::MonthCardCPP& CardCfg::monthcard() const {
  // @@protoc_insertion_point(field_get:ConfigCard.CardCfg.monthcard)
  return monthcard_ != NULL ? *monthcard_ : *default_instance_->monthcard_;
}
inline ::ConfigCard::MonthCardCPP* CardCfg::mutable_monthcard() {
  set_has_monthcard();
  if (monthcard_ == NULL) monthcard_ = new ::ConfigCard::MonthCardCPP;
  // @@protoc_insertion_point(field_mutable:ConfigCard.CardCfg.monthcard)
  return monthcard_;
}
inline ::ConfigCard::MonthCardCPP* CardCfg::release_monthcard() {
  clear_has_monthcard();
  ::ConfigCard::MonthCardCPP* temp = monthcard_;
  monthcard_ = NULL;
  return temp;
}
inline void CardCfg::set_allocated_monthcard(::ConfigCard::MonthCardCPP* monthcard) {
  delete monthcard_;
  monthcard_ = monthcard;
  if (monthcard) {
    set_has_monthcard();
  } else {
    clear_has_monthcard();
  }
  // @@protoc_insertion_point(field_set_allocated:ConfigCard.CardCfg.monthcard)
}

// required .ConfigCard.LifeCardCPP lifecard = 2;
inline bool CardCfg::has_lifecard() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void CardCfg::set_has_lifecard() {
  _has_bits_[0] |= 0x00000002u;
}
inline void CardCfg::clear_has_lifecard() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void CardCfg::clear_lifecard() {
  if (lifecard_ != NULL) lifecard_->::ConfigCard::LifeCardCPP::Clear();
  clear_has_lifecard();
}
inline const ::ConfigCard::LifeCardCPP& CardCfg::lifecard() const {
  // @@protoc_insertion_point(field_get:ConfigCard.CardCfg.lifecard)
  return lifecard_ != NULL ? *lifecard_ : *default_instance_->lifecard_;
}
inline ::ConfigCard::LifeCardCPP* CardCfg::mutable_lifecard() {
  set_has_lifecard();
  if (lifecard_ == NULL) lifecard_ = new ::ConfigCard::LifeCardCPP;
  // @@protoc_insertion_point(field_mutable:ConfigCard.CardCfg.lifecard)
  return lifecard_;
}
inline ::ConfigCard::LifeCardCPP* CardCfg::release_lifecard() {
  clear_has_lifecard();
  ::ConfigCard::LifeCardCPP* temp = lifecard_;
  lifecard_ = NULL;
  return temp;
}
inline void CardCfg::set_allocated_lifecard(::ConfigCard::LifeCardCPP* lifecard) {
  delete lifecard_;
  lifecard_ = lifecard;
  if (lifecard) {
    set_has_lifecard();
  } else {
    clear_has_lifecard();
  }
  // @@protoc_insertion_point(field_set_allocated:ConfigCard.CardCfg.lifecard)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ConfigCard

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ConfigCard_2eproto__INCLUDED
