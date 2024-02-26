=head1 Name

SPVM::Document::NativeAPI::Method - Method Native APIs

=head1 Description

The method native APIs in L<SPVM> are the APIs to get definition information for methods.

=head1 Usage

  SPVM_API_METHOD* api_method = env->api->method;
  
  void* basic_type = env->get_basic_type(env, stack, "Foo");
  
  void* method = env->api->basic_type->get_method_by_name(env->runtime, basic_type, "get");
  
  const char* method_name = api_method->get_name(env->runtime, method);

=head1 Native APIs

=head2 get_name

C<const char* (*get_name)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the name of the method.

=head2 get_index

C<int32_t (*get_index)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the index of the method. This index is the position of the method in its belonging class.

=head2 get_return_basic_type

C<void* (*get_return_basic_type)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the L<basic type|SPVM::Document::NativeAPI::BasicType> of the return type of the method.

=head2 get_return_type_dimension

C<int32_t (*get_return_type_dimension)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the type dimention of the return type of the method.

=head2 get_return_type_flag

C<int32_t (*get_return_type_flag)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the L<type flag ID|SPVM::Document::NativeAPI/"Type Flag IDs"> of the return type of the method.

=head2 get_arg_by_index

C<void* (*get_arg_by_index)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>, int32_t arg_index);>

Gets the L<argument|SPVM::Document::NativeAPI::Argument> at the index I<arg_index>, and returns it.

=head2 get_args_length

C<int32_t (*get_args_length)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the length of the arguments of the method.

=head2 get_required_args_length

C<int32_t (*get_required_args_length)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the length of the required arguments of the method.

=head2 get_current_basic_type

C<void* (*get_current_basic_type)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the L<basic type|SPVM::Document::NativeAPI::BasicType> of the method where the method I<method> is defined.

=head2 get_opcode_by_index

C<void* (*get_opcode_by_index)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>, int32_t opcode_index);>

Gets the operation code at the index I<opcode_index>, and returns it.

=head2 get_opcodes_length

C<int32_t (*get_opcodes_length)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the length of operation codes.

=head2 is_class_method

C<int32_t (*is_class_method)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

If the method is a class method, returns 1, otherwise returns 0.

=head2 is_anon

C<int32_t (*is_anon)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

If the method is a anon method, returns 1, otherwise returns 0.

=head2 is_native

C<int32_t (*is_native)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

If the method is a native method, returns 1, otherwise returns 0.

=head2 is_precompile

C<int32_t (*is_precompile)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

If the method is a method with the C<precompile> attribute, returns 1, otherwise returns 0.

=head2 is_enum

C<int32_t (*is_enum)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

If the method is an enumeration, returns 1, otherwise returns 0.

=head2 get_byte_vars_width

C<int32_t (*get_byte_vars_width)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the length of the variables of the C<byte> type allocated by the method.

=head2 get_short_vars_width

C<int32_t (*get_short_vars_width)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the length of the variables of the C<short> type allocated by the method.

=head2 get_int_vars_width

C<int32_t (*get_int_vars_width)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the length of the variables of the C<int> type allocated by the method.

=head2 get_long_vars_width

C<int32_t (*get_long_vars_width)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the length of the variables of the C<long> type allocated by the method.

=head2 get_float_vars_width

C<int32_t (*get_float_vars_width)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the length of the variables of the C<float> type allocated by the method.

=head2 get_double_vars_width

C<int32_t (*get_double_vars_width)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the length of the variables of the C<double> type allocated by the method.

=head2 get_object_vars_width

C<int32_t (*get_object_vars_width)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the length of the variables of the object type allocated by the method.

=head2 get_ref_vars_width

C<int32_t (*get_ref_vars_width)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the length of the variables of the reference type allocated by the method.

=head2 get_mortal_stack_length

C<int32_t (*get_mortal_stack_length)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the length of the mortal stack of the method.

=head2 get_native_address

C<void* (*get_native_address)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the starting address of the machine code of the native method.

=head2 set_native_address

C<void (*set_native_address)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>, void* address);>

Sets the starting address of the machine code of the native method.

=head2 get_precompile_address

C<void* (*get_precompile_address)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the starting address of the machine code of the precompiled method.

=head2 set_precompile_address

C<void (*set_precompile_address)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>, void* address);>

Sets the starting address of the machine code of the precompiled method.

=head1 Native API IDs

  0 get_name
  1 get_index
  2 get_return_basic_type
  3 get_return_type_dimension
  4 get_return_type_flag
  5 get_arg_by_index
  6 get_args_length
  7 get_required_args_length
  8 get_current_basic_type
  9 get_opcode_by_index
  10 get_opcodes_length
  11 is_class_method
  12 is_anon
  13 is_native
  14 is_precompile
  15 is_enum
  16 get_byte_vars_width
  17 get_short_vars_width
  18 get_int_vars_width
  19 get_long_vars_width
  20 get_float_vars_width
  21 get_double_vars_width
  22 get_object_vars_width
  23 get_ref_vars_width
  24 get_mortal_stack_length
  25 get_native_address
  26 set_native_address
  27 get_precompile_address
  28 set_precompile_address

=head1 See Aloso

=over 2

=item * L<SPVM::Document::NativeAPI>

=item * L<SPVM::Document::NativeClass>

=item * L<SPVM::Document>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
