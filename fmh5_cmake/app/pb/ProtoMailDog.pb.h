// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProtoMailDog.proto

#ifndef PROTOBUF_ProtoMailDog_2eproto__INCLUDED
#define PROTOBUF_ProtoMailDog_2eproto__INCLUDED

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
#include "DataCommon.pb.h"
// @@protoc_insertion_point(includes)

namespace ProtoMailDog {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ProtoMailDog_2eproto();
void protobuf_AssignDesc_ProtoMailDog_2eproto();
void protobuf_ShutdownFile_ProtoMailDog_2eproto();

class MaidDogCPP;
class ProsperityValueCPP;
class GetMailDogInfoReq;
class GetMailDogInfoResp;

// ===================================================================

class MaidDogCPP : public ::google::protobuf::Message {
 public:
  MaidDogCPP();
  virtual ~MaidDogCPP();

  MaidDogCPP(const MaidDogCPP& from);

  inline MaidDogCPP& operator=(const MaidDogCPP& from) {
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
  static const MaidDogCPP& default_instance();

  void Swap(MaidDogCPP* other);

  // implements Message ----------------------------------------------

  MaidDogCPP* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MaidDogCPP& from);
  void MergeFrom(const MaidDogCPP& from);
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

  // required uint32 value = 2;
  inline bool has_value() const;
  inline void clear_value();
  static const int kValueFieldNumber = 2;
  inline ::google::protobuf::uint32 value() const;
  inline void set_value(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:ProtoMailDog.MaidDogCPP)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_value();
  inline void clear_has_value();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 value_;
  friend void  protobuf_AddDesc_ProtoMailDog_2eproto();
  friend void protobuf_AssignDesc_ProtoMailDog_2eproto();
  friend void protobuf_ShutdownFile_ProtoMailDog_2eproto();

  void InitAsDefaultInstance();
  static MaidDogCPP* default_instance_;
};
// -------------------------------------------------------------------

class ProsperityValueCPP : public ::google::protobuf::Message {
 public:
  ProsperityValueCPP();
  virtual ~ProsperityValueCPP();

  ProsperityValueCPP(const ProsperityValueCPP& from);

  inline ProsperityValueCPP& operator=(const ProsperityValueCPP& from) {
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
  static const ProsperityValueCPP& default_instance();

  void Swap(ProsperityValueCPP* other);

  // implements Message ----------------------------------------------

  ProsperityValueCPP* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ProsperityValueCPP& from);
  void MergeFrom(const ProsperityValueCPP& from);
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

  // required uint32 prosperity = 1;
  inline bool has_prosperity() const;
  inline void clear_prosperity();
  static const int kProsperityFieldNumber = 1;
  inline ::google::protobuf::uint32 prosperity() const;
  inline void set_prosperity(::google::protobuf::uint32 value);

  // optional uint32 rewardts = 2;
  inline bool has_rewardts() const;
  inline void clear_rewardts();
  static const int kRewardtsFieldNumber = 2;
  inline ::google::protobuf::uint32 rewardts() const;
  inline void set_rewardts(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:ProtoMailDog.ProsperityValueCPP)
 private:
  inline void set_has_prosperity();
  inline void clear_has_prosperity();
  inline void set_has_rewardts();
  inline void clear_has_rewardts();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 prosperity_;
  ::google::protobuf::uint32 rewardts_;
  friend void  protobuf_AddDesc_ProtoMailDog_2eproto();
  friend void protobuf_AssignDesc_ProtoMailDog_2eproto();
  friend void protobuf_ShutdownFile_ProtoMailDog_2eproto();

  void InitAsDefaultInstance();
  static ProsperityValueCPP* default_instance_;
};
// -------------------------------------------------------------------

class GetMailDogInfoReq : public ::google::protobuf::Message {
 public:
  GetMailDogInfoReq();
  virtual ~GetMailDogInfoReq();

  GetMailDogInfoReq(const GetMailDogInfoReq& from);

  inline GetMailDogInfoReq& operator=(const GetMailDogInfoReq& from) {
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
  static const GetMailDogInfoReq& default_instance();

  void Swap(GetMailDogInfoReq* other);

  // implements Message ----------------------------------------------

  GetMailDogInfoReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GetMailDogInfoReq& from);
  void MergeFrom(const GetMailDogInfoReq& from);
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

  // @@protoc_insertion_point(class_scope:ProtoMailDog.GetMailDogInfoReq)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_ProtoMailDog_2eproto();
  friend void protobuf_AssignDesc_ProtoMailDog_2eproto();
  friend void protobuf_ShutdownFile_ProtoMailDog_2eproto();

  void InitAsDefaultInstance();
  static GetMailDogInfoReq* default_instance_;
};
// -------------------------------------------------------------------

class GetMailDogInfoResp : public ::google::protobuf::Message {
 public:
  GetMailDogInfoResp();
  virtual ~GetMailDogInfoResp();

  GetMailDogInfoResp(const GetMailDogInfoResp& from);

  inline GetMailDogInfoResp& operator=(const GetMailDogInfoResp& from) {
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
  static const GetMailDogInfoResp& default_instance();

  void Swap(GetMailDogInfoResp* other);

  // implements Message ----------------------------------------------

  GetMailDogInfoResp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GetMailDogInfoResp& from);
  void MergeFrom(const GetMailDogInfoResp& from);
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

  // repeated .ProtoMailDog.MaidDogCPP dog = 1;
  inline int dog_size() const;
  inline void clear_dog();
  static const int kDogFieldNumber = 1;
  inline const ::ProtoMailDog::MaidDogCPP& dog(int index) const;
  inline ::ProtoMailDog::MaidDogCPP* mutable_dog(int index);
  inline ::ProtoMailDog::MaidDogCPP* add_dog();
  inline const ::google::protobuf::RepeatedPtrField< ::ProtoMailDog::MaidDogCPP >&
      dog() const;
  inline ::google::protobuf::RepeatedPtrField< ::ProtoMailDog::MaidDogCPP >*
      mutable_dog();

  // required .ProtoMailDog.ProsperityValueCPP prosperity = 2;
  inline bool has_prosperity() const;
  inline void clear_prosperity();
  static const int kProsperityFieldNumber = 2;
  inline const ::ProtoMailDog::ProsperityValueCPP& prosperity() const;
  inline ::ProtoMailDog::ProsperityValueCPP* mutable_prosperity();
  inline ::ProtoMailDog::ProsperityValueCPP* release_prosperity();
  inline void set_allocated_prosperity(::ProtoMailDog::ProsperityValueCPP* prosperity);

  // optional .DataCommon.CommonItemsCPP commons = 3;
  inline bool has_commons() const;
  inline void clear_commons();
  static const int kCommonsFieldNumber = 3;
  inline const ::DataCommon::CommonItemsCPP& commons() const;
  inline ::DataCommon::CommonItemsCPP* mutable_commons();
  inline ::DataCommon::CommonItemsCPP* release_commons();
  inline void set_allocated_commons(::DataCommon::CommonItemsCPP* commons);

  // @@protoc_insertion_point(class_scope:ProtoMailDog.GetMailDogInfoResp)
 private:
  inline void set_has_prosperity();
  inline void clear_has_prosperity();
  inline void set_has_commons();
  inline void clear_has_commons();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::ProtoMailDog::MaidDogCPP > dog_;
  ::ProtoMailDog::ProsperityValueCPP* prosperity_;
  ::DataCommon::CommonItemsCPP* commons_;
  friend void  protobuf_AddDesc_ProtoMailDog_2eproto();
  friend void protobuf_AssignDesc_ProtoMailDog_2eproto();
  friend void protobuf_ShutdownFile_ProtoMailDog_2eproto();

  void InitAsDefaultInstance();
  static GetMailDogInfoResp* default_instance_;
};
// ===================================================================


// ===================================================================

// MaidDogCPP

// required uint32 id = 1;
inline bool MaidDogCPP::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MaidDogCPP::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MaidDogCPP::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MaidDogCPP::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 MaidDogCPP::id() const {
  // @@protoc_insertion_point(field_get:ProtoMailDog.MaidDogCPP.id)
  return id_;
}
inline void MaidDogCPP::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:ProtoMailDog.MaidDogCPP.id)
}

// required uint32 value = 2;
inline bool MaidDogCPP::has_value() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MaidDogCPP::set_has_value() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MaidDogCPP::clear_has_value() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MaidDogCPP::clear_value() {
  value_ = 0u;
  clear_has_value();
}
inline ::google::protobuf::uint32 MaidDogCPP::value() const {
  // @@protoc_insertion_point(field_get:ProtoMailDog.MaidDogCPP.value)
  return value_;
}
inline void MaidDogCPP::set_value(::google::protobuf::uint32 value) {
  set_has_value();
  value_ = value;
  // @@protoc_insertion_point(field_set:ProtoMailDog.MaidDogCPP.value)
}

// -------------------------------------------------------------------

// ProsperityValueCPP

// required uint32 prosperity = 1;
inline bool ProsperityValueCPP::has_prosperity() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ProsperityValueCPP::set_has_prosperity() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ProsperityValueCPP::clear_has_prosperity() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ProsperityValueCPP::clear_prosperity() {
  prosperity_ = 0u;
  clear_has_prosperity();
}
inline ::google::protobuf::uint32 ProsperityValueCPP::prosperity() const {
  // @@protoc_insertion_point(field_get:ProtoMailDog.ProsperityValueCPP.prosperity)
  return prosperity_;
}
inline void ProsperityValueCPP::set_prosperity(::google::protobuf::uint32 value) {
  set_has_prosperity();
  prosperity_ = value;
  // @@protoc_insertion_point(field_set:ProtoMailDog.ProsperityValueCPP.prosperity)
}

// optional uint32 rewardts = 2;
inline bool ProsperityValueCPP::has_rewardts() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ProsperityValueCPP::set_has_rewardts() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ProsperityValueCPP::clear_has_rewardts() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ProsperityValueCPP::clear_rewardts() {
  rewardts_ = 0u;
  clear_has_rewardts();
}
inline ::google::protobuf::uint32 ProsperityValueCPP::rewardts() const {
  // @@protoc_insertion_point(field_get:ProtoMailDog.ProsperityValueCPP.rewardts)
  return rewardts_;
}
inline void ProsperityValueCPP::set_rewardts(::google::protobuf::uint32 value) {
  set_has_rewardts();
  rewardts_ = value;
  // @@protoc_insertion_point(field_set:ProtoMailDog.ProsperityValueCPP.rewardts)
}

// -------------------------------------------------------------------

// GetMailDogInfoReq

// -------------------------------------------------------------------

// GetMailDogInfoResp

// repeated .ProtoMailDog.MaidDogCPP dog = 1;
inline int GetMailDogInfoResp::dog_size() const {
  return dog_.size();
}
inline void GetMailDogInfoResp::clear_dog() {
  dog_.Clear();
}
inline const ::ProtoMailDog::MaidDogCPP& GetMailDogInfoResp::dog(int index) const {
  // @@protoc_insertion_point(field_get:ProtoMailDog.GetMailDogInfoResp.dog)
  return dog_.Get(index);
}
inline ::ProtoMailDog::MaidDogCPP* GetMailDogInfoResp::mutable_dog(int index) {
  // @@protoc_insertion_point(field_mutable:ProtoMailDog.GetMailDogInfoResp.dog)
  return dog_.Mutable(index);
}
inline ::ProtoMailDog::MaidDogCPP* GetMailDogInfoResp::add_dog() {
  // @@protoc_insertion_point(field_add:ProtoMailDog.GetMailDogInfoResp.dog)
  return dog_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ProtoMailDog::MaidDogCPP >&
GetMailDogInfoResp::dog() const {
  // @@protoc_insertion_point(field_list:ProtoMailDog.GetMailDogInfoResp.dog)
  return dog_;
}
inline ::google::protobuf::RepeatedPtrField< ::ProtoMailDog::MaidDogCPP >*
GetMailDogInfoResp::mutable_dog() {
  // @@protoc_insertion_point(field_mutable_list:ProtoMailDog.GetMailDogInfoResp.dog)
  return &dog_;
}

// required .ProtoMailDog.ProsperityValueCPP prosperity = 2;
inline bool GetMailDogInfoResp::has_prosperity() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void GetMailDogInfoResp::set_has_prosperity() {
  _has_bits_[0] |= 0x00000002u;
}
inline void GetMailDogInfoResp::clear_has_prosperity() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void GetMailDogInfoResp::clear_prosperity() {
  if (prosperity_ != NULL) prosperity_->::ProtoMailDog::ProsperityValueCPP::Clear();
  clear_has_prosperity();
}
inline const ::ProtoMailDog::ProsperityValueCPP& GetMailDogInfoResp::prosperity() const {
  // @@protoc_insertion_point(field_get:ProtoMailDog.GetMailDogInfoResp.prosperity)
  return prosperity_ != NULL ? *prosperity_ : *default_instance_->prosperity_;
}
inline ::ProtoMailDog::ProsperityValueCPP* GetMailDogInfoResp::mutable_prosperity() {
  set_has_prosperity();
  if (prosperity_ == NULL) prosperity_ = new ::ProtoMailDog::ProsperityValueCPP;
  // @@protoc_insertion_point(field_mutable:ProtoMailDog.GetMailDogInfoResp.prosperity)
  return prosperity_;
}
inline ::ProtoMailDog::ProsperityValueCPP* GetMailDogInfoResp::release_prosperity() {
  clear_has_prosperity();
  ::ProtoMailDog::ProsperityValueCPP* temp = prosperity_;
  prosperity_ = NULL;
  return temp;
}
inline void GetMailDogInfoResp::set_allocated_prosperity(::ProtoMailDog::ProsperityValueCPP* prosperity) {
  delete prosperity_;
  prosperity_ = prosperity;
  if (prosperity) {
    set_has_prosperity();
  } else {
    clear_has_prosperity();
  }
  // @@protoc_insertion_point(field_set_allocated:ProtoMailDog.GetMailDogInfoResp.prosperity)
}

// optional .DataCommon.CommonItemsCPP commons = 3;
inline bool GetMailDogInfoResp::has_commons() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void GetMailDogInfoResp::set_has_commons() {
  _has_bits_[0] |= 0x00000004u;
}
inline void GetMailDogInfoResp::clear_has_commons() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void GetMailDogInfoResp::clear_commons() {
  if (commons_ != NULL) commons_->::DataCommon::CommonItemsCPP::Clear();
  clear_has_commons();
}
inline const ::DataCommon::CommonItemsCPP& GetMailDogInfoResp::commons() const {
  // @@protoc_insertion_point(field_get:ProtoMailDog.GetMailDogInfoResp.commons)
  return commons_ != NULL ? *commons_ : *default_instance_->commons_;
}
inline ::DataCommon::CommonItemsCPP* GetMailDogInfoResp::mutable_commons() {
  set_has_commons();
  if (commons_ == NULL) commons_ = new ::DataCommon::CommonItemsCPP;
  // @@protoc_insertion_point(field_mutable:ProtoMailDog.GetMailDogInfoResp.commons)
  return commons_;
}
inline ::DataCommon::CommonItemsCPP* GetMailDogInfoResp::release_commons() {
  clear_has_commons();
  ::DataCommon::CommonItemsCPP* temp = commons_;
  commons_ = NULL;
  return temp;
}
inline void GetMailDogInfoResp::set_allocated_commons(::DataCommon::CommonItemsCPP* commons) {
  delete commons_;
  commons_ = commons;
  if (commons) {
    set_has_commons();
  } else {
    clear_has_commons();
  }
  // @@protoc_insertion_point(field_set_allocated:ProtoMailDog.GetMailDogInfoResp.commons)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ProtoMailDog

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ProtoMailDog_2eproto__INCLUDED
