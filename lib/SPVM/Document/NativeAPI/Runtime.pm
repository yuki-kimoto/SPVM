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
  3  reserved3
  4  get_runtime_codes
  5  get_runtime_codes_length
  6  reserved6
  7  reserved7
  8  get_constant_string_value
  9  get_name
  10 get_basic_type_id_by_name
  11 get_basic_type_name
  12 reserved12
  13 get_basic_type_category
  14 reserved14
  15 reserved15
  16 reserved16
  17 reserved17
  18 reserved18
  19 reserved19
  20 reserved20
  21 reserved21
  22 reserved22
  23 reserved23
  24 reserved24
  25 reserved25
  26 reserved26
  27 reserved27
  28 reserved28
  29 reserved29
  30 reserved30
  31 reserved31
  32 get_class_var
  33 reserved33
  34 get_class_var_name
  35 reserved35
  36 reserved36
  37 reserved37
  38 get_field_name
  39 reserved39
  40 reserved40
  41 reserved41
  42 reserved42
  43 get_method_name
  44 reserved44
  45 reserved45
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
  59 get_method_opcodes_base
  60 get_method_opcodes_length
  61 get_method_args_base
  62 get_method_args_length
  63 reserved63
  64 reserved64
  65 get_native_method_address
  66 set_native_method_address
  67 get_precompile_method_address
  68 set_precompile_method_address
  69 object_header_size
  70 object_weaken_backref_head_offset
  71 object_ref_count_offset
  72 reserved72
  73 reserved73
  74 reserved74
  75 object_length_offset
  76 get_allocator
  77 build
  78 reserved78
  79 get_method_required_args_length
  80 reserved80
  81 get_method_is_enum
  82 reserved82
  83 is_object_type
  84 reserved84
  85 reserved85
  86 can_assign
  87 get_basic_type_module_rel_file_id
  88 get_basic_type_module_dir_id
  89 get_basic_type_is_anon
  90 get_basic_type_fields_base
  91 get_basic_type_fields_length
  92 get_basic_type_methods_base
  93 get_basic_type_methods_length
  94 get_basic_type_class_vars_base
  95 get_basic_type_class_vars_length
  96 reserved96
  97 reserved97
  98 reserved98
  99 get_basic_types_length
  100 get_field_basic_type_id
  101 get_field_type_dimension
  102 get_field_type_flag
  103 get_class_var_basic_type_id
  104 get_class_var_type_dimension
  105 get_class_var_type_flag
  103 get_method_return_basic_type_id
  104 get_method_return_type_dimension
  105 get_method_return_type_flag
  106 get_arg_basic_type_id
  107 get_arg_type_dimension
  108 get_arg_type_flag
  109 get_method_current_basic_type_id
  110 get_basic_type_parent_id

=head1 Runtime Native APIs

=head2 new_object

  void* (*new_object)();

=head2 free_object

  void (*free_object)(void* runtime);

=head2 get_opcodes

  int32_t* (*get_opcodes)(void* runtime);

=head2 get_runtime_codes

  int32_t* (*get_runtime_codes)(void* runtime);

=head2 get_runtime_codes_length

  int32_t (*get_runtime_codes_length)(void* runtime);

=head2 get_constant_string_value

  const char* (*get_constant_string_value)(void* runtime, int32_t constant_string_id, int32_t* string_length);

=head2 get_name

  const char* (*get_name)(void* runtime, int32_t constant_string_id);

=head2 get_basic_type_id_by_name

  int32_t (*get_basic_type_id_by_name)(void* runtime, const char* basic_type_name);

=head2 get_basic_type_name

  const char* (*get_basic_type_name)(void* runtime, int32_t basic_type_id);

=head2 get_basic_type_category

  int32_t (*get_basic_type_category)(void* runtime, int32_t basic_type_id);

=head2 get_basic_type_module_rel_file_id

  int32_t (*get_basic_type_module_rel_file_id)(void* runtime, int32_t basic_type_id);

=head2 get_basic_type_include_dir_id

  int32_t (*get_basic_type_include_dir_id)(void* runtime, int32_t basic_type_id);

=head2 get_basic_type_is_anon

  int32_t (*get_basic_type_is_anon)(void* runtime, int32_t basic_type_id);

=head2 get_basic_type_fields_base

  int32_t (*get_basic_type_fields_base)(void* runtime, int32_t basic_type_id);

=head2 get_basic_type_fields_length

  int32_t (*get_basic_type_fields_length)(void* runtime, int32_t basic_type_id);

=head2 get_basic_type_methods_base

  int32_t (*get_basic_type_methods_base)(void* runtime, int32_t basic_type_id);

=head2 get_basic_type_methods_length

  int32_t (*get_basic_type_methods_length)(void* runtime, int32_t basic_type_id);

=head2 get_basic_type_class_vars_base

  int32_t (*get_basic_type_class_vars_base)(void* runtime, int32_t basic_type_id);

=head2 get_basic_type_class_vars_length

  int32_t (*get_basic_type_class_vars_length)(void* runtime, int32_t basic_type_id);

=head2 get_class_var

  void* (*get_class_var)(void* runtime, void* basic_type, int32_t class_var_index);

=head2 get_class_var_name

  const char* (*get_class_var_name)(void* runtime, void* class_var);

=head2 get_field_name

  const char* (*get_field_name)(void* runtime, void* field);

=head2 get_method_name

  const char* (*get_method_name)(void* runtime, void* method);

=head2 get_method_is_class_method

  int32_t (*get_method_is_class_method)(void* runtime, void* method);

=head2 get_method_is_anon

  int32_t (*get_method_is_anon)(void* runtime, void* method);

=head2 get_method_is_native

  int32_t (*get_method_is_native)(void* runtime, void* method);

=head2 get_method_is_precompile

  int32_t (*get_method_is_precompile)(void* runtime, void* method);

=head2 get_method_call_stack_byte_vars_length

  int32_t (*get_method_call_stack_byte_vars_length)(void* runtime, void* method);

=head2 get_method_call_stack_short_vars_length

  int32_t (*get_method_call_stack_short_vars_length)(void* runtime, void* method);

=head2 get_method_call_stack_int_vars_length

  int32_t (*get_method_call_stack_int_vars_length)(void* runtime, void* method);

=head2 get_method_call_stack_long_vars_length

  int32_t (*get_method_call_stack_long_vars_length)(void* runtime, void* method);

=head2 get_method_call_stack_float_vars_length

  int32_t (*get_method_call_stack_float_vars_length)(void* runtime, void* method);

=head2 get_method_call_stack_double_vars_length

  int32_t (*get_method_call_stack_double_vars_length)(void* runtime, void* method);

=head2 get_method_call_stack_object_vars_length

  int32_t (*get_method_call_stack_object_vars_length)(void* runtime, void* method);

=head2 get_method_call_stack_ref_vars_length

  int32_t (*get_method_call_stack_ref_vars_length)(void* runtime, void* method);

=head2 get_method_mortal_stack_length

  int32_t (*get_method_mortal_stack_length)(void* runtime, void* method);

=head2 get_method_opcodes_base

  int32_t (*get_method_opcodes_base)(void* runtime, void* method);

=head2 get_method_opcodes_length

  int32_t (*get_method_opcodes_length)(void* runtime, void* method);

=head2 get_method_args_base

  int32_t (*get_method_args_base)(void* runtime, void* method);

=head2 get_method_args_length

  int32_t (*get_method_args_length)(void* runtime, void* method);

=head2 get_native_method_address

  void* (*get_native_method_address)(void* runtime, void* method);

=head2 set_native_method_address

  void (*set_native_method_address)(void* runtime, void* method, void* address);

=head2 get_precompile_method_address

  void* (*get_precompile_method_address)(SPVM_ENV*, void* method);

=head2 set_precompile_method_address

  void (*set_precompile_method_address)(void* runtime, void* method, void* address);

=head2 object_header_size

  void* object_header_size;

=head2 object_ref_count_offset

  void* object_ref_count_offset;

=head2 object_length_offset

  void* object_length_offset;

=head2 get_allocator

  void* (*get_allocator)(void* runtime);

=head2 build

  void (*build)(void* runtime, int32_t* runtime_codes);

=head2 get_basic_type_parent_basic_type_id

  int32_t (*get_basic_type_parent_basic_type_id)(void* runtime, int32_t basic_type_id);

=head2 get_method_required_args_length

  int32_t (*get_method_required_args_length)(void* runtime, void* method);

=head2 get_basic_type_is_pointer

  int32_t (*get_basic_type_is_pointer)(void* runtime, int32_t basic_type_id);

=head2 get_method_is_enum

  int32_t (*get_basic_type_is_pointer)(void* runtime, int32_t basic_type_id);

=head2 is_object_type

  int32_t (*is_object_type)(void* runtime, int32_t basic_type_id, int32_t type_dimension, int32_t flag);

=head2 get_basic_type_version_string_id

  int32_t (*get_basic_type_version_string_id)(void* runtime, int32_t basic_type_id);

Gets the ID of the constant string of the version number.

=head2 can_assign

  int32_t (*can_assign)(void* runtime, int32_t dist_basic_type_id, int32_t dist_type_dimension, int32_t dist_type_flag, int32_t src_basic_type_id, int32_t src_type_dimension, int32_t src_type_flag);

=head2 get_field_basic_type_id

  int32_t (*get_field_basic_type_id)(void* runtime, void* field);

=head2 get_field_type_dimension

  int32_t (*get_field_type_dimension)(void* runtime, void* field);

=head2 get_field_type_flag

  int32_t (*get_field_type_flag)(void* runtime, void* field);

=head2 get_field_basic_type_id

  int32_t (*get_field_basic_type_id)(void* runtime, void* field);

=head2 get_field_type_dimension

  int32_t (*get_field_type_dimension)(void* runtime, void* field);

=head2 get_field_type_flag

  int32_t (*get_field_type_flag)(void* runtime, void* field);

=head2 get_method_return_basic_type_id

  int32_t (*get_method_return_basic_type_id)(void* runtime, void* method);

=head2 get_method_return_type_dimension

  int32_t (*get_method_return_type_dimension)(void* runtime, void* method);

=head2 get_method_return_type_flag

  int32_t (*get_method_return_type_flag)(void* runtime, void* method);

=head2 get_arg_basic_type_id

  int32_t (*get_arg_basic_type_id)(void* runtime, int32_t arg_id);

=head2 get_arg_type_dimension

  int32_t (*get_arg_type_dimension)(void* runtime, int32_t arg_id);

=head2 get_arg_type_flag

  int32_t (*get_arg_type_flag)(void* runtime, int32_t arg_id);

=head2 get_method_current_basic_type_id

  int32_t (*get_method_current_basic_type_id)(void* runtime, void* method);

=head2 get_field_current_basic_type_id

  int32_t (*get_field_current_basic_type_id)(void* runtime, void* field);

=head2 get_field_current_basic_type_id

  int32_t (*get_field_current_basic_type_id)(void* runtime, void* field);

=head2 get_basic_type_parent_id

  int32_t (*get_basic_type_parent_id)(void* runtime, int32_t basic_type_id);

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
