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

Returns the name of the method I<method>.

=head2 get_index

C<int32_t (*get_index)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the index of the method I<method>. This index is the position of the method I<method> in its belonging class.

=head2 get_return_basic_type

C<void* (*get_return_basic_type)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the L<basic type|SPVM::Document::NativeAPI::BasicType> of the return type of the method I<method>.

=head2 get_return_type_dimension

C<int32_t (*get_return_type_dimension)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the type dimention of the return type of the method I<method>.

=head2 get_return_type_flag

C<int32_t (*get_return_type_flag)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the L<type flag ID|SPVM::Document::NativeAPI/"Type Flag IDs"> of the return type of the method I<method>.

=head2 get_arg_by_index

C<void* (*get_arg_by_index)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>, int32_t arg_index);>

Searches a L<argument|SPVM::Document::NativeAPI::Argument> at the index I<arg_index>.

If it is found, returns it. Otherwise, returns C<NULL>.

=head2 get_args_length

C<int32_t (*get_args_length)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the length of the arguments of the method I<method>.

=head2 get_required_args_length

C<int32_t (*get_required_args_length)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the length of the required arguments of the method I<method>.

=head2 get_current_basic_type

C<void* (*get_current_basic_type)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the L<basic type|SPVM::Document::NativeAPI::BasicType> that owns the method I<method>.

=head2 get_opcode_by_index

C<void* (*get_opcode_by_index)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>, int32_t opcode_index);>

Searches an operation code at the index I<opcode_index>.

If it is found, returns it. Otherwise, returns C<NULL>.

=head2 get_opcodes_length

C<int32_t (*get_opcodes_length)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the length of operation codes.

=head2 is_class_method

C<int32_t (*is_class_method)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

If the method I<method> is a class method, returns 1, otherwise returns 0.

=head2 is_anon

C<int32_t (*is_anon)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

If the method I<method> is an anon method, returns 1, otherwise returns 0.

=head2 is_native

C<int32_t (*is_native)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

If the method I<method> is a native method, returns 1, otherwise returns 0.

=head2 is_precompile

C<int32_t (*is_precompile)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

If the method I<method> is a method with the C<precompile> attribute, returns 1, otherwise returns 0.

=head2 is_enum

C<int32_t (*is_enum)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

If the method I<method> is an enumeration, returns 1, otherwise returns 0.

=head2 get_byte_vars_width

C<int32_t (*get_byte_vars_width)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the length of the variables of the C<byte> type allocated by the method I<method>.

=head2 get_short_vars_width

C<int32_t (*get_short_vars_width)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the length of the variables of the C<short> type allocated by the method I<method>.

=head2 get_int_vars_width

C<int32_t (*get_int_vars_width)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the length of the variables of the C<int> type allocated by the method I<method>.

=head2 get_long_vars_width

C<int32_t (*get_long_vars_width)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the length of the variables of the C<long> type allocated by the method I<method>.

=head2 get_float_vars_width

C<int32_t (*get_float_vars_width)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the length of the variables of the C<float> type allocated by the method I<method>.

=head2 get_double_vars_width

C<int32_t (*get_double_vars_width)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the length of the variables of the C<double> type allocated by the method I<method>.

=head2 get_object_vars_width

C<int32_t (*get_object_vars_width)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the length of the variables of the object type allocated by the method I<method>.

=head2 get_ref_vars_width

C<int32_t (*get_ref_vars_width)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the length of the variables of the reference type allocated by the method I<method>.

=head2 get_mortal_stack_length

C<int32_t (*get_mortal_stack_length)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the length of the mortal stack of the method I<method>.

=head2 get_native_address

C<void* (*get_native_address)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the C<native_address> field of the method I<method>. The address of the machine code for a native method is stored to this field.

=head2 set_native_address

C<void (*set_native_address)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>, void* address);>

Sets I<address> to the C<native_address> field of the method I<method>.

=head2 get_precompile_address

C<void* (*get_precompile_address)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the C<precompile_address> field of the method I<method>. The address of the machine code for a precompiled method is stored to this field.

=head2 set_precompile_address

C<void (*set_precompile_address)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>, void* address);>

Sets I<address> to the C<precompile_address> field of the method I<method>.

=head2 is_precompile_fallback

C<int32_t (*is_precompile_fallback)(void* runtime, void* method);>

Gets the C<is_precompile_fallback> field.

If this field is a true value, the precompilation method that does not have the execution address is fallback to the vm method.

=head2 set_is_precompile_fallback

C<void (*set_is_precompile_fallback)(void* runtime, void* method, int32_t is_precompile_fallback);>

Sets the C<is_precompile_fallback> field to I<is_precompile_fallback>. 

=head2 is_not_permitted

C<int32_t (*is_not_permitted)(void* runtime, void* method);>

Gets the C<is_not_permitted> field.

If this field is a true value, the method throw an exception with C<eval_error_id> set to the basic type ID of L<

=head2 set_is_not_permitted

C<void (*set_is_not_permitted)(void* runtime, void* method, int32_t is_not_permitted);>

Sets the C<is_not_permitted> field to I<is_not_permitted>. 

This native API is intended for use by browser applications that want to implement a security sandbox.

=head2 get_args_signature

C<const char* (*get_args_signature)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the arguments signature of the method I<method>.

=head2 get_abs_name

C<const char* (*get_abs_name)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* method|SPVM::Document::NativeAPI::Method>);>

Returns the absolute name of the method I<method>.

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
  29 is_precompile_fallback
  30 set_is_precompile_fallback
  31 is_not_permitted
  32 set_is_not_permitted
  32 get_args_signature
  34 get_abs_name
  
=head1 See Also

=over 2

=item * L<SPVM::Document::NativeAPI>

=item * L<SPVM::Document::NativeClass>

=item * L<SPVM::Document>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
