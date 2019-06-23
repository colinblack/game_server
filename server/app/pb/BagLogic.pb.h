// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: BagLogic.proto

#ifndef PROTOBUF_BagLogic_2eproto__INCLUDED
#define PROTOBUF_BagLogic_2eproto__INCLUDED

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

namespace BagLogic {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_BagLogic_2eproto();
void protobuf_AssignDesc_BagLogic_2eproto();
void protobuf_ShutdownFile_BagLogic_2eproto();

class PurchaseBagReq;
class PurchaseBagResp;

// ===================================================================

class PurchaseBagReq : public ::google::protobuf::Message {
 public:
  PurchaseBagReq();
  virtual ~PurchaseBagReq();

  PurchaseBagReq(const PurchaseBagReq& from);

  inline PurchaseBagReq& operator=(const PurchaseBagReq& from) {
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
  static const PurchaseBagReq& default_instance();

  void Swap(PurchaseBagReq* other);

  // implements Message ----------------------------------------------

  PurchaseBagReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PurchaseBagReq& from);
  void MergeFrom(const PurchaseBagReq& from);
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

  // @@protoc_insertion_point(class_scope:BagLogic.PurchaseBagReq)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_BagLogic_2eproto();
  friend void protobuf_AssignDesc_BagLogic_2eproto();
  friend void protobuf_ShutdownFile_BagLogic_2eproto();

  void InitAsDefaultInstance();
  static PurchaseBagReq* default_instance_;
};
// -------------------------------------------------------------------

class PurchaseBagResp : public ::google::protobuf::Message {
 public:
  PurchaseBagResp();
  virtual ~PurchaseBagResp();

  PurchaseBagResp(const PurchaseBagResp& from);

  inline PurchaseBagResp& operator=(const PurchaseBagResp& from) {
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
  static const PurchaseBagResp& default_instance();

  void Swap(PurchaseBagResp* other);

  // implements Message ----------------------------------------------

  PurchaseBagResp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PurchaseBagResp& from);
  void MergeFrom(const PurchaseBagResp& from);
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

  // required uint32 bag = 1;
  inline bool has_bag() const;
  inline void clear_bag();
  static const int kBagFieldNumber = 1;
  inline ::google::protobuf::uint32 bag() const;
  inline void set_bag(::google::protobuf::uint32 value);

  // required uint32 coin = 2;
  inline bool has_coin() const;
  inline void clear_coin();
  static const int kCoinFieldNumber = 2;
  inline ::google::protobuf::uint32 coin() const;
  inline void set_coin(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:BagLogic.PurchaseBagResp)
 private:
  inline void set_has_bag();
  inline void clear_has_bag();
  inline void set_has_coin();
  inline void clear_has_coin();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 bag_;
  ::google::protobuf::uint32 coin_;
  friend void  protobuf_AddDesc_BagLogic_2eproto();
  friend void protobuf_AssignDesc_BagLogic_2eproto();
  friend void protobuf_ShutdownFile_BagLogic_2eproto();

  void InitAsDefaultInstance();
  static PurchaseBagResp* default_instance_;
};
// ===================================================================


// ===================================================================

// PurchaseBagReq

// -------------------------------------------------------------------

// PurchaseBagResp

// required uint32 bag = 1;
inline bool PurchaseBagResp::has_bag() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PurchaseBagResp::set_has_bag() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PurchaseBagResp::clear_has_bag() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PurchaseBagResp::clear_bag() {
  bag_ = 0u;
  clear_has_bag();
}
inline ::google::protobuf::uint32 PurchaseBagResp::bag() const {
  // @@protoc_insertion_point(field_get:BagLogic.PurchaseBagResp.bag)
  return bag_;
}
inline void PurchaseBagResp::set_bag(::google::protobuf::uint32 value) {
  set_has_bag();
  bag_ = value;
  // @@protoc_insertion_point(field_set:BagLogic.PurchaseBagResp.bag)
}

// required uint32 coin = 2;
inline bool PurchaseBagResp::has_coin() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void PurchaseBagResp::set_has_coin() {
  _has_bits_[0] |= 0x00000002u;
}
inline void PurchaseBagResp::clear_has_coin() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void PurchaseBagResp::clear_coin() {
  coin_ = 0u;
  clear_has_coin();
}
inline ::google::protobuf::uint32 PurchaseBagResp::coin() const {
  // @@protoc_insertion_point(field_get:BagLogic.PurchaseBagResp.coin)
  return coin_;
}
inline void PurchaseBagResp::set_coin(::google::protobuf::uint32 value) {
  set_has_coin();
  coin_ = value;
  // @@protoc_insertion_point(field_set:BagLogic.PurchaseBagResp.coin)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace BagLogic

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_BagLogic_2eproto__INCLUDED