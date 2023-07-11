=head1 Name

SPVM::Document::NativeAPI::Method - Method Native APIs

=head1 Description

The method native APIs are the APIs to manipulate information of methods.

=head1 Usage

  SPVM_API_METHOD* api_method = env->api->method;
  
  const char* method_name = api_method->get_name(env->runtime, method);

The C<method> is got by the L<get_method_by_index|SPVM::Document::NativeAPI::BasicType/"get_method_by_index"> and the L<get_method_by_name|SPVM::Document::NativeAPI::BasicType/"get_method_by_name"> basic type native API.

=head1 Native APIs

=head2 get_name

  const void* (*get_name)(void* runtime, void* method);

Returns the name of the method.

=head2 get_index

  int32_t (*get_index)(void* runtime, void* method);

Returns the index of the method.

=head2 get_return_basic_type

  void* (*get_return_basic_type)(void* runtime, void* method);

Returns the L<basic type|SPVM::Document::NativeAPI::BasicType> object of the return value of the method.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 get_return_type_dimension

  int32_t (*get_return_type_dimension)(void* runtime, void* method);

Returns the type dimention of the return value of the method.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 get_return_type_flag

  int32_t (*get_return_type_flag)(void* runtime, void* method);

Returns the type flag of the return value of the method.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 get_arg_by_index

  void* (*get_arg_by_index)(void* runtime, void* method, int32_t arg_index);

Gets an L<argument|SPVM::Document::NativeAPI::Argument> object by an argument index, and returns it.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 get_args_length

  int32_t (*get_args_length)(void* runtime, void* method);

Returns the length of the arguments of the method.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 get_required_args_length

  int32_t (*get_required_args_length)(void* runtime, void* method);

Returns the length of the required arguments of the method.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 get_current_basic_type

  void* (*get_current_basic_type)(void* runtime, void* method);

Returns the current L<basic type|SPVM::Document::NativeAPI::BasicType> object of the method.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 get_opcode_by_index

  void* (*get_opcode_by_index)(void* runtime, void* method, int32_t opcode_index);

Gets an operation code object by an operation code index, and returns it.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 get_opcodes_length

  int32_t (*get_opcodes_length)(void* runtime, void* method);

Returns the length of operation codes.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 is_class_method

  int32_t (*is_class_method)(void* runtime, void* method);

If the method is a class method, returns 1. Otherwise returns 0.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 is_anon

  int32_t (*is_anon)(void* runtime, void* method);

If the method is a anon method, returns 1. Otherwise returns 0.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 is_native

  int32_t (*is_native)(void* runtime, void* method);

If the method is a native method, returns 1. Otherwise returns 0.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 is_precompile

  int32_t (*is_precompile)(void* runtime, void* method);

If the method is a precompiled method, returns 1. Otherwise returns 0.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 is_enum

  int32_t (*is_enum)(void* runtime, void* method);

If the method is a enum method, returns 1. Otherwise returns 0.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 get_byte_vars_width

  int32_t (*get_byte_vars_width)(void* runtime, void* method);

Returns the total byte size of the byte variables assigned by the method.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 get_short_vars_width

  int32_t (*get_short_vars_width)(void* runtime, void* method);

Returns the total byte size of the short variables assigned by the method.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 get_int_vars_width

  int32_t (*get_int_vars_width)(void* runtime, void* method);

Returns the total byte size of the int variables assigned by the method.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 get_long_vars_width

  int32_t (*get_long_vars_width)(void* runtime, void* method);

Returns the total byte size of the long variables assigned by the method.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 get_float_vars_width

  int32_t (*get_float_vars_width)(void* runtime, void* method);

Returns the total byte size of the float variables assigned by the method.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 get_double_vars_width

  int32_t (*get_double_vars_width)(void* runtime, void* method);

Returns the total byte size of the double variables assigned by the method.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 get_object_vars_width

  int32_t (*get_object_vars_width)(void* runtime, void* method);

Returns the total byte size of the object variables assigned by the method.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 get_ref_vars_width

  int32_t (*get_ref_vars_width)(void* runtime, void* method);

Returns the total byte size of the reference variables assigned by the method.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 get_mortal_stack_length

  int32_t (*get_mortal_stack_length)(void* runtime, void* method);

Returns the length of the mortal stack of the method.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 get_native_address

  void* (*get_native_address)(void* runtime, void* method);

Returns the address of the native method.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 set_native_address

  void (*set_native_address)(void* runtime, void* method, void* address);

Sets an address of the native method.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 get_precompile_address

  void* (*get_precompile_address)(void* runtime, void* method);

Returns the address of the precompiled method.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

=head2 set_precompile_address

  void (*set_precompile_address)(void* runtime, void* method, void* address);

Sets an address of the precompiled method.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<method> argument is a method object.

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
  
=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
