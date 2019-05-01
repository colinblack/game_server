// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ModelTrialConfig.proto

#ifndef PROTOBUF_ModelTrialConfig_2eproto__INCLUDED
#define PROTOBUF_ModelTrialConfig_2eproto__INCLUDED

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

namespace ModelTrialConfig {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ModelTrialConfig_2eproto();
void protobuf_AssignDesc_ModelTrialConfig_2eproto();
void protobuf_ShutdownFile_ModelTrialConfig_2eproto();

class TrialGate;
class ModelTrial;

// ===================================================================

class TrialGate : public ::google::protobuf::Message {
 public:
  TrialGate();
  virtual ~TrialGate();

  TrialGate(const TrialGate& from);

  inline TrialGate& operator=(const TrialGate& from) {
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
  static const TrialGate& default_instance();

  void Swap(TrialGate* other);

  // implements Message ----------------------------------------------

  TrialGate* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TrialGate& from);
  void MergeFrom(const TrialGate& from);
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

  // required uint32 terrain = 2;
  inline bool has_terrain() const;
  inline void clear_terrain();
  static const int kTerrainFieldNumber = 2;
  inline ::google::protobuf::uint32 terrain() const;
  inline void set_terrain(::google::protobuf::uint32 value);

  // repeated uint32 npcs = 3;
  inline int npcs_size() const;
  inline void clear_npcs();
  static const int kNpcsFieldNumber = 3;
  inline ::google::protobuf::uint32 npcs(int index) const;
  inline void set_npcs(int index, ::google::protobuf::uint32 value);
  inline void add_npcs(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      npcs() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_npcs();

  // repeated .RewardConfig.Reward first_reward = 4;
  inline int first_reward_size() const;
  inline void clear_first_reward();
  static const int kFirstRewardFieldNumber = 4;
  inline const ::RewardConfig::Reward& first_reward(int index) const;
  inline ::RewardConfig::Reward* mutable_first_reward(int index);
  inline ::RewardConfig::Reward* add_first_reward();
  inline const ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward >&
      first_reward() const;
  inline ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward >*
      mutable_first_reward();

  // repeated .RewardConfig.Reward reward = 5;
  inline int reward_size() const;
  inline void clear_reward();
  static const int kRewardFieldNumber = 5;
  inline const ::RewardConfig::Reward& reward(int index) const;
  inline ::RewardConfig::Reward* mutable_reward(int index);
  inline ::RewardConfig::Reward* add_reward();
  inline const ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward >&
      reward() const;
  inline ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward >*
      mutable_reward();

  // @@protoc_insertion_point(class_scope:ModelTrialConfig.TrialGate)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_terrain();
  inline void clear_has_terrain();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 terrain_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > npcs_;
  ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward > first_reward_;
  ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward > reward_;
  friend void  protobuf_AddDesc_ModelTrialConfig_2eproto();
  friend void protobuf_AssignDesc_ModelTrialConfig_2eproto();
  friend void protobuf_ShutdownFile_ModelTrialConfig_2eproto();

  void InitAsDefaultInstance();
  static TrialGate* default_instance_;
};
// -------------------------------------------------------------------

class ModelTrial : public ::google::protobuf::Message {
 public:
  ModelTrial();
  virtual ~ModelTrial();

  ModelTrial(const ModelTrial& from);

  inline ModelTrial& operator=(const ModelTrial& from) {
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
  static const ModelTrial& default_instance();

  void Swap(ModelTrial* other);

  // implements Message ----------------------------------------------

  ModelTrial* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ModelTrial& from);
  void MergeFrom(const ModelTrial& from);
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

  // required uint32 maxtimes = 1;
  inline bool has_maxtimes() const;
  inline void clear_maxtimes();
  static const int kMaxtimesFieldNumber = 1;
  inline ::google::protobuf::uint32 maxtimes() const;
  inline void set_maxtimes(::google::protobuf::uint32 value);

  // repeated uint32 times_price = 2;
  inline int times_price_size() const;
  inline void clear_times_price();
  static const int kTimesPriceFieldNumber = 2;
  inline ::google::protobuf::uint32 times_price(int index) const;
  inline void set_times_price(int index, ::google::protobuf::uint32 value);
  inline void add_times_price(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      times_price() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_times_price();

  // repeated .ModelTrialConfig.TrialGate gates = 3;
  inline int gates_size() const;
  inline void clear_gates();
  static const int kGatesFieldNumber = 3;
  inline const ::ModelTrialConfig::TrialGate& gates(int index) const;
  inline ::ModelTrialConfig::TrialGate* mutable_gates(int index);
  inline ::ModelTrialConfig::TrialGate* add_gates();
  inline const ::google::protobuf::RepeatedPtrField< ::ModelTrialConfig::TrialGate >&
      gates() const;
  inline ::google::protobuf::RepeatedPtrField< ::ModelTrialConfig::TrialGate >*
      mutable_gates();

  // @@protoc_insertion_point(class_scope:ModelTrialConfig.ModelTrial)
 private:
  inline void set_has_maxtimes();
  inline void clear_has_maxtimes();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > times_price_;
  ::google::protobuf::RepeatedPtrField< ::ModelTrialConfig::TrialGate > gates_;
  ::google::protobuf::uint32 maxtimes_;
  friend void  protobuf_AddDesc_ModelTrialConfig_2eproto();
  friend void protobuf_AssignDesc_ModelTrialConfig_2eproto();
  friend void protobuf_ShutdownFile_ModelTrialConfig_2eproto();

  void InitAsDefaultInstance();
  static ModelTrial* default_instance_;
};
// ===================================================================


// ===================================================================

// TrialGate

// required uint32 id = 1;
inline bool TrialGate::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TrialGate::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TrialGate::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TrialGate::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 TrialGate::id() const {
  // @@protoc_insertion_point(field_get:ModelTrialConfig.TrialGate.id)
  return id_;
}
inline void TrialGate::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:ModelTrialConfig.TrialGate.id)
}

// required uint32 terrain = 2;
inline bool TrialGate::has_terrain() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TrialGate::set_has_terrain() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TrialGate::clear_has_terrain() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TrialGate::clear_terrain() {
  terrain_ = 0u;
  clear_has_terrain();
}
inline ::google::protobuf::uint32 TrialGate::terrain() const {
  // @@protoc_insertion_point(field_get:ModelTrialConfig.TrialGate.terrain)
  return terrain_;
}
inline void TrialGate::set_terrain(::google::protobuf::uint32 value) {
  set_has_terrain();
  terrain_ = value;
  // @@protoc_insertion_point(field_set:ModelTrialConfig.TrialGate.terrain)
}

// repeated uint32 npcs = 3;
inline int TrialGate::npcs_size() const {
  return npcs_.size();
}
inline void TrialGate::clear_npcs() {
  npcs_.Clear();
}
inline ::google::protobuf::uint32 TrialGate::npcs(int index) const {
  // @@protoc_insertion_point(field_get:ModelTrialConfig.TrialGate.npcs)
  return npcs_.Get(index);
}
inline void TrialGate::set_npcs(int index, ::google::protobuf::uint32 value) {
  npcs_.Set(index, value);
  // @@protoc_insertion_point(field_set:ModelTrialConfig.TrialGate.npcs)
}
inline void TrialGate::add_npcs(::google::protobuf::uint32 value) {
  npcs_.Add(value);
  // @@protoc_insertion_point(field_add:ModelTrialConfig.TrialGate.npcs)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
TrialGate::npcs() const {
  // @@protoc_insertion_point(field_list:ModelTrialConfig.TrialGate.npcs)
  return npcs_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
TrialGate::mutable_npcs() {
  // @@protoc_insertion_point(field_mutable_list:ModelTrialConfig.TrialGate.npcs)
  return &npcs_;
}

// repeated .RewardConfig.Reward first_reward = 4;
inline int TrialGate::first_reward_size() const {
  return first_reward_.size();
}
inline void TrialGate::clear_first_reward() {
  first_reward_.Clear();
}
inline const ::RewardConfig::Reward& TrialGate::first_reward(int index) const {
  // @@protoc_insertion_point(field_get:ModelTrialConfig.TrialGate.first_reward)
  return first_reward_.Get(index);
}
inline ::RewardConfig::Reward* TrialGate::mutable_first_reward(int index) {
  // @@protoc_insertion_point(field_mutable:ModelTrialConfig.TrialGate.first_reward)
  return first_reward_.Mutable(index);
}
inline ::RewardConfig::Reward* TrialGate::add_first_reward() {
  // @@protoc_insertion_point(field_add:ModelTrialConfig.TrialGate.first_reward)
  return first_reward_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward >&
TrialGate::first_reward() const {
  // @@protoc_insertion_point(field_list:ModelTrialConfig.TrialGate.first_reward)
  return first_reward_;
}
inline ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward >*
TrialGate::mutable_first_reward() {
  // @@protoc_insertion_point(field_mutable_list:ModelTrialConfig.TrialGate.first_reward)
  return &first_reward_;
}

// repeated .RewardConfig.Reward reward = 5;
inline int TrialGate::reward_size() const {
  return reward_.size();
}
inline void TrialGate::clear_reward() {
  reward_.Clear();
}
inline const ::RewardConfig::Reward& TrialGate::reward(int index) const {
  // @@protoc_insertion_point(field_get:ModelTrialConfig.TrialGate.reward)
  return reward_.Get(index);
}
inline ::RewardConfig::Reward* TrialGate::mutable_reward(int index) {
  // @@protoc_insertion_point(field_mutable:ModelTrialConfig.TrialGate.reward)
  return reward_.Mutable(index);
}
inline ::RewardConfig::Reward* TrialGate::add_reward() {
  // @@protoc_insertion_point(field_add:ModelTrialConfig.TrialGate.reward)
  return reward_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward >&
TrialGate::reward() const {
  // @@protoc_insertion_point(field_list:ModelTrialConfig.TrialGate.reward)
  return reward_;
}
inline ::google::protobuf::RepeatedPtrField< ::RewardConfig::Reward >*
TrialGate::mutable_reward() {
  // @@protoc_insertion_point(field_mutable_list:ModelTrialConfig.TrialGate.reward)
  return &reward_;
}

// -------------------------------------------------------------------

// ModelTrial

// required uint32 maxtimes = 1;
inline bool ModelTrial::has_maxtimes() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ModelTrial::set_has_maxtimes() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ModelTrial::clear_has_maxtimes() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ModelTrial::clear_maxtimes() {
  maxtimes_ = 0u;
  clear_has_maxtimes();
}
inline ::google::protobuf::uint32 ModelTrial::maxtimes() const {
  // @@protoc_insertion_point(field_get:ModelTrialConfig.ModelTrial.maxtimes)
  return maxtimes_;
}
inline void ModelTrial::set_maxtimes(::google::protobuf::uint32 value) {
  set_has_maxtimes();
  maxtimes_ = value;
  // @@protoc_insertion_point(field_set:ModelTrialConfig.ModelTrial.maxtimes)
}

// repeated uint32 times_price = 2;
inline int ModelTrial::times_price_size() const {
  return times_price_.size();
}
inline void ModelTrial::clear_times_price() {
  times_price_.Clear();
}
inline ::google::protobuf::uint32 ModelTrial::times_price(int index) const {
  // @@protoc_insertion_point(field_get:ModelTrialConfig.ModelTrial.times_price)
  return times_price_.Get(index);
}
inline void ModelTrial::set_times_price(int index, ::google::protobuf::uint32 value) {
  times_price_.Set(index, value);
  // @@protoc_insertion_point(field_set:ModelTrialConfig.ModelTrial.times_price)
}
inline void ModelTrial::add_times_price(::google::protobuf::uint32 value) {
  times_price_.Add(value);
  // @@protoc_insertion_point(field_add:ModelTrialConfig.ModelTrial.times_price)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
ModelTrial::times_price() const {
  // @@protoc_insertion_point(field_list:ModelTrialConfig.ModelTrial.times_price)
  return times_price_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
ModelTrial::mutable_times_price() {
  // @@protoc_insertion_point(field_mutable_list:ModelTrialConfig.ModelTrial.times_price)
  return &times_price_;
}

// repeated .ModelTrialConfig.TrialGate gates = 3;
inline int ModelTrial::gates_size() const {
  return gates_.size();
}
inline void ModelTrial::clear_gates() {
  gates_.Clear();
}
inline const ::ModelTrialConfig::TrialGate& ModelTrial::gates(int index) const {
  // @@protoc_insertion_point(field_get:ModelTrialConfig.ModelTrial.gates)
  return gates_.Get(index);
}
inline ::ModelTrialConfig::TrialGate* ModelTrial::mutable_gates(int index) {
  // @@protoc_insertion_point(field_mutable:ModelTrialConfig.ModelTrial.gates)
  return gates_.Mutable(index);
}
inline ::ModelTrialConfig::TrialGate* ModelTrial::add_gates() {
  // @@protoc_insertion_point(field_add:ModelTrialConfig.ModelTrial.gates)
  return gates_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ModelTrialConfig::TrialGate >&
ModelTrial::gates() const {
  // @@protoc_insertion_point(field_list:ModelTrialConfig.ModelTrial.gates)
  return gates_;
}
inline ::google::protobuf::RepeatedPtrField< ::ModelTrialConfig::TrialGate >*
ModelTrial::mutable_gates() {
  // @@protoc_insertion_point(field_mutable_list:ModelTrialConfig.ModelTrial.gates)
  return &gates_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ModelTrialConfig

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ModelTrialConfig_2eproto__INCLUDED
