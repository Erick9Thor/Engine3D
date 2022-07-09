// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: graph.proto

#ifndef PROTOBUF_graph_2eproto__INCLUDED
#define PROTOBUF_graph_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3005001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/map.h>  // IWYU pragma: export
#include <google/protobuf/map_entry.h>
#include <google/protobuf/map_field_inl.h>
#include <google/protobuf/unknown_field_set.h>
#include "attr_value.pb.h"
#include "function.pb.h"
#include "versions.pb.h"
// @@protoc_insertion_point(includes)

namespace protobuf_graph_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[3];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
void InitDefaultsGraphDefImpl();
void InitDefaultsGraphDef();
void InitDefaultsNodeDef_AttrEntry_DoNotUseImpl();
void InitDefaultsNodeDef_AttrEntry_DoNotUse();
void InitDefaultsNodeDefImpl();
void InitDefaultsNodeDef();
inline void InitDefaults() {
  InitDefaultsGraphDef();
  InitDefaultsNodeDef_AttrEntry_DoNotUse();
  InitDefaultsNodeDef();
}
}  // namespace protobuf_graph_2eproto
namespace opencv_tensorflow {
class GraphDef;
class GraphDefDefaultTypeInternal;
extern GraphDefDefaultTypeInternal _GraphDef_default_instance_;
class NodeDef;
class NodeDefDefaultTypeInternal;
extern NodeDefDefaultTypeInternal _NodeDef_default_instance_;
class NodeDef_AttrEntry_DoNotUse;
class NodeDef_AttrEntry_DoNotUseDefaultTypeInternal;
extern NodeDef_AttrEntry_DoNotUseDefaultTypeInternal _NodeDef_AttrEntry_DoNotUse_default_instance_;
}  // namespace opencv_tensorflow
namespace opencv_tensorflow {

// ===================================================================

class GraphDef : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:opencv_tensorflow.GraphDef) */ {
 public:
  GraphDef();
  virtual ~GraphDef();

  GraphDef(const GraphDef& from);

  inline GraphDef& operator=(const GraphDef& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  GraphDef(GraphDef&& from) noexcept
    : GraphDef() {
    *this = ::std::move(from);
  }

  inline GraphDef& operator=(GraphDef&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline ::google::protobuf::Arena* GetArena() const PROTOBUF_FINAL {
    return GetArenaNoVirtual();
  }
  inline void* GetMaybeArenaPointer() const PROTOBUF_FINAL {
    return MaybeArenaPtr();
  }
  static const ::google::protobuf::Descriptor* descriptor();
  static const GraphDef& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const GraphDef* internal_default_instance() {
    return reinterpret_cast<const GraphDef*>(
               &_GraphDef_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void UnsafeArenaSwap(GraphDef* other);
  void Swap(GraphDef* other);
  friend void swap(GraphDef& a, GraphDef& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline GraphDef* New() const PROTOBUF_FINAL { return New(NULL); }

  GraphDef* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const GraphDef& from);
  void MergeFrom(const GraphDef& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(GraphDef* other);
  protected:
  explicit GraphDef(::google::protobuf::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::google::protobuf::Arena* arena);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .opencv_tensorflow.NodeDef node = 1;
  int node_size() const;
  void clear_node();
  static const int kNodeFieldNumber = 1;
  const ::opencv_tensorflow::NodeDef& node(int index) const;
  ::opencv_tensorflow::NodeDef* mutable_node(int index);
  ::opencv_tensorflow::NodeDef* add_node();
  ::google::protobuf::RepeatedPtrField< ::opencv_tensorflow::NodeDef >*
      mutable_node();
  const ::google::protobuf::RepeatedPtrField< ::opencv_tensorflow::NodeDef >&
      node() const;

  // .opencv_tensorflow.FunctionDefLibrary library = 2;
  bool has_library() const;
  void clear_library();
  static const int kLibraryFieldNumber = 2;
  private:
  void _slow_mutable_library();
  public:
  const ::opencv_tensorflow::FunctionDefLibrary& library() const;
  ::opencv_tensorflow::FunctionDefLibrary* release_library();
  ::opencv_tensorflow::FunctionDefLibrary* mutable_library();
  void set_allocated_library(::opencv_tensorflow::FunctionDefLibrary* library);
  void unsafe_arena_set_allocated_library(
      ::opencv_tensorflow::FunctionDefLibrary* library);
  ::opencv_tensorflow::FunctionDefLibrary* unsafe_arena_release_library();

  // .opencv_tensorflow.VersionDef versions = 4;
  bool has_versions() const;
  void clear_versions();
  static const int kVersionsFieldNumber = 4;
  private:
  void _slow_mutable_versions();
  public:
  const ::opencv_tensorflow::VersionDef& versions() const;
  ::opencv_tensorflow::VersionDef* release_versions();
  ::opencv_tensorflow::VersionDef* mutable_versions();
  void set_allocated_versions(::opencv_tensorflow::VersionDef* versions);
  void unsafe_arena_set_allocated_versions(
      ::opencv_tensorflow::VersionDef* versions);
  ::opencv_tensorflow::VersionDef* unsafe_arena_release_versions();

  // int32 version = 3 [deprecated = true];
  GOOGLE_PROTOBUF_DEPRECATED_ATTR void clear_version();
  GOOGLE_PROTOBUF_DEPRECATED_ATTR static const int kVersionFieldNumber = 3;
  GOOGLE_PROTOBUF_DEPRECATED_ATTR ::google::protobuf::int32 version() const;
  GOOGLE_PROTOBUF_DEPRECATED_ATTR void set_version(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:opencv_tensorflow.GraphDef)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  template <typename T> friend class ::google::protobuf::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::google::protobuf::RepeatedPtrField< ::opencv_tensorflow::NodeDef > node_;
  ::opencv_tensorflow::FunctionDefLibrary* library_;
  ::opencv_tensorflow::VersionDef* versions_;
  ::google::protobuf::int32 version_;
  mutable int _cached_size_;
  friend struct ::protobuf_graph_2eproto::TableStruct;
  friend void ::protobuf_graph_2eproto::InitDefaultsGraphDefImpl();
};
// -------------------------------------------------------------------

class NodeDef_AttrEntry_DoNotUse : public ::google::protobuf::internal::MapEntry<NodeDef_AttrEntry_DoNotUse,
    ::std::string, ::opencv_tensorflow::AttrValue,
    ::google::protobuf::internal::WireFormatLite::TYPE_STRING,
    ::google::protobuf::internal::WireFormatLite::TYPE_MESSAGE,
    0 > {
public:
  typedef ::google::protobuf::internal::MapEntry<NodeDef_AttrEntry_DoNotUse,
    ::std::string, ::opencv_tensorflow::AttrValue,
    ::google::protobuf::internal::WireFormatLite::TYPE_STRING,
    ::google::protobuf::internal::WireFormatLite::TYPE_MESSAGE,
    0 > SuperType;
  NodeDef_AttrEntry_DoNotUse();
  NodeDef_AttrEntry_DoNotUse(::google::protobuf::Arena* arena);
  void MergeFrom(const NodeDef_AttrEntry_DoNotUse& other);
  static const NodeDef_AttrEntry_DoNotUse* internal_default_instance() { return reinterpret_cast<const NodeDef_AttrEntry_DoNotUse*>(&_NodeDef_AttrEntry_DoNotUse_default_instance_); }
  void MergeFrom(const ::google::protobuf::Message& other) PROTOBUF_FINAL;
  ::google::protobuf::Metadata GetMetadata() const;
};

// -------------------------------------------------------------------

class NodeDef : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:opencv_tensorflow.NodeDef) */ {
 public:
  NodeDef();
  virtual ~NodeDef();

  NodeDef(const NodeDef& from);

  inline NodeDef& operator=(const NodeDef& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  NodeDef(NodeDef&& from) noexcept
    : NodeDef() {
    *this = ::std::move(from);
  }

  inline NodeDef& operator=(NodeDef&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline ::google::protobuf::Arena* GetArena() const PROTOBUF_FINAL {
    return GetArenaNoVirtual();
  }
  inline void* GetMaybeArenaPointer() const PROTOBUF_FINAL {
    return MaybeArenaPtr();
  }
  static const ::google::protobuf::Descriptor* descriptor();
  static const NodeDef& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const NodeDef* internal_default_instance() {
    return reinterpret_cast<const NodeDef*>(
               &_NodeDef_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    2;

  void UnsafeArenaSwap(NodeDef* other);
  void Swap(NodeDef* other);
  friend void swap(NodeDef& a, NodeDef& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline NodeDef* New() const PROTOBUF_FINAL { return New(NULL); }

  NodeDef* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const NodeDef& from);
  void MergeFrom(const NodeDef& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(NodeDef* other);
  protected:
  explicit NodeDef(::google::protobuf::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::google::protobuf::Arena* arena);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------


  // accessors -------------------------------------------------------

  // repeated string input = 3;
  int input_size() const;
  void clear_input();
  static const int kInputFieldNumber = 3;
  const ::std::string& input(int index) const;
  ::std::string* mutable_input(int index);
  void set_input(int index, const ::std::string& value);
  #if LANG_CXX11
  void set_input(int index, ::std::string&& value);
  #endif
  void set_input(int index, const char* value);
  void set_input(int index, const char* value, size_t size);
  ::std::string* add_input();
  void add_input(const ::std::string& value);
  #if LANG_CXX11
  void add_input(::std::string&& value);
  #endif
  void add_input(const char* value);
  void add_input(const char* value, size_t size);
  const ::google::protobuf::RepeatedPtrField< ::std::string>& input() const;
  ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_input();

  // map<string, .opencv_tensorflow.AttrValue> attr = 5;
  int attr_size() const;
  void clear_attr();
  static const int kAttrFieldNumber = 5;
  const ::google::protobuf::Map< ::std::string, ::opencv_tensorflow::AttrValue >&
      attr() const;
  ::google::protobuf::Map< ::std::string, ::opencv_tensorflow::AttrValue >*
      mutable_attr();

  // string name = 1;
  void clear_name();
  static const int kNameFieldNumber = 1;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  #if LANG_CXX11
  void set_name(::std::string&& value);
  #endif
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);
  PROTOBUF_RUNTIME_DEPRECATED("The unsafe_arena_ accessors for"
  "    string fields are deprecated and will be removed in a"
  "    future release.")
  ::std::string* unsafe_arena_release_name();
  PROTOBUF_RUNTIME_DEPRECATED("The unsafe_arena_ accessors for"
  "    string fields are deprecated and will be removed in a"
  "    future release.")
  void unsafe_arena_set_allocated_name(
      ::std::string* name);

  // string op = 2;
  void clear_op();
  static const int kOpFieldNumber = 2;
  const ::std::string& op() const;
  void set_op(const ::std::string& value);
  #if LANG_CXX11
  void set_op(::std::string&& value);
  #endif
  void set_op(const char* value);
  void set_op(const char* value, size_t size);
  ::std::string* mutable_op();
  ::std::string* release_op();
  void set_allocated_op(::std::string* op);
  PROTOBUF_RUNTIME_DEPRECATED("The unsafe_arena_ accessors for"
  "    string fields are deprecated and will be removed in a"
  "    future release.")
  ::std::string* unsafe_arena_release_op();
  PROTOBUF_RUNTIME_DEPRECATED("The unsafe_arena_ accessors for"
  "    string fields are deprecated and will be removed in a"
  "    future release.")
  void unsafe_arena_set_allocated_op(
      ::std::string* op);

  // string device = 4;
  void clear_device();
  static const int kDeviceFieldNumber = 4;
  const ::std::string& device() const;
  void set_device(const ::std::string& value);
  #if LANG_CXX11
  void set_device(::std::string&& value);
  #endif
  void set_device(const char* value);
  void set_device(const char* value, size_t size);
  ::std::string* mutable_device();
  ::std::string* release_device();
  void set_allocated_device(::std::string* device);
  PROTOBUF_RUNTIME_DEPRECATED("The unsafe_arena_ accessors for"
  "    string fields are deprecated and will be removed in a"
  "    future release.")
  ::std::string* unsafe_arena_release_device();
  PROTOBUF_RUNTIME_DEPRECATED("The unsafe_arena_ accessors for"
  "    string fields are deprecated and will be removed in a"
  "    future release.")
  void unsafe_arena_set_allocated_device(
      ::std::string* device);

  // @@protoc_insertion_point(class_scope:opencv_tensorflow.NodeDef)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  template <typename T> friend class ::google::protobuf::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::google::protobuf::RepeatedPtrField< ::std::string> input_;
  ::google::protobuf::internal::MapField<
      NodeDef_AttrEntry_DoNotUse,
      ::std::string, ::opencv_tensorflow::AttrValue,
      ::google::protobuf::internal::WireFormatLite::TYPE_STRING,
      ::google::protobuf::internal::WireFormatLite::TYPE_MESSAGE,
      0 > attr_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::internal::ArenaStringPtr op_;
  ::google::protobuf::internal::ArenaStringPtr device_;
  mutable int _cached_size_;
  friend struct ::protobuf_graph_2eproto::TableStruct;
  friend void ::protobuf_graph_2eproto::InitDefaultsNodeDefImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// GraphDef

// repeated .opencv_tensorflow.NodeDef node = 1;
inline int GraphDef::node_size() const {
  return node_.size();
}
inline void GraphDef::clear_node() {
  node_.Clear();
}
inline const ::opencv_tensorflow::NodeDef& GraphDef::node(int index) const {
  // @@protoc_insertion_point(field_get:opencv_tensorflow.GraphDef.node)
  return node_.Get(index);
}
inline ::opencv_tensorflow::NodeDef* GraphDef::mutable_node(int index) {
  // @@protoc_insertion_point(field_mutable:opencv_tensorflow.GraphDef.node)
  return node_.Mutable(index);
}
inline ::opencv_tensorflow::NodeDef* GraphDef::add_node() {
  // @@protoc_insertion_point(field_add:opencv_tensorflow.GraphDef.node)
  return node_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::opencv_tensorflow::NodeDef >*
GraphDef::mutable_node() {
  // @@protoc_insertion_point(field_mutable_list:opencv_tensorflow.GraphDef.node)
  return &node_;
}
inline const ::google::protobuf::RepeatedPtrField< ::opencv_tensorflow::NodeDef >&
GraphDef::node() const {
  // @@protoc_insertion_point(field_list:opencv_tensorflow.GraphDef.node)
  return node_;
}

// .opencv_tensorflow.VersionDef versions = 4;
inline bool GraphDef::has_versions() const {
  return this != internal_default_instance() && versions_ != NULL;
}
inline const ::opencv_tensorflow::VersionDef& GraphDef::versions() const {
  const ::opencv_tensorflow::VersionDef* p = versions_;
  // @@protoc_insertion_point(field_get:opencv_tensorflow.GraphDef.versions)
  return p != NULL ? *p : *reinterpret_cast<const ::opencv_tensorflow::VersionDef*>(
      &::opencv_tensorflow::_VersionDef_default_instance_);
}
inline ::opencv_tensorflow::VersionDef* GraphDef::release_versions() {
  // @@protoc_insertion_point(field_release:opencv_tensorflow.GraphDef.versions)

  ::opencv_tensorflow::VersionDef* temp = versions_;
  if (GetArenaNoVirtual() != NULL) {
    temp = ::google::protobuf::internal::DuplicateIfNonNull(temp, NULL);
  }
  versions_ = NULL;
  return temp;
}
inline ::opencv_tensorflow::VersionDef* GraphDef::unsafe_arena_release_versions() {
  // @@protoc_insertion_point(field_unsafe_arena_release:opencv_tensorflow.GraphDef.versions)

  ::opencv_tensorflow::VersionDef* temp = versions_;
  versions_ = NULL;
  return temp;
}
inline ::opencv_tensorflow::VersionDef* GraphDef::mutable_versions() {

  if (versions_ == NULL) {
    _slow_mutable_versions();
  }
  // @@protoc_insertion_point(field_mutable:opencv_tensorflow.GraphDef.versions)
  return versions_;
}
inline void GraphDef::set_allocated_versions(::opencv_tensorflow::VersionDef* versions) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete reinterpret_cast< ::google::protobuf::MessageLite*>(versions_);
  }
  if (versions) {
    ::google::protobuf::Arena* submessage_arena =
      reinterpret_cast< ::google::protobuf::MessageLite*>(versions)->GetArena();
    if (message_arena != submessage_arena) {
      versions = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, versions, submessage_arena);
    }

  } else {

  }
  versions_ = versions;
  // @@protoc_insertion_point(field_set_allocated:opencv_tensorflow.GraphDef.versions)
}

// int32 version = 3 [deprecated = true];
inline void GraphDef::clear_version() {
  version_ = 0;
}
inline ::google::protobuf::int32 GraphDef::version() const {
  // @@protoc_insertion_point(field_get:opencv_tensorflow.GraphDef.version)
  return version_;
}
inline void GraphDef::set_version(::google::protobuf::int32 value) {

  version_ = value;
  // @@protoc_insertion_point(field_set:opencv_tensorflow.GraphDef.version)
}

// .opencv_tensorflow.FunctionDefLibrary library = 2;
inline bool GraphDef::has_library() const {
  return this != internal_default_instance() && library_ != NULL;
}
inline const ::opencv_tensorflow::FunctionDefLibrary& GraphDef::library() const {
  const ::opencv_tensorflow::FunctionDefLibrary* p = library_;
  // @@protoc_insertion_point(field_get:opencv_tensorflow.GraphDef.library)
  return p != NULL ? *p : *reinterpret_cast<const ::opencv_tensorflow::FunctionDefLibrary*>(
      &::opencv_tensorflow::_FunctionDefLibrary_default_instance_);
}
inline ::opencv_tensorflow::FunctionDefLibrary* GraphDef::release_library() {
  // @@protoc_insertion_point(field_release:opencv_tensorflow.GraphDef.library)

  ::opencv_tensorflow::FunctionDefLibrary* temp = library_;
  if (GetArenaNoVirtual() != NULL) {
    temp = ::google::protobuf::internal::DuplicateIfNonNull(temp, NULL);
  }
  library_ = NULL;
  return temp;
}
inline ::opencv_tensorflow::FunctionDefLibrary* GraphDef::unsafe_arena_release_library() {
  // @@protoc_insertion_point(field_unsafe_arena_release:opencv_tensorflow.GraphDef.library)

  ::opencv_tensorflow::FunctionDefLibrary* temp = library_;
  library_ = NULL;
  return temp;
}
inline ::opencv_tensorflow::FunctionDefLibrary* GraphDef::mutable_library() {

  if (library_ == NULL) {
    _slow_mutable_library();
  }
  // @@protoc_insertion_point(field_mutable:opencv_tensorflow.GraphDef.library)
  return library_;
}
inline void GraphDef::set_allocated_library(::opencv_tensorflow::FunctionDefLibrary* library) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete reinterpret_cast< ::google::protobuf::MessageLite*>(library_);
  }
  if (library) {
    ::google::protobuf::Arena* submessage_arena =
      reinterpret_cast< ::google::protobuf::MessageLite*>(library)->GetArena();
    if (message_arena != submessage_arena) {
      library = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, library, submessage_arena);
    }

  } else {

  }
  library_ = library;
  // @@protoc_insertion_point(field_set_allocated:opencv_tensorflow.GraphDef.library)
}

// -------------------------------------------------------------------

// -------------------------------------------------------------------

// NodeDef

// string name = 1;
inline void NodeDef::clear_name() {
  name_.ClearToEmpty(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), GetArenaNoVirtual());
}
inline const ::std::string& NodeDef::name() const {
  // @@protoc_insertion_point(field_get:opencv_tensorflow.NodeDef.name)
  return name_.Get();
}
inline void NodeDef::set_name(const ::std::string& value) {

  name_.Set(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value, GetArenaNoVirtual());
  // @@protoc_insertion_point(field_set:opencv_tensorflow.NodeDef.name)
}
#if LANG_CXX11
inline void NodeDef::set_name(::std::string&& value) {

  name_.Set(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value), GetArenaNoVirtual());
  // @@protoc_insertion_point(field_set_rvalue:opencv_tensorflow.NodeDef.name)
}
#endif
inline void NodeDef::set_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);

  name_.Set(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value),
              GetArenaNoVirtual());
  // @@protoc_insertion_point(field_set_char:opencv_tensorflow.NodeDef.name)
}
inline void NodeDef::set_name(const char* value,
    size_t size) {

  name_.Set(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(
      reinterpret_cast<const char*>(value), size), GetArenaNoVirtual());
  // @@protoc_insertion_point(field_set_pointer:opencv_tensorflow.NodeDef.name)
}
inline ::std::string* NodeDef::mutable_name() {

  // @@protoc_insertion_point(field_mutable:opencv_tensorflow.NodeDef.name)
  return name_.Mutable(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), GetArenaNoVirtual());
}
inline ::std::string* NodeDef::release_name() {
  // @@protoc_insertion_point(field_release:opencv_tensorflow.NodeDef.name)

  return name_.Release(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), GetArenaNoVirtual());
}
inline void NodeDef::set_allocated_name(::std::string* name) {
  if (name != NULL) {

  } else {

  }
  name_.SetAllocated(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name,
      GetArenaNoVirtual());
  // @@protoc_insertion_point(field_set_allocated:opencv_tensorflow.NodeDef.name)
}
inline ::std::string* NodeDef::unsafe_arena_release_name() {
  // @@protoc_insertion_point(field_unsafe_arena_release:opencv_tensorflow.NodeDef.name)
  GOOGLE_DCHECK(GetArenaNoVirtual() != NULL);

  return name_.UnsafeArenaRelease(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      GetArenaNoVirtual());
}
inline void NodeDef::unsafe_arena_set_allocated_name(
    ::std::string* name) {
  GOOGLE_DCHECK(GetArenaNoVirtual() != NULL);
  if (name != NULL) {

  } else {

  }
  name_.UnsafeArenaSetAllocated(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      name, GetArenaNoVirtual());
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:opencv_tensorflow.NodeDef.name)
}

// string op = 2;
inline void NodeDef::clear_op() {
  op_.ClearToEmpty(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), GetArenaNoVirtual());
}
inline const ::std::string& NodeDef::op() const {
  // @@protoc_insertion_point(field_get:opencv_tensorflow.NodeDef.op)
  return op_.Get();
}
inline void NodeDef::set_op(const ::std::string& value) {

  op_.Set(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value, GetArenaNoVirtual());
  // @@protoc_insertion_point(field_set:opencv_tensorflow.NodeDef.op)
}
#if LANG_CXX11
inline void NodeDef::set_op(::std::string&& value) {

  op_.Set(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value), GetArenaNoVirtual());
  // @@protoc_insertion_point(field_set_rvalue:opencv_tensorflow.NodeDef.op)
}
#endif
inline void NodeDef::set_op(const char* value) {
  GOOGLE_DCHECK(value != NULL);

  op_.Set(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value),
              GetArenaNoVirtual());
  // @@protoc_insertion_point(field_set_char:opencv_tensorflow.NodeDef.op)
}
inline void NodeDef::set_op(const char* value,
    size_t size) {

  op_.Set(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(
      reinterpret_cast<const char*>(value), size), GetArenaNoVirtual());
  // @@protoc_insertion_point(field_set_pointer:opencv_tensorflow.NodeDef.op)
}
inline ::std::string* NodeDef::mutable_op() {

  // @@protoc_insertion_point(field_mutable:opencv_tensorflow.NodeDef.op)
  return op_.Mutable(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), GetArenaNoVirtual());
}
inline ::std::string* NodeDef::release_op() {
  // @@protoc_insertion_point(field_release:opencv_tensorflow.NodeDef.op)

  return op_.Release(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), GetArenaNoVirtual());
}
inline void NodeDef::set_allocated_op(::std::string* op) {
  if (op != NULL) {

  } else {

  }
  op_.SetAllocated(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), op,
      GetArenaNoVirtual());
  // @@protoc_insertion_point(field_set_allocated:opencv_tensorflow.NodeDef.op)
}
inline ::std::string* NodeDef::unsafe_arena_release_op() {
  // @@protoc_insertion_point(field_unsafe_arena_release:opencv_tensorflow.NodeDef.op)
  GOOGLE_DCHECK(GetArenaNoVirtual() != NULL);

  return op_.UnsafeArenaRelease(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      GetArenaNoVirtual());
}
inline void NodeDef::unsafe_arena_set_allocated_op(
    ::std::string* op) {
  GOOGLE_DCHECK(GetArenaNoVirtual() != NULL);
  if (op != NULL) {

  } else {

  }
  op_.UnsafeArenaSetAllocated(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      op, GetArenaNoVirtual());
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:opencv_tensorflow.NodeDef.op)
}

// repeated string input = 3;
inline int NodeDef::input_size() const {
  return input_.size();
}
inline void NodeDef::clear_input() {
  input_.Clear();
}
inline const ::std::string& NodeDef::input(int index) const {
  // @@protoc_insertion_point(field_get:opencv_tensorflow.NodeDef.input)
  return input_.Get(index);
}
inline ::std::string* NodeDef::mutable_input(int index) {
  // @@protoc_insertion_point(field_mutable:opencv_tensorflow.NodeDef.input)
  return input_.Mutable(index);
}
inline void NodeDef::set_input(int index, const ::std::string& value) {
  // @@protoc_insertion_point(field_set:opencv_tensorflow.NodeDef.input)
  input_.Mutable(index)->assign(value);
}
#if LANG_CXX11
inline void NodeDef::set_input(int index, ::std::string&& value) {
  // @@protoc_insertion_point(field_set:opencv_tensorflow.NodeDef.input)
  input_.Mutable(index)->assign(std::move(value));
}
#endif
inline void NodeDef::set_input(int index, const char* value) {
  GOOGLE_DCHECK(value != NULL);
  input_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:opencv_tensorflow.NodeDef.input)
}
inline void NodeDef::set_input(int index, const char* value, size_t size) {
  input_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:opencv_tensorflow.NodeDef.input)
}
inline ::std::string* NodeDef::add_input() {
  // @@protoc_insertion_point(field_add_mutable:opencv_tensorflow.NodeDef.input)
  return input_.Add();
}
inline void NodeDef::add_input(const ::std::string& value) {
  input_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:opencv_tensorflow.NodeDef.input)
}
#if LANG_CXX11
inline void NodeDef::add_input(::std::string&& value) {
  input_.Add(std::move(value));
  // @@protoc_insertion_point(field_add:opencv_tensorflow.NodeDef.input)
}
#endif
inline void NodeDef::add_input(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  input_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:opencv_tensorflow.NodeDef.input)
}
inline void NodeDef::add_input(const char* value, size_t size) {
  input_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:opencv_tensorflow.NodeDef.input)
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
NodeDef::input() const {
  // @@protoc_insertion_point(field_list:opencv_tensorflow.NodeDef.input)
  return input_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
NodeDef::mutable_input() {
  // @@protoc_insertion_point(field_mutable_list:opencv_tensorflow.NodeDef.input)
  return &input_;
}

// string device = 4;
inline void NodeDef::clear_device() {
  device_.ClearToEmpty(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), GetArenaNoVirtual());
}
inline const ::std::string& NodeDef::device() const {
  // @@protoc_insertion_point(field_get:opencv_tensorflow.NodeDef.device)
  return device_.Get();
}
inline void NodeDef::set_device(const ::std::string& value) {

  device_.Set(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value, GetArenaNoVirtual());
  // @@protoc_insertion_point(field_set:opencv_tensorflow.NodeDef.device)
}
#if LANG_CXX11
inline void NodeDef::set_device(::std::string&& value) {

  device_.Set(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value), GetArenaNoVirtual());
  // @@protoc_insertion_point(field_set_rvalue:opencv_tensorflow.NodeDef.device)
}
#endif
inline void NodeDef::set_device(const char* value) {
  GOOGLE_DCHECK(value != NULL);

  device_.Set(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value),
              GetArenaNoVirtual());
  // @@protoc_insertion_point(field_set_char:opencv_tensorflow.NodeDef.device)
}
inline void NodeDef::set_device(const char* value,
    size_t size) {

  device_.Set(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(
      reinterpret_cast<const char*>(value), size), GetArenaNoVirtual());
  // @@protoc_insertion_point(field_set_pointer:opencv_tensorflow.NodeDef.device)
}
inline ::std::string* NodeDef::mutable_device() {

  // @@protoc_insertion_point(field_mutable:opencv_tensorflow.NodeDef.device)
  return device_.Mutable(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), GetArenaNoVirtual());
}
inline ::std::string* NodeDef::release_device() {
  // @@protoc_insertion_point(field_release:opencv_tensorflow.NodeDef.device)

  return device_.Release(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), GetArenaNoVirtual());
}
inline void NodeDef::set_allocated_device(::std::string* device) {
  if (device != NULL) {

  } else {

  }
  device_.SetAllocated(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), device,
      GetArenaNoVirtual());
  // @@protoc_insertion_point(field_set_allocated:opencv_tensorflow.NodeDef.device)
}
inline ::std::string* NodeDef::unsafe_arena_release_device() {
  // @@protoc_insertion_point(field_unsafe_arena_release:opencv_tensorflow.NodeDef.device)
  GOOGLE_DCHECK(GetArenaNoVirtual() != NULL);

  return device_.UnsafeArenaRelease(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      GetArenaNoVirtual());
}
inline void NodeDef::unsafe_arena_set_allocated_device(
    ::std::string* device) {
  GOOGLE_DCHECK(GetArenaNoVirtual() != NULL);
  if (device != NULL) {

  } else {

  }
  device_.UnsafeArenaSetAllocated(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      device, GetArenaNoVirtual());
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:opencv_tensorflow.NodeDef.device)
}

// map<string, .opencv_tensorflow.AttrValue> attr = 5;
inline int NodeDef::attr_size() const {
  return attr_.size();
}
inline const ::google::protobuf::Map< ::std::string, ::opencv_tensorflow::AttrValue >&
NodeDef::attr() const {
  // @@protoc_insertion_point(field_map:opencv_tensorflow.NodeDef.attr)
  return attr_.GetMap();
}
inline ::google::protobuf::Map< ::std::string, ::opencv_tensorflow::AttrValue >*
NodeDef::mutable_attr() {
  // @@protoc_insertion_point(field_mutable_map:opencv_tensorflow.NodeDef.attr)
  return attr_.MutableMap();
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace opencv_tensorflow

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_graph_2eproto__INCLUDED
