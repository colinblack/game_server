// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CfgActivity.proto

#ifndef PROTOBUF_CfgActivity_2eproto__INCLUDED
#define PROTOBUF_CfgActivity_2eproto__INCLUDED

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
#include "CfgCommon.pb.h"
// @@protoc_insertion_point(includes)

namespace CfgActivity {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_CfgActivity_2eproto();
void protobuf_AssignDesc_CfgActivity_2eproto();
void protobuf_ShutdownFile_CfgActivity_2eproto();

class LimitTs;
class DaliyAct;
class DaliyActs;
class Reward;
class Active;
class Actives;

// ===================================================================

class LimitTs : public ::google::protobuf::Message {
 public:
  LimitTs();
  virtual ~LimitTs();

  LimitTs(const LimitTs& from);

  inline LimitTs& operator=(const LimitTs& from) {
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
  static const LimitTs& default_instance();

  void Swap(LimitTs* other);

  // implements Message ----------------------------------------------

  LimitTs* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const LimitTs& from);
  void MergeFrom(const LimitTs& from);
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

  // required uint32 startTs = 1;
  inline bool has_startts() const;
  inline void clear_startts();
  static const int kStartTsFieldNumber = 1;
  inline ::google::protobuf::uint32 startts() const;
  inline void set_startts(::google::protobuf::uint32 value);

  // required uint32 endTs = 2;
  inline bool has_endts() const;
  inline void clear_endts();
  static const int kEndTsFieldNumber = 2;
  inline ::google::protobuf::uint32 endts() const;
  inline void set_endts(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:CfgActivity.LimitTs)
 private:
  inline void set_has_startts();
  inline void clear_has_startts();
  inline void set_has_endts();
  inline void clear_has_endts();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 startts_;
  ::google::protobuf::uint32 endts_;
  friend void  protobuf_AddDesc_CfgActivity_2eproto();
  friend void protobuf_AssignDesc_CfgActivity_2eproto();
  friend void protobuf_ShutdownFile_CfgActivity_2eproto();

  void InitAsDefaultInstance();
  static LimitTs* default_instance_;
};
// -------------------------------------------------------------------

class DaliyAct : public ::google::protobuf::Message {
 public:
  DaliyAct();
  virtual ~DaliyAct();

  DaliyAct(const DaliyAct& from);

  inline DaliyAct& operator=(const DaliyAct& from) {
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
  static const DaliyAct& default_instance();

  void Swap(DaliyAct* other);

  // implements Message ----------------------------------------------

  DaliyAct* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DaliyAct& from);
  void MergeFrom(const DaliyAct& from);
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

  // required uint32 activity = 1;
  inline bool has_activity() const;
  inline void clear_activity();
  static const int kActivityFieldNumber = 1;
  inline ::google::protobuf::uint32 activity() const;
  inline void set_activity(::google::protobuf::uint32 value);

  // required uint32 copyCfg = 2;
  inline bool has_copycfg() const;
  inline void clear_copycfg();
  static const int kCopyCfgFieldNumber = 2;
  inline ::google::protobuf::uint32 copycfg() const;
  inline void set_copycfg(::google::protobuf::uint32 value);

  // required uint32 copyId = 3;
  inline bool has_copyid() const;
  inline void clear_copyid();
  static const int kCopyIdFieldNumber = 3;
  inline ::google::protobuf::uint32 copyid() const;
  inline void set_copyid(::google::protobuf::uint32 value);

  // required uint32 count = 4;
  inline bool has_count() const;
  inline void clear_count();
  static const int kCountFieldNumber = 4;
  inline ::google::protobuf::uint32 count() const;
  inline void set_count(::google::protobuf::uint32 value);

  // required uint32 type = 5;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 5;
  inline ::google::protobuf::uint32 type() const;
  inline void set_type(::google::protobuf::uint32 value);

  // required uint32 actId = 6;
  inline bool has_actid() const;
  inline void clear_actid();
  static const int kActIdFieldNumber = 6;
  inline ::google::protobuf::uint32 actid() const;
  inline void set_actid(::google::protobuf::uint32 value);

  // repeated .CfgActivity.LimitTs limits = 7;
  inline int limits_size() const;
  inline void clear_limits();
  static const int kLimitsFieldNumber = 7;
  inline const ::CfgActivity::LimitTs& limits(int index) const;
  inline ::CfgActivity::LimitTs* mutable_limits(int index);
  inline ::CfgActivity::LimitTs* add_limits();
  inline const ::google::protobuf::RepeatedPtrField< ::CfgActivity::LimitTs >&
      limits() const;
  inline ::google::protobuf::RepeatedPtrField< ::CfgActivity::LimitTs >*
      mutable_limits();

  // @@protoc_insertion_point(class_scope:CfgActivity.DaliyAct)
 private:
  inline void set_has_activity();
  inline void clear_has_activity();
  inline void set_has_copycfg();
  inline void clear_has_copycfg();
  inline void set_has_copyid();
  inline void clear_has_copyid();
  inline void set_has_count();
  inline void clear_has_count();
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_actid();
  inline void clear_has_actid();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 activity_;
  ::google::protobuf::uint32 copycfg_;
  ::google::protobuf::uint32 copyid_;
  ::google::protobuf::uint32 count_;
  ::google::protobuf::uint32 type_;
  ::google::protobuf::uint32 actid_;
  ::google::protobuf::RepeatedPtrField< ::CfgActivity::LimitTs > limits_;
  friend void  protobuf_AddDesc_CfgActivity_2eproto();
  friend void protobuf_AssignDesc_CfgActivity_2eproto();
  friend void protobuf_ShutdownFile_CfgActivity_2eproto();

  void InitAsDefaultInstance();
  static DaliyAct* default_instance_;
};
// -------------------------------------------------------------------

class DaliyActs : public ::google::protobuf::Message {
 public:
  DaliyActs();
  virtual ~DaliyActs();

  DaliyActs(const DaliyActs& from);

  inline DaliyActs& operator=(const DaliyActs& from) {
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
  static const DaliyActs& default_instance();

  void Swap(DaliyActs* other);

  // implements Message ----------------------------------------------

  DaliyActs* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DaliyActs& from);
  void MergeFrom(const DaliyActs& from);
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

  // repeated .CfgActivity.DaliyAct daliy_act = 1;
  inline int daliy_act_size() const;
  inline void clear_daliy_act();
  static const int kDaliyActFieldNumber = 1;
  inline const ::CfgActivity::DaliyAct& daliy_act(int index) const;
  inline ::CfgActivity::DaliyAct* mutable_daliy_act(int index);
  inline ::CfgActivity::DaliyAct* add_daliy_act();
  inline const ::google::protobuf::RepeatedPtrField< ::CfgActivity::DaliyAct >&
      daliy_act() const;
  inline ::google::protobuf::RepeatedPtrField< ::CfgActivity::DaliyAct >*
      mutable_daliy_act();

  // @@protoc_insertion_point(class_scope:CfgActivity.DaliyActs)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::CfgActivity::DaliyAct > daliy_act_;
  friend void  protobuf_AddDesc_CfgActivity_2eproto();
  friend void protobuf_AssignDesc_CfgActivity_2eproto();
  friend void protobuf_ShutdownFile_CfgActivity_2eproto();

  void InitAsDefaultInstance();
  static DaliyActs* default_instance_;
};
// -------------------------------------------------------------------

class Reward : public ::google::protobuf::Message {
 public:
  Reward();
  virtual ~Reward();

  Reward(const Reward& from);

  inline Reward& operator=(const Reward& from) {
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
  static const Reward& default_instance();

  void Swap(Reward* other);

  // implements Message ----------------------------------------------

  Reward* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Reward& from);
  void MergeFrom(const Reward& from);
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

  // required uint32 count = 2;
  inline bool has_count() const;
  inline void clear_count();
  static const int kCountFieldNumber = 2;
  inline ::google::protobuf::uint32 count() const;
  inline void set_count(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:CfgActivity.Reward)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_count();
  inline void clear_has_count();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 count_;
  friend void  protobuf_AddDesc_CfgActivity_2eproto();
  friend void protobuf_AssignDesc_CfgActivity_2eproto();
  friend void protobuf_ShutdownFile_CfgActivity_2eproto();

  void InitAsDefaultInstance();
  static Reward* default_instance_;
};
// -------------------------------------------------------------------

class Active : public ::google::protobuf::Message {
 public:
  Active();
  virtual ~Active();

  Active(const Active& from);

  inline Active& operator=(const Active& from) {
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
  static const Active& default_instance();

  void Swap(Active* other);

  // implements Message ----------------------------------------------

  Active* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Active& from);
  void MergeFrom(const Active& from);
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

  // required uint32 limit = 1;
  inline bool has_limit() const;
  inline void clear_limit();
  static const int kLimitFieldNumber = 1;
  inline ::google::protobuf::uint32 limit() const;
  inline void set_limit(::google::protobuf::uint32 value);

  // required uint32 type = 2;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 2;
  inline ::google::protobuf::uint32 type() const;
  inline void set_type(::google::protobuf::uint32 value);

  // repeated .CfgCommon.Reward reward = 3;
  inline int reward_size() const;
  inline void clear_reward();
  static const int kRewardFieldNumber = 3;
  inline const ::CfgCommon::Reward& reward(int index) const;
  inline ::CfgCommon::Reward* mutable_reward(int index);
  inline ::CfgCommon::Reward* add_reward();
  inline const ::google::protobuf::RepeatedPtrField< ::CfgCommon::Reward >&
      reward() const;
  inline ::google::protobuf::RepeatedPtrField< ::CfgCommon::Reward >*
      mutable_reward();

  // @@protoc_insertion_point(class_scope:CfgActivity.Active)
 private:
  inline void set_has_limit();
  inline void clear_has_limit();
  inline void set_has_type();
  inline void clear_has_type();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 limit_;
  ::google::protobuf::uint32 type_;
  ::google::protobuf::RepeatedPtrField< ::CfgCommon::Reward > reward_;
  friend void  protobuf_AddDesc_CfgActivity_2eproto();
  friend void protobuf_AssignDesc_CfgActivity_2eproto();
  friend void protobuf_ShutdownFile_CfgActivity_2eproto();

  void InitAsDefaultInstance();
  static Active* default_instance_;
};
// -------------------------------------------------------------------

class Actives : public ::google::protobuf::Message {
 public:
  Actives();
  virtual ~Actives();

  Actives(const Actives& from);

  inline Actives& operator=(const Actives& from) {
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
  static const Actives& default_instance();

  void Swap(Actives* other);

  // implements Message ----------------------------------------------

  Actives* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Actives& from);
  void MergeFrom(const Actives& from);
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

  // repeated .CfgActivity.Active active = 1;
  inline int active_size() const;
  inline void clear_active();
  static const int kActiveFieldNumber = 1;
  inline const ::CfgActivity::Active& active(int index) const;
  inline ::CfgActivity::Active* mutable_active(int index);
  inline ::CfgActivity::Active* add_active();
  inline const ::google::protobuf::RepeatedPtrField< ::CfgActivity::Active >&
      active() const;
  inline ::google::protobuf::RepeatedPtrField< ::CfgActivity::Active >*
      mutable_active();

  // @@protoc_insertion_point(class_scope:CfgActivity.Actives)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::CfgActivity::Active > active_;
  friend void  protobuf_AddDesc_CfgActivity_2eproto();
  friend void protobuf_AssignDesc_CfgActivity_2eproto();
  friend void protobuf_ShutdownFile_CfgActivity_2eproto();

  void InitAsDefaultInstance();
  static Actives* default_instance_;
};
// ===================================================================


// ===================================================================

// LimitTs

// required uint32 startTs = 1;
inline bool LimitTs::has_startts() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void LimitTs::set_has_startts() {
  _has_bits_[0] |= 0x00000001u;
}
inline void LimitTs::clear_has_startts() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void LimitTs::clear_startts() {
  startts_ = 0u;
  clear_has_startts();
}
inline ::google::protobuf::uint32 LimitTs::startts() const {
  // @@protoc_insertion_point(field_get:CfgActivity.LimitTs.startTs)
  return startts_;
}
inline void LimitTs::set_startts(::google::protobuf::uint32 value) {
  set_has_startts();
  startts_ = value;
  // @@protoc_insertion_point(field_set:CfgActivity.LimitTs.startTs)
}

// required uint32 endTs = 2;
inline bool LimitTs::has_endts() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void LimitTs::set_has_endts() {
  _has_bits_[0] |= 0x00000002u;
}
inline void LimitTs::clear_has_endts() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void LimitTs::clear_endts() {
  endts_ = 0u;
  clear_has_endts();
}
inline ::google::protobuf::uint32 LimitTs::endts() const {
  // @@protoc_insertion_point(field_get:CfgActivity.LimitTs.endTs)
  return endts_;
}
inline void LimitTs::set_endts(::google::protobuf::uint32 value) {
  set_has_endts();
  endts_ = value;
  // @@protoc_insertion_point(field_set:CfgActivity.LimitTs.endTs)
}

// -------------------------------------------------------------------

// DaliyAct

// required uint32 activity = 1;
inline bool DaliyAct::has_activity() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void DaliyAct::set_has_activity() {
  _has_bits_[0] |= 0x00000001u;
}
inline void DaliyAct::clear_has_activity() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void DaliyAct::clear_activity() {
  activity_ = 0u;
  clear_has_activity();
}
inline ::google::protobuf::uint32 DaliyAct::activity() const {
  // @@protoc_insertion_point(field_get:CfgActivity.DaliyAct.activity)
  return activity_;
}
inline void DaliyAct::set_activity(::google::protobuf::uint32 value) {
  set_has_activity();
  activity_ = value;
  // @@protoc_insertion_point(field_set:CfgActivity.DaliyAct.activity)
}

// required uint32 copyCfg = 2;
inline bool DaliyAct::has_copycfg() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void DaliyAct::set_has_copycfg() {
  _has_bits_[0] |= 0x00000002u;
}
inline void DaliyAct::clear_has_copycfg() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void DaliyAct::clear_copycfg() {
  copycfg_ = 0u;
  clear_has_copycfg();
}
inline ::google::protobuf::uint32 DaliyAct::copycfg() const {
  // @@protoc_insertion_point(field_get:CfgActivity.DaliyAct.copyCfg)
  return copycfg_;
}
inline void DaliyAct::set_copycfg(::google::protobuf::uint32 value) {
  set_has_copycfg();
  copycfg_ = value;
  // @@protoc_insertion_point(field_set:CfgActivity.DaliyAct.copyCfg)
}

// required uint32 copyId = 3;
inline bool DaliyAct::has_copyid() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void DaliyAct::set_has_copyid() {
  _has_bits_[0] |= 0x00000004u;
}
inline void DaliyAct::clear_has_copyid() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void DaliyAct::clear_copyid() {
  copyid_ = 0u;
  clear_has_copyid();
}
inline ::google::protobuf::uint32 DaliyAct::copyid() const {
  // @@protoc_insertion_point(field_get:CfgActivity.DaliyAct.copyId)
  return copyid_;
}
inline void DaliyAct::set_copyid(::google::protobuf::uint32 value) {
  set_has_copyid();
  copyid_ = value;
  // @@protoc_insertion_point(field_set:CfgActivity.DaliyAct.copyId)
}

// required uint32 count = 4;
inline bool DaliyAct::has_count() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void DaliyAct::set_has_count() {
  _has_bits_[0] |= 0x00000008u;
}
inline void DaliyAct::clear_has_count() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void DaliyAct::clear_count() {
  count_ = 0u;
  clear_has_count();
}
inline ::google::protobuf::uint32 DaliyAct::count() const {
  // @@protoc_insertion_point(field_get:CfgActivity.DaliyAct.count)
  return count_;
}
inline void DaliyAct::set_count(::google::protobuf::uint32 value) {
  set_has_count();
  count_ = value;
  // @@protoc_insertion_point(field_set:CfgActivity.DaliyAct.count)
}

// required uint32 type = 5;
inline bool DaliyAct::has_type() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void DaliyAct::set_has_type() {
  _has_bits_[0] |= 0x00000010u;
}
inline void DaliyAct::clear_has_type() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void DaliyAct::clear_type() {
  type_ = 0u;
  clear_has_type();
}
inline ::google::protobuf::uint32 DaliyAct::type() const {
  // @@protoc_insertion_point(field_get:CfgActivity.DaliyAct.type)
  return type_;
}
inline void DaliyAct::set_type(::google::protobuf::uint32 value) {
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:CfgActivity.DaliyAct.type)
}

// required uint32 actId = 6;
inline bool DaliyAct::has_actid() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void DaliyAct::set_has_actid() {
  _has_bits_[0] |= 0x00000020u;
}
inline void DaliyAct::clear_has_actid() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void DaliyAct::clear_actid() {
  actid_ = 0u;
  clear_has_actid();
}
inline ::google::protobuf::uint32 DaliyAct::actid() const {
  // @@protoc_insertion_point(field_get:CfgActivity.DaliyAct.actId)
  return actid_;
}
inline void DaliyAct::set_actid(::google::protobuf::uint32 value) {
  set_has_actid();
  actid_ = value;
  // @@protoc_insertion_point(field_set:CfgActivity.DaliyAct.actId)
}

// repeated .CfgActivity.LimitTs limits = 7;
inline int DaliyAct::limits_size() const {
  return limits_.size();
}
inline void DaliyAct::clear_limits() {
  limits_.Clear();
}
inline const ::CfgActivity::LimitTs& DaliyAct::limits(int index) const {
  // @@protoc_insertion_point(field_get:CfgActivity.DaliyAct.limits)
  return limits_.Get(index);
}
inline ::CfgActivity::LimitTs* DaliyAct::mutable_limits(int index) {
  // @@protoc_insertion_point(field_mutable:CfgActivity.DaliyAct.limits)
  return limits_.Mutable(index);
}
inline ::CfgActivity::LimitTs* DaliyAct::add_limits() {
  // @@protoc_insertion_point(field_add:CfgActivity.DaliyAct.limits)
  return limits_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::CfgActivity::LimitTs >&
DaliyAct::limits() const {
  // @@protoc_insertion_point(field_list:CfgActivity.DaliyAct.limits)
  return limits_;
}
inline ::google::protobuf::RepeatedPtrField< ::CfgActivity::LimitTs >*
DaliyAct::mutable_limits() {
  // @@protoc_insertion_point(field_mutable_list:CfgActivity.DaliyAct.limits)
  return &limits_;
}

// -------------------------------------------------------------------

// DaliyActs

// repeated .CfgActivity.DaliyAct daliy_act = 1;
inline int DaliyActs::daliy_act_size() const {
  return daliy_act_.size();
}
inline void DaliyActs::clear_daliy_act() {
  daliy_act_.Clear();
}
inline const ::CfgActivity::DaliyAct& DaliyActs::daliy_act(int index) const {
  // @@protoc_insertion_point(field_get:CfgActivity.DaliyActs.daliy_act)
  return daliy_act_.Get(index);
}
inline ::CfgActivity::DaliyAct* DaliyActs::mutable_daliy_act(int index) {
  // @@protoc_insertion_point(field_mutable:CfgActivity.DaliyActs.daliy_act)
  return daliy_act_.Mutable(index);
}
inline ::CfgActivity::DaliyAct* DaliyActs::add_daliy_act() {
  // @@protoc_insertion_point(field_add:CfgActivity.DaliyActs.daliy_act)
  return daliy_act_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::CfgActivity::DaliyAct >&
DaliyActs::daliy_act() const {
  // @@protoc_insertion_point(field_list:CfgActivity.DaliyActs.daliy_act)
  return daliy_act_;
}
inline ::google::protobuf::RepeatedPtrField< ::CfgActivity::DaliyAct >*
DaliyActs::mutable_daliy_act() {
  // @@protoc_insertion_point(field_mutable_list:CfgActivity.DaliyActs.daliy_act)
  return &daliy_act_;
}

// -------------------------------------------------------------------

// Reward

// required uint32 id = 1;
inline bool Reward::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Reward::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Reward::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Reward::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 Reward::id() const {
  // @@protoc_insertion_point(field_get:CfgActivity.Reward.id)
  return id_;
}
inline void Reward::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:CfgActivity.Reward.id)
}

// required uint32 count = 2;
inline bool Reward::has_count() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Reward::set_has_count() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Reward::clear_has_count() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Reward::clear_count() {
  count_ = 0u;
  clear_has_count();
}
inline ::google::protobuf::uint32 Reward::count() const {
  // @@protoc_insertion_point(field_get:CfgActivity.Reward.count)
  return count_;
}
inline void Reward::set_count(::google::protobuf::uint32 value) {
  set_has_count();
  count_ = value;
  // @@protoc_insertion_point(field_set:CfgActivity.Reward.count)
}

// -------------------------------------------------------------------

// Active

// required uint32 limit = 1;
inline bool Active::has_limit() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Active::set_has_limit() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Active::clear_has_limit() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Active::clear_limit() {
  limit_ = 0u;
  clear_has_limit();
}
inline ::google::protobuf::uint32 Active::limit() const {
  // @@protoc_insertion_point(field_get:CfgActivity.Active.limit)
  return limit_;
}
inline void Active::set_limit(::google::protobuf::uint32 value) {
  set_has_limit();
  limit_ = value;
  // @@protoc_insertion_point(field_set:CfgActivity.Active.limit)
}

// required uint32 type = 2;
inline bool Active::has_type() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Active::set_has_type() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Active::clear_has_type() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Active::clear_type() {
  type_ = 0u;
  clear_has_type();
}
inline ::google::protobuf::uint32 Active::type() const {
  // @@protoc_insertion_point(field_get:CfgActivity.Active.type)
  return type_;
}
inline void Active::set_type(::google::protobuf::uint32 value) {
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:CfgActivity.Active.type)
}

// repeated .CfgCommon.Reward reward = 3;
inline int Active::reward_size() const {
  return reward_.size();
}
inline void Active::clear_reward() {
  reward_.Clear();
}
inline const ::CfgCommon::Reward& Active::reward(int index) const {
  // @@protoc_insertion_point(field_get:CfgActivity.Active.reward)
  return reward_.Get(index);
}
inline ::CfgCommon::Reward* Active::mutable_reward(int index) {
  // @@protoc_insertion_point(field_mutable:CfgActivity.Active.reward)
  return reward_.Mutable(index);
}
inline ::CfgCommon::Reward* Active::add_reward() {
  // @@protoc_insertion_point(field_add:CfgActivity.Active.reward)
  return reward_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::CfgCommon::Reward >&
Active::reward() const {
  // @@protoc_insertion_point(field_list:CfgActivity.Active.reward)
  return reward_;
}
inline ::google::protobuf::RepeatedPtrField< ::CfgCommon::Reward >*
Active::mutable_reward() {
  // @@protoc_insertion_point(field_mutable_list:CfgActivity.Active.reward)
  return &reward_;
}

// -------------------------------------------------------------------

// Actives

// repeated .CfgActivity.Active active = 1;
inline int Actives::active_size() const {
  return active_.size();
}
inline void Actives::clear_active() {
  active_.Clear();
}
inline const ::CfgActivity::Active& Actives::active(int index) const {
  // @@protoc_insertion_point(field_get:CfgActivity.Actives.active)
  return active_.Get(index);
}
inline ::CfgActivity::Active* Actives::mutable_active(int index) {
  // @@protoc_insertion_point(field_mutable:CfgActivity.Actives.active)
  return active_.Mutable(index);
}
inline ::CfgActivity::Active* Actives::add_active() {
  // @@protoc_insertion_point(field_add:CfgActivity.Actives.active)
  return active_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::CfgActivity::Active >&
Actives::active() const {
  // @@protoc_insertion_point(field_list:CfgActivity.Actives.active)
  return active_;
}
inline ::google::protobuf::RepeatedPtrField< ::CfgActivity::Active >*
Actives::mutable_active() {
  // @@protoc_insertion_point(field_mutable_list:CfgActivity.Actives.active)
  return &active_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace CfgActivity

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_CfgActivity_2eproto__INCLUDED
