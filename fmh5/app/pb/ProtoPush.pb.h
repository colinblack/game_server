// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProtoPush.proto

#ifndef PROTOBUF_ProtoPush_2eproto__INCLUDED
#define PROTOBUF_ProtoPush_2eproto__INCLUDED

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
#include "ProtoBuilding.pb.h"
#include "ProtoProduce.pb.h"
#include "DataCommon.pb.h"
// @@protoc_insertion_point(includes)

namespace ProtoPush {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ProtoPush_2eproto();
void protobuf_AssignDesc_ProtoPush_2eproto();
void protobuf_ShutdownFile_ProtoPush_2eproto();

class PushBuildingsCPP;
class PushUserUpLevel;
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

  // @@protoc_insertion_point(class_scope:ProtoPush.PushBuildingsCPP)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::ProtoBuilding::BuildingCPP > buildings_;
  ::google::protobuf::RepeatedPtrField< ::ProtoProduce::CropLandCPP > croplands_;
  ::google::protobuf::RepeatedPtrField< ::ProtoProduce::ProduceEquipCPP > equipments_;
  ::google::protobuf::RepeatedPtrField< ::ProtoProduce::AnimalCPP > animals_;
  ::google::protobuf::RepeatedPtrField< ::ProtoBuilding::EquipmentStarCPP > equipmentstar_;
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
  inline void set_allocated_commons(::DataCommon::CommonItemsCPP* commons);

  // @@protoc_insertion_point(class_scope:ProtoPush.PushUserUpLevel)
 private:
  inline void set_has_commons();
  inline void clear_has_commons();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::DataCommon::CommonItemsCPP* commons_;
  friend void  protobuf_AddDesc_ProtoPush_2eproto();
  friend void protobuf_AssignDesc_ProtoPush_2eproto();
  friend void protobuf_ShutdownFile_ProtoPush_2eproto();

  void InitAsDefaultInstance();
  static PushUserUpLevel* default_instance_;
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

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
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
  // @@protoc_insertion_point(field_get:ProtoPush.PushBuildingsCPP.buildings)
  return buildings_.Get(index);
}
inline ::ProtoBuilding::BuildingCPP* PushBuildingsCPP::mutable_buildings(int index) {
  // @@protoc_insertion_point(field_mutable:ProtoPush.PushBuildingsCPP.buildings)
  return buildings_.Mutable(index);
}
inline ::ProtoBuilding::BuildingCPP* PushBuildingsCPP::add_buildings() {
  // @@protoc_insertion_point(field_add:ProtoPush.PushBuildingsCPP.buildings)
  return buildings_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ProtoBuilding::BuildingCPP >&
PushBuildingsCPP::buildings() const {
  // @@protoc_insertion_point(field_list:ProtoPush.PushBuildingsCPP.buildings)
  return buildings_;
}
inline ::google::protobuf::RepeatedPtrField< ::ProtoBuilding::BuildingCPP >*
PushBuildingsCPP::mutable_buildings() {
  // @@protoc_insertion_point(field_mutable_list:ProtoPush.PushBuildingsCPP.buildings)
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
  // @@protoc_insertion_point(field_get:ProtoPush.PushBuildingsCPP.croplands)
  return croplands_.Get(index);
}
inline ::ProtoProduce::CropLandCPP* PushBuildingsCPP::mutable_croplands(int index) {
  // @@protoc_insertion_point(field_mutable:ProtoPush.PushBuildingsCPP.croplands)
  return croplands_.Mutable(index);
}
inline ::ProtoProduce::CropLandCPP* PushBuildingsCPP::add_croplands() {
  // @@protoc_insertion_point(field_add:ProtoPush.PushBuildingsCPP.croplands)
  return croplands_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ProtoProduce::CropLandCPP >&
PushBuildingsCPP::croplands() const {
  // @@protoc_insertion_point(field_list:ProtoPush.PushBuildingsCPP.croplands)
  return croplands_;
}
inline ::google::protobuf::RepeatedPtrField< ::ProtoProduce::CropLandCPP >*
PushBuildingsCPP::mutable_croplands() {
  // @@protoc_insertion_point(field_mutable_list:ProtoPush.PushBuildingsCPP.croplands)
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
  // @@protoc_insertion_point(field_get:ProtoPush.PushBuildingsCPP.equipments)
  return equipments_.Get(index);
}
inline ::ProtoProduce::ProduceEquipCPP* PushBuildingsCPP::mutable_equipments(int index) {
  // @@protoc_insertion_point(field_mutable:ProtoPush.PushBuildingsCPP.equipments)
  return equipments_.Mutable(index);
}
inline ::ProtoProduce::ProduceEquipCPP* PushBuildingsCPP::add_equipments() {
  // @@protoc_insertion_point(field_add:ProtoPush.PushBuildingsCPP.equipments)
  return equipments_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ProtoProduce::ProduceEquipCPP >&
PushBuildingsCPP::equipments() const {
  // @@protoc_insertion_point(field_list:ProtoPush.PushBuildingsCPP.equipments)
  return equipments_;
}
inline ::google::protobuf::RepeatedPtrField< ::ProtoProduce::ProduceEquipCPP >*
PushBuildingsCPP::mutable_equipments() {
  // @@protoc_insertion_point(field_mutable_list:ProtoPush.PushBuildingsCPP.equipments)
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
  // @@protoc_insertion_point(field_get:ProtoPush.PushBuildingsCPP.animals)
  return animals_.Get(index);
}
inline ::ProtoProduce::AnimalCPP* PushBuildingsCPP::mutable_animals(int index) {
  // @@protoc_insertion_point(field_mutable:ProtoPush.PushBuildingsCPP.animals)
  return animals_.Mutable(index);
}
inline ::ProtoProduce::AnimalCPP* PushBuildingsCPP::add_animals() {
  // @@protoc_insertion_point(field_add:ProtoPush.PushBuildingsCPP.animals)
  return animals_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ProtoProduce::AnimalCPP >&
PushBuildingsCPP::animals() const {
  // @@protoc_insertion_point(field_list:ProtoPush.PushBuildingsCPP.animals)
  return animals_;
}
inline ::google::protobuf::RepeatedPtrField< ::ProtoProduce::AnimalCPP >*
PushBuildingsCPP::mutable_animals() {
  // @@protoc_insertion_point(field_mutable_list:ProtoPush.PushBuildingsCPP.animals)
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
  // @@protoc_insertion_point(field_get:ProtoPush.PushBuildingsCPP.equipmentstar)
  return equipmentstar_.Get(index);
}
inline ::ProtoBuilding::EquipmentStarCPP* PushBuildingsCPP::mutable_equipmentstar(int index) {
  // @@protoc_insertion_point(field_mutable:ProtoPush.PushBuildingsCPP.equipmentstar)
  return equipmentstar_.Mutable(index);
}
inline ::ProtoBuilding::EquipmentStarCPP* PushBuildingsCPP::add_equipmentstar() {
  // @@protoc_insertion_point(field_add:ProtoPush.PushBuildingsCPP.equipmentstar)
  return equipmentstar_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ProtoBuilding::EquipmentStarCPP >&
PushBuildingsCPP::equipmentstar() const {
  // @@protoc_insertion_point(field_list:ProtoPush.PushBuildingsCPP.equipmentstar)
  return equipmentstar_;
}
inline ::google::protobuf::RepeatedPtrField< ::ProtoBuilding::EquipmentStarCPP >*
PushBuildingsCPP::mutable_equipmentstar() {
  // @@protoc_insertion_point(field_mutable_list:ProtoPush.PushBuildingsCPP.equipmentstar)
  return &equipmentstar_;
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
  // @@protoc_insertion_point(field_get:ProtoPush.PushUserUpLevel.commons)
  return commons_ != NULL ? *commons_ : *default_instance_->commons_;
}
inline ::DataCommon::CommonItemsCPP* PushUserUpLevel::mutable_commons() {
  set_has_commons();
  if (commons_ == NULL) commons_ = new ::DataCommon::CommonItemsCPP;
  // @@protoc_insertion_point(field_mutable:ProtoPush.PushUserUpLevel.commons)
  return commons_;
}
inline ::DataCommon::CommonItemsCPP* PushUserUpLevel::release_commons() {
  clear_has_commons();
  ::DataCommon::CommonItemsCPP* temp = commons_;
  commons_ = NULL;
  return temp;
}
inline void PushUserUpLevel::set_allocated_commons(::DataCommon::CommonItemsCPP* commons) {
  delete commons_;
  commons_ = commons;
  if (commons) {
    set_has_commons();
  } else {
    clear_has_commons();
  }
  // @@protoc_insertion_point(field_set_allocated:ProtoPush.PushUserUpLevel.commons)
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
