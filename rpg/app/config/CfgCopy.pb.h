// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CfgCopy.proto

#ifndef PROTOBUF_CfgCopy_2eproto__INCLUDED
#define PROTOBUF_CfgCopy_2eproto__INCLUDED

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
#include "CfgCommon.pb.h"
// @@protoc_insertion_point(includes)

namespace CfgCopy {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_CfgCopy_2eproto();
void protobuf_AssignDesc_CfgCopy_2eproto();
void protobuf_ShutdownFile_CfgCopy_2eproto();

class Copy;
class Copys;

// ===================================================================

class Copy : public ::google::protobuf::Message {
 public:
  Copy();
  virtual ~Copy();

  Copy(const Copy& from);

  inline Copy& operator=(const Copy& from) {
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
  static const Copy& default_instance();

  void Swap(Copy* other);

  // implements Message ----------------------------------------------

  Copy* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Copy& from);
  void MergeFrom(const Copy& from);
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

  // required uint32 quickDay = 1;
  inline bool has_quickday() const;
  inline void clear_quickday();
  static const int kQuickDayFieldNumber = 1;
  inline ::google::protobuf::uint32 quickday() const;
  inline void set_quickday(::google::protobuf::uint32 value);

  // required uint32 costId = 2;
  inline bool has_costid() const;
  inline void clear_costid();
  static const int kCostIdFieldNumber = 2;
  inline ::google::protobuf::uint32 costid() const;
  inline void set_costid(::google::protobuf::uint32 value);

  // required uint32 needLevel = 3;
  inline bool has_needlevel() const;
  inline void clear_needlevel();
  static const int kNeedLevelFieldNumber = 3;
  inline ::google::protobuf::uint32 needlevel() const;
  inline void set_needlevel(::google::protobuf::uint32 value);

  // required uint32 daily = 4;
  inline bool has_daily() const;
  inline void clear_daily();
  static const int kDailyFieldNumber = 4;
  inline ::google::protobuf::uint32 daily() const;
  inline void set_daily(::google::protobuf::uint32 value);

  // repeated .CfgCommon.Reward firstReward = 5;
  inline int firstreward_size() const;
  inline void clear_firstreward();
  static const int kFirstRewardFieldNumber = 5;
  inline const ::CfgCommon::Reward& firstreward(int index) const;
  inline ::CfgCommon::Reward* mutable_firstreward(int index);
  inline ::CfgCommon::Reward* add_firstreward();
  inline const ::google::protobuf::RepeatedPtrField< ::CfgCommon::Reward >&
      firstreward() const;
  inline ::google::protobuf::RepeatedPtrField< ::CfgCommon::Reward >*
      mutable_firstreward();

  // required uint32 num = 6;
  inline bool has_num() const;
  inline void clear_num();
  static const int kNumFieldNumber = 6;
  inline ::google::protobuf::uint32 num() const;
  inline void set_num(::google::protobuf::uint32 value);

  // required uint32 costNum = 7;
  inline bool has_costnum() const;
  inline void clear_costnum();
  static const int kCostNumFieldNumber = 7;
  inline ::google::protobuf::uint32 costnum() const;
  inline void set_costnum(::google::protobuf::uint32 value);

  // required uint32 time = 8;
  inline bool has_time() const;
  inline void clear_time();
  static const int kTimeFieldNumber = 8;
  inline ::google::protobuf::uint32 time() const;
  inline void set_time(::google::protobuf::uint32 value);

  // required uint32 reincarnLevel = 9;
  inline bool has_reincarnlevel() const;
  inline void clear_reincarnlevel();
  static const int kReincarnLevelFieldNumber = 9;
  inline ::google::protobuf::uint32 reincarnlevel() const;
  inline void set_reincarnlevel(::google::protobuf::uint32 value);

  // repeated .CfgCommon.Reward reward = 10;
  inline int reward_size() const;
  inline void clear_reward();
  static const int kRewardFieldNumber = 10;
  inline const ::CfgCommon::Reward& reward(int index) const;
  inline ::CfgCommon::Reward* mutable_reward(int index);
  inline ::CfgCommon::Reward* add_reward();
  inline const ::google::protobuf::RepeatedPtrField< ::CfgCommon::Reward >&
      reward() const;
  inline ::google::protobuf::RepeatedPtrField< ::CfgCommon::Reward >*
      mutable_reward();

  // required uint32 type = 11;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 11;
  inline ::google::protobuf::uint32 type() const;
  inline void set_type(::google::protobuf::uint32 value);

  // required uint32 copyId = 12;
  inline bool has_copyid() const;
  inline void clear_copyid();
  static const int kCopyIdFieldNumber = 12;
  inline ::google::protobuf::uint32 copyid() const;
  inline void set_copyid(::google::protobuf::uint32 value);

  // required uint32 mapId = 13;
  inline bool has_mapid() const;
  inline void clear_mapid();
  static const int kMapIdFieldNumber = 13;
  inline ::google::protobuf::uint32 mapid() const;
  inline void set_mapid(::google::protobuf::uint32 value);

  // optional uint32 duringTime = 14;
  inline bool has_duringtime() const;
  inline void clear_duringtime();
  static const int kDuringTimeFieldNumber = 14;
  inline ::google::protobuf::uint32 duringtime() const;
  inline void set_duringtime(::google::protobuf::uint32 value);

  // optional uint32 preapareTime = 15;
  inline bool has_preaparetime() const;
  inline void clear_preaparetime();
  static const int kPreapareTimeFieldNumber = 15;
  inline ::google::protobuf::uint32 preaparetime() const;
  inline void set_preaparetime(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:CfgCopy.Copy)
 private:
  inline void set_has_quickday();
  inline void clear_has_quickday();
  inline void set_has_costid();
  inline void clear_has_costid();
  inline void set_has_needlevel();
  inline void clear_has_needlevel();
  inline void set_has_daily();
  inline void clear_has_daily();
  inline void set_has_num();
  inline void clear_has_num();
  inline void set_has_costnum();
  inline void clear_has_costnum();
  inline void set_has_time();
  inline void clear_has_time();
  inline void set_has_reincarnlevel();
  inline void clear_has_reincarnlevel();
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_copyid();
  inline void clear_has_copyid();
  inline void set_has_mapid();
  inline void clear_has_mapid();
  inline void set_has_duringtime();
  inline void clear_has_duringtime();
  inline void set_has_preaparetime();
  inline void clear_has_preaparetime();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 quickday_;
  ::google::protobuf::uint32 costid_;
  ::google::protobuf::uint32 needlevel_;
  ::google::protobuf::uint32 daily_;
  ::google::protobuf::RepeatedPtrField< ::CfgCommon::Reward > firstreward_;
  ::google::protobuf::uint32 num_;
  ::google::protobuf::uint32 costnum_;
  ::google::protobuf::uint32 time_;
  ::google::protobuf::uint32 reincarnlevel_;
  ::google::protobuf::RepeatedPtrField< ::CfgCommon::Reward > reward_;
  ::google::protobuf::uint32 type_;
  ::google::protobuf::uint32 copyid_;
  ::google::protobuf::uint32 mapid_;
  ::google::protobuf::uint32 duringtime_;
  ::google::protobuf::uint32 preaparetime_;
  friend void  protobuf_AddDesc_CfgCopy_2eproto();
  friend void protobuf_AssignDesc_CfgCopy_2eproto();
  friend void protobuf_ShutdownFile_CfgCopy_2eproto();

  void InitAsDefaultInstance();
  static Copy* default_instance_;
};
// -------------------------------------------------------------------

class Copys : public ::google::protobuf::Message {
 public:
  Copys();
  virtual ~Copys();

  Copys(const Copys& from);

  inline Copys& operator=(const Copys& from) {
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
  static const Copys& default_instance();

  void Swap(Copys* other);

  // implements Message ----------------------------------------------

  Copys* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Copys& from);
  void MergeFrom(const Copys& from);
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

  // repeated .CfgCopy.Copy copys = 1;
  inline int copys_size() const;
  inline void clear_copys();
  static const int kCopysFieldNumber = 1;
  inline const ::CfgCopy::Copy& copys(int index) const;
  inline ::CfgCopy::Copy* mutable_copys(int index);
  inline ::CfgCopy::Copy* add_copys();
  inline const ::google::protobuf::RepeatedPtrField< ::CfgCopy::Copy >&
      copys() const;
  inline ::google::protobuf::RepeatedPtrField< ::CfgCopy::Copy >*
      mutable_copys();

  // @@protoc_insertion_point(class_scope:CfgCopy.Copys)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::CfgCopy::Copy > copys_;
  friend void  protobuf_AddDesc_CfgCopy_2eproto();
  friend void protobuf_AssignDesc_CfgCopy_2eproto();
  friend void protobuf_ShutdownFile_CfgCopy_2eproto();

  void InitAsDefaultInstance();
  static Copys* default_instance_;
};
// ===================================================================


// ===================================================================

// Copy

// required uint32 quickDay = 1;
inline bool Copy::has_quickday() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Copy::set_has_quickday() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Copy::clear_has_quickday() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Copy::clear_quickday() {
  quickday_ = 0u;
  clear_has_quickday();
}
inline ::google::protobuf::uint32 Copy::quickday() const {
  // @@protoc_insertion_point(field_get:CfgCopy.Copy.quickDay)
  return quickday_;
}
inline void Copy::set_quickday(::google::protobuf::uint32 value) {
  set_has_quickday();
  quickday_ = value;
  // @@protoc_insertion_point(field_set:CfgCopy.Copy.quickDay)
}

// required uint32 costId = 2;
inline bool Copy::has_costid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Copy::set_has_costid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Copy::clear_has_costid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Copy::clear_costid() {
  costid_ = 0u;
  clear_has_costid();
}
inline ::google::protobuf::uint32 Copy::costid() const {
  // @@protoc_insertion_point(field_get:CfgCopy.Copy.costId)
  return costid_;
}
inline void Copy::set_costid(::google::protobuf::uint32 value) {
  set_has_costid();
  costid_ = value;
  // @@protoc_insertion_point(field_set:CfgCopy.Copy.costId)
}

// required uint32 needLevel = 3;
inline bool Copy::has_needlevel() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Copy::set_has_needlevel() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Copy::clear_has_needlevel() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Copy::clear_needlevel() {
  needlevel_ = 0u;
  clear_has_needlevel();
}
inline ::google::protobuf::uint32 Copy::needlevel() const {
  // @@protoc_insertion_point(field_get:CfgCopy.Copy.needLevel)
  return needlevel_;
}
inline void Copy::set_needlevel(::google::protobuf::uint32 value) {
  set_has_needlevel();
  needlevel_ = value;
  // @@protoc_insertion_point(field_set:CfgCopy.Copy.needLevel)
}

// required uint32 daily = 4;
inline bool Copy::has_daily() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Copy::set_has_daily() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Copy::clear_has_daily() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Copy::clear_daily() {
  daily_ = 0u;
  clear_has_daily();
}
inline ::google::protobuf::uint32 Copy::daily() const {
  // @@protoc_insertion_point(field_get:CfgCopy.Copy.daily)
  return daily_;
}
inline void Copy::set_daily(::google::protobuf::uint32 value) {
  set_has_daily();
  daily_ = value;
  // @@protoc_insertion_point(field_set:CfgCopy.Copy.daily)
}

// repeated .CfgCommon.Reward firstReward = 5;
inline int Copy::firstreward_size() const {
  return firstreward_.size();
}
inline void Copy::clear_firstreward() {
  firstreward_.Clear();
}
inline const ::CfgCommon::Reward& Copy::firstreward(int index) const {
  // @@protoc_insertion_point(field_get:CfgCopy.Copy.firstReward)
  return firstreward_.Get(index);
}
inline ::CfgCommon::Reward* Copy::mutable_firstreward(int index) {
  // @@protoc_insertion_point(field_mutable:CfgCopy.Copy.firstReward)
  return firstreward_.Mutable(index);
}
inline ::CfgCommon::Reward* Copy::add_firstreward() {
  // @@protoc_insertion_point(field_add:CfgCopy.Copy.firstReward)
  return firstreward_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::CfgCommon::Reward >&
Copy::firstreward() const {
  // @@protoc_insertion_point(field_list:CfgCopy.Copy.firstReward)
  return firstreward_;
}
inline ::google::protobuf::RepeatedPtrField< ::CfgCommon::Reward >*
Copy::mutable_firstreward() {
  // @@protoc_insertion_point(field_mutable_list:CfgCopy.Copy.firstReward)
  return &firstreward_;
}

// required uint32 num = 6;
inline bool Copy::has_num() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Copy::set_has_num() {
  _has_bits_[0] |= 0x00000020u;
}
inline void Copy::clear_has_num() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void Copy::clear_num() {
  num_ = 0u;
  clear_has_num();
}
inline ::google::protobuf::uint32 Copy::num() const {
  // @@protoc_insertion_point(field_get:CfgCopy.Copy.num)
  return num_;
}
inline void Copy::set_num(::google::protobuf::uint32 value) {
  set_has_num();
  num_ = value;
  // @@protoc_insertion_point(field_set:CfgCopy.Copy.num)
}

// required uint32 costNum = 7;
inline bool Copy::has_costnum() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void Copy::set_has_costnum() {
  _has_bits_[0] |= 0x00000040u;
}
inline void Copy::clear_has_costnum() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void Copy::clear_costnum() {
  costnum_ = 0u;
  clear_has_costnum();
}
inline ::google::protobuf::uint32 Copy::costnum() const {
  // @@protoc_insertion_point(field_get:CfgCopy.Copy.costNum)
  return costnum_;
}
inline void Copy::set_costnum(::google::protobuf::uint32 value) {
  set_has_costnum();
  costnum_ = value;
  // @@protoc_insertion_point(field_set:CfgCopy.Copy.costNum)
}

// required uint32 time = 8;
inline bool Copy::has_time() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void Copy::set_has_time() {
  _has_bits_[0] |= 0x00000080u;
}
inline void Copy::clear_has_time() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void Copy::clear_time() {
  time_ = 0u;
  clear_has_time();
}
inline ::google::protobuf::uint32 Copy::time() const {
  // @@protoc_insertion_point(field_get:CfgCopy.Copy.time)
  return time_;
}
inline void Copy::set_time(::google::protobuf::uint32 value) {
  set_has_time();
  time_ = value;
  // @@protoc_insertion_point(field_set:CfgCopy.Copy.time)
}

// required uint32 reincarnLevel = 9;
inline bool Copy::has_reincarnlevel() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void Copy::set_has_reincarnlevel() {
  _has_bits_[0] |= 0x00000100u;
}
inline void Copy::clear_has_reincarnlevel() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void Copy::clear_reincarnlevel() {
  reincarnlevel_ = 0u;
  clear_has_reincarnlevel();
}
inline ::google::protobuf::uint32 Copy::reincarnlevel() const {
  // @@protoc_insertion_point(field_get:CfgCopy.Copy.reincarnLevel)
  return reincarnlevel_;
}
inline void Copy::set_reincarnlevel(::google::protobuf::uint32 value) {
  set_has_reincarnlevel();
  reincarnlevel_ = value;
  // @@protoc_insertion_point(field_set:CfgCopy.Copy.reincarnLevel)
}

// repeated .CfgCommon.Reward reward = 10;
inline int Copy::reward_size() const {
  return reward_.size();
}
inline void Copy::clear_reward() {
  reward_.Clear();
}
inline const ::CfgCommon::Reward& Copy::reward(int index) const {
  // @@protoc_insertion_point(field_get:CfgCopy.Copy.reward)
  return reward_.Get(index);
}
inline ::CfgCommon::Reward* Copy::mutable_reward(int index) {
  // @@protoc_insertion_point(field_mutable:CfgCopy.Copy.reward)
  return reward_.Mutable(index);
}
inline ::CfgCommon::Reward* Copy::add_reward() {
  // @@protoc_insertion_point(field_add:CfgCopy.Copy.reward)
  return reward_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::CfgCommon::Reward >&
Copy::reward() const {
  // @@protoc_insertion_point(field_list:CfgCopy.Copy.reward)
  return reward_;
}
inline ::google::protobuf::RepeatedPtrField< ::CfgCommon::Reward >*
Copy::mutable_reward() {
  // @@protoc_insertion_point(field_mutable_list:CfgCopy.Copy.reward)
  return &reward_;
}

// required uint32 type = 11;
inline bool Copy::has_type() const {
  return (_has_bits_[0] & 0x00000400u) != 0;
}
inline void Copy::set_has_type() {
  _has_bits_[0] |= 0x00000400u;
}
inline void Copy::clear_has_type() {
  _has_bits_[0] &= ~0x00000400u;
}
inline void Copy::clear_type() {
  type_ = 0u;
  clear_has_type();
}
inline ::google::protobuf::uint32 Copy::type() const {
  // @@protoc_insertion_point(field_get:CfgCopy.Copy.type)
  return type_;
}
inline void Copy::set_type(::google::protobuf::uint32 value) {
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:CfgCopy.Copy.type)
}

// required uint32 copyId = 12;
inline bool Copy::has_copyid() const {
  return (_has_bits_[0] & 0x00000800u) != 0;
}
inline void Copy::set_has_copyid() {
  _has_bits_[0] |= 0x00000800u;
}
inline void Copy::clear_has_copyid() {
  _has_bits_[0] &= ~0x00000800u;
}
inline void Copy::clear_copyid() {
  copyid_ = 0u;
  clear_has_copyid();
}
inline ::google::protobuf::uint32 Copy::copyid() const {
  // @@protoc_insertion_point(field_get:CfgCopy.Copy.copyId)
  return copyid_;
}
inline void Copy::set_copyid(::google::protobuf::uint32 value) {
  set_has_copyid();
  copyid_ = value;
  // @@protoc_insertion_point(field_set:CfgCopy.Copy.copyId)
}

// required uint32 mapId = 13;
inline bool Copy::has_mapid() const {
  return (_has_bits_[0] & 0x00001000u) != 0;
}
inline void Copy::set_has_mapid() {
  _has_bits_[0] |= 0x00001000u;
}
inline void Copy::clear_has_mapid() {
  _has_bits_[0] &= ~0x00001000u;
}
inline void Copy::clear_mapid() {
  mapid_ = 0u;
  clear_has_mapid();
}
inline ::google::protobuf::uint32 Copy::mapid() const {
  // @@protoc_insertion_point(field_get:CfgCopy.Copy.mapId)
  return mapid_;
}
inline void Copy::set_mapid(::google::protobuf::uint32 value) {
  set_has_mapid();
  mapid_ = value;
  // @@protoc_insertion_point(field_set:CfgCopy.Copy.mapId)
}

// optional uint32 duringTime = 14;
inline bool Copy::has_duringtime() const {
  return (_has_bits_[0] & 0x00002000u) != 0;
}
inline void Copy::set_has_duringtime() {
  _has_bits_[0] |= 0x00002000u;
}
inline void Copy::clear_has_duringtime() {
  _has_bits_[0] &= ~0x00002000u;
}
inline void Copy::clear_duringtime() {
  duringtime_ = 0u;
  clear_has_duringtime();
}
inline ::google::protobuf::uint32 Copy::duringtime() const {
  // @@protoc_insertion_point(field_get:CfgCopy.Copy.duringTime)
  return duringtime_;
}
inline void Copy::set_duringtime(::google::protobuf::uint32 value) {
  set_has_duringtime();
  duringtime_ = value;
  // @@protoc_insertion_point(field_set:CfgCopy.Copy.duringTime)
}

// optional uint32 preapareTime = 15;
inline bool Copy::has_preaparetime() const {
  return (_has_bits_[0] & 0x00004000u) != 0;
}
inline void Copy::set_has_preaparetime() {
  _has_bits_[0] |= 0x00004000u;
}
inline void Copy::clear_has_preaparetime() {
  _has_bits_[0] &= ~0x00004000u;
}
inline void Copy::clear_preaparetime() {
  preaparetime_ = 0u;
  clear_has_preaparetime();
}
inline ::google::protobuf::uint32 Copy::preaparetime() const {
  // @@protoc_insertion_point(field_get:CfgCopy.Copy.preapareTime)
  return preaparetime_;
}
inline void Copy::set_preaparetime(::google::protobuf::uint32 value) {
  set_has_preaparetime();
  preaparetime_ = value;
  // @@protoc_insertion_point(field_set:CfgCopy.Copy.preapareTime)
}

// -------------------------------------------------------------------

// Copys

// repeated .CfgCopy.Copy copys = 1;
inline int Copys::copys_size() const {
  return copys_.size();
}
inline void Copys::clear_copys() {
  copys_.Clear();
}
inline const ::CfgCopy::Copy& Copys::copys(int index) const {
  // @@protoc_insertion_point(field_get:CfgCopy.Copys.copys)
  return copys_.Get(index);
}
inline ::CfgCopy::Copy* Copys::mutable_copys(int index) {
  // @@protoc_insertion_point(field_mutable:CfgCopy.Copys.copys)
  return copys_.Mutable(index);
}
inline ::CfgCopy::Copy* Copys::add_copys() {
  // @@protoc_insertion_point(field_add:CfgCopy.Copys.copys)
  return copys_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::CfgCopy::Copy >&
Copys::copys() const {
  // @@protoc_insertion_point(field_list:CfgCopy.Copys.copys)
  return copys_;
}
inline ::google::protobuf::RepeatedPtrField< ::CfgCopy::Copy >*
Copys::mutable_copys() {
  // @@protoc_insertion_point(field_mutable_list:CfgCopy.Copys.copys)
  return &copys_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace CfgCopy

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_CfgCopy_2eproto__INCLUDED