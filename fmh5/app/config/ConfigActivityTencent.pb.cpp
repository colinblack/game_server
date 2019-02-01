// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ConfigActivityTencent.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace ConfigActivityTencent {

namespace {

const ::google::protobuf::Descriptor* ActivityInfo_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ActivityInfo_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_ConfigActivityTencent_2eproto() {
  protobuf_AddDesc_ConfigActivityTencent_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "ConfigActivityTencent.proto");
  GOOGLE_CHECK(file != NULL);
  ActivityInfo_descriptor_ = file->message_type(0);
  static const int ActivityInfo_offsets_[6] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ActivityInfo, normal_blue_daily_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ActivityInfo, super_blue_daily_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ActivityInfo, year_blue_daily_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ActivityInfo, blue_grow_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ActivityInfo, qqgame_privilege_daily_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ActivityInfo, qqgame_privilege_grow_),
  };
  ActivityInfo_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ActivityInfo_descriptor_,
      ActivityInfo::default_instance_,
      ActivityInfo_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ActivityInfo, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ActivityInfo, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ActivityInfo));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_ConfigActivityTencent_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ActivityInfo_descriptor_, &ActivityInfo::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_ConfigActivityTencent_2eproto() {
  delete ActivityInfo::default_instance_;
  delete ActivityInfo_reflection_;
}

void protobuf_AddDesc_ConfigActivityTencent_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::CommonGiftConfig::protobuf_AddDesc_CommonGiftConfig_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\033ConfigActivityTencent.proto\022\025ConfigAct"
    "ivityTencent\032\026CommonGiftConfig.proto\"\246\003\n"
    "\014ActivityInfo\022C\n\021normal_blue_daily\030\001 \003(\013"
    "2(.CommonGiftConfig.CommonModifyItemSimp"
    "le\022B\n\020super_blue_daily\030\002 \002(\0132(.CommonGif"
    "tConfig.CommonModifyItemNormal\022A\n\017year_b"
    "lue_daily\030\003 \002(\0132(.CommonGiftConfig.Commo"
    "nModifyItemNormal\0229\n\tblue_grow\030\004 \003(\0132&.C"
    "ommonGiftConfig.CommonModifyItemGrow\022H\n\026"
    "qqgame_privilege_daily\030\005 \002(\0132(.CommonGif"
    "tConfig.CommonModifyItemNormal\022E\n\025qqgame"
    "_privilege_grow\030\006 \003(\0132&.CommonGiftConfig"
    ".CommonModifyItemGrow", 501);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ConfigActivityTencent.proto", &protobuf_RegisterTypes);
  ActivityInfo::default_instance_ = new ActivityInfo();
  ActivityInfo::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ConfigActivityTencent_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ConfigActivityTencent_2eproto {
  StaticDescriptorInitializer_ConfigActivityTencent_2eproto() {
    protobuf_AddDesc_ConfigActivityTencent_2eproto();
  }
} static_descriptor_initializer_ConfigActivityTencent_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int ActivityInfo::kNormalBlueDailyFieldNumber;
const int ActivityInfo::kSuperBlueDailyFieldNumber;
const int ActivityInfo::kYearBlueDailyFieldNumber;
const int ActivityInfo::kBlueGrowFieldNumber;
const int ActivityInfo::kQqgamePrivilegeDailyFieldNumber;
const int ActivityInfo::kQqgamePrivilegeGrowFieldNumber;
#endif  // !_MSC_VER

ActivityInfo::ActivityInfo()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void ActivityInfo::InitAsDefaultInstance() {
  super_blue_daily_ = const_cast< ::CommonGiftConfig::CommonModifyItemNormal*>(&::CommonGiftConfig::CommonModifyItemNormal::default_instance());
  year_blue_daily_ = const_cast< ::CommonGiftConfig::CommonModifyItemNormal*>(&::CommonGiftConfig::CommonModifyItemNormal::default_instance());
  qqgame_privilege_daily_ = const_cast< ::CommonGiftConfig::CommonModifyItemNormal*>(&::CommonGiftConfig::CommonModifyItemNormal::default_instance());
}

ActivityInfo::ActivityInfo(const ActivityInfo& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void ActivityInfo::SharedCtor() {
  _cached_size_ = 0;
  super_blue_daily_ = NULL;
  year_blue_daily_ = NULL;
  qqgame_privilege_daily_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ActivityInfo::~ActivityInfo() {
  SharedDtor();
}

void ActivityInfo::SharedDtor() {
  if (this != default_instance_) {
    delete super_blue_daily_;
    delete year_blue_daily_;
    delete qqgame_privilege_daily_;
  }
}

void ActivityInfo::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ActivityInfo::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ActivityInfo_descriptor_;
}

const ActivityInfo& ActivityInfo::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ConfigActivityTencent_2eproto();  return *default_instance_;
}

ActivityInfo* ActivityInfo::default_instance_ = NULL;

ActivityInfo* ActivityInfo::New() const {
  return new ActivityInfo;
}

void ActivityInfo::Clear() {
  if (_has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    if (has_super_blue_daily()) {
      if (super_blue_daily_ != NULL) super_blue_daily_->::CommonGiftConfig::CommonModifyItemNormal::Clear();
    }
    if (has_year_blue_daily()) {
      if (year_blue_daily_ != NULL) year_blue_daily_->::CommonGiftConfig::CommonModifyItemNormal::Clear();
    }
    if (has_qqgame_privilege_daily()) {
      if (qqgame_privilege_daily_ != NULL) qqgame_privilege_daily_->::CommonGiftConfig::CommonModifyItemNormal::Clear();
    }
  }
  normal_blue_daily_.Clear();
  blue_grow_.Clear();
  qqgame_privilege_grow_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ActivityInfo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .CommonGiftConfig.CommonModifyItemSimple normal_blue_daily = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_normal_blue_daily:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_normal_blue_daily()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_normal_blue_daily;
        if (input->ExpectTag(18)) goto parse_super_blue_daily;
        break;
      }
      
      // required .CommonGiftConfig.CommonModifyItemNormal super_blue_daily = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_super_blue_daily:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_super_blue_daily()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_year_blue_daily;
        break;
      }
      
      // required .CommonGiftConfig.CommonModifyItemNormal year_blue_daily = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_year_blue_daily:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_year_blue_daily()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_blue_grow;
        break;
      }
      
      // repeated .CommonGiftConfig.CommonModifyItemGrow blue_grow = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_blue_grow:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_blue_grow()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_blue_grow;
        if (input->ExpectTag(42)) goto parse_qqgame_privilege_daily;
        break;
      }
      
      // required .CommonGiftConfig.CommonModifyItemNormal qqgame_privilege_daily = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_qqgame_privilege_daily:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_qqgame_privilege_daily()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(50)) goto parse_qqgame_privilege_grow;
        break;
      }
      
      // repeated .CommonGiftConfig.CommonModifyItemGrow qqgame_privilege_grow = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_qqgame_privilege_grow:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_qqgame_privilege_grow()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(50)) goto parse_qqgame_privilege_grow;
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void ActivityInfo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .CommonGiftConfig.CommonModifyItemSimple normal_blue_daily = 1;
  for (int i = 0; i < this->normal_blue_daily_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->normal_blue_daily(i), output);
  }
  
  // required .CommonGiftConfig.CommonModifyItemNormal super_blue_daily = 2;
  if (has_super_blue_daily()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->super_blue_daily(), output);
  }
  
  // required .CommonGiftConfig.CommonModifyItemNormal year_blue_daily = 3;
  if (has_year_blue_daily()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->year_blue_daily(), output);
  }
  
  // repeated .CommonGiftConfig.CommonModifyItemGrow blue_grow = 4;
  for (int i = 0; i < this->blue_grow_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4, this->blue_grow(i), output);
  }
  
  // required .CommonGiftConfig.CommonModifyItemNormal qqgame_privilege_daily = 5;
  if (has_qqgame_privilege_daily()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      5, this->qqgame_privilege_daily(), output);
  }
  
  // repeated .CommonGiftConfig.CommonModifyItemGrow qqgame_privilege_grow = 6;
  for (int i = 0; i < this->qqgame_privilege_grow_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      6, this->qqgame_privilege_grow(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* ActivityInfo::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .CommonGiftConfig.CommonModifyItemSimple normal_blue_daily = 1;
  for (int i = 0; i < this->normal_blue_daily_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->normal_blue_daily(i), target);
  }
  
  // required .CommonGiftConfig.CommonModifyItemNormal super_blue_daily = 2;
  if (has_super_blue_daily()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->super_blue_daily(), target);
  }
  
  // required .CommonGiftConfig.CommonModifyItemNormal year_blue_daily = 3;
  if (has_year_blue_daily()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->year_blue_daily(), target);
  }
  
  // repeated .CommonGiftConfig.CommonModifyItemGrow blue_grow = 4;
  for (int i = 0; i < this->blue_grow_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        4, this->blue_grow(i), target);
  }
  
  // required .CommonGiftConfig.CommonModifyItemNormal qqgame_privilege_daily = 5;
  if (has_qqgame_privilege_daily()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        5, this->qqgame_privilege_daily(), target);
  }
  
  // repeated .CommonGiftConfig.CommonModifyItemGrow qqgame_privilege_grow = 6;
  for (int i = 0; i < this->qqgame_privilege_grow_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        6, this->qqgame_privilege_grow(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int ActivityInfo::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    // required .CommonGiftConfig.CommonModifyItemNormal super_blue_daily = 2;
    if (has_super_blue_daily()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->super_blue_daily());
    }
    
    // required .CommonGiftConfig.CommonModifyItemNormal year_blue_daily = 3;
    if (has_year_blue_daily()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->year_blue_daily());
    }
    
    // required .CommonGiftConfig.CommonModifyItemNormal qqgame_privilege_daily = 5;
    if (has_qqgame_privilege_daily()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->qqgame_privilege_daily());
    }
    
  }
  // repeated .CommonGiftConfig.CommonModifyItemSimple normal_blue_daily = 1;
  total_size += 1 * this->normal_blue_daily_size();
  for (int i = 0; i < this->normal_blue_daily_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->normal_blue_daily(i));
  }
  
  // repeated .CommonGiftConfig.CommonModifyItemGrow blue_grow = 4;
  total_size += 1 * this->blue_grow_size();
  for (int i = 0; i < this->blue_grow_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->blue_grow(i));
  }
  
  // repeated .CommonGiftConfig.CommonModifyItemGrow qqgame_privilege_grow = 6;
  total_size += 1 * this->qqgame_privilege_grow_size();
  for (int i = 0; i < this->qqgame_privilege_grow_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->qqgame_privilege_grow(i));
  }
  
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ActivityInfo::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ActivityInfo* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ActivityInfo*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ActivityInfo::MergeFrom(const ActivityInfo& from) {
  GOOGLE_CHECK_NE(&from, this);
  normal_blue_daily_.MergeFrom(from.normal_blue_daily_);
  blue_grow_.MergeFrom(from.blue_grow_);
  qqgame_privilege_grow_.MergeFrom(from.qqgame_privilege_grow_);
  if (from._has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    if (from.has_super_blue_daily()) {
      mutable_super_blue_daily()->::CommonGiftConfig::CommonModifyItemNormal::MergeFrom(from.super_blue_daily());
    }
    if (from.has_year_blue_daily()) {
      mutable_year_blue_daily()->::CommonGiftConfig::CommonModifyItemNormal::MergeFrom(from.year_blue_daily());
    }
    if (from.has_qqgame_privilege_daily()) {
      mutable_qqgame_privilege_daily()->::CommonGiftConfig::CommonModifyItemNormal::MergeFrom(from.qqgame_privilege_daily());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ActivityInfo::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ActivityInfo::CopyFrom(const ActivityInfo& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ActivityInfo::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000016) != 0x00000016) return false;
  
  for (int i = 0; i < normal_blue_daily_size(); i++) {
    if (!this->normal_blue_daily(i).IsInitialized()) return false;
  }
  if (has_super_blue_daily()) {
    if (!this->super_blue_daily().IsInitialized()) return false;
  }
  if (has_year_blue_daily()) {
    if (!this->year_blue_daily().IsInitialized()) return false;
  }
  for (int i = 0; i < blue_grow_size(); i++) {
    if (!this->blue_grow(i).IsInitialized()) return false;
  }
  if (has_qqgame_privilege_daily()) {
    if (!this->qqgame_privilege_daily().IsInitialized()) return false;
  }
  for (int i = 0; i < qqgame_privilege_grow_size(); i++) {
    if (!this->qqgame_privilege_grow(i).IsInitialized()) return false;
  }
  return true;
}

void ActivityInfo::Swap(ActivityInfo* other) {
  if (other != this) {
    normal_blue_daily_.Swap(&other->normal_blue_daily_);
    std::swap(super_blue_daily_, other->super_blue_daily_);
    std::swap(year_blue_daily_, other->year_blue_daily_);
    blue_grow_.Swap(&other->blue_grow_);
    std::swap(qqgame_privilege_daily_, other->qqgame_privilege_daily_);
    qqgame_privilege_grow_.Swap(&other->qqgame_privilege_grow_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ActivityInfo::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ActivityInfo_descriptor_;
  metadata.reflection = ActivityInfo_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ConfigActivityTencent

// @@protoc_insertion_point(global_scope)