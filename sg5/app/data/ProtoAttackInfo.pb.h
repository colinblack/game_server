// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProtoAttackInfo.proto

#ifndef PROTOBUF_ProtoAttackInfo_2eproto__INCLUDED
#define PROTOBUF_ProtoAttackInfo_2eproto__INCLUDED

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
// @@protoc_insertion_point(includes)

namespace ProtoAttackInfo {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ProtoAttackInfo_2eproto();
void protobuf_AssignDesc_ProtoAttackInfo_2eproto();
void protobuf_ShutdownFile_ProtoAttackInfo_2eproto();

class ProtoAttackHero;
class ProtoAttackBuilding;
class ProtoAttackRes;
class ProtoAttackInfo;

// ===================================================================

class ProtoAttackHero : public ::google::protobuf::Message {
 public:
  ProtoAttackHero();
  virtual ~ProtoAttackHero();

  ProtoAttackHero(const ProtoAttackHero& from);

  inline ProtoAttackHero& operator=(const ProtoAttackHero& from) {
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
  static const ProtoAttackHero& default_instance();

  void Swap(ProtoAttackHero* other);

  // implements Message ----------------------------------------------

  ProtoAttackHero* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ProtoAttackHero& from);
  void MergeFrom(const ProtoAttackHero& from);
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

  // required uint32 ud = 1;
  inline bool has_ud() const;
  inline void clear_ud();
  static const int kUdFieldNumber = 1;
  inline ::google::protobuf::uint32 ud() const;
  inline void set_ud(::google::protobuf::uint32 value);

  // required uint32 hp = 2;
  inline bool has_hp() const;
  inline void clear_hp();
  static const int kHpFieldNumber = 2;
  inline ::google::protobuf::uint32 hp() const;
  inline void set_hp(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:ProtoAttackInfo.ProtoAttackHero)
 private:
  inline void set_has_ud();
  inline void clear_has_ud();
  inline void set_has_hp();
  inline void clear_has_hp();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 ud_;
  ::google::protobuf::uint32 hp_;
  friend void  protobuf_AddDesc_ProtoAttackInfo_2eproto();
  friend void protobuf_AssignDesc_ProtoAttackInfo_2eproto();
  friend void protobuf_ShutdownFile_ProtoAttackInfo_2eproto();

  void InitAsDefaultInstance();
  static ProtoAttackHero* default_instance_;
};
// -------------------------------------------------------------------

class ProtoAttackBuilding : public ::google::protobuf::Message {
 public:
  ProtoAttackBuilding();
  virtual ~ProtoAttackBuilding();

  ProtoAttackBuilding(const ProtoAttackBuilding& from);

  inline ProtoAttackBuilding& operator=(const ProtoAttackBuilding& from) {
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
  static const ProtoAttackBuilding& default_instance();

  void Swap(ProtoAttackBuilding* other);

  // implements Message ----------------------------------------------

  ProtoAttackBuilding* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ProtoAttackBuilding& from);
  void MergeFrom(const ProtoAttackBuilding& from);
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

  // required uint32 ud = 1;
  inline bool has_ud() const;
  inline void clear_ud();
  static const int kUdFieldNumber = 1;
  inline ::google::protobuf::uint32 ud() const;
  inline void set_ud(::google::protobuf::uint32 value);

  // required uint32 hp = 2;
  inline bool has_hp() const;
  inline void clear_hp();
  static const int kHpFieldNumber = 2;
  inline ::google::protobuf::uint32 hp() const;
  inline void set_hp(::google::protobuf::uint32 value);

  // required uint32 res = 3;
  inline bool has_res() const;
  inline void clear_res();
  static const int kResFieldNumber = 3;
  inline ::google::protobuf::uint32 res() const;
  inline void set_res(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:ProtoAttackInfo.ProtoAttackBuilding)
 private:
  inline void set_has_ud();
  inline void clear_has_ud();
  inline void set_has_hp();
  inline void clear_has_hp();
  inline void set_has_res();
  inline void clear_has_res();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 ud_;
  ::google::protobuf::uint32 hp_;
  ::google::protobuf::uint32 res_;
  friend void  protobuf_AddDesc_ProtoAttackInfo_2eproto();
  friend void protobuf_AssignDesc_ProtoAttackInfo_2eproto();
  friend void protobuf_ShutdownFile_ProtoAttackInfo_2eproto();

  void InitAsDefaultInstance();
  static ProtoAttackBuilding* default_instance_;
};
// -------------------------------------------------------------------

class ProtoAttackRes : public ::google::protobuf::Message {
 public:
  ProtoAttackRes();
  virtual ~ProtoAttackRes();

  ProtoAttackRes(const ProtoAttackRes& from);

  inline ProtoAttackRes& operator=(const ProtoAttackRes& from) {
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
  static const ProtoAttackRes& default_instance();

  void Swap(ProtoAttackRes* other);

  // implements Message ----------------------------------------------

  ProtoAttackRes* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ProtoAttackRes& from);
  void MergeFrom(const ProtoAttackRes& from);
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

  // @@protoc_insertion_point(class_scope:ProtoAttackInfo.ProtoAttackRes)
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
  friend void  protobuf_AddDesc_ProtoAttackInfo_2eproto();
  friend void protobuf_AssignDesc_ProtoAttackInfo_2eproto();
  friend void protobuf_ShutdownFile_ProtoAttackInfo_2eproto();

  void InitAsDefaultInstance();
  static ProtoAttackRes* default_instance_;
};
// -------------------------------------------------------------------

class ProtoAttackInfo : public ::google::protobuf::Message {
 public:
  ProtoAttackInfo();
  virtual ~ProtoAttackInfo();

  ProtoAttackInfo(const ProtoAttackInfo& from);

  inline ProtoAttackInfo& operator=(const ProtoAttackInfo& from) {
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
  static const ProtoAttackInfo& default_instance();

  void Swap(ProtoAttackInfo* other);

  // implements Message ----------------------------------------------

  ProtoAttackInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ProtoAttackInfo& from);
  void MergeFrom(const ProtoAttackInfo& from);
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

  // repeated .ProtoAttackInfo.ProtoAttackHero hero = 1;
  inline int hero_size() const;
  inline void clear_hero();
  static const int kHeroFieldNumber = 1;
  inline const ::ProtoAttackInfo::ProtoAttackHero& hero(int index) const;
  inline ::ProtoAttackInfo::ProtoAttackHero* mutable_hero(int index);
  inline ::ProtoAttackInfo::ProtoAttackHero* add_hero();
  inline const ::google::protobuf::RepeatedPtrField< ::ProtoAttackInfo::ProtoAttackHero >&
      hero() const;
  inline ::google::protobuf::RepeatedPtrField< ::ProtoAttackInfo::ProtoAttackHero >*
      mutable_hero();

  // repeated .ProtoAttackInfo.ProtoAttackBuilding building = 2;
  inline int building_size() const;
  inline void clear_building();
  static const int kBuildingFieldNumber = 2;
  inline const ::ProtoAttackInfo::ProtoAttackBuilding& building(int index) const;
  inline ::ProtoAttackInfo::ProtoAttackBuilding* mutable_building(int index);
  inline ::ProtoAttackInfo::ProtoAttackBuilding* add_building();
  inline const ::google::protobuf::RepeatedPtrField< ::ProtoAttackInfo::ProtoAttackBuilding >&
      building() const;
  inline ::google::protobuf::RepeatedPtrField< ::ProtoAttackInfo::ProtoAttackBuilding >*
      mutable_building();

  // repeated .ProtoAttackInfo.ProtoAttackRes res = 3;
  inline int res_size() const;
  inline void clear_res();
  static const int kResFieldNumber = 3;
  inline const ::ProtoAttackInfo::ProtoAttackRes& res(int index) const;
  inline ::ProtoAttackInfo::ProtoAttackRes* mutable_res(int index);
  inline ::ProtoAttackInfo::ProtoAttackRes* add_res();
  inline const ::google::protobuf::RepeatedPtrField< ::ProtoAttackInfo::ProtoAttackRes >&
      res() const;
  inline ::google::protobuf::RepeatedPtrField< ::ProtoAttackInfo::ProtoAttackRes >*
      mutable_res();

  // required uint32 attackts = 4;
  inline bool has_attackts() const;
  inline void clear_attackts();
  static const int kAttacktsFieldNumber = 4;
  inline ::google::protobuf::uint32 attackts() const;
  inline void set_attackts(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:ProtoAttackInfo.ProtoAttackInfo)
 private:
  inline void set_has_attackts();
  inline void clear_has_attackts();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::ProtoAttackInfo::ProtoAttackHero > hero_;
  ::google::protobuf::RepeatedPtrField< ::ProtoAttackInfo::ProtoAttackBuilding > building_;
  ::google::protobuf::RepeatedPtrField< ::ProtoAttackInfo::ProtoAttackRes > res_;
  ::google::protobuf::uint32 attackts_;
  friend void  protobuf_AddDesc_ProtoAttackInfo_2eproto();
  friend void protobuf_AssignDesc_ProtoAttackInfo_2eproto();
  friend void protobuf_ShutdownFile_ProtoAttackInfo_2eproto();

  void InitAsDefaultInstance();
  static ProtoAttackInfo* default_instance_;
};
// ===================================================================


// ===================================================================

// ProtoAttackHero

// required uint32 ud = 1;
inline bool ProtoAttackHero::has_ud() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ProtoAttackHero::set_has_ud() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ProtoAttackHero::clear_has_ud() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ProtoAttackHero::clear_ud() {
  ud_ = 0u;
  clear_has_ud();
}
inline ::google::protobuf::uint32 ProtoAttackHero::ud() const {
  // @@protoc_insertion_point(field_get:ProtoAttackInfo.ProtoAttackHero.ud)
  return ud_;
}
inline void ProtoAttackHero::set_ud(::google::protobuf::uint32 value) {
  set_has_ud();
  ud_ = value;
  // @@protoc_insertion_point(field_set:ProtoAttackInfo.ProtoAttackHero.ud)
}

// required uint32 hp = 2;
inline bool ProtoAttackHero::has_hp() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ProtoAttackHero::set_has_hp() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ProtoAttackHero::clear_has_hp() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ProtoAttackHero::clear_hp() {
  hp_ = 0u;
  clear_has_hp();
}
inline ::google::protobuf::uint32 ProtoAttackHero::hp() const {
  // @@protoc_insertion_point(field_get:ProtoAttackInfo.ProtoAttackHero.hp)
  return hp_;
}
inline void ProtoAttackHero::set_hp(::google::protobuf::uint32 value) {
  set_has_hp();
  hp_ = value;
  // @@protoc_insertion_point(field_set:ProtoAttackInfo.ProtoAttackHero.hp)
}

// -------------------------------------------------------------------

// ProtoAttackBuilding

// required uint32 ud = 1;
inline bool ProtoAttackBuilding::has_ud() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ProtoAttackBuilding::set_has_ud() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ProtoAttackBuilding::clear_has_ud() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ProtoAttackBuilding::clear_ud() {
  ud_ = 0u;
  clear_has_ud();
}
inline ::google::protobuf::uint32 ProtoAttackBuilding::ud() const {
  // @@protoc_insertion_point(field_get:ProtoAttackInfo.ProtoAttackBuilding.ud)
  return ud_;
}
inline void ProtoAttackBuilding::set_ud(::google::protobuf::uint32 value) {
  set_has_ud();
  ud_ = value;
  // @@protoc_insertion_point(field_set:ProtoAttackInfo.ProtoAttackBuilding.ud)
}

// required uint32 hp = 2;
inline bool ProtoAttackBuilding::has_hp() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ProtoAttackBuilding::set_has_hp() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ProtoAttackBuilding::clear_has_hp() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ProtoAttackBuilding::clear_hp() {
  hp_ = 0u;
  clear_has_hp();
}
inline ::google::protobuf::uint32 ProtoAttackBuilding::hp() const {
  // @@protoc_insertion_point(field_get:ProtoAttackInfo.ProtoAttackBuilding.hp)
  return hp_;
}
inline void ProtoAttackBuilding::set_hp(::google::protobuf::uint32 value) {
  set_has_hp();
  hp_ = value;
  // @@protoc_insertion_point(field_set:ProtoAttackInfo.ProtoAttackBuilding.hp)
}

// required uint32 res = 3;
inline bool ProtoAttackBuilding::has_res() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ProtoAttackBuilding::set_has_res() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ProtoAttackBuilding::clear_has_res() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ProtoAttackBuilding::clear_res() {
  res_ = 0u;
  clear_has_res();
}
inline ::google::protobuf::uint32 ProtoAttackBuilding::res() const {
  // @@protoc_insertion_point(field_get:ProtoAttackInfo.ProtoAttackBuilding.res)
  return res_;
}
inline void ProtoAttackBuilding::set_res(::google::protobuf::uint32 value) {
  set_has_res();
  res_ = value;
  // @@protoc_insertion_point(field_set:ProtoAttackInfo.ProtoAttackBuilding.res)
}

// -------------------------------------------------------------------

// ProtoAttackRes

// required uint32 id = 1;
inline bool ProtoAttackRes::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ProtoAttackRes::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ProtoAttackRes::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ProtoAttackRes::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 ProtoAttackRes::id() const {
  // @@protoc_insertion_point(field_get:ProtoAttackInfo.ProtoAttackRes.id)
  return id_;
}
inline void ProtoAttackRes::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:ProtoAttackInfo.ProtoAttackRes.id)
}

// required uint32 count = 2;
inline bool ProtoAttackRes::has_count() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ProtoAttackRes::set_has_count() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ProtoAttackRes::clear_has_count() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ProtoAttackRes::clear_count() {
  count_ = 0u;
  clear_has_count();
}
inline ::google::protobuf::uint32 ProtoAttackRes::count() const {
  // @@protoc_insertion_point(field_get:ProtoAttackInfo.ProtoAttackRes.count)
  return count_;
}
inline void ProtoAttackRes::set_count(::google::protobuf::uint32 value) {
  set_has_count();
  count_ = value;
  // @@protoc_insertion_point(field_set:ProtoAttackInfo.ProtoAttackRes.count)
}

// -------------------------------------------------------------------

// ProtoAttackInfo

// repeated .ProtoAttackInfo.ProtoAttackHero hero = 1;
inline int ProtoAttackInfo::hero_size() const {
  return hero_.size();
}
inline void ProtoAttackInfo::clear_hero() {
  hero_.Clear();
}
inline const ::ProtoAttackInfo::ProtoAttackHero& ProtoAttackInfo::hero(int index) const {
  // @@protoc_insertion_point(field_get:ProtoAttackInfo.ProtoAttackInfo.hero)
  return hero_.Get(index);
}
inline ::ProtoAttackInfo::ProtoAttackHero* ProtoAttackInfo::mutable_hero(int index) {
  // @@protoc_insertion_point(field_mutable:ProtoAttackInfo.ProtoAttackInfo.hero)
  return hero_.Mutable(index);
}
inline ::ProtoAttackInfo::ProtoAttackHero* ProtoAttackInfo::add_hero() {
  // @@protoc_insertion_point(field_add:ProtoAttackInfo.ProtoAttackInfo.hero)
  return hero_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ProtoAttackInfo::ProtoAttackHero >&
ProtoAttackInfo::hero() const {
  // @@protoc_insertion_point(field_list:ProtoAttackInfo.ProtoAttackInfo.hero)
  return hero_;
}
inline ::google::protobuf::RepeatedPtrField< ::ProtoAttackInfo::ProtoAttackHero >*
ProtoAttackInfo::mutable_hero() {
  // @@protoc_insertion_point(field_mutable_list:ProtoAttackInfo.ProtoAttackInfo.hero)
  return &hero_;
}

// repeated .ProtoAttackInfo.ProtoAttackBuilding building = 2;
inline int ProtoAttackInfo::building_size() const {
  return building_.size();
}
inline void ProtoAttackInfo::clear_building() {
  building_.Clear();
}
inline const ::ProtoAttackInfo::ProtoAttackBuilding& ProtoAttackInfo::building(int index) const {
  // @@protoc_insertion_point(field_get:ProtoAttackInfo.ProtoAttackInfo.building)
  return building_.Get(index);
}
inline ::ProtoAttackInfo::ProtoAttackBuilding* ProtoAttackInfo::mutable_building(int index) {
  // @@protoc_insertion_point(field_mutable:ProtoAttackInfo.ProtoAttackInfo.building)
  return building_.Mutable(index);
}
inline ::ProtoAttackInfo::ProtoAttackBuilding* ProtoAttackInfo::add_building() {
  // @@protoc_insertion_point(field_add:ProtoAttackInfo.ProtoAttackInfo.building)
  return building_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ProtoAttackInfo::ProtoAttackBuilding >&
ProtoAttackInfo::building() const {
  // @@protoc_insertion_point(field_list:ProtoAttackInfo.ProtoAttackInfo.building)
  return building_;
}
inline ::google::protobuf::RepeatedPtrField< ::ProtoAttackInfo::ProtoAttackBuilding >*
ProtoAttackInfo::mutable_building() {
  // @@protoc_insertion_point(field_mutable_list:ProtoAttackInfo.ProtoAttackInfo.building)
  return &building_;
}

// repeated .ProtoAttackInfo.ProtoAttackRes res = 3;
inline int ProtoAttackInfo::res_size() const {
  return res_.size();
}
inline void ProtoAttackInfo::clear_res() {
  res_.Clear();
}
inline const ::ProtoAttackInfo::ProtoAttackRes& ProtoAttackInfo::res(int index) const {
  // @@protoc_insertion_point(field_get:ProtoAttackInfo.ProtoAttackInfo.res)
  return res_.Get(index);
}
inline ::ProtoAttackInfo::ProtoAttackRes* ProtoAttackInfo::mutable_res(int index) {
  // @@protoc_insertion_point(field_mutable:ProtoAttackInfo.ProtoAttackInfo.res)
  return res_.Mutable(index);
}
inline ::ProtoAttackInfo::ProtoAttackRes* ProtoAttackInfo::add_res() {
  // @@protoc_insertion_point(field_add:ProtoAttackInfo.ProtoAttackInfo.res)
  return res_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ProtoAttackInfo::ProtoAttackRes >&
ProtoAttackInfo::res() const {
  // @@protoc_insertion_point(field_list:ProtoAttackInfo.ProtoAttackInfo.res)
  return res_;
}
inline ::google::protobuf::RepeatedPtrField< ::ProtoAttackInfo::ProtoAttackRes >*
ProtoAttackInfo::mutable_res() {
  // @@protoc_insertion_point(field_mutable_list:ProtoAttackInfo.ProtoAttackInfo.res)
  return &res_;
}

// required uint32 attackts = 4;
inline bool ProtoAttackInfo::has_attackts() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ProtoAttackInfo::set_has_attackts() {
  _has_bits_[0] |= 0x00000008u;
}
inline void ProtoAttackInfo::clear_has_attackts() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void ProtoAttackInfo::clear_attackts() {
  attackts_ = 0u;
  clear_has_attackts();
}
inline ::google::protobuf::uint32 ProtoAttackInfo::attackts() const {
  // @@protoc_insertion_point(field_get:ProtoAttackInfo.ProtoAttackInfo.attackts)
  return attackts_;
}
inline void ProtoAttackInfo::set_attackts(::google::protobuf::uint32 value) {
  set_has_attackts();
  attackts_ = value;
  // @@protoc_insertion_point(field_set:ProtoAttackInfo.ProtoAttackInfo.attackts)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ProtoAttackInfo

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ProtoAttackInfo_2eproto__INCLUDED