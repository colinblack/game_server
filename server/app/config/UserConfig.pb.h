// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UserConfig.proto

#ifndef PROTOBUF_UserConfig_2eproto__INCLUDED
#define PROTOBUF_UserConfig_2eproto__INCLUDED

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
#include "VipGiftConfig.pb.h"
// @@protoc_insertion_point(includes)

namespace UserCfg {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_UserConfig_2eproto();
void protobuf_AssignDesc_UserConfig_2eproto();
void protobuf_ShutdownFile_UserConfig_2eproto();

class UserBase;
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

  // required uint32 wood = 2;
  inline bool has_wood() const;
  inline void clear_wood();
  static const int kWoodFieldNumber = 2;
  inline ::google::protobuf::uint32 wood() const;
  inline void set_wood(::google::protobuf::uint32 value);

  // required uint32 food = 3;
  inline bool has_food() const;
  inline void clear_food();
  static const int kFoodFieldNumber = 3;
  inline ::google::protobuf::uint32 food() const;
  inline void set_food(::google::protobuf::uint32 value);

  // required uint32 iron = 4;
  inline bool has_iron() const;
  inline void clear_iron();
  static const int kIronFieldNumber = 4;
  inline ::google::protobuf::uint32 iron() const;
  inline void set_iron(::google::protobuf::uint32 value);

  // required uint32 cash = 5;
  inline bool has_cash() const;
  inline void clear_cash();
  static const int kCashFieldNumber = 5;
  inline ::google::protobuf::uint32 cash() const;
  inline void set_cash(::google::protobuf::uint32 value);

  // required uint32 level = 6;
  inline bool has_level() const;
  inline void clear_level();
  static const int kLevelFieldNumber = 6;
  inline ::google::protobuf::uint32 level() const;
  inline void set_level(::google::protobuf::uint32 value);

  // required uint32 exp = 7;
  inline bool has_exp() const;
  inline void clear_exp();
  static const int kExpFieldNumber = 7;
  inline ::google::protobuf::uint32 exp() const;
  inline void set_exp(::google::protobuf::uint32 value);

  // required uint32 order = 8;
  inline bool has_order() const;
  inline void clear_order();
  static const int kOrderFieldNumber = 8;
  inline ::google::protobuf::uint32 order() const;
  inline void set_order(::google::protobuf::uint32 value);

  // repeated .VipGiftConfig.EquipReward equips = 9;
  inline int equips_size() const;
  inline void clear_equips();
  static const int kEquipsFieldNumber = 9;
  inline const ::VipGiftConfig::EquipReward& equips(int index) const;
  inline ::VipGiftConfig::EquipReward* mutable_equips(int index);
  inline ::VipGiftConfig::EquipReward* add_equips();
  inline const ::google::protobuf::RepeatedPtrField< ::VipGiftConfig::EquipReward >&
      equips() const;
  inline ::google::protobuf::RepeatedPtrField< ::VipGiftConfig::EquipReward >*
      mutable_equips();

  // @@protoc_insertion_point(class_scope:UserCfg.UserBase)
 private:
  inline void set_has_coin();
  inline void clear_has_coin();
  inline void set_has_wood();
  inline void clear_has_wood();
  inline void set_has_food();
  inline void clear_has_food();
  inline void set_has_iron();
  inline void clear_has_iron();
  inline void set_has_cash();
  inline void clear_has_cash();
  inline void set_has_level();
  inline void clear_has_level();
  inline void set_has_exp();
  inline void clear_has_exp();
  inline void set_has_order();
  inline void clear_has_order();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 coin_;
  ::google::protobuf::uint32 wood_;
  ::google::protobuf::uint32 food_;
  ::google::protobuf::uint32 iron_;
  ::google::protobuf::uint32 cash_;
  ::google::protobuf::uint32 level_;
  ::google::protobuf::uint32 exp_;
  ::google::protobuf::uint32 order_;
  ::google::protobuf::RepeatedPtrField< ::VipGiftConfig::EquipReward > equips_;
  friend void  protobuf_AddDesc_UserConfig_2eproto();
  friend void protobuf_AssignDesc_UserConfig_2eproto();
  friend void protobuf_ShutdownFile_UserConfig_2eproto();

  void InitAsDefaultInstance();
  static UserBase* default_instance_;
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
  inline void set_allocated_user_init(::UserCfg::UserBase* user_init);

  // repeated uint64 user_exp = 2;
  inline int user_exp_size() const;
  inline void clear_user_exp();
  static const int kUserExpFieldNumber = 2;
  inline ::google::protobuf::uint64 user_exp(int index) const;
  inline void set_user_exp(int index, ::google::protobuf::uint64 value);
  inline void add_user_exp(::google::protobuf::uint64 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
      user_exp() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
      mutable_user_exp();

  // @@protoc_insertion_point(class_scope:UserCfg.User)
 private:
  inline void set_has_user_init();
  inline void clear_has_user_init();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::UserCfg::UserBase* user_init_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint64 > user_exp_;
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
  // @@protoc_insertion_point(field_get:UserCfg.UserBase.coin)
  return coin_;
}
inline void UserBase::set_coin(::google::protobuf::uint32 value) {
  set_has_coin();
  coin_ = value;
  // @@protoc_insertion_point(field_set:UserCfg.UserBase.coin)
}

// required uint32 wood = 2;
inline bool UserBase::has_wood() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void UserBase::set_has_wood() {
  _has_bits_[0] |= 0x00000002u;
}
inline void UserBase::clear_has_wood() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void UserBase::clear_wood() {
  wood_ = 0u;
  clear_has_wood();
}
inline ::google::protobuf::uint32 UserBase::wood() const {
  // @@protoc_insertion_point(field_get:UserCfg.UserBase.wood)
  return wood_;
}
inline void UserBase::set_wood(::google::protobuf::uint32 value) {
  set_has_wood();
  wood_ = value;
  // @@protoc_insertion_point(field_set:UserCfg.UserBase.wood)
}

// required uint32 food = 3;
inline bool UserBase::has_food() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void UserBase::set_has_food() {
  _has_bits_[0] |= 0x00000004u;
}
inline void UserBase::clear_has_food() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void UserBase::clear_food() {
  food_ = 0u;
  clear_has_food();
}
inline ::google::protobuf::uint32 UserBase::food() const {
  // @@protoc_insertion_point(field_get:UserCfg.UserBase.food)
  return food_;
}
inline void UserBase::set_food(::google::protobuf::uint32 value) {
  set_has_food();
  food_ = value;
  // @@protoc_insertion_point(field_set:UserCfg.UserBase.food)
}

// required uint32 iron = 4;
inline bool UserBase::has_iron() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void UserBase::set_has_iron() {
  _has_bits_[0] |= 0x00000008u;
}
inline void UserBase::clear_has_iron() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void UserBase::clear_iron() {
  iron_ = 0u;
  clear_has_iron();
}
inline ::google::protobuf::uint32 UserBase::iron() const {
  // @@protoc_insertion_point(field_get:UserCfg.UserBase.iron)
  return iron_;
}
inline void UserBase::set_iron(::google::protobuf::uint32 value) {
  set_has_iron();
  iron_ = value;
  // @@protoc_insertion_point(field_set:UserCfg.UserBase.iron)
}

// required uint32 cash = 5;
inline bool UserBase::has_cash() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void UserBase::set_has_cash() {
  _has_bits_[0] |= 0x00000010u;
}
inline void UserBase::clear_has_cash() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void UserBase::clear_cash() {
  cash_ = 0u;
  clear_has_cash();
}
inline ::google::protobuf::uint32 UserBase::cash() const {
  // @@protoc_insertion_point(field_get:UserCfg.UserBase.cash)
  return cash_;
}
inline void UserBase::set_cash(::google::protobuf::uint32 value) {
  set_has_cash();
  cash_ = value;
  // @@protoc_insertion_point(field_set:UserCfg.UserBase.cash)
}

// required uint32 level = 6;
inline bool UserBase::has_level() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void UserBase::set_has_level() {
  _has_bits_[0] |= 0x00000020u;
}
inline void UserBase::clear_has_level() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void UserBase::clear_level() {
  level_ = 0u;
  clear_has_level();
}
inline ::google::protobuf::uint32 UserBase::level() const {
  // @@protoc_insertion_point(field_get:UserCfg.UserBase.level)
  return level_;
}
inline void UserBase::set_level(::google::protobuf::uint32 value) {
  set_has_level();
  level_ = value;
  // @@protoc_insertion_point(field_set:UserCfg.UserBase.level)
}

// required uint32 exp = 7;
inline bool UserBase::has_exp() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void UserBase::set_has_exp() {
  _has_bits_[0] |= 0x00000040u;
}
inline void UserBase::clear_has_exp() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void UserBase::clear_exp() {
  exp_ = 0u;
  clear_has_exp();
}
inline ::google::protobuf::uint32 UserBase::exp() const {
  // @@protoc_insertion_point(field_get:UserCfg.UserBase.exp)
  return exp_;
}
inline void UserBase::set_exp(::google::protobuf::uint32 value) {
  set_has_exp();
  exp_ = value;
  // @@protoc_insertion_point(field_set:UserCfg.UserBase.exp)
}

// required uint32 order = 8;
inline bool UserBase::has_order() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void UserBase::set_has_order() {
  _has_bits_[0] |= 0x00000080u;
}
inline void UserBase::clear_has_order() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void UserBase::clear_order() {
  order_ = 0u;
  clear_has_order();
}
inline ::google::protobuf::uint32 UserBase::order() const {
  // @@protoc_insertion_point(field_get:UserCfg.UserBase.order)
  return order_;
}
inline void UserBase::set_order(::google::protobuf::uint32 value) {
  set_has_order();
  order_ = value;
  // @@protoc_insertion_point(field_set:UserCfg.UserBase.order)
}

// repeated .VipGiftConfig.EquipReward equips = 9;
inline int UserBase::equips_size() const {
  return equips_.size();
}
inline void UserBase::clear_equips() {
  equips_.Clear();
}
inline const ::VipGiftConfig::EquipReward& UserBase::equips(int index) const {
  // @@protoc_insertion_point(field_get:UserCfg.UserBase.equips)
  return equips_.Get(index);
}
inline ::VipGiftConfig::EquipReward* UserBase::mutable_equips(int index) {
  // @@protoc_insertion_point(field_mutable:UserCfg.UserBase.equips)
  return equips_.Mutable(index);
}
inline ::VipGiftConfig::EquipReward* UserBase::add_equips() {
  // @@protoc_insertion_point(field_add:UserCfg.UserBase.equips)
  return equips_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::VipGiftConfig::EquipReward >&
UserBase::equips() const {
  // @@protoc_insertion_point(field_list:UserCfg.UserBase.equips)
  return equips_;
}
inline ::google::protobuf::RepeatedPtrField< ::VipGiftConfig::EquipReward >*
UserBase::mutable_equips() {
  // @@protoc_insertion_point(field_mutable_list:UserCfg.UserBase.equips)
  return &equips_;
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
  // @@protoc_insertion_point(field_get:UserCfg.User.user_init)
  return user_init_ != NULL ? *user_init_ : *default_instance_->user_init_;
}
inline ::UserCfg::UserBase* User::mutable_user_init() {
  set_has_user_init();
  if (user_init_ == NULL) user_init_ = new ::UserCfg::UserBase;
  // @@protoc_insertion_point(field_mutable:UserCfg.User.user_init)
  return user_init_;
}
inline ::UserCfg::UserBase* User::release_user_init() {
  clear_has_user_init();
  ::UserCfg::UserBase* temp = user_init_;
  user_init_ = NULL;
  return temp;
}
inline void User::set_allocated_user_init(::UserCfg::UserBase* user_init) {
  delete user_init_;
  user_init_ = user_init;
  if (user_init) {
    set_has_user_init();
  } else {
    clear_has_user_init();
  }
  // @@protoc_insertion_point(field_set_allocated:UserCfg.User.user_init)
}

// repeated uint64 user_exp = 2;
inline int User::user_exp_size() const {
  return user_exp_.size();
}
inline void User::clear_user_exp() {
  user_exp_.Clear();
}
inline ::google::protobuf::uint64 User::user_exp(int index) const {
  // @@protoc_insertion_point(field_get:UserCfg.User.user_exp)
  return user_exp_.Get(index);
}
inline void User::set_user_exp(int index, ::google::protobuf::uint64 value) {
  user_exp_.Set(index, value);
  // @@protoc_insertion_point(field_set:UserCfg.User.user_exp)
}
inline void User::add_user_exp(::google::protobuf::uint64 value) {
  user_exp_.Add(value);
  // @@protoc_insertion_point(field_add:UserCfg.User.user_exp)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
User::user_exp() const {
  // @@protoc_insertion_point(field_list:UserCfg.User.user_exp)
  return user_exp_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
User::mutable_user_exp() {
  // @@protoc_insertion_point(field_mutable_list:UserCfg.User.user_exp)
  return &user_exp_;
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
