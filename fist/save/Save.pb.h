// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Save.proto

#ifndef PROTOBUF_Save_2eproto__INCLUDED
#define PROTOBUF_Save_2eproto__INCLUDED

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

namespace Save {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_Save_2eproto();
void protobuf_AssignDesc_Save_2eproto();
void protobuf_ShutdownFile_Save_2eproto();

class SaveTest;

// ===================================================================

class SaveTest : public ::google::protobuf::Message {
 public:
  SaveTest();
  virtual ~SaveTest();
  
  SaveTest(const SaveTest& from);
  
  inline SaveTest& operator=(const SaveTest& from) {
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
  static const SaveTest& default_instance();
  
  void Swap(SaveTest* other);
  
  // implements Message ----------------------------------------------
  
  SaveTest* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SaveTest& from);
  void MergeFrom(const SaveTest& from);
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
  
  // repeated uint32 test = 1;
  inline int test_size() const;
  inline void clear_test();
  static const int kTestFieldNumber = 1;
  inline ::google::protobuf::uint32 test(int index) const;
  inline void set_test(int index, ::google::protobuf::uint32 value);
  inline void add_test(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      test() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_test();
  
  // @@protoc_insertion_point(class_scope:Save.SaveTest)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > test_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_Save_2eproto();
  friend void protobuf_AssignDesc_Save_2eproto();
  friend void protobuf_ShutdownFile_Save_2eproto();
  
  void InitAsDefaultInstance();
  static SaveTest* default_instance_;
};
// ===================================================================


// ===================================================================

// SaveTest

// repeated uint32 test = 1;
inline int SaveTest::test_size() const {
  return test_.size();
}
inline void SaveTest::clear_test() {
  test_.Clear();
}
inline ::google::protobuf::uint32 SaveTest::test(int index) const {
  return test_.Get(index);
}
inline void SaveTest::set_test(int index, ::google::protobuf::uint32 value) {
  test_.Set(index, value);
}
inline void SaveTest::add_test(::google::protobuf::uint32 value) {
  test_.Add(value);
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
SaveTest::test() const {
  return test_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
SaveTest::mutable_test() {
  return &test_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Save

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Save_2eproto__INCLUDED
