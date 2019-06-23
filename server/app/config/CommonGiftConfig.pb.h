// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CommonGiftConfig.proto

#ifndef PROTOBUF_CommonGiftConfig_2eproto__INCLUDED
#define PROTOBUF_CommonGiftConfig_2eproto__INCLUDED

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

namespace CommonGiftConfig {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_CommonGiftConfig_2eproto();
void protobuf_AssignDesc_CommonGiftConfig_2eproto();
void protobuf_ShutdownFile_CommonGiftConfig_2eproto();

class BaseReward;

// ===================================================================

class BaseReward : public ::google::protobuf::Message {
 public:
  BaseReward();
  virtual ~BaseReward();

  BaseReward(const BaseReward& from);

  inline BaseReward& operator=(const BaseReward& from) {
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
  static const BaseReward& default_instance();

  void Swap(BaseReward* other);

  // implements Message ----------------------------------------------

  BaseReward* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BaseReward& from);
  void MergeFrom(const BaseReward& from);
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

  // optional uint32 coin = 1;
  inline bool has_coin() const;
  inline void clear_coin();
  static const int kCoinFieldNumber = 1;
  inline ::google::protobuf::uint32 coin() const;
  inline void set_coin(::google::protobuf::uint32 value);

  // optional uint32 wood = 2;
  inline bool has_wood() const;
  inline void clear_wood();
  static const int kWoodFieldNumber = 2;
  inline ::google::protobuf::uint32 wood() const;
  inline void set_wood(::google::protobuf::uint32 value);

  // optional uint32 food = 3;
  inline bool has_food() const;
  inline void clear_food();
  static const int kFoodFieldNumber = 3;
  inline ::google::protobuf::uint32 food() const;
  inline void set_food(::google::protobuf::uint32 value);

  // optional uint32 iron = 4;
  inline bool has_iron() const;
  inline void clear_iron();
  static const int kIronFieldNumber = 4;
  inline ::google::protobuf::uint32 iron() const;
  inline void set_iron(::google::protobuf::uint32 value);

  // optional uint32 hammer = 5;
  inline bool has_hammer() const;
  inline void clear_hammer();
  static const int kHammerFieldNumber = 5;
  inline ::google::protobuf::uint32 hammer() const;
  inline void set_hammer(::google::protobuf::uint32 value);

  // optional uint32 order = 6;
  inline bool has_order() const;
  inline void clear_order();
  static const int kOrderFieldNumber = 6;
  inline ::google::protobuf::uint32 order() const;
  inline void set_order(::google::protobuf::uint32 value);

  // optional uint32 exp = 7;
  inline bool has_exp() const;
  inline void clear_exp();
  static const int kExpFieldNumber = 7;
  inline ::google::protobuf::uint32 exp() const;
  inline void set_exp(::google::protobuf::uint32 value);

  // optional uint32 cash = 8;
  inline bool has_cash() const;
  inline void clear_cash();
  static const int kCashFieldNumber = 8;
  inline ::google::protobuf::uint32 cash() const;
  inline void set_cash(::google::protobuf::uint32 value);

  // optional uint32 refresh = 9;
  inline bool has_refresh() const;
  inline void clear_refresh();
  static const int kRefreshFieldNumber = 9;
  inline ::google::protobuf::uint32 refresh() const;
  inline void set_refresh(::google::protobuf::uint32 value);

  // optional uint32 arefresh = 10;
  inline bool has_arefresh() const;
  inline void clear_arefresh();
  static const int kArefreshFieldNumber = 10;
  inline ::google::protobuf::uint32 arefresh() const;
  inline void set_arefresh(::google::protobuf::uint32 value);

  // optional uint32 sacrifice = 11;
  inline bool has_sacrifice() const;
  inline void clear_sacrifice();
  static const int kSacrificeFieldNumber = 11;
  inline ::google::protobuf::uint32 sacrifice() const;
  inline void set_sacrifice(::google::protobuf::uint32 value);

  // optional uint32 market = 12;
  inline bool has_market() const;
  inline void clear_market();
  static const int kMarketFieldNumber = 12;
  inline ::google::protobuf::uint32 market() const;
  inline void set_market(::google::protobuf::uint32 value);

  // optional uint32 shadow = 13;
  inline bool has_shadow() const;
  inline void clear_shadow();
  static const int kShadowFieldNumber = 13;
  inline ::google::protobuf::uint32 shadow() const;
  inline void set_shadow(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:CommonGiftConfig.BaseReward)
 private:
  inline void set_has_coin();
  inline void clear_has_coin();
  inline void set_has_wood();
  inline void clear_has_wood();
  inline void set_has_food();
  inline void clear_has_food();
  inline void set_has_iron();
  inline void clear_has_iron();
  inline void set_has_hammer();
  inline void clear_has_hammer();
  inline void set_has_order();
  inline void clear_has_order();
  inline void set_has_exp();
  inline void clear_has_exp();
  inline void set_has_cash();
  inline void clear_has_cash();
  inline void set_has_refresh();
  inline void clear_has_refresh();
  inline void set_has_arefresh();
  inline void clear_has_arefresh();
  inline void set_has_sacrifice();
  inline void clear_has_sacrifice();
  inline void set_has_market();
  inline void clear_has_market();
  inline void set_has_shadow();
  inline void clear_has_shadow();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 coin_;
  ::google::protobuf::uint32 wood_;
  ::google::protobuf::uint32 food_;
  ::google::protobuf::uint32 iron_;
  ::google::protobuf::uint32 hammer_;
  ::google::protobuf::uint32 order_;
  ::google::protobuf::uint32 exp_;
  ::google::protobuf::uint32 cash_;
  ::google::protobuf::uint32 refresh_;
  ::google::protobuf::uint32 arefresh_;
  ::google::protobuf::uint32 sacrifice_;
  ::google::protobuf::uint32 market_;
  ::google::protobuf::uint32 shadow_;
  friend void  protobuf_AddDesc_CommonGiftConfig_2eproto();
  friend void protobuf_AssignDesc_CommonGiftConfig_2eproto();
  friend void protobuf_ShutdownFile_CommonGiftConfig_2eproto();

  void InitAsDefaultInstance();
  static BaseReward* default_instance_;
};
// ===================================================================


// ===================================================================

// BaseReward

// optional uint32 coin = 1;
inline bool BaseReward::has_coin() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void BaseReward::set_has_coin() {
  _has_bits_[0] |= 0x00000001u;
}
inline void BaseReward::clear_has_coin() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void BaseReward::clear_coin() {
  coin_ = 0u;
  clear_has_coin();
}
inline ::google::protobuf::uint32 BaseReward::coin() const {
  // @@protoc_insertion_point(field_get:CommonGiftConfig.BaseReward.coin)
  return coin_;
}
inline void BaseReward::set_coin(::google::protobuf::uint32 value) {
  set_has_coin();
  coin_ = value;
  // @@protoc_insertion_point(field_set:CommonGiftConfig.BaseReward.coin)
}

// optional uint32 wood = 2;
inline bool BaseReward::has_wood() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void BaseReward::set_has_wood() {
  _has_bits_[0] |= 0x00000002u;
}
inline void BaseReward::clear_has_wood() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void BaseReward::clear_wood() {
  wood_ = 0u;
  clear_has_wood();
}
inline ::google::protobuf::uint32 BaseReward::wood() const {
  // @@protoc_insertion_point(field_get:CommonGiftConfig.BaseReward.wood)
  return wood_;
}
inline void BaseReward::set_wood(::google::protobuf::uint32 value) {
  set_has_wood();
  wood_ = value;
  // @@protoc_insertion_point(field_set:CommonGiftConfig.BaseReward.wood)
}

// optional uint32 food = 3;
inline bool BaseReward::has_food() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void BaseReward::set_has_food() {
  _has_bits_[0] |= 0x00000004u;
}
inline void BaseReward::clear_has_food() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void BaseReward::clear_food() {
  food_ = 0u;
  clear_has_food();
}
inline ::google::protobuf::uint32 BaseReward::food() const {
  // @@protoc_insertion_point(field_get:CommonGiftConfig.BaseReward.food)
  return food_;
}
inline void BaseReward::set_food(::google::protobuf::uint32 value) {
  set_has_food();
  food_ = value;
  // @@protoc_insertion_point(field_set:CommonGiftConfig.BaseReward.food)
}

// optional uint32 iron = 4;
inline bool BaseReward::has_iron() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void BaseReward::set_has_iron() {
  _has_bits_[0] |= 0x00000008u;
}
inline void BaseReward::clear_has_iron() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void BaseReward::clear_iron() {
  iron_ = 0u;
  clear_has_iron();
}
inline ::google::protobuf::uint32 BaseReward::iron() const {
  // @@protoc_insertion_point(field_get:CommonGiftConfig.BaseReward.iron)
  return iron_;
}
inline void BaseReward::set_iron(::google::protobuf::uint32 value) {
  set_has_iron();
  iron_ = value;
  // @@protoc_insertion_point(field_set:CommonGiftConfig.BaseReward.iron)
}

// optional uint32 hammer = 5;
inline bool BaseReward::has_hammer() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void BaseReward::set_has_hammer() {
  _has_bits_[0] |= 0x00000010u;
}
inline void BaseReward::clear_has_hammer() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void BaseReward::clear_hammer() {
  hammer_ = 0u;
  clear_has_hammer();
}
inline ::google::protobuf::uint32 BaseReward::hammer() const {
  // @@protoc_insertion_point(field_get:CommonGiftConfig.BaseReward.hammer)
  return hammer_;
}
inline void BaseReward::set_hammer(::google::protobuf::uint32 value) {
  set_has_hammer();
  hammer_ = value;
  // @@protoc_insertion_point(field_set:CommonGiftConfig.BaseReward.hammer)
}

// optional uint32 order = 6;
inline bool BaseReward::has_order() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void BaseReward::set_has_order() {
  _has_bits_[0] |= 0x00000020u;
}
inline void BaseReward::clear_has_order() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void BaseReward::clear_order() {
  order_ = 0u;
  clear_has_order();
}
inline ::google::protobuf::uint32 BaseReward::order() const {
  // @@protoc_insertion_point(field_get:CommonGiftConfig.BaseReward.order)
  return order_;
}
inline void BaseReward::set_order(::google::protobuf::uint32 value) {
  set_has_order();
  order_ = value;
  // @@protoc_insertion_point(field_set:CommonGiftConfig.BaseReward.order)
}

// optional uint32 exp = 7;
inline bool BaseReward::has_exp() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void BaseReward::set_has_exp() {
  _has_bits_[0] |= 0x00000040u;
}
inline void BaseReward::clear_has_exp() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void BaseReward::clear_exp() {
  exp_ = 0u;
  clear_has_exp();
}
inline ::google::protobuf::uint32 BaseReward::exp() const {
  // @@protoc_insertion_point(field_get:CommonGiftConfig.BaseReward.exp)
  return exp_;
}
inline void BaseReward::set_exp(::google::protobuf::uint32 value) {
  set_has_exp();
  exp_ = value;
  // @@protoc_insertion_point(field_set:CommonGiftConfig.BaseReward.exp)
}

// optional uint32 cash = 8;
inline bool BaseReward::has_cash() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void BaseReward::set_has_cash() {
  _has_bits_[0] |= 0x00000080u;
}
inline void BaseReward::clear_has_cash() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void BaseReward::clear_cash() {
  cash_ = 0u;
  clear_has_cash();
}
inline ::google::protobuf::uint32 BaseReward::cash() const {
  // @@protoc_insertion_point(field_get:CommonGiftConfig.BaseReward.cash)
  return cash_;
}
inline void BaseReward::set_cash(::google::protobuf::uint32 value) {
  set_has_cash();
  cash_ = value;
  // @@protoc_insertion_point(field_set:CommonGiftConfig.BaseReward.cash)
}

// optional uint32 refresh = 9;
inline bool BaseReward::has_refresh() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void BaseReward::set_has_refresh() {
  _has_bits_[0] |= 0x00000100u;
}
inline void BaseReward::clear_has_refresh() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void BaseReward::clear_refresh() {
  refresh_ = 0u;
  clear_has_refresh();
}
inline ::google::protobuf::uint32 BaseReward::refresh() const {
  // @@protoc_insertion_point(field_get:CommonGiftConfig.BaseReward.refresh)
  return refresh_;
}
inline void BaseReward::set_refresh(::google::protobuf::uint32 value) {
  set_has_refresh();
  refresh_ = value;
  // @@protoc_insertion_point(field_set:CommonGiftConfig.BaseReward.refresh)
}

// optional uint32 arefresh = 10;
inline bool BaseReward::has_arefresh() const {
  return (_has_bits_[0] & 0x00000200u) != 0;
}
inline void BaseReward::set_has_arefresh() {
  _has_bits_[0] |= 0x00000200u;
}
inline void BaseReward::clear_has_arefresh() {
  _has_bits_[0] &= ~0x00000200u;
}
inline void BaseReward::clear_arefresh() {
  arefresh_ = 0u;
  clear_has_arefresh();
}
inline ::google::protobuf::uint32 BaseReward::arefresh() const {
  // @@protoc_insertion_point(field_get:CommonGiftConfig.BaseReward.arefresh)
  return arefresh_;
}
inline void BaseReward::set_arefresh(::google::protobuf::uint32 value) {
  set_has_arefresh();
  arefresh_ = value;
  // @@protoc_insertion_point(field_set:CommonGiftConfig.BaseReward.arefresh)
}

// optional uint32 sacrifice = 11;
inline bool BaseReward::has_sacrifice() const {
  return (_has_bits_[0] & 0x00000400u) != 0;
}
inline void BaseReward::set_has_sacrifice() {
  _has_bits_[0] |= 0x00000400u;
}
inline void BaseReward::clear_has_sacrifice() {
  _has_bits_[0] &= ~0x00000400u;
}
inline void BaseReward::clear_sacrifice() {
  sacrifice_ = 0u;
  clear_has_sacrifice();
}
inline ::google::protobuf::uint32 BaseReward::sacrifice() const {
  // @@protoc_insertion_point(field_get:CommonGiftConfig.BaseReward.sacrifice)
  return sacrifice_;
}
inline void BaseReward::set_sacrifice(::google::protobuf::uint32 value) {
  set_has_sacrifice();
  sacrifice_ = value;
  // @@protoc_insertion_point(field_set:CommonGiftConfig.BaseReward.sacrifice)
}

// optional uint32 market = 12;
inline bool BaseReward::has_market() const {
  return (_has_bits_[0] & 0x00000800u) != 0;
}
inline void BaseReward::set_has_market() {
  _has_bits_[0] |= 0x00000800u;
}
inline void BaseReward::clear_has_market() {
  _has_bits_[0] &= ~0x00000800u;
}
inline void BaseReward::clear_market() {
  market_ = 0u;
  clear_has_market();
}
inline ::google::protobuf::uint32 BaseReward::market() const {
  // @@protoc_insertion_point(field_get:CommonGiftConfig.BaseReward.market)
  return market_;
}
inline void BaseReward::set_market(::google::protobuf::uint32 value) {
  set_has_market();
  market_ = value;
  // @@protoc_insertion_point(field_set:CommonGiftConfig.BaseReward.market)
}

// optional uint32 shadow = 13;
inline bool BaseReward::has_shadow() const {
  return (_has_bits_[0] & 0x00001000u) != 0;
}
inline void BaseReward::set_has_shadow() {
  _has_bits_[0] |= 0x00001000u;
}
inline void BaseReward::clear_has_shadow() {
  _has_bits_[0] &= ~0x00001000u;
}
inline void BaseReward::clear_shadow() {
  shadow_ = 0u;
  clear_has_shadow();
}
inline ::google::protobuf::uint32 BaseReward::shadow() const {
  // @@protoc_insertion_point(field_get:CommonGiftConfig.BaseReward.shadow)
  return shadow_;
}
inline void BaseReward::set_shadow(::google::protobuf::uint32 value) {
  set_has_shadow();
  shadow_ = value;
  // @@protoc_insertion_point(field_set:CommonGiftConfig.BaseReward.shadow)
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