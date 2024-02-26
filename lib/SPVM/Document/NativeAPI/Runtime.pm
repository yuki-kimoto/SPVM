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

Returns the offset of data area in the data structure C<SPVM_OBJECT>.

The data structure C<SPVM_OBJECT> is a data structure in the C language for SPVM objects.

Elements in an array or fields or a pointer in a pointer class is stored into the data area.

=head2 get_object_ref_count_offset

C<int32_t (*get_object_ref_count_offset)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>);>

Returns the offset of the C<ref_count> member variable in the data structure C<SPVM_OBJECT>.

The data structure C<SPVM_OBJECT> is a data structure in the C language for SPVM objects.

=head2 get_object_length_offset

C<int32_t (*get_object_length_offset)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>);>

Returns the offset of the C<length> member variable in the data structure C<SPVM_OBJECT>.

The data structure C<SPVM_OBJECT> is a data structure in the C language for SPVM objects.

=head2 get_basic_type_by_id

C<void* (*get_basic_type_by_id)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, int32_t basic_type_id);>

Returns a L<basic type|SPVM::Document::NativeAPI::BasicType> object given the basic type ID.

=head2 get_basic_type_by_name

C<void* (*get_basic_type_by_name)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, const char* basic_type_name);>

Returns a L<basic type|SPVM::Document::NativeAPI::BasicType> object given the basic type name.

=head2 get_basic_types_length

C<int32_t (*get_basic_types_length)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>);>

Returns the length of the basic types defined in the SPVM runtime.

=head2 build_precompile_class_source

C<void (*build_precompile_class_source)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* string_buffer|SPVM::Document::NativeAPI::StringBuffer>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>);>

Creates the C source code for a precompiled methods defined in the basic type, and saves it to the string buffer.

=head2 build_precompile_method_source

C<void (*build_precompile_method_source)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* string_buffer|SPVM::Document::NativeAPI::StringBuffer>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Creates the C source code for a precompiled method, and saves it to the string buffer.

=head2 get_compiler

C<void* (*get_compiler)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>);>

Returns the compiler.

=head2 set_compiler

C<void (*set_compiler)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* compiler|SPVM::Document::NativeAPI::Compiler>);>

Sets the compiler.

=head2 get_spvm_stdin

C<FILE* (*get_spvm_stdin)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>);>

Returns SPVM's C<stdin>.

=head2 get_spvm_stdout

C<FILE* (*get_spvm_stdout)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>);>

Returns SPVM's C<stdout>.

=head2 get_spvm_stderr

C<FILE* (*get_spvm_stderr)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>);>

Returns SPVM's C<stderr>.

=head1 Native API IDs

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
