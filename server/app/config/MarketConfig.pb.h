// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MarketConfig.proto

#ifndef PROTOBUF_MarketConfig_2eproto__INCLUDED
#define PROTOBUF_MarketConfig_2eproto__INCLUDED

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

namespace MarketConfig {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_MarketConfig_2eproto();
void protobuf_AssignDesc_MarketConfig_2eproto();
void protobuf_ShutdownFile_MarketConfig_2eproto();

class MarketItem;
class BlackMarketItem;
class MarketAll;

// ===================================================================

class MarketItem : public ::google::protobuf::Message {
 public:
  MarketItem();
  virtual ~MarketItem();

  MarketItem(const MarketItem& from);

  inline MarketItem& operator=(const MarketItem& from) {
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
  static const MarketItem& default_instance();

  void Swap(MarketItem* other);

  // implements Message ----------------------------------------------

  MarketItem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MarketItem& from);
  void MergeFrom(const MarketItem& from);
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

  // required uint32 type = 1;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline ::google::protobuf::uint32 type() const;
  inline void set_type(::google::protobuf::uint32 value);

  // required uint32 price = 2;
  inline bool has_price() const;
  inline void clear_price();
  static const int kPriceFieldNumber = 2;
  inline ::google::protobuf::uint32 price() const;
  inline void set_price(::google::protobuf::uint32 value);

  // repeated uint32 reward = 3;
  inline int reward_size() const;
  inline void clear_reward();
  static const int kRewardFieldNumber = 3;
  inline ::google::protobuf::uint32 reward(int index) const;
  inline void set_reward(int index, ::google::protobuf::uint32 value);
  inline void add_reward(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      reward() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_reward();

  // @@protoc_insertion_point(class_scope:MarketConfig.MarketItem)
 private:
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_price();
  inline void clear_has_price();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 type_;
  ::google::protobuf::uint32 price_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > reward_;
  friend void  protobuf_AddDesc_MarketConfig_2eproto();
  friend void protobuf_AssignDesc_MarketConfig_2eproto();
  friend void protobuf_ShutdownFile_MarketConfig_2eproto();

  void InitAsDefaultInstance();
  static MarketItem* default_instance_;
};
// -------------------------------------------------------------------

class BlackMarketItem : public ::google::protobuf::Message {
 public:
  BlackMarketItem();
  virtual ~BlackMarketItem();

  BlackMarketItem(const BlackMarketItem& from);

  inline BlackMarketItem& operator=(const BlackMarketItem& from) {
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
  static const BlackMarketItem& default_instance();

  void Swap(BlackMarketItem* other);

  // implements Message ----------------------------------------------

  BlackMarketItem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BlackMarketItem& from);
  void MergeFrom(const BlackMarketItem& from);
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

  // required uint32 clearCdPrice = 1;
  inline bool has_clearcdprice() const;
  inline void clear_clearcdprice();
  static const int kClearCdPriceFieldNumber = 1;
  inline ::google::protobuf::uint32 clearcdprice() const;
  inline void set_clearcdprice(::google::protobuf::uint32 value);

  // repeated uint32 ratio = 2;
  inline int ratio_size() const;
  inline void clear_ratio();
  static const int kRatioFieldNumber = 2;
  inline ::google::protobuf::uint32 ratio(int index) const;
  inline void set_ratio(int index, ::google::protobuf::uint32 value);
  inline void add_ratio(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      ratio() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_ratio();

  // @@protoc_insertion_point(class_scope:MarketConfig.BlackMarketItem)
 private:
  inline void set_has_clearcdprice();
  inline void clear_has_clearcdprice();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > ratio_;
  ::google::protobuf::uint32 clearcdprice_;
  friend void  protobuf_AddDesc_MarketConfig_2eproto();
  friend void protobuf_AssignDesc_MarketConfig_2eproto();
  friend void protobuf_ShutdownFile_MarketConfig_2eproto();

  void InitAsDefaultInstance();
  static BlackMarketItem* default_instance_;
};
// -------------------------------------------------------------------

class MarketAll : public ::google::protobuf::Message {
 public:
  MarketAll();
  virtual ~MarketAll();

  MarketAll(const MarketAll& from);

  inline MarketAll& operator=(const MarketAll& from) {
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
  static const MarketAll& default_instance();

  void Swap(MarketAll* other);

  // implements Message ----------------------------------------------

  MarketAll* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MarketAll& from);
  void MergeFrom(const MarketAll& from);
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

  // repeated .MarketConfig.MarketItem market = 1;
  inline int market_size() const;
  inline void clear_market();
  static const int kMarketFieldNumber = 1;
  inline const ::MarketConfig::MarketItem& market(int index) const;
  inline ::MarketConfig::MarketItem* mutable_market(int index);
  inline ::MarketConfig::MarketItem* add_market();
  inline const ::google::protobuf::RepeatedPtrField< ::MarketConfig::MarketItem >&
      market() const;
  inline ::google::protobuf::RepeatedPtrField< ::MarketConfig::MarketItem >*
      mutable_market();

  // required .MarketConfig.BlackMarketItem blackmarket = 2;
  inline bool has_blackmarket() const;
  inline void clear_blackmarket();
  static const int kBlackmarketFieldNumber = 2;
  inline const ::MarketConfig::BlackMarketItem& blackmarket() const;
  inline ::MarketConfig::BlackMarketItem* mutable_blackmarket();
  inline ::MarketConfig::BlackMarketItem* release_blackmarket();
  inline void set_allocated_blackmarket(::MarketConfig::BlackMarketItem* blackmarket);

  // @@protoc_insertion_point(class_scope:MarketConfig.MarketAll)
 private:
  inline void set_has_blackmarket();
  inline void clear_has_blackmarket();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::MarketConfig::MarketItem > market_;
  ::MarketConfig::BlackMarketItem* blackmarket_;
  friend void  protobuf_AddDesc_MarketConfig_2eproto();
  friend void protobuf_AssignDesc_MarketConfig_2eproto();
  friend void protobuf_ShutdownFile_MarketConfig_2eproto();

  void InitAsDefaultInstance();
  static MarketAll* default_instance_;
};
// ===================================================================


// ===================================================================

// MarketItem

// required uint32 type = 1;
inline bool MarketItem::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MarketItem::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MarketItem::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MarketItem::clear_type() {
  type_ = 0u;
  clear_has_type();
}
inline ::google::protobuf::uint32 MarketItem::type() const {
  // @@protoc_insertion_point(field_get:MarketConfig.MarketItem.type)
  return type_;
}
inline void MarketItem::set_type(::google::protobuf::uint32 value) {
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:MarketConfig.MarketItem.type)
}

// required uint32 price = 2;
inline bool MarketItem::has_price() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MarketItem::set_has_price() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MarketItem::clear_has_price() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MarketItem::clear_price() {
  price_ = 0u;
  clear_has_price();
}
inline ::google::protobuf::uint32 MarketItem::price() const {
  // @@protoc_insertion_point(field_get:MarketConfig.MarketItem.price)
  return price_;
}
inline void MarketItem::set_price(::google::protobuf::uint32 value) {
  set_has_price();
  price_ = value;
  // @@protoc_insertion_point(field_set:MarketConfig.MarketItem.price)
}

// repeated uint32 reward = 3;
inline int MarketItem::reward_size() const {
  return reward_.size();
}
inline void MarketItem::clear_reward() {
  reward_.Clear();
}
inline ::google::protobuf::uint32 MarketItem::reward(int index) const {
  // @@protoc_insertion_point(field_get:MarketConfig.MarketItem.reward)
  return reward_.Get(index);
}
inline void MarketItem::set_reward(int index, ::google::protobuf::uint32 value) {
  reward_.Set(index, value);
  // @@protoc_insertion_point(field_set:MarketConfig.MarketItem.reward)
}
inline void MarketItem::add_reward(::google::protobuf::uint32 value) {
  reward_.Add(value);
  // @@protoc_insertion_point(field_add:MarketConfig.MarketItem.reward)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
MarketItem::reward() const {
  // @@protoc_insertion_point(field_list:MarketConfig.MarketItem.reward)
  return reward_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
MarketItem::mutable_reward() {
  // @@protoc_insertion_point(field_mutable_list:MarketConfig.MarketItem.reward)
  return &reward_;
}

// -------------------------------------------------------------------

// BlackMarketItem

// required uint32 clearCdPrice = 1;
inline bool BlackMarketItem::has_clearcdprice() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void BlackMarketItem::set_has_clearcdprice() {
  _has_bits_[0] |= 0x00000001u;
}
inline void BlackMarketItem::clear_has_clearcdprice() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void BlackMarketItem::clear_clearcdprice() {
  clearcdprice_ = 0u;
  clear_has_clearcdprice();
}
inline ::google::protobuf::uint32 BlackMarketItem::clearcdprice() const {
  // @@protoc_insertion_point(field_get:MarketConfig.BlackMarketItem.clearCdPrice)
  return clearcdprice_;
}
inline void BlackMarketItem::set_clearcdprice(::google::protobuf::uint32 value) {
  set_has_clearcdprice();
  clearcdprice_ = value;
  // @@protoc_insertion_point(field_set:MarketConfig.BlackMarketItem.clearCdPrice)
}

// repeated uint32 ratio = 2;
inline int BlackMarketItem::ratio_size() const {
  return ratio_.size();
}
inline void BlackMarketItem::clear_ratio() {
  ratio_.Clear();
}
inline ::google::protobuf::uint32 BlackMarketItem::ratio(int index) const {
  // @@protoc_insertion_point(field_get:MarketConfig.BlackMarketItem.ratio)
  return ratio_.Get(index);
}
inline void BlackMarketItem::set_ratio(int index, ::google::protobuf::uint32 value) {
  ratio_.Set(index, value);
  // @@protoc_insertion_point(field_set:MarketConfig.BlackMarketItem.ratio)
}
inline void BlackMarketItem::add_ratio(::google::protobuf::uint32 value) {
  ratio_.Add(value);
  // @@protoc_insertion_point(field_add:MarketConfig.BlackMarketItem.ratio)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
BlackMarketItem::ratio() const {
  // @@protoc_insertion_point(field_list:MarketConfig.BlackMarketItem.ratio)
  return ratio_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
BlackMarketItem::mutable_ratio() {
  // @@protoc_insertion_point(field_mutable_list:MarketConfig.BlackMarketItem.ratio)
  return &ratio_;
}

// -------------------------------------------------------------------

// MarketAll

// repeated .MarketConfig.MarketItem market = 1;
inline int MarketAll::market_size() const {
  return market_.size();
}
inline void MarketAll::clear_market() {
  market_.Clear();
}
inline const ::MarketConfig::MarketItem& MarketAll::market(int index) const {
  // @@protoc_insertion_point(field_get:MarketConfig.MarketAll.market)
  return market_.Get(index);
}
inline ::MarketConfig::MarketItem* MarketAll::mutable_market(int index) {
  // @@protoc_insertion_point(field_mutable:MarketConfig.MarketAll.market)
  return market_.Mutable(index);
}
inline ::MarketConfig::MarketItem* MarketAll::add_market() {
  // @@protoc_insertion_point(field_add:MarketConfig.MarketAll.market)
  return market_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::MarketConfig::MarketItem >&
MarketAll::market() const {
  // @@protoc_insertion_point(field_list:MarketConfig.MarketAll.market)
  return market_;
}
inline ::google::protobuf::RepeatedPtrField< ::MarketConfig::MarketItem >*
MarketAll::mutable_market() {
  // @@protoc_insertion_point(field_mutable_list:MarketConfig.MarketAll.market)
  return &market_;
}

// required .MarketConfig.BlackMarketItem blackmarket = 2;
inline bool MarketAll::has_blackmarket() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MarketAll::set_has_blackmarket() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MarketAll::clear_has_blackmarket() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MarketAll::clear_blackmarket() {
  if (blackmarket_ != NULL) blackmarket_->::MarketConfig::BlackMarketItem::Clear();
  clear_has_blackmarket();
}
inline const ::MarketConfig::BlackMarketItem& MarketAll::blackmarket() const {
  // @@protoc_insertion_point(field_get:MarketConfig.MarketAll.blackmarket)
  return blackmarket_ != NULL ? *blackmarket_ : *default_instance_->blackmarket_;
}
inline ::MarketConfig::BlackMarketItem* MarketAll::mutable_blackmarket() {
  set_has_blackmarket();
  if (blackmarket_ == NULL) blackmarket_ = new ::MarketConfig::BlackMarketItem;
  // @@protoc_insertion_point(field_mutable:MarketConfig.MarketAll.blackmarket)
  return blackmarket_;
}
inline ::MarketConfig::BlackMarketItem* MarketAll::release_blackmarket() {
  clear_has_blackmarket();
  ::MarketConfig::BlackMarketItem* temp = blackmarket_;
  blackmarket_ = NULL;
  return temp;
}
inline void MarketAll::set_allocated_blackmarket(::MarketConfig::BlackMarketItem* blackmarket) {
  delete blackmarket_;
  blackmarket_ = blackmarket;
  if (blackmarket) {
    set_has_blackmarket();
  } else {
    clear_has_blackmarket();
  }
  // @@protoc_insertion_point(field_set_allocated:MarketConfig.MarketAll.blackmarket)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace MarketConfig

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_MarketConfig_2eproto__INCLUDED
