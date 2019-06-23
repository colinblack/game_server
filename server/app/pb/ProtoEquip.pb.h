// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProtoEquip.proto

#ifndef PROTOBUF_ProtoEquip_2eproto__INCLUDED
#define PROTOBUF_ProtoEquip_2eproto__INCLUDED

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

namespace ProtoEquip {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ProtoEquip_2eproto();
void protobuf_AssignDesc_ProtoEquip_2eproto();
void protobuf_ShutdownFile_ProtoEquip_2eproto();

class SoldEquipReq;
class SoldEquipResp;
class OpenRepurchaseWindowReq;
class OpenRepurchaseWindowResp;

// ===================================================================

class SoldEquipReq : public ::google::protobuf::Message {
 public:
  SoldEquipReq();
  virtual ~SoldEquipReq();

  SoldEquipReq(const SoldEquipReq& from);

  inline SoldEquipReq& operator=(const SoldEquipReq& from) {
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
  static const SoldEquipReq& default_instance();

  void Swap(SoldEquipReq* other);

  // implements Message ----------------------------------------------

  SoldEquipReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SoldEquipReq& from);
  void MergeFrom(const SoldEquipReq& from);
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

  // required uint32 equd = 1;
  inline bool has_equd() const;
  inline void clear_equd();
  static const int kEqudFieldNumber = 1;
  inline ::google::protobuf::uint32 equd() const;
  inline void set_equd(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:ProtoEquip.SoldEquipReq)
 private:
  inline void set_has_equd();
  inline void clear_has_equd();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 equd_;
  friend void  protobuf_AddDesc_ProtoEquip_2eproto();
  friend void protobuf_AssignDesc_ProtoEquip_2eproto();
  friend void protobuf_ShutdownFile_ProtoEquip_2eproto();

  void InitAsDefaultInstance();
  static SoldEquipReq* default_instance_;
};
// -------------------------------------------------------------------

class SoldEquipResp : public ::google::protobuf::Message {
 public:
  SoldEquipResp();
  virtual ~SoldEquipResp();

  SoldEquipResp(const SoldEquipResp& from);

  inline SoldEquipResp& operator=(const SoldEquipResp& from) {
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
  static const SoldEquipResp& default_instance();

  void Swap(SoldEquipResp* other);

  // implements Message ----------------------------------------------

  SoldEquipResp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SoldEquipResp& from);
  void MergeFrom(const SoldEquipResp& from);
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

  // required .DataCommon.EquipmentCPP soldequip = 1;
  inline bool has_soldequip() const;
  inline void clear_soldequip();
  static const int kSoldequipFieldNumber = 1;
  inline const ::DataCommon::EquipmentCPP& soldequip() const;
  inline ::DataCommon::EquipmentCPP* mutable_soldequip();
  inline ::DataCommon::EquipmentCPP* release_soldequip();
  inline void set_allocated_soldequip(::DataCommon::EquipmentCPP* soldequip);

  // required uint32 coin = 2;
  inline bool has_coin() const;
  inline void clear_coin();
  static const int kCoinFieldNumber = 2;
  inline ::google::protobuf::uint32 coin() const;
  inline void set_coin(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:ProtoEquip.SoldEquipResp)
 private:
  inline void set_has_soldequip();
  inline void clear_has_soldequip();
  inline void set_has_coin();
  inline void clear_has_coin();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::DataCommon::EquipmentCPP* soldequip_;
  ::google::protobuf::uint32 coin_;
  friend void  protobuf_AddDesc_ProtoEquip_2eproto();
  friend void protobuf_AssignDesc_ProtoEquip_2eproto();
  friend void protobuf_ShutdownFile_ProtoEquip_2eproto();

  void InitAsDefaultInstance();
  static SoldEquipResp* default_instance_;
};
// -------------------------------------------------------------------

class OpenRepurchaseWindowReq : public ::google::protobuf::Message {
 public:
  OpenRepurchaseWindowReq();
  virtual ~OpenRepurchaseWindowReq();

  OpenRepurchaseWindowReq(const OpenRepurchaseWindowReq& from);

  inline OpenRepurchaseWindowReq& operator=(const OpenRepurchaseWindowReq& from) {
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
  static const OpenRepurchaseWindowReq& default_instance();

  void Swap(OpenRepurchaseWindowReq* other);

  // implements Message ----------------------------------------------

  OpenRepurchaseWindowReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const OpenRepurchaseWindowReq& from);
  void MergeFrom(const OpenRepurchaseWindowReq& from);
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

  // @@protoc_insertion_point(class_scope:ProtoEquip.OpenRepurchaseWindowReq)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_ProtoEquip_2eproto();
  friend void protobuf_AssignDesc_ProtoEquip_2eproto();
  friend void protobuf_ShutdownFile_ProtoEquip_2eproto();

  void InitAsDefaultInstance();
  static OpenRepurchaseWindowReq* default_instance_;
};
// -------------------------------------------------------------------

class OpenRepurchaseWindowResp : public ::google::protobuf::Message {
 public:
  OpenRepurchaseWindowResp();
  virtual ~OpenRepurchaseWindowResp();

  OpenRepurchaseWindowResp(const OpenRepurchaseWindowResp& from);

  inline OpenRepurchaseWindowResp& operator=(const OpenRepurchaseWindowResp& from) {
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
  static const OpenRepurchaseWindowResp& default_instance();

  void Swap(OpenRepurchaseWindowResp* other);

  // implements Message ----------------------------------------------

  OpenRepurchaseWindowResp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const OpenRepurchaseWindowResp& from);
  void MergeFrom(const OpenRepurchaseWindowResp& from);
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

  // repeated .DataCommon.EquipmentCPP equips = 1;
  inline int equips_size() const;
  inline void clear_equips();
  static const int kEquipsFieldNumber = 1;
  inline const ::DataCommon::EquipmentCPP& equips(int index) const;
  inline ::DataCommon::EquipmentCPP* mutable_equips(int index);
  inline ::DataCommon::EquipmentCPP* add_equips();
  inline const ::google::protobuf::RepeatedPtrField< ::DataCommon::EquipmentCPP >&
      equips() const;
  inline ::google::protobuf::RepeatedPtrField< ::DataCommon::EquipmentCPP >*
      mutable_equips();

  // @@protoc_insertion_point(class_scope:ProtoEquip.OpenRepurchaseWindowResp)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::DataCommon::EquipmentCPP > equips_;
  friend void  protobuf_AddDesc_ProtoEquip_2eproto();
  friend void protobuf_AssignDesc_ProtoEquip_2eproto();
  friend void protobuf_ShutdownFile_ProtoEquip_2eproto();

  void InitAsDefaultInstance();
  static OpenRepurchaseWindowResp* default_instance_;
};
// ===================================================================


// ===================================================================

// SoldEquipReq

// required uint32 equd = 1;
inline bool SoldEquipReq::has_equd() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SoldEquipReq::set_has_equd() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SoldEquipReq::clear_has_equd() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SoldEquipReq::clear_equd() {
  equd_ = 0u;
  clear_has_equd();
}
inline ::google::protobuf::uint32 SoldEquipReq::equd() const {
  // @@protoc_insertion_point(field_get:ProtoEquip.SoldEquipReq.equd)
  return equd_;
}
inline void SoldEquipReq::set_equd(::google::protobuf::uint32 value) {
  set_has_equd();
  equd_ = value;
  // @@protoc_insertion_point(field_set:ProtoEquip.SoldEquipReq.equd)
}

// -------------------------------------------------------------------

// SoldEquipResp

// required .DataCommon.EquipmentCPP soldequip = 1;
inline bool SoldEquipResp::has_soldequip() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SoldEquipResp::set_has_soldequip() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SoldEquipResp::clear_has_soldequip() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SoldEquipResp::clear_soldequip() {
  if (soldequip_ != NULL) soldequip_->::DataCommon::EquipmentCPP::Clear();
  clear_has_soldequip();
}
inline const ::DataCommon::EquipmentCPP& SoldEquipResp::soldequip() const {
  // @@protoc_insertion_point(field_get:ProtoEquip.SoldEquipResp.soldequip)
  return soldequip_ != NULL ? *soldequip_ : *default_instance_->soldequip_;
}
inline ::DataCommon::EquipmentCPP* SoldEquipResp::mutable_soldequip() {
  set_has_soldequip();
  if (soldequip_ == NULL) soldequip_ = new ::DataCommon::EquipmentCPP;
  // @@protoc_insertion_point(field_mutable:ProtoEquip.SoldEquipResp.soldequip)
  return soldequip_;
}
inline ::DataCommon::EquipmentCPP* SoldEquipResp::release_soldequip() {
  clear_has_soldequip();
  ::DataCommon::EquipmentCPP* temp = soldequip_;
  soldequip_ = NULL;
  return temp;
}
inline void SoldEquipResp::set_allocated_soldequip(::DataCommon::EquipmentCPP* soldequip) {
  delete soldequip_;
  soldequip_ = soldequip;
  if (soldequip) {
    set_has_soldequip();
  } else {
    clear_has_soldequip();
  }
  // @@protoc_insertion_point(field_set_allocated:ProtoEquip.SoldEquipResp.soldequip)
}

// required uint32 coin = 2;
inline bool SoldEquipResp::has_coin() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SoldEquipResp::set_has_coin() {
  _has_bits_[0] |= 0x00000002u;
}
inline void SoldEquipResp::clear_has_coin() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void SoldEquipResp::clear_coin() {
  coin_ = 0u;
  clear_has_coin();
}
inline ::google::protobuf::uint32 SoldEquipResp::coin() const {
  // @@protoc_insertion_point(field_get:ProtoEquip.SoldEquipResp.coin)
  return coin_;
}
inline void SoldEquipResp::set_coin(::google::protobuf::uint32 value) {
  set_has_coin();
  coin_ = value;
  // @@protoc_insertion_point(field_set:ProtoEquip.SoldEquipResp.coin)
}

// -------------------------------------------------------------------

// OpenRepurchaseWindowReq

// -------------------------------------------------------------------

// OpenRepurchaseWindowResp

// repeated .DataCommon.EquipmentCPP equips = 1;
inline int OpenRepurchaseWindowResp::equips_size() const {
  return equips_.size();
}
inline void OpenRepurchaseWindowResp::clear_equips() {
  equips_.Clear();
}
inline const ::DataCommon::EquipmentCPP& OpenRepurchaseWindowResp::equips(int index) const {
  // @@protoc_insertion_point(field_get:ProtoEquip.OpenRepurchaseWindowResp.equips)
  return equips_.Get(index);
}
inline ::DataCommon::EquipmentCPP* OpenRepurchaseWindowResp::mutable_equips(int index) {
  // @@protoc_insertion_point(field_mutable:ProtoEquip.OpenRepurchaseWindowResp.equips)
  return equips_.Mutable(index);
}
inline ::DataCommon::EquipmentCPP* OpenRepurchaseWindowResp::add_equips() {
  // @@protoc_insertion_point(field_add:ProtoEquip.OpenRepurchaseWindowResp.equips)
  return equips_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::DataCommon::EquipmentCPP >&
OpenRepurchaseWindowResp::equips() const {
  // @@protoc_insertion_point(field_list:ProtoEquip.OpenRepurchaseWindowResp.equips)
  return equips_;
}
inline ::google::protobuf::RepeatedPtrField< ::DataCommon::EquipmentCPP >*
OpenRepurchaseWindowResp::mutable_equips() {
  // @@protoc_insertion_point(field_mutable_list:ProtoEquip.OpenRepurchaseWindowResp.equips)
  return &equips_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ProtoEquip

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ProtoEquip_2eproto__INCLUDED