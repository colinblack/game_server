// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ConfigAlliance.proto

#ifndef PROTOBUF_ConfigAlliance_2eproto__INCLUDED
#define PROTOBUF_ConfigAlliance_2eproto__INCLUDED

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
#include "CommonGiftConfig.pb.h"
// @@protoc_insertion_point(includes)

namespace ConfigAlliance {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ConfigAlliance_2eproto();
void protobuf_AssignDesc_ConfigAlliance_2eproto();
void protobuf_ShutdownFile_ConfigAlliance_2eproto();

class TypeStorage;
class Donation;
class Alliance;

// ===================================================================

class TypeStorage : public ::google::protobuf::Message {
 public:
  TypeStorage();
  virtual ~TypeStorage();

  TypeStorage(const TypeStorage& from);

  inline TypeStorage& operator=(const TypeStorage& from) {
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
  static const TypeStorage& default_instance();

  void Swap(TypeStorage* other);

  // implements Message ----------------------------------------------

  TypeStorage* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TypeStorage& from);
  void MergeFrom(const TypeStorage& from);
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

  // required uint32 limitnum = 1;
  inline bool has_limitnum() const;
  inline void clear_limitnum();
  static const int kLimitnumFieldNumber = 1;
  inline ::google::protobuf::uint32 limitnum() const;
  inline void set_limitnum(::google::protobuf::uint32 value);

  // required uint32 type = 2;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 2;
  inline ::google::protobuf::uint32 type() const;
  inline void set_type(::google::protobuf::uint32 value);

  // repeated uint32 products = 3;
  inline int products_size() const;
  inline void clear_products();
  static const int kProductsFieldNumber = 3;
  inline ::google::protobuf::uint32 products(int index) const;
  inline void set_products(int index, ::google::protobuf::uint32 value);
  inline void add_products(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      products() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_products();

  // @@protoc_insertion_point(class_scope:ConfigAlliance.TypeStorage)
 private:
  inline void set_has_limitnum();
  inline void clear_has_limitnum();
  inline void set_has_type();
  inline void clear_has_type();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 limitnum_;
  ::google::protobuf::uint32 type_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > products_;
  friend void  protobuf_AddDesc_ConfigAlliance_2eproto();
  friend void protobuf_AssignDesc_ConfigAlliance_2eproto();
  friend void protobuf_ShutdownFile_ConfigAlliance_2eproto();

  void InitAsDefaultInstance();
  static TypeStorage* default_instance_;
};
// -------------------------------------------------------------------

class Donation : public ::google::protobuf::Message {
 public:
  Donation();
  virtual ~Donation();

  Donation(const Donation& from);

  inline Donation& operator=(const Donation& from) {
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
  static const Donation& default_instance();

  void Swap(Donation* other);

  // implements Message ----------------------------------------------

  Donation* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Donation& from);
  void MergeFrom(const Donation& from);
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

  // required uint32 cdtime = 1;
  inline bool has_cdtime() const;
  inline void clear_cdtime();
  static const int kCdtimeFieldNumber = 1;
  inline ::google::protobuf::uint32 cdtime() const;
  inline void set_cdtime(::google::protobuf::uint32 value);

  // required uint32 cdprice = 2;
  inline bool has_cdprice() const;
  inline void clear_cdprice();
  static const int kCdpriceFieldNumber = 2;
  inline ::google::protobuf::uint32 cdprice() const;
  inline void set_cdprice(::google::protobuf::uint32 value);

  // repeated .ConfigAlliance.TypeStorage type_storge = 3;
  inline int type_storge_size() const;
  inline void clear_type_storge();
  static const int kTypeStorgeFieldNumber = 3;
  inline const ::ConfigAlliance::TypeStorage& type_storge(int index) const;
  inline ::ConfigAlliance::TypeStorage* mutable_type_storge(int index);
  inline ::ConfigAlliance::TypeStorage* add_type_storge();
  inline const ::google::protobuf::RepeatedPtrField< ::ConfigAlliance::TypeStorage >&
      type_storge() const;
  inline ::google::protobuf::RepeatedPtrField< ::ConfigAlliance::TypeStorage >*
      mutable_type_storge();

  // @@protoc_insertion_point(class_scope:ConfigAlliance.Donation)
 private:
  inline void set_has_cdtime();
  inline void clear_has_cdtime();
  inline void set_has_cdprice();
  inline void clear_has_cdprice();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 cdtime_;
  ::google::protobuf::uint32 cdprice_;
  ::google::protobuf::RepeatedPtrField< ::ConfigAlliance::TypeStorage > type_storge_;
  friend void  protobuf_AddDesc_ConfigAlliance_2eproto();
  friend void protobuf_AssignDesc_ConfigAlliance_2eproto();
  friend void protobuf_ShutdownFile_ConfigAlliance_2eproto();

  void InitAsDefaultInstance();
  static Donation* default_instance_;
};
// -------------------------------------------------------------------

class Alliance : public ::google::protobuf::Message {
 public:
  Alliance();
  virtual ~Alliance();

  Alliance(const Alliance& from);

  inline Alliance& operator=(const Alliance& from) {
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
  static const Alliance& default_instance();

  void Swap(Alliance* other);

  // implements Message ----------------------------------------------

  Alliance* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Alliance& from);
  void MergeFrom(const Alliance& from);
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

  // required uint32 create_level = 1;
  inline bool has_create_level() const;
  inline void clear_create_level();
  static const int kCreateLevelFieldNumber = 1;
  inline ::google::protobuf::uint32 create_level() const;
  inline void set_create_level(::google::protobuf::uint32 value);

  // required .CommonGiftConfig.CommonModifyItem create_cost = 2;
  inline bool has_create_cost() const;
  inline void clear_create_cost();
  static const int kCreateCostFieldNumber = 2;
  inline const ::CommonGiftConfig::CommonModifyItem& create_cost() const;
  inline ::CommonGiftConfig::CommonModifyItem* mutable_create_cost();
  inline ::CommonGiftConfig::CommonModifyItem* release_create_cost();
  inline void set_allocated_create_cost(::CommonGiftConfig::CommonModifyItem* create_cost);

  // required uint32 member_num_limit = 3;
  inline bool has_member_num_limit() const;
  inline void clear_member_num_limit();
  static const int kMemberNumLimitFieldNumber = 3;
  inline ::google::protobuf::uint32 member_num_limit() const;
  inline void set_member_num_limit(::google::protobuf::uint32 value);

  // required uint32 director_num_limit = 4;
  inline bool has_director_num_limit() const;
  inline void clear_director_num_limit();
  static const int kDirectorNumLimitFieldNumber = 4;
  inline ::google::protobuf::uint32 director_num_limit() const;
  inline void set_director_num_limit(::google::protobuf::uint32 value);

  // required uint32 committee_num_limit = 5;
  inline bool has_committee_num_limit() const;
  inline void clear_committee_num_limit();
  static const int kCommitteeNumLimitFieldNumber = 5;
  inline ::google::protobuf::uint32 committee_num_limit() const;
  inline void set_committee_num_limit(::google::protobuf::uint32 value);

  // required .ConfigAlliance.Donation donation = 6;
  inline bool has_donation() const;
  inline void clear_donation();
  static const int kDonationFieldNumber = 6;
  inline const ::ConfigAlliance::Donation& donation() const;
  inline ::ConfigAlliance::Donation* mutable_donation();
  inline ::ConfigAlliance::Donation* release_donation();
  inline void set_allocated_donation(::ConfigAlliance::Donation* donation);

  // @@protoc_insertion_point(class_scope:ConfigAlliance.Alliance)
 private:
  inline void set_has_create_level();
  inline void clear_has_create_level();
  inline void set_has_create_cost();
  inline void clear_has_create_cost();
  inline void set_has_member_num_limit();
  inline void clear_has_member_num_limit();
  inline void set_has_director_num_limit();
  inline void clear_has_director_num_limit();
  inline void set_has_committee_num_limit();
  inline void clear_has_committee_num_limit();
  inline void set_has_donation();
  inline void clear_has_donation();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::CommonGiftConfig::CommonModifyItem* create_cost_;
  ::google::protobuf::uint32 create_level_;
  ::google::protobuf::uint32 member_num_limit_;
  ::google::protobuf::uint32 director_num_limit_;
  ::google::protobuf::uint32 committee_num_limit_;
  ::ConfigAlliance::Donation* donation_;
  friend void  protobuf_AddDesc_ConfigAlliance_2eproto();
  friend void protobuf_AssignDesc_ConfigAlliance_2eproto();
  friend void protobuf_ShutdownFile_ConfigAlliance_2eproto();

  void InitAsDefaultInstance();
  static Alliance* default_instance_;
};
// ===================================================================


// ===================================================================

// TypeStorage

// required uint32 limitnum = 1;
inline bool TypeStorage::has_limitnum() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TypeStorage::set_has_limitnum() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TypeStorage::clear_has_limitnum() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TypeStorage::clear_limitnum() {
  limitnum_ = 0u;
  clear_has_limitnum();
}
inline ::google::protobuf::uint32 TypeStorage::limitnum() const {
  // @@protoc_insertion_point(field_get:ConfigAlliance.TypeStorage.limitnum)
  return limitnum_;
}
inline void TypeStorage::set_limitnum(::google::protobuf::uint32 value) {
  set_has_limitnum();
  limitnum_ = value;
  // @@protoc_insertion_point(field_set:ConfigAlliance.TypeStorage.limitnum)
}

// required uint32 type = 2;
inline bool TypeStorage::has_type() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TypeStorage::set_has_type() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TypeStorage::clear_has_type() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TypeStorage::clear_type() {
  type_ = 0u;
  clear_has_type();
}
inline ::google::protobuf::uint32 TypeStorage::type() const {
  // @@protoc_insertion_point(field_get:ConfigAlliance.TypeStorage.type)
  return type_;
}
inline void TypeStorage::set_type(::google::protobuf::uint32 value) {
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:ConfigAlliance.TypeStorage.type)
}

// repeated uint32 products = 3;
inline int TypeStorage::products_size() const {
  return products_.size();
}
inline void TypeStorage::clear_products() {
  products_.Clear();
}
inline ::google::protobuf::uint32 TypeStorage::products(int index) const {
  // @@protoc_insertion_point(field_get:ConfigAlliance.TypeStorage.products)
  return products_.Get(index);
}
inline void TypeStorage::set_products(int index, ::google::protobuf::uint32 value) {
  products_.Set(index, value);
  // @@protoc_insertion_point(field_set:ConfigAlliance.TypeStorage.products)
}
inline void TypeStorage::add_products(::google::protobuf::uint32 value) {
  products_.Add(value);
  // @@protoc_insertion_point(field_add:ConfigAlliance.TypeStorage.products)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
TypeStorage::products() const {
  // @@protoc_insertion_point(field_list:ConfigAlliance.TypeStorage.products)
  return products_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
TypeStorage::mutable_products() {
  // @@protoc_insertion_point(field_mutable_list:ConfigAlliance.TypeStorage.products)
  return &products_;
}

// -------------------------------------------------------------------

// Donation

// required uint32 cdtime = 1;
inline bool Donation::has_cdtime() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Donation::set_has_cdtime() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Donation::clear_has_cdtime() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Donation::clear_cdtime() {
  cdtime_ = 0u;
  clear_has_cdtime();
}
inline ::google::protobuf::uint32 Donation::cdtime() const {
  // @@protoc_insertion_point(field_get:ConfigAlliance.Donation.cdtime)
  return cdtime_;
}
inline void Donation::set_cdtime(::google::protobuf::uint32 value) {
  set_has_cdtime();
  cdtime_ = value;
  // @@protoc_insertion_point(field_set:ConfigAlliance.Donation.cdtime)
}

// required uint32 cdprice = 2;
inline bool Donation::has_cdprice() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Donation::set_has_cdprice() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Donation::clear_has_cdprice() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Donation::clear_cdprice() {
  cdprice_ = 0u;
  clear_has_cdprice();
}
inline ::google::protobuf::uint32 Donation::cdprice() const {
  // @@protoc_insertion_point(field_get:ConfigAlliance.Donation.cdprice)
  return cdprice_;
}
inline void Donation::set_cdprice(::google::protobuf::uint32 value) {
  set_has_cdprice();
  cdprice_ = value;
  // @@protoc_insertion_point(field_set:ConfigAlliance.Donation.cdprice)
}

// repeated .ConfigAlliance.TypeStorage type_storge = 3;
inline int Donation::type_storge_size() const {
  return type_storge_.size();
}
inline void Donation::clear_type_storge() {
  type_storge_.Clear();
}
inline const ::ConfigAlliance::TypeStorage& Donation::type_storge(int index) const {
  // @@protoc_insertion_point(field_get:ConfigAlliance.Donation.type_storge)
  return type_storge_.Get(index);
}
inline ::ConfigAlliance::TypeStorage* Donation::mutable_type_storge(int index) {
  // @@protoc_insertion_point(field_mutable:ConfigAlliance.Donation.type_storge)
  return type_storge_.Mutable(index);
}
inline ::ConfigAlliance::TypeStorage* Donation::add_type_storge() {
  // @@protoc_insertion_point(field_add:ConfigAlliance.Donation.type_storge)
  return type_storge_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ConfigAlliance::TypeStorage >&
Donation::type_storge() const {
  // @@protoc_insertion_point(field_list:ConfigAlliance.Donation.type_storge)
  return type_storge_;
}
inline ::google::protobuf::RepeatedPtrField< ::ConfigAlliance::TypeStorage >*
Donation::mutable_type_storge() {
  // @@protoc_insertion_point(field_mutable_list:ConfigAlliance.Donation.type_storge)
  return &type_storge_;
}

// -------------------------------------------------------------------

// Alliance

// required uint32 create_level = 1;
inline bool Alliance::has_create_level() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Alliance::set_has_create_level() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Alliance::clear_has_create_level() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Alliance::clear_create_level() {
  create_level_ = 0u;
  clear_has_create_level();
}
inline ::google::protobuf::uint32 Alliance::create_level() const {
  // @@protoc_insertion_point(field_get:ConfigAlliance.Alliance.create_level)
  return create_level_;
}
inline void Alliance::set_create_level(::google::protobuf::uint32 value) {
  set_has_create_level();
  create_level_ = value;
  // @@protoc_insertion_point(field_set:ConfigAlliance.Alliance.create_level)
}

// required .CommonGiftConfig.CommonModifyItem create_cost = 2;
inline bool Alliance::has_create_cost() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Alliance::set_has_create_cost() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Alliance::clear_has_create_cost() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Alliance::clear_create_cost() {
  if (create_cost_ != NULL) create_cost_->::CommonGiftConfig::CommonModifyItem::Clear();
  clear_has_create_cost();
}
inline const ::CommonGiftConfig::CommonModifyItem& Alliance::create_cost() const {
  // @@protoc_insertion_point(field_get:ConfigAlliance.Alliance.create_cost)
  return create_cost_ != NULL ? *create_cost_ : *default_instance_->create_cost_;
}
inline ::CommonGiftConfig::CommonModifyItem* Alliance::mutable_create_cost() {
  set_has_create_cost();
  if (create_cost_ == NULL) create_cost_ = new ::CommonGiftConfig::CommonModifyItem;
  // @@protoc_insertion_point(field_mutable:ConfigAlliance.Alliance.create_cost)
  return create_cost_;
}
inline ::CommonGiftConfig::CommonModifyItem* Alliance::release_create_cost() {
  clear_has_create_cost();
  ::CommonGiftConfig::CommonModifyItem* temp = create_cost_;
  create_cost_ = NULL;
  return temp;
}
inline void Alliance::set_allocated_create_cost(::CommonGiftConfig::CommonModifyItem* create_cost) {
  delete create_cost_;
  create_cost_ = create_cost;
  if (create_cost) {
    set_has_create_cost();
  } else {
    clear_has_create_cost();
  }
  // @@protoc_insertion_point(field_set_allocated:ConfigAlliance.Alliance.create_cost)
}

// required uint32 member_num_limit = 3;
inline bool Alliance::has_member_num_limit() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Alliance::set_has_member_num_limit() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Alliance::clear_has_member_num_limit() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Alliance::clear_member_num_limit() {
  member_num_limit_ = 0u;
  clear_has_member_num_limit();
}
inline ::google::protobuf::uint32 Alliance::member_num_limit() const {
  // @@protoc_insertion_point(field_get:ConfigAlliance.Alliance.member_num_limit)
  return member_num_limit_;
}
inline void Alliance::set_member_num_limit(::google::protobuf::uint32 value) {
  set_has_member_num_limit();
  member_num_limit_ = value;
  // @@protoc_insertion_point(field_set:ConfigAlliance.Alliance.member_num_limit)
}

// required uint32 director_num_limit = 4;
inline bool Alliance::has_director_num_limit() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Alliance::set_has_director_num_limit() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Alliance::clear_has_director_num_limit() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Alliance::clear_director_num_limit() {
  director_num_limit_ = 0u;
  clear_has_director_num_limit();
}
inline ::google::protobuf::uint32 Alliance::director_num_limit() const {
  // @@protoc_insertion_point(field_get:ConfigAlliance.Alliance.director_num_limit)
  return director_num_limit_;
}
inline void Alliance::set_director_num_limit(::google::protobuf::uint32 value) {
  set_has_director_num_limit();
  director_num_limit_ = value;
  // @@protoc_insertion_point(field_set:ConfigAlliance.Alliance.director_num_limit)
}

// required uint32 committee_num_limit = 5;
inline bool Alliance::has_committee_num_limit() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Alliance::set_has_committee_num_limit() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Alliance::clear_has_committee_num_limit() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Alliance::clear_committee_num_limit() {
  committee_num_limit_ = 0u;
  clear_has_committee_num_limit();
}
inline ::google::protobuf::uint32 Alliance::committee_num_limit() const {
  // @@protoc_insertion_point(field_get:ConfigAlliance.Alliance.committee_num_limit)
  return committee_num_limit_;
}
inline void Alliance::set_committee_num_limit(::google::protobuf::uint32 value) {
  set_has_committee_num_limit();
  committee_num_limit_ = value;
  // @@protoc_insertion_point(field_set:ConfigAlliance.Alliance.committee_num_limit)
}

// required .ConfigAlliance.Donation donation = 6;
inline bool Alliance::has_donation() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Alliance::set_has_donation() {
  _has_bits_[0] |= 0x00000020u;
}
inline void Alliance::clear_has_donation() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void Alliance::clear_donation() {
  if (donation_ != NULL) donation_->::ConfigAlliance::Donation::Clear();
  clear_has_donation();
}
inline const ::ConfigAlliance::Donation& Alliance::donation() const {
  // @@protoc_insertion_point(field_get:ConfigAlliance.Alliance.donation)
  return donation_ != NULL ? *donation_ : *default_instance_->donation_;
}
inline ::ConfigAlliance::Donation* Alliance::mutable_donation() {
  set_has_donation();
  if (donation_ == NULL) donation_ = new ::ConfigAlliance::Donation;
  // @@protoc_insertion_point(field_mutable:ConfigAlliance.Alliance.donation)
  return donation_;
}
inline ::ConfigAlliance::Donation* Alliance::release_donation() {
  clear_has_donation();
  ::ConfigAlliance::Donation* temp = donation_;
  donation_ = NULL;
  return temp;
}
inline void Alliance::set_allocated_donation(::ConfigAlliance::Donation* donation) {
  delete donation_;
  donation_ = donation;
  if (donation) {
    set_has_donation();
  } else {
    clear_has_donation();
  }
  // @@protoc_insertion_point(field_set_allocated:ConfigAlliance.Alliance.donation)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ConfigAlliance

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ConfigAlliance_2eproto__INCLUDED