// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: BattleDemoConfig.proto

#ifndef PROTOBUF_BattleDemoConfig_2eproto__INCLUDED
#define PROTOBUF_BattleDemoConfig_2eproto__INCLUDED

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

namespace BattleDemoConfig {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_BattleDemoConfig_2eproto();
void protobuf_AssignDesc_BattleDemoConfig_2eproto();
void protobuf_ShutdownFile_BattleDemoConfig_2eproto();

class BattleDemoConfig;

// ===================================================================

class BattleDemoConfig : public ::google::protobuf::Message {
 public:
  BattleDemoConfig();
  virtual ~BattleDemoConfig();
  
  BattleDemoConfig(const BattleDemoConfig& from);
  
  inline BattleDemoConfig& operator=(const BattleDemoConfig& from) {
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
  static const BattleDemoConfig& default_instance();
  
  void Swap(BattleDemoConfig* other);
  
  // implements Message ----------------------------------------------
  
  BattleDemoConfig* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BattleDemoConfig& from);
  void MergeFrom(const BattleDemoConfig& from);
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
  
  // required uint32 turn_max = 1;
  inline bool has_turn_max() const;
  inline void clear_turn_max();
  static const int kTurnMaxFieldNumber = 1;
  inline ::google::protobuf::uint32 turn_max() const;
  inline void set_turn_max(::google::protobuf::uint32 value);
  
  // required double dodge_p = 2;
  inline bool has_dodge_p() const;
  inline void clear_dodge_p();
  static const int kDodgePFieldNumber = 2;
  inline double dodge_p() const;
  inline void set_dodge_p(double value);
  
  // required uint32 dodge_max = 3;
  inline bool has_dodge_max() const;
  inline void clear_dodge_max();
  static const int kDodgeMaxFieldNumber = 3;
  inline ::google::protobuf::uint32 dodge_max() const;
  inline void set_dodge_max(::google::protobuf::uint32 value);
  
  // required uint32 dodge_min = 4;
  inline bool has_dodge_min() const;
  inline void clear_dodge_min();
  static const int kDodgeMinFieldNumber = 4;
  inline ::google::protobuf::uint32 dodge_min() const;
  inline void set_dodge_min(::google::protobuf::uint32 value);
  
  // required uint32 dodge_c = 5;
  inline bool has_dodge_c() const;
  inline void clear_dodge_c();
  static const int kDodgeCFieldNumber = 5;
  inline ::google::protobuf::uint32 dodge_c() const;
  inline void set_dodge_c(::google::protobuf::uint32 value);
  
  // required double crit_p = 6;
  inline bool has_crit_p() const;
  inline void clear_crit_p();
  static const int kCritPFieldNumber = 6;
  inline double crit_p() const;
  inline void set_crit_p(double value);
  
  // required uint32 crit_max = 7;
  inline bool has_crit_max() const;
  inline void clear_crit_max();
  static const int kCritMaxFieldNumber = 7;
  inline ::google::protobuf::uint32 crit_max() const;
  inline void set_crit_max(::google::protobuf::uint32 value);
  
  // required uint32 crit_min = 8;
  inline bool has_crit_min() const;
  inline void clear_crit_min();
  static const int kCritMinFieldNumber = 8;
  inline ::google::protobuf::uint32 crit_min() const;
  inline void set_crit_min(::google::protobuf::uint32 value);
  
  // repeated uint32 crit_l = 9;
  inline int crit_l_size() const;
  inline void clear_crit_l();
  static const int kCritLFieldNumber = 9;
  inline ::google::protobuf::uint32 crit_l(int index) const;
  inline void set_crit_l(int index, ::google::protobuf::uint32 value);
  inline void add_crit_l(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      crit_l() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_crit_l();
  
  // repeated uint32 crit_c = 10;
  inline int crit_c_size() const;
  inline void clear_crit_c();
  static const int kCritCFieldNumber = 10;
  inline ::google::protobuf::uint32 crit_c(int index) const;
  inline void set_crit_c(int index, ::google::protobuf::uint32 value);
  inline void add_crit_c(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      crit_c() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_crit_c();
  
  // required double att_p = 11;
  inline bool has_att_p() const;
  inline void clear_att_p();
  static const int kAttPFieldNumber = 11;
  inline double att_p() const;
  inline void set_att_p(double value);
  
  // required double def_p = 12;
  inline bool has_def_p() const;
  inline void clear_def_p();
  static const int kDefPFieldNumber = 12;
  inline double def_p() const;
  inline void set_def_p(double value);
  
  // repeated uint32 skill_power = 13;
  inline int skill_power_size() const;
  inline void clear_skill_power();
  static const int kSkillPowerFieldNumber = 13;
  inline ::google::protobuf::uint32 skill_power(int index) const;
  inline void set_skill_power(int index, ::google::protobuf::uint32 value);
  inline void add_skill_power(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      skill_power() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_skill_power();
  
  // required uint32 slow_power = 14;
  inline bool has_slow_power() const;
  inline void clear_slow_power();
  static const int kSlowPowerFieldNumber = 14;
  inline ::google::protobuf::uint32 slow_power() const;
  inline void set_slow_power(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:BattleDemoConfig.BattleDemoConfig)
 private:
  inline void set_has_turn_max();
  inline void clear_has_turn_max();
  inline void set_has_dodge_p();
  inline void clear_has_dodge_p();
  inline void set_has_dodge_max();
  inline void clear_has_dodge_max();
  inline void set_has_dodge_min();
  inline void clear_has_dodge_min();
  inline void set_has_dodge_c();
  inline void clear_has_dodge_c();
  inline void set_has_crit_p();
  inline void clear_has_crit_p();
  inline void set_has_crit_max();
  inline void clear_has_crit_max();
  inline void set_has_crit_min();
  inline void clear_has_crit_min();
  inline void set_has_att_p();
  inline void clear_has_att_p();
  inline void set_has_def_p();
  inline void clear_has_def_p();
  inline void set_has_slow_power();
  inline void clear_has_slow_power();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  double dodge_p_;
  ::google::protobuf::uint32 turn_max_;
  ::google::protobuf::uint32 dodge_max_;
  ::google::protobuf::uint32 dodge_min_;
  ::google::protobuf::uint32 dodge_c_;
  double crit_p_;
  ::google::protobuf::uint32 crit_max_;
  ::google::protobuf::uint32 crit_min_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > crit_l_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > crit_c_;
  double att_p_;
  double def_p_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > skill_power_;
  ::google::protobuf::uint32 slow_power_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(14 + 31) / 32];
  
  friend void  protobuf_AddDesc_BattleDemoConfig_2eproto();
  friend void protobuf_AssignDesc_BattleDemoConfig_2eproto();
  friend void protobuf_ShutdownFile_BattleDemoConfig_2eproto();
  
  void InitAsDefaultInstance();
  static BattleDemoConfig* default_instance_;
};
// ===================================================================


// ===================================================================

// BattleDemoConfig

// required uint32 turn_max = 1;
inline bool BattleDemoConfig::has_turn_max() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void BattleDemoConfig::set_has_turn_max() {
  _has_bits_[0] |= 0x00000001u;
}
inline void BattleDemoConfig::clear_has_turn_max() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void BattleDemoConfig::clear_turn_max() {
  turn_max_ = 0u;
  clear_has_turn_max();
}
inline ::google::protobuf::uint32 BattleDemoConfig::turn_max() const {
  return turn_max_;
}
inline void BattleDemoConfig::set_turn_max(::google::protobuf::uint32 value) {
  set_has_turn_max();
  turn_max_ = value;
}

// required double dodge_p = 2;
inline bool BattleDemoConfig::has_dodge_p() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void BattleDemoConfig::set_has_dodge_p() {
  _has_bits_[0] |= 0x00000002u;
}
inline void BattleDemoConfig::clear_has_dodge_p() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void BattleDemoConfig::clear_dodge_p() {
  dodge_p_ = 0;
  clear_has_dodge_p();
}
inline double BattleDemoConfig::dodge_p() const {
  return dodge_p_;
}
inline void BattleDemoConfig::set_dodge_p(double value) {
  set_has_dodge_p();
  dodge_p_ = value;
}

// required uint32 dodge_max = 3;
inline bool BattleDemoConfig::has_dodge_max() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void BattleDemoConfig::set_has_dodge_max() {
  _has_bits_[0] |= 0x00000004u;
}
inline void BattleDemoConfig::clear_has_dodge_max() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void BattleDemoConfig::clear_dodge_max() {
  dodge_max_ = 0u;
  clear_has_dodge_max();
}
inline ::google::protobuf::uint32 BattleDemoConfig::dodge_max() const {
  return dodge_max_;
}
inline void BattleDemoConfig::set_dodge_max(::google::protobuf::uint32 value) {
  set_has_dodge_max();
  dodge_max_ = value;
}

// required uint32 dodge_min = 4;
inline bool BattleDemoConfig::has_dodge_min() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void BattleDemoConfig::set_has_dodge_min() {
  _has_bits_[0] |= 0x00000008u;
}
inline void BattleDemoConfig::clear_has_dodge_min() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void BattleDemoConfig::clear_dodge_min() {
  dodge_min_ = 0u;
  clear_has_dodge_min();
}
inline ::google::protobuf::uint32 BattleDemoConfig::dodge_min() const {
  return dodge_min_;
}
inline void BattleDemoConfig::set_dodge_min(::google::protobuf::uint32 value) {
  set_has_dodge_min();
  dodge_min_ = value;
}

// required uint32 dodge_c = 5;
inline bool BattleDemoConfig::has_dodge_c() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void BattleDemoConfig::set_has_dodge_c() {
  _has_bits_[0] |= 0x00000010u;
}
inline void BattleDemoConfig::clear_has_dodge_c() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void BattleDemoConfig::clear_dodge_c() {
  dodge_c_ = 0u;
  clear_has_dodge_c();
}
inline ::google::protobuf::uint32 BattleDemoConfig::dodge_c() const {
  return dodge_c_;
}
inline void BattleDemoConfig::set_dodge_c(::google::protobuf::uint32 value) {
  set_has_dodge_c();
  dodge_c_ = value;
}

// required double crit_p = 6;
inline bool BattleDemoConfig::has_crit_p() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void BattleDemoConfig::set_has_crit_p() {
  _has_bits_[0] |= 0x00000020u;
}
inline void BattleDemoConfig::clear_has_crit_p() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void BattleDemoConfig::clear_crit_p() {
  crit_p_ = 0;
  clear_has_crit_p();
}
inline double BattleDemoConfig::crit_p() const {
  return crit_p_;
}
inline void BattleDemoConfig::set_crit_p(double value) {
  set_has_crit_p();
  crit_p_ = value;
}

// required uint32 crit_max = 7;
inline bool BattleDemoConfig::has_crit_max() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void BattleDemoConfig::set_has_crit_max() {
  _has_bits_[0] |= 0x00000040u;
}
inline void BattleDemoConfig::clear_has_crit_max() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void BattleDemoConfig::clear_crit_max() {
  crit_max_ = 0u;
  clear_has_crit_max();
}
inline ::google::protobuf::uint32 BattleDemoConfig::crit_max() const {
  return crit_max_;
}
inline void BattleDemoConfig::set_crit_max(::google::protobuf::uint32 value) {
  set_has_crit_max();
  crit_max_ = value;
}

// required uint32 crit_min = 8;
inline bool BattleDemoConfig::has_crit_min() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void BattleDemoConfig::set_has_crit_min() {
  _has_bits_[0] |= 0x00000080u;
}
inline void BattleDemoConfig::clear_has_crit_min() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void BattleDemoConfig::clear_crit_min() {
  crit_min_ = 0u;
  clear_has_crit_min();
}
inline ::google::protobuf::uint32 BattleDemoConfig::crit_min() const {
  return crit_min_;
}
inline void BattleDemoConfig::set_crit_min(::google::protobuf::uint32 value) {
  set_has_crit_min();
  crit_min_ = value;
}

// repeated uint32 crit_l = 9;
inline int BattleDemoConfig::crit_l_size() const {
  return crit_l_.size();
}
inline void BattleDemoConfig::clear_crit_l() {
  crit_l_.Clear();
}
inline ::google::protobuf::uint32 BattleDemoConfig::crit_l(int index) const {
  return crit_l_.Get(index);
}
inline void BattleDemoConfig::set_crit_l(int index, ::google::protobuf::uint32 value) {
  crit_l_.Set(index, value);
}
inline void BattleDemoConfig::add_crit_l(::google::protobuf::uint32 value) {
  crit_l_.Add(value);
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
BattleDemoConfig::crit_l() const {
  return crit_l_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
BattleDemoConfig::mutable_crit_l() {
  return &crit_l_;
}

// repeated uint32 crit_c = 10;
inline int BattleDemoConfig::crit_c_size() const {
  return crit_c_.size();
}
inline void BattleDemoConfig::clear_crit_c() {
  crit_c_.Clear();
}
inline ::google::protobuf::uint32 BattleDemoConfig::crit_c(int index) const {
  return crit_c_.Get(index);
}
inline void BattleDemoConfig::set_crit_c(int index, ::google::protobuf::uint32 value) {
  crit_c_.Set(index, value);
}
inline void BattleDemoConfig::add_crit_c(::google::protobuf::uint32 value) {
  crit_c_.Add(value);
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
BattleDemoConfig::crit_c() const {
  return crit_c_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
BattleDemoConfig::mutable_crit_c() {
  return &crit_c_;
}

// required double att_p = 11;
inline bool BattleDemoConfig::has_att_p() const {
  return (_has_bits_[0] & 0x00000400u) != 0;
}
inline void BattleDemoConfig::set_has_att_p() {
  _has_bits_[0] |= 0x00000400u;
}
inline void BattleDemoConfig::clear_has_att_p() {
  _has_bits_[0] &= ~0x00000400u;
}
inline void BattleDemoConfig::clear_att_p() {
  att_p_ = 0;
  clear_has_att_p();
}
inline double BattleDemoConfig::att_p() const {
  return att_p_;
}
inline void BattleDemoConfig::set_att_p(double value) {
  set_has_att_p();
  att_p_ = value;
}

// required double def_p = 12;
inline bool BattleDemoConfig::has_def_p() const {
  return (_has_bits_[0] & 0x00000800u) != 0;
}
inline void BattleDemoConfig::set_has_def_p() {
  _has_bits_[0] |= 0x00000800u;
}
inline void BattleDemoConfig::clear_has_def_p() {
  _has_bits_[0] &= ~0x00000800u;
}
inline void BattleDemoConfig::clear_def_p() {
  def_p_ = 0;
  clear_has_def_p();
}
inline double BattleDemoConfig::def_p() const {
  return def_p_;
}
inline void BattleDemoConfig::set_def_p(double value) {
  set_has_def_p();
  def_p_ = value;
}

// repeated uint32 skill_power = 13;
inline int BattleDemoConfig::skill_power_size() const {
  return skill_power_.size();
}
inline void BattleDemoConfig::clear_skill_power() {
  skill_power_.Clear();
}
inline ::google::protobuf::uint32 BattleDemoConfig::skill_power(int index) const {
  return skill_power_.Get(index);
}
inline void BattleDemoConfig::set_skill_power(int index, ::google::protobuf::uint32 value) {
  skill_power_.Set(index, value);
}
inline void BattleDemoConfig::add_skill_power(::google::protobuf::uint32 value) {
  skill_power_.Add(value);
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
BattleDemoConfig::skill_power() const {
  return skill_power_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
BattleDemoConfig::mutable_skill_power() {
  return &skill_power_;
}

// required uint32 slow_power = 14;
inline bool BattleDemoConfig::has_slow_power() const {
  return (_has_bits_[0] & 0x00002000u) != 0;
}
inline void BattleDemoConfig::set_has_slow_power() {
  _has_bits_[0] |= 0x00002000u;
}
inline void BattleDemoConfig::clear_has_slow_power() {
  _has_bits_[0] &= ~0x00002000u;
}
inline void BattleDemoConfig::clear_slow_power() {
  slow_power_ = 0u;
  clear_has_slow_power();
}
inline ::google::protobuf::uint32 BattleDemoConfig::slow_power() const {
  return slow_power_;
}
inline void BattleDemoConfig::set_slow_power(::google::protobuf::uint32 value) {
  set_has_slow_power();
  slow_power_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace BattleDemoConfig

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_BattleDemoConfig_2eproto__INCLUDED