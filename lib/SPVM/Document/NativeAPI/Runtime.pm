=head1 Name

SPVM::Document::NativeAPI::Runtime - Runtime Native APIs

=head1 Description

The runtime native APIs of L<SPVM> are the APIs for SPVM runtimes.

=head1 Usage

  SPVM_API_RUNTIME* api_runtime = env->api->runtime;
  
  int32_t basic_types_length = api_runtime->get_basic_types_length(env->runtime);

=head1 Runtime Native APIs

=head2 get_object_data_offset

C<int32_t (*get_object_data_offset)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>);>

Returns the offset of data area in L<SPVM_OBJECT|SPVM::Document::NativeAPI/"SPVM_OBJECT"> struct.

Elements in an array or fields or a pointer in a pointer class is stored into the data area.

=head2 get_object_ref_count_offset

C<int32_t (*get_object_ref_count_offset)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>);>

Returns the offset of the C<ref_count> field in L<SPVM_OBJECT|SPVM::Document::NativeAPI/"SPVM_OBJECT"> struct.

=head2 get_object_length_offset

C<int32_t (*get_object_length_offset)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>);>

Returns the offset of the C<length> field in L<SPVM_OBJECT|SPVM::Document::NativeAPI/"SPVM_OBJECT"> struct.

=head2 get_basic_type_by_id

C<void* (*get_basic_type_by_id)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, int32_t basic_type_id);>

Searches a L<basic type|SPVM::Document::NativeAPI::BasicType> given the basic type ID I<basic_type_id>.

If it is found, returns it. Otherwise, returns C<NULL>.

=head2 get_basic_type_by_name

C<void* (*get_basic_type_by_name)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, const char* basic_type_name);>

Searches a L<basic type|SPVM::Document::NativeAPI::BasicType> given the basic type name I<basic_type_name>.

If it is found, returns it. Otherwise, returns C<NULL>.

=head2 get_basic_types_length

C<int32_t (*get_basic_types_length)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>);>

Returns the length of the basic types owned by the SPVM runtime I<runtime>.

=head2 build_precompile_class_source

C<void (*build_precompile_class_source)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* string_buffer|SPVM::Document::NativeAPI::StringBuffer>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>);>

Creates a C source code for methods with the C<precompile> attribute defined in the class given by the its basic type I<basic_type>, and saves it to the string buffer I<string_buffer>.

=head2 build_precompile_method_source

C<void (*build_precompile_method_source)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* string_buffer|SPVM::Document::NativeAPI::StringBuffer>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Creates a C source code for the method I<method>, and saves it to the string buffer I<string_buffer>.

=head2 get_compiler

C<void* (*get_compiler)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>);>

Returns the value of the C<compiler> field. The compiler that build the runtime I<runtime> is stored to this field.

=head2 set_compiler

C<void (*set_compiler)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* compiler|SPVM::Document::NativeAPI::Compiler>);>

Sets I<compiler> to the C<compiler> field.

=head2 get_spvm_stdin

C<FILE* (*get_spvm_stdin)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>);>

Returns L<SPVM's standard input|SPVM::Document::Language::System/"Standard Streams">.

=head2 get_spvm_stdout

C<FILE* (*get_spvm_stdout)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>);>

Returns L<SPVM's standard output|SPVM::Document::Language::System/"Standard Streams">.

=head2 get_spvm_stderr

C<FILE* (*get_spvm_stderr)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>);>

Returns L<SPVM's standard error|SPVM::Document::Language::System/"Standard Streams">.

=head2 get_env

C<SPVM_ENV* (*get_env)(void* runtime);>

Returns the runtime environment.

=head2 get_object_capacity_offset

C<int32_t (*get_object_capacity_offset)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>);>

Returns the offset of C<capacity> membar variable in L<SPVM_OBJECT|SPVM::Document::NativeAPI/"SPVM_OBJECT"> struct.

=head2 method_begin_cb

C<void* method_begin_cb;>

The callback function called at the beginning of a method.

The callback function must be a function pointer with the following signature:

C<void cb(L<SPVM_ENV* env|SPVM::Document::NativeAPI>, L<SPVM_VALUE* stack|SPVM::Document::NativeAPI::Value>);>

=over 2

=item * I<env> : The runtime environment.

=item * I<stack> : The runtime stack. This can be used to access arguments.

=back

=head2 method_end_cb

C<void* method_end_cb;>

The callback function called at the end of a method.

The callback function must be a function pointer with the following signature:

C<void cb(L<SPVM_ENV* env|SPVM::Document::NativeAPI>, L<SPVM_VALUE* stack|SPVM::Document::NativeAPI::Value>);>

The arguments are the same as L</"method_begin_cb">. This can be used to access the return value.

=head2 object_data_offset

C<void* object_data_offset;>.

Returns the offset of C<data> member variavle in C<SPVM_OBJECT> object. This must not be used because it is only for internal.

=head2 object_length_offset

C<void* object_length_offset;>

Returns the offset of C<length> member variavle in C<SPVM_OBJECT> object. This must not be used because it is only for internal.

=head2 object_capacity_offset

C<void* object_capacity_offset;>

Returns the offset of C<capacity> member variavle in C<SPVM_OBJECT> object. This must not be used because it is only for internal.

=head2 stack_index_call_depth

C<void* stack_index_call_depth;>

The index of the C<call_depth> stack variable on the runtime stack. This value is cast to C<void*>.

Examples:

  int32_t call_depth_index = (int32_t)(intptr_t)env->api->runtime->stack_index_call_depth;
  int32_t call_depth = stack[call_depth_index].ival;

=head2 stack_index_caller_info_stack

C<void* stack_index_caller_info_stack;>

The index of the C<caller_info_stack> stack variable on the runtime stack. This value is cast to C<void*>.

Examples:

  int32_t caller_info_stack_index = (int32_t)(intptr_t)env->api->runtime->stack_index_caller_info_stack;
  void** caller_info_stack = (void**)stack[caller_info_stack_index].oval;

=head2 stack_index_caller_info_stack_record_size

C<void* stack_index_caller_info_stack_record_size;>

The index of the C<caller_info_stack_record_size> stack variable on the runtime stack. This value is cast to C<void*>.

Examples:

  int32_t record_size_index = (int32_t)(intptr_t)env->api->runtime->stack_index_caller_info_stack_record_size;
  int32_t record_size = stack[record_size_index].ival;

=head1 Native Runtime API IDs

  0 get_object_data_offset
  1 get_object_ref_count_offset
  2 get_object_length_offset
  3 get_basic_type_by_id
  4 get_basic_type_by_name
  5 get_basic_types_length
  6 build_precompile_class_source
  7 build_precompile_method_source
  8 get_compiler
  9 set_compiler
  10 get_spvm_stdin
  11 get_spvm_stdout
  12 get_spvm_stderr
  13 get_env
  14 get_object_capacity_offset
  15 method_begin_cb
  16 method_end_cb
  17 object_data_offset
  18 object_length_offset
  19 object_capacity_offset
  20 stack_index_call_depth
  21 stack_index_caller_info_stack
  22 stack_index_caller_info_stack_record_size
  
=head1 See Also

=over 2

=item * L<SPVM::Document::NativeAPI>

=item * L<SPVM::Document::NativeAPI::BasicType>

=item * L<SPVM::Document::NativeAPI::Method>

=item * L<SPVM::Document::NativeAPI::StringBuffer>

=item * L<SPVM::Document::NativeAPI::Compiler>

=item * L<SPVM::Document::NativeClass>

=item * L<SPVM::Document>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
