// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: AutoTransport.proto

#ifndef PROTOBUF_AutoTransport_2eproto__INCLUDED
#define PROTOBUF_AutoTransport_2eproto__INCLUDED

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

namespace ProtoAutoTransport {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_AutoTransport_2eproto();
void protobuf_AssignDesc_AutoTransport_2eproto();
void protobuf_ShutdownFile_AutoTransport_2eproto();

class AutoTransportItem;
class AutoTransport;

// ===================================================================

class AutoTransportItem : public ::google::protobuf::Message {
 public:
  AutoTransportItem();
  virtual ~AutoTransportItem();

  AutoTransportItem(const AutoTransportItem& from);

  inline AutoTransportItem& operator=(const AutoTransportItem& from) {
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
  static const AutoTransportItem& default_instance();

  void Swap(AutoTransportItem* other);

  // implements Message ----------------------------------------------

  AutoTransportItem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AutoTransportItem& from);
  void MergeFrom(const AutoTransportItem& from);
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

  // required uint32 uid = 1;
  inline bool has_uid() const;
  inline void clear_uid();
  static const int kUidFieldNumber = 1;
  inline ::google::protobuf::uint32 uid() const;
  inline void set_uid(::google::protobuf::uint32 value);

  // required uint32 ets = 2;
  inline bool has_ets() const;
  inline void clear_ets();
  static const int kEtsFieldNumber = 2;
  inline ::google::protobuf::uint32 ets() const;
  inline void set_ets(::google::protobuf::uint32 value);

  // required uint32 res = 3;
  inline bool has_res() const;
  inline void clear_res();
  static const int kResFieldNumber = 3;
  inline ::google::protobuf::uint32 res() const;
  inline void set_res(::google::protobuf::uint32 value);

  // required uint32 lost = 4;
  inline bool has_lost() const;
  inline void clear_lost();
  static const int kLostFieldNumber = 4;
  inline ::google::protobuf::uint32 lost() const;
  inline void set_lost(::google::protobuf::uint32 value);

  // required uint32 lv = 5;
  inline bool has_lv() const;
  inline void clear_lv();
  static const int kLvFieldNumber = 5;
  inline ::google::protobuf::uint32 lv() const;
  inline void set_lv(::google::protobuf::uint32 value);

  // required uint32 blv = 6;
  inline bool has_blv() const;
  inline void clear_blv();
  static const int kBlvFieldNumber = 6;
  inline ::google::protobuf::uint32 blv() const;
  inline void set_blv(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:ProtoAutoTransport.AutoTransportItem)
 private:
  inline void set_has_uid();
  inline void clear_has_uid();
  inline void set_has_ets();
  inline void clear_has_ets();
  inline void set_has_res();
  inline void clear_has_res();
  inline void set_has_lost();
  inline void clear_has_lost();
  inline void set_has_lv();
  inline void clear_has_lv();
  inline void set_has_blv();
  inline void clear_has_blv();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 uid_;
  ::google::protobuf::uint32 ets_;
  ::google::protobuf::uint32 res_;
  ::google::protobuf::uint32 lost_;
  ::google::protobuf::uint32 lv_;
  ::google::protobuf::uint32 blv_;
  friend void  protobuf_AddDesc_AutoTransport_2eproto();
  friend void protobuf_AssignDesc_AutoTransport_2eproto();
  friend void protobuf_ShutdownFile_AutoTransport_2eproto();

  void InitAsDefaultInstance();
  static AutoTransportItem* default_instance_;
};
// -------------------------------------------------------------------

class AutoTransport : public ::google::protobuf::Message {
 public:
  AutoTransport();
  virtual ~AutoTransport();

  AutoTransport(const AutoTransport& from);

  inline AutoTransport& operator=(const AutoTransport& from) {
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
  static const AutoTransport& default_instance();

  void Swap(AutoTransport* other);

  // implements Message ----------------------------------------------

  AutoTransport* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AutoTransport& from);
  void MergeFrom(const AutoTransport& from);
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

  // repeated .ProtoAutoTransport.AutoTransportItem datas = 1;
  inline int datas_size() const;
  inline void clear_datas();
  static const int kDatasFieldNumber = 1;
  inline const ::ProtoAutoTransport::AutoTransportItem& datas(int index) const;
  inline ::ProtoAutoTransport::AutoTransportItem* mutable_datas(int index);
  inline ::ProtoAutoTransport::AutoTransportItem* add_datas();
  inline const ::google::protobuf::RepeatedPtrField< ::ProtoAutoTransport::AutoTransportItem >&
      datas() const;
  inline ::google::protobuf::RepeatedPtrField< ::ProtoAutoTransport::AutoTransportItem >*
      mutable_datas();

  // @@protoc_insertion_point(class_scope:ProtoAutoTransport.AutoTransport)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::ProtoAutoTransport::AutoTransportItem > datas_;
  friend void  protobuf_AddDesc_AutoTransport_2eproto();
  friend void protobuf_AssignDesc_AutoTransport_2eproto();
  friend void protobuf_ShutdownFile_AutoTransport_2eproto();

  void InitAsDefaultInstance();
  static AutoTransport* default_instance_;
};
// ===================================================================


// ===================================================================

// AutoTransportItem

// required uint32 uid = 1;
inline bool AutoTransportItem::has_uid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AutoTransportItem::set_has_uid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AutoTransportItem::clear_has_uid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AutoTransportItem::clear_uid() {
  uid_ = 0u;
  clear_has_uid();
}
inline ::google::protobuf::uint32 AutoTransportItem::uid() const {
  // @@protoc_insertion_point(field_get:ProtoAutoTransport.AutoTransportItem.uid)
  return uid_;
}
inline void AutoTransportItem::set_uid(::google::protobuf::uint32 value) {
  set_has_uid();
  uid_ = value;
  // @@protoc_insertion_point(field_set:ProtoAutoTransport.AutoTransportItem.uid)
}

// required uint32 ets = 2;
inline bool AutoTransportItem::has_ets() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AutoTransportItem::set_has_ets() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AutoTransportItem::clear_has_ets() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AutoTransportItem::clear_ets() {
  ets_ = 0u;
  clear_has_ets();
}
inline ::google::protobuf::uint32 AutoTransportItem::ets() const {
  // @@protoc_insertion_point(field_get:ProtoAutoTransport.AutoTransportItem.ets)
  return ets_;
}
inline void AutoTransportItem::set_ets(::google::protobuf::uint32 value) {
  set_has_ets();
  ets_ = value;
  // @@protoc_insertion_point(field_set:ProtoAutoTransport.AutoTransportItem.ets)
}

// required uint32 res = 3;
inline bool AutoTransportItem::has_res() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void AutoTransportItem::set_has_res() {
  _has_bits_[0] |= 0x00000004u;
}
inline void AutoTransportItem::clear_has_res() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void AutoTransportItem::clear_res() {
  res_ = 0u;
  clear_has_res();
}
inline ::google::protobuf::uint32 AutoTransportItem::res() const {
  // @@protoc_insertion_point(field_get:ProtoAutoTransport.AutoTransportItem.res)
  return res_;
}
inline void AutoTransportItem::set_res(::google::protobuf::uint32 value) {
  set_has_res();
  res_ = value;
  // @@protoc_insertion_point(field_set:ProtoAutoTransport.AutoTransportItem.res)
}

// required uint32 lost = 4;
inline bool AutoTransportItem::has_lost() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void AutoTransportItem::set_has_lost() {
  _has_bits_[0] |= 0x00000008u;
}
inline void AutoTransportItem::clear_has_lost() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void AutoTransportItem::clear_lost() {
  lost_ = 0u;
  clear_has_lost();
}
inline ::google::protobuf::uint32 AutoTransportItem::lost() const {
  // @@protoc_insertion_point(field_get:ProtoAutoTransport.AutoTransportItem.lost)
  return lost_;
}
inline void AutoTransportItem::set_lost(::google::protobuf::uint32 value) {
  set_has_lost();
  lost_ = value;
  // @@protoc_insertion_point(field_set:ProtoAutoTransport.AutoTransportItem.lost)
}

// required uint32 lv = 5;
inline bool AutoTransportItem::has_lv() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void AutoTransportItem::set_has_lv() {
  _has_bits_[0] |= 0x00000010u;
}
inline void AutoTransportItem::clear_has_lv() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void AutoTransportItem::clear_lv() {
  lv_ = 0u;
  clear_has_lv();
}
inline ::google::protobuf::uint32 AutoTransportItem::lv() const {
  // @@protoc_insertion_point(field_get:ProtoAutoTransport.AutoTransportItem.lv)
  return lv_;
}
inline void AutoTransportItem::set_lv(::google::protobuf::uint32 value) {
  set_has_lv();
  lv_ = value;
  // @@protoc_insertion_point(field_set:ProtoAutoTransport.AutoTransportItem.lv)
}

// required uint32 blv = 6;
inline bool AutoTransportItem::has_blv() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void AutoTransportItem::set_has_blv() {
  _has_bits_[0] |= 0x00000020u;
}
inline void AutoTransportItem::clear_has_blv() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void AutoTransportItem::clear_blv() {
  blv_ = 0u;
  clear_has_blv();
}
inline ::google::protobuf::uint32 AutoTransportItem::blv() const {
  // @@protoc_insertion_point(field_get:ProtoAutoTransport.AutoTransportItem.blv)
  return blv_;
}
inline void AutoTransportItem::set_blv(::google::protobuf::uint32 value) {
  set_has_blv();
  blv_ = value;
  // @@protoc_insertion_point(field_set:ProtoAutoTransport.AutoTransportItem.blv)
}

// -------------------------------------------------------------------

// AutoTransport

// repeated .ProtoAutoTransport.AutoTransportItem datas = 1;
inline int AutoTransport::datas_size() const {
  return datas_.size();
}
inline void AutoTransport::clear_datas() {
  datas_.Clear();
}
inline const ::ProtoAutoTransport::AutoTransportItem& AutoTransport::datas(int index) const {
  // @@protoc_insertion_point(field_get:ProtoAutoTransport.AutoTransport.datas)
  return datas_.Get(index);
}
inline ::ProtoAutoTransport::AutoTransportItem* AutoTransport::mutable_datas(int index) {
  // @@protoc_insertion_point(field_mutable:ProtoAutoTransport.AutoTransport.datas)
  return datas_.Mutable(index);
}
inline ::ProtoAutoTransport::AutoTransportItem* AutoTransport::add_datas() {
  // @@protoc_insertion_point(field_add:ProtoAutoTransport.AutoTransport.datas)
  return datas_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ProtoAutoTransport::AutoTransportItem >&
AutoTransport::datas() const {
  // @@protoc_insertion_point(field_list:ProtoAutoTransport.AutoTransport.datas)
  return datas_;
}
inline ::google::protobuf::RepeatedPtrField< ::ProtoAutoTransport::AutoTransportItem >*
AutoTransport::mutable_datas() {
  // @@protoc_insertion_point(field_mutable_list:ProtoAutoTransport.AutoTransport.datas)
  return &datas_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ProtoAutoTransport

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_AutoTransport_2eproto__INCLUDED
