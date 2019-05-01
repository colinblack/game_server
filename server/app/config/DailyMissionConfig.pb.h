// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: DailyMissionConfig.proto

#ifndef PROTOBUF_DailyMissionConfig_2eproto__INCLUDED
#define PROTOBUF_DailyMissionConfig_2eproto__INCLUDED

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

namespace DailyMissionConfig {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_DailyMissionConfig_2eproto();
void protobuf_AssignDesc_DailyMissionConfig_2eproto();
void protobuf_ShutdownFile_DailyMissionConfig_2eproto();

class DailyMission;
class DailyMissionsItem;
class DailyMissonItemList;

// ===================================================================

class DailyMission : public ::google::protobuf::Message {
 public:
  DailyMission();
  virtual ~DailyMission();

  DailyMission(const DailyMission& from);

  inline DailyMission& operator=(const DailyMission& from) {
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
  static const DailyMission& default_instance();

  void Swap(DailyMission* other);

  // implements Message ----------------------------------------------

  DailyMission* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DailyMission& from);
  void MergeFrom(const DailyMission& from);
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

  // required uint32 rate = 2;
  inline bool has_rate() const;
  inline void clear_rate();
  static const int kRateFieldNumber = 2;
  inline ::google::protobuf::uint32 rate() const;
  inline void set_rate(::google::protobuf::uint32 value);

  // required uint32 type = 3;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 3;
  inline ::google::protobuf::uint32 type() const;
  inline void set_type(::google::protobuf::uint32 value);

  // required uint32 subtype = 4;
  inline bool has_subtype() const;
  inline void clear_subtype();
  static const int kSubtypeFieldNumber = 4;
  inline ::google::protobuf::uint32 subtype() const;
  inline void set_subtype(::google::protobuf::uint32 value);

  // required uint32 count = 5;
  inline bool has_count() const;
  inline void clear_count();
  static const int kCountFieldNumber = 5;
  inline ::google::protobuf::uint32 count() const;
  inline void set_count(::google::protobuf::uint32 value);

  // repeated uint32 starrate = 6;
  inline int starrate_size() const;
  inline void clear_starrate();
  static const int kStarrateFieldNumber = 6;
  inline ::google::protobuf::uint32 starrate(int index) const;
  inline void set_starrate(int index, ::google::protobuf::uint32 value);
  inline void add_starrate(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      starrate() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_starrate();

  // repeated double starcoefficient = 7;
  inline int starcoefficient_size() const;
  inline void clear_starcoefficient();
  static const int kStarcoefficientFieldNumber = 7;
  inline double starcoefficient(int index) const;
  inline void set_starcoefficient(int index, double value);
  inline void add_starcoefficient(double value);
  inline const ::google::protobuf::RepeatedField< double >&
      starcoefficient() const;
  inline ::google::protobuf::RepeatedField< double >*
      mutable_starcoefficient();

  // required uint32 exp = 8;
  inline bool has_exp() const;
  inline void clear_exp();
  static const int kExpFieldNumber = 8;
  inline ::google::protobuf::uint32 exp() const;
  inline void set_exp(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:DailyMissionConfig.DailyMission)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_rate();
  inline void clear_has_rate();
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_subtype();
  inline void clear_has_subtype();
  inline void set_has_count();
  inline void clear_has_count();
  inline void set_has_exp();
  inline void clear_has_exp();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 rate_;
  ::google::protobuf::uint32 type_;
  ::google::protobuf::uint32 subtype_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > starrate_;
  ::google::protobuf::uint32 count_;
  ::google::protobuf::uint32 exp_;
  ::google::protobuf::RepeatedField< double > starcoefficient_;
  friend void  protobuf_AddDesc_DailyMissionConfig_2eproto();
  friend void protobuf_AssignDesc_DailyMissionConfig_2eproto();
  friend void protobuf_ShutdownFile_DailyMissionConfig_2eproto();

  void InitAsDefaultInstance();
  static DailyMission* default_instance_;
};
// -------------------------------------------------------------------

class DailyMissionsItem : public ::google::protobuf::Message {
 public:
  DailyMissionsItem();
  virtual ~DailyMissionsItem();

  DailyMissionsItem(const DailyMissionsItem& from);

  inline DailyMissionsItem& operator=(const DailyMissionsItem& from) {
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
  static const DailyMissionsItem& default_instance();

  void Swap(DailyMissionsItem* other);

  // implements Message ----------------------------------------------

  DailyMissionsItem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DailyMissionsItem& from);
  void MergeFrom(const DailyMissionsItem& from);
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

  // required uint32 tech = 1;
  inline bool has_tech() const;
  inline void clear_tech();
  static const int kTechFieldNumber = 1;
  inline ::google::protobuf::uint32 tech() const;
  inline void set_tech(::google::protobuf::uint32 value);

  // repeated .DailyMissionConfig.DailyMission missions = 2;
  inline int missions_size() const;
  inline void clear_missions();
  static const int kMissionsFieldNumber = 2;
  inline const ::DailyMissionConfig::DailyMission& missions(int index) const;
  inline ::DailyMissionConfig::DailyMission* mutable_missions(int index);
  inline ::DailyMissionConfig::DailyMission* add_missions();
  inline const ::google::protobuf::RepeatedPtrField< ::DailyMissionConfig::DailyMission >&
      missions() const;
  inline ::google::protobuf::RepeatedPtrField< ::DailyMissionConfig::DailyMission >*
      mutable_missions();

  // @@protoc_insertion_point(class_scope:DailyMissionConfig.DailyMissionsItem)
 private:
  inline void set_has_tech();
  inline void clear_has_tech();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::DailyMissionConfig::DailyMission > missions_;
  ::google::protobuf::uint32 tech_;
  friend void  protobuf_AddDesc_DailyMissionConfig_2eproto();
  friend void protobuf_AssignDesc_DailyMissionConfig_2eproto();
  friend void protobuf_ShutdownFile_DailyMissionConfig_2eproto();

  void InitAsDefaultInstance();
  static DailyMissionsItem* default_instance_;
};
// -------------------------------------------------------------------

class DailyMissonItemList : public ::google::protobuf::Message {
 public:
  DailyMissonItemList();
  virtual ~DailyMissonItemList();

  DailyMissonItemList(const DailyMissonItemList& from);

  inline DailyMissonItemList& operator=(const DailyMissonItemList& from) {
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
  static const DailyMissonItemList& default_instance();

  void Swap(DailyMissonItemList* other);

  // implements Message ----------------------------------------------

  DailyMissonItemList* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DailyMissonItemList& from);
  void MergeFrom(const DailyMissonItemList& from);
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

  // repeated .DailyMissionConfig.DailyMissionsItem daily_missions = 1;
  inline int daily_missions_size() const;
  inline void clear_daily_missions();
  static const int kDailyMissionsFieldNumber = 1;
  inline const ::DailyMissionConfig::DailyMissionsItem& daily_missions(int index) const;
  inline ::DailyMissionConfig::DailyMissionsItem* mutable_daily_missions(int index);
  inline ::DailyMissionConfig::DailyMissionsItem* add_daily_missions();
  inline const ::google::protobuf::RepeatedPtrField< ::DailyMissionConfig::DailyMissionsItem >&
      daily_missions() const;
  inline ::google::protobuf::RepeatedPtrField< ::DailyMissionConfig::DailyMissionsItem >*
      mutable_daily_missions();

  // @@protoc_insertion_point(class_scope:DailyMissionConfig.DailyMissonItemList)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::DailyMissionConfig::DailyMissionsItem > daily_missions_;
  friend void  protobuf_AddDesc_DailyMissionConfig_2eproto();
  friend void protobuf_AssignDesc_DailyMissionConfig_2eproto();
  friend void protobuf_ShutdownFile_DailyMissionConfig_2eproto();

  void InitAsDefaultInstance();
  static DailyMissonItemList* default_instance_;
};
// ===================================================================


// ===================================================================

// DailyMission

// required uint32 id = 1;
inline bool DailyMission::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void DailyMission::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void DailyMission::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void DailyMission::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 DailyMission::id() const {
  // @@protoc_insertion_point(field_get:DailyMissionConfig.DailyMission.id)
  return id_;
}
inline void DailyMission::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:DailyMissionConfig.DailyMission.id)
}

// required uint32 rate = 2;
inline bool DailyMission::has_rate() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void DailyMission::set_has_rate() {
  _has_bits_[0] |= 0x00000002u;
}
inline void DailyMission::clear_has_rate() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void DailyMission::clear_rate() {
  rate_ = 0u;
  clear_has_rate();
}
inline ::google::protobuf::uint32 DailyMission::rate() const {
  // @@protoc_insertion_point(field_get:DailyMissionConfig.DailyMission.rate)
  return rate_;
}
inline void DailyMission::set_rate(::google::protobuf::uint32 value) {
  set_has_rate();
  rate_ = value;
  // @@protoc_insertion_point(field_set:DailyMissionConfig.DailyMission.rate)
}

// required uint32 type = 3;
inline bool DailyMission::has_type() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void DailyMission::set_has_type() {
  _has_bits_[0] |= 0x00000004u;
}
inline void DailyMission::clear_has_type() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void DailyMission::clear_type() {
  type_ = 0u;
  clear_has_type();
}
inline ::google::protobuf::uint32 DailyMission::type() const {
  // @@protoc_insertion_point(field_get:DailyMissionConfig.DailyMission.type)
  return type_;
}
inline void DailyMission::set_type(::google::protobuf::uint32 value) {
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:DailyMissionConfig.DailyMission.type)
}

// required uint32 subtype = 4;
inline bool DailyMission::has_subtype() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void DailyMission::set_has_subtype() {
  _has_bits_[0] |= 0x00000008u;
}
inline void DailyMission::clear_has_subtype() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void DailyMission::clear_subtype() {
  subtype_ = 0u;
  clear_has_subtype();
}
inline ::google::protobuf::uint32 DailyMission::subtype() const {
  // @@protoc_insertion_point(field_get:DailyMissionConfig.DailyMission.subtype)
  return subtype_;
}
inline void DailyMission::set_subtype(::google::protobuf::uint32 value) {
  set_has_subtype();
  subtype_ = value;
  // @@protoc_insertion_point(field_set:DailyMissionConfig.DailyMission.subtype)
}

// required uint32 count = 5;
inline bool DailyMission::has_count() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void DailyMission::set_has_count() {
  _has_bits_[0] |= 0x00000010u;
}
inline void DailyMission::clear_has_count() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void DailyMission::clear_count() {
  count_ = 0u;
  clear_has_count();
}
inline ::google::protobuf::uint32 DailyMission::count() const {
  // @@protoc_insertion_point(field_get:DailyMissionConfig.DailyMission.count)
  return count_;
}
inline void DailyMission::set_count(::google::protobuf::uint32 value) {
  set_has_count();
  count_ = value;
  // @@protoc_insertion_point(field_set:DailyMissionConfig.DailyMission.count)
}

// repeated uint32 starrate = 6;
inline int DailyMission::starrate_size() const {
  return starrate_.size();
}
inline void DailyMission::clear_starrate() {
  starrate_.Clear();
}
inline ::google::protobuf::uint32 DailyMission::starrate(int index) const {
  // @@protoc_insertion_point(field_get:DailyMissionConfig.DailyMission.starrate)
  return starrate_.Get(index);
}
inline void DailyMission::set_starrate(int index, ::google::protobuf::uint32 value) {
  starrate_.Set(index, value);
  // @@protoc_insertion_point(field_set:DailyMissionConfig.DailyMission.starrate)
}
inline void DailyMission::add_starrate(::google::protobuf::uint32 value) {
  starrate_.Add(value);
  // @@protoc_insertion_point(field_add:DailyMissionConfig.DailyMission.starrate)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
DailyMission::starrate() const {
  // @@protoc_insertion_point(field_list:DailyMissionConfig.DailyMission.starrate)
  return starrate_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
DailyMission::mutable_starrate() {
  // @@protoc_insertion_point(field_mutable_list:DailyMissionConfig.DailyMission.starrate)
  return &starrate_;
}

// repeated double starcoefficient = 7;
inline int DailyMission::starcoefficient_size() const {
  return starcoefficient_.size();
}
inline void DailyMission::clear_starcoefficient() {
  starcoefficient_.Clear();
}
inline double DailyMission::starcoefficient(int index) const {
  // @@protoc_insertion_point(field_get:DailyMissionConfig.DailyMission.starcoefficient)
  return starcoefficient_.Get(index);
}
inline void DailyMission::set_starcoefficient(int index, double value) {
  starcoefficient_.Set(index, value);
  // @@protoc_insertion_point(field_set:DailyMissionConfig.DailyMission.starcoefficient)
}
inline void DailyMission::add_starcoefficient(double value) {
  starcoefficient_.Add(value);
  // @@protoc_insertion_point(field_add:DailyMissionConfig.DailyMission.starcoefficient)
}
inline const ::google::protobuf::RepeatedField< double >&
DailyMission::starcoefficient() const {
  // @@protoc_insertion_point(field_list:DailyMissionConfig.DailyMission.starcoefficient)
  return starcoefficient_;
}
inline ::google::protobuf::RepeatedField< double >*
DailyMission::mutable_starcoefficient() {
  // @@protoc_insertion_point(field_mutable_list:DailyMissionConfig.DailyMission.starcoefficient)
  return &starcoefficient_;
}

// required uint32 exp = 8;
inline bool DailyMission::has_exp() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void DailyMission::set_has_exp() {
  _has_bits_[0] |= 0x00000080u;
}
inline void DailyMission::clear_has_exp() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void DailyMission::clear_exp() {
  exp_ = 0u;
  clear_has_exp();
}
inline ::google::protobuf::uint32 DailyMission::exp() const {
  // @@protoc_insertion_point(field_get:DailyMissionConfig.DailyMission.exp)
  return exp_;
}
inline void DailyMission::set_exp(::google::protobuf::uint32 value) {
  set_has_exp();
  exp_ = value;
  // @@protoc_insertion_point(field_set:DailyMissionConfig.DailyMission.exp)
}

// -------------------------------------------------------------------

// DailyMissionsItem

// required uint32 tech = 1;
inline bool DailyMissionsItem::has_tech() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void DailyMissionsItem::set_has_tech() {
  _has_bits_[0] |= 0x00000001u;
}
inline void DailyMissionsItem::clear_has_tech() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void DailyMissionsItem::clear_tech() {
  tech_ = 0u;
  clear_has_tech();
}
inline ::google::protobuf::uint32 DailyMissionsItem::tech() const {
  // @@protoc_insertion_point(field_get:DailyMissionConfig.DailyMissionsItem.tech)
  return tech_;
}
inline void DailyMissionsItem::set_tech(::google::protobuf::uint32 value) {
  set_has_tech();
  tech_ = value;
  // @@protoc_insertion_point(field_set:DailyMissionConfig.DailyMissionsItem.tech)
}

// repeated .DailyMissionConfig.DailyMission missions = 2;
inline int DailyMissionsItem::missions_size() const {
  return missions_.size();
}
inline void DailyMissionsItem::clear_missions() {
  missions_.Clear();
}
inline const ::DailyMissionConfig::DailyMission& DailyMissionsItem::missions(int index) const {
  // @@protoc_insertion_point(field_get:DailyMissionConfig.DailyMissionsItem.missions)
  return missions_.Get(index);
}
inline ::DailyMissionConfig::DailyMission* DailyMissionsItem::mutable_missions(int index) {
  // @@protoc_insertion_point(field_mutable:DailyMissionConfig.DailyMissionsItem.missions)
  return missions_.Mutable(index);
}
inline ::DailyMissionConfig::DailyMission* DailyMissionsItem::add_missions() {
  // @@protoc_insertion_point(field_add:DailyMissionConfig.DailyMissionsItem.missions)
  return missions_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::DailyMissionConfig::DailyMission >&
DailyMissionsItem::missions() const {
  // @@protoc_insertion_point(field_list:DailyMissionConfig.DailyMissionsItem.missions)
  return missions_;
}
inline ::google::protobuf::RepeatedPtrField< ::DailyMissionConfig::DailyMission >*
DailyMissionsItem::mutable_missions() {
  // @@protoc_insertion_point(field_mutable_list:DailyMissionConfig.DailyMissionsItem.missions)
  return &missions_;
}

// -------------------------------------------------------------------

// DailyMissonItemList

// repeated .DailyMissionConfig.DailyMissionsItem daily_missions = 1;
inline int DailyMissonItemList::daily_missions_size() const {
  return daily_missions_.size();
}
inline void DailyMissonItemList::clear_daily_missions() {
  daily_missions_.Clear();
}
inline const ::DailyMissionConfig::DailyMissionsItem& DailyMissonItemList::daily_missions(int index) const {
  // @@protoc_insertion_point(field_get:DailyMissionConfig.DailyMissonItemList.daily_missions)
  return daily_missions_.Get(index);
}
inline ::DailyMissionConfig::DailyMissionsItem* DailyMissonItemList::mutable_daily_missions(int index) {
  // @@protoc_insertion_point(field_mutable:DailyMissionConfig.DailyMissonItemList.daily_missions)
  return daily_missions_.Mutable(index);
}
inline ::DailyMissionConfig::DailyMissionsItem* DailyMissonItemList::add_daily_missions() {
  // @@protoc_insertion_point(field_add:DailyMissionConfig.DailyMissonItemList.daily_missions)
  return daily_missions_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::DailyMissionConfig::DailyMissionsItem >&
DailyMissonItemList::daily_missions() const {
  // @@protoc_insertion_point(field_list:DailyMissionConfig.DailyMissonItemList.daily_missions)
  return daily_missions_;
}
inline ::google::protobuf::RepeatedPtrField< ::DailyMissionConfig::DailyMissionsItem >*
DailyMissonItemList::mutable_daily_missions() {
  // @@protoc_insertion_point(field_mutable_list:DailyMissionConfig.DailyMissonItemList.daily_missions)
  return &daily_missions_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace DailyMissionConfig

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_DailyMissionConfig_2eproto__INCLUDED
