// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProtoNotify.proto

#ifndef PROTOBUF_ProtoNotify_2eproto__INCLUDED
#define PROTOBUF_ProtoNotify_2eproto__INCLUDED

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

namespace ProtoNotify {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ProtoNotify_2eproto();
void protobuf_AssignDesc_ProtoNotify_2eproto();
void protobuf_ShutdownFile_ProtoNotify_2eproto();

class NotifyItemCPP;
class GetNotifyReq;
class GetNotifyResp;

// ===================================================================

class NotifyItemCPP : public ::google::protobuf::Message {
 public:
  NotifyItemCPP();
  virtual ~NotifyItemCPP();

  NotifyItemCPP(const NotifyItemCPP& from);

  inline NotifyItemCPP& operator=(const NotifyItemCPP& from) {
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
  static const NotifyItemCPP& default_instance();

  void Swap(NotifyItemCPP* other);

  // implements Message ----------------------------------------------

  NotifyItemCPP* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const NotifyItemCPP& from);
  void MergeFrom(const NotifyItemCPP& from);
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

  // required uint32 ts = 2;
  inline bool has_ts() const;
  inline void clear_ts();
  static const int kTsFieldNumber = 2;
  inline ::google::protobuf::uint32 ts() const;
  inline void set_ts(::google::protobuf::uint32 value);

  // required bytes content = 3;
  inline bool has_content() const;
  inline void clear_content();
  static const int kContentFieldNumber = 3;
  inline const ::std::string& content() const;
  inline void set_content(const ::std::string& value);
  inline void set_content(const char* value);
  inline void set_content(const void* value, size_t size);
  inline ::std::string* mutable_content();
  inline ::std::string* release_content();
  inline void set_allocated_content(::std::string* content);

  // @@protoc_insertion_point(class_scope:ProtoNotify.NotifyItemCPP)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_ts();
  inline void clear_has_ts();
  inline void set_has_content();
  inline void clear_has_content();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 ts_;
  ::std::string* content_;
  friend void  protobuf_AddDesc_ProtoNotify_2eproto();
  friend void protobuf_AssignDesc_ProtoNotify_2eproto();
  friend void protobuf_ShutdownFile_ProtoNotify_2eproto();

  void InitAsDefaultInstance();
  static NotifyItemCPP* default_instance_;
};
// -------------------------------------------------------------------

class GetNotifyReq : public ::google::protobuf::Message {
 public:
  GetNotifyReq();
  virtual ~GetNotifyReq();

  GetNotifyReq(const GetNotifyReq& from);

  inline GetNotifyReq& operator=(const GetNotifyReq& from) {
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
  static const GetNotifyReq& default_instance();

  void Swap(GetNotifyReq* other);

  // implements Message ----------------------------------------------

  GetNotifyReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GetNotifyReq& from);
  void MergeFrom(const GetNotifyReq& from);
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

  // @@protoc_insertion_point(class_scope:ProtoNotify.GetNotifyReq)
 private:
  inline void set_has_id();
  inline void clear_has_id();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 id_;
  friend void  protobuf_AddDesc_ProtoNotify_2eproto();
  friend void protobuf_AssignDesc_ProtoNotify_2eproto();
  friend void protobuf_ShutdownFile_ProtoNotify_2eproto();

  void InitAsDefaultInstance();
  static GetNotifyReq* default_instance_;
};
// -------------------------------------------------------------------

class GetNotifyResp : public ::google::protobuf::Message {
 public:
  GetNotifyResp();
  virtual ~GetNotifyResp();

  GetNotifyResp(const GetNotifyResp& from);

  inline GetNotifyResp& operator=(const GetNotifyResp& from) {
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
  static const GetNotifyResp& default_instance();

  void Swap(GetNotifyResp* other);

  // implements Message ----------------------------------------------

  GetNotifyResp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GetNotifyResp& from);
  void MergeFrom(const GetNotifyResp& from);
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

  // required .ProtoNotify.NotifyItemCPP notify = 1;
  inline bool has_notify() const;
  inline void clear_notify();
  static const int kNotifyFieldNumber = 1;
  inline const ::ProtoNotify::NotifyItemCPP& notify() const;
  inline ::ProtoNotify::NotifyItemCPP* mutable_notify();
  inline ::ProtoNotify::NotifyItemCPP* release_notify();
  inline void set_allocated_notify(::ProtoNotify::NotifyItemCPP* notify);

  // @@protoc_insertion_point(class_scope:ProtoNotify.GetNotifyResp)
 private:
  inline void set_has_notify();
  inline void clear_has_notify();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::ProtoNotify::NotifyItemCPP* notify_;
  friend void  protobuf_AddDesc_ProtoNotify_2eproto();
  friend void protobuf_AssignDesc_ProtoNotify_2eproto();
  friend void protobuf_ShutdownFile_ProtoNotify_2eproto();

  void InitAsDefaultInstance();
  static GetNotifyResp* default_instance_;
};
// ===================================================================


// ===================================================================

// NotifyItemCPP

// required uint32 id = 1;
inline bool NotifyItemCPP::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void NotifyItemCPP::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void NotifyItemCPP::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void NotifyItemCPP::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 NotifyItemCPP::id() const {
  // @@protoc_insertion_point(field_get:ProtoNotify.NotifyItemCPP.id)
  return id_;
}
inline void NotifyItemCPP::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:ProtoNotify.NotifyItemCPP.id)
}

// required uint32 ts = 2;
inline bool NotifyItemCPP::has_ts() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void NotifyItemCPP::set_has_ts() {
  _has_bits_[0] |= 0x00000002u;
}
inline void NotifyItemCPP::clear_has_ts() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void NotifyItemCPP::clear_ts() {
  ts_ = 0u;
  clear_has_ts();
}
inline ::google::protobuf::uint32 NotifyItemCPP::ts() const {
  // @@protoc_insertion_point(field_get:ProtoNotify.NotifyItemCPP.ts)
  return ts_;
}
inline void NotifyItemCPP::set_ts(::google::protobuf::uint32 value) {
  set_has_ts();
  ts_ = value;
  // @@protoc_insertion_point(field_set:ProtoNotify.NotifyItemCPP.ts)
}

// required bytes content = 3;
inline bool NotifyItemCPP::has_content() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void NotifyItemCPP::set_has_content() {
  _has_bits_[0] |= 0x00000004u;
}
inline void NotifyItemCPP::clear_has_content() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void NotifyItemCPP::clear_content() {
  if (content_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    content_->clear();
  }
  clear_has_content();
}
inline const ::std::string& NotifyItemCPP::content() const {
  // @@protoc_insertion_point(field_get:ProtoNotify.NotifyItemCPP.content)
  return *content_;
}
inline void NotifyItemCPP::set_content(const ::std::string& value) {
  set_has_content();
  if (content_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    content_ = new ::std::string;
  }
  content_->assign(value);
  // @@protoc_insertion_point(field_set:ProtoNotify.NotifyItemCPP.content)
}
inline void NotifyItemCPP::set_content(const char* value) {
  set_has_content();
  if (content_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    content_ = new ::std::string;
  }
  content_->assign(value);
  // @@protoc_insertion_point(field_set_char:ProtoNotify.NotifyItemCPP.content)
}
inline void NotifyItemCPP::set_content(const void* value, size_t size) {
  set_has_content();
  if (content_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    content_ = new ::std::string;
  }
  content_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:ProtoNotify.NotifyItemCPP.content)
}
inline ::std::string* NotifyItemCPP::mutable_content() {
  set_has_content();
  if (content_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    content_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:ProtoNotify.NotifyItemCPP.content)
  return content_;
}
inline ::std::string* NotifyItemCPP::release_content() {
  clear_has_content();
  if (content_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = content_;
    content_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void NotifyItemCPP::set_allocated_content(::std::string* content) {
  if (content_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete content_;
  }
  if (content) {
    set_has_content();
    content_ = content;
  } else {
    clear_has_content();
    content_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:ProtoNotify.NotifyItemCPP.content)
}

// -------------------------------------------------------------------

// GetNotifyReq

// required uint32 id = 1;
inline bool GetNotifyReq::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GetNotifyReq::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void GetNotifyReq::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void GetNotifyReq::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 GetNotifyReq::id() const {
  // @@protoc_insertion_point(field_get:ProtoNotify.GetNotifyReq.id)
  return id_;
}
inline void GetNotifyReq::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:ProtoNotify.GetNotifyReq.id)
}

// -------------------------------------------------------------------

// GetNotifyResp

// required .ProtoNotify.NotifyItemCPP notify = 1;
inline bool GetNotifyResp::has_notify() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GetNotifyResp::set_has_notify() {
  _has_bits_[0] |= 0x00000001u;
}
inline void GetNotifyResp::clear_has_notify() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void GetNotifyResp::clear_notify() {
  if (notify_ != NULL) notify_->::ProtoNotify::NotifyItemCPP::Clear();
  clear_has_notify();
}
inline const ::ProtoNotify::NotifyItemCPP& GetNotifyResp::notify() const {
  // @@protoc_insertion_point(field_get:ProtoNotify.GetNotifyResp.notify)
  return notify_ != NULL ? *notify_ : *default_instance_->notify_;
}
inline ::ProtoNotify::NotifyItemCPP* GetNotifyResp::mutable_notify() {
  set_has_notify();
  if (notify_ == NULL) notify_ = new ::ProtoNotify::NotifyItemCPP;
  // @@protoc_insertion_point(field_mutable:ProtoNotify.GetNotifyResp.notify)
  return notify_;
}
inline ::ProtoNotify::NotifyItemCPP* GetNotifyResp::release_notify() {
  clear_has_notify();
  ::ProtoNotify::NotifyItemCPP* temp = notify_;
  notify_ = NULL;
  return temp;
}
inline void GetNotifyResp::set_allocated_notify(::ProtoNotify::NotifyItemCPP* notify) {
  delete notify_;
  notify_ = notify;
  if (notify) {
    set_has_notify();
  } else {
    clear_has_notify();
  }
  // @@protoc_insertion_point(field_set_allocated:ProtoNotify.GetNotifyResp.notify)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ProtoNotify

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ProtoNotify_2eproto__INCLUDED
