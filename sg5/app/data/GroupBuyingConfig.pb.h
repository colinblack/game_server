// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: GroupBuyingConfig.proto

#ifndef PROTOBUF_GroupBuyingConfig_2eproto__INCLUDED
#define PROTOBUF_GroupBuyingConfig_2eproto__INCLUDED

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
#include "RewardConfig.pb.h"
// @@protoc_insertion_point(includes)

namespace GroupBuyingConfig {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_GroupBuyingConfig_2eproto();
void protobuf_AssignDesc_GroupBuyingConfig_2eproto();
void protobuf_ShutdownFile_GroupBuyingConfig_2eproto();

class CountPrice;
class GroupBuyingItem;
class GroupBuyingItemsCfg;

// ===================================================================

class CountPrice : public ::google::protobuf::Message {
 public:
  CountPrice();
  virtual ~CountPrice();

  CountPrice(const CountPrice& from);

  inline CountPrice& operator=(const CountPrice& from) {
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
  static const CountPrice& default_instance();

  void Swap(CountPrice* other);

  // implements Message ----------------------------------------------

  CountPrice* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CountPrice& from);
  void MergeFrom(const CountPrice& from);
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

  // required uint32 count = 1;
  inline bool has_count() const;
  inline void clear_count();
  static const int kCountFieldNumber = 1;
  inline ::google::protobuf::uint32 count() const;
  inline void set_count(::google::protobuf::uint32 value);

  // required uint32 price = 2;
  inline bool has_price() const;
  inline void clear_price();
  static const int kPriceFieldNumber = 2;
  inline ::google::protobuf::uint32 price() const;
  inline void set_price(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:GroupBuyingConfig.CountPrice)
 private:
  inline void set_has_count();
  inline void clear_has_count();
  inline void set_has_price();
  inline void clear_has_price();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 count_;
  ::google::protobuf::uint32 price_;
  friend void  protobuf_AddDesc_GroupBuyingConfig_2eproto();
  friend void protobuf_AssignDesc_GroupBuyingConfig_2eproto();
  friend void protobuf_ShutdownFile_GroupBuyingConfig_2eproto();

  void InitAsDefaultInstance();
  static CountPrice* default_instance_;
};
// -------------------------------------------------------------------

class GroupBuyingItem : public ::google::protobuf::Message {
 public:
  GroupBuyingItem();
  virtual ~GroupBuyingItem();

  GroupBuyingItem(const GroupBuyingItem& from);

  inline GroupBuyingItem& operator=(const GroupBuyingItem& from) {
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
  static const GroupBuyingItem& default_instance();

  void Swap(GroupBuyingItem* other);

  // implements Message ----------------------------------------------

  GroupBuyingItem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GroupBuyingItem& from);
  void MergeFrom(const GroupBuyingItem& from);
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

  // required uint32 oriprice = 2;
  inline bool has_oriprice() const;
  inline void clear_oriprice();
  static const int kOripriceFieldNumber = 2;
  inline ::google::protobuf::uint32 oriprice() const;
  inline void set_oriprice(::google::protobuf::uint32 value);

  // required .RewardConfig.RewardItemCfg reward = 3;
  inline bool has_reward() const;
  inline void clear_reward();
  static const int kRewardFieldNumber = 3;
  inline const ::RewardConfig::RewardItemCfg& reward() const;
  inline ::RewardConfig::RewardItemCfg* mutable_reward();
  inline ::RewardConfig::RewardItemCfg* release_reward();
  inline void set_allocated_reward(::RewardConfig::RewardItemCfg* reward);

  // repeated .GroupBuyingConfig.CountPrice people = 4;
  inline int people_size() const;
  inline void clear_people();
  static const int kPeopleFieldNumber = 4;
  inline const ::GroupBuyingConfig::CountPrice& people(int index) const;
  inline ::GroupBuyingConfig::CountPrice* mutable_people(int index);
  inline ::GroupBuyingConfig::CountPrice* add_people();
  inline const ::google::protobuf::RepeatedPtrField< ::GroupBuyingConfig::CountPrice >&
      people() const;
  inline ::google::protobuf::RepeatedPtrField< ::GroupBuyingConfig::CountPrice >*
      mutable_people();

  // @@protoc_insertion_point(class_scope:GroupBuyingConfig.GroupBuyingItem)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_oriprice();
  inline void clear_has_oriprice();
  inline void set_has_reward();
  inline void clear_has_reward();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 oriprice_;
  ::RewardConfig::RewardItemCfg* reward_;
  ::google::protobuf::RepeatedPtrField< ::GroupBuyingConfig::CountPrice > people_;
  friend void  protobuf_AddDesc_GroupBuyingConfig_2eproto();
  friend void protobuf_AssignDesc_GroupBuyingConfig_2eproto();
  friend void protobuf_ShutdownFile_GroupBuyingConfig_2eproto();

  void InitAsDefaultInstance();
  static GroupBuyingItem* default_instance_;
};
// -------------------------------------------------------------------

class GroupBuyingItemsCfg : public ::google::protobuf::Message {
 public:
  GroupBuyingItemsCfg();
  virtual ~GroupBuyingItemsCfg();

  GroupBuyingItemsCfg(const GroupBuyingItemsCfg& from);

  inline GroupBuyingItemsCfg& operator=(const GroupBuyingItemsCfg& from) {
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
  static const GroupBuyingItemsCfg& default_instance();

  void Swap(GroupBuyingItemsCfg* other);

  // implements Message ----------------------------------------------

  GroupBuyingItemsCfg* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GroupBuyingItemsCfg& from);
  void MergeFrom(const GroupBuyingItemsCfg& from);
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

  // repeated .GroupBuyingConfig.GroupBuyingItem tuangou = 1;
  inline int tuangou_size() const;
  inline void clear_tuangou();
  static const int kTuangouFieldNumber = 1;
  inline const ::GroupBuyingConfig::GroupBuyingItem& tuangou(int index) const;
  inline ::GroupBuyingConfig::GroupBuyingItem* mutable_tuangou(int index);
  inline ::GroupBuyingConfig::GroupBuyingItem* add_tuangou();
  inline const ::google::protobuf::RepeatedPtrField< ::GroupBuyingConfig::GroupBuyingItem >&
      tuangou() const;
  inline ::google::protobuf::RepeatedPtrField< ::GroupBuyingConfig::GroupBuyingItem >*
      mutable_tuangou();

  // @@protoc_insertion_point(class_scope:GroupBuyingConfig.GroupBuyingItemsCfg)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::GroupBuyingConfig::GroupBuyingItem > tuangou_;
  friend void  protobuf_AddDesc_GroupBuyingConfig_2eproto();
  friend void protobuf_AssignDesc_GroupBuyingConfig_2eproto();
  friend void protobuf_ShutdownFile_GroupBuyingConfig_2eproto();

  void InitAsDefaultInstance();
  static GroupBuyingItemsCfg* default_instance_;
};
// ===================================================================


// ===================================================================

// CountPrice

// required uint32 count = 1;
inline bool CountPrice::has_count() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CountPrice::set_has_count() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CountPrice::clear_has_count() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void CountPrice::clear_count() {
  count_ = 0u;
  clear_has_count();
}
inline ::google::protobuf::uint32 CountPrice::count() const {
  // @@protoc_insertion_point(field_get:GroupBuyingConfig.CountPrice.count)
  return count_;
}
inline void CountPrice::set_count(::google::protobuf::uint32 value) {
  set_has_count();
  count_ = value;
  // @@protoc_insertion_point(field_set:GroupBuyingConfig.CountPrice.count)
}

// required uint32 price = 2;
inline bool CountPrice::has_price() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void CountPrice::set_has_price() {
  _has_bits_[0] |= 0x00000002u;
}
inline void CountPrice::clear_has_price() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void CountPrice::clear_price() {
  price_ = 0u;
  clear_has_price();
}
inline ::google::protobuf::uint32 CountPrice::price() const {
  // @@protoc_insertion_point(field_get:GroupBuyingConfig.CountPrice.price)
  return price_;
}
inline void CountPrice::set_price(::google::protobuf::uint32 value) {
  set_has_price();
  price_ = value;
  // @@protoc_insertion_point(field_set:GroupBuyingConfig.CountPrice.price)
}

// -------------------------------------------------------------------

// GroupBuyingItem

// required uint32 id = 1;
inline bool GroupBuyingItem::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GroupBuyingItem::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void GroupBuyingItem::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void GroupBuyingItem::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 GroupBuyingItem::id() const {
  // @@protoc_insertion_point(field_get:GroupBuyingConfig.GroupBuyingItem.id)
  return id_;
}
inline void GroupBuyingItem::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:GroupBuyingConfig.GroupBuyingItem.id)
}

// required uint32 oriprice = 2;
inline bool GroupBuyingItem::has_oriprice() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void GroupBuyingItem::set_has_oriprice() {
  _has_bits_[0] |= 0x00000002u;
}
inline void GroupBuyingItem::clear_has_oriprice() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void GroupBuyingItem::clear_oriprice() {
  oriprice_ = 0u;
  clear_has_oriprice();
}
inline ::google::protobuf::uint32 GroupBuyingItem::oriprice() const {
  // @@protoc_insertion_point(field_get:GroupBuyingConfig.GroupBuyingItem.oriprice)
  return oriprice_;
}
inline void GroupBuyingItem::set_oriprice(::google::protobuf::uint32 value) {
  set_has_oriprice();
  oriprice_ = value;
  // @@protoc_insertion_point(field_set:GroupBuyingConfig.GroupBuyingItem.oriprice)
}

// required .RewardConfig.RewardItemCfg reward = 3;
inline bool GroupBuyingItem::has_reward() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void GroupBuyingItem::set_has_reward() {
  _has_bits_[0] |= 0x00000004u;
}
inline void GroupBuyingItem::clear_has_reward() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void GroupBuyingItem::clear_reward() {
  if (reward_ != NULL) reward_->::RewardConfig::RewardItemCfg::Clear();
  clear_has_reward();
}
inline const ::RewardConfig::RewardItemCfg& GroupBuyingItem::reward() const {
  // @@protoc_insertion_point(field_get:GroupBuyingConfig.GroupBuyingItem.reward)
  return reward_ != NULL ? *reward_ : *default_instance_->reward_;
}
inline ::RewardConfig::RewardItemCfg* GroupBuyingItem::mutable_reward() {
  set_has_reward();
  if (reward_ == NULL) reward_ = new ::RewardConfig::RewardItemCfg;
  // @@protoc_insertion_point(field_mutable:GroupBuyingConfig.GroupBuyingItem.reward)
  return reward_;
}
inline ::RewardConfig::RewardItemCfg* GroupBuyingItem::release_reward() {
  clear_has_reward();
  ::RewardConfig::RewardItemCfg* temp = reward_;
  reward_ = NULL;
  return temp;
}
inline void GroupBuyingItem::set_allocated_reward(::RewardConfig::RewardItemCfg* reward) {
  delete reward_;
  reward_ = reward;
  if (reward) {
    set_has_reward();
  } else {
    clear_has_reward();
  }
  // @@protoc_insertion_point(field_set_allocated:GroupBuyingConfig.GroupBuyingItem.reward)
}

// repeated .GroupBuyingConfig.CountPrice people = 4;
inline int GroupBuyingItem::people_size() const {
  return people_.size();
}
inline void GroupBuyingItem::clear_people() {
  people_.Clear();
}
inline const ::GroupBuyingConfig::CountPrice& GroupBuyingItem::people(int index) const {
  // @@protoc_insertion_point(field_get:GroupBuyingConfig.GroupBuyingItem.people)
  return people_.Get(index);
}
inline ::GroupBuyingConfig::CountPrice* GroupBuyingItem::mutable_people(int index) {
  // @@protoc_insertion_point(field_mutable:GroupBuyingConfig.GroupBuyingItem.people)
  return people_.Mutable(index);
}
inline ::GroupBuyingConfig::CountPrice* GroupBuyingItem::add_people() {
  // @@protoc_insertion_point(field_add:GroupBuyingConfig.GroupBuyingItem.people)
  return people_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::GroupBuyingConfig::CountPrice >&
GroupBuyingItem::people() const {
  // @@protoc_insertion_point(field_list:GroupBuyingConfig.GroupBuyingItem.people)
  return people_;
}
inline ::google::protobuf::RepeatedPtrField< ::GroupBuyingConfig::CountPrice >*
GroupBuyingItem::mutable_people() {
  // @@protoc_insertion_point(field_mutable_list:GroupBuyingConfig.GroupBuyingItem.people)
  return &people_;
}

// -------------------------------------------------------------------

// GroupBuyingItemsCfg

// repeated .GroupBuyingConfig.GroupBuyingItem tuangou = 1;
inline int GroupBuyingItemsCfg::tuangou_size() const {
  return tuangou_.size();
}
inline void GroupBuyingItemsCfg::clear_tuangou() {
  tuangou_.Clear();
}
inline const ::GroupBuyingConfig::GroupBuyingItem& GroupBuyingItemsCfg::tuangou(int index) const {
  // @@protoc_insertion_point(field_get:GroupBuyingConfig.GroupBuyingItemsCfg.tuangou)
  return tuangou_.Get(index);
}
inline ::GroupBuyingConfig::GroupBuyingItem* GroupBuyingItemsCfg::mutable_tuangou(int index) {
  // @@protoc_insertion_point(field_mutable:GroupBuyingConfig.GroupBuyingItemsCfg.tuangou)
  return tuangou_.Mutable(index);
}
inline ::GroupBuyingConfig::GroupBuyingItem* GroupBuyingItemsCfg::add_tuangou() {
  // @@protoc_insertion_point(field_add:GroupBuyingConfig.GroupBuyingItemsCfg.tuangou)
  return tuangou_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::GroupBuyingConfig::GroupBuyingItem >&
GroupBuyingItemsCfg::tuangou() const {
  // @@protoc_insertion_point(field_list:GroupBuyingConfig.GroupBuyingItemsCfg.tuangou)
  return tuangou_;
}
inline ::google::protobuf::RepeatedPtrField< ::GroupBuyingConfig::GroupBuyingItem >*
GroupBuyingItemsCfg::mutable_tuangou() {
  // @@protoc_insertion_point(field_mutable_list:GroupBuyingConfig.GroupBuyingItemsCfg.tuangou)
  return &tuangou_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace GroupBuyingConfig

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_GroupBuyingConfig_2eproto__INCLUDED
