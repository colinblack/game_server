// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Stars.proto

#ifndef PROTOBUF_Stars_2eproto__INCLUDED
#define PROTOBUF_Stars_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
#include "CommonGiftConfig.pb.h"
// @@protoc_insertion_point(includes)

namespace Stars {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_Stars_2eproto();
void protobuf_AssignDesc_Stars_2eproto();
void protobuf_ShutdownFile_Stars_2eproto();

class Attributes;
class StarList;
class HeroWithStars;
class StarInfo;

// ===================================================================

class Attributes : public ::google::protobuf::Message {
 public:
  Attributes();
  virtual ~Attributes();
  
  Attributes(const Attributes& from);
  
  inline Attributes& operator=(const Attributes& from) {
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
  static const Attributes& default_instance();
  
  void Swap(Attributes* other);
  
  // implements Message ----------------------------------------------
  
  Attributes* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Attributes& from);
  void MergeFrom(const Attributes& from);
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
  
  // optional uint32 hp = 1;
  inline bool has_hp() const;
  inline void clear_hp();
  static const int kHpFieldNumber = 1;
  inline ::google::protobuf::uint32 hp() const;
  inline void set_hp(::google::protobuf::uint32 value);
  
  // optional uint32 att = 2;
  inline bool has_att() const;
  inline void clear_att();
  static const int kAttFieldNumber = 2;
  inline ::google::protobuf::uint32 att() const;
  inline void set_att(::google::protobuf::uint32 value);
  
  // optional uint32 def = 3;
  inline bool has_def() const;
  inline void clear_def();
  static const int kDefFieldNumber = 3;
  inline ::google::protobuf::uint32 def() const;
  inline void set_def(::google::protobuf::uint32 value);
  
  // optional uint32 first = 4;
  inline bool has_first() const;
  inline void clear_first();
  static const int kFirstFieldNumber = 4;
  inline ::google::protobuf::uint32 first() const;
  inline void set_first(::google::protobuf::uint32 value);
  
  // optional uint32 hit = 5;
  inline bool has_hit() const;
  inline void clear_hit();
  static const int kHitFieldNumber = 5;
  inline ::google::protobuf::uint32 hit() const;
  inline void set_hit(::google::protobuf::uint32 value);
  
  // optional uint32 dodge = 6;
  inline bool has_dodge() const;
  inline void clear_dodge();
  static const int kDodgeFieldNumber = 6;
  inline ::google::protobuf::uint32 dodge() const;
  inline void set_dodge(::google::protobuf::uint32 value);
  
  // optional uint32 critStrike = 7;
  inline bool has_critstrike() const;
  inline void clear_critstrike();
  static const int kCritStrikeFieldNumber = 7;
  inline ::google::protobuf::uint32 critstrike() const;
  inline void set_critstrike(::google::protobuf::uint32 value);
  
  // optional uint32 critRate = 8;
  inline bool has_critrate() const;
  inline void clear_critrate();
  static const int kCritRateFieldNumber = 8;
  inline ::google::protobuf::uint32 critrate() const;
  inline void set_critrate(::google::protobuf::uint32 value);
  
  // optional uint32 critResist = 9;
  inline bool has_critresist() const;
  inline void clear_critresist();
  static const int kCritResistFieldNumber = 9;
  inline ::google::protobuf::uint32 critresist() const;
  inline void set_critresist(::google::protobuf::uint32 value);
  
  // optional double hp_add = 10;
  inline bool has_hp_add() const;
  inline void clear_hp_add();
  static const int kHpAddFieldNumber = 10;
  inline double hp_add() const;
  inline void set_hp_add(double value);
  
  // optional double att_add = 11;
  inline bool has_att_add() const;
  inline void clear_att_add();
  static const int kAttAddFieldNumber = 11;
  inline double att_add() const;
  inline void set_att_add(double value);
  
  // optional double def_add = 12;
  inline bool has_def_add() const;
  inline void clear_def_add();
  static const int kDefAddFieldNumber = 12;
  inline double def_add() const;
  inline void set_def_add(double value);
  
  // @@protoc_insertion_point(class_scope:Stars.Attributes)
 private:
  inline void set_has_hp();
  inline void clear_has_hp();
  inline void set_has_att();
  inline void clear_has_att();
  inline void set_has_def();
  inline void clear_has_def();
  inline void set_has_first();
  inline void clear_has_first();
  inline void set_has_hit();
  inline void clear_has_hit();
  inline void set_has_dodge();
  inline void clear_has_dodge();
  inline void set_has_critstrike();
  inline void clear_has_critstrike();
  inline void set_has_critrate();
  inline void clear_has_critrate();
  inline void set_has_critresist();
  inline void clear_has_critresist();
  inline void set_has_hp_add();
  inline void clear_has_hp_add();
  inline void set_has_att_add();
  inline void clear_has_att_add();
  inline void set_has_def_add();
  inline void clear_has_def_add();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint32 hp_;
  ::google::protobuf::uint32 att_;
  ::google::protobuf::uint32 def_;
  ::google::protobuf::uint32 first_;
  ::google::protobuf::uint32 hit_;
  ::google::protobuf::uint32 dodge_;
  ::google::protobuf::uint32 critstrike_;
  ::google::protobuf::uint32 critrate_;
  double hp_add_;
  double att_add_;
  double def_add_;
  ::google::protobuf::uint32 critresist_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(12 + 31) / 32];
  
  friend void  protobuf_AddDesc_Stars_2eproto();
  friend void protobuf_AssignDesc_Stars_2eproto();
  friend void protobuf_ShutdownFile_Stars_2eproto();
  
  void InitAsDefaultInstance();
  static Attributes* default_instance_;
};
// -------------------------------------------------------------------

class StarList : public ::google::protobuf::Message {
 public:
  StarList();
  virtual ~StarList();
  
  StarList(const StarList& from);
  
  inline StarList& operator=(const StarList& from) {
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
  static const StarList& default_instance();
  
  void Swap(StarList* other);
  
  // implements Message ----------------------------------------------
  
  StarList* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const StarList& from);
  void MergeFrom(const StarList& from);
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
  
  // required .Stars.Attributes attr = 2;
  inline bool has_attr() const;
  inline void clear_attr();
  static const int kAttrFieldNumber = 2;
  inline const ::Stars::Attributes& attr() const;
  inline ::Stars::Attributes* mutable_attr();
  inline ::Stars::Attributes* release_attr();
  
  // required .CommonGiftConfig.CommonModifyItem price = 3;
  inline bool has_price() const;
  inline void clear_price();
  static const int kPriceFieldNumber = 3;
  inline const ::CommonGiftConfig::CommonModifyItem& price() const;
  inline ::CommonGiftConfig::CommonModifyItem* mutable_price();
  inline ::CommonGiftConfig::CommonModifyItem* release_price();
  
  // required uint32 fight_power = 4;
  inline bool has_fight_power() const;
  inline void clear_fight_power();
  static const int kFightPowerFieldNumber = 4;
  inline ::google::protobuf::uint32 fight_power() const;
  inline void set_fight_power(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:Stars.StarList)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_attr();
  inline void clear_has_attr();
  inline void set_has_price();
  inline void clear_has_price();
  inline void set_has_fight_power();
  inline void clear_has_fight_power();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::Stars::Attributes* attr_;
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 fight_power_;
  ::CommonGiftConfig::CommonModifyItem* price_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];
  
  friend void  protobuf_AddDesc_Stars_2eproto();
  friend void protobuf_AssignDesc_Stars_2eproto();
  friend void protobuf_ShutdownFile_Stars_2eproto();
  
  void InitAsDefaultInstance();
  static StarList* default_instance_;
};
// -------------------------------------------------------------------

class HeroWithStars : public ::google::protobuf::Message {
 public:
  HeroWithStars();
  virtual ~HeroWithStars();
  
  HeroWithStars(const HeroWithStars& from);
  
  inline HeroWithStars& operator=(const HeroWithStars& from) {
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
  static const HeroWithStars& default_instance();
  
  void Swap(HeroWithStars* other);
  
  // implements Message ----------------------------------------------
  
  HeroWithStars* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const HeroWithStars& from);
  void MergeFrom(const HeroWithStars& from);
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
  
  // required uint32 heroid = 1;
  inline bool has_heroid() const;
  inline void clear_heroid();
  static const int kHeroidFieldNumber = 1;
  inline ::google::protobuf::uint32 heroid() const;
  inline void set_heroid(::google::protobuf::uint32 value);
  
  // repeated .Stars.StarList list = 2;
  inline int list_size() const;
  inline void clear_list();
  static const int kListFieldNumber = 2;
  inline const ::Stars::StarList& list(int index) const;
  inline ::Stars::StarList* mutable_list(int index);
  inline ::Stars::StarList* add_list();
  inline const ::google::protobuf::RepeatedPtrField< ::Stars::StarList >&
      list() const;
  inline ::google::protobuf::RepeatedPtrField< ::Stars::StarList >*
      mutable_list();
  
  // @@protoc_insertion_point(class_scope:Stars.HeroWithStars)
 private:
  inline void set_has_heroid();
  inline void clear_has_heroid();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::Stars::StarList > list_;
  ::google::protobuf::uint32 heroid_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_Stars_2eproto();
  friend void protobuf_AssignDesc_Stars_2eproto();
  friend void protobuf_ShutdownFile_Stars_2eproto();
  
  void InitAsDefaultInstance();
  static HeroWithStars* default_instance_;
};
// -------------------------------------------------------------------

class StarInfo : public ::google::protobuf::Message {
 public:
  StarInfo();
  virtual ~StarInfo();
  
  StarInfo(const StarInfo& from);
  
  inline StarInfo& operator=(const StarInfo& from) {
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
  static const StarInfo& default_instance();
  
  void Swap(StarInfo* other);
  
  // implements Message ----------------------------------------------
  
  StarInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const StarInfo& from);
  void MergeFrom(const StarInfo& from);
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
  
  // repeated .Stars.HeroWithStars starInfo = 1;
  inline int starinfo_size() const;
  inline void clear_starinfo();
  static const int kStarInfoFieldNumber = 1;
  inline const ::Stars::HeroWithStars& starinfo(int index) const;
  inline ::Stars::HeroWithStars* mutable_starinfo(int index);
  inline ::Stars::HeroWithStars* add_starinfo();
  inline const ::google::protobuf::RepeatedPtrField< ::Stars::HeroWithStars >&
      starinfo() const;
  inline ::google::protobuf::RepeatedPtrField< ::Stars::HeroWithStars >*
      mutable_starinfo();
  
  // @@protoc_insertion_point(class_scope:Stars.StarInfo)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::Stars::HeroWithStars > starinfo_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_Stars_2eproto();
  friend void protobuf_AssignDesc_Stars_2eproto();
  friend void protobuf_ShutdownFile_Stars_2eproto();
  
  void InitAsDefaultInstance();
  static StarInfo* default_instance_;
};
// ===================================================================


// ===================================================================

// Attributes

// optional uint32 hp = 1;
inline bool Attributes::has_hp() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Attributes::set_has_hp() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Attributes::clear_has_hp() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Attributes::clear_hp() {
  hp_ = 0u;
  clear_has_hp();
}
inline ::google::protobuf::uint32 Attributes::hp() const {
  return hp_;
}
inline void Attributes::set_hp(::google::protobuf::uint32 value) {
  set_has_hp();
  hp_ = value;
}

// optional uint32 att = 2;
inline bool Attributes::has_att() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Attributes::set_has_att() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Attributes::clear_has_att() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Attributes::clear_att() {
  att_ = 0u;
  clear_has_att();
}
inline ::google::protobuf::uint32 Attributes::att() const {
  return att_;
}
inline void Attributes::set_att(::google::protobuf::uint32 value) {
  set_has_att();
  att_ = value;
}

// optional uint32 def = 3;
inline bool Attributes::has_def() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Attributes::set_has_def() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Attributes::clear_has_def() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Attributes::clear_def() {
  def_ = 0u;
  clear_has_def();
}
inline ::google::protobuf::uint32 Attributes::def() const {
  return def_;
}
inline void Attributes::set_def(::google::protobuf::uint32 value) {
  set_has_def();
  def_ = value;
}

// optional uint32 first = 4;
inline bool Attributes::has_first() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Attributes::set_has_first() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Attributes::clear_has_first() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Attributes::clear_first() {
  first_ = 0u;
  clear_has_first();
}
inline ::google::protobuf::uint32 Attributes::first() const {
  return first_;
}
inline void Attributes::set_first(::google::protobuf::uint32 value) {
  set_has_first();
  first_ = value;
}

// optional uint32 hit = 5;
inline bool Attributes::has_hit() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Attributes::set_has_hit() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Attributes::clear_has_hit() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Attributes::clear_hit() {
  hit_ = 0u;
  clear_has_hit();
}
inline ::google::protobuf::uint32 Attributes::hit() const {
  return hit_;
}
inline void Attributes::set_hit(::google::protobuf::uint32 value) {
  set_has_hit();
  hit_ = value;
}

// optional uint32 dodge = 6;
inline bool Attributes::has_dodge() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Attributes::set_has_dodge() {
  _has_bits_[0] |= 0x00000020u;
}
inline void Attributes::clear_has_dodge() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void Attributes::clear_dodge() {
  dodge_ = 0u;
  clear_has_dodge();
}
inline ::google::protobuf::uint32 Attributes::dodge() const {
  return dodge_;
}
inline void Attributes::set_dodge(::google::protobuf::uint32 value) {
  set_has_dodge();
  dodge_ = value;
}

// optional uint32 critStrike = 7;
inline bool Attributes::has_critstrike() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void Attributes::set_has_critstrike() {
  _has_bits_[0] |= 0x00000040u;
}
inline void Attributes::clear_has_critstrike() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void Attributes::clear_critstrike() {
  critstrike_ = 0u;
  clear_has_critstrike();
}
inline ::google::protobuf::uint32 Attributes::critstrike() const {
  return critstrike_;
}
inline void Attributes::set_critstrike(::google::protobuf::uint32 value) {
  set_has_critstrike();
  critstrike_ = value;
}

// optional uint32 critRate = 8;
inline bool Attributes::has_critrate() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void Attributes::set_has_critrate() {
  _has_bits_[0] |= 0x00000080u;
}
inline void Attributes::clear_has_critrate() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void Attributes::clear_critrate() {
  critrate_ = 0u;
  clear_has_critrate();
}
inline ::google::protobuf::uint32 Attributes::critrate() const {
  return critrate_;
}
inline void Attributes::set_critrate(::google::protobuf::uint32 value) {
  set_has_critrate();
  critrate_ = value;
}

// optional uint32 critResist = 9;
inline bool Attributes::has_critresist() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void Attributes::set_has_critresist() {
  _has_bits_[0] |= 0x00000100u;
}
inline void Attributes::clear_has_critresist() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void Attributes::clear_critresist() {
  critresist_ = 0u;
  clear_has_critresist();
}
inline ::google::protobuf::uint32 Attributes::critresist() const {
  return critresist_;
}
inline void Attributes::set_critresist(::google::protobuf::uint32 value) {
  set_has_critresist();
  critresist_ = value;
}

// optional double hp_add = 10;
inline bool Attributes::has_hp_add() const {
  return (_has_bits_[0] & 0x00000200u) != 0;
}
inline void Attributes::set_has_hp_add() {
  _has_bits_[0] |= 0x00000200u;
}
inline void Attributes::clear_has_hp_add() {
  _has_bits_[0] &= ~0x00000200u;
}
inline void Attributes::clear_hp_add() {
  hp_add_ = 0;
  clear_has_hp_add();
}
inline double Attributes::hp_add() const {
  return hp_add_;
}
inline void Attributes::set_hp_add(double value) {
  set_has_hp_add();
  hp_add_ = value;
}

// optional double att_add = 11;
inline bool Attributes::has_att_add() const {
  return (_has_bits_[0] & 0x00000400u) != 0;
}
inline void Attributes::set_has_att_add() {
  _has_bits_[0] |= 0x00000400u;
}
inline void Attributes::clear_has_att_add() {
  _has_bits_[0] &= ~0x00000400u;
}
inline void Attributes::clear_att_add() {
  att_add_ = 0;
  clear_has_att_add();
}
inline double Attributes::att_add() const {
  return att_add_;
}
inline void Attributes::set_att_add(double value) {
  set_has_att_add();
  att_add_ = value;
}

// optional double def_add = 12;
inline bool Attributes::has_def_add() const {
  return (_has_bits_[0] & 0x00000800u) != 0;
}
inline void Attributes::set_has_def_add() {
  _has_bits_[0] |= 0x00000800u;
}
inline void Attributes::clear_has_def_add() {
  _has_bits_[0] &= ~0x00000800u;
}
inline void Attributes::clear_def_add() {
  def_add_ = 0;
  clear_has_def_add();
}
inline double Attributes::def_add() const {
  return def_add_;
}
inline void Attributes::set_def_add(double value) {
  set_has_def_add();
  def_add_ = value;
}

// -------------------------------------------------------------------

// StarList

// required uint32 id = 1;
inline bool StarList::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void StarList::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void StarList::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void StarList::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 StarList::id() const {
  return id_;
}
inline void StarList::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// required .Stars.Attributes attr = 2;
inline bool StarList::has_attr() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void StarList::set_has_attr() {
  _has_bits_[0] |= 0x00000002u;
}
inline void StarList::clear_has_attr() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void StarList::clear_attr() {
  if (attr_ != NULL) attr_->::Stars::Attributes::Clear();
  clear_has_attr();
}
inline const ::Stars::Attributes& StarList::attr() const {
  return attr_ != NULL ? *attr_ : *default_instance_->attr_;
}
inline ::Stars::Attributes* StarList::mutable_attr() {
  set_has_attr();
  if (attr_ == NULL) attr_ = new ::Stars::Attributes;
  return attr_;
}
inline ::Stars::Attributes* StarList::release_attr() {
  clear_has_attr();
  ::Stars::Attributes* temp = attr_;
  attr_ = NULL;
  return temp;
}

// required .CommonGiftConfig.CommonModifyItem price = 3;
inline bool StarList::has_price() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void StarList::set_has_price() {
  _has_bits_[0] |= 0x00000004u;
}
inline void StarList::clear_has_price() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void StarList::clear_price() {
  if (price_ != NULL) price_->::CommonGiftConfig::CommonModifyItem::Clear();
  clear_has_price();
}
inline const ::CommonGiftConfig::CommonModifyItem& StarList::price() const {
  return price_ != NULL ? *price_ : *default_instance_->price_;
}
inline ::CommonGiftConfig::CommonModifyItem* StarList::mutable_price() {
  set_has_price();
  if (price_ == NULL) price_ = new ::CommonGiftConfig::CommonModifyItem;
  return price_;
}
inline ::CommonGiftConfig::CommonModifyItem* StarList::release_price() {
  clear_has_price();
  ::CommonGiftConfig::CommonModifyItem* temp = price_;
  price_ = NULL;
  return temp;
}

// required uint32 fight_power = 4;
inline bool StarList::has_fight_power() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void StarList::set_has_fight_power() {
  _has_bits_[0] |= 0x00000008u;
}
inline void StarList::clear_has_fight_power() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void StarList::clear_fight_power() {
  fight_power_ = 0u;
  clear_has_fight_power();
}
inline ::google::protobuf::uint32 StarList::fight_power() const {
  return fight_power_;
}
inline void StarList::set_fight_power(::google::protobuf::uint32 value) {
  set_has_fight_power();
  fight_power_ = value;
}

// -------------------------------------------------------------------

// HeroWithStars

// required uint32 heroid = 1;
inline bool HeroWithStars::has_heroid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void HeroWithStars::set_has_heroid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void HeroWithStars::clear_has_heroid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void HeroWithStars::clear_heroid() {
  heroid_ = 0u;
  clear_has_heroid();
}
inline ::google::protobuf::uint32 HeroWithStars::heroid() const {
  return heroid_;
}
inline void HeroWithStars::set_heroid(::google::protobuf::uint32 value) {
  set_has_heroid();
  heroid_ = value;
}

// repeated .Stars.StarList list = 2;
inline int HeroWithStars::list_size() const {
  return list_.size();
}
inline void HeroWithStars::clear_list() {
  list_.Clear();
}
inline const ::Stars::StarList& HeroWithStars::list(int index) const {
  return list_.Get(index);
}
inline ::Stars::StarList* HeroWithStars::mutable_list(int index) {
  return list_.Mutable(index);
}
inline ::Stars::StarList* HeroWithStars::add_list() {
  return list_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Stars::StarList >&
HeroWithStars::list() const {
  return list_;
}
inline ::google::protobuf::RepeatedPtrField< ::Stars::StarList >*
HeroWithStars::mutable_list() {
  return &list_;
}

// -------------------------------------------------------------------

// StarInfo

// repeated .Stars.HeroWithStars starInfo = 1;
inline int StarInfo::starinfo_size() const {
  return starinfo_.size();
}
inline void StarInfo::clear_starinfo() {
  starinfo_.Clear();
}
inline const ::Stars::HeroWithStars& StarInfo::starinfo(int index) const {
  return starinfo_.Get(index);
}
inline ::Stars::HeroWithStars* StarInfo::mutable_starinfo(int index) {
  return starinfo_.Mutable(index);
}
inline ::Stars::HeroWithStars* StarInfo::add_starinfo() {
  return starinfo_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Stars::HeroWithStars >&
StarInfo::starinfo() const {
  return starinfo_;
}
inline ::google::protobuf::RepeatedPtrField< ::Stars::HeroWithStars >*
StarInfo::mutable_starinfo() {
  return &starinfo_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Stars

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Stars_2eproto__INCLUDED