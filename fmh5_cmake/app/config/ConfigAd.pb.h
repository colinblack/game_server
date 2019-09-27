// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ConfigAd.proto

#ifndef PROTOBUF_ConfigAd_2eproto__INCLUDED
#define PROTOBUF_ConfigAd_2eproto__INCLUDED

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

namespace ConfigAd {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ConfigAd_2eproto();
void protobuf_AssignDesc_ConfigAd_2eproto();
void protobuf_ShutdownFile_ConfigAd_2eproto();

class AdCPP;
class AdInfo;

// ===================================================================

class AdCPP : public ::google::protobuf::Message {
 public:
  AdCPP();
  virtual ~AdCPP();

  AdCPP(const AdCPP& from);

  inline AdCPP& operator=(const AdCPP& from) {
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
  static const AdCPP& default_instance();

  void Swap(AdCPP* other);

  // implements Message ----------------------------------------------

  AdCPP* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AdCPP& from);
  void MergeFrom(const AdCPP& from);
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

  // required uint32 adCnt = 1;
  inline bool has_adcnt() const;
  inline void clear_adcnt();
  static const int kAdCntFieldNumber = 1;
  inline ::google::protobuf::uint32 adcnt() const;
  inline void set_adcnt(::google::protobuf::uint32 value);

  // required uint32 adTime = 2;
  inline bool has_adtime() const;
  inline void clear_adtime();
  static const int kAdTimeFieldNumber = 2;
  inline ::google::protobuf::uint32 adtime() const;
  inline void set_adtime(::google::protobuf::uint32 value);

  // required uint32 coolAdCost = 3;
  inline bool has_cooladcost() const;
  inline void clear_cooladcost();
  static const int kCoolAdCostFieldNumber = 3;
  inline ::google::protobuf::uint32 cooladcost() const;
  inline void set_cooladcost(::google::protobuf::uint32 value);

  // required uint32 delOrderCost = 4;
  inline bool has_delordercost() const;
  inline void clear_delordercost();
  static const int kDelOrderCostFieldNumber = 4;
  inline ::google::protobuf::uint32 delordercost() const;
  inline void set_delordercost(::google::protobuf::uint32 value);

  // required uint32 adCdTs = 5;
  inline bool has_adcdts() const;
  inline void clear_adcdts();
  static const int kAdCdTsFieldNumber = 5;
  inline ::google::protobuf::uint32 adcdts() const;
  inline void set_adcdts(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:ConfigAd.AdCPP)
 private:
  inline void set_has_adcnt();
  inline void clear_has_adcnt();
  inline void set_has_adtime();
  inline void clear_has_adtime();
  inline void set_has_cooladcost();
  inline void clear_has_cooladcost();
  inline void set_has_delordercost();
  inline void clear_has_delordercost();
  inline void set_has_adcdts();
  inline void clear_has_adcdts();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 adcnt_;
  ::google::protobuf::uint32 adtime_;
  ::google::protobuf::uint32 cooladcost_;
  ::google::protobuf::uint32 delordercost_;
  ::google::protobuf::uint32 adcdts_;
  friend void  protobuf_AddDesc_ConfigAd_2eproto();
  friend void protobuf_AssignDesc_ConfigAd_2eproto();
  friend void protobuf_ShutdownFile_ConfigAd_2eproto();

  void InitAsDefaultInstance();
  static AdCPP* default_instance_;
};
// -------------------------------------------------------------------

class AdInfo : public ::google::protobuf::Message {
 public:
  AdInfo();
  virtual ~AdInfo();

  AdInfo(const AdInfo& from);

  inline AdInfo& operator=(const AdInfo& from) {
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
  static const AdInfo& default_instance();

  void Swap(AdInfo* other);

  // implements Message ----------------------------------------------

  AdInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AdInfo& from);
  void MergeFrom(const AdInfo& from);
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

  // required .ConfigAd.AdCPP adInfo = 1;
  inline bool has_adinfo() const;
  inline void clear_adinfo();
  static const int kAdInfoFieldNumber = 1;
  inline const ::ConfigAd::AdCPP& adinfo() const;
  inline ::ConfigAd::AdCPP* mutable_adinfo();
  inline ::ConfigAd::AdCPP* release_adinfo();
  inline void set_allocated_adinfo(::ConfigAd::AdCPP* adinfo);

  // @@protoc_insertion_point(class_scope:ConfigAd.AdInfo)
 private:
  inline void set_has_adinfo();
  inline void clear_has_adinfo();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::ConfigAd::AdCPP* adinfo_;
  friend void  protobuf_AddDesc_ConfigAd_2eproto();
  friend void protobuf_AssignDesc_ConfigAd_2eproto();
  friend void protobuf_ShutdownFile_ConfigAd_2eproto();

  void InitAsDefaultInstance();
  static AdInfo* default_instance_;
};
// ===================================================================


// ===================================================================

// AdCPP

// required uint32 adCnt = 1;
inline bool AdCPP::has_adcnt() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AdCPP::set_has_adcnt() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AdCPP::clear_has_adcnt() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AdCPP::clear_adcnt() {
  adcnt_ = 0u;
  clear_has_adcnt();
}
inline ::google::protobuf::uint32 AdCPP::adcnt() const {
  // @@protoc_insertion_point(field_get:ConfigAd.AdCPP.adCnt)
  return adcnt_;
}
inline void AdCPP::set_adcnt(::google::protobuf::uint32 value) {
  set_has_adcnt();
  adcnt_ = value;
  // @@protoc_insertion_point(field_set:ConfigAd.AdCPP.adCnt)
}

// required uint32 adTime = 2;
inline bool AdCPP::has_adtime() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AdCPP::set_has_adtime() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AdCPP::clear_has_adtime() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AdCPP::clear_adtime() {
  adtime_ = 0u;
  clear_has_adtime();
}
inline ::google::protobuf::uint32 AdCPP::adtime() const {
  // @@protoc_insertion_point(field_get:ConfigAd.AdCPP.adTime)
  return adtime_;
}
inline void AdCPP::set_adtime(::google::protobuf::uint32 value) {
  set_has_adtime();
  adtime_ = value;
  // @@protoc_insertion_point(field_set:ConfigAd.AdCPP.adTime)
}

// required uint32 coolAdCost = 3;
inline bool AdCPP::has_cooladcost() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void AdCPP::set_has_cooladcost() {
  _has_bits_[0] |= 0x00000004u;
}
inline void AdCPP::clear_has_cooladcost() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void AdCPP::clear_cooladcost() {
  cooladcost_ = 0u;
  clear_has_cooladcost();
}
inline ::google::protobuf::uint32 AdCPP::cooladcost() const {
  // @@protoc_insertion_point(field_get:ConfigAd.AdCPP.coolAdCost)
  return cooladcost_;
}
inline void AdCPP::set_cooladcost(::google::protobuf::uint32 value) {
  set_has_cooladcost();
  cooladcost_ = value;
  // @@protoc_insertion_point(field_set:ConfigAd.AdCPP.coolAdCost)
}

// required uint32 delOrderCost = 4;
inline bool AdCPP::has_delordercost() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void AdCPP::set_has_delordercost() {
  _has_bits_[0] |= 0x00000008u;
}
inline void AdCPP::clear_has_delordercost() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void AdCPP::clear_delordercost() {
  delordercost_ = 0u;
  clear_has_delordercost();
}
inline ::google::protobuf::uint32 AdCPP::delordercost() const {
  // @@protoc_insertion_point(field_get:ConfigAd.AdCPP.delOrderCost)
  return delordercost_;
}
inline void AdCPP::set_delordercost(::google::protobuf::uint32 value) {
  set_has_delordercost();
  delordercost_ = value;
  // @@protoc_insertion_point(field_set:ConfigAd.AdCPP.delOrderCost)
}

// required uint32 adCdTs = 5;
inline bool AdCPP::has_adcdts() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void AdCPP::set_has_adcdts() {
  _has_bits_[0] |= 0x00000010u;
}
inline void AdCPP::clear_has_adcdts() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void AdCPP::clear_adcdts() {
  adcdts_ = 0u;
  clear_has_adcdts();
}
inline ::google::protobuf::uint32 AdCPP::adcdts() const {
  // @@protoc_insertion_point(field_get:ConfigAd.AdCPP.adCdTs)
  return adcdts_;
}
inline void AdCPP::set_adcdts(::google::protobuf::uint32 value) {
  set_has_adcdts();
  adcdts_ = value;
  // @@protoc_insertion_point(field_set:ConfigAd.AdCPP.adCdTs)
}

// -------------------------------------------------------------------

// AdInfo

// required .ConfigAd.AdCPP adInfo = 1;
inline bool AdInfo::has_adinfo() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AdInfo::set_has_adinfo() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AdInfo::clear_has_adinfo() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AdInfo::clear_adinfo() {
  if (adinfo_ != NULL) adinfo_->::ConfigAd::AdCPP::Clear();
  clear_has_adinfo();
}
inline const ::ConfigAd::AdCPP& AdInfo::adinfo() const {
  // @@protoc_insertion_point(field_get:ConfigAd.AdInfo.adInfo)
  return adinfo_ != NULL ? *adinfo_ : *default_instance_->adinfo_;
}
inline ::ConfigAd::AdCPP* AdInfo::mutable_adinfo() {
  set_has_adinfo();
  if (adinfo_ == NULL) adinfo_ = new ::ConfigAd::AdCPP;
  // @@protoc_insertion_point(field_mutable:ConfigAd.AdInfo.adInfo)
  return adinfo_;
}
inline ::ConfigAd::AdCPP* AdInfo::release_adinfo() {
  clear_has_adinfo();
  ::ConfigAd::AdCPP* temp = adinfo_;
  adinfo_ = NULL;
  return temp;
}
inline void AdInfo::set_allocated_adinfo(::ConfigAd::AdCPP* adinfo) {
  delete adinfo_;
  adinfo_ = adinfo;
  if (adinfo) {
    set_has_adinfo();
  } else {
    clear_has_adinfo();
  }
  // @@protoc_insertion_point(field_set_allocated:ConfigAd.AdInfo.adInfo)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ConfigAd

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ConfigAd_2eproto__INCLUDED
