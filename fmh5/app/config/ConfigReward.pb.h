// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ConfigReward.proto

#ifndef PROTOBUF_ConfigReward_2eproto__INCLUDED
#define PROTOBUF_ConfigReward_2eproto__INCLUDED

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

namespace ConfigReward {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ConfigReward_2eproto();
void protobuf_AssignDesc_ConfigReward_2eproto();
void protobuf_ShutdownFile_ConfigReward_2eproto();

class FirstRechargeRewardCPP;
class FollowPublicRewardCPP;
class FetchProductWatchAdsItem;
class FetchProductWatchAds;
class RewardList;

// ===================================================================

class FirstRechargeRewardCPP : public ::google::protobuf::Message {
 public:
  FirstRechargeRewardCPP();
  virtual ~FirstRechargeRewardCPP();
  
  FirstRechargeRewardCPP(const FirstRechargeRewardCPP& from);
  
  inline FirstRechargeRewardCPP& operator=(const FirstRechargeRewardCPP& from) {
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
  static const FirstRechargeRewardCPP& default_instance();
  
  void Swap(FirstRechargeRewardCPP* other);
  
  // implements Message ----------------------------------------------
  
  FirstRechargeRewardCPP* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const FirstRechargeRewardCPP& from);
  void MergeFrom(const FirstRechargeRewardCPP& from);
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
  
  // required .CommonGiftConfig.CommonModifyItem common = 1;
  inline bool has_common() const;
  inline void clear_common();
  static const int kCommonFieldNumber = 1;
  inline const ::CommonGiftConfig::CommonModifyItem& common() const;
  inline ::CommonGiftConfig::CommonModifyItem* mutable_common();
  inline ::CommonGiftConfig::CommonModifyItem* release_common();
  
  // @@protoc_insertion_point(class_scope:ConfigReward.FirstRechargeRewardCPP)
 private:
  inline void set_has_common();
  inline void clear_has_common();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::CommonGiftConfig::CommonModifyItem* common_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_ConfigReward_2eproto();
  friend void protobuf_AssignDesc_ConfigReward_2eproto();
  friend void protobuf_ShutdownFile_ConfigReward_2eproto();
  
  void InitAsDefaultInstance();
  static FirstRechargeRewardCPP* default_instance_;
};
// -------------------------------------------------------------------

class FollowPublicRewardCPP : public ::google::protobuf::Message {
 public:
  FollowPublicRewardCPP();
  virtual ~FollowPublicRewardCPP();
  
  FollowPublicRewardCPP(const FollowPublicRewardCPP& from);
  
  inline FollowPublicRewardCPP& operator=(const FollowPublicRewardCPP& from) {
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
  static const FollowPublicRewardCPP& default_instance();
  
  void Swap(FollowPublicRewardCPP* other);
  
  // implements Message ----------------------------------------------
  
  FollowPublicRewardCPP* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const FollowPublicRewardCPP& from);
  void MergeFrom(const FollowPublicRewardCPP& from);
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
  
  // required .CommonGiftConfig.CommonModifyItem common = 1;
  inline bool has_common() const;
  inline void clear_common();
  static const int kCommonFieldNumber = 1;
  inline const ::CommonGiftConfig::CommonModifyItem& common() const;
  inline ::CommonGiftConfig::CommonModifyItem* mutable_common();
  inline ::CommonGiftConfig::CommonModifyItem* release_common();
  
  // @@protoc_insertion_point(class_scope:ConfigReward.FollowPublicRewardCPP)
 private:
  inline void set_has_common();
  inline void clear_has_common();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::CommonGiftConfig::CommonModifyItem* common_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_ConfigReward_2eproto();
  friend void protobuf_AssignDesc_ConfigReward_2eproto();
  friend void protobuf_ShutdownFile_ConfigReward_2eproto();
  
  void InitAsDefaultInstance();
  static FollowPublicRewardCPP* default_instance_;
};
// -------------------------------------------------------------------

class FetchProductWatchAdsItem : public ::google::protobuf::Message {
 public:
  FetchProductWatchAdsItem();
  virtual ~FetchProductWatchAdsItem();
  
  FetchProductWatchAdsItem(const FetchProductWatchAdsItem& from);
  
  inline FetchProductWatchAdsItem& operator=(const FetchProductWatchAdsItem& from) {
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
  static const FetchProductWatchAdsItem& default_instance();
  
  void Swap(FetchProductWatchAdsItem* other);
  
  // implements Message ----------------------------------------------
  
  FetchProductWatchAdsItem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const FetchProductWatchAdsItem& from);
  void MergeFrom(const FetchProductWatchAdsItem& from);
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
  
  // required uint32 rate = 2;
  inline bool has_rate() const;
  inline void clear_rate();
  static const int kRateFieldNumber = 2;
  inline ::google::protobuf::uint32 rate() const;
  inline void set_rate(::google::protobuf::uint32 value);
  
  // required uint32 count = 3;
  inline bool has_count() const;
  inline void clear_count();
  static const int kCountFieldNumber = 3;
  inline ::google::protobuf::uint32 count() const;
  inline void set_count(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:ConfigReward.FetchProductWatchAdsItem)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_rate();
  inline void clear_has_rate();
  inline void set_has_count();
  inline void clear_has_count();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 rate_;
  ::google::protobuf::uint32 count_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_ConfigReward_2eproto();
  friend void protobuf_AssignDesc_ConfigReward_2eproto();
  friend void protobuf_ShutdownFile_ConfigReward_2eproto();
  
  void InitAsDefaultInstance();
  static FetchProductWatchAdsItem* default_instance_;
};
// -------------------------------------------------------------------

class FetchProductWatchAds : public ::google::protobuf::Message {
 public:
  FetchProductWatchAds();
  virtual ~FetchProductWatchAds();
  
  FetchProductWatchAds(const FetchProductWatchAds& from);
  
  inline FetchProductWatchAds& operator=(const FetchProductWatchAds& from) {
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
  static const FetchProductWatchAds& default_instance();
  
  void Swap(FetchProductWatchAds* other);
  
  // implements Message ----------------------------------------------
  
  FetchProductWatchAds* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const FetchProductWatchAds& from);
  void MergeFrom(const FetchProductWatchAds& from);
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
  
  // required uint32 minTime = 1;
  inline bool has_mintime() const;
  inline void clear_mintime();
  static const int kMinTimeFieldNumber = 1;
  inline ::google::protobuf::uint32 mintime() const;
  inline void set_mintime(::google::protobuf::uint32 value);
  
  // required uint32 cd = 2;
  inline bool has_cd() const;
  inline void clear_cd();
  static const int kCdFieldNumber = 2;
  inline ::google::protobuf::uint32 cd() const;
  inline void set_cd(::google::protobuf::uint32 value);
  
  // repeated .ConfigReward.FetchProductWatchAdsItem reward = 3;
  inline int reward_size() const;
  inline void clear_reward();
  static const int kRewardFieldNumber = 3;
  inline const ::ConfigReward::FetchProductWatchAdsItem& reward(int index) const;
  inline ::ConfigReward::FetchProductWatchAdsItem* mutable_reward(int index);
  inline ::ConfigReward::FetchProductWatchAdsItem* add_reward();
  inline const ::google::protobuf::RepeatedPtrField< ::ConfigReward::FetchProductWatchAdsItem >&
      reward() const;
  inline ::google::protobuf::RepeatedPtrField< ::ConfigReward::FetchProductWatchAdsItem >*
      mutable_reward();
  
  // @@protoc_insertion_point(class_scope:ConfigReward.FetchProductWatchAds)
 private:
  inline void set_has_mintime();
  inline void clear_has_mintime();
  inline void set_has_cd();
  inline void clear_has_cd();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint32 mintime_;
  ::google::protobuf::uint32 cd_;
  ::google::protobuf::RepeatedPtrField< ::ConfigReward::FetchProductWatchAdsItem > reward_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_ConfigReward_2eproto();
  friend void protobuf_AssignDesc_ConfigReward_2eproto();
  friend void protobuf_ShutdownFile_ConfigReward_2eproto();
  
  void InitAsDefaultInstance();
  static FetchProductWatchAds* default_instance_;
};
// -------------------------------------------------------------------

class RewardList : public ::google::protobuf::Message {
 public:
  RewardList();
  virtual ~RewardList();
  
  RewardList(const RewardList& from);
  
  inline RewardList& operator=(const RewardList& from) {
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
  static const RewardList& default_instance();
  
  void Swap(RewardList* other);
  
  // implements Message ----------------------------------------------
  
  RewardList* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RewardList& from);
  void MergeFrom(const RewardList& from);
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
  
  // required .ConfigReward.FirstRechargeRewardCPP firstRecharge = 1;
  inline bool has_firstrecharge() const;
  inline void clear_firstrecharge();
  static const int kFirstRechargeFieldNumber = 1;
  inline const ::ConfigReward::FirstRechargeRewardCPP& firstrecharge() const;
  inline ::ConfigReward::FirstRechargeRewardCPP* mutable_firstrecharge();
  inline ::ConfigReward::FirstRechargeRewardCPP* release_firstrecharge();
  
  // required .ConfigReward.FollowPublicRewardCPP followPublic = 2;
  inline bool has_followpublic() const;
  inline void clear_followpublic();
  static const int kFollowPublicFieldNumber = 2;
  inline const ::ConfigReward::FollowPublicRewardCPP& followpublic() const;
  inline ::ConfigReward::FollowPublicRewardCPP* mutable_followpublic();
  inline ::ConfigReward::FollowPublicRewardCPP* release_followpublic();
  
  // required .ConfigReward.FetchProductWatchAds fetchProductWatchAds = 3;
  inline bool has_fetchproductwatchads() const;
  inline void clear_fetchproductwatchads();
  static const int kFetchProductWatchAdsFieldNumber = 3;
  inline const ::ConfigReward::FetchProductWatchAds& fetchproductwatchads() const;
  inline ::ConfigReward::FetchProductWatchAds* mutable_fetchproductwatchads();
  inline ::ConfigReward::FetchProductWatchAds* release_fetchproductwatchads();
  
  // @@protoc_insertion_point(class_scope:ConfigReward.RewardList)
 private:
  inline void set_has_firstrecharge();
  inline void clear_has_firstrecharge();
  inline void set_has_followpublic();
  inline void clear_has_followpublic();
  inline void set_has_fetchproductwatchads();
  inline void clear_has_fetchproductwatchads();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::ConfigReward::FirstRechargeRewardCPP* firstrecharge_;
  ::ConfigReward::FollowPublicRewardCPP* followpublic_;
  ::ConfigReward::FetchProductWatchAds* fetchproductwatchads_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_ConfigReward_2eproto();
  friend void protobuf_AssignDesc_ConfigReward_2eproto();
  friend void protobuf_ShutdownFile_ConfigReward_2eproto();
  
  void InitAsDefaultInstance();
  static RewardList* default_instance_;
};
// ===================================================================


// ===================================================================

// FirstRechargeRewardCPP

// required .CommonGiftConfig.CommonModifyItem common = 1;
inline bool FirstRechargeRewardCPP::has_common() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void FirstRechargeRewardCPP::set_has_common() {
  _has_bits_[0] |= 0x00000001u;
}
inline void FirstRechargeRewardCPP::clear_has_common() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void FirstRechargeRewardCPP::clear_common() {
  if (common_ != NULL) common_->::CommonGiftConfig::CommonModifyItem::Clear();
  clear_has_common();
}
inline const ::CommonGiftConfig::CommonModifyItem& FirstRechargeRewardCPP::common() const {
  return common_ != NULL ? *common_ : *default_instance_->common_;
}
inline ::CommonGiftConfig::CommonModifyItem* FirstRechargeRewardCPP::mutable_common() {
  set_has_common();
  if (common_ == NULL) common_ = new ::CommonGiftConfig::CommonModifyItem;
  return common_;
}
inline ::CommonGiftConfig::CommonModifyItem* FirstRechargeRewardCPP::release_common() {
  clear_has_common();
  ::CommonGiftConfig::CommonModifyItem* temp = common_;
  common_ = NULL;
  return temp;
}

// -------------------------------------------------------------------

// FollowPublicRewardCPP

// required .CommonGiftConfig.CommonModifyItem common = 1;
inline bool FollowPublicRewardCPP::has_common() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void FollowPublicRewardCPP::set_has_common() {
  _has_bits_[0] |= 0x00000001u;
}
inline void FollowPublicRewardCPP::clear_has_common() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void FollowPublicRewardCPP::clear_common() {
  if (common_ != NULL) common_->::CommonGiftConfig::CommonModifyItem::Clear();
  clear_has_common();
}
inline const ::CommonGiftConfig::CommonModifyItem& FollowPublicRewardCPP::common() const {
  return common_ != NULL ? *common_ : *default_instance_->common_;
}
inline ::CommonGiftConfig::CommonModifyItem* FollowPublicRewardCPP::mutable_common() {
  set_has_common();
  if (common_ == NULL) common_ = new ::CommonGiftConfig::CommonModifyItem;
  return common_;
}
inline ::CommonGiftConfig::CommonModifyItem* FollowPublicRewardCPP::release_common() {
  clear_has_common();
  ::CommonGiftConfig::CommonModifyItem* temp = common_;
  common_ = NULL;
  return temp;
}

// -------------------------------------------------------------------

// FetchProductWatchAdsItem

// required uint32 id = 1;
inline bool FetchProductWatchAdsItem::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void FetchProductWatchAdsItem::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void FetchProductWatchAdsItem::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void FetchProductWatchAdsItem::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 FetchProductWatchAdsItem::id() const {
  return id_;
}
inline void FetchProductWatchAdsItem::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// required uint32 rate = 2;
inline bool FetchProductWatchAdsItem::has_rate() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void FetchProductWatchAdsItem::set_has_rate() {
  _has_bits_[0] |= 0x00000002u;
}
inline void FetchProductWatchAdsItem::clear_has_rate() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void FetchProductWatchAdsItem::clear_rate() {
  rate_ = 0u;
  clear_has_rate();
}
inline ::google::protobuf::uint32 FetchProductWatchAdsItem::rate() const {
  return rate_;
}
inline void FetchProductWatchAdsItem::set_rate(::google::protobuf::uint32 value) {
  set_has_rate();
  rate_ = value;
}

// required uint32 count = 3;
inline bool FetchProductWatchAdsItem::has_count() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void FetchProductWatchAdsItem::set_has_count() {
  _has_bits_[0] |= 0x00000004u;
}
inline void FetchProductWatchAdsItem::clear_has_count() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void FetchProductWatchAdsItem::clear_count() {
  count_ = 0u;
  clear_has_count();
}
inline ::google::protobuf::uint32 FetchProductWatchAdsItem::count() const {
  return count_;
}
inline void FetchProductWatchAdsItem::set_count(::google::protobuf::uint32 value) {
  set_has_count();
  count_ = value;
}

// -------------------------------------------------------------------

// FetchProductWatchAds

// required uint32 minTime = 1;
inline bool FetchProductWatchAds::has_mintime() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void FetchProductWatchAds::set_has_mintime() {
  _has_bits_[0] |= 0x00000001u;
}
inline void FetchProductWatchAds::clear_has_mintime() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void FetchProductWatchAds::clear_mintime() {
  mintime_ = 0u;
  clear_has_mintime();
}
inline ::google::protobuf::uint32 FetchProductWatchAds::mintime() const {
  return mintime_;
}
inline void FetchProductWatchAds::set_mintime(::google::protobuf::uint32 value) {
  set_has_mintime();
  mintime_ = value;
}

// required uint32 cd = 2;
inline bool FetchProductWatchAds::has_cd() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void FetchProductWatchAds::set_has_cd() {
  _has_bits_[0] |= 0x00000002u;
}
inline void FetchProductWatchAds::clear_has_cd() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void FetchProductWatchAds::clear_cd() {
  cd_ = 0u;
  clear_has_cd();
}
inline ::google::protobuf::uint32 FetchProductWatchAds::cd() const {
  return cd_;
}
inline void FetchProductWatchAds::set_cd(::google::protobuf::uint32 value) {
  set_has_cd();
  cd_ = value;
}

// repeated .ConfigReward.FetchProductWatchAdsItem reward = 3;
inline int FetchProductWatchAds::reward_size() const {
  return reward_.size();
}
inline void FetchProductWatchAds::clear_reward() {
  reward_.Clear();
}
inline const ::ConfigReward::FetchProductWatchAdsItem& FetchProductWatchAds::reward(int index) const {
  return reward_.Get(index);
}
inline ::ConfigReward::FetchProductWatchAdsItem* FetchProductWatchAds::mutable_reward(int index) {
  return reward_.Mutable(index);
}
inline ::ConfigReward::FetchProductWatchAdsItem* FetchProductWatchAds::add_reward() {
  return reward_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ConfigReward::FetchProductWatchAdsItem >&
FetchProductWatchAds::reward() const {
  return reward_;
}
inline ::google::protobuf::RepeatedPtrField< ::ConfigReward::FetchProductWatchAdsItem >*
FetchProductWatchAds::mutable_reward() {
  return &reward_;
}

// -------------------------------------------------------------------

// RewardList

// required .ConfigReward.FirstRechargeRewardCPP firstRecharge = 1;
inline bool RewardList::has_firstrecharge() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RewardList::set_has_firstrecharge() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RewardList::clear_has_firstrecharge() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RewardList::clear_firstrecharge() {
  if (firstrecharge_ != NULL) firstrecharge_->::ConfigReward::FirstRechargeRewardCPP::Clear();
  clear_has_firstrecharge();
}
inline const ::ConfigReward::FirstRechargeRewardCPP& RewardList::firstrecharge() const {
  return firstrecharge_ != NULL ? *firstrecharge_ : *default_instance_->firstrecharge_;
}
inline ::ConfigReward::FirstRechargeRewardCPP* RewardList::mutable_firstrecharge() {
  set_has_firstrecharge();
  if (firstrecharge_ == NULL) firstrecharge_ = new ::ConfigReward::FirstRechargeRewardCPP;
  return firstrecharge_;
}
inline ::ConfigReward::FirstRechargeRewardCPP* RewardList::release_firstrecharge() {
  clear_has_firstrecharge();
  ::ConfigReward::FirstRechargeRewardCPP* temp = firstrecharge_;
  firstrecharge_ = NULL;
  return temp;
}

// required .ConfigReward.FollowPublicRewardCPP followPublic = 2;
inline bool RewardList::has_followpublic() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void RewardList::set_has_followpublic() {
  _has_bits_[0] |= 0x00000002u;
}
inline void RewardList::clear_has_followpublic() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void RewardList::clear_followpublic() {
  if (followpublic_ != NULL) followpublic_->::ConfigReward::FollowPublicRewardCPP::Clear();
  clear_has_followpublic();
}
inline const ::ConfigReward::FollowPublicRewardCPP& RewardList::followpublic() const {
  return followpublic_ != NULL ? *followpublic_ : *default_instance_->followpublic_;
}
inline ::ConfigReward::FollowPublicRewardCPP* RewardList::mutable_followpublic() {
  set_has_followpublic();
  if (followpublic_ == NULL) followpublic_ = new ::ConfigReward::FollowPublicRewardCPP;
  return followpublic_;
}
inline ::ConfigReward::FollowPublicRewardCPP* RewardList::release_followpublic() {
  clear_has_followpublic();
  ::ConfigReward::FollowPublicRewardCPP* temp = followpublic_;
  followpublic_ = NULL;
  return temp;
}

// required .ConfigReward.FetchProductWatchAds fetchProductWatchAds = 3;
inline bool RewardList::has_fetchproductwatchads() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void RewardList::set_has_fetchproductwatchads() {
  _has_bits_[0] |= 0x00000004u;
}
inline void RewardList::clear_has_fetchproductwatchads() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void RewardList::clear_fetchproductwatchads() {
  if (fetchproductwatchads_ != NULL) fetchproductwatchads_->::ConfigReward::FetchProductWatchAds::Clear();
  clear_has_fetchproductwatchads();
}
inline const ::ConfigReward::FetchProductWatchAds& RewardList::fetchproductwatchads() const {
  return fetchproductwatchads_ != NULL ? *fetchproductwatchads_ : *default_instance_->fetchproductwatchads_;
}
inline ::ConfigReward::FetchProductWatchAds* RewardList::mutable_fetchproductwatchads() {
  set_has_fetchproductwatchads();
  if (fetchproductwatchads_ == NULL) fetchproductwatchads_ = new ::ConfigReward::FetchProductWatchAds;
  return fetchproductwatchads_;
}
inline ::ConfigReward::FetchProductWatchAds* RewardList::release_fetchproductwatchads() {
  clear_has_fetchproductwatchads();
  ::ConfigReward::FetchProductWatchAds* temp = fetchproductwatchads_;
  fetchproductwatchads_ = NULL;
  return temp;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ConfigReward

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ConfigReward_2eproto__INCLUDED
