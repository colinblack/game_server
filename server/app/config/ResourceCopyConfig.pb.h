// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ResourceCopyConfig.proto

#ifndef PROTOBUF_ResourceCopyConfig_2eproto__INCLUDED
#define PROTOBUF_ResourceCopyConfig_2eproto__INCLUDED

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

namespace ResourceCopyConfig {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ResourceCopyConfig_2eproto();
void protobuf_AssignDesc_ResourceCopyConfig_2eproto();
void protobuf_ShutdownFile_ResourceCopyConfig_2eproto();

class ResourceCopy;
class ResourceCopyAll;

// ===================================================================

class ResourceCopy : public ::google::protobuf::Message {
 public:
  ResourceCopy();
  virtual ~ResourceCopy();

  ResourceCopy(const ResourceCopy& from);

  inline ResourceCopy& operator=(const ResourceCopy& from) {
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
  static const ResourceCopy& default_instance();

  void Swap(ResourceCopy* other);

  // implements Message ----------------------------------------------

  ResourceCopy* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ResourceCopy& from);
  void MergeFrom(const ResourceCopy& from);
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

  // required uint32 gateid = 2;
  inline bool has_gateid() const;
  inline void clear_gateid();
  static const int kGateidFieldNumber = 2;
  inline ::google::protobuf::uint32 gateid() const;
  inline void set_gateid(::google::protobuf::uint32 value);

  // required uint32 viplevel = 3;
  inline bool has_viplevel() const;
  inline void clear_viplevel();
  static const int kViplevelFieldNumber = 3;
  inline ::google::protobuf::uint32 viplevel() const;
  inline void set_viplevel(::google::protobuf::uint32 value);

  // required uint32 timeslimit = 4;
  inline bool has_timeslimit() const;
  inline void clear_timeslimit();
  static const int kTimeslimitFieldNumber = 4;
  inline ::google::protobuf::uint32 timeslimit() const;
  inline void set_timeslimit(::google::protobuf::uint32 value);

  // repeated uint32 cash = 5;
  inline int cash_size() const;
  inline void clear_cash();
  static const int kCashFieldNumber = 5;
  inline ::google::protobuf::uint32 cash(int index) const;
  inline void set_cash(int index, ::google::protobuf::uint32 value);
  inline void add_cash(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      cash() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_cash();

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

  // @@protoc_insertion_point(class_scope:ResourceCopyConfig.ResourceCopy)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_gateid();
  inline void clear_has_gateid();
  inline void set_has_viplevel();
  inline void clear_has_viplevel();
  inline void set_has_timeslimit();
  inline void clear_has_timeslimit();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 gateid_;
  ::google::protobuf::uint32 viplevel_;
  ::google::protobuf::uint32 timeslimit_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > cash_;
  ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward > reward_;
  friend void  protobuf_AddDesc_ResourceCopyConfig_2eproto();
  friend void protobuf_AssignDesc_ResourceCopyConfig_2eproto();
  friend void protobuf_ShutdownFile_ResourceCopyConfig_2eproto();

  void InitAsDefaultInstance();
  static ResourceCopy* default_instance_;
};
// -------------------------------------------------------------------

class ResourceCopyAll : public ::google::protobuf::Message {
 public:
  ResourceCopyAll();
  virtual ~ResourceCopyAll();

  ResourceCopyAll(const ResourceCopyAll& from);

  inline ResourceCopyAll& operator=(const ResourceCopyAll& from) {
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
  static const ResourceCopyAll& default_instance();

  void Swap(ResourceCopyAll* other);

  // implements Message ----------------------------------------------

  ResourceCopyAll* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ResourceCopyAll& from);
  void MergeFrom(const ResourceCopyAll& from);
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

  // repeated .ResourceCopyConfig.ResourceCopy resource_copies = 1;
  inline int resource_copies_size() const;
  inline void clear_resource_copies();
  static const int kResourceCopiesFieldNumber = 1;
  inline const ::ResourceCopyConfig::ResourceCopy& resource_copies(int index) const;
  inline ::ResourceCopyConfig::ResourceCopy* mutable_resource_copies(int index);
  inline ::ResourceCopyConfig::ResourceCopy* add_resource_copies();
  inline const ::google::protobuf::RepeatedPtrField< ::ResourceCopyConfig::ResourceCopy >&
      resource_copies() const;
  inline ::google::protobuf::RepeatedPtrField< ::ResourceCopyConfig::ResourceCopy >*
      mutable_resource_copies();

  // @@protoc_insertion_point(class_scope:ResourceCopyConfig.ResourceCopyAll)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::ResourceCopyConfig::ResourceCopy > resource_copies_;
  friend void  protobuf_AddDesc_ResourceCopyConfig_2eproto();
  friend void protobuf_AssignDesc_ResourceCopyConfig_2eproto();
  friend void protobuf_ShutdownFile_ResourceCopyConfig_2eproto();

  void InitAsDefaultInstance();
  static ResourceCopyAll* default_instance_;
};
// ===================================================================


// ===================================================================

// ResourceCopy

// required uint32 id = 1;
inline bool ResourceCopy::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ResourceCopy::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ResourceCopy::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ResourceCopy::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 ResourceCopy::id() const {
  // @@protoc_insertion_point(field_get:ResourceCopyConfig.ResourceCopy.id)
  return id_;
}
inline void ResourceCopy::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:ResourceCopyConfig.ResourceCopy.id)
}

// required uint32 gateid = 2;
inline bool ResourceCopy::has_gateid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ResourceCopy::set_has_gateid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ResourceCopy::clear_has_gateid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ResourceCopy::clear_gateid() {
  gateid_ = 0u;
  clear_has_gateid();
}
inline ::google::protobuf::uint32 ResourceCopy::gateid() const {
  // @@protoc_insertion_point(field_get:ResourceCopyConfig.ResourceCopy.gateid)
  return gateid_;
}
inline void ResourceCopy::set_gateid(::google::protobuf::uint32 value) {
  set_has_gateid();
  gateid_ = value;
  // @@protoc_insertion_point(field_set:ResourceCopyConfig.ResourceCopy.gateid)
}

// required uint32 viplevel = 3;
inline bool ResourceCopy::has_viplevel() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ResourceCopy::set_has_viplevel() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ResourceCopy::clear_has_viplevel() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ResourceCopy::clear_viplevel() {
  viplevel_ = 0u;
  clear_has_viplevel();
}
inline ::google::protobuf::uint32 ResourceCopy::viplevel() const {
  // @@protoc_insertion_point(field_get:ResourceCopyConfig.ResourceCopy.viplevel)
  return viplevel_;
}
inline void ResourceCopy::set_viplevel(::google::protobuf::uint32 value) {
  set_has_viplevel();
  viplevel_ = value;
  // @@protoc_insertion_point(field_set:ResourceCopyConfig.ResourceCopy.viplevel)
}

// required uint32 timeslimit = 4;
inline bool ResourceCopy::has_timeslimit() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ResourceCopy::set_has_timeslimit() {
  _has_bits_[0] |= 0x00000008u;
}
inline void ResourceCopy::clear_has_timeslimit() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void ResourceCopy::clear_timeslimit() {
  timeslimit_ = 0u;
  clear_has_timeslimit();
}
inline ::google::protobuf::uint32 ResourceCopy::timeslimit() const {
  // @@protoc_insertion_point(field_get:ResourceCopyConfig.ResourceCopy.timeslimit)
  return timeslimit_;
}
inline void ResourceCopy::set_timeslimit(::google::protobuf::uint32 value) {
  set_has_timeslimit();
  timeslimit_ = value;
  // @@protoc_insertion_point(field_set:ResourceCopyConfig.ResourceCopy.timeslimit)
}

// repeated uint32 cash = 5;
inline int ResourceCopy::cash_size() const {
  return cash_.size();
}
inline void ResourceCopy::clear_cash() {
  cash_.Clear();
}
inline ::google::protobuf::uint32 ResourceCopy::cash(int index) const {
  // @@protoc_insertion_point(field_get:ResourceCopyConfig.ResourceCopy.cash)
  return cash_.Get(index);
}
inline void ResourceCopy::set_cash(int index, ::google::protobuf::uint32 value) {
  cash_.Set(index, value);
  // @@protoc_insertion_point(field_set:ResourceCopyConfig.ResourceCopy.cash)
}
inline void ResourceCopy::add_cash(::google::protobuf::uint32 value) {
  cash_.Add(value);
  // @@protoc_insertion_point(field_add:ResourceCopyConfig.ResourceCopy.cash)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
ResourceCopy::cash() const {
  // @@protoc_insertion_point(field_list:ResourceCopyConfig.ResourceCopy.cash)
  return cash_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
ResourceCopy::mutable_cash() {
  // @@protoc_insertion_point(field_mutable_list:ResourceCopyConfig.ResourceCopy.cash)
  return &cash_;
}

// repeated .RewardConfig.Reward reward = 6;
inline int ResourceCopy::reward_size() const {
  return reward_.size();
}
inline void ResourceCopy::clear_reward() {
  reward_.Clear();
}
inline const ::RewardConfig::Reward& ResourceCopy::reward(int index) const {
  // @@protoc_insertion_point(field_get:ResourceCopyConfig.ResourceCopy.reward)
  return reward_.Get(index);
}
inline ::RewardConfig::Reward* ResourceCopy::mutable_reward(int index) {
  // @@protoc_insertion_point(field_mutable:ResourceCopyConfig.ResourceCopy.reward)
  return reward_.Mutable(index);
}
inline ::RewardConfig::Reward* ResourceCopy::add_reward() {
  // @@protoc_insertion_point(field_add:ResourceCopyConfig.ResourceCopy.reward)
  return reward_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward >&
ResourceCopy::reward() const {
  // @@protoc_insertion_point(field_list:ResourceCopyConfig.ResourceCopy.reward)
  return reward_;
}
inline ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward >*
ResourceCopy::mutable_reward() {
  // @@protoc_insertion_point(field_mutable_list:ResourceCopyConfig.ResourceCopy.reward)
  return &reward_;
}

// -------------------------------------------------------------------

// ResourceCopyAll

// repeated .ResourceCopyConfig.ResourceCopy resource_copies = 1;
inline int ResourceCopyAll::resource_copies_size() const {
  return resource_copies_.size();
}
inline void ResourceCopyAll::clear_resource_copies() {
  resource_copies_.Clear();
}
inline const ::ResourceCopyConfig::ResourceCopy& ResourceCopyAll::resource_copies(int index) const {
  // @@protoc_insertion_point(field_get:ResourceCopyConfig.ResourceCopyAll.resource_copies)
  return resource_copies_.Get(index);
}
inline ::ResourceCopyConfig::ResourceCopy* ResourceCopyAll::mutable_resource_copies(int index) {
  // @@protoc_insertion_point(field_mutable:ResourceCopyConfig.ResourceCopyAll.resource_copies)
  return resource_copies_.Mutable(index);
}
inline ::ResourceCopyConfig::ResourceCopy* ResourceCopyAll::add_resource_copies() {
  // @@protoc_insertion_point(field_add:ResourceCopyConfig.ResourceCopyAll.resource_copies)
  return resource_copies_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ResourceCopyConfig::ResourceCopy >&
ResourceCopyAll::resource_copies() const {
  // @@protoc_insertion_point(field_list:ResourceCopyConfig.ResourceCopyAll.resource_copies)
  return resource_copies_;
}
inline ::google::protobuf::RepeatedPtrField< ::ResourceCopyConfig::ResourceCopy >*
ResourceCopyAll::mutable_resource_copies() {
  // @@protoc_insertion_point(field_mutable_list:ResourceCopyConfig.ResourceCopyAll.resource_copies)
  return &resource_copies_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ResourceCopyConfig

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ResourceCopyConfig_2eproto__INCLUDED
