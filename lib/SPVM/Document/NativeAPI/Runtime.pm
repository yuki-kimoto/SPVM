=head1 Name

SPVM::Document::NativeAPI::Runtime - Runtime Native APIs

=head1 Description

The runtime native APIs of L<SPVM> are the APIs to manipulate information of runtime.

=head1 Usage

  SPVM_API_RUNTIME* api_runtime = env->api->runtime;
  
  int32_t basic_types_length = api_runtime->get_basic_types_length(env->runtime);

=head1 Runtime Native APIs

=head2 get_object_data_offset

  int32_t (*get_object_data_offset)(void* runtime);

Returns the offset of the data of the C<SPVM_OBJECT> type.

The C<runtime> argument is a runtime object.

=head2 get_object_ref_count_offset

  int32_t (*get_object_ref_count_offset)(void* runtime);

Returns the offset of the C<ref_count> member variable of the C<SPVM_OBJECT> type.

The C<runtime> argument is a runtime object.

=head2 get_object_length_offset

  int32_t (*get_object_length_offset)(void* runtime);

Returns the offset of the C<length> member variable of the C<SPVM_OBJECT> type.

The C<runtime> argument is a runtime object.

=head2 get_basic_type_by_id

  void* (*get_basic_type_by_id)(void* runtime, int32_t basic_type_id);

Gets a L<basic type|SPVM::Document::NativeAPI::BasicType> object by a basic type ID and returns it.

The C<runtime> argument is a runtime object.

=head2 get_basic_type_by_name

  void* (*get_basic_type_by_name)(void* runtime, const char* basic_type_name);

Gets a L<basic type|SPVM::Document::NativeAPI::BasicType> object by a basic type name and returns it.

The C<runtime> argument is a runtime object.

=head2 get_basic_types_length

  int32_t (*get_basic_types_length)(void* runtime);

Gets the length of the basic types.

The C<runtime> argument is a runtime object.

=head2 build_precompile_module_source

  void (*build_precompile_module_source)(void* runtime, void* string_buffer, void* module_basic_type);

Builds the C source code of a precompiled module, and saves it to the string buffer.

The C<runtime> argument is a runtime object.

The C<string_buffer> argument is a L<string buffer|SPVM::Document::NativeAPI::StringBuffer> object.

The C<module_basic_type> argument is a L<basic type|SPVM::Document::NativeAPI::BasicType> object.

=head2 build_precompile_method_source

  void (*build_precompile_method_source)(void* runtime, void* string_buffer, void* method);
  
Builds the C source code of a precompiled method, and saves it to the string buffer.

The C<runtime> argument is a runtime object.

The C<string_buffer> argument is a L<string buffer|SPVM::Document::NativeAPI::StringBuffer> object.

The C<method> argument is a L<method|SPVM::Document::NativeAPI::Method> object.

=head2 get_compiler

  void* (*get_compiler)(void* runtime);

=head2 set_compiler

  void (*set_compiler)(void* runtime, void* compiler);

=head2 get_spvm_stdin

  FILE* (*get_spvm_stdin)(void* runtime);

=head2 get_spvm_stdout

  FILE* (*get_spvm_stdout)(void* runtime);

=head2 get_spvm_stderr

  FILE* (*get_spvm_stderr)(void* runtime);

=head1 Native API IDs

  0 get_object_data_offset
  1 get_object_ref_count_offset
  2 get_object_length_offset
  3 get_basic_type_by_id
  4 get_basic_type_by_name
  5 get_basic_types_length
  6 build_precompile_module_source
  7 build_precompile_method_source
  8 get_compiler
  9 set_compiler
  10 get_spvm_stdin
  11 get_spvm_stdout
  12 get_spvm_stderr

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
