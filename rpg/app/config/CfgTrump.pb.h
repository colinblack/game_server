// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CfgTrump.proto

#ifndef PROTOBUF_CfgTrump_2eproto__INCLUDED
#define PROTOBUF_CfgTrump_2eproto__INCLUDED

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

namespace CfgTrump {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_CfgTrump_2eproto();
void protobuf_AssignDesc_CfgTrump_2eproto();
void protobuf_ShutdownFile_CfgTrump_2eproto();

class TrumpInfo;
class Trumps;
class TrumpSkillInfo;
class TrumpSkill;

// ===================================================================

class TrumpInfo : public ::google::protobuf::Message {
 public:
  TrumpInfo();
  virtual ~TrumpInfo();

  TrumpInfo(const TrumpInfo& from);

  inline TrumpInfo& operator=(const TrumpInfo& from) {
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
  static const TrumpInfo& default_instance();

  void Swap(TrumpInfo* other);

  // implements Message ----------------------------------------------

  TrumpInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TrumpInfo& from);
  void MergeFrom(const TrumpInfo& from);
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

  // required int32 level = 1;
  inline bool has_level() const;
  inline void clear_level();
  static const int kLevelFieldNumber = 1;
  inline ::google::protobuf::int32 level() const;
  inline void set_level(::google::protobuf::int32 value);

  // required int32 star = 2;
  inline bool has_star() const;
  inline void clear_star();
  static const int kStarFieldNumber = 2;
  inline ::google::protobuf::int32 star() const;
  inline void set_star(::google::protobuf::int32 value);

  // required int32 stage = 3;
  inline bool has_stage() const;
  inline void clear_stage();
  static const int kStageFieldNumber = 3;
  inline ::google::protobuf::int32 stage() const;
  inline void set_stage(::google::protobuf::int32 value);

  // required int32 cost_item = 4;
  inline bool has_cost_item() const;
  inline void clear_cost_item();
  static const int kCostItemFieldNumber = 4;
  inline ::google::protobuf::int32 cost_item() const;
  inline void set_cost_item(::google::protobuf::int32 value);

  // required int32 cost_count = 5;
  inline bool has_cost_count() const;
  inline void clear_cost_count();
  static const int kCostCountFieldNumber = 5;
  inline ::google::protobuf::int32 cost_count() const;
  inline void set_cost_count(::google::protobuf::int32 value);

  // repeated .CfgCommon.Attribute attr = 6;
  inline int attr_size() const;
  inline void clear_attr();
  static const int kAttrFieldNumber = 6;
  inline const ::CfgCommon::Attribute& attr(int index) const;
  inline ::CfgCommon::Attribute* mutable_attr(int index);
  inline ::CfgCommon::Attribute* add_attr();
  inline const ::google::protobuf::RepeatedPtrField< ::CfgCommon::Attribute >&
      attr() const;
  inline ::google::protobuf::RepeatedPtrField< ::CfgCommon::Attribute >*
      mutable_attr();

  // @@protoc_insertion_point(class_scope:CfgTrump.TrumpInfo)
 private:
  inline void set_has_level();
  inline void clear_has_level();
  inline void set_has_star();
  inline void clear_has_star();
  inline void set_has_stage();
  inline void clear_has_stage();
  inline void set_has_cost_item();
  inline void clear_has_cost_item();
  inline void set_has_cost_count();
  inline void clear_has_cost_count();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int32 level_;
  ::google::protobuf::int32 star_;
  ::google::protobuf::int32 stage_;
  ::google::protobuf::int32 cost_item_;
  ::google::protobuf::RepeatedPtrField< ::CfgCommon::Attribute > attr_;
  ::google::protobuf::int32 cost_count_;
  friend void  protobuf_AddDesc_CfgTrump_2eproto();
  friend void protobuf_AssignDesc_CfgTrump_2eproto();
  friend void protobuf_ShutdownFile_CfgTrump_2eproto();

  void InitAsDefaultInstance();
  static TrumpInfo* default_instance_;
};
// -------------------------------------------------------------------

class Trumps : public ::google::protobuf::Message {
 public:
  Trumps();
  virtual ~Trumps();

  Trumps(const Trumps& from);

  inline Trumps& operator=(const Trumps& from) {
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
  static const Trumps& default_instance();

  void Swap(Trumps* other);

  // implements Message ----------------------------------------------

  Trumps* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Trumps& from);
  void MergeFrom(const Trumps& from);
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

  // repeated .CfgTrump.TrumpInfo trump = 1;
  inline int trump_size() const;
  inline void clear_trump();
  static const int kTrumpFieldNumber = 1;
  inline const ::CfgTrump::TrumpInfo& trump(int index) const;
  inline ::CfgTrump::TrumpInfo* mutable_trump(int index);
  inline ::CfgTrump::TrumpInfo* add_trump();
  inline const ::google::protobuf::RepeatedPtrField< ::CfgTrump::TrumpInfo >&
      trump() const;
  inline ::google::protobuf::RepeatedPtrField< ::CfgTrump::TrumpInfo >*
      mutable_trump();

  // @@protoc_insertion_point(class_scope:CfgTrump.Trumps)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::CfgTrump::TrumpInfo > trump_;
  friend void  protobuf_AddDesc_CfgTrump_2eproto();
  friend void protobuf_AssignDesc_CfgTrump_2eproto();
  friend void protobuf_ShutdownFile_CfgTrump_2eproto();

  void InitAsDefaultInstance();
  static Trumps* default_instance_;
};
// -------------------------------------------------------------------

class TrumpSkillInfo : public ::google::protobuf::Message {
 public:
  TrumpSkillInfo();
  virtual ~TrumpSkillInfo();

  TrumpSkillInfo(const TrumpSkillInfo& from);

  inline TrumpSkillInfo& operator=(const TrumpSkillInfo& from) {
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
  static const TrumpSkillInfo& default_instance();

  void Swap(TrumpSkillInfo* other);

  // implements Message ----------------------------------------------

  TrumpSkillInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TrumpSkillInfo& from);
  void MergeFrom(const TrumpSkillInfo& from);
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

  // required int32 stage = 1;
  inline bool has_stage() const;
  inline void clear_stage();
  static const int kStageFieldNumber = 1;
  inline ::google::protobuf::int32 stage() const;
  inline void set_stage(::google::protobuf::int32 value);

  // repeated .CfgCommon.Attribute attr = 2;
  inline int attr_size() const;
  inline void clear_attr();
  static const int kAttrFieldNumber = 2;
  inline const ::CfgCommon::Attribute& attr(int index) const;
  inline ::CfgCommon::Attribute* mutable_attr(int index);
  inline ::CfgCommon::Attribute* add_attr();
  inline const ::google::protobuf::RepeatedPtrField< ::CfgCommon::Attribute >&
      attr() const;
  inline ::google::protobuf::RepeatedPtrField< ::CfgCommon::Attribute >*
      mutable_attr();

  // @@protoc_insertion_point(class_scope:CfgTrump.TrumpSkillInfo)
 private:
  inline void set_has_stage();
  inline void clear_has_stage();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::CfgCommon::Attribute > attr_;
  ::google::protobuf::int32 stage_;
  friend void  protobuf_AddDesc_CfgTrump_2eproto();
  friend void protobuf_AssignDesc_CfgTrump_2eproto();
  friend void protobuf_ShutdownFile_CfgTrump_2eproto();

  void InitAsDefaultInstance();
  static TrumpSkillInfo* default_instance_;
};
// -------------------------------------------------------------------

class TrumpSkill : public ::google::protobuf::Message {
 public:
  TrumpSkill();
  virtual ~TrumpSkill();

  TrumpSkill(const TrumpSkill& from);

  inline TrumpSkill& operator=(const TrumpSkill& from) {
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
  static const TrumpSkill& default_instance();

  void Swap(TrumpSkill* other);

  // implements Message ----------------------------------------------

  TrumpSkill* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TrumpSkill& from);
  void MergeFrom(const TrumpSkill& from);
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

  // repeated .CfgTrump.TrumpSkillInfo trump_skill = 1;
  inline int trump_skill_size() const;
  inline void clear_trump_skill();
  static const int kTrumpSkillFieldNumber = 1;
  inline const ::CfgTrump::TrumpSkillInfo& trump_skill(int index) const;
  inline ::CfgTrump::TrumpSkillInfo* mutable_trump_skill(int index);
  inline ::CfgTrump::TrumpSkillInfo* add_trump_skill();
  inline const ::google::protobuf::RepeatedPtrField< ::CfgTrump::TrumpSkillInfo >&
      trump_skill() const;
  inline ::google::protobuf::RepeatedPtrField< ::CfgTrump::TrumpSkillInfo >*
      mutable_trump_skill();

  // @@protoc_insertion_point(class_scope:CfgTrump.TrumpSkill)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::CfgTrump::TrumpSkillInfo > trump_skill_;
  friend void  protobuf_AddDesc_CfgTrump_2eproto();
  friend void protobuf_AssignDesc_CfgTrump_2eproto();
  friend void protobuf_ShutdownFile_CfgTrump_2eproto();

  void InitAsDefaultInstance();
  static TrumpSkill* default_instance_;
};
// ===================================================================


// ===================================================================

// TrumpInfo

// required int32 level = 1;
inline bool TrumpInfo::has_level() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TrumpInfo::set_has_level() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TrumpInfo::clear_has_level() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TrumpInfo::clear_level() {
  level_ = 0;
  clear_has_level();
}
inline ::google::protobuf::int32 TrumpInfo::level() const {
  // @@protoc_insertion_point(field_get:CfgTrump.TrumpInfo.level)
  return level_;
}
inline void TrumpInfo::set_level(::google::protobuf::int32 value) {
  set_has_level();
  level_ = value;
  // @@protoc_insertion_point(field_set:CfgTrump.TrumpInfo.level)
}

// required int32 star = 2;
inline bool TrumpInfo::has_star() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TrumpInfo::set_has_star() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TrumpInfo::clear_has_star() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TrumpInfo::clear_star() {
  star_ = 0;
  clear_has_star();
}
inline ::google::protobuf::int32 TrumpInfo::star() const {
  // @@protoc_insertion_point(field_get:CfgTrump.TrumpInfo.star)
  return star_;
}
inline void TrumpInfo::set_star(::google::protobuf::int32 value) {
  set_has_star();
  star_ = value;
  // @@protoc_insertion_point(field_set:CfgTrump.TrumpInfo.star)
}

// required int32 stage = 3;
inline bool TrumpInfo::has_stage() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void TrumpInfo::set_has_stage() {
  _has_bits_[0] |= 0x00000004u;
}
inline void TrumpInfo::clear_has_stage() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void TrumpInfo::clear_stage() {
  stage_ = 0;
  clear_has_stage();
}
inline ::google::protobuf::int32 TrumpInfo::stage() const {
  // @@protoc_insertion_point(field_get:CfgTrump.TrumpInfo.stage)
  return stage_;
}
inline void TrumpInfo::set_stage(::google::protobuf::int32 value) {
  set_has_stage();
  stage_ = value;
  // @@protoc_insertion_point(field_set:CfgTrump.TrumpInfo.stage)
}

// required int32 cost_item = 4;
inline bool TrumpInfo::has_cost_item() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void TrumpInfo::set_has_cost_item() {
  _has_bits_[0] |= 0x00000008u;
}
inline void TrumpInfo::clear_has_cost_item() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void TrumpInfo::clear_cost_item() {
  cost_item_ = 0;
  clear_has_cost_item();
}
inline ::google::protobuf::int32 TrumpInfo::cost_item() const {
  // @@protoc_insertion_point(field_get:CfgTrump.TrumpInfo.cost_item)
  return cost_item_;
}
inline void TrumpInfo::set_cost_item(::google::protobuf::int32 value) {
  set_has_cost_item();
  cost_item_ = value;
  // @@protoc_insertion_point(field_set:CfgTrump.TrumpInfo.cost_item)
}

// required int32 cost_count = 5;
inline bool TrumpInfo::has_cost_count() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void TrumpInfo::set_has_cost_count() {
  _has_bits_[0] |= 0x00000010u;
}
inline void TrumpInfo::clear_has_cost_count() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void TrumpInfo::clear_cost_count() {
  cost_count_ = 0;
  clear_has_cost_count();
}
inline ::google::protobuf::int32 TrumpInfo::cost_count() const {
  // @@protoc_insertion_point(field_get:CfgTrump.TrumpInfo.cost_count)
  return cost_count_;
}
inline void TrumpInfo::set_cost_count(::google::protobuf::int32 value) {
  set_has_cost_count();
  cost_count_ = value;
  // @@protoc_insertion_point(field_set:CfgTrump.TrumpInfo.cost_count)
}

// repeated .CfgCommon.Attribute attr = 6;
inline int TrumpInfo::attr_size() const {
  return attr_.size();
}
inline void TrumpInfo::clear_attr() {
  attr_.Clear();
}
inline const ::CfgCommon::Attribute& TrumpInfo::attr(int index) const {
  // @@protoc_insertion_point(field_get:CfgTrump.TrumpInfo.attr)
  return attr_.Get(index);
}
inline ::CfgCommon::Attribute* TrumpInfo::mutable_attr(int index) {
  // @@protoc_insertion_point(field_mutable:CfgTrump.TrumpInfo.attr)
  return attr_.Mutable(index);
}
inline ::CfgCommon::Attribute* TrumpInfo::add_attr() {
  // @@protoc_insertion_point(field_add:CfgTrump.TrumpInfo.attr)
  return attr_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::CfgCommon::Attribute >&
TrumpInfo::attr() const {
  // @@protoc_insertion_point(field_list:CfgTrump.TrumpInfo.attr)
  return attr_;
}
inline ::google::protobuf::RepeatedPtrField< ::CfgCommon::Attribute >*
TrumpInfo::mutable_attr() {
  // @@protoc_insertion_point(field_mutable_list:CfgTrump.TrumpInfo.attr)
  return &attr_;
}

// -------------------------------------------------------------------

// Trumps

// repeated .CfgTrump.TrumpInfo trump = 1;
inline int Trumps::trump_size() const {
  return trump_.size();
}
inline void Trumps::clear_trump() {
  trump_.Clear();
}
inline const ::CfgTrump::TrumpInfo& Trumps::trump(int index) const {
  // @@protoc_insertion_point(field_get:CfgTrump.Trumps.trump)
  return trump_.Get(index);
}
inline ::CfgTrump::TrumpInfo* Trumps::mutable_trump(int index) {
  // @@protoc_insertion_point(field_mutable:CfgTrump.Trumps.trump)
  return trump_.Mutable(index);
}
inline ::CfgTrump::TrumpInfo* Trumps::add_trump() {
  // @@protoc_insertion_point(field_add:CfgTrump.Trumps.trump)
  return trump_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::CfgTrump::TrumpInfo >&
Trumps::trump() const {
  // @@protoc_insertion_point(field_list:CfgTrump.Trumps.trump)
  return trump_;
}
inline ::google::protobuf::RepeatedPtrField< ::CfgTrump::TrumpInfo >*
Trumps::mutable_trump() {
  // @@protoc_insertion_point(field_mutable_list:CfgTrump.Trumps.trump)
  return &trump_;
}

// -------------------------------------------------------------------

// TrumpSkillInfo

// required int32 stage = 1;
inline bool TrumpSkillInfo::has_stage() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TrumpSkillInfo::set_has_stage() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TrumpSkillInfo::clear_has_stage() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TrumpSkillInfo::clear_stage() {
  stage_ = 0;
  clear_has_stage();
}
inline ::google::protobuf::int32 TrumpSkillInfo::stage() const {
  // @@protoc_insertion_point(field_get:CfgTrump.TrumpSkillInfo.stage)
  return stage_;
}
inline void TrumpSkillInfo::set_stage(::google::protobuf::int32 value) {
  set_has_stage();
  stage_ = value;
  // @@protoc_insertion_point(field_set:CfgTrump.TrumpSkillInfo.stage)
}

// repeated .CfgCommon.Attribute attr = 2;
inline int TrumpSkillInfo::attr_size() const {
  return attr_.size();
}
inline void TrumpSkillInfo::clear_attr() {
  attr_.Clear();
}
inline const ::CfgCommon::Attribute& TrumpSkillInfo::attr(int index) const {
  // @@protoc_insertion_point(field_get:CfgTrump.TrumpSkillInfo.attr)
  return attr_.Get(index);
}
inline ::CfgCommon::Attribute* TrumpSkillInfo::mutable_attr(int index) {
  // @@protoc_insertion_point(field_mutable:CfgTrump.TrumpSkillInfo.attr)
  return attr_.Mutable(index);
}
inline ::CfgCommon::Attribute* TrumpSkillInfo::add_attr() {
  // @@protoc_insertion_point(field_add:CfgTrump.TrumpSkillInfo.attr)
  return attr_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::CfgCommon::Attribute >&
TrumpSkillInfo::attr() const {
  // @@protoc_insertion_point(field_list:CfgTrump.TrumpSkillInfo.attr)
  return attr_;
}
inline ::google::protobuf::RepeatedPtrField< ::CfgCommon::Attribute >*
TrumpSkillInfo::mutable_attr() {
  // @@protoc_insertion_point(field_mutable_list:CfgTrump.TrumpSkillInfo.attr)
  return &attr_;
}

// -------------------------------------------------------------------

// TrumpSkill

// repeated .CfgTrump.TrumpSkillInfo trump_skill = 1;
inline int TrumpSkill::trump_skill_size() const {
  return trump_skill_.size();
}
inline void TrumpSkill::clear_trump_skill() {
  trump_skill_.Clear();
}
inline const ::CfgTrump::TrumpSkillInfo& TrumpSkill::trump_skill(int index) const {
  // @@protoc_insertion_point(field_get:CfgTrump.TrumpSkill.trump_skill)
  return trump_skill_.Get(index);
}
inline ::CfgTrump::TrumpSkillInfo* TrumpSkill::mutable_trump_skill(int index) {
  // @@protoc_insertion_point(field_mutable:CfgTrump.TrumpSkill.trump_skill)
  return trump_skill_.Mutable(index);
}
inline ::CfgTrump::TrumpSkillInfo* TrumpSkill::add_trump_skill() {
  // @@protoc_insertion_point(field_add:CfgTrump.TrumpSkill.trump_skill)
  return trump_skill_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::CfgTrump::TrumpSkillInfo >&
TrumpSkill::trump_skill() const {
  // @@protoc_insertion_point(field_list:CfgTrump.TrumpSkill.trump_skill)
  return trump_skill_;
}
inline ::google::protobuf::RepeatedPtrField< ::CfgTrump::TrumpSkillInfo >*
TrumpSkill::mutable_trump_skill() {
  // @@protoc_insertion_point(field_mutable_list:CfgTrump.TrumpSkill.trump_skill)
  return &trump_skill_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace CfgTrump

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_CfgTrump_2eproto__INCLUDED
