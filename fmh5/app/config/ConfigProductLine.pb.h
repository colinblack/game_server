// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ConfigProductLine.proto

#ifndef PROTOBUF_ConfigProductLine_2eproto__INCLUDED
#define PROTOBUF_ConfigProductLine_2eproto__INCLUDED

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

namespace ConfigProductLine {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ConfigProductLine_2eproto();
void protobuf_AssignDesc_ConfigProductLine_2eproto();
void protobuf_ShutdownFile_ConfigProductLine_2eproto();

class EquipLine;
class AnimalLine;
class ProductLine;

// ===================================================================

class EquipLine : public ::google::protobuf::Message {
 public:
  EquipLine();
  virtual ~EquipLine();

  EquipLine(const EquipLine& from);

  inline EquipLine& operator=(const EquipLine& from) {
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
  static const EquipLine& default_instance();

  void Swap(EquipLine* other);

  // implements Message ----------------------------------------------

  EquipLine* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const EquipLine& from);
  void MergeFrom(const EquipLine& from);
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

  // repeated .CommonGiftConfig.CommonModifyItem product_list = 2;
  inline int product_list_size() const;
  inline void clear_product_list();
  static const int kProductListFieldNumber = 2;
  inline const ::CommonGiftConfig::CommonModifyItem& product_list(int index) const;
  inline ::CommonGiftConfig::CommonModifyItem* mutable_product_list(int index);
  inline ::CommonGiftConfig::CommonModifyItem* add_product_list();
  inline const ::google::protobuf::RepeatedPtrField< ::CommonGiftConfig::CommonModifyItem >&
      product_list() const;
  inline ::google::protobuf::RepeatedPtrField< ::CommonGiftConfig::CommonModifyItem >*
      mutable_product_list();

  // required uint32 maxqueue = 3;
  inline bool has_maxqueue() const;
  inline void clear_maxqueue();
  static const int kMaxqueueFieldNumber = 3;
  inline ::google::protobuf::uint32 maxqueue() const;
  inline void set_maxqueue(::google::protobuf::uint32 value);

  // repeated .CommonGiftConfig.CommonModifyItem queue_price = 4;
  inline int queue_price_size() const;
  inline void clear_queue_price();
  static const int kQueuePriceFieldNumber = 4;
  inline const ::CommonGiftConfig::CommonModifyItem& queue_price(int index) const;
  inline ::CommonGiftConfig::CommonModifyItem* mutable_queue_price(int index);
  inline ::CommonGiftConfig::CommonModifyItem* add_queue_price();
  inline const ::google::protobuf::RepeatedPtrField< ::CommonGiftConfig::CommonModifyItem >&
      queue_price() const;
  inline ::google::protobuf::RepeatedPtrField< ::CommonGiftConfig::CommonModifyItem >*
      mutable_queue_price();

  // @@protoc_insertion_point(class_scope:ConfigProductLine.EquipLine)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_maxqueue();
  inline void clear_has_maxqueue();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::CommonGiftConfig::CommonModifyItem > product_list_;
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 maxqueue_;
  ::google::protobuf::RepeatedPtrField< ::CommonGiftConfig::CommonModifyItem > queue_price_;
  friend void  protobuf_AddDesc_ConfigProductLine_2eproto();
  friend void protobuf_AssignDesc_ConfigProductLine_2eproto();
  friend void protobuf_ShutdownFile_ConfigProductLine_2eproto();

  void InitAsDefaultInstance();
  static EquipLine* default_instance_;
};
// -------------------------------------------------------------------

class AnimalLine : public ::google::protobuf::Message {
 public:
  AnimalLine();
  virtual ~AnimalLine();

  AnimalLine(const AnimalLine& from);

  inline AnimalLine& operator=(const AnimalLine& from) {
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
  static const AnimalLine& default_instance();

  void Swap(AnimalLine* other);

  // implements Message ----------------------------------------------

  AnimalLine* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AnimalLine& from);
  void MergeFrom(const AnimalLine& from);
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

  // required uint32 fodder = 2;
  inline bool has_fodder() const;
  inline void clear_fodder();
  static const int kFodderFieldNumber = 2;
  inline ::google::protobuf::uint32 fodder() const;
  inline void set_fodder(::google::protobuf::uint32 value);

  // required .CommonGiftConfig.CommonModifyItem product = 3;
  inline bool has_product() const;
  inline void clear_product();
  static const int kProductFieldNumber = 3;
  inline const ::CommonGiftConfig::CommonModifyItem& product() const;
  inline ::CommonGiftConfig::CommonModifyItem* mutable_product();
  inline ::CommonGiftConfig::CommonModifyItem* release_product();
  inline void set_allocated_product(::CommonGiftConfig::CommonModifyItem* product);

  // @@protoc_insertion_point(class_scope:ConfigProductLine.AnimalLine)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_fodder();
  inline void clear_has_fodder();
  inline void set_has_product();
  inline void clear_has_product();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 fodder_;
  ::CommonGiftConfig::CommonModifyItem* product_;
  friend void  protobuf_AddDesc_ConfigProductLine_2eproto();
  friend void protobuf_AssignDesc_ConfigProductLine_2eproto();
  friend void protobuf_ShutdownFile_ConfigProductLine_2eproto();

  void InitAsDefaultInstance();
  static AnimalLine* default_instance_;
};
// -------------------------------------------------------------------

class ProductLine : public ::google::protobuf::Message {
 public:
  ProductLine();
  virtual ~ProductLine();

  ProductLine(const ProductLine& from);

  inline ProductLine& operator=(const ProductLine& from) {
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
  static const ProductLine& default_instance();

  void Swap(ProductLine* other);

  // implements Message ----------------------------------------------

  ProductLine* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ProductLine& from);
  void MergeFrom(const ProductLine& from);
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

  // repeated .ConfigProductLine.EquipLine equipline = 1;
  inline int equipline_size() const;
  inline void clear_equipline();
  static const int kEquiplineFieldNumber = 1;
  inline const ::ConfigProductLine::EquipLine& equipline(int index) const;
  inline ::ConfigProductLine::EquipLine* mutable_equipline(int index);
  inline ::ConfigProductLine::EquipLine* add_equipline();
  inline const ::google::protobuf::RepeatedPtrField< ::ConfigProductLine::EquipLine >&
      equipline() const;
  inline ::google::protobuf::RepeatedPtrField< ::ConfigProductLine::EquipLine >*
      mutable_equipline();

  // repeated .ConfigProductLine.AnimalLine animal_line = 2;
  inline int animal_line_size() const;
  inline void clear_animal_line();
  static const int kAnimalLineFieldNumber = 2;
  inline const ::ConfigProductLine::AnimalLine& animal_line(int index) const;
  inline ::ConfigProductLine::AnimalLine* mutable_animal_line(int index);
  inline ::ConfigProductLine::AnimalLine* add_animal_line();
  inline const ::google::protobuf::RepeatedPtrField< ::ConfigProductLine::AnimalLine >&
      animal_line() const;
  inline ::google::protobuf::RepeatedPtrField< ::ConfigProductLine::AnimalLine >*
      mutable_animal_line();

  // @@protoc_insertion_point(class_scope:ConfigProductLine.ProductLine)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::ConfigProductLine::EquipLine > equipline_;
  ::google::protobuf::RepeatedPtrField< ::ConfigProductLine::AnimalLine > animal_line_;
  friend void  protobuf_AddDesc_ConfigProductLine_2eproto();
  friend void protobuf_AssignDesc_ConfigProductLine_2eproto();
  friend void protobuf_ShutdownFile_ConfigProductLine_2eproto();

  void InitAsDefaultInstance();
  static ProductLine* default_instance_;
};
// ===================================================================


// ===================================================================

// EquipLine

// required uint32 id = 1;
inline bool EquipLine::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void EquipLine::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void EquipLine::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void EquipLine::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 EquipLine::id() const {
  // @@protoc_insertion_point(field_get:ConfigProductLine.EquipLine.id)
  return id_;
}
inline void EquipLine::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:ConfigProductLine.EquipLine.id)
}

// repeated .CommonGiftConfig.CommonModifyItem product_list = 2;
inline int EquipLine::product_list_size() const {
  return product_list_.size();
}
inline void EquipLine::clear_product_list() {
  product_list_.Clear();
}
inline const ::CommonGiftConfig::CommonModifyItem& EquipLine::product_list(int index) const {
  // @@protoc_insertion_point(field_get:ConfigProductLine.EquipLine.product_list)
  return product_list_.Get(index);
}
inline ::CommonGiftConfig::CommonModifyItem* EquipLine::mutable_product_list(int index) {
  // @@protoc_insertion_point(field_mutable:ConfigProductLine.EquipLine.product_list)
  return product_list_.Mutable(index);
}
inline ::CommonGiftConfig::CommonModifyItem* EquipLine::add_product_list() {
  // @@protoc_insertion_point(field_add:ConfigProductLine.EquipLine.product_list)
  return product_list_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::CommonGiftConfig::CommonModifyItem >&
EquipLine::product_list() const {
  // @@protoc_insertion_point(field_list:ConfigProductLine.EquipLine.product_list)
  return product_list_;
}
inline ::google::protobuf::RepeatedPtrField< ::CommonGiftConfig::CommonModifyItem >*
EquipLine::mutable_product_list() {
  // @@protoc_insertion_point(field_mutable_list:ConfigProductLine.EquipLine.product_list)
  return &product_list_;
}

// required uint32 maxqueue = 3;
inline bool EquipLine::has_maxqueue() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void EquipLine::set_has_maxqueue() {
  _has_bits_[0] |= 0x00000004u;
}
inline void EquipLine::clear_has_maxqueue() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void EquipLine::clear_maxqueue() {
  maxqueue_ = 0u;
  clear_has_maxqueue();
}
inline ::google::protobuf::uint32 EquipLine::maxqueue() const {
  // @@protoc_insertion_point(field_get:ConfigProductLine.EquipLine.maxqueue)
  return maxqueue_;
}
inline void EquipLine::set_maxqueue(::google::protobuf::uint32 value) {
  set_has_maxqueue();
  maxqueue_ = value;
  // @@protoc_insertion_point(field_set:ConfigProductLine.EquipLine.maxqueue)
}

// repeated .CommonGiftConfig.CommonModifyItem queue_price = 4;
inline int EquipLine::queue_price_size() const {
  return queue_price_.size();
}
inline void EquipLine::clear_queue_price() {
  queue_price_.Clear();
}
inline const ::CommonGiftConfig::CommonModifyItem& EquipLine::queue_price(int index) const {
  // @@protoc_insertion_point(field_get:ConfigProductLine.EquipLine.queue_price)
  return queue_price_.Get(index);
}
inline ::CommonGiftConfig::CommonModifyItem* EquipLine::mutable_queue_price(int index) {
  // @@protoc_insertion_point(field_mutable:ConfigProductLine.EquipLine.queue_price)
  return queue_price_.Mutable(index);
}
inline ::CommonGiftConfig::CommonModifyItem* EquipLine::add_queue_price() {
  // @@protoc_insertion_point(field_add:ConfigProductLine.EquipLine.queue_price)
  return queue_price_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::CommonGiftConfig::CommonModifyItem >&
EquipLine::queue_price() const {
  // @@protoc_insertion_point(field_list:ConfigProductLine.EquipLine.queue_price)
  return queue_price_;
}
inline ::google::protobuf::RepeatedPtrField< ::CommonGiftConfig::CommonModifyItem >*
EquipLine::mutable_queue_price() {
  // @@protoc_insertion_point(field_mutable_list:ConfigProductLine.EquipLine.queue_price)
  return &queue_price_;
}

// -------------------------------------------------------------------

// AnimalLine

// required uint32 id = 1;
inline bool AnimalLine::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AnimalLine::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AnimalLine::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AnimalLine::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 AnimalLine::id() const {
  // @@protoc_insertion_point(field_get:ConfigProductLine.AnimalLine.id)
  return id_;
}
inline void AnimalLine::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:ConfigProductLine.AnimalLine.id)
}

// required uint32 fodder = 2;
inline bool AnimalLine::has_fodder() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AnimalLine::set_has_fodder() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AnimalLine::clear_has_fodder() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AnimalLine::clear_fodder() {
  fodder_ = 0u;
  clear_has_fodder();
}
inline ::google::protobuf::uint32 AnimalLine::fodder() const {
  // @@protoc_insertion_point(field_get:ConfigProductLine.AnimalLine.fodder)
  return fodder_;
}
inline void AnimalLine::set_fodder(::google::protobuf::uint32 value) {
  set_has_fodder();
  fodder_ = value;
  // @@protoc_insertion_point(field_set:ConfigProductLine.AnimalLine.fodder)
}

// required .CommonGiftConfig.CommonModifyItem product = 3;
inline bool AnimalLine::has_product() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void AnimalLine::set_has_product() {
  _has_bits_[0] |= 0x00000004u;
}
inline void AnimalLine::clear_has_product() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void AnimalLine::clear_product() {
  if (product_ != NULL) product_->::CommonGiftConfig::CommonModifyItem::Clear();
  clear_has_product();
}
inline const ::CommonGiftConfig::CommonModifyItem& AnimalLine::product() const {
  // @@protoc_insertion_point(field_get:ConfigProductLine.AnimalLine.product)
  return product_ != NULL ? *product_ : *default_instance_->product_;
}
inline ::CommonGiftConfig::CommonModifyItem* AnimalLine::mutable_product() {
  set_has_product();
  if (product_ == NULL) product_ = new ::CommonGiftConfig::CommonModifyItem;
  // @@protoc_insertion_point(field_mutable:ConfigProductLine.AnimalLine.product)
  return product_;
}
inline ::CommonGiftConfig::CommonModifyItem* AnimalLine::release_product() {
  clear_has_product();
  ::CommonGiftConfig::CommonModifyItem* temp = product_;
  product_ = NULL;
  return temp;
}
inline void AnimalLine::set_allocated_product(::CommonGiftConfig::CommonModifyItem* product) {
  delete product_;
  product_ = product;
  if (product) {
    set_has_product();
  } else {
    clear_has_product();
  }
  // @@protoc_insertion_point(field_set_allocated:ConfigProductLine.AnimalLine.product)
}

// -------------------------------------------------------------------

// ProductLine

// repeated .ConfigProductLine.EquipLine equipline = 1;
inline int ProductLine::equipline_size() const {
  return equipline_.size();
}
inline void ProductLine::clear_equipline() {
  equipline_.Clear();
}
inline const ::ConfigProductLine::EquipLine& ProductLine::equipline(int index) const {
  // @@protoc_insertion_point(field_get:ConfigProductLine.ProductLine.equipline)
  return equipline_.Get(index);
}
inline ::ConfigProductLine::EquipLine* ProductLine::mutable_equipline(int index) {
  // @@protoc_insertion_point(field_mutable:ConfigProductLine.ProductLine.equipline)
  return equipline_.Mutable(index);
}
inline ::ConfigProductLine::EquipLine* ProductLine::add_equipline() {
  // @@protoc_insertion_point(field_add:ConfigProductLine.ProductLine.equipline)
  return equipline_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ConfigProductLine::EquipLine >&
ProductLine::equipline() const {
  // @@protoc_insertion_point(field_list:ConfigProductLine.ProductLine.equipline)
  return equipline_;
}
inline ::google::protobuf::RepeatedPtrField< ::ConfigProductLine::EquipLine >*
ProductLine::mutable_equipline() {
  // @@protoc_insertion_point(field_mutable_list:ConfigProductLine.ProductLine.equipline)
  return &equipline_;
}

// repeated .ConfigProductLine.AnimalLine animal_line = 2;
inline int ProductLine::animal_line_size() const {
  return animal_line_.size();
}
inline void ProductLine::clear_animal_line() {
  animal_line_.Clear();
}
inline const ::ConfigProductLine::AnimalLine& ProductLine::animal_line(int index) const {
  // @@protoc_insertion_point(field_get:ConfigProductLine.ProductLine.animal_line)
  return animal_line_.Get(index);
}
inline ::ConfigProductLine::AnimalLine* ProductLine::mutable_animal_line(int index) {
  // @@protoc_insertion_point(field_mutable:ConfigProductLine.ProductLine.animal_line)
  return animal_line_.Mutable(index);
}
inline ::ConfigProductLine::AnimalLine* ProductLine::add_animal_line() {
  // @@protoc_insertion_point(field_add:ConfigProductLine.ProductLine.animal_line)
  return animal_line_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ConfigProductLine::AnimalLine >&
ProductLine::animal_line() const {
  // @@protoc_insertion_point(field_list:ConfigProductLine.ProductLine.animal_line)
  return animal_line_;
}
inline ::google::protobuf::RepeatedPtrField< ::ConfigProductLine::AnimalLine >*
ProductLine::mutable_animal_line() {
  // @@protoc_insertion_point(field_mutable_list:ConfigProductLine.ProductLine.animal_line)
  return &animal_line_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ConfigProductLine

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ConfigProductLine_2eproto__INCLUDED
