// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CfgReinCarnSheng.proto

#ifndef PROTOBUF_CfgReinCarnSheng_2eproto__INCLUDED
#define PROTOBUF_CfgReinCarnSheng_2eproto__INCLUDED

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

namespace CfgReinCarnSheng {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_CfgReinCarnSheng_2eproto();
void protobuf_AssignDesc_CfgReinCarnSheng_2eproto();
void protobuf_ShutdownFile_CfgReinCarnSheng_2eproto();

class ShengMission;
class ShengMissions;

// ===================================================================

class ShengMission : public ::google::protobuf::Message {
 public:
  ShengMission();
  virtual ~ShengMission();

  ShengMission(const ShengMission& from);

  inline ShengMission& operator=(const ShengMission& from) {
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
  static const ShengMission& default_instance();

  void Swap(ShengMission* other);

  // implements Message ----------------------------------------------

  ShengMission* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ShengMission& from);
  void MergeFrom(const ShengMission& from);
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

  // required int32 part = 2;
  inline bool has_part() const;
  inline void clear_part();
  static const int kPartFieldNumber = 2;
  inline ::google::protobuf::int32 part() const;
  inline void set_part(::google::protobuf::int32 value);

  // required uint32 reincarnlevel = 3;
  inline bool has_reincarnlevel() const;
  inline void clear_reincarnlevel();
  static const int kReincarnlevelFieldNumber = 3;
  inline ::google::protobuf::uint32 reincarnlevel() const;
  inline void set_reincarnlevel(::google::protobuf::uint32 value);

  // repeated .CfgCommon.Attribute attr = 4;
  inline int attr_size() const;
  inline void clear_attr();
  static const int kAttrFieldNumber = 4;
  inline const ::CfgCommon::Attribute& attr(int index) const;
  inline ::CfgCommon::Attribute* mutable_attr(int index);
  inline ::CfgCommon::Attribute* add_attr();
  inline const ::google::protobuf::RepeatedPtrField< ::CfgCommon::Attribute >&
      attr() const;
  inline ::google::protobuf::RepeatedPtrField< ::CfgCommon::Attribute >*
      mutable_attr();

  // required uint32 rate = 5;
  inline bool has_rate() const;
  inline void clear_rate();
  static const int kRateFieldNumber = 5;
  inline ::google::protobuf::uint32 rate() const;
  inline void set_rate(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:CfgReinCarnSheng.ShengMission)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_part();
  inline void clear_has_part();
  inline void set_has_reincarnlevel();
  inline void clear_has_reincarnlevel();
  inline void set_has_rate();
  inline void clear_has_rate();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 id_;
  ::google::protobuf::int32 part_;
  ::google::protobuf::RepeatedPtrField< ::CfgCommon::Attribute > attr_;
  ::google::protobuf::uint32 reincarnlevel_;
  ::google::protobuf::uint32 rate_;
  friend void  protobuf_AddDesc_CfgReinCarnSheng_2eproto();
  friend void protobuf_AssignDesc_CfgReinCarnSheng_2eproto();
  friend void protobuf_ShutdownFile_CfgReinCarnSheng_2eproto();

  void InitAsDefaultInstance();
  static ShengMission* default_instance_;
};
// -------------------------------------------------------------------

class ShengMissions : public ::google::protobuf::Message {
 public:
  ShengMissions();
  virtual ~ShengMissions();

  ShengMissions(const ShengMissions& from);

  inline ShengMissions& operator=(const ShengMissions& from) {
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
  static const ShengMissions& default_instance();

  void Swap(ShengMissions* other);

  // implements Message ----------------------------------------------

  ShengMissions* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ShengMissions& from);
  void MergeFrom(const ShengMissions& from);
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

  // repeated .CfgReinCarnSheng.ShengMission sheng_mission = 1;
  inline int sheng_mission_size() const;
  inline void clear_sheng_mission();
  static const int kShengMissionFieldNumber = 1;
  inline const ::CfgReinCarnSheng::ShengMission& sheng_mission(int index) const;
  inline ::CfgReinCarnSheng::ShengMission* mutable_sheng_mission(int index);
  inline ::CfgReinCarnSheng::ShengMission* add_sheng_mission();
  inline const ::google::protobuf::RepeatedPtrField< ::CfgReinCarnSheng::ShengMission >&
      sheng_mission() const;
  inline ::google::protobuf::RepeatedPtrField< ::CfgReinCarnSheng::ShengMission >*
      mutable_sheng_mission();

  // @@protoc_insertion_point(class_scope:CfgReinCarnSheng.ShengMissions)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::CfgReinCarnSheng::ShengMission > sheng_mission_;
  friend void  protobuf_AddDesc_CfgReinCarnSheng_2eproto();
  friend void protobuf_AssignDesc_CfgReinCarnSheng_2eproto();
  friend void protobuf_ShutdownFile_CfgReinCarnSheng_2eproto();

  void InitAsDefaultInstance();
  static ShengMissions* default_instance_;
};
// ===================================================================


// ===================================================================

// ShengMission

// required uint32 id = 1;
inline bool ShengMission::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ShengMission::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ShengMission::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ShengMission::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 ShengMission::id() const {
  // @@protoc_insertion_point(field_get:CfgReinCarnSheng.ShengMission.id)
  return id_;
}
inline void ShengMission::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:CfgReinCarnSheng.ShengMission.id)
}

// required int32 part = 2;
inline bool ShengMission::has_part() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ShengMission::set_has_part() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ShengMission::clear_has_part() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ShengMission::clear_part() {
  part_ = 0;
  clear_has_part();
}
inline ::google::protobuf::int32 ShengMission::part() const {
  // @@protoc_insertion_point(field_get:CfgReinCarnSheng.ShengMission.part)
  return part_;
}
inline void ShengMission::set_part(::google::protobuf::int32 value) {
  set_has_part();
  part_ = value;
  // @@protoc_insertion_point(field_set:CfgReinCarnSheng.ShengMission.part)
}

// required uint32 reincarnlevel = 3;
inline bool ShengMission::has_reincarnlevel() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ShengMission::set_has_reincarnlevel() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ShengMission::clear_has_reincarnlevel() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ShengMission::clear_reincarnlevel() {
  reincarnlevel_ = 0u;
  clear_has_reincarnlevel();
}
inline ::google::protobuf::uint32 ShengMission::reincarnlevel() const {
  // @@protoc_insertion_point(field_get:CfgReinCarnSheng.ShengMission.reincarnlevel)
  return reincarnlevel_;
}
inline void ShengMission::set_reincarnlevel(::google::protobuf::uint32 value) {
  set_has_reincarnlevel();
  reincarnlevel_ = value;
  // @@protoc_insertion_point(field_set:CfgReinCarnSheng.ShengMission.reincarnlevel)
}

// repeated .CfgCommon.Attribute attr = 4;
inline int ShengMission::attr_size() const {
  return attr_.size();
}
inline void ShengMission::clear_attr() {
  attr_.Clear();
}
inline const ::CfgCommon::Attribute& ShengMission::attr(int index) const {
  // @@protoc_insertion_point(field_get:CfgReinCarnSheng.ShengMission.attr)
  return attr_.Get(index);
}
inline ::CfgCommon::Attribute* ShengMission::mutable_attr(int index) {
  // @@protoc_insertion_point(field_mutable:CfgReinCarnSheng.ShengMission.attr)
  return attr_.Mutable(index);
}
inline ::CfgCommon::Attribute* ShengMission::add_attr() {
  // @@protoc_insertion_point(field_add:CfgReinCarnSheng.ShengMission.attr)
  return attr_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::CfgCommon::Attribute >&
ShengMission::attr() const {
  // @@protoc_insertion_point(field_list:CfgReinCarnSheng.ShengMission.attr)
  return attr_;
}
inline ::google::protobuf::RepeatedPtrField< ::CfgCommon::Attribute >*
ShengMission::mutable_attr() {
  // @@protoc_insertion_point(field_mutable_list:CfgReinCarnSheng.ShengMission.attr)
  return &attr_;
}

// required uint32 rate = 5;
inline bool ShengMission::has_rate() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void ShengMission::set_has_rate() {
  _has_bits_[0] |= 0x00000010u;
}
inline void ShengMission::clear_has_rate() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void ShengMission::clear_rate() {
  rate_ = 0u;
  clear_has_rate();
}
inline ::google::protobuf::uint32 ShengMission::rate() const {
  // @@protoc_insertion_point(field_get:CfgReinCarnSheng.ShengMission.rate)
  return rate_;
}
inline void ShengMission::set_rate(::google::protobuf::uint32 value) {
  set_has_rate();
  rate_ = value;
  // @@protoc_insertion_point(field_set:CfgReinCarnSheng.ShengMission.rate)
}

// -------------------------------------------------------------------

// ShengMissions

// repeated .CfgReinCarnSheng.ShengMission sheng_mission = 1;
inline int ShengMissions::sheng_mission_size() const {
  return sheng_mission_.size();
}
inline void ShengMissions::clear_sheng_mission() {
  sheng_mission_.Clear();
}
inline const ::CfgReinCarnSheng::ShengMission& ShengMissions::sheng_mission(int index) const {
  // @@protoc_insertion_point(field_get:CfgReinCarnSheng.ShengMissions.sheng_mission)
  return sheng_mission_.Get(index);
}
inline ::CfgReinCarnSheng::ShengMission* ShengMissions::mutable_sheng_mission(int index) {
  // @@protoc_insertion_point(field_mutable:CfgReinCarnSheng.ShengMissions.sheng_mission)
  return sheng_mission_.Mutable(index);
}
inline ::CfgReinCarnSheng::ShengMission* ShengMissions::add_sheng_mission() {
  // @@protoc_insertion_point(field_add:CfgReinCarnSheng.ShengMissions.sheng_mission)
  return sheng_mission_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::CfgReinCarnSheng::ShengMission >&
ShengMissions::sheng_mission() const {
  // @@protoc_insertion_point(field_list:CfgReinCarnSheng.ShengMissions.sheng_mission)
  return sheng_mission_;
}
inline ::google::protobuf::RepeatedPtrField< ::CfgReinCarnSheng::ShengMission >*
ShengMissions::mutable_sheng_mission() {
  // @@protoc_insertion_point(field_mutable_list:CfgReinCarnSheng.ShengMissions.sheng_mission)
  return &sheng_mission_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace CfgReinCarnSheng

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_CfgReinCarnSheng_2eproto__INCLUDED