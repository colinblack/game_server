// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CommonGiftConfig.proto

#ifndef PROTOBUF_CommonGiftConfig_2eproto__INCLUDED
#define PROTOBUF_CommonGiftConfig_2eproto__INCLUDED

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
// @@protoc_insertion_point(includes)

namespace CommonGiftConfig {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_CommonGiftConfig_2eproto();
void protobuf_AssignDesc_CommonGiftConfig_2eproto();
void protobuf_ShutdownFile_CommonGiftConfig_2eproto();

class BaseItem;
class PropsItem;
class CardsItem;
class CommonModifyItem;

// ===================================================================

class BaseItem : public ::google::protobuf::Message {
 public:
  BaseItem();
  virtual ~BaseItem();
  
  BaseItem(const BaseItem& from);
  
  inline BaseItem& operator=(const BaseItem& from) {
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
  static const BaseItem& default_instance();
  
  void Swap(BaseItem* other);
  
  // implements Message ----------------------------------------------
  
  BaseItem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BaseItem& from);
  void MergeFrom(const BaseItem& from);
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
  
  // optional int32 coin = 1;
  inline bool has_coin() const;
  inline void clear_coin();
  static const int kCoinFieldNumber = 1;
  inline ::google::protobuf::int32 coin() const;
  inline void set_coin(::google::protobuf::int32 value);
  
  // optional int32 cash = 2;
  inline bool has_cash() const;
  inline void clear_cash();
  static const int kCashFieldNumber = 2;
  inline ::google::protobuf::int32 cash() const;
  inline void set_cash(::google::protobuf::int32 value);
  
  // optional int32 exp = 3;
  inline bool has_exp() const;
  inline void clear_exp();
  static const int kExpFieldNumber = 3;
  inline ::google::protobuf::int32 exp() const;
  inline void set_exp(::google::protobuf::int32 value);
  
  // optional int32 power = 4;
  inline bool has_power() const;
  inline void clear_power();
  static const int kPowerFieldNumber = 4;
  inline ::google::protobuf::int32 power() const;
  inline void set_power(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:CommonGiftConfig.BaseItem)
 private:
  inline void set_has_coin();
  inline void clear_has_coin();
  inline void set_has_cash();
  inline void clear_has_cash();
  inline void set_has_exp();
  inline void clear_has_exp();
  inline void set_has_power();
  inline void clear_has_power();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 coin_;
  ::google::protobuf::int32 cash_;
  ::google::protobuf::int32 exp_;
  ::google::protobuf::int32 power_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];
  
  friend void  protobuf_AddDesc_CommonGiftConfig_2eproto();
  friend void protobuf_AssignDesc_CommonGiftConfig_2eproto();
  friend void protobuf_ShutdownFile_CommonGiftConfig_2eproto();
  
  void InitAsDefaultInstance();
  static BaseItem* default_instance_;
};
// -------------------------------------------------------------------

class PropsItem : public ::google::protobuf::Message {
 public:
  PropsItem();
  virtual ~PropsItem();
  
  PropsItem(const PropsItem& from);
  
  inline PropsItem& operator=(const PropsItem& from) {
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
  static const PropsItem& default_instance();
  
  void Swap(PropsItem* other);
  
  // implements Message ----------------------------------------------
  
  PropsItem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PropsItem& from);
  void MergeFrom(const PropsItem& from);
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
  
  // required int32 count = 2;
  inline bool has_count() const;
  inline void clear_count();
  static const int kCountFieldNumber = 2;
  inline ::google::protobuf::int32 count() const;
  inline void set_count(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:CommonGiftConfig.PropsItem)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_count();
  inline void clear_has_count();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint32 id_;
  ::google::protobuf::int32 count_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_CommonGiftConfig_2eproto();
  friend void protobuf_AssignDesc_CommonGiftConfig_2eproto();
  friend void protobuf_ShutdownFile_CommonGiftConfig_2eproto();
  
  void InitAsDefaultInstance();
  static PropsItem* default_instance_;
};
// -------------------------------------------------------------------

class CardsItem : public ::google::protobuf::Message {
 public:
  CardsItem();
  virtual ~CardsItem();
  
  CardsItem(const CardsItem& from);
  
  inline CardsItem& operator=(const CardsItem& from) {
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
  static const CardsItem& default_instance();
  
  void Swap(CardsItem* other);
  
  // implements Message ----------------------------------------------
  
  CardsItem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CardsItem& from);
  void MergeFrom(const CardsItem& from);
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
  
  // required uint32 star = 2;
  inline bool has_star() const;
  inline void clear_star();
  static const int kStarFieldNumber = 2;
  inline ::google::protobuf::uint32 star() const;
  inline void set_star(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:CommonGiftConfig.CardsItem)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_star();
  inline void clear_has_star();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 star_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_CommonGiftConfig_2eproto();
  friend void protobuf_AssignDesc_CommonGiftConfig_2eproto();
  friend void protobuf_ShutdownFile_CommonGiftConfig_2eproto();
  
  void InitAsDefaultInstance();
  static CardsItem* default_instance_;
};
// -------------------------------------------------------------------

class CommonModifyItem : public ::google::protobuf::Message {
 public:
  CommonModifyItem();
  virtual ~CommonModifyItem();
  
  CommonModifyItem(const CommonModifyItem& from);
  
  inline CommonModifyItem& operator=(const CommonModifyItem& from) {
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
  static const CommonModifyItem& default_instance();
  
  void Swap(CommonModifyItem* other);
  
  // implements Message ----------------------------------------------
  
  CommonModifyItem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CommonModifyItem& from);
  void MergeFrom(const CommonModifyItem& from);
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
  
  // optional .CommonGiftConfig.BaseItem based = 1;
  inline bool has_based() const;
  inline void clear_based();
  static const int kBasedFieldNumber = 1;
  inline const ::CommonGiftConfig::BaseItem& based() const;
  inline ::CommonGiftConfig::BaseItem* mutable_based();
  inline ::CommonGiftConfig::BaseItem* release_based();
  
  // repeated .CommonGiftConfig.PropsItem props = 2;
  inline int props_size() const;
  inline void clear_props();
  static const int kPropsFieldNumber = 2;
  inline const ::CommonGiftConfig::PropsItem& props(int index) const;
  inline ::CommonGiftConfig::PropsItem* mutable_props(int index);
  inline ::CommonGiftConfig::PropsItem* add_props();
  inline const ::google::protobuf::RepeatedPtrField< ::CommonGiftConfig::PropsItem >&
      props() const;
  inline ::google::protobuf::RepeatedPtrField< ::CommonGiftConfig::PropsItem >*
      mutable_props();
  
  // repeated .CommonGiftConfig.CardsItem cards = 3;
  inline int cards_size() const;
  inline void clear_cards();
  static const int kCardsFieldNumber = 3;
  inline const ::CommonGiftConfig::CardsItem& cards(int index) const;
  inline ::CommonGiftConfig::CardsItem* mutable_cards(int index);
  inline ::CommonGiftConfig::CardsItem* add_cards();
  inline const ::google::protobuf::RepeatedPtrField< ::CommonGiftConfig::CardsItem >&
      cards() const;
  inline ::google::protobuf::RepeatedPtrField< ::CommonGiftConfig::CardsItem >*
      mutable_cards();
  
  // @@protoc_insertion_point(class_scope:CommonGiftConfig.CommonModifyItem)
 private:
  inline void set_has_based();
  inline void clear_has_based();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::CommonGiftConfig::BaseItem* based_;
  ::google::protobuf::RepeatedPtrField< ::CommonGiftConfig::PropsItem > props_;
  ::google::protobuf::RepeatedPtrField< ::CommonGiftConfig::CardsItem > cards_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_CommonGiftConfig_2eproto();
  friend void protobuf_AssignDesc_CommonGiftConfig_2eproto();
  friend void protobuf_ShutdownFile_CommonGiftConfig_2eproto();
  
  void InitAsDefaultInstance();
  static CommonModifyItem* default_instance_;
};
// ===================================================================


// ===================================================================

// BaseItem

// optional int32 coin = 1;
inline bool BaseItem::has_coin() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void BaseItem::set_has_coin() {
  _has_bits_[0] |= 0x00000001u;
}
inline void BaseItem::clear_has_coin() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void BaseItem::clear_coin() {
  coin_ = 0;
  clear_has_coin();
}
inline ::google::protobuf::int32 BaseItem::coin() const {
  return coin_;
}
inline void BaseItem::set_coin(::google::protobuf::int32 value) {
  set_has_coin();
  coin_ = value;
}

// optional int32 cash = 2;
inline bool BaseItem::has_cash() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void BaseItem::set_has_cash() {
  _has_bits_[0] |= 0x00000002u;
}
inline void BaseItem::clear_has_cash() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void BaseItem::clear_cash() {
  cash_ = 0;
  clear_has_cash();
}
inline ::google::protobuf::int32 BaseItem::cash() const {
  return cash_;
}
inline void BaseItem::set_cash(::google::protobuf::int32 value) {
  set_has_cash();
  cash_ = value;
}

// optional int32 exp = 3;
inline bool BaseItem::has_exp() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void BaseItem::set_has_exp() {
  _has_bits_[0] |= 0x00000004u;
}
inline void BaseItem::clear_has_exp() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void BaseItem::clear_exp() {
  exp_ = 0;
  clear_has_exp();
}
inline ::google::protobuf::int32 BaseItem::exp() const {
  return exp_;
}
inline void BaseItem::set_exp(::google::protobuf::int32 value) {
  set_has_exp();
  exp_ = value;
}

// optional int32 power = 4;
inline bool BaseItem::has_power() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void BaseItem::set_has_power() {
  _has_bits_[0] |= 0x00000008u;
}
inline void BaseItem::clear_has_power() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void BaseItem::clear_power() {
  power_ = 0;
  clear_has_power();
}
inline ::google::protobuf::int32 BaseItem::power() const {
  return power_;
}
inline void BaseItem::set_power(::google::protobuf::int32 value) {
  set_has_power();
  power_ = value;
}

// -------------------------------------------------------------------

// PropsItem

// required uint32 id = 1;
inline bool PropsItem::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PropsItem::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PropsItem::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PropsItem::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 PropsItem::id() const {
  return id_;
}
inline void PropsItem::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// required int32 count = 2;
inline bool PropsItem::has_count() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void PropsItem::set_has_count() {
  _has_bits_[0] |= 0x00000002u;
}
inline void PropsItem::clear_has_count() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void PropsItem::clear_count() {
  count_ = 0;
  clear_has_count();
}
inline ::google::protobuf::int32 PropsItem::count() const {
  return count_;
}
inline void PropsItem::set_count(::google::protobuf::int32 value) {
  set_has_count();
  count_ = value;
}

// -------------------------------------------------------------------

// CardsItem

// required uint32 id = 1;
inline bool CardsItem::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CardsItem::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CardsItem::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void CardsItem::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 CardsItem::id() const {
  return id_;
}
inline void CardsItem::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// required uint32 star = 2;
inline bool CardsItem::has_star() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void CardsItem::set_has_star() {
  _has_bits_[0] |= 0x00000002u;
}
inline void CardsItem::clear_has_star() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void CardsItem::clear_star() {
  star_ = 0u;
  clear_has_star();
}
inline ::google::protobuf::uint32 CardsItem::star() const {
  return star_;
}
inline void CardsItem::set_star(::google::protobuf::uint32 value) {
  set_has_star();
  star_ = value;
}

// -------------------------------------------------------------------

// CommonModifyItem

// optional .CommonGiftConfig.BaseItem based = 1;
inline bool CommonModifyItem::has_based() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CommonModifyItem::set_has_based() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CommonModifyItem::clear_has_based() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void CommonModifyItem::clear_based() {
  if (based_ != NULL) based_->::CommonGiftConfig::BaseItem::Clear();
  clear_has_based();
}
inline const ::CommonGiftConfig::BaseItem& CommonModifyItem::based() const {
  return based_ != NULL ? *based_ : *default_instance_->based_;
}
inline ::CommonGiftConfig::BaseItem* CommonModifyItem::mutable_based() {
  set_has_based();
  if (based_ == NULL) based_ = new ::CommonGiftConfig::BaseItem;
  return based_;
}
inline ::CommonGiftConfig::BaseItem* CommonModifyItem::release_based() {
  clear_has_based();
  ::CommonGiftConfig::BaseItem* temp = based_;
  based_ = NULL;
  return temp;
}

// repeated .CommonGiftConfig.PropsItem props = 2;
inline int CommonModifyItem::props_size() const {
  return props_.size();
}
inline void CommonModifyItem::clear_props() {
  props_.Clear();
}
inline const ::CommonGiftConfig::PropsItem& CommonModifyItem::props(int index) const {
  return props_.Get(index);
}
inline ::CommonGiftConfig::PropsItem* CommonModifyItem::mutable_props(int index) {
  return props_.Mutable(index);
}
inline ::CommonGiftConfig::PropsItem* CommonModifyItem::add_props() {
  return props_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::CommonGiftConfig::PropsItem >&
CommonModifyItem::props() const {
  return props_;
}
inline ::google::protobuf::RepeatedPtrField< ::CommonGiftConfig::PropsItem >*
CommonModifyItem::mutable_props() {
  return &props_;
}

// repeated .CommonGiftConfig.CardsItem cards = 3;
inline int CommonModifyItem::cards_size() const {
  return cards_.size();
}
inline void CommonModifyItem::clear_cards() {
  cards_.Clear();
}
inline const ::CommonGiftConfig::CardsItem& CommonModifyItem::cards(int index) const {
  return cards_.Get(index);
}
inline ::CommonGiftConfig::CardsItem* CommonModifyItem::mutable_cards(int index) {
  return cards_.Mutable(index);
}
inline ::CommonGiftConfig::CardsItem* CommonModifyItem::add_cards() {
  return cards_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::CommonGiftConfig::CardsItem >&
CommonModifyItem::cards() const {
  return cards_;
}
inline ::google::protobuf::RepeatedPtrField< ::CommonGiftConfig::CardsItem >*
CommonModifyItem::mutable_cards() {
  return &cards_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace CommonGiftConfig

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_CommonGiftConfig_2eproto__INCLUDED
