// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ConfigScrollFeedback.proto

#ifndef PROTOBUF_ConfigScrollFeedback_2eproto__INCLUDED
#define PROTOBUF_ConfigScrollFeedback_2eproto__INCLUDED

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
#include "RewardConfig.pb.h"
// @@protoc_insertion_point(includes)

namespace ConfigScrollFeedback {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ConfigScrollFeedback_2eproto();
void protobuf_AssignDesc_ConfigScrollFeedback_2eproto();
void protobuf_ShutdownFile_ConfigScrollFeedback_2eproto();

class FeedBackItem;
class ScrollFeedBack;

// ===================================================================

class FeedBackItem : public ::google::protobuf::Message {
 public:
  FeedBackItem();
  virtual ~FeedBackItem();

  FeedBackItem(const FeedBackItem& from);

  inline FeedBackItem& operator=(const FeedBackItem& from) {
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
  static const FeedBackItem& default_instance();

  void Swap(FeedBackItem* other);

  // implements Message ----------------------------------------------

  FeedBackItem* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const FeedBackItem& from);
  void MergeFrom(const FeedBackItem& from);
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

  // required uint32 diamond = 1;
  inline bool has_diamond() const;
  inline void clear_diamond();
  static const int kDiamondFieldNumber = 1;
  inline ::google::protobuf::uint32 diamond() const;
  inline void set_diamond(::google::protobuf::uint32 value);

  // required .RewardConfig.RewardItemCfg reward = 2;
  inline bool has_reward() const;
  inline void clear_reward();
  static const int kRewardFieldNumber = 2;
  inline const ::RewardConfig::RewardItemCfg& reward() const;
  inline ::RewardConfig::RewardItemCfg* mutable_reward();
  inline ::RewardConfig::RewardItemCfg* release_reward();
  inline void set_allocated_reward(::RewardConfig::RewardItemCfg* reward);

  // @@protoc_insertion_point(class_scope:ConfigScrollFeedback.FeedBackItem)
 private:
  inline void set_has_diamond();
  inline void clear_has_diamond();
  inline void set_has_reward();
  inline void clear_has_reward();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::RewardConfig::RewardItemCfg* reward_;
  ::google::protobuf::uint32 diamond_;
  friend void  protobuf_AddDesc_ConfigScrollFeedback_2eproto();
  friend void protobuf_AssignDesc_ConfigScrollFeedback_2eproto();
  friend void protobuf_ShutdownFile_ConfigScrollFeedback_2eproto();

  void InitAsDefaultInstance();
  static FeedBackItem* default_instance_;
};
// -------------------------------------------------------------------

class ScrollFeedBack : public ::google::protobuf::Message {
 public:
  ScrollFeedBack();
  virtual ~ScrollFeedBack();

  ScrollFeedBack(const ScrollFeedBack& from);

  inline ScrollFeedBack& operator=(const ScrollFeedBack& from) {
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
  static const ScrollFeedBack& default_instance();

  void Swap(ScrollFeedBack* other);

  // implements Message ----------------------------------------------

  ScrollFeedBack* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ScrollFeedBack& from);
  void MergeFrom(const ScrollFeedBack& from);
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

  // repeated .ConfigScrollFeedback.FeedBackItem scrollfeedback = 1;
  inline int scrollfeedback_size() const;
  inline void clear_scrollfeedback();
  static const int kScrollfeedbackFieldNumber = 1;
  inline const ::ConfigScrollFeedback::FeedBackItem& scrollfeedback(int index) const;
  inline ::ConfigScrollFeedback::FeedBackItem* mutable_scrollfeedback(int index);
  inline ::ConfigScrollFeedback::FeedBackItem* add_scrollfeedback();
  inline const ::google::protobuf::RepeatedPtrField< ::ConfigScrollFeedback::FeedBackItem >&
      scrollfeedback() const;
  inline ::google::protobuf::RepeatedPtrField< ::ConfigScrollFeedback::FeedBackItem >*
      mutable_scrollfeedback();

  // @@protoc_insertion_point(class_scope:ConfigScrollFeedback.ScrollFeedBack)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::ConfigScrollFeedback::FeedBackItem > scrollfeedback_;
  friend void  protobuf_AddDesc_ConfigScrollFeedback_2eproto();
  friend void protobuf_AssignDesc_ConfigScrollFeedback_2eproto();
  friend void protobuf_ShutdownFile_ConfigScrollFeedback_2eproto();

  void InitAsDefaultInstance();
  static ScrollFeedBack* default_instance_;
};
// ===================================================================


// ===================================================================

// FeedBackItem

// required uint32 diamond = 1;
inline bool FeedBackItem::has_diamond() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void FeedBackItem::set_has_diamond() {
  _has_bits_[0] |= 0x00000001u;
}
inline void FeedBackItem::clear_has_diamond() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void FeedBackItem::clear_diamond() {
  diamond_ = 0u;
  clear_has_diamond();
}
inline ::google::protobuf::uint32 FeedBackItem::diamond() const {
  // @@protoc_insertion_point(field_get:ConfigScrollFeedback.FeedBackItem.diamond)
  return diamond_;
}
inline void FeedBackItem::set_diamond(::google::protobuf::uint32 value) {
  set_has_diamond();
  diamond_ = value;
  // @@protoc_insertion_point(field_set:ConfigScrollFeedback.FeedBackItem.diamond)
}

// required .RewardConfig.RewardItemCfg reward = 2;
inline bool FeedBackItem::has_reward() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void FeedBackItem::set_has_reward() {
  _has_bits_[0] |= 0x00000002u;
}
inline void FeedBackItem::clear_has_reward() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void FeedBackItem::clear_reward() {
  if (reward_ != NULL) reward_->::RewardConfig::RewardItemCfg::Clear();
  clear_has_reward();
}
inline const ::RewardConfig::RewardItemCfg& FeedBackItem::reward() const {
  // @@protoc_insertion_point(field_get:ConfigScrollFeedback.FeedBackItem.reward)
  return reward_ != NULL ? *reward_ : *default_instance_->reward_;
}
inline ::RewardConfig::RewardItemCfg* FeedBackItem::mutable_reward() {
  set_has_reward();
  if (reward_ == NULL) reward_ = new ::RewardConfig::RewardItemCfg;
  // @@protoc_insertion_point(field_mutable:ConfigScrollFeedback.FeedBackItem.reward)
  return reward_;
}
inline ::RewardConfig::RewardItemCfg* FeedBackItem::release_reward() {
  clear_has_reward();
  ::RewardConfig::RewardItemCfg* temp = reward_;
  reward_ = NULL;
  return temp;
}
inline void FeedBackItem::set_allocated_reward(::RewardConfig::RewardItemCfg* reward) {
  delete reward_;
  reward_ = reward;
  if (reward) {
    set_has_reward();
  } else {
    clear_has_reward();
  }
  // @@protoc_insertion_point(field_set_allocated:ConfigScrollFeedback.FeedBackItem.reward)
}

// -------------------------------------------------------------------

// ScrollFeedBack

// repeated .ConfigScrollFeedback.FeedBackItem scrollfeedback = 1;
inline int ScrollFeedBack::scrollfeedback_size() const {
  return scrollfeedback_.size();
}
inline void ScrollFeedBack::clear_scrollfeedback() {
  scrollfeedback_.Clear();
}
inline const ::ConfigScrollFeedback::FeedBackItem& ScrollFeedBack::scrollfeedback(int index) const {
  // @@protoc_insertion_point(field_get:ConfigScrollFeedback.ScrollFeedBack.scrollfeedback)
  return scrollfeedback_.Get(index);
}
inline ::ConfigScrollFeedback::FeedBackItem* ScrollFeedBack::mutable_scrollfeedback(int index) {
  // @@protoc_insertion_point(field_mutable:ConfigScrollFeedback.ScrollFeedBack.scrollfeedback)
  return scrollfeedback_.Mutable(index);
}
inline ::ConfigScrollFeedback::FeedBackItem* ScrollFeedBack::add_scrollfeedback() {
  // @@protoc_insertion_point(field_add:ConfigScrollFeedback.ScrollFeedBack.scrollfeedback)
  return scrollfeedback_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ConfigScrollFeedback::FeedBackItem >&
ScrollFeedBack::scrollfeedback() const {
  // @@protoc_insertion_point(field_list:ConfigScrollFeedback.ScrollFeedBack.scrollfeedback)
  return scrollfeedback_;
}
inline ::google::protobuf::RepeatedPtrField< ::ConfigScrollFeedback::FeedBackItem >*
ScrollFeedBack::mutable_scrollfeedback() {
  // @@protoc_insertion_point(field_mutable_list:ConfigScrollFeedback.ScrollFeedBack.scrollfeedback)
  return &scrollfeedback_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ConfigScrollFeedback

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ConfigScrollFeedback_2eproto__INCLUDED