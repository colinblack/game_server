// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UserConfig.proto

#ifndef PROTOBUF_UserConfig_2eproto__INCLUDED
#define PROTOBUF_UserConfig_2eproto__INCLUDED

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

namespace UserCfg {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_UserConfig_2eproto();
void protobuf_AssignDesc_UserConfig_2eproto();
void protobuf_ShutdownFile_UserConfig_2eproto();

class UserBase;
class Hero;
class ChampionshipCfg;
class User;

// ===================================================================

class UserBase : public ::google::protobuf::Message {
 public:
  UserBase();
  virtual ~UserBase();
  
  UserBase(const UserBase& from);
  
  inline UserBase& operator=(const UserBase& from) {
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
  static const UserBase& default_instance();
  
  void Swap(UserBase* other);
  
  // implements Message ----------------------------------------------
  
  UserBase* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const UserBase& from);
  void MergeFrom(const UserBase& from);
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
  
  // required uint32 coin = 1;
  inline bool has_coin() const;
  inline void clear_coin();
  static const int kCoinFieldNumber = 1;
  inline ::google::protobuf::uint32 coin() const;
  inline void set_coin(::google::protobuf::uint32 value);
  
  // required uint32 cash = 2;
  inline bool has_cash() const;
  inline void clear_cash();
  static const int kCashFieldNumber = 2;
  inline ::google::protobuf::uint32 cash() const;
  inline void set_cash(::google::protobuf::uint32 value);
  
  // required uint32 level = 3;
  inline bool has_level() const;
  inline void clear_level();
  static const int kLevelFieldNumber = 3;
  inline ::google::protobuf::uint32 level() const;
  inline void set_level(::google::protobuf::uint32 value);
  
  // required uint32 exp = 4;
  inline bool has_exp() const;
  inline void clear_exp();
  static const int kExpFieldNumber = 4;
  inline ::google::protobuf::uint32 exp() const;
  inline void set_exp(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:UserCfg.UserBase)
 private:
  inline void set_has_coin();
  inline void clear_has_coin();
  inline void set_has_cash();
  inline void clear_has_cash();
  inline void set_has_level();
  inline void clear_has_level();
  inline void set_has_exp();
  inline void clear_has_exp();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint32 coin_;
  ::google::protobuf::uint32 cash_;
  ::google::protobuf::uint32 level_;
  ::google::protobuf::uint32 exp_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];
  
  friend void  protobuf_AddDesc_UserConfig_2eproto();
  friend void protobuf_AssignDesc_UserConfig_2eproto();
  friend void protobuf_ShutdownFile_UserConfig_2eproto();
  
  void InitAsDefaultInstance();
  static UserBase* default_instance_;
};
// -------------------------------------------------------------------

class Hero : public ::google::protobuf::Message {
 public:
  Hero();
  virtual ~Hero();
  
  Hero(const Hero& from);
  
  inline Hero& operator=(const Hero& from) {
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
  static const Hero& default_instance();
  
  void Swap(Hero* other);
  
  // implements Message ----------------------------------------------
  
  Hero* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Hero& from);
  void MergeFrom(const Hero& from);
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
  
  // required uint32 level = 2;
  inline bool has_level() const;
  inline void clear_level();
  static const int kLevelFieldNumber = 2;
  inline ::google::protobuf::uint32 level() const;
  inline void set_level(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:UserCfg.Hero)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_level();
  inline void clear_has_level();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 level_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_UserConfig_2eproto();
  friend void protobuf_AssignDesc_UserConfig_2eproto();
  friend void protobuf_ShutdownFile_UserConfig_2eproto();
  
  void InitAsDefaultInstance();
  static Hero* default_instance_;
};
// -------------------------------------------------------------------

class ChampionshipCfg : public ::google::protobuf::Message {
 public:
  ChampionshipCfg();
  virtual ~ChampionshipCfg();
  
  ChampionshipCfg(const ChampionshipCfg& from);
  
  inline ChampionshipCfg& operator=(const ChampionshipCfg& from) {
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
  static const ChampionshipCfg& default_instance();
  
  void Swap(ChampionshipCfg* other);
  
  // implements Message ----------------------------------------------
  
  ChampionshipCfg* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ChampionshipCfg& from);
  void MergeFrom(const ChampionshipCfg& from);
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
  
  // required uint32 grade_limit = 2;
  inline bool has_grade_limit() const;
  inline void clear_grade_limit();
  static const int kGradeLimitFieldNumber = 2;
  inline ::google::protobuf::uint32 grade_limit() const;
  inline void set_grade_limit(::google::protobuf::uint32 value);
  
  // required .CommonGiftConfig.CommonModifyItem cost = 3;
  inline bool has_cost() const;
  inline void clear_cost();
  static const int kCostFieldNumber = 3;
  inline const ::CommonGiftConfig::CommonModifyItem& cost() const;
  inline ::CommonGiftConfig::CommonModifyItem* mutable_cost();
  inline ::CommonGiftConfig::CommonModifyItem* release_cost();
  
  // @@protoc_insertion_point(class_scope:UserCfg.ChampionshipCfg)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_grade_limit();
  inline void clear_has_grade_limit();
  inline void set_has_cost();
  inline void clear_has_cost();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 grade_limit_;
  ::CommonGiftConfig::CommonModifyItem* cost_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_UserConfig_2eproto();
  friend void protobuf_AssignDesc_UserConfig_2eproto();
  friend void protobuf_ShutdownFile_UserConfig_2eproto();
  
  void InitAsDefaultInstance();
  static ChampionshipCfg* default_instance_;
};
// -------------------------------------------------------------------

class User : public ::google::protobuf::Message {
 public:
  User();
  virtual ~User();
  
  User(const User& from);
  
  inline User& operator=(const User& from) {
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
  static const User& default_instance();
  
  void Swap(User* other);
  
  // implements Message ----------------------------------------------
  
  User* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const User& from);
  void MergeFrom(const User& from);
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
  
  // required .UserCfg.UserBase user_init = 1;
  inline bool has_user_init() const;
  inline void clear_user_init();
  static const int kUserInitFieldNumber = 1;
  inline const ::UserCfg::UserBase& user_init() const;
  inline ::UserCfg::UserBase* mutable_user_init();
  inline ::UserCfg::UserBase* release_user_init();
  
  // required .CommonGiftConfig.CommonModifyItem initprops = 2;
  inline bool has_initprops() const;
  inline void clear_initprops();
  static const int kInitpropsFieldNumber = 2;
  inline const ::CommonGiftConfig::CommonModifyItem& initprops() const;
  inline ::CommonGiftConfig::CommonModifyItem* mutable_initprops();
  inline ::CommonGiftConfig::CommonModifyItem* release_initprops();
  
  // repeated uint64 user_exp = 3;
  inline int user_exp_size() const;
  inline void clear_user_exp();
  static const int kUserExpFieldNumber = 3;
  inline ::google::protobuf::uint64 user_exp(int index) const;
  inline void set_user_exp(int index, ::google::protobuf::uint64 value);
  inline void add_user_exp(::google::protobuf::uint64 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
      user_exp() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
      mutable_user_exp();
  
  // repeated .UserCfg.Hero hero = 4;
  inline int hero_size() const;
  inline void clear_hero();
  static const int kHeroFieldNumber = 4;
  inline const ::UserCfg::Hero& hero(int index) const;
  inline ::UserCfg::Hero* mutable_hero(int index);
  inline ::UserCfg::Hero* add_hero();
  inline const ::google::protobuf::RepeatedPtrField< ::UserCfg::Hero >&
      hero() const;
  inline ::google::protobuf::RepeatedPtrField< ::UserCfg::Hero >*
      mutable_hero();
  
  // repeated .UserCfg.ChampionshipCfg championship = 5;
  inline int championship_size() const;
  inline void clear_championship();
  static const int kChampionshipFieldNumber = 5;
  inline const ::UserCfg::ChampionshipCfg& championship(int index) const;
  inline ::UserCfg::ChampionshipCfg* mutable_championship(int index);
  inline ::UserCfg::ChampionshipCfg* add_championship();
  inline const ::google::protobuf::RepeatedPtrField< ::UserCfg::ChampionshipCfg >&
      championship() const;
  inline ::google::protobuf::RepeatedPtrField< ::UserCfg::ChampionshipCfg >*
      mutable_championship();
  
  // @@protoc_insertion_point(class_scope:UserCfg.User)
 private:
  inline void set_has_user_init();
  inline void clear_has_user_init();
  inline void set_has_initprops();
  inline void clear_has_initprops();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::UserCfg::UserBase* user_init_;
  ::CommonGiftConfig::CommonModifyItem* initprops_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint64 > user_exp_;
  ::google::protobuf::RepeatedPtrField< ::UserCfg::Hero > hero_;
  ::google::protobuf::RepeatedPtrField< ::UserCfg::ChampionshipCfg > championship_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];
  
  friend void  protobuf_AddDesc_UserConfig_2eproto();
  friend void protobuf_AssignDesc_UserConfig_2eproto();
  friend void protobuf_ShutdownFile_UserConfig_2eproto();
  
  void InitAsDefaultInstance();
  static User* default_instance_;
};
// ===================================================================


// ===================================================================

// UserBase

// required uint32 coin = 1;
inline bool UserBase::has_coin() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void UserBase::set_has_coin() {
  _has_bits_[0] |= 0x00000001u;
}
inline void UserBase::clear_has_coin() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void UserBase::clear_coin() {
  coin_ = 0u;
  clear_has_coin();
}
inline ::google::protobuf::uint32 UserBase::coin() const {
  return coin_;
}
inline void UserBase::set_coin(::google::protobuf::uint32 value) {
  set_has_coin();
  coin_ = value;
}

// required uint32 cash = 2;
inline bool UserBase::has_cash() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void UserBase::set_has_cash() {
  _has_bits_[0] |= 0x00000002u;
}
inline void UserBase::clear_has_cash() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void UserBase::clear_cash() {
  cash_ = 0u;
  clear_has_cash();
}
inline ::google::protobuf::uint32 UserBase::cash() const {
  return cash_;
}
inline void UserBase::set_cash(::google::protobuf::uint32 value) {
  set_has_cash();
  cash_ = value;
}

// required uint32 level = 3;
inline bool UserBase::has_level() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void UserBase::set_has_level() {
  _has_bits_[0] |= 0x00000004u;
}
inline void UserBase::clear_has_level() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void UserBase::clear_level() {
  level_ = 0u;
  clear_has_level();
}
inline ::google::protobuf::uint32 UserBase::level() const {
  return level_;
}
inline void UserBase::set_level(::google::protobuf::uint32 value) {
  set_has_level();
  level_ = value;
}

// required uint32 exp = 4;
inline bool UserBase::has_exp() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void UserBase::set_has_exp() {
  _has_bits_[0] |= 0x00000008u;
}
inline void UserBase::clear_has_exp() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void UserBase::clear_exp() {
  exp_ = 0u;
  clear_has_exp();
}
inline ::google::protobuf::uint32 UserBase::exp() const {
  return exp_;
}
inline void UserBase::set_exp(::google::protobuf::uint32 value) {
  set_has_exp();
  exp_ = value;
}

// -------------------------------------------------------------------

// Hero

// required uint32 id = 1;
inline bool Hero::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Hero::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Hero::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Hero::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 Hero::id() const {
  return id_;
}
inline void Hero::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// required uint32 level = 2;
inline bool Hero::has_level() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Hero::set_has_level() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Hero::clear_has_level() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Hero::clear_level() {
  level_ = 0u;
  clear_has_level();
}
inline ::google::protobuf::uint32 Hero::level() const {
  return level_;
}
inline void Hero::set_level(::google::protobuf::uint32 value) {
  set_has_level();
  level_ = value;
}

// -------------------------------------------------------------------

// ChampionshipCfg

// required uint32 id = 1;
inline bool ChampionshipCfg::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ChampionshipCfg::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ChampionshipCfg::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ChampionshipCfg::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 ChampionshipCfg::id() const {
  return id_;
}
inline void ChampionshipCfg::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// required uint32 grade_limit = 2;
inline bool ChampionshipCfg::has_grade_limit() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ChampionshipCfg::set_has_grade_limit() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ChampionshipCfg::clear_has_grade_limit() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ChampionshipCfg::clear_grade_limit() {
  grade_limit_ = 0u;
  clear_has_grade_limit();
}
inline ::google::protobuf::uint32 ChampionshipCfg::grade_limit() const {
  return grade_limit_;
}
inline void ChampionshipCfg::set_grade_limit(::google::protobuf::uint32 value) {
  set_has_grade_limit();
  grade_limit_ = value;
}

// required .CommonGiftConfig.CommonModifyItem cost = 3;
inline bool ChampionshipCfg::has_cost() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ChampionshipCfg::set_has_cost() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ChampionshipCfg::clear_has_cost() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ChampionshipCfg::clear_cost() {
  if (cost_ != NULL) cost_->::CommonGiftConfig::CommonModifyItem::Clear();
  clear_has_cost();
}
inline const ::CommonGiftConfig::CommonModifyItem& ChampionshipCfg::cost() const {
  return cost_ != NULL ? *cost_ : *default_instance_->cost_;
}
inline ::CommonGiftConfig::CommonModifyItem* ChampionshipCfg::mutable_cost() {
  set_has_cost();
  if (cost_ == NULL) cost_ = new ::CommonGiftConfig::CommonModifyItem;
  return cost_;
}
inline ::CommonGiftConfig::CommonModifyItem* ChampionshipCfg::release_cost() {
  clear_has_cost();
  ::CommonGiftConfig::CommonModifyItem* temp = cost_;
  cost_ = NULL;
  return temp;
}

// -------------------------------------------------------------------

// User

// required .UserCfg.UserBase user_init = 1;
inline bool User::has_user_init() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void User::set_has_user_init() {
  _has_bits_[0] |= 0x00000001u;
}
inline void User::clear_has_user_init() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void User::clear_user_init() {
  if (user_init_ != NULL) user_init_->::UserCfg::UserBase::Clear();
  clear_has_user_init();
}
inline const ::UserCfg::UserBase& User::user_init() const {
  return user_init_ != NULL ? *user_init_ : *default_instance_->user_init_;
}
inline ::UserCfg::UserBase* User::mutable_user_init() {
  set_has_user_init();
  if (user_init_ == NULL) user_init_ = new ::UserCfg::UserBase;
  return user_init_;
}
inline ::UserCfg::UserBase* User::release_user_init() {
  clear_has_user_init();
  ::UserCfg::UserBase* temp = user_init_;
  user_init_ = NULL;
  return temp;
}

// required .CommonGiftConfig.CommonModifyItem initprops = 2;
inline bool User::has_initprops() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void User::set_has_initprops() {
  _has_bits_[0] |= 0x00000002u;
}
inline void User::clear_has_initprops() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void User::clear_initprops() {
  if (initprops_ != NULL) initprops_->::CommonGiftConfig::CommonModifyItem::Clear();
  clear_has_initprops();
}
inline const ::CommonGiftConfig::CommonModifyItem& User::initprops() const {
  return initprops_ != NULL ? *initprops_ : *default_instance_->initprops_;
}
inline ::CommonGiftConfig::CommonModifyItem* User::mutable_initprops() {
  set_has_initprops();
  if (initprops_ == NULL) initprops_ = new ::CommonGiftConfig::CommonModifyItem;
  return initprops_;
}
inline ::CommonGiftConfig::CommonModifyItem* User::release_initprops() {
  clear_has_initprops();
  ::CommonGiftConfig::CommonModifyItem* temp = initprops_;
  initprops_ = NULL;
  return temp;
}

// repeated uint64 user_exp = 3;
inline int User::user_exp_size() const {
  return user_exp_.size();
}
inline void User::clear_user_exp() {
  user_exp_.Clear();
}
inline ::google::protobuf::uint64 User::user_exp(int index) const {
  return user_exp_.Get(index);
}
inline void User::set_user_exp(int index, ::google::protobuf::uint64 value) {
  user_exp_.Set(index, value);
}
inline void User::add_user_exp(::google::protobuf::uint64 value) {
  user_exp_.Add(value);
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
User::user_exp() const {
  return user_exp_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
User::mutable_user_exp() {
  return &user_exp_;
}

// repeated .UserCfg.Hero hero = 4;
inline int User::hero_size() const {
  return hero_.size();
}
inline void User::clear_hero() {
  hero_.Clear();
}
inline const ::UserCfg::Hero& User::hero(int index) const {
  return hero_.Get(index);
}
inline ::UserCfg::Hero* User::mutable_hero(int index) {
  return hero_.Mutable(index);
}
inline ::UserCfg::Hero* User::add_hero() {
  return hero_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::UserCfg::Hero >&
User::hero() const {
  return hero_;
}
inline ::google::protobuf::RepeatedPtrField< ::UserCfg::Hero >*
User::mutable_hero() {
  return &hero_;
}

// repeated .UserCfg.ChampionshipCfg championship = 5;
inline int User::championship_size() const {
  return championship_.size();
}
inline void User::clear_championship() {
  championship_.Clear();
}
inline const ::UserCfg::ChampionshipCfg& User::championship(int index) const {
  return championship_.Get(index);
}
inline ::UserCfg::ChampionshipCfg* User::mutable_championship(int index) {
  return championship_.Mutable(index);
}
inline ::UserCfg::ChampionshipCfg* User::add_championship() {
  return championship_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::UserCfg::ChampionshipCfg >&
User::championship() const {
  return championship_;
}
inline ::google::protobuf::RepeatedPtrField< ::UserCfg::ChampionshipCfg >*
User::mutable_championship() {
  return &championship_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace UserCfg

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_UserConfig_2eproto__INCLUDED
