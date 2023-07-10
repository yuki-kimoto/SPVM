=head1 Name

SPVM::Document::NativeAPI::BasicType - Basic Type Native APIs

=head1 Description

The basic type native APIs are the APIs to get information of basic types.

=head1 Usage

  SPVM_API_BASIC_TYPE* api_basic_type = env->api->basic_type;
  
  const char* basic_type_name = api_class_var->get_name(runtime, basic_type);

The C<class_var> is got by the L<get_basic_type_by_id|SPVM::Document::NativeAPI::Runtime/"get_basic_type_by_id"> and the L<get_basic_type_by_name|SPVM::Document::NativeAPI::Runtime/"get_basic_type_by_name"> runtime native API.

=head1 Native APIs

=head2 get_name

  const void* (*get_name)(void* runtime, void* basic_type);

=head2 get_id

  int32_t (*get_id)(void* runtime, void* basic_type);

=head2 get_category

  int32_t (*get_category)(void* runtime, void* basic_type);

=head2 get_parent

  void* (*get_parent)(void* runtime, void* basic_type);

=head2 get_version_string

  const void* (*get_version_string)(void* runtime, void* basic_type);

=head2 get_module_dir

  const void* (*get_module_dir)(void* runtime, void* basic_type);

=head2 get_module_rel_file

  const void* (*get_module_rel_file)(void* runtime, void* basic_type);

=head2 get_is_pointer

  int32_t (*get_is_pointer)(void* runtime, void* basic_type);

=head2 get_is_anon

  int32_t (*get_is_anon)(void* runtime, void* basic_type);

=head2 get_class_var_by_index

  void* (*get_class_var_by_index)(void* runtime, void* basic_type, int32_t class_var_index);

=head2 get_class_var_by_name

  void* (*get_class_var_by_name)(void* runtime, void* basic_type, const void* class_var_name);

=head2 get_class_vars_length

  int32_t (*get_class_vars_length)(void* runtime, void* basic_type);

=head2 get_field_by_index

  void* (*get_field_by_index)(void* runtime, void* basic_type, int32_t field_index);

=head2 get_field_by_name

  void* (*get_field_by_name)(void* runtime, void* basic_type, const void* field_name);

=head2 get_fields_length

  int32_t (*get_fields_length)(void* runtime, void* basic_type);

=head2 get_method_by_index

  void* (*get_method_by_index)(void* runtime, void* basic_type, int32_t method_index);

=head2 get_method_by_name

  void* (*get_method_by_name)(void* runtime, void* basic_type, const void* method_name);

=head2 get_methods_length

  int32_t (*get_methods_length)(void* runtime, void* basic_type);

=head2 get_anon_basic_type_by_index

  void* (*get_anon_basic_type_by_index)(void* runtime, void* basic_type, int32_t anon_basic_type_index);  int32_t (*get_anon_basic_types_length)(void* runtime, void* basic_type);

=head1 Native API IDs

  0 get_name,
  1 get_index,
  2 get_return_basic_type,
  3 get_return_type_dimension,
  4 get_return_type_flag,
  5 get_arg_by_index,
  6 get_args_length,
  7 get_required_args_length,
  8 get_current_basic_type,
  9 get_opcodes,
  10 get_opcodes_length,
  11 get_is_class_method,
  12 get_is_anon,
  13 get_is_native,
  14 get_is_precompile,
  15 get_is_enum,
  16 get_byte_vars_width,
  17 get_short_vars_width,
  18 get_int_vars_width,
  19 get_long_vars_width,
  20 get_float_vars_width,
  21 get_double_vars_width,
  22 get_object_vars_width,
  23 get_ref_vars_width,
  24 get_mortal_stack_length,

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
