// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: AchievementConfig.proto

#ifndef PROTOBUF_AchievementConfig_2eproto__INCLUDED
#define PROTOBUF_AchievementConfig_2eproto__INCLUDED

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

namespace AchievementConfig {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_AchievementConfig_2eproto();
void protobuf_AssignDesc_AchievementConfig_2eproto();
void protobuf_ShutdownFile_AchievementConfig_2eproto();

class Achievement;
class AchievementList;

// ===================================================================

class Achievement : public ::google::protobuf::Message {
 public:
  Achievement();
  virtual ~Achievement();

  Achievement(const Achievement& from);

  inline Achievement& operator=(const Achievement& from) {
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
  static const Achievement& default_instance();

  void Swap(Achievement* other);

  // implements Message ----------------------------------------------

  Achievement* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Achievement& from);
  void MergeFrom(const Achievement& from);
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

  // required uint32 achitype = 2;
  inline bool has_achitype() const;
  inline void clear_achitype();
  static const int kAchitypeFieldNumber = 2;
  inline ::google::protobuf::uint32 achitype() const;
  inline void set_achitype(::google::protobuf::uint32 value);

  // required uint32 type = 3;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 3;
  inline ::google::protobuf::uint32 type() const;
  inline void set_type(::google::protobuf::uint32 value);

  // optional uint32 subtype = 4;
  inline bool has_subtype() const;
  inline void clear_subtype();
  static const int kSubtypeFieldNumber = 4;
  inline ::google::protobuf::uint32 subtype() const;
  inline void set_subtype(::google::protobuf::uint32 value);

  // repeated uint32 condition = 5;
  inline int condition_size() const;
  inline void clear_condition();
  static const int kConditionFieldNumber = 5;
  inline ::google::protobuf::uint32 condition(int index) const;
  inline void set_condition(int index, ::google::protobuf::uint32 value);
  inline void add_condition(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      condition() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_condition();

  // repeated .RewardConfig.Reward reward = 6;
  inline int reward_size() const;
  inline void clear_reward();
  static const int kRewardFieldNumber = 6;
  inline const ::RewardConfig::Reward& reward(int index) const;
  inline ::RewardConfig::Reward* mutable_reward(int index);
  inline ::RewardConfig::Reward* add_reward();
  inline const ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward >&
      reward() const;
  inline ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward >*
      mutable_reward();

  // @@protoc_insertion_point(class_scope:AchievementConfig.Achievement)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_achitype();
  inline void clear_has_achitype();
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_subtype();
  inline void clear_has_subtype();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 achitype_;
  ::google::protobuf::uint32 type_;
  ::google::protobuf::uint32 subtype_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > condition_;
  ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward > reward_;
  friend void  protobuf_AddDesc_AchievementConfig_2eproto();
  friend void protobuf_AssignDesc_AchievementConfig_2eproto();
  friend void protobuf_ShutdownFile_AchievementConfig_2eproto();

  void InitAsDefaultInstance();
  static Achievement* default_instance_;
};
// -------------------------------------------------------------------

class AchievementList : public ::google::protobuf::Message {
 public:
  AchievementList();
  virtual ~AchievementList();

  AchievementList(const AchievementList& from);

  inline AchievementList& operator=(const AchievementList& from) {
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
  static const AchievementList& default_instance();

  void Swap(AchievementList* other);

  // implements Message ----------------------------------------------

  AchievementList* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AchievementList& from);
  void MergeFrom(const AchievementList& from);
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

  // repeated .AchievementConfig.Achievement achievements = 1;
  inline int achievements_size() const;
  inline void clear_achievements();
  static const int kAchievementsFieldNumber = 1;
  inline const ::AchievementConfig::Achievement& achievements(int index) const;
  inline ::AchievementConfig::Achievement* mutable_achievements(int index);
  inline ::AchievementConfig::Achievement* add_achievements();
  inline const ::google::protobuf::RepeatedPtrField< ::AchievementConfig::Achievement >&
      achievements() const;
  inline ::google::protobuf::RepeatedPtrField< ::AchievementConfig::Achievement >*
      mutable_achievements();

  // @@protoc_insertion_point(class_scope:AchievementConfig.AchievementList)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::AchievementConfig::Achievement > achievements_;
  friend void  protobuf_AddDesc_AchievementConfig_2eproto();
  friend void protobuf_AssignDesc_AchievementConfig_2eproto();
  friend void protobuf_ShutdownFile_AchievementConfig_2eproto();

  void InitAsDefaultInstance();
  static AchievementList* default_instance_;
};
// ===================================================================


// ===================================================================

// Achievement

// required uint32 id = 1;
inline bool Achievement::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Achievement::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Achievement::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Achievement::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 Achievement::id() const {
  // @@protoc_insertion_point(field_get:AchievementConfig.Achievement.id)
  return id_;
}
inline void Achievement::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:AchievementConfig.Achievement.id)
}

// required uint32 achitype = 2;
inline bool Achievement::has_achitype() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Achievement::set_has_achitype() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Achievement::clear_has_achitype() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Achievement::clear_achitype() {
  achitype_ = 0u;
  clear_has_achitype();
}
inline ::google::protobuf::uint32 Achievement::achitype() const {
  // @@protoc_insertion_point(field_get:AchievementConfig.Achievement.achitype)
  return achitype_;
}
inline void Achievement::set_achitype(::google::protobuf::uint32 value) {
  set_has_achitype();
  achitype_ = value;
  // @@protoc_insertion_point(field_set:AchievementConfig.Achievement.achitype)
}

// required uint32 type = 3;
inline bool Achievement::has_type() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Achievement::set_has_type() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Achievement::clear_has_type() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Achievement::clear_type() {
  type_ = 0u;
  clear_has_type();
}
inline ::google::protobuf::uint32 Achievement::type() const {
  // @@protoc_insertion_point(field_get:AchievementConfig.Achievement.type)
  return type_;
}
inline void Achievement::set_type(::google::protobuf::uint32 value) {
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:AchievementConfig.Achievement.type)
}

// optional uint32 subtype = 4;
inline bool Achievement::has_subtype() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Achievement::set_has_subtype() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Achievement::clear_has_subtype() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Achievement::clear_subtype() {
  subtype_ = 0u;
  clear_has_subtype();
}
inline ::google::protobuf::uint32 Achievement::subtype() const {
  // @@protoc_insertion_point(field_get:AchievementConfig.Achievement.subtype)
  return subtype_;
}
inline void Achievement::set_subtype(::google::protobuf::uint32 value) {
  set_has_subtype();
  subtype_ = value;
  // @@protoc_insertion_point(field_set:AchievementConfig.Achievement.subtype)
}

// repeated uint32 condition = 5;
inline int Achievement::condition_size() const {
  return condition_.size();
}
inline void Achievement::clear_condition() {
  condition_.Clear();
}
inline ::google::protobuf::uint32 Achievement::condition(int index) const {
  // @@protoc_insertion_point(field_get:AchievementConfig.Achievement.condition)
  return condition_.Get(index);
}
inline void Achievement::set_condition(int index, ::google::protobuf::uint32 value) {
  condition_.Set(index, value);
  // @@protoc_insertion_point(field_set:AchievementConfig.Achievement.condition)
}
inline void Achievement::add_condition(::google::protobuf::uint32 value) {
  condition_.Add(value);
  // @@protoc_insertion_point(field_add:AchievementConfig.Achievement.condition)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
Achievement::condition() const {
  // @@protoc_insertion_point(field_list:AchievementConfig.Achievement.condition)
  return condition_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
Achievement::mutable_condition() {
  // @@protoc_insertion_point(field_mutable_list:AchievementConfig.Achievement.condition)
  return &condition_;
}

// repeated .RewardConfig.Reward reward = 6;
inline int Achievement::reward_size() const {
  return reward_.size();
}
inline void Achievement::clear_reward() {
  reward_.Clear();
}
inline const ::RewardConfig::Reward& Achievement::reward(int index) const {
  // @@protoc_insertion_point(field_get:AchievementConfig.Achievement.reward)
  return reward_.Get(index);
}
inline ::RewardConfig::Reward* Achievement::mutable_reward(int index) {
  // @@protoc_insertion_point(field_mutable:AchievementConfig.Achievement.reward)
  return reward_.Mutable(index);
}
inline ::RewardConfig::Reward* Achievement::add_reward() {
  // @@protoc_insertion_point(field_add:AchievementConfig.Achievement.reward)
  return reward_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward >&
Achievement::reward() const {
  // @@protoc_insertion_point(field_list:AchievementConfig.Achievement.reward)
  return reward_;
}
inline ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward >*
Achievement::mutable_reward() {
  // @@protoc_insertion_point(field_mutable_list:AchievementConfig.Achievement.reward)
  return &reward_;
}

// -------------------------------------------------------------------

// AchievementList

// repeated .AchievementConfig.Achievement achievements = 1;
inline int AchievementList::achievements_size() const {
  return achievements_.size();
}
inline void AchievementList::clear_achievements() {
  achievements_.Clear();
}
inline const ::AchievementConfig::Achievement& AchievementList::achievements(int index) const {
  // @@protoc_insertion_point(field_get:AchievementConfig.AchievementList.achievements)
  return achievements_.Get(index);
}
inline ::AchievementConfig::Achievement* AchievementList::mutable_achievements(int index) {
  // @@protoc_insertion_point(field_mutable:AchievementConfig.AchievementList.achievements)
  return achievements_.Mutable(index);
}
inline ::AchievementConfig::Achievement* AchievementList::add_achievements() {
  // @@protoc_insertion_point(field_add:AchievementConfig.AchievementList.achievements)
  return achievements_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::AchievementConfig::Achievement >&
AchievementList::achievements() const {
  // @@protoc_insertion_point(field_list:AchievementConfig.AchievementList.achievements)
  return achievements_;
}
inline ::google::protobuf::RepeatedPtrField< ::AchievementConfig::Achievement >*
AchievementList::mutable_achievements() {
  // @@protoc_insertion_point(field_mutable_list:AchievementConfig.AchievementList.achievements)
  return &achievements_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace AchievementConfig

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_AchievementConfig_2eproto__INCLUDED
