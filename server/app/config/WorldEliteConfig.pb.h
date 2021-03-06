// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: WorldEliteConfig.proto

#ifndef PROTOBUF_WorldEliteConfig_2eproto__INCLUDED
#define PROTOBUF_WorldEliteConfig_2eproto__INCLUDED

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

namespace WorldEliteConfig {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_WorldEliteConfig_2eproto();
void protobuf_AssignDesc_WorldEliteConfig_2eproto();
void protobuf_ShutdownFile_WorldEliteConfig_2eproto();

class NPCInfo;
class TypeNPC;
class OpenPlatformNPC;
class EliteNPC;

// ===================================================================

class NPCInfo : public ::google::protobuf::Message {
 public:
  NPCInfo();
  virtual ~NPCInfo();

  NPCInfo(const NPCInfo& from);

  inline NPCInfo& operator=(const NPCInfo& from) {
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
  static const NPCInfo& default_instance();

  void Swap(NPCInfo* other);

  // implements Message ----------------------------------------------

  NPCInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const NPCInfo& from);
  void MergeFrom(const NPCInfo& from);
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

  // required uint32 npcid = 1;
  inline bool has_npcid() const;
  inline void clear_npcid();
  static const int kNpcidFieldNumber = 1;
  inline ::google::protobuf::uint32 npcid() const;
  inline void set_npcid(::google::protobuf::uint32 value);

  // required uint32 count = 2;
  inline bool has_count() const;
  inline void clear_count();
  static const int kCountFieldNumber = 2;
  inline ::google::protobuf::uint32 count() const;
  inline void set_count(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:WorldEliteConfig.NPCInfo)
 private:
  inline void set_has_npcid();
  inline void clear_has_npcid();
  inline void set_has_count();
  inline void clear_has_count();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 npcid_;
  ::google::protobuf::uint32 count_;
  friend void  protobuf_AddDesc_WorldEliteConfig_2eproto();
  friend void protobuf_AssignDesc_WorldEliteConfig_2eproto();
  friend void protobuf_ShutdownFile_WorldEliteConfig_2eproto();

  void InitAsDefaultInstance();
  static NPCInfo* default_instance_;
};
// -------------------------------------------------------------------

class TypeNPC : public ::google::protobuf::Message {
 public:
  TypeNPC();
  virtual ~TypeNPC();

  TypeNPC(const TypeNPC& from);

  inline TypeNPC& operator=(const TypeNPC& from) {
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
  static const TypeNPC& default_instance();

  void Swap(TypeNPC* other);

  // implements Message ----------------------------------------------

  TypeNPC* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TypeNPC& from);
  void MergeFrom(const TypeNPC& from);
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

  // required uint32 type = 1;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline ::google::protobuf::uint32 type() const;
  inline void set_type(::google::protobuf::uint32 value);

  // repeated .WorldEliteConfig.NPCInfo npcs = 2;
  inline int npcs_size() const;
  inline void clear_npcs();
  static const int kNpcsFieldNumber = 2;
  inline const ::WorldEliteConfig::NPCInfo& npcs(int index) const;
  inline ::WorldEliteConfig::NPCInfo* mutable_npcs(int index);
  inline ::WorldEliteConfig::NPCInfo* add_npcs();
  inline const ::google::protobuf::RepeatedPtrField< ::WorldEliteConfig::NPCInfo >&
      npcs() const;
  inline ::google::protobuf::RepeatedPtrField< ::WorldEliteConfig::NPCInfo >*
      mutable_npcs();

  // @@protoc_insertion_point(class_scope:WorldEliteConfig.TypeNPC)
 private:
  inline void set_has_type();
  inline void clear_has_type();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::WorldEliteConfig::NPCInfo > npcs_;
  ::google::protobuf::uint32 type_;
  friend void  protobuf_AddDesc_WorldEliteConfig_2eproto();
  friend void protobuf_AssignDesc_WorldEliteConfig_2eproto();
  friend void protobuf_ShutdownFile_WorldEliteConfig_2eproto();

  void InitAsDefaultInstance();
  static TypeNPC* default_instance_;
};
// -------------------------------------------------------------------

class OpenPlatformNPC : public ::google::protobuf::Message {
 public:
  OpenPlatformNPC();
  virtual ~OpenPlatformNPC();

  OpenPlatformNPC(const OpenPlatformNPC& from);

  inline OpenPlatformNPC& operator=(const OpenPlatformNPC& from) {
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
  static const OpenPlatformNPC& default_instance();

  void Swap(OpenPlatformNPC* other);

  // implements Message ----------------------------------------------

  OpenPlatformNPC* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const OpenPlatformNPC& from);
  void MergeFrom(const OpenPlatformNPC& from);
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

  // repeated .WorldEliteConfig.TypeNPC npcall = 2;
  inline int npcall_size() const;
  inline void clear_npcall();
  static const int kNpcallFieldNumber = 2;
  inline const ::WorldEliteConfig::TypeNPC& npcall(int index) const;
  inline ::WorldEliteConfig::TypeNPC* mutable_npcall(int index);
  inline ::WorldEliteConfig::TypeNPC* add_npcall();
  inline const ::google::protobuf::RepeatedPtrField< ::WorldEliteConfig::TypeNPC >&
      npcall() const;
  inline ::google::protobuf::RepeatedPtrField< ::WorldEliteConfig::TypeNPC >*
      mutable_npcall();

  // @@protoc_insertion_point(class_scope:WorldEliteConfig.OpenPlatformNPC)
 private:
  inline void set_has_startday();
  inline void clear_has_startday();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::WorldEliteConfig::TypeNPC > npcall_;
  ::google::protobuf::uint32 startday_;
  friend void  protobuf_AddDesc_WorldEliteConfig_2eproto();
  friend void protobuf_AssignDesc_WorldEliteConfig_2eproto();
  friend void protobuf_ShutdownFile_WorldEliteConfig_2eproto();

  void InitAsDefaultInstance();
  static OpenPlatformNPC* default_instance_;
};
// -------------------------------------------------------------------

class EliteNPC : public ::google::protobuf::Message {
 public:
  EliteNPC();
  virtual ~EliteNPC();

  EliteNPC(const EliteNPC& from);

  inline EliteNPC& operator=(const EliteNPC& from) {
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
  static const EliteNPC& default_instance();

  void Swap(EliteNPC* other);

  // implements Message ----------------------------------------------

  EliteNPC* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const EliteNPC& from);
  void MergeFrom(const EliteNPC& from);
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

  // repeated .WorldEliteConfig.OpenPlatformNPC open_platform_npc = 1;
  inline int open_platform_npc_size() const;
  inline void clear_open_platform_npc();
  static const int kOpenPlatformNpcFieldNumber = 1;
  inline const ::WorldEliteConfig::OpenPlatformNPC& open_platform_npc(int index) const;
  inline ::WorldEliteConfig::OpenPlatformNPC* mutable_open_platform_npc(int index);
  inline ::WorldEliteConfig::OpenPlatformNPC* add_open_platform_npc();
  inline const ::google::protobuf::RepeatedPtrField< ::WorldEliteConfig::OpenPlatformNPC >&
      open_platform_npc() const;
  inline ::google::protobuf::RepeatedPtrField< ::WorldEliteConfig::OpenPlatformNPC >*
      mutable_open_platform_npc();

  // @@protoc_insertion_point(class_scope:WorldEliteConfig.EliteNPC)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::WorldEliteConfig::OpenPlatformNPC > open_platform_npc_;
  friend void  protobuf_AddDesc_WorldEliteConfig_2eproto();
  friend void protobuf_AssignDesc_WorldEliteConfig_2eproto();
  friend void protobuf_ShutdownFile_WorldEliteConfig_2eproto();

  void InitAsDefaultInstance();
  static EliteNPC* default_instance_;
};
// ===================================================================


// ===================================================================

// NPCInfo

// required uint32 npcid = 1;
inline bool NPCInfo::has_npcid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void NPCInfo::set_has_npcid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void NPCInfo::clear_has_npcid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void NPCInfo::clear_npcid() {
  npcid_ = 0u;
  clear_has_npcid();
}
inline ::google::protobuf::uint32 NPCInfo::npcid() const {
  // @@protoc_insertion_point(field_get:WorldEliteConfig.NPCInfo.npcid)
  return npcid_;
}
inline void NPCInfo::set_npcid(::google::protobuf::uint32 value) {
  set_has_npcid();
  npcid_ = value;
  // @@protoc_insertion_point(field_set:WorldEliteConfig.NPCInfo.npcid)
}

// required uint32 count = 2;
inline bool NPCInfo::has_count() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void NPCInfo::set_has_count() {
  _has_bits_[0] |= 0x00000002u;
}
inline void NPCInfo::clear_has_count() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void NPCInfo::clear_count() {
  count_ = 0u;
  clear_has_count();
}
inline ::google::protobuf::uint32 NPCInfo::count() const {
  // @@protoc_insertion_point(field_get:WorldEliteConfig.NPCInfo.count)
  return count_;
}
inline void NPCInfo::set_count(::google::protobuf::uint32 value) {
  set_has_count();
  count_ = value;
  // @@protoc_insertion_point(field_set:WorldEliteConfig.NPCInfo.count)
}

// -------------------------------------------------------------------

// TypeNPC

// required uint32 type = 1;
inline bool TypeNPC::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TypeNPC::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TypeNPC::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TypeNPC::clear_type() {
  type_ = 0u;
  clear_has_type();
}
inline ::google::protobuf::uint32 TypeNPC::type() const {
  // @@protoc_insertion_point(field_get:WorldEliteConfig.TypeNPC.type)
  return type_;
}
inline void TypeNPC::set_type(::google::protobuf::uint32 value) {
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:WorldEliteConfig.TypeNPC.type)
}

// repeated .WorldEliteConfig.NPCInfo npcs = 2;
inline int TypeNPC::npcs_size() const {
  return npcs_.size();
}
inline void TypeNPC::clear_npcs() {
  npcs_.Clear();
}
inline const ::WorldEliteConfig::NPCInfo& TypeNPC::npcs(int index) const {
  // @@protoc_insertion_point(field_get:WorldEliteConfig.TypeNPC.npcs)
  return npcs_.Get(index);
}
inline ::WorldEliteConfig::NPCInfo* TypeNPC::mutable_npcs(int index) {
  // @@protoc_insertion_point(field_mutable:WorldEliteConfig.TypeNPC.npcs)
  return npcs_.Mutable(index);
}
inline ::WorldEliteConfig::NPCInfo* TypeNPC::add_npcs() {
  // @@protoc_insertion_point(field_add:WorldEliteConfig.TypeNPC.npcs)
  return npcs_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::WorldEliteConfig::NPCInfo >&
TypeNPC::npcs() const {
  // @@protoc_insertion_point(field_list:WorldEliteConfig.TypeNPC.npcs)
  return npcs_;
}
inline ::google::protobuf::RepeatedPtrField< ::WorldEliteConfig::NPCInfo >*
TypeNPC::mutable_npcs() {
  // @@protoc_insertion_point(field_mutable_list:WorldEliteConfig.TypeNPC.npcs)
  return &npcs_;
}

// -------------------------------------------------------------------

// OpenPlatformNPC

// required uint32 startday = 1;
inline bool OpenPlatformNPC::has_startday() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void OpenPlatformNPC::set_has_startday() {
  _has_bits_[0] |= 0x00000001u;
}
inline void OpenPlatformNPC::clear_has_startday() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void OpenPlatformNPC::clear_startday() {
  startday_ = 0u;
  clear_has_startday();
}
inline ::google::protobuf::uint32 OpenPlatformNPC::startday() const {
  // @@protoc_insertion_point(field_get:WorldEliteConfig.OpenPlatformNPC.startday)
  return startday_;
}
inline void OpenPlatformNPC::set_startday(::google::protobuf::uint32 value) {
  set_has_startday();
  startday_ = value;
  // @@protoc_insertion_point(field_set:WorldEliteConfig.OpenPlatformNPC.startday)
}

// repeated .WorldEliteConfig.TypeNPC npcall = 2;
inline int OpenPlatformNPC::npcall_size() const {
  return npcall_.size();
}
inline void OpenPlatformNPC::clear_npcall() {
  npcall_.Clear();
}
inline const ::WorldEliteConfig::TypeNPC& OpenPlatformNPC::npcall(int index) const {
  // @@protoc_insertion_point(field_get:WorldEliteConfig.OpenPlatformNPC.npcall)
  return npcall_.Get(index);
}
inline ::WorldEliteConfig::TypeNPC* OpenPlatformNPC::mutable_npcall(int index) {
  // @@protoc_insertion_point(field_mutable:WorldEliteConfig.OpenPlatformNPC.npcall)
  return npcall_.Mutable(index);
}
inline ::WorldEliteConfig::TypeNPC* OpenPlatformNPC::add_npcall() {
  // @@protoc_insertion_point(field_add:WorldEliteConfig.OpenPlatformNPC.npcall)
  return npcall_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::WorldEliteConfig::TypeNPC >&
OpenPlatformNPC::npcall() const {
  // @@protoc_insertion_point(field_list:WorldEliteConfig.OpenPlatformNPC.npcall)
  return npcall_;
}
inline ::google::protobuf::RepeatedPtrField< ::WorldEliteConfig::TypeNPC >*
OpenPlatformNPC::mutable_npcall() {
  // @@protoc_insertion_point(field_mutable_list:WorldEliteConfig.OpenPlatformNPC.npcall)
  return &npcall_;
}

// -------------------------------------------------------------------

// EliteNPC

// repeated .WorldEliteConfig.OpenPlatformNPC open_platform_npc = 1;
inline int EliteNPC::open_platform_npc_size() const {
  return open_platform_npc_.size();
}
inline void EliteNPC::clear_open_platform_npc() {
  open_platform_npc_.Clear();
}
inline const ::WorldEliteConfig::OpenPlatformNPC& EliteNPC::open_platform_npc(int index) const {
  // @@protoc_insertion_point(field_get:WorldEliteConfig.EliteNPC.open_platform_npc)
  return open_platform_npc_.Get(index);
}
inline ::WorldEliteConfig::OpenPlatformNPC* EliteNPC::mutable_open_platform_npc(int index) {
  // @@protoc_insertion_point(field_mutable:WorldEliteConfig.EliteNPC.open_platform_npc)
  return open_platform_npc_.Mutable(index);
}
inline ::WorldEliteConfig::OpenPlatformNPC* EliteNPC::add_open_platform_npc() {
  // @@protoc_insertion_point(field_add:WorldEliteConfig.EliteNPC.open_platform_npc)
  return open_platform_npc_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::WorldEliteConfig::OpenPlatformNPC >&
EliteNPC::open_platform_npc() const {
  // @@protoc_insertion_point(field_list:WorldEliteConfig.EliteNPC.open_platform_npc)
  return open_platform_npc_;
}
inline ::google::protobuf::RepeatedPtrField< ::WorldEliteConfig::OpenPlatformNPC >*
EliteNPC::mutable_open_platform_npc() {
  // @@protoc_insertion_point(field_mutable_list:WorldEliteConfig.EliteNPC.open_platform_npc)
  return &open_platform_npc_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace WorldEliteConfig

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_WorldEliteConfig_2eproto__INCLUDED
