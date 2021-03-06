// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: SystemMsg.proto

#ifndef PROTOBUF_SystemMsg_2eproto__INCLUDED
#define PROTOBUF_SystemMsg_2eproto__INCLUDED

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

namespace SysgemMsg {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_SystemMsg_2eproto();
void protobuf_AssignDesc_SystemMsg_2eproto();
void protobuf_ShutdownFile_SystemMsg_2eproto();

class SysgemMsgData;
class SysgemMsgReward;
class SysgemMsgItem;
class SysgemMsg;

// ===================================================================

class SysgemMsgData : public ::google::protobuf::Message {
 public:
  SysgemMsgData();
  virtual ~SysgemMsgData();

  SysgemMsgData(const SysgemMsgData& from);

  inline SysgemMsgData& operator=(const SysgemMsgData& from) {
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
  static const SysgemMsgData& default_instance();

  void Swap(SysgemMsgData* other);

  // implements Message ----------------------------------------------

  SysgemMsgData* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SysgemMsgData& from);
  void MergeFrom(const SysgemMsgData& from);
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

  // required uint32 k = 1;
  inline bool has_k() const;
  inline void clear_k();
  static const int kKFieldNumber = 1;
  inline ::google::protobuf::uint32 k() const;
  inline void set_k(::google::protobuf::uint32 value);

  // required uint32 v = 2;
  inline bool has_v() const;
  inline void clear_v();
  static const int kVFieldNumber = 2;
  inline ::google::protobuf::uint32 v() const;
  inline void set_v(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:SysgemMsg.SysgemMsgData)
 private:
  inline void set_has_k();
  inline void clear_has_k();
  inline void set_has_v();
  inline void clear_has_v();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 k_;
  ::google::protobuf::uint32 v_;
  friend void  protobuf_AddDesc_SystemMsg_2eproto();
  friend void protobuf_AssignDesc_SystemMsg_2eproto();
  friend void protobuf_ShutdownFile_SystemMsg_2eproto();

  void InitAsDefaultInstance();
  static SysgemMsgData* default_instance_;
};
// -------------------------------------------------------------------

class SysgemMsgReward : public ::google::protobuf::Message {
 public:
  SysgemMsgReward();
  virtual ~SysgemMsgReward();

  SysgemMsgReward(const SysgemMsgReward& from);

  inline SysgemMsgReward& operator=(const SysgemMsgReward& from) {
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
  static const SysgemMsgReward& default_instance();

  void Swap(SysgemMsgReward* other);

  // implements Message ----------------------------------------------

  SysgemMsgReward* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SysgemMsgReward& from);
  void MergeFrom(const SysgemMsgReward& from);
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

  // required uint32 t = 1;
  inline bool has_t() const;
  inline void clear_t();
  static const int kTFieldNumber = 1;
  inline ::google::protobuf::uint32 t() const;
  inline void set_t(::google::protobuf::uint32 value);

  // required uint32 id = 2;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 2;
  inline ::google::protobuf::uint32 id() const;
  inline void set_id(::google::protobuf::uint32 value);

  // required uint32 c = 3;
  inline bool has_c() const;
  inline void clear_c();
  static const int kCFieldNumber = 3;
  inline ::google::protobuf::uint32 c() const;
  inline void set_c(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:SysgemMsg.SysgemMsgReward)
 private:
  inline void set_has_t();
  inline void clear_has_t();
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_c();
  inline void clear_has_c();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 t_;
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 c_;
  friend void  protobuf_AddDesc_SystemMsg_2eproto();
  friend void protobuf_AssignDesc_SystemMsg_2eproto();
  friend void protobuf_ShutdownFile_SystemMsg_2eproto();

  void InitAsDefaultInstance();
  static SysgemMsgReward* default_instance_;
};
// -------------------------------------------------------------------

class SysgemMsgItem : public ::google::protobuf::Message {
 public:
  SysgemMsgItem();
  virtual ~SysgemMsgItem();

  SysgemMsgItem(const SysgemMsgItem& from);

  inline SysgemMsgItem& operator=(const SysgemMsgItem& from) {
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
  static const SysgemMsgItem& default_instance();

  void Swap(SysgemMsgItem* other);

  // implements Message ----------------------------------------------

  SysgemMsgItem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SysgemMsgItem& from);
  void MergeFrom(const SysgemMsgItem& from);
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

  // required uint32 ts = 1;
  inline bool has_ts() const;
  inline void clear_ts();
  static const int kTsFieldNumber = 1;
  inline ::google::protobuf::uint32 ts() const;
  inline void set_ts(::google::protobuf::uint32 value);

  // required uint32 uid = 2;
  inline bool has_uid() const;
  inline void clear_uid();
  static const int kUidFieldNumber = 2;
  inline ::google::protobuf::uint32 uid() const;
  inline void set_uid(::google::protobuf::uint32 value);

  // required string user_name = 3;
  inline bool has_user_name() const;
  inline void clear_user_name();
  static const int kUserNameFieldNumber = 3;
  inline const ::std::string& user_name() const;
  inline void set_user_name(const ::std::string& value);
  inline void set_user_name(const char* value);
  inline void set_user_name(const char* value, size_t size);
  inline ::std::string* mutable_user_name();
  inline ::std::string* release_user_name();
  inline void set_allocated_user_name(::std::string* user_name);

  // repeated .SysgemMsg.SysgemMsgData data = 4;
  inline int data_size() const;
  inline void clear_data();
  static const int kDataFieldNumber = 4;
  inline const ::SysgemMsg::SysgemMsgData& data(int index) const;
  inline ::SysgemMsg::SysgemMsgData* mutable_data(int index);
  inline ::SysgemMsg::SysgemMsgData* add_data();
  inline const ::google::protobuf::RepeatedPtrField< ::SysgemMsg::SysgemMsgData >&
      data() const;
  inline ::google::protobuf::RepeatedPtrField< ::SysgemMsg::SysgemMsgData >*
      mutable_data();

  // repeated .SysgemMsg.SysgemMsgReward reward = 5;
  inline int reward_size() const;
  inline void clear_reward();
  static const int kRewardFieldNumber = 5;
  inline const ::SysgemMsg::SysgemMsgReward& reward(int index) const;
  inline ::SysgemMsg::SysgemMsgReward* mutable_reward(int index);
  inline ::SysgemMsg::SysgemMsgReward* add_reward();
  inline const ::google::protobuf::RepeatedPtrField< ::SysgemMsg::SysgemMsgReward >&
      reward() const;
  inline ::google::protobuf::RepeatedPtrField< ::SysgemMsg::SysgemMsgReward >*
      mutable_reward();

  // @@protoc_insertion_point(class_scope:SysgemMsg.SysgemMsgItem)
 private:
  inline void set_has_ts();
  inline void clear_has_ts();
  inline void set_has_uid();
  inline void clear_has_uid();
  inline void set_has_user_name();
  inline void clear_has_user_name();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 ts_;
  ::google::protobuf::uint32 uid_;
  ::std::string* user_name_;
  ::google::protobuf::RepeatedPtrField< ::SysgemMsg::SysgemMsgData > data_;
  ::google::protobuf::RepeatedPtrField< ::SysgemMsg::SysgemMsgReward > reward_;
  friend void  protobuf_AddDesc_SystemMsg_2eproto();
  friend void protobuf_AssignDesc_SystemMsg_2eproto();
  friend void protobuf_ShutdownFile_SystemMsg_2eproto();

  void InitAsDefaultInstance();
  static SysgemMsgItem* default_instance_;
};
// -------------------------------------------------------------------

class SysgemMsg : public ::google::protobuf::Message {
 public:
  SysgemMsg();
  virtual ~SysgemMsg();

  SysgemMsg(const SysgemMsg& from);

  inline SysgemMsg& operator=(const SysgemMsg& from) {
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
  static const SysgemMsg& default_instance();

  void Swap(SysgemMsg* other);

  // implements Message ----------------------------------------------

  SysgemMsg* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SysgemMsg& from);
  void MergeFrom(const SysgemMsg& from);
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

  // repeated .SysgemMsg.SysgemMsgItem items = 1;
  inline int items_size() const;
  inline void clear_items();
  static const int kItemsFieldNumber = 1;
  inline const ::SysgemMsg::SysgemMsgItem& items(int index) const;
  inline ::SysgemMsg::SysgemMsgItem* mutable_items(int index);
  inline ::SysgemMsg::SysgemMsgItem* add_items();
  inline const ::google::protobuf::RepeatedPtrField< ::SysgemMsg::SysgemMsgItem >&
      items() const;
  inline ::google::protobuf::RepeatedPtrField< ::SysgemMsg::SysgemMsgItem >*
      mutable_items();

  // @@protoc_insertion_point(class_scope:SysgemMsg.SysgemMsg)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::SysgemMsg::SysgemMsgItem > items_;
  friend void  protobuf_AddDesc_SystemMsg_2eproto();
  friend void protobuf_AssignDesc_SystemMsg_2eproto();
  friend void protobuf_ShutdownFile_SystemMsg_2eproto();

  void InitAsDefaultInstance();
  static SysgemMsg* default_instance_;
};
// ===================================================================


// ===================================================================

// SysgemMsgData

// required uint32 k = 1;
inline bool SysgemMsgData::has_k() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SysgemMsgData::set_has_k() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SysgemMsgData::clear_has_k() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SysgemMsgData::clear_k() {
  k_ = 0u;
  clear_has_k();
}
inline ::google::protobuf::uint32 SysgemMsgData::k() const {
  // @@protoc_insertion_point(field_get:SysgemMsg.SysgemMsgData.k)
  return k_;
}
inline void SysgemMsgData::set_k(::google::protobuf::uint32 value) {
  set_has_k();
  k_ = value;
  // @@protoc_insertion_point(field_set:SysgemMsg.SysgemMsgData.k)
}

// required uint32 v = 2;
inline bool SysgemMsgData::has_v() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SysgemMsgData::set_has_v() {
  _has_bits_[0] |= 0x00000002u;
}
inline void SysgemMsgData::clear_has_v() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void SysgemMsgData::clear_v() {
  v_ = 0u;
  clear_has_v();
}
inline ::google::protobuf::uint32 SysgemMsgData::v() const {
  // @@protoc_insertion_point(field_get:SysgemMsg.SysgemMsgData.v)
  return v_;
}
inline void SysgemMsgData::set_v(::google::protobuf::uint32 value) {
  set_has_v();
  v_ = value;
  // @@protoc_insertion_point(field_set:SysgemMsg.SysgemMsgData.v)
}

// -------------------------------------------------------------------

// SysgemMsgReward

// required uint32 t = 1;
inline bool SysgemMsgReward::has_t() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SysgemMsgReward::set_has_t() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SysgemMsgReward::clear_has_t() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SysgemMsgReward::clear_t() {
  t_ = 0u;
  clear_has_t();
}
inline ::google::protobuf::uint32 SysgemMsgReward::t() const {
  // @@protoc_insertion_point(field_get:SysgemMsg.SysgemMsgReward.t)
  return t_;
}
inline void SysgemMsgReward::set_t(::google::protobuf::uint32 value) {
  set_has_t();
  t_ = value;
  // @@protoc_insertion_point(field_set:SysgemMsg.SysgemMsgReward.t)
}

// required uint32 id = 2;
inline bool SysgemMsgReward::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SysgemMsgReward::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void SysgemMsgReward::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void SysgemMsgReward::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 SysgemMsgReward::id() const {
  // @@protoc_insertion_point(field_get:SysgemMsg.SysgemMsgReward.id)
  return id_;
}
inline void SysgemMsgReward::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:SysgemMsg.SysgemMsgReward.id)
}

// required uint32 c = 3;
inline bool SysgemMsgReward::has_c() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void SysgemMsgReward::set_has_c() {
  _has_bits_[0] |= 0x00000004u;
}
inline void SysgemMsgReward::clear_has_c() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void SysgemMsgReward::clear_c() {
  c_ = 0u;
  clear_has_c();
}
inline ::google::protobuf::uint32 SysgemMsgReward::c() const {
  // @@protoc_insertion_point(field_get:SysgemMsg.SysgemMsgReward.c)
  return c_;
}
inline void SysgemMsgReward::set_c(::google::protobuf::uint32 value) {
  set_has_c();
  c_ = value;
  // @@protoc_insertion_point(field_set:SysgemMsg.SysgemMsgReward.c)
}

// -------------------------------------------------------------------

// SysgemMsgItem

// required uint32 ts = 1;
inline bool SysgemMsgItem::has_ts() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SysgemMsgItem::set_has_ts() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SysgemMsgItem::clear_has_ts() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SysgemMsgItem::clear_ts() {
  ts_ = 0u;
  clear_has_ts();
}
inline ::google::protobuf::uint32 SysgemMsgItem::ts() const {
  // @@protoc_insertion_point(field_get:SysgemMsg.SysgemMsgItem.ts)
  return ts_;
}
inline void SysgemMsgItem::set_ts(::google::protobuf::uint32 value) {
  set_has_ts();
  ts_ = value;
  // @@protoc_insertion_point(field_set:SysgemMsg.SysgemMsgItem.ts)
}

// required uint32 uid = 2;
inline bool SysgemMsgItem::has_uid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SysgemMsgItem::set_has_uid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void SysgemMsgItem::clear_has_uid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void SysgemMsgItem::clear_uid() {
  uid_ = 0u;
  clear_has_uid();
}
inline ::google::protobuf::uint32 SysgemMsgItem::uid() const {
  // @@protoc_insertion_point(field_get:SysgemMsg.SysgemMsgItem.uid)
  return uid_;
}
inline void SysgemMsgItem::set_uid(::google::protobuf::uint32 value) {
  set_has_uid();
  uid_ = value;
  // @@protoc_insertion_point(field_set:SysgemMsg.SysgemMsgItem.uid)
}

// required string user_name = 3;
inline bool SysgemMsgItem::has_user_name() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void SysgemMsgItem::set_has_user_name() {
  _has_bits_[0] |= 0x00000004u;
}
inline void SysgemMsgItem::clear_has_user_name() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void SysgemMsgItem::clear_user_name() {
  if (user_name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    user_name_->clear();
  }
  clear_has_user_name();
}
inline const ::std::string& SysgemMsgItem::user_name() const {
  // @@protoc_insertion_point(field_get:SysgemMsg.SysgemMsgItem.user_name)
  return *user_name_;
}
inline void SysgemMsgItem::set_user_name(const ::std::string& value) {
  set_has_user_name();
  if (user_name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    user_name_ = new ::std::string;
  }
  user_name_->assign(value);
  // @@protoc_insertion_point(field_set:SysgemMsg.SysgemMsgItem.user_name)
}
inline void SysgemMsgItem::set_user_name(const char* value) {
  set_has_user_name();
  if (user_name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    user_name_ = new ::std::string;
  }
  user_name_->assign(value);
  // @@protoc_insertion_point(field_set_char:SysgemMsg.SysgemMsgItem.user_name)
}
inline void SysgemMsgItem::set_user_name(const char* value, size_t size) {
  set_has_user_name();
  if (user_name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    user_name_ = new ::std::string;
  }
  user_name_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:SysgemMsg.SysgemMsgItem.user_name)
}
inline ::std::string* SysgemMsgItem::mutable_user_name() {
  set_has_user_name();
  if (user_name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    user_name_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:SysgemMsg.SysgemMsgItem.user_name)
  return user_name_;
}
inline ::std::string* SysgemMsgItem::release_user_name() {
  clear_has_user_name();
  if (user_name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = user_name_;
    user_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void SysgemMsgItem::set_allocated_user_name(::std::string* user_name) {
  if (user_name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete user_name_;
  }
  if (user_name) {
    set_has_user_name();
    user_name_ = user_name;
  } else {
    clear_has_user_name();
    user_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:SysgemMsg.SysgemMsgItem.user_name)
}

// repeated .SysgemMsg.SysgemMsgData data = 4;
inline int SysgemMsgItem::data_size() const {
  return data_.size();
}
inline void SysgemMsgItem::clear_data() {
  data_.Clear();
}
inline const ::SysgemMsg::SysgemMsgData& SysgemMsgItem::data(int index) const {
  // @@protoc_insertion_point(field_get:SysgemMsg.SysgemMsgItem.data)
  return data_.Get(index);
}
inline ::SysgemMsg::SysgemMsgData* SysgemMsgItem::mutable_data(int index) {
  // @@protoc_insertion_point(field_mutable:SysgemMsg.SysgemMsgItem.data)
  return data_.Mutable(index);
}
inline ::SysgemMsg::SysgemMsgData* SysgemMsgItem::add_data() {
  // @@protoc_insertion_point(field_add:SysgemMsg.SysgemMsgItem.data)
  return data_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::SysgemMsg::SysgemMsgData >&
SysgemMsgItem::data() const {
  // @@protoc_insertion_point(field_list:SysgemMsg.SysgemMsgItem.data)
  return data_;
}
inline ::google::protobuf::RepeatedPtrField< ::SysgemMsg::SysgemMsgData >*
SysgemMsgItem::mutable_data() {
  // @@protoc_insertion_point(field_mutable_list:SysgemMsg.SysgemMsgItem.data)
  return &data_;
}

// repeated .SysgemMsg.SysgemMsgReward reward = 5;
inline int SysgemMsgItem::reward_size() const {
  return reward_.size();
}
inline void SysgemMsgItem::clear_reward() {
  reward_.Clear();
}
inline const ::SysgemMsg::SysgemMsgReward& SysgemMsgItem::reward(int index) const {
  // @@protoc_insertion_point(field_get:SysgemMsg.SysgemMsgItem.reward)
  return reward_.Get(index);
}
inline ::SysgemMsg::SysgemMsgReward* SysgemMsgItem::mutable_reward(int index) {
  // @@protoc_insertion_point(field_mutable:SysgemMsg.SysgemMsgItem.reward)
  return reward_.Mutable(index);
}
inline ::SysgemMsg::SysgemMsgReward* SysgemMsgItem::add_reward() {
  // @@protoc_insertion_point(field_add:SysgemMsg.SysgemMsgItem.reward)
  return reward_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::SysgemMsg::SysgemMsgReward >&
SysgemMsgItem::reward() const {
  // @@protoc_insertion_point(field_list:SysgemMsg.SysgemMsgItem.reward)
  return reward_;
}
inline ::google::protobuf::RepeatedPtrField< ::SysgemMsg::SysgemMsgReward >*
SysgemMsgItem::mutable_reward() {
  // @@protoc_insertion_point(field_mutable_list:SysgemMsg.SysgemMsgItem.reward)
  return &reward_;
}

// -------------------------------------------------------------------

// SysgemMsg

// repeated .SysgemMsg.SysgemMsgItem items = 1;
inline int SysgemMsg::items_size() const {
  return items_.size();
}
inline void SysgemMsg::clear_items() {
  items_.Clear();
}
inline const ::SysgemMsg::SysgemMsgItem& SysgemMsg::items(int index) const {
  // @@protoc_insertion_point(field_get:SysgemMsg.SysgemMsg.items)
  return items_.Get(index);
}
inline ::SysgemMsg::SysgemMsgItem* SysgemMsg::mutable_items(int index) {
  // @@protoc_insertion_point(field_mutable:SysgemMsg.SysgemMsg.items)
  return items_.Mutable(index);
}
inline ::SysgemMsg::SysgemMsgItem* SysgemMsg::add_items() {
  // @@protoc_insertion_point(field_add:SysgemMsg.SysgemMsg.items)
  return items_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::SysgemMsg::SysgemMsgItem >&
SysgemMsg::items() const {
  // @@protoc_insertion_point(field_list:SysgemMsg.SysgemMsg.items)
  return items_;
}
inline ::google::protobuf::RepeatedPtrField< ::SysgemMsg::SysgemMsgItem >*
SysgemMsg::mutable_items() {
  // @@protoc_insertion_point(field_mutable_list:SysgemMsg.SysgemMsg.items)
  return &items_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace SysgemMsg

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_SystemMsg_2eproto__INCLUDED
