// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Demo.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Demo.pb.h"

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

namespace Demo {

namespace {

const ::google::protobuf::Descriptor* Server_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Server_reflection_ = NULL;
const ::google::protobuf::Descriptor* Demo_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Demo_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_Demo_2eproto() {
  protobuf_AddDesc_Demo_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "Demo.proto");
  GOOGLE_CHECK(file != NULL);
  Server_descriptor_ = file->message_type(0);
  static const int Server_offsets_[6] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Server, begin_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Server, end_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Server, host_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Server, port_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Server, accesshost_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Server, accessport_),
  };
  Server_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Server_descriptor_,
      Server::default_instance_,
      Server_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Server, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Server, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Server));
  Demo_descriptor_ = file->message_type(1);
  static const int Demo_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Demo, battle_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Demo, open_),
  };
  Demo_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Demo_descriptor_,
      Demo::default_instance_,
      Demo_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Demo, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Demo, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Demo));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_Demo_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Server_descriptor_, &Server::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Demo_descriptor_, &Demo::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_Demo_2eproto() {
  delete Server::default_instance_;
  delete Server_reflection_;
  delete Demo::default_instance_;
  delete Demo_reflection_;
}

void protobuf_AddDesc_Demo_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\nDemo.proto\022\004Demo\"h\n\006Server\022\r\n\005begin\030\001 "
    "\002(\r\022\013\n\003end\030\002 \002(\r\022\014\n\004host\030\003 \002(\t\022\014\n\004port\030\004"
    " \002(\r\022\022\n\naccesshost\030\005 \002(\t\022\022\n\naccessport\030\006"
    " \002(\r\"2\n\004Demo\022\034\n\006battle\030\001 \003(\0132\014.Demo.Serv"
    "er\022\014\n\004open\030\002 \003(\r", 176);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Demo.proto", &protobuf_RegisterTypes);
  Server::default_instance_ = new Server();
  Demo::default_instance_ = new Demo();
  Server::default_instance_->InitAsDefaultInstance();
  Demo::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Demo_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Demo_2eproto {
  StaticDescriptorInitializer_Demo_2eproto() {
    protobuf_AddDesc_Demo_2eproto();
  }
} static_descriptor_initializer_Demo_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Server::kBeginFieldNumber;
const int Server::kEndFieldNumber;
const int Server::kHostFieldNumber;
const int Server::kPortFieldNumber;
const int Server::kAccesshostFieldNumber;
const int Server::kAccessportFieldNumber;
#endif  // !_MSC_VER

Server::Server()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Demo.Server)
}

void Server::InitAsDefaultInstance() {
}

Server::Server(const Server& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Demo.Server)
}

void Server::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  begin_ = 0u;
  end_ = 0u;
  host_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  port_ = 0u;
  accesshost_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  accessport_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Server::~Server() {
  // @@protoc_insertion_point(destructor:Demo.Server)
  SharedDtor();
}

void Server::SharedDtor() {
  if (host_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete host_;
  }
  if (accesshost_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete accesshost_;
  }
  if (this != default_instance_) {
  }
}

void Server::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Server::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Server_descriptor_;
}

const Server& Server::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Demo_2eproto();
  return *default_instance_;
}

Server* Server::default_instance_ = NULL;

Server* Server::New() const {
  return new Server;
}

void Server::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Server*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 63) {
    ZR_(begin_, end_);
    ZR_(port_, accessport_);
    if (has_host()) {
      if (host_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        host_->clear();
      }
    }
    if (has_accesshost()) {
      if (accesshost_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        accesshost_->clear();
      }
    }
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Server::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Demo.Server)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 begin = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &begin_)));
          set_has_begin();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_end;
        break;
      }

      // required uint32 end = 2;
      case 2: {
        if (tag == 16) {
         parse_end:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &end_)));
          set_has_end();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_host;
        break;
      }

      // required string host = 3;
      case 3: {
        if (tag == 26) {
         parse_host:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_host()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->host().data(), this->host().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "host");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_port;
        break;
      }

      // required uint32 port = 4;
      case 4: {
        if (tag == 32) {
         parse_port:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &port_)));
          set_has_port();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(42)) goto parse_accesshost;
        break;
      }

      // required string accesshost = 5;
      case 5: {
        if (tag == 42) {
         parse_accesshost:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_accesshost()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->accesshost().data(), this->accesshost().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "accesshost");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(48)) goto parse_accessport;
        break;
      }

      // required uint32 accessport = 6;
      case 6: {
        if (tag == 48) {
         parse_accessport:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &accessport_)));
          set_has_accessport();
        } else {
          goto handle_unusual;
        }
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
  // @@protoc_insertion_point(parse_success:Demo.Server)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Demo.Server)
  return false;
#undef DO_
}

void Server::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Demo.Server)
  // required uint32 begin = 1;
  if (has_begin()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->begin(), output);
  }

  // required uint32 end = 2;
  if (has_end()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->end(), output);
  }

  // required string host = 3;
  if (has_host()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->host().data(), this->host().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "host");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      3, this->host(), output);
  }

  // required uint32 port = 4;
  if (has_port()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->port(), output);
  }

  // required string accesshost = 5;
  if (has_accesshost()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->accesshost().data(), this->accesshost().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "accesshost");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      5, this->accesshost(), output);
  }

  // required uint32 accessport = 6;
  if (has_accessport()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(6, this->accessport(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Demo.Server)
}

::google::protobuf::uint8* Server::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Demo.Server)
  // required uint32 begin = 1;
  if (has_begin()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->begin(), target);
  }

  // required uint32 end = 2;
  if (has_end()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->end(), target);
  }

  // required string host = 3;
  if (has_host()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->host().data(), this->host().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "host");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->host(), target);
  }

  // required uint32 port = 4;
  if (has_port()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->port(), target);
  }

  // required string accesshost = 5;
  if (has_accesshost()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->accesshost().data(), this->accesshost().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "accesshost");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        5, this->accesshost(), target);
  }

  // required uint32 accessport = 6;
  if (has_accessport()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(6, this->accessport(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Demo.Server)
  return target;
}

int Server::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 begin = 1;
    if (has_begin()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->begin());
    }

    // required uint32 end = 2;
    if (has_end()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->end());
    }

    // required string host = 3;
    if (has_host()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->host());
    }

    // required uint32 port = 4;
    if (has_port()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->port());
    }

    // required string accesshost = 5;
    if (has_accesshost()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->accesshost());
    }

    // required uint32 accessport = 6;
    if (has_accessport()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->accessport());
    }

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

void Server::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Server* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Server*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Server::MergeFrom(const Server& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_begin()) {
      set_begin(from.begin());
    }
    if (from.has_end()) {
      set_end(from.end());
    }
    if (from.has_host()) {
      set_host(from.host());
    }
    if (from.has_port()) {
      set_port(from.port());
    }
    if (from.has_accesshost()) {
      set_accesshost(from.accesshost());
    }
    if (from.has_accessport()) {
      set_accessport(from.accessport());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Server::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Server::CopyFrom(const Server& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Server::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000003f) != 0x0000003f) return false;

  return true;
}

void Server::Swap(Server* other) {
  if (other != this) {
    std::swap(begin_, other->begin_);
    std::swap(end_, other->end_);
    std::swap(host_, other->host_);
    std::swap(port_, other->port_);
    std::swap(accesshost_, other->accesshost_);
    std::swap(accessport_, other->accessport_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Server::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Server_descriptor_;
  metadata.reflection = Server_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Demo::kBattleFieldNumber;
const int Demo::kOpenFieldNumber;
#endif  // !_MSC_VER

Demo::Demo()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Demo.Demo)
}

void Demo::InitAsDefaultInstance() {
}

Demo::Demo(const Demo& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Demo.Demo)
}

void Demo::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Demo::~Demo() {
  // @@protoc_insertion_point(destructor:Demo.Demo)
  SharedDtor();
}

void Demo::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Demo::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Demo::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Demo_descriptor_;
}

const Demo& Demo::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Demo_2eproto();
  return *default_instance_;
}

Demo* Demo::default_instance_ = NULL;

Demo* Demo::New() const {
  return new Demo;
}

void Demo::Clear() {
  battle_.Clear();
  open_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Demo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Demo.Demo)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .Demo.Server battle = 1;
      case 1: {
        if (tag == 10) {
         parse_battle:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_battle()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_battle;
        if (input->ExpectTag(16)) goto parse_open;
        break;
      }

      // repeated uint32 open = 2;
      case 2: {
        if (tag == 16) {
         parse_open:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 16, input, this->mutable_open())));
        } else if (tag == 18) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_open())));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_open;
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
  // @@protoc_insertion_point(parse_success:Demo.Demo)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Demo.Demo)
  return false;
#undef DO_
}

void Demo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Demo.Demo)
  // repeated .Demo.Server battle = 1;
  for (int i = 0; i < this->battle_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->battle(i), output);
  }

  // repeated uint32 open = 2;
  for (int i = 0; i < this->open_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      2, this->open(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Demo.Demo)
}

::google::protobuf::uint8* Demo::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Demo.Demo)
  // repeated .Demo.Server battle = 1;
  for (int i = 0; i < this->battle_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->battle(i), target);
  }

  // repeated uint32 open = 2;
  for (int i = 0; i < this->open_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt32ToArray(2, this->open(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Demo.Demo)
  return target;
}

int Demo::ByteSize() const {
  int total_size = 0;

  // repeated .Demo.Server battle = 1;
  total_size += 1 * this->battle_size();
  for (int i = 0; i < this->battle_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->battle(i));
  }

  // repeated uint32 open = 2;
  {
    int data_size = 0;
    for (int i = 0; i < this->open_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt32Size(this->open(i));
    }
    total_size += 1 * this->open_size() + data_size;
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

void Demo::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Demo* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Demo*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Demo::MergeFrom(const Demo& from) {
  GOOGLE_CHECK_NE(&from, this);
  battle_.MergeFrom(from.battle_);
  open_.MergeFrom(from.open_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Demo::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Demo::CopyFrom(const Demo& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Demo::IsInitialized() const {

  if (!::google::protobuf::internal::AllAreInitialized(this->battle())) return false;
  return true;
}

void Demo::Swap(Demo* other) {
  if (other != this) {
    battle_.Swap(&other->battle_);
    open_.Swap(&other->open_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Demo::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Demo_descriptor_;
  metadata.reflection = Demo_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Demo

// @@protoc_insertion_point(global_scope)
