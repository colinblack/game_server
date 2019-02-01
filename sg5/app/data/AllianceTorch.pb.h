// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: AllianceTorch.proto

#ifndef PROTOBUF_AllianceTorch_2eproto__INCLUDED
#define PROTOBUF_AllianceTorch_2eproto__INCLUDED

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

namespace AllianceTorch {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_AllianceTorch_2eproto();
void protobuf_AssignDesc_AllianceTorch_2eproto();
void protobuf_ShutdownFile_AllianceTorch_2eproto();

class CurrTorchStatus;
class LogBuyRecord;
class SingleAllianceTorch;
class AllianceTorch;

// ===================================================================

class CurrTorchStatus : public ::google::protobuf::Message {
 public:
  CurrTorchStatus();
  virtual ~CurrTorchStatus();

  CurrTorchStatus(const CurrTorchStatus& from);

  inline CurrTorchStatus& operator=(const CurrTorchStatus& from) {
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
  static const CurrTorchStatus& default_instance();

  void Swap(CurrTorchStatus* other);

  // implements Message ----------------------------------------------

  CurrTorchStatus* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CurrTorchStatus& from);
  void MergeFrom(const CurrTorchStatus& from);
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

  // required uint32 tid = 1;
  inline bool has_tid() const;
  inline void clear_tid();
  static const int kTidFieldNumber = 1;
  inline ::google::protobuf::uint32 tid() const;
  inline void set_tid(::google::protobuf::uint32 value);

  // required uint32 status = 2;
  inline bool has_status() const;
  inline void clear_status();
  static const int kStatusFieldNumber = 2;
  inline ::google::protobuf::uint32 status() const;
  inline void set_status(::google::protobuf::uint32 value);

  // required uint32 uid = 3;
  inline bool has_uid() const;
  inline void clear_uid();
  static const int kUidFieldNumber = 3;
  inline ::google::protobuf::uint32 uid() const;
  inline void set_uid(::google::protobuf::uint32 value);

  // required uint32 ts = 4;
  inline bool has_ts() const;
  inline void clear_ts();
  static const int kTsFieldNumber = 4;
  inline ::google::protobuf::uint32 ts() const;
  inline void set_ts(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:AllianceTorch.CurrTorchStatus)
 private:
  inline void set_has_tid();
  inline void clear_has_tid();
  inline void set_has_status();
  inline void clear_has_status();
  inline void set_has_uid();
  inline void clear_has_uid();
  inline void set_has_ts();
  inline void clear_has_ts();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 tid_;
  ::google::protobuf::uint32 status_;
  ::google::protobuf::uint32 uid_;
  ::google::protobuf::uint32 ts_;
  friend void  protobuf_AddDesc_AllianceTorch_2eproto();
  friend void protobuf_AssignDesc_AllianceTorch_2eproto();
  friend void protobuf_ShutdownFile_AllianceTorch_2eproto();

  void InitAsDefaultInstance();
  static CurrTorchStatus* default_instance_;
};
// -------------------------------------------------------------------

class LogBuyRecord : public ::google::protobuf::Message {
 public:
  LogBuyRecord();
  virtual ~LogBuyRecord();

  LogBuyRecord(const LogBuyRecord& from);

  inline LogBuyRecord& operator=(const LogBuyRecord& from) {
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
  static const LogBuyRecord& default_instance();

  void Swap(LogBuyRecord* other);

  // implements Message ----------------------------------------------

  LogBuyRecord* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const LogBuyRecord& from);
  void MergeFrom(const LogBuyRecord& from);
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

  // required uint32 time = 1;
  inline bool has_time() const;
  inline void clear_time();
  static const int kTimeFieldNumber = 1;
  inline ::google::protobuf::uint32 time() const;
  inline void set_time(::google::protobuf::uint32 value);

  // required uint32 uid = 2;
  inline bool has_uid() const;
  inline void clear_uid();
  static const int kUidFieldNumber = 2;
  inline ::google::protobuf::uint32 uid() const;
  inline void set_uid(::google::protobuf::uint32 value);

  // required uint32 tid = 3;
  inline bool has_tid() const;
  inline void clear_tid();
  static const int kTidFieldNumber = 3;
  inline ::google::protobuf::uint32 tid() const;
  inline void set_tid(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:AllianceTorch.LogBuyRecord)
 private:
  inline void set_has_time();
  inline void clear_has_time();
  inline void set_has_uid();
  inline void clear_has_uid();
  inline void set_has_tid();
  inline void clear_has_tid();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 time_;
  ::google::protobuf::uint32 uid_;
  ::google::protobuf::uint32 tid_;
  friend void  protobuf_AddDesc_AllianceTorch_2eproto();
  friend void protobuf_AssignDesc_AllianceTorch_2eproto();
  friend void protobuf_ShutdownFile_AllianceTorch_2eproto();

  void InitAsDefaultInstance();
  static LogBuyRecord* default_instance_;
};
// -------------------------------------------------------------------

class SingleAllianceTorch : public ::google::protobuf::Message {
 public:
  SingleAllianceTorch();
  virtual ~SingleAllianceTorch();

  SingleAllianceTorch(const SingleAllianceTorch& from);

  inline SingleAllianceTorch& operator=(const SingleAllianceTorch& from) {
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
  static const SingleAllianceTorch& default_instance();

  void Swap(SingleAllianceTorch* other);

  // implements Message ----------------------------------------------

  SingleAllianceTorch* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SingleAllianceTorch& from);
  void MergeFrom(const SingleAllianceTorch& from);
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

  // required uint32 aid = 1;
  inline bool has_aid() const;
  inline void clear_aid();
  static const int kAidFieldNumber = 1;
  inline ::google::protobuf::uint32 aid() const;
  inline void set_aid(::google::protobuf::uint32 value);

  // repeated .AllianceTorch.CurrTorchStatus curr = 2;
  inline int curr_size() const;
  inline void clear_curr();
  static const int kCurrFieldNumber = 2;
  inline const ::AllianceTorch::CurrTorchStatus& curr(int index) const;
  inline ::AllianceTorch::CurrTorchStatus* mutable_curr(int index);
  inline ::AllianceTorch::CurrTorchStatus* add_curr();
  inline const ::google::protobuf::RepeatedPtrField< ::AllianceTorch::CurrTorchStatus >&
      curr() const;
  inline ::google::protobuf::RepeatedPtrField< ::AllianceTorch::CurrTorchStatus >*
      mutable_curr();

  // repeated .AllianceTorch.LogBuyRecord log = 3;
  inline int log_size() const;
  inline void clear_log();
  static const int kLogFieldNumber = 3;
  inline const ::AllianceTorch::LogBuyRecord& log(int index) const;
  inline ::AllianceTorch::LogBuyRecord* mutable_log(int index);
  inline ::AllianceTorch::LogBuyRecord* add_log();
  inline const ::google::protobuf::RepeatedPtrField< ::AllianceTorch::LogBuyRecord >&
      log() const;
  inline ::google::protobuf::RepeatedPtrField< ::AllianceTorch::LogBuyRecord >*
      mutable_log();

  // @@protoc_insertion_point(class_scope:AllianceTorch.SingleAllianceTorch)
 private:
  inline void set_has_aid();
  inline void clear_has_aid();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::AllianceTorch::CurrTorchStatus > curr_;
  ::google::protobuf::RepeatedPtrField< ::AllianceTorch::LogBuyRecord > log_;
  ::google::protobuf::uint32 aid_;
  friend void  protobuf_AddDesc_AllianceTorch_2eproto();
  friend void protobuf_AssignDesc_AllianceTorch_2eproto();
  friend void protobuf_ShutdownFile_AllianceTorch_2eproto();

  void InitAsDefaultInstance();
  static SingleAllianceTorch* default_instance_;
};
// -------------------------------------------------------------------

class AllianceTorch : public ::google::protobuf::Message {
 public:
  AllianceTorch();
  virtual ~AllianceTorch();

  AllianceTorch(const AllianceTorch& from);

  inline AllianceTorch& operator=(const AllianceTorch& from) {
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
  static const AllianceTorch& default_instance();

  void Swap(AllianceTorch* other);

  // implements Message ----------------------------------------------

  AllianceTorch* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AllianceTorch& from);
  void MergeFrom(const AllianceTorch& from);
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

  // repeated .AllianceTorch.SingleAllianceTorch alliance = 1;
  inline int alliance_size() const;
  inline void clear_alliance();
  static const int kAllianceFieldNumber = 1;
  inline const ::AllianceTorch::SingleAllianceTorch& alliance(int index) const;
  inline ::AllianceTorch::SingleAllianceTorch* mutable_alliance(int index);
  inline ::AllianceTorch::SingleAllianceTorch* add_alliance();
  inline const ::google::protobuf::RepeatedPtrField< ::AllianceTorch::SingleAllianceTorch >&
      alliance() const;
  inline ::google::protobuf::RepeatedPtrField< ::AllianceTorch::SingleAllianceTorch >*
      mutable_alliance();

  // @@protoc_insertion_point(class_scope:AllianceTorch.AllianceTorch)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::AllianceTorch::SingleAllianceTorch > alliance_;
  friend void  protobuf_AddDesc_AllianceTorch_2eproto();
  friend void protobuf_AssignDesc_AllianceTorch_2eproto();
  friend void protobuf_ShutdownFile_AllianceTorch_2eproto();

  void InitAsDefaultInstance();
  static AllianceTorch* default_instance_;
};
// ===================================================================


// ===================================================================

// CurrTorchStatus

// required uint32 tid = 1;
inline bool CurrTorchStatus::has_tid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CurrTorchStatus::set_has_tid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CurrTorchStatus::clear_has_tid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void CurrTorchStatus::clear_tid() {
  tid_ = 0u;
  clear_has_tid();
}
inline ::google::protobuf::uint32 CurrTorchStatus::tid() const {
  // @@protoc_insertion_point(field_get:AllianceTorch.CurrTorchStatus.tid)
  return tid_;
}
inline void CurrTorchStatus::set_tid(::google::protobuf::uint32 value) {
  set_has_tid();
  tid_ = value;
  // @@protoc_insertion_point(field_set:AllianceTorch.CurrTorchStatus.tid)
}

// required uint32 status = 2;
inline bool CurrTorchStatus::has_status() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void CurrTorchStatus::set_has_status() {
  _has_bits_[0] |= 0x00000002u;
}
inline void CurrTorchStatus::clear_has_status() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void CurrTorchStatus::clear_status() {
  status_ = 0u;
  clear_has_status();
}
inline ::google::protobuf::uint32 CurrTorchStatus::status() const {
  // @@protoc_insertion_point(field_get:AllianceTorch.CurrTorchStatus.status)
  return status_;
}
inline void CurrTorchStatus::set_status(::google::protobuf::uint32 value) {
  set_has_status();
  status_ = value;
  // @@protoc_insertion_point(field_set:AllianceTorch.CurrTorchStatus.status)
}

// required uint32 uid = 3;
inline bool CurrTorchStatus::has_uid() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void CurrTorchStatus::set_has_uid() {
  _has_bits_[0] |= 0x00000004u;
}
inline void CurrTorchStatus::clear_has_uid() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void CurrTorchStatus::clear_uid() {
  uid_ = 0u;
  clear_has_uid();
}
inline ::google::protobuf::uint32 CurrTorchStatus::uid() const {
  // @@protoc_insertion_point(field_get:AllianceTorch.CurrTorchStatus.uid)
  return uid_;
}
inline void CurrTorchStatus::set_uid(::google::protobuf::uint32 value) {
  set_has_uid();
  uid_ = value;
  // @@protoc_insertion_point(field_set:AllianceTorch.CurrTorchStatus.uid)
}

// required uint32 ts = 4;
inline bool CurrTorchStatus::has_ts() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void CurrTorchStatus::set_has_ts() {
  _has_bits_[0] |= 0x00000008u;
}
inline void CurrTorchStatus::clear_has_ts() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void CurrTorchStatus::clear_ts() {
  ts_ = 0u;
  clear_has_ts();
}
inline ::google::protobuf::uint32 CurrTorchStatus::ts() const {
  // @@protoc_insertion_point(field_get:AllianceTorch.CurrTorchStatus.ts)
  return ts_;
}
inline void CurrTorchStatus::set_ts(::google::protobuf::uint32 value) {
  set_has_ts();
  ts_ = value;
  // @@protoc_insertion_point(field_set:AllianceTorch.CurrTorchStatus.ts)
}

// -------------------------------------------------------------------

// LogBuyRecord

// required uint32 time = 1;
inline bool LogBuyRecord::has_time() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void LogBuyRecord::set_has_time() {
  _has_bits_[0] |= 0x00000001u;
}
inline void LogBuyRecord::clear_has_time() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void LogBuyRecord::clear_time() {
  time_ = 0u;
  clear_has_time();
}
inline ::google::protobuf::uint32 LogBuyRecord::time() const {
  // @@protoc_insertion_point(field_get:AllianceTorch.LogBuyRecord.time)
  return time_;
}
inline void LogBuyRecord::set_time(::google::protobuf::uint32 value) {
  set_has_time();
  time_ = value;
  // @@protoc_insertion_point(field_set:AllianceTorch.LogBuyRecord.time)
}

// required uint32 uid = 2;
inline bool LogBuyRecord::has_uid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void LogBuyRecord::set_has_uid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void LogBuyRecord::clear_has_uid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void LogBuyRecord::clear_uid() {
  uid_ = 0u;
  clear_has_uid();
}
inline ::google::protobuf::uint32 LogBuyRecord::uid() const {
  // @@protoc_insertion_point(field_get:AllianceTorch.LogBuyRecord.uid)
  return uid_;
}
inline void LogBuyRecord::set_uid(::google::protobuf::uint32 value) {
  set_has_uid();
  uid_ = value;
  // @@protoc_insertion_point(field_set:AllianceTorch.LogBuyRecord.uid)
}

// required uint32 tid = 3;
inline bool LogBuyRecord::has_tid() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void LogBuyRecord::set_has_tid() {
  _has_bits_[0] |= 0x00000004u;
}
inline void LogBuyRecord::clear_has_tid() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void LogBuyRecord::clear_tid() {
  tid_ = 0u;
  clear_has_tid();
}
inline ::google::protobuf::uint32 LogBuyRecord::tid() const {
  // @@protoc_insertion_point(field_get:AllianceTorch.LogBuyRecord.tid)
  return tid_;
}
inline void LogBuyRecord::set_tid(::google::protobuf::uint32 value) {
  set_has_tid();
  tid_ = value;
  // @@protoc_insertion_point(field_set:AllianceTorch.LogBuyRecord.tid)
}

// -------------------------------------------------------------------

// SingleAllianceTorch

// required uint32 aid = 1;
inline bool SingleAllianceTorch::has_aid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SingleAllianceTorch::set_has_aid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SingleAllianceTorch::clear_has_aid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SingleAllianceTorch::clear_aid() {
  aid_ = 0u;
  clear_has_aid();
}
inline ::google::protobuf::uint32 SingleAllianceTorch::aid() const {
  // @@protoc_insertion_point(field_get:AllianceTorch.SingleAllianceTorch.aid)
  return aid_;
}
inline void SingleAllianceTorch::set_aid(::google::protobuf::uint32 value) {
  set_has_aid();
  aid_ = value;
  // @@protoc_insertion_point(field_set:AllianceTorch.SingleAllianceTorch.aid)
}

// repeated .AllianceTorch.CurrTorchStatus curr = 2;
inline int SingleAllianceTorch::curr_size() const {
  return curr_.size();
}
inline void SingleAllianceTorch::clear_curr() {
  curr_.Clear();
}
inline const ::AllianceTorch::CurrTorchStatus& SingleAllianceTorch::curr(int index) const {
  // @@protoc_insertion_point(field_get:AllianceTorch.SingleAllianceTorch.curr)
  return curr_.Get(index);
}
inline ::AllianceTorch::CurrTorchStatus* SingleAllianceTorch::mutable_curr(int index) {
  // @@protoc_insertion_point(field_mutable:AllianceTorch.SingleAllianceTorch.curr)
  return curr_.Mutable(index);
}
inline ::AllianceTorch::CurrTorchStatus* SingleAllianceTorch::add_curr() {
  // @@protoc_insertion_point(field_add:AllianceTorch.SingleAllianceTorch.curr)
  return curr_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::AllianceTorch::CurrTorchStatus >&
SingleAllianceTorch::curr() const {
  // @@protoc_insertion_point(field_list:AllianceTorch.SingleAllianceTorch.curr)
  return curr_;
}
inline ::google::protobuf::RepeatedPtrField< ::AllianceTorch::CurrTorchStatus >*
SingleAllianceTorch::mutable_curr() {
  // @@protoc_insertion_point(field_mutable_list:AllianceTorch.SingleAllianceTorch.curr)
  return &curr_;
}

// repeated .AllianceTorch.LogBuyRecord log = 3;
inline int SingleAllianceTorch::log_size() const {
  return log_.size();
}
inline void SingleAllianceTorch::clear_log() {
  log_.Clear();
}
inline const ::AllianceTorch::LogBuyRecord& SingleAllianceTorch::log(int index) const {
  // @@protoc_insertion_point(field_get:AllianceTorch.SingleAllianceTorch.log)
  return log_.Get(index);
}
inline ::AllianceTorch::LogBuyRecord* SingleAllianceTorch::mutable_log(int index) {
  // @@protoc_insertion_point(field_mutable:AllianceTorch.SingleAllianceTorch.log)
  return log_.Mutable(index);
}
inline ::AllianceTorch::LogBuyRecord* SingleAllianceTorch::add_log() {
  // @@protoc_insertion_point(field_add:AllianceTorch.SingleAllianceTorch.log)
  return log_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::AllianceTorch::LogBuyRecord >&
SingleAllianceTorch::log() const {
  // @@protoc_insertion_point(field_list:AllianceTorch.SingleAllianceTorch.log)
  return log_;
}
inline ::google::protobuf::RepeatedPtrField< ::AllianceTorch::LogBuyRecord >*
SingleAllianceTorch::mutable_log() {
  // @@protoc_insertion_point(field_mutable_list:AllianceTorch.SingleAllianceTorch.log)
  return &log_;
}

// -------------------------------------------------------------------

// AllianceTorch

// repeated .AllianceTorch.SingleAllianceTorch alliance = 1;
inline int AllianceTorch::alliance_size() const {
  return alliance_.size();
}
inline void AllianceTorch::clear_alliance() {
  alliance_.Clear();
}
inline const ::AllianceTorch::SingleAllianceTorch& AllianceTorch::alliance(int index) const {
  // @@protoc_insertion_point(field_get:AllianceTorch.AllianceTorch.alliance)
  return alliance_.Get(index);
}
inline ::AllianceTorch::SingleAllianceTorch* AllianceTorch::mutable_alliance(int index) {
  // @@protoc_insertion_point(field_mutable:AllianceTorch.AllianceTorch.alliance)
  return alliance_.Mutable(index);
}
inline ::AllianceTorch::SingleAllianceTorch* AllianceTorch::add_alliance() {
  // @@protoc_insertion_point(field_add:AllianceTorch.AllianceTorch.alliance)
  return alliance_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::AllianceTorch::SingleAllianceTorch >&
AllianceTorch::alliance() const {
  // @@protoc_insertion_point(field_list:AllianceTorch.AllianceTorch.alliance)
  return alliance_;
}
inline ::google::protobuf::RepeatedPtrField< ::AllianceTorch::SingleAllianceTorch >*
AllianceTorch::mutable_alliance() {
  // @@protoc_insertion_point(field_mutable_list:AllianceTorch.AllianceTorch.alliance)
  return &alliance_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace AllianceTorch

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_AllianceTorch_2eproto__INCLUDED