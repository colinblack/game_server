// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Demo.proto

#ifndef PROTOBUF_Demo_2eproto__INCLUDED
#define PROTOBUF_Demo_2eproto__INCLUDED

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

namespace Demo {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_Demo_2eproto();
void protobuf_AssignDesc_Demo_2eproto();
void protobuf_ShutdownFile_Demo_2eproto();

class Server;
class Demo;

// ===================================================================

class Server : public ::google::protobuf::Message {
 public:
  Server();
  virtual ~Server();

  Server(const Server& from);

  inline Server& operator=(const Server& from) {
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
  static const Server& default_instance();

  void Swap(Server* other);

  // implements Message ----------------------------------------------

  Server* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Server& from);
  void MergeFrom(const Server& from);
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

  // required uint32 begin = 1;
  inline bool has_begin() const;
  inline void clear_begin();
  static const int kBeginFieldNumber = 1;
  inline ::google::protobuf::uint32 begin() const;
  inline void set_begin(::google::protobuf::uint32 value);

  // required uint32 end = 2;
  inline bool has_end() const;
  inline void clear_end();
  static const int kEndFieldNumber = 2;
  inline ::google::protobuf::uint32 end() const;
  inline void set_end(::google::protobuf::uint32 value);

  // required string host = 3;
  inline bool has_host() const;
  inline void clear_host();
  static const int kHostFieldNumber = 3;
  inline const ::std::string& host() const;
  inline void set_host(const ::std::string& value);
  inline void set_host(const char* value);
  inline void set_host(const char* value, size_t size);
  inline ::std::string* mutable_host();
  inline ::std::string* release_host();
  inline void set_allocated_host(::std::string* host);

  // required uint32 port = 4;
  inline bool has_port() const;
  inline void clear_port();
  static const int kPortFieldNumber = 4;
  inline ::google::protobuf::uint32 port() const;
  inline void set_port(::google::protobuf::uint32 value);

  // required string accesshost = 5;
  inline bool has_accesshost() const;
  inline void clear_accesshost();
  static const int kAccesshostFieldNumber = 5;
  inline const ::std::string& accesshost() const;
  inline void set_accesshost(const ::std::string& value);
  inline void set_accesshost(const char* value);
  inline void set_accesshost(const char* value, size_t size);
  inline ::std::string* mutable_accesshost();
  inline ::std::string* release_accesshost();
  inline void set_allocated_accesshost(::std::string* accesshost);

  // required uint32 accessport = 6;
  inline bool has_accessport() const;
  inline void clear_accessport();
  static const int kAccessportFieldNumber = 6;
  inline ::google::protobuf::uint32 accessport() const;
  inline void set_accessport(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:Demo.Server)
 private:
  inline void set_has_begin();
  inline void clear_has_begin();
  inline void set_has_end();
  inline void clear_has_end();
  inline void set_has_host();
  inline void clear_has_host();
  inline void set_has_port();
  inline void clear_has_port();
  inline void set_has_accesshost();
  inline void clear_has_accesshost();
  inline void set_has_accessport();
  inline void clear_has_accessport();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 begin_;
  ::google::protobuf::uint32 end_;
  ::std::string* host_;
  ::std::string* accesshost_;
  ::google::protobuf::uint32 port_;
  ::google::protobuf::uint32 accessport_;
  friend void  protobuf_AddDesc_Demo_2eproto();
  friend void protobuf_AssignDesc_Demo_2eproto();
  friend void protobuf_ShutdownFile_Demo_2eproto();

  void InitAsDefaultInstance();
  static Server* default_instance_;
};
// -------------------------------------------------------------------

class Demo : public ::google::protobuf::Message {
 public:
  Demo();
  virtual ~Demo();

  Demo(const Demo& from);

  inline Demo& operator=(const Demo& from) {
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
  static const Demo& default_instance();

  void Swap(Demo* other);

  // implements Message ----------------------------------------------

  Demo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Demo& from);
  void MergeFrom(const Demo& from);
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

  // repeated .Demo.Server battle = 1;
  inline int battle_size() const;
  inline void clear_battle();
  static const int kBattleFieldNumber = 1;
  inline const ::Demo::Server& battle(int index) const;
  inline ::Demo::Server* mutable_battle(int index);
  inline ::Demo::Server* add_battle();
  inline const ::google::protobuf::RepeatedPtrField< ::Demo::Server >&
      battle() const;
  inline ::google::protobuf::RepeatedPtrField< ::Demo::Server >*
      mutable_battle();

  // repeated uint32 open = 2;
  inline int open_size() const;
  inline void clear_open();
  static const int kOpenFieldNumber = 2;
  inline ::google::protobuf::uint32 open(int index) const;
  inline void set_open(int index, ::google::protobuf::uint32 value);
  inline void add_open(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      open() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_open();

  // @@protoc_insertion_point(class_scope:Demo.Demo)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::Demo::Server > battle_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > open_;
  friend void  protobuf_AddDesc_Demo_2eproto();
  friend void protobuf_AssignDesc_Demo_2eproto();
  friend void protobuf_ShutdownFile_Demo_2eproto();

  void InitAsDefaultInstance();
  static Demo* default_instance_;
};
// ===================================================================


// ===================================================================

// Server

// required uint32 begin = 1;
inline bool Server::has_begin() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Server::set_has_begin() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Server::clear_has_begin() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Server::clear_begin() {
  begin_ = 0u;
  clear_has_begin();
}
inline ::google::protobuf::uint32 Server::begin() const {
  // @@protoc_insertion_point(field_get:Demo.Server.begin)
  return begin_;
}
inline void Server::set_begin(::google::protobuf::uint32 value) {
  set_has_begin();
  begin_ = value;
  // @@protoc_insertion_point(field_set:Demo.Server.begin)
}

// required uint32 end = 2;
inline bool Server::has_end() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Server::set_has_end() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Server::clear_has_end() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Server::clear_end() {
  end_ = 0u;
  clear_has_end();
}
inline ::google::protobuf::uint32 Server::end() const {
  // @@protoc_insertion_point(field_get:Demo.Server.end)
  return end_;
}
inline void Server::set_end(::google::protobuf::uint32 value) {
  set_has_end();
  end_ = value;
  // @@protoc_insertion_point(field_set:Demo.Server.end)
}

// required string host = 3;
inline bool Server::has_host() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Server::set_has_host() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Server::clear_has_host() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Server::clear_host() {
  if (host_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    host_->clear();
  }
  clear_has_host();
}
inline const ::std::string& Server::host() const {
  // @@protoc_insertion_point(field_get:Demo.Server.host)
  return *host_;
}
inline void Server::set_host(const ::std::string& value) {
  set_has_host();
  if (host_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    host_ = new ::std::string;
  }
  host_->assign(value);
  // @@protoc_insertion_point(field_set:Demo.Server.host)
}
inline void Server::set_host(const char* value) {
  set_has_host();
  if (host_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    host_ = new ::std::string;
  }
  host_->assign(value);
  // @@protoc_insertion_point(field_set_char:Demo.Server.host)
}
inline void Server::set_host(const char* value, size_t size) {
  set_has_host();
  if (host_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    host_ = new ::std::string;
  }
  host_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:Demo.Server.host)
}
inline ::std::string* Server::mutable_host() {
  set_has_host();
  if (host_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    host_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:Demo.Server.host)
  return host_;
}
inline ::std::string* Server::release_host() {
  clear_has_host();
  if (host_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = host_;
    host_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void Server::set_allocated_host(::std::string* host) {
  if (host_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete host_;
  }
  if (host) {
    set_has_host();
    host_ = host;
  } else {
    clear_has_host();
    host_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:Demo.Server.host)
}

// required uint32 port = 4;
inline bool Server::has_port() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Server::set_has_port() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Server::clear_has_port() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Server::clear_port() {
  port_ = 0u;
  clear_has_port();
}
inline ::google::protobuf::uint32 Server::port() const {
  // @@protoc_insertion_point(field_get:Demo.Server.port)
  return port_;
}
inline void Server::set_port(::google::protobuf::uint32 value) {
  set_has_port();
  port_ = value;
  // @@protoc_insertion_point(field_set:Demo.Server.port)
}

// required string accesshost = 5;
inline bool Server::has_accesshost() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Server::set_has_accesshost() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Server::clear_has_accesshost() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Server::clear_accesshost() {
  if (accesshost_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    accesshost_->clear();
  }
  clear_has_accesshost();
}
inline const ::std::string& Server::accesshost() const {
  // @@protoc_insertion_point(field_get:Demo.Server.accesshost)
  return *accesshost_;
}
inline void Server::set_accesshost(const ::std::string& value) {
  set_has_accesshost();
  if (accesshost_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    accesshost_ = new ::std::string;
  }
  accesshost_->assign(value);
  // @@protoc_insertion_point(field_set:Demo.Server.accesshost)
}
inline void Server::set_accesshost(const char* value) {
  set_has_accesshost();
  if (accesshost_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    accesshost_ = new ::std::string;
  }
  accesshost_->assign(value);
  // @@protoc_insertion_point(field_set_char:Demo.Server.accesshost)
}
inline void Server::set_accesshost(const char* value, size_t size) {
  set_has_accesshost();
  if (accesshost_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    accesshost_ = new ::std::string;
  }
  accesshost_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:Demo.Server.accesshost)
}
inline ::std::string* Server::mutable_accesshost() {
  set_has_accesshost();
  if (accesshost_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    accesshost_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:Demo.Server.accesshost)
  return accesshost_;
}
inline ::std::string* Server::release_accesshost() {
  clear_has_accesshost();
  if (accesshost_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = accesshost_;
    accesshost_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void Server::set_allocated_accesshost(::std::string* accesshost) {
  if (accesshost_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete accesshost_;
  }
  if (accesshost) {
    set_has_accesshost();
    accesshost_ = accesshost;
  } else {
    clear_has_accesshost();
    accesshost_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:Demo.Server.accesshost)
}

// required uint32 accessport = 6;
inline bool Server::has_accessport() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Server::set_has_accessport() {
  _has_bits_[0] |= 0x00000020u;
}
inline void Server::clear_has_accessport() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void Server::clear_accessport() {
  accessport_ = 0u;
  clear_has_accessport();
}
inline ::google::protobuf::uint32 Server::accessport() const {
  // @@protoc_insertion_point(field_get:Demo.Server.accessport)
  return accessport_;
}
inline void Server::set_accessport(::google::protobuf::uint32 value) {
  set_has_accessport();
  accessport_ = value;
  // @@protoc_insertion_point(field_set:Demo.Server.accessport)
}

// -------------------------------------------------------------------

// Demo

// repeated .Demo.Server battle = 1;
inline int Demo::battle_size() const {
  return battle_.size();
}
inline void Demo::clear_battle() {
  battle_.Clear();
}
inline const ::Demo::Server& Demo::battle(int index) const {
  // @@protoc_insertion_point(field_get:Demo.Demo.battle)
  return battle_.Get(index);
}
inline ::Demo::Server* Demo::mutable_battle(int index) {
  // @@protoc_insertion_point(field_mutable:Demo.Demo.battle)
  return battle_.Mutable(index);
}
inline ::Demo::Server* Demo::add_battle() {
  // @@protoc_insertion_point(field_add:Demo.Demo.battle)
  return battle_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Demo::Server >&
Demo::battle() const {
  // @@protoc_insertion_point(field_list:Demo.Demo.battle)
  return battle_;
}
inline ::google::protobuf::RepeatedPtrField< ::Demo::Server >*
Demo::mutable_battle() {
  // @@protoc_insertion_point(field_mutable_list:Demo.Demo.battle)
  return &battle_;
}

// repeated uint32 open = 2;
inline int Demo::open_size() const {
  return open_.size();
}
inline void Demo::clear_open() {
  open_.Clear();
}
inline ::google::protobuf::uint32 Demo::open(int index) const {
  // @@protoc_insertion_point(field_get:Demo.Demo.open)
  return open_.Get(index);
}
inline void Demo::set_open(int index, ::google::protobuf::uint32 value) {
  open_.Set(index, value);
  // @@protoc_insertion_point(field_set:Demo.Demo.open)
}
inline void Demo::add_open(::google::protobuf::uint32 value) {
  open_.Add(value);
  // @@protoc_insertion_point(field_add:Demo.Demo.open)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
Demo::open() const {
  // @@protoc_insertion_point(field_list:Demo.Demo.open)
  return open_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
Demo::mutable_open() {
  // @@protoc_insertion_point(field_mutable_list:Demo.Demo.open)
  return &open_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Demo

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Demo_2eproto__INCLUDED
