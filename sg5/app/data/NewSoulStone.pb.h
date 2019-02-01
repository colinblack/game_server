// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: NewSoulStone.proto

#ifndef PROTOBUF_NewSoulStone_2eproto__INCLUDED
#define PROTOBUF_NewSoulStone_2eproto__INCLUDED

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

namespace NewSoulStone {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_NewSoulStone_2eproto();
void protobuf_AssignDesc_NewSoulStone_2eproto();
void protobuf_ShutdownFile_NewSoulStone_2eproto();

class OldSoulStoneA;
class NewSoulStoneP;
class NewSoulStoneP3;
class NewSoulStone;

// ===================================================================

class OldSoulStoneA : public ::google::protobuf::Message {
 public:
  OldSoulStoneA();
  virtual ~OldSoulStoneA();

  OldSoulStoneA(const OldSoulStoneA& from);

  inline OldSoulStoneA& operator=(const OldSoulStoneA& from) {
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
  static const OldSoulStoneA& default_instance();

  void Swap(OldSoulStoneA* other);

  // implements Message ----------------------------------------------

  OldSoulStoneA* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const OldSoulStoneA& from);
  void MergeFrom(const OldSoulStoneA& from);
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

  // repeated uint32 a = 2;
  inline int a_size() const;
  inline void clear_a();
  static const int kAFieldNumber = 2;
  inline ::google::protobuf::uint32 a(int index) const;
  inline void set_a(int index, ::google::protobuf::uint32 value);
  inline void add_a(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      a() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_a();

  // @@protoc_insertion_point(class_scope:NewSoulStone.OldSoulStoneA)
 private:
  inline void set_has_id();
  inline void clear_has_id();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > a_;
  ::google::protobuf::uint32 id_;
  friend void  protobuf_AddDesc_NewSoulStone_2eproto();
  friend void protobuf_AssignDesc_NewSoulStone_2eproto();
  friend void protobuf_ShutdownFile_NewSoulStone_2eproto();

  void InitAsDefaultInstance();
  static OldSoulStoneA* default_instance_;
};
// -------------------------------------------------------------------

class NewSoulStoneP : public ::google::protobuf::Message {
 public:
  NewSoulStoneP();
  virtual ~NewSoulStoneP();

  NewSoulStoneP(const NewSoulStoneP& from);

  inline NewSoulStoneP& operator=(const NewSoulStoneP& from) {
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
  static const NewSoulStoneP& default_instance();

  void Swap(NewSoulStoneP* other);

  // implements Message ----------------------------------------------

  NewSoulStoneP* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const NewSoulStoneP& from);
  void MergeFrom(const NewSoulStoneP& from);
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

  // required uint32 p = 2;
  inline bool has_p() const;
  inline void clear_p();
  static const int kPFieldNumber = 2;
  inline ::google::protobuf::uint32 p() const;
  inline void set_p(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:NewSoulStone.NewSoulStoneP)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_p();
  inline void clear_has_p();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 p_;
  friend void  protobuf_AddDesc_NewSoulStone_2eproto();
  friend void protobuf_AssignDesc_NewSoulStone_2eproto();
  friend void protobuf_ShutdownFile_NewSoulStone_2eproto();

  void InitAsDefaultInstance();
  static NewSoulStoneP* default_instance_;
};
// -------------------------------------------------------------------

class NewSoulStoneP3 : public ::google::protobuf::Message {
 public:
  NewSoulStoneP3();
  virtual ~NewSoulStoneP3();

  NewSoulStoneP3(const NewSoulStoneP3& from);

  inline NewSoulStoneP3& operator=(const NewSoulStoneP3& from) {
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
  static const NewSoulStoneP3& default_instance();

  void Swap(NewSoulStoneP3* other);

  // implements Message ----------------------------------------------

  NewSoulStoneP3* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const NewSoulStoneP3& from);
  void MergeFrom(const NewSoulStoneP3& from);
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

  // repeated .NewSoulStone.NewSoulStoneP newstone = 1;
  inline int newstone_size() const;
  inline void clear_newstone();
  static const int kNewstoneFieldNumber = 1;
  inline const ::NewSoulStone::NewSoulStoneP& newstone(int index) const;
  inline ::NewSoulStone::NewSoulStoneP* mutable_newstone(int index);
  inline ::NewSoulStone::NewSoulStoneP* add_newstone();
  inline const ::google::protobuf::RepeatedPtrField< ::NewSoulStone::NewSoulStoneP >&
      newstone() const;
  inline ::google::protobuf::RepeatedPtrField< ::NewSoulStone::NewSoulStoneP >*
      mutable_newstone();

  // required uint32 a = 2;
  inline bool has_a() const;
  inline void clear_a();
  static const int kAFieldNumber = 2;
  inline ::google::protobuf::uint32 a() const;
  inline void set_a(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:NewSoulStone.NewSoulStoneP3)
 private:
  inline void set_has_a();
  inline void clear_has_a();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::NewSoulStone::NewSoulStoneP > newstone_;
  ::google::protobuf::uint32 a_;
  friend void  protobuf_AddDesc_NewSoulStone_2eproto();
  friend void protobuf_AssignDesc_NewSoulStone_2eproto();
  friend void protobuf_ShutdownFile_NewSoulStone_2eproto();

  void InitAsDefaultInstance();
  static NewSoulStoneP3* default_instance_;
};
// -------------------------------------------------------------------

class NewSoulStone : public ::google::protobuf::Message {
 public:
  NewSoulStone();
  virtual ~NewSoulStone();

  NewSoulStone(const NewSoulStone& from);

  inline NewSoulStone& operator=(const NewSoulStone& from) {
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
  static const NewSoulStone& default_instance();

  void Swap(NewSoulStone* other);

  // implements Message ----------------------------------------------

  NewSoulStone* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const NewSoulStone& from);
  void MergeFrom(const NewSoulStone& from);
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

  // repeated .NewSoulStone.OldSoulStoneA oldstone = 1;
  inline int oldstone_size() const;
  inline void clear_oldstone();
  static const int kOldstoneFieldNumber = 1;
  inline const ::NewSoulStone::OldSoulStoneA& oldstone(int index) const;
  inline ::NewSoulStone::OldSoulStoneA* mutable_oldstone(int index);
  inline ::NewSoulStone::OldSoulStoneA* add_oldstone();
  inline const ::google::protobuf::RepeatedPtrField< ::NewSoulStone::OldSoulStoneA >&
      oldstone() const;
  inline ::google::protobuf::RepeatedPtrField< ::NewSoulStone::OldSoulStoneA >*
      mutable_oldstone();

  // repeated .NewSoulStone.NewSoulStoneP3 newstone3 = 2;
  inline int newstone3_size() const;
  inline void clear_newstone3();
  static const int kNewstone3FieldNumber = 2;
  inline const ::NewSoulStone::NewSoulStoneP3& newstone3(int index) const;
  inline ::NewSoulStone::NewSoulStoneP3* mutable_newstone3(int index);
  inline ::NewSoulStone::NewSoulStoneP3* add_newstone3();
  inline const ::google::protobuf::RepeatedPtrField< ::NewSoulStone::NewSoulStoneP3 >&
      newstone3() const;
  inline ::google::protobuf::RepeatedPtrField< ::NewSoulStone::NewSoulStoneP3 >*
      mutable_newstone3();

  // @@protoc_insertion_point(class_scope:NewSoulStone.NewSoulStone)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::NewSoulStone::OldSoulStoneA > oldstone_;
  ::google::protobuf::RepeatedPtrField< ::NewSoulStone::NewSoulStoneP3 > newstone3_;
  friend void  protobuf_AddDesc_NewSoulStone_2eproto();
  friend void protobuf_AssignDesc_NewSoulStone_2eproto();
  friend void protobuf_ShutdownFile_NewSoulStone_2eproto();

  void InitAsDefaultInstance();
  static NewSoulStone* default_instance_;
};
// ===================================================================


// ===================================================================

// OldSoulStoneA

// required uint32 id = 1;
inline bool OldSoulStoneA::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void OldSoulStoneA::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void OldSoulStoneA::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void OldSoulStoneA::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 OldSoulStoneA::id() const {
  // @@protoc_insertion_point(field_get:NewSoulStone.OldSoulStoneA.id)
  return id_;
}
inline void OldSoulStoneA::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:NewSoulStone.OldSoulStoneA.id)
}

// repeated uint32 a = 2;
inline int OldSoulStoneA::a_size() const {
  return a_.size();
}
inline void OldSoulStoneA::clear_a() {
  a_.Clear();
}
inline ::google::protobuf::uint32 OldSoulStoneA::a(int index) const {
  // @@protoc_insertion_point(field_get:NewSoulStone.OldSoulStoneA.a)
  return a_.Get(index);
}
inline void OldSoulStoneA::set_a(int index, ::google::protobuf::uint32 value) {
  a_.Set(index, value);
  // @@protoc_insertion_point(field_set:NewSoulStone.OldSoulStoneA.a)
}
inline void OldSoulStoneA::add_a(::google::protobuf::uint32 value) {
  a_.Add(value);
  // @@protoc_insertion_point(field_add:NewSoulStone.OldSoulStoneA.a)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
OldSoulStoneA::a() const {
  // @@protoc_insertion_point(field_list:NewSoulStone.OldSoulStoneA.a)
  return a_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
OldSoulStoneA::mutable_a() {
  // @@protoc_insertion_point(field_mutable_list:NewSoulStone.OldSoulStoneA.a)
  return &a_;
}

// -------------------------------------------------------------------

// NewSoulStoneP

// required uint32 id = 1;
inline bool NewSoulStoneP::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void NewSoulStoneP::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void NewSoulStoneP::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void NewSoulStoneP::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 NewSoulStoneP::id() const {
  // @@protoc_insertion_point(field_get:NewSoulStone.NewSoulStoneP.id)
  return id_;
}
inline void NewSoulStoneP::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:NewSoulStone.NewSoulStoneP.id)
}

// required uint32 p = 2;
inline bool NewSoulStoneP::has_p() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void NewSoulStoneP::set_has_p() {
  _has_bits_[0] |= 0x00000002u;
}
inline void NewSoulStoneP::clear_has_p() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void NewSoulStoneP::clear_p() {
  p_ = 0u;
  clear_has_p();
}
inline ::google::protobuf::uint32 NewSoulStoneP::p() const {
  // @@protoc_insertion_point(field_get:NewSoulStone.NewSoulStoneP.p)
  return p_;
}
inline void NewSoulStoneP::set_p(::google::protobuf::uint32 value) {
  set_has_p();
  p_ = value;
  // @@protoc_insertion_point(field_set:NewSoulStone.NewSoulStoneP.p)
}

// -------------------------------------------------------------------

// NewSoulStoneP3

// repeated .NewSoulStone.NewSoulStoneP newstone = 1;
inline int NewSoulStoneP3::newstone_size() const {
  return newstone_.size();
}
inline void NewSoulStoneP3::clear_newstone() {
  newstone_.Clear();
}
inline const ::NewSoulStone::NewSoulStoneP& NewSoulStoneP3::newstone(int index) const {
  // @@protoc_insertion_point(field_get:NewSoulStone.NewSoulStoneP3.newstone)
  return newstone_.Get(index);
}
inline ::NewSoulStone::NewSoulStoneP* NewSoulStoneP3::mutable_newstone(int index) {
  // @@protoc_insertion_point(field_mutable:NewSoulStone.NewSoulStoneP3.newstone)
  return newstone_.Mutable(index);
}
inline ::NewSoulStone::NewSoulStoneP* NewSoulStoneP3::add_newstone() {
  // @@protoc_insertion_point(field_add:NewSoulStone.NewSoulStoneP3.newstone)
  return newstone_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::NewSoulStone::NewSoulStoneP >&
NewSoulStoneP3::newstone() const {
  // @@protoc_insertion_point(field_list:NewSoulStone.NewSoulStoneP3.newstone)
  return newstone_;
}
inline ::google::protobuf::RepeatedPtrField< ::NewSoulStone::NewSoulStoneP >*
NewSoulStoneP3::mutable_newstone() {
  // @@protoc_insertion_point(field_mutable_list:NewSoulStone.NewSoulStoneP3.newstone)
  return &newstone_;
}

// required uint32 a = 2;
inline bool NewSoulStoneP3::has_a() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void NewSoulStoneP3::set_has_a() {
  _has_bits_[0] |= 0x00000002u;
}
inline void NewSoulStoneP3::clear_has_a() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void NewSoulStoneP3::clear_a() {
  a_ = 0u;
  clear_has_a();
}
inline ::google::protobuf::uint32 NewSoulStoneP3::a() const {
  // @@protoc_insertion_point(field_get:NewSoulStone.NewSoulStoneP3.a)
  return a_;
}
inline void NewSoulStoneP3::set_a(::google::protobuf::uint32 value) {
  set_has_a();
  a_ = value;
  // @@protoc_insertion_point(field_set:NewSoulStone.NewSoulStoneP3.a)
}

// -------------------------------------------------------------------

// NewSoulStone

// repeated .NewSoulStone.OldSoulStoneA oldstone = 1;
inline int NewSoulStone::oldstone_size() const {
  return oldstone_.size();
}
inline void NewSoulStone::clear_oldstone() {
  oldstone_.Clear();
}
inline const ::NewSoulStone::OldSoulStoneA& NewSoulStone::oldstone(int index) const {
  // @@protoc_insertion_point(field_get:NewSoulStone.NewSoulStone.oldstone)
  return oldstone_.Get(index);
}
inline ::NewSoulStone::OldSoulStoneA* NewSoulStone::mutable_oldstone(int index) {
  // @@protoc_insertion_point(field_mutable:NewSoulStone.NewSoulStone.oldstone)
  return oldstone_.Mutable(index);
}
inline ::NewSoulStone::OldSoulStoneA* NewSoulStone::add_oldstone() {
  // @@protoc_insertion_point(field_add:NewSoulStone.NewSoulStone.oldstone)
  return oldstone_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::NewSoulStone::OldSoulStoneA >&
NewSoulStone::oldstone() const {
  // @@protoc_insertion_point(field_list:NewSoulStone.NewSoulStone.oldstone)
  return oldstone_;
}
inline ::google::protobuf::RepeatedPtrField< ::NewSoulStone::OldSoulStoneA >*
NewSoulStone::mutable_oldstone() {
  // @@protoc_insertion_point(field_mutable_list:NewSoulStone.NewSoulStone.oldstone)
  return &oldstone_;
}

// repeated .NewSoulStone.NewSoulStoneP3 newstone3 = 2;
inline int NewSoulStone::newstone3_size() const {
  return newstone3_.size();
}
inline void NewSoulStone::clear_newstone3() {
  newstone3_.Clear();
}
inline const ::NewSoulStone::NewSoulStoneP3& NewSoulStone::newstone3(int index) const {
  // @@protoc_insertion_point(field_get:NewSoulStone.NewSoulStone.newstone3)
  return newstone3_.Get(index);
}
inline ::NewSoulStone::NewSoulStoneP3* NewSoulStone::mutable_newstone3(int index) {
  // @@protoc_insertion_point(field_mutable:NewSoulStone.NewSoulStone.newstone3)
  return newstone3_.Mutable(index);
}
inline ::NewSoulStone::NewSoulStoneP3* NewSoulStone::add_newstone3() {
  // @@protoc_insertion_point(field_add:NewSoulStone.NewSoulStone.newstone3)
  return newstone3_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::NewSoulStone::NewSoulStoneP3 >&
NewSoulStone::newstone3() const {
  // @@protoc_insertion_point(field_list:NewSoulStone.NewSoulStone.newstone3)
  return newstone3_;
}
inline ::google::protobuf::RepeatedPtrField< ::NewSoulStone::NewSoulStoneP3 >*
NewSoulStone::mutable_newstone3() {
  // @@protoc_insertion_point(field_mutable_list:NewSoulStone.NewSoulStone.newstone3)
  return &newstone3_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace NewSoulStone

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_NewSoulStone_2eproto__INCLUDED