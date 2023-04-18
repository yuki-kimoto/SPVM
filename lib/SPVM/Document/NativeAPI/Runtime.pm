=head1 Name

SPVM::Document::NativeAPI::Runtime - SPVM Runtime Native APIs

=head1 Usage

  // New a runtime
  void* runtime = env->api->runtime->new_object();
  
  // Build the runtime
  env->api->runtime->build(runtime, runtime_codes);
  
  // Free a runtime
  env->api->runtime->free_object(runtime);

=head1 Description

SPVM runtime native APIs are the public APIs to manipulate the runtime information.

=head1 Ids Of Runtime Native APIs

Runtime native APIs have its IDs.

  0  new_object
  1  free_object
  2  get_opcodes
  3  get_opcodes_length
  4  get_runtime_codes
  5  get_runtime_codes_length
  6  get_classes_length
  7  get_constant_string_id
  8  get_constant_string_value
  9  get_name
  10 get_basic_type_id_by_name
  11 get_basic_type_name_id
  12 get_basic_type_class_id
  13 get_basic_type_category
  14 get_type_basic_type_id
  15 get_type_dimension
  16 get_type_stack_length
  17 get_type_is_object
  18 get_type_is_ref
  19 get_class_id_by_name
  20 get_class_name_id
  21 get_class_class_rel_file_id
  22 get_class_class_path_id
  23 get_class_is_anon
  24 get_class_fields_base_id
  25 get_class_fields_length
  26 get_class_methods_base_id
  27 get_class_methods_length
  28 get_class_class_vars_base_id
  29 get_class_class_vars_length
  30 get_class_anon_methods_base_id
  31 get_class_anon_methods_length
  32 get_class_var_id_by_index
  33 get_class_var_id_by_name
  34 get_class_var_name_id
  35 get_class_var_class_id
  36 get_field_id_by_index
  37 get_field_id_by_name
  38 get_field_name_id
  39 get_field_type_id
  40 get_field_class_id
  41 get_method_id_by_index
  42 get_method_id_by_name
  43 get_method_name_id
  44 get_method_return_type_id
  45 get_method_class_id
  46 get_method_is_class_method
  47 get_method_is_anon
  48 get_method_is_native
  49 get_method_is_precompile
  50 get_method_call_stack_byte_vars_length
  51 get_method_call_stack_short_vars_length
  52 get_method_call_stack_int_vars_length
  53 get_method_call_stack_long_vars_length
  54 get_method_call_stack_float_vars_length
  55 get_method_call_stack_double_vars_length
  56 get_method_call_stack_object_vars_length
  57 get_method_call_stack_ref_vars_length
  58 get_method_mortal_stack_length
  59 get_method_opcodes_base_id
  60 get_method_opcodes_length
  61 get_method_args_base_id
  62 get_method_args_length
  63 get_arg_type_id
  64 get_anon_method_method_id
  65 get_native_method_address
  66 set_native_method_address
  67 get_precompile_method_address
  68 set_precompile_method_address
  69 object_header_size
  70 object_weaken_backref_head_offset
  71 object_ref_count_offset
  72 object_basic_type_id_offset
  73 object_type_dimension_offset
  74 object_flag_offset
  75 object_length_offset
  76 get_allocator
  77 build
  78 get_class_parent_class_id
  79 get_method_required_args_length
  80 get_class_is_pointer
  81 get_method_is_enum
  82 get_type_flag
  83 is_object_type
  84 get_class_version_id

=head1 Runtime Native APIs

=head2 new_object

  void* (*new_object)();

=head2 free_object

  void (*free_object)(void* runtime);

=head2 get_opcodes

  int32_t* (*get_opcodes)(void* runtime);

=head2 get_opcodes_length

  int32_t (*get_opcodes_length)(void* runtime);

=head2 get_runtime_codes

  int32_t* (*get_runtime_codes)(void* runtime);

=head2 get_runtime_codes_length

  int32_t (*get_runtime_codes_length)(void* runtime);

=head2 get_classes_length

  int32_t (*get_classes_length)(void* runtime);

=head2 get_constant_string_id

  int32_t (*get_constant_string_id)(void* runtime, const char* string);

=head2 get_constant_string_value

  const char* (*get_constant_string_value)(void* runtime, int32_t constant_string_id, int32_t* string_length);

=head2 get_name

  const char* (*get_name)(void* runtime, int32_t constant_string_id);

=head2 get_basic_type_id_by_name

  int32_t (*get_basic_type_id_by_name)(void* runtime, const char* basic_type_name);

=head2 get_basic_type_name_id

  int32_t (*get_basic_type_name_id)(void* runtime, int32_t basic_type_id);

=head2 get_basic_type_class_id

  int32_t (*get_basic_type_class_id)(void* runtime, int32_t basic_type_id);

=head2 get_basic_type_category

  int32_t (*get_basic_type_category)(void* runtime, int32_t basic_type_id);

=head2 get_type_basic_type_id

  int32_t (*get_type_basic_type_id)(void* runtime, int32_t type_id);

=head2 get_type_dimension

  int32_t (*get_type_dimension)(void* runtime, int32_t type_id);

=head2 get_type_stack_length

  int32_t (*get_type_stack_length)(void* runtime, int32_t type_id);

=head2 get_type_is_object

  int32_t (*get_type_is_object)(void* runtime, int32_t type_id);

=head2 get_type_is_ref

  int32_t (*get_type_is_ref)(void* runtime, int32_t type_id);

=head2 get_class_id_by_name

  int32_t (*get_class_id_by_name)(void* runtime, const char* class_name);

=head2 get_class_name_id

  int32_t (*get_class_name_id)(void* runtime, int32_t class_id);

=head2 get_class_class_rel_file_id

  int32_t (*get_class_class_rel_file_id)(void* runtime, int32_t class_id);

=head2 get_class_class_path_id

  int32_t (*get_class_class_path_id)(void* runtime, int32_t class_id);

=head2 get_class_is_anon

  int32_t (*get_class_is_anon)(void* runtime, int32_t class_id);

=head2 get_class_fields_base_id

  int32_t (*get_class_fields_base_id)(void* runtime, int32_t class_id);

=head2 get_class_fields_length

  int32_t (*get_class_fields_length)(void* runtime, int32_t class_id);

=head2 get_class_methods_base_id

  int32_t (*get_class_methods_base_id)(void* runtime, int32_t class_id);

=head2 get_class_methods_length

  int32_t (*get_class_methods_length)(void* runtime, int32_t class_id);

=head2 get_class_class_vars_base_id

  int32_t (*get_class_class_vars_base_id)(void* runtime, int32_t class_id);

=head2 get_class_class_vars_length

  int32_t (*get_class_class_vars_length)(void* runtime, int32_t class_id);

=head2 get_class_anon_methods_base_id

  int32_t (*get_class_anon_methods_base_id)(void* runtime, int32_t class_id);

=head2 get_class_anon_methods_length

  int32_t (*get_class_anon_methods_length)(void* runtime, int32_t class_id);

=head2 get_class_var_id_by_index

  int32_t (*get_class_var_id_by_index)(void* runtime, int32_t class_id, int32_t class_var_index);

=head2 get_class_var_id_by_name

  int32_t (*get_class_var_id_by_name)(void* runtime, const char* class_name, const char* class_var_name);

=head2 get_class_var_name_id

  int32_t (*get_class_var_name_id)(void* runtime, int32_t class_var_id);

=head2 get_class_var_class_id

  int32_t (*get_class_var_class_id)(void* runtime, int32_t class_var_id);

=head2 get_field_id_by_index

  int32_t (*get_field_id_by_index)(void* runtime, int32_t class_id, int32_t field_index);

=head2 get_field_id_by_name

  int32_t (*get_field_id_by_name)(void* runtime, const char* class_name, const char* field_name);

=head2 get_field_name_id

  int32_t (*get_field_name_id)(void* runtime, int32_t field_id);

=head2 get_field_type_id

  int32_t (*get_field_type_id)(void* runtime, int32_t field_id);

=head2 get_field_class_id

  int32_t (*get_field_class_id)(void* runtime, int32_t field_id);

=head2 get_method_id_by_index

  int32_t (*get_method_id_by_index)(void* runtime, int32_t class_id, int32_t method_index);

=head2 get_method_id_by_name

  int32_t (*get_method_id_by_name)(void* runtime, const char* class_name, const char* method_name);

=head2 get_method_name_id

  int32_t (*get_method_name_id)(void* runtime, int32_t method_id);

=head2 get_method_return_type_id

  int32_t (*get_method_return_type_id)(void* runtime, int32_t method_id);

=head2 get_method_class_id

  int32_t (*get_method_class_id)(void* runtime, int32_t method_id);

=head2 get_method_is_class_method

  int32_t (*get_method_is_class_method)(void* runtime, int32_t method_id);

=head2 get_method_is_anon

  int32_t (*get_method_is_anon)(void* runtime, int32_t method_id);

=head2 get_method_is_native

  int32_t (*get_method_is_native)(void* runtime, int32_t method_id);

=head2 get_method_is_precompile

  int32_t (*get_method_is_precompile)(void* runtime, int32_t method_id);

=head2 get_method_call_stack_byte_vars_length

  int32_t (*get_method_call_stack_byte_vars_length)(void* runtime, int32_t method_id);

=head2 get_method_call_stack_short_vars_length

  int32_t (*get_method_call_stack_short_vars_length)(void* runtime, int32_t method_id);

=head2 get_method_call_stack_int_vars_length

  int32_t (*get_method_call_stack_int_vars_length)(void* runtime, int32_t method_id);

=head2 get_method_call_stack_long_vars_length

  int32_t (*get_method_call_stack_long_vars_length)(void* runtime, int32_t method_id);

=head2 get_method_call_stack_float_vars_length

  int32_t (*get_method_call_stack_float_vars_length)(void* runtime, int32_t method_id);

=head2 get_method_call_stack_double_vars_length

  int32_t (*get_method_call_stack_double_vars_length)(void* runtime, int32_t method_id);

=head2 get_method_call_stack_object_vars_length

  int32_t (*get_method_call_stack_object_vars_length)(void* runtime, int32_t method_id);

=head2 get_method_call_stack_ref_vars_length

  int32_t (*get_method_call_stack_ref_vars_length)(void* runtime, int32_t method_id);

=head2 get_method_mortal_stack_length

  int32_t (*get_method_mortal_stack_length)(void* runtime, int32_t method_id);

=head2 get_method_opcodes_base_id

  int32_t (*get_method_opcodes_base_id)(void* runtime, int32_t method_id);

=head2 get_method_opcodes_length

  int32_t (*get_method_opcodes_length)(void* runtime, int32_t method_id);

=head2 get_method_args_base_id

  int32_t (*get_method_args_base_id)(void* runtime, int32_t method_id);

=head2 get_method_args_length

  int32_t (*get_method_args_length)(void* runtime, int32_t method_id);

=head2 get_arg_type_id

  int32_t (*get_arg_type_id)(void* runtime, int32_t arg_id);

=head2 get_anon_method_method_id

  int32_t (*get_anon_method_method_id)(void* runtime, int32_t anon_method_id);

=head2 get_native_method_address

  void* (*get_native_method_address)(void* runtime, int32_t method_id);

=head2 set_native_method_address

  void (*set_native_method_address)(void* runtime, int32_t method_id, void* address);

=head2 get_precompile_method_address

  void* (*get_precompile_method_address)(SPVM_ENV*, int32_t method_id);

=head2 set_precompile_method_address

  void (*set_precompile_method_address)(void* runtime, int32_t method_id, void* address);

=head2 object_header_size

  void* object_header_size;

=head2 object_weaken_backref_head_offset

  void* object_weaken_backref_head_offset;

=head2 object_ref_count_offset

  void* object_ref_count_offset;

=head2 object_basic_type_id_offset

  void* object_basic_type_id_offset;

=head2 object_type_dimension_offset

  void* object_type_dimension_offset;

=head2 object_flag_offset

  void* object_flag_offset;

=head2 object_length_offset

  void* object_length_offset;

=head2 get_allocator

  void* (*get_allocator)(void* runtime);

=head2 build

  void (*build)(void* runtime, int32_t* runtime_codes);

=head2 get_class_parent_class_id

  int32_t (*get_class_parent_class_id)(void* runtime, int32_t class_id);

=head2 get_method_required_args_length

  int32_t (*get_method_required_args_length)(void* runtime, int32_t method_id);

=head2 get_class_is_pointer

  int32_t (*get_class_is_pointer)(void* runtime, int32_t class_id);

=head2 get_method_is_enum

  int32_t (*get_class_is_pointer)(void* runtime, int32_t class_id);

=head2 get_type_flag

  int32_t (*get_type_flag)(void* runtime, int32_t type_id);

=head2 is_object_type

  int32_t (*is_object_type)(void* runtime, int32_t basic_type_id, int32_t type_dimension, int32_t flag);

=head2 get_class_version_id

  int32_t (*get_class_version_id)(void* runtime, int32_t class_id);

Gets the ID of the constant string of the version number.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
