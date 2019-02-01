// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ConfigKeeper.proto

#ifndef PROTOBUF_ConfigKeeper_2eproto__INCLUDED
#define PROTOBUF_ConfigKeeper_2eproto__INCLUDED

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

namespace ConfigKeeper {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ConfigKeeper_2eproto();
void protobuf_AssignDesc_ConfigKeeper_2eproto();
void protobuf_ShutdownFile_ConfigKeeper_2eproto();

class KeeperUpgradeItem;
class KeeperTaskTarget;
class KeeperTask;
class KeeperInfo;
class KeeperCfg;

// ===================================================================

class KeeperUpgradeItem : public ::google::protobuf::Message {
 public:
  KeeperUpgradeItem();
  virtual ~KeeperUpgradeItem();
  
  KeeperUpgradeItem(const KeeperUpgradeItem& from);
  
  inline KeeperUpgradeItem& operator=(const KeeperUpgradeItem& from) {
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
  static const KeeperUpgradeItem& default_instance();
  
  void Swap(KeeperUpgradeItem* other);
  
  // implements Message ----------------------------------------------
  
  KeeperUpgradeItem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const KeeperUpgradeItem& from);
  void MergeFrom(const KeeperUpgradeItem& from);
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
  
  // required uint32 exp = 1;
  inline bool has_exp() const;
  inline void clear_exp();
  static const int kExpFieldNumber = 1;
  inline ::google::protobuf::uint32 exp() const;
  inline void set_exp(::google::protobuf::uint32 value);
  
  // required uint32 max = 2;
  inline bool has_max() const;
  inline void clear_max();
  static const int kMaxFieldNumber = 2;
  inline ::google::protobuf::uint32 max() const;
  inline void set_max(::google::protobuf::uint32 value);
  
  // required uint32 cap = 3;
  inline bool has_cap() const;
  inline void clear_cap();
  static const int kCapFieldNumber = 3;
  inline ::google::protobuf::uint32 cap() const;
  inline void set_cap(::google::protobuf::uint32 value);
  
  // required .CommonGiftConfig.CommonModifyItem item = 4;
  inline bool has_item() const;
  inline void clear_item();
  static const int kItemFieldNumber = 4;
  inline const ::CommonGiftConfig::CommonModifyItem& item() const;
  inline ::CommonGiftConfig::CommonModifyItem* mutable_item();
  inline ::CommonGiftConfig::CommonModifyItem* release_item();
  
  // @@protoc_insertion_point(class_scope:ConfigKeeper.KeeperUpgradeItem)
 private:
  inline void set_has_exp();
  inline void clear_has_exp();
  inline void set_has_max();
  inline void clear_has_max();
  inline void set_has_cap();
  inline void clear_has_cap();
  inline void set_has_item();
  inline void clear_has_item();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint32 exp_;
  ::google::protobuf::uint32 max_;
  ::CommonGiftConfig::CommonModifyItem* item_;
  ::google::protobuf::uint32 cap_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];
  
  friend void  protobuf_AddDesc_ConfigKeeper_2eproto();
  friend void protobuf_AssignDesc_ConfigKeeper_2eproto();
  friend void protobuf_ShutdownFile_ConfigKeeper_2eproto();
  
  void InitAsDefaultInstance();
  static KeeperUpgradeItem* default_instance_;
};
// -------------------------------------------------------------------

class KeeperTaskTarget : public ::google::protobuf::Message {
 public:
  KeeperTaskTarget();
  virtual ~KeeperTaskTarget();
  
  KeeperTaskTarget(const KeeperTaskTarget& from);
  
  inline KeeperTaskTarget& operator=(const KeeperTaskTarget& from) {
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
  static const KeeperTaskTarget& default_instance();
  
  void Swap(KeeperTaskTarget* other);
  
  // implements Message ----------------------------------------------
  
  KeeperTaskTarget* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const KeeperTaskTarget& from);
  void MergeFrom(const KeeperTaskTarget& from);
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
  
  // required uint32 tid = 2;
  inline bool has_tid() const;
  inline void clear_tid();
  static const int kTidFieldNumber = 2;
  inline ::google::protobuf::uint32 tid() const;
  inline void set_tid(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:ConfigKeeper.KeeperTaskTarget)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_tid();
  inline void clear_has_tid();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 tid_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_ConfigKeeper_2eproto();
  friend void protobuf_AssignDesc_ConfigKeeper_2eproto();
  friend void protobuf_ShutdownFile_ConfigKeeper_2eproto();
  
  void InitAsDefaultInstance();
  static KeeperTaskTarget* default_instance_;
};
// -------------------------------------------------------------------

class KeeperTask : public ::google::protobuf::Message {
 public:
  KeeperTask();
  virtual ~KeeperTask();
  
  KeeperTask(const KeeperTask& from);
  
  inline KeeperTask& operator=(const KeeperTask& from) {
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
  static const KeeperTask& default_instance();
  
  void Swap(KeeperTask* other);
  
  // implements Message ----------------------------------------------
  
  KeeperTask* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const KeeperTask& from);
  void MergeFrom(const KeeperTask& from);
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
  
  // required uint32 type = 1;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline ::google::protobuf::uint32 type() const;
  inline void set_type(::google::protobuf::uint32 value);
  
  // required uint32 bid = 2;
  inline bool has_bid() const;
  inline void clear_bid();
  static const int kBidFieldNumber = 2;
  inline ::google::protobuf::uint32 bid() const;
  inline void set_bid(::google::protobuf::uint32 value);
  
  // repeated .ConfigKeeper.KeeperTaskTarget target = 3;
  inline int target_size() const;
  inline void clear_target();
  static const int kTargetFieldNumber = 3;
  inline const ::ConfigKeeper::KeeperTaskTarget& target(int index) const;
  inline ::ConfigKeeper::KeeperTaskTarget* mutable_target(int index);
  inline ::ConfigKeeper::KeeperTaskTarget* add_target();
  inline const ::google::protobuf::RepeatedPtrField< ::ConfigKeeper::KeeperTaskTarget >&
      target() const;
  inline ::google::protobuf::RepeatedPtrField< ::ConfigKeeper::KeeperTaskTarget >*
      mutable_target();
  
  // @@protoc_insertion_point(class_scope:ConfigKeeper.KeeperTask)
 private:
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_bid();
  inline void clear_has_bid();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint32 type_;
  ::google::protobuf::uint32 bid_;
  ::google::protobuf::RepeatedPtrField< ::ConfigKeeper::KeeperTaskTarget > target_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_ConfigKeeper_2eproto();
  friend void protobuf_AssignDesc_ConfigKeeper_2eproto();
  friend void protobuf_ShutdownFile_ConfigKeeper_2eproto();
  
  void InitAsDefaultInstance();
  static KeeperTask* default_instance_;
};
// -------------------------------------------------------------------

class KeeperInfo : public ::google::protobuf::Message {
 public:
  KeeperInfo();
  virtual ~KeeperInfo();
  
  KeeperInfo(const KeeperInfo& from);
  
  inline KeeperInfo& operator=(const KeeperInfo& from) {
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
  static const KeeperInfo& default_instance();
  
  void Swap(KeeperInfo* other);
  
  // implements Message ----------------------------------------------
  
  KeeperInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const KeeperInfo& from);
  void MergeFrom(const KeeperInfo& from);
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
  
  // repeated .ConfigKeeper.KeeperTask item = 2;
  inline int item_size() const;
  inline void clear_item();
  static const int kItemFieldNumber = 2;
  inline const ::ConfigKeeper::KeeperTask& item(int index) const;
  inline ::ConfigKeeper::KeeperTask* mutable_item(int index);
  inline ::ConfigKeeper::KeeperTask* add_item();
  inline const ::google::protobuf::RepeatedPtrField< ::ConfigKeeper::KeeperTask >&
      item() const;
  inline ::google::protobuf::RepeatedPtrField< ::ConfigKeeper::KeeperTask >*
      mutable_item();
  
  // @@protoc_insertion_point(class_scope:ConfigKeeper.KeeperInfo)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::ConfigKeeper::KeeperTask > item_;
  ::google::protobuf::uint32 id_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_ConfigKeeper_2eproto();
  friend void protobuf_AssignDesc_ConfigKeeper_2eproto();
  friend void protobuf_ShutdownFile_ConfigKeeper_2eproto();
  
  void InitAsDefaultInstance();
  static KeeperInfo* default_instance_;
};
// -------------------------------------------------------------------

class KeeperCfg : public ::google::protobuf::Message {
 public:
  KeeperCfg();
  virtual ~KeeperCfg();
  
  KeeperCfg(const KeeperCfg& from);
  
  inline KeeperCfg& operator=(const KeeperCfg& from) {
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
  static const KeeperCfg& default_instance();
  
  void Swap(KeeperCfg* other);
  
  // implements Message ----------------------------------------------
  
  KeeperCfg* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const KeeperCfg& from);
  void MergeFrom(const KeeperCfg& from);
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
  
  // required int32 upgrade_cost = 1;
  inline bool has_upgrade_cost() const;
  inline void clear_upgrade_cost();
  static const int kUpgradeCostFieldNumber = 1;
  inline ::google::protobuf::int32 upgrade_cost() const;
  inline void set_upgrade_cost(::google::protobuf::int32 value);
  
  // required uint32 ad_reward_time = 2;
  inline bool has_ad_reward_time() const;
  inline void clear_ad_reward_time();
  static const int kAdRewardTimeFieldNumber = 2;
  inline ::google::protobuf::uint32 ad_reward_time() const;
  inline void set_ad_reward_time(::google::protobuf::uint32 value);
  
  // required uint32 upgrade_cost_reward_time = 3;
  inline bool has_upgrade_cost_reward_time() const;
  inline void clear_upgrade_cost_reward_time();
  static const int kUpgradeCostRewardTimeFieldNumber = 3;
  inline ::google::protobuf::uint32 upgrade_cost_reward_time() const;
  inline void set_upgrade_cost_reward_time(::google::protobuf::uint32 value);
  
  // repeated .ConfigKeeper.KeeperUpgradeItem upgrade = 4;
  inline int upgrade_size() const;
  inline void clear_upgrade();
  static const int kUpgradeFieldNumber = 4;
  inline const ::ConfigKeeper::KeeperUpgradeItem& upgrade(int index) const;
  inline ::ConfigKeeper::KeeperUpgradeItem* mutable_upgrade(int index);
  inline ::ConfigKeeper::KeeperUpgradeItem* add_upgrade();
  inline const ::google::protobuf::RepeatedPtrField< ::ConfigKeeper::KeeperUpgradeItem >&
      upgrade() const;
  inline ::google::protobuf::RepeatedPtrField< ::ConfigKeeper::KeeperUpgradeItem >*
      mutable_upgrade();
  
  // repeated .ConfigKeeper.KeeperInfo keeper = 5;
  inline int keeper_size() const;
  inline void clear_keeper();
  static const int kKeeperFieldNumber = 5;
  inline const ::ConfigKeeper::KeeperInfo& keeper(int index) const;
  inline ::ConfigKeeper::KeeperInfo* mutable_keeper(int index);
  inline ::ConfigKeeper::KeeperInfo* add_keeper();
  inline const ::google::protobuf::RepeatedPtrField< ::ConfigKeeper::KeeperInfo >&
      keeper() const;
  inline ::google::protobuf::RepeatedPtrField< ::ConfigKeeper::KeeperInfo >*
      mutable_keeper();
  
  // @@protoc_insertion_point(class_scope:ConfigKeeper.KeeperCfg)
 private:
  inline void set_has_upgrade_cost();
  inline void clear_has_upgrade_cost();
  inline void set_has_ad_reward_time();
  inline void clear_has_ad_reward_time();
  inline void set_has_upgrade_cost_reward_time();
  inline void clear_has_upgrade_cost_reward_time();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 upgrade_cost_;
  ::google::protobuf::uint32 ad_reward_time_;
  ::google::protobuf::RepeatedPtrField< ::ConfigKeeper::KeeperUpgradeItem > upgrade_;
  ::google::protobuf::RepeatedPtrField< ::ConfigKeeper::KeeperInfo > keeper_;
  ::google::protobuf::uint32 upgrade_cost_reward_time_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];
  
  friend void  protobuf_AddDesc_ConfigKeeper_2eproto();
  friend void protobuf_AssignDesc_ConfigKeeper_2eproto();
  friend void protobuf_ShutdownFile_ConfigKeeper_2eproto();
  
  void InitAsDefaultInstance();
  static KeeperCfg* default_instance_;
};
// ===================================================================


// ===================================================================

// KeeperUpgradeItem

// required uint32 exp = 1;
inline bool KeeperUpgradeItem::has_exp() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void KeeperUpgradeItem::set_has_exp() {
  _has_bits_[0] |= 0x00000001u;
}
inline void KeeperUpgradeItem::clear_has_exp() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void KeeperUpgradeItem::clear_exp() {
  exp_ = 0u;
  clear_has_exp();
}
inline ::google::protobuf::uint32 KeeperUpgradeItem::exp() const {
  return exp_;
}
inline void KeeperUpgradeItem::set_exp(::google::protobuf::uint32 value) {
  set_has_exp();
  exp_ = value;
}

// required uint32 max = 2;
inline bool KeeperUpgradeItem::has_max() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void KeeperUpgradeItem::set_has_max() {
  _has_bits_[0] |= 0x00000002u;
}
inline void KeeperUpgradeItem::clear_has_max() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void KeeperUpgradeItem::clear_max() {
  max_ = 0u;
  clear_has_max();
}
inline ::google::protobuf::uint32 KeeperUpgradeItem::max() const {
  return max_;
}
inline void KeeperUpgradeItem::set_max(::google::protobuf::uint32 value) {
  set_has_max();
  max_ = value;
}

// required uint32 cap = 3;
inline bool KeeperUpgradeItem::has_cap() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void KeeperUpgradeItem::set_has_cap() {
  _has_bits_[0] |= 0x00000004u;
}
inline void KeeperUpgradeItem::clear_has_cap() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void KeeperUpgradeItem::clear_cap() {
  cap_ = 0u;
  clear_has_cap();
}
inline ::google::protobuf::uint32 KeeperUpgradeItem::cap() const {
  return cap_;
}
inline void KeeperUpgradeItem::set_cap(::google::protobuf::uint32 value) {
  set_has_cap();
  cap_ = value;
}

// required .CommonGiftConfig.CommonModifyItem item = 4;
inline bool KeeperUpgradeItem::has_item() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void KeeperUpgradeItem::set_has_item() {
  _has_bits_[0] |= 0x00000008u;
}
inline void KeeperUpgradeItem::clear_has_item() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void KeeperUpgradeItem::clear_item() {
  if (item_ != NULL) item_->::CommonGiftConfig::CommonModifyItem::Clear();
  clear_has_item();
}
inline const ::CommonGiftConfig::CommonModifyItem& KeeperUpgradeItem::item() const {
  return item_ != NULL ? *item_ : *default_instance_->item_;
}
inline ::CommonGiftConfig::CommonModifyItem* KeeperUpgradeItem::mutable_item() {
  set_has_item();
  if (item_ == NULL) item_ = new ::CommonGiftConfig::CommonModifyItem;
  return item_;
}
inline ::CommonGiftConfig::CommonModifyItem* KeeperUpgradeItem::release_item() {
  clear_has_item();
  ::CommonGiftConfig::CommonModifyItem* temp = item_;
  item_ = NULL;
  return temp;
}

// -------------------------------------------------------------------

// KeeperTaskTarget

// required uint32 id = 1;
inline bool KeeperTaskTarget::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void KeeperTaskTarget::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void KeeperTaskTarget::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void KeeperTaskTarget::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 KeeperTaskTarget::id() const {
  return id_;
}
inline void KeeperTaskTarget::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// required uint32 tid = 2;
inline bool KeeperTaskTarget::has_tid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void KeeperTaskTarget::set_has_tid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void KeeperTaskTarget::clear_has_tid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void KeeperTaskTarget::clear_tid() {
  tid_ = 0u;
  clear_has_tid();
}
inline ::google::protobuf::uint32 KeeperTaskTarget::tid() const {
  return tid_;
}
inline void KeeperTaskTarget::set_tid(::google::protobuf::uint32 value) {
  set_has_tid();
  tid_ = value;
}

// -------------------------------------------------------------------

// KeeperTask

// required uint32 type = 1;
inline bool KeeperTask::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void KeeperTask::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void KeeperTask::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void KeeperTask::clear_type() {
  type_ = 0u;
  clear_has_type();
}
inline ::google::protobuf::uint32 KeeperTask::type() const {
  return type_;
}
inline void KeeperTask::set_type(::google::protobuf::uint32 value) {
  set_has_type();
  type_ = value;
}

// required uint32 bid = 2;
inline bool KeeperTask::has_bid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void KeeperTask::set_has_bid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void KeeperTask::clear_has_bid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void KeeperTask::clear_bid() {
  bid_ = 0u;
  clear_has_bid();
}
inline ::google::protobuf::uint32 KeeperTask::bid() const {
  return bid_;
}
inline void KeeperTask::set_bid(::google::protobuf::uint32 value) {
  set_has_bid();
  bid_ = value;
}

// repeated .ConfigKeeper.KeeperTaskTarget target = 3;
inline int KeeperTask::target_size() const {
  return target_.size();
}
inline void KeeperTask::clear_target() {
  target_.Clear();
}
inline const ::ConfigKeeper::KeeperTaskTarget& KeeperTask::target(int index) const {
  return target_.Get(index);
}
inline ::ConfigKeeper::KeeperTaskTarget* KeeperTask::mutable_target(int index) {
  return target_.Mutable(index);
}
inline ::ConfigKeeper::KeeperTaskTarget* KeeperTask::add_target() {
  return target_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ConfigKeeper::KeeperTaskTarget >&
KeeperTask::target() const {
  return target_;
}
inline ::google::protobuf::RepeatedPtrField< ::ConfigKeeper::KeeperTaskTarget >*
KeeperTask::mutable_target() {
  return &target_;
}

// -------------------------------------------------------------------

// KeeperInfo

// required uint32 id = 1;
inline bool KeeperInfo::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void KeeperInfo::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void KeeperInfo::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void KeeperInfo::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 KeeperInfo::id() const {
  return id_;
}
inline void KeeperInfo::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// repeated .ConfigKeeper.KeeperTask item = 2;
inline int KeeperInfo::item_size() const {
  return item_.size();
}
inline void KeeperInfo::clear_item() {
  item_.Clear();
}
inline const ::ConfigKeeper::KeeperTask& KeeperInfo::item(int index) const {
  return item_.Get(index);
}
inline ::ConfigKeeper::KeeperTask* KeeperInfo::mutable_item(int index) {
  return item_.Mutable(index);
}
inline ::ConfigKeeper::KeeperTask* KeeperInfo::add_item() {
  return item_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ConfigKeeper::KeeperTask >&
KeeperInfo::item() const {
  return item_;
}
inline ::google::protobuf::RepeatedPtrField< ::ConfigKeeper::KeeperTask >*
KeeperInfo::mutable_item() {
  return &item_;
}

// -------------------------------------------------------------------

// KeeperCfg

// required int32 upgrade_cost = 1;
inline bool KeeperCfg::has_upgrade_cost() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void KeeperCfg::set_has_upgrade_cost() {
  _has_bits_[0] |= 0x00000001u;
}
inline void KeeperCfg::clear_has_upgrade_cost() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void KeeperCfg::clear_upgrade_cost() {
  upgrade_cost_ = 0;
  clear_has_upgrade_cost();
}
inline ::google::protobuf::int32 KeeperCfg::upgrade_cost() const {
  return upgrade_cost_;
}
inline void KeeperCfg::set_upgrade_cost(::google::protobuf::int32 value) {
  set_has_upgrade_cost();
  upgrade_cost_ = value;
}

// required uint32 ad_reward_time = 2;
inline bool KeeperCfg::has_ad_reward_time() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void KeeperCfg::set_has_ad_reward_time() {
  _has_bits_[0] |= 0x00000002u;
}
inline void KeeperCfg::clear_has_ad_reward_time() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void KeeperCfg::clear_ad_reward_time() {
  ad_reward_time_ = 0u;
  clear_has_ad_reward_time();
}
inline ::google::protobuf::uint32 KeeperCfg::ad_reward_time() const {
  return ad_reward_time_;
}
inline void KeeperCfg::set_ad_reward_time(::google::protobuf::uint32 value) {
  set_has_ad_reward_time();
  ad_reward_time_ = value;
}

// required uint32 upgrade_cost_reward_time = 3;
inline bool KeeperCfg::has_upgrade_cost_reward_time() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void KeeperCfg::set_has_upgrade_cost_reward_time() {
  _has_bits_[0] |= 0x00000004u;
}
inline void KeeperCfg::clear_has_upgrade_cost_reward_time() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void KeeperCfg::clear_upgrade_cost_reward_time() {
  upgrade_cost_reward_time_ = 0u;
  clear_has_upgrade_cost_reward_time();
}
inline ::google::protobuf::uint32 KeeperCfg::upgrade_cost_reward_time() const {
  return upgrade_cost_reward_time_;
}
inline void KeeperCfg::set_upgrade_cost_reward_time(::google::protobuf::uint32 value) {
  set_has_upgrade_cost_reward_time();
  upgrade_cost_reward_time_ = value;
}

// repeated .ConfigKeeper.KeeperUpgradeItem upgrade = 4;
inline int KeeperCfg::upgrade_size() const {
  return upgrade_.size();
}
inline void KeeperCfg::clear_upgrade() {
  upgrade_.Clear();
}
inline const ::ConfigKeeper::KeeperUpgradeItem& KeeperCfg::upgrade(int index) const {
  return upgrade_.Get(index);
}
inline ::ConfigKeeper::KeeperUpgradeItem* KeeperCfg::mutable_upgrade(int index) {
  return upgrade_.Mutable(index);
}
inline ::ConfigKeeper::KeeperUpgradeItem* KeeperCfg::add_upgrade() {
  return upgrade_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ConfigKeeper::KeeperUpgradeItem >&
KeeperCfg::upgrade() const {
  return upgrade_;
}
inline ::google::protobuf::RepeatedPtrField< ::ConfigKeeper::KeeperUpgradeItem >*
KeeperCfg::mutable_upgrade() {
  return &upgrade_;
}

// repeated .ConfigKeeper.KeeperInfo keeper = 5;
inline int KeeperCfg::keeper_size() const {
  return keeper_.size();
}
inline void KeeperCfg::clear_keeper() {
  keeper_.Clear();
}
inline const ::ConfigKeeper::KeeperInfo& KeeperCfg::keeper(int index) const {
  return keeper_.Get(index);
}
inline ::ConfigKeeper::KeeperInfo* KeeperCfg::mutable_keeper(int index) {
  return keeper_.Mutable(index);
}
inline ::ConfigKeeper::KeeperInfo* KeeperCfg::add_keeper() {
  return keeper_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ConfigKeeper::KeeperInfo >&
KeeperCfg::keeper() const {
  return keeper_;
}
inline ::google::protobuf::RepeatedPtrField< ::ConfigKeeper::KeeperInfo >*
KeeperCfg::mutable_keeper() {
  return &keeper_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ConfigKeeper

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ConfigKeeper_2eproto__INCLUDED
