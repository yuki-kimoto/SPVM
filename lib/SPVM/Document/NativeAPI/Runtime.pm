=head1 Name

SPVM::Document::NativeAPI::Runtime - SPVM Runtime Native APIs

=head1 Synopsys

  // Runtime API
  void* runtime_api = env->api->runtime;
  
  // New runtime
  void* runtime = runtime_api->new_runtime();
  
  // Free runtime
  runtime_api->free_runtime(runtime);

=head1 Description

SPVM runtime native APIs are the public APIs to manipulate the runtime information.

=head1 Ids Of Runtime Native APIs

Runtime native APIs have its IDs.

  0  new_runtime
  1  free_runtime
  2  prepare
  3  get_opcodes
  4  get_opcodes_length
  5  get_spvm_32bit_codes
  6  get_spvm_32bit_codes_length
  7  get_classes_length
  8  get_constant_string_id
  9  get_constant_string_value
  10 get_name
  11 get_basic_type_id_by_name
  12 get_basic_type_name_id
  13 get_basic_type_class_id
  14 get_basic_type_category
  15 get_type_basic_type_id
  16 get_type_dimension
  17 get_type_width
  18 get_type_is_object
  19 get_type_is_ref
  20 get_class_id_by_name
  21 get_class_name_id
  22 get_class_module_rel_file_id
  23 get_class_module_dir_id
  24 get_class_is_anon
  25 get_class_fields_base_id
  26 get_class_fields_length
  27 get_class_methods_base_id
  28 get_class_methods_length
  29 get_class_class_vars_base_id
  30 get_class_class_vars_length
  31 get_class_anon_methods_base_id
  32 get_class_anon_methods_length
  33 get_class_var_id_by_index
  34 get_class_var_id_by_name
  35 get_class_var_name_id
  36 get_class_var_signature_id
  37 get_class_var_class_id
  38 get_field_id_by_index
  39 get_field_id_by_name
  40 get_field_name_id
  41 get_field_type_id
  42 get_field_signature_id
  43 get_field_class_id
  44 get_method_id_by_index
  45 get_method_id_by_name
  46 get_method_name_id
  47 get_method_signature_id
  48 get_method_return_type_id
  49 get_method_class_id
  50 get_method_is_class_method
  51 get_method_is_anon
  52 get_method_is_native
  53 get_method_is_precompile
  54 get_method_call_stack_byte_vars_length
  55 get_method_call_stack_short_vars_length
  56 get_method_call_stack_int_vars_length
  57 get_method_call_stack_long_vars_length
  58 get_method_call_stack_float_vars_length
  59 get_method_call_stack_double_vars_length
  60 get_method_call_stack_object_vars_length
  61 get_method_call_stack_ref_vars_length
  62 get_method_mortal_stack_length
  63 get_method_opcodes_base_id
  64 get_method_opcodes_length
  65 get_method_args_base_id
  66 get_method_args_length
  67 get_arg_type_id
  68 get_anon_method_method_id
  69 get_native_method_address
  70 set_native_method_address
  71 get_precompile_method_address
  72 set_precompile_method_address
  73 object_header_byte_size
  74 object_weaken_backref_head_offset
  75 object_ref_count_offset
  76 object_basic_type_id_offset
  77 object_type_dimension_offset
  78 object_flag_offset
  79 object_length_offset
  80 get_allocator
  81 build
  82 get_class_parent_class_id

=head1 Runtime Native APIs

=head2 new_runtime

  void* (*new_runtime)();

=head2 free_runtime

  void (*free_runtime)(void* runtime);

=head2 prepare

  void (*prepare)(void* runtime);

=head2 get_opcodes

  int32_t* (*get_opcodes)(void* runtime);

=head2 get_opcodes_length

  int32_t (*get_opcodes_length)(void* runtime);

=head2 get_spvm_32bit_codes

  int32_t* (*get_spvm_32bit_codes)(void* runtime);

=head2 get_spvm_32bit_codes_length

  int32_t (*get_spvm_32bit_codes_length)(void* runtime);

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

=head2 get_type_width

  int32_t (*get_type_width)(void* runtime, int32_t type_id);

=head2 get_type_is_object

  int32_t (*get_type_is_object)(void* runtime, int32_t type_id);

=head2 get_type_is_ref

  int32_t (*get_type_is_ref)(void* runtime, int32_t type_id);

=head2 get_class_id_by_name

  int32_t (*get_class_id_by_name)(void* runtime, const char* class_name);

=head2 get_class_name_id

  int32_t (*get_class_name_id)(void* runtime, int32_t class_id);

=head2 get_class_module_rel_file_id

  int32_t (*get_class_module_rel_file_id)(void* runtime, int32_t class_id);

=head2 get_class_module_dir_id

  int32_t (*get_class_module_dir_id)(void* runtime, int32_t class_id);

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

=head2 get_class_var_signature_id

  int32_t (*get_class_var_signature_id)(void* runtime, int32_t class_var_id);

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

=head2 get_field_signature_id

  int32_t (*get_field_signature_id)(void* runtime, int32_t field_id);

=head2 get_field_class_id

  int32_t (*get_field_class_id)(void* runtime, int32_t field_id);

=head2 get_method_id_by_index

  int32_t (*get_method_id_by_index)(void* runtime, int32_t class_id, int32_t method_index);

=head2 get_method_id_by_name

  int32_t (*get_method_id_by_name)(void* runtime, const char* class_name, const char* method_name);

=head2 get_method_name_id

  int32_t (*get_method_name_id)(void* runtime, int32_t method_id);

=head2 get_method_signature_id

  int32_t (*get_method_signature_id)(void* runtime, int32_t method_id);

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

=head2 object_header_byte_size

  void* object_header_byte_size;

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

  void (*build)(void* runtime, int32_t* spvm_32bit_codes);

=head2 get_class_parent_class_id

  int32_t (*get_class_parent_class_id)(void* runtime, int32_t class_id);
