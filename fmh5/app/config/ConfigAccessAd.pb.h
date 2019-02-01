// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ConfigAccessAd.proto

#ifndef PROTOBUF_ConfigAccessAd_2eproto__INCLUDED
#define PROTOBUF_ConfigAccessAd_2eproto__INCLUDED

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
// @@protoc_insertion_point(includes)

namespace ConfigAccessAd {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ConfigAccessAd_2eproto();
void protobuf_AssignDesc_ConfigAccessAd_2eproto();
void protobuf_ShutdownFile_ConfigAccessAd_2eproto();

class AdReardItemLibCPP;
class AdRewardCPP;
class ViewAdCPP;
class ScarecrowCPP;
class AccessAdCfg;

// ===================================================================

class AdReardItemLibCPP : public ::google::protobuf::Message {
 public:
  AdReardItemLibCPP();
  virtual ~AdReardItemLibCPP();
  
  AdReardItemLibCPP(const AdReardItemLibCPP& from);
  
  inline AdReardItemLibCPP& operator=(const AdReardItemLibCPP& from) {
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
  static const AdReardItemLibCPP& default_instance();
  
  void Swap(AdReardItemLibCPP* other);
  
  // implements Message ----------------------------------------------
  
  AdReardItemLibCPP* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AdReardItemLibCPP& from);
  void MergeFrom(const AdReardItemLibCPP& from);
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
  
  // required uint32 itemid = 1;
  inline bool has_itemid() const;
  inline void clear_itemid();
  static const int kItemidFieldNumber = 1;
  inline ::google::protobuf::uint32 itemid() const;
  inline void set_itemid(::google::protobuf::uint32 value);
  
  // required uint32 weight = 2;
  inline bool has_weight() const;
  inline void clear_weight();
  static const int kWeightFieldNumber = 2;
  inline ::google::protobuf::uint32 weight() const;
  inline void set_weight(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:ConfigAccessAd.AdReardItemLibCPP)
 private:
  inline void set_has_itemid();
  inline void clear_has_itemid();
  inline void set_has_weight();
  inline void clear_has_weight();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint32 itemid_;
  ::google::protobuf::uint32 weight_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_ConfigAccessAd_2eproto();
  friend void protobuf_AssignDesc_ConfigAccessAd_2eproto();
  friend void protobuf_ShutdownFile_ConfigAccessAd_2eproto();
  
  void InitAsDefaultInstance();
  static AdReardItemLibCPP* default_instance_;
};
// -------------------------------------------------------------------

class AdRewardCPP : public ::google::protobuf::Message {
 public:
  AdRewardCPP();
  virtual ~AdRewardCPP();
  
  AdRewardCPP(const AdRewardCPP& from);
  
  inline AdRewardCPP& operator=(const AdRewardCPP& from) {
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
  static const AdRewardCPP& default_instance();
  
  void Swap(AdRewardCPP* other);
  
  // implements Message ----------------------------------------------
  
  AdRewardCPP* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AdRewardCPP& from);
  void MergeFrom(const AdRewardCPP& from);
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
  
  // repeated uint32 level = 1;
  inline int level_size() const;
  inline void clear_level();
  static const int kLevelFieldNumber = 1;
  inline ::google::protobuf::uint32 level(int index) const;
  inline void set_level(int index, ::google::protobuf::uint32 value);
  inline void add_level(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      level() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_level();
  
  // repeated .ConfigAccessAd.AdReardItemLibCPP itemlib = 2;
  inline int itemlib_size() const;
  inline void clear_itemlib();
  static const int kItemlibFieldNumber = 2;
  inline const ::ConfigAccessAd::AdReardItemLibCPP& itemlib(int index) const;
  inline ::ConfigAccessAd::AdReardItemLibCPP* mutable_itemlib(int index);
  inline ::ConfigAccessAd::AdReardItemLibCPP* add_itemlib();
  inline const ::google::protobuf::RepeatedPtrField< ::ConfigAccessAd::AdReardItemLibCPP >&
      itemlib() const;
  inline ::google::protobuf::RepeatedPtrField< ::ConfigAccessAd::AdReardItemLibCPP >*
      mutable_itemlib();
  
  // @@protoc_insertion_point(class_scope:ConfigAccessAd.AdRewardCPP)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > level_;
  ::google::protobuf::RepeatedPtrField< ::ConfigAccessAd::AdReardItemLibCPP > itemlib_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_ConfigAccessAd_2eproto();
  friend void protobuf_AssignDesc_ConfigAccessAd_2eproto();
  friend void protobuf_ShutdownFile_ConfigAccessAd_2eproto();
  
  void InitAsDefaultInstance();
  static AdRewardCPP* default_instance_;
};
// -------------------------------------------------------------------

class ViewAdCPP : public ::google::protobuf::Message {
 public:
  ViewAdCPP();
  virtual ~ViewAdCPP();
  
  ViewAdCPP(const ViewAdCPP& from);
  
  inline ViewAdCPP& operator=(const ViewAdCPP& from) {
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
  static const ViewAdCPP& default_instance();
  
  void Swap(ViewAdCPP* other);
  
  // implements Message ----------------------------------------------
  
  ViewAdCPP* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ViewAdCPP& from);
  void MergeFrom(const ViewAdCPP& from);
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
  
  // required uint32 unlock_level = 1;
  inline bool has_unlock_level() const;
  inline void clear_unlock_level();
  static const int kUnlockLevelFieldNumber = 1;
  inline ::google::protobuf::uint32 unlock_level() const;
  inline void set_unlock_level(::google::protobuf::uint32 value);
  
  // required uint32 balloon_unlock_level = 2;
  inline bool has_balloon_unlock_level() const;
  inline void clear_balloon_unlock_level();
  static const int kBalloonUnlockLevelFieldNumber = 2;
  inline ::google::protobuf::uint32 balloon_unlock_level() const;
  inline void set_balloon_unlock_level(::google::protobuf::uint32 value);
  
  // required uint32 balloon_cd_time = 3;
  inline bool has_balloon_cd_time() const;
  inline void clear_balloon_cd_time();
  static const int kBalloonCdTimeFieldNumber = 3;
  inline ::google::protobuf::uint32 balloon_cd_time() const;
  inline void set_balloon_cd_time(::google::protobuf::uint32 value);
  
  // required uint32 daily_ballon_view_ad_cnt = 4;
  inline bool has_daily_ballon_view_ad_cnt() const;
  inline void clear_daily_ballon_view_ad_cnt();
  static const int kDailyBallonViewAdCntFieldNumber = 4;
  inline ::google::protobuf::uint32 daily_ballon_view_ad_cnt() const;
  inline void set_daily_ballon_view_ad_cnt(::google::protobuf::uint32 value);
  
  // required uint32 reward_wait_time = 5;
  inline bool has_reward_wait_time() const;
  inline void clear_reward_wait_time();
  static const int kRewardWaitTimeFieldNumber = 5;
  inline ::google::protobuf::uint32 reward_wait_time() const;
  inline void set_reward_wait_time(::google::protobuf::uint32 value);
  
  // repeated .ConfigAccessAd.AdRewardCPP reward_item_lib = 6;
  inline int reward_item_lib_size() const;
  inline void clear_reward_item_lib();
  static const int kRewardItemLibFieldNumber = 6;
  inline const ::ConfigAccessAd::AdRewardCPP& reward_item_lib(int index) const;
  inline ::ConfigAccessAd::AdRewardCPP* mutable_reward_item_lib(int index);
  inline ::ConfigAccessAd::AdRewardCPP* add_reward_item_lib();
  inline const ::google::protobuf::RepeatedPtrField< ::ConfigAccessAd::AdRewardCPP >&
      reward_item_lib() const;
  inline ::google::protobuf::RepeatedPtrField< ::ConfigAccessAd::AdRewardCPP >*
      mutable_reward_item_lib();
  
  // @@protoc_insertion_point(class_scope:ConfigAccessAd.ViewAdCPP)
 private:
  inline void set_has_unlock_level();
  inline void clear_has_unlock_level();
  inline void set_has_balloon_unlock_level();
  inline void clear_has_balloon_unlock_level();
  inline void set_has_balloon_cd_time();
  inline void clear_has_balloon_cd_time();
  inline void set_has_daily_ballon_view_ad_cnt();
  inline void clear_has_daily_ballon_view_ad_cnt();
  inline void set_has_reward_wait_time();
  inline void clear_has_reward_wait_time();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint32 unlock_level_;
  ::google::protobuf::uint32 balloon_unlock_level_;
  ::google::protobuf::uint32 balloon_cd_time_;
  ::google::protobuf::uint32 daily_ballon_view_ad_cnt_;
  ::google::protobuf::RepeatedPtrField< ::ConfigAccessAd::AdRewardCPP > reward_item_lib_;
  ::google::protobuf::uint32 reward_wait_time_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(6 + 31) / 32];
  
  friend void  protobuf_AddDesc_ConfigAccessAd_2eproto();
  friend void protobuf_AssignDesc_ConfigAccessAd_2eproto();
  friend void protobuf_ShutdownFile_ConfigAccessAd_2eproto();
  
  void InitAsDefaultInstance();
  static ViewAdCPP* default_instance_;
};
// -------------------------------------------------------------------

class ScarecrowCPP : public ::google::protobuf::Message {
 public:
  ScarecrowCPP();
  virtual ~ScarecrowCPP();
  
  ScarecrowCPP(const ScarecrowCPP& from);
  
  inline ScarecrowCPP& operator=(const ScarecrowCPP& from) {
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
  static const ScarecrowCPP& default_instance();
  
  void Swap(ScarecrowCPP* other);
  
  // implements Message ----------------------------------------------
  
  ScarecrowCPP* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ScarecrowCPP& from);
  void MergeFrom(const ScarecrowCPP& from);
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
  
  // required uint32 bonus_time = 1;
  inline bool has_bonus_time() const;
  inline void clear_bonus_time();
  static const int kBonusTimeFieldNumber = 1;
  inline ::google::protobuf::uint32 bonus_time() const;
  inline void set_bonus_time(::google::protobuf::uint32 value);
  
  // required uint32 bonus_percent = 2;
  inline bool has_bonus_percent() const;
  inline void clear_bonus_percent();
  static const int kBonusPercentFieldNumber = 2;
  inline ::google::protobuf::uint32 bonus_percent() const;
  inline void set_bonus_percent(::google::protobuf::uint32 value);
  
  // required uint32 cd_time = 3;
  inline bool has_cd_time() const;
  inline void clear_cd_time();
  static const int kCdTimeFieldNumber = 3;
  inline ::google::protobuf::uint32 cd_time() const;
  inline void set_cd_time(::google::protobuf::uint32 value);
  
  // required uint32 unlock_level = 4;
  inline bool has_unlock_level() const;
  inline void clear_unlock_level();
  static const int kUnlockLevelFieldNumber = 4;
  inline ::google::protobuf::uint32 unlock_level() const;
  inline void set_unlock_level(::google::protobuf::uint32 value);
  
  // required uint32 daily_bonus_cnt = 5;
  inline bool has_daily_bonus_cnt() const;
  inline void clear_daily_bonus_cnt();
  static const int kDailyBonusCntFieldNumber = 5;
  inline ::google::protobuf::uint32 daily_bonus_cnt() const;
  inline void set_daily_bonus_cnt(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:ConfigAccessAd.ScarecrowCPP)
 private:
  inline void set_has_bonus_time();
  inline void clear_has_bonus_time();
  inline void set_has_bonus_percent();
  inline void clear_has_bonus_percent();
  inline void set_has_cd_time();
  inline void clear_has_cd_time();
  inline void set_has_unlock_level();
  inline void clear_has_unlock_level();
  inline void set_has_daily_bonus_cnt();
  inline void clear_has_daily_bonus_cnt();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint32 bonus_time_;
  ::google::protobuf::uint32 bonus_percent_;
  ::google::protobuf::uint32 cd_time_;
  ::google::protobuf::uint32 unlock_level_;
  ::google::protobuf::uint32 daily_bonus_cnt_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];
  
  friend void  protobuf_AddDesc_ConfigAccessAd_2eproto();
  friend void protobuf_AssignDesc_ConfigAccessAd_2eproto();
  friend void protobuf_ShutdownFile_ConfigAccessAd_2eproto();
  
  void InitAsDefaultInstance();
  static ScarecrowCPP* default_instance_;
};
// -------------------------------------------------------------------

class AccessAdCfg : public ::google::protobuf::Message {
 public:
  AccessAdCfg();
  virtual ~AccessAdCfg();
  
  AccessAdCfg(const AccessAdCfg& from);
  
  inline AccessAdCfg& operator=(const AccessAdCfg& from) {
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
  static const AccessAdCfg& default_instance();
  
  void Swap(AccessAdCfg* other);
  
  // implements Message ----------------------------------------------
  
  AccessAdCfg* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AccessAdCfg& from);
  void MergeFrom(const AccessAdCfg& from);
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
  
  // required .ConfigAccessAd.ViewAdCPP access_ad = 1;
  inline bool has_access_ad() const;
  inline void clear_access_ad();
  static const int kAccessAdFieldNumber = 1;
  inline const ::ConfigAccessAd::ViewAdCPP& access_ad() const;
  inline ::ConfigAccessAd::ViewAdCPP* mutable_access_ad();
  inline ::ConfigAccessAd::ViewAdCPP* release_access_ad();
  
  // required .ConfigAccessAd.ScarecrowCPP scarecrow_ad = 2;
  inline bool has_scarecrow_ad() const;
  inline void clear_scarecrow_ad();
  static const int kScarecrowAdFieldNumber = 2;
  inline const ::ConfigAccessAd::ScarecrowCPP& scarecrow_ad() const;
  inline ::ConfigAccessAd::ScarecrowCPP* mutable_scarecrow_ad();
  inline ::ConfigAccessAd::ScarecrowCPP* release_scarecrow_ad();
  
  // @@protoc_insertion_point(class_scope:ConfigAccessAd.AccessAdCfg)
 private:
  inline void set_has_access_ad();
  inline void clear_has_access_ad();
  inline void set_has_scarecrow_ad();
  inline void clear_has_scarecrow_ad();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::ConfigAccessAd::ViewAdCPP* access_ad_;
  ::ConfigAccessAd::ScarecrowCPP* scarecrow_ad_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_ConfigAccessAd_2eproto();
  friend void protobuf_AssignDesc_ConfigAccessAd_2eproto();
  friend void protobuf_ShutdownFile_ConfigAccessAd_2eproto();
  
  void InitAsDefaultInstance();
  static AccessAdCfg* default_instance_;
};
// ===================================================================


// ===================================================================

// AdReardItemLibCPP

// required uint32 itemid = 1;
inline bool AdReardItemLibCPP::has_itemid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AdReardItemLibCPP::set_has_itemid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AdReardItemLibCPP::clear_has_itemid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AdReardItemLibCPP::clear_itemid() {
  itemid_ = 0u;
  clear_has_itemid();
}
inline ::google::protobuf::uint32 AdReardItemLibCPP::itemid() const {
  return itemid_;
}
inline void AdReardItemLibCPP::set_itemid(::google::protobuf::uint32 value) {
  set_has_itemid();
  itemid_ = value;
}

// required uint32 weight = 2;
inline bool AdReardItemLibCPP::has_weight() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AdReardItemLibCPP::set_has_weight() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AdReardItemLibCPP::clear_has_weight() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AdReardItemLibCPP::clear_weight() {
  weight_ = 0u;
  clear_has_weight();
}
inline ::google::protobuf::uint32 AdReardItemLibCPP::weight() const {
  return weight_;
}
inline void AdReardItemLibCPP::set_weight(::google::protobuf::uint32 value) {
  set_has_weight();
  weight_ = value;
}

// -------------------------------------------------------------------

// AdRewardCPP

// repeated uint32 level = 1;
inline int AdRewardCPP::level_size() const {
  return level_.size();
}
inline void AdRewardCPP::clear_level() {
  level_.Clear();
}
inline ::google::protobuf::uint32 AdRewardCPP::level(int index) const {
  return level_.Get(index);
}
inline void AdRewardCPP::set_level(int index, ::google::protobuf::uint32 value) {
  level_.Set(index, value);
}
inline void AdRewardCPP::add_level(::google::protobuf::uint32 value) {
  level_.Add(value);
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
AdRewardCPP::level() const {
  return level_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
AdRewardCPP::mutable_level() {
  return &level_;
}

// repeated .ConfigAccessAd.AdReardItemLibCPP itemlib = 2;
inline int AdRewardCPP::itemlib_size() const {
  return itemlib_.size();
}
inline void AdRewardCPP::clear_itemlib() {
  itemlib_.Clear();
}
inline const ::ConfigAccessAd::AdReardItemLibCPP& AdRewardCPP::itemlib(int index) const {
  return itemlib_.Get(index);
}
inline ::ConfigAccessAd::AdReardItemLibCPP* AdRewardCPP::mutable_itemlib(int index) {
  return itemlib_.Mutable(index);
}
inline ::ConfigAccessAd::AdReardItemLibCPP* AdRewardCPP::add_itemlib() {
  return itemlib_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ConfigAccessAd::AdReardItemLibCPP >&
AdRewardCPP::itemlib() const {
  return itemlib_;
}
inline ::google::protobuf::RepeatedPtrField< ::ConfigAccessAd::AdReardItemLibCPP >*
AdRewardCPP::mutable_itemlib() {
  return &itemlib_;
}

// -------------------------------------------------------------------

// ViewAdCPP

// required uint32 unlock_level = 1;
inline bool ViewAdCPP::has_unlock_level() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ViewAdCPP::set_has_unlock_level() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ViewAdCPP::clear_has_unlock_level() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ViewAdCPP::clear_unlock_level() {
  unlock_level_ = 0u;
  clear_has_unlock_level();
}
inline ::google::protobuf::uint32 ViewAdCPP::unlock_level() const {
  return unlock_level_;
}
inline void ViewAdCPP::set_unlock_level(::google::protobuf::uint32 value) {
  set_has_unlock_level();
  unlock_level_ = value;
}

// required uint32 balloon_unlock_level = 2;
inline bool ViewAdCPP::has_balloon_unlock_level() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ViewAdCPP::set_has_balloon_unlock_level() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ViewAdCPP::clear_has_balloon_unlock_level() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ViewAdCPP::clear_balloon_unlock_level() {
  balloon_unlock_level_ = 0u;
  clear_has_balloon_unlock_level();
}
inline ::google::protobuf::uint32 ViewAdCPP::balloon_unlock_level() const {
  return balloon_unlock_level_;
}
inline void ViewAdCPP::set_balloon_unlock_level(::google::protobuf::uint32 value) {
  set_has_balloon_unlock_level();
  balloon_unlock_level_ = value;
}

// required uint32 balloon_cd_time = 3;
inline bool ViewAdCPP::has_balloon_cd_time() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ViewAdCPP::set_has_balloon_cd_time() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ViewAdCPP::clear_has_balloon_cd_time() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ViewAdCPP::clear_balloon_cd_time() {
  balloon_cd_time_ = 0u;
  clear_has_balloon_cd_time();
}
inline ::google::protobuf::uint32 ViewAdCPP::balloon_cd_time() const {
  return balloon_cd_time_;
}
inline void ViewAdCPP::set_balloon_cd_time(::google::protobuf::uint32 value) {
  set_has_balloon_cd_time();
  balloon_cd_time_ = value;
}

// required uint32 daily_ballon_view_ad_cnt = 4;
inline bool ViewAdCPP::has_daily_ballon_view_ad_cnt() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ViewAdCPP::set_has_daily_ballon_view_ad_cnt() {
  _has_bits_[0] |= 0x00000008u;
}
inline void ViewAdCPP::clear_has_daily_ballon_view_ad_cnt() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void ViewAdCPP::clear_daily_ballon_view_ad_cnt() {
  daily_ballon_view_ad_cnt_ = 0u;
  clear_has_daily_ballon_view_ad_cnt();
}
inline ::google::protobuf::uint32 ViewAdCPP::daily_ballon_view_ad_cnt() const {
  return daily_ballon_view_ad_cnt_;
}
inline void ViewAdCPP::set_daily_ballon_view_ad_cnt(::google::protobuf::uint32 value) {
  set_has_daily_ballon_view_ad_cnt();
  daily_ballon_view_ad_cnt_ = value;
}

// required uint32 reward_wait_time = 5;
inline bool ViewAdCPP::has_reward_wait_time() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void ViewAdCPP::set_has_reward_wait_time() {
  _has_bits_[0] |= 0x00000010u;
}
inline void ViewAdCPP::clear_has_reward_wait_time() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void ViewAdCPP::clear_reward_wait_time() {
  reward_wait_time_ = 0u;
  clear_has_reward_wait_time();
}
inline ::google::protobuf::uint32 ViewAdCPP::reward_wait_time() const {
  return reward_wait_time_;
}
inline void ViewAdCPP::set_reward_wait_time(::google::protobuf::uint32 value) {
  set_has_reward_wait_time();
  reward_wait_time_ = value;
}

// repeated .ConfigAccessAd.AdRewardCPP reward_item_lib = 6;
inline int ViewAdCPP::reward_item_lib_size() const {
  return reward_item_lib_.size();
}
inline void ViewAdCPP::clear_reward_item_lib() {
  reward_item_lib_.Clear();
}
inline const ::ConfigAccessAd::AdRewardCPP& ViewAdCPP::reward_item_lib(int index) const {
  return reward_item_lib_.Get(index);
}
inline ::ConfigAccessAd::AdRewardCPP* ViewAdCPP::mutable_reward_item_lib(int index) {
  return reward_item_lib_.Mutable(index);
}
inline ::ConfigAccessAd::AdRewardCPP* ViewAdCPP::add_reward_item_lib() {
  return reward_item_lib_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ConfigAccessAd::AdRewardCPP >&
ViewAdCPP::reward_item_lib() const {
  return reward_item_lib_;
}
inline ::google::protobuf::RepeatedPtrField< ::ConfigAccessAd::AdRewardCPP >*
ViewAdCPP::mutable_reward_item_lib() {
  return &reward_item_lib_;
}

// -------------------------------------------------------------------

// ScarecrowCPP

// required uint32 bonus_time = 1;
inline bool ScarecrowCPP::has_bonus_time() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ScarecrowCPP::set_has_bonus_time() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ScarecrowCPP::clear_has_bonus_time() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ScarecrowCPP::clear_bonus_time() {
  bonus_time_ = 0u;
  clear_has_bonus_time();
}
inline ::google::protobuf::uint32 ScarecrowCPP::bonus_time() const {
  return bonus_time_;
}
inline void ScarecrowCPP::set_bonus_time(::google::protobuf::uint32 value) {
  set_has_bonus_time();
  bonus_time_ = value;
}

// required uint32 bonus_percent = 2;
inline bool ScarecrowCPP::has_bonus_percent() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ScarecrowCPP::set_has_bonus_percent() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ScarecrowCPP::clear_has_bonus_percent() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ScarecrowCPP::clear_bonus_percent() {
  bonus_percent_ = 0u;
  clear_has_bonus_percent();
}
inline ::google::protobuf::uint32 ScarecrowCPP::bonus_percent() const {
  return bonus_percent_;
}
inline void ScarecrowCPP::set_bonus_percent(::google::protobuf::uint32 value) {
  set_has_bonus_percent();
  bonus_percent_ = value;
}

// required uint32 cd_time = 3;
inline bool ScarecrowCPP::has_cd_time() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ScarecrowCPP::set_has_cd_time() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ScarecrowCPP::clear_has_cd_time() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ScarecrowCPP::clear_cd_time() {
  cd_time_ = 0u;
  clear_has_cd_time();
}
inline ::google::protobuf::uint32 ScarecrowCPP::cd_time() const {
  return cd_time_;
}
inline void ScarecrowCPP::set_cd_time(::google::protobuf::uint32 value) {
  set_has_cd_time();
  cd_time_ = value;
}

// required uint32 unlock_level = 4;
inline bool ScarecrowCPP::has_unlock_level() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ScarecrowCPP::set_has_unlock_level() {
  _has_bits_[0] |= 0x00000008u;
}
inline void ScarecrowCPP::clear_has_unlock_level() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void ScarecrowCPP::clear_unlock_level() {
  unlock_level_ = 0u;
  clear_has_unlock_level();
}
inline ::google::protobuf::uint32 ScarecrowCPP::unlock_level() const {
  return unlock_level_;
}
inline void ScarecrowCPP::set_unlock_level(::google::protobuf::uint32 value) {
  set_has_unlock_level();
  unlock_level_ = value;
}

// required uint32 daily_bonus_cnt = 5;
inline bool ScarecrowCPP::has_daily_bonus_cnt() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void ScarecrowCPP::set_has_daily_bonus_cnt() {
  _has_bits_[0] |= 0x00000010u;
}
inline void ScarecrowCPP::clear_has_daily_bonus_cnt() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void ScarecrowCPP::clear_daily_bonus_cnt() {
  daily_bonus_cnt_ = 0u;
  clear_has_daily_bonus_cnt();
}
inline ::google::protobuf::uint32 ScarecrowCPP::daily_bonus_cnt() const {
  return daily_bonus_cnt_;
}
inline void ScarecrowCPP::set_daily_bonus_cnt(::google::protobuf::uint32 value) {
  set_has_daily_bonus_cnt();
  daily_bonus_cnt_ = value;
}

// -------------------------------------------------------------------

// AccessAdCfg

// required .ConfigAccessAd.ViewAdCPP access_ad = 1;
inline bool AccessAdCfg::has_access_ad() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AccessAdCfg::set_has_access_ad() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AccessAdCfg::clear_has_access_ad() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AccessAdCfg::clear_access_ad() {
  if (access_ad_ != NULL) access_ad_->::ConfigAccessAd::ViewAdCPP::Clear();
  clear_has_access_ad();
}
inline const ::ConfigAccessAd::ViewAdCPP& AccessAdCfg::access_ad() const {
  return access_ad_ != NULL ? *access_ad_ : *default_instance_->access_ad_;
}
inline ::ConfigAccessAd::ViewAdCPP* AccessAdCfg::mutable_access_ad() {
  set_has_access_ad();
  if (access_ad_ == NULL) access_ad_ = new ::ConfigAccessAd::ViewAdCPP;
  return access_ad_;
}
inline ::ConfigAccessAd::ViewAdCPP* AccessAdCfg::release_access_ad() {
  clear_has_access_ad();
  ::ConfigAccessAd::ViewAdCPP* temp = access_ad_;
  access_ad_ = NULL;
  return temp;
}

// required .ConfigAccessAd.ScarecrowCPP scarecrow_ad = 2;
inline bool AccessAdCfg::has_scarecrow_ad() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AccessAdCfg::set_has_scarecrow_ad() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AccessAdCfg::clear_has_scarecrow_ad() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AccessAdCfg::clear_scarecrow_ad() {
  if (scarecrow_ad_ != NULL) scarecrow_ad_->::ConfigAccessAd::ScarecrowCPP::Clear();
  clear_has_scarecrow_ad();
}
inline const ::ConfigAccessAd::ScarecrowCPP& AccessAdCfg::scarecrow_ad() const {
  return scarecrow_ad_ != NULL ? *scarecrow_ad_ : *default_instance_->scarecrow_ad_;
}
inline ::ConfigAccessAd::ScarecrowCPP* AccessAdCfg::mutable_scarecrow_ad() {
  set_has_scarecrow_ad();
  if (scarecrow_ad_ == NULL) scarecrow_ad_ = new ::ConfigAccessAd::ScarecrowCPP;
  return scarecrow_ad_;
}
inline ::ConfigAccessAd::ScarecrowCPP* AccessAdCfg::release_scarecrow_ad() {
  clear_has_scarecrow_ad();
  ::ConfigAccessAd::ScarecrowCPP* temp = scarecrow_ad_;
  scarecrow_ad_ = NULL;
  return temp;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ConfigAccessAd

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ConfigAccessAd_2eproto__INCLUDED
