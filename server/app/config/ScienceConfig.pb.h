// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ScienceConfig.proto

#ifndef PROTOBUF_ScienceConfig_2eproto__INCLUDED
#define PROTOBUF_ScienceConfig_2eproto__INCLUDED

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

namespace ScienceConfig {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ScienceConfig_2eproto();
void protobuf_AssignDesc_ScienceConfig_2eproto();
void protobuf_ShutdownFile_ScienceConfig_2eproto();

class ScienceItem;
class Science;

// ===================================================================

class ScienceItem : public ::google::protobuf::Message {
 public:
  ScienceItem();
  virtual ~ScienceItem();

  ScienceItem(const ScienceItem& from);

  inline ScienceItem& operator=(const ScienceItem& from) {
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
  static const ScienceItem& default_instance();

  void Swap(ScienceItem* other);

  // implements Message ----------------------------------------------

  ScienceItem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ScienceItem& from);
  void MergeFrom(const ScienceItem& from);
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

  // required uint32 pass = 2;
  inline bool has_pass() const;
  inline void clear_pass();
  static const int kPassFieldNumber = 2;
  inline ::google::protobuf::uint32 pass() const;
  inline void set_pass(::google::protobuf::uint32 value);

  // required uint32 type = 3;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 3;
  inline ::google::protobuf::uint32 type() const;
  inline void set_type(::google::protobuf::uint32 value);

  // required uint32 val = 4;
  inline bool has_val() const;
  inline void clear_val();
  static const int kValFieldNumber = 4;
  inline ::google::protobuf::uint32 val() const;
  inline void set_val(::google::protobuf::uint32 value);

  // required uint32 cd = 5;
  inline bool has_cd() const;
  inline void clear_cd();
  static const int kCdFieldNumber = 5;
  inline ::google::protobuf::uint32 cd() const;
  inline void set_cd(::google::protobuf::uint32 value);

  // required uint32 cost_coins = 6;
  inline bool has_cost_coins() const;
  inline void clear_cost_coins();
  static const int kCostCoinsFieldNumber = 6;
  inline ::google::protobuf::uint32 cost_coins() const;
  inline void set_cost_coins(::google::protobuf::uint32 value);

  // required uint32 cost_food = 7;
  inline bool has_cost_food() const;
  inline void clear_cost_food();
  static const int kCostFoodFieldNumber = 7;
  inline ::google::protobuf::uint32 cost_food() const;
  inline void set_cost_food(::google::protobuf::uint32 value);

  // required uint32 cost_wood = 8;
  inline bool has_cost_wood() const;
  inline void clear_cost_wood();
  static const int kCostWoodFieldNumber = 8;
  inline ::google::protobuf::uint32 cost_wood() const;
  inline void set_cost_wood(::google::protobuf::uint32 value);

  // required uint32 cost_iron = 9;
  inline bool has_cost_iron() const;
  inline void clear_cost_iron();
  static const int kCostIronFieldNumber = 9;
  inline ::google::protobuf::uint32 cost_iron() const;
  inline void set_cost_iron(::google::protobuf::uint32 value);

  // required uint32 capital_cnt = 10;
  inline bool has_capital_cnt() const;
  inline void clear_capital_cnt();
  static const int kCapitalCntFieldNumber = 10;
  inline ::google::protobuf::uint32 capital_cnt() const;
  inline void set_capital_cnt(::google::protobuf::uint32 value);

  // required uint32 pre_lock_id = 11;
  inline bool has_pre_lock_id() const;
  inline void clear_pre_lock_id();
  static const int kPreLockIdFieldNumber = 11;
  inline ::google::protobuf::uint32 pre_lock_id() const;
  inline void set_pre_lock_id(::google::protobuf::uint32 value);

  // required uint32 speed_cash = 12;
  inline bool has_speed_cash() const;
  inline void clear_speed_cash();
  static const int kSpeedCashFieldNumber = 12;
  inline ::google::protobuf::uint32 speed_cash() const;
  inline void set_speed_cash(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:ScienceConfig.ScienceItem)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_pass();
  inline void clear_has_pass();
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_val();
  inline void clear_has_val();
  inline void set_has_cd();
  inline void clear_has_cd();
  inline void set_has_cost_coins();
  inline void clear_has_cost_coins();
  inline void set_has_cost_food();
  inline void clear_has_cost_food();
  inline void set_has_cost_wood();
  inline void clear_has_cost_wood();
  inline void set_has_cost_iron();
  inline void clear_has_cost_iron();
  inline void set_has_capital_cnt();
  inline void clear_has_capital_cnt();
  inline void set_has_pre_lock_id();
  inline void clear_has_pre_lock_id();
  inline void set_has_speed_cash();
  inline void clear_has_speed_cash();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 pass_;
  ::google::protobuf::uint32 type_;
  ::google::protobuf::uint32 val_;
  ::google::protobuf::uint32 cd_;
  ::google::protobuf::uint32 cost_coins_;
  ::google::protobuf::uint32 cost_food_;
  ::google::protobuf::uint32 cost_wood_;
  ::google::protobuf::uint32 cost_iron_;
  ::google::protobuf::uint32 capital_cnt_;
  ::google::protobuf::uint32 pre_lock_id_;
  ::google::protobuf::uint32 speed_cash_;
  friend void  protobuf_AddDesc_ScienceConfig_2eproto();
  friend void protobuf_AssignDesc_ScienceConfig_2eproto();
  friend void protobuf_ShutdownFile_ScienceConfig_2eproto();

  void InitAsDefaultInstance();
  static ScienceItem* default_instance_;
};
// -------------------------------------------------------------------

class Science : public ::google::protobuf::Message {
 public:
  Science();
  virtual ~Science();

  Science(const Science& from);

  inline Science& operator=(const Science& from) {
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
  static const Science& default_instance();

  void Swap(Science* other);

  // implements Message ----------------------------------------------

  Science* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Science& from);
  void MergeFrom(const Science& from);
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

  // repeated .ScienceConfig.ScienceItem sciences = 1;
  inline int sciences_size() const;
  inline void clear_sciences();
  static const int kSciencesFieldNumber = 1;
  inline const ::ScienceConfig::ScienceItem& sciences(int index) const;
  inline ::ScienceConfig::ScienceItem* mutable_sciences(int index);
  inline ::ScienceConfig::ScienceItem* add_sciences();
  inline const ::google::protobuf::RepeatedPtrField< ::ScienceConfig::ScienceItem >&
      sciences() const;
  inline ::google::protobuf::RepeatedPtrField< ::ScienceConfig::ScienceItem >*
      mutable_sciences();

  // @@protoc_insertion_point(class_scope:ScienceConfig.Science)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::ScienceConfig::ScienceItem > sciences_;
  friend void  protobuf_AddDesc_ScienceConfig_2eproto();
  friend void protobuf_AssignDesc_ScienceConfig_2eproto();
  friend void protobuf_ShutdownFile_ScienceConfig_2eproto();

  void InitAsDefaultInstance();
  static Science* default_instance_;
};
// ===================================================================


// ===================================================================

// ScienceItem

// required uint32 id = 1;
inline bool ScienceItem::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ScienceItem::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ScienceItem::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ScienceItem::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 ScienceItem::id() const {
  // @@protoc_insertion_point(field_get:ScienceConfig.ScienceItem.id)
  return id_;
}
inline void ScienceItem::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:ScienceConfig.ScienceItem.id)
}

// required uint32 pass = 2;
inline bool ScienceItem::has_pass() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ScienceItem::set_has_pass() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ScienceItem::clear_has_pass() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ScienceItem::clear_pass() {
  pass_ = 0u;
  clear_has_pass();
}
inline ::google::protobuf::uint32 ScienceItem::pass() const {
  // @@protoc_insertion_point(field_get:ScienceConfig.ScienceItem.pass)
  return pass_;
}
inline void ScienceItem::set_pass(::google::protobuf::uint32 value) {
  set_has_pass();
  pass_ = value;
  // @@protoc_insertion_point(field_set:ScienceConfig.ScienceItem.pass)
}

// required uint32 type = 3;
inline bool ScienceItem::has_type() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ScienceItem::set_has_type() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ScienceItem::clear_has_type() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ScienceItem::clear_type() {
  type_ = 0u;
  clear_has_type();
}
inline ::google::protobuf::uint32 ScienceItem::type() const {
  // @@protoc_insertion_point(field_get:ScienceConfig.ScienceItem.type)
  return type_;
}
inline void ScienceItem::set_type(::google::protobuf::uint32 value) {
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:ScienceConfig.ScienceItem.type)
}

// required uint32 val = 4;
inline bool ScienceItem::has_val() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ScienceItem::set_has_val() {
  _has_bits_[0] |= 0x00000008u;
}
inline void ScienceItem::clear_has_val() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void ScienceItem::clear_val() {
  val_ = 0u;
  clear_has_val();
}
inline ::google::protobuf::uint32 ScienceItem::val() const {
  // @@protoc_insertion_point(field_get:ScienceConfig.ScienceItem.val)
  return val_;
}
inline void ScienceItem::set_val(::google::protobuf::uint32 value) {
  set_has_val();
  val_ = value;
  // @@protoc_insertion_point(field_set:ScienceConfig.ScienceItem.val)
}

// required uint32 cd = 5;
inline bool ScienceItem::has_cd() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void ScienceItem::set_has_cd() {
  _has_bits_[0] |= 0x00000010u;
}
inline void ScienceItem::clear_has_cd() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void ScienceItem::clear_cd() {
  cd_ = 0u;
  clear_has_cd();
}
inline ::google::protobuf::uint32 ScienceItem::cd() const {
  // @@protoc_insertion_point(field_get:ScienceConfig.ScienceItem.cd)
  return cd_;
}
inline void ScienceItem::set_cd(::google::protobuf::uint32 value) {
  set_has_cd();
  cd_ = value;
  // @@protoc_insertion_point(field_set:ScienceConfig.ScienceItem.cd)
}

// required uint32 cost_coins = 6;
inline bool ScienceItem::has_cost_coins() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void ScienceItem::set_has_cost_coins() {
  _has_bits_[0] |= 0x00000020u;
}
inline void ScienceItem::clear_has_cost_coins() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void ScienceItem::clear_cost_coins() {
  cost_coins_ = 0u;
  clear_has_cost_coins();
}
inline ::google::protobuf::uint32 ScienceItem::cost_coins() const {
  // @@protoc_insertion_point(field_get:ScienceConfig.ScienceItem.cost_coins)
  return cost_coins_;
}
inline void ScienceItem::set_cost_coins(::google::protobuf::uint32 value) {
  set_has_cost_coins();
  cost_coins_ = value;
  // @@protoc_insertion_point(field_set:ScienceConfig.ScienceItem.cost_coins)
}

// required uint32 cost_food = 7;
inline bool ScienceItem::has_cost_food() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void ScienceItem::set_has_cost_food() {
  _has_bits_[0] |= 0x00000040u;
}
inline void ScienceItem::clear_has_cost_food() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void ScienceItem::clear_cost_food() {
  cost_food_ = 0u;
  clear_has_cost_food();
}
inline ::google::protobuf::uint32 ScienceItem::cost_food() const {
  // @@protoc_insertion_point(field_get:ScienceConfig.ScienceItem.cost_food)
  return cost_food_;
}
inline void ScienceItem::set_cost_food(::google::protobuf::uint32 value) {
  set_has_cost_food();
  cost_food_ = value;
  // @@protoc_insertion_point(field_set:ScienceConfig.ScienceItem.cost_food)
}

// required uint32 cost_wood = 8;
inline bool ScienceItem::has_cost_wood() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void ScienceItem::set_has_cost_wood() {
  _has_bits_[0] |= 0x00000080u;
}
inline void ScienceItem::clear_has_cost_wood() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void ScienceItem::clear_cost_wood() {
  cost_wood_ = 0u;
  clear_has_cost_wood();
}
inline ::google::protobuf::uint32 ScienceItem::cost_wood() const {
  // @@protoc_insertion_point(field_get:ScienceConfig.ScienceItem.cost_wood)
  return cost_wood_;
}
inline void ScienceItem::set_cost_wood(::google::protobuf::uint32 value) {
  set_has_cost_wood();
  cost_wood_ = value;
  // @@protoc_insertion_point(field_set:ScienceConfig.ScienceItem.cost_wood)
}

// required uint32 cost_iron = 9;
inline bool ScienceItem::has_cost_iron() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void ScienceItem::set_has_cost_iron() {
  _has_bits_[0] |= 0x00000100u;
}
inline void ScienceItem::clear_has_cost_iron() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void ScienceItem::clear_cost_iron() {
  cost_iron_ = 0u;
  clear_has_cost_iron();
}
inline ::google::protobuf::uint32 ScienceItem::cost_iron() const {
  // @@protoc_insertion_point(field_get:ScienceConfig.ScienceItem.cost_iron)
  return cost_iron_;
}
inline void ScienceItem::set_cost_iron(::google::protobuf::uint32 value) {
  set_has_cost_iron();
  cost_iron_ = value;
  // @@protoc_insertion_point(field_set:ScienceConfig.ScienceItem.cost_iron)
}

// required uint32 capital_cnt = 10;
inline bool ScienceItem::has_capital_cnt() const {
  return (_has_bits_[0] & 0x00000200u) != 0;
}
inline void ScienceItem::set_has_capital_cnt() {
  _has_bits_[0] |= 0x00000200u;
}
inline void ScienceItem::clear_has_capital_cnt() {
  _has_bits_[0] &= ~0x00000200u;
}
inline void ScienceItem::clear_capital_cnt() {
  capital_cnt_ = 0u;
  clear_has_capital_cnt();
}
inline ::google::protobuf::uint32 ScienceItem::capital_cnt() const {
  // @@protoc_insertion_point(field_get:ScienceConfig.ScienceItem.capital_cnt)
  return capital_cnt_;
}
inline void ScienceItem::set_capital_cnt(::google::protobuf::uint32 value) {
  set_has_capital_cnt();
  capital_cnt_ = value;
  // @@protoc_insertion_point(field_set:ScienceConfig.ScienceItem.capital_cnt)
}

// required uint32 pre_lock_id = 11;
inline bool ScienceItem::has_pre_lock_id() const {
  return (_has_bits_[0] & 0x00000400u) != 0;
}
inline void ScienceItem::set_has_pre_lock_id() {
  _has_bits_[0] |= 0x00000400u;
}
inline void ScienceItem::clear_has_pre_lock_id() {
  _has_bits_[0] &= ~0x00000400u;
}
inline void ScienceItem::clear_pre_lock_id() {
  pre_lock_id_ = 0u;
  clear_has_pre_lock_id();
}
inline ::google::protobuf::uint32 ScienceItem::pre_lock_id() const {
  // @@protoc_insertion_point(field_get:ScienceConfig.ScienceItem.pre_lock_id)
  return pre_lock_id_;
}
inline void ScienceItem::set_pre_lock_id(::google::protobuf::uint32 value) {
  set_has_pre_lock_id();
  pre_lock_id_ = value;
  // @@protoc_insertion_point(field_set:ScienceConfig.ScienceItem.pre_lock_id)
}

// required uint32 speed_cash = 12;
inline bool ScienceItem::has_speed_cash() const {
  return (_has_bits_[0] & 0x00000800u) != 0;
}
inline void ScienceItem::set_has_speed_cash() {
  _has_bits_[0] |= 0x00000800u;
}
inline void ScienceItem::clear_has_speed_cash() {
  _has_bits_[0] &= ~0x00000800u;
}
inline void ScienceItem::clear_speed_cash() {
  speed_cash_ = 0u;
  clear_has_speed_cash();
}
inline ::google::protobuf::uint32 ScienceItem::speed_cash() const {
  // @@protoc_insertion_point(field_get:ScienceConfig.ScienceItem.speed_cash)
  return speed_cash_;
}
inline void ScienceItem::set_speed_cash(::google::protobuf::uint32 value) {
  set_has_speed_cash();
  speed_cash_ = value;
  // @@protoc_insertion_point(field_set:ScienceConfig.ScienceItem.speed_cash)
}

// -------------------------------------------------------------------

// Science

// repeated .ScienceConfig.ScienceItem sciences = 1;
inline int Science::sciences_size() const {
  return sciences_.size();
}
inline void Science::clear_sciences() {
  sciences_.Clear();
}
inline const ::ScienceConfig::ScienceItem& Science::sciences(int index) const {
  // @@protoc_insertion_point(field_get:ScienceConfig.Science.sciences)
  return sciences_.Get(index);
}
inline ::ScienceConfig::ScienceItem* Science::mutable_sciences(int index) {
  // @@protoc_insertion_point(field_mutable:ScienceConfig.Science.sciences)
  return sciences_.Mutable(index);
}
inline ::ScienceConfig::ScienceItem* Science::add_sciences() {
  // @@protoc_insertion_point(field_add:ScienceConfig.Science.sciences)
  return sciences_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ScienceConfig::ScienceItem >&
Science::sciences() const {
  // @@protoc_insertion_point(field_list:ScienceConfig.Science.sciences)
  return sciences_;
}
inline ::google::protobuf::RepeatedPtrField< ::ScienceConfig::ScienceItem >*
Science::mutable_sciences() {
  // @@protoc_insertion_point(field_mutable_list:ScienceConfig.Science.sciences)
  return &sciences_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ScienceConfig

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ScienceConfig_2eproto__INCLUDED
