// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: FriendConfig.proto

#ifndef PROTOBUF_FriendConfig_2eproto__INCLUDED
#define PROTOBUF_FriendConfig_2eproto__INCLUDED

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

namespace FriendConfig {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_FriendConfig_2eproto();
void protobuf_AssignDesc_FriendConfig_2eproto();
void protobuf_ShutdownFile_FriendConfig_2eproto();

class LevelReward;
class FriendInfo;

// ===================================================================

class LevelReward : public ::google::protobuf::Message {
 public:
  LevelReward();
  virtual ~LevelReward();
  
  LevelReward(const LevelReward& from);
  
  inline LevelReward& operator=(const LevelReward& from) {
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
  static const LevelReward& default_instance();
  
  void Swap(LevelReward* other);
  
  // implements Message ----------------------------------------------
  
  LevelReward* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const LevelReward& from);
  void MergeFrom(const LevelReward& from);
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
  
  // required uint32 level = 1;
  inline bool has_level() const;
  inline void clear_level();
  static const int kLevelFieldNumber = 1;
  inline ::google::protobuf::uint32 level() const;
  inline void set_level(::google::protobuf::uint32 value);
  
  // required uint32 heroExp = 2;
  inline bool has_heroexp() const;
  inline void clear_heroexp();
  static const int kHeroExpFieldNumber = 2;
  inline ::google::protobuf::uint32 heroexp() const;
  inline void set_heroexp(::google::protobuf::uint32 value);
  
  // required .CommonGiftConfig.CommonModifyItem reward = 3;
  inline bool has_reward() const;
  inline void clear_reward();
  static const int kRewardFieldNumber = 3;
  inline const ::CommonGiftConfig::CommonModifyItem& reward() const;
  inline ::CommonGiftConfig::CommonModifyItem* mutable_reward();
  inline ::CommonGiftConfig::CommonModifyItem* release_reward();
  
  // @@protoc_insertion_point(class_scope:FriendConfig.LevelReward)
 private:
  inline void set_has_level();
  inline void clear_has_level();
  inline void set_has_heroexp();
  inline void clear_has_heroexp();
  inline void set_has_reward();
  inline void clear_has_reward();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint32 level_;
  ::google::protobuf::uint32 heroexp_;
  ::CommonGiftConfig::CommonModifyItem* reward_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_FriendConfig_2eproto();
  friend void protobuf_AssignDesc_FriendConfig_2eproto();
  friend void protobuf_ShutdownFile_FriendConfig_2eproto();
  
  void InitAsDefaultInstance();
  static LevelReward* default_instance_;
};
// -------------------------------------------------------------------

class FriendInfo : public ::google::protobuf::Message {
 public:
  FriendInfo();
  virtual ~FriendInfo();
  
  FriendInfo(const FriendInfo& from);
  
  inline FriendInfo& operator=(const FriendInfo& from) {
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
  static const FriendInfo& default_instance();
  
  void Swap(FriendInfo* other);
  
  // implements Message ----------------------------------------------
  
  FriendInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const FriendInfo& from);
  void MergeFrom(const FriendInfo& from);
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
  
  // repeated .FriendConfig.LevelReward rewards = 1;
  inline int rewards_size() const;
  inline void clear_rewards();
  static const int kRewardsFieldNumber = 1;
  inline const ::FriendConfig::LevelReward& rewards(int index) const;
  inline ::FriendConfig::LevelReward* mutable_rewards(int index);
  inline ::FriendConfig::LevelReward* add_rewards();
  inline const ::google::protobuf::RepeatedPtrField< ::FriendConfig::LevelReward >&
      rewards() const;
  inline ::google::protobuf::RepeatedPtrField< ::FriendConfig::LevelReward >*
      mutable_rewards();
  
  // @@protoc_insertion_point(class_scope:FriendConfig.FriendInfo)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::FriendConfig::LevelReward > rewards_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_FriendConfig_2eproto();
  friend void protobuf_AssignDesc_FriendConfig_2eproto();
  friend void protobuf_ShutdownFile_FriendConfig_2eproto();
  
  void InitAsDefaultInstance();
  static FriendInfo* default_instance_;
};
// ===================================================================


// ===================================================================

// LevelReward

// required uint32 level = 1;
inline bool LevelReward::has_level() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void LevelReward::set_has_level() {
  _has_bits_[0] |= 0x00000001u;
}
inline void LevelReward::clear_has_level() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void LevelReward::clear_level() {
  level_ = 0u;
  clear_has_level();
}
inline ::google::protobuf::uint32 LevelReward::level() const {
  return level_;
}
inline void LevelReward::set_level(::google::protobuf::uint32 value) {
  set_has_level();
  level_ = value;
}

// required uint32 heroExp = 2;
inline bool LevelReward::has_heroexp() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void LevelReward::set_has_heroexp() {
  _has_bits_[0] |= 0x00000002u;
}
inline void LevelReward::clear_has_heroexp() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void LevelReward::clear_heroexp() {
  heroexp_ = 0u;
  clear_has_heroexp();
}
inline ::google::protobuf::uint32 LevelReward::heroexp() const {
  return heroexp_;
}
inline void LevelReward::set_heroexp(::google::protobuf::uint32 value) {
  set_has_heroexp();
  heroexp_ = value;
}

// required .CommonGiftConfig.CommonModifyItem reward = 3;
inline bool LevelReward::has_reward() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void LevelReward::set_has_reward() {
  _has_bits_[0] |= 0x00000004u;
}
inline void LevelReward::clear_has_reward() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void LevelReward::clear_reward() {
  if (reward_ != NULL) reward_->::CommonGiftConfig::CommonModifyItem::Clear();
  clear_has_reward();
}
inline const ::CommonGiftConfig::CommonModifyItem& LevelReward::reward() const {
  return reward_ != NULL ? *reward_ : *default_instance_->reward_;
}
inline ::CommonGiftConfig::CommonModifyItem* LevelReward::mutable_reward() {
  set_has_reward();
  if (reward_ == NULL) reward_ = new ::CommonGiftConfig::CommonModifyItem;
  return reward_;
}
inline ::CommonGiftConfig::CommonModifyItem* LevelReward::release_reward() {
  clear_has_reward();
  ::CommonGiftConfig::CommonModifyItem* temp = reward_;
  reward_ = NULL;
  return temp;
}

// -------------------------------------------------------------------

// FriendInfo

// repeated .FriendConfig.LevelReward rewards = 1;
inline int FriendInfo::rewards_size() const {
  return rewards_.size();
}
inline void FriendInfo::clear_rewards() {
  rewards_.Clear();
}
inline const ::FriendConfig::LevelReward& FriendInfo::rewards(int index) const {
  return rewards_.Get(index);
}
inline ::FriendConfig::LevelReward* FriendInfo::mutable_rewards(int index) {
  return rewards_.Mutable(index);
}
inline ::FriendConfig::LevelReward* FriendInfo::add_rewards() {
  return rewards_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::FriendConfig::LevelReward >&
FriendInfo::rewards() const {
  return rewards_;
}
inline ::google::protobuf::RepeatedPtrField< ::FriendConfig::LevelReward >*
FriendInfo::mutable_rewards() {
  return &rewards_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace FriendConfig

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_FriendConfig_2eproto__INCLUDED
