// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProtoPush.proto

#ifndef PROTOBUF_ProtoPush_2eproto__INCLUDED
#define PROTOBUF_ProtoPush_2eproto__INCLUDED

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
#include "ProtoBuilding.pb.h"
#include "ProtoProduce.pb.h"
#include "DataCommon.pb.h"
#include "ProtoOrder.pb.h"
#include "ProtoShipping.pb.h"
// @@protoc_insertion_point(includes)

namespace ProtoPush {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ProtoPush_2eproto();
void protobuf_AssignDesc_ProtoPush_2eproto();
void protobuf_ShutdownFile_ProtoPush_2eproto();

class PushBuildingsCPP;
class PushUserUpLevel;
class RewardLevelUpReq;
class RewardLevelUpResp;
class PushOnceEveryDayReward;

// ===================================================================

class PushBuildingsCPP : public ::google::protobuf::Message {
 public:
  PushBuildingsCPP();
  virtual ~PushBuildingsCPP();
  
  PushBuildingsCPP(const PushBuildingsCPP& from);
  
  inline PushBuildingsCPP& operator=(const PushBuildingsCPP& from) {
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
  static const PushBuildingsCPP& default_instance();
  
  void Swap(PushBuildingsCPP* other);
  
  // implements Message ----------------------------------------------
  
  PushBuildingsCPP* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PushBuildingsCPP& from);
  void MergeFrom(const PushBuildingsCPP& from);
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
  
  // repeated .ProtoBuilding.BuildingCPP buildings = 1;
  inline int buildings_size() const;
  inline void clear_buildings();
  static const int kBuildingsFieldNumber = 1;
  inline const ::ProtoBuilding::BuildingCPP& buildings(int index) const;
  inline ::ProtoBuilding::BuildingCPP* mutable_buildings(int index);
  inline ::ProtoBuilding::BuildingCPP* add_buildings();
  inline const ::google::protobuf::RepeatedPtrField< ::ProtoBuilding::BuildingCPP >&
      buildings() const;
  inline ::google::protobuf::RepeatedPtrField< ::ProtoBuilding::BuildingCPP >*
      mutable_buildings();
  
  // repeated .ProtoProduce.CropLandCPP croplands = 2;
  inline int croplands_size() const;
  inline void clear_croplands();
  static const int kCroplandsFieldNumber = 2;
  inline const ::ProtoProduce::CropLandCPP& croplands(int index) const;
  inline ::ProtoProduce::CropLandCPP* mutable_croplands(int index);
  inline ::ProtoProduce::CropLandCPP* add_croplands();
  inline const ::google::protobuf::RepeatedPtrField< ::ProtoProduce::CropLandCPP >&
      croplands() const;
  inline ::google::protobuf::RepeatedPtrField< ::ProtoProduce::CropLandCPP >*
      mutable_croplands();
  
  // repeated .ProtoProduce.ProduceEquipCPP equipments = 3;
  inline int equipments_size() const;
  inline void clear_equipments();
  static const int kEquipmentsFieldNumber = 3;
  inline const ::ProtoProduce::ProduceEquipCPP& equipments(int index) const;
  inline ::ProtoProduce::ProduceEquipCPP* mutable_equipments(int index);
  inline ::ProtoProduce::ProduceEquipCPP* add_equipments();
  inline const ::google::protobuf::RepeatedPtrField< ::ProtoProduce::ProduceEquipCPP >&
      equipments() const;
  inline ::google::protobuf::RepeatedPtrField< ::ProtoProduce::ProduceEquipCPP >*
      mutable_equipments();
  
  // repeated .ProtoProduce.AnimalCPP animals = 4;
  inline int animals_size() const;
  inline void clear_animals();
  static const int kAnimalsFieldNumber = 4;
  inline const ::ProtoProduce::AnimalCPP& animals(int index) const;
  inline ::ProtoProduce::AnimalCPP* mutable_animals(int index);
  inline ::ProtoProduce::AnimalCPP* add_animals();
  inline const ::google::protobuf::RepeatedPtrField< ::ProtoProduce::AnimalCPP >&
      animals() const;
  inline ::google::protobuf::RepeatedPtrField< ::ProtoProduce::AnimalCPP >*
      mutable_animals();
  
  // repeated .ProtoBuilding.EquipmentStarCPP equipmentstar = 5;
  inline int equipmentstar_size() const;
  inline void clear_equipmentstar();
  static const int kEquipmentstarFieldNumber = 5;
  inline const ::ProtoBuilding::EquipmentStarCPP& equipmentstar(int index) const;
  inline ::ProtoBuilding::EquipmentStarCPP* mutable_equipmentstar(int index);
  inline ::ProtoBuilding::EquipmentStarCPP* add_equipmentstar();
  inline const ::google::protobuf::RepeatedPtrField< ::ProtoBuilding::EquipmentStarCPP >&
      equipmentstar() const;
  inline ::google::protobuf::RepeatedPtrField< ::ProtoBuilding::EquipmentStarCPP >*
      mutable_equipmentstar();
  
  // repeated .ProtoProduce.FruitCPP fruits = 6;
  inline int fruits_size() const;
  inline void clear_fruits();
  static const int kFruitsFieldNumber = 6;
  inline const ::ProtoProduce::FruitCPP& fruits(int index) const;
  inline ::ProtoProduce::FruitCPP* mutable_fruits(int index);
  inline ::ProtoProduce::FruitCPP* add_fruits();
  inline const ::google::protobuf::RepeatedPtrField< ::ProtoProduce::FruitCPP >&
      fruits() const;
  inline ::google::protobuf::RepeatedPtrField< ::ProtoProduce::FruitCPP >*
      mutable_fruits();
  
  // repeated .ProtoOrder.OrderCPP orders = 7;
  inline int orders_size() const;
  inline void clear_orders();
  static const int kOrdersFieldNumber = 7;
  inline const ::ProtoOrder::OrderCPP& orders(int index) const;
  inline ::ProtoOrder::OrderCPP* mutable_orders(int index);
  inline ::ProtoOrder::OrderCPP* add_orders();
  inline const ::google::protobuf::RepeatedPtrField< ::ProtoOrder::OrderCPP >&
      orders() const;
  inline ::google::protobuf::RepeatedPtrField< ::ProtoOrder::OrderCPP >*
      mutable_orders();
  
  // optional .ProtoOrder.TruckCPP truck = 8;
  inline bool has_truck() const;
  inline void clear_truck();
  static const int kTruckFieldNumber = 8;
  inline const ::ProtoOrder::TruckCPP& truck() const;
  inline ::ProtoOrder::TruckCPP* mutable_truck();
  inline ::ProtoOrder::TruckCPP* release_truck();
  
  // optional .ProtoShipping.ShippingCPP shipping = 9;
  inline bool has_shipping() const;
  inline void clear_shipping();
  static const int kShippingFieldNumber = 9;
  inline const ::ProtoShipping::ShippingCPP& shipping() const;
  inline ::ProtoShipping::ShippingCPP* mutable_shipping();
  inline ::ProtoShipping::ShippingCPP* release_shipping();
  
  // repeated .ProtoShipping.ShippingBoxCPP shipboxes = 10;
  inline int shipboxes_size() const;
  inline void clear_shipboxes();
  static const int kShipboxesFieldNumber = 10;
  inline const ::ProtoShipping::ShippingBoxCPP& shipboxes(int index) const;
  inline ::ProtoShipping::ShippingBoxCPP* mutable_shipboxes(int index);
  inline ::ProtoShipping::ShippingBoxCPP* add_shipboxes();
  inline const ::google::protobuf::RepeatedPtrField< ::ProtoShipping::ShippingBoxCPP >&
      shipboxes() const;
  inline ::google::protobuf::RepeatedPtrField< ::ProtoShipping::ShippingBoxCPP >*
      mutable_shipboxes();
  
  // optional .DataCommon.CommonItemsCPP commons = 11;
  inline bool has_commons() const;
  inline void clear_commons();
  static const int kCommonsFieldNumber = 11;
  inline const ::DataCommon::CommonItemsCPP& commons() const;
  inline ::DataCommon::CommonItemsCPP* mutable_commons();
  inline ::DataCommon::CommonItemsCPP* release_commons();
  
  // @@protoc_insertion_point(class_scope:ProtoPush.PushBuildingsCPP)
 private:
  inline void set_has_truck();
  inline void clear_has_truck();
  inline void set_has_shipping();
  inline void clear_has_shipping();
  inline void set_has_commons();
  inline void clear_has_commons();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::ProtoBuilding::BuildingCPP > buildings_;
  ::google::protobuf::RepeatedPtrField< ::ProtoProduce::CropLandCPP > croplands_;
  ::google::protobuf::RepeatedPtrField< ::ProtoProduce::ProduceEquipCPP > equipments_;
  ::google::protobuf::RepeatedPtrField< ::ProtoProduce::AnimalCPP > animals_;
  ::google::protobuf::RepeatedPtrField< ::ProtoBuilding::EquipmentStarCPP > equipmentstar_;
  ::google::protobuf::RepeatedPtrField< ::ProtoProduce::FruitCPP > fruits_;
  ::google::protobuf::RepeatedPtrField< ::ProtoOrder::OrderCPP > orders_;
  ::ProtoOrder::TruckCPP* truck_;
  ::ProtoShipping::ShippingCPP* shipping_;
  ::google::protobuf::RepeatedPtrField< ::ProtoShipping::ShippingBoxCPP > shipboxes_;
  ::DataCommon::CommonItemsCPP* commons_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(11 + 31) / 32];
  
  friend void  protobuf_AddDesc_ProtoPush_2eproto();
  friend void protobuf_AssignDesc_ProtoPush_2eproto();
  friend void protobuf_ShutdownFile_ProtoPush_2eproto();
  
  void InitAsDefaultInstance();
  static PushBuildingsCPP* default_instance_;
};
// -------------------------------------------------------------------

class PushUserUpLevel : public ::google::protobuf::Message {
 public:
  PushUserUpLevel();
  virtual ~PushUserUpLevel();
  
  PushUserUpLevel(const PushUserUpLevel& from);
  
  inline PushUserUpLevel& operator=(const PushUserUpLevel& from) {
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
  static const PushUserUpLevel& default_instance();
  
  void Swap(PushUserUpLevel* other);
  
  // implements Message ----------------------------------------------
  
  PushUserUpLevel* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PushUserUpLevel& from);
  void MergeFrom(const PushUserUpLevel& from);
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
  
  // required .DataCommon.CommonItemsCPP commons = 1;
  inline bool has_commons() const;
  inline void clear_commons();
  static const int kCommonsFieldNumber = 1;
  inline const ::DataCommon::CommonItemsCPP& commons() const;
  inline ::DataCommon::CommonItemsCPP* mutable_commons();
  inline ::DataCommon::CommonItemsCPP* release_commons();
  
  // @@protoc_insertion_point(class_scope:ProtoPush.PushUserUpLevel)
 private:
  inline void set_has_commons();
  inline void clear_has_commons();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::DataCommon::CommonItemsCPP* commons_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_ProtoPush_2eproto();
  friend void protobuf_AssignDesc_ProtoPush_2eproto();
  friend void protobuf_ShutdownFile_ProtoPush_2eproto();
  
  void InitAsDefaultInstance();
  static PushUserUpLevel* default_instance_;
};
// -------------------------------------------------------------------

class RewardLevelUpReq : public ::google::protobuf::Message {
 public:
  RewardLevelUpReq();
  virtual ~RewardLevelUpReq();
  
  RewardLevelUpReq(const RewardLevelUpReq& from);
  
  inline RewardLevelUpReq& operator=(const RewardLevelUpReq& from) {
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
  static const RewardLevelUpReq& default_instance();
  
  void Swap(RewardLevelUpReq* other);
  
  // implements Message ----------------------------------------------
  
  RewardLevelUpReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RewardLevelUpReq& from);
  void MergeFrom(const RewardLevelUpReq& from);
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
  
  // @@protoc_insertion_point(class_scope:ProtoPush.RewardLevelUpReq)
 private:
  inline void set_has_type();
  inline void clear_has_type();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint32 type_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_ProtoPush_2eproto();
  friend void protobuf_AssignDesc_ProtoPush_2eproto();
  friend void protobuf_ShutdownFile_ProtoPush_2eproto();
  
  void InitAsDefaultInstance();
  static RewardLevelUpReq* default_instance_;
};
// -------------------------------------------------------------------

class RewardLevelUpResp : public ::google::protobuf::Message {
 public:
  RewardLevelUpResp();
  virtual ~RewardLevelUpResp();
  
  RewardLevelUpResp(const RewardLevelUpResp& from);
  
  inline RewardLevelUpResp& operator=(const RewardLevelUpResp& from) {
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
  static const RewardLevelUpResp& default_instance();
  
  void Swap(RewardLevelUpResp* other);
  
  // implements Message ----------------------------------------------
  
  RewardLevelUpResp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RewardLevelUpResp& from);
  void MergeFrom(const RewardLevelUpResp& from);
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
  
  // required .DataCommon.CommonItemsCPP commons = 1;
  inline bool has_commons() const;
  inline void clear_commons();
  static const int kCommonsFieldNumber = 1;
  inline const ::DataCommon::CommonItemsCPP& commons() const;
  inline ::DataCommon::CommonItemsCPP* mutable_commons();
  inline ::DataCommon::CommonItemsCPP* release_commons();
  
  // @@protoc_insertion_point(class_scope:ProtoPush.RewardLevelUpResp)
 private:
  inline void set_has_commons();
  inline void clear_has_commons();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::DataCommon::CommonItemsCPP* commons_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_ProtoPush_2eproto();
  friend void protobuf_AssignDesc_ProtoPush_2eproto();
  friend void protobuf_ShutdownFile_ProtoPush_2eproto();
  
  void InitAsDefaultInstance();
  static RewardLevelUpResp* default_instance_;
};
// -------------------------------------------------------------------

class PushOnceEveryDayReward : public ::google::protobuf::Message {
 public:
  PushOnceEveryDayReward();
  virtual ~PushOnceEveryDayReward();
  
  PushOnceEveryDayReward(const PushOnceEveryDayReward& from);
  
  inline PushOnceEveryDayReward& operator=(const PushOnceEveryDayReward& from) {
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
  static const PushOnceEveryDayReward& default_instance();
  
  void Swap(PushOnceEveryDayReward* other);
  
  // implements Message ----------------------------------------------
  
  PushOnceEveryDayReward* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PushOnceEveryDayReward& from);
  void MergeFrom(const PushOnceEveryDayReward& from);
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
  
  // @@protoc_insertion_point(class_scope:ProtoPush.PushOnceEveryDayReward)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[1];
  
  friend void  protobuf_AddDesc_ProtoPush_2eproto();
  friend void protobuf_AssignDesc_ProtoPush_2eproto();
  friend void protobuf_ShutdownFile_ProtoPush_2eproto();
  
  void InitAsDefaultInstance();
  static PushOnceEveryDayReward* default_instance_;
};
// ===================================================================


// ===================================================================

// PushBuildingsCPP

// repeated .ProtoBuilding.BuildingCPP buildings = 1;
inline int PushBuildingsCPP::buildings_size() const {
  return buildings_.size();
}
inline void PushBuildingsCPP::clear_buildings() {
  buildings_.Clear();
}
inline const ::ProtoBuilding::BuildingCPP& PushBuildingsCPP::buildings(int index) const {
  return buildings_.Get(index);
}
inline ::ProtoBuilding::BuildingCPP* PushBuildingsCPP::mutable_buildings(int index) {
  return buildings_.Mutable(index);
}
inline ::ProtoBuilding::BuildingCPP* PushBuildingsCPP::add_buildings() {
  return buildings_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ProtoBuilding::BuildingCPP >&
PushBuildingsCPP::buildings() const {
  return buildings_;
}
inline ::google::protobuf::RepeatedPtrField< ::ProtoBuilding::BuildingCPP >*
PushBuildingsCPP::mutable_buildings() {
  return &buildings_;
}

// repeated .ProtoProduce.CropLandCPP croplands = 2;
inline int PushBuildingsCPP::croplands_size() const {
  return croplands_.size();
}
inline void PushBuildingsCPP::clear_croplands() {
  croplands_.Clear();
}
inline const ::ProtoProduce::CropLandCPP& PushBuildingsCPP::croplands(int index) const {
  return croplands_.Get(index);
}
inline ::ProtoProduce::CropLandCPP* PushBuildingsCPP::mutable_croplands(int index) {
  return croplands_.Mutable(index);
}
inline ::ProtoProduce::CropLandCPP* PushBuildingsCPP::add_croplands() {
  return croplands_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ProtoProduce::CropLandCPP >&
PushBuildingsCPP::croplands() const {
  return croplands_;
}
inline ::google::protobuf::RepeatedPtrField< ::ProtoProduce::CropLandCPP >*
PushBuildingsCPP::mutable_croplands() {
  return &croplands_;
}

// repeated .ProtoProduce.ProduceEquipCPP equipments = 3;
inline int PushBuildingsCPP::equipments_size() const {
  return equipments_.size();
}
inline void PushBuildingsCPP::clear_equipments() {
  equipments_.Clear();
}
inline const ::ProtoProduce::ProduceEquipCPP& PushBuildingsCPP::equipments(int index) const {
  return equipments_.Get(index);
}
inline ::ProtoProduce::ProduceEquipCPP* PushBuildingsCPP::mutable_equipments(int index) {
  return equipments_.Mutable(index);
}
inline ::ProtoProduce::ProduceEquipCPP* PushBuildingsCPP::add_equipments() {
  return equipments_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ProtoProduce::ProduceEquipCPP >&
PushBuildingsCPP::equipments() const {
  return equipments_;
}
inline ::google::protobuf::RepeatedPtrField< ::ProtoProduce::ProduceEquipCPP >*
PushBuildingsCPP::mutable_equipments() {
  return &equipments_;
}

// repeated .ProtoProduce.AnimalCPP animals = 4;
inline int PushBuildingsCPP::animals_size() const {
  return animals_.size();
}
inline void PushBuildingsCPP::clear_animals() {
  animals_.Clear();
}
inline const ::ProtoProduce::AnimalCPP& PushBuildingsCPP::animals(int index) const {
  return animals_.Get(index);
}
inline ::ProtoProduce::AnimalCPP* PushBuildingsCPP::mutable_animals(int index) {
  return animals_.Mutable(index);
}
inline ::ProtoProduce::AnimalCPP* PushBuildingsCPP::add_animals() {
  return animals_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ProtoProduce::AnimalCPP >&
PushBuildingsCPP::animals() const {
  return animals_;
}
inline ::google::protobuf::RepeatedPtrField< ::ProtoProduce::AnimalCPP >*
PushBuildingsCPP::mutable_animals() {
  return &animals_;
}

// repeated .ProtoBuilding.EquipmentStarCPP equipmentstar = 5;
inline int PushBuildingsCPP::equipmentstar_size() const {
  return equipmentstar_.size();
}
inline void PushBuildingsCPP::clear_equipmentstar() {
  equipmentstar_.Clear();
}
inline const ::ProtoBuilding::EquipmentStarCPP& PushBuildingsCPP::equipmentstar(int index) const {
  return equipmentstar_.Get(index);
}
inline ::ProtoBuilding::EquipmentStarCPP* PushBuildingsCPP::mutable_equipmentstar(int index) {
  return equipmentstar_.Mutable(index);
}
inline ::ProtoBuilding::EquipmentStarCPP* PushBuildingsCPP::add_equipmentstar() {
  return equipmentstar_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ProtoBuilding::EquipmentStarCPP >&
PushBuildingsCPP::equipmentstar() const {
  return equipmentstar_;
}
inline ::google::protobuf::RepeatedPtrField< ::ProtoBuilding::EquipmentStarCPP >*
PushBuildingsCPP::mutable_equipmentstar() {
  return &equipmentstar_;
}

// repeated .ProtoProduce.FruitCPP fruits = 6;
inline int PushBuildingsCPP::fruits_size() const {
  return fruits_.size();
}
inline void PushBuildingsCPP::clear_fruits() {
  fruits_.Clear();
}
inline const ::ProtoProduce::FruitCPP& PushBuildingsCPP::fruits(int index) const {
  return fruits_.Get(index);
}
inline ::ProtoProduce::FruitCPP* PushBuildingsCPP::mutable_fruits(int index) {
  return fruits_.Mutable(index);
}
inline ::ProtoProduce::FruitCPP* PushBuildingsCPP::add_fruits() {
  return fruits_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ProtoProduce::FruitCPP >&
PushBuildingsCPP::fruits() const {
  return fruits_;
}
inline ::google::protobuf::RepeatedPtrField< ::ProtoProduce::FruitCPP >*
PushBuildingsCPP::mutable_fruits() {
  return &fruits_;
}

// repeated .ProtoOrder.OrderCPP orders = 7;
inline int PushBuildingsCPP::orders_size() const {
  return orders_.size();
}
inline void PushBuildingsCPP::clear_orders() {
  orders_.Clear();
}
inline const ::ProtoOrder::OrderCPP& PushBuildingsCPP::orders(int index) const {
  return orders_.Get(index);
}
inline ::ProtoOrder::OrderCPP* PushBuildingsCPP::mutable_orders(int index) {
  return orders_.Mutable(index);
}
inline ::ProtoOrder::OrderCPP* PushBuildingsCPP::add_orders() {
  return orders_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ProtoOrder::OrderCPP >&
PushBuildingsCPP::orders() const {
  return orders_;
}
inline ::google::protobuf::RepeatedPtrField< ::ProtoOrder::OrderCPP >*
PushBuildingsCPP::mutable_orders() {
  return &orders_;
}

// optional .ProtoOrder.TruckCPP truck = 8;
inline bool PushBuildingsCPP::has_truck() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void PushBuildingsCPP::set_has_truck() {
  _has_bits_[0] |= 0x00000080u;
}
inline void PushBuildingsCPP::clear_has_truck() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void PushBuildingsCPP::clear_truck() {
  if (truck_ != NULL) truck_->::ProtoOrder::TruckCPP::Clear();
  clear_has_truck();
}
inline const ::ProtoOrder::TruckCPP& PushBuildingsCPP::truck() const {
  return truck_ != NULL ? *truck_ : *default_instance_->truck_;
}
inline ::ProtoOrder::TruckCPP* PushBuildingsCPP::mutable_truck() {
  set_has_truck();
  if (truck_ == NULL) truck_ = new ::ProtoOrder::TruckCPP;
  return truck_;
}
inline ::ProtoOrder::TruckCPP* PushBuildingsCPP::release_truck() {
  clear_has_truck();
  ::ProtoOrder::TruckCPP* temp = truck_;
  truck_ = NULL;
  return temp;
}

// optional .ProtoShipping.ShippingCPP shipping = 9;
inline bool PushBuildingsCPP::has_shipping() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void PushBuildingsCPP::set_has_shipping() {
  _has_bits_[0] |= 0x00000100u;
}
inline void PushBuildingsCPP::clear_has_shipping() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void PushBuildingsCPP::clear_shipping() {
  if (shipping_ != NULL) shipping_->::ProtoShipping::ShippingCPP::Clear();
  clear_has_shipping();
}
inline const ::ProtoShipping::ShippingCPP& PushBuildingsCPP::shipping() const {
  return shipping_ != NULL ? *shipping_ : *default_instance_->shipping_;
}
inline ::ProtoShipping::ShippingCPP* PushBuildingsCPP::mutable_shipping() {
  set_has_shipping();
  if (shipping_ == NULL) shipping_ = new ::ProtoShipping::ShippingCPP;
  return shipping_;
}
inline ::ProtoShipping::ShippingCPP* PushBuildingsCPP::release_shipping() {
  clear_has_shipping();
  ::ProtoShipping::ShippingCPP* temp = shipping_;
  shipping_ = NULL;
  return temp;
}

// repeated .ProtoShipping.ShippingBoxCPP shipboxes = 10;
inline int PushBuildingsCPP::shipboxes_size() const {
  return shipboxes_.size();
}
inline void PushBuildingsCPP::clear_shipboxes() {
  shipboxes_.Clear();
}
inline const ::ProtoShipping::ShippingBoxCPP& PushBuildingsCPP::shipboxes(int index) const {
  return shipboxes_.Get(index);
}
inline ::ProtoShipping::ShippingBoxCPP* PushBuildingsCPP::mutable_shipboxes(int index) {
  return shipboxes_.Mutable(index);
}
inline ::ProtoShipping::ShippingBoxCPP* PushBuildingsCPP::add_shipboxes() {
  return shipboxes_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ProtoShipping::ShippingBoxCPP >&
PushBuildingsCPP::shipboxes() const {
  return shipboxes_;
}
inline ::google::protobuf::RepeatedPtrField< ::ProtoShipping::ShippingBoxCPP >*
PushBuildingsCPP::mutable_shipboxes() {
  return &shipboxes_;
}

// optional .DataCommon.CommonItemsCPP commons = 11;
inline bool PushBuildingsCPP::has_commons() const {
  return (_has_bits_[0] & 0x00000400u) != 0;
}
inline void PushBuildingsCPP::set_has_commons() {
  _has_bits_[0] |= 0x00000400u;
}
inline void PushBuildingsCPP::clear_has_commons() {
  _has_bits_[0] &= ~0x00000400u;
}
inline void PushBuildingsCPP::clear_commons() {
  if (commons_ != NULL) commons_->::DataCommon::CommonItemsCPP::Clear();
  clear_has_commons();
}
inline const ::DataCommon::CommonItemsCPP& PushBuildingsCPP::commons() const {
  return commons_ != NULL ? *commons_ : *default_instance_->commons_;
}
inline ::DataCommon::CommonItemsCPP* PushBuildingsCPP::mutable_commons() {
  set_has_commons();
  if (commons_ == NULL) commons_ = new ::DataCommon::CommonItemsCPP;
  return commons_;
}
inline ::DataCommon::CommonItemsCPP* PushBuildingsCPP::release_commons() {
  clear_has_commons();
  ::DataCommon::CommonItemsCPP* temp = commons_;
  commons_ = NULL;
  return temp;
}

// -------------------------------------------------------------------

// PushUserUpLevel

// required .DataCommon.CommonItemsCPP commons = 1;
inline bool PushUserUpLevel::has_commons() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PushUserUpLevel::set_has_commons() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PushUserUpLevel::clear_has_commons() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PushUserUpLevel::clear_commons() {
  if (commons_ != NULL) commons_->::DataCommon::CommonItemsCPP::Clear();
  clear_has_commons();
}
inline const ::DataCommon::CommonItemsCPP& PushUserUpLevel::commons() const {
  return commons_ != NULL ? *commons_ : *default_instance_->commons_;
}
inline ::DataCommon::CommonItemsCPP* PushUserUpLevel::mutable_commons() {
  set_has_commons();
  if (commons_ == NULL) commons_ = new ::DataCommon::CommonItemsCPP;
  return commons_;
}
inline ::DataCommon::CommonItemsCPP* PushUserUpLevel::release_commons() {
  clear_has_commons();
  ::DataCommon::CommonItemsCPP* temp = commons_;
  commons_ = NULL;
  return temp;
}

// -------------------------------------------------------------------

// RewardLevelUpReq

// required uint32 type = 1;
inline bool RewardLevelUpReq::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RewardLevelUpReq::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RewardLevelUpReq::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RewardLevelUpReq::clear_type() {
  type_ = 0u;
  clear_has_type();
}
inline ::google::protobuf::uint32 RewardLevelUpReq::type() const {
  return type_;
}
inline void RewardLevelUpReq::set_type(::google::protobuf::uint32 value) {
  set_has_type();
  type_ = value;
}

// -------------------------------------------------------------------

// RewardLevelUpResp

// required .DataCommon.CommonItemsCPP commons = 1;
inline bool RewardLevelUpResp::has_commons() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RewardLevelUpResp::set_has_commons() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RewardLevelUpResp::clear_has_commons() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RewardLevelUpResp::clear_commons() {
  if (commons_ != NULL) commons_->::DataCommon::CommonItemsCPP::Clear();
  clear_has_commons();
}
inline const ::DataCommon::CommonItemsCPP& RewardLevelUpResp::commons() const {
  return commons_ != NULL ? *commons_ : *default_instance_->commons_;
}
inline ::DataCommon::CommonItemsCPP* RewardLevelUpResp::mutable_commons() {
  set_has_commons();
  if (commons_ == NULL) commons_ = new ::DataCommon::CommonItemsCPP;
  return commons_;
}
inline ::DataCommon::CommonItemsCPP* RewardLevelUpResp::release_commons() {
  clear_has_commons();
  ::DataCommon::CommonItemsCPP* temp = commons_;
  commons_ = NULL;
  return temp;
}

// -------------------------------------------------------------------

// PushOnceEveryDayReward


// @@protoc_insertion_point(namespace_scope)

}  // namespace ProtoPush

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ProtoPush_2eproto__INCLUDED
