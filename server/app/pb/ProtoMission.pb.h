// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProtoMission.proto

#ifndef PROTOBUF_ProtoMission_2eproto__INCLUDED
#define PROTOBUF_ProtoMission_2eproto__INCLUDED

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

namespace ProtoMission {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ProtoMission_2eproto();
void protobuf_AssignDesc_ProtoMission_2eproto();
void protobuf_ShutdownFile_ProtoMission_2eproto();

class MissionCPP;
class MissionAllCPP;
class PushMissionReq;
class VerfifyMissonReq;
class VerifyWorldMoveMissionReq;
class GetMissionRewardReq;
class GetMissionRewardResp;

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

  // required bool status = 2;
  inline bool has_status() const;
  inline void clear_status();
  static const int kStatusFieldNumber = 2;
  inline bool status() const;
  inline void set_status(bool value);

  // repeated uint32 current = 3;
  inline int current_size() const;
  inline void clear_current();
  static const int kCurrentFieldNumber = 3;
  inline ::google::protobuf::uint32 current(int index) const;
  inline void set_current(int index, ::google::protobuf::uint32 value);
  inline void add_current(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      current() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_current();

  // @@protoc_insertion_point(class_scope:ProtoMission.MissionCPP)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_status();
  inline void clear_has_status();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 id_;
  bool status_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > current_;
  friend void  protobuf_AddDesc_ProtoMission_2eproto();
  friend void protobuf_AssignDesc_ProtoMission_2eproto();
  friend void protobuf_ShutdownFile_ProtoMission_2eproto();

  void InitAsDefaultInstance();
  static MissionCPP* default_instance_;
};
// -------------------------------------------------------------------

class MissionAllCPP : public ::google::protobuf::Message {
 public:
  MissionAllCPP();
  virtual ~MissionAllCPP();

  MissionAllCPP(const MissionAllCPP& from);

  inline MissionAllCPP& operator=(const MissionAllCPP& from) {
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
  static const MissionAllCPP& default_instance();

  void Swap(MissionAllCPP* other);

  // implements Message ----------------------------------------------

  MissionAllCPP* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MissionAllCPP& from);
  void MergeFrom(const MissionAllCPP& from);
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

  // @@protoc_insertion_point(class_scope:ProtoMission.MissionAllCPP)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::ProtoMission::MissionCPP > missions_;
  friend void  protobuf_AddDesc_ProtoMission_2eproto();
  friend void protobuf_AssignDesc_ProtoMission_2eproto();
  friend void protobuf_ShutdownFile_ProtoMission_2eproto();

  void InitAsDefaultInstance();
  static MissionAllCPP* default_instance_;
};
// -------------------------------------------------------------------

class PushMissionReq : public ::google::protobuf::Message {
 public:
  PushMissionReq();
  virtual ~PushMissionReq();

  PushMissionReq(const PushMissionReq& from);

  inline PushMissionReq& operator=(const PushMissionReq& from) {
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
  static const PushMissionReq& default_instance();

  void Swap(PushMissionReq* other);

  // implements Message ----------------------------------------------

  PushMissionReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PushMissionReq& from);
  void MergeFrom(const PushMissionReq& from);
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

  // required .ProtoMission.MissionAllCPP missions = 1;
  inline bool has_missions() const;
  inline void clear_missions();
  static const int kMissionsFieldNumber = 1;
  inline const ::ProtoMission::MissionAllCPP& missions() const;
  inline ::ProtoMission::MissionAllCPP* mutable_missions();
  inline ::ProtoMission::MissionAllCPP* release_missions();
  inline void set_allocated_missions(::ProtoMission::MissionAllCPP* missions);

  // @@protoc_insertion_point(class_scope:ProtoMission.PushMissionReq)
 private:
  inline void set_has_missions();
  inline void clear_has_missions();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::ProtoMission::MissionAllCPP* missions_;
  friend void  protobuf_AddDesc_ProtoMission_2eproto();
  friend void protobuf_AssignDesc_ProtoMission_2eproto();
  friend void protobuf_ShutdownFile_ProtoMission_2eproto();

  void InitAsDefaultInstance();
  static PushMissionReq* default_instance_;
};
// -------------------------------------------------------------------

class VerfifyMissonReq : public ::google::protobuf::Message {
 public:
  VerfifyMissonReq();
  virtual ~VerfifyMissonReq();

  VerfifyMissonReq(const VerfifyMissonReq& from);

  inline VerfifyMissonReq& operator=(const VerfifyMissonReq& from) {
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
  static const VerfifyMissonReq& default_instance();

  void Swap(VerfifyMissonReq* other);

  // implements Message ----------------------------------------------

  VerfifyMissonReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const VerfifyMissonReq& from);
  void MergeFrom(const VerfifyMissonReq& from);
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

  // @@protoc_insertion_point(class_scope:ProtoMission.VerfifyMissonReq)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_ProtoMission_2eproto();
  friend void protobuf_AssignDesc_ProtoMission_2eproto();
  friend void protobuf_ShutdownFile_ProtoMission_2eproto();

  void InitAsDefaultInstance();
  static VerfifyMissonReq* default_instance_;
};
// -------------------------------------------------------------------

class VerifyWorldMoveMissionReq : public ::google::protobuf::Message {
 public:
  VerifyWorldMoveMissionReq();
  virtual ~VerifyWorldMoveMissionReq();

  VerifyWorldMoveMissionReq(const VerifyWorldMoveMissionReq& from);

  inline VerifyWorldMoveMissionReq& operator=(const VerifyWorldMoveMissionReq& from) {
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
  static const VerifyWorldMoveMissionReq& default_instance();

  void Swap(VerifyWorldMoveMissionReq* other);

  // implements Message ----------------------------------------------

  VerifyWorldMoveMissionReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const VerifyWorldMoveMissionReq& from);
  void MergeFrom(const VerifyWorldMoveMissionReq& from);
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

  // @@protoc_insertion_point(class_scope:ProtoMission.VerifyWorldMoveMissionReq)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_ProtoMission_2eproto();
  friend void protobuf_AssignDesc_ProtoMission_2eproto();
  friend void protobuf_ShutdownFile_ProtoMission_2eproto();

  void InitAsDefaultInstance();
  static VerifyWorldMoveMissionReq* default_instance_;
};
// -------------------------------------------------------------------

class GetMissionRewardReq : public ::google::protobuf::Message {
 public:
  GetMissionRewardReq();
  virtual ~GetMissionRewardReq();

  GetMissionRewardReq(const GetMissionRewardReq& from);

  inline GetMissionRewardReq& operator=(const GetMissionRewardReq& from) {
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
  static const GetMissionRewardReq& default_instance();

  void Swap(GetMissionRewardReq* other);

  // implements Message ----------------------------------------------

  GetMissionRewardReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GetMissionRewardReq& from);
  void MergeFrom(const GetMissionRewardReq& from);
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

  // @@protoc_insertion_point(class_scope:ProtoMission.GetMissionRewardReq)
 private:
  inline void set_has_id();
  inline void clear_has_id();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 id_;
  friend void  protobuf_AddDesc_ProtoMission_2eproto();
  friend void protobuf_AssignDesc_ProtoMission_2eproto();
  friend void protobuf_ShutdownFile_ProtoMission_2eproto();

  void InitAsDefaultInstance();
  static GetMissionRewardReq* default_instance_;
};
// -------------------------------------------------------------------

class GetMissionRewardResp : public ::google::protobuf::Message {
 public:
  GetMissionRewardResp();
  virtual ~GetMissionRewardResp();

  GetMissionRewardResp(const GetMissionRewardResp& from);

  inline GetMissionRewardResp& operator=(const GetMissionRewardResp& from) {
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
  static const GetMissionRewardResp& default_instance();

  void Swap(GetMissionRewardResp* other);

  // implements Message ----------------------------------------------

  GetMissionRewardResp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GetMissionRewardResp& from);
  void MergeFrom(const GetMissionRewardResp& from);
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

  // required uint32 food = 1;
  inline bool has_food() const;
  inline void clear_food();
  static const int kFoodFieldNumber = 1;
  inline ::google::protobuf::uint32 food() const;
  inline void set_food(::google::protobuf::uint32 value);

  // required uint32 coin = 2;
  inline bool has_coin() const;
  inline void clear_coin();
  static const int kCoinFieldNumber = 2;
  inline ::google::protobuf::uint32 coin() const;
  inline void set_coin(::google::protobuf::uint32 value);

  // required uint32 wood = 3;
  inline bool has_wood() const;
  inline void clear_wood();
  static const int kWoodFieldNumber = 3;
  inline ::google::protobuf::uint32 wood() const;
  inline void set_wood(::google::protobuf::uint32 value);

  // required uint64 exp = 4;
  inline bool has_exp() const;
  inline void clear_exp();
  static const int kExpFieldNumber = 4;
  inline ::google::protobuf::uint64 exp() const;
  inline void set_exp(::google::protobuf::uint64 value);

  // required uint32 level = 5;
  inline bool has_level() const;
  inline void clear_level();
  static const int kLevelFieldNumber = 5;
  inline ::google::protobuf::uint32 level() const;
  inline void set_level(::google::protobuf::uint32 value);

  // required .ProtoMission.MissionAllCPP nextmission = 6;
  inline bool has_nextmission() const;
  inline void clear_nextmission();
  static const int kNextmissionFieldNumber = 6;
  inline const ::ProtoMission::MissionAllCPP& nextmission() const;
  inline ::ProtoMission::MissionAllCPP* mutable_nextmission();
  inline ::ProtoMission::MissionAllCPP* release_nextmission();
  inline void set_allocated_nextmission(::ProtoMission::MissionAllCPP* nextmission);

  // optional uint32 hammer = 7;
  inline bool has_hammer() const;
  inline void clear_hammer();
  static const int kHammerFieldNumber = 7;
  inline ::google::protobuf::uint32 hammer() const;
  inline void set_hammer(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:ProtoMission.GetMissionRewardResp)
 private:
  inline void set_has_food();
  inline void clear_has_food();
  inline void set_has_coin();
  inline void clear_has_coin();
  inline void set_has_wood();
  inline void clear_has_wood();
  inline void set_has_exp();
  inline void clear_has_exp();
  inline void set_has_level();
  inline void clear_has_level();
  inline void set_has_nextmission();
  inline void clear_has_nextmission();
  inline void set_has_hammer();
  inline void clear_has_hammer();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 food_;
  ::google::protobuf::uint32 coin_;
  ::google::protobuf::uint64 exp_;
  ::google::protobuf::uint32 wood_;
  ::google::protobuf::uint32 level_;
  ::ProtoMission::MissionAllCPP* nextmission_;
  ::google::protobuf::uint32 hammer_;
  friend void  protobuf_AddDesc_ProtoMission_2eproto();
  friend void protobuf_AssignDesc_ProtoMission_2eproto();
  friend void protobuf_ShutdownFile_ProtoMission_2eproto();

  void InitAsDefaultInstance();
  static GetMissionRewardResp* default_instance_;
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
  // @@protoc_insertion_point(field_get:ProtoMission.MissionCPP.id)
  return id_;
}
inline void MissionCPP::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:ProtoMission.MissionCPP.id)
}

// required bool status = 2;
inline bool MissionCPP::has_status() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MissionCPP::set_has_status() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MissionCPP::clear_has_status() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MissionCPP::clear_status() {
  status_ = false;
  clear_has_status();
}
inline bool MissionCPP::status() const {
  // @@protoc_insertion_point(field_get:ProtoMission.MissionCPP.status)
  return status_;
}
inline void MissionCPP::set_status(bool value) {
  set_has_status();
  status_ = value;
  // @@protoc_insertion_point(field_set:ProtoMission.MissionCPP.status)
}

// repeated uint32 current = 3;
inline int MissionCPP::current_size() const {
  return current_.size();
}
inline void MissionCPP::clear_current() {
  current_.Clear();
}
inline ::google::protobuf::uint32 MissionCPP::current(int index) const {
  // @@protoc_insertion_point(field_get:ProtoMission.MissionCPP.current)
  return current_.Get(index);
}
inline void MissionCPP::set_current(int index, ::google::protobuf::uint32 value) {
  current_.Set(index, value);
  // @@protoc_insertion_point(field_set:ProtoMission.MissionCPP.current)
}
inline void MissionCPP::add_current(::google::protobuf::uint32 value) {
  current_.Add(value);
  // @@protoc_insertion_point(field_add:ProtoMission.MissionCPP.current)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
MissionCPP::current() const {
  // @@protoc_insertion_point(field_list:ProtoMission.MissionCPP.current)
  return current_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
MissionCPP::mutable_current() {
  // @@protoc_insertion_point(field_mutable_list:ProtoMission.MissionCPP.current)
  return &current_;
}

// -------------------------------------------------------------------

// MissionAllCPP

// repeated .ProtoMission.MissionCPP missions = 1;
inline int MissionAllCPP::missions_size() const {
  return missions_.size();
}
inline void MissionAllCPP::clear_missions() {
  missions_.Clear();
}
inline const ::ProtoMission::MissionCPP& MissionAllCPP::missions(int index) const {
  // @@protoc_insertion_point(field_get:ProtoMission.MissionAllCPP.missions)
  return missions_.Get(index);
}
inline ::ProtoMission::MissionCPP* MissionAllCPP::mutable_missions(int index) {
  // @@protoc_insertion_point(field_mutable:ProtoMission.MissionAllCPP.missions)
  return missions_.Mutable(index);
}
inline ::ProtoMission::MissionCPP* MissionAllCPP::add_missions() {
  // @@protoc_insertion_point(field_add:ProtoMission.MissionAllCPP.missions)
  return missions_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ProtoMission::MissionCPP >&
MissionAllCPP::missions() const {
  // @@protoc_insertion_point(field_list:ProtoMission.MissionAllCPP.missions)
  return missions_;
}
inline ::google::protobuf::RepeatedPtrField< ::ProtoMission::MissionCPP >*
MissionAllCPP::mutable_missions() {
  // @@protoc_insertion_point(field_mutable_list:ProtoMission.MissionAllCPP.missions)
  return &missions_;
}

// -------------------------------------------------------------------

// PushMissionReq

// required .ProtoMission.MissionAllCPP missions = 1;
inline bool PushMissionReq::has_missions() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PushMissionReq::set_has_missions() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PushMissionReq::clear_has_missions() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PushMissionReq::clear_missions() {
  if (missions_ != NULL) missions_->::ProtoMission::MissionAllCPP::Clear();
  clear_has_missions();
}
inline const ::ProtoMission::MissionAllCPP& PushMissionReq::missions() const {
  // @@protoc_insertion_point(field_get:ProtoMission.PushMissionReq.missions)
  return missions_ != NULL ? *missions_ : *default_instance_->missions_;
}
inline ::ProtoMission::MissionAllCPP* PushMissionReq::mutable_missions() {
  set_has_missions();
  if (missions_ == NULL) missions_ = new ::ProtoMission::MissionAllCPP;
  // @@protoc_insertion_point(field_mutable:ProtoMission.PushMissionReq.missions)
  return missions_;
}
inline ::ProtoMission::MissionAllCPP* PushMissionReq::release_missions() {
  clear_has_missions();
  ::ProtoMission::MissionAllCPP* temp = missions_;
  missions_ = NULL;
  return temp;
}
inline void PushMissionReq::set_allocated_missions(::ProtoMission::MissionAllCPP* missions) {
  delete missions_;
  missions_ = missions;
  if (missions) {
    set_has_missions();
  } else {
    clear_has_missions();
  }
  // @@protoc_insertion_point(field_set_allocated:ProtoMission.PushMissionReq.missions)
}

// -------------------------------------------------------------------

// VerfifyMissonReq

// -------------------------------------------------------------------

// VerifyWorldMoveMissionReq

// -------------------------------------------------------------------

// GetMissionRewardReq

// required uint32 id = 1;
inline bool GetMissionRewardReq::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GetMissionRewardReq::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void GetMissionRewardReq::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void GetMissionRewardReq::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 GetMissionRewardReq::id() const {
  // @@protoc_insertion_point(field_get:ProtoMission.GetMissionRewardReq.id)
  return id_;
}
inline void GetMissionRewardReq::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:ProtoMission.GetMissionRewardReq.id)
}

// -------------------------------------------------------------------

// GetMissionRewardResp

// required uint32 food = 1;
inline bool GetMissionRewardResp::has_food() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GetMissionRewardResp::set_has_food() {
  _has_bits_[0] |= 0x00000001u;
}
inline void GetMissionRewardResp::clear_has_food() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void GetMissionRewardResp::clear_food() {
  food_ = 0u;
  clear_has_food();
}
inline ::google::protobuf::uint32 GetMissionRewardResp::food() const {
  // @@protoc_insertion_point(field_get:ProtoMission.GetMissionRewardResp.food)
  return food_;
}
inline void GetMissionRewardResp::set_food(::google::protobuf::uint32 value) {
  set_has_food();
  food_ = value;
  // @@protoc_insertion_point(field_set:ProtoMission.GetMissionRewardResp.food)
}

// required uint32 coin = 2;
inline bool GetMissionRewardResp::has_coin() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void GetMissionRewardResp::set_has_coin() {
  _has_bits_[0] |= 0x00000002u;
}
inline void GetMissionRewardResp::clear_has_coin() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void GetMissionRewardResp::clear_coin() {
  coin_ = 0u;
  clear_has_coin();
}
inline ::google::protobuf::uint32 GetMissionRewardResp::coin() const {
  // @@protoc_insertion_point(field_get:ProtoMission.GetMissionRewardResp.coin)
  return coin_;
}
inline void GetMissionRewardResp::set_coin(::google::protobuf::uint32 value) {
  set_has_coin();
  coin_ = value;
  // @@protoc_insertion_point(field_set:ProtoMission.GetMissionRewardResp.coin)
}

// required uint32 wood = 3;
inline bool GetMissionRewardResp::has_wood() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void GetMissionRewardResp::set_has_wood() {
  _has_bits_[0] |= 0x00000004u;
}
inline void GetMissionRewardResp::clear_has_wood() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void GetMissionRewardResp::clear_wood() {
  wood_ = 0u;
  clear_has_wood();
}
inline ::google::protobuf::uint32 GetMissionRewardResp::wood() const {
  // @@protoc_insertion_point(field_get:ProtoMission.GetMissionRewardResp.wood)
  return wood_;
}
inline void GetMissionRewardResp::set_wood(::google::protobuf::uint32 value) {
  set_has_wood();
  wood_ = value;
  // @@protoc_insertion_point(field_set:ProtoMission.GetMissionRewardResp.wood)
}

// required uint64 exp = 4;
inline bool GetMissionRewardResp::has_exp() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void GetMissionRewardResp::set_has_exp() {
  _has_bits_[0] |= 0x00000008u;
}
inline void GetMissionRewardResp::clear_has_exp() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void GetMissionRewardResp::clear_exp() {
  exp_ = GOOGLE_ULONGLONG(0);
  clear_has_exp();
}
inline ::google::protobuf::uint64 GetMissionRewardResp::exp() const {
  // @@protoc_insertion_point(field_get:ProtoMission.GetMissionRewardResp.exp)
  return exp_;
}
inline void GetMissionRewardResp::set_exp(::google::protobuf::uint64 value) {
  set_has_exp();
  exp_ = value;
  // @@protoc_insertion_point(field_set:ProtoMission.GetMissionRewardResp.exp)
}

// required uint32 level = 5;
inline bool GetMissionRewardResp::has_level() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void GetMissionRewardResp::set_has_level() {
  _has_bits_[0] |= 0x00000010u;
}
inline void GetMissionRewardResp::clear_has_level() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void GetMissionRewardResp::clear_level() {
  level_ = 0u;
  clear_has_level();
}
inline ::google::protobuf::uint32 GetMissionRewardResp::level() const {
  // @@protoc_insertion_point(field_get:ProtoMission.GetMissionRewardResp.level)
  return level_;
}
inline void GetMissionRewardResp::set_level(::google::protobuf::uint32 value) {
  set_has_level();
  level_ = value;
  // @@protoc_insertion_point(field_set:ProtoMission.GetMissionRewardResp.level)
}

// required .ProtoMission.MissionAllCPP nextmission = 6;
inline bool GetMissionRewardResp::has_nextmission() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void GetMissionRewardResp::set_has_nextmission() {
  _has_bits_[0] |= 0x00000020u;
}
inline void GetMissionRewardResp::clear_has_nextmission() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void GetMissionRewardResp::clear_nextmission() {
  if (nextmission_ != NULL) nextmission_->::ProtoMission::MissionAllCPP::Clear();
  clear_has_nextmission();
}
inline const ::ProtoMission::MissionAllCPP& GetMissionRewardResp::nextmission() const {
  // @@protoc_insertion_point(field_get:ProtoMission.GetMissionRewardResp.nextmission)
  return nextmission_ != NULL ? *nextmission_ : *default_instance_->nextmission_;
}
inline ::ProtoMission::MissionAllCPP* GetMissionRewardResp::mutable_nextmission() {
  set_has_nextmission();
  if (nextmission_ == NULL) nextmission_ = new ::ProtoMission::MissionAllCPP;
  // @@protoc_insertion_point(field_mutable:ProtoMission.GetMissionRewardResp.nextmission)
  return nextmission_;
}
inline ::ProtoMission::MissionAllCPP* GetMissionRewardResp::release_nextmission() {
  clear_has_nextmission();
  ::ProtoMission::MissionAllCPP* temp = nextmission_;
  nextmission_ = NULL;
  return temp;
}
inline void GetMissionRewardResp::set_allocated_nextmission(::ProtoMission::MissionAllCPP* nextmission) {
  delete nextmission_;
  nextmission_ = nextmission;
  if (nextmission) {
    set_has_nextmission();
  } else {
    clear_has_nextmission();
  }
  // @@protoc_insertion_point(field_set_allocated:ProtoMission.GetMissionRewardResp.nextmission)
}

// optional uint32 hammer = 7;
inline bool GetMissionRewardResp::has_hammer() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void GetMissionRewardResp::set_has_hammer() {
  _has_bits_[0] |= 0x00000040u;
}
inline void GetMissionRewardResp::clear_has_hammer() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void GetMissionRewardResp::clear_hammer() {
  hammer_ = 0u;
  clear_has_hammer();
}
inline ::google::protobuf::uint32 GetMissionRewardResp::hammer() const {
  // @@protoc_insertion_point(field_get:ProtoMission.GetMissionRewardResp.hammer)
  return hammer_;
}
inline void GetMissionRewardResp::set_hammer(::google::protobuf::uint32 value) {
  set_has_hammer();
  hammer_ = value;
  // @@protoc_insertion_point(field_set:ProtoMission.GetMissionRewardResp.hammer)
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
