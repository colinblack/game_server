// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: BagConfig.proto

#ifndef PROTOBUF_BagConfig_2eproto__INCLUDED
#define PROTOBUF_BagConfig_2eproto__INCLUDED

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

namespace BagConfig {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_BagConfig_2eproto();
void protobuf_AssignDesc_BagConfig_2eproto();
void protobuf_ShutdownFile_BagConfig_2eproto();

class Costs;
class BagCosts;

// ===================================================================

class Costs : public ::google::protobuf::Message {
 public:
  Costs();
  virtual ~Costs();

  Costs(const Costs& from);

  inline Costs& operator=(const Costs& from) {
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
  static const Costs& default_instance();

  void Swap(Costs* other);

  // implements Message ----------------------------------------------

  Costs* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Costs& from);
  void MergeFrom(const Costs& from);
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

  // required uint32 price = 2;
  inline bool has_price() const;
  inline void clear_price();
  static const int kPriceFieldNumber = 2;
  inline ::google::protobuf::uint32 price() const;
  inline void set_price(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:BagConfig.Costs)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_price();
  inline void clear_has_price();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 price_;
  friend void  protobuf_AddDesc_BagConfig_2eproto();
  friend void protobuf_AssignDesc_BagConfig_2eproto();
  friend void protobuf_ShutdownFile_BagConfig_2eproto();

  void InitAsDefaultInstance();
  static Costs* default_instance_;
};
// -------------------------------------------------------------------

class BagCosts : public ::google::protobuf::Message {
 public:
  BagCosts();
  virtual ~BagCosts();

  BagCosts(const BagCosts& from);

  inline BagCosts& operator=(const BagCosts& from) {
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
  static const BagCosts& default_instance();

  void Swap(BagCosts* other);

  // implements Message ----------------------------------------------

  BagCosts* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BagCosts& from);
  void MergeFrom(const BagCosts& from);
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

  // required uint32 init = 1;
  inline bool has_init() const;
  inline void clear_init();
  static const int kInitFieldNumber = 1;
  inline ::google::protobuf::uint32 init() const;
  inline void set_init(::google::protobuf::uint32 value);

  // required uint32 max = 2;
  inline bool has_max() const;
  inline void clear_max();
  static const int kMaxFieldNumber = 2;
  inline ::google::protobuf::uint32 max() const;
  inline void set_max(::google::protobuf::uint32 value);

  // repeated .BagConfig.Costs costs = 3;
  inline int costs_size() const;
  inline void clear_costs();
  static const int kCostsFieldNumber = 3;
  inline const ::BagConfig::Costs& costs(int index) const;
  inline ::BagConfig::Costs* mutable_costs(int index);
  inline ::BagConfig::Costs* add_costs();
  inline const ::google::protobuf::RepeatedPtrField< ::BagConfig::Costs >&
      costs() const;
  inline ::google::protobuf::RepeatedPtrField< ::BagConfig::Costs >*
      mutable_costs();

  // @@protoc_insertion_point(class_scope:BagConfig.BagCosts)
 private:
  inline void set_has_init();
  inline void clear_has_init();
  inline void set_has_max();
  inline void clear_has_max();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 init_;
  ::google::protobuf::uint32 max_;
  ::google::protobuf::RepeatedPtrField< ::BagConfig::Costs > costs_;
  friend void  protobuf_AddDesc_BagConfig_2eproto();
  friend void protobuf_AssignDesc_BagConfig_2eproto();
  friend void protobuf_ShutdownFile_BagConfig_2eproto();

  void InitAsDefaultInstance();
  static BagCosts* default_instance_;
};
// ===================================================================


// ===================================================================

// Costs

// required uint32 id = 1;
inline bool Costs::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Costs::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Costs::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Costs::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 Costs::id() const {
  // @@protoc_insertion_point(field_get:BagConfig.Costs.id)
  return id_;
}
inline void Costs::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:BagConfig.Costs.id)
}

// required uint32 price = 2;
inline bool Costs::has_price() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Costs::set_has_price() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Costs::clear_has_price() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Costs::clear_price() {
  price_ = 0u;
  clear_has_price();
}
inline ::google::protobuf::uint32 Costs::price() const {
  // @@protoc_insertion_point(field_get:BagConfig.Costs.price)
  return price_;
}
inline void Costs::set_price(::google::protobuf::uint32 value) {
  set_has_price();
  price_ = value;
  // @@protoc_insertion_point(field_set:BagConfig.Costs.price)
}

// -------------------------------------------------------------------

// BagCosts

// required uint32 init = 1;
inline bool BagCosts::has_init() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void BagCosts::set_has_init() {
  _has_bits_[0] |= 0x00000001u;
}
inline void BagCosts::clear_has_init() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void BagCosts::clear_init() {
  init_ = 0u;
  clear_has_init();
}
inline ::google::protobuf::uint32 BagCosts::init() const {
  // @@protoc_insertion_point(field_get:BagConfig.BagCosts.init)
  return init_;
}
inline void BagCosts::set_init(::google::protobuf::uint32 value) {
  set_has_init();
  init_ = value;
  // @@protoc_insertion_point(field_set:BagConfig.BagCosts.init)
}

// required uint32 max = 2;
inline bool BagCosts::has_max() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void BagCosts::set_has_max() {
  _has_bits_[0] |= 0x00000002u;
}
inline void BagCosts::clear_has_max() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void BagCosts::clear_max() {
  max_ = 0u;
  clear_has_max();
}
inline ::google::protobuf::uint32 BagCosts::max() const {
  // @@protoc_insertion_point(field_get:BagConfig.BagCosts.max)
  return max_;
}
inline void BagCosts::set_max(::google::protobuf::uint32 value) {
  set_has_max();
  max_ = value;
  // @@protoc_insertion_point(field_set:BagConfig.BagCosts.max)
}

// repeated .BagConfig.Costs costs = 3;
inline int BagCosts::costs_size() const {
  return costs_.size();
}
inline void BagCosts::clear_costs() {
  costs_.Clear();
}
inline const ::BagConfig::Costs& BagCosts::costs(int index) const {
  // @@protoc_insertion_point(field_get:BagConfig.BagCosts.costs)
  return costs_.Get(index);
}
inline ::BagConfig::Costs* BagCosts::mutable_costs(int index) {
  // @@protoc_insertion_point(field_mutable:BagConfig.BagCosts.costs)
  return costs_.Mutable(index);
}
inline ::BagConfig::Costs* BagCosts::add_costs() {
  // @@protoc_insertion_point(field_add:BagConfig.BagCosts.costs)
  return costs_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::BagConfig::Costs >&
BagCosts::costs() const {
  // @@protoc_insertion_point(field_list:BagConfig.BagCosts.costs)
  return costs_;
}
inline ::google::protobuf::RepeatedPtrField< ::BagConfig::Costs >*
BagCosts::mutable_costs() {
  // @@protoc_insertion_point(field_mutable_list:BagConfig.BagCosts.costs)
  return &costs_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace BagConfig

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_BagConfig_2eproto__INCLUDED
