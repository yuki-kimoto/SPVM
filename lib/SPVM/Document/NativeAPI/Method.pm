=head1 Name

SPVM::Document::NativeAPI::Method - Method Native APIs

=head1 Description

The method native APIs are the APIs to get information of methods.

=head1 Usage

  SPVM_API_METHOD* api_method = env->api->method;
  
  const char* method_name = api_method->get_name(env->runtime, method);

The C<method> is got by the L<get_method_by_index|SPVM::Document::NativeAPI::BasicType/"get_method_by_index"> and the L<get_method_by_name|SPVM::Document::NativeAPI::BasicType/"get_method_by_name"> basic type native API.

=head1 Native APIs

=head2 get_name

  const void* (*get_name)(void* runtime, void* method);

=head2 get_index

  int32_t (*get_index)(void* runtime, void* method);

=head2 get_return_basic_type

  void* (*get_return_basic_type)(void* runtime, void* method);

=head2 get_return_type_dimension

  int32_t (*get_return_type_dimension)(void* runtime, void* method);

=head2 get_return_type_flag

  int32_t (*get_return_type_flag)(void* runtime, void* method);

=head2 get_arg_by_index

  void* (*get_arg_by_index)(void* runtime, void* method, int32_t arg_index);

=head2 get_args_length

  int32_t (*get_args_length)(void* runtime, void* method);

=head2 get_required_args_length

  int32_t (*get_required_args_length)(void* runtime, void* method);

=head2 get_current_basic_type

  void* (*get_current_basic_type)(void* runtime, void* method);

=head2 get_opcodes

  void* (*get_opcodes)(void* runtime, void* method);

=head2 get_opcodes_length

  int32_t (*get_opcodes_length)(void* runtime, void* method);

=head2 get_is_class_method

  int32_t (*get_is_class_method)(void* runtime, void* method);

=head2 get_is_anon

  int32_t (*get_is_anon)(void* runtime, void* method);

=head2 get_is_native

  int32_t (*get_is_native)(void* runtime, void* method);

=head2 get_is_precompile

  int32_t (*get_is_precompile)(void* runtime, void* method);

=head2 get_is_enum

  int32_t (*get_is_enum)(void* runtime, void* method);

=head2 get_byte_vars_width

  int32_t (*get_byte_vars_width)(void* runtime, void* method);

=head2 get_short_vars_width

  int32_t (*get_short_vars_width)(void* runtime, void* method);

=head2 get_int_vars_width

  int32_t (*get_int_vars_width)(void* runtime, void* method);

=head2 get_long_vars_width

  int32_t (*get_long_vars_width)(void* runtime, void* method);

=head2 get_float_vars_width

  int32_t (*get_float_vars_width)(void* runtime, void* method);

=head2 get_double_vars_width

  int32_t (*get_double_vars_width)(void* runtime, void* method);

=head2 get_object_vars_width

  int32_t (*get_object_vars_width)(void* runtime, void* method);

=head2 get_ref_vars_width

  int32_t (*get_ref_vars_width)(void* runtime, void* method);

=head2 get_mortal_stack_length

  int32_t (*get_mortal_stack_length)(void* runtime, void* method);

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
  9 get_opcodes
  10 get_opcodes_length
  11 get_is_class_method
  12 get_is_anon
  13 get_is_native
  14 get_is_precompile
  15 get_is_enum
  16 get_byte_vars_width
  17 get_short_vars_width
  18 get_int_vars_width
  19 get_long_vars_width
  20 get_float_vars_width
  21 get_double_vars_width
  22 get_object_vars_width
  23 get_ref_vars_width
  24 get_mortal_stack_length

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
