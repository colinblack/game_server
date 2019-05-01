// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: LittleChargeConfig.proto

#ifndef PROTOBUF_LittleChargeConfig_2eproto__INCLUDED
#define PROTOBUF_LittleChargeConfig_2eproto__INCLUDED

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

namespace LittleChargeConfig {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_LittleChargeConfig_2eproto();
void protobuf_AssignDesc_LittleChargeConfig_2eproto();
void protobuf_ShutdownFile_LittleChargeConfig_2eproto();

class OpenPlatFormReward;
class LittleCharge;

// ===================================================================

class OpenPlatFormReward : public ::google::protobuf::Message {
 public:
  OpenPlatFormReward();
  virtual ~OpenPlatFormReward();

  OpenPlatFormReward(const OpenPlatFormReward& from);

  inline OpenPlatFormReward& operator=(const OpenPlatFormReward& from) {
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
  static const OpenPlatFormReward& default_instance();

  void Swap(OpenPlatFormReward* other);

  // implements Message ----------------------------------------------

  OpenPlatFormReward* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const OpenPlatFormReward& from);
  void MergeFrom(const OpenPlatFormReward& from);
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

  // required uint32 startday = 1;
  inline bool has_startday() const;
  inline void clear_startday();
  static const int kStartdayFieldNumber = 1;
  inline ::google::protobuf::uint32 startday() const;
  inline void set_startday(::google::protobuf::uint32 value);

  // repeated .RewardConfig.Reward reward = 2;
  inline int reward_size() const;
  inline void clear_reward();
  static const int kRewardFieldNumber = 2;
  inline const ::RewardConfig::Reward& reward(int index) const;
  inline ::RewardConfig::Reward* mutable_reward(int index);
  inline ::RewardConfig::Reward* add_reward();
  inline const ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward >&
      reward() const;
  inline ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward >*
      mutable_reward();

  // @@protoc_insertion_point(class_scope:LittleChargeConfig.OpenPlatFormReward)
 private:
  inline void set_has_startday();
  inline void clear_has_startday();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward > reward_;
  ::google::protobuf::uint32 startday_;
  friend void  protobuf_AddDesc_LittleChargeConfig_2eproto();
  friend void protobuf_AssignDesc_LittleChargeConfig_2eproto();
  friend void protobuf_ShutdownFile_LittleChargeConfig_2eproto();

  void InitAsDefaultInstance();
  static OpenPlatFormReward* default_instance_;
};
// -------------------------------------------------------------------

class LittleCharge : public ::google::protobuf::Message {
 public:
  LittleCharge();
  virtual ~LittleCharge();

  LittleCharge(const LittleCharge& from);

  inline LittleCharge& operator=(const LittleCharge& from) {
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
  static const LittleCharge& default_instance();

  void Swap(LittleCharge* other);

  // implements Message ----------------------------------------------

  LittleCharge* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const LittleCharge& from);
  void MergeFrom(const LittleCharge& from);
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

  // required uint32 condition = 1;
  inline bool has_condition() const;
  inline void clear_condition();
  static const int kConditionFieldNumber = 1;
  inline ::google::protobuf::uint32 condition() const;
  inline void set_condition(::google::protobuf::uint32 value);

  // repeated .LittleChargeConfig.OpenPlatFormReward open_platform = 2;
  inline int open_platform_size() const;
  inline void clear_open_platform();
  static const int kOpenPlatformFieldNumber = 2;
  inline const ::LittleChargeConfig::OpenPlatFormReward& open_platform(int index) const;
  inline ::LittleChargeConfig::OpenPlatFormReward* mutable_open_platform(int index);
  inline ::LittleChargeConfig::OpenPlatFormReward* add_open_platform();
  inline const ::google::protobuf::RepeatedPtrField< ::LittleChargeConfig::OpenPlatFormReward >&
      open_platform() const;
  inline ::google::protobuf::RepeatedPtrField< ::LittleChargeConfig::OpenPlatFormReward >*
      mutable_open_platform();

  // @@protoc_insertion_point(class_scope:LittleChargeConfig.LittleCharge)
 private:
  inline void set_has_condition();
  inline void clear_has_condition();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::LittleChargeConfig::OpenPlatFormReward > open_platform_;
  ::google::protobuf::uint32 condition_;
  friend void  protobuf_AddDesc_LittleChargeConfig_2eproto();
  friend void protobuf_AssignDesc_LittleChargeConfig_2eproto();
  friend void protobuf_ShutdownFile_LittleChargeConfig_2eproto();

  void InitAsDefaultInstance();
  static LittleCharge* default_instance_;
};
// ===================================================================


// ===================================================================

// OpenPlatFormReward

// required uint32 startday = 1;
inline bool OpenPlatFormReward::has_startday() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void OpenPlatFormReward::set_has_startday() {
  _has_bits_[0] |= 0x00000001u;
}
inline void OpenPlatFormReward::clear_has_startday() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void OpenPlatFormReward::clear_startday() {
  startday_ = 0u;
  clear_has_startday();
}
inline ::google::protobuf::uint32 OpenPlatFormReward::startday() const {
  // @@protoc_insertion_point(field_get:LittleChargeConfig.OpenPlatFormReward.startday)
  return startday_;
}
inline void OpenPlatFormReward::set_startday(::google::protobuf::uint32 value) {
  set_has_startday();
  startday_ = value;
  // @@protoc_insertion_point(field_set:LittleChargeConfig.OpenPlatFormReward.startday)
}

// repeated .RewardConfig.Reward reward = 2;
inline int OpenPlatFormReward::reward_size() const {
  return reward_.size();
}
inline void OpenPlatFormReward::clear_reward() {
  reward_.Clear();
}
inline const ::RewardConfig::Reward& OpenPlatFormReward::reward(int index) const {
  // @@protoc_insertion_point(field_get:LittleChargeConfig.OpenPlatFormReward.reward)
  return reward_.Get(index);
}
inline ::RewardConfig::Reward* OpenPlatFormReward::mutable_reward(int index) {
  // @@protoc_insertion_point(field_mutable:LittleChargeConfig.OpenPlatFormReward.reward)
  return reward_.Mutable(index);
}
inline ::RewardConfig::Reward* OpenPlatFormReward::add_reward() {
  // @@protoc_insertion_point(field_add:LittleChargeConfig.OpenPlatFormReward.reward)
  return reward_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward >&
OpenPlatFormReward::reward() const {
  // @@protoc_insertion_point(field_list:LittleChargeConfig.OpenPlatFormReward.reward)
  return reward_;
}
inline ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward >*
OpenPlatFormReward::mutable_reward() {
  // @@protoc_insertion_point(field_mutable_list:LittleChargeConfig.OpenPlatFormReward.reward)
  return &reward_;
}

// -------------------------------------------------------------------

// LittleCharge

// required uint32 condition = 1;
inline bool LittleCharge::has_condition() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void LittleCharge::set_has_condition() {
  _has_bits_[0] |= 0x00000001u;
}
inline void LittleCharge::clear_has_condition() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void LittleCharge::clear_condition() {
  condition_ = 0u;
  clear_has_condition();
}
inline ::google::protobuf::uint32 LittleCharge::condition() const {
  // @@protoc_insertion_point(field_get:LittleChargeConfig.LittleCharge.condition)
  return condition_;
}
inline void LittleCharge::set_condition(::google::protobuf::uint32 value) {
  set_has_condition();
  condition_ = value;
  // @@protoc_insertion_point(field_set:LittleChargeConfig.LittleCharge.condition)
}

// repeated .LittleChargeConfig.OpenPlatFormReward open_platform = 2;
inline int LittleCharge::open_platform_size() const {
  return open_platform_.size();
}
inline void LittleCharge::clear_open_platform() {
  open_platform_.Clear();
}
inline const ::LittleChargeConfig::OpenPlatFormReward& LittleCharge::open_platform(int index) const {
  // @@protoc_insertion_point(field_get:LittleChargeConfig.LittleCharge.open_platform)
  return open_platform_.Get(index);
}
inline ::LittleChargeConfig::OpenPlatFormReward* LittleCharge::mutable_open_platform(int index) {
  // @@protoc_insertion_point(field_mutable:LittleChargeConfig.LittleCharge.open_platform)
  return open_platform_.Mutable(index);
}
inline ::LittleChargeConfig::OpenPlatFormReward* LittleCharge::add_open_platform() {
  // @@protoc_insertion_point(field_add:LittleChargeConfig.LittleCharge.open_platform)
  return open_platform_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::LittleChargeConfig::OpenPlatFormReward >&
LittleCharge::open_platform() const {
  // @@protoc_insertion_point(field_list:LittleChargeConfig.LittleCharge.open_platform)
  return open_platform_;
}
inline ::google::protobuf::RepeatedPtrField< ::LittleChargeConfig::OpenPlatFormReward >*
LittleCharge::mutable_open_platform() {
  // @@protoc_insertion_point(field_mutable_list:LittleChargeConfig.LittleCharge.open_platform)
  return &open_platform_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace LittleChargeConfig

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_LittleChargeConfig_2eproto__INCLUDED
