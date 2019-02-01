// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProtoMission.proto

#ifndef PROTOBUF_ProtoMission_2eproto__INCLUDED
#define PROTOBUF_ProtoMission_2eproto__INCLUDED

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
#include "DataCommon.pb.h"
// @@protoc_insertion_point(includes)

namespace ProtoMission {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ProtoMission_2eproto();
void protobuf_AssignDesc_ProtoMission_2eproto();
void protobuf_ShutdownFile_ProtoMission_2eproto();

class MissionCPP;
class GetCurMissionReq;
class GetCurMissionResp;
class RewardMissionReq;
class RewardMissionResp;
class PushMission;

// ===================================================================

class MissionCPP : public ::google::protobuf::Message {
 public:
  MissionCPP();
  virtual ~MissionCPP();
  
  MissionCPP(const MissionCPP& from);
  
  inline MissionCPP& operator=(const MissionCPP& from) {
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
  static const MissionCPP& default_instance();
  
  void Swap(MissionCPP* other);
  
  // implements Message ----------------------------------------------
  
  MissionCPP* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MissionCPP& from);
  void MergeFrom(const MissionCPP& from);
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
  
  // required uint32 value = 2;
  inline bool has_value() const;
  inline void clear_value();
  static const int kValueFieldNumber = 2;
  inline ::google::protobuf::uint32 value() const;
  inline void set_value(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:ProtoMission.MissionCPP)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_value();
  inline void clear_has_value();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 value_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_ProtoMission_2eproto();
  friend void protobuf_AssignDesc_ProtoMission_2eproto();
  friend void protobuf_ShutdownFile_ProtoMission_2eproto();
  
  void InitAsDefaultInstance();
  static MissionCPP* default_instance_;
};
// -------------------------------------------------------------------

class GetCurMissionReq : public ::google::protobuf::Message {
 public:
  GetCurMissionReq();
  virtual ~GetCurMissionReq();
  
  GetCurMissionReq(const GetCurMissionReq& from);
  
  inline GetCurMissionReq& operator=(const GetCurMissionReq& from) {
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
  static const GetCurMissionReq& default_instance();
  
  void Swap(GetCurMissionReq* other);
  
  // implements Message ----------------------------------------------
  
  GetCurMissionReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GetCurMissionReq& from);
  void MergeFrom(const GetCurMissionReq& from);
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
  
  // @@protoc_insertion_point(class_scope:ProtoMission.GetCurMissionReq)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[1];
  
  friend void  protobuf_AddDesc_ProtoMission_2eproto();
  friend void protobuf_AssignDesc_ProtoMission_2eproto();
  friend void protobuf_ShutdownFile_ProtoMission_2eproto();
  
  void InitAsDefaultInstance();
  static GetCurMissionReq* default_instance_;
};
// -------------------------------------------------------------------

class GetCurMissionResp : public ::google::protobuf::Message {
 public:
  GetCurMissionResp();
  virtual ~GetCurMissionResp();
  
  GetCurMissionResp(const GetCurMissionResp& from);
  
  inline GetCurMissionResp& operator=(const GetCurMissionResp& from) {
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
  static const GetCurMissionResp& default_instance();
  
  void Swap(GetCurMissionResp* other);
  
  // implements Message ----------------------------------------------
  
  GetCurMissionResp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GetCurMissionResp& from);
  void MergeFrom(const GetCurMissionResp& from);
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
  
  // repeated .ProtoMission.MissionCPP misssion = 1;
  inline int misssion_size() const;
  inline void clear_misssion();
  static const int kMisssionFieldNumber = 1;
  inline const ::ProtoMission::MissionCPP& misssion(int index) const;
  inline ::ProtoMission::MissionCPP* mutable_misssion(int index);
  inline ::ProtoMission::MissionCPP* add_misssion();
  inline const ::google::protobuf::RepeatedPtrField< ::ProtoMission::MissionCPP >&
      misssion() const;
  inline ::google::protobuf::RepeatedPtrField< ::ProtoMission::MissionCPP >*
      mutable_misssion();
  
  // @@protoc_insertion_point(class_scope:ProtoMission.GetCurMissionResp)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::ProtoMission::MissionCPP > misssion_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_ProtoMission_2eproto();
  friend void protobuf_AssignDesc_ProtoMission_2eproto();
  friend void protobuf_ShutdownFile_ProtoMission_2eproto();
  
  void InitAsDefaultInstance();
  static GetCurMissionResp* default_instance_;
};
// -------------------------------------------------------------------

class RewardMissionReq : public ::google::protobuf::Message {
 public:
  RewardMissionReq();
  virtual ~RewardMissionReq();
  
  RewardMissionReq(const RewardMissionReq& from);
  
  inline RewardMissionReq& operator=(const RewardMissionReq& from) {
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
  static const RewardMissionReq& default_instance();
  
  void Swap(RewardMissionReq* other);
  
  // implements Message ----------------------------------------------
  
  RewardMissionReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RewardMissionReq& from);
  void MergeFrom(const RewardMissionReq& from);
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
  
  // required uint32 ud = 1;
  inline bool has_ud() const;
  inline void clear_ud();
  static const int kUdFieldNumber = 1;
  inline ::google::protobuf::uint32 ud() const;
  inline void set_ud(::google::protobuf::uint32 value);
  
  // required uint32 type = 2;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 2;
  inline ::google::protobuf::uint32 type() const;
  inline void set_type(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:ProtoMission.RewardMissionReq)
 private:
  inline void set_has_ud();
  inline void clear_has_ud();
  inline void set_has_type();
  inline void clear_has_type();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint32 ud_;
  ::google::protobuf::uint32 type_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_ProtoMission_2eproto();
  friend void protobuf_AssignDesc_ProtoMission_2eproto();
  friend void protobuf_ShutdownFile_ProtoMission_2eproto();
  
  void InitAsDefaultInstance();
  static RewardMissionReq* default_instance_;
};
// -------------------------------------------------------------------

class RewardMissionResp : public ::google::protobuf::Message {
 public:
  RewardMissionResp();
  virtual ~RewardMissionResp();
  
  RewardMissionResp(const RewardMissionResp& from);
  
  inline RewardMissionResp& operator=(const RewardMissionResp& from) {
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
  static const RewardMissionResp& default_instance();
  
  void Swap(RewardMissionResp* other);
  
  // implements Message ----------------------------------------------
  
  RewardMissionResp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RewardMissionResp& from);
  void MergeFrom(const RewardMissionResp& from);
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
  
  // repeated .ProtoMission.MissionCPP missions = 1;
  inline int missions_size() const;
  inline void clear_missions();
  static const int kMissionsFieldNumber = 1;
  inline const ::ProtoMission::MissionCPP& missions(int index) const;
  inline ::ProtoMission::MissionCPP* mutable_missions(int index);
  inline ::ProtoMission::MissionCPP* add_missions();
  inline const ::google::protobuf::RepeatedPtrField< ::ProtoMission::MissionCPP >&
      missions() const;
  inline ::google::protobuf::RepeatedPtrField< ::ProtoMission::MissionCPP >*
      mutable_missions();
  
  // required .DataCommon.CommonItemsCPP commons = 2;
  inline bool has_commons() const;
  inline void clear_commons();
  static const int kCommonsFieldNumber = 2;
  inline const ::DataCommon::CommonItemsCPP& commons() const;
  inline ::DataCommon::CommonItemsCPP* mutable_commons();
  inline ::DataCommon::CommonItemsCPP* release_commons();
  
  // @@protoc_insertion_point(class_scope:ProtoMission.RewardMissionResp)
 private:
  inline void set_has_commons();
  inline void clear_has_commons();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::ProtoMission::MissionCPP > missions_;
  ::DataCommon::CommonItemsCPP* commons_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_ProtoMission_2eproto();
  friend void protobuf_AssignDesc_ProtoMission_2eproto();
  friend void protobuf_ShutdownFile_ProtoMission_2eproto();
  
  void InitAsDefaultInstance();
  static RewardMissionResp* default_instance_;
};
// -------------------------------------------------------------------

class PushMission : public ::google::protobuf::Message {
 public:
  PushMission();
  virtual ~PushMission();
  
  PushMission(const PushMission& from);
  
  inline PushMission& operator=(const PushMission& from) {
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
  static const PushMission& default_instance();
  
  void Swap(PushMission* other);
  
  // implements Message ----------------------------------------------
  
  PushMission* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PushMission& from);
  void MergeFrom(const PushMission& from);
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
  
  // required .ProtoMission.MissionCPP mission = 1;
  inline bool has_mission() const;
  inline void clear_mission();
  static const int kMissionFieldNumber = 1;
  inline const ::ProtoMission::MissionCPP& mission() const;
  inline ::ProtoMission::MissionCPP* mutable_mission();
  inline ::ProtoMission::MissionCPP* release_mission();
  
  // @@protoc_insertion_point(class_scope:ProtoMission.PushMission)
 private:
  inline void set_has_mission();
  inline void clear_has_mission();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::ProtoMission::MissionCPP* mission_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_ProtoMission_2eproto();
  friend void protobuf_AssignDesc_ProtoMission_2eproto();
  friend void protobuf_ShutdownFile_ProtoMission_2eproto();
  
  void InitAsDefaultInstance();
  static PushMission* default_instance_;
};
// ===================================================================


// ===================================================================

// MissionCPP

// required uint32 id = 1;
inline bool MissionCPP::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MissionCPP::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MissionCPP::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MissionCPP::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 MissionCPP::id() const {
  return id_;
}
inline void MissionCPP::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// required uint32 value = 2;
inline bool MissionCPP::has_value() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MissionCPP::set_has_value() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MissionCPP::clear_has_value() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MissionCPP::clear_value() {
  value_ = 0u;
  clear_has_value();
}
inline ::google::protobuf::uint32 MissionCPP::value() const {
  return value_;
}
inline void MissionCPP::set_value(::google::protobuf::uint32 value) {
  set_has_value();
  value_ = value;
}

// -------------------------------------------------------------------

// GetCurMissionReq

// -------------------------------------------------------------------

// GetCurMissionResp

// repeated .ProtoMission.MissionCPP misssion = 1;
inline int GetCurMissionResp::misssion_size() const {
  return misssion_.size();
}
inline void GetCurMissionResp::clear_misssion() {
  misssion_.Clear();
}
inline const ::ProtoMission::MissionCPP& GetCurMissionResp::misssion(int index) const {
  return misssion_.Get(index);
}
inline ::ProtoMission::MissionCPP* GetCurMissionResp::mutable_misssion(int index) {
  return misssion_.Mutable(index);
}
inline ::ProtoMission::MissionCPP* GetCurMissionResp::add_misssion() {
  return misssion_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ProtoMission::MissionCPP >&
GetCurMissionResp::misssion() const {
  return misssion_;
}
inline ::google::protobuf::RepeatedPtrField< ::ProtoMission::MissionCPP >*
GetCurMissionResp::mutable_misssion() {
  return &misssion_;
}

// -------------------------------------------------------------------

// RewardMissionReq

// required uint32 ud = 1;
inline bool RewardMissionReq::has_ud() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RewardMissionReq::set_has_ud() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RewardMissionReq::clear_has_ud() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RewardMissionReq::clear_ud() {
  ud_ = 0u;
  clear_has_ud();
}
inline ::google::protobuf::uint32 RewardMissionReq::ud() const {
  return ud_;
}
inline void RewardMissionReq::set_ud(::google::protobuf::uint32 value) {
  set_has_ud();
  ud_ = value;
}

// required uint32 type = 2;
inline bool RewardMissionReq::has_type() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void RewardMissionReq::set_has_type() {
  _has_bits_[0] |= 0x00000002u;
}
inline void RewardMissionReq::clear_has_type() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void RewardMissionReq::clear_type() {
  type_ = 0u;
  clear_has_type();
}
inline ::google::protobuf::uint32 RewardMissionReq::type() const {
  return type_;
}
inline void RewardMissionReq::set_type(::google::protobuf::uint32 value) {
  set_has_type();
  type_ = value;
}

// -------------------------------------------------------------------

// RewardMissionResp

// repeated .ProtoMission.MissionCPP missions = 1;
inline int RewardMissionResp::missions_size() const {
  return missions_.size();
}
inline void RewardMissionResp::clear_missions() {
  missions_.Clear();
}
inline const ::ProtoMission::MissionCPP& RewardMissionResp::missions(int index) const {
  return missions_.Get(index);
}
inline ::ProtoMission::MissionCPP* RewardMissionResp::mutable_missions(int index) {
  return missions_.Mutable(index);
}
inline ::ProtoMission::MissionCPP* RewardMissionResp::add_missions() {
  return missions_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ProtoMission::MissionCPP >&
RewardMissionResp::missions() const {
  return missions_;
}
inline ::google::protobuf::RepeatedPtrField< ::ProtoMission::MissionCPP >*
RewardMissionResp::mutable_missions() {
  return &missions_;
}

// required .DataCommon.CommonItemsCPP commons = 2;
inline bool RewardMissionResp::has_commons() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void RewardMissionResp::set_has_commons() {
  _has_bits_[0] |= 0x00000002u;
}
inline void RewardMissionResp::clear_has_commons() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void RewardMissionResp::clear_commons() {
  if (commons_ != NULL) commons_->::DataCommon::CommonItemsCPP::Clear();
  clear_has_commons();
}
inline const ::DataCommon::CommonItemsCPP& RewardMissionResp::commons() const {
  return commons_ != NULL ? *commons_ : *default_instance_->commons_;
}
inline ::DataCommon::CommonItemsCPP* RewardMissionResp::mutable_commons() {
  set_has_commons();
  if (commons_ == NULL) commons_ = new ::DataCommon::CommonItemsCPP;
  return commons_;
}
inline ::DataCommon::CommonItemsCPP* RewardMissionResp::release_commons() {
  clear_has_commons();
  ::DataCommon::CommonItemsCPP* temp = commons_;
  commons_ = NULL;
  return temp;
}

// -------------------------------------------------------------------

// PushMission

// required .ProtoMission.MissionCPP mission = 1;
inline bool PushMission::has_mission() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PushMission::set_has_mission() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PushMission::clear_has_mission() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PushMission::clear_mission() {
  if (mission_ != NULL) mission_->::ProtoMission::MissionCPP::Clear();
  clear_has_mission();
}
inline const ::ProtoMission::MissionCPP& PushMission::mission() const {
  return mission_ != NULL ? *mission_ : *default_instance_->mission_;
}
inline ::ProtoMission::MissionCPP* PushMission::mutable_mission() {
  set_has_mission();
  if (mission_ == NULL) mission_ = new ::ProtoMission::MissionCPP;
  return mission_;
}
inline ::ProtoMission::MissionCPP* PushMission::release_mission() {
  clear_has_mission();
  ::ProtoMission::MissionCPP* temp = mission_;
  mission_ = NULL;
  return temp;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ProtoMission

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ProtoMission_2eproto__INCLUDED
