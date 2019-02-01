// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: NewWorldAllianceMap.proto

#ifndef PROTOBUF_NewWorldAllianceMap_2eproto__INCLUDED
#define PROTOBUF_NewWorldAllianceMap_2eproto__INCLUDED

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

namespace NewWorldAllianceMap {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_NewWorldAllianceMap_2eproto();
void protobuf_AssignDesc_NewWorldAllianceMap_2eproto();
void protobuf_ShutdownFile_NewWorldAllianceMap_2eproto();

class NewWorldAllianceMapAlliance;
class NewWorldAllianceMap;

// ===================================================================

class NewWorldAllianceMapAlliance : public ::google::protobuf::Message {
 public:
  NewWorldAllianceMapAlliance();
  virtual ~NewWorldAllianceMapAlliance();

  NewWorldAllianceMapAlliance(const NewWorldAllianceMapAlliance& from);

  inline NewWorldAllianceMapAlliance& operator=(const NewWorldAllianceMapAlliance& from) {
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
  static const NewWorldAllianceMapAlliance& default_instance();

  void Swap(NewWorldAllianceMapAlliance* other);

  // implements Message ----------------------------------------------

  NewWorldAllianceMapAlliance* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const NewWorldAllianceMapAlliance& from);
  void MergeFrom(const NewWorldAllianceMapAlliance& from);
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

  // required uint32 rid = 1;
  inline bool has_rid() const;
  inline void clear_rid();
  static const int kRidFieldNumber = 1;
  inline ::google::protobuf::uint32 rid() const;
  inline void set_rid(::google::protobuf::uint32 value);

  // required uint32 level = 2;
  inline bool has_level() const;
  inline void clear_level();
  static const int kLevelFieldNumber = 2;
  inline ::google::protobuf::uint32 level() const;
  inline void set_level(::google::protobuf::uint32 value);

  // required uint32 reward = 3;
  inline bool has_reward() const;
  inline void clear_reward();
  static const int kRewardFieldNumber = 3;
  inline ::google::protobuf::uint32 reward() const;
  inline void set_reward(::google::protobuf::uint32 value);

  // repeated uint32 aid = 4;
  inline int aid_size() const;
  inline void clear_aid();
  static const int kAidFieldNumber = 4;
  inline ::google::protobuf::uint32 aid(int index) const;
  inline void set_aid(int index, ::google::protobuf::uint32 value);
  inline void add_aid(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      aid() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_aid();

  // @@protoc_insertion_point(class_scope:NewWorldAllianceMap.NewWorldAllianceMapAlliance)
 private:
  inline void set_has_rid();
  inline void clear_has_rid();
  inline void set_has_level();
  inline void clear_has_level();
  inline void set_has_reward();
  inline void clear_has_reward();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 rid_;
  ::google::protobuf::uint32 level_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > aid_;
  ::google::protobuf::uint32 reward_;
  friend void  protobuf_AddDesc_NewWorldAllianceMap_2eproto();
  friend void protobuf_AssignDesc_NewWorldAllianceMap_2eproto();
  friend void protobuf_ShutdownFile_NewWorldAllianceMap_2eproto();

  void InitAsDefaultInstance();
  static NewWorldAllianceMapAlliance* default_instance_;
};
// -------------------------------------------------------------------

class NewWorldAllianceMap : public ::google::protobuf::Message {
 public:
  NewWorldAllianceMap();
  virtual ~NewWorldAllianceMap();

  NewWorldAllianceMap(const NewWorldAllianceMap& from);

  inline NewWorldAllianceMap& operator=(const NewWorldAllianceMap& from) {
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
  static const NewWorldAllianceMap& default_instance();

  void Swap(NewWorldAllianceMap* other);

  // implements Message ----------------------------------------------

  NewWorldAllianceMap* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const NewWorldAllianceMap& from);
  void MergeFrom(const NewWorldAllianceMap& from);
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

  // repeated .NewWorldAllianceMap.NewWorldAllianceMapAlliance alliance = 1;
  inline int alliance_size() const;
  inline void clear_alliance();
  static const int kAllianceFieldNumber = 1;
  inline const ::NewWorldAllianceMap::NewWorldAllianceMapAlliance& alliance(int index) const;
  inline ::NewWorldAllianceMap::NewWorldAllianceMapAlliance* mutable_alliance(int index);
  inline ::NewWorldAllianceMap::NewWorldAllianceMapAlliance* add_alliance();
  inline const ::google::protobuf::RepeatedPtrField< ::NewWorldAllianceMap::NewWorldAllianceMapAlliance >&
      alliance() const;
  inline ::google::protobuf::RepeatedPtrField< ::NewWorldAllianceMap::NewWorldAllianceMapAlliance >*
      mutable_alliance();

  // @@protoc_insertion_point(class_scope:NewWorldAllianceMap.NewWorldAllianceMap)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::NewWorldAllianceMap::NewWorldAllianceMapAlliance > alliance_;
  friend void  protobuf_AddDesc_NewWorldAllianceMap_2eproto();
  friend void protobuf_AssignDesc_NewWorldAllianceMap_2eproto();
  friend void protobuf_ShutdownFile_NewWorldAllianceMap_2eproto();

  void InitAsDefaultInstance();
  static NewWorldAllianceMap* default_instance_;
};
// ===================================================================


// ===================================================================

// NewWorldAllianceMapAlliance

// required uint32 rid = 1;
inline bool NewWorldAllianceMapAlliance::has_rid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void NewWorldAllianceMapAlliance::set_has_rid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void NewWorldAllianceMapAlliance::clear_has_rid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void NewWorldAllianceMapAlliance::clear_rid() {
  rid_ = 0u;
  clear_has_rid();
}
inline ::google::protobuf::uint32 NewWorldAllianceMapAlliance::rid() const {
  // @@protoc_insertion_point(field_get:NewWorldAllianceMap.NewWorldAllianceMapAlliance.rid)
  return rid_;
}
inline void NewWorldAllianceMapAlliance::set_rid(::google::protobuf::uint32 value) {
  set_has_rid();
  rid_ = value;
  // @@protoc_insertion_point(field_set:NewWorldAllianceMap.NewWorldAllianceMapAlliance.rid)
}

// required uint32 level = 2;
inline bool NewWorldAllianceMapAlliance::has_level() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void NewWorldAllianceMapAlliance::set_has_level() {
  _has_bits_[0] |= 0x00000002u;
}
inline void NewWorldAllianceMapAlliance::clear_has_level() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void NewWorldAllianceMapAlliance::clear_level() {
  level_ = 0u;
  clear_has_level();
}
inline ::google::protobuf::uint32 NewWorldAllianceMapAlliance::level() const {
  // @@protoc_insertion_point(field_get:NewWorldAllianceMap.NewWorldAllianceMapAlliance.level)
  return level_;
}
inline void NewWorldAllianceMapAlliance::set_level(::google::protobuf::uint32 value) {
  set_has_level();
  level_ = value;
  // @@protoc_insertion_point(field_set:NewWorldAllianceMap.NewWorldAllianceMapAlliance.level)
}

// required uint32 reward = 3;
inline bool NewWorldAllianceMapAlliance::has_reward() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void NewWorldAllianceMapAlliance::set_has_reward() {
  _has_bits_[0] |= 0x00000004u;
}
inline void NewWorldAllianceMapAlliance::clear_has_reward() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void NewWorldAllianceMapAlliance::clear_reward() {
  reward_ = 0u;
  clear_has_reward();
}
inline ::google::protobuf::uint32 NewWorldAllianceMapAlliance::reward() const {
  // @@protoc_insertion_point(field_get:NewWorldAllianceMap.NewWorldAllianceMapAlliance.reward)
  return reward_;
}
inline void NewWorldAllianceMapAlliance::set_reward(::google::protobuf::uint32 value) {
  set_has_reward();
  reward_ = value;
  // @@protoc_insertion_point(field_set:NewWorldAllianceMap.NewWorldAllianceMapAlliance.reward)
}

// repeated uint32 aid = 4;
inline int NewWorldAllianceMapAlliance::aid_size() const {
  return aid_.size();
}
inline void NewWorldAllianceMapAlliance::clear_aid() {
  aid_.Clear();
}
inline ::google::protobuf::uint32 NewWorldAllianceMapAlliance::aid(int index) const {
  // @@protoc_insertion_point(field_get:NewWorldAllianceMap.NewWorldAllianceMapAlliance.aid)
  return aid_.Get(index);
}
inline void NewWorldAllianceMapAlliance::set_aid(int index, ::google::protobuf::uint32 value) {
  aid_.Set(index, value);
  // @@protoc_insertion_point(field_set:NewWorldAllianceMap.NewWorldAllianceMapAlliance.aid)
}
inline void NewWorldAllianceMapAlliance::add_aid(::google::protobuf::uint32 value) {
  aid_.Add(value);
  // @@protoc_insertion_point(field_add:NewWorldAllianceMap.NewWorldAllianceMapAlliance.aid)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
NewWorldAllianceMapAlliance::aid() const {
  // @@protoc_insertion_point(field_list:NewWorldAllianceMap.NewWorldAllianceMapAlliance.aid)
  return aid_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
NewWorldAllianceMapAlliance::mutable_aid() {
  // @@protoc_insertion_point(field_mutable_list:NewWorldAllianceMap.NewWorldAllianceMapAlliance.aid)
  return &aid_;
}

// -------------------------------------------------------------------

// NewWorldAllianceMap

// repeated .NewWorldAllianceMap.NewWorldAllianceMapAlliance alliance = 1;
inline int NewWorldAllianceMap::alliance_size() const {
  return alliance_.size();
}
inline void NewWorldAllianceMap::clear_alliance() {
  alliance_.Clear();
}
inline const ::NewWorldAllianceMap::NewWorldAllianceMapAlliance& NewWorldAllianceMap::alliance(int index) const {
  // @@protoc_insertion_point(field_get:NewWorldAllianceMap.NewWorldAllianceMap.alliance)
  return alliance_.Get(index);
}
inline ::NewWorldAllianceMap::NewWorldAllianceMapAlliance* NewWorldAllianceMap::mutable_alliance(int index) {
  // @@protoc_insertion_point(field_mutable:NewWorldAllianceMap.NewWorldAllianceMap.alliance)
  return alliance_.Mutable(index);
}
inline ::NewWorldAllianceMap::NewWorldAllianceMapAlliance* NewWorldAllianceMap::add_alliance() {
  // @@protoc_insertion_point(field_add:NewWorldAllianceMap.NewWorldAllianceMap.alliance)
  return alliance_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::NewWorldAllianceMap::NewWorldAllianceMapAlliance >&
NewWorldAllianceMap::alliance() const {
  // @@protoc_insertion_point(field_list:NewWorldAllianceMap.NewWorldAllianceMap.alliance)
  return alliance_;
}
inline ::google::protobuf::RepeatedPtrField< ::NewWorldAllianceMap::NewWorldAllianceMapAlliance >*
NewWorldAllianceMap::mutable_alliance() {
  // @@protoc_insertion_point(field_mutable_list:NewWorldAllianceMap.NewWorldAllianceMap.alliance)
  return &alliance_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace NewWorldAllianceMap

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_NewWorldAllianceMap_2eproto__INCLUDED