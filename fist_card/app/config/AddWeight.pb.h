// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: AddWeight.proto

#ifndef PROTOBUF_AddWeight_2eproto__INCLUDED
#define PROTOBUF_AddWeight_2eproto__INCLUDED

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
// @@protoc_insertion_point(includes)

namespace AddWeight {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_AddWeight_2eproto();
void protobuf_AssignDesc_AddWeight_2eproto();
void protobuf_ShutdownFile_AddWeight_2eproto();

class PlayerAddWeight;
class PvpAddWeight;
class VipAddWeight;
class AddWeightList;
class AddWeightInfo;

// ===================================================================

class PlayerAddWeight : public ::google::protobuf::Message {
 public:
  PlayerAddWeight();
  virtual ~PlayerAddWeight();
  
  PlayerAddWeight(const PlayerAddWeight& from);
  
  inline PlayerAddWeight& operator=(const PlayerAddWeight& from) {
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
  static const PlayerAddWeight& default_instance();
  
  void Swap(PlayerAddWeight* other);
  
  // implements Message ----------------------------------------------
  
  PlayerAddWeight* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PlayerAddWeight& from);
  void MergeFrom(const PlayerAddWeight& from);
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
  
  // required uint32 level = 1;
  inline bool has_level() const;
  inline void clear_level();
  static const int kLevelFieldNumber = 1;
  inline ::google::protobuf::uint32 level() const;
  inline void set_level(::google::protobuf::uint32 value);
  
  // repeated uint32 weight = 2;
  inline int weight_size() const;
  inline void clear_weight();
  static const int kWeightFieldNumber = 2;
  inline ::google::protobuf::uint32 weight(int index) const;
  inline void set_weight(int index, ::google::protobuf::uint32 value);
  inline void add_weight(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      weight() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_weight();
  
  // @@protoc_insertion_point(class_scope:AddWeight.PlayerAddWeight)
 private:
  inline void set_has_level();
  inline void clear_has_level();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > weight_;
  ::google::protobuf::uint32 level_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_AddWeight_2eproto();
  friend void protobuf_AssignDesc_AddWeight_2eproto();
  friend void protobuf_ShutdownFile_AddWeight_2eproto();
  
  void InitAsDefaultInstance();
  static PlayerAddWeight* default_instance_;
};
// -------------------------------------------------------------------

class PvpAddWeight : public ::google::protobuf::Message {
 public:
  PvpAddWeight();
  virtual ~PvpAddWeight();
  
  PvpAddWeight(const PvpAddWeight& from);
  
  inline PvpAddWeight& operator=(const PvpAddWeight& from) {
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
  static const PvpAddWeight& default_instance();
  
  void Swap(PvpAddWeight* other);
  
  // implements Message ----------------------------------------------
  
  PvpAddWeight* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PvpAddWeight& from);
  void MergeFrom(const PvpAddWeight& from);
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
  
  // required uint32 failCnt = 1;
  inline bool has_failcnt() const;
  inline void clear_failcnt();
  static const int kFailCntFieldNumber = 1;
  inline ::google::protobuf::uint32 failcnt() const;
  inline void set_failcnt(::google::protobuf::uint32 value);
  
  // repeated uint32 weight = 2;
  inline int weight_size() const;
  inline void clear_weight();
  static const int kWeightFieldNumber = 2;
  inline ::google::protobuf::uint32 weight(int index) const;
  inline void set_weight(int index, ::google::protobuf::uint32 value);
  inline void add_weight(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      weight() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_weight();
  
  // @@protoc_insertion_point(class_scope:AddWeight.PvpAddWeight)
 private:
  inline void set_has_failcnt();
  inline void clear_has_failcnt();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > weight_;
  ::google::protobuf::uint32 failcnt_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_AddWeight_2eproto();
  friend void protobuf_AssignDesc_AddWeight_2eproto();
  friend void protobuf_ShutdownFile_AddWeight_2eproto();
  
  void InitAsDefaultInstance();
  static PvpAddWeight* default_instance_;
};
// -------------------------------------------------------------------

class VipAddWeight : public ::google::protobuf::Message {
 public:
  VipAddWeight();
  virtual ~VipAddWeight();
  
  VipAddWeight(const VipAddWeight& from);
  
  inline VipAddWeight& operator=(const VipAddWeight& from) {
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
  static const VipAddWeight& default_instance();
  
  void Swap(VipAddWeight* other);
  
  // implements Message ----------------------------------------------
  
  VipAddWeight* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const VipAddWeight& from);
  void MergeFrom(const VipAddWeight& from);
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
  
  // required uint32 level = 1;
  inline bool has_level() const;
  inline void clear_level();
  static const int kLevelFieldNumber = 1;
  inline ::google::protobuf::uint32 level() const;
  inline void set_level(::google::protobuf::uint32 value);
  
  // repeated uint32 weight = 2;
  inline int weight_size() const;
  inline void clear_weight();
  static const int kWeightFieldNumber = 2;
  inline ::google::protobuf::uint32 weight(int index) const;
  inline void set_weight(int index, ::google::protobuf::uint32 value);
  inline void add_weight(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      weight() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_weight();
  
  // @@protoc_insertion_point(class_scope:AddWeight.VipAddWeight)
 private:
  inline void set_has_level();
  inline void clear_has_level();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > weight_;
  ::google::protobuf::uint32 level_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_AddWeight_2eproto();
  friend void protobuf_AssignDesc_AddWeight_2eproto();
  friend void protobuf_ShutdownFile_AddWeight_2eproto();
  
  void InitAsDefaultInstance();
  static VipAddWeight* default_instance_;
};
// -------------------------------------------------------------------

class AddWeightList : public ::google::protobuf::Message {
 public:
  AddWeightList();
  virtual ~AddWeightList();
  
  AddWeightList(const AddWeightList& from);
  
  inline AddWeightList& operator=(const AddWeightList& from) {
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
  static const AddWeightList& default_instance();
  
  void Swap(AddWeightList* other);
  
  // implements Message ----------------------------------------------
  
  AddWeightList* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AddWeightList& from);
  void MergeFrom(const AddWeightList& from);
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
  
  // repeated .AddWeight.PlayerAddWeight player = 1;
  inline int player_size() const;
  inline void clear_player();
  static const int kPlayerFieldNumber = 1;
  inline const ::AddWeight::PlayerAddWeight& player(int index) const;
  inline ::AddWeight::PlayerAddWeight* mutable_player(int index);
  inline ::AddWeight::PlayerAddWeight* add_player();
  inline const ::google::protobuf::RepeatedPtrField< ::AddWeight::PlayerAddWeight >&
      player() const;
  inline ::google::protobuf::RepeatedPtrField< ::AddWeight::PlayerAddWeight >*
      mutable_player();
  
  // repeated .AddWeight.PvpAddWeight pvp = 2;
  inline int pvp_size() const;
  inline void clear_pvp();
  static const int kPvpFieldNumber = 2;
  inline const ::AddWeight::PvpAddWeight& pvp(int index) const;
  inline ::AddWeight::PvpAddWeight* mutable_pvp(int index);
  inline ::AddWeight::PvpAddWeight* add_pvp();
  inline const ::google::protobuf::RepeatedPtrField< ::AddWeight::PvpAddWeight >&
      pvp() const;
  inline ::google::protobuf::RepeatedPtrField< ::AddWeight::PvpAddWeight >*
      mutable_pvp();
  
  // repeated .AddWeight.VipAddWeight vip = 3;
  inline int vip_size() const;
  inline void clear_vip();
  static const int kVipFieldNumber = 3;
  inline const ::AddWeight::VipAddWeight& vip(int index) const;
  inline ::AddWeight::VipAddWeight* mutable_vip(int index);
  inline ::AddWeight::VipAddWeight* add_vip();
  inline const ::google::protobuf::RepeatedPtrField< ::AddWeight::VipAddWeight >&
      vip() const;
  inline ::google::protobuf::RepeatedPtrField< ::AddWeight::VipAddWeight >*
      mutable_vip();
  
  // @@protoc_insertion_point(class_scope:AddWeight.AddWeightList)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::AddWeight::PlayerAddWeight > player_;
  ::google::protobuf::RepeatedPtrField< ::AddWeight::PvpAddWeight > pvp_;
  ::google::protobuf::RepeatedPtrField< ::AddWeight::VipAddWeight > vip_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_AddWeight_2eproto();
  friend void protobuf_AssignDesc_AddWeight_2eproto();
  friend void protobuf_ShutdownFile_AddWeight_2eproto();
  
  void InitAsDefaultInstance();
  static AddWeightList* default_instance_;
};
// -------------------------------------------------------------------

class AddWeightInfo : public ::google::protobuf::Message {
 public:
  AddWeightInfo();
  virtual ~AddWeightInfo();
  
  AddWeightInfo(const AddWeightInfo& from);
  
  inline AddWeightInfo& operator=(const AddWeightInfo& from) {
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
  static const AddWeightInfo& default_instance();
  
  void Swap(AddWeightInfo* other);
  
  // implements Message ----------------------------------------------
  
  AddWeightInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AddWeightInfo& from);
  void MergeFrom(const AddWeightInfo& from);
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
  
  // required .AddWeight.AddWeightList addWeight = 1;
  inline bool has_addweight() const;
  inline void clear_addweight();
  static const int kAddWeightFieldNumber = 1;
  inline const ::AddWeight::AddWeightList& addweight() const;
  inline ::AddWeight::AddWeightList* mutable_addweight();
  inline ::AddWeight::AddWeightList* release_addweight();
  
  // @@protoc_insertion_point(class_scope:AddWeight.AddWeightInfo)
 private:
  inline void set_has_addweight();
  inline void clear_has_addweight();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::AddWeight::AddWeightList* addweight_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_AddWeight_2eproto();
  friend void protobuf_AssignDesc_AddWeight_2eproto();
  friend void protobuf_ShutdownFile_AddWeight_2eproto();
  
  void InitAsDefaultInstance();
  static AddWeightInfo* default_instance_;
};
// ===================================================================


// ===================================================================

// PlayerAddWeight

// required uint32 level = 1;
inline bool PlayerAddWeight::has_level() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PlayerAddWeight::set_has_level() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PlayerAddWeight::clear_has_level() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PlayerAddWeight::clear_level() {
  level_ = 0u;
  clear_has_level();
}
inline ::google::protobuf::uint32 PlayerAddWeight::level() const {
  return level_;
}
inline void PlayerAddWeight::set_level(::google::protobuf::uint32 value) {
  set_has_level();
  level_ = value;
}

// repeated uint32 weight = 2;
inline int PlayerAddWeight::weight_size() const {
  return weight_.size();
}
inline void PlayerAddWeight::clear_weight() {
  weight_.Clear();
}
inline ::google::protobuf::uint32 PlayerAddWeight::weight(int index) const {
  return weight_.Get(index);
}
inline void PlayerAddWeight::set_weight(int index, ::google::protobuf::uint32 value) {
  weight_.Set(index, value);
}
inline void PlayerAddWeight::add_weight(::google::protobuf::uint32 value) {
  weight_.Add(value);
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
PlayerAddWeight::weight() const {
  return weight_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
PlayerAddWeight::mutable_weight() {
  return &weight_;
}

// -------------------------------------------------------------------

// PvpAddWeight

// required uint32 failCnt = 1;
inline bool PvpAddWeight::has_failcnt() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PvpAddWeight::set_has_failcnt() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PvpAddWeight::clear_has_failcnt() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PvpAddWeight::clear_failcnt() {
  failcnt_ = 0u;
  clear_has_failcnt();
}
inline ::google::protobuf::uint32 PvpAddWeight::failcnt() const {
  return failcnt_;
}
inline void PvpAddWeight::set_failcnt(::google::protobuf::uint32 value) {
  set_has_failcnt();
  failcnt_ = value;
}

// repeated uint32 weight = 2;
inline int PvpAddWeight::weight_size() const {
  return weight_.size();
}
inline void PvpAddWeight::clear_weight() {
  weight_.Clear();
}
inline ::google::protobuf::uint32 PvpAddWeight::weight(int index) const {
  return weight_.Get(index);
}
inline void PvpAddWeight::set_weight(int index, ::google::protobuf::uint32 value) {
  weight_.Set(index, value);
}
inline void PvpAddWeight::add_weight(::google::protobuf::uint32 value) {
  weight_.Add(value);
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
PvpAddWeight::weight() const {
  return weight_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
PvpAddWeight::mutable_weight() {
  return &weight_;
}

// -------------------------------------------------------------------

// VipAddWeight

// required uint32 level = 1;
inline bool VipAddWeight::has_level() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void VipAddWeight::set_has_level() {
  _has_bits_[0] |= 0x00000001u;
}
inline void VipAddWeight::clear_has_level() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void VipAddWeight::clear_level() {
  level_ = 0u;
  clear_has_level();
}
inline ::google::protobuf::uint32 VipAddWeight::level() const {
  return level_;
}
inline void VipAddWeight::set_level(::google::protobuf::uint32 value) {
  set_has_level();
  level_ = value;
}

// repeated uint32 weight = 2;
inline int VipAddWeight::weight_size() const {
  return weight_.size();
}
inline void VipAddWeight::clear_weight() {
  weight_.Clear();
}
inline ::google::protobuf::uint32 VipAddWeight::weight(int index) const {
  return weight_.Get(index);
}
inline void VipAddWeight::set_weight(int index, ::google::protobuf::uint32 value) {
  weight_.Set(index, value);
}
inline void VipAddWeight::add_weight(::google::protobuf::uint32 value) {
  weight_.Add(value);
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
VipAddWeight::weight() const {
  return weight_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
VipAddWeight::mutable_weight() {
  return &weight_;
}

// -------------------------------------------------------------------

// AddWeightList

// repeated .AddWeight.PlayerAddWeight player = 1;
inline int AddWeightList::player_size() const {
  return player_.size();
}
inline void AddWeightList::clear_player() {
  player_.Clear();
}
inline const ::AddWeight::PlayerAddWeight& AddWeightList::player(int index) const {
  return player_.Get(index);
}
inline ::AddWeight::PlayerAddWeight* AddWeightList::mutable_player(int index) {
  return player_.Mutable(index);
}
inline ::AddWeight::PlayerAddWeight* AddWeightList::add_player() {
  return player_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::AddWeight::PlayerAddWeight >&
AddWeightList::player() const {
  return player_;
}
inline ::google::protobuf::RepeatedPtrField< ::AddWeight::PlayerAddWeight >*
AddWeightList::mutable_player() {
  return &player_;
}

// repeated .AddWeight.PvpAddWeight pvp = 2;
inline int AddWeightList::pvp_size() const {
  return pvp_.size();
}
inline void AddWeightList::clear_pvp() {
  pvp_.Clear();
}
inline const ::AddWeight::PvpAddWeight& AddWeightList::pvp(int index) const {
  return pvp_.Get(index);
}
inline ::AddWeight::PvpAddWeight* AddWeightList::mutable_pvp(int index) {
  return pvp_.Mutable(index);
}
inline ::AddWeight::PvpAddWeight* AddWeightList::add_pvp() {
  return pvp_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::AddWeight::PvpAddWeight >&
AddWeightList::pvp() const {
  return pvp_;
}
inline ::google::protobuf::RepeatedPtrField< ::AddWeight::PvpAddWeight >*
AddWeightList::mutable_pvp() {
  return &pvp_;
}

// repeated .AddWeight.VipAddWeight vip = 3;
inline int AddWeightList::vip_size() const {
  return vip_.size();
}
inline void AddWeightList::clear_vip() {
  vip_.Clear();
}
inline const ::AddWeight::VipAddWeight& AddWeightList::vip(int index) const {
  return vip_.Get(index);
}
inline ::AddWeight::VipAddWeight* AddWeightList::mutable_vip(int index) {
  return vip_.Mutable(index);
}
inline ::AddWeight::VipAddWeight* AddWeightList::add_vip() {
  return vip_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::AddWeight::VipAddWeight >&
AddWeightList::vip() const {
  return vip_;
}
inline ::google::protobuf::RepeatedPtrField< ::AddWeight::VipAddWeight >*
AddWeightList::mutable_vip() {
  return &vip_;
}

// -------------------------------------------------------------------

// AddWeightInfo

// required .AddWeight.AddWeightList addWeight = 1;
inline bool AddWeightInfo::has_addweight() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AddWeightInfo::set_has_addweight() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AddWeightInfo::clear_has_addweight() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AddWeightInfo::clear_addweight() {
  if (addweight_ != NULL) addweight_->::AddWeight::AddWeightList::Clear();
  clear_has_addweight();
}
inline const ::AddWeight::AddWeightList& AddWeightInfo::addweight() const {
  return addweight_ != NULL ? *addweight_ : *default_instance_->addweight_;
}
inline ::AddWeight::AddWeightList* AddWeightInfo::mutable_addweight() {
  set_has_addweight();
  if (addweight_ == NULL) addweight_ = new ::AddWeight::AddWeightList;
  return addweight_;
}
inline ::AddWeight::AddWeightList* AddWeightInfo::release_addweight() {
  clear_has_addweight();
  ::AddWeight::AddWeightList* temp = addweight_;
  addweight_ = NULL;
  return temp;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace AddWeight

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_AddWeight_2eproto__INCLUDED
