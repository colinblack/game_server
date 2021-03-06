// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ActivityConfig.proto

#ifndef PROTOBUF_ActivityConfig_2eproto__INCLUDED
#define PROTOBUF_ActivityConfig_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
#include "CommonGiftConfig.pb.h"
// @@protoc_insertion_point(includes)

namespace ActivityConfig {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ActivityConfig_2eproto();
void protobuf_AssignDesc_ActivityConfig_2eproto();
void protobuf_ShutdownFile_ActivityConfig_2eproto();

class InviteFriendReward;
class AccumulateReward;
class LuckyDrawItem;
class LuckyDrawReward;
class Activity;

// ===================================================================

class InviteFriendReward : public ::google::protobuf::Message {
 public:
  InviteFriendReward();
  virtual ~InviteFriendReward();
  
  InviteFriendReward(const InviteFriendReward& from);
  
  inline InviteFriendReward& operator=(const InviteFriendReward& from) {
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
  static const InviteFriendReward& default_instance();
  
  void Swap(InviteFriendReward* other);
  
  // implements Message ----------------------------------------------
  
  InviteFriendReward* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const InviteFriendReward& from);
  void MergeFrom(const InviteFriendReward& from);
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
  
  // required uint32 seq = 1;
  inline bool has_seq() const;
  inline void clear_seq();
  static const int kSeqFieldNumber = 1;
  inline ::google::protobuf::uint32 seq() const;
  inline void set_seq(::google::protobuf::uint32 value);
  
  // required .CommonGiftConfig.CommonModifyItem rewards = 2;
  inline bool has_rewards() const;
  inline void clear_rewards();
  static const int kRewardsFieldNumber = 2;
  inline const ::CommonGiftConfig::CommonModifyItem& rewards() const;
  inline ::CommonGiftConfig::CommonModifyItem* mutable_rewards();
  inline ::CommonGiftConfig::CommonModifyItem* release_rewards();
  
  // @@protoc_insertion_point(class_scope:ActivityConfig.InviteFriendReward)
 private:
  inline void set_has_seq();
  inline void clear_has_seq();
  inline void set_has_rewards();
  inline void clear_has_rewards();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::CommonGiftConfig::CommonModifyItem* rewards_;
  ::google::protobuf::uint32 seq_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_ActivityConfig_2eproto();
  friend void protobuf_AssignDesc_ActivityConfig_2eproto();
  friend void protobuf_ShutdownFile_ActivityConfig_2eproto();
  
  void InitAsDefaultInstance();
  static InviteFriendReward* default_instance_;
};
// -------------------------------------------------------------------

class AccumulateReward : public ::google::protobuf::Message {
 public:
  AccumulateReward();
  virtual ~AccumulateReward();
  
  AccumulateReward(const AccumulateReward& from);
  
  inline AccumulateReward& operator=(const AccumulateReward& from) {
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
  static const AccumulateReward& default_instance();
  
  void Swap(AccumulateReward* other);
  
  // implements Message ----------------------------------------------
  
  AccumulateReward* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AccumulateReward& from);
  void MergeFrom(const AccumulateReward& from);
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
  
  // required uint32 num = 1;
  inline bool has_num() const;
  inline void clear_num();
  static const int kNumFieldNumber = 1;
  inline ::google::protobuf::uint32 num() const;
  inline void set_num(::google::protobuf::uint32 value);
  
  // required .CommonGiftConfig.CommonModifyItem rewards = 2;
  inline bool has_rewards() const;
  inline void clear_rewards();
  static const int kRewardsFieldNumber = 2;
  inline const ::CommonGiftConfig::CommonModifyItem& rewards() const;
  inline ::CommonGiftConfig::CommonModifyItem* mutable_rewards();
  inline ::CommonGiftConfig::CommonModifyItem* release_rewards();
  
  // @@protoc_insertion_point(class_scope:ActivityConfig.AccumulateReward)
 private:
  inline void set_has_num();
  inline void clear_has_num();
  inline void set_has_rewards();
  inline void clear_has_rewards();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::CommonGiftConfig::CommonModifyItem* rewards_;
  ::google::protobuf::uint32 num_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_ActivityConfig_2eproto();
  friend void protobuf_AssignDesc_ActivityConfig_2eproto();
  friend void protobuf_ShutdownFile_ActivityConfig_2eproto();
  
  void InitAsDefaultInstance();
  static AccumulateReward* default_instance_;
};
// -------------------------------------------------------------------

class LuckyDrawItem : public ::google::protobuf::Message {
 public:
  LuckyDrawItem();
  virtual ~LuckyDrawItem();
  
  LuckyDrawItem(const LuckyDrawItem& from);
  
  inline LuckyDrawItem& operator=(const LuckyDrawItem& from) {
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
  static const LuckyDrawItem& default_instance();
  
  void Swap(LuckyDrawItem* other);
  
  // implements Message ----------------------------------------------
  
  LuckyDrawItem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const LuckyDrawItem& from);
  void MergeFrom(const LuckyDrawItem& from);
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
  
  // required .CommonGiftConfig.CommonModifyItem rewards = 1;
  inline bool has_rewards() const;
  inline void clear_rewards();
  static const int kRewardsFieldNumber = 1;
  inline const ::CommonGiftConfig::CommonModifyItem& rewards() const;
  inline ::CommonGiftConfig::CommonModifyItem* mutable_rewards();
  inline ::CommonGiftConfig::CommonModifyItem* release_rewards();
  
  // required uint32 weight = 2;
  inline bool has_weight() const;
  inline void clear_weight();
  static const int kWeightFieldNumber = 2;
  inline ::google::protobuf::uint32 weight() const;
  inline void set_weight(::google::protobuf::uint32 value);
  
  // required uint32 freeWeight = 3;
  inline bool has_freeweight() const;
  inline void clear_freeweight();
  static const int kFreeWeightFieldNumber = 3;
  inline ::google::protobuf::uint32 freeweight() const;
  inline void set_freeweight(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:ActivityConfig.LuckyDrawItem)
 private:
  inline void set_has_rewards();
  inline void clear_has_rewards();
  inline void set_has_weight();
  inline void clear_has_weight();
  inline void set_has_freeweight();
  inline void clear_has_freeweight();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::CommonGiftConfig::CommonModifyItem* rewards_;
  ::google::protobuf::uint32 weight_;
  ::google::protobuf::uint32 freeweight_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_ActivityConfig_2eproto();
  friend void protobuf_AssignDesc_ActivityConfig_2eproto();
  friend void protobuf_ShutdownFile_ActivityConfig_2eproto();
  
  void InitAsDefaultInstance();
  static LuckyDrawItem* default_instance_;
};
// -------------------------------------------------------------------

class LuckyDrawReward : public ::google::protobuf::Message {
 public:
  LuckyDrawReward();
  virtual ~LuckyDrawReward();
  
  LuckyDrawReward(const LuckyDrawReward& from);
  
  inline LuckyDrawReward& operator=(const LuckyDrawReward& from) {
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
  static const LuckyDrawReward& default_instance();
  
  void Swap(LuckyDrawReward* other);
  
  // implements Message ----------------------------------------------
  
  LuckyDrawReward* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const LuckyDrawReward& from);
  void MergeFrom(const LuckyDrawReward& from);
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
  
  // required uint32 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::uint32 id() const;
  inline void set_id(::google::protobuf::uint32 value);
  
  // required uint32 range = 2;
  inline bool has_range() const;
  inline void clear_range();
  static const int kRangeFieldNumber = 2;
  inline ::google::protobuf::uint32 range() const;
  inline void set_range(::google::protobuf::uint32 value);
  
  // repeated .ActivityConfig.LuckyDrawItem items = 3;
  inline int items_size() const;
  inline void clear_items();
  static const int kItemsFieldNumber = 3;
  inline const ::ActivityConfig::LuckyDrawItem& items(int index) const;
  inline ::ActivityConfig::LuckyDrawItem* mutable_items(int index);
  inline ::ActivityConfig::LuckyDrawItem* add_items();
  inline const ::google::protobuf::RepeatedPtrField< ::ActivityConfig::LuckyDrawItem >&
      items() const;
  inline ::google::protobuf::RepeatedPtrField< ::ActivityConfig::LuckyDrawItem >*
      mutable_items();
  
  // @@protoc_insertion_point(class_scope:ActivityConfig.LuckyDrawReward)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_range();
  inline void clear_has_range();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 range_;
  ::google::protobuf::RepeatedPtrField< ::ActivityConfig::LuckyDrawItem > items_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_ActivityConfig_2eproto();
  friend void protobuf_AssignDesc_ActivityConfig_2eproto();
  friend void protobuf_ShutdownFile_ActivityConfig_2eproto();
  
  void InitAsDefaultInstance();
  static LuckyDrawReward* default_instance_;
};
// -------------------------------------------------------------------

class Activity : public ::google::protobuf::Message {
 public:
  Activity();
  virtual ~Activity();
  
  Activity(const Activity& from);
  
  inline Activity& operator=(const Activity& from) {
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
  static const Activity& default_instance();
  
  void Swap(Activity* other);
  
  // implements Message ----------------------------------------------
  
  Activity* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Activity& from);
  void MergeFrom(const Activity& from);
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
  
  // repeated .ActivityConfig.InviteFriendReward inviteRewards = 1;
  inline int inviterewards_size() const;
  inline void clear_inviterewards();
  static const int kInviteRewardsFieldNumber = 1;
  inline const ::ActivityConfig::InviteFriendReward& inviterewards(int index) const;
  inline ::ActivityConfig::InviteFriendReward* mutable_inviterewards(int index);
  inline ::ActivityConfig::InviteFriendReward* add_inviterewards();
  inline const ::google::protobuf::RepeatedPtrField< ::ActivityConfig::InviteFriendReward >&
      inviterewards() const;
  inline ::google::protobuf::RepeatedPtrField< ::ActivityConfig::InviteFriendReward >*
      mutable_inviterewards();
  
  // repeated .ActivityConfig.AccumulateReward accRewards = 2;
  inline int accrewards_size() const;
  inline void clear_accrewards();
  static const int kAccRewardsFieldNumber = 2;
  inline const ::ActivityConfig::AccumulateReward& accrewards(int index) const;
  inline ::ActivityConfig::AccumulateReward* mutable_accrewards(int index);
  inline ::ActivityConfig::AccumulateReward* add_accrewards();
  inline const ::google::protobuf::RepeatedPtrField< ::ActivityConfig::AccumulateReward >&
      accrewards() const;
  inline ::google::protobuf::RepeatedPtrField< ::ActivityConfig::AccumulateReward >*
      mutable_accrewards();
  
  // required uint32 luckyRewardCost = 3;
  inline bool has_luckyrewardcost() const;
  inline void clear_luckyrewardcost();
  static const int kLuckyRewardCostFieldNumber = 3;
  inline ::google::protobuf::uint32 luckyrewardcost() const;
  inline void set_luckyrewardcost(::google::protobuf::uint32 value);
  
  // repeated .ActivityConfig.LuckyDrawReward luckyReward = 4;
  inline int luckyreward_size() const;
  inline void clear_luckyreward();
  static const int kLuckyRewardFieldNumber = 4;
  inline const ::ActivityConfig::LuckyDrawReward& luckyreward(int index) const;
  inline ::ActivityConfig::LuckyDrawReward* mutable_luckyreward(int index);
  inline ::ActivityConfig::LuckyDrawReward* add_luckyreward();
  inline const ::google::protobuf::RepeatedPtrField< ::ActivityConfig::LuckyDrawReward >&
      luckyreward() const;
  inline ::google::protobuf::RepeatedPtrField< ::ActivityConfig::LuckyDrawReward >*
      mutable_luckyreward();
  
  // @@protoc_insertion_point(class_scope:ActivityConfig.Activity)
 private:
  inline void set_has_luckyrewardcost();
  inline void clear_has_luckyrewardcost();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::ActivityConfig::InviteFriendReward > inviterewards_;
  ::google::protobuf::RepeatedPtrField< ::ActivityConfig::AccumulateReward > accrewards_;
  ::google::protobuf::RepeatedPtrField< ::ActivityConfig::LuckyDrawReward > luckyreward_;
  ::google::protobuf::uint32 luckyrewardcost_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];
  
  friend void  protobuf_AddDesc_ActivityConfig_2eproto();
  friend void protobuf_AssignDesc_ActivityConfig_2eproto();
  friend void protobuf_ShutdownFile_ActivityConfig_2eproto();
  
  void InitAsDefaultInstance();
  static Activity* default_instance_;
};
// ===================================================================


// ===================================================================

// InviteFriendReward

// required uint32 seq = 1;
inline bool InviteFriendReward::has_seq() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void InviteFriendReward::set_has_seq() {
  _has_bits_[0] |= 0x00000001u;
}
inline void InviteFriendReward::clear_has_seq() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void InviteFriendReward::clear_seq() {
  seq_ = 0u;
  clear_has_seq();
}
inline ::google::protobuf::uint32 InviteFriendReward::seq() const {
  return seq_;
}
inline void InviteFriendReward::set_seq(::google::protobuf::uint32 value) {
  set_has_seq();
  seq_ = value;
}

// required .CommonGiftConfig.CommonModifyItem rewards = 2;
inline bool InviteFriendReward::has_rewards() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void InviteFriendReward::set_has_rewards() {
  _has_bits_[0] |= 0x00000002u;
}
inline void InviteFriendReward::clear_has_rewards() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void InviteFriendReward::clear_rewards() {
  if (rewards_ != NULL) rewards_->::CommonGiftConfig::CommonModifyItem::Clear();
  clear_has_rewards();
}
inline const ::CommonGiftConfig::CommonModifyItem& InviteFriendReward::rewards() const {
  return rewards_ != NULL ? *rewards_ : *default_instance_->rewards_;
}
inline ::CommonGiftConfig::CommonModifyItem* InviteFriendReward::mutable_rewards() {
  set_has_rewards();
  if (rewards_ == NULL) rewards_ = new ::CommonGiftConfig::CommonModifyItem;
  return rewards_;
}
inline ::CommonGiftConfig::CommonModifyItem* InviteFriendReward::release_rewards() {
  clear_has_rewards();
  ::CommonGiftConfig::CommonModifyItem* temp = rewards_;
  rewards_ = NULL;
  return temp;
}

// -------------------------------------------------------------------

// AccumulateReward

// required uint32 num = 1;
inline bool AccumulateReward::has_num() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AccumulateReward::set_has_num() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AccumulateReward::clear_has_num() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AccumulateReward::clear_num() {
  num_ = 0u;
  clear_has_num();
}
inline ::google::protobuf::uint32 AccumulateReward::num() const {
  return num_;
}
inline void AccumulateReward::set_num(::google::protobuf::uint32 value) {
  set_has_num();
  num_ = value;
}

// required .CommonGiftConfig.CommonModifyItem rewards = 2;
inline bool AccumulateReward::has_rewards() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AccumulateReward::set_has_rewards() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AccumulateReward::clear_has_rewards() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AccumulateReward::clear_rewards() {
  if (rewards_ != NULL) rewards_->::CommonGiftConfig::CommonModifyItem::Clear();
  clear_has_rewards();
}
inline const ::CommonGiftConfig::CommonModifyItem& AccumulateReward::rewards() const {
  return rewards_ != NULL ? *rewards_ : *default_instance_->rewards_;
}
inline ::CommonGiftConfig::CommonModifyItem* AccumulateReward::mutable_rewards() {
  set_has_rewards();
  if (rewards_ == NULL) rewards_ = new ::CommonGiftConfig::CommonModifyItem;
  return rewards_;
}
inline ::CommonGiftConfig::CommonModifyItem* AccumulateReward::release_rewards() {
  clear_has_rewards();
  ::CommonGiftConfig::CommonModifyItem* temp = rewards_;
  rewards_ = NULL;
  return temp;
}

// -------------------------------------------------------------------

// LuckyDrawItem

// required .CommonGiftConfig.CommonModifyItem rewards = 1;
inline bool LuckyDrawItem::has_rewards() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void LuckyDrawItem::set_has_rewards() {
  _has_bits_[0] |= 0x00000001u;
}
inline void LuckyDrawItem::clear_has_rewards() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void LuckyDrawItem::clear_rewards() {
  if (rewards_ != NULL) rewards_->::CommonGiftConfig::CommonModifyItem::Clear();
  clear_has_rewards();
}
inline const ::CommonGiftConfig::CommonModifyItem& LuckyDrawItem::rewards() const {
  return rewards_ != NULL ? *rewards_ : *default_instance_->rewards_;
}
inline ::CommonGiftConfig::CommonModifyItem* LuckyDrawItem::mutable_rewards() {
  set_has_rewards();
  if (rewards_ == NULL) rewards_ = new ::CommonGiftConfig::CommonModifyItem;
  return rewards_;
}
inline ::CommonGiftConfig::CommonModifyItem* LuckyDrawItem::release_rewards() {
  clear_has_rewards();
  ::CommonGiftConfig::CommonModifyItem* temp = rewards_;
  rewards_ = NULL;
  return temp;
}

// required uint32 weight = 2;
inline bool LuckyDrawItem::has_weight() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void LuckyDrawItem::set_has_weight() {
  _has_bits_[0] |= 0x00000002u;
}
inline void LuckyDrawItem::clear_has_weight() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void LuckyDrawItem::clear_weight() {
  weight_ = 0u;
  clear_has_weight();
}
inline ::google::protobuf::uint32 LuckyDrawItem::weight() const {
  return weight_;
}
inline void LuckyDrawItem::set_weight(::google::protobuf::uint32 value) {
  set_has_weight();
  weight_ = value;
}

// required uint32 freeWeight = 3;
inline bool LuckyDrawItem::has_freeweight() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void LuckyDrawItem::set_has_freeweight() {
  _has_bits_[0] |= 0x00000004u;
}
inline void LuckyDrawItem::clear_has_freeweight() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void LuckyDrawItem::clear_freeweight() {
  freeweight_ = 0u;
  clear_has_freeweight();
}
inline ::google::protobuf::uint32 LuckyDrawItem::freeweight() const {
  return freeweight_;
}
inline void LuckyDrawItem::set_freeweight(::google::protobuf::uint32 value) {
  set_has_freeweight();
  freeweight_ = value;
}

// -------------------------------------------------------------------

// LuckyDrawReward

// required uint32 id = 1;
inline bool LuckyDrawReward::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void LuckyDrawReward::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void LuckyDrawReward::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void LuckyDrawReward::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 LuckyDrawReward::id() const {
  return id_;
}
inline void LuckyDrawReward::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// required uint32 range = 2;
inline bool LuckyDrawReward::has_range() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void LuckyDrawReward::set_has_range() {
  _has_bits_[0] |= 0x00000002u;
}
inline void LuckyDrawReward::clear_has_range() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void LuckyDrawReward::clear_range() {
  range_ = 0u;
  clear_has_range();
}
inline ::google::protobuf::uint32 LuckyDrawReward::range() const {
  return range_;
}
inline void LuckyDrawReward::set_range(::google::protobuf::uint32 value) {
  set_has_range();
  range_ = value;
}

// repeated .ActivityConfig.LuckyDrawItem items = 3;
inline int LuckyDrawReward::items_size() const {
  return items_.size();
}
inline void LuckyDrawReward::clear_items() {
  items_.Clear();
}
inline const ::ActivityConfig::LuckyDrawItem& LuckyDrawReward::items(int index) const {
  return items_.Get(index);
}
inline ::ActivityConfig::LuckyDrawItem* LuckyDrawReward::mutable_items(int index) {
  return items_.Mutable(index);
}
inline ::ActivityConfig::LuckyDrawItem* LuckyDrawReward::add_items() {
  return items_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ActivityConfig::LuckyDrawItem >&
LuckyDrawReward::items() const {
  return items_;
}
inline ::google::protobuf::RepeatedPtrField< ::ActivityConfig::LuckyDrawItem >*
LuckyDrawReward::mutable_items() {
  return &items_;
}

// -------------------------------------------------------------------

// Activity

// repeated .ActivityConfig.InviteFriendReward inviteRewards = 1;
inline int Activity::inviterewards_size() const {
  return inviterewards_.size();
}
inline void Activity::clear_inviterewards() {
  inviterewards_.Clear();
}
inline const ::ActivityConfig::InviteFriendReward& Activity::inviterewards(int index) const {
  return inviterewards_.Get(index);
}
inline ::ActivityConfig::InviteFriendReward* Activity::mutable_inviterewards(int index) {
  return inviterewards_.Mutable(index);
}
inline ::ActivityConfig::InviteFriendReward* Activity::add_inviterewards() {
  return inviterewards_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ActivityConfig::InviteFriendReward >&
Activity::inviterewards() const {
  return inviterewards_;
}
inline ::google::protobuf::RepeatedPtrField< ::ActivityConfig::InviteFriendReward >*
Activity::mutable_inviterewards() {
  return &inviterewards_;
}

// repeated .ActivityConfig.AccumulateReward accRewards = 2;
inline int Activity::accrewards_size() const {
  return accrewards_.size();
}
inline void Activity::clear_accrewards() {
  accrewards_.Clear();
}
inline const ::ActivityConfig::AccumulateReward& Activity::accrewards(int index) const {
  return accrewards_.Get(index);
}
inline ::ActivityConfig::AccumulateReward* Activity::mutable_accrewards(int index) {
  return accrewards_.Mutable(index);
}
inline ::ActivityConfig::AccumulateReward* Activity::add_accrewards() {
  return accrewards_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ActivityConfig::AccumulateReward >&
Activity::accrewards() const {
  return accrewards_;
}
inline ::google::protobuf::RepeatedPtrField< ::ActivityConfig::AccumulateReward >*
Activity::mutable_accrewards() {
  return &accrewards_;
}

// required uint32 luckyRewardCost = 3;
inline bool Activity::has_luckyrewardcost() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Activity::set_has_luckyrewardcost() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Activity::clear_has_luckyrewardcost() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Activity::clear_luckyrewardcost() {
  luckyrewardcost_ = 0u;
  clear_has_luckyrewardcost();
}
inline ::google::protobuf::uint32 Activity::luckyrewardcost() const {
  return luckyrewardcost_;
}
inline void Activity::set_luckyrewardcost(::google::protobuf::uint32 value) {
  set_has_luckyrewardcost();
  luckyrewardcost_ = value;
}

// repeated .ActivityConfig.LuckyDrawReward luckyReward = 4;
inline int Activity::luckyreward_size() const {
  return luckyreward_.size();
}
inline void Activity::clear_luckyreward() {
  luckyreward_.Clear();
}
inline const ::ActivityConfig::LuckyDrawReward& Activity::luckyreward(int index) const {
  return luckyreward_.Get(index);
}
inline ::ActivityConfig::LuckyDrawReward* Activity::mutable_luckyreward(int index) {
  return luckyreward_.Mutable(index);
}
inline ::ActivityConfig::LuckyDrawReward* Activity::add_luckyreward() {
  return luckyreward_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ActivityConfig::LuckyDrawReward >&
Activity::luckyreward() const {
  return luckyreward_;
}
inline ::google::protobuf::RepeatedPtrField< ::ActivityConfig::LuckyDrawReward >*
Activity::mutable_luckyreward() {
  return &luckyreward_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ActivityConfig

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ActivityConfig_2eproto__INCLUDED
