// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Save.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Save.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace Save {

namespace {

const ::google::protobuf::Descriptor* SaveTest_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  SaveTest_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_Save_2eproto() {
  protobuf_AddDesc_Save_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "Save.proto");
  GOOGLE_CHECK(file != NULL);
  SaveTest_descriptor_ = file->message_type(0);
  static const int SaveTest_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SaveTest, test_),
  };
  SaveTest_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      SaveTest_descriptor_,
      SaveTest::default_instance_,
      SaveTest_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SaveTest, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SaveTest, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(SaveTest));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_Save_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    SaveTest_descriptor_, &SaveTest::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_Save_2eproto() {
  delete SaveTest::default_instance_;
  delete SaveTest_reflection_;
}

void protobuf_AddDesc_Save_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\nSave.proto\022\004Save\"\030\n\010SaveTest\022\014\n\004test\030\001"
    " \003(\r", 44);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Save.proto", &protobuf_RegisterTypes);
  SaveTest::default_instance_ = new SaveTest();
  SaveTest::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Save_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Save_2eproto {
  StaticDescriptorInitializer_Save_2eproto() {
    protobuf_AddDesc_Save_2eproto();
  }
} static_descriptor_initializer_Save_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int SaveTest::kTestFieldNumber;
#endif  // !_MSC_VER

SaveTest::SaveTest()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Save.SaveTest)
}

void SaveTest::InitAsDefaultInstance() {
}

SaveTest::SaveTest(const SaveTest& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Save.SaveTest)
}

void SaveTest::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

SaveTest::~SaveTest() {
  // @@protoc_insertion_point(destructor:Save.SaveTest)
  SharedDtor();
}

void SaveTest::SharedDtor() {
  if (this != default_instance_) {
  }
}

void SaveTest::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* SaveTest::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return SaveTest_descriptor_;
}

const SaveTest& SaveTest::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Save_2eproto();
  return *default_instance_;
}

SaveTest* SaveTest::default_instance_ = NULL;

SaveTest* SaveTest::New() const {
  return new SaveTest;
}

void SaveTest::Clear() {
  test_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool SaveTest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Save.SaveTest)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated uint32 test = 1;
      case 1: {
        if (tag == 8) {
         parse_test:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 8, input, this->mutable_test())));
        } else if (tag == 10) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_test())));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(8)) goto parse_test;
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:Save.SaveTest)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Save.SaveTest)
  return false;
#undef DO_
}

void SaveTest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Save.SaveTest)
  // repeated uint32 test = 1;
  for (int i = 0; i < this->test_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      1, this->test(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Save.SaveTest)
}

::google::protobuf::uint8* SaveTest::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Save.SaveTest)
  // repeated uint32 test = 1;
  for (int i = 0; i < this->test_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt32ToArray(1, this->test(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Save.SaveTest)
  return target;
}

int SaveTest::ByteSize() const {
  int total_size = 0;

  // repeated uint32 test = 1;
  {
    int data_size = 0;
    for (int i = 0; i < this->test_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt32Size(this->test(i));
    }
    total_size += 1 * this->test_size() + data_size;
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

void SaveTest::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const SaveTest* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const SaveTest*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void SaveTest::MergeFrom(const SaveTest& from) {
  GOOGLE_CHECK_NE(&from, this);
  test_.MergeFrom(from.test_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void SaveTest::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SaveTest::CopyFrom(const SaveTest& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SaveTest::IsInitialized() const {

  return true;
}

void SaveTest::Swap(SaveTest* other) {
  if (other != this) {
    test_.Swap(&other->test_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata SaveTest::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = SaveTest_descriptor_;
  metadata.reflection = SaveTest_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Save

// @@protoc_insertion_point(global_scope)
