=head1 Name

SPVM::Document::NativeAPI::Runtime - SPVM Runtime Native APIs

=head1 Usage

  // Runtime Native API
  SSPVM_ENV_RUNTIME* runtime_api = env->api->runtime;
  
  // New a runtime object
  void* runtime = runtime_api->new_instance();
  
  // Free a runtime object
  env->api->runtime->free_instance(runtime);

=head1 Description

SPVM Runtime Native APIs are the APIs to manipulate runtime information.

=head1 IDs of Runtime Native APIs

Runtime native APIs have its IDs.

  0  new_instance
  1  free_instance
  2  get_opcodes
  3  reserved3
  4  reserved4
  5  reserved5
  6  reserved6
  7  reserved7
  8  reserved8
  9  reserved9
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
  76 reserved76
  77 reserved77
  78 reserved78
  79 get_method_required_args_length
  80 reserved80
  81 get_method_is_enum
  82 reserved82
  83 is_object_type
  84 reserved84
  85 reserved85
  86 can_assign
  87 get_basic_type_module_rel_file
  88 get_basic_type_module_dir
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
  99   get_basic_types_length
  100   get_field_basic_type
  101   get_field_type_dimension
  102   get_field_type_flag
  103   get_class_var_basic_type
  104   get_class_var_type_dimension
  105   get_class_var_type_flag
  106   get_method_return_basic_type
  107   get_method_return_type_dimension
  108   get_method_return_type_flag
  109   get_arg_basic_type
  110   get_arg_type_dimension
  111   get_arg_type_flag
  112   get_method_current_basic_type
  113   get_field_current_basic_type
  114   get_class_var_current_basic_type
  115   get_basic_type_parent
  116   get_basic_type_version_string
  117   get_basic_type
  118   get_field
  119   get_method
  120   reserved120,
  121   reserved121
  122   get_class_var_by_name
  123   get_field_by_name
  124   get_method_by_name
  125   get_basic_type_id
  126   reserved126
  127   get_method_index
  128   reserved128,
  129   get_class_var_index
  130   get_field_index
  131   get_field_offset
  132   get_arg
  133   get_basic_type_by_name
  134   get_basic_type_anon_basic_type

=head1 Runtime Native APIs

=head2 new_instance

  void* (*new_instance)(void);

=head2 free_instance

  void (*free_instance)(void* runtime);

=head2 get_opcodes

  int32_t* (*get_opcodes)(void* runtime);

=head2 get_basic_type_id_by_name

  int32_t (*get_basic_type_id_by_name)(void* runtime, const char* basic_type_name);

=head2 get_basic_type_name

  const char* (*get_basic_type_name)(void* runtime, void* basic_type);

=head2 get_basic_type_category

  int32_t (*get_basic_type_category)(void* runtime, void* basic_type);

=head2 get_basic_type_module_rel_file

  const char* (*get_basic_type_module_rel_file)(void* runtime, void* basic_type);

=head2 get_basic_type_module_dir

  const char* (*get_basic_type_module_dir)(void* runtime, void* basic_type);

=head2 get_basic_type_is_anon

  int32_t (*get_basic_type_is_anon)(void* runtime, void* basic_type);

=head2 get_basic_type_fields_base

  int32_t (*get_basic_type_fields_base)(void* runtime, void* basic_type);

=head2 get_basic_type_fields_length

  int32_t (*get_basic_type_fields_length)(void* runtime, void* basic_type);

=head2 get_basic_type_methods_base

  int32_t (*get_basic_type_methods_base)(void* runtime, void* basic_type);

=head2 get_basic_type_methods_length

  int32_t (*get_basic_type_methods_length)(void* runtime, void* basic_type);

=head2 get_basic_type_class_vars_base

  int32_t (*get_basic_type_class_vars_base)(void* runtime, void* basic_type);

=head2 get_basic_type_class_vars_length

  int32_t (*get_basic_type_class_vars_length)(void* runtime, void* basic_type);
  
=head2 get_basic_types_length

  int32_t (*get_basic_types_length)(void* runtime);
  
=head2 get_field_basic_type

  void* (*get_field_basic_type)(void* runtime, void* field);
  
=head2 get_field_type_dimension

  int32_t (*get_field_type_dimension)(void* runtime, void* field);
  
=head2 get_field_type_flag

  int32_t (*get_field_type_flag)(void* runtime, void* field);
  
=head2 get_class_var_basic_type

  void* (*get_class_var_basic_type)(void* runtime, void* class_var);
  
=head2 get_class_var_type_dimension

  int32_t (*get_class_var_type_dimension)(void* runtime, void* class_var);
  
=head2 get_class_var_type_flag

  int32_t (*get_class_var_type_flag)(void* runtime, void* class_var);
  
=head2 get_method_return_basic_type

  void* (*get_method_return_basic_type)(void* runtime, void* method);
  
=head2 get_method_return_type_dimension

  int32_t (*get_method_return_type_dimension)(void* runtime, void* method);
  
=head2 get_method_return_type_flag

  int32_t (*get_method_return_type_flag)(void* runtime, void* method);
  
=head2 get_arg_basic_type

  void* (*get_arg_basic_type)(void* runtime, void* arg);
  
=head2 get_arg_type_dimension

  int32_t (*get_arg_type_dimension)(void* runtime, void* arg);
  
=head2 get_arg_type_flag

  int32_t (*get_arg_type_flag)(void* runtime, void* arg);
  
=head2 get_method_current_basic_type

  void* (*get_method_current_basic_type)(void* runtime, void* method);
  
=head2 get_field_current_basic_type

  void* (*get_field_current_basic_type)(void* runtime, void* field);
  
=head2 get_class_var_current_basic_type

  void* (*get_class_var_current_basic_type)(void* runtime, void* class_var);
  
=head2 get_basic_type_parent

  void* (*get_basic_type_parent)(void* runtime, void* basic_type);
  
=head2 get_basic_type_version_string

  const char* (*get_basic_type_version_string)(void* runtime, void* basic_type);
  
=head2 get_basic_type_by_id

  void* (*get_basic_type_by_id)(void* runtime, int32_t basic_type_id);
  
=head2 get_field

  void* (*get_field)(void* runtime, void* basic_type, int32_t field_index);
  
=head2 get_method

  void* (*get_method)(void* runtime, void* basic_type, int32_t method_index);
  
=head2 get_class_var_by_name

  void* (*get_class_var_by_name)(void* runtime, void* basic_type, const char* class_var_name);
  
=head2 get_field_by_name

  void* (*get_field_by_name)(void* runtime, void* basic_type, const char* field_name);
  
=head2 get_method_by_name

  void* (*get_method_by_name)(void* runtime, void* basic_type, const char* method_name);
  
=head2 get_basic_type_id

  int32_t (*get_basic_type_id)(void* runtime, void* basic_type);
  
=head2 get_method_index

  int32_t (*get_method_index)(void* runtime, void* method);
  
=head2 get_class_var_index

  int32_t (*get_class_var_index)(void* runtime, void* class_var);
  
=head2 get_field_index

  int32_t (*get_field_index)(void* runtime, void* field);
  
=head2 get_field_offset

  int32_t (*get_field_offset)(void* runtime, void* field);
  
=head2 get_arg

  void* (*get_arg)(void* runtime, void* method, int32_t arg_index);
  
=head2 get_basic_type_by_name

  void* (*get_basic_type_by_name)(void* runtime, const char* basic_type_name);
  
=head2 

  void* (*get_basic_type_anon_basic_type)(void* runtime, void* basic_type, int32_t anon_basic_type_index);

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
