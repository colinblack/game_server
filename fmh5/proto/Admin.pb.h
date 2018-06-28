// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Admin.proto

#ifndef PROTOBUF_Admin_2eproto__INCLUDED
#define PROTOBUF_Admin_2eproto__INCLUDED

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

namespace Admin {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_Admin_2eproto();
void protobuf_AssignDesc_Admin_2eproto();
void protobuf_ShutdownFile_Admin_2eproto();

class AddCash;
class ReplyAddCash;
class AsycItem;
class AsycAdd;
class AsycAddResp;
class RequestForbidTS;
class ReplyForbidTS;
class SetForbidTS;

// ===================================================================

class AddCash : public ::google::protobuf::Message {
 public:
  AddCash();
  virtual ~AddCash();

  AddCash(const AddCash& from);

  inline AddCash& operator=(const AddCash& from) {
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
  static const AddCash& default_instance();

  void Swap(AddCash* other);

  // implements Message ----------------------------------------------

  AddCash* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AddCash& from);
  void MergeFrom(const AddCash& from);
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

  // required int32 cash = 2;
  inline bool has_cash() const;
  inline void clear_cash();
  static const int kCashFieldNumber = 2;
  inline ::google::protobuf::int32 cash() const;
  inline void set_cash(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:Admin.AddCash)
 private:
  inline void set_has_uid();
  inline void clear_has_uid();
  inline void set_has_cash();
  inline void clear_has_cash();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 uid_;
  ::google::protobuf::int32 cash_;
  friend void  protobuf_AddDesc_Admin_2eproto();
  friend void protobuf_AssignDesc_Admin_2eproto();
  friend void protobuf_ShutdownFile_Admin_2eproto();

  void InitAsDefaultInstance();
  static AddCash* default_instance_;
};
// -------------------------------------------------------------------

class ReplyAddCash : public ::google::protobuf::Message {
 public:
  ReplyAddCash();
  virtual ~ReplyAddCash();

  ReplyAddCash(const ReplyAddCash& from);

  inline ReplyAddCash& operator=(const ReplyAddCash& from) {
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
  static const ReplyAddCash& default_instance();

  void Swap(ReplyAddCash* other);

  // implements Message ----------------------------------------------

  ReplyAddCash* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ReplyAddCash& from);
  void MergeFrom(const ReplyAddCash& from);
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

  // required uint32 cash = 2;
  inline bool has_cash() const;
  inline void clear_cash();
  static const int kCashFieldNumber = 2;
  inline ::google::protobuf::uint32 cash() const;
  inline void set_cash(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:Admin.ReplyAddCash)
 private:
  inline void set_has_uid();
  inline void clear_has_uid();
  inline void set_has_cash();
  inline void clear_has_cash();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 uid_;
  ::google::protobuf::uint32 cash_;
  friend void  protobuf_AddDesc_Admin_2eproto();
  friend void protobuf_AssignDesc_Admin_2eproto();
  friend void protobuf_ShutdownFile_Admin_2eproto();

  void InitAsDefaultInstance();
  static ReplyAddCash* default_instance_;
};
// -------------------------------------------------------------------

class AsycItem : public ::google::protobuf::Message {
 public:
  AsycItem();
  virtual ~AsycItem();

  AsycItem(const AsycItem& from);

  inline AsycItem& operator=(const AsycItem& from) {
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
  static const AsycItem& default_instance();

  void Swap(AsycItem* other);

  // implements Message ----------------------------------------------

  AsycItem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AsycItem& from);
  void MergeFrom(const AsycItem& from);
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

  // required uint32 id = 2;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 2;
  inline ::google::protobuf::uint32 id() const;
  inline void set_id(::google::protobuf::uint32 value);

  // required uint32 count = 3;
  inline bool has_count() const;
  inline void clear_count();
  static const int kCountFieldNumber = 3;
  inline ::google::protobuf::uint32 count() const;
  inline void set_count(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:Admin.AsycItem)
 private:
  inline void set_has_uid();
  inline void clear_has_uid();
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_count();
  inline void clear_has_count();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 uid_;
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 count_;
  friend void  protobuf_AddDesc_Admin_2eproto();
  friend void protobuf_AssignDesc_Admin_2eproto();
  friend void protobuf_ShutdownFile_Admin_2eproto();

  void InitAsDefaultInstance();
  static AsycItem* default_instance_;
};
// -------------------------------------------------------------------

class AsycAdd : public ::google::protobuf::Message {
 public:
  AsycAdd();
  virtual ~AsycAdd();

  AsycAdd(const AsycAdd& from);

  inline AsycAdd& operator=(const AsycAdd& from) {
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
  static const AsycAdd& default_instance();

  void Swap(AsycAdd* other);

  // implements Message ----------------------------------------------

  AsycAdd* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AsycAdd& from);
  void MergeFrom(const AsycAdd& from);
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

  // repeated .Admin.AsycItem item = 1;
  inline int item_size() const;
  inline void clear_item();
  static const int kItemFieldNumber = 1;
  inline const ::Admin::AsycItem& item(int index) const;
  inline ::Admin::AsycItem* mutable_item(int index);
  inline ::Admin::AsycItem* add_item();
  inline const ::google::protobuf::RepeatedPtrField< ::Admin::AsycItem >&
      item() const;
  inline ::google::protobuf::RepeatedPtrField< ::Admin::AsycItem >*
      mutable_item();

  // @@protoc_insertion_point(class_scope:Admin.AsycAdd)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::Admin::AsycItem > item_;
  friend void  protobuf_AddDesc_Admin_2eproto();
  friend void protobuf_AssignDesc_Admin_2eproto();
  friend void protobuf_ShutdownFile_Admin_2eproto();

  void InitAsDefaultInstance();
  static AsycAdd* default_instance_;
};
// -------------------------------------------------------------------

class AsycAddResp : public ::google::protobuf::Message {
 public:
  AsycAddResp();
  virtual ~AsycAddResp();

  AsycAddResp(const AsycAddResp& from);

  inline AsycAddResp& operator=(const AsycAddResp& from) {
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
  static const AsycAddResp& default_instance();

  void Swap(AsycAddResp* other);

  // implements Message ----------------------------------------------

  AsycAddResp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AsycAddResp& from);
  void MergeFrom(const AsycAddResp& from);
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

  // required uint32 ret = 1;
  inline bool has_ret() const;
  inline void clear_ret();
  static const int kRetFieldNumber = 1;
  inline ::google::protobuf::uint32 ret() const;
  inline void set_ret(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:Admin.AsycAddResp)
 private:
  inline void set_has_ret();
  inline void clear_has_ret();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 ret_;
  friend void  protobuf_AddDesc_Admin_2eproto();
  friend void protobuf_AssignDesc_Admin_2eproto();
  friend void protobuf_ShutdownFile_Admin_2eproto();

  void InitAsDefaultInstance();
  static AsycAddResp* default_instance_;
};
// -------------------------------------------------------------------

class RequestForbidTS : public ::google::protobuf::Message {
 public:
  RequestForbidTS();
  virtual ~RequestForbidTS();

  RequestForbidTS(const RequestForbidTS& from);

  inline RequestForbidTS& operator=(const RequestForbidTS& from) {
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
  static const RequestForbidTS& default_instance();

  void Swap(RequestForbidTS* other);

  // implements Message ----------------------------------------------

  RequestForbidTS* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RequestForbidTS& from);
  void MergeFrom(const RequestForbidTS& from);
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

  // @@protoc_insertion_point(class_scope:Admin.RequestForbidTS)
 private:
  inline void set_has_uid();
  inline void clear_has_uid();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 uid_;
  friend void  protobuf_AddDesc_Admin_2eproto();
  friend void protobuf_AssignDesc_Admin_2eproto();
  friend void protobuf_ShutdownFile_Admin_2eproto();

  void InitAsDefaultInstance();
  static RequestForbidTS* default_instance_;
};
// -------------------------------------------------------------------

class ReplyForbidTS : public ::google::protobuf::Message {
 public:
  ReplyForbidTS();
  virtual ~ReplyForbidTS();

  ReplyForbidTS(const ReplyForbidTS& from);

  inline ReplyForbidTS& operator=(const ReplyForbidTS& from) {
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
  static const ReplyForbidTS& default_instance();

  void Swap(ReplyForbidTS* other);

  // implements Message ----------------------------------------------

  ReplyForbidTS* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ReplyForbidTS& from);
  void MergeFrom(const ReplyForbidTS& from);
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

  // required uint32 forbid_ts = 1;
  inline bool has_forbid_ts() const;
  inline void clear_forbid_ts();
  static const int kForbidTsFieldNumber = 1;
  inline ::google::protobuf::uint32 forbid_ts() const;
  inline void set_forbid_ts(::google::protobuf::uint32 value);

  // required bytes reason = 2;
  inline bool has_reason() const;
  inline void clear_reason();
  static const int kReasonFieldNumber = 2;
  inline const ::std::string& reason() const;
  inline void set_reason(const ::std::string& value);
  inline void set_reason(const char* value);
  inline void set_reason(const void* value, size_t size);
  inline ::std::string* mutable_reason();
  inline ::std::string* release_reason();
  inline void set_allocated_reason(::std::string* reason);

  // @@protoc_insertion_point(class_scope:Admin.ReplyForbidTS)
 private:
  inline void set_has_forbid_ts();
  inline void clear_has_forbid_ts();
  inline void set_has_reason();
  inline void clear_has_reason();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* reason_;
  ::google::protobuf::uint32 forbid_ts_;
  friend void  protobuf_AddDesc_Admin_2eproto();
  friend void protobuf_AssignDesc_Admin_2eproto();
  friend void protobuf_ShutdownFile_Admin_2eproto();

  void InitAsDefaultInstance();
  static ReplyForbidTS* default_instance_;
};
// -------------------------------------------------------------------

class SetForbidTS : public ::google::protobuf::Message {
 public:
  SetForbidTS();
  virtual ~SetForbidTS();

  SetForbidTS(const SetForbidTS& from);

  inline SetForbidTS& operator=(const SetForbidTS& from) {
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
  static const SetForbidTS& default_instance();

  void Swap(SetForbidTS* other);

  // implements Message ----------------------------------------------

  SetForbidTS* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SetForbidTS& from);
  void MergeFrom(const SetForbidTS& from);
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

  // required uint32 forbid_ts = 2;
  inline bool has_forbid_ts() const;
  inline void clear_forbid_ts();
  static const int kForbidTsFieldNumber = 2;
  inline ::google::protobuf::uint32 forbid_ts() const;
  inline void set_forbid_ts(::google::protobuf::uint32 value);

  // required bytes reason = 3;
  inline bool has_reason() const;
  inline void clear_reason();
  static const int kReasonFieldNumber = 3;
  inline const ::std::string& reason() const;
  inline void set_reason(const ::std::string& value);
  inline void set_reason(const char* value);
  inline void set_reason(const void* value, size_t size);
  inline ::std::string* mutable_reason();
  inline ::std::string* release_reason();
  inline void set_allocated_reason(::std::string* reason);

  // @@protoc_insertion_point(class_scope:Admin.SetForbidTS)
 private:
  inline void set_has_uid();
  inline void clear_has_uid();
  inline void set_has_forbid_ts();
  inline void clear_has_forbid_ts();
  inline void set_has_reason();
  inline void clear_has_reason();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 uid_;
  ::google::protobuf::uint32 forbid_ts_;
  ::std::string* reason_;
  friend void  protobuf_AddDesc_Admin_2eproto();
  friend void protobuf_AssignDesc_Admin_2eproto();
  friend void protobuf_ShutdownFile_Admin_2eproto();

  void InitAsDefaultInstance();
  static SetForbidTS* default_instance_;
};
// ===================================================================


// ===================================================================

// AddCash

// required uint32 uid = 1;
inline bool AddCash::has_uid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AddCash::set_has_uid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AddCash::clear_has_uid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AddCash::clear_uid() {
  uid_ = 0u;
  clear_has_uid();
}
inline ::google::protobuf::uint32 AddCash::uid() const {
  // @@protoc_insertion_point(field_get:Admin.AddCash.uid)
  return uid_;
}
inline void AddCash::set_uid(::google::protobuf::uint32 value) {
  set_has_uid();
  uid_ = value;
  // @@protoc_insertion_point(field_set:Admin.AddCash.uid)
}

// required int32 cash = 2;
inline bool AddCash::has_cash() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AddCash::set_has_cash() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AddCash::clear_has_cash() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AddCash::clear_cash() {
  cash_ = 0;
  clear_has_cash();
}
inline ::google::protobuf::int32 AddCash::cash() const {
  // @@protoc_insertion_point(field_get:Admin.AddCash.cash)
  return cash_;
}
inline void AddCash::set_cash(::google::protobuf::int32 value) {
  set_has_cash();
  cash_ = value;
  // @@protoc_insertion_point(field_set:Admin.AddCash.cash)
}

// -------------------------------------------------------------------

// ReplyAddCash

// required uint32 uid = 1;
inline bool ReplyAddCash::has_uid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ReplyAddCash::set_has_uid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ReplyAddCash::clear_has_uid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ReplyAddCash::clear_uid() {
  uid_ = 0u;
  clear_has_uid();
}
inline ::google::protobuf::uint32 ReplyAddCash::uid() const {
  // @@protoc_insertion_point(field_get:Admin.ReplyAddCash.uid)
  return uid_;
}
inline void ReplyAddCash::set_uid(::google::protobuf::uint32 value) {
  set_has_uid();
  uid_ = value;
  // @@protoc_insertion_point(field_set:Admin.ReplyAddCash.uid)
}

// required uint32 cash = 2;
inline bool ReplyAddCash::has_cash() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ReplyAddCash::set_has_cash() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ReplyAddCash::clear_has_cash() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ReplyAddCash::clear_cash() {
  cash_ = 0u;
  clear_has_cash();
}
inline ::google::protobuf::uint32 ReplyAddCash::cash() const {
  // @@protoc_insertion_point(field_get:Admin.ReplyAddCash.cash)
  return cash_;
}
inline void ReplyAddCash::set_cash(::google::protobuf::uint32 value) {
  set_has_cash();
  cash_ = value;
  // @@protoc_insertion_point(field_set:Admin.ReplyAddCash.cash)
}

// -------------------------------------------------------------------

// AsycItem

// required uint32 uid = 1;
inline bool AsycItem::has_uid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AsycItem::set_has_uid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AsycItem::clear_has_uid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AsycItem::clear_uid() {
  uid_ = 0u;
  clear_has_uid();
}
inline ::google::protobuf::uint32 AsycItem::uid() const {
  // @@protoc_insertion_point(field_get:Admin.AsycItem.uid)
  return uid_;
}
inline void AsycItem::set_uid(::google::protobuf::uint32 value) {
  set_has_uid();
  uid_ = value;
  // @@protoc_insertion_point(field_set:Admin.AsycItem.uid)
}

// required uint32 id = 2;
inline bool AsycItem::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AsycItem::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AsycItem::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AsycItem::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 AsycItem::id() const {
  // @@protoc_insertion_point(field_get:Admin.AsycItem.id)
  return id_;
}
inline void AsycItem::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:Admin.AsycItem.id)
}

// required uint32 count = 3;
inline bool AsycItem::has_count() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void AsycItem::set_has_count() {
  _has_bits_[0] |= 0x00000004u;
}
inline void AsycItem::clear_has_count() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void AsycItem::clear_count() {
  count_ = 0u;
  clear_has_count();
}
inline ::google::protobuf::uint32 AsycItem::count() const {
  // @@protoc_insertion_point(field_get:Admin.AsycItem.count)
  return count_;
}
inline void AsycItem::set_count(::google::protobuf::uint32 value) {
  set_has_count();
  count_ = value;
  // @@protoc_insertion_point(field_set:Admin.AsycItem.count)
}

// -------------------------------------------------------------------

// AsycAdd

// repeated .Admin.AsycItem item = 1;
inline int AsycAdd::item_size() const {
  return item_.size();
}
inline void AsycAdd::clear_item() {
  item_.Clear();
}
inline const ::Admin::AsycItem& AsycAdd::item(int index) const {
  // @@protoc_insertion_point(field_get:Admin.AsycAdd.item)
  return item_.Get(index);
}
inline ::Admin::AsycItem* AsycAdd::mutable_item(int index) {
  // @@protoc_insertion_point(field_mutable:Admin.AsycAdd.item)
  return item_.Mutable(index);
}
inline ::Admin::AsycItem* AsycAdd::add_item() {
  // @@protoc_insertion_point(field_add:Admin.AsycAdd.item)
  return item_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Admin::AsycItem >&
AsycAdd::item() const {
  // @@protoc_insertion_point(field_list:Admin.AsycAdd.item)
  return item_;
}
inline ::google::protobuf::RepeatedPtrField< ::Admin::AsycItem >*
AsycAdd::mutable_item() {
  // @@protoc_insertion_point(field_mutable_list:Admin.AsycAdd.item)
  return &item_;
}

// -------------------------------------------------------------------

// AsycAddResp

// required uint32 ret = 1;
inline bool AsycAddResp::has_ret() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AsycAddResp::set_has_ret() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AsycAddResp::clear_has_ret() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AsycAddResp::clear_ret() {
  ret_ = 0u;
  clear_has_ret();
}
inline ::google::protobuf::uint32 AsycAddResp::ret() const {
  // @@protoc_insertion_point(field_get:Admin.AsycAddResp.ret)
  return ret_;
}
inline void AsycAddResp::set_ret(::google::protobuf::uint32 value) {
  set_has_ret();
  ret_ = value;
  // @@protoc_insertion_point(field_set:Admin.AsycAddResp.ret)
}

// -------------------------------------------------------------------

// RequestForbidTS

// required uint32 uid = 1;
inline bool RequestForbidTS::has_uid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RequestForbidTS::set_has_uid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RequestForbidTS::clear_has_uid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RequestForbidTS::clear_uid() {
  uid_ = 0u;
  clear_has_uid();
}
inline ::google::protobuf::uint32 RequestForbidTS::uid() const {
  // @@protoc_insertion_point(field_get:Admin.RequestForbidTS.uid)
  return uid_;
}
inline void RequestForbidTS::set_uid(::google::protobuf::uint32 value) {
  set_has_uid();
  uid_ = value;
  // @@protoc_insertion_point(field_set:Admin.RequestForbidTS.uid)
}

// -------------------------------------------------------------------

// ReplyForbidTS

// required uint32 forbid_ts = 1;
inline bool ReplyForbidTS::has_forbid_ts() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ReplyForbidTS::set_has_forbid_ts() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ReplyForbidTS::clear_has_forbid_ts() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ReplyForbidTS::clear_forbid_ts() {
  forbid_ts_ = 0u;
  clear_has_forbid_ts();
}
inline ::google::protobuf::uint32 ReplyForbidTS::forbid_ts() const {
  // @@protoc_insertion_point(field_get:Admin.ReplyForbidTS.forbid_ts)
  return forbid_ts_;
}
inline void ReplyForbidTS::set_forbid_ts(::google::protobuf::uint32 value) {
  set_has_forbid_ts();
  forbid_ts_ = value;
  // @@protoc_insertion_point(field_set:Admin.ReplyForbidTS.forbid_ts)
}

// required bytes reason = 2;
inline bool ReplyForbidTS::has_reason() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ReplyForbidTS::set_has_reason() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ReplyForbidTS::clear_has_reason() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ReplyForbidTS::clear_reason() {
  if (reason_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    reason_->clear();
  }
  clear_has_reason();
}
inline const ::std::string& ReplyForbidTS::reason() const {
  // @@protoc_insertion_point(field_get:Admin.ReplyForbidTS.reason)
  return *reason_;
}
inline void ReplyForbidTS::set_reason(const ::std::string& value) {
  set_has_reason();
  if (reason_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    reason_ = new ::std::string;
  }
  reason_->assign(value);
  // @@protoc_insertion_point(field_set:Admin.ReplyForbidTS.reason)
}
inline void ReplyForbidTS::set_reason(const char* value) {
  set_has_reason();
  if (reason_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    reason_ = new ::std::string;
  }
  reason_->assign(value);
  // @@protoc_insertion_point(field_set_char:Admin.ReplyForbidTS.reason)
}
inline void ReplyForbidTS::set_reason(const void* value, size_t size) {
  set_has_reason();
  if (reason_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    reason_ = new ::std::string;
  }
  reason_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:Admin.ReplyForbidTS.reason)
}
inline ::std::string* ReplyForbidTS::mutable_reason() {
  set_has_reason();
  if (reason_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    reason_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:Admin.ReplyForbidTS.reason)
  return reason_;
}
inline ::std::string* ReplyForbidTS::release_reason() {
  clear_has_reason();
  if (reason_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = reason_;
    reason_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void ReplyForbidTS::set_allocated_reason(::std::string* reason) {
  if (reason_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete reason_;
  }
  if (reason) {
    set_has_reason();
    reason_ = reason;
  } else {
    clear_has_reason();
    reason_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:Admin.ReplyForbidTS.reason)
}

// -------------------------------------------------------------------

// SetForbidTS

// required uint32 uid = 1;
inline bool SetForbidTS::has_uid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SetForbidTS::set_has_uid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SetForbidTS::clear_has_uid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SetForbidTS::clear_uid() {
  uid_ = 0u;
  clear_has_uid();
}
inline ::google::protobuf::uint32 SetForbidTS::uid() const {
  // @@protoc_insertion_point(field_get:Admin.SetForbidTS.uid)
  return uid_;
}
inline void SetForbidTS::set_uid(::google::protobuf::uint32 value) {
  set_has_uid();
  uid_ = value;
  // @@protoc_insertion_point(field_set:Admin.SetForbidTS.uid)
}

// required uint32 forbid_ts = 2;
inline bool SetForbidTS::has_forbid_ts() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SetForbidTS::set_has_forbid_ts() {
  _has_bits_[0] |= 0x00000002u;
}
inline void SetForbidTS::clear_has_forbid_ts() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void SetForbidTS::clear_forbid_ts() {
  forbid_ts_ = 0u;
  clear_has_forbid_ts();
}
inline ::google::protobuf::uint32 SetForbidTS::forbid_ts() const {
  // @@protoc_insertion_point(field_get:Admin.SetForbidTS.forbid_ts)
  return forbid_ts_;
}
inline void SetForbidTS::set_forbid_ts(::google::protobuf::uint32 value) {
  set_has_forbid_ts();
  forbid_ts_ = value;
  // @@protoc_insertion_point(field_set:Admin.SetForbidTS.forbid_ts)
}

// required bytes reason = 3;
inline bool SetForbidTS::has_reason() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void SetForbidTS::set_has_reason() {
  _has_bits_[0] |= 0x00000004u;
}
inline void SetForbidTS::clear_has_reason() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void SetForbidTS::clear_reason() {
  if (reason_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    reason_->clear();
  }
  clear_has_reason();
}
inline const ::std::string& SetForbidTS::reason() const {
  // @@protoc_insertion_point(field_get:Admin.SetForbidTS.reason)
  return *reason_;
}
inline void SetForbidTS::set_reason(const ::std::string& value) {
  set_has_reason();
  if (reason_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    reason_ = new ::std::string;
  }
  reason_->assign(value);
  // @@protoc_insertion_point(field_set:Admin.SetForbidTS.reason)
}
inline void SetForbidTS::set_reason(const char* value) {
  set_has_reason();
  if (reason_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    reason_ = new ::std::string;
  }
  reason_->assign(value);
  // @@protoc_insertion_point(field_set_char:Admin.SetForbidTS.reason)
}
inline void SetForbidTS::set_reason(const void* value, size_t size) {
  set_has_reason();
  if (reason_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    reason_ = new ::std::string;
  }
  reason_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:Admin.SetForbidTS.reason)
}
inline ::std::string* SetForbidTS::mutable_reason() {
  set_has_reason();
  if (reason_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    reason_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:Admin.SetForbidTS.reason)
  return reason_;
}
inline ::std::string* SetForbidTS::release_reason() {
  clear_has_reason();
  if (reason_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = reason_;
    reason_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void SetForbidTS::set_allocated_reason(::std::string* reason) {
  if (reason_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete reason_;
  }
  if (reason) {
    set_has_reason();
    reason_ = reason;
  } else {
    clear_has_reason();
    reason_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:Admin.SetForbidTS.reason)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Admin

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Admin_2eproto__INCLUDED
